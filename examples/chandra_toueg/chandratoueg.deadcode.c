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
void out(int v1, int v2);
int in();
msg *max_timestamp(struct List *mbox);
int all_ack(struct List *mbox);
void send(msg *message, int pid);
int leader(int phase, int net_size);
int count(msg *mbox, int phase, enum round_typ round, int from);
int havoc();
int failure_detector(int process);
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
      if ((round_0_0 == SECOND_ROUND) && (failure_detector(leader(phase, n)) == 1))
      {
        round_1_2 = THIRD_ROUND;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, NACK, NULL), leader(phase, n));
        phase++;
        continue;
      }

      if (((round_0_0 == SECOND_ROUND) && (count(mbox_0_0, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0_0, NULL, FOURTH_ROUND, NULL) == 0))
      {
        m = mbox_1_3->message;
        estimate = m->estimate;
        timestamp = phase;
        ack = 1;
        round_1_3 = THIRD_ROUND;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
        if (p != leader(phase, n))
        {
          round_1_3 = FOURTH_ROUND;
        }

        mbox_1_3 = havoc();
        continue;
      }

      if (count(mbox_0_0, NULL, FOURTH_ROUND, NULL) > 0)
      {
        round_1_5 = FOURTH_ROUND;
        m = mbox_1_5->message;
        if (m->decided == 1)
        {
          estimate = m->estimate;
          out(p, estimate);
        }

        phase++;
        continue;
      }

      continue;
    }

    if ((((p == leader(phase, n)) && (round == FIRST_ROUND)) && (count(mbox, phase, FIRST_ROUND, NULL) > ((n + 1) / 2))) && (count(mbox, NULL, FOURTH_ROUND, NULL) == 0))
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
        continue;
      }

      if (((round_0_1 == SECOND_ROUND) && (count(mbox_0_1, phase, SECOND_ROUND, leader(phase, n)) > 0)) && (count(mbox_0_1, NULL, FOURTH_ROUND, NULL) == 0))
      {
        m = mbox_1_3->message;
        estimate = m->estimate;
        timestamp = phase;
        ack = 1;
        round_1_3 = THIRD_ROUND;
        send(message(phase, THIRD_ROUND, estimate, p, timestamp, ACK, NULL), leader(phase, n));
        mbox_1_3 = havoc();
        if ((((p == leader(phase, n)) && (round_1_3 == THIRD_ROUND)) && (count(mbox_1_3, phase, THIRD_ROUND, NULL) > ((n + 1) / 2))) && (count(mbox_1_3, NULL, FOURTH_ROUND, NULL) == 0))
        {
          if (all_ack(mbox_2_0) == 1)
          {
            round_2_0 = FOURTH_ROUND;
            send(message(phase, FOURTH_ROUND, estimate, p, NULL, NULL, true), to_all);
          }

          phase++;
          continue;
        }

        continue;
      }

      continue;
    }

    if (count(mbox, NULL, FOURTH_ROUND, NULL) > 0)
    {
      round_0_5 = FOURTH_ROUND;
      m = mbox_0_5->message;
      if (m->decided == 1)
      {
        estimate = m->estimate;
        out(p, estimate);
      }

      phase++;
      continue;
    }

  }

}


