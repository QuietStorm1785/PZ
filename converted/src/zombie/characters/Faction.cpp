#include "zombie/characters/Faction.h"

namespace zombie {
namespace characters {

public
Faction::Faction() {
  // TODO: Implement Faction
  return nullptr;
}

public
Faction::Faction(const std::string &_name, const std::string &_owner) {
  // TODO: Implement Faction
  return nullptr;
}

Faction Faction::createFaction(const std::string &_name,
                               const std::string &_owner) {
  // TODO: Implement createFaction
  return nullptr;
}

bool Faction::canCreateFaction(IsoPlayer player) {
  // TODO: Implement canCreateFaction
  return false;
}

bool Faction::canCreateTag() {
  // TODO: Implement canCreateTag
  return false;
}

bool Faction::isAlreadyInFaction(const std::string &username) {
  // TODO: Implement isAlreadyInFaction
  return false;
}

bool Faction::isAlreadyInFaction(IsoPlayer player) {
  // TODO: Implement isAlreadyInFaction
  return false;
}

return Faction::isAlreadyInFaction() {
  // TODO: Implement isAlreadyInFaction
  return nullptr;
}

void Faction::removePlayer(const std::string &player) {
  // TODO: Implement removePlayer
}

bool Faction::factionExist(const std::string &_name) {
  // TODO: Implement factionExist
  return false;
}

bool Faction::tagExist(const std::string &_name) {
  // TODO: Implement tagExist
  return false;
}

Faction Faction::getPlayerFaction(IsoPlayer player) {
  // TODO: Implement getPlayerFaction
  return nullptr;
}

Faction Faction::getPlayerFaction(const std::string &username) {
  // TODO: Implement getPlayerFaction
  return nullptr;
}

Faction Faction::getFaction(const std::string &_name) {
  // TODO: Implement getFaction
  return nullptr;
}

void Faction::removeFaction() {
  // TODO: Implement removeFaction
}

void Faction::syncFaction() {
  // TODO: Implement syncFaction
}

bool Faction::isOwner(const std::string &_name) {
  // TODO: Implement isOwner
  return false;
}

bool Faction::isPlayerMember(IsoPlayer player) {
  // TODO: Implement isPlayerMember
  return false;
}

bool Faction::isMember(const std::string &_name) {
  // TODO: Implement isMember
  return false;
}

void Faction::writeToBuffer(ByteBufferWriter bb, bool remove) {
  // TODO: Implement writeToBuffer
}

void Faction::save(ByteBuffer output) {
  // TODO: Implement save
}

void Faction::load(ByteBuffer input, int WorldVersion) {
  // TODO: Implement load
}

void Faction::addPlayer(const std::string &pName) {
  // TODO: Implement addPlayer
}

ColorInfo Faction::getTagColor() {
  // TODO: Implement getTagColor
  return nullptr;
}

void Faction::setTagColor(ColorInfo _tagColor) {
  // TODO: Implement setTagColor
}

std::string Faction::getTag() {
  // TODO: Implement getTag
  return "";
}

void Faction::setTag(const std::string &_tag) {
  // TODO: Implement setTag
}

std::string Faction::getName() {
  // TODO: Implement getName
  return "";
}

void Faction::setName(const std::string &_name) {
  // TODO: Implement setName
}

std::string Faction::getOwner() {
  // TODO: Implement getOwner
  return "";
}

void Faction::setOwner(const std::string &_owner) {
  // TODO: Implement setOwner
}

} // namespace characters
} // namespace zombie
