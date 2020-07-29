struct msg
{
  int round;
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
int leader(int phase, int net_size);
int count(struct list *mbox, int phase, enum round_typ round, int from);
struct list *havoc(int phase, enum round_typ round);
_Bool timeout(enum round_typ round);
struct msg *message(int phase, enum round_typ round, int estimate, int p, int timestamp, _Bool decided);
_Bool value_decided(int p);
_Bool decide(int estimate);
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
    if (((((!value_decided(p)) && (p == leader(phase, n))) && (round == FIRST_ROUND)) && (count(mbox, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox, null_int(), FOURTH_ROUND, null_int()) == 0))
    {
      round_0 = SECOND_ROUND;
      m = max_timestamp(mbox);
      estimate = m->estimate;
      send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
      round_0 = THIRD_ROUND;
      mbox_0 = havoc(phase, round_0);
      if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == FIRST_ROUND)) && (count(mbox_0, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1 = SECOND_ROUND;
        m = max_timestamp(mbox_0);
        estimate = m->estimate;
        send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
        round_1 = THIRD_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == THIRD_ROUND)) && (count(mbox_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_0))
      {
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        decide(estimate);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == THIRD_ROUND)) && (count(mbox_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_0)))
      {
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
        round_1 = SECOND_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == SECOND_ROUND)) && (count(mbox_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1 = THIRD_ROUND;
        m = mbox_0->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1 = FOURTH_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == FOURTH_ROUND)) && (count(mbox_0, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_0->message->decided)
      {
        estimate = m->estimate;
        decide(estimate);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_0, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_0->message->decided) && (mbox_0->message->phase > phase))
      {
        round_1 = FOURTH_ROUND;
        estimate = m->estimate;
        decide(estimate);
        phase = mbox_0->message->phase + 1;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
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
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (value_decided(p) && (p == leader(phase, n)))
      {
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      continue;
    }

    if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round == THIRD_ROUND)) && (count(mbox, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox))
    {
      round_0 = FOURTH_ROUND;
      send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
      decide(estimate);
      phase++;
      round_0 = FIRST_ROUND;
      mbox_0 = havoc(phase, round_0);
      if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == FIRST_ROUND)) && (count(mbox_0, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1 = SECOND_ROUND;
        m = max_timestamp(mbox_0);
        estimate = m->estimate;
        send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
        round_1 = THIRD_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == THIRD_ROUND)) && (count(mbox_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_0))
      {
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        decide(estimate);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == THIRD_ROUND)) && (count(mbox_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_0)))
      {
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
        round_1 = SECOND_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == SECOND_ROUND)) && (count(mbox_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1 = THIRD_ROUND;
        m = mbox_0->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1 = FOURTH_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == FOURTH_ROUND)) && (count(mbox_0, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_0->message->decided)
      {
        estimate = m->estimate;
        decide(estimate);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_0, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_0->message->decided) && (mbox_0->message->phase > phase))
      {
        round_1 = FOURTH_ROUND;
        estimate = m->estimate;
        decide(estimate);
        phase = mbox_0->message->phase + 1;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
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
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (value_decided(p) && (p == leader(phase, n)))
      {
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      continue;
    }

    if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round == THIRD_ROUND)) && (count(mbox, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox)))
    {
      phase++;
      round_0 = FIRST_ROUND;
      mbox_0 = havoc(phase, round_0);
      if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == FIRST_ROUND)) && (count(mbox_0, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1 = SECOND_ROUND;
        m = max_timestamp(mbox_0);
        estimate = m->estimate;
        send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
        round_1 = THIRD_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == THIRD_ROUND)) && (count(mbox_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_0))
      {
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        decide(estimate);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == THIRD_ROUND)) && (count(mbox_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_0)))
      {
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
        round_1 = SECOND_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == SECOND_ROUND)) && (count(mbox_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1 = THIRD_ROUND;
        m = mbox_0->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1 = FOURTH_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == FOURTH_ROUND)) && (count(mbox_0, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_0->message->decided)
      {
        estimate = m->estimate;
        decide(estimate);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_0, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_0->message->decided) && (mbox_0->message->phase > phase))
      {
        round_1 = FOURTH_ROUND;
        estimate = m->estimate;
        decide(estimate);
        phase = mbox_0->message->phase + 1;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
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
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (value_decided(p) && (p == leader(phase, n)))
      {
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      continue;
    }

    if (((!value_decided(p)) && (p != leader(phase, n))) && (round == FIRST_ROUND))
    {
      send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
      round_0 = SECOND_ROUND;
      mbox_0 = havoc(phase, round_0);
      if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == FIRST_ROUND)) && (count(mbox_0, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1 = SECOND_ROUND;
        m = max_timestamp(mbox_0);
        estimate = m->estimate;
        send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
        round_1 = THIRD_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == THIRD_ROUND)) && (count(mbox_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_0))
      {
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        decide(estimate);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == THIRD_ROUND)) && (count(mbox_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_0)))
      {
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
        round_1 = SECOND_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == SECOND_ROUND)) && (count(mbox_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1 = THIRD_ROUND;
        m = mbox_0->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1 = FOURTH_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == FOURTH_ROUND)) && (count(mbox_0, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_0->message->decided)
      {
        estimate = m->estimate;
        decide(estimate);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_0, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_0->message->decided) && (mbox_0->message->phase > phase))
      {
        round_1 = FOURTH_ROUND;
        estimate = m->estimate;
        decide(estimate);
        phase = mbox_0->message->phase + 1;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
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
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (value_decided(p) && (p == leader(phase, n)))
      {
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      continue;
    }

    if (((((!value_decided(p)) && (p != leader(phase, n))) && (round == SECOND_ROUND)) && (count(mbox, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox, null_int(), FOURTH_ROUND, null_int()) == 0))
    {
      round_0 = THIRD_ROUND;
      m = mbox->message;
      estimate = m->estimate;
      timestamp = phase;
      send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
      round_0 = FOURTH_ROUND;
      mbox_0 = havoc(phase, round_0);
      if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == FIRST_ROUND)) && (count(mbox_0, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1 = SECOND_ROUND;
        m = max_timestamp(mbox_0);
        estimate = m->estimate;
        send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
        round_1 = THIRD_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == THIRD_ROUND)) && (count(mbox_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_0))
      {
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        decide(estimate);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == THIRD_ROUND)) && (count(mbox_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_0)))
      {
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
        round_1 = SECOND_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == SECOND_ROUND)) && (count(mbox_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1 = THIRD_ROUND;
        m = mbox_0->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1 = FOURTH_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == FOURTH_ROUND)) && (count(mbox_0, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_0->message->decided)
      {
        estimate = m->estimate;
        decide(estimate);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_0, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_0->message->decided) && (mbox_0->message->phase > phase))
      {
        round_1 = FOURTH_ROUND;
        estimate = m->estimate;
        decide(estimate);
        phase = mbox_0->message->phase + 1;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
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
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (value_decided(p) && (p == leader(phase, n)))
      {
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      continue;
    }

    if (((((!value_decided(p)) && (p != leader(phase, n))) && (round == FOURTH_ROUND)) && (count(mbox, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox->message->decided)
    {
      estimate = m->estimate;
      decide(estimate);
      phase++;
      round_0 = FIRST_ROUND;
      mbox_0 = havoc(phase, round_0);
      if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == FIRST_ROUND)) && (count(mbox_0, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1 = SECOND_ROUND;
        m = max_timestamp(mbox_0);
        estimate = m->estimate;
        send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
        round_1 = THIRD_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == THIRD_ROUND)) && (count(mbox_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_0))
      {
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        decide(estimate);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == THIRD_ROUND)) && (count(mbox_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_0)))
      {
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
        round_1 = SECOND_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == SECOND_ROUND)) && (count(mbox_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1 = THIRD_ROUND;
        m = mbox_0->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1 = FOURTH_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == FOURTH_ROUND)) && (count(mbox_0, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_0->message->decided)
      {
        estimate = m->estimate;
        decide(estimate);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_0, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_0->message->decided) && (mbox_0->message->phase > phase))
      {
        round_1 = FOURTH_ROUND;
        estimate = m->estimate;
        decide(estimate);
        phase = mbox_0->message->phase + 1;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
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
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (value_decided(p) && (p == leader(phase, n)))
      {
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      continue;
    }

    if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox->message->decided) && (mbox->message->phase > phase))
    {
      round_0 = FOURTH_ROUND;
      estimate = m->estimate;
      decide(estimate);
      phase = mbox->message->phase + 1;
      round_0 = FIRST_ROUND;
      mbox_0 = havoc(phase, round_0);
      if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == FIRST_ROUND)) && (count(mbox_0, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1 = SECOND_ROUND;
        m = max_timestamp(mbox_0);
        estimate = m->estimate;
        send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
        round_1 = THIRD_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == THIRD_ROUND)) && (count(mbox_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_0))
      {
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        decide(estimate);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == THIRD_ROUND)) && (count(mbox_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_0)))
      {
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
        round_1 = SECOND_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == SECOND_ROUND)) && (count(mbox_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1 = THIRD_ROUND;
        m = mbox_0->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1 = FOURTH_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == FOURTH_ROUND)) && (count(mbox_0, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_0->message->decided)
      {
        estimate = m->estimate;
        decide(estimate);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_0, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_0->message->decided) && (mbox_0->message->phase > phase))
      {
        round_1 = FOURTH_ROUND;
        estimate = m->estimate;
        decide(estimate);
        phase = mbox_0->message->phase + 1;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
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
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (value_decided(p) && (p == leader(phase, n)))
      {
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
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
      if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == FIRST_ROUND)) && (count(mbox_0, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1 = SECOND_ROUND;
        m = max_timestamp(mbox_0);
        estimate = m->estimate;
        send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
        round_1 = THIRD_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == THIRD_ROUND)) && (count(mbox_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_0))
      {
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        decide(estimate);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == THIRD_ROUND)) && (count(mbox_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_0)))
      {
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
        round_1 = SECOND_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == SECOND_ROUND)) && (count(mbox_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1 = THIRD_ROUND;
        m = mbox_0->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1 = FOURTH_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == FOURTH_ROUND)) && (count(mbox_0, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_0->message->decided)
      {
        estimate = m->estimate;
        decide(estimate);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_0, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_0->message->decided) && (mbox_0->message->phase > phase))
      {
        round_1 = FOURTH_ROUND;
        estimate = m->estimate;
        decide(estimate);
        phase = mbox_0->message->phase + 1;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
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
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (value_decided(p) && (p == leader(phase, n)))
      {
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      continue;
    }

    if (value_decided(p) && (p == leader(phase, n)))
    {
      round_0 = FOURTH_ROUND;
      send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
      phase++;
      round_0 = FIRST_ROUND;
      mbox_0 = havoc(phase, round_0);
      if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == FIRST_ROUND)) && (count(mbox_0, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1 = SECOND_ROUND;
        m = max_timestamp(mbox_0);
        estimate = m->estimate;
        send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
        round_1 = THIRD_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == THIRD_ROUND)) && (count(mbox_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_0))
      {
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        decide(estimate);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0 == THIRD_ROUND)) && (count(mbox_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_0)))
      {
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
        round_1 = SECOND_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == SECOND_ROUND)) && (count(mbox_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1 = THIRD_ROUND;
        m = mbox_0->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1 = FOURTH_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0 == FOURTH_ROUND)) && (count(mbox_0, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_0->message->decided)
      {
        estimate = m->estimate;
        decide(estimate);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_0, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_0->message->decided) && (mbox_0->message->phase > phase))
      {
        round_1 = FOURTH_ROUND;
        estimate = m->estimate;
        decide(estimate);
        phase = mbox_0->message->phase + 1;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
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
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (value_decided(p) && (p == leader(phase, n)))
      {
        round_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        round_1 = FIRST_ROUND;
        mbox_1 = havoc(phase, round_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == FIRST_ROUND)) && (count(mbox_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = SECOND_ROUND;
          m = max_timestamp(mbox_1);
          estimate = m->estimate;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1 == THIRD_ROUND)) && (count(mbox_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1)))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == SECOND_ROUND)) && (count(mbox_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2 = THIRD_ROUND;
          m = mbox_1->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1 == FOURTH_ROUND)) && (count(mbox_1, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1->message->decided) && (mbox_1->message->phase > phase))
        {
          round_2 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_1->message->phase + 1;
          round_2 = FIRST_ROUND;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1))
        {
          phase++;
          round_2 = FIRST_ROUND;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          round_2 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
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


