enum FailureModel {NoFailure, Timeouts}

fun primary(phase: int, participants: set[machine]) : machine {
    return participants[modulo(phase, sizeof(participants))];
}

fun modulo(a : int, mod : int) : int{
    while(a >= mod){
        a = a-mod;
    }
    return a;
}

fun BroadCast(fm : FailureModel, ms: set[machine], ev: event, payload: any){
    if(fm == NoFailure){
        ReliableBroadCast(ms, ev, payload);
    }else{
        UnReliableBroadCast(ms, ev, payload);
    }
}

fun MaybeStartTimer(fm : FailureModel, timer: Timer)
{
    if(fm == Timeouts){
        StartTimer(timer);
    }
}

fun MaybeCancelTimer(fm : FailureModel, timer: Timer)
{
    if(fm == Timeouts){
        CancelTimer(timer);
    }
}

fun Send(fm : FailureModel, target: machine, message: event, payload: any){
    if(fm == NoFailure){
        send target, message, payload;
    }else{
        UnReliableSend(target, message, payload);
    }
}

// var threshold is the minimal size of the desired subset
fun NonDeterministicSubset(elements: set[any], threshold: int) : set[any]{
    var subsetSize : int;
    var element : any;
    var i : int;
    var subset : set[any];

    subsetSize = threshold + choose(sizeof(elements)-threshold+1);

    i = 0;
    while (i < subsetSize){
        element = choose(elements);
        elements -= (element);
        subset += (element);
        i = i+1;
    }

    assert(sizeof(subset) >= threshold);

    return subset;
}
