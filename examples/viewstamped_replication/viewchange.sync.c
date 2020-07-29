################## STARTVIEWCHANGE ######################
############ send ############
int main()
{
  send(all, message(view, STARTVIEWCHANGE, p, null_log()));
}


############ update ############
int main()
{
  vround = STARTVIEWCHANGE;
  view = 0;
  mbox = havoc(view, vround);
  if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
  {
    vround_0 = DOVIEWCHANGE;
  }

  if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
  {
    vround_0 = DOVIEWCHANGE;
  }

}


################## DOVIEWCHANGE ######################
############ send ############
int main()
{
  if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
  {
    send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
  }

}


############ update ############
int main()
{
  if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
  {
    vround_0 = DOVIEWCHANGE;
    mbox_0 = havoc(view, vround_0);
    if (((vround_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0->size > f))
    {
      computes_new_log();
      vround_1 = STARTVIEW;
    }

  }

  if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
  {
    vround_0 = DOVIEWCHANGE;
    vround_0 = STARTVIEW;
  }

}


################## STARTVIEW ######################
############ send ############
int main()
{
  if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
  {
    if (((vround_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0->size > f))
    {
      send(all, message(view, STARTVIEW, p, local_log()));
    }

  }

}


############ update ############
int main()
{
  if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
  {
    if (((vround_0 == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox_0->size > f))
    {
      vround_1 = STARTVIEW;
      view++;
    }

  }

  if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
  {
    vround_0 = STARTVIEW;
    mbox_0 = havoc(view, vround_0);
    if (((vround_0 == STARTVIEW) && (p != primary(view, n))) && (mbox_0->size == 1))
    {
      computes_new_log();
      view++;
    }

  }

}


