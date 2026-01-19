#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace worldMap {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WorldMapJNI {
public:
 static void init() {}

 static void writeToStdErr(std::string_view string) {
 System.err.println(string);
 }
}
} // namespace worldMap
} // namespace zombie
