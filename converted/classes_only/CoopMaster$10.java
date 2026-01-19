package zombie.network;

import se.krka.kahlua.vm.JavaFunction;
import se.krka.kahlua.vm.LuaCallFrame;

class CoopMaster$10 implements JavaFunction {
   CoopMaster$10(CoopMaster var1) {
      this.this$0 = var1;
   }

   public int call(LuaCallFrame var1, int var2) {
      this.this$0.abortServer();
      return 0;
   }
}
