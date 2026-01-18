#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/array/TShortArrayList.h"
#include "java/net/InetSocketAddress.h"
#include "zombie/SystemDisabler.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/commands/PlayerType.h"
#include "zombie/core/Core.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/utils/UpdateTimer.h"
#include "zombie/core/znet/ZNetStatistics.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/Vector3.h"
#include "zombie/network/ClientServerMap.h"
#include "zombie/network/ConnectionManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/MPStatistic.h"
#include "zombie/network/PacketValidator.h"
#include "zombie/network/PlayerDownloadServer.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace core {
namespace raknet {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class UdpConnection {
public:
 Lock bufferLock = std::make_unique<ReentrantLock>();
 ByteBuffer bb = ByteBuffer.allocate(1000000);
 ByteBufferWriter bbw = new ByteBufferWriter(this->bb);
 Lock bufferLockPing = std::make_unique<ReentrantLock>();
 ByteBuffer bbPing = ByteBuffer.allocate(50);
 ByteBufferWriter bbwPing = new ByteBufferWriter(this->bbPing);
 long connectedGUID = 0L;
 UdpEngine engine;
 int index;
 bool allChatMuted = false;
 std::string username;
 public String[] usernames = new String[4];
 uint8_t ReleventRange;
 uint8_t accessLevel = 1;
 long lastUnauthorizedPacket = 0L;
 std::string ip;
 bool preferredInQueue;
 bool wasInLoadingQueue;
 std::string password;
 bool ping = false;
 public Vector3[] ReleventPos = new Vector3[4];
 public short[] playerIDs = new short[4];
 public IsoPlayer[] players = new IsoPlayer[4];
 public Vector3[] connectArea = new Vector3[4];
 int ChunkGridWidth;
 public ClientServerMap[] loadedCells = new ClientServerMap[4];
 PlayerDownloadServer playerDownloadServer;
 public UdpConnection.ChecksumState checksumState = UdpConnection.ChecksumState.Init;
 long checksumTime;
 bool awaitingCoopApprove = false;
 long steamID;
 long ownerID;
 std::string idStr;
 bool isCoopHost;
 int maxPlayers;
 const TShortArrayList chunkObjectState = new TShortArrayList();
 public UdpConnection.MPClientStatistic statistic = new UdpConnection.MPClientStatistic();
 ZNetStatistics netStatistics;
 public Deque<Long> pingHistory = std::make_unique<ArrayDeque<>>();
 const PacketValidator validator = new PacketValidator(this);
 static const long CONNECTION_ATTEMPT_TIMEOUT = 5000L;
 static const long CONNECTION_GRACE_INTERVAL = 60000L;
 long connectionTimestamp;
 UpdateTimer timerSendZombie = new UpdateTimer();
 bool bFullyConnected = false;
 bool isNeighborPlayer = false;

 public UdpConnection(UdpEngine _engine, long _connectedGUID, int _index) {
 this->engine = _engine;
 this->connectedGUID = _connectedGUID;
 this->index = _index;
 this->ReleventPos[0] = std::make_unique<Vector3>();

 for (int int0 = 0; int0 < 4; int0++) {
 this->playerIDs[int0] = -1;
 }

 this->connectionTimestamp = System.currentTimeMillis();
 this->wasInLoadingQueue = false;
 }

 RakNetPeerInterface getPeer() {
 return this->engine.peer;
 }

 long getConnectedGUID() {
 return this->connectedGUID;
 }

 std::string getServerIP() {
 return this->engine.getServerIP();
 }

 ByteBufferWriter startPacket() {
 this->bufferLock.lock();
 this->bb.clear();
 return this->bbw;
 }

 ByteBufferWriter startPingPacket() {
 this->bufferLockPing.lock();
 this->bbPing.clear();
 return this->bbwPing;
 }

