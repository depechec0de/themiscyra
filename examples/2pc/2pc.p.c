struct list *mbox;
int N;
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
    initConfig(backups);
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
      broadcast(ALPHA, phase, this, newcommand);
      round = BETA;
      continue;
    }

    if ((Primary(phase) && (round == BETA)) && (count(phase, BETA, mbox) == numBackup))
    {
      decision[m.phase] = commit_or_abort(m.phase);
      round = GAMMA;
      broadcast(GAMMA, phase, this, decision[phase]);
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
      vote = ABORT;
      if (non_deterministic_choice())
      {
        vote = COMMIT;
      }

      send(leader(phase), BETA);
      round = GAMMA;
      continue;
    }

    if ((Backup(phase) && (round == GAMMA)) && (count(phase, GAMMA, mbox) == 1))
    {
      if (payload(m) == COMMIT)
      {
        decision[phase] = COMMIT;
      }
      else
      {
        decision[phase] = ABORT;
      }

      round = DELTA;
      send(leader(phase), DELTA);
      phase = phase + 1;
      round = ALPHA;
      continue;
    }

  }

}


