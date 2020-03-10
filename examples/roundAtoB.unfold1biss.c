#include "stdlib.h"
#include "roundAtoB_types.h"

/*@ ensures (\result == \null) ||
    (\result != \null &&
    \valid(\result) &&
    \initialized(&\result->round) &&
    \initialized(&\result->ballot) &&
    (\result->round == 0 ||  \result->round == 1));
@*/
msg * recv(int v, int t){
    msg* m = (msg *) malloc(sizeof(msg));
    if (m==NULL) return NULL;
    m->round = v%2;
    m->ballot = t;
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

int func(int p, int n)
{
  int round;
  int ballot;
  int v = p;
  int t = p;
  int all = 1000;
  int timeout;
  msg *m;
  msg *recv_msg;
  list *mboxA = NULL;
  list *mboxB = NULL;
  round = 0;
  ballot = 0;
  m = (msg *) malloc(sizeof(msg));
  if (m == NULL)
    return 0;

  m->round = 0;
  m->ballot = ballot;
  mboxA = NULL;
  send(all, m);
  recv_msg = (msg *) malloc(sizeof(msg));
  if (round == 0)
  {
    if (count(mboxA, ballot, n) > ((2 * n) / 3))
    {
      round = 1;
      m = (msg *) malloc(sizeof(msg));
      if (m == NULL)
        return 0;

      m->round = 1;
      m->ballot = ballot;
      send(all, m);
      return 0;
    }

    return 0;
  }

  if (round == 1)
  {
    if (count(mboxB, ballot, n) > ((2 * n) / 3))
    {
      round = 0;
      ballot++;
      m = (msg *) malloc(sizeof(msg));
      if (m == NULL)
        return 0;

      m->round = 0;
      m->ballot = ballot;
      send(all, m);
      return 0;
    }

    return 0;
  }

  recv_msg = (msg *) malloc(sizeof(msg));
  if (round == 0)
  {
    if (count(mboxA, ballot, n) > ((2 * n) / 3))
    {
      round = 1;
      m = (msg *) malloc(sizeof(msg));
      if (m == NULL)
        return 0;

      m->round = 1;
      m->ballot = ballot;
      send(all, m);
      return 0;
    }

    return 0;
  }

  if (round == 1)
  {
    if (count(mboxB, ballot, n) > ((2 * n) / 3))
    {
      round = 0;
      ballot++;
      m = (msg *) malloc(sizeof(msg));
      if (m == NULL)
        return 0;

      m->round = 0;
      m->ballot = ballot;
      send(all, m);
      return 0;
    }

    return 0;
  }

  return 0;
  return 0;
}


