struct msg {
    int round;
    int phase;
    int estimate;
    int timestamp;
    _Bool ack;
    int sender;
    _Bool decided;
};
struct list
{
  struct msg* message;
  struct list* next;
  int size;
};

enum round_typ {FIRST_ROUND, SECOND_ROUND, THIRD_ROUND, FOURTH_ROUND};
enum null {BOOL_NULL, INT_NULL};

int out(int v1, int v2);
int in();
struct msg* max_timestamp(struct list* mbox);
_Bool all_ack(struct list* mbox);
_Bool send(struct msg *message, int pid);
int leader(int phase, int net_size);
int count(struct list* mbox, int phase, enum round_typ round, int from);
struct list* havoc();
_Bool timeout(enum round_typ round);
struct msg* message(int phase, enum round_typ round, int estimate, int p, int timestamp, _Bool decided);

int main()
{
    int p;
    int n;
    int timestamp;
    int phase;
    enum round_typ round;
    int to_all = n+1;
    int estimate;
    _Bool decided;
    
    struct list* mbox;
    struct msg* m;

    decided = false;
    phase = 1;
    round = FIRST_ROUND;
    estimate = in();
    timestamp = 0;

    while(1){

        mbox = havoc();

        if(p != leader(phase,n) && round == FIRST_ROUND){
            send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase,n)); 
            round = SECOND_ROUND;

            continue;
        }

        if(p == leader(phase,n) && round == FIRST_ROUND && count(mbox, phase, FIRST_ROUND, INT_NULL) > (n+1)/2 && count(mbox, INT_NULL, FOURTH_ROUND, INT_NULL) == 0){
            m = max_timestamp(mbox);
            estimate = m->estimate;

            round = SECOND_ROUND;
            send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all); 
            round = THIRD_ROUND;

            continue;
        }

        if(p == leader(phase,n) && round == FIRST_ROUND && timeout(round)){
            
            round = FIRST_ROUND;
            phase++;

            continue;
        } 

        if(p != leader(phase,n) && round == SECOND_ROUND && timeout(round)){
            
            round = FIRST_ROUND;
            phase++;

            continue;
        } 

        if(p != leader(phase,n) && round == SECOND_ROUND && count(mbox, phase, SECOND_ROUND, leader(phase,n)) > 0 && count(mbox, INT_NULL, FOURTH_ROUND, INT_NULL) == 0){
            
            round = THIRD_ROUND;
            m = mbox->message;
            estimate = m->estimate;
            timestamp = phase;
            send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase,n)); 
            round = FOURTH_ROUND;
            
            continue;
        }  
        
        if(p == leader(phase,n) && round == THIRD_ROUND && count(mbox, phase, THIRD_ROUND, INT_NULL) > (n+1)/2 && count(mbox, INT_NULL, FOURTH_ROUND, INT_NULL) == 0){
            
            if(all_ack(mbox)){ 
                // the value is installed in a majority
                round = FOURTH_ROUND;
                send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
                decided = true;
            }else{
                round = FIRST_ROUND;
                phase++;
            }
        
            continue;
        } 

        // timeouted without a majority of ACKs, we try again in a new phase
        if(p == leader(phase,n) && round == THIRD_ROUND && timeout(round)){

            round = FIRST_ROUND;
            phase++;

            continue;
        }

        if(p != leader(phase,n) && count(mbox, INT_NULL, FOURTH_ROUND, INT_NULL) == 1){
            
            m = mbox->message;

            if(m->decided && m->phase >= phase){
                round = FOURTH_ROUND;
                estimate = m->estimate;
                decided = true;
                out(p, estimate);
                phase++;
            }

            continue;
        } 

        if(p != leader(phase,n) && round == FOURTH_ROUND && decided == false && timeout(round)){
            
            round = FIRST_ROUND;
            phase++;

            continue;
        }

        // A majority was achieved somewhere in the past and I am the leader of the phase 
        // => broadcast the decision
        if(p == leader(phase,n) && round == FOURTH_ROUND && decided){

            send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
            phase++;

            continue;
        }
        
        
    }

}
