#ifndef __COMMON_HPP_INCLUDED__
#define __COMMON_HPP_INCLUDED__

#include <string>
#include <climits>
#include <iostream>
#include <chrono>

#include "data.hpp"

template<typename T>
void
init_message(T* r)
{
    for (size_t i = 0; i < kIntegers.size(); i++) {
        r->add_i(kIntegers[i]);
    }

    for (size_t i = 0; i < kStringsCount; i++) {
        r->add_s(kStringValue);
    }

    for (size_t i = 0; i < kSmallIntegers.size(); i++) {
        r->add_small_i(kSmallIntegers[i]);
    }

    for (size_t i = 0; i < kDoubles1.size(); i++) {
        r->add_d1(kDoubles1[i]);
    }

    for (size_t i = 0; i < kDoubles2.size(); i++) {
        r->add_d2(kDoubles2[i]);
    }
}

template<typename T>
void
message_serialization_test(long iterations)
{
    T r1, r2;
    std::string serialized;

    init_message(&r1);
    r1.SerializeToString(&serialized);

    std::cout << "only serialization/deserialization cycle: ";

    auto start = std::chrono::high_resolution_clock::now();
    for (long i = 0; i < iterations; i++) {
        serialized.clear();
        r1.SerializeToString(&serialized);
        r2.ParseFromString(serialized);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();

    std::cout << duration << " milliseconds" << std::endl;
}

template<typename T>
void
full_message_construction_test(long iterations)
{
    std::string serialized;

    std::cout << "full construction/destruction cycle: ";
    auto start = std::chrono::high_resolution_clock::now();
    for (long i = 0; i < iterations; i++) {
        T* r1 = new T();
        T* r2 = new T();
        init_message(r1);
        r1->SerializeToString(&serialized);
        r2->ParseFromString(serialized);
        delete r1;
        delete r2;
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();

    std::cout << duration << " milliseconds" << std::endl;
}

int str2int(const char* str, long& value);

#endif
