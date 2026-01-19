package zombie.core.skinnedmodel.model;

import org.lwjgl.opengl.GL11;
import zombie.core.SpriteRenderer;
import zombie.core.skinnedmodel.model.WorldItemAtlas.AtlasEntry;
import zombie.core.skinnedmodel.model.WorldItemAtlas.ItemTexture;
import zombie.core.textures.TextureDraw.GenericDrawer;

final class WorldItemAtlas$ItemTextureDrawer extends GenericDrawer {
   ItemTexture itemTexture;
   float x;
   float y;
   float r;
   float g;
   float b;
   float a;

   private WorldItemAtlas$ItemTextureDrawer() {
   }

   WorldItemAtlas$ItemTextureDrawer init(ItemTexture var1, float var2, float var3, float var4, float var5, float var6, float var7) {
      this.itemTexture = var1;
      this.x = var2;
      this.y = var3;
      this.r = var4;
      this.g = var5;
      this.b = var6;
      this.a = var7;
      return this;
   }

   public void render() {
      AtlasEntry var1 = this.itemTexture.entry;
      if (var1 != null && var1.ready && var1.tex.isReady()) {
         int var2 = (int)(this.x - (var1.w / 2.0F - var1.offsetX) / 2.5F);
         int var3 = (int)(this.y - (var1.h / 2.0F - var1.offsetY) / 2.5F);
         int var4 = (int)(var1.w / 2.5F);
         int var5 = (int)(var1.h / 2.5F);
         var1.tex.bind();
         GL11.glBegin(7);
         GL11.glColor4f(this.r, this.g, this.b, this.a);
         GL11.glTexCoord2f(var1.tex.xStart, var1.tex.yStart);
         GL11.glVertex2i(var2, var3);
         GL11.glTexCoord2f(var1.tex.xEnd, var1.tex.yStart);
         GL11.glVertex2i(var2 + var4, var3);
         GL11.glTexCoord2f(var1.tex.xEnd, var1.tex.yEnd);
         GL11.glVertex2i(var2 + var4, var3 + var5);
         GL11.glTexCoord2f(var1.tex.xStart, var1.tex.yEnd);
         GL11.glVertex2i(var2, var3 + var5);
         GL11.glColor4f(1.0F, 1.0F, 1.0F, 1.0F);
         GL11.glEnd();
         SpriteRenderer.ringBuffer.restoreBoundTextures = true;
      }
   }

   public void postRender() {
      this.itemTexture = null;
      WorldItemAtlas.instance.itemTextureDrawerPool.release(this);
   }
}
