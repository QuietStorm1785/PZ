#include "zombie/characters/BodyDamage/BodyPart.h"

namespace zombie {
namespace characters {
namespace BodyDamage {

public BodyPart::BodyPart(BodyPartType ChosenType, IsoGameCharacter PC) {
 // TODO: Implement BodyPart
 return nullptr;
}

void BodyPart::AddDamage(float Val) {
 // TODO: Implement AddDamage
}

bool BodyPart::isBandageDirty() {
 // TODO: Implement isBandageDirty
 return false;
}

void BodyPart::DamageUpdate() {
 // TODO: Implement DamageUpdate
}

float BodyPart::getHealth() {
 // TODO: Implement getHealth
 return 0;
}

void BodyPart::SetHealth(float NewHealth) {
 // TODO: Implement SetHealth
}

void BodyPart::AddHealth(float Val) {
 // TODO: Implement AddHealth
}

void BodyPart::ReduceHealth(float Val) {
 // TODO: Implement ReduceHealth
}

bool BodyPart::HasInjury() {
 // TODO: Implement HasInjury
 return false;
}

bool BodyPart::bandaged() {
 // TODO: Implement bandaged
 return false;
}

bool BodyPart::bitten() {
 // TODO: Implement bitten
 return false;
}

bool BodyPart::bleeding() {
 // TODO: Implement bleeding
 return false;
}

bool BodyPart::IsBleedingStemmed() {
 // TODO: Implement IsBleedingStemmed
 return false;
}

bool BodyPart::IsCortorised() {
 // TODO: Implement IsCortorised
 return false;
}

bool BodyPart::IsInfected() {
 // TODO: Implement IsInfected
 return false;
}

void BodyPart::SetInfected(bool inf) {
 // TODO: Implement SetInfected
}

void BodyPart::SetFakeInfected(bool inf) {
 // TODO: Implement SetFakeInfected
}

bool BodyPart::IsFakeInfected() {
 // TODO: Implement IsFakeInfected
 return false;
}

void BodyPart::DisableFakeInfection() {
 // TODO: Implement DisableFakeInfection
}

bool BodyPart::scratched() {
 // TODO: Implement scratched
 return false;
}

bool BodyPart::stitched() {
 // TODO: Implement stitched
 return false;
}

bool BodyPart::deepWounded() {
 // TODO: Implement deepWounded
 return false;
}

void BodyPart::RestoreToFullHealth() {
 // TODO: Implement RestoreToFullHealth
}

void BodyPart::setBandaged(bool Bandaged, float _bandageLife) {
 // TODO: Implement setBandaged
}

void BodyPart::setBandaged(bool Bandaged, float _bandageLife, bool isAlcoholic, const std::string& _bandageType) {
 // TODO: Implement setBandaged
}

void BodyPart::SetBitten(bool Bitten) {
 // TODO: Implement SetBitten
}

void BodyPart::SetBitten(bool Bitten, bool Infected) {
 // TODO: Implement SetBitten
}

void BodyPart::setBleeding(bool Bleeding) {
 // TODO: Implement setBleeding
}

void BodyPart::SetBleedingStemmed(bool BleedingStemmed) {
 // TODO: Implement SetBleedingStemmed
}

void BodyPart::SetCortorised(bool Cortorised) {
 // TODO: Implement SetCortorised
}

void BodyPart::setCut(bool _cut) {
 // TODO: Implement setCut
}

void BodyPart::setCut(bool _cut, bool forceNoInfection) {
 // TODO: Implement setCut
}

void BodyPart::generateZombieInfection(int baseChance) {
 // TODO: Implement generateZombieInfection
}

void BodyPart::setScratched(bool Scratched, bool forceNoInfection) {
 // TODO: Implement setScratched
}

void BodyPart::SetScratchedWeapon(bool Scratched) {
 // TODO: Implement SetScratchedWeapon
}

void BodyPart::generateDeepWound() {
 // TODO: Implement generateDeepWound
}

void BodyPart::generateDeepShardWound() {
 // TODO: Implement generateDeepShardWound
}

void BodyPart::SetScratchedWindow(bool Scratched) {
 // TODO: Implement SetScratchedWindow
}

void BodyPart::setStitched(bool Stitched) {
 // TODO: Implement setStitched
}

void BodyPart::damageFromFirearm(float damage) {
 // TODO: Implement damageFromFirearm
}

float BodyPart::getPain() {
 // TODO: Implement getPain
 return 0;
}

float BodyPart::getBiteTime() {
 // TODO: Implement getBiteTime
 return 0;
}

void BodyPart::setBiteTime(float _biteTime) {
 // TODO: Implement setBiteTime
}

float BodyPart::getDeepWoundTime() {
 // TODO: Implement getDeepWoundTime
 return 0;
}

void BodyPart::setDeepWoundTime(float _deepWoundTime) {
 // TODO: Implement setDeepWoundTime
}

bool BodyPart::haveGlass() {
 // TODO: Implement haveGlass
 return false;
}

void BodyPart::setHaveGlass(bool _haveGlass) {
 // TODO: Implement setHaveGlass
}

float BodyPart::getStitchTime() {
 // TODO: Implement getStitchTime
 return 0;
}

void BodyPart::setStitchTime(float _stitchTime) {
 // TODO: Implement setStitchTime
}

int BodyPart::getIndex() {
 // TODO: Implement getIndex
 return 0;
}

float BodyPart::getAlcoholLevel() {
 // TODO: Implement getAlcoholLevel
 return 0;
}

void BodyPart::setAlcoholLevel(float _alcoholLevel) {
 // TODO: Implement setAlcoholLevel
}

float BodyPart::getAdditionalPain(bool includeStiffness) {
 // TODO: Implement getAdditionalPain
 return 0;
}

float BodyPart::getAdditionalPain() {
 // TODO: Implement getAdditionalPain
 return 0;
}

void BodyPart::setAdditionalPain(float _additionalPain) {
 // TODO: Implement setAdditionalPain
}

std::string BodyPart::getBandageType() {
 // TODO: Implement getBandageType
 return "";
}

void BodyPart::setBandageType(const std::string& _bandageType) {
 // TODO: Implement setBandageType
}

bool BodyPart::isGetBandageXp() {
 // TODO: Implement isGetBandageXp
 return false;
}

void BodyPart::setGetBandageXp(bool _getBandageXp) {
 // TODO: Implement setGetBandageXp
}

bool BodyPart::isGetStitchXp() {
 // TODO: Implement isGetStitchXp
 return false;
}

void BodyPart::setGetStitchXp(bool _getStitchXp) {
 // TODO: Implement setGetStitchXp
}

float BodyPart::getSplintFactor() {
 // TODO: Implement getSplintFactor
 return 0;
}

void BodyPart::setSplintFactor(float _splintFactor) {
 // TODO: Implement setSplintFactor
}

float BodyPart::getFractureTime() {
 // TODO: Implement getFractureTime
 return 0;
}

void BodyPart::setFractureTime(float _fractureTime) {
 // TODO: Implement setFractureTime
}

bool BodyPart::isGetSplintXp() {
 // TODO: Implement isGetSplintXp
 return false;
}

void BodyPart::setGetSplintXp(bool _getSplintXp) {
 // TODO: Implement setGetSplintXp
}

bool BodyPart::isSplint() {
 // TODO: Implement isSplint
 return false;
}

void BodyPart::setSplint(bool _splint, float _splintFactor) {
 // TODO: Implement setSplint
}

bool BodyPart::haveBullet() {
 // TODO: Implement haveBullet
 return false;
}

void BodyPart::setHaveBullet(bool _haveBullet, int doctorLevel) {
 // TODO: Implement setHaveBullet
}

float BodyPart::getBurnTime() {
 // TODO: Implement getBurnTime
 return 0;
}

void BodyPart::setBurnTime(float _burnTime) {
 // TODO: Implement setBurnTime
}

bool BodyPart::isNeedBurnWash() {
 // TODO: Implement isNeedBurnWash
 return false;
}

void BodyPart::setNeedBurnWash(bool _needBurnWash) {
 // TODO: Implement setNeedBurnWash
}

float BodyPart::getLastTimeBurnWash() {
 // TODO: Implement getLastTimeBurnWash
 return 0;
}

void BodyPart::setLastTimeBurnWash(float _lastTimeBurnWash) {
 // TODO: Implement setLastTimeBurnWash
}

bool BodyPart::isInfectedWound() {
 // TODO: Implement isInfectedWound
 return false;
}

void BodyPart::setInfectedWound(bool _infectedWound) {
 // TODO: Implement setInfectedWound
}

BodyPartType BodyPart::getType() {
 // TODO: Implement getType
 return nullptr;
}

float BodyPart::getBleedingTime() {
 // TODO: Implement getBleedingTime
 return 0;
}

void BodyPart::setBleedingTime(float _bleedingTime) {
 // TODO: Implement setBleedingTime
}

bool BodyPart::isDeepWounded() {
 // TODO: Implement isDeepWounded
 return false;
}

void BodyPart::setDeepWounded(bool Wounded) {
 // TODO: Implement setDeepWounded
}

float BodyPart::getBandageLife() {
 // TODO: Implement getBandageLife
 return 0;
}

void BodyPart::setBandageLife(float _bandageLife) {
 // TODO: Implement setBandageLife
}

float BodyPart::getScratchTime() {
 // TODO: Implement getScratchTime
 return 0;
}

void BodyPart::setScratchTime(float _scratchTime) {
 // TODO: Implement setScratchTime
}

float BodyPart::getWoundInfectionLevel() {
 // TODO: Implement getWoundInfectionLevel
 return 0;
}

void BodyPart::setWoundInfectionLevel(float _infectedWound) {
 // TODO: Implement setWoundInfectionLevel
}

void BodyPart::setBurned() {
 // TODO: Implement setBurned
}

std::string BodyPart::getSplintItem() {
 // TODO: Implement getSplintItem
 return "";
}

void BodyPart::setSplintItem(const std::string& _splintItem) {
 // TODO: Implement setSplintItem
}

float BodyPart::getPlantainFactor() {
 // TODO: Implement getPlantainFactor
 return 0;
}

void BodyPart::setPlantainFactor(float _plantainFactor) {
 // TODO: Implement setPlantainFactor
}

float BodyPart::getGarlicFactor() {
 // TODO: Implement getGarlicFactor
 return 0;
}

void BodyPart::setGarlicFactor(float _garlicFactor) {
 // TODO: Implement setGarlicFactor
}

float BodyPart::getComfreyFactor() {
 // TODO: Implement getComfreyFactor
 return 0;
}

void BodyPart::setComfreyFactor(float _comfreyFactor) {
 // TODO: Implement setComfreyFactor
}

void BodyPart::sync(BodyPart other, BodyDamageSync.Updater updater) {
 // TODO: Implement sync
}

void BodyPart::sync(ByteBuffer bb, uint8_t id) {
 // TODO: Implement sync
}

float BodyPart::getCutTime() {
 // TODO: Implement getCutTime
 return 0;
}

void BodyPart::setCutTime(float _cutTime) {
 // TODO: Implement setCutTime
}

bool BodyPart::isCut() {
 // TODO: Implement isCut
 return false;
}

float BodyPart::getScratchSpeedModifier() {
 // TODO: Implement getScratchSpeedModifier
 return 0;
}

void BodyPart::setScratchSpeedModifier(float _scratchSpeedModifier) {
 // TODO: Implement setScratchSpeedModifier
}

float BodyPart::getCutSpeedModifier() {
 // TODO: Implement getCutSpeedModifier
 return 0;
}

void BodyPart::setCutSpeedModifier(float _cutSpeedModifier) {
 // TODO: Implement setCutSpeedModifier
}

float BodyPart::getBurnSpeedModifier() {
 // TODO: Implement getBurnSpeedModifier
 return 0;
}

void BodyPart::setBurnSpeedModifier(float _burnSpeedModifier) {
 // TODO: Implement setBurnSpeedModifier
}

float BodyPart::getDeepWoundSpeedModifier() {
 // TODO: Implement getDeepWoundSpeedModifier
 return 0;
}

void BodyPart::setDeepWoundSpeedModifier(float _deepWoundSpeedModifier) {
 // TODO: Implement setDeepWoundSpeedModifier
}

bool BodyPart::isBurnt() {
 // TODO: Implement isBurnt
 return false;
}

void BodyPart::generateBleeding() {
 // TODO: Implement generateBleeding
}

float BodyPart::getInnerTemperature() {
 // TODO: Implement getInnerTemperature
 return 0;
}

float BodyPart::getSkinTemperature() {
 // TODO: Implement getSkinTemperature
 return 0;
}

float BodyPart::getDistToCore() {
 // TODO: Implement getDistToCore
 return 0;
}

float BodyPart::getSkinSurface() {
 // TODO: Implement getSkinSurface
 return 0;
}

float BodyPart::getWetness() {
 // TODO: Implement getWetness
 return 0;
}

void BodyPart::setWetness(float _wetness) {
 // TODO: Implement setWetness
}

float BodyPart::getStiffness() {
 // TODO: Implement getStiffness
 return 0;
}

void BodyPart::setStiffness(float _stiffness) {
 // TODO: Implement setStiffness
}

} // namespace BodyDamage
} // namespace characters
} // namespace zombie
