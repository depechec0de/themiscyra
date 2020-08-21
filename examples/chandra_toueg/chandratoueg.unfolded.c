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
struct msg *max_timestamp(struct list *mbox);
_Bool all_ack(struct list *mbox);
_Bool send(struct msg *message, int pid);
_Bool leader(int phase);
int leaderid(int phase);
struct list *havoc(int phase, enum round_typ round);
struct list *query(struct list *mbox, int phase, enum round_typ round);
int max_phase_recv(struct list *mbox);
_Bool timeout(enum round_typ round);
struct msg *message(int phase, enum round_typ round, int estimate, int p, int timestamp, _Bool decided);
_Bool value_decided(int p);
_Bool decide(int estimate);
int phase_matching(struct list *mbox, int current_phase, enum round_typ round, int size_to_count);
int phase_matching(struct list *mbox, int current_phase, enum round_typ round, int size_to_count)
{
  for (int i = current_phase; i <= max_phase_recv(mbox); i++)
  {
    if (query(mbox, i, round) >= size_to_count)
    {
      return i;
    }

  }

  return 0;
}

int main()
{
  struct list *mbox_2;
  struct list *mbox_1;
  struct list *mbox_0;
  enum round_typ round_2;
  enum round_typ round_1;
  enum round_typ round_0;
  int p;
  int n;
  int timestamp;
  int phase;
  enum round_typ round;
  int to_all = n + 1;
  int estimate;
  struct list *mbox;
  struct msg *m;
  phase = 1;
  round = FIRST_ROUND;
  estimate = in();
  timestamp = 0;
  while (1)
  {
    mbox = havoc(phase, round);
    if ((!value_decided(p)) && (round == FIRST_ROUND))
    {
      send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
      round_0 = SECOND_ROUND;
      mbox_0 = havoc(phase, round_0);
      if ((!value_decided(p)) && (round_0 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
        round_1 = SECOND_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((leader(phase) && (phase_matching(mbox_0, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
      {
        if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
        {
          phase = phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2);
          round_2 = FIRST_ROUND;
        }

        m = max_timestamp(mbox_0);
        estimate = m->estimate;
        round_1 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
        round_1 = THIRD_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((!leader(phase)) && (phase_matching(mbox_0, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
      {
        if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
        {
          phase = phase_matching(mbox_1, phase, SECOND_ROUND, 1);
          round_2 = SECOND_ROUND;
        }

        m = mbox_0->message;
        estimate = m->estimate;
        timestamp = phase;
        round_1 = THIRD_ROUND;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
        round_1 = FOURTH_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (leader(phase) && (phase_matching(mbox_0, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
      {
        if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
        {
          phase = phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2);
          round_2 = THIRD_ROUND;
        }

        decide(estimate);
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((!leader(phase)) && (phase_matching(mbox_0, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
      {
        if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
        {
          phase = phase_matching(mbox_1, phase, FOURTH_ROUND, 1);
          round_2 = FOURTH_ROUND;
        }

        if (mbox->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
        }

        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (leader(phase) && value_decided(p))
      {
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((!value_decided(p)) && timeout(round_0))
      {
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      continue;
    }

    if ((leader(phase) && (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
    {
      if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
      {
        phase = phase_matching(mbox_0, phase, FIRST_ROUND, (n - 1) / 2);
        round_1 = FIRST_ROUND;
      }

      m = max_timestamp(mbox);
      estimate = m->estimate;
      round_0 = SECOND_ROUND;
      send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
      round_0 = THIRD_ROUND;
      mbox_0 = havoc(phase, round_0);
      if ((!value_decided(p)) && (round_0 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
        round_1 = SECOND_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((leader(phase) && (phase_matching(mbox_0, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
      {
        if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
        {
          phase = phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2);
          round_2 = FIRST_ROUND;
        }

        m = max_timestamp(mbox_0);
        estimate = m->estimate;
        round_1 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
        round_1 = THIRD_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((!leader(phase)) && (phase_matching(mbox_0, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
      {
        if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
        {
          phase = phase_matching(mbox_1, phase, SECOND_ROUND, 1);
          round_2 = SECOND_ROUND;
        }

        m = mbox_0->message;
        estimate = m->estimate;
        timestamp = phase;
        round_1 = THIRD_ROUND;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
        round_1 = FOURTH_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (leader(phase) && (phase_matching(mbox_0, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
      {
        if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
        {
          phase = phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2);
          round_2 = THIRD_ROUND;
        }

        decide(estimate);
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((!leader(phase)) && (phase_matching(mbox_0, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
      {
        if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
        {
          phase = phase_matching(mbox_1, phase, FOURTH_ROUND, 1);
          round_2 = FOURTH_ROUND;
        }

        if (mbox->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
        }

        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (leader(phase) && value_decided(p))
      {
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((!value_decided(p)) && timeout(round_0))
      {
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      continue;
    }

    if (((!leader(phase)) && (phase_matching(mbox, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
    {
      if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
      {
        phase = phase_matching(mbox_0, phase, SECOND_ROUND, 1);
        round_1 = SECOND_ROUND;
      }

      m = mbox->message;
      estimate = m->estimate;
      timestamp = phase;
      round_0 = THIRD_ROUND;
      send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
      round_0 = FOURTH_ROUND;
      mbox_0 = havoc(phase, round_0);
      if ((!value_decided(p)) && (round_0 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
        round_1 = SECOND_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((leader(phase) && (phase_matching(mbox_0, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
      {
        if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
        {
          phase = phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2);
          round_2 = FIRST_ROUND;
        }

        m = max_timestamp(mbox_0);
        estimate = m->estimate;
        round_1 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
        round_1 = THIRD_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((!leader(phase)) && (phase_matching(mbox_0, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
      {
        if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
        {
          phase = phase_matching(mbox_1, phase, SECOND_ROUND, 1);
          round_2 = SECOND_ROUND;
        }

        m = mbox_0->message;
        estimate = m->estimate;
        timestamp = phase;
        round_1 = THIRD_ROUND;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
        round_1 = FOURTH_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (leader(phase) && (phase_matching(mbox_0, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
      {
        if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
        {
          phase = phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2);
          round_2 = THIRD_ROUND;
        }

        decide(estimate);
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((!leader(phase)) && (phase_matching(mbox_0, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
      {
        if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
        {
          phase = phase_matching(mbox_1, phase, FOURTH_ROUND, 1);
          round_2 = FOURTH_ROUND;
        }

        if (mbox->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
        }

        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (leader(phase) && value_decided(p))
      {
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((!value_decided(p)) && timeout(round_0))
      {
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      continue;
    }

    if (leader(phase) && (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
    {
      if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
      {
        phase = phase_matching(mbox_0, phase, THIRD_ROUND, (n - 1) / 2);
        round_1 = THIRD_ROUND;
      }

      decide(estimate);
      round_0 = FOURTH_ROUND;
      send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
      phase++;
      round_0 = FIRST_ROUND;
      mbox_0 = havoc(phase, round_0);
      if ((!value_decided(p)) && (round_0 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
        round_1 = SECOND_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((leader(phase) && (phase_matching(mbox_0, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
      {
        if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
        {
          phase = phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2);
          round_2 = FIRST_ROUND;
        }

        m = max_timestamp(mbox_0);
        estimate = m->estimate;
        round_1 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
        round_1 = THIRD_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((!leader(phase)) && (phase_matching(mbox_0, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
      {
        if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
        {
          phase = phase_matching(mbox_1, phase, SECOND_ROUND, 1);
          round_2 = SECOND_ROUND;
        }

        m = mbox_0->message;
        estimate = m->estimate;
        timestamp = phase;
        round_1 = THIRD_ROUND;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
        round_1 = FOURTH_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (leader(phase) && (phase_matching(mbox_0, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
      {
        if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
        {
          phase = phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2);
          round_2 = THIRD_ROUND;
        }

        decide(estimate);
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((!leader(phase)) && (phase_matching(mbox_0, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
      {
        if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
        {
          phase = phase_matching(mbox_1, phase, FOURTH_ROUND, 1);
          round_2 = FOURTH_ROUND;
        }

        if (mbox->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
        }

        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (leader(phase) && value_decided(p))
      {
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((!value_decided(p)) && timeout(round_0))
      {
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      continue;
    }

    if (((!leader(phase)) && (phase_matching(mbox, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
    {
      if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
      {
        phase = phase_matching(mbox_0, phase, FOURTH_ROUND, 1);
        round_1 = FOURTH_ROUND;
      }

      if (mbox->message->decided)
      {
        estimate = m->estimate;
        decide(estimate);
      }

      phase++;
      round_0 = FIRST_ROUND;
      mbox_0 = havoc(phase, round_0);
      if ((!value_decided(p)) && (round_0 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
        round_1 = SECOND_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((leader(phase) && (phase_matching(mbox_0, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
      {
        if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
        {
          phase = phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2);
          round_2 = FIRST_ROUND;
        }

        m = max_timestamp(mbox_0);
        estimate = m->estimate;
        round_1 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
        round_1 = THIRD_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((!leader(phase)) && (phase_matching(mbox_0, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
      {
        if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
        {
          phase = phase_matching(mbox_1, phase, SECOND_ROUND, 1);
          round_2 = SECOND_ROUND;
        }

        m = mbox_0->message;
        estimate = m->estimate;
        timestamp = phase;
        round_1 = THIRD_ROUND;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
        round_1 = FOURTH_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (leader(phase) && (phase_matching(mbox_0, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
      {
        if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
        {
          phase = phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2);
          round_2 = THIRD_ROUND;
        }

        decide(estimate);
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((!leader(phase)) && (phase_matching(mbox_0, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
      {
        if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
        {
          phase = phase_matching(mbox_1, phase, FOURTH_ROUND, 1);
          round_2 = FOURTH_ROUND;
        }

        if (mbox->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
        }

        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (leader(phase) && value_decided(p))
      {
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((!value_decided(p)) && timeout(round_0))
      {
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      continue;
    }

    if (leader(phase) && value_decided(p))
    {
      round_0 = FOURTH_ROUND;
      send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
      phase++;
      round_0 = FIRST_ROUND;
      mbox_0 = havoc(phase, round_0);
      if ((!value_decided(p)) && (round_0 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
        round_1 = SECOND_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((leader(phase) && (phase_matching(mbox_0, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
      {
        if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
        {
          phase = phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2);
          round_2 = FIRST_ROUND;
        }

        m = max_timestamp(mbox_0);
        estimate = m->estimate;
        round_1 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
        round_1 = THIRD_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((!leader(phase)) && (phase_matching(mbox_0, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
      {
        if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
        {
          phase = phase_matching(mbox_1, phase, SECOND_ROUND, 1);
          round_2 = SECOND_ROUND;
        }

        m = mbox_0->message;
        estimate = m->estimate;
        timestamp = phase;
        round_1 = THIRD_ROUND;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
        round_1 = FOURTH_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (leader(phase) && (phase_matching(mbox_0, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
      {
        if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
        {
          phase = phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2);
          round_2 = THIRD_ROUND;
        }

        decide(estimate);
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((!leader(phase)) && (phase_matching(mbox_0, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
      {
        if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
        {
          phase = phase_matching(mbox_1, phase, FOURTH_ROUND, 1);
          round_2 = FOURTH_ROUND;
        }

        if (mbox->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
        }

        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (leader(phase) && value_decided(p))
      {
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((!value_decided(p)) && timeout(round_0))
      {
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      continue;
    }

    if ((!value_decided(p)) && timeout(round))
    {
      phase++;
      round_0 = FIRST_ROUND;
      mbox_0 = havoc(phase, round_0);
      if ((!value_decided(p)) && (round_0 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
        round_1 = SECOND_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((leader(phase) && (phase_matching(mbox_0, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
      {
        if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
        {
          phase = phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2);
          round_2 = FIRST_ROUND;
        }

        m = max_timestamp(mbox_0);
        estimate = m->estimate;
        round_1 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
        round_1 = THIRD_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((!leader(phase)) && (phase_matching(mbox_0, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
      {
        if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
        {
          phase = phase_matching(mbox_1, phase, SECOND_ROUND, 1);
          round_2 = SECOND_ROUND;
        }

        m = mbox_0->message;
        estimate = m->estimate;
        timestamp = phase;
        round_1 = THIRD_ROUND;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
        round_1 = FOURTH_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (leader(phase) && (phase_matching(mbox_0, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
      {
        if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
        {
          phase = phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2);
          round_2 = THIRD_ROUND;
        }

        decide(estimate);
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((!leader(phase)) && (phase_matching(mbox_0, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
      {
        if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
        {
          phase = phase_matching(mbox_1, phase, FOURTH_ROUND, 1);
          round_2 = FOURTH_ROUND;
        }

        if (mbox->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
        }

        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (leader(phase) && value_decided(p))
      {
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((!value_decided(p)) && timeout(round_0))
      {
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if ((!value_decided(p)) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leaderid(phase));
          round_2 = SECOND_ROUND;
          continue;
        }

        if ((leader(phase) && (phase_matching(mbox_1, phase, FIRST_ROUND, (n - 1) / 2) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, FIRST_ROUND, (n - 1) / 2);
            round = FIRST_ROUND;
          }

          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          round_2 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, SECOND_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, SECOND_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, SECOND_ROUND, 1);
            round = SECOND_ROUND;
          }

          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          round_2 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leaderid(phase));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (leader(phase) && (phase_matching(mbox_1, phase, THIRD_ROUND, (n - 1) / 2) >= phase))
        {
          if (phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2) > phase)
          {
            phase = phase_matching(mbox, phase, THIRD_ROUND, (n - 1) / 2);
            round = THIRD_ROUND;
          }

          decide(estimate);
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!leader(phase)) && (phase_matching(mbox_1, phase, FOURTH_ROUND, 1) >= phase)) && (!value_decided(phase)))
        {
          if (phase_matching(mbox, phase, FOURTH_ROUND, 1) > phase)
          {
            phase = phase_matching(mbox, phase, FOURTH_ROUND, 1);
            round = FOURTH_ROUND;
          }

          if (mbox->message->decided)
          {
            estimate = m->estimate;
            decide(estimate);
          }

          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (leader(phase) && value_decided(p))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      continue;
    }

  }

}


