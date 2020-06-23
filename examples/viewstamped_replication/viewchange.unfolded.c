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
msg *recv();
void send(int addr, msg *m);
int count_messages(list *mbox, int view, enum vround_typ vround);
int main(int p, int n, int f);
int main(int p, int n, int f)
{
  list *mbox_1;
  list *mbox_0;
  enum vround_typ vround_1;
  enum vround_typ vround_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  vround = STARTVIEWCHANGE;
  view = 0;
  send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
  while (1)
  {
    mbox = havoc(view, vround);
    if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
    {
      vround_0 = DOVIEWCHANGE;
      mbox_0 = havoc(view, vround);
      if (((vround_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0->size > f))
      {
        computes_new_log();
        vround_1 = STARTVIEW;
        send(all, message(view, STARTVIEW, NULL, NULL, p, local_log()));
        view++;
        vround_1 = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        continue;
      }

    }

    if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
    {
      vround_0 = DOVIEWCHANGE;
      send(primary(view, n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));
      vround_0 = STARTVIEW;
      mbox_0 = havoc(view, vround);
      if (((vround_0 == STARTVIEW) && (p != primary(view, n))) && (mbox_0->size == 1))
      {
        computes_new_log();
        view++;
        vround_1 = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        continue;
      }

    }

  }

}


