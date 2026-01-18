#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace worldMap {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class WorldMapJNI {
public:
 static void init() {
 }

 static void writeToStdErr(const std::string& string) {
 System.err.println(string);
 }
}
} // namespace worldMap
} // namespace zombie
