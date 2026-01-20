#pragma once
#include <cstdint>

namespace com {
namespace sixlegs {
namespace png {

struct Integers {
    // Return an int value (boxing is not needed in C++ codebase).
    static inline int valueOf(int v) { return v; }
};

} // namespace png
} // namespace sixlegs
} // namespace com
