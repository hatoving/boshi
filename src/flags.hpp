#pragma once
#include <cstdint>

namespace boshi {
    /*
     * Every flag you can use in the engine (e.g. window flags)
    */
    class Flags {
        public:
            // Window flags
            const static uint32_t WND_SHOWN = 0x00000004; /* Show the window */
            const static uint32_t WND_BORDERLESS = 0x00000010; /* Make the window borderless */
            const static uint32_t WND_RESIZABLE = 0x00000020; /* Make the window resizable */

            const static uint32_t BACKEND_WINDOW_DUMMY = 0x01; /* Dummy window backend */
            const static uint32_t BACKEND_WINDOW_SDL2 = 0x02; /* SDL2 window backend */

            const static uint32_t BACKEND_RENDER_DUMMY = 0x3; /* Dummy render backend */
            const static uint32_t BACKEND_RENDER_GL = 0x04; /* OpenGL 2.0 render backend */
    };
}
