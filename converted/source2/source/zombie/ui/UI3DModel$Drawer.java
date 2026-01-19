package zombie.ui;

import zombie.core.Core;
import zombie.core.textures.TextureDraw.GenericDrawer;

final class UI3DModel$Drawer extends GenericDrawer {
   int absX;
   int absY;
   float m_animPlayerAngle;
   boolean bRendered;

   private UI3DModel$Drawer(UI3DModel var1) {
      this.this$0 = var1;
   }

   public void init(int var1, int var2) {
      this.absX = var1;
      this.absY = var2;
      this.m_animPlayerAngle = this.this$0.animatedModel.getAnimationPlayer().getRenderedAngle();
      this.bRendered = false;
      float var3 = this.this$0.animatedModel.isIsometric() ? -0.45F : -0.5F;
      if (this.this$0.yOffset != 0.0F) {
         var3 = this.this$0.yOffset;
      }

      this.this$0.animatedModel.setOffset(this.this$0.xOffset, var3, 0.0F);
      this.this$0.animatedModel.renderMain();
   }

   public void render() {
      float var1 = this.this$0.animatedModel.isIsometric() ? 22.0F : 25.0F;
      if (this.this$0.zoom > 0.0F) {
         var1 -= this.this$0.zoom;
      }

      this.this$0
         .animatedModel
         .DoRender(this.absX, Core.height - this.absY - (int)this.this$0.height, (int)this.this$0.width, (int)this.this$0.height, var1, this.m_animPlayerAngle);
      this.bRendered = true;
   }

   public void postRender() {
      this.this$0.animatedModel.postRender(this.bRendered);
   }
}
