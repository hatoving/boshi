#pragma once

#include <cstdint>
#include <string>

#define BOSHIBACKEND_WND_SDL2 1

namespace boshi::Backends::Window {
    class Base {
        public:
            virtual ~Base() = default;

            virtual void Initialize(uint32_t windowFlags) = 0;
            virtual uint8_t IsInitialized() = 0;
            virtual void Update() = 0;
            virtual void Destroy() = 0;
        private:

    };
}
