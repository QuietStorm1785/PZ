#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multiset/Entry.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ConcurrentHashMultiset {
public:
   private ConcurrentHashMultiset$EntrySet(ConcurrentHashMultiset var1) {
      super(var1);
      this.this$0 = var1;
   }

   ConcurrentHashMultiset<E> multiset() {
      return this.this$0;
   }

   public Object[] toArray() {
      return this.snapshot().toArray();
   }

   public <T> T[] toArray(T[] array) {
      return (T[])this.snapshot().toArray(array);
   }

   private List<Entry<E>> snapshot() {
      List<Entry<E>> list = Lists.newArrayListWithExpectedSize(this.size());
      Iterators.addAll(list, this.iterator());
    return list;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
