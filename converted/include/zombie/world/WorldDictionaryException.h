#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace world {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class WorldDictionaryException : public Exception {
public:
 public WorldDictionaryException(const std::string& string) {
 super(string);
 }

 public WorldDictionaryException(const std::string& string, std::exception throwable) {
 super(string, throwable);
 }
}
} // namespace world
} // namespace zombie
