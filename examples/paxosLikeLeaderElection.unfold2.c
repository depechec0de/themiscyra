#include "stdlib.h"
#include "paxosLikeLeaderElection_types.h"

/*@ ensures (\result == \null) ||
    (\result != \null &&
     \valid(\result) &&
     \initialized(&\result->round) &&
     \initialized(&\result->ballot) &&
     (\result->round == 0 ||  \result->round == 1));
 @*/
msg * recv(){
    msg* m = (msg *) malloc(sizeof(msg));
    if (m==NULL) return NULL;

    return m;
}

/*@
  requires \true;
 ensures \result >= 0 && \result <= n;
 @*/
int count(list * mboxA, int ballot, int n);

void send(int addr, msg * m);

/*@ requires p>=0 && n>0 && n<=2000;
@*/
int func(int p, int n);
struct Msg
{
  int round;
  int ballot;
  int leader;
};
typedef struct Msg msg;
typedef struct List
{
  msg *message;
  struct List *next;
  int size;
} list;
enum round_typ
{
  NewBallot,
  AckBallot
};
int func(int p, int n)
{
  int round;
  int ballot;
  int all = 1000;
  int timeout;
  msg *m;
  msg *recv_msg = (msg *) malloc(sizeof(msg));
  list *mboxNewBallot = NULL;
  list *mboxAckBallot = NULL;
  round = NewBallot;
  ballot = 0;
  if (leader(ballot) == p)
  {
    m = (msg *) malloc(sizeof(msg));
    if (m == NULL)
    {
      return 0;
    }

    m->round = NewBallot;
    m->ballot = ballot;
    send(all, m);
  }

  recv_msg = recv();
  if (recv_msg != NULL)
  {
    if (recv_msg->ballot > ballot)
    {
      ballot = recv_msg->ballot;
      round = NewBallot;
    }

    if (((recv_msg->round == NewBallot) && (round == NewBallot)) && (ballot == recv_msg->ballot))
    {
      add_msg(recv_msg, mboxNewBallot);
      round = AckBallot;
      m = (msg *) malloc(sizeof(msg));
      if (m == NULL)
      {
        return 0;
      }

      m->round = AckBallot;
      m->ballot = ballot;
      send(all, m);
      recv_msg = recv();
      if (recv_msg != NULL)
      {
        if (recv_msg->ballot > ballot)
        {
          ballot = recv_msg->ballot;
          round = NewBallot;
        }

        if (((recv_msg->round == NewBallot) && (round == NewBallot)) && (ballot == recv_msg->ballot))
        {
          add_msg(recv_msg, mboxNewBallot);
          round = AckBallot;
          m = (msg *) malloc(sizeof(msg));
          if (m == NULL)
          {
            return 0;
          }

          m->round = AckBallot;
          m->ballot = ballot;
          send(all, m);
          return 0;
        }

        if ((recv_msg->round == AckBallot) && (round == AckBallot))
        {
          add_msg(recv_msg, mboxAckBallot);
          if (count(mboxAckBallot, ballot, n) > (n / 2))
          {
            out(m->leader);
            dispose(mboxNewBallot);
            dispose(mboxAckBallot);
            round = NewBallot;
            ballot++;
            m = (msg *) malloc(sizeof(msg));
            if (m == NULL)
            {
              return 0;
            }

            m->round = NewBallot;
            m->ballot = ballot;
            send(all, m);
          }

          return 0;
        }

      }

      if (entered_timeout())
      {
        dispose(mboxNewBallot);
        dispose(mboxAckBallot);
        reset_timeout();
        ballot++;
        round = NewBallot;
        if (leader(ballot) == p)
        {
          m = (msg *) malloc(sizeof(msg));
          m->round = NewBallot;
          m->ballot = ballot;
          send(all, m);
        }

        return 0;
      }

    }

    if ((recv_msg->round == AckBallot) && (round == AckBallot))
    {
      add_msg(recv_msg, mboxAckBallot);
      if (count(mboxAckBallot, ballot, n) > (n / 2))
      {
        out(m->leader);
        dispose(mboxNewBallot);
        dispose(mboxAckBallot);
        round = NewBallot;
        ballot++;
        m = (msg *) malloc(sizeof(msg));
        if (m == NULL)
        {
          return 0;
        }

        m->round = NewBallot;
        m->ballot = ballot;
        send(all, m);
      }

      recv_msg = recv();
      if (recv_msg != NULL)
      {
        if (recv_msg->ballot > ballot)
        {
          ballot = recv_msg->ballot;
          round = NewBallot;
        }

        if (((recv_msg->round == NewBallot) && (round == NewBallot)) && (ballot == recv_msg->ballot))
        {
          add_msg(recv_msg, mboxNewBallot);
          round = AckBallot;
          m = (msg *) malloc(sizeof(msg));
          if (m == NULL)
          {
            return 0;
          }

          m->round = AckBallot;
          m->ballot = ballot;
          send(all, m);
          return 0;
        }

        if ((recv_msg->round == AckBallot) && (round == AckBallot))
        {
          add_msg(recv_msg, mboxAckBallot);
          if (count(mboxAckBallot, ballot, n) > (n / 2))
          {
            out(m->leader);
            dispose(mboxNewBallot);
            dispose(mboxAckBallot);
            round = NewBallot;
            ballot++;
            m = (msg *) malloc(sizeof(msg));
            if (m == NULL)
            {
              return 0;
            }

            m->round = NewBallot;
            m->ballot = ballot;
            send(all, m);
          }

          return 0;
        }

      }

      if (entered_timeout())
      {
        dispose(mboxNewBallot);
        dispose(mboxAckBallot);
        reset_timeout();
        ballot++;
        round = NewBallot;
        if (leader(ballot) == p)
        {
          m = (msg *) malloc(sizeof(msg));
          m->round = NewBallot;
          m->ballot = ballot;
          send(all, m);
        }

        return 0;
      }

    }

  }

  if (entered_timeout())
  {
    dispose(mboxNewBallot);
    dispose(mboxAckBallot);
    reset_timeout();
    ballot++;
    round = NewBallot;
    if (leader(ballot) == p)
    {
      m = (msg *) malloc(sizeof(msg));
      m->round = NewBallot;
      m->ballot = ballot;
      send(all, m);
    }

    recv_msg = recv();
    if (recv_msg != NULL)
    {
      if (recv_msg->ballot > ballot)
      {
        ballot = recv_msg->ballot;
        round = NewBallot;
      }

      if (((recv_msg->round == NewBallot) && (round == NewBallot)) && (ballot == recv_msg->ballot))
      {
        add_msg(recv_msg, mboxNewBallot);
        round = AckBallot;
        m = (msg *) malloc(sizeof(msg));
        if (m == NULL)
        {
          return 0;
        }

        m->round = AckBallot;
        m->ballot = ballot;
        send(all, m);
        return 0;
      }

      if ((recv_msg->round == AckBallot) && (round == AckBallot))
      {
        add_msg(recv_msg, mboxAckBallot);
        if (count(mboxAckBallot, ballot, n) > (n / 2))
        {
          out(m->leader);
          dispose(mboxNewBallot);
          dispose(mboxAckBallot);
          round = NewBallot;
          ballot++;
          m = (msg *) malloc(sizeof(msg));
          if (m == NULL)
          {
            return 0;
          }

          m->round = NewBallot;
          m->ballot = ballot;
          send(all, m);
        }

        return 0;
      }

    }

    if (entered_timeout())
    {
      dispose(mboxNewBallot);
      dispose(mboxAckBallot);
      reset_timeout();
      ballot++;
      round = NewBallot;
      if (leader(ballot) == p)
      {
        m = (msg *) malloc(sizeof(msg));
        m->round = NewBallot;
        m->ballot = ballot;
        send(all, m);
      }

      return 0;
    }

  }

  return 0;
}


