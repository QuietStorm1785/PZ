#pragma once
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SystemDisabler.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/inventory/types/Moveable.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoLightSource.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoRoomLight.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes.h"
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

class IsoLightSwitch : public IsoObject {
public:
 bool Activated = false;
public
 ArrayList<IsoLightSource> lights = std::make_unique<ArrayList<>>();
 bool lightRoom = false;
 int RoomID = -1;
 bool bStreetLight = false;
 bool canBeModified = false;
 bool useBattery = false;
 bool hasBattery = false;
 std::string bulbItem = "Base.LightBulb";
 float power = 0.0F;
 float delta = 2.5E-4F;
 float primaryR = 1.0F;
 float primaryG = 1.0F;
 float primaryB = 1.0F;
 long lastMinuteStamp = -1L;
 int bulbBurnMinutes = -1;
 int lastMin = 0;
 int nextBreakUpdate = 60;

 std::string getObjectName() { return "LightSwitch"; }

public
 IsoLightSwitch(IsoCell cell) { super(cell); }

public
 IsoLightSwitch(IsoCell cell, IsoGridSquare sq, IsoSprite gid, int _RoomID) {
 super(cell, sq, gid);
 this->RoomID = _RoomID;
 if (gid != nullptr && gid.getProperties().Is("lightR")) {
 if (gid.getProperties().Is("IsMoveAble")) {
 this->canBeModified = true;
 }

 this->primaryR =
 Float.parseFloat(gid.getProperties().Val("lightR")) / 255.0F;
 this->primaryG =
 Float.parseFloat(gid.getProperties().Val("lightG")) / 255.0F;
 this->primaryB =
 Float.parseFloat(gid.getProperties().Val("lightB")) / 255.0F;
 } else {
 this->lightRoom = true;
 }

 this->bStreetLight = gid != nullptr && gid.getProperties().Is("streetlight");
 IsoRoom room = this->square.getRoom();
 if (room != nullptr && this->lightRoom) {
 if (!sq.haveElectricity() && !IsoWorld.instance.isHydroPowerOn()) {
 room.def.bLightsActive = false;
 }

 this->Activated = room.def.bLightsActive;
 room.lightSwitches.add(this);
 } else {
 this->Activated = true;
 }
 }

 void addLightSourceFromSprite() {
 if (this->sprite != nullptr && this->sprite.getProperties().Is("lightR")) {
 float float0 =
 Float.parseFloat(this->sprite.getProperties().Val("lightR")) / 255.0F;
 float float1 =
 Float.parseFloat(this->sprite.getProperties().Val("lightG")) / 255.0F;
 float float2 =
 Float.parseFloat(this->sprite.getProperties().Val("lightB")) / 255.0F;
 this->Activated = false;
 this->setActive(true, true);
 int int0 = 10;
 if (this->sprite.getProperties().Is("LightRadius") &&
 Integer.parseInt(this->sprite.getProperties().Val("LightRadius")) >
 0) {
 int0 = Integer.parseInt(this->sprite.getProperties().Val("LightRadius"));
 }

 IsoLightSource lightSource =
 new IsoLightSource(this->square.getX(), this->square.getY(),
 this->square.getZ(), float0, float1, float2, int0);
 lightSource.bActive = this->Activated;
 lightSource.bHydroPowered = true;
 lightSource.switches.add(this);
 this->lights.add(lightSource);
 }
 }

 bool getCanBeModified() { return this->canBeModified; }

 float getPower() { return this->power; }

 void setPower(float _power) { this->power = _power; }

 void setDelta(float _delta) { this->delta = _delta; }

 float getDelta() { return this->delta; }

 void setUseBattery(bool b) {
 this->setActive(false);
 this->useBattery = b;
 if (GameClient.bClient) {
 this->syncCustomizedSettings(nullptr);
 }
 }

 bool getUseBattery() { return this->useBattery; }

 bool getHasBattery() { return this->hasBattery; }

 void setHasBatteryRaw(bool b) { this->hasBattery = b; }

