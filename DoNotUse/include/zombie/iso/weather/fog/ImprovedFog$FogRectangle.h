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
namespace fog {

class ImprovedFog {
public:
    int startX;
    int startY;
    int endX;
    int endY;
    int Z;
    bool hasStarted = false;

   private ImprovedFog$FogRectangle() {
   }
}
} // namespace fog
} // namespace weather
} // namespace iso
} // namespace zombie
