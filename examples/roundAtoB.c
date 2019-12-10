#include "roundAtoB_types.h"
#include "roundAtoB_decl.h"
int func(int p, int n)
{
    int round;
    int ballot;
    int v=p;
    int t=p;
    int all=1000;
    int timeout;
    
    msg* m;
    msg* recv_msg;
    list* mboxA=NULL;
    list* mboxB=NULL;

    round = 0;
    ballot = 0;
    m = (msg *) malloc(sizeof(msg));
    if (m==NULL) return 0;
    m->round = 0;
    m->ballot = ballot;
    mboxA = NULL;
    send(all, m);

    while(1)
    {

        recv_msg = (msg *) malloc(sizeof(msg));
        
        if (recv_msg!=NULL){
            recv_msg->round = v%2;
            recv_msg->ballot = t;
            if (recv_msg->round == 0){
                if (round == 0) {
                    if (count(mboxA, ballot,n) > ((2 * n) / 3)){
                    round = 1;
                    m = (msg *) malloc(sizeof(msg));
                    if (m==NULL) return 0;
                    m->round = 1;
                    m->ballot = ballot;
                    send(all, m);
                }
                continue;
                }
            }
        }

        if (recv_msg!=NULL){
            recv_msg->round = v%2;
            recv_msg->ballot = t;
            if(recv_msg->round == 1)
            {
            if (round == 1) {
                if(count(mboxB, ballot,n) > ((2 * n) / 3))
                {
                round = 0;
                ballot++;
                m = (msg *) malloc(sizeof(msg));
                if (m==NULL) return 0;
                m->round = 0;
                m->ballot = ballot;
                send(all, m);
                }
            }
            }
            continue;
        }
        

    }

    return 0;
}
