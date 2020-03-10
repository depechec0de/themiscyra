#include "modsmartsync_types.h"
#include "modsmartsync_decl.h"

int all=1000;

int func(int p, int n)
{
    int round;
    int nreg;
    int creg;
    int leader;

    int timeout;
    
    msg* m;
    msg* recv_msg;

    list* stop_mbox=NULL;
    list* stopdata_mbox=NULL;

    list* decided_log=NULL;
    list* valid_timedout_msgs=NULL;

    creg = 0;
    nreg = 0;

    while(1){

        stop_mbox = havoc(creg);
        stopdata_mbox = havoc(creg);
        
        if(timeout){
            if(nreg == creg){
                nreg = creg+1;
                round = STOP;

                cancelTimers();
                msg* m = (msg *) malloc(sizeof(msg));
                m->round = STOP;
                m->reg = nreg;
                m->timedout_msgs = timedout_messages();
                send(all,m);
            }
            continue; 
        }

        if(count_change_regency(stop_mbox, creg+1)>n/3){
            valid_timedout_msgs = valid_timedout_messages(stop_mbox);
            if(nreg == creg){
                nreg = creg+1;
                round = STOP;

                cancelTimers();
                msg* m = (msg *) malloc(sizeof(msg));
                m->round = STOP;
                m->reg = nreg;
                m->timedout_msgs = valid_timedout_msgs;
                send(all,m);
            }
            add_messages_to_order(valid_timedout_msgs);

            continue;
        }

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

        if(round == STOPDATA && p == leader && size(stopdata_mbox) > 2*n/3){

            round = SYNC;

            msg* m = (msg *) malloc(sizeof(msg));
            m->round = SYNC;
            m->reg = creg;
            m->proofs = stopdata_mbox;
            send(leader,m);

            continue;
        }

    }

}
