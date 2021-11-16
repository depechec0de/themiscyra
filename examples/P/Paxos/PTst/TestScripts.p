// checks that all events are handled correctly and also the local assertions in the P machines.

test TestPaxosAsyncNoFailure[main = PaxosAsyncNoFailure]: assert LogConsistency in { PaxosAsyncNoFailure, Process, FailureInjector, Timer };

test TestPaxosAsyncTimeouts[main = PaxosAsyncTimeouts]: assert LogConsistency in { PaxosAsyncTimeouts, Process, FailureInjector, Timer };

test TestPaxosSyncNoFailure[main = PaxosSyncNoFailure]: assert LogConsistency in { PaxosSyncNoFailure, Participant, PaxosSync };

test TestPaxosSyncTimeouts[main = PaxosSyncTimeouts]: assert LogConsistency in { PaxosSyncTimeouts, Participant, PaxosSync };