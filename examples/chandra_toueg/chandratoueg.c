struct msg {
    enum round_typ round;
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
_Bool leader(int phase);
int leaderid(int phase);
// mbox query functions

struct list* havoc(int phase, enum round_typ round);
struct list* query(struct list* mbox, int phase, enum round_typ round );
int max_phase_recv(struct list* mbox);
_Bool timeout(enum round_typ round);
struct msg* message(int phase, enum round_typ round, int estimate, int p, int timestamp, _Bool decided);
// value_decided(p) := false until decide(estimate) is called
_Bool value_decided(int p);
// Inform the client of a decision, value_decided(p) := true
_Bool decide(int estimate);
// Look into the mbox for a phase >= `current_phase` with at least `size_to_count` messages in round `round`
int phase_matching(struct list * mbox, int current_phase, enum round_typ round, int size_to_count);

int phase_matching(struct list * mbox, int current_phase, enum round_typ round, int size_to_count){
    for(int i = current_phase; i <= max_phase_recv(mbox); i++){ 
        if(query(mbox, i, round) >= size_to_count){
            return i;
        } 
    }
    return 0;
}

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

        if(!value_decided(p) && round == FIRST_ROUND)
        {
            send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase)); 
            round = SECOND_ROUND;

            continue;
        }

        
        if  (leader(phase) && phase_matching(mbox, phase, FIRST_ROUND, (n-1)/2) >= phase && !value_decided(phase))
        {
            if(phase_matching(mbox, phase, FIRST_ROUND, (n-1)/2) > phase)
            {
                phase = phase_matching(mbox, phase, FIRST_ROUND, (n-1)/2);
                round = FIRST_ROUND;
            }
            
            m = max_timestamp(mbox);
            estimate = m->estimate;
            
            round = SECOND_ROUND;
            send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all); 
            round = THIRD_ROUND;

            continue;
        }

        if  (!leader(phase) && phase_matching(mbox, phase, SECOND_ROUND, 1) >= phase && !value_decided(phase))
        {
            if(phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
            {
                phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
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

        if  (leader(phase) && phase_matching(mbox, phase, THIRD_ROUND, (n-1)/2) >= phase)
        {     
            if(phase_matching(mbox, phase, THIRD_ROUND, (n-1)/2) > phase)
            {
                phase = phase_matching(mbox, phase, THIRD_ROUND, (n-1)/2);
                round = THIRD_ROUND;
            }

            decide(estimate);

            round = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
            
            phase++;
            round = FIRST_ROUND;
            continue;

        }

        if  (!leader(phase) && phase_matching(mbox, phase, FOURTH_ROUND, 1) >= phase && !value_decided(phase))
        {
            if(phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
            {
                phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
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

        if(leader(phase) && value_decided(p))
        {
            round = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
            phase++;
            round = FIRST_ROUND;

            continue;
        }

        if(!value_decided(p) && timeout(round))
        {
            phase++;
            round = FIRST_ROUND;

            continue;
        } 

    }

}
