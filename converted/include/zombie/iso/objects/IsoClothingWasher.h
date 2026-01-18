#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoClothingWasher : public IsoObject {
public:
 const ClothingWasherLogic m_logic = new ClothingWasherLogic(this);

 public IsoClothingWasher(IsoCell cell) {
 super(cell);
 }

 public IsoClothingWasher(IsoCell cell, IsoGridSquare sq, IsoSprite gid) {
 super(cell, sq, gid);
 }

 std::string getObjectName() {
 return "ClothingWasher";
 }

 void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 super.load(input, WorldVersion, IS_DEBUG_SAVE);
 this->m_logic.load(input, WorldVersion, IS_DEBUG_SAVE);
 }

 void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 super.save(output, IS_DEBUG_SAVE);
 this->m_logic.save(output, IS_DEBUG_SAVE);
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
 this->m_logic.saveChange(change, tbl, bb);
 }

 void loadChange(const std::string& change, ByteBuffer bb) {
 this->m_logic.loadChange(change, bb);
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
}
} // namespace objects
} // namespace iso
} // namespace zombie
