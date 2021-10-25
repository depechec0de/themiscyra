
/*
This machine creates the 2 participants, 1 coordinator, and 2 clients 
*/

machine TestDriverAsync0 {
    start state Init {
        entry {
            launchASync(5, 1);
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
        send participants[i], Config, participants;
        i=i+1;
    }

    announce eMonitor_Initialize, sizeof(participants);

    //new FailureInjector((nodes = participants, nFailures = (sizeof(participants)/2)-1));

    i = 0;
    while(i < requests){
        j = 0;
        while (j < n) {
            send participants[j], ConsensusRequest, (request=100+i, estimate=choose(2));
            j=j+1;
        }
        i=i+1;
    }
}

fun launchSync(n: int, requests: int)
{
    var system : BenOrSync;
    var i : int;
    var p : machine;
    var participants: set[Participant];
    
    i = 0;
    while (i < n) {
        participants += (new Participant());
        i = i + 1;
    }    

    announce eMonitor_Initialize, sizeof(participants);
    
    system = new BenOrSync(participants);

    i = 0;
    while(i < requests){
        send system, ConsensusRequest, (request=100+i, estimate=choose(2));
        i=i+1;
    }
 
}