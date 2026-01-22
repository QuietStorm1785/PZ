#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"

namespace com {
namespace google {
namespace common {
namespace base {


class PatternCompiler {
public:
    virtual ~PatternCompiler() = default;
    CommonPattern compile(const std::string& var1);
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
