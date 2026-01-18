#pragma once
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
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace visual {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class HumanVisual : public BaseVisual {
public:
  const IHumanVisual owner;
  ImmutableColor skinColor = ImmutableColor.white;
  int skinTexture = -1;
  std::string skinTextureName = null;
  int zombieRotStage = -1;
  ImmutableColor hairColor;
  ImmutableColor beardColor;
  ImmutableColor naturalHairColor;
  ImmutableColor naturalBeardColor;
  std::string hairModel;
  std::string beardModel;
  int bodyHair = -1;
private
  final byte[] blood = new byte[BloodBodyPartType.MAX.index()];
private
  final byte[] dirt = new byte[BloodBodyPartType.MAX.index()];
private
  final byte[] holes = new byte[BloodBodyPartType.MAX.index()];
  const ItemVisuals bodyVisuals = new ItemVisuals();
  Outfit outfit = null;
  std::string nonAttachedHair = null;
  Model forceModel = null;
  std::string forceModelScript = null;
private
  static final ArrayList<String> itemVisualLocations =
      std::make_unique<ArrayList<>>();
  static const int LASTSTAND_VERSION1 = 1;
  static const int LASTSTAND_VERSION = 1;

public
  HumanVisual(IHumanVisual _owner) {
    this.owner = _owner;
    Arrays.fill(this.blood, (byte)0);
    Arrays.fill(this.dirt, (byte)0);
    Arrays.fill(this.holes, (byte)0);
  }

  bool isFemale() { return this.owner.isFemale(); }

  bool isZombie() { return this.owner.isZombie(); }

  bool isSkeleton() { return this.owner.isSkeleton(); }

  void setSkinColor(ImmutableColor color) { this.skinColor = color; }

  ImmutableColor getSkinColor() {
    if (this.skinColor == nullptr) {
      this.skinColor = new ImmutableColor(SurvivorDesc.getRandomSkinColor());
    }

    return this.skinColor;
  }

  void setBodyHairIndex(int index) { this.bodyHair = index; }

  int getBodyHairIndex() { return this.bodyHair; }

  void setSkinTextureIndex(int index) { this.skinTexture = index; }

  int getSkinTextureIndex() { return this.skinTexture; }

  void setSkinTextureName(const std::string &textureName) {
    this.skinTextureName = textureName;
  }

  float lerp(float start, float __end__, float delta) {
    if (delta < 0.0F) {
      delta = 0.0F;
    }

    if (delta >= 1.0F) {
      delta = 1.0F;
    }

    float float0 = __end__ - start;
    float float1 = float0 * delta;
    return start + float1;
  }

  int pickRandomZombieRotStage() {
    int int0 = Math.max((int)IsoWorld.instance.getWorldAgeDays(), 0);
    float float0 = 20.0F;
    float float1 = 90.0F;
    float float2 = 100.0F;
    float float3 = 20.0F;
    float float4 = 10.0F;
    float float5 = 30.0F;
    if (int0 >= 180) {
      float3 = 0.0F;
      float5 = 10.0F;
    }

    float float6 = int0 - float0;
    float float7 = float6 / (float1 - float0);
    float float8 = this.lerp(float2, float3, float7);
    float float9 = this.lerp(float4, float5, float7);
    float float10 = OutfitRNG.Next(100);
    if (float10 < float8) {
      return 1;
    } else {
      return float10 < float9 + float8 ? 2 : 3;
    }
  }

  std::string getSkinTexture() {
    if (this.skinTextureName != nullptr) {
      return this.skinTextureName;
    } else {
      std::string string = "";
      std::vector arrayList = this.owner.isFemale()
                                  ? PopTemplateManager.instance.m_FemaleSkins
                                  : PopTemplateManager.instance.m_MaleSkins;
      if (this.owner.isZombie() && this.owner.isSkeleton()) {
        if (this.owner.isFemale()) {
          arrayList = PopTemplateManager.instance.m_SkeletonFemaleSkins_Zombie;
        } else {
          arrayList = PopTemplateManager.instance.m_SkeletonMaleSkins_Zombie;
        }
      } else if (this.owner.isZombie()) {
        if (this.zombieRotStage < 1 || this.zombieRotStage > 3) {
          this.zombieRotStage = this.pickRandomZombieRotStage();
        }

        switch (this.zombieRotStage) {
        case 1:
          arrayList = this.owner.isFemale()
                          ? PopTemplateManager.instance.m_FemaleSkins_Zombie1
                          : PopTemplateManager.instance.m_MaleSkins_Zombie1;
          break;
        case 2:
          arrayList = this.owner.isFemale()
                          ? PopTemplateManager.instance.m_FemaleSkins_Zombie2
                          : PopTemplateManager.instance.m_MaleSkins_Zombie2;
          break;
        case 3:
          arrayList = this.owner.isFemale()
                          ? PopTemplateManager.instance.m_FemaleSkins_Zombie3
                          : PopTemplateManager.instance.m_MaleSkins_Zombie3;
        }
      } else if (!this.owner.isFemale()) {
        string = !this.owner.isZombie() && this.bodyHair >= 0 ? "a" : "";
      }

      if (this.skinTexture == arrayList.size()) {
        this.skinTexture--;
      } else if (this.skinTexture < 0 || this.skinTexture > arrayList.size()) {
        this.skinTexture = OutfitRNG.Next(arrayList.size());
      }

      return (String)arrayList.get(this.skinTexture) + string;
    }
  }

  void setHairColor(ImmutableColor color) { this.hairColor = color; }

  ImmutableColor getHairColor() {
    if (this.hairColor == nullptr) {
      this.hairColor = HairOutfitDefinitions.instance.getRandomHaircutColor(
          this.outfit != nullptr ? this.outfit.m_Name : nullptr);
    }

    return this.hairColor;
  }

  void setBeardColor(ImmutableColor color) { this.beardColor = color; }

  ImmutableColor getBeardColor() {
    if (this.beardColor == nullptr) {
      this.beardColor = this.getHairColor();
    }

    return this.beardColor;
  }

  void setNaturalHairColor(ImmutableColor color) {
    this.naturalHairColor = color;
  }

  ImmutableColor getNaturalHairColor() {
    if (this.naturalHairColor == nullptr) {
      this.naturalHairColor = this.getHairColor();
    }

    return this.naturalHairColor;
  }

  void setNaturalBeardColor(ImmutableColor color) {
    this.naturalBeardColor = color;
  }

  ImmutableColor getNaturalBeardColor() {
    if (this.naturalBeardColor == nullptr) {
      this.naturalBeardColor = this.getNaturalHairColor();
    }

    return this.naturalBeardColor;
  }

  void setHairModel(const std::string &model) { this.hairModel = model; }

  std::string getHairModel() {
    if (this.owner.isFemale()) {
      if (HairStyles.instance.FindFemaleStyle(this.hairModel) == nullptr) {
        this.hairModel = HairStyles.instance.getRandomFemaleStyle(
            this.outfit != nullptr ? this.outfit.m_Name : nullptr);
      }
    } else if (HairStyles.instance.FindMaleStyle(this.hairModel) == nullptr) {
      this.hairModel = HairStyles.instance.getRandomMaleStyle(
          this.outfit != nullptr ? this.outfit.m_Name : nullptr);
    }

    return this.hairModel;
  }

  void setBeardModel(const std::string &model) { this.beardModel = model; }

  std::string getBeardModel() {
    if (this.owner.isFemale()) {
      this.beardModel = nullptr;
    } else if (BeardStyles.instance.FindStyle(this.beardModel) == nullptr) {
      this.beardModel = BeardStyles.instance.getRandomStyle(
          this.outfit != nullptr ? this.outfit.m_Name : nullptr);
    }

    return this.beardModel;
  }

  void setBlood(BloodBodyPartType bodyPartType, float amount) {
    amount = Math.max(0.0F, Math.min(1.0F, amount));
    this.blood[bodyPartType.index()] = (byte)(amount * 255.0F);
  }

  float getBlood(BloodBodyPartType bodyPartType) {
    return (this.blood[bodyPartType.index()] & 255) / 255.0F;
  }

  void setDirt(BloodBodyPartType bodyPartType, float amount) {
    amount = Math.max(0.0F, Math.min(1.0F, amount));
    this.dirt[bodyPartType.index()] = (byte)(amount * 255.0F);
  }

  float getDirt(BloodBodyPartType bodyPartType) {
    return (this.dirt[bodyPartType.index()] & 255) / 255.0F;
  }

  void setHole(BloodBodyPartType bodyPartType) {
    this.holes[bodyPartType.index()] = -1;
  }

  float getHole(BloodBodyPartType bodyPartType) {
    return (this.holes[bodyPartType.index()] & 255) / 255.0F;
  }

  void removeBlood() { Arrays.fill(this.blood, (byte)0); }

  void removeDirt() { Arrays.fill(this.dirt, (byte)0); }

  void randomBlood() {
    for (int int0 = 0; int0 < BloodBodyPartType.MAX.index(); int0++) {
      this.setBlood(BloodBodyPartType.FromIndex(int0),
                    OutfitRNG.Next(0.0F, 1.0F));
    }
  }

  void randomDirt() {
    for (int int0 = 0; int0 < BloodBodyPartType.MAX.index(); int0++) {
      this.setDirt(BloodBodyPartType.FromIndex(int0),
                   OutfitRNG.Next(0.0F, 1.0F));
    }
  }

  float getTotalBlood() {
    float float0 = 0.0F;

    for (int int0 = 0; int0 < this.blood.length; int0++) {
      float0 += (this.blood[int0] & 255) / 255.0F;
    }

    return float0;
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

  void copyFrom(BaseVisual other_) {
    if (other_ == nullptr) {
      this.clear();
    } else {
      HumanVisual humanVisual = Type.tryCastTo(other_, HumanVisual.class);
      if (humanVisual == nullptr) {
        throw new IllegalArgumentException("expected HumanVisual, got " +
                                           other_);
      } else {
        humanVisual.getHairColor();
        humanVisual.getNaturalHairColor();
        humanVisual.getNaturalBeardColor();
        humanVisual.getHairModel();
        humanVisual.getBeardModel();
        humanVisual.getSkinTexture();
        this.skinColor = humanVisual.skinColor;
        this.skinTexture = humanVisual.skinTexture;
        this.skinTextureName = humanVisual.skinTextureName;
        this.zombieRotStage = humanVisual.zombieRotStage;
        this.hairColor = humanVisual.hairColor;
        this.beardColor = humanVisual.beardColor;
        this.naturalHairColor = humanVisual.naturalHairColor;
        this.naturalBeardColor = humanVisual.naturalBeardColor;
        this.hairModel = humanVisual.hairModel;
        this.nonAttachedHair = humanVisual.nonAttachedHair;
        this.beardModel = humanVisual.beardModel;
        this.bodyHair = humanVisual.bodyHair;
        this.outfit = humanVisual.outfit;
        System.arraycopy(humanVisual.blood, 0, this.blood, 0,
                         this.blood.length);
        System.arraycopy(humanVisual.dirt, 0, this.dirt, 0, this.dirt.length);
        System.arraycopy(humanVisual.holes, 0, this.holes, 0,
                         this.holes.length);
        this.bodyVisuals.clear();
        this.bodyVisuals.addAll(humanVisual.bodyVisuals);
        this.forceModel = humanVisual.forceModel;
        this.forceModelScript = humanVisual.forceModelScript;
      }
    }
  }

  void save(ByteBuffer output) {
    uint8_t byte0 = 0;
    if (this.hairColor != nullptr) {
      byte0 = (byte)(byte0 | 4);
    }

    if (this.beardColor != nullptr) {
      byte0 = (byte)(byte0 | 2);
    }

    if (this.skinColor != nullptr) {
      byte0 = (byte)(byte0 | 8);
    }

    if (this.beardModel != nullptr) {
      byte0 = (byte)(byte0 | 16);
    }

    if (this.hairModel != nullptr) {
      byte0 = (byte)(byte0 | 32);
    }

    if (this.skinTextureName != nullptr) {
      byte0 = (byte)(byte0 | 64);
    }

    output.put(byte0);
    if (this.hairColor != nullptr) {
      output.put(this.hairColor.getRedByte());
      output.put(this.hairColor.getGreenByte());
      output.put(this.hairColor.getBlueByte());
    }

    if (this.beardColor != nullptr) {
      output.put(this.beardColor.getRedByte());
      output.put(this.beardColor.getGreenByte());
      output.put(this.beardColor.getBlueByte());
    }

    if (this.skinColor != nullptr) {
      output.put(this.skinColor.getRedByte());
      output.put(this.skinColor.getGreenByte());
      output.put(this.skinColor.getBlueByte());
    }

    output.put((byte)this.bodyHair);
    output.put((byte)this.skinTexture);
    output.put((byte)this.zombieRotStage);
    if (this.skinTextureName != nullptr) {
      GameWindow.WriteString(output, this.skinTextureName);
    }

    if (this.beardModel != nullptr) {
      GameWindow.WriteString(output, this.beardModel);
    }

    if (this.hairModel != nullptr) {
      GameWindow.WriteString(output, this.hairModel);
    }

    output.put((byte)this.blood.length);

    for (int int0 = 0; int0 < this.blood.length; int0++) {
      output.put(this.blood[int0]);
    }

    output.put((byte)this.dirt.length);

    for (int int1 = 0; int1 < this.dirt.length; int1++) {
      output.put(this.dirt[int1]);
    }

    output.put((byte)this.holes.length);

    for (int int2 = 0; int2 < this.holes.length; int2++) {
      output.put(this.holes[int2]);
    }

    output.put((byte)this.bodyVisuals.size());

    for (int int3 = 0; int3 < this.bodyVisuals.size(); int3++) {
      ItemVisual itemVisual = this.bodyVisuals.get(int3);
      itemVisual.save(output);
    }

    GameWindow.WriteString(output, this.getNonAttachedHair());
    uint8_t byte1 = 0;
    if (this.naturalHairColor != nullptr) {
      byte1 = (byte)(byte1 | 4);
    }

    if (this.naturalBeardColor != nullptr) {
      byte1 = (byte)(byte1 | 2);
    }

    output.put(byte1);
    if (this.naturalHairColor != nullptr) {
      output.put(this.naturalHairColor.getRedByte());
      output.put(this.naturalHairColor.getGreenByte());
      output.put(this.naturalHairColor.getBlueByte());
    }

    if (this.naturalBeardColor != nullptr) {
      output.put(this.naturalBeardColor.getRedByte());
      output.put(this.naturalBeardColor.getGreenByte());
      output.put(this.naturalBeardColor.getBlueByte());
    }
  }

  void load(ByteBuffer input, int WorldVersion) {
    this.clear();
    int int0 = input.get() & 255;
    if ((int0 & 4) != 0) {
      int int1 = input.get() & 255;
      int int2 = input.get() & 255;
      int int3 = input.get() & 255;
      this.hairColor = new ImmutableColor(int1, int2, int3);
    }

    if ((int0 & 2) != 0) {
      int int4 = input.get() & 255;
      int int5 = input.get() & 255;
      int int6 = input.get() & 255;
      this.beardColor = new ImmutableColor(int4, int5, int6);
    }

    if ((int0 & 8) != 0) {
      int int7 = input.get() & 255;
      int int8 = input.get() & 255;
      int int9 = input.get() & 255;
      this.skinColor = new ImmutableColor(int7, int8, int9);
    }

    this.bodyHair = input.get();
    this.skinTexture = input.get();
    if (WorldVersion >= 156) {
      this.zombieRotStage = input.get();
    }

    if ((int0 & 64) != 0) {
      this.skinTextureName = GameWindow.ReadString(input);
    }

    if ((int0 & 16) != 0) {
      this.beardModel = GameWindow.ReadString(input);
    }

    if ((int0 & 32) != 0) {
      this.hairModel = GameWindow.ReadString(input);
    }

    uint8_t byte0 = input.get();

    for (int int10 = 0; int10 < byte0; int10++) {
      uint8_t byte1 = input.get();
      if (int10 < this.blood.length) {
        this.blood[int10] = byte1;
      }
    }

    if (WorldVersion >= 163) {
      byte0 = input.get();

      for (int int11 = 0; int11 < byte0; int11++) {
        uint8_t byte2 = input.get();
        if (int11 < this.dirt.length) {
          this.dirt[int11] = byte2;
        }
      }
    }

    byte0 = input.get();

    for (int int12 = 0; int12 < byte0; int12++) {
      uint8_t byte3 = input.get();
      if (int12 < this.holes.length) {
        this.holes[int12] = byte3;
      }
    }

    byte0 = input.get();

    for (int int13 = 0; int13 < byte0; int13++) {
      ItemVisual itemVisual = new ItemVisual();
      itemVisual.load(input, WorldVersion);
      this.bodyVisuals.add(itemVisual);
    }

    this.setNonAttachedHair(GameWindow.ReadString(input));
    if (WorldVersion >= 187) {
      int int14 = input.get() & 255;
      if ((int14 & 4) != 0) {
        int int15 = input.get() & 255;
        int int16 = input.get() & 255;
        int int17 = input.get() & 255;
        this.naturalHairColor = new ImmutableColor(int15, int16, int17);
      }

      if ((int14 & 2) != 0) {
        int int18 = input.get() & 255;
        int int19 = input.get() & 255;
        int int20 = input.get() & 255;
        this.naturalBeardColor = new ImmutableColor(int18, int19, int20);
      }
    }
  }

  Model getModel() {
    if (this.forceModel != nullptr) {
      return this.forceModel;
    } else if (this.isSkeleton()) {
      return this.isFemale() ? ModelManager.instance.m_skeletonFemaleModel
                             : ModelManager.instance.m_skeletonMaleModel;
    } else {
      return this.isFemale() ? ModelManager.instance.m_femaleModel
                             : ModelManager.instance.m_maleModel;
    }
  }

  ModelScript getModelScript() {
    return this.forceModelScript != nullptr
               ? ScriptManager.instance.getModelScript(this.forceModelScript)
               : ScriptManager.instance.getModelScript(
                     this.isFemale() ? "FemaleBody" : "MaleBody");
  }

  static CharacterMask GetMask(ItemVisuals itemVisuals) {
    CharacterMask characterMask = new CharacterMask();

    for (int int0 = itemVisuals.size() - 1; int0 >= 0; int0--) {
      itemVisuals.get(int0).getClothingItemCombinedMask(characterMask);
    }

    return characterMask;
  }

  void synchWithOutfit(Outfit _outfit) {
    if (_outfit != nullptr) {
      this.hairColor = _outfit.RandomData.m_hairColor;
      this.beardColor = this.hairColor;
      this.hairModel = this.owner.isFemale()
                           ? _outfit.RandomData.m_femaleHairName
                           : _outfit.RandomData.m_maleHairName;
      this.beardModel =
          this.owner.isFemale() ? nullptr : _outfit.RandomData.m_beardName;
      this.getSkinTexture();
    }
  }

  void dressInNamedOutfit(const std::string &outfitName,
                          ItemVisuals itemVisuals) {
    itemVisuals.clear();
    if (!StringUtils.isNullOrWhitespace(outfitName)) {
      Outfit outfit0 = this.owner.isFemale()
                           ? OutfitManager.instance.FindFemaleOutfit(outfitName)
                           : OutfitManager.instance.FindMaleOutfit(outfitName);
      if (outfit0 != nullptr) {
        Outfit outfit1 = outfit0.clone();
        outfit1.Randomize();
        this.dressInOutfit(outfit1, itemVisuals);
      }
    }
  }

  void dressInClothingItem(const std::string &itemGUID,
                           ItemVisuals itemVisuals) {
    this.dressInClothingItem(itemGUID, itemVisuals, true);
  }

  void dressInClothingItem(const std::string &itemGUID, ItemVisuals itemVisuals,
                           bool clearCurrentVisuals) {
    if (clearCurrentVisuals) {
      this.clear();
      itemVisuals.clear();
    }

    ClothingItem clothingItem =
        OutfitManager.instance.getClothingItem(itemGUID);
    if (clothingItem != nullptr) {
      Outfit outfitx = new Outfit();
      ClothingItemReference clothingItemReference = new ClothingItemReference();
      clothingItemReference.itemGUID = itemGUID;
      outfitx.m_items.add(clothingItemReference);
      outfitx.m_Pants = false;
      outfitx.m_Top = false;
      outfitx.Randomize();
      this.dressInOutfit(outfitx, itemVisuals);
    }
  }

  void dressInOutfit(Outfit outfitx, ItemVisuals itemVisuals) {
    this.setOutfit(outfitx);
    this.getItemVisualLocations(itemVisuals, itemVisualLocations);
    if (outfitx.m_Pants) {
      String string0 =
          outfitx.m_AllowPantsHue
              ? DefaultClothing.instance.pickPantsHue()
              : (outfitx.m_AllowPantsTint
                     ? DefaultClothing.instance.pickPantsTint()
                     : DefaultClothing.instance.pickPantsTexture());
      this.addClothingItem(itemVisuals, itemVisualLocations, string0, nullptr);
    }

    if (outfitx.m_Top && outfitx.RandomData.m_hasTop) {
      std::string string1;
      if (outfitx.RandomData.m_hasTShirt) {
        if (outfitx.RandomData.m_hasTShirtDecal &&
            outfitx.GetMask().isTorsoVisible() && outfitx.m_AllowTShirtDecal) {
          string1 = outfitx.m_AllowTopTint
                        ? DefaultClothing.instance.pickTShirtDecalTint()
                        : DefaultClothing.instance.pickTShirtDecalTexture();
        } else {
          string1 = outfitx.m_AllowTopTint
                        ? DefaultClothing.instance.pickTShirtTint()
                        : DefaultClothing.instance.pickTShirtTexture();
        }
      } else {
        string1 = outfitx.m_AllowTopTint
                      ? DefaultClothing.instance.pickVestTint()
                      : DefaultClothing.instance.pickVestTexture();
      }

      this.addClothingItem(itemVisuals, itemVisualLocations, string1, nullptr);
    }

    for (int int0 = 0; int0 < outfitx.m_items.size(); int0++) {
      ClothingItemReference clothingItemReference = outfitx.m_items.get(int0);
      ClothingItem clothingItem = clothingItemReference.getClothingItem();
      if (clothingItem != nullptr && clothingItem.isReady()) {
        this.addClothingItem(itemVisuals, itemVisualLocations,
                             clothingItem.m_Name, clothingItemReference);
      }
    }

    outfitx.m_Pants = false;
    outfitx.m_Top = false;
    outfitx.RandomData.m_topTexture = nullptr;
    outfitx.RandomData.m_pantsTexture = nullptr;
  }

  ItemVisuals getBodyVisuals() { return this.bodyVisuals; }

  ItemVisual addBodyVisual(const std::string &clothingItemName) {
    return this.addBodyVisualFromClothingItemName(clothingItemName);
  }

  ItemVisual addBodyVisualFromItemType(const std::string &itemType) {
    Item item = ScriptManager.instance.getItem(itemType);
    return item != nullptr &&
                   !StringUtils.isNullOrWhitespace(item.getClothingItem())
               ? this.addBodyVisualFromClothingItemName(item.getClothingItem())
               : nullptr;
  }

  ItemVisual
  addBodyVisualFromClothingItemName(const std::string &clothingItemName) {
    if (StringUtils.isNullOrWhitespace(clothingItemName)) {
      return null;
    } else {
      Item item =
          ScriptManager.instance.getItemForClothingItem(clothingItemName);
      if (item == nullptr) {
        return null;
      } else {
        ClothingItem clothingItem = item.getClothingItemAsset();
        if (clothingItem == nullptr) {
          return null;
        } else {
          for (int int0 = 0; int0 < this.bodyVisuals.size(); int0++) {
            if (this.bodyVisuals.get(int0).getClothingItemName() ==
                clothingItemName)) {
    return null;
                        }
          }

          ClothingItemReference clothingItemReference =
              new ClothingItemReference();
          clothingItemReference.itemGUID = clothingItem.m_GUID;
          clothingItemReference.randomize();
          ItemVisual itemVisual = new ItemVisual();
          itemVisual.setItemType(item.getFullName());
          itemVisual.synchWithOutfit(clothingItemReference);
          this.bodyVisuals.add(itemVisual);
          return itemVisual;
        }
      }
    }
  }

  ItemVisual removeBodyVisualFromItemType(const std::string &itemType) {
    for (int int0 = 0; int0 < this.bodyVisuals.size(); int0++) {
      ItemVisual itemVisual = this.bodyVisuals.get(int0);
      if (itemVisual.getItemType() == itemType)) {
          this.bodyVisuals.remove(int0);
          return itemVisual;
        }
    }

    return null;
  }

  bool hasBodyVisualFromItemType(const std::string &itemType) {
    for (int int0 = 0; int0 < this.bodyVisuals.size(); int0++) {
      ItemVisual itemVisual = this.bodyVisuals.get(int0);
      if (itemVisual.getItemType() == itemType)) {
    return true;
            }
    }

    return false;
  }

  void getItemVisualLocations(ItemVisuals itemVisuals,
                              ArrayList<String> arrayList) {
    arrayList.clear();

    for (int int0 = 0; int0 < itemVisuals.size(); int0++) {
      ItemVisual itemVisual = itemVisuals.get(int0);
      Item item = itemVisual.getScriptItem();
      if (item == nullptr) {
        arrayList.add(nullptr);
      } else {
        std::string string = item.getBodyLocation();
        if (StringUtils.isNullOrWhitespace(string)) {
          string = item.CanBeEquipped;
        }

        arrayList.add(string);
      }
    }
  }

  ItemVisual addClothingItem(ItemVisuals itemVisuals, Item scriptItem) {
    if (scriptItem == nullptr) {
      return null;
    } else {
      ClothingItem clothingItem = scriptItem.getClothingItemAsset();
      if (clothingItem == nullptr) {
        return null;
      } else if (!clothingItem.isReady()) {
        return null;
      } else {
        this.getItemVisualLocations(itemVisuals, itemVisualLocations);
        return this.addClothingItem(itemVisuals, itemVisualLocations,
                                    clothingItem.m_Name, nullptr);
      }
    }
  }

  ItemVisual addClothingItem(ItemVisuals itemVisuals,
                             ArrayList<String> arrayList,
                             const std::string &string0,
                             ClothingItemReference clothingItemReference) {
    assert itemVisuals.size() == arrayList.size();

    if (clothingItemReference != nullptr &&
        !clothingItemReference.RandomData.m_Active) {
      return null;
    } else if (StringUtils.isNullOrWhitespace(string0)) {
      return null;
    } else {
      Item item = ScriptManager.instance.getItemForClothingItem(string0);
      if (item == nullptr) {
        if (DebugLog.isEnabled(DebugType.Clothing)) {
          DebugLog.Clothing.warn("Could not find item type for %s", string0);
        }

        return null;
      } else {
        ClothingItem clothingItem = item.getClothingItemAsset();
        if (clothingItem == nullptr) {
          return null;
        } else if (!clothingItem.isReady()) {
          return null;
        } else {
          std::string string1 = item.getBodyLocation();
          if (StringUtils.isNullOrWhitespace(string1)) {
            string1 = item.CanBeEquipped;
          }

          if (StringUtils.isNullOrWhitespace(string1)) {
            return null;
          } else {
            if (clothingItemReference == nullptr) {
              clothingItemReference = std::make_unique<ClothingItemReference>();
              clothingItemReference.itemGUID = clothingItem.m_GUID;
              clothingItemReference.randomize();
            }

            if (!clothingItemReference.RandomData.m_Active) {
              return null;
            } else {
              BodyLocationGroup bodyLocationGroup =
                  BodyLocations.getGroup("Human");
              BodyLocation bodyLocation =
                  bodyLocationGroup.getLocation(string1);
              if (bodyLocation == nullptr) {
                DebugLog.General.error("The game can't found location '" +
                                       string1 + "' for the item '" +
                                       item.name + "'");
                return null;
              } else {
                if (!bodyLocation.isMultiItem()) {
                  int int0 = arrayList.indexOf(string1);
                  if (int0 != -1) {
                    itemVisuals.remove(int0);
                    arrayList.remove(int0);
                  }
                }

                for (int int1 = 0; int1 < itemVisuals.size(); int1++) {
                  if (bodyLocationGroup.isExclusive(
                          string1, (String)arrayList.get(int1))) {
                    itemVisuals.remove(int1);
                    arrayList.remove(int1);
                    int1--;
                  }
                }

                assert itemVisuals.size() == arrayList.size();

                int int2 = bodyLocationGroup.indexOf(string1);
                int int3 = itemVisuals.size();

                for (int int4 = 0; int4 < itemVisuals.size(); int4++) {
                  if (bodyLocationGroup.indexOf((String)arrayList.get(int4)) >
                      int2) {
                    int3 = int4;
                    break;
                  }
                }

                ItemVisual itemVisual = new ItemVisual();
                itemVisual.setItemType(item.getFullName());
                itemVisual.synchWithOutfit(clothingItemReference);
                itemVisuals.add(int3, itemVisual);
                arrayList.add(int3, string1);
                return itemVisual;
              }
            }
          }
        }
      }
    }
  }

  Outfit getOutfit() { return this.outfit; }

  void setOutfit(Outfit _outfit) { this.outfit = _outfit; }

  std::string getNonAttachedHair() { return this.nonAttachedHair; }

  void setNonAttachedHair(const std::string &_nonAttachedHair) {
    if (StringUtils.isNullOrWhitespace(_nonAttachedHair)) {
      _nonAttachedHair = nullptr;
    }

    this.nonAttachedHair = _nonAttachedHair;
  }

  void setForceModel(Model model) { this.forceModel = model; }

  void setForceModelScript(const std::string &modelScript) {
    this.forceModelScript = modelScript;
  }

  static StringBuilder toString(ImmutableColor immutableColor,
                                StringBuilder stringBuilder) {
    stringBuilder.append(immutableColor.getRedByte() & 255);
    stringBuilder.append(",");
    stringBuilder.append(immutableColor.getGreenByte() & 255);
    stringBuilder.append(",");
    stringBuilder.append(immutableColor.getBlueByte() & 255);
    return stringBuilder;
  }

  static ImmutableColor colorFromString(const std::string &string) {
    String[] strings = string.split(",");
    if (strings.length == 3) {
      try {
        int int0 = Integer.parseInt(strings[0]);
        int int1 = Integer.parseInt(strings[1]);
        int int2 = Integer.parseInt(strings[2]);
        return new ImmutableColor(int0 / 255.0F, int1 / 255.0F, int2 / 255.0F);
      } catch (NumberFormatException numberFormatException) {
      }
    }

    return null;
  }

  std::string getLastStandString() {
    StringBuilder stringBuilder = new StringBuilder();
    stringBuilder.append("version=");
    stringBuilder.append(1);
    stringBuilder.append(";");
    if (this.getHairColor() != nullptr) {
      stringBuilder.append("hairColor=");
      toString(this.getHairColor(), stringBuilder);
      stringBuilder.append(";");
    }

    if (this.getBeardColor() != nullptr) {
      stringBuilder.append("beardColor=");
      toString(this.getBeardColor(), stringBuilder);
      stringBuilder.append(";");
    }

    if (this.getNaturalHairColor() != nullptr) {
      stringBuilder.append("naturalHairColor=");
      toString(this.getNaturalHairColor(), stringBuilder);
      stringBuilder.append(";");
    }

    if (this.getNaturalBeardColor() != nullptr) {
      stringBuilder.append("naturalBeardColor=");
      toString(this.getNaturalBeardColor(), stringBuilder);
      stringBuilder.append(";");
    }

    if (this.getSkinColor() != nullptr) {
      stringBuilder.append("skinColor=");
      toString(this.getSkinColor(), stringBuilder);
      stringBuilder.append(";");
    }

    stringBuilder.append("bodyHair=");
    stringBuilder.append(this.getBodyHairIndex());
    stringBuilder.append(";");
    stringBuilder.append("skinTexture=");
    stringBuilder.append(this.getSkinTextureIndex());
    stringBuilder.append(";");
    if (this.getSkinTexture() != nullptr) {
      stringBuilder.append("skinTextureName=");
      stringBuilder.append(this.getSkinTexture());
      stringBuilder.append(";");
    }

    if (this.getHairModel() != nullptr) {
      stringBuilder.append("hairModel=");
      stringBuilder.append(this.getHairModel());
      stringBuilder.append(";");
    }

    if (this.getBeardModel() != nullptr) {
      stringBuilder.append("beardModel=");
      stringBuilder.append(this.getBeardModel());
      stringBuilder.append(";");
    }

    return stringBuilder.toString();
  }

  bool loadLastStandString(const std::string &saveStr) {
    saveStr = saveStr.trim();
    if (!StringUtils.isNullOrWhitespace(saveStr) &&
        saveStr.startsWith("version=")) {
      int int0 = -1;
      String[] strings = saveStr.split(";");

      for (int int1 = 0; int1 < strings.length; int1++) {
        int int2 = strings[int1].indexOf(61);
        if (int2 != -1) {
          std::string string0 = strings[int1].substring(0, int2).trim();
          std::string string1 = strings[int1].substring(int2 + 1).trim();
          switch (string0) {
          case "version":
            int0 = Integer.parseInt(string1);
            if (int0 < 1 || int0 > 1) {
              return false;
            }
            break;
          case "beardColor":
            ImmutableColor immutableColor4 = colorFromString(string1);
            if (immutableColor4 != nullptr) {
              this.setBeardColor(immutableColor4);
            }
            break;
          case "naturalBeardColor":
            ImmutableColor immutableColor3 = colorFromString(string1);
            if (immutableColor3 != nullptr) {
              this.setNaturalBeardColor(immutableColor3);
            }
            break;
          case "beardModel":
            this.setBeardModel(string1);
            break;
          case "bodyHair":
            try {
              this.setBodyHairIndex(Integer.parseInt(string1));
            } catch (NumberFormatException numberFormatException1) {
            }
            break;
          case "hairColor":
            ImmutableColor immutableColor2 = colorFromString(string1);
            if (immutableColor2 != nullptr) {
              this.setHairColor(immutableColor2);
            }
            break;
          case "naturalHairColor":
            ImmutableColor immutableColor1 = colorFromString(string1);
            if (immutableColor1 != nullptr) {
              this.setNaturalHairColor(immutableColor1);
            }
            break;
          case "hairModel":
            this.setHairModel(string1);
            break;
          case "skinColor":
            ImmutableColor immutableColor0 = colorFromString(string1);
            if (immutableColor0 != nullptr) {
              this.setSkinColor(immutableColor0);
            }
            break;
          case "skinTexture":
            try {
              this.setSkinTextureIndex(Integer.parseInt(string1));
            } catch (NumberFormatException numberFormatException0) {
            }
            break;
          case "skinTextureName":
            this.setSkinTextureName(string1);
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
