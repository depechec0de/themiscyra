event eMonitor_NewLogEntry: (id: machine, request: RequestId, logentry: any);

spec LogConsistency observes eMonitor_NewLogEntry
{
    var log: Log;

    start state Init {
        on eMonitor_NewLogEntry do (payload: (id: machine, request: RequestId, logentry: any))
        {
            var loge : any;

            loge = payload.logentry;

            if(loge != null){
                if(payload.request in log){
                    assert (loge == log[payload.request]), format("Log entry breaks atomicity {0} vs {1}", loge, log[payload.request]);
                }else{
                    log[payload.request] = loge;
                }
            }
            
        }
    }
}