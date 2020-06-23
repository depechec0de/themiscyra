STARTVIEWCHANGE
################Path######################
{
  if (start_flag)
  {
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
          vround_0 = DOVIEWCHANGE;
        }

      }

    }

  }

}

##########################################
################Path######################
{
  if (start_flag)
  {
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
            vround_0 = DOVIEWCHANGE;
          }

        }

      }

    }

  }

}

##########################################
################Path######################
{
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
          vround_0 = DOVIEWCHANGE;
        }

      }

    }

  }

}

##########################################
################Path######################
{
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
            vround_0 = DOVIEWCHANGE;
          }

        }

      }

    }

  }

}

##########################################
################Path######################
{
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
          vround_0 = DOVIEWCHANGE;
        }

      }

    }

  }

}

##########################################
################Path######################
{
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
            vround_0 = DOVIEWCHANGE;
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
  if (!start_flag)
  {
    if (!primary_restart_flag)
    {
      if (!follower_restart_flag)
      {
        if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
        {
          vround_0 = DOVIEWCHANGE;
          mbox_0 = havoc(view, vround);
          if (((vround_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0->size > f))
          {
            computes_new_log();
            vround_1 = STARTVIEW;
          }

        }

      }

    }

  }

}

##########################################
################Path######################
{
  if (!start_flag)
  {
    if (!primary_restart_flag)
    {
      if (!follower_restart_flag)
      {
        if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
        {
          if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
          {
            vround_0 = DOVIEWCHANGE;
            send(primary(view, n), message(view, DOVIEWCHANGE, NULL, NULL, p, local_log()));
            vround_0 = STARTVIEW;
          }

        }

      }

    }

  }

}

##########################################
STARTVIEW
