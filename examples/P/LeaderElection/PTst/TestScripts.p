// checks that all events are handled correctly and also the local assertions in the P machines.
test TestAsyncBasic[main = TestDriverAsync0]: { TestDriverAsync0, Process, Timer };

test TestAsyncIntensive[main = TestDriverAsync1]: { TestDriverAsync1, Process, Timer };

test TestAsyncIntensiveAtomicity[main = TestDriverAsync1]: assert LogConsistencyInvariant in { TestDriverAsync1, Process, Timer };

test TestAsyncBasicAtomicity[main = TestDriverAsync0]: assert LogConsistencyInvariant in { TestDriverAsync0, Process, Timer };

//test TestAsyncSyncTag[main = TestDriverAsync0]: assert SyncTagInvariant in { TestDriverAsync0, Process, Timer };

test TestSyncLogConsistencyBasic[main = TestDriverSync0]: assert LogConsistencyInvariant in { TestDriverSync0, LeaderElectionSync, Participant };

test TestSyncLogConsistencyIntensive[main = TestDriverSync1]: assert LogConsistencyInvariant in { TestDriverSync1, LeaderElectionSync, Participant };