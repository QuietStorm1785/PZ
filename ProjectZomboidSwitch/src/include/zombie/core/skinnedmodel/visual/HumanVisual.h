#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characters/HairOutfitDefinitions.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/characters/WornItems/BodyLocation.h"
#include "zombie/characters/WornItems/BodyLocationGroup.h"
#include "zombie/characters/WornItems/BodyLocations.h"
#include "zombie/core/ImmutableColor.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/model/CharacterMask.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/core/skinnedmodel/population/BeardStyles.h"
#include "zombie/core/skinnedmodel/population/ClothingItem.h"
#include "zombie/core/skinnedmodel/population/ClothingItemReference.h"
#include "zombie/core/skinnedmodel/population/DefaultClothing.h"
#include "zombie/core/skinnedmodel/population/HairStyles.h"
#include "zombie/core/skinnedmodel/population/Outfit.h"
#include "zombie/core/skinnedmodel/population/OutfitManager.h"
#include "zombie/core/skinnedmodel/population/OutfitRNG.h"
#include "zombie/core/skinnedmodel/population/PopTemplateManager.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/scripting/objects/ModelScript.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace visual {


class HumanVisual : public BaseVisual {
public:
    const IHumanVisual owner;
    ImmutableColor skinColor = ImmutableColor.white;
    int skinTexture = -1;
    std::string skinTextureName = nullptr;
    int zombieRotStage = -1;
    ImmutableColor hairColor;
    ImmutableColor beardColor;
    ImmutableColor naturalHairColor;
    ImmutableColor naturalBeardColor;
    std::string hairModel;
    std::string beardModel;
    int bodyHair = -1;
   private const byte[] blood = new byte[BloodBodyPartType.MAX.index()];
   private const byte[] dirt = new byte[BloodBodyPartType.MAX.index()];
   private const byte[] holes = new byte[BloodBodyPartType.MAX.index()];
    const ItemVisuals bodyVisuals = std::make_shared<ItemVisuals>();
    Outfit outfit = nullptr;
    std::string nonAttachedHair = nullptr;
    Model forceModel = nullptr;
    std::string forceModelScript = nullptr;
   private static const std::vector<std::string> itemVisualLocations = std::make_unique<std::vector<>>();
    static const int LASTSTAND_VERSION1 = 1;
    static const int LASTSTAND_VERSION = 1;

    public HumanVisual(IHumanVisual var1) {
      this.owner = var1;
      Arrays.fill(this.blood, (byte)0);
      Arrays.fill(this.dirt, (byte)0);
      Arrays.fill(this.holes, (byte)0);
   }

    bool isFemale() {
      return this.owner.isFemale();
   }

    bool isZombie() {
      return this.owner.isZombie();
   }

    bool isSkeleton() {
      return this.owner.isSkeleton();
   }

    void setSkinColor(ImmutableColor var1) {
      this.skinColor = var1;
   }

    ImmutableColor getSkinColor() {
      if (this.skinColor == nullptr) {
         this.skinColor = std::make_shared<ImmutableColor>(SurvivorDesc.getRandomSkinColor());
      }

      return this.skinColor;
   }

    void setBodyHairIndex(int var1) {
      this.bodyHair = var1;
   }

    int getBodyHairIndex() {
      return this.bodyHair;
   }

    void setSkinTextureIndex(int var1) {
      this.skinTexture = var1;
   }

    int getSkinTextureIndex() {
      return this.skinTexture;
   }

    void setSkinTextureName(const std::string& var1) {
      this.skinTextureName = var1;
   }

    float lerp(float var1, float var2, float var3) {
      if (var3 < 0.0F) {
         var3 = 0.0F;
      }

      if (var3 >= 1.0F) {
         var3 = 1.0F;
      }

    float var4 = var2 - var1;
    float var5 = var4 * var3;
      return var1 + var5;
   }

    int pickRandomZombieRotStage() {
    int var1 = Math.max((int)IsoWorld.instance.getWorldAgeDays(), 0);
    float var2 = 20.0F;
    float var3 = 90.0F;
    float var4 = 100.0F;
    float var5 = 20.0F;
    float var6 = 10.0F;
    float var7 = 30.0F;
      if (var1 >= 180) {
         var5 = 0.0F;
         var7 = 10.0F;
      }

    float var8 = var1 - var2;
    float var9 = var8 / (var3 - var2);
    float var10 = this.lerp(var4, var5, var9);
    float var11 = this.lerp(var6, var7, var9);
    float var12 = OutfitRNG.Next(100);
      if (var12 < var10) {
    return 1;
      } else {
         return var12 < var11 + var10 ? 2 : 3;
      }
   }

