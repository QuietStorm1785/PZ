#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODGlobalParameter.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/IsoWorld.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterZone : public FMODGlobalParameter {
public:
    const std::string m_zoneName;
   private const std::vector<Zone> m_zones = std::make_unique<std::vector<>>();

    public ParameterZone(const std::string& var1, const std::string& var2) {
      super(var1);
      this.m_zoneName = var2;
   }

    float calculateCurrentValue() {
    IsoGameCharacter var1 = this.getCharacter();
      if (var1 == nullptr) {
         return 40.0F;
      } else {
    uint8_t var2 = 0;
         this.m_zones.clear();
         IsoWorld.instance.MetaGrid.getZonesIntersecting((int)var1.x - 40, (int)var1.y - 40, var2, 80, 80, this.m_zones);
    float var3 = float.MAX_VALUE;

         for (int var4 = 0; var4 < this.m_zones.size(); var4++) {
    Zone var5 = this.m_zones.get(var4);
            if (this.m_zoneName.equalsIgnoreCase(var5.getType())) {
               if (var5.contains((int)var1.x, (int)var1.y, var2)) {
                  return 0.0F;
               }

    float var6 = var5.x + var5.w / 2.0F;
    float var7 = var5.y + var5.h / 2.0F;
    float var8 = PZMath.max(PZMath.abs(var1.x - var6) - var5.w / 2.0F, 0.0F);
    float var9 = PZMath.max(PZMath.abs(var1.y - var7) - var5.h / 2.0F, 0.0F);
               var3 = PZMath.min(var3, var8 * var8 + var9 * var9);
            }
         }

         return (int)PZMath.clamp(PZMath.sqrt(var3), 0.0F, 40.0F);
      }
   }

    IsoGameCharacter getCharacter() {
    IsoPlayer var1 = nullptr;

      for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
    IsoPlayer var3 = IsoPlayer.players[var2];
         if (var3 != nullptr && (var1 == nullptr || var1.isDead() && var3.isAlive() || var1.Traits.Deaf.isSet() && !var3.Traits.Deaf.isSet())) {
            var1 = var3;
         }
      }

    return var1;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
