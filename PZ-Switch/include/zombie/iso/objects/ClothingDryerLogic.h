#pragma once
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/Clothing.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/interfaces/IClothingWasherDryerLogic.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ClothingDryerLogic {
public:
 const IsoObject m_object;
 bool bActivated;
 long soundInstance = -1L;
 float lastUpdate = -1.0F;
 bool cycleFinished = false;
 float startTime = 0.0F;
 float cycleLengthMinutes = 90.0F;
 bool alreadyExecuted = false;

public
 ClothingDryerLogic(IsoObject object) { this->m_object = object; }

 IsoObject getObject() { return this->m_object; }

 void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 this->bActivated = input.get() == 1;
 }

 void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 output.put((byte)(this->isActivated() ? 1 : 0);
 }

 void update() {
 if (this->getObject().getObjectIndex() != -1) {
 if (this->getContainer() != nullptr) {
 if (!this->getContainer().isPowered()) {
 this->setActivated(false);
 }

 this->cycleFinished();
 this->updateSound();
 if (GameClient.bClient) {
 }

 if (!this->isActivated()) {
 this->lastUpdate = -1.0F;
 } else {
 float float0 = (float)GameTime.getInstance().getWorldAgeHours();
 if (this->lastUpdate < 0.0F) {
 this->lastUpdate = float0;
 } else if (this->lastUpdate > float0) {
 this->lastUpdate = float0;
 }

 float float1 = float0 - this->lastUpdate;
 int int0 = (int)(float1 * 60.0F);
 if (int0 >= 1) {
 this->lastUpdate = float0;

 for (int int1 = 0; int1 < this->getContainer().getItems().size();
 int1++) {
 InventoryItem item0 = this->getContainer().getItems().get(int1);
 if (item0 instanceof Clothing clothing) {
 float float2 = clothing.getWetness();
 if (float2 > 0.0F) {
 float2 -= int0;
 clothing.setWetness(float2);
 if (GameServer.bServer) {
 }
 }
 }

 if (item0.isWet() && item0.getItemWhenDry() != nullptr) {
 item0.setWetCooldown(item0.getWetCooldown() - int0 * 250);
 if (item0.getWetCooldown() <= 0.0F) {
 InventoryItem item1 =
 InventoryItemFactory.CreateItem(item0.getItemWhenDry());
 this->getContainer().addItem(item1);
 this->getContainer().Remove(item0);
 int1--;
 item0.setWet(false);
 IsoWorld.instance.CurrentCell.addToProcessItemsRemove(item0);
 }
 }
 }
 }
 }
 }
 }
 }

 void saveChange(const std::string &change, KahluaTable tbl, ByteBuffer bb) {
 if ("dryer.state" == change) {
 bb.put((byte)(this->isActivated() ? 1 : 0);
 }
 }

 void loadChange(const std::string &change, ByteBuffer bb) {
 if ("dryer.state" == change) {
 this->setActivated(bb.get() == 1);
 }
 }

 ItemContainer getContainer() {
 return this->getObject().getContainerByType("clothingdryer");
 }

 void updateSound() {
 if (this->isActivated()) {
 if (!GameServer.bServer) {
 if (this->getObject().emitter != nullptr &&
 this->getObject().emitter.isPlaying("ClothingDryerFinished")) {
 this->getObject().emitter.stopOrTriggerSoundByName(
 "ClothingDryerFinished");
 }

 if (this->soundInstance == -1L) {
 this->getObject().emitter = IsoWorld.instance.getFreeEmitter(
 this->getObject().getX() + 0.5F, this->getObject().getY() + 0.5F,
 (int)this->getObject().getZ());
 IsoWorld.instance.setEmitterOwner(this->getObject().emitter,
 this->getObject());
 this->soundInstance = this->getObject().emitter.playSoundLoopedImpl(
 "ClothingDryerRunning");
 }
 }

 if (!GameClient.bClient) {
 WorldSoundManager.instance.addSoundRepeating(
 this, this->getObject().square.x, this->getObject().square.y,
 this->getObject().square.z, 10, 10, false);
 }
 } else if (this->soundInstance != -1L) {
 this->getObject().emitter.stopOrTriggerSound(this->soundInstance);
 this->soundInstance = -1L;
 if (this->cycleFinished) {
 this->cycleFinished = false;
 this->getObject().emitter.playSoundImpl("ClothingDryerFinished",
 this->getObject());
 }
 }
 }

 bool cycleFinished() {
 if (this->isActivated()) {
 if (!this->alreadyExecuted) {
 this->startTime = (float)GameTime.getInstance().getWorldAgeHours();
 this->alreadyExecuted = true;
 }

 float float0 =
 (float)GameTime.getInstance().getWorldAgeHours() - this->startTime;
 int int0 = (int)(float0 * 60.0F);
 if (int0 < this->cycleLengthMinutes) {
 return false;
 }

 this->cycleFinished = true;
 this->setActivated(false);
 }

 return true;
 }

 bool isItemAllowedInContainer(ItemContainer container, InventoryItem item) {
 return this->isActivated() ? false : this->getContainer() == container;
 }

 bool isRemoveItemAllowedFromContainer(ItemContainer container,
 InventoryItem item) {
 return !this->getContainer().empty() && this->isActivated()
 ? false
 : this->getContainer() == container;
 }

 bool isActivated() { return this->bActivated; }

 void setActivated(bool activated) {
 bool boolean0 = activated != this->bActivated;
 this->bActivated = activated;
 this->alreadyExecuted = false;
 if (boolean0) {
 Thread thread = Thread.currentThread();
 if (thread == GameWindow.GameThread || thread == GameServer.MainThread) {
 IsoGenerator.updateGenerator(this->getObject().getSquare());
 }
 }
 }

 void switchModeOn() {}

 void switchModeOff() {
 this->setActivated(false);
 this->updateSound();
 this->cycleFinished = false;
 }
}
} // namespace objects
} // namespace iso
} // namespace zombie
