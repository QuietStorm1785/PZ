#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/FMOD_DriverInfo.h"
#include "fmod/javafmod.h"
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include "zombie/core/Core.h"

namespace zombie {
namespace core {
namespace raknet {


class VoiceManager {
public:
   VoiceManager$3(VoiceManager var1) {
      this.this$0 = var1;
   }

    int call(LuaCallFrame var1, int var2) {
      if (!Core.SoundDisabled && !VoiceManager.VoipDisabled) {
    int var7 = javafmod.FMOD_System_GetRecordNumDrivers();
    KahluaTable var4 = var1.getPlatform().newTable();

         for (int var5 = 0; var5 < var7; var5++) {
    FMOD_DriverInfo var6 = std::make_shared<FMOD_DriverInfo>();
            javafmod.FMOD_System_GetRecordDriverInfo(var5, var6);
            var4.rawset(var5 + 1, var6.name);
         }

         var1.push(var4);
    return 1;
      } else {
    KahluaTable var3 = var1.getPlatform().newTable();
         var1.push(var3);
    return 1;
      }
   }
}
} // namespace raknet
} // namespace core
} // namespace zombie
