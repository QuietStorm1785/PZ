#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace cache {

enum class RemovalCause {
    bool wasEvicted() {
    return false;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
