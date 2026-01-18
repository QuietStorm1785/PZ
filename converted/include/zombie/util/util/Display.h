#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {
namespace util {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class Display {
public:
 static const std::string displayChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#\u00a4%&/()=?'@\u00a3${[]}+|^~*-_.:,;

 static std::string display(int int0) {
 return String.valueOf(int0);
 }

 static std::string hexChar(char char0) {
 std::string string = Integer.toHexString(char0);
 switch (string.length()) {
 case 1:
 return "\\u000" + string;
 case 2:
 return "\\u00" + string;
 case 3:
 return "\\u0" + string;
 case 4:
 return "\\u" + string;
 default:
 throw RuntimeException("Internal error");
 }
 }
}
} // namespace util
} // namespace util
} // namespace zombie
