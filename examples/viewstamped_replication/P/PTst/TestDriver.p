
/*
This machine creates the 2 participants, 1 coordinator, and 2 clients 
*/

machine TestDriverSync0 {
    start state Init {
        entry {
            var N : int;
            var system : ViewStampedReplicationSync;
            var i : int;
            var participants: seq[Replica];
            
            N = 6;
            i = 0;
            while (i < N) {
                participants += (i, new Replica());
                i = i + 1;
            }
            
            system = new ViewStampedReplicationSync(participants);

            send system, eClientRequest, (transactionId = 100, command = "x = 0;");
            send system, eClientRequest, (transactionId = 101, command = "x = 1;");
        }
    }
}