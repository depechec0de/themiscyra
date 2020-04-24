
STARTVIEWCHANGE
    SEND:
        send(all, message(view,STARTVIEWCHANGE,p));

    UPDATE:

DOVIEWCHANGE
    SEND:
        if( p!=primary(view,n) && count_messages(mbox) > f)
            send(primary(view,n), message(view, DOVIEWCHANGE, p, log));
        }
    UPDATE:

STARTVIEW
    SEND:

    UPDATE:
        if( p==primary(view,n) && count_messages(old_mbox) > f)
            computes_new_log();
            NORMALOP();
        }


NORMALOP(){

    PREPARE

        SEND:
            if(p==primary(view,n) && client_request()){
                send(all, message(view,vround,opnumber,PREPARE,p));
            }
        UPDATE:
            if(p==primary(view,n) && count_messages(mbox) == 1){
                add_to_log(opnumber);
            }

    PREPAREOK

        SEND:
            if(p!=primary(view,n) && count_messages(mbox) == 1){
                send(primary(view,n), message(view,vround,opnumber,PREPAREOK,p));
            }
        UPDATE:  
            commit_number = opnumber;
            if( p==primary(view,n) && count_messages(mbox) >= f){
                reply_to_client();
            }else if(p!=primary(view,n)){
                add_to_log(opnumber);
            }

}