type Messages = map[machine, Mbox];

machine ViewStampedReplicationSync
{
    var numParticipants : int;
    var PHASE : Phase;
    var leader : machine;
    var participants : set[machine];
    var failures : map[machine, map[Phase, bool]];

    var messages : Messages;

    var logs : map[machine,Log];

    var msg_sent: int;
    var command: any;

    var i, j : int;
    var p : machine;

    start state Init 
    {
        entry (p: set[machine]){

            participants = p;
            numParticipants = sizeof(participants);
            
            PHASE = 0; 
            leader = participants[0];
            Init(PHASE);

            announce eMonitor_Initialize, participants;
        }

        on eClientRequest do (m : ClientRequest) 
        {
            command = m.command;
            goto STARTVIEWCHANGE;
        }
    }

    state STARTVIEWCHANGE
    {
        entry 
        {
            i = 0;
            while (i < sizeof(participants)){
                p = participants[i];
                if(!failures[p][PHASE]){
                    j = 0;
                    while (j < numParticipants){
                        if($){
                            send this, eMessage, (phase = PHASE, from=p, dst=participants[j], payload=command);
                            p = participants[j];
                            receiveMessageBlocking(p, STARTVIEWCHANGE);
                        }
                        j = j + 1;
                    }
                }
                i = i + 1;
            }

            i = 0;
            while (i < sizeof(participants)) {
                p = participants[i];

                if(sizeof(messages[p][PHASE][STARTVIEWCHANGE]) > numParticipants/2){
                    // NoOp
                }else{
                    failures[p][PHASE] = true;
                    insertLogEntry(p, PHASE, null);
                }
                i=i+1;
            }

            goto DOVIEWCHANGE;
        }

    }

    state DOVIEWCHANGE
    {
        entry 
        {
            while (i < sizeof(participants)){
                p = participants[i];
                if(!failures[p][PHASE]){
                    if($){
                        send this, eMessage, (phase = PHASE, from=p, dst=leader, payload = command);
                        receiveMessageBlocking(leader, DOVIEWCHANGE);
                    }
                }
                i = i + 1;
            }

            // Update
            i = 0;
            while (i < numParticipants) {
                p = participants[i];

                if(p == leader){
                    if(sizeof(messages[p][PHASE][DOVIEWCHANGE]) > numParticipants/2){
                        insertLogEntry(p, PHASE, command);
                    }else{
                        failures[p][PHASE] = true;
                        insertLogEntry(p, PHASE, null);
                    }
                }else{
                    // Follower NoOp
                }
                i=i+1;
            }
            
            // Primary decides using votes
            goto STARTVIEW;
        }

    }

    state STARTVIEW
    {
        entry 
        {
            while (i < sizeof(participants)){
                p = participants[i];
                if(!failures[p][PHASE]){
                    if($){
                        send this, eMessage, (phase = PHASE, from=leader, dst=p, payload = true);
                        receiveMessageBlocking(p, STARTVIEW);
                    }
                }
                i = i + 1;
            }

            // Update
            i = 0;
            while (i < numParticipants) {
                p = participants[i];

                if(sizeof(messages[p][PHASE][STARTVIEW]) == 1){
                    if(p != leader){
                        insertLogEntry(p, PHASE, command);
                    }
                }else{
                    failures[p][PHASE] = true;
                    insertLogEntry(p, PHASE, null);
                }
                i=i+1;
            }

            if(!failures[leader][PHASE]){
                print(format("Leader finish succesfully phase {0}, failures {1}", PHASE, failures));
            }
            

            PHASE = PHASE+1;
            Init(PHASE);

        }

        on eClientRequest do (m : ClientRequest) 
        {
            goto STARTVIEWCHANGE;
        }

    }


    fun Init(phase: Phase)
    {
        var i: int; 
        var p: machine;
        
        i = 0;
       
        logs = default(map[machine,Log]);
        failures = default(map[machine,map[Phase, bool]]);

        messages = default(Messages);
        
        while (i < numParticipants) {
            p = participants[i];
            
            logs[p] = default(Log);

            failures[p] = default(map[Phase, bool]);
            failures[p][PHASE] = false;

            messages[p] = default(Mbox);
            messages[p][PHASE] = default(map[Round, set[Message]]);

            messages[p][PHASE][STARTVIEWCHANGE] = default(set[Message]);
            messages[p][PHASE][DOVIEWCHANGE] = default(set[Message]);
            messages[p][PHASE][STARTVIEW] = default(set[Message]);

            i = i+1;
        }

    }

    fun insertLogEntry(p: machine, phase: Phase, e: any)
    {
        announce eMonitor_NewLogEntry, (phase=phase, logentry=e);
        logs[p][phase] = e;
    }

    fun receiveMessageBlocking(pdest: machine, r : Round)
    {
        receive {
            case eMessage: (m: Message) { 
                messages[pdest][PHASE][r] += (m); 
            }
        }
    }

}
