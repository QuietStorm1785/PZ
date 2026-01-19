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
namespace script {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class RadioScriptEntry {
public:
 int chanceMin = 0;
 int chanceMax = 100;
 std::string scriptName = "";
 int Delay = 0;

public
 RadioScriptEntry(std::string_view string, int int0) {
 this(string, int0, 0, 100);
 }

public
 RadioScriptEntry(std::string_view string, int int2, int int0, int int1) {
 this->scriptName = string;
 this->setChanceMin(int0);
 this->setChanceMax(int1);
 this->setDelay(int2);
 }

 void setChanceMin(int int0) {
 this->chanceMin = int0 < 0 ? 0 : (int0 > 100 ? 100 : int0);
 }

 int getChanceMin() { return this->chanceMin; }

 void setChanceMax(int int0) {
 this->chanceMax = int0 < 0 ? 0 : (int0 > 100 ? 100 : int0);
 }

 int getChanceMax() { return this->chanceMax; }

 std::string getScriptName() { return this->scriptName; }

 void setScriptName(std::string_view string) { this->scriptName = string; }

 int getDelay() { return this->Delay; }

 void setDelay(int int0) { this->Delay = int0 >= 0 ? int0 : 0; }
}
} // namespace script
} // namespace radio
} // namespace zombie
