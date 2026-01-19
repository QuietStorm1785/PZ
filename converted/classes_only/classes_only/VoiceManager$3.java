package zombie.core.raknet;

import fmod.FMOD_DriverInfo;
import fmod.javafmod;
import se.krka.kahlua.vm.JavaFunction;
import se.krka.kahlua.vm.KahluaTable;
import se.krka.kahlua.vm.LuaCallFrame;
import zombie.core.Core;

class VoiceManager$3 implements JavaFunction {
   VoiceManager$3(VoiceManager var1) {
      this.this$0 = var1;
   }

   public int call(LuaCallFrame var1, int var2) {
      if (!Core.SoundDisabled && !VoiceManager.VoipDisabled) {
         int var7 = javafmod.FMOD_System_GetRecordNumDrivers();
         KahluaTable var4 = var1.getPlatform().newTable();

         for (int var5 = 0; var5 < var7; var5++) {
            FMOD_DriverInfo var6 = new FMOD_DriverInfo();
            javafmod.FMOD_System_GetRecordDriverInfo(var5, var6);
            var4.rawset(var5 + 1, var6.name);
         }

         var1.push(var4);
         return 1;
      } else {
         KahluaTable var3 = var1.getPlatform().newTable();
         var1.push(var3);
         return 1;
      }
   }
}
