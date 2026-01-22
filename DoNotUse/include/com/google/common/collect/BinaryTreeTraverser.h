#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Optional.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/BinaryTreeTraverser/1.h"
#include "com/google/common/collect/BinaryTreeTraverser/2.h"
#include "com/google/common/collect/BinaryTreeTraverser/PostOrderIterator.h"
#include "com/google/common/collect/BinaryTreeTraverser/PreOrderIterator.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class BinaryTreeTraverser {
public:
   public abstract Optional<T> leftChild(T var1);

   public abstract Optional<T> rightChild(T var1);

   public const Iterable<T> children(T root) {
      Preconditions.checkNotNull(root);
      return std::make_shared<1>(this, root);
   }

   UnmodifiableIterator<T> preOrderIterator(T root) {
      return std::make_shared<PreOrderIterator>(this, root);
   }

   UnmodifiableIterator<T> postOrderIterator(T root) {
      return std::make_shared<PostOrderIterator>(this, root);
   }

   public const FluentIterable<T> inOrderTraversal(T root) {
      Preconditions.checkNotNull(root);
      return std::make_shared<2>(this, root);
   }

   private static <T> void pushIfPresent(std::deque<T> stack, Optional<T> node) {
      if (node.isPresent()) {
         stack.addLast((T)node.get());
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
