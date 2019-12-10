#include "stdlib.h"
#include "roundAtoB_types.h"

/*@ ensures (\result == \null) ||
    (\result != \null &&
     \valid(\result) &&
     \initialized(&\result->round) &&
     \initialized(&\result->ballot) &&
     (\result->round == 0 ||  \result->round == 1));
 @*/
msg * recv(int v, int t){
    msg* m = (msg *) malloc(sizeof(msg));
    if (m==NULL) return NULL;
    m->round = v%2;
    m->ballot = t;
    return m;
}

/*@
  requires \true;
 ensures \result >= 0 && \result <= n;
 @*/
int count(list * mboxA, int ballot, int n);

void send(int addr, msg * m);

// Main function ACSL
/*@ requires p>=0 && n>0 && n<=2000;
 @*/