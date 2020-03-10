#include "stdlib.h"
#include "paxosLikeLeaderElection_types.h"

/*@ ensures (\result == \null) ||
    (\result != \null &&
     \valid(\result) &&
     \initialized(&\result->round) &&
     \initialized(&\result->ballot) &&
     (\result->round == 0 ||  \result->round == 1));
 @*/
msg * recv(){
    msg* m = (msg *) malloc(sizeof(msg));
    if (m==NULL) return NULL;

    return m;
}

/*@
  requires \true;
 ensures \result >= 0 && \result <= n;
 @*/
int count(list * mboxA, int ballot, int n);

void send(int addr, msg * m);

/*@ requires p>=0 && n>0 && n<=2000;
@*/
int func(int p, int n);
