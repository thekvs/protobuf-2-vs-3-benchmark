#include <string>
#include <iostream>
#include <chrono>

#include "generated/message/v3/message.pb.h"

#include "data.hpp"
#include "common.hpp"

template<typename T>
void
arena_message_construction_test(long iterations)
{
    std::string serialized;

    std::cout << "full construction/destruction cycle with arena (protobuf 3 only): ";
    auto start = std::chrono::high_resolution_clock::now();
    for (long i = 0; i < iterations; i++) {
        google::protobuf::Arena arena;
        T* r1 = google::protobuf::Arena::CreateMessage<T>(&arena);
        T* r2 = google::protobuf::Arena::CreateMessage<T>(&arena);
        init_message(r1);
        r1->SerializeToString(&serialized);
        r2->ParseFromString(serialized);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();

    std::cout << duration << " milliseconds" << std::endl;
}

void
run_all_benchmarks(long iterations)
{
    using namespace protobuf_v3_benchmark;

    message_serialization_test<Record>(iterations);
    full_message_construction_test<Record>(iterations);
    arena_message_construction_test<Record>(iterations);
}