    std::string getSkinTexture() {
      if (this.skinTextureName != nullptr) {
         return this.skinTextureName;
      } else {
    std::string var1 = "";
    std::vector var2 = this.owner.isFemale() ? PopTemplateManager.instance.m_FemaleSkins : PopTemplateManager.instance.m_MaleSkins;
         if (this.owner.isZombie() && this.owner.isSkeleton()) {
            if (this.owner.isFemale()) {
               var2 = PopTemplateManager.instance.m_SkeletonFemaleSkins_Zombie;
            } else {
               var2 = PopTemplateManager.instance.m_SkeletonMaleSkins_Zombie;
            }
         } else if (this.owner.isZombie()) {
            if (this.zombieRotStage < 1 || this.zombieRotStage > 3) {
               this.zombieRotStage = this.pickRandomZombieRotStage();
            }

            switch (this.zombieRotStage) {
               case 1:
                  var2 = this.owner.isFemale() ? PopTemplateManager.instance.m_FemaleSkins_Zombie1 : PopTemplateManager.instance.m_MaleSkins_Zombie1;
                  break;
               case 2:
                  var2 = this.owner.isFemale() ? PopTemplateManager.instance.m_FemaleSkins_Zombie2 : PopTemplateManager.instance.m_MaleSkins_Zombie2;
                  break;
               case 3:
                  var2 = this.owner.isFemale() ? PopTemplateManager.instance.m_FemaleSkins_Zombie3 : PopTemplateManager.instance.m_MaleSkins_Zombie3;
            }
         } else if (!this.owner.isFemale()) {
            var1 = !this.owner.isZombie() && this.bodyHair >= 0 ? "a" : "";
         }

         if (this.skinTexture == var2.size()) {
            this.skinTexture--;
         } else if (this.skinTexture < 0 || this.skinTexture > var2.size()) {
            this.skinTexture = OutfitRNG.Next(var2.size());
         }

         return (std::string)var2.get(this.skinTexture) + var1;
      }
   }

    void setHairColor(ImmutableColor var1) {
      this.hairColor = var1;
   }

    ImmutableColor getHairColor() {
      if (this.hairColor == nullptr) {
         this.hairColor = HairOutfitDefinitions.instance.getRandomHaircutColor(this.outfit != nullptr ? this.outfit.m_Name : nullptr);
      }

      return this.hairColor;
   }

    void setBeardColor(ImmutableColor var1) {
      this.beardColor = var1;
   }

    ImmutableColor getBeardColor() {
      if (this.beardColor == nullptr) {
         this.beardColor = this.getHairColor();
      }

      return this.beardColor;
   }

    void setNaturalHairColor(ImmutableColor var1) {
      this.naturalHairColor = var1;
   }

    ImmutableColor getNaturalHairColor() {
      if (this.naturalHairColor == nullptr) {
         this.naturalHairColor = this.getHairColor();
      }

      return this.naturalHairColor;
   }

    void setNaturalBeardColor(ImmutableColor var1) {
      this.naturalBeardColor = var1;
   }

    ImmutableColor getNaturalBeardColor() {
      if (this.naturalBeardColor == nullptr) {
         this.naturalBeardColor = this.getNaturalHairColor();
      }

      return this.naturalBeardColor;
   }

    void setHairModel(const std::string& var1) {
      this.hairModel = var1;
   }

    std::string getHairModel() {
      if (this.owner.isFemale()) {
         if (HairStyles.instance.FindFemaleStyle(this.hairModel) == nullptr) {
            this.hairModel = HairStyles.instance.getRandomFemaleStyle(this.outfit != nullptr ? this.outfit.m_Name : nullptr);
         }
      } else if (HairStyles.instance.FindMaleStyle(this.hairModel) == nullptr) {
         this.hairModel = HairStyles.instance.getRandomMaleStyle(this.outfit != nullptr ? this.outfit.m_Name : nullptr);
      }

      return this.hairModel;
   }

    void setBeardModel(const std::string& var1) {
      this.beardModel = var1;
   }

    std::string getBeardModel() {
      if (this.owner.isFemale()) {
         this.beardModel = nullptr;
      } else if (BeardStyles.instance.FindStyle(this.beardModel) == nullptr) {
         this.beardModel = BeardStyles.instance.getRandomStyle(this.outfit != nullptr ? this.outfit.m_Name : nullptr);
      }

      return this.beardModel;
   }

