package zombie.Lua;

import se.krka.kahlua.luaj.compiler.LuaCompiler;
import se.krka.kahlua.vm.JavaFunction;
import se.krka.kahlua.vm.LuaCallFrame;
import se.krka.kahlua.vm.LuaClosure;

public final class Event$Remove implements JavaFunction {
   Event e;

   public Event$Remove(Event var1) {
      this.e = var1;
   }

   public int call(LuaCallFrame var1, int var2) {
      if (LuaCompiler.rewriteEvents) {
         return 0;
      } else {
         if (var1.get(0) instanceof LuaClosure var4) {
            this.e.callbacks.remove(var4);
         }

         return 0;
      }
   }
}
