# 2PC in the P language

## To compile

```
pc -proj:TwoPhaseCommit.pproj
```

## Run model checking with 1000 schedulers
```
pmc netcoreapp3.1/TwoPhaseCommit.dll -m PImplementation.TestAsyncBasic.Execute -i 10000

pmc netcoreapp3.1/TwoPhaseCommit.dll -m PImplementation.TestAsyncIntensive.Execute -i 10000

pmc netcoreapp3.1/TwoPhaseCommit.dll -m PImplementation.TestAsyncSyncTag.Execute -i 10000

```

## Experiments SYNC
```
pmc netcoreapp3.1/TwoPhaseCommit.dll -m PImplementation.TestSyncBasic.Execute -i 10000

pmc netcoreapp3.1/TwoPhaseCommit.dll -m PImplementation.TestSyncIntensive.Execute -i 10000
```

## Experiments ASYNC
```
pmc netcoreapp3.1/TwoPhaseCommit.dll -m PImplementation.TestAsyncAtomicityBasic.Execute -i 10000

pmc netcoreapp3.1/TwoPhaseCommit.dll -m PImplementation.TestAsyncAtomicityIntensive.Execute -i 10000
```