#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace hash {


class Funnel {
public:
    virtual ~Funnel() = default;
    void funnel(T var1, PrimitiveSink var2);
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
