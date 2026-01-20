#include "zombie\savefile/PlayerDB.h"

namespace zombie {
namespace savefile {

void PlayerDB::setAllow(bool var0) {
    // TODO: Implement setAllow
}

bool PlayerDB::isAllow() {
    // TODO: Implement isAllow
    return false;
}

bool PlayerDB::isAvailable() {
    // TODO: Implement isAvailable
    return false;
}

public PlayerDB::PlayerDB() {
    // TODO: Implement PlayerDB
    return nullptr;
}

void PlayerDB::create() {
    // TODO: Implement create
}

void PlayerDB::close() {
    // TODO: Implement close
}

int PlayerDB::allocateID() {
    // TODO: Implement allocateID
    return 0;
}

PlayerData PlayerDB::allocPlayerData() {
    // TODO: Implement allocPlayerData
    return nullptr;
}

void PlayerDB::releasePlayerData(PlayerData var1) {
    // TODO: Implement releasePlayerData
}

void PlayerDB::updateMain() {
    // TODO: Implement updateMain
}

void PlayerDB::updateWorldStreamer() {
    // TODO: Implement updateWorldStreamer
}

void PlayerDB::savePlayerAsync(IsoPlayer var1) {
    // TODO: Implement savePlayerAsync
}

void PlayerDB::savePlayersAsync() {
    // TODO: Implement savePlayersAsync
}

void PlayerDB::savePlayers() {
    // TODO: Implement savePlayers
}

void PlayerDB::saveLocalPlayersForce() {
    // TODO: Implement saveLocalPlayersForce
}

void PlayerDB::importPlayersFromVehiclesDB() {
    // TODO: Implement importPlayersFromVehiclesDB
}

void PlayerDB::uploadLocalPlayers2DB() {
    // TODO: Implement uploadLocalPlayers2DB
}

bool PlayerDB::loadPlayer(int var1, IsoPlayer var2) {
    // TODO: Implement loadPlayer
    return false;
}

bool PlayerDB::loadLocalPlayer(int var1) {
    // TODO: Implement loadLocalPlayer
    return false;
}

bool PlayerDB::loadLocalPlayerInfo(int var1) {
    // TODO: Implement loadLocalPlayerInfo
    return false;
}

} // namespace savefile
} // namespace zombie
