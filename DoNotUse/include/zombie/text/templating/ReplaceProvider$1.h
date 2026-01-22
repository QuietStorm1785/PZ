#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace text {
namespace templating {

class ReplaceProvider {
public:
   ReplaceProvider$1(ReplaceProvider var1, std::string var2) {
      this.this$0 = var1;
      this.val$value = var2;
   }

    std::string getString() {
      return this.val$value;
   }
}
} // namespace templating
} // namespace text
} // namespace zombie
