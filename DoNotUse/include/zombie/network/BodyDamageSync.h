#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/BodyDamage/BodyDamage.h"
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/BodyDamageSync/Updater.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include <filesystem>

namespace zombie {
namespace network {


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
    static BodyDamageSync instance = std::make_shared<BodyDamageSync>();
   private std::vector<Updater> updaters = std::make_unique<std::vector<>>();

    static void noise(const std::string& var0) {
      if (Core.bDebug || GameServer.bServer && GameServer.bDebug) {
         DebugLog.log("BodyDamage: " + var0);
      }
   }

    void startSendingUpdates(short var1, short var2) {
      if (GameClient.bClient) {
         noise("start sending updates to " + var2);

         for (int var3 = 0; var3 < this.updaters.size(); var3++) {
    Updater var4 = this.updaters.get(var3);
            if (var4.localIndex == var1 && var4.remoteID == var2) {
               return;
            }
         }

    IsoPlayer var5 = IsoPlayer.players[var1];
    Updater var6 = std::make_shared<Updater>();
         var6.localIndex = var1;
         var6.remoteID = var2;
         var6.bdLocal = var5.getBodyDamage();
         var6.bdSent = std::make_shared<BodyDamage>(nullptr);
         this.updaters.push_back(var6);
      }
   }

    void stopSendingUpdates(short var1, short var2) {
      if (GameClient.bClient) {
         noise("stop sending updates to " + var2);

         for (int var3 = 0; var3 < this.updaters.size(); var3++) {
    Updater var4 = this.updaters.get(var3);
            if (var4.localIndex == var1 && var4.remoteID == var2) {
               this.updaters.remove(var3);
               return;
            }
         }
      }
   }

    void startReceivingUpdates(short var1) {
      if (GameClient.bClient) {
         noise("start receiving updates from " + var1 + " to " + IsoPlayer.players[0].getOnlineID());
    ByteBufferWriter var2 = GameClient.connection.startPacket();
         PacketType.BodyDamageUpdate.doPacket(var2);
         var2.putByte((byte)1);
         var2.putShort(IsoPlayer.players[0].getOnlineID());
         var2.putShort(var1);
         PacketType.BodyDamageUpdate.send(GameClient.connection);
      }
   }

    void stopReceivingUpdates(short var1) {
      if (GameClient.bClient) {
         noise("stop receiving updates from " + var1 + " to " + IsoPlayer.players[0].getOnlineID());
    ByteBufferWriter var2 = GameClient.connection.startPacket();
         PacketType.BodyDamageUpdate.doPacket(var2);
         var2.putByte((byte)2);
         var2.putShort(IsoPlayer.players[0].getOnlineID());
         var2.putShort(var1);
         PacketType.BodyDamageUpdate.send(GameClient.connection);
      }
   }

    void update() {
      if (GameClient.bClient) {
         for (int var1 = 0; var1 < this.updaters.size(); var1++) {
    Updater var2 = this.updaters.get(var1);
            var2.update();
         }
      }
   }

    void serverPacket(ByteBuffer var1) {
    uint8_t var2 = var1.get();
      if (var2 == 1) {
    short var9 = var1.getShort();
    short var11 = var1.getShort();
    long var13 = (int64_t)GameServer.IDToAddressMap.get(var11);
         if (var13 != nullptr) {
    UdpConnection var15 = GameServer.udpEngine.getActiveConnection(var13);
            if (var15 != nullptr) {
    ByteBufferWriter var17 = var15.startPacket();
               PacketType.BodyDamageUpdate.doPacket(var17);
               var17.putByte((byte)1);
               var17.putShort(var9);
               var17.putShort(var11);
               PacketType.BodyDamageUpdate.send(var15);
            }
         }
      } else if (var2 == 2) {
    short var8 = var1.getShort();
    short var10 = var1.getShort();
    long var12 = (int64_t)GameServer.IDToAddressMap.get(var10);
         if (var12 != nullptr) {
    UdpConnection var14 = GameServer.udpEngine.getActiveConnection(var12);
            if (var14 != nullptr) {
    ByteBufferWriter var16 = var14.startPacket();
               PacketType.BodyDamageUpdate.doPacket(var16);
               var16.putByte((byte)2);
               var16.putShort(var8);
               var16.putShort(var10);
               PacketType.BodyDamageUpdate.send(var14);
            }
         }
      } else if (var2 == 3) {
    short var3 = var1.getShort();
    short var4 = var1.getShort();
    long var5 = (int64_t)GameServer.IDToAddressMap.get(var4);
         if (var5 != nullptr) {
    UdpConnection var6 = GameServer.udpEngine.getActiveConnection(var5);
            if (var6 != nullptr) {
    ByteBufferWriter var7 = var6.startPacket();
               PacketType.BodyDamageUpdate.doPacket(var7);
               var7.putByte((byte)3);
               var7.putShort(var3);
               var7.putShort(var4);
               var7.bb.put(var1);
               PacketType.BodyDamageUpdate.send(var6);
            }
         }
      }
   }

    void clientPacket(ByteBuffer var1) {
    uint8_t var2 = var1.get();
      if (var2 == 1) {
    short var12 = var1.getShort();
    short var14 = var1.getShort();

         for (short var16 = 0; var16 < IsoPlayer.numPlayers; var16++) {
    IsoPlayer var18 = IsoPlayer.players[var16];
            noise("looking for " + var14 + " testing player ID=" + var18.getOnlineID());
            if (var18 != nullptr && var18.isAlive() && var18.getOnlineID() == var14) {
               this.startSendingUpdates(var16, var12);
               break;
            }
         }
      } else if (var2 == 2) {
    short var11 = var1.getShort();
    short var13 = var1.getShort();

         for (short var15 = 0; var15 < IsoPlayer.numPlayers; var15++) {
    IsoPlayer var17 = IsoPlayer.players[var15];
            if (var17 != nullptr && var17.getOnlineID() == var13) {
               this.stopSendingUpdates(var15, var11);
               break;
            }
         }
      } else if (var2 == 3) {
    short var3 = var1.getShort();
    short var4 = var1.getShort();
    IsoPlayer var5 = (IsoPlayer)GameClient.IDToPlayerMap.get(var3);
         if (var5 != nullptr) {
    BodyDamage var6 = var5.getBodyDamageRemote();
    uint8_t var7 = var1.get();
            if (var7 == 50) {
               var6.setOverallBodyHealth(var1.getFloat());
               var6.setRemotePainLevel(var1.get());
               var6.IsFakeInfected = var1.get() == 1;
               var6.InfectionLevel = var1.getFloat();
               var7 = var1.get();
            }

            while (var7 == 64) {
    uint8_t var8 = var1.get();
    BodyPart var9 = (BodyPart)var6.BodyParts.get(var8);

               for (byte var10 = var1.get(); var10 != 65; var10 = var1.get()) {
                  var9.sync(var1, var10);
               }

               var7 = var1.get();
            }
         }
      }
   }
}
} // namespace network
} // namespace zombie
