#ifndef __COMMON_HPP_INCLUDED__
#define __COMMON_HPP_INCLUDED__

#include <string>

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
message_serialization_test(size_t iterations)
{
    T r1;
    std::string serialized;

    init_message(&r1);
    r1.SerializeToString(&serialized);

    // check if we can deserialize back
    T r2;
    bool ok = r2.ParseFromString(serialized);
    if (!ok /*|| r2 != r1*/) {
        throw std::logic_error("deserialization failed");
    }

    std::cout << "only message serialization cycle" << std::endl;
    std::cout << "size = " << serialized.size() << " bytes" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
        serialized.clear();
        r1.SerializeToString(&serialized);
        r2.ParseFromString(serialized);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();

    std::cout << "time = " << duration << " milliseconds" << std::endl << std::endl;
}

template<typename T>
void
full_message_construction_test(size_t iterations)
{
    std::string serialized;

    std::cout << "full message construction/destruction cycle" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; i++) {
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

    std::cout << "time = " << duration << " milliseconds" << std::endl << std::endl;
}

#endif
