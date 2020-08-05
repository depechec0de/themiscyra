INIT
    jump_to_decision = i_should_jump();

FIRST_ROUND
    SEND:
        if(!jump_to_decision){
            if(!value_decided(p)){
                send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase,n)); 
            }
        }
    UPDATE:
        jump_to_decision1 = i_should_jump();
        jump_to_decision = jump_to_decision1;
        if(!jump_to_decision){
            condition1 = !value_decided(p) && p == leader(phase,n) && count(mbox, phase, FIRST_ROUND, null_int()) > (n+1)/2;
            if(!value_decided(p) && p == leader(phase,n) && count(mbox, phase, FIRST_ROUND, null_int()) > (n+1)/2){
                round = SECOND_ROUND;
                m = max_timestamp(mbox);
                estimate = m->estimate;
            }
        }

SECOND_ROUND
    SEND:
        if(!jump_to_decision){
            if(!value_decided(p) && p == leader(phase,n) && condition1){
                send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all); 
            }
        }

    UPDATE:
        jump_to_decision2 = i_should_jump();
        jump_to_decision = jump_to_decision1 || jump_to_decision2;
        if(!jump_to_decision){
            condition2 = !value_decided(p) && p != leader(phase,n) && count(mbox, phase, SECOND_ROUND, leader(phase,n)) == 1;
            // adding condition1 would contradict p != leader(phase,n)
            if(!value_decided(p) && p != leader(phase,n) && count(mbox, phase, SECOND_ROUND, leader(phase,n)) == 1){
                m = mbox->message;
                estimate = m->estimate;
                timestamp = phase;
            }
        }

THIRD_ROUND
    SEND:
        if(!jump_to_decision){
            if(!value_decided(p) && p != leader(phase,n) && condition2){
                send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase,n)); 
            }
        }

    UPDATE:
        jump_to_decision3 = i_should_jump();
        jump_to_decision = jump_to_decision1 || jump_to_decision2 || jump_to_decision3;
        if(!jump_to_decision){
            condition3 = !value_decided(p) && p == leader(phase,n) && count(mbox, phase, THIRD_ROUND, null_int()) > (n+1)/2 && all_ack(mbox) && condition1????;
            
            // adding condition2 would contradict p == leader(phase,n)
            // I see no reason to remove condition1
            if(!value_decided(p) && p == leader(phase,n) && count(mbox, phase, THIRD_ROUND, null_int()) > (n+1)/2 && all_ack(mbox) && condition1????){
                decide(estimate);
            }
        
        }

FOURTH_ROUND
    SEND:
        if(!jump_to_decision){
            if(p == leader(phase,n) && condition3){
                send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
            }
            if(value_decided(p) && p == leader(phase,n)){
                send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
            }
        }
    UPDATE:
        jump_to_decision4 = i_should_jump();
        jump_to_decision = jump_to_decision1 || jump_to_decision2 || jump_to_decision3 || jump_to_decision4;
        
        // I see no reason to remove condition1
        if(jump_to_decision || (p != leader(phase,n) && count(mbox, phase, FOURTH_ROUND, leader(phase,n)) == 1 && mbox->message->decided && condition2????)){
            estimate = m->estimate;
            decide(estimate);
        }
        // next phase
        jump_to_decision = i_should_jump();