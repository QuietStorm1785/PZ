#pragma once
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/iso/IsoWorld.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace inventory {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ItemSoundManager {
public:
private
 static ArrayList<InventoryItem> items = std::make_unique<ArrayList<>>();
private
 static ArrayList<BaseSoundEmitter> emitters =
 std::make_unique<ArrayList<>>();
private
 static ArrayList<InventoryItem> toAdd = std::make_unique<ArrayList<>>();
private
 static ArrayList<InventoryItem> toRemove =
 std::make_unique<ArrayList<>>();
private
 static ArrayList<InventoryItem> toStopItems =
 std::make_unique<ArrayList<>>();
private
 static ArrayList<BaseSoundEmitter> toStopEmitters =
 std::make_unique<ArrayList<>>();

 static void addItem(InventoryItem item) {
 if (item != nullptr && !items.contains(item) {
 toRemove.remove(item);
 int int0 = toStopItems.indexOf(item);
 if (int0 != -1) {
 toStopItems.remove(int0);
 BaseSoundEmitter baseSoundEmitter = toStopEmitters.remove(int0);
 items.add(item);
 emitters.add(baseSoundEmitter);
 } else if (!toAdd.contains(item) {
 toAdd.add(item);
 }
 }
 }

 static void removeItem(InventoryItem item) {
 toAdd.remove(item);
 int int0 = items.indexOf(item);
 if (item != nullptr && int0 != -1) {
 if (!toRemove.contains(item) {
 toRemove.add(item);
 }
 }
 }

 static void removeItems(ArrayList<InventoryItem> arrayList) {
 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 removeItem((InventoryItem)arrayList.get(int0);
 }
 }

 static void update() {
 if (!toStopItems.empty()) {
 for (int int0 = 0; int0 < toStopItems.size(); int0++) {
 BaseSoundEmitter baseSoundEmitter0 = toStopEmitters.get(int0);
 baseSoundEmitter0.stopAll();
 IsoWorld.instance.returnOwnershipOfEmitter(baseSoundEmitter0);
 }

 toStopItems.clear();
 toStopEmitters.clear();
 }

 if (!toAdd.empty()) {
 for (int int1 = 0; int1 < toAdd.size(); int1++) {
 InventoryItem item0 = toAdd.get(int1);

 assert !items.contains(item0);

 items.add(item0);
 BaseSoundEmitter baseSoundEmitter1 = IsoWorld.instance.getFreeEmitter();
 IsoWorld.instance.takeOwnershipOfEmitter(baseSoundEmitter1);
 emitters.add(baseSoundEmitter1);
 }

 toAdd.clear();
 }

 if (!toRemove.empty()) {
 for (int int2 = 0; int2 < toRemove.size(); int2++) {
 InventoryItem item1 = toRemove.get(int2);

 assert items.contains(item1);

 int int3 = items.indexOf(item1);
 items.remove(int3);
 BaseSoundEmitter baseSoundEmitter2 = emitters.get(int3);
 emitters.remove(int3);
 toStopItems.add(item1);
 toStopEmitters.add(baseSoundEmitter2);
 }

 toRemove.clear();
 }

 for (int int4 = 0; int4 < items.size(); int4++) {
 InventoryItem item2 = items.get(int4);
 BaseSoundEmitter baseSoundEmitter3 = emitters.get(int4);
 ItemContainer container = item2.getOutermostContainer();
 if (container != nullptr) {
 if (container.containingItem != nullptr &&
 container.containingItem.getWorldItem() != nullptr) {
 if (container.containingItem.getWorldItem().getWorldObjectIndex() ==
 -1) {
 container = nullptr;
 }
 } else if (container.parent != nullptr) {
 if (container.parent.getObjectIndex() == -1 &&
 container.parent.getMovingObjectIndex() == -1 &&
 container.parent.getStaticMovingObjectIndex() == -1) {
 container = nullptr;
 }
 } else {
 container = nullptr;
 }
 }

 if (container != nullptr ||
 item2.getWorldItem() != nullptr &&
 item2.getWorldItem().getWorldObjectIndex() != -1) {
 item2.updateSound(baseSoundEmitter3);
 baseSoundEmitter3.tick();
 } else {
 removeItem(item2);
 }
 }
 }

 static void Reset() {
 items.clear();
 emitters.clear();
 toAdd.clear();
 toRemove.clear();
 toStopItems.clear();
 toStopEmitters.clear();
 }
}
} // namespace inventory
} // namespace zombie
