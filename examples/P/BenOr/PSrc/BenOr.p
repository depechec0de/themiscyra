event eMessage : MessageType;

event ReportMessage: ReportType;
event DecisionMessage: DecisionType;

event ConsensusRequest: ConsensusType;
event Config: set[machine];

type Value = int; // 0, 1, -1 = ?
type RequestId = int;
type Phase = int;
type Mbox = map[Phase, map[Round, set[MessageType]]];
type Timestamp = (phase: Phase, round: Round);
type Log = map[RequestId, any];

type MessageType = (phase: Phase, from: machine, payload: any);
type ReportType = (phase: Phase, from: machine, payload: Value);
type DecisionType = (phase: Phase, from: machine, payload: Value);

type ConsensusType = (request: RequestId, estimate: Value);

enum Round { REPORT, DECISION }

machine Process {   
    var participants : set[machine];
    var K : Phase;
    var mbox : Mbox;
    var log : Log;
    var timer : Timer;
    var estimate : Value;
    var currentRequest : RequestId;

    start state Init {
        defer ConsensusRequest, ReportMessage, DecisionMessage;
        
        entry {
            receive {
                case Config: (payload: set[machine]) { 
                    participants = payload;
                }
            }
            timer = CreateTimer(this);

            K = 0;
            goto WaitForConsensusRequest;
        }
    }

    state WaitForConsensusRequest {
        defer ReportMessage, DecisionMessage;

        on ConsensusRequest do (payload : (request: RequestId, estimate: Value)) 
        {
            currentRequest = payload.request;
            estimate = payload.estimate;
            goto Report;
        }

        on eShutDown do {
            raise halt;
        }
    }

    state Report {
        defer ConsensusRequest, DecisionMessage;

        entry {
            init_mbox(K);

            UnReliableBroadCast(participants, ReportMessage, (phase=K, from=this, payload = estimate));
            StartTimer(timer);
        }

        on ReportMessage do (m : ReportType) {
            collectMessage(m, REPORT);

            if(sizeof(mbox[K][REPORT]) > sizeof(participants)/2){
                print(format("{0} reached report in phase {1}", this, K));
                CancelTimer(timer);
                estimate = mayority_value(mbox[K][REPORT], sizeof(participants));
                goto Decision;
            }
            
        }

        on eShutDown do {
            raise halt;
        }

        on eTimeOut do {
            K = K+1;
            goto Report;
        }
    }

    state Decision {
        defer ConsensusRequest, ReportMessage;

        entry {
            var val : Value;
            
            UnReliableBroadCast(participants, DecisionMessage, (phase=K, from=this, payload = val));
            StartTimer(timer);
        }

        on DecisionMessage do (m : DecisionType) {
            var val : Value;
            var coin_toss : int;

            collectMessage(m, DECISION);

            if(sizeof(mbox[K][DECISION]) > sizeof(participants)/2){
                CancelTimer(timer);

                print(format("{0} reached mayority decision in phase {2}", this, val, K));

                val = mayority_value(mbox[K][DECISION], sizeof(participants));

                if(mayority_value(mbox[K][DECISION], sizeof(participants)) != -1){

                    // decide value
                    print(format("{0} Decided {1} in phase {2}", this, val, K));
                    insertLogEntry(val);
                    K = K+1;
                    print(format("{0} moves to phase {1}", this, K));
                    goto WaitForConsensusRequest;

                }else if(get_valid_estimate(mbox[K][DECISION]) != -1){

                    // We try again a new phase proposing a valid value
                    estimate = get_valid_estimate(mbox[K][DECISION]);
                    print(format("{0} got valid estimate {1} in phase {2}", this, estimate, K));
                    K = K+1;
                    goto Report;
                    
                }else{
                    estimate = choose(2); // 0 or 1 randomly
                    print(format("{0} Flip a coin {1}", this, estimate));
                    K = K+1;
                    goto Report;
                }
            }
            
        }

        on eShutDown do {
            raise halt;
        }

        on eTimeOut do {
            K = K+1;
            goto Report;
        }
    }

    fun collectMessage(m:MessageType, r: Round) {
        if(!(m.phase in mbox)){
            init_mbox(m.phase);
        }
        mbox[m.phase][r] += (m);
    }

    fun init_mbox(phase: Phase) {
        mbox[phase] = default(map[Round, set[MessageType]]);

        mbox[phase][REPORT] = default(set[MessageType]);
        mbox[phase][DECISION] = default(set[MessageType]);
    }

    fun insertLogEntry(e: any) {
        announce eMonitor_NewLogEntry, (request=currentRequest, logentry=e);
        if(e != null){
            log[currentRequest] = e;
            print(format("insertLogEntry {0} {1}", this, log));
        }
    }
}

fun mayority_value(msgs : set[MessageType], N: int) : Value {
    var count_zero : int;
    var count_one : int;
    var i : int;

    while(i < sizeof(msgs)){
        if(msgs[i].payload == 0){
            count_zero=count_zero+1;
        }else if(msgs[i].payload == 1){
            count_one=count_one+1;
        }
        i=i+1;
    }

    //print(format("{0} mayority_value {1} {2}", this, count_zero, count_one));

    if(count_zero>N/2){
        return 0;
    }else if(count_one>N/2){
        return 1;
    }else{
        return -1;
    }
}

fun get_valid_estimate(msgs : set[MessageType]) : Value{
    var i : int;

    while(i < sizeof(msgs)){
        if(msgs[i].payload == 0){
            return 0;
        }else if(msgs[i].payload == 1){
            return 1;
        }
        i=i+1;
    }

    return -1;
}