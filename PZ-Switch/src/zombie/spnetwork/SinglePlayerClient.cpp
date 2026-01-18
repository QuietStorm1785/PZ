#include "zombie/spnetwork/SinglePlayerClient.h"

namespace zombie {
namespace spnetwork {

void SinglePlayerClient::addIncoming(short short0, ByteBuffer byteBuffer) {
 // TODO: Implement addIncoming
}

void SinglePlayerClient::update() {
 // TODO: Implement update
}

void SinglePlayerClient::mainLoopDealWithNetData(
 ZomboidNetData zomboidNetData) {
 // TODO: Implement mainLoopDealWithNetData
}

void SinglePlayerClient::delayPacket(int var0, int var1, int var2) {
 // TODO: Implement delayPacket
}

IsoPlayer SinglePlayerClient::getPlayerByID(int int0) {
 // TODO: Implement getPlayerByID
 return nullptr;
}

void SinglePlayerClient::receiveObjectChange(ByteBuffer byteBuffer) {
 // TODO: Implement receiveObjectChange
}

void SinglePlayerClient::sendClientCommand(IsoPlayer player,
 const std::string &string0,
 const std::string &string1,
 KahluaTable table) {
 // TODO: Implement sendClientCommand
}

void SinglePlayerClient::receiveServerCommand(ByteBuffer byteBuffer) {
 // TODO: Implement receiveServerCommand
}

void SinglePlayerClient::Reset() {
 // TODO: Implement Reset
}

void SinglePlayerClient::Send(ByteBuffer byteBuffer) {
 // TODO: Implement Send
}

void SinglePlayerClient::Receive(ByteBuffer byteBuffer) {
 // TODO: Implement Receive
}

} // namespace spnetwork
} // namespace zombie
