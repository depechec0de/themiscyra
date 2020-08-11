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

struct timestamp
{
  int phase;
  enum round_typ round;
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
int count(struct list* l);
struct list* havoc(int phase, enum round_typ round);
struct list* query(struct list* mbox, int phase, enum round_typ round );
int max_phase_recv(struct list* mbox);
_Bool timeout(enum round_typ round);
struct msg* message(int phase, enum round_typ round, int estimate, int p, int timestamp, _Bool decided);
// value_decided(p) := false until decide(estimate) is called
_Bool value_decided(int p);
// Inform the client of a decision, value_decided(p) := true
_Bool decide(int estimate);

_Bool leader_recv_all_estimates(struct list* mbox, int phase, int n){
    return count(query(mbox, phase, FIRST_ROUND)) > (n-1)/2 && leader(phase) && !value_decided(phase);
}

_Bool leader_recv_all_acks(struct list* mbox, int phase, int n){
    return count(query(mbox, phase, THIRD_ROUND)) > (n-1)/2 && leader(phase) && !value_decided(phase);
}

_Bool follower_recv_estimate(struct list* mbox, int phase){
    return count(query(mbox, phase, SECOND_ROUND)) == 1 && !leader(phase) && !value_decided(phase);
}

_Bool follower_recv_desicion(struct list* mbox, int phase){
    return count(query(mbox, phase, FOURTH_ROUND)) == 1 && !leader(phase) && !value_decided(phase);
}

struct timestamp jump_to(struct list* mbox, int current_phase, enum round_typ current_round, int n){

    int max_phase = max_phase_recv(mbox);
    int new_phase = current_phase;
    enum round_typ new_round = current_round;
        
    for(int i=max_phase; i>current_phase; i--){
        // leader jump to end of first round
        if(leader_recv_all_estimates(mbox, i, n)){
            new_phase = i;
            new_round = FIRST_ROUND;
            break;
        }

        if(follower_recv_estimate(mbox, i)){
            new_phase = i;
            new_round = SECOND_ROUND;
            break;
        }

        if(leader_recv_all_acks(mbox, i, n)){
            new_phase = i;
            new_round = THIRD_ROUND;
            break;
        }

        if(follower_recv_desicion(mbox, i)){
            new_phase = i;
            new_round = FOURTH_ROUND;
            break;
        }

    }

    struct timestamp ts = { .phase = new_phase, .round = new_round};

    return ts;

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
    struct timestamp current_ts;

    phase = 1;
    round = FIRST_ROUND;
    estimate = in();
    timestamp = 0;
    
    while(1){

        mbox = havoc(phase, round);
        current_ts = jump_to(mbox, phase, round, n);
        phase = current_ts.phase;
        round = current_ts.round;

        if(!value_decided(p) && !leader(phase) && round == FIRST_ROUND){
            
            send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase)); 
            round = SECOND_ROUND;

            continue;
        }

        if(leader_recv_all_estimates(mbox, phase, n) && round == FIRST_ROUND){
            
            m = max_timestamp(mbox);
            estimate = m->estimate;
            
            round = SECOND_ROUND;
            send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all); 
            round = THIRD_ROUND;

            continue;
        }

        if(follower_recv_estimate(mbox, phase) && round == SECOND_ROUND){
            
            m = mbox->message;
            estimate = m->estimate;
            timestamp = phase;

            round = THIRD_ROUND;
            send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase)); 
            round = FOURTH_ROUND;
            
            continue;
        }  

        if(leader_recv_all_acks(mbox, phase, n) && round == THIRD_ROUND){     
            
            round = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
            decide(estimate);
            
            phase++;
            round = FIRST_ROUND;
            continue;

        }

        if(follower_recv_desicion(mbox, phase) && round == FOURTH_ROUND){

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

        if(value_decided(p) && leader(phase)){
            
            round = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
            phase++;
            round = FIRST_ROUND;

            continue;
        }

    }

}
