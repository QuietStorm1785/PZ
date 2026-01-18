#include "zombie/spnetwork/SinglePlayerServer.h"

namespace zombie {
namespace spnetwork {

void SinglePlayerServer::addIncoming(short short0, ByteBuffer byteBuffer,
 UdpConnection udpConnection) {
 // TODO: Implement addIncoming
}

void SinglePlayerServer::sendObjectChange(IsoObject object,
 const std::string &string,
 KahluaTable table,
 UdpConnection udpConnection) {
 // TODO: Implement sendObjectChange
}

void SinglePlayerServer::sendObjectChange(IsoObject object,
 const std::string &string,
 KahluaTable table) {
 // TODO: Implement sendObjectChange
}

void SinglePlayerServer::sendObjectChange(IsoObject object0,
 const std::string &string,
 Object... objects) {
 // TODO: Implement sendObjectChange
}

void SinglePlayerServer::sendServerCommand(const std::string &string0,
 const std::string &string1,
 KahluaTable table,
 UdpConnection udpConnection) {
 // TODO: Implement sendServerCommand
}

void SinglePlayerServer::sendServerCommand(const std::string &string0,
 const std::string &string1,
 KahluaTable table) {
 // TODO: Implement sendServerCommand
}

void SinglePlayerServer::update() {
 // TODO: Implement update
}

void SinglePlayerServer::mainLoopDealWithNetData(
 ZomboidNetData zomboidNetData) {
 // TODO: Implement mainLoopDealWithNetData
}

IsoPlayer
SinglePlayerServer::getAnyPlayerFromConnection(UdpConnection udpConnection) {
 // TODO: Implement getAnyPlayerFromConnection
 return nullptr;
}

IsoPlayer
SinglePlayerServer::getPlayerFromConnection(UdpConnection udpConnection,
 int int0) {
 // TODO: Implement getPlayerFromConnection
 return nullptr;
}

void SinglePlayerServer::receiveClientCommand(ByteBuffer byteBuffer,
 UdpConnection udpConnection) {
 // TODO: Implement receiveClientCommand
}

void SinglePlayerServer::receiveGlobalObjects(ByteBuffer byteBuffer,
 UdpConnection udpConnection) {
 // TODO: Implement receiveGlobalObjects
}

void SinglePlayerServer::Reset() {
 // TODO: Implement Reset
}

void SinglePlayerServer::Send(ByteBuffer byteBuffer) {
 // TODO: Implement Send
}

void SinglePlayerServer::Receive(ByteBuffer byteBuffer) {
 // TODO: Implement Receive
}

} // namespace spnetwork
} // namespace zombie
