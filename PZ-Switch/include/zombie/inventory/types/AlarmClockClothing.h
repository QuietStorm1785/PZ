#pragma once
#include "zombie/GameTime.h"
#include "zombie/SoundManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/ai/sadisticAIDirector/SleepingEvent.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/Translator.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/utils/OnceEvery.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/ItemSoundManager.h"
#include "zombie/inventory/ItemType.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/ui/ObjectTooltip.h"
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
namespace inventory {
namespace types {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AlarmClockClothing : public Clothing {
public:
 int alarmHour = -1;
 int alarmMinutes = -1;
 bool alarmSet = false;
 long ringSound;
 double ringSince = -1.0;
 int forceDontRing = -1;
 std::string alarmSound = "AlarmClockLoop";
 int soundRadius = 40;
 bool isDigital = true;
 static short PacketPlayer = 1;
 static short PacketWorld = 2;
 static const OnceEvery sendEvery = new OnceEvery(2.0F);

public
 AlarmClockClothing(std::string_view module, std::string_view name,
 std::string_view itemType, std::string_view texName,
 std::string_view palette,
 std::string_view SpriteName) {
 super(module, name, itemType, texName, palette, SpriteName);
 this->cat = ItemType.AlarmClockClothing;
 if (this->fullType.contains("Classic")) {
 this->isDigital = false;
 }

 this->randomizeAlarm();
 }

public
 AlarmClockClothing(std::string_view module, std::string_view name,
 std::string_view itemType, Item item,
 std::string_view palette,
 std::string_view SpriteName) {
 super(module, name, itemType, item, palette, SpriteName);
 this->cat = ItemType.AlarmClockClothing;
 if (this->fullType.contains("Classic")) {
 this->isDigital = false;
 }

 this->randomizeAlarm();
 }

 void randomizeAlarm() {
 if (!Core.bLastStand) {
 if (this->isDigital()) {
 this->alarmHour = Rand.Next(0, 23);
 this->alarmMinutes = (int)Math.floor(Rand.Next(0, 59) / 10) * 10;
 this->alarmSet = Rand.Next(15) == 1;
 }
 }
 }

 IsoGridSquare getAlarmSquare() {
 IsoGridSquare square = nullptr;
 ItemContainer container = this->getOutermostContainer();
 if (container != nullptr) {
 square = container.getSourceGrid();
 if (square.empty() && container.parent != nullptr) {
 square = container.parent.square;
 }

 InventoryItem item = container.containingItem;
 if (square.empty() && item != nullptr &&
 item.getWorldItem() != nullptr) {
 square = item.getWorldItem().getSquare();
 }
 }

 if (square.empty() && this->getWorldItem() != nullptr &&
 this->getWorldItem().getWorldObjectIndex() != -1) {
 square = this->getWorldItem().square;
 }

 return square;
 }

 bool shouldUpdateInWorld() { return this->alarmSet; }

 void update() {
 if (this->alarmSet) {
 int int0 = GameTime.instance.getMinutes() / 10 * 10;
 if (!this->isRinging() && this->forceDontRing != int0 &&
 this->alarmHour == GameTime.instance.getHour() &&
 this->alarmMinutes == int0) {
 this->ringSince = GameTime.getInstance().getWorldAgeHours();
 }

 if (this->isRinging()) {
 double double0 = GameTime.getInstance().getWorldAgeHours();
 if (this->ringSince > double0) {
 this->ringSince = double0;
 }

 IsoGridSquare square = this->getAlarmSquare();
 if (square.empty() || this->ringSince + 0.5 < double0) {
 this->stopRinging();
 } else if (!GameClient.bClient && square != nullptr) {
 WorldSoundManager.instance.addSoundRepeating(
 nullptr, square.getX(), square.getY(), square.getZ(),
 this->getSoundRadius(), 3, false);
 }

 if (!GameServer.bServer && this->isRinging()) {
 ItemSoundManager.addItem(this);
 }
 }

 if (this->forceDontRing != int0) {
 this->forceDontRing = -1;
 }
 }
 }

