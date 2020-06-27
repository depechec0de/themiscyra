typedef struct Msg {
    int round;
    int phase;
    int estimate;
    int timestamp;
    int response;
    int sender;
    _Bool decided;
} msg;
typedef struct List
{
  msg *message;
  struct List *next;
  int size;
} list;

enum round_typ {FIRST_ROUND, SECOND_ROUND, THIRD_ROUND, FOURTH_ROUND};
enum ack_typ {ACK, NACK};

msg * recv();

void out(int v1, int v2);

int in();

int timeout();

int reset_timeout();

int rand_bool();

msg* max_timestamp(struct List* mbox);

int all_ack(struct List* mbox);

void dispose(msg *c);

void list_dispose(struct List *l);

void send(msg *message, int pid);

int leader(int phase, int net_size);

int all_agree(struct List *l);

msg* message(int phase, enum round_typ round, int estimate, int p, int timestamp, int response, _Bool decided);

int true = 1;

int main(int p, int n, int f)
{
    
    int timestamp;
    int phase;
    enum round_typ round;
    int ack;
    int to_all = n+1;
    int estimate;
    int state;
    
    list *mbox = NULL;
    list* mbox_new = NULL;
    msg* m = NULL;

    phase = 1;
    round = FIRST_ROUND;
    estimate = in();
    state = 0;
    timestamp = 0;

    send(message(phase, FIRST_ROUND, estimate, p, timestamp, NULL, NULL), leader(phase,n)); 

    while(1){

        mbox = havoc();

        if(p != leader(phase,n) && round == FIRST_ROUND){
            round = SECOND_ROUND;
            continue;
        }

        if(p == leader(phase,n) && round == FIRST_ROUND && count(mbox, FIRST_ROUND, phase) > (n+1)/2 && count(mbox, FOURTH_ROUND) == 0){
            
            m = max_timestamp(mbox);
            estimate = m->estimate;

            round = SECOND_ROUND;
            send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all); 
            continue;
        }

        if(round == SECOND_ROUND && failure_detector(leader(phase,n)) == 1){
            round = THIRD_ROUND;
            send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase,n));

            phase++;
            round = FIRST_ROUND;
            continue;
        } 

        if(round == SECOND_ROUND && count(mbox, SECOND_ROUND, phase, leader(phase,n)) > 0 && count(mbox, FOURTH_ROUND) == 0){
            
            estimate = mbox->message->estimate;
            timestamp = phase;
            ack = 1;

            round = THIRD_ROUND;
            send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase,n)); 

            if(p != leader(phase,n)){
                round = FOURTH_ROUND;
            }
            
            continue;
        }  
        
        if(p == leader(phase,n) && round == THIRD_ROUND && count(mbox, THIRD_ROUND, phase) > (n+1)/2 && count(mbox, FOURTH_ROUND) == 0){
            
            if(all_ack(mbox) == 1){ 
                round = FOURTH_ROUND;
                send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
            }

            phase++;
            round = FIRST_ROUND;
        
            continue;
        } 

        if(count(mbox, FOURTH_ROUND) > 0){
            
            round = FOURTH_ROUND;
            
            if(mbox->message->decided){
                estimate = mbox->message->estimate;
                out(p, estimate);
            }

            phase++;
            round = FIRST_ROUND;

            continue;
        } 
        
        
    }

}
