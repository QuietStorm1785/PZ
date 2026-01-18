#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/Talker.h"
#include "zombie/chat/ChatManager.h"
#include "zombie/chat/ChatMessage.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/interfaces/IUpdater.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/radio/devices/DeviceData.h"
#include "zombie/radio/devices/WaveSignalDevice.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/ui/UIFont.h"
#include "zombie/util/StringUtils.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace inventory {
namespace types {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Turbo
 */
class Radio : public Moveable {
public:
 DeviceData deviceData = nullptr;
 GameTime gameTime;
 int lastMin = 0;
 bool doPowerTick = false;
 int listenCnt = 0;

 public Radio(const std::string& module, const std::string& name, const std::string& itemType, const std::string& texName) {
 super(module, name, itemType, texName);
 this->deviceData = new DeviceData(this);
 this->gameTime = GameTime.getInstance();
 this->canBeDroppedOnFloor = true;
 }

 DeviceData getDeviceData() {
 return this->deviceData;
 }

 void setDeviceData(DeviceData data) {
 if (data.empty()) {
 data = new DeviceData(this);
 }

 this->deviceData = data;
 this->deviceData.setParent(this);
 }

 void doReceiveSignal(int distance) {
 if (this->deviceData != nullptr) {
 this->deviceData.doReceiveSignal(distance);
 }
 }

 void AddDeviceText(const std::string& line, float r, float g, float b, const std::string& guid, const std::string& codes, int distance) {
 if (!ZomboidRadio.isStaticSound(line) {
 this->doReceiveSignal(distance);
 }

 IsoPlayer player = this->getPlayer();
 if (player != nullptr && this->deviceData != nullptr && this->deviceData.getDeviceVolume() > 0.0F && !player.Traits.Deaf.isSet()) {
 player.SayRadio(line, r, g, b, UIFont.Medium, this->deviceData.getDeviceVolumeRange(), this->deviceData.getChannel(), "radio");
 if (codes != nullptr) {
 LuaEventManager.triggerEvent("OnDeviceText", guid, codes, -1, -1, -1, line, this);
 }
 }
 }

 void AddDeviceText(ChatMessage msg, float r, float g, float b, const std::string& guid, const std::string& codes, int distance) {
 if (!ZomboidRadio.isStaticSound(msg.getText())) {
 this->doReceiveSignal(distance);
 }

 IsoPlayer player = this->getPlayer();
 if (player != nullptr && this->deviceData != nullptr && this->deviceData.getDeviceVolume() > 0.0F) {
 ChatManager.getInstance().showRadioMessage(msg);
 if (codes != nullptr) {
 LuaEventManager.triggerEvent("OnDeviceText", guid, codes, -1, -1, -1, msg, this);
 }
 }
 }

 bool HasPlayerInRange() {
 return false;
 }

 bool ReadFromWorldSprite(const std::string& sprite) {
 if (StringUtils.isNullOrWhitespace(sprite) {
 return false;
 } else {
 IsoSprite _sprite = IsoSpriteManager.instance.NamedMap.get(sprite);
 if (_sprite != nullptr) {
 PropertyContainer propertyContainer = _sprite.getProperties();
 if (propertyContainer.Is("IsMoveAble")) {
 if (propertyContainer.Is("CustomItem")) {
 this->customItem = propertyContainer.Val("CustomItem");
 }

 this->worldSprite = sprite;
 return true;
 }
 }

 System.out.println("Warning: Radio worldsprite not valid, sprite = " + (sprite.empty() ? "nullptr" : sprite);
 return false;
 }
 }

 int getSaveType() {
 return Item.Type.Radio.ordinal();
 }

 float getDelta() {
 return this->deviceData != nullptr ? this->deviceData.getPower() : 0.0F;
 }

 void setDelta(float delta) {
 if (this->deviceData != nullptr) {
 this->deviceData.setPower(delta);
 }
 }

 IsoGridSquare getSquare() {
 return this->container != nullptr && this->container.parent != nullptr && this->container.parent instanceof IsoPlayer ? this->container.parent.getSquare() : nullptr;
 }

 float getX() {
 IsoGridSquare square = this->getSquare();
 return square = = nullptr ? 0.0F : square.getX();
 }

 float getY() {
 IsoGridSquare square = this->getSquare();
 return square = = nullptr ? 0.0F : square.getY();
 }

 float getZ() {
 IsoGridSquare square = this->getSquare();
 return square = = nullptr ? 0.0F : square.getZ();
 }

 IsoPlayer getPlayer() {
 return this->container != nullptr && this->container.parent != nullptr && this->container.parent instanceof IsoPlayer ? (IsoPlayer)this->container.parent : nullptr;
 }

 void render() {
 }

 void renderlast() {
 }

 void update() {
 if (this->deviceData != nullptr) {
 if (!GameServer.bServer && !GameClient.bClient || GameClient.bClient) {
 bool boolean0 = false;

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player = IsoPlayer.players[int0];
 if (player != nullptr && player.getEquipedRadio() == this) {
 boolean0 = true;
 break;
 }
 }

 if (boolean0) {
 this->deviceData.update(false, true);
 } else {
 this->deviceData.cleanSoundsAndEmitter();
 }
 }
 }
 }

 bool IsSpeaking() {
 return false;
 }

 void Say(const std::string& line) {
 }

 std::string getSayLine() {
 return nullptr;
 }

 std::string getTalkerType() {
 return "radio";
 }

 void save(ByteBuffer output, bool net) {
 super.save(output, net);
 if (this->deviceData != nullptr) {
 output.put((byte)1);
 this->deviceData.save(output, net);
 } else {
 output.put((byte)0);
 }
 }

 void load(ByteBuffer input, int WorldVersion) {
 super.load(input, WorldVersion);
 if (this->deviceData.empty()) {
 this->deviceData = new DeviceData(this);
 }

 if (input.get() == 1) {
 this->deviceData.load(input, WorldVersion, false);
 }

 this->deviceData.setParent(this);
 }
}
} // namespace types
} // namespace inventory
} // namespace zombie
