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
void init_mbox(Phase phase);
void commit_or_abort(Phase phase);
Vote get_decision(Phase p);
void broadcast(event message, Phase phase, machine from, data payload);
void initConfig(seq[Backup] b);
data payload(Message m);
Primary leader(int phase);
void set_decision(Phase phase, Vote vote);
data payload(Message m);
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
      init_mbox(phase);
      broadcast(ALPHA, phase, this, newcommand);
      round = BETA;
      continue;
    }

    if ((Primary(phase) && (round == BETA)) && (count(phase, BETA, mbox) == numBackup))
    {
      commit_or_abort(m.phase);
      round = GAMMA;
      broadcast(GAMMA, phase, this, get_decision(phase));
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
        set_decision(phase, COMMIT);
      }
      else
      {
        set_decision(phase, ABORT);
      }

      round = DELTA;
      send(leader(phase), DELTA);
      phase = phase + 1;
      round = ALPHA;
      continue;
    }

  }

}


