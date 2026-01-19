package zombie.Lua;

import java.util.ArrayList;
import se.krka.kahlua.vm.LuaClosure;
import zombie.core.znet.ISteamWorkshopCallback;
import zombie.core.znet.SteamUGCDetails;
import zombie.core.znet.SteamUtils;
import zombie.core.znet.SteamWorkshop;

final class LuaManager$GlobalObject$ItemQuery implements ISteamWorkshopCallback {
   private LuaClosure functionObj;
   private Object arg1;
   private long handle;

   public LuaManager$GlobalObject$ItemQuery(ArrayList<String> var1, LuaClosure var2, Object var3) {
      this.functionObj = var2;
      this.arg1 = var3;
      long[] var4 = new long[var1.size()];
      int var5 = 0;

      for (int var6 = 0; var6 < var1.size(); var6++) {
         long var7 = SteamUtils.convertStringToSteamID((String)var1.get(var6));
         if (var7 != -1L) {
            var4[var5++] = var7;
         }
      }

      this.handle = SteamWorkshop.instance.CreateQueryUGCDetailsRequest(var4, this);
      if (this.handle == 0L) {
         SteamWorkshop.instance.RemoveCallback(this);
         if (var3 == null) {
            LuaManager.caller.pcall(LuaManager.thread, var2, "NotCompleted");
         } else {
            LuaManager.caller.pcall(LuaManager.thread, var2, new Object[]{var3, "NotCompleted"});
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
         ArrayList var4 = new ArrayList();

         for (int var5 = 0; var5 < var3; var5++) {
            SteamUGCDetails var6 = SteamWorkshop.instance.GetQueryUGCResult(var1, var5);
            if (var6 != null) {
               var4.add(var6);
            }
         }

         SteamWorkshop.instance.ReleaseQueryUGCRequest(var1);
         if (this.arg1 == null) {
            LuaManager.caller.pcall(LuaManager.thread, this.functionObj, new Object[]{"Completed", var4});
         } else {
            LuaManager.caller.pcall(LuaManager.thread, this.functionObj, new Object[]{this.arg1, "Completed", var4});
         }
      }
   }

   public void onItemQueryNotCompleted(long var1, int var3) {
      if (var1 == this.handle) {
         SteamWorkshop.instance.RemoveCallback(this);
         SteamWorkshop.instance.ReleaseQueryUGCRequest(var1);
         if (this.arg1 == null) {
            LuaManager.caller.pcall(LuaManager.thread, this.functionObj, "NotCompleted");
         } else {
            LuaManager.caller.pcall(LuaManager.thread, this.functionObj, new Object[]{this.arg1, "NotCompleted"});
         }
      }
   }
}
