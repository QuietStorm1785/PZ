#include "zombie/config/IntegerConfigOption.h"

namespace zombie {
namespace config {

public
IntegerConfigOption::IntegerConfigOption(const std::string &name, int _min,
                                         int _max, int _defaultValue) {
  // TODO: Implement IntegerConfigOption
  return nullptr;
}

std::string IntegerConfigOption::getType() {
  // TODO: Implement getType
  return "";
}

void IntegerConfigOption::resetToDefault() {
  // TODO: Implement resetToDefault
}

double IntegerConfigOption::getMin() {
  // TODO: Implement getMin
  return 0;
}

double IntegerConfigOption::getMax() {
  // TODO: Implement getMax
  return 0;
}

void IntegerConfigOption::setDefaultToCurrentValue() {
  // TODO: Implement setDefaultToCurrentValue
}

void IntegerConfigOption::parse(const std::string &s) {
  // TODO: Implement parse
}

std::string IntegerConfigOption::getValueAsString() {
  // TODO: Implement getValueAsString
  return "";
}

void IntegerConfigOption::setValueFromObject(void *o) {
  // TODO: Implement setValueFromObject
}

void *IntegerConfigOption::getValueAsObject() {
  // TODO: Implement getValueAsObject
  return nullptr;
}

bool IntegerConfigOption::isValidString(const std::string &s) {
  // TODO: Implement isValidString
  return false;
}

void IntegerConfigOption::setValue(int _value) {
  // TODO: Implement setValue
}

int IntegerConfigOption::getValue() {
  // TODO: Implement getValue
  return 0;
}

int IntegerConfigOption::getDefaultValue() {
  // TODO: Implement getDefaultValue
  return 0;
}

std::string IntegerConfigOption::getTooltip() {
  // TODO: Implement getTooltip
  return "";
}

} // namespace config
} // namespace zombie
