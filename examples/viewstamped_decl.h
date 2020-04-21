#include "stdlib.h"
#include "viewstamped_types.h"

/*@ ensures (\result == \null) ||
    (\result != \null &&
    \valid(\result) &&
    \initialized(&\result->round) &&
    \initialized(&\result->ballot) &&
    (\result->round == 0 ||  \result->round == 1));
@*/
msg * recv();

/*@
requires \true;
ensures \result >= 0 && \result <= n;
@*/
int count(list * mbox, int regency, int round, int n);

int size(list * mbox);

void send(int addr, msg * m);

// Count how many messages in mbox satisfy to be equal in view, vround, phase and nround.
int count_messages(list * mbox, int view, enum vround_typ vround, int phase, enum nround_typ nround);

/*@ requires p>=0 && n>0 && n<=2000;
@*/
int func(int p, int n, int f);