    void setBlood(BloodBodyPartType var1, float var2) {
      var2 = Math.max(0.0F, Math.min(1.0F, var2));
      this.blood[var1.index()] = (byte)(var2 * 255.0F);
   }

    float getBlood(BloodBodyPartType var1) {
      return (this.blood[var1.index()] & 255) / 255.0F;
   }

    void setDirt(BloodBodyPartType var1, float var2) {
      var2 = Math.max(0.0F, Math.min(1.0F, var2));
      this.dirt[var1.index()] = (byte)(var2 * 255.0F);
   }

    float getDirt(BloodBodyPartType var1) {
      return (this.dirt[var1.index()] & 255) / 255.0F;
   }

    void setHole(BloodBodyPartType var1) {
      this.holes[var1.index()] = -1;
   }

    float getHole(BloodBodyPartType var1) {
      return (this.holes[var1.index()] & 255) / 255.0F;
   }

    void removeBlood() {
      Arrays.fill(this.blood, (byte)0);
   }

    void removeDirt() {
      Arrays.fill(this.dirt, (byte)0);
   }

    void randomBlood() {
      for (int var1 = 0; var1 < BloodBodyPartType.MAX.index(); var1++) {
         this.setBlood(BloodBodyPartType.FromIndex(var1), OutfitRNG.Next(0.0F, 1.0F));
      }
   }

    void randomDirt() {
      for (int var1 = 0; var1 < BloodBodyPartType.MAX.index(); var1++) {
         this.setDirt(BloodBodyPartType.FromIndex(var1), OutfitRNG.Next(0.0F, 1.0F));
      }
   }

    float getTotalBlood() {
    float var1 = 0.0F;

      for (int var2 = 0; var2 < this.blood.length; var2++) {
         var1 += (this.blood[var2] & 255) / 255.0F;
      }

    return var1;
   }

    void clear() {
      this.skinColor = ImmutableColor.white;
      this.skinTexture = -1;
      this.skinTextureName = nullptr;
      this.zombieRotStage = -1;
      this.hairColor = nullptr;
      this.beardColor = nullptr;
      this.naturalHairColor = nullptr;
      this.naturalBeardColor = nullptr;
      this.hairModel = nullptr;
      this.nonAttachedHair = nullptr;
      this.beardModel = nullptr;
      this.bodyHair = -1;
      Arrays.fill(this.blood, (byte)0);
      Arrays.fill(this.dirt, (byte)0);
      Arrays.fill(this.holes, (byte)0);
      this.bodyVisuals.clear();
      this.forceModel = nullptr;
      this.forceModelScript = nullptr;
   }

    void copyFrom(BaseVisual var1) {
      if (var1 == nullptr) {
         this.clear();
      } else {
    HumanVisual var2 = (HumanVisual)Type.tryCastTo(var1, HumanVisual.class);
         if (var2 == nullptr) {
            throw IllegalArgumentException("expected HumanVisual, got " + var1);
         } else {
            var2.getHairColor();
            var2.getNaturalHairColor();
            var2.getNaturalBeardColor();
            var2.getHairModel();
            var2.getBeardModel();
            var2.getSkinTexture();
            this.skinColor = var2.skinColor;
            this.skinTexture = var2.skinTexture;
            this.skinTextureName = var2.skinTextureName;
            this.zombieRotStage = var2.zombieRotStage;
            this.hairColor = var2.hairColor;
            this.beardColor = var2.beardColor;
            this.naturalHairColor = var2.naturalHairColor;
            this.naturalBeardColor = var2.naturalBeardColor;
            this.hairModel = var2.hairModel;
            this.nonAttachedHair = var2.nonAttachedHair;
            this.beardModel = var2.beardModel;
            this.bodyHair = var2.bodyHair;
            this.outfit = var2.outfit;
            System.arraycopy(var2.blood, 0, this.blood, 0, this.blood.length);
            System.arraycopy(var2.dirt, 0, this.dirt, 0, this.dirt.length);
            System.arraycopy(var2.holes, 0, this.holes, 0, this.holes.length);
            this.bodyVisuals.clear();
            this.bodyVisuals.addAll(var2.bodyVisuals);
            this.forceModel = var2.forceModel;
            this.forceModelScript = var2.forceModelScript;
         }
      }
   }

