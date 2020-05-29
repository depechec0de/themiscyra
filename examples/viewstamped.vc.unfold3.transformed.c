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

  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;

  while (1)
  {
  
    if(start_flag){
      view = 0;
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      start_flag = false;
    }
    if(primary_restart_flag){
      view = view + 1;
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    }
    if(follower_restart_flag){
      view = view + 1;
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    }
    
    mbox = havoc(view, vround);
    if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
    {
      vround = DOVIEWCHANGE;
      mbox = havoc(view, vround);
      if (((vround == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
      {
        computes_new_log();
        vround = STARTVIEW;
        send(all, message(view, STARTVIEW, NULL, NULL, p, local_log()));
        primary_restart_flag = true;
        follower_restart_flag = false;

        continue;
      }

    }

    if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
    {
      vround = DOVIEWCHANGE;
      send(primary(view, n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));
      vround = STARTVIEW;
      mbox = havoc(view, vround);
      if (((vround == STARTVIEW) && (p != primary(view, n))) && (mbox->size == 1))
      {
        computes_new_log();

        primary_restart_flag = false;
        follower_restart_flag = true;

        continue;
      }

    }

  }

}


