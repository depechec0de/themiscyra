event eMonitor_NewLog: (id: machine, newlog: seq[any]);

spec LogConsistency observes eMonitor_NewLog
{
    var globalLog: Log;

    start state Init {
        on eMonitor_NewLog do (payload: (id: machine, newlog: seq[any]))
        {
            assert sequenceIsPrefix(globalLog, payload.newlog), format("Log {0} is not a prefix of {1}", globalLog, payload.newlog);

            globalLog = payload.newlog;
        }
    }

    fun sequenceIsPrefix(prefix: seq[any], longerseq: seq[any]) : bool {
        var i: int;

        assert(sizeof(longerseq) >= sizeof(prefix)), format("seq {0} is not longer than {1}", longerseq, prefix);

        i = 0;

        while(i < sizeof(prefix)){
            if (prefix[i] != longerseq[i]){
                return false;
            }
            i=i+1;
        }

        return true;
    }
}