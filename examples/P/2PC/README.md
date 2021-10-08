# 2PC in the P language

## To compile

```
pc -proj:TwoPhaseCommit.pproj
```

## Run model checking with 1000 schedulers
```
pmc netcoreapp3.1/TwoPhaseCommit.dll -m PImplementation.TestAsyncBasic.Execute -i 10000

pmc netcoreapp3.1/TwoPhaseCommit.dll -m PImplementation.TestAsyncIntensive.Execute -i 10000

pmc netcoreapp3.1/TwoPhaseCommit.dll -m PImplementation.TestAsyncAtomicity.Execute -i 10000

pmc netcoreapp3.1/TwoPhaseCommit.dll -m PImplementation.TestAsyncSyncTag.Execute -i 10000

pmc netcoreapp3.1/TwoPhaseCommit.dll -m PImplementation.TestSyncBasic.Execute -i 10000

pmc netcoreapp3.1/TwoPhaseCommit.dll -m PImplementation.TestSyncIntensive.Execute -i 10000

```
