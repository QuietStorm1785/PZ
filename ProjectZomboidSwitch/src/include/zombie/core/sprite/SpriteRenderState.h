#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Styles/TransparentStyle.h"
#include "zombie/core/opengl/GLState.h"
#include "zombie/core/opengl/RenderSettings.h"
#include "zombie/core/textures/TextureFBO.h"
#include "zombie/input/Mouse.h"
#include "zombie/iso/PlayerCamera.h"

namespace zombie {
namespace core {
namespace sprite {


class SpriteRenderState : public GenericSpriteRenderState {
public:
    TextureFBO fbo = nullptr;
    long time;
    const SpriteRenderStateUI stateUI;
    int playerIndex;
   public const PlayerCamera[] playerCamera = new PlayerCamera[4];
   public const float[] playerAmbient = new float[4];
    float maxZoomLevel = 0.0F;
    float minZoomLevel = 0.0F;
   public const float[] zoomLevel = new float[4];

    public SpriteRenderState(int var1) {
      super(var1);

      for (int var2 = 0; var2 < 4; var2++) {
         this.playerCamera[var2] = std::make_shared<PlayerCamera>(var2);
      }

      this.stateUI = std::make_shared<SpriteRenderStateUI>(var1);
   }

    void onRendered() {
      super.onRendered();
      this.stateUI.onRendered();
   }

    void onReady() {
      super.onReady();
      this.stateUI.onReady();
   }

    void CheckSpriteSlots() {
      if (this.stateUI.bActive) {
         this.stateUI.CheckSpriteSlots();
      } else {
         super.CheckSpriteSlots();
      }
   }

    void clear() {
      this.stateUI.clear();
      super.clear();
   }

    GenericSpriteRenderState getActiveState() {
      return (GenericSpriteRenderState)(this.stateUI.bActive ? this.stateUI : this);
   }

    void prePopulating() {
      this.clear();
      this.fbo = Core.getInstance().getOffscreenBuffer();

      for (int var1 = 0; var1 < IsoPlayer.numPlayers; var1++) {
    IsoPlayer var2 = IsoPlayer.players[var1];
         if (var2 != nullptr) {
            this.playerCamera[var1].initFromIsoCamera(var1);
            this.playerAmbient[var1] = RenderSettings.getInstance().getAmbientForPlayer(var1);
            this.zoomLevel[var1] = Core.getInstance().getZoom(var1);
            this.maxZoomLevel = Core.getInstance().getMaxZoom();
            this.minZoomLevel = Core.getInstance().getMinZoom();
         }
      }

      this.defaultStyle = TransparentStyle.instance;
      this.bCursorVisible = Mouse.isCursorVisible();
      GLState.startFrame();
   }
}
} // namespace sprite
} // namespace core
} // namespace zombie
