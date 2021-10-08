
/*
This machine creates the 2 participants, 1 coordinator, and 2 clients 
*/

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

machine Participant{
    start state Init {}
}

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

fun launchASync(n: int, requests: int)
{
    var prim : Primary;
    var backups: seq[Backup];
    var i : int;

    i = 0;
    while (i < n-1) {
        backups += (i, new Backup());
        i = i + 1;
    }
    prim = new Primary(backups);

    i = 0;
    while(i < requests){
        send prim, eClientRequest, (transactionId = 100+i, command = "x = 0;");
        i=i+1;
    }
}

fun launchSync(n: int, requests: int)
{
    var system : TwoPhaseSync;
    var i : int;
    var participants: seq[Participant];
    
    i = 0;
    while (i < n) {
        participants += (i, new Participant());
        i = i + 1;
    }
    
    system = new TwoPhaseSync(participants);

    i = 0;
    while(i < requests){
        send system, eClientRequest, (transactionId = 100+i, command = "x = 0;");
        i=i+1;
    }
 
}