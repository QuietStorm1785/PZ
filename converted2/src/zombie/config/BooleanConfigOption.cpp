#include "zombie/config/BooleanConfigOption.h"

namespace zombie {
namespace config {

public
BooleanConfigOption::BooleanConfigOption(const std::string &name,
                                         bool _defaultValue) {
  // TODO: Implement BooleanConfigOption
  return nullptr;
}

std::string BooleanConfigOption::getType() {
  // TODO: Implement getType
  return "";
}

void BooleanConfigOption::resetToDefault() {
  // TODO: Implement resetToDefault
}

void BooleanConfigOption::setDefaultToCurrentValue() {
  // TODO: Implement setDefaultToCurrentValue
}

void BooleanConfigOption::parse(const std::string &s) {
  // TODO: Implement parse
}

std::string BooleanConfigOption::getValueAsString() {
  // TODO: Implement getValueAsString
  return "";
}

void BooleanConfigOption::setValueFromObject(void *o) {
  // TODO: Implement setValueFromObject
}

void *BooleanConfigOption::getValueAsObject() {
  // TODO: Implement getValueAsObject
  return nullptr;
}

bool BooleanConfigOption::isValidString(const std::string &s) {
  // TODO: Implement isValidString
  return false;
}

bool BooleanConfigOption::getValue() {
  // TODO: Implement getValue
  return false;
}

void BooleanConfigOption::setValue(bool _value) {
  // TODO: Implement setValue
}

bool BooleanConfigOption::getDefaultValue() {
  // TODO: Implement getDefaultValue
  return false;
}

std::string BooleanConfigOption::getTooltip() {
  // TODO: Implement getTooltip
  return "";
}

} // namespace config
} // namespace zombie
