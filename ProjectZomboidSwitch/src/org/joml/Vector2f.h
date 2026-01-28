// Minimal stub for org/joml/Vector2f
#ifndef ORG_JOML_VECTOR2F_H
#define ORG_JOML_VECTOR2F_H

class Vector2f {
public:
    float x, y;

    Vector2f() : x(0.0f), y(0.0f) {}
    Vector2f(float x, float y) : x(x), y(y) {}

    Vector2f& set(float nx, float ny) { x = nx; y = ny; return *this; }
};

#endif // ORG_JOML_VECTOR2F_H
