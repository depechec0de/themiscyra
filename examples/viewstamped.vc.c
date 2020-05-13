struct Msg
{
  int view;
  int vround;
  int opnumber;
  int nround;
  
  int replica;
  void* log;
};
typedef struct Msg msg;
typedef struct List
{
  msg *message;
  struct List *next;
  int size;
} list;

enum vround_typ {STARTVIEWCHANGE, DOVIEWCHANGE, STARTVIEW};
enum nround_typ {PREPARE, PREPAREOK, COMMIT};

/*@ ensures (\result == \null) ||
    (\result != \null &&
    \valid(\result) &&
    \initialized(&\result->round) &&
    \initialized(&\result->ballot) &&
    (\result->round == 0 ||  \result->round == 1));
@*/
msg * recv();

/*@
requires \true;
ensures \result >= 0 && \result <= n;
@*/
int count(list * mbox, int regency, int round, int n);

int size(list * mbox);

void send(int addr, msg * m);

// Count how many messages in mbox satisfy to be equal in view, vround, phase and nround.
int count_messages(list * mbox, int view, enum vround_typ vround, int phase, enum nround_typ nround);

/*@ requires p>=0 && n>0 && n<=2000;
@*/
int main(int p, int n, int f);
int main(int p, int n, int f)
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

            vround = STARTVIEWCHANGE;
    
            continue;
        }

        if(vround == STARTVIEW && p!=primary(view,n) && count_messages(mbox, view, STARTVIEW, NULL, NULL) == 1){
            computes_new_log();
            view = view+1;
            
            vround = STARTVIEWCHANGE;
            send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p)); 

            continue;
        }

    }

}
