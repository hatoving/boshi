#pragma once

#include <cstdint>
#include <string>

#include "../../types/color.hpp"

//#define BACKEND_RND_GL 1
#define BOSHIBACKEND_RND_GL 1

namespace boshi::Backends::Render {
    class Base {
        public:
            virtual ~Base() = default;

            virtual void Initialize() = 0;
                virtual uint8_t IsInitialized() = 0;
            virtual void Destroy() = 0;

            virtual void PrepareRenderTexture(int w, int h) = 0;

            virtual void BeginFrame() = 0;
                virtual void Clear(Color color) = 0;
            virtual void PresentFrame() = 0;

            virtual void DrawRectangle(float x1, float y1, float x2, float y2, Color color) = 0;

            virtual void ChangeViewport(int w, int h) = 0;
    };
}
