#include <string>
#include <iostream>
#include <chrono>

#include "generated/message/v2/message.pb.h"

#include "data.hpp"
#include "common.hpp"

void
run_all_benchmarks(long iterations, long tests)
{
    using namespace protobuf_v2_benchmark;

    message_serialization_test<Record>(iterations, tests);
    full_message_construction_test<Record>(iterations, tests);
}
