struct msg
{
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
  struct msg *message;
  struct list *next;
  int size;
};
enum round_typ
{
  FIRST_ROUND,
  SECOND_ROUND,
  THIRD_ROUND,
  FOURTH_ROUND
};
int null_int();
_Bool null_bool();
int in();
int max_timestamp(struct list *mbox);
_Bool all_ack(struct list *mbox);
_Bool send(struct msg *message, int pid);
_Bool leader(int phase);
int leaderid(int phase);
int count_ack(struct list *mbox, int phase);
struct list *havoc(int phase, enum round_typ round);
struct list *query(struct list *mbox, int phase, enum round_typ round);
int max_phase_recv(struct list *mbox);
_Bool timeout(enum round_typ round);
struct msg *message(int phase, enum round_typ round, int estimate, int p, int timestamp, _Bool decided);
int count(struct list *mbox, int current_phase, enum round_typ round);
int count_with_max_phase_geq(struct list *mbox, int phase, enum round_typ round);
int max_phase_geq(struct list *mbox, int current_phase, enum round_typ round);
int main()
{
  int p;
  int n;
  int timestamp;
  int phase;
  enum round_typ round;
  int to_all = n + 1;
  int estimate;
  struct list *mbox;
  struct msg *m;
  _Bool value_decided;
  value_decided = false;
  estimate = in();
  timestamp = 0;
  phase = 1;
  round = FIRST_ROUND;
  send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
  while (1)
  {
    mbox = havoc(phase, round);
    if (((!value_decided) && (round == FIRST_ROUND)) && (!leader(phase)))
    {
      round = SECOND_ROUND;
      mbox = havoc(phase, round);
      if ((((!value_decided) && (!leader(phase))) && (round == SECOND_ROUND)) && (count(mbox, phase, SECOND_ROUND) == 1))
      {
        round = THIRD_ROUND;
        m = mbox->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, NULL, p, timestamp, true), leaderid(phase));
        round = FOURTH_ROUND;
        mbox = havoc(phase, round);
        if ((!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1))
        {
          estimate = m->estimate;
          value_decided = true;
          phase = max_phase_geq(mbox, phase, FOURTH_ROUND);
          round = FOURTH_ROUND;
          mbox = havoc(phase, round);
          if ((leader(phase) && value_decided) && (round == FOURTH_ROUND))
          {
            round = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
            phase++;
            round = FOURTH_ROUND;
            continue;
          }

          break;
        }

        if (((!value_decided) && (round == FOURTH_ROUND)) && timeout(round))
        {
          phase++;
          round = FIRST_ROUND;
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          continue;
        }

        break;
      }

      if ((!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1))
      {
        estimate = m->estimate;
        value_decided = true;
        phase = max_phase_geq(mbox, phase, FOURTH_ROUND);
        round = FOURTH_ROUND;
        mbox = havoc(phase, round);
        if ((leader(phase) && value_decided) && (round == FOURTH_ROUND))
        {
          round = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round = FOURTH_ROUND;
          continue;
        }

        break;
      }

      if ((((!value_decided) && (!leader(phase))) && (round == SECOND_ROUND)) && timeout(round))
      {
        round = THIRD_ROUND;
        send(message(phase, THIRD_ROUND, NULL, p, timestamp, false), leaderid(phase));
        round = FOURTH_ROUND;
        mbox = havoc(phase, round);
        if ((!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1))
        {
          estimate = m->estimate;
          value_decided = true;
          phase = max_phase_geq(mbox, phase, FOURTH_ROUND);
          round = FOURTH_ROUND;
          mbox = havoc(phase, round);
          if ((leader(phase) && value_decided) && (round == FOURTH_ROUND))
          {
            round = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
            phase++;
            round = FOURTH_ROUND;
            continue;
          }

          break;
        }

        if (((!value_decided) && (round == FOURTH_ROUND)) && timeout(round))
        {
          phase++;
          round = FIRST_ROUND;
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          continue;
        }

        break;
      }

      break;
    }

    if ((((!value_decided) && leader(phase)) && (round == FIRST_ROUND)) && (count(mbox, phase, FIRST_ROUND) > (n / 2)))
    {
      estimate = max_timestamp(mbox);
      round = SECOND_ROUND;
      send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
      round = THIRD_ROUND;
      mbox = havoc(phase, round);
      if (((((!value_decided) && leader(phase)) && (round == THIRD_ROUND)) && (count(mbox, phase, THIRD_ROUND) > (n / 2))) && (count_ack(mbox, phase) <= (n / 2)))
      {
        value_decided = false;
        phase++;
        round = FIRST_ROUND;
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
        continue;
      }

      if (((((!value_decided) && leader(phase)) && (round == THIRD_ROUND)) && (count(mbox, phase, THIRD_ROUND) > (n / 2))) && (count_ack(mbox, phase) > (n / 2)))
      {
        value_decided = true;
        round = FOURTH_ROUND;
        mbox = havoc(phase, round);
        if ((leader(phase) && value_decided) && (round == FOURTH_ROUND))
        {
          round = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round = FOURTH_ROUND;
          continue;
        }

        break;
      }

      if ((!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1))
      {
        estimate = m->estimate;
        value_decided = true;
        phase = max_phase_geq(mbox, phase, FOURTH_ROUND);
        round = FOURTH_ROUND;
        mbox = havoc(phase, round);
        if ((leader(phase) && value_decided) && (round == FOURTH_ROUND))
        {
          round = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round = FOURTH_ROUND;
          continue;
        }

        break;
      }

      if ((((!value_decided) && leader(phase)) && (round == THIRD_ROUND)) && timeout(round))
      {
        value_decided = false;
        phase++;
        round = FIRST_ROUND;
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
        continue;
      }

      break;
    }

    if ((leader(phase) && value_decided) && (round == FOURTH_ROUND))
    {
      round = FOURTH_ROUND;
      send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
      phase++;
      round = FOURTH_ROUND;
      continue;
    }

    if ((!value_decided) && (count_with_max_phase_geq(mbox, phase, FOURTH_ROUND) == 1))
    {
      estimate = m->estimate;
      value_decided = true;
      phase = max_phase_geq(mbox, phase, FOURTH_ROUND);
      round = FOURTH_ROUND;
      mbox = havoc(phase, round);
      if ((leader(phase) && value_decided) && (round == FOURTH_ROUND))
      {
        round = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        round = FOURTH_ROUND;
        continue;
      }

      break;
    }

    if ((((!value_decided) && leader(phase)) && (round == FIRST_ROUND)) && timeout(round))
    {
      value_decided = false;
      phase++;
      round = FIRST_ROUND;
      send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
      continue;
    }

  }

}


