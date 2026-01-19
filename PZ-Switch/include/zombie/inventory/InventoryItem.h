#pragma once
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characterTextures/BloodClothingType.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/core/Color.h"
#include "zombie/core/Colors.h"
#include "zombie/core/Core.h"
#include "zombie/core/Translator.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/model/WorldItemAtlas.h"
#include "zombie/core/skinnedmodel/population/ClothingItem.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/core/stash/StashSystem.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/utils/Bits.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/inventory/types/Clothing.h"
#include "zombie/inventory/types/Drainable.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/InventoryContainer.h"
#include "zombie/inventory/types/Key.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/iso/objects/RainManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/radio/media/MediaData.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/scripting/objects/ItemReplacement.h"
#include "zombie/ui/ObjectTooltip.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIFont.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/util/io/BitHeader.h"
#include "zombie/util/io/BitHeaderRead.h"
#include "zombie/util/io/BitHeaderWrite.h"
#include "zombie/vehicles/VehiclePart.h"
#include "zombie/world/ItemInfo.h"
#include "zombie/world/WorldDictionary.h"
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
namespace inventory {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class InventoryItem {
public:
 IsoGameCharacter previousOwner = nullptr;
 Item ScriptItem = nullptr;
 ItemType cat = ItemType.None;
 ItemContainer container;
 int containerX = 0;
 int containerY = 0;
 std::string name;
 std::string replaceOnUse = nullptr;
 std::string replaceOnUseFullType = nullptr;
 int ConditionMax = 10;
 ItemContainer rightClickContainer = nullptr;
 Texture texture;
 Texture texturerotten;
 Texture textureCooked;
 Texture textureBurnt;
 std::string type;
 std::string fullType;
 int uses = 1;
 float Age = 0.0F;
 float LastAged = -1.0F;
 bool IsCookable = false;
 float CookingTime = 0.0F;
 float MinutesToCook = 60.0F;
 float MinutesToBurn = 120.0F;
 bool Cooked = false;
 bool Burnt = false;
 int OffAge = 1000000000;
 int OffAgeMax = 1000000000;
 float Weight = 1.0F;
 float ActualWeight = 1.0F;
 std::string WorldTexture;
 std::string Description;
 int Condition = 10;
 std::string OffString = Translator.getText("Tooltip_food_Rotten");
 std::string FreshString = Translator.getText("Tooltip_food_Fresh");
 std::string StaleString = Translator.getText("Tooltip_food_Stale");
 std::string CookedString = Translator.getText("Tooltip_food_Cooked");
 std::string UnCookedString = Translator.getText("Tooltip_food_Uncooked");
 std::string FrozenString = Translator.getText("Tooltip_food_Frozen");
 std::string BurntString = Translator.getText("Tooltip_food_Burnt");
 std::string brokenString = Translator.getText("Tooltip_broken");
 std::string module = "Base";
 float boredomChange = 0.0F;
 float unhappyChange = 0.0F;
 float stressChange = 0.0F;
protected
 ArrayList<IsoObject> Taken = std::make_unique<ArrayList<>>();
 IsoDirections placeDir = IsoDirections.Max;
 IsoDirections newPlaceDir = IsoDirections.Max;
 KahluaTable table = nullptr;
 std::string ReplaceOnUseOn = nullptr;
 Color col = Color.white;
 bool IsWaterSource = false;
 bool CanStoreWater = false;
 bool CanStack = false;
 bool activated = false;
 bool isTorchCone = false;
 int lightDistance = 0;
 int Count = 1;
 float fatigueChange = 0.0F;
 IsoWorldInventoryObject worldItem = nullptr;
 std::string customMenuOption = nullptr;
 std::string tooltip = nullptr;
 std::string displayCategory = nullptr;
 int haveBeenRepaired = 1;
 bool broken = false;
 std::string originalName = nullptr;
 int id = 0;
 bool RequiresEquippedBothHands;
 ByteBuffer byteData;
public
 ArrayList<String> extraItems = nullptr;
 bool customName = false;
 std::string breakSound = nullptr;
 bool alcoholic = false;
 float alcoholPower = 0.0F;
 float bandagePower = 0.0F;
 float ReduceInfectionPower = 0.0F;
 bool customWeight = false;
 bool customColor = false;
 int keyId = -1;
 bool taintedWater = false;
 bool remoteController = false;
 bool canBeRemote = false;
 int remoteControlID = -1;
 int remoteRange = 0;
 float colorRed = 1.0F;
 float colorGreen = 1.0F;
 float colorBlue = 1.0F;
 std::string countDownSound = nullptr;
 std::string explosionSound = nullptr;
 IsoGameCharacter equipParent = nullptr;
 std::string evolvedRecipeName = nullptr;
 float metalValue = 0.0F;
 float itemHeat = 1.0F;
 float meltingTime = 0.0F;
 std::string worker;
 bool isWet = false;
 float wetCooldown = -1.0F;
 std::string itemWhenDry = nullptr;
 bool favorite = false;
protected
 ArrayList<String> requireInHandOrInventory = nullptr;
 std::string map = nullptr;
 std::string stashMap = nullptr;
 bool keepOnDeplete = false;
 bool zombieInfected = false;
 bool rainFactorZero = false;
 float itemCapacity = -1.0F;
 int maxCapacity = -1;
 float brakeForce = 0.0F;
 int chanceToSpawnDamaged = 0;
 float conditionLowerNormal = 0.0F;
 float conditionLowerOffroad = 0.0F;
 float wheelFriction = 0.0F;
 float suspensionDamping = 0.0F;
 float suspensionCompression = 0.0F;
 float engineLoudness = 0.0F;
 ItemVisual visual = nullptr;
 std::string staticModel = nullptr;
private
 ArrayList<String> iconsForTexture = nullptr;
private
 ArrayList<BloodClothingType> bloodClothingType =
 std::make_unique<ArrayList<>>();
 int stashChance = 80;
 std::string ammoType = nullptr;
 int maxAmmo = 0;
 int currentAmmoCount = 0;
 std::string gunType = nullptr;
 std::string attachmentType = nullptr;
private
 ArrayList<String> attachmentsProvided = nullptr;
 int attachedSlot = -1;
 std::string attachedSlotType = nullptr;
 std::string attachmentReplacement = nullptr;
 std::string attachedToModel = nullptr;
 std::string m_alternateModelName = nullptr;
 short registry_id = -1;
 int worldZRotation = -1;
 float worldScale = 1.0F;
 short recordedMediaIndex = -1;
 uint8_t mediaType = -1;
 bool isInitialised = false;
public
 WorldItemAtlas.ItemTexture atlasTexture = nullptr;
 const int maxTextLength = 256;
 float jobDelta = 0.0F;
 std::string jobType = nullptr;
 static ByteBuffer tempBuffer = ByteBuffer.allocate(20000);
 std::string mainCategory = nullptr;
 bool canBeActivated;
 float lightStrength;
 std::string CloseKillMove = nullptr;
 bool beingFilled = false;

 int getSaveType() {
 throw RuntimeException(
 "InventoryItem.getSaveType() not implemented for " +
 this->getClass().getName());
 }

 IsoWorldInventoryObject getWorldItem() { return this->worldItem; }

 void setEquipParent(IsoGameCharacter parent) { this->equipParent = parent; }

 IsoGameCharacter getEquipParent() {
 return this->equipParent.empty() ||
 this->equipParent.getPrimaryHandItem() != this &&
 this->equipParent.getSecondaryHandItem() != this
 ? nullptr
 : this->equipParent;
 }

 std::string getBringToBearSound() {
 return this->getScriptItem().getBringToBearSound();
 }

 std::string getEquipSound() { return this->getScriptItem().getEquipSound(); }

 std::string getUnequipSound() {
 return this->getScriptItem().getUnequipSound();
 }

 void setWorldItem(IsoWorldInventoryObject w) { this->worldItem = w; }

 void setJobDelta(float delta) { this->jobDelta = delta; }

 float getJobDelta() { return this->jobDelta; }

 void setJobType(std::string_view _type) { this->jobType = _type; }

 std::string getJobType() { return this->jobType; }

 bool hasModData() { return this->table != nullptr && !this->table.empty(); }

 KahluaTable getModData() {
 if (this->table.empty()) {
 this->table = LuaManager.platform.newTable();
 }

 return this->table;
 }

 void storeInByteData(IsoObject o) {
 tempBuffer.clear();

 try {
 o.save(tempBuffer, false);
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }

 tempBuffer.flip();
 if (this->byteData.empty() ||
 this->byteData.capacity() < tempBuffer.limit() - 2 + 8) {
 this->byteData = ByteBuffer.allocate(tempBuffer.limit() - 2 + 8);
 }

 tempBuffer.get();
 tempBuffer.get();
 this->byteData.clear();
 this->byteData.put((byte)87);
 this->byteData.put((byte)86);
 this->byteData.put((byte)69);
 this->byteData.put((byte)82);
 this->byteData.putInt(195);
 this->byteData.put(tempBuffer);
 this->byteData.flip();
 }

 ByteBuffer getByteData() { return this->byteData; }

 bool isRequiresEquippedBothHands() { return this->RequiresEquippedBothHands; }

 float getA() { return this->col.a; }

 float getR() { return this->col.r; }

 float getG() { return this->col.g; }

 float getB() { return this->col.b; }

public
 InventoryItem(std::string_view _module, std::string_view _name,
 std::string_view _type, std::string_view tex) {
 this->col = Color.white;
 this->texture = Texture.trygetTexture(tex);
 if (this->texture.empty()) {
 this->texture =
 Texture.getSharedTexture("media/inventory/Question_On.png");
 }

 this->module = _module;
 this->name = _name;
 this->originalName = _name;
 this->type = _type;
 this->fullType = _module + "." + _type;
 this->WorldTexture = tex.replace("Item_", "media/inventory/world/WItem_");
 this->WorldTexture = this->WorldTexture + ".png";
 }

public
 InventoryItem(std::string_view _module, std::string_view _name,
 std::string_view _type, Item item) {
 this->col = Color.white;
 this->texture = item.NormalTexture;
 this->module = _module;
 this->name = _name;
 this->originalName = _name;
 this->type = _type;
 this->fullType = _module + "." + _type;
 this->WorldTexture = item.WorldTextureName;
 }

 std::string getType() { return this->type; }

 Texture getTex() { return this->texture; }

 std::string getCategory() {
 return this->mainCategory != nullptr ? this->mainCategory : "Item";
 }

 bool IsRotten() { return this->Age > this->OffAge; }

 float HowRotten() {
 if (this->OffAgeMax - this->OffAge == 0) {
 return this->Age > this->OffAge ? 1.0F : 0.0F;
 } else {
 return (this->Age - this->OffAge) / (this->OffAgeMax - this->OffAge);
 }
 }

 bool CanStack(InventoryItem item) { return false; }

 bool ModDataMatches(InventoryItem item) {
 KahluaTable table0 = item.getModData();
 KahluaTable table1 = item.getModData();
 if (table0.empty() && table1.empty()) {
 return true;
 } else if (table0.empty()) {
 return false;
 } else if (table1.empty()) {
 return false;
 } else if (table0.len() != table1.len()) {
 return false;
 } else {
 KahluaTableIterator kahluaTableIterator = table0.iterator();

 while (kahluaTableIterator.advance()) {
 void *object0 = table1.rawget(kahluaTableIterator.getKey());
 void *object1 = kahluaTableIterator.getValue();
 if (!object0 == object1) {
 return false;
 }
 }

 return true;
 }
 }

