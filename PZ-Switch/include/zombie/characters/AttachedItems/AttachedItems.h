#pragma once
#include "zombie/inventory/InventoryItem.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
namespace AttachedItems {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AttachedItems {
public:
 const AttachedLocationGroup group;
protected
 ArrayList<AttachedItem> items = std::make_unique<ArrayList<>>();

public
 AttachedItems(AttachedLocationGroup _group) { this->group = _group; }

public
 AttachedItems(AttachedItems other) {
 this->group = other.group;
 this->copyFrom(other);
 }

 void copyFrom(AttachedItems other) {
 if (this->group != other.group) {
 throw RuntimeException("group=" + this->group.id +
 " other.group=" + other.group.id);
 } else {
 this->items.clear();
 this->items.addAll(other.items);
 }
 }

 AttachedLocationGroup getGroup() { return this->group; }

 AttachedItem get(int index) { return this->items.get(index); }

 void setItem(std::string_view location, InventoryItem item) {
 this->group.checkValid(location);
 int int0 = this->indexOf(location);
 if (int0 != -1) {
 this->items.remove(int0);
 }

 if (item != nullptr) {
 this->remove(item);
 int int1 = this->items.size();

 for (int int2 = 0; int2 < this->items.size(); int2++) {
 AttachedItem attachedItem0 = this->items.get(int2);
 if (this->group.indexOf(attachedItem0.getLocation()) >
 this->group.indexOf(location) {
 int1 = int2;
 break;
 }
 }

 AttachedItem attachedItem1 = new AttachedItem(location, item);
 this->items.add(int1, attachedItem1);
 }
 }

 InventoryItem getItem(std::string_view location) {
 this->group.checkValid(location);
 int int0 = this->indexOf(location);
 return int0 = = -1 ? nullptr : this->items.get(int0).item;
 }

 InventoryItem getItemByIndex(int index) {
 return index >= 0 && index < this->items.size()
 ? this->items.get(index).getItem()
 : nullptr;
 }

 void remove(InventoryItem item) {
 int int0 = this->indexOf(item);
 if (int0 != -1) {
 this->items.remove(int0);
 }
 }

 void clear() { this->items.clear(); }

 std::string getLocation(InventoryItem item) {
 int int0 = this->indexOf(item);
 return int0 = = -1 ? nullptr : this->items.get(int0).getLocation();
 }

 bool contains(InventoryItem item) { return this->indexOf(item) != -1; }

 int size() { return this->items.size(); }

 bool isEmpty() { return this->items.empty(); }

 void forEach(Consumer<AttachedItem> c) {
 for (int int0 = 0; int0 < this->items.size(); int0++) {
 c.accept(this->items.get(int0);
 }
 }

 int indexOf(std::string_view string) {
 for (int int0 = 0; int0 < this->items.size(); int0++) {
 AttachedItem attachedItem = this->items.get(int0);
 if (attachedItem.location == string) {
 return int0;
 }
 }

 return -1;
 }

 int indexOf(InventoryItem item) {
 for (int int0 = 0; int0 < this->items.size(); int0++) {
 AttachedItem attachedItem = this->items.get(int0);
 if (attachedItem.getItem() == item) {
 return int0;
 }
 }

 return -1;
 }
}
} // namespace AttachedItems
} // namespace characters
} // namespace zombie
