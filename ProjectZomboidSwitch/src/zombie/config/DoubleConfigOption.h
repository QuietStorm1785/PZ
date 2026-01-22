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


class DoubleConfigOption : public ConfigOption {
public:
    double value;
    double defaultValue;
    double min;
    double max;

    public DoubleConfigOption(const std::string& var1, double var2, double var4, double var6) {
      super(var1);
      if (!(var6 < var2) && !(var6 > var4)) {
         this.value = var6;
         this.defaultValue = var6;
         this.min = var2;
         this.max = var4;
      } else {
         throw std::make_unique<IllegalArgumentException>();
      }
   }

    std::string getType() {
      return "double";
   }

    double getMin() {
      return this.min;
   }

    double getMax() {
      return this.max;
   }

    void resetToDefault() {
      this.setValue(this.defaultValue);
   }

    void setDefaultToCurrentValue() {
      this.defaultValue = this.value;
   }

    void parse(const std::string& var1) {
      try {
    double var2 = double.parseDouble(var1);
         this.setValue(var2);
      } catch (NumberFormatException var4) {
         DebugLog.log("ERROR DoubleConfigOption.parse() \"" + this.name + "\" string=" + var1 + "\"");
      }
   }

    std::string getValueAsString() {
      return std::string.valueOf(this.value);
   }

    void setValueFromObject(void* var1) {
      if (dynamic_cast<double*>(var1) != nullptr) {
         this.setValue((double)var1);
      } else if (dynamic_cast<std*>(var1) != nullptr::string) {
         this.parse((std::string)var1);
      }
   }

    void* getValueAsObject() {
      return this.value;
   }

    bool isValidString(const std::string& var1) {
      try {
    double var2 = double.parseDouble(var1);
         return var2 >= this.min && var2 <= this.max;
      } catch (NumberFormatException var4) {
    return false;
      }
   }

    void setValue(double var1) {
      if (var1 < this.min) {
         DebugLog.log("ERROR: DoubleConfigOption.setValue() \"" + this.name + "\" " + var1 + " is less than min=" + this.min);
      } else if (var1 > this.max) {
         DebugLog.log("ERROR: DoubleConfigOption.setValue() \"" + this.name + "\" " + var1 + " is greater than max=" + this.max);
      } else {
         this.value = var1;
      }
   }

    double getValue() {
      return this.value;
   }

    double getDefaultValue() {
      return this.defaultValue;
   }

    std::string getTooltip() {
      return std::string.valueOf(this.value);
   }
}
} // namespace config
} // namespace zombie
