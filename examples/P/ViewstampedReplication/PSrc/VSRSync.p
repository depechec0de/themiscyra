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
            var i : int;
            var p : machine;

            // ###### SEND ######
            msg_sent = SendStartViewChange(PHASE);

            // #### UPDATE ######
            ReceiveMessages(PHASE, STARTVIEWCHANGE, msg_sent);

            i = 0;
            while (i < numParticipants) {
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
            var p : machine;
            var i : int;

            // ###### SEND ######
            msg_sent = SendDoViewChange(PHASE);

            // #### UPDATE ######
            ReceiveMessages(PHASE, DOVIEWCHANGE, msg_sent);

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
            var i: int;
            var p: machine;

            // ###### SEND ######
            msg_sent = SendStartView(PHASE);

            // #### UPDATE ######
            ReceiveMessages(PHASE, STARTVIEW, msg_sent);

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

    fun SendStartViewChange(currentPhase: Phase) : int
    {
        var newdata : data;
        // Broadcast from all to all
        var i, j: int; 
        var msg_sent: int;
        var p: machine;

        msg_sent = 0;
        i = 0;
        while (i < numParticipants) 
        {
            p = participants[i];
            if(!failures[p][currentPhase]){
                j = 0;
                while (j < numParticipants) 
                {
                    if($){
                        send this, eMessage, (phase = currentPhase, from=p, dst=participants[j], payload=newdata);
                        msg_sent = msg_sent+1;
                    }
                    j = j + 1;
                }
            }
            i = i + 1;
        }

        return msg_sent;
    }

    fun SendDoViewChange(currentPhase: Phase) : int
    {
        var newdata : data;
        var i: int; 
        var msg_sent: int;
        var p: machine;

        msg_sent = 0;
        i = 0;
        
        while (i < numParticipants) 
        {
            p = participants[i];

            if(!failures[p][currentPhase]){
                if($){
                    send this, eMessage, (phase = currentPhase, from=p, dst=leader, payload = newdata);
                    msg_sent = msg_sent+1;
                }
            }
            i = i+1;
        }

        return msg_sent;
    }

    fun SendStartView(currentPhase: Phase) : int
    {
        var i: int; 
        var msg_sent: int;
        var p: machine;

        i = 0;
        msg_sent = 0;
        while (i < numParticipants) 
        {
            p = participants[i];
            if(!failures[p][currentPhase]){
                if($){
                    send this, eMessage, (phase = currentPhase, from=leader, dst=p, payload = true);
                    msg_sent=msg_sent+1;
                }
            }
            i = i+1;
        }

        return msg_sent;
    }

    fun ReceiveMessages(phase: Phase, round: Round, msg_to_receive: int)
    {
        var i : int;
        var p : machine;
        i = 0;
        while (i < msg_to_receive) {
            
            receive {
                case eMessage: (m: Message) { 
                    messages[m.dst][phase][round] += (m); 
                }
            }
            
            i = i + 1;
        }      
    }

    fun insertLogEntry(p: machine, phase: Phase, e: any)
    {
        logs[p][phase] = e;
    }

}