 void addBattery(IsoGameCharacter chr, InventoryItem battery) {
 if (this->canBeModified && this->useBattery && !this->hasBattery &&
 battery != nullptr && battery.getFullType() == "Base.Battery")) {
 this->power = ((DrainableComboItem)battery).getUsedDelta();
 this->hasBattery = true;
 chr.removeFromHands(battery);
 chr.getInventory().Remove(battery);
 if (GameClient.bClient) {
 this->syncCustomizedSettings(nullptr);
 }
 }
 }

 DrainableComboItem removeBattery(IsoGameCharacter chr) {
 if (this->canBeModified && this->useBattery && this->hasBattery) {
 DrainableComboItem drainableComboItem =
 (DrainableComboItem)InventoryItemFactory.CreateItem("Base.Battery");
 if (drainableComboItem != nullptr) {
 this->hasBattery = false;
 drainableComboItem.setUsedDelta(this->power >= 0.0F ? this->power : 0.0F);
 this->power = 0.0F;
 this->setActive(false, false, true);
 chr.getInventory().AddItem(drainableComboItem);
 if (GameClient.bClient) {
 this->syncCustomizedSettings(nullptr);
 }

 return drainableComboItem;
 }
 }

 return nullptr;
 }

 bool hasLightBulb() { return this->bulbItem != nullptr; }

 std::string getBulbItem() { return this->bulbItem; }

 void setBulbItemRaw(const std::string &item) { this->bulbItem = item; }

 void addLightBulb(IsoGameCharacter chr, InventoryItem bulb) {
 if (!this->hasLightBulb() && bulb != nullptr &&
 bulb.getType().startsWith("LightBulb")) {
 IsoLightSource lightSource = this->getPrimaryLight();
 if (lightSource != nullptr) {
 this->setPrimaryR(bulb.getColorRed());
 this->setPrimaryG(bulb.getColorGreen());
 this->setPrimaryB(bulb.getColorBlue());
 this->bulbItem = bulb.getFullType();
 chr.removeFromHands(bulb);
 chr.getInventory().Remove(bulb);
 if (GameClient.bClient) {
 this->syncCustomizedSettings(nullptr);
 }
 }
 }
 }

 InventoryItem removeLightBulb(IsoGameCharacter chr) {
 IsoLightSource lightSource = this->getPrimaryLight();
 if (lightSource != nullptr && this->hasLightBulb()) {
 InventoryItem item = InventoryItemFactory.CreateItem(this->bulbItem);
 if (item != nullptr) {
 item.setColorRed(this->getPrimaryR());
 item.setColorGreen(this->getPrimaryG());
 item.setColorBlue(this->getPrimaryB());
 item.setColor(new Color(lightSource.r, lightSource.g, lightSource.b);
 this->bulbItem = nullptr;
 chr.getInventory().AddItem(item);
 this->setActive(false, false, true);
 if (GameClient.bClient) {
 this->syncCustomizedSettings(nullptr);
 }

 return item;
 }
 }

 return nullptr;
 }

 IsoLightSource getPrimaryLight() {
 return this->lights.size() > 0 ? this->lights.get(0) : nullptr;
 }

 float getPrimaryR() {
 return this->getPrimaryLight() != nullptr ? this->getPrimaryLight().r
 : this->primaryR;
 }

 float getPrimaryG() {
 return this->getPrimaryLight() != nullptr ? this->getPrimaryLight().g
 : this->primaryG;
 }

 float getPrimaryB() {
 return this->getPrimaryLight() != nullptr ? this->getPrimaryLight().b
 : this->primaryB;
 }

 void setPrimaryR(float r) {
 this->primaryR = r;
 if (this->getPrimaryLight() != nullptr) {
 this->getPrimaryLight().r = r;
 }
 }

 void setPrimaryG(float g) {
 this->primaryG = g;
 if (this->getPrimaryLight() != nullptr) {
 this->getPrimaryLight().g = g;
 }
 }

 void setPrimaryB(float b) {
 this->primaryB = b;
 if (this->getPrimaryLight() != nullptr) {
 this->getPrimaryLight().b = b;
 }
 }

 void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 super.load(input, WorldVersion, IS_DEBUG_SAVE);
 this->lightRoom = input.get() == 1;
 this->RoomID = input.getInt();
 this->Activated = input.get() == 1;
 if (WorldVersion >= 76) {
 this->canBeModified = input.get() == 1;
 if (this->canBeModified) {
 this->useBattery = input.get() == 1;
 this->hasBattery = input.get() == 1;
 if (input.get() == 1) {
 this->bulbItem = GameWindow.ReadString(input);
 } else {
 this->bulbItem = nullptr;
 }

 this->power = input.getFloat();
 this->delta = input.getFloat();
 this->setPrimaryR(input.getFloat());
 this->setPrimaryG(input.getFloat());
 this->setPrimaryB(input.getFloat());
 }
 }

 if (WorldVersion >= 79) {
 this->lastMinuteStamp = input.getLong();
 this->bulbBurnMinutes = input.getInt();
 }

 this->bStreetLight =
 this->sprite != nullptr && this->sprite.getProperties().Is("streetlight");
 if (this->square != nullptr) {
 IsoRoom room = this->square.getRoom();
 if (room != nullptr && this->lightRoom) {
 this->Activated = room.def.bLightsActive;
 room.lightSwitches.add(this);
 } else {
 float float0 = 0.9F;
 float float1 = 0.8F;
 float float2 = 0.7F;
 if (this->sprite != nullptr &&
 this->sprite.getProperties().Is("lightR")) {
 if (WorldVersion >= 76 && this->canBeModified) {
 float0 = this->primaryR;
 float1 = this->primaryG;
 float2 = this->primaryB;
 } else {
 float0 =
 Float.parseFloat(this->sprite.getProperties().Val("lightR")) /
 255.0F;
 float1 =
 Float.parseFloat(this->sprite.getProperties().Val("lightG")) /
 255.0F;
 float2 =
 Float.parseFloat(this->sprite.getProperties().Val("lightB")) /
 255.0F;
 this->primaryR = float0;
 this->primaryG = float1;
 this->primaryB = float2;
 }
 }

 int int0 = 8;
 if (this->sprite.getProperties().Is("LightRadius") &&
 Integer.parseInt(this->sprite.getProperties().Val("LightRadius")) >
 0) {
 int0 =
 Integer.parseInt(this->sprite.getProperties().Val("LightRadius"));
 }

 IsoLightSource lightSource =
 new IsoLightSource((int)this->getX(), (int)this->getY(),
 (int)this->getZ(), float0, float1, float2, int0);
 lightSource.bActive = this->Activated;
 lightSource.bWasActive = lightSource.bActive;
 lightSource.bHydroPowered = true;
 lightSource.switches.add(this);
 this->lights.add(lightSource);
 }

 if (SystemDisabler.doObjectStateSyncEnable && GameClient.bClient) {
 GameClient.instance.objectSyncReq.putRequestLoad(this->square);
 }
 }
 }

 void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 super.save(output, IS_DEBUG_SAVE);
 output.put((byte)(this->lightRoom ? 1 : 0);
 output.putInt(this->RoomID);
 output.put((byte)(this->Activated ? 1 : 0);
 output.put((byte)(this->canBeModified ? 1 : 0);
 if (this->canBeModified) {
 output.put((byte)(this->useBattery ? 1 : 0);
 output.put((byte)(this->hasBattery ? 1 : 0);
 output.put((byte)(this->hasLightBulb() ? 1 : 0);
 if (this->hasLightBulb()) {
 GameWindow.WriteString(output, this->bulbItem);
 }

 output.putFloat(this->power);
 output.putFloat(this->delta);
 output.putFloat(this->getPrimaryR());
 output.putFloat(this->getPrimaryG());
 output.putFloat(this->getPrimaryB());
 }

 output.putLong(this->lastMinuteStamp);
 output.putInt(this->bulbBurnMinutes);
 }

 bool onMouseLeftClick(int x, int y) { return false; }

 bool canSwitchLight() {
 if (this->bulbItem != nullptr) {
 bool boolean0 = IsoWorld.instance.isHydroPowerOn();
 bool boolean1 = boolean0
 ? this->square.getRoom() != nullptr || this->bStreetLight
 : this->square.haveElectricity();
 if (!boolean1 && this->getCell() != nullptr) {
 for (int int0 = 0; int0 >= (this->getZ() >= 1.0F ? -1 : 0); int0--) {
 for (int int1 = -1; int1 < 2; int1++) {
 for (int int2 = -1; int2 < 2; int2++) {
 if (int1 != 0 || int2 != 0 || int0 != 0) {
 IsoGridSquare square = this->getCell().getGridSquare(
 (double)(this->getX() + int1), (double)(this->getY() + int2),
 (double)(this->getZ() + int0);
 if (square != nullptr &&
 (boolean0 && square.getRoom() != nullptr ||
 square.haveElectricity())) {
 boolean1 = true;
 break;
 }
 }
 }

 if (boolean1) {
 break;
 }
 }
 }
 }

 if (!this->useBattery && boolean1 ||
 this->canBeModified && this->useBattery && this->hasBattery &&
 this->power > 0.0F) {
 return true;
 }
 }

 return false;
 }

 bool setActive(bool active) { return this->setActive(active, false, false); }

 bool setActive(bool active, bool setActiveBoolOnly) {
 return this->setActive(active, setActiveBoolOnly, false);
 }

 bool setActive(bool active, bool setActiveBoolOnly, bool ignoreSwitchCheck) {
 if (this->bulbItem.empty()) {
 active = false;
 }

 if (active == this->Activated) {
 return this->Activated;
 } else if (this->square.getRoom() == nullptr && !this->canBeModified) {
 return this->Activated;
 } else {
 if (ignoreSwitchCheck || this->canSwitchLight()) {
 this->Activated = active;
 if (!setActiveBoolOnly) {
 IsoWorld.instance.getFreeEmitter().playSound("LightSwitch",
 this->square);
 this->switchLight(this->Activated);
 this->syncIsoObject(false, (byte)(this->Activated ? 1 : 0), nullptr);
 }
 }

 return this->Activated;
 }
 }

 bool toggle() { return this->setActive(!this->Activated); }

 void switchLight(bool _Activated) {
 if (this->lightRoom && this->square.getRoom() != nullptr) {
 this->square.getRoom().def.bLightsActive = _Activated;

 for (int int0 = 0; int0 < this->square.getRoom().lightSwitches.size();
 int0++) {
 this->square.getRoom().lightSwitches.get(int0).Activated = _Activated;
 }

 if (GameServer.bServer) {
 int int1 = this->square.getX() / 300;
 int int2 = this->square.getY() / 300;
 int int3 = this->square.getRoom().def.ID;
 GameServer.sendMetaGrid(int1, int2, int3);
 }
 }

 for (int int4 = 0; int4 < this->lights.size(); int4++) {
 IsoLightSource lightSource = this->lights.get(int4);
 lightSource.bActive = _Activated;
 }

 IsoGridSquare.RecalcLightTime = -1;
 GameTime.instance.lightSourceUpdate = 100.0F;
 IsoGenerator.updateGenerator(this->getSquare());
 }

 void getCustomSettingsFromItem(InventoryItem item) {
 if (item instanceof Moveable moveable && moveable.isLight()) {
 this->useBattery = moveable.isLightUseBattery();
 this->hasBattery = moveable.isLightHasBattery();
 this->bulbItem = moveable.getLightBulbItem();
 this->power = moveable.getLightPower();
 this->delta = moveable.getLightDelta();
 this->setPrimaryR(moveable.getLightR());
 this->setPrimaryG(moveable.getLightG());
 this->setPrimaryB(moveable.getLightB());
 }
 }

 void setCustomSettingsToItem(InventoryItem item) {
 if (item instanceof Moveable moveable) {
 moveable.setLightUseBattery(this->useBattery);
 moveable.setLightHasBattery(this->hasBattery);
 moveable.setLightBulbItem(this->bulbItem);
 moveable.setLightPower(this->power);
 moveable.setLightDelta(this->delta);
 moveable.setLightR(this->primaryR);
 moveable.setLightG(this->primaryG);
 moveable.setLightB(this->primaryB);
 }
 }

 void syncCustomizedSettings(UdpConnection source) {
 if (GameClient.bClient) {
 this->writeCustomizedSettingsPacket(GameClient.connection);
 } else if (GameServer.bServer) {
 for (UdpConnection udpConnection : GameServer.udpEngine.connections) {
 if (source.empty() ||
 udpConnection.getConnectedGUID() != source.getConnectedGUID()) {
 this->writeCustomizedSettingsPacket(udpConnection);
 }
 }
 }
 }

 void writeCustomizedSettingsPacket(UdpConnection udpConnection) {
 if (udpConnection != nullptr) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.SyncCustomLightSettings.doPacket(byteBufferWriter);
 this->writeLightSwitchObjectHeader(byteBufferWriter,
 (byte)(this->Activated ? 1 : 0);
 byteBufferWriter.putBoolean(this->canBeModified);
 byteBufferWriter.putBoolean(this->useBattery);
 byteBufferWriter.putBoolean(this->hasBattery);
 byteBufferWriter.putByte((byte)(this->bulbItem != nullptr ? 1 : 0);
 if (this->bulbItem != nullptr) {
 GameWindow.WriteString(byteBufferWriter.bb, this->bulbItem);
 }

 byteBufferWriter.putFloat(this->power);
 byteBufferWriter.putFloat(this->delta);
 byteBufferWriter.putFloat(this->primaryR);
 byteBufferWriter.putFloat(this->primaryG);
 byteBufferWriter.putFloat(this->primaryB);
 PacketTypes.PacketType.SyncCustomLightSettings.send(udpConnection);
 }
 }

 void readCustomizedSettingsPacket(ByteBuffer byteBuffer) {
 this->Activated = byteBuffer.get() == 1;
 this->canBeModified = byteBuffer.get() == 1;
 this->useBattery = byteBuffer.get() == 1;
 this->hasBattery = byteBuffer.get() == 1;
 if (byteBuffer.get() == 1) {
 this->bulbItem = GameWindow.ReadString(byteBuffer);
 } else {
 this->bulbItem = nullptr;
 }

 this->power = byteBuffer.getFloat();
 this->delta = byteBuffer.getFloat();
 this->setPrimaryR(byteBuffer.getFloat());
 this->setPrimaryG(byteBuffer.getFloat());
 this->setPrimaryB(byteBuffer.getFloat());
 }

 void receiveSyncCustomizedSettings(ByteBuffer bb, UdpConnection connection) {
 if (GameClient.bClient) {
 this->readCustomizedSettingsPacket(bb);
 } else if (GameServer.bServer) {
 this->readCustomizedSettingsPacket(bb);
 this->syncCustomizedSettings(connection);
 }

 this->switchLight(this->Activated);
 }

 void writeLightSwitchObjectHeader(ByteBufferWriter byteBufferWriter,
 uint8_t byte0) {
 byteBufferWriter.putInt(this->square.getX());
 byteBufferWriter.putInt(this->square.getY());
 byteBufferWriter.putInt(this->square.getZ());
 byteBufferWriter.putByte((byte)this->square.getObjects().indexOf(this);
 byteBufferWriter.putByte(byte0);
 }

 void syncIsoObjectSend(ByteBufferWriter b) {
 b.putInt(this->square.getX());
 b.putInt(this->square.getY());
 b.putInt(this->square.getZ());
 uint8_t byte0 = (byte)this->square.getObjects().indexOf(this);
 b.putByte(byte0);
 b.putByte((byte)1);
 b.putByte((byte)(this->Activated ? 1 : 0);
 }

 void syncIsoObject(bool bRemote, uint8_t val, UdpConnection source,
 ByteBuffer bb) {
 this->syncIsoObject(bRemote, val, source);
 }

 void syncIsoObject(bool bRemote, uint8_t val, UdpConnection source) {
 if (this->square.empty()) {
 System.out.println("ERROR: " + this->getClass().getSimpleName() +
 " square is nullptr");
 } else if (this->getObjectIndex() == -1) {
 System.out.println("ERROR: " + this->getClass().getSimpleName() +
 " not found on square " + this->square.getX() + "," +
 this->square.getY() + "," + this->square.getZ());
 } else {
 if (GameClient.bClient && !bRemote) {
 ByteBufferWriter byteBufferWriter0 =
 GameClient.connection.startPacket();
 PacketTypes.PacketType.SyncIsoObject.doPacket(byteBufferWriter0);
 this->syncIsoObjectSend(byteBufferWriter0);
 PacketTypes.PacketType.SyncIsoObject.send(GameClient.connection);
 } else if (bRemote) {
 if (val == 1) {
 this->switchLight(true);
 this->Activated = true;
 } else {
 this->switchLight(false);
 this->Activated = false;
 }

 if (GameServer.bServer) {
 for (UdpConnection udpConnection : GameServer.udpEngine.connections) {
 if (source != nullptr) {
 if (udpConnection.getConnectedGUID() !=
 source.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter1 =
 udpConnection.startPacket();
 PacketTypes.PacketType.SyncIsoObject.doPacket(
 byteBufferWriter1);
 this->syncIsoObjectSend(byteBufferWriter1);
 PacketTypes.PacketType.SyncIsoObject.send(udpConnection);
 }
 } else if (udpConnection.RelevantTo(this->square.x, this->square.y) {
 ByteBufferWriter byteBufferWriter2 = udpConnection.startPacket();
 PacketTypes.PacketType.SyncIsoObject.doPacket(byteBufferWriter2);
 byteBufferWriter2.putInt(this->square.getX());
 byteBufferWriter2.putInt(this->square.getY());
 byteBufferWriter2.putInt(this->square.getZ());
 uint8_t byte0 = (byte)this->square.getObjects().indexOf(this);
 if (byte0 != -1) {
 byteBufferWriter2.putByte(byte0);
 } else {
 byteBufferWriter2.putByte(
 (byte)this->square.getObjects().size());
 }

 byteBufferWriter2.putByte((byte)1);
 byteBufferWriter2.putByte((byte)(this->Activated ? 1 : 0);
 PacketTypes.PacketType.SyncIsoObject.send(udpConnection);
 }
 }
 }
 }
 }
 }

 void update() {
 if (!GameServer.bServer && !GameClient.bClient || GameServer.bServer) {
 bool boolean0 = false;
 if (!this->Activated) {
 this->lastMinuteStamp = -1L;
 }

 if (!this->lightRoom && this->canBeModified && this->Activated) {
 if (this->lastMinuteStamp == -1L) {
 this->lastMinuteStamp = GameTime.instance.getMinutesStamp();
 }

 if (GameTime.instance.getMinutesStamp() > this->lastMinuteStamp) {
 if (this->bulbBurnMinutes == -1) {
 int int0 = SandboxOptions.instance.getElecShutModifier() * 24 * 60;
 if (this->lastMinuteStamp < int0) {
 this->bulbBurnMinutes = (int)this->lastMinuteStamp;
 } else {
 this->bulbBurnMinutes = int0;
 }
 }

 long long0 =
 GameTime.instance.getMinutesStamp() - this->lastMinuteStamp;
 this->lastMinuteStamp = GameTime.instance.getMinutesStamp();
 bool boolean1 = false;
 bool boolean2 = IsoWorld.instance.isHydroPowerOn();
 bool boolean3 = boolean2 ? this->square.getRoom() != nullptr
 : this->square.haveElectricity();
 bool boolean4 =
 this->useBattery && this->hasBattery && this->power > 0.0F;
 if (boolean4 || !this->useBattery && boolean3) {
 boolean1 = true;
 }

 double double0 = SandboxOptions.instance.LightBulbLifespan.getValue();
 if (double0 <= 0.0) {
 boolean1 = false;
 }

 if (this->Activated && this->hasLightBulb() && boolean1) {
 this->bulbBurnMinutes = (int)(this->bulbBurnMinutes + long0);
 }

 this->nextBreakUpdate = (int)(this->nextBreakUpdate - long0);
 if (this->nextBreakUpdate <= 0) {
 if (this->Activated && this->hasLightBulb() && boolean1) {
 int int1 = (int)(1000.0 * double0);
 if (int1 < 1) {
 int1 = 1;
 }

 int int2 = Rand.Next(0, int1);
 int int3 = this->bulbBurnMinutes / 10000;
 if (int2 < int3) {
 this->bulbBurnMinutes = 0;
 this->setActive(false, true, true);
 this->bulbItem = nullptr;
 IsoWorld.instance.getFreeEmitter().playSound(
 "LightbulbBurnedOut", this->square);
 boolean0 = true;
 if (Core.bDebug) {
 System.out.println("broke bulb at x=" + this->getX() + ", y=" +
 this->getY() + ", z=" + this->getZ());
 }
 }
 }

 this->nextBreakUpdate = 60;
 }

 if (this->Activated && boolean4 && this->hasLightBulb()) {
 float float0 = this->power - this->power % 0.01F;
 this->power = this->power - this->delta * (float)long0;
 if (this->power < 0.0F) {
 this->power = 0.0F;
 }

 if (long0 == 1L || this->power < float0) {
 boolean0 = true;
 }
 }
 }

 if (this->useBattery && this->Activated &&
 (this->power <= 0.0F || !this->hasBattery) {
 this->power = 0.0F;
 this->setActive(false, true, true);
 boolean0 = true;
 }
 }

 if (this->Activated && !this->hasLightBulb()) {
 this->setActive(false, true, true);
 boolean0 = true;
 }

 if (boolean0 && GameServer.bServer) {
 this->syncCustomizedSettings(nullptr);
 }
 }
 }

 bool isActivated() { return this->Activated; }

 void addToWorld() {
 if (!this->Activated) {
 this->lastMinuteStamp = -1L;
 }

 if (!this->lightRoom && !this->lights.empty()) {
 for (int int0 = 0; int0 < this->lights.size(); int0++) {
 IsoWorld.instance.CurrentCell.getLamppostPositions().add(
 this->lights.get(int0);
 }
 }

 if (this->getCell() != nullptr && this->canBeModified && !this->lightRoom &&
 (!GameServer.bServer && !GameClient.bClient || GameServer.bServer) {
 this->getCell().addToStaticUpdaterObjectList(this);
 }

 this->checkAmbientSound();
 }

 void removeFromWorld() {
 if (!this->lightRoom && !this->lights.empty()) {
 for (int int0 = 0; int0 < this->lights.size(); int0++) {
 this->lights.get(int0).setActive(false);
 IsoWorld.instance.CurrentCell.removeLamppost(this->lights.get(int0);
 }

 this->lights.clear();
 }

 if (this->square != nullptr && this->lightRoom) {
 IsoRoom room = this->square.getRoom();
 if (room != nullptr) {
 room.lightSwitches.remove(this);
 }
 }

 super.removeFromWorld();
 }

 static void chunkLoaded(IsoChunk chunk) {
 std::vector arrayList = new ArrayList();

 for (int int0 = 0; int0 < 10; int0++) {
 for (int int1 = 0; int1 < 10; int1++) {
 for (int int2 = 0; int2 < 8; int2++) {
 IsoGridSquare square = chunk.getGridSquare(int0, int1, int2);
 if (square != nullptr) {
 IsoRoom room0 = square.getRoom();
 if (room0 != nullptr && room0.hasLightSwitches() &&
 !arrayList.contains(room0) {
 arrayList.add(room0);
 }
 }
 }
 }
 }

 for (int int3 = 0; int3 < arrayList.size(); int3++) {
 IsoRoom room1 = (IsoRoom)arrayList.get(int3);
 room1.createLights(room1.def.bLightsActive);

 for (int int4 = 0; int4 < room1.roomLights.size(); int4++) {
 IsoRoomLight roomLight = room1.roomLights.get(int4);
 if (!chunk.roomLights.contains(roomLight) {
 chunk.roomLights.add(roomLight);
 }
 }
 }
 }

public
 ArrayList<IsoLightSource> getLights() { return this->lights; }
}
} // namespace objects
} // namespace iso
} // namespace zombie
