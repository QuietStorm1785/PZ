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
namespace collect {


class Sets {
public:
   Sets$CartesianSet$1(ImmutableList var1) {
      this.val$axes = var1;
   }

    int size() {
      return this.val$axes.size();
   }

   public List<E> get(int index) {
      return ((ImmutableSet)this.val$axes.get(index)).asList();
   }

    bool isPartialView() {
    return true;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
