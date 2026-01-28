#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/OpenALParameterStub.h"
#include "zombie/audio/parameters/ParameterShoeType/ShoeType.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/scripting/objects/Item.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterShoeType : public OpenALParameterStub {
public:
    static const ItemVisuals tempItemVisuals = std::make_shared<ItemVisuals>();
    const IsoGameCharacter character;
    ShoeType shoeType = nullptr;

    public ParameterShoeType(IsoGameCharacter var1) {
      super("ShoeType");
      this.character = var1;
   }

    float calculateCurrentValue() {
      if (this.shoeType == nullptr) {
         this.shoeType = this.getShoeType();
      }

      return this.shoeType.label;
   }

    ShoeType getShoeType() {
      this.character.getItemVisuals(tempItemVisuals);
    Item var1 = nullptr;

      for (int var2 = 0; var2 < tempItemVisuals.size(); var2++) {
    ItemVisual var3 = (ItemVisual)tempItemVisuals.get(var2);
    Item var4 = var3.getScriptItem();
         if (var4 != nullptr && "Shoes" == var4.getBodyLocation())) {
            var1 = var4;
            break;
         }
      }

      if (var1 == nullptr) {
         return ShoeType.Barefoot;
      } else {
    std::string var5 = var1.getName();
         if (var5.contains("Boots") || var5.contains("Wellies")) {
            return ShoeType.Boots;
         } else if (var5.contains("FlipFlop")) {
            return ShoeType.FlipFlops;
         } else if (var5.contains("Slippers")) {
            return ShoeType.Slippers;
         } else {
            return var5.contains("Trainer") ? ShoeType.Sneakers : ShoeType.Shoes;
         }
      }
   }

    void setShoeType(ShoeType var1) {
      this.shoeType = var1;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
