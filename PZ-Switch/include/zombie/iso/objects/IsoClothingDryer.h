#pragma once
#include "se/krka/kahlua/vm/KahluaTable.h"
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
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IsoClothingDryer : public IsoObject {
public:
 const ClothingDryerLogic m_logic = new ClothingDryerLogic(this);

public
 IsoClothingDryer(IsoCell cell) { super(cell); }

public
 IsoClothingDryer(IsoCell cell, IsoGridSquare sq, IsoSprite gid) {
 super(cell, sq, gid);
 }

 std::string getObjectName() { return "ClothingDryer"; }

 void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 super.load(input, WorldVersion, IS_DEBUG_SAVE);
 this->m_logic.load(input, WorldVersion, IS_DEBUG_SAVE);
 }

 void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 super.save(output, IS_DEBUG_SAVE);
 this->m_logic.save(output, IS_DEBUG_SAVE);
 }

 void update() { this->m_logic.update(); }

 void addToWorld() {
 IsoCell cell = this->getCell();
 cell.addToProcessIsoObject(this);
 }

 void removeFromWorld() { super.removeFromWorld(); }

 void saveChange(std::string_view change, KahluaTable tbl, ByteBuffer bb) {
 this->m_logic.saveChange(change, tbl, bb);
 }

 void loadChange(std::string_view change, ByteBuffer bb) {
 this->m_logic.loadChange(change, bb);
 }

 bool isItemAllowedInContainer(ItemContainer container, InventoryItem item) {
 return this->m_logic.isItemAllowedInContainer(container, item);
 }

 bool isRemoveItemAllowedFromContainer(ItemContainer container,
 InventoryItem item) {
 return this->m_logic.isRemoveItemAllowedFromContainer(container, item);
 }

 bool isActivated() { return this->m_logic.isActivated(); }

 void setActivated(bool activated) { this->m_logic.setActivated(activated); }
}
} // namespace objects
} // namespace iso
} // namespace zombie
