STARTVIEWCHANGE
################Path######################
{
  int main(int p, int n, int f)
{
  list *mbox_1_3;
  list *mbox_1_2;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_3;
  list *mbox_0_2;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_1_3;
  enum vround_typ vround_1_2;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
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
  mbox = havoc(view, vround);
  if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
  {
    vround_0_0 = DOVIEWCHANGE;
  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_1_3;
  list *mbox_1_2;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_3;
  list *mbox_0_2;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_1_3;
  enum vround_typ vround_1_2;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
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
  mbox = havoc(view, vround);
  if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
  {
    if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
    {
      vround_0_1 = DOVIEWCHANGE;
    }

  }

}


}

##########################################
DOVIEWCHANGE
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_1_3;
  list *mbox_1_2;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_3;
  list *mbox_0_2;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_1_3;
  enum vround_typ vround_1_2;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
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
  mbox = havoc(view, vround);
  if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
  {
    vround_0_0 = DOVIEWCHANGE;
    mbox_0_0 = havoc(view, vround);
    if (((vround_0_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_0->size > f))
    {
      computes_new_log();
      vround_1_0 = STARTVIEW;
    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_1_3;
  list *mbox_1_2;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_3;
  list *mbox_0_2;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_1_3;
  enum vround_typ vround_1_2;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
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
  mbox = havoc(view, vround);
  if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
  {
    if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
    {
      vround_0_1 = DOVIEWCHANGE;
      send(primary(view, n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));
      vround_0_1 = STARTVIEW;
    }

  }

}


}

##########################################
STARTVIEW
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_1_3;
  list *mbox_1_2;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_3;
  list *mbox_0_2;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_1_3;
  enum vround_typ vround_1_2;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
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
    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_1_3;
  list *mbox_1_2;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_3;
  list *mbox_0_2;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_1_3;
  enum vround_typ vround_1_2;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
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
  mbox = havoc(view, vround);
  if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
  {
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
      }

    }

  }

}


}

##########################################
