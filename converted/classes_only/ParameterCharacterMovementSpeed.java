package zombie.audio.parameters;

import zombie.audio.FMODLocalParameter;
import zombie.audio.parameters.ParameterCharacterMovementSpeed.MovementType;
import zombie.characters.IsoGameCharacter;

public final class ParameterCharacterMovementSpeed extends FMODLocalParameter {
   private final IsoGameCharacter character;
   private MovementType movementType = MovementType.Walk;

   public ParameterCharacterMovementSpeed(IsoGameCharacter var1) {
      super("CharacterMovementSpeed");
      this.character = var1;
   }

   public float calculateCurrentValue() {
      return this.movementType.label;
   }

   public void setMovementType(MovementType var1) {
      this.movementType = var1;
   }
}
