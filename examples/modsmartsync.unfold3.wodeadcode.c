#include "stdlib.h"
#include "modsmartsync_types.h"

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
int count(list * mbox, int regency, int round, int n);

int count_change_regency(list * mbox, int regency);

list* valid_timedout_messages(list* mbox);

list* signed_stopdata_messages(list* mbox);

int size(list * mbox);

void send(int addr, msg * m);

/*@ requires p>=0 && n>0 && n<=2000;
@*/
int func(int p, int n);
struct Msg
{
  int round;
  int reg;
  void *timedout_msgs;
  void *decided_log;
  void *proofs;
};
typedef struct Msg msg;
typedef struct List
{
  msg *message;
  struct List *next;
  int size;
} list;
enum round_typ
{
  STOP,
  STOPDATA,
  SYNC
};
int func(int p, int n)
{
  int round;
  int leader;
  int timeout;
  int all = 1000;
  int creg = 0;
  int nreg = 0;
  msg *m;
  msg *recv_msg;
  list *stop_mbox = NULL;
  list *stopdata_mbox = NULL;
  list *sync_mbox = NULL;
  list *decided_log = NULL;
  list *valid_timedout_msgs = NULL;
  stop_mbox = havoc(creg);
  stopdata_mbox = havoc(creg);
  sync_mbox = havoc(creg);
  if (timeout && (nreg == creg))
  {
    nreg = creg + 1;
    round = STOP;
    cancelTimers();
    msg *m = (msg *) malloc(sizeof(msg));
    m->round = STOP;
    m->reg = nreg;
    m->timedout_msgs = timedout_messages();
    send(all, m);
    stop_mbox = havoc(creg);
    stopdata_mbox = havoc(creg);
    sync_mbox = havoc(creg);
    if (timeout && (nreg == creg))
    {
      nreg = creg + 1;
      round = STOP;
      cancelTimers();
      msg *m = (msg *) malloc(sizeof(msg));
      m->round = STOP;
      m->reg = nreg;
      m->timedout_msgs = timedout_messages();
      send(all, m);
        stop_mbox = havoc(creg);
        stopdata_mbox = havoc(creg);
        sync_mbox = havoc(creg);

        if(timeout && nreg == creg){
            nreg = creg+1;
            round = STOP;

            cancelTimers();
            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOP;
            m->reg = nreg;
            m->timedout_msgs = timedout_messages();
            send(all,m);
            
            return 0; 
        }

        if(round == STOP && count_change_regency(stop_mbox, creg+1)>2*n/3 && nreg > creg){
            creg = nreg;
            round = STOPDATA;

            activateTimers();
            leader = creg % n;

            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOPDATA;
            m->reg = nreg;
            m->decided_log = decided_log;
            send(leader,m);

            return 0;
        }

    }

    if (((round == STOP) && (count_change_regency(stop_mbox, creg + 1) > ((2 * n) / 3))) && (nreg > creg))
    {
      creg = nreg;
      round = STOPDATA;
      activateTimers();
      leader = creg % n;
      msg *m = (msg *) malloc(sizeof(msg));
      m->round = STOPDATA;
      m->reg = nreg;
      m->decided_log = decided_log;
      send(leader, m);
        stop_mbox = havoc(creg);
        stopdata_mbox = havoc(creg);
        sync_mbox = havoc(creg);

        if(timeout && nreg == creg){
            nreg = creg+1;
            round = STOP;

            cancelTimers();
            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOP;
            m->reg = nreg;
            m->timedout_msgs = timedout_messages();
            send(all,m);
            
            return 0; 
        }

        if(count_change_regency(stop_mbox, creg+1)>n/3 && nreg == creg){
            
            nreg = creg+1;
            round = STOP;

            valid_timedout_msgs = valid_timedout_messages(stop_mbox);
            add_messages_to_order(valid_timedout_msgs);

            cancelTimers();
            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOP;
            m->reg = nreg;
            m->timedout_msgs = valid_timedout_msgs;
            send(all,m);

            return 0;
        }

        if(round == STOP && count_change_regency(stop_mbox, creg+1)>2*n/3 && nreg > creg){
            creg = nreg;
            round = STOPDATA;

            activateTimers();
            leader = creg % n;

            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOPDATA;
            m->reg = nreg;
            m->decided_log = decided_log;
            send(leader,m);

            return 0;
        }

        if(round == STOPDATA && (p == creg % n) && size(stopdata_mbox) > 2*n/3){

            round = SYNC;

            msg* m = (msg *) malloc(sizeof(msg));
            m->round = SYNC;
            m->reg = creg;
            m->proofs = stopdata_mbox;
            send(all,m);

            return 0;
        }

        if(round == STOPDATA && size(sync_mbox) == 1 && nreg == creg && from_leader(sync_mbox) && check_proofs()){
            back_to_normalop();
            round = STOP;
            return 0;
        }
    }

  }

  if ((count_change_regency(stop_mbox, creg + 1) > (n / 3)) && (nreg == creg))
  {
    nreg = creg + 1;
    round = STOP;
    valid_timedout_msgs = valid_timedout_messages(stop_mbox);
    add_messages_to_order(valid_timedout_msgs);
    cancelTimers();
    msg *m = (msg *) malloc(sizeof(msg));
    m->round = STOP;
    m->reg = nreg;
    m->timedout_msgs = valid_timedout_msgs;
    send(all, m);
    stop_mbox = havoc(creg);
    stopdata_mbox = havoc(creg);
    sync_mbox = havoc(creg);


    if (((round == STOP) && (count_change_regency(stop_mbox, creg + 1) > ((2 * n) / 3))) && (nreg > creg))
    {
      creg = nreg;
      round = STOPDATA;
      activateTimers();
      leader = creg % n;
      msg *m = (msg *) malloc(sizeof(msg));
      m->round = STOPDATA;
      m->reg = nreg;
      m->decided_log = decided_log;
      send(leader, m);
        stop_mbox = havoc(creg);
        stopdata_mbox = havoc(creg);
        sync_mbox = havoc(creg);

        if(timeout && nreg == creg){
            nreg = creg+1;
            round = STOP;

            cancelTimers();
            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOP;
            m->reg = nreg;
            m->timedout_msgs = timedout_messages();
            send(all,m);
            
            return 0; 
        }

        if(count_change_regency(stop_mbox, creg+1)>n/3 && nreg == creg){
            
            nreg = creg+1;
            round = STOP;

            valid_timedout_msgs = valid_timedout_messages(stop_mbox);
            add_messages_to_order(valid_timedout_msgs);

            cancelTimers();
            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOP;
            m->reg = nreg;
            m->timedout_msgs = valid_timedout_msgs;
            send(all,m);

            return 0;
        }

        if(round == STOP && count_change_regency(stop_mbox, creg+1)>2*n/3 && nreg > creg){
            creg = nreg;
            round = STOPDATA;

            activateTimers();
            leader = creg % n;

            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOPDATA;
            m->reg = nreg;
            m->decided_log = decided_log;
            send(leader,m);

            return 0;
        }

        if(round == STOPDATA && (p == creg % n) && size(stopdata_mbox) > 2*n/3){

            round = SYNC;

            msg* m = (msg *) malloc(sizeof(msg));
            m->round = SYNC;
            m->reg = creg;
            m->proofs = stopdata_mbox;
            send(all,m);

            return 0;
        }

        if(round == STOPDATA && size(sync_mbox) == 1 && nreg == creg && from_leader(sync_mbox) && check_proofs()){
            back_to_normalop();
            round = STOP;
            return 0;
        }
    }

  }

  if (((round == STOP) && (count_change_regency(stop_mbox, creg + 1) > ((2 * n) / 3))) && (nreg > creg))
  {
    creg = nreg;
    round = STOPDATA;
    activateTimers();
    leader = creg % n;
    msg *m = (msg *) malloc(sizeof(msg));
    m->round = STOPDATA;
    m->reg = nreg;
    m->decided_log = decided_log;
    send(leader, m);

    stop_mbox = havoc(creg);
    stopdata_mbox = havoc(creg);
    sync_mbox = havoc(creg);
    if (timeout && (nreg == creg))
    {
      nreg = creg + 1;
      round = STOP;
      cancelTimers();
      msg *m = (msg *) malloc(sizeof(msg));
      m->round = STOP;
      m->reg = nreg;
      m->timedout_msgs = timedout_messages();
      send(all, m);
        stop_mbox = havoc(creg);
        stopdata_mbox = havoc(creg);
        sync_mbox = havoc(creg);

        if(timeout && nreg == creg){
            nreg = creg+1;
            round = STOP;

            cancelTimers();
            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOP;
            m->reg = nreg;
            m->timedout_msgs = timedout_messages();
            send(all,m);
            
            return 0; 
        }

        if(count_change_regency(stop_mbox, creg+1)>n/3 && nreg == creg){
            
            nreg = creg+1;
            round = STOP;

            valid_timedout_msgs = valid_timedout_messages(stop_mbox);
            add_messages_to_order(valid_timedout_msgs);

            cancelTimers();
            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOP;
            m->reg = nreg;
            m->timedout_msgs = valid_timedout_msgs;
            send(all,m);

            return 0;
        }

        if(round == STOP && count_change_regency(stop_mbox, creg+1)>2*n/3 && nreg > creg){
            creg = nreg;
            round = STOPDATA;

            activateTimers();
            leader = creg % n;

            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOPDATA;
            m->reg = nreg;
            m->decided_log = decided_log;
            send(leader,m);

            return 0;
        }

        if(round == STOPDATA && (p == creg % n) && size(stopdata_mbox) > 2*n/3){

            round = SYNC;

            msg* m = (msg *) malloc(sizeof(msg));
            m->round = SYNC;
            m->reg = creg;
            m->proofs = stopdata_mbox;
            send(all,m);

            return 0;
        }

        if(round == STOPDATA && size(sync_mbox) == 1 && nreg == creg && from_leader(sync_mbox) && check_proofs()){
            back_to_normalop();
            round = STOP;
            return 0;
        }
    }

    if ((count_change_regency(stop_mbox, creg + 1) > (n / 3)) && (nreg == creg))
    {
      nreg = creg + 1;
      round = STOP;
      valid_timedout_msgs = valid_timedout_messages(stop_mbox);
      add_messages_to_order(valid_timedout_msgs);
      cancelTimers();
      msg *m = (msg *) malloc(sizeof(msg));
      m->round = STOP;
      m->reg = nreg;
      m->timedout_msgs = valid_timedout_msgs;
      send(all, m);
        stop_mbox = havoc(creg);
        stopdata_mbox = havoc(creg);
        sync_mbox = havoc(creg);

        if(timeout && nreg == creg){
            nreg = creg+1;
            round = STOP;

            cancelTimers();
            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOP;
            m->reg = nreg;
            m->timedout_msgs = timedout_messages();
            send(all,m);
            
            return 0; 
        }

        if(count_change_regency(stop_mbox, creg+1)>n/3 && nreg == creg){
            
            nreg = creg+1;
            round = STOP;

            valid_timedout_msgs = valid_timedout_messages(stop_mbox);
            add_messages_to_order(valid_timedout_msgs);

            cancelTimers();
            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOP;
            m->reg = nreg;
            m->timedout_msgs = valid_timedout_msgs;
            send(all,m);

            return 0;
        }

        if(round == STOP && count_change_regency(stop_mbox, creg+1)>2*n/3 && nreg > creg){
            creg = nreg;
            round = STOPDATA;

            activateTimers();
            leader = creg % n;

            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOPDATA;
            m->reg = nreg;
            m->decided_log = decided_log;
            send(leader,m);

            return 0;
        }

        if(round == STOPDATA && (p == creg % n) && size(stopdata_mbox) > 2*n/3){

            round = SYNC;

            msg* m = (msg *) malloc(sizeof(msg));
            m->round = SYNC;
            m->reg = creg;
            m->proofs = stopdata_mbox;
            send(all,m);

            return 0;
        }

        if(round == STOPDATA && size(sync_mbox) == 1 && nreg == creg && from_leader(sync_mbox) && check_proofs()){
            back_to_normalop();
            round = STOP;
            return 0;
        }
    }

    if (((round == STOPDATA) && (p == (creg % n))) && (size(stopdata_mbox) > ((2 * n) / 3)))
    {
      round = SYNC;
      msg *m = (msg *) malloc(sizeof(msg));
      m->round = SYNC;
      m->reg = creg;
      m->proofs = stopdata_mbox;
      send(all, m);
        stop_mbox = havoc(creg);
        stopdata_mbox = havoc(creg);
        sync_mbox = havoc(creg);

        if(timeout && nreg == creg){
            nreg = creg+1;
            round = STOP;

            cancelTimers();
            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOP;
            m->reg = nreg;
            m->timedout_msgs = timedout_messages();
            send(all,m);
            
            return 0; 
        }

        if(count_change_regency(stop_mbox, creg+1)>n/3 && nreg == creg){
            
            nreg = creg+1;
            round = STOP;

            valid_timedout_msgs = valid_timedout_messages(stop_mbox);
            add_messages_to_order(valid_timedout_msgs);

            cancelTimers();
            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOP;
            m->reg = nreg;
            m->timedout_msgs = valid_timedout_msgs;
            send(all,m);

            return 0;
        }

        if(round == STOP && count_change_regency(stop_mbox, creg+1)>2*n/3 && nreg > creg){
            creg = nreg;
            round = STOPDATA;

            activateTimers();
            leader = creg % n;

            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOPDATA;
            m->reg = nreg;
            m->decided_log = decided_log;
            send(leader,m);

            return 0;
        }

        if(round == STOPDATA && (p == creg % n) && size(stopdata_mbox) > 2*n/3){

            round = SYNC;

            msg* m = (msg *) malloc(sizeof(msg));
            m->round = SYNC;
            m->reg = creg;
            m->proofs = stopdata_mbox;
            send(all,m);

            return 0;
        }

        if(round == STOPDATA && size(sync_mbox) == 1 && nreg == creg && from_leader(sync_mbox) && check_proofs()){
            back_to_normalop();
            round = STOP;
            return 0;
        }
    }

    if ((((round == STOPDATA) && (size(sync_mbox) == 1)) && (nreg == creg)) && from_leader(sync_mbox))
    {
      if (check_proofs())
      {
        back_to_normalop();
        round = STOP;
      }

    }

  }

  if (((round == STOPDATA) && (p == (creg % n))) && (size(stopdata_mbox) > ((2 * n) / 3)))
  {
    round = SYNC;
    msg *m = (msg *) malloc(sizeof(msg));
    m->round = SYNC;
    m->reg = creg;
    m->proofs = stopdata_mbox;
    send(all, m);
    stop_mbox = havoc(creg);
    stopdata_mbox = havoc(creg);
    sync_mbox = havoc(creg);
    if (timeout && (nreg == creg))
    {
      nreg = creg + 1;
      round = STOP;
      cancelTimers();
      msg *m = (msg *) malloc(sizeof(msg));
      m->round = STOP;
      m->reg = nreg;
      m->timedout_msgs = timedout_messages();
      send(all, m);
        stop_mbox = havoc(creg);
        stopdata_mbox = havoc(creg);
        sync_mbox = havoc(creg);

        if(timeout && nreg == creg){
            nreg = creg+1;
            round = STOP;

            cancelTimers();
            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOP;
            m->reg = nreg;
            m->timedout_msgs = timedout_messages();
            send(all,m);
            
            return 0; 
        }

        if(count_change_regency(stop_mbox, creg+1)>n/3 && nreg == creg){
            
            nreg = creg+1;
            round = STOP;

            valid_timedout_msgs = valid_timedout_messages(stop_mbox);
            add_messages_to_order(valid_timedout_msgs);

            cancelTimers();
            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOP;
            m->reg = nreg;
            m->timedout_msgs = valid_timedout_msgs;
            send(all,m);

            return 0;
        }

        if(round == STOP && count_change_regency(stop_mbox, creg+1)>2*n/3 && nreg > creg){
            creg = nreg;
            round = STOPDATA;

            activateTimers();
            leader = creg % n;

            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOPDATA;
            m->reg = nreg;
            m->decided_log = decided_log;
            send(leader,m);

            return 0;
        }

        if(round == STOPDATA && (p == creg % n) && size(stopdata_mbox) > 2*n/3){

            round = SYNC;

            msg* m = (msg *) malloc(sizeof(msg));
            m->round = SYNC;
            m->reg = creg;
            m->proofs = stopdata_mbox;
            send(all,m);

            return 0;
        }

        if(round == STOPDATA && size(sync_mbox) == 1 && nreg == creg && from_leader(sync_mbox) && check_proofs()){
            back_to_normalop();
            round = STOP;
            return 0;
        }
    }

    if ((count_change_regency(stop_mbox, creg + 1) > (n / 3)) && (nreg == creg))
    {
      nreg = creg + 1;
      round = STOP;
      valid_timedout_msgs = valid_timedout_messages(stop_mbox);
      add_messages_to_order(valid_timedout_msgs);
      cancelTimers();
      msg *m = (msg *) malloc(sizeof(msg));
      m->round = STOP;
      m->reg = nreg;
      m->timedout_msgs = valid_timedout_msgs;
      send(all, m);
        stop_mbox = havoc(creg);
        stopdata_mbox = havoc(creg);
        sync_mbox = havoc(creg);

        if(timeout && nreg == creg){
            nreg = creg+1;
            round = STOP;

            cancelTimers();
            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOP;
            m->reg = nreg;
            m->timedout_msgs = timedout_messages();
            send(all,m);
            
            return 0; 
        }

        if(count_change_regency(stop_mbox, creg+1)>n/3 && nreg == creg){
            
            nreg = creg+1;
            round = STOP;

            valid_timedout_msgs = valid_timedout_messages(stop_mbox);
            add_messages_to_order(valid_timedout_msgs);

            cancelTimers();
            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOP;
            m->reg = nreg;
            m->timedout_msgs = valid_timedout_msgs;
            send(all,m);

            return 0;
        }

        if(round == STOP && count_change_regency(stop_mbox, creg+1)>2*n/3 && nreg > creg){
            creg = nreg;
            round = STOPDATA;

            activateTimers();
            leader = creg % n;

            msg* m = (msg *) malloc(sizeof(msg));
            m->round = STOPDATA;
            m->reg = nreg;
            m->decided_log = decided_log;
            send(leader,m);

            return 0;
        }

        if(round == STOPDATA && (p == creg % n) && size(stopdata_mbox) > 2*n/3){

            round = SYNC;

            msg* m = (msg *) malloc(sizeof(msg));
            m->round = SYNC;
            m->reg = creg;
            m->proofs = stopdata_mbox;
            send(all,m);

            return 0;
        }

        if(round == STOPDATA && size(sync_mbox) == 1 && nreg == creg && from_leader(sync_mbox) && check_proofs()){
            back_to_normalop();
            round = STOP;
            return 0;
        }
    }

  }

  if (((((round == STOPDATA) && (size(sync_mbox) == 1)) && (nreg == creg)) && from_leader(sync_mbox)) && check_proofs())
  {
    back_to_normalop();
    round = STOP;

  }

}


