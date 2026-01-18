#pragma once
#include <cmath>

namespace org { namespace lwjgl { namespace util { namespace vector {
class Vector3f {
public:
    float x{0.0f}, y{0.0f}, z{0.0f};
    Vector3f() = default;
    Vector3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};
}}}}
