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
#include "zombie/core/ImmutableColor.h"
#include "zombie/core/skinnedmodel/model/CharacterMask.h"
#include "zombie/core/skinnedmodel/population/ClothingDecals.h"
#include "zombie/core/skinnedmodel/population/ClothingItem.h"
#include "zombie/core/skinnedmodel/population/ClothingItemReference.h"
#include "zombie/core/skinnedmodel/population/OutfitRNG.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace visual {


class ItemVisual {
public:
    std::string m_fullType;
    std::string m_clothingItemName;
    std::string m_alternateModelName;
    static const float NULL_HUE = float.POSITIVE_INFINITY;
    float m_Hue = float.POSITIVE_INFINITY;
    ImmutableColor m_Tint = nullptr;
    int m_BaseTexture = -1;
    int m_TextureChoice = -1;
    std::string m_Decal = nullptr;
   private byte[] blood;
   private byte[] dirt;
   private byte[] holes;
   private byte[] basicPatches;
   private byte[] denimPatches;
   private byte[] leatherPatches;
    InventoryItem inventoryItem = nullptr;
    static const int LASTSTAND_VERSION1 = 1;
    static const int LASTSTAND_VERSION = 1;

    public ItemVisual() {
   }

    public ItemVisual(ItemVisual var1) {
      this.copyFrom(var1);
   }

    void setItemType(const std::string& var1) {
      Objects.requireNonNull(var1);

      assert var1.contains(".");

      this.m_fullType = var1;
   }

    std::string getItemType() {
      return this.m_fullType;
   }

    void setAlternateModelName(const std::string& var1) {
      this.m_alternateModelName = var1;
   }

    std::string getAlternateModelName() {
      return this.m_alternateModelName;
   }

    std::string toString() {
      return this.getClass().getSimpleName() + "{ m_clothingItemName:\"" + this.m_clothingItemName + "\"}";
   }

    std::string getClothingItemName() {
      return this.m_clothingItemName;
   }

    void setClothingItemName(const std::string& var1) {
      this.m_clothingItemName = var1;
   }

    Item getScriptItem() {
      return StringUtils.isNullOrWhitespace(this.m_fullType) ? nullptr : ScriptManager.instance.getItem(this.m_fullType);
   }

    ClothingItem getClothingItem() {
    Item var1 = this.getScriptItem();
      if (var1 == nullptr) {
    return nullptr;
      } else {
         if (!StringUtils.isNullOrWhitespace(this.m_alternateModelName)) {
            if ("LeftHand".equalsIgnoreCase(this.m_alternateModelName)) {
               return var1.replaceSecondHand.clothingItem;
            }

            if ("RightHand".equalsIgnoreCase(this.m_alternateModelName)) {
               return var1.replacePrimaryHand.clothingItem;
            }
         }

         return var1.getClothingItemAsset();
      }
   }

    void getClothingItemCombinedMask(CharacterMask var1) {
      ClothingItem.tryGetCombinedMask(this.getClothingItem(), var1);
   }

    void setHue(float var1) {
      var1 = Math.max(var1, -1.0F);
      var1 = Math.min(var1, 1.0F);
      this.m_Hue = var1;
   }

    float getHue(ClothingItem var1) {
      if (var1.m_AllowRandomHue) {
         if (this.m_Hue == float.POSITIVE_INFINITY) {
            this.m_Hue = OutfitRNG.Next(200) / 100.0F - 1.0F;
         }

         return this.m_Hue;
      } else {
         return this.m_Hue = 0.0F;
      }
   }

    void setTint(ImmutableColor var1) {
      this.m_Tint = var1;
   }

    ImmutableColor getTint(ClothingItem var1) {
      if (var1.m_AllowRandomTint) {
         if (this.m_Tint == nullptr) {
            this.m_Tint = OutfitRNG.randomImmutableColor();
         }

         return this.m_Tint;
      } else {
         return this.m_Tint = ImmutableColor.white;
      }
   }

    ImmutableColor getTint() {
      return this.m_Tint;
   }

    std::string getBaseTexture(ClothingItem var1) {
      if (var1.m_BaseTextures.empty()) {
         this.m_BaseTexture = -1;
    return nullptr;
      } else {
         if (this.m_BaseTexture < 0 || this.m_BaseTexture >= var1.m_BaseTextures.size()) {
            this.m_BaseTexture = OutfitRNG.Next(var1.m_BaseTextures.size());
         }

         return (std::string)var1.m_BaseTextures.get(this.m_BaseTexture);
      }
   }

