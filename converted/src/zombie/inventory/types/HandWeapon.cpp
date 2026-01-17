#include "zombie/inventory/types/HandWeapon.h"

namespace zombie {
namespace inventory {
namespace types {

float HandWeapon::getSplatSize() {
  // TODO: Implement getSplatSize
  return 0;
}

bool HandWeapon::CanStack(InventoryItem item) {
  // TODO: Implement CanStack
  return false;
}

std::string HandWeapon::getCategory() {
  // TODO: Implement getCategory
  return "";
}

public
HandWeapon::HandWeapon(const std::string &module, const std::string &name,
                       const std::string &itemType,
                       const std::string &texName) {
  // TODO: Implement HandWeapon
  return nullptr;
}

public
HandWeapon::HandWeapon(const std::string &module, const std::string &name,
                       const std::string &itemType, Item item) {
  // TODO: Implement HandWeapon
  return nullptr;
}

bool HandWeapon::IsWeapon() {
  // TODO: Implement IsWeapon
  return false;
}

int HandWeapon::getSaveType() {
  // TODO: Implement getSaveType
  return 0;
}

float HandWeapon::getScore(SurvivorDesc desc) {
  // TODO: Implement getScore
  return 0;
}

float HandWeapon::getActualWeight() {
  // TODO: Implement getActualWeight
  return 0;
}

float HandWeapon::getWeight() {
  // TODO: Implement getWeight
  return 0;
}

float HandWeapon::getContentsWeight() {
  // TODO: Implement getContentsWeight
  return 0;
}

void HandWeapon::DoTooltip(ObjectTooltip tooltipUI,
                           ObjectTooltip.Layout layout) {
  // TODO: Implement DoTooltip
}

float HandWeapon::getDamageMod(IsoGameCharacter chr) {
  // TODO: Implement getDamageMod
  return 0;
}

float HandWeapon::getRangeMod(IsoGameCharacter chr) {
  // TODO: Implement getRangeMod
  return 0;
}

float HandWeapon::getFatigueMod(IsoGameCharacter chr) {
  // TODO: Implement getFatigueMod
  return 0;
}

float HandWeapon::getKnockbackMod(IsoGameCharacter chr) {
  // TODO: Implement getKnockbackMod
  return 0;
}

float HandWeapon::getSpeedMod(IsoGameCharacter chr) {
  // TODO: Implement getSpeedMod
  return 0;
}

float HandWeapon::getToHitMod(IsoGameCharacter chr) {
  // TODO: Implement getToHitMod
  return 0;
}

bool HandWeapon::isAngleFalloff() {
  // TODO: Implement isAngleFalloff
  return false;
}

void HandWeapon::setAngleFalloff(bool _angleFalloff) {
  // TODO: Implement setAngleFalloff
}

bool HandWeapon::isCanBarracade() {
  // TODO: Implement isCanBarracade
  return false;
}

void HandWeapon::setCanBarracade(bool _bCanBarracade) {
  // TODO: Implement setCanBarracade
}

float HandWeapon::getDoSwingBeforeImpact() {
  // TODO: Implement getDoSwingBeforeImpact
  return 0;
}

void HandWeapon::setDoSwingBeforeImpact(float _doSwingBeforeImpact) {
  // TODO: Implement setDoSwingBeforeImpact
}

std::string HandWeapon::getImpactSound() {
  // TODO: Implement getImpactSound
  return "";
}

void HandWeapon::setImpactSound(const std::string &_impactSound) {
  // TODO: Implement setImpactSound
}

bool HandWeapon::isKnockBackOnNoDeath() {
  // TODO: Implement isKnockBackOnNoDeath
  return false;
}

void HandWeapon::setKnockBackOnNoDeath(bool _knockBackOnNoDeath) {
  // TODO: Implement setKnockBackOnNoDeath
}

float HandWeapon::getMaxAngle() {
  // TODO: Implement getMaxAngle
  return 0;
}

void HandWeapon::setMaxAngle(float _maxAngle) {
  // TODO: Implement setMaxAngle
}

float HandWeapon::getMaxDamage() {
  // TODO: Implement getMaxDamage
  return 0;
}

void HandWeapon::setMaxDamage(float _maxDamage) {
  // TODO: Implement setMaxDamage
}

int HandWeapon::getMaxHitCount() {
  // TODO: Implement getMaxHitCount
  return 0;
}

void HandWeapon::setMaxHitCount(int _maxHitCount) {
  // TODO: Implement setMaxHitCount
}

float HandWeapon::getMaxRange() {
  // TODO: Implement getMaxRange
  return 0;
}

float HandWeapon::getMaxRange(IsoGameCharacter owner) {
  // TODO: Implement getMaxRange
  return 0;
}

void HandWeapon::setMaxRange(float _maxRange) {
  // TODO: Implement setMaxRange
}

bool HandWeapon::isRanged() {
  // TODO: Implement isRanged
  return false;
}

void HandWeapon::setRanged(bool _ranged) {
  // TODO: Implement setRanged
}

float HandWeapon::getMinAngle() {
  // TODO: Implement getMinAngle
  return 0;
}

void HandWeapon::setMinAngle(float _minAngle) {
  // TODO: Implement setMinAngle
}

float HandWeapon::getMinDamage() {
  // TODO: Implement getMinDamage
  return 0;
}

void HandWeapon::setMinDamage(float _minDamage) {
  // TODO: Implement setMinDamage
}

float HandWeapon::getMinimumSwingTime() {
  // TODO: Implement getMinimumSwingTime
  return 0;
}

void HandWeapon::setMinimumSwingTime(float _minimumSwingTime) {
  // TODO: Implement setMinimumSwingTime
}

float HandWeapon::getMinRange() {
  // TODO: Implement getMinRange
  return 0;
}

void HandWeapon::setMinRange(float _minRange) {
  // TODO: Implement setMinRange
}

float HandWeapon::getNoiseFactor() {
  // TODO: Implement getNoiseFactor
  return 0;
}

void HandWeapon::setNoiseFactor(float _noiseFactor) {
  // TODO: Implement setNoiseFactor
}

std::string HandWeapon::getOtherHandRequire() {
  // TODO: Implement getOtherHandRequire
  return "";
}

void HandWeapon::setOtherHandRequire(const std::string &_otherHandRequire) {
  // TODO: Implement setOtherHandRequire
}

bool HandWeapon::isOtherHandUse() {
  // TODO: Implement isOtherHandUse
  return false;
}

void HandWeapon::setOtherHandUse(bool _otherHandUse) {
  // TODO: Implement setOtherHandUse
}

std::string HandWeapon::getPhysicsObject() {
  // TODO: Implement getPhysicsObject
  return "";
}

void HandWeapon::setPhysicsObject(const std::string &_physicsObject) {
  // TODO: Implement setPhysicsObject
}

float HandWeapon::getPushBackMod() {
  // TODO: Implement getPushBackMod
  return 0;
}

void HandWeapon::setPushBackMod(float _pushBackMod) {
  // TODO: Implement setPushBackMod
}

bool HandWeapon::isRangeFalloff() {
  // TODO: Implement isRangeFalloff
  return false;
}

void HandWeapon::setRangeFalloff(bool _rangeFalloff) {
  // TODO: Implement setRangeFalloff
}

bool HandWeapon::isShareDamage() {
  // TODO: Implement isShareDamage
  return false;
}

void HandWeapon::setShareDamage(bool _shareDamage) {
  // TODO: Implement setShareDamage
}

int HandWeapon::getSoundRadius() {
  // TODO: Implement getSoundRadius
  return 0;
}

void HandWeapon::setSoundRadius(int _soundRadius) {
  // TODO: Implement setSoundRadius
}

int HandWeapon::getSoundVolume() {
  // TODO: Implement getSoundVolume
  return 0;
}

void HandWeapon::setSoundVolume(int _soundVolume) {
  // TODO: Implement setSoundVolume
}

bool HandWeapon::isSplatBloodOnNoDeath() {
  // TODO: Implement isSplatBloodOnNoDeath
  return false;
}

void HandWeapon::setSplatBloodOnNoDeath(bool _splatBloodOnNoDeath) {
  // TODO: Implement setSplatBloodOnNoDeath
}

int HandWeapon::getSplatNumber() {
  // TODO: Implement getSplatNumber
  return 0;
}

void HandWeapon::setSplatNumber(int _splatNumber) {
  // TODO: Implement setSplatNumber
}

std::string HandWeapon::getSwingSound() {
  // TODO: Implement getSwingSound
  return "";
}

void HandWeapon::setSwingSound(const std::string &_swingSound) {
  // TODO: Implement setSwingSound
}

float HandWeapon::getSwingTime() {
  // TODO: Implement getSwingTime
  return 0;
}

void HandWeapon::setSwingTime(float _swingTime) {
  // TODO: Implement setSwingTime
}

float HandWeapon::getToHitModifier() {
  // TODO: Implement getToHitModifier
  return 0;
}

void HandWeapon::setToHitModifier(float _toHitModifier) {
  // TODO: Implement setToHitModifier
}

bool HandWeapon::isUseEndurance() {
  // TODO: Implement isUseEndurance
  return false;
}

void HandWeapon::setUseEndurance(bool _useEndurance) {
  // TODO: Implement setUseEndurance
}

bool HandWeapon::isUseSelf() {
  // TODO: Implement isUseSelf
  return false;
}

void HandWeapon::setUseSelf(bool _useSelf) {
  // TODO: Implement setUseSelf
}

std::string HandWeapon::getWeaponSprite() {
  // TODO: Implement getWeaponSprite
  return "";
}

void HandWeapon::setWeaponSprite(const std::string &_weaponSprite) {
  // TODO: Implement setWeaponSprite
}

float HandWeapon::getOtherBoost() {
  // TODO: Implement getOtherBoost
  return 0;
}

void HandWeapon::setOtherBoost(float _otherBoost) {
  // TODO: Implement setOtherBoost
}

int HandWeapon::getDoorDamage() {
  // TODO: Implement getDoorDamage
  return 0;
}

void HandWeapon::setDoorDamage(int _DoorDamage) {
  // TODO: Implement setDoorDamage
}

std::string HandWeapon::getDoorHitSound() {
  // TODO: Implement getDoorHitSound
  return "";
}

void HandWeapon::setDoorHitSound(const std::string &_doorHitSound) {
  // TODO: Implement setDoorHitSound
}

int HandWeapon::getConditionLowerChance() {
  // TODO: Implement getConditionLowerChance
  return 0;
}

void HandWeapon::setConditionLowerChance(int _ConditionLowerChance) {
  // TODO: Implement setConditionLowerChance
}

bool HandWeapon::isMultipleHitConditionAffected() {
  // TODO: Implement isMultipleHitConditionAffected
  return false;
}

void HandWeapon::setMultipleHitConditionAffected(
    bool _MultipleHitConditionAffected) {
  // TODO: Implement setMultipleHitConditionAffected
}

bool HandWeapon::isShareEndurance() {
  // TODO: Implement isShareEndurance
  return false;
}

void HandWeapon::setShareEndurance(bool _shareEndurance) {
  // TODO: Implement setShareEndurance
}

bool HandWeapon::isAlwaysKnockdown() {
  // TODO: Implement isAlwaysKnockdown
  return false;
}

void HandWeapon::setAlwaysKnockdown(bool _AlwaysKnockdown) {
  // TODO: Implement setAlwaysKnockdown
}

float HandWeapon::getEnduranceMod() {
  // TODO: Implement getEnduranceMod
  return 0;
}

void HandWeapon::setEnduranceMod(float _EnduranceMod) {
  // TODO: Implement setEnduranceMod
}

float HandWeapon::getKnockdownMod() {
  // TODO: Implement getKnockdownMod
  return 0;
}

void HandWeapon::setKnockdownMod(float _KnockdownMod) {
  // TODO: Implement setKnockdownMod
}

bool HandWeapon::isCantAttackWithLowestEndurance() {
  // TODO: Implement isCantAttackWithLowestEndurance
  return false;
}

void HandWeapon::setCantAttackWithLowestEndurance(
    bool _CantAttackWithLowestEndurance) {
  // TODO: Implement setCantAttackWithLowestEndurance
}

bool HandWeapon::isAimedFirearm() {
  // TODO: Implement isAimedFirearm
  return false;
}

bool HandWeapon::isAimedHandWeapon() {
  // TODO: Implement isAimedHandWeapon
  return false;
}

int HandWeapon::getProjectileCount() {
  // TODO: Implement getProjectileCount
  return 0;
}

void HandWeapon::setProjectileCount(int count) {
  // TODO: Implement setProjectileCount
}

float HandWeapon::getAimingMod() {
  // TODO: Implement getAimingMod
  return 0;
}

bool HandWeapon::isAimed() {
  // TODO: Implement isAimed
  return false;
}

void HandWeapon::setCriticalChance(float criticalChance) {
  // TODO: Implement setCriticalChance
}

float HandWeapon::getCriticalChance() {
  // TODO: Implement getCriticalChance
  return 0;
}

void HandWeapon::setSubCategory(const std::string &subcategory) {
  // TODO: Implement setSubCategory
}

std::string HandWeapon::getSubCategory() {
  // TODO: Implement getSubCategory
  return "";
}

void HandWeapon::setZombieHitSound(const std::string &_hitSound) {
  // TODO: Implement setZombieHitSound
}

std::string HandWeapon::getZombieHitSound() {
  // TODO: Implement getZombieHitSound
  return "";
}

void HandWeapon::setCategories(ArrayList<String> categories) {
  // TODO: Implement setCategories
}

int HandWeapon::getAimingPerkCritModifier() {
  // TODO: Implement getAimingPerkCritModifier
  return 0;
}

void HandWeapon::setAimingPerkCritModifier(int aimingPerkCritModifier) {
  // TODO: Implement setAimingPerkCritModifier
}

float HandWeapon::getAimingPerkRangeModifier() {
  // TODO: Implement getAimingPerkRangeModifier
  return 0;
}

void HandWeapon::setAimingPerkRangeModifier(float aimingPerkRangeModifier) {
  // TODO: Implement setAimingPerkRangeModifier
}

int HandWeapon::getHitChance() {
  // TODO: Implement getHitChance
  return 0;
}

void HandWeapon::setHitChance(int hitChance) {
  // TODO: Implement setHitChance
}

float HandWeapon::getAimingPerkHitChanceModifier() {
  // TODO: Implement getAimingPerkHitChanceModifier
  return 0;
}

void HandWeapon::setAimingPerkHitChanceModifier(
    float aimingPerkHitChanceModifier) {
  // TODO: Implement setAimingPerkHitChanceModifier
}

float HandWeapon::getAimingPerkMinAngleModifier() {
  // TODO: Implement getAimingPerkMinAngleModifier
  return 0;
}

void HandWeapon::setAimingPerkMinAngleModifier(
    float aimingPerkMinAngleModifier) {
  // TODO: Implement setAimingPerkMinAngleModifier
}

int HandWeapon::getRecoilDelay() {
  // TODO: Implement getRecoilDelay
  return 0;
}

void HandWeapon::setRecoilDelay(int recoilDelay) {
  // TODO: Implement setRecoilDelay
}

bool HandWeapon::isPiercingBullets() {
  // TODO: Implement isPiercingBullets
  return false;
}

void HandWeapon::setPiercingBullets(bool piercingBullets) {
  // TODO: Implement setPiercingBullets
}

float HandWeapon::getSoundGain() {
  // TODO: Implement getSoundGain
  return 0;
}

void HandWeapon::setSoundGain(float _soundGain) {
  // TODO: Implement setSoundGain
}

WeaponPart HandWeapon::getScope() {
  // TODO: Implement getScope
  return nullptr;
}

void HandWeapon::setScope(WeaponPart _scope) {
  // TODO: Implement setScope
}

WeaponPart HandWeapon::getClip() {
  // TODO: Implement getClip
  return nullptr;
}

void HandWeapon::setClip(WeaponPart _clip) {
  // TODO: Implement setClip
}

WeaponPart HandWeapon::getCanon() {
  // TODO: Implement getCanon
  return nullptr;
}

void HandWeapon::setCanon(WeaponPart _canon) {
  // TODO: Implement setCanon
}

WeaponPart HandWeapon::getRecoilpad() {
  // TODO: Implement getRecoilpad
  return nullptr;
}

void HandWeapon::setRecoilpad(WeaponPart _recoilpad) {
  // TODO: Implement setRecoilpad
}

int HandWeapon::getClipSize() {
  // TODO: Implement getClipSize
  return 0;
}

void HandWeapon::setClipSize(int capacity) {
  // TODO: Implement setClipSize
}

void HandWeapon::save(ByteBuffer output, bool net) {
  // TODO: Implement save
}

void HandWeapon::load(ByteBuffer input, int WorldVersion) {
  // TODO: Implement load
}

float HandWeapon::getMinRangeRanged() {
  // TODO: Implement getMinRangeRanged
  return 0;
}

void HandWeapon::setMinRangeRanged(float _minRangeRanged) {
  // TODO: Implement setMinRangeRanged
}

int HandWeapon::getReloadTime() {
  // TODO: Implement getReloadTime
  return 0;
}

void HandWeapon::setReloadTime(int _reloadTime) {
  // TODO: Implement setReloadTime
}

WeaponPart HandWeapon::getSling() {
  // TODO: Implement getSling
  return nullptr;
}

void HandWeapon::setSling(WeaponPart _sling) {
  // TODO: Implement setSling
}

int HandWeapon::getAimingTime() {
  // TODO: Implement getAimingTime
  return 0;
}

void HandWeapon::setAimingTime(int _aimingTime) {
  // TODO: Implement setAimingTime
}

WeaponPart HandWeapon::getStock() {
  // TODO: Implement getStock
  return nullptr;
}

void HandWeapon::setStock(WeaponPart _stock) {
  // TODO: Implement setStock
}

int HandWeapon::getTreeDamage() {
  // TODO: Implement getTreeDamage
  return 0;
}

void HandWeapon::setTreeDamage(int _treeDamage) {
  // TODO: Implement setTreeDamage
}

std::string HandWeapon::getBulletOutSound() {
  // TODO: Implement getBulletOutSound
  return "";
}

void HandWeapon::setBulletOutSound(const std::string &_bulletOutSound) {
  // TODO: Implement setBulletOutSound
}

std::string HandWeapon::getShellFallSound() {
  // TODO: Implement getShellFallSound
  return "";
}

void HandWeapon::setShellFallSound(const std::string &_shellFallSound) {
  // TODO: Implement setShellFallSound
}

void HandWeapon::addPartToList(const std::string &string,
                               ArrayList<WeaponPart> arrayList) {
  // TODO: Implement addPartToList
}

void HandWeapon::setWeaponPart(const std::string &type, WeaponPart part) {
  // TODO: Implement setWeaponPart
}

WeaponPart HandWeapon::getWeaponPart(const std::string &type) {
  // TODO: Implement getWeaponPart
  return nullptr;
}

float HandWeapon::getWeaponPartWeightModifier(const std::string &type) {
  // TODO: Implement getWeaponPartWeightModifier
  return 0;
}

float HandWeapon::getWeaponPartWeightModifier(WeaponPart part) {
  // TODO: Implement getWeaponPartWeightModifier
  return 0;
}

void HandWeapon::attachWeaponPart(WeaponPart part) {
  // TODO: Implement attachWeaponPart
}

void HandWeapon::attachWeaponPart(WeaponPart part, bool doChange) {
  // TODO: Implement attachWeaponPart
}

void HandWeapon::detachWeaponPart(WeaponPart part) {
  // TODO: Implement detachWeaponPart
}

int HandWeapon::getTriggerExplosionTimer() {
  // TODO: Implement getTriggerExplosionTimer
  return 0;
}

void HandWeapon::setTriggerExplosionTimer(int _triggerExplosionTimer) {
  // TODO: Implement setTriggerExplosionTimer
}

bool HandWeapon::canBePlaced() {
  // TODO: Implement canBePlaced
  return false;
}

void HandWeapon::setCanBePlaced(bool _canBePlaced) {
  // TODO: Implement setCanBePlaced
}

int HandWeapon::getExplosionRange() {
  // TODO: Implement getExplosionRange
  return 0;
}

void HandWeapon::setExplosionRange(int _explosionRange) {
  // TODO: Implement setExplosionRange
}

int HandWeapon::getExplosionPower() {
  // TODO: Implement getExplosionPower
  return 0;
}

void HandWeapon::setExplosionPower(int _explosionPower) {
  // TODO: Implement setExplosionPower
}

int HandWeapon::getFireRange() {
  // TODO: Implement getFireRange
  return 0;
}

void HandWeapon::setFireRange(int _fireRange) {
  // TODO: Implement setFireRange
}

int HandWeapon::getSmokeRange() {
  // TODO: Implement getSmokeRange
  return 0;
}

void HandWeapon::setSmokeRange(int _smokeRange) {
  // TODO: Implement setSmokeRange
}

int HandWeapon::getFirePower() {
  // TODO: Implement getFirePower
  return 0;
}

void HandWeapon::setFirePower(int _firePower) {
  // TODO: Implement setFirePower
}

int HandWeapon::getNoiseRange() {
  // TODO: Implement getNoiseRange
  return 0;
}

void HandWeapon::setNoiseRange(int _noiseRange) {
  // TODO: Implement setNoiseRange
}

int HandWeapon::getNoiseDuration() {
  // TODO: Implement getNoiseDuration
  return 0;
}

float HandWeapon::getExtraDamage() {
  // TODO: Implement getExtraDamage
  return 0;
}

void HandWeapon::setExtraDamage(float _extraDamage) {
  // TODO: Implement setExtraDamage
}

int HandWeapon::getExplosionTimer() {
  // TODO: Implement getExplosionTimer
  return 0;
}

void HandWeapon::setExplosionTimer(int _explosionTimer) {
  // TODO: Implement setExplosionTimer
}

std::string HandWeapon::getPlacedSprite() {
  // TODO: Implement getPlacedSprite
  return "";
}

void HandWeapon::setPlacedSprite(const std::string &_placedSprite) {
  // TODO: Implement setPlacedSprite
}

bool HandWeapon::canBeReused() {
  // TODO: Implement canBeReused
  return false;
}

void HandWeapon::setCanBeReused(bool _canBeReused) {
  // TODO: Implement setCanBeReused
}

int HandWeapon::getSensorRange() {
  // TODO: Implement getSensorRange
  return 0;
}

void HandWeapon::setSensorRange(int _sensorRange) {
  // TODO: Implement setSensorRange
}

std::string HandWeapon::getRunAnim() {
  // TODO: Implement getRunAnim
  return "";
}

float HandWeapon::getCritDmgMultiplier() {
  // TODO: Implement getCritDmgMultiplier
  return 0;
}

void HandWeapon::setCritDmgMultiplier(float _critDmgMultiplier) {
  // TODO: Implement setCritDmgMultiplier
}

std::string HandWeapon::getStaticModel() {
  // TODO: Implement getStaticModel
  return "";
}

float HandWeapon::getBaseSpeed() {
  // TODO: Implement getBaseSpeed
  return 0;
}

void HandWeapon::setBaseSpeed(float _baseSpeed) {
  // TODO: Implement setBaseSpeed
}

float HandWeapon::getBloodLevel() {
  // TODO: Implement getBloodLevel
  return 0;
}

void HandWeapon::setBloodLevel(float level) {
  // TODO: Implement setBloodLevel
}

void HandWeapon::setWeaponLength(float weaponLength) {
  // TODO: Implement setWeaponLength
}

std::string HandWeapon::getAmmoBox() {
  // TODO: Implement getAmmoBox
  return "";
}

void HandWeapon::setAmmoBox(const std::string &_ammoBox) {
  // TODO: Implement setAmmoBox
}

std::string HandWeapon::getMagazineType() {
  // TODO: Implement getMagazineType
  return "";
}

void HandWeapon::setMagazineType(const std::string &_magazineType) {
  // TODO: Implement setMagazineType
}

std::string HandWeapon::getEjectAmmoStartSound() {
  // TODO: Implement getEjectAmmoStartSound
  return "";
}

std::string HandWeapon::getEjectAmmoSound() {
  // TODO: Implement getEjectAmmoSound
  return "";
}

std::string HandWeapon::getEjectAmmoStopSound() {
  // TODO: Implement getEjectAmmoStopSound
  return "";
}

std::string HandWeapon::getInsertAmmoStartSound() {
  // TODO: Implement getInsertAmmoStartSound
  return "";
}

std::string HandWeapon::getInsertAmmoSound() {
  // TODO: Implement getInsertAmmoSound
  return "";
}

std::string HandWeapon::getInsertAmmoStopSound() {
  // TODO: Implement getInsertAmmoStopSound
  return "";
}

std::string HandWeapon::getRackSound() {
  // TODO: Implement getRackSound
  return "";
}

void HandWeapon::setRackSound(const std::string &_rackSound) {
  // TODO: Implement setRackSound
}

bool HandWeapon::isReloadable(IsoGameCharacter owner) {
  // TODO: Implement isReloadable
  return false;
}

bool HandWeapon::isContainsClip() {
  // TODO: Implement isContainsClip
  return false;
}

void HandWeapon::setContainsClip(bool _containsClip) {
  // TODO: Implement setContainsClip
}

InventoryItem HandWeapon::getBestMagazine(IsoGameCharacter owner) {
  // TODO: Implement getBestMagazine
  return nullptr;
}

std::string HandWeapon::getWeaponReloadType() {
  // TODO: Implement getWeaponReloadType
  return "";
}

void HandWeapon::setWeaponReloadType(const std::string &_weaponReloadType) {
  // TODO: Implement setWeaponReloadType
}

bool HandWeapon::isRackAfterShoot() {
  // TODO: Implement isRackAfterShoot
  return false;
}

void HandWeapon::setRackAfterShoot(bool _rackAfterShoot) {
  // TODO: Implement setRackAfterShoot
}

bool HandWeapon::isRoundChambered() {
  // TODO: Implement isRoundChambered
  return false;
}

void HandWeapon::setRoundChambered(bool _roundChambered) {
  // TODO: Implement setRoundChambered
}

bool HandWeapon::isSpentRoundChambered() {
  // TODO: Implement isSpentRoundChambered
  return false;
}

void HandWeapon::setSpentRoundChambered(bool _roundChambered) {
  // TODO: Implement setSpentRoundChambered
}

int HandWeapon::getSpentRoundCount() {
  // TODO: Implement getSpentRoundCount
  return 0;
}

void HandWeapon::setSpentRoundCount(int count) {
  // TODO: Implement setSpentRoundCount
}

bool HandWeapon::isManuallyRemoveSpentRounds() {
  // TODO: Implement isManuallyRemoveSpentRounds
  return false;
}

int HandWeapon::getAmmoPerShoot() {
  // TODO: Implement getAmmoPerShoot
  return 0;
}

void HandWeapon::setAmmoPerShoot(int _ammoPerShoot) {
  // TODO: Implement setAmmoPerShoot
}

float HandWeapon::getJamGunChance() {
  // TODO: Implement getJamGunChance
  return 0;
}

void HandWeapon::setJamGunChance(float _jamGunChance) {
  // TODO: Implement setJamGunChance
}

bool HandWeapon::isJammed() {
  // TODO: Implement isJammed
  return false;
}

void HandWeapon::setJammed(bool _isJammed) {
  // TODO: Implement setJammed
}

std::string HandWeapon::getClickSound() {
  // TODO: Implement getClickSound
  return "";
}

void HandWeapon::setClickSound(const std::string &_clickSound) {
  // TODO: Implement setClickSound
}

void HandWeapon::setModelWeaponPart(
    ArrayList<ModelWeaponPart> _modelWeaponPart) {
  // TODO: Implement setModelWeaponPart
}

std::string HandWeapon::getOriginalWeaponSprite() {
  // TODO: Implement getOriginalWeaponSprite
  return "";
}

void HandWeapon::setOriginalWeaponSprite(
    const std::string &_originalWeaponSprite) {
  // TODO: Implement setOriginalWeaponSprite
}

bool HandWeapon::haveChamber() {
  // TODO: Implement haveChamber
  return false;
}

void HandWeapon::setHaveChamber(bool _haveChamber) {
  // TODO: Implement setHaveChamber
}

std::string HandWeapon::getDamageCategory() {
  // TODO: Implement getDamageCategory
  return "";
}

void HandWeapon::setDamageCategory(const std::string &_damageCategory) {
  // TODO: Implement setDamageCategory
}

bool HandWeapon::isDamageMakeHole() {
  // TODO: Implement isDamageMakeHole
  return false;
}

void HandWeapon::setDamageMakeHole(bool _damageMakeHole) {
  // TODO: Implement setDamageMakeHole
}

std::string HandWeapon::getHitFloorSound() {
  // TODO: Implement getHitFloorSound
  return "";
}

void HandWeapon::setHitFloorSound(const std::string &_hitFloorSound) {
  // TODO: Implement setHitFloorSound
}

bool HandWeapon::isInsertAllBulletsReload() {
  // TODO: Implement isInsertAllBulletsReload
  return false;
}

void HandWeapon::setInsertAllBulletsReload(bool _insertAllBulletsReload) {
  // TODO: Implement setInsertAllBulletsReload
}

std::string HandWeapon::getFireMode() {
  // TODO: Implement getFireMode
  return "";
}

void HandWeapon::setFireMode(const std::string &_fireMode) {
  // TODO: Implement setFireMode
}

void HandWeapon::setFireModePossibilities(
    ArrayList<String> _fireModePossibilities) {
  // TODO: Implement setFireModePossibilities
}

void HandWeapon::randomizeBullets() {
  // TODO: Implement randomizeBullets
}

float HandWeapon::getStopPower() {
  // TODO: Implement getStopPower
  return 0;
}

bool HandWeapon::isInstantExplosion() {
  // TODO: Implement isInstantExplosion
  return false;
}

} // namespace types
} // namespace inventory
} // namespace zombie
