# UniformVoting in the P language

## To compile

```
pc -proj:UniformVoting.pproj
```

## Experiments ASYNC
```
pmc POutput/netcoreapp3.1/UniformVoting.dll -m PImplementation.TestAsyncTimeouts.Execute -i 10000

pmc POutput/netcoreapp3.1/UniformVoting.dll -m PImplementation.TestAsyncNoFailure.Execute -i 10000
```

## Experiments SYNC
```
pmc POutput/netcoreapp3.1/UniformVoting.dll -m PImplementation.TestSequentialTimeouts.Execute -i 10000
```