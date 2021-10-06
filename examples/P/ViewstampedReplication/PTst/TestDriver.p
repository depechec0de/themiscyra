
/*
This machine creates the 2 participants, 1 coordinator, and 2 clients 
*/

machine TestDriverSync0 {
    start state Init {
        entry {
            var N : int;
            var system : ViewStampedReplicationSync;
            var i : int;
            var participants: set[SyncReplica];
            
            N = 6;
            i = 0;
            while (i < N) {
                participants += (new SyncReplica());
                i = i + 1;
            }
            
            system = new ViewStampedReplicationSync(participants);

            send system, eClientRequest, (transactionId = 100, command = "x = 0;");
            send system, eClientRequest, (transactionId = 101, command = "x = 1;");
        }
    }
}

machine SyncReplica {
    start state Init {
    }
}

machine TestDriverAsync0 {
    start state Init {
        entry {
            var N : int;
            var participants: set[Replica];
            var i : int;
            var leader : Replica;

            N = 5;
            i = 0;
            while (i < N) {
                participants += (new Replica());
                i = i + 1;
            }

            leader = participants[0];
            
            i = 0;
            while (i < N) {
                send participants[i], eConfig, (participants=participants, leader=leader);
                i=i+1;
            }

            i = 0;
            while (i < N) {
                send participants[i], eClientRequest, (transactionId = 100, command = "x = 0;");
                i=i+1;
            }

            i = 0;
            while (i < N) {
                send participants[i], eClientRequest, (transactionId = 101, command = "x = 1;");
                i=i+1;
            }
            
        }
    }
}