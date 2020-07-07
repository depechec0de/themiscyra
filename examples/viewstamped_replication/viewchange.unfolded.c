struct msg
{
  int view;
  enum vround_typ vround;
  int replica;
  struct list *log;
};
struct list
{
  struct msg *message;
  struct list *next;
  int size;
};
enum vround_typ
{
  STARTVIEWCHANGE,
  DOVIEWCHANGE,
  STARTVIEW
};
enum null
{
  BOOL_NULL,
  INT_NULL
};
_Bool send(int addr, struct msg *m);
struct list *havoc(int view, enum vround_typ vround);
int primary(int view, int n);
struct msg *message(int phase, enum vround_typ round, int p, int timestamp);
struct list *local_log();
struct list *null_log();
int main()
{
  struct list *mbox_1_4;
  struct list *mbox_1_3;
  struct list *mbox_1_2;
  struct list *mbox_1_1;
  struct list *mbox_1_0;
  struct list *mbox_0_4;
  struct list *mbox_0_3;
  struct list *mbox_0_2;
  struct list *mbox_0_1;
  struct list *mbox_0_0;
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
  int p;
  int f;
  int n;
  int all;
  int view;
  enum vround_typ vround;
  struct msg *m;
  struct msg *recv_msg;
  struct list *mbox;
  vround = STARTVIEWCHANGE;
  view = 0;
  send(all, message(view, STARTVIEWCHANGE, p, null_log()));
  while (1)
  {
    mbox = havoc(view, vround);
    if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
    {
      vround_0_0 = DOVIEWCHANGE;
      mbox_0_0 = havoc(view, vround);
      if (((vround_0_0 == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_0->size > f))
      {
        vround_1_0 = DOVIEWCHANGE;
        continue;
      }

      if (((vround_0_0 == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox_0_0->size > f))
      {
        vround_1_0 = DOVIEWCHANGE;
        send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
        vround_1_0 = STARTVIEW;
        continue;
      }

      if (((vround_0_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_0->size > f))
      {
        computes_new_log();
        vround_1_0 = STARTVIEW;
        send(all, message(view, STARTVIEW, p, local_log()));
        view++;
        vround_1_0 = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, p, null_log()));
        continue;
      }

      if (((vround_0_0 == STARTVIEW) && (p != primary(view, n))) && (mbox_0_0->size == 1))
      {
        computes_new_log();
        view++;
        vround_1_0 = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, p, null_log()));
        continue;
      }

      continue;
    }

    if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
    {
      vround_0_1 = DOVIEWCHANGE;
      send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
      vround_0_1 = STARTVIEW;
      mbox_0_1 = havoc(view, vround);
      if (((vround_0_1 == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_1->size > f))
      {
        vround_1_0 = DOVIEWCHANGE;
        continue;
      }

      if (((vround_0_1 == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox_0_1->size > f))
      {
        vround_1_0 = DOVIEWCHANGE;
        send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
        vround_1_0 = STARTVIEW;
        continue;
      }

      if (((vround_0_1 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_1->size > f))
      {
        computes_new_log();
        vround_1_0 = STARTVIEW;
        send(all, message(view, STARTVIEW, p, local_log()));
        view++;
        vround_1_0 = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, p, null_log()));
        continue;
      }

      if (((vround_0_1 == STARTVIEW) && (p != primary(view, n))) && (mbox_0_1->size == 1))
      {
        computes_new_log();
        view++;
        vround_1_0 = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, p, null_log()));
        continue;
      }

      continue;
    }

    if (((vround == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
    {
      computes_new_log();
      vround_0_2 = STARTVIEW;
      send(all, message(view, STARTVIEW, p, local_log()));
      view++;
      vround_0_2 = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, p, null_log()));
      mbox_0_2 = havoc(view, vround);
      if (((vround_0_2 == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_2->size > f))
      {
        vround_1_0 = DOVIEWCHANGE;
        continue;
      }

      if (((vround_0_2 == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox_0_2->size > f))
      {
        vround_1_0 = DOVIEWCHANGE;
        send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
        vround_1_0 = STARTVIEW;
        continue;
      }

      if (((vround_0_2 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_2->size > f))
      {
        computes_new_log();
        vround_1_0 = STARTVIEW;
        send(all, message(view, STARTVIEW, p, local_log()));
        view++;
        vround_1_0 = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, p, null_log()));
        continue;
      }

      if (((vround_0_2 == STARTVIEW) && (p != primary(view, n))) && (mbox_0_2->size == 1))
      {
        computes_new_log();
        view++;
        vround_1_0 = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, p, null_log()));
        continue;
      }

      continue;
    }

    if (((vround == STARTVIEW) && (p != primary(view, n))) && (mbox->size == 1))
    {
      computes_new_log();
      view++;
      vround_0_3 = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, p, null_log()));
      mbox_0_3 = havoc(view, vround);
      if (((vround_0_3 == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_3->size > f))
      {
        vround_1_0 = DOVIEWCHANGE;
        continue;
      }

      if (((vround_0_3 == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox_0_3->size > f))
      {
        vround_1_0 = DOVIEWCHANGE;
        send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
        vround_1_0 = STARTVIEW;
        continue;
      }

      if (((vround_0_3 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_3->size > f))
      {
        computes_new_log();
        vround_1_0 = STARTVIEW;
        send(all, message(view, STARTVIEW, p, local_log()));
        view++;
        vround_1_0 = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, p, null_log()));
        continue;
      }

      if (((vround_0_3 == STARTVIEW) && (p != primary(view, n))) && (mbox_0_3->size == 1))
      {
        computes_new_log();
        view++;
        vround_1_0 = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, p, null_log()));
        continue;
      }

      continue;
    }

  }

}


