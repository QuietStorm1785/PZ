#include "zombie/globalObjects/CGlobalObjectNetwork.h"

namespace zombie {
namespace globalObjects {

void CGlobalObjectNetwork::receive(ByteBuffer byteBuffer) {
 // TODO: Implement receive
}

void CGlobalObjectNetwork::receiveServerCommand(ByteBuffer byteBuffer) {
 // TODO: Implement receiveServerCommand
}

void CGlobalObjectNetwork::receiveNewLuaObjectAt(ByteBuffer byteBuffer) {
 // TODO: Implement receiveNewLuaObjectAt
}

void CGlobalObjectNetwork::receiveRemoveLuaObjectAt(ByteBuffer byteBuffer) {
 // TODO: Implement receiveRemoveLuaObjectAt
}

void CGlobalObjectNetwork::receiveUpdateLuaObjectAt(ByteBuffer byteBuffer) {
 // TODO: Implement receiveUpdateLuaObjectAt
}

void CGlobalObjectNetwork::sendPacket(ByteBuffer byteBuffer) {
 // TODO: Implement sendPacket
}

void CGlobalObjectNetwork::sendClientCommand(IsoPlayer player, const std::string& string0, const std::string& string1, KahluaTable table) {
 // TODO: Implement sendClientCommand
}

void CGlobalObjectNetwork::writeClientCommand(IsoPlayer player, const std::string& string0, const std::string& string1, KahluaTable table, ByteBufferWriter byteBufferWriter) {
 // TODO: Implement writeClientCommand
}

void CGlobalObjectNetwork::Reset() {
 // TODO: Implement Reset
}

} // namespace globalObjects
} // namespace zombie
