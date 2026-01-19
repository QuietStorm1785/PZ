package zombie.network;

import se.krka.kahlua.vm.JavaFunction;
import se.krka.kahlua.vm.LuaCallFrame;

class CoopMaster$4 implements JavaFunction {
   CoopMaster$4(CoopMaster var1) {
      this.this$0 = var1;
   }

   public int call(LuaCallFrame var1, int var2) {
      if (var2 == 4) {
         Object var3 = var1.get(1);
         Object var4 = var1.get(2);
         Object var5 = var1.get(3);
         if (var3 instanceof String && var4 instanceof String && var5 instanceof String) {
            this.this$0.sendMessage((String)var3, (String)var4, (String)var5);
         }
      } else if (var2 == 3) {
         Object var6 = var1.get(1);
         Object var7 = var1.get(2);
         if (var6 instanceof String && var7 instanceof String) {
            this.this$0.sendMessage((String)var6, (String)var7);
         }
      }

      return 0;
   }
}
