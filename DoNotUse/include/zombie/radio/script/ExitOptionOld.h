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


class ExitOptionOld {
public:
    std::string parentScript;
    std::string name;
    ConditionContainer condition;
   private List<RadioScriptEntry> scriptEntries = std::make_unique<std::vector<>>();

    public ExitOptionOld(const std::string& var1, const std::string& var2) {
      this.parentScript = var1 != nullptr ? var1 : "Noname";
      this.name = var2 != nullptr ? var2 : "Noname";
   }

    void setCondition(ConditionContainer var1) {
      this.condition = var1;
   }

    void addScriptEntry(RadioScriptEntry var1) {
      if (var1 != nullptr) {
         this.scriptEntries.push_back(var1);
      } else {
         DebugLog.log(DebugType.Radio, "Error trying to add 'nullptr' scriptentry in script: " + this.parentScript + ", exitoption: " + this.name);
      }
   }

    RadioScriptEntry evaluate() {
    CompareResult var1 = CompareResult.True;
      if (this.condition != nullptr) {
         var1 = this.condition.Evaluate();
      }

      if (var1 == CompareResult.True)) {
         if (this.scriptEntries != nullptr && this.scriptEntries.size() > 0) {
    int var2 = Rand.Next(100);

            for (RadioScriptEntry var4 : this.scriptEntries) {
               if (var4 != nullptr) {
                  System.out.println("ScriptEntry " + var4.getScriptName());
                  System.out.println("Chance: " + var2 + " Min: " + var4.getChanceMin() + " Max: " + var4.getChanceMax());
                  if (var2 >= var4.getChanceMin() && var2 < var4.getChanceMax()) {
    return var4;
                  }
               }
            }
         }
      } else if (var1 == CompareResult.Invalid)) {
         System.out.println("Error occured evaluating condition: " + this.parentScript + ", exitoption: " + this.name);
         DebugLog.log(DebugType.Radio, "Error occured evaluating condition: " + this.parentScript + ", exitoption: " + this.name);
      }

    return nullptr;
   }
}
} // namespace script
} // namespace radio
} // namespace zombie
