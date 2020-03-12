struct Msg
{
  int round;
  int reg;
  void* timedout_msgs;
  void* decided_log;
  void* proofs;
};
typedef struct Msg msg;
typedef struct List
{
  msg *message;
  struct List *next;
  int size;
} list;

enum round_typ {STOP, STOPDATA, SYNC};