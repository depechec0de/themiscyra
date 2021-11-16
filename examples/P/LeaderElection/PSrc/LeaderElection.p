event eMessage : MessageType;

event ElectMeMessage: ElectMeType;
event LeaderIsMessage: LeaderIsType;
event LeaderRequest: LeaderRequestType;
event eConfig: set[machine];

type Command = int;
type Phase = int;
type Mbox = map[Phase, map[Round, set[MessageType]]];
type Timestamp = (phase: Phase, round: Round);
type Log = map[Phase, any];
type MessageType = (phase: Phase, from: machine, payload: any);
type ElectMeType = (phase: Phase, from: machine, payload: machine);
type LeaderIsType = (phase: Phase, from: machine, payload: machine);
type LeaderRequestType = int;

enum Round { ELECTME, LEADERIS }

machine Process {   
    var participants : set[machine];
    var phase : Phase;
    var mbox : Mbox;
    var log : Log;
    var timer : Timer;

    start state Init {
        defer LeaderRequest, LeaderIsMessage, ElectMeMessage;
        
        entry {
            receive {
                case eConfig: (payload: set[machine]) { 
                    participants = payload;
                }
            }
            timer = CreateTimer(this);

            phase = 0;
            goto WaitForLeaderRequest;
        }
    }

    state WaitForLeaderRequest {
        defer ElectMeMessage, LeaderIsMessage;

        on LeaderRequest do (transId : LeaderRequestType) 
        {
            goto ElectMe;
        }
    }

    state ElectMe {
        defer LeaderRequest, LeaderIsMessage;

        entry {
            init_mbox(phase);

            StartTimer(timer);

            if(primary(phase) == this){
                UnReliableBroadCast(participants, ElectMeMessage, (phase=phase, from=this, dst=null, payload = this));
            }
        }

        on ElectMeMessage do (m : ElectMeType) {
            CancelTimer(timer);
            if(m.phase > phase){ 
                phase = m.phase;
            }
            goto LeaderIs;
        }

        on eTimeOut do { timeout(); }
    }

    state LeaderIs {
        defer LeaderRequest, ElectMeMessage;

        entry {
            UnReliableBroadCast(participants, LeaderIsMessage, (phase=phase, from=this, dst=null, payload = primary(phase)));
            StartTimer(timer);
        }

        on LeaderIsMessage do (m : LeaderIsType) {

            if(m.payload == primary(m.phase)){
                collectMessage(m, LEADERIS);
            }

            if(sizeof(mbox[m.phase][LEADERIS]) > sizeof(participants)/2){
                CancelTimer(timer);
                insertLogEntry(phase, m.payload);
                
                phase = phase+1;
                goto WaitForLeaderRequest;
            }
        }

        on eTimeOut do { timeout(); }
    }

    fun init_mbox(phase: Phase) {
        mbox[phase] = default(map[Round, set[MessageType]]);

        mbox[phase][LEADERIS] = default(set[MessageType]);
    }

    fun collectMessage(m:MessageType, r: Round) {
        if(!(m.phase in mbox)){
            init_mbox(m.phase);
        }
        mbox[m.phase][r] += (m);
    }

    fun timeout() {
        insertLogEntry(phase, null);
        phase = phase+1;
        goto WaitForLeaderRequest;
    }

    fun insertLogEntry(p: Phase, e: any) {
        announce eMonitor_NewLogEntry, (phase=p, logentry=e);
        log[p] = e;
    }

    fun primary(phase: Phase) : machine {
        return participants[0];
    }
}