################## INIT ######################
value_decided = false;
phase = 0;
estimate = in();
timestamp = 0;

################## FIRST_ROUND ######################
SEND(PHASE, ROUND): 
{
    if(PHASE == phase){
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
    }
  
}

UPDATE(MBOX, PHASE, ROUND): 
{
    if(PHASE == phase){
        estimate = in();
        timestamp = 0;
        if (((!value_decided) && (round == FIRST_ROUND)) && (!leader(phase)))
        {
            __pred_0 = true;
        }
        else
            if ((((!value_decided) && leader(phase)) && (round == FIRST_ROUND)) && (count(mbox, phase, FIRST_ROUND) > (n / 2)))
        {
            __pred_8 = true;
            estimate = max_timestamp(mbox);
        }
        else
            if ((((!value_decided) && leader(phase)) && (round == FIRST_ROUND)) && nondet_timeout())
            //if ((((!value_decided) && leader(phase)) && (round == FIRST_ROUND)) && timeout(round))
        {
            __pred_14 = true;
            value_decided = false;
        }
        else
            if ((!value_decided) && (nondet_count_with_max_phase_geq()))
            //if ((!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1))
        {
            __pred_15 = true;
            estimate = m->estimate;
            value_decided = true;
            //phase = max_phase_geq(mbox, phase, FOURTH_ROUND);
            phase = nondet_max_phase_geq();
        }
        else
            if (leader(phase) && value_decided)
        {
            __pred_16 = true;
        }
    }

}

################## SECOND_ROUND ######################
SEND(PHASE, ROUND): 
{
    if(PHASE == phase){
        if (__pred_8)
        {
            send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
        }
    }
}

UPDATE(MBOX, PHASE, ROUND): 
{
    if(PHASE == phase){
        if (__pred_0)
        {
            if ((((!value_decided) && (!leader(phase))) && (round == SECOND_ROUND)) && (count(mbox, phase, SECOND_ROUND) == 1))
            {
                __pred_1 = true;
            }
            else
            if ((((!value_decided) && (!leader(phase))) && (round == SECOND_ROUND)) && nondet_timeout())
            //if ((((!value_decided) && (!leader(phase))) && (round == SECOND_ROUND)) && timeout(round))
            {
                __pred_4 = true;
            }
            else
            if ((!value_decided) && (nondet_count_with_max_phase_geq()))
            //if ((!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1))
            {
                __pred_7 = true;
                estimate = m->estimate;
                value_decided = true;
                //phase = max_phase_geq(mbox, phase, FOURTH_ROUND);
                phase = nondet_max_phase_geq();
            }

        }
    }

}

################## THIRD_ROUND ######################
SEND(PHASE, ROUND): 
{
    if(PHASE == phase){
        if (__pred_0 && __pred_1)
        {
            send(message(phase, THIRD_ROUND, NULL, p, timestamp, true), leaderid(phase));
        }
        else
            if (__pred_0 && __pred_4)
        {
            send(message(phase, THIRD_ROUND, NULL, p, timestamp, false), leaderid(phase));
        }
    }

}

UPDATE(MBOX, PHASE, ROUND): 
{
    if(PHASE == phase){
        if (__pred_0 && __pred_1)
        {
            m = mbox->message;
            estimate = m->estimate;
            timestamp = phase;
        }
        else
            if (__pred_8)
        {
            if (((((!value_decided) && leader(phase)) && (round == THIRD_ROUND)) && (count(mbox, phase, THIRD_ROUND) > (n / 2))) && (count_ack(mbox, phase) <= (n / 2)))
            {
                __pred_9 = true;
                value_decided = false;
            }
            else
            if (((((!value_decided) && leader(phase)) && (round == THIRD_ROUND)) && (count(mbox, phase, THIRD_ROUND) > (n / 2))) && (count_ack(mbox, phase) > (n / 2)))
            {
                __pred_10 = true;
                value_decided = true;
            }
            else
            if ((((!value_decided) && leader(phase)) && (round == THIRD_ROUND)) && nondet_timeout())
            //if ((((!value_decided) && leader(phase)) && (round == THIRD_ROUND)) && timeout(round))
            {
                __pred_12 = true;
                value_decided = false;
            }
            else
            if ((!value_decided) && (nondet_count_with_max_phase_geq())
            //if ((!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1))
            {
                __pred_13 = true;
                estimate = m->estimate;
                value_decided = true;
                //phase = max_phase_geq(mbox, phase, FOURTH_ROUND);
                phase = nondet_max_phase_geq();
            }
        }

    }
}

################## FOURTH_ROUND ######################
SEND(PHASE, ROUND): 
{
    if(PHASE == phase){

        if (__pred_8 && __pred_10)
        {
            if (leader(phase) && value_decided)
            {
                send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
            }

        }
        else
            if (__pred_8 && (__pred_10 && __pred_11))
        {
            send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        }
        else
            if (__pred_16)
        {
            send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        }

    }

}

UPDATE(MBOX, PHASE, ROUND): 
{
    if(PHASE == phase){

        if (__pred_0 && __pred_1)
        {
            if ((!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1))
            {
                __pred_2 = true;
                estimate = m->estimate;
                value_decided = true;
                phase = max_phase_geq(mbox, phase, FOURTH_ROUND);
            }
            else
            if (((!value_decided) && (round == FOURTH_ROUND)) && nondet_timeout())
            //if (((!value_decided) && (round == FOURTH_ROUND)) && timeout(round))
            {
                __pred_3 = true;
            }


        }
        else
            if (__pred_0 && __pred_4)
        {
            if ((!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1))
            {
                __pred_5 = true;
                estimate = m->estimate;
                value_decided = true;
                phase = max_phase_geq(mbox, phase, FOURTH_ROUND);
            }
            else
            if (((!value_decided) && (round == FOURTH_ROUND)) && nondet_timeout())
            //if (((!value_decided) && (round == FOURTH_ROUND)) && timeout(round))
            {
                __pred_6 = true;
            }


        }
        else
            if (__pred_8 && __pred_10)
        {
            if (leader(phase) && value_decided)
            {
                __pred_11 = true;
            }

        }


    }
}

