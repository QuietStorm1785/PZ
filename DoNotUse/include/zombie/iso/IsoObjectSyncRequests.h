#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/SystemDisabler.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/IsoObjectSyncRequests/SyncData.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include <filesystem>

namespace zombie {
namespace iso {


class IsoObjectSyncRequests {
public:
   public const std::vector<SyncData> requests = std::make_unique<std::vector<>>();
    long timeout = 1000L;

    void putRequest(IsoGridSquare var1, IsoObject var2) {
      if (GameClient.bClient) {
         this.putRequest(var1.x, var1.y, var1.z, (byte)var1.getObjects().indexOf(var2));
      }
   }

    void putRequestLoad(IsoGridSquare var1) {
      if (GameClient.bClient) {
         this.putRequest(var1.x, var1.y, var1.z, (byte)var1.getObjects().size());
      }
   }

    void putRequest(int var1, int var2, int var3, uint8_t var4) {
      if (SystemDisabler.doObjectStateSyncEnable) {
    SyncData var5 = std::make_shared<SyncData>(this);
         var5.x = var1;
         var5.y = var2;
         var5.z = var3;
         var5.objIndex = var4;
         var5.reqTime = 0L;
         var5.reqCount = 0;
         /* synchronized - TODO: add std::mutex */ (this.requests) {
            this.requests.push_back(var5);
         }
      }
   }

    void sendRequests(UdpConnection var1) {
      if (SystemDisabler.doObjectStateSyncEnable) {
         if (this.requests.size() != 0) {
    ByteBufferWriter var2 = var1.startPacket();
            PacketType.SyncIsoObjectReq.doPacket(var2);
    ByteBuffer var3 = var2.bb;
    int var4 = var3.position();
            var2.putShort((short)0);
    int var5 = 0;
            /* synchronized - TODO: add std::mutex */ (this.requests) {
               for (int var7 = 0; var7 < this.requests.size(); var7++) {
    SyncData var8 = this.requests.get(var7);
                  if (var8.reqCount > 4) {
                     this.requests.remove(var7);
                     var7--;
                  } else {
                     if (var8.reqTime == 0L) {
                        var8.reqTime = System.currentTimeMillis();
                        var5++;
                        var3.putInt(var8.x);
                        var3.putInt(var8.y);
                        var3.putInt(var8.z);
                        var3.put(var8.objIndex);
                        var8.reqCount++;
                     }

                     if (System.currentTimeMillis() - var8.reqTime >= this.timeout) {
                        var8.reqTime = System.currentTimeMillis();
                        var5++;
                        var3.putInt(var8.x);
                        var3.putInt(var8.y);
                        var3.putInt(var8.z);
                        var3.put(var8.objIndex);
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
               PacketType.SyncIsoObjectReq.send(GameClient.connection);
            }
         }
      }
   }

    void receiveIsoSync(int var1, int var2, int var3, uint8_t var4) {
      /* synchronized - TODO: add std::mutex */ (this.requests) {
         for (int var6 = 0; var6 < this.requests.size(); var6++) {
    SyncData var7 = this.requests.get(var6);
            if (var7.x == var1 && var7.y == var2 && var7.z == var3 && var7.objIndex == var4) {
               this.requests.remove(var6);
            }
         }
      }
   }
}
} // namespace iso
} // namespace zombie
