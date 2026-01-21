#include <cstdint>
#include <string>
#include "zombie/characters/BodyDamage/BodyPart.h"

namespace zombie {
namespace characters {
namespace BodyDamage {

public BodyPart::BodyPart(BodyPartType var1, IsoGameCharacter var2) {
    // TODO: Implement BodyPart
    return nullptr;
}

void BodyPart::AddDamage(float var1) {
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

void BodyPart::SetHealth(float var1) {
    // TODO: Implement SetHealth
}

void BodyPart::AddHealth(float var1) {
    // TODO: Implement AddHealth
}

void BodyPart::ReduceHealth(float var1) {
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

void BodyPart::SetInfected(bool var1) {
    // TODO: Implement SetInfected
}

void BodyPart::SetFakeInfected(bool var1) {
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

void BodyPart::setBandaged(bool var1, float var2) {
    // TODO: Implement setBandaged
}

void BodyPart::setBandaged(bool var1, float var2, bool var3, const std::string& var4) {
    // TODO: Implement setBandaged
}

void BodyPart::SetBitten(bool var1) {
    // TODO: Implement SetBitten
}

void BodyPart::SetBitten(bool var1, bool var2) {
    // TODO: Implement SetBitten
}

void BodyPart::setBleeding(bool var1) {
    // TODO: Implement setBleeding
}

void BodyPart::SetBleedingStemmed(bool var1) {
    // TODO: Implement SetBleedingStemmed
}

void BodyPart::SetCortorised(bool var1) {
    // TODO: Implement SetCortorised
}

void BodyPart::setCut(bool var1) {
    // TODO: Implement setCut
}

void BodyPart::setCut(bool var1, bool var2) {
    // TODO: Implement setCut
}

void BodyPart::generateZombieInfection(int var1) {
    // TODO: Implement generateZombieInfection
}

void BodyPart::setScratched(bool var1, bool var2) {
    // TODO: Implement setScratched
}

void BodyPart::SetScratchedWeapon(bool var1) {
    // TODO: Implement SetScratchedWeapon
}

void BodyPart::generateDeepWound() {
    // TODO: Implement generateDeepWound
}

void BodyPart::generateDeepShardWound() {
    // TODO: Implement generateDeepShardWound
}

void BodyPart::SetScratchedWindow(bool var1) {
    // TODO: Implement SetScratchedWindow
}

void BodyPart::setStitched(bool var1) {
    // TODO: Implement setStitched
}

void BodyPart::damageFromFirearm(float var1) {
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

void BodyPart::setBiteTime(float var1) {
    // TODO: Implement setBiteTime
}

float BodyPart::getDeepWoundTime() {
    // TODO: Implement getDeepWoundTime
    return 0;
}

void BodyPart::setDeepWoundTime(float var1) {
    // TODO: Implement setDeepWoundTime
}

bool BodyPart::haveGlass() {
    // TODO: Implement haveGlass
    return false;
}

void BodyPart::setHaveGlass(bool var1) {
    // TODO: Implement setHaveGlass
}

float BodyPart::getStitchTime() {
    // TODO: Implement getStitchTime
    return 0;
}

void BodyPart::setStitchTime(float var1) {
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

void BodyPart::setAlcoholLevel(float var1) {
    // TODO: Implement setAlcoholLevel
}

float BodyPart::getAdditionalPain(bool var1) {
    // TODO: Implement getAdditionalPain
    return 0;
}

float BodyPart::getAdditionalPain() {
    // TODO: Implement getAdditionalPain
    return 0;
}

void BodyPart::setAdditionalPain(float var1) {
    // TODO: Implement setAdditionalPain
}

std::string BodyPart::getBandageType() {
    // TODO: Implement getBandageType
    return "";
}

void BodyPart::setBandageType(const std::string& var1) {
    // TODO: Implement setBandageType
}

bool BodyPart::isGetBandageXp() {
    // TODO: Implement isGetBandageXp
    return false;
}

void BodyPart::setGetBandageXp(bool var1) {
    // TODO: Implement setGetBandageXp
}

bool BodyPart::isGetStitchXp() {
    // TODO: Implement isGetStitchXp
    return false;
}

void BodyPart::setGetStitchXp(bool var1) {
    // TODO: Implement setGetStitchXp
}

float BodyPart::getSplintFactor() {
    // TODO: Implement getSplintFactor
    return 0;
}

void BodyPart::setSplintFactor(float var1) {
    // TODO: Implement setSplintFactor
}

float BodyPart::getFractureTime() {
    // TODO: Implement getFractureTime
    return 0;
}

void BodyPart::setFractureTime(float var1) {
    // TODO: Implement setFractureTime
}

bool BodyPart::isGetSplintXp() {
    // TODO: Implement isGetSplintXp
    return false;
}

void BodyPart::setGetSplintXp(bool var1) {
    // TODO: Implement setGetSplintXp
}

bool BodyPart::isSplint() {
    // TODO: Implement isSplint
    return false;
}

void BodyPart::setSplint(bool var1, float var2) {
    // TODO: Implement setSplint
}

bool BodyPart::haveBullet() {
    // TODO: Implement haveBullet
    return false;
}

void BodyPart::setHaveBullet(bool var1, int var2) {
    // TODO: Implement setHaveBullet
}

float BodyPart::getBurnTime() {
    // TODO: Implement getBurnTime
    return 0;
}

void BodyPart::setBurnTime(float var1) {
    // TODO: Implement setBurnTime
}

bool BodyPart::isNeedBurnWash() {
    // TODO: Implement isNeedBurnWash
    return false;
}

void BodyPart::setNeedBurnWash(bool var1) {
    // TODO: Implement setNeedBurnWash
}

float BodyPart::getLastTimeBurnWash() {
    // TODO: Implement getLastTimeBurnWash
    return 0;
}

void BodyPart::setLastTimeBurnWash(float var1) {
    // TODO: Implement setLastTimeBurnWash
}

bool BodyPart::isInfectedWound() {
    // TODO: Implement isInfectedWound
    return false;
}

void BodyPart::setInfectedWound(bool var1) {
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

void BodyPart::setBleedingTime(float var1) {
    // TODO: Implement setBleedingTime
}

bool BodyPart::isDeepWounded() {
    // TODO: Implement isDeepWounded
    return false;
}

void BodyPart::setDeepWounded(bool var1) {
    // TODO: Implement setDeepWounded
}

float BodyPart::getBandageLife() {
    // TODO: Implement getBandageLife
    return 0;
}

void BodyPart::setBandageLife(float var1) {
    // TODO: Implement setBandageLife
}

float BodyPart::getScratchTime() {
    // TODO: Implement getScratchTime
    return 0;
}

void BodyPart::setScratchTime(float var1) {
    // TODO: Implement setScratchTime
}

float BodyPart::getWoundInfectionLevel() {
    // TODO: Implement getWoundInfectionLevel
    return 0;
}

void BodyPart::setWoundInfectionLevel(float var1) {
    // TODO: Implement setWoundInfectionLevel
}

void BodyPart::setBurned() {
    // TODO: Implement setBurned
}

std::string BodyPart::getSplintItem() {
    // TODO: Implement getSplintItem
    return "";
}

void BodyPart::setSplintItem(const std::string& var1) {
    // TODO: Implement setSplintItem
}

float BodyPart::getPlantainFactor() {
    // TODO: Implement getPlantainFactor
    return 0;
}

void BodyPart::setPlantainFactor(float var1) {
    // TODO: Implement setPlantainFactor
}

float BodyPart::getGarlicFactor() {
    // TODO: Implement getGarlicFactor
    return 0;
}

void BodyPart::setGarlicFactor(float var1) {
    // TODO: Implement setGarlicFactor
}

float BodyPart::getComfreyFactor() {
    // TODO: Implement getComfreyFactor
    return 0;
}

void BodyPart::setComfreyFactor(float var1) {
    // TODO: Implement setComfreyFactor
}

void BodyPart::sync(BodyPart var1, Updater var2) {
    // TODO: Implement sync
}

void BodyPart::sync(ByteBuffer var1, uint8_t var2) {
    // TODO: Implement sync
}

float BodyPart::getCutTime() {
    // TODO: Implement getCutTime
    return 0;
}

void BodyPart::setCutTime(float var1) {
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

void BodyPart::setScratchSpeedModifier(float var1) {
    // TODO: Implement setScratchSpeedModifier
}

float BodyPart::getCutSpeedModifier() {
    // TODO: Implement getCutSpeedModifier
    return 0;
}

void BodyPart::setCutSpeedModifier(float var1) {
    // TODO: Implement setCutSpeedModifier
}

float BodyPart::getBurnSpeedModifier() {
    // TODO: Implement getBurnSpeedModifier
    return 0;
}

void BodyPart::setBurnSpeedModifier(float var1) {
    // TODO: Implement setBurnSpeedModifier
}

float BodyPart::getDeepWoundSpeedModifier() {
    // TODO: Implement getDeepWoundSpeedModifier
    return 0;
}

void BodyPart::setDeepWoundSpeedModifier(float var1) {
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

ThermalNode BodyPart::getThermalNode() {
    // TODO: Implement getThermalNode
    return nullptr;
}

float BodyPart::getWetness() {
    // TODO: Implement getWetness
    return 0;
}

void BodyPart::setWetness(float var1) {
    // TODO: Implement setWetness
}

float BodyPart::getStiffness() {
    // TODO: Implement getStiffness
    return 0;
}

void BodyPart::setStiffness(float var1) {
    // TODO: Implement setStiffness
}

} // namespace BodyDamage
} // namespace characters
} // namespace zombie
