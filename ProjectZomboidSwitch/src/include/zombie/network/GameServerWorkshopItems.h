#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/znet/SteamUGCDetails.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/core/znet/SteamWorkshop.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameServerWorkshopItems/ItemQuery.h"
#include "zombie/network/GameServerWorkshopItems/WorkshopInstallState.h"
#include "zombie/network/GameServerWorkshopItems/WorkshopItem.h"

namespace zombie {
namespace network {


class GameServerWorkshopItems {
public:
    static void noise(const std::string& var0) {
      DebugLog.log("Workshop: " + var0);
   }

    static bool Install(std::vector<int64_t> var0) {
      if (!GameServer.bServer) {
    return false;
      } else if (var0.empty()) {
    return true;
      } else {
    std::vector var1 = new std::vector();

    for (auto& var3 : var0)    WorkshopItem var5 = std::make_shared<WorkshopItem>(var3);
            var1.push_back(var5);
         }

         if (!QueryItemDetails(var1)) {
    return false;
         } else {
            while (true) {
               SteamUtils.runLoop();
    bool var7 = false;

               for (int var9 = 0; var9 < var1.size(); var9++) {
    WorkshopItem var4 = (WorkshopItem)var1.get(var9);
                  var4.update();
                  if (var4.state == WorkshopInstallState.Fail) {
    return false;
                  }

                  if (var4.state != WorkshopInstallState.Ready) {
                     var7 = true;
                     break;
                  }
               }

               if (!var7) {
                  GameServer.WorkshopInstallFolders = new std::string[var0.size()];
                  GameServer.WorkshopTimeStamps = new long[var0.size()];

                  for (int var8 = 0; var8 < var0.size(); var8++) {
    long var10 = (int64_t)var0.get(var8);
    std::string var11 = SteamWorkshop.instance.GetItemInstallFolder(var10);
                     if (var11 == nullptr) {
                        noise("GetItemInstallFolder() failed ID=" + var10);
    return false;
                     }

                     noise(var10 + " installed to " + var11);
                     GameServer.WorkshopInstallFolders[var8] = var11;
                     GameServer.WorkshopTimeStamps[var8] = SteamWorkshop.instance.GetItemInstallTimeStamp(var10);
                  }

    return true;
               }

               try {
                  Thread.sleep(33L);
               } catch (Exception var6) {
                  var6.printStackTrace();
               }
            }
         }
      }
   }

    static bool QueryItemDetails(std::vector<WorkshopItem> var0) {
      long[] var1 = new long[var0.size()];

      for (int var2 = 0; var2 < var0.size(); var2++) {
    WorkshopItem var3 = (WorkshopItem)var0.get(var2);
         var1[var2] = var3.ID;
      }

    ItemQuery var8 = std::make_shared<ItemQuery>();
      var8.handle = SteamWorkshop.instance.CreateQueryUGCDetailsRequest(var1, var8);
      if (var8.handle == 0L) {
    return false;
      } else {
         while (true) {
            SteamUtils.runLoop();
            if (var8.isCompleted()) {
               for (SteamUGCDetails var4 : var8.details) {
    for (auto& var6 : var0)                     if (var6.ID == var4.getID()) {
                        var6.details = var4;
                        break;
                     }
                  }
               }

    return true;
            }

            if (var8.isNotCompleted()) {
    return false;
            }

            try {
               Thread.sleep(33L);
            } catch (Exception var7) {
               var7.printStackTrace();
            }
         }
      }
   }
}
} // namespace network
} // namespace zombie
