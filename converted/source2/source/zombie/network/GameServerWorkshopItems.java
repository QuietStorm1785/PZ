package zombie.network;

import java.util.ArrayList;
import zombie.core.znet.SteamUGCDetails;
import zombie.core.znet.SteamUtils;
import zombie.core.znet.SteamWorkshop;
import zombie.debug.DebugLog;
import zombie.network.GameServerWorkshopItems.ItemQuery;
import zombie.network.GameServerWorkshopItems.WorkshopInstallState;
import zombie.network.GameServerWorkshopItems.WorkshopItem;

public class GameServerWorkshopItems {
   private static void noise(String var0) {
      DebugLog.log("Workshop: " + var0);
   }

   public static boolean Install(ArrayList<Long> var0) {
      if (!GameServer.bServer) {
         return false;
      } else if (var0.isEmpty()) {
         return true;
      } else {
         ArrayList var1 = new ArrayList();

         for (long var3 : var0) {
            WorkshopItem var5 = new WorkshopItem(var3);
            var1.add(var5);
         }

         if (!QueryItemDetails(var1)) {
            return false;
         } else {
            while (true) {
               SteamUtils.runLoop();
               boolean var7 = false;

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
                  GameServer.WorkshopInstallFolders = new String[var0.size()];
                  GameServer.WorkshopTimeStamps = new long[var0.size()];

                  for (int var8 = 0; var8 < var0.size(); var8++) {
                     long var10 = (Long)var0.get(var8);
                     String var11 = SteamWorkshop.instance.GetItemInstallFolder(var10);
                     if (var11 == null) {
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

   private static boolean QueryItemDetails(ArrayList<WorkshopItem> var0) {
      long[] var1 = new long[var0.size()];

      for (int var2 = 0; var2 < var0.size(); var2++) {
         WorkshopItem var3 = (WorkshopItem)var0.get(var2);
         var1[var2] = var3.ID;
      }

      ItemQuery var8 = new ItemQuery();
      var8.handle = SteamWorkshop.instance.CreateQueryUGCDetailsRequest(var1, var8);
      if (var8.handle == 0L) {
         return false;
      } else {
         while (true) {
            SteamUtils.runLoop();
            if (var8.isCompleted()) {
               for (SteamUGCDetails var4 : var8.details) {
                  for (WorkshopItem var6 : var0) {
                     if (var6.ID == var4.getID()) {
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
