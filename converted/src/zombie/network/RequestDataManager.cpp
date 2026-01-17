#include "zombie/network/RequestDataManager.h"

namespace zombie {
namespace network {

private
RequestDataManager::RequestDataManager() {
  // TODO: Implement RequestDataManager
  return nullptr;
}

RequestDataManager RequestDataManager::getInstance() {
  // TODO: Implement getInstance
  return nullptr;
}

void RequestDataManager::ACKWasReceived(RequestDataPacket.RequestID requestID,
                                        UdpConnection udpConnection, int var3) {
  // TODO: Implement ACKWasReceived
}

void RequestDataManager::putDataForTransmit(
    RequestDataPacket.RequestID requestID, UdpConnection udpConnection,
    ByteBuffer byteBuffer) {
  // TODO: Implement putDataForTransmit
}

void RequestDataManager::disconnect(UdpConnection udpConnection) {
  // TODO: Implement disconnect
}

void RequestDataManager::clear() {
  // TODO: Implement clear
}

void RequestDataManager::sendData(RequestDataManager.RequestData requestData) {
  // TODO: Implement sendData
}

ByteBuffer
RequestDataManager::receiveClientData(RequestDataPacket.RequestID requestID,
                                      ByteBuffer byteBuffer, int int1,
                                      int int2) {
  // TODO: Implement receiveClientData
  return nullptr;
}

public
RequestDataManager::RequestData(RequestDataPacket.RequestID requestID,
                                ByteBuffer byteBuffer, long long0) {
  // TODO: Implement RequestData
  return nullptr;
}

public
RequestDataManager::RequestData(RequestDataPacket.RequestID requestID, int int0,
                                long long0) {
  // TODO: Implement RequestData
  return nullptr;
}

} // namespace network
} // namespace zombie
