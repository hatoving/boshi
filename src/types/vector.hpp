#pragma once

namespace boshi {
    typedef struct Vector2i {
        int x, y;

        Vector2i() = default;
        Vector2i(int x, int y);

        Vector2i Zero();
    } Vector2i;

    typedef struct Vector3f {
        float x, y, z;

        Vector3f() = default;
        Vector3f(float x, float y, float z);

        Vector3f Zero();
    } Vector3f;

    typedef struct Vector3i {
        int x, y, z;

        Vector3i() = default;
        Vector3i(int x, int y, int z);

        Vector3i Zero();
    } Vector3i;
}
