type Messages = map[machine, Mbox];

machine PaxosSync
{
    var participants : set[machine];
    var quorum : int;
    var phase : Phase;
    var last : map[machine,Phase];
    var messages : Messages;
    var log : map[machine, Log];
    var fm : FailureModel;
    var roundCompleted : map[machine, map[Round, bool]];

    var i, j: int; 
    var p, from, dst: machine;

    start state Init{
        entry (config: (peers: set[machine], quorum: int, failurem: FailureModel)){
            participants = config.peers;
            quorum = config.quorum;
            fm = config.failurem;

            phase = 0;
            init_phase(phase);

            i = 0;
            while (i < sizeof(participants)){
                p = participants[i];
                last[p] = phase;
                log[p] = default(Log);
                i = i + 1;
            }

            phase = phase+1;
            init_phase(phase);

            goto WaitForConsensusRequest;
        }

    }

    state WaitForConsensusRequest {
        on ConsensusRequest do 
        {
            goto Prepare;
        }
    }

    state Prepare{
        defer ConsensusRequest;

        entry{
            var msg : MessageType;
            // SEND / RECEIVE
            i = 0;
            while (i < sizeof(participants)) {
                p = participants[i];

                if(primary(phase, participants) == p){
                    BroadCast(fm, participants, PrepareMessage, (phase=phase, from=primary(phase, participants), payload = null));
                }
            
                i=i+1;
            }

            // UPDATE
            i = 0;
            while (i < sizeof(participants)) {
                p = participants[i];

                if(primary(phase, participants) == p){
                    roundCompleted[p][PREPARE] = true;
                    //last[p] = msg.phase; // BUG, remove
                }
                
                if(primary(phase, participants) != p){
                    print(format("process {0} mbox {1}", p, messages[p][phase][PREPARE]));
                    if(sizeof(messages[p][phase][PREPARE]) > 0){
                        
                        roundCompleted[p][PREPARE] = true;
                        msg = messages[p][phase][PREPARE][0];
                        //last[p] = msg.phase; // BUG, remove
                    }

                }

                print(format("roundCompleted PREPARE {0} {1}", p, roundCompleted[p][PREPARE]));

                i=i+1;
            }
            
            // Primary decides using votes
            goto Ack;
        }
    }

    state Ack{
        defer ConsensusRequest;

        entry{
            var newCommand : Command;

            // SEND / RECEIVE
            i = 0;
            while (i < sizeof(participants)) {
                p = participants[i];
                
                if(primary(phase, participants) != p && roundCompleted[p][PREPARE]){
                    Send(fm, primary(phase, participants), AckMessage, (phase=phase, from=p, payload = (last=last[p], log=log[p])));
                }

                i=i+1;
            }

            // UPDATE
            i = 0;
            while (i < sizeof(participants)) {
                p = participants[i];

                if(primary(phase, participants) == p && roundCompleted[p][PREPARE]){

                    if(sizeof(messages[p][phase][ACK]) >= quorum){
                        roundCompleted[p][ACK] = true;
                        log[p] = select_log_from_received_messages(messages[p][phase][ACK]);
                        newCommand = new_command();
                        log[p] += (sizeof(log[p]), newCommand);
                    }

                }

                if(primary(phase, participants) != p && roundCompleted[p][PREPARE]){
                    roundCompleted[p][ACK] = true;
                }

                print(format("roundCompleted ACK {0} {1}", p, roundCompleted[p][ACK]));
                
                i=i+1;
            }

            goto Propose;
            
        }
    }

    state Propose{
        defer ConsensusRequest;

        entry{
            var msg : PromiseType;

            // SEND / RECEIVE
            i = 0;
            while (i < sizeof(participants)) {
                p = participants[i];

                if(primary(phase, participants) == p && roundCompleted[p][ACK]){
                    BroadCast(fm, participants, ProposeMessage, (phase=phase, from=p, payload = log[p]));
                }

                i=i+1;
            }

            // UPDATE
            i = 0;
            while (i < sizeof(participants)) {
                p = participants[i];

                if(primary(phase, participants) != p && roundCompleted[p][ACK]){

                    if(sizeof(messages[p][phase][PROPOSE]) > 0){
                        msg = messages[p][phase][PROPOSE][0] as ProposeType;
                        log[p] = msg.payload;
                        last[p] = phase; // BUG, add

                        roundCompleted[p][PROPOSE] = true;
                        
                    }

                }

                if(primary(phase, participants) == p && roundCompleted[p][ACK]){
                    roundCompleted[p][PROPOSE] = true;
                    last[p] = phase; // BUG, add
                }

                print(format("roundCompleted PROPOSE {0} {1}", p, roundCompleted[p][PROPOSE]));
                
                i=i+1;
            }

            goto Promise;
            
        }
    }

    state Promise{
        defer ConsensusRequest;

        entry{

            // SEND / RECEIVE
            i = 0;
            while (i < sizeof(participants)) {
                p = participants[i];

                if(roundCompleted[p][PROPOSE]){
                    BroadCast(fm, participants, PromiseMessage, (phase=phase, from=p, payload = log[p]));
                }

                i=i+1;
            }

            // UPDATE
            i = 0;
            while (i < sizeof(participants)) {
                p = participants[i];

                if(roundCompleted[p][PROPOSE]){

                    if(sizeof(messages[p][phase][PROMISE]) >= quorum){
                        roundCompleted[p][PROMISE] = true;
                        announce eMonitor_NewLog, (id=p, newlog=log[p]);
                    }

                }

                print(format("roundCompleted PROMISE {0} {1}", p, roundCompleted[p][PROMISE]));
                
                i=i+1;
            }

            phase = phase+1;
            if(phase > 9){
                raise halt;
            }
            init_phase(phase);

            i = 0;
            while (i < sizeof(participants)) {
                p = participants[i];
                if(!roundCompleted[p][PROMISE]){
                    goto Prepare;
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
        roundCompleted = default(map[machine, map[Round, bool]]);
        
        while (i < sizeof(participants)) {
            p = participants[i];

            roundCompleted[p] = default(map[Round, bool]);

            roundCompleted[p][PREPARE] = false;
            roundCompleted[p][ACK] = false;
            roundCompleted[p][PROPOSE] = false;
            roundCompleted[p][PROMISE] = false;
            
            messages[p] = default(Mbox);
            messages[p][phase] = default(map[Round, set[MessageType]]);

            messages[p][phase][PREPARE] = default(set[PrepareType]);
            messages[p][phase][ACK] = default(set[AckType]);
            messages[p][phase][PROPOSE] = default(set[ProposeType]);
            messages[p][phase][PROMISE] = default(set[PromiseType]);

            i = i+1;
        }
    }

    fun receiveMessageBlocking(pdest: machine, r : Round)
    {
        receive {
            case eMessage: (m: MessageType) { 
                messages[pdest][phase][r] += (m); 
                print(format("process {0} received message {1}", pdest, m));
            }
        }
    }

    fun BroadCast(fm : FailureModel, ms: set[machine], ev: event, payload: MessageType){
        var receiver : machine;
        var i : int;

        i=0;
        while (i < sizeof(participants)){
            receiver = participants[i];
            Send(fm, receiver, ev, payload);
                        
            i = i + 1;
        }
    }

    fun Send(fm : FailureModel, target: machine, message: event, payload: MessageType){
        var round : Round;

        if(fm == NoFailure || $){
            send this, eMessage, payload;

            if(message == PrepareMessage){
                round = PREPARE;
            }else if(message == AckMessage){
                round = ACK;
            }else if(message == ProposeMessage){
                round = PROPOSE;
            }else{
                round = PROMISE;
            }

            receiveMessageBlocking(target, round);
        }else{
            print(format("Message lost! {0}", fm));
        }
    }
}
