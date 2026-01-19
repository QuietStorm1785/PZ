package zombie.vehicles;

import org.joml.Matrix4f;
import org.lwjgl.opengl.GL11;
import zombie.core.Core;
import zombie.core.opengl.PZGLUtil;
import zombie.vehicles.UI3DScene.SceneModelCamera;
import zombie.vehicles.UI3DScene.StateData;

final class UI3DScene$CharacterSceneModelCamera extends SceneModelCamera {
   private UI3DScene$CharacterSceneModelCamera(UI3DScene var1) {
      super(var1);
      this.this$0 = var1;
   }

   public void Begin() {
      StateData var1 = this.this$0.stateDataRender();
      GL11.glViewport(
         this.this$0.getAbsoluteX().intValue(),
         Core.getInstance().getScreenHeight() - this.this$0.getAbsoluteY().intValue() - this.this$0.getHeight().intValue(),
         this.this$0.getWidth().intValue(),
         this.this$0.getHeight().intValue()
      );
      PZGLUtil.pushAndLoadMatrix(5889, var1.m_projection);
      Matrix4f var2 = UI3DScene.allocMatrix4f();
      var2.set(var1.m_modelView);
      var2.mul(this.m_renderData.m_transform);
      PZGLUtil.pushAndLoadMatrix(5888, var2);
      UI3DScene.releaseMatrix4f(var2);
   }

   public void End() {
      PZGLUtil.popMatrix(5889);
      PZGLUtil.popMatrix(5888);
   }
}
