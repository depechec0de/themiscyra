struct msg
{
  int phase;
  enum round_type round;
  int replica;
  int command;
  _Bool commit;
  _Bool ack;
};
struct list
{
  struct msg *message;
  struct list *next;
  int size;
};
enum round_type
{
  ALPHA,
  BETA,
  GAMMA,
  DELTA
};
_Bool send(int addr, struct msg *m);
struct list *havoc(int view, enum round_type vround);
int primary(int view, int n);
struct msg *message(int phase, enum round_type round, int replica, int command, _Bool commit, _Bool ack);
int count(int phase, enum round_type round, struct list *mbox);
_Bool all_followers_commit(int phase, enum round_type round, struct list *mbox);
_Bool primary_commit(int phase, enum round_type round, struct list *mbox);
int null_int();
int command();
_Bool commit_or_abort();
_Bool null_bool();
_Bool execute_command();
_Bool add_msg(struct msg *m, struct list *mbox);
_Bool recv(int phase, enum round_type round);
int main()
{
  int p;
  int n;
  int all;
  int phase;
  _Bool commit;
  enum round_type round;
  struct msg *m;
  struct msg *recv_msg;
  struct list *mbox;
  phase = 0;
  round = ALPHA;
  while (1)
  {
    if ((round == ALPHA) && (p == primary(phase, n)))
    {
      send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
      round = BETA;
      if ((round == ALPHA) && (p == primary(phase, n)))
      {
        send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
        round = BETA;
        if ((round == ALPHA) && (p == primary(phase, n)))
        {
          send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
          round = BETA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
        {
          commit = commit_or_abort();
          round = BETA;
          send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
          round = GAMMA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
        {
          commit = all_followers_commit(phase, BETA, mbox);
          round = GAMMA;
          send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
          round = DELTA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
        {
          commit = primary_commit(phase, GAMMA, mbox);
          if (commit)
          {
            execute_command();
          }

          round = DELTA;
          send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
        {
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        break;
      }

      if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
      {
        commit = commit_or_abort();
        round = BETA;
        send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
        round = GAMMA;
        if ((round == ALPHA) && (p == primary(phase, n)))
        {
          send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
          round = BETA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
        {
          commit = commit_or_abort();
          round = BETA;
          send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
          round = GAMMA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
        {
          commit = all_followers_commit(phase, BETA, mbox);
          round = GAMMA;
          send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
          round = DELTA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
        {
          commit = primary_commit(phase, GAMMA, mbox);
          if (commit)
          {
            execute_command();
          }

          round = DELTA;
          send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
        {
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        break;
      }

      if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
      {
        commit = all_followers_commit(phase, BETA, mbox);
        round = GAMMA;
        send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
        round = DELTA;
        if ((round == ALPHA) && (p == primary(phase, n)))
        {
          send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
          round = BETA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
        {
          commit = commit_or_abort();
          round = BETA;
          send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
          round = GAMMA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
        {
          commit = all_followers_commit(phase, BETA, mbox);
          round = GAMMA;
          send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
          round = DELTA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
        {
          commit = primary_commit(phase, GAMMA, mbox);
          if (commit)
          {
            execute_command();
          }

          round = DELTA;
          send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
        {
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        break;
      }

      if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
      {
        commit = primary_commit(phase, GAMMA, mbox);
        if (commit)
        {
          execute_command();
        }

        round = DELTA;
        send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
        phase++;
        round = ALPHA;
        if ((round == ALPHA) && (p == primary(phase, n)))
        {
          send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
          round = BETA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
        {
          commit = commit_or_abort();
          round = BETA;
          send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
          round = GAMMA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
        {
          commit = all_followers_commit(phase, BETA, mbox);
          round = GAMMA;
          send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
          round = DELTA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
        {
          commit = primary_commit(phase, GAMMA, mbox);
          if (commit)
          {
            execute_command();
          }

          round = DELTA;
          send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
        {
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        break;
      }

      if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
      {
        phase++;
        round = ALPHA;
        if ((round == ALPHA) && (p == primary(phase, n)))
        {
          send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
          round = BETA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
        {
          commit = commit_or_abort();
          round = BETA;
          send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
          round = GAMMA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
        {
          commit = all_followers_commit(phase, BETA, mbox);
          round = GAMMA;
          send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
          round = DELTA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
        {
          commit = primary_commit(phase, GAMMA, mbox);
          if (commit)
          {
            execute_command();
          }

          round = DELTA;
          send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
        {
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        break;
      }

      break;
    }

    if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
    {
      commit = commit_or_abort();
      round = BETA;
      send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
      round = GAMMA;
      if ((round == ALPHA) && (p == primary(phase, n)))
      {
        send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
        round = BETA;
        if ((round == ALPHA) && (p == primary(phase, n)))
        {
          send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
          round = BETA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
        {
          commit = commit_or_abort();
          round = BETA;
          send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
          round = GAMMA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
        {
          commit = all_followers_commit(phase, BETA, mbox);
          round = GAMMA;
          send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
          round = DELTA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
        {
          commit = primary_commit(phase, GAMMA, mbox);
          if (commit)
          {
            execute_command();
          }

          round = DELTA;
          send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
        {
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        break;
      }

      if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
      {
        commit = commit_or_abort();
        round = BETA;
        send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
        round = GAMMA;
        if ((round == ALPHA) && (p == primary(phase, n)))
        {
          send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
          round = BETA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
        {
          commit = commit_or_abort();
          round = BETA;
          send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
          round = GAMMA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
        {
          commit = all_followers_commit(phase, BETA, mbox);
          round = GAMMA;
          send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
          round = DELTA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
        {
          commit = primary_commit(phase, GAMMA, mbox);
          if (commit)
          {
            execute_command();
          }

          round = DELTA;
          send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
        {
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        break;
      }

      if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
      {
        commit = all_followers_commit(phase, BETA, mbox);
        round = GAMMA;
        send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
        round = DELTA;
        if ((round == ALPHA) && (p == primary(phase, n)))
        {
          send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
          round = BETA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
        {
          commit = commit_or_abort();
          round = BETA;
          send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
          round = GAMMA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
        {
          commit = all_followers_commit(phase, BETA, mbox);
          round = GAMMA;
          send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
          round = DELTA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
        {
          commit = primary_commit(phase, GAMMA, mbox);
          if (commit)
          {
            execute_command();
          }

          round = DELTA;
          send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
        {
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        break;
      }

      if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
      {
        commit = primary_commit(phase, GAMMA, mbox);
        if (commit)
        {
          execute_command();
        }

        round = DELTA;
        send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
        phase++;
        round = ALPHA;
        if ((round == ALPHA) && (p == primary(phase, n)))
        {
          send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
          round = BETA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
        {
          commit = commit_or_abort();
          round = BETA;
          send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
          round = GAMMA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
        {
          commit = all_followers_commit(phase, BETA, mbox);
          round = GAMMA;
          send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
          round = DELTA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
        {
          commit = primary_commit(phase, GAMMA, mbox);
          if (commit)
          {
            execute_command();
          }

          round = DELTA;
          send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
        {
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        break;
      }

      if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
      {
        phase++;
        round = ALPHA;
        if ((round == ALPHA) && (p == primary(phase, n)))
        {
          send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
          round = BETA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
        {
          commit = commit_or_abort();
          round = BETA;
          send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
          round = GAMMA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
        {
          commit = all_followers_commit(phase, BETA, mbox);
          round = GAMMA;
          send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
          round = DELTA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
        {
          commit = primary_commit(phase, GAMMA, mbox);
          if (commit)
          {
            execute_command();
          }

          round = DELTA;
          send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
        {
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        break;
      }

      break;
    }

    if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
    {
      commit = all_followers_commit(phase, BETA, mbox);
      round = GAMMA;
      send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
      round = DELTA;
      if ((round == ALPHA) && (p == primary(phase, n)))
      {
        send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
        round = BETA;
        if ((round == ALPHA) && (p == primary(phase, n)))
        {
          send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
          round = BETA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
        {
          commit = commit_or_abort();
          round = BETA;
          send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
          round = GAMMA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
        {
          commit = all_followers_commit(phase, BETA, mbox);
          round = GAMMA;
          send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
          round = DELTA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
        {
          commit = primary_commit(phase, GAMMA, mbox);
          if (commit)
          {
            execute_command();
          }

          round = DELTA;
          send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
        {
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        break;
      }

      if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
      {
        commit = commit_or_abort();
        round = BETA;
        send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
        round = GAMMA;
        if ((round == ALPHA) && (p == primary(phase, n)))
        {
          send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
          round = BETA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
        {
          commit = commit_or_abort();
          round = BETA;
          send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
          round = GAMMA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
        {
          commit = all_followers_commit(phase, BETA, mbox);
          round = GAMMA;
          send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
          round = DELTA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
        {
          commit = primary_commit(phase, GAMMA, mbox);
          if (commit)
          {
            execute_command();
          }

          round = DELTA;
          send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
        {
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        break;
      }

      if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
      {
        commit = all_followers_commit(phase, BETA, mbox);
        round = GAMMA;
        send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
        round = DELTA;
        if ((round == ALPHA) && (p == primary(phase, n)))
        {
          send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
          round = BETA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
        {
          commit = commit_or_abort();
          round = BETA;
          send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
          round = GAMMA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
        {
          commit = all_followers_commit(phase, BETA, mbox);
          round = GAMMA;
          send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
          round = DELTA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
        {
          commit = primary_commit(phase, GAMMA, mbox);
          if (commit)
          {
            execute_command();
          }

          round = DELTA;
          send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
        {
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        break;
      }

      if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
      {
        commit = primary_commit(phase, GAMMA, mbox);
        if (commit)
        {
          execute_command();
        }

        round = DELTA;
        send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
        phase++;
        round = ALPHA;
        if ((round == ALPHA) && (p == primary(phase, n)))
        {
          send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
          round = BETA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
        {
          commit = commit_or_abort();
          round = BETA;
          send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
          round = GAMMA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
        {
          commit = all_followers_commit(phase, BETA, mbox);
          round = GAMMA;
          send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
          round = DELTA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
        {
          commit = primary_commit(phase, GAMMA, mbox);
          if (commit)
          {
            execute_command();
          }

          round = DELTA;
          send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
        {
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        break;
      }

      if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
      {
        phase++;
        round = ALPHA;
        if ((round == ALPHA) && (p == primary(phase, n)))
        {
          send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
          round = BETA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
        {
          commit = commit_or_abort();
          round = BETA;
          send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
          round = GAMMA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
        {
          commit = all_followers_commit(phase, BETA, mbox);
          round = GAMMA;
          send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
          round = DELTA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
        {
          commit = primary_commit(phase, GAMMA, mbox);
          if (commit)
          {
            execute_command();
          }

          round = DELTA;
          send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
        {
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        break;
      }

      break;
    }

    if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
    {
      commit = primary_commit(phase, GAMMA, mbox);
      if (commit)
      {
        execute_command();
      }

      round = DELTA;
      send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
      phase++;
      round = ALPHA;
      if ((round == ALPHA) && (p == primary(phase, n)))
      {
        send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
        round = BETA;
        if ((round == ALPHA) && (p == primary(phase, n)))
        {
          send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
          round = BETA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
        {
          commit = commit_or_abort();
          round = BETA;
          send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
          round = GAMMA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
        {
          commit = all_followers_commit(phase, BETA, mbox);
          round = GAMMA;
          send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
          round = DELTA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
        {
          commit = primary_commit(phase, GAMMA, mbox);
          if (commit)
          {
            execute_command();
          }

          round = DELTA;
          send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
        {
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        break;
      }

      if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
      {
        commit = commit_or_abort();
        round = BETA;
        send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
        round = GAMMA;
        if ((round == ALPHA) && (p == primary(phase, n)))
        {
          send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
          round = BETA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
        {
          commit = commit_or_abort();
          round = BETA;
          send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
          round = GAMMA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
        {
          commit = all_followers_commit(phase, BETA, mbox);
          round = GAMMA;
          send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
          round = DELTA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
        {
          commit = primary_commit(phase, GAMMA, mbox);
          if (commit)
          {
            execute_command();
          }

          round = DELTA;
          send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
        {
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        break;
      }

      if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
      {
        commit = all_followers_commit(phase, BETA, mbox);
        round = GAMMA;
        send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
        round = DELTA;
        if ((round == ALPHA) && (p == primary(phase, n)))
        {
          send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
          round = BETA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
        {
          commit = commit_or_abort();
          round = BETA;
          send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
          round = GAMMA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
        {
          commit = all_followers_commit(phase, BETA, mbox);
          round = GAMMA;
          send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
          round = DELTA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
        {
          commit = primary_commit(phase, GAMMA, mbox);
          if (commit)
          {
            execute_command();
          }

          round = DELTA;
          send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
        {
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        break;
      }

      if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
      {
        commit = primary_commit(phase, GAMMA, mbox);
        if (commit)
        {
          execute_command();
        }

        round = DELTA;
        send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
        phase++;
        round = ALPHA;
        if ((round == ALPHA) && (p == primary(phase, n)))
        {
          send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
          round = BETA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
        {
          commit = commit_or_abort();
          round = BETA;
          send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
          round = GAMMA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
        {
          commit = all_followers_commit(phase, BETA, mbox);
          round = GAMMA;
          send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
          round = DELTA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
        {
          commit = primary_commit(phase, GAMMA, mbox);
          if (commit)
          {
            execute_command();
          }

          round = DELTA;
          send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
        {
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        break;
      }

      if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
      {
        phase++;
        round = ALPHA;
        if ((round == ALPHA) && (p == primary(phase, n)))
        {
          send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
          round = BETA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
        {
          commit = commit_or_abort();
          round = BETA;
          send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
          round = GAMMA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
        {
          commit = all_followers_commit(phase, BETA, mbox);
          round = GAMMA;
          send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
          round = DELTA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
        {
          commit = primary_commit(phase, GAMMA, mbox);
          if (commit)
          {
            execute_command();
          }

          round = DELTA;
          send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
        {
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        break;
      }

      break;
    }

    if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
    {
      phase++;
      round = ALPHA;
      if ((round == ALPHA) && (p == primary(phase, n)))
      {
        send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
        round = BETA;
        if ((round == ALPHA) && (p == primary(phase, n)))
        {
          send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
          round = BETA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
        {
          commit = commit_or_abort();
          round = BETA;
          send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
          round = GAMMA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
        {
          commit = all_followers_commit(phase, BETA, mbox);
          round = GAMMA;
          send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
          round = DELTA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
        {
          commit = primary_commit(phase, GAMMA, mbox);
          if (commit)
          {
            execute_command();
          }

          round = DELTA;
          send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
        {
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        break;
      }

      if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
      {
        commit = commit_or_abort();
        round = BETA;
        send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
        round = GAMMA;
        if ((round == ALPHA) && (p == primary(phase, n)))
        {
          send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
          round = BETA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
        {
          commit = commit_or_abort();
          round = BETA;
          send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
          round = GAMMA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
        {
          commit = all_followers_commit(phase, BETA, mbox);
          round = GAMMA;
          send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
          round = DELTA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
        {
          commit = primary_commit(phase, GAMMA, mbox);
          if (commit)
          {
            execute_command();
          }

          round = DELTA;
          send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
        {
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        break;
      }

      if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
      {
        commit = all_followers_commit(phase, BETA, mbox);
        round = GAMMA;
        send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
        round = DELTA;
        if ((round == ALPHA) && (p == primary(phase, n)))
        {
          send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
          round = BETA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
        {
          commit = commit_or_abort();
          round = BETA;
          send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
          round = GAMMA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
        {
          commit = all_followers_commit(phase, BETA, mbox);
          round = GAMMA;
          send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
          round = DELTA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
        {
          commit = primary_commit(phase, GAMMA, mbox);
          if (commit)
          {
            execute_command();
          }

          round = DELTA;
          send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
        {
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        break;
      }

      if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
      {
        commit = primary_commit(phase, GAMMA, mbox);
        if (commit)
        {
          execute_command();
        }

        round = DELTA;
        send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
        phase++;
        round = ALPHA;
        if ((round == ALPHA) && (p == primary(phase, n)))
        {
          send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
          round = BETA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
        {
          commit = commit_or_abort();
          round = BETA;
          send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
          round = GAMMA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
        {
          commit = all_followers_commit(phase, BETA, mbox);
          round = GAMMA;
          send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
          round = DELTA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
        {
          commit = primary_commit(phase, GAMMA, mbox);
          if (commit)
          {
            execute_command();
          }

          round = DELTA;
          send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
        {
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        break;
      }

      if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
      {
        phase++;
        round = ALPHA;
        if ((round == ALPHA) && (p == primary(phase, n)))
        {
          send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
          round = BETA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
        {
          commit = commit_or_abort();
          round = BETA;
          send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
          round = GAMMA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
        {
          commit = all_followers_commit(phase, BETA, mbox);
          round = GAMMA;
          send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
          round = DELTA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
        {
          commit = primary_commit(phase, GAMMA, mbox);
          if (commit)
          {
            execute_command();
          }

          round = DELTA;
          send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
        {
          phase++;
          round = ALPHA;
          if ((round == ALPHA) && (p == primary(phase, n)))
          {
            send(all, message(phase, ALPHA, p, command(), null_bool(), null_bool()));
            round = BETA;
            continue;
          }

          if (((round == ALPHA) && (p != primary(phase, n))) && (count(phase, ALPHA, mbox) == 1))
          {
            commit = commit_or_abort();
            round = BETA;
            send(primary(phase, n), message(phase, BETA, p, null_int(), commit, null_bool()));
            round = GAMMA;
            continue;
          }

          if (((round == BETA) && (p == primary(phase, n))) && (count(phase, BETA, mbox) == n))
          {
            commit = all_followers_commit(phase, BETA, mbox);
            round = GAMMA;
            send(all, message(phase, GAMMA, p, null_int(), commit, null_bool()));
            round = DELTA;
            continue;
          }

          if (((round == GAMMA) && (p != primary(phase, n))) && (count(phase, GAMMA, mbox) == 1))
          {
            commit = primary_commit(phase, GAMMA, mbox);
            if (commit)
            {
              execute_command();
            }

            round = DELTA;
            send(primary(phase, n), message(phase, DELTA, p, null_int(), null_bool(), true));
            phase++;
            round = ALPHA;
            continue;
          }

          if (((round == DELTA) && (p == primary(phase, n))) && (count(phase, DELTA, mbox) == n))
          {
            phase++;
            round = ALPHA;
            continue;
          }

          break;
        }

        break;
      }

      break;
    }

  }

}


