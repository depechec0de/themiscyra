################## FIRST_ROUND ######################
SEND: 
{
  send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
}

UPDATE: 
{
  estimate = in();
  timestamp = 0;
  if (((!value_decided) && (round == FIRST_ROUND)) && (!leader(phase)))
  {
    __pred_0 = ((!value_decided) && (round == FIRST_ROUND)) && (!leader(phase));
  }

  if ((((!value_decided) && leader(phase)) && (round == FIRST_ROUND)) && (count(mbox, phase, FIRST_ROUND) > (n / 2)))
  {
    __pred_8 = (((!value_decided) && leader(phase)) && (round == FIRST_ROUND)) && (count(mbox, phase, FIRST_ROUND) > (n / 2));
    estimate = max_timestamp(mbox);
  }

  if ((((!value_decided) && leader(phase)) && (round == FIRST_ROUND)) && timeout(round))
  {
    __pred_18 = (((!value_decided) && leader(phase)) && (round == FIRST_ROUND)) && timeout(round);
  }

  if ((!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1))
  {
    __pred_21 = (!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1);
    phase = max_phase_geq(mbox, phase, FOURTH_ROUND);
  }

  if (leader(phase) && value_decided)
  {
    __pred_22 = leader(phase) && value_decided;
  }

}

################## SECOND_ROUND ######################
SEND: 
{
  if (__pred_8)
  {
    send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
  }

}

UPDATE: 
{
  if (__pred_0)
  {
    if ((((!value_decided) && (!leader(phase))) && (round == SECOND_ROUND)) && (count(mbox, phase, SECOND_ROUND) == 1))
    {
      __pred_1 = (((!value_decided) && (!leader(phase))) && (round == SECOND_ROUND)) && (count(mbox, phase, SECOND_ROUND) == 1);
      m = mbox->message;
      estimate = m->estimate;
      timestamp = phase;
    }

    if ((((!value_decided) && (!leader(phase))) && (round == SECOND_ROUND)) && timeout(round))
    {
      __pred_4 = (((!value_decided) && (!leader(phase))) && (round == SECOND_ROUND)) && timeout(round);
    }

    if ((!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1))
    {
      __pred_7 = (!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1);
      phase = max_phase_geq(mbox, phase, FOURTH_ROUND);
    }

  }

}

################## THIRD_ROUND ######################
SEND: 
{
  if (__pred_0 && __pred_1)
  {
    send(message(phase, THIRD_ROUND, NULL, p, timestamp, true), leaderid(phase));
  }

  if (__pred_0 && __pred_4)
  {
    send(message(phase, THIRD_ROUND, NULL, p, timestamp, false), leaderid(phase));
  }

}

UPDATE: 
{
  if (__pred_8)
  {
    if (((((!value_decided) && leader(phase)) && (round == THIRD_ROUND)) && (count(mbox, phase, THIRD_ROUND) > (n / 2))) && (count_ack(mbox, phase) <= (n / 2)))
    {
      __pred_9 = ((((!value_decided) && leader(phase)) && (round == THIRD_ROUND)) && (count(mbox, phase, THIRD_ROUND) > (n / 2))) && (count_ack(mbox, phase) <= (n / 2));
    }

    if (((((!value_decided) && leader(phase)) && (round == THIRD_ROUND)) && (count(mbox, phase, THIRD_ROUND) > (n / 2))) && (count_ack(mbox, phase) > (n / 2)))
    {
      __pred_12 = ((((!value_decided) && leader(phase)) && (round == THIRD_ROUND)) && (count(mbox, phase, THIRD_ROUND) > (n / 2))) && (count_ack(mbox, phase) > (n / 2));
    }

    if ((((!value_decided) && leader(phase)) && (round == THIRD_ROUND)) && timeout(round))
    {
      __pred_14 = (((!value_decided) && leader(phase)) && (round == THIRD_ROUND)) && timeout(round);
    }

    if ((!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1))
    {
      __pred_17 = (!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1);
      phase = max_phase_geq(mbox, phase, FOURTH_ROUND);
    }

  }

}

