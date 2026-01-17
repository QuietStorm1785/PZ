#pragma once
#include "zombie/core/Translator.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/gameStates/GameLoadingState.h"
#include "zombie/network/packets/RequestDataPacket.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class RequestDataManager {
public:
  static const int smallFileSize = 1024;
  static const int maxLargeFileSize = 52428800;
  static const int packSize = 204800;
private
  final ArrayList<RequestDataManager.RequestData> requests =
      std::make_unique<ArrayList<>>();
  static RequestDataManager instance;

private
  RequestDataManager() {}

  static RequestDataManager getInstance() {
    if (instance == nullptr) {
      instance = std::make_unique<RequestDataManager>();
    }

    return instance;
  }

  void ACKWasReceived(RequestDataPacket.RequestID requestID,
                      UdpConnection udpConnection, int var3) {
    RequestDataManager.RequestData requestData = nullptr;

    for (int int0 = 0; int0 <= this.requests.size(); int0++) {
      if (this.requests.get(int0).connectionGUID ==
          udpConnection.getConnectedGUID()) {
        requestData = this.requests.get(int0);
        break;
      }
    }

    if (requestData != nullptr && requestData.id == requestID) {
      this.sendData(requestData);
    }
  }

  void putDataForTransmit(RequestDataPacket.RequestID requestID,
                          UdpConnection udpConnection, ByteBuffer byteBuffer) {
    RequestDataManager.RequestData requestData =
        new RequestDataManager.RequestData(requestID, byteBuffer,
                                           udpConnection.getConnectedGUID());
    this.requests.add(requestData);
    this.sendData(requestData);
  }

  void disconnect(UdpConnection udpConnection) {
    long long0 = System.currentTimeMillis();
    this.requests.removeIf(
        requestData->long0 - requestData.creationTime > 60000L ||
        requestData.connectionGUID == udpConnection.getConnectedGUID());
  }

  void clear() { this.requests.clear(); }

  void sendData(RequestDataManager.RequestData requestData) {
    requestData.creationTime = System.currentTimeMillis();
    int int0 = requestData.bb.limit();
    requestData.realTransmittedFromLastACK = 0;
    UdpConnection udpConnection =
        GameServer.udpEngine.getActiveConnection(requestData.connectionGUID);
    RequestDataPacket requestDataPacket = new RequestDataPacket();
    requestDataPacket.setPartData(requestData.id, requestData.bb);

    while (requestData.realTransmittedFromLastACK < 204800) {
      int int1 = Math.min(1024, int0 - requestData.realTransmitted);
      if (int1 == 0) {
        break;
      }

      requestDataPacket.setPartDataParameters(requestData.realTransmitted,
                                              int1);
      ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
      PacketTypes.PacketType.RequestData.doPacket(byteBufferWriter);
      requestDataPacket.write(byteBufferWriter);
      PacketTypes.PacketType.RequestData.send(udpConnection);
      requestData.realTransmittedFromLastACK += int1;
      requestData.realTransmitted += int1;
    }

    if (requestData.realTransmitted == int0) {
      this.requests.remove(requestData);
    }
  }

  ByteBuffer receiveClientData(RequestDataPacket.RequestID requestID,
                               ByteBuffer byteBuffer, int int1, int int2) {
    RequestDataManager.RequestData requestData = nullptr;

    for (int int0 = 0; int0 < this.requests.size(); int0++) {
      if (this.requests.get(int0).id == requestID) {
        requestData = this.requests.get(int0);
        break;
      }
    }

    if (requestData == nullptr) {
      requestData = new RequestDataManager.RequestData(requestID, int1, 0L);
      this.requests.add(requestData);
    }

    requestData.bb.position(int2);
    requestData.bb.put(byteBuffer.array(), 0, byteBuffer.limit());
    requestData.realTransmitted =
        requestData.realTransmitted + byteBuffer.limit();
    requestData.realTransmittedFromLastACK =
        requestData.realTransmittedFromLastACK + byteBuffer.limit();
    if (requestData.realTransmittedFromLastACK >= 204800) {
      requestData.realTransmittedFromLastACK = 0;
      RequestDataPacket requestDataPacket = new RequestDataPacket();
      requestDataPacket.setACK(requestData.id);
      ByteBufferWriter byteBufferWriter = GameClient.connection.startPacket();
      PacketTypes.PacketType.RequestData.doPacket(byteBufferWriter);
      requestDataPacket.write(byteBufferWriter);
      PacketTypes.PacketType.RequestData.send(GameClient.connection);
    }

    GameLoadingState.GameLoadingString = Translator.getText(
        "IGUI_MP_DownloadedLargeFile", requestData.realTransmitted * 100 / int1,
        requestData.id.getDescriptor());
    if (requestData.realTransmitted == int1) {
      this.requests.remove(requestData);
      requestData.bb.position(0);
      return requestData.bb;
    } else {
      return null;
    }
  }

  static class RequestData {
  private
    final RequestDataPacket.RequestID id;
    const ByteBuffer bb;
    const long connectionGUID;
    long creationTime = System.currentTimeMillis();
    int realTransmitted;
    int realTransmittedFromLastACK;

  public
    RequestData(RequestDataPacket.RequestID requestID, ByteBuffer byteBuffer,
                long long0) {
      this.id = requestID;
      this.bb = ByteBuffer.allocate(byteBuffer.position());
      this.bb.put(byteBuffer.array(), 0, this.bb.limit());
      this.connectionGUID = long0;
      this.realTransmitted = 0;
      this.realTransmittedFromLastACK = 0;
    }

  public
    RequestData(RequestDataPacket.RequestID requestID, int int0, long long0) {
      this.id = requestID;
      this.bb = ByteBuffer.allocate(int0);
      this.bb.clear();
      this.connectionGUID = long0;
      this.realTransmitted = 0;
      this.realTransmittedFromLastACK = 0;
    }
  }
}
} // namespace network
} // namespace zombie
