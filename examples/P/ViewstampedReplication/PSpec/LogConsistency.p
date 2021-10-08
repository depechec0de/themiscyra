event eMonitor_Initialize: set[machine];
event eMonitor_NewLogEntry: (phase: Phase, logentry: any);

spec LogConsistencyInvariant observes eMonitor_Initialize, eMonitor_NewLogEntry
{
    
    var log: Log;

    start state Init {

        on eMonitor_Initialize goto WaitForEvents with (participants: set[machine]) {

        }
    }

    state WaitForEvents {

        on eMonitor_NewLogEntry do (payload: (phase: Phase, logentry: any))
        {
            var loge : any;
            loge = payload.logentry;

            if(loge != null){
                if(payload.phase in log){
                    assert (loge == log[payload.phase]), format("Log entry breaks atomicity {0} vs {1}", loge, log[payload.phase]);
                }else{
                    log[payload.phase] = loge;
                }
            }
            
        }
 
    }
}