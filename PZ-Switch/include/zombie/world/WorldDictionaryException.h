#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace world {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WorldDictionaryException : public Exception {
public:
public
 WorldDictionaryException(std::string_view string) { super(string); }

public
 WorldDictionaryException(std::string_view string,
 std::exception throwable) {
 super(string, throwable);
 }
}
} // namespace world
} // namespace zombie