 bool RelevantTo(float x, float y) {
 for (int int0 = 0; int0 < 4; int0++) {
 if (this->connectArea[int0] != nullptr) {
 int int1 = (int)this->connectArea[int0].z;
 int int2 = (int)(this->connectArea[int0].x - int1 / 2) * 10;
 int int3 = (int)(this->connectArea[int0].y - int1 / 2) * 10;
 int int4 = int2 + int1 * 10;
 int int5 = int3 + int1 * 10;
 if (x >= int2 && x < int4 && y >= int3 && y < int5) {
 return true;
 }
 }

 if (this->ReleventPos[int0] != nullptr
 && Math.abs(this->ReleventPos[int0].x - x) <= this->ReleventRange * 10
 && Math.abs(this->ReleventPos[int0].y - y) <= this->ReleventRange * 10) {
 return true;
 }
 }

 return false;
 }

 float getRelevantAndDistance(float x, float y, float z) {
 for (int int0 = 0; int0 < 4; int0++) {
 if (this->ReleventPos[int0] != nullptr
 && Math.abs(this->ReleventPos[int0].x - x) <= this->ReleventRange * 10
 && Math.abs(this->ReleventPos[int0].y - y) <= this->ReleventRange * 10) {
 return IsoUtils.DistanceTo(this->ReleventPos[int0].x, this->ReleventPos[int0].y, x, y);
 }
 }

 return Float.POSITIVE_INFINITY;
 }

 bool RelevantToPlayerIndex(int n, float x, float y) {
 if (this->connectArea[n] != nullptr) {
 int int0 = (int)this->connectArea[n].z;
 int int1 = (int)(this->connectArea[n].x - int0 / 2) * 10;
 int int2 = (int)(this->connectArea[n].y - int0 / 2) * 10;
 int int3 = int1 + int0 * 10;
 int int4 = int2 + int0 * 10;
 if (x >= int1 && x < int3 && y >= int2 && y < int4) {
 return true;
 }
 }

 return this->ReleventPos[n] != nullptr
 && Math.abs(this->ReleventPos[n].x - x) <= this->ReleventRange * 10
 && Math.abs(this->ReleventPos[n].y - y) <= this->ReleventRange * 10;
 }

 bool RelevantTo(float x, float y, float radius) {
 for (int int0 = 0; int0 < 4; int0++) {
 if (this->connectArea[int0] != nullptr) {
 int int1 = (int)this->connectArea[int0].z;
 int int2 = (int)(this->connectArea[int0].x - int1 / 2) * 10;
 int int3 = (int)(this->connectArea[int0].y - int1 / 2) * 10;
 int int4 = int2 + int1 * 10;
 int int5 = int3 + int1 * 10;
 if (x >= int2 && x < int4 && y >= int3 && y < int5) {
 return true;
 }
 }

 if (this->ReleventPos[int0] != nullptr && Math.abs(this->ReleventPos[int0].x - x) <= radius && Math.abs(this->ReleventPos[int0].y - y) <= radius) {
 return true;
 }
 }

 return false;
 }

 void cancelPacket() {
 this->bufferLock.unlock();
 }

 int getBufferPosition() {
 return this->bb.position();
 }

 void endPacket(int priority, int reliability, uint8_t ordering) {
 if (GameServer.bServer) {
 int int0 = this->bb.position();
 this->bb.position(1);
 MPStatistic.getInstance().addOutcomePacket(this->bb.getShort(), int0);
 this->bb.position(int0);
 }

 this->bb.flip();
 int int1 = this->engine.peer.Send(this->bb, priority, reliability, ordering, this->connectedGUID, false);
 this->bufferLock.unlock();
 }

 void endPacket() {
 if (GameServer.bServer) {
 int int0 = this->bb.position();
 this->bb.position(1);
 MPStatistic.getInstance().addOutcomePacket(this->bb.getShort(), int0);
 this->bb.position(int0);
 }

 this->bb.flip();
 int int1 = this->engine.peer.Send(this->bb, 1, 3, (byte)0, this->connectedGUID, false);
 this->bufferLock.unlock();
 }

