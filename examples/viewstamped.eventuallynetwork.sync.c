/*
Network assumption: EVENTUALLY process receive at least f+1 messages
*/

INIT(){
    int view = 0;
    int vround = STARTVIEWCHANGE;
    int phase = 0;
    int nround = PREPARE;

    int STARTVIEWCHANGE_mbox;
    int DOVIEWCHANGE_mbox;
    int PREPARE_mbox;
    int PREPAREOK_mbox;
}

MAIN(){
    STARTVIEWCHANGE{
        SEND(phase){
            send(all, message(view,STARTVIEWCHANGE,p));
        }
        UPDATE(phase, mbox){
            if(count_messages(mbox) > f){
                STARTVIEWCHANGE_mbox = mbox;
            }
        }
    }        

    DOVIEWCHANGE{
        SEND(phase){
            if( p!=primary(view,n)) && count_messages(STARTVIEWCHANGE_mbox) > f){
                send(primary(view,n), message(view, DOVIEWCHANGE, p, log));
            }
        }
        UPDATE(phase, mbox){
            if(p==primary(view,n) && count_messages(STARTVIEWCHANGE_mbox) > f){
                DOVIEWCHANGE_mbox = mbox
            }
        }
    }

    STARTVIEW{
        SEND(phase){
            if( p==primary(view,n)) && count_messages(STARTVIEWCHANGE_mbox) > f) && count_messages(DOVIEWCHANGE_mbox) > f){
                send(all, message(view,STARTVIEW,p));
            }
        }
        UPDATE(phase, mbox){
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

        SEND(phase){
            if(p==primary(view,n)){
                send(all, message(view,PREPARE,p));
            }
        }
        UPDATE(phase, mbox){
            if(!(count_messages(mbox) == 1 && mbox[0]->replica == primary(view,n))){
                out();
            }else{
                PREPARE_mbox = mbox
            }
        }
    }
    PREPAREOK{

        SEND(phase){
            if(p!=primary(view,n) && count_messages(PREPARE_mbox) == 1){
                send(primary(view,n), message(view,vround,opnumber,PREPAREOK,p));
            }
        }
        UPDATE(phase, mbox){
            if( p==primary(view,n) && count_messages(mbox) > f){
                PREPAREOK_mbox = mbox
            }else{
                out();
            }
        }
    }    

    COMMIT{

        SEND(phase){
            if(p==primary(view,n) && count_messages(PREPAREOK_mbox) > f){
                send(all, message(view,vround,opnumber,COMMIT,p));
            }
        }

        UPDATE(phase, mbox){
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