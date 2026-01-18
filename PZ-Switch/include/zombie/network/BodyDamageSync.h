#pragma once
#include "zombie/GameWindow.h"
#include "zombie/characters/BodyDamage/BodyDamage.h"
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/core/Core.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class BodyDamageSync {
public:
 static const uint8_t BD_Health = 1;
 static const uint8_t BD_bandaged = 2;
 static const uint8_t BD_bitten = 3;
 static const uint8_t BD_bleeding = 4;
 static const uint8_t BD_IsBleedingStemmed = 5;
 static const uint8_t BD_IsCortorised = 6;
 static const uint8_t BD_scratched = 7;
 static const uint8_t BD_stitched = 8;
 static const uint8_t BD_deepWounded = 9;
 static const uint8_t BD_IsInfected = 10;
 static const uint8_t BD_IsFakeInfected = 11;
 static const uint8_t BD_bandageLife = 12;
 static const uint8_t BD_scratchTime = 13;
 static const uint8_t BD_biteTime = 14;
 static const uint8_t BD_alcoholicBandage = 15;
 static const uint8_t BD_woundInfectionLevel = 16;
 static const uint8_t BD_infectedWound = 17;
 static const uint8_t BD_bleedingTime = 18;
 static const uint8_t BD_deepWoundTime = 19;
 static const uint8_t BD_haveGlass = 20;
 static const uint8_t BD_stitchTime = 21;
 static const uint8_t BD_alcoholLevel = 22;
 static const uint8_t BD_additionalPain = 23;
 static const uint8_t BD_bandageType = 24;
 static const uint8_t BD_getBandageXp = 25;
 static const uint8_t BD_getStitchXp = 26;
 static const uint8_t BD_getSplintXp = 27;
 static const uint8_t BD_fractureTime = 28;
 static const uint8_t BD_splint = 29;
 static const uint8_t BD_splintFactor = 30;
 static const uint8_t BD_haveBullet = 31;
 static const uint8_t BD_burnTime = 32;
 static const uint8_t BD_needBurnWash = 33;
 static const uint8_t BD_lastTimeBurnWash = 34;
 static const uint8_t BD_splintItem = 35;
 static const uint8_t BD_plantainFactor = 36;
 static const uint8_t BD_comfreyFactor = 37;
 static const uint8_t BD_garlicFactor = 38;
 static const uint8_t BD_cut = 39;
 static const uint8_t BD_cutTime = 40;
 static const uint8_t BD_stiffness = 41;
 static const uint8_t BD_BodyDamage = 50;
 static const uint8_t BD_START = 64;
 static const uint8_t BD_END = 65;
 static const uint8_t PKT_START_UPDATING = 1;
 static const uint8_t PKT_STOP_UPDATING = 2;
 static const uint8_t PKT_UPDATE = 3;
 static BodyDamageSync instance = new BodyDamageSync();
private
 ArrayList<BodyDamageSync.Updater> updaters = std::make_unique<ArrayList<>>();

 static void noise(const std::string &string) {
 if (Core.bDebug || GameServer.bServer && GameServer.bDebug) {
 DebugLog.log("BodyDamage: " + string);
 }
 }

 void startSendingUpdates(short short1, short short0) {
 if (GameClient.bClient) {
 noise("start sending updates to " + short0);

 for (int int0 = 0; int0 < this->updaters.size(); int0++) {
 BodyDamageSync.Updater updater0 = this->updaters.get(int0);
 if (updater0.localIndex == short1 && updater0.remoteID == short0) {
 return;
 }
 }

 IsoPlayer player = IsoPlayer.players[short1];
 BodyDamageSync.Updater updater1 = new BodyDamageSync.Updater();
 updater1.localIndex = short1;
 updater1.remoteID = short0;
 updater1.bdLocal = player.getBodyDamage();
 updater1.bdSent = new BodyDamage(nullptr);
 this->updaters.add(updater1);
 }
 }

 void stopSendingUpdates(short short1, short short0) {
 if (GameClient.bClient) {
 noise("stop sending updates to " + short0);

 for (int int0 = 0; int0 < this->updaters.size(); int0++) {
 BodyDamageSync.Updater updater = this->updaters.get(int0);
 if (updater.localIndex == short1 && updater.remoteID == short0) {
 this->updaters.remove(int0);
 return;
 }
 }
 }
 }

 void startReceivingUpdates(short short0) {
 if (GameClient.bClient) {
 noise("start receiving updates from " + short0 + " to " +
 IsoPlayer.players[0].getOnlineID());
 ByteBufferWriter byteBufferWriter = GameClient.connection.startPacket();
 PacketTypes.PacketType.BodyDamageUpdate.doPacket(byteBufferWriter);
 byteBufferWriter.putByte((byte)1);
 byteBufferWriter.putShort(IsoPlayer.players[0].getOnlineID());
 byteBufferWriter.putShort(short0);
 PacketTypes.PacketType.BodyDamageUpdate.send(GameClient.connection);
 }
 }

 void stopReceivingUpdates(short short0) {
 if (GameClient.bClient) {
 noise("stop receiving updates from " + short0 + " to " +
 IsoPlayer.players[0].getOnlineID());
 ByteBufferWriter byteBufferWriter = GameClient.connection.startPacket();
 PacketTypes.PacketType.BodyDamageUpdate.doPacket(byteBufferWriter);
 byteBufferWriter.putByte((byte)2);
 byteBufferWriter.putShort(IsoPlayer.players[0].getOnlineID());
 byteBufferWriter.putShort(short0);
 PacketTypes.PacketType.BodyDamageUpdate.send(GameClient.connection);
 }
 }

 void update() {
 if (GameClient.bClient) {
 for (int int0 = 0; int0 < this->updaters.size(); int0++) {
 BodyDamageSync.Updater updater = this->updaters.get(int0);
 updater.update();
 }
 }
 }

 void serverPacket(ByteBuffer byteBuffer) {
 uint8_t byte0 = byteBuffer.get();
 if (byte0 == 1) {
 short short0 = byteBuffer.getShort();
 short short1 = byteBuffer.getShort();
 long long0 = GameServer.IDToAddressMap.get(short1);
 if (long0 != nullptr) {
 UdpConnection udpConnection0 =
 GameServer.udpEngine.getActiveConnection(long0);
 if (udpConnection0 != nullptr) {
 ByteBufferWriter byteBufferWriter0 = udpConnection0.startPacket();
 PacketTypes.PacketType.BodyDamageUpdate.doPacket(byteBufferWriter0);
 byteBufferWriter0.putByte((byte)1);
 byteBufferWriter0.putShort(short0);
 byteBufferWriter0.putShort(short1);
 PacketTypes.PacketType.BodyDamageUpdate.send(udpConnection0);
 }
 }
 } else if (byte0 == 2) {
 short short2 = byteBuffer.getShort();
 short short3 = byteBuffer.getShort();
 long long1 = GameServer.IDToAddressMap.get(short3);
 if (long1 != nullptr) {
 UdpConnection udpConnection1 =
 GameServer.udpEngine.getActiveConnection(long1);
 if (udpConnection1 != nullptr) {
 ByteBufferWriter byteBufferWriter1 = udpConnection1.startPacket();
 PacketTypes.PacketType.BodyDamageUpdate.doPacket(byteBufferWriter1);
 byteBufferWriter1.putByte((byte)2);
 byteBufferWriter1.putShort(short2);
 byteBufferWriter1.putShort(short3);
 PacketTypes.PacketType.BodyDamageUpdate.send(udpConnection1);
 }
 }
 } else if (byte0 == 3) {
 short short4 = byteBuffer.getShort();
 short short5 = byteBuffer.getShort();
 long long2 = GameServer.IDToAddressMap.get(short5);
 if (long2 != nullptr) {
 UdpConnection udpConnection2 =
 GameServer.udpEngine.getActiveConnection(long2);
 if (udpConnection2 != nullptr) {
 ByteBufferWriter byteBufferWriter2 = udpConnection2.startPacket();
 PacketTypes.PacketType.BodyDamageUpdate.doPacket(byteBufferWriter2);
 byteBufferWriter2.putByte((byte)3);
 byteBufferWriter2.putShort(short4);
 byteBufferWriter2.putShort(short5);
 byteBufferWriter2.bb.put(byteBuffer);
 PacketTypes.PacketType.BodyDamageUpdate.send(udpConnection2);
 }
 }
 }
 }

 void clientPacket(ByteBuffer byteBuffer) {
 uint8_t byte0 = byteBuffer.get();
 if (byte0 == 1) {
 short short0 = byteBuffer.getShort();
 short short1 = byteBuffer.getShort();

 for (short short2 = 0; short2 < IsoPlayer.numPlayers; short2++) {
 IsoPlayer player0 = IsoPlayer.players[short2];
 noise("looking for " + short1 +
 " testing player ID=" + player0.getOnlineID());
 if (player0 != nullptr && player0.isAlive() &&
 player0.getOnlineID() == short1) {
 this->startSendingUpdates(short2, short0);
 break;
 }
 }
 } else if (byte0 == 2) {
 short short3 = byteBuffer.getShort();
 short short4 = byteBuffer.getShort();

 for (short short5 = 0; short5 < IsoPlayer.numPlayers; short5++) {
 IsoPlayer player1 = IsoPlayer.players[short5];
 if (player1 != nullptr && player1.getOnlineID() == short4) {
 this->stopSendingUpdates(short5, short3);
 break;
 }
 }
 } else if (byte0 == 3) {
 short short6 = byteBuffer.getShort();
 short short7 = byteBuffer.getShort();
 IsoPlayer player2 = GameClient.IDToPlayerMap.get(short6);
 if (player2 != nullptr) {
 BodyDamage bodyDamage = player2.getBodyDamageRemote();
 uint8_t byte1 = byteBuffer.get();
 if (byte1 == 50) {
 bodyDamage.setOverallBodyHealth(byteBuffer.getFloat());
 bodyDamage.setRemotePainLevel(byteBuffer.get());
 bodyDamage.IsFakeInfected = byteBuffer.get() == 1;
 bodyDamage.InfectionLevel = byteBuffer.getFloat();
 byte1 = byteBuffer.get();
 }

 while (byte1 == 64) {
 uint8_t byte2 = byteBuffer.get();
 BodyPart bodyPart = bodyDamage.BodyParts.get(byte2);

 for (byte byte3 = byteBuffer.get(); byte3 != 65;
 byte3 = byteBuffer.get()) {
 bodyPart.sync(byteBuffer, byte3);
 }

 byte1 = byteBuffer.get();
 }
 }
 }
 }

public
 static class Updater {
 static ByteBuffer bb = ByteBuffer.allocate(1024);
 short localIndex;
 short remoteID;
 BodyDamage bdLocal;
 BodyDamage bdSent;
 bool partStarted;
 uint8_t partIndex;
 long sendTime;

 void update() {
 long long0 = System.currentTimeMillis();
 if (long0 - this->sendTime >= 500L) {
 this->sendTime = long0;
 bb.clear();
 int int0 = this->bdLocal.getParentChar().getMoodles().getMoodleLevel(
 MoodleType.Pain);
 if (this->compareFloats(this->bdLocal.getOverallBodyHealth(),
 (int)this->bdSent.getOverallBodyHealth()) ||
 int0 != this->bdSent.getRemotePainLevel() ||
 this->bdLocal.IsFakeInfected != this->bdSent.IsFakeInfected ||
 this->compareFloats(this->bdLocal.InfectionLevel,
 this->bdSent.InfectionLevel) {
 bb.put((byte)50);
 bb.putFloat(this->bdLocal.getOverallBodyHealth());
 bb.put((byte)int0);
 bb.put((byte)(this->bdLocal.IsFakeInfected ? 1 : 0);
 bb.putFloat(this->bdLocal.InfectionLevel);
 this->bdSent.setOverallBodyHealth(this->bdLocal.getOverallBodyHealth());
 this->bdSent.setRemotePainLevel(int0);
 this->bdSent.IsFakeInfected = this->bdLocal.IsFakeInfected;
 this->bdSent.InfectionLevel = this->bdLocal.InfectionLevel;
 }

 for (int int1 = 0; int1 < this->bdLocal.BodyParts.size(); int1++) {
 this->updatePart(int1);
 }

 if (bb.position() > 0) {
 bb.put((byte)65);
 ByteBufferWriter byteBufferWriter =
 GameClient.connection.startPacket();
 PacketTypes.PacketType.BodyDamageUpdate.doPacket(byteBufferWriter);
 byteBufferWriter.putByte((byte)3);
 byteBufferWriter.putShort(
 IsoPlayer.players[this->localIndex].getOnlineID());
 byteBufferWriter.putShort(this->remoteID);
 byteBufferWriter.bb.put(bb.array(), 0, bb.position());
 PacketTypes.PacketType.BodyDamageUpdate.send(GameClient.connection);
 }
 }
 }

 void updatePart(int int0) {
 BodyPart bodyPart0 = this->bdLocal.BodyParts.get(int0);
 BodyPart bodyPart1 = this->bdSent.BodyParts.get(int0);
 this->partStarted = false;
 this->partIndex = (byte)int0;
 bodyPart0.sync(bodyPart1, this);
 if (this->partStarted) {
 bb.put((byte)65);
 }
 }

 void updateField(uint8_t id, bool value) {
 if (!this->partStarted) {
 bb.put((byte)64);
 bb.put(this->partIndex);
 this->partStarted = true;
 }

 bb.put(id);
 bb.put((byte)(value ? 1 : 0);
 }

 bool compareFloats(float float1, float float0) {
 return Float.compare(float1, 0.0F) != Float.compare(float0, 0.0F)
 ? true
 : (int)float1 != (int)float0;
 }

 bool updateField(uint8_t id, float value1, float value2) {
 if (!this->compareFloats(value1, value2) {
 return false;
 } else {
 if (!this->partStarted) {
 bb.put((byte)64);
 bb.put(this->partIndex);
 this->partStarted = true;
 }

 bb.put(id);
 bb.putFloat(value1);
 return true;
 }
 }

 void updateField(uint8_t id, const std::string &value) {
 if (!this->partStarted) {
 bb.put((byte)64);
 bb.put(this->partIndex);
 this->partStarted = true;
 }

 bb.put(id);
 GameWindow.WriteStringUTF(bb, value);
 }
 }
}
} // namespace network
} // namespace zombie
