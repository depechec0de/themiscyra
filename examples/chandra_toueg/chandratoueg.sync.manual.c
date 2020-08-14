/*
given current_phase' > current_phase

jumpt_to()  = (current_phase', FIRST_ROUND) if leader(current_phase') && count(mbox, current_phase', FIRST_ROUND) > f
            = (current_phase', THIRD_ROUND) if leader(current_phase') && count(mbox, current_phase', THIRD_ROUND) > f
            = (current_phase', SECOND_ROUND) if !leader(current_phase') && count(mbox, current_phase', THIRD_ROUND) == 1
            = (current_phase', FOURTH_ROUND) if !leader(current_phase') && count(mbox, current_phase', FOURTH_ROUND) == 1

*/
jumpt_to(int current_phase, int current_round);

INIT(){
    current_phase_round = jump_to();
}

FIRST_ROUND(){
    SEND(){
        if(current_phase_round == (PHASE, ROUND)){
            if(!value_decided(p)){
                send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase)); 
            }
        }
    }
    UPDATE(){
        current_phase_round = jump_to();
        if(current_phase_round == (PHASE, ROUND)){
            condition1 = count(mbox, FIRST_ROUND) > f && !value_decided(p) && leader(phase);

            if(condition1){
                m = max_timestamp(mbox);
                estimate = m->estimate;
            }
        }
    }
}

SECOND_ROUND(){
    SEND(){
        if(current_phase_round == (PHASE, ROUND)){
            if(!value_decided(p) && leader(phase) && condition1){
                send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all); 
            }
        }
    }
    UPDATE(){
        current_phase_round = jump_to();
        if(current_phase_round == (PHASE, ROUND)){
            condition2 = !value_decided(p) && !leader(phase) && count(mbox, SECOND_ROUND) == 1;

            if(condition2){
                m = mbox->message;
                estimate = m->estimate;
                timestamp = phase;
            }
        }
    }
}

THIRD_ROUND(){
    SEND(){
        if(current_phase_round == (PHASE, ROUND)){
            if(!value_decided(p) && !leader(phase) && condition2){
                send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase)); 
            }
        }
    }

    UPDATE(){
        current_phase_round = jump_to();
        if(current_phase_round == (PHASE, ROUND)){
            condition3 = !value_decided(p) && leader(phase) && count(mbox, THIRD_ROUND) > f;
            
            if(all_ack(mbox) && condition3){
                decide(estimate);
            }
        }
    }
}

FOURTH_ROUND(){
    SEND(){
        if(current_phase_round == (PHASE, ROUND)){
            if(!value_decided(p) && leader(phase) && condition3){
                send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
            }
            if(value_decided(p) && leader(phase)){
                send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
            }
        }
    }
    UPDATE(){
        current_phase_round = jump_to();
        
        condition4 = !leader(phase) && count(mbox, FOURTH_ROUND) == 1;
        
        if(current_phase_round == (PHASE, ROUND) || (condition4 && condition2)){
            estimate = m->estimate;
            decide(estimate);
        }
        // next phase
        current_phase_round = jump_to();
    }
}