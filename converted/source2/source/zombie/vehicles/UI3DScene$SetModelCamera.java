package zombie.vehicles;

import zombie.core.skinnedmodel.ModelCamera;
import zombie.core.textures.TextureDraw.GenericDrawer;
import zombie.vehicles.UI3DScene.SceneModelCamera;
import zombie.vehicles.UI3DScene.SceneObjectRenderData;

final class UI3DScene$SetModelCamera extends GenericDrawer {
   SceneModelCamera m_camera;
   SceneObjectRenderData m_renderData;

   private UI3DScene$SetModelCamera() {
   }

   UI3DScene$SetModelCamera init(SceneModelCamera var1, SceneObjectRenderData var2) {
      this.m_camera = var1;
      this.m_renderData = var2;
      return this;
   }

   public void render() {
      this.m_camera.m_renderData = this.m_renderData;
      ModelCamera.instance = this.m_camera;
   }

   public void postRender() {
      UI3DScene.s_SetModelCameraPool.release(this);
   }
}
