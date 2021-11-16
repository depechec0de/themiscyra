type Messages = map[machine, Mbox];

machine TwoPhaseSync
{
    var numParticipants : int;
    var PHASE : Phase;
    var leader : machine;
    var participants : seq[machine];

    var messages : Messages;

    var decision : map[machine,map[Phase, Vote]];

    var i: int; 
    var p: machine;

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
            goto Alpha;
        }
    }

    state Alpha
    {
        defer eClientRequest;

        entry 
        {
            // ###### SEND ######
            var newcommand : Command;
            // Broadcast from leader to all
            i = 0;
            while (i < numParticipants) 
            {
                send this, eventALPHA, (phase = PHASE, from=leader, payload=newcommand);
                p = participants[i];
                receiveMessageBlocking(p, ALPHA);
                i = i + 1;
            }

            // #### UPDATE ######
            i = 1; // skip the leader
            while (i < numParticipants) 
            {
                p = participants[i];
                decision[p][PHASE] = ABORT;
                if($)
                {
                    decision[p][PHASE] = COMMIT; 
                }
                i = i + 1;
            }

            goto Beta;
        }

    }

    state Beta
    {
        defer eClientRequest;

        entry 
        {
            // ###### SEND ######
            i = 1;
            while (i < numParticipants) 
            {
                p = participants[i];
                send this, eventBETA, (phase = PHASE, from=p, payload = decision[p][PHASE]);
                receiveMessageBlocking(leader, BETA);

                i = i + 1;
            }

            // #### UPDATE ######            
            // Primary decides using votes
            decision[leader][PHASE] = commit_or_abort(messages[leader][PHASE][BETA], numParticipants-1);

            goto Gamma;
        }

    }

    state Gamma
    {
        defer eClientRequest;

        entry 
        {
            // ###### SEND ######
            var finaldecision : Vote;
            
            i = 0;
            while (i < numParticipants) 
            {
                p = participants[i];
                send this, eventGAMMA, (phase = PHASE, from=leader, payload = decision[leader][PHASE]);

                
                receiveMessageBlocking(p, GAMMA);

                i = i + 1;
            }

            // #### UPDATE ######
            // Backups record decision
            finaldecision = decision[leader][PHASE];

            i = 1; // skip the leader
            while (i < numParticipants) 
            {
                p = participants[i];
                decision[p][PHASE] = finaldecision;
                i = i + 1;
            }

            goto Delta;
        }
    }

    state Delta
    {
        entry 
        {
            // ###### SEND ######
            i = 1; // skip leader
            while (i < numParticipants) 
            {
                p = participants[i];
                send this, eventDELTA, (phase = PHASE, from=p, payload = true);
                receiveMessageBlocking(leader, DELTA);

                i = i + 1;
            }

            // #### UPDATE ######
            PHASE = PHASE+1;
            Init(PHASE);

        }

        on eClientRequest do (m : ClientRequest) 
        {
            goto Alpha;
        }

    }


    fun Init(phase: Phase)
    {
        var i: int; 
        var p: machine;
        
        i = 0;
       
        decision = default(map[machine,map[Phase, Vote]]);
        messages = default(Messages);
        
        while (i < numParticipants) {
            p = participants[i];
            decision[p] = default(map[Phase, Vote]);
            
            messages[p] = default(Mbox);
            messages[p][PHASE] = default(map[Round, set[Message]]);

            messages[p][PHASE][ALPHA] = default(set[Message]);
            messages[p][PHASE][BETA] = default(set[Message]);
            messages[p][PHASE][GAMMA] = default(set[Message]);
            messages[p][PHASE][DELTA] = default(set[Message]);

            i = i+1;
        }
    }

    fun receiveMessageBlocking(pdest: machine, r : Round)
    {
        if(r == ALPHA){
            receive {
                case eventALPHA: (m: Message) { 
                    messages[pdest][PHASE][r] += (m); 
                }
            }
        }

        if(r == BETA){
            receive {
                case eventBETA: (m: Message) { 
                    messages[pdest][PHASE][r] += (m); 
                }
            }
        }

        if(r == GAMMA){
            receive {
                case eventGAMMA: (m: Message) { 
                    messages[pdest][PHASE][r] += (m); 
                }
            }
        }

        if(r == DELTA){
            receive {
                case eventDELTA: (m: Message) { 
                    messages[pdest][PHASE][r] += (m); 
                }
            }
        }
        
    }
}
