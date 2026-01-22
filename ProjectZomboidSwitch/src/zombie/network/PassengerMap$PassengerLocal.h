#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/network/PacketTypes/PacketType.h"

namespace zombie {
namespace network {


class PassengerMap {
public:
    const int playerIndex;
    IsoChunkMap chunkMap;
    int wx = -1;
    int wy = -1;
    long loaded = 0L;

   PassengerMap$PassengerLocal(int var1) {
      this.playerIndex = var1;
   }

    bool setLoaded() {
    int var1 = this.chunkMap.WorldX;
    int var2 = this.chunkMap.WorldY;
    Vector3f var3 = IsoPlayer.players[this.playerIndex].getVehicle().jniLinearVelocity;
    float var4 = Math.abs(var3.x);
    float var5 = Math.abs(var3.z);
    bool var6 = var3.x < 0.0F && var4 > var5;
    bool var7 = var3.x > 0.0F && var4 > var5;
    bool var8 = var3.z < 0.0F && var5 > var4;
    bool var9 = var3.z > 0.0F && var5 > var4;
      if (var7) {
         var1++;
      } else if (var6) {
         var1--;
      } else if (var8) {
         var2--;
      } else if (var9) {
         var2++;
      }

    long var10 = 0L;

      for (int var12 = 0; var12 < 7; var12++) {
         for (int var13 = 0; var13 < 7; var13++) {
    IsoChunk var14 = this.chunkMap.getChunk(IsoChunkMap.ChunkGridWidth / 2 - 3 + var13, IsoChunkMap.ChunkGridWidth / 2 - 3 + var12);
            if (var14 != nullptr && var14.bLoaded) {
               var10 |= 1L << var13 + var12 * 7;
            }
         }
      }

    bool var15 = var1 != this.wx || var2 != this.wy || var10 != this.loaded;
      if (var15) {
         this.wx = var1;
         this.wy = var2;
         this.loaded = var10;
      }

    return var15;
   }

    void updateLoaded() {
      if (this.setLoaded()) {
         this.clientSendPacket(GameClient.connection);
      }
   }

    void clientSendPacket(UdpConnection var1) {
    ByteBufferWriter var2 = var1.startPacket();
      PacketType.PassengerMap.doPacket(var2);
      var2.putByte((byte)this.playerIndex);
      var2.putInt(this.wx);
      var2.putInt(this.wy);
      var2.putLong(this.loaded);
      PacketType.PassengerMap.send(var1);
   }
}
} // namespace network
} // namespace zombie
