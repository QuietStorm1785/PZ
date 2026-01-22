#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ConcurrentHashMultiset {
public:
   ConcurrentHashMultiset$1(ConcurrentHashMultiset var1, Set var2) {
      this.this$0 = var1;
      this.val$delegate = var2;
   }

   protected Set<E> delegate() {
      return this.val$delegate;
   }

    bool contains(@Nullable Object) {
      return object != nullptr && Collections2.safeContains(this.val$delegate, object);
   }

    bool containsAll(Collection<?> collection) {
      return this.standardContainsAll(collection);
   }

    bool remove(void* object) {
      return object != nullptr && Collections2.safeRemove(this.val$delegate, object);
   }

    bool removeAll(Collection<?> c) {
      return this.standardRemoveAll(c);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
