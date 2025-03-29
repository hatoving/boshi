#pragma once

#include <cstdint>
#include "base.hpp"

#ifdef BOSHIBACKEND_RND_GL
#include <GL/gl.h>

namespace boshi::Backends::Render {
    class OpenGL : public boshi::Backends::Render::Base {
        public:
            OpenGL() : isInitialized(false)  {}
            ~OpenGL() {}

            void Initialize() override;
                uint8_t IsInitialized() override;
            void Destroy() override;

            void PrepareRenderTexture(int w, int h) override;

            void BeginFrame() override;
                void Clear(Color color) override;
            void PresentFrame() override;

            void DrawRectangle(float x1, float y1, float x2, float y2, Color color) override;

            void ChangeViewport(int w, int h) override;
        private:
            uint8_t isInitialized = 0;

            GLuint screenTexture;
            GLuint screenTextureFBO;
    };
}
#endif
