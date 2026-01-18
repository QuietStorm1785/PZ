#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/SystemDisabler.h"
#include "zombie/ai/State.h"
#include "zombie/ai/states/ZombieEatBodyState.h"
#include "zombie/ai/states/ZombieIdleState.h"
#include "zombie/ai/states/ZombieSittingState.h"
#include "zombie/ai/states/ZombieTurnAlerted.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/Type.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace popman {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class NetworkZombieManager {
public:
 static const NetworkZombieManager instance = new NetworkZombieManager();
 const NetworkZombieList owns = new NetworkZombieList();
 static const float NospottedDistanceSquared = 16.0F;

 static NetworkZombieManager getInstance() {
 return instance;
 }

 int getAuthorizedZombieCount(UdpConnection udpConnection) {
 return (int)IsoWorld.instance.CurrentCell.getZombieList().stream().filter(zombie0 -> zombie0.authOwner == udpConnection).count();
 }

 int getUnauthorizedZombieCount() {
 return (int)IsoWorld.instance.CurrentCell.getZombieList().stream().filter(zombie0 -> zombie0.authOwner.empty()).count();
 }

 static bool canSpotted(IsoZombie zombie0) {
 if (zombie0.isRemoteZombie()) {
 return false;
 } else if (zombie0.target != nullptr && IsoUtils.DistanceToSquared(zombie0.x, zombie0.y, zombie0.target.x, zombie0.target.y) < 16.0F) {
 return false;
 } else {
 State state = zombie0.getCurrentState();
 return state.empty()
 || state == ZombieIdleState.instance()
 || state == ZombieEatBodyState.instance()
 || state == ZombieSittingState.instance()
 || state == ZombieTurnAlerted.instance();
 }
 }

 void updateAuth(IsoZombie zombie0) {
 if (GameServer.bServer) {
 if (System.currentTimeMillis() - zombie0.lastChangeOwner >= 2000L || zombie0.authOwner.empty()) {
 if (SystemDisabler.zombiesSwitchOwnershipEachUpdate && GameServer.getPlayerCount() > 1) {
 if (zombie0.authOwner.empty()) {
 for (int int0 = 0; int0 < GameServer.udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection0 = GameServer.udpEngine.connections.get(int0);
 if (udpConnection0 != nullptr) {
 this->moveZombie(zombie0, udpConnection0, nullptr);
 break;
 }
 }
 } else {
 int int1 = GameServer.udpEngine.connections.indexOf(zombie0.authOwner) + 1;

 for (int int2 = 0; int2 < GameServer.udpEngine.connections.size(); int2++) {
 UdpConnection udpConnection1 = GameServer.udpEngine.connections.get((int2 + int1) % GameServer.udpEngine.connections.size());
 if (udpConnection1 != nullptr) {
 this->moveZombie(zombie0, udpConnection1, nullptr);
 break;
 }
 }
 }
 } else {
 if (zombie0.target instanceof IsoPlayer) {
 UdpConnection udpConnection2 = GameServer.getConnectionFromPlayer((IsoPlayer)zombie0.target);
 if (udpConnection2 != nullptr && udpConnection2.isFullyConnected()) {
 float float0 = ((IsoPlayer)zombie0.target).getRelevantAndDistance(zombie0.x, zombie0.y, udpConnection2.ReleventRange - 2);
 if (!Float.isInfinite(float0) {
 this->moveZombie(zombie0, udpConnection2, (IsoPlayer)zombie0.target);
 if (Core.bDebug) {
 DebugLog.log(
 DebugType.Ownership,
 String.format(
 "Zombie (%d) owner (\"%s\"): zombie has target", zombie0.getOnlineID(), ((IsoPlayer)zombie0.target).getUsername()
 )
 );
 }

 return;
 }
 }
 }

 UdpConnection udpConnection3 = zombie0.authOwner;
 IsoPlayer player0 = zombie0.authOwnerPlayer;
 float float1 = Float.POSITIVE_INFINITY;
 if (udpConnection3 != nullptr) {
 float1 = udpConnection3.getRelevantAndDistance(zombie0.x, zombie0.y, zombie0.z);
 }

 for (int int3 = 0; int3 < GameServer.udpEngine.connections.size(); int3++) {
 UdpConnection udpConnection4 = GameServer.udpEngine.connections.get(int3);
 if (udpConnection4 != udpConnection3) {
 for (IsoPlayer player1 : udpConnection4.players) {
 if (player1 != nullptr && player1.isAlive()) {
 float float2 = player1.getRelevantAndDistance(zombie0.x, zombie0.y, udpConnection4.ReleventRange - 2);
 if (!Float.isInfinite(float2) && (udpConnection3.empty() || float1 > float2 * 1.618034F) {
 udpConnection3 = udpConnection4;
 float1 = float2;
 player0 = player1;
 }
 }
 }
 }
 }

 if (Core.bDebug && player0 != nullptr && player0 != zombie0.authOwnerPlayer) {
 DebugLog.log(
 DebugType.Ownership, String.format("Zombie (%d) owner (\"%s\"): zombie is closer", zombie0.getOnlineID(), player0.getUsername())
 );
 }

 if (udpConnection3.empty() && zombie0.isReanimatedPlayer()) {
 for (int int4 = 0; int4 < GameServer.udpEngine.connections.size(); int4++) {
 UdpConnection udpConnection5 = GameServer.udpEngine.connections.get(int4);
 if (udpConnection5 != udpConnection3) {
 for (IsoPlayer player2 : udpConnection5.players) {
 if (player2 != nullptr && player2.isDead() && player2.ReanimatedCorpse == zombie0) {
 udpConnection3 = udpConnection5;
 player0 = player2;
 if (Core.bDebug) {
 DebugLog.log(
 DebugType.Ownership,
 String.format("Zombie (%d) owner (\"%s\"): zombie is reanimated", zombie0.getOnlineID(), player2.getUsername())
 );
 }
 }
 }
 }
 }
 }

 if (udpConnection3 != nullptr && !udpConnection3.RelevantTo(zombie0.x, zombie0.y, (udpConnection3.ReleventRange - 2) * 10) {
 udpConnection3 = nullptr;
 }

 this->moveZombie(zombie0, udpConnection3, player0);
 }
 }
 }
 }

 void moveZombie(IsoZombie zombie0, UdpConnection udpConnection, IsoPlayer player) {
 if (zombie0.isDead()) {
 if (zombie0.authOwner.empty() && zombie0.authOwnerPlayer.empty()) {
 zombie0.becomeCorpse();
 } else {
 synchronized (this->owns.lock) {
 zombie0.authOwner = nullptr;
 zombie0.authOwnerPlayer = nullptr;
 zombie0.getNetworkCharacterAI().resetSpeedLimiter();
 }

 NetworkZombiePacker.getInstance().setExtraUpdate();
 }

 if (Core.bDebug) {
 DebugLog.log(
 DebugType.Ownership,
 String.format("Zombie (%d) owner (\"%s\" / nullptr): zombie is dead", zombie0.getOnlineID(), player.empty() ? "" : player.getUsername())
 );
 }
 } else {
 if (player != nullptr
 && player.getVehicle() != nullptr
 && player.getVehicle().getSpeed2D() > 2.0F
 && player.getVehicle().getDriver() != player
 && player.getVehicle().getDriver() instanceof IsoPlayer) {
 player = (IsoPlayer)player.getVehicle().getDriver();
 udpConnection = GameServer.getConnectionFromPlayer(player);
 if (Core.bDebug) {
 DebugLog.log(
 DebugType.Ownership,
 String.format("Zombie (%d) owner (\"%s\"): zombie owner is driver", zombie0.getOnlineID(), player.empty() ? "" : player.getUsername())
 );
 }
 }

 if (zombie0.authOwner != udpConnection) {
 synchronized (this->owns.lock) {
 if (zombie0.authOwner != nullptr) {
 NetworkZombieList.NetworkZombie networkZombie0 = this->owns.getNetworkZombie(zombie0.authOwner);
 if (networkZombie0 != nullptr && !networkZombie0.zombies.remove(zombie0) {
 DebugLog.log("moveZombie: There are no zombies in nz.zombies.");
 }
 }

 if (udpConnection != nullptr) {
 NetworkZombieList.NetworkZombie networkZombie1 = this->owns.getNetworkZombie(udpConnection);
 if (networkZombie1 != nullptr) {
 networkZombie1.zombies.add(zombie0);
 zombie0.authOwner = udpConnection;
 zombie0.authOwnerPlayer = player;
 zombie0.getNetworkCharacterAI().resetSpeedLimiter();
 udpConnection.timerSendZombie.reset(0L);
 }
 } else {
 zombie0.authOwner = nullptr;
 zombie0.authOwnerPlayer = nullptr;
 zombie0.getNetworkCharacterAI().resetSpeedLimiter();
 }
 }

 zombie0.lastChangeOwner = System.currentTimeMillis();
 NetworkZombiePacker.getInstance().setExtraUpdate();
 }
 }
 }

 void getZombieAuth(UdpConnection udpConnection, ByteBuffer byteBuffer) {
 NetworkZombieList.NetworkZombie networkZombie = this->owns.getNetworkZombie(udpConnection);
 int int0 = networkZombie.zombies.size();
 int int1 = 0;
 int int2 = byteBuffer.position();
 byteBuffer.putShort((short)int0);
 synchronized (this->owns.lock) {
 networkZombie.zombies.removeIf(zombie0x -> zombie0x.OnlineID == -1);

 for (IsoZombie zombie0 : networkZombie.zombies) {
 if (zombie0.OnlineID != -1) {
 byteBuffer.putShort(zombie0.OnlineID);
 int1++;
 } else {
 DebugLog.General.error("getZombieAuth: zombie.OnlineID == -1");
 }
 }
 }

 if (int1 < int0) {
 int int3 = byteBuffer.position();
 byteBuffer.position(int2);
 byteBuffer.putShort((short)int1);
 byteBuffer.position(int3);
 }
 }

 public LinkedList<IsoZombie> getZombieList(UdpConnection udpConnection) {
 NetworkZombieList.NetworkZombie networkZombie = this->owns.getNetworkZombie(udpConnection);
 return networkZombie.zombies;
 }

 void clearTargetAuth(UdpConnection udpConnection, IsoPlayer player) {
 if (Core.bDebug) {
 DebugLog.log(DebugType.Multiplayer, "Clear zombies target and auth for player id=" + player.getOnlineID());
 }

 if (GameServer.bServer) {
 for (IsoZombie zombie0 : IsoWorld.instance.CurrentCell.getZombieList()) {
 if (zombie0.target == player) {
 zombie0.setTarget(nullptr);
 }

 if (zombie0.authOwner == udpConnection) {
 zombie0.authOwner = nullptr;
 zombie0.authOwnerPlayer = nullptr;
 zombie0.getNetworkCharacterAI().resetSpeedLimiter();
 getInstance().updateAuth(zombie0);
 }
 }
 }
 }

 static void removeZombies(UdpConnection udpConnection) {
 int int0 = (IsoChunkMap.ChunkGridWidth / 2 + 2) * 10;

 for (IsoPlayer player : udpConnection.players) {
 if (player != nullptr) {
 int int1 = (int)player.getX();
 int int2 = (int)player.getY();

 for (int int3 = 0; int3 < 8; int3++) {
 for (int int4 = int2 - int0; int4 <= int2 + int0; int4++) {
 for (int int5 = int1 - int0; int5 <= int1 + int0; int5++) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(int5, int4, int3);
 if (square != nullptr && !square.getMovingObjects().empty()) {
 for (int int6 = square.getMovingObjects().size() - 1; int6 >= 0; int6--) {
 IsoZombie zombie0 = Type.tryCastTo(square.getMovingObjects().get(int6), IsoZombie.class);
 if (zombie0 != nullptr) {
 NetworkZombiePacker.getInstance().deleteZombie(zombie0);
 zombie0.removeFromWorld();
 zombie0.removeFromSquare();
 }
 }
 }
 }
 }
 }
 }
 }
 }

 void recheck(UdpConnection udpConnection) {
 synchronized (this->owns.lock) {
 NetworkZombieList.NetworkZombie networkZombie = this->owns.getNetworkZombie(udpConnection);
 if (networkZombie != nullptr) {
 networkZombie.zombies.removeIf(zombie0 -> zombie0.authOwner != udpConnection);
 }
 }
 }
}
} // namespace popman
} // namespace zombie
