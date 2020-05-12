#include "viewstamped_types.h"
#include "viewstamped_decl.h"
int func(int p, int n, int f)
{
    int all=1000;

    // sync variables
    int view;
    int vround;

    msg* m;
    msg* recv_msg;

    list* mbox=NULL;
    
    view = 0;
    vround = STARTVIEWCHANGE;

    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));  

    while(1){

        mbox = havoc();

        if(vround == STARTVIEWCHANGE && p==primary(view,n) && count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f){
            vround = DOVIEWCHANGE;
            continue;
        }

        if(vround == STARTVIEWCHANGE && p!=primary(view,n) && count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f){
            vround = DOVIEWCHANGE;
            send(primary(view,n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));  
            vround = STARTVIEW;

            continue;
        }

        if(vround == DOVIEWCHANGE && p==primary(view,n) && count_messages(mbox, view, DOVIEWCHANGE, NULL, NULL) > f){
            vround = STARTVIEW;
            computes_new_log();
            send(all, message(view, STARTVIEW, NULL, NULL, p, local_log()));  
            view = view+1;
    
            continue;
        }

        if(vround == STARTVIEW && p!=primary(view,n) && count_messages(mbox, view, STARTVIEW, NULL, NULL) == 1){
            computes_new_log();
            view = view+1;

            continue;
        }

    }

}
