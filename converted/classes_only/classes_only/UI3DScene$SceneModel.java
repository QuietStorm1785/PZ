package zombie.vehicles;

import java.util.Objects;
import org.joml.Matrix4f;
import org.joml.Vector3f;
import zombie.core.SpriteRenderer;
import zombie.core.skinnedmodel.model.Model;
import zombie.scripting.objects.ModelAttachment;
import zombie.scripting.objects.ModelScript;
import zombie.vehicles.UI3DScene.ModelRenderData;
import zombie.vehicles.UI3DScene.SceneObject;
import zombie.vehicles.UI3DScene.SceneObjectRenderData;

final class UI3DScene$SceneModel extends SceneObject {
   ModelScript m_modelScript;
   Model m_model;
   boolean m_useWorldAttachment = false;
   boolean m_weaponRotationHack = false;

   UI3DScene$SceneModel(UI3DScene var1, String var2, ModelScript var3, Model var4) {
      super(var1, var2);
      Objects.requireNonNull(var3);
      Objects.requireNonNull(var4);
      this.m_modelScript = var3;
      this.m_model = var4;
   }

   SceneObjectRenderData renderMain() {
      if (!this.m_model.isReady()) {
         return null;
      } else {
         ModelRenderData var1 = (ModelRenderData)ModelRenderData.s_pool.alloc();
         var1.initModel(this);
         SpriteRenderer.instance.drawGeneric(var1.m_drawer);
         return var1;
      }
   }

   Matrix4f getLocalTransform(Matrix4f var1) {
      super.getLocalTransform(var1);
      return var1;
   }

   Matrix4f getAttachmentTransform(String var1, Matrix4f var2) {
      var2.identity();
      ModelAttachment var3 = this.m_modelScript.getAttachmentById(var1);
      if (var3 == null) {
         return var2;
      } else {
         var2.translation(var3.getOffset());
         Vector3f var4 = var3.getRotate();
         var2.rotateXYZ(var4.x * (float) (Math.PI / 180.0), var4.y * (float) (Math.PI / 180.0), var4.z * (float) (Math.PI / 180.0));
         return var2;
      }
   }
}
