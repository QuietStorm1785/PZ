#include "zombie/config/DoubleConfigOption.h"

namespace zombie {
namespace config {

public
DoubleConfigOption::DoubleConfigOption(const std::string &name, double _min,
 double _max, double _defaultValue) {
 // TODO: Implement DoubleConfigOption
 return nullptr;
}

std::string DoubleConfigOption::getType() {
 // TODO: Implement getType
 return "";
}

double DoubleConfigOption::getMin() {
 // TODO: Implement getMin
 return 0;
}

double DoubleConfigOption::getMax() {
 // TODO: Implement getMax
 return 0;
}

void DoubleConfigOption::resetToDefault() {
 // TODO: Implement resetToDefault
}

void DoubleConfigOption::setDefaultToCurrentValue() {
 // TODO: Implement setDefaultToCurrentValue
}

void DoubleConfigOption::parse(const std::string &s) {
 // TODO: Implement parse
}

std::string DoubleConfigOption::getValueAsString() {
 // TODO: Implement getValueAsString
 return "";
}

void DoubleConfigOption::setValueFromObject(void *o) {
 // TODO: Implement setValueFromObject
}

void *DoubleConfigOption::getValueAsObject() {
 // TODO: Implement getValueAsObject
 return nullptr;
}

bool DoubleConfigOption::isValidString(const std::string &s) {
 // TODO: Implement isValidString
 return false;
}

void DoubleConfigOption::setValue(double _value) {
 // TODO: Implement setValue
}

double DoubleConfigOption::getValue() {
 // TODO: Implement getValue
 return 0;
}

double DoubleConfigOption::getDefaultValue() {
 // TODO: Implement getDefaultValue
 return 0;
}

std::string DoubleConfigOption::getTooltip() {
 // TODO: Implement getTooltip
 return "";
}

} // namespace config
} // namespace zombie
