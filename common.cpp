#include "common.hpp"

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
