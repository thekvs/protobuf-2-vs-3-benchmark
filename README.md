#### Benchmark comparing performance of Google's protobuf library version 2 vs. version 3.

#### Building
This is a tipical CMake project, which does not have any external dependences, i.e. all needed
protobuf libraries will be downloaded and build automatically. Note that to build this project
you need a compiler that supports C++11 features. Compilation was tested on GCC 4.8.2 and clang 3.5.

```
$ mkdir /path/to/build-root/
$ cd /path/to/build-root/
$ cmake /path/to/protobuf-v2-vs-v3 -DCMAKE_BUILD_TYPE=Release
$ make
```

#### Results
