package zombie.core.skinnedmodel;

import zombie.core.skinnedmodel.visual.HumanVisual;
import zombie.core.skinnedmodel.visual.IHumanVisual;
import zombie.core.skinnedmodel.visual.ItemVisuals;

final class DeadBodyAtlas$CharacterTextureVisual implements IHumanVisual {
   final HumanVisual humanVisual = new HumanVisual(this);
   boolean bFemale;

   DeadBodyAtlas$CharacterTextureVisual(boolean var1) {
      this.bFemale = var1;
      this.humanVisual.setHairModel("");
      this.humanVisual.setBeardModel("");
   }

   public HumanVisual getHumanVisual() {
      return this.humanVisual;
   }

   public void getItemVisuals(ItemVisuals var1) {
      var1.clear();
   }

   public boolean isFemale() {
      return this.bFemale;
   }

   public boolean isZombie() {
      return true;
   }

   public boolean isSkeleton() {
      return false;
   }
}
