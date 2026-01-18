#include "zombie/characters/IsoPlayer.h"

namespace zombie {
namespace characters {

public
IsoPlayer::IsoPlayer(IsoCell cell) {
  // TODO: Implement IsoPlayer
  return nullptr;
}

public
IsoPlayer::IsoPlayer(IsoCell cell, SurvivorDesc desc, int x, int y, int z) {
  // TODO: Implement IsoPlayer
  return nullptr;
}

void IsoPlayer::setOnlineID(short value) {
  // TODO: Implement setOnlineID
}

void IsoPlayer::registerVariableCallbacks() {
  // TODO: Implement registerVariableCallbacks
}

Vector2 IsoPlayer::getDeferredMovement(Vector2 out_result) {
  // TODO: Implement getDeferredMovement
  return nullptr;
}

float IsoPlayer::getTurnDelta() {
  // TODO: Implement getTurnDelta
  return 0;
}

void IsoPlayer::setPerformingAnAction(bool val) {
  // TODO: Implement setPerformingAnAction
}

bool IsoPlayer::isPerformingAnAction() {
  // TODO: Implement isPerformingAnAction
  return false;
}

bool IsoPlayer::isAttacking() {
  // TODO: Implement isAttacking
  return false;
}

bool IsoPlayer::shouldBeTurning() {
  // TODO: Implement shouldBeTurning
  return false;
}

void IsoPlayer::invokeOnPlayerInstance(Runnable callback) {
  // TODO: Implement invokeOnPlayerInstance
}

IsoPlayer IsoPlayer::getInstance() {
  // TODO: Implement getInstance
  return nullptr;
}

void IsoPlayer::setInstance(IsoPlayer newInstance) {
  // TODO: Implement setInstance
}

bool IsoPlayer::hasInstance() {
  // TODO: Implement hasInstance
  return false;
}

void IsoPlayer::onTrigger_ResetIsoPlayerModel(const std::string &string) {
  // TODO: Implement onTrigger_ResetIsoPlayerModel
}

int IsoPlayer::getFollowDeadCount() {
  // TODO: Implement getFollowDeadCount
  return 0;
}

void IsoPlayer::setFollowDeadCount(int aFollowDeadCount) {
  // TODO: Implement setFollowDeadCount
}

std::string IsoPlayer::getUniqueFileName() {
  // TODO: Implement getUniqueFileName
  return "";
}

bool IsoPlayer::isServerPlayerIDValid(const std::string &id) {
  // TODO: Implement isServerPlayerIDValid
  return false;
}

int IsoPlayer::getPlayerIndex() {
  // TODO: Implement getPlayerIndex
  return 0;
}

bool IsoPlayer::allPlayersDead() {
  // TODO: Implement allPlayersDead
  return false;
}

bool IsoPlayer::allPlayersAsleep() {
  // TODO: Implement allPlayersAsleep
  return false;
}

bool IsoPlayer::getCoopPVP() {
  // TODO: Implement getCoopPVP
  return false;
}

void IsoPlayer::setCoopPVP(bool enabled) {
  // TODO: Implement setCoopPVP
}

void IsoPlayer::TestZombieSpotPlayer(IsoMovingObject chr) {
  // TODO: Implement TestZombieSpotPlayer
}

float IsoPlayer::getPathSpeed() {
  // TODO: Implement getPathSpeed
  return 0;
}

bool IsoPlayer::isGhostMode() {
  // TODO: Implement isGhostMode
  return false;
}

void IsoPlayer::setGhostMode(bool aGhostMode) {
  // TODO: Implement setGhostMode
}

bool IsoPlayer::isSeeEveryone() {
  // TODO: Implement isSeeEveryone
  return false;
}

bool IsoPlayer::zombiesSwitchOwnershipEachUpdate() {
  // TODO: Implement zombiesSwitchOwnershipEachUpdate
  return false;
}

Vector2 IsoPlayer::getPlayerMoveDir() {
  // TODO: Implement getPlayerMoveDir
  return nullptr;
}

void IsoPlayer::setPlayerMoveDir(Vector2 aPlayerMoveDir) {
  // TODO: Implement setPlayerMoveDir
}

void IsoPlayer::MoveUnmodded(Vector2 dir) {
  // TODO: Implement MoveUnmodded
}

void IsoPlayer::nullifyAiming() {
  // TODO: Implement nullifyAiming
}

bool IsoPlayer::isAimKeyDown() {
  // TODO: Implement isAimKeyDown
  return false;
}

void IsoPlayer::initializeStates() {
  // TODO: Implement initializeStates
}

ActionContext IsoPlayer::getActionContext() {
  // TODO: Implement getActionContext
  return nullptr;
}

void IsoPlayer::onAnimPlayerCreated(AnimationPlayer animationPlayer) {
  // TODO: Implement onAnimPlayerCreated
}

std::string IsoPlayer::GetAnimSetName() {
  // TODO: Implement GetAnimSetName
  return "";
}

bool IsoPlayer::IsInMeleeAttack() {
  // TODO: Implement IsInMeleeAttack
  return false;
}

void IsoPlayer::load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
  // TODO: Implement load
}

void IsoPlayer::save(ByteBuffer output, bool IS_DEBUG_SAVE) {
  // TODO: Implement save
}

void IsoPlayer::save() {
  // TODO: Implement save
}

void IsoPlayer::save(const std::string &fileName) {
  // TODO: Implement save
}

void IsoPlayer::load(const std::string &fileName) {
  // TODO: Implement load
}

void IsoPlayer::removeFromWorld() {
  // TODO: Implement removeFromWorld
}

void IsoPlayer::UpdateRemovedEmitters() {
  // TODO: Implement UpdateRemovedEmitters
}

void IsoPlayer::Reset() {
  // TODO: Implement Reset
}

void IsoPlayer::setVehicle4TestCollision(BaseVehicle vehicle) {
  // TODO: Implement setVehicle4TestCollision
}

bool IsoPlayer::isSaveFileInUse() {
  // TODO: Implement isSaveFileInUse
  return false;
}

void IsoPlayer::removeSaveFile() {
  // TODO: Implement removeSaveFile
}

bool IsoPlayer::isSaveFileIPValid() {
  // TODO: Implement isSaveFileIPValid
  return false;
}

return IsoPlayer::isServerPlayerIDValid() {
  // TODO: Implement isServerPlayerIDValid
  return nullptr;
}

std::string IsoPlayer::getObjectName() {
  // TODO: Implement getObjectName
  return "";
}

int IsoPlayer::getJoypadBind() {
  // TODO: Implement getJoypadBind
  return 0;
}

bool IsoPlayer::isLBPressed() {
  // TODO: Implement isLBPressed
  return false;
}

Vector2 IsoPlayer::getControllerAimDir(Vector2 vec) {
  // TODO: Implement getControllerAimDir
  return nullptr;
}

Vector2 IsoPlayer::getMouseAimVector(Vector2 vec) {
  // TODO: Implement getMouseAimVector
  return nullptr;
}

Vector2 IsoPlayer::getAimVector(Vector2 vec) {
  // TODO: Implement getAimVector
  return nullptr;
}

float IsoPlayer::getGlobalMovementMod(bool bDoNoises) {
  // TODO: Implement getGlobalMovementMod
  return 0;
}

bool IsoPlayer::isInTrees2(bool ignoreBush) {
  // TODO: Implement isInTrees2
  return false;
}

float IsoPlayer::getMoveSpeed() {
  // TODO: Implement getMoveSpeed
  return 0;
}

void IsoPlayer::setMoveSpeed(float moveSpeed) {
  // TODO: Implement setMoveSpeed
}

float IsoPlayer::getTorchStrength() {
  // TODO: Implement getTorchStrength
  return 0;
}

float IsoPlayer::getInvAimingMod() {
  // TODO: Implement getInvAimingMod
  return 0;
}

float IsoPlayer::getAimingMod() {
  // TODO: Implement getAimingMod
  return 0;
}

float IsoPlayer::getReloadingMod() {
  // TODO: Implement getReloadingMod
  return 0;
}

float IsoPlayer::getAimingRangeMod() {
  // TODO: Implement getAimingRangeMod
  return 0;
}

bool IsoPlayer::isPathfindRunning() {
  // TODO: Implement isPathfindRunning
  return false;
}

void IsoPlayer::setPathfindRunning(bool newvalue) {
  // TODO: Implement setPathfindRunning
}

bool IsoPlayer::isBannedAttacking() {
  // TODO: Implement isBannedAttacking
  return false;
}

void IsoPlayer::setBannedAttacking(bool b) {
  // TODO: Implement setBannedAttacking
}

float IsoPlayer::getInvAimingRangeMod() {
  // TODO: Implement getInvAimingRangeMod
  return 0;
}

void IsoPlayer::updateCursorVisibility() {
  // TODO: Implement updateCursorVisibility
}

void IsoPlayer::render(float x, float y, float z, ColorInfo col, bool bDoChild,
                       bool bWallLightingPass, Shader shader) {
  // TODO: Implement render
}

void IsoPlayer::renderlast() {
  // TODO: Implement renderlast
}

float IsoPlayer::doBeatenVehicle(float vehicleSpeed) {
  // TODO: Implement doBeatenVehicle
  return 0;
}

void IsoPlayer::update() {
  // TODO: Implement update
}

void IsoPlayer::updateInternal1() {
  // TODO: Implement updateInternal1
}

void IsoPlayer::setBeenMovingSprinting() {
  // TODO: Implement setBeenMovingSprinting
}

bool IsoPlayer::updateInternal2() {
  // TODO: Implement updateInternal2
  return false;
}

void IsoPlayer::updateMovementFromInput(IsoPlayer.MoveVars moveVars) {
  // TODO: Implement updateMovementFromInput
}

void IsoPlayer::updateMovementFromJoypad(IsoPlayer.MoveVars moveVars) {
  // TODO: Implement updateMovementFromJoypad
}

void IsoPlayer::updateMovementFromKeyboardMouse(IsoPlayer.MoveVars moveVars) {
  // TODO: Implement updateMovementFromKeyboardMouse
}

void IsoPlayer::updateAimingStance() {
  // TODO: Implement updateAimingStance
}

void IsoPlayer::calculateStats() {
  // TODO: Implement calculateStats
}

void IsoPlayer::updateStats_Sleeping() {
  // TODO: Implement updateStats_Sleeping
}

void IsoPlayer::updateEnduranceWhileSitting() {
  // TODO: Implement updateEnduranceWhileSitting
}

void IsoPlayer::updateEndurance(float float7) {
  // TODO: Implement updateEndurance
}

bool IsoPlayer::checkActionsBlockingMovement() {
  // TODO: Implement checkActionsBlockingMovement
  return false;
}

void IsoPlayer::updateInteractKeyPanic() {
  // TODO: Implement updateInteractKeyPanic
}

void IsoPlayer::updateSneakKey() {
  // TODO: Implement updateSneakKey
}

void IsoPlayer::updateChangeCharacterKey() {
  // TODO: Implement updateChangeCharacterKey
}

void IsoPlayer::updateEnableModelsKey() {
  // TODO: Implement updateEnableModelsKey
}

void IsoPlayer::updateDeathDragDown() {
  // TODO: Implement updateDeathDragDown
}

void IsoPlayer::updateGodModeKey() {
  // TODO: Implement updateGodModeKey
}

void IsoPlayer::checkReloading() {
  // TODO: Implement checkReloading
}

void IsoPlayer::postupdate() {
  // TODO: Implement postupdate
}

void IsoPlayer::postupdateInternal() {
  // TODO: Implement postupdateInternal
}

void IsoPlayer::highlightRangedTargets() {
  // TODO: Implement highlightRangedTargets
}

void IsoPlayer::highlightRangedTargetsInternal() {
  // TODO: Implement highlightRangedTargetsInternal
}

bool IsoPlayer::isSolidForSeparate() {
  // TODO: Implement isSolidForSeparate
  return false;
}

bool IsoPlayer::isPushableForSeparate() {
  // TODO: Implement isPushableForSeparate
  return false;
}

bool IsoPlayer::isPushedByForSeparate(IsoMovingObject other) {
  // TODO: Implement isPushedByForSeparate
  return false;
}

void IsoPlayer::updateExt() {
  // TODO: Implement updateExt
}

void IsoPlayer::onIdlePerformFidgets() {
  // TODO: Implement onIdlePerformFidgets
}

bool IsoPlayer::updateUseKey() {
  // TODO: Implement updateUseKey
  return false;
}

void IsoPlayer::updateHitByVehicle() {
  // TODO: Implement updateHitByVehicle
}

void IsoPlayer::updateSoundListener() {
  // TODO: Implement updateSoundListener
}

void IsoPlayer::updateMovementRates() {
  // TODO: Implement updateMovementRates
}

void IsoPlayer::pressedAttack(bool calcAttackVars) {
  // TODO: Implement pressedAttack
}

void IsoPlayer::setAttackAnimThrowTimer(long dt) {
  // TODO: Implement setAttackAnimThrowTimer
}

bool IsoPlayer::isAttackAnimThrowTimeOut() {
  // TODO: Implement isAttackAnimThrowTimeOut
  return false;
}

bool IsoPlayer::getAttackAnim() {
  // TODO: Implement getAttackAnim
  return false;
}

std::string IsoPlayer::getWeaponType() {
  // TODO: Implement getWeaponType
  return "";
}

void IsoPlayer::setWeaponType(const std::string &string) {
  // TODO: Implement setWeaponType
}

int IsoPlayer::calculateCritChance(IsoGameCharacter target) {
  // TODO: Implement calculateCritChance
  return 0;
}

void IsoPlayer::checkJoypadIgnoreAimUntilCentered() {
  // TODO: Implement checkJoypadIgnoreAimUntilCentered
}

bool IsoPlayer::isAimControlActive() {
  // TODO: Implement isAimControlActive
  return false;
}

Vector2 IsoPlayer::getJoypadAimVector(Vector2 vector) {
  // TODO: Implement getJoypadAimVector
  return nullptr;
}

Vector2 IsoPlayer::getJoypadMoveVector(Vector2 vector) {
  // TODO: Implement getJoypadMoveVector
  return nullptr;
}

void IsoPlayer::updateToggleToAim() {
  // TODO: Implement updateToggleToAim
}

void IsoPlayer::UpdateInputState(IsoPlayer.InputState inputStatex) {
  // TODO: Implement UpdateInputState
}

IsoZombie IsoPlayer::getClosestZombieToOtherZombie(IsoZombie closestTo) {
  // TODO: Implement getClosestZombieToOtherZombie
  return nullptr;
}

IsoGameCharacter IsoPlayer::getClosestZombieDist() {
  // TODO: Implement getClosestZombieDist
  return nullptr;
}

int IsoPlayer::compare(IsoGameCharacter character0,
                       IsoGameCharacter character1) {
  // TODO: Implement compare
  return 0;
}

void IsoPlayer::hitConsequences(HandWeapon weapon, IsoGameCharacter wielder,
                                bool bIgnoreDamage, float damage,
                                bool _bRemote) {
  // TODO: Implement hitConsequences
}

HandWeapon IsoPlayer::getWeapon() {
  // TODO: Implement getWeapon
  return nullptr;
}

void IsoPlayer::updateMechanicsItems() {
  // TODO: Implement updateMechanicsItems
}

void IsoPlayer::enterExitVehicle() {
  // TODO: Implement enterExitVehicle
}

void IsoPlayer::checkActionGroup() {
  // TODO: Implement checkActionGroup
}

BaseVehicle IsoPlayer::getUseableVehicle() {
  // TODO: Implement getUseableVehicle
  return nullptr;
}

bool IsoPlayer::isNearVehicle() {
  // TODO: Implement isNearVehicle
  return false;
}

BaseVehicle IsoPlayer::getNearVehicle() {
  // TODO: Implement getNearVehicle
  return nullptr;
}

void IsoPlayer::updateWhileInVehicle() {
  // TODO: Implement updateWhileInVehicle
}

void IsoPlayer::attackWhileInVehicle() {
  // TODO: Implement attackWhileInVehicle
}

void IsoPlayer::setAngleFromAim() {
  // TODO: Implement setAngleFromAim
}

void IsoPlayer::updateTorchStrength() {
  // TODO: Implement updateTorchStrength
}

IsoCell IsoPlayer::getCell() {
  // TODO: Implement getCell
  return nullptr;
}

void IsoPlayer::calculateContext() {
  // TODO: Implement calculateContext
}

bool IsoPlayer::isSafeToClimbOver(IsoDirections dir) {
  // TODO: Implement isSafeToClimbOver
  return false;
}

bool IsoPlayer::doContext(IsoDirections dir) {
  // TODO: Implement doContext
  return false;
}

bool IsoPlayer::doContextNSWE(IsoDirections directions) {
  // TODO: Implement doContextNSWE
  return false;
}

IsoObject
IsoPlayer::getContextDoorOrWindowOrWindowFrame(IsoDirections assumedDir) {
  // TODO: Implement getContextDoorOrWindowOrWindowFrame
  return nullptr;
}

void IsoPlayer::doContextDoorOrWindowOrWindowFrame(IsoDirections directions,
                                                   IsoObject object) {
  // TODO: Implement doContextDoorOrWindowOrWindowFrame
}

bool IsoPlayer::hopFence(IsoDirections dir, bool bTest) {
  // TODO: Implement hopFence
  return false;
}

bool IsoPlayer::canClimbOverWall(IsoDirections dir) {
  // TODO: Implement canClimbOverWall
  return false;
}

bool IsoPlayer::climbOverWall(IsoDirections dir) {
  // TODO: Implement climbOverWall
  return false;
}

void IsoPlayer::updateSleepingPillsTaken() {
  // TODO: Implement updateSleepingPillsTaken
}

bool IsoPlayer::AttemptAttack() {
  // TODO: Implement AttemptAttack
  return false;
}

bool IsoPlayer::DoAttack(float chargeDelta) {
  // TODO: Implement DoAttack
  return false;
}

bool IsoPlayer::DoAttack(float chargeDelta, bool forceShove,
                         const std::string &clickSound) {
  // TODO: Implement DoAttack
  return false;
}

int IsoPlayer::getPlayerNum() {
  // TODO: Implement getPlayerNum
  return 0;
}

void IsoPlayer::updateLOS() {
  // TODO: Implement updateLOS
}

float IsoPlayer::getSeeNearbyCharacterDistance() {
  // TODO: Implement getSeeNearbyCharacterDistance
  return 0;
}

bool IsoPlayer::checkSpottedPLayerTimer(IsoPlayer player0) {
  // TODO: Implement checkSpottedPLayerTimer
  return false;
}

bool IsoPlayer::checkCanSeeClient(UdpConnection remoteConnection) {
  // TODO: Implement checkCanSeeClient
  return false;
}

bool IsoPlayer::checkCanSeeClient(IsoPlayer remoteChr) {
  // TODO: Implement checkCanSeeClient
  return false;
}

std::string IsoPlayer::getTimeSurvived() {
  // TODO: Implement getTimeSurvived
  return "";
}

bool IsoPlayer::IsUsingAimWeapon() {
  // TODO: Implement IsUsingAimWeapon
  return false;
}

bool IsoPlayer::IsUsingAimHandWeapon() {
  // TODO: Implement IsUsingAimHandWeapon
  return false;
}

bool IsoPlayer::DoAimAnimOnAiming() {
  // TODO: Implement DoAimAnimOnAiming
  return false;
}

int IsoPlayer::getSleepingPillsTaken() {
  // TODO: Implement getSleepingPillsTaken
  return 0;
}

void IsoPlayer::setSleepingPillsTaken(int _sleepingPillsTaken) {
  // TODO: Implement setSleepingPillsTaken
}

bool IsoPlayer::isOutside() {
  // TODO: Implement isOutside
  return false;
}

double IsoPlayer::getLastSeenZomboidTime() {
  // TODO: Implement getLastSeenZomboidTime
  return 0;
}

float IsoPlayer::getPlayerClothingTemperature() {
  // TODO: Implement getPlayerClothingTemperature
  return 0;
}

float IsoPlayer::getPlayerClothingInsulation() {
  // TODO: Implement getPlayerClothingInsulation
  return 0;
}

InventoryItem IsoPlayer::getActiveLightItem() {
  // TODO: Implement getActiveLightItem
  return nullptr;
}

bool IsoPlayer::isTorchCone() {
  // TODO: Implement isTorchCone
  return false;
}

float IsoPlayer::getTorchDot() {
  // TODO: Implement getTorchDot
  return 0;
}

float IsoPlayer::getLightDistance() {
  // TODO: Implement getLightDistance
  return 0;
}

bool IsoPlayer::pressedMovement(bool ignoreBlock) {
  // TODO: Implement pressedMovement
  return false;
}

bool IsoPlayer::pressedCancelAction() {
  // TODO: Implement pressedCancelAction
  return false;
}

bool IsoPlayer::checkWalkTo() {
  // TODO: Implement checkWalkTo
  return false;
}

bool IsoPlayer::pressedAim() {
  // TODO: Implement pressedAim
  return false;
}

bool IsoPlayer::isDoingActionThatCanBeCancelled() {
  // TODO: Implement isDoingActionThatCanBeCancelled
  return false;
}

long IsoPlayer::getSteamID() {
  // TODO: Implement getSteamID
  return 0;
}

void IsoPlayer::setSteamID(long _steamID) {
  // TODO: Implement setSteamID
}

bool IsoPlayer::isTargetedByZombie() {
  // TODO: Implement isTargetedByZombie
  return false;
}

bool IsoPlayer::isMaskClicked(int x, int y, bool flip) {
  // TODO: Implement isMaskClicked
  return false;
}

int IsoPlayer::getOffSetXUI() {
  // TODO: Implement getOffSetXUI
  return 0;
}

void IsoPlayer::setOffSetXUI(int _offSetXUI) {
  // TODO: Implement setOffSetXUI
}

int IsoPlayer::getOffSetYUI() {
  // TODO: Implement getOffSetYUI
  return 0;
}

void IsoPlayer::setOffSetYUI(int _offSetYUI) {
  // TODO: Implement setOffSetYUI
}

std::string IsoPlayer::getUsername() {
  // TODO: Implement getUsername
  return "";
}

std::string IsoPlayer::getUsername(bool canShowFirstname) {
  // TODO: Implement getUsername
  return "";
}

void IsoPlayer::setUsername(const std::string &newUsername) {
  // TODO: Implement setUsername
}

void IsoPlayer::updateUsername() {
  // TODO: Implement updateUsername
}

short IsoPlayer::getOnlineID() {
  // TODO: Implement getOnlineID
  return 0;
}

bool IsoPlayer::isLocalPlayer() {
  // TODO: Implement isLocalPlayer
  return false;
}

void IsoPlayer::setLocalPlayer(int index, IsoPlayer newPlayerObj) {
  // TODO: Implement setLocalPlayer
}

IsoPlayer IsoPlayer::getLocalPlayerByOnlineID(short ID) {
  // TODO: Implement getLocalPlayerByOnlineID
  return nullptr;
}

bool IsoPlayer::isOnlyPlayerAsleep() {
  // TODO: Implement isOnlyPlayerAsleep
  return false;
}

void IsoPlayer::OnDeath() {
  // TODO: Implement OnDeath
}

bool IsoPlayer::isNoClip() {
  // TODO: Implement isNoClip
  return false;
}

void IsoPlayer::setNoClip(bool _noClip) {
  // TODO: Implement setNoClip
}

void IsoPlayer::setAuthorizeMeleeAction(bool enabled) {
  // TODO: Implement setAuthorizeMeleeAction
}

bool IsoPlayer::isAuthorizeMeleeAction() {
  // TODO: Implement isAuthorizeMeleeAction
  return false;
}

void IsoPlayer::setAuthorizeShoveStomp(bool enabled) {
  // TODO: Implement setAuthorizeShoveStomp
}

bool IsoPlayer::isAuthorizeShoveStomp() {
  // TODO: Implement isAuthorizeShoveStomp
  return false;
}

bool IsoPlayer::isBlockMovement() {
  // TODO: Implement isBlockMovement
  return false;
}

void IsoPlayer::setBlockMovement(bool _blockMovement) {
  // TODO: Implement setBlockMovement
}

void IsoPlayer::startReceivingBodyDamageUpdates(IsoPlayer other) {
  // TODO: Implement startReceivingBodyDamageUpdates
}

void IsoPlayer::stopReceivingBodyDamageUpdates(IsoPlayer other) {
  // TODO: Implement stopReceivingBodyDamageUpdates
}

Nutrition IsoPlayer::getNutrition() {
  // TODO: Implement getNutrition
  return nullptr;
}

Fitness IsoPlayer::getFitness() {
  // TODO: Implement getFitness
  return nullptr;
}

bool IsoPlayer::updateRemotePlayer() {
  // TODO: Implement updateRemotePlayer
  return false;
}

bool IsoPlayer::updateWhileDead() {
  // TODO: Implement updateWhileDead
  return false;
}

void IsoPlayer::initFMODParameters() {
  // TODO: Implement initFMODParameters
}

ParameterCharacterMovementSpeed
IsoPlayer::getParameterCharacterMovementSpeed() {
  // TODO: Implement getParameterCharacterMovementSpeed
  return nullptr;
}

void IsoPlayer::setMeleeHitSurface(ParameterMeleeHitSurface.Material material) {
  // TODO: Implement setMeleeHitSurface
}

void IsoPlayer::setMeleeHitSurface(const std::string &material) {
  // TODO: Implement setMeleeHitSurface
}

void IsoPlayer::setVehicleHitLocation(BaseVehicle vehicle) {
  // TODO: Implement setVehicleHitLocation
}

void IsoPlayer::updateHeartSound() {
  // TODO: Implement updateHeartSound
}

void IsoPlayer::updateWorldAmbiance() {
  // TODO: Implement updateWorldAmbiance
}

void IsoPlayer::updateEquippedBaggageContainer() {
  // TODO: Implement updateEquippedBaggageContainer
}

void IsoPlayer::DoFootstepSound(const std::string &type) {
  // TODO: Implement DoFootstepSound
}

void IsoPlayer::updateHeavyBreathing() {
  // TODO: Implement updateHeavyBreathing
}

void IsoPlayer::checkVehicleContainers() {
  // TODO: Implement checkVehicleContainers
}

void IsoPlayer::setJoypadIgnoreAimUntilCentered(bool ignore) {
  // TODO: Implement setJoypadIgnoreAimUntilCentered
}

bool IsoPlayer::canSeePlayerStats() {
  // TODO: Implement canSeePlayerStats
  return false;
}

ByteBufferWriter
IsoPlayer::createPlayerStats(ByteBufferWriter b,
                             const std::string &adminUsername) {
  // TODO: Implement createPlayerStats
  return nullptr;
}

std::string IsoPlayer::setPlayerStats(ByteBuffer bb,
                                      const std::string &adminUsername) {
  // TODO: Implement setPlayerStats
  return "";
}

bool IsoPlayer::isAllChatMuted() {
  // TODO: Implement isAllChatMuted
  return false;
}

void IsoPlayer::setAllChatMuted(bool _allChatMuted) {
  // TODO: Implement setAllChatMuted
}

std::string IsoPlayer::getAccessLevel() {
  // TODO: Implement getAccessLevel
  return "";
}

bool IsoPlayer::isAccessLevel(const std::string &level) {
  // TODO: Implement isAccessLevel
  return false;
}

void IsoPlayer::setAccessLevel(const std::string &newLvl) {
  // TODO: Implement setAccessLevel
}

void IsoPlayer::addMechanicsItem(const std::string &itemid, VehiclePart part,
                                 long milli) {
  // TODO: Implement addMechanicsItem
}

void IsoPlayer::setPosition(float ax, float ay, float az) {
  // TODO: Implement setPosition
}

void IsoPlayer::updateTemperatureCheck() {
  // TODO: Implement updateTemperatureCheck
}

float IsoPlayer::getZombieRelevenceScore(IsoZombie z) {
  // TODO: Implement getZombieRelevenceScore
  return 0;
}

BaseVisual IsoPlayer::getVisual() {
  // TODO: Implement getVisual
  return nullptr;
}

HumanVisual IsoPlayer::getHumanVisual() {
  // TODO: Implement getHumanVisual
  return nullptr;
}

ItemVisuals IsoPlayer::getItemVisuals() {
  // TODO: Implement getItemVisuals
  return nullptr;
}

void IsoPlayer::getItemVisuals(ItemVisuals _itemVisuals) {
  // TODO: Implement getItemVisuals
}

void IsoPlayer::dressInNamedOutfit(const std::string &outfitName) {
  // TODO: Implement dressInNamedOutfit
}

void IsoPlayer::dressInClothingItem(const std::string &itemGUID) {
  // TODO: Implement dressInClothingItem
}

void IsoPlayer::onClothingOutfitPreviewChanged() {
  // TODO: Implement onClothingOutfitPreviewChanged
}

void IsoPlayer::onWornItemsChanged() {
  // TODO: Implement onWornItemsChanged
}

void IsoPlayer::actionStateChanged(ActionContext sender) {
  // TODO: Implement actionStateChanged
}

Vector2 IsoPlayer::getLastAngle() {
  // TODO: Implement getLastAngle
  return nullptr;
}

void IsoPlayer::setLastAngle(Vector2 _lastAngle) {
  // TODO: Implement setLastAngle
}

int IsoPlayer::getDialogMood() {
  // TODO: Implement getDialogMood
  return 0;
}

void IsoPlayer::setDialogMood(int _DialogMood) {
  // TODO: Implement setDialogMood
}

int IsoPlayer::getPing() {
  // TODO: Implement getPing
  return 0;
}

void IsoPlayer::setPing(int _ping) {
  // TODO: Implement setPing
}

IsoMovingObject IsoPlayer::getDragObject() {
  // TODO: Implement getDragObject
  return nullptr;
}

void IsoPlayer::setDragObject(IsoMovingObject _DragObject) {
  // TODO: Implement setDragObject
}

float IsoPlayer::getAsleepTime() {
  // TODO: Implement getAsleepTime
  return 0;
}

void IsoPlayer::setAsleepTime(float _AsleepTime) {
  // TODO: Implement setAsleepTime
}

int IsoPlayer::getTicksSinceSeenZombie() {
  // TODO: Implement getTicksSinceSeenZombie
  return 0;
}

void IsoPlayer::setTicksSinceSeenZombie(int _TicksSinceSeenZombie) {
  // TODO: Implement setTicksSinceSeenZombie
}

bool IsoPlayer::isWaiting() {
  // TODO: Implement isWaiting
  return false;
}

void IsoPlayer::setWaiting(bool _Waiting) {
  // TODO: Implement setWaiting
}

IsoSurvivor IsoPlayer::getDragCharacter() {
  // TODO: Implement getDragCharacter
  return nullptr;
}

void IsoPlayer::setDragCharacter(IsoSurvivor _DragCharacter) {
  // TODO: Implement setDragCharacter
}

float IsoPlayer::getHeartDelay() {
  // TODO: Implement getHeartDelay
  return 0;
}

void IsoPlayer::setHeartDelay(float _heartDelay) {
  // TODO: Implement setHeartDelay
}

float IsoPlayer::getHeartDelayMax() {
  // TODO: Implement getHeartDelayMax
  return 0;
}

void IsoPlayer::setHeartDelayMax(int _heartDelayMax) {
  // TODO: Implement setHeartDelayMax
}

double IsoPlayer::getHoursSurvived() {
  // TODO: Implement getHoursSurvived
  return 0;
}

void IsoPlayer::setHoursSurvived(double hrs) {
  // TODO: Implement setHoursSurvived
}

float IsoPlayer::getMaxWeightDelta() {
  // TODO: Implement getMaxWeightDelta
  return 0;
}

void IsoPlayer::setMaxWeightDelta(float _maxWeightDelta) {
  // TODO: Implement setMaxWeightDelta
}

std::string IsoPlayer::getForname() {
  // TODO: Implement getForname
  return "";
}

void IsoPlayer::setForname(const std::string &_Forname) {
  // TODO: Implement setForname
}

std::string IsoPlayer::getSurname() {
  // TODO: Implement getSurname
  return "";
}

void IsoPlayer::setSurname(const std::string &_Surname) {
  // TODO: Implement setSurname
}

bool IsoPlayer::isbChangeCharacterDebounce() {
  // TODO: Implement isbChangeCharacterDebounce
  return false;
}

void IsoPlayer::setbChangeCharacterDebounce(bool _bChangeCharacterDebounce) {
  // TODO: Implement setbChangeCharacterDebounce
}

int IsoPlayer::getFollowID() {
  // TODO: Implement getFollowID
  return 0;
}

void IsoPlayer::setFollowID(int _followID) {
  // TODO: Implement setFollowID
}

bool IsoPlayer::isbSeenThisFrame() {
  // TODO: Implement isbSeenThisFrame
  return false;
}

void IsoPlayer::setbSeenThisFrame(bool _bSeenThisFrame) {
  // TODO: Implement setbSeenThisFrame
}

bool IsoPlayer::isbCouldBeSeenThisFrame() {
  // TODO: Implement isbCouldBeSeenThisFrame
  return false;
}

void IsoPlayer::setbCouldBeSeenThisFrame(bool _bCouldBeSeenThisFrame) {
  // TODO: Implement setbCouldBeSeenThisFrame
}

float IsoPlayer::getTimeSinceLastStab() {
  // TODO: Implement getTimeSinceLastStab
  return 0;
}

void IsoPlayer::setTimeSinceLastStab(float _timeSinceLastStab) {
  // TODO: Implement setTimeSinceLastStab
}

void IsoPlayer::setLastSpotted(Stack<IsoMovingObject> _LastSpotted) {
  // TODO: Implement setLastSpotted
}

int IsoPlayer::getClearSpottedTimer() {
  // TODO: Implement getClearSpottedTimer
  return 0;
}

void IsoPlayer::setClearSpottedTimer(int _ClearSpottedTimer) {
  // TODO: Implement setClearSpottedTimer
}

bool IsoPlayer::IsRunning() {
  // TODO: Implement IsRunning
  return false;
}

void IsoPlayer::InitSpriteParts() {
  // TODO: Implement InitSpriteParts
}

bool IsoPlayer::IsAiming() {
  // TODO: Implement IsAiming
  return false;
}

std::string IsoPlayer::getTagPrefix() {
  // TODO: Implement getTagPrefix
  return "";
}

void IsoPlayer::setTagPrefix(const std::string &newTag) {
  // TODO: Implement setTagPrefix
}

ColorInfo IsoPlayer::getTagColor() {
  // TODO: Implement getTagColor
  return nullptr;
}

void IsoPlayer::setTagColor(ColorInfo _tagColor) {
  // TODO: Implement setTagColor
}

int IsoPlayer::getTransactionID() {
  // TODO: Implement getTransactionID
  return 0;
}

void IsoPlayer::setTransactionID(int _transactionID) {
  // TODO: Implement setTransactionID
}

std::string IsoPlayer::getDisplayName() {
  // TODO: Implement getDisplayName
  return "";
}

void IsoPlayer::setDisplayName(const std::string &_displayName) {
  // TODO: Implement setDisplayName
}

bool IsoPlayer::isSeeNonPvpZone() {
  // TODO: Implement isSeeNonPvpZone
  return false;
}

void IsoPlayer::setSeeNonPvpZone(bool _seeNonPvpZone) {
  // TODO: Implement setSeeNonPvpZone
}

bool IsoPlayer::isShowTag() {
  // TODO: Implement isShowTag
  return false;
}

void IsoPlayer::setShowTag(bool show) {
  // TODO: Implement setShowTag
}

bool IsoPlayer::isFactionPvp() {
  // TODO: Implement isFactionPvp
  return false;
}

void IsoPlayer::setFactionPvp(bool pvp) {
  // TODO: Implement setFactionPvp
}

bool IsoPlayer::isForceAim() {
  // TODO: Implement isForceAim
  return false;
}

void IsoPlayer::setForceAim(bool _forceAim) {
  // TODO: Implement setForceAim
}

bool IsoPlayer::toggleForceAim() {
  // TODO: Implement toggleForceAim
  return false;
}

bool IsoPlayer::isForceSprint() {
  // TODO: Implement isForceSprint
  return false;
}

void IsoPlayer::setForceSprint(bool _forceSprint) {
  // TODO: Implement setForceSprint
}

bool IsoPlayer::toggleForceSprint() {
  // TODO: Implement toggleForceSprint
  return false;
}

bool IsoPlayer::isForceRun() {
  // TODO: Implement isForceRun
  return false;
}

void IsoPlayer::setForceRun(bool _forceRun) {
  // TODO: Implement setForceRun
}

bool IsoPlayer::toggleForceRun() {
  // TODO: Implement toggleForceRun
  return false;
}

bool IsoPlayer::isDeaf() {
  // TODO: Implement isDeaf
  return false;
}

bool IsoPlayer::isForceOverrideAnim() {
  // TODO: Implement isForceOverrideAnim
  return false;
}

void IsoPlayer::setForceOverrideAnim(bool forceOverride) {
  // TODO: Implement setForceOverrideAnim
}

long IsoPlayer::getMechanicsItem(const std::string &itemId) {
  // TODO: Implement getMechanicsItem
  return 0;
}

bool IsoPlayer::isWearingNightVisionGoggles() {
  // TODO: Implement isWearingNightVisionGoggles
  return false;
}

void IsoPlayer::setWearingNightVisionGoggles(bool b) {
  // TODO: Implement setWearingNightVisionGoggles
}

void IsoPlayer::OnAnimEvent(AnimLayer sender, AnimEvent event) {
  // TODO: Implement OnAnimEvent
}

void IsoPlayer::onCullStateChanged(ModelManager modelManager, bool isCulled) {
  // TODO: Implement onCullStateChanged
}

bool IsoPlayer::isTimedActionInstant() {
  // TODO: Implement isTimedActionInstant
  return false;
}

bool IsoPlayer::isSkeleton() {
  // TODO: Implement isSkeleton
  return false;
}

void IsoPlayer::addWorldSoundUnlessInvisible(int radius, int volume,
                                             bool bStressHumans) {
  // TODO: Implement addWorldSoundUnlessInvisible
}

void IsoPlayer::updateFootInjuries() {
  // TODO: Implement updateFootInjuries
}

int IsoPlayer::getMoodleLevel(MoodleType type) {
  // TODO: Implement getMoodleLevel
  return 0;
}

bool IsoPlayer::isAttackStarted() {
  // TODO: Implement isAttackStarted
  return false;
}

bool IsoPlayer::isBehaviourMoving() {
  // TODO: Implement isBehaviourMoving
  return false;
}

bool IsoPlayer::isJustMoved() {
  // TODO: Implement isJustMoved
  return false;
}

void IsoPlayer::setJustMoved(bool val) {
  // TODO: Implement setJustMoved
}

bool IsoPlayer::isPlayerMoving() {
  // TODO: Implement isPlayerMoving
  return false;
}

float IsoPlayer::getTimedActionTimeModifier() {
  // TODO: Implement getTimedActionTimeModifier
  return 0;
}

bool IsoPlayer::isLookingWhileInVehicle() {
  // TODO: Implement isLookingWhileInVehicle
  return false;
}

void IsoPlayer::setInitiateAttack(bool initiate) {
  // TODO: Implement setInitiateAttack
}

bool IsoPlayer::isIgnoreInputsForDirection() {
  // TODO: Implement isIgnoreInputsForDirection
  return false;
}

void IsoPlayer::setIgnoreInputsForDirection(bool _ignoreInputsForDirection) {
  // TODO: Implement setIgnoreInputsForDirection
}

bool IsoPlayer::isIgnoreContextKey() {
  // TODO: Implement isIgnoreContextKey
  return false;
}

void IsoPlayer::setIgnoreContextKey(bool _ignoreContextKey) {
  // TODO: Implement setIgnoreContextKey
}

bool IsoPlayer::isIgnoreAutoVault() {
  // TODO: Implement isIgnoreAutoVault
  return false;
}

void IsoPlayer::setIgnoreAutoVault(bool _ignoreAutoVault) {
  // TODO: Implement setIgnoreAutoVault
}

bool IsoPlayer::isAllowSprint() {
  // TODO: Implement isAllowSprint
  return false;
}

void IsoPlayer::setAllowSprint(bool _allowSprint) {
  // TODO: Implement setAllowSprint
}

bool IsoPlayer::isAllowRun() {
  // TODO: Implement isAllowRun
  return false;
}

void IsoPlayer::setAllowRun(bool _allowRun) {
  // TODO: Implement setAllowRun
}

std::string IsoPlayer::getAttackType() {
  // TODO: Implement getAttackType
  return "";
}

void IsoPlayer::setAttackType(const std::string &_attackType) {
  // TODO: Implement setAttackType
}

void IsoPlayer::clearNetworkEvents() {
  // TODO: Implement clearNetworkEvents
}

bool IsoPlayer::isCanSeeAll() {
  // TODO: Implement isCanSeeAll
  return false;
}

void IsoPlayer::setCanSeeAll(bool b) {
  // TODO: Implement setCanSeeAll
}

bool IsoPlayer::isNetworkTeleportEnabled() {
  // TODO: Implement isNetworkTeleportEnabled
  return false;
}

void IsoPlayer::setNetworkTeleportEnabled(bool b) {
  // TODO: Implement setNetworkTeleportEnabled
}

bool IsoPlayer::isCheatPlayerSeeEveryone() {
  // TODO: Implement isCheatPlayerSeeEveryone
  return false;
}

float IsoPlayer::getRelevantAndDistance(float x, float y, float RelevantRange) {
  // TODO: Implement getRelevantAndDistance
  return 0;
}

bool IsoPlayer::isCanHearAll() {
  // TODO: Implement isCanHearAll
  return false;
}

void IsoPlayer::setCanHearAll(bool b) {
  // TODO: Implement setCanHearAll
}

void IsoPlayer::setMoodleCantSprint(bool b) {
  // TODO: Implement setMoodleCantSprint
}

void IsoPlayer::setAttackFromBehind(bool _attackFromBehind) {
  // TODO: Implement setAttackFromBehind
}

bool IsoPlayer::isAttackFromBehind() {
  // TODO: Implement isAttackFromBehind
  return false;
}

float IsoPlayer::getDamageFromHitByACar(float vehicleSpeed) {
  // TODO: Implement getDamageFromHitByACar
  return 0;
}

float IsoPlayer::Hit(BaseVehicle vehicle, float speed, bool isHitFromBehind,
                     float hitDirX, float hitDirY) {
  // TODO: Implement Hit
  return 0;
}

void IsoPlayer::Kill(IsoGameCharacter killer) {
  // TODO: Implement Kill
}

bool IsoPlayer::shouldDoInventory() {
  // TODO: Implement shouldDoInventory
  return false;
}

void IsoPlayer::becomeCorpse() {
  // TODO: Implement becomeCorpse
}

void IsoPlayer::preupdate() {
  // TODO: Implement preupdate
}

HitReactionNetworkAI IsoPlayer::getHitReactionNetworkAI() {
  // TODO: Implement getHitReactionNetworkAI
  return nullptr;
}

NetworkCharacterAI IsoPlayer::getNetworkCharacterAI() {
  // TODO: Implement getNetworkCharacterAI
  return nullptr;
}

void IsoPlayer::setFitnessSpeed() {
  // TODO: Implement setFitnessSpeed
}

bool IsoPlayer::isLocal() {
  // TODO: Implement isLocal
  return false;
}

bool IsoPlayer::isClimbOverWallSuccess() {
  // TODO: Implement isClimbOverWallSuccess
  return false;
}

void IsoPlayer::setClimbOverWallSuccess(bool _climbOverWallSuccess) {
  // TODO: Implement setClimbOverWallSuccess
}

bool IsoPlayer::isClimbOverWallStruggle() {
  // TODO: Implement isClimbOverWallStruggle
  return false;
}

void IsoPlayer::setClimbOverWallStruggle(bool _climbOverWallStruggle) {
  // TODO: Implement setClimbOverWallStruggle
}

bool IsoPlayer::isVehicleCollisionActive(BaseVehicle testVehicle) {
  // TODO: Implement isVehicleCollisionActive
  return false;
}

bool IsoPlayer::isShowMPInfos() {
  // TODO: Implement isShowMPInfos
  return false;
}

void IsoPlayer::setShowMPInfos(bool b) {
  // TODO: Implement setShowMPInfos
}

bool IsoPlayer::equals(void *object) {
  // TODO: Implement equals
  return false;
}

} // namespace characters
} // namespace zombie
