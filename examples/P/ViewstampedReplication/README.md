# Viewstamped Replication in the P language

## To compile

```
pc -proj:ViewStampedReplication.pproj
```

## Run model checking with 1000 schedulers
```
pmc netcoreapp3.1/ViewStampedReplication.dll -m PImplementation.TestSyncBasic.Execute -i 10000

pmc netcoreapp3.1/ViewStampedReplication.dll -m PImplementation.TestSyncIntensive.Execute -i 10000

pmc netcoreapp3.1/ViewStampedReplication.dll -m PImplementation.TestAsyncBasic.Execute -i 10000

pmc netcoreapp3.1/ViewStampedReplication.dll -m PImplementation.TestAsyncIntensive.Execute -i 10000

pmc netcoreapp3.1/ViewStampedReplication.dll -m PImplementation.TestAsyncSyncTag.Execute -i 10000

pmc netcoreapp3.1/ViewStampedReplication.dll -m PImplementation.TestAsyncLogConsistency.Execute -i 10000
```
