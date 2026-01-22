#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Converter/1/1.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace base {


class Converter {
public:
   Converter$1(Converter var1, Iterable var2) {
      this.this$0 = var1;
      this.val$fromIterable = var2;
   }

   public Iterator<B> iterator() {
      return std::make_shared<1>(this);
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
