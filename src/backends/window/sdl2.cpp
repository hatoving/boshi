#include "../../core.hpp"
#include "../../debug.hpp"

#include <cassert>
#include <cstdint>

#ifdef BOSHIBACKEND_WND_SDL2
#include "sdl2.hpp"

namespace boshi::Backends::Window {
    void SDL2::Destroy() {
        if (!isInitialized) return;

        if (window != nullptr) {
            SDL_DestroyWindow(window);
            window = nullptr;
        }
        #ifdef BOSHIBACKEND_RND_GL
            if (dynamic_cast<Backends::Render::OpenGL*>(GEI.renderBackend.get()) != nullptr) {
                SDL_GL_DeleteContext(glContext);
            }
        #endif
        SDL_Quit();

        isInitialized = false;
    }

    void SDL2::Initialize(uint32_t windowFlags) {
        Debug::Log(0x00, "Using SDL2 as the window backend...");
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

        window = SDL_CreateWindow(
            GEI.windowTitle.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            GEI.screenSize.x,
            GEI.screenSize.y,
            windowFlags
        );
        if (window == NULL) Debug::Log(0x02, "Couldn't create window! %s", SDL_GetError());
        assert(window != NULL);

        #ifdef BOSHIBACKEND_RND_GL
            if (dynamic_cast<Backends::Render::OpenGL*>(GEI.renderBackend.get()) != nullptr) {
                SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
                SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );

                glContext = SDL_GL_CreateContext(window);
                SDL_GL_MakeCurrent(window, glContext);
            }
        #endif

        isInitialized = 1;
    }

    uint8_t SDL2::IsInitialized() {
        return isInitialized;
    }

    void SDL2::Update() {
        if (!isInitialized) return;

        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                boshi::GEI.endGame = true;
            }
            if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    GEI.screenSize.x = event.window.data1;
                    GEI.screenSize.y = event.window.data2;
                }
            }
        }
    }

    SDL_Window* SDL2::GetWindow() {
        return window;
    }
}

#endif
