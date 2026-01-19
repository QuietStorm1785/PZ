package zombie.randomizedWorld.randomizedBuilding;

import zombie.characters.IsoGameCharacter;
import zombie.characters.SurvivorDesc;
import zombie.core.skinnedmodel.visual.HumanVisual;
import zombie.core.skinnedmodel.visual.IHumanVisual;
import zombie.core.skinnedmodel.visual.ItemVisuals;
import zombie.iso.IsoCell;

public final class RandomizedBuildingBase$HumanCorpse extends IsoGameCharacter implements IHumanVisual {
   final HumanVisual humanVisual = new HumanVisual(this);
   final ItemVisuals itemVisuals = new ItemVisuals();
   public boolean isSkeleton = false;

   public RandomizedBuildingBase$HumanCorpse(IsoCell var1, float var2, float var3, float var4) {
      super(var1, var2, var3, var4);
      var1.getObjectList().remove(this);
      var1.getAddList().remove(this);
   }

   public void dressInNamedOutfit(String var1) {
      this.getHumanVisual().dressInNamedOutfit(var1, this.itemVisuals);
      this.getHumanVisual().synchWithOutfit(this.getHumanVisual().getOutfit());
   }

   public HumanVisual getHumanVisual() {
      return this.humanVisual;
   }

   public HumanVisual getVisual() {
      return this.humanVisual;
   }

   public void Dressup(SurvivorDesc var1) {
      this.wornItems.setFromItemVisuals(this.itemVisuals);
      this.wornItems.addItemsToItemContainer(this.inventory);
   }

   public boolean isSkeleton() {
      return this.isSkeleton;
   }
}
