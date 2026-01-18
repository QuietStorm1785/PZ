#pragma once
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

class ConfigOption {
public:
  const std::string name;

public
  ConfigOption(const std::string &_name) {
    if (_name != nullptr && !_name.isEmpty() && !_name.contains("=")) {
      this.name = _name;
    } else {
      throw std::make_unique<IllegalArgumentException>();
    }
  }

  std::string getName() { return this.name; }

public
  abstract String getType();

public
  abstract void resetToDefault();

public
  abstract void setDefaultToCurrentValue();

public
  abstract void parse(String s);

public
  abstract String getValueAsString();

  std::string getValueAsLuaString() { return this.getValueAsString(); }

public
  abstract void setValueFromObject(Object o);

public
  abstract Object getValueAsObject();

public
  abstract boolean isValidString(String s);

public
  abstract String getTooltip();
}
} // namespace config
} // namespace zombie
