#include "roundAtoB_havoc_types.h"
#include "roundAtoB_havoc_decl.h"
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
    list* mbox=NULL;

    round = A;
    ballot = 0;
    m = (msg *) malloc(sizeof(msg));
    if (m==NULL) return 0;
    m->round = A;
    m->ballot = ballot;
    mbox = NULL;
    send(all, m);

    while(1)
    {

        mbox=havoc(ballot,round);

        if (round == A && count(mbox, ballot, round, n) > 2*n/3) {
            computation(mbox);
            dispose(mbox, ballot, round);
            round = B;
            m = (msg *) malloc(sizeof(msg));
            if (m==NULL) return 0;
            m->round = B;
            m->ballot = ballot;
            send(all, m);
            continue; 

        }

        if (round == B && count(mbox, ballot, round, n) > 2*n/3){
            computation(mbox);
            dispose(mbox, ballot, round);
            round = A;
            ballot++;
            m = (msg *) malloc(sizeof(msg));
            if (m==NULL) return 0;
            m->round = A;
            m->ballot = ballot;
            send(all, m);
            continue; 
        }       
        

    }

    return 0;
}
