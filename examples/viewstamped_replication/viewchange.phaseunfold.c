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
  int p;
  int f;
  int n;
  int all;
  int view;
  enum vround_typ vround;
  struct msg *m;
  struct msg *recv_msg;
  struct list *mbox;
  view = 0;
  vround = STARTVIEWCHANGE;
  send(all, message(view, STARTVIEWCHANGE, p, null_log()));
  while (1)
  {
    mbox = havoc(view, vround);
    if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
    {
      vround = DOVIEWCHANGE;
      mbox = havoc(view, vround);
      if (((vround == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
      {
        computes_new_log();
        vround = STARTVIEW;
        send(all, message(view, STARTVIEW, p, local_log()));
        view++;
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, p, null_log()));
        continue;
      }

      break;
    }

    if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
    {
      vround = DOVIEWCHANGE;
      send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
      vround = STARTVIEW;
      mbox = havoc(view, vround);
      if (((vround == STARTVIEW) && (p != primary(view, n))) && (mbox->size == 1))
      {
        computes_new_log();
        view++;
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, p, null_log()));
        continue;
      }

      break;
    }

  }

}


