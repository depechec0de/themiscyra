
/*
This machine creates the 2 participants, 1 coordinator, and 2 clients 
*/

machine TestDriverSync0 {
    start state Init {
        entry {
            launchSync(5, 3);
        }
    }
}

machine TestDriverSync1 {
    start state Init {
        entry {
            launchSync(8, 3);
        }
    }
}

fun launchSync(n: int, requests: int)
{
    var system : ViewStampedReplicationSync;
    var i : int;
    var participants: set[SyncReplica];
    
    i = 0;
    while (i < n) {
        participants += (new SyncReplica());
        i = i + 1;
    }
    
    system = new ViewStampedReplicationSync(participants);
    
    i = 0;
    while(i < requests){
        send system, eClientRequest, (transactionId = 100+i, command = "x = 0;");
        i = i + 1;
    }
}

machine SyncReplica {
    start state Init {
    }
}

machine TestDriverAsync0 {
    start state Init {
        entry {
            launchASync(5, 3);
        }
    }
}

machine TestDriverAsync1 {
    start state Init {
        entry {
            launchASync(8, 3);
        }
    }
}

fun launchASync(n: int, requests: int)
{
    var participants: set[Replica];
    var i : int;
    var leader : Replica;

    i = 0;
    while (i < n) {
        participants += (new Replica());
        i = i + 1;
    }

    announce eMonitor_Initialize, participants;

    leader = participants[0];
    
    i = 0;
    while (i < n) {
        send participants[i], eConfig, (participants=participants, leader=leader);
        i=i+1;
    }

    i = 0;
    while(i < requests){
        send leader, eClientRequest, (transactionId = 100+i, command = "x = 0;");
       i = i + 1;
    }
}


