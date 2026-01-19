package zombie.vehicles;

import zombie.popman.ObjectPool;
import zombie.vehicles.UI3DScene.CharacterDrawer;
import zombie.vehicles.UI3DScene.SceneCharacter;
import zombie.vehicles.UI3DScene.SceneObjectRenderData;

class UI3DScene$CharacterRenderData extends SceneObjectRenderData {
   final CharacterDrawer m_drawer = new CharacterDrawer();
   private static final ObjectPool<UI3DScene$CharacterRenderData> s_pool = new ObjectPool(UI3DScene$CharacterRenderData::new);

   private UI3DScene$CharacterRenderData() {
   }

   SceneObjectRenderData initCharacter(SceneCharacter var1) {
      this.m_drawer.init(var1, this);
      super.init(var1);
      return this;
   }

   void release() {
      s_pool.release(this);
   }
}
