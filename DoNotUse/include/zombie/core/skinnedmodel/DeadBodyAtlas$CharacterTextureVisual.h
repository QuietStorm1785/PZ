#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/visual/HumanVisual.h"
#include "zombie/core/skinnedmodel/visual/IHumanVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"

namespace zombie {
namespace core {
namespace skinnedmodel {


class DeadBodyAtlas {
public:
    const HumanVisual humanVisual = std::make_shared<HumanVisual>(this);
    bool bFemale;

   DeadBodyAtlas$CharacterTextureVisual(boolean var1) {
      this.bFemale = var1;
      this.humanVisual.setHairModel("");
      this.humanVisual.setBeardModel("");
   }

    HumanVisual getHumanVisual() {
      return this.humanVisual;
   }

    void getItemVisuals(ItemVisuals var1) {
      var1.clear();
   }

    bool isFemale() {
      return this.bFemale;
   }

    bool isZombie() {
    return true;
   }

    bool isSkeleton() {
    return false;
   }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
