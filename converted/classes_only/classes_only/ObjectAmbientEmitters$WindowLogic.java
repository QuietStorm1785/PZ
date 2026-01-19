package zombie.audio;

import zombie.audio.ObjectAmbientEmitters.PerObjectLogic;
import zombie.iso.objects.IsoWindow;
import zombie.util.Type;

public final class ObjectAmbientEmitters$WindowLogic extends PerObjectLogic {
   public boolean shouldPlaySound() {
      return true;
   }

   public String getSoundName() {
      return "WindowAmbiance";
   }

   public void startPlaying(BaseSoundEmitter var1, long var2) {
   }

   public void stopPlaying(BaseSoundEmitter var1, long var2) {
      this.parameterValue1 = Float.NaN;
   }

   public void checkParameters(BaseSoundEmitter var1, long var2) {
      IsoWindow var4 = (IsoWindow)Type.tryCastTo(this.object, IsoWindow.class);
      float var5 = !var4.IsOpen() && !var4.isDestroyed() ? 0.0F : 1.0F;
      this.setParameterValue1(var1, var2, "DoorWindowOpen", var5);
   }
}
