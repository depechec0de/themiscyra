struct msg
{
  int phase;
  enum round_type round;  
  int replica;
  struct log* log;
  int last;
};
struct list
{
  struct msg *message;
  struct list *next;
  int size;
};

struct log
{
  int command;
  struct log *next;
  int size;
};

enum round_type {PREPARE, ACK, PROPOSE, PROMISE};

_Bool send(int addr, struct msg * m);
struct list* havoc(int view, enum round_type vround);
int primary(int view, int n);
struct msg* message(int phase, enum round_type round, int sender, struct log* log, int last);
int count(int phase, enum round_type round, struct list* mbox);
_Bool all_followers_commit(int phase, enum round_type round, struct list* mbox);
_Bool primary_commit(int phase, enum round_type round, struct list* mbox);
int null_int();
int command();
_Bool commit_or_abort();
_Bool null_bool();
_Bool execute_command();

struct log* null_log();
_Bool add_msg(struct msg * m, struct list* mbox);
_Bool recv(int phase, enum round_type round);

int main()
{
    int p;
    int n;
    int all;
    int phase;
    enum round_type round;

    struct msg* m;
    struct msg* recv_msg;

    struct list* mbox;
    
    phase = 0;
    round = PREPARE;
    
    while(1){

        if(round == PREPARE && p==primary(phase,n)){
            send( all, message(phase+1, PREPARE, p, null_log(), null_int()) ); 
            round = BETA;
            continue;
        }

        if(round == ALPHA && p!=primary(phase,n) && count(phase, ALPHA, mbox) == 1){
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase,n), message(phase, BETA, p, null_int(), commit, null_bool())); 
            round = GAMMA;
            continue;
        }  

        if(round == BETA && p==primary(phase,n) && count(phase, BETA, mbox) == n){
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool())); 
            round = DELTA;
            continue;
        } 

        if(round == GAMMA && p!=primary(phase,n) && count(phase, GAMMA, mbox) == 1){
            commit = primary_commit(phase, GAMMA, mbox);
            if(commit){
                execute_command();
            }
            round = DELTA;
            send(primary(phase,n), message(phase, DELTA, p, null_int(), null_bool(), true)); 
            phase++;
            round = ALPHA;
            continue;
        }

        if(round == DELTA && p==primary(phase,n) && count(phase, DELTA, mbox) == n){
            phase++;
            round = ALPHA;
            continue;
        }
        
    }

}