    void save(ByteBuffer var1) {
    uint8_t var2 = 0;
      if (this.hairColor != nullptr) {
         var2 = (byte)(var2 | 4);
      }

      if (this.beardColor != nullptr) {
         var2 = (byte)(var2 | 2);
      }

      if (this.skinColor != nullptr) {
         var2 = (byte)(var2 | 8);
      }

      if (this.beardModel != nullptr) {
         var2 = (byte)(var2 | 16);
      }

      if (this.hairModel != nullptr) {
         var2 = (byte)(var2 | 32);
      }

      if (this.skinTextureName != nullptr) {
         var2 = (byte)(var2 | 64);
      }

      var1.put(var2);
      if (this.hairColor != nullptr) {
         var1.put(this.hairColor.getRedByte());
         var1.put(this.hairColor.getGreenByte());
         var1.put(this.hairColor.getBlueByte());
      }

      if (this.beardColor != nullptr) {
         var1.put(this.beardColor.getRedByte());
         var1.put(this.beardColor.getGreenByte());
         var1.put(this.beardColor.getBlueByte());
      }

      if (this.skinColor != nullptr) {
         var1.put(this.skinColor.getRedByte());
         var1.put(this.skinColor.getGreenByte());
         var1.put(this.skinColor.getBlueByte());
      }

      var1.put((byte)this.bodyHair);
      var1.put((byte)this.skinTexture);
      var1.put((byte)this.zombieRotStage);
      if (this.skinTextureName != nullptr) {
         GameWindow.WriteString(var1, this.skinTextureName);
      }

      if (this.beardModel != nullptr) {
         GameWindow.WriteString(var1, this.beardModel);
      }

      if (this.hairModel != nullptr) {
         GameWindow.WriteString(var1, this.hairModel);
      }

      var1.put((byte)this.blood.length);

      for (int var3 = 0; var3 < this.blood.length; var3++) {
         var1.put(this.blood[var3]);
      }

      var1.put((byte)this.dirt.length);

      for (int var5 = 0; var5 < this.dirt.length; var5++) {
         var1.put(this.dirt[var5]);
      }

      var1.put((byte)this.holes.length);

      for (int var6 = 0; var6 < this.holes.length; var6++) {
         var1.put(this.holes[var6]);
      }

      var1.put((byte)this.bodyVisuals.size());

      for (int var7 = 0; var7 < this.bodyVisuals.size(); var7++) {
    ItemVisual var4 = (ItemVisual)this.bodyVisuals.get(var7);
         var4.save(var1);
      }

      GameWindow.WriteString(var1, this.getNonAttachedHair());
    uint8_t var8 = 0;
      if (this.naturalHairColor != nullptr) {
         var8 = (byte)(var8 | 4);
      }

      if (this.naturalBeardColor != nullptr) {
         var8 = (byte)(var8 | 2);
      }

      var1.put(var8);
      if (this.naturalHairColor != nullptr) {
         var1.put(this.naturalHairColor.getRedByte());
         var1.put(this.naturalHairColor.getGreenByte());
         var1.put(this.naturalHairColor.getBlueByte());
      }

      if (this.naturalBeardColor != nullptr) {
         var1.put(this.naturalBeardColor.getRedByte());
         var1.put(this.naturalBeardColor.getGreenByte());
         var1.put(this.naturalBeardColor.getBlueByte());
      }
   }

