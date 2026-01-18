#pragma once
#include "javax/xml/bind/annotation/XmlTransient.h"
#include "zombie/core/ImmutableColor.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ClothingItemReference {
public:
  float probability = 1.0F;
  std::string itemGUID;
public
  ArrayList<ClothingItemReference> subItems = std::make_unique<ArrayList<>>();
  bool bRandomized = false;
  bool m_Immutable = false;
public
  final ClothingItemReference.RandomData RandomData =
      new ClothingItemReference.RandomData();

  void setModID(const std::string &modID) {
    this.itemGUID = modID + "-" + this.itemGUID;

    for (ClothingItemReference clothingItemReference : this.subItems) {
      clothingItemReference.setModID(modID);
    }
  }

  ClothingItem getClothingItem() {
    std::string string = this.itemGUID;
    if (!this.bRandomized) {
      throw new RuntimeException("not randomized yet");
    } else {
      if (this.RandomData.m_PickedItemRef != nullptr) {
        string = this.RandomData.m_PickedItemRef.itemGUID;
      }

      return OutfitManager.instance.getClothingItem(string);
    }
  }

  void randomize() {
    if (this.m_Immutable) {
      throw new RuntimeException(
          "trying to randomize an immutable ClothingItemReference");
    } else {
      this.RandomData.reset();

      for (int int0 = 0; int0 < this.subItems.size(); int0++) {
        ClothingItemReference clothingItemReference1 = this.subItems.get(int0);
        clothingItemReference1.randomize();
      }

      this.RandomData.m_PickedItemRef = this.pickRandomItemInternal();
      this.bRandomized = true;
      ClothingItem clothingItem = this.getClothingItem();
      if (clothingItem == nullptr) {
        this.RandomData.m_Active = false;
      } else {
        this.RandomData.m_Active =
            OutfitRNG.Next(0.0F, 1.0F) <= this.probability;
        if (clothingItem.m_AllowRandomHue) {
          this.RandomData.m_Hue = OutfitRNG.Next(200) / 100.0F - 1.0F;
        }

        if (clothingItem.m_AllowRandomTint) {
          this.RandomData.m_Tint = OutfitRNG.randomImmutableColor();
        } else {
          this.RandomData.m_Tint = ImmutableColor.white;
        }

        this.RandomData.m_BaseTexture =
            OutfitRNG.pickRandom(clothingItem.m_BaseTextures);
        this.RandomData.m_TextureChoice =
            OutfitRNG.pickRandom(clothingItem.textureChoices);
        if (!StringUtils.isNullOrWhitespace(clothingItem.m_DecalGroup)) {
          this.RandomData.m_Decal =
              ClothingDecals.instance.getRandomDecal(clothingItem.m_DecalGroup);
        }
      }
    }
  }

  ClothingItemReference pickRandomItemInternal() {
    if (this.subItems.isEmpty()) {
      return this;
    } else {
      int int0 = OutfitRNG.Next(this.subItems.size() + 1);
      if (int0 == 0) {
        return this;
      } else {
        ClothingItemReference clothingItemReference1 =
            this.subItems.get(int0 - 1);
        return clothingItemReference1.RandomData.m_PickedItemRef;
      }
    }
  }

  ClothingItemReference clone() {
    try {
      ClothingItemReference clothingItemReference0 =
          new ClothingItemReference();
      clothingItemReference0.probability = this.probability;
      clothingItemReference0.itemGUID = this.itemGUID;
      PZArrayUtil.copy(clothingItemReference0.subItems, this.subItems,
                       ClothingItemReference::clone);
      return clothingItemReference0;
    } catch (CloneNotSupportedException cloneNotSupportedException) {
      throw new RuntimeException("ClothingItemReference clone failed.",
                                 cloneNotSupportedException);
    }
  }

public
  static class RandomData {
    bool m_Active = true;
    float m_Hue = 0.0F;
    ImmutableColor m_Tint = ImmutableColor.white;
    std::string m_BaseTexture;
    ClothingItemReference m_PickedItemRef;
    std::string m_TextureChoice;
    std::string m_Decal;

    void reset() {
      this.m_Active = true;
      this.m_Hue = 0.0F;
      this.m_Tint = ImmutableColor.white;
      this.m_BaseTexture = nullptr;
      this.m_PickedItemRef = nullptr;
      this.m_TextureChoice = nullptr;
      this.m_Decal = nullptr;
    }
  }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
