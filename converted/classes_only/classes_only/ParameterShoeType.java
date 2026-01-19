package zombie.audio.parameters;

import zombie.audio.FMODLocalParameter;
import zombie.audio.parameters.ParameterShoeType.ShoeType;
import zombie.characters.IsoGameCharacter;
import zombie.core.skinnedmodel.visual.ItemVisual;
import zombie.core.skinnedmodel.visual.ItemVisuals;
import zombie.scripting.objects.Item;

public final class ParameterShoeType extends FMODLocalParameter {
   private static final ItemVisuals tempItemVisuals = new ItemVisuals();
   private final IsoGameCharacter character;
   private ShoeType shoeType = null;

   public ParameterShoeType(IsoGameCharacter var1) {
      super("ShoeType");
      this.character = var1;
   }

   public float calculateCurrentValue() {
      if (this.shoeType == null) {
         this.shoeType = this.getShoeType();
      }

      return this.shoeType.label;
   }

   private ShoeType getShoeType() {
      this.character.getItemVisuals(tempItemVisuals);
      Item var1 = null;

      for (int var2 = 0; var2 < tempItemVisuals.size(); var2++) {
         ItemVisual var3 = (ItemVisual)tempItemVisuals.get(var2);
         Item var4 = var3.getScriptItem();
         if (var4 != null && "Shoes".equals(var4.getBodyLocation())) {
            var1 = var4;
            break;
         }
      }

      if (var1 == null) {
         return ShoeType.Barefoot;
      } else {
         String var5 = var1.getName();
         if (var5.contains("Boots") || var5.contains("Wellies")) {
            return ShoeType.Boots;
         } else if (var5.contains("FlipFlop")) {
            return ShoeType.FlipFlops;
         } else if (var5.contains("Slippers")) {
            return ShoeType.Slippers;
         } else {
            return var5.contains("Trainer") ? ShoeType.Sneakers : ShoeType.Shoes;
         }
      }
   }

   public void setShoeType(ShoeType var1) {
      this.shoeType = var1;
   }
}
