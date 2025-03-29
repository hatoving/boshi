#pragma once

#include "base.hpp"
#include <cstdint>

#ifdef BOSHIBACKEND_WND_SDL2

#include <SDL2/SDL.h>

namespace boshi::Backends::Window {
    class SDL2 : public boshi::Backends::Window::Base {
        public:
            SDL2() : window(nullptr), isInitialized(false) {}
            ~SDL2() { Destroy(); }

            void Initialize(uint32_t windowFlags) override;
            uint8_t IsInitialized() override;

            void Update() override;
            void Destroy() override;

            SDL_Window* GetWindow(); // Specific to this backend impl. only

        private:
            SDL_Window* window;
            SDL_Event event;

            #ifdef BOSHIBACKEND_RND_GL
                SDL_GLContext glContext;
            #endif

            uint8_t isInitialized = 0;
    };
}

#endif
