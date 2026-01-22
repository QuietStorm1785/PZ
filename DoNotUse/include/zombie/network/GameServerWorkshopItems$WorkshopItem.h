#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/znet/ISteamWorkshopCallback.h"
#include "zombie/core/znet/SteamUGCDetails.h"
#include "zombie/core/znet/SteamWorkshop.h"
#include "zombie/core/znet/SteamWorkshopItem/ItemState.h"
#include "zombie/network/GameServerWorkshopItems/1.h"
#include "zombie/network/GameServerWorkshopItems/WorkshopInstallState.h"
#include <filesystem>

namespace zombie {
namespace network {


class GameServerWorkshopItems {
public:
    long ID;
    WorkshopInstallState state = WorkshopInstallState.CheckItemState;
    long downloadStartTime;
    long downloadQueryTime;
    std::string error;
    SteamUGCDetails details;

   GameServerWorkshopItems$WorkshopItem(long var1) {
      this.ID = var1;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void update() {
      switch (1.$SwitchMap$zombie$network$GameServerWorkshopItems$WorkshopInstallState[this.state.ordinal()]) {
         case 1:
            this.CheckItemState();
            break;
         case 2:
            this.DownloadPending();
         case 3:
      }
   }

    void setState(WorkshopInstallState var1) {
      GameServerWorkshopItems.noise("item state " + this.state + " -> " + var1 + " ID=" + this.ID);
      this.state = var1;
   }

    void CheckItemState() {
    long var1 = SteamWorkshop.instance.GetItemState(this.ID);
      GameServerWorkshopItems.noise("GetItemState()=" + ItemState.toString(var1) + " ID=" + this.ID);
      if (ItemState.Installed.and(var1)
         && this.details != nullptr
         && this.details.getTimeCreated() != 0L
         && this.details.getTimeUpdated() != SteamWorkshop.instance.GetItemInstallTimeStamp(this.ID)) {
         GameServerWorkshopItems.noise("Installed status but timeUpdated doesn't match!!!");
         this.RemoveFolderForReinstall();
         var1 |= ItemState.NeedsUpdate.getValue();
      }

      if (var1 != ItemState.None.getValue() && !ItemState.NeedsUpdate.and(var1)) {
         if (ItemState.Installed.and(var1)) {
            this.setState(WorkshopInstallState.Ready);
         } else {
            this.error = "UnknownItemState";
            this.setState(WorkshopInstallState.Fail);
         }
      } else if (SteamWorkshop.instance.DownloadItem(this.ID, true, this)) {
         this.setState(WorkshopInstallState.DownloadPending);
         this.downloadStartTime = System.currentTimeMillis();
      } else {
         this.error = "DownloadItemFalse";
         this.setState(WorkshopInstallState.Fail);
      }
   }

    void RemoveFolderForReinstall() {
    std::string var1 = SteamWorkshop.instance.GetItemInstallFolder(this.ID);
      if (var1 == nullptr) {
         GameServerWorkshopItems.noise("not removing install folder because GetItemInstallFolder() failed ID=" + this.ID);
      } else {
    Path var2 = Paths.get(var1);
         if (!Files.exists(var2)) {
            GameServerWorkshopItems.noise("not removing install folder because it does not exist : \"" + var1 + "\"");
         } else {
            try {
               Files.walkFileTree(var2, new zombie.network.GameServerWorkshopItems.WorkshopItem.1(this));
            } catch (Exception var4) {
               ExceptionLogger.logException(var4);
            }
         }
      }
   }

    void DownloadPending() {
    long var1 = System.currentTimeMillis();
      if (this.downloadQueryTime + 100L <= var1) {
         this.downloadQueryTime = var1;
    long var3 = SteamWorkshop.instance.GetItemState(this.ID);
         GameServerWorkshopItems.noise("DownloadPending GetItemState()=" + ItemState.toString(var3) + " ID=" + this.ID);
         if (ItemState.NeedsUpdate.and(var3)) {
            long[] var5 = new long[2];
            if (SteamWorkshop.instance.GetItemDownloadInfo(this.ID, var5)) {
               GameServerWorkshopItems.noise("download " + var5[0] + "/" + var5[1] + " ID=" + this.ID);
            }
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
      GameServerWorkshopItems.noise("onItemSubscribed itemID=" + var1);
   }

    void onItemNotSubscribed(long var1, int var3) {
      GameServerWorkshopItems.noise("onItemNotSubscribed itemID=" + var1 + " result=" + var3);
   }

    void onItemDownloaded(long var1) {
      GameServerWorkshopItems.noise("onItemDownloaded itemID=" + var1 + " time=" + (System.currentTimeMillis() - this.downloadStartTime) + " ms");
      if (var1 == this.ID) {
         SteamWorkshop.instance.RemoveCallback(this);
         this.setState(WorkshopInstallState.CheckItemState);
      }
   }

    void onItemNotDownloaded(long var1, int var3) {
      GameServerWorkshopItems.noise("onItemNotDownloaded itemID=" + var1 + " result=" + var3);
      if (var1 == this.ID) {
         SteamWorkshop.instance.RemoveCallback(this);
         this.error = "ItemNotDownloaded";
         this.setState(WorkshopInstallState.Fail);
      }
   }

    void onItemQueryCompleted(long var1, int var3) {
      GameServerWorkshopItems.noise("onItemQueryCompleted handle=" + var1 + " numResult=" + var3);
   }

    void onItemQueryNotCompleted(long var1, int var3) {
      GameServerWorkshopItems.noise("onItemQueryNotCompleted handle=" + var1 + " result=" + var3);
   }
}
} // namespace network
} // namespace zombie
