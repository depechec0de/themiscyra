/*
Network assumption: process receive at least f+1 messages each round
*/

MAIN(){
    STARTVIEWCHANGE
        SEND:
            send(all, message(view,STARTVIEWCHANGE,p));

        UPDATE:
            
            
    DOVIEWCHANGE
        SEND:
            if( p!=primary(view,n) ){
                send(primary(view,n), message(view, DOVIEWCHANGE, p, log));
            }
        UPDATE:
            

    STARTVIEW
        SEND:
            if( p==primary(view,n))){
                send(all, message(view,STARTVIEW,p));
            }
        UPDATE:
            if(!(count_messages(mbox) == 1 && mbox[0]->replica == primary(view,n))){
                vround = STARTVIEWCHANGE;
            }
            computes_new_log();
            NORMALOP();
            
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
            }

    PREPAREOK

        SEND:
            if(p!=primary(view,n)){
                send(primary(view,n), message(view,vround,opnumber,PREPAREOK,p));
            }
        UPDATE:  


    COMMIT

        SEND:
            if(p==primary(view,n)){
                send(all, message(view,vround,opnumber,COMMIT,p));
            }

        UPDATE:                
            if(count_messages(mbox) == 1 && mbox[0]->replica == primary(view,n)){
                commit_to_log();
            }else{
                out();
            }
            
}