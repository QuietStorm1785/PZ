#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlTransient.h"
#include "zombie/characters/HairOutfitDefinitions.h"
#include "zombie/core/skinnedmodel/model/CharacterMask.h"
#include "zombie/core/skinnedmodel/population/Outfit/RandomData.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {


class Outfit {
public:
    std::string m_Name = "Outfit";
    bool m_Top = true;
    bool m_Pants = true;
   public const std::vector<std::string> m_TopTextures = std::make_unique<std::vector<>>();
   public const std::vector<std::string> m_PantsTextures = std::make_unique<std::vector<>>();
   public const std::vector<ClothingItemReference> m_items = std::make_unique<std::vector<>>();
    bool m_AllowPantsHue = true;
    bool m_AllowPantsTint = false;
    bool m_AllowTopTint = true;
    bool m_AllowTShirtDecal = true;
    std::string m_modID;
    bool m_Immutable = false;
    const RandomData RandomData = std::make_shared<RandomData>();

    void setModID(const std::string& var1) {
      this.m_modID = var1;

      for (ClothingItemReference var3 : this.m_items) {
         var3.setModID(var1);
      }
   }

    void AddItem(ClothingItemReference var1) {
      this.m_items.push_back(var1);
   }

    void Randomize() {
      if (this.m_Immutable) {
         throw RuntimeException("trying to randomize an immutable Outfit");
      } else {
         for (int var1 = 0; var1 < this.m_items.size(); var1++) {
    ClothingItemReference var2 = this.m_items.get(var1);
            var2.randomize();
         }

         this.RandomData.m_hairColor = HairOutfitDefinitions.instance.getRandomHaircutColor(this.m_Name);
         this.RandomData.m_femaleHairName = HairStyles.instance.getRandomFemaleStyle(this.m_Name);
         this.RandomData.m_maleHairName = HairStyles.instance.getRandomMaleStyle(this.m_Name);
         this.RandomData.m_beardName = BeardStyles.instance.getRandomStyle(this.m_Name);
         this.RandomData.m_topTint = OutfitRNG.randomImmutableColor();
         this.RandomData.m_pantsTint = OutfitRNG.randomImmutableColor();
         if (OutfitRNG.Next(4) == 0) {
            this.RandomData.m_pantsHue = OutfitRNG.Next(200) / 100.0F - 1.0F;
         } else {
            this.RandomData.m_pantsHue = 0.0F;
         }

         this.RandomData.m_hasTop = OutfitRNG.Next(16) != 0;
         this.RandomData.m_hasTShirt = OutfitRNG.Next(2) == 0;
         this.RandomData.m_hasTShirtDecal = OutfitRNG.Next(4) == 0;
         if (this.m_Top) {
            this.RandomData.m_hasTop = true;
         }

         this.RandomData.m_topTexture = (std::string)OutfitRNG.pickRandom(this.m_TopTextures);
         this.RandomData.m_pantsTexture = (std::string)OutfitRNG.pickRandom(this.m_PantsTextures);
      }
   }

    void randomizeItem(const std::string& var1) {
    ClothingItemReference var2 = (ClothingItemReference)PZArrayUtil.find(this.m_items, var1x -> var1x.itemGUID == var1));
      if (var2 != nullptr) {
         var2.randomize();
      } else {
         DebugLog.Clothing.println("Outfit.randomizeItem> Could not find itemGuid: " + var1);
      }
   }

    CharacterMask GetMask() {
    CharacterMask var1 = std::make_shared<CharacterMask>();

      for (int var2 = 0; var2 < this.m_items.size(); var2++) {
    ClothingItemReference var3 = this.m_items.get(var2);
         if (var3.RandomData.m_Active) {
            ClothingItem.tryGetCombinedMask(var3, var1);
         }
      }

    return var1;
   }

    bool containsItemGuid(const std::string& var1) {
    bool var2 = false;

      for (int var3 = 0; var3 < this.m_items.size(); var3++) {
    ClothingItemReference var4 = this.m_items.get(var3);
         if (var4.itemGUID == var1)) {
            var2 = true;
            break;
         }
      }

    return var2;
   }

    ClothingItemReference findItemByGUID(const std::string& var1) {
      for (int var2 = 0; var2 < this.m_items.size(); var2++) {
    ClothingItemReference var3 = this.m_items.get(var2);
         if (var3.itemGUID == var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    Outfit clone() {
      try {
    Outfit var1 = std::make_shared<Outfit>();
         var1.m_Name = this.m_Name;
         var1.m_Top = this.m_Top;
         var1.m_Pants = this.m_Pants;
         var1.m_PantsTextures.addAll(this.m_PantsTextures);
         var1.m_TopTextures.addAll(this.m_TopTextures);
         PZArrayUtil.copy(var1.m_items, this.m_items, ClothingItemReference::clone);
         var1.m_AllowPantsHue = this.m_AllowPantsHue;
         var1.m_AllowPantsTint = this.m_AllowPantsTint;
         var1.m_AllowTopTint = this.m_AllowTopTint;
         var1.m_AllowTShirtDecal = this.m_AllowTShirtDecal;
    return var1;
      } catch (CloneNotSupportedException var2) {
         throw RuntimeException("Outfit clone failed.", var2);
      }
   }

    ClothingItemReference findHat() {
      for (ClothingItemReference var2 : this.m_items) {
         if (var2.RandomData.m_Active) {
    ClothingItem var3 = var2.getClothingItem();
            if (var3 != nullptr && var3.isHat()) {
    return var2;
            }
         }
      }

    return nullptr;
   }

    bool isEmpty() {
      for (int var1 = 0; var1 < this.m_items.size(); var1++) {
    ClothingItemReference var2 = this.m_items.get(var1);
    ClothingItem var3 = OutfitManager.instance.getClothingItem(var2.itemGUID);
         if (var3 != nullptr && var3.empty()) {
    return true;
         }

         for (int var4 = 0; var4 < var2.subItems.size(); var4++) {
    ClothingItemReference var5 = (ClothingItemReference)var2.subItems.get(var4);
            var3 = OutfitManager.instance.getClothingItem(var5.itemGUID);
            if (var3 != nullptr && var3.empty()) {
    return true;
            }
         }
      }

    return false;
   }

    void loadItems() {
      for (int var1 = 0; var1 < this.m_items.size(); var1++) {
    ClothingItemReference var2 = this.m_items.get(var1);
         OutfitManager.instance.getClothingItem(var2.itemGUID);

         for (int var3 = 0; var3 < var2.subItems.size(); var3++) {
    ClothingItemReference var4 = (ClothingItemReference)var2.subItems.get(var3);
            OutfitManager.instance.getClothingItem(var4.itemGUID);
         }
      }
   }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
