#pragma once

namespace boshi {
    typedef struct Color {
        float r, g, b, a;

        Color() = default;

        Color(float r, float g, float b);
        Color(float r, float g, float b, float a);
    } Color;

    namespace Colors {
        const Color WHITE = Color(1.0, 1.0, 1.0);
        const Color BLACK = Color(0.0, 0.0, 0.0);
        const Color RED = Color(1.0, 0.0, 0.0);
    }
}
