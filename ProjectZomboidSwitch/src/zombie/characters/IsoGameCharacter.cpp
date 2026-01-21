#include <queue>
#include <stack>
#include <string>
#include <vector>
#include "zombie/characters/IsoGameCharacter.h"

namespace zombie {
namespace characters {

public IsoGameCharacter::IsoGameCharacter(IsoCell var1, float var2, float var3, float var4) {
    // TODO: Implement IsoGameCharacter
    return nullptr;
}

void IsoGameCharacter::registerVariableCallbacks() {
    // TODO: Implement registerVariableCallbacks
}

void IsoGameCharacter::updateRecoilVar() {
    // TODO: Implement updateRecoilVar
}

void IsoGameCharacter::registerDebugGameVariables() {
    // TODO: Implement registerDebugGameVariables
}

void IsoGameCharacter::dbgRegisterAnimTrackVariable(int var1, int var2) {
    // TODO: Implement dbgRegisterAnimTrackVariable
}

float IsoGameCharacter::getMomentumScalar() {
    // TODO: Implement getMomentumScalar
    return 0;
}

void IsoGameCharacter::setMomentumScalar(float var1) {
    // TODO: Implement setMomentumScalar
}

Vector2 IsoGameCharacter::getDeferredMovement(Vector2 var1) {
    // TODO: Implement getDeferredMovement
    return nullptr;
}

float IsoGameCharacter::getDeferredAngleDelta() {
    // TODO: Implement getDeferredAngleDelta
    return 0;
}

float IsoGameCharacter::getDeferredRotationWeight() {
    // TODO: Implement getDeferredRotationWeight
    return 0;
}

bool IsoGameCharacter::isStrafing() {
    // TODO: Implement isStrafing
    return false;
}

AnimationTrack IsoGameCharacter::dbgGetAnimTrack(int var1, int var2) {
    // TODO: Implement dbgGetAnimTrack
    return nullptr;
}

std::string IsoGameCharacter::dbgGetAnimTrackName(int var1, int var2) {
    // TODO: Implement dbgGetAnimTrackName
    return "";
}

float IsoGameCharacter::dbgGetAnimTrackTime(int var1, int var2) {
    // TODO: Implement dbgGetAnimTrackTime
    return 0;
}

float IsoGameCharacter::dbgGetAnimTrackWeight(int var1, int var2) {
    // TODO: Implement dbgGetAnimTrackWeight
    return 0;
}

float IsoGameCharacter::getTwist() {
    // TODO: Implement getTwist
    return 0;
}

float IsoGameCharacter::getShoulderTwist() {
    // TODO: Implement getShoulderTwist
    return 0;
}

float IsoGameCharacter::getMaxTwist() {
    // TODO: Implement getMaxTwist
    return 0;
}

void IsoGameCharacter::setMaxTwist(float var1) {
    // TODO: Implement setMaxTwist
}

float IsoGameCharacter::getExcessTwist() {
    // TODO: Implement getExcessTwist
    return 0;
}

float IsoGameCharacter::getAbsoluteExcessTwist() {
    // TODO: Implement getAbsoluteExcessTwist
    return 0;
}

float IsoGameCharacter::getAnimAngleTwistDelta() {
    // TODO: Implement getAnimAngleTwistDelta
    return 0;
}

float IsoGameCharacter::getAnimAngleStepDelta() {
    // TODO: Implement getAnimAngleStepDelta
    return 0;
}

float IsoGameCharacter::getTargetTwist() {
    // TODO: Implement getTargetTwist
    return 0;
}

bool IsoGameCharacter::isRangedWeaponEmpty() {
    // TODO: Implement isRangedWeaponEmpty
    return false;
}

void IsoGameCharacter::setRangedWeaponEmpty(bool var1) {
    // TODO: Implement setRangedWeaponEmpty
}

bool IsoGameCharacter::hasFootInjury() {
    // TODO: Implement hasFootInjury
    return false;
}

bool IsoGameCharacter::isInTrees2(bool var1) {
    // TODO: Implement isInTrees2
    return false;
}

bool IsoGameCharacter::isInTreesNoBush() {
    // TODO: Implement isInTreesNoBush
    return false;
}

bool IsoGameCharacter::isInTrees() {
    // TODO: Implement isInTrees
    return false;
}

Vector2 IsoGameCharacter::getTempo() {
    // TODO: Implement getTempo
    return nullptr;
}

ColorInfo IsoGameCharacter::getInf() {
    // TODO: Implement getInf
    return nullptr;
}

GameCharacterAIBrain IsoGameCharacter::getBrain() {
    // TODO: Implement getBrain
    return nullptr;
}

bool IsoGameCharacter::getIsNPC() {
    // TODO: Implement getIsNPC
    return false;
}

void IsoGameCharacter::setIsNPC(bool var1) {
    // TODO: Implement setIsNPC
}

BaseCharacterSoundEmitter IsoGameCharacter::getEmitter() {
    // TODO: Implement getEmitter
    return nullptr;
}

void IsoGameCharacter::updateEmitter() {
    // TODO: Implement updateEmitter
}

void IsoGameCharacter::doDeferredMovement() {
    // TODO: Implement doDeferredMovement
}

ActionContext IsoGameCharacter::getActionContext() {
    // TODO: Implement getActionContext
    return nullptr;
}

std::string IsoGameCharacter::getPreviousActionContextStateName() {
    // TODO: Implement getPreviousActionContextStateName
    return "";
}

std::string IsoGameCharacter::getCurrentActionContextStateName() {
    // TODO: Implement getCurrentActionContextStateName
    return "";
}

bool IsoGameCharacter::hasAnimationPlayer() {
    // TODO: Implement hasAnimationPlayer
    return false;
}

AnimationPlayer IsoGameCharacter::getAnimationPlayer() {
    // TODO: Implement getAnimationPlayer
    return nullptr;
}

void IsoGameCharacter::releaseAnimationPlayer() {
    // TODO: Implement releaseAnimationPlayer
}

void IsoGameCharacter::onAnimPlayerCreated(AnimationPlayer var1) {
    // TODO: Implement onAnimPlayerCreated
}

void IsoGameCharacter::updateAnimationRecorderState() {
    // TODO: Implement updateAnimationRecorderState
}

AdvancedAnimator IsoGameCharacter::getAdvancedAnimator() {
    // TODO: Implement getAdvancedAnimator
    return nullptr;
}

ModelInstance IsoGameCharacter::getModelInstance() {
    // TODO: Implement getModelInstance
    return nullptr;
}

std::string IsoGameCharacter::getCurrentStateName() {
    // TODO: Implement getCurrentStateName
    return "";
}

std::string IsoGameCharacter::getPreviousStateName() {
    // TODO: Implement getPreviousStateName
    return "";
}

std::string IsoGameCharacter::getAnimationDebug() {
    // TODO: Implement getAnimationDebug
    return "";
}

std::string IsoGameCharacter::getTalkerType() {
    // TODO: Implement getTalkerType
    return "";
}

bool IsoGameCharacter::isAnimForecasted() {
    // TODO: Implement isAnimForecasted
    return false;
}

void IsoGameCharacter::setAnimForecasted(int var1) {
    // TODO: Implement setAnimForecasted
}

void IsoGameCharacter::resetModel() {
    // TODO: Implement resetModel
}

void IsoGameCharacter::resetModelNextFrame() {
    // TODO: Implement resetModelNextFrame
}

void IsoGameCharacter::onTrigger_setClothingToXmlTriggerFile(TriggerXmlFile var1) {
    // TODO: Implement onTrigger_setClothingToXmlTriggerFile
}

void IsoGameCharacter::onTrigger_setAnimStateToTriggerFile(AnimStateTriggerXmlFile var1) {
    // TODO: Implement onTrigger_setAnimStateToTriggerFile
}

void IsoGameCharacter::restoreAnimatorStateToActionContext() {
    // TODO: Implement restoreAnimatorStateToActionContext
}

void IsoGameCharacter::clothingItemChanged(const std::string& var1) {
    // TODO: Implement clothingItemChanged
}

void IsoGameCharacter::reloadOutfit() {
    // TODO: Implement reloadOutfit
}

bool IsoGameCharacter::isSceneCulled() {
    // TODO: Implement isSceneCulled
    return false;
}

void IsoGameCharacter::setSceneCulled(bool var1) {
    // TODO: Implement setSceneCulled
}

void IsoGameCharacter::onCullStateChanged(ModelManager var1, bool var2) {
    // TODO: Implement onCullStateChanged
}

void IsoGameCharacter::dressInRandomOutfit() {
    // TODO: Implement dressInRandomOutfit
}

void IsoGameCharacter::dressInNamedOutfit(const std::string& var1) {
    // TODO: Implement dressInNamedOutfit
}

void IsoGameCharacter::dressInPersistentOutfit(const std::string& var1) {
    // TODO: Implement dressInPersistentOutfit
}

void IsoGameCharacter::dressInPersistentOutfitID(int var1) {
    // TODO: Implement dressInPersistentOutfitID
}

std::string IsoGameCharacter::getOutfitName() {
    // TODO: Implement getOutfitName
    return "";
}

void IsoGameCharacter::dressInClothingItem(const std::string& var1) {
    // TODO: Implement dressInClothingItem
}

Outfit IsoGameCharacter::getRandomDefaultOutfit() {
    // TODO: Implement getRandomDefaultOutfit
    return nullptr;
}

ModelInstance IsoGameCharacter::getModel() {
    // TODO: Implement getModel
    return nullptr;
}

bool IsoGameCharacter::hasActiveModel() {
    // TODO: Implement hasActiveModel
    return false;
}

bool IsoGameCharacter::hasItems(const std::string& var1, int var2) {
    // TODO: Implement hasItems
    return false;
}

int IsoGameCharacter::getLevelUpLevels(int var1) {
    // TODO: Implement getLevelUpLevels
    return 0;
}

int IsoGameCharacter::getLevelMaxForXp() {
    // TODO: Implement getLevelMaxForXp
    return 0;
}

int IsoGameCharacter::getXpForLevel(int var1) {
    // TODO: Implement getXpForLevel
    return 0;
}

void IsoGameCharacter::DoDeath(HandWeapon var1, IsoGameCharacter var2) {
    // TODO: Implement DoDeath
}

void IsoGameCharacter::DoDeath(HandWeapon var1, IsoGameCharacter var2, bool var3) {
    // TODO: Implement DoDeath
}

bool IsoGameCharacter::TestIfSeen(int var1) {
    // TODO: Implement TestIfSeen
    return false;
}

void IsoGameCharacter::DoLand() {
    // TODO: Implement DoLand
}

IsoGameCharacter IsoGameCharacter::getFollowingTarget() {
    // TODO: Implement getFollowingTarget
    return nullptr;
}

void IsoGameCharacter::setFollowingTarget(IsoGameCharacter var1) {
    // TODO: Implement setFollowingTarget
}

float IsoGameCharacter::getDangerLevels() {
    // TODO: Implement getDangerLevels
    return 0;
}

void IsoGameCharacter::setDangerLevels(float var1) {
    // TODO: Implement setDangerLevels
}

float IsoGameCharacter::getLeaveBodyTimedown() {
    // TODO: Implement getLeaveBodyTimedown
    return 0;
}

void IsoGameCharacter::setLeaveBodyTimedown(float var1) {
    // TODO: Implement setLeaveBodyTimedown
}

bool IsoGameCharacter::isAllowConversation() {
    // TODO: Implement isAllowConversation
    return false;
}

void IsoGameCharacter::setAllowConversation(bool var1) {
    // TODO: Implement setAllowConversation
}

float IsoGameCharacter::getReanimateTimer() {
    // TODO: Implement getReanimateTimer
    return 0;
}

void IsoGameCharacter::setReanimateTimer(float var1) {
    // TODO: Implement setReanimateTimer
}

int IsoGameCharacter::getReanimAnimFrame() {
    // TODO: Implement getReanimAnimFrame
    return 0;
}

void IsoGameCharacter::setReanimAnimFrame(int var1) {
    // TODO: Implement setReanimAnimFrame
}

int IsoGameCharacter::getReanimAnimDelay() {
    // TODO: Implement getReanimAnimDelay
    return 0;
}

void IsoGameCharacter::setReanimAnimDelay(int var1) {
    // TODO: Implement setReanimAnimDelay
}

bool IsoGameCharacter::isReanim() {
    // TODO: Implement isReanim
    return false;
}

void IsoGameCharacter::setReanim(bool var1) {
    // TODO: Implement setReanim
}

bool IsoGameCharacter::isVisibleToNPCs() {
    // TODO: Implement isVisibleToNPCs
    return false;
}

void IsoGameCharacter::setVisibleToNPCs(bool var1) {
    // TODO: Implement setVisibleToNPCs
}

int IsoGameCharacter::getDieCount() {
    // TODO: Implement getDieCount
    return 0;
}

void IsoGameCharacter::setDieCount(int var1) {
    // TODO: Implement setDieCount
}

float IsoGameCharacter::getLlx() {
    // TODO: Implement getLlx
    return 0;
}

void IsoGameCharacter::setLlx(float var1) {
    // TODO: Implement setLlx
}

float IsoGameCharacter::getLly() {
    // TODO: Implement getLly
    return 0;
}

void IsoGameCharacter::setLly(float var1) {
    // TODO: Implement setLly
}

float IsoGameCharacter::getLlz() {
    // TODO: Implement getLlz
    return 0;
}

void IsoGameCharacter::setLlz(float var1) {
    // TODO: Implement setLlz
}

int IsoGameCharacter::getRemoteID() {
    // TODO: Implement getRemoteID
    return 0;
}

void IsoGameCharacter::setRemoteID(int var1) {
    // TODO: Implement setRemoteID
}

int IsoGameCharacter::getNumSurvivorsInVicinity() {
    // TODO: Implement getNumSurvivorsInVicinity
    return 0;
}

void IsoGameCharacter::setNumSurvivorsInVicinity(int var1) {
    // TODO: Implement setNumSurvivorsInVicinity
}

float IsoGameCharacter::getLevelUpMultiplier() {
    // TODO: Implement getLevelUpMultiplier
    return 0;
}

void IsoGameCharacter::setLevelUpMultiplier(float var1) {
    // TODO: Implement setLevelUpMultiplier
}

XP IsoGameCharacter::getXp() {
    // TODO: Implement getXp
    return nullptr;
}

void IsoGameCharacter::setXp(XP var1) {
    // TODO: Implement setXp
}

int IsoGameCharacter::getLastLocalEnemies() {
    // TODO: Implement getLastLocalEnemies
    return 0;
}

void IsoGameCharacter::setLastLocalEnemies(int var1) {
    // TODO: Implement setLastLocalEnemies
}

IsoGameCharacter IsoGameCharacter::getAttackedBy() {
    // TODO: Implement getAttackedBy
    return nullptr;
}

void IsoGameCharacter::setAttackedBy(IsoGameCharacter var1) {
    // TODO: Implement setAttackedBy
}

bool IsoGameCharacter::isIgnoreStaggerBack() {
    // TODO: Implement isIgnoreStaggerBack
    return false;
}

void IsoGameCharacter::setIgnoreStaggerBack(bool var1) {
    // TODO: Implement setIgnoreStaggerBack
}

bool IsoGameCharacter::isAttackWasSuperAttack() {
    // TODO: Implement isAttackWasSuperAttack
    return false;
}

void IsoGameCharacter::setAttackWasSuperAttack(bool var1) {
    // TODO: Implement setAttackWasSuperAttack
}

int IsoGameCharacter::getTimeThumping() {
    // TODO: Implement getTimeThumping
    return 0;
}

void IsoGameCharacter::setTimeThumping(int var1) {
    // TODO: Implement setTimeThumping
}

int IsoGameCharacter::getPatienceMax() {
    // TODO: Implement getPatienceMax
    return 0;
}

void IsoGameCharacter::setPatienceMax(int var1) {
    // TODO: Implement setPatienceMax
}

int IsoGameCharacter::getPatienceMin() {
    // TODO: Implement getPatienceMin
    return 0;
}

void IsoGameCharacter::setPatienceMin(int var1) {
    // TODO: Implement setPatienceMin
}

int IsoGameCharacter::getPatience() {
    // TODO: Implement getPatience
    return 0;
}

void IsoGameCharacter::setPatience(int var1) {
    // TODO: Implement setPatience
}

bool IsoGameCharacter::hasTimedActions() {
    // TODO: Implement hasTimedActions
    return false;
}

Vector2 IsoGameCharacter::getForwardDirection() {
    // TODO: Implement getForwardDirection
    return nullptr;
}

void IsoGameCharacter::setForwardDirection(Vector2 var1) {
    // TODO: Implement setForwardDirection
}

void IsoGameCharacter::setForwardDirection(float var1, float var2) {
    // TODO: Implement setForwardDirection
}

void IsoGameCharacter::zeroForwardDirectionX() {
    // TODO: Implement zeroForwardDirectionX
}

void IsoGameCharacter::zeroForwardDirectionY() {
    // TODO: Implement zeroForwardDirectionY
}

float IsoGameCharacter::getDirectionAngle() {
    // TODO: Implement getDirectionAngle
    return 0;
}

void IsoGameCharacter::setDirectionAngle(float var1) {
    // TODO: Implement setDirectionAngle
}

float IsoGameCharacter::getAnimAngle() {
    // TODO: Implement getAnimAngle
    return 0;
}

float IsoGameCharacter::getAnimAngleRadians() {
    // TODO: Implement getAnimAngleRadians
    return 0;
}

Vector2 IsoGameCharacter::getAnimVector(Vector2 var1) {
    // TODO: Implement getAnimVector
    return nullptr;
}

float IsoGameCharacter::getLookAngleRadians() {
    // TODO: Implement getLookAngleRadians
    return 0;
}

Vector2 IsoGameCharacter::getLookVector(Vector2 var1) {
    // TODO: Implement getLookVector
    return nullptr;
}

float IsoGameCharacter::getDotWithForwardDirection(Vector3 var1) {
    // TODO: Implement getDotWithForwardDirection
    return 0;
}

float IsoGameCharacter::getDotWithForwardDirection(float var1, float var2) {
    // TODO: Implement getDotWithForwardDirection
    return 0;
}

bool IsoGameCharacter::isAsleep() {
    // TODO: Implement isAsleep
    return false;
}

void IsoGameCharacter::setAsleep(bool var1) {
    // TODO: Implement setAsleep
}

int IsoGameCharacter::getZombieKills() {
    // TODO: Implement getZombieKills
    return 0;
}

void IsoGameCharacter::setZombieKills(int var1) {
    // TODO: Implement setZombieKills
}

int IsoGameCharacter::getLastZombieKills() {
    // TODO: Implement getLastZombieKills
    return 0;
}

void IsoGameCharacter::setLastZombieKills(int var1) {
    // TODO: Implement setLastZombieKills
}

bool IsoGameCharacter::isSuperAttack() {
    // TODO: Implement isSuperAttack
    return false;
}

void IsoGameCharacter::setSuperAttack(bool var1) {
    // TODO: Implement setSuperAttack
}

float IsoGameCharacter::getForceWakeUpTime() {
    // TODO: Implement getForceWakeUpTime
    return 0;
}

void IsoGameCharacter::setForceWakeUpTime(float var1) {
    // TODO: Implement setForceWakeUpTime
}

void IsoGameCharacter::forceAwake() {
    // TODO: Implement forceAwake
}

BodyDamage IsoGameCharacter::getBodyDamage() {
    // TODO: Implement getBodyDamage
    return nullptr;
}

BodyDamage IsoGameCharacter::getBodyDamageRemote() {
    // TODO: Implement getBodyDamageRemote
    return nullptr;
}

void IsoGameCharacter::resetBodyDamageRemote() {
    // TODO: Implement resetBodyDamageRemote
}

State IsoGameCharacter::getDefaultState() {
    // TODO: Implement getDefaultState
    return nullptr;
}

void IsoGameCharacter::setDefaultState(State var1) {
    // TODO: Implement setDefaultState
}

SurvivorDesc IsoGameCharacter::getDescriptor() {
    // TODO: Implement getDescriptor
    return nullptr;
}

void IsoGameCharacter::setDescriptor(SurvivorDesc var1) {
    // TODO: Implement setDescriptor
}

std::string IsoGameCharacter::getFullName() {
    // TODO: Implement getFullName
    return "";
}

BaseVisual IsoGameCharacter::getVisual() {
    // TODO: Implement getVisual
    return nullptr;
}

ItemVisuals IsoGameCharacter::getItemVisuals() {
    // TODO: Implement getItemVisuals
    return nullptr;
}

void IsoGameCharacter::getItemVisuals(ItemVisuals var1) {
    // TODO: Implement getItemVisuals
}

bool IsoGameCharacter::isUsingWornItems() {
    // TODO: Implement isUsingWornItems
    return false;
}

AStarPathFinderResult IsoGameCharacter::getFinder() {
    // TODO: Implement getFinder
    return nullptr;
}

float IsoGameCharacter::getFireKillRate() {
    // TODO: Implement getFireKillRate
    return 0;
}

void IsoGameCharacter::setFireKillRate(float var1) {
    // TODO: Implement setFireKillRate
}

int IsoGameCharacter::getFireSpreadProbability() {
    // TODO: Implement getFireSpreadProbability
    return 0;
}

void IsoGameCharacter::setFireSpreadProbability(int var1) {
    // TODO: Implement setFireSpreadProbability
}

float IsoGameCharacter::getHealth() {
    // TODO: Implement getHealth
    return 0;
}

void IsoGameCharacter::setHealth(float var1) {
    // TODO: Implement setHealth
}

bool IsoGameCharacter::isOnDeathDone() {
    // TODO: Implement isOnDeathDone
    return false;
}

void IsoGameCharacter::setOnDeathDone(bool var1) {
    // TODO: Implement setOnDeathDone
}

bool IsoGameCharacter::isOnKillDone() {
    // TODO: Implement isOnKillDone
    return false;
}

void IsoGameCharacter::setOnKillDone(bool var1) {
    // TODO: Implement setOnKillDone
}

bool IsoGameCharacter::isDeathDragDown() {
    // TODO: Implement isDeathDragDown
    return false;
}

void IsoGameCharacter::setDeathDragDown(bool var1) {
    // TODO: Implement setDeathDragDown
}

bool IsoGameCharacter::isPlayingDeathSound() {
    // TODO: Implement isPlayingDeathSound
    return false;
}

void IsoGameCharacter::setPlayingDeathSound(bool var1) {
    // TODO: Implement setPlayingDeathSound
}

std::string IsoGameCharacter::getHurtSound() {
    // TODO: Implement getHurtSound
    return "";
}

void IsoGameCharacter::setHurtSound(const std::string& var1) {
    // TODO: Implement setHurtSound
}

bool IsoGameCharacter::isIgnoreMovementForDirection() {
    // TODO: Implement isIgnoreMovementForDirection
    return false;
}

ItemContainer IsoGameCharacter::getInventory() {
    // TODO: Implement getInventory
    return nullptr;
}

void IsoGameCharacter::setInventory(ItemContainer var1) {
    // TODO: Implement setInventory
}

bool IsoGameCharacter::isPrimaryEquipped(const std::string& var1) {
    // TODO: Implement isPrimaryEquipped
    return false;
}

InventoryItem IsoGameCharacter::getPrimaryHandItem() {
    // TODO: Implement getPrimaryHandItem
    return nullptr;
}

void IsoGameCharacter::setPrimaryHandItem(InventoryItem var1) {
    // TODO: Implement setPrimaryHandItem
}

void IsoGameCharacter::setEquipParent(InventoryItem var1, InventoryItem var2) {
    // TODO: Implement setEquipParent
}

void IsoGameCharacter::initWornItems(const std::string& var1) {
    // TODO: Implement initWornItems
}

WornItems IsoGameCharacter::getWornItems() {
    // TODO: Implement getWornItems
    return nullptr;
}

void IsoGameCharacter::setWornItems(WornItems var1) {
    // TODO: Implement setWornItems
}

InventoryItem IsoGameCharacter::getWornItem(const std::string& var1) {
    // TODO: Implement getWornItem
    return nullptr;
}

void IsoGameCharacter::setWornItem(const std::string& var1, InventoryItem var2) {
    // TODO: Implement setWornItem
}

void IsoGameCharacter::setWornItem(const std::string& var1, InventoryItem var2, bool var3) {
    // TODO: Implement setWornItem
}

void IsoGameCharacter::removeWornItem(InventoryItem var1) {
    // TODO: Implement removeWornItem
}

void IsoGameCharacter::removeWornItem(InventoryItem var1, bool var2) {
    // TODO: Implement removeWornItem
}

void IsoGameCharacter::clearWornItems() {
    // TODO: Implement clearWornItems
}

BodyLocationGroup IsoGameCharacter::getBodyLocationGroup() {
    // TODO: Implement getBodyLocationGroup
    return nullptr;
}

void IsoGameCharacter::onWornItemsChanged() {
    // TODO: Implement onWornItemsChanged
}

void IsoGameCharacter::initAttachedItems(const std::string& var1) {
    // TODO: Implement initAttachedItems
}

AttachedItems IsoGameCharacter::getAttachedItems() {
    // TODO: Implement getAttachedItems
    return nullptr;
}

void IsoGameCharacter::setAttachedItems(AttachedItems var1) {
    // TODO: Implement setAttachedItems
}

InventoryItem IsoGameCharacter::getAttachedItem(const std::string& var1) {
    // TODO: Implement getAttachedItem
    return nullptr;
}

void IsoGameCharacter::setAttachedItem(const std::string& var1, InventoryItem var2) {
    // TODO: Implement setAttachedItem
}

void IsoGameCharacter::removeAttachedItem(InventoryItem var1) {
    // TODO: Implement removeAttachedItem
}

void IsoGameCharacter::clearAttachedItems() {
    // TODO: Implement clearAttachedItems
}

AttachedLocationGroup IsoGameCharacter::getAttachedLocationGroup() {
    // TODO: Implement getAttachedLocationGroup
    return nullptr;
}

ClothingWetness IsoGameCharacter::getClothingWetness() {
    // TODO: Implement getClothingWetness
    return nullptr;
}

InventoryItem IsoGameCharacter::getClothingItem_Head() {
    // TODO: Implement getClothingItem_Head
    return nullptr;
}

void IsoGameCharacter::setClothingItem_Head(InventoryItem var1) {
    // TODO: Implement setClothingItem_Head
}

InventoryItem IsoGameCharacter::getClothingItem_Torso() {
    // TODO: Implement getClothingItem_Torso
    return nullptr;
}

void IsoGameCharacter::setClothingItem_Torso(InventoryItem var1) {
    // TODO: Implement setClothingItem_Torso
}

InventoryItem IsoGameCharacter::getClothingItem_Back() {
    // TODO: Implement getClothingItem_Back
    return nullptr;
}

void IsoGameCharacter::setClothingItem_Back(InventoryItem var1) {
    // TODO: Implement setClothingItem_Back
}

InventoryItem IsoGameCharacter::getClothingItem_Hands() {
    // TODO: Implement getClothingItem_Hands
    return nullptr;
}

void IsoGameCharacter::setClothingItem_Hands(InventoryItem var1) {
    // TODO: Implement setClothingItem_Hands
}

InventoryItem IsoGameCharacter::getClothingItem_Legs() {
    // TODO: Implement getClothingItem_Legs
    return nullptr;
}

void IsoGameCharacter::setClothingItem_Legs(InventoryItem var1) {
    // TODO: Implement setClothingItem_Legs
}

InventoryItem IsoGameCharacter::getClothingItem_Feet() {
    // TODO: Implement getClothingItem_Feet
    return nullptr;
}

void IsoGameCharacter::setClothingItem_Feet(InventoryItem var1) {
    // TODO: Implement setClothingItem_Feet
}

int IsoGameCharacter::getNextWander() {
    // TODO: Implement getNextWander
    return 0;
}

void IsoGameCharacter::setNextWander(int var1) {
    // TODO: Implement setNextWander
}

bool IsoGameCharacter::isOnFire() {
    // TODO: Implement isOnFire
    return false;
}

void IsoGameCharacter::setOnFire(bool var1) {
    // TODO: Implement setOnFire
}

void IsoGameCharacter::removeFromWorld() {
    // TODO: Implement removeFromWorld
}

int IsoGameCharacter::getPathIndex() {
    // TODO: Implement getPathIndex
    return 0;
}

void IsoGameCharacter::setPathIndex(int var1) {
    // TODO: Implement setPathIndex
}

int IsoGameCharacter::getPathTargetX() {
    // TODO: Implement getPathTargetX
    return 0;
}

int IsoGameCharacter::getPathTargetY() {
    // TODO: Implement getPathTargetY
    return 0;
}

int IsoGameCharacter::getPathTargetZ() {
    // TODO: Implement getPathTargetZ
    return 0;
}

InventoryItem IsoGameCharacter::getSecondaryHandItem() {
    // TODO: Implement getSecondaryHandItem
    return nullptr;
}

void IsoGameCharacter::setSecondaryHandItem(InventoryItem var1) {
    // TODO: Implement setSecondaryHandItem
}

bool IsoGameCharacter::isHandItem(InventoryItem var1) {
    // TODO: Implement isHandItem
    return false;
}

bool IsoGameCharacter::isPrimaryHandItem(InventoryItem var1) {
    // TODO: Implement isPrimaryHandItem
    return false;
}

bool IsoGameCharacter::isSecondaryHandItem(InventoryItem var1) {
    // TODO: Implement isSecondaryHandItem
    return false;
}

bool IsoGameCharacter::isItemInBothHands(InventoryItem var1) {
    // TODO: Implement isItemInBothHands
    return false;
}

bool IsoGameCharacter::removeFromHands(InventoryItem var1) {
    // TODO: Implement removeFromHands
    return false;
}

Color IsoGameCharacter::getSpeakColour() {
    // TODO: Implement getSpeakColour
    return nullptr;
}

void IsoGameCharacter::setSpeakColour(Color var1) {
    // TODO: Implement setSpeakColour
}

void IsoGameCharacter::setSpeakColourInfo(ColorInfo var1) {
    // TODO: Implement setSpeakColourInfo
}

float IsoGameCharacter::getSlowFactor() {
    // TODO: Implement getSlowFactor
    return 0;
}

void IsoGameCharacter::setSlowFactor(float var1) {
    // TODO: Implement setSlowFactor
}

float IsoGameCharacter::getSlowTimer() {
    // TODO: Implement getSlowTimer
    return 0;
}

void IsoGameCharacter::setSlowTimer(float var1) {
    // TODO: Implement setSlowTimer
}

bool IsoGameCharacter::isbUseParts() {
    // TODO: Implement isbUseParts
    return false;
}

void IsoGameCharacter::setbUseParts(bool var1) {
    // TODO: Implement setbUseParts
}

bool IsoGameCharacter::isSpeaking() {
    // TODO: Implement isSpeaking
    return false;
}

void IsoGameCharacter::setSpeaking(bool var1) {
    // TODO: Implement setSpeaking
}

float IsoGameCharacter::getSpeakTime() {
    // TODO: Implement getSpeakTime
    return 0;
}

void IsoGameCharacter::setSpeakTime(int var1) {
    // TODO: Implement setSpeakTime
}

float IsoGameCharacter::getSpeedMod() {
    // TODO: Implement getSpeedMod
    return 0;
}

void IsoGameCharacter::setSpeedMod(float var1) {
    // TODO: Implement setSpeedMod
}

float IsoGameCharacter::getStaggerTimeMod() {
    // TODO: Implement getStaggerTimeMod
    return 0;
}

void IsoGameCharacter::setStaggerTimeMod(float var1) {
    // TODO: Implement setStaggerTimeMod
}

StateMachine IsoGameCharacter::getStateMachine() {
    // TODO: Implement getStateMachine
    return nullptr;
}

Moodles IsoGameCharacter::getMoodles() {
    // TODO: Implement getMoodles
    return nullptr;
}

Stats IsoGameCharacter::getStats() {
    // TODO: Implement getStats
    return nullptr;
}

HandWeapon IsoGameCharacter::getUseHandWeapon() {
    // TODO: Implement getUseHandWeapon
    return nullptr;
}

void IsoGameCharacter::setUseHandWeapon(HandWeapon var1) {
    // TODO: Implement setUseHandWeapon
}

IsoSprite IsoGameCharacter::getLegsSprite() {
    // TODO: Implement getLegsSprite
    return nullptr;
}

void IsoGameCharacter::setLegsSprite(IsoSprite var1) {
    // TODO: Implement setLegsSprite
}

IsoGridSquare IsoGameCharacter::getAttackTargetSquare() {
    // TODO: Implement getAttackTargetSquare
    return nullptr;
}

void IsoGameCharacter::setAttackTargetSquare(IsoGridSquare var1) {
    // TODO: Implement setAttackTargetSquare
}

float IsoGameCharacter::getBloodImpactX() {
    // TODO: Implement getBloodImpactX
    return 0;
}

void IsoGameCharacter::setBloodImpactX(float var1) {
    // TODO: Implement setBloodImpactX
}

float IsoGameCharacter::getBloodImpactY() {
    // TODO: Implement getBloodImpactY
    return 0;
}

void IsoGameCharacter::setBloodImpactY(float var1) {
    // TODO: Implement setBloodImpactY
}

float IsoGameCharacter::getBloodImpactZ() {
    // TODO: Implement getBloodImpactZ
    return 0;
}

void IsoGameCharacter::setBloodImpactZ(float var1) {
    // TODO: Implement setBloodImpactZ
}

IsoSprite IsoGameCharacter::getBloodSplat() {
    // TODO: Implement getBloodSplat
    return nullptr;
}

void IsoGameCharacter::setBloodSplat(IsoSprite var1) {
    // TODO: Implement setBloodSplat
}

bool IsoGameCharacter::isbOnBed() {
    // TODO: Implement isbOnBed
    return false;
}

void IsoGameCharacter::setbOnBed(bool var1) {
    // TODO: Implement setbOnBed
}

Vector2 IsoGameCharacter::getMoveForwardVec() {
    // TODO: Implement getMoveForwardVec
    return nullptr;
}

void IsoGameCharacter::setMoveForwardVec(Vector2 var1) {
    // TODO: Implement setMoveForwardVec
}

bool IsoGameCharacter::isPathing() {
    // TODO: Implement isPathing
    return false;
}

void IsoGameCharacter::setPathing(bool var1) {
    // TODO: Implement setPathing
}

TraitCollection IsoGameCharacter::getTraits() {
    // TODO: Implement getTraits
    return nullptr;
}

CharacterTraits IsoGameCharacter::getCharacterTraits() {
    // TODO: Implement getCharacterTraits
    return nullptr;
}

int IsoGameCharacter::getMaxWeight() {
    // TODO: Implement getMaxWeight
    return 0;
}

void IsoGameCharacter::setMaxWeight(int var1) {
    // TODO: Implement setMaxWeight
}

int IsoGameCharacter::getMaxWeightBase() {
    // TODO: Implement getMaxWeightBase
    return 0;
}

void IsoGameCharacter::setMaxWeightBase(int var1) {
    // TODO: Implement setMaxWeightBase
}

float IsoGameCharacter::getSleepingTabletDelta() {
    // TODO: Implement getSleepingTabletDelta
    return 0;
}

void IsoGameCharacter::setSleepingTabletDelta(float var1) {
    // TODO: Implement setSleepingTabletDelta
}

float IsoGameCharacter::getBetaEffect() {
    // TODO: Implement getBetaEffect
    return 0;
}

void IsoGameCharacter::setBetaEffect(float var1) {
    // TODO: Implement setBetaEffect
}

float IsoGameCharacter::getDepressEffect() {
    // TODO: Implement getDepressEffect
    return 0;
}

void IsoGameCharacter::setDepressEffect(float var1) {
    // TODO: Implement setDepressEffect
}

float IsoGameCharacter::getSleepingTabletEffect() {
    // TODO: Implement getSleepingTabletEffect
    return 0;
}

void IsoGameCharacter::setSleepingTabletEffect(float var1) {
    // TODO: Implement setSleepingTabletEffect
}

float IsoGameCharacter::getBetaDelta() {
    // TODO: Implement getBetaDelta
    return 0;
}

void IsoGameCharacter::setBetaDelta(float var1) {
    // TODO: Implement setBetaDelta
}

float IsoGameCharacter::getDepressDelta() {
    // TODO: Implement getDepressDelta
    return 0;
}

void IsoGameCharacter::setDepressDelta(float var1) {
    // TODO: Implement setDepressDelta
}

float IsoGameCharacter::getPainEffect() {
    // TODO: Implement getPainEffect
    return 0;
}

void IsoGameCharacter::setPainEffect(float var1) {
    // TODO: Implement setPainEffect
}

float IsoGameCharacter::getPainDelta() {
    // TODO: Implement getPainDelta
    return 0;
}

void IsoGameCharacter::setPainDelta(float var1) {
    // TODO: Implement setPainDelta
}

bool IsoGameCharacter::isbDoDefer() {
    // TODO: Implement isbDoDefer
    return false;
}

void IsoGameCharacter::setbDoDefer(bool var1) {
    // TODO: Implement setbDoDefer
}

Location IsoGameCharacter::getLastHeardSound() {
    // TODO: Implement getLastHeardSound
    return nullptr;
}

void IsoGameCharacter::setLastHeardSound(int var1, int var2, int var3) {
    // TODO: Implement setLastHeardSound
}

float IsoGameCharacter::getLrx() {
    // TODO: Implement getLrx
    return 0;
}

void IsoGameCharacter::setLrx(float var1) {
    // TODO: Implement setLrx
}

float IsoGameCharacter::getLry() {
    // TODO: Implement getLry
    return 0;
}

void IsoGameCharacter::setLry(float var1) {
    // TODO: Implement setLry
}

bool IsoGameCharacter::isClimbing() {
    // TODO: Implement isClimbing
    return false;
}

void IsoGameCharacter::setbClimbing(bool var1) {
    // TODO: Implement setbClimbing
}

bool IsoGameCharacter::isLastCollidedW() {
    // TODO: Implement isLastCollidedW
    return false;
}

void IsoGameCharacter::setLastCollidedW(bool var1) {
    // TODO: Implement setLastCollidedW
}

bool IsoGameCharacter::isLastCollidedN() {
    // TODO: Implement isLastCollidedN
    return false;
}

void IsoGameCharacter::setLastCollidedN(bool var1) {
    // TODO: Implement setLastCollidedN
}

float IsoGameCharacter::getFallTime() {
    // TODO: Implement getFallTime
    return 0;
}

void IsoGameCharacter::setFallTime(float var1) {
    // TODO: Implement setFallTime
}

float IsoGameCharacter::getLastFallSpeed() {
    // TODO: Implement getLastFallSpeed
    return 0;
}

void IsoGameCharacter::setLastFallSpeed(float var1) {
    // TODO: Implement setLastFallSpeed
}

bool IsoGameCharacter::isbFalling() {
    // TODO: Implement isbFalling
    return false;
}

void IsoGameCharacter::setbFalling(bool var1) {
    // TODO: Implement setbFalling
}

IsoBuilding IsoGameCharacter::getCurrentBuilding() {
    // TODO: Implement getCurrentBuilding
    return nullptr;
}

BuildingDef IsoGameCharacter::getCurrentBuildingDef() {
    // TODO: Implement getCurrentBuildingDef
    return nullptr;
}

RoomDef IsoGameCharacter::getCurrentRoomDef() {
    // TODO: Implement getCurrentRoomDef
    return nullptr;
}

float IsoGameCharacter::getTorchStrength() {
    // TODO: Implement getTorchStrength
    return 0;
}

void IsoGameCharacter::OnAnimEvent(AnimLayer var1, AnimEvent var2) {
    // TODO: Implement OnAnimEvent
}

void IsoGameCharacter::damageWhileInTrees() {
    // TODO: Implement damageWhileInTrees
}

float IsoGameCharacter::getHammerSoundMod() {
    // TODO: Implement getHammerSoundMod
    return 0;
}

float IsoGameCharacter::getWeldingSoundMod() {
    // TODO: Implement getWeldingSoundMod
    return 0;
}

float IsoGameCharacter::getBarricadeTimeMod() {
    // TODO: Implement getBarricadeTimeMod
    return 0;
}

float IsoGameCharacter::getMetalBarricadeStrengthMod() {
    // TODO: Implement getMetalBarricadeStrengthMod
    return 0;
}

float IsoGameCharacter::getBarricadeStrengthMod() {
    // TODO: Implement getBarricadeStrengthMod
    return 0;
}

float IsoGameCharacter::getSneakSpotMod() {
    // TODO: Implement getSneakSpotMod
    return 0;
}

float IsoGameCharacter::getNimbleMod() {
    // TODO: Implement getNimbleMod
    return 0;
}

float IsoGameCharacter::getFatigueMod() {
    // TODO: Implement getFatigueMod
    return 0;
}

float IsoGameCharacter::getLightfootMod() {
    // TODO: Implement getLightfootMod
    return 0;
}

float IsoGameCharacter::getPacingMod() {
    // TODO: Implement getPacingMod
    return 0;
}

float IsoGameCharacter::getHyperthermiaMod() {
    // TODO: Implement getHyperthermiaMod
    return 0;
}

float IsoGameCharacter::getHittingMod() {
    // TODO: Implement getHittingMod
    return 0;
}

float IsoGameCharacter::getShovingMod() {
    // TODO: Implement getShovingMod
    return 0;
}

float IsoGameCharacter::getRecoveryMod() {
    // TODO: Implement getRecoveryMod
    return 0;
}

float IsoGameCharacter::getWeightMod() {
    // TODO: Implement getWeightMod
    return 0;
}

int IsoGameCharacter::getHitChancesMod() {
    // TODO: Implement getHitChancesMod
    return 0;
}

float IsoGameCharacter::getSprintMod() {
    // TODO: Implement getSprintMod
    return 0;
}

int IsoGameCharacter::getPerkLevel(Perk var1) {
    // TODO: Implement getPerkLevel
    return 0;
}

void IsoGameCharacter::setPerkLevelDebug(Perk var1, int var2) {
    // TODO: Implement setPerkLevelDebug
}

void IsoGameCharacter::LoseLevel(Perk var1) {
    // TODO: Implement LoseLevel
}

void IsoGameCharacter::LevelPerk(Perk var1, bool var2) {
    // TODO: Implement LevelPerk
}

void IsoGameCharacter::LevelPerk(Perk var1) {
    // TODO: Implement LevelPerk
}

void IsoGameCharacter::level0(Perk var1) {
    // TODO: Implement level0
}

Location IsoGameCharacter::getLastKnownLocationOf(const std::string& var1) {
    // TODO: Implement getLastKnownLocationOf
    return nullptr;
}

void IsoGameCharacter::ReadLiterature(Literature var1) {
    // TODO: Implement ReadLiterature
}

void IsoGameCharacter::OnDeath() {
    // TODO: Implement OnDeath
}

void IsoGameCharacter::splatBloodFloorBig() {
    // TODO: Implement splatBloodFloorBig
}

void IsoGameCharacter::splatBloodFloor() {
    // TODO: Implement splatBloodFloor
}

int IsoGameCharacter::getThreatLevel() {
    // TODO: Implement getThreatLevel
    return 0;
}

bool IsoGameCharacter::isDead() {
    // TODO: Implement isDead
    return false;
}

bool IsoGameCharacter::isAlive() {
    // TODO: Implement isAlive
    return false;
}

void IsoGameCharacter::Seen(std::stack<IsoMovingObject> var1) {
    // TODO: Implement Seen
}

bool IsoGameCharacter::CanSee(IsoMovingObject var1) {
    // TODO: Implement CanSee
    return false;
}

IsoGridSquare IsoGameCharacter::getLowDangerInVicinity(int var1, int var2) {
    // TODO: Implement getLowDangerInVicinity
    return nullptr;
}

void IsoGameCharacter::Anger(int var1) {
    // TODO: Implement Anger
}

bool IsoGameCharacter::hasEquipped(const std::string& var1) {
    // TODO: Implement hasEquipped
    return false;
}

bool IsoGameCharacter::hasEquippedTag(const std::string& var1) {
    // TODO: Implement hasEquippedTag
    return false;
}

void IsoGameCharacter::setDir(IsoDirections var1) {
    // TODO: Implement setDir
}

void IsoGameCharacter::Callout(bool var1) {
    // TODO: Implement Callout
}

void IsoGameCharacter::Callout() {
    // TODO: Implement Callout
}

void IsoGameCharacter::load(ByteBuffer var1, int var2, bool var3) {
    // TODO: Implement load
}

void IsoGameCharacter::save(ByteBuffer var1, bool var2) {
    // TODO: Implement save
}

ChatElement IsoGameCharacter::getChatElement() {
    // TODO: Implement getChatElement
    return nullptr;
}

void IsoGameCharacter::StartAction(BaseAction var1) {
    // TODO: Implement StartAction
}

void IsoGameCharacter::QueueAction(BaseAction var1) {
    // TODO: Implement QueueAction
}

void IsoGameCharacter::StopAllActionQueue() {
    // TODO: Implement StopAllActionQueue
}

void IsoGameCharacter::StopAllActionQueueRunning() {
    // TODO: Implement StopAllActionQueueRunning
}

void IsoGameCharacter::StopAllActionQueueAiming() {
    // TODO: Implement StopAllActionQueueAiming
}

void IsoGameCharacter::StopAllActionQueueWalking() {
    // TODO: Implement StopAllActionQueueWalking
}

std::string IsoGameCharacter::GetAnimSetName() {
    // TODO: Implement GetAnimSetName
    return "";
}

void IsoGameCharacter::SleepingTablet(float var1) {
    // TODO: Implement SleepingTablet
}

void IsoGameCharacter::BetaBlockers(float var1) {
    // TODO: Implement BetaBlockers
}

void IsoGameCharacter::BetaAntiDepress(float var1) {
    // TODO: Implement BetaAntiDepress
}

void IsoGameCharacter::PainMeds(float var1) {
    // TODO: Implement PainMeds
}

void IsoGameCharacter::initSpritePartsEmpty() {
    // TODO: Implement initSpritePartsEmpty
}

void IsoGameCharacter::InitSpriteParts(SurvivorDesc var1) {
    // TODO: Implement InitSpriteParts
}

bool IsoGameCharacter::HasTrait(const std::string& var1) {
    // TODO: Implement HasTrait
    return false;
}

void IsoGameCharacter::ApplyInBedOffset(bool var1) {
    // TODO: Implement ApplyInBedOffset
}

void IsoGameCharacter::Dressup(SurvivorDesc var1) {
    // TODO: Implement Dressup
}

void IsoGameCharacter::PlayAnim(const std::string& var1) {
    // TODO: Implement PlayAnim
}

void IsoGameCharacter::PlayAnimWithSpeed(const std::string& var1, float var2) {
    // TODO: Implement PlayAnimWithSpeed
}

void IsoGameCharacter::PlayAnimUnlooped(const std::string& var1) {
    // TODO: Implement PlayAnimUnlooped
}

void IsoGameCharacter::DirectionFromVector(Vector2 var1) {
    // TODO: Implement DirectionFromVector
}

void IsoGameCharacter::DoFootstepSound(const std::string& var1) {
    // TODO: Implement DoFootstepSound
}

void IsoGameCharacter::DoFootstepSound(float var1) {
    // TODO: Implement DoFootstepSound
}

bool IsoGameCharacter::Eat(InventoryItem var1, float var2) {
    // TODO: Implement Eat
    return false;
}

bool IsoGameCharacter::Eat(InventoryItem var1) {
    // TODO: Implement Eat
    return false;
}

void IsoGameCharacter::FireCheck() {
    // TODO: Implement FireCheck
}

std::string IsoGameCharacter::getPrimaryHandType() {
    // TODO: Implement getPrimaryHandType
    return "";
}

float IsoGameCharacter::getGlobalMovementMod(bool var1) {
    // TODO: Implement getGlobalMovementMod
    return 0;
}

float IsoGameCharacter::getMoveSpeed() {
    // TODO: Implement getMoveSpeed
    return 0;
}

std::string IsoGameCharacter::getSecondaryHandType() {
    // TODO: Implement getSecondaryHandType
    return "";
}

bool IsoGameCharacter::HasItem(const std::string& var1) {
    // TODO: Implement HasItem
    return false;
}

void IsoGameCharacter::changeState(State var1) {
    // TODO: Implement changeState
}

State IsoGameCharacter::getCurrentState() {
    // TODO: Implement getCurrentState
    return nullptr;
}

bool IsoGameCharacter::isCurrentState(State var1) {
    // TODO: Implement isCurrentState
    return false;
}

void IsoGameCharacter::setStateMachineLocked(bool var1) {
    // TODO: Implement setStateMachineLocked
}

float IsoGameCharacter::Hit(HandWeapon var1, IsoGameCharacter var2, float var3, bool var4, float var5) {
    // TODO: Implement Hit
    return 0;
}

float IsoGameCharacter::Hit(HandWeapon var1, IsoGameCharacter var2, float var3, bool var4, float var5, bool var6) {
    // TODO: Implement Hit
    return 0;
}

float IsoGameCharacter::processHitDamage(HandWeapon var1, IsoGameCharacter var2, float var3, bool var4, float var5) {
    // TODO: Implement processHitDamage
    return 0;
}

void IsoGameCharacter::hitConsequences(HandWeapon var1, IsoGameCharacter var2, bool var3, float var4, bool var5) {
    // TODO: Implement hitConsequences
}

bool IsoGameCharacter::IsAttackRange(float var1, float var2, float var3) {
    // TODO: Implement IsAttackRange
    return false;
}

bool IsoGameCharacter::IsAttackRange(HandWeapon var1, IsoMovingObject var2, Vector3 var3, bool var4) {
    // TODO: Implement IsAttackRange
    return false;
}

bool IsoGameCharacter::IsSpeaking() {
    // TODO: Implement IsSpeaking
    return false;
}

void IsoGameCharacter::MoveForward(float var1, float var2, float var3, float var4) {
    // TODO: Implement MoveForward
}

void IsoGameCharacter::pathToAux(float var1, float var2, float var3) {
    // TODO: Implement pathToAux
}

void IsoGameCharacter::pathToCharacter(IsoGameCharacter var1) {
    // TODO: Implement pathToCharacter
}

void IsoGameCharacter::pathToLocation(int var1, int var2, int var3) {
    // TODO: Implement pathToLocation
}

void IsoGameCharacter::pathToLocationF(float var1, float var2, float var3) {
    // TODO: Implement pathToLocationF
}

void IsoGameCharacter::pathToSound(int var1, int var2, int var3) {
    // TODO: Implement pathToSound
}

bool IsoGameCharacter::CanAttack() {
    // TODO: Implement CanAttack
    return false;
}

void IsoGameCharacter::ReduceHealthWhenBurning() {
    // TODO: Implement ReduceHealthWhenBurning
}

void IsoGameCharacter::DrawSneezeText() {
    // TODO: Implement DrawSneezeText
}

IsoSpriteInstance IsoGameCharacter::getSpriteDef() {
    // TODO: Implement getSpriteDef
    return nullptr;
}

void IsoGameCharacter::render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
    // TODO: Implement render
}

void IsoGameCharacter::renderServerGUI() {
    // TODO: Implement renderServerGUI
}

float IsoGameCharacter::getAlphaUpdateRateMul() {
    // TODO: Implement getAlphaUpdateRateMul
    return 0;
}

bool IsoGameCharacter::isUpdateAlphaEnabled() {
    // TODO: Implement isUpdateAlphaEnabled
    return false;
}

bool IsoGameCharacter::isUpdateAlphaDuringRender() {
    // TODO: Implement isUpdateAlphaDuringRender
    return false;
}

bool IsoGameCharacter::isSeatedInVehicle() {
    // TODO: Implement isSeatedInVehicle
    return false;
}

void IsoGameCharacter::renderObjectPicker(float var1, float var2, float var3, ColorInfo var4) {
    // TODO: Implement renderObjectPicker
}

Vector2 IsoGameCharacter::closestpointonline(double var0, double var2, double var4, double var6, double var8, double var10, Vector2 var12) {
    // TODO: Implement closestpointonline
    return nullptr;
}

void IsoGameCharacter::renderShadow(float var1, float var2, float var3) {
    // TODO: Implement renderShadow
}

void IsoGameCharacter::checkUpdateModelTextures() {
    // TODO: Implement checkUpdateModelTextures
}

bool IsoGameCharacter::isMaskClicked(int var1, int var2, bool var3) {
    // TODO: Implement isMaskClicked
    return false;
}

void IsoGameCharacter::setHaloNote(const std::string& var1) {
    // TODO: Implement setHaloNote
}

void IsoGameCharacter::setHaloNote(const std::string& var1, float var2) {
    // TODO: Implement setHaloNote
}

void IsoGameCharacter::setHaloNote(const std::string& var1, int var2, int var3, int var4, float var5) {
    // TODO: Implement setHaloNote
}

float IsoGameCharacter::getHaloTimerCount() {
    // TODO: Implement getHaloTimerCount
    return 0;
}

void IsoGameCharacter::DoSneezeText() {
    // TODO: Implement DoSneezeText
}

std::string IsoGameCharacter::getSayLine() {
    // TODO: Implement getSayLine
    return "";
}

void IsoGameCharacter::setSayLine(const std::string& var1) {
    // TODO: Implement setSayLine
}

ChatMessage IsoGameCharacter::getLastChatMessage() {
    // TODO: Implement getLastChatMessage
    return nullptr;
}

void IsoGameCharacter::setLastChatMessage(ChatMessage var1) {
    // TODO: Implement setLastChatMessage
}

std::string IsoGameCharacter::getLastSpokenLine() {
    // TODO: Implement getLastSpokenLine
    return "";
}

void IsoGameCharacter::setLastSpokenLine(const std::string& var1) {
    // TODO: Implement setLastSpokenLine
}

void IsoGameCharacter::doSleepSpeech() {
    // TODO: Implement doSleepSpeech
}

void IsoGameCharacter::SayDebug(const std::string& var1) {
    // TODO: Implement SayDebug
}

void IsoGameCharacter::SayDebug(int var1, const std::string& var2) {
    // TODO: Implement SayDebug
}

int IsoGameCharacter::getMaxChatLines() {
    // TODO: Implement getMaxChatLines
    return 0;
}

void IsoGameCharacter::Say(const std::string& var1) {
    // TODO: Implement Say
}

void IsoGameCharacter::Say(const std::string& var1, float var2, float var3, float var4, UIFont var5, float var6, const std::string& var7) {
    // TODO: Implement Say
}

void IsoGameCharacter::SayWhisper(const std::string& var1) {
    // TODO: Implement SayWhisper
}

void IsoGameCharacter::SayShout(const std::string& var1) {
    // TODO: Implement SayShout
}

void IsoGameCharacter::SayRadio(const std::string& var1, float var2, float var3, float var4, UIFont var5, float var6, int var7, const std::string& var8) {
    // TODO: Implement SayRadio
}

void IsoGameCharacter::ProcessSay(const std::string& var1, float var2, float var3, float var4, float var5, int var6, const std::string& var7) {
    // TODO: Implement ProcessSay
}

void IsoGameCharacter::addLineChatElement(const std::string& var1) {
    // TODO: Implement addLineChatElement
}

void IsoGameCharacter::addLineChatElement(const std::string& var1, float var2, float var3, float var4) {
    // TODO: Implement addLineChatElement
}

void IsoGameCharacter::addLineChatElement(const std::string& var1, float var2, float var3, float var4, UIFont var5, float var6, const std::string& var7) {
    // TODO: Implement addLineChatElement
}

bool IsoGameCharacter::playerIsSelf() {
    // TODO: Implement playerIsSelf
    return false;
}

int IsoGameCharacter::getUserNameHeight() {
    // TODO: Implement getUserNameHeight
    return 0;
}

void IsoGameCharacter::initTextObjects() {
    // TODO: Implement initTextObjects
}

void IsoGameCharacter::updateUserName() {
    // TODO: Implement updateUserName
}

void IsoGameCharacter::updateTextObjects() {
    // TODO: Implement updateTextObjects
}

void IsoGameCharacter::renderlast() {
    // TODO: Implement renderlast
}

bool IsoGameCharacter::renderTextureInsteadOfModel(float var1, float var2) {
    // TODO: Implement renderTextureInsteadOfModel
    return false;
}

void IsoGameCharacter::drawDirectionLine(Vector2 var1, float var2, float var3, float var4, float var5) {
    // TODO: Implement drawDirectionLine
}

void IsoGameCharacter::drawDebugTextBelow(const std::string& var1) {
    // TODO: Implement drawDebugTextBelow
}

Radio IsoGameCharacter::getEquipedRadio() {
    // TODO: Implement getEquipedRadio
    return nullptr;
}

void IsoGameCharacter::radioEquipedCheck() {
    // TODO: Implement radioEquipedCheck
}

void IsoGameCharacter::debugAim() {
    // TODO: Implement debugAim
}

void IsoGameCharacter::debugTestDotSide() {
    // TODO: Implement debugTestDotSide
}

void IsoGameCharacter::debugVision() {
    // TODO: Implement debugVision
}

void IsoGameCharacter::setDefaultState() {
    // TODO: Implement setDefaultState
}

void IsoGameCharacter::SetOnFire() {
    // TODO: Implement SetOnFire
}

void IsoGameCharacter::StopBurning() {
    // TODO: Implement StopBurning
}

void IsoGameCharacter::sendStopBurning() {
    // TODO: Implement sendStopBurning
}

void IsoGameCharacter::SpreadFireMP() {
    // TODO: Implement SpreadFireMP
}

void IsoGameCharacter::SpreadFire() {
    // TODO: Implement SpreadFire
}

void IsoGameCharacter::Throw(HandWeapon var1) {
    // TODO: Implement Throw
}

new IsoGameCharacter::IsoBall() {
    // TODO: Implement IsoBall
    return nullptr;
}

new IsoGameCharacter::IsoMolotovCocktail() {
    // TODO: Implement IsoMolotovCocktail
    return nullptr;
}

void IsoGameCharacter::serverRemoveItemFromZombie(const std::string& var1) {
    // TODO: Implement serverRemoveItemFromZombie
}

bool IsoGameCharacter::helmetFall(bool var1) {
    // TODO: Implement helmetFall
    return false;
}

bool IsoGameCharacter::helmetFall(bool var1, const std::string& var2) {
    // TODO: Implement helmetFall
    return false;
}

void IsoGameCharacter::smashCarWindow(VehiclePart var1) {
    // TODO: Implement smashCarWindow
}

void IsoGameCharacter::smashWindow(IsoWindow var1) {
    // TODO: Implement smashWindow
}

void IsoGameCharacter::openWindow(IsoWindow var1) {
    // TODO: Implement openWindow
}

void IsoGameCharacter::closeWindow(IsoWindow var1) {
    // TODO: Implement closeWindow
}

void IsoGameCharacter::climbThroughWindow(IsoWindow var1) {
    // TODO: Implement climbThroughWindow
}

void IsoGameCharacter::climbThroughWindow(IsoWindow var1, int var2) {
    // TODO: Implement climbThroughWindow
}

bool IsoGameCharacter::isClosingWindow(IsoWindow var1) {
    // TODO: Implement isClosingWindow
    return false;
}

bool IsoGameCharacter::isClimbingThroughWindow(IsoWindow var1) {
    // TODO: Implement isClimbingThroughWindow
    return false;
}

void IsoGameCharacter::climbThroughWindowFrame(IsoObject var1) {
    // TODO: Implement climbThroughWindowFrame
}

void IsoGameCharacter::climbSheetRope() {
    // TODO: Implement climbSheetRope
}

void IsoGameCharacter::climbDownSheetRope() {
    // TODO: Implement climbDownSheetRope
}

bool IsoGameCharacter::canClimbSheetRope(IsoGridSquare var1) {
    // TODO: Implement canClimbSheetRope
    return false;
}

bool IsoGameCharacter::canClimbDownSheetRopeInCurrentSquare() {
    // TODO: Implement canClimbDownSheetRopeInCurrentSquare
    return false;
}

bool IsoGameCharacter::canClimbDownSheetRope(IsoGridSquare var1) {
    // TODO: Implement canClimbDownSheetRope
    return false;
}

void IsoGameCharacter::climbThroughWindow(IsoThumpable var1) {
    // TODO: Implement climbThroughWindow
}

void IsoGameCharacter::climbThroughWindow(IsoThumpable var1, int var2) {
    // TODO: Implement climbThroughWindow
}

void IsoGameCharacter::climbOverFence(IsoDirections var1) {
    // TODO: Implement climbOverFence
}

bool IsoGameCharacter::isAboveTopOfStairs() {
    // TODO: Implement isAboveTopOfStairs
    return false;
}

void IsoGameCharacter::preupdate() {
    // TODO: Implement preupdate
}

void IsoGameCharacter::setTeleport(NetworkTeleport var1) {
    // TODO: Implement setTeleport
}

NetworkTeleport IsoGameCharacter::getTeleport() {
    // TODO: Implement getTeleport
    return nullptr;
}

bool IsoGameCharacter::isTeleporting() {
    // TODO: Implement isTeleporting
    return false;
}

void IsoGameCharacter::update() {
    // TODO: Implement update
}

void IsoGameCharacter::updateInternal() {
    // TODO: Implement updateInternal
}

void IsoGameCharacter::updateSeenVisibility() {
    // TODO: Implement updateSeenVisibility
}

void IsoGameCharacter::updateSeenVisibility(int var1) {
    // TODO: Implement updateSeenVisibility
}

void IsoGameCharacter::recursiveItemUpdater(ItemContainer var1) {
    // TODO: Implement recursiveItemUpdater
}

void IsoGameCharacter::recursiveItemUpdater(InventoryContainer var1) {
    // TODO: Implement recursiveItemUpdater
}

void IsoGameCharacter::updateDirt() {
    // TODO: Implement updateDirt
}

void IsoGameCharacter::updateMovementMomentum() {
    // TODO: Implement updateMovementMomentum
}

double IsoGameCharacter::getHoursSurvived() {
    // TODO: Implement getHoursSurvived
    return 0;
}

void IsoGameCharacter::updateBeardAndHair() {
    // TODO: Implement updateBeardAndHair
}

void IsoGameCharacter::updateFalling() {
    // TODO: Implement updateFalling
}

float IsoGameCharacter::getHeightAboveFloor() {
    // TODO: Implement getHeightAboveFloor
    return 0;
}

void IsoGameCharacter::updateMovementRates() {
    // TODO: Implement updateMovementRates
}

float IsoGameCharacter::calculateIdleSpeed() {
    // TODO: Implement calculateIdleSpeed
    return 0;
}

float IsoGameCharacter::calculateBaseSpeed() {
    // TODO: Implement calculateBaseSpeed
    return 0;
}

float IsoGameCharacter::calcRunSpeedModByClothing() {
    // TODO: Implement calcRunSpeedModByClothing
    return 0;
}

float IsoGameCharacter::calcRunSpeedModByBag(InventoryContainer var1) {
    // TODO: Implement calcRunSpeedModByBag
    return 0;
}

float IsoGameCharacter::calculateCombatSpeed() {
    // TODO: Implement calculateCombatSpeed
    return 0;
}

float IsoGameCharacter::getArmsInjurySpeedModifier() {
    // TODO: Implement getArmsInjurySpeedModifier
    return 0;
}

float IsoGameCharacter::getFootInjurySpeedModifier() {
    // TODO: Implement getFootInjurySpeedModifier
    return 0;
}

float IsoGameCharacter::calculateInjurySpeed(BodyPart var1, bool var2) {
    // TODO: Implement calculateInjurySpeed
    return 0;
}

float IsoGameCharacter::calcFractureInjurySpeed(BodyPart var1) {
    // TODO: Implement calcFractureInjurySpeed
    return 0;
}

void IsoGameCharacter::calculateWalkSpeed() {
    // TODO: Implement calculateWalkSpeed
}

void IsoGameCharacter::updateSpeedModifiers() {
    // TODO: Implement updateSpeedModifiers
}

void IsoGameCharacter::DoFloorSplat(IsoGridSquare var1, const std::string& var2, bool var3, float var4, float var5) {
    // TODO: Implement DoFloorSplat
}

void IsoGameCharacter::DoSplat(IsoGridSquare var1, const std::string& var2, bool var3, IsoFlagType var4, float var5, float var6, float var7) {
    // TODO: Implement DoSplat
}

bool IsoGameCharacter::onMouseLeftClick(int var1, int var2) {
    // TODO: Implement onMouseLeftClick
    return false;
}

void IsoGameCharacter::calculateStats() {
    // TODO: Implement calculateStats
}

void IsoGameCharacter::updateStats_WakeState() {
    // TODO: Implement updateStats_WakeState
}

void IsoGameCharacter::updateStats_Sleeping() {
    // TODO: Implement updateStats_Sleeping
}

void IsoGameCharacter::updateStats_Awake() {
    // TODO: Implement updateStats_Awake
}

void IsoGameCharacter::updateMorale() {
    // TODO: Implement updateMorale
}

void IsoGameCharacter::updateFitness() {
    // TODO: Implement updateFitness
}

void IsoGameCharacter::updateTripping() {
    // TODO: Implement updateTripping
}

float IsoGameCharacter::getAppetiteMultiplier() {
    // TODO: Implement getAppetiteMultiplier
    return 0;
}

void IsoGameCharacter::updateStress() {
    // TODO: Implement updateStress
}

void IsoGameCharacter::updateEndurance() {
    // TODO: Implement updateEndurance
}

void IsoGameCharacter::updateThirst() {
    // TODO: Implement updateThirst
}

double IsoGameCharacter::getRunningThirstReduction() {
    // TODO: Implement getRunningThirstReduction
    return 0;
}

void IsoGameCharacter::faceLocation(float var1, float var2) {
    // TODO: Implement faceLocation
}

void IsoGameCharacter::faceLocationF(float var1, float var2) {
    // TODO: Implement faceLocationF
}

bool IsoGameCharacter::isFacingLocation(float var1, float var2, float var3) {
    // TODO: Implement isFacingLocation
    return false;
}

bool IsoGameCharacter::isFacingObject(IsoObject var1, float var2) {
    // TODO: Implement isFacingObject
    return false;
}

void IsoGameCharacter::checkDrawWeaponPre(float var1, float var2, float var3, ColorInfo var4) {
    // TODO: Implement checkDrawWeaponPre
}

void IsoGameCharacter::splatBlood(int var1, float var2) {
    // TODO: Implement splatBlood
}

bool IsoGameCharacter::isOutside() {
    // TODO: Implement isOutside
    return false;
}

bool IsoGameCharacter::isFemale() {
    // TODO: Implement isFemale
    return false;
}

void IsoGameCharacter::setFemale(bool var1) {
    // TODO: Implement setFemale
}

bool IsoGameCharacter::isZombie() {
    // TODO: Implement isZombie
    return false;
}

int IsoGameCharacter::getLastHitCount() {
    // TODO: Implement getLastHitCount
    return 0;
}

void IsoGameCharacter::setLastHitCount(int var1) {
    // TODO: Implement setLastHitCount
}

int IsoGameCharacter::getSurvivorKills() {
    // TODO: Implement getSurvivorKills
    return 0;
}

void IsoGameCharacter::setSurvivorKills(int var1) {
    // TODO: Implement setSurvivorKills
}

int IsoGameCharacter::getAge() {
    // TODO: Implement getAge
    return 0;
}

void IsoGameCharacter::setAge(int var1) {
    // TODO: Implement setAge
}

void IsoGameCharacter::exert(float var1) {
    // TODO: Implement exert
}

PerkInfo IsoGameCharacter::getPerkInfo(Perk var1) {
    // TODO: Implement getPerkInfo
    return nullptr;
}

bool IsoGameCharacter::isEquipped(InventoryItem var1) {
    // TODO: Implement isEquipped
    return false;
}

bool IsoGameCharacter::isEquippedClothing(InventoryItem var1) {
    // TODO: Implement isEquippedClothing
    return false;
}

bool IsoGameCharacter::isAttachedItem(InventoryItem var1) {
    // TODO: Implement isAttachedItem
    return false;
}

void IsoGameCharacter::faceThisObject(IsoObject var1) {
    // TODO: Implement faceThisObject
}

void IsoGameCharacter::facePosition(int var1, int var2) {
    // TODO: Implement facePosition
}

void IsoGameCharacter::faceThisObjectAlt(IsoObject var1) {
    // TODO: Implement faceThisObjectAlt
}

void IsoGameCharacter::setAnimated(bool var1) {
    // TODO: Implement setAnimated
}

void IsoGameCharacter::playHurtSound() {
    // TODO: Implement playHurtSound
}

void IsoGameCharacter::playDeadSound() {
    // TODO: Implement playDeadSound
}

void IsoGameCharacter::saveChange(const std::string& var1, KahluaTable var2, ByteBuffer var3) {
    // TODO: Implement saveChange
}

void IsoGameCharacter::loadChange(const std::string& var1, ByteBuffer var2) {
    // TODO: Implement loadChange
}

int IsoGameCharacter::getAlreadyReadPages(const std::string& var1) {
    // TODO: Implement getAlreadyReadPages
    return 0;
}

void IsoGameCharacter::setAlreadyReadPages(const std::string& var1, int var2) {
    // TODO: Implement setAlreadyReadPages
}

void IsoGameCharacter::updateLightInfo() {
    // TODO: Implement updateLightInfo
}

LightInfo IsoGameCharacter::initLightInfo2() {
    // TODO: Implement initLightInfo2
    return nullptr;
}

LightInfo IsoGameCharacter::getLightInfo2() {
    // TODO: Implement getLightInfo2
    return nullptr;
}

void IsoGameCharacter::postupdate() {
    // TODO: Implement postupdate
}

void IsoGameCharacter::postUpdateInternal() {
    // TODO: Implement postUpdateInternal
}

bool IsoGameCharacter::shouldBeTurning() {
    // TODO: Implement shouldBeTurning
    return false;
}

bool IsoGameCharacter::shouldBeTurning90() {
    // TODO: Implement shouldBeTurning90
    return false;
}

bool IsoGameCharacter::shouldBeTurningAround() {
    // TODO: Implement shouldBeTurningAround
    return false;
}

bool IsoGameCharacter::isTurning() {
    // TODO: Implement isTurning
    return false;
}

void IsoGameCharacter::setTurning(bool var1) {
    // TODO: Implement setTurning
}

bool IsoGameCharacter::isTurningAround() {
    // TODO: Implement isTurningAround
    return false;
}

void IsoGameCharacter::setTurningAround(bool var1) {
    // TODO: Implement setTurningAround
}

bool IsoGameCharacter::isTurning90() {
    // TODO: Implement isTurning90
    return false;
}

void IsoGameCharacter::setTurning90(bool var1) {
    // TODO: Implement setTurning90
}

bool IsoGameCharacter::hasPath() {
    // TODO: Implement hasPath
    return false;
}

bool IsoGameCharacter::isAnimationRecorderActive() {
    // TODO: Implement isAnimationRecorderActive
    return false;
}

AnimationPlayerRecorder IsoGameCharacter::getAnimationPlayerRecorder() {
    // TODO: Implement getAnimationPlayerRecorder
    return nullptr;
}

float IsoGameCharacter::getMeleeDelay() {
    // TODO: Implement getMeleeDelay
    return 0;
}

void IsoGameCharacter::setMeleeDelay(float var1) {
    // TODO: Implement setMeleeDelay
}

float IsoGameCharacter::getRecoilDelay() {
    // TODO: Implement getRecoilDelay
    return 0;
}

void IsoGameCharacter::setRecoilDelay(float var1) {
    // TODO: Implement setRecoilDelay
}

float IsoGameCharacter::getBeenMovingFor() {
    // TODO: Implement getBeenMovingFor
    return 0;
}

void IsoGameCharacter::setBeenMovingFor(float var1) {
    // TODO: Implement setBeenMovingFor
}

bool IsoGameCharacter::isForceShove() {
    // TODO: Implement isForceShove
    return false;
}

void IsoGameCharacter::setForceShove(bool var1) {
    // TODO: Implement setForceShove
}

std::string IsoGameCharacter::getClickSound() {
    // TODO: Implement getClickSound
    return "";
}

void IsoGameCharacter::setClickSound(const std::string& var1) {
    // TODO: Implement setClickSound
}

int IsoGameCharacter::getMeleeCombatMod() {
    // TODO: Implement getMeleeCombatMod
    return 0;
}

int IsoGameCharacter::getWeaponLevel() {
    // TODO: Implement getWeaponLevel
    return 0;
}

int IsoGameCharacter::getMaintenanceMod() {
    // TODO: Implement getMaintenanceMod
    return 0;
}

BaseVehicle IsoGameCharacter::getVehicle() {
    // TODO: Implement getVehicle
    return nullptr;
}

void IsoGameCharacter::setVehicle(BaseVehicle var1) {
    // TODO: Implement setVehicle
}

bool IsoGameCharacter::isUnderVehicle() {
    // TODO: Implement isUnderVehicle
    return false;
}

bool IsoGameCharacter::isProne() {
    // TODO: Implement isProne
    return false;
}

bool IsoGameCharacter::isBeingSteppedOn() {
    // TODO: Implement isBeingSteppedOn
    return false;
}

float IsoGameCharacter::getTemperature() {
    // TODO: Implement getTemperature
    return 0;
}

void IsoGameCharacter::setTemperature(float var1) {
    // TODO: Implement setTemperature
}

float IsoGameCharacter::getReduceInfectionPower() {
    // TODO: Implement getReduceInfectionPower
    return 0;
}

void IsoGameCharacter::setReduceInfectionPower(float var1) {
    // TODO: Implement setReduceInfectionPower
}

float IsoGameCharacter::getInventoryWeight() {
    // TODO: Implement getInventoryWeight
    return 0;
}

void IsoGameCharacter::dropHandItems() {
    // TODO: Implement dropHandItems
}

bool IsoGameCharacter::shouldBecomeZombieAfterDeath() {
    // TODO: Implement shouldBecomeZombieAfterDeath
    return false;
}

void IsoGameCharacter::applyTraits(std::vector<std::string> var1) {
    // TODO: Implement applyTraits
}

void IsoGameCharacter::createKeyRing() {
    // TODO: Implement createKeyRing
}

void IsoGameCharacter::autoDrink() {
    // TODO: Implement autoDrink
}

InventoryItem IsoGameCharacter::getWaterSource(std::vector<InventoryItem> var1) {
    // TODO: Implement getWaterSource
    return nullptr;
}

new IsoGameCharacter::std::vector() {
    // TODO: Implement std::vector
    return nullptr;
}

bool IsoGameCharacter::isRecipeKnown(Recipe var1) {
    // TODO: Implement isRecipeKnown
    return false;
}

bool IsoGameCharacter::isRecipeKnown(const std::string& var1) {
    // TODO: Implement isRecipeKnown
    return false;
}

bool IsoGameCharacter::learnRecipe(const std::string& var1) {
    // TODO: Implement learnRecipe
    return false;
}

void IsoGameCharacter::addKnownMediaLine(const std::string& var1) {
    // TODO: Implement addKnownMediaLine
}

void IsoGameCharacter::removeKnownMediaLine(const std::string& var1) {
    // TODO: Implement removeKnownMediaLine
}

void IsoGameCharacter::clearKnownMediaLines() {
    // TODO: Implement clearKnownMediaLines
}

bool IsoGameCharacter::isKnownMediaLine(const std::string& var1) {
    // TODO: Implement isKnownMediaLine
    return false;
}

void IsoGameCharacter::saveKnownMediaLines(ByteBuffer var1) {
    // TODO: Implement saveKnownMediaLines
}

void IsoGameCharacter::loadKnownMediaLines(ByteBuffer var1, int var2) {
    // TODO: Implement loadKnownMediaLines
}

bool IsoGameCharacter::isMoving() {
    // TODO: Implement isMoving
    return false;
}

bool IsoGameCharacter::isBehaviourMoving() {
    // TODO: Implement isBehaviourMoving
    return false;
}

bool IsoGameCharacter::isPlayerMoving() {
    // TODO: Implement isPlayerMoving
    return false;
}

void IsoGameCharacter::setMoving(bool var1) {
    // TODO: Implement setMoving
}

bool IsoGameCharacter::isFacingNorthWesterly() {
    // TODO: Implement isFacingNorthWesterly
    return false;
}

bool IsoGameCharacter::isAttacking() {
    // TODO: Implement isAttacking
    return false;
}

bool IsoGameCharacter::isZombieAttacking() {
    // TODO: Implement isZombieAttacking
    return false;
}

bool IsoGameCharacter::isZombieAttacking(IsoMovingObject var1) {
    // TODO: Implement isZombieAttacking
    return false;
}

bool IsoGameCharacter::isZombieThumping() {
    // TODO: Implement isZombieThumping
    return false;
}

int IsoGameCharacter::compareMovePriority(IsoGameCharacter var1) {
    // TODO: Implement compareMovePriority
    return 0;
}

long IsoGameCharacter::playSound(const std::string& var1) {
    // TODO: Implement playSound
    return 0;
}

long IsoGameCharacter::playSoundLocal(const std::string& var1) {
    // TODO: Implement playSoundLocal
    return 0;
}

void IsoGameCharacter::stopOrTriggerSound(long var1) {
    // TODO: Implement stopOrTriggerSound
}

void IsoGameCharacter::addWorldSoundUnlessInvisible(int var1, int var2, bool var3) {
    // TODO: Implement addWorldSoundUnlessInvisible
}

bool IsoGameCharacter::isKnownPoison(InventoryItem var1) {
    // TODO: Implement isKnownPoison
    return false;
}

int IsoGameCharacter::getLastHourSleeped() {
    // TODO: Implement getLastHourSleeped
    return 0;
}

void IsoGameCharacter::setLastHourSleeped(int var1) {
    // TODO: Implement setLastHourSleeped
}

void IsoGameCharacter::setTimeOfSleep(float var1) {
    // TODO: Implement setTimeOfSleep
}

void IsoGameCharacter::setDelayToSleep(float var1) {
    // TODO: Implement setDelayToSleep
}

std::string IsoGameCharacter::getBedType() {
    // TODO: Implement getBedType
    return "";
}

void IsoGameCharacter::setBedType(const std::string& var1) {
    // TODO: Implement setBedType
}

void IsoGameCharacter::enterVehicle(BaseVehicle var1, int var2, Vector3f var3) {
    // TODO: Implement enterVehicle
}

float IsoGameCharacter::Hit(BaseVehicle var1, float var2, bool var3, float var4, float var5) {
    // TODO: Implement Hit
    return 0;
}

Path IsoGameCharacter::getPath2() {
    // TODO: Implement getPath2
    return nullptr;
}

void IsoGameCharacter::setPath2(Path var1) {
    // TODO: Implement setPath2
}

PathFindBehavior2 IsoGameCharacter::getPathFindBehavior2() {
    // TODO: Implement getPathFindBehavior2
    return nullptr;
}

MapKnowledge IsoGameCharacter::getMapKnowledge() {
    // TODO: Implement getMapKnowledge
    return nullptr;
}

IsoObject IsoGameCharacter::getBed() {
    // TODO: Implement getBed
    return nullptr;
}

void IsoGameCharacter::setBed(IsoObject var1) {
    // TODO: Implement setBed
}

bool IsoGameCharacter::avoidDamage() {
    // TODO: Implement avoidDamage
    return false;
}

void IsoGameCharacter::setAvoidDamage(bool var1) {
    // TODO: Implement setAvoidDamage
}

bool IsoGameCharacter::isReading() {
    // TODO: Implement isReading
    return false;
}

void IsoGameCharacter::setReading(bool var1) {
    // TODO: Implement setReading
}

float IsoGameCharacter::getTimeSinceLastSmoke() {
    // TODO: Implement getTimeSinceLastSmoke
    return 0;
}

void IsoGameCharacter::setTimeSinceLastSmoke(float var1) {
    // TODO: Implement setTimeSinceLastSmoke
}

bool IsoGameCharacter::isInvisible() {
    // TODO: Implement isInvisible
    return false;
}

void IsoGameCharacter::setInvisible(bool var1) {
    // TODO: Implement setInvisible
}

bool IsoGameCharacter::isDriving() {
    // TODO: Implement isDriving
    return false;
}

bool IsoGameCharacter::isInARoom() {
    // TODO: Implement isInARoom
    return false;
}

bool IsoGameCharacter::isGodMod() {
    // TODO: Implement isGodMod
    return false;
}

void IsoGameCharacter::setGodMod(bool var1) {
    // TODO: Implement setGodMod
}

bool IsoGameCharacter::isUnlimitedCarry() {
    // TODO: Implement isUnlimitedCarry
    return false;
}

void IsoGameCharacter::setUnlimitedCarry(bool var1) {
    // TODO: Implement setUnlimitedCarry
}

bool IsoGameCharacter::isBuildCheat() {
    // TODO: Implement isBuildCheat
    return false;
}

void IsoGameCharacter::setBuildCheat(bool var1) {
    // TODO: Implement setBuildCheat
}

bool IsoGameCharacter::isFarmingCheat() {
    // TODO: Implement isFarmingCheat
    return false;
}

void IsoGameCharacter::setFarmingCheat(bool var1) {
    // TODO: Implement setFarmingCheat
}

bool IsoGameCharacter::isHealthCheat() {
    // TODO: Implement isHealthCheat
    return false;
}

void IsoGameCharacter::setHealthCheat(bool var1) {
    // TODO: Implement setHealthCheat
}

bool IsoGameCharacter::isMechanicsCheat() {
    // TODO: Implement isMechanicsCheat
    return false;
}

void IsoGameCharacter::setMechanicsCheat(bool var1) {
    // TODO: Implement setMechanicsCheat
}

bool IsoGameCharacter::isMovablesCheat() {
    // TODO: Implement isMovablesCheat
    return false;
}

void IsoGameCharacter::setMovablesCheat(bool var1) {
    // TODO: Implement setMovablesCheat
}

bool IsoGameCharacter::isTimedActionInstantCheat() {
    // TODO: Implement isTimedActionInstantCheat
    return false;
}

void IsoGameCharacter::setTimedActionInstantCheat(bool var1) {
    // TODO: Implement setTimedActionInstantCheat
}

bool IsoGameCharacter::isTimedActionInstant() {
    // TODO: Implement isTimedActionInstant
    return false;
}

bool IsoGameCharacter::isShowAdminTag() {
    // TODO: Implement isShowAdminTag
    return false;
}

void IsoGameCharacter::setShowAdminTag(bool var1) {
    // TODO: Implement setShowAdminTag
}

IAnimationVariableSlot IsoGameCharacter::getVariable(AnimationVariableHandle var1) {
    // TODO: Implement getVariable
    return nullptr;
}

IAnimationVariableSlot IsoGameCharacter::getVariable(const std::string& var1) {
    // TODO: Implement getVariable
    return nullptr;
}

IAnimationVariableSlot IsoGameCharacter::getOrCreateVariable(const std::string& var1) {
    // TODO: Implement getOrCreateVariable
    return nullptr;
}

void IsoGameCharacter::setVariable(IAnimationVariableSlot var1) {
    // TODO: Implement setVariable
}

void IsoGameCharacter::setVariable(const std::string& var1, const std::string& var2) {
    // TODO: Implement setVariable
}

void IsoGameCharacter::setVariable(const std::string& var1, bool var2) {
    // TODO: Implement setVariable
}

void IsoGameCharacter::setVariable(const std::string& var1, float var2) {
    // TODO: Implement setVariable
}

void IsoGameCharacter::setVariable(const std::string& var1, zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackBool.CallbackGetStrongTyped var2) {
    // TODO: Implement setVariable
}

void IsoGameCharacter::setVariable(const std::string& var1, zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackString.CallbackGetStrongTyped var2) {
    // TODO: Implement setVariable
}

void IsoGameCharacter::setVariable(const std::string& var1, CallbackGetStrongTyped var2) {
    // TODO: Implement setVariable
}

void IsoGameCharacter::setVariable(const std::string& var1, zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackInt.CallbackGetStrongTyped var2) {
    // TODO: Implement setVariable
}

void IsoGameCharacter::setVariable(const std::string& var1, bool var2, zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackBool.CallbackGetStrongTyped var3) {
    // TODO: Implement setVariable
}

void IsoGameCharacter::setVariable(const std::string& var1, const std::string& var2, zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackString.CallbackGetStrongTyped var3) {
    // TODO: Implement setVariable
}

void IsoGameCharacter::setVariable(const std::string& var1, float var2, CallbackGetStrongTyped var3) {
    // TODO: Implement setVariable
}

void IsoGameCharacter::setVariable(const std::string& var1, int var2, zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackInt.CallbackGetStrongTyped var3) {
    // TODO: Implement setVariable
}

void IsoGameCharacter::clearVariable(const std::string& var1) {
    // TODO: Implement clearVariable
}

void IsoGameCharacter::clearVariables() {
    // TODO: Implement clearVariables
}

std::string IsoGameCharacter::getVariableString(const std::string& var1) {
    // TODO: Implement getVariableString
    return "";
}

std::string IsoGameCharacter::getFootInjuryType() {
    // TODO: Implement getFootInjuryType
    return "";
}

float IsoGameCharacter::getVariableFloat(const std::string& var1, float var2) {
    // TODO: Implement getVariableFloat
    return 0;
}

bool IsoGameCharacter::getVariableBoolean(const std::string& var1) {
    // TODO: Implement getVariableBoolean
    return false;
}

bool IsoGameCharacter::getVariableBoolean(const std::string& var1, bool var2) {
    // TODO: Implement getVariableBoolean
    return false;
}

bool IsoGameCharacter::isVariable(const std::string& var1, const std::string& var2) {
    // TODO: Implement isVariable
    return false;
}

bool IsoGameCharacter::containsVariable(const std::string& var1) {
    // TODO: Implement containsVariable
    return false;
}

AnimationVariableSource IsoGameCharacter::getGameVariablesInternal() {
    // TODO: Implement getGameVariablesInternal
    return nullptr;
}

AnimationVariableSource IsoGameCharacter::startPlaybackGameVariables() {
    // TODO: Implement startPlaybackGameVariables
    return nullptr;
}

void IsoGameCharacter::endPlaybackGameVariables(AnimationVariableSource var1) {
    // TODO: Implement endPlaybackGameVariables
}

void IsoGameCharacter::playbackSetCurrentStateSnapshot(ActionStateSnapshot var1) {
    // TODO: Implement playbackSetCurrentStateSnapshot
}

ActionStateSnapshot IsoGameCharacter::playbackRecordCurrentStateSnapshot() {
    // TODO: Implement playbackRecordCurrentStateSnapshot
    return nullptr;
}

std::string IsoGameCharacter::GetVariable(const std::string& var1) {
    // TODO: Implement GetVariable
    return "";
}

void IsoGameCharacter::SetVariable(const std::string& var1, const std::string& var2) {
    // TODO: Implement SetVariable
}

void IsoGameCharacter::ClearVariable(const std::string& var1) {
    // TODO: Implement ClearVariable
}

void IsoGameCharacter::actionStateChanged(ActionContext var1) {
    // TODO: Implement actionStateChanged
}

bool IsoGameCharacter::isFallOnFront() {
    // TODO: Implement isFallOnFront
    return false;
}

void IsoGameCharacter::setFallOnFront(bool var1) {
    // TODO: Implement setFallOnFront
}

bool IsoGameCharacter::isHitFromBehind() {
    // TODO: Implement isHitFromBehind
    return false;
}

void IsoGameCharacter::setHitFromBehind(bool var1) {
    // TODO: Implement setHitFromBehind
}

void IsoGameCharacter::reportEvent(const std::string& var1) {
    // TODO: Implement reportEvent
}

void IsoGameCharacter::StartTimedActionAnim(const std::string& var1) {
    // TODO: Implement StartTimedActionAnim
}

void IsoGameCharacter::StartTimedActionAnim(const std::string& var1, const std::string& var2) {
    // TODO: Implement StartTimedActionAnim
}

void IsoGameCharacter::StopTimedActionAnim() {
    // TODO: Implement StopTimedActionAnim
}

bool IsoGameCharacter::hasHitReaction() {
    // TODO: Implement hasHitReaction
    return false;
}

std::string IsoGameCharacter::getHitReaction() {
    // TODO: Implement getHitReaction
    return "";
}

void IsoGameCharacter::setHitReaction(const std::string& var1) {
    // TODO: Implement setHitReaction
}

void IsoGameCharacter::CacheEquipped() {
    // TODO: Implement CacheEquipped
}

InventoryItem IsoGameCharacter::GetPrimaryEquippedCache() {
    // TODO: Implement GetPrimaryEquippedCache
    return nullptr;
}

InventoryItem IsoGameCharacter::GetSecondaryEquippedCache() {
    // TODO: Implement GetSecondaryEquippedCache
    return nullptr;
}

void IsoGameCharacter::ClearEquippedCache() {
    // TODO: Implement ClearEquippedCache
}

bool IsoGameCharacter::isBehind(IsoGameCharacter var1) {
    // TODO: Implement isBehind
    return false;
}

void IsoGameCharacter::resetEquippedHandsModels() {
    // TODO: Implement resetEquippedHandsModels
}

AnimatorDebugMonitor IsoGameCharacter::getDebugMonitor() {
    // TODO: Implement getDebugMonitor
    return nullptr;
}

void IsoGameCharacter::setDebugMonitor(AnimatorDebugMonitor var1) {
    // TODO: Implement setDebugMonitor
}

bool IsoGameCharacter::isAimAtFloor() {
    // TODO: Implement isAimAtFloor
    return false;
}

void IsoGameCharacter::setAimAtFloor(bool var1) {
    // TODO: Implement setAimAtFloor
}

std::string IsoGameCharacter::testDotSide(IsoMovingObject var1) {
    // TODO: Implement testDotSide
    return "";
}

void IsoGameCharacter::addBasicPatch(BloodBodyPartType var1) {
    // TODO: Implement addBasicPatch
}

bool IsoGameCharacter::addHole(BloodBodyPartType var1) {
    // TODO: Implement addHole
    return false;
}

bool IsoGameCharacter::addHole(BloodBodyPartType var1, bool var2) {
    // TODO: Implement addHole
    return false;
}

void IsoGameCharacter::addDirt(BloodBodyPartType var1, int var2, bool var3) {
    // TODO: Implement addDirt
}

void IsoGameCharacter::addBlood(BloodBodyPartType var1, bool var2, bool var3, bool var4) {
    // TODO: Implement addBlood
}

float IsoGameCharacter::getBodyPartClothingDefense(int var1, bool var2, bool var3) {
    // TODO: Implement getBodyPartClothingDefense
    return 0;
}

bool IsoGameCharacter::isBumped() {
    // TODO: Implement isBumped
    return false;
}

bool IsoGameCharacter::isBumpDone() {
    // TODO: Implement isBumpDone
    return false;
}

void IsoGameCharacter::setBumpDone(bool var1) {
    // TODO: Implement setBumpDone
}

bool IsoGameCharacter::isBumpFall() {
    // TODO: Implement isBumpFall
    return false;
}

void IsoGameCharacter::setBumpFall(bool var1) {
    // TODO: Implement setBumpFall
}

bool IsoGameCharacter::isBumpStaggered() {
    // TODO: Implement isBumpStaggered
    return false;
}

void IsoGameCharacter::setBumpStaggered(bool var1) {
    // TODO: Implement setBumpStaggered
}

std::string IsoGameCharacter::getBumpType() {
    // TODO: Implement getBumpType
    return "";
}

void IsoGameCharacter::setBumpType(const std::string& var1) {
    // TODO: Implement setBumpType
}

std::string IsoGameCharacter::getBumpFallType() {
    // TODO: Implement getBumpFallType
    return "";
}

void IsoGameCharacter::setBumpFallType(const std::string& var1) {
    // TODO: Implement setBumpFallType
}

IsoGameCharacter IsoGameCharacter::getBumpedChr() {
    // TODO: Implement getBumpedChr
    return nullptr;
}

void IsoGameCharacter::setBumpedChr(IsoGameCharacter var1) {
    // TODO: Implement setBumpedChr
}

long IsoGameCharacter::getLastBump() {
    // TODO: Implement getLastBump
    return 0;
}

void IsoGameCharacter::setLastBump(long var1) {
    // TODO: Implement setLastBump
}

bool IsoGameCharacter::isSitOnGround() {
    // TODO: Implement isSitOnGround
    return false;
}

void IsoGameCharacter::setSitOnGround(bool var1) {
    // TODO: Implement setSitOnGround
}

std::string IsoGameCharacter::getUID() {
    // TODO: Implement getUID
    return "";
}

bool IsoGameCharacter::isRunning() {
    // TODO: Implement isRunning
    return false;
}

void IsoGameCharacter::setRunning(bool var1) {
    // TODO: Implement setRunning
}

bool IsoGameCharacter::isSprinting() {
    // TODO: Implement isSprinting
    return false;
}

void IsoGameCharacter::setSprinting(bool var1) {
    // TODO: Implement setSprinting
}

bool IsoGameCharacter::canSprint() {
    // TODO: Implement canSprint
    return false;
}

void IsoGameCharacter::postUpdateModelTextures() {
    // TODO: Implement postUpdateModelTextures
}

ModelInstanceTextureCreator IsoGameCharacter::getTextureCreator() {
    // TODO: Implement getTextureCreator
    return nullptr;
}

void IsoGameCharacter::setTextureCreator(ModelInstanceTextureCreator var1) {
    // TODO: Implement setTextureCreator
}

void IsoGameCharacter::postUpdateEquippedTextures() {
    // TODO: Implement postUpdateEquippedTextures
}

bool IsoGameCharacter::getIgnoreMovement() {
    // TODO: Implement getIgnoreMovement
    return false;
}

void IsoGameCharacter::setIgnoreMovement(bool var1) {
    // TODO: Implement setIgnoreMovement
}

bool IsoGameCharacter::isAutoWalk() {
    // TODO: Implement isAutoWalk
    return false;
}

void IsoGameCharacter::setAutoWalk(bool var1) {
    // TODO: Implement setAutoWalk
}

void IsoGameCharacter::setAutoWalkDirection(Vector2 var1) {
    // TODO: Implement setAutoWalkDirection
}

Vector2 IsoGameCharacter::getAutoWalkDirection() {
    // TODO: Implement getAutoWalkDirection
    return nullptr;
}

bool IsoGameCharacter::isSneaking() {
    // TODO: Implement isSneaking
    return false;
}

void IsoGameCharacter::setSneaking(bool var1) {
    // TODO: Implement setSneaking
}

GameCharacterAIBrain IsoGameCharacter::getGameCharacterAIBrain() {
    // TODO: Implement getGameCharacterAIBrain
    return nullptr;
}

float IsoGameCharacter::getMoveDelta() {
    // TODO: Implement getMoveDelta
    return 0;
}

void IsoGameCharacter::setMoveDelta(float var1) {
    // TODO: Implement setMoveDelta
}

float IsoGameCharacter::getTurnDelta() {
    // TODO: Implement getTurnDelta
    return 0;
}

void IsoGameCharacter::setTurnDelta(float var1) {
    // TODO: Implement setTurnDelta
}

float IsoGameCharacter::getChopTreeSpeed() {
    // TODO: Implement getChopTreeSpeed
    return 0;
}

bool IsoGameCharacter::testDefense(IsoZombie var1) {
    // TODO: Implement testDefense
    return false;
}

int IsoGameCharacter::getSurroundingAttackingZombies() {
    // TODO: Implement getSurroundingAttackingZombies
    return 0;
}

float IsoGameCharacter::checkIsNearWall() {
    // TODO: Implement checkIsNearWall
    return 0;
}

float IsoGameCharacter::getBeenSprintingFor() {
    // TODO: Implement getBeenSprintingFor
    return 0;
}

void IsoGameCharacter::setBeenSprintingFor(float var1) {
    // TODO: Implement setBeenSprintingFor
}

bool IsoGameCharacter::isHideWeaponModel() {
    // TODO: Implement isHideWeaponModel
    return false;
}

void IsoGameCharacter::setHideWeaponModel(bool var1) {
    // TODO: Implement setHideWeaponModel
}

void IsoGameCharacter::setIsAiming(bool var1) {
    // TODO: Implement setIsAiming
}

bool IsoGameCharacter::isAiming() {
    // TODO: Implement isAiming
    return false;
}

void IsoGameCharacter::resetBeardGrowingTime() {
    // TODO: Implement resetBeardGrowingTime
}

void IsoGameCharacter::resetHairGrowingTime() {
    // TODO: Implement resetHairGrowingTime
}

void IsoGameCharacter::fallenOnKnees() {
    // TODO: Implement fallenOnKnees
}

void IsoGameCharacter::addVisualDamage(const std::string& var1) {
    // TODO: Implement addVisualDamage
}

ItemVisual IsoGameCharacter::addBodyVisualFromItemType(const std::string& var1) {
    // TODO: Implement addBodyVisualFromItemType
    return nullptr;
}

ItemVisual IsoGameCharacter::addBodyVisualFromClothingItemName(const std::string& var1) {
    // TODO: Implement addBodyVisualFromClothingItemName
    return nullptr;
}

bool IsoGameCharacter::isDuplicateBodyVisual(ItemVisual var1) {
    // TODO: Implement isDuplicateBodyVisual
    return false;
}

bool IsoGameCharacter::isCriticalHit() {
    // TODO: Implement isCriticalHit
    return false;
}

void IsoGameCharacter::setCriticalHit(bool var1) {
    // TODO: Implement setCriticalHit
}

float IsoGameCharacter::getRunSpeedModifier() {
    // TODO: Implement getRunSpeedModifier
    return 0;
}

void IsoGameCharacter::startMuzzleFlash() {
    // TODO: Implement startMuzzleFlash
}

bool IsoGameCharacter::isMuzzleFlash() {
    // TODO: Implement isMuzzleFlash
    return false;
}

bool IsoGameCharacter::isNPC() {
    // TODO: Implement isNPC
    return false;
}

void IsoGameCharacter::setNPC(bool var1) {
    // TODO: Implement setNPC
}

void IsoGameCharacter::NPCSetRunning(bool var1) {
    // TODO: Implement NPCSetRunning
}

bool IsoGameCharacter::NPCGetRunning() {
    // TODO: Implement NPCGetRunning
    return false;
}

void IsoGameCharacter::NPCSetJustMoved(bool var1) {
    // TODO: Implement NPCSetJustMoved
}

void IsoGameCharacter::NPCSetAiming(bool var1) {
    // TODO: Implement NPCSetAiming
}

bool IsoGameCharacter::NPCGetAiming() {
    // TODO: Implement NPCGetAiming
    return false;
}

void IsoGameCharacter::NPCSetAttack(bool var1) {
    // TODO: Implement NPCSetAttack
}

void IsoGameCharacter::NPCSetMelee(bool var1) {
    // TODO: Implement NPCSetMelee
}

void IsoGameCharacter::setMetabolicTarget(Metabolics var1) {
    // TODO: Implement setMetabolicTarget
}

void IsoGameCharacter::setMetabolicTarget(float var1) {
    // TODO: Implement setMetabolicTarget
}

double IsoGameCharacter::getThirstMultiplier() {
    // TODO: Implement getThirstMultiplier
    return 0;
}

double IsoGameCharacter::getHungerMultiplier() {
    // TODO: Implement getHungerMultiplier
    return 0;
}

double IsoGameCharacter::getFatiqueMultiplier() {
    // TODO: Implement getFatiqueMultiplier
    return 0;
}

float IsoGameCharacter::getTimedActionTimeModifier() {
    // TODO: Implement getTimedActionTimeModifier
    return 0;
}

bool IsoGameCharacter::addHoleFromZombieAttacks(BloodBodyPartType var1, bool var2) {
    // TODO: Implement addHoleFromZombieAttacks
    return false;
}

void IsoGameCharacter::updateBandages() {
    // TODO: Implement updateBandages
}

float IsoGameCharacter::getTotalBlood() {
    // TODO: Implement getTotalBlood
    return 0;
}

void IsoGameCharacter::attackFromWindowsLunge(IsoZombie var1) {
    // TODO: Implement attackFromWindowsLunge
}

bool IsoGameCharacter::DoSwingCollisionBoneCheck(IsoGameCharacter var1, int var2, float var3) {
    // TODO: Implement DoSwingCollisionBoneCheck
    return false;
}

bool IsoGameCharacter::isInvincible() {
    // TODO: Implement isInvincible
    return false;
}

void IsoGameCharacter::setInvincible(bool var1) {
    // TODO: Implement setInvincible
}

BaseVehicle IsoGameCharacter::getNearVehicle() {
    // TODO: Implement getNearVehicle
    return nullptr;
}

IsoGridSquare IsoGameCharacter::getSolidFloorAt(int var1, int var2, int var3) {
    // TODO: Implement getSolidFloorAt
    return nullptr;
}

void IsoGameCharacter::dropHeavyItems() {
    // TODO: Implement dropHeavyItems
}

bool IsoGameCharacter::isHeavyItem(InventoryItem var1) {
    // TODO: Implement isHeavyItem
    return false;
}

bool IsoGameCharacter::isCanShout() {
    // TODO: Implement isCanShout
    return false;
}

void IsoGameCharacter::setCanShout(bool var1) {
    // TODO: Implement setCanShout
}

bool IsoGameCharacter::isUnlimitedEndurance() {
    // TODO: Implement isUnlimitedEndurance
    return false;
}

void IsoGameCharacter::setUnlimitedEndurance(bool var1) {
    // TODO: Implement setUnlimitedEndurance
}

void IsoGameCharacter::addActiveLightItem(InventoryItem var1, std::vector<InventoryItem> var2) {
    // TODO: Implement addActiveLightItem
}

SleepingEventData IsoGameCharacter::getOrCreateSleepingEventData() {
    // TODO: Implement getOrCreateSleepingEventData
    return nullptr;
}

void IsoGameCharacter::playEmote(const std::string& var1) {
    // TODO: Implement playEmote
}

std::string IsoGameCharacter::getAnimationStateName() {
    // TODO: Implement getAnimationStateName
    return "";
}

std::string IsoGameCharacter::getActionStateName() {
    // TODO: Implement getActionStateName
    return "";
}

bool IsoGameCharacter::shouldWaitToStartTimedAction() {
    // TODO: Implement shouldWaitToStartTimedAction
    return false;
}

void IsoGameCharacter::setPersistentOutfitID(int var1) {
    // TODO: Implement setPersistentOutfitID
}

void IsoGameCharacter::setPersistentOutfitID(int var1, bool var2) {
    // TODO: Implement setPersistentOutfitID
}

int IsoGameCharacter::getPersistentOutfitID() {
    // TODO: Implement getPersistentOutfitID
    return 0;
}

bool IsoGameCharacter::isPersistentOutfitInit() {
    // TODO: Implement isPersistentOutfitInit
    return false;
}

bool IsoGameCharacter::isDoingActionThatCanBeCancelled() {
    // TODO: Implement isDoingActionThatCanBeCancelled
    return false;
}

bool IsoGameCharacter::isDoDeathSound() {
    // TODO: Implement isDoDeathSound
    return false;
}

void IsoGameCharacter::setDoDeathSound(bool var1) {
    // TODO: Implement setDoDeathSound
}

void IsoGameCharacter::updateEquippedRadioFreq() {
    // TODO: Implement updateEquippedRadioFreq
}

FMODParameterList IsoGameCharacter::getFMODParameters() {
    // TODO: Implement getFMODParameters
    return nullptr;
}

void IsoGameCharacter::startEvent(long var1, GameSoundClip var3, BitSet var4) {
    // TODO: Implement startEvent
}

void IsoGameCharacter::updateEvent(long var1, GameSoundClip var3) {
    // TODO: Implement updateEvent
}

void IsoGameCharacter::stopEvent(long var1, GameSoundClip var3, BitSet var4) {
    // TODO: Implement stopEvent
}

void IsoGameCharacter::playBloodSplatterSound() {
    // TODO: Implement playBloodSplatterSound
}

void IsoGameCharacter::setIgnoreAimingInput(bool var1) {
    // TODO: Implement setIgnoreAimingInput
}

void IsoGameCharacter::addBlood(float var1) {
    // TODO: Implement addBlood
}

bool IsoGameCharacter::isKnockedDown() {
    // TODO: Implement isKnockedDown
    return false;
}

void IsoGameCharacter::setKnockedDown(bool var1) {
    // TODO: Implement setKnockedDown
}

void IsoGameCharacter::writeInventory(ByteBuffer var1) {
    // TODO: Implement writeInventory
}

std::string IsoGameCharacter::readInventory(ByteBuffer var1) {
    // TODO: Implement readInventory
    return "";
}

void IsoGameCharacter::Kill(IsoGameCharacter var1) {
    // TODO: Implement Kill
}

bool IsoGameCharacter::shouldDoInventory() {
    // TODO: Implement shouldDoInventory
    return false;
}

void IsoGameCharacter::die() {
    // TODO: Implement die
}

void IsoGameCharacter::becomeCorpse() {
    // TODO: Implement becomeCorpse
}

bool IsoGameCharacter::shouldBecomeCorpse() {
    // TODO: Implement shouldBecomeCorpse
    return false;
}

HitReactionNetworkAI IsoGameCharacter::getHitReactionNetworkAI() {
    // TODO: Implement getHitReactionNetworkAI
    return nullptr;
}

NetworkCharacterAI IsoGameCharacter::getNetworkCharacterAI() {
    // TODO: Implement getNetworkCharacterAI
    return nullptr;
}

bool IsoGameCharacter::isLocal() {
    // TODO: Implement isLocal
    return false;
}

bool IsoGameCharacter::isVehicleCollisionActive(BaseVehicle var1) {
    // TODO: Implement isVehicleCollisionActive
    return false;
}

void IsoGameCharacter::doHitByVehicle(BaseVehicle var1, HitVars var2) {
    // TODO: Implement doHitByVehicle
}

bool IsoGameCharacter::isSkipResolveCollision() {
    // TODO: Implement isSkipResolveCollision
    return false;
}

bool IsoGameCharacter::isAttackAnim() {
    // TODO: Implement isAttackAnim
    return false;
}

void IsoGameCharacter::setAttackAnim(bool var1) {
    // TODO: Implement setAttackAnim
}

float IsoGameCharacter::getNextAnimationTranslationLength() {
    // TODO: Implement getNextAnimationTranslationLength
    return 0;
}

float IsoGameCharacter::calcHitDir(IsoGameCharacter var1, HandWeapon var2, Vector2 var3) {
    // TODO: Implement calcHitDir
    return 0;
}

void IsoGameCharacter::calcHitDir(Vector2 var1) {
    // TODO: Implement calcHitDir
}

Safety IsoGameCharacter::getSafety() {
    // TODO: Implement getSafety
    return nullptr;
}

void IsoGameCharacter::setSafety(Safety var1) {
    // TODO: Implement setSafety
}

void IsoGameCharacter::burnCorpse(IsoDeadBody var1) {
    // TODO: Implement burnCorpse
}

} // namespace characters
} // namespace zombie
