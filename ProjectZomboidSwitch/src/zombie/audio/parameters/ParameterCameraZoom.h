#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/OpenALParameterStub.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterCameraZoom : public OpenALParameterStub {
public:
    public ParameterCameraZoom() {
      super("CameraZoom");
   }

    float calculateCurrentValue() {
    IsoPlayer var1 = this.getPlayer();
      if (var1 == nullptr) {
         return 0.0F;
      } else {
    float var2 = Core.getInstance().getZoom(var1.PlayerIndex) - Core.getInstance().OffscreenBuffer.getMinZoom();
    float var3 = Core.getInstance().OffscreenBuffer.getMaxZoom() - Core.getInstance().OffscreenBuffer.getMinZoom();
         return var2 / var3;
      }
   }

    IsoPlayer getPlayer() {
    IsoPlayer var1 = nullptr;

      for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
    IsoPlayer var3 = IsoPlayer.players[var2];
         if (var3 != nullptr && (var1 == nullptr || var1.isDead() && var3.isAlive())) {
            var1 = var3;
         }
      }

    return var1;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
