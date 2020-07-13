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
  struct list *mbox_2_8;
  struct list *mbox_2_7;
  struct list *mbox_2_6;
  struct list *mbox_2_5;
  struct list *mbox_2_4;
  struct list *mbox_2_3;
  struct list *mbox_2_2;
  struct list *mbox_2_1;
  struct list *mbox_2_0;
  struct list *mbox_1_8;
  struct list *mbox_1_7;
  struct list *mbox_1_6;
  struct list *mbox_1_5;
  struct list *mbox_1_4;
  struct list *mbox_1_3;
  struct list *mbox_1_2;
  struct list *mbox_1_1;
  struct list *mbox_1_0;
  struct list *mbox_0_8;
  struct list *mbox_0_7;
  struct list *mbox_0_6;
  struct list *mbox_0_5;
  struct list *mbox_0_4;
  struct list *mbox_0_3;
  struct list *mbox_0_2;
  struct list *mbox_0_1;
  struct list *mbox_0_0;
  enum round_typ round_2_8;
  enum round_typ round_2_7;
  enum round_typ round_2_6;
  enum round_typ round_2_5;
  enum round_typ round_2_4;
  enum round_typ round_2_3;
  enum round_typ round_2_2;
  enum round_typ round_2_1;
  enum round_typ round_2_0;
  enum round_typ round_1_8;
  enum round_typ round_1_7;
  enum round_typ round_1_6;
  enum round_typ round_1_5;
  enum round_typ round_1_4;
  enum round_typ round_1_3;
  enum round_typ round_1_2;
  enum round_typ round_1_1;
  enum round_typ round_1_0;
  enum round_typ round_0_8;
  enum round_typ round_0_7;
  enum round_typ round_0_6;
  enum round_typ round_0_5;
  enum round_typ round_0_4;
  enum round_typ round_0_3;
  enum round_typ round_0_2;
  enum round_typ round_0_1;
  enum round_typ round_0_0;
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
      m = max_timestamp(mbox_0_0);
      estimate = m->estimate;
      round_0_0 = SECOND_ROUND;
      send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
      round_0_0 = THIRD_ROUND;
      mbox_0_0 = havoc(phase, round_0_0);
      if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_0 == FIRST_ROUND)) && (count(mbox_0_0, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_0, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        m = max_timestamp(mbox_1_0);
        estimate = m->estimate;
        round_1_0 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
        round_1_0 = THIRD_ROUND;
        mbox_1_0 = havoc(phase, round_1_0);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_0 == FIRST_ROUND)) && (count(mbox_1_0, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_0))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_0)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_0 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_0 == SECOND_ROUND)) && (count(mbox_1_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_0->message->decided) && (mbox_1_0->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_0 == THIRD_ROUND)) && (count(mbox_0_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_0_0))
      {
        round_1_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        decide(estimate);
        phase++;
        mbox_1_1 = havoc(phase, round_1_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_1 == FIRST_ROUND)) && (count(mbox_1_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_1))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_1)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_1 == SECOND_ROUND)) && (count(mbox_1_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_1->message->decided) && (mbox_1_1->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_0 == THIRD_ROUND)) && (count(mbox_0_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_0_0)))
      {
        round_1_2 = FIRST_ROUND;
        phase++;
        mbox_1_2 = havoc(phase, round_1_2);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_2 == FIRST_ROUND)) && (count(mbox_1_2, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_2))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_2)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_2 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_2 == SECOND_ROUND)) && (count(mbox_1_2, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_2->message->decided) && (mbox_1_2->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (((!value_decided(p)) && (p != leader(phase, n))) && (round_0_0 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
        round_1_3 = SECOND_ROUND;
        mbox_1_3 = havoc(phase, round_1_3);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_3 == FIRST_ROUND)) && (count(mbox_1_3, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_3))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_3)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_3 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_3 == SECOND_ROUND)) && (count(mbox_1_3, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_3->message->decided) && (mbox_1_3->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0_0 == SECOND_ROUND)) && (count(mbox_0_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0_0, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1_4 = THIRD_ROUND;
        m = mbox_1_4->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1_4 = FOURTH_ROUND;
        mbox_1_4 = havoc(phase, round_1_4);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_4 == FIRST_ROUND)) && (count(mbox_1_4, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_4))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_4)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_4 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_4 == SECOND_ROUND)) && (count(mbox_1_4, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_4->message->decided) && (mbox_1_4->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_0_0, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_0_0->message->decided) && (mbox_0_0->message->phase >= phase))
      {
        estimate = m->estimate;
        decide(estimate);
        phase = mbox_1_5->message->phase;
        mbox_1_5 = havoc(phase, round_1_5);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_5 == FIRST_ROUND)) && (count(mbox_1_5, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_5))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_5)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_5 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_5 == SECOND_ROUND)) && (count(mbox_1_5, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_5->message->decided) && (mbox_1_5->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if ((!value_decided(p)) && timeout(round_0_0))
      {
        round_1_6 = FIRST_ROUND;
        phase++;
        mbox_1_6 = havoc(phase, round_1_6);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_6 == FIRST_ROUND)) && (count(mbox_1_6, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_6))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_6)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_6 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_6 == SECOND_ROUND)) && (count(mbox_1_6, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_6->message->decided) && (mbox_1_6->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (value_decided(p) && (p == leader(phase, n)))
      {
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        mbox_1_7 = havoc(phase, round_1_7);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_7 == FIRST_ROUND)) && (count(mbox_1_7, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_7))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_7)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_7 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_7 == SECOND_ROUND)) && (count(mbox_1_7, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_7->message->decided) && (mbox_1_7->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      continue;
    }

    if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round == THIRD_ROUND)) && (count(mbox, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox))
    {
      round_0_1 = FOURTH_ROUND;
      send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
      decide(estimate);
      phase++;
      mbox_0_1 = havoc(phase, round_0_1);
      if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_1 == FIRST_ROUND)) && (count(mbox_0_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_1, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        m = max_timestamp(mbox_1_0);
        estimate = m->estimate;
        round_1_0 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
        round_1_0 = THIRD_ROUND;
        mbox_1_0 = havoc(phase, round_1_0);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_0 == FIRST_ROUND)) && (count(mbox_1_0, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_0))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_0)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_0 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_0 == SECOND_ROUND)) && (count(mbox_1_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_0->message->decided) && (mbox_1_0->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_1 == THIRD_ROUND)) && (count(mbox_0_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_0_1))
      {
        round_1_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        decide(estimate);
        phase++;
        mbox_1_1 = havoc(phase, round_1_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_1 == FIRST_ROUND)) && (count(mbox_1_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_1))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_1)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_1 == SECOND_ROUND)) && (count(mbox_1_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_1->message->decided) && (mbox_1_1->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_1 == THIRD_ROUND)) && (count(mbox_0_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_0_1)))
      {
        round_1_2 = FIRST_ROUND;
        phase++;
        mbox_1_2 = havoc(phase, round_1_2);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_2 == FIRST_ROUND)) && (count(mbox_1_2, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_2))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_2)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_2 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_2 == SECOND_ROUND)) && (count(mbox_1_2, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_2->message->decided) && (mbox_1_2->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (((!value_decided(p)) && (p != leader(phase, n))) && (round_0_1 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
        round_1_3 = SECOND_ROUND;
        mbox_1_3 = havoc(phase, round_1_3);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_3 == FIRST_ROUND)) && (count(mbox_1_3, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_3))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_3)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_3 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_3 == SECOND_ROUND)) && (count(mbox_1_3, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_3->message->decided) && (mbox_1_3->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0_1 == SECOND_ROUND)) && (count(mbox_0_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0_1, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1_4 = THIRD_ROUND;
        m = mbox_1_4->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1_4 = FOURTH_ROUND;
        mbox_1_4 = havoc(phase, round_1_4);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_4 == FIRST_ROUND)) && (count(mbox_1_4, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_4))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_4)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_4 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_4 == SECOND_ROUND)) && (count(mbox_1_4, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_4->message->decided) && (mbox_1_4->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_0_1, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_0_1->message->decided) && (mbox_0_1->message->phase >= phase))
      {
        estimate = m->estimate;
        decide(estimate);
        phase = mbox_1_5->message->phase;
        mbox_1_5 = havoc(phase, round_1_5);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_5 == FIRST_ROUND)) && (count(mbox_1_5, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_5))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_5)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_5 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_5 == SECOND_ROUND)) && (count(mbox_1_5, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_5->message->decided) && (mbox_1_5->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if ((!value_decided(p)) && timeout(round_0_1))
      {
        round_1_6 = FIRST_ROUND;
        phase++;
        mbox_1_6 = havoc(phase, round_1_6);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_6 == FIRST_ROUND)) && (count(mbox_1_6, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_6))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_6)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_6 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_6 == SECOND_ROUND)) && (count(mbox_1_6, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_6->message->decided) && (mbox_1_6->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (value_decided(p) && (p == leader(phase, n)))
      {
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        mbox_1_7 = havoc(phase, round_1_7);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_7 == FIRST_ROUND)) && (count(mbox_1_7, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_7))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_7)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_7 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_7 == SECOND_ROUND)) && (count(mbox_1_7, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_7->message->decided) && (mbox_1_7->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      continue;
    }

    if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round == THIRD_ROUND)) && (count(mbox, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox)))
    {
      round_0_2 = FIRST_ROUND;
      phase++;
      mbox_0_2 = havoc(phase, round_0_2);
      if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_2 == FIRST_ROUND)) && (count(mbox_0_2, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_2, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        m = max_timestamp(mbox_1_0);
        estimate = m->estimate;
        round_1_0 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
        round_1_0 = THIRD_ROUND;
        mbox_1_0 = havoc(phase, round_1_0);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_0 == FIRST_ROUND)) && (count(mbox_1_0, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_0))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_0)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_0 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_0 == SECOND_ROUND)) && (count(mbox_1_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_0->message->decided) && (mbox_1_0->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_2 == THIRD_ROUND)) && (count(mbox_0_2, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_2, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_0_2))
      {
        round_1_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        decide(estimate);
        phase++;
        mbox_1_1 = havoc(phase, round_1_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_1 == FIRST_ROUND)) && (count(mbox_1_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_1))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_1)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_1 == SECOND_ROUND)) && (count(mbox_1_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_1->message->decided) && (mbox_1_1->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_2 == THIRD_ROUND)) && (count(mbox_0_2, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_2, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_0_2)))
      {
        round_1_2 = FIRST_ROUND;
        phase++;
        mbox_1_2 = havoc(phase, round_1_2);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_2 == FIRST_ROUND)) && (count(mbox_1_2, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_2))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_2)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_2 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_2 == SECOND_ROUND)) && (count(mbox_1_2, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_2->message->decided) && (mbox_1_2->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (((!value_decided(p)) && (p != leader(phase, n))) && (round_0_2 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
        round_1_3 = SECOND_ROUND;
        mbox_1_3 = havoc(phase, round_1_3);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_3 == FIRST_ROUND)) && (count(mbox_1_3, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_3))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_3)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_3 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_3 == SECOND_ROUND)) && (count(mbox_1_3, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_3->message->decided) && (mbox_1_3->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0_2 == SECOND_ROUND)) && (count(mbox_0_2, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0_2, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1_4 = THIRD_ROUND;
        m = mbox_1_4->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1_4 = FOURTH_ROUND;
        mbox_1_4 = havoc(phase, round_1_4);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_4 == FIRST_ROUND)) && (count(mbox_1_4, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_4))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_4)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_4 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_4 == SECOND_ROUND)) && (count(mbox_1_4, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_4->message->decided) && (mbox_1_4->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_0_2, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_0_2->message->decided) && (mbox_0_2->message->phase >= phase))
      {
        estimate = m->estimate;
        decide(estimate);
        phase = mbox_1_5->message->phase;
        mbox_1_5 = havoc(phase, round_1_5);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_5 == FIRST_ROUND)) && (count(mbox_1_5, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_5))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_5)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_5 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_5 == SECOND_ROUND)) && (count(mbox_1_5, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_5->message->decided) && (mbox_1_5->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if ((!value_decided(p)) && timeout(round_0_2))
      {
        round_1_6 = FIRST_ROUND;
        phase++;
        mbox_1_6 = havoc(phase, round_1_6);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_6 == FIRST_ROUND)) && (count(mbox_1_6, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_6))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_6)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_6 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_6 == SECOND_ROUND)) && (count(mbox_1_6, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_6->message->decided) && (mbox_1_6->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (value_decided(p) && (p == leader(phase, n)))
      {
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        mbox_1_7 = havoc(phase, round_1_7);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_7 == FIRST_ROUND)) && (count(mbox_1_7, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_7))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_7)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_7 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_7 == SECOND_ROUND)) && (count(mbox_1_7, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_7->message->decided) && (mbox_1_7->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      continue;
    }

    if (((!value_decided(p)) && (p != leader(phase, n))) && (round == FIRST_ROUND))
    {
      send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
      round_0_3 = SECOND_ROUND;
      mbox_0_3 = havoc(phase, round_0_3);
      if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_3 == FIRST_ROUND)) && (count(mbox_0_3, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_3, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        m = max_timestamp(mbox_1_0);
        estimate = m->estimate;
        round_1_0 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
        round_1_0 = THIRD_ROUND;
        mbox_1_0 = havoc(phase, round_1_0);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_0 == FIRST_ROUND)) && (count(mbox_1_0, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_0))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_0)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_0 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_0 == SECOND_ROUND)) && (count(mbox_1_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_0->message->decided) && (mbox_1_0->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_3 == THIRD_ROUND)) && (count(mbox_0_3, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_3, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_0_3))
      {
        round_1_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        decide(estimate);
        phase++;
        mbox_1_1 = havoc(phase, round_1_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_1 == FIRST_ROUND)) && (count(mbox_1_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_1))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_1)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_1 == SECOND_ROUND)) && (count(mbox_1_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_1->message->decided) && (mbox_1_1->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_3 == THIRD_ROUND)) && (count(mbox_0_3, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_3, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_0_3)))
      {
        round_1_2 = FIRST_ROUND;
        phase++;
        mbox_1_2 = havoc(phase, round_1_2);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_2 == FIRST_ROUND)) && (count(mbox_1_2, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_2))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_2)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_2 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_2 == SECOND_ROUND)) && (count(mbox_1_2, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_2->message->decided) && (mbox_1_2->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (((!value_decided(p)) && (p != leader(phase, n))) && (round_0_3 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
        round_1_3 = SECOND_ROUND;
        mbox_1_3 = havoc(phase, round_1_3);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_3 == FIRST_ROUND)) && (count(mbox_1_3, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_3))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_3)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_3 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_3 == SECOND_ROUND)) && (count(mbox_1_3, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_3->message->decided) && (mbox_1_3->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0_3 == SECOND_ROUND)) && (count(mbox_0_3, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0_3, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1_4 = THIRD_ROUND;
        m = mbox_1_4->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1_4 = FOURTH_ROUND;
        mbox_1_4 = havoc(phase, round_1_4);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_4 == FIRST_ROUND)) && (count(mbox_1_4, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_4))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_4)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_4 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_4 == SECOND_ROUND)) && (count(mbox_1_4, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_4->message->decided) && (mbox_1_4->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_0_3, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_0_3->message->decided) && (mbox_0_3->message->phase >= phase))
      {
        estimate = m->estimate;
        decide(estimate);
        phase = mbox_1_5->message->phase;
        mbox_1_5 = havoc(phase, round_1_5);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_5 == FIRST_ROUND)) && (count(mbox_1_5, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_5))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_5)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_5 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_5 == SECOND_ROUND)) && (count(mbox_1_5, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_5->message->decided) && (mbox_1_5->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if ((!value_decided(p)) && timeout(round_0_3))
      {
        round_1_6 = FIRST_ROUND;
        phase++;
        mbox_1_6 = havoc(phase, round_1_6);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_6 == FIRST_ROUND)) && (count(mbox_1_6, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_6))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_6)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_6 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_6 == SECOND_ROUND)) && (count(mbox_1_6, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_6->message->decided) && (mbox_1_6->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (value_decided(p) && (p == leader(phase, n)))
      {
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        mbox_1_7 = havoc(phase, round_1_7);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_7 == FIRST_ROUND)) && (count(mbox_1_7, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_7))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_7)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_7 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_7 == SECOND_ROUND)) && (count(mbox_1_7, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_7->message->decided) && (mbox_1_7->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      continue;
    }

    if (((((!value_decided(p)) && (p != leader(phase, n))) && (round == SECOND_ROUND)) && (count(mbox, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox, null_int(), FOURTH_ROUND, null_int()) == 0))
    {
      round_0_4 = THIRD_ROUND;
      m = mbox_0_4->message;
      estimate = m->estimate;
      timestamp = phase;
      send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
      round_0_4 = FOURTH_ROUND;
      mbox_0_4 = havoc(phase, round_0_4);
      if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_4 == FIRST_ROUND)) && (count(mbox_0_4, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_4, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        m = max_timestamp(mbox_1_0);
        estimate = m->estimate;
        round_1_0 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
        round_1_0 = THIRD_ROUND;
        mbox_1_0 = havoc(phase, round_1_0);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_0 == FIRST_ROUND)) && (count(mbox_1_0, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_0))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_0)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_0 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_0 == SECOND_ROUND)) && (count(mbox_1_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_0->message->decided) && (mbox_1_0->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_4 == THIRD_ROUND)) && (count(mbox_0_4, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_4, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_0_4))
      {
        round_1_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        decide(estimate);
        phase++;
        mbox_1_1 = havoc(phase, round_1_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_1 == FIRST_ROUND)) && (count(mbox_1_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_1))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_1)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_1 == SECOND_ROUND)) && (count(mbox_1_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_1->message->decided) && (mbox_1_1->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_4 == THIRD_ROUND)) && (count(mbox_0_4, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_4, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_0_4)))
      {
        round_1_2 = FIRST_ROUND;
        phase++;
        mbox_1_2 = havoc(phase, round_1_2);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_2 == FIRST_ROUND)) && (count(mbox_1_2, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_2))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_2)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_2 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_2 == SECOND_ROUND)) && (count(mbox_1_2, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_2->message->decided) && (mbox_1_2->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (((!value_decided(p)) && (p != leader(phase, n))) && (round_0_4 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
        round_1_3 = SECOND_ROUND;
        mbox_1_3 = havoc(phase, round_1_3);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_3 == FIRST_ROUND)) && (count(mbox_1_3, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_3))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_3)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_3 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_3 == SECOND_ROUND)) && (count(mbox_1_3, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_3->message->decided) && (mbox_1_3->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0_4 == SECOND_ROUND)) && (count(mbox_0_4, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0_4, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1_4 = THIRD_ROUND;
        m = mbox_1_4->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1_4 = FOURTH_ROUND;
        mbox_1_4 = havoc(phase, round_1_4);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_4 == FIRST_ROUND)) && (count(mbox_1_4, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_4))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_4)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_4 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_4 == SECOND_ROUND)) && (count(mbox_1_4, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_4->message->decided) && (mbox_1_4->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_0_4, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_0_4->message->decided) && (mbox_0_4->message->phase >= phase))
      {
        estimate = m->estimate;
        decide(estimate);
        phase = mbox_1_5->message->phase;
        mbox_1_5 = havoc(phase, round_1_5);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_5 == FIRST_ROUND)) && (count(mbox_1_5, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_5))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_5)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_5 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_5 == SECOND_ROUND)) && (count(mbox_1_5, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_5->message->decided) && (mbox_1_5->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if ((!value_decided(p)) && timeout(round_0_4))
      {
        round_1_6 = FIRST_ROUND;
        phase++;
        mbox_1_6 = havoc(phase, round_1_6);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_6 == FIRST_ROUND)) && (count(mbox_1_6, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_6))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_6)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_6 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_6 == SECOND_ROUND)) && (count(mbox_1_6, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_6->message->decided) && (mbox_1_6->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (value_decided(p) && (p == leader(phase, n)))
      {
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        mbox_1_7 = havoc(phase, round_1_7);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_7 == FIRST_ROUND)) && (count(mbox_1_7, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_7))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_7)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_7 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_7 == SECOND_ROUND)) && (count(mbox_1_7, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_7->message->decided) && (mbox_1_7->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      continue;
    }

    if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox->message->decided) && (mbox->message->phase >= phase))
    {
      estimate = m->estimate;
      decide(estimate);
      phase = mbox_0_5->message->phase;
      mbox_0_5 = havoc(phase, round_0_5);
      if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_5 == FIRST_ROUND)) && (count(mbox_0_5, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_5, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        m = max_timestamp(mbox_1_0);
        estimate = m->estimate;
        round_1_0 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
        round_1_0 = THIRD_ROUND;
        mbox_1_0 = havoc(phase, round_1_0);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_0 == FIRST_ROUND)) && (count(mbox_1_0, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_0))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_0)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_0 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_0 == SECOND_ROUND)) && (count(mbox_1_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_0->message->decided) && (mbox_1_0->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_5 == THIRD_ROUND)) && (count(mbox_0_5, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_5, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_0_5))
      {
        round_1_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        decide(estimate);
        phase++;
        mbox_1_1 = havoc(phase, round_1_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_1 == FIRST_ROUND)) && (count(mbox_1_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_1))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_1)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_1 == SECOND_ROUND)) && (count(mbox_1_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_1->message->decided) && (mbox_1_1->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_5 == THIRD_ROUND)) && (count(mbox_0_5, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_5, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_0_5)))
      {
        round_1_2 = FIRST_ROUND;
        phase++;
        mbox_1_2 = havoc(phase, round_1_2);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_2 == FIRST_ROUND)) && (count(mbox_1_2, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_2))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_2)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_2 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_2 == SECOND_ROUND)) && (count(mbox_1_2, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_2->message->decided) && (mbox_1_2->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (((!value_decided(p)) && (p != leader(phase, n))) && (round_0_5 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
        round_1_3 = SECOND_ROUND;
        mbox_1_3 = havoc(phase, round_1_3);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_3 == FIRST_ROUND)) && (count(mbox_1_3, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_3))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_3)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_3 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_3 == SECOND_ROUND)) && (count(mbox_1_3, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_3->message->decided) && (mbox_1_3->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0_5 == SECOND_ROUND)) && (count(mbox_0_5, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0_5, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1_4 = THIRD_ROUND;
        m = mbox_1_4->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1_4 = FOURTH_ROUND;
        mbox_1_4 = havoc(phase, round_1_4);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_4 == FIRST_ROUND)) && (count(mbox_1_4, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_4))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_4)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_4 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_4 == SECOND_ROUND)) && (count(mbox_1_4, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_4->message->decided) && (mbox_1_4->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_0_5, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_0_5->message->decided) && (mbox_0_5->message->phase >= phase))
      {
        estimate = m->estimate;
        decide(estimate);
        phase = mbox_1_5->message->phase;
        mbox_1_5 = havoc(phase, round_1_5);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_5 == FIRST_ROUND)) && (count(mbox_1_5, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_5))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_5)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_5 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_5 == SECOND_ROUND)) && (count(mbox_1_5, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_5->message->decided) && (mbox_1_5->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if ((!value_decided(p)) && timeout(round_0_5))
      {
        round_1_6 = FIRST_ROUND;
        phase++;
        mbox_1_6 = havoc(phase, round_1_6);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_6 == FIRST_ROUND)) && (count(mbox_1_6, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_6))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_6)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_6 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_6 == SECOND_ROUND)) && (count(mbox_1_6, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_6->message->decided) && (mbox_1_6->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (value_decided(p) && (p == leader(phase, n)))
      {
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        mbox_1_7 = havoc(phase, round_1_7);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_7 == FIRST_ROUND)) && (count(mbox_1_7, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_7))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_7)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_7 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_7 == SECOND_ROUND)) && (count(mbox_1_7, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_7->message->decided) && (mbox_1_7->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      continue;
    }

    if ((!value_decided(p)) && timeout(round))
    {
      round_0_6 = FIRST_ROUND;
      phase++;
      mbox_0_6 = havoc(phase, round_0_6);
      if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_6 == FIRST_ROUND)) && (count(mbox_0_6, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_6, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        m = max_timestamp(mbox_1_0);
        estimate = m->estimate;
        round_1_0 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
        round_1_0 = THIRD_ROUND;
        mbox_1_0 = havoc(phase, round_1_0);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_0 == FIRST_ROUND)) && (count(mbox_1_0, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_0))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_0)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_0 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_0 == SECOND_ROUND)) && (count(mbox_1_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_0->message->decided) && (mbox_1_0->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_6 == THIRD_ROUND)) && (count(mbox_0_6, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_6, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_0_6))
      {
        round_1_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        decide(estimate);
        phase++;
        mbox_1_1 = havoc(phase, round_1_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_1 == FIRST_ROUND)) && (count(mbox_1_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_1))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_1)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_1 == SECOND_ROUND)) && (count(mbox_1_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_1->message->decided) && (mbox_1_1->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_6 == THIRD_ROUND)) && (count(mbox_0_6, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_6, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_0_6)))
      {
        round_1_2 = FIRST_ROUND;
        phase++;
        mbox_1_2 = havoc(phase, round_1_2);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_2 == FIRST_ROUND)) && (count(mbox_1_2, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_2))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_2)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_2 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_2 == SECOND_ROUND)) && (count(mbox_1_2, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_2->message->decided) && (mbox_1_2->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (((!value_decided(p)) && (p != leader(phase, n))) && (round_0_6 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
        round_1_3 = SECOND_ROUND;
        mbox_1_3 = havoc(phase, round_1_3);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_3 == FIRST_ROUND)) && (count(mbox_1_3, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_3))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_3)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_3 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_3 == SECOND_ROUND)) && (count(mbox_1_3, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_3->message->decided) && (mbox_1_3->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0_6 == SECOND_ROUND)) && (count(mbox_0_6, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0_6, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1_4 = THIRD_ROUND;
        m = mbox_1_4->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1_4 = FOURTH_ROUND;
        mbox_1_4 = havoc(phase, round_1_4);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_4 == FIRST_ROUND)) && (count(mbox_1_4, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_4))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_4)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_4 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_4 == SECOND_ROUND)) && (count(mbox_1_4, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_4->message->decided) && (mbox_1_4->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_0_6, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_0_6->message->decided) && (mbox_0_6->message->phase >= phase))
      {
        estimate = m->estimate;
        decide(estimate);
        phase = mbox_1_5->message->phase;
        mbox_1_5 = havoc(phase, round_1_5);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_5 == FIRST_ROUND)) && (count(mbox_1_5, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_5))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_5)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_5 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_5 == SECOND_ROUND)) && (count(mbox_1_5, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_5->message->decided) && (mbox_1_5->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if ((!value_decided(p)) && timeout(round_0_6))
      {
        round_1_6 = FIRST_ROUND;
        phase++;
        mbox_1_6 = havoc(phase, round_1_6);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_6 == FIRST_ROUND)) && (count(mbox_1_6, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_6))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_6)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_6 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_6 == SECOND_ROUND)) && (count(mbox_1_6, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_6->message->decided) && (mbox_1_6->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (value_decided(p) && (p == leader(phase, n)))
      {
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        mbox_1_7 = havoc(phase, round_1_7);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_7 == FIRST_ROUND)) && (count(mbox_1_7, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_7))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_7)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_7 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_7 == SECOND_ROUND)) && (count(mbox_1_7, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_7->message->decided) && (mbox_1_7->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      continue;
    }

    if (value_decided(p) && (p == leader(phase, n)))
    {
      send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
      phase++;
      mbox_0_7 = havoc(phase, round_0_7);
      if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_7 == FIRST_ROUND)) && (count(mbox_0_7, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_7, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        m = max_timestamp(mbox_1_0);
        estimate = m->estimate;
        round_1_0 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
        round_1_0 = THIRD_ROUND;
        mbox_1_0 = havoc(phase, round_1_0);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_0 == FIRST_ROUND)) && (count(mbox_1_0, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_0))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_0)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_0 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_0 == SECOND_ROUND)) && (count(mbox_1_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_0, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_0->message->decided) && (mbox_1_0->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_7 == THIRD_ROUND)) && (count(mbox_0_7, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_7, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_0_7))
      {
        round_1_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        decide(estimate);
        phase++;
        mbox_1_1 = havoc(phase, round_1_1);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_1 == FIRST_ROUND)) && (count(mbox_1_1, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_1))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_1)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_1 == SECOND_ROUND)) && (count(mbox_1_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_1, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_1->message->decided) && (mbox_1_1->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_7 == THIRD_ROUND)) && (count(mbox_0_7, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_7, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_0_7)))
      {
        round_1_2 = FIRST_ROUND;
        phase++;
        mbox_1_2 = havoc(phase, round_1_2);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_2 == FIRST_ROUND)) && (count(mbox_1_2, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_2))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_2)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_2 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_2 == SECOND_ROUND)) && (count(mbox_1_2, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_2, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_2->message->decided) && (mbox_1_2->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (((!value_decided(p)) && (p != leader(phase, n))) && (round_0_7 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
        round_1_3 = SECOND_ROUND;
        mbox_1_3 = havoc(phase, round_1_3);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_3 == FIRST_ROUND)) && (count(mbox_1_3, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_3))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_3)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_3 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_3 == SECOND_ROUND)) && (count(mbox_1_3, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_3, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_3->message->decided) && (mbox_1_3->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0_7 == SECOND_ROUND)) && (count(mbox_0_7, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0_7, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        round_1_4 = THIRD_ROUND;
        m = mbox_1_4->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1_4 = FOURTH_ROUND;
        mbox_1_4 = havoc(phase, round_1_4);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_4 == FIRST_ROUND)) && (count(mbox_1_4, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_4))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_4)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_4 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_4 == SECOND_ROUND)) && (count(mbox_1_4, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_4->message->decided) && (mbox_1_4->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_0_7, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_0_7->message->decided) && (mbox_0_7->message->phase >= phase))
      {
        estimate = m->estimate;
        decide(estimate);
        phase = mbox_1_5->message->phase;
        mbox_1_5 = havoc(phase, round_1_5);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_5 == FIRST_ROUND)) && (count(mbox_1_5, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_5))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_5)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_5 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_5 == SECOND_ROUND)) && (count(mbox_1_5, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_5, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_5->message->decided) && (mbox_1_5->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if ((!value_decided(p)) && timeout(round_0_7))
      {
        round_1_6 = FIRST_ROUND;
        phase++;
        mbox_1_6 = havoc(phase, round_1_6);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_6 == FIRST_ROUND)) && (count(mbox_1_6, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_6))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_6)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_6 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_6 == SECOND_ROUND)) && (count(mbox_1_6, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_6, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_6->message->decided) && (mbox_1_6->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      if (value_decided(p) && (p == leader(phase, n)))
      {
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        phase++;
        mbox_1_7 = havoc(phase, round_1_7);
        if (((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_7 == FIRST_ROUND)) && (count(mbox_1_7, phase, FIRST_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, null_int(), null_bool()), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_1_7))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          decide(estimate);
          phase++;
          continue;
        }

        if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_1_7)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((!value_decided(p)) && (p != leader(phase, n))) && (round_1_7 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_7 == SECOND_ROUND)) && (count(mbox_1_7, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_7, null_int(), FOURTH_ROUND, null_int()) == 1)) && mbox_1_7->message->decided) && (mbox_1_7->message->phase >= phase))
        {
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (value_decided(p) && (p == leader(phase, n)))
        {
          send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
          phase++;
          continue;
        }

        continue;
      }

      continue;
    }

  }

}


