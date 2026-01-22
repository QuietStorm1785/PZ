#pragma once
#include <queue>
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
#include "zombie/core/raknet/UdpConnection/ChecksumState.h"
#include "zombie/core/raknet/UdpConnection/ConnectionType.h"
#include "zombie/core/raknet/UdpConnection/MPClientStatistic.h"
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


class UdpConnection {
public:
    Lock bufferLock = std::make_shared<ReentrantLock>();
    ByteBuffer bb = ByteBuffer.allocate(1000000);
    ByteBufferWriter bbw = std::make_shared<ByteBufferWriter>(this.bb);
    Lock bufferLockPing = std::make_shared<ReentrantLock>();
    ByteBuffer bbPing = ByteBuffer.allocate(50);
    ByteBufferWriter bbwPing = std::make_shared<ByteBufferWriter>(this.bbPing);
    long connectedGUID = 0L;
    UdpEngine engine;
    int index;
    bool allChatMuted = false;
    std::string username;
   public std::string[] usernames = new std::string[4];
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
    ChecksumState checksumState = ChecksumState.Init;
    long checksumTime;
    bool awaitingCoopApprove = false;
    long steamID;
    long ownerID;
    std::string idStr;
    bool isCoopHost;
    int maxPlayers;
    const TShortArrayList chunkObjectState = std::make_shared<TShortArrayList>();
    MPClientStatistic statistic = std::make_shared<MPClientStatistic>(this);
    ZNetStatistics netStatistics;
   public const std::deque<int64_t> pingHistory = std::make_unique<ArrayDeque<>>();
    const PacketValidator validator = std::make_shared<PacketValidator>(this);
    static const long CONNECTION_ATTEMPT_TIMEOUT = 5000L;
    static const long CONNECTION_GRACE_INTERVAL = 60000L;
    long connectionTimestamp;
    UpdateTimer timerSendZombie = std::make_shared<UpdateTimer>();
    bool bFullyConnected = false;
    bool isNeighborPlayer = false;

    public UdpConnection(UdpEngine var1, long var2, int var4) {
      this.engine = var1;
      this.connectedGUID = var2;
      this.index = var4;
      this.ReleventPos[0] = std::make_unique<Vector3>();

      for (int var5 = 0; var5 < 4; var5++) {
         this.playerIDs[var5] = -1;
      }

      this.connectionTimestamp = System.currentTimeMillis();
      this.wasInLoadingQueue = false;
   }

    RakNetPeerInterface getPeer() {
      return this.engine.peer;
   }

    long getConnectedGUID() {
      return this.connectedGUID;
   }

    std::string getServerIP() {
      return this.engine.getServerIP();
   }

    ByteBufferWriter startPacket() {
      this.bufferLock.lock();
      this.bb.clear();
      return this.bbw;
   }

    ByteBufferWriter startPingPacket() {
      this.bufferLockPing.lock();
      this.bbPing.clear();
      return this.bbwPing;
   }

    bool RelevantTo(float var1, float var2) {
      for (int var3 = 0; var3 < 4; var3++) {
         if (this.connectArea[var3] != nullptr) {
    int var4 = (int)this.connectArea[var3].z;
    int var5 = (int)(this.connectArea[var3].x - var4 / 2) * 10;
    int var6 = (int)(this.connectArea[var3].y - var4 / 2) * 10;
    int var7 = var5 + var4 * 10;
    int var8 = var6 + var4 * 10;
            if (var1 >= var5 && var1 < var7 && var2 >= var6 && var2 < var8) {
    return true;
            }
         }

         if (this.ReleventPos[var3] != nullptr
            && Math.abs(this.ReleventPos[var3].x - var1) <= this.ReleventRange * 10
            && Math.abs(this.ReleventPos[var3].y - var2) <= this.ReleventRange * 10) {
    return true;
         }
      }

    return false;
   }

    float getRelevantAndDistance(float var1, float var2, float var3) {
      for (int var4 = 0; var4 < 4; var4++) {
         if (this.ReleventPos[var4] != nullptr
            && Math.abs(this.ReleventPos[var4].x - var1) <= this.ReleventRange * 10
            && Math.abs(this.ReleventPos[var4].y - var2) <= this.ReleventRange * 10) {
            return IsoUtils.DistanceTo(this.ReleventPos[var4].x, this.ReleventPos[var4].y, var1, var2);
         }
      }

      return float.POSITIVE_INFINITY;
   }

    bool RelevantToPlayerIndex(int var1, float var2, float var3) {
      if (this.connectArea[var1] != nullptr) {
    int var4 = (int)this.connectArea[var1].z;
    int var5 = (int)(this.connectArea[var1].x - var4 / 2) * 10;
    int var6 = (int)(this.connectArea[var1].y - var4 / 2) * 10;
    int var7 = var5 + var4 * 10;
    int var8 = var6 + var4 * 10;
         if (var2 >= var5 && var2 < var7 && var3 >= var6 && var3 < var8) {
    return true;
         }
      }

      return this.ReleventPos[var1] != nullptr
         && Math.abs(this.ReleventPos[var1].x - var2) <= this.ReleventRange * 10
         && Math.abs(this.ReleventPos[var1].y - var3) <= this.ReleventRange * 10;
   }

    bool RelevantTo(float var1, float var2, float var3) {
      for (int var4 = 0; var4 < 4; var4++) {
         if (this.connectArea[var4] != nullptr) {
    int var5 = (int)this.connectArea[var4].z;
    int var6 = (int)(this.connectArea[var4].x - var5 / 2) * 10;
    int var7 = (int)(this.connectArea[var4].y - var5 / 2) * 10;
    int var8 = var6 + var5 * 10;
    int var9 = var7 + var5 * 10;
            if (var1 >= var6 && var1 < var8 && var2 >= var7 && var2 < var9) {
    return true;
            }
         }

         if (this.ReleventPos[var4] != nullptr && Math.abs(this.ReleventPos[var4].x - var1) <= var3 && Math.abs(this.ReleventPos[var4].y - var2) <= var3) {
    return true;
         }
      }

    return false;
   }

    void cancelPacket() {
      this.bufferLock.unlock();
   }

    int getBufferPosition() {
      return this.bb.position();
   }

    void endPacket(int var1, int var2, uint8_t var3) {
      if (GameServer.bServer) {
    int var4 = this.bb.position();
         this.bb.position(1);
         MPStatistic.getInstance().addOutcomePacket(this.bb.getShort(), var4);
         this.bb.position(var4);
      }

      this.bb.flip();
    int var5 = this.engine.peer.Send(this.bb, var1, var2, var3, this.connectedGUID, false);
      this.bufferLock.unlock();
   }

    void endPacket() {
      if (GameServer.bServer) {
    int var1 = this.bb.position();
         this.bb.position(1);
         MPStatistic.getInstance().addOutcomePacket(this.bb.getShort(), var1);
         this.bb.position(var1);
      }

      this.bb.flip();
    int var2 = this.engine.peer.Send(this.bb, 1, 3, (byte)0, this.connectedGUID, false);
      this.bufferLock.unlock();
   }

    void endPacketImmediate() {
      if (GameServer.bServer) {
    int var1 = this.bb.position();
         this.bb.position(1);
         MPStatistic.getInstance().addOutcomePacket(this.bb.getShort(), var1);
         this.bb.position(var1);
      }

      this.bb.flip();
    int var2 = this.engine.peer.Send(this.bb, 0, 3, (byte)0, this.connectedGUID, false);
      this.bufferLock.unlock();
   }

    void endPacketUnordered() {
      if (GameServer.bServer) {
    int var1 = this.bb.position();
         this.bb.position(1);
         MPStatistic.getInstance().addOutcomePacket(this.bb.getShort(), var1);
         this.bb.position(var1);
      }

      this.bb.flip();
    int var2 = this.engine.peer.Send(this.bb, 2, 2, (byte)0, this.connectedGUID, false);
      this.bufferLock.unlock();
   }

    void endPacketUnreliable() {
      this.bb.flip();
    int var1 = this.engine.peer.Send(this.bb, 2, 1, (byte)0, this.connectedGUID, false);
      this.bufferLock.unlock();
   }

    void endPacketSuperHighUnreliable() {
      if (GameServer.bServer) {
    int var1 = this.bb.position();
         this.bb.position(1);
         MPStatistic.getInstance().addOutcomePacket(this.bb.getShort(), var1);
         this.bb.position(var1);
      }

      this.bb.flip();
    int var2 = this.engine.peer.Send(this.bb, 0, 1, (byte)0, this.connectedGUID, false);
      this.bufferLock.unlock();
   }

    void endPingPacket() {
      if (GameServer.bServer) {
    int var1 = this.bb.position();
         this.bb.position(1);
         MPStatistic.getInstance().addOutcomePacket(this.bb.getShort(), var1);
         this.bb.position(var1);
      }

      this.bbPing.flip();
      this.engine.peer.Send(this.bbPing, 0, 1, (byte)0, this.connectedGUID, false);
      this.bufferLockPing.unlock();
   }

    InetSocketAddress getInetSocketAddress() {
    std::string var1 = this.engine.peer.getIPFromGUID(this.connectedGUID);
      if ("UNASSIGNED_SYSTEM_ADDRESS" == var1)) {
    return nullptr;
      } else {
         var1 = var1.replace("|", "Â£");
         std::string[] var2 = var1.split("Â£");
         return std::make_shared<InetSocketAddress>(var2[0], int.parseInt(var2[1]));
      }
   }

    void forceDisconnect(const std::string& var1) {
      if (!GameServer.bServer) {
         GameClient.instance.disconnect();
      }

      this.engine.forceDisconnect(this.getConnectedGUID(), var1);
      ConnectionManager.log("force-disconnect", var1, this);
   }

    void setFullyConnected() {
      this.validator.reset();
      this.bFullyConnected = true;
      this.setConnectionTimestamp();
      ConnectionManager.log("fully-connected", "", this);
   }

    void setConnectionTimestamp() {
      this.connectionTimestamp = System.currentTimeMillis();
   }

    bool isConnectionAttemptTimeout() {
      return System.currentTimeMillis() > this.connectionTimestamp + 5000L;
   }

    bool isConnectionGraceIntervalTimeout() {
      return System.currentTimeMillis() > this.connectionTimestamp + 60000L || Core.bDebug && SystemDisabler.doKickInDebug;
   }

    bool isFullyConnected() {
      return this.bFullyConnected;
   }

    void calcCountPlayersInRelevantPosition() {
      if (this.isFullyConnected()) {
    bool var1 = false;

         for (int var2 = 0; var2 < GameServer.udpEngine.connections.size(); var2++) {
    UdpConnection var3 = (UdpConnection)GameServer.udpEngine.connections.get(var2);
            if (var3.isFullyConnected() && var3 != this) {
               for (int var4 = 0; var4 < var3.players.length; var4++) {
    IsoPlayer var5 = var3.players[var4];
                  if (var5 != nullptr && this.RelevantTo(var5.x, var5.y, 120.0F)) {
                     var1 = true;
                  }
               }

               if (var1) {
                  break;
               }
            }
         }

         this.isNeighborPlayer = var1;
      }
   }

    ZNetStatistics getStatistics() {
      try {
         this.netStatistics = this.engine.peer.GetNetStatistics(this.connectedGUID);
      } catch (Exception var5) {
         this.netStatistics = nullptr;
      } finally {
         return this.netStatistics;
      }
   }

    int getAveragePing() {
      return this.engine.peer.GetAveragePing(this.connectedGUID);
   }

    int getLastPing() {
      return this.engine.peer.GetLastPing(this.connectedGUID);
   }

    int getLowestPing() {
      return this.engine.peer.GetLowestPing(this.connectedGUID);
   }

    int getMTUSize() {
      return this.engine.peer.GetMTUSize(this.connectedGUID);
   }

    ConnectionType getConnectionType() {
      return ConnectionType.values()[this.engine.peer.GetConnectionType(this.connectedGUID)];
   }

    std::string toString() {
      return GameClient.bClient
         ? std::string.format(
            "guid=%s ip=%s steam-id=%s access=\"%s\" username=\"%s\" connection-type=\"%s\"",
            this.connectedGUID,
            this.ip == nullptr ? GameClient.ip : this.ip,
            this.steamID == 0L ? GameClient.steamID : this.steamID,
            PlayerType.toString(this.accessLevel),
            this.username == nullptr ? GameClient.username : this.username,
            this.getConnectionType().name()
         )
         : std::string.format(
            "guid=%s ip=%s steam-id=%s access=%s username=\"%s\" connection-type=\"%s\"",
            this.connectedGUID,
            this.ip,
            this.steamID,
            PlayerType.toString(this.accessLevel),
            this.username,
            this.getConnectionType().name()
         );
   }

    bool havePlayer(IsoPlayer var1) {
      if (var1 == nullptr) {
    return false;
      } else {
         for (int var2 = 0; var2 < this.players.length; var2++) {
            if (this.players[var2] == var1) {
    return true;
            }
         }

    return false;
      }
   }
}
} // namespace raknet
} // namespace core
} // namespace zombie
