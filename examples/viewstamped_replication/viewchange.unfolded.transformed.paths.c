STARTVIEWCHANGE
################Path######################
{
  int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (start_flag)
  {
    view = 0;
    vround = STARTVIEWCHANGE;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    start_flag = false;
    if (!primary_restart_flag)
    {
      if (!follower_restart_flag)
      {
        mbox = havoc(view, vround);
        if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
        {
          vround_0_0 = DOVIEWCHANGE;
        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (start_flag)
  {
    view = 0;
    vround = STARTVIEWCHANGE;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    start_flag = false;
    if (!primary_restart_flag)
    {
      if (!follower_restart_flag)
      {
        mbox = havoc(view, vround);
        if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
        {
          if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
          {
            vround_1_0 = DOVIEWCHANGE;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (start_flag)
  {
    view = 0;
    vround = STARTVIEWCHANGE;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    start_flag = false;
    if (primary_restart_flag)
    {
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      if (!follower_restart_flag)
      {
        mbox = havoc(view, vround);
        if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
        {
          vround_0_0 = DOVIEWCHANGE;
        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (!start_flag)
  {
    if (primary_restart_flag)
    {
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      if (!follower_restart_flag)
      {
        mbox = havoc(view, vround);
        if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
        {
          vround_0_0 = DOVIEWCHANGE;
        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (start_flag)
  {
    view = 0;
    vround = STARTVIEWCHANGE;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    start_flag = false;
    if (primary_restart_flag)
    {
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      if (!follower_restart_flag)
      {
        mbox = havoc(view, vround);
        if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
        {
          if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
          {
            vround_1_0 = DOVIEWCHANGE;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (!start_flag)
  {
    if (primary_restart_flag)
    {
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      if (!follower_restart_flag)
      {
        mbox = havoc(view, vround);
        if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
        {
          if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
          {
            vround_1_0 = DOVIEWCHANGE;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (start_flag)
  {
    view = 0;
    vround = STARTVIEWCHANGE;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    start_flag = false;
    if (primary_restart_flag)
    {
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      if (follower_restart_flag)
      {
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        mbox = havoc(view, vround);
        if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
        {
          vround_0_0 = DOVIEWCHANGE;
        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (start_flag)
  {
    view = 0;
    vround = STARTVIEWCHANGE;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    start_flag = false;
    if (!primary_restart_flag)
    {
      if (follower_restart_flag)
      {
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        mbox = havoc(view, vround);
        if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
        {
          vround_0_0 = DOVIEWCHANGE;
        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (!start_flag)
  {
    if (primary_restart_flag)
    {
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      if (follower_restart_flag)
      {
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        mbox = havoc(view, vround);
        if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
        {
          vround_0_0 = DOVIEWCHANGE;
        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (!start_flag)
  {
    if (!primary_restart_flag)
    {
      if (follower_restart_flag)
      {
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        mbox = havoc(view, vround);
        if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
        {
          vround_0_0 = DOVIEWCHANGE;
        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (start_flag)
  {
    view = 0;
    vround = STARTVIEWCHANGE;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    start_flag = false;
    if (primary_restart_flag)
    {
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      if (follower_restart_flag)
      {
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        mbox = havoc(view, vround);
        if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
        {
          if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
          {
            vround_1_0 = DOVIEWCHANGE;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (start_flag)
  {
    view = 0;
    vround = STARTVIEWCHANGE;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    start_flag = false;
    if (!primary_restart_flag)
    {
      if (follower_restart_flag)
      {
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        mbox = havoc(view, vround);
        if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
        {
          if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
          {
            vround_1_0 = DOVIEWCHANGE;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (!start_flag)
  {
    if (primary_restart_flag)
    {
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      if (follower_restart_flag)
      {
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        mbox = havoc(view, vround);
        if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
        {
          if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
          {
            vround_1_0 = DOVIEWCHANGE;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (!start_flag)
  {
    if (!primary_restart_flag)
    {
      if (follower_restart_flag)
      {
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        mbox = havoc(view, vround);
        if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
        {
          if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
          {
            vround_1_0 = DOVIEWCHANGE;
          }

        }

      }

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
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (start_flag)
  {
    view = 0;
    vround = STARTVIEWCHANGE;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    start_flag = false;
    if (primary_restart_flag)
    {
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      if (follower_restart_flag)
      {
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        mbox = havoc(view, vround);
        if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
        {
          vround_0_0 = DOVIEWCHANGE;
          mbox_0_0 = havoc(view, vround);
          if (((vround_0_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_0->size > f))
          {
            computes_new_log();
            vround_0_1 = STARTVIEW;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (start_flag)
  {
    view = 0;
    vround = STARTVIEWCHANGE;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    start_flag = false;
    if (primary_restart_flag)
    {
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      if (!follower_restart_flag)
      {
        mbox = havoc(view, vround);
        if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
        {
          vround_0_0 = DOVIEWCHANGE;
          mbox_0_0 = havoc(view, vround);
          if (((vround_0_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_0->size > f))
          {
            computes_new_log();
            vround_0_1 = STARTVIEW;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (start_flag)
  {
    view = 0;
    vround = STARTVIEWCHANGE;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    start_flag = false;
    if (!primary_restart_flag)
    {
      if (follower_restart_flag)
      {
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        mbox = havoc(view, vround);
        if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
        {
          vround_0_0 = DOVIEWCHANGE;
          mbox_0_0 = havoc(view, vround);
          if (((vround_0_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_0->size > f))
          {
            computes_new_log();
            vround_0_1 = STARTVIEW;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (start_flag)
  {
    view = 0;
    vround = STARTVIEWCHANGE;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    start_flag = false;
    if (!primary_restart_flag)
    {
      if (!follower_restart_flag)
      {
        mbox = havoc(view, vround);
        if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
        {
          vround_0_0 = DOVIEWCHANGE;
          mbox_0_0 = havoc(view, vround);
          if (((vround_0_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_0->size > f))
          {
            computes_new_log();
            vround_0_1 = STARTVIEW;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (!start_flag)
  {
    if (primary_restart_flag)
    {
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      if (follower_restart_flag)
      {
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        mbox = havoc(view, vround);
        if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
        {
          vround_0_0 = DOVIEWCHANGE;
          mbox_0_0 = havoc(view, vround);
          if (((vround_0_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_0->size > f))
          {
            computes_new_log();
            vround_0_1 = STARTVIEW;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (!start_flag)
  {
    if (primary_restart_flag)
    {
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      if (!follower_restart_flag)
      {
        mbox = havoc(view, vround);
        if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
        {
          vround_0_0 = DOVIEWCHANGE;
          mbox_0_0 = havoc(view, vround);
          if (((vround_0_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_0->size > f))
          {
            computes_new_log();
            vround_0_1 = STARTVIEW;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (!start_flag)
  {
    if (!primary_restart_flag)
    {
      if (follower_restart_flag)
      {
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        mbox = havoc(view, vround);
        if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
        {
          vround_0_0 = DOVIEWCHANGE;
          mbox_0_0 = havoc(view, vround);
          if (((vround_0_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_0->size > f))
          {
            computes_new_log();
            vround_0_1 = STARTVIEW;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (!start_flag)
  {
    if (!primary_restart_flag)
    {
      if (!follower_restart_flag)
      {
        mbox = havoc(view, vround);
        if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
        {
          vround_0_0 = DOVIEWCHANGE;
          mbox_0_0 = havoc(view, vround);
          if (((vround_0_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_0->size > f))
          {
            computes_new_log();
            vround_0_1 = STARTVIEW;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (start_flag)
  {
    view = 0;
    vround = STARTVIEWCHANGE;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    start_flag = false;
    if (primary_restart_flag)
    {
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      if (follower_restart_flag)
      {
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        mbox = havoc(view, vround);
        if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
        {
          if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
          {
            vround_1_0 = DOVIEWCHANGE;
            send(primary(view, n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));
            vround_1_0 = STARTVIEW;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (start_flag)
  {
    view = 0;
    vround = STARTVIEWCHANGE;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    start_flag = false;
    if (primary_restart_flag)
    {
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      if (!follower_restart_flag)
      {
        mbox = havoc(view, vround);
        if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
        {
          if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
          {
            vround_1_0 = DOVIEWCHANGE;
            send(primary(view, n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));
            vround_1_0 = STARTVIEW;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (start_flag)
  {
    view = 0;
    vround = STARTVIEWCHANGE;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    start_flag = false;
    if (!primary_restart_flag)
    {
      if (follower_restart_flag)
      {
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        mbox = havoc(view, vround);
        if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
        {
          if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
          {
            vround_1_0 = DOVIEWCHANGE;
            send(primary(view, n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));
            vround_1_0 = STARTVIEW;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (start_flag)
  {
    view = 0;
    vround = STARTVIEWCHANGE;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    start_flag = false;
    if (!primary_restart_flag)
    {
      if (!follower_restart_flag)
      {
        mbox = havoc(view, vround);
        if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
        {
          if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
          {
            vround_1_0 = DOVIEWCHANGE;
            send(primary(view, n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));
            vround_1_0 = STARTVIEW;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (!start_flag)
  {
    if (primary_restart_flag)
    {
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      if (follower_restart_flag)
      {
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        mbox = havoc(view, vround);
        if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
        {
          if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
          {
            vround_1_0 = DOVIEWCHANGE;
            send(primary(view, n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));
            vround_1_0 = STARTVIEW;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (!start_flag)
  {
    if (primary_restart_flag)
    {
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      if (!follower_restart_flag)
      {
        mbox = havoc(view, vround);
        if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
        {
          if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
          {
            vround_1_0 = DOVIEWCHANGE;
            send(primary(view, n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));
            vround_1_0 = STARTVIEW;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (!start_flag)
  {
    if (!primary_restart_flag)
    {
      if (follower_restart_flag)
      {
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        mbox = havoc(view, vround);
        if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
        {
          if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
          {
            vround_1_0 = DOVIEWCHANGE;
            send(primary(view, n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));
            vround_1_0 = STARTVIEW;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (!start_flag)
  {
    if (!primary_restart_flag)
    {
      if (!follower_restart_flag)
      {
        mbox = havoc(view, vround);
        if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
        {
          if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
          {
            vround_1_0 = DOVIEWCHANGE;
            send(primary(view, n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));
            vround_1_0 = STARTVIEW;
          }

        }

      }

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
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (start_flag)
  {
    view = 0;
    vround = STARTVIEWCHANGE;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    start_flag = false;
    if (primary_restart_flag)
    {
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      if (follower_restart_flag)
      {
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        mbox = havoc(view, vround);
        if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
        {
          vround_0_0 = DOVIEWCHANGE;
          mbox_0_0 = havoc(view, vround);
          if (((vround_0_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_0->size > f))
          {
            computes_new_log();
            vround_0_1 = STARTVIEW;
            send(all, message(view, STARTVIEW, NULL, NULL, p, local_log()));
            view++;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (start_flag)
  {
    view = 0;
    vround = STARTVIEWCHANGE;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    start_flag = false;
    if (primary_restart_flag)
    {
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      if (!follower_restart_flag)
      {
        mbox = havoc(view, vround);
        if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
        {
          vround_0_0 = DOVIEWCHANGE;
          mbox_0_0 = havoc(view, vround);
          if (((vround_0_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_0->size > f))
          {
            computes_new_log();
            vround_0_1 = STARTVIEW;
            send(all, message(view, STARTVIEW, NULL, NULL, p, local_log()));
            view++;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (start_flag)
  {
    view = 0;
    vround = STARTVIEWCHANGE;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    start_flag = false;
    if (!primary_restart_flag)
    {
      if (follower_restart_flag)
      {
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        mbox = havoc(view, vround);
        if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
        {
          vround_0_0 = DOVIEWCHANGE;
          mbox_0_0 = havoc(view, vround);
          if (((vround_0_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_0->size > f))
          {
            computes_new_log();
            vround_0_1 = STARTVIEW;
            send(all, message(view, STARTVIEW, NULL, NULL, p, local_log()));
            view++;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (start_flag)
  {
    view = 0;
    vround = STARTVIEWCHANGE;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    start_flag = false;
    if (!primary_restart_flag)
    {
      if (!follower_restart_flag)
      {
        mbox = havoc(view, vround);
        if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
        {
          vround_0_0 = DOVIEWCHANGE;
          mbox_0_0 = havoc(view, vround);
          if (((vround_0_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_0->size > f))
          {
            computes_new_log();
            vround_0_1 = STARTVIEW;
            send(all, message(view, STARTVIEW, NULL, NULL, p, local_log()));
            view++;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (!start_flag)
  {
    if (primary_restart_flag)
    {
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      if (follower_restart_flag)
      {
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        mbox = havoc(view, vround);
        if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
        {
          vround_0_0 = DOVIEWCHANGE;
          mbox_0_0 = havoc(view, vround);
          if (((vround_0_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_0->size > f))
          {
            computes_new_log();
            vround_0_1 = STARTVIEW;
            send(all, message(view, STARTVIEW, NULL, NULL, p, local_log()));
            view++;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (!start_flag)
  {
    if (primary_restart_flag)
    {
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      if (!follower_restart_flag)
      {
        mbox = havoc(view, vround);
        if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
        {
          vround_0_0 = DOVIEWCHANGE;
          mbox_0_0 = havoc(view, vround);
          if (((vround_0_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_0->size > f))
          {
            computes_new_log();
            vround_0_1 = STARTVIEW;
            send(all, message(view, STARTVIEW, NULL, NULL, p, local_log()));
            view++;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (!start_flag)
  {
    if (!primary_restart_flag)
    {
      if (follower_restart_flag)
      {
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        mbox = havoc(view, vround);
        if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
        {
          vround_0_0 = DOVIEWCHANGE;
          mbox_0_0 = havoc(view, vround);
          if (((vround_0_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_0->size > f))
          {
            computes_new_log();
            vround_0_1 = STARTVIEW;
            send(all, message(view, STARTVIEW, NULL, NULL, p, local_log()));
            view++;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (!start_flag)
  {
    if (!primary_restart_flag)
    {
      if (!follower_restart_flag)
      {
        mbox = havoc(view, vround);
        if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
        {
          vround_0_0 = DOVIEWCHANGE;
          mbox_0_0 = havoc(view, vround);
          if (((vround_0_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0_0->size > f))
          {
            computes_new_log();
            vround_0_1 = STARTVIEW;
            send(all, message(view, STARTVIEW, NULL, NULL, p, local_log()));
            view++;
          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (start_flag)
  {
    view = 0;
    vround = STARTVIEWCHANGE;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    start_flag = false;
    if (primary_restart_flag)
    {
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      if (follower_restart_flag)
      {
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        mbox = havoc(view, vround);
        if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
        {
          if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
          {
            vround_1_0 = DOVIEWCHANGE;
            send(primary(view, n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));
            vround_1_0 = STARTVIEW;
            mbox_1_0 = havoc(view, vround);
            if (((vround_1_0 == STARTVIEW) && (p != primary(view, n))) && (mbox_1_0->size == 1))
            {
              computes_new_log();
              view++;
            }

          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (start_flag)
  {
    view = 0;
    vround = STARTVIEWCHANGE;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    start_flag = false;
    if (primary_restart_flag)
    {
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      if (!follower_restart_flag)
      {
        mbox = havoc(view, vround);
        if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
        {
          if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
          {
            vround_1_0 = DOVIEWCHANGE;
            send(primary(view, n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));
            vround_1_0 = STARTVIEW;
            mbox_1_0 = havoc(view, vround);
            if (((vround_1_0 == STARTVIEW) && (p != primary(view, n))) && (mbox_1_0->size == 1))
            {
              computes_new_log();
              view++;
            }

          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (start_flag)
  {
    view = 0;
    vround = STARTVIEWCHANGE;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    start_flag = false;
    if (!primary_restart_flag)
    {
      if (follower_restart_flag)
      {
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        mbox = havoc(view, vround);
        if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
        {
          if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
          {
            vround_1_0 = DOVIEWCHANGE;
            send(primary(view, n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));
            vround_1_0 = STARTVIEW;
            mbox_1_0 = havoc(view, vround);
            if (((vround_1_0 == STARTVIEW) && (p != primary(view, n))) && (mbox_1_0->size == 1))
            {
              computes_new_log();
              view++;
            }

          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (start_flag)
  {
    view = 0;
    vround = STARTVIEWCHANGE;
    send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
    start_flag = false;
    if (!primary_restart_flag)
    {
      if (!follower_restart_flag)
      {
        mbox = havoc(view, vround);
        if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
        {
          if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
          {
            vround_1_0 = DOVIEWCHANGE;
            send(primary(view, n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));
            vround_1_0 = STARTVIEW;
            mbox_1_0 = havoc(view, vround);
            if (((vround_1_0 == STARTVIEW) && (p != primary(view, n))) && (mbox_1_0->size == 1))
            {
              computes_new_log();
              view++;
            }

          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (!start_flag)
  {
    if (primary_restart_flag)
    {
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      if (follower_restart_flag)
      {
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        mbox = havoc(view, vround);
        if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
        {
          if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
          {
            vround_1_0 = DOVIEWCHANGE;
            send(primary(view, n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));
            vround_1_0 = STARTVIEW;
            mbox_1_0 = havoc(view, vround);
            if (((vround_1_0 == STARTVIEW) && (p != primary(view, n))) && (mbox_1_0->size == 1))
            {
              computes_new_log();
              view++;
            }

          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (!start_flag)
  {
    if (primary_restart_flag)
    {
      vround = STARTVIEWCHANGE;
      send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
      if (!follower_restart_flag)
      {
        mbox = havoc(view, vround);
        if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
        {
          if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
          {
            vround_1_0 = DOVIEWCHANGE;
            send(primary(view, n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));
            vround_1_0 = STARTVIEW;
            mbox_1_0 = havoc(view, vround);
            if (((vround_1_0 == STARTVIEW) && (p != primary(view, n))) && (mbox_1_0->size == 1))
            {
              computes_new_log();
              view++;
            }

          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (!start_flag)
  {
    if (!primary_restart_flag)
    {
      if (follower_restart_flag)
      {
        vround = STARTVIEWCHANGE;
        send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
        mbox = havoc(view, vround);
        if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
        {
          if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
          {
            vround_1_0 = DOVIEWCHANGE;
            send(primary(view, n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));
            vround_1_0 = STARTVIEW;
            mbox_1_0 = havoc(view, vround);
            if (((vround_1_0 == STARTVIEW) && (p != primary(view, n))) && (mbox_1_0->size == 1))
            {
              computes_new_log();
              view++;
            }

          }

        }

      }

    }

  }

}


}

##########################################
################Path######################
{
int main(int p, int n, int f)
{
  list *mbox_3_1;
  list *mbox_3_0;
  list *mbox_2_1;
  list *mbox_2_0;
  list *mbox_1_1;
  list *mbox_1_0;
  list *mbox_0_1;
  list *mbox_0_0;
  enum vround_typ vround_3_1;
  enum vround_typ vround_3_0;
  enum vround_typ vround_2_1;
  enum vround_typ vround_2_0;
  enum vround_typ vround_1_1;
  enum vround_typ vround_1_0;
  enum vround_typ vround_0_1;
  enum vround_typ vround_0_0;
  int all;
  int view;
  enum vround_typ vround;
  msg *m;
  msg *recv_msg;
  list *mbox;
  _Bool start_flag = true;
  _Bool primary_restart_flag = false;
  _Bool follower_restart_flag = false;
  if (!start_flag)
  {
    if (!primary_restart_flag)
    {
      if (!follower_restart_flag)
      {
        mbox = havoc(view, vround);
        if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
        {
          if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
          {
            vround_1_0 = DOVIEWCHANGE;
            send(primary(view, n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));
            vround_1_0 = STARTVIEW;
            mbox_1_0 = havoc(view, vround);
            if (((vround_1_0 == STARTVIEW) && (p != primary(view, n))) && (mbox_1_0->size == 1))
            {
              computes_new_log();
              view++;
            }

          }

        }

      }

    }

  }

}


}

##########################################
