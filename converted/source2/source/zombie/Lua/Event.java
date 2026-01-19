package zombie.Lua;

import java.util.ArrayList;
import se.krka.kahlua.integration.LuaCaller;
import se.krka.kahlua.vm.KahluaTable;
import se.krka.kahlua.vm.LuaClosure;
import se.krka.kahlua.vm.Platform;
import zombie.Lua.Event.Add;
import zombie.Lua.Event.Remove;
import zombie.core.logger.ExceptionLogger;
import zombie.debug.DebugLog;
import zombie.debug.DebugOptions;

public final class Event {
   public static final int ADD = 0;
   public static final int NUM_FUNCTIONS = 1;
   private final Add add;
   private final Remove remove;
   public final ArrayList<LuaClosure> callbacks = new ArrayList<>();
   public String name;
   private int index = 0;

   public boolean trigger(KahluaTable var1, LuaCaller var2, Object[] var3) {
      if (this.callbacks.isEmpty()) {
         return false;
      } else if (DebugOptions.instance.Checks.SlowLuaEvents.getValue()) {
         for (int var12 = 0; var12 < this.callbacks.size(); var12++) {
            try {
               LuaClosure var5 = this.callbacks.get(var12);
               long var6 = System.nanoTime();
               var2.protectedCallVoid(LuaManager.thread, var5, var3);
               double var8 = (System.nanoTime() - var6) / 1000000.0;
               if (var8 > 250.0) {
                  DebugLog.Lua.warn("SLOW Lua event callback %s %s %dms", new Object[]{var5.prototype.file, var5, (int)var8});
               }
            } catch (Exception var10) {
               ExceptionLogger.logException(var10);
            }
         }

         return true;
      } else {
         for (int var4 = 0; var4 < this.callbacks.size(); var4++) {
            try {
               var2.protectedCallVoid(LuaManager.thread, this.callbacks.get(var4), var3);
            } catch (Exception var11) {
               ExceptionLogger.logException(var11);
            }
         }

         return true;
      }
   }

   public Event(String var1, int var2) {
      this.index = var2;
      this.name = var1;
      this.add = new Add(this);
      this.remove = new Remove(this);
   }

   public void register(Platform var1, KahluaTable var2) {
      KahluaTable var3 = var1.newTable();
      var3.rawset("Add", this.add);
      var3.rawset("Remove", this.remove);
      var2.rawset(this.name, var3);
   }
}
