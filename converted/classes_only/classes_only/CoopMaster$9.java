package zombie.network;

import se.krka.kahlua.vm.JavaFunction;
import se.krka.kahlua.vm.LuaCallFrame;

class CoopMaster$9 implements JavaFunction {
   CoopMaster$9(CoopMaster var1) {
      this.this$0 = var1;
   }

   public int call(LuaCallFrame var1, int var2) {
      var1.push(this.this$0.serverPort);
      return 1;
   }
}
