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

class Ticker {
public:
    long read() {
      return Platform.systemNanoTime();
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
