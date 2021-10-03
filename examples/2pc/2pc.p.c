struct list *mbox;
int phase;
enum round_type
{
  ALPHA,
  BETA,
  GAMMA,
  DELTA
};
enum round_type round;
_Bool non_deterministic_choice();
void broadcast();
_Bool Primary(int phase);
_Bool Backup(int phase);
int main()
{
  if (Primary(phase))
  {
    backups = b;
    numBackup = sizeof(backups);
    sendConfig();
    participants = backups;
    participants += (sizeof(participants), this);
    phase = 0;
    round = ALPHA;
  }

  if (Backup(phase))
  {
    phase = 0;
    round = ALPHA;
  }

  while (1)
  {
    if ((Primary(phase) && (round == ALPHA)) && (count(phase, ALPHA, mbox) == 1))
    {
      initMbox(phase);
      broadcast(eventALPHA, (phase = phase, from = this, payload = newcommand));
      round = BETA;
      continue;
    }

    if ((Primary(phase) && (round == BETA)) && (count(phase, BETA, mbox) == numBackup))
    {
      decision[m.phase] = commit_or_abort(m.phase);
      round = GAMMA;
      broadcast(eventGAMMA, (phase = phase, from = this, payload = decision[phase]));
      round = DELTA;
    }

    if ((Primary(phase) && (round == DELTA)) && (count(phase, DELTA, mbox) == numBackup))
    {
      phase = phase + 1;
      round = ALPHA;
    }

    if ((Backup(phase) && (round == ALPHA)) && (count(phase, ALPHA, mbox) == 1))
    {
      round = BETA;
      v = ABORT;
      if (non_deterministic_choice())
      {
        v = COMMIT;
      }

      send(leader(phase), eventBETA);
      round = GAMMA;
      continue;
    }

    if ((Backup(phase) && (round == GAMMA)) && (count(phase, GAMMA, mbox) == 1))
    {
      if (m.payload == COMMIT)
      {
        decision[phase] = COMMIT;
      }
      else
      {
        decision[phase] = ABORT;
      }

      round = DELTA;
      send(leader(phase), eventDELTA);
      phase = phase + 1;
      round = ALPHA;
      continue;
    }

  }

}


