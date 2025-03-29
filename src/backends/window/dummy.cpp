#include "dummy.hpp"

#include "../../core.hpp"
#include "../../debug.hpp"

#include <cassert>
#include <cstdint>

namespace boshi::Backends::Window {
    void Dummy::Destroy() {
        isInitialized = 0;
    }

    void Dummy::Initialize(uint32_t windowFlags) {
        isInitialized = 1;
    }

    uint8_t Dummy::IsInitialized() {
        return isInitialized;
    }

    void Dummy::Update() {
    }
}
