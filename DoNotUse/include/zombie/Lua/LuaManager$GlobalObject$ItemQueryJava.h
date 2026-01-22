#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/znet/ISteamWorkshopCallback.h"
#include "zombie/core/znet/SteamUGCDetails.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/core/znet/SteamWorkshop.h"
#include "zombie/core/znet/SteamWorkshopItem/ItemState.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/chat/ChatServer.h"

namespace zombie {
namespace Lua {


class LuaManager {
public:
    long handle;
    UdpConnection connection;

   public LuaManager$GlobalObject$ItemQueryJava(std::vector<std::string> var1, UdpConnection var2) {
      this.connection = var2;
      long[] var3 = new long[var1.size()];
    int var4 = 0;

      for (int var5 = 0; var5 < var1.size(); var5++) {
    long var6 = SteamUtils.convertStringToSteamID((std::string)var1.get(var5));
         if (var6 != -1L) {
            var3[var4++] = var6;
         }
      }

      this.handle = SteamWorkshop.instance.CreateQueryUGCDetailsRequest(var3, this);
      if (this.handle == 0L) {
         SteamWorkshop.instance.RemoveCallback(this);
         this.inform("CheckModsNeedUpdate: Check not completed");
      }
   }

    void inform(const std::string& var1) {
      if (this.connection != nullptr) {
         ChatServer.getInstance().sendMessageToServerChat(this.connection, var1);
      }

      DebugLog.log(var1);
   }

    void onItemCreated(long var1, bool var3) {
   }

    void onItemNotCreated(int var1) {
   }

    void onItemUpdated(bool var1) {
   }

    void onItemNotUpdated(int var1) {
   }

    void onItemSubscribed(long var1) {
   }

    void onItemNotSubscribed(long var1, int var3) {
   }

    void onItemDownloaded(long var1) {
   }

    void onItemNotDownloaded(long var1, int var3) {
   }

    void onItemQueryCompleted(long var1, int var3) {
      if (var1 == this.handle) {
         SteamWorkshop.instance.RemoveCallback(this);

         for (int var4 = 0; var4 < var3; var4++) {
    SteamUGCDetails var5 = SteamWorkshop.instance.GetQueryUGCResult(var1, var4);
            if (var5 != nullptr) {
    long var6 = var5.getID();
    long var8 = SteamWorkshop.instance.GetItemState(var6);
               if (ItemState.Installed.and(var8)
                  && ItemState.NeedsUpdate.not(var8)
                  && var5.getTimeCreated() != 0L
                  && var5.getTimeUpdated() != SteamWorkshop.instance.GetItemInstallTimeStamp(var6)) {
                  var8 |= ItemState.NeedsUpdate.getValue();
               }

               if (ItemState.NeedsUpdate.and(var8)) {
                  this.inform("CheckModsNeedUpdate: Mods need update");
                  SteamWorkshop.instance.ReleaseQueryUGCRequest(var1);
                  return;
               }
            }
         }

         this.inform("CheckModsNeedUpdate: Mods updated");
         SteamWorkshop.instance.ReleaseQueryUGCRequest(var1);
      }
   }

    void onItemQueryNotCompleted(long var1, int var3) {
      if (var1 == this.handle) {
         SteamWorkshop.instance.RemoveCallback(this);
         SteamWorkshop.instance.ReleaseQueryUGCRequest(var1);
         this.inform("CheckModsNeedUpdate: Check not completed");
      }
   }
}
} // namespace Lua
} // namespace zombie
