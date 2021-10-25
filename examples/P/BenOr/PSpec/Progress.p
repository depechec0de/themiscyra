event eMonitor_Initialize: int;

spec Progress observes ConsensusRequest, eMonitor_NewLogEntry, eMonitor_Initialize {
    // keep track of the pending requests
    var pendingReqs: set[RequestId];
    var decisionCount: map[RequestId, int];
    var N: int;

    start state Init {
        on eMonitor_Initialize do (participants: int) {
            N = participants;
            goto NopendingRequests;
        }
    }

    cold state NopendingRequests {
        on ConsensusRequest goto PendingReqs with (payload: (request: RequestId, estimate: Value)){
            if(!(payload.request in decisionCount)){
                decisionCount[payload.request] = 0;
                pendingReqs += (payload.request);
            }
        }

        on eMonitor_NewLogEntry do (payload: (request: RequestId, logentry: any)) {
            decisionCount[payload.request] = decisionCount[payload.request]+1;
        }
    }

    hot state PendingReqs {
        on eMonitor_NewLogEntry do (payload: (request: RequestId, logentry: any)) {
            decisionCount[payload.request] = decisionCount[payload.request]+1;

            if(decisionCount[payload.request] == (N/2)+1){
                print(format("Request {0} reached consensus from a mayority", payload.request));
                pendingReqs -= (payload.request);
            }

            if(sizeof(pendingReqs) == 0){
                goto NopendingRequests;
            }
                
        }
        on ConsensusRequest goto PendingReqs with (payload: (request: RequestId, estimate: Value)){
            if(!(payload.request in decisionCount)){
                decisionCount[payload.request] = 0;
                pendingReqs += (payload.request);
            }
        }
    }
}