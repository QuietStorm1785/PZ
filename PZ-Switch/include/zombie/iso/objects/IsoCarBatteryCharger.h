#pragma once
#include "zombie/GameTime.h"
#include "zombie/core/Core.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/skinnedmodel/model/WorldItemModelDrawer.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
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

class IsoCarBatteryCharger : public IsoObject {
public:
 InventoryItem item;
 InventoryItem battery;
 bool activated;
 float lastUpdate = -1.0F;
 float chargeRate = 0.16666667F;
 IsoSprite chargerSprite;
 IsoSprite batterySprite;
 long sound = 0L;

public
 IsoCarBatteryCharger(IsoCell cell) { super(cell); }

public
 IsoCarBatteryCharger(InventoryItem _item, IsoCell cell,
 IsoGridSquare square) {
 super(cell, square, (IsoSprite) nullptr);
 if (_item.empty()) {
 throw NullPointerException("item is nullptr");
 } else {
 this->item = _item;
 }
 }

 std::string getObjectName() { return "IsoCarBatteryCharger"; }

 void load(ByteBuffer bb, int WorldVersion, bool IS_DEBUG_SAVE) {
 super.load(bb, WorldVersion, IS_DEBUG_SAVE);
 if (bb.get() == 1) {
 try {
 this->item = InventoryItem.loadItem(bb, WorldVersion);
 } catch (Exception exception0) {
 exception0.printStackTrace();
 }
 }

 if (bb.get() == 1) {
 try {
 this->battery = InventoryItem.loadItem(bb, WorldVersion);
 } catch (Exception exception1) {
 exception1.printStackTrace();
 }
 }

 this->activated = bb.get() == 1;
 this->lastUpdate = bb.getFloat();
 this->chargeRate = bb.getFloat();
 }

