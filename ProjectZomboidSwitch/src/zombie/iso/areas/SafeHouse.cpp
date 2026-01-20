#include <string>
#include <vector>
#include "zombie\iso\areas/SafeHouse.h"

namespace zombie {
namespace iso {
namespace areas {

void SafeHouse::init() {
    // TODO: Implement init
}

SafeHouse SafeHouse::addSafeHouse(int var0, int var1, int var2, int var3, const std::string& var4, bool var5) {
    // TODO: Implement addSafeHouse
    return nullptr;
}

SafeHouse SafeHouse::addSafeHouse(IsoGridSquare var0, IsoPlayer var1) {
    // TODO: Implement addSafeHouse
    return nullptr;
}

SafeHouse SafeHouse::hasSafehouse(const std::string& var0) {
    // TODO: Implement hasSafehouse
    return nullptr;
}

SafeHouse SafeHouse::hasSafehouse(IsoPlayer var0) {
    // TODO: Implement hasSafehouse
    return nullptr;
}

return SafeHouse::hasSafehouse() {
    // TODO: Implement hasSafehouse
    return nullptr;
}

void SafeHouse::updateSafehousePlayersConnected() {
    // TODO: Implement updateSafehousePlayersConnected
}

void SafeHouse::updatePlayersConnected() {
    // TODO: Implement updatePlayersConnected
}

SafeHouse SafeHouse::getSafeHouse(IsoGridSquare var0) {
    // TODO: Implement getSafeHouse
    return nullptr;
}

return SafeHouse::isSafeHouse() {
    // TODO: Implement isSafeHouse
    return nullptr;
}

SafeHouse SafeHouse::getSafeHouse(int var0, int var1, int var2, int var3) {
    // TODO: Implement getSafeHouse
    return nullptr;
}

SafeHouse SafeHouse::isSafeHouse(IsoGridSquare var0, const std::string& var1, bool var2) {
    // TODO: Implement isSafeHouse
    return nullptr;
}

void SafeHouse::clearSafehouseList() {
    // TODO: Implement clearSafehouseList
}

bool SafeHouse::playerAllowed(IsoPlayer var1) {
    // TODO: Implement playerAllowed
    return false;
}

bool SafeHouse::playerAllowed(const std::string& var1) {
    // TODO: Implement playerAllowed
    return false;
}

void SafeHouse::addPlayer(const std::string& var1) {
    // TODO: Implement addPlayer
}

void SafeHouse::removePlayer(const std::string& var1) {
    // TODO: Implement removePlayer
}

void SafeHouse::syncSafehouse() {
    // TODO: Implement syncSafehouse
}

void SafeHouse::removeSafeHouse(IsoPlayer var1) {
    // TODO: Implement removeSafeHouse
}

void SafeHouse::removeSafeHouse(IsoPlayer var1, bool var2) {
    // TODO: Implement removeSafeHouse
}

void SafeHouse::save(ByteBuffer var1) {
    // TODO: Implement save
}

SafeHouse SafeHouse::load(ByteBuffer var0, int var1) {
    // TODO: Implement load
    return nullptr;
}

std::string SafeHouse::canBeSafehouse(IsoGridSquare var0, IsoPlayer var1) {
    // TODO: Implement canBeSafehouse
    return "";
}

void SafeHouse::kickOutOfSafehouse(IsoPlayer var1) {
    // TODO: Implement kickOutOfSafehouse
}

void SafeHouse::checkTrespass(IsoPlayer var1) {
    // TODO: Implement checkTrespass
}

SafeHouse SafeHouse::alreadyHaveSafehouse(const std::string& var1) {
    // TODO: Implement alreadyHaveSafehouse
    return nullptr;
}

SafeHouse SafeHouse::alreadyHaveSafehouse(IsoPlayer var1) {
    // TODO: Implement alreadyHaveSafehouse
    return nullptr;
}

bool SafeHouse::allowSafeHouse(IsoPlayer var0) {
    // TODO: Implement allowSafeHouse
    return false;
}

void SafeHouse::updateSafehouse(IsoPlayer var1) {
    // TODO: Implement updateSafehouse
}

public SafeHouse::SafeHouse(int var1, int var2, int var3, int var4, const std::string& var5) {
    // TODO: Implement SafeHouse
    return nullptr;
}

std::string SafeHouse::getId() {
    // TODO: Implement getId
    return "";
}

int SafeHouse::getX() {
    // TODO: Implement getX
    return 0;
}

void SafeHouse::setX(int var1) {
    // TODO: Implement setX
}

int SafeHouse::getY() {
    // TODO: Implement getY
    return 0;
}

void SafeHouse::setY(int var1) {
    // TODO: Implement setY
}

int SafeHouse::getW() {
    // TODO: Implement getW
    return 0;
}

void SafeHouse::setW(int var1) {
    // TODO: Implement setW
}

int SafeHouse::getH() {
    // TODO: Implement getH
    return 0;
}

void SafeHouse::setH(int var1) {
    // TODO: Implement setH
}

int SafeHouse::getX2() {
    // TODO: Implement getX2
    return 0;
}

int SafeHouse::getY2() {
    // TODO: Implement getY2
    return 0;
}

bool SafeHouse::containsLocation(float var1, float var2) {
    // TODO: Implement containsLocation
    return false;
}

void SafeHouse::setPlayers(std::vector<std::string> var1) {
    // TODO: Implement setPlayers
}

std::string SafeHouse::getOwner() {
    // TODO: Implement getOwner
    return "";
}

void SafeHouse::setOwner(const std::string& var1) {
    // TODO: Implement setOwner
}

bool SafeHouse::isOwner(IsoPlayer var1) {
    // TODO: Implement isOwner
    return false;
}

long SafeHouse::getLastVisited() {
    // TODO: Implement getLastVisited
    return 0;
}

void SafeHouse::setLastVisited(long var1) {
    // TODO: Implement setLastVisited
}

std::string SafeHouse::getTitle() {
    // TODO: Implement getTitle
    return "";
}

void SafeHouse::setTitle(const std::string& var1) {
    // TODO: Implement setTitle
}

int SafeHouse::getPlayerConnected() {
    // TODO: Implement getPlayerConnected
    return 0;
}

void SafeHouse::setPlayerConnected(int var1) {
    // TODO: Implement setPlayerConnected
}

int SafeHouse::getOpenTimer() {
    // TODO: Implement getOpenTimer
    return 0;
}

void SafeHouse::setOpenTimer(int var1) {
    // TODO: Implement setOpenTimer
}

void SafeHouse::setRespawnInSafehouse(bool var1, const std::string& var2) {
    // TODO: Implement setRespawnInSafehouse
}

bool SafeHouse::isRespawnInSafehouse(const std::string& var1) {
    // TODO: Implement isRespawnInSafehouse
    return false;
}

bool SafeHouse::isPlayerAllowedOnSquare(IsoPlayer var0, IsoGridSquare var1) {
    // TODO: Implement isPlayerAllowedOnSquare
    return false;
}

} // namespace areas
} // namespace iso
} // namespace zombie
