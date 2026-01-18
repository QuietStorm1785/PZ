#include "zombie/globalObjects/SGlobalObjectNetwork.h"

namespace zombie {
namespace globalObjects {

void SGlobalObjectNetwork::receive(ByteBuffer byteBuffer, IsoPlayer player) {
  // TODO: Implement receive
}

void SGlobalObjectNetwork::sendPacket(ByteBuffer byteBuffer) {
  // TODO: Implement sendPacket
}

void SGlobalObjectNetwork::writeServerCommand(
    const std::string &string0, const std::string &string1, KahluaTable table,
    ByteBufferWriter byteBufferWriter) {
  // TODO: Implement writeServerCommand
}

void SGlobalObjectNetwork::sendServerCommand(const std::string &string0,
                                             const std::string &string1,
                                             KahluaTable table) {
  // TODO: Implement sendServerCommand
}

void SGlobalObjectNetwork::addGlobalObjectOnClient(
    SGlobalObject sGlobalObject) {
  // TODO: Implement addGlobalObjectOnClient
}

void SGlobalObjectNetwork::removeGlobalObjectOnClient(
    GlobalObject globalObject) {
  // TODO: Implement removeGlobalObjectOnClient
}

void SGlobalObjectNetwork::updateGlobalObjectOnClient(
    SGlobalObject sGlobalObject) {
  // TODO: Implement updateGlobalObjectOnClient
}

void SGlobalObjectNetwork::receiveClientCommand(ByteBuffer byteBuffer,
                                                IsoPlayer player) {
  // TODO: Implement receiveClientCommand
}

} // namespace globalObjects
} // namespace zombie
