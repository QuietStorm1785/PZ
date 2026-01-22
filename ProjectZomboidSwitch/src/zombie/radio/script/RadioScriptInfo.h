#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/radio/globals/RadioGlobal.h"

namespace zombie {
namespace radio {
namespace script {


class RadioScriptInfo {
public:
   private const Map<std::string, RadioGlobal> onStartSetters = std::make_unique<std::unordered_map<>>();
   private const List<ExitOptionOld> exitOptions = std::make_unique<std::vector<>>();

    RadioScriptEntry getNextScript() {
    RadioScriptEntry var1 = nullptr;

      for (ExitOptionOld var3 : this.exitOptions) {
         if (var3 != nullptr) {
            var1 = var3.evaluate();
            if (var1 != nullptr) {
               break;
            }
         }
      }

    return var1;
   }

    void addExitOption(ExitOptionOld var1) {
      if (var1 != nullptr) {
         this.exitOptions.push_back(var1);
      }
   }
}
} // namespace script
} // namespace radio
} // namespace zombie
