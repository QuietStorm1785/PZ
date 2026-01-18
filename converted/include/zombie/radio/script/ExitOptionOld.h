#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/radio/globals/CompareResult.h"

namespace zombie {
namespace radio {
namespace script {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ExitOptionOld {
public:
 std::string parentScript;
 std::string name;
 ConditionContainer condition;
 private List<RadioScriptEntry> scriptEntries = std::make_unique<ArrayList<>>();

 public ExitOptionOld(const std::string& string0, const std::string& string1) {
 this->parentScript = string0 != nullptr ? string0 : "Noname";
 this->name = string1 != nullptr ? string1 : "Noname";
 }

 void setCondition(ConditionContainer conditionContainer) {
 this->condition = conditionContainer;
 }

 void addScriptEntry(RadioScriptEntry radioScriptEntry) {
 if (radioScriptEntry != nullptr) {
 this->scriptEntries.add(radioScriptEntry);
 } else {
 DebugLog.log(DebugType.Radio, "Error trying to add 'nullptr' scriptentry in script: " + this->parentScript + ", exitoption: " + this->name);
 }
 }

 RadioScriptEntry evaluate() {
 CompareResult compareResult = CompareResult.True;
 if (this->condition != nullptr) {
 compareResult = this->condition.Evaluate();
 }

 if (compareResult == CompareResult.True) {
 if (this->scriptEntries != nullptr && this->scriptEntries.size() > 0) {
 int int0 = Rand.Next(100);

 for (RadioScriptEntry radioScriptEntry : this->scriptEntries) {
 if (radioScriptEntry != nullptr) {
 System.out.println("ScriptEntry " + radioScriptEntry.getScriptName());
 System.out.println("Chance: " + int0 + " Min: " + radioScriptEntry.getChanceMin() + " Max: " + radioScriptEntry.getChanceMax());
 if (int0 >= radioScriptEntry.getChanceMin() && int0 < radioScriptEntry.getChanceMax()) {
 return radioScriptEntry;
 }
 }
 }
 }
 } else if (compareResult == CompareResult.Invalid) {
 System.out.println("Error occured evaluating condition: " + this->parentScript + ", exitoption: " + this->name);
 DebugLog.log(DebugType.Radio, "Error occured evaluating condition: " + this->parentScript + ", exitoption: " + this->name);
 }

 return nullptr;
 }
}
} // namespace script
} // namespace radio
} // namespace zombie
