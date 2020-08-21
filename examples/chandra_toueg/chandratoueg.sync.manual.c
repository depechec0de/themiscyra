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
        if(!value_decided(p)){
            send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase)); 
        }
    }
    UPDATE(){
        leader_round1 = phase_matching(mbox, phase, FIRST_ROUND, (n-1)/2) == phase && !value_decided(p) && leader(phase);
        if(current_phase_round == (PHASE, ROUND) || leader_round1){
            m = max_timestamp(mbox);
            estimate = m->estimate;
        }

        current_phase_round = jump_to();
    }
}

SECOND_ROUND(){
    SEND(){
        if(current_phase_round == (PHASE, ROUND) || (!value_decided(p) && leader(phase) && leader_round1)){
            send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all); 
        }
    }
    UPDATE(){
        follower_round2 = !value_decided(p) && !leader(phase) && phase_matching(mbox, phase, SECOND_ROUND, 1) == phase;

        if(current_phase_round == (PHASE, ROUND) || follower_round2){
            m = mbox->message;
            estimate = m->estimate;
            timestamp = phase;
        }

        current_phase_round = jump_to();
    }
}

THIRD_ROUND(){
    SEND(){
        if(current_phase_round == (PHASE, ROUND) || (!value_decided(p) && !leader(phase) && follower_round2)){
            send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase)); 
        }
    }

    UPDATE(){
        leader_round3 = !value_decided(p) && leader(phase) && count(mbox, THIRD_ROUND) > f;
        if(current_phase_round == (PHASE, ROUND) || leader_round3){
            decide(estimate);
        }

        current_phase_round = jump_to();
    }
}

FOURTH_ROUND(){
    SEND(){
        if(current_phase_round == (PHASE, ROUND) || (!value_decided(p) && leader(phase) && leader_round3)){
            send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        }
        if(value_decided(p) && leader(phase)){
            send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        }
    }

    UPDATE(){        
        follower_round4 = !leader(phase) && count(mbox, FOURTH_ROUND) == 1;
        
        if(current_phase_round == (PHASE, ROUND) || (follower_round4 && follower_round2)){
            estimate = m->estimate;
            decide(estimate);
        }

        current_phase_round = jump_to();
    }
}