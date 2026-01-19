package zombie.audio;

import fmod.fmod.FMODSoundEmitter;
import zombie.audio.ObjectAmbientEmitters.PerObjectLogic;
import zombie.audio.parameters.ParameterCurrentZone;
import zombie.util.Type;

public final class ObjectAmbientEmitters$TreeAmbianceLogic extends PerObjectLogic {
   public boolean shouldPlaySound() {
      return true;
   }

   public String getSoundName() {
      return "TreeAmbiance";
   }

   public void startPlaying(BaseSoundEmitter var1, long var2) {
      FMODSoundEmitter var4 = (FMODSoundEmitter)Type.tryCastTo(var1, FMODSoundEmitter.class);
      if (var4 != null) {
         var4.addParameter(new ParameterCurrentZone(this.object));
      }

      var1.playAmbientLoopedImpl("BirdInTree");
   }

   public void stopPlaying(BaseSoundEmitter var1, long var2) {
      var1.stopOrTriggerSoundByName("BirdInTree");
   }

   public void checkParameters(BaseSoundEmitter var1, long var2) {
   }
}
