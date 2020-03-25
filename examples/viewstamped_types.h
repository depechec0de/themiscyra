struct Msg
{
  int phase;
  int round;
  
  int view;
  int replica;
  void* log;
};
typedef struct Msg msg;
typedef struct List
{
  msg *message;
  struct List *next;
  int size;
} list;

enum round_typ {STARTVIEWCHANGE, DOVIEWCHANGE, STARTVIEW, REQUEST, PREPARE, PREPAREOK};