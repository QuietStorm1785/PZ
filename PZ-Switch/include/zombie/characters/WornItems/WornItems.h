#pragma once
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/Clothing.h"
#include "zombie/inventory/types/InventoryContainer.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>
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

class WornItems {
public:
 const BodyLocationGroup group;
protected
 ArrayList<WornItem> items = std::make_unique<ArrayList<>>();

public
 WornItems(BodyLocationGroup _group) { this->group = _group; }

public
 WornItems(WornItems other) {
 this->group = other.group;
 this->copyFrom(other);
 }

 void copyFrom(WornItems other) {
 if (this->group != other.group) {
 throw RuntimeException("group=" + this->group.id +
 " other.group=" + other.group.id);
 } else {
 this->items.clear();
 this->items.addAll(other.items);
 }
 }

 BodyLocationGroup getBodyLocationGroup() { return this->group; }

 WornItem get(int index) { return this->items.get(index); }

 void setItem(const std::string &location, InventoryItem item) {
 this->group.checkValid(location);
 if (!this->group.isMultiItem(location) {
 int int0 = this->indexOf(location);
 if (int0 != -1) {
 this->items.remove(int0);
 }
 }

 for (int int1 = 0; int1 < this->items.size(); int1++) {
 WornItem wornItem0 = this->items.get(int1);
 if (this->group.isExclusive(location, wornItem0.location) {
 this->items.remove(int1--);
 }
 }

 if (item != nullptr) {
 this->remove(item);
 int int2 = this->items.size();

 for (int int3 = 0; int3 < this->items.size(); int3++) {
 WornItem wornItem1 = this->items.get(int3);
 if (this->group.indexOf(wornItem1.getLocation()) >
 this->group.indexOf(location) {
 int2 = int3;
 break;
 }
 }

 WornItem wornItem2 = new WornItem(location, item);
 this->items.add(int2, wornItem2);
 }
 }

 InventoryItem getItem(const std::string &location) {
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

 void forEach(Consumer<WornItem> c) {
 for (int int0 = 0; int0 < this->items.size(); int0++) {
 c.accept(this->items.get(int0);
 }
 }

 void setFromItemVisuals(ItemVisuals itemVisuals) {
 this->clear();

 for (int int0 = 0; int0 < itemVisuals.size(); int0++) {
 ItemVisual itemVisual = itemVisuals.get(int0);
 std::string string = itemVisual.getItemType();
 InventoryItem item = InventoryItemFactory.CreateItem(string);
 if (item != nullptr) {
 if (item.getVisual() != nullptr) {
 item.getVisual().copyFrom(itemVisual);
 item.synchWithVisual();
 }

 if (item instanceof Clothing && !StringUtils.isNullOrWhitespace(
 item.getBodyLocation())) {
 this->setItem(item.getBodyLocation(), item);
 } else if (item instanceof
 InventoryContainer &&
 !StringUtils.isNullOrWhitespace(
 ((InventoryContainer)item).canBeEquipped())) {
 this->setItem(((InventoryContainer)item).canBeEquipped(), item);
 }
 }
 }
 }

 void getItemVisuals(ItemVisuals itemVisuals) {
 itemVisuals.clear();

 for (int int0 = 0; int0 < this->items.size(); int0++) {
 InventoryItem item = this->items.get(int0).getItem();
 ItemVisual itemVisual = item.getVisual();
 if (itemVisual != nullptr) {
 itemVisual.setInventoryItem(item);
 itemVisuals.add(itemVisual);
 }
 }
 }

 void addItemsToItemContainer(ItemContainer container) {
 for (int int0 = 0; int0 < this->items.size(); int0++) {
 InventoryItem item = this->items.get(int0).getItem();
 int int1 = item.getVisual().getHolesNumber();
 item.setCondition(item.getConditionMax() - int1 * 3);
 container.AddItem(item);
 }
 }

 int indexOf(const std::string &string) {
 for (int int0 = 0; int0 < this->items.size(); int0++) {
 WornItem wornItem = this->items.get(int0);
 if (wornItem.location == string) {
 return int0;
 }
 }

 return -1;
 }

 int indexOf(InventoryItem item) {
 for (int int0 = 0; int0 < this->items.size(); int0++) {
 WornItem wornItem = this->items.get(int0);
 if (wornItem.getItem() == item) {
 return int0;
 }
 }

 return -1;
 }
}
} // namespace WornItems
} // namespace characters
} // namespace zombie
