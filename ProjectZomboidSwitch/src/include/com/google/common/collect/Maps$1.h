#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   Maps$1(Iterator x0, Function var2) {
      super(x0);
      this.val$function = var2;
   }

   Entry<K, V> transform(K key) {
      return Maps.immutableEntry(key, this.val$function.apply(key));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
