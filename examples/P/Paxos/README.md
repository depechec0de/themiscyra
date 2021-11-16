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
pmc POutput/netcoreapp3.1/Paxos.dll -m PImplementation.TestPaxosSyncNoFailure.Execute -i 10000

pmc POutput/netcoreapp3.1/Paxos.dll -m PImplementation.TestPaxosSyncTimeouts.Execute -i 10000
```

## Experiments ASYNC
```
pmc POutput/netcoreapp3.1/Paxos.dll -m PImplementation.TestPaxosAsyncNoFailure.Execute -i 10000

pmc POutput/netcoreapp3.1/Paxos.dll -m PImplementation.TestPaxosAsyncTimeouts.Execute -i 10000
```

# Buggy
# pmc POutput/netcoreapp3.1/Paxos.dll -m PImplementation.TestPaxosSyncTimeouts.Execute -i 1 -v --seed 2272731343 > sarasa