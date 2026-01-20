#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace graph {

class ImmutableNetwork {
public:
   ImmutableNetwork$1(ImmutableNetwork var1, Graph var2) {
      this.this$0 = var1;
      this.val$asGraph = var2;
   }

   protected Graph<N> delegate() {
      return this.val$asGraph;
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
