#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/PassengerMap/DriverLocal.h"
#include "zombie/network/PassengerMap/PassengerLocal.h"
#include "zombie/network/PassengerMap/PassengerRemote.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <filesystem>

namespace zombie {
namespace network {


class PassengerMap {
public:
    static const int CHUNKS = 7;
    static const int MAX_PASSENGERS = 16;
   private static const PassengerLocal[] perPlayerPngr = new PassengerLocal[4];
   private static const DriverLocal[] perPlayerDriver = new DriverLocal[4];

    static void updatePassenger(IsoPlayer var0) {
      if (var0 != nullptr && var0.getVehicle() != nullptr && !var0.getVehicle().isDriver(var0)) {
    IsoGameCharacter var1 = var0.getVehicle().getDriver();
         if (dynamic_cast<IsoPlayer*>(var1) != nullptr && !((IsoPlayer)var1).isLocalPlayer()) {
    PassengerLocal var2 = perPlayerPngr[var0.PlayerIndex];
            var2.chunkMap = IsoWorld.instance.CurrentCell.ChunkMap[var0.PlayerIndex];
            var2.updateLoaded();
         }
      }
   }

    static void serverReceivePacket(ByteBuffer var0, UdpConnection var1) {
    uint8_t var2 = var0.get();
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    long var5 = var0.getLong();
    IsoPlayer var7 = var1.players[var2];
      if (var7 != nullptr && var7.getVehicle() != nullptr) {
    IsoGameCharacter var8 = var7.getVehicle().getDriver();
         if (dynamic_cast<IsoPlayer*>(var8) != nullptr && var8 != var7) {
    UdpConnection var9 = GameServer.getConnectionFromPlayer((IsoPlayer)var8);
            if (var9 != nullptr) {
    ByteBufferWriter var10 = var9.startPacket();
               PacketType.PassengerMap.doPacket(var10);
               var10.putShort(var7.getVehicle().VehicleID);
               var10.putByte((byte)var7.getVehicle().getSeat(var7));
               var10.putInt(var3);
               var10.putInt(var4);
               var10.putLong(var5);
               PacketType.PassengerMap.send(var9);
            }
         }
      }
   }

    static void clientReceivePacket(ByteBuffer var0) {
    short var1 = var0.getShort();
    uint8_t var2 = var0.get();
    int var3 = var0.getInt();
    int var4 = var0.getInt();
    long var5 = var0.getLong();

      for (int var7 = 0; var7 < IsoPlayer.numPlayers; var7++) {
    IsoPlayer var8 = IsoPlayer.players[var7];
         if (var8 != nullptr && var8.getVehicle() != nullptr) {
    BaseVehicle var9 = var8.getVehicle();
            if (var9.VehicleID == var1 && var9.isDriver(var8)) {
    DriverLocal var10 = perPlayerDriver[var7];
    PassengerRemote var11 = var10.passengers[var2];
               if (var11 == nullptr) {
                  var11 = var10.passengers[var2] = std::make_unique<PassengerRemote>();
               }

               var11.setLoaded(var3, var4, var5);
            }
         }
      }
   }

    static bool isChunkLoaded(BaseVehicle var0, int var1, int var2) {
      if (!GameClient.bClient) {
    return false;
      } else if (var0 != nullptr && var1 >= 0 && var2 >= 0) {
    IsoGameCharacter var3 = var0.getDriver();
         if (dynamic_cast<IsoPlayer*>(var3) != nullptr && ((IsoPlayer)var3).isLocalPlayer()) {
    int var4 = ((IsoPlayer)var3).PlayerIndex;
    DriverLocal var5 = perPlayerDriver[var4];

            for (int var6 = 1; var6 < var0.getMaxPassengers(); var6++) {
    PassengerRemote var7 = var5.passengers[var6];
               if (var7 != nullptr && var7.wx != -1) {
    IsoGameCharacter var8 = var0.getCharacter(var6);
                  if (dynamic_cast<IsoPlayer*>(var8) != nullptr && !((IsoPlayer)var8).isLocalPlayer()) {
    int var9 = var7.wx - 3;
    int var10 = var7.wy - 3;
                     if (var1 >= var9 && var2 >= var10 && var1 < var9 + 7 && var2 < var10 + 7 && (var7.loaded & 1L << var1 - var9 + (var2 - var10) * 7) == 0L) {
    return false;
                     }
                  } else {
                     var7.wx = -1;
                  }
               }
            }

    return true;
         } else {
    return false;
         }
      } else {
    return false;
      }
   }

    static void render(int var0) {
      if (GameClient.bClient) {
    IsoPlayer var1 = IsoPlayer.players[var0];
         if (var1 != nullptr && var1.getVehicle() != nullptr) {
    BaseVehicle var2 = var1.getVehicle();
    int var3 = Core.TileScale;
    uint8_t var4 = 10;
    float var5 = 0.1F;
    float var6 = 0.1F;
    float var7 = 0.1F;
    float var8 = 0.75F;
    float var9 = 0.0F;
    DriverLocal var10 = perPlayerDriver[var0];

            for (int var11 = 1; var11 < var2.getMaxPassengers(); var11++) {
    PassengerRemote var12 = var10.passengers[var11];
               if (var12 != nullptr && var12.wx != -1) {
    IsoGameCharacter var13 = var2.getCharacter(var11);
                  if (dynamic_cast<IsoPlayer*>(var13) != nullptr && !((IsoPlayer)var13).isLocalPlayer()) {
                     for (int var14 = 0; var14 < 7; var14++) {
                        for (int var15 = 0; var15 < 7; var15++) {
    bool var16 = (var12.loaded & 1L << var15 + var14 * 7) != 0L;
                           if (!var16) {
    float var17 = (var12.wx - 3 + var15) * var4;
    float var18 = (var12.wy - 3 + var14) * var4;
    float var19 = IsoUtils.XToScreenExact(var17, var18 + var4, var9, 0);
    float var20 = IsoUtils.YToScreenExact(var17, var18 + var4, var9, 0);
                              SpriteRenderer.instance
                                 .renderPoly(
                                    (int)var19,
                                    (int)var20,
                                    (int)(var19 + var4 * 64 / 2 * var3),
                                    (int)(var20 - var4 * 32 / 2 * var3),
                                    (int)(var19 + var4 * 64 * var3),
                                    (int)var20,
                                    (int)(var19 + var4 * 64 / 2 * var3),
                                    (int)(var20 + var4 * 32 / 2 * var3),
                                    var5,
                                    var6,
                                    var7,
                                    var8
                                 );
                           }
                        }
                     }
                  } else {
                     var12.wx = -1;
                  }
               }
            }
         }
      }
   }

    static void Reset() {
      for (int var0 = 0; var0 < 4; var0++) {
    PassengerLocal var1 = perPlayerPngr[var0];
         var1.wx = -1;
    DriverLocal var2 = perPlayerDriver[var0];

         for (int var3 = 0; var3 < 16; var3++) {
    PassengerRemote var4 = var2.passengers[var3];
            if (var4 != nullptr) {
               var4.wx = -1;
            }
         }
      }
   }

   static {
      for (int var0 = 0; var0 < 4; var0++) {
         perPlayerPngr[var0] = std::make_shared<PassengerLocal>(var0);
         perPlayerDriver[var0] = std::make_unique<DriverLocal>();
      }
   }
}
} // namespace network
} // namespace zombie
