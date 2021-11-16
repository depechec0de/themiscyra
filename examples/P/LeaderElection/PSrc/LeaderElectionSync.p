type Messages = map[machine, Mbox];

machine LeaderElectionSync
{
    var numBackups : int;
    var PHASE : Phase;
    var leader : machine;
    var participants : set[machine];
    var electmeReceived : map[machine, map[Phase, bool]];
    var decision : map[machine, map[Phase, any]];

    var messages : Messages;

    var i, j: int; 
    var p, from, dst: machine;

    start state Init{
        entry (p: set[machine]){

            participants = p;
            
            PHASE = 0; 
            leader = participants[0];
            Init(PHASE);

            announce eMonitor_Initialize, participants;
        }

        on LeaderRequest do (m : LeaderRequestType) { goto ElectMe; }
    }

    state ElectMe{
        entry{
            i = 0;
            while (i < sizeof(participants)){
                if($){
                    send this, eMessage, (phase = PHASE, from=leader, payload=leader);
                    p = participants[i];
                    receiveMessageBlocking(p, ELECTME);
                }
                i = i + 1;
            }

            i = 0;
            while (i < sizeof(participants)){
                p = participants[i];
                if(sizeof(messages[p][PHASE][ELECTME]) == 1){
                    electmeReceived[p][PHASE] = true;
                }else{
                    electmeReceived[p][PHASE] = false;
                }
                i = i + 1;
            }

            goto LeaderIs;
        }

    }
    state LeaderIs{
        entry{
            i = 0; j = 0;
            while (i < sizeof(participants)){
                from = participants[i];
                while (j < sizeof(participants)){
                    if(electmeReceived[from][PHASE]){
                        if($){
                            dst = participants[j];
                            send this, eMessage, (phase = PHASE, from=from, payload=leader);
                            receiveMessageBlocking(dst, LEADERIS);
                        }
                    }
                    j = j + 1;
                }
                i = i + 1;
            }

            i = 0;
            while (i < sizeof(participants)){
                p = participants[i];
                if(electmeReceived[p][PHASE]){
                    if (sizeof(messages[p][PHASE][LEADERIS]) > sizeof(participants)/2){
                        decision[p][PHASE] = messages[p][PHASE][LEADERIS][0].payload;  
                        announce eMonitor_NewLogEntry, (phase=PHASE, logentry=decision[p][PHASE]);
                    }
                }
                i=i+1;
            }

            PHASE = PHASE+1;
            Init(PHASE);
        }
        on LeaderRequest do (m : LeaderRequestType) { goto ElectMe; }
       
    }

    fun Init(phase: Phase)
    {
        var i: int; 
        var p: machine;
        
        i = 0;
       
        decision = default(map[machine, map[Phase, machine]]);
        electmeReceived = default(map[machine, map[Phase, bool]]);
        messages = default(Messages);
        
        while (i < sizeof(participants)) {
            p = participants[i];
            decision[p] = default(map[Phase, machine]);
            electmeReceived[p] = default(map[Phase, bool]);
            
            messages[p] = default(Mbox);
            messages[p][PHASE] = default(map[Round, set[MessageType]]);

            messages[p][PHASE][ELECTME] = default(set[ElectMeType]);
            messages[p][PHASE][LEADERIS] = default(set[LeaderIsType]);

            i = i+1;
        }
    }

    fun receiveMessageBlocking(pdest: machine, r : Round)
    {
        receive {
            case eMessage: (m: MessageType) { 
                messages[pdest][PHASE][r] += (m); 
            }
        }
    }
}
