type Messages = map[machine, Mbox];

machine BenOrSync
{
    var K : Phase;
    var maxFailures : int;
    var quorum : int;
    var participants : set[machine];
    var logs : map[machine, Log];
    var estimates : map[machine, Value];
    var messages : Messages;
    var reportRoundSuccessful : map[machine, bool];
    var decided : map[machine, bool];
    var crashedMachines : set[machine];
    var currentRequest : RequestId;

    var i, j: int; 
    var p, from, dst: machine;

    start state Init{
        entry (config: (peers: set[machine], quorum: int, failures: int)){
            
            participants = config.peers;
            maxFailures = config.failures;
            quorum = config.quorum;

            crashedMachines = default(set[machine]);

            i = 0;
            while (i < sizeof(participants)){
                if(sizeof(crashedMachines) < maxFailures){
                    p = participants[i];
                    if($){
                        crashedMachines += (p);
                    }
                }
                i=i+1;
            }

            print(format("Crashed machines {0}", crashedMachines));

            K = 0; 
            init_phase(K);

            i = 0;
            while (i < sizeof(participants)){
                p = participants[i];
                decided[p] = false;
                estimates[p] = choose(2);
                i=i+1;
            }
        }

        on ConsensusRequest do (payload : (request: RequestId, estimate: Value)) 
        {
            currentRequest = payload.request;
            goto Report;
        }

    }

    state Report{
        entry{
            i = 0;
            while (i < sizeof(participants)){
                from = participants[i];

                if(!(from in crashedMachines)){

                    j = 0;
                    while (j < sizeof(participants)){

                        dst = participants[j];
                        if(!(dst in crashedMachines)){
                            print(format("{0} send REPORT message {1} to {2}", from, (phase = K, from=from, payload=estimates[from]), dst));
                            if($){
                                send this, eMessage, (phase = K, from=from, payload=estimates[from]);
                                receiveMessageBlocking(dst, REPORT);
                                print(format("{0} received REPORT estimate {1} in phase {2} from {3}", dst, estimates[from], K, from));
                            }                        
                        }

                        j = j + 1;
                    }

                }
                i = i + 1;
            }

            i = 0;
            while (i < sizeof(participants)){
                p = participants[i];

                if(!(p in crashedMachines)){    

                    if(!decided[p]){
                        if(sizeof(messages[p][K][REPORT]) == quorum){
                            reportRoundSuccessful[p] = true;
                            estimates[p] = mayority_value(messages[p][K][REPORT], quorum);
                            print(format("{0} REPORT mayority {1} in phase {2}, mailbox: {3}", p, estimates[p], K, messages[p][K]));
                        }
                    }

                }
                
                i = i + 1;
            }

            goto Decision;
        }

    }

    state Decision{
        entry{
            var val : Value;

            i = 0;
            while (i < sizeof(participants)){
                from = participants[i];

                if(!(from in crashedMachines)){

                    j = 0;
                    if(reportRoundSuccessful[from] || decided[from]){

                        while (j < sizeof(participants)){

                            dst = participants[j];
                            
                            if(!(dst in crashedMachines)){
                                print(format("{0} send DECISION message {1} to {2}", from, (phase = K, from=from, payload=estimates[from]), dst));
                                if($){
                                    send this, eMessage, (phase = K, from=from, payload=estimates[from]);
                                    receiveMessageBlocking(dst, DECISION);
                                    print(format("{0} received DECISION estimate {1} in phase {2}", dst, estimates[from], K));
                                }
                            }

                            j = j + 1;
                        }

                    }

                }
                i = i + 1;
            }

            i = 0;
            while (i < sizeof(participants)){
                p = participants[i];

                if(!(p in crashedMachines)){    

                    if(!decided[p] && reportRoundSuccessful[p]){

                        if(sizeof(messages[p][K][DECISION]) == quorum){

                            print(format("{0} received enough DECISION messages in phase {1}", p, K));

                            val = mayority_value(messages[p][K][DECISION], quorum);

                            if(val != -1){
                                // decide value
                                print(format("{0} Decided {1} in phase {2}", p, val, K));

                                // BUG
                                if(choose(1000) == 1){
                                    announce eMonitor_NewLogEntry, (id=p, request=currentRequest, logentry=0);
                                }else{
                                    announce eMonitor_NewLogEntry, (id=p, request=currentRequest, logentry=val);
                                }
                                
                                logs[p][K] = val;

                                decided[p] = true;
                                estimates[p] = val;

                            }else if(get_valid_estimate(messages[p][K][DECISION]) != -1){

                                // We try again a new phase proposing a valid value
                                estimates[p] = get_valid_estimate(messages[p][K][DECISION]);
                                print(format("{0} changed estimate to {1} in phase {2}", p, estimates[p], K));
                                
                            }else{
                                estimates[p] = choose(2); // 0 or 1 randomly
                                print(format("{0} Flip a coin {1}", p, estimates[p]));
                            }
                        }else{
                            print(format("{0} did not receive enough DECISION messages in phase {1}", p, K));
                        }

                    }

                }
                i=i+1;
            }

            i = 0;
            while (i < sizeof(participants)){
                p = participants[i];

                if(!decided[p] && !(p in crashedMachines)){
                    print(format("{0} did not decide, start new phase", p));
                    K = K+1;
                    init_phase(K);
                    goto Report;
                }

                i=i+1;
            }
            
        }

       
    }

    fun init_phase(phase: Phase)
    {
        var i: int; 
        var p: machine;
        
        i = 0;
       
        messages = default(Messages);
        reportRoundSuccessful = default(map[machine, bool]);
        
        while (i < sizeof(participants)) {
            p = participants[i];
            reportRoundSuccessful[p] = false;
            logs[p] = default(Log);
            
            messages[p] = default(Mbox);
            messages[p][phase] = default(map[Round, set[MessageType]]);

            messages[p][phase][REPORT] = default(set[ReportType]);
            messages[p][phase][DECISION] = default(set[DecisionType]);

            i = i+1;
        }
    }

    fun receiveMessageBlocking(pdest: machine, r : Round)
    {
        receive {
            case eMessage: (m: MessageType) { 
                messages[pdest][K][r] += (m); 
            }
        }
    }
}
