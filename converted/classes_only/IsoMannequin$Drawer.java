package zombie.iso.objects;

import zombie.core.textures.TextureDraw.GenericDrawer;

final class IsoMannequin$Drawer extends GenericDrawer {
   float x;
   float y;
   float z;
   float m_animPlayerAngle;
   boolean bRendered;

   private IsoMannequin$Drawer(IsoMannequin var1) {
      this.this$0 = var1;
   }

   public void init(float var1, float var2, float var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      this.bRendered = false;
      this.this$0.animatedModel.renderMain();
      this.m_animPlayerAngle = this.this$0.animatedModel.getAnimationPlayer().getRenderedAngle();
   }

   public void render() {
      this.this$0.animatedModel.DoRenderToWorld(this.x, this.y, this.z, this.m_animPlayerAngle);
      this.bRendered = true;
   }

   public void postRender() {
      this.this$0.animatedModel.postRender(this.bRendered);
   }
}
