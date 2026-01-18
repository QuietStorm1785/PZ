#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/objects/interfaces/IClothingWasherDryerLogic.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoCombinationWasherDryer : public IsoObject {
public:
 const ClothingWasherLogic m_washer = new ClothingWasherLogic(this);
 const ClothingDryerLogic m_dryer = new ClothingDryerLogic(this);
 IClothingWasherDryerLogic m_logic = this->m_washer;

 public IsoCombinationWasherDryer(IsoCell cell) {
 super(cell);
 }

 public IsoCombinationWasherDryer(IsoCell cell, IsoGridSquare sq, IsoSprite gid) {
 super(cell, sq, gid);
 }

 std::string getObjectName() {
 return "CombinationWasherDryer";
 }

 void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 super.load(input, WorldVersion, IS_DEBUG_SAVE);
 this->m_logic = (IClothingWasherDryerLogic)(input.get() == 0 ? this->m_washer : this->m_dryer);
 this->m_washer.load(input, WorldVersion, IS_DEBUG_SAVE);
 this->m_dryer.load(input, WorldVersion, IS_DEBUG_SAVE);
 }

 void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 super.save(output, IS_DEBUG_SAVE);
 output.put((byte)(this->m_logic == this->m_washer ? 0 : 1);
 this->m_washer.save(output, IS_DEBUG_SAVE);
 this->m_dryer.save(output, IS_DEBUG_SAVE);
 }

 void update() {
 this->m_logic.update();
 }

 void addToWorld() {
 IsoCell cell = this->getCell();
 cell.addToProcessIsoObject(this);
 }

 void removeFromWorld() {
 super.removeFromWorld();
 }

 void saveChange(const std::string& change, KahluaTable tbl, ByteBuffer bb) {
 if ("mode" == change) {
 bb.put((byte)(this->isModeWasher() ? 0 : 1);
 } else {
 this->m_logic.saveChange(change, tbl, bb);
 }
 }

 void loadChange(const std::string& change, ByteBuffer bb) {
 if ("mode" == change) {
 if (bb.get() == 0) {
 this->setModeWasher();
 } else {
 this->setModeDryer();
 }
 } else {
 this->m_logic.loadChange(change, bb);
 }
 }

 bool isItemAllowedInContainer(ItemContainer container, InventoryItem item) {
 return this->m_logic.isItemAllowedInContainer(container, item);
 }

 bool isRemoveItemAllowedFromContainer(ItemContainer container, InventoryItem item) {
 return this->m_logic.isRemoveItemAllowedFromContainer(container, item);
 }

 bool isActivated() {
 return this->m_logic.isActivated();
 }

 void setActivated(bool activated) {
 this->m_logic.setActivated(activated);
 }

 void setModeWasher() {
 if (!this->isModeWasher()) {
 this->m_dryer.switchModeOff();
 this->m_logic = this->m_washer;
 this->getContainer().setType("clothingwasher");
 this->m_washer.switchModeOn();
 LuaEventManager.triggerEvent("OnContainerUpdate");
 }
 }

 void setModeDryer() {
 if (!this->isModeDryer()) {
 this->m_washer.switchModeOff();
 this->m_logic = this->m_dryer;
 this->getContainer().setType("clothingdryer");
 this->m_dryer.switchModeOn();
 LuaEventManager.triggerEvent("OnContainerUpdate");
 }
 }

 bool isModeWasher() {
 return this->m_logic == this->m_washer;
 }

 bool isModeDryer() {
 return this->m_logic == this->m_dryer;
 }
}
} // namespace objects
} // namespace iso
} // namespace zombie
