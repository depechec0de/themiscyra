typedef struct Msg
{
  int round;
  int phase;
  int estimate;
  int timestamp;
  int response;
  int sender;
  _Bool decided;
} msg;
typedef struct List
{
  msg *message;
  struct List *next;
  int size;
} list;
enum round_typ
{
  FIRST_ROUND,
  SECOND_ROUND,
  THIRD_ROUND,
  FOURTH_ROUND
};
enum ack_typ
{
  ACK,
  NACK
};
msg *recv();
void out(int v1, int v2);
int in();
int timeout();
int reset_timeout();
int rand_bool();
msg *max_timestamp(struct List *mbox);
int all_ack(struct List *mbox);
void dispose(msg *c);
void list_dispose(struct List *l);
void send(msg *message, int pid);
int leader(int phase, int net_size);
int all_agree(struct List *l);
msg *message(int phase, enum round_typ round, int estimate, int p, int timestamp, int response, _Bool decided);
int true = 1;
int main(int p, int n, int f)
{
  list *mbox_2_6 = NULL;
  list *mbox_2_5 = NULL;
  list *mbox_2_4 = NULL;
  list *mbox_2_3 = NULL;
  list *mbox_2_2 = NULL;
  list *mbox_2_1 = NULL;
  list *mbox_2_0 = NULL;
  list *mbox_1_6 = NULL;
  list *mbox_1_5 = NULL;
  list *mbox_1_4 = NULL;
  list *mbox_1_3 = NULL;
  list *mbox_1_2 = NULL;
  list *mbox_1_1 = NULL;
  list *mbox_1_0 = NULL;
  list *mbox_0_6 = NULL;
  list *mbox_0_5 = NULL;
  list *mbox_0_4 = NULL;
  list *mbox_0_3 = NULL;
  list *mbox_0_2 = NULL;
  list *mbox_0_1 = NULL;
  list *mbox_0_0 = NULL;
  enum round_typ round_2_6;
  enum round_typ round_2_5;
  enum round_typ round_2_4;
  enum round_typ round_2_3;
  enum round_typ round_2_2;
  enum round_typ round_2_1;
  enum round_typ round_2_0;
  enum round_typ round_1_6;
  enum round_typ round_1_5;
  enum round_typ round_1_4;
  enum round_typ round_1_3;
  enum round_typ round_1_2;
  enum round_typ round_1_1;
  enum round_typ round_1_0;
  enum round_typ round_0_6;
  enum round_typ round_0_5;
  enum round_typ round_0_4;
  enum round_typ round_0_3;
  enum round_typ round_0_2;
  enum round_typ round_0_1;
  enum round_typ round_0_0;
  int timestamp;
  int phase;
  enum round_typ round;
  int ack;
  int to_all = n + 1;
  int estimate;
  int state;
  list *mbox = NULL;
  list *mbox_new = NULL;
  msg *m = NULL;
  phase = 1;
  round = FIRST_ROUND;
  estimate = in();
  state = 0;
  timestamp = 0;
  send(message(phase, FIRST_ROUND, estimate, p, timestamp, NULL, NULL), leader(phase, n));
  while (1)
  {
    mbox = havoc();
    if ((p != leader(phase, n)) && (round == FIRST_ROUND))
    {
      round_0_0 = SECOND_ROUND;
      mbox_0_0 = havoc();
      if ((p != leader(phase, n)) && (round_0_0 == FIRST_ROUND))
      {
        round_1_0 = SECOND_ROUND;
        mbox_1_0 = havoc();
        if ((p != leader(phase, n)) && (round_1_0 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_0 == FIRST_ROUND)) && (count(mbox_1_0, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_0, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_0 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_0 == SECOND_ROUND) && (count(mbox_1_0, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_0, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_0, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_0, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((p == leader(phase, n)) && (round_0_0 == FIRST_ROUND)) && (count(mbox_0_0, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_0_0, FOURTH_ROUND) == 0))
      {
        m = max_timestamp(mbox_1_1);
        estimate = m->estimate;
        round_1_1 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
        mbox_1_1 = havoc();
        if ((p != leader(phase, n)) && (round_1_1 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && (count(mbox_1_1, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_1, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_1 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_1 == SECOND_ROUND) && (count(mbox_1_1, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_1, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_1, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_1, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((round_0_0 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
      {
        round_1_2 = THIRD_ROUND;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
        phase++;
        round_1_2 = FIRST_ROUND;
        mbox_1_2 = havoc();
        if ((p != leader(phase, n)) && (round_1_2 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && (count(mbox_1_2, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_2, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_2 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_2 == SECOND_ROUND) && (count(mbox_1_2, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_2, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_2, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_2, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

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

        mbox_1_3 = havoc();
        if ((p != leader(phase, n)) && (round_1_3 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && (count(mbox_1_3, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_3, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_3 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_3 == SECOND_ROUND) && (count(mbox_1_3, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_3, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_3, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_3, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((p == leader(phase, n)) && (round_0_0 == THIRD_ROUND)) && (count(mbox_0_0, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_0_0, FOURTH_ROUND) == 0))
      {
        if (all_ack(mbox_1_4) == 1)
        {
          round_1_4 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
        }

        phase++;
        round_1_4 = FIRST_ROUND;
        mbox_1_4 = havoc();
        if ((p != leader(phase, n)) && (round_1_4 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && (count(mbox_1_4, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_4, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_4 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_4 == SECOND_ROUND) && (count(mbox_1_4, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_4, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_4, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_4, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (count(mbox_0_0, FOURTH_ROUND) > 0)
      {
        round_1_5 = FOURTH_ROUND;
        if (mbox_1_5->message->decided)
        {
          estimate = mbox_1_5->message->estimate;
          out(p, estimate);
        }

        phase++;
        round_1_5 = FIRST_ROUND;
        mbox_1_5 = havoc();
        if ((p != leader(phase, n)) && (round_1_5 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && (count(mbox_1_5, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_5, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_5 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_5 == SECOND_ROUND) && (count(mbox_1_5, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_5, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_5, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_5, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      continue;
    }

    if ((((p == leader(phase, n)) && (round == FIRST_ROUND)) && (count(mbox, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox, FOURTH_ROUND) == 0))
    {
      m = max_timestamp(mbox_0_1);
      estimate = m->estimate;
      round_0_1 = SECOND_ROUND;
      send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
      mbox_0_1 = havoc();
      if ((p != leader(phase, n)) && (round_0_1 == FIRST_ROUND))
      {
        round_1_0 = SECOND_ROUND;
        mbox_1_0 = havoc();
        if ((p != leader(phase, n)) && (round_1_0 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_0 == FIRST_ROUND)) && (count(mbox_1_0, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_0, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_0 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_0 == SECOND_ROUND) && (count(mbox_1_0, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_0, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_0, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_0, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((p == leader(phase, n)) && (round_0_1 == FIRST_ROUND)) && (count(mbox_0_1, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_0_1, FOURTH_ROUND) == 0))
      {
        m = max_timestamp(mbox_1_1);
        estimate = m->estimate;
        round_1_1 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
        mbox_1_1 = havoc();
        if ((p != leader(phase, n)) && (round_1_1 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && (count(mbox_1_1, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_1, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_1 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_1 == SECOND_ROUND) && (count(mbox_1_1, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_1, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_1, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_1, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((round_0_1 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
      {
        round_1_2 = THIRD_ROUND;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
        phase++;
        round_1_2 = FIRST_ROUND;
        mbox_1_2 = havoc();
        if ((p != leader(phase, n)) && (round_1_2 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && (count(mbox_1_2, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_2, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_2 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_2 == SECOND_ROUND) && (count(mbox_1_2, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_2, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_2, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_2, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((round_0_1 == SECOND_ROUND) && (count(mbox_0_1, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_0_1, FOURTH_ROUND) == 0))
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

        mbox_1_3 = havoc();
        if ((p != leader(phase, n)) && (round_1_3 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && (count(mbox_1_3, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_3, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_3 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_3 == SECOND_ROUND) && (count(mbox_1_3, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_3, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_3, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_3, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((p == leader(phase, n)) && (round_0_1 == THIRD_ROUND)) && (count(mbox_0_1, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_0_1, FOURTH_ROUND) == 0))
      {
        if (all_ack(mbox_1_4) == 1)
        {
          round_1_4 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
        }

        phase++;
        round_1_4 = FIRST_ROUND;
        mbox_1_4 = havoc();
        if ((p != leader(phase, n)) && (round_1_4 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && (count(mbox_1_4, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_4, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_4 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_4 == SECOND_ROUND) && (count(mbox_1_4, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_4, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_4, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_4, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (count(mbox_0_1, FOURTH_ROUND) > 0)
      {
        round_1_5 = FOURTH_ROUND;
        if (mbox_1_5->message->decided)
        {
          estimate = mbox_1_5->message->estimate;
          out(p, estimate);
        }

        phase++;
        round_1_5 = FIRST_ROUND;
        mbox_1_5 = havoc();
        if ((p != leader(phase, n)) && (round_1_5 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && (count(mbox_1_5, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_5, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_5 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_5 == SECOND_ROUND) && (count(mbox_1_5, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_5, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_5, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_5, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      continue;
    }

    if ((round == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
    {
      round_0_2 = THIRD_ROUND;
      send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
      phase++;
      round_0_2 = FIRST_ROUND;
      mbox_0_2 = havoc();
      if ((p != leader(phase, n)) && (round_0_2 == FIRST_ROUND))
      {
        round_1_0 = SECOND_ROUND;
        mbox_1_0 = havoc();
        if ((p != leader(phase, n)) && (round_1_0 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_0 == FIRST_ROUND)) && (count(mbox_1_0, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_0, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_0 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_0 == SECOND_ROUND) && (count(mbox_1_0, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_0, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_0 == THIRD_ROUND)) && (count(mbox_1_0, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_0, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_0, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((p == leader(phase, n)) && (round_0_2 == FIRST_ROUND)) && (count(mbox_0_2, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_0_2, FOURTH_ROUND) == 0))
      {
        m = max_timestamp(mbox_1_1);
        estimate = m->estimate;
        round_1_1 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
        mbox_1_1 = havoc();
        if ((p != leader(phase, n)) && (round_1_1 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && (count(mbox_1_1, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_1, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_1 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_1 == SECOND_ROUND) && (count(mbox_1_1, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_1, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_1, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_1, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((round_0_2 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
      {
        round_1_2 = THIRD_ROUND;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
        phase++;
        round_1_2 = FIRST_ROUND;
        mbox_1_2 = havoc();
        if ((p != leader(phase, n)) && (round_1_2 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && (count(mbox_1_2, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_2, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_2 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_2 == SECOND_ROUND) && (count(mbox_1_2, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_2, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_2, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_2, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((round_0_2 == SECOND_ROUND) && (count(mbox_0_2, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_0_2, FOURTH_ROUND) == 0))
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

        mbox_1_3 = havoc();
        if ((p != leader(phase, n)) && (round_1_3 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && (count(mbox_1_3, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_3, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_3 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_3 == SECOND_ROUND) && (count(mbox_1_3, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_3, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_3, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_3, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((p == leader(phase, n)) && (round_0_2 == THIRD_ROUND)) && (count(mbox_0_2, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_0_2, FOURTH_ROUND) == 0))
      {
        if (all_ack(mbox_1_4) == 1)
        {
          round_1_4 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
        }

        phase++;
        round_1_4 = FIRST_ROUND;
        mbox_1_4 = havoc();
        if ((p != leader(phase, n)) && (round_1_4 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && (count(mbox_1_4, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_4, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_4 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_4 == SECOND_ROUND) && (count(mbox_1_4, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_4, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_4, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_4, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (count(mbox_0_2, FOURTH_ROUND) > 0)
      {
        round_1_5 = FOURTH_ROUND;
        if (mbox_1_5->message->decided)
        {
          estimate = mbox_1_5->message->estimate;
          out(p, estimate);
        }

        phase++;
        round_1_5 = FIRST_ROUND;
        mbox_1_5 = havoc();
        if ((p != leader(phase, n)) && (round_1_5 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && (count(mbox_1_5, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_5, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_5 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_5 == SECOND_ROUND) && (count(mbox_1_5, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_5, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_5, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_5, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      continue;
    }

    if (((round == SECOND_ROUND) && (count(mbox, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox, FOURTH_ROUND) == 0))
    {
      estimate = mbox_0_3->message->estimate;
      timestamp = phase;
      ack = 1;
      round_0_3 = THIRD_ROUND;
      send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
      if (p != leader(phase, n))
      {
        round_0_3 = FOURTH_ROUND;
      }

      mbox_0_3 = havoc();
      if ((p != leader(phase, n)) && (round_0_3 == FIRST_ROUND))
      {
        round_1_1 = SECOND_ROUND;
        mbox_1_1 = havoc();
        if ((p != leader(phase, n)) && (round_1_1 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && (count(mbox_1_1, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_1, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_1 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_1 == SECOND_ROUND) && (count(mbox_1_1, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_1, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_1, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_1, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((p == leader(phase, n)) && (round_0_3 == FIRST_ROUND)) && (count(mbox_0_3, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_0_3, FOURTH_ROUND) == 0))
      {
        m = max_timestamp(mbox_1_2);
        estimate = m->estimate;
        round_1_2 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
        mbox_1_2 = havoc();
        if ((p != leader(phase, n)) && (round_1_2 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && (count(mbox_1_2, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_2, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_2 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_2 == SECOND_ROUND) && (count(mbox_1_2, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_2, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_2, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_2, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((round_0_3 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
      {
        round_1_3 = THIRD_ROUND;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
        phase++;
        round_1_3 = FIRST_ROUND;
        mbox_1_3 = havoc();
        if ((p != leader(phase, n)) && (round_1_3 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && (count(mbox_1_3, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_3, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_3 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_3 == SECOND_ROUND) && (count(mbox_1_3, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_3, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_3, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_3, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((round_0_3 == SECOND_ROUND) && (count(mbox_0_3, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_0_3, FOURTH_ROUND) == 0))
      {
        estimate = mbox_1_4->message->estimate;
        timestamp = phase;
        ack = 1;
        round_1_4 = THIRD_ROUND;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
        if (p != leader(phase, n))
        {
          round_1_4 = FOURTH_ROUND;
        }

        mbox_1_4 = havoc();
        if ((p != leader(phase, n)) && (round_1_4 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && (count(mbox_1_4, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_4, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_4 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_4 == SECOND_ROUND) && (count(mbox_1_4, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_4, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_4, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_4, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((p == leader(phase, n)) && (round_0_3 == THIRD_ROUND)) && (count(mbox_0_3, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_0_3, FOURTH_ROUND) == 0))
      {
        if (all_ack(mbox_1_5) == 1)
        {
          round_1_5 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
        }

        phase++;
        round_1_5 = FIRST_ROUND;
        mbox_1_5 = havoc();
        if ((p != leader(phase, n)) && (round_1_5 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && (count(mbox_1_5, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_5, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_5 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_5 == SECOND_ROUND) && (count(mbox_1_5, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_5, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_5, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_5, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (count(mbox_0_3, FOURTH_ROUND) > 0)
      {
        round_1_6 = FOURTH_ROUND;
        if (mbox_1_6->message->decided)
        {
          estimate = mbox_1_6->message->estimate;
          out(p, estimate);
        }

        phase++;
        round_1_6 = FIRST_ROUND;
        mbox_1_6 = havoc();
        if ((p != leader(phase, n)) && (round_1_6 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_6 == FIRST_ROUND)) && (count(mbox_1_6, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_6, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_6 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_6 == SECOND_ROUND) && (count(mbox_1_6, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_6, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_6, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_6, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      continue;
    }

    if ((((p == leader(phase, n)) && (round == THIRD_ROUND)) && (count(mbox, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox, FOURTH_ROUND) == 0))
    {
      if (all_ack(mbox_0_4) == 1)
      {
        round_0_4 = FOURTH_ROUND;
        send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
      }

      phase++;
      round_0_4 = FIRST_ROUND;
      mbox_0_4 = havoc();
      if ((p != leader(phase, n)) && (round_0_4 == FIRST_ROUND))
      {
        round_1_1 = SECOND_ROUND;
        mbox_1_1 = havoc();
        if ((p != leader(phase, n)) && (round_1_1 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && (count(mbox_1_1, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_1, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_1 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_1 == SECOND_ROUND) && (count(mbox_1_1, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_1, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_1, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_1, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((p == leader(phase, n)) && (round_0_4 == FIRST_ROUND)) && (count(mbox_0_4, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_0_4, FOURTH_ROUND) == 0))
      {
        m = max_timestamp(mbox_1_2);
        estimate = m->estimate;
        round_1_2 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
        mbox_1_2 = havoc();
        if ((p != leader(phase, n)) && (round_1_2 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && (count(mbox_1_2, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_2, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_2 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_2 == SECOND_ROUND) && (count(mbox_1_2, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_2, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_2, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_2, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((round_0_4 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
      {
        round_1_3 = THIRD_ROUND;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
        phase++;
        round_1_3 = FIRST_ROUND;
        mbox_1_3 = havoc();
        if ((p != leader(phase, n)) && (round_1_3 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && (count(mbox_1_3, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_3, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_3 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_3 == SECOND_ROUND) && (count(mbox_1_3, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_3, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_3, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_3, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((round_0_4 == SECOND_ROUND) && (count(mbox_0_4, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_0_4, FOURTH_ROUND) == 0))
      {
        estimate = mbox_1_4->message->estimate;
        timestamp = phase;
        ack = 1;
        round_1_4 = THIRD_ROUND;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
        if (p != leader(phase, n))
        {
          round_1_4 = FOURTH_ROUND;
        }

        mbox_1_4 = havoc();
        if ((p != leader(phase, n)) && (round_1_4 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && (count(mbox_1_4, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_4, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_4 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_4 == SECOND_ROUND) && (count(mbox_1_4, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_4, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_4, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_4, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((p == leader(phase, n)) && (round_0_4 == THIRD_ROUND)) && (count(mbox_0_4, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_0_4, FOURTH_ROUND) == 0))
      {
        if (all_ack(mbox_1_5) == 1)
        {
          round_1_5 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
        }

        phase++;
        round_1_5 = FIRST_ROUND;
        mbox_1_5 = havoc();
        if ((p != leader(phase, n)) && (round_1_5 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && (count(mbox_1_5, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_5, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_5 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_5 == SECOND_ROUND) && (count(mbox_1_5, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_5, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_5, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_5, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (count(mbox_0_4, FOURTH_ROUND) > 0)
      {
        round_1_6 = FOURTH_ROUND;
        if (mbox_1_6->message->decided)
        {
          estimate = mbox_1_6->message->estimate;
          out(p, estimate);
        }

        phase++;
        round_1_6 = FIRST_ROUND;
        mbox_1_6 = havoc();
        if ((p != leader(phase, n)) && (round_1_6 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_6 == FIRST_ROUND)) && (count(mbox_1_6, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_6, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_6 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_6 == SECOND_ROUND) && (count(mbox_1_6, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_6, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_6, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_6, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      continue;
    }

    if (count(mbox, FOURTH_ROUND) > 0)
    {
      round_0_5 = FOURTH_ROUND;
      if (mbox_0_5->message->decided)
      {
        estimate = mbox_0_5->message->estimate;
        out(p, estimate);
      }

      phase++;
      round_0_5 = FIRST_ROUND;
      mbox_0_5 = havoc();
      if ((p != leader(phase, n)) && (round_0_5 == FIRST_ROUND))
      {
        round_1_1 = SECOND_ROUND;
        mbox_1_1 = havoc();
        if ((p != leader(phase, n)) && (round_1_1 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_1 == FIRST_ROUND)) && (count(mbox_1_1, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_1, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_1 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_1 == SECOND_ROUND) && (count(mbox_1_1, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_1, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_1 == THIRD_ROUND)) && (count(mbox_1_1, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_1, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_1, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((p == leader(phase, n)) && (round_0_5 == FIRST_ROUND)) && (count(mbox_0_5, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_0_5, FOURTH_ROUND) == 0))
      {
        m = max_timestamp(mbox_1_2);
        estimate = m->estimate;
        round_1_2 = SECOND_ROUND;
        send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
        mbox_1_2 = havoc();
        if ((p != leader(phase, n)) && (round_1_2 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_2 == FIRST_ROUND)) && (count(mbox_1_2, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_2, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_2 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_2 == SECOND_ROUND) && (count(mbox_1_2, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_2, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_2 == THIRD_ROUND)) && (count(mbox_1_2, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_2, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_2, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((round_0_5 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
      {
        round_1_3 = THIRD_ROUND;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
        phase++;
        round_1_3 = FIRST_ROUND;
        mbox_1_3 = havoc();
        if ((p != leader(phase, n)) && (round_1_3 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_3 == FIRST_ROUND)) && (count(mbox_1_3, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_3, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_3 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_3 == SECOND_ROUND) && (count(mbox_1_3, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_3, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_3, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_3, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (((round_0_5 == SECOND_ROUND) && (count(mbox_0_5, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_0_5, FOURTH_ROUND) == 0))
      {
        estimate = mbox_1_4->message->estimate;
        timestamp = phase;
        ack = 1;
        round_1_4 = THIRD_ROUND;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
        if (p != leader(phase, n))
        {
          round_1_4 = FOURTH_ROUND;
        }

        mbox_1_4 = havoc();
        if ((p != leader(phase, n)) && (round_1_4 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_4 == FIRST_ROUND)) && (count(mbox_1_4, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_4, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_4 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_4 == SECOND_ROUND) && (count(mbox_1_4, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_4, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_4 == THIRD_ROUND)) && (count(mbox_1_4, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_4, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_4, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if ((((p == leader(phase, n)) && (round_0_5 == THIRD_ROUND)) && (count(mbox_0_5, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_0_5, FOURTH_ROUND) == 0))
      {
        if (all_ack(mbox_1_5) == 1)
        {
          round_1_5 = FOURTH_ROUND;
          send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
        }

        phase++;
        round_1_5 = FIRST_ROUND;
        mbox_1_5 = havoc();
        if ((p != leader(phase, n)) && (round_1_5 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_5 == FIRST_ROUND)) && (count(mbox_1_5, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_5, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_5 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_5 == SECOND_ROUND) && (count(mbox_1_5, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_5, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_5 == THIRD_ROUND)) && (count(mbox_1_5, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_5, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_5, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      if (count(mbox_0_5, FOURTH_ROUND) > 0)
      {
        round_1_6 = FOURTH_ROUND;
        if (mbox_1_6->message->decided)
        {
          estimate = mbox_1_6->message->estimate;
          out(p, estimate);
        }

        phase++;
        round_1_6 = FIRST_ROUND;
        mbox_1_6 = havoc();
        if ((p != leader(phase, n)) && (round_1_6 == FIRST_ROUND))
        {
          round_2_0 = SECOND_ROUND;
          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_6 == FIRST_ROUND)) && (count(mbox_1_6, FIRST_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_6, FOURTH_ROUND) == 0))
        {
          m = max_timestamp(mbox_2_0);
          estimate = m->estimate;
          round_2_0 = SECOND_ROUND;
          send(message(phase, SECOND_ROUND, estimate, p, NULL, NULL, NULL), to_all);
          continue;
        }

        if ((round_1_6 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
        {
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (((round_1_6 == SECOND_ROUND) && (count(mbox_1_6, SECOND_ROUND, phase, leader(phase, n)) > 0)) && (count(mbox_1_6, FOURTH_ROUND) == 0))
        {
          estimate = mbox_2_0->message->estimate;
          timestamp = phase;
          ack = 1;
          round_2_0 = THIRD_ROUND;
          send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
          if (p != leader(phase, n))
          {
            round_2_0 = FOURTH_ROUND;
          }

          continue;
        }

        if ((((p == leader(phase, n)) && (round_1_6 == THIRD_ROUND)) && (count(mbox_1_6, THIRD_ROUND, phase) > ((n + 1) / 2))) && (count(mbox_1_6, FOURTH_ROUND) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        if (count(mbox_1_6, FOURTH_ROUND) > 0)
        {
          round_2_0 = FOURTH_ROUND;
          if (mbox_2_0->message->decided)
          {
            estimate = mbox_2_0->message->estimate;
            out(p, estimate);
          }

          phase++;
          round_2_0 = FIRST_ROUND;
          continue;
        }

        continue;
      }

      continue;
    }

  }

}


