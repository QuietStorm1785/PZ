package zombie.Lua;

import java.util.ArrayList;
import zombie.core.raknet.UdpConnection;
import zombie.core.znet.ISteamWorkshopCallback;
import zombie.core.znet.SteamUGCDetails;
import zombie.core.znet.SteamUtils;
import zombie.core.znet.SteamWorkshop;
import zombie.core.znet.SteamWorkshopItem.ItemState;
import zombie.debug.DebugLog;
import zombie.network.chat.ChatServer;

final class LuaManager$GlobalObject$ItemQueryJava implements ISteamWorkshopCallback {
   private long handle;
   private UdpConnection connection;

   public LuaManager$GlobalObject$ItemQueryJava(ArrayList<String> var1, UdpConnection var2) {
      this.connection = var2;
      long[] var3 = new long[var1.size()];
      int var4 = 0;

      for (int var5 = 0; var5 < var1.size(); var5++) {
         long var6 = SteamUtils.convertStringToSteamID((String)var1.get(var5));
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

   private void inform(String var1) {
      if (this.connection != null) {
         ChatServer.getInstance().sendMessageToServerChat(this.connection, var1);
      }

      DebugLog.log(var1);
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
      if (var1 == this.handle) {
         SteamWorkshop.instance.RemoveCallback(this);

         for (int var4 = 0; var4 < var3; var4++) {
            SteamUGCDetails var5 = SteamWorkshop.instance.GetQueryUGCResult(var1, var4);
            if (var5 != null) {
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

   public void onItemQueryNotCompleted(long var1, int var3) {
      if (var1 == this.handle) {
         SteamWorkshop.instance.RemoveCallback(this);
         SteamWorkshop.instance.ReleaseQueryUGCRequest(var1);
         this.inform("CheckModsNeedUpdate: Check not completed");
      }
   }
}
