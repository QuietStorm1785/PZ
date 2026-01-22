#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace znet {

enum class SteamWorkshopItem {
   None(0),
   Subscribed(1),
   LegacyItem(2),
   Installed(4),
   NeedsUpdate(8),
   Downloading(16),
   DownloadPending(32);

    const int value;

   private SteamWorkshopItem$ItemState(int var3) {
      this.value = var3;
   }

    int getValue() {
      return this.value;
   }

    bool and(SteamWorkshopItem$ItemState var1) {
      return (this.value & var1.value) != 0;
   }

    bool and(long var1) {
      return (this.value & var1) != 0L;
   }

    bool not(long var1) {
      return (this.value & var1) == 0L;
   }

    static std::string toString(long var0) {
      if (var0 == None.getValue()) {
         return "None";
      } else {
    std::stringstream var2 = new std::stringstream();

         for (SteamWorkshopItem$ItemState var6 : values()) {
            if (var6 != None && var6.and(var0)) {
               if (var2.length() > 0) {
                  var2.append("|");
               }

               var2.append(var6.name());
            }
         }

         return var2;
      }
   }
}
} // namespace znet
} // namespace core
} // namespace zombie
