#include "viewstamped_types.h"
#include "viewstamped_decl.h"
int func(int p, int n, int f)
{
    int all=1000;

    // sync variables
    int phase = 0;
    int round = REQUEST;

    int view = 0;
    
    msg* m;
    msg* recv_msg;

    list* mbox=NULL;


    while(1){

        msg* m = (msg *) malloc(sizeof(msg));
        m = recv();
        add(m,mbox);
   
        // NORMALOP

        if(round == REQUEST && p==primary(view,n) && count_messages(mbox, view, REQUEST) > 0){

            round = PREPARE;

            for(list * msg = mbox_iterator(mbox, view, REQUEST); msg != NULL; msg = msg->next){
                m->round = PREPARE;
                m->phase = phase;
                m->view = view;
                send(all,m);
            }

            round = PREPAREOK;
            
            continue;
        }

        if(round == REQUEST && count_messages(mbox, view, PREPARE) > 0){

            round = PREPAREOK;

            for(list * msg = mbox_iterator(mbox, view, PREPARE); msg != NULL; msg = msg->next){
                m->round = PREPAREOK;
                m->phase = phase;
                m->view = view;
                send(primary(view,n),m);
            }

            phase = phase+1;
            round = REQUEST;

            continue;
        }

        if(round == PREPAREOK && p==primary(view,n) && count_messages(mbox, view, PREPAREOK) > 0){

            for(list * msg = mbox_iterator(mbox, view, PREPAREOK); msg != NULL; msg = msg->next){
                if(count_by_message(msg, mbox, view, PREPAREOK) > f){
                    reply_to_client(msg);
                }
            }

            phase = phase+1;
            round = REQUEST;
            
            continue;
        }

        // VIEWCHANGE

        if(primary_timeout()){
            
            round = STARTVIEWCHANGE;

            view = view+1;

            m->round = STARTVIEWCHANGE;
            m->phase = phase;
            m->view = view;
            m->replica = p;
            send(all,m);
            continue;
        }

        if(round == STARTVIEWCHANGE && count_messages(mbox, view, STARTVIEWCHANGE) > f){
            round = DOVIEWCHANGE;

            m->round = DOVIEWCHANGE;
            m->view = view;
            m->log = local_log();
            send(primary(view,n), m);

            round = STARTVIEW;

            continue;
        }

        if(round == DOVIEWCHANGE && p==primary(view,n) && count_messages(mbox, view, DOVIEWCHANGE) > f){

            round = STARTVIEW;

            m->round = STARTVIEW;
            m->view = view;
            m->log = local_log();
            send(all, m);

            continue;
        }

        if(round == STARTVIEW && count_messages(mbox, view, STARTVIEW) > 0){
            
            computes_new_log();

            // Back to normalop
            round = REQUEST;
            phase = phase+1;
            continue;
        }


        

    }

}
