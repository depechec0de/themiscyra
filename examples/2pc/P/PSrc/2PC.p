event eMessage : Message;

event eventALPHA: (phase: Phase, from: machine, payload: AlphaPayload);
event eventBETA: (phase: Phase, from: machine, payload: BetaPayload);
event eventGAMMA: (phase: Phase, from: machine, payload: GammaPayload);
event eventDELTA: (phase: Phase, from: machine, payload: DeltaPayload);

type Command = int;
type Phase = int;
type Mbox = map[Phase, map[Round, seq[Message]]];
type Timestamp = (phase: Phase, round: Round);

event configMessage: Primary;
event eClientRequest: ClientRequest;

type ClientRequest = (transactionId: int, command: string);

type Message = (phase: Phase, from: machine, payload: data);

type AlphaPayload = Command;
type BetaPayload = Vote;
type GammaPayload = Vote;
type DeltaPayload = bool;

enum Round { ALPHA, BETA, GAMMA, DELTA }
enum Vote {COMMIT, ABORT}

machine Primary
{
    var numBackup : int;
    var backups : seq[Backup];
    var phase : Phase;
    var mbox : Mbox;
    var commitvotes : map[Phase, int];
    var decision : map[Phase, Vote];

    start state Init 
    {
        defer eClientRequest;

        entry (b: seq[Backup]){
            var participants : seq[machine];

            backups = b;
            numBackup = sizeof(backups);
            sendConfig();

            participants = backups;
            participants += (sizeof(participants), this);

            announce eMonitor_Initialize, participants;

            phase = 0; 

            goto ALPHA;
        }
    }

    state ALPHA 
    {
        defer eventALPHA, eventBETA, eventDELTA, eventGAMMA;

        entry {
            announce eMonitor_TimestampChange, (id=this, ts=(phase=phase, round=ALPHA));
        }

        on eClientRequest do (m : ClientRequest) 
        {
            var newcommand : Command;

            initMbox(phase);

            broadcast(eventALPHA, (phase = phase, from=this, payload = newcommand));
            goto BETA;
        }
    }

    state BETA 
    {
        defer eClientRequest, eventALPHA, eventGAMMA, eventDELTA;

        entry {
            announce eMonitor_TimestampChange, (id=this, ts=(phase=phase, round=BETA));
        }

        on eventBETA do (m : Message) 
        {
            announce eMonitor_MessageReceived, (localTs=(phase=phase, round=BETA), msgTs=(phase=m.phase, round=BETA));

            announce eMonitor_MailboxUsed, (id=this, mboxTs=(phase=m.phase, round=BETA));
            if(m.payload == COMMIT)
            {
                commitvotes[m.phase] = commitvotes[m.phase]+1;
            }

            mbox[m.phase][BETA] += (sizeof(mbox[m.phase][BETA]),m);

            //print format("Primary receives eventBETA {0} / {1}", sizeof(mbox[m.phase][BETA]), numBackup);

            if(sizeof(mbox[m.phase][BETA]) == numBackup)
            {
                decision[m.phase] = commit_or_abort(m.phase); 
                goto GAMMA;
            }
        }
    }

    state GAMMA 
    {
        defer eClientRequest, eventALPHA, eventBETA, eventDELTA;

        entry 
        {
            announce eMonitor_TimestampChange, (id=this, ts=(phase=phase, round=GAMMA));

            broadcast(eventGAMMA, (phase = phase, from=this, payload = decision[phase]));
            goto DELTA;
        }
    }

    state DELTA 
    {
        defer eClientRequest, eventALPHA, eventBETA, eventGAMMA;

        entry {
            announce eMonitor_TimestampChange, (id=this, ts=(phase=phase, round=DELTA));
        }

        on eventDELTA do (m : Message) 
        {
            announce eMonitor_MessageReceived, (localTs=(phase=phase, round=DELTA), msgTs=(phase=m.phase, round=DELTA));

            announce eMonitor_MailboxUsed, (id=this, mboxTs=(phase=m.phase, round=DELTA));
            mbox[m.phase][DELTA] += (sizeof(mbox[m.phase][DELTA]),m);

            if(sizeof(mbox[m.phase][DELTA]) == numBackup)
            {
                phase = phase+1;
                goto ALPHA;
            }
        }
    }

    fun initMbox(phase: Phase)
    {
        commitvotes[phase] = 0;

        mbox[phase] = default(map[Round, seq[Message]]);

        mbox[phase][ALPHA] = default(seq[Message]);
        mbox[phase][BETA] = default(seq[Message]);
        mbox[phase][GAMMA] = default(seq[Message]);
        mbox[phase][DELTA] = default(seq[Message]);
    }

    fun commit_or_abort(phase: Phase) : Vote
    {
        var decision : Vote;
        decision = ABORT;
        if(commitvotes[phase] == numBackup)
        {
            decision = COMMIT;
        }

        return decision;
    }

    fun broadcast(message: event, payload: Message)
    {
        var i: int; i = 0;
        while (i < numBackup) 
        {
            send backups[i], message, payload;
            i = i + 1;
        }
    }

    fun sendConfig()
    {
        var i : int;
        i = 0;
        while (i < numBackup) 
        {
            send backups[i], configMessage, this;
            i = i + 1;
        }
    }
}

machine Backup
{
    var phase : Phase;
    var leader : Primary;
    var decision : map[Phase, Vote];

    start state Init 
    {
        entry
        {
            phase = 0;
            receive {
                case configMessage: (payload: Primary) { 
                    leader = payload;
                }
            }
            goto ALPHA;
        }
    }

    state ALPHA 
    {
        on eventALPHA do (m : Message) 
        {
            announce eMonitor_MessageReceived, (localTs=(phase=phase, round=ALPHA), msgTs=(phase=m.phase, round=ALPHA));
            announce eMonitor_TimestampChange, (id=this, ts=(phase=phase, round=ALPHA));
            goto BETA;
        }
    }

    state BETA 
    {

        entry 
        {
            var v : Vote;
            
            announce eMonitor_TimestampChange, (id=this, ts=(phase=phase, round=BETA));

            v = ABORT;
            if($)
            {
                v = COMMIT;
            }
            send leader(phase), eventBETA, (phase = phase, from=this, payload = v);
            goto GAMMA;
        }

    }

    state GAMMA 
    {
        entry {
            announce eMonitor_TimestampChange, (id=this, ts=(phase=phase, round=GAMMA));
        }

        on eventGAMMA do (m : Message) 
        {
            announce eMonitor_MessageReceived, (localTs=(phase=phase, round=GAMMA), msgTs=(phase=m.phase, round=GAMMA));

            announce eMonitor_MailboxUsed, (id=this, mboxTs=(phase=m.phase, round=GAMMA));
            if(m.payload == COMMIT)
            {
                decision[phase] = COMMIT;
            } else {
                decision[phase] = ABORT;
            }
            goto DELTA;
        }
    }

    state DELTA {
        entry 
        {
            announce eMonitor_TimestampChange, (id=this, ts=(phase=phase, round=DELTA));

            send leader(phase), eventDELTA, (phase = phase, from=this, payload=true);
            phase = phase+1;
            goto ALPHA;
        }
    }

    fun leader(phase: int) : Primary
    {
        return leader;
    }
}
