test TestSyncBasic[main = TestDriverSync0]: { TestDriverSync0, ViewStampedReplicationSync, SyncReplica };

test TestSyncIntensive[main = TestDriverSync1]: { TestDriverSync1, ViewStampedReplicationSync, SyncReplica };

test TestAsyncBasic[main = TestDriverAsync0]: { TestDriverAsync0, Replica, Timer };

test TestAsyncIntensive[main = TestDriverAsync1]: { TestDriverAsync1, Replica, Timer };

test TestAsyncSyncTag[main = TestDriverAsync0]: assert SyncTagInvariant in { TestDriverAsync0, Replica, Timer };

test TestAsyncLogConsistencyBasic[main = TestDriverAsync0]: assert LeadersConsistencyInvariant in { TestDriverAsync0, Replica, Timer };

test TestAsyncLogConsistencyIntensive[main = TestDriverAsync1]: assert LeadersConsistencyInvariant in { TestDriverAsync1, Replica, Timer };

test TestSyncLogConsistencyBasic[main = TestDriverSync0]: assert LeadersConsistencyInvariant in { TestDriverSync0, ViewStampedReplicationSync, SyncReplica };

test TestSyncLogConsistencyIntensive[main = TestDriverSync1]: assert LeadersConsistencyInvariant in { TestDriverSync1, ViewStampedReplicationSync, SyncReplica };