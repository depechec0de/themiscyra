
/*
This machine creates the 2 participants, 1 coordinator, and 2 clients 
*/

machine PaxosAsyncNoFailure {
    start state Init {
        entry {
            launchASync((n=3, quorum=2, f=0, fm=NoFailure));
        }
    }
}

machine PaxosAsyncTimeouts {
    start state Init {
        entry {
            launchASync((n=3, quorum=2, f=0, fm=Timeouts));
        }
    }
}

machine Participant{
    start state Init {}
}

machine PaxosSyncNoFailure {
    start state Init {
        entry {
            launchSync((n=3, quorum=2, f=0, fm=NoFailure));
        }
    }
}

machine PaxosSyncTimeouts {
    start state Init {
        entry {
            launchSync((n=3, quorum=2, f=0, fm=Timeouts));
        }
    }
}

fun launchASync(config: (n: int, quorum: int, f: int, fm: FailureModel))
{
    var participants: set[Process];
    var i, j: int;

    assert(config.quorum >= config.n/2);
    assert(config.f < config.quorum);

    i = 0;
    while (i < config.n) {
        participants += (new Process());
        i = i + 1;
    }

    i = 0;
    while (i < config.n) {
        send participants[i], Config, (peers=participants, quorum=config.quorum, failurem=config.fm);
        i=i+1;
    }

    announce eMonitor_Initialize, config.f;

    if(config.f > 0){
        new FailureInjector((nodes = participants, nFailures = config.f));
    }    

    j = 0;
    while (j < 3) {
        i = 0;
        while (i < config.n) {
            send participants[i], ConsensusRequest;
            i=i+1;
        }
        j=j+1;
    }

}

fun launchSync(config: (n: int, quorum: int, f: int, fm: FailureModel))
{
    var system : PaxosSync;
    var i, j : int;
    var p : machine;
    var participants: set[Participant];

    assert(config.quorum >= config.n/2);
    assert(config.f < config.quorum);
    
    i = 0;
    while (i < config.n) {
        participants += (new Participant());
        i = i + 1;
    }    

    announce eMonitor_Initialize, config.f;
    
    system = new PaxosSync((peers=participants, quorum=config.quorum, failurem=config.fm));

    i = 0;
    while (i < 3) {
        send system, ConsensusRequest;
        i=i+1;
    }
 
}