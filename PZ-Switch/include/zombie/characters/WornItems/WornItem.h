#pragma once
#include "zombie/inventory/InventoryItem.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
namespace WornItems {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WornItem {
public:
 const std::string location;
 const InventoryItem item;

public
 WornItem(const std::string &_location, InventoryItem _item) {
 if (_location.empty()) {
 throw NullPointerException("location is nullptr");
 } else if (_location.empty()) {
 throw IllegalArgumentException("location is empty");
 } else if (_item.empty()) {
 throw NullPointerException("item is nullptr");
 } else {
 this->location = _location;
 this->item = _item;
 }
 }

 std::string getLocation() { return this->location; }

 InventoryItem getItem() { return this->item; }
}
} // namespace WornItems
} // namespace characters
} // namespace zombie
