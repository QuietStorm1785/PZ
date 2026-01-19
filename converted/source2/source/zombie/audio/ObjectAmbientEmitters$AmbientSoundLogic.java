package zombie.audio;

import zombie.GameSounds;
import zombie.audio.ObjectAmbientEmitters.PerObjectLogic;
import zombie.audio.ObjectAmbientEmitters.PowerPolicy;
import zombie.core.properties.PropertyContainer;
import zombie.iso.IsoObject;
import zombie.iso.IsoWorld;

public final class ObjectAmbientEmitters$AmbientSoundLogic extends PerObjectLogic {
   PowerPolicy powerPolicy = PowerPolicy.NotRequired;
   boolean bHasGeneratorParameter = false;

   public PerObjectLogic init(IsoObject var1) {
      super.init(var1);
      String var2 = this.getSoundName();
      this.powerPolicy = ObjectAmbientEmitters.getInstance().powerPolicyMap.getOrDefault(var2, PowerPolicy.NotRequired);
      if (this.powerPolicy != PowerPolicy.NotRequired) {
         GameSound var3 = GameSounds.getSound(var2);
         this.bHasGeneratorParameter = var3 != null && var3.numClipsUsingParameter("Generator") > 0;
      }

      return this;
   }

   public boolean shouldPlaySound() {
      if (this.powerPolicy == PowerPolicy.InteriorHydro) {
         boolean var1 = this.object.square.haveElectricity() || IsoWorld.instance.isHydroPowerOn() && this.object.square.getRoom() != null;
         if (!var1) {
            return false;
         }
      }

      if (this.powerPolicy == PowerPolicy.ExteriorOK) {
         boolean var2 = this.object.square.haveElectricity() || IsoWorld.instance.isHydroPowerOn();
         if (!var2) {
            return false;
         }
      }

      if (this.powerPolicy != PowerPolicy.NotRequired && !IsoWorld.instance.isHydroPowerOn() && !this.bHasGeneratorParameter) {
         return false;
      } else {
         PropertyContainer var3 = this.object.getProperties();
         return var3 != null && var3.Is("AmbientSound");
      }
   }

   public String getSoundName() {
      return this.object.getProperties().Val("AmbientSound");
   }

   public void startPlaying(BaseSoundEmitter var1, long var2) {
   }

   public void stopPlaying(BaseSoundEmitter var1, long var2) {
      this.parameterValue1 = Float.NaN;
   }

   public void checkParameters(BaseSoundEmitter var1, long var2) {
      if (this.powerPolicy != PowerPolicy.NotRequired) {
         this.setParameterValue1(var1, var2, "Generator", IsoWorld.instance.isHydroPowerOn() ? 0.0F : 1.0F);
      }
   }
}
