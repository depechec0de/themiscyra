struct Msg
{
  int view;
  int vround;
  int opnumber;
  int nround;
  
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

enum vround_typ {STARTVIEWCHANGE, DOVIEWCHANGE, STARTVIEW};
enum nround_typ {PREPARE, PREPAREOK, COMMIT};