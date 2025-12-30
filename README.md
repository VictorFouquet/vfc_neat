# C Lightweight NEAT Framework

Depends on vfc_utils, clone recursively, else will be fetched at build.

## Build

### Build and run

#### Build Debug

Creates `build/libneat.a` static library for debug

```shell
cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug

cmake --build build/debug
```

#### Build Release

Creates `build/libneat.a` static library for release

```shell
cmake -S . -B build/release -DCMAKE_BUILD_TYPE=Release

cmake --build build/release
```

#### Run Test

```shell
cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug -DNEAT_BUILD_TESTS=ON

cmake --build build/debug

./build/debug/neat/test/neat_test
```