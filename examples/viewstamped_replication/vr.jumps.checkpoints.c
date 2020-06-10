struct Msg
{
  int view;
  int vround;

  int opnumber;
  int nround;

  int last_checkpoint_opnumber;
  int last_checkpoint_view;
  int cround;

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
  LISTENINGCHECKPOINT,
  CHECKPOINT_ACK
};
msg *recv();
int count(list *mbox, int regency, int round, int n);
int size(list *mbox);
void send(int addr, msg *m);
int func(int p, int n, int f);
int func(int p, int n, int f)
{
    int all=1000;

    // sync variables
    int view;
    int vround;

    int opnumber;
    int nround;
    
    int last_checkpoint_opnumber;
    int cround;

    // protocol variables
    int last_checkpoint_view;
    
    int commit_number = 0;
    int future_view = 0;
    list* log = NULL;

    // last snapshot
    void* current_state = NULL;

    // checkpoint variables
    int CHECKPOINT_CYCLE = 128;

    /***** Starting state *****/
    view = 0;
    vround = STARTVIEWCHANGE;

    opnumber = 0;
    nround = PREPARE;

    last_checkpoint_opnumber = 0;
    cround = LISTENINGCHECKPOINT;

    last_checkpoint_view = 0;
    
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

        if( future_view > view && count_messages(mbox, future_view, STARTVIEWCHANGE) > 0)
        {
            // VIEWCHANGE
            vround = STARTVIEWCHANGE;
            view = future_view;
            send(all, message(future_view,STARTVIEWCHANGE,p));
            continue;
        }

        if( future_view > view && count_messages(mbox, future_view, DOVIEWCHANGE) > 0)
        {
            // VIEWCHANGE
            vround = STARTVIEWCHANGE;
            view = future_view;
            send(all, message(future_view,STARTVIEWCHANGE,p));
            continue;
        }

        if( p!=primary(future_view,n) && future_view > view && count_messages(mbox, future_view, STARTVIEWCHANGE) > f)
        {
            // VIEWCHANGE
            vround = DOVIEWCHANGE;
            send(primary(future_view,n), message(future_view, DOVIEWCHANGE, p, log));
            vround = STARTVIEW;        
            continue;
        }

        if( p==primary(future_view,n) && count_messages(mbox, future_view, DOVIEWCHANGE) > f)
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

        if( p!=primary(future_view,n) && count_messages(mbox, future_view, STARTVIEW) > 0)
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

            current_state = generate_snapshot(log);
            last_checkpoint_opnumber = opnumber;
            last_checkpoint_view = view;
            
            delete_all_entries(log);

            continue;

        }

        // if I received a message asking for an old view / opnumber we update the replica
        if(p==primary(view,n) && cround == LISTENINGCHECKPOINT && heard_delayed_replica(mbox)){

            send(get_delayed_replica(mbox, view, opnumber), checkpoint_message(last_checkpoint_opnumber, LISTENINGCHECKPOINT, current_state));
            cround = CHECKPOINT_ACK;
            continue;
        }

        if(p==primary(view,n) && cround == CHECKPOINT_ACK && count_messages(mbox, CHECKPOINT_ACK) > 0){
            cround = LISTENINGCHECKPOINT;
            continue;
        }

        if(p!=primary(view,n) && cround == LISTENINGCHECKPOINT && count_messages(mbox, LISTENINGCHECKPOINT) > 0){

            cround = CHECKPOINT_ACK; 

            recv_msg = get_snapshot_message(mbox);

            last_checkpoint_opnumber = recv_msg->last_checkpoint_opnumber;
            last_checkpoint_view = recv_msg->last_checkpoint_view;
            current_state = recv_msg->state;

            opnumber = last_checkpoint_opnumber;

            // remove all entries < snapshot.last_included_opnumber
            delete_old_entries(log, last_checkpoint_opnumber);

            send(primary(view,n), checkpoint_message(last_checkpoint_opnumber, CHECKPOINT_ACK));

            cround = LISTENINGCHECKPOINT;

            continue;

        }
    }

}
