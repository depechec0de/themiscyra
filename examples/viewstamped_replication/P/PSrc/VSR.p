event eMessage : Message;

type Command = int;
type Phase = int;
type Mbox = map[Phase, map[Round, seq[Message]]];
type Timestamp = (phase: Phase, round: Round);
type Message = (phase: Phase, from: machine, dst: machine, payload: data);
type ClientRequest = (transactionId: int, command: string);

event configMessage: Replica;
event eClientRequest: ClientRequest;

enum Round { STARTVIEWCHANGE, DOVIEWCHANGE, STARTVIEW }

machine Replica
{
    start state Init 
    {

    }

}