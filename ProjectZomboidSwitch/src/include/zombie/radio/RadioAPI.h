#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include <algorithm>

namespace zombie {
namespace radio {


class RadioAPI {
public:
    static RadioAPI instance;

    static int timeToTimeStamp(int var0, int var1, int var2) {
      return var0 * 24 + var1 * 60 + var2;
   }

    static int timeStampToDays(int var0) {
      return var0 / 1440;
   }

    static int timeStampToHours(int var0) {
      return var0 / 60 % 24;
   }

    static int timeStampToMinutes(int var0) {
      return var0 % 60;
   }

    static bool hasInstance() {
      return instance != nullptr;
   }

    static RadioAPI getInstance() {
      if (instance == nullptr) {
         instance = std::make_unique<RadioAPI>();
      }

    return instance;
   }

    private RadioAPI() {
   }

    KahluaTable getChannels(const std::string& var1) {
    std::unordered_map var2 = ZomboidRadio.getInstance().GetChannelList(var1);
    KahluaTable var3 = LuaManager.platform.newTable();
      if (var2 != nullptr) {
         for (Entry var5 : var2.entrySet()) {
            var3.rawset(var5.getKey(), var5.getValue());
         }
      }

    return var3;
   }
}
} // namespace radio
} // namespace zombie
