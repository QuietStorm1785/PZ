package zombie.audio;

import zombie.audio.ObjectAmbientEmitters.PerObjectLogic;

public final class ObjectAmbientEmitters$TentAmbianceLogic extends PerObjectLogic {
   public boolean shouldPlaySound() {
      return this.object.sprite != null
         && this.object.sprite.getName() != null
         && this.object.sprite.getName().startsWith("camping_01")
         && (this.object.sprite.tileSheetIndex == 0 || this.object.sprite.tileSheetIndex == 3);
   }

   public String getSoundName() {
      return "TentAmbiance";
   }

   public void startPlaying(BaseSoundEmitter var1, long var2) {
   }

   public void stopPlaying(BaseSoundEmitter var1, long var2) {
   }

   public void checkParameters(BaseSoundEmitter var1, long var2) {
   }
}
