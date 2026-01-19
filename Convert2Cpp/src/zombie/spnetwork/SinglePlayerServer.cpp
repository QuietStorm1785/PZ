#include "zombie/spnetwork/SinglePlayerServer.h"

namespace zombie {
namespace spnetwork {

void SinglePlayerServer::addIncoming(short var0, ByteBuffer var1, UdpConnection var2) {
    // TODO: Implement addIncoming
}

void SinglePlayerServer::sendObjectChange(IsoObject var0, const std::string& var1, KahluaTable var2, UdpConnection var3) {
    // TODO: Implement sendObjectChange
}

void SinglePlayerServer::sendObjectChange(IsoObject var0, const std::string& var1, KahluaTable var2) {
    // TODO: Implement sendObjectChange
}

void SinglePlayerServer::sendObjectChange(IsoObject var0, const std::string& var1, Object... var2) {
    // TODO: Implement sendObjectChange
}

void SinglePlayerServer::sendServerCommand(const std::string& var0, const std::string& var1, KahluaTable var2, UdpConnection var3) {
    // TODO: Implement sendServerCommand
}

void SinglePlayerServer::sendServerCommand(const std::string& var0, const std::string& var1, KahluaTable var2) {
    // TODO: Implement sendServerCommand
}

void SinglePlayerServer::update() {
    // TODO: Implement update
}

void SinglePlayerServer::mainLoopDealWithNetData(ZomboidNetData var0) {
    // TODO: Implement mainLoopDealWithNetData
}

IsoPlayer SinglePlayerServer::getAnyPlayerFromConnection(UdpConnection var0) {
    // TODO: Implement getAnyPlayerFromConnection
    return nullptr;
}

IsoPlayer SinglePlayerServer::getPlayerFromConnection(UdpConnection var0, int var1) {
    // TODO: Implement getPlayerFromConnection
    return nullptr;
}

void SinglePlayerServer::receiveClientCommand(ByteBuffer var0, UdpConnection var1) {
    // TODO: Implement receiveClientCommand
}

void SinglePlayerServer::receiveGlobalObjects(ByteBuffer var0, UdpConnection var1) {
    // TODO: Implement receiveGlobalObjects
}

void SinglePlayerServer::Reset() {
    // TODO: Implement Reset
}

} // namespace spnetwork
} // namespace zombie
