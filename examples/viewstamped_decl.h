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

/*@ requires p>=0 && n>0 && n<=2000;
@*/
int func(int p, int n, int f);
