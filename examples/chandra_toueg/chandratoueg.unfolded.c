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
enum null
{
  BOOL_NULL,
  INT_NULL
};
int out(int v1, int v2);
int in();
struct msg *max_timestamp(struct list *mbox);
_Bool all_ack(struct list *mbox);
_Bool send(struct msg *message, int pid);
int leader(int phase, int net_size);
int count(struct list *mbox, int phase, enum round_typ round, int from);
struct list *havoc(int phase, enum round_typ round);
_Bool timeout(enum round_typ round);
struct msg *message(int phase, enum round_typ round, int estimate, int p, int timestamp, _Bool decided);
int main()
{
  struct list *mbox_2_10;
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
  struct list *mbox_1_10;
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
  struct list *mbox_0_10;
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
  enum round_typ round_2_10;
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
  enum round_typ round_1_10;
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
  enum round_typ round_0_10;
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
  _Bool decided;
  struct list *mbox;
  struct msg *m;
  decided = false;
  phase = 1;
  round = FIRST_ROUND;
  estimate = in();
  timestamp = 0;
  while (1)
  {
    mbox = havoc(phase, round);
    if ((p != leader(phase, n)) && (round == FIRST_ROUND))
    {
      send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
      round_0_0 = SECOND_ROUND;
      mbox_0_0 = havoc(phase, round_0_0);
      if ((p != leader(phase, n)) && (round_0_0 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
        round_1_0 = SECOND_ROUND;
        mbox_1_0 = havoc(phase, round_1_0);
        if ((p != leader(phase, n)) && (round_1_0 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_0 == FIRST_ROUND)) && (count(mbox_1_0, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_0 == FIRST_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_0 == SECOND_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_0 == SECOND_ROUND)) && (count(mbox_1_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_0))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_0)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_0->message->decided) && (mbox_1_0->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_0 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p == leader(phase, n)) && (round_0_0 == FIRST_ROUND)) && (count(mbox_0_0, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
      {
        m = max_timestamp(mbox_1_1);
        estimate = m->estimate;
        round_1_1 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
        round_1_1 = THIRD_ROUND;
        mbox_1_1 = havoc(phase, round_1_1);
        if ((p != leader(phase, n)) && (round_1_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && (count(mbox_1_1, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_1 == SECOND_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_1 == SECOND_ROUND)) && (count(mbox_1_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_1))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_1)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_1->message->decided) && (mbox_1_1->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_1 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p == leader(phase, n)) && (round_0_0 == FIRST_ROUND)) && timeout(round_0_0))
      {
        round_1_2 = FIRST_ROUND;
        phase++;
        mbox_1_2 = havoc(phase, round_1_2);
        if ((p != leader(phase, n)) && (round_1_2 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && (count(mbox_1_2, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_2 == SECOND_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_2 == SECOND_ROUND)) && (count(mbox_1_2, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_2))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_2)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_2->message->decided) && (mbox_1_2->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_2 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p != leader(phase, n)) && (round_0_0 == SECOND_ROUND)) && timeout(round_0_0))
      {
        round_1_3 = FIRST_ROUND;
        phase++;
        mbox_1_3 = havoc(phase, round_1_3);
        if ((p != leader(phase, n)) && (round_1_3 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && (count(mbox_1_3, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_3 == SECOND_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_3 == SECOND_ROUND)) && (count(mbox_1_3, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_3))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_3)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_3->message->decided) && (mbox_1_3->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_3 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (round_0_0 == SECOND_ROUND)) && (count(mbox_0_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
      {
        round_1_4 = THIRD_ROUND;
        m = mbox_1_4->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1_4 = FOURTH_ROUND;
        mbox_1_4 = havoc(phase, round_1_4);
        if ((p != leader(phase, n)) && (round_1_4 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && (count(mbox_1_4, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_4 == SECOND_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_4 == SECOND_ROUND)) && (count(mbox_1_4, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_4))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_4)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_4->message->decided) && (mbox_1_4->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_4 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((((p == leader(phase, n)) && (round_0_0 == THIRD_ROUND)) && (count(mbox_0_0, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_0_0))
      {
        round_1_5 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
        decided = true;
        round_1_5 = FIRST_ROUND;
        phase++;
        mbox_1_5 = havoc(phase, round_1_5);
        if ((p != leader(phase, n)) && (round_1_5 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && (count(mbox_1_5, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_5 == SECOND_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_5 == SECOND_ROUND)) && (count(mbox_1_5, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_5))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_5)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_5->message->decided) && (mbox_1_5->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_5 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((((p == leader(phase, n)) && (round_0_0 == THIRD_ROUND)) && (count(mbox_0_0, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_0_0)))
      {
        round_1_6 = FIRST_ROUND;
        phase++;
        mbox_1_6 = havoc(phase, round_1_6);
        if ((p != leader(phase, n)) && (round_1_6 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_6 == FIRST_ROUND)) && (count(mbox_1_6, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_6 == FIRST_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_6 == SECOND_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_6 == SECOND_ROUND)) && (count(mbox_1_6, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_6))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_6)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_6->message->decided) && (mbox_1_6->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_6 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p == leader(phase, n)) && (round_0_0 == THIRD_ROUND)) && timeout(round_0_0))
      {
        round_1_7 = FIRST_ROUND;
        phase++;
        mbox_1_7 = havoc(phase, round_1_7);
        if ((p != leader(phase, n)) && (round_1_7 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_7 == FIRST_ROUND)) && (count(mbox_1_7, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_7 == FIRST_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_7 == SECOND_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_7 == SECOND_ROUND)) && (count(mbox_1_7, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_7))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_7)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_7->message->decided) && (mbox_1_7->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_7 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (count(mbox_0_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_0_0->message->decided) && (mbox_0_0->message->phase >= phase))
      {
        round_1_8 = FOURTH_ROUND;
        estimate = m->estimate;
        decided = true;
        out(p, estimate);
        phase++;
        mbox_1_8 = havoc(phase, round_1_8);
        if ((p != leader(phase, n)) && (round_1_8 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_8 == FIRST_ROUND)) && (count(mbox_1_8, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_8 == FIRST_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_8 == SECOND_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_8 == SECOND_ROUND)) && (count(mbox_1_8, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && (count(mbox_1_8, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_8))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && (count(mbox_1_8, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_8)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_8->message->decided) && (mbox_1_8->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_8 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (round_0_0 == FOURTH_ROUND)) && (decided == false)) && timeout(round_0_0))
      {
        round_1_9 = FIRST_ROUND;
        phase++;
        mbox_1_9 = havoc(phase, round_1_9);
        if ((p != leader(phase, n)) && (round_1_9 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_9 == FIRST_ROUND)) && (count(mbox_1_9, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_9 == FIRST_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_9 == SECOND_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_9 == SECOND_ROUND)) && (count(mbox_1_9, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && (count(mbox_1_9, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_9))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && (count(mbox_1_9, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_9)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_9->message->decided) && (mbox_1_9->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_9 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      continue;
    }

    if ((((p == leader(phase, n)) && (round == FIRST_ROUND)) && (count(mbox, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
    {
      m = max_timestamp(mbox_0_1);
      estimate = m->estimate;
      round_0_1 = SECOND_ROUND;
      send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
      round_0_1 = THIRD_ROUND;
      mbox_0_1 = havoc(phase, round_0_1);
      if ((p != leader(phase, n)) && (round_0_1 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
        round_1_0 = SECOND_ROUND;
        mbox_1_0 = havoc(phase, round_1_0);
        if ((p != leader(phase, n)) && (round_1_0 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_0 == FIRST_ROUND)) && (count(mbox_1_0, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_0 == FIRST_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_0 == SECOND_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_0 == SECOND_ROUND)) && (count(mbox_1_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_0))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_0)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_0->message->decided) && (mbox_1_0->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_0 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p == leader(phase, n)) && (round_0_1 == FIRST_ROUND)) && (count(mbox_0_1, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
      {
        m = max_timestamp(mbox_1_1);
        estimate = m->estimate;
        round_1_1 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
        round_1_1 = THIRD_ROUND;
        mbox_1_1 = havoc(phase, round_1_1);
        if ((p != leader(phase, n)) && (round_1_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && (count(mbox_1_1, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_1 == SECOND_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_1 == SECOND_ROUND)) && (count(mbox_1_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_1))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_1)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_1->message->decided) && (mbox_1_1->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_1 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p == leader(phase, n)) && (round_0_1 == FIRST_ROUND)) && timeout(round_0_1))
      {
        round_1_2 = FIRST_ROUND;
        phase++;
        mbox_1_2 = havoc(phase, round_1_2);
        if ((p != leader(phase, n)) && (round_1_2 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && (count(mbox_1_2, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_2 == SECOND_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_2 == SECOND_ROUND)) && (count(mbox_1_2, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_2))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_2)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_2->message->decided) && (mbox_1_2->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_2 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p != leader(phase, n)) && (round_0_1 == SECOND_ROUND)) && timeout(round_0_1))
      {
        round_1_3 = FIRST_ROUND;
        phase++;
        mbox_1_3 = havoc(phase, round_1_3);
        if ((p != leader(phase, n)) && (round_1_3 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && (count(mbox_1_3, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_3 == SECOND_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_3 == SECOND_ROUND)) && (count(mbox_1_3, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_3))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_3)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_3->message->decided) && (mbox_1_3->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_3 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (round_0_1 == SECOND_ROUND)) && (count(mbox_0_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
      {
        round_1_4 = THIRD_ROUND;
        m = mbox_1_4->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1_4 = FOURTH_ROUND;
        mbox_1_4 = havoc(phase, round_1_4);
        if ((p != leader(phase, n)) && (round_1_4 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && (count(mbox_1_4, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_4 == SECOND_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_4 == SECOND_ROUND)) && (count(mbox_1_4, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_4))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_4)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_4->message->decided) && (mbox_1_4->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_4 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((((p == leader(phase, n)) && (round_0_1 == THIRD_ROUND)) && (count(mbox_0_1, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_0_1))
      {
        round_1_5 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
        decided = true;
        round_1_5 = FIRST_ROUND;
        phase++;
        mbox_1_5 = havoc(phase, round_1_5);
        if ((p != leader(phase, n)) && (round_1_5 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && (count(mbox_1_5, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_5 == SECOND_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_5 == SECOND_ROUND)) && (count(mbox_1_5, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_5))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_5)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_5->message->decided) && (mbox_1_5->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_5 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((((p == leader(phase, n)) && (round_0_1 == THIRD_ROUND)) && (count(mbox_0_1, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_0_1)))
      {
        round_1_6 = FIRST_ROUND;
        phase++;
        mbox_1_6 = havoc(phase, round_1_6);
        if ((p != leader(phase, n)) && (round_1_6 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_6 == FIRST_ROUND)) && (count(mbox_1_6, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_6 == FIRST_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_6 == SECOND_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_6 == SECOND_ROUND)) && (count(mbox_1_6, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_6))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_6)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_6->message->decided) && (mbox_1_6->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_6 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p == leader(phase, n)) && (round_0_1 == THIRD_ROUND)) && timeout(round_0_1))
      {
        round_1_7 = FIRST_ROUND;
        phase++;
        mbox_1_7 = havoc(phase, round_1_7);
        if ((p != leader(phase, n)) && (round_1_7 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_7 == FIRST_ROUND)) && (count(mbox_1_7, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_7 == FIRST_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_7 == SECOND_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_7 == SECOND_ROUND)) && (count(mbox_1_7, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_7))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_7)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_7->message->decided) && (mbox_1_7->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_7 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (count(mbox_0_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_0_1->message->decided) && (mbox_0_1->message->phase >= phase))
      {
        round_1_8 = FOURTH_ROUND;
        estimate = m->estimate;
        decided = true;
        out(p, estimate);
        phase++;
        mbox_1_8 = havoc(phase, round_1_8);
        if ((p != leader(phase, n)) && (round_1_8 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_8 == FIRST_ROUND)) && (count(mbox_1_8, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_8 == FIRST_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_8 == SECOND_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_8 == SECOND_ROUND)) && (count(mbox_1_8, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && (count(mbox_1_8, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_8))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && (count(mbox_1_8, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_8)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_8->message->decided) && (mbox_1_8->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_8 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (round_0_1 == FOURTH_ROUND)) && (decided == false)) && timeout(round_0_1))
      {
        round_1_9 = FIRST_ROUND;
        phase++;
        mbox_1_9 = havoc(phase, round_1_9);
        if ((p != leader(phase, n)) && (round_1_9 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_9 == FIRST_ROUND)) && (count(mbox_1_9, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_9 == FIRST_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_9 == SECOND_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_9 == SECOND_ROUND)) && (count(mbox_1_9, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && (count(mbox_1_9, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_9))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && (count(mbox_1_9, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_9)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_9->message->decided) && (mbox_1_9->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_9 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      continue;
    }

    if (((p == leader(phase, n)) && (round == FIRST_ROUND)) && timeout(round))
    {
      round_0_2 = FIRST_ROUND;
      phase++;
      mbox_0_2 = havoc(phase, round_0_2);
      if ((p != leader(phase, n)) && (round_0_2 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
        round_1_0 = SECOND_ROUND;
        mbox_1_0 = havoc(phase, round_1_0);
        if ((p != leader(phase, n)) && (round_1_0 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_0 == FIRST_ROUND)) && (count(mbox_1_0, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_0 == FIRST_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_0 == SECOND_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_0 == SECOND_ROUND)) && (count(mbox_1_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_0))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_0)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_0->message->decided) && (mbox_1_0->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_0 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p == leader(phase, n)) && (round_0_2 == FIRST_ROUND)) && (count(mbox_0_2, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
      {
        m = max_timestamp(mbox_1_1);
        estimate = m->estimate;
        round_1_1 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
        round_1_1 = THIRD_ROUND;
        mbox_1_1 = havoc(phase, round_1_1);
        if ((p != leader(phase, n)) && (round_1_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && (count(mbox_1_1, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_1 == SECOND_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_1 == SECOND_ROUND)) && (count(mbox_1_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_1))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_1)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_1->message->decided) && (mbox_1_1->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_1 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p == leader(phase, n)) && (round_0_2 == FIRST_ROUND)) && timeout(round_0_2))
      {
        round_1_2 = FIRST_ROUND;
        phase++;
        mbox_1_2 = havoc(phase, round_1_2);
        if ((p != leader(phase, n)) && (round_1_2 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && (count(mbox_1_2, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_2 == SECOND_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_2 == SECOND_ROUND)) && (count(mbox_1_2, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_2))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_2)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_2->message->decided) && (mbox_1_2->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_2 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p != leader(phase, n)) && (round_0_2 == SECOND_ROUND)) && timeout(round_0_2))
      {
        round_1_3 = FIRST_ROUND;
        phase++;
        mbox_1_3 = havoc(phase, round_1_3);
        if ((p != leader(phase, n)) && (round_1_3 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && (count(mbox_1_3, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_3 == SECOND_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_3 == SECOND_ROUND)) && (count(mbox_1_3, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_3))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_3)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_3->message->decided) && (mbox_1_3->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_3 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (round_0_2 == SECOND_ROUND)) && (count(mbox_0_2, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
      {
        round_1_4 = THIRD_ROUND;
        m = mbox_1_4->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1_4 = FOURTH_ROUND;
        mbox_1_4 = havoc(phase, round_1_4);
        if ((p != leader(phase, n)) && (round_1_4 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && (count(mbox_1_4, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_4 == SECOND_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_4 == SECOND_ROUND)) && (count(mbox_1_4, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_4))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_4)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_4->message->decided) && (mbox_1_4->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_4 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((((p == leader(phase, n)) && (round_0_2 == THIRD_ROUND)) && (count(mbox_0_2, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_0_2))
      {
        round_1_5 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
        decided = true;
        round_1_5 = FIRST_ROUND;
        phase++;
        mbox_1_5 = havoc(phase, round_1_5);
        if ((p != leader(phase, n)) && (round_1_5 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && (count(mbox_1_5, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_5 == SECOND_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_5 == SECOND_ROUND)) && (count(mbox_1_5, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_5))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_5)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_5->message->decided) && (mbox_1_5->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_5 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((((p == leader(phase, n)) && (round_0_2 == THIRD_ROUND)) && (count(mbox_0_2, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_0_2)))
      {
        round_1_6 = FIRST_ROUND;
        phase++;
        mbox_1_6 = havoc(phase, round_1_6);
        if ((p != leader(phase, n)) && (round_1_6 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_6 == FIRST_ROUND)) && (count(mbox_1_6, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_6 == FIRST_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_6 == SECOND_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_6 == SECOND_ROUND)) && (count(mbox_1_6, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_6))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_6)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_6->message->decided) && (mbox_1_6->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_6 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p == leader(phase, n)) && (round_0_2 == THIRD_ROUND)) && timeout(round_0_2))
      {
        round_1_7 = FIRST_ROUND;
        phase++;
        mbox_1_7 = havoc(phase, round_1_7);
        if ((p != leader(phase, n)) && (round_1_7 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_7 == FIRST_ROUND)) && (count(mbox_1_7, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_7 == FIRST_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_7 == SECOND_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_7 == SECOND_ROUND)) && (count(mbox_1_7, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_7))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_7)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_7->message->decided) && (mbox_1_7->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_7 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (count(mbox_0_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_0_2->message->decided) && (mbox_0_2->message->phase >= phase))
      {
        round_1_8 = FOURTH_ROUND;
        estimate = m->estimate;
        decided = true;
        out(p, estimate);
        phase++;
        mbox_1_8 = havoc(phase, round_1_8);
        if ((p != leader(phase, n)) && (round_1_8 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_8 == FIRST_ROUND)) && (count(mbox_1_8, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_8 == FIRST_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_8 == SECOND_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_8 == SECOND_ROUND)) && (count(mbox_1_8, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && (count(mbox_1_8, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_8))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && (count(mbox_1_8, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_8)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_8->message->decided) && (mbox_1_8->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_8 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (round_0_2 == FOURTH_ROUND)) && (decided == false)) && timeout(round_0_2))
      {
        round_1_9 = FIRST_ROUND;
        phase++;
        mbox_1_9 = havoc(phase, round_1_9);
        if ((p != leader(phase, n)) && (round_1_9 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_9 == FIRST_ROUND)) && (count(mbox_1_9, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_9 == FIRST_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_9 == SECOND_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_9 == SECOND_ROUND)) && (count(mbox_1_9, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && (count(mbox_1_9, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_9))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && (count(mbox_1_9, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_9)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_9->message->decided) && (mbox_1_9->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_9 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      continue;
    }

    if (((p != leader(phase, n)) && (round == SECOND_ROUND)) && timeout(round))
    {
      round_0_3 = FIRST_ROUND;
      phase++;
      mbox_0_3 = havoc(phase, round_0_3);
      if ((p != leader(phase, n)) && (round_0_3 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
        round_1_0 = SECOND_ROUND;
        mbox_1_0 = havoc(phase, round_1_0);
        if ((p != leader(phase, n)) && (round_1_0 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_0 == FIRST_ROUND)) && (count(mbox_1_0, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_0 == FIRST_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_0 == SECOND_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_0 == SECOND_ROUND)) && (count(mbox_1_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_0))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_0)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_0->message->decided) && (mbox_1_0->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_0 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p == leader(phase, n)) && (round_0_3 == FIRST_ROUND)) && (count(mbox_0_3, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
      {
        m = max_timestamp(mbox_1_1);
        estimate = m->estimate;
        round_1_1 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
        round_1_1 = THIRD_ROUND;
        mbox_1_1 = havoc(phase, round_1_1);
        if ((p != leader(phase, n)) && (round_1_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && (count(mbox_1_1, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_1 == SECOND_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_1 == SECOND_ROUND)) && (count(mbox_1_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_1))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_1)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_1->message->decided) && (mbox_1_1->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_1 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p == leader(phase, n)) && (round_0_3 == FIRST_ROUND)) && timeout(round_0_3))
      {
        round_1_2 = FIRST_ROUND;
        phase++;
        mbox_1_2 = havoc(phase, round_1_2);
        if ((p != leader(phase, n)) && (round_1_2 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && (count(mbox_1_2, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_2 == SECOND_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_2 == SECOND_ROUND)) && (count(mbox_1_2, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_2))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_2)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_2->message->decided) && (mbox_1_2->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_2 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p != leader(phase, n)) && (round_0_3 == SECOND_ROUND)) && timeout(round_0_3))
      {
        round_1_3 = FIRST_ROUND;
        phase++;
        mbox_1_3 = havoc(phase, round_1_3);
        if ((p != leader(phase, n)) && (round_1_3 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && (count(mbox_1_3, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_3 == SECOND_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_3 == SECOND_ROUND)) && (count(mbox_1_3, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_3))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_3)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_3->message->decided) && (mbox_1_3->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_3 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (round_0_3 == SECOND_ROUND)) && (count(mbox_0_3, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
      {
        round_1_4 = THIRD_ROUND;
        m = mbox_1_4->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1_4 = FOURTH_ROUND;
        mbox_1_4 = havoc(phase, round_1_4);
        if ((p != leader(phase, n)) && (round_1_4 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && (count(mbox_1_4, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_4 == SECOND_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_4 == SECOND_ROUND)) && (count(mbox_1_4, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_4))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_4)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_4->message->decided) && (mbox_1_4->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_4 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((((p == leader(phase, n)) && (round_0_3 == THIRD_ROUND)) && (count(mbox_0_3, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_0_3))
      {
        round_1_5 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
        decided = true;
        round_1_5 = FIRST_ROUND;
        phase++;
        mbox_1_5 = havoc(phase, round_1_5);
        if ((p != leader(phase, n)) && (round_1_5 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && (count(mbox_1_5, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_5 == SECOND_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_5 == SECOND_ROUND)) && (count(mbox_1_5, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_5))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_5)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_5->message->decided) && (mbox_1_5->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_5 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((((p == leader(phase, n)) && (round_0_3 == THIRD_ROUND)) && (count(mbox_0_3, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_0_3)))
      {
        round_1_6 = FIRST_ROUND;
        phase++;
        mbox_1_6 = havoc(phase, round_1_6);
        if ((p != leader(phase, n)) && (round_1_6 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_6 == FIRST_ROUND)) && (count(mbox_1_6, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_6 == FIRST_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_6 == SECOND_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_6 == SECOND_ROUND)) && (count(mbox_1_6, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_6))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_6)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_6->message->decided) && (mbox_1_6->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_6 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p == leader(phase, n)) && (round_0_3 == THIRD_ROUND)) && timeout(round_0_3))
      {
        round_1_7 = FIRST_ROUND;
        phase++;
        mbox_1_7 = havoc(phase, round_1_7);
        if ((p != leader(phase, n)) && (round_1_7 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_7 == FIRST_ROUND)) && (count(mbox_1_7, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_7 == FIRST_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_7 == SECOND_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_7 == SECOND_ROUND)) && (count(mbox_1_7, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_7))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_7)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_7->message->decided) && (mbox_1_7->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_7 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (count(mbox_0_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_0_3->message->decided) && (mbox_0_3->message->phase >= phase))
      {
        round_1_8 = FOURTH_ROUND;
        estimate = m->estimate;
        decided = true;
        out(p, estimate);
        phase++;
        mbox_1_8 = havoc(phase, round_1_8);
        if ((p != leader(phase, n)) && (round_1_8 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_8 == FIRST_ROUND)) && (count(mbox_1_8, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_8 == FIRST_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_8 == SECOND_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_8 == SECOND_ROUND)) && (count(mbox_1_8, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && (count(mbox_1_8, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_8))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && (count(mbox_1_8, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_8)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_8->message->decided) && (mbox_1_8->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_8 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (round_0_3 == FOURTH_ROUND)) && (decided == false)) && timeout(round_0_3))
      {
        round_1_9 = FIRST_ROUND;
        phase++;
        mbox_1_9 = havoc(phase, round_1_9);
        if ((p != leader(phase, n)) && (round_1_9 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_9 == FIRST_ROUND)) && (count(mbox_1_9, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_9 == FIRST_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_9 == SECOND_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_9 == SECOND_ROUND)) && (count(mbox_1_9, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && (count(mbox_1_9, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_9))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && (count(mbox_1_9, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_9)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_9->message->decided) && (mbox_1_9->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_9 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      continue;
    }

    if ((((p != leader(phase, n)) && (round == SECOND_ROUND)) && (count(mbox, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
    {
      round_0_4 = THIRD_ROUND;
      m = mbox_0_4->message;
      estimate = m->estimate;
      timestamp = phase;
      send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
      round_0_4 = FOURTH_ROUND;
      mbox_0_4 = havoc(phase, round_0_4);
      if ((p != leader(phase, n)) && (round_0_4 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
        round_1_0 = SECOND_ROUND;
        mbox_1_0 = havoc(phase, round_1_0);
        if ((p != leader(phase, n)) && (round_1_0 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_0 == FIRST_ROUND)) && (count(mbox_1_0, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_0 == FIRST_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_0 == SECOND_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_0 == SECOND_ROUND)) && (count(mbox_1_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_0))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_0)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_0->message->decided) && (mbox_1_0->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_0 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p == leader(phase, n)) && (round_0_4 == FIRST_ROUND)) && (count(mbox_0_4, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
      {
        m = max_timestamp(mbox_1_1);
        estimate = m->estimate;
        round_1_1 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
        round_1_1 = THIRD_ROUND;
        mbox_1_1 = havoc(phase, round_1_1);
        if ((p != leader(phase, n)) && (round_1_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && (count(mbox_1_1, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_1 == SECOND_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_1 == SECOND_ROUND)) && (count(mbox_1_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_1))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_1)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_1->message->decided) && (mbox_1_1->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_1 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p == leader(phase, n)) && (round_0_4 == FIRST_ROUND)) && timeout(round_0_4))
      {
        round_1_2 = FIRST_ROUND;
        phase++;
        mbox_1_2 = havoc(phase, round_1_2);
        if ((p != leader(phase, n)) && (round_1_2 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && (count(mbox_1_2, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_2 == SECOND_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_2 == SECOND_ROUND)) && (count(mbox_1_2, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_2))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_2)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_2->message->decided) && (mbox_1_2->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_2 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p != leader(phase, n)) && (round_0_4 == SECOND_ROUND)) && timeout(round_0_4))
      {
        round_1_3 = FIRST_ROUND;
        phase++;
        mbox_1_3 = havoc(phase, round_1_3);
        if ((p != leader(phase, n)) && (round_1_3 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && (count(mbox_1_3, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_3 == SECOND_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_3 == SECOND_ROUND)) && (count(mbox_1_3, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_3))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_3)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_3->message->decided) && (mbox_1_3->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_3 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (round_0_4 == SECOND_ROUND)) && (count(mbox_0_4, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
      {
        round_1_4 = THIRD_ROUND;
        m = mbox_1_4->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1_4 = FOURTH_ROUND;
        mbox_1_4 = havoc(phase, round_1_4);
        if ((p != leader(phase, n)) && (round_1_4 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && (count(mbox_1_4, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_4 == SECOND_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_4 == SECOND_ROUND)) && (count(mbox_1_4, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_4))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_4)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_4->message->decided) && (mbox_1_4->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_4 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((((p == leader(phase, n)) && (round_0_4 == THIRD_ROUND)) && (count(mbox_0_4, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_0_4))
      {
        round_1_5 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
        decided = true;
        round_1_5 = FIRST_ROUND;
        phase++;
        mbox_1_5 = havoc(phase, round_1_5);
        if ((p != leader(phase, n)) && (round_1_5 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && (count(mbox_1_5, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_5 == SECOND_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_5 == SECOND_ROUND)) && (count(mbox_1_5, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_5))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_5)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_5->message->decided) && (mbox_1_5->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_5 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((((p == leader(phase, n)) && (round_0_4 == THIRD_ROUND)) && (count(mbox_0_4, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_0_4)))
      {
        round_1_6 = FIRST_ROUND;
        phase++;
        mbox_1_6 = havoc(phase, round_1_6);
        if ((p != leader(phase, n)) && (round_1_6 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_6 == FIRST_ROUND)) && (count(mbox_1_6, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_6 == FIRST_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_6 == SECOND_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_6 == SECOND_ROUND)) && (count(mbox_1_6, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_6))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_6)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_6->message->decided) && (mbox_1_6->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_6 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p == leader(phase, n)) && (round_0_4 == THIRD_ROUND)) && timeout(round_0_4))
      {
        round_1_7 = FIRST_ROUND;
        phase++;
        mbox_1_7 = havoc(phase, round_1_7);
        if ((p != leader(phase, n)) && (round_1_7 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_7 == FIRST_ROUND)) && (count(mbox_1_7, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_7 == FIRST_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_7 == SECOND_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_7 == SECOND_ROUND)) && (count(mbox_1_7, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_7))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_7)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_7->message->decided) && (mbox_1_7->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_7 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (count(mbox_0_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_0_4->message->decided) && (mbox_0_4->message->phase >= phase))
      {
        round_1_8 = FOURTH_ROUND;
        estimate = m->estimate;
        decided = true;
        out(p, estimate);
        phase++;
        mbox_1_8 = havoc(phase, round_1_8);
        if ((p != leader(phase, n)) && (round_1_8 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_8 == FIRST_ROUND)) && (count(mbox_1_8, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_8 == FIRST_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_8 == SECOND_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_8 == SECOND_ROUND)) && (count(mbox_1_8, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && (count(mbox_1_8, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_8))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && (count(mbox_1_8, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_8)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_8->message->decided) && (mbox_1_8->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_8 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (round_0_4 == FOURTH_ROUND)) && (decided == false)) && timeout(round_0_4))
      {
        round_1_9 = FIRST_ROUND;
        phase++;
        mbox_1_9 = havoc(phase, round_1_9);
        if ((p != leader(phase, n)) && (round_1_9 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_9 == FIRST_ROUND)) && (count(mbox_1_9, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_9 == FIRST_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_9 == SECOND_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_9 == SECOND_ROUND)) && (count(mbox_1_9, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && (count(mbox_1_9, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_9))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && (count(mbox_1_9, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_9)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_9->message->decided) && (mbox_1_9->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_9 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      continue;
    }

    if (((((p == leader(phase, n)) && (round == THIRD_ROUND)) && (count(mbox, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox))
    {
      round_0_5 = FOURTH_ROUND;
      send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
      decided = true;
      round_0_5 = FIRST_ROUND;
      phase++;
      mbox_0_5 = havoc(phase, round_0_5);
      if ((p != leader(phase, n)) && (round_0_5 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
        round_1_0 = SECOND_ROUND;
        mbox_1_0 = havoc(phase, round_1_0);
        if ((p != leader(phase, n)) && (round_1_0 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_0 == FIRST_ROUND)) && (count(mbox_1_0, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_0 == FIRST_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_0 == SECOND_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_0 == SECOND_ROUND)) && (count(mbox_1_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_0))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_0)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_0->message->decided) && (mbox_1_0->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_0 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p == leader(phase, n)) && (round_0_5 == FIRST_ROUND)) && (count(mbox_0_5, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
      {
        m = max_timestamp(mbox_1_1);
        estimate = m->estimate;
        round_1_1 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
        round_1_1 = THIRD_ROUND;
        mbox_1_1 = havoc(phase, round_1_1);
        if ((p != leader(phase, n)) && (round_1_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && (count(mbox_1_1, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_1 == SECOND_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_1 == SECOND_ROUND)) && (count(mbox_1_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_1))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_1)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_1->message->decided) && (mbox_1_1->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_1 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p == leader(phase, n)) && (round_0_5 == FIRST_ROUND)) && timeout(round_0_5))
      {
        round_1_2 = FIRST_ROUND;
        phase++;
        mbox_1_2 = havoc(phase, round_1_2);
        if ((p != leader(phase, n)) && (round_1_2 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && (count(mbox_1_2, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_2 == SECOND_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_2 == SECOND_ROUND)) && (count(mbox_1_2, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_2))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_2)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_2->message->decided) && (mbox_1_2->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_2 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p != leader(phase, n)) && (round_0_5 == SECOND_ROUND)) && timeout(round_0_5))
      {
        round_1_3 = FIRST_ROUND;
        phase++;
        mbox_1_3 = havoc(phase, round_1_3);
        if ((p != leader(phase, n)) && (round_1_3 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && (count(mbox_1_3, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_3 == SECOND_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_3 == SECOND_ROUND)) && (count(mbox_1_3, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_3))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_3)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_3->message->decided) && (mbox_1_3->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_3 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (round_0_5 == SECOND_ROUND)) && (count(mbox_0_5, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
      {
        round_1_4 = THIRD_ROUND;
        m = mbox_1_4->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1_4 = FOURTH_ROUND;
        mbox_1_4 = havoc(phase, round_1_4);
        if ((p != leader(phase, n)) && (round_1_4 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && (count(mbox_1_4, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_4 == SECOND_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_4 == SECOND_ROUND)) && (count(mbox_1_4, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_4))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_4)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_4->message->decided) && (mbox_1_4->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_4 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((((p == leader(phase, n)) && (round_0_5 == THIRD_ROUND)) && (count(mbox_0_5, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_0_5))
      {
        round_1_5 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
        decided = true;
        round_1_5 = FIRST_ROUND;
        phase++;
        mbox_1_5 = havoc(phase, round_1_5);
        if ((p != leader(phase, n)) && (round_1_5 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && (count(mbox_1_5, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_5 == SECOND_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_5 == SECOND_ROUND)) && (count(mbox_1_5, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_5))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_5)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_5->message->decided) && (mbox_1_5->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_5 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((((p == leader(phase, n)) && (round_0_5 == THIRD_ROUND)) && (count(mbox_0_5, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_0_5)))
      {
        round_1_6 = FIRST_ROUND;
        phase++;
        mbox_1_6 = havoc(phase, round_1_6);
        if ((p != leader(phase, n)) && (round_1_6 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_6 == FIRST_ROUND)) && (count(mbox_1_6, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_6 == FIRST_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_6 == SECOND_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_6 == SECOND_ROUND)) && (count(mbox_1_6, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_6))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_6)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_6->message->decided) && (mbox_1_6->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_6 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p == leader(phase, n)) && (round_0_5 == THIRD_ROUND)) && timeout(round_0_5))
      {
        round_1_7 = FIRST_ROUND;
        phase++;
        mbox_1_7 = havoc(phase, round_1_7);
        if ((p != leader(phase, n)) && (round_1_7 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_7 == FIRST_ROUND)) && (count(mbox_1_7, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_7 == FIRST_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_7 == SECOND_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_7 == SECOND_ROUND)) && (count(mbox_1_7, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_7))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_7)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_7->message->decided) && (mbox_1_7->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_7 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (count(mbox_0_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_0_5->message->decided) && (mbox_0_5->message->phase >= phase))
      {
        round_1_8 = FOURTH_ROUND;
        estimate = m->estimate;
        decided = true;
        out(p, estimate);
        phase++;
        mbox_1_8 = havoc(phase, round_1_8);
        if ((p != leader(phase, n)) && (round_1_8 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_8 == FIRST_ROUND)) && (count(mbox_1_8, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_8 == FIRST_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_8 == SECOND_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_8 == SECOND_ROUND)) && (count(mbox_1_8, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && (count(mbox_1_8, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_8))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && (count(mbox_1_8, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_8)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_8->message->decided) && (mbox_1_8->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_8 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (round_0_5 == FOURTH_ROUND)) && (decided == false)) && timeout(round_0_5))
      {
        round_1_9 = FIRST_ROUND;
        phase++;
        mbox_1_9 = havoc(phase, round_1_9);
        if ((p != leader(phase, n)) && (round_1_9 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_9 == FIRST_ROUND)) && (count(mbox_1_9, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_9 == FIRST_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_9 == SECOND_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_9 == SECOND_ROUND)) && (count(mbox_1_9, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && (count(mbox_1_9, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_9))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && (count(mbox_1_9, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_9)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_9->message->decided) && (mbox_1_9->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_9 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      continue;
    }

    if (((((p == leader(phase, n)) && (round == THIRD_ROUND)) && (count(mbox, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox)))
    {
      round_0_6 = FIRST_ROUND;
      phase++;
      mbox_0_6 = havoc(phase, round_0_6);
      if ((p != leader(phase, n)) && (round_0_6 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
        round_1_0 = SECOND_ROUND;
        mbox_1_0 = havoc(phase, round_1_0);
        if ((p != leader(phase, n)) && (round_1_0 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_0 == FIRST_ROUND)) && (count(mbox_1_0, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_0 == FIRST_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_0 == SECOND_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_0 == SECOND_ROUND)) && (count(mbox_1_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_0))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_0)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_0->message->decided) && (mbox_1_0->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_0 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p == leader(phase, n)) && (round_0_6 == FIRST_ROUND)) && (count(mbox_0_6, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
      {
        m = max_timestamp(mbox_1_1);
        estimate = m->estimate;
        round_1_1 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
        round_1_1 = THIRD_ROUND;
        mbox_1_1 = havoc(phase, round_1_1);
        if ((p != leader(phase, n)) && (round_1_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && (count(mbox_1_1, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_1 == SECOND_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_1 == SECOND_ROUND)) && (count(mbox_1_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_1))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_1)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_1->message->decided) && (mbox_1_1->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_1 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p == leader(phase, n)) && (round_0_6 == FIRST_ROUND)) && timeout(round_0_6))
      {
        round_1_2 = FIRST_ROUND;
        phase++;
        mbox_1_2 = havoc(phase, round_1_2);
        if ((p != leader(phase, n)) && (round_1_2 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && (count(mbox_1_2, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_2 == SECOND_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_2 == SECOND_ROUND)) && (count(mbox_1_2, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_2))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_2)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_2->message->decided) && (mbox_1_2->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_2 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p != leader(phase, n)) && (round_0_6 == SECOND_ROUND)) && timeout(round_0_6))
      {
        round_1_3 = FIRST_ROUND;
        phase++;
        mbox_1_3 = havoc(phase, round_1_3);
        if ((p != leader(phase, n)) && (round_1_3 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && (count(mbox_1_3, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_3 == SECOND_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_3 == SECOND_ROUND)) && (count(mbox_1_3, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_3))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_3)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_3->message->decided) && (mbox_1_3->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_3 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (round_0_6 == SECOND_ROUND)) && (count(mbox_0_6, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
      {
        round_1_4 = THIRD_ROUND;
        m = mbox_1_4->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1_4 = FOURTH_ROUND;
        mbox_1_4 = havoc(phase, round_1_4);
        if ((p != leader(phase, n)) && (round_1_4 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && (count(mbox_1_4, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_4 == SECOND_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_4 == SECOND_ROUND)) && (count(mbox_1_4, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_4))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_4)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_4->message->decided) && (mbox_1_4->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_4 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((((p == leader(phase, n)) && (round_0_6 == THIRD_ROUND)) && (count(mbox_0_6, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_0_6))
      {
        round_1_5 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
        decided = true;
        round_1_5 = FIRST_ROUND;
        phase++;
        mbox_1_5 = havoc(phase, round_1_5);
        if ((p != leader(phase, n)) && (round_1_5 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && (count(mbox_1_5, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_5 == SECOND_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_5 == SECOND_ROUND)) && (count(mbox_1_5, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_5))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_5)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_5->message->decided) && (mbox_1_5->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_5 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((((p == leader(phase, n)) && (round_0_6 == THIRD_ROUND)) && (count(mbox_0_6, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_0_6)))
      {
        round_1_6 = FIRST_ROUND;
        phase++;
        mbox_1_6 = havoc(phase, round_1_6);
        if ((p != leader(phase, n)) && (round_1_6 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_6 == FIRST_ROUND)) && (count(mbox_1_6, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_6 == FIRST_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_6 == SECOND_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_6 == SECOND_ROUND)) && (count(mbox_1_6, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_6))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_6)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_6->message->decided) && (mbox_1_6->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_6 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p == leader(phase, n)) && (round_0_6 == THIRD_ROUND)) && timeout(round_0_6))
      {
        round_1_7 = FIRST_ROUND;
        phase++;
        mbox_1_7 = havoc(phase, round_1_7);
        if ((p != leader(phase, n)) && (round_1_7 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_7 == FIRST_ROUND)) && (count(mbox_1_7, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_7 == FIRST_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_7 == SECOND_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_7 == SECOND_ROUND)) && (count(mbox_1_7, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_7))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_7)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_7->message->decided) && (mbox_1_7->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_7 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (count(mbox_0_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_0_6->message->decided) && (mbox_0_6->message->phase >= phase))
      {
        round_1_8 = FOURTH_ROUND;
        estimate = m->estimate;
        decided = true;
        out(p, estimate);
        phase++;
        mbox_1_8 = havoc(phase, round_1_8);
        if ((p != leader(phase, n)) && (round_1_8 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_8 == FIRST_ROUND)) && (count(mbox_1_8, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_8 == FIRST_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_8 == SECOND_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_8 == SECOND_ROUND)) && (count(mbox_1_8, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && (count(mbox_1_8, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_8))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && (count(mbox_1_8, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_8)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_8->message->decided) && (mbox_1_8->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_8 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (round_0_6 == FOURTH_ROUND)) && (decided == false)) && timeout(round_0_6))
      {
        round_1_9 = FIRST_ROUND;
        phase++;
        mbox_1_9 = havoc(phase, round_1_9);
        if ((p != leader(phase, n)) && (round_1_9 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_9 == FIRST_ROUND)) && (count(mbox_1_9, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_9 == FIRST_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_9 == SECOND_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_9 == SECOND_ROUND)) && (count(mbox_1_9, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && (count(mbox_1_9, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_9))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && (count(mbox_1_9, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_9)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_9->message->decided) && (mbox_1_9->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_9 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      continue;
    }

    if (((p == leader(phase, n)) && (round == THIRD_ROUND)) && timeout(round))
    {
      round_0_7 = FIRST_ROUND;
      phase++;
      mbox_0_7 = havoc(phase, round_0_7);
      if ((p != leader(phase, n)) && (round_0_7 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
        round_1_0 = SECOND_ROUND;
        mbox_1_0 = havoc(phase, round_1_0);
        if ((p != leader(phase, n)) && (round_1_0 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_0 == FIRST_ROUND)) && (count(mbox_1_0, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_0 == FIRST_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_0 == SECOND_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_0 == SECOND_ROUND)) && (count(mbox_1_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_0))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_0)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_0->message->decided) && (mbox_1_0->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_0 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p == leader(phase, n)) && (round_0_7 == FIRST_ROUND)) && (count(mbox_0_7, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
      {
        m = max_timestamp(mbox_1_1);
        estimate = m->estimate;
        round_1_1 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
        round_1_1 = THIRD_ROUND;
        mbox_1_1 = havoc(phase, round_1_1);
        if ((p != leader(phase, n)) && (round_1_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && (count(mbox_1_1, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_1 == SECOND_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_1 == SECOND_ROUND)) && (count(mbox_1_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_1))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_1)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_1->message->decided) && (mbox_1_1->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_1 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p == leader(phase, n)) && (round_0_7 == FIRST_ROUND)) && timeout(round_0_7))
      {
        round_1_2 = FIRST_ROUND;
        phase++;
        mbox_1_2 = havoc(phase, round_1_2);
        if ((p != leader(phase, n)) && (round_1_2 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && (count(mbox_1_2, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_2 == SECOND_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_2 == SECOND_ROUND)) && (count(mbox_1_2, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_2))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_2)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_2->message->decided) && (mbox_1_2->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_2 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p != leader(phase, n)) && (round_0_7 == SECOND_ROUND)) && timeout(round_0_7))
      {
        round_1_3 = FIRST_ROUND;
        phase++;
        mbox_1_3 = havoc(phase, round_1_3);
        if ((p != leader(phase, n)) && (round_1_3 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && (count(mbox_1_3, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_3 == SECOND_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_3 == SECOND_ROUND)) && (count(mbox_1_3, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_3))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_3)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_3->message->decided) && (mbox_1_3->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_3 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (round_0_7 == SECOND_ROUND)) && (count(mbox_0_7, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
      {
        round_1_4 = THIRD_ROUND;
        m = mbox_1_4->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1_4 = FOURTH_ROUND;
        mbox_1_4 = havoc(phase, round_1_4);
        if ((p != leader(phase, n)) && (round_1_4 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && (count(mbox_1_4, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_4 == SECOND_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_4 == SECOND_ROUND)) && (count(mbox_1_4, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_4))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_4)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_4->message->decided) && (mbox_1_4->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_4 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((((p == leader(phase, n)) && (round_0_7 == THIRD_ROUND)) && (count(mbox_0_7, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_0_7))
      {
        round_1_5 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
        decided = true;
        round_1_5 = FIRST_ROUND;
        phase++;
        mbox_1_5 = havoc(phase, round_1_5);
        if ((p != leader(phase, n)) && (round_1_5 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && (count(mbox_1_5, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_5 == SECOND_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_5 == SECOND_ROUND)) && (count(mbox_1_5, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_5))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_5)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_5->message->decided) && (mbox_1_5->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_5 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((((p == leader(phase, n)) && (round_0_7 == THIRD_ROUND)) && (count(mbox_0_7, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_0_7)))
      {
        round_1_6 = FIRST_ROUND;
        phase++;
        mbox_1_6 = havoc(phase, round_1_6);
        if ((p != leader(phase, n)) && (round_1_6 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_6 == FIRST_ROUND)) && (count(mbox_1_6, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_6 == FIRST_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_6 == SECOND_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_6 == SECOND_ROUND)) && (count(mbox_1_6, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_6))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_6)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_6->message->decided) && (mbox_1_6->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_6 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p == leader(phase, n)) && (round_0_7 == THIRD_ROUND)) && timeout(round_0_7))
      {
        round_1_7 = FIRST_ROUND;
        phase++;
        mbox_1_7 = havoc(phase, round_1_7);
        if ((p != leader(phase, n)) && (round_1_7 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_7 == FIRST_ROUND)) && (count(mbox_1_7, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_7 == FIRST_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_7 == SECOND_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_7 == SECOND_ROUND)) && (count(mbox_1_7, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_7))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_7)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_7->message->decided) && (mbox_1_7->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_7 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (count(mbox_0_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_0_7->message->decided) && (mbox_0_7->message->phase >= phase))
      {
        round_1_8 = FOURTH_ROUND;
        estimate = m->estimate;
        decided = true;
        out(p, estimate);
        phase++;
        mbox_1_8 = havoc(phase, round_1_8);
        if ((p != leader(phase, n)) && (round_1_8 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_8 == FIRST_ROUND)) && (count(mbox_1_8, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_8 == FIRST_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_8 == SECOND_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_8 == SECOND_ROUND)) && (count(mbox_1_8, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && (count(mbox_1_8, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_8))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && (count(mbox_1_8, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_8)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_8->message->decided) && (mbox_1_8->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_8 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (round_0_7 == FOURTH_ROUND)) && (decided == false)) && timeout(round_0_7))
      {
        round_1_9 = FIRST_ROUND;
        phase++;
        mbox_1_9 = havoc(phase, round_1_9);
        if ((p != leader(phase, n)) && (round_1_9 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_9 == FIRST_ROUND)) && (count(mbox_1_9, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_9 == FIRST_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_9 == SECOND_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_9 == SECOND_ROUND)) && (count(mbox_1_9, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && (count(mbox_1_9, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_9))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && (count(mbox_1_9, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_9)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_9->message->decided) && (mbox_1_9->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_9 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      continue;
    }

    if ((((p != leader(phase, n)) && (count(mbox, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox->message->decided) && (mbox->message->phase >= phase))
    {
      round_0_8 = FOURTH_ROUND;
      estimate = m->estimate;
      decided = true;
      out(p, estimate);
      phase++;
      mbox_0_8 = havoc(phase, round_0_8);
      if ((p != leader(phase, n)) && (round_0_8 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
        round_1_0 = SECOND_ROUND;
        mbox_1_0 = havoc(phase, round_1_0);
        if ((p != leader(phase, n)) && (round_1_0 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_0 == FIRST_ROUND)) && (count(mbox_1_0, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_0 == FIRST_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_0 == SECOND_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_0 == SECOND_ROUND)) && (count(mbox_1_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_0))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_0)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_0->message->decided) && (mbox_1_0->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_0 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p == leader(phase, n)) && (round_0_8 == FIRST_ROUND)) && (count(mbox_0_8, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
      {
        m = max_timestamp(mbox_1_1);
        estimate = m->estimate;
        round_1_1 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
        round_1_1 = THIRD_ROUND;
        mbox_1_1 = havoc(phase, round_1_1);
        if ((p != leader(phase, n)) && (round_1_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && (count(mbox_1_1, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_1 == SECOND_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_1 == SECOND_ROUND)) && (count(mbox_1_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_1))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_1)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_1->message->decided) && (mbox_1_1->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_1 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p == leader(phase, n)) && (round_0_8 == FIRST_ROUND)) && timeout(round_0_8))
      {
        round_1_2 = FIRST_ROUND;
        phase++;
        mbox_1_2 = havoc(phase, round_1_2);
        if ((p != leader(phase, n)) && (round_1_2 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && (count(mbox_1_2, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_2 == SECOND_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_2 == SECOND_ROUND)) && (count(mbox_1_2, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_2))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_2)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_2->message->decided) && (mbox_1_2->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_2 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p != leader(phase, n)) && (round_0_8 == SECOND_ROUND)) && timeout(round_0_8))
      {
        round_1_3 = FIRST_ROUND;
        phase++;
        mbox_1_3 = havoc(phase, round_1_3);
        if ((p != leader(phase, n)) && (round_1_3 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && (count(mbox_1_3, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_3 == SECOND_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_3 == SECOND_ROUND)) && (count(mbox_1_3, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_3))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_3)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_3->message->decided) && (mbox_1_3->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_3 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (round_0_8 == SECOND_ROUND)) && (count(mbox_0_8, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
      {
        round_1_4 = THIRD_ROUND;
        m = mbox_1_4->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1_4 = FOURTH_ROUND;
        mbox_1_4 = havoc(phase, round_1_4);
        if ((p != leader(phase, n)) && (round_1_4 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && (count(mbox_1_4, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_4 == SECOND_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_4 == SECOND_ROUND)) && (count(mbox_1_4, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_4))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_4)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_4->message->decided) && (mbox_1_4->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_4 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((((p == leader(phase, n)) && (round_0_8 == THIRD_ROUND)) && (count(mbox_0_8, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_0_8))
      {
        round_1_5 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
        decided = true;
        round_1_5 = FIRST_ROUND;
        phase++;
        mbox_1_5 = havoc(phase, round_1_5);
        if ((p != leader(phase, n)) && (round_1_5 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && (count(mbox_1_5, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_5 == SECOND_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_5 == SECOND_ROUND)) && (count(mbox_1_5, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_5))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_5)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_5->message->decided) && (mbox_1_5->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_5 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((((p == leader(phase, n)) && (round_0_8 == THIRD_ROUND)) && (count(mbox_0_8, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_0_8)))
      {
        round_1_6 = FIRST_ROUND;
        phase++;
        mbox_1_6 = havoc(phase, round_1_6);
        if ((p != leader(phase, n)) && (round_1_6 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_6 == FIRST_ROUND)) && (count(mbox_1_6, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_6 == FIRST_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_6 == SECOND_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_6 == SECOND_ROUND)) && (count(mbox_1_6, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_6))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_6)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_6->message->decided) && (mbox_1_6->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_6 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p == leader(phase, n)) && (round_0_8 == THIRD_ROUND)) && timeout(round_0_8))
      {
        round_1_7 = FIRST_ROUND;
        phase++;
        mbox_1_7 = havoc(phase, round_1_7);
        if ((p != leader(phase, n)) && (round_1_7 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_7 == FIRST_ROUND)) && (count(mbox_1_7, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_7 == FIRST_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_7 == SECOND_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_7 == SECOND_ROUND)) && (count(mbox_1_7, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_7))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_7)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_7->message->decided) && (mbox_1_7->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_7 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (count(mbox_0_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_0_8->message->decided) && (mbox_0_8->message->phase >= phase))
      {
        round_1_8 = FOURTH_ROUND;
        estimate = m->estimate;
        decided = true;
        out(p, estimate);
        phase++;
        mbox_1_8 = havoc(phase, round_1_8);
        if ((p != leader(phase, n)) && (round_1_8 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_8 == FIRST_ROUND)) && (count(mbox_1_8, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_8 == FIRST_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_8 == SECOND_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_8 == SECOND_ROUND)) && (count(mbox_1_8, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && (count(mbox_1_8, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_8))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && (count(mbox_1_8, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_8)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_8->message->decided) && (mbox_1_8->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_8 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (round_0_8 == FOURTH_ROUND)) && (decided == false)) && timeout(round_0_8))
      {
        round_1_9 = FIRST_ROUND;
        phase++;
        mbox_1_9 = havoc(phase, round_1_9);
        if ((p != leader(phase, n)) && (round_1_9 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_9 == FIRST_ROUND)) && (count(mbox_1_9, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_9 == FIRST_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_9 == SECOND_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_9 == SECOND_ROUND)) && (count(mbox_1_9, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && (count(mbox_1_9, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_9))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && (count(mbox_1_9, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_9)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_9->message->decided) && (mbox_1_9->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_9 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      continue;
    }

    if ((((p != leader(phase, n)) && (round == FOURTH_ROUND)) && (decided == false)) && timeout(round))
    {
      round_0_9 = FIRST_ROUND;
      phase++;
      mbox_0_9 = havoc(phase, round_0_9);
      if ((p != leader(phase, n)) && (round_0_9 == FIRST_ROUND))
      {
        send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
        round_1_0 = SECOND_ROUND;
        mbox_1_0 = havoc(phase, round_1_0);
        if ((p != leader(phase, n)) && (round_1_0 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_0 == FIRST_ROUND)) && (count(mbox_1_0, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_0 == FIRST_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_0 == SECOND_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_0 == SECOND_ROUND)) && (count(mbox_1_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_0))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_0)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_0, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_0->message->decided) && (mbox_1_0->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_0 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_0))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p == leader(phase, n)) && (round_0_9 == FIRST_ROUND)) && (count(mbox_0_9, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
      {
        m = max_timestamp(mbox_1_1);
        estimate = m->estimate;
        round_1_1 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
        round_1_1 = THIRD_ROUND;
        mbox_1_1 = havoc(phase, round_1_1);
        if ((p != leader(phase, n)) && (round_1_1 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && (count(mbox_1_1, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_1 == SECOND_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_1 == SECOND_ROUND)) && (count(mbox_1_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_1))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_1)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_1, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_1->message->decided) && (mbox_1_1->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_1 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_1))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p == leader(phase, n)) && (round_0_9 == FIRST_ROUND)) && timeout(round_0_9))
      {
        round_1_2 = FIRST_ROUND;
        phase++;
        mbox_1_2 = havoc(phase, round_1_2);
        if ((p != leader(phase, n)) && (round_1_2 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && (count(mbox_1_2, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_2 == SECOND_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_2 == SECOND_ROUND)) && (count(mbox_1_2, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_2))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_2)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_2, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_2->message->decided) && (mbox_1_2->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_2 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_2))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p != leader(phase, n)) && (round_0_9 == SECOND_ROUND)) && timeout(round_0_9))
      {
        round_1_3 = FIRST_ROUND;
        phase++;
        mbox_1_3 = havoc(phase, round_1_3);
        if ((p != leader(phase, n)) && (round_1_3 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && (count(mbox_1_3, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_3 == SECOND_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_3 == SECOND_ROUND)) && (count(mbox_1_3, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_3))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_3)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_3, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_3->message->decided) && (mbox_1_3->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_3 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_3))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (round_0_9 == SECOND_ROUND)) && (count(mbox_0_9, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
      {
        round_1_4 = THIRD_ROUND;
        m = mbox_1_4->message;
        estimate = m->estimate;
        timestamp = phase;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
        round_1_4 = FOURTH_ROUND;
        mbox_1_4 = havoc(phase, round_1_4);
        if ((p != leader(phase, n)) && (round_1_4 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && (count(mbox_1_4, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_4 == SECOND_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_4 == SECOND_ROUND)) && (count(mbox_1_4, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_4))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_4)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_4, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_4->message->decided) && (mbox_1_4->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_4 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_4))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((((p == leader(phase, n)) && (round_0_9 == THIRD_ROUND)) && (count(mbox_0_9, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_0_9))
      {
        round_1_5 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
        decided = true;
        round_1_5 = FIRST_ROUND;
        phase++;
        mbox_1_5 = havoc(phase, round_1_5);
        if ((p != leader(phase, n)) && (round_1_5 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && (count(mbox_1_5, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_5 == SECOND_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_5 == SECOND_ROUND)) && (count(mbox_1_5, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_5))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_5)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_5, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_5->message->decided) && (mbox_1_5->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_5 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_5))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((((p == leader(phase, n)) && (round_0_9 == THIRD_ROUND)) && (count(mbox_0_9, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_0_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_0_9)))
      {
        round_1_6 = FIRST_ROUND;
        phase++;
        mbox_1_6 = havoc(phase, round_1_6);
        if ((p != leader(phase, n)) && (round_1_6 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_6 == FIRST_ROUND)) && (count(mbox_1_6, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_6 == FIRST_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_6 == SECOND_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_6 == SECOND_ROUND)) && (count(mbox_1_6, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_6))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_6)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_6, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_6->message->decided) && (mbox_1_6->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_6 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_6))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if (((p == leader(phase, n)) && (round_0_9 == THIRD_ROUND)) && timeout(round_0_9))
      {
        round_1_7 = FIRST_ROUND;
        phase++;
        mbox_1_7 = havoc(phase, round_1_7);
        if ((p != leader(phase, n)) && (round_1_7 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_7 == FIRST_ROUND)) && (count(mbox_1_7, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_7 == FIRST_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_7 == SECOND_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_7 == SECOND_ROUND)) && (count(mbox_1_7, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_7))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && (count(mbox_1_7, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_7)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_7 == THIRD_ROUND)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_7, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_7->message->decided) && (mbox_1_7->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_7 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_7))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (count(mbox_0_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_0_9->message->decided) && (mbox_0_9->message->phase >= phase))
      {
        round_1_8 = FOURTH_ROUND;
        estimate = m->estimate;
        decided = true;
        out(p, estimate);
        phase++;
        mbox_1_8 = havoc(phase, round_1_8);
        if ((p != leader(phase, n)) && (round_1_8 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_8 == FIRST_ROUND)) && (count(mbox_1_8, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_8 == FIRST_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_8 == SECOND_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_8 == SECOND_ROUND)) && (count(mbox_1_8, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && (count(mbox_1_8, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_8))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && (count(mbox_1_8, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_8)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_8 == THIRD_ROUND)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_8, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_8->message->decided) && (mbox_1_8->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_8 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_8))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      if ((((p != leader(phase, n)) && (round_0_9 == FOURTH_ROUND)) && (decided == false)) && timeout(round_0_9))
      {
        round_1_9 = FIRST_ROUND;
        phase++;
        mbox_1_9 = havoc(phase, round_1_9);
        if ((p != leader(phase, n)) && (round_1_9 == FIRST_ROUND))
        {
          send(message(phase, FIRST_ROUND, estimate, p, timestamp, BOOL_NULL), leader(phase, n));
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_9 == FIRST_ROUND)) && (count(mbox_1_9, phase, FIRST_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, INT_NULL, BOOL_NULL), to_all);
          round_2_0 = THIRD_ROUND;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_9 == FIRST_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p != leader(phase, n)) && (round_1_9 == SECOND_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_9 == SECOND_ROUND)) && (count(mbox_1_9, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0))
        {
          round_2_0 = THIRD_ROUND;
          m = mbox_2_0->message;
          estimate = m->estimate;
          timestamp = phase;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, true), leader(phase, n));
          round_2_0 = FOURTH_ROUND;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && (count(mbox_1_9, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && all_ack(mbox_1_9))
        {
          round_2_0 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, INT_NULL, true), to_all);
          decided = true;
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && (count(mbox_1_9, phase, THIRD_ROUND, INT_NULL) > ((n + 1) / 2))) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 0)) && (!all_ack(mbox_1_9)))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if (((p == leader(phase, n)) && (round_1_9 == THIRD_ROUND)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (count(mbox_1_9, INT_NULL, FOURTH_ROUND, INT_NULL) == 1)) && mbox_1_9->message->decided) && (mbox_1_9->message->phase >= phase))
        {
          round_2_0 = FOURTH_ROUND;
          estimate = m->estimate;
          decided = true;
          out(p, estimate);
          phase++;
          continue;
        }

        if ((((p != leader(phase, n)) && (round_1_9 == FOURTH_ROUND)) && (decided == false)) && timeout(round_1_9))
        {
          round_2_0 = FIRST_ROUND;
          phase++;
          continue;
        }

        continue;
      }

      continue;
    }

  }

}


