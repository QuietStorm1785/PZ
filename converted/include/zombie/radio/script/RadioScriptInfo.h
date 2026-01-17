#pragma once
#include "zombie/radio/globals/RadioGlobal.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace radio {
namespace script {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class RadioScriptInfo {
public:
private
  final Map<String, RadioGlobal> onStartSetters = std::make_unique<HashMap<>>();
private
  final List<ExitOptionOld> exitOptions = std::make_unique<ArrayList<>>();

  RadioScriptEntry getNextScript() {
    RadioScriptEntry radioScriptEntry = null;

    for (ExitOptionOld exitOptionOld : this.exitOptions) {
      if (exitOptionOld != nullptr) {
        radioScriptEntry = exitOptionOld.evaluate();
        if (radioScriptEntry != nullptr) {
          break;
        }
      }
    }

    return radioScriptEntry;
  }

  void addExitOption(ExitOptionOld exitOptionOld) {
    if (exitOptionOld != nullptr) {
      this.exitOptions.add(exitOptionOld);
    }
  }
}
} // namespace script
} // namespace radio
} // namespace zombie
