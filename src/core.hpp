#ifndef BOSHI_CORE_HPP
#define BOSHI_CORE_HPP

#include <memory>
#include <cstdint>
#include <string>

#include "backends/render/all.hpp"
#include "backends/window/all.hpp"

#include "types/vector.hpp"
#include "types/color.hpp"

/*
 * A game engine I made in C++.
*/
namespace boshi {
    /*
     * Has all of the important info the engine needs to run the game.
    */
    typedef struct EngineInstance {
        std::unique_ptr<Backends::Window::Base> windowBackend;
        std::unique_ptr<Backends::Render::Base> renderBackend;

        std::string internalName;
        std::string windowTitle;

        Vector2i gameSize;
        Vector2i screenSize;

        void (*gameUpdateLoop)();
        void (*gameRenderLoop)();
        uint8_t endGame;

        EngineInstance() : windowBackend(nullptr), renderBackend(nullptr) {}
    } EngineInstance;

    /*
     * Global Engine Instance. Used by the engine itself.
    */
    extern EngineInstance GEI;

    void SetBackends(uint32_t flags);

    /*
     * Sets up the GEI and initalizes it from the given parameters. Normally this information would be given out by a base .bshi file, but this can be also used for debugging purposes.
    */
    void Create(std::string internalName, std::string windowTitle, uint32_t windowFlags, Vector2i gameSize, Vector2i screenSize, void (*gameUpdateLoop)(), void (*gameRenderLoop)());
}

#endif
