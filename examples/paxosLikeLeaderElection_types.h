struct Msg
{
  int round;
  int ballot;
  int leader;
};
typedef struct Msg msg;
typedef struct List
{
  msg *message;
  struct List *next;
  int size;
} list;

enum round_typ {NewBallot, AckBallot};