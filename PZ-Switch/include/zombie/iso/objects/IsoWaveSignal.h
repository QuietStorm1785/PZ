#pragma once
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/Talker.h"
#include "zombie/chat/ChatElement.h"
#include "zombie/chat/ChatElementOwner.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/types/Radio.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoLightSource.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/radio/devices/DeviceData.h"
#include "zombie/radio/devices/PresetEntry.h"
#include "zombie/radio/devices/WaveSignalDevice.h"
#include "zombie/ui/UIFont.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Turbo
 */
class IsoWaveSignal : public IsoObject {
public:
 IsoLightSource lightSource = nullptr;
 bool lightWasRemoved = false;
 int lightSourceRadius = 4;
 float nextLightUpdate = 0.0F;
 float lightUpdateCnt = 0.0F;
 DeviceData deviceData = nullptr;
 bool displayRange = false;
 bool hasPlayerInRange = false;
 GameTime gameTime;
 ChatElement chatElement;
 std::string talkerType = "device";
protected
 static Map<String, DeviceData> deviceDataCache =
 std::make_unique<HashMap<>>();

public
 IsoWaveSignal(IsoCell cell) {
 super(cell);
 this->init(true);
 }

public
 IsoWaveSignal(IsoCell cell, IsoGridSquare sq, IsoSprite spr) {
 super(cell, sq, spr);
 this->init(false);
 }