 void DoTooltip(ObjectTooltip tooltipUI) {
 tooltipUI.render();
 UIFont uIFont = tooltipUI.getFont();
 int int0 = tooltipUI.getLineSpacing();
 int int1 = 5;
 std::string string0 = "";
 if (this->Burnt) {
 string0 = string0 + this->BurntString + " ";
 } else if (this->OffAge < 1000000000 && this->Age < this->OffAge) {
 string0 = string0 + this->FreshString + " ";
 } else if (this->OffAgeMax < 1000000000 && this->Age >= this->OffAgeMax) {
 string0 = string0 + this->OffString + " ";
 } else if (this->OffAgeMax < 1000000000 && this->Age >= this->OffAge) {
 string0 = string0 + this->StaleString + " ";
 }

 if (this->isCooked() && !this->Burnt && !this->hasTag("HideCooked")) {
 string0 = string0 + this->CookedString + " ";
 } else if (this->IsCookable && !this->Burnt &&
 !(this instanceof DrainableComboItem) &&
 !this->hasTag("HideCooked")) {
 string0 = string0 + this->UnCookedString + " ";
 }

 if (this instanceof Food && ((Food)this).isFrozen()) {
 string0 = string0 + this->FrozenString + " ";
 }

 string0 = string0.trim();
 std::string string1;
 if (string0.empty()) {
 tooltipUI.DrawText(uIFont, string1 = this->getName(), 5.0, int1, 1.0, 1.0,
 0.8F, 1.0);
 } else if (this->OffAgeMax < 1000000000 && this->Age >= this->OffAgeMax) {
 tooltipUI.DrawText(
 uIFont,
 string1 = Translator.getText("IGUI_FoodNaming", string0, this->name),
 5.0, int1, 1.0, 0.1F, 0.1F, 1.0);
 } else {
 tooltipUI.DrawText(
 uIFont,
 string1 = Translator.getText("IGUI_FoodNaming", string0, this->name),
 5.0, int1, 1.0, 1.0, 0.8F, 1.0);
 }

 tooltipUI.adjustWidth(5, string1);
 int1 += int0 + 5;
 if (this->extraItems != nullptr) {
 tooltipUI.DrawText(uIFont, Translator.getText("Tooltip_item_Contains"),
 5.0, int1, 1.0, 1.0, 0.8F, 1.0);
 int int2 = 5 +
 TextManager.instance.MeasureStringX(
 uIFont, Translator.getText("Tooltip_item_Contains")) +
 4;
 int int3 = (int0 - 10) / 2;

 for (int int4 = 0; int4 < this->extraItems.size(); int4++) {
 InventoryItem item0 =
 InventoryItemFactory.CreateItem(this->extraItems.get(int4);
 if (!this->IsCookable && item0.IsCookable) {
 item0.setCooked(true);
 }

 if (this->isCooked() && item0.IsCookable) {
 item0.setCooked(true);
 }

 tooltipUI.DrawTextureScaled(item0.getTex(), int2, int1 + int3, 10.0,
 10.0, 1.0);
 int2 += 11;
 }

 int1 = int1 + int0 + 5;
 }

 if (this instanceof Food && ((Food)this).spices != nullptr) {
 tooltipUI.DrawText(uIFont, Translator.getText("Tooltip_item_Spices"), 5.0,
 int1, 1.0, 1.0, 0.8F, 1.0);
 int int5 = 5 +
 TextManager.instance.MeasureStringX(
 uIFont, Translator.getText("Tooltip_item_Spices")) +
 4;
 int int6 = (int0 - 10) / 2;

 for (int int7 = 0; int7 < ((Food)this).spices.size(); int7++) {
 InventoryItem item1 =
 InventoryItemFactory.CreateItem(((Food)this).spices.get(int7);
 tooltipUI.DrawTextureScaled(item1.getTex(), int5, int1 + int6, 10.0,
 10.0, 1.0);
 int5 += 11;
 }

 int1 = int1 + int0 + 5;
 }

 ObjectTooltip.Layout layout = tooltipUI.beginLayout();
 layout.setMinLabelWidth(80);
 ObjectTooltip.LayoutItem layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_item_Weight") + ":", 1.0F,
 1.0F, 0.8F, 1.0F);
 bool boolean0 = this->isEquipped();
 if (!(this instanceof HandWeapon) && !(this instanceof Clothing) &&
 !(this instanceof DrainableComboItem) &&
 !this->getFullType().contains("Walkie")) {
 float float0 = this->getUnequippedWeight();
 if (float0 > 0.0F && float0 < 0.01F) {
 float0 = 0.01F;
 }

 layoutItem.setValueRightNoPlus(float0);
 } else if (boolean0) {
 layoutItem.setValue(
 this->getCleanString(this->getEquippedWeight()) + " (" +
 this->getCleanString(this->getUnequippedWeight()) + " " +
 Translator.getText("Tooltip_item_Unequipped") + ")",
 1.0F, 1.0F, 1.0F, 1.0F);
 } else if (this->getAttachedSlot() > -1) {
 layoutItem.setValue(
 this->getCleanString(this->getHotbarEquippedWeight()) + " (" +
 this->getCleanString(this->getUnequippedWeight()) + " " +
 Translator.getText("Tooltip_item_Unequipped") + ")",
 1.0F, 1.0F, 1.0F, 1.0F);
 } else {
 layoutItem.setValue(
 this->getCleanString(this->getUnequippedWeight()) + " (" +
 this->getCleanString(this->getEquippedWeight()) + " " +
 Translator.getText("Tooltip_item_Equipped") + ")",
 1.0F, 1.0F, 1.0F, 1.0F);
 }

 if (tooltipUI.getWeightOfStack() > 0.0F) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_item_StackWeight") + ":",
 1.0F, 1.0F, 0.8F, 1.0F);
 float float1 = tooltipUI.getWeightOfStack();
 if (float1 > 0.0F && float1 < 0.01F) {
 float1 = 0.01F;
 }

 layoutItem.setValueRightNoPlus(float1);
 }

 if (this->getMaxAmmo() > 0 && !(this instanceof HandWeapon) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_weapon_AmmoCount") + ":",
 1.0F, 1.0F, 0.8F, 1.0F);
 layoutItem.setValue(this->getCurrentAmmoCount() + " / " +
 this->getMaxAmmo(),
 1.0F, 1.0F, 1.0F, 1.0F);
 }

