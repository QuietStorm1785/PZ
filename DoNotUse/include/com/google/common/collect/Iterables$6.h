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


class Iterables {
public:
   Iterables$6(Iterable var1, Function var2) {
      this.val$fromIterable = var1;
      this.val$function = var2;
   }

   public Iterator<T> iterator() {
      return Iterators.transform(this.val$fromIterable.iterator(), this.val$function);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
