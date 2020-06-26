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
  list *mbox_1_4;
  list *mbox_1_3;
  list *mbox_1_2;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_4;
  list *mbox_0_3;
  list *mbox_0_2;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_1_4;
  enum vround_typ vround_1_3;
  enum vround_typ vround_1_2;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_4;
  enum vround_typ vround_0_3;
  enum vround_typ vround_0_2;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
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
      vround_0_0 = DOVIEWCHANGE;
      mbox_0_0 = havoc(view, vround);
      if (((vround_0_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_0->size > f))
      {
        computes_new_log();
        vround_1_0 = STARTVIEW;
        send(all, message(view, STARTVIEW, NULL, NULL, p, local_log()));
        view++;
        vround_1_0 = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        continue;
      }

      continue;
    }

    if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
    {
      vround_0_1 = DOVIEWCHANGE;
      send(primary(view, n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));
      vround_0_1 = STARTVIEW;
      mbox_0_1 = havoc(view, vround);
      if (((vround_0_1 == STARTVIEW) && (p != primary(view, n))) && (mbox_0_1->size == 1))
      {
        computes_new_log();
        view++;
        vround_1_0 = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        continue;
      }

      continue;
    }

  }

}


