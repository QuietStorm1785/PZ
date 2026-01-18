#pragma once

namespace java {
namespace awt {

class Dimension {
public:
 int width;
 int height;

 Dimension() : width(0), height(0) {}
 Dimension(int w, int h) : width(w), height(h) {}
 virtual ~Dimension() = default;

 bool isEmpty() const { return width <= 0 || height <= 0; }
};

} // namespace awt
} // namespace java
