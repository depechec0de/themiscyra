FIRST_ROUND
################Path######################
{
  int main(int p, int n, int f)
{
  phase = 1;
  round = FIRST_ROUND;
  estimate = in();
  state = 0;
  timestamp = 0;
  send(message(phase, FIRST_ROUND, estimate, p, timestamp, NULL, NULL), leader(phase, n));
  mbox = havoc();
  if ((p != leader(phase, n)) && (round == FIRST_ROUND))
  {
    round_0_0 = SECOND_ROUND;
  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  phase = 1;
  round = FIRST_ROUND;
  estimate = in();
  state = 0;
  timestamp = 0;
  send(message(phase, FIRST_ROUND, estimate, p, timestamp, NULL, NULL), leader(phase, n));
  mbox = havoc();
  if (!((p != leader(phase, n)) && (round == FIRST_ROUND)))
  {
    if ((((p == leader(phase, n)) && (round == FIRST_ROUND)) && (count(mbox, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox, FOURTH_ROUND) == 0))
    {
      m = max_timestamp(mbox_0_1);
      estimate = m->estimate;
      round_0_1 = SECOND_ROUND;
    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  phase = 1;
  round = FIRST_ROUND;
  estimate = in();
  state = 0;
  timestamp = 0;
  send(message(phase, FIRST_ROUND, estimate, p, timestamp, NULL, NULL), leader(phase, n));
  mbox = havoc();
  if (!((p != leader(phase, n)) && (round == FIRST_ROUND)))
  {
    if (!((((p == leader(phase, n)) && (round == FIRST_ROUND)) && (count(mbox, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox, FOURTH_ROUND) == 0)))
    {
      if (count(mbox, FOURTH_ROUND) > 0)
      {
        round_0_5 = FOURTH_ROUND;
      }

    }

  }

}


}

##########################################
SECOND_ROUND
################Path######################
{
int main(int p, int n, int f)
{
  phase = 1;
  round = FIRST_ROUND;
  estimate = in();
  state = 0;
  timestamp = 0;
  send(message(phase, FIRST_ROUND, estimate, p, timestamp, NULL, NULL), leader(phase, n));
  mbox = havoc();
  if ((p != leader(phase, n)) && (round == FIRST_ROUND))
  {
    round_0_0 = SECOND_ROUND;
    mbox_0_0 = havoc();
    if ((round_0_0 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
    {
      round_1_2 = THIRD_ROUND;
    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  phase = 1;
  round = FIRST_ROUND;
  estimate = in();
  state = 0;
  timestamp = 0;
  send(message(phase, FIRST_ROUND, estimate, p, timestamp, NULL, NULL), leader(phase, n));
  mbox = havoc();
  if ((p != leader(phase, n)) && (round == FIRST_ROUND))
  {
    round_0_0 = SECOND_ROUND;
    mbox_0_0 = havoc();
    if (!((round_0_0 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1)))
    {
      if (((round_0_0 == SECOND_ROUND) && (count(mbox_0_0, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_0_0, FOURTH_ROUND) == 0))
      {
        estimate = mbox_1_3->message->estimate;
        timestamp = phase;
        ack = 1;
        round_1_3 = THIRD_ROUND;
      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  phase = 1;
  round = FIRST_ROUND;
  estimate = in();
  state = 0;
  timestamp = 0;
  send(message(phase, FIRST_ROUND, estimate, p, timestamp, NULL, NULL), leader(phase, n));
  mbox = havoc();
  if (!((p != leader(phase, n)) && (round == FIRST_ROUND)))
  {
    if ((((p == leader(phase, n)) && (round == FIRST_ROUND)) && (count(mbox, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox, FOURTH_ROUND) == 0))
    {
      m = max_timestamp(mbox_0_1);
      estimate = m->estimate;
      round_0_1 = SECOND_ROUND;
      send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
      mbox_0_1 = havoc();
      if ((round_0_1 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
      {
        round_1_2 = THIRD_ROUND;
      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  phase = 1;
  round = FIRST_ROUND;
  estimate = in();
  state = 0;
  timestamp = 0;
  send(message(phase, FIRST_ROUND, estimate, p, timestamp, NULL, NULL), leader(phase, n));
  mbox = havoc();
  if (!((p != leader(phase, n)) && (round == FIRST_ROUND)))
  {
    if ((((p == leader(phase, n)) && (round == FIRST_ROUND)) && (count(mbox, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox, FOURTH_ROUND) == 0))
    {
      m = max_timestamp(mbox_0_1);
      estimate = m->estimate;
      round_0_1 = SECOND_ROUND;
      send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
      mbox_0_1 = havoc();
      if (!((round_0_1 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1)))
      {
        if (((round_0_1 == SECOND_ROUND) && (count(mbox_0_1, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_0_1, FOURTH_ROUND) == 0))
        {
          estimate = mbox_1_3->message->estimate;
          timestamp = phase;
          ack = 1;
          round_1_3 = THIRD_ROUND;
        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  phase = 1;
  round = FIRST_ROUND;
  estimate = in();
  state = 0;
  timestamp = 0;
  send(message(phase, FIRST_ROUND, estimate, p, timestamp, NULL, NULL), leader(phase, n));
  mbox = havoc();
  if ((p != leader(phase, n)) && (round == FIRST_ROUND))
  {
    round_0_0 = SECOND_ROUND;
    mbox_0_0 = havoc();
    if (!((round_0_0 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1)))
    {
      if (!(((round_0_0 == SECOND_ROUND) && (count(mbox_0_0, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_0_0, FOURTH_ROUND) == 0)))
      {
        if (count(mbox_0_0, FOURTH_ROUND) > 0)
        {
          round_1_5 = FOURTH_ROUND;
        }

      }

    }

  }

}


}

##########################################
THIRD_ROUND
################Path######################
{
int main(int p, int n, int f)
{
  phase = 1;
  round = FIRST_ROUND;
  estimate = in();
  state = 0;
  timestamp = 0;
  send(message(phase, FIRST_ROUND, estimate, p, timestamp, NULL, NULL), leader(phase, n));
  mbox = havoc();
  if ((p != leader(phase, n)) && (round == FIRST_ROUND))
  {
    round_0_0 = SECOND_ROUND;
    mbox_0_0 = havoc();
    if (!((round_0_0 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1)))
    {
      if (((round_0_0 == SECOND_ROUND) && (count(mbox_0_0, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_0_0, FOURTH_ROUND) == 0))
      {
        estimate = mbox_1_3->message->estimate;
        timestamp = phase;
        ack = 1;
        round_1_3 = THIRD_ROUND;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
        if (p != leader(phase, n))
        {
          round_1_3 = FOURTH_ROUND;
        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  phase = 1;
  round = FIRST_ROUND;
  estimate = in();
  state = 0;
  timestamp = 0;
  send(message(phase, FIRST_ROUND, estimate, p, timestamp, NULL, NULL), leader(phase, n));
  mbox = havoc();
  if (!((p != leader(phase, n)) && (round == FIRST_ROUND)))
  {
    if ((((p == leader(phase, n)) && (round == FIRST_ROUND)) && (count(mbox, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox, FOURTH_ROUND) == 0))
    {
      m = max_timestamp(mbox_0_1);
      estimate = m->estimate;
      round_0_1 = SECOND_ROUND;
      send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
      mbox_0_1 = havoc();
      if (!((round_0_1 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1)))
      {
        if (((round_0_1 == SECOND_ROUND) && (count(mbox_0_1, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_0_1, FOURTH_ROUND) == 0))
        {
          estimate = mbox_1_3->message->estimate;
          timestamp = phase;
          ack = 1;
          round_1_3 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          mbox_1_3 = havoc();
          if ((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, THIRD_ROUND, phase) > (n + (1 / 2)))) && (count(mbox_1_3, FOURTH_ROUND) == 0))
          {
            if (all_ack(mbox_2_0) == 1)
            {
              round_2_0 = FOURTH_ROUND;
            }

          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  phase = 1;
  round = FIRST_ROUND;
  estimate = in();
  state = 0;
  timestamp = 0;
  send(message(phase, FIRST_ROUND, estimate, p, timestamp, NULL, NULL), leader(phase, n));
  mbox = havoc();
  if ((p != leader(phase, n)) && (round == FIRST_ROUND))
  {
    round_0_0 = SECOND_ROUND;
    mbox_0_0 = havoc();
    if ((round_0_0 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
    {
      round_1_2 = THIRD_ROUND;
      send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
      phase++;
    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  phase = 1;
  round = FIRST_ROUND;
  estimate = in();
  state = 0;
  timestamp = 0;
  send(message(phase, FIRST_ROUND, estimate, p, timestamp, NULL, NULL), leader(phase, n));
  mbox = havoc();
  if (!((p != leader(phase, n)) && (round == FIRST_ROUND)))
  {
    if ((((p == leader(phase, n)) && (round == FIRST_ROUND)) && (count(mbox, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox, FOURTH_ROUND) == 0))
    {
      m = max_timestamp(mbox_0_1);
      estimate = m->estimate;
      round_0_1 = SECOND_ROUND;
      send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
      mbox_0_1 = havoc();
      if ((round_0_1 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
      {
        round_1_2 = THIRD_ROUND;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
        phase++;
      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  phase = 1;
  round = FIRST_ROUND;
  estimate = in();
  state = 0;
  timestamp = 0;
  send(message(phase, FIRST_ROUND, estimate, p, timestamp, NULL, NULL), leader(phase, n));
  mbox = havoc();
  if (!((p != leader(phase, n)) && (round == FIRST_ROUND)))
  {
    if ((((p == leader(phase, n)) && (round == FIRST_ROUND)) && (count(mbox, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox, FOURTH_ROUND) == 0))
    {
      m = max_timestamp(mbox_0_1);
      estimate = m->estimate;
      round_0_1 = SECOND_ROUND;
      send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
      mbox_0_1 = havoc();
      if (!((round_0_1 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1)))
      {
        if (((round_0_1 == SECOND_ROUND) && (count(mbox_0_1, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_0_1, FOURTH_ROUND) == 0))
        {
          estimate = mbox_1_3->message->estimate;
          timestamp = phase;
          ack = 1;
          round_1_3 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          mbox_1_3 = havoc();
          if ((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, THIRD_ROUND, phase) > (n + (1 / 2)))) && (count(mbox_1_3, FOURTH_ROUND) == 0))
          {
            if (!(all_ack(mbox_2_0) == 1))
            {
              phase++;
            }

          }

        }

      }

    }

  }

}


}

##########################################
FOURTH_ROUND
################Path######################
{
int main(int p, int n, int f)
{
  phase = 1;
  round = FIRST_ROUND;
  estimate = in();
  state = 0;
  timestamp = 0;
  send(message(phase, FIRST_ROUND, estimate, p, timestamp, NULL, NULL), leader(phase, n));
  mbox = havoc();
  if ((p != leader(phase, n)) && (round == FIRST_ROUND))
  {
    round_0_0 = SECOND_ROUND;
    mbox_0_0 = havoc();
    if (!((round_0_0 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1)))
    {
      if (!(((round_0_0 == SECOND_ROUND) && (count(mbox_0_0, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_0_0, FOURTH_ROUND) == 0)))
      {
        if (count(mbox_0_0, FOURTH_ROUND) > 0)
        {
          round_1_5 = FOURTH_ROUND;
          if (mbox_1_5->message->decided)
          {
            estimate = mbox_1_5->message->estimate;
            out(p, estimate);
            phase++;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  phase = 1;
  round = FIRST_ROUND;
  estimate = in();
  state = 0;
  timestamp = 0;
  send(message(phase, FIRST_ROUND, estimate, p, timestamp, NULL, NULL), leader(phase, n));
  mbox = havoc();
  if ((p != leader(phase, n)) && (round == FIRST_ROUND))
  {
    round_0_0 = SECOND_ROUND;
    mbox_0_0 = havoc();
    if (!((round_0_0 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1)))
    {
      if (!(((round_0_0 == SECOND_ROUND) && (count(mbox_0_0, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_0_0, FOURTH_ROUND) == 0)))
      {
        if (count(mbox_0_0, FOURTH_ROUND) > 0)
        {
          round_1_5 = FOURTH_ROUND;
          if (!mbox_1_5->message->decided)
          {
            phase++;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  phase = 1;
  round = FIRST_ROUND;
  estimate = in();
  state = 0;
  timestamp = 0;
  send(message(phase, FIRST_ROUND, estimate, p, timestamp, NULL, NULL), leader(phase, n));
  mbox = havoc();
  if (!((p != leader(phase, n)) && (round == FIRST_ROUND)))
  {
    if ((((p == leader(phase, n)) && (round == FIRST_ROUND)) && (count(mbox, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox, FOURTH_ROUND) == 0))
    {
      m = max_timestamp(mbox_0_1);
      estimate = m->estimate;
      round_0_1 = SECOND_ROUND;
      send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
      mbox_0_1 = havoc();
      if (!((round_0_1 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1)))
      {
        if (((round_0_1 == SECOND_ROUND) && (count(mbox_0_1, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_0_1, FOURTH_ROUND) == 0))
        {
          estimate = mbox_1_3->message->estimate;
          timestamp = phase;
          ack = 1;
          round_1_3 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          mbox_1_3 = havoc();
          if ((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, THIRD_ROUND, phase) > (n + (1 / 2)))) && (count(mbox_1_3, FOURTH_ROUND) == 0))
          {
            if (all_ack(mbox_2_0) == 1)
            {
              round_2_0 = FOURTH_ROUND;
              send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
              phase++;
            }

          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  phase = 1;
  round = FIRST_ROUND;
  estimate = in();
  state = 0;
  timestamp = 0;
  send(message(phase, FIRST_ROUND, estimate, p, timestamp, NULL, NULL), leader(phase, n));
  mbox = havoc();
  if (!((p != leader(phase, n)) && (round == FIRST_ROUND)))
  {
    if (!((((p == leader(phase, n)) && (round == FIRST_ROUND)) && (count(mbox, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox, FOURTH_ROUND) == 0)))
    {
      if (count(mbox, FOURTH_ROUND) > 0)
      {
        round_0_5 = FOURTH_ROUND;
        if (mbox_0_5->message->decided)
        {
          estimate = mbox_0_5->message->estimate;
          out(p, estimate);
          phase++;
        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  phase = 1;
  round = FIRST_ROUND;
  estimate = in();
  state = 0;
  timestamp = 0;
  send(message(phase, FIRST_ROUND, estimate, p, timestamp, NULL, NULL), leader(phase, n));
  mbox = havoc();
  if (!((p != leader(phase, n)) && (round == FIRST_ROUND)))
  {
    if (!((((p == leader(phase, n)) && (round == FIRST_ROUND)) && (count(mbox, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox, FOURTH_ROUND) == 0)))
    {
      if (count(mbox, FOURTH_ROUND) > 0)
      {
        round_0_5 = FOURTH_ROUND;
        if (!mbox_0_5->message->decided)
        {
          phase++;
        }

      }

    }

  }

}


}

##########################################
