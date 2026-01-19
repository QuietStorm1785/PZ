package zombie.network;

import se.krka.kahlua.vm.JavaFunction;
import se.krka.kahlua.vm.LuaCallFrame;
import zombie.core.znet.SteamUtils;

class CoopMaster$7 implements JavaFunction {
   CoopMaster$7(CoopMaster var1) {
      this.this$0 = var1;
   }

   public int call(LuaCallFrame var1, int var2) {
      if (this.this$0.serverSteamID != null) {
         var1.push(SteamUtils.convertSteamIDToString(this.this$0.serverSteamID));
         return 1;
      } else {
         return 0;
      }
   }
}
