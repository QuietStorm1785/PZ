#include "zombie/characters/BodyDamage/BodyDamage.h"

namespace zombie {
namespace characters {
namespace BodyDamage {

public
BodyDamage::BodyDamage(IsoGameCharacter ParentCharacter) {
  // TODO: Implement BodyDamage
  return nullptr;
}

BodyPart BodyDamage::getBodyPart(BodyPartType type) {
  // TODO: Implement getBodyPart
  return nullptr;
}

BodyPartLast BodyDamage::getBodyPartsLastState(BodyPartType type) {
  // TODO: Implement getBodyPartsLastState
  return nullptr;
}

void BodyDamage::setBodyPartsLastState() {
  // TODO: Implement setBodyPartsLastState
}

void BodyDamage::load(ByteBuffer input, int WorldVersion) {
  // TODO: Implement load
}

void BodyDamage::save(ByteBuffer output) {
  // TODO: Implement save
}

bool BodyDamage::IsFakeInfected() {
  // TODO: Implement IsFakeInfected
  return false;
}

void BodyDamage::OnFire(bool OnFire) {
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

void BodyDamage::IncreasePanicFloat(float delta) {
  // TODO: Implement IncreasePanicFloat
}

void BodyDamage::IncreasePanic(int NumNewZombiesSeen) {
  // TODO: Implement IncreasePanic
}

void BodyDamage::ReducePanic() {
  // TODO: Implement ReducePanic
}

void BodyDamage::UpdatePanicState() {
  // TODO: Implement UpdatePanicState
}

void BodyDamage::JustDrankBooze(Food food, float percentage) {
  // TODO: Implement JustDrankBooze
}

void BodyDamage::JustTookPill(InventoryItem Pill) {
  // TODO: Implement JustTookPill
}

void BodyDamage::JustAteFood(Food NewFood, float percentage) {
  // TODO: Implement JustAteFood
}

void BodyDamage::JustAteFood(Food NewFood) {
  // TODO: Implement JustAteFood
}

float BodyDamage::getHealthFromFoodTimeByHunger() {
  // TODO: Implement getHealthFromFoodTimeByHunger
  return 0;
}

void BodyDamage::JustReadSomething(Literature lit) {
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

void BodyDamage::AddDamage(BodyPartType BodyPart, float Val) {
  // TODO: Implement AddDamage
}

void BodyDamage::AddGeneralHealth(float Val) {
  // TODO: Implement AddGeneralHealth
}

void BodyDamage::ReduceGeneralHealth(float Val) {
  // TODO: Implement ReduceGeneralHealth
}

void BodyDamage::AddDamage(int BodyPartIndex, float val) {
  // TODO: Implement AddDamage
}

void BodyDamage::splatBloodFloorBig() {
  // TODO: Implement splatBloodFloorBig
}

void BodyDamage::DamageFromWeapon(HandWeapon weapon) {
  // TODO: Implement DamageFromWeapon
}

bool BodyDamage::AddRandomDamageFromZombie(IsoZombie zombie,
                                           const std::string &hitReaction) {
  // TODO: Implement AddRandomDamageFromZombie
  return false;
}

bool BodyDamage::doesBodyPartHaveInjury(BodyPartType part) {
  // TODO: Implement doesBodyPartHaveInjury
  return false;
}

bool BodyDamage::doBodyPartsHaveInjuries(BodyPartType partA,
                                         BodyPartType partB) {
  // TODO: Implement doBodyPartsHaveInjuries
  return false;
}

bool BodyDamage::isBodyPartBleeding(BodyPartType part) {
  // TODO: Implement isBodyPartBleeding
  return false;
}

bool BodyDamage::areBodyPartsBleeding(BodyPartType partA, BodyPartType partB) {
  // TODO: Implement areBodyPartsBleeding
  return false;
}

void BodyDamage::DrawUntexturedQuad(int X, int Y, int Width, int Height,
                                    float r, float g, float b, float a) {
  // TODO: Implement DrawUntexturedQuad
}

float BodyDamage::getBodyPartHealth(BodyPartType BodyPart) {
  // TODO: Implement getBodyPartHealth
  return 0;
}

float BodyDamage::getBodyPartHealth(int BodyPartIndex) {
  // TODO: Implement getBodyPartHealth
  return 0;
}

std::string BodyDamage::getBodyPartName(BodyPartType BodyPart) {
  // TODO: Implement getBodyPartName
  return "";
}

std::string BodyDamage::getBodyPartName(int BodyPartIndex) {
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

bool BodyDamage::IsBandaged(BodyPartType BodyPart) {
  // TODO: Implement IsBandaged
  return false;
}

bool BodyDamage::IsDeepWounded(BodyPartType BodyPart) {
  // TODO: Implement IsDeepWounded
  return false;
}

bool BodyDamage::IsBandaged(int BodyPartIndex) {
  // TODO: Implement IsBandaged
  return false;
}

bool BodyDamage::IsBitten(BodyPartType BodyPart) {
  // TODO: Implement IsBitten
  return false;
}

bool BodyDamage::IsBitten(int BodyPartIndex) {
  // TODO: Implement IsBitten
  return false;
}

bool BodyDamage::IsBleeding(BodyPartType BodyPart) {
  // TODO: Implement IsBleeding
  return false;
}

bool BodyDamage::IsBleeding(int BodyPartIndex) {
  // TODO: Implement IsBleeding
  return false;
}

bool BodyDamage::IsBleedingStemmed(BodyPartType BodyPart) {
  // TODO: Implement IsBleedingStemmed
  return false;
}

bool BodyDamage::IsBleedingStemmed(int BodyPartIndex) {
  // TODO: Implement IsBleedingStemmed
  return false;
}

bool BodyDamage::IsCortorised(BodyPartType BodyPart) {
  // TODO: Implement IsCortorised
  return false;
}

bool BodyDamage::IsCortorised(int BodyPartIndex) {
  // TODO: Implement IsCortorised
  return false;
}

bool BodyDamage::IsInfected() {
  // TODO: Implement IsInfected
  return false;
}

bool BodyDamage::IsInfected(BodyPartType BodyPart) {
  // TODO: Implement IsInfected
  return false;
}

bool BodyDamage::IsInfected(int BodyPartIndex) {
  // TODO: Implement IsInfected
  return false;
}

bool BodyDamage::IsFakeInfected(int BodyPartIndex) {
  // TODO: Implement IsFakeInfected
  return false;
}

void BodyDamage::DisableFakeInfection(int BodyPartIndex) {
  // TODO: Implement DisableFakeInfection
}

bool BodyDamage::IsScratched(BodyPartType BodyPart) {
  // TODO: Implement IsScratched
  return false;
}

bool BodyDamage::IsCut(BodyPartType BodyPart) {
  // TODO: Implement IsCut
  return false;
}

bool BodyDamage::IsScratched(int BodyPartIndex) {
  // TODO: Implement IsScratched
  return false;
}

bool BodyDamage::IsStitched(BodyPartType BodyPart) {
  // TODO: Implement IsStitched
  return false;
}

bool BodyDamage::IsStitched(int BodyPartIndex) {
  // TODO: Implement IsStitched
  return false;
}

bool BodyDamage::IsWounded(BodyPartType BodyPart) {
  // TODO: Implement IsWounded
  return false;
}

bool BodyDamage::IsWounded(int BodyPartIndex) {
  // TODO: Implement IsWounded
  return false;
}

void BodyDamage::RestoreToFullHealth() {
  // TODO: Implement RestoreToFullHealth
}

void BodyDamage::SetBandaged(int BodyPartIndex, bool Bandaged,
                             float bandageLife, bool isAlcoholic,
                             const std::string &bandageType) {
  // TODO: Implement SetBandaged
}

void BodyDamage::SetBitten(BodyPartType BodyPart, bool Bitten) {
  // TODO: Implement SetBitten
}

void BodyDamage::SetBitten(int BodyPartIndex, bool Bitten) {
  // TODO: Implement SetBitten
}

void BodyDamage::SetBitten(int BodyPartIndex, bool Bitten, bool Infected) {
  // TODO: Implement SetBitten
}

void BodyDamage::SetBleeding(BodyPartType BodyPart, bool Bleeding) {
  // TODO: Implement SetBleeding
}

void BodyDamage::SetBleeding(int BodyPartIndex, bool Bleeding) {
  // TODO: Implement SetBleeding
}

void BodyDamage::SetBleedingStemmed(BodyPartType BodyPart,
                                    bool BleedingStemmed) {
  // TODO: Implement SetBleedingStemmed
}

void BodyDamage::SetBleedingStemmed(int BodyPartIndex, bool BleedingStemmed) {
  // TODO: Implement SetBleedingStemmed
}

void BodyDamage::SetCortorised(BodyPartType BodyPart, bool Cortorised) {
  // TODO: Implement SetCortorised
}

void BodyDamage::SetCortorised(int BodyPartIndex, bool Cortorised) {
  // TODO: Implement SetCortorised
}

BodyPart BodyDamage::setScratchedWindow() {
  // TODO: Implement setScratchedWindow
  return nullptr;
}

void BodyDamage::SetScratched(BodyPartType BodyPart, bool Scratched) {
  // TODO: Implement SetScratched
}

void BodyDamage::SetScratched(int BodyPartIndex, bool Scratched) {
  // TODO: Implement SetScratched
}

void BodyDamage::SetScratchedFromWeapon(int BodyPartIndex, bool Scratched) {
  // TODO: Implement SetScratchedFromWeapon
}

void BodyDamage::SetCut(int BodyPartIndex, bool Cut) {
  // TODO: Implement SetCut
}

void BodyDamage::SetWounded(BodyPartType BodyPart, bool Wounded) {
  // TODO: Implement SetWounded
}

void BodyDamage::SetWounded(int BodyPartIndex, bool Wounded) {
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

float BodyDamage::getSicknessFromCorpsesRate(int corpseCount) {
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

void BodyDamage::setDamageModCount(int _DamageModCount) {
  // TODO: Implement setDamageModCount
}

float BodyDamage::getInfectionGrowthRate() {
  // TODO: Implement getInfectionGrowthRate
  return 0;
}

void BodyDamage::setInfectionGrowthRate(float _InfectionGrowthRate) {
  // TODO: Implement setInfectionGrowthRate
}

void BodyDamage::setInfectionLevel(float _InfectionLevel) {
  // TODO: Implement setInfectionLevel
}

bool BodyDamage::isInfected() {
  // TODO: Implement isInfected
  return false;
}

void BodyDamage::setInfected(bool infected) {
  // TODO: Implement setInfected
}

float BodyDamage::getInfectionTime() {
  // TODO: Implement getInfectionTime
  return 0;
}

void BodyDamage::setInfectionTime(float worldHours) {
  // TODO: Implement setInfectionTime
}

float BodyDamage::getInfectionMortalityDuration() {
  // TODO: Implement getInfectionMortalityDuration
  return 0;
}

void BodyDamage::setInfectionMortalityDuration(float worldHours) {
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

void BodyDamage::setInf(bool inf) {
  // TODO: Implement setInf
}

float BodyDamage::getFakeInfectionLevel() {
  // TODO: Implement getFakeInfectionLevel
  return 0;
}

void BodyDamage::setFakeInfectionLevel(float _FakeInfectionLevel) {
  // TODO: Implement setFakeInfectionLevel
}

bool BodyDamage::isIsFakeInfected() {
  // TODO: Implement isIsFakeInfected
  return false;
}

void BodyDamage::setIsFakeInfected(bool _IsFakeInfected) {
  // TODO: Implement setIsFakeInfected
}

float BodyDamage::getOverallBodyHealth() {
  // TODO: Implement getOverallBodyHealth
  return 0;
}

void BodyDamage::setOverallBodyHealth(float _OverallBodyHealth) {
  // TODO: Implement setOverallBodyHealth
}

float BodyDamage::getStandardHealthAddition() {
  // TODO: Implement getStandardHealthAddition
  return 0;
}

void BodyDamage::setStandardHealthAddition(float _StandardHealthAddition) {
  // TODO: Implement setStandardHealthAddition
}

float BodyDamage::getReducedHealthAddition() {
  // TODO: Implement getReducedHealthAddition
  return 0;
}

void BodyDamage::setReducedHealthAddition(float _ReducedHealthAddition) {
  // TODO: Implement setReducedHealthAddition
}

float BodyDamage::getSeverlyReducedHealthAddition() {
  // TODO: Implement getSeverlyReducedHealthAddition
  return 0;
}

void BodyDamage::setSeverlyReducedHealthAddition(
    float _SeverlyReducedHealthAddition) {
  // TODO: Implement setSeverlyReducedHealthAddition
}

float BodyDamage::getSleepingHealthAddition() {
  // TODO: Implement getSleepingHealthAddition
  return 0;
}

void BodyDamage::setSleepingHealthAddition(float _SleepingHealthAddition) {
  // TODO: Implement setSleepingHealthAddition
}

float BodyDamage::getHealthFromFood() {
  // TODO: Implement getHealthFromFood
  return 0;
}

void BodyDamage::setHealthFromFood(float _HealthFromFood) {
  // TODO: Implement setHealthFromFood
}

float BodyDamage::getHealthReductionFromSevereBadMoodles() {
  // TODO: Implement getHealthReductionFromSevereBadMoodles
  return 0;
}

void BodyDamage::setHealthReductionFromSevereBadMoodles(
    float _HealthReductionFromSevereBadMoodles) {
  // TODO: Implement setHealthReductionFromSevereBadMoodles
}

int BodyDamage::getStandardHealthFromFoodTime() {
  // TODO: Implement getStandardHealthFromFoodTime
  return 0;
}

void BodyDamage::setStandardHealthFromFoodTime(
    int _StandardHealthFromFoodTime) {
  // TODO: Implement setStandardHealthFromFoodTime
}

float BodyDamage::getHealthFromFoodTimer() {
  // TODO: Implement getHealthFromFoodTimer
  return 0;
}

void BodyDamage::setHealthFromFoodTimer(float _HealthFromFoodTimer) {
  // TODO: Implement setHealthFromFoodTimer
}

void BodyDamage::setBoredomLevel(float _BoredomLevel) {
  // TODO: Implement setBoredomLevel
}

float BodyDamage::getBoredomDecreaseFromReading() {
  // TODO: Implement getBoredomDecreaseFromReading
  return 0;
}

void BodyDamage::setBoredomDecreaseFromReading(
    float _BoredomDecreaseFromReading) {
  // TODO: Implement setBoredomDecreaseFromReading
}

float BodyDamage::getInitialThumpPain() {
  // TODO: Implement getInitialThumpPain
  return 0;
}

void BodyDamage::setInitialThumpPain(float _InitialThumpPain) {
  // TODO: Implement setInitialThumpPain
}

float BodyDamage::getInitialScratchPain() {
  // TODO: Implement getInitialScratchPain
  return 0;
}

void BodyDamage::setInitialScratchPain(float _InitialScratchPain) {
  // TODO: Implement setInitialScratchPain
}

float BodyDamage::getInitialBitePain() {
  // TODO: Implement getInitialBitePain
  return 0;
}

void BodyDamage::setInitialBitePain(float _InitialBitePain) {
  // TODO: Implement setInitialBitePain
}

float BodyDamage::getInitialWoundPain() {
  // TODO: Implement getInitialWoundPain
  return 0;
}

void BodyDamage::setInitialWoundPain(float _InitialWoundPain) {
  // TODO: Implement setInitialWoundPain
}

float BodyDamage::getContinualPainIncrease() {
  // TODO: Implement getContinualPainIncrease
  return 0;
}

void BodyDamage::setContinualPainIncrease(float _ContinualPainIncrease) {
  // TODO: Implement setContinualPainIncrease
}

float BodyDamage::getPainReductionFromMeds() {
  // TODO: Implement getPainReductionFromMeds
  return 0;
}

void BodyDamage::setPainReductionFromMeds(float _PainReductionFromMeds) {
  // TODO: Implement setPainReductionFromMeds
}

float BodyDamage::getStandardPainReductionWhenWell() {
  // TODO: Implement getStandardPainReductionWhenWell
  return 0;
}

void BodyDamage::setStandardPainReductionWhenWell(
    float _StandardPainReductionWhenWell) {
  // TODO: Implement setStandardPainReductionWhenWell
}

int BodyDamage::getOldNumZombiesVisible() {
  // TODO: Implement getOldNumZombiesVisible
  return 0;
}

void BodyDamage::setOldNumZombiesVisible(int _OldNumZombiesVisible) {
  // TODO: Implement setOldNumZombiesVisible
}

int BodyDamage::getCurrentNumZombiesVisible() {
  // TODO: Implement getCurrentNumZombiesVisible
  return 0;
}

void BodyDamage::setCurrentNumZombiesVisible(int _CurrentNumZombiesVisible) {
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

void BodyDamage::setPanicIncreaseValue(float _PanicIncreaseValue) {
  // TODO: Implement setPanicIncreaseValue
}

float BodyDamage::getPanicReductionValue() {
  // TODO: Implement getPanicReductionValue
  return 0;
}

void BodyDamage::setPanicReductionValue(float _PanicReductionValue) {
  // TODO: Implement setPanicReductionValue
}

float BodyDamage::getDrunkIncreaseValue() {
  // TODO: Implement getDrunkIncreaseValue
  return 0;
}

void BodyDamage::setDrunkIncreaseValue(float _DrunkIncreaseValue) {
  // TODO: Implement setDrunkIncreaseValue
}

float BodyDamage::getDrunkReductionValue() {
  // TODO: Implement getDrunkReductionValue
  return 0;
}

void BodyDamage::setDrunkReductionValue(float _DrunkReductionValue) {
  // TODO: Implement setDrunkReductionValue
}

bool BodyDamage::isIsOnFire() {
  // TODO: Implement isIsOnFire
  return false;
}

void BodyDamage::setIsOnFire(bool _IsOnFire) {
  // TODO: Implement setIsOnFire
}

bool BodyDamage::isBurntToDeath() {
  // TODO: Implement isBurntToDeath
  return false;
}

void BodyDamage::setBurntToDeath(bool _BurntToDeath) {
  // TODO: Implement setBurntToDeath
}

void BodyDamage::setWetness(float _Wetness) {
  // TODO: Implement setWetness
}

float BodyDamage::getCatchACold() {
  // TODO: Implement getCatchACold
  return 0;
}

void BodyDamage::setCatchACold(float _CatchACold) {
  // TODO: Implement setCatchACold
}

bool BodyDamage::isHasACold() {
  // TODO: Implement isHasACold
  return false;
}

void BodyDamage::setHasACold(bool _HasACold) {
  // TODO: Implement setHasACold
}

void BodyDamage::setColdStrength(float _ColdStrength) {
  // TODO: Implement setColdStrength
}

float BodyDamage::getColdProgressionRate() {
  // TODO: Implement getColdProgressionRate
  return 0;
}

void BodyDamage::setColdProgressionRate(float _ColdProgressionRate) {
  // TODO: Implement setColdProgressionRate
}

int BodyDamage::getTimeToSneezeOrCough() {
  // TODO: Implement getTimeToSneezeOrCough
  return 0;
}

void BodyDamage::setTimeToSneezeOrCough(int _TimeToSneezeOrCough) {
  // TODO: Implement setTimeToSneezeOrCough
}

int BodyDamage::getMildColdSneezeTimerMin() {
  // TODO: Implement getMildColdSneezeTimerMin
  return 0;
}

void BodyDamage::setMildColdSneezeTimerMin(int _MildColdSneezeTimerMin) {
  // TODO: Implement setMildColdSneezeTimerMin
}

int BodyDamage::getMildColdSneezeTimerMax() {
  // TODO: Implement getMildColdSneezeTimerMax
  return 0;
}

void BodyDamage::setMildColdSneezeTimerMax(int _MildColdSneezeTimerMax) {
  // TODO: Implement setMildColdSneezeTimerMax
}

int BodyDamage::getColdSneezeTimerMin() {
  // TODO: Implement getColdSneezeTimerMin
  return 0;
}

void BodyDamage::setColdSneezeTimerMin(int _ColdSneezeTimerMin) {
  // TODO: Implement setColdSneezeTimerMin
}

int BodyDamage::getColdSneezeTimerMax() {
  // TODO: Implement getColdSneezeTimerMax
  return 0;
}

void BodyDamage::setColdSneezeTimerMax(int _ColdSneezeTimerMax) {
  // TODO: Implement setColdSneezeTimerMax
}

int BodyDamage::getNastyColdSneezeTimerMin() {
  // TODO: Implement getNastyColdSneezeTimerMin
  return 0;
}

void BodyDamage::setNastyColdSneezeTimerMin(int _NastyColdSneezeTimerMin) {
  // TODO: Implement setNastyColdSneezeTimerMin
}

int BodyDamage::getNastyColdSneezeTimerMax() {
  // TODO: Implement getNastyColdSneezeTimerMax
  return 0;
}

void BodyDamage::setNastyColdSneezeTimerMax(int _NastyColdSneezeTimerMax) {
  // TODO: Implement setNastyColdSneezeTimerMax
}

int BodyDamage::getSneezeCoughActive() {
  // TODO: Implement getSneezeCoughActive
  return 0;
}

void BodyDamage::setSneezeCoughActive(int _SneezeCoughActive) {
  // TODO: Implement setSneezeCoughActive
}

int BodyDamage::getSneezeCoughTime() {
  // TODO: Implement getSneezeCoughTime
  return 0;
}

void BodyDamage::setSneezeCoughTime(int _SneezeCoughTime) {
  // TODO: Implement setSneezeCoughTime
}

int BodyDamage::getSneezeCoughDelay() {
  // TODO: Implement getSneezeCoughDelay
  return 0;
}

void BodyDamage::setSneezeCoughDelay(int _SneezeCoughDelay) {
  // TODO: Implement setSneezeCoughDelay
}

void BodyDamage::setUnhappynessLevel(float _UnhappynessLevel) {
  // TODO: Implement setUnhappynessLevel
}

IsoGameCharacter BodyDamage::getParentChar() {
  // TODO: Implement getParentChar
  return nullptr;
}

void BodyDamage::setParentChar(IsoGameCharacter _ParentChar) {
  // TODO: Implement setParentChar
}

float BodyDamage::getTemperature() {
  // TODO: Implement getTemperature
  return 0;
}

void BodyDamage::setTemperature(float t) {
  // TODO: Implement setTemperature
}

float BodyDamage::getTemperatureChangeTick() {
  // TODO: Implement getTemperatureChangeTick
  return 0;
}

void BodyDamage::setPoisonLevel(float poisonLevel) {
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

void BodyDamage::setFoodSicknessLevel(float foodSicknessLevel) {
  // TODO: Implement setFoodSicknessLevel
}

bool BodyDamage::isReduceFakeInfection() {
  // TODO: Implement isReduceFakeInfection
  return false;
}

void BodyDamage::setReduceFakeInfection(bool _reduceFakeInfection) {
  // TODO: Implement setReduceFakeInfection
}

void BodyDamage::AddRandomDamage() {
  // TODO: Implement AddRandomDamage
}

float BodyDamage::getPainReduction() {
  // TODO: Implement getPainReduction
  return 0;
}

void BodyDamage::setPainReduction(float _painReduction) {
  // TODO: Implement setPainReduction
}

float BodyDamage::getColdReduction() {
  // TODO: Implement getColdReduction
  return 0;
}

void BodyDamage::setColdReduction(float _coldReduction) {
  // TODO: Implement setColdReduction
}

int BodyDamage::getRemotePainLevel() {
  // TODO: Implement getRemotePainLevel
  return 0;
}

void BodyDamage::setRemotePainLevel(int painLevel) {
  // TODO: Implement setRemotePainLevel
}

float BodyDamage::getColdDamageStage() {
  // TODO: Implement getColdDamageStage
  return 0;
}

void BodyDamage::setColdDamageStage(float coldDamageStage) {
  // TODO: Implement setColdDamageStage
}

Thermoregulator BodyDamage::getThermoregulator() {
  // TODO: Implement getThermoregulator
  return nullptr;
}

void BodyDamage::decreaseBodyWetness(float amount) {
  // TODO: Implement decreaseBodyWetness
}

void BodyDamage::increaseBodyWetness(float amount) {
  // TODO: Implement increaseBodyWetness
}

} // namespace BodyDamage
} // namespace characters
} // namespace zombie
