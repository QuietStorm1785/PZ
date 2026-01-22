#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/znet/ISteamWorkshopCallback.h"
#include "zombie/core/znet/SteamUGCDetails.h"
#include "zombie/core/znet/SteamWorkshop.h"

namespace zombie {
namespace gameStates {


class ConnectToServerState {
public:
    long handle;
   std::vector<SteamUGCDetails> details;
    bool bCompleted;
    bool bNotCompleted;

   private ConnectToServerState$ItemQuery(ConnectToServerState var1) {
      this.this$0 = var1;
   }

    bool isCompleted() {
      return this.bCompleted;
   }

    bool isNotCompleted() {
      return this.bNotCompleted;
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
      ConnectToServerState.noise("onItemQueryCompleted handle=" + var1 + " numResult=" + var3);
      if (var1 == this.handle) {
         SteamWorkshop.instance.RemoveCallback(this);
    std::vector var4 = new std::vector();

         for (int var5 = 0; var5 < var3; var5++) {
    SteamUGCDetails var6 = SteamWorkshop.instance.GetQueryUGCResult(var1, var5);
            if (var6 != nullptr) {
               var4.push_back(var6);
            }
         }

         this.details = var4;
         SteamWorkshop.instance.ReleaseQueryUGCRequest(var1);
         this.bCompleted = true;
      }
   }

    void onItemQueryNotCompleted(long var1, int var3) {
      ConnectToServerState.noise("onItemQueryNotCompleted handle=" + var1 + " result=" + var3);
      if (var1 == this.handle) {
         SteamWorkshop.instance.RemoveCallback(this);
         SteamWorkshop.instance.ReleaseQueryUGCRequest(var1);
         this.bNotCompleted = true;
      }
   }
}
} // namespace gameStates
} // namespace zombie
