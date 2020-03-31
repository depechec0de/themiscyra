#include "viewstamped_types.h"
#include "viewstamped_decl.h"
int func(int p, int n, int f)
{
    int all=1000;

    // sync variables
    int view = 0;
    int vround = STARTVIEW;
    int phase = 0;
    int nround;
    if(p==primary(view,n)){
        nround = REQUEST;
    }else{
        nround = PREPARE;
    }
    

    msg* m;
    msg* recv_msg;

    list* mbox=NULL;


    while(1){

        msg* m = (msg *) malloc(sizeof(msg));
        if(m = recv() && m != NULL){
        
            if(local_timestamp() <= timestamp(m)){
            
                if(local_timestamp() < timestamp(m)){
                    discard(mbox);
                    view = m->view;
                    vround = m->vround;
                    phase = m->phase;
                    nround = m->nround;
                }

                add(m,mbox);

            }

        }

        // NORMALOP

        if(vround == STARTVIEW && nround == REQUEST && p==primary(view,n) && count_messages(mbox, STARTVIEW, phase, REQUEST) > 0){

            nround = PREPARE;

            for(list * msg = mbox_iterator(mbox, view, STARTVIEW, phase, REQUEST); msg != NULL; msg = msg->next){
                m->view = view;
                m->vround = vround;
                m->phase = phase;
                m->nround = PREPARE;
                m->replica = p;
                send(all,m);
            }

            nround = PREPAREOK;
            
            continue;
        }

        if(vround == STARTVIEW && nround == PREPARE && p!=primary(view,n) && count_messages(mbox, view, STARTVIEW, phase, PREPARE) > 0){

            nround = PREPAREOK;

            for(list * msg = mbox_iterator(mbox, view, STARTVIEW, phase, PREPARE); msg != NULL; msg = msg->next){
                m->view = view;
                m->vround = vround;
                m->phase = phase;
                m->nround = PREPAREOK;
                m->replica = p;
                send(primary(view,n),m);
            }

            nround = COMMIT;

            continue;
        }

        if(vround == STARTVIEW && nround == PREPAREOK && p==primary(view,n) && count_messages(mbox, view, phase, PREPAREOK) > f){

            nround = COMMIT;
            commit_to_log();

            for(list * msg = mbox_iterator(mbox, view, STARTVIEW, phase, PREPAREOK); msg != NULL; msg = msg->next){
                reply_to_client(msg);

                m->view = view;
                m->vround = vround;
                m->phase = phase;
                m->nround = COMMIT;
                m->replica = p;
                send(all,m);
            }

            phase = phase+1;
            nround = REQUEST;

            continue;
        }

        if(vround == STARTVIEW && nround == COMMIT && p!=primary(view,n) && count_messages(mbox, view, STARTVIEW, phase, COMMIT) > 0){

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
            m->phase = phase;
            m->nround = nround;
            m->replica = p;
            send(all,m);
            continue;
        }

        if(vround == STARTVIEWCHANGE && p==primary(view,n) && count_messages(mbox, view, STARTVIEWCHANGE, phase, nround) > f){
            vround = DOVIEWCHANGE;
            continue;
        }

        if(vround == STARTVIEWCHANGE && p!=primary(view,n) && count_messages(mbox, view, STARTVIEWCHANGE, phase, nround) > f){
            vround = DOVIEWCHANGE;

            m->view = view;
            m->vround = DOVIEWCHANGE;
            m->phase = phase;
            m->nround = nround;
            m->replica = p;
            m->log = local_log();
            send(primary(view,n), m);

            vround = STARTVIEW;

            continue;
        }

        if(vround == DOVIEWCHANGE && p==primary(view,n) && count_messages(mbox, view, DOVIEWCHANGE, phase, nround) > f){

            vround = STARTVIEW;
            computes_new_log();

            m->view = view;
            m->vround = STARTVIEW;
            m->phase = phase;
            m->nround = nround;
            m->replica = p;
            m->log = local_log();
            send(all, m);

            nround = REQUEST;
            phase = phase+1;

            continue;
        }

        if(vround == STARTVIEW && p!=primary(view,n) && count_messages(mbox, view, STARTVIEW, phase, nround) > 0){
            
            computes_new_log();

            // Back to normalop
            nround = REQUEST;
            phase = phase+1;
            continue;
        }


        

    }

}
