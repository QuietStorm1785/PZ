#include <queue>
#include <string>
#include "zombie/characters/ILuaGameCharacter.h"

namespace zombie {
namespace characters {

std::string ILuaGameCharacter::getFullName() {
    // TODO: Implement getFullName
    return "";
}

SurvivorDesc ILuaGameCharacter::getDescriptor() {
    // TODO: Implement getDescriptor
    return nullptr;
}

void ILuaGameCharacter::setDescriptor(SurvivorDesc var1) {
    // TODO: Implement setDescriptor
}

bool ILuaGameCharacter::isRangedWeaponEmpty() {
    // TODO: Implement isRangedWeaponEmpty
    return false;
}

void ILuaGameCharacter::setRangedWeaponEmpty(bool var1) {
    // TODO: Implement setRangedWeaponEmpty
}

BaseVisual ILuaGameCharacter::getVisual() {
    // TODO: Implement getVisual
    return nullptr;
}

BaseCharacterSoundEmitter ILuaGameCharacter::getEmitter() {
    // TODO: Implement getEmitter
    return nullptr;
}

void ILuaGameCharacter::resetModel() {
    // TODO: Implement resetModel
}

void ILuaGameCharacter::resetModelNextFrame() {
    // TODO: Implement resetModelNextFrame
}

IsoSpriteInstance ILuaGameCharacter::getSpriteDef() {
    // TODO: Implement getSpriteDef
    return nullptr;
}

bool ILuaGameCharacter::hasItems(const std::string& var1, int var2) {
    // TODO: Implement hasItems
    return false;
}

int ILuaGameCharacter::getXpForLevel(int var1) {
    // TODO: Implement getXpForLevel
    return 0;
}

XP ILuaGameCharacter::getXp() {
    // TODO: Implement getXp
    return nullptr;
}

bool ILuaGameCharacter::isAsleep() {
    // TODO: Implement isAsleep
    return false;
}

void ILuaGameCharacter::setAsleep(bool var1) {
    // TODO: Implement setAsleep
}

int ILuaGameCharacter::getZombieKills() {
    // TODO: Implement getZombieKills
    return 0;
}

void ILuaGameCharacter::setForceWakeUpTime(float var1) {
    // TODO: Implement setForceWakeUpTime
}

ItemContainer ILuaGameCharacter::getInventory() {
    // TODO: Implement getInventory
    return nullptr;
}

InventoryItem ILuaGameCharacter::getPrimaryHandItem() {
    // TODO: Implement getPrimaryHandItem
    return nullptr;
}

void ILuaGameCharacter::setPrimaryHandItem(InventoryItem var1) {
    // TODO: Implement setPrimaryHandItem
}

InventoryItem ILuaGameCharacter::getSecondaryHandItem() {
    // TODO: Implement getSecondaryHandItem
    return nullptr;
}

void ILuaGameCharacter::setSecondaryHandItem(InventoryItem var1) {
    // TODO: Implement setSecondaryHandItem
}

bool ILuaGameCharacter::hasEquipped(const std::string& var1) {
    // TODO: Implement hasEquipped
    return false;
}

bool ILuaGameCharacter::hasEquippedTag(const std::string& var1) {
    // TODO: Implement hasEquippedTag
    return false;
}

bool ILuaGameCharacter::isHandItem(InventoryItem var1) {
    // TODO: Implement isHandItem
    return false;
}

bool ILuaGameCharacter::isPrimaryHandItem(InventoryItem var1) {
    // TODO: Implement isPrimaryHandItem
    return false;
}

bool ILuaGameCharacter::isSecondaryHandItem(InventoryItem var1) {
    // TODO: Implement isSecondaryHandItem
    return false;
}

bool ILuaGameCharacter::isItemInBothHands(InventoryItem var1) {
    // TODO: Implement isItemInBothHands
    return false;
}

bool ILuaGameCharacter::removeFromHands(InventoryItem var1) {
    // TODO: Implement removeFromHands
    return false;
}

void ILuaGameCharacter::setSpeakColourInfo(ColorInfo var1) {
    // TODO: Implement setSpeakColourInfo
}

bool ILuaGameCharacter::isSpeaking() {
    // TODO: Implement isSpeaking
    return false;
}

Moodles ILuaGameCharacter::getMoodles() {
    // TODO: Implement getMoodles
    return nullptr;
}

Stats ILuaGameCharacter::getStats() {
    // TODO: Implement getStats
    return nullptr;
}

TraitCollection ILuaGameCharacter::getTraits() {
    // TODO: Implement getTraits
    return nullptr;
}

int ILuaGameCharacter::getMaxWeight() {
    // TODO: Implement getMaxWeight
    return 0;
}

void ILuaGameCharacter::PlayAnim(const std::string& var1) {
    // TODO: Implement PlayAnim
}

void ILuaGameCharacter::PlayAnimWithSpeed(const std::string& var1, float var2) {
    // TODO: Implement PlayAnimWithSpeed
}

void ILuaGameCharacter::PlayAnimUnlooped(const std::string& var1) {
    // TODO: Implement PlayAnimUnlooped
}

void ILuaGameCharacter::StartTimedActionAnim(const std::string& var1) {
    // TODO: Implement StartTimedActionAnim
}

void ILuaGameCharacter::StartTimedActionAnim(const std::string& var1, const std::string& var2) {
    // TODO: Implement StartTimedActionAnim
}

void ILuaGameCharacter::StopTimedActionAnim() {
    // TODO: Implement StopTimedActionAnim
}

void ILuaGameCharacter::StartAction(BaseAction var1) {
    // TODO: Implement StartAction
}

void ILuaGameCharacter::StopAllActionQueue() {
    // TODO: Implement StopAllActionQueue
}

int ILuaGameCharacter::getPerkLevel(Perk var1) {
    // TODO: Implement getPerkLevel
    return 0;
}

PerkInfo ILuaGameCharacter::getPerkInfo(Perk var1) {
    // TODO: Implement getPerkInfo
    return nullptr;
}

void ILuaGameCharacter::setPerkLevelDebug(Perk var1, int var2) {
    // TODO: Implement setPerkLevelDebug
}

void ILuaGameCharacter::LoseLevel(Perk var1) {
    // TODO: Implement LoseLevel
}

void ILuaGameCharacter::LevelPerk(Perk var1, bool var2) {
    // TODO: Implement LevelPerk
}

void ILuaGameCharacter::LevelPerk(Perk var1) {
    // TODO: Implement LevelPerk
}

void ILuaGameCharacter::ReadLiterature(Literature var1) {
    // TODO: Implement ReadLiterature
}

void ILuaGameCharacter::setDir(IsoDirections var1) {
    // TODO: Implement setDir
}

void ILuaGameCharacter::Callout() {
    // TODO: Implement Callout
}

bool ILuaGameCharacter::IsSpeaking() {
    // TODO: Implement IsSpeaking
    return false;
}

void ILuaGameCharacter::Say(const std::string& var1) {
    // TODO: Implement Say
}

void ILuaGameCharacter::Say(const std::string& var1, float var2, float var3, float var4, UIFont var5, float var6, const std::string& var7) {
    // TODO: Implement Say
}

void ILuaGameCharacter::setHaloNote(const std::string& var1) {
    // TODO: Implement setHaloNote
}

void ILuaGameCharacter::setHaloNote(const std::string& var1, float var2) {
    // TODO: Implement setHaloNote
}

void ILuaGameCharacter::setHaloNote(const std::string& var1, int var2, int var3, int var4, float var5) {
    // TODO: Implement setHaloNote
}

void ILuaGameCharacter::initSpritePartsEmpty() {
    // TODO: Implement initSpritePartsEmpty
}

bool ILuaGameCharacter::HasTrait(const std::string& var1) {
    // TODO: Implement HasTrait
    return false;
}

void ILuaGameCharacter::changeState(State var1) {
    // TODO: Implement changeState
}

bool ILuaGameCharacter::isCurrentState(State var1) {
    // TODO: Implement isCurrentState
    return false;
}

State ILuaGameCharacter::getCurrentState() {
    // TODO: Implement getCurrentState
    return nullptr;
}

void ILuaGameCharacter::pathToLocation(int var1, int var2, int var3) {
    // TODO: Implement pathToLocation
}

void ILuaGameCharacter::pathToLocationF(float var1, float var2, float var3) {
    // TODO: Implement pathToLocationF
}

bool ILuaGameCharacter::CanAttack() {
    // TODO: Implement CanAttack
    return false;
}

void ILuaGameCharacter::smashCarWindow(VehiclePart var1) {
    // TODO: Implement smashCarWindow
}

void ILuaGameCharacter::smashWindow(IsoWindow var1) {
    // TODO: Implement smashWindow
}

void ILuaGameCharacter::openWindow(IsoWindow var1) {
    // TODO: Implement openWindow
}

void ILuaGameCharacter::closeWindow(IsoWindow var1) {
    // TODO: Implement closeWindow
}

void ILuaGameCharacter::climbThroughWindow(IsoWindow var1) {
    // TODO: Implement climbThroughWindow
}

void ILuaGameCharacter::climbThroughWindow(IsoWindow var1, int var2) {
    // TODO: Implement climbThroughWindow
}

void ILuaGameCharacter::climbThroughWindowFrame(IsoObject var1) {
    // TODO: Implement climbThroughWindowFrame
}

void ILuaGameCharacter::climbSheetRope() {
    // TODO: Implement climbSheetRope
}

void ILuaGameCharacter::climbDownSheetRope() {
    // TODO: Implement climbDownSheetRope
}

bool ILuaGameCharacter::canClimbSheetRope(IsoGridSquare var1) {
    // TODO: Implement canClimbSheetRope
    return false;
}

bool ILuaGameCharacter::canClimbDownSheetRopeInCurrentSquare() {
    // TODO: Implement canClimbDownSheetRopeInCurrentSquare
    return false;
}

bool ILuaGameCharacter::canClimbDownSheetRope(IsoGridSquare var1) {
    // TODO: Implement canClimbDownSheetRope
    return false;
}

void ILuaGameCharacter::climbThroughWindow(IsoThumpable var1) {
    // TODO: Implement climbThroughWindow
}

void ILuaGameCharacter::climbThroughWindow(IsoThumpable var1, int var2) {
    // TODO: Implement climbThroughWindow
}

void ILuaGameCharacter::climbOverFence(IsoDirections var1) {
    // TODO: Implement climbOverFence
}

bool ILuaGameCharacter::isAboveTopOfStairs() {
    // TODO: Implement isAboveTopOfStairs
    return false;
}

double ILuaGameCharacter::getHoursSurvived() {
    // TODO: Implement getHoursSurvived
    return 0;
}

bool ILuaGameCharacter::isOutside() {
    // TODO: Implement isOutside
    return false;
}

bool ILuaGameCharacter::isFemale() {
    // TODO: Implement isFemale
    return false;
}

void ILuaGameCharacter::setFemale(bool var1) {
    // TODO: Implement setFemale
}

bool ILuaGameCharacter::isZombie() {
    // TODO: Implement isZombie
    return false;
}

bool ILuaGameCharacter::isEquipped(InventoryItem var1) {
    // TODO: Implement isEquipped
    return false;
}

bool ILuaGameCharacter::isEquippedClothing(InventoryItem var1) {
    // TODO: Implement isEquippedClothing
    return false;
}

bool ILuaGameCharacter::isAttachedItem(InventoryItem var1) {
    // TODO: Implement isAttachedItem
    return false;
}

void ILuaGameCharacter::faceThisObject(IsoObject var1) {
    // TODO: Implement faceThisObject
}

void ILuaGameCharacter::facePosition(int var1, int var2) {
    // TODO: Implement facePosition
}

void ILuaGameCharacter::faceThisObjectAlt(IsoObject var1) {
    // TODO: Implement faceThisObjectAlt
}

int ILuaGameCharacter::getAlreadyReadPages(const std::string& var1) {
    // TODO: Implement getAlreadyReadPages
    return 0;
}

void ILuaGameCharacter::setAlreadyReadPages(const std::string& var1, int var2) {
    // TODO: Implement setAlreadyReadPages
}

Safety ILuaGameCharacter::getSafety() {
    // TODO: Implement getSafety
    return nullptr;
}

void ILuaGameCharacter::setSafety(Safety var1) {
    // TODO: Implement setSafety
}

float ILuaGameCharacter::getMeleeDelay() {
    // TODO: Implement getMeleeDelay
    return 0;
}

void ILuaGameCharacter::setMeleeDelay(float var1) {
    // TODO: Implement setMeleeDelay
}

float ILuaGameCharacter::getRecoilDelay() {
    // TODO: Implement getRecoilDelay
    return 0;
}

void ILuaGameCharacter::setRecoilDelay(float var1) {
    // TODO: Implement setRecoilDelay
}

int ILuaGameCharacter::getMaintenanceMod() {
    // TODO: Implement getMaintenanceMod
    return 0;
}

float ILuaGameCharacter::getHammerSoundMod() {
    // TODO: Implement getHammerSoundMod
    return 0;
}

float ILuaGameCharacter::getWeldingSoundMod() {
    // TODO: Implement getWeldingSoundMod
    return 0;
}

bool ILuaGameCharacter::isGodMod() {
    // TODO: Implement isGodMod
    return false;
}

void ILuaGameCharacter::setGodMod(bool var1) {
    // TODO: Implement setGodMod
}

BaseVehicle ILuaGameCharacter::getVehicle() {
    // TODO: Implement getVehicle
    return nullptr;
}

void ILuaGameCharacter::setVehicle(BaseVehicle var1) {
    // TODO: Implement setVehicle
}

float ILuaGameCharacter::getInventoryWeight() {
    // TODO: Implement getInventoryWeight
    return 0;
}

bool ILuaGameCharacter::isRecipeKnown(Recipe var1) {
    // TODO: Implement isRecipeKnown
    return false;
}

bool ILuaGameCharacter::isRecipeKnown(const std::string& var1) {
    // TODO: Implement isRecipeKnown
    return false;
}

void ILuaGameCharacter::addKnownMediaLine(const std::string& var1) {
    // TODO: Implement addKnownMediaLine
}

void ILuaGameCharacter::removeKnownMediaLine(const std::string& var1) {
    // TODO: Implement removeKnownMediaLine
}

void ILuaGameCharacter::clearKnownMediaLines() {
    // TODO: Implement clearKnownMediaLines
}

bool ILuaGameCharacter::isKnownMediaLine(const std::string& var1) {
    // TODO: Implement isKnownMediaLine
    return false;
}

long ILuaGameCharacter::playSound(const std::string& var1) {
    // TODO: Implement playSound
    return 0;
}

long ILuaGameCharacter::playSoundLocal(const std::string& var1) {
    // TODO: Implement playSoundLocal
    return 0;
}

void ILuaGameCharacter::stopOrTriggerSound(long var1) {
    // TODO: Implement stopOrTriggerSound
}

void ILuaGameCharacter::addWorldSoundUnlessInvisible(int var1, int var2, bool var3) {
    // TODO: Implement addWorldSoundUnlessInvisible
}

bool ILuaGameCharacter::isKnownPoison(InventoryItem var1) {
    // TODO: Implement isKnownPoison
    return false;
}

std::string ILuaGameCharacter::getBedType() {
    // TODO: Implement getBedType
    return "";
}

void ILuaGameCharacter::setBedType(const std::string& var1) {
    // TODO: Implement setBedType
}

Path ILuaGameCharacter::getPath2() {
    // TODO: Implement getPath2
    return nullptr;
}

void ILuaGameCharacter::setPath2(Path var1) {
    // TODO: Implement setPath2
}

PathFindBehavior2 ILuaGameCharacter::getPathFindBehavior2() {
    // TODO: Implement getPathFindBehavior2
    return nullptr;
}

IsoObject ILuaGameCharacter::getBed() {
    // TODO: Implement getBed
    return nullptr;
}

void ILuaGameCharacter::setBed(IsoObject var1) {
    // TODO: Implement setBed
}

bool ILuaGameCharacter::isReading() {
    // TODO: Implement isReading
    return false;
}

void ILuaGameCharacter::setReading(bool var1) {
    // TODO: Implement setReading
}

float ILuaGameCharacter::getTimeSinceLastSmoke() {
    // TODO: Implement getTimeSinceLastSmoke
    return 0;
}

void ILuaGameCharacter::setTimeSinceLastSmoke(float var1) {
    // TODO: Implement setTimeSinceLastSmoke
}

bool ILuaGameCharacter::isInvisible() {
    // TODO: Implement isInvisible
    return false;
}

void ILuaGameCharacter::setInvisible(bool var1) {
    // TODO: Implement setInvisible
}

bool ILuaGameCharacter::isDriving() {
    // TODO: Implement isDriving
    return false;
}

bool ILuaGameCharacter::isInARoom() {
    // TODO: Implement isInARoom
    return false;
}

bool ILuaGameCharacter::isUnlimitedCarry() {
    // TODO: Implement isUnlimitedCarry
    return false;
}

void ILuaGameCharacter::setUnlimitedCarry(bool var1) {
    // TODO: Implement setUnlimitedCarry
}

bool ILuaGameCharacter::isBuildCheat() {
    // TODO: Implement isBuildCheat
    return false;
}

void ILuaGameCharacter::setBuildCheat(bool var1) {
    // TODO: Implement setBuildCheat
}

bool ILuaGameCharacter::isFarmingCheat() {
    // TODO: Implement isFarmingCheat
    return false;
}

void ILuaGameCharacter::setFarmingCheat(bool var1) {
    // TODO: Implement setFarmingCheat
}

bool ILuaGameCharacter::isHealthCheat() {
    // TODO: Implement isHealthCheat
    return false;
}

void ILuaGameCharacter::setHealthCheat(bool var1) {
    // TODO: Implement setHealthCheat
}

bool ILuaGameCharacter::isMechanicsCheat() {
    // TODO: Implement isMechanicsCheat
    return false;
}

void ILuaGameCharacter::setMechanicsCheat(bool var1) {
    // TODO: Implement setMechanicsCheat
}

bool ILuaGameCharacter::isMovablesCheat() {
    // TODO: Implement isMovablesCheat
    return false;
}

void ILuaGameCharacter::setMovablesCheat(bool var1) {
    // TODO: Implement setMovablesCheat
}

bool ILuaGameCharacter::isTimedActionInstantCheat() {
    // TODO: Implement isTimedActionInstantCheat
    return false;
}

void ILuaGameCharacter::setTimedActionInstantCheat(bool var1) {
    // TODO: Implement setTimedActionInstantCheat
}

bool ILuaGameCharacter::isTimedActionInstant() {
    // TODO: Implement isTimedActionInstant
    return false;
}

bool ILuaGameCharacter::isShowAdminTag() {
    // TODO: Implement isShowAdminTag
    return false;
}

void ILuaGameCharacter::setShowAdminTag(bool var1) {
    // TODO: Implement setShowAdminTag
}

void ILuaGameCharacter::reportEvent(const std::string& var1) {
    // TODO: Implement reportEvent
}

AnimatorDebugMonitor ILuaGameCharacter::getDebugMonitor() {
    // TODO: Implement getDebugMonitor
    return nullptr;
}

void ILuaGameCharacter::setDebugMonitor(AnimatorDebugMonitor var1) {
    // TODO: Implement setDebugMonitor
}

bool ILuaGameCharacter::isAiming() {
    // TODO: Implement isAiming
    return false;
}

void ILuaGameCharacter::resetBeardGrowingTime() {
    // TODO: Implement resetBeardGrowingTime
}

void ILuaGameCharacter::resetHairGrowingTime() {
    // TODO: Implement resetHairGrowingTime
}

} // namespace characters
} // namespace zombie
