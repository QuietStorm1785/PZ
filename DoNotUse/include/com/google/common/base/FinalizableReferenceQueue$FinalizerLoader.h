#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace base {


class FinalizableReferenceQueue {
public:
    virtual ~FinalizableReferenceQueue() = default;
   Class<?> loadFinalizer();
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
