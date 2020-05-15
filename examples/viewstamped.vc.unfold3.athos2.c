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
void send(int addr, msg *m);
int count_messages(list *mbox, int view, enum vround_typ vround, int phase, enum nround_typ nround);
int main(int p, int n, int f);
int main(int p, int n, int f)
{
  int all = 1000;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox = NULL;
  view = 0;
  
  while (1)
  {
    vround = STARTVIEWCHANGE;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    
    if(p == primary(view, n)){
      
      if ((vround == STARTVIEWCHANGE) && (count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f))
      {
        vround = DOVIEWCHANGE;

        if (((vround == DOVIEWCHANGE)) && (count_messages(mbox, view, DOVIEWCHANGE, NULL, NULL) > f))
        {
          computes_new_log();
          vround = STARTVIEW;
          send(all, message(view, STARTVIEW, NULL, NULL, p, local_log()));
          view = view + 1;
          vround = STARTVIEWCHANGE;

        }

      }

    }else{

      if (((vround == STARTVIEWCHANGE)) && (count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f))
      {
        vround = DOVIEWCHANGE;
        send(primary(view, n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));
        vround = STARTVIEW;

        if (((vround == STARTVIEW)) && (count_messages(mbox, view, STARTVIEW, NULL, NULL) == 1))
        {
          computes_new_log();
          view = view + 1;
          vround = STARTVIEWCHANGE;
        }

      }

    }

  }

}


