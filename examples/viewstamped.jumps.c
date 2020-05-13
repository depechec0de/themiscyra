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
    int vround = STARTVIEW;
    int opnumber = 0;
    int nround;

    // protocol variables
    int commit_number = 0;
    int future_view = 0;
    list* log = NULL;

    nround = PREPARE;
    
    msg* m;
    msg* recv_msg;

    list* mbox=NULL;

    while(1){

        mbox = havoc();
        future_view = get_max_view(mbox);

        if( p==primary(view,n) && vround == STARTVIEW && nround == PREPARE && client_request())
        { 
            // NORMALOP
            add_to_log(opnumber);
            send(all, message(view,vround,opnumber,PREPARE,p));
            nround = PREPAREOK;
            
            continue;
        }

        if( p==primary(view,n) && vround == STARTVIEW && nround == PREPAREOK && count_messages(mbox, view, STARTVIEW, opnumber, PREPAREOK) >= f)
        {
            // NORMALOP
            commit_number = opnumber;

            reply_to_client();
            
            opnumber = opnumber+1;
            nround = PREPARE;
            
            continue;
        }

        if( p!=primary(view,n) && vround == STARTVIEW && nround == PREPARE && count_messages(mbox, view, STARTVIEW, opnumber, PREPARE) == 1)
        {
            // NORMALOP
            nround = PREPAREOK;

            commit_number = opnumber;
            add_to_log(opnumber);
            send(primary(view,n), message(view,vround,opnumber,PREPAREOK,p));
            
            opnumber = opnumber+1;
            nround = PREPARE;
            
            continue;
        }

        if( primary_timeout() )
        {
            // VIEWCHANGE
            vround = STARTVIEWCHANGE;
            view = view+1;
            send(all, message(view,STARTVIEWCHANGE,p));
            continue;
        }

        if( future_view > view && count_messages(mbox, future_view, STARTVIEWCHANGE, NULL, NULL) > 0)
        {
            // VIEWCHANGE
            vround = STARTVIEWCHANGE;
            view = future_view;
            send(all, message(future_view,STARTVIEWCHANGE,p));
            continue;
        }

        if( future_view > view && count_messages(mbox, future_view, DOVIEWCHANGE, NULL, NULL) > 0)
        {
            // VIEWCHANGE
            vround = STARTVIEWCHANGE;
            view = future_view;
            send(all, message(future_view,STARTVIEWCHANGE,p));
            continue;
        }

        if( p!=primary(future_view,n) && future_view > view && count_messages(mbox, future_view, STARTVIEWCHANGE, NULL, NULL) > f)
        {
            // VIEWCHANGE
            vround = DOVIEWCHANGE;
            send(primary(future_view,n), message(future_view, DOVIEWCHANGE, p, log));
            vround = STARTVIEW;        
            continue;
        }

        if( p==primary(future_view,n) && count_messages(mbox, future_view, DOVIEWCHANGE, NULL, NULL) > f)
        {
            // VIEWCHANGE
            view = future_view;
            vround = STARTVIEW;

            computes_new_log();
            send(all, message(future_view, STARTVIEW, p, log));
            // NORMALOP
            nround = PREPARE;
            continue;
        }

        if( p!=primary(future_view,n) && count_messages(mbox, future_view, STARTVIEW, NULL, NULL) > 0)
        {
            // VIEWCHANGE
            view = future_view;
            computes_new_log();
            // NORMALOP
            nround = PREPARE;
            continue;
        }

    }

}
