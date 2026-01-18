#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemType.h"
#include "zombie/scripting/objects/Item.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace inventory {
namespace types {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Key : public InventoryItem {
public:
 int keyId = -1;
 bool padlock = false;
 int numberOfKey = 0;
 bool digitalPadlock = false;
 public static Key[] highlightDoor = new Key[4];

 public Key(const std::string& module, const std::string& name, const std::string& type, const std::string& tex) {
 super(module, name, type, tex);
 this->cat = ItemType.Key;
 }

 int getSaveType() {
 return Item.Type.Key.ordinal();
 }

 /**
 * Get the key number of the building and set it to the key
 */
 void takeKeyId() {
 if (this->getContainer() != nullptr
 && this->getContainer().getSourceGrid() != nullptr
 && this->getContainer().getSourceGrid().getBuilding() != nullptr
 && this->getContainer().getSourceGrid().getBuilding().def != nullptr) {
 this->setKeyId(this->getContainer().getSourceGrid().getBuilding().def.getKeyId());
 }
 }

 static void setHighlightDoors(int playerNum, InventoryItem item) {
 if (item instanceof Key && !((Key)item).isPadlock() && !((Key)item).isDigitalPadlock()) {
 highlightDoor[playerNum] = (Key)item;
 } else {
 highlightDoor[playerNum] = nullptr;
 }
 }

 int getKeyId() {
 return this->keyId;
 }

 void setKeyId(int _keyId) {
 this->keyId = _keyId;
 }

 std::string getCategory() {
 return this->mainCategory != nullptr ? this->mainCategory : "Key";
 }

 void save(ByteBuffer output, bool net) {
 super.save(output, net);
 output.putInt(this->getKeyId());
 output.put((byte)this->numberOfKey);
 }

 void load(ByteBuffer input, int WorldVersion) {
 super.load(input, WorldVersion);
 this->setKeyId(input.getInt());
 this->numberOfKey = input.get();
 }

 bool isPadlock() {
 return this->padlock;
 }

 void setPadlock(bool _padlock) {
 this->padlock = _padlock;
 }

 int getNumberOfKey() {
 return this->numberOfKey;
 }

 void setNumberOfKey(int _numberOfKey) {
 this->numberOfKey = _numberOfKey;
 }

 bool isDigitalPadlock() {
 return this->digitalPadlock;
 }

 void setDigitalPadlock(bool _digitalPadlock) {
 this->digitalPadlock = _digitalPadlock;
 }
}
} // namespace types
} // namespace inventory
} // namespace zombie
