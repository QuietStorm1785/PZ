#include <string>
#include "zombie\globalObjects/SGlobalObjectNetwork.h"

namespace zombie {
namespace globalObjects {

void SGlobalObjectNetwork::receive(ByteBuffer var0, IsoPlayer var1) {
    // TODO: Implement receive
}

void SGlobalObjectNetwork::sendPacket(ByteBuffer var0) {
    // TODO: Implement sendPacket
}

void SGlobalObjectNetwork::writeServerCommand(const std::string& var0, const std::string& var1, KahluaTable var2, ByteBufferWriter var3) {
    // TODO: Implement writeServerCommand
}

void SGlobalObjectNetwork::sendServerCommand(const std::string& var0, const std::string& var1, KahluaTable var2) {
    // TODO: Implement sendServerCommand
}

void SGlobalObjectNetwork::addGlobalObjectOnClient(SGlobalObject var0) {
    // TODO: Implement addGlobalObjectOnClient
}

void SGlobalObjectNetwork::removeGlobalObjectOnClient(GlobalObject var0) {
    // TODO: Implement removeGlobalObjectOnClient
}

void SGlobalObjectNetwork::updateGlobalObjectOnClient(SGlobalObject var0) {
    // TODO: Implement updateGlobalObjectOnClient
}

void SGlobalObjectNetwork::receiveClientCommand(ByteBuffer var0, IsoPlayer var1) {
    // TODO: Implement receiveClientCommand
}

} // namespace globalObjects
} // namespace zombie
