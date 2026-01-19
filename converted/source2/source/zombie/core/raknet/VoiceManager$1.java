package zombie.core.raknet;

import se.krka.kahlua.vm.JavaFunction;
import se.krka.kahlua.vm.LuaCallFrame;

class VoiceManager$1 implements JavaFunction {
   VoiceManager$1(VoiceManager var1) {
      this.this$0 = var1;
   }

   public int call(LuaCallFrame var1, int var2) {
      Object var3 = var1.get(1);
      VoiceManager.playerSetMute((String)var3);
      return 1;
   }
}
