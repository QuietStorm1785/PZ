#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/Vector2.h"
#include "zombie/iso/Vector3.h"

namespace zombie {
namespace iso {
namespace sprite {


class IsoSprite {
public:
    static const Vector3 colorInfoBackup = std::make_shared<Vector3>();
    static const Vector2 spritePos = std::make_shared<Vector2>();

   private IsoSprite$l_renderCurrentAnim() {
   }
}
} // namespace sprite
} // namespace iso
} // namespace zombie
