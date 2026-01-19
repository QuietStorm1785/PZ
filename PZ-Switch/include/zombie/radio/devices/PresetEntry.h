#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace radio {
namespace devices {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * turbo
 */
class PresetEntry {
public:
 std::string name = "New preset";
 int frequency = 93200;

public
 PresetEntry() {}

public
 PresetEntry(std::string_view n, int f) {
 this->name = n;
 this->frequency = f;
 }

 std::string getName() { return this->name; }

 void setName(std::string_view n) { this->name = n; }

 int getFrequency() { return this->frequency; }

 void setFrequency(int f) { this->frequency = f; }
}
} // namespace devices
} // namespace radio
} // namespace zombie
