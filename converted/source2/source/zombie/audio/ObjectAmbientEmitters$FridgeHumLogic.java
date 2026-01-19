package zombie.audio;

import zombie.audio.ObjectAmbientEmitters.PerObjectLogic;
import zombie.inventory.ItemContainer;
import zombie.iso.IsoWorld;

public final class ObjectAmbientEmitters$FridgeHumLogic extends PerObjectLogic {
   public boolean shouldPlaySound() {
      ItemContainer var1 = this.object.getContainerByEitherType("fridge", "freezer");
      return var1 != null && var1.isPowered();
   }

   public String getSoundName() {
      return "FridgeHum";
   }

   public void startPlaying(BaseSoundEmitter var1, long var2) {
   }

   public void stopPlaying(BaseSoundEmitter var1, long var2) {
      this.parameterValue1 = Float.NaN;
   }

   public void checkParameters(BaseSoundEmitter var1, long var2) {
      this.setParameterValue1(var1, var2, "Generator", IsoWorld.instance.isHydroPowerOn() ? 0.0F : 1.0F);
   }
}