 void endPacketImmediate() {
 if (GameServer.bServer) {
 int int0 = this->bb.position();
 this->bb.position(1);
 MPStatistic.getInstance().addOutcomePacket(this->bb.getShort(), int0);
 this->bb.position(int0);
 }

 this->bb.flip();
 int int1 = this->engine.peer.Send(this->bb, 0, 3, (byte)0, this->connectedGUID, false);
 this->bufferLock.unlock();
 }

 void endPacketUnordered() {
 if (GameServer.bServer) {
 int int0 = this->bb.position();
 this->bb.position(1);
 MPStatistic.getInstance().addOutcomePacket(this->bb.getShort(), int0);
 this->bb.position(int0);
 }

 this->bb.flip();
 int int1 = this->engine.peer.Send(this->bb, 2, 2, (byte)0, this->connectedGUID, false);
 this->bufferLock.unlock();
 }

 void endPacketUnreliable() {
 this->bb.flip();
 int int0 = this->engine.peer.Send(this->bb, 2, 1, (byte)0, this->connectedGUID, false);
 this->bufferLock.unlock();
 }

 void endPacketSuperHighUnreliable() {
 if (GameServer.bServer) {
 int int0 = this->bb.position();
 this->bb.position(1);
 MPStatistic.getInstance().addOutcomePacket(this->bb.getShort(), int0);
 this->bb.position(int0);
 }

 this->bb.flip();
 int int1 = this->engine.peer.Send(this->bb, 0, 1, (byte)0, this->connectedGUID, false);
 this->bufferLock.unlock();
 }

 void endPingPacket() {
 if (GameServer.bServer) {
 int int0 = this->bb.position();
 this->bb.position(1);
 MPStatistic.getInstance().addOutcomePacket(this->bb.getShort(), int0);
 this->bb.position(int0);
 }

 this->bbPing.flip();
 this->engine.peer.Send(this->bbPing, 0, 1, (byte)0, this->connectedGUID, false);
 this->bufferLockPing.unlock();
 }

 InetSocketAddress getInetSocketAddress() {
 std::string string = this->engine.peer.getIPFromGUID(this->connectedGUID);
 if ("UNASSIGNED_SYSTEM_ADDRESS" == string) {
 return nullptr;
 } else {
 string = string.replace("|", "\u00c2\u00a3");
 String[] strings = string.split("\u00c2\u00a3");
 return new InetSocketAddress(strings[0], Integer.parseInt(strings[1]));
 }
 }

 void forceDisconnect(const std::string& description) {
 if (!GameServer.bServer) {
 GameClient.instance.disconnect();
 }

 this->engine.forceDisconnect(this->getConnectedGUID(), description);
 ConnectionManager.log("force-disconnect", description, this);
 }

 void setFullyConnected() {
 this->validator.reset();
 this->bFullyConnected = true;
 this->setConnectionTimestamp();
 ConnectionManager.log("fully-connected", "", this);
 }

 void setConnectionTimestamp() {
 this->connectionTimestamp = System.currentTimeMillis();
 }

 bool isConnectionAttemptTimeout() {
 return System.currentTimeMillis() > this->connectionTimestamp + 5000L;
 }

 bool isConnectionGraceIntervalTimeout() {
 return System.currentTimeMillis() > this->connectionTimestamp + 60000L || Core.bDebug && SystemDisabler.doKickInDebug;
 }

 bool isFullyConnected() {
 return this->bFullyConnected;
 }

