#include "viewstamped_types.h"
#include "viewstamped_decl.h"
int func(int p, int n, int f)
{
    int all=1000;

    // sync variables
    int view = 0;
    int vround = STARTVIEW;
    int phase = 0;
    int nround = PREPARE;

    msg* m;
    msg* recv_msg;

    list* mbox=NULL;


    while(1){

        mbox = havoc();

        // NORMALOP

        if(vround == STARTVIEW && nround == PREPARE && p==primary(view,n)){

            m->view = view;
            m->vround = vround;
            m->phase = phase;
            m->nround = PREPARE;
            m->replica = p;
            send(all,m);
            
            nround = PREPAREOK;
            
            continue;
        }

        if(vround == STARTVIEW && nround == PREPARE && p!=primary(view,n) && count_messages(mbox, view, STARTVIEW, phase, PREPARE) == 1){

            nround = PREPAREOK;

            m->view = view;
            m->vround = vround;
            m->phase = phase;
            m->nround = PREPAREOK;
            m->replica = p;
            send(primary(view,n),m);
            
            nround = COMMIT;

            continue;
        }

        if(vround == STARTVIEW && nround == PREPAREOK && p==primary(view,n) && count_messages(mbox, view, STARTVIEW, phase, PREPAREOK) > f){

            nround = COMMIT;
            commit_to_log();

            reply_to_clients();

            m->view = view;
            m->vround = vround;
            m->phase = phase;
            m->nround = COMMIT;
            m->replica = p;
            send(all,m);
            

            phase = phase+1;
            nround = PREPARE;

            continue;
        }

        if(vround == STARTVIEW && nround == COMMIT && p!=primary(view,n) && count_messages(mbox, view, STARTVIEW, phase, COMMIT) == 1){

            commit_to_log();

            phase = phase+1;
            nround = PREPARE;
        }


        // VIEWCHANGE

        if(primary_timeout()){
            
            vround = STARTVIEWCHANGE;
            view = view+1;

            m->view = view;
            m->vround = STARTVIEWCHANGE;
            m->replica = p;
            send(all,m);
            continue;
        }

        if(vround == STARTVIEWCHANGE && p==primary(view,n) && count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f){
            vround = DOVIEWCHANGE;
            continue;
        }

        if(vround == STARTVIEWCHANGE && p!=primary(view,n) && count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f){
            vround = DOVIEWCHANGE;

            m->view = view;
            m->vround = DOVIEWCHANGE;
            m->replica = p;
            m->log = local_log();
            send(primary(view,n), m);

            vround = STARTVIEW;

            continue;
        }

        if(vround == DOVIEWCHANGE && p==primary(view,n) && count_messages(mbox, view, DOVIEWCHANGE, NULL, NULL) > f){

            vround = STARTVIEW;
            computes_new_log();

            m->view = view;
            m->vround = STARTVIEW;
            m->replica = p;
            m->log = local_log();
            send(all, m);

            nround = PREPARE;
            phase = phase+1;

            continue;
        }

        if(vround == STARTVIEW && p!=primary(view,n) && count_messages(mbox, view, STARTVIEW, NULL, NULL) == 1){
            
            computes_new_log();

            // Back to normalop
            nround = PREPARE;
            phase = phase+1;
            continue;
        }


        

    }

}
