
#include "DiamondMatrixIterator.h"

namespace zombie {
namespace iso {

DiamondMatrixIterator::DiamondMatrixIterator(int size)
    : size(size), lineSize(1), line(0), column(0) {}

DiamondMatrixIterator& DiamondMatrixIterator::reset(int newSize) {
    size = newSize;
    lineSize = 1;
    line = 0;
    column = 0;
    return *this;
}

void DiamondMatrixIterator::reset() {
    lineSize = 1;
    line = 0;
    column = 0;
}

bool DiamondMatrixIterator::next(Vector2i& v) {
    if (lineSize == 0) {
        v.x = 0;
        v.y = 0;
        return false;
    } else if (line == 0 && column == 0) {
        v.x = 0;
        v.y = 0;
        column++;
        return true;
    } else {
        if (column < lineSize) {
            v.x++;
            v.y--;
            column++;
        } else {
            column = 1;
            line++;
            if (line < size) {
                lineSize++;
                v.x = 0;
                v.y = line;
            } else {
                lineSize--;
                v.x = line - size + 1;
                v.y = size - 1;
            }
        }
        if (lineSize == 0) {
            v.x = 0;
            v.y = 0;
            return false;
        } else {
            return true;
        }
    }
}

Vector2i DiamondMatrixIterator::i2line(int idx) const {
    int acc = 0;
    for (int i = 1; i < size + 1; ++i) {
        acc += i;
        if (idx + 1 <= acc) {
            return Vector2i(idx - acc + i, i - 1);
        }
    }
    for (int i = size + 1; i < size * 2; ++i) {
        acc += size * 2 - i;
        if (idx + 1 <= acc) {
            return Vector2i(idx - acc + size * 2 - i, i - 1);
        }
    }
    return Vector2i(0, 0); // or throw/return invalid
}

Vector2i DiamondMatrixIterator::line2coord(const Vector2i& v) const {
    if (v.y < size) {
        Vector2i res(0, v.y);
        for (int i = 0; i < v.x; ++i) {
            res.x++;
            res.y--;
        }
        return res;
    } else {
        Vector2i res(v.y - size + 1, size - 1);
        for (int i = 0; i < v.x; ++i) {
            res.x++;
            res.y--;
        }
        return res;
    }
}

} // namespace iso
} // namespace zombie
