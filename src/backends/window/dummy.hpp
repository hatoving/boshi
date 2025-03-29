#pragma once

#include "base.hpp"
#include <cstdint>

namespace boshi::Backends::Window {
    class Dummy : public boshi::Backends::Window::Base {
    public:
        Dummy() {}
        ~Dummy() { Destroy(); }

        void Initialize(uint32_t windowFlags) override;
        uint8_t IsInitialized() override;
        void Update() override;
        void Destroy() override;

    private:
        uint8_t isInitialized = 0;
    };
}
