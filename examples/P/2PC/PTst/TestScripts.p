// checks that all events are handled correctly and also the local assertions in the P machines.
test TestAsyncSyncTag[main = TestDriverAsync5nodes]: assert SyncTagInvariant in { TestDriverAsync5nodes, Primary, Backup };

// Experiments ASYNC

test TestAsyncAtomicity5nodes[main = TestDriverAsync5nodes]: assert AtomicityInvariant in { TestDriverAsync5nodes, Primary, Backup };

test TestAsyncAtomicity8nodes[main = TestDriverAsync8nodes]: assert AtomicityInvariant in { TestDriverAsync8nodes, Primary, Backup };

// Experiments SEQ

test TestSyncAtomicity5nodes[main = TestDriverSync5nodes]: assert AtomicityInvariant in { TestDriverSync5nodes, TwoPhaseSync, Participant };

test TestSyncAtomicity8nodes[main = TestDriverSync8nodes]: assert AtomicityInvariant in { TestDriverSync8nodes, TwoPhaseSync, Participant };