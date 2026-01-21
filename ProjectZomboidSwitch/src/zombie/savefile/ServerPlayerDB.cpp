#include <string>
#include "zombie/savefile/ServerPlayerDB.h"

namespace zombie {
namespace savefile {

void ServerPlayerDB::setAllow(bool var0) {
    // TODO: Implement setAllow
}

bool ServerPlayerDB::isAllow() {
    // TODO: Implement isAllow
    return false;
}

bool ServerPlayerDB::isAvailable() {
    // TODO: Implement isAvailable
    return false;
}

public ServerPlayerDB::ServerPlayerDB() {
    // TODO: Implement ServerPlayerDB
    return nullptr;
}

void ServerPlayerDB::close() {
    // TODO: Implement close
}

void ServerPlayerDB::create() {
    // TODO: Implement create
}

void ServerPlayerDB::process() {
    // TODO: Implement process
}

void ServerPlayerDB::serverUpdateNetworkCharacter(ByteBuffer var1, UdpConnection var2) {
    // TODO: Implement serverUpdateNetworkCharacter
}

void ServerPlayerDB::serverUpdateNetworkCharacterInt(NetworkCharacterData var1) {
    // TODO: Implement serverUpdateNetworkCharacterInt
}

void ServerPlayerDB::serverConvertNetworkCharacter(const std::string& var1, const std::string& var2) {
    // TODO: Implement serverConvertNetworkCharacter
}

void ServerPlayerDB::serverLoadNetworkCharacter(ByteBuffer var1, UdpConnection var2) {
    // TODO: Implement serverLoadNetworkCharacter
}

} // namespace savefile
} // namespace zombie
