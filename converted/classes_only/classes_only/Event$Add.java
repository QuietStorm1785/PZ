package zombie.Lua;

import se.krka.kahlua.luaj.compiler.LuaCompiler;
import se.krka.kahlua.vm.JavaFunction;
import se.krka.kahlua.vm.LuaCallFrame;
import se.krka.kahlua.vm.LuaClosure;

public final class Event$Add implements JavaFunction {
   Event e;

   public Event$Add(Event var1) {
      this.e = var1;
   }

   public int call(LuaCallFrame var1, int var2) {
      if (LuaCompiler.rewriteEvents) {
         return 0;
      } else {
         Object var3 = var1.get(0);
         if (this.e.name.contains("CreateUI")) {
            boolean var4 = false;
         }

         if (var3 instanceof LuaClosure var5) {
            this.e.callbacks.add(var5);
         }

         return 0;
      }
   }
}
