#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <iterator>

namespace org {
namespace uncommons {
namespace maths {
namespace combinatorics {


class PermutationGenerator {
public:
   PermutationGenerator$1(PermutationGenerator var1) {
      this.this$0 = var1;
   }

    bool hasNext() {
      return this.this$0.hasMore();
   }

   public List<T> next() {
      return this.this$0.nextPermutationAsList();
   }

    void remove() {
      throw UnsupportedOperationException("Iterator does not support removal.");
   }
}
} // namespace combinatorics
} // namespace maths
} // namespace uncommons
} // namespace org
