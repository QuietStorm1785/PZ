#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace config {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class EnumConfigOption : public IntegerConfigOption {
public:
 public EnumConfigOption(const std::string& name, int numValues, int defaultValue) {
 super(name, 1, numValues, defaultValue);
 }

 std::string getType() {
 return "enum";
 }

 int getNumValues() {
 return this->max;
 }
}
} // namespace config
} // namespace zombie
