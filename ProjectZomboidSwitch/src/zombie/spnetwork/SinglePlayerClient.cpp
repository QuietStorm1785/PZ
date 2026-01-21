#include <string>
#include "zombie/spnetwork/SinglePlayerClient.h"

namespace zombie {
namespace spnetwork {

void SinglePlayerClient::addIncoming(short var0, ByteBuffer var1) {
    // TODO: Implement addIncoming
}

void SinglePlayerClient::update() {
    // TODO: Implement update
}

void SinglePlayerClient::mainLoopDealWithNetData(ZomboidNetData var0) {
    // TODO: Implement mainLoopDealWithNetData
}

void SinglePlayerClient::delayPacket(int var0, int var1, int var2) {
    // TODO: Implement delayPacket
}

IsoPlayer SinglePlayerClient::getPlayerByID(int var0) {
    // TODO: Implement getPlayerByID
    return nullptr;
}

void SinglePlayerClient::receiveObjectChange(ByteBuffer var0) {
    // TODO: Implement receiveObjectChange
}

void SinglePlayerClient::sendClientCommand(IsoPlayer var0, const std::string& var1, const std::string& var2, KahluaTable var3) {
    // TODO: Implement sendClientCommand
}

void SinglePlayerClient::receiveServerCommand(ByteBuffer var0) {
    // TODO: Implement receiveServerCommand
}

void SinglePlayerClient::Reset() {
    // TODO: Implement Reset
}

} // namespace spnetwork
} // namespace zombie
