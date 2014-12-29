#### Benchmark comparing performance of Google's protobuf library version 2 vs. version 3.

#### Building
This is a tipical CMake project, which does not have any external dependences, i.e. all needed
protobuf libraries will be downloaded and build automatically. To build this project you need a
compiler that supports C++11 features, compilation was tested on GCC 4.8.2 and clang 3.5.

```
$ mkdir /path/to/build-root/
$ cd /path/to/build-root/
$ cmake /path/to/protobuf-v2-vs-v3 -DCMAKE_BUILD_TYPE=Release
$ make
```

#### Libraries used

#### Results

Here is results we've got when running tests on typical desktop Core i7 computer:

##### Message serialization/deserialization only

| protobuf's version | result (ms) |
| ------------------ | ----------- |
|          2         |   1304      |
|          3         |   1321      |

##### Full message construction/destruction

| protobuf's version | result (ms) |
| ------------------ | ----------- |
|          2         |   2588      |
|          3         |   3059      |
|  3 (with arena)    |   2618      |


##### Raw benchmarks' output

```
$ ./benchmark-v3 50000 50
version: 3000000
only serialization/deserialization cycle: 1321 milliseconds
full construction/destruction cycle: 3059 milliseconds
full construction/destruction cycle with arena (protobuf 3 only): 2618 milliseconds
```

```
$ ./benchmark-v2 50000 50
version: 2006001
only serialization/deserialization cycle: 1304 milliseconds
full construction/destruction cycle: 2588 milliseconds
```
