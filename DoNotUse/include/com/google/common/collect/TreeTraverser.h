#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/TreeTraverser/1.h"
#include "com/google/common/collect/TreeTraverser/2.h"
#include "com/google/common/collect/TreeTraverser/3.h"
#include "com/google/common/collect/TreeTraverser/4.h"
#include "com/google/common/collect/TreeTraverser/PostOrderIterator.h"
#include "com/google/common/collect/TreeTraverser/PreOrderIterator.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeTraverser {
public:
   public static <T> TreeTraverser<T> using(Function<T, ? : public Iterable<T>> nodeToChildrenFunction) {
      Preconditions.checkNotNull(nodeToChildrenFunction);
      return std::make_shared<1>(nodeToChildrenFunction);
   }

   public abstract Iterable<T> children(T var1);

   public const FluentIterable<T> preOrderTraversal(T root) {
      Preconditions.checkNotNull(root);
      return std::make_shared<2>(this, root);
   }

   UnmodifiableIterator<T> preOrderIterator(T root) {
      return std::make_shared<PreOrderIterator>(this, root);
   }

   public const FluentIterable<T> postOrderTraversal(T root) {
      Preconditions.checkNotNull(root);
      return std::make_shared<3>(this, root);
   }

   UnmodifiableIterator<T> postOrderIterator(T root) {
      return std::make_shared<PostOrderIterator>(this, root);
   }

   public const FluentIterable<T> breadthFirstTraversal(T root) {
      Preconditions.checkNotNull(root);
      return std::make_shared<4>(this, root);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
