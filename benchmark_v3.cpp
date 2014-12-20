#include <string>
#include <set>
#include <iostream>
#include <stdexcept>
#include <memory>
#include <chrono>
#include <sstream>

#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include "generated/message/v3/message.pb.h"
#include "data.hpp"
#include "common.hpp"

using namespace protobuf_v3_benchmark;

template<typename T>
void
arena_message_construction_test(size_t iterations)
{
    std::string serialized;

    std::cout << "full message construction/destruction cycle with arena (protobuf 3 only)" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        google::protobuf::Arena arena;
        T* r1 = google::protobuf::Arena::CreateMessage<T>(&arena);
        T* r2 = google::protobuf::Arena::CreateMessage<T>(&arena);
        init_message(r1);
        r1->SerializeToString(&serialized);
        r2->ParseFromString(serialized);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();

    std::cout << "time = " << duration << " milliseconds" << std::endl << std::endl;
}

int
main(int argc, char **argv)
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc < 2) {
        std::cout << "usage: " << argv[0] << " N";
        std::cout << std::endl << std::endl;
        std::cout << "arguments: " << std::endl;
        std::cout << " N  -- number of iterations" << std::endl << std::endl;
        return EXIT_SUCCESS;
    }

    size_t iterations;

    try {
        iterations = boost::lexical_cast<size_t>(argv[1]);
    } catch (std::exception &exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        std::cerr << "First positional argument must be an integer." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "performing " << iterations << " iterations" << std::endl << std::endl;
    std::cout << "version: " << GOOGLE_PROTOBUF_VERSION << std::endl;

    try {
        message_serialization_test<Record>(iterations);
        full_message_construction_test<Record>(iterations);
        arena_message_construction_test<Record>(iterations);
    } catch (std::exception &exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        return EXIT_FAILURE;
    }

    google::protobuf::ShutdownProtobufLibrary();

    return EXIT_SUCCESS;
}
