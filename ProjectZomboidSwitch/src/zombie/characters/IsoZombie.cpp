#include <string>
#include "zombie/characters/IsoZombie.h"

namespace zombie {
namespace characters {

std::string IsoZombie::getObjectName() {
    // TODO: Implement getObjectName
    return "";
}

short IsoZombie::getOnlineID() {
    // TODO: Implement getOnlineID
    return 0;
}

bool IsoZombie::isRemoteZombie() {
    // TODO: Implement isRemoteZombie
    return false;
}

void IsoZombie::setVehicle4TestCollision(BaseVehicle var1) {
    // TODO: Implement setVehicle4TestCollision
}

public IsoZombie::IsoZombie(IsoCell var1) {
    // TODO: Implement IsoZombie
    return nullptr;
}

public IsoZombie::IsoZombie(IsoCell var1, SurvivorDesc var2, int var3) {
    // TODO: Implement IsoZombie
    return nullptr;
}

void IsoZombie::initializeStates() {
    // TODO: Implement initializeStates
}

void IsoZombie::registerVariableCallbacks() {
    // TODO: Implement registerVariableCallbacks
}

void IsoZombie::actionStateChanged(ActionContext var1) {
    // TODO: Implement actionStateChanged
}

ActionContext IsoZombie::getActionContext() {
    // TODO: Implement getActionContext
    return nullptr;
}

void IsoZombie::onAnimPlayerCreated(AnimationPlayer var1) {
    // TODO: Implement onAnimPlayerCreated
}

std::string IsoZombie::GetAnimSetName() {
    // TODO: Implement GetAnimSetName
    return "";
}

void IsoZombie::InitSpritePartsZombie() {
    // TODO: Implement InitSpritePartsZombie
}

void IsoZombie::InitSpritePartsZombie(SurvivorDesc var1) {
    // TODO: Implement InitSpritePartsZombie
}

void IsoZombie::pathToCharacter(IsoGameCharacter var1) {
    // TODO: Implement pathToCharacter
}

void IsoZombie::pathToLocationF(float var1, float var2, float var3) {
    // TODO: Implement pathToLocationF
}

void IsoZombie::load(ByteBuffer var1, int var2, bool var3) {
    // TODO: Implement load
}

void IsoZombie::save(ByteBuffer var1, bool var2) {
    // TODO: Implement save
}

void IsoZombie::collideWith(IsoObject var1) {
    // TODO: Implement collideWith
}

float IsoZombie::Hit(HandWeapon var1, IsoGameCharacter var2, float var3, bool var4, float var5, bool var6) {
    // TODO: Implement Hit
    return 0;
}

void IsoZombie::onMouseLeftClick() {
    // TODO: Implement onMouseLeftClick
}

void IsoZombie::renderAtlasTexture(float var1, float var2, float var3) {
    // TODO: Implement renderAtlasTexture
}

void IsoZombie::render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
    // TODO: Implement render
}

void IsoZombie::renderlast() {
    // TODO: Implement renderlast
}

bool IsoZombie::renderTextureInsteadOfModel(float var1, float var2) {
    // TODO: Implement renderTextureInsteadOfModel
    return false;
}

void IsoZombie::renderTextureOverHead(const std::string& var1) {
    // TODO: Implement renderTextureOverHead
}

void IsoZombie::updateAlpha(int var1, float var2, float var3) {
    // TODO: Implement updateAlpha
}

void IsoZombie::RespondToSound() {
    // TODO: Implement RespondToSound
}

void IsoZombie::setTurnAlertedValues(int var1, int var2) {
    // TODO: Implement setTurnAlertedValues
}

void IsoZombie::clearAggroList() {
    // TODO: Implement clearAggroList
}

void IsoZombie::processAggroList() {
    // TODO: Implement processAggroList
}

void IsoZombie::addAggro(IsoMovingObject var1, float var2) {
    // TODO: Implement addAggro
}

bool IsoZombie::isLeadAggro(IsoMovingObject var1) {
    // TODO: Implement isLeadAggro
    return false;
}

void IsoZombie::spotted(IsoMovingObject var1, bool var2) {
    // TODO: Implement spotted
}

void IsoZombie::Move(Vector2 var1) {
    // TODO: Implement Move
}

void IsoZombie::MoveUnmodded(Vector2 var1) {
    // TODO: Implement MoveUnmodded
}

bool IsoZombie::canBeDeletedUnnoticed(float var1) {
    // TODO: Implement canBeDeletedUnnoticed
    return false;
}

void IsoZombie::DoFootstepSound(const std::string& var1) {
    // TODO: Implement DoFootstepSound
}

void IsoZombie::DoFootstepSound(float var1) {
    // TODO: Implement DoFootstepSound
}

void IsoZombie::preupdate() {
    // TODO: Implement preupdate
}

void IsoZombie::postupdate() {
    // TODO: Implement postupdate
}

void IsoZombie::postUpdateInternal() {
    // TODO: Implement postUpdateInternal
}

bool IsoZombie::isSolidForSeparate() {
    // TODO: Implement isSolidForSeparate
    return false;
}

bool IsoZombie::isPushableForSeparate() {
    // TODO: Implement isPushableForSeparate
    return false;
}

bool IsoZombie::isPushedByForSeparate(IsoMovingObject var1) {
    // TODO: Implement isPushedByForSeparate
    return false;
}

void IsoZombie::update() {
    // TODO: Implement update
}

void IsoZombie::updateInternal() {
    // TODO: Implement updateInternal
}

void IsoZombie::calculateStats() {
    // TODO: Implement calculateStats
}

void IsoZombie::updateZombieTripping() {
    // TODO: Implement updateZombieTripping
}

void IsoZombie::updateVocalProperties() {
    // TODO: Implement updateVocalProperties
}

void IsoZombie::setVehicleHitLocation(BaseVehicle var1) {
    // TODO: Implement setVehicleHitLocation
}

void IsoZombie::updateSearchForCorpse() {
    // TODO: Implement updateSearchForCorpse
}

void IsoZombie::damageSheetRope() {
    // TODO: Implement damageSheetRope
}

void IsoZombie::getZombieWalkTowardSpeed(float var1, float var2, Vector2 var3) {
    // TODO: Implement getZombieWalkTowardSpeed
}

void IsoZombie::getZombieLungeSpeed() {
    // TODO: Implement getZombieLungeSpeed
}

bool IsoZombie::tryThump(IsoGridSquare var1) {
    // TODO: Implement tryThump
    return false;
}

void IsoZombie::Wander() {
    // TODO: Implement Wander
}

void IsoZombie::DoZombieInventory() {
    // TODO: Implement DoZombieInventory
}

void IsoZombie::DoCorpseInventory() {
    // TODO: Implement DoCorpseInventory
}

void IsoZombie::DoZombieInventory(bool var1) {
    // TODO: Implement DoZombieInventory
}

void IsoZombie::DoZombieStats() {
    // TODO: Implement DoZombieStats
}

void IsoZombie::setWalkType(const std::string& var1) {
    // TODO: Implement setWalkType
}

void IsoZombie::DoZombieSpeeds(float var1) {
    // TODO: Implement DoZombieSpeeds
}

bool IsoZombie::isFakeDead() {
    // TODO: Implement isFakeDead
    return false;
}

void IsoZombie::setFakeDead(bool var1) {
    // TODO: Implement setFakeDead
}

bool IsoZombie::isForceFakeDead() {
    // TODO: Implement isForceFakeDead
    return false;
}

void IsoZombie::setForceFakeDead(bool var1) {
    // TODO: Implement setForceFakeDead
}

float IsoZombie::Hit(BaseVehicle var1, float var2, bool var3, Vector2 var4) {
    // TODO: Implement Hit
    return 0;
}

void IsoZombie::addBlood(float var1) {
    // TODO: Implement addBlood
}

void IsoZombie::processHitDirection(HandWeapon var1, IsoGameCharacter var2) {
    // TODO: Implement processHitDirection
}

void IsoZombie::hitConsequences(HandWeapon var1, IsoGameCharacter var2, bool var3, float var4, bool var5) {
    // TODO: Implement hitConsequences
}

void IsoZombie::playHurtSound() {
    // TODO: Implement playHurtSound
}

void IsoZombie::checkClimbOverFenceHit() {
    // TODO: Implement checkClimbOverFenceHit
}

void IsoZombie::checkClimbThroughWindowHit() {
    // TODO: Implement checkClimbThroughWindowHit
}

void IsoZombie::climbFenceWindowHit(int var1, int var2) {
    // TODO: Implement climbFenceWindowHit
}

bool IsoZombie::shouldBecomeCrawler(IsoGameCharacter var1) {
    // TODO: Implement shouldBecomeCrawler
    return false;
}

void IsoZombie::removeFromWorld() {
    // TODO: Implement removeFromWorld
}

void IsoZombie::resetForReuse() {
    // TODO: Implement resetForReuse
}

bool IsoZombie::wasFakeDead() {
    // TODO: Implement wasFakeDead
    return false;
}

void IsoZombie::setWasFakeDead(bool var1) {
    // TODO: Implement setWasFakeDead
}

void IsoZombie::setCrawler(bool var1) {
    // TODO: Implement setCrawler
}

bool IsoZombie::isBecomeCrawler() {
    // TODO: Implement isBecomeCrawler
    return false;
}

void IsoZombie::setBecomeCrawler(bool var1) {
    // TODO: Implement setBecomeCrawler
}

bool IsoZombie::isReanimate() {
    // TODO: Implement isReanimate
    return false;
}

void IsoZombie::setReanimate(bool var1) {
    // TODO: Implement setReanimate
}

bool IsoZombie::isReanimatedPlayer() {
    // TODO: Implement isReanimatedPlayer
    return false;
}

void IsoZombie::setReanimatedPlayer(bool var1) {
    // TODO: Implement setReanimatedPlayer
}

IsoPlayer IsoZombie::getReanimatedPlayer() {
    // TODO: Implement getReanimatedPlayer
    return nullptr;
}

void IsoZombie::setFemaleEtc(bool var1) {
    // TODO: Implement setFemaleEtc
}

void IsoZombie::addRandomBloodDirtHolesEtc() {
    // TODO: Implement addRandomBloodDirtHolesEtc
}

void IsoZombie::useDescriptor(Descriptor var1) {
    // TODO: Implement useDescriptor
}

Descriptor IsoZombie::getSharedDescriptor() {
    // TODO: Implement getSharedDescriptor
    return nullptr;
}

int IsoZombie::getSharedDescriptorID() {
    // TODO: Implement getSharedDescriptorID
    return 0;
}

int IsoZombie::getScreenProperX(int var1) {
    // TODO: Implement getScreenProperX
    return 0;
}

int IsoZombie::getScreenProperY(int var1) {
    // TODO: Implement getScreenProperY
    return 0;
}

BaseVisual IsoZombie::getVisual() {
    // TODO: Implement getVisual
    return nullptr;
}

HumanVisual IsoZombie::getHumanVisual() {
    // TODO: Implement getHumanVisual
    return nullptr;
}

ItemVisuals IsoZombie::getItemVisuals() {
    // TODO: Implement getItemVisuals
    return nullptr;
}

void IsoZombie::getItemVisuals(ItemVisuals var1) {
    // TODO: Implement getItemVisuals
}

bool IsoZombie::isUsingWornItems() {
    // TODO: Implement isUsingWornItems
    return false;
}

void IsoZombie::setAsSurvivor() {
    // TODO: Implement setAsSurvivor
}

void IsoZombie::dressInRandomOutfit() {
    // TODO: Implement dressInRandomOutfit
}

void IsoZombie::dressInNamedOutfit(const std::string& var1) {
    // TODO: Implement dressInNamedOutfit
}

void IsoZombie::dressInPersistentOutfitID(int var1) {
    // TODO: Implement dressInPersistentOutfitID
}

void IsoZombie::dressInClothingItem(const std::string& var1) {
    // TODO: Implement dressInClothingItem
}

void IsoZombie::onWornItemsChanged() {
    // TODO: Implement onWornItemsChanged
}

void IsoZombie::clothingItemChanged(const std::string& var1) {
    // TODO: Implement clothingItemChanged
}

bool IsoZombie::WanderFromWindow() {
    // TODO: Implement WanderFromWindow
    return false;
}

bool IsoZombie::isUseless() {
    // TODO: Implement isUseless
    return false;
}

void IsoZombie::setUseless(bool var1) {
    // TODO: Implement setUseless
}

void IsoZombie::setImmortalTutorialZombie(bool var1) {
    // TODO: Implement setImmortalTutorialZombie
}

bool IsoZombie::isTargetInCone(float var1, float var2) {
    // TODO: Implement isTargetInCone
    return false;
}

bool IsoZombie::testCollideWithVehicles(BaseVehicle var1) {
    // TODO: Implement testCollideWithVehicles
    return false;
}

bool IsoZombie::isCrawling() {
    // TODO: Implement isCrawling
    return false;
}

bool IsoZombie::isCanCrawlUnderVehicle() {
    // TODO: Implement isCanCrawlUnderVehicle
    return false;
}

void IsoZombie::setCanCrawlUnderVehicle(bool var1) {
    // TODO: Implement setCanCrawlUnderVehicle
}

bool IsoZombie::isCanWalk() {
    // TODO: Implement isCanWalk
    return false;
}

void IsoZombie::setCanWalk(bool var1) {
    // TODO: Implement setCanWalk
}

void IsoZombie::initCanCrawlUnderVehicle() {
    // TODO: Implement initCanCrawlUnderVehicle
}

bool IsoZombie::shouldGetUpFromCrawl() {
    // TODO: Implement shouldGetUpFromCrawl
    return false;
}

void IsoZombie::toggleCrawling() {
    // TODO: Implement toggleCrawling
}

void IsoZombie::knockDown(bool var1) {
    // TODO: Implement knockDown
}

void IsoZombie::addItemToSpawnAtDeath(InventoryItem var1) {
    // TODO: Implement addItemToSpawnAtDeath
}

void IsoZombie::clearItemsToSpawnAtDeath() {
    // TODO: Implement clearItemsToSpawnAtDeath
}

IsoMovingObject IsoZombie::getEatBodyTarget() {
    // TODO: Implement getEatBodyTarget
    return nullptr;
}

float IsoZombie::getEatSpeed() {
    // TODO: Implement getEatSpeed
    return 0;
}

void IsoZombie::setEatBodyTarget(IsoMovingObject var1, bool var2) {
    // TODO: Implement setEatBodyTarget
}

void IsoZombie::setEatBodyTarget(IsoMovingObject var1, bool var2, float var3) {
    // TODO: Implement setEatBodyTarget
}

void IsoZombie::updateEatBodyTarget() {
    // TODO: Implement updateEatBodyTarget
}

void IsoZombie::updateCharacterTextureAnimTime() {
    // TODO: Implement updateCharacterTextureAnimTime
}

Vector2 IsoZombie::getHitAngle() {
    // TODO: Implement getHitAngle
    return nullptr;
}

void IsoZombie::setHitAngle(Vector2 var1) {
    // TODO: Implement setHitAngle
}

int IsoZombie::getCrawlerType() {
    // TODO: Implement getCrawlerType
    return 0;
}

void IsoZombie::setCrawlerType(int var1) {
    // TODO: Implement setCrawlerType
}

void IsoZombie::addRandomVisualBandages() {
    // TODO: Implement addRandomVisualBandages
}

void IsoZombie::addVisualBandage(BodyPartType var1, bool var2) {
    // TODO: Implement addVisualBandage
}

void IsoZombie::addRandomVisualDamages() {
    // TODO: Implement addRandomVisualDamages
}

std::string IsoZombie::getPlayerAttackPosition() {
    // TODO: Implement getPlayerAttackPosition
    return "";
}

void IsoZombie::setPlayerAttackPosition(const std::string& var1) {
    // TODO: Implement setPlayerAttackPosition
}

bool IsoZombie::isSitAgainstWall() {
    // TODO: Implement isSitAgainstWall
    return false;
}

void IsoZombie::setSitAgainstWall(bool var1) {
    // TODO: Implement setSitAgainstWall
}

bool IsoZombie::isSkeleton() {
    // TODO: Implement isSkeleton
    return false;
}

bool IsoZombie::isZombie() {
    // TODO: Implement isZombie
    return false;
}

void IsoZombie::setSkeleton(bool var1) {
    // TODO: Implement setSkeleton
}

int IsoZombie::getHitTime() {
    // TODO: Implement getHitTime
    return 0;
}

void IsoZombie::setHitTime(int var1) {
    // TODO: Implement setHitTime
}

int IsoZombie::getThumpTimer() {
    // TODO: Implement getThumpTimer
    return 0;
}

void IsoZombie::setThumpTimer(int var1) {
    // TODO: Implement setThumpTimer
}

IsoMovingObject IsoZombie::getTarget() {
    // TODO: Implement getTarget
    return nullptr;
}

void IsoZombie::setTargetSeenTime(float var1) {
    // TODO: Implement setTargetSeenTime
}

float IsoZombie::getTargetSeenTime() {
    // TODO: Implement getTargetSeenTime
    return 0;
}

bool IsoZombie::isTargetVisible() {
    // TODO: Implement isTargetVisible
    return false;
}

float IsoZombie::getTurnDelta() {
    // TODO: Implement getTurnDelta
    return 0;
}

bool IsoZombie::isAttacking() {
    // TODO: Implement isAttacking
    return false;
}

bool IsoZombie::isZombieAttacking() {
    // TODO: Implement isZombieAttacking
    return false;
}

bool IsoZombie::isZombieAttacking(IsoMovingObject var1) {
    // TODO: Implement isZombieAttacking
    return false;
}

int IsoZombie::getHitHeadWhileOnFloor() {
    // TODO: Implement getHitHeadWhileOnFloor
    return 0;
}

std::string IsoZombie::getRealState() {
    // TODO: Implement getRealState
    return "";
}

void IsoZombie::setHitHeadWhileOnFloor(int var1) {
    // TODO: Implement setHitHeadWhileOnFloor
}

bool IsoZombie::isHitLegsWhileOnFloor() {
    // TODO: Implement isHitLegsWhileOnFloor
    return false;
}

void IsoZombie::setHitLegsWhileOnFloor(bool var1) {
    // TODO: Implement setHitLegsWhileOnFloor
}

void IsoZombie::makeInactive(bool var1) {
    // TODO: Implement makeInactive
}

float IsoZombie::getFootstepVolume() {
    // TODO: Implement getFootstepVolume
    return 0;
}

bool IsoZombie::isFacingTarget() {
    // TODO: Implement isFacingTarget
    return false;
}

bool IsoZombie::isTargetLocationKnown() {
    // TODO: Implement isTargetLocationKnown
    return false;
}

int IsoZombie::getSandboxMemoryDuration() {
    // TODO: Implement getSandboxMemoryDuration
    return 0;
}

bool IsoZombie::shouldDoFenceLunge() {
    // TODO: Implement shouldDoFenceLunge
    return false;
}

bool IsoZombie::isProne() {
    // TODO: Implement isProne
    return false;
}

void IsoZombie::setTarget(IsoMovingObject var1) {
    // TODO: Implement setTarget
}

bool IsoZombie::isAlwaysKnockedDown() {
    // TODO: Implement isAlwaysKnockedDown
    return false;
}

void IsoZombie::setAlwaysKnockedDown(bool var1) {
    // TODO: Implement setAlwaysKnockedDown
}

void IsoZombie::setDressInRandomOutfit(bool var1) {
    // TODO: Implement setDressInRandomOutfit
}

void IsoZombie::setBodyToEat(IsoDeadBody var1) {
    // TODO: Implement setBodyToEat
}

bool IsoZombie::isForceEatingAnimation() {
    // TODO: Implement isForceEatingAnimation
    return false;
}

void IsoZombie::setForceEatingAnimation(bool var1) {
    // TODO: Implement setForceEatingAnimation
}

bool IsoZombie::isOnlyJawStab() {
    // TODO: Implement isOnlyJawStab
    return false;
}

void IsoZombie::setOnlyJawStab(bool var1) {
    // TODO: Implement setOnlyJawStab
}

bool IsoZombie::isNoTeeth() {
    // TODO: Implement isNoTeeth
    return false;
}

void IsoZombie::setNoTeeth(bool var1) {
    // TODO: Implement setNoTeeth
}

void IsoZombie::setThumpFlag(int var1) {
    // TODO: Implement setThumpFlag
}

void IsoZombie::setThumpCondition(float var1) {
    // TODO: Implement setThumpCondition
}

void IsoZombie::setThumpCondition(int var1, int var2) {
    // TODO: Implement setThumpCondition
}

float IsoZombie::getThumpCondition() {
    // TODO: Implement getThumpCondition
    return 0;
}

bool IsoZombie::isStaggerBack() {
    // TODO: Implement isStaggerBack
    return false;
}

void IsoZombie::setStaggerBack(bool var1) {
    // TODO: Implement setStaggerBack
}

bool IsoZombie::isKnifeDeath() {
    // TODO: Implement isKnifeDeath
    return false;
}

void IsoZombie::setKnifeDeath(bool var1) {
    // TODO: Implement setKnifeDeath
}

bool IsoZombie::isJawStabAttach() {
    // TODO: Implement isJawStabAttach
    return false;
}

void IsoZombie::setJawStabAttach(bool var1) {
    // TODO: Implement setJawStabAttach
}

void IsoZombie::writeInventory(ByteBuffer var1) {
    // TODO: Implement writeInventory
}

void IsoZombie::Kill(IsoGameCharacter var1, bool var2) {
    // TODO: Implement Kill
}

void IsoZombie::Kill(IsoGameCharacter var1) {
    // TODO: Implement Kill
}

bool IsoZombie::shouldDoInventory() {
    // TODO: Implement shouldDoInventory
    return false;
}

void IsoZombie::becomeCorpse() {
    // TODO: Implement becomeCorpse
}

HitReactionNetworkAI IsoZombie::getHitReactionNetworkAI() {
    // TODO: Implement getHitReactionNetworkAI
    return nullptr;
}

NetworkCharacterAI IsoZombie::getNetworkCharacterAI() {
    // TODO: Implement getNetworkCharacterAI
    return nullptr;
}

bool IsoZombie::wasLocal() {
    // TODO: Implement wasLocal
    return false;
}

bool IsoZombie::isLocal() {
    // TODO: Implement isLocal
    return false;
}

bool IsoZombie::isVehicleCollisionActive(BaseVehicle var1) {
    // TODO: Implement isVehicleCollisionActive
    return false;
}

void IsoZombie::applyDamageFromVehicle(float var1, float var2) {
    // TODO: Implement applyDamageFromVehicle
}

float IsoZombie::Hit(BaseVehicle var1, float var2, bool var3, float var4, float var5) {
    // TODO: Implement Hit
    return 0;
}

float IsoZombie::calcHitDir(IsoGameCharacter var1, HandWeapon var2, Vector2 var3) {
    // TODO: Implement calcHitDir
    return 0;
}

} // namespace characters
} // namespace zombie
