package zombie.network;

import java.io.IOException;
import se.krka.kahlua.vm.JavaFunction;
import se.krka.kahlua.vm.LuaCallFrame;
import zombie.debug.DebugLog;
import zombie.debug.DebugType;

class CoopMaster$2 implements JavaFunction {
   CoopMaster$2(CoopMaster var1) {
      this.this$0 = var1;
   }

   public int call(LuaCallFrame var1, int var2) {
      boolean var3 = false;
      if (var2 == 4) {
         Object var4 = var1.get(1);
         Object var5 = var1.get(2);
         Object var6 = var1.get(3);
         if (!(var4 instanceof String) || !(var5 instanceof String) || !(var6 instanceof Double)) {
            return 0;
         }

         try {
            this.this$0.softreset((String)var4, (String)var5, ((Double)var6).intValue());
            var3 = true;
         } catch (IOException var8) {
            var8.printStackTrace();
         }
      } else {
         DebugLog.log(DebugType.Network, "[CoopMaster] wrong number of arguments: " + var2);
      }

      var1.push(var3);
      return 1;
   }
}
