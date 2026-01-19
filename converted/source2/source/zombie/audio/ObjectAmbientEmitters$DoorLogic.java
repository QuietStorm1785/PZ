package zombie.audio;

import zombie.audio.ObjectAmbientEmitters.PerObjectLogic;
import zombie.iso.objects.IsoDoor;
import zombie.util.Type;

public final class ObjectAmbientEmitters$DoorLogic extends PerObjectLogic {
   public boolean shouldPlaySound() {
      return true;
   }

   public String getSoundName() {
      return "DoorAmbiance";
   }

   public void startPlaying(BaseSoundEmitter var1, long var2) {
   }

   public void stopPlaying(BaseSoundEmitter var1, long var2) {
      this.parameterValue1 = Float.NaN;
   }

   public void checkParameters(BaseSoundEmitter var1, long var2) {
      IsoDoor var4 = (IsoDoor)Type.tryCastTo(this.object, IsoDoor.class);
      float var5 = var4.IsOpen() ? 1.0F : 0.0F;
      this.setParameterValue1(var1, var2, "DoorWindowOpen", var5);
   }
}
