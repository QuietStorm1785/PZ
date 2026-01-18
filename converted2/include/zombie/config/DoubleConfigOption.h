#pragma once
#include "zombie/debug/DebugLog.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace config {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class DoubleConfigOption : public ConfigOption {
public:
  double value;
  double defaultValue;
  double min;
  double max;

public
  DoubleConfigOption(const std::string &name, double _min, double _max,
                     double _defaultValue) {
    super(name);
    if (!(_defaultValue < _min) && !(_defaultValue > _max)) {
      this.value = _defaultValue;
      this.defaultValue = _defaultValue;
      this.min = _min;
      this.max = _max;
    } else {
      throw std::make_unique<IllegalArgumentException>();
    }
  }

  std::string getType() { return "double"; }

  double getMin() { return this.min; }

  double getMax() { return this.max; }

  void resetToDefault() { this.setValue(this.defaultValue); }

  void setDefaultToCurrentValue() { this.defaultValue = this.value; }

  void parse(const std::string &s) {
    try {
      double double0 = Double.parseDouble(s);
      this.setValue(double0);
    } catch (NumberFormatException numberFormatException) {
      DebugLog.log("ERROR DoubleConfigOption.parse() \"" + this.name +
                   "\" string=" + s + "\"");
    }
  }

  std::string getValueAsString() { return String.valueOf(this.value); }

  void setValueFromObject(void *o) {
    if (o instanceof Double) {
      this.setValue((Double)o);
    } else if (o instanceof String) {
      this.parse((String)o);
    }
  }

  void *getValueAsObject() { return this.value; }

  bool isValidString(const std::string &s) {
    try {
      double double0 = Double.parseDouble(s);
      return double0 >= this.min && double0 <= this.max;
    } catch (NumberFormatException numberFormatException) {
      return false;
    }
  }

  void setValue(double _value) {
    if (_value < this.min) {
      DebugLog.log("ERROR: DoubleConfigOption.setValue() \"" + this.name +
                   "\" " + _value + " is less than min=" + this.min);
    } else if (_value > this.max) {
      DebugLog.log("ERROR: DoubleConfigOption.setValue() \"" + this.name +
                   "\" " + _value + " is greater than max=" + this.max);
    } else {
      this.value = _value;
    }
  }

  double getValue() { return this.value; }

  double getDefaultValue() { return this.defaultValue; }

  std::string getTooltip() { return String.valueOf(this.value); }
}
} // namespace config
} // namespace zombie
