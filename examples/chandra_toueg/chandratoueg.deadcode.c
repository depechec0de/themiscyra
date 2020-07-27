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
  struct list *mbox_2_9;
  struct list *mbox_2_8;
  struct list *mbox_2_7;
  struct list *mbox_2_6;
  struct list *mbox_2_5;
  struct list *mbox_2_4;
  struct list *mbox_2_3;
  struct list *mbox_2_2;
  struct list *mbox_2_1;
  struct list *mbox_2_0;
  struct list *mbox_1_9;
  struct list *mbox_1_8;
  struct list *mbox_1_7;
  struct list *mbox_1_6;
  struct list *mbox_1_5;
  struct list *mbox_1_4;
  struct list *mbox_1_3;
  struct list *mbox_1_2;
  struct list *mbox_1_1;
  struct list *mbox_1_0;
  struct list *mbox_0_9;
  struct list *mbox_0_8;
  struct list *mbox_0_7;
  struct list *mbox_0_6;
  struct list *mbox_0_5;
  struct list *mbox_0_4;
  struct list *mbox_0_3;
  struct list *mbox_0_2;
  struct list *mbox_0_1;
  struct list *mbox_0_0;
  enum round_typ round_2_9;
  enum round_typ round_2_8;
  enum round_typ round_2_7;
  enum round_typ round_2_6;
  enum round_typ round_2_5;
  enum round_typ round_2_4;
  enum round_typ round_2_3;
  enum round_typ round_2_2;
  enum round_typ round_2_1;
  enum round_typ round_2_0;
  enum round_typ round_1_9;
  enum round_typ round_1_8;
  enum round_typ round_1_7;
  enum round_typ round_1_6;
  enum round_typ round_1_5;
  enum round_typ round_1_4;
  enum round_typ round_1_3;
  enum round_typ round_1_2;
  enum round_typ round_1_1;
  enum round_typ round_1_0;
  enum round_typ round_0_9;
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
      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_0 == THIRD_ROUND)) && (count(mbox_0_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && all_ack(mbox_0_0))
      {
        round_1_1 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
        decide(estimate);
        phase++;
        continue;
      }

      if ((((((!value_decided(p)) && (p == leader(phase, n))) && (round_0_0 == THIRD_ROUND)) && (count(mbox_0_0, phase, THIRD_ROUND, null_int()) > ((n + 1) / 2))) && (count(mbox_0_0, null_int(), FOURTH_ROUND, null_int()) == 0)) && (!all_ack(mbox_0_0)))
      {
        phase++;
        continue;
      }

      if ((!value_decided(p)) && timeout(round_0_0))
      {
        phase++;
        continue;
      }

      continue;
    }

    if (((!value_decided(p)) && (p != leader(phase, n))) && (round == FIRST_ROUND))
    {
      send(message(phase, FIRST_ROUND, estimate, p, timestamp, null_bool()), leader(phase, n));
      round_0_3 = SECOND_ROUND;
      mbox_0_3 = havoc(phase, round_0_3);
      if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_0_3 == SECOND_ROUND)) && (count(mbox_0_3, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0_3, null_int(), FOURTH_ROUND, null_int()) == 0))
      {
        m = mbox_1_4->message;
        estimate = m->estimate;
        timestamp = phase;
        round_1_4 = THIRD_ROUND;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1_4 = FOURTH_ROUND;
        mbox_1_4 = havoc(phase, round_1_4);
        if (((((!value_decided(p)) && (p != leader(phase, n))) && (round_1_4 == FOURTH_ROUND)) && (count(mbox_1_4, phase, FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1_4->message->decided)
        {
          estimate = m->estimate;
          decide(estimate);
          phase++;
          continue;
        }

        if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_1_4, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_1_4->message->decided) && (mbox_1_4->message->phase > phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decide(estimate);
          phase = mbox_2_0->message->phase + 1;
          continue;
        }

        if ((!value_decided(p)) && timeout(round_1_4))
        {
          phase++;
          continue;
        }

        continue;
      }

      if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox_0_3, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox_0_3->message->decided) && (mbox_0_3->message->phase > phase))
      {
        round_1_6 = FOURTH_ROUND;
        estimate = m->estimate;
        decide(estimate);
        phase = mbox_1_6->message->phase + 1;
        continue;
      }

      if ((!value_decided(p)) && timeout(round_0_3))
      {
        phase++;
        continue;
      }

      continue;
    }

    if (((((!value_decided(p)) && (p != leader(phase, n))) && (count(mbox, null_int(), FOURTH_ROUND, leader(phase, n)) == 1)) && mbox->message->decided) && (mbox->message->phase > phase))
    {
      round_0_6 = FOURTH_ROUND;
      estimate = m->estimate;
      decide(estimate);
      phase = mbox_0_6->message->phase + 1;
      continue;
    }

    if ((!value_decided(p)) && timeout(round))
    {
      phase++;
      continue;
    }

    if (value_decided(p) && (p == leader(phase, n)))
    {
      round_0_8 = FOURTH_ROUND;
      send(message(phase, FOURTH_ROUND, estimate, p, null_int(), true), to_all);
      phase++;
      continue;
    }

  }

}


