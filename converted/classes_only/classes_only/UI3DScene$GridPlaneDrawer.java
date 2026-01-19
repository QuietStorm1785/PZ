package zombie.vehicles;

import org.lwjgl.opengl.GL11;
import zombie.core.Core;
import zombie.core.opengl.PZGLUtil;
import zombie.core.textures.TextureDraw.GenericDrawer;
import zombie.vehicles.UI3DScene.GridPlane;
import zombie.vehicles.UI3DScene.StateData;

final class UI3DScene$GridPlaneDrawer extends GenericDrawer {
   final UI3DScene m_scene;

   UI3DScene$GridPlaneDrawer(UI3DScene var1, UI3DScene var2) {
      this.this$0 = var1;
      this.m_scene = var2;
   }

   public void render() {
      StateData var1 = this.this$0.stateDataRender();
      PZGLUtil.pushAndLoadMatrix(5889, var1.m_projection);
      PZGLUtil.pushAndLoadMatrix(5888, var1.m_modelView);
      GL11.glPushAttrib(2048);
      GL11.glViewport(
         this.this$0.getAbsoluteX().intValue(),
         Core.getInstance().getScreenHeight() - this.this$0.getAbsoluteY().intValue() - this.this$0.getHeight().intValue(),
         this.this$0.getWidth().intValue(),
         this.this$0.getHeight().intValue()
      );
      float var2 = 5.0F;
      UI3DScene.vboLines.setMode(4);
      UI3DScene.vboLines.setDepthTest(true);
      if (this.m_scene.m_gridPlane == GridPlane.XZ) {
         UI3DScene.vboLines.addTriangle(-var2, 0.0F, -var2, var2, 0.0F, -var2, -var2, 0.0F, var2, 0.5F, 0.5F, 0.5F, 1.0F);
         UI3DScene.vboLines.addTriangle(var2, 0.0F, var2, -var2, 0.0F, var2, var2, 0.0F, -var2, 0.5F, 0.5F, 0.5F, 1.0F);
      }

      UI3DScene.vboLines.setMode(1);
      UI3DScene.vboLines.setDepthTest(false);
      GL11.glPopAttrib();
      PZGLUtil.popMatrix(5889);
      PZGLUtil.popMatrix(5888);
   }
}
