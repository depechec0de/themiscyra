struct Msg
{
  int view;
  int vround;
  int opnumber;
  int nround;
  int replica;
  void *log;
  void *state;
};
typedef struct Msg msg;

typedef struct List
{
  msg *message;
  struct List *next;
  int size;
} list;

typedef struct State
{
  int last_included_opnumber;
  int last_included_view;
  void *data;
} state;

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

enum checkpoint_typ
{
  INSTALLSNAPSHOT,
  INSTALLSNAPSHOT_ACK
};
msg *recv();
int count(list *mbox, int regency, int round, int n);
int size(list *mbox);
void send(int addr, msg *m);
int count_messages(list *mbox, int view, enum vround_typ vround, int phase, enum nround_typ nround);
int count_checkpoint_messages(list *mbox, enum checkpoint_typ vround);
int func(int p, int n, int f);
int func(int p, int n, int f)
{
    int all=1000;

    // sync variables
    int view = 0;
    int vround = STARTVIEWCHANGE;
    int opnumber = 0;
    int nround;

    // protocol variables
    int commit_number = 0;
    int future_view = 0;
    list* log = NULL;
    state* current_state = NULL;

    // checkpoint variables
    int CHECKPOINT_CYCLE = 128;

    /***** Starting state *****/

    nround = PREPARE;
    
    msg* m;
    msg* recv_msg;

    list* mbox=NULL;

    while(1){

        mbox = havoc();
        future_view = get_max_view(mbox);

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

        
        if(opnumber % CHECKPOINT_CYCLE == 0){

            current_state->data = generate_snapshot(log);
            current_state->last_included_opnumber = opnumber;
            current_state->last_included_view = view;
            
            delete_all_entries(log);

            continue;

        }

        // if I received a message asking for an old view / opnumber we update the replica
        if(p==primary(view,n) && count_delayed_messages(mbox, view, opnumber) > 0){

            send(get_delayed_replica(mbox, view, opnumber), message(INSTALLSNAPSHOT, current_state));

            continue;

        }

        if(p!=primary(view,n) && count_checkpoint_messages(mbox, INSTALLSNAPSHOT) > 0){

            recv_msg = get_snapshot_message(mbox);

            current_state = recv_msg->state;

            // remove all entries < snapshot.last_included_opnumber
            delete_old_entries(log, current_state->last_included_opnumber);

            send(primary(view,n), message(INSTALLSNAPSHOT_ACK));

            continue;

        }
    }

}
