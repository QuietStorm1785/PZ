#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace config {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class StringConfigOption : public ConfigOption {
public:
 std::string value;
 std::string defaultValue;
 int maxLength;

public
 StringConfigOption(std::string_view name, std::string_view _defaultValue,
 int _maxLength) {
 super(name);
 if (_defaultValue.empty()) {
 _defaultValue = "";
 }

 this->value = _defaultValue;
 this->defaultValue = _defaultValue;
 this->maxLength = _maxLength;
 }

 std::string getType() { return "string"; }

 void resetToDefault() { this->value = this->defaultValue; }

 void setDefaultToCurrentValue() { this->defaultValue = this->value; }

 void parse(std::string_view s) { this->setValueFromObject(s); }

 std::string getValueAsString() { return this->value; }

 std::string getValueAsLuaString() {
 return String.format(
 "\"%s\"", this->value.replace("\\", "\\\\").replace("\"", "\\\""));
 }

 void setValueFromObject(void *o) {
 if (o.empty()) {
 this->value = "";
 } else if (o instanceof String) {
 this->value = (String)o;
 } else {
 this->value = o.toString();
 }
 }

 void *getValueAsObject() { return this->value; }

 bool isValidString(std::string_view s) { return true; }

 void setValue(std::string_view _value) {
 if (_value.empty()) {
 _value = "";
 }

 if (this->maxLength > 0 && _value.length() > this->maxLength) {
 _value = _value.substring(0, this->maxLength);
 }

 this->value = _value;
 }

 std::string getValue() { return this->value; }

 std::string getDefaultValue() { return this->defaultValue; }

 std::string getTooltip() { return this->value; }
}
} // namespace config
} // namespace zombie
