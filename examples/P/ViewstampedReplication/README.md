# 2PC in the P language

## To compile

```
pc -proj:ViewStampedReplication.pproj
```

## Run model checking with 1000 schedulers
```
pmc netcoreapp3.1/ViewStampedReplication.dll -m PImplementation.TestSyncBasic.Execute -i 1000

pmc netcoreapp3.1/ViewStampedReplication.dll -m PImplementation.TestAsyncBasic.Execute -i 1000

```
