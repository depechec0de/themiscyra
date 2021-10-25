// checks that all events are handled correctly and also the local assertions in the P machines.
test TestAsyncLogConsistencyIntensive[main = TestDriverAsync1]: assert LogConsistency, Progress in { TestDriverAsync1, Process, FailureInjector, Timer };

test TestAsyncLogConsistencyBasic[main = TestDriverAsync0]: assert LogConsistency, Progress in { TestDriverAsync0, Process, FailureInjector, Timer };

//test TestAsyncSyncTag[main = TestDriverAsync0]: assert SyncTagInvariant in { TestDriverAsync0, Process, Timer };

test TestSyncLogConsistencyBasic[main = TestDriverSync0]: assert LogConsistency in { TestDriverSync0, BenOrSync, Participant };

test TestSyncLogConsistencyIntensive[main = TestDriverSync1]: assert LogConsistency in { TestDriverSync1, BenOrSync, Participant };