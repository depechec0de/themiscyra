/* 

Reduction from viewstamped.c as an intermediate step to viewstamped.eventuallynetwork.sync.c

Transformations:
* UPONS separated in main while and inner while depending of the protocol
* Break statement when we need to return to main protocol
* vround == STARTVIEW removed from all normalop upons and moved to while boolean condition

*/

struct Msg
{
  int view;
  int vround;
  int opnumber;
  int nround;
  int replica;
  void *log;
};
typedef struct Msg msg;
typedef struct List
{
  msg *message;
  struct List *next;
  int size;
} list;
enum vround_typ
{
  STARTVIEWCHANGE,
  DOVIEWCHANGE,
  STARTVIEW
};
enum nround_typ
{
  PREPARE,
  PREPAREOK,
  COMMIT
};
msg *recv();
int count(list *mbox, int regency, int round, int n);
int size(list *mbox);
void send(int addr, msg *m);
int count_messages(list *mbox, int view, enum vround_typ vround, int phase, enum nround_typ nround);
int func(int p, int n, int f);
int func(int p, int n, int f)
{
    int all=1000;

    // sync variables
    int view = 0;
    int vround = STARTVIEWCHANGE;
    int opnumber = 0;
    int nround = PREPARE;

    msg* m;
    msg* recv_msg;

    list* mbox=NULL;

    while(1){

        mbox = havoc();

        if(vround == STARTVIEWCHANGE && p==primary(view,n) && count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f){
            // VIEWCHANGE
            vround = DOVIEWCHANGE;
            continue;
        }

        if(vround == STARTVIEWCHANGE && p!=primary(view,n) && count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f){
            // VIEWCHANGE
            vround = DOVIEWCHANGE;
            send(primary(view,n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));  
            vround = STARTVIEW;

            continue;
        }

        if(vround == DOVIEWCHANGE && p==primary(view,n) && count_messages(mbox, view, DOVIEWCHANGE, NULL, NULL) > f){
            // VIEWCHANGE
            vround = STARTVIEW;
            computes_new_log();
            send(all, message(view, STARTVIEW, NULL, NULL, p, local_log()));  
            view = view+1;
            nround = PREPARE;
            // NORMALOP

            continue;
        }

        if(vround == STARTVIEW && p!=primary(view,n) && count_messages(mbox, view, STARTVIEW, NULL, NULL) == 1){
            // VIEWCHANGE
            computes_new_log();
            view = view+1;

            nround = PREPARE;
            // NORMALOP
            continue;
        }

        while(vround == STARTVIEW){

            mbox = havoc();

            if(nround == PREPARE && p==primary(view,n)){
                // NORMALOP
                send(all, message(view, STARTVIEW, opnumber, PREPARE, p));      
                nround = PREPAREOK;

                continue;
            }

            if(nround == PREPARE && p!=primary(view,n) && count_messages(mbox, view, STARTVIEW, opnumber, PREPARE) == 1){
                // NORMALOP
                nround = PREPAREOK;
                send(primary(view,n), message(view, STARTVIEW, opnumber, PREPAREOK, p));
                nround = COMMIT;

                continue;
            }

            if(nround == PREPAREOK && p==primary(view,n) && count_messages(mbox, view, STARTVIEW, opnumber, PREPAREOK) > f){
                // NORMALOP
                nround = COMMIT;
                commit_to_log();
                reply_to_clients();
                send(all, message(view, STARTVIEW, opnumber, COMMIT, p));     
                
                opnumber = opnumber+1;
                nround = PREPARE;

                continue;
            }

            if(nround == COMMIT && p!=primary(view,n) && count_messages(mbox, view, STARTVIEW, opnumber, COMMIT) == 1){
                // NORMALOP
                commit_to_log();

                opnumber = opnumber+1;
                nround = PREPARE;
            }

            if(primary_timeout()){
                // VIEWCHANGE
                vround = STARTVIEWCHANGE;
                send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
                break;
            }

        }  // END NORMALOP

        
    }

}