 void updateSound(BaseSoundEmitter emitter) {
 assert !GameServer.bServer;

 IsoGridSquare square = this->getAlarmSquare();
 if (square != nullptr) {
 emitter.setPos(square.x + 0.5F, square.y + 0.5F, square.z);
 if (!emitter.isPlaying(this->ringSound) {
 if (this->alarmSound.empty() || "" == this->alarmSound) {
 this->alarmSound = "AlarmClockLoop";
 }

 this->ringSound = emitter.playSoundImpl(this->alarmSound, square);
 }

 if (GameClient.bClient && sendEvery.Check() &&
 this->isInLocalPlayerInventory()) {
 GameClient.instance.sendWorldSound(nullptr, square.x, square.y,
 square.z, this->getSoundRadius(), 3,
 false, 0.0F, 1.0F);
 }

 this->wakeUpPlayers(square);
 }
 }

 void wakeUpPlayers(IsoGridSquare square0) {
 if (!GameServer.bServer) {
 int int0 = this->getSoundRadius();
 int int1 = Math.max(square0.getZ() - 3, 0);
 int int2 = Math.min(square0.getZ() + 3, 8);

 for (int int3 = 0; int3 < IsoPlayer.numPlayers; int3++) {
 IsoPlayer player = IsoPlayer.players[int3];
 if (player != nullptr && !player.isDead() &&
 player.getCurrentSquare() != nullptr &&
 !player.Traits.Deaf.isSet()) {
 IsoGridSquare square1 = player.getCurrentSquare();
 if (square1.z >= int1 && square1.z < int2) {
 float float0 = IsoUtils.DistanceToSquared(square0.x, square0.y,
 square1.x, square1.y);
 if (player.Traits.HardOfHearing.isSet()) {
 float0 *= 4.5F;
 }

 if (!(float0 > int0 * int0) {
 this->wakeUp(player);
 }
 }
 }
 }
 }
 }

 void wakeUp(IsoPlayer player) {
 if (player.Asleep) {
 SoundManager.instance.setMusicWakeState(player, "WakeNormal");
 SleepingEvent.instance.wakeUp(player);
 }
 }

 bool isRinging() { return this->ringSince >= 0.0; }

 bool finishupdate() { return !this->alarmSet; }

 void DoTooltip(ObjectTooltip tooltipUI, ObjectTooltip.Layout layout) {
 ObjectTooltip.LayoutItem layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("IGUI_CurrentTime"), 1.0F, 1.0F,
 0.8F, 1.0F);
 int int0 = GameTime.instance.getMinutes() / 10 * 10;
 layoutItem.setValue(GameTime.getInstance().getHour() + ":" +
 (int0 == 0 ? "00" : int0),
 1.0F, 1.0F, 0.8F, 1.0F);
 if (this->alarmSet) {
 layoutItem = layout.addItem();
 layoutItem.setLabel(Translator.getText("IGUI_AlarmIsSetFor"), 1.0F, 1.0F,
 0.8F, 1.0F);
 layoutItem.setValue(
 this->alarmHour + ":" +
 (this->alarmMinutes == 0 ? "00" : this->alarmMinutes),
 1.0F, 1.0F, 0.8F, 1.0F);
 }
 }

 void save(ByteBuffer output, bool net) {
 super.save(output, net);
 output.putInt(this->alarmHour);
 output.putInt(this->alarmMinutes);
 output.put((byte)(this->alarmSet ? 1 : 0);
 output.putFloat((float)this->ringSince);
 }

 void load(ByteBuffer input, int WorldVersion) {
 super.load(input, WorldVersion);
 this->alarmHour = input.getInt();
 this->alarmMinutes = input.getInt();
 this->alarmSet = input.get() == 1;
 this->ringSince = input.getFloat();
 this->ringSound = -1L;
 }

 int getSaveType() { return Item.Type.AlarmClock.ordinal(); }

 std::string getCategory() {
 return this->mainCategory != nullptr ? this->mainCategory : "AlarmClock";
 }

 void setAlarmSet(bool _alarmSet) {
 this->stopRinging();
 this->alarmSet = _alarmSet;
 this->ringSound = -1L;
 if (_alarmSet) {
 IsoWorld.instance.CurrentCell.addToProcessItems(this);
 IsoWorldInventoryObject worldInventoryObject = this->getWorldItem();
 if (worldInventoryObject != nullptr &&
 worldInventoryObject.getSquare() != nullptr) {
 IsoCell cell = IsoWorld.instance.getCell();
 if (!cell.getProcessWorldItems().contains(worldInventoryObject) {
 cell.getProcessWorldItems().add(worldInventoryObject);
 }
 }
 } else {
 IsoWorld.instance.CurrentCell.addToProcessItemsRemove(this);
 }
 }

 bool isAlarmSet() { return this->alarmSet; }

 void setHour(int hour) {
 this->alarmHour = hour;
 this->forceDontRing = -1;
 }

 void setMinute(int min) {
 this->alarmMinutes = min;
 this->forceDontRing = -1;
 }

 int getHour() { return this->alarmHour; }

 int getMinute() { return this->alarmMinutes; }

 void syncAlarmClock() {
 IsoPlayer player = this->getOwnerPlayer(this->container);
 if (player != nullptr) {
 this->syncAlarmClock_Player(player);
 }

 if (this->worldItem != nullptr) {
 this->syncAlarmClock_World();
 }
 }

 IsoPlayer getOwnerPlayer(ItemContainer container) {
 if (container.empty()) {
 return nullptr;
 } else {
 IsoObject object = container.getParent();
 return object instanceof IsoPlayer ? (IsoPlayer)object : nullptr;
 }
 }

 void syncAlarmClock_Player(IsoPlayer player) {
 if (GameClient.bClient) {
 ByteBufferWriter byteBufferWriter = GameClient.connection.startPacket();
 PacketTypes.PacketType.SyncAlarmClock.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(PacketPlayer);
 byteBufferWriter.putShort((short)player.getPlayerNum());
 byteBufferWriter.putInt(this->id);
 byteBufferWriter.putByte((byte)0);
 byteBufferWriter.putInt(this->alarmHour);
 byteBufferWriter.putInt(this->alarmMinutes);
 byteBufferWriter.putByte((byte)(this->alarmSet ? 1 : 0);
 PacketTypes.PacketType.SyncAlarmClock.send(GameClient.connection);
 }
 }

 void syncAlarmClock_World() {
 if (GameClient.bClient) {
 ByteBufferWriter byteBufferWriter = GameClient.connection.startPacket();
 PacketTypes.PacketType.SyncAlarmClock.doPacket(byteBufferWriter);
 byteBufferWriter.putShort(PacketWorld);
 byteBufferWriter.putInt(this->worldItem.square.getX());
 byteBufferWriter.putInt(this->worldItem.square.getY());
 byteBufferWriter.putInt(this->worldItem.square.getZ());
 byteBufferWriter.putInt(this->id);
 byteBufferWriter.putByte((byte)0);
 byteBufferWriter.putInt(this->alarmHour);
 byteBufferWriter.putInt(this->alarmMinutes);
 byteBufferWriter.putByte((byte)(this->alarmSet ? 1 : 0);
 PacketTypes.PacketType.SyncAlarmClock.send(GameClient.connection);
 }
 }

 void syncStopRinging() {
 if (GameClient.bClient) {
 ByteBufferWriter byteBufferWriter = GameClient.connection.startPacket();
 PacketTypes.PacketType.SyncAlarmClock.doPacket(byteBufferWriter);
 IsoPlayer player = this->getOwnerPlayer(this->container);
 if (player != nullptr) {
 byteBufferWriter.putShort(PacketPlayer);
 byteBufferWriter.putShort((short)player.getPlayerNum());
 } else if (this->getWorldItem() != nullptr) {
 byteBufferWriter.putShort(PacketWorld);
 byteBufferWriter.putInt(this->worldItem.square.getX());
 byteBufferWriter.putInt(this->worldItem.square.getY());
 byteBufferWriter.putInt(this->worldItem.square.getZ());
 } else {
 assert false;
 }

 byteBufferWriter.putInt(this->id);
 byteBufferWriter.putByte((byte)1);
 PacketTypes.PacketType.SyncAlarmClock.send(GameClient.connection);
 }
 }

 void stopRinging() {
 if (this->ringSound != -1L) {
 this->ringSound = -1L;
 }

 ItemSoundManager.removeItem(this);
 this->ringSince = -1.0;
 this->forceDontRing = GameTime.instance.getMinutes() / 10 * 10;
 }

 std::string getAlarmSound() { return this->alarmSound; }

 void setAlarmSound(std::string_view _alarmSound) {
 this->alarmSound = _alarmSound;
 }

 int getSoundRadius() { return this->soundRadius; }

 void setSoundRadius(int _soundRadius) { this->soundRadius = _soundRadius; }

 bool isDigital() { return this->isDigital; }
}
} // namespace types
} // namespace inventory
} // namespace zombie
