#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/DebugLog.h"

namespace zombie {
namespace config {


class BooleanConfigOption : public ConfigOption {
public:
    bool value;
    bool defaultValue;

    public BooleanConfigOption(const std::string& var1, bool var2) {
      super(var1);
      this.value = var2;
      this.defaultValue = var2;
   }

    std::string getType() {
      return "boolean";
   }

    void resetToDefault() {
      this.setValue(this.defaultValue);
   }

    void setDefaultToCurrentValue() {
      this.defaultValue = this.value;
   }

    void parse(const std::string& var1) {
      if (this.isValidString(var1)) {
         this.setValue(var1.equalsIgnoreCase("true") || var1.equalsIgnoreCase("1"));
      } else {
         DebugLog.log("ERROR BooleanConfigOption.parse() \"" + this.name + "\" string=" + var1 + "\"");
      }
   }

    std::string getValueAsString() {
      return std::string.valueOf(this.value);
   }

    void setValueFromObject(void* var1) {
      if (dynamic_cast<bool*>(var1) != nullptr) {
         this.setValue((bool)var1);
      } else if (dynamic_cast<double*>(var1) != nullptr) {
         this.setValue((double)var1 != 0.0);
      } else if (dynamic_cast<std*>(var1) != nullptr::string) {
         this.parse((std::string)var1);
      }
   }

    void* getValueAsObject() {
      return this.value;
   }

    bool isValidString(const std::string& var1) {
      return var1 != nullptr && (var1.equalsIgnoreCase("true") || var1.equalsIgnoreCase("false") || var1.equalsIgnoreCase("1") || var1.equalsIgnoreCase("0"));
   }

    bool getValue() {
      return this.value;
   }

    void setValue(bool var1) {
      this.value = var1;
   }

    bool getDefaultValue() {
      return this.defaultValue;
   }

    std::string getTooltip() {
      return std::string.valueOf(this.value);
   }
}
} // namespace config
} // namespace zombie