    void load(ByteBuffer var1, int var2) {
      this.clear();
    int var3 = var1.get() & 255;
      if ((var3 & 4) != 0) {
    int var4 = var1.get() & 255;
    int var5 = var1.get() & 255;
    int var6 = var1.get() & 255;
         this.hairColor = std::make_shared<ImmutableColor>(var4, var5, var6);
      }

      if ((var3 & 2) != 0) {
    int var9 = var1.get() & 255;
    int var15 = var1.get() & 255;
    int var22 = var1.get() & 255;
         this.beardColor = std::make_shared<ImmutableColor>(var9, var15, var22);
      }

      if ((var3 & 8) != 0) {
    int var10 = var1.get() & 255;
    int var16 = var1.get() & 255;
    int var23 = var1.get() & 255;
         this.skinColor = std::make_shared<ImmutableColor>(var10, var16, var23);
      }

      this.bodyHair = var1.get();
      this.skinTexture = var1.get();
      if (var2 >= 156) {
         this.zombieRotStage = var1.get();
      }

      if ((var3 & 64) != 0) {
         this.skinTextureName = GameWindow.ReadString(var1);
      }

      if ((var3 & 16) != 0) {
         this.beardModel = GameWindow.ReadString(var1);
      }

      if ((var3 & 32) != 0) {
         this.hairModel = GameWindow.ReadString(var1);
      }

    uint8_t var11 = var1.get();

      for (int var17 = 0; var17 < var11; var17++) {
    uint8_t var24 = var1.get();
         if (var17 < this.blood.length) {
            this.blood[var17] = var24;
         }
      }

      if (var2 >= 163) {
         var11 = var1.get();

         for (int var18 = 0; var18 < var11; var18++) {
    uint8_t var25 = var1.get();
            if (var18 < this.dirt.length) {
               this.dirt[var18] = var25;
            }
         }
      }

      var11 = var1.get();

      for (int var19 = 0; var19 < var11; var19++) {
    uint8_t var26 = var1.get();
         if (var19 < this.holes.length) {
            this.holes[var19] = var26;
         }
      }

      var11 = var1.get();

      for (int var20 = 0; var20 < var11; var20++) {
    ItemVisual var27 = std::make_shared<ItemVisual>();
         var27.load(var1, var2);
         this.bodyVisuals.push_back(var27);
      }

      this.setNonAttachedHair(GameWindow.ReadString(var1));
      if (var2 >= 187) {
    int var21 = var1.get() & 255;
         if ((var21 & 4) != 0) {
    int var28 = var1.get() & 255;
    int var7 = var1.get() & 255;
    int var8 = var1.get() & 255;
            this.naturalHairColor = std::make_shared<ImmutableColor>(var28, var7, var8);
         }

         if ((var21 & 2) != 0) {
    int var29 = var1.get() & 255;
    int var30 = var1.get() & 255;
    int var31 = var1.get() & 255;
            this.naturalBeardColor = std::make_shared<ImmutableColor>(var29, var30, var31);
         }
      }
   }

    Model getModel() {
      if (this.forceModel != nullptr) {
         return this.forceModel;
      } else if (this.isSkeleton()) {
         return this.isFemale() ? ModelManager.instance.m_skeletonFemaleModel : ModelManager.instance.m_skeletonMaleModel;
      } else {
         return this.isFemale() ? ModelManager.instance.m_femaleModel : ModelManager.instance.m_maleModel;
      }
   }

    ModelScript getModelScript() {
      return this.forceModelScript != nullptr
         ? ScriptManager.instance.getModelScript(this.forceModelScript)
         : ScriptManager.instance.getModelScript(this.isFemale() ? "FemaleBody" : "MaleBody");
   }

    static CharacterMask GetMask(ItemVisuals var0) {
    CharacterMask var1 = std::make_shared<CharacterMask>();

      for (int var2 = var0.size() - 1; var2 >= 0; var2--) {
         ((ItemVisual)var0.get(var2)).getClothingItemCombinedMask(var1);
      }

    return var1;
   }

    void synchWithOutfit(Outfit var1) {
      if (var1 != nullptr) {
         this.hairColor = var1.RandomData.m_hairColor;
         this.beardColor = this.hairColor;
         this.hairModel = this.owner.isFemale() ? var1.RandomData.m_femaleHairName : var1.RandomData.m_maleHairName;
         this.beardModel = this.owner.isFemale() ? nullptr : var1.RandomData.m_beardName;
         this.getSkinTexture();
      }
   }

    void dressInNamedOutfit(const std::string& var1, ItemVisuals var2) {
      var2.clear();
      if (!StringUtils.isNullOrWhitespace(var1)) {
    Outfit var3 = this.owner.isFemale() ? OutfitManager.instance.FindFemaleOutfit(var1) : OutfitManager.instance.FindMaleOutfit(var1);
         if (var3 != nullptr) {
    Outfit var4 = var3.clone();
            var4.Randomize();
            this.dressInOutfit(var4, var2);
         }
      }
   }

    void dressInClothingItem(const std::string& var1, ItemVisuals var2) {
      this.dressInClothingItem(var1, var2, true);
   }

    void dressInClothingItem(const std::string& var1, ItemVisuals var2, bool var3) {
      if (var3) {
         this.clear();
         var2.clear();
      }

    ClothingItem var4 = OutfitManager.instance.getClothingItem(var1);
      if (var4 != nullptr) {
    Outfit var5 = std::make_shared<Outfit>();
    ClothingItemReference var6 = std::make_shared<ClothingItemReference>();
         var6.itemGUID = var1;
         var5.m_items.push_back(var6);
         var5.m_Pants = false;
         var5.m_Top = false;
         var5.Randomize();
         this.dressInOutfit(var5, var2);
      }
   }

