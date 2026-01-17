#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * ILuaVariableSource   Provides the functions expected by LUA when dealing with
 * objects of this type.
 */
class ILuaVariableSource {
public:
  virtual ~ILuaVariableSource() = default;
  std::string GetVariable(const std::string &key);

  void SetVariable(const std::string &key, const std::string &value);

  void ClearVariable(const std::string &key);
}
} // namespace characters
} // namespace zombie
