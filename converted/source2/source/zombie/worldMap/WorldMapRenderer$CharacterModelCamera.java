package zombie.worldMap;

import org.joml.Matrix4f;
import zombie.core.opengl.PZGLUtil;
import zombie.core.skinnedmodel.ModelCamera;

final class WorldMapRenderer$CharacterModelCamera extends ModelCamera {
   float m_worldScale;
   float m_angle;
   float m_playerX;
   float m_playerY;
   boolean m_bVehicle;

   private WorldMapRenderer$CharacterModelCamera() {
   }

   public void Begin() {
      Matrix4f var1 = WorldMapRenderer.allocMatrix4f();
      var1.identity();
      var1.translate(this.m_playerX * this.m_worldScale, this.m_playerY * this.m_worldScale, 0.0F);
      var1.rotateX((float) (Math.PI / 2));
      var1.rotateY(this.m_angle + (float) (Math.PI * 3.0 / 2.0));
      if (this.m_bVehicle) {
         var1.scale(this.m_worldScale);
      } else {
         var1.scale(1.5F * this.m_worldScale);
      }

      PZGLUtil.pushAndMultMatrix(5888, var1);
      WorldMapRenderer.releaseMatrix4f(var1);
   }

   public void End() {
      PZGLUtil.popMatrix(5888);
   }
}
