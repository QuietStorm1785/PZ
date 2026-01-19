package zombie.network;

import se.krka.kahlua.vm.JavaFunction;
import se.krka.kahlua.vm.LuaCallFrame;

class CoopMaster$11 implements JavaFunction {
   CoopMaster$11(CoopMaster var1) {
      this.this$0 = var1;
   }

   public int call(LuaCallFrame var1, int var2) {
      Object var3 = var1.get(1);
      var1.push(this.this$0.getServerSaveFolder((String)var3));
      return 1;
   }
}
