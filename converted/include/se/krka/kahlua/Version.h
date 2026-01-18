#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace se {
namespace krka {
namespace kahlua {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class Version {
public:
 static const std::string LUA_VERSION = "lua.version";
 static const std::string KAHLUA_MAJOR = "kahlua.major";
 static const std::string KAHLUA_MINOR = "kahlua.minor";
 static const std::string KAHLUA_FIX = "kahlua.fix";
 static const std::string VERSION = "Kahlua kahlua.major.kahlua.minor.kahlua.fix for Lua lua.version";
}
} // namespace kahlua
} // namespace krka
} // namespace se
