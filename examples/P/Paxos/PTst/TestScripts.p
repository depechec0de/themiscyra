// checks that all events are handled correctly and also the local assertions in the P machines.

test TestPaxosAsync_Timeouts[main = TestDriverPaxosAsync_Timeouts]: assert LogConsistency in { TestDriverPaxosAsync_Timeouts, Process, Timer };

test TestPaxosSeq_ArbitraryNetwork[main = TestDriverPaxosSeq_ArbitraryNetwork]: assert LogConsistency in { TestDriverPaxosSeq_ArbitraryNetwork, Participant, PaxosSeq_ArbitraryNetwork };
