event eMessage : Message;

event eventSTARTVIEWCHANGE: (phase: Phase, from: machine, dst: machine, payload: data);
event eventDOVIEWCHANGE: (phase: Phase, from: machine, dst: machine, payload: data);
event eventSTARTVIEW: (phase: Phase, from: machine, dst: machine, payload: data);

type Command = int;
type Phase = int;
type Mbox = map[Phase, map[Round, set[Message]]];
type Timestamp = (phase: Phase, round: Round);
type Message = (phase: Phase, from: machine, dst: machine, payload: data);
type ClientRequest = (transactionId: int, command: string);

event eConfig: (participants: set[Replica], leader: Replica);
event eClientRequest: ClientRequest;

enum Round { STARTVIEWCHANGE, DOVIEWCHANGE, STARTVIEW }

machine Replica
{
    var phase : Phase;
    var leader : Replica;
    var participants: set[Replica];
    var mbox : Mbox;
    var timer : Timer;

    start state Init 
    {
        defer eClientRequest, eventSTARTVIEWCHANGE, eventDOVIEWCHANGE, eventSTARTVIEW;

        entry
        {
            receive {
                case eConfig: (payload: (participants: set[Replica], leader: Replica)) { 
                    participants = payload.participants;
                    leader = payload.leader;
                }
            }

            phase = 0;
            
            timer = CreateTimer(this);
            goto WaitForClientRequest;
        }
    }

    state WaitForClientRequest
    {
        defer eventDOVIEWCHANGE, eventSTARTVIEWCHANGE, eventSTARTVIEW;

        on eClientRequest do (m : ClientRequest) 
        {
            goto STARTVIEWCHANGE;
        }

    }

    state STARTVIEWCHANGE
    {
        defer eClientRequest, eventDOVIEWCHANGE, eventSTARTVIEW;

        entry {
            var newcommand : Command;

            UnReliableBroadCast(participants, eventSTARTVIEWCHANGE, (phase=phase, from=this, dst=null, payload = newcommand));
            StartTimer(timer);
        }

        on eventSTARTVIEWCHANGE do (m : Message) 
        {
            announce eMonitor_MessageReceived, (localTs=(phase=phase, round=STARTVIEWCHANGE), msgTs=(phase=m.phase, round=STARTVIEWCHANGE));

            announce eMonitor_MailboxUsed, (id=this, mboxTs=(phase=m.phase, round=STARTVIEWCHANGE));
            collectMessage(m, STARTVIEWCHANGE);

            if(sizeof(mbox[m.phase][STARTVIEWCHANGE]) > sizeof(participants)/2)
            { 
                CancelTimer(timer);
                goto DOVIEWCHANGE;
            }
        }

        on eTimeOut do { raise halt; }

    }

    state DOVIEWCHANGE
    {
        defer eClientRequest, eventSTARTVIEWCHANGE, eventSTARTVIEW;

        entry {
            var newcommand : Command;

            announce eMonitor_TimestampChange, (id=this, ts=(phase=phase, round=DOVIEWCHANGE));

            UnReliableSend(leader, eventDOVIEWCHANGE, (phase = phase, from=this, dst=leader, payload = newcommand));

            if(this == leader){
                StartTimer(timer);
            }else{
                goto STARTVIEW;
            }
            
        }

        on eventDOVIEWCHANGE do (m : Message) 
        {
            announce eMonitor_MessageReceived, (localTs=(phase=phase, round=DOVIEWCHANGE), msgTs=(phase=m.phase, round=DOVIEWCHANGE));

            announce eMonitor_MailboxUsed, (id=this, mboxTs=(phase=m.phase, round=DOVIEWCHANGE));
            collectMessage(m, DOVIEWCHANGE);

            if(sizeof(mbox[m.phase][DOVIEWCHANGE]) > sizeof(participants)/2)
            { 
                computes_new_log();
                CancelTimer(timer);
                goto STARTVIEW;
            }
        }

        on eTimeOut do { raise halt; }

    }

    state STARTVIEW
    {
        defer eClientRequest, eventSTARTVIEWCHANGE, eventDOVIEWCHANGE;

        entry {
            var newcommand : Command;

            announce eMonitor_TimestampChange, (id=this, ts=(phase=phase, round=STARTVIEW));

            if(this == leader){
                UnReliableBroadCast(participants, eventSTARTVIEW, (phase=phase, from=this, dst=null, payload = newcommand));
            }

            StartTimer(timer);
            
        }

        on eventSTARTVIEW do (m : Message) 
        {
            announce eMonitor_MessageReceived, (localTs=(phase=phase, round=STARTVIEW), msgTs=(phase=m.phase, round=STARTVIEW));

            announce eMonitor_MailboxUsed, (id=this, mboxTs=(phase=m.phase, round=STARTVIEW));
            collectMessage(m, STARTVIEW);

            CancelTimer(timer);

            computes_new_log();

            phase = phase+1;
            goto WaitForClientRequest;
        }

        on eTimeOut do { raise halt; }

    }

    fun initMbox(phase: Phase)
    {
        mbox[phase] = default(map[Round, set[Message]]);

        mbox[phase][STARTVIEWCHANGE] = default(set[Message]);
        mbox[phase][DOVIEWCHANGE] = default(set[Message]);
        mbox[phase][STARTVIEW] = default(set[Message]);
    }

    fun collectMessage(m: Message, r: Round)
    {
        if(!(m.phase in mbox)){
            initMbox(m.phase);
        }
        mbox[m.phase][r] += (m);
    }

    fun computes_new_log()
    {
        
    }
}