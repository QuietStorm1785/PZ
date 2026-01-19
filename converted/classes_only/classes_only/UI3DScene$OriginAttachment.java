package zombie.vehicles;

import org.joml.Matrix4f;
import zombie.vehicles.UI3DScene.SceneObject;
import zombie.vehicles.UI3DScene.SceneObjectRenderData;

final class UI3DScene$OriginAttachment extends SceneObject {
   SceneObject m_object;
   String m_attachmentName;

   UI3DScene$OriginAttachment(UI3DScene var1) {
      super(var1, "OriginAttachment");
   }

   SceneObjectRenderData renderMain() {
      return null;
   }

   Matrix4f getGlobalTransform(Matrix4f var1) {
      return this.m_object.getAttachmentTransform(this.m_attachmentName, var1);
   }
}
