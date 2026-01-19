package zombie.iso.weather.fx;

import org.joml.Matrix4f;
import zombie.core.SpriteRenderer;
import zombie.core.math.PZMath;
import zombie.core.textures.TextureDraw.GenericDrawer;

final class IsoWeatherFX$Drawer extends GenericDrawer {
   static final Matrix4f s_matrix4f = new Matrix4f();
   final org.lwjgl.util.vector.Matrix4f m_mvp = new org.lwjgl.util.vector.Matrix4f();
   int m_width;
   int m_height;
   boolean m_bSet = false;

   private IsoWeatherFX$Drawer() {
   }

   void init(int var1, int var2) {
      if (var1 != this.m_width || var2 != this.m_height || !this.m_bSet) {
         this.m_width = var1;
         this.m_height = var2;
         this.m_bSet = false;
         s_matrix4f.setOrtho(0.0F, this.m_width, this.m_height, 0.0F, -1.0F, 1.0F);
         PZMath.convertMatrix(s_matrix4f, this.m_mvp);
         this.m_mvp.transpose();
         SpriteRenderer.instance.drawGeneric(this);
      }
   }

   public void render() {
      IsoWeatherFX.s_shader.getShaderProgram().setValue("u_mvp", this.m_mvp);
      this.m_bSet = true;
   }
}
