#include "viewstamped_types.h"
#include "viewstamped_decl.h"
int func(int p, int n, int f)
{
    int all=1000;

    // sync variables
    int view = 0;
    int vround = STARTVIEW;
    int opnumber = 0;
    int nround = PREPARE;

    msg* m;
    msg* recv_msg;

    list* mbox=NULL;


    while(1){

        mbox = havoc();

        if(vround == STARTVIEW && nround == PREPARE && p==primary(view,n)){
            // NORMALOP
            m->view = view;
            m->vround = vround;
            m->opnumber = opnumber;
            m->nround = PREPARE;
            m->replica = p;
            send(all,m);
            
            nround = PREPAREOK;
            
            continue;
        }

        if(vround == STARTVIEW && nround == PREPARE && p!=primary(view,n) && count_messages(mbox, view, STARTVIEW, opnumber, PREPARE) == 1){
            // NORMALOP
            nround = PREPAREOK;

            m->view = view;
            m->vround = vround;
            m->opnumber = opnumber;
            m->nround = PREPAREOK;
            m->replica = p;
            send(primary(view,n),m);
            
            nround = COMMIT;

            continue;
        }

        if(vround == STARTVIEW && nround == PREPAREOK && p==primary(view,n) && count_messages(mbox, view, STARTVIEW, opnumber, PREPAREOK) > f){
            // NORMALOP
            nround = COMMIT;
            commit_to_log();

            reply_to_clients();

            m->view = view;
            m->vround = vround;
            m->opnumber = opnumber;
            m->nround = COMMIT;
            m->replica = p;
            send(all,m);
            

            opnumber = opnumber+1;
            nround = PREPARE;

            continue;
        }

        if(vround == STARTVIEW && nround == COMMIT && p!=primary(view,n) && count_messages(mbox, view, STARTVIEW, opnumber, COMMIT) == 1){
            // NORMALOP
            commit_to_log();

            opnumber = opnumber+1;
            nround = PREPARE;
        }

        if(primary_timeout()){
            // VIEWCHANGE
            vround = STARTVIEWCHANGE;
            
            m->view = view;
            m->vround = STARTVIEWCHANGE;
            m->replica = p;
            send(all,m);
            continue;
        }

        if(vround == STARTVIEWCHANGE && p==primary(view,n) && count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f){
            // VIEWCHANGE
            vround = DOVIEWCHANGE;
            continue;
        }

        if(vround == STARTVIEWCHANGE && p!=primary(view,n) && count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f){
            // VIEWCHANGE
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
            // VIEWCHANGE
            vround = STARTVIEW;
            computes_new_log();

            m->view = view;
            m->vround = STARTVIEW;
            m->replica = p;
            m->log = local_log();
            send(all, m);

            view = view+1;
            nround = PREPARE;

            continue;
        }

        if(vround == STARTVIEW && p!=primary(view,n) && count_messages(mbox, view, STARTVIEW, NULL, NULL) == 1){
            // VIEWCHANGE
            computes_new_log();
            view = view+1;

            // NORMALOP
            nround = PREPARE;
            continue;
        }


        

    }

}
