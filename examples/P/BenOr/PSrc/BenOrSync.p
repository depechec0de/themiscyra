type Messages = map[machine, Mbox];

machine BenOrSync
{
    var K : Phase;
    var participants : set[machine];
    var logs : map[machine, Log];
    var estimates : map[machine, Value];
    var messages : Messages;
    var reportRoundSuccessful : map[machine, bool];
    var decisionRoundSuccessful : map[machine, bool];
    var crashedMachines : set[machine];

    var i, j: int; 
    var p, from, dst: machine;

    start state Init{
        entry (proc: set[machine]){

            participants = proc;
            crashedMachines = default(set[machine]);

            i = 0;
            while (i < sizeof(participants)){
                p = participants[i];
                if($){
                    crashedMachines += (p);
                }
                if(sizeof(crashedMachines) == (sizeof(participants)/2)-1){
                    break;
                }
            }

            print(format("Crashed machines {0}", crashedMachines));

            K = 0; 
            init_phase(K);

            i = 0;
            while (i < sizeof(participants)){
                p = participants[i];
                decisionRoundSuccessful[p] = false;
                estimates[p] = choose(2);
                i=i+1;
            }

            announce eMonitor_Initialize, participants;
        }

        on ConsensusRequest do (m : ConsensusType) { goto Report; }
    }

    state WaitForConsensusRequest {
        defer eMessage;

        on ConsensusRequest do (payload : (request: RequestId, estimate: Value)) 
        {
            goto Report;
        }
    }

    state Report{
        entry{
            i = 0;
            while (i < sizeof(participants)){
                from = participants[i];
                j = 0;
                while (j < sizeof(participants)){

                    dst = participants[j];
                    if(!(dst in crashedMachines)){
                        send this, eMessage, (phase = K, from=from, payload=estimates[from]);
                        receiveMessageBlocking(dst, REPORT);
                        print(format("{0} received Report estimate {1} in phase {2}", dst, estimates[from], K));
                    }

                    j = j + 1;
                }
                i = i + 1;
            }

            i = 0;
            while (i < sizeof(participants)){
                p = participants[i];

                if(!decisionRoundSuccessful[p]){
                    if(sizeof(messages[p][K][REPORT]) > sizeof(participants)/2){
                        reportRoundSuccessful[p] = true;
                        estimates[p] = mayority_value(messages[p][K][REPORT], sizeof(participants));
                        print(format("{0} REPORT mayority {1} in phase {2}", this, estimates[p], K));
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
                j = 0;
                if(reportRoundSuccessful[from]){

                    while (j < sizeof(participants)){

                        dst = participants[j];

                        if(!(dst in crashedMachines)){
                            send this, eMessage, (phase = K, from=from, payload=estimates[p]);
                            receiveMessageBlocking(dst, DECISION);
                            print(format("{0} received Report estimate {1} in phase {2}", dst, estimates[from], K));
                        }

                        j = j + 1;
                    }

                }
                i = i + 1;
            }

            i = 0;
            while (i < sizeof(participants)){
                p = participants[i];
                if(!decisionRoundSuccessful[p] && reportRoundSuccessful[p]){

                    if(sizeof(messages[p][K][DECISION]) > sizeof(participants)/2){

                        val = mayority_value(messages[p][K][DECISION], sizeof(participants));

                        if(mayority_value(messages[p][K][DECISION], sizeof(participants)) != -1){

                            // decide value
                            print(format("{0} Decided {1} in phase {2}", p, val, K));
                            logs[p][K] = val;

                            decisionRoundSuccessful[p] = true;
                            estimates[p] = val;

                        }else if(get_valid_estimate(messages[p][K][DECISION]) != -1){

                            // We try again a new phase proposing a valid value
                            estimates[p] = get_valid_estimate(messages[p][K][DECISION]);
                            
                        }else{
                            estimates[p] = choose(2); // 0 or 1 randomly
                            print(format("{0} Flip a coin {1}", this, estimates[p]));
                        }
                    }

                }
                i=i+1;
            }

            i = 0;
            while (i < sizeof(participants)){
                p = participants[i];

                if(!decisionRoundSuccessful[p] && !(p in crashedMachines)){
                    K = K+1;
                    init_phase(K);
                    goto Report;
                }

                i=i+1;
            }

            goto WaitForConsensusRequest;
            
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
            messages[p][K] = default(map[Round, set[MessageType]]);

            messages[p][K][REPORT] = default(set[ReportType]);
            messages[p][K][DECISION] = default(set[DecisionType]);

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
