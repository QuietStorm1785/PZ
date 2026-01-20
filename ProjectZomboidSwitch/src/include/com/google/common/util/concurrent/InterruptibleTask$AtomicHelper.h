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
namespace util {
namespace concurrent {

class InterruptibleTask {
public:
   private InterruptibleTask$AtomicHelper() {
   }

   abstract boolean compareAndSetRunner(InterruptibleTask var1, Thread var2, Thread var3);
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
