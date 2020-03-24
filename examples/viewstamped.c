#include "viewstamped_types.h"
#include "viewstamped_decl.h"
int func(int p, int n, int f)
{
    int all=1000;

    int view = 0;
    int round;
    
    msg* m;
    msg* recv_msg;

    list* mbox=NULL;


    while(1){

        mbox = havoc();

        if(primary_timeout()){
            view = view+1;
            round = STARTVIEWCHANGE;

            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STARTVIEWCHANGE;
            m->view = view;
            m->replica = p;
            send(all,m);
        }

        if(round == STARTVIEWCHANGE && count_messages(mbox, view, STARTVIEWCHANGE) > f){
            round = DOVIEWCHANGE;

            msg* m = (msg *) malloc(sizeof(msg));
            m->round = DOVIEWCHANGE;
            m->view = view;
            m->log = local_log();
            send(view % n, m);

            continue;
        }

        if(round == DOVIEWCHANGE && is_primary(view,p,n) && count_messages(mbox, view, DOVIEWCHANGE) > f){

            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STARTVIEW;
            m->view = view;
            m->log = local_log();
            send(all, m);

            continue;
        }

        if(round == DOVIEWCHANGE && count_messages(mbox, view, STARTVIEW) > 0){
            round = STARTVIEW;
            computes_new_log();
            continue;
        }


        

    }

}
