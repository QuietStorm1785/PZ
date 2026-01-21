#include <string>
#include "zombie/characters/BodyDamage/BodyDamage.h"

namespace zombie {
namespace characters {
namespace BodyDamage {

public BodyDamage::BodyDamage(IsoGameCharacter var1) {
    // TODO: Implement BodyDamage
    return nullptr;
}

BodyPart BodyDamage::getBodyPart(BodyPartType var1) {
    // TODO: Implement getBodyPart
    return nullptr;
}

BodyPartLast BodyDamage::getBodyPartsLastState(BodyPartType var1) {
    // TODO: Implement getBodyPartsLastState
    return nullptr;
}

void BodyDamage::setBodyPartsLastState() {
    // TODO: Implement setBodyPartsLastState
}

void BodyDamage::load(ByteBuffer var1, int var2) {
    // TODO: Implement load
}

void BodyDamage::save(ByteBuffer var1) {
    // TODO: Implement save
}

bool BodyDamage::IsFakeInfected() {
    // TODO: Implement IsFakeInfected
    return false;
}

void BodyDamage::OnFire(bool var1) {
    // TODO: Implement OnFire
}

bool BodyDamage::IsOnFire() {
    // TODO: Implement IsOnFire
    return false;
}

bool BodyDamage::WasBurntToDeath() {
    // TODO: Implement WasBurntToDeath
    return false;
}

void BodyDamage::IncreasePanicFloat(float var1) {
    // TODO: Implement IncreasePanicFloat
}

void BodyDamage::IncreasePanic(int var1) {
    // TODO: Implement IncreasePanic
}

void BodyDamage::ReducePanic() {
    // TODO: Implement ReducePanic
}

void BodyDamage::UpdatePanicState() {
    // TODO: Implement UpdatePanicState
}

void BodyDamage::JustDrankBooze(Food var1, float var2) {
    // TODO: Implement JustDrankBooze
}

void BodyDamage::JustTookPill(InventoryItem var1) {
    // TODO: Implement JustTookPill
}

void BodyDamage::JustAteFood(Food var1, float var2) {
    // TODO: Implement JustAteFood
}

void BodyDamage::JustAteFood(Food var1) {
    // TODO: Implement JustAteFood
}

float BodyDamage::getHealthFromFoodTimeByHunger() {
    // TODO: Implement getHealthFromFoodTimeByHunger
    return 0;
}

void BodyDamage::JustReadSomething(Literature var1) {
    // TODO: Implement JustReadSomething
}

void BodyDamage::JustTookPainMeds() {
    // TODO: Implement JustTookPainMeds
}

void BodyDamage::UpdateWetness() {
    // TODO: Implement UpdateWetness
}

void BodyDamage::TriggerSneezeCough() {
    // TODO: Implement TriggerSneezeCough
}

int BodyDamage::IsSneezingCoughing() {
    // TODO: Implement IsSneezingCoughing
    return 0;
}

void BodyDamage::UpdateCold() {
    // TODO: Implement UpdateCold
}

float BodyDamage::getColdStrength() {
    // TODO: Implement getColdStrength
    return 0;
}

float BodyDamage::getWetness() {
    // TODO: Implement getWetness
    return 0;
}

void BodyDamage::AddDamage(BodyPartType var1, float var2) {
    // TODO: Implement AddDamage
}

void BodyDamage::AddGeneralHealth(float var1) {
    // TODO: Implement AddGeneralHealth
}

void BodyDamage::ReduceGeneralHealth(float var1) {
    // TODO: Implement ReduceGeneralHealth
}

void BodyDamage::AddDamage(int var1, float var2) {
    // TODO: Implement AddDamage
}

void BodyDamage::splatBloodFloorBig() {
    // TODO: Implement splatBloodFloorBig
}

void BodyDamage::DamageFromWeapon(HandWeapon var1) {
    // TODO: Implement DamageFromWeapon
}

bool BodyDamage::AddRandomDamageFromZombie(IsoZombie var1, const std::string& var2) {
    // TODO: Implement AddRandomDamageFromZombie
    return false;
}

bool BodyDamage::doesBodyPartHaveInjury(BodyPartType var1) {
    // TODO: Implement doesBodyPartHaveInjury
    return false;
}

bool BodyDamage::doBodyPartsHaveInjuries(BodyPartType var1, BodyPartType var2) {
    // TODO: Implement doBodyPartsHaveInjuries
    return false;
}

bool BodyDamage::isBodyPartBleeding(BodyPartType var1) {
    // TODO: Implement isBodyPartBleeding
    return false;
}

bool BodyDamage::areBodyPartsBleeding(BodyPartType var1, BodyPartType var2) {
    // TODO: Implement areBodyPartsBleeding
    return false;
}

void BodyDamage::DrawUntexturedQuad(int var1, int var2, int var3, int var4, float var5, float var6, float var7, float var8) {
    // TODO: Implement DrawUntexturedQuad
}

float BodyDamage::getBodyPartHealth(BodyPartType var1) {
    // TODO: Implement getBodyPartHealth
    return 0;
}

float BodyDamage::getBodyPartHealth(int var1) {
    // TODO: Implement getBodyPartHealth
    return 0;
}

std::string BodyDamage::getBodyPartName(BodyPartType var1) {
    // TODO: Implement getBodyPartName
    return "";
}

std::string BodyDamage::getBodyPartName(int var1) {
    // TODO: Implement getBodyPartName
    return "";
}

float BodyDamage::getHealth() {
    // TODO: Implement getHealth
    return 0;
}

float BodyDamage::getInfectionLevel() {
    // TODO: Implement getInfectionLevel
    return 0;
}

float BodyDamage::getApparentInfectionLevel() {
    // TODO: Implement getApparentInfectionLevel
    return 0;
}

int BodyDamage::getNumPartsBleeding() {
    // TODO: Implement getNumPartsBleeding
    return 0;
}

int BodyDamage::getNumPartsScratched() {
    // TODO: Implement getNumPartsScratched
    return 0;
}

int BodyDamage::getNumPartsBitten() {
    // TODO: Implement getNumPartsBitten
    return 0;
}

bool BodyDamage::HasInjury() {
    // TODO: Implement HasInjury
    return false;
}

bool BodyDamage::IsBandaged(BodyPartType var1) {
    // TODO: Implement IsBandaged
    return false;
}

bool BodyDamage::IsDeepWounded(BodyPartType var1) {
    // TODO: Implement IsDeepWounded
    return false;
}

bool BodyDamage::IsBandaged(int var1) {
    // TODO: Implement IsBandaged
    return false;
}

bool BodyDamage::IsBitten(BodyPartType var1) {
    // TODO: Implement IsBitten
    return false;
}

bool BodyDamage::IsBitten(int var1) {
    // TODO: Implement IsBitten
    return false;
}

bool BodyDamage::IsBleeding(BodyPartType var1) {
    // TODO: Implement IsBleeding
    return false;
}

bool BodyDamage::IsBleeding(int var1) {
    // TODO: Implement IsBleeding
    return false;
}

bool BodyDamage::IsBleedingStemmed(BodyPartType var1) {
    // TODO: Implement IsBleedingStemmed
    return false;
}

bool BodyDamage::IsBleedingStemmed(int var1) {
    // TODO: Implement IsBleedingStemmed
    return false;
}

bool BodyDamage::IsCortorised(BodyPartType var1) {
    // TODO: Implement IsCortorised
    return false;
}

bool BodyDamage::IsCortorised(int var1) {
    // TODO: Implement IsCortorised
    return false;
}

bool BodyDamage::IsInfected() {
    // TODO: Implement IsInfected
    return false;
}

bool BodyDamage::IsInfected(BodyPartType var1) {
    // TODO: Implement IsInfected
    return false;
}

bool BodyDamage::IsInfected(int var1) {
    // TODO: Implement IsInfected
    return false;
}

bool BodyDamage::IsFakeInfected(int var1) {
    // TODO: Implement IsFakeInfected
    return false;
}

void BodyDamage::DisableFakeInfection(int var1) {
    // TODO: Implement DisableFakeInfection
}

bool BodyDamage::IsScratched(BodyPartType var1) {
    // TODO: Implement IsScratched
    return false;
}

bool BodyDamage::IsCut(BodyPartType var1) {
    // TODO: Implement IsCut
    return false;
}

bool BodyDamage::IsScratched(int var1) {
    // TODO: Implement IsScratched
    return false;
}

bool BodyDamage::IsStitched(BodyPartType var1) {
    // TODO: Implement IsStitched
    return false;
}

bool BodyDamage::IsStitched(int var1) {
    // TODO: Implement IsStitched
    return false;
}

bool BodyDamage::IsWounded(BodyPartType var1) {
    // TODO: Implement IsWounded
    return false;
}

bool BodyDamage::IsWounded(int var1) {
    // TODO: Implement IsWounded
    return false;
}

void BodyDamage::RestoreToFullHealth() {
    // TODO: Implement RestoreToFullHealth
}

void BodyDamage::SetBandaged(int var1, bool var2, float var3, bool var4, const std::string& var5) {
    // TODO: Implement SetBandaged
}

void BodyDamage::SetBitten(BodyPartType var1, bool var2) {
    // TODO: Implement SetBitten
}

void BodyDamage::SetBitten(int var1, bool var2) {
    // TODO: Implement SetBitten
}

void BodyDamage::SetBitten(int var1, bool var2, bool var3) {
    // TODO: Implement SetBitten
}

void BodyDamage::SetBleeding(BodyPartType var1, bool var2) {
    // TODO: Implement SetBleeding
}

void BodyDamage::SetBleeding(int var1, bool var2) {
    // TODO: Implement SetBleeding
}

void BodyDamage::SetBleedingStemmed(BodyPartType var1, bool var2) {
    // TODO: Implement SetBleedingStemmed
}

void BodyDamage::SetBleedingStemmed(int var1, bool var2) {
    // TODO: Implement SetBleedingStemmed
}

void BodyDamage::SetCortorised(BodyPartType var1, bool var2) {
    // TODO: Implement SetCortorised
}

void BodyDamage::SetCortorised(int var1, bool var2) {
    // TODO: Implement SetCortorised
}

BodyPart BodyDamage::setScratchedWindow() {
    // TODO: Implement setScratchedWindow
    return nullptr;
}

void BodyDamage::SetScratched(BodyPartType var1, bool var2) {
    // TODO: Implement SetScratched
}

void BodyDamage::SetScratched(int var1, bool var2) {
    // TODO: Implement SetScratched
}

void BodyDamage::SetScratchedFromWeapon(int var1, bool var2) {
    // TODO: Implement SetScratchedFromWeapon
}

void BodyDamage::SetCut(int var1, bool var2) {
    // TODO: Implement SetCut
}

void BodyDamage::SetWounded(BodyPartType var1, bool var2) {
    // TODO: Implement SetWounded
}

void BodyDamage::SetWounded(int var1, bool var2) {
    // TODO: Implement SetWounded
}

void BodyDamage::ShowDebugInfo() {
    // TODO: Implement ShowDebugInfo
}

void BodyDamage::UpdateBoredom() {
    // TODO: Implement UpdateBoredom
}

float BodyDamage::getUnhappynessLevel() {
    // TODO: Implement getUnhappynessLevel
    return 0;
}

float BodyDamage::getBoredomLevel() {
    // TODO: Implement getBoredomLevel
    return 0;
}

void BodyDamage::UpdateStrength() {
    // TODO: Implement UpdateStrength
}

float BodyDamage::pickMortalityDuration() {
    // TODO: Implement pickMortalityDuration
    return 0;
}

void BodyDamage::Update() {
    // TODO: Implement Update
}

void BodyDamage::calculateOverallHealth() {
    // TODO: Implement calculateOverallHealth
}

float BodyDamage::getSicknessFromCorpsesRate(int var0) {
    // TODO: Implement getSicknessFromCorpsesRate
    return 0;
}

void BodyDamage::UpdateIllness() {
    // TODO: Implement UpdateIllness
}

void BodyDamage::UpdateTemperatureState() {
    // TODO: Implement UpdateTemperatureState
}

float BodyDamage::getDamageFromPills() {
    // TODO: Implement getDamageFromPills
    return 0;
}

bool BodyDamage::UseBandageOnMostNeededPart() {
    // TODO: Implement UseBandageOnMostNeededPart
    return false;
}

int BodyDamage::getDamageModCount() {
    // TODO: Implement getDamageModCount
    return 0;
}

void BodyDamage::setDamageModCount(int var1) {
    // TODO: Implement setDamageModCount
}

float BodyDamage::getInfectionGrowthRate() {
    // TODO: Implement getInfectionGrowthRate
    return 0;
}

void BodyDamage::setInfectionGrowthRate(float var1) {
    // TODO: Implement setInfectionGrowthRate
}

void BodyDamage::setInfectionLevel(float var1) {
    // TODO: Implement setInfectionLevel
}

bool BodyDamage::isInfected() {
    // TODO: Implement isInfected
    return false;
}

void BodyDamage::setInfected(bool var1) {
    // TODO: Implement setInfected
}

float BodyDamage::getInfectionTime() {
    // TODO: Implement getInfectionTime
    return 0;
}

void BodyDamage::setInfectionTime(float var1) {
    // TODO: Implement setInfectionTime
}

float BodyDamage::getInfectionMortalityDuration() {
    // TODO: Implement getInfectionMortalityDuration
    return 0;
}

void BodyDamage::setInfectionMortalityDuration(float var1) {
    // TODO: Implement setInfectionMortalityDuration
}

float BodyDamage::getCurrentTimeForInfection() {
    // TODO: Implement getCurrentTimeForInfection
    return 0;
}

bool BodyDamage::isInf() {
    // TODO: Implement isInf
    return false;
}

void BodyDamage::setInf(bool var1) {
    // TODO: Implement setInf
}

float BodyDamage::getFakeInfectionLevel() {
    // TODO: Implement getFakeInfectionLevel
    return 0;
}

void BodyDamage::setFakeInfectionLevel(float var1) {
    // TODO: Implement setFakeInfectionLevel
}

bool BodyDamage::isIsFakeInfected() {
    // TODO: Implement isIsFakeInfected
    return false;
}

void BodyDamage::setIsFakeInfected(bool var1) {
    // TODO: Implement setIsFakeInfected
}

float BodyDamage::getOverallBodyHealth() {
    // TODO: Implement getOverallBodyHealth
    return 0;
}

void BodyDamage::setOverallBodyHealth(float var1) {
    // TODO: Implement setOverallBodyHealth
}

float BodyDamage::getStandardHealthAddition() {
    // TODO: Implement getStandardHealthAddition
    return 0;
}

void BodyDamage::setStandardHealthAddition(float var1) {
    // TODO: Implement setStandardHealthAddition
}

float BodyDamage::getReducedHealthAddition() {
    // TODO: Implement getReducedHealthAddition
    return 0;
}

void BodyDamage::setReducedHealthAddition(float var1) {
    // TODO: Implement setReducedHealthAddition
}

float BodyDamage::getSeverlyReducedHealthAddition() {
    // TODO: Implement getSeverlyReducedHealthAddition
    return 0;
}

void BodyDamage::setSeverlyReducedHealthAddition(float var1) {
    // TODO: Implement setSeverlyReducedHealthAddition
}

float BodyDamage::getSleepingHealthAddition() {
    // TODO: Implement getSleepingHealthAddition
    return 0;
}

void BodyDamage::setSleepingHealthAddition(float var1) {
    // TODO: Implement setSleepingHealthAddition
}

float BodyDamage::getHealthFromFood() {
    // TODO: Implement getHealthFromFood
    return 0;
}

void BodyDamage::setHealthFromFood(float var1) {
    // TODO: Implement setHealthFromFood
}

float BodyDamage::getHealthReductionFromSevereBadMoodles() {
    // TODO: Implement getHealthReductionFromSevereBadMoodles
    return 0;
}

void BodyDamage::setHealthReductionFromSevereBadMoodles(float var1) {
    // TODO: Implement setHealthReductionFromSevereBadMoodles
}

int BodyDamage::getStandardHealthFromFoodTime() {
    // TODO: Implement getStandardHealthFromFoodTime
    return 0;
}

void BodyDamage::setStandardHealthFromFoodTime(int var1) {
    // TODO: Implement setStandardHealthFromFoodTime
}

float BodyDamage::getHealthFromFoodTimer() {
    // TODO: Implement getHealthFromFoodTimer
    return 0;
}

void BodyDamage::setHealthFromFoodTimer(float var1) {
    // TODO: Implement setHealthFromFoodTimer
}

void BodyDamage::setBoredomLevel(float var1) {
    // TODO: Implement setBoredomLevel
}

float BodyDamage::getBoredomDecreaseFromReading() {
    // TODO: Implement getBoredomDecreaseFromReading
    return 0;
}

void BodyDamage::setBoredomDecreaseFromReading(float var1) {
    // TODO: Implement setBoredomDecreaseFromReading
}

float BodyDamage::getInitialThumpPain() {
    // TODO: Implement getInitialThumpPain
    return 0;
}

void BodyDamage::setInitialThumpPain(float var1) {
    // TODO: Implement setInitialThumpPain
}

float BodyDamage::getInitialScratchPain() {
    // TODO: Implement getInitialScratchPain
    return 0;
}

void BodyDamage::setInitialScratchPain(float var1) {
    // TODO: Implement setInitialScratchPain
}

float BodyDamage::getInitialBitePain() {
    // TODO: Implement getInitialBitePain
    return 0;
}

void BodyDamage::setInitialBitePain(float var1) {
    // TODO: Implement setInitialBitePain
}

float BodyDamage::getInitialWoundPain() {
    // TODO: Implement getInitialWoundPain
    return 0;
}

void BodyDamage::setInitialWoundPain(float var1) {
    // TODO: Implement setInitialWoundPain
}

float BodyDamage::getContinualPainIncrease() {
    // TODO: Implement getContinualPainIncrease
    return 0;
}

void BodyDamage::setContinualPainIncrease(float var1) {
    // TODO: Implement setContinualPainIncrease
}

float BodyDamage::getPainReductionFromMeds() {
    // TODO: Implement getPainReductionFromMeds
    return 0;
}

void BodyDamage::setPainReductionFromMeds(float var1) {
    // TODO: Implement setPainReductionFromMeds
}

float BodyDamage::getStandardPainReductionWhenWell() {
    // TODO: Implement getStandardPainReductionWhenWell
    return 0;
}

void BodyDamage::setStandardPainReductionWhenWell(float var1) {
    // TODO: Implement setStandardPainReductionWhenWell
}

int BodyDamage::getOldNumZombiesVisible() {
    // TODO: Implement getOldNumZombiesVisible
    return 0;
}

void BodyDamage::setOldNumZombiesVisible(int var1) {
    // TODO: Implement setOldNumZombiesVisible
}

int BodyDamage::getCurrentNumZombiesVisible() {
    // TODO: Implement getCurrentNumZombiesVisible
    return 0;
}

void BodyDamage::setCurrentNumZombiesVisible(int var1) {
    // TODO: Implement setCurrentNumZombiesVisible
}

float BodyDamage::getPanicIncreaseValue() {
    // TODO: Implement getPanicIncreaseValue
    return 0;
}

float BodyDamage::getPanicIncreaseValueFrame() {
    // TODO: Implement getPanicIncreaseValueFrame
    return 0;
}

void BodyDamage::setPanicIncreaseValue(float var1) {
    // TODO: Implement setPanicIncreaseValue
}

float BodyDamage::getPanicReductionValue() {
    // TODO: Implement getPanicReductionValue
    return 0;
}

void BodyDamage::setPanicReductionValue(float var1) {
    // TODO: Implement setPanicReductionValue
}

float BodyDamage::getDrunkIncreaseValue() {
    // TODO: Implement getDrunkIncreaseValue
    return 0;
}

void BodyDamage::setDrunkIncreaseValue(float var1) {
    // TODO: Implement setDrunkIncreaseValue
}

float BodyDamage::getDrunkReductionValue() {
    // TODO: Implement getDrunkReductionValue
    return 0;
}

void BodyDamage::setDrunkReductionValue(float var1) {
    // TODO: Implement setDrunkReductionValue
}

bool BodyDamage::isIsOnFire() {
    // TODO: Implement isIsOnFire
    return false;
}

void BodyDamage::setIsOnFire(bool var1) {
    // TODO: Implement setIsOnFire
}

bool BodyDamage::isBurntToDeath() {
    // TODO: Implement isBurntToDeath
    return false;
}

void BodyDamage::setBurntToDeath(bool var1) {
    // TODO: Implement setBurntToDeath
}

void BodyDamage::setWetness(float var1) {
    // TODO: Implement setWetness
}

float BodyDamage::getCatchACold() {
    // TODO: Implement getCatchACold
    return 0;
}

void BodyDamage::setCatchACold(float var1) {
    // TODO: Implement setCatchACold
}

bool BodyDamage::isHasACold() {
    // TODO: Implement isHasACold
    return false;
}

void BodyDamage::setHasACold(bool var1) {
    // TODO: Implement setHasACold
}

void BodyDamage::setColdStrength(float var1) {
    // TODO: Implement setColdStrength
}

float BodyDamage::getColdProgressionRate() {
    // TODO: Implement getColdProgressionRate
    return 0;
}

void BodyDamage::setColdProgressionRate(float var1) {
    // TODO: Implement setColdProgressionRate
}

int BodyDamage::getTimeToSneezeOrCough() {
    // TODO: Implement getTimeToSneezeOrCough
    return 0;
}

void BodyDamage::setTimeToSneezeOrCough(int var1) {
    // TODO: Implement setTimeToSneezeOrCough
}

int BodyDamage::getMildColdSneezeTimerMin() {
    // TODO: Implement getMildColdSneezeTimerMin
    return 0;
}

void BodyDamage::setMildColdSneezeTimerMin(int var1) {
    // TODO: Implement setMildColdSneezeTimerMin
}

int BodyDamage::getMildColdSneezeTimerMax() {
    // TODO: Implement getMildColdSneezeTimerMax
    return 0;
}

void BodyDamage::setMildColdSneezeTimerMax(int var1) {
    // TODO: Implement setMildColdSneezeTimerMax
}

int BodyDamage::getColdSneezeTimerMin() {
    // TODO: Implement getColdSneezeTimerMin
    return 0;
}

void BodyDamage::setColdSneezeTimerMin(int var1) {
    // TODO: Implement setColdSneezeTimerMin
}

int BodyDamage::getColdSneezeTimerMax() {
    // TODO: Implement getColdSneezeTimerMax
    return 0;
}

void BodyDamage::setColdSneezeTimerMax(int var1) {
    // TODO: Implement setColdSneezeTimerMax
}

int BodyDamage::getNastyColdSneezeTimerMin() {
    // TODO: Implement getNastyColdSneezeTimerMin
    return 0;
}

void BodyDamage::setNastyColdSneezeTimerMin(int var1) {
    // TODO: Implement setNastyColdSneezeTimerMin
}

int BodyDamage::getNastyColdSneezeTimerMax() {
    // TODO: Implement getNastyColdSneezeTimerMax
    return 0;
}

void BodyDamage::setNastyColdSneezeTimerMax(int var1) {
    // TODO: Implement setNastyColdSneezeTimerMax
}

int BodyDamage::getSneezeCoughActive() {
    // TODO: Implement getSneezeCoughActive
    return 0;
}

void BodyDamage::setSneezeCoughActive(int var1) {
    // TODO: Implement setSneezeCoughActive
}

int BodyDamage::getSneezeCoughTime() {
    // TODO: Implement getSneezeCoughTime
    return 0;
}

void BodyDamage::setSneezeCoughTime(int var1) {
    // TODO: Implement setSneezeCoughTime
}

int BodyDamage::getSneezeCoughDelay() {
    // TODO: Implement getSneezeCoughDelay
    return 0;
}

void BodyDamage::setSneezeCoughDelay(int var1) {
    // TODO: Implement setSneezeCoughDelay
}

void BodyDamage::setUnhappynessLevel(float var1) {
    // TODO: Implement setUnhappynessLevel
}

IsoGameCharacter BodyDamage::getParentChar() {
    // TODO: Implement getParentChar
    return nullptr;
}

void BodyDamage::setParentChar(IsoGameCharacter var1) {
    // TODO: Implement setParentChar
}

float BodyDamage::getTemperature() {
    // TODO: Implement getTemperature
    return 0;
}

void BodyDamage::setTemperature(float var1) {
    // TODO: Implement setTemperature
}

float BodyDamage::getTemperatureChangeTick() {
    // TODO: Implement getTemperatureChangeTick
    return 0;
}

void BodyDamage::setPoisonLevel(float var1) {
    // TODO: Implement setPoisonLevel
}

float BodyDamage::getPoisonLevel() {
    // TODO: Implement getPoisonLevel
    return 0;
}

float BodyDamage::getFoodSicknessLevel() {
    // TODO: Implement getFoodSicknessLevel
    return 0;
}

void BodyDamage::setFoodSicknessLevel(float var1) {
    // TODO: Implement setFoodSicknessLevel
}

bool BodyDamage::isReduceFakeInfection() {
    // TODO: Implement isReduceFakeInfection
    return false;
}

void BodyDamage::setReduceFakeInfection(bool var1) {
    // TODO: Implement setReduceFakeInfection
}

void BodyDamage::AddRandomDamage() {
    // TODO: Implement AddRandomDamage
}

float BodyDamage::getPainReduction() {
    // TODO: Implement getPainReduction
    return 0;
}

void BodyDamage::setPainReduction(float var1) {
    // TODO: Implement setPainReduction
}

float BodyDamage::getColdReduction() {
    // TODO: Implement getColdReduction
    return 0;
}

void BodyDamage::setColdReduction(float var1) {
    // TODO: Implement setColdReduction
}

int BodyDamage::getRemotePainLevel() {
    // TODO: Implement getRemotePainLevel
    return 0;
}

void BodyDamage::setRemotePainLevel(int var1) {
    // TODO: Implement setRemotePainLevel
}

float BodyDamage::getColdDamageStage() {
    // TODO: Implement getColdDamageStage
    return 0;
}

void BodyDamage::setColdDamageStage(float var1) {
    // TODO: Implement setColdDamageStage
}

Thermoregulator BodyDamage::getThermoregulator() {
    // TODO: Implement getThermoregulator
    return nullptr;
}

void BodyDamage::decreaseBodyWetness(float var1) {
    // TODO: Implement decreaseBodyWetness
}

void BodyDamage::increaseBodyWetness(float var1) {
    // TODO: Implement increaseBodyWetness
}

} // namespace BodyDamage
} // namespace characters
} // namespace zombie
