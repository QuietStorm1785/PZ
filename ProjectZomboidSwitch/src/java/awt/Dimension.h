#pragma once

// Stub for java.awt.Dimension

namespace java {
namespace awt {

class Dimension {
public:
    int width = 0;
    int height = 0;
    Dimension() = default;
    Dimension(int w, int h) : width(w), height(h) {}
};

} // namespace awt
} // namespace java