    std::string getTextureChoice(ClothingItem var1) {
      if (var1.textureChoices.empty()) {
         this.m_TextureChoice = -1;
    return nullptr;
      } else {
         if (this.m_TextureChoice < 0 || this.m_TextureChoice >= var1.textureChoices.size()) {
            this.m_TextureChoice = OutfitRNG.Next(var1.textureChoices.size());
         }

         return (std::string)var1.textureChoices.get(this.m_TextureChoice);
      }
   }

    void setDecal(const std::string& var1) {
      this.m_Decal = var1;
   }

    std::string getDecal(ClothingItem var1) {
      if (StringUtils.isNullOrWhitespace(var1.m_DecalGroup)) {
         return this.m_Decal = nullptr;
      } else {
         if (this.m_Decal == nullptr) {
            this.m_Decal = ClothingDecals.instance.getRandomDecal(var1.m_DecalGroup);
         }

         return this.m_Decal;
      }
   }

    void pickUninitializedValues(ClothingItem var1) {
      if (var1 != nullptr && var1.isReady()) {
         this.getHue(var1);
         this.getTint(var1);
         this.getBaseTexture(var1);
         this.getTextureChoice(var1);
         this.getDecal(var1);
      }
   }

    void synchWithOutfit(ClothingItemReference var1) {
    ClothingItem var2 = var1.getClothingItem();
      this.m_clothingItemName = var2.m_Name;
      this.m_Hue = var1.RandomData.m_Hue;
      this.m_Tint = var1.RandomData.m_Tint;
      this.m_BaseTexture = var2.m_BaseTextures.indexOf(var1.RandomData.m_BaseTexture);
      this.m_TextureChoice = var2.textureChoices.indexOf(var1.RandomData.m_TextureChoice);
      this.m_Decal = var1.RandomData.m_Decal;
   }

    void clear() {
      this.m_fullType = nullptr;
      this.m_clothingItemName = nullptr;
      this.m_alternateModelName = nullptr;
      this.m_Hue = float.POSITIVE_INFINITY;
      this.m_Tint = nullptr;
      this.m_BaseTexture = -1;
      this.m_TextureChoice = -1;
      this.m_Decal = nullptr;
      if (this.blood != nullptr) {
         Arrays.fill(this.blood, (byte)0);
      }

      if (this.dirt != nullptr) {
         Arrays.fill(this.dirt, (byte)0);
      }

      if (this.holes != nullptr) {
         Arrays.fill(this.holes, (byte)0);
      }

      if (this.basicPatches != nullptr) {
         Arrays.fill(this.basicPatches, (byte)0);
      }

      if (this.denimPatches != nullptr) {
         Arrays.fill(this.denimPatches, (byte)0);
      }

      if (this.leatherPatches != nullptr) {
         Arrays.fill(this.leatherPatches, (byte)0);
      }
   }

    void copyFrom(ItemVisual var1) {
      if (var1 == nullptr) {
         this.clear();
      } else {
    ClothingItem var2 = var1.getClothingItem();
         if (var2 != nullptr) {
            var1.pickUninitializedValues(var2);
         }

         this.m_fullType = var1.m_fullType;
         this.m_clothingItemName = var1.m_clothingItemName;
         this.m_alternateModelName = var1.m_alternateModelName;
         this.m_Hue = var1.m_Hue;
         this.m_Tint = var1.m_Tint;
         this.m_BaseTexture = var1.m_BaseTexture;
         this.m_TextureChoice = var1.m_TextureChoice;
         this.m_Decal = var1.m_Decal;
         this.copyBlood(var1);
         this.copyHoles(var1);
         this.copyPatches(var1);
      }
   }

