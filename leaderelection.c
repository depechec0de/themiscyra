pid = INPUT;
leader = 0;

ballot = 0;
round = NB;

while(true){
    
    recv_msg = recv();

    if(round==NB && leader(ballot)==pid){
        //@assert round == NB && ballot%N==pid
        msg = new Message;   
        //@assert round == NB                   
        msg->ballot = ballot;                 
        //@assert round == NB
        msg->round = NB;                       
        //@assert round == NB
        send(*,msg);                           
        round = AB;                           
        continue;
    }

    if(round==NB && recv_msg->round==NB && recv_msg->ballot==ballot && follower(ballot)==pid){
        round = AB;                             
        msg = new Message;                      
        msg->ballot = ballot;                   
        msg->round = AB;                        
        send(*,msg);                           
        continue;
    }
    
    if(round==AB && recv_msg->round==AB && recv_msg->ballot==ballot){
        mbox = mbox + msg;   
        if (msg ==3) round =NB;               
        continue;
    }
    
    if(round==AB && countAB(mbox,ballot)>n/2){
        leader=ballot%n;                   
        ballot++;                              
        round=NB;   
        //@assert round == NB                          
        dispose(mbox);          
        //@assert round == NB              
        continue;
    }

    if(timeout){
        //ballot++;
        round = NB;
        //@assert round == NB
        dispose(mbox);
        //@assert round == NB
        continue;
    }

}