################## FOURTH_ROUND ######################
SEND: 
{
  if (__pred_8 && __pred_12)
  {
    send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
    if (leader(phase) && value_decided)
    {
      send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
    }

  }

  if (__pred_8 && (__pred_12 && __pred_13))
  {
    send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
  }

  if (__pred_22)
  {
    send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
  }

}

UPDATE: 
{
  if (__pred_0 && __pred_1)
  {
    if ((!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1))
    {
      __pred_2 = (!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1);
      phase = max_phase_geq(mbox, phase, FOURTH_ROUND);
      estimate = m->estimate;
      value_decided = true;
    }

    if (((!value_decided) && (round == FOURTH_ROUND)) && timeout(round))
    {
      __pred_3 = ((!value_decided) && (round == FOURTH_ROUND)) && timeout(round);
    }

  }

  if (__pred_0 && (__pred_1 && __pred_2))
  {
    estimate = m->estimate;
    value_decided = true;
  }

  if (__pred_0 && __pred_4)
  {
    if ((!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1))
    {
      __pred_5 = (!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1);
      phase = max_phase_geq(mbox, phase, FOURTH_ROUND);
      estimate = m->estimate;
      value_decided = true;
    }

    if (((!value_decided) && (round == FOURTH_ROUND)) && timeout(round))
    {
      __pred_6 = ((!value_decided) && (round == FOURTH_ROUND)) && timeout(round);
    }

  }

  if (__pred_0 && (__pred_4 && __pred_5))
  {
    estimate = m->estimate;
    value_decided = true;
  }

  if (__pred_0 && __pred_7)
  {
    estimate = m->estimate;
    value_decided = true;
  }

  if (__pred_8 && __pred_9)
  {
    value_decided = false;
    if ((!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1))
    {
      __pred_10 = (!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1);
      phase = max_phase_geq(mbox, phase, FOURTH_ROUND);
      estimate = m->estimate;
      value_decided = true;
    }

    if (((!value_decided) && (round == FOURTH_ROUND)) && timeout(round))
    {
      __pred_11 = ((!value_decided) && (round == FOURTH_ROUND)) && timeout(round);
    }

  }

  if (__pred_8 && (__pred_9 && __pred_10))
  {
    estimate = m->estimate;
    value_decided = true;
  }

  if (__pred_8 && __pred_12)
  {
    value_decided = true;
    if (leader(phase) && value_decided)
    {
      __pred_13 = leader(phase) && value_decided;
    }

  }

  if (__pred_8 && __pred_14)
  {
    value_decided = false;
    if ((!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1))
    {
      __pred_15 = (!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1);
      phase = max_phase_geq(mbox, phase, FOURTH_ROUND);
      estimate = m->estimate;
      value_decided = true;
    }

    if (((!value_decided) && (round == FOURTH_ROUND)) && timeout(round))
    {
      __pred_16 = ((!value_decided) && (round == FOURTH_ROUND)) && timeout(round);
    }

  }

  if (__pred_8 && (__pred_14 && __pred_15))
  {
    estimate = m->estimate;
    value_decided = true;
  }

  if (__pred_8 && __pred_17)
  {
    estimate = m->estimate;
    value_decided = true;
  }

  if (__pred_18)
  {
    value_decided = false;
    if ((!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1))
    {
      __pred_19 = (!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1);
      phase = max_phase_geq(mbox, phase, FOURTH_ROUND);
      estimate = m->estimate;
      value_decided = true;
    }

    if (((!value_decided) && (round == FOURTH_ROUND)) && timeout(round))
    {
      __pred_20 = ((!value_decided) && (round == FOURTH_ROUND)) && timeout(round);
    }

  }

  if (__pred_18 && __pred_19)
  {
    estimate = m->estimate;
    value_decided = true;
  }

  if (__pred_21)
  {
    estimate = m->estimate;
    value_decided = true;
  }

}

