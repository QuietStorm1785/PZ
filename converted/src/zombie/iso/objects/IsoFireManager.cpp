#include "zombie/iso/objects/IsoFireManager.h"

namespace zombie {
namespace iso {
namespace objects {

void IsoFireManager::Add(IsoFire NewFire) {
 // TODO: Implement Add
}

void IsoFireManager::AddBurningCharacter(IsoGameCharacter BurningCharacter) {
 // TODO: Implement AddBurningCharacter
}

void IsoFireManager::Fire_LightCalc(IsoGridSquare FireSquare, IsoGridSquare TestSquare, int playerIndex) {
 // TODO: Implement Fire_LightCalc
}

void IsoFireManager::LightTileWithFire(IsoGridSquare TestSquare) {
 // TODO: Implement LightTileWithFire
}

void IsoFireManager::explode(IsoCell cell, IsoGridSquare gridSquare, int power) {
 // TODO: Implement explode
}

void IsoFireManager::MolotovSmash(IsoCell cell, IsoGridSquare gridSquare) {
 // TODO: Implement MolotovSmash
}

void IsoFireManager::Remove(IsoFire DyingFire) {
 // TODO: Implement Remove
}

void IsoFireManager::RemoveBurningCharacter(IsoGameCharacter BurningCharacter) {
 // TODO: Implement RemoveBurningCharacter
}

void IsoFireManager::StartFire(IsoCell cell, IsoGridSquare gridSquare, bool IgniteOnAny, int FireStartingEnergy, int Life) {
 // TODO: Implement StartFire
}

void IsoFireManager::StartSmoke(IsoCell cell, IsoGridSquare gridSquare, bool IgniteOnAny, int FireStartingEnergy, int Life) {
 // TODO: Implement StartSmoke
}

void IsoFireManager::StartFire(IsoCell cell, IsoGridSquare gridSquare, bool IgniteOnAny, int FireStartingEnergy) {
 // TODO: Implement StartFire
}

void IsoFireManager::addCharacterOnFire(IsoGameCharacter character) {
 // TODO: Implement addCharacterOnFire
}

void IsoFireManager::deleteCharacterOnFire(IsoGameCharacter character) {
 // TODO: Implement deleteCharacterOnFire
}

void IsoFireManager::Update() {
 // TODO: Implement Update
}

void IsoFireManager::updateSound(IsoFire fire) {
 // TODO: Implement updateSound
}

void IsoFireManager::stopSound(IsoFire fire) {
 // TODO: Implement stopSound
}

void IsoFireManager::RemoveAllOn(IsoGridSquare sq) {
 // TODO: Implement RemoveAllOn
}

void IsoFireManager::Reset() {
 // TODO: Implement Reset
}

int IsoFireManager::compare(IsoFire fire0, IsoFire fire1) {
 // TODO: Implement compare
 return 0;
}

void IsoFireManager::addFire(IsoFire fire) {
 // TODO: Implement addFire
}

void IsoFireManager::removeFire(IsoFire fire) {
 // TODO: Implement removeFire
}

void IsoFireManager::update() {
 // TODO: Implement update
}

float IsoFireManager::getClosestListener(float float5, float float6, float float7) {
 // TODO: Implement getClosestListener
 return 0;
}

bool IsoFireManager::shouldPlay(IsoFire fire) {
 // TODO: Implement shouldPlay
 return false;
}

int IsoFireManager::getExistingSlot(IsoFire fire) {
 // TODO: Implement getExistingSlot
 return 0;
}

int IsoFireManager::getFreeSlot() {
 // TODO: Implement getFreeSlot
 return 0;
}

void IsoFireManager::stopNotPlaying() {
 // TODO: Implement stopNotPlaying
}

void IsoFireManager::Reset() {
 // TODO: Implement Reset
}

void IsoFireManager::playSound(IsoFire firex) {
 // TODO: Implement playSound
}

void IsoFireManager::stopPlaying() {
 // TODO: Implement stopPlaying
}

} // namespace objects
} // namespace iso
} // namespace zombie