    void dressInOutfit(Outfit var1, ItemVisuals var2) {
      this.setOutfit(var1);
      this.getItemVisualLocations(var2, itemVisualLocations);
      if (var1.m_Pants) {
         std::string var3 = var1.m_AllowPantsHue
            ? DefaultClothing.instance.pickPantsHue()
            : (var1.m_AllowPantsTint ? DefaultClothing.instance.pickPantsTint() : DefaultClothing.instance.pickPantsTexture());
         this.addClothingItem(var2, itemVisualLocations, var3, nullptr);
      }

      if (var1.m_Top && var1.RandomData.m_hasTop) {
    std::string var6;
         if (var1.RandomData.m_hasTShirt) {
            if (var1.RandomData.m_hasTShirtDecal && var1.GetMask().isTorsoVisible() && var1.m_AllowTShirtDecal) {
               var6 = var1.m_AllowTopTint ? DefaultClothing.instance.pickTShirtDecalTint() : DefaultClothing.instance.pickTShirtDecalTexture();
            } else {
               var6 = var1.m_AllowTopTint ? DefaultClothing.instance.pickTShirtTint() : DefaultClothing.instance.pickTShirtTexture();
            }
         } else {
            var6 = var1.m_AllowTopTint ? DefaultClothing.instance.pickVestTint() : DefaultClothing.instance.pickVestTexture();
         }

         this.addClothingItem(var2, itemVisualLocations, var6, nullptr);
      }

      for (int var7 = 0; var7 < var1.m_items.size(); var7++) {
    ClothingItemReference var4 = (ClothingItemReference)var1.m_items.get(var7);
    ClothingItem var5 = var4.getClothingItem();
         if (var5 != nullptr && var5.isReady()) {
            this.addClothingItem(var2, itemVisualLocations, var5.m_Name, var4);
         }
      }

      var1.m_Pants = false;
      var1.m_Top = false;
      var1.RandomData.m_topTexture = nullptr;
      var1.RandomData.m_pantsTexture = nullptr;
   }

    ItemVisuals getBodyVisuals() {
      return this.bodyVisuals;
   }

    ItemVisual addBodyVisual(const std::string& var1) {
      return this.addBodyVisualFromClothingItemName(var1);
   }

    ItemVisual addBodyVisualFromItemType(const std::string& var1) {
    Item var2 = ScriptManager.instance.getItem(var1);
      return var2 != nullptr && !StringUtils.isNullOrWhitespace(var2.getClothingItem()) ? this.addBodyVisualFromClothingItemName(var2.getClothingItem()) : nullptr;
   }

