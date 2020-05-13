No inner algorithm detected

def round STARTVIEWCHANGE:
  SEND():

if(round == STARTVIEWCHANGE){
  send(all, message(PHASE, STARTVIEWCHANGE, NULL, NULL, p));
}

  UPDATE():

if(round == STARTVIEWCHANGE)
{
  old_0_vround = vround;
  old_0_p = p;
  if ((((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f)))
  {
    vround = DOVIEWCHANGE;
  }
  
  old_2_vround = vround;
  old_2_p = p;
  if ((((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f)))
  {
    vround = DOVIEWCHANGE;
  }
  old_0_vround = vround;
  old_0_p = p;
  if (!(((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f)))
  {
    old_2_vround = vround;
    old_2_p = p;
    if ((((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f)))
    {
      vround = DOVIEWCHANGE;
    }
  }
}


def round DOVIEWCHANGE:
  SEND():

if(round == DOVIEWCHANGE){
  if ((((old_2_vround == STARTVIEWCHANGE) && (old_2_p != primary(view, n))) && (count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f)))
  {
    send(primary(PHASE, n), message(PHASE, DOVIEWCHANGE, NULL, NULL, p, local_log()));
  }
}

  UPDATE():

if(round == DOVIEWCHANGE)
{
  if ((((old_0_vround == STARTVIEWCHANGE) && (old_0_p == primary(view, n))) && (count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f)))
  {
    old_1_vround = vround;
    old_1_p = p;
    if ((((vround == DOVIEWCHANGE) && (p == primary(view, n))) && (count_messages(mbox, view, DOVIEWCHANGE, NULL, NULL) > f)))
    {
      computes_new_log();
      vround = STARTVIEW;
    }
  }
  if ((((old_2_vround == STARTVIEWCHANGE) && (old_2_p != primary(view, n))) && (count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f)))
  {
    vround = STARTVIEW;
  }
}


def round STARTVIEW:
  SEND():

if(round == STARTVIEW){
  if ((((old_0_vround == STARTVIEWCHANGE) && (old_0_p == primary(view, n))) && (count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f)) && (((old_1_vround == DOVIEWCHANGE) && (old_1_p == primary(view, n))) && (count_messages(mbox, view, DOVIEWCHANGE, NULL, NULL) > f)))
  {
    send(all, message(PHASE, STARTVIEW, NULL, NULL, p, local_log()));
  }
}

  UPDATE():

if(round == STARTVIEW)
{
  if ((((old_0_vround == STARTVIEWCHANGE) && (old_0_p == primary(view, n))) && (count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f)) && (((old_1_vround == DOVIEWCHANGE) && (old_1_p == primary(view, n))) && (count_messages(mbox, view, DOVIEWCHANGE, NULL, NULL) > f)))
  {
    vround = STARTVIEWCHANGE;
  }
  if ((((old_2_vround == STARTVIEWCHANGE) && (old_2_p != primary(view, n))) && (count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f)))
  {
    if ((((vround == STARTVIEW) && (p != primary(view, n))) && (count_messages(mbox, view, STARTVIEW, NULL, NULL) == 1)))
    {
      computes_new_log();
      vround = STARTVIEWCHANGE;
    }
  }
}


