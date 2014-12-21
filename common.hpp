#ifndef __COMMON_HPP_INCLUDED__
#define __COMMON_HPP_INCLUDED__

#include <string>
#include <climits>

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

int
str2int(const char* str, long& value)
{
    long n;
    char* end;

    if (str == NULL || *str == 0x0) {
        return -1;
    }

    n = strtol(str, &end, 10);

    if ((n == LONG_MIN || n == LONG_MAX) && errno == ERANGE) {
        std::cerr << "Error: number " << str << " out of range for a long int type" << std::endl;
        return -1;
    }

    if (end == str) {
        std::cerr << "Error: can't convert string " << str << " to a long int value" << std::endl;
        return -1;
    }

    if (*end != '\0') {
        std::cerr << "Error: trailing garbage at the end of " << str << std::endl;
        return -1;
    }

    value = n;

    return 0;
}

#endif
