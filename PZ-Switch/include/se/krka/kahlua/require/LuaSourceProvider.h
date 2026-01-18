#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace require {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class LuaSourceProvider {
public:
 virtual ~LuaSourceProvider() = default;
 Reader getLuaSource(const std::string &var1);
}
} // namespace require
} // namespace kahlua
} // namespace krka
} // namespace se
