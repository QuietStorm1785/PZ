package zombie.vehicles;

import org.joml.Matrix4f;
import zombie.core.skinnedmodel.model.ModelInstanceRenderData;
import zombie.popman.ObjectPool;
import zombie.scripting.objects.ModelAttachment;
import zombie.vehicles.UI3DScene.ModelDrawer;
import zombie.vehicles.UI3DScene.SceneModel;
import zombie.vehicles.UI3DScene.SceneObjectRenderData;

class UI3DScene$ModelRenderData extends SceneObjectRenderData {
   final ModelDrawer m_drawer = new ModelDrawer();
   private static final ObjectPool<UI3DScene$ModelRenderData> s_pool = new ObjectPool(UI3DScene$ModelRenderData::new);

   private UI3DScene$ModelRenderData() {
   }

   SceneObjectRenderData initModel(SceneModel var1) {
      super.init(var1);
      if (var1.m_useWorldAttachment) {
         if (var1.m_weaponRotationHack) {
            this.m_transform.rotateXYZ(0.0F, (float) Math.PI, (float) (Math.PI / 2));
         }

         if (var1.m_modelScript != null) {
            ModelAttachment var2 = var1.m_modelScript.getAttachmentById("world");
            if (var2 != null) {
               Matrix4f var3 = ModelInstanceRenderData.makeAttachmentTransform(var2, UI3DScene.allocMatrix4f());
               var3.invert();
               this.m_transform.mul(var3);
               UI3DScene.releaseMatrix4f(var3);
            }
         }
      }

      if (var1.m_model.isReady() && var1.m_model.Mesh.m_transform != null) {
         var1.m_model.Mesh.m_transform.transpose();
         this.m_transform.mul(var1.m_model.Mesh.m_transform);
         var1.m_model.Mesh.m_transform.transpose();
      }

      if (var1.m_modelScript != null && var1.m_modelScript.scale != 1.0F) {
         this.m_transform.scale(var1.m_modelScript.scale);
      }

      this.m_drawer.init(var1, this);
      return this;
   }

   void release() {
      s_pool.release(this);
   }
}
