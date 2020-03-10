struct Msg
{
  int round;
  int reg;
  list* timedout_msgs;
  list* decided_log;
  list* proofs;
};
typedef struct Msg msg;
typedef struct List
{
  msg *message;
  struct List *next;
  int size;
} list;

enum round_typ {STOP, STOPDATA, SYNC};