 if (!(this instanceof HandWeapon) && this->getAmmoType() != nullptr) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("ContextMenu_AmmoType") + ":",
 1.0F, 1.0F, 0.8F, 1.0F);
 std::string string2 =
 InventoryItemFactory.CreateItem(this->getAmmoType()).getDisplayName();
 layoutItem.setValue(Translator.getText(string2), 1.0F, 1.0F, 1.0F, 1.0F);
 }

 if (this->gunType != nullptr) {
 Item item2 = ScriptManager.instance.FindItem(this->getGunType());
 if (item2.empty()) {
 item2 = ScriptManager.instance.FindItem(this->getModule() + "." +
 this->ammoType);
 }

 if (item2 != nullptr) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("ContextMenu_GunType") + ":",
 1.0F, 1.0F, 0.8F, 1.0F);
 layoutItem.setValue(item2.getDisplayName(), 1.0F, 1.0F, 1.0F, 1.0F);
 }
 }

 if (Core.bDebug && DebugOptions.instance.TooltipInfo.getValue()) {
 layoutItem = layout.addItem();
 layoutItem.setLabel("getActualWeight()", 1.0F, 1.0F, 0.8F, 1.0F);
 layoutItem.setValueRightNoPlus(this->getActualWeight());
 layoutItem = layout.addItem();
 layoutItem.setLabel("getWeight()", 1.0F, 1.0F, 0.8F, 1.0F);
 layoutItem.setValueRightNoPlus(this->getWeight());
 layoutItem = layout.addItem();
 layoutItem.setLabel("getEquippedWeight()", 1.0F, 1.0F, 0.8F, 1.0F);
 layoutItem.setValueRightNoPlus(this->getEquippedWeight());
 layoutItem = layout.addItem();
 layoutItem.setLabel("getUnequippedWeight()", 1.0F, 1.0F, 0.8F, 1.0F);
 layoutItem.setValueRightNoPlus(this->getUnequippedWeight());
 layoutItem = layout.addItem();
 layoutItem.setLabel("getContentsWeight()", 1.0F, 1.0F, 0.8F, 1.0F);
 layoutItem.setValueRightNoPlus(this->getContentsWeight());
 if (this instanceof Key || "Doorknob" == this->type) {
 layoutItem = layout.addItem();
 layoutItem.setLabel("DBG: keyId", 1.0F, 1.0F, 0.8F, 1.0F);
 layoutItem.setValueRightNoPlus(this->getKeyId());
 }

 layoutItem = layout.addItem();
 layoutItem.setLabel("ID", 1.0F, 1.0F, 0.8F, 1.0F);
 layoutItem.setValueRightNoPlus(this->id);
 layoutItem = layout.addItem();
 layoutItem.setLabel("DictionaryID", 1.0F, 1.0F, 0.8F, 1.0F);
 layoutItem.setValueRightNoPlus(this->registry_id);
 ClothingItem clothingItem = this->getClothingItem();
 if (clothingItem != nullptr) {
 layoutItem = layout.addItem();
 layoutItem.setLabel("ClothingItem", 1.0F, 1.0F, 1.0F, 1.0F);
 layoutItem.setValue(this->getClothingItem().m_Name, 1.0F, 1.0F, 1.0F,
 1.0F);
 }
 }

 if (this->getFatigueChange() != 0.0F) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_item_Fatigue") + ": ",
 1.0F, 1.0F, 0.8F, 1.0F);
 layoutItem.setValueRight((int)(this->getFatigueChange() * 100.0F), false);
 }

 if (this instanceof DrainableComboItem) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("IGUI_invpanel_Remaining") + ": ",
 1.0F, 1.0F, 0.8F, 1.0F);
 float float2 = ((DrainableComboItem)this).getUsedDelta();
 ColorInfo colorInfo0 = new ColorInfo();
 Core.getInstance().getBadHighlitedColor().interp(
 Core.getInstance().getGoodHighlitedColor(), float2, colorInfo0);
 layoutItem.setProgress(float2, colorInfo0.getR(), colorInfo0.getG(),
 colorInfo0.getB(), 1.0F);
 }

 if (this->isTaintedWater() &&
 SandboxOptions.instance.EnableTaintedWaterText.getValue()) {
 layoutItem = layout.addItem();
 if (this->isCookable()) {
 layoutItem.setLabel(Translator.getText("Tooltip_item_TaintedWater"),
 1.0F, 0.5F, 0.5F, 1.0F);
 } else {
 layoutItem.setLabel(
 Translator.getText("Tooltip_item_TaintedWater_Plastic"), 1.0F, 0.5F,
 0.5F, 1.0F);
 }
 }

 this->DoTooltip(tooltipUI, layout);
 if (this->getRemoteControlID() != -1) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_TrapControllerID"), 1.0F,
 1.0F, 0.8F, 1.0F);
 layoutItem.setValue(Integer.toString(this->getRemoteControlID()), 1.0F,
 1.0F, 0.8F, 1.0F);
 }

 if (!FixingManager.getFixes(this).empty()) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_weapon_Repaired") + ":",
 1.0F, 1.0F, 0.8F, 1.0F);
 if (this->getHaveBeenRepaired() == 1) {
 layoutItem.setValue(Translator.getText("Tooltip_never"), 1.0F, 1.0F,
 1.0F, 1.0F);
 } else {
 layoutItem.setValue(this->getHaveBeenRepaired() - 1 + "x", 1.0F, 1.0F,
 1.0F, 1.0F);
 }
 }

 if (this->isEquippedNoSprint()) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_CantSprintEquipped"),
 1.0F, 0.1F, 0.1F, 1.0F);
 }

 if (this->isWet()) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_Wetness") + ": ", 1.0F,
 1.0F, 0.8F, 1.0F);
 float float3 = this->getWetCooldown() / 10000.0F;
 ColorInfo colorInfo1 = new ColorInfo();
 Core.getInstance().getGoodHighlitedColor().interp(
 Core.getInstance().getBadHighlitedColor(), float3, colorInfo1);
 layoutItem.setProgress(float3, colorInfo1.getR(), colorInfo1.getG(),
 colorInfo1.getB(), 1.0F);
 }

 if (this->getMaxCapacity() > 0) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_container_Capacity") +
 ":",
 1.0F, 1.0F, 0.8F, 1.0F);
 float float4 = this->getMaxCapacity();
 if (this->isConditionAffectsCapacity()) {
 float4 = VehiclePart.getNumberByCondition(this->getMaxCapacity(),
 this->getCondition(), 5.0F);
 }

 if (this->getItemCapacity() > -1.0F) {
 layoutItem.setValue(this->getItemCapacity() + " / " + float4, 1.0F, 1.0F,
 0.8F, 1.0F);
 } else {
 layoutItem.setValue("0 / " + float4, 1.0F, 1.0F, 0.8F, 1.0F);
 }
 }

 if (this->getConditionMax() > 0 && this->getMechanicType() > 0) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_weapon_Condition") + ":",
 1.0F, 1.0F, 0.8F, 1.0F);
 layoutItem.setValue(this->getCondition() + " / " + this->getConditionMax(),
 1.0F, 1.0F, 0.8F, 1.0F);
 }

 if (this->isRecordedMedia()) {
 MediaData mediaData = this->getMediaData();
 if (mediaData != nullptr) {
 if (mediaData.getTranslatedTitle() != nullptr) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_media_title") + ":",
 1.0F, 1.0F, 0.8F, 1.0F);
 layoutItem.setValue(mediaData.getTranslatedTitle(), 1.0F, 1.0F, 1.0F,
 1.0F);
 if (mediaData.getTranslatedSubTitle() != nullptr) {
 layoutItem = layout.addItem();
 layoutItem.setLabel("", 1.0F, 1.0F, 0.8F, 1.0F);
 layoutItem.setValue(mediaData.getTranslatedSubTitle(), 1.0F, 1.0F,
 1.0F, 1.0F);
 }
 }

 if (mediaData.getTranslatedAuthor() != nullptr) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("Tooltip_media_author") + ":",
 1.0F, 1.0F, 0.8F, 1.0F);
 layoutItem.setValue(mediaData.getTranslatedAuthor(), 1.0F, 1.0F, 1.0F,
 1.0F);
 }
 }
 }

 if (Core.getInstance().getOptionShowItemModInfo() && !this->isVanilla()) {
 layoutItem = layout.addItem();
 Color color = Colors.CornFlowerBlue;
 layoutItem.setLabel("Mod: " + this->getModName(), color.r, color.g,
 color.b, 1.0F);
 ItemInfo itemInfo = WorldDictionary.getItemInfoFromID(this->registry_id);
 if (itemInfo != nullptr && itemInfo.getModOverrides() != nullptr) {
 layoutItem = layout.addItem();
 float float5 = 0.5F;
 if (itemInfo.getModOverrides().size() == 1) {
 layoutItem.setLabel("This item overrides: " +
 WorldDictionary.getModNameFromID(
 itemInfo.getModOverrides().get(0),
 float5, float5, float5, 1.0F);
 } else {
 layoutItem.setLabel("This item overrides:", float5, float5, float5,
 1.0F);

 for (int int8 = 0; int8 < itemInfo.getModOverrides().size(); int8++) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(" - " +
 WorldDictionary.getModNameFromID(
 itemInfo.getModOverrides().get(int8),
 float5, float5, float5, 1.0F);
 }
 }
 }
 }

 if (this->getTooltip() != nullptr) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText(this->tooltip), 1.0F, 1.0F, 0.8F,
 1.0F);
 }

 int1 = layout.render(5, int1, tooltipUI);
 tooltipUI.endLayout(layout);
 int1 += tooltipUI.padBottom;
 tooltipUI.setHeight(int1);
 if (tooltipUI.getWidth() < 150.0) {
 tooltipUI.setWidth(150.0);
 }
 }

 std::string getCleanString(float weight) {
 float float0 = (int)((weight + 0.005) * 100.0) / 100.0F;
 return Float.toString(float0);
 }

 void DoTooltip(ObjectTooltip tooltipUI, ObjectTooltip.Layout layout) {}

 void SetContainerPosition(int x, int y) {
 this->containerX = x;
 this->containerY = y;
 }

 void Use() { this->Use(false); }

 void UseItem() { this->Use(false); }

 void Use(bool bCrafting) { this->Use(bCrafting, false); }

 void Use(bool bCrafting, bool bInContainer) {
 if (this->isDisappearOnUse() || bCrafting) {
 this->uses--;
 if (this->replaceOnUse != nullptr && !bInContainer && !bCrafting &&
 this->container != nullptr) {
 std::string string = this->replaceOnUse;
 if (!this->replaceOnUse.contains(".")) {
 string = this->module + "." + string;
 }

 InventoryItem item = this->container.AddItem(string);
 if (item != nullptr) {
 item.setConditionFromModData(this);
 }

 this->container.setDrawDirty(true);
 this->container.setDirty(true);
 item.setFavorite(this->isFavorite());
 }

 if (this->uses <= 0) {
 if (this->keepOnDeplete) {
 return;
 }

 if (this->container != nullptr) {
 if (this->container.parent instanceof
 IsoGameCharacter && !(this instanceof HandWeapon) {
 IsoGameCharacter character =
 (IsoGameCharacter)this->container.parent;
 character.removeFromHands(this);
 }

 this->container.Items.remove(this);
 this->container.setDirty(true);
 this->container.setDrawDirty(true);
 this->container = nullptr;
 }
 }
 }
 }

 bool shouldUpdateInWorld() {
 if (!GameClient.bClient && !this->rainFactorZero && this->canStoreWater() &&
 this->hasReplaceType("WaterSource")) {
 IsoGridSquare square = this->getWorldItem().getSquare();
 return square != nullptr && square.isOutside();
 } else {
 return false;
 }
 }

 void update() {
 if (this->isWet()) {
 this->wetCooldown =
 this->wetCooldown - 1.0F * GameTime.instance.getMultiplier();
 if (this->wetCooldown <= 0.0F) {
 InventoryItem item1 = InventoryItemFactory.CreateItem(this->itemWhenDry);
 if (this->isFavorite()) {
 item1.setFavorite(true);
 }

 IsoWorldInventoryObject worldInventoryObject0 = this->getWorldItem();
 if (worldInventoryObject0 != nullptr) {
 IsoGridSquare square0 = worldInventoryObject0.getSquare();
 square0.AddWorldInventoryItem(item1,
 worldInventoryObject0.getX() % 1.0F,
 worldInventoryObject0.getY() % 1.0F,
 worldInventoryObject0.getZ() % 1.0F);
 square0.transmitRemoveItemFromSquare(worldInventoryObject0);
 if (this->getContainer() != nullptr) {
 this->getContainer().setDirty(true);
 this->getContainer().setDrawDirty(true);
 }

 square0.chunk.recalcHashCodeObjects();
 this->setWorldItem(nullptr);
 } else if (this->getContainer() != nullptr) {
 this->getContainer().addItem(item1);
 this->getContainer().Remove(this);
 }

 this->setWet(false);
 IsoWorld.instance.CurrentCell.addToProcessItemsRemove(this);
 LuaEventManager.triggerEvent("OnContainerUpdate");
 }
 }

 if (!GameClient.bClient && !this->rainFactorZero &&
 this->getWorldItem() != nullptr && this->canStoreWater() &&
 this->hasReplaceType("WaterSource") && RainManager.isRaining()) {
 IsoWorldInventoryObject worldInventoryObject1 = this->getWorldItem();
 IsoGridSquare square1 = worldInventoryObject1.getSquare();
 if (square1 != nullptr && square1.isOutside()) {
 InventoryItem item2 =
 InventoryItemFactory.CreateItem(this->getReplaceType("WaterSource"));
 if (item2.empty()) {
 this->rainFactorZero = true;
 return;
 }

 item2.setCondition(this->getCondition());
 if (item2 instanceof DrainableComboItem && item2.canStoreWater()) {
 if (((DrainableComboItem)item2).getRainFactor() == 0.0F) {
 this->rainFactorZero = true;
 return;
 }

 ((DrainableComboItem)item2).setUsedDelta(0.0F);
 worldInventoryObject1.swapItem(item2);
 }
 }
 }
 }

 bool finishupdate() {
 return !GameClient.bClient && !this->rainFactorZero &&
 this->canStoreWater() && this->hasReplaceType("WaterSource") &&
 this->getWorldItem() != nullptr &&
 this->getWorldItem().getObjectIndex() != -1
 ? false
 : !this->isWet();
 }

 void updateSound(BaseSoundEmitter emitter) {}

 std::string getFullType() {
 assert this->fullType != nullptr && this->fullType == this->module + "." + this->type);

 return this->fullType;
 }

 void save(ByteBuffer output, bool net) {
 net = false;
 if (GameWindow.DEBUG_SAVE) {
 DebugLog.log(this->getFullType());
 }

 output.putShort(this->registry_id);
 output.put((byte)this->getSaveType());
 output.putInt(this->id);
 BitHeaderWrite bitHeaderWrite0 =
 BitHeader.allocWrite(BitHeader.HeaderSize.Byte, output);
 if (this->uses != 1) {
 bitHeaderWrite0.addFlags(1);
 if (this->uses > 32767) {
 output.putShort((short)32767);
 } else {
 output.putShort((short)this->uses);
 }
 }

 if (this->IsDrainable() &&
 ((DrainableComboItem)this).getUsedDelta() < 1.0F) {
 bitHeaderWrite0.addFlags(2);
 float float0 = ((DrainableComboItem)this).getUsedDelta();
 uint8_t byte0 = (byte)((byte)(float0 * 255.0F) + -128);
 output.put(byte0);
 }

 if (this->Condition != this->ConditionMax) {
 bitHeaderWrite0.addFlags(4);
 output.put((byte)this->getCondition());
 }

 if (this->visual != nullptr) {
 bitHeaderWrite0.addFlags(8);
 this->visual.save(output);
 }

 if (this->isCustomColor() && (this->col.r != 1.0F || this->col.g != 1.0F ||
 this->col.b != 1.0F || this->col.a != 1.0F) {
 bitHeaderWrite0.addFlags(16);
 output.put(Bits.packFloatUnitToByte(this->getColor().r);
 output.put(Bits.packFloatUnitToByte(this->getColor().g);
 output.put(Bits.packFloatUnitToByte(this->getColor().b);
 output.put(Bits.packFloatUnitToByte(this->getColor().a);
 }

 if (this->itemCapacity != -1.0F) {
 bitHeaderWrite0.addFlags(32);
 output.putFloat(this->itemCapacity);
 }

 BitHeaderWrite bitHeaderWrite1 =
 BitHeader.allocWrite(BitHeader.HeaderSize.Integer, output);
 if (this->table != nullptr && !this->table.empty()) {
 bitHeaderWrite1.addFlags(1);
 this->table.save(output);
 }

 if (this->isActivated()) {
 bitHeaderWrite1.addFlags(2);
 }

 if (this->haveBeenRepaired != 1) {
 bitHeaderWrite1.addFlags(4);
 output.putShort((short)this->getHaveBeenRepaired());
 }

 if (this->name != nullptr && !this->name == this->originalName) {
 bitHeaderWrite1.addFlags(8);
 GameWindow.WriteString(output, this->name);
 }

 if (this->byteData != nullptr) {
 bitHeaderWrite1.addFlags(16);
 this->byteData.rewind();
 output.putInt(this->byteData.limit());
 output.put(this->byteData);
 this->byteData.flip();
 }

 if (this->extraItems != nullptr && this->extraItems.size() > 0) {
 bitHeaderWrite1.addFlags(32);
 output.putInt(this->extraItems.size());

 for (int int0 = 0; int0 < this->extraItems.size(); int0++) {
 output.putShort(
 WorldDictionary.getItemRegistryID(this->extraItems.get(int0));
 }
 }

 if (this->isCustomName()) {
 bitHeaderWrite1.addFlags(64);
 }

 if (this->isCustomWeight()) {
 bitHeaderWrite1.addFlags(128);
 output.putFloat(this->isCustomWeight() ? this->getActualWeight() : -1.0F);
 }

 if (this->keyId != -1) {
 bitHeaderWrite1.addFlags(256);
 output.putInt(this->getKeyId());
 }

 if (this->isTaintedWater()) {
 bitHeaderWrite1.addFlags(512);
 }

 if (this->remoteControlID != -1 || this->remoteRange != 0) {
 bitHeaderWrite1.addFlags(1024);
 output.putInt(this->getRemoteControlID());
 output.putInt(this->getRemoteRange());
 }

 if (this->colorRed != 1.0F || this->colorGreen != 1.0F ||
 this->colorBlue != 1.0F) {
 bitHeaderWrite1.addFlags(2048);
 output.put(Bits.packFloatUnitToByte(this->colorRed);
 output.put(Bits.packFloatUnitToByte(this->colorGreen);
 output.put(Bits.packFloatUnitToByte(this->colorBlue);
 }

 if (this->worker != nullptr) {
 bitHeaderWrite1.addFlags(4096);
 GameWindow.WriteString(output, this->getWorker());
 }

 if (this->wetCooldown != -1.0F) {
 bitHeaderWrite1.addFlags(8192);
 output.putFloat(this->wetCooldown);
 }

 if (this->isFavorite()) {
 bitHeaderWrite1.addFlags(16384);
 }

 if (this->stashMap != nullptr) {
 bitHeaderWrite1.addFlags(32768);
 GameWindow.WriteString(output, this->stashMap);
 }

 if (this->isInfected()) {
 bitHeaderWrite1.addFlags(65536);
 }

 if (this->currentAmmoCount != 0) {
 bitHeaderWrite1.addFlags(131072);
 output.putInt(this->currentAmmoCount);
 }

 if (this->attachedSlot != -1) {
 bitHeaderWrite1.addFlags(262144);
 output.putInt(this->attachedSlot);
 }

 if (this->attachedSlotType != nullptr) {
 bitHeaderWrite1.addFlags(524288);
 GameWindow.WriteString(output, this->attachedSlotType);
 }

 if (this->attachedToModel != nullptr) {
 bitHeaderWrite1.addFlags(1048576);
 GameWindow.WriteString(output, this->attachedToModel);
 }

 if (this->maxCapacity != -1) {
 bitHeaderWrite1.addFlags(2097152);
 output.putInt(this->maxCapacity);
 }

 if (this->isRecordedMedia()) {
 bitHeaderWrite1.addFlags(4194304);
 output.putShort(this->recordedMediaIndex);
 }

 if (this->worldZRotation > -1) {
 bitHeaderWrite1.addFlags(8388608);
 output.putInt(this->worldZRotation);
 }

 if (this->worldScale != 1.0F) {
 bitHeaderWrite1.addFlags(16777216);
 output.putFloat(this->worldScale);
 }

 if (this->isInitialised) {
 bitHeaderWrite1.addFlags(33554432);
 }

 if (!bitHeaderWrite1 == 0) {
 bitHeaderWrite0.addFlags(64);
 bitHeaderWrite1.write();
 }
 else {
 output.position(bitHeaderWrite1.getStartPosition());
 }

 bitHeaderWrite0.write();
 bitHeaderWrite0.release();
 bitHeaderWrite1.release();
 }

 static InventoryItem loadItem(ByteBuffer input, int WorldVersion) {
 return loadItem();
 }

 /**
 * Attempts loading the item including creation, uppon failure bytes might be
 * skipped or the buffer position may be set to end item position. Item needs
 * to be saved with size.
 * @return InventoryItem, or nullptr if the item failed loading or if Creating
 * the item failed due to being obsolete etc.
 */
 static InventoryItem loadItem(ByteBuffer input, int WorldVersion,
 bool doSaveTypeCheck) {
 int int0 = input.getInt();
 if (int0 <= 0) {
 throw IOException(
 "InventoryItem.loadItem() invalid item data length: " + int0);
 } else {
 int int1 = input.position();
 short short0 = input.getShort();
 uint8_t byte0 = -1;
 if (WorldVersion >= 70) {
 byte0 = input.get();
 if (byte0 < 0) {
 DebugLog.log(
 "InventoryItem.loadItem() invalid item save-type " + byte0 +
 ", itemtype: " + WorldDictionary.getItemTypeDebugString(short0);
 return nullptr;
 }
 }

 InventoryItem item = InventoryItemFactory.CreateItem(short0);
 if (doSaveTypeCheck && byte0 != -1 && item != nullptr &&
 item.getSaveType() != byte0) {
 DebugLog.log("InventoryItem.loadItem() ignoring \"" +
 item.getFullType() + "\" because type changed from " +
 byte0 + " to " + item.getSaveType());
 item = nullptr;
 }

 if (item != nullptr) {
 try {
 item.load(input, WorldVersion);
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 item = nullptr;
 }
 }

 if (item != nullptr) {
 if (int0 != -1 && input.position() != int1 + int0) {
 input.position(int1 + int0);
 DebugLog.log("InventoryItem.loadItem() data length not matching, "
 "resetting buffer position to '" +
 (int1 + int0) + "'. itemtype: " +
 WorldDictionary.getItemTypeDebugString(short0);
 if (Core.bDebug) {
 throw IOException(
 "InventoryItem.loadItem() read more data than save() wrote (" +
 WorldDictionary.getItemTypeDebugString(short0) + ")");
 }
 }

 return item;
 } else {
 if (input.position() >= int1 + int0) {
 if (input.position() >= int1 + int0) {
 input.position(int1 + int0);
 DebugLog.log("InventoryItem.loadItem() item.empty(), resetting "
 "buffer position to '" +
 (int1 + int0) + "'. itemtype: " +
 WorldDictionary.getItemTypeDebugString(short0);
 }
 } else {
 while (input.position() < int1 + int0) {
 input.get();
 }

 DebugLog.log("InventoryItem.loadItem() item.empty(), skipped "
 "bytes. itemtype: " +
 WorldDictionary.getItemTypeDebugString(short0);
 }

 return nullptr;
 }
 }
 }

 void load(ByteBuffer input, int WorldVersion) {
 this->id = input.getInt();
 BitHeaderRead bitHeaderRead0 =
 BitHeader.allocRead(BitHeader.HeaderSize.Byte, input);
 this->uses = 1;
 if (this->IsDrainable()) {
 ((DrainableComboItem)this).setUsedDelta(1.0F);
 }

 this->Condition = this->ConditionMax;
 this->customColor = false;
 this->col = Color.white;
 this->itemCapacity = -1.0F;
 this->activated = false;
 this->haveBeenRepaired = 1;
 this->customName = false;
 this->customWeight = false;
 this->keyId = -1;
 this->taintedWater = false;
 this->remoteControlID = -1;
 this->remoteRange = 0;
 this->colorRed = this->colorGreen = this->colorBlue = 1.0F;
 this->worker = nullptr;
 this->wetCooldown = -1.0F;
 this->favorite = false;
 this->stashMap = nullptr;
 this->zombieInfected = false;
 this->currentAmmoCount = 0;
 this->attachedSlot = -1;
 this->attachedSlotType = nullptr;
 this->attachedToModel = nullptr;
 this->maxCapacity = -1;
 this->recordedMediaIndex = -1;
 this->worldZRotation = -1;
 this->worldScale = 1.0F;
 this->isInitialised = false;
 if (!bitHeaderRead0 == 0) {
 if (bitHeaderRead0.hasFlags(1) {
 this->uses = input.getShort();
 }

 if (bitHeaderRead0.hasFlags(2) {
 uint8_t byte0 = input.get();
 float float0 = PZMath.clamp((byte0 - -128) / 255.0F, 0.0F, 1.0F);
 ((DrainableComboItem)this).setUsedDelta(float0);
 }

 if (bitHeaderRead0.hasFlags(4) {
 this->setCondition(input.get(), false);
 }

 if (bitHeaderRead0.hasFlags(8) {
 this->visual = std::make_unique<ItemVisual>();
 this->visual.load(input, WorldVersion);
 }

 if (bitHeaderRead0.hasFlags(16) {
 float float1 = Bits.unpackByteToFloatUnit(input.get());
 float float2 = Bits.unpackByteToFloatUnit(input.get());
 float float3 = Bits.unpackByteToFloatUnit(input.get());
 float float4 = Bits.unpackByteToFloatUnit(input.get());
 this->setColor(new Color(float1, float2, float3, float4);
 }

 if (bitHeaderRead0.hasFlags(32) {
 this->itemCapacity = input.getFloat();
 }

 if (bitHeaderRead0.hasFlags(64) {
 BitHeaderRead bitHeaderRead1 =
 BitHeader.allocRead(BitHeader.HeaderSize.Integer, input);
 if (bitHeaderRead1.hasFlags(1) {
 if (this->table.empty()) {
 this->table = LuaManager.platform.newTable();
 }

 this->table.load(input, WorldVersion);
 }

 this->activated = bitHeaderRead1.hasFlags(2);
 if (bitHeaderRead1.hasFlags(4) {
 this->setHaveBeenRepaired(input.getShort());
 }

 if (bitHeaderRead1.hasFlags(8) {
 this->name = GameWindow.ReadString(input);
 }

 if (bitHeaderRead1.hasFlags(16) {
 int int0 = input.getInt();
 this->byteData = ByteBuffer.allocate(int0);

 for (int int1 = 0; int1 < int0; int1++) {
 this->byteData.put(input.get());
 }

 this->byteData.flip();
 }

 if (bitHeaderRead1.hasFlags(32) {
 int int2 = input.getInt();
 if (int2 > 0) {
 this->extraItems = std::make_unique<ArrayList<>>();

 for (int int3 = 0; int3 < int2; int3++) {
 short short0 = input.getShort();
 std::string string = WorldDictionary.getItemTypeFromID(short0);
 this->extraItems.add(string);
 }
 }
 }

 this->setCustomName(bitHeaderRead1.hasFlags(64);
 if (bitHeaderRead1.hasFlags(128) {
 float float5 = input.getFloat();
 if (float5 >= 0.0F) {
 this->setActualWeight(float5);
 this->setWeight(float5);
 this->setCustomWeight(true);
 }
 }

 if (bitHeaderRead1.hasFlags(256) {
 this->setKeyId(input.getInt());
 }

 this->setTaintedWater(bitHeaderRead1.hasFlags(512);
 if (bitHeaderRead1.hasFlags(1024) {
 this->setRemoteControlID(input.getInt());
 this->setRemoteRange(input.getInt());
 }

 if (bitHeaderRead1.hasFlags(2048) {
 float float6 = Bits.unpackByteToFloatUnit(input.get());
 float float7 = Bits.unpackByteToFloatUnit(input.get());
 float float8 = Bits.unpackByteToFloatUnit(input.get());
 this->setColorRed(float6);
 this->setColorGreen(float7);
 this->setColorBlue(float8);
 this->setColor(
 new Color(this->colorRed, this->colorGreen, this->colorBlue);
 }

 if (bitHeaderRead1.hasFlags(4096) {
 this->setWorker(GameWindow.ReadString(input);
 }

 if (bitHeaderRead1.hasFlags(8192) {
 this->setWetCooldown(input.getFloat());
 }

 this->setFavorite(bitHeaderRead1.hasFlags(16384);
 if (bitHeaderRead1.hasFlags(32768) {
 this->stashMap = GameWindow.ReadString(input);
 }

 this->setInfected(bitHeaderRead1.hasFlags(65536);
 if (bitHeaderRead1.hasFlags(131072) {
 this->setCurrentAmmoCount(input.getInt());
 }

 if (bitHeaderRead1.hasFlags(262144) {
 this->attachedSlot = input.getInt();
 }

 if (bitHeaderRead1.hasFlags(524288) {
 if (WorldVersion < 179) {
 short short1 = input.getShort();
 this->attachedSlotType = nullptr;
 } else {
 this->attachedSlotType = GameWindow.ReadString(input);
 }
 }

 if (bitHeaderRead1.hasFlags(1048576) {
 this->attachedToModel = GameWindow.ReadString(input);
 }

 if (bitHeaderRead1.hasFlags(2097152) {
 this->maxCapacity = input.getInt();
 }

 if (bitHeaderRead1.hasFlags(4194304) {
 this->setRecordedMediaIndex(input.getShort());
 }

 if (bitHeaderRead1.hasFlags(8388608) {
 this->setWorldZRotation(input.getInt());
 }

 if (bitHeaderRead1.hasFlags(16777216) {
 this->worldScale = input.getFloat();
 }

 this->setInitialised(bitHeaderRead1.hasFlags(33554432);
 bitHeaderRead1.release();
 }
 }

 bitHeaderRead0.release();
 }

 bool IsFood() { return false; }

 bool IsWeapon() { return false; }

 bool IsDrainable() { return false; }

 bool IsLiterature() { return false; }

 bool IsClothing() { return false; }

 bool IsInventoryContainer() { return false; }

 bool IsMap() { return false; }

 static InventoryItem LoadFromFile(DataInputStream dataInputStream) {
 GameWindow.ReadString(dataInputStream);
 return nullptr;
 }

 ItemContainer getOutermostContainer() {
 if (this->container != nullptr && !"floor" == this->container.type) {
 ItemContainer containerx = this->container;

 while (containerx.getContainingItem() != nullptr &&
 containerx.getContainingItem().getContainer() != nullptr &&
 !"floor" == containerx.getContainingItem().getContainer().type)
 ) {
 containerx = containerx.getContainingItem().getContainer();
 }

 return containerx;
 }
 else {
 return nullptr;
 }
 }

 bool isInLocalPlayerInventory() {
 if (!GameClient.bClient) {
 return false;
 } else {
 ItemContainer containerx = this->getOutermostContainer();
 if (containerx.empty()) {
 return false;
 } else {
 return containerx.getParent() instanceof
 IsoPlayer ? ((IsoPlayer)containerx.getParent()).isLocalPlayer()
 : false;
 }
 }
 }

 bool isInPlayerInventory() {
 ItemContainer containerx = this->getOutermostContainer();
 return containerx = = nullptr ? false : containerx.getParent() instanceof
 IsoPlayer;
 }

 ItemReplacement getItemReplacementPrimaryHand() {
 return this->ScriptItem.replacePrimaryHand;
 }

 ItemReplacement getItemReplacementSecondHand() {
 return this->ScriptItem.replaceSecondHand;
 }

 ClothingItem getClothingItem() {
 if ("RightHand".equalsIgnoreCase(this->getAlternateModelName())) {
 return this->getItemReplacementPrimaryHand().clothingItem;
 } else {
 return "LeftHand".equalsIgnoreCase(this->getAlternateModelName())
 ? this->getItemReplacementSecondHand().clothingItem
 : this->ScriptItem.getClothingItemAsset();
 }
 }

 std::string getAlternateModelName() {
 if (this->getContainer() != nullptr && this->getContainer().getParent()
 instanceof IsoGameCharacter) {
 IsoGameCharacter character =
 (IsoGameCharacter)this->getContainer().getParent();
 if (character.getPrimaryHandItem() == this &&
 this->getItemReplacementPrimaryHand() != nullptr) {
 return "RightHand";
 }

 if (character.getSecondaryHandItem() == this &&
 this->getItemReplacementSecondHand() != nullptr) {
 return "LeftHand";
 }
 }

 return this->m_alternateModelName;
 }

 ItemVisual getVisual() {
 ClothingItem clothingItem = this->getClothingItem();
 if (clothingItem != nullptr && clothingItem.isReady()) {
 if (this->visual.empty()) {
 this->visual = std::make_unique<ItemVisual>();
 this->visual.setItemType(this->getFullType());
 this->visual.pickUninitializedValues(clothingItem);
 }

 this->visual.setClothingItemName(clothingItem.m_Name);
 this->visual.setAlternateModelName(this->getAlternateModelName());
 return this->visual;
 } else {
 this->visual = nullptr;
 return nullptr;
 }
 }

 bool allowRandomTint() {
 ClothingItem clothingItem = this->getClothingItem();
 return clothingItem != nullptr ? clothingItem.m_AllowRandomTint : false;
 }

 void synchWithVisual() {
 if (this instanceof Clothing || this instanceof InventoryContainer) {
 ItemVisual itemVisual = this->getVisual();
 if (itemVisual != nullptr) {
 if (this instanceof
 Clothing && this->getBloodClothingType() != nullptr) {
 BloodClothingType.calcTotalBloodLevel((Clothing)this);
 }

 ClothingItem clothingItem = this->getClothingItem();
 if (clothingItem.m_AllowRandomTint) {
 this->setColor(new Color(itemVisual.m_Tint.r, itemVisual.m_Tint.g,
 itemVisual.m_Tint.b);
 } else {
 this->setColor(new Color(this->getColorRed(), this->getColorGreen(),
 this->getColorBlue()));
 }

 if ((clothingItem.m_BaseTextures.size() > 1 ||
 itemVisual.m_TextureChoice > -1) &&
 this->getIconsForTexture() != nullptr) {
 std::string string = nullptr;
 if (itemVisual.m_BaseTexture > -1 &&
 this->getIconsForTexture().size() > itemVisual.m_BaseTexture) {
 string = this->getIconsForTexture().get(itemVisual.m_BaseTexture);
 } else if (itemVisual.m_TextureChoice > -1 &&
 this->getIconsForTexture().size() >
 itemVisual.m_TextureChoice) {
 string = this->getIconsForTexture().get(itemVisual.m_TextureChoice);
 }

 if (!StringUtils.isNullOrWhitespace(string) {
 this->texture = Texture.trygetTexture("Item_" + string);
 if (this->texture.empty()) {
 this->texture =
 Texture.getSharedTexture("media/inventory/Question_On.png");
 }
 }
 }
 }
 }
 }

 /**
 * @return the containerX
 */
 int getContainerX() { return this->containerX; }

 /**
 *
 * @param _containerX the containerX to set
 */
 void setContainerX(int _containerX) { this->containerX = _containerX; }

 /**
 * @return the containerY
 */
 int getContainerY() { return this->containerY; }

 /**
 *
 * @param _containerY the containerY to set
 */
 void setContainerY(int _containerY) { this->containerY = _containerY; }

 /**
 * @return the DisappearOnUse
 */
 bool isDisappearOnUse() { return this->getScriptItem().isDisappearOnUse(); }

 /**
 * @return the name
 */
 std::string getName() {
 if (this->isBroken()) {
 return Translator.getText("IGUI_ItemNaming", this->brokenString,
 this->name);
 } else if (this->isTaintedWater() &&
 SandboxOptions.instance.EnableTaintedWaterText.getValue()) {
 return Translator.getText("IGUI_ItemNameTaintedWater", this->name);
 } else if (this->getRemoteControlID() != -1) {
 return Translator.getText("IGUI_ItemNameControllerLinked", this->name);
 } else {
 return this->getMechanicType() > 0
 ? Translator.getText(
 "IGUI_ItemNameMechanicalType", this->name,
 Translator.getText("IGUI_VehicleType_" +
 this->getMechanicType()))
 : this->name;
 }
 }

 /**
 *
 * @param _name the name to set
 */
 void setName(std::string_view _name) {
 if (_name.length() > 256) {
 _name = _name.substring(0, Math.min(_name.length(), 256);
 }

 this->name = _name;
 }

 /**
 * @return the replaceOnUse
 */
 std::string getReplaceOnUse() { return this->replaceOnUse; }

 /**
 *
 * @param _replaceOnUse the replaceOnUse to set
 */
 void setReplaceOnUse(std::string_view _replaceOnUse) {
 this->replaceOnUse = _replaceOnUse;
 this->replaceOnUseFullType =
 StringUtils.moduleDotType(this->getModule(), _replaceOnUse);
 }

 std::string getReplaceOnUseFullType() { return this->replaceOnUseFullType; }

 /**
 * @return the ConditionMax
 */
 int getConditionMax() { return this->ConditionMax; }

 /**
 *
 * @param _ConditionMax the ConditionMax to set
 */
 void setConditionMax(int _ConditionMax) { this->ConditionMax = _ConditionMax; }

 /**
 * @return the rightClickContainer
 */
 ItemContainer getRightClickContainer() { return this->rightClickContainer; }

 /**
 *
 * @param _rightClickContainer the rightClickContainer to set
 */
 void setRightClickContainer(ItemContainer _rightClickContainer) {
 this->rightClickContainer = _rightClickContainer;
 }

 /**
 * @return the swingAnim
 */
 std::string getSwingAnim() { return this->getScriptItem().SwingAnim; }

 /**
 * @return the texture
 */
 Texture getTexture() { return this->texture; }

 /**
 *
 * @param _texture the texture to set
 */
 void setTexture(Texture _texture) { this->texture = _texture; }

 /**
 * @return the texturerotten
 */
 Texture getTexturerotten() { return this->texturerotten; }

 /**
 *
 * @param _texturerotten the texturerotten to set
 */
 void setTexturerotten(Texture _texturerotten) {
 this->texturerotten = _texturerotten;
 }

 /**
 * @return the textureCooked
 */
 Texture getTextureCooked() { return this->textureCooked; }

 /**
 *
 * @param _textureCooked the textureCooked to set
 */
 void setTextureCooked(Texture _textureCooked) {
 this->textureCooked = _textureCooked;
 }

 /**
 * @return the textureBurnt
 */
 Texture getTextureBurnt() { return this->textureBurnt; }

 /**
 *
 * @param _textureBurnt the textureBurnt to set
 */
 void setTextureBurnt(Texture _textureBurnt) {
 this->textureBurnt = _textureBurnt;
 }

 /**
 *
 * @param _type the type to set
 */
 void setType(std::string_view _type) {
 this->type = _type;
 this->fullType = this->module + "." + _type;
 }

 int getCurrentUses() { return this->uses; }

 /**
 * @return the uses
 */
 int getUses() { return 1; }

 /**
 *
 * @param _uses the uses to set
 */
 void setUses(int _uses) {}

 /**
 * @return the Age
 */
 float getAge() { return this->Age; }

 /**
 *
 * @param _Age the Age to set
 */
 void setAge(float _Age) { this->Age = _Age; }

 float getLastAged() { return this->LastAged; }

 void setLastAged(float time) { this->LastAged = time; }

 void updateAge() {}

 void setAutoAge() {}

 /**
 * @return the IsCookable
 */
 bool isIsCookable() { return this->IsCookable; }

 /**
 * @return the IsCookable
 */
 bool isCookable() { return this->IsCookable; }

 /**
 *
 * @param _IsCookable the IsCookable to set
 */
 void setIsCookable(bool _IsCookable) { this->IsCookable = _IsCookable; }

 /**
 * @return the CookingTime
 */
 float getCookingTime() { return this->CookingTime; }

 /**
 *
 * @param _CookingTime the CookingTime to set
 */
 void setCookingTime(float _CookingTime) { this->CookingTime = _CookingTime; }

 /**
 * @return the MinutesToCook
 */
 float getMinutesToCook() { return this->MinutesToCook; }

 /**
 *
 * @param _MinutesToCook the MinutesToCook to set
 */
 void setMinutesToCook(float _MinutesToCook) {
 this->MinutesToCook = _MinutesToCook;
 }

 /**
 * @return the MinutesToBurn
 */
 float getMinutesToBurn() { return this->MinutesToBurn; }

 /**
 *
 * @param _MinutesToBurn the MinutesToBurn to set
 */
 void setMinutesToBurn(float _MinutesToBurn) {
 this->MinutesToBurn = _MinutesToBurn;
 }

 /**
 * @return the Cooked
 */
 bool isCooked() { return this->Cooked; }

 /**
 *
 * @param _Cooked the Cooked to set
 */
 void setCooked(bool _Cooked) { this->Cooked = _Cooked; }

 /**
 * @return the Burnt
 */
 bool isBurnt() { return this->Burnt; }

 /**
 *
 * @param _Burnt the Burnt to set
 */
 void setBurnt(bool _Burnt) { this->Burnt = _Burnt; }

 /**
 * @return the OffAge
 */
 int getOffAge() { return this->OffAge; }

 /**
 *
 * @param _OffAge the OffAge to set
 */
 void setOffAge(int _OffAge) { this->OffAge = _OffAge; }

 /**
 * @return the OffAgeMax
 */
 int getOffAgeMax() { return this->OffAgeMax; }

 /**
 *
 * @param _OffAgeMax the OffAgeMax to set
 */
 void setOffAgeMax(int _OffAgeMax) { this->OffAgeMax = _OffAgeMax; }

 /**
 * @return the Weight
 */
 float getWeight() { return this->Weight; }

 /**
 *
 * @param _Weight the Weight to set
 */
 void setWeight(float _Weight) { this->Weight = _Weight; }

 /**
 * @return the ActualWeight
 */
 float getActualWeight() {
 return this->getDisplayName() == this->getFullType()) ? 0.0F : this->ActualWeight;
 }

 /**
 *
 * @param _ActualWeight the ActualWeight to set
 */
 void setActualWeight(float _ActualWeight) {
 this->ActualWeight = _ActualWeight;
 }

 /**
 * @return the WorldTexture
 */
 std::string getWorldTexture() { return this->WorldTexture; }

 /**
 *
 * @param _WorldTexture the WorldTexture to set
 */
 void setWorldTexture(std::string_view _WorldTexture) {
 this->WorldTexture = _WorldTexture;
 }

 /**
 * @return the Description
 */
 std::string getDescription() { return this->Description; }

 /**
 *
 * @param _Description the Description to set
 */
 void setDescription(std::string_view _Description) {
 this->Description = _Description;
 }

 /**
 * @return the Condition
 */
 int getCondition() { return this->Condition; }

 void setCondition(int _Condition, bool doSound) {
 _Condition = Math.max(0, _Condition);
 if (this->Condition > 0 && _Condition <= 0 && doSound &&
 this->getBreakSound() != nullptr && !this->getBreakSound().empty() &&
 IsoPlayer.getInstance() != nullptr) {
 IsoPlayer.getInstance().playSound(this->getBreakSound());
 }

 this->Condition = _Condition;
 this->setBroken(_Condition <= 0);
 }

 /**
 *
 * @param _Condition the Condition to set
 */
 void setCondition(int _Condition) { this->setCondition(_Condition, true); }

 /**
 * @return the OffString
 */
 std::string getOffString() { return this->OffString; }

 /**
 *
 * @param _OffString the OffString to set
 */
 void setOffString(std::string_view _OffString) {
 this->OffString = _OffString;
 }

 /**
 * @return the CookedString
 */
 std::string getCookedString() { return this->CookedString; }

 /**
 *
 * @param _CookedString the CookedString to set
 */
 void setCookedString(std::string_view _CookedString) {
 this->CookedString = _CookedString;
 }

 /**
 * @return the UnCookedString
 */
 std::string getUnCookedString() { return this->UnCookedString; }

 /**
 *
 * @param _UnCookedString the UnCookedString to set
 */
 void setUnCookedString(std::string_view _UnCookedString) {
 this->UnCookedString = _UnCookedString;
 }

 /**
 * @return the BurntString
 */
 std::string getBurntString() { return this->BurntString; }

 /**
 *
 * @param _BurntString the BurntString to set
 */
 void setBurntString(std::string_view _BurntString) {
 this->BurntString = _BurntString;
 }

 /**
 * @return the module
 */
 std::string getModule() { return this->module; }

 /**
 *
 * @param _module the module to set
 */
 void setModule(std::string_view _module) {
 this->module = _module;
 this->fullType = _module + "." + this->type;
 }

 /**
 * @return the AlwaysWelcomeGift
 */
 bool isAlwaysWelcomeGift() {
 return this->getScriptItem().isAlwaysWelcomeGift();
 }

 /**
 * @return the CanBandage
 */
 bool isCanBandage() { return this->getScriptItem().isCanBandage(); }

 /**
 * @return the boredomChange
 */
 float getBoredomChange() { return this->boredomChange; }

 /**
 *
 * @param _boredomChange the boredomChange to set
 */
 void setBoredomChange(float _boredomChange) {
 this->boredomChange = _boredomChange;
 }

 /**
 * @return the unhappyChange
 */
 float getUnhappyChange() { return this->unhappyChange; }

 /**
 *
 * @param _unhappyChange the unhappyChange to set
 */
 void setUnhappyChange(float _unhappyChange) {
 this->unhappyChange = _unhappyChange;
 }

 /**
 * @return the stressChange
 */
 float getStressChange() { return this->stressChange; }

 /**
 *
 * @param _stressChange the stressChange to set
 */
 void setStressChange(float _stressChange) {
 this->stressChange = _stressChange;
 }

public
 ArrayList<String> getTags() { return this->ScriptItem.getTags(); }

 bool hasTag(std::string_view tag) {
 std::vector arrayList = this->getTags();

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 if (((String)arrayList.get(int0).equalsIgnoreCase(tag) {
 return true;
 }
 }

 return false;
 }

 /**
 * @return the Taken
 */
public
 ArrayList<IsoObject> getTaken() { return this->Taken; }

 /**
 *
 * @param _Taken the Taken to set
 */
 void setTaken(ArrayList<IsoObject> _Taken) { this->Taken = _Taken; }

 /**
 * @return the placeDir
 */
 IsoDirections getPlaceDir() { return this->placeDir; }

 /**
 *
 * @param _placeDir the placeDir to set
 */
 void setPlaceDir(IsoDirections _placeDir) { this->placeDir = _placeDir; }

 /**
 * @return the newPlaceDir
 */
 IsoDirections getNewPlaceDir() { return this->newPlaceDir; }

 /**
 *
 * @param _newPlaceDir the newPlaceDir to set
 */
 void setNewPlaceDir(IsoDirections _newPlaceDir) {
 this->newPlaceDir = _newPlaceDir;
 }

 void setReplaceOnUseOn(std::string_view _ReplaceOnUseOn) {
 this->ReplaceOnUseOn = _ReplaceOnUseOn;
 }

 std::string getReplaceOnUseOn() { return this->ReplaceOnUseOn; }

 std::string getReplaceOnUseOnString() {
 std::string string = this->getReplaceOnUseOn();
 if (string.split("-")[0].trim().contains("WaterSource")) {
 string = string.split("-")[1];
 if (!string.contains(".")) {
 string = this->getModule() + "." + string;
 }
 }

 return string;
 }

 std::string getReplaceTypes() {
 return this->getScriptItem().getReplaceTypes();
 }

public
 HashMap<String, String> getReplaceTypesMap() {
 return this->getScriptItem().getReplaceTypesMap();
 }

 std::string getReplaceType(std::string_view key) {
 return this->getScriptItem().getReplaceType(key);
 }

 bool hasReplaceType(std::string_view key) {
 return this->getScriptItem().hasReplaceType(key);
 }

 void setIsWaterSource(bool _IsWaterSource) {
 this->IsWaterSource = _IsWaterSource;
 }

 /**
 * @return the IsWaterSource
 */
 bool isWaterSource() { return this->IsWaterSource; }

 bool CanStackNoTemp(InventoryItem var1) { return false; }

 void CopyModData(KahluaTable DefaultModData) {
 this->copyModData(DefaultModData);
 }

 void copyModData(KahluaTable modData) {
 if (this->table != nullptr) {
 this->table.wipe();
 }

 if (modData != nullptr) {
 LuaManager.copyTable(this->getModData(), modData);
 }
 }

 int getCount() noexcept{ return this->Count; }

 void setCount(int count) { this->Count = count; }

 bool isActivated() { return this->activated; }

 void setActivated(bool _activated) {
 this->activated = _activated;
 if (this->canEmitLight() && GameClient.bClient &&
 this->getEquipParent() != nullptr) {
 if (this->getEquipParent().getPrimaryHandItem() == this) {
 this->getEquipParent().reportEvent("EventSetActivatedPrimary");
 } else if (this->getEquipParent().getSecondaryHandItem() == this) {
 this->getEquipParent().reportEvent("EventSetActivatedSecondary");
 }
 }
 }

 void setActivatedRemote(bool _activated) { this->activated = _activated; }

 void setCanBeActivated(bool activatedItem) {
 this->canBeActivated = activatedItem;
 }

 bool canBeActivated() { return this->canBeActivated; }

 void setLightStrength(float _lightStrength) {
 this->lightStrength = _lightStrength;
 }

 float getLightStrength() { return this->lightStrength; }

 bool isTorchCone() { return this->isTorchCone; }

 void setTorchCone(bool _isTorchCone) { this->isTorchCone = _isTorchCone; }

 float getTorchDot() { return this->getScriptItem().torchDot; }

 int getLightDistance() { return this->lightDistance; }

 void setLightDistance(int _lightDistance) {
 this->lightDistance = _lightDistance;
 }

 bool canEmitLight() {
 if (this->getLightStrength() <= 0.0F) {
 return false;
 } else {
 Drainable drainable = Type.tryCastTo(this, Drainable.class);
 return drainable = = nullptr || !(drainable.getUsedDelta() <= 0.0F);
 }
 }

 bool isEmittingLight() {
 return !this->canEmitLight() ? false
 : !this->canBeActivated() || this->isActivated();
 }

 bool canStoreWater() { return this->CanStoreWater; }

 float getFatigueChange() { return this->fatigueChange; }

 void setFatigueChange(float _fatigueChange) {
 this->fatigueChange = _fatigueChange;
 }

 /**
 * Return the real condition of the weapon, based on this calcul :
 * Condition/ConditionMax * 100
 * @return float
 */
 float getCurrentCondition() {
 float float0 = (float)this->Condition / this->ConditionMax;
 return Float.valueOf(float0 * 100.0F);
 }

 void setColor(Color color) { this->col = color; }

 Color getColor() { return this->col; }

 ColorInfo getColorInfo() {
 return new ColorInfo(this->col.getRedFloat(), this->col.getGreenFloat(),
 this->col.getBlueFloat(), this->col.getAlphaFloat());
 }

 bool isTwoHandWeapon() { return this->getScriptItem().TwoHandWeapon; }

 std::string getCustomMenuOption() { return this->customMenuOption; }

 void setCustomMenuOption(std::string_view _customMenuOption) {
 this->customMenuOption = _customMenuOption;
 }

 void setTooltip(std::string_view _tooltip) { this->tooltip = _tooltip; }

 std::string getTooltip() { return this->tooltip; }

 std::string getDisplayCategory() { return this->displayCategory; }

 void setDisplayCategory(std::string_view _displayCategory) {
 this->displayCategory = _displayCategory;
 }

 int getHaveBeenRepaired() { return this->haveBeenRepaired; }

 void setHaveBeenRepaired(int _haveBeenRepaired) {
 this->haveBeenRepaired = _haveBeenRepaired;
 }

 bool isBroken() { return this->broken; }

 void setBroken(bool _broken) { this->broken = _broken; }

 std::string getDisplayName() { return this->name; }

 bool isTrap() { return this->getScriptItem().Trap; }

 void addExtraItem(std::string_view _type) {
 if (this->extraItems.empty()) {
 this->extraItems = std::make_unique<ArrayList<>>();
 }

 this->extraItems.add(_type);
 }

 bool haveExtraItems() { return this->extraItems != nullptr; }

public
 ArrayList<String> getExtraItems() { return this->extraItems; }

 float getExtraItemsWeight() {
 if (!this->haveExtraItems()) {
 return 0.0F;
 } else {
 float float0 = 0.0F;

 for (int int0 = 0; int0 < this->extraItems.size(); int0++) {
 InventoryItem item1 =
 InventoryItemFactory.CreateItem(this->extraItems.get(int0);
 float0 += item1.getActualWeight();
 }

 return float0 * 0.6F;
 }
 }

 bool isCustomName() { return this->customName; }

 void setCustomName(bool _customName) { this->customName = _customName; }

 bool isFishingLure() { return this->getScriptItem().FishingLure; }

 void copyConditionModData(InventoryItem other) {
 if (other.hasModData()) {
 KahluaTableIterator kahluaTableIterator = other.getModData().iterator();

 while (kahluaTableIterator.advance()) {
 if (kahluaTableIterator.getKey() instanceof
 String && ((String)kahluaTableIterator.getKey())
 .startsWith("condition:")) {
 this->getModData().rawset(kahluaTableIterator.getKey(),
 kahluaTableIterator.getValue());
 }
 }
 }
 }

 void setConditionFromModData(InventoryItem other) {
 if (other.hasModData()) {
 void *object = other.getModData().rawget("condition:" + this->getType());
 if (object != nullptr && object instanceof Double) {
 this->setCondition(
 (int)Math.round((Double)object * this->getConditionMax()));
 }
 }
 }

 std::string getBreakSound() { return this->breakSound; }

 void setBreakSound(std::string_view _breakSound) {
 this->breakSound = _breakSound;
 }

 std::string getPlaceOneSound() {
 return this->getScriptItem().getPlaceOneSound();
 }

 std::string getPlaceMultipleSound() {
 return this->getScriptItem().getPlaceMultipleSound();
 }

 std::string getSoundByID(std::string_view ID) {
 return this->getScriptItem().getSoundByID(ID);
 }

 void setBeingFilled(bool v) { this->beingFilled = v; }

 bool isBeingFilled() { return this->beingFilled; }

 std::string getFillFromDispenserSound() {
 return this->getScriptItem().getFillFromDispenserSound();
 }

 std::string getFillFromTapSound() {
 return this->getScriptItem().getFillFromTapSound();
 }

 bool isAlcoholic() { return this->alcoholic; }

 void setAlcoholic(bool _alcoholic) { this->alcoholic = _alcoholic; }

 float getAlcoholPower() { return this->alcoholPower; }

 void setAlcoholPower(float _alcoholPower) {
 this->alcoholPower = _alcoholPower;
 }

 float getBandagePower() { return this->bandagePower; }

 void setBandagePower(float _bandagePower) {
 this->bandagePower = _bandagePower;
 }

 float getReduceInfectionPower() { return this->ReduceInfectionPower; }

 void setReduceInfectionPower(float reduceInfectionPower) {
 this->ReduceInfectionPower = reduceInfectionPower;
 }

 void saveWithSize(ByteBuffer output, bool net) {
 int int0 = output.position();
 output.putInt(0);
 int int1 = output.position();
 this->save(output, net);
 int int2 = output.position();
 output.position(int0);
 output.putInt(int2 - int1);
 output.position(int2);
 }

 bool isCustomWeight() { return this->customWeight; }

 void setCustomWeight(bool custom) { this->customWeight = custom; }

 float getContentsWeight() {
 if (!StringUtils.isNullOrEmpty(this->getAmmoType())) {
 Item item1 = ScriptManager.instance.FindItem(this->getAmmoType());
 if (item1 != nullptr) {
 return item1.getActualWeight() * this->getCurrentAmmoCount();
 }
 }

 return 0.0F;
 }

 float getHotbarEquippedWeight() {
 return (this->getActualWeight() + this->getContentsWeight()) * 0.7F;
 }

 float getEquippedWeight() {
 return (this->getActualWeight() + this->getContentsWeight()) * 0.3F;
 }

 float getUnequippedWeight() {
 return this->getActualWeight() + this->getContentsWeight();
 }

 bool isEquipped() {
 return this->getContainer() != nullptr && this->getContainer().getParent()
 instanceof
 IsoGameCharacter ? ((IsoGameCharacter)this->getContainer().getParent())
 .isEquipped(this)
 : false;
 }

 int getKeyId() { return this->keyId; }

 void setKeyId(int _keyId) { this->keyId = _keyId; }

 bool isTaintedWater() { return this->taintedWater; }

 void setTaintedWater(bool _taintedWater) {
 this->taintedWater = _taintedWater;
 }

 bool isRemoteController() { return this->remoteController; }

 void setRemoteController(bool _remoteController) {
 this->remoteController = _remoteController;
 }

 bool canBeRemote() { return this->canBeRemote; }

 void setCanBeRemote(bool _canBeRemote) { this->canBeRemote = _canBeRemote; }

 int getRemoteControlID() { return this->remoteControlID; }

 void setRemoteControlID(int _remoteControlID) {
 this->remoteControlID = _remoteControlID;
 }

 int getRemoteRange() { return this->remoteRange; }

 void setRemoteRange(int _remoteRange) { this->remoteRange = _remoteRange; }

 std::string getExplosionSound() { return this->explosionSound; }

 void setExplosionSound(std::string_view _explosionSound) {
 this->explosionSound = _explosionSound;
 }

 std::string getCountDownSound() noexcept{ return this->countDownSound; }

 void setCountDownSound(std::string_view sound) {
 this->countDownSound = sound;
 }

 float getColorRed() { return this->colorRed; }

 void setColorRed(float _colorRed) { this->colorRed = _colorRed; }

 float getColorGreen() { return this->colorGreen; }

 void setColorGreen(float _colorGreen) { this->colorGreen = _colorGreen; }

 float getColorBlue() { return this->colorBlue; }

 void setColorBlue(float _colorBlue) { this->colorBlue = _colorBlue; }

 std::string getEvolvedRecipeName() { return this->evolvedRecipeName; }

 void setEvolvedRecipeName(std::string_view _evolvedRecipeName) {
 this->evolvedRecipeName = _evolvedRecipeName;
 }

 float getMetalValue() { return this->metalValue; }

 void setMetalValue(float _metalValue) { this->metalValue = _metalValue; }

 float getItemHeat() { return this->itemHeat; }

 void setItemHeat(float _itemHeat) {
 if (_itemHeat > 2.0F) {
 _itemHeat = 2.0F;
 }

 if (_itemHeat < 0.0F) {
 _itemHeat = 0.0F;
 }

 this->itemHeat = _itemHeat;
 }

 float getInvHeat() { return 1.0F - this->itemHeat; }

 float getMeltingTime() { return this->meltingTime; }

 void setMeltingTime(float _meltingTime) {
 if (_meltingTime > 100.0F) {
 _meltingTime = 100.0F;
 }

 if (_meltingTime < 0.0F) {
 _meltingTime = 0.0F;
 }

 this->meltingTime = _meltingTime;
 }

 std::string getWorker() { return this->worker; }

 void setWorker(std::string_view _worker) { this->worker = _worker; }

 int getID() { return this->id; }

 void setID(int itemId) { this->id = itemId; }

 bool isWet() { return this->isWet; }

 void setWet(bool _isWet) { this->isWet = _isWet; }

 float getWetCooldown() { return this->wetCooldown; }

 void setWetCooldown(float _wetCooldown) { this->wetCooldown = _wetCooldown; }

 std::string getItemWhenDry() { return this->itemWhenDry; }

 void setItemWhenDry(std::string_view _itemWhenDry) {
 this->itemWhenDry = _itemWhenDry;
 }

 bool isFavorite() { return this->favorite; }

 void setFavorite(bool _favorite) { this->favorite = _favorite; }

public
 ArrayList<String> getRequireInHandOrInventory() {
 return this->requireInHandOrInventory;
 }

 void
 setRequireInHandOrInventory(ArrayList<String> _requireInHandOrInventory) {
 this->requireInHandOrInventory = _requireInHandOrInventory;
 }

 bool isCustomColor() { return this->customColor; }

 void setCustomColor(bool _customColor) { this->customColor = _customColor; }

 void doBuildingStash() {
 if (this->stashMap != nullptr) {
 if (GameClient.bClient) {
 GameClient.sendBuildingStashToDo(this->stashMap);
 } else {
 StashSystem.prepareBuildingStash(this->stashMap);
 }
 }
 }

 void setStashMap(std::string_view _stashMap) { this->stashMap = _stashMap; }

 int getMechanicType() { return this->getScriptItem().vehicleType; }

 float getItemCapacity() { return this->itemCapacity; }

 void setItemCapacity(float capacity) { this->itemCapacity = capacity; }

 int getMaxCapacity() { return this->maxCapacity; }

 void setMaxCapacity(int _maxCapacity) { this->maxCapacity = _maxCapacity; }

 bool isConditionAffectsCapacity() {
 return this->ScriptItem != nullptr &&
 this->ScriptItem.isConditionAffectsCapacity();
 }

 float getBrakeForce() { return this->brakeForce; }

 void setBrakeForce(float _brakeForce) { this->brakeForce = _brakeForce; }

 int getChanceToSpawnDamaged() { return this->chanceToSpawnDamaged; }

 void setChanceToSpawnDamaged(int _chanceToSpawnDamaged) {
 this->chanceToSpawnDamaged = _chanceToSpawnDamaged;
 }

 float getConditionLowerNormal() { return this->conditionLowerNormal; }

 void setConditionLowerNormal(float _conditionLowerNormal) {
 this->conditionLowerNormal = _conditionLowerNormal;
 }

 float getConditionLowerOffroad() { return this->conditionLowerOffroad; }

 void setConditionLowerOffroad(float _conditionLowerOffroad) {
 this->conditionLowerOffroad = _conditionLowerOffroad;
 }

 float getWheelFriction() { return this->wheelFriction; }

 void setWheelFriction(float _wheelFriction) {
 this->wheelFriction = _wheelFriction;
 }

 float getSuspensionDamping() { return this->suspensionDamping; }

 void setSuspensionDamping(float _suspensionDamping) {
 this->suspensionDamping = _suspensionDamping;
 }

 float getSuspensionCompression() { return this->suspensionCompression; }

 void setSuspensionCompression(float _suspensionCompression) {
 this->suspensionCompression = _suspensionCompression;
 }

 void setInfected(bool infected) { this->zombieInfected = infected; }

 bool isInfected() { return this->zombieInfected; }

 float getEngineLoudness() { return this->engineLoudness; }

 void setEngineLoudness(float _engineLoudness) {
 this->engineLoudness = _engineLoudness;
 }

 std::string getStaticModel() { return this->getScriptItem().getStaticModel(); }

public
 ArrayList<String> getIconsForTexture() { return this->iconsForTexture; }

 void setIconsForTexture(ArrayList<String> _iconsForTexture) {
 this->iconsForTexture = _iconsForTexture;
 }

 float getScore(SurvivorDesc desc) { return 0.0F; }

 /**
 * @return the previousOwner
 */
 IsoGameCharacter getPreviousOwner() { return this->previousOwner; }

 /**
 *
 * @param _previousOwner the previousOwner to set
 */
 void setPreviousOwner(IsoGameCharacter _previousOwner) {
 this->previousOwner = _previousOwner;
 }

 /**
 * @return the ScriptItem
 */
 Item getScriptItem() { return this->ScriptItem; }

 /**
 *
 * @param _ScriptItem the ScriptItem to set
 */
 void setScriptItem(Item _ScriptItem) { this->ScriptItem = _ScriptItem; }

 /**
 * @return the cat
 */
 ItemType getCat() { return this->cat; }

 /**
 *
 * @param _cat the cat to set
 */
 void setCat(ItemType _cat) { this->cat = _cat; }

 /**
 * @return the container
 */
 ItemContainer getContainer() { return this->container; }

 /**
 *
 * @param _container the container to set
 */
 void setContainer(ItemContainer _container) { this->container = _container; }

public
 ArrayList<BloodClothingType> getBloodClothingType() {
 return this->bloodClothingType;
 }

 void setBloodClothingType(ArrayList<BloodClothingType> _bloodClothingType) {
 this->bloodClothingType = _bloodClothingType;
 }

 void setBlood(BloodBodyPartType bodyPartType, float amount) {
 ItemVisual itemVisual = this->getVisual();
 if (itemVisual != nullptr) {
 itemVisual.setBlood(bodyPartType, amount);
 }
 }

 float getBlood(BloodBodyPartType bodyPartType) {
 ItemVisual itemVisual = this->getVisual();
 return itemVisual != nullptr ? itemVisual.getBlood(bodyPartType) : 0.0F;
 }

 void setDirt(BloodBodyPartType bodyPartType, float amount) {
 ItemVisual itemVisual = this->getVisual();
 if (itemVisual != nullptr) {
 itemVisual.setDirt(bodyPartType, amount);
 }
 }

 float getDirt(BloodBodyPartType bodyPartType) {
 ItemVisual itemVisual = this->getVisual();
 return itemVisual != nullptr ? itemVisual.getDirt(bodyPartType) : 0.0F;
 }

 std::string getClothingItemName() {
 return this->getScriptItem().ClothingItem;
 }

 int getStashChance() { return this->stashChance; }

 void setStashChance(int _stashChance) { this->stashChance = _stashChance; }

 std::string getEatType() { return this->getScriptItem().eatType; }

 bool isUseWorldItem() { return this->getScriptItem().UseWorldItem; }

 bool isHairDye() { return this->getScriptItem().hairDye; }

 std::string getAmmoType() { return this->ammoType; }

 void setAmmoType(std::string_view _ammoType) { this->ammoType = _ammoType; }

 int getMaxAmmo() { return this->maxAmmo; }

 void setMaxAmmo(int maxAmmoCount) { this->maxAmmo = maxAmmoCount; }

 int getCurrentAmmoCount() noexcept{ return this->currentAmmoCount; }

 void setCurrentAmmoCount(int ammo) { this->currentAmmoCount = ammo; }

 std::string getGunType() { return this->gunType; }

 void setGunType(std::string_view _gunType) { this->gunType = _gunType; }

 bool hasBlood() {
 if (this instanceof Clothing) {
 if (this->getBloodClothingType() == nullptr ||
 this->getBloodClothingType().empty()) {
 return false;
 }

 std::vector arrayList =
 BloodClothingType.getCoveredParts(this->getBloodClothingType());
 if (arrayList.empty()) {
 return false;
 }

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 if (this->getBlood((BloodBodyPartType)arrayList.get(int0) > 0.0F) {
 return true;
 }
 }
 } else {
 if (this instanceof HandWeapon) {
 return ((HandWeapon)this).getBloodLevel() > 0.0F;
 }

 if (this instanceof InventoryContainer) {
 return ((InventoryContainer)this).getBloodLevel() > 0.0F;
 }
 }

 return false;
 }

 bool hasDirt() {
 if (this instanceof Clothing) {
 if (this->getBloodClothingType() == nullptr ||
 this->getBloodClothingType().empty()) {
 return false;
 }

 std::vector arrayList =
 BloodClothingType.getCoveredParts(this->getBloodClothingType());
 if (arrayList.empty()) {
 return false;
 }

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 if (this->getDirt((BloodBodyPartType)arrayList.get(int0) > 0.0F) {
 return true;
 }
 }
 }

 return false;
 }

 std::string getAttachmentType() { return this->attachmentType; }

 void setAttachmentType(std::string_view _attachmentType) {
 this->attachmentType = _attachmentType;
 }

 int getAttachedSlot() { return this->attachedSlot; }

 void setAttachedSlot(int _attachedSlot) { this->attachedSlot = _attachedSlot; }

public
 ArrayList<String> getAttachmentsProvided() {
 return this->attachmentsProvided;
 }

 void setAttachmentsProvided(ArrayList<String> _attachmentsProvided) {
 this->attachmentsProvided = _attachmentsProvided;
 }

 std::string getAttachedSlotType() { return this->attachedSlotType; }

 void setAttachedSlotType(std::string_view _attachedSlotType) {
 this->attachedSlotType = _attachedSlotType;
 }

 std::string getAttachmentReplacement() { return this->attachmentReplacement; }

 void setAttachmentReplacement(std::string_view attachementReplacement) {
 this->attachmentReplacement = attachementReplacement;
 }

 std::string getAttachedToModel() { return this->attachedToModel; }

 void setAttachedToModel(std::string_view _attachedToModel) {
 this->attachedToModel = _attachedToModel;
 }

 std::string getFabricType() { return this->getScriptItem().fabricType; }

 std::string getStringItemType() {
 Item item0 = ScriptManager.instance.FindItem(this->getFullType());
 if (item0 != nullptr && item0.getType() != nullptr) {
 if (item0.getType() == Item.Type.Food) {
 return item0.CannedFood ? "CannedFood" : "Food";
 } else if ("Ammo" == item0.getDisplayCategory())) {
 return "Ammo";
 }
 else if (item0.getType() == Item.Type.Weapon && !item0.isRanged()) {
 return "MeleeWeapon";
 } else if (item0.getType() != Item.Type.WeaponPart &&
 (item0.getType() != Item.Type.Weapon || !item0.isRanged()) &&
 (item0.getType() != Item.Type.Normal ||
 StringUtils.isNullOrEmpty(item0.getAmmoType()))) {
 if (item0.getType() == Item.Type.Literature) {
 return "Literature";
 } else if (item0.Medical) {
 return "Medical";
 } else if (item0.SurvivalGear) {
 return "SurvivalGear";
 } else {
 return item0.MechanicsItem ? "Mechanic" : "Other";
 }
 } else {
 return "RangedWeapon";
 }
 } else {
 return "Other";
 }
 }

 bool isProtectFromRainWhileEquipped() {
 return this->getScriptItem().ProtectFromRainWhenEquipped;
 }

 bool isEquippedNoSprint() { return this->getScriptItem().equippedNoSprint; }

 std::string getBodyLocation() { return this->getScriptItem().BodyLocation; }

 std::string getMakeUpType() { return this->getScriptItem().makeUpType; }

 bool isHidden() { return this->getScriptItem().isHidden(); }

 std::string getConsolidateOption() {
 return this->getScriptItem().consolidateOption;
 }

public
 ArrayList<String> getClothingItemExtra() {
 return this->getScriptItem().clothingItemExtra;
 }

public
 ArrayList<String> getClothingItemExtraOption() {
 return this->getScriptItem().clothingItemExtraOption;
 }

 std::string getWorldStaticItem() {
 return this->getModData().rawget("Flatpack") == "true"
 ? "Flatpack"
 : this->getScriptItem().worldStaticModel;
 }

 void setRegistry_id(Item itemscript) {
 if (itemscript.getFullName() == this->getFullType())) {
 this->registry_id = itemscript.getRegistry_id();
 }
 else if (Core.bDebug) {
 WorldDictionary.DebugPrintItem(itemscript);
 throw RuntimeException("These types should always match");
 }
 }

 short getRegistry_id() { return this->registry_id; }

 std::string getModID() {
 return this->ScriptItem != nullptr && this->ScriptItem.getModID() != nullptr
 ? this->ScriptItem.getModID()
 : WorldDictionary.getItemModID(this->registry_id);
 }

 std::string getModName() {
 return WorldDictionary.getModNameFromID(this->getModID());
 }

 bool isVanilla() {
 if (this->getModID() != nullptr) {
 return this->getModID() == "pz-vanilla");
 } else if (Core.bDebug) {
 WorldDictionary.DebugPrintItem(this);
 throw RuntimeException("Item has no modID?");
 } else {
 return true;
 }
 }

 short getRecordedMediaIndex() { return this->recordedMediaIndex; }

 void setRecordedMediaIndex(short _id) {
 this->recordedMediaIndex = _id;
 if (this->recordedMediaIndex >= 0) {
 MediaData mediaData =
 ZomboidRadio.getInstance().getRecordedMedia().getMediaDataFromIndex(
 this->recordedMediaIndex);
 this->mediaType = -1;
 if (mediaData != nullptr) {
 this->name = mediaData.getTranslatedItemDisplayName();
 this->mediaType = mediaData.getMediaType();
 } else {
 this->recordedMediaIndex = -1;
 }
 } else {
 this->mediaType = -1;
 this->name = this->getScriptItem().getDisplayName();
 }
 }

 void setRecordedMediaIndexInteger(int _id) {
 this->setRecordedMediaIndex((short)_id);
 }

 bool isRecordedMedia() { return this->recordedMediaIndex >= 0; }

 MediaData getMediaData() {
 return this->isRecordedMedia()
 ? ZomboidRadio.getInstance()
 .getRecordedMedia()
 .getMediaDataFromIndex(this->recordedMediaIndex)
 : nullptr;
 }

 uint8_t getMediaType() { return this->mediaType; }

 void setMediaType(uint8_t b) { this->mediaType = b; }

 void setRecordedMediaData(MediaData data) {
 if (data != nullptr && data.getIndex() >= 0) {
 this->setRecordedMediaIndex(data.getIndex());
 }
 }

 void setWorldZRotation(int rot) { this->worldZRotation = rot; }

 void setWorldScale(float scale) { this->worldScale = scale; }

 std::string getLuaCreate() { return this->getScriptItem().getLuaCreate(); }

 bool isInitialised() { return this->isInitialised; }

 void setInitialised(bool initialised) { this->isInitialised = initialised; }

 void initialiseItem() {
 this->setInitialised(true);
 if (this->getLuaCreate() != nullptr) {
 void *object = LuaManager.getFunctionObject(this->getLuaCreate());
 if (object != nullptr) {
 LuaManager.caller.protectedCallVoid(LuaManager.thread, object, this);
 }
 }
 }

 std::string getSoundParameter(std::string_view parameterName) {
 return this->getScriptItem().getSoundParameter(parameterName);
 }
}
} // namespace inventory
} // namespace zombie
