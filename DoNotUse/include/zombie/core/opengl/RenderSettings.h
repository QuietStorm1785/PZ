#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/opengl/RenderSettings/PlayerRenderSettings.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace core {
namespace opengl {


class RenderSettings {
public:
    static RenderSettings instance;
    static Texture texture;
    static const float AMBIENT_MIN_SHADER = 0.4F;
    static const float AMBIENT_MAX_SHADER = 1.0F;
    static const float AMBIENT_MIN_LEGACY = 0.4F;
    static const float AMBIENT_MAX_LEGACY = 1.0F;
   private const PlayerRenderSettings[] playerSettings = new PlayerRenderSettings[4];
    Color defaultClear = std::make_shared<Color>(0, 0, 0, 1);

    static RenderSettings getInstance() {
      if (instance == nullptr) {
         instance = std::make_unique<RenderSettings>();
      }

    return instance;
   }

    public RenderSettings() {
      for (int var1 = 0; var1 < this.playerSettings.length; var1++) {
         this.playerSettings[var1] = std::make_unique<PlayerRenderSettings>();
      }

      texture = Texture.getSharedTexture("media/textures/weather/fogwhite.png");
      if (texture == nullptr) {
         DebugLog.log("Missing texture: media/textures/weather/fogwhite.png");
      }
   }

    PlayerRenderSettings getPlayerSettings(int var1) {
      return this.playerSettings[var1];
   }

    void update() {
      if (!GameServer.bServer) {
         for (int var1 = 0; var1 < 4; var1++) {
            if (IsoPlayer.players[var1] != nullptr) {
               this.playerSettings[var1].updateRenderSettings(var1, IsoPlayer.players[var1]);
            }
         }
      }
   }

    void applyRenderSettings(int var1) {
      if (!GameServer.bServer) {
         this.getPlayerSettings(var1).applyRenderSettings(var1);
      }
   }

    void legacyPostRender(int var1) {
      if (!GameServer.bServer) {
         if (Core.getInstance().RenderShader == nullptr || Core.getInstance().getOffscreenBuffer() == nullptr) {
            this.getPlayerSettings(var1).legacyPostRender(var1);
         }
      }
   }

    float getAmbientForPlayer(int var1) {
    PlayerRenderSettings var2 = this.getPlayerSettings(var1);
      return var2 != nullptr ? var2.getAmbient() : 0.0F;
   }

    Color getMaskClearColorForPlayer(int var1) {
    PlayerRenderSettings var2 = this.getPlayerSettings(var1);
      return var2 != nullptr ? var2.getMaskClearColor() : this.defaultClear;
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
