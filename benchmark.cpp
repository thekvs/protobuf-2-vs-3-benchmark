#include <iostream>
#include <stdexcept>

#include <google/protobuf/stubs/common.h>

#include "common.hpp"

void run_all_benchmarks(long iterations, long tests);

int
main(int argc, char **argv)
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc < 3) {
        std::cout << "usage: " << argv[0] << " N M";
        std::cout << std::endl << std::endl;
        std::cout << "arguments: " << std::endl;
        std::cout << " N  -- number of iterations" << std::endl;
        std::cout << " M  -- number of tests to run" << std::endl;
        std::cout << std::endl;

        return EXIT_SUCCESS;
    }

    long iterations;
    long tests;

    try {
        int rc = str2int(argv[1], iterations);
        if (rc != 0) {
            return EXIT_FAILURE;
        }
        rc = str2int(argv[2], tests);
        if (rc != 0) {
            return EXIT_FAILURE;
        }
    } catch (std::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        std::cerr << "First positional argument must be an integer." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "version: " << GOOGLE_PROTOBUF_VERSION << std::endl;

    try {
        run_all_benchmarks(iterations, tests);
    } catch (std::exception &exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        return EXIT_FAILURE;
    }

    google::protobuf::ShutdownProtobufLibrary();

    return EXIT_SUCCESS;
}
