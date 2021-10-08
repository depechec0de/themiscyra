test TestSyncBasic[main = TestDriverSync0]: { TestDriverSync0, ViewStampedReplicationSync, SyncReplica };

test TestSyncIntensive[main = TestDriverSync1]: { TestDriverSync1, ViewStampedReplicationSync, SyncReplica };

test TestAsyncBasic[main = TestDriverAsync0]: { TestDriverAsync0, Replica, Timer };

test TestAsyncIntensive[main = TestDriverAsync1]: { TestDriverAsync1, Replica, Timer };

test TestAsyncSyncTag[main = TestDriverAsync0]: assert SyncTagInvariant in { TestDriverAsync0, Replica, Timer };

test TestAsyncLogConsistency[main = TestDriverAsync0]: assert LogConsistencyInvariant in { TestDriverAsync0, Replica, Timer };