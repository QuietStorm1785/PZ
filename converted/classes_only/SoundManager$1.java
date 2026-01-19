package zombie;

import fmod.fmod.FMOD_STUDIO_EVENT_CALLBACK;
import zombie.debug.DebugLog;
import zombie.gameStates.MainScreenState;

class SoundManager$1 extends FMOD_STUDIO_EVENT_CALLBACK {
   SoundManager$1(SoundManager var1) {
      this.this$0 = var1;
   }

   public void timelineMarker(long var1, String var3, int var4) {
      DebugLog.Sound.debugln("timelineMarker %s %d", var3, var4);
      if ("Lightning".equals(var3)) {
         MainScreenState.getInstance().lightningTimelineMarker = true;
      }
   }
}
