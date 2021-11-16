event eMonitor_Initialize: int;

spec Progress observes ConsensusRequest, eMonitor_NewLog, eMonitor_Initialize {
    // keep track of the pending requests
    var pendingReqs: set[RequestId];
    var decisionCount: map[RequestId, set[machine]];
    var failures: int;

    start state Init {
        on eMonitor_Initialize do (failures: int) {
            // failures = failures;
            // goto NopendingRequests;
        }
    }

    // cold state NopendingRequests {
    //     on ConsensusRequest {
    //         if(!(payload.request in decisionCount)){
    //             decisionCount[payload.request] = default(set[machine]);
    //             pendingReqs += (payload.request);
    //         }
    //         goto PendingReqs;
    //     }

    //     on eMonitor_NewLog do (payload: (id: machine, request: RequestId, logentry: any)) {
    //         decisionCount[payload.request] += (payload.id);
    //     }
    // }

    // hot state PendingReqs {
    //     on eMonitor_NewLog do (payload: (id: machine, request: RequestId, logentry: any)) {
    //         decisionCount[payload.request] += (payload.id);

    //         if(sizeof(decisionCount[payload.request]) > failures){
    //             print(format("Request {0} reached consensus from a mayority", payload.request));
    //             pendingReqs -= (payload.request);
    //         }

    //         if(sizeof(pendingReqs) == 0){
    //             goto NopendingRequests;
    //         }
                
    //     }
    //     on ConsensusRequest goto PendingReqs with (payload: (request: RequestId, estimate: Value)){
    //         if(!(payload.request in decisionCount)){
    //             decisionCount[payload.request] = default(set[machine]);
    //             pendingReqs += (payload.request);
    //         }
    //     }
    // }
}