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


class IntegerConfigOption : public ConfigOption {
public:
    int value;
    int defaultValue;
    int min;
    int max;

    public IntegerConfigOption(const std::string& var1, int var2, int var3, int var4) {
      super(var1);
      if (var4 >= var2 && var4 <= var3) {
         this.value = var4;
         this.defaultValue = var4;
         this.min = var2;
         this.max = var3;
      } else {
         throw std::make_unique<IllegalArgumentException>();
      }
   }

    std::string getType() {
      return "integer";
   }

    void resetToDefault() {
      this.setValue(this.defaultValue);
   }

    double getMin() {
      return this.min;
   }

    double getMax() {
      return this.max;
   }

    void setDefaultToCurrentValue() {
      this.defaultValue = this.value;
   }

    void parse(const std::string& var1) {
      try {
    double var2 = double.parseDouble(var1);
         this.setValue((int)var2);
      } catch (NumberFormatException var4) {
         DebugLog.log("ERROR IntegerConfigOption.parse() \"" + this.name + "\" string=\"" + var1 + "\"");
      }
   }

    std::string getValueAsString() {
      return std::string.valueOf(this.value);
   }

    void setValueFromObject(void* var1) {
      if (dynamic_cast<double*>(var1) != nullptr) {
         this.setValue(((double)var1).intValue());
      } else if (dynamic_cast<std*>(var1) != nullptr::string) {
         this.parse((std::string)var1);
      }
   }

    void* getValueAsObject() {
      return (double)this.value;
   }

    bool isValidString(const std::string& var1) {
      try {
    int var2 = int.parseInt(var1);
         return var2 >= this.min && var2 <= this.max;
      } catch (NumberFormatException var3) {
    return false;
      }
   }

    void setValue(int var1) {
      if (var1 < this.min) {
         DebugLog.log("ERROR: IntegerConfigOption.setValue() \"" + this.name + "\" " + var1 + " is less than min=" + this.min);
      } else if (var1 > this.max) {
         DebugLog.log("ERROR: IntegerConfigOption.setValue() \"" + this.name + "\" " + var1 + " is greater than max=" + this.max);
      } else {
         this.value = var1;
      }
   }

    int getValue() {
      return this.value;
   }

    int getDefaultValue() {
      return this.defaultValue;
   }

    std::string getTooltip() {
      return std::string.valueOf(this.value);
   }
}
} // namespace config
} // namespace zombie
