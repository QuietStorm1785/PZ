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


class FinalizableReference {
public:
    virtual ~FinalizableReference() = default;
    void finalizeReferent();
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
