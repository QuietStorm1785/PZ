#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/ItemPickerJava.h"
#include "zombie/iso/ContainerOverlays.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/TileOverlays.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class LoadGridsquarePerformanceWorkaround {
public:
 static void init(int var0, int var1) {
 if (!GameClient.bClient) {
 LoadGridsquarePerformanceWorkaround.ItemPicker.instance.init();
 }
 }

 static void LoadGridsquare(IsoGridSquare square) {
 if (LoadGridsquarePerformanceWorkaround.ItemPicker.instance.begin(square) {
 IsoObject[] objects = square.getObjects().getElements();
 int int0 = square.getObjects().size();

 for (int int1 = 0; int1 < int0; int1++) {
 IsoObject object = objects[int1];
 if (!(object instanceof IsoWorldInventoryObject) {
 if (!GameClient.bClient) {
 LoadGridsquarePerformanceWorkaround.ItemPicker.instance.checkObject(object);
 }

 if (object.sprite != nullptr && object.sprite.name != nullptr && !ContainerOverlays.instance.hasOverlays(object) {
 TileOverlays.instance.updateTileOverlaySprite(object);
 }
 }
 }
 }

 LoadGridsquarePerformanceWorkaround.ItemPicker.instance.end(square);
 }

 private static class ItemPicker {
 public static LoadGridsquarePerformanceWorkaround.ItemPicker instance = new LoadGridsquarePerformanceWorkaround.ItemPicker();
 IsoGridSquare square;

 void init() {
 }

 bool begin(IsoGridSquare squarex) {
 if (squarex.isOverlayDone()) {
 this->square = nullptr;
 return false;
 } else {
 this->square = squarex;
 return true;
 }
 }

 void checkObject(IsoObject object) {
 IsoSprite sprite = object.getSprite();
 if (sprite != nullptr && sprite.getName() != nullptr) {
 ItemContainer container = object.getContainer();
 if (container != nullptr && !container.isExplored()) {
 ItemPickerJava.fillContainer(container, IsoPlayer.getInstance());
 container.setExplored(true);
 if (GameServer.bServer) {
 GameServer.sendItemsInContainer(object, container);
 }
 }

 if (container == nullptr || !container.empty()) {
 ItemPickerJava.updateOverlaySprite(object);
 }
 }
 }

 void end(IsoGridSquare squarex) {
 squarex.setOverlayDone(true);
 }
 }
}
} // namespace zombie
