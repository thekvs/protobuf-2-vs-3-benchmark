#include <iostream>
#include <stdexcept>

#include <google/protobuf/stubs/common.h>

#include "common.hpp"

void run_all_benchmarks(long iterations);

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

    long iterations;

    try {
        int rc = str2int(argv[1], iterations);
        if (rc != 0) {
            return EXIT_FAILURE;
        }
    } catch (std::exception &exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        std::cerr << "First positional argument must be an integer." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "version: " << GOOGLE_PROTOBUF_VERSION << std::endl;

    try {
        run_all_benchmarks(iterations);
    } catch (std::exception &exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        return EXIT_FAILURE;
    }

    google::protobuf::ShutdownProtobufLibrary();

    return EXIT_SUCCESS;
}
