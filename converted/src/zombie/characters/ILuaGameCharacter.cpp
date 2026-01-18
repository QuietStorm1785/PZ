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

void ILuaGameCharacter::setDescriptor(SurvivorDesc descriptor) {
 // TODO: Implement setDescriptor
}

bool ILuaGameCharacter::isRangedWeaponEmpty() {
 // TODO: Implement isRangedWeaponEmpty
 return false;
}

void ILuaGameCharacter::setRangedWeaponEmpty(bool val) {
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

bool ILuaGameCharacter::hasItems(const std::string& type, int count) {
 // TODO: Implement hasItems
 return false;
}

int ILuaGameCharacter::getXpForLevel(int level) {
 // TODO: Implement getXpForLevel
 return 0;
}

bool ILuaGameCharacter::isAsleep() {
 // TODO: Implement isAsleep
 return false;
}

void ILuaGameCharacter::setAsleep(bool Asleep) {
 // TODO: Implement setAsleep
}

int ILuaGameCharacter::getZombieKills() {
 // TODO: Implement getZombieKills
 return 0;
}

void ILuaGameCharacter::setForceWakeUpTime(float ForceWakeUpTime) {
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

void ILuaGameCharacter::setPrimaryHandItem(InventoryItem leftHandItem) {
 // TODO: Implement setPrimaryHandItem
}

InventoryItem ILuaGameCharacter::getSecondaryHandItem() {
 // TODO: Implement getSecondaryHandItem
 return nullptr;
}

void ILuaGameCharacter::setSecondaryHandItem(InventoryItem rightHandItem) {
 // TODO: Implement setSecondaryHandItem
}

bool ILuaGameCharacter::hasEquipped(const std::string& String) {
 // TODO: Implement hasEquipped
 return false;
}

bool ILuaGameCharacter::hasEquippedTag(const std::string& tag) {
 // TODO: Implement hasEquippedTag
 return false;
}

bool ILuaGameCharacter::isHandItem(InventoryItem item) {
 // TODO: Implement isHandItem
 return false;
}

bool ILuaGameCharacter::isPrimaryHandItem(InventoryItem item) {
 // TODO: Implement isPrimaryHandItem
 return false;
}

bool ILuaGameCharacter::isSecondaryHandItem(InventoryItem item) {
 // TODO: Implement isSecondaryHandItem
 return false;
}

bool ILuaGameCharacter::isItemInBothHands(InventoryItem item) {
 // TODO: Implement isItemInBothHands
 return false;
}

bool ILuaGameCharacter::removeFromHands(InventoryItem item) {
 // TODO: Implement removeFromHands
 return false;
}

void ILuaGameCharacter::setSpeakColourInfo(ColorInfo info) {
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

void ILuaGameCharacter::PlayAnim(const std::string& string) {
 // TODO: Implement PlayAnim
}

void ILuaGameCharacter::PlayAnimWithSpeed(const std::string& string, float framesSpeedPerFrame) {
 // TODO: Implement PlayAnimWithSpeed
}

void ILuaGameCharacter::PlayAnimUnlooped(const std::string& string) {
 // TODO: Implement PlayAnimUnlooped
}

void ILuaGameCharacter::StartTimedActionAnim(const std::string& event) {
 // TODO: Implement StartTimedActionAnim
}

void ILuaGameCharacter::StartTimedActionAnim(const std::string& event, const std::string& type) {
 // TODO: Implement StartTimedActionAnim
}

void ILuaGameCharacter::StopTimedActionAnim() {
 // TODO: Implement StopTimedActionAnim
}

void ILuaGameCharacter::StartAction(BaseAction act) {
 // TODO: Implement StartAction
}

void ILuaGameCharacter::StopAllActionQueue() {
 // TODO: Implement StopAllActionQueue
}

int ILuaGameCharacter::getPerkLevel(PerkFactory.Perk perks) {
 // TODO: Implement getPerkLevel
 return 0;
}

void ILuaGameCharacter::setPerkLevelDebug(PerkFactory.Perk perks, int level) {
 // TODO: Implement setPerkLevelDebug
}

void ILuaGameCharacter::LoseLevel(PerkFactory.Perk perk) {
 // TODO: Implement LoseLevel
}

void ILuaGameCharacter::LevelPerk(PerkFactory.Perk perk, bool removePick) {
 // TODO: Implement LevelPerk
}

void ILuaGameCharacter::LevelPerk(PerkFactory.Perk perk) {
 // TODO: Implement LevelPerk
}

void ILuaGameCharacter::ReadLiterature(Literature literature) {
 // TODO: Implement ReadLiterature
}

void ILuaGameCharacter::setDir(IsoDirections directions) {
 // TODO: Implement setDir
}

void ILuaGameCharacter::Callout() {
 // TODO: Implement Callout
}

bool ILuaGameCharacter::IsSpeaking() {
 // TODO: Implement IsSpeaking
 return false;
}

void ILuaGameCharacter::Say(const std::string& line) {
 // TODO: Implement Say
}

void ILuaGameCharacter::Say(const std::string& line, float r, float g, float b, UIFont font, float baseRange, const std::string& customTag) {
 // TODO: Implement Say
}

void ILuaGameCharacter::setHaloNote(const std::string& str) {
 // TODO: Implement setHaloNote
}

void ILuaGameCharacter::setHaloNote(const std::string& str, float dispTime) {
 // TODO: Implement setHaloNote
}

void ILuaGameCharacter::setHaloNote(const std::string& str, int r, int g, int b, float dispTime) {
 // TODO: Implement setHaloNote
}

void ILuaGameCharacter::initSpritePartsEmpty() {
 // TODO: Implement initSpritePartsEmpty
}

bool ILuaGameCharacter::HasTrait(const std::string& trait) {
 // TODO: Implement HasTrait
 return false;
}

void ILuaGameCharacter::changeState(State state) {
 // TODO: Implement changeState
}

bool ILuaGameCharacter::isCurrentState(State state) {
 // TODO: Implement isCurrentState
 return false;
}

State ILuaGameCharacter::getCurrentState() {
 // TODO: Implement getCurrentState
 return nullptr;
}

void ILuaGameCharacter::pathToLocation(int x, int y, int z) {
 // TODO: Implement pathToLocation
}

void ILuaGameCharacter::pathToLocationF(float x, float y, float z) {
 // TODO: Implement pathToLocationF
}

bool ILuaGameCharacter::CanAttack() {
 // TODO: Implement CanAttack
 return false;
}

void ILuaGameCharacter::smashCarWindow(VehiclePart part) {
 // TODO: Implement smashCarWindow
}

void ILuaGameCharacter::smashWindow(IsoWindow w) {
 // TODO: Implement smashWindow
}

void ILuaGameCharacter::openWindow(IsoWindow w) {
 // TODO: Implement openWindow
}

void ILuaGameCharacter::closeWindow(IsoWindow w) {
 // TODO: Implement closeWindow
}

void ILuaGameCharacter::climbThroughWindow(IsoWindow w) {
 // TODO: Implement climbThroughWindow
}

void ILuaGameCharacter::climbThroughWindow(IsoWindow w, int startingFrame) {
 // TODO: Implement climbThroughWindow
}

void ILuaGameCharacter::climbThroughWindowFrame(IsoObject obj) {
 // TODO: Implement climbThroughWindowFrame
}

void ILuaGameCharacter::climbSheetRope() {
 // TODO: Implement climbSheetRope
}

void ILuaGameCharacter::climbDownSheetRope() {
 // TODO: Implement climbDownSheetRope
}

bool ILuaGameCharacter::canClimbSheetRope(IsoGridSquare sq) {
 // TODO: Implement canClimbSheetRope
 return false;
}

bool ILuaGameCharacter::canClimbDownSheetRopeInCurrentSquare() {
 // TODO: Implement canClimbDownSheetRopeInCurrentSquare
 return false;
}

bool ILuaGameCharacter::canClimbDownSheetRope(IsoGridSquare sq) {
 // TODO: Implement canClimbDownSheetRope
 return false;
}

void ILuaGameCharacter::climbThroughWindow(IsoThumpable w) {
 // TODO: Implement climbThroughWindow
}

void ILuaGameCharacter::climbThroughWindow(IsoThumpable w, int startingFrame) {
 // TODO: Implement climbThroughWindow
}

void ILuaGameCharacter::climbOverFence(IsoDirections dir) {
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

void ILuaGameCharacter::setFemale(bool isFemale) {
 // TODO: Implement setFemale
}

bool ILuaGameCharacter::isZombie() {
 // TODO: Implement isZombie
 return false;
}

bool ILuaGameCharacter::isEquipped(InventoryItem item) {
 // TODO: Implement isEquipped
 return false;
}

bool ILuaGameCharacter::isEquippedClothing(InventoryItem item) {
 // TODO: Implement isEquippedClothing
 return false;
}

bool ILuaGameCharacter::isAttachedItem(InventoryItem item) {
 // TODO: Implement isAttachedItem
 return false;
}

void ILuaGameCharacter::faceThisObject(IsoObject object) {
 // TODO: Implement faceThisObject
}

void ILuaGameCharacter::facePosition(int x, int y) {
 // TODO: Implement facePosition
}

void ILuaGameCharacter::faceThisObjectAlt(IsoObject object) {
 // TODO: Implement faceThisObjectAlt
}

int ILuaGameCharacter::getAlreadyReadPages(const std::string& fullType) {
 // TODO: Implement getAlreadyReadPages
 return 0;
}

void ILuaGameCharacter::setAlreadyReadPages(const std::string& fullType, int pages) {
 // TODO: Implement setAlreadyReadPages
}

Safety ILuaGameCharacter::getSafety() {
 // TODO: Implement getSafety
 return nullptr;
}

void ILuaGameCharacter::setSafety(Safety safety) {
 // TODO: Implement setSafety
}

float ILuaGameCharacter::getMeleeDelay() {
 // TODO: Implement getMeleeDelay
 return 0;
}

void ILuaGameCharacter::setMeleeDelay(float delay) {
 // TODO: Implement setMeleeDelay
}

float ILuaGameCharacter::getRecoilDelay() {
 // TODO: Implement getRecoilDelay
 return 0;
}

void ILuaGameCharacter::setRecoilDelay(float recoilDelay) {
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

void ILuaGameCharacter::setGodMod(bool b) {
 // TODO: Implement setGodMod
}

BaseVehicle ILuaGameCharacter::getVehicle() {
 // TODO: Implement getVehicle
 return nullptr;
}

void ILuaGameCharacter::setVehicle(BaseVehicle v) {
 // TODO: Implement setVehicle
}

float ILuaGameCharacter::getInventoryWeight() {
 // TODO: Implement getInventoryWeight
 return 0;
}

bool ILuaGameCharacter::isRecipeKnown(Recipe recipe) {
 // TODO: Implement isRecipeKnown
 return false;
}

bool ILuaGameCharacter::isRecipeKnown(const std::string& name) {
 // TODO: Implement isRecipeKnown
 return false;
}

void ILuaGameCharacter::addKnownMediaLine(const std::string& guid) {
 // TODO: Implement addKnownMediaLine
}

void ILuaGameCharacter::removeKnownMediaLine(const std::string& guid) {
 // TODO: Implement removeKnownMediaLine
}

void ILuaGameCharacter::clearKnownMediaLines() {
 // TODO: Implement clearKnownMediaLines
}

bool ILuaGameCharacter::isKnownMediaLine(const std::string& guid) {
 // TODO: Implement isKnownMediaLine
 return false;
}

long ILuaGameCharacter::playSound(const std::string& file) {
 // TODO: Implement playSound
 return 0;
}

long ILuaGameCharacter::playSoundLocal(const std::string& file) {
 // TODO: Implement playSoundLocal
 return 0;
}

void ILuaGameCharacter::stopOrTriggerSound(long eventInstance) {
 // TODO: Implement stopOrTriggerSound
}

void ILuaGameCharacter::addWorldSoundUnlessInvisible(int radius, int volume, bool bStressHumans) {
 // TODO: Implement addWorldSoundUnlessInvisible
}

bool ILuaGameCharacter::isKnownPoison(InventoryItem item) {
 // TODO: Implement isKnownPoison
 return false;
}

std::string ILuaGameCharacter::getBedType() {
 // TODO: Implement getBedType
 return "";
}

void ILuaGameCharacter::setBedType(const std::string& bedType) {
 // TODO: Implement setBedType
}

void ILuaGameCharacter::setPath2(PolygonalMap2.Path path) {
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

void ILuaGameCharacter::setBed(IsoObject bed) {
 // TODO: Implement setBed
}

bool ILuaGameCharacter::isReading() {
 // TODO: Implement isReading
 return false;
}

void ILuaGameCharacter::setReading(bool isReading) {
 // TODO: Implement setReading
}

float ILuaGameCharacter::getTimeSinceLastSmoke() {
 // TODO: Implement getTimeSinceLastSmoke
 return 0;
}

void ILuaGameCharacter::setTimeSinceLastSmoke(float timeSinceLastSmoke) {
 // TODO: Implement setTimeSinceLastSmoke
}

bool ILuaGameCharacter::isInvisible() {
 // TODO: Implement isInvisible
 return false;
}

void ILuaGameCharacter::setInvisible(bool b) {
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

void ILuaGameCharacter::setUnlimitedCarry(bool unlimitedCarry) {
 // TODO: Implement setUnlimitedCarry
}

bool ILuaGameCharacter::isBuildCheat() {
 // TODO: Implement isBuildCheat
 return false;
}

void ILuaGameCharacter::setBuildCheat(bool buildCheat) {
 // TODO: Implement setBuildCheat
}

bool ILuaGameCharacter::isFarmingCheat() {
 // TODO: Implement isFarmingCheat
 return false;
}

void ILuaGameCharacter::setFarmingCheat(bool b) {
 // TODO: Implement setFarmingCheat
}

bool ILuaGameCharacter::isHealthCheat() {
 // TODO: Implement isHealthCheat
 return false;
}

void ILuaGameCharacter::setHealthCheat(bool healthCheat) {
 // TODO: Implement setHealthCheat
}

bool ILuaGameCharacter::isMechanicsCheat() {
 // TODO: Implement isMechanicsCheat
 return false;
}

void ILuaGameCharacter::setMechanicsCheat(bool mechanicsCheat) {
 // TODO: Implement setMechanicsCheat
}

bool ILuaGameCharacter::isMovablesCheat() {
 // TODO: Implement isMovablesCheat
 return false;
}

void ILuaGameCharacter::setMovablesCheat(bool b) {
 // TODO: Implement setMovablesCheat
}

bool ILuaGameCharacter::isTimedActionInstantCheat() {
 // TODO: Implement isTimedActionInstantCheat
 return false;
}

void ILuaGameCharacter::setTimedActionInstantCheat(bool b) {
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

void ILuaGameCharacter::setShowAdminTag(bool showAdminTag) {
 // TODO: Implement setShowAdminTag
}

void ILuaGameCharacter::reportEvent(const std::string& name) {
 // TODO: Implement reportEvent
}

AnimatorDebugMonitor ILuaGameCharacter::getDebugMonitor() {
 // TODO: Implement getDebugMonitor
 return nullptr;
}

void ILuaGameCharacter::setDebugMonitor(AnimatorDebugMonitor monitor) {
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