 void calcCountPlayersInRelevantPosition() {
 if (this->isFullyConnected()) {
 bool boolean0 = false;

 for (int int0 = 0; int0 < GameServer.udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection1 = GameServer.udpEngine.connections.get(int0);
 if (udpConnection1.isFullyConnected() && udpConnection1 != this) {
 for (int int1 = 0; int1 < udpConnection1.players.length; int1++) {
 IsoPlayer player = udpConnection1.players[int1];
 if (player != nullptr && this->RelevantTo(player.x, player.y, 120.0F) {
 boolean0 = true;
 }
 }

 if (boolean0) {
 break;
 }
 }
 }

 this->isNeighborPlayer = boolean0;
 }
 }

 ZNetStatistics getStatistics() {
 try {
 this->netStatistics = this->engine.peer.GetNetStatistics(this->connectedGUID);
 } catch (Exception exception) {
 this->netStatistics = nullptr;
 } finally {
 return this->netStatistics;
 }
 }

 int getAveragePing() {
 return this->engine.peer.GetAveragePing(this->connectedGUID);
 }

 int getLastPing() {
 return this->engine.peer.GetLastPing(this->connectedGUID);
 }

 int getLowestPing() {
 return this->engine.peer.GetLowestPing(this->connectedGUID);
 }

 int getMTUSize() {
 return this->engine.peer.GetMTUSize(this->connectedGUID);
 }

 public UdpConnection.ConnectionType getConnectionType() {
 return UdpConnection.ConnectionType.values()[this->engine.peer.GetConnectionType(this->connectedGUID)];
 }

 std::string toString() {
 return GameClient.bClient
 ? String.format(
 "guid=%s ip=%s steam-id=%s access=\"%s\" username=\"%s\" connection-type=\"%s\"",
 this->connectedGUID,
 this->ip == nullptr ? GameClient.ip : this->ip,
 this->steamID == 0L ? GameClient.steamID : this->steamID,
 PlayerType.toString(this->accessLevel),
 this->username == nullptr ? GameClient.username : this->username,
 this->getConnectionType().name()
 )
 : String.format(
 "guid=%s ip=%s steam-id=%s access=%s username=\"%s\" connection-type=\"%s\"",
 this->connectedGUID,
 this->ip,
 this->steamID,
 PlayerType.toString(this->accessLevel),
 this->username,
 this->getConnectionType().name()
 );
 }

 bool havePlayer(IsoPlayer p) {
 if (p == nullptr) {
 return false;
 } else {
 for (int int0 = 0; int0 < this->players.length; int0++) {
 if (this->players[int0] == p) {
 return true;
 }
 }

 return false;
 }
 }

 public static enum ChecksumState {
 Init,
 Different,
 Done;
 }

 public static enum ConnectionType {
 Disconnected,
 UDPRakNet,
 Steam;
 }

 public class MPClientStatistic {
 uint8_t enable = 0;
 int diff = 0;
 float pingAVG = 0.0F;
 int zombiesCount = 0;
 int zombiesLocalOwnership = 0;
 float zombiesDesyncAVG = 0.0F;
 float zombiesDesyncMax = 0.0F;
 int zombiesTeleports = 0;
 int remotePlayersCount = 0;
 float remotePlayersDesyncAVG = 0.0F;
 float remotePlayersDesyncMax = 0.0F;
 int remotePlayersTeleports = 0;
 float FPS = 0.0F;
 float FPSMin = 0.0F;
 float FPSAvg = 0.0F;
 float FPSMax = 0.0F;
 public short[] FPSHistogramm = new short[32];

 void parse(ByteBuffer bb) {
 long long0 = bb.getLong();
 long long1 = System.currentTimeMillis();
 this->diff = (int)(long1 - long0);
 this->pingAVG = this->pingAVG + (this->diff * 0.5F - this->pingAVG) * 0.1F;
 this->zombiesCount = bb.getInt();
 this->zombiesLocalOwnership = bb.getInt();
 this->zombiesDesyncAVG = bb.getFloat();
 this->zombiesDesyncMax = bb.getFloat();
 this->zombiesTeleports = bb.getInt();
 this->remotePlayersCount = bb.getInt();
 this->remotePlayersDesyncAVG = bb.getFloat();
 this->remotePlayersDesyncMax = bb.getFloat();
 this->remotePlayersTeleports = bb.getInt();
 this->FPS = bb.getFloat();
 this->FPSMin = bb.getFloat();
 this->FPSAvg = bb.getFloat();
 this->FPSMax = bb.getFloat();

 for (int int0 = 0; int0 < 32; int0++) {
 this->FPSHistogramm[int0] = bb.getShort();
 }
 }
 }
}
} // namespace raknet
} // namespace core
} // namespace zombie
