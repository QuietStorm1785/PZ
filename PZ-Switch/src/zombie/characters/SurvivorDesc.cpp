#include "zombie/characters/SurvivorDesc.h"

namespace zombie {
namespace characters {

HumanVisual SurvivorDesc::getHumanVisual() {
 // TODO: Implement getHumanVisual
 return nullptr;
}

void SurvivorDesc::getItemVisuals(ItemVisuals itemVisuals) {
 // TODO: Implement getItemVisuals
}

bool SurvivorDesc::isFemale() {
 // TODO: Implement isFemale
 return false;
}

bool SurvivorDesc::isZombie() {
 // TODO: Implement isZombie
 return false;
}

bool SurvivorDesc::isSkeleton() {
 // TODO: Implement isSkeleton
 return false;
}

WornItems SurvivorDesc::getWornItems() {
 // TODO: Implement getWornItems
 return nullptr;
}

void SurvivorDesc::setWornItem(const std::string &bodyLocation,
 InventoryItem item) {
 // TODO: Implement setWornItem
}

InventoryItem SurvivorDesc::getWornItem(const std::string &bodyLocation) {
 // TODO: Implement getWornItem
 return nullptr;
}

void SurvivorDesc::dressInNamedOutfit(const std::string &outfitName) {
 // TODO: Implement dressInNamedOutfit
}

SurvivorGroup SurvivorDesc::getGroup() {
 // TODO: Implement getGroup
 return nullptr;
}

bool SurvivorDesc::isLeader() {
 // TODO: Implement isLeader
 return false;
}

int SurvivorDesc::getIDCount() {
 // TODO: Implement getIDCount
 return 0;
}

void SurvivorDesc::setProfessionSkills(
 ProfessionFactory.Profession profession) {
 // TODO: Implement setProfessionSkills
}

KahluaTable SurvivorDesc::getMeta() {
 // TODO: Implement getMeta
 return nullptr;
}

int SurvivorDesc::getCalculatedToughness() {
 // TODO: Implement getCalculatedToughness
 return 0;
}

void SurvivorDesc::setIDCount(int aIDCount) {
 // TODO: Implement setIDCount
}

bool SurvivorDesc::isDead() {
 // TODO: Implement isDead
 return false;
}

public
SurvivorDesc::SurvivorDesc() {
 // TODO: Implement SurvivorDesc
 return nullptr;
}

public
SurvivorDesc::SurvivorDesc(bool bNew) {
 // TODO: Implement SurvivorDesc
 return nullptr;
}

public
SurvivorDesc::SurvivorDesc(SurvivorDesc other) {
 // TODO: Implement SurvivorDesc
 return nullptr;
}

void SurvivorDesc::meet(SurvivorDesc desc) {
 // TODO: Implement meet
}

bool SurvivorDesc::hasObservation(const std::string &o) {
 // TODO: Implement hasObservation
 return false;
}

void SurvivorDesc::savePerk(ByteBuffer byteBuffer, PerkFactory.Perk perk) {
 // TODO: Implement savePerk
}

void SurvivorDesc::load(ByteBuffer input, int WorldVersion,
 IsoGameCharacter chr) {
 // TODO: Implement load
}

void SurvivorDesc::save(ByteBuffer output) {
 // TODO: Implement save
}

void SurvivorDesc::loadCompact(ByteBuffer input) {
 // TODO: Implement loadCompact
}

void SurvivorDesc::saveCompact(ByteBuffer output) {
 // TODO: Implement saveCompact
}

void SurvivorDesc::addObservation(const std::string &obv) {
 // TODO: Implement addObservation
}

void SurvivorDesc::doStats() {
 // TODO: Implement doStats
}

int SurvivorDesc::getMetCount(SurvivorDesc descriptor) {
 // TODO: Implement getMetCount
 return 0;
}

std::string SurvivorDesc::getForename() {
 // TODO: Implement getForename
 return "";
}

void SurvivorDesc::setForename(const std::string &_forename) {
 // TODO: Implement setForename
}

int SurvivorDesc::getID() {
 // TODO: Implement getID
 return 0;
}

void SurvivorDesc::setID(int _ID) {
 // TODO: Implement setID
}

IsoGameCharacter SurvivorDesc::getInstance() {
 // TODO: Implement getInstance
 return nullptr;
}

void SurvivorDesc::setInstance(IsoGameCharacter _Instance) {
 // TODO: Implement setInstance
}

std::string SurvivorDesc::getSurname() {
 // TODO: Implement getSurname
 return "";
}

void SurvivorDesc::setSurname(const std::string &_surname) {
 // TODO: Implement setSurname
}

std::string SurvivorDesc::getInventoryScript() {
 // TODO: Implement getInventoryScript
 return "";
}

void SurvivorDesc::setInventoryScript(const std::string &_InventoryScript) {
 // TODO: Implement setInventoryScript
}

std::string SurvivorDesc::getTorso() {
 // TODO: Implement getTorso
 return "";
}

void SurvivorDesc::setTorso(const std::string &_torso) {
 // TODO: Implement setTorso
}

float SurvivorDesc::getBravery() {
 // TODO: Implement getBravery
 return 0;
}

void SurvivorDesc::setBravery(float _bravery) {
 // TODO: Implement setBravery
}

float SurvivorDesc::getLoner() {
 // TODO: Implement getLoner
 return 0;
}

void SurvivorDesc::setLoner(float _loner) {
 // TODO: Implement setLoner
}

float SurvivorDesc::getAggressiveness() {
 // TODO: Implement getAggressiveness
 return 0;
}

void SurvivorDesc::setAggressiveness(float _aggressiveness) {
 // TODO: Implement setAggressiveness
}

float SurvivorDesc::getCompassion() {
 // TODO: Implement getCompassion
 return 0;
}

void SurvivorDesc::setCompassion(float _compassion) {
 // TODO: Implement setCompassion
}

float SurvivorDesc::getTemper() {
 // TODO: Implement getTemper
 return 0;
}

void SurvivorDesc::setTemper(float _temper) {
 // TODO: Implement setTemper
}

float SurvivorDesc::getFriendliness() {
 // TODO: Implement getFriendliness
 return 0;
}

void SurvivorDesc::setFriendliness(float _friendliness) {
 // TODO: Implement setFriendliness
}

float SurvivorDesc::getFavourindoors() {
 // TODO: Implement getFavourindoors
 return 0;
}

void SurvivorDesc::setFavourindoors(float _favourindoors) {
 // TODO: Implement setFavourindoors
}

float SurvivorDesc::getLoyalty() {
 // TODO: Implement getLoyalty
 return 0;
}

void SurvivorDesc::setLoyalty(float _loyalty) {
 // TODO: Implement setLoyalty
}

std::string SurvivorDesc::getProfession() {
 // TODO: Implement getProfession
 return "";
}

void SurvivorDesc::setProfession(const std::string &_Profession) {
 // TODO: Implement setProfession
}

bool SurvivorDesc::isAggressive() {
 // TODO: Implement isAggressive
 return false;
}

bool SurvivorDesc::isFriendly() {
 // TODO: Implement isFriendly
 return false;
}

void SurvivorDesc::setType(SurvivorFactory.SurvivorType _type) {
 // TODO: Implement setType
}

void SurvivorDesc::setFemale(bool _bFemale) {
 // TODO: Implement setFemale
}

void SurvivorDesc::addTrouserColor(ColorInfo color) {
 // TODO: Implement addTrouserColor
}

void SurvivorDesc::addHairColor(ColorInfo color) {
 // TODO: Implement addHairColor
}

Color SurvivorDesc::getRandomSkinColor() {
 // TODO: Implement getRandomSkinColor
 return nullptr;
}

} // namespace characters
} // namespace zombie
