package zombie;

import fmod.fmod.FMOD_STUDIO_EVENT_CALLBACK;
import zombie.debug.DebugLog;
import zombie.iso.IsoWorld;

class AmbientStreamManager$1 extends FMOD_STUDIO_EVENT_CALLBACK {
   AmbientStreamManager$1(AmbientStreamManager var1) {
      this.this$0 = var1;
   }

   public void timelineMarker(long var1, String var3, int var4) {
      DebugLog.Sound.debugln("timelineMarker %s %d", var3, var4);
      if ("ElectricityOff".equals(var3)) {
         IsoWorld.instance.setHydroPowerOn(false);
         this.this$0.checkHaveElectricity();
      }
   }
}
