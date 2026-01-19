package zombie.core.skinnedmodel.model;

import zombie.core.SpriteRenderer;
import zombie.core.skinnedmodel.model.WorldItemAtlas.AtlasEntry;
import zombie.core.skinnedmodel.model.WorldItemAtlas.ItemParams;
import zombie.core.skinnedmodel.model.WorldItemAtlas.ItemTextureDrawer;
import zombie.inventory.InventoryItem;

public final class WorldItemAtlas$ItemTexture {
   final ItemParams itemParams = new ItemParams();
   AtlasEntry entry;

   public boolean isStillValid(InventoryItem var1) {
      return this.entry == null ? false : this.itemParams.isStillValid(var1);
   }

   public boolean isRenderMainOK() {
      return this.entry.bRenderMainOK;
   }

   public boolean isTooBig() {
      return this.entry.bTooBig;
   }

   public void render(float var1, float var2, float var3, float var4, float var5, float var6) {
      if (this.entry.ready && this.entry.tex.isReady()) {
         SpriteRenderer.instance
            .m_states
            .getPopulatingActiveState()
            .render(
               this.entry.tex,
               var1 - (this.entry.w / 2.0F - this.entry.offsetX) / 2.5F,
               var2 - (this.entry.h / 2.0F - this.entry.offsetY) / 2.5F,
               this.entry.w / 2.5F,
               this.entry.h / 2.5F,
               var3,
               var4,
               var5,
               var6,
               null
            );
      } else {
         SpriteRenderer.instance
            .drawGeneric(((ItemTextureDrawer)WorldItemAtlas.instance.itemTextureDrawerPool.alloc()).init(this, var1, var2, var3, var4, var5, var6));
      }
   }

   void Reset() {
      this.itemParams.Reset();
      this.entry = null;
   }
}
