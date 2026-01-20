#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace radio {
namespace script {

class RadioScriptEntry {
public:
    int chanceMin = 0;
    int chanceMax = 100;
    std::string scriptName = "";
    int Delay = 0;

    public RadioScriptEntry(const std::string& var1, int var2) {
      this(var1, var2, 0, 100);
   }

    public RadioScriptEntry(const std::string& var1, int var2, int var3, int var4) {
      this.scriptName = var1;
      this.setChanceMin(var3);
      this.setChanceMax(var4);
      this.setDelay(var2);
   }

    void setChanceMin(int var1) {
      this.chanceMin = var1 < 0 ? 0 : (var1 > 100 ? 100 : var1);
   }

    int getChanceMin() {
      return this.chanceMin;
   }

    void setChanceMax(int var1) {
      this.chanceMax = var1 < 0 ? 0 : (var1 > 100 ? 100 : var1);
   }

    int getChanceMax() {
      return this.chanceMax;
   }

    std::string getScriptName() {
      return this.scriptName;
   }

    void setScriptName(const std::string& var1) {
      this.scriptName = var1;
   }

    int getDelay() {
      return this.Delay;
   }

    void setDelay(int var1) {
      this.Delay = var1 >= 0 ? var1 : 0;
   }
}
} // namespace script
} // namespace radio
} // namespace zombie
