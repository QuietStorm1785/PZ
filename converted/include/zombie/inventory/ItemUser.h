#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/inventory/types/Clothing.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoMannequin.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/network/GameClient.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/VehiclePart.h"

namespace zombie {
namespace inventory {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ItemUser {
public:
 private static ArrayList<InventoryItem> tempItems = std::make_unique<ArrayList<>>();

 static void UseItem(InventoryItem item0) {
 DrainableComboItem drainableComboItem = Type.tryCastTo(item0, DrainableComboItem.class);
 if (drainableComboItem != nullptr) {
 drainableComboItem.setDelta(drainableComboItem.getDelta() - drainableComboItem.getUseDelta());
 if (drainableComboItem.uses > 1) {
 int int0 = drainableComboItem.uses - 1;
 drainableComboItem.uses = 1;
 CreateItem(drainableComboItem.getFullType(), tempItems);
 uint8_t byte0 = 0;
 if (byte0 < tempItems.size()) {
 InventoryItem item1 = tempItems.get(byte0);
 item1.setUses(int0);
 AddItem(drainableComboItem, item1);
 }
 }

 if (drainableComboItem.getDelta() <= 1.0E-4F) {
 drainableComboItem.setDelta(0.0F);
 if (drainableComboItem.getReplaceOnDeplete() == nullptr) {
 UseItem(drainableComboItem, false, false);
 } else {
 std::string string = drainableComboItem.getReplaceOnDepleteFullType();
 CreateItem(string, tempItems);

 for (int int1 = 0; int1 < tempItems.size(); int1++) {
 InventoryItem item2 = tempItems.get(int1);
 item2.setFavorite(drainableComboItem.isFavorite());
 AddItem(drainableComboItem, item2);
 }

 RemoveItem(drainableComboItem);
 }
 }

 drainableComboItem.updateWeight();
 } else {
 UseItem(item0, false, false);
 }
 }

 static void UseItem(InventoryItem item0, bool boolean0, bool boolean1) {
 if (item0.isDisappearOnUse() || boolean0) {
 item0.uses--;
 if (item0.replaceOnUse != nullptr && !boolean1 && !boolean0) {
 std::string string = item0.replaceOnUse;
 if (!string.contains(".")) {
 string = item0.module + "." + string;
 }

 CreateItem(string, tempItems);

 for (int int0 = 0; int0 < tempItems.size(); int0++) {
 InventoryItem item1 = tempItems.get(int0);
 item1.setConditionFromModData(item0);
 AddItem(item0, item1);
 item1.setFavorite(item0.isFavorite());
 }
 }

 if (item0.uses <= 0) {
 if (item0.keepOnDeplete) {
 return;
 }

 RemoveItem(item0);
 } else if (GameClient.bClient && !item0.isInPlayerInventory()) {
 GameClient.instance.sendItemStats(item0);
 }
 }
 }

 static void CreateItem(const std::string& string, ArrayList<InventoryItem> arrayList) {
 arrayList.clear();
 Item item0 = ScriptManager.instance.FindItem(string);
 if (item0.empty()) {
 DebugLog.General.warn("ERROR: ItemUses.CreateItem: can't find " + string);
 } else {
 int int0 = item0.getCount();

 for (int int1 = 0; int1 < int0; int1++) {
 InventoryItem item1 = InventoryItemFactory.CreateItem(string);
 if (item1.empty()) {
 return;
 }

 arrayList.add(item1);
 }
 }
 }

 static void AddItem(InventoryItem item0, InventoryItem item1) {
 IsoWorldInventoryObject worldInventoryObject = item0.getWorldItem();
 if (worldInventoryObject != nullptr && worldInventoryObject.getWorldObjectIndex() == -1) {
 worldInventoryObject = nullptr;
 }

 if (worldInventoryObject != nullptr) {
 worldInventoryObject.getSquare().AddWorldInventoryItem(item1, 0.0F, 0.0F, 0.0F, true);
 } else {
 if (item0.container != nullptr) {
 VehiclePart part = item0.container.vehiclePart;
 if (!item0.isInPlayerInventory() && GameClient.bClient) {
 item0.container.addItemOnServer(item1);
 }

 item0.container.AddItem(item1);
 if (part != nullptr) {
 part.setContainerContentAmount(part.getItemContainer().getCapacityWeight());
 }
 }
 }
 }

 static void RemoveItem(InventoryItem item) {
 IsoWorldInventoryObject worldInventoryObject = item.getWorldItem();
 if (worldInventoryObject != nullptr && worldInventoryObject.getWorldObjectIndex() == -1) {
 worldInventoryObject = nullptr;
 }

 if (worldInventoryObject != nullptr) {
 worldInventoryObject.getSquare().transmitRemoveItemFromSquare(worldInventoryObject);
 if (item.container != nullptr) {
 item.container.Items.remove(item);
 item.container.setDirty(true);
 item.container.setDrawDirty(true);
 item.container = nullptr;
 }
 } else {
 if (item.container != nullptr) {
 IsoObject object = item.container.parent;
 VehiclePart part = item.container.vehiclePart;
 if (object instanceof IsoGameCharacter character) {
 if (item instanceof Clothing) {
 ((Clothing)item).Unwear();
 }

 character.removeFromHands(item);
 if (character.getClothingItem_Back() == item) {
 character.setClothingItem_Back(nullptr);
 }
 } else if (!item.isInPlayerInventory() && GameClient.bClient) {
 item.container.removeItemOnServer(item);
 }

 item.container.Items.remove(item);
 item.container.setDirty(true);
 item.container.setDrawDirty(true);
 item.container = nullptr;
 if (object instanceof IsoDeadBody) {
 ((IsoDeadBody)object).checkClothing(item);
 }

 if (object instanceof IsoMannequin) {
 ((IsoMannequin)object).checkClothing(item);
 }

 if (part != nullptr) {
 part.setContainerContentAmount(part.getItemContainer().getCapacityWeight());
 }
 }
 }
 }
}
} // namespace inventory
} // namespace zombie