    void save(ByteBuffer var1) {
    uint8_t var2 = 0;
      if (this.m_Tint != nullptr) {
         var2 = (byte)(var2 | 1);
      }

      if (this.m_BaseTexture != -1) {
         var2 = (byte)(var2 | 2);
      }

      if (this.m_TextureChoice != -1) {
         var2 = (byte)(var2 | 4);
      }

      if (this.m_Hue != float.POSITIVE_INFINITY) {
         var2 = (byte)(var2 | 8);
      }

      if (!StringUtils.isNullOrWhitespace(this.m_Decal)) {
         var2 = (byte)(var2 | 16);
      }

      var1.put(var2);
      GameWindow.WriteString(var1, this.m_fullType);
      GameWindow.WriteString(var1, this.m_alternateModelName);
      GameWindow.WriteString(var1, this.m_clothingItemName);
      if (this.m_Tint != nullptr) {
         var1.put(this.m_Tint.getRedByte());
         var1.put(this.m_Tint.getGreenByte());
         var1.put(this.m_Tint.getBlueByte());
      }

      if (this.m_BaseTexture != -1) {
         var1.put((byte)this.m_BaseTexture);
      }

      if (this.m_TextureChoice != -1) {
         var1.put((byte)this.m_TextureChoice);
      }

      if (this.m_Hue != float.POSITIVE_INFINITY) {
         var1.putFloat(this.m_Hue);
      }

      if (!StringUtils.isNullOrWhitespace(this.m_Decal)) {
         GameWindow.WriteString(var1, this.m_Decal);
      }

      if (this.blood != nullptr) {
         var1.put((byte)this.blood.length);

         for (int var3 = 0; var3 < this.blood.length; var3++) {
            var1.put(this.blood[var3]);
         }
      } else {
         var1.put((byte)0);
      }

      if (this.dirt != nullptr) {
         var1.put((byte)this.dirt.length);

         for (int var4 = 0; var4 < this.dirt.length; var4++) {
            var1.put(this.dirt[var4]);
         }
      } else {
         var1.put((byte)0);
      }

      if (this.holes != nullptr) {
         var1.put((byte)this.holes.length);

         for (int var5 = 0; var5 < this.holes.length; var5++) {
            var1.put(this.holes[var5]);
         }
      } else {
         var1.put((byte)0);
      }

      if (this.basicPatches != nullptr) {
         var1.put((byte)this.basicPatches.length);

         for (int var6 = 0; var6 < this.basicPatches.length; var6++) {
            var1.put(this.basicPatches[var6]);
         }
      } else {
         var1.put((byte)0);
      }

      if (this.denimPatches != nullptr) {
         var1.put((byte)this.denimPatches.length);

         for (int var7 = 0; var7 < this.denimPatches.length; var7++) {
            var1.put(this.denimPatches[var7]);
         }
      } else {
         var1.put((byte)0);
      }

      if (this.leatherPatches != nullptr) {
         var1.put((byte)this.leatherPatches.length);

         for (int var8 = 0; var8 < this.leatherPatches.length; var8++) {
            var1.put(this.leatherPatches[var8]);
         }
      } else {
         var1.put((byte)0);
      }
   }

