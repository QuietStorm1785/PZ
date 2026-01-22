#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class LineProcessor {
public:
    virtual ~LineProcessor() = default;
    bool processLine(const std::string& var1);

    T getResult();
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
