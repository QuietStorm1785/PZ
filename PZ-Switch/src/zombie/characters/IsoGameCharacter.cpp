#include "zombie/characters/IsoGameCharacter.h"

namespace zombie {
namespace characters {

public
IsoGameCharacter::IsoGameCharacter(IsoCell cell, float x, float y, float z) {
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

void IsoGameCharacter::dbgRegisterAnimTrackVariable(int int0, int int1) {
 // TODO: Implement dbgRegisterAnimTrackVariable
}

float IsoGameCharacter::getMomentumScalar() {
 // TODO: Implement getMomentumScalar
 return 0;
}

void IsoGameCharacter::setMomentumScalar(float val) {
 // TODO: Implement setMomentumScalar
}

Vector2 IsoGameCharacter::getDeferredMovement(Vector2 out_result) {
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

AnimationTrack IsoGameCharacter::dbgGetAnimTrack(int layerIdx, int trackIdx) {
 // TODO: Implement dbgGetAnimTrack
 return nullptr;
}

std::string IsoGameCharacter::dbgGetAnimTrackName(int layerIdx, int trackIdx) {
 // TODO: Implement dbgGetAnimTrackName
 return "";
}

float IsoGameCharacter::dbgGetAnimTrackTime(int layerIdx, int trackIdx) {
 // TODO: Implement dbgGetAnimTrackTime
 return 0;
}

float IsoGameCharacter::dbgGetAnimTrackWeight(int layerIdx, int trackIdx) {
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

void IsoGameCharacter::setMaxTwist(float degrees) {
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

void IsoGameCharacter::setRangedWeaponEmpty(bool val) {
 // TODO: Implement setRangedWeaponEmpty
}

bool IsoGameCharacter::hasFootInjury() {
 // TODO: Implement hasFootInjury
 return false;
}

bool IsoGameCharacter::isInTrees2(bool ignoreBush) {
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

void IsoGameCharacter::setIsNPC(bool isAI) {
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

void IsoGameCharacter::onAnimPlayerCreated(AnimationPlayer animationPlayer) {
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

void IsoGameCharacter::setAnimForecasted(int timeMs) {
 // TODO: Implement setAnimForecasted
}

void IsoGameCharacter::resetModel() {
 // TODO: Implement resetModel
}

void IsoGameCharacter::resetModelNextFrame() {
 // TODO: Implement resetModelNextFrame
}

void IsoGameCharacter::onTrigger_setClothingToXmlTriggerFile(
 TriggerXmlFile triggerXmlFile) {
 // TODO: Implement onTrigger_setClothingToXmlTriggerFile
}

void IsoGameCharacter::onTrigger_setAnimStateToTriggerFile(
 AnimStateTriggerXmlFile animStateTriggerXmlFile) {
 // TODO: Implement onTrigger_setAnimStateToTriggerFile
}

void IsoGameCharacter::restoreAnimatorStateToActionContext() {
 // TODO: Implement restoreAnimatorStateToActionContext
}

void IsoGameCharacter::clothingItemChanged(const std::string &itemGuid) {
 // TODO: Implement clothingItemChanged
}

void IsoGameCharacter::reloadOutfit() {
 // TODO: Implement reloadOutfit
}

bool IsoGameCharacter::isSceneCulled() {
 // TODO: Implement isSceneCulled
 return false;
}

void IsoGameCharacter::setSceneCulled(bool isCulled) {
 // TODO: Implement setSceneCulled
}

void IsoGameCharacter::onCullStateChanged(ModelManager modelManager,
 bool isCulled) {
 // TODO: Implement onCullStateChanged
}

void IsoGameCharacter::dressInRandomOutfit() {
 // TODO: Implement dressInRandomOutfit
}

void IsoGameCharacter::dressInNamedOutfit(const std::string &outfitName) {
 // TODO: Implement dressInNamedOutfit
}

void IsoGameCharacter::dressInPersistentOutfit(const std::string &outfitName) {
 // TODO: Implement dressInPersistentOutfit
}

void IsoGameCharacter::dressInPersistentOutfitID(int outfitID) {
 // TODO: Implement dressInPersistentOutfitID
}

std::string IsoGameCharacter::getOutfitName() {
 // TODO: Implement getOutfitName
 return "";
}

void IsoGameCharacter::dressInClothingItem(const std::string &itemGUID) {
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

bool IsoGameCharacter::hasItems(const std::string &type, int count) {
 // TODO: Implement hasItems
 return false;
}

int IsoGameCharacter::getLevelUpLevels(int level) {
 // TODO: Implement getLevelUpLevels
 return 0;
}

int IsoGameCharacter::getLevelMaxForXp() {
 // TODO: Implement getLevelMaxForXp
 return 0;
}

int IsoGameCharacter::getXpForLevel(int level) {
 // TODO: Implement getXpForLevel
 return 0;
}

void IsoGameCharacter::DoDeath(HandWeapon weapon, IsoGameCharacter wielder) {
 // TODO: Implement DoDeath
}

void IsoGameCharacter::DoDeath(HandWeapon weapon, IsoGameCharacter wielder,
 bool bGory) {
 // TODO: Implement DoDeath
}

bool IsoGameCharacter::TestIfSeen(int int0) {
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

void IsoGameCharacter::setFollowingTarget(IsoGameCharacter _FollowingTarget) {
 // TODO: Implement setFollowingTarget
}

float IsoGameCharacter::getDangerLevels() {
 // TODO: Implement getDangerLevels
 return 0;
}

void IsoGameCharacter::setDangerLevels(float _dangerLevels) {
 // TODO: Implement setDangerLevels
}

float IsoGameCharacter::getLeaveBodyTimedown() {
 // TODO: Implement getLeaveBodyTimedown
 return 0;
}

void IsoGameCharacter::setLeaveBodyTimedown(float _leaveBodyTimedown) {
 // TODO: Implement setLeaveBodyTimedown
}

bool IsoGameCharacter::isAllowConversation() {
 // TODO: Implement isAllowConversation
 return false;
}

void IsoGameCharacter::setAllowConversation(bool _AllowConversation) {
 // TODO: Implement setAllowConversation
}

float IsoGameCharacter::getReanimateTimer() {
 // TODO: Implement getReanimateTimer
 return 0;
}

void IsoGameCharacter::setReanimateTimer(float _ReanimateTimer) {
 // TODO: Implement setReanimateTimer
}

int IsoGameCharacter::getReanimAnimFrame() {
 // TODO: Implement getReanimAnimFrame
 return 0;
}

void IsoGameCharacter::setReanimAnimFrame(int _ReanimAnimFrame) {
 // TODO: Implement setReanimAnimFrame
}

int IsoGameCharacter::getReanimAnimDelay() {
 // TODO: Implement getReanimAnimDelay
 return 0;
}

void IsoGameCharacter::setReanimAnimDelay(int _ReanimAnimDelay) {
 // TODO: Implement setReanimAnimDelay
}

bool IsoGameCharacter::isReanim() {
 // TODO: Implement isReanim
 return false;
}

void IsoGameCharacter::setReanim(bool _Reanim) {
 // TODO: Implement setReanim
}

bool IsoGameCharacter::isVisibleToNPCs() {
 // TODO: Implement isVisibleToNPCs
 return false;
}

void IsoGameCharacter::setVisibleToNPCs(bool _VisibleToNPCs) {
 // TODO: Implement setVisibleToNPCs
}

int IsoGameCharacter::getDieCount() {
 // TODO: Implement getDieCount
 return 0;
}

void IsoGameCharacter::setDieCount(int _DieCount) {
 // TODO: Implement setDieCount
}

float IsoGameCharacter::getLlx() {
 // TODO: Implement getLlx
 return 0;
}

void IsoGameCharacter::setLlx(float _llx) {
 // TODO: Implement setLlx
}

float IsoGameCharacter::getLly() {
 // TODO: Implement getLly
 return 0;
}

void IsoGameCharacter::setLly(float _lly) {
 // TODO: Implement setLly
}

float IsoGameCharacter::getLlz() {
 // TODO: Implement getLlz
 return 0;
}

void IsoGameCharacter::setLlz(float _llz) {
 // TODO: Implement setLlz
}

int IsoGameCharacter::getRemoteID() {
 // TODO: Implement getRemoteID
 return 0;
}

void IsoGameCharacter::setRemoteID(int _RemoteID) {
 // TODO: Implement setRemoteID
}

int IsoGameCharacter::getNumSurvivorsInVicinity() {
 // TODO: Implement getNumSurvivorsInVicinity
 return 0;
}

void IsoGameCharacter::setNumSurvivorsInVicinity(int _NumSurvivorsInVicinity) {
 // TODO: Implement setNumSurvivorsInVicinity
}

float IsoGameCharacter::getLevelUpMultiplier() {
 // TODO: Implement getLevelUpMultiplier
 return 0;
}

void IsoGameCharacter::setLevelUpMultiplier(float _LevelUpMultiplier) {
 // TODO: Implement setLevelUpMultiplier
}

void IsoGameCharacter::setXp(IsoGameCharacter.XP _xp) {
 // TODO: Implement setXp
}

int IsoGameCharacter::getLastLocalEnemies() {
 // TODO: Implement getLastLocalEnemies
 return 0;
}

void IsoGameCharacter::setLastLocalEnemies(int _LastLocalEnemies) {
 // TODO: Implement setLastLocalEnemies
}

IsoGameCharacter IsoGameCharacter::getAttackedBy() {
 // TODO: Implement getAttackedBy
 return nullptr;
}

void IsoGameCharacter::setAttackedBy(IsoGameCharacter _AttackedBy) {
 // TODO: Implement setAttackedBy
}

bool IsoGameCharacter::isIgnoreStaggerBack() {
 // TODO: Implement isIgnoreStaggerBack
 return false;
}

void IsoGameCharacter::setIgnoreStaggerBack(bool _IgnoreStaggerBack) {
 // TODO: Implement setIgnoreStaggerBack
}

bool IsoGameCharacter::isAttackWasSuperAttack() {
 // TODO: Implement isAttackWasSuperAttack
 return false;
}

void IsoGameCharacter::setAttackWasSuperAttack(bool _AttackWasSuperAttack) {
 // TODO: Implement setAttackWasSuperAttack
}

int IsoGameCharacter::getTimeThumping() {
 // TODO: Implement getTimeThumping
 return 0;
}

void IsoGameCharacter::setTimeThumping(int _TimeThumping) {
 // TODO: Implement setTimeThumping
}

int IsoGameCharacter::getPatienceMax() {
 // TODO: Implement getPatienceMax
 return 0;
}

void IsoGameCharacter::setPatienceMax(int _PatienceMax) {
 // TODO: Implement setPatienceMax
}

int IsoGameCharacter::getPatienceMin() {
 // TODO: Implement getPatienceMin
 return 0;
}

void IsoGameCharacter::setPatienceMin(int _PatienceMin) {
 // TODO: Implement setPatienceMin
}

int IsoGameCharacter::getPatience() {
 // TODO: Implement getPatience
 return 0;
}

void IsoGameCharacter::setPatience(int _Patience) {
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

void IsoGameCharacter::setForwardDirection(Vector2 dir) {
 // TODO: Implement setForwardDirection
}

void IsoGameCharacter::setForwardDirection(float x, float y) {
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

void IsoGameCharacter::setDirectionAngle(float angleDegrees) {
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

Vector2 IsoGameCharacter::getAnimVector(Vector2 out) {
 // TODO: Implement getAnimVector
 return nullptr;
}

float IsoGameCharacter::getLookAngleRadians() {
 // TODO: Implement getLookAngleRadians
 return 0;
}

Vector2 IsoGameCharacter::getLookVector(Vector2 vector2) {
 // TODO: Implement getLookVector
 return nullptr;
}

float IsoGameCharacter::getDotWithForwardDirection(Vector3 bonePos) {
 // TODO: Implement getDotWithForwardDirection
 return 0;
}

float IsoGameCharacter::getDotWithForwardDirection(float targetX,
 float targetY) {
 // TODO: Implement getDotWithForwardDirection
 return 0;
}

bool IsoGameCharacter::isAsleep() {
 // TODO: Implement isAsleep
 return false;
}

void IsoGameCharacter::setAsleep(bool _Asleep) {
 // TODO: Implement setAsleep
}

int IsoGameCharacter::getZombieKills() {
 // TODO: Implement getZombieKills
 return 0;
}

void IsoGameCharacter::setZombieKills(int _ZombieKills) {
 // TODO: Implement setZombieKills
}

int IsoGameCharacter::getLastZombieKills() {
 // TODO: Implement getLastZombieKills
 return 0;
}

void IsoGameCharacter::setLastZombieKills(int _LastZombieKills) {
 // TODO: Implement setLastZombieKills
}

bool IsoGameCharacter::isSuperAttack() {
 // TODO: Implement isSuperAttack
 return false;
}

void IsoGameCharacter::setSuperAttack(bool _superAttack) {
 // TODO: Implement setSuperAttack
}

float IsoGameCharacter::getForceWakeUpTime() {
 // TODO: Implement getForceWakeUpTime
 return 0;
}

void IsoGameCharacter::setForceWakeUpTime(float _ForceWakeUpTime) {
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

void IsoGameCharacter::setDefaultState(State _defaultState) {
 // TODO: Implement setDefaultState
}

SurvivorDesc IsoGameCharacter::getDescriptor() {
 // TODO: Implement getDescriptor
 return nullptr;
}

void IsoGameCharacter::setDescriptor(SurvivorDesc _descriptor) {
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

void IsoGameCharacter::getItemVisuals(ItemVisuals itemVisuals) {
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

void IsoGameCharacter::setFireKillRate(float _FireKillRate) {
 // TODO: Implement setFireKillRate
}

int IsoGameCharacter::getFireSpreadProbability() {
 // TODO: Implement getFireSpreadProbability
 return 0;
}

void IsoGameCharacter::setFireSpreadProbability(int _FireSpreadProbability) {
 // TODO: Implement setFireSpreadProbability
}

float IsoGameCharacter::getHealth() {
 // TODO: Implement getHealth
 return 0;
}

void IsoGameCharacter::setHealth(float _Health) {
 // TODO: Implement setHealth
}

bool IsoGameCharacter::isOnDeathDone() {
 // TODO: Implement isOnDeathDone
 return false;
}

void IsoGameCharacter::setOnDeathDone(bool done) {
 // TODO: Implement setOnDeathDone
}

bool IsoGameCharacter::isOnKillDone() {
 // TODO: Implement isOnKillDone
 return false;
}

void IsoGameCharacter::setOnKillDone(bool done) {
 // TODO: Implement setOnKillDone
}

bool IsoGameCharacter::isDeathDragDown() {
 // TODO: Implement isDeathDragDown
 return false;
}

void IsoGameCharacter::setDeathDragDown(bool dragDown) {
 // TODO: Implement setDeathDragDown
}

bool IsoGameCharacter::isPlayingDeathSound() {
 // TODO: Implement isPlayingDeathSound
 return false;
}

void IsoGameCharacter::setPlayingDeathSound(bool playing) {
 // TODO: Implement setPlayingDeathSound
}

std::string IsoGameCharacter::getHurtSound() {
 // TODO: Implement getHurtSound
 return "";
}

void IsoGameCharacter::setHurtSound(const std::string &_hurtSound) {
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

void IsoGameCharacter::setInventory(ItemContainer _inventory) {
 // TODO: Implement setInventory
}

bool IsoGameCharacter::isPrimaryEquipped(const std::string &item) {
 // TODO: Implement isPrimaryEquipped
 return false;
}

InventoryItem IsoGameCharacter::getPrimaryHandItem() {
 // TODO: Implement getPrimaryHandItem
 return nullptr;
}

void IsoGameCharacter::setPrimaryHandItem(InventoryItem _leftHandItem) {
 // TODO: Implement setPrimaryHandItem
}

void IsoGameCharacter::setEquipParent(InventoryItem item0,
 InventoryItem item1) {
 // TODO: Implement setEquipParent
}

void IsoGameCharacter::initWornItems(const std::string &bodyLocationGroupName) {
 // TODO: Implement initWornItems
}

WornItems IsoGameCharacter::getWornItems() {
 // TODO: Implement getWornItems
 return nullptr;
}

void IsoGameCharacter::setWornItems(WornItems other) {
 // TODO: Implement setWornItems
}

InventoryItem IsoGameCharacter::getWornItem(const std::string &location) {
 // TODO: Implement getWornItem
 return nullptr;
}

void IsoGameCharacter::setWornItem(const std::string &location,
 InventoryItem item) {
 // TODO: Implement setWornItem
}

void IsoGameCharacter::setWornItem(const std::string &location,
 InventoryItem item, bool forceDropTooHeavy) {
 // TODO: Implement setWornItem
}

void IsoGameCharacter::removeWornItem(InventoryItem item) {
 // TODO: Implement removeWornItem
}

void IsoGameCharacter::removeWornItem(InventoryItem item,
 bool forceDropTooHeavy) {
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

void IsoGameCharacter::initAttachedItems(const std::string &groupName) {
 // TODO: Implement initAttachedItems
}

AttachedItems IsoGameCharacter::getAttachedItems() {
 // TODO: Implement getAttachedItems
 return nullptr;
}

void IsoGameCharacter::setAttachedItems(AttachedItems other) {
 // TODO: Implement setAttachedItems
}

InventoryItem IsoGameCharacter::getAttachedItem(const std::string &location) {
 // TODO: Implement getAttachedItem
 return nullptr;
}

void IsoGameCharacter::setAttachedItem(const std::string &location,
 InventoryItem item) {
 // TODO: Implement setAttachedItem
}

void IsoGameCharacter::removeAttachedItem(InventoryItem item) {
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

void IsoGameCharacter::setClothingItem_Head(InventoryItem item) {
 // TODO: Implement setClothingItem_Head
}

InventoryItem IsoGameCharacter::getClothingItem_Torso() {
 // TODO: Implement getClothingItem_Torso
 return nullptr;
}

void IsoGameCharacter::setClothingItem_Torso(InventoryItem item) {
 // TODO: Implement setClothingItem_Torso
}

InventoryItem IsoGameCharacter::getClothingItem_Back() {
 // TODO: Implement getClothingItem_Back
 return nullptr;
}

void IsoGameCharacter::setClothingItem_Back(InventoryItem item) {
 // TODO: Implement setClothingItem_Back
}

InventoryItem IsoGameCharacter::getClothingItem_Hands() {
 // TODO: Implement getClothingItem_Hands
 return nullptr;
}

void IsoGameCharacter::setClothingItem_Hands(InventoryItem item) {
 // TODO: Implement setClothingItem_Hands
}

InventoryItem IsoGameCharacter::getClothingItem_Legs() {
 // TODO: Implement getClothingItem_Legs
 return nullptr;
}

void IsoGameCharacter::setClothingItem_Legs(InventoryItem item) {
 // TODO: Implement setClothingItem_Legs
}

InventoryItem IsoGameCharacter::getClothingItem_Feet() {
 // TODO: Implement getClothingItem_Feet
 return nullptr;
}

void IsoGameCharacter::setClothingItem_Feet(InventoryItem item) {
 // TODO: Implement setClothingItem_Feet
}

int IsoGameCharacter::getNextWander() {
 // TODO: Implement getNextWander
 return 0;
}

void IsoGameCharacter::setNextWander(int _NextWander) {
 // TODO: Implement setNextWander
}

bool IsoGameCharacter::isOnFire() {
 // TODO: Implement isOnFire
 return false;
}

void IsoGameCharacter::setOnFire(bool _OnFire) {
 // TODO: Implement setOnFire
}

void IsoGameCharacter::removeFromWorld() {
 // TODO: Implement removeFromWorld
}

int IsoGameCharacter::getPathIndex() {
 // TODO: Implement getPathIndex
 return 0;
}

void IsoGameCharacter::setPathIndex(int _pathIndex) {
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

void IsoGameCharacter::setSecondaryHandItem(InventoryItem _rightHandItem) {
 // TODO: Implement setSecondaryHandItem
}

bool IsoGameCharacter::isHandItem(InventoryItem item) {
 // TODO: Implement isHandItem
 return false;
}

bool IsoGameCharacter::isPrimaryHandItem(InventoryItem item) {
 // TODO: Implement isPrimaryHandItem
 return false;
}

bool IsoGameCharacter::isSecondaryHandItem(InventoryItem item) {
 // TODO: Implement isSecondaryHandItem
 return false;
}

bool IsoGameCharacter::isItemInBothHands(InventoryItem item) {
 // TODO: Implement isItemInBothHands
 return false;
}

bool IsoGameCharacter::removeFromHands(InventoryItem item) {
 // TODO: Implement removeFromHands
 return false;
}

Color IsoGameCharacter::getSpeakColour() {
 // TODO: Implement getSpeakColour
 return nullptr;
}

void IsoGameCharacter::setSpeakColour(Color _SpeakColour) {
 // TODO: Implement setSpeakColour
}

void IsoGameCharacter::setSpeakColourInfo(ColorInfo info) {
 // TODO: Implement setSpeakColourInfo
}

float IsoGameCharacter::getSlowFactor() {
 // TODO: Implement getSlowFactor
 return 0;
}

void IsoGameCharacter::setSlowFactor(float _slowFactor) {
 // TODO: Implement setSlowFactor
}

float IsoGameCharacter::getSlowTimer() {
 // TODO: Implement getSlowTimer
 return 0;
}

void IsoGameCharacter::setSlowTimer(float _slowTimer) {
 // TODO: Implement setSlowTimer
}

bool IsoGameCharacter::isbUseParts() {
 // TODO: Implement isbUseParts
 return false;
}

void IsoGameCharacter::setbUseParts(bool _bUseParts) {
 // TODO: Implement setbUseParts
}

bool IsoGameCharacter::isSpeaking() {
 // TODO: Implement isSpeaking
 return false;
}

void IsoGameCharacter::setSpeaking(bool _Speaking) {
 // TODO: Implement setSpeaking
}

float IsoGameCharacter::getSpeakTime() {
 // TODO: Implement getSpeakTime
 return 0;
}

void IsoGameCharacter::setSpeakTime(int _SpeakTime) {
 // TODO: Implement setSpeakTime
}

float IsoGameCharacter::getSpeedMod() {
 // TODO: Implement getSpeedMod
 return 0;
}

void IsoGameCharacter::setSpeedMod(float _speedMod) {
 // TODO: Implement setSpeedMod
}

float IsoGameCharacter::getStaggerTimeMod() {
 // TODO: Implement getStaggerTimeMod
 return 0;
}

void IsoGameCharacter::setStaggerTimeMod(float _staggerTimeMod) {
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

void IsoGameCharacter::setUseHandWeapon(HandWeapon _useHandWeapon) {
 // TODO: Implement setUseHandWeapon
}

IsoSprite IsoGameCharacter::getLegsSprite() {
 // TODO: Implement getLegsSprite
 return nullptr;
}

void IsoGameCharacter::setLegsSprite(IsoSprite _legsSprite) {
 // TODO: Implement setLegsSprite
}

IsoGridSquare IsoGameCharacter::getAttackTargetSquare() {
 // TODO: Implement getAttackTargetSquare
 return nullptr;
}

void IsoGameCharacter::setAttackTargetSquare(
 IsoGridSquare _attackTargetSquare) {
 // TODO: Implement setAttackTargetSquare
}

float IsoGameCharacter::getBloodImpactX() {
 // TODO: Implement getBloodImpactX
 return 0;
}

void IsoGameCharacter::setBloodImpactX(float _BloodImpactX) {
 // TODO: Implement setBloodImpactX
}

float IsoGameCharacter::getBloodImpactY() {
 // TODO: Implement getBloodImpactY
 return 0;
}

void IsoGameCharacter::setBloodImpactY(float _BloodImpactY) {
 // TODO: Implement setBloodImpactY
}

float IsoGameCharacter::getBloodImpactZ() {
 // TODO: Implement getBloodImpactZ
 return 0;
}

void IsoGameCharacter::setBloodImpactZ(float _BloodImpactZ) {
 // TODO: Implement setBloodImpactZ
}

IsoSprite IsoGameCharacter::getBloodSplat() {
 // TODO: Implement getBloodSplat
 return nullptr;
}

void IsoGameCharacter::setBloodSplat(IsoSprite _bloodSplat) {
 // TODO: Implement setBloodSplat
}

bool IsoGameCharacter::isbOnBed() {
 // TODO: Implement isbOnBed
 return false;
}

void IsoGameCharacter::setbOnBed(bool _bOnBed) {
 // TODO: Implement setbOnBed
}

Vector2 IsoGameCharacter::getMoveForwardVec() {
 // TODO: Implement getMoveForwardVec
 return nullptr;
}

void IsoGameCharacter::setMoveForwardVec(Vector2 _moveForwardVec) {
 // TODO: Implement setMoveForwardVec
}

bool IsoGameCharacter::isPathing() {
 // TODO: Implement isPathing
 return false;
}

void IsoGameCharacter::setPathing(bool _pathing) {
 // TODO: Implement setPathing
}

TraitCollection IsoGameCharacter::getTraits() {
 // TODO: Implement getTraits
 return nullptr;
}

int IsoGameCharacter::getMaxWeight() {
 // TODO: Implement getMaxWeight
 return 0;
}

void IsoGameCharacter::setMaxWeight(int _maxWeight) {
 // TODO: Implement setMaxWeight
}

int IsoGameCharacter::getMaxWeightBase() {
 // TODO: Implement getMaxWeightBase
 return 0;
}

void IsoGameCharacter::setMaxWeightBase(int _maxWeightBase) {
 // TODO: Implement setMaxWeightBase
}

float IsoGameCharacter::getSleepingTabletDelta() {
 // TODO: Implement getSleepingTabletDelta
 return 0;
}

void IsoGameCharacter::setSleepingTabletDelta(float _SleepingTabletDelta) {
 // TODO: Implement setSleepingTabletDelta
}

float IsoGameCharacter::getBetaEffect() {
 // TODO: Implement getBetaEffect
 return 0;
}

void IsoGameCharacter::setBetaEffect(float _BetaEffect) {
 // TODO: Implement setBetaEffect
}

float IsoGameCharacter::getDepressEffect() {
 // TODO: Implement getDepressEffect
 return 0;
}

void IsoGameCharacter::setDepressEffect(float _DepressEffect) {
 // TODO: Implement setDepressEffect
}

float IsoGameCharacter::getSleepingTabletEffect() {
 // TODO: Implement getSleepingTabletEffect
 return 0;
}

void IsoGameCharacter::setSleepingTabletEffect(float _SleepingTabletEffect) {
 // TODO: Implement setSleepingTabletEffect
}

float IsoGameCharacter::getBetaDelta() {
 // TODO: Implement getBetaDelta
 return 0;
}

void IsoGameCharacter::setBetaDelta(float _BetaDelta) {
 // TODO: Implement setBetaDelta
}

float IsoGameCharacter::getDepressDelta() {
 // TODO: Implement getDepressDelta
 return 0;
}

void IsoGameCharacter::setDepressDelta(float _DepressDelta) {
 // TODO: Implement setDepressDelta
}

float IsoGameCharacter::getPainEffect() {
 // TODO: Implement getPainEffect
 return 0;
}

void IsoGameCharacter::setPainEffect(float _PainEffect) {
 // TODO: Implement setPainEffect
}

float IsoGameCharacter::getPainDelta() {
 // TODO: Implement getPainDelta
 return 0;
}

void IsoGameCharacter::setPainDelta(float _PainDelta) {
 // TODO: Implement setPainDelta
}

bool IsoGameCharacter::isbDoDefer() {
 // TODO: Implement isbDoDefer
 return false;
}

void IsoGameCharacter::setbDoDefer(bool _bDoDefer) {
 // TODO: Implement setbDoDefer
}

void IsoGameCharacter::setLastHeardSound(int x, int y, int z) {
 // TODO: Implement setLastHeardSound
}

float IsoGameCharacter::getLrx() {
 // TODO: Implement getLrx
 return 0;
}

void IsoGameCharacter::setLrx(float _lrx) {
 // TODO: Implement setLrx
}

float IsoGameCharacter::getLry() {
 // TODO: Implement getLry
 return 0;
}

void IsoGameCharacter::setLry(float _lry) {
 // TODO: Implement setLry
}

bool IsoGameCharacter::isClimbing() {
 // TODO: Implement isClimbing
 return false;
}

void IsoGameCharacter::setbClimbing(bool _bClimbing) {
 // TODO: Implement setbClimbing
}

bool IsoGameCharacter::isLastCollidedW() {
 // TODO: Implement isLastCollidedW
 return false;
}

void IsoGameCharacter::setLastCollidedW(bool _lastCollidedW) {
 // TODO: Implement setLastCollidedW
}

bool IsoGameCharacter::isLastCollidedN() {
 // TODO: Implement isLastCollidedN
 return false;
}

void IsoGameCharacter::setLastCollidedN(bool _lastCollidedN) {
 // TODO: Implement setLastCollidedN
}

float IsoGameCharacter::getFallTime() {
 // TODO: Implement getFallTime
 return 0;
}

void IsoGameCharacter::setFallTime(float _fallTime) {
 // TODO: Implement setFallTime
}

float IsoGameCharacter::getLastFallSpeed() {
 // TODO: Implement getLastFallSpeed
 return 0;
}

void IsoGameCharacter::setLastFallSpeed(float _lastFallSpeed) {
 // TODO: Implement setLastFallSpeed
}

bool IsoGameCharacter::isbFalling() {
 // TODO: Implement isbFalling
 return false;
}

void IsoGameCharacter::setbFalling(bool _bFalling) {
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

void IsoGameCharacter::OnAnimEvent(AnimLayer sender, AnimEvent event) {
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

int IsoGameCharacter::getPerkLevel(PerkFactory.Perk perks) {
 // TODO: Implement getPerkLevel
 return 0;
}

void IsoGameCharacter::setPerkLevelDebug(PerkFactory.Perk perks, int level) {
 // TODO: Implement setPerkLevelDebug
}

void IsoGameCharacter::LoseLevel(PerkFactory.Perk perk) {
 // TODO: Implement LoseLevel
}

void IsoGameCharacter::LevelPerk(PerkFactory.Perk perk, bool removePick) {
 // TODO: Implement LevelPerk
}

void IsoGameCharacter::LevelPerk(PerkFactory.Perk perk) {
 // TODO: Implement LevelPerk
}

void IsoGameCharacter::level0(PerkFactory.Perk perk) {
 // TODO: Implement level0
}

void IsoGameCharacter::ReadLiterature(Literature literature) {
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

void IsoGameCharacter::Seen(Stack<IsoMovingObject> SeenList) {
 // TODO: Implement Seen
}

bool IsoGameCharacter::CanSee(IsoMovingObject obj) {
 // TODO: Implement CanSee
 return false;
}

IsoGridSquare IsoGameCharacter::getLowDangerInVicinity(int attempts,
 int range) {
 // TODO: Implement getLowDangerInVicinity
 return nullptr;
}

void IsoGameCharacter::Anger(int amount) {
 // TODO: Implement Anger
}

bool IsoGameCharacter::hasEquipped(const std::string &itemType) {
 // TODO: Implement hasEquipped
 return false;
}

bool IsoGameCharacter::hasEquippedTag(const std::string &tag) {
 // TODO: Implement hasEquippedTag
 return false;
}

void IsoGameCharacter::setDir(IsoDirections directions) {
 // TODO: Implement setDir
}

void IsoGameCharacter::Callout(bool doAnim) {
 // TODO: Implement Callout
}

void IsoGameCharacter::Callout() {
 // TODO: Implement Callout
}

void IsoGameCharacter::load(ByteBuffer input, int WorldVersion,
 bool IS_DEBUG_SAVE) {
 // TODO: Implement load
}

void IsoGameCharacter::save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 // TODO: Implement save
}

ChatElement IsoGameCharacter::getChatElement() {
 // TODO: Implement getChatElement
 return nullptr;
}

void IsoGameCharacter::StartAction(BaseAction act) {
 // TODO: Implement StartAction
}

void IsoGameCharacter::QueueAction(BaseAction act) {
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

void IsoGameCharacter::SleepingTablet(float _SleepingTabletDelta) {
 // TODO: Implement SleepingTablet
}

void IsoGameCharacter::BetaBlockers(float delta) {
 // TODO: Implement BetaBlockers
}

void IsoGameCharacter::BetaAntiDepress(float delta) {
 // TODO: Implement BetaAntiDepress
}

void IsoGameCharacter::PainMeds(float delta) {
 // TODO: Implement PainMeds
}

void IsoGameCharacter::initSpritePartsEmpty() {
 // TODO: Implement initSpritePartsEmpty
}

void IsoGameCharacter::InitSpriteParts(SurvivorDesc desc) {
 // TODO: Implement InitSpriteParts
}

bool IsoGameCharacter::HasTrait(const std::string &trait) {
 // TODO: Implement HasTrait
 return false;
}

void IsoGameCharacter::ApplyInBedOffset(bool apply) {
 // TODO: Implement ApplyInBedOffset
}

void IsoGameCharacter::Dressup(SurvivorDesc desc) {
 // TODO: Implement Dressup
}

void IsoGameCharacter::PlayAnim(const std::string &string) {
 // TODO: Implement PlayAnim
}

void IsoGameCharacter::PlayAnimWithSpeed(const std::string &string,
 float framesSpeedPerFrame) {
 // TODO: Implement PlayAnimWithSpeed
}

void IsoGameCharacter::PlayAnimUnlooped(const std::string &string) {
 // TODO: Implement PlayAnimUnlooped
}

void IsoGameCharacter::DirectionFromVector(Vector2 vecA) {
 // TODO: Implement DirectionFromVector
}

void IsoGameCharacter::DoFootstepSound(const std::string &type) {
 // TODO: Implement DoFootstepSound
}

void IsoGameCharacter::DoFootstepSound(float volume) {
 // TODO: Implement DoFootstepSound
}

bool IsoGameCharacter::Eat(InventoryItem info, float percentage) {
 // TODO: Implement Eat
 return false;
}

bool IsoGameCharacter::Eat(InventoryItem info) {
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

float IsoGameCharacter::getGlobalMovementMod(bool bDoNoises) {
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

bool IsoGameCharacter::HasItem(const std::string &string) {
 // TODO: Implement HasItem
 return false;
}

void IsoGameCharacter::changeState(State state) {
 // TODO: Implement changeState
}

State IsoGameCharacter::getCurrentState() {
 // TODO: Implement getCurrentState
 return nullptr;
}

bool IsoGameCharacter::isCurrentState(State state) {
 // TODO: Implement isCurrentState
 return false;
}

void IsoGameCharacter::setStateMachineLocked(bool val) {
 // TODO: Implement setStateMachineLocked
}

float IsoGameCharacter::Hit(HandWeapon weapon, IsoGameCharacter wielder,
 float damageSplit, bool bIgnoreDamage,
 float modDelta) {
 // TODO: Implement Hit
 return 0;
}

float IsoGameCharacter::Hit(HandWeapon weapon, IsoGameCharacter wielder,
 float damageSplit, bool bIgnoreDamage,
 float modDelta, bool bRemote) {
 // TODO: Implement Hit
 return 0;
}

float IsoGameCharacter::processHitDamage(HandWeapon weapon,
 IsoGameCharacter wielder,
 float damageSplit, bool bIgnoreDamage,
 float modDelta) {
 // TODO: Implement processHitDamage
 return 0;
}

void IsoGameCharacter::hitConsequences(HandWeapon weapon,
 IsoGameCharacter wielder,
 bool bIgnoreDamage, float damage,
 bool bRemote) {
 // TODO: Implement hitConsequences
}

bool IsoGameCharacter::IsAttackRange(float x, float y, float z) {
 // TODO: Implement IsAttackRange
 return false;
}

bool IsoGameCharacter::IsAttackRange(HandWeapon we, IsoMovingObject obj,
 Vector3 bonePos, bool extraRange) {
 // TODO: Implement IsAttackRange
 return false;
}

bool IsoGameCharacter::IsSpeaking() {
 // TODO: Implement IsSpeaking
 return false;
}

void IsoGameCharacter::MoveForward(float dist, float x, float y,
 float soundDelta) {
 // TODO: Implement MoveForward
}

void IsoGameCharacter::pathToAux(float float0, float float1, float float2) {
 // TODO: Implement pathToAux
}

void IsoGameCharacter::pathToCharacter(IsoGameCharacter target) {
 // TODO: Implement pathToCharacter
}

void IsoGameCharacter::pathToLocation(int x, int y, int z) {
 // TODO: Implement pathToLocation
}

void IsoGameCharacter::pathToLocationF(float x, float y, float z) {
 // TODO: Implement pathToLocationF
}

void IsoGameCharacter::pathToSound(int x, int y, int z) {
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

void IsoGameCharacter::render(float x, float y, float z, ColorInfo col,
 bool bDoChild, bool bWallLightingPass,
 Shader shader) {
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

void IsoGameCharacter::renderObjectPicker(float x, float y, float z,
 ColorInfo _lightInfo) {
 // TODO: Implement renderObjectPicker
}

Vector2 IsoGameCharacter::closestpointonline(double double4, double double2,
 double double5, double double1,
 double double9, double double8,
 Vector2 vector) {
 // TODO: Implement closestpointonline
 return nullptr;
}

void IsoGameCharacter::renderShadow(float x, float y, float z) {
 // TODO: Implement renderShadow
}

void IsoGameCharacter::checkUpdateModelTextures() {
 // TODO: Implement checkUpdateModelTextures
}

bool IsoGameCharacter::isMaskClicked(int x, int y, bool flip) {
 // TODO: Implement isMaskClicked
 return false;
}

void IsoGameCharacter::setHaloNote(const std::string &str) {
 // TODO: Implement setHaloNote
}

void IsoGameCharacter::setHaloNote(const std::string &str, float dispTime) {
 // TODO: Implement setHaloNote
}

void IsoGameCharacter::setHaloNote(const std::string &str, int r, int g, int b,
 float dispTime) {
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

void IsoGameCharacter::setSayLine(const std::string &sayLine) {
 // TODO: Implement setSayLine
}

ChatMessage IsoGameCharacter::getLastChatMessage() {
 // TODO: Implement getLastChatMessage
 return nullptr;
}

void IsoGameCharacter::setLastChatMessage(ChatMessage _lastChatMessage) {
 // TODO: Implement setLastChatMessage
}

std::string IsoGameCharacter::getLastSpokenLine() {
 // TODO: Implement getLastSpokenLine
 return "";
}

void IsoGameCharacter::setLastSpokenLine(const std::string &line) {
 // TODO: Implement setLastSpokenLine
}

void IsoGameCharacter::doSleepSpeech() {
 // TODO: Implement doSleepSpeech
}

void IsoGameCharacter::SayDebug(const std::string &text) {
 // TODO: Implement SayDebug
}

void IsoGameCharacter::SayDebug(int n, const std::string &text) {
 // TODO: Implement SayDebug
}

int IsoGameCharacter::getMaxChatLines() {
 // TODO: Implement getMaxChatLines
 return 0;
}

void IsoGameCharacter::Say(const std::string &line) {
 // TODO: Implement Say
}

void IsoGameCharacter::Say(const std::string &line, float r, float g, float b,
 UIFont font, float baseRange,
 const std::string &customTag) {
 // TODO: Implement Say
}

void IsoGameCharacter::SayWhisper(const std::string &line) {
 // TODO: Implement SayWhisper
}

void IsoGameCharacter::SayShout(const std::string &line) {
 // TODO: Implement SayShout
}

void IsoGameCharacter::SayRadio(const std::string &line, float r, float g,
 float b, UIFont font, float baseRange,
 int channel, const std::string &customTag) {
 // TODO: Implement SayRadio
}

void IsoGameCharacter::ProcessSay(const std::string &string0, float float0,
 float float1, float float2, float float3,
 int int0, const std::string &string1) {
 // TODO: Implement ProcessSay
}

void IsoGameCharacter::addLineChatElement(const std::string &line) {
 // TODO: Implement addLineChatElement
}

void IsoGameCharacter::addLineChatElement(const std::string &line, float r,
 float g, float b) {
 // TODO: Implement addLineChatElement
}

void IsoGameCharacter::addLineChatElement(const std::string &line, float r,
 float g, float b, UIFont font,
 float baseRange,
 const std::string &customTag) {
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

void IsoGameCharacter::drawDirectionLine(Vector2 dir, float length, float r,
 float g, float b) {
 // TODO: Implement drawDirectionLine
}

void IsoGameCharacter::drawDebugTextBelow(const std::string &text) {
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

void IsoGameCharacter::Throw(HandWeapon weapon) {
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

void IsoGameCharacter::serverRemoveItemFromZombie(const std::string &item) {
 // TODO: Implement serverRemoveItemFromZombie
}

bool IsoGameCharacter::helmetFall(bool hitHead) {
 // TODO: Implement helmetFall
 return false;
}

bool IsoGameCharacter::helmetFall(bool hitHead, const std::string &forcedItem) {
 // TODO: Implement helmetFall
 return false;
}

void IsoGameCharacter::smashCarWindow(VehiclePart part) {
 // TODO: Implement smashCarWindow
}

void IsoGameCharacter::smashWindow(IsoWindow w) {
 // TODO: Implement smashWindow
}

void IsoGameCharacter::openWindow(IsoWindow w) {
 // TODO: Implement openWindow
}

void IsoGameCharacter::closeWindow(IsoWindow w) {
 // TODO: Implement closeWindow
}

void IsoGameCharacter::climbThroughWindow(IsoWindow w) {
 // TODO: Implement climbThroughWindow
}

void IsoGameCharacter::climbThroughWindow(IsoWindow w, int startingFrame) {
 // TODO: Implement climbThroughWindow
}

bool IsoGameCharacter::isClosingWindow(IsoWindow window) {
 // TODO: Implement isClosingWindow
 return false;
}

bool IsoGameCharacter::isClimbingThroughWindow(IsoWindow window) {
 // TODO: Implement isClimbingThroughWindow
 return false;
}

void IsoGameCharacter::climbThroughWindowFrame(IsoObject obj) {
 // TODO: Implement climbThroughWindowFrame
}

void IsoGameCharacter::climbSheetRope() {
 // TODO: Implement climbSheetRope
}

void IsoGameCharacter::climbDownSheetRope() {
 // TODO: Implement climbDownSheetRope
}

bool IsoGameCharacter::canClimbSheetRope(IsoGridSquare sq) {
 // TODO: Implement canClimbSheetRope
 return false;
}

bool IsoGameCharacter::canClimbDownSheetRopeInCurrentSquare() {
 // TODO: Implement canClimbDownSheetRopeInCurrentSquare
 return false;
}

bool IsoGameCharacter::canClimbDownSheetRope(IsoGridSquare sq) {
 // TODO: Implement canClimbDownSheetRope
 return false;
}

void IsoGameCharacter::climbThroughWindow(IsoThumpable w) {
 // TODO: Implement climbThroughWindow
}

void IsoGameCharacter::climbThroughWindow(IsoThumpable w, int startingFrame) {
 // TODO: Implement climbThroughWindow
}

void IsoGameCharacter::climbOverFence(IsoDirections dir) {
 // TODO: Implement climbOverFence
}

bool IsoGameCharacter::isAboveTopOfStairs() {
 // TODO: Implement isAboveTopOfStairs
 return false;
}

void IsoGameCharacter::preupdate() {
 // TODO: Implement preupdate
}

void IsoGameCharacter::setTeleport(NetworkTeleport _teleport) {
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

void IsoGameCharacter::updateSeenVisibility(int int0) {
 // TODO: Implement updateSeenVisibility
}

void IsoGameCharacter::recursiveItemUpdater(ItemContainer container) {
 // TODO: Implement recursiveItemUpdater
}

void IsoGameCharacter::recursiveItemUpdater(
 InventoryContainer inventoryContainer) {
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

float IsoGameCharacter::calcRunSpeedModByBag(
 InventoryContainer inventoryContainer) {
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

float IsoGameCharacter::calculateInjurySpeed(BodyPart bodyPart, bool boolean0) {
 // TODO: Implement calculateInjurySpeed
 return 0;
}

float IsoGameCharacter::calcFractureInjurySpeed(BodyPart bodyPart) {
 // TODO: Implement calcFractureInjurySpeed
 return 0;
}

void IsoGameCharacter::calculateWalkSpeed() {
 // TODO: Implement calculateWalkSpeed
}

void IsoGameCharacter::updateSpeedModifiers() {
 // TODO: Implement updateSpeedModifiers
}

void IsoGameCharacter::DoFloorSplat(IsoGridSquare sq, const std::string &id,
 bool bFlip, float offZ, float alpha) {
 // TODO: Implement DoFloorSplat
}

void IsoGameCharacter::DoSplat(IsoGridSquare square, const std::string &string,
 bool boolean0, IsoFlagType flagType,
 float float0, float float1, float float2) {
 // TODO: Implement DoSplat
}

bool IsoGameCharacter::onMouseLeftClick(int x, int y) {
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

void IsoGameCharacter::faceLocation(float x, float y) {
 // TODO: Implement faceLocation
}

void IsoGameCharacter::faceLocationF(float x, float y) {
 // TODO: Implement faceLocationF
}

bool IsoGameCharacter::isFacingLocation(float x, float y, float dot) {
 // TODO: Implement isFacingLocation
 return false;
}

bool IsoGameCharacter::isFacingObject(IsoObject object, float dot) {
 // TODO: Implement isFacingObject
 return false;
}

void IsoGameCharacter::checkDrawWeaponPre(float var1, float var2, float var3,
 ColorInfo var4) {
 // TODO: Implement checkDrawWeaponPre
}

void IsoGameCharacter::splatBlood(int dist, float alpha) {
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

void IsoGameCharacter::setFemale(bool isFemale) {
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

void IsoGameCharacter::setLastHitCount(int hitCount) {
 // TODO: Implement setLastHitCount
}

int IsoGameCharacter::getSurvivorKills() {
 // TODO: Implement getSurvivorKills
 return 0;
}

void IsoGameCharacter::setSurvivorKills(int survivorKills) {
 // TODO: Implement setSurvivorKills
}

int IsoGameCharacter::getAge() {
 // TODO: Implement getAge
 return 0;
}

void IsoGameCharacter::setAge(int _age) {
 // TODO: Implement setAge
}

void IsoGameCharacter::exert(float f) {
 // TODO: Implement exert
}

bool IsoGameCharacter::isEquipped(InventoryItem item) {
 // TODO: Implement isEquipped
 return false;
}

bool IsoGameCharacter::isEquippedClothing(InventoryItem item) {
 // TODO: Implement isEquippedClothing
 return false;
}

bool IsoGameCharacter::isAttachedItem(InventoryItem item) {
 // TODO: Implement isAttachedItem
 return false;
}

void IsoGameCharacter::faceThisObject(IsoObject object) {
 // TODO: Implement faceThisObject
}

void IsoGameCharacter::facePosition(int x, int y) {
 // TODO: Implement facePosition
}

void IsoGameCharacter::faceThisObjectAlt(IsoObject object) {
 // TODO: Implement faceThisObjectAlt
}

void IsoGameCharacter::setAnimated(bool b) {
 // TODO: Implement setAnimated
}

void IsoGameCharacter::playHurtSound() {
 // TODO: Implement playHurtSound
}

void IsoGameCharacter::playDeadSound() {
 // TODO: Implement playDeadSound
}

void IsoGameCharacter::saveChange(const std::string &change, KahluaTable tbl,
 ByteBuffer bb) {
 // TODO: Implement saveChange
}

void IsoGameCharacter::loadChange(const std::string &change, ByteBuffer bb) {
 // TODO: Implement loadChange
}

int IsoGameCharacter::getAlreadyReadPages(const std::string &fullType) {
 // TODO: Implement getAlreadyReadPages
 return 0;
}

void IsoGameCharacter::setAlreadyReadPages(const std::string &fullType,
 int pages) {
 // TODO: Implement setAlreadyReadPages
}

void IsoGameCharacter::updateLightInfo() {
 // TODO: Implement updateLightInfo
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

void IsoGameCharacter::setTurning(bool boolean0) {
 // TODO: Implement setTurning
}

bool IsoGameCharacter::isTurningAround() {
 // TODO: Implement isTurningAround
 return false;
}

void IsoGameCharacter::setTurningAround(bool boolean0) {
 // TODO: Implement setTurningAround
}

bool IsoGameCharacter::isTurning90() {
 // TODO: Implement isTurning90
 return false;
}

void IsoGameCharacter::setTurning90(bool boolean0) {
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

void IsoGameCharacter::setMeleeDelay(float delay) {
 // TODO: Implement setMeleeDelay
}

float IsoGameCharacter::getRecoilDelay() {
 // TODO: Implement getRecoilDelay
 return 0;
}

void IsoGameCharacter::setRecoilDelay(float recoilDelay) {
 // TODO: Implement setRecoilDelay
}

float IsoGameCharacter::getBeenMovingFor() {
 // TODO: Implement getBeenMovingFor
 return 0;
}

void IsoGameCharacter::setBeenMovingFor(float beenMovingFor) {
 // TODO: Implement setBeenMovingFor
}

bool IsoGameCharacter::isForceShove() {
 // TODO: Implement isForceShove
 return false;
}

void IsoGameCharacter::setForceShove(bool _forceShove) {
 // TODO: Implement setForceShove
}

std::string IsoGameCharacter::getClickSound() {
 // TODO: Implement getClickSound
 return "";
}

void IsoGameCharacter::setClickSound(const std::string &_clickSound) {
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

void IsoGameCharacter::setVehicle(BaseVehicle v) {
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

void IsoGameCharacter::setTemperature(float t) {
 // TODO: Implement setTemperature
}

float IsoGameCharacter::getReduceInfectionPower() {
 // TODO: Implement getReduceInfectionPower
 return 0;
}

void IsoGameCharacter::setReduceInfectionPower(float _reduceInfectionPower) {
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

void IsoGameCharacter::applyTraits(ArrayList<String> luaTraits) {
 // TODO: Implement applyTraits
}

void IsoGameCharacter::createKeyRing() {
 // TODO: Implement createKeyRing
}

void IsoGameCharacter::autoDrink() {
 // TODO: Implement autoDrink
}

InventoryItem IsoGameCharacter::getWaterSource(ArrayList<InventoryItem> items) {
 // TODO: Implement getWaterSource
 return nullptr;
}

new IsoGameCharacter::ArrayList() {
 // TODO: Implement ArrayList
 return nullptr;
}

bool IsoGameCharacter::isRecipeKnown(Recipe recipe) {
 // TODO: Implement isRecipeKnown
 return false;
}

bool IsoGameCharacter::isRecipeKnown(const std::string &name) {
 // TODO: Implement isRecipeKnown
 return false;
}

bool IsoGameCharacter::learnRecipe(const std::string &name) {
 // TODO: Implement learnRecipe
 return false;
}

void IsoGameCharacter::addKnownMediaLine(const std::string &guid) {
 // TODO: Implement addKnownMediaLine
}

void IsoGameCharacter::removeKnownMediaLine(const std::string &guid) {
 // TODO: Implement removeKnownMediaLine
}

void IsoGameCharacter::clearKnownMediaLines() {
 // TODO: Implement clearKnownMediaLines
}

bool IsoGameCharacter::isKnownMediaLine(const std::string &guid) {
 // TODO: Implement isKnownMediaLine
 return false;
}

void IsoGameCharacter::saveKnownMediaLines(ByteBuffer byteBuffer) {
 // TODO: Implement saveKnownMediaLines
}

void IsoGameCharacter::loadKnownMediaLines(ByteBuffer byteBuffer, int var2) {
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

void IsoGameCharacter::setMoving(bool val) {
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

bool IsoGameCharacter::isZombieAttacking(IsoMovingObject other) {
 // TODO: Implement isZombieAttacking
 return false;
}

bool IsoGameCharacter::isZombieThumping() {
 // TODO: Implement isZombieThumping
 return false;
}

int IsoGameCharacter::compareMovePriority(IsoGameCharacter other) {
 // TODO: Implement compareMovePriority
 return 0;
}

long IsoGameCharacter::playSound(const std::string &file) {
 // TODO: Implement playSound
 return 0;
}

long IsoGameCharacter::playSoundLocal(const std::string &file) {
 // TODO: Implement playSoundLocal
 return 0;
}

void IsoGameCharacter::stopOrTriggerSound(long eventInstance) {
 // TODO: Implement stopOrTriggerSound
}

void IsoGameCharacter::addWorldSoundUnlessInvisible(int radius, int volume,
 bool bStressHumans) {
 // TODO: Implement addWorldSoundUnlessInvisible
}

bool IsoGameCharacter::isKnownPoison(InventoryItem item) {
 // TODO: Implement isKnownPoison
 return false;
}

int IsoGameCharacter::getLastHourSleeped() {
 // TODO: Implement getLastHourSleeped
 return 0;
}

void IsoGameCharacter::setLastHourSleeped(int _lastHourSleeped) {
 // TODO: Implement setLastHourSleeped
}

void IsoGameCharacter::setTimeOfSleep(float _timeOfSleep) {
 // TODO: Implement setTimeOfSleep
}

void IsoGameCharacter::setDelayToSleep(float delay) {
 // TODO: Implement setDelayToSleep
}

std::string IsoGameCharacter::getBedType() {
 // TODO: Implement getBedType
 return "";
}

void IsoGameCharacter::setBedType(const std::string &_bedType) {
 // TODO: Implement setBedType
}

void IsoGameCharacter::enterVehicle(BaseVehicle v, int seat, Vector3f offset) {
 // TODO: Implement enterVehicle
}

float IsoGameCharacter::Hit(BaseVehicle _vehicle, float speed,
 bool isHitFromBehind, float hitDirX,
 float hitDirY) {
 // TODO: Implement Hit
 return 0;
}

void IsoGameCharacter::setPath2(PolygonalMap2.Path path) {
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

void IsoGameCharacter::setBed(IsoObject _bed) {
 // TODO: Implement setBed
}

bool IsoGameCharacter::avoidDamage() {
 // TODO: Implement avoidDamage
 return false;
}

void IsoGameCharacter::setAvoidDamage(bool avoid) {
 // TODO: Implement setAvoidDamage
}

bool IsoGameCharacter::isReading() {
 // TODO: Implement isReading
 return false;
}

void IsoGameCharacter::setReading(bool _isReading) {
 // TODO: Implement setReading
}

float IsoGameCharacter::getTimeSinceLastSmoke() {
 // TODO: Implement getTimeSinceLastSmoke
 return 0;
}

void IsoGameCharacter::setTimeSinceLastSmoke(float _timeSinceLastSmoke) {
 // TODO: Implement setTimeSinceLastSmoke
}

bool IsoGameCharacter::isInvisible() {
 // TODO: Implement isInvisible
 return false;
}

void IsoGameCharacter::setInvisible(bool b) {
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

void IsoGameCharacter::setGodMod(bool b) {
 // TODO: Implement setGodMod
}

bool IsoGameCharacter::isUnlimitedCarry() {
 // TODO: Implement isUnlimitedCarry
 return false;
}

void IsoGameCharacter::setUnlimitedCarry(bool _unlimitedCarry) {
 // TODO: Implement setUnlimitedCarry
}

bool IsoGameCharacter::isBuildCheat() {
 // TODO: Implement isBuildCheat
 return false;
}

void IsoGameCharacter::setBuildCheat(bool _buildCheat) {
 // TODO: Implement setBuildCheat
}

bool IsoGameCharacter::isFarmingCheat() {
 // TODO: Implement isFarmingCheat
 return false;
}

void IsoGameCharacter::setFarmingCheat(bool b) {
 // TODO: Implement setFarmingCheat
}

bool IsoGameCharacter::isHealthCheat() {
 // TODO: Implement isHealthCheat
 return false;
}

void IsoGameCharacter::setHealthCheat(bool _healthCheat) {
 // TODO: Implement setHealthCheat
}

bool IsoGameCharacter::isMechanicsCheat() {
 // TODO: Implement isMechanicsCheat
 return false;
}

void IsoGameCharacter::setMechanicsCheat(bool _mechanicsCheat) {
 // TODO: Implement setMechanicsCheat
}

bool IsoGameCharacter::isMovablesCheat() {
 // TODO: Implement isMovablesCheat
 return false;
}

void IsoGameCharacter::setMovablesCheat(bool b) {
 // TODO: Implement setMovablesCheat
}

bool IsoGameCharacter::isTimedActionInstantCheat() {
 // TODO: Implement isTimedActionInstantCheat
 return false;
}

void IsoGameCharacter::setTimedActionInstantCheat(bool b) {
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

void IsoGameCharacter::setShowAdminTag(bool _showAdminTag) {
 // TODO: Implement setShowAdminTag
}

IAnimationVariableSlot
IsoGameCharacter::getVariable(AnimationVariableHandle handle) {
 // TODO: Implement getVariable
 return nullptr;
}

IAnimationVariableSlot IsoGameCharacter::getVariable(const std::string &key) {
 // TODO: Implement getVariable
 return nullptr;
}

IAnimationVariableSlot
IsoGameCharacter::getOrCreateVariable(const std::string &key) {
 // TODO: Implement getOrCreateVariable
 return nullptr;
}

void IsoGameCharacter::setVariable(IAnimationVariableSlot var) {
 // TODO: Implement setVariable
}

void IsoGameCharacter::setVariable(const std::string &key,
 const std::string &value) {
 // TODO: Implement setVariable
}

void IsoGameCharacter::setVariable(const std::string &key, bool value) {
 // TODO: Implement setVariable
}

void IsoGameCharacter::setVariable(const std::string &key, float value) {
 // TODO: Implement setVariable
}

void IsoGameCharacter::setVariable(
 const std::string &string,
 AnimationVariableSlotCallbackBool
 .CallbackGetStrongTyped callbackGetStrongTyped) {
 // TODO: Implement setVariable
}

void IsoGameCharacter::setVariable(
 const std::string &string,
 AnimationVariableSlotCallbackString
 .CallbackGetStrongTyped callbackGetStrongTyped) {
 // TODO: Implement setVariable
}

void IsoGameCharacter::setVariable(
 const std::string &string,
 AnimationVariableSlotCallbackFloat
 .CallbackGetStrongTyped callbackGetStrongTyped) {
 // TODO: Implement setVariable
}

void IsoGameCharacter::setVariable(
 const std::string &string,
 AnimationVariableSlotCallbackInt
 .CallbackGetStrongTyped callbackGetStrongTyped) {
 // TODO: Implement setVariable
}

void IsoGameCharacter::setVariable(
 const std::string &key, bool defaultVal,
 AnimationVariableSlotCallbackBool.CallbackGetStrongTyped callbackGet) {
 // TODO: Implement setVariable
}

void IsoGameCharacter::setVariable(
 const std::string &key, const std::string &defaultVal,
 AnimationVariableSlotCallbackString.CallbackGetStrongTyped callbackGet) {
 // TODO: Implement setVariable
}

void IsoGameCharacter::setVariable(
 const std::string &key, float defaultVal,
 AnimationVariableSlotCallbackFloat.CallbackGetStrongTyped callbackGet) {
 // TODO: Implement setVariable
}

void IsoGameCharacter::setVariable(
 const std::string &key, int defaultVal,
 AnimationVariableSlotCallbackInt.CallbackGetStrongTyped callbackGet) {
 // TODO: Implement setVariable
}

void IsoGameCharacter::clearVariable(const std::string &key) {
 // TODO: Implement clearVariable
}

void IsoGameCharacter::clearVariables() {
 // TODO: Implement clearVariables
}

std::string IsoGameCharacter::getVariableString(const std::string &name) {
 // TODO: Implement getVariableString
 return "";
}

std::string IsoGameCharacter::getFootInjuryType() {
 // TODO: Implement getFootInjuryType
 return "";
}

float IsoGameCharacter::getVariableFloat(const std::string &name,
 float defaultVal) {
 // TODO: Implement getVariableFloat
 return 0;
}

bool IsoGameCharacter::getVariableBoolean(const std::string &name) {
 // TODO: Implement getVariableBoolean
 return false;
}

bool IsoGameCharacter::getVariableBoolean(const std::string &key,
 bool defaultVal) {
 // TODO: Implement getVariableBoolean
 return false;
}

bool IsoGameCharacter::isVariable(const std::string &name,
 const std::string &val) {
 // TODO: Implement isVariable
 return false;
}

bool IsoGameCharacter::containsVariable(const std::string &name) {
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

void IsoGameCharacter::endPlaybackGameVariables(
 AnimationVariableSource playbackVars) {
 // TODO: Implement endPlaybackGameVariables
}

void IsoGameCharacter::playbackSetCurrentStateSnapshot(
 ActionStateSnapshot snapshot) {
 // TODO: Implement playbackSetCurrentStateSnapshot
}

ActionStateSnapshot IsoGameCharacter::playbackRecordCurrentStateSnapshot() {
 // TODO: Implement playbackRecordCurrentStateSnapshot
 return nullptr;
}

std::string IsoGameCharacter::GetVariable(const std::string &key) {
 // TODO: Implement GetVariable
 return "";
}

void IsoGameCharacter::SetVariable(const std::string &key,
 const std::string &value) {
 // TODO: Implement SetVariable
}

void IsoGameCharacter::ClearVariable(const std::string &key) {
 // TODO: Implement ClearVariable
}

void IsoGameCharacter::actionStateChanged(ActionContext sender) {
 // TODO: Implement actionStateChanged
}

bool IsoGameCharacter::isFallOnFront() {
 // TODO: Implement isFallOnFront
 return false;
}

void IsoGameCharacter::setFallOnFront(bool _fallOnFront) {
 // TODO: Implement setFallOnFront
}

bool IsoGameCharacter::isHitFromBehind() {
 // TODO: Implement isHitFromBehind
 return false;
}

void IsoGameCharacter::setHitFromBehind(bool _hitFromBehind) {
 // TODO: Implement setHitFromBehind
}

void IsoGameCharacter::reportEvent(const std::string &name) {
 // TODO: Implement reportEvent
}

void IsoGameCharacter::StartTimedActionAnim(const std::string &event) {
 // TODO: Implement StartTimedActionAnim
}

void IsoGameCharacter::StartTimedActionAnim(const std::string &event,
 const std::string &type) {
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

void IsoGameCharacter::setHitReaction(const std::string &_hitReaction) {
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

bool IsoGameCharacter::isBehind(IsoGameCharacter chr) {
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

void IsoGameCharacter::setDebugMonitor(AnimatorDebugMonitor monitor) {
 // TODO: Implement setDebugMonitor
}

bool IsoGameCharacter::isAimAtFloor() {
 // TODO: Implement isAimAtFloor
 return false;
}

void IsoGameCharacter::setAimAtFloor(bool b) {
 // TODO: Implement setAimAtFloor
}

std::string IsoGameCharacter::testDotSide(IsoMovingObject target) {
 // TODO: Implement testDotSide
 return "";
}

void IsoGameCharacter::addBasicPatch(BloodBodyPartType part) {
 // TODO: Implement addBasicPatch
}

bool IsoGameCharacter::addHole(BloodBodyPartType part) {
 // TODO: Implement addHole
 return false;
}

bool IsoGameCharacter::addHole(BloodBodyPartType part, bool allLayers) {
 // TODO: Implement addHole
 return false;
}

void IsoGameCharacter::addDirt(BloodBodyPartType part, int nbr,
 bool allLayers) {
 // TODO: Implement addDirt
}

void IsoGameCharacter::addBlood(BloodBodyPartType part, bool scratched,
 bool bitten, bool allLayers) {
 // TODO: Implement addBlood
}

float IsoGameCharacter::getBodyPartClothingDefense(int part, bool bite,
 bool bullet) {
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

void IsoGameCharacter::setBumpDone(bool val) {
 // TODO: Implement setBumpDone
}

bool IsoGameCharacter::isBumpFall() {
 // TODO: Implement isBumpFall
 return false;
}

void IsoGameCharacter::setBumpFall(bool val) {
 // TODO: Implement setBumpFall
}

bool IsoGameCharacter::isBumpStaggered() {
 // TODO: Implement isBumpStaggered
 return false;
}

void IsoGameCharacter::setBumpStaggered(bool val) {
 // TODO: Implement setBumpStaggered
}

std::string IsoGameCharacter::getBumpType() {
 // TODO: Implement getBumpType
 return "";
}

void IsoGameCharacter::setBumpType(const std::string &_bumpType) {
 // TODO: Implement setBumpType
}

std::string IsoGameCharacter::getBumpFallType() {
 // TODO: Implement getBumpFallType
 return "";
}

void IsoGameCharacter::setBumpFallType(const std::string &val) {
 // TODO: Implement setBumpFallType
}

IsoGameCharacter IsoGameCharacter::getBumpedChr() {
 // TODO: Implement getBumpedChr
 return nullptr;
}

void IsoGameCharacter::setBumpedChr(IsoGameCharacter _bumpedChr) {
 // TODO: Implement setBumpedChr
}

long IsoGameCharacter::getLastBump() {
 // TODO: Implement getLastBump
 return 0;
}

void IsoGameCharacter::setLastBump(long _lastBump) {
 // TODO: Implement setLastBump
}

bool IsoGameCharacter::isSitOnGround() {
 // TODO: Implement isSitOnGround
 return false;
}

void IsoGameCharacter::setSitOnGround(bool _sitOnGround) {
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

void IsoGameCharacter::setRunning(bool _bRunning) {
 // TODO: Implement setRunning
}

bool IsoGameCharacter::isSprinting() {
 // TODO: Implement isSprinting
 return false;
}

void IsoGameCharacter::setSprinting(bool _bSprinting) {
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

void IsoGameCharacter::setTextureCreator(
 ModelInstanceTextureCreator _textureCreator) {
 // TODO: Implement setTextureCreator
}

void IsoGameCharacter::postUpdateEquippedTextures() {
 // TODO: Implement postUpdateEquippedTextures
}

bool IsoGameCharacter::getIgnoreMovement() {
 // TODO: Implement getIgnoreMovement
 return false;
}

void IsoGameCharacter::setIgnoreMovement(bool _ignoreMovement) {
 // TODO: Implement setIgnoreMovement
}

bool IsoGameCharacter::isAutoWalk() {
 // TODO: Implement isAutoWalk
 return false;
}

void IsoGameCharacter::setAutoWalk(bool b) {
 // TODO: Implement setAutoWalk
}

void IsoGameCharacter::setAutoWalkDirection(Vector2 v) {
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

void IsoGameCharacter::setSneaking(bool _bSneaking) {
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

void IsoGameCharacter::setMoveDelta(float moveDelta) {
 // TODO: Implement setMoveDelta
}

float IsoGameCharacter::getTurnDelta() {
 // TODO: Implement getTurnDelta
 return 0;
}

void IsoGameCharacter::setTurnDelta(float m_turnDelta) {
 // TODO: Implement setTurnDelta
}

float IsoGameCharacter::getChopTreeSpeed() {
 // TODO: Implement getChopTreeSpeed
 return 0;
}

bool IsoGameCharacter::testDefense(IsoZombie zomb) {
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

void IsoGameCharacter::setBeenSprintingFor(float beenSprintingFor) {
 // TODO: Implement setBeenSprintingFor
}

bool IsoGameCharacter::isHideWeaponModel() {
 // TODO: Implement isHideWeaponModel
 return false;
}

void IsoGameCharacter::setHideWeaponModel(bool _hideWeaponModel) {
 // TODO: Implement setHideWeaponModel
}

void IsoGameCharacter::setIsAiming(bool aIsAiming) {
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

void IsoGameCharacter::addVisualDamage(const std::string &itemType) {
 // TODO: Implement addVisualDamage
}

ItemVisual
IsoGameCharacter::addBodyVisualFromItemType(const std::string &string) {
 // TODO: Implement addBodyVisualFromItemType
 return nullptr;
}

ItemVisual IsoGameCharacter::addBodyVisualFromClothingItemName(
 const std::string &string1) {
 // TODO: Implement addBodyVisualFromClothingItemName
 return nullptr;
}

bool IsoGameCharacter::isDuplicateBodyVisual(ItemVisual itemVisual1) {
 // TODO: Implement isDuplicateBodyVisual
 return false;
}

bool IsoGameCharacter::isCriticalHit() {
 // TODO: Implement isCriticalHit
 return false;
}

void IsoGameCharacter::setCriticalHit(bool _isCrit) {
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

void IsoGameCharacter::setNPC(bool newvalue) {
 // TODO: Implement setNPC
}

void IsoGameCharacter::NPCSetRunning(bool newvalue) {
 // TODO: Implement NPCSetRunning
}

bool IsoGameCharacter::NPCGetRunning() {
 // TODO: Implement NPCGetRunning
 return false;
}

void IsoGameCharacter::NPCSetJustMoved(bool newvalue) {
 // TODO: Implement NPCSetJustMoved
}

void IsoGameCharacter::NPCSetAiming(bool _isAiming) {
 // TODO: Implement NPCSetAiming
}

bool IsoGameCharacter::NPCGetAiming() {
 // TODO: Implement NPCGetAiming
 return false;
}

void IsoGameCharacter::NPCSetAttack(bool newvalue) {
 // TODO: Implement NPCSetAttack
}

void IsoGameCharacter::NPCSetMelee(bool newvalue) {
 // TODO: Implement NPCSetMelee
}

void IsoGameCharacter::setMetabolicTarget(Metabolics m) {
 // TODO: Implement setMetabolicTarget
}

void IsoGameCharacter::setMetabolicTarget(float target) {
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

bool IsoGameCharacter::addHoleFromZombieAttacks(BloodBodyPartType part,
 bool scratch) {
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

void IsoGameCharacter::attackFromWindowsLunge(IsoZombie zombie) {
 // TODO: Implement attackFromWindowsLunge
}

bool IsoGameCharacter::DoSwingCollisionBoneCheck(IsoGameCharacter zombie,
 int bone,
 float tempoLengthTest) {
 // TODO: Implement DoSwingCollisionBoneCheck
 return false;
}

bool IsoGameCharacter::isInvincible() {
 // TODO: Implement isInvincible
 return false;
}

void IsoGameCharacter::setInvincible(bool _invincible) {
 // TODO: Implement setInvincible
}

BaseVehicle IsoGameCharacter::getNearVehicle() {
 // TODO: Implement getNearVehicle
 return nullptr;
}

IsoGridSquare IsoGameCharacter::getSolidFloorAt(int int1, int int2, int int0) {
 // TODO: Implement getSolidFloorAt
 return nullptr;
}

void IsoGameCharacter::dropHeavyItems() {
 // TODO: Implement dropHeavyItems
}

bool IsoGameCharacter::isHeavyItem(InventoryItem item) {
 // TODO: Implement isHeavyItem
 return false;
}

bool IsoGameCharacter::isCanShout() {
 // TODO: Implement isCanShout
 return false;
}

void IsoGameCharacter::setCanShout(bool _canShout) {
 // TODO: Implement setCanShout
}

bool IsoGameCharacter::isUnlimitedEndurance() {
 // TODO: Implement isUnlimitedEndurance
 return false;
}

void IsoGameCharacter::setUnlimitedEndurance(bool _unlimitedEndurance) {
 // TODO: Implement setUnlimitedEndurance
}

void IsoGameCharacter::addActiveLightItem(InventoryItem item,
 ArrayList<InventoryItem> arrayList) {
 // TODO: Implement addActiveLightItem
}

SleepingEventData IsoGameCharacter::getOrCreateSleepingEventData() {
 // TODO: Implement getOrCreateSleepingEventData
 return nullptr;
}

void IsoGameCharacter::playEmote(const std::string &emote) {
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

void IsoGameCharacter::setPersistentOutfitID(int outfitID) {
 // TODO: Implement setPersistentOutfitID
}

void IsoGameCharacter::setPersistentOutfitID(int outfitID, bool init) {
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

void IsoGameCharacter::setDoDeathSound(bool _doDeathSound) {
 // TODO: Implement setDoDeathSound
}

void IsoGameCharacter::updateEquippedRadioFreq() {
 // TODO: Implement updateEquippedRadioFreq
}

FMODParameterList IsoGameCharacter::getFMODParameters() {
 // TODO: Implement getFMODParameters
 return nullptr;
}

void IsoGameCharacter::startEvent(long eventInstance, GameSoundClip clip,
 BitSet parameterSet) {
 // TODO: Implement startEvent
}

void IsoGameCharacter::updateEvent(long eventInstance, GameSoundClip clip) {
 // TODO: Implement updateEvent
}

void IsoGameCharacter::stopEvent(long eventInstance, GameSoundClip clip,
 BitSet parameterSet) {
 // TODO: Implement stopEvent
}

void IsoGameCharacter::playBloodSplatterSound() {
 // TODO: Implement playBloodSplatterSound
}

void IsoGameCharacter::setIgnoreAimingInput(bool b) {
 // TODO: Implement setIgnoreAimingInput
}

void IsoGameCharacter::addBlood(float speed) {
 // TODO: Implement addBlood
}

bool IsoGameCharacter::isKnockedDown() {
 // TODO: Implement isKnockedDown
 return false;
}

void IsoGameCharacter::setKnockedDown(bool _bKnockedDown) {
 // TODO: Implement setKnockedDown
}

void IsoGameCharacter::writeInventory(ByteBuffer b) {
 // TODO: Implement writeInventory
}

std::string IsoGameCharacter::readInventory(ByteBuffer b) {
 // TODO: Implement readInventory
 return "";
}

void IsoGameCharacter::Kill(IsoGameCharacter killer) {
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

bool IsoGameCharacter::isVehicleCollisionActive(BaseVehicle testVehicle) {
 // TODO: Implement isVehicleCollisionActive
 return false;
}

void IsoGameCharacter::doHitByVehicle(BaseVehicle baseVehicle,
 BaseVehicle.HitVars hitVars) {
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

void IsoGameCharacter::setAttackAnim(bool _attackAnim) {
 // TODO: Implement setAttackAnim
}

float IsoGameCharacter::getNextAnimationTranslationLength() {
 // TODO: Implement getNextAnimationTranslationLength
 return 0;
}

float IsoGameCharacter::calcHitDir(IsoGameCharacter wielder, HandWeapon weapon,
 Vector2 out) {
 // TODO: Implement calcHitDir
 return 0;
}

void IsoGameCharacter::calcHitDir(Vector2 out) {
 // TODO: Implement calcHitDir
}

Safety IsoGameCharacter::getSafety() {
 // TODO: Implement getSafety
 return nullptr;
}

void IsoGameCharacter::setSafety(Safety _safety) {
 // TODO: Implement setSafety
}

void IsoGameCharacter::burnCorpse(IsoDeadBody corpse) {
 // TODO: Implement burnCorpse
}

std::string IsoGameCharacter::getBloodBandageType(const std::string &string1) {
 // TODO: Implement getBloodBandageType
 return "";
}

void IsoGameCharacter::update(IsoGameCharacter character) {
 // TODO: Implement update
}

void IsoGameCharacter::addBandageModel(IsoGameCharacter character,
 const std::string &string) {
 // TODO: Implement addBandageModel
}

void IsoGameCharacter::removeBandageModel(IsoGameCharacter character,
 const std::string &string) {
 // TODO: Implement removeBandageModel
}

bool IsoGameCharacter::isIlliterate() {
 // TODO: Implement isIlliterate
 return false;
}

void IsoGameCharacter::initFrom(IsoGameCharacter.LightInfo other) {
 // TODO: Implement initFrom
}

public
IsoGameCharacter::Location() {
 // TODO: Implement Location
 return nullptr;
}

public
IsoGameCharacter::Location(int _x, int _y, int _z) {
 // TODO: Implement Location
 return nullptr;
}

int IsoGameCharacter::getX() {
 // TODO: Implement getX
 return 0;
}

int IsoGameCharacter::getY() {
 // TODO: Implement getY
 return 0;
}

int IsoGameCharacter::getZ() {
 // TODO: Implement getZ
 return 0;
}

bool IsoGameCharacter::equals(void *other) {
 // TODO: Implement equals
 return false;
}

int IsoGameCharacter::getLevel() {
 // TODO: Implement getLevel
 return 0;
}

void IsoGameCharacter::release(IsoGameCharacter.TorchInfo torchInfo) {
 // TODO: Implement release
}

public
IsoGameCharacter::XP(IsoGameCharacter character1) {
 // TODO: Implement XP
 return nullptr;
}

void IsoGameCharacter::update() {
 // TODO: Implement update
}

void IsoGameCharacter::addXpMultiplier(PerkFactory.Perk perks, float multiplier,
 int minLevel, int maxLevel) {
 // TODO: Implement addXpMultiplier
}

float IsoGameCharacter::getMultiplier(PerkFactory.Perk perk) {
 // TODO: Implement getMultiplier
 return 0;
}

int IsoGameCharacter::getPerkBoost(PerkFactory.Perk type) {
 // TODO: Implement getPerkBoost
 return 0;
}

void IsoGameCharacter::setPerkBoost(PerkFactory.Perk perk, int _level) {
 // TODO: Implement setPerkBoost
}

int IsoGameCharacter::getLevel() {
 // TODO: Implement getLevel
 return 0;
}

void IsoGameCharacter::setLevel(int newlevel) {
 // TODO: Implement setLevel
}

float IsoGameCharacter::getTotalXp() {
 // TODO: Implement getTotalXp
 return 0;
}

void IsoGameCharacter::AddXP(PerkFactory.Perk type, float amount) {
 // TODO: Implement AddXP
}

void IsoGameCharacter::AddXPNoMultiplier(PerkFactory.Perk type, float amount) {
 // TODO: Implement AddXPNoMultiplier
}

void IsoGameCharacter::AddXP(PerkFactory.Perk type, float amount, bool callLua,
 bool doXPBoost, bool remote) {
 // TODO: Implement AddXP
}

bool IsoGameCharacter::isSkillExcludedFromSpeedReduction(
 PerkFactory.Perk perk) {
 // TODO: Implement isSkillExcludedFromSpeedReduction
 return false;
}

bool IsoGameCharacter::isSkillExcludedFromSpeedIncrease(PerkFactory.Perk perk) {
 // TODO: Implement isSkillExcludedFromSpeedIncrease
 return false;
}

float IsoGameCharacter::getXP(PerkFactory.Perk type) {
 // TODO: Implement getXP
 return 0;
}

void IsoGameCharacter::AddXP(HandWeapon weapon, int amount) {
 // TODO: Implement AddXP
}

void IsoGameCharacter::setTotalXP(float xp) {
 // TODO: Implement setTotalXP
}

void IsoGameCharacter::savePerk(ByteBuffer byteBuffer, PerkFactory.Perk perk) {
 // TODO: Implement savePerk
}

void IsoGameCharacter::recalcSumm() {
 // TODO: Implement recalcSumm
}

void IsoGameCharacter::load(ByteBuffer input, int WorldVersion) {
 // TODO: Implement load
}

void IsoGameCharacter::save(ByteBuffer output) {
 // TODO: Implement save
}

void IsoGameCharacter::setXPToLevel(PerkFactory.Perk key, int perkLevel) {
 // TODO: Implement setXPToLevel
}

} // namespace characters
} // namespace zombie