    void load(ByteBuffer var1, int var2) {
    int var3 = var1.get() & 255;
      if (var2 >= 164) {
         this.m_fullType = GameWindow.ReadString(var1);
         this.m_alternateModelName = GameWindow.ReadString(var1);
      }

      this.m_clothingItemName = GameWindow.ReadString(var1);
      if (var2 < 164) {
         this.m_fullType = ScriptManager.instance.getItemTypeForClothingItem(this.m_clothingItemName);
      }

      if ((var3 & 1) != 0) {
    int var4 = var1.get() & 255;
    int var5 = var1.get() & 255;
    int var6 = var1.get() & 255;
         this.m_Tint = std::make_shared<ImmutableColor>(var4, var5, var6);
      }

      if ((var3 & 2) != 0) {
         this.m_BaseTexture = var1.get();
      }

      if ((var3 & 4) != 0) {
         this.m_TextureChoice = var1.get();
      }

      if (var2 >= 146) {
         if ((var3 & 8) != 0) {
            this.m_Hue = var1.getFloat();
         }

         if ((var3 & 16) != 0) {
            this.m_Decal = GameWindow.ReadString(var1);
         }
      }

    uint8_t var7 = var1.get();
      if (var7 > 0 && this.blood == nullptr) {
         this.blood = new byte[BloodBodyPartType.MAX.index()];
      }

      for (int var13 = 0; var13 < var7; var13++) {
    uint8_t var19 = var1.get();
         if (var13 < this.blood.length) {
            this.blood[var13] = var19;
         }
      }

      if (var2 >= 163) {
         var7 = var1.get();
         if (var7 > 0 && this.dirt == nullptr) {
            this.dirt = new byte[BloodBodyPartType.MAX.index()];
         }

         for (int var14 = 0; var14 < var7; var14++) {
    uint8_t var20 = var1.get();
            if (var14 < this.dirt.length) {
               this.dirt[var14] = var20;
            }
         }
      }

      var7 = var1.get();
      if (var7 > 0 && this.holes == nullptr) {
         this.holes = new byte[BloodBodyPartType.MAX.index()];
      }

      for (int var15 = 0; var15 < var7; var15++) {
    uint8_t var21 = var1.get();
         if (var15 < this.holes.length) {
            this.holes[var15] = var21;
         }
      }

      if (var2 >= 154) {
         var7 = var1.get();
         if (var7 > 0 && this.basicPatches == nullptr) {
            this.basicPatches = new byte[BloodBodyPartType.MAX.index()];
         }

         for (int var16 = 0; var16 < var7; var16++) {
    uint8_t var22 = var1.get();
            if (var16 < this.basicPatches.length) {
               this.basicPatches[var16] = var22;
            }
         }
      }

      if (var2 >= 155) {
         var7 = var1.get();
         if (var7 > 0 && this.denimPatches == nullptr) {
            this.denimPatches = new byte[BloodBodyPartType.MAX.index()];
         }

         for (int var17 = 0; var17 < var7; var17++) {
    uint8_t var23 = var1.get();
            if (var17 < this.denimPatches.length) {
               this.denimPatches[var17] = var23;
            }
         }

         var7 = var1.get();
         if (var7 > 0 && this.leatherPatches == nullptr) {
            this.leatherPatches = new byte[BloodBodyPartType.MAX.index()];
         }

         for (int var18 = 0; var18 < var7; var18++) {
    uint8_t var24 = var1.get();
            if (var18 < this.leatherPatches.length) {
               this.leatherPatches[var18] = var24;
            }
         }
      }
   }

    void setDenimPatch(BloodBodyPartType var1) {
      if (this.denimPatches == nullptr) {
         this.denimPatches = new byte[BloodBodyPartType.MAX.index()];
      }

      this.denimPatches[var1.index()] = -1;
   }

    float getDenimPatch(BloodBodyPartType var1) {
      return this.denimPatches == nullptr ? 0.0F : (this.denimPatches[var1.index()] & 255) / 255.0F;
   }

    void setLeatherPatch(BloodBodyPartType var1) {
      if (this.leatherPatches == nullptr) {
         this.leatherPatches = new byte[BloodBodyPartType.MAX.index()];
      }

      this.leatherPatches[var1.index()] = -1;
   }

    float getLeatherPatch(BloodBodyPartType var1) {
      return this.leatherPatches == nullptr ? 0.0F : (this.leatherPatches[var1.index()] & 255) / 255.0F;
   }

    void setBasicPatch(BloodBodyPartType var1) {
      if (this.basicPatches == nullptr) {
         this.basicPatches = new byte[BloodBodyPartType.MAX.index()];
      }

      this.basicPatches[var1.index()] = -1;
   }

    float getBasicPatch(BloodBodyPartType var1) {
      return this.basicPatches == nullptr ? 0.0F : (this.basicPatches[var1.index()] & 255) / 255.0F;
   }

    int getBasicPatchesNumber() {
      if (this.basicPatches == nullptr) {
    return 0;
      } else {
    int var1 = 0;

         for (int var2 = 0; var2 < this.basicPatches.length; var2++) {
            if (this.basicPatches[var2] != 0) {
               var1++;
            }
         }

    return var1;
      }
   }

    void setHole(BloodBodyPartType var1) {
      if (this.holes == nullptr) {
         this.holes = new byte[BloodBodyPartType.MAX.index()];
      }

      this.holes[var1.index()] = -1;
   }

    float getHole(BloodBodyPartType var1) {
      return this.holes == nullptr ? 0.0F : (this.holes[var1.index()] & 255) / 255.0F;
   }

    int getHolesNumber() {
      if (this.holes == nullptr) {
    return 0;
      } else {
    int var1 = 0;

         for (int var2 = 0; var2 < this.holes.length; var2++) {
            if (this.holes[var2] != 0) {
               var1++;
            }
         }

    return var1;
      }
   }

