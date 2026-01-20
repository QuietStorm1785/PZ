#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Optional/1/1.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace base {


class Optional {
public:
   Optional$1(Iterable var1) {
      this.val$optionals = var1;
   }

   public Iterator<T> iterator() {
      return std::make_shared<1>(this);
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
