event eMessage : Message;

event eventSTARTVIEWCHANGE: (phase: Phase, from: machine, dst: machine, payload: data);
event eventDOVIEWCHANGE: (phase: Phase, from: machine, dst: machine, payload: data);
event eventSTARTVIEW: (phase: Phase, from: machine, dst: machine, payload: data);

type Command = int;
type Phase = int;
type Mbox = map[Phase, map[Round, seq[Message]]];
type Timestamp = (phase: Phase, round: Round);
type Message = (phase: Phase, from: machine, dst: machine, payload: data);
type ClientRequest = (transactionId: int, command: string);

event eConfig: (participants: seq[Replica], leader: Replica);
event eClientRequest: ClientRequest;

enum Round { STARTVIEWCHANGE, DOVIEWCHANGE, STARTVIEW }

machine Replica
{
    var phase : Phase;
    var leader : Replica;
    var participants: seq[Replica];
    var mbox : Mbox;

    start state Init 
    {
        defer eClientRequest, eventSTARTVIEWCHANGE, eventDOVIEWCHANGE, eventSTARTVIEW;

        entry
        {
            phase = 0;
            receive {
                case eConfig: (payload: (participants: seq[Replica], leader: Replica)) { 
                    participants = payload.participants;
                    leader = payload.leader;
                }
            }
            goto STARTVIEWCHANGE;
        }
    }

    state STARTVIEWCHANGE
    {
        defer eventDOVIEWCHANGE, eventSTARTVIEW;

        entry {
            initMbox(phase);
        }

        on eClientRequest do (m : ClientRequest) 
        {
            var newcommand : Command;
            
            broadcast(eventSTARTVIEWCHANGE, phase, this, newcommand);
            goto DOVIEWCHANGE;
        }

        on eventSTARTVIEWCHANGE do (m : Message) 
        {
            announce eMonitor_MessageReceived, (localTs=(phase=phase, round=STARTVIEWCHANGE), msgTs=(phase=m.phase, round=STARTVIEWCHANGE));

            assert(m.phase in mbox);

            announce eMonitor_MailboxUsed, (id=this, mboxTs=(phase=m.phase, round=STARTVIEWCHANGE));
            mbox[m.phase][STARTVIEWCHANGE] += (sizeof(mbox[m.phase][STARTVIEWCHANGE]),m);

            if(sizeof(mbox[m.phase][STARTVIEWCHANGE]) > sizeof(participants)/2)
            { 
                goto DOVIEWCHANGE;
            }
        }

    }

    state DOVIEWCHANGE
    {
        defer eClientRequest, eventSTARTVIEWCHANGE, eventSTARTVIEW;

        entry {
            var newcommand : Command;

            announce eMonitor_TimestampChange, (id=this, ts=(phase=phase, round=DOVIEWCHANGE));

            send leader, eventDOVIEWCHANGE, (phase = phase, from=this, dst=leader, payload = newcommand);

            if(this != leader){
                goto STARTVIEW;
            }
            
        }

        on eventDOVIEWCHANGE do (m : Message) 
        {
            announce eMonitor_MessageReceived, (localTs=(phase=phase, round=DOVIEWCHANGE), msgTs=(phase=m.phase, round=DOVIEWCHANGE));

            announce eMonitor_MailboxUsed, (id=this, mboxTs=(phase=m.phase, round=DOVIEWCHANGE));
            mbox[m.phase][DOVIEWCHANGE] += (sizeof(mbox[m.phase][DOVIEWCHANGE]),m);

            if(sizeof(mbox[m.phase][DOVIEWCHANGE]) > sizeof(participants)/2)
            { 
                computes_new_log();
                goto STARTVIEW;
            }
        }

    }

    state STARTVIEW
    {
        defer eClientRequest, eventSTARTVIEWCHANGE, eventDOVIEWCHANGE;

        entry {
            var newcommand : Command;

            announce eMonitor_TimestampChange, (id=this, ts=(phase=phase, round=STARTVIEW));

            if(this == leader){
                broadcast(eventSTARTVIEW, phase, this, newcommand);
            }
            
        }

        on eventSTARTVIEW do (m : Message) 
        {
            announce eMonitor_MessageReceived, (localTs=(phase=phase, round=STARTVIEW), msgTs=(phase=m.phase, round=STARTVIEW));

            announce eMonitor_MailboxUsed, (id=this, mboxTs=(phase=m.phase, round=STARTVIEW));
            mbox[m.phase][STARTVIEW] += (sizeof(mbox[m.phase][STARTVIEW]),m);

            computes_new_log();

            phase = phase+1;
            goto STARTVIEWCHANGE;
        }

    }

    fun broadcast(message: event, phase: Phase, from: machine, payload: data)
    {
        var i: int; i = 0;
        
        while (i < sizeof(participants)) 
        {
            send participants[i], message, (phase=phase, from=from, dst=participants[i], payload = payload);
            i = i + 1;
        }
    }

    fun initMbox(phase: Phase)
    {
        mbox[phase] = default(map[Round, seq[Message]]);

        mbox[phase][STARTVIEWCHANGE] = default(seq[Message]);
        mbox[phase][DOVIEWCHANGE] = default(seq[Message]);
        mbox[phase][STARTVIEW] = default(seq[Message]);
    }

    fun computes_new_log()
    {
        
    }
}