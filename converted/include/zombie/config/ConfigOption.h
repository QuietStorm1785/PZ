#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace config {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class ConfigOption {
public:
 const std::string name;

 public ConfigOption(const std::string& _name) {
 if (_name != nullptr && !_name.empty() && !_name.contains("=")) {
 this->name = _name;
 } else {
 throw std::make_unique<IllegalArgumentException>();
 }
 }

 std::string getName() {
 return this->name;
 }

 public String getType();

 public void resetToDefault();

 public void setDefaultToCurrentValue();

 public void parse(String s);

 public String getValueAsString();

 std::string getValueAsLuaString() {
 return this->getValueAsString();
 }

 public void setValueFromObject(Object o);

 public Object getValueAsObject();

 public boolean isValidString(String s);

 public String getTooltip();
}
} // namespace config
} // namespace zombie
