package zombie.vehicles;

import org.joml.Matrix4f;
import zombie.popman.ObjectPool;
import zombie.vehicles.UI3DScene.SceneObject;

class UI3DScene$SceneObjectRenderData {
   SceneObject m_object;
   final Matrix4f m_transform = new Matrix4f();
   private static final ObjectPool<UI3DScene$SceneObjectRenderData> s_pool = new ObjectPool(UI3DScene$SceneObjectRenderData::new);

   private UI3DScene$SceneObjectRenderData() {
   }

   UI3DScene$SceneObjectRenderData init(SceneObject var1) {
      this.m_object = var1;
      var1.getGlobalTransform(this.m_transform);
      return this;
   }

   void release() {
      s_pool.release(this);
   }
}
