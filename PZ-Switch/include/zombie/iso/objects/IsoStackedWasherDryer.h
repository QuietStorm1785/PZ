#pragma once
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/sprite/IsoSprite.h"
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
namespace iso {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IsoStackedWasherDryer : public IsoObject {
public:
 const ClothingWasherLogic m_washer = new ClothingWasherLogic(this);
 const ClothingDryerLogic m_dryer = new ClothingDryerLogic(this);

public
 IsoStackedWasherDryer(IsoCell cell) { super(cell); }

public
 IsoStackedWasherDryer(IsoCell cell, IsoGridSquare sq, IsoSprite gid) {
 super(cell, sq, gid);
 }

 std::string getObjectName() { return "StackedWasherDryer"; }

 void createContainersFromSpriteProperties() {
 super.createContainersFromSpriteProperties();
 PropertyContainer propertyContainer = this->getProperties();
 if (propertyContainer != nullptr) {
 if (this->getContainerByType("clothingwasher") == nullptr) {
 ItemContainer container0 =
 new ItemContainer("clothingwasher", this->getSquare(), this);
 if (propertyContainer.Is("ContainerCapacity")) {
 container0.Capacity = PZMath.tryParseInt(
 propertyContainer.Val("ContainerCapacity"), 20);
 }

 if (this->getContainer() == nullptr) {
 this->setContainer(container0);
 } else {
 this->addSecondaryContainer(container0);
 }
 }

 if (this->getContainerByType("clothingdryer") == nullptr) {
 ItemContainer container1 =
 new ItemContainer("clothingdryer", this->getSquare(), this);
 if (propertyContainer.Is("ContainerCapacity")) {
 container1.Capacity = PZMath.tryParseInt(
 propertyContainer.Val("ContainerCapacity"), 20);
 }

 if (this->getContainer() == nullptr) {
 this->setContainer(container1);
 } else {
 this->addSecondaryContainer(container1);
 }
 }
 }
 }

 void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 super.load(input, WorldVersion, IS_DEBUG_SAVE);
 this->m_washer.load(input, WorldVersion, IS_DEBUG_SAVE);
 this->m_dryer.load(input, WorldVersion, IS_DEBUG_SAVE);
 }

 void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 super.save(output, IS_DEBUG_SAVE);
 this->m_washer.save(output, IS_DEBUG_SAVE);
 this->m_dryer.save(output, IS_DEBUG_SAVE);
 }

 void update() {
 this->m_washer.update();
 this->m_dryer.update();
 }

 void addToWorld() {
 IsoCell cell = this->getCell();
 cell.addToProcessIsoObject(this);
 }

 void removeFromWorld() { super.removeFromWorld(); }

 void saveChange(const std::string &change, KahluaTable tbl, ByteBuffer bb) {
 this->m_washer.saveChange(change, tbl, bb);
 this->m_dryer.saveChange(change, tbl, bb);
 }

 void loadChange(const std::string &change, ByteBuffer bb) {
 this->m_washer.loadChange(change, bb);
 this->m_dryer.loadChange(change, bb);
 }

 bool isItemAllowedInContainer(ItemContainer container, InventoryItem item) {
 return this->m_washer.isItemAllowedInContainer(container, item) ||
 this->m_dryer.isItemAllowedInContainer(container, item);
 }

 bool isRemoveItemAllowedFromContainer(ItemContainer container,
 InventoryItem item) {
 return this->m_washer.isRemoveItemAllowedFromContainer(container, item) ||
 this->m_dryer.isRemoveItemAllowedFromContainer(container, item);
 }

 bool isWasherActivated() { return this->m_washer.isActivated(); }

 void setWasherActivated(bool activated) {
 this->m_washer.setActivated(activated);
 }

 bool isDryerActivated() { return this->m_dryer.isActivated(); }

 void setDryerActivated(bool activated) {
 this->m_dryer.setActivated(activated);
 }
}
} // namespace objects
} // namespace iso
} // namespace zombie
