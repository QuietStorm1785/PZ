#include "zombie/iso/areas/SafeHouse.h"

namespace zombie {
namespace iso {
namespace areas {

void SafeHouse::init() {
 // TODO: Implement init
}

SafeHouse SafeHouse::addSafeHouse(int _x, int _y, int _w, int _h,
 const std::string &player, bool remote) {
 // TODO: Implement addSafeHouse
 return nullptr;
}

SafeHouse SafeHouse::addSafeHouse(IsoGridSquare square, IsoPlayer player) {
 // TODO: Implement addSafeHouse
 return nullptr;
}

SafeHouse SafeHouse::hasSafehouse(const std::string &username) {
 // TODO: Implement hasSafehouse
 return nullptr;
}

SafeHouse SafeHouse::hasSafehouse(IsoPlayer player) {
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

SafeHouse SafeHouse::getSafeHouse(IsoGridSquare square) {
 // TODO: Implement getSafeHouse
 return nullptr;
}

return SafeHouse::isSafeHouse() {
 // TODO: Implement isSafeHouse
 return nullptr;
}

SafeHouse SafeHouse::getSafeHouse(int _x, int _y, int _w, int _h) {
 // TODO: Implement getSafeHouse
 return nullptr;
}

SafeHouse SafeHouse::isSafeHouse(IsoGridSquare square,
 const std::string &username,
 bool doDisableSafehouse) {
 // TODO: Implement isSafeHouse
 return nullptr;
}

void SafeHouse::clearSafehouseList() {
 // TODO: Implement clearSafehouseList
}

bool SafeHouse::playerAllowed(IsoPlayer player) {
 // TODO: Implement playerAllowed
 return false;
}

bool SafeHouse::playerAllowed(const std::string &name) {
 // TODO: Implement playerAllowed
 return false;
}

void SafeHouse::addPlayer(const std::string &player) {
 // TODO: Implement addPlayer
}

void SafeHouse::removePlayer(const std::string &player) {
 // TODO: Implement removePlayer
}

void SafeHouse::syncSafehouse() {
 // TODO: Implement syncSafehouse
}

void SafeHouse::removeSafeHouse(IsoPlayer player) {
 // TODO: Implement removeSafeHouse
}

void SafeHouse::removeSafeHouse(IsoPlayer player, bool force) {
 // TODO: Implement removeSafeHouse
}

void SafeHouse::save(ByteBuffer output) {
 // TODO: Implement save
}

SafeHouse SafeHouse::load(ByteBuffer bb, int WorldVersion) {
 // TODO: Implement load
 return nullptr;
}

std::string SafeHouse::canBeSafehouse(IsoGridSquare clickedSquare,
 IsoPlayer player) {
 // TODO: Implement canBeSafehouse
 return "";
}

void SafeHouse::kickOutOfSafehouse(IsoPlayer player) {
 // TODO: Implement kickOutOfSafehouse
}

void SafeHouse::checkTrespass(IsoPlayer player) {
 // TODO: Implement checkTrespass
}

SafeHouse SafeHouse::alreadyHaveSafehouse(const std::string &username) {
 // TODO: Implement alreadyHaveSafehouse
 return nullptr;
}

SafeHouse SafeHouse::alreadyHaveSafehouse(IsoPlayer player) {
 // TODO: Implement alreadyHaveSafehouse
 return nullptr;
}

bool SafeHouse::allowSafeHouse(IsoPlayer player) {
 // TODO: Implement allowSafeHouse
 return false;
}

void SafeHouse::updateSafehouse(IsoPlayer player) {
 // TODO: Implement updateSafehouse
}

public
SafeHouse::SafeHouse(int _x, int _y, int _w, int _h,
 const std::string &player) {
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

void SafeHouse::setX(int _x) {
 // TODO: Implement setX
}

int SafeHouse::getY() {
 // TODO: Implement getY
 return 0;
}

void SafeHouse::setY(int _y) {
 // TODO: Implement setY
}

int SafeHouse::getW() {
 // TODO: Implement getW
 return 0;
}

void SafeHouse::setW(int _w) {
 // TODO: Implement setW
}

int SafeHouse::getH() {
 // TODO: Implement getH
 return 0;
}

void SafeHouse::setH(int _h) {
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

bool SafeHouse::containsLocation(float _x, float _y) {
 // TODO: Implement containsLocation
 return false;
}

void SafeHouse::setPlayers(ArrayList<String> _players) {
 // TODO: Implement setPlayers
}

std::string SafeHouse::getOwner() {
 // TODO: Implement getOwner
 return "";
}

void SafeHouse::setOwner(const std::string &_owner) {
 // TODO: Implement setOwner
}

bool SafeHouse::isOwner(IsoPlayer player) {
 // TODO: Implement isOwner
 return false;
}

long SafeHouse::getLastVisited() {
 // TODO: Implement getLastVisited
 return 0;
}

void SafeHouse::setLastVisited(long _lastVisited) {
 // TODO: Implement setLastVisited
}

std::string SafeHouse::getTitle() {
 // TODO: Implement getTitle
 return "";
}

void SafeHouse::setTitle(const std::string &_title) {
 // TODO: Implement setTitle
}

int SafeHouse::getPlayerConnected() {
 // TODO: Implement getPlayerConnected
 return 0;
}

void SafeHouse::setPlayerConnected(int _playerConnected) {
 // TODO: Implement setPlayerConnected
}

int SafeHouse::getOpenTimer() {
 // TODO: Implement getOpenTimer
 return 0;
}

void SafeHouse::setOpenTimer(int _openTimer) {
 // TODO: Implement setOpenTimer
}

void SafeHouse::setRespawnInSafehouse(bool b, const std::string &username) {
 // TODO: Implement setRespawnInSafehouse
}

bool SafeHouse::isRespawnInSafehouse(const std::string &username) {
 // TODO: Implement isRespawnInSafehouse
 return false;
}

bool SafeHouse::isPlayerAllowedOnSquare(IsoPlayer player, IsoGridSquare sq) {
 // TODO: Implement isPlayerAllowedOnSquare
 return false;
}

} // namespace areas
} // namespace iso
} // namespace zombie
