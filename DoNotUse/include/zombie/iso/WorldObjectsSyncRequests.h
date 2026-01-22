#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/WorldObjectsSyncRequests/SyncData.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include <filesystem>

namespace zombie {
namespace iso {


class WorldObjectsSyncRequests {
public:
   public const std::vector<SyncData> requests = std::make_unique<std::vector<>>();
    long timeout = 1000L;

    void putRequest(IsoChunk var1) {
    SyncData var2 = std::make_shared<SyncData>(this);
      var2.x = var1.wx;
      var2.y = var1.wy;
      var2.hashCodeWorldObjects = var1.getHashCodeObjects();
      var2.reqTime = 0L;
      var2.reqCount = 0;
      /* synchronized - TODO: add std::mutex */ (this.requests) {
         this.requests.push_back(var2);
      }
   }

    void sendRequests(UdpConnection var1) {
      if (this.requests.size() != 0) {
    ByteBufferWriter var2 = var1.startPacket();
         PacketType.SyncWorldObjectsReq.doPacket(var2);
    ByteBuffer var3 = var2.bb;
    int var4 = var3.position();
         var2.putShort((short)0);
    int var5 = 0;
         /* synchronized - TODO: add std::mutex */ (this.requests) {
            for (int var7 = 0; var7 < this.requests.size(); var7++) {
    SyncData var8 = this.requests.get(var7);
               if (var8.reqCount > 2) {
                  this.requests.remove(var7);
                  var7--;
               } else {
                  if (var8.reqTime == 0L) {
                     var8.reqTime = System.currentTimeMillis();
                     var5++;
                     var3.putInt(var8.x);
                     var3.putInt(var8.y);
                     var3.putLong(var8.hashCodeWorldObjects);
                     var8.reqCount++;
                  }

                  if (System.currentTimeMillis() - var8.reqTime >= this.timeout) {
                     var8.reqTime = System.currentTimeMillis();
                     var5++;
                     var3.putInt(var8.x);
                     var3.putInt(var8.y);
                     var3.putLong(var8.hashCodeWorldObjects);
                     var8.reqCount++;
                  }

                  if (var5 >= 50) {
                     break;
                  }
               }
            }
         }

         if (var5 == 0) {
            GameClient.connection.cancelPacket();
         } else {
    int var11 = var3.position();
            var3.position(var4);
            var3.putShort((short)var5);
            var3.position(var11);
            PacketType.SyncWorldObjectsReq.send(GameClient.connection);
         }
      }
   }

    void receiveIsoSync(int var1, int var2) {
      /* synchronized - TODO: add std::mutex */ (this.requests) {
         for (int var4 = 0; var4 < this.requests.size(); var4++) {
    SyncData var5 = this.requests.get(var4);
            if (var5.x == var1 && var5.y == var2) {
               this.requests.remove(var4);
            }
         }
      }
   }
}
} // namespace iso
} // namespace zombie
