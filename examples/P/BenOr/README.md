# BenOr in the P language

## To compile

```
pc -proj:BenOr.pproj
```

## SyncTag test

```
pmc POutput/netcoreapp3.1/BenOr.dll -m PImplementation.TestAsyncSyncTag.Execute -i 10000
```

## Experiments SYNC
```
pmc POutput/netcoreapp3.1/BenOr.dll -m PImplementation.TestSyncLogConsistencyBasic.Execute -i 10000

pmc POutput/netcoreapp3.1/BenOr.dll -m PImplementation.TestSyncLogConsistencyIntensive.Execute -i 10000
```

## Experiments ASYNC
```
pmc POutput/netcoreapp3.1/BenOr.dll -m PImplementation.TestAsyncLogConsistencyBasic.Execute -i 10000

pmc POutput/netcoreapp3.1/BenOr.dll -m PImplementation.TestAsyncLogConsistencyIntensive.Execute -i 10000
```
