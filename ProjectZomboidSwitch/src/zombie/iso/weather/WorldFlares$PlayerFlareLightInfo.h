#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {
namespace weather {

class WorldFlares {
public:
    float intensity;
    float lerp;
    float distMod;
    ClimateColorInfo flareCol = std::make_shared<ClimateColorInfo>(1.0F, 1.0F, 1.0F, 1.0F);
    ClimateColorInfo outColor = std::make_shared<ClimateColorInfo>(1.0F, 1.0F, 1.0F, 1.0F);

   private WorldFlares$PlayerFlareLightInfo() {
   }
}
} // namespace weather
} // namespace iso
} // namespace zombie
