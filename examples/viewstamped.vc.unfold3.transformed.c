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
  STARTVIEW,
  AUX_ROUND
};

msg *recv();
void send(int addr, msg *m);
int count_messages(list *mbox, int view, enum vround_typ vround);
int main(int p, int n, int f);
int main(int p, int n, int f)
{
  int all = 1000;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox = NULL;
  
  vround = STARTVIEWCHANGE;
  view = 0;
  send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
  while (1)
  {
    
    if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (count_messages(mbox, view, STARTVIEWCHANGE) > f))
    {
      vround = DOVIEWCHANGE;

      if (((vround == DOVIEWCHANGE) && (p == primary(view, n))) && (count_messages(mbox, view, DOVIEWCHANGE) > f))
      {
        computes_new_log();
        vround = STARTVIEW;
        send(all, message(view, STARTVIEW, NULL, NULL, p, local_log()));
        view = view + 1;
        vround = STARTVIEWCHANGE;
        // b_1
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      }

    }

    if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (count_messages(mbox, view, STARTVIEWCHANGE) > f))
    {
      vround = DOVIEWCHANGE;
      send(primary(view, n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));
      vround = STARTVIEW;

      if (((vround == STARTVIEW) && (p != primary(view, n))) && (count_messages(mbox, view, STARTVIEW) == 1))
      {
        computes_new_log();
        view = view + 1;
        vround = STARTVIEWCHANGE;
        // b_2
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      }

    }

  }

}