    void setBlood(BloodBodyPartType var1, float var2) {
      if (this.blood == nullptr) {
         this.blood = new byte[BloodBodyPartType.MAX.index()];
      }

      var2 = Math.max(0.0F, Math.min(1.0F, var2));
      this.blood[var1.index()] = (byte)(var2 * 255.0F);
   }

    float getBlood(BloodBodyPartType var1) {
      return this.blood == nullptr ? 0.0F : (this.blood[var1.index()] & 255) / 255.0F;
   }

    float getDirt(BloodBodyPartType var1) {
      return this.dirt == nullptr ? 0.0F : (this.dirt[var1.index()] & 255) / 255.0F;
   }

    void setDirt(BloodBodyPartType var1, float var2) {
      if (this.dirt == nullptr) {
         this.dirt = new byte[BloodBodyPartType.MAX.index()];
      }

      var2 = Math.max(0.0F, Math.min(1.0F, var2));
      this.dirt[var1.index()] = (byte)(var2 * 255.0F);
   }

    void copyBlood(ItemVisual var1) {
      if (var1.blood != nullptr) {
         if (this.blood == nullptr) {
            this.blood = new byte[BloodBodyPartType.MAX.index()];
         }

         System.arraycopy(var1.blood, 0, this.blood, 0, this.blood.length);
      } else if (this.blood != nullptr) {
         Arrays.fill(this.blood, (byte)0);
      }
   }

    void copyDirt(ItemVisual var1) {
      if (var1.dirt != nullptr) {
         if (this.dirt == nullptr) {
            this.dirt = new byte[BloodBodyPartType.MAX.index()];
         }

         System.arraycopy(var1.dirt, 0, this.dirt, 0, this.dirt.length);
      } else if (this.dirt != nullptr) {
         Arrays.fill(this.dirt, (byte)0);
      }
   }

    void copyHoles(ItemVisual var1) {
      if (var1.holes != nullptr) {
         if (this.holes == nullptr) {
            this.holes = new byte[BloodBodyPartType.MAX.index()];
         }

         System.arraycopy(var1.holes, 0, this.holes, 0, this.holes.length);
      } else if (this.holes != nullptr) {
         Arrays.fill(this.holes, (byte)0);
      }
   }

    void copyPatches(ItemVisual var1) {
      if (var1.basicPatches != nullptr) {
         if (this.basicPatches == nullptr) {
            this.basicPatches = new byte[BloodBodyPartType.MAX.index()];
         }

         System.arraycopy(var1.basicPatches, 0, this.basicPatches, 0, this.basicPatches.length);
      } else if (this.basicPatches != nullptr) {
         Arrays.fill(this.basicPatches, (byte)0);
      }

      if (var1.denimPatches != nullptr) {
         if (this.denimPatches == nullptr) {
            this.denimPatches = new byte[BloodBodyPartType.MAX.index()];
         }

         System.arraycopy(var1.denimPatches, 0, this.denimPatches, 0, this.denimPatches.length);
      } else if (this.denimPatches != nullptr) {
         Arrays.fill(this.denimPatches, (byte)0);
      }

      if (var1.leatherPatches != nullptr) {
         if (this.leatherPatches == nullptr) {
            this.leatherPatches = new byte[BloodBodyPartType.MAX.index()];
         }

         System.arraycopy(var1.leatherPatches, 0, this.leatherPatches, 0, this.leatherPatches.length);
      } else if (this.leatherPatches != nullptr) {
         Arrays.fill(this.leatherPatches, (byte)0);
      }
   }

    void removeHole(int var1) {
      if (this.holes != nullptr) {
         this.holes[var1] = 0;
      }
   }

    void removePatch(int var1) {
      if (this.basicPatches != nullptr) {
         this.basicPatches[var1] = 0;
      }

      if (this.denimPatches != nullptr) {
         this.denimPatches[var1] = 0;
      }

      if (this.leatherPatches != nullptr) {
         this.leatherPatches[var1] = 0;
      }
   }

    void removeBlood() {
      if (this.blood != nullptr) {
         Arrays.fill(this.blood, (byte)0);
      }
   }

