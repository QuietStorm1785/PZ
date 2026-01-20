#include <string>
#include "zombie\characters/ILuaGameCharacterDamage.h"

namespace zombie {
namespace characters {

BodyDamage ILuaGameCharacterDamage::getBodyDamage() {
    // TODO: Implement getBodyDamage
    return nullptr;
}

BodyDamage ILuaGameCharacterDamage::getBodyDamageRemote() {
    // TODO: Implement getBodyDamageRemote
    return nullptr;
}

float ILuaGameCharacterDamage::getHealth() {
    // TODO: Implement getHealth
    return 0;
}

void ILuaGameCharacterDamage::setHealth(float var1) {
    // TODO: Implement setHealth
}

float ILuaGameCharacterDamage::Hit(BaseVehicle var1, float var2, bool var3, float var4, float var5) {
    // TODO: Implement Hit
    return 0;
}

float ILuaGameCharacterDamage::Hit(HandWeapon var1, IsoGameCharacter var2, float var3, bool var4, float var5) {
    // TODO: Implement Hit
    return 0;
}

float ILuaGameCharacterDamage::Hit(HandWeapon var1, IsoGameCharacter var2, float var3, bool var4, float var5, bool var6) {
    // TODO: Implement Hit
    return 0;
}

bool ILuaGameCharacterDamage::isOnFire() {
    // TODO: Implement isOnFire
    return false;
}

void ILuaGameCharacterDamage::StopBurning() {
    // TODO: Implement StopBurning
}

void ILuaGameCharacterDamage::sendStopBurning() {
    // TODO: Implement sendStopBurning
}

int ILuaGameCharacterDamage::getLastHitCount() {
    // TODO: Implement getLastHitCount
    return 0;
}

void ILuaGameCharacterDamage::setLastHitCount(int var1) {
    // TODO: Implement setLastHitCount
}

bool ILuaGameCharacterDamage::addHole(BloodBodyPartType var1) {
    // TODO: Implement addHole
    return false;
}

void ILuaGameCharacterDamage::addBlood(BloodBodyPartType var1, bool var2, bool var3, bool var4) {
    // TODO: Implement addBlood
}

bool ILuaGameCharacterDamage::isBumped() {
    // TODO: Implement isBumped
    return false;
}

std::string ILuaGameCharacterDamage::getBumpType() {
    // TODO: Implement getBumpType
    return "";
}

bool ILuaGameCharacterDamage::isOnDeathDone() {
    // TODO: Implement isOnDeathDone
    return false;
}

void ILuaGameCharacterDamage::setOnDeathDone(bool var1) {
    // TODO: Implement setOnDeathDone
}

bool ILuaGameCharacterDamage::isOnKillDone() {
    // TODO: Implement isOnKillDone
    return false;
}

void ILuaGameCharacterDamage::setOnKillDone(bool var1) {
    // TODO: Implement setOnKillDone
}

bool ILuaGameCharacterDamage::isDeathDragDown() {
    // TODO: Implement isDeathDragDown
    return false;
}

void ILuaGameCharacterDamage::setDeathDragDown(bool var1) {
    // TODO: Implement setDeathDragDown
}

bool ILuaGameCharacterDamage::isPlayingDeathSound() {
    // TODO: Implement isPlayingDeathSound
    return false;
}

void ILuaGameCharacterDamage::setPlayingDeathSound(bool var1) {
    // TODO: Implement setPlayingDeathSound
}

} // namespace characters
} // namespace zombie
