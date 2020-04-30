/*
Network assumption: process receive at least f+1 messages each round
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
        UPDATE(phase, mbox){}
    }        
            
    DOVIEWCHANGE{
        SEND(phase){
            if( p!=primary(view,n) ){
                send(primary(view,n), message(view, DOVIEWCHANGE, p, log));
            }
        }
        UPDATE(phase, mbox){}
    }        

    STARTVIEW{
        SEND(phase){
            if( p==primary(view,n))){
                send(all, message(view,STARTVIEW,p));
            }
        }
        UPDATE(phase, mbox){
            if(!(count_messages(mbox) == 1 && mbox[0]->replica == primary(view,n))){
                vround = STARTVIEWCHANGE;
            }
            computes_new_log();
            NORMALOP();
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
            }
        }
    }

    PREPAREOK{
        SEND(phase){
            if(p!=primary(view,n)){
                send(primary(view,n), message(view,vround,opnumber,PREPAREOK,p));
            }
        }
        UPDATE(phase, mbox){}
    }

    COMMIT{
        SEND(phase){
            if(p==primary(view,n)){
                send(all, message(view,vround,opnumber,COMMIT,p));
            }
        }
        UPDATE(phase, mbox){              
            if(count_messages(mbox) == 1 && mbox[0]->replica == primary(view,n)){
                commit_to_log();
            }else{
                out();
            }
        }
    }        
}