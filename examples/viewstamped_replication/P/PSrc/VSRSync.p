type Messages = map[machine, Mbox];

machine ViewStampedReplicationSync
{
    var numParticipants : int;
    var PHASE : Phase;
    var leader : machine;
    var participants : seq[machine];

    var messages : Messages;

    var log : map[machine,map[Phase, Command]];

    start state Init 
    {
        entry (p: seq[machine]){

            participants = p;
            numParticipants = sizeof(participants);
            
            PHASE = 0; 
            leader = participants[0];
            Init(PHASE);

            announce eMonitor_Initialize, participants;
        }

        on eClientRequest do (m : ClientRequest) 
        {
            goto STARTVIEWCHANGE;
        }
    }

    state STARTVIEWCHANGE
    {
        entry 
        {
            // ###### SEND ######
            var newcommand : Command;
            // Broadcast from all to all
            var i, j: int; 
            var p: machine;
            i = 0;
            while (i < numParticipants) 
            {
                j = 0;
                while (j < numParticipants) 
                {
                    send this, eMessage, (phase = PHASE, from=participants[i], dst=participants[j], payload=newcommand);
                    j = j + 1;
                }
                i = i + 1;
            }

            // #### UPDATE ######
            i = 0;
            while (i < numParticipants*numParticipants) {
                
                receive {
                    case eMessage: (m: Message) { 
                        messages[m.dst][PHASE][STARTVIEWCHANGE] += (sizeof(messages[m.dst][PHASE][STARTVIEWCHANGE]), m); 
                    }
                }
                
                i = i + 1;
            }

            goto DOVIEWCHANGE;
        }

    }

    state DOVIEWCHANGE
    {
        entry 
        {
            // ###### SEND ######
            var newcommand : Command;
            var i: int; 
            i = 0;
            while (i < numParticipants) 
            {
                send this, eMessage, (phase = PHASE, from=participants[i], dst=leader, payload = newcommand);
                i = i+1;
            }

            // #### UPDATE ######
            i = 0;
            while (i < numParticipants) {
                
                receive {
                    case eMessage: (m: Message) { 
                        messages[m.dst][PHASE][DOVIEWCHANGE] += (sizeof(messages[m.dst][PHASE][DOVIEWCHANGE]), m); 
                    }
                }
                i = i + 1;
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
            // ###### SEND ######
            i = 0;
            while (i < numParticipants) 
            {
                send this, eMessage, (phase = PHASE, from=leader, dst=participants[i], payload = true);
                i = i+1;
            }

            // #### UPDATE ######
            i = 0;
            while (i < numParticipants) {
                
                receive {
                    case eMessage: (m: Message) { 
                        messages[m.dst][PHASE][STARTVIEW] += (sizeof(messages[m.dst][PHASE][STARTVIEW]), m); 
                    }
                }
                i = i + 1;
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
       
        log = default(map[machine,map[Phase, Command]]);
        messages = default(Messages);
        
        while (i < numParticipants) {
            p = participants[i];
            log[p] = default(map[Phase, Command]);
            
            messages[p] = default(Mbox);
            messages[p][PHASE] = default(map[Round, seq[Message]]);

            messages[p][PHASE][STARTVIEWCHANGE] = default(seq[Message]);
            messages[p][PHASE][DOVIEWCHANGE] = default(seq[Message]);
            messages[p][PHASE][STARTVIEW] = default(seq[Message]);

            i = i+1;
        }
    }


}
