#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include <algorithm>

namespace zombie {
namespace modding {


class ModUtilsJava {
:
    static std::string getRandomUUID() const {
      return UUID.randomUUID().toString();
   }

    static bool sendItemListNet(IsoPlayer var0, ArrayList<InventoryItem> var1, IsoPlayer var2, const std::string& var3, const std::string& var4) {
      if (var1 != nullptr) {
         var3 = var3 != nullptr ? var3 : "-1";
         if (GameClient.bClient) {
            if (var1.size() > 50) {
    return false;
            }

            for (int var5 = 0; var5 < var1.size(); var5++) {
    InventoryItem var6 = (InventoryItem)var1.get(var5);
               if (!var0.getInventory().getItems().contains(var6)) {
    return false;
               }
            }

            return GameClient.sendItemListNet(var0, var1, var2, var3, var4);
         }

         if (GameServer.bServer) {
            return GameServer.sendItemListNet(nullptr, var0, var1, var2, var3, var4);
         }
      }

    return false;
   }
}
} // namespace modding
} // namespace zombie
