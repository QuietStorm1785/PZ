package zombie.vehicles;

import org.joml.Matrix4f;
import zombie.vehicles.UI3DScene.SceneCharacter;
import zombie.vehicles.UI3DScene.SceneObject;
import zombie.vehicles.UI3DScene.SceneObjectRenderData;

final class UI3DScene$OriginBone extends SceneObject {
   SceneCharacter m_character;
   String m_boneName;

   UI3DScene$OriginBone(UI3DScene var1) {
      super(var1, "OriginBone");
   }

   SceneObjectRenderData renderMain() {
      return null;
   }

   Matrix4f getGlobalTransform(Matrix4f var1) {
      return this.m_character.getBoneMatrix(this.m_boneName, var1);
   }
}
