MAIN(){
    STARTVIEWCHANGE
        SEND:
            send(all, message(view,STARTVIEWCHANGE,p));

        UPDATE:
            if(count_messages(mbox) > f){
                vround = DOVIEWCHANGE;
            }
            STARTVIEWCHANGE_mbox = mbox;

    DOVIEWCHANGE
        SEND:
            if( p!=primary(view,n)) && count_messages(STARTVIEWCHANGE_mbox) > f){
                send(primary(view,n), message(view, DOVIEWCHANGE, p, log));
            }
        UPDATE:
            DOVIEWCHANGE_mbox = mbox
            if( p!=primary(view,n)){
                vround = STARTVIEW;
            }else if(p==primary(view,n) && count_messages(STARTVIEWCHANGE_mbox) > f){
                vround = STARTVIEW;
            }else{
                vround = ERR_ROUND;
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
                    nround = PREPARE;
                    NORMALOP();
                    vround = STARTVIEWCHANGE;
                }else{
                    vround = ERR_ROUND;
                }
            }else{
                if(count_messages(STARTVIEWCHANGE_mbox) > f && count_messages(mbox) == 1){
                    nround = PREPARE;
                    NORMALOP();
                    vround = STARTVIEWCHANGE;
                }else{
                    vround = ERR_ROUND;
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
            PREPARE_mbox = mbox
            if(p!=primary(view,n) && count_messages(mbox) == 1){
                nround = PREPAREOK;
            }else if(p==primary(view,n)){
                nround = PREPAREOK;
            }else{
                out();
            }

    PREPAREOK

        SEND:
            if(p!=primary(view,n) && count_messages(PREPARE_mbox) == 1){
                send(primary(view,n), message(view,vround,opnumber,PREPAREOK,p));
            }
        UPDATE:  
            if( p==primary(view,n) && count_messages(mbox) > f){
                nround = COMMIT;
            }else if(p!=primary(view,n)){
                nround = COMMIT;
            }else{
                out();
            }
            PREPAREOK_mbox = mbox

    COMMIT

        SEND:
            if(p==primary(view,n) && count_messages(PREPAREOK_mbox) > f){
                send(all, message(view,vround,opnumber,COMMIT,p));
            }

        UPDATE:
            if(p!=primary(view,n) && count_messages(PREPARE_mbox) == 1 && count_messages(mbox) == 1){
                commit_to_log();
                nround = PREPARE;
            }else if(p==primary(view,n) && count_messages(PREPAREOK_mbox) > f){
                commit_to_log();
                nround = PREPARE;
            }else{
                out();
            }
             
}