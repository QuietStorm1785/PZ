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

class BooleanConfigOption : public ConfigOption {
public:
 bool value;
 bool defaultValue;

public
 BooleanConfigOption(const std::string &name, bool _defaultValue) {
 super(name);
 this->value = _defaultValue;
 this->defaultValue = _defaultValue;
 }

 std::string getType() { return "boolean"; }

 void resetToDefault() { this->setValue(this->defaultValue); }

 void setDefaultToCurrentValue() { this->defaultValue = this->value; }

 void parse(const std::string &s) {
 if (this->isValidString(s) {
 this->setValue(s.equalsIgnoreCase("true") || s.equalsIgnoreCase("1"));
 } else {
 DebugLog.log("ERROR BooleanConfigOption.parse() \"" + this->name +
 "\" string=" + s + "\"");
 }
 }

 std::string getValueAsString() { return String.valueOf(this->value); }

 void setValueFromObject(void *o) {
 if (o instanceof Boolean) {
 this->setValue((Boolean)o);
 } else if (o instanceof Double) {
 this->setValue((Double)o != 0.0);
 } else if (o instanceof String) {
 this->parse((String)o);
 }
 }

 void *getValueAsObject() { return this->value; }

 bool isValidString(const std::string &s) {
 return s != nullptr &&
 (s.equalsIgnoreCase("true") || s.equalsIgnoreCase("false") ||
 s.equalsIgnoreCase("1") || s.equalsIgnoreCase("0"));
 }

 bool getValue() { return this->value; }

 void setValue(bool _value) { this->value = _value; }

 bool getDefaultValue() { return this->defaultValue; }

 std::string getTooltip() { return String.valueOf(this->value); }
}
} // namespace config
} // namespace zombie
