#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Iterators {
public:
   Iterators$7(Iterator x0, Function var2) {
      super(x0);
      this.val$function = var2;
   }

    T transform(F from) {
      return (T)this.val$function.apply(from);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
