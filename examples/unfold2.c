#include "roundAtoB_types.h"
#include "roundAtoB_decl.h"

struct Msg
{
  int round;
  int ballot;
};
enum round_typ_B {FIRST_ROUND, SECOND_ROUND, AUX_ROUND} ;

typedef struct Msg msg;
typedef struct List
{
  msg *message;
  struct List *next;
  int size;
} list;


msg* recv();

int main(int p, int n)
{
    int round;
    int ballot;
    int v=p;
    int t=p;
    int all=1000;
    int timeout;
    
    msg* m;
    msg* recv_msg;
    list* mbox=NULL;


while(true){
    round = FIRST_ROUND;
    ballot = 0;
    m = (msg *) malloc(sizeof(msg));
    if (m==NULL) return 0;
    m->round = FIRST_ROUND;
    m->ballot = ballot;
    mbox = NULL;
    send(all, m);


      if (round == FIRST_ROUND) {
        if (count(mbox, ballot,n) > ((2 * n) / 3)){
                    round =  SECOND_ROUND;
                    m = (msg *) malloc(sizeof(msg));
                    if (m==NULL) return 0;
                    m->round = SECOND_ROUND;
                    m->ballot = ballot;
                    send(all, m);
                    round = AUX_ROUND;
                    } 
                    else{
                        ballot++;
                        round = AUX_ROUND; 
                        
                    }            
                }else  if (round == SECOND_ROUND) {
                            if(count(mbox, ballot,n) > ((2 * n) / 3))
                                 {
                            round = AUX_ROUND;
                            ballot++;
                            }else{
                                ballot++;
                                round = AUX_ROUND;
                            }
                }else{  ballot++;
                        round = AUX_ROUND; 
                        }

            

        
}
    return 0;
}
