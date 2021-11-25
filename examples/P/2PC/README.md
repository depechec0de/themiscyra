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
pmc netcoreapp3.1/TwoPhaseCommit.dll -m PImplementation.TestSyncAtomicity5nodes.Execute --timeout 10

pmc netcoreapp3.1/TwoPhaseCommit.dll -m PImplementation.TestSyncAtomicity5nodes.Execute --timeout 100

pmc netcoreapp3.1/TwoPhaseCommit.dll -m PImplementation.TestSyncAtomicity5nodes.Execute --timeout 1000

pmc netcoreapp3.1/TwoPhaseCommit.dll -m PImplementation.TestSyncAtomicity8nodes.Execute --timeout 10

pmc netcoreapp3.1/TwoPhaseCommit.dll -m PImplementation.TestSyncAtomicity8nodes.Execute --timeout 100

pmc netcoreapp3.1/TwoPhaseCommit.dll -m PImplementation.TestSyncAtomicity8nodes.Execute --timeout 1000
```

## Experiments ASYNC
```
pmc netcoreapp3.1/TwoPhaseCommit.dll -m PImplementation.TestAsyncAtomicity5nodes.Execute --timeout 10

pmc netcoreapp3.1/TwoPhaseCommit.dll -m PImplementation.TestAsyncAtomicity5nodes.Execute --timeout 100

pmc netcoreapp3.1/TwoPhaseCommit.dll -m PImplementation.TestAsyncAtomicity5nodes.Execute --timeout 1000

pmc netcoreapp3.1/TwoPhaseCommit.dll -m PImplementation.TestAsyncAtomicity8nodes.Execute --timeout 10

pmc netcoreapp3.1/TwoPhaseCommit.dll -m PImplementation.TestAsyncAtomicity8nodes.Execute --timeout 100

pmc netcoreapp3.1/TwoPhaseCommit.dll -m PImplementation.TestAsyncAtomicity8nodes.Execute --timeout 1000
```