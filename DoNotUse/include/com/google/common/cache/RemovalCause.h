#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"

namespace com {
namespace google {
namespace common {
namespace cache {


enum class RemovalCause {
   EXPLICIT,
   REPLACED,
   COLLECTED,
   EXPIRED,
   SIZE;

    private RemovalCause() {
   }

   abstract boolean wasEvicted();
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
