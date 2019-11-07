typedef struct Msg {
    int op;
    int i;
    int round;
    int sender;
} msg;

typedef struct List{
    msg * message;
    struct List * next;
    int size;
} list;


int main()
{
    int round;
    int ballot;
    struct list* mboxA = NULL;
    struct list* mboxB = NULL;
    struct msg* recv_msg = NULL;
    struct msg* m = NULL;
    int n;
    int all = n+1;
    _Bool timeout;

    round = 0;
    ballot = 0;

    m = (msg *) malloc(sizeof(msg));
    m->round = round;
    m->ballot = ballot;
    send(all,m);

    while(true){
        
        recv_msg = recv();

        if(recv_msg!=NULL && recv_msg->round==0 ){
            mboxA[recv_msg->ballot] = mboxA[recv_msg->ballot] + recv_msg;
            if(round==0 && countA(mboxA,ballot) > 2*n/3){
                computation(mboxA);
                dispose(mboxA);
                round = 1;
                m = (msg *) malloc(sizeof(msg));
                m->round = round;
                m->ballot = ballot;
                send(all,m);
                continue; 
            }

        }
        
        if(recv_msg!=NULL && recv_msg->round==1){
            mboxB[recv_msg->ballot] = mboxB[recv_msg->ballot]  + recv_msg;
            if(round==1 && countB(mboxB,ballot) > 2*n/3){
                computation(mboxB);
                dispose(mboxB);
                ballot++;
                round = 0;
                m = (msg *) malloc(sizeof(msg));
                m->round = round;
                m->ballot = ballot;
                send(all,m);
                continue;
            }
            
        }

        if(timeout){
            dispose(mboxB, mboxA);
            reset_timeout();
            ballot++;
            round = 0;
            m = (msg *) malloc(sizeof(msg));
            m->round = round;
            m->ballot = ballot;
            send(all,m);
            continue;
        }

    }



}