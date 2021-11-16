# LeaderElection in the P language

## To compile

```
pc -proj:LeaderElection.pproj
```

## SyncTag test

```
pmc POutput/netcoreapp3.1/LeaderElection.dll -m PImplementation.TestAsyncSyncTag.Execute -i 10000
```

## Experiments SYNC
```
pmc POutput/netcoreapp3.1/LeaderElection.dll -m PImplementation.TestSyncLogConsistencyBasic.Execute -i 10000

pmc POutput/netcoreapp3.1/LeaderElection.dll -m PImplementation.TestSyncLogConsistencyIntensive.Execute -i 10000
```

## Experiments ASYNC
```
pmc POutput/netcoreapp3.1/LeaderElection.dll -m PImplementation.TestAsyncBasicAtomicity.Execute -i 10000

pmc POutput/netcoreapp3.1/LeaderElection.dll -m PImplementation.TestAsyncIntensiveAtomicity.Execute -i 10000
```
