FIRST_ROUND
    SEND:
        if(!value_decided(p)){
            send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase,n)); 
        }
    UPDATE:
        if(!value_decided(p) && p == leader(phase,n) && count(mbox, phase, FIRST_ROUND, null_int()) > (n+1)/2){
            m = max_timestamp(mbox);
            estimate = m->estimate;
        }

SECOND_ROUND
    SEND:
        if(!value_decided(p) && p == leader(phase,n){
            send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all); 
        }

    UPDATE:
        if(!value_decided(p) && p != leader(phase,n) && count(mbox, phase, SECOND_ROUND, leader(phase,n)) == 1){
            m = mbox->message;
            estimate = m->estimate;
            timestamp = phase;
        }

THIRD_ROUND
    SEND:
        if(!value_decided(p) && p != leader(phase,n)){
            send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase,n)); 
        }

    UPDATE:
        if(!value_decided(p) && p == leader(phase,n) && count(mbox, phase, THIRD_ROUND, null_int()) > (n+1)/2 && all_ack(mbox)){
            decide(estimate);
        }

FOURTH_ROUND
    SEND:
        if((value_decided(p) || jump_to_decision) && p == leader(phase,n)){
            send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        }
    UPDATE:
        if(jump_to_decision || (p != leader(phase,n) && count(mbox, phase, FOURTH_ROUND, leader(phase,n)) == 1 && mbox->message->decided)){
            estimate = m->estimate;
            decide(estimate);
        }