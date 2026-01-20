#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/common/collect/Multisets/1/1.h"
#include "javax/annotation/Nullable.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multisets {
public:
   Multisets$1(Multiset var1, Multiset var2) {
      this.val$multiset1 = var1;
      this.val$multiset2 = var2;
   }

    bool contains(@Nullable Object) {
      return this.val$multiset1.contains(element) || this.val$multiset2.contains(element);
   }

    bool isEmpty() {
      return this.val$multiset1.empty() && this.val$multiset2.empty();
   }

    int count(void* element) {
      return Math.max(this.val$multiset1.count(element), this.val$multiset2.count(element));
   }

   Set<E> createElementSet() {
      return Sets.union(this.val$multiset1.elementSet(), this.val$multiset2.elementSet());
   }

   Iterator<Entry<E>> entryIterator() {
      Iterator<? : public Entry<? : public E>> iterator1 = this.val$multiset1.entrySet().iterator();
      Iterator<? : public Entry<? : public E>> iterator2 = this.val$multiset2.entrySet().iterator();
      return std::make_shared<1>(this, iterator1, iterator2);
   }

    int distinctElements() {
      return this.elementSet().size();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
