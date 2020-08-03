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
mbox = havoc(phase, round);
int main()
{
  estimate = in();
  timestamp = 0;
  if (((((!value_decided(p)) && (p == leader(phase, n))) && (round == FIRST_ROUND)) && (count(mbox, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox, null_int(), FOURTH_ROUND, null_int()) == 0))
  {
    round_0 = SECOND_ROUND;
  }

  if (((!value_decided(p)) && (p != leader(phase, n))) && (round == FIRST_ROUND))
  {
    round_0 = SECOND_ROUND;
  }

  if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox->message->decided) && (mbox->message->phase > phase))
  {
    round_0 = FOURTH_ROUND;
  }

  if ((!value_decided(p)) && timeout(round))
  {
    phase++;
  }

  if (value_decided(p) && (p == leader(phase, n)))
  {
    round_0 = FOURTH_ROUND;
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
mbox_0 = havoc(phase, round_0);
int main()
{
  if (((((!value_decided(p)) && (p == leader(phase, n))) && (round == FIRST_ROUND)) && (count(mbox, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox, null_int(), FOURTH_ROUND, null_int()) == 0))
  {
    m = max_timestamp(mbox);
    estimate = m->estimate;
    round_0 = THIRD_ROUND;
  }

  if (((!value_decided(p)) && (p != leader(phase, n))) && (round == FIRST_ROUND))
  {
    if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == SECOND_ROUND)) && (count(mbox_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0))
    {
      round_1 = THIRD_ROUND;
    }

    if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_0, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_0->message->decided) && (mbox_0->message->phase > phase))
    {
      round_1 = FOURTH_ROUND;
    }

    if ((!value_decided(p)) && timeout(round_0))
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
    if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == SECOND_ROUND)) && (count(mbox_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0))
    {
      send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
    }

  }

}


############ update ############
mbox_0 = havoc(phase, round_0);
int main()
{
  if (((((!value_decided(p)) && (p == leader(phase, n))) && (round == FIRST_ROUND)) && (count(mbox, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox, null_int(), FOURTH_ROUND, null_int()) == 0))
  {
    if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == THIRD_ROUND)) && (count(mbox_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_0))
    {
      round_1 = FOURTH_ROUND;
    }

    if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == THIRD_ROUND)) && (count(mbox_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_0)))
    {
      phase++;
    }

    if ((!value_decided(p)) && timeout(round_0))
    {
      phase++;
    }

  }

  if (((!value_decided(p)) && (p != leader(phase, n))) && (round == FIRST_ROUND))
  {
    if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == SECOND_ROUND)) && (count(mbox_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0))
    {
      m = mbox_0->message;
      estimate = m->estimate;
      timestamp = phase;
      round_1 = FOURTH_ROUND;
    }

  }

}


################## FOURTH_ROUND ######################
############ send ############
int main()
{
  if (((((!value_decided(p)) && (p == leader(phase, n))) && (round == FIRST_ROUND)) && (count(mbox, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox, null_int(), FOURTH_ROUND, null_int()) == 0))
  {
    if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == THIRD_ROUND)) && (count(mbox_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_0))
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
mbox_1 = havoc(phase, round_1);
int main()
{
  if (((((!value_decided(p)) && (p == leader(phase, n))) && (round == FIRST_ROUND)) && (count(mbox, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox, null_int(), FOURTH_ROUND, null_int()) == 0))
  {
    if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == THIRD_ROUND)) && (count(mbox_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_0))
    {
      decide(estimate);
      phase++;
    }

  }

  if (((!value_decided(p)) && (p != leader(phase, n))) && (round == FIRST_ROUND))
  {
    if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == SECOND_ROUND)) && (count(mbox_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0))
    {
      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
      {
        estimate = m->estimate;
        decide(estimate);
        phase++;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
      {
        phase = mbox_1->message->phase;
      }

      if ((!value_decided(p)) && timeout(round_1))
      {
        phase++;
      }

    }

    if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_0, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_0->message->decided) && (mbox_0->message->phase > phase))
    {
      phase = mbox_0->message->phase;
    }

  }

  if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox->message->decided) && (mbox->message->phase > phase))
  {
    phase = mbox->message->phase;
  }

  if (value_decided(p) && (p == leader(phase, n)))
  {
    phase++;
  }

}


