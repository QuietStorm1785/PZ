#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Translator.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/gameStates/GameLoadingState.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/RequestDataManager/RequestData.h"
#include "zombie/network/packets/RequestDataPacket.h"
#include "zombie/network/packets/RequestDataPacket/RequestID.h"
#include <filesystem>

namespace zombie {
namespace network {


class RequestDataManager {
public:
    static const int smallFileSize = 1024;
    static const int maxLargeFileSize = 52428800;
    static const int packSize = 204800;
   private const std::vector<RequestData> requests = std::make_unique<std::vector<>>();
    static RequestDataManager instance;

    private RequestDataManager() {
   }

    static RequestDataManager getInstance() {
      if (instance == nullptr) {
         instance = std::make_unique<RequestDataManager>();
      }

    return instance;
   }

    void ACKWasReceived(RequestID var1, UdpConnection var2, int var3) {
    RequestData var4 = nullptr;

      for (int var5 = 0; var5 <= this.requests.size(); var5++) {
         if (this.requests.get(var5).connectionGUID == var2.getConnectedGUID()) {
            var4 = this.requests.get(var5);
            break;
         }
      }

      if (var4 != nullptr && var4.id == var1) {
         this.sendData(var4);
      }
   }

    void putDataForTransmit(RequestID var1, UdpConnection var2, ByteBuffer var3) {
    RequestData var4 = std::make_shared<RequestData>(var1, var3, var2.getConnectedGUID());
      this.requests.push_back(var4);
      this.sendData(var4);
   }

    void disconnect(UdpConnection var1) {
    long var2 = System.currentTimeMillis();
      this.requests.removeIf(var3 -> var2 - var3.creationTime > 60000L || var3.connectionGUID == var1.getConnectedGUID());
   }

    void clear() {
      this.requests.clear();
   }

    void sendData(RequestData var1) {
      var1.creationTime = System.currentTimeMillis();
    int var2 = var1.bb.limit();
      var1.realTransmittedFromLastACK = 0;
    UdpConnection var3 = GameServer.udpEngine.getActiveConnection(var1.connectionGUID);
    RequestDataPacket var4 = std::make_shared<RequestDataPacket>();
      var4.setPartData(var1.id, var1.bb);

      while (var1.realTransmittedFromLastACK < 204800) {
    int var5 = Math.min(1024, var2 - var1.realTransmitted);
         if (var5 == 0) {
            break;
         }

         var4.setPartDataParameters(var1.realTransmitted, var5);
    ByteBufferWriter var6 = var3.startPacket();
         PacketType.RequestData.doPacket(var6);
         var4.write(var6);
         PacketType.RequestData.send(var3);
         var1.realTransmittedFromLastACK += var5;
         var1.realTransmitted += var5;
      }

      if (var1.realTransmitted == var2) {
         this.requests.remove(var1);
      }
   }

    ByteBuffer receiveClientData(RequestID var1, ByteBuffer var2, int var3, int var4) {
    RequestData var5 = nullptr;

      for (int var6 = 0; var6 < this.requests.size(); var6++) {
         if (this.requests.get(var6).id == var1) {
            var5 = this.requests.get(var6);
            break;
         }
      }

      if (var5 == nullptr) {
         var5 = std::make_shared<RequestData>(var1, var3, 0L);
         this.requests.push_back(var5);
      }

      var5.bb.position(var4);
      var5.bb.put(var2.array(), 0, var2.limit());
      var5.realTransmitted = var5.realTransmitted + var2.limit();
      var5.realTransmittedFromLastACK = var5.realTransmittedFromLastACK + var2.limit();
      if (var5.realTransmittedFromLastACK >= 204800) {
         var5.realTransmittedFromLastACK = 0;
    RequestDataPacket var8 = std::make_shared<RequestDataPacket>();
         var8.setACK(var5.id);
    ByteBufferWriter var7 = GameClient.connection.startPacket();
         PacketType.RequestData.doPacket(var7);
         var8.write(var7);
         PacketType.RequestData.send(GameClient.connection);
      }

      GameLoadingState.GameLoadingString = Translator.getText("IGUI_MP_DownloadedLargeFile", var5.realTransmitted * 100 / var3, var5.id.getDescriptor());
      if (var5.realTransmitted == var3) {
         this.requests.remove(var5);
         var5.bb.position(0);
         return var5.bb;
      } else {
    return nullptr;
      }
   }
}
} // namespace network
} // namespace zombie
