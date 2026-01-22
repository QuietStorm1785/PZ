#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace config {

class EnumConfigOption : public IntegerConfigOption {
public:
    public EnumConfigOption(const std::string& var1, int var2, int var3) {
      super(var1, 1, var2, var3);
   }

    std::string getType() {
      return "enum";
   }

    int getNumValues() {
      return this.max;
   }
}
} // namespace config
} // namespace zombie
