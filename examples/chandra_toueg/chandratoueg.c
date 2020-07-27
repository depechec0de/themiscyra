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

int null_int();
_Bool null_bool();
int in();
struct msg* max_timestamp(struct list* mbox);
_Bool all_ack(struct list* mbox);
_Bool send(struct msg *message, int pid);
int leader(int phase, int net_size);
int count(struct list* mbox, int phase, enum round_typ round, int from);
struct list *havoc(int phase, enum round_typ round);
_Bool timeout(enum round_typ round);
struct msg* message(int phase, enum round_typ round, int estimate, int p, int timestamp, _Bool decided);
// In the first execution returns false, upon decide(estimate) is executed it will always returns true
_Bool value_decided(int p);
// Inform the client of a decision
_Bool decide(int estimate);

int main()
{
    int p;
    int n;
    int timestamp;
    int phase;
    enum round_typ round;
    int to_all = n+1;
    int estimate;
    
    struct list* mbox;
    struct msg* m;

    phase = 1;
    round = FIRST_ROUND;
    estimate = in();
    timestamp = 0;

    while(1){

        mbox = havoc(phase, round);

        if(!value_decided(p) && p == leader(phase,n) && round == FIRST_ROUND && count(mbox, phase, FIRST_ROUND, null_int()) > (n+1)/2 && count(mbox, null_int(), FOURTH_ROUND, null_int()) == 0){
            m = max_timestamp(mbox);
            estimate = m->estimate;

            round = SECOND_ROUND;
            send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all); 
            round = THIRD_ROUND;

            continue;
        }

        if(!value_decided(p) && p == leader(phase,n) && round == THIRD_ROUND && count(mbox, phase, THIRD_ROUND, null_int()) > (n+1)/2 && count(mbox, null_int(), FOURTH_ROUND, null_int()) == 0 && all_ack(mbox)){
            
            round = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
            decide(estimate);

            phase++;
            round = FIRST_ROUND;
            continue;

        }
        
        if(!value_decided(p) && p == leader(phase,n) && round == THIRD_ROUND && count(mbox, phase, THIRD_ROUND, null_int()) > (n+1)/2 && count(mbox, null_int(), FOURTH_ROUND, null_int()) == 0 && !all_ack(mbox)){
            phase++;
            round = FIRST_ROUND;
            continue;
        }

        if(!value_decided(p) && p != leader(phase,n) && round == FIRST_ROUND){
            send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase,n)); 
            round = SECOND_ROUND;

            continue;
        }

        if(!value_decided(p) && p != leader(phase,n) && round == SECOND_ROUND && count(mbox, phase, SECOND_ROUND, leader(phase,n)) > 0 && count(mbox, null_int(), FOURTH_ROUND, null_int()) == 0){
            
            m = mbox->message;
            estimate = m->estimate;
            timestamp = phase;
            round = THIRD_ROUND;
            send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase,n)); 
            round = FOURTH_ROUND;
            
            continue;
        }  

        if(!value_decided(p) && p != leader(phase,n) && round == FOURTH_ROUND && count(mbox, phase, FOURTH_ROUND, leader(phase,n)) == 1 && mbox->message->decided){
    
            estimate = m->estimate;
            // from now on value_decided(p) -> true
            decide(estimate);

            phase++;
            round = FIRST_ROUND;
            continue;
        }

        // Jump to a decision
        if(!value_decided(p) && p != leader(phase,n) && count(mbox, null_int(), FOURTH_ROUND, leader(phase,n)) == 1 && mbox->message->decided && mbox->message->phase > phase){

            round = FOURTH_ROUND;
            
            estimate = m->estimate;
            // from now on value_decided(p) -> true
            decide(estimate);

            phase = mbox->message->phase + 1;
            round = FIRST_ROUND;
            
            continue;
        }

        if(!value_decided(p) && timeout(round)){
            
            phase++;
            round = FIRST_ROUND;

            continue;
        } 

        // A majority was achieved somewhere in the past and I am the leader of the phase 
        // => broadcast the decision
        if(value_decided(p) && p == leader(phase,n)){
            
            round = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
            phase++;
            round = FIRST_ROUND;

            continue;
        }
    }

}
