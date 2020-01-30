# GOR
GOR (Get Or Return) is library which provide TRY macro. This macro allows easy handling exceptional circumstances (like runtime errors).

## Basic
GOD is header only library which providing simple macro for handling exceptional circumstances without `try...cache` blocks. 

## Requirements

c++14 or higher\
gcc >= 9.1\
clang >= 6.0.0

## Building and test running
```bash
mkdir bin
cd bin
cmake ...
make
ctest -VV
```

## Example
Simple example [here](test/tests/sompleTest.cpp) 