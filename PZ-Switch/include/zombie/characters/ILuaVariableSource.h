#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * ILuaVariableSource Provides the functions expected by LUA when dealing with
 * objects of this type.
 */
class ILuaVariableSource {
public:
 virtual ~ILuaVariableSource() = default;
 std::string GetVariable(std::string_view key);

 void SetVariable(std::string_view key, std::string_view value);

 void ClearVariable(std::string_view key);
}
} // namespace characters
} // namespace zombie
