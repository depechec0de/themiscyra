struct Msg
{
  int view;
  int vround;
  int opnumber;
  int nround;
  int replica;
  void *log;
};
typedef struct Msg msg;
typedef struct List
{
  msg *message;
  struct List *next;
  int size;
} list;
enum vround_typ
{
  STARTVIEWCHANGE,
  DOVIEWCHANGE,
  STARTVIEW
};
enum nround_typ
{
  PREPARE,
  PREPAREOK,
  COMMIT
};
msg *recv();
int count(list *mbox, int regency, int round, int n);
int size(list *mbox);
void send(int addr, msg *m);
int count_messages(list *mbox, int view, enum vround_typ vround, int phase, enum nround_typ nround);
int main(int p, int n, int f);
int main(int p, int n, int f)
{
  int all = 1000;
  int view;
  int vround;
  msg *m;
  msg *recv_msg;
  list *mbox = NULL;
  view = 0;
  
  while (1)
  {
    vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));

    while(1) {msg * m = recv(); if(timeout()){ break;} }
    if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f))
    {
      vround = DOVIEWCHANGE;

      if (((vround == DOVIEWCHANGE) && (p == primary(view, n))) && (count_messages(mbox, view, DOVIEWCHANGE, NULL, NULL) > f))
      {
        vround = STARTVIEW;
        computes_new_log();
        send(all, message(view, STARTVIEW, NULL, NULL, p, local_log()));
        view = view + 1;
        vround = STARTVIEWCHANGE;

      }

    }

    if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f))
    {
      vround = DOVIEWCHANGE;
      send(primary(view, n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));
      vround = STARTVIEW;

      if (((vround == STARTVIEW) && (p != primary(view, n))) && (count_messages(mbox, view, STARTVIEW, NULL, NULL) == 1))
      {
        computes_new_log();
        view = view + 1;
        vround = AUX_ROUND;
      }

    }

  }

}


