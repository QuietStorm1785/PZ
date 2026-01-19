package zombie.erosion.obj;

import zombie.erosion.ErosionMain;
import zombie.iso.sprite.IsoSprite;
import zombie.iso.sprite.IsoSpriteInstance;

final class ErosionObjOverlaySprites$Sprite {
   private final String sprite;

   public ErosionObjOverlaySprites$Sprite(String var1) {
      this.sprite = var1;
   }

   public IsoSprite getSprite() {
      return this.sprite != null ? ErosionMain.getInstance().getSpriteManager().getSprite(this.sprite) : null;
   }

   public IsoSpriteInstance getInstance() {
      return this.sprite != null ? ErosionMain.getInstance().getSpriteManager().getSprite(this.sprite).newInstance() : null;
   }
}
