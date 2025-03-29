#include "debug.hpp"

#include <cstdarg>
#include <cstdio>

using namespace boshi;

void Debug::Log(uint8_t type, const std::string& format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format.c_str(), args);
    va_end(args);

    char type_char;
    switch (type) {
        case 0x00:
            type_char = 'I';
            break;
        case 0x01:
            type_char = 'W';
            break;
        case 0x02:
            type_char = 'E';
            break;
        default:
            type_char = '?';
            break;
    }

    printf("[%c] %s\n", type_char, buffer);
}
