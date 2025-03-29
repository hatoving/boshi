#include "core.hpp"
#include "debug.hpp"
#include "flags.hpp"

#include <cassert>
#include <cstddef>
#include <cstdint>

#include <cstdlib>
#include <memory>
boshi::EngineInstance boshi::GEI;

void Destroy() {
    boshi::Debug::Log(0x00, "Destroying engine...");

    if (boshi::GEI.windowBackend->IsInitialized()) {
        boshi::GEI.windowBackend->Destroy();
    }
}

void Loop() {
    while(!boshi::GEI.endGame) {
        boshi::GEI.windowBackend->Update();

            boshi::GEI.gameUpdateLoop();

            boshi::GEI.renderBackend->BeginFrame();
                boshi::GEI.gameRenderLoop();
            boshi::GEI.renderBackend->PresentFrame();

        //boshi::GEI.windowBackend->SwapWindow();
    }
}

void boshi::SetBackends(uint32_t flags) {
    if (flags & Flags::BACKEND_WINDOW_SDL2) {
        #ifdef BOSHIBACKEND_WND_SDL2
            GEI.windowBackend = std::make_unique<Backends::Window::SDL2>();
        #else
            Debug::Log(0x02, "Backends::Window::SDL2 is either not compiled or not supported in this version of boshi");
        #endif
    }
    else if (flags & Flags::BACKEND_WINDOW_DUMMY || !GEI.windowBackend) {
        GEI.windowBackend = std::make_unique<Backends::Window::Dummy>();
    }
    assert(GEI.windowBackend);

    if (flags & Flags::BACKEND_RENDER_GL) {
        #ifdef BOSHIBACKEND_RND_GL
            GEI.renderBackend = std::make_unique<Backends::Render::OpenGL>();
        #else
            Debug::Log(0x02, "Backends::Render::OpenGL is either not compiled or not supported in this version of boshi");
        #endif
    }
    if ((flags & Flags::BACKEND_RENDER_GL) == 0 || !GEI.renderBackend) {
        GEI.renderBackend = std::make_unique<Backends::Render::Dummy>();
        Debug::Log(0x00, "Falling back to Dummy render backend...");
    }
    assert(GEI.renderBackend);
}

void boshi::Create (
    std::string internalName,
    std::string windowTitle,
    uint32_t windowFlags,
    Vector2i gameSize,
    Vector2i screenSize,
    void (*gameUpdateLoop)(),
    void (*gameRenderLoop)()
) {
    if (internalName.length() < 4) {
        Debug::Log(0x02, "internalName MUST be at least four characters long.");
        return;
    }
    Debug::Log(0x00, "Creating instance [%s]...", internalName.c_str());
    GEI.internalName = internalName;

    if (windowTitle.length() > 0) {
        GEI.windowTitle = windowTitle;
    } else if (windowTitle.empty() || windowTitle == "" || windowTitle.length() < 1) {
        GEI.windowTitle = std::string("boshi (v0.1) ~ ") + internalName;
    }

    GEI.gameSize = gameSize;
    GEI.screenSize = screenSize;

    /*
     * I'm gonna be doing a lot of asserts for stuff that need to have guraanteed behaviour,
     * simply because of the fact that the engine is supposed to be robust and well-taken
     * care of. It should go along without any major errors whatsoever in the core of it all.
    */

    uint32_t extraWindowFlags = 0;
    #if defined(BOSHIBACKEND_WND_SDL2) && defined(BOSHIBACKEND_RND_GL)
        if (dynamic_cast<Backends::Window::SDL2*>(GEI.windowBackend.get()) != nullptr &&
            dynamic_cast<Backends::Render::OpenGL*>(GEI.renderBackend.get()) != nullptr
        ) {
            extraWindowFlags |= SDL_WINDOW_OPENGL;
        }
    #endif

    GEI.windowBackend->Initialize(windowFlags | extraWindowFlags);
    extraWindowFlags = 1;
    GEI.renderBackend->Initialize();

    assert(gameUpdateLoop != NULL);
    assert(gameRenderLoop != NULL);

    GEI.gameUpdateLoop = gameUpdateLoop;
    GEI.gameRenderLoop = gameRenderLoop;

    GEI.endGame = 0;

    Debug::Log(0x00, "Starting game (update %p, render %p)...", GEI.gameUpdateLoop, GEI.gameRenderLoop);
    Loop();

    Destroy();
}