 void init(bool boolean0) {
 this->chatElement = new ChatElement(this, 5, this->talkerType);
 this->gameTime = GameTime.getInstance();
 if (!boolean0) {
 if (this->sprite != nullptr && this->sprite.getProperties() != nullptr) {
 PropertyContainer propertyContainer = this->sprite.getProperties();
 if (propertyContainer.Is("CustomItem") &&
 propertyContainer.Val("CustomItem") != nullptr) {
 this->deviceData =
 this->cloneDeviceDataFromItem(propertyContainer.Val("CustomItem"));
 }
 }

 if (!GameClient.bClient && this->deviceData != nullptr) {
 this->deviceData.generatePresets();
 this->deviceData.setDeviceVolume(Rand.Next(0.1F, 1.0F);
 this->deviceData.setRandomChannel();
 if (Rand.Next(100) <= 35 && !"Tutorial" == Core.GameMode) {
 this->deviceData.setTurnedOnRaw(true);
 if (this instanceof IsoRadio) {
 this->deviceData.setInitialPower();
 if (this->deviceData.getIsBatteryPowered() &&
 this->deviceData.getPower() <= 0.0F) {
 this->deviceData.setTurnedOnRaw(false);
 }
 }
 }
 }
 }

 if (this->deviceData.empty()) {
 this->deviceData = new DeviceData(this);
 }

 this->deviceData.setParent(this);
 }

 DeviceData cloneDeviceDataFromItem(std::string_view itemfull) {
 if (itemfull != nullptr) {
 if (deviceDataCache.containsKey(itemfull) &&
 deviceDataCache.get(itemfull) != nullptr) {
 return deviceDataCache.get(itemfull).getClone();
 }

 InventoryItem item = InventoryItemFactory.CreateItem(itemfull);
 if (item != nullptr && item instanceof Radio) {
 DeviceData deviceDatax = ((Radio)item).getDeviceData();
 if (deviceDatax != nullptr) {
 deviceDataCache.put(itemfull, deviceDatax);
 return deviceDatax.getClone();
 }
 }
 }

 return nullptr;
 }

 bool hasChatToDisplay() { return this->chatElement.getHasChatToDisplay(); }

 bool HasPlayerInRange() { return this->hasPlayerInRange; }

 float getDelta() {
 return this->deviceData != nullptr ? this->deviceData.getPower() : 0.0F;
 }

 void setDelta(float delta) {
 if (this->deviceData != nullptr) {
 this->deviceData.setPower(delta);
 }
 }

 DeviceData getDeviceData() { return this->deviceData; }

 void setDeviceData(DeviceData data) {
 if (data.empty()) {
 data = new DeviceData(this);
 }

 this->deviceData = data;
 this->deviceData.setParent(this);
 }

 bool IsSpeaking() { return this->chatElement.IsSpeaking(); }

 std::string getTalkerType() { return this->chatElement.getTalkerType(); }

 void setTalkerType(std::string_view type) {
 this->talkerType = type.empty() ? "" : type;
 this->chatElement.setTalkerType(this->talkerType);
 }

 std::string getSayLine() { return this->chatElement.getSayLine(); }

 void Say(std::string_view line) {
 this->AddDeviceText(line, 1.0F, 1.0F, 1.0F, nullptr, nullptr, -1, false);
 }

 void AddDeviceText(std::string_view line, float r, float g, float b,
 std::string_view guid, std::string_view codes,
 int distance) {
 this->AddDeviceText(line, r, g, b, guid, codes, distance, true);
 }

 void AddDeviceText(std::string_view line, int r, int g, int b,
 std::string_view guid, std::string_view codes,
 int distance) {
 this->AddDeviceText(line, r / 255.0F, g / 255.0F, b / 255.0F, guid, codes,
 distance, true);
 }

 void AddDeviceText(std::string_view line, int r, int g, int b,
 std::string_view guid, std::string_view codes,
 int distance, bool attractZombies) {
 this->AddDeviceText(line, r / 255.0F, g / 255.0F, b / 255.0F, guid, codes,
 distance, attractZombies);
 }

 void AddDeviceText(std::string_view line, float r, float g, float b,
 std::string_view guid, std::string_view codes,
 int distance, bool attractZombies) {
 if (this->deviceData != nullptr && this->deviceData.getIsTurnedOn()) {
 if (!ZomboidRadio.isStaticSound(line) {
 this->deviceData.doReceiveSignal(distance);
 }

 if (this->deviceData.getDeviceVolume() > 0.0F) {
 this->chatElement.addChatLine(line, r, g, b, UIFont.Medium,
 this->deviceData.getDeviceVolumeRange(),
 "default", true, true, true, true, true,
 true);
 if (codes != nullptr) {
 LuaEventManager.triggerEvent("OnDeviceText", guid, codes, this->getX(),
 this->getY(), this->getZ(), line, this);
 }
 }
 }
 }

 void renderlast() {
 if (this->chatElement.getHasChatToDisplay()) {
 if (this->getDeviceData() != nullptr &&
 !this->getDeviceData().getIsTurnedOn()) {
 this->chatElement.clear(IsoCamera.frameState.playerIndex);
 return;
 }

 float float0 =
 IsoUtils.XToScreen(this->getX(), this->getY(), this->getZ(), 0);
 float float1 =
 IsoUtils.YToScreen(this->getX(), this->getY(), this->getZ(), 0);
 float0 = float0 - IsoCamera.getOffX() - this->offsetX;
 float1 = float1 - IsoCamera.getOffY() - this->offsetY;
 float0 += 32 * Core.TileScale;
 float1 += 50 * Core.TileScale;
 float0 /= Core.getInstance().getZoom(IsoPlayer.getPlayerIndex());
 float1 /= Core.getInstance().getZoom(IsoPlayer.getPlayerIndex());
 this->chatElement.renderBatched(IsoPlayer.getPlayerIndex(), (int)float0,
 (int)float1);
 }
 }

 void renderlastold2() {
 if (this->chatElement.getHasChatToDisplay()) {
 float float0 =
 IsoUtils.XToScreen(this->getX(), this->getY(), this->getZ(), 0);
 float float1 =
 IsoUtils.YToScreen(this->getX(), this->getY(), this->getZ(), 0);
 float0 = float0 - IsoCamera.getOffX() - this->offsetX;
 float1 = float1 - IsoCamera.getOffY() - this->offsetY;
 float0 += 28.0F;
 float1 += 180.0F;
 float0 /= Core.getInstance().getZoom(IsoPlayer.getPlayerIndex());
 float1 /= Core.getInstance().getZoom(IsoPlayer.getPlayerIndex());
 float0 += IsoCamera.getScreenLeft(IsoPlayer.getPlayerIndex());
 float1 += IsoCamera.getScreenTop(IsoPlayer.getPlayerIndex());
 this->chatElement.renderBatched(IsoPlayer.getPlayerIndex(), (int)float0,
 (int)float1);
 }
 }

 bool playerWithinBounds(IsoPlayer player, float float0) {
 return player.empty() ? false
 : (player.getX() > this->getX() - float0 ||
 player.getX() < this->getX() + float0) &&
 (player.getY() > this->getY() - float0 ||
 player.getY() < this->getY() + float0);
 }

 void update() {
 if (this->deviceData != nullptr) {
 if ((GameServer.bServer || GameClient.bClient) && !GameServer.bServer) {
 this->deviceData.updateSimple();
 } else {
 this->deviceData.update(true, this->hasPlayerInRange);
 }

 if (!GameServer.bServer) {
 this->hasPlayerInRange = false;
 if (this->deviceData.getIsTurnedOn()) {
 IsoPlayer player = IsoPlayer.getInstance();
 if (this->playerWithinBounds(
 player, this->deviceData.getDeviceVolumeRange() * 0.6F) {
 this->hasPlayerInRange = true;
 }

 this->updateLightSource();
 } else {
 this->removeLightSourceFromWorld();
 }

 this->chatElement.setHistoryRange(
 this->deviceData.getDeviceVolumeRange() * 0.6F);
 this->chatElement.update();
 } else {
 this->hasPlayerInRange = false;
 }
 }
 }

 void updateLightSource() {}

 void removeLightSourceFromWorld() {
 if (this->lightSource != nullptr) {
 IsoWorld.instance.CurrentCell.removeLamppost(this->lightSource);
 this->lightSource = nullptr;
 }
 }

 void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 super.load(input, WorldVersion, IS_DEBUG_SAVE);
 if (this->deviceData.empty()) {
 this->deviceData = new DeviceData(this);
 }

 if (input.get() == 1) {
 this->deviceData.load(input, WorldVersion, true);
 }

 this->deviceData.setParent(this);
 }

 void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 super.save(output, IS_DEBUG_SAVE);
 if (this->deviceData != nullptr) {
 output.put((byte)1);
 this->deviceData.save(output, true);
 } else {
 output.put((byte)0);
 }
 }

 void addToWorld() {
 if (!GameServer.bServer) {
 ZomboidRadio.getInstance().RegisterDevice(this);
 }

 if (this->getCell() != nullptr) {
 this->getCell().addToStaticUpdaterObjectList(this);
 }

 super.addToWorld();
 }

 void removeFromWorld() {
 if (!GameServer.bServer) {
 ZomboidRadio.getInstance().UnRegisterDevice(this);
 }

 this->removeLightSourceFromWorld();
 this->lightSource = nullptr;
 if (this->deviceData != nullptr) {
 this->deviceData.cleanSoundsAndEmitter();
 }

 super.removeFromWorld();
 }

 void removeFromSquare() {
 super.removeFromSquare();
 this->square = nullptr;
 }

 void saveState(ByteBuffer bb) {
 if (this->deviceData != nullptr) {
 std::vector arrayList = this->deviceData.getDevicePresets().getPresets();
 bb.putInt(arrayList.size());

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 PresetEntry presetEntry = (PresetEntry)arrayList.get(int0);
 GameWindow.WriteString(bb, presetEntry.getName());
 bb.putInt(presetEntry.getFrequency());
 }

 bb.put((byte)(this->deviceData.getIsTurnedOn() ? 1 : 0);
 bb.putInt(this->deviceData.getChannel());
 bb.putFloat(this->deviceData.getDeviceVolume());
 }
 }

 void loadState(ByteBuffer bb) {
 std::vector arrayList = this->deviceData.getDevicePresets().getPresets();
 int int0 = bb.getInt();

 for (int int1 = 0; int1 < int0; int1++) {
 std::string string = GameWindow.ReadString(bb);
 int int2 = bb.getInt();
 if (int1 < arrayList.size()) {
 PresetEntry presetEntry = (PresetEntry)arrayList.get(int1);
 presetEntry.setName(string);
 presetEntry.setFrequency(int2);
 } else {
 this->deviceData.getDevicePresets().addPreset(string, int2);
 }
 }

 while (arrayList.size() > int0) {
 this->deviceData.getDevicePresets().removePreset(int0);
 }

 this->deviceData.setTurnedOnRaw(bb.get() == 1);
 this->deviceData.setChannelRaw(bb.getInt());
 this->deviceData.setDeviceVolumeRaw(bb.getFloat());
 }

 ChatElement getChatElement() { return this->chatElement; }

 static void Reset() { deviceDataCache.clear(); }
}
} // namespace objects
} // namespace iso
} // namespace zombie
