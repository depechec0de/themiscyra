struct Msg
{
  int round;
  int ballot;
};
typedef struct Msg msg;
typedef struct List
{
  msg *message;
  struct List *next;
  int size;
} list;

enum round_typ {A, B};

/*@ ensures (\result == \null) ||
    (\result != \null &&
    \valid(\result) &&
    \initialized(&\result->round) &&
    \initialized(&\result->ballot) &&
    (\result->round == 0 ||  \result->round == 1));
@*/
msg * recv(int v, int t){
    msg* m = (msg *) malloc(sizeof(msg));
    if (m==NULL) return NULL;
    m->round = v%2;
    m->ballot = t;
    return m;
}

/*@
requires \true;
ensures \result >= 0 && \result <= n;
@*/
int count(list * mboxA, int ballot, int round, int n);

void send(int addr, msg * m);

/*@ requires p>=0 && n>0 && n<=2000;
@*/
int func(int p, int n);
int func(int p, int n)
{
    int round;
    int ballot;
    int v=p;
    int t=p;
    int all=1000;
    int timeout;
    
    msg* m;
    msg* recv_msg;
    list* mboxA=NULL;
    list* mboxB=NULL;

    round = A;
    ballot = 0;

    m = (msg *) malloc(sizeof(msg));
    m->round = round;
    m->ballot = ballot;
    send(all,m);

    while(1){
        
        recv_msg = recv(v,t);

        if(recv_msg!=NULL && recv_msg->round==A ){
            add_msg(mboxA, recv_msg->ballot, recv_msg);
        }
        if(recv_msg!=NULL && recv_msg->round==B){
            add_msg(mboxB, recv_msg->ballot, recv_msg);
        }

        
        if(round==A && countA(mboxA,ballot) > 2*n/3){
            computation(mboxA);
            dispose(mboxA, ballot, round);
            round = B;
            m = (msg *) malloc(sizeof(msg));
            m->round = B;
            m->ballot = ballot;
            send(all,m);
            continue; 
        }
 
        if(round==B && countB(mboxB,ballot) > 2*n/3){
            computation(mboxB);
            dispose(mboxB, ballot, round);
            ballot++;
            round = A;
            m = (msg *) malloc(sizeof(msg));
            m->round = A;
            m->ballot = ballot;
            send(all,m);
            continue; 
        }

        if(timeout){
            dispose(mboxB, mboxA);
            reset_timeout();
            ballot++;
            round = A;
            m = (msg *) malloc(sizeof(msg));
            m->round = A;
            m->ballot = ballot;
            send(all,m);
            continue;
        }

    }



}