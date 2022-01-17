type Messages = map[machine, Mbox];

machine RaftSeq
{
    var messages : Messages;

    var globalservers : set[machine];
    var configs : map[machine, set[machine]];
    var PHASE : Phase;
    var logs : map[machine, Log];
    var acks : map[machine, bool];
    var commits : map[machine, bool];
    var newservers : map[machine, SeqServer];

    var i, j: int; 
    var p, from, dst: machine;
    var msg : MessageType;

    start state Init{
        entry (s: set[machine]){

            globalservers = s;

            i = 0;
            while (i < sizeof(s)){
                p = globalservers[i];
                configs[p] = s;
                logs[p] = default(Log);
                logs[p] += (sizeof(logs[p]), s);
                i = i + 1;
            }
            
            PHASE = 0;
            init_phase();
            
            goto Propose;
        }
    }

    state Propose{

        entry{
            
            // SEND / RECEIVE
            i = 0;
            while (i < sizeof(globalservers)) {
                p = globalservers[i];

                if(p == primary(PHASE, configs[p])){
                    // Only create one server per primary
                    if(!(p in newservers)){
                        newservers[p] = new SeqServer();
                        print(format("{0} CREATES SERVER {1}", p, newservers[p]));
                        init_server(newservers[p]);
                        configs[p] += (newservers[p]);
                        globalservers += (newservers[p]);
                        configs[newservers[p]] = configs[p];

                        logs[p] += (sizeof(logs[p]), configs[p]);

                        logs[newservers[p]] = default(Log);
                        logs[newservers[p]] += (sizeof(logs[newservers[p]]), configs[newservers[p]]);
                    }                 

                    BroadCast(configs[p], ProposeMessage, (phase=PHASE, from=p, payload=logs[p]));

                    acks[p] = true;

                }
            
                i=i+1;
            }

            // UPDATE
            i = 0;
            while (i < sizeof(globalservers)) {
                p = globalservers[i];

                if(sizeof(messages[p][PHASE][PROPOSE]) > 0){
                    msg = messages[p][PHASE][PROPOSE][0];

                    //if(sequenceIsPrefix(logs[p], msg.payload as Log)){
                        acks[p] = true;
                    //}
                }
                
                i=i+1;
            }

            goto Ack;
        }
    }

    state Ack{

        entry{
            // SEND / RECEIVE
            i = 0;
            while (i < sizeof(globalservers)) {
                p = globalservers[i];

                if(acks[p]){
                    Send(primary(PHASE, configs[p]), AckMessage, (phase=PHASE, from=p, payload=logs[p]));
                }
            
                i=i+1;
            }

            // UPDATE
            i = 0;
            while (i < sizeof(globalservers)) {
                p = globalservers[i];

                if(p == primary(PHASE, configs[p])){
                    if(sizeof(messages[p][PHASE][ACK]) >= sizeof(configs[p])/2 + 1){
                        print(format("{0} HAS ACK QUORUM {1}", p, messages[p][PHASE][ACK]));
                        commits[p] = true;
                    }
                }
                
                i=i+1;
            }

            goto Commit;
        }
    }

    state Commit{

        entry{
            var msg: MessageType;
            var newconfig: LogConfigEntry;

            // SEND / RECEIVE
            i = 0;
            while (i < sizeof(globalservers)) {
                p = globalservers[i];

                if(p == primary(PHASE, configs[p]) && commits[p]){
                    BroadCast(configs[p], CommitMessage, (phase=PHASE, from=p, payload=logs[p]));
                }
            
                i=i+1;
            }

            // UPDATE
            i = 0;
            while (i < sizeof(globalservers)) {
                p = globalservers[i];

                if(sizeof(messages[p][PHASE][COMMIT]) > 0){
                    commits[p] = true;
                    msg = messages[p][PHASE][COMMIT][0];
                    logs[p] = msg.payload as Log;

                    newconfig = logs[p][sizeof(logs[p])-1] as LogConfigEntry;
                    configs[p] = newconfig;

                    print(format("{0} APPLY NEW CONFIG {1} FROM LOG {2}", p, newconfig, logs[p]));

                    announce eMonitor_NewLog, (id=p, newlog=logs[p]);
                }
                
                i=i+1;
            }

            PHASE = PHASE+1;
            init_phase();
            goto Propose;
        }
    }

    fun init_phase()
    {
        var i: int; 
        var s: machine;
        
        print(format("STARTING PHASE {0}", PHASE));
        i = 0;

        messages = default(Messages);

        while (i < sizeof(globalservers)) {
            s = globalservers[i];
            init_server(s);

            i = i+1;
        }
    }

    fun init_server(p: machine){
        acks[p] = false;
        commits[p] = false;
        
        messages[p] = default(Mbox);
        messages[p][PHASE] = default(map[Round, set[MessageType]]);

        messages[p][PHASE][PROPOSE] = default(set[ProposeMessageType]);
        messages[p][PHASE][ACK] = default(set[AckMessageType]);
        messages[p][PHASE][COMMIT] = default(set[CommitMessageType]);
    }

    fun BroadCast(ms: set[machine], ev: event, payload: MessageType){
        var receiver : machine;
        var i : int;

        i=0;
        while (i < sizeof(ms)){
            receiver = ms[i];
            Send(receiver, ev, payload);
                        
            i = i + 1;
        }
    }

    fun Send(target: machine, message: event, msg: MessageType){
        var round : Round;

        if(message == ProposeMessage){
            round = PROPOSE;
        }else if(message == AckMessage){
            round = ACK;
        }else{
            round = COMMIT;
        }

        if($){
            send this, eMessage, msg;

            if(msg.from in configs[target]){
                messages[target][PHASE][round] += (msg);
                print(format("MESSAGE {0} RECEIVED TO {1}", msg, target));
            }else{
                print(format("MESSAGE {0} FROM UNKNOWN SENDER TO {1}", msg, target));
            }
        }else{
            print(format("MESSAGE {0} LOST TO {1}", msg, target));
        }
    }

    
}
