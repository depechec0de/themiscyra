/*

This file contains the (desired) sync version of viewstamped.c

The reductions are: viewstamped.c -> viewstamped.reduction1.c -> viewstamped.eventuallynetwork.sync.c

Communication predicate: EVENTUALLY process receive at least f+1 messages

\Pi = set of processes

\forall p \in \Pi, \forall r > 0, \exists r_0 > r : |HO(p, r_0)| >= n - f

*/

INIT(){
    int view = 0;
    int vround = STARTVIEWCHANGE;
    int opnumber = 0;
    int nround = PREPARE;

    int STARTVIEWCHANGE_mbox;
    int DOVIEWCHANGE_mbox;
    int PREPARE_mbox;
    int PREPAREOK_mbox;
}

MAIN(){
    STARTVIEWCHANGE{
        SEND(){
            send(all, message(view,STARTVIEWCHANGE,p));
        }
        UPDATE(mbox){
            STARTVIEWCHANGE_mbox = mbox;
            if(count_messages(mbox) > f){
                vround = DOVIEWCHANGE;
            }
        }
    }        

    DOVIEWCHANGE{
        SEND(){
            if( p!=primary(view,n)) && count_messages(STARTVIEWCHANGE_mbox) > f){
                send(primary(view,n), message(view, DOVIEWCHANGE, p, log));
            }
        }
        UPDATE(mbox){
            if(p!=primary(view,n) && count_messages(STARTVIEWCHANGE_mbox) > f){
                vround = STARTVIEW;
            }
            if(p==primary(view,n) && count_messages(mbox) > f){
                vround = STARTVIEW;
                DOVIEWCHANGE_mbox = mbox
            }
        }
    }

    STARTVIEW{
        SEND(){
            if( p==primary(view,n)) && count_messages(STARTVIEWCHANGE_mbox) > f) && count_messages(DOVIEWCHANGE_mbox) > f){
                send(all, message(view,STARTVIEW,p));
            }
        }
        UPDATE(mbox){
            if( p==primary(view,n) ){
                if(count_messages(STARTVIEWCHANGE_mbox) > f && count_messages(DOVIEWCHANGE_mbox) > f){
                    computes_new_log();
                    NORMALOP();
                }
            }else{
                if(count_messages(STARTVIEWCHANGE_mbox) > f && count_messages(mbox) == 1){
                    NORMALOP();
                }
            }
        }
    }        
}

NORMALOP(){
    PREPARE{

        SEND(){
            if(p==primary(view,n)){
                send(all, message(view,PREPARE,p));
            }
        }
        UPDATE(mbox){
            if(!(count_messages(mbox) == 1 && mbox[0]->replica == primary(view,n))){
                out();
            }else{
                PREPARE_mbox = mbox
            }
        }
    }
    PREPAREOK{

        SEND(){
            if(p!=primary(view,n) && count_messages(PREPARE_mbox) == 1){
                send(primary(view,n), message(view,vround,opnumber,PREPAREOK,p));
            }
        }
        UPDATE(mbox){
            if( p==primary(view,n) && count_messages(mbox) > f){
                PREPAREOK_mbox = mbox
            }else{
                out();
            }
        }
    }    

    COMMIT{

        SEND(){
            if(p==primary(view,n) && count_messages(PREPAREOK_mbox) > f){
                send(all, message(view,vround,opnumber,COMMIT,p));
            }
        }

        UPDATE(mbox){
            if(p!=primary(view,n) && count_messages(PREPARE_mbox) == 1 && count_messages(mbox) == 1){
                commit_to_log();
            }else if(p==primary(view,n) && count_messages(PREPAREOK_mbox) > f){
                commit_to_log();
            }else{
                out();
            }
        }
    }       
}