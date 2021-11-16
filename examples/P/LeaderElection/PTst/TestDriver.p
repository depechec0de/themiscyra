
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
    var participants: set[Process];
    var i, j : int;

    i = 0;
    while (i < n) {
        participants += (new Process());
        i = i + 1;
    }

    i = 0;
    while (i < n) {
        send participants[i], eConfig, participants;
        i=i+1;
    }

    i = 0;
    while(i < requests){
        j = 0;
        while (j < n) {
            send participants[j], LeaderRequest, 100+i;
            j=j+1;
        }
        i=i+1;
    }
}

fun launchSync(n: int, requests: int)
{
    var system : LeaderElectionSync;
    var i : int;
    var participants: set[Participant];
    
    i = 0;
    while (i < n) {
        participants += (new Participant());
        i = i + 1;
    }
    
    system = new LeaderElectionSync(participants);

    i = 0;
    while(i < requests){
        send system, LeaderRequest, 100+i;
        i=i+1;
    }
 
}