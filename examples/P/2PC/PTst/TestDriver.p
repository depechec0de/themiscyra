
/*
This machine creates the 2 participants, 1 coordinator, and 2 clients 
*/

machine TestDriverAsync5nodes {
    start state Init {
        entry {
            launchASync(5, 10);
        }
    }
}

machine TestDriverAsync8nodes {
    start state Init {
        entry {
            launchASync(8, 10);
        }
    }
}

machine Participant{
    start state Init {}
}

machine TestDriverSync5nodes {
    start state Init {
        entry {
            launchSync(5, 10);
        }
    }
}

machine TestDriverSync8nodes {
    start state Init {
        entry {
            launchSync(8, 10);
        }
    }
}

fun launchASync(n: int, requests: int)
{
    var prim : Primary;
    var backups: seq[Backup];
    var i : int;

    i = 0;
    while (i < n) {
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
    // n+1 Include Primary
    while (i < n+1) {
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