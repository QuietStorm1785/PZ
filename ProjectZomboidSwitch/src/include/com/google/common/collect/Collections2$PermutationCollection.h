#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Collections2/PermutationIterator.h"
#include "com/google/common/math/IntMath.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Collections2 {
public:
   const ImmutableList<E> inputList;

   Collections2$PermutationCollection(ImmutableList<E> input) {
      this.inputList = input;
   }

    int size() {
      return IntMath.factorial(this.inputList.size());
   }

    bool isEmpty() {
    return false;
   }

   public Iterator<List<E>> iterator() {
      return std::make_shared<PermutationIterator>(this.inputList);
   }

    bool contains(@Nullable Object) {
      if (dynamic_cast<List*>(obj) != nullptr) {
         List<?> list = (List<?>)obj;
         return Collections2.access$100(this.inputList, list);
      } else {
    return false;
      }
   }

    std::string toString() {
      return "permutations(" + this.inputList + ")";
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