    void removeDirt() {
      if (this.dirt != nullptr) {
         Arrays.fill(this.dirt, (byte)0);
      }
   }

    float getTotalBlood() {
    float var1 = 0.0F;
      if (this.blood != nullptr) {
         for (int var2 = 0; var2 < this.blood.length; var2++) {
            var1 += (this.blood[var2] & 255) / 255.0F;
         }
      }

    return var1;
   }

    InventoryItem getInventoryItem() {
      return this.inventoryItem;
   }

    void setInventoryItem(InventoryItem var1) {
      this.inventoryItem = var1;
   }

    void setBaseTexture(int var1) {
      this.m_BaseTexture = var1;
   }

    int getBaseTexture() {
      return this.m_BaseTexture;
   }

    void setTextureChoice(int var1) {
      this.m_TextureChoice = var1;
   }

    int getTextureChoice() {
      return this.m_TextureChoice;
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
    Item var1 = this.getScriptItem();
      if (var1 == nullptr) {
    return nullptr;
      } else {
    ClothingItem var2 = this.getClothingItem();
         if (var2 == nullptr) {
    return nullptr;
         } else {
    std::stringstream var3 = new std::stringstream();
            var3.append("version=");
            var3.append(1);
            var3.append(";");
            var3.append("type=");
            var3.append(this.inventoryItem.getFullType());
            var3.append(";");
    ImmutableColor var4 = this.getTint(var2);
            var3.append("tint=");
            toString(var4, var3);
            var3.append(";");
    int var5 = this.getBaseTexture();
            if (var5 != -1) {
               var3.append("baseTexture=");
               var3.append(var5);
               var3.append(";");
            }

    int var6 = this.getTextureChoice();
            if (var6 != -1) {
               var3.append("textureChoice=");
               var3.append(var6);
               var3.append(";");
            }

    float var7 = this.getHue(var2);
            if (var7 != 0.0F) {
               var3.append("hue=");
               var3.append(var7);
               var3.append(";");
            }

    std::string var8 = this.getDecal(var2);
            if (!StringUtils.isNullOrWhitespace(var8)) {
               var3.append("decal=");
               var3.append(var8);
               var3.append(";");
            }

            return var3;
         }
      }
   }

    static InventoryItem createLastStandItem(const std::string& var0) {
      var0 = var0.trim();
      if (!StringUtils.isNullOrWhitespace(var0) && var0.startsWith("version=")) {
    InventoryItem var1 = nullptr;
    ItemVisual var2 = nullptr;
    int var3 = -1;
         std::string[] var4 = var0.split(";");
         if (var4.length >= 2 && var4[1].trim().startsWith("type=")) {
            for (int var5 = 0; var5 < var4.length; var5++) {
    int var6 = var4[var5].indexOf(61);
               if (var6 != -1) {
    std::string var7 = var4[var5].substr(0, var6).trim();
    std::string var8 = var4[var5].substr(var6 + 1).trim();
                  switch (var7) {
                     case "version":
                        var3 = int.parseInt(var8);
                        if (var3 < 1 || var3 > 1) {
    return nullptr;
                        }
                        break;
                     case "baseTexture":
                        try {
                           var2.setBaseTexture(int.parseInt(var8));
                        } catch (NumberFormatException var14) {
                        }
                        break;
                     case "decal":
                        if (!StringUtils.isNullOrWhitespace(var8)) {
                           var2.setDecal(var8);
                        }
                        break;
                     case "hue":
                        try {
                           var2.setHue(float.parseFloat(var8));
                        } catch (NumberFormatException var13) {
                        }
                        break;
                     case "textureChoice":
                        try {
                           var2.setTextureChoice(int.parseInt(var8));
                        } catch (NumberFormatException var12) {
                        }
                        break;
                     case "tint":
    ImmutableColor var11 = colorFromString(var8);
                        if (var11 != nullptr) {
                           var2.setTint(var11);
                        }
                        break;
                     case "type":
                        var1 = InventoryItemFactory.CreateItem(var8);
                        if (var1 == nullptr) {
    return nullptr;
                        }

                        var2 = var1.getVisual();
                        if (var2 == nullptr) {
    return nullptr;
                        }
                  }
               }
            }

    return var1;
         } else {
    return nullptr;
         }
      } else {
    return nullptr;
      }
   }
}
} // namespace visual
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
