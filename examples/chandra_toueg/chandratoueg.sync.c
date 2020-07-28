################## FIRST_ROUND ######################
############ send ############
int main()
{
  if (((!value_decided(p)) && (p != leader(phase, n))) && (round == FIRST_ROUND))
  {
    send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
  }

}


############ update ############
int main()
{
  round = FIRST_ROUND;
  estimate = in();
  timestamp = 0;
  mbox = havoc(phase, round);
  if (((((!value_decided(p)) && (p == leader(phase, n))) && (round == FIRST_ROUND)) && (count(mbox, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox, null_int(), FOURTH_ROUND, null_int()) == 0))
  {
    m = max_timestamp(mbox_0_0);
    estimate = m->estimate;
    round_0_0 = SECOND_ROUND;
  }

  if (((!value_decided(p)) && (p != leader(phase, n))) && (round == FIRST_ROUND))
  {
    round_0_3 = SECOND_ROUND;
  }

  if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox->message->decided) && (mbox->message->phase > phase))
  {
    round_0_6 = FOURTH_ROUND;
  }

  if ((!value_decided(p)) && timeout(round))
  {
    phase++;
  }

  if (value_decided(p) && (p == leader(phase, n)))
  {
    round_0_8 = FOURTH_ROUND;
  }

}


################## SECOND_ROUND ######################
############ send ############
int main()
{
  if (((((!value_decided(p)) && (p == leader(phase, n))) && (round == FIRST_ROUND)) && (count(mbox, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox, null_int(), FOURTH_ROUND, null_int()) == 0))
  {
    send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
  }

}


############ update ############
int main()
{
  if (((((!value_decided(p)) && (p == leader(phase, n))) && (round == FIRST_ROUND)) && (count(mbox, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox, null_int(), FOURTH_ROUND, null_int()) == 0))
  {
    round_0_0 = SECOND_ROUND;
    round_0_0 = THIRD_ROUND;
  }

  if (((!value_decided(p)) && (p != leader(phase, n))) && (round == FIRST_ROUND))
  {
    round_0_3 = SECOND_ROUND;
    mbox_0_3 = havoc(phase, round_0_3);
    if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0_3 == SECOND_ROUND)) && (count(mbox_0_3, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0_3, null_int(), FOURTH_ROUND, null_int()) == 0))
    {
      m = mbox_1_4->message;
      estimate = m->estimate;
      timestamp = phase;
      round_1_4 = THIRD_ROUND;
    }

    if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_0_3, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_0_3->message->decided) && (mbox_0_3->message->phase > phase))
    {
      round_1_6 = FOURTH_ROUND;
    }

    if ((!value_decided(p)) && timeout(round_0_3))
    {
      phase++;
    }

  }

}


################## THIRD_ROUND ######################
############ send ############
int main()
{
  if (((!value_decided(p)) && (p != leader(phase, n))) && (round == FIRST_ROUND))
  {
    if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0_3 == SECOND_ROUND)) && (count(mbox_0_3, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0_3, null_int(), FOURTH_ROUND, null_int()) == 0))
    {
      send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
    }

  }

}


############ update ############
int main()
{
  if (((((!value_decided(p)) && (p == leader(phase, n))) && (round == FIRST_ROUND)) && (count(mbox, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox, null_int(), FOURTH_ROUND, null_int()) == 0))
  {
    round_0_0 = THIRD_ROUND;
    mbox_0_0 = havoc(phase, round_0_0);
    if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_0 == THIRD_ROUND)) && (count(mbox_0_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_0_0))
    {
      round_1_1 = FOURTH_ROUND;
    }

    if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_0 == THIRD_ROUND)) && (count(mbox_0_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_0_0)))
    {
      phase++;
    }

    if ((!value_decided(p)) && timeout(round_0_0))
    {
      phase++;
    }

  }

  if (((!value_decided(p)) && (p != leader(phase, n))) && (round == FIRST_ROUND))
  {
    if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0_3 == SECOND_ROUND)) && (count(mbox_0_3, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0_3, null_int(), FOURTH_ROUND, null_int()) == 0))
    {
      round_1_4 = THIRD_ROUND;
      round_1_4 = FOURTH_ROUND;
    }

  }

}


################## FOURTH_ROUND ######################
############ send ############
int main()
{
  if (((((!value_decided(p)) && (p == leader(phase, n))) && (round == FIRST_ROUND)) && (count(mbox, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox, null_int(), FOURTH_ROUND, null_int()) == 0))
  {
    if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_0 == THIRD_ROUND)) && (count(mbox_0_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_0_0))
    {
      send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
    }

  }

  if (value_decided(p) && (p == leader(phase, n)))
  {
    send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
  }

}


############ update ############
int main()
{
  if (((((!value_decided(p)) && (p == leader(phase, n))) && (round == FIRST_ROUND)) && (count(mbox, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox, null_int(), FOURTH_ROUND, null_int()) == 0))
  {
    if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_0 == THIRD_ROUND)) && (count(mbox_0_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_0_0))
    {
      round_1_1 = FOURTH_ROUND;
      decide(estimate);
      phase++;
    }

  }

  if (((!value_decided(p)) && (p != leader(phase, n))) && (round == FIRST_ROUND))
  {
    if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0_3 == SECOND_ROUND)) && (count(mbox_0_3, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0_3, null_int(), FOURTH_ROUND, null_int()) == 0))
    {
      round_1_4 = FOURTH_ROUND;
      mbox_1_4 = havoc(phase, round_1_4);
      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_4 == FOURTH_ROUND)) && (count(mbox_1_4, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1_4->message->decided)
      {
        estimate = m->estimate;
        decide(estimate);
        phase++;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1_4->message->decided) && (mbox_1_4->message->phase > phase))
      {
        round_2_0 = FOURTH_ROUND;
        estimate = m->estimate;
        decide(estimate);
        phase = mbox_2_0->message->phase + 1;
      }

      if ((!value_decided(p)) && timeout(round_1_4))
      {
        phase++;
      }

    }

    if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_0_3, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_0_3->message->decided) && (mbox_0_3->message->phase > phase))
    {
      round_1_6 = FOURTH_ROUND;
      estimate = m->estimate;
      decide(estimate);
      phase = mbox_1_6->message->phase + 1;
    }

  }

  if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox->message->decided) && (mbox->message->phase > phase))
  {
    round_0_6 = FOURTH_ROUND;
    estimate = m->estimate;
    decide(estimate);
    phase = mbox_0_6->message->phase + 1;
  }

  if (value_decided(p) && (p == leader(phase, n)))
  {
    round_0_8 = FOURTH_ROUND;
    phase++;
  }

}


