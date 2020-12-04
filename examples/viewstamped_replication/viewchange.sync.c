################## STARTVIEWCHANGE ######################
SEND: 
{
  send(all, message(view, STARTVIEWCHANGE, p, null_log()));
}

UPDATE: 
{
  if (((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
  {
    __pred_0 = ((vround == STARTVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f);
  }

  if (((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f))
  {
    __pred_2 = ((vround == STARTVIEWCHANGE) && (p != primary(view, n))) && (mbox->size > f);
  }

}

################## DOVIEWCHANGE ######################
SEND: 
{
  if (__pred_2)
  {
    send(primary(view, n), message(view, DOVIEWCHANGE, p, local_log()));
  }

}

UPDATE: 
{
  if (__pred_0)
  {
    if (((vround == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f))
    {
      __pred_1 = ((vround == DOVIEWCHANGE) && (p == primary(view, n))) && (mbox->size > f);
      computes_new_log();
    }

  }

}

################## STARTVIEW ######################
SEND: 
{
  if (__pred_0 && __pred_1)
  {
    send(all, message(view, STARTVIEW, p, local_log()));
  }

}

UPDATE: 
{
  if (__pred_2)
  {
    if (((vround == STARTVIEW) && (p != primary(view, n))) && (mbox->size == 1))
    {
      __pred_3 = ((vround == STARTVIEW) && (p != primary(view, n))) && (mbox->size == 1);
      computes_new_log();
    }

  }

}

