test TestAsyncNoFailure[main = TestDriverAsyncNoFailure]: assert Agreement in { TestDriverAsyncNoFailure, Process, FailureInjector, Timer };

test TestAsyncTimeouts[main = TestDriverAsyncTimeouts]: assert Agreement in { TestDriverAsyncTimeouts, Process, FailureInjector, Timer };

test TestSequentialTimeouts[main = TestDriverSequentialTimeouts]: assert Agreement in { TestDriverSequentialTimeouts, UniformVotingSequential, Participant };