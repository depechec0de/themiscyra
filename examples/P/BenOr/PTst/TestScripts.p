// checks that all events are handled correctly and also the local assertions in the P machines.
test TestAsyncLogConsistencyIntensive[main = TestDriverAsync1]: assert Agreement in { TestDriverAsync1, Process, FailureInjector, Timer };

test TestAsyncLogConsistencyBasic[main = TestDriverAsync0]: assert Agreement in { TestDriverAsync0, Process, FailureInjector, Timer };

test TestSyncLogConsistencyBasic[main = TestDriverSync0]: assert Agreement in { TestDriverSync0, BenOrSync, Participant };

test TestSyncLogConsistencyIntensive[main = TestDriverSync1]: assert Agreement in { TestDriverSync1, BenOrSync, Participant };