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
_Bool send(int addr, struct msg *m);
struct list *havoc(int view, enum vround_typ vround);
int primary(int view, int n);
struct msg *message(int phase, enum vround_typ round, int p, int timestamp);
struct list *local_log();
struct list *null_log();
int main()
{
  struct list *mbox_2;
  struct list *mbox_1;
  struct list *mbox_0;
  enum vround_typ vround_2;
  enum vround_typ vround_1;
  enum vround_typ vround_0;
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
      vround_0 = DOVIEWCHANGE;
      mbox_0 = havoc(view, vround_0);
      if (((vround_0 == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox_0->size > f))
      {
        vround_1 = DOVIEWCHANGE;
        mbox_1 = havoc(view, vround_1);
        if (((vround_1 == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          continue;
        }

        if (((vround_1 == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
          vround_2 = STARTVIEW;
          continue;
        }

        if (((vround_1 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          computes_new_log();
          vround_2 = STARTVIEW;
          send(all, message(view, STARTVIEW, p, local_log()));
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        if (((vround_1 == STARTVIEW) && (p != primary(view, n))) && (mbox_1->size == 1))
        {
          computes_new_log();
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        continue;
      }

      if (((vround_0 == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox_0->size > f))
      {
        vround_1 = DOVIEWCHANGE;
        send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
        vround_1 = STARTVIEW;
        mbox_1 = havoc(view, vround_1);
        if (((vround_1 == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          continue;
        }

        if (((vround_1 == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
          vround_2 = STARTVIEW;
          continue;
        }

        if (((vround_1 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          computes_new_log();
          vround_2 = STARTVIEW;
          send(all, message(view, STARTVIEW, p, local_log()));
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        if (((vround_1 == STARTVIEW) && (p != primary(view, n))) && (mbox_1->size == 1))
        {
          computes_new_log();
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        continue;
      }

      if (((vround_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0->size > f))
      {
        computes_new_log();
        vround_1 = STARTVIEW;
        send(all, message(view, STARTVIEW, p, local_log()));
        view++;
        vround_1 = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, p, null_log()));
        mbox_1 = havoc(view, vround_1);
        if (((vround_1 == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          continue;
        }

        if (((vround_1 == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
          vround_2 = STARTVIEW;
          continue;
        }

        if (((vround_1 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          computes_new_log();
          vround_2 = STARTVIEW;
          send(all, message(view, STARTVIEW, p, local_log()));
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        if (((vround_1 == STARTVIEW) && (p != primary(view, n))) && (mbox_1->size == 1))
        {
          computes_new_log();
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        continue;
      }

      if (((vround_0 == STARTVIEW) && (p != primary(view, n))) && (mbox_0->size == 1))
      {
        computes_new_log();
        view++;
        vround_1 = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, p, null_log()));
        mbox_1 = havoc(view, vround_1);
        if (((vround_1 == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          continue;
        }

        if (((vround_1 == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
          vround_2 = STARTVIEW;
          continue;
        }

        if (((vround_1 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          computes_new_log();
          vround_2 = STARTVIEW;
          send(all, message(view, STARTVIEW, p, local_log()));
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        if (((vround_1 == STARTVIEW) && (p != primary(view, n))) && (mbox_1->size == 1))
        {
          computes_new_log();
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        continue;
      }

      continue;
    }

    if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
    {
      vround_0 = DOVIEWCHANGE;
      send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
      vround_0 = STARTVIEW;
      mbox_0 = havoc(view, vround_0);
      if (((vround_0 == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox_0->size > f))
      {
        vround_1 = DOVIEWCHANGE;
        mbox_1 = havoc(view, vround_1);
        if (((vround_1 == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          continue;
        }

        if (((vround_1 == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
          vround_2 = STARTVIEW;
          continue;
        }

        if (((vround_1 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          computes_new_log();
          vround_2 = STARTVIEW;
          send(all, message(view, STARTVIEW, p, local_log()));
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        if (((vround_1 == STARTVIEW) && (p != primary(view, n))) && (mbox_1->size == 1))
        {
          computes_new_log();
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        continue;
      }

      if (((vround_0 == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox_0->size > f))
      {
        vround_1 = DOVIEWCHANGE;
        send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
        vround_1 = STARTVIEW;
        mbox_1 = havoc(view, vround_1);
        if (((vround_1 == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          continue;
        }

        if (((vround_1 == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
          vround_2 = STARTVIEW;
          continue;
        }

        if (((vround_1 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          computes_new_log();
          vround_2 = STARTVIEW;
          send(all, message(view, STARTVIEW, p, local_log()));
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        if (((vround_1 == STARTVIEW) && (p != primary(view, n))) && (mbox_1->size == 1))
        {
          computes_new_log();
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        continue;
      }

      if (((vround_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0->size > f))
      {
        computes_new_log();
        vround_1 = STARTVIEW;
        send(all, message(view, STARTVIEW, p, local_log()));
        view++;
        vround_1 = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, p, null_log()));
        mbox_1 = havoc(view, vround_1);
        if (((vround_1 == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          continue;
        }

        if (((vround_1 == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
          vround_2 = STARTVIEW;
          continue;
        }

        if (((vround_1 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          computes_new_log();
          vround_2 = STARTVIEW;
          send(all, message(view, STARTVIEW, p, local_log()));
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        if (((vround_1 == STARTVIEW) && (p != primary(view, n))) && (mbox_1->size == 1))
        {
          computes_new_log();
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        continue;
      }

      if (((vround_0 == STARTVIEW) && (p != primary(view, n))) && (mbox_0->size == 1))
      {
        computes_new_log();
        view++;
        vround_1 = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, p, null_log()));
        mbox_1 = havoc(view, vround_1);
        if (((vround_1 == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          continue;
        }

        if (((vround_1 == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
          vround_2 = STARTVIEW;
          continue;
        }

        if (((vround_1 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          computes_new_log();
          vround_2 = STARTVIEW;
          send(all, message(view, STARTVIEW, p, local_log()));
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        if (((vround_1 == STARTVIEW) && (p != primary(view, n))) && (mbox_1->size == 1))
        {
          computes_new_log();
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        continue;
      }

      continue;
    }

    if (((vround == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
    {
      computes_new_log();
      vround_0 = STARTVIEW;
      send(all, message(view, STARTVIEW, p, local_log()));
      view++;
      vround_0 = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, p, null_log()));
      mbox_0 = havoc(view, vround_0);
      if (((vround_0 == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox_0->size > f))
      {
        vround_1 = DOVIEWCHANGE;
        mbox_1 = havoc(view, vround_1);
        if (((vround_1 == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          continue;
        }

        if (((vround_1 == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
          vround_2 = STARTVIEW;
          continue;
        }

        if (((vround_1 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          computes_new_log();
          vround_2 = STARTVIEW;
          send(all, message(view, STARTVIEW, p, local_log()));
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        if (((vround_1 == STARTVIEW) && (p != primary(view, n))) && (mbox_1->size == 1))
        {
          computes_new_log();
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        continue;
      }

      if (((vround_0 == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox_0->size > f))
      {
        vround_1 = DOVIEWCHANGE;
        send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
        vround_1 = STARTVIEW;
        mbox_1 = havoc(view, vround_1);
        if (((vround_1 == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          continue;
        }

        if (((vround_1 == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
          vround_2 = STARTVIEW;
          continue;
        }

        if (((vround_1 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          computes_new_log();
          vround_2 = STARTVIEW;
          send(all, message(view, STARTVIEW, p, local_log()));
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        if (((vround_1 == STARTVIEW) && (p != primary(view, n))) && (mbox_1->size == 1))
        {
          computes_new_log();
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        continue;
      }

      if (((vround_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0->size > f))
      {
        computes_new_log();
        vround_1 = STARTVIEW;
        send(all, message(view, STARTVIEW, p, local_log()));
        view++;
        vround_1 = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, p, null_log()));
        mbox_1 = havoc(view, vround_1);
        if (((vround_1 == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          continue;
        }

        if (((vround_1 == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
          vround_2 = STARTVIEW;
          continue;
        }

        if (((vround_1 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          computes_new_log();
          vround_2 = STARTVIEW;
          send(all, message(view, STARTVIEW, p, local_log()));
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        if (((vround_1 == STARTVIEW) && (p != primary(view, n))) && (mbox_1->size == 1))
        {
          computes_new_log();
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        continue;
      }

      if (((vround_0 == STARTVIEW) && (p != primary(view, n))) && (mbox_0->size == 1))
      {
        computes_new_log();
        view++;
        vround_1 = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, p, null_log()));
        mbox_1 = havoc(view, vround_1);
        if (((vround_1 == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          continue;
        }

        if (((vround_1 == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
          vround_2 = STARTVIEW;
          continue;
        }

        if (((vround_1 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          computes_new_log();
          vround_2 = STARTVIEW;
          send(all, message(view, STARTVIEW, p, local_log()));
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        if (((vround_1 == STARTVIEW) && (p != primary(view, n))) && (mbox_1->size == 1))
        {
          computes_new_log();
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        continue;
      }

      continue;
    }

    if (((vround == STARTVIEW) && (p != primary(view, n))) && (mbox->size == 1))
    {
      computes_new_log();
      view++;
      vround_0 = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, p, null_log()));
      mbox_0 = havoc(view, vround_0);
      if (((vround_0 == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox_0->size > f))
      {
        vround_1 = DOVIEWCHANGE;
        mbox_1 = havoc(view, vround_1);
        if (((vround_1 == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          continue;
        }

        if (((vround_1 == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
          vround_2 = STARTVIEW;
          continue;
        }

        if (((vround_1 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          computes_new_log();
          vround_2 = STARTVIEW;
          send(all, message(view, STARTVIEW, p, local_log()));
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        if (((vround_1 == STARTVIEW) && (p != primary(view, n))) && (mbox_1->size == 1))
        {
          computes_new_log();
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        continue;
      }

      if (((vround_0 == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox_0->size > f))
      {
        vround_1 = DOVIEWCHANGE;
        send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
        vround_1 = STARTVIEW;
        mbox_1 = havoc(view, vround_1);
        if (((vround_1 == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          continue;
        }

        if (((vround_1 == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
          vround_2 = STARTVIEW;
          continue;
        }

        if (((vround_1 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          computes_new_log();
          vround_2 = STARTVIEW;
          send(all, message(view, STARTVIEW, p, local_log()));
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        if (((vround_1 == STARTVIEW) && (p != primary(view, n))) && (mbox_1->size == 1))
        {
          computes_new_log();
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        continue;
      }

      if (((vround_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0->size > f))
      {
        computes_new_log();
        vround_1 = STARTVIEW;
        send(all, message(view, STARTVIEW, p, local_log()));
        view++;
        vround_1 = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, p, null_log()));
        mbox_1 = havoc(view, vround_1);
        if (((vround_1 == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          continue;
        }

        if (((vround_1 == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
          vround_2 = STARTVIEW;
          continue;
        }

        if (((vround_1 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          computes_new_log();
          vround_2 = STARTVIEW;
          send(all, message(view, STARTVIEW, p, local_log()));
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        if (((vround_1 == STARTVIEW) && (p != primary(view, n))) && (mbox_1->size == 1))
        {
          computes_new_log();
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        continue;
      }

      if (((vround_0 == STARTVIEW) && (p != primary(view, n))) && (mbox_0->size == 1))
      {
        computes_new_log();
        view++;
        vround_1 = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, p, null_log()));
        mbox_1 = havoc(view, vround_1);
        if (((vround_1 == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          continue;
        }

        if (((vround_1 == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox_1->size > f))
        {
          vround_2 = DOVIEWCHANGE;
          send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
          vround_2 = STARTVIEW;
          continue;
        }

        if (((vround_1 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_1->size > f))
        {
          computes_new_log();
          vround_2 = STARTVIEW;
          send(all, message(view, STARTVIEW, p, local_log()));
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        if (((vround_1 == STARTVIEW) && (p != primary(view, n))) && (mbox_1->size == 1))
        {
          computes_new_log();
          view++;
          vround_2 = STARTVIEWCHANGE;
          send(all, message(view, STARTVIEWCHANGE, p, null_log()));
          continue;
        }

        continue;
      }

      continue;
    }

  }

}


