project(benchmark)
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

include(FindThreads)
include(CheckTypeSize)
include(CheckIncludeFile)
include(CheckCXXCompilerFlag)
include(ExternalProject)

CHECK_CXX_COMPILER_FLAG("-std=c++11" CXX11)
if (NOT CXX11)
    message(FATAL_ERROR "C++ compiler doesn't support C++11")
endif()

include_directories(${benchmark_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

set(protobuf_v2_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/protobuf/v2)
ExternalProject_Add(
    protobuf_v2
    PREFIX ${protobuf_v2_PREFIX}
    URL "https://github.com/google/protobuf/releases/download/v2.6.1/protobuf-2.6.1.tar.bz2"
    URL_MD5 "11aaac2d704eef8efd1867a807865d85"
    CONFIGURE_COMMAND CXX=${CMAKE_CXX_COMPILER} CC=${CMAKE_C_COMPILER} ${protobuf_v2_PREFIX}/src/protobuf_v2/configure --prefix=${protobuf_v2_PREFIX} --enable-shared=no
    BUILD_COMMAND $(MAKE)
    INSTALL_COMMAND $(MAKE) install
    BUILD_IN_SOURCE 1
)
include_directories(SYSTEM ${protobuf_v2_PREFIX}/include)
set(PROTOBUF_V2_LIBRARIES ${protobuf_v2_PREFIX}/lib/libprotobuf.a)
set(PROTOBUF_V2_GENERATOR ${protobuf_v2_PREFIX}/bin/protoc)

set(LINKLIBS
    ${PROTOBUF_V2_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)

add_custom_command(
    DEPENDS ${benchmark_SOURCE_DIR}/message/v2/message.proto
    COMMAND ${PROTOBUF_V2_GENERATOR}
    ARGS -I${benchmark_SOURCE_DIR} --cpp_out=${benchmark_SOURCE_DIR}/generated/ ${benchmark_SOURCE_DIR}/message/v2/message.proto
    OUTPUT  "${benchmark_SOURCE_DIR}/generated/message/v2/message.pb.cc"
    COMMENT "Executing Protobuf compiler"
)
set_source_files_properties(
    ${benchmark_SOURCE_DIR}/generated/message/v2/message.pb.cc
    ${benchmark_SOURCE_DIR}/generated/message/v2/message.pb.h
    PROPERTIES GENERATED TRUE
)
set(PROTOBUF_V2_SERIALIZATION_SOURCES ${benchmark_SOURCE_DIR}/generated/message/v2/message.pb.cc)

include_directories(${benchmark_SOURCE_DIR}/generated)

add_executable(benchmark-v2
    ${benchmark_SOURCE_DIR}/benchmark_v2.cpp
    ${PROTOBUF_V2_SERIALIZATION_SOURCES}
)
add_dependencies(benchmark-v2 protobuf_v2)
target_link_libraries(benchmark-v2 ${PROTOBUF_V2_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(benchmark-v2 PROPERTIES COMPILE_FLAGS "-std=c++11")
