#include <string>
#include "zombie\globalObjects/CGlobalObjectNetwork.h"

namespace zombie {
namespace globalObjects {

void CGlobalObjectNetwork::receive(ByteBuffer var0) {
    // TODO: Implement receive
}

void CGlobalObjectNetwork::receiveServerCommand(ByteBuffer var0) {
    // TODO: Implement receiveServerCommand
}

void CGlobalObjectNetwork::receiveNewLuaObjectAt(ByteBuffer var0) {
    // TODO: Implement receiveNewLuaObjectAt
}

void CGlobalObjectNetwork::receiveRemoveLuaObjectAt(ByteBuffer var0) {
    // TODO: Implement receiveRemoveLuaObjectAt
}

void CGlobalObjectNetwork::receiveUpdateLuaObjectAt(ByteBuffer var0) {
    // TODO: Implement receiveUpdateLuaObjectAt
}

void CGlobalObjectNetwork::sendPacket(ByteBuffer var0) {
    // TODO: Implement sendPacket
}

void CGlobalObjectNetwork::sendClientCommand(IsoPlayer var0, const std::string& var1, const std::string& var2, KahluaTable var3) {
    // TODO: Implement sendClientCommand
}

void CGlobalObjectNetwork::writeClientCommand(IsoPlayer var0, const std::string& var1, const std::string& var2, KahluaTable var3, ByteBufferWriter var4) {
    // TODO: Implement writeClientCommand
}

void CGlobalObjectNetwork::Reset() {
    // TODO: Implement Reset
}

} // namespace globalObjects
} // namespace zombie
