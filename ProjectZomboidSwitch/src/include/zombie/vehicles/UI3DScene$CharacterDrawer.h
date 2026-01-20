#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/GL11.h"
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/vehicles/UI3DScene/CharacterRenderData.h"
#include "zombie/vehicles/UI3DScene/SceneCharacter.h"

namespace zombie {
namespace vehicles {


class UI3DScene {
public:
    SceneCharacter m_character;
    CharacterRenderData m_renderData;
    bool bRendered;

   private UI3DScene$CharacterDrawer() {
   }

    void init(SceneCharacter var1, CharacterRenderData var2) {
      this.m_character = var1;
      this.m_renderData = var2;
      this.bRendered = false;
      this.m_character.m_animatedModel.renderMain();
   }

    void render() {
      if (this.m_character.m_bClearDepthBuffer) {
         GL11.glClear(256);
      }

    bool var1 = DebugOptions.instance.ModelRenderBones.getValue();
      DebugOptions.instance.ModelRenderBones.setValue(this.m_character.m_bShowBones);
      this.m_character.m_scene.m_CharacterSceneModelCamera.m_renderData = this.m_renderData;
      this.m_character.m_animatedModel.DoRender(this.m_character.m_scene.m_CharacterSceneModelCamera);
      DebugOptions.instance.ModelRenderBones.setValue(var1);
      this.bRendered = true;
      GL11.glDepthMask(true);
   }

    void postRender() {
      this.m_character.m_animatedModel.postRender(this.bRendered);
   }
}
} // namespace vehicles
} // namespace zombie
