#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace config {

class StringConfigOption : public ConfigOption {
public:
    std::string value;
    std::string defaultValue;
    int maxLength;

    public StringConfigOption(const std::string& var1, const std::string& var2, int var3) {
      super(var1);
      if (var2 == nullptr) {
         var2 = "";
      }

      this.value = var2;
      this.defaultValue = var2;
      this.maxLength = var3;
   }

    std::string getType() {
      return "string";
   }

    void resetToDefault() {
      this.value = this.defaultValue;
   }

    void setDefaultToCurrentValue() {
      this.defaultValue = this.value;
   }

    void parse(const std::string& var1) {
      this.setValueFromObject(var1);
   }

    std::string getValueAsString() {
      return this.value;
   }

    std::string getValueAsLuaString() {
      return std::string.format("\"%s\"", this.value.replace("\\", "\\\\").replace("\"", "\\\""));
   }

    void setValueFromObject(void* var1) {
      if (var1 == nullptr) {
         this.value = "";
      } else if (dynamic_cast<std*>(var1) != nullptr::string) {
         this.value = (std::string)var1;
      } else {
         this.value = var1;
      }
   }

    void* getValueAsObject() {
      return this.value;
   }

    bool isValidString(const std::string& var1) {
    return true;
   }

    void setValue(const std::string& var1) {
      if (var1 == nullptr) {
         var1 = "";
      }

      if (this.maxLength > 0 && var1.length() > this.maxLength) {
         var1 = var1.substr(0, this.maxLength);
      }

      this.value = var1;
   }

    std::string getValue() {
      return this.value;
   }

    std::string getDefaultValue() {
      return this.defaultValue;
   }

    std::string getTooltip() {
      return this.value;
   }
}
} // namespace config
} // namespace zombie
