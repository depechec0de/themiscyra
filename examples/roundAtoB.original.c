typedef struct Msg
{
  int round;
  int ballot;
} msg;

typedef struct List
{
  msg *message;
  struct List *next;
  int size;
} list;

int round;
int ballot;
int n;
int all;
int timeout;

msg* m;
msg* recv_msg;
msg* mboxA;
msg* mboxB;

int main()
{
  round = 0;
  ballot = 0;
  m = (msg *) malloc(sizeof(msg));
  m->round = 0;
  m->ballot = ballot;
  send(all, m);

  while(1)
  {
    recv_msg = recv();
    if (not_null(recv_msg) && (recv_msg->round == 0))
    {
      add_msg(mboxA, recv_msg->ballot, recv_msg);
      if ((round == 0) && (countA(mboxA, ballot) > ((2 * n) / 3)))
      {
        computation(mboxA);
        dispose(mboxA);
        round = 1;
        m = (msg *) malloc(sizeof(msg));
        m->round = 1;
        m->ballot = ballot;
        send(all, m);
      }
      continue;
      
    }

    if (not_null(recv_msg) && (recv_msg->round == 1))
    {
      add_msg(mboxB, recv_msg->ballot, recv_msg);
      if ((round == 1) && (countB(mboxB, ballot) > ((2 * n) / 3)))
      {
        computation(mboxB);
        dispose(mboxB);
        ballot++;
        round = 0;
        m = (msg *) malloc(sizeof(msg));
        m->round = 0;
        m->ballot = ballot;
        send(all, m);
      }
      continue;
    }

    if (timeout)
    {
      dispose(mboxA);
      dispose(mboxB);
      reset_timeout();
      ballot++;
      round = 0;
      m = (msg *) malloc(sizeof(msg));
      m->round = 0;
      m->ballot = ballot;
      send(all, m);
      continue;
    }

  }

}

