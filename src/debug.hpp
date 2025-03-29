#pragma once

#include <cstdint>
#include <string>

namespace boshi {
    /*
     * Debug functions (e.g. logging)
    */
    class Debug {
        public:
            /*
             * Log something to the console output (a newline gets appended at the end of "format"). Types are the following:
             * * 0x00 - Info
             * * 0x01 - Warning
             * * 0x02 - Error
             *
             * Anything else and the engine will put a question mark instead of the type initial (e.g. I for info.)
            */
            static void Log(uint8_t type, const std::string& format, ...);
    };
}
