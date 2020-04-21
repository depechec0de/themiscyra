#include "viewstamped_types.h"
#include "viewstamped_decl.h"
int func(int p, int n, int f)
{
    int all=1000;

    // sync variables
    int view = 0;
    int vround = STARTVIEW;
    int opnumber = 0;
    int nround;

    // protocol variables
    int commit_number = 0;
    int future_view = 0;
    list* log = NULL;

    nround = PREPARE;
    
    msg* m;
    msg* recv_msg;

    list* mbox=NULL;

    while(1){

        mbox = havoc();

        /*********************
        
            Normal operation 
        
        **********************/

        if( p==primary(view,n) && vround == STARTVIEW && nround == PREPARE && client_request())
        { 
            add_to_log(opnumber);
            send(all, message(view,vround,opnumber,PREPARE,p));
            nround = PREPAREOK;
            
            continue;
        }

        if( p==primary(view,n) && vround == STARTVIEW && nround == PREPAREOK && count_messages(mbox, view, STARTVIEW, opnumber, PREPAREOK) >= f)
        {
            commit_number = opnumber;

            reply_to_client();
            
            opnumber = opnumber+1;
            nround = PREPARE;
            
            continue;
        }

        if( p!=primary(view,n) && vround == STARTVIEW && nround == PREPARE && count_messages(mbox, view, STARTVIEW, opnumber, PREPARE) == 1)
        {
            
            nround = PREPAREOK;

            commit_number = opnumber;
            add_to_log(opnumber);
            send(primary(view,n), message(view,vround,opnumber,PREPAREOK,p));
            
            opnumber = opnumber+1;
            nround = PREPARE;
            
            continue;
        }

        // if I didn't received the requests between opnumber and my max stored opnumber for a long time I request a state transfer
        if (requests_timeout())
        {
            // I ask for all the requests starting from my last commit
            state_transfer_from(commit_number);
        }

        /*********************
        
            View Change 
        
        **********************/

        future_view = get_max_view(mbox);

        if( primary_timeout())
        {
            vround = STARTVIEWCHANGE;
            view = view+1;
            send(all, message(view,STARTVIEWCHANGE,p));
            continue;
        }

        if( future_view > view && count_messages(mbox, future_view, STARTVIEWCHANGE, NULL, NULL) > 0)
        {
            vround = STARTVIEWCHANGE;
            view = future_view;
            send(all, message(future_view,STARTVIEWCHANGE,p));
            continue;
        }

        if( future_view > view && count_messages(mbox, future_view, DOVIEWCHANGE, NULL, NULL) > 0)
        {
            vround = STARTVIEWCHANGE;
            view = future_view;
            send(all, message(future_view,STARTVIEWCHANGE,p));
            continue;
        }

        if( p!=primary(future_view,n) && future_view > view && count_messages(mbox, future_view, STARTVIEWCHANGE, NULL, NULL) > f)
        {
            vround = DOVIEWCHANGE;
            send(primary(future_view,n), message(future_view, DOVIEWCHANGE, p, log));
            vround = STARTVIEW;        
            continue;
        }

        if( p==primary(future_view,n) && count_messages(mbox, future_view, DOVIEWCHANGE, NULL, NULL) > f)
        {
            view = future_view;
            vround = STARTVIEW;

            computes_new_log();
            send(all, message(future_view, STARTVIEW, p, log));

            nround = REQUEST;

            continue;
        }

        if( p!=primary(future_view,n) && count_messages(mbox, future_view, STARTVIEW, NULL, NULL) > 0)
        {
            view = future_view;
            computes_new_log();
            // Back to normalop
            nround = PREPARE;
            continue;
        }

    }

}
