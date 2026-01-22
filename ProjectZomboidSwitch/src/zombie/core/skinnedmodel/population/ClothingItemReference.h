#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlTransient.h"
#include "zombie/core/ImmutableColor.h"
#include "zombie/core/skinnedmodel/population/ClothingItemReference/RandomData.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {


class ClothingItemReference {
public:
    float probability = 1.0F;
    std::string itemGUID;
   public std::vector<ClothingItemReference> subItems = std::make_unique<std::vector<>>();
    bool bRandomized = false;
    bool m_Immutable = false;
    const RandomData RandomData = std::make_shared<RandomData>();

    void setModID(const std::string& var1) {
      this.itemGUID = var1 + "-" + this.itemGUID;

      for (ClothingItemReference var3 : this.subItems) {
         var3.setModID(var1);
      }
   }

    ClothingItem getClothingItem() {
    std::string var1 = this.itemGUID;
      if (!this.bRandomized) {
         throw RuntimeException("not randomized yet");
      } else {
         if (this.RandomData.m_PickedItemRef != nullptr) {
            var1 = this.RandomData.m_PickedItemRef.itemGUID;
         }

         return OutfitManager.instance.getClothingItem(var1);
      }
   }

    void randomize() {
      if (this.m_Immutable) {
         throw RuntimeException("trying to randomize an immutable ClothingItemReference");
      } else {
         this.RandomData.reset();

         for (int var1 = 0; var1 < this.subItems.size(); var1++) {
    ClothingItemReference var2 = this.subItems.get(var1);
            var2.randomize();
         }

         this.RandomData.m_PickedItemRef = this.pickRandomItemInternal();
         this.bRandomized = true;
    ClothingItem var3 = this.getClothingItem();
         if (var3 == nullptr) {
            this.RandomData.m_Active = false;
         } else {
            this.RandomData.m_Active = OutfitRNG.Next(0.0F, 1.0F) <= this.probability;
            if (var3.m_AllowRandomHue) {
               this.RandomData.m_Hue = OutfitRNG.Next(200) / 100.0F - 1.0F;
            }

            if (var3.m_AllowRandomTint) {
               this.RandomData.m_Tint = OutfitRNG.randomImmutableColor();
            } else {
               this.RandomData.m_Tint = ImmutableColor.white;
            }

            this.RandomData.m_BaseTexture = (std::string)OutfitRNG.pickRandom(var3.m_BaseTextures);
            this.RandomData.m_TextureChoice = (std::string)OutfitRNG.pickRandom(var3.textureChoices);
            if (!StringUtils.isNullOrWhitespace(var3.m_DecalGroup)) {
               this.RandomData.m_Decal = ClothingDecals.instance.getRandomDecal(var3.m_DecalGroup);
            }
         }
      }
   }

    ClothingItemReference pickRandomItemInternal() {
      if (this.subItems.empty()) {
    return this;
      } else {
    int var1 = OutfitRNG.Next(this.subItems.size() + 1);
         if (var1 == 0) {
    return this;
         } else {
    ClothingItemReference var2 = this.subItems.get(var1 - 1);
            return var2.RandomData.m_PickedItemRef;
         }
      }
   }

    ClothingItemReference clone() {
      try {
    ClothingItemReference var1 = std::make_shared<ClothingItemReference>();
         var1.probability = this.probability;
         var1.itemGUID = this.itemGUID;
         PZArrayUtil.copy(var1.subItems, this.subItems, ClothingItemReference::clone);
    return var1;
      } catch (CloneNotSupportedException var2) {
         throw RuntimeException("ClothingItemReference clone failed.", var2);
      }
   }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
