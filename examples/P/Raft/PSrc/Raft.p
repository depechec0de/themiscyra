
type Phase = int;
type Mbox = map[Phase, map[Round, set[MessageType]]];
type Log = seq[any];
type LogConfigEntry = set[machine];

type InitMessageType = (log: Log, servers: set[machine]);
event InitMessage : InitMessageType; 

type MessageType = (phase: Phase, from: machine, payload: any);
event eMessage : MessageType;

type ProposeMessageType = (phase: Phase, from: machine, payload: Log);
event ProposeMessage: ProposeMessageType;

type AckMessageType = (phase: Phase, from: machine, payload: Log);
event AckMessage: AckMessageType;

type CommitMessageType = (phase: Phase, from: machine, payload: Log);
event CommitMessage: CommitMessageType;

enum Round { PROPOSE, ACK, COMMIT }

machine Server {   
    var servers : set[machine];
    var phase : int;
    var mbox : Mbox;
    var log : Log;
    var timer : Timer;
    var ack : bool;
    var commit : bool;

    start state Init {
        defer ProposeMessage, AckMessage, CommitMessage;
        
        entry {
            init_phase(0);
            
            timer = CreateTimer(this);

            receive {
                case InitMessage: (payload: InitMessageType) { 
                    servers = payload.servers;
                    log = payload.log;
                }
            }

            goto Propose;
        }
    }

    state Propose {

        defer AckMessage, CommitMessage;

        entry {
            var newserver : machine;

            if(this == primary(phase, servers)){
                newserver = new Server();
                servers += (newserver);
                log += (sizeof(log), servers);

                send newserver, InitMessage, (log=log, servers=servers);
    
                print(format("PRIMARY {0} PROPOSE NEW SERVER {1} ", this, newserver));

                UnReliableBroadCast(servers, ProposeMessage, (phase=phase, from=this, payload=log));
                //ReliableBroadCast(servers, ProposeMessage, (phase=phase, from=this, payload=log));
                ack = true;

                goto Ack;
            }

            StartTimer(timer);
        }

        on ProposeMessage do (m: ProposeMessageType) {
            CancelTimer(timer);

            if(m.phase == phase && sequenceIsPrefix(log, m.payload)){
                log = m.payload;
                ack = true;
            }else{
                ack = false;
            }
            goto Ack;
        }

        on eTimeOut do {
            goto Ack;
        }
    }

    state Ack {

        defer ProposeMessage, CommitMessage;

        entry {
            if(ack){
                if($){
                //if(true){
                    send primary(phase, servers), AckMessage, (phase=phase, from=this, payload=log);
                }
            }

            if(this != primary(phase, servers)){
                goto Commit;
            }
            StartTimer(timer);
        }

        on AckMessage do (m: AckMessageType) {
            if(m.phase == phase && this == primary(phase, servers)){
                mbox[m.phase][ACK] += (m);

                print(format("SERVER {0} RECEIVED {1} ACK MESSAGES, EXPECTING: {2} ", this, sizeof(mbox[m.phase][ACK]), sizeof(servers)/2 + 1));

                if(sizeof(mbox[m.phase][ACK]) >= sizeof(servers)/2 + 1){
                    CancelTimer(timer);

                    commit = true;
                    goto Commit;
                }
            }
        }

        on eTimeOut do {
            goto Commit;
        }

    }

    state Commit {

        defer ProposeMessage, AckMessage;

        entry {
            if(this == primary(phase, servers) && commit){
                UnReliableBroadCast(servers, CommitMessage, (phase=phase, from=this, payload=log));
                //ReliableBroadCast(servers, CommitMessage, (phase=phase, from=this, payload=log));
                init_phase(phase+1);
                goto Propose;
            }

            StartTimer(timer);
        }

        on CommitMessage do (m: CommitMessageType) {
            if(m.phase == phase){
                CancelTimer(timer);

                log = m.payload;

                announce eMonitor_NewLog, (id=this, newlog=log);
                
                init_phase(phase+1);
                goto Propose;
            }
        }

        on eTimeOut do {
            init_phase(phase+1);
            goto Propose;
        }
    }

    fun init_phase(p: Phase){
        phase = p;
        ack = false;
        commit = false;

        mbox[p] = default(map[Round, set[MessageType]]);

        mbox[p][PROPOSE] = default(set[MessageType]);
        mbox[p][ACK] = default(set[MessageType]);
        mbox[p][COMMIT] = default(set[MessageType]);
    }

}