#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace text {
namespace templating {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class ReplaceSingle {
public:
 std::string value = "";

 public ReplaceSingle() {
 }

 public ReplaceSingle(const std::string& string) {
 this->value = string;
 }

 std::string getValue() {
 return this->value;
 }

 void setValue(const std::string& string) {
 this->value = string;
 }

 std::string getString() {
 return this->value;
 }
}
} // namespace templating
} // namespace text
} // namespace zombie
