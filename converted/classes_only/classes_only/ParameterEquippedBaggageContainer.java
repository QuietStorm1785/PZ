package zombie.audio.parameters;

import zombie.audio.FMODLocalParameter;
import zombie.audio.parameters.ParameterEquippedBaggageContainer.ContainerType;
import zombie.characters.IsoGameCharacter;

public final class ParameterEquippedBaggageContainer extends FMODLocalParameter {
   private final IsoGameCharacter character;
   private ContainerType containerType = ContainerType.None;

   public ParameterEquippedBaggageContainer(IsoGameCharacter var1) {
      super("EquippedBaggageContainer");
      this.character = var1;
   }

   public float calculateCurrentValue() {
      return this.containerType.label;
   }

   public void setContainerType(ContainerType var1) {
      this.containerType = var1;
   }

   public void setContainerType(String var1) {
      if (var1 != null) {
         try {
            this.containerType = ContainerType.valueOf(var1);
         } catch (IllegalArgumentException var3) {
         }
      }
   }
}
