#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/DeadBodyAtlas/BodyTexture.h"
#include "zombie/iso/IsoDirections.h"

namespace zombie {
namespace iso {
namespace objects {


class IsoMannequin {
public:
    BodyTexture atlasTex = nullptr;
    IsoDirections renderDirection = nullptr;
    bool bWasRenderDirection = false;

   private IsoMannequin$PerPlayer() {
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
