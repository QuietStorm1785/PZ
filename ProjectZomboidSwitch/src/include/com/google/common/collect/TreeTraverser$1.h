#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeTraverser {
public:
   TreeTraverser$1(Function var1) {
      this.val$nodeToChildrenFunction = var1;
   }

   public Iterable<T> children(T root) {
      return (Iterable<T>)this.val$nodeToChildrenFunction.apply(root);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
