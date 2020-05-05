#include "viewstamped_types.h"
#include "viewstamped_decl.h"
int func(int p, int n, int f)
{
    int all=1000;

    // sync variables
    int view = 0;
    int vround = STARTVIEWCHANGE;
    int opnumber = 0;
    int nround = PREPARE;

    msg* m;
    msg* recv_msg;

    list* mbox=NULL;

    while(1){

        mbox = havoc();

        if(vround == STARTVIEW && nround == PREPARE && p==primary(view,n)){
            // NORMALOP
            send(all, message(view, STARTVIEW, opnumber, PREPARE, p));      
            nround = PREPAREOK;

            continue;
        }

        if(vround == STARTVIEW && nround == PREPARE && p!=primary(view,n) && count_messages(mbox, view, STARTVIEW, opnumber, PREPARE) == 1){
            // NORMALOP
            nround = PREPAREOK;
            send(primary(view,n), message(view, STARTVIEW, opnumber, PREPAREOK, p));
            nround = COMMIT;

            continue;
        }

        if(vround == STARTVIEW && nround == PREPAREOK && p==primary(view,n) && count_messages(mbox, view, STARTVIEW, opnumber, PREPAREOK) > f){
            // NORMALOP
            nround = COMMIT;
            commit_to_log();
            reply_to_clients();
            send(all, message(view, STARTVIEW, opnumber, COMMIT, p));     
            
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
            send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));  

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
            send(primary(view,n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));  
            vround = STARTVIEW;

            continue;
        }

        if(vround == DOVIEWCHANGE && p==primary(view,n) && count_messages(mbox, view, DOVIEWCHANGE, NULL, NULL) > f){
            // VIEWCHANGE
            vround = STARTVIEW;
            computes_new_log();
            send(all, message(view, STARTVIEW, NULL, NULL, p, local_log()));  
            view = view+1;
            nround = PREPARE;
            // NORMALOP

            continue;
        }

        if(vround == STARTVIEW && p!=primary(view,n) && count_messages(mbox, view, STARTVIEW, NULL, NULL) == 1){
            // VIEWCHANGE
            computes_new_log();
            view = view+1;

            nround = PREPARE;
            // NORMALOP
            continue;
        }

    }

}
