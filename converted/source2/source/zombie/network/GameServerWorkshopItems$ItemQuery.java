package zombie.network;

import java.util.ArrayList;
import zombie.core.znet.ISteamWorkshopCallback;
import zombie.core.znet.SteamUGCDetails;
import zombie.core.znet.SteamWorkshop;

final class GameServerWorkshopItems$ItemQuery implements ISteamWorkshopCallback {
   long handle;
   ArrayList<SteamUGCDetails> details;
   boolean bCompleted;
   boolean bNotCompleted;

   private GameServerWorkshopItems$ItemQuery() {
   }

   public boolean isCompleted() {
      return this.bCompleted;
   }

   public boolean isNotCompleted() {
      return this.bNotCompleted;
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
   }

   public void onItemNotSubscribed(long var1, int var3) {
   }

   public void onItemDownloaded(long var1) {
   }

   public void onItemNotDownloaded(long var1, int var3) {
   }

   public void onItemQueryCompleted(long var1, int var3) {
      GameServerWorkshopItems.noise("onItemQueryCompleted handle=" + var1 + " numResult=" + var3);
      if (var1 == this.handle) {
         SteamWorkshop.instance.RemoveCallback(this);
         ArrayList var4 = new ArrayList();

         for (int var5 = 0; var5 < var3; var5++) {
            SteamUGCDetails var6 = SteamWorkshop.instance.GetQueryUGCResult(var1, var5);
            if (var6 != null) {
               var4.add(var6);
            }
         }

         this.details = var4;
         SteamWorkshop.instance.ReleaseQueryUGCRequest(var1);
         this.bCompleted = true;
      }
   }

   public void onItemQueryNotCompleted(long var1, int var3) {
      GameServerWorkshopItems.noise("onItemQueryNotCompleted handle=" + var1 + " result=" + var3);
      if (var1 == this.handle) {
         SteamWorkshop.instance.RemoveCallback(this);
         SteamWorkshop.instance.ReleaseQueryUGCRequest(var1);
         this.bNotCompleted = true;
      }
   }
}
