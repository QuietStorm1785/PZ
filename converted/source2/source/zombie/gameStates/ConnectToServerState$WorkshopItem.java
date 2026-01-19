package zombie.gameStates;

import zombie.Lua.LuaEventManager;
import zombie.core.znet.ISteamWorkshopCallback;
import zombie.core.znet.SteamUGCDetails;
import zombie.core.znet.SteamUtils;
import zombie.core.znet.SteamWorkshop;
import zombie.core.znet.SteamWorkshopItem.ItemState;
import zombie.gameStates.ConnectToServerState.1;
import zombie.gameStates.ConnectToServerState.WorkshopItemState;

final class ConnectToServerState$WorkshopItem implements ISteamWorkshopCallback {
   long ID;
   long serverTimeStamp;
   WorkshopItemState state = WorkshopItemState.CheckItemState;
   boolean subscribed;
   long downloadStartTime;
   long downloadQueryTime;
   String error;
   SteamUGCDetails details;

   ConnectToServerState$WorkshopItem(long var1, long var3) {
      this.ID = var1;
      this.serverTimeStamp = var3;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   void update() {
      switch (1.$SwitchMap$zombie$gameStates$ConnectToServerState$WorkshopItemState[this.state.ordinal()]) {
         case 1:
            this.CheckItemState();
            break;
         case 2:
            this.SubscribePending();
            break;
         case 3:
            this.DownloadPending();
         case 4:
      }
   }

   void setState(WorkshopItemState var1) {
      ConnectToServerState.noise("item state " + this.state + " -> " + var1 + " ID=" + this.ID);
      this.state = var1;
   }

   void CheckItemState() {
      long var1 = SteamWorkshop.instance.GetItemState(this.ID);
      ConnectToServerState.noise("GetItemState()=" + ItemState.toString(var1) + " ID=" + this.ID);
      if (!ItemState.Subscribed.and(var1)) {
         if (SteamWorkshop.instance.SubscribeItem(this.ID, this)) {
            this.setState(WorkshopItemState.SubscribePending);
         } else {
            this.error = "SubscribeItemFalse";
            this.setState(WorkshopItemState.Fail);
         }
      } else {
         if (ItemState.Installed.and(var1)
            && ItemState.NeedsUpdate.not(var1)
            && this.details != null
            && this.details.getTimeCreated() != 0L
            && this.details.getTimeUpdated() != SteamWorkshop.instance.GetItemInstallTimeStamp(this.ID)) {
            ConnectToServerState.noise("Installed status but timeUpdated doesn't match!!!");
            var1 |= ItemState.NeedsUpdate.getValue();
         }

         if (ItemState.NeedsUpdate.and(var1)) {
            if (SteamWorkshop.instance.DownloadItem(this.ID, true, this)) {
               this.setState(WorkshopItemState.DownloadPending);
               this.downloadStartTime = System.currentTimeMillis();
            } else {
               this.error = "DownloadItemFalse";
               this.setState(WorkshopItemState.Fail);
            }
         } else if (ItemState.Installed.and(var1)) {
            long var3 = SteamWorkshop.instance.GetItemInstallTimeStamp(this.ID);
            if (var3 == 0L) {
               this.error = "GetItemInstallTimeStamp";
               this.setState(WorkshopItemState.Fail);
            } else if (var3 != this.serverTimeStamp) {
               this.error = "VersionMismatch";
               this.setState(WorkshopItemState.Fail);
            } else {
               this.setState(WorkshopItemState.Ready);
            }
         } else {
            this.error = "UnknownItemState";
            this.setState(WorkshopItemState.Fail);
         }
      }
   }

   void SubscribePending() {
      if (this.subscribed) {
         long var1 = SteamWorkshop.instance.GetItemState(this.ID);
         if (ItemState.Subscribed.and(var1)) {
            this.setState(WorkshopItemState.CheckItemState);
         }
      }
   }

   void DownloadPending() {
      long var1 = System.currentTimeMillis();
      if (this.downloadQueryTime + 100L <= var1) {
         this.downloadQueryTime = var1;
         long var3 = SteamWorkshop.instance.GetItemState(this.ID);
         if (ItemState.NeedsUpdate.and(var3)) {
            long[] var5 = new long[2];
            if (SteamWorkshop.instance.GetItemDownloadInfo(this.ID, var5)) {
               ConnectToServerState.noise("download " + var5[0] + "/" + var5[1] + " ID=" + this.ID);
               LuaEventManager.triggerEvent("OnServerWorkshopItems", "Progress", SteamUtils.convertSteamIDToString(this.ID), var5[0], Math.max(var5[1], 1L));
            }
         }
      }
   }

   public void onItemCreated(long var1, boolean var3) {
   }

   public void onItemNotCreated(int var1) {
   }

   public void onItemUpdated(boolean var1) {
   }

   public void onItemNotUpdated(int var1) {
   }

   public void onItemSubscribed(long var1) {
      ConnectToServerState.noise("onItemSubscribed itemID=" + var1);
      if (var1 == this.ID) {
         SteamWorkshop.instance.RemoveCallback(this);
         this.subscribed = true;
      }
   }

   public void onItemNotSubscribed(long var1, int var3) {
      ConnectToServerState.noise("onItemNotSubscribed itemID=" + var1 + " result=" + var3);
      if (var1 == this.ID) {
         SteamWorkshop.instance.RemoveCallback(this);
         this.error = "ItemNotSubscribed";
         this.setState(WorkshopItemState.Fail);
      }
   }

   public void onItemDownloaded(long var1) {
      ConnectToServerState.noise("onItemDownloaded itemID=" + var1 + " time=" + (System.currentTimeMillis() - this.downloadStartTime) + " ms");
      if (var1 == this.ID) {
         SteamWorkshop.instance.RemoveCallback(this);
         this.setState(WorkshopItemState.CheckItemState);
      }
   }

   public void onItemNotDownloaded(long var1, int var3) {
      ConnectToServerState.noise("onItemNotDownloaded itemID=" + var1 + " result=" + var3);
      if (var1 == this.ID) {
         SteamWorkshop.instance.RemoveCallback(this);
         this.error = "ItemNotDownloaded";
         this.setState(WorkshopItemState.Fail);
      }
   }

   public void onItemQueryCompleted(long var1, int var3) {
   }

   public void onItemQueryNotCompleted(long var1, int var3) {
   }
}
