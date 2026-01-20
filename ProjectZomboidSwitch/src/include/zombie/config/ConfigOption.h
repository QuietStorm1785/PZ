#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace config {

class ConfigOption {
public:
    const std::string name;

    public ConfigOption(const std::string& var1) {
      if (var1 != nullptr && !var1.empty() && !var1.contains("=")) {
         this.name = var1;
      } else {
         throw std::make_unique<IllegalArgumentException>();
      }
   }

    std::string getName() {
      return this.name;
   }

   public abstract std::string getType();

   public abstract void resetToDefault();

   public abstract void setDefaultToCurrentValue();

   public abstract void parse(std::string var1);

   public abstract std::string getValueAsString();

    std::string getValueAsLuaString() {
      return this.getValueAsString();
   }

   public abstract void setValueFromObject(Object var1);

   public abstract Object getValueAsObject();

   public abstract boolean isValidString(std::string var1);

   public abstract std::string getTooltip();
}
} // namespace config
} // namespace zombie
