# Paxos in the P language

## To compile

```
pc -proj:Paxos.pproj
```

## SyncTag test

```
pmc POutput/netcoreapp3.1/Paxos.dll -m PImplementation.TestAsyncSyncTag.Execute -i 10000
```

## Experiments SYNC
```
pmc POutput/netcoreapp3.1/Paxos.dll -m PImplementation.TestPaxosSyncTimeouts.Execute -i 10000
```

## Experiments ASYNC
```
pmc POutput/netcoreapp3.1/Paxos.dll -m PImplementation.TestPaxosAsyncTimeouts.Execute -i 10000
```