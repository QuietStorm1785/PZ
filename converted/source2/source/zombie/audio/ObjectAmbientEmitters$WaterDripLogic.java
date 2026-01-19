package zombie.audio;

import zombie.audio.ObjectAmbientEmitters.PerObjectLogic;
import zombie.iso.SpriteDetails.IsoFlagType;

public final class ObjectAmbientEmitters$WaterDripLogic extends PerObjectLogic {
   public boolean shouldPlaySound() {
      return this.object.sprite != null && this.object.sprite.getProperties().Is(IsoFlagType.waterPiped) && this.object.getWaterAmount() > 0.0F;
   }

   public String getSoundName() {
      return "WaterDrip";
   }

   public void startPlaying(BaseSoundEmitter var1, long var2) {
      if (this.object.sprite != null && this.object.sprite.getProperties().Is("SinkType")) {
         String var4 = this.object.sprite.getProperties().Val("SinkType");

         byte var5 = switch (var4) {
            case "Ceramic" -> 1;
            case "Metal" -> 2;
            default -> 0;
         };
         this.setParameterValue1(var1, var2, "SinkType", var5);
      }
   }

   public void stopPlaying(BaseSoundEmitter var1, long var2) {
      this.parameterValue1 = Float.NaN;
   }

   public void checkParameters(BaseSoundEmitter var1, long var2) {
   }
}
