#pragma once
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characterTextures/BloodClothingType.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/Translator.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/ui/ObjectTooltip.h"
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
namespace inventory {
namespace types {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class InventoryContainer : public InventoryItem {
public:
 ItemContainer container = std::make_unique<ItemContainer>();
 int capacity = 0;
 int weightReduction = 0;
 std::string CanBeEquipped = "";

public
 InventoryContainer(const std::string &module, const std::string &name,
 const std::string &itemType, const std::string &texName) {
 super(module, name, itemType, texName);
 this->container.containingItem = this;
 this->container.type = itemType;
 this->container.inventoryContainer = this;
 }

 bool IsInventoryContainer() { return true; }

 int getSaveType() { return Item.Type.Container.ordinal(); }

 std::string getCategory() {
 return this->mainCategory != nullptr ? this->mainCategory : "Container";
 }

 ItemContainer getInventory() { return this->container; }

 void save(ByteBuffer output, bool net) {
 super.save(output, net);
 output.putInt(this->container.ID);
 output.putInt(this->weightReduction);
 this->container.save(output);
 }

 void load(ByteBuffer input, int WorldVersion) {
 super.load(input, WorldVersion);
 int int0 = input.getInt();
 this->setWeightReduction(input.getInt());
 if (this->container.empty()) {
 this->container = std::make_unique<ItemContainer>();
 }

 this->container.clear();
 this->container.containingItem = this;
 this->container.setWeightReduction(this->weightReduction);
 this->container.Capacity = this->capacity;
 this->container.ID = int0;
 this->container.load(input, WorldVersion);
 this->synchWithVisual();
 }

 int getCapacity() { return this->container.getCapacity(); }

 void setCapacity(int _capacity) {
 this->capacity = _capacity;
 if (this->container.empty()) {
 this->container = std::make_unique<ItemContainer>();
 }

 this->container.Capacity = _capacity;
 }

 float getInventoryWeight() {
 if (this->getInventory() == nullptr) {
 return 0.0F;
 } else {
 float float0 = 0.0F;
 std::vector arrayList = this->getInventory().getItems();

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 InventoryItem item = (InventoryItem)arrayList.get(int0);
 if (this->isEquipped()) {
 float0 += item.getEquippedWeight();
 } else {
 float0 += item.getUnequippedWeight();
 }
 }

 return float0;
 }
 }

 int getEffectiveCapacity(IsoGameCharacter chr) {
 return this->container.getEffectiveCapacity(chr);
 }

 int getWeightReduction() { return this->weightReduction; }

 void setWeightReduction(int _weightReduction) {
 _weightReduction = Math.min(_weightReduction, 100);
 _weightReduction = Math.max(_weightReduction, 0);
 this->weightReduction = _weightReduction;
 this->container.setWeightReduction(_weightReduction);
 }

 void updateAge() {
 std::vector arrayList = this->getInventory().getItems();

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 ((InventoryItem)arrayList.get(int0).updateAge();
 }
 }

 void DoTooltip(ObjectTooltip tooltipUI) {
 tooltipUI.render();
 super.DoTooltip(tooltipUI);
 int int0 = tooltipUI.getHeight().intValue();
 int0 -= tooltipUI.padBottom;
 if (tooltipUI.getWidth() < 160.0) {
 tooltipUI.setWidth(160.0);
 }

 if (!this->getItemContainer().getItems().empty()) {
 uint8_t byte0 = 5;
 int0 += 4;
 std::unordered_set hashSet = new HashSet();

 for (int int1 = this->getItemContainer().getItems().size() - 1; int1 >= 0;
 int1--) {
 InventoryItem item = this->getItemContainer().getItems().get(int1);
 if (item.getName() != nullptr) {
 if (hashSet.contains(item.getName())) {
 continue;
 }

 hashSet.add(item.getName());
 }

 tooltipUI.DrawTextureScaledAspect(item.getTex(), byte0, int0, 16.0,
 16.0, 1.0, 1.0, 1.0, 1.0);
 byte0 += 17;
 if (byte0 + 16 > tooltipUI.width - tooltipUI.padRight) {
 break;
 }
 }

 int0 += 16;
 }

 int0 += tooltipUI.padBottom;
 tooltipUI.setHeight(int0);
 }

 void DoTooltip(ObjectTooltip tooltipUI, ObjectTooltip.Layout layout) {
 float float0 = 0.0F;
 float float1 = 0.6F;
 float float2 = 0.0F;
 float float3 = 0.7F;
 if (this->getEffectiveCapacity(tooltipUI.getCharacter()) != 0) {
 ObjectTooltip.LayoutItem layoutItem0 = layout.addItem();
 layoutItem0.setLabel(Translator.getText("Tooltip_container_Capacity") +
 ":",
 1.0F, 1.0F, 1.0F, 1.0F);
 layoutItem0.setValueRightNoPlus(
 this->getEffectiveCapacity(tooltipUI.getCharacter()));
 }

 if (this->getWeightReduction() != 0) {
 ObjectTooltip.LayoutItem layoutItem1 = layout.addItem();
 layoutItem1.setLabel(
 Translator.getText("Tooltip_container_Weight_Reduction") + ":", 1.0F,
 1.0F, 1.0F, 1.0F);
 layoutItem1.setValueRightNoPlus(this->getWeightReduction());
 }

 if (this->getBloodClothingType() != nullptr) {
 float float4 = this->getBloodLevel();
 if (float4 != 0.0F) {
 ObjectTooltip.LayoutItem layoutItem2 = layout.addItem();
 layoutItem2.setLabel(Translator.getText("Tooltip_clothing_bloody") +
 ":",
 1.0F, 1.0F, 0.8F, 1.0F);
 layoutItem2.setProgress(float4, float0, float1, float2, float3);
 }
 }
 }

 void setBloodLevel(float delta) {
 std::vector arrayList =
 BloodClothingType.getCoveredParts(this->getBloodClothingType());

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 this->setBlood((BloodBodyPartType)arrayList.get(int0),
 PZMath.clamp(delta, 0.0F, 100.0F);
 }
 }

 float getBloodLevel() {
 std::vector arrayList =
 BloodClothingType.getCoveredParts(this->getBloodClothingType());
 float float0 = 0.0F;

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 float0 += this->getBlood((BloodBodyPartType)arrayList.get(int0);
 }

 return float0;
 }

 void setCanBeEquipped(const std::string &canBeEquipped) {
 this->CanBeEquipped = canBeEquipped.empty() ? "" : canBeEquipped;
 }

 std::string canBeEquipped() { return this->CanBeEquipped; }

 ItemContainer getItemContainer() { return this->container; }

 void setItemContainer(ItemContainer cont) { this->container = cont; }

 float getContentsWeight() { return this->getInventory().getContentsWeight(); }

 float getEquippedWeight() {
 float float0 = 1.0F;
 if (this->getWeightReduction() > 0) {
 float0 = 1.0F - this->getWeightReduction() / 100.0F;
 }

 return this->getActualWeight() * 0.3F + this->getContentsWeight() * float0;
 }

 std::string getClothingExtraSubmenu() {
 return this->ScriptItem.clothingExtraSubmenu;
 }
}
} // namespace types
} // namespace inventory
} // namespace zombie
