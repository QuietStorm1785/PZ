#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace base {


class Throwables {
public:
   Throwables$1(Throwable var1) {
      this.val$t = var1;
   }

    StackTraceElement get(int n) {
      return (StackTraceElement)Throwables.access$200(Throwables.access$000(), Throwables.access$100(), new Object[]{this.val$t, n});
   }

    int size() {
      return (int)Throwables.access$200(Throwables.access$300(), Throwables.access$100(), new Object[]{this.val$t});
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