    ItemVisual addBodyVisualFromClothingItemName(const std::string& var1) {
      if (StringUtils.isNullOrWhitespace(var1)) {
    return nullptr;
      } else {
    Item var2 = ScriptManager.instance.getItemForClothingItem(var1);
         if (var2 == nullptr) {
    return nullptr;
         } else {
    ClothingItem var3 = var2.getClothingItemAsset();
            if (var3 == nullptr) {
    return nullptr;
            } else {
               for (int var4 = 0; var4 < this.bodyVisuals.size(); var4++) {
                  if (((ItemVisual)this.bodyVisuals.get(var4)).getClothingItemName() == var1)) {
    return nullptr;
                  }
               }

    ClothingItemReference var6 = std::make_shared<ClothingItemReference>();
               var6.itemGUID = var3.m_GUID;
               var6.randomize();
    ItemVisual var5 = std::make_shared<ItemVisual>();
               var5.setItemType(var2.getFullName());
               var5.synchWithOutfit(var6);
               this.bodyVisuals.push_back(var5);
    return var5;
            }
         }
      }
   }

    ItemVisual removeBodyVisualFromItemType(const std::string& var1) {
      for (int var2 = 0; var2 < this.bodyVisuals.size(); var2++) {
    ItemVisual var3 = (ItemVisual)this.bodyVisuals.get(var2);
         if (var3.getItemType() == var1)) {
            this.bodyVisuals.remove(var2);
    return var3;
         }
      }

    return nullptr;
   }

    bool hasBodyVisualFromItemType(const std::string& var1) {
      for (int var2 = 0; var2 < this.bodyVisuals.size(); var2++) {
    ItemVisual var3 = (ItemVisual)this.bodyVisuals.get(var2);
         if (var3.getItemType() == var1)) {
    return true;
         }
      }

    return false;
   }

    void getItemVisualLocations(ItemVisuals var1, std::vector<std::string> var2) {
      var2.clear();

      for (int var3 = 0; var3 < var1.size(); var3++) {
    ItemVisual var4 = (ItemVisual)var1.get(var3);
    Item var5 = var4.getScriptItem();
         if (var5 == nullptr) {
            var2.push_back(nullptr);
         } else {
    std::string var6 = var5.getBodyLocation();
            if (StringUtils.isNullOrWhitespace(var6)) {
               var6 = var5.CanBeEquipped;
            }

            var2.push_back(var6);
         }
      }
   }

    ItemVisual addClothingItem(ItemVisuals var1, Item var2) {
      if (var2 == nullptr) {
    return nullptr;
      } else {
    ClothingItem var3 = var2.getClothingItemAsset();
         if (var3 == nullptr) {
    return nullptr;
         } else if (!var3.isReady()) {
    return nullptr;
         } else {
            this.getItemVisualLocations(var1, itemVisualLocations);
            return this.addClothingItem(var1, itemVisualLocations, var3.m_Name, nullptr);
         }
      }
   }

    ItemVisual addClothingItem(ItemVisuals var1, std::vector<std::string> var2, const std::string& var3, ClothingItemReference var4) {
      assert var1.size() == var2.size();

      if (var4 != nullptr && !var4.RandomData.m_Active) {
    return nullptr;
      } else if (StringUtils.isNullOrWhitespace(var3)) {
    return nullptr;
      } else {
    Item var5 = ScriptManager.instance.getItemForClothingItem(var3);
         if (var5 == nullptr) {
            if (DebugLog.isEnabled(DebugType.Clothing)) {
               DebugLog.Clothing.warn("Could not find item type for %s", new Object[]{var3});
            }

    return nullptr;
         } else {
    ClothingItem var6 = var5.getClothingItemAsset();
            if (var6 == nullptr) {
    return nullptr;
            } else if (!var6.isReady()) {
    return nullptr;
            } else {
    std::string var7 = var5.getBodyLocation();
               if (StringUtils.isNullOrWhitespace(var7)) {
                  var7 = var5.CanBeEquipped;
               }

               if (StringUtils.isNullOrWhitespace(var7)) {
    return nullptr;
               } else {
                  if (var4 == nullptr) {
                     var4 = std::make_unique<ClothingItemReference>();
                     var4.itemGUID = var6.m_GUID;
                     var4.randomize();
                  }

                  if (!var4.RandomData.m_Active) {
    return nullptr;
                  } else {
    BodyLocationGroup var8 = BodyLocations.getGroup("Human");
    BodyLocation var9 = var8.getLocation(var7);
                     if (var9 == nullptr) {
                        DebugLog.General.error("The game can't found location '" + var7 + "' for the item '" + var5.name + "'");
    return nullptr;
                     } else {
                        if (!var9.isMultiItem()) {
    int var10 = var2.indexOf(var7);
                           if (var10 != -1) {
                              var1.remove(var10);
                              var2.remove(var10);
                           }
                        }

                        for (int var13 = 0; var13 < var1.size(); var13++) {
                           if (var8.isExclusive(var7, (std::string)var2.get(var13))) {
                              var1.remove(var13);
                              var2.remove(var13);
                              var13--;
                           }
                        }

                        assert var1.size() == var2.size();

    int var14 = var8.indexOf(var7);
    int var11 = var1.size();

                        for (int var12 = 0; var12 < var1.size(); var12++) {
                           if (var8.indexOf((std::string)var2.get(var12)) > var14) {
                              var11 = var12;
                              break;
                           }
                        }

    ItemVisual var15 = std::make_shared<ItemVisual>();
                        var15.setItemType(var5.getFullName());
                        var15.synchWithOutfit(var4);
                        var1.push_back(var11, var15);
                        var2.push_back(var11, var7);
    return var15;
                     }
                  }
               }
            }
         }
      }
   }

    Outfit getOutfit() {
      return this.outfit;
   }

    void setOutfit(Outfit var1) {
      this.outfit = var1;
   }

    std::string getNonAttachedHair() {
      return this.nonAttachedHair;
   }

    void setNonAttachedHair(const std::string& var1) {
      if (StringUtils.isNullOrWhitespace(var1)) {
         var1 = nullptr;
      }

      this.nonAttachedHair = var1;
   }

    void setForceModel(Model var1) {
      this.forceModel = var1;
   }

    void setForceModelScript(const std::string& var1) {
      this.forceModelScript = var1;
   }

    static std::stringstream toString(ImmutableColor var0, std::stringstream var1) {
      var1.append(var0.getRedByte() & 255);
      var1.append(",");
      var1.append(var0.getGreenByte() & 255);
      var1.append(",");
      var1.append(var0.getBlueByte() & 255);
    return var1;
   }

    static ImmutableColor colorFromString(const std::string& var0) {
      std::string[] var1 = var0.split(",");
      if (var1.length == 3) {
         try {
    int var2 = int.parseInt(var1[0]);
    int var3 = int.parseInt(var1[1]);
    int var4 = int.parseInt(var1[2]);
            return std::make_shared<ImmutableColor>(var2 / 255.0F, var3 / 255.0F, var4 / 255.0F);
         } catch (NumberFormatException var5) {
         }
      }

    return nullptr;
   }

    std::string getLastStandString() {
    std::stringstream var1 = new std::stringstream();
      var1.append("version=");
      var1.append(1);
      var1.append(";");
      if (this.getHairColor() != nullptr) {
         var1.append("hairColor=");
         toString(this.getHairColor(), var1);
         var1.append(";");
      }

      if (this.getBeardColor() != nullptr) {
         var1.append("beardColor=");
         toString(this.getBeardColor(), var1);
         var1.append(";");
      }

      if (this.getNaturalHairColor() != nullptr) {
         var1.append("naturalHairColor=");
         toString(this.getNaturalHairColor(), var1);
         var1.append(";");
      }

      if (this.getNaturalBeardColor() != nullptr) {
         var1.append("naturalBeardColor=");
         toString(this.getNaturalBeardColor(), var1);
         var1.append(";");
      }

      if (this.getSkinColor() != nullptr) {
         var1.append("skinColor=");
         toString(this.getSkinColor(), var1);
         var1.append(";");
      }

      var1.append("bodyHair=");
      var1.append(this.getBodyHairIndex());
      var1.append(";");
      var1.append("skinTexture=");
      var1.append(this.getSkinTextureIndex());
      var1.append(";");
      if (this.getSkinTexture() != nullptr) {
         var1.append("skinTextureName=");
         var1.append(this.getSkinTexture());
         var1.append(";");
      }

      if (this.getHairModel() != nullptr) {
         var1.append("hairModel=");
         var1.append(this.getHairModel());
         var1.append(";");
      }

      if (this.getBeardModel() != nullptr) {
         var1.append("beardModel=");
         var1.append(this.getBeardModel());
         var1.append(";");
      }

      return var1;
   }

    bool loadLastStandString(const std::string& var1) {
      var1 = var1.trim();
      if (!StringUtils.isNullOrWhitespace(var1) && var1.startsWith("version=")) {
    int var2 = -1;
         std::string[] var3 = var1.split(";");

         for (int var4 = 0; var4 < var3.length; var4++) {
    int var5 = var3[var4].indexOf(61);
            if (var5 != -1) {
    std::string var6 = var3[var4].substr(0, var5).trim();
    std::string var7 = var3[var4].substr(var5 + 1).trim();
               switch (var6) {
                  case "version":
                     var2 = int.parseInt(var7);
                     if (var2 < 1 || var2 > 1) {
    return false;
                     }
                     break;
                  case "beardColor":
    ImmutableColor var18 = colorFromString(var7);
                     if (var18 != nullptr) {
                        this.setBeardColor(var18);
                     }
                     break;
                  case "naturalBeardColor":
    ImmutableColor var17 = colorFromString(var7);
                     if (var17 != nullptr) {
                        this.setNaturalBeardColor(var17);
                     }
                     break;
                  case "beardModel":
                     this.setBeardModel(var7);
                     break;
                  case "bodyHair":
                     try {
                        this.setBodyHairIndex(int.parseInt(var7));
                     } catch (NumberFormatException var12) {
                     }
                     break;
                  case "hairColor":
    ImmutableColor var16 = colorFromString(var7);
                     if (var16 != nullptr) {
                        this.setHairColor(var16);
                     }
                     break;
                  case "naturalHairColor":
    ImmutableColor var15 = colorFromString(var7);
                     if (var15 != nullptr) {
                        this.setNaturalHairColor(var15);
                     }
                     break;
                  case "hairModel":
                     this.setHairModel(var7);
                     break;
                  case "skinColor":
    ImmutableColor var10 = colorFromString(var7);
                     if (var10 != nullptr) {
                        this.setSkinColor(var10);
                     }
                     break;
                  case "skinTexture":
                     try {
                        this.setSkinTextureIndex(int.parseInt(var7));
                     } catch (NumberFormatException var11) {
                     }
                     break;
                  case "skinTextureName":
                     this.setSkinTextureName(var7);
               }
            }
         }

    return true;
      } else {
    return false;
      }
   }
}
} // namespace visual
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
