#pragma once

namespace java {
namespace awt {

class Point {
public:
 int x;
 int y;

 Point() : x(0), y(0) {}
 Point(int px, int py) : x(px), y(py) {}
 virtual ~Point() = default;

 bool isEmpty() const { return x == 0 && y == 0; }
};

} // namespace awt
} // namespace java
