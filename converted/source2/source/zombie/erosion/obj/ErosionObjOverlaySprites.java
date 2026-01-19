package zombie.erosion.obj;

import zombie.erosion.obj.ErosionObjOverlaySprites.Sprite;
import zombie.erosion.obj.ErosionObjOverlaySprites.Stage;
import zombie.iso.sprite.IsoSprite;
import zombie.iso.sprite.IsoSpriteInstance;

public final class ErosionObjOverlaySprites {
   public String name;
   public int stages;
   private Stage[] sprites;

   public ErosionObjOverlaySprites(int var1, String var2) {
      this.name = var2;
      this.stages = var1;
      this.sprites = new Stage[this.stages];

      for (int var3 = 0; var3 < this.stages; var3++) {
         this.sprites[var3] = new Stage();
      }
   }

   public IsoSprite getSprite(int var1, int var2) {
      return this.sprites[var1].seasons[var2].getSprite();
   }

   public IsoSpriteInstance getSpriteInstance(int var1, int var2) {
      return this.sprites[var1].seasons[var2].getInstance();
   }

   public void setSprite(int var1, String var2, int var3) {
      this.sprites[var1].seasons[var3] = new Sprite(var2);
   }
}
