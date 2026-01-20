#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeTraverser {
public:
    const T root;
   const Iterator<T> childIterator;

   TreeTraverser$PostOrderNode(T root, Iterator<T> childIterator) {
      this.root = (T)Preconditions.checkNotNull(root);
      this.childIterator = (Iterator<T>)Preconditions.checkNotNull(childIterator);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
