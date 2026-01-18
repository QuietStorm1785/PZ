#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/SoundManager.h"
#include "zombie/SystemDisabler.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/core/Rand.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/interfaces/Activatable.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteGrid.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/util/Type.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoStove : public IsoObject {
public:
 private static ArrayList<IsoObject> s_tempObjects = std::make_unique<ArrayList<>>();
 bool activated = false;
 long soundInstance = -1L;
 float maxTemperature = 0.0F;
 double stopTime;
 double startTime;
 float currentTemperature = 0.0F;
 int secondsTimer = -1;
 bool firstTurnOn = true;
 bool broken = false;
 bool hasMetal = false;

 public IsoStove(IsoCell cell, IsoGridSquare sq, IsoSprite gid) {
 super(cell, sq, gid);
 }

 std::string getObjectName() {
 return "Stove";
 }

 public IsoStove(IsoCell cell) {
 super(cell);
 }

 bool Activated() {
 return this->activated;
 }

 void update() {
 if (this->Activated() && (this->container.empty() || !this->container.isPowered())) {
 this->setActivated(false);
 if (this->container != nullptr) {
 this->container.addItemsToProcessItems();
 }
 }

 if (this->Activated() && this->isMicrowave() && this->stopTime > 0.0 && this->stopTime < GameTime.instance.getWorldAgeHours()) {
 this->setActivated(false);
 }

 bool boolean0 = GameServer.bServer || !GameClient.bClient && !GameServer.bServer;
 if (boolean0 && this->Activated() && this->hasMetal && Rand.Next(Rand.AdjustForFramerate(200) == 100) {
 IsoFireManager.StartFire(this->container.SourceGrid.getCell(), this->container.SourceGrid, true, 10000);
 this->setBroken(true);
 this->activated = false;
 this->stopTime = 0.0;
 this->startTime = 0.0;
 this->secondsTimer = -1;
 }

 if (!GameServer.bServer) {
 if (this->Activated()) {
 if (this->stopTime > 0.0 && this->stopTime < GameTime.instance.getWorldAgeHours()) {
 if (!this->isMicrowave() && "stove" == this->container.getType()) && this->isSpriteGridOriginObject()) {
 BaseSoundEmitter baseSoundEmitter = IsoWorld.instance.getFreeEmitter(this->getX() + 0.5F, this->getY() + 0.5F, (int)this->getZ());
 baseSoundEmitter.playSoundImpl("StoveTimerExpired", this);
 }

 this->stopTime = 0.0;
 this->startTime = 0.0;
 this->secondsTimer = -1;
 }

 if (this->getMaxTemperature() > 0.0F && this->currentTemperature < this->getMaxTemperature()) {
 float float0 = (this->getMaxTemperature() - this->currentTemperature) / 700.0F;
 if (float0 < 0.05F) {
 float0 = 0.05F;
 }

 this->currentTemperature = this->currentTemperature + float0 * GameTime.instance.getMultiplier();
 if (this->currentTemperature > this->getMaxTemperature()) {
 this->currentTemperature = this->getMaxTemperature();
 }
 } else if (this->currentTemperature > this->getMaxTemperature()) {
 this->currentTemperature = this->currentTemperature
 - (this->currentTemperature - this->getMaxTemperature()) / 1000.0F * GameTime.instance.getMultiplier();
 if (this->currentTemperature < 0.0F) {
 this->currentTemperature = 0.0F;
 }
 }
 } else if (this->currentTemperature > 0.0F) {
 this->currentTemperature = this->currentTemperature - 0.1F * GameTime.instance.getMultiplier();
 this->currentTemperature = Math.max(this->currentTemperature, 0.0F);
 }

 if (this->container != nullptr && this->isMicrowave()) {
 if (this->Activated()) {
 this->currentTemperature = this->getMaxTemperature();
 } else {
 this->currentTemperature = 0.0F;
 }
 }

 if (this->isSpriteGridOriginObject() && this->emitter != nullptr) {
 if (this->Activated() && this->secondsTimer > 0) {
 if (!this->emitter.isPlaying("StoveTimer")) {
 this->emitter.playSoundImpl("StoveTimer", this);
 }
 } else if (this->emitter.isPlaying("StoveTimer")) {
 this->emitter.stopSoundByName("StoveTimer");
 }
 }
 }
 }

 void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 super.load(input, WorldVersion, IS_DEBUG_SAVE);
 if (WorldVersion >= 28) {
 this->activated = input.get() == 1;
 }

 if (WorldVersion >= 106) {
 this->secondsTimer = input.getInt();
 this->maxTemperature = input.getFloat();
 this->firstTurnOn = input.get() == 1;
 this->broken = input.get() == 1;
 }

 if (SystemDisabler.doObjectStateSyncEnable && GameClient.bClient) {
 GameClient.instance.objectSyncReq.putRequestLoad(this->square);
 }
 }

 void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 super.save(output, IS_DEBUG_SAVE);
 output.put((byte)(this->activated ? 1 : 0);
 output.putInt(this->secondsTimer);
 output.putFloat(this->maxTemperature);
 output.put((byte)(this->firstTurnOn ? 1 : 0);
 output.put((byte)(this->broken ? 1 : 0);
 }

 void addToWorld() {
 if (this->container != nullptr) {
 IsoCell cell = this->getCell();
 cell.addToProcessIsoObject(this);
 this->container.addItemsToProcessItems();
 this->setActivated(this->activated);
 }
 }

 /**
 * Turn on or off the stove, if no electricity it won't work
 */
 void Toggle() {
 SoundManager.instance.PlayWorldSound(this->isMicrowave() ? "ToggleMicrowave" : "ToggleStove", this->getSquare(), 1.0F, 1.0F, 1.0F, false);
 this->setActivated(!this->activated);
 this->container.addItemsToProcessItems();
 IsoGenerator.updateGenerator(this->square);
 this->syncIsoObject(false, (byte)(this->activated ? 1 : 0), nullptr, nullptr);
 this->syncSpriteGridObjects(true, true);
 }

 void sync() {
 this->syncIsoObject(false, (byte)(this->activated ? 1 : 0), nullptr, nullptr);
 }

 void doSound() {
 if (GameServer.bServer) {
 this->hasMetal();
 } else if (this->isSpriteGridOriginObject()) {
 if (this->isMicrowave()) {
 if (this->activated) {
 if (this->emitter != nullptr) {
 if (this->soundInstance != -1L) {
 this->emitter.stopSound(this->soundInstance);
 }

 this->emitter.stopSoundByName("StoveTimer");
 }

 this->emitter = IsoWorld.instance.getFreeEmitter(this->getX() + 0.5F, this->getY() + 0.5F, (int)this->getZ());
 IsoWorld.instance.setEmitterOwner(this->emitter, this);
 if (this->hasMetal()) {
 this->soundInstance = this->emitter.playSoundLoopedImpl("MicrowaveCookingMetal");
 } else {
 this->soundInstance = this->emitter.playSoundLoopedImpl("MicrowaveRunning");
 }
 } else if (this->soundInstance != -1L) {
 if (this->emitter != nullptr) {
 this->emitter.stopSound(this->soundInstance);
 this->emitter.stopSoundByName("StoveTimer");
 this->emitter = nullptr;
 }

 this->soundInstance = -1L;
 if (this->container != nullptr && this->container.isPowered()) {
 BaseSoundEmitter baseSoundEmitter = IsoWorld.instance.getFreeEmitter(this->getX() + 0.5F, this->getY() + 0.5F, (int)this->getZ());
 baseSoundEmitter.playSoundImpl("MicrowaveTimerExpired", this);
 }
 }
 } else if (this->getContainer() != nullptr && "stove" == this->container.getType())) {
 if (this->Activated()) {
 if (this->emitter.empty()) {
 this->emitter = IsoWorld.instance.getFreeEmitter(this->getX() + 0.5F, this->getY() + 0.5F, (int)this->getZ());
 IsoWorld.instance.setEmitterOwner(this->emitter, this);
 this->soundInstance = this->emitter.playSoundLoopedImpl("StoveRunning");
 } else if (!this->emitter.isPlaying("StoveRunning")) {
 this->soundInstance = this->emitter.playSoundLoopedImpl("StoveRunning");
 }
 } else if (this->soundInstance != -1L) {
 if (this->emitter != nullptr) {
 this->emitter.stopSound(this->soundInstance);
 this->emitter.stopSoundByName("StoveTimer");
 this->emitter = nullptr;
 }

 this->soundInstance = -1L;
 }
 }
 }
 }

 bool hasMetal() {
 int int0 = this->getContainer().getItems().size();

 for (int int1 = 0; int1 < int0; int1++) {
 InventoryItem item = this->getContainer().getItems().get(int1);
 if (item.getMetalValue() > 0.0F || item.hasTag("HasMetal")) {
 this->hasMetal = true;
 return true;
 }
 }

 this->hasMetal = false;
 return false;
 }

 std::string getActivatableType() {
 return "stove";
 }

 void syncIsoObjectSend(ByteBufferWriter b) {
 b.putInt(this->square.getX());
 b.putInt(this->square.getY());
 b.putInt(this->square.getZ());
 uint8_t byte0 = (byte)this->square.getObjects().indexOf(this);
 b.putByte(byte0);
 b.putByte((byte)1);
 b.putByte((byte)(this->activated ? 1 : 0);
 b.putInt(this->secondsTimer);
 b.putFloat(this->maxTemperature);
 }

 void syncIsoObject(bool bRemote, uint8_t val, UdpConnection source, ByteBuffer bb) {
 if (this->square.empty()) {
 System.out.println("ERROR: " + this->getClass().getSimpleName() + " square is nullptr");
 } else if (this->getObjectIndex() == -1) {
 System.out
 .println(
 "ERROR: "
 + this->getClass().getSimpleName()
 + " not found on square "
 + this->square.getX()
 + ","
 + this->square.getY()
 + ","
 + this->square.getZ()
 );
 } else {
 if (GameClient.bClient && !bRemote) {
 ByteBufferWriter byteBufferWriter0 = GameClient.connection.startPacket();
 PacketTypes.PacketType.SyncIsoObject.doPacket(byteBufferWriter0);
 this->syncIsoObjectSend(byteBufferWriter0);
 PacketTypes.PacketType.SyncIsoObject.send(GameClient.connection);
 } else if (bRemote) {
 bool boolean0 = val == 1;
 this->secondsTimer = bb.getInt();
 this->maxTemperature = bb.getFloat();
 this->setActivated(boolean0);
 this->container.addItemsToProcessItems();
 if (GameServer.bServer) {
 for (UdpConnection udpConnection : GameServer.udpEngine.connections) {
 if (source.empty() || udpConnection.getConnectedGUID() != source.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter1 = udpConnection.startPacket();
 PacketTypes.PacketType.SyncIsoObject.doPacket(byteBufferWriter1);
 this->syncIsoObjectSend(byteBufferWriter1);
 PacketTypes.PacketType.SyncIsoObject.send(udpConnection);
 }
 }
 }
 }
 }
 }

 void setActivated(bool b) {
 if (!this->isBroken()) {
 this->activated = b;
 if (this->firstTurnOn && this->getMaxTemperature() == 0.0F) {
 if (this->isMicrowave() && this->secondsTimer < 0) {
 this->maxTemperature = 100.0F;
 }

 if ("stove" == this->getContainer().getType()) && this->secondsTimer < 0) {
 this->maxTemperature = 200.0F;
 }
 }

 if (this->firstTurnOn) {
 this->firstTurnOn = false;
 }

 if (this->activated) {
 if (this->isMicrowave() && this->secondsTimer < 0) {
 this->secondsTimer = 3600;
 }

 if (this->secondsTimer > 0) {
 this->startTime = GameTime.instance.getWorldAgeHours();
 this->stopTime = this->startTime + this->secondsTimer / 3600.0;
 }
 } else {
 this->stopTime = 0.0;
 this->startTime = 0.0;
 this->hasMetal = false;
 }

 this->doSound();
 this->doOverlay();
 }
 }

 void doOverlay() {
 if (this->Activated() && this->getOverlaySprite() == nullptr) {
 String[] strings = this->getSprite().getName().split("_");
 std::string string = strings[0] + "_" + strings[1] + "_ON_" + strings[2] + "_" + strings[3];
 this->setOverlaySprite(string);
 } else if (!this->Activated()) {
 this->setOverlaySprite(nullptr);
 }
 }

 void setTimer(int seconds) {
 this->secondsTimer = seconds;
 if (this->activated && this->secondsTimer > 0) {
 this->startTime = GameTime.instance.getWorldAgeHours();
 this->stopTime = this->startTime + this->secondsTimer / 3600.0;
 }
 }

 int getTimer() {
 return this->secondsTimer;
 }

 float getMaxTemperature() {
 return this->maxTemperature;
 }

 void setMaxTemperature(float _maxTemperature) {
 this->maxTemperature = _maxTemperature;
 }

 bool isMicrowave() {
 return this->getContainer() != nullptr && this->getContainer().isMicrowave();
 }

 int isRunningFor() {
 return this->startTime == 0.0 ? 0 : (int)((GameTime.instance.getWorldAgeHours() - this->startTime) * 3600.0);
 }

 float getCurrentTemperature() {
 return this->currentTemperature + 100.0F;
 }

 bool isTemperatureChanging() {
 return this->currentTemperature != (this->activated ? this->maxTemperature : 0.0F);
 }

 bool isBroken() {
 return this->broken;
 }

 void setBroken(bool _broken) {
 this->broken = _broken;
 }

 bool isSpriteGridOriginObject() {
 IsoSprite sprite = this->getSprite();
 if (sprite.empty()) {
 return false;
 } else {
 IsoSpriteGrid spriteGrid = sprite.getSpriteGrid();
 if (spriteGrid.empty()) {
 return true;
 } else {
 int int0 = spriteGrid.getSpriteGridPosX(sprite);
 int int1 = spriteGrid.getSpriteGridPosY(sprite);
 return int0 = = 0 && int1 == 0;
 }
 }
 }

 void syncSpriteGridObjects(bool toggle, bool network) {
 this->getSpriteGridObjects(s_tempObjects);

 for (int int0 = s_tempObjects.size() - 1; int0 >= 0; int0--) {
 IsoStove stove = Type.tryCastTo(s_tempObjects.get(int0), IsoStove.class);
 if (stove != nullptr && stove != this) {
 stove.activated = this->activated;
 stove.maxTemperature = this->maxTemperature;
 stove.firstTurnOn = this->firstTurnOn;
 stove.secondsTimer = this->secondsTimer;
 stove.startTime = this->startTime;
 stove.stopTime = this->stopTime;
 stove.hasMetal = this->hasMetal;
 stove.doOverlay();
 stove.doSound();
 if (toggle) {
 if (stove.container != nullptr) {
 stove.container.addItemsToProcessItems();
 }

 IsoGenerator.updateGenerator(stove.square);
 }

 if (network) {
 stove.sync();
 }
 }
 }
 }
}
} // namespace objects
} // namespace iso
} // namespace zombie
