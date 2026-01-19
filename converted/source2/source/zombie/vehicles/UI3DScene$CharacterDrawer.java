package zombie.vehicles;

import org.lwjgl.opengl.GL11;
import zombie.core.textures.TextureDraw.GenericDrawer;
import zombie.debug.DebugOptions;
import zombie.vehicles.UI3DScene.CharacterRenderData;
import zombie.vehicles.UI3DScene.SceneCharacter;

final class UI3DScene$CharacterDrawer extends GenericDrawer {
   SceneCharacter m_character;
   CharacterRenderData m_renderData;
   boolean bRendered;

   private UI3DScene$CharacterDrawer() {
   }

   public void init(SceneCharacter var1, CharacterRenderData var2) {
      this.m_character = var1;
      this.m_renderData = var2;
      this.bRendered = false;
      this.m_character.m_animatedModel.renderMain();
   }

   public void render() {
      if (this.m_character.m_bClearDepthBuffer) {
         GL11.glClear(256);
      }

      boolean var1 = DebugOptions.instance.ModelRenderBones.getValue();
      DebugOptions.instance.ModelRenderBones.setValue(this.m_character.m_bShowBones);
      this.m_character.m_scene.m_CharacterSceneModelCamera.m_renderData = this.m_renderData;
      this.m_character.m_animatedModel.DoRender(this.m_character.m_scene.m_CharacterSceneModelCamera);
      DebugOptions.instance.ModelRenderBones.setValue(var1);
      this.bRendered = true;
      GL11.glDepthMask(true);
   }

   public void postRender() {
      this.m_character.m_animatedModel.postRender(this.bRendered);
   }
}
