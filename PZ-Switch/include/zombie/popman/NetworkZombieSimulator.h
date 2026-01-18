#pragma once
#include <mutex>
#include "com/google/common/collect/Sets.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/ai/states/ZombieHitReactionState.h"
#include "zombie/ai/states/ZombieOnGroundState.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/NetworkZombieVariables.h"
#include "zombie/core/Core.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/utils/UpdateLimit.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/DebugType.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/network/packets/ZombiePacket.h"
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace popman {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class NetworkZombieSimulator {
public:

 // Mutexes for synchronized blocks
 std::mutex authoriseZombies_mutex;
 static const int MAX_ZOMBIES_PER_UPDATE = 300;
 static const NetworkZombieSimulator instance = new NetworkZombieSimulator();
 static const ZombiePacket zombiePacket = new ZombiePacket();
 const ByteBuffer bb = ByteBuffer.allocate(1000000);
private
 ArrayList<Short> unknownZombies = std::make_unique<ArrayList<>>();
private
 HashSet<Short> authoriseZombies = std::make_unique<HashSet<>>();
private
 ArrayDeque<IsoZombie> SendQueue = std::make_unique<ArrayDeque<>>();
private
 ArrayDeque<IsoZombie> ExtraSendQueue = std::make_unique<ArrayDeque<>>();
private
 HashSet<Short> authoriseZombiesCurrent = std::make_unique<HashSet<>>();
private
 HashSet<Short> authoriseZombiesLast = std::make_unique<HashSet<>>();
 UpdateLimit ZombieSimulationReliableLimit = new UpdateLimit(1000L);

 static NetworkZombieSimulator getInstance() { return instance; }

 int getAuthorizedZombieCount() {
 return (int)IsoWorld.instance.CurrentCell.getZombieList()
 .stream()
 .filter(zombie0->zombie0.authOwner == GameClient.connection)
 .count();
 }

 int getUnauthorizedZombieCount() {
 return (int)IsoWorld.instance.CurrentCell.getZombieList()
 .stream()
 .filter(zombie0->zombie0.authOwner.empty())
 .count();
 }

 void clear() {
 std::unordered_set hashSet = this->authoriseZombiesCurrent;
 this->authoriseZombiesCurrent = this->authoriseZombiesLast;
 this->authoriseZombiesLast = hashSet;
 this->authoriseZombiesLast.removeIf(short0->GameClient.getZombie(short0) ==
 nullptr);
 this->authoriseZombiesCurrent.clear();
 }

 void addExtraUpdate(IsoZombie zombie0) {
 if (zombie0.authOwner == GameClient.connection &&
 !this->ExtraSendQueue.contains(zombie0) {
 this->ExtraSendQueue.add(zombie0);
 }
 }

 void add(short short0) { this->authoriseZombiesCurrent.add(short0); }

 void added() {
 for (Short short0 : Sets.difference(this->authoriseZombiesCurrent,
 this->authoriseZombiesLast) {
 IsoZombie zombie0 = GameClient.getZombie(short0);
 if (zombie0 != nullptr && zombie0.OnlineID == short0) {
 this->becomeLocal(zombie0);
 } else if (!this->unknownZombies.contains(short0) {
 this->unknownZombies.add(short0);
 }
 }

 for (Short short1 : Sets.difference(this->authoriseZombiesLast,
 this->authoriseZombiesCurrent) {
 IsoZombie zombie1 = GameClient.getZombie(short1);
 if (zombie1 != nullptr) {
 this->becomeRemote(zombie1);
 }
 }

 { std::lock_guard<std::mutex> __sync_lock__(authoriseZombies_mutex);
 this->authoriseZombies.clear();
 this->authoriseZombies.addAll(this->authoriseZombiesCurrent);
 }
 }

 void becomeLocal(IsoZombie zombie0) {
 zombie0.lastRemoteUpdate = 0;
 zombie0.authOwner = GameClient.connection;
 zombie0.authOwnerPlayer = IsoPlayer.getInstance();
 zombie0.networkAI.setUpdateTimer(0.0F);
 zombie0.AllowRepathDelay = 0.0F;
 zombie0.networkAI.mindSync.restorePFBTarget();
 }

 void becomeRemote(IsoZombie zombie0) {
 if (zombie0.isDead() && zombie0.authOwner == GameClient.connection) {
 zombie0.getNetworkCharacterAI().setLocal(true);
 }

 zombie0.lastRemoteUpdate = 0;
 zombie0.authOwner = nullptr;
 zombie0.authOwnerPlayer = nullptr;
 if (zombie0.group != nullptr) {
 zombie0.group.remove(zombie0);
 }
 }

 bool isZombieSimulated(short short0) {
 { std::lock_guard<std::mutex> __sync_lock__(authoriseZombies_mutex);
 return this->authoriseZombies.contains(short0);
 }
 }

 void receivePacket(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 if (DebugOptions.instance.Network.Client.UpdateZombiesFromPacket
 .getValue()) {
 short short0 = byteBuffer.getShort();

 for (short short1 = 0; short1 < short0; short1++) {
 this->parseZombie(byteBuffer, udpConnection);
 }
 }
 }

 void parseZombie(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 ZombiePacket zombiePacketx = zombiePacket;
 zombiePacketx.parse(byteBuffer, udpConnection);
 if (zombiePacketx.id == -1) {
 DebugLog.General.error("NetworkZombieSimulator.parseZombie id=" +
 zombiePacketx.id);
 } else {
 try {
 IsoZombie zombie0 = GameClient.IDToZombieMap.get(zombiePacketx.id);
 if (zombie0.empty()) {
 if (IsoDeadBody.isDead(zombiePacketx.id) {
 DebugLog.Death.debugln("Skip dead zombie creation id=%d",
 zombiePacketx.id);
 return;
 }

 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(
 (double)zombiePacketx.realX, (double)zombiePacketx.realY,
 (double)zombiePacketx.realZ);
 if (square != nullptr) {
 VirtualZombieManager.instance.choices.clear();
 VirtualZombieManager.instance.choices.add(square);
 zombie0 = VirtualZombieManager.instance.createRealZombieAlways(
 zombiePacketx.descriptorID, IsoDirections.getRandom().index(),
 false);
 DebugLog.log(DebugType.ActionSystem,
 "ParseZombie: CreateRealZombieAlways id=" +
 zombiePacketx.id);
 if (zombie0 != nullptr) {
 zombie0.setFakeDead(false);
 zombie0.OnlineID = zombiePacketx.id;
 GameClient.IDToZombieMap.put(zombiePacketx.id, zombie0);
 zombie0.lx = zombie0.nx = zombie0.x = zombiePacketx.realX;
 zombie0.ly = zombie0.ny = zombie0.y = zombiePacketx.realY;
 zombie0.lz = zombie0.z = zombiePacketx.realZ;
 zombie0.setForwardDirection(zombie0.dir.ToVector());
 zombie0.setCurrent(square);
 zombie0.networkAI.targetX = zombiePacketx.x;
 zombie0.networkAI.targetY = zombiePacketx.y;
 zombie0.networkAI.targetZ = zombiePacketx.z;
 zombie0.networkAI.predictionType = zombiePacketx.moveType;
 zombie0.networkAI.reanimatedBodyID =
 zombiePacketx.reanimatedBodyID;
 NetworkZombieVariables.setInt(zombie0, (short)0,
 zombiePacketx.realHealth);
 NetworkZombieVariables.setInt(zombie0, (short)2,
 zombiePacketx.speedMod);
 NetworkZombieVariables.setInt(zombie0, (short)1,
 zombiePacketx.target);
 NetworkZombieVariables.setInt(zombie0, (short)3,
 zombiePacketx.timeSinceSeenFlesh);
 NetworkZombieVariables.setInt(zombie0, (short)4,
 zombiePacketx.smParamTargetAngle);
 NetworkZombieVariables.setBooleanVariables(
 zombie0, zombiePacketx.booleanVariables);
 if (zombie0.isKnockedDown()) {
 zombie0.setOnFloor(true);
 zombie0.changeState(ZombieOnGroundState.instance());
 }

 zombie0.setWalkType(zombiePacketx.walkType.toString());
 zombie0.realState = zombiePacketx.realState;
 if (zombie0.isReanimatedPlayer()) {
 IsoDeadBody deadBody =
 IsoDeadBody.getDeadBody(zombie0.networkAI.reanimatedBodyID);
 if (deadBody != nullptr) {
 zombie0.setDir(deadBody.getDir());
 zombie0.setForwardDirection(deadBody.getDir().ToVector());
 zombie0.setFallOnFront(deadBody.isFallOnFront());
 }

 zombie0.getStateMachine().changeState(
 ZombieOnGroundState.instance(), nullptr);
 zombie0.bNeverDoneAlpha = false;
 }

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player = IsoPlayer.players[int0];
 if (square.isCanSee(int0) {
 zombie0.setAlphaAndTarget(int0, 1.0F);
 }

 if (player != nullptr &&
 player.ReanimatedCorpseID == zombiePacketx.id &&
 zombiePacketx.id != -1) {
 player.ReanimatedCorpseID = -1;
 player.ReanimatedCorpse = zombie0;
 }
 }

 zombie0.networkAI.mindSync.parse(zombiePacketx);
 } else {
 DebugLog.log("Error: VirtualZombieManager can't create zombie");
 }
 }

 if (zombie0.empty()) {
 return;
 }
 }

 if (getInstance().isZombieSimulated(zombie0.OnlineID) {
 zombie0.authOwner = GameClient.connection;
 zombie0.authOwnerPlayer = IsoPlayer.getInstance();
 return;
 }

 zombie0.authOwner = nullptr;
 zombie0.authOwnerPlayer = nullptr;
 if (!zombie0.networkAI.isSetVehicleHit() ||
 !zombie0.isCurrentState(ZombieHitReactionState.instance())) {
 zombie0.networkAI.parse(zombiePacketx);
 zombie0.networkAI.mindSync.parse(zombiePacketx);
 }

 zombie0.lastRemoteUpdate = 0;
 if (!IsoWorld.instance.CurrentCell.getZombieList().contains(zombie0) {
 IsoWorld.instance.CurrentCell.getZombieList().add(zombie0);
 }

 if (!IsoWorld.instance.CurrentCell.getObjectList().contains(zombie0) {
 IsoWorld.instance.CurrentCell.getObjectList().add(zombie0);
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }
 }

 bool anyUnknownZombies() { return this->unknownZombies.size() > 0; }

 void send() {
 if (this->authoriseZombies.size() != 0 || this->unknownZombies.size() != 0) {
 if (this->SendQueue.empty()) {
 { std::lock_guard<std::mutex> __sync_lock__(authoriseZombies_mutex);
 for (Short short0 : this->authoriseZombies) {
 IsoZombie zombie0 = GameClient.getZombie(short0);
 if (zombie0 != nullptr && zombie0.OnlineID != -1) {
 this->SendQueue.add(zombie0);
 }
 }
 }
 }

 this->bb.clear();
 { std::lock_guard<std::mutex> __sync_lock__(ZombieCountOptimiser.zombiesForDelete_mutex);
 int int0 = ZombieCountOptimiser.zombiesForDelete.size();
 this->bb.putShort((short)int0);

 for (int int1 = 0; int1 < int0; int1++) {
 this->bb.putShort(
 ZombieCountOptimiser.zombiesForDelete.get(int1).OnlineID);
 }

 ZombieCountOptimiser.zombiesForDelete.clear();
 }

 int int2 = this->unknownZombies.size();
 this->bb.putShort((short)int2);

 for (int int3 = 0; int3 < int2; int3++) {
 this->bb.putShort(this->unknownZombies.get(int3);
 }

 this->unknownZombies.clear();
 int int4 = this->bb.position();
 this->bb.putShort((short)300);
 int int5 = 0;

 while (!this->SendQueue.empty()) {
 IsoZombie zombie1 = this->SendQueue.poll();
 this->ExtraSendQueue.remove(zombie1);
 zombie1.zombiePacket.set(zombie1);
 if (zombie1.OnlineID != -1) {
 zombie1.zombiePacket.write(this->bb);
 zombie1.networkAI.targetX = zombie1.realx = zombie1.x;
 zombie1.networkAI.targetY = zombie1.realy = zombie1.y;
 zombie1.networkAI.targetZ = zombie1.realz = (byte)zombie1.z;
 zombie1.realdir = zombie1.getDir();
 if (++int5 >= 300) {
 break;
 }
 }
 }

 if (int5 < 300) {
 int int6 = this->bb.position();
 this->bb.position(int4);
 this->bb.putShort((short)int5);
 this->bb.position(int6);
 }

 if (int5 > 0 || int2 > 0) {
 ByteBufferWriter byteBufferWriter0 =
 GameClient.connection.startPacket();
 PacketTypes.PacketType packetType;
 if (int2 > 0 && this->ZombieSimulationReliableLimit.Check()) {
 packetType = PacketTypes.PacketType.ZombieSimulationReliable;
 } else {
 packetType = PacketTypes.PacketType.ZombieSimulation;
 }

 packetType.doPacket(byteBufferWriter0);
 byteBufferWriter0.bb.put(this->bb.array(), 0, this->bb.position());
 packetType.send(GameClient.connection);
 }

 if (!this->ExtraSendQueue.empty()) {
 this->bb.clear();
 this->bb.putShort((short)0);
 this->bb.putShort((short)0);
 int4 = this->bb.position();
 this->bb.putShort((short)0);
 int int7 = 0;

 while (!this->ExtraSendQueue.empty()) {
 IsoZombie zombie2 = this->ExtraSendQueue.poll();
 zombie2.zombiePacket.set(zombie2);
 if (zombie2.OnlineID != -1) {
 zombie2.zombiePacket.write(this->bb);
 zombie2.networkAI.targetX = zombie2.realx = zombie2.x;
 zombie2.networkAI.targetY = zombie2.realy = zombie2.y;
 zombie2.networkAI.targetZ = zombie2.realz = (byte)zombie2.z;
 zombie2.realdir = zombie2.getDir();
 int7++;
 }
 }

 int int8 = this->bb.position();
 this->bb.position(int4);
 this->bb.putShort((short)int7);
 this->bb.position(int8);
 if (int7 > 0) {
 ByteBufferWriter byteBufferWriter1 =
 GameClient.connection.startPacket();
 PacketTypes.PacketType.ZombieSimulation.doPacket(byteBufferWriter1);
 byteBufferWriter1.bb.put(this->bb.array(), 0, this->bb.position());
 PacketTypes.PacketType.ZombieSimulation.send(GameClient.connection);
 }
 }
 }
 }

 void remove(IsoZombie zombie0) {
 if (zombie0 != nullptr && zombie0.OnlineID != -1) {
 GameClient.IDToZombieMap.remove(zombie0.OnlineID);
 }
 }

 void clearTargetAuth(IsoPlayer player) {
 if (Core.bDebug) {
 DebugLog.log(DebugType.Multiplayer,
 "Clear zombies target and auth for player id=" +
 player.getOnlineID());
 }

 if (GameClient.bClient) {
 for (IsoZombie zombie0 : GameClient.IDToZombieMap.valueCollection()) {
 if (zombie0.target == player) {
 zombie0.setTarget(nullptr);
 }
 }
 }
 }
}
} // namespace popman
} // namespace zombie
