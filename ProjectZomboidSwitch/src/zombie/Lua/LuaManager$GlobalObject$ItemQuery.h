#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/LuaClosure.h"
#include "zombie/core/znet/ISteamWorkshopCallback.h"
#include "zombie/core/znet/SteamUGCDetails.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/core/znet/SteamWorkshop.h"

namespace zombie {
namespace Lua {


class LuaManager {
public:
    LuaClosure functionObj;
    void* arg1;
    long handle;

   public LuaManager$GlobalObject$ItemQuery(std::vector<std::string> var1, LuaClosure var2, Object var3) {
      this.functionObj = var2;
      this.arg1 = var3;
      long[] var4 = new long[var1.size()];
    int var5 = 0;

      for (int var6 = 0; var6 < var1.size(); var6++) {
    long var7 = SteamUtils.convertStringToSteamID((std::string)var1.get(var6));
         if (var7 != -1L) {
            var4[var5++] = var7;
         }
      }

      this.handle = SteamWorkshop.instance.CreateQueryUGCDetailsRequest(var4, this);
      if (this.handle == 0L) {
         SteamWorkshop.instance.RemoveCallback(this);
         if (var3 == nullptr) {
            LuaManager.caller.pcall(LuaManager.thread, var2, "NotCompleted");
         } else {
            LuaManager.caller.pcall(LuaManager.thread, var2, new Object[]{var3, "NotCompleted"});
         }
      }
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
    std::vector var4 = new std::vector();

         for (int var5 = 0; var5 < var3; var5++) {
    SteamUGCDetails var6 = SteamWorkshop.instance.GetQueryUGCResult(var1, var5);
            if (var6 != nullptr) {
               var4.push_back(var6);
            }
         }

         SteamWorkshop.instance.ReleaseQueryUGCRequest(var1);
         if (this.arg1 == nullptr) {
            LuaManager.caller.pcall(LuaManager.thread, this.functionObj, new Object[]{"Completed", var4});
         } else {
            LuaManager.caller.pcall(LuaManager.thread, this.functionObj, new Object[]{this.arg1, "Completed", var4});
         }
      }
   }

    void onItemQueryNotCompleted(long var1, int var3) {
      if (var1 == this.handle) {
         SteamWorkshop.instance.RemoveCallback(this);
         SteamWorkshop.instance.ReleaseQueryUGCRequest(var1);
         if (this.arg1 == nullptr) {
            LuaManager.caller.pcall(LuaManager.thread, this.functionObj, "NotCompleted");
         } else {
            LuaManager.caller.pcall(LuaManager.thread, this.functionObj, new Object[]{this.arg1, "NotCompleted"});
         }
      }
   }
}
} // namespace Lua
} // namespace zombie
