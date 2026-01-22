#pragma once
#include <stack>
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

class AbstractFuture {
public:
   AbstractFuture$Failure$1(std::string x0) {
      super(x0);
   }

   public /* synchronized - TODO: add std::mutex */ Throwable fillInStackTrace() {
    return this;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
