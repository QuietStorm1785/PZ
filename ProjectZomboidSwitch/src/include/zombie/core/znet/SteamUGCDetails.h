#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/znet/SteamWorkshopItem/ItemState.h"
#include "zombie/debug/DebugLog.h"

namespace zombie {
namespace core {
namespace znet {


class SteamUGCDetails {
public:
    long ID;
    std::string title;
    long timeCreated;
    long timeUpdated;
    int fileSize;
   private long[] childIDs;

    public SteamUGCDetails(long var1, const std::string& var3, long var4, long var6, int var8, long[] var9) {
      this.ID = var1;
      this.title = var3;
      this.timeCreated = var4;
      this.timeUpdated = var6;
      this.fileSize = var8;
      this.childIDs = var9;
   }

    long getID() {
      return this.ID;
   }

    std::string getIDString() {
      return SteamUtils.convertSteamIDToString(this.ID);
   }

    std::string getTitle() {
      return this.title;
   }

    long getTimeCreated() {
      return this.timeCreated;
   }

    long getTimeUpdated() {
      return this.timeUpdated;
   }

    int getFileSize() {
      return this.fileSize;
   }

   public long[] getChildren() {
      return this.childIDs;
   }

    int getNumChildren() {
      return this.childIDs == nullptr ? 0 : this.childIDs.length;
   }

    long getChildID(int var1) {
      if (var1 >= 0 && var1 < this.getNumChildren()) {
         return this.childIDs[var1];
      } else {
         throw IndexOutOfBoundsException("invalid child index");
      }
   }

    std::string getState() {
    long var1 = SteamWorkshop.instance.GetItemState(this.ID);
      if (!ItemState.Subscribed.and(var1)) {
         return "NotSubscribed";
      } else if (ItemState.DownloadPending.and(var1)) {
         DebugLog.log(ItemState.toString(var1) + " ID=" + this.ID);
         return "Downloading";
      } else if (ItemState.NeedsUpdate.and(var1)) {
         return "NeedsUpdate";
      } else {
         return ItemState.Installed.and(var1) ? "Installed" : "Error";
      }
   }
}
} // namespace znet
} // namespace core
} // namespace zombie
