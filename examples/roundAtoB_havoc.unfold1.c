#include "stdlib.h"
#include "roundAtoB_havoc_types.h"

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
int count(list * mboxA, int ballot, int round, int n);

void send(int addr, msg * m);

/*@ requires p>=0 && n>0 && n<=2000;
@*/
int func(int p, int n);
struct Msg
{
  int round;
  int ballot;
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
  A,
  B
};
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
  list *mbox = NULL;
  round = A;
  ballot = 0;
  m = (msg *) malloc(sizeof(msg));
  if (m == NULL)
    return 0;

  m->round = A;
  m->ballot = ballot;
  mbox = NULL;
  send(all, m);

  mbox = havoc(ballot, round);
  
  if ((round == A) && (count(mbox, ballot, round, n) > ((2 * n) / 3)))
  {
    computation(mbox);
    dispose(mbox, ballot, round);
    round = B;
    m = (msg *) malloc(sizeof(msg));
    if (m == NULL)
      return 0;

    m->round = B;
    m->ballot = ballot;
    send(all, m);
    return 0;
  }

  if ((round == B) && (count(mbox, ballot, round, n) > ((2 * n) / 3)))
  {
    computation(mbox);
    dispose(mbox, ballot, round);
    round = A;
    ballot++;
    m = (msg *) malloc(sizeof(msg));
    if (m == NULL)
      return 0;

    m->round = A;
    m->ballot = ballot;
    send(all, m);
    return 0;
  }

  return 0;
}


