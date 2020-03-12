#include "modsmartsync_types.h"
#include "modsmartsync_decl.h"

int all=1000;

int creg = 0;
int nreg = 0;

int func(int p, int n)
{
    int round;
    int leader;

    int timeout;
    
    msg* m;
    msg* recv_msg;

    list* stop_mbox=NULL;
    list* stopdata_mbox=NULL;
    list* sync_mbox=NULL;

    list* decided_log=NULL;
    list* valid_timedout_msgs=NULL;

    while(1){

        stop_mbox = havoc(creg);
        stopdata_mbox = havoc(creg);
        sync_mbox = havoc(creg);
        
        // TIMEOUT DETECTED
        // PHASE := nreg
        // ROUND := round
        if(timeout && nreg == creg){
            nreg = creg+1;
            round = STOP;

            cancelTimers();
            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOP;
            m->reg = nreg;
            m->timedout_msgs = timedout_messages();
            send(all,m);
            
            continue; 
        }

        if(count_change_regency(stop_mbox, creg+1)>n/3 && nreg == creg){
            
            nreg = creg+1;
            round = STOP;

            valid_timedout_msgs = valid_timedout_messages(stop_mbox);
            add_messages_to_order(valid_timedout_msgs);

            cancelTimers();
            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOP;
            m->reg = nreg;
            m->timedout_msgs = valid_timedout_msgs;
            send(all,m);

            continue;
        }

        // count_change_regency() check that I received 2n/3 stop messages for the next regency creg+1
        if(round == STOP && count_change_regency(stop_mbox, creg+1)>2*n/3 && nreg > creg){
            creg = nreg;
            round = STOPDATA;

            activateTimers();
            leader = creg % n;

            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOPDATA;
            m->reg = nreg;
            m->decided_log = decided_log;
            send(leader,m);

            continue;
        }

        // LEADER
        if(round == STOPDATA && p == leader && size(stopdata_mbox) > 2*n/3){

            round = SYNC;

            msg* m = (msg *) malloc(sizeof(msg));
            m->round = SYNC;
            m->reg = creg;
            m->proofs = stopdata_mbox;
            send(leader,m);

            continue;
        }

        // FOLLOWER
        if(round == STOPDATA && size(sync_mbox) == 1 && nreg == creg && from_leader(sync_mbox)){
            if(check_proofs()){
                back_to_normalop();
                round = STOP;
            }
        }


    }

}
