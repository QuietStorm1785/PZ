#include "zombie/config/StringConfigOption.h"

namespace zombie {
namespace config {

public
StringConfigOption::StringConfigOption(const std::string &name,
 const std::string &_defaultValue,
 int _maxLength) {
 // TODO: Implement StringConfigOption
 return nullptr;
}

std::string StringConfigOption::getType() {
 // TODO: Implement getType
 return "";
}

void StringConfigOption::resetToDefault() {
 // TODO: Implement resetToDefault
}

void StringConfigOption::setDefaultToCurrentValue() {
 // TODO: Implement setDefaultToCurrentValue
}

void StringConfigOption::parse(const std::string &s) {
 // TODO: Implement parse
}

std::string StringConfigOption::getValueAsString() {
 // TODO: Implement getValueAsString
 return "";
}

std::string StringConfigOption::getValueAsLuaString() {
 // TODO: Implement getValueAsLuaString
 return "";
}

void StringConfigOption::setValueFromObject(void *o) {
 // TODO: Implement setValueFromObject
}

void *StringConfigOption::getValueAsObject() {
 // TODO: Implement getValueAsObject
 return nullptr;
}

bool StringConfigOption::isValidString(const std::string &s) {
 // TODO: Implement isValidString
 return false;
}

void StringConfigOption::setValue(const std::string &_value) {
 // TODO: Implement setValue
}

std::string StringConfigOption::getValue() {
 // TODO: Implement getValue
 return "";
}

std::string StringConfigOption::getDefaultValue() {
 // TODO: Implement getDefaultValue
 return "";
}

std::string StringConfigOption::getTooltip() {
 // TODO: Implement getTooltip
 return "";
}

} // namespace config
} // namespace zombie
