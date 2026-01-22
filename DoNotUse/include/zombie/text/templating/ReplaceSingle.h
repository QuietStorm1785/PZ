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

class ReplaceSingle {
public:
    std::string value = "";

    public ReplaceSingle() {
   }

    public ReplaceSingle(const std::string& var1) {
      this.value = var1;
   }

    std::string getValue() {
      return this.value;
   }

    void setValue(const std::string& var1) {
      this.value = var1;
   }

    std::string getString() {
      return this.value;
   }
}
} // namespace templating
} // namespace text
} // namespace zombie
