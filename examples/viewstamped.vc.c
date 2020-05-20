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

/*@ ensures (\result == \null) ||
    (\result != \null &&
    \valid(\result) &&
    \initialized(&\result->round) &&
    \initialized(&\result->ballot) &&
    (\result->round == 0 ||  \result->round == 1));
@*/
msg * recv();

void send(int addr, msg * m);

// Count how many messages in mbox satisfy to be equal in view, vround, phase and nround.
int count_messages(list * mbox, int view, enum vround_typ vround);

/*@ requires p>=0 && n>0 && n<=2000;
@*/
int main(int p, int n, int f);
int main(int p, int n, int f)
{
    int all;
    // sync variables
    int view;
    enum vround_typ vround;

    msg* m;
    msg* recv_msg;

    list* mbox=NULL;
    
    vround = STARTVIEWCHANGE;
    view = 0;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p)); 

    while(1){

        mbox = havoc();
        if(vround == STARTVIEWCHANGE && p==primary(view,n) && count_messages(mbox, view, STARTVIEWCHANGE) > f){
            vround = DOVIEWCHANGE;
            continue;
        }      
        
        if(vround == STARTVIEWCHANGE && p!=primary(view,n) && count_messages(mbox, view, STARTVIEWCHANGE) > f){
            vround = DOVIEWCHANGE;
            send(primary(view,n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));  
            vround = STARTVIEW;

            continue;
        }

        if(vround == DOVIEWCHANGE && p==primary(view,n) && count_messages(mbox, view, DOVIEWCHANGE) > f){
            computes_new_log();
            vround = STARTVIEW;
            send(all, message(view, STARTVIEW, NULL, NULL, p, local_log())); 

            view = view+1;
            vround = STARTVIEWCHANGE;
            send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p)); 
    
            continue;
        }
        
        if(vround == STARTVIEW && p!=primary(view,n) && count_messages(mbox, view, STARTVIEW) == 1){
            computes_new_log();
            
            view = view+1;
            vround = STARTVIEWCHANGE;
            send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p)); 

            continue;
        }
        
    }

}
