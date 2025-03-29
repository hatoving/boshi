#include "vector.hpp"

namespace boshi {
    Vector2i::Vector2i(int x, int y) {
        this->x = x;
        this ->y = y;
    }

    Vector2i Vector2i::Zero() {
        return Vector2i(0, 0);
    }

    Vector3i::Vector3i(int x, int y, int z) {
        this->x = x;
        this ->y = y;
        this->z = z;
    }

    Vector3f::Vector3f(float x, float y, float z) {
        this->x = x;
        this ->y = y;
        this->z = z;
    }

    Vector3i Vector3i::Zero() {
        return Vector3i(0, 0, 0);
    }

    Vector3f Vector3f::Zero() {
        return Vector3f(0.0F, 0.0F, 0.0F);
    }
}
