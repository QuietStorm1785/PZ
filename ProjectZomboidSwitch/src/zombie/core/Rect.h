#pragma once

namespace zombie {
namespace core {

struct Rect {
    float x, y, w, h;
    Rect() : x(0), y(0), w(0), h(0) {}
    Rect(float x_, float y_, float w_, float h_) : x(x_), y(y_), w(w_), h(h_) {}
};

} // namespace core
} // namespace zombie
