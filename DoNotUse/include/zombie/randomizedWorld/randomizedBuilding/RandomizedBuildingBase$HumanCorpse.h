#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/core/skinnedmodel/visual/HumanVisual.h"
#include "zombie/core/skinnedmodel/visual/IHumanVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/iso/IsoCell.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {


class RandomizedBuildingBase {
public:
    const HumanVisual humanVisual = std::make_shared<HumanVisual>(this);
    const ItemVisuals itemVisuals = std::make_shared<ItemVisuals>();
    bool isSkeleton = false;

   public RandomizedBuildingBase$HumanCorpse(IsoCell var1, float var2, float var3, float var4) {
      super(var1, var2, var3, var4);
      var1.getObjectList().remove(this);
      var1.getAddList().remove(this);
   }

    void dressInNamedOutfit(const std::string& var1) {
      this.getHumanVisual().dressInNamedOutfit(var1, this.itemVisuals);
      this.getHumanVisual().synchWithOutfit(this.getHumanVisual().getOutfit());
   }

    HumanVisual getHumanVisual() {
      return this.humanVisual;
   }

    HumanVisual getVisual() {
      return this.humanVisual;
   }

    void Dressup(SurvivorDesc var1) {
      this.wornItems.setFromItemVisuals(this.itemVisuals);
      this.wornItems.addItemsToItemContainer(this.inventory);
   }

    bool isSkeleton() {
      return this.isSkeleton;
   }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
