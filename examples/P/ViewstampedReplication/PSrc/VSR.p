event eMessage : Message;

event eventSTARTVIEWCHANGE: (phase: Phase, from: machine, dst: machine, payload: data);
event eventDOVIEWCHANGE: (phase: Phase, from: machine, dst: machine, payload: data);
event eventSTARTVIEW: (phase: Phase, from: machine, dst: machine, payload: data);

type Phase = int;
type Mbox = map[Phase, map[Round, set[Message]]];
type Timestamp = (phase: Phase, round: Round);
type Message = (phase: Phase, from: machine, dst: machine, payload: data);
type ClientRequest = (transactionId: int, command: data);
type Log = map[Phase, any];

event eConfig: (participants: set[Replica], leader: Replica);
event eClientRequest: ClientRequest;

enum Round { STARTVIEWCHANGE, DOVIEWCHANGE, STARTVIEW }

machine Replica
{
    var phase : Phase;
    var leader : Replica;
    var log : Log;
    var participants: set[Replica];
    var mbox : Mbox;
    var timer : Timer;
    var command : data;

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
            print(format("{0} enters phase {1}", this, phase));
            
            timer = CreateTimer(this);
            goto WaitForClientRequest;
        }
    }

    state WaitForClientRequest
    {
        defer eventDOVIEWCHANGE, eventSTARTVIEWCHANGE, eventSTARTVIEW;

        on eClientRequest do (m : ClientRequest) 
        {
            if(this == leader){
                UnReliableBroadCast(participants, eClientRequest, m);
            }

            command = m.command;

            goto STARTVIEWCHANGE;
        }
    }

    state STARTVIEWCHANGE
    {
        defer eClientRequest, eventDOVIEWCHANGE, eventSTARTVIEW;

        entry  {
            announce eMonitor_TimestampChange, (id=this, ts=(phase=phase, round=STARTVIEWCHANGE));

            UnReliableBroadCast(participants, eventSTARTVIEWCHANGE, (phase=phase, from=this, dst=null, payload = command));
            StartTimer(timer);
        }

        on eventSTARTVIEWCHANGE do (m : Message) 
        {
            if(m.phase == phase){
                announce eMonitor_MessageReceived, (localTs=(phase=phase, round=STARTVIEWCHANGE), msgTs=(phase=m.phase, round=STARTVIEWCHANGE));

                announce eMonitor_MailboxUsed, (id=this, mboxTs=(phase=m.phase, round=STARTVIEWCHANGE));
                collectMessage(m, STARTVIEWCHANGE);

                if(sizeof(mbox[m.phase][STARTVIEWCHANGE]) > sizeof(participants)/2)
                { 
                    CancelTimer(timer);
                    goto DOVIEWCHANGE;
                }
            }
        }

        on eTimeOut do { 
            timeout();
        }

    }

    state DOVIEWCHANGE
    {
        defer eClientRequest, eventSTARTVIEWCHANGE, eventSTARTVIEW;

        entry {
            var newcommand : data;

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
            if(m.phase == phase){
                announce eMonitor_MessageReceived, (localTs=(phase=phase, round=DOVIEWCHANGE), msgTs=(phase=m.phase, round=DOVIEWCHANGE));

                announce eMonitor_MailboxUsed, (id=this, mboxTs=(phase=m.phase, round=DOVIEWCHANGE));
                collectMessage(m, DOVIEWCHANGE);

                if(sizeof(mbox[m.phase][DOVIEWCHANGE]) > sizeof(participants)/2)
                { 
                    insertLogEntry(phase, m.payload);
                    CancelTimer(timer);
                    goto STARTVIEW;
                }
            }
        }

        on eTimeOut do { 
            timeout();
        }

    }

    state STARTVIEW
    {
        defer eClientRequest, eventSTARTVIEWCHANGE, eventDOVIEWCHANGE;

        entry {
            announce eMonitor_TimestampChange, (id=this, ts=(phase=phase, round=STARTVIEW));

            if(this == leader){
                UnReliableBroadCast(participants, eventSTARTVIEW, (phase=phase, from=this, dst=null, payload = command));
            }

            StartTimer(timer);
            
        }

        on eventSTARTVIEW do (m : Message) 
        {
            if(m.phase == phase){
                announce eMonitor_MessageReceived, (localTs=(phase=phase, round=STARTVIEW), msgTs=(phase=m.phase, round=STARTVIEW));

                announce eMonitor_MailboxUsed, (id=this, mboxTs=(phase=m.phase, round=STARTVIEW));
                collectMessage(m, STARTVIEW);

                CancelTimer(timer);

                insertLogEntry(phase, m.payload);

                phase = phase+1;
                print(format("{0} enters phase {1}", this, phase));

                goto WaitForClientRequest;
            }
        }

        on eTimeOut do { 
            timeout();
        }

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

    fun timeout()
    {
        insertLogEntry(phase, null);
        phase = phase+1;
        goto WaitForClientRequest;
        //raise halt;
    }

    fun insertLogEntry(phase: Phase, e: any)
    {
        announce eMonitor_NewLogEntry, (phase=phase, logentry=e);
        log[phase] = e;
    }
}