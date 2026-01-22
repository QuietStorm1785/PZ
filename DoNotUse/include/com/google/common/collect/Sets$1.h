#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableSet/Builder.h"
#include "com/google/common/collect/Sets/SetView.h"
#include "com/google/common/math/IntMath.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Sets {
public:
   Sets$1(Set var1, Set var2, Set var3) {
      super(nullptr);
      this.val$set1 = var1;
      this.val$set2minus1 = var2;
      this.val$set2 = var3;
   }

    int size() {
      return IntMath.saturatedAdd(this.val$set1.size(), this.val$set2minus1.size());
   }

    bool isEmpty() {
      return this.val$set1.empty() && this.val$set2.empty();
   }

   public UnmodifiableIterator<E> iterator() {
      return Iterators.unmodifiableIterator(Iterators.concat(this.val$set1.iterator(), this.val$set2minus1.iterator()));
   }

    bool contains(void* object) {
      return this.val$set1.contains(object) || this.val$set2.contains(object);
   }

   public <S : public Set<E>> S copyInto(S set) {
      set.addAll(this.val$set1);
      set.addAll(this.val$set2);
    return set;
   }

   public ImmutableSet<E> immutableCopy() {
      return std::make_unique<Builder>().addAll(this.val$set1).addAll(this.val$set2).build();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
