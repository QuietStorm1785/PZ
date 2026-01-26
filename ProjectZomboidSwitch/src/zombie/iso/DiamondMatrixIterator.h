
#pragma once
#include "glm/vec2.hpp"
using Vector2i = glm::ivec2;


namespace zombie {
namespace iso {

class DiamondMatrixIterator {
public:
    int size;
    int lineSize;
    int line;
    int column;

    DiamondMatrixIterator(int size);
    DiamondMatrixIterator& reset(int size);
    void reset();
    bool next(Vector2i& v);
    Vector2i i2line(int idx) const;
    Vector2i line2coord(const Vector2i& v) const;
};

} // namespace iso
} // namespace zombie
