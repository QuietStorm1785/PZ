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
namespace base {

enum class AbstractIterator {
   READY,
   NOT_READY,
   DONE,
   FAILED;
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