 void save(ByteBuffer bb, bool IS_DEBUG_SAVE) {
 super.save(bb, IS_DEBUG_SAVE);
 if (this->item.empty()) {
 assert false;

 bb.put((byte)0);
 } else {
 bb.put((byte)1);
 this->item.saveWithSize(bb, false);
 }

 if (this->battery.empty()) {
 bb.put((byte)0);
 } else {
 bb.put((byte)1);
 this->battery.saveWithSize(bb, false);
 }

 bb.put((byte)(this->activated ? 1 : 0);
 bb.putFloat(this->lastUpdate);
 bb.putFloat(this->chargeRate);
 }

 void addToWorld() {
 super.addToWorld();
 this->getCell().addToProcessIsoObject(this);
 }

 void removeFromWorld() {
 this->stopChargingSound();
 super.removeFromWorld();
 }

 void update() {
 super.update();
 if (!(this->battery instanceof DrainableComboItem) {
 this->battery = nullptr;
 }

 if (this->battery.empty()) {
 this->lastUpdate = -1.0F;
 this->activated = false;
 this->stopChargingSound();
 } else {
 bool boolean0 =
 this->square != nullptr &&
 (this->square.haveElectricity() ||
 IsoWorld.instance.isHydroPowerOn() && this->square.getRoom() != nullptr);
 if (!boolean0) {
 this->activated = false;
 }

 if (!this->activated) {
 this->lastUpdate = -1.0F;
 this->stopChargingSound();
 } else {
 this->startChargingSound();
 DrainableComboItem drainableComboItem =
 (DrainableComboItem)this->battery;
 if (!(drainableComboItem.getUsedDelta() >= 1.0F) {
 float float0 = (float)GameTime.getInstance().getWorldAgeHours();
 if (this->lastUpdate < 0.0F) {
 this->lastUpdate = float0;
 }

 if (this->lastUpdate > float0) {
 this->lastUpdate = float0;
 }

 float float1 = float0 - this->lastUpdate;
 if (float1 > 0.0F) {
 drainableComboItem.setUsedDelta(
 Math.min(1.0F, drainableComboItem.getUsedDelta() +
 this->chargeRate * float1);
 this->lastUpdate = float0;
 }
 }
 }
 }
 }

 void render(float x, float y, float z, ColorInfo col, bool bDoChild,
 bool bWallLightingPass, Shader shader) {
 this->chargerSprite = this->configureSprite(this->item, this->chargerSprite);
 if (this->chargerSprite.CurrentAnim != nullptr &&
 !this->chargerSprite.CurrentAnim.Frames.empty()) {
 Texture texture =
 this->chargerSprite.CurrentAnim.Frames.get(0).getTexture(this->dir);
 if (texture != nullptr) {
 float float0 =
 texture.getWidthOrig() * this->chargerSprite.def.getScaleX() / 2.0F;
 float float1 = texture.getHeightOrig() *
 this->chargerSprite.def.getScaleY() * 3.0F / 4.0F;
 this->offsetX = this->offsetY = 0.0F;
 this->setAlpha(IsoCamera.frameState.playerIndex, 1.0F);
 float float2 = 0.5F;
 float float3 = 0.5F;
 float float4 = 0.0F;
 this->sx = 0.0F;
 this->item.setWorldZRotation(315);
 if (!WorldItemModelDrawer.renderMain(
 this->getItem(), this->getSquare(), this->getX() + float2,
 this->getY() + float3, this->getZ() + float4, -1.0F) {
 this->chargerSprite.render(
 this, x + float2, y + float3, z + float4, this->dir,
 this->offsetX + float0 + 8 * Core.TileScale,
 this->offsetY + float1 + 4 * Core.TileScale, col, true);
 }

 if (this->battery != nullptr) {
 this->batterySprite =
 this->configureSprite(this->battery, this->batterySprite);
 if (this->batterySprite != nullptr &&
 this->batterySprite.CurrentAnim != nullptr &&
 !this->batterySprite.CurrentAnim.Frames.empty()) {
 this->sx = 0.0F;
 this->getBattery().setWorldZRotation(90);
 if (!WorldItemModelDrawer.renderMain(
 this->getBattery(), this->getSquare(), this->getX() + 0.75F,
 this->getY() + 0.75F, this->getZ() + float4, -1.0F) {
 this->batterySprite.render(
 this, x + float2, y + float3, z + float4, this->dir,
 this->offsetX + float0 - 8.0F + Core.TileScale,
 this->offsetY + float1 - 4 * Core.TileScale, col, true);
 }
 }
 }
 }
 }
 }

 void renderObjectPicker(float x, float y, float z, ColorInfo lightInfo) {}

 IsoSprite configureSprite(InventoryItem itemx, IsoSprite sprite) {
 std::string string = itemx.getWorldTexture();

 try {
 Texture texture0 = Texture.getSharedTexture(string);
 if (texture0.empty()) {
 string = itemx.getTex().getName();
 }
 } catch (Exception exception) {
 string = "media/inventory/world/WItem_Sack.png";
 }

 Texture texture1 = Texture.getSharedTexture(string);
 bool boolean0 = false;
 if (sprite.empty()) {
 sprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
 }

 if (sprite.CurrentAnim.empty()) {
 sprite.LoadFramesNoDirPageSimple(string);
 sprite.CurrentAnim.name = string;
 boolean0 = true;
 } else if (!string == sprite.CurrentAnim.name) {
 sprite.ReplaceCurrentAnimFrames(string);
 sprite.CurrentAnim.name = string;
 boolean0 = true;
 }

 if (boolean0) {
 if (itemx.getScriptItem() == nullptr) {
 sprite.def.scaleAspect(texture1.getWidthOrig(),
 texture1.getHeightOrig(), 16 * Core.TileScale,
 16 * Core.TileScale);
 } else if (this->battery != nullptr &&
 this->battery.getScriptItem() != nullptr) {
 float float0 = Core.TileScale;
 float float1 =
 this->battery.getScriptItem().ScaleWorldIcon * (float0 / 2.0F);
 sprite.def.setScale(float1, float1);
 }
 }

 return sprite;
 }

 void syncIsoObjectSend(ByteBufferWriter b) {
 uint8_t byte0 = (byte)this->getObjectIndex();
 b.putInt(this->square.getX());
 b.putInt(this->square.getY());
 b.putInt(this->square.getZ());
 b.putByte(byte0);
 b.putByte((byte)1);
 b.putByte((byte)0);
 if (this->battery.empty()) {
 b.putByte((byte)0);
 } else {
 b.putByte((byte)1);

 try {
 this->battery.saveWithSize(b.bb, false);
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }
 }

 b.putBoolean(this->activated);
 b.putFloat(this->chargeRate);
 }

 void syncIsoObject(bool bRemote, uint8_t val, UdpConnection source,
 ByteBuffer bb) {
 if (GameClient.bClient && !bRemote) {
 ByteBufferWriter byteBufferWriter0 = GameClient.connection.startPacket();
 PacketTypes.PacketType.SyncIsoObject.doPacket(byteBufferWriter0);
 this->syncIsoObjectSend(byteBufferWriter0);
 PacketTypes.PacketType.SyncIsoObject.send(GameClient.connection);
 } else if (GameServer.bServer && !bRemote) {
 for (UdpConnection udpConnection0 : GameServer.udpEngine.connections) {
 ByteBufferWriter byteBufferWriter1 = udpConnection0.startPacket();
 PacketTypes.PacketType.SyncIsoObject.doPacket(byteBufferWriter1);
 this->syncIsoObjectSend(byteBufferWriter1);
 PacketTypes.PacketType.SyncIsoObject.send(udpConnection0);
 }
 } else if (bRemote) {
 if (bb.get() == 1) {
 try {
 this->battery = InventoryItem.loadItem(bb, 195);
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 } else {
 this->battery = nullptr;
 }

 this->activated = bb.get() == 1;
 this->chargeRate = bb.getFloat();
 if (GameServer.bServer) {
 for (UdpConnection udpConnection1 : GameServer.udpEngine.connections) {
 if (source != nullptr && udpConnection1 != source) {
 ByteBufferWriter byteBufferWriter2 = udpConnection1.startPacket();
 PacketTypes.PacketType.SyncIsoObject.doPacket(byteBufferWriter2);
 this->syncIsoObjectSend(byteBufferWriter2);
 PacketTypes.PacketType.SyncIsoObject.send(udpConnection1);
 }
 }
 }
 }
 }

 void sync() { this->syncIsoObject(false, (byte)0, nullptr, nullptr); }

 InventoryItem getItem() { return this->item; }

 InventoryItem getBattery() { return this->battery; }

 void setBattery(InventoryItem _battery) {
 if (_battery != nullptr) {
 if (!(_battery instanceof DrainableComboItem) {
 throw IllegalArgumentException("battery isn't DrainableComboItem");
 }

 if (this->battery != nullptr) {
 throw IllegalStateException("battery already inserted");
 }
 }

 this->battery = _battery;
 }

 bool isActivated() { return this->activated; }

 void setActivated(bool _activated) { this->activated = _activated; }

 float getChargeRate() { return this->chargeRate; }

 void setChargeRate(float _chargeRate) {
 if (_chargeRate <= 0.0F) {
 throw IllegalArgumentException("chargeRate <= 0.0f");
 } else {
 this->chargeRate = _chargeRate;
 }
 }

 void startChargingSound() {
 if (!GameServer.bServer) {
 if (this->getObjectIndex() != -1) {
 if (this->sound != -1L) {
 if (this->emitter.empty()) {
 this->emitter = IsoWorld.instance.getFreeEmitter(
 this->square.x + 0.5F, this->square.y + 0.5F, this->square.z);
 IsoWorld.instance.takeOwnershipOfEmitter(this->emitter);
 }

 if (!this->emitter.isPlaying(this->sound) {
 this->sound = this->emitter.playSound("CarBatteryChargerRunning");
 if (this->sound == 0L) {
 this->sound = -1L;
 }
 }

 this->emitter.tick();
 }
 }
 }
 }

 void stopChargingSound() {
 if (!GameServer.bServer) {
 if (this->emitter != nullptr) {
 this->emitter.stopOrTriggerSound(this->sound);
 this->sound = 0L;
 IsoWorld.instance.returnOwnershipOfEmitter(this->emitter);
 this->emitter = nullptr;
 }
 }
 }
}
} // namespace objects
} // namespace iso
} // namespace zombie
