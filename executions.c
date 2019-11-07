//{}
round = A;
ballot = 0;

//{round==A, ballot==0}
m = (msg *) malloc(sizeof(msg));
m->round = round;
m->ballot = ballot;
send(all,m);
recv_msg = recv();

if(recv_msg!=NULL && recv_msg->round==A ){

    //{round==A, ballot==0, recv_msg!=NULL, recv_msg->round==A}
    mboxA[recv_msg->ballot] = mboxA[recv_msg->ballot] + recv_msg;

    //{round==A, ballot==0, recv_msg!=NULL, recv_msg->round==A, |mboxA[recv_msg->ballot]|==1}
    if(round==A && countA(mboxA,ballot) >= 2*n/3){
        
        // CAN'T ENTER BECAUSE OF CONTEXT: countA(mboxA,ballot) >= 2*n/3, |mboxA[recv_msg->round]|==1 => not sat

        

    }else{
        //{round==A, ballot==0, ¬(round==A && countA(mboxA,ballot) > 2*n/3), recv_msg!=NULL, recv_msg->round==A, |mboxA[recv_msg->round]|==1}

        if(recv_msg!=NULL && recv_msg->round==B){
            // CAN'T ENTER BECAUSE OF CONTEXT: recv_msg->round==A && recv_msg->round==B => not sat
        }

        if(timeout){
            // CAN'T ENTER BECAUSE OF CONTEXT: recv_msg!=NULL && TIMEOUT => not sat
        }
        // ITERATE AGAIN

        recv_msg = recv();

        if(recv_msg!=NULL && recv_msg->round==A ){
            //{round==A, ballot==0, recv_msg!=NULL, recv_msg->round==A}
            mboxA[recv_msg->ballot] = mboxA[recv_msg->ballot] + recv_msg;
            //{round==A, ballot==0, recv_msg!=NULL, recv_msg->round==A}
            if(round==A && countA(mboxA,ballot) > 2*n/3){

                //{round==A, ballot==0, recv_msg!=NULL, recv_msg->round==A, countA(mboxA,ballot) > 2*n/3}

                dispose(mboxA);
                round = B;

                //{round==B, ballot==0, recv_msg!=NULL, recv_msg->round==A, countA(mboxA,ballot) > 2*n/3}
                m = (msg *) malloc(sizeof(msg));
                m->round = round;
                m->ballot = ballot;
                send(all,m);
                continue; 

                // ITERATE AGAIN

                //{round==B, ballot==0, countA(mboxA,ballot) > 2*n/3}
                recv_msg = recv();


            }

        }
           
        

    }

}else{

    //{round==A, ballot==0, ¬(recv_msg!=NULL && recv_msg->round==A)}

    if(recv_msg!=NULL && recv_msg->round==B){
        //{round==A, ballot==0, ¬(recv_msg!=NULL && recv_msg->round==A), recv_msg!=NULL, recv_msg->round==B}
        mboxB[recv_msg->ballot] = mboxB[recv_msg->ballot]  + recv_msg;
        //{round==A, ballot==0, ¬(recv_msg!=NULL && recv_msg->round==A), recv_msg!=NULL, recv_msg->round==B}
        if(round==B && countB(mboxB,ballot) >= 2*n/3){
            // CAN'T ENTER BECAUSE OF CONTEXT: round==B && round==A => not sat
        }else{
            //{round==A, ballot==0, ¬(recv_msg!=NULL && recv_msg->round==A), recv_msg!=NULL, recv_msg->round==B, ¬(round==B && countB(mboxB,ballot) > 2*n/3), |mboxB[recv_msg->ballot]|==1}

            if(timeout){
                // CAN'T ENTER BECAUSE OF CONTEXT: recv_msg!=NULL && TIMEOUT => not sat
            }else{
                // ITERATE AGAIN
            }
        }

    }else{
        //{round==A, ballot==0, ¬(recv_msg!=NULL && recv_msg->round==B)}
        if(timeout){
            //{round==A, ballot==0, ¬(recv_msg!=NULL && recv_msg->round==B), TIMEOUT}
            dispose(mboxB, mboxA);
            reset_timeout();
            ballot++;
            round = A;

            //{round==A, ballot==1, ¬(recv_msg!=NULL && recv_msg->round==B), TIMEOUT}
            m = (msg *) malloc(sizeof(msg));
            m->round = round;
            m->ballot = ballot;
            send(all,m);
            continue;

            // ITERATE AGAIN

        }
    }



}


