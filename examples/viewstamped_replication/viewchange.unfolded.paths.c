STARTVIEWCHANGE
################Path######################
{
  vround = STARTVIEWCHANGE;
  view = 0;
  send(all, message(view, STARTVIEWCHANGE, NULL, NULL, p));
  mbox = havoc(view, vround);
  if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
  {
    vround_0 = DOVIEWCHANGE;
  }

}

##########################################
################Path######################
{
  vround = STARTVIEWCHANGE;
  view = 0;
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

##########################################
DOVIEWCHANGE
################Path######################
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

##########################################
################Path######################
{
  if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
  {
    if (!(((vround_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0->size > f)))
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

##########################################
################Path######################
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

##########################################
STARTVIEW
################Path######################
{
  if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
  {
    if (((vround_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0->size > f))
    {
      vround_1 = STARTVIEW;
      send(all, message(view, STARTVIEW, NULL, NULL, p, local_log()));
      view++;
    }

  }

}

##########################################
################Path######################
{
  if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
  {
    if (!(((vround_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0->size > f)))
    {
      if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
      {
        vround_0 = STARTVIEW;
        mbox_0 = havoc(view, vround);
        if (((vround_0 == STARTVIEW) && (p != primary(view, n))) && (mbox_0->size == 1))
        {
          computes_new_log();
          view++;
        }

      }

    }

  }

}

##########################################
################Path######################
{
  if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f)))
  {
    if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
    {
      vround_0 = STARTVIEW;
      mbox_0 = havoc(view, vround);
      if (((vround_0 == STARTVIEW) && (p != primary(view, n))) && (mbox_0->size == 1))
      {
        computes_new_log();
        view++;
      }

    }

  }

}

##########################################
