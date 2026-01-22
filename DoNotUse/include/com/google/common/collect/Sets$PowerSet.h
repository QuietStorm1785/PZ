#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Sets/PowerSet/1.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Sets {
public:
   const ImmutableMap<E, int> inputSet;

   Sets$PowerSet(Set<E> input) {
      this.inputSet = Maps.indexMap(input);
      Preconditions.checkArgument(this.inputSet.size() <= 30, "Too many elements to create power set: %s > 30", this.inputSet.size());
   }

    int size() {
      return 1 << this.inputSet.size();
   }

    bool isEmpty() {
    return false;
   }

   public Iterator<Set<E>> iterator() {
      return std::make_shared<1>(this, this.size());
   }

    bool contains(@Nullable Object) {
      if (dynamic_cast<Set*>(obj) != nullptr) {
         Set<?> set = (Set<?>)obj;
         return this.inputSet.keySet().containsAll(set);
      } else {
    return false;
      }
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<Sets*>(obj) != nullptr$PowerSet) {
         Sets$PowerSet<?> that = (Sets$PowerSet<?>)obj;
         return this.inputSet == that.inputSet);
      } else {
         return super == obj);
      }
   }

    int hashCode() {
      return this.inputSet.keySet().hashCode() << this.inputSet.size() - 1;
   }

    std::string toString() {
      return "powerSet(" + this.inputSet + ")";
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
