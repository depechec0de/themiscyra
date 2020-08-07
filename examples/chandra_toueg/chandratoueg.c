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
  int phase;
  int size;
};

enum round_typ {FIRST_ROUND, SECOND_ROUND, THIRD_ROUND, FOURTH_ROUND};

int null_int();
_Bool null_bool();
int in();
struct msg* max_timestamp(struct list* mbox);
_Bool all_ack(struct list* mbox);
_Bool send(struct msg *message, int pid);
_Bool leader(int phase);
int leaderid(int phase);
// mbox query functions
int count(struct list* mbox, enum round_typ round);
// havoc returns when an upon condition is met
struct list* havoc(int phase, enum round_typ round);
_Bool timeout(enum round_typ round);
struct msg* message(int phase, enum round_typ round, int estimate, int p, int timestamp, _Bool decided);
// value_decided(p) := false until decide(estimate) is called
_Bool value_decided(int p);
// Inform the client of a decision, value_decided(p) := true
_Bool decide(int estimate);

int main()
{
    int p;
    int n;
    int f = (n-1)/2;
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

        if(!value_decided(p) && !leader(phase) && round == FIRST_ROUND){
            
            send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase)); 
            round = SECOND_ROUND;

            continue;
        }

        if(count(mbox, FIRST_ROUND) > f && !value_decided(p) && (mbox->phase > phase && leader(mbox->phase) || round == FIRST_ROUND && leader(phase))){

            if(mbox->phase > phase){
                phase = mbox->phase;
                round = FIRST_ROUND;
            }
            
            m = max_timestamp(mbox);
            estimate = m->estimate;
            
            round = SECOND_ROUND;
            send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all); 
            round = THIRD_ROUND;

            continue;
        }

        if(count(mbox, THIRD_ROUND) > f && !value_decided(p) && (mbox->phase > phase && leader(mbox->phase) || round == THIRD_ROUND && leader(phase))){

            if(mbox->phase > phase){
                phase = mbox->phase;
                round = THIRD_ROUND;
            }           
            
            if(all_ack(mbox)){
                round = FOURTH_ROUND;
                send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
                decide(estimate);
            }

            phase++;
            round = FIRST_ROUND;
            continue;

        }

        if(count(mbox, SECOND_ROUND) == 1 && !value_decided(p) && (mbox->phase > phase && !leader(mbox->phase) || round == SECOND_ROUND && !leader(phase))){

            if(mbox->phase > phase){
                phase = mbox->phase;
                round = SECOND_ROUND;
            }
            
            m = mbox->message;
            estimate = m->estimate;
            timestamp = phase;

            round = THIRD_ROUND;
            send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase)); 
            round = FOURTH_ROUND;
            
            continue;
        }  

        if(count(mbox, FOURTH_ROUND) == 1 && !value_decided(p) && (mbox->phase > phase && !leader(mbox->phase) || round == FOURTH_ROUND && !leader(phase))){

            if(mbox->phase > phase){
                phase = mbox->phase;
                round = FOURTH_ROUND;
            }

            if(mbox->message->decided){
                estimate = m->estimate;
                decide(estimate);
            }

            phase++;
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
        if(value_decided(p) && leader(phase)){
            
            round = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
            phase++;
            round = FIRST_ROUND;

            continue;
        }

    }

}
