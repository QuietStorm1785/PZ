#include "zombie/core/raknet/UdpEngine.h"

namespace zombie {
namespace core {
namespace raknet {

public UdpEngine::UdpEngine(int _port, int UDPPort, int _maxConnections, const std::string& serverPassword, bool bListen) {
 // TODO: Implement UdpEngine
 return nullptr;
}

void UdpEngine::threadRun() {
 // TODO: Implement threadRun
}

void UdpEngine::Shutdown() {
 // TODO: Implement Shutdown
}

void UdpEngine::SetServerPassword(const std::string& password) {
 // TODO: Implement SetServerPassword
}

std::string UdpEngine::hashServerPassword(const std::string& password) {
 // TODO: Implement hashServerPassword
 return "";
}

std::string UdpEngine::getServerIP() {
 // TODO: Implement getServerIP
 return "";
}

long UdpEngine::getClientSteamID(long guid) {
 // TODO: Implement getClientSteamID
 return 0;
}

long UdpEngine::getClientOwnerSteamID(long guid) {
 // TODO: Implement getClientOwnerSteamID
 return 0;
}

ByteBufferWriter UdpEngine::startPacket() {
 // TODO: Implement startPacket
 return nullptr;
}

void UdpEngine::endPacketBroadcast(PacketTypes.PacketType packetType) {
 // TODO: Implement endPacketBroadcast
}

void UdpEngine::endPacketBroadcastExcept(int priority, int reliability, UdpConnection connection) {
 // TODO: Implement endPacketBroadcastExcept
}

void UdpEngine::connected() {
 // TODO: Implement connected
}

void UdpEngine::decode(ByteBuffer byteBuffer) {
 // TODO: Implement decode
}

void UdpEngine::removeConnection(int int0) {
 // TODO: Implement removeConnection
}

UdpConnection UdpEngine::addConnection(int int0, long long0) {
 // TODO: Implement addConnection
 return nullptr;
}

ByteBuffer UdpEngine::Receive() {
 // TODO: Implement Receive
 return nullptr;
}

UdpConnection UdpEngine::getActiveConnection(long connection) {
 // TODO: Implement getActiveConnection
 return nullptr;
}

void UdpEngine::Connect(const std::string& string0, int int0, const std::string& string1, bool boolean0) {
 // TODO: Implement Connect
}

void UdpEngine::forceDisconnect(long connectedGUID, const std::string& message) {
 // TODO: Implement forceDisconnect
}

void UdpEngine::removeConnection(long long0) {
 // TODO: Implement removeConnection
}

RakNetPeerInterface UdpEngine::getPeer() {
 // TODO: Implement getPeer
 return nullptr;
}

int UdpEngine::getMaxConnections() {
 // TODO: Implement getMaxConnections
 return 0;
}

std::string UdpEngine::getDescription() {
 // TODO: Implement getDescription
 return "";
}

} // namespace raknet
} // namespace core
} // namespace zombie
