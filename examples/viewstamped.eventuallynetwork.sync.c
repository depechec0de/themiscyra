/*
Network assumption: EVENTUALLY process receive at least f+1 messages
*/

MAIN(){
    STARTVIEWCHANGE
        SEND:
            send(all, message(view,STARTVIEWCHANGE,p));

        UPDATE:
            if(count_messages(mbox) > f){
                STARTVIEWCHANGE_mbox = mbox;
            }else{
                vround = STARTVIEWCHANGE;
            }
            

    DOVIEWCHANGE
        SEND:
            if( p!=primary(view,n)) && count_messages(STARTVIEWCHANGE_mbox) > f){
                send(primary(view,n), message(view, DOVIEWCHANGE, p, log));
            }
        UPDATE:
            if(p==primary(view,n) && count_messages(STARTVIEWCHANGE_mbox) > f){
                DOVIEWCHANGE_mbox = mbox
            }else{
                vround = STARTVIEWCHANGE;
            }


    STARTVIEW
        SEND:
            if( p==primary(view,n)) && count_messages(STARTVIEWCHANGE_mbox) > f) && count_messages(DOVIEWCHANGE_mbox) > f){
                send(all, message(view,STARTVIEW,p));
            }
        UPDATE:
            if( p==primary(view,n) ){
                if(count_messages(STARTVIEWCHANGE_mbox) > f && count_messages(DOVIEWCHANGE_mbox) > f){
                    computes_new_log();
                    NORMALOP();
                }else{
                    vround = STARTVIEWCHANGE;
                }
            }else{
                if(count_messages(STARTVIEWCHANGE_mbox) > f && count_messages(mbox) == 1){
                    NORMALOP();
                }else{
                    vround = STARTVIEWCHANGE;
                }
            }
            
}

NORMALOP(){
    PREPARE

        SEND:
            if(p==primary(view,n)){
                send(all, message(view,PREPARE,p));
            }
        UPDATE:
            if(!(count_messages(mbox) == 1 && mbox[0]->replica == primary(view,n))){
                out();
            }else{
                PREPARE_mbox = mbox
            }

    PREPAREOK

        SEND:
            if(p!=primary(view,n) && count_messages(PREPARE_mbox) == 1){
                send(primary(view,n), message(view,vround,opnumber,PREPAREOK,p));
            }
        UPDATE:  
            if( p==primary(view,n) && count_messages(mbox) > f){
                PREPAREOK_mbox = mbox
            }else{
                out();
            }
            

    COMMIT

        SEND:
            if(p==primary(view,n) && count_messages(PREPAREOK_mbox) > f){
                send(all, message(view,vround,opnumber,COMMIT,p));
            }

        UPDATE:
            if(p!=primary(view,n) && count_messages(PREPARE_mbox) == 1 && count_messages(mbox) == 1){
                commit_to_log();
            }else if(p==primary(view,n) && count_messages(PREPAREOK_mbox) > f){
                commit_to_log();
            }else{
                out();
            }
             
}