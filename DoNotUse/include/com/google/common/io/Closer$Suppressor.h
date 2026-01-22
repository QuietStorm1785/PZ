#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class Closer {
public:
    virtual ~Closer() = default;
    void suppress(Closeable var1, std::exception var2, std::exception var3);
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
