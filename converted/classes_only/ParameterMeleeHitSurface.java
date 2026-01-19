package zombie.audio.parameters;

import zombie.audio.FMODLocalParameter;
import zombie.audio.parameters.ParameterMeleeHitSurface.Material;
import zombie.characters.IsoGameCharacter;

public final class ParameterMeleeHitSurface extends FMODLocalParameter {
   private final IsoGameCharacter character;
   private Material material = Material.Default;

   public ParameterMeleeHitSurface(IsoGameCharacter var1) {
      super("MeleeHitSurface");
      this.character = var1;
   }

   public float calculateCurrentValue() {
      return this.getMaterial().label;
   }

   private Material getMaterial() {
      return this.material;
   }

   public void setMaterial(Material var1) {
      this.material = var1;
   }
}
