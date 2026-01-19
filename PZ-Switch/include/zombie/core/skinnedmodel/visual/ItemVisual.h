#pragma once
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
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace visual {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ItemVisual {
public:
 std::string m_fullType;
 std::string m_clothingItemName;
 std::string m_alternateModelName;
 static const float NULL_HUE = Float.POSITIVE_INFINITY;
 float m_Hue = Float.POSITIVE_INFINITY;
 ImmutableColor m_Tint = nullptr;
 int m_BaseTexture = -1;
 int m_TextureChoice = -1;
 std::string m_Decal = nullptr;
private
 byte[] blood;
private
 byte[] dirt;
private
 byte[] holes;
private
 byte[] basicPatches;
private
 byte[] denimPatches;
private
 byte[] leatherPatches;
 InventoryItem inventoryItem = nullptr;
 static const int LASTSTAND_VERSION1 = 1;
 static const int LASTSTAND_VERSION = 1;

public
 ItemVisual() {}

public
 ItemVisual(ItemVisual other) { this->copyFrom(other); }

 void setItemType(std::string_view fullType) {
 Objects.requireNonNull(fullType);

 assert fullType.contains(".");

 this->m_fullType = fullType;
 }

 std::string getItemType() { return this->m_fullType; }

 void setAlternateModelName(std::string_view name) {
 this->m_alternateModelName = name;
 }

 std::string getAlternateModelName() { return this->m_alternateModelName; }

 std::string toString() {
 return this->getClass().getSimpleName() + "{ m_clothingItemName:\"" +
 this->m_clothingItemName + "\"}";
 }

 std::string getClothingItemName() { return this->m_clothingItemName; }

 void setClothingItemName(std::string_view name) {
 this->m_clothingItemName = name;
 }

 Item getScriptItem() {
 return StringUtils.isNullOrWhitespace(this->m_fullType)
 ? nullptr
 : ScriptManager.instance.getItem(this->m_fullType);
 }

 ClothingItem getClothingItem() {
 Item item = this->getScriptItem();
 if (item.empty()) {
 return nullptr;
 } else {
 if (!StringUtils.isNullOrWhitespace(this->m_alternateModelName) {
 if ("LeftHand".equalsIgnoreCase(this->m_alternateModelName) {
 return item.replaceSecondHand.clothingItem;
 }

 if ("RightHand".equalsIgnoreCase(this->m_alternateModelName) {
 return item.replacePrimaryHand.clothingItem;
 }
 }

 return item.getClothingItemAsset();
 }
 }

 void getClothingItemCombinedMask(CharacterMask in_out_mask) {
 ClothingItem.tryGetCombinedMask(this->getClothingItem(), in_out_mask);
 }

 void setHue(float hue) {
 hue = Math.max(hue, -1.0F);
 hue = Math.min(hue, 1.0F);
 this->m_Hue = hue;
 }

 float getHue(ClothingItem clothingItem) {
 if (clothingItem.m_AllowRandomHue) {
 if (this->m_Hue == Float.POSITIVE_INFINITY) {
 this->m_Hue = OutfitRNG.Next(200) / 100.0F - 1.0F;
 }

 return this->m_Hue;
 } else {
 return this->m_Hue = 0.0F;
 }
 }

 void setTint(ImmutableColor tint) { this->m_Tint = tint; }

 ImmutableColor getTint(ClothingItem clothingItem) {
 if (clothingItem.m_AllowRandomTint) {
 if (this->m_Tint.empty()) {
 this->m_Tint = OutfitRNG.randomImmutableColor();
 }

 return this->m_Tint;
 } else {
 return this->m_Tint = ImmutableColor.white;
 }
 }

 ImmutableColor getTint() { return this->m_Tint; }

 std::string getBaseTexture(ClothingItem clothingItem) {
 if (clothingItem.m_BaseTextures.empty()) {
 this->m_BaseTexture = -1;
 return nullptr;
 } else {
 if (this->m_BaseTexture < 0 ||
 this->m_BaseTexture >= clothingItem.m_BaseTextures.size()) {
 this->m_BaseTexture = OutfitRNG.Next(clothingItem.m_BaseTextures.size());
 }

 return clothingItem.m_BaseTextures.get(this->m_BaseTexture);
 }
 }

 std::string getTextureChoice(ClothingItem clothingItem) {
 if (clothingItem.textureChoices.empty()) {
 this->m_TextureChoice = -1;
 return nullptr;
 } else {
 if (this->m_TextureChoice < 0 ||
 this->m_TextureChoice >= clothingItem.textureChoices.size()) {
 this->m_TextureChoice =
 OutfitRNG.Next(clothingItem.textureChoices.size());
 }

 return clothingItem.textureChoices.get(this->m_TextureChoice);
 }
 }

 void setDecal(std::string_view decalName) { this->m_Decal = decalName; }

 std::string getDecal(ClothingItem clothingItem) {
 if (StringUtils.isNullOrWhitespace(clothingItem.m_DecalGroup) {
 return this->m_Decal = nullptr;
 } else {
 if (this->m_Decal.empty()) {
 this->m_Decal =
 ClothingDecals.instance.getRandomDecal(clothingItem.m_DecalGroup);
 }

 return this->m_Decal;
 }
 }

 void pickUninitializedValues(ClothingItem clothingItem) {
 if (clothingItem != nullptr && clothingItem.isReady()) {
 this->getHue(clothingItem);
 this->getTint(clothingItem);
 this->getBaseTexture(clothingItem);
 this->getTextureChoice(clothingItem);
 this->getDecal(clothingItem);
 }
 }

 void synchWithOutfit(ClothingItemReference itemRef) {
 ClothingItem clothingItem = itemRef.getClothingItem();
 this->m_clothingItemName = clothingItem.m_Name;
 this->m_Hue = itemRef.RandomData.m_Hue;
 this->m_Tint = itemRef.RandomData.m_Tint;
 this->m_BaseTexture =
 clothingItem.m_BaseTextures.indexOf(itemRef.RandomData.m_BaseTexture);
 this->m_TextureChoice =
 clothingItem.textureChoices.indexOf(itemRef.RandomData.m_TextureChoice);
 this->m_Decal = itemRef.RandomData.m_Decal;
 }

 void clear() {
 this->m_fullType = nullptr;
 this->m_clothingItemName = nullptr;
 this->m_alternateModelName = nullptr;
 this->m_Hue = Float.POSITIVE_INFINITY;
 this->m_Tint = nullptr;
 this->m_BaseTexture = -1;
 this->m_TextureChoice = -1;
 this->m_Decal = nullptr;
 if (this->blood != nullptr) {
 Arrays.fill(this->blood, (byte)0);
 }

 if (this->dirt != nullptr) {
 Arrays.fill(this->dirt, (byte)0);
 }

 if (this->holes != nullptr) {
 Arrays.fill(this->holes, (byte)0);
 }

 if (this->basicPatches != nullptr) {
 Arrays.fill(this->basicPatches, (byte)0);
 }

 if (this->denimPatches != nullptr) {
 Arrays.fill(this->denimPatches, (byte)0);
 }

 if (this->leatherPatches != nullptr) {
 Arrays.fill(this->leatherPatches, (byte)0);
 }
 }

 void copyFrom(ItemVisual other) {
 if (other.empty()) {
 this->clear();
 } else {
 ClothingItem clothingItem = other.getClothingItem();
 if (clothingItem != nullptr) {
 other.pickUninitializedValues(clothingItem);
 }

 this->m_fullType = other.m_fullType;
 this->m_clothingItemName = other.m_clothingItemName;
 this->m_alternateModelName = other.m_alternateModelName;
 this->m_Hue = other.m_Hue;
 this->m_Tint = other.m_Tint;
 this->m_BaseTexture = other.m_BaseTexture;
 this->m_TextureChoice = other.m_TextureChoice;
 this->m_Decal = other.m_Decal;
 this->copyBlood(other);
 this->copyHoles(other);
 this->copyPatches(other);
 }
 }

 void save(ByteBuffer output) {
 uint8_t byte0 = 0;
 if (this->m_Tint != nullptr) {
 byte0 = (byte)(byte0 | 1);
 }

 if (this->m_BaseTexture != -1) {
 byte0 = (byte)(byte0 | 2);
 }

 if (this->m_TextureChoice != -1) {
 byte0 = (byte)(byte0 | 4);
 }

 if (this->m_Hue != Float.POSITIVE_INFINITY) {
 byte0 = (byte)(byte0 | 8);
 }

 if (!StringUtils.isNullOrWhitespace(this->m_Decal) {
 byte0 = (byte)(byte0 | 16);
 }

 output.put(byte0);
 GameWindow.WriteString(output, this->m_fullType);
 GameWindow.WriteString(output, this->m_alternateModelName);
 GameWindow.WriteString(output, this->m_clothingItemName);
 if (this->m_Tint != nullptr) {
 output.put(this->m_Tint.getRedByte());
 output.put(this->m_Tint.getGreenByte());
 output.put(this->m_Tint.getBlueByte());
 }

 if (this->m_BaseTexture != -1) {
 output.put((byte)this->m_BaseTexture);
 }

 if (this->m_TextureChoice != -1) {
 output.put((byte)this->m_TextureChoice);
 }

 if (this->m_Hue != Float.POSITIVE_INFINITY) {
 output.putFloat(this->m_Hue);
 }

 if (!StringUtils.isNullOrWhitespace(this->m_Decal) {
 GameWindow.WriteString(output, this->m_Decal);
 }

 if (this->blood != nullptr) {
 output.put((byte)this->blood.length);

 for (int int0 = 0; int0 < this->blood.length; int0++) {
 output.put(this->blood[int0]);
 }
 } else {
 output.put((byte)0);
 }

 if (this->dirt != nullptr) {
 output.put((byte)this->dirt.length);

 for (int int1 = 0; int1 < this->dirt.length; int1++) {
 output.put(this->dirt[int1]);
 }
 } else {
 output.put((byte)0);
 }

 if (this->holes != nullptr) {
 output.put((byte)this->holes.length);

 for (int int2 = 0; int2 < this->holes.length; int2++) {
 output.put(this->holes[int2]);
 }
 } else {
 output.put((byte)0);
 }

 if (this->basicPatches != nullptr) {
 output.put((byte)this->basicPatches.length);

 for (int int3 = 0; int3 < this->basicPatches.length; int3++) {
 output.put(this->basicPatches[int3]);
 }
 } else {
 output.put((byte)0);
 }

 if (this->denimPatches != nullptr) {
 output.put((byte)this->denimPatches.length);

 for (int int4 = 0; int4 < this->denimPatches.length; int4++) {
 output.put(this->denimPatches[int4]);
 }
 } else {
 output.put((byte)0);
 }

 if (this->leatherPatches != nullptr) {
 output.put((byte)this->leatherPatches.length);

 for (int int5 = 0; int5 < this->leatherPatches.length; int5++) {
 output.put(this->leatherPatches[int5]);
 }
 } else {
 output.put((byte)0);
 }
 }

 void load(ByteBuffer input, int WorldVersion) {
 int int0 = input.get() & 255;
 if (WorldVersion >= 164) {
 this->m_fullType = GameWindow.ReadString(input);
 this->m_alternateModelName = GameWindow.ReadString(input);
 }

 this->m_clothingItemName = GameWindow.ReadString(input);
 if (WorldVersion < 164) {
 this->m_fullType = ScriptManager.instance.getItemTypeForClothingItem(
 this->m_clothingItemName);
 }

 if ((int0 & 1) != 0) {
 int int1 = input.get() & 255;
 int int2 = input.get() & 255;
 int int3 = input.get() & 255;
 this->m_Tint = new ImmutableColor(int1, int2, int3);
 }

 if ((int0 & 2) != 0) {
 this->m_BaseTexture = input.get();
 }

 if ((int0 & 4) != 0) {
 this->m_TextureChoice = input.get();
 }

 if (WorldVersion >= 146) {
 if ((int0 & 8) != 0) {
 this->m_Hue = input.getFloat();
 }

 if ((int0 & 16) != 0) {
 this->m_Decal = GameWindow.ReadString(input);
 }
 }

 uint8_t byte0 = input.get();
 if (byte0 > 0 && this->blood.empty()) {
 this->blood = new byte[BloodBodyPartType.MAX.index()];
 }

 for (int int4 = 0; int4 < byte0; int4++) {
 uint8_t byte1 = input.get();
 if (int4 < this->blood.length) {
 this->blood[int4] = byte1;
 }
 }

 if (WorldVersion >= 163) {
 byte0 = input.get();
 if (byte0 > 0 && this->dirt.empty()) {
 this->dirt = new byte[BloodBodyPartType.MAX.index()];
 }

 for (int int5 = 0; int5 < byte0; int5++) {
 uint8_t byte2 = input.get();
 if (int5 < this->dirt.length) {
 this->dirt[int5] = byte2;
 }
 }
 }

 byte0 = input.get();
 if (byte0 > 0 && this->holes.empty()) {
 this->holes = new byte[BloodBodyPartType.MAX.index()];
 }

 for (int int6 = 0; int6 < byte0; int6++) {
 uint8_t byte3 = input.get();
 if (int6 < this->holes.length) {
 this->holes[int6] = byte3;
 }
 }

 if (WorldVersion >= 154) {
 byte0 = input.get();
 if (byte0 > 0 && this->basicPatches.empty()) {
 this->basicPatches = new byte[BloodBodyPartType.MAX.index()];
 }

 for (int int7 = 0; int7 < byte0; int7++) {
 uint8_t byte4 = input.get();
 if (int7 < this->basicPatches.length) {
 this->basicPatches[int7] = byte4;
 }
 }
 }

 if (WorldVersion >= 155) {
 byte0 = input.get();
 if (byte0 > 0 && this->denimPatches.empty()) {
 this->denimPatches = new byte[BloodBodyPartType.MAX.index()];
 }

 for (int int8 = 0; int8 < byte0; int8++) {
 uint8_t byte5 = input.get();
 if (int8 < this->denimPatches.length) {
 this->denimPatches[int8] = byte5;
 }
 }

 byte0 = input.get();
 if (byte0 > 0 && this->leatherPatches.empty()) {
 this->leatherPatches = new byte[BloodBodyPartType.MAX.index()];
 }

 for (int int9 = 0; int9 < byte0; int9++) {
 uint8_t byte6 = input.get();
 if (int9 < this->leatherPatches.length) {
 this->leatherPatches[int9] = byte6;
 }
 }
 }
 }

 void setDenimPatch(BloodBodyPartType bodyPartType) {
 if (this->denimPatches.empty()) {
 this->denimPatches = new byte[BloodBodyPartType.MAX.index()];
 }

 this->denimPatches[bodyPartType.index()] = -1;
 }

 float getDenimPatch(BloodBodyPartType bodyPartType) {
 return this->denimPatches.empty()
 ? 0.0F
 : (this->denimPatches[bodyPartType.index()] & 255) / 255.0F;
 }

 void setLeatherPatch(BloodBodyPartType bodyPartType) {
 if (this->leatherPatches.empty()) {
 this->leatherPatches = new byte[BloodBodyPartType.MAX.index()];
 }

 this->leatherPatches[bodyPartType.index()] = -1;
 }

 float getLeatherPatch(BloodBodyPartType bodyPartType) {
 return this->leatherPatches.empty()
 ? 0.0F
 : (this->leatherPatches[bodyPartType.index()] & 255) / 255.0F;
 }

 void setBasicPatch(BloodBodyPartType bodyPartType) {
 if (this->basicPatches.empty()) {
 this->basicPatches = new byte[BloodBodyPartType.MAX.index()];
 }

 this->basicPatches[bodyPartType.index()] = -1;
 }

 float getBasicPatch(BloodBodyPartType bodyPartType) {
 return this->basicPatches.empty()
 ? 0.0F
 : (this->basicPatches[bodyPartType.index()] & 255) / 255.0F;
 }

 int getBasicPatchesNumber() {
 if (this->basicPatches.empty()) {
 return 0;
 } else {
 int int0 = 0;

 for (int int1 = 0; int1 < this->basicPatches.length; int1++) {
 if (this->basicPatches[int1] != 0) {
 int0++;
 }
 }

 return int0;
 }
 }

 void setHole(BloodBodyPartType bodyPartType) {
 if (this->holes.empty()) {
 this->holes = new byte[BloodBodyPartType.MAX.index()];
 }

 this->holes[bodyPartType.index()] = -1;
 }

 float getHole(BloodBodyPartType bodyPartType) {
 return this->holes.empty()
 ? 0.0F
 : (this->holes[bodyPartType.index()] & 255) / 255.0F;
 }

 int getHolesNumber() {
 if (this->holes.empty()) {
 return 0;
 } else {
 int int0 = 0;

 for (int int1 = 0; int1 < this->holes.length; int1++) {
 if (this->holes[int1] != 0) {
 int0++;
 }
 }

 return int0;
 }
 }

 void setBlood(BloodBodyPartType bodyPartType, float amount) {
 if (this->blood.empty()) {
 this->blood = new byte[BloodBodyPartType.MAX.index()];
 }

 amount = Math.max(0.0F, Math.min(1.0F, amount);
 this->blood[bodyPartType.index()] = (byte)(amount * 255.0F);
 }

 float getBlood(BloodBodyPartType bodyPartType) {
 return this->blood.empty()
 ? 0.0F
 : (this->blood[bodyPartType.index()] & 255) / 255.0F;
 }

 float getDirt(BloodBodyPartType bodyPartType) {
 return this->dirt.empty()
 ? 0.0F
 : (this->dirt[bodyPartType.index()] & 255) / 255.0F;
 }

 void setDirt(BloodBodyPartType bodyPartType, float amount) {
 if (this->dirt.empty()) {
 this->dirt = new byte[BloodBodyPartType.MAX.index()];
 }

 amount = Math.max(0.0F, Math.min(1.0F, amount);
 this->dirt[bodyPartType.index()] = (byte)(amount * 255.0F);
 }

 void copyBlood(ItemVisual other) {
 if (other.blood != nullptr) {
 if (this->blood.empty()) {
 this->blood = new byte[BloodBodyPartType.MAX.index()];
 }

 System.arraycopy(other.blood, 0, this->blood, 0, this->blood.length);
 } else if (this->blood != nullptr) {
 Arrays.fill(this->blood, (byte)0);
 }
 }

 void copyDirt(ItemVisual other) {
 if (other.dirt != nullptr) {
 if (this->dirt.empty()) {
 this->dirt = new byte[BloodBodyPartType.MAX.index()];
 }

 System.arraycopy(other.dirt, 0, this->dirt, 0, this->dirt.length);
 } else if (this->dirt != nullptr) {
 Arrays.fill(this->dirt, (byte)0);
 }
 }

 void copyHoles(ItemVisual other) {
 if (other.holes != nullptr) {
 if (this->holes.empty()) {
 this->holes = new byte[BloodBodyPartType.MAX.index()];
 }

 System.arraycopy(other.holes, 0, this->holes, 0, this->holes.length);
 } else if (this->holes != nullptr) {
 Arrays.fill(this->holes, (byte)0);
 }
 }

 void copyPatches(ItemVisual other) {
 if (other.basicPatches != nullptr) {
 if (this->basicPatches.empty()) {
 this->basicPatches = new byte[BloodBodyPartType.MAX.index()];
 }

 System.arraycopy(other.basicPatches, 0, this->basicPatches, 0,
 this->basicPatches.length);
 } else if (this->basicPatches != nullptr) {
 Arrays.fill(this->basicPatches, (byte)0);
 }

 if (other.denimPatches != nullptr) {
 if (this->denimPatches.empty()) {
 this->denimPatches = new byte[BloodBodyPartType.MAX.index()];
 }

 System.arraycopy(other.denimPatches, 0, this->denimPatches, 0,
 this->denimPatches.length);
 } else if (this->denimPatches != nullptr) {
 Arrays.fill(this->denimPatches, (byte)0);
 }

 if (other.leatherPatches != nullptr) {
 if (this->leatherPatches.empty()) {
 this->leatherPatches = new byte[BloodBodyPartType.MAX.index()];
 }

 System.arraycopy(other.leatherPatches, 0, this->leatherPatches, 0,
 this->leatherPatches.length);
 } else if (this->leatherPatches != nullptr) {
 Arrays.fill(this->leatherPatches, (byte)0);
 }
 }

 void removeHole(int bodyPartIndex) {
 if (this->holes != nullptr) {
 this->holes[bodyPartIndex] = 0;
 }
 }

 void removePatch(int bodyPartIndex) {
 if (this->basicPatches != nullptr) {
 this->basicPatches[bodyPartIndex] = 0;
 }

 if (this->denimPatches != nullptr) {
 this->denimPatches[bodyPartIndex] = 0;
 }

 if (this->leatherPatches != nullptr) {
 this->leatherPatches[bodyPartIndex] = 0;
 }
 }

 void removeBlood() {
 if (this->blood != nullptr) {
 Arrays.fill(this->blood, (byte)0);
 }
 }

 void removeDirt() {
 if (this->dirt != nullptr) {
 Arrays.fill(this->dirt, (byte)0);
 }
 }

 float getTotalBlood() {
 float float0 = 0.0F;
 if (this->blood != nullptr) {
 for (int int0 = 0; int0 < this->blood.length; int0++) {
 float0 += (this->blood[int0] & 255) / 255.0F;
 }
 }

 return float0;
 }

 InventoryItem getInventoryItem() { return this->inventoryItem; }

 void setInventoryItem(InventoryItem _inventoryItem) {
 this->inventoryItem = _inventoryItem;
 }

 void setBaseTexture(int baseTexture) { this->m_BaseTexture = baseTexture; }

 int getBaseTexture() { return this->m_BaseTexture; }

 void setTextureChoice(int TextureChoice) {
 this->m_TextureChoice = TextureChoice;
 }

 int getTextureChoice() { return this->m_TextureChoice; }

 static StringBuilder toString(ImmutableColor immutableColor,
 StringBuilder stringBuilder) {
 stringBuilder.append(immutableColor.getRedByte() & 255);
 stringBuilder.append(",");
 stringBuilder.append(immutableColor.getGreenByte() & 255);
 stringBuilder.append(",");
 stringBuilder.append(immutableColor.getBlueByte() & 255);
 return stringBuilder;
 }

 static ImmutableColor colorFromString(std::string_view string) {
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

 return nullptr;
 }

 std::string getLastStandString() {
 Item item = this->getScriptItem();
 if (item.empty()) {
 return nullptr;
 } else {
 ClothingItem clothingItem = this->getClothingItem();
 if (clothingItem.empty()) {
 return nullptr;
 } else {
 StringBuilder stringBuilder = new StringBuilder();
 stringBuilder.append("version=");
 stringBuilder.append(1);
 stringBuilder.append(";");
 stringBuilder.append("type=");
 stringBuilder.append(this->inventoryItem.getFullType());
 stringBuilder.append(";");
 ImmutableColor immutableColor = this->getTint(clothingItem);
 stringBuilder.append("tint=");
 toString(immutableColor, stringBuilder);
 stringBuilder.append(";");
 int int0 = this->getBaseTexture();
 if (int0 != -1) {
 stringBuilder.append("baseTexture=");
 stringBuilder.append(int0);
 stringBuilder.append(";");
 }

 int int1 = this->getTextureChoice();
 if (int1 != -1) {
 stringBuilder.append("textureChoice=");
 stringBuilder.append(int1);
 stringBuilder.append(";");
 }

 float float0 = this->getHue(clothingItem);
 if (float0 != 0.0F) {
 stringBuilder.append("hue=");
 stringBuilder.append(float0);
 stringBuilder.append(";");
 }

 std::string string = this->getDecal(clothingItem);
 if (!StringUtils.isNullOrWhitespace(string) {
 stringBuilder.append("decal=");
 stringBuilder.append(string);
 stringBuilder.append(";");
 }

 return stringBuilder.toString();
 }
 }
 }

 static InventoryItem createLastStandItem(std::string_view saveStr) {
 saveStr = saveStr.trim();
 if (!StringUtils.isNullOrWhitespace(saveStr) &&
 saveStr.startsWith("version=")) {
 InventoryItem item = nullptr;
 ItemVisual itemVisual = nullptr;
 int int0 = -1;
 String[] strings = saveStr.split(";");
 if (strings.length >= 2 && strings[1].trim().startsWith("type=")) {
 for (int int1 = 0; int1 < strings.length; int1++) {
 int int2 = strings[int1].indexOf(61);
 if (int2 != -1) {
 std::string string0 = strings[int1].substring(0, int2).trim();
 std::string string1 = strings[int1].substring(int2 + 1).trim();
 switch (string0) {
 case "version":
 int0 = Integer.parseInt(string1);
 if (int0 < 1 || int0 > 1) {
 return nullptr;
 }
 break;
 case "baseTexture":
 try {
 itemVisual.setBaseTexture(Integer.parseInt(string1);
 } catch (NumberFormatException numberFormatException2) {
 }
 break;
 case "decal":
 if (!StringUtils.isNullOrWhitespace(string1) {
 itemVisual.setDecal(string1);
 }
 break;
 case "hue":
 try {
 itemVisual.setHue(Float.parseFloat(string1);
 } catch (NumberFormatException numberFormatException1) {
 }
 break;
 case "textureChoice":
 try {
 itemVisual.setTextureChoice(Integer.parseInt(string1);
 } catch (NumberFormatException numberFormatException0) {
 }
 break;
 case "tint":
 ImmutableColor immutableColor = colorFromString(string1);
 if (immutableColor != nullptr) {
 itemVisual.setTint(immutableColor);
 }
 break;
 case "type":
 item = InventoryItemFactory.CreateItem(string1);
 if (item.empty()) {
 return nullptr;
 }

 itemVisual = item.getVisual();
 if (itemVisual.empty()) {
 return nullptr;
 }
 }
 }
 }

 return item;
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
