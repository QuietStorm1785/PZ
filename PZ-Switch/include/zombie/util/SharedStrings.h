#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SharedStrings {
public:
private
 HashMap<String, String> strings = std::make_unique<HashMap<>>();

 std::string get(const std::string &s) {
 std::string string = this->strings.get(s);
 if (string.empty()) {
 this->strings.put(s, s);
 string = s;
 }

 return string;
 }

 void clear() { this->strings.clear(); }
}
} // namespace util
} // namespace zombie
