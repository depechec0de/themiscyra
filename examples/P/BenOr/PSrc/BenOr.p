event eMessage : MessageType;

event ReportMessage: ReportType;
event DecisionMessage: DecisionType;

event ConsensusRequest: ConsensusType;
event Config: (peers: set[machine], quorum: int) ;

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
    var quorum : int;
    var K : Phase;
    var mbox : Mbox;
    var log : Log;
    var timer : Timer;
    var estimate : Value;
    var decision : Value;
    var currentRequest : RequestId;

    start state Init {
        defer ConsensusRequest, ReportMessage, DecisionMessage;
        
        entry {
            receive {
                case Config: (payload: (peers: set[machine], quorum: int)) { 
                    participants = payload.peers;
                    quorum = payload.quorum;
                }
            }
            timer = CreateTimer(this);

            decision = -1;
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
        defer ConsensusRequest;

        entry {
            UnReliableBroadCast(participants, ReportMessage, (phase=K, from=this, payload = estimate));
            StartTimer(timer);
        }

        on ReportMessage do (m : ReportType) {
            
            if(m.phase >= K){
                collectMessage(m, REPORT);

                if(m.phase > K){
                    // Jump
                    K = m.phase;
                    CancelTimer(timer);
                    print(format("{0} jumped to {1} Report", this, K ));
                    goto Report;
                }
                
                if(sizeof(mbox[K][REPORT]) >= quorum){
                    print(format("{0} reached report in phase {1}", this, K));
                    CancelTimer(timer);
                    estimate = mayority_value(mbox[K][REPORT], quorum);
                    goto Decision;
                }

            }
            
        }

        on DecisionMessage do (m : DecisionType) {
            if(m.phase >= K){
                // Jump
                CancelTimer(timer);
                print(format("{0} jumped to {1} Decision", this, K ));
                collectMessage(m, DECISION);

                K = m.phase;
                goto Decision;
            }
        }

        on eShutDown do {
            raise halt;
        }

        on eTimeOut do {
            timeout();
            //goto Report;
        }
    }

    state Decision {
        defer ConsensusRequest;

        entry { 
            if(decision != -1){
                UnReliableBroadCast(participants, DecisionMessage, (phase=K, from=this, payload = decision));
            }else{
                UnReliableBroadCast(participants, DecisionMessage, (phase=K, from=this, payload = estimate));
                StartTimer(timer);
            }           
        }

        on ReportMessage do (m : ReportType) {
            if(m.phase > K){
                // Jump
                CancelTimer(timer);
                print(format("{0} jumped to {1} Report", this, K ));

                collectMessage(m, REPORT);
                K = m.phase;
                goto Report;
            }
        }

        on DecisionMessage do (m : DecisionType) {
            var val : Value;
            var coin_toss : int;

            if(m.phase >= K){
                collectMessage(m, DECISION);

                if(m.phase > K){
                    // Jump
                    CancelTimer(timer);
                    print(format("{0} jumped to {1} Report", this, K ));

                    K = m.phase;
                    goto Decision;
                }

                if(sizeof(mbox[K][DECISION]) >= quorum){
                    
                    CancelTimer(timer);
                    val = mayority_value(mbox[K][DECISION], quorum);

                    if(val != -1){

                        // decide value
                        print(format("{0} Decided {1} in phase {2}", this, val, K));
                        insertLogEntry(val);
                        decision = val;
                        // K = K+1;

                        // // Keep broadcasting the decision
                        // goto Decision;

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
            
        }

        on eShutDown do {
            raise halt;
        }

        on eTimeOut do {
            timeout();
            //goto Decision;
        }
    }

    fun collectMessage(m:MessageType, r: Round) {
        if(!(m.phase in mbox)){
            init_mbox(m.phase);
        }
        
        mbox[m.phase][r] += (m);

        //print(format("{0} collected message {1} {2} in phase, MAILBOX {3}", this, r, K, mbox));
    }

    fun init_mbox(phase: Phase) {
        mbox[phase] = default(map[Round, set[MessageType]]);

        mbox[phase][REPORT] = default(set[MessageType]);
        mbox[phase][DECISION] = default(set[MessageType]);
    }

    fun insertLogEntry(e: any) {
        if(choose(1000) == 1){
            announce eMonitor_NewLogEntry, (id=this, request=currentRequest, logentry=0);
        }else{
            announce eMonitor_NewLogEntry, (id=this, request=currentRequest, logentry=e);
        }
        
        if(e != null){
            log[currentRequest] = e;
            print(format("insertLogEntry {0} {1}", this, log));
        }
    }

    fun timeout(){
        K = K+1;
        init_mbox(K);
        goto Report;
    }
}

fun mayority_value(msgs : set[MessageType], quorum: int) : Value {
    var count_zero : int;
    var count_one : int;
    var i : int;

    count_one = 0;
    count_one = 0;

    i = 0;

    while(i < sizeof(msgs)){
        if(msgs[i].payload == 0){
            count_zero=count_zero+1;
        }else if(msgs[i].payload == 1){
            count_one=count_one+1;
        }
        i=i+1;
    }

    if(count_zero >= quorum){
        return 0;
    }else if(count_one >= quorum){
        return 1;
    }else{
        return -1;
    }
}

fun get_valid_estimate(msgs : set[MessageType]) : Value{
    var i : int;

    print(format("get_valid_estimate {0}", msgs));

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