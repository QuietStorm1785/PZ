#pragma once
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace profanity {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Phonizer {
public:
 std::string name;
 std::string regex;

public
 Phonizer(std::string_view string0, std::string_view string1) {
 this->name = string0;
 this->regex = string1;
 }

 std::string getName() { return this->name; }

 std::string getRegex() { return this->regex; }

 void execute(Matcher matcher, StringBuffer stringBuffer) {
 if (matcher.group(this->name) != nullptr) {
 matcher.appendReplacement(stringBuffer, "${" + this->name + "}");
 }
 }
}
} // namespace profanity
} // namespace zombie
