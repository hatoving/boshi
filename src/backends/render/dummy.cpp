#include "dummy.hpp"

namespace boshi::Backends::Render {
    Dummy::Dummy() {}
    Dummy::~Dummy() {}

    void Dummy::Initialize() {}
    uint8_t Dummy::IsInitialized() { return 1; }

    void Dummy::BeginFrame() {}
    void Dummy::Clear(Color color) {}
    void Dummy::PresentFrame() {}
}
