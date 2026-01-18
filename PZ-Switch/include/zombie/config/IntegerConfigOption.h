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

class IntegerConfigOption : public ConfigOption {
public:
 int value;
 int defaultValue;
 int min;
 int max;

public
 IntegerConfigOption(const std::string &name, int _min, int _max,
 int _defaultValue) {
 super(name);
 if (_defaultValue >= _min && _defaultValue <= _max) {
 this->value = _defaultValue;
 this->defaultValue = _defaultValue;
 this->min = _min;
 this->max = _max;
 } else {
 throw std::make_unique<IllegalArgumentException>();
 }
 }

 std::string getType() { return "integer"; }

 void resetToDefault() { this->setValue(this->defaultValue); }

 double getMin() { return this->min; }

 double getMax() { return this->max; }

 void setDefaultToCurrentValue() { this->defaultValue = this->value; }

 void parse(const std::string &s) {
 try {
 double double0 = Double.parseDouble(s);
 this->setValue((int)double0);
 } catch (NumberFormatException numberFormatException) {
 DebugLog.log("ERROR IntegerConfigOption.parse() \"" + this->name +
 "\" string=\"" + s + "\"");
 }
 }

 std::string getValueAsString() { return String.valueOf(this->value); }

 void setValueFromObject(void *o) {
 if (o instanceof Double) {
 this->setValue(((Double)o).intValue());
 } else if (o instanceof String) {
 this->parse((String)o);
 }
 }

 void *getValueAsObject() { return (double)this->value; }

 bool isValidString(const std::string &s) {
 try {
 int int0 = Integer.parseInt(s);
 return int0 >= this->min && int0 <= this->max;
 } catch (NumberFormatException numberFormatException) {
 return false;
 }
 }

 void setValue(int _value) {
 if (_value < this->min) {
 DebugLog.log("ERROR: IntegerConfigOption.setValue() \"" + this->name +
 "\" " + _value + " is less than min=" + this->min);
 } else if (_value > this->max) {
 DebugLog.log("ERROR: IntegerConfigOption.setValue() \"" + this->name +
 "\" " + _value + " is greater than max=" + this->max);
 } else {
 this->value = _value;
 }
 }

 int getValue() { return this->value; }

 int getDefaultValue() { return this->defaultValue; }

 std::string getTooltip() { return String.valueOf(this->value); }
}
} // namespace config
} // namespace zombie
