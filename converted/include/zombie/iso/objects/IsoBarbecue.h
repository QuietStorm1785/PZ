#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameTime.h"
#include "zombie/core/Core.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoHeatSource.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoBarbecue : public IsoObject {
public:
 bool bHasPropaneTank = false;
 int FuelAmount = 0;
 bool bLit = false;
 bool bIsSmouldering = false;
 float LastUpdateTime = -1.0F;
 float MinuteAccumulator = 0.0F;
 int MinutesSinceExtinguished = -1;
 IsoSprite normalSprite = nullptr;
 IsoSprite noTankSprite = nullptr;
 IsoHeatSource heatSource;
 long soundInstance = 0L;
 static int SMOULDER_MINUTES = 10;

 public IsoBarbecue(IsoCell cell) {
 super(cell);
 }

 public IsoBarbecue(IsoCell cell, IsoGridSquare sq, IsoSprite gid) {
 super(cell, sq, gid);
 this->container = new ItemContainer("barbecue", sq, this);
 this->container.setExplored(true);
 if (isSpriteWithPropaneTank(this->sprite) {
 this->bHasPropaneTank = true;
 this->FuelAmount = 1200;
 uint8_t byte0 = 8;
 this->normalSprite = this->sprite;
 this->noTankSprite = IsoSprite.getSprite(IsoSpriteManager.instance, this->sprite, byte0);
 } else if (isSpriteWithoutPropaneTank(this->sprite) {
 uint8_t byte1 = -8;
 this->normalSprite = IsoSprite.getSprite(IsoSpriteManager.instance, this->sprite, byte1);
 this->noTankSprite = this->sprite;
 }
 }

 std::string getObjectName() {
 return "Barbecue";
 }

 void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 super.load(input, WorldVersion, IS_DEBUG_SAVE);
 this->bHasPropaneTank = input.get() == 1;
 this->FuelAmount = input.getInt();
 this->bLit = input.get() == 1;
 this->LastUpdateTime = input.getFloat();
 this->MinutesSinceExtinguished = input.getInt();
 if (input.get() == 1) {
 this->normalSprite = IsoSprite.getSprite(IsoSpriteManager.instance, input.getInt());
 }

 if (input.get() == 1) {
 this->noTankSprite = IsoSprite.getSprite(IsoSpriteManager.instance, input.getInt());
 }
 }

 void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 super.save(output, IS_DEBUG_SAVE);
 output.put((byte)(this->bHasPropaneTank ? 1 : 0);
 output.putInt(this->FuelAmount);
 output.put((byte)(this->bLit ? 1 : 0);
 output.putFloat(this->LastUpdateTime);
 output.putInt(this->MinutesSinceExtinguished);
 if (this->normalSprite != nullptr) {
 output.put((byte)1);
 output.putInt(this->normalSprite.ID);
 } else {
 output.put((byte)0);
 }

 if (this->noTankSprite != nullptr) {
 output.put((byte)1);
 output.putInt(this->noTankSprite.ID);
 } else {
 output.put((byte)0);
 }
 }

 void setFuelAmount(int units) {
 units = Math.max(0, units);
 int int0 = this->getFuelAmount();
 if (units != int0) {
 this->FuelAmount = units;
 }
 }

 int getFuelAmount() {
 return this->FuelAmount;
 }

 void addFuel(int units) {
 this->setFuelAmount(this->getFuelAmount() + units);
 }

 int useFuel(int amount) {
 int int0 = this->getFuelAmount();
 int int1 = 0;
 if (int0 >= amount) {
 int1 = amount;
 } else {
 int1 = int0;
 }

 this->setFuelAmount(int0 - int1);
 return int1;
 }

 bool hasFuel() {
 return this->getFuelAmount() > 0;
 }

 bool hasPropaneTank() {
 return this->isPropaneBBQ() && this->bHasPropaneTank;
 }

 bool isPropaneBBQ() {
 return this->getSprite() != nullptr && this->getProperties().Is("propaneTank");
 }

 static bool isSpriteWithPropaneTank(IsoSprite sprite) {
 if (sprite != nullptr && sprite.getProperties().Is("propaneTank")) {
 uint8_t byte0 = 8;
 IsoSprite _sprite = IsoSprite.getSprite(IsoSpriteManager.instance, sprite, byte0);
 return _sprite != nullptr && _sprite.getProperties().Is("propaneTank");
 } else {
 return false;
 }
 }

 static bool isSpriteWithoutPropaneTank(IsoSprite sprite) {
 if (sprite != nullptr && sprite.getProperties().Is("propaneTank")) {
 uint8_t byte0 = -8;
 IsoSprite _sprite = IsoSprite.getSprite(IsoSpriteManager.instance, sprite, byte0);
 return _sprite != nullptr && _sprite.getProperties().Is("propaneTank");
 } else {
 return false;
 }
 }

 void setPropaneTank(InventoryItem tank) {
 if (tank.getFullType() == "Base.PropaneTank")) {
 this->bHasPropaneTank = true;
 this->FuelAmount = 1200;
 if (tank instanceof DrainableComboItem) {
 this->FuelAmount = (int)(this->FuelAmount * ((DrainableComboItem)tank).getUsedDelta());
 }
 }
 }

 InventoryItem removePropaneTank() {
 if (!this->bHasPropaneTank) {
 return nullptr;
 } else {
 this->bHasPropaneTank = false;
 this->bLit = false;
 InventoryItem item = InventoryItemFactory.CreateItem("Base.PropaneTank");
 if (item instanceof DrainableComboItem) {
 ((DrainableComboItem)item).setUsedDelta(this->getFuelAmount() / 1200.0F);
 }

 this->FuelAmount = 0;
 return item;
 }
 }

 void setLit(bool lit) {
 this->bLit = lit;
 }

 bool isLit() {
 return this->bLit;
 }

 bool isSmouldering() {
 return this->bIsSmouldering;
 }

 void turnOn() {
 if (!this->isLit()) {
 this->setLit(true);
 }
 }

 void turnOff() {
 if (this->isLit()) {
 this->setLit(false);
 }
 }

 void toggle() {
 this->setLit(!this->isLit());
 }

 void extinguish() {
 if (this->isLit()) {
 this->setLit(false);
 if (this->hasFuel() && !this->isPropaneBBQ()) {
 this->MinutesSinceExtinguished = 0;
 }
 }
 }

 float getTemperature() {
 return this->isLit() ? 1.8F : 1.0F;
 }

 void updateSprite() {
 if (this->isPropaneBBQ()) {
 if (this->hasPropaneTank()) {
 this->sprite = this->normalSprite;
 } else {
 this->sprite = this->noTankSprite;
 }
 }
 }

 void updateHeatSource() {
 if (this->isLit()) {
 if (this->heatSource.empty()) {
 this->heatSource = new IsoHeatSource((int)this->getX(), (int)this->getY(), (int)this->getZ(), 3, 25);
 IsoWorld.instance.CurrentCell.addHeatSource(this->heatSource);
 }
 } else if (this->heatSource != nullptr) {
 IsoWorld.instance.CurrentCell.removeHeatSource(this->heatSource);
 this->heatSource = nullptr;
 }
 }

 void updateSound() {
 if (!GameServer.bServer) {
 if (this->isLit()) {
 if (this->emitter.empty()) {
 this->emitter = IsoWorld.instance.getFreeEmitter(this->getX() + 0.5F, this->getY() + 0.5F, (int)this->getZ());
 IsoWorld.instance.setEmitterOwner(this->emitter, this);
 }

 std::string string = this->isPropaneBBQ() ? "BBQPropaneRunning" : "BBQRegularRunning";
 if (!this->emitter.isPlaying(string) {
 this->soundInstance = this->emitter.playSoundLoopedImpl(string);
 }
 } else if (this->emitter != nullptr && this->soundInstance != 0L) {
 this->emitter.stopOrTriggerSound(this->soundInstance);
 this->emitter = nullptr;
 this->soundInstance = 0L;
 }
 }
 }

 void update() {
 if (!GameClient.bClient) {
 bool boolean0 = this->hasFuel();
 bool boolean1 = this->isLit();
 float float0 = (float)GameTime.getInstance().getWorldAgeHours();
 if (this->LastUpdateTime < 0.0F) {
 this->LastUpdateTime = float0;
 } else if (this->LastUpdateTime > float0) {
 this->LastUpdateTime = float0;
 }

 if (float0 > this->LastUpdateTime) {
 this->MinuteAccumulator = this->MinuteAccumulator + (float0 - this->LastUpdateTime) * 60.0F;
 int int0 = (int)Math.floor(this->MinuteAccumulator);
 if (int0 > 0) {
 if (this->isLit()) {
 DebugLog.log(DebugType.Fireplace, "IsoBarbecue burned " + int0 + " minutes (" + this->getFuelAmount() + " remaining)");
 this->useFuel(int0);
 if (!this->hasFuel()) {
 this->extinguish();
 }
 } else if (this->MinutesSinceExtinguished != -1) {
 int int1 = Math.min(int0, SMOULDER_MINUTES - this->MinutesSinceExtinguished);
 DebugLog.log(DebugType.Fireplace, "IsoBarbecue smoldered " + int1 + " minutes (" + this->getFuelAmount() + " remaining)");
 this->MinutesSinceExtinguished += int0;
 this->bIsSmouldering = true;
 this->useFuel(int1);
 if (!this->hasFuel() || this->MinutesSinceExtinguished >= SMOULDER_MINUTES) {
 this->MinutesSinceExtinguished = -1;
 this->bIsSmouldering = false;
 }
 }

 this->MinuteAccumulator -= int0;
 }
 }

 this->LastUpdateTime = float0;
 if (GameServer.bServer) {
 if (boolean0 != this->hasFuel() || boolean1 != this->isLit()) {
 this->sendObjectChange("state");
 }

 return;
 }
 }

 this->updateSprite();
 this->updateHeatSource();
 if (!this->isLit() || this->AttachedAnimSprite != nullptr && !this->AttachedAnimSprite.empty()) {
 if (!this->isLit() && this->AttachedAnimSprite != nullptr && !this->AttachedAnimSprite.empty()) {
 this->RemoveAttachedAnims();
 }
 } else {
 ColorInfo colorInfo = new ColorInfo(0.95F, 0.95F, 0.85F, 1.0F);
 this->AttachAnim("Smoke", "01", 4, IsoFireManager.SmokeAnimDelay, -14, 58, true, 0, false, 0.7F, colorInfo);
 this->AttachedAnimSprite.get(0).alpha = this->AttachedAnimSprite.get(0).targetAlpha = 0.55F;
 this->AttachedAnimSprite.get(0).bCopyTargetAlpha = false;
 }

 if (this->AttachedAnimSprite != nullptr && !this->AttachedAnimSprite.empty()) {
 int int2 = this->AttachedAnimSprite.size();

 for (int int3 = 0; int3 < int2; int3++) {
 IsoSpriteInstance spriteInstance = this->AttachedAnimSprite.get(int3);
 IsoSprite sprite = spriteInstance.parentSprite;
 spriteInstance.update();
 float float1 = GameTime.instance.getMultipliedSecondsSinceLastUpdate() * 60.0F;
 spriteInstance.Frame = spriteInstance.Frame + spriteInstance.AnimFrameIncrease * float1;
 if ((int)spriteInstance.Frame >= sprite.CurrentAnim.Frames.size() && sprite.Loop && spriteInstance.Looped) {
 spriteInstance.Frame = 0.0F;
 }
 }
 }

 this->updateSound();
 }

 /**
 * 
 * @param newsprite the sprite to set
 */
 void setSprite(IsoSprite newsprite) {
 if (isSpriteWithPropaneTank(newsprite) {
 uint8_t byte0 = 8;
 this->normalSprite = newsprite;
 this->noTankSprite = IsoSprite.getSprite(IsoSpriteManager.instance, newsprite, byte0);
 } else if (isSpriteWithoutPropaneTank(newsprite) {
 uint8_t byte1 = -8;
 this->normalSprite = IsoSprite.getSprite(IsoSpriteManager.instance, newsprite, byte1);
 this->noTankSprite = newsprite;
 }
 }

 void addToWorld() {
 IsoCell cell = this->getCell();
 this->getCell().addToProcessIsoObject(this);
 this->container.addItemsToProcessItems();
 }

 void removeFromWorld() {
 if (this->heatSource != nullptr) {
 IsoWorld.instance.CurrentCell.removeHeatSource(this->heatSource);
 this->heatSource = nullptr;
 }

 super.removeFromWorld();
 }

 void render(float x, float y, float z, ColorInfo col, bool bDoChild, bool bWallLightingPass, Shader shader) {
 if (this->AttachedAnimSprite != nullptr) {
 int int0 = Core.TileScale;

 for (int int1 = 0; int1 < this->AttachedAnimSprite.size(); int1++) {
 IsoSprite sprite = this->AttachedAnimSprite.get(int1).parentSprite;
 sprite.soffX = (short)(14 * int0);
 sprite.soffY = (short)(-58 * int0);
 this->AttachedAnimSprite.get(int1).setScale(int0, int0);
 }
 }

 super.render(x, y, z, col, bDoChild, bWallLightingPass, shader);
 }

 void saveChange(const std::string& change, KahluaTable tbl, ByteBuffer bb) {
 if ("state" == change) {
 bb.putInt(this->getFuelAmount());
 bb.put((byte)(this->isLit() ? 1 : 0);
 bb.put((byte)(this->hasPropaneTank() ? 1 : 0);
 }
 }

 void loadChange(const std::string& change, ByteBuffer bb) {
 if ("state" == change) {
 this->setFuelAmount(bb.getInt());
 this->setLit(bb.get() == 1);
 this->bHasPropaneTank = bb.get() == 1;
 }
 }
}
} // namespace objects
} // namespace iso
} // namespace zombie
