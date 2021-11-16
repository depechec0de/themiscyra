
/*
This machine creates the 2 participants, 1 coordinator, and 2 clients 
*/

machine TestDriverAsync0 {
    start state Init {
        entry {
            launchASync((n=3, quorum=2, failures=1));
        }
    }
}

machine TestDriverAsync1 {
    start state Init {
        entry {
            launchASync((n=8, quorum=5, failures=3));
        }
    }
}

machine Participant{
    start state Init {}
}

machine TestDriverSync0 {
    start state Init {
        entry {
            launchSync((n=3, quorum=2, failures=1));
        }
    }
}

machine TestDriverSync1 {
    start state Init {
        entry {
            launchSync((n=8, quorum=5, failures=3));
        }
    }
}

fun launchASync(config: (n: int, quorum: int, failures: int))
{
    var participants: set[Process];
    var i: int;

    assert(config.quorum >= config.n/2);
    assert(config.failures < config.quorum);

    i = 0;
    while (i < config.n) {
        participants += (new Process());
        i = i + 1;
    }

    i = 0;
    while (i < config.n) {
        send participants[i], Config, (peers=participants, quorum=config.quorum);
        i=i+1;
    }

    announce eMonitor_Initialize, config.failures;

    new FailureInjector((nodes = participants, nFailures = config.failures));

    i = 0;
    while (i < config.n) {
        send participants[i], ConsensusRequest, (request=100, estimate=choose(2));
        i=i+1;
    }

}

fun launchSync(config: (n: int, quorum: int, failures: int))
{
    var system : BenOrSync;
    var i : int;
    var p : machine;
    var participants: set[Participant];

    assert(config.quorum >= config.n/2);
    assert(config.failures < config.quorum);
    
    i = 0;
    while (i < config.n) {
        participants += (new Participant());
        i = i + 1;
    }    

    announce eMonitor_Initialize, config.failures;
    
    system = new BenOrSync((peers=participants, quorum=config.quorum, failures=config.failures));

    send system, ConsensusRequest, (request=100, estimate=-1);
 
}