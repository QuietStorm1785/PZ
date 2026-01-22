#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/InetAddress.h"
#include "java/net/UnknownHostException.h"
#include "zombie/characters/NetworkCharacter/Transform.h"
#include "zombie/core/ThreadGroups.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/RakVoice.h"
#include "zombie/core/utils/UpdateLimit.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/FakeClientManager/1.h"
#include "zombie/network/FakeClientManager/Client/Request.h"
#include "zombie/network/FakeClientManager/Client/State.h"
#include "zombie/network/FakeClientManager/Network.h"
#include "zombie/network/FakeClientManager/Player.h"
#include "zombie/network/FakeClientManager/Player/Clothes.h"
#include "zombie/network/FakeClientManager/Zombie.h"
#include "zombie/network/NetworkVariables/PredictionTypes.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/packets/PlayerPacket.h"
#include "zombie/network/packets/SyncInjuriesPacket.h"
#include <filesystem>

namespace zombie {
namespace network {


class FakeClientManager {
public:
    static std::string connectionServerHost = "127.0.0.1";
    static long connectionInterval = 1500L;
    static long connectionTimeout = 10000L;
    static long connectionDelay = 15000L;
    static int statisticsClientID = -1;
    static int statisticsPeriod = 1;
    static long serverTimeShift = 0L;
    static bool serverTimeShiftIsSet = false;
   private const std::unordered_map<int, Request> requests = std::make_unique<std::unordered_map<>>();
    const Player player;
    const Network network;
    const int connectionIndex;
    const int port;
    long connectionGUID = -1L;
    int requestId = 0;
    long stateTime;
    State state;
    std::string host;
    static std::string luaChecksum = "";
    static std::string scriptChecksum = "";

   private FakeClientManager$Client(Player var1, Network var2, int var3, int var4) {
      this.connectionIndex = var3;
      this.network = var2;
      this.player = var1;
      this.port = var4;

      try {
         this.host = InetAddress.getByName(connectionServerHost).getHostAddress();
         this.state = State.CONNECT;
    Thread var5 = std::make_shared<Thread>(ThreadGroups.Workers, this::updateThread, this.player.username);
         var5.setDaemon(true);
         var5.start();
      } catch (UnknownHostException var6) {
         this.state = State.QUIT;
         var6.printStackTrace();
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void updateThread() {
      FakeClientManager.info(
         this.player.movement.id,
         std::string.format(
            "Start client (%d) %s:%d => %s:%d / \"%s\"", this.connectionIndex, "0.0.0.0", this.port, this.host, 16261, this.player.movement.description
         )
      );
      FakeClientManager.sleep(this.player.movement.connectDelay);
      switch (1.$SwitchMap$zombie$network$FakeClientManager$Movement$Type[this.player.movement.type.ordinal()]) {
         case 1:
            this.player.circleMovement();
            break;
         case 2:
            this.player.lineMovement();
            break;
         case 3:
            this.player.aiAttackZombiesMovement();
            break;
         case 4:
            this.player.aiRunAwayFromZombiesMovement();
            break;
         case 5:
            this.player.aiRunToAnotherPlayersMovement();
            break;
         case 6:
            this.player.aiNormalMovement();
      }

      while (this.state != State.QUIT) {
         this.update();
         FakeClientManager.sleep(1L);
      }

      FakeClientManager.info(
         this.player.movement.id,
         std::string.format(
            "Stop client (%d) %s:%d => %s:%d / \"%s\"", this.connectionIndex, "0.0.0.0", this.port, this.host, 16261, this.player.movement.description
         )
      );
   }

    void updateTime() {
      this.stateTime = System.currentTimeMillis();
   }

    long getServerTime() {
      return serverTimeShiftIsSet ? System.nanoTime() + serverTimeShift : 0L;
   }

    bool checkConnectionTimeout() {
      return System.currentTimeMillis() - this.stateTime > connectionTimeout;
   }

    bool checkConnectionDelay() {
      return System.currentTimeMillis() - this.stateTime > connectionDelay;
   }

    void changeState(State var1) {
      this.updateTime();
      FakeClientManager.log(this.player.movement.id, std::string.format("%s >> %s", this.state, var1));
      if (State.RUN == var1)) {
         this.player.movement.connect(this.player.OnlineID);
         if (this.player.teleportLimiter == nullptr) {
            this.player.teleportLimiter = std::make_shared<UpdateLimit>(this.player.movement.teleportDelay);
         }

         if (this.player.movement.id == statisticsClientID) {
            this.sendTimeSync();
            this.sendInjuries();
            this.sendStatisticsEnable(statisticsPeriod);
         }
      } else if (State.DISCONNECT == var1) && !State.DISCONNECT == this.state)) {
         this.player.movement.disconnect(this.player.OnlineID);
      }

      this.state = var1;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void update() {
      switch (1.$SwitchMap$zombie$network$FakeClientManager$Client$State[this.state.ordinal()]) {
         case 1:
            this.player.movement.timestamp = System.currentTimeMillis();
            this.network.connect(this.player.movement.id, this.host);
            this.changeState(State.WAIT);
            break;
         case 2:
            this.sendPlayerLogin();
            this.changeState(State.WAIT);
            break;
         case 3:
            this.sendPlayerConnect();
            this.changeState(State.WAIT);
            break;
         case 4:
            this.sendChecksum();
            this.changeState(State.WAIT);
            break;
         case 5:
            this.sendPlayerExtraInfo(this.player.movement.ghost, this.player.movement.hordeCreator != nullptr || Player.isVOIPEnabled);
            this.sendEquip();
            this.changeState(State.WAIT);
            break;
         case 6:
            this.requestId = 0;
            this.requests.clear();
            this.requestFullUpdate();
            this.requestLargeAreaZip();
            this.changeState(State.WAIT);
            break;
         case 7:
            if (this.player.movement.doDisconnect() && this.player.movement.checkDisconnect()) {
               this.changeState(State.DISCONNECT);
            } else {
               this.player.run();
            }
            break;
         case 8:
            if (this.checkConnectionTimeout()) {
               this.changeState(State.DISCONNECT);
            }
            break;
         case 9:
            if (this.network.isConnected()) {
               this.player.movement.timestamp = System.currentTimeMillis();
               this.network.disconnect(this.connectionGUID, this.player.movement.id, this.host);
            }

            if (this.player.movement.doReconnect() && this.player.movement.checkReconnect()
               || !this.player.movement.doReconnect() && this.checkConnectionDelay()) {
               this.changeState(State.CONNECT);
            }
         case 10:
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void receive(short var1, ByteBuffer var2) {
    PacketType var3 = (PacketType)PacketTypes.packetTypes.get(var1);
      Network.logUserPacket(this.player.movement.id, var1);
      switch (1.$SwitchMap$zombie$network$PacketTypes$PacketType[var3.ordinal()]) {
         case 1:
            if (this.receivePlayerConnect(var2)) {
               if (luaChecksum.empty()) {
                  this.changeState(State.PLAYER_EXTRA_INFO);
               } else {
                  this.changeState(State.CHECKSUM);
               }
            }
            break;
         case 2:
            if (this.receivePlayerExtraInfo(var2)) {
               this.changeState(State.RUN);
            }
            break;
         case 3:
            if (this.state == State.WAIT && this.receiveChunkPart(var2)) {
               this.updateTime();
               if (this.allChunkPartsReceived()) {
                  this.changeState(State.PLAYER_CONNECT);
               }
            }
            break;
         case 4:
            if (this.state == State.WAIT && this.receiveNotRequired(var2)) {
               this.updateTime();
               if (this.allChunkPartsReceived()) {
                  this.changeState(State.PLAYER_CONNECT);
               }
            }
         case 5:
         default:
            break;
         case 6:
            this.receiveStatistics(var2);
            break;
         case 7:
            this.receiveTimeSync(var2);
            break;
         case 8:
            this.receiveSyncClock(var2);
            break;
         case 9:
         case 10:
            this.receiveZombieSimulation(var2);
            break;
         case 11:
         case 12:
            this.player.playerManager.parsePlayer(var2);
            break;
         case 13:
            this.player.playerManager.parsePlayerTimeout(var2);
            break;
         case 14:
            this.receiveKicked(var2);
            break;
         case 15:
            this.receiveChecksum(var2);
            break;
         case 16:
            this.receiveKillZombie(var2);
            break;
         case 17:
            this.receiveTeleport(var2);
      }

      var2.clear();
   }

    void doPacket(short var1, ByteBuffer var2) {
      var2.put((byte)-122);
      var2.putShort(var1);
   }

    void putUTF(ByteBuffer var1, const std::string& var2) {
      if (var2 == nullptr) {
         var1.putShort((short)0);
      } else {
         byte[] var3 = var2.getBytes();
         var1.putShort((short)var3.length);
         var1.put(var3);
      }
   }

    void putBoolean(ByteBuffer var1, bool var2) {
      var1.put((byte)(var2 ? 1 : 0));
   }

    void sendPlayerLogin() {
    ByteBuffer var1 = this.network.startPacket();
      this.doPacket(PacketType.Login.getId(), var1);
      this.putUTF(var1, this.player.username);
      this.putUTF(var1, this.player.username);
      this.putUTF(var1, FakeClientManager.versionNumber);
      this.network.endPacketImmediate(this.connectionGUID);
   }

    void sendPlayerConnect() {
    ByteBuffer var1 = this.network.startPacket();
      this.doPacket(PacketType.PlayerConnect.getId(), var1);
      this.writePlayerConnectData(var1);
      this.network.endPacketImmediate(this.connectionGUID);
   }

    void writePlayerConnectData(ByteBuffer var1) {
      var1.put((byte)0);
      var1.put((byte)13);
      var1.putFloat(this.player.x);
      var1.putFloat(this.player.y);
      var1.putFloat(this.player.z);
      var1.putInt(0);
      this.putUTF(var1, this.player.username);
      this.putUTF(var1, this.player.username);
      this.putUTF(var1, this.player.isFemale == 0 ? "Kate" : "Male");
      var1.putInt(this.player.isFemale);
      this.putUTF(var1, "fireofficer");
      var1.putInt(0);
      var1.putInt(4);
      this.putUTF(var1, "Sprinting");
      var1.putInt(1);
      this.putUTF(var1, "Fitness");
      var1.putInt(6);
      this.putUTF(var1, "Strength");
      var1.putInt(6);
      this.putUTF(var1, "Axe");
      var1.putInt(1);
      var1.put((byte)0);
      var1.put((byte)0);
      var1.put((byte)Math.round(Math.random() * 5.0));
      var1.put((byte)0);
      var1.put((byte)0);
      var1.put((byte)0);
      var1.put((byte)0);
    int var2 = this.player.clothes.size();
      var1.put((byte)var2);

      for (Clothes var4 : this.player.clothes) {
         var1.put(var4.flags);
         this.putUTF(var1, "Base." + var4.name);
         this.putUTF(var1, nullptr);
         this.putUTF(var1, var4.name);
         var1.put((byte)-1);
         var1.put((byte)-1);
         var1.put((byte)-1);
         var1.put(var4.text);
         var1.putFloat(0.0F);
         var1.put((byte)0);
         var1.put((byte)0);
         var1.put((byte)0);
         var1.put((byte)0);
         var1.put((byte)0);
         var1.put((byte)0);
      }

      this.putUTF(var1, "fake_str");
      var1.putShort((short)0);
      var1.putInt(2);
      this.putUTF(var1, "Fit");
      this.putUTF(var1, "Stout");
      var1.putFloat(0.0F);
      var1.putInt(0);
      var1.putInt(0);
      var1.putInt(4);
      this.putUTF(var1, "Sprinting");
      var1.putFloat(75.0F);
      this.putUTF(var1, "Fitness");
      var1.putFloat(67500.0F);
      this.putUTF(var1, "Strength");
      var1.putFloat(67500.0F);
      this.putUTF(var1, "Axe");
      var1.putFloat(75.0F);
      var1.putInt(4);
      this.putUTF(var1, "Sprinting");
      var1.putInt(1);
      this.putUTF(var1, "Fitness");
      var1.putInt(6);
      this.putUTF(var1, "Strength");
      var1.putInt(6);
      this.putUTF(var1, "Axe");
      var1.putInt(1);
      var1.putInt(0);
      this.putBoolean(var1, true);
      this.putUTF(var1, "fake");
      var1.putFloat(this.player.tagColor.r);
      var1.putFloat(this.player.tagColor.g);
      var1.putFloat(this.player.tagColor.b);
      var1.putInt(0);
      var1.putDouble(0.0);
      var1.putInt(0);
      this.putUTF(var1, this.player.username);
      var1.putFloat(this.player.speakColor.r);
      var1.putFloat(this.player.speakColor.g);
      var1.putFloat(this.player.speakColor.b);
      this.putBoolean(var1, true);
      this.putBoolean(var1, false);
      var1.put((byte)0);
      var1.put((byte)0);
      var1.putInt(0);
      var1.putInt(0);
   }

    void sendPlayerExtraInfo(bool var1, bool var2) {
    ByteBuffer var3 = this.network.startPacket();
      this.doPacket(PacketType.ExtraInfo.getId(), var3);
      var3.putShort(this.player.OnlineID);
      var3.put((byte)0);
      var3.put((byte)(var1 ? 1 : 0));
      var3.put((byte)0);
      var3.put((byte)0);
      var3.put((byte)0);
      var3.put((byte)(Player.isVOIPEnabled ? 1 : 0));
      this.network.endPacketImmediate(this.connectionGUID);
   }

    void sendSyncRadioData() {
    ByteBuffer var1 = this.network.startPacket();
      this.doPacket(PacketType.SyncRadioData.getId(), var1);
      var1.put((byte)(Player.isVOIPEnabled ? 1 : 0));
      var1.putInt(4);
      var1.putInt(0);
      var1.putInt((int)RakVoice.GetMaxDistance());
      var1.putInt((int)this.player.x);
      var1.putInt((int)this.player.y);
      this.network.endPacketImmediate(this.connectionGUID);
   }

    void sendEquip() {
    ByteBuffer var1 = this.network.startPacket();
      this.doPacket(PacketType.Equip.getId(), var1);
      var1.put((byte)0);
      var1.put((byte)0);
      var1.put((byte)1);
      var1.putInt(16);
      var1.putShort(this.player.registry_id);
      var1.put((byte)1);
      var1.putInt(this.player.weapon_id);
      var1.put((byte)0);
      var1.putInt(0);
      var1.putInt(0);
      var1.put((byte)0);
      this.network.endPacketImmediate(this.connectionGUID);
   }

    void sendChatMessage(const std::string& var1) {
    ByteBuffer var2 = this.network.startPacket();
      var2.putShort(this.player.OnlineID);
      var2.putInt(2);
      this.putUTF(var2, this.player.username);
      this.putUTF(var2, var1);
      this.network.endPacketImmediate(this.connectionGUID);
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    int getBooleanVariables() {
    short var1 = 0;
      if (this.player.movement.speed > 0.0F) {
         switch (1.$SwitchMap$zombie$network$FakeClientManager$Movement$Motion[this.player.movement.motion.ordinal()]) {
            case 1:
               var1 |= 64;
               break;
            case 2:
               var1 |= 1;
               break;
            case 3:
               var1 |= 17;
               break;
            case 4:
               var1 |= 16;
               break;
            case 5:
               var1 |= 32;
         }

         var1 |= 17408;
      }

    return var1;
   }

    void sendPlayer(Transform var1, int var2, Vector2 var3) {
    PlayerPacket var4 = std::make_shared<PlayerPacket>();
      var4.id = this.player.OnlineID;
      var4.x = var1.position.x;
      var4.y = var1.position.y;
      var4.z = (byte)this.player.z;
      var4.direction = var3.getDirection();
      var4.usePathFinder = false;
      var4.moveType = PredictionTypes.None;
      var4.VehicleID = -1;
      var4.VehicleSeat = -1;
      var4.booleanVariables = this.getBooleanVariables();
      var4.footstepSoundRadius = 0;
      var4.bleedingLevel = 0;
      var4.realx = this.player.x;
      var4.realy = this.player.y;
      var4.realz = (byte)this.player.z;
      var4.realdir = (byte)IsoDirections.fromAngleActual(this.player.direction).index();
      var4.realt = var2;
      var4.collidePointX = -1.0F;
      var4.collidePointY = -1.0F;
    ByteBuffer var5 = this.network.startPacket();
      this.doPacket(PacketType.PlayerUpdateReliable.getId(), var5);
    ByteBufferWriter var6 = std::make_shared<ByteBufferWriter>(var5);
      var4.write(var6);
      this.network.endPacket(this.connectionGUID);
   }

    bool receivePlayerConnect(ByteBuffer var1) {
    short var2 = var1.getShort();
      if (var2 == -1) {
    uint8_t var3 = var1.get();
         var2 = var1.getShort();
         this.player.OnlineID = var2;
    return true;
      } else {
    return false;
      }
   }

    bool receivePlayerExtraInfo(ByteBuffer var1) {
    short var2 = var1.getShort();
    return var2 = = this.player.OnlineID;
   }

    bool receiveChunkPart(ByteBuffer var1) {
    bool var2 = false;
    int var3 = var1.getInt();
    int var4 = var1.getInt();
    int var5 = var1.getInt();
    int var6 = var1.getInt();
    int var7 = var1.getInt();
    int var8 = var1.getInt();
      if (this.requests.remove(var3) != nullptr) {
         var2 = true;
      }

    return var2;
   }

    bool receiveNotRequired(ByteBuffer var1) {
    bool var2 = false;
    int var3 = var1.getInt();

      for (int var4 = 0; var4 < var3; var4++) {
    int var5 = var1.getInt();
    bool var6 = var1.get() == 1;
         if (this.requests.remove(var5) != nullptr) {
            var2 = true;
         }
      }

    return var2;
   }

    bool allChunkPartsReceived() {
      return this.requests.size() == 0;
   }

    void addChunkRequest(int var1, int var2, int var3, int var4) {
    Request var5 = std::make_shared<Request>(var1, var2, this.requestId);
      this.requestId++;
      this.requests.put(var5.id, var5);
   }

    void requestZipList() {
    ByteBuffer var1 = this.network.startPacket();
      this.doPacket(PacketType.RequestZipList.getId(), var1);
      var1.putInt(this.requests.size());

      for (Request var3 : this.requests.values()) {
         var1.putInt(var3.id);
         var1.putInt(var3.wx);
         var1.putInt(var3.wy);
         var1.putLong(var3.crc);
      }

      this.network.endPacket(this.connectionGUID);
   }

    void requestLargeAreaZip() {
    ByteBuffer var1 = this.network.startPacket();
      this.doPacket(PacketType.RequestLargeAreaZip.getId(), var1);
      var1.putInt(this.player.WorldX);
      var1.putInt(this.player.WorldY);
      var1.putInt(13);
      this.network.endPacketImmediate(this.connectionGUID);
    int var2 = this.player.WorldX - 6 + 2;
    int var3 = this.player.WorldY - 6 + 2;
    int var4 = this.player.WorldX + 6 + 2;
    int var5 = this.player.WorldY + 6 + 2;

      for (int var6 = var3; var6 <= var5; var6++) {
         for (int var7 = var2; var7 <= var4; var7++) {
    Request var8 = std::make_shared<Request>(var7, var6, this.requestId);
            this.requestId++;
            this.requests.put(var8.id, var8);
         }
      }

      this.requestZipList();
   }

    void requestFullUpdate() {
    ByteBuffer var1 = this.network.startPacket();
      this.doPacket(PacketType.IsoRegionClientRequestFullUpdate.getId(), var1);
      this.network.endPacketImmediate(this.connectionGUID);
   }

    void requestChunkObjectState() {
      for (Request var2 : this.requests.values()) {
    ByteBuffer var3 = this.network.startPacket();
         this.doPacket(PacketType.ChunkObjectState.getId(), var3);
         var3.putShort((short)var2.wx);
         var3.putShort((short)var2.wy);
         this.network.endPacket(this.connectionGUID);
      }
   }

    void requestChunks() {
      if (!this.requests.empty()) {
         this.requestZipList();
         this.requestChunkObjectState();
         this.requests.clear();
      }
   }

    void sendStatisticsEnable(int var1) {
    ByteBuffer var2 = this.network.startPacket();
      this.doPacket(PacketType.StatisticRequest.getId(), var2);
      var2.put((byte)3);
      var2.putInt(var1);
      this.network.endPacketImmediate(this.connectionGUID);
   }

    void receiveStatistics(ByteBuffer var1) {
    long var2 = var1.getLong();
    long var4 = var1.getLong();
    long var6 = var1.getLong();
    long var8 = var1.getLong();
    long var10 = var1.getLong();
    long var12 = var1.getLong();
    long var14 = var1.getLong();
    long var16 = var1.getLong();
    long var18 = var1.getLong();
      FakeClientManager.info(
         this.player.movement.id,
         std::string.format(
            "ServerStats: con=[%2d] fps=[%2d] tps=[%2d] upt=[%4d-%4d/%4d], c1=[%d] c2=[%d] c3=[%d]", var12, var8, var10, var2, var4, var6, var14, var16, var18
         )
      );
   }

    void sendTimeSync() {
    ByteBuffer var1 = this.network.startPacket();
      this.doPacket(PacketType.TimeSync.getId(), var1);
    long var2 = System.nanoTime();
      var1.putLong(var2);
      var1.putLong(0L);
      this.network.endPacketImmediate(this.connectionGUID);
   }

    void receiveTimeSync(ByteBuffer var1) {
    long var2 = var1.getLong();
    long var4 = var1.getLong();
    long var6 = System.nanoTime();
    long var8 = var6 - var2;
    long var10 = var4 - var6 + var8 / 2L;
    long var12 = serverTimeShift;
      if (!serverTimeShiftIsSet) {
         serverTimeShift = var10;
      } else {
         serverTimeShift = (long)((float)serverTimeShift + (float)(var10 - serverTimeShift) * 0.05F);
      }

    long var14 = 10000000L;
      if (Math.abs(serverTimeShift - var12) > var14) {
         this.sendTimeSync();
      } else {
         serverTimeShiftIsSet = true;
      }
   }

    void receiveSyncClock(ByteBuffer var1) {
      FakeClientManager.trace(this.player.movement.id, std::string.format("Player %3d sync clock", this.player.OnlineID));
   }

    void receiveKicked(ByteBuffer var1) {
    std::string var2 = FakeClientManager.ReadStringUTF(var1);
      FakeClientManager.info(this.player.movement.id, std::string.format("Client kicked. Reason: %s", var2));
   }

    void receiveChecksum(ByteBuffer var1) {
      FakeClientManager.trace(this.player.movement.id, std::string.format("Player %3d receive Checksum", this.player.OnlineID));
    short var2 = var1.getShort();
    bool var3 = var1.get() == 1;
    bool var4 = var1.get() == 1;
      if (var2 != 1 || !var3 || !var4) {
         FakeClientManager.info(this.player.movement.id, std::string.format("checksum lua: %b, script: %b", var3, var4));
      }

      this.changeState(State.PLAYER_EXTRA_INFO);
   }

    void receiveKillZombie(ByteBuffer var1) {
      FakeClientManager.trace(this.player.movement.id, std::string.format("Player %3d receive KillZombie", this.player.OnlineID));
    short var2 = var1.getShort();
    Zombie var3 = (Zombie)this.player.simulator.zombies.get(int.valueOf(var2));
      if (var3 != nullptr) {
         this.player.simulator.zombies4Delete.push_back(var3);
      }
   }

    void receiveTeleport(ByteBuffer var1) {
    uint8_t var2 = var1.get();
    float var3 = var1.getFloat();
    float var4 = var1.getFloat();
    float var5 = var1.getFloat();
      FakeClientManager.info(this.player.movement.id, std::string.format("Player %3d teleport to (%d, %d)", this.player.OnlineID, (int)var3, (int)var4));
      this.player.x = var3;
      this.player.y = var4;
   }

    void receiveZombieSimulation(ByteBuffer var1) {
      this.player.simulator.clear();
    bool var2 = var1.get() == 1;
    short var3 = var1.getShort();

      for (short var4 = 0; var4 < var3; var4++) {
    short var5 = var1.getShort();
    Zombie var6 = (Zombie)this.player.simulator.zombies.get(int.valueOf(var5));
         this.player.simulator.zombies4Delete.push_back(var6);
      }

    short var7 = var1.getShort();

      for (short var8 = 0; var8 < var7; var8++) {
    short var9 = var1.getShort();
         this.player.simulator.push_back(var9);
      }

      this.player.simulator.receivePacket(var1);
      this.player.simulator.process();
   }

    void sendInjuries() {
    SyncInjuriesPacket var1 = std::make_shared<SyncInjuriesPacket>();
      var1.id = this.player.OnlineID;
      var1.strafeSpeed = 1.0F;
      var1.walkSpeed = 1.0F;
      var1.walkInjury = 0.0F;
    ByteBuffer var2 = this.network.startPacket();
      this.doPacket(PacketType.SyncInjuries.getId(), var2);
    ByteBufferWriter var3 = std::make_shared<ByteBufferWriter>(var2);
      var1.write(var3);
      this.network.endPacketImmediate(this.connectionGUID);
   }

    void sendChecksum() {
      if (!luaChecksum.empty()) {
         FakeClientManager.trace(this.player.movement.id, std::string.format("Player %3d sendChecksum", this.player.OnlineID));
    ByteBuffer var1 = this.network.startPacket();
         this.doPacket(PacketType.Checksum.getId(), var1);
         var1.putShort((short)1);
         this.putUTF(var1, luaChecksum);
         this.putUTF(var1, scriptChecksum);
         this.network.endPacketImmediate(this.connectionGUID);
      }
   }

    void sendCommand(const std::string& var1) {
    ByteBuffer var2 = this.network.startPacket();
      this.doPacket(PacketType.ReceiveCommand.getId(), var2);
      FakeClientManager.WriteStringUTF(var2, var1);
      this.network.endPacketImmediate(this.connectionGUID);
   }

    void sendEventPacket(short var1, int var2, int var3, int var4, uint8_t var5, const std::string& var6) {
    ByteBuffer var7 = this.network.startPacket();
      this.doPacket(PacketType.EventPacket.getId(), var7);
      var7.putShort(var1);
      var7.putFloat(var2);
      var7.putFloat(var3);
      var7.putFloat(var4);
      var7.put(var5);
      FakeClientManager.WriteStringUTF(var7, var6);
      FakeClientManager.WriteStringUTF(var7, "");
      FakeClientManager.WriteStringUTF(var7, "");
      FakeClientManager.WriteStringUTF(var7, "");
      var7.putFloat(1.0F);
      var7.putFloat(1.0F);
      var7.putFloat(0.0F);
      var7.putInt(0);
      var7.putShort((short)0);
      this.network.endPacketImmediate(this.connectionGUID);
   }

    void sendWorldSound4Player(int var1, int var2, int var3, int var4, int var5) {
    ByteBuffer var6 = this.network.startPacket();
      this.doPacket(PacketType.WorldSound.getId(), var6);
      var6.putInt(var1);
      var6.putInt(var2);
      var6.putInt(var3);
      var6.putInt(var4);
      var6.putInt(var5);
      var6.put((byte)0);
      var6.putFloat(0.0F);
      var6.putFloat(1.0F);
      var6.put((byte)0);
      this.network.endPacketImmediate(this.connectionGUID);
   }
}
} // namespace network
} // namespace zombie
