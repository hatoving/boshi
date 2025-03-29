#pragma once
#include "base.hpp"

namespace boshi::Backends::Render {
    class Dummy : public boshi::Backends::Render::Base {
        public:
            Dummy();
            ~Dummy();

            void Initialize() override;
                uint8_t IsInitialized() override;
            void Destroy() override {}

            void PrepareRenderTexture(int w, int h) override {}

            void BeginFrame() override;
                void Clear(Color color) override;
            void PresentFrame() override;

            void ChangeViewport(int w, int h) override {}
    };
}
