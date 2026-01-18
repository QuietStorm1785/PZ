#pragma once
#include <cmath>

namespace org { namespace lwjgl { namespace util { namespace vector {
class Vector4f {
public:
    float x{0.0f}, y{0.0f}, z{0.0f}, w{0.0f};
    Vector4f() = default;
    Vector4f(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
};
}}}}
