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

void IsoZombie::setVehicle4TestCollision(BaseVehicle vehicle) {
 // TODO: Implement setVehicle4TestCollision
}

public IsoZombie::IsoZombie(IsoCell cell) {
 // TODO: Implement IsoZombie
 return nullptr;
}

public IsoZombie::IsoZombie(IsoCell cell, SurvivorDesc desc, int _palette) {
 // TODO: Implement IsoZombie
 return nullptr;
}

void IsoZombie::initializeStates() {
 // TODO: Implement initializeStates
}

void IsoZombie::registerVariableCallbacks() {
 // TODO: Implement registerVariableCallbacks
}

void IsoZombie::actionStateChanged(ActionContext sender) {
 // TODO: Implement actionStateChanged
}

ActionContext IsoZombie::getActionContext() {
 // TODO: Implement getActionContext
 return nullptr;
}

void IsoZombie::onAnimPlayerCreated(AnimationPlayer animationPlayer) {
 // TODO: Implement onAnimPlayerCreated
}

std::string IsoZombie::GetAnimSetName() {
 // TODO: Implement GetAnimSetName
 return "";
}

void IsoZombie::InitSpritePartsZombie() {
 // TODO: Implement InitSpritePartsZombie
}

void IsoZombie::InitSpritePartsZombie(SurvivorDesc desc) {
 // TODO: Implement InitSpritePartsZombie
}

void IsoZombie::pathToCharacter(IsoGameCharacter _target) {
 // TODO: Implement pathToCharacter
}

void IsoZombie::pathToLocationF(float x, float y, float z) {
 // TODO: Implement pathToLocationF
}

void IsoZombie::load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 // TODO: Implement load
}

void IsoZombie::save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 // TODO: Implement save
}

void IsoZombie::collideWith(IsoObject obj) {
 // TODO: Implement collideWith
}

float IsoZombie::Hit(HandWeapon weapon, IsoGameCharacter wielder, float damageSplit, bool bIgnoreDamage, float modDelta, bool _bRemote) {
 // TODO: Implement Hit
 return 0;
}

void IsoZombie::onMouseLeftClick() {
 // TODO: Implement onMouseLeftClick
}

void IsoZombie::renderAtlasTexture(float float1, float float2, float float3) {
 // TODO: Implement renderAtlasTexture
}

void IsoZombie::render(float x, float y, float z, ColorInfo col, bool bDoChild, bool bWallLightingPass, Shader shader) {
 // TODO: Implement render
}

void IsoZombie::renderlast() {
 // TODO: Implement renderlast
}

bool IsoZombie::renderTextureInsteadOfModel(float float2, float float3) {
 // TODO: Implement renderTextureInsteadOfModel
 return false;
}

void IsoZombie::renderTextureOverHead(const std::string& string) {
 // TODO: Implement renderTextureOverHead
}

void IsoZombie::updateAlpha(int int0, float float0, float float1) {
 // TODO: Implement updateAlpha
}

void IsoZombie::RespondToSound() {
 // TODO: Implement RespondToSound
}

void IsoZombie::setTurnAlertedValues(int soundX, int soundY) {
 // TODO: Implement setTurnAlertedValues
}

void IsoZombie::clearAggroList() {
 // TODO: Implement clearAggroList
}

void IsoZombie::processAggroList() {
 // TODO: Implement processAggroList
}

void IsoZombie::addAggro(IsoMovingObject other, float damage) {
 // TODO: Implement addAggro
}

bool IsoZombie::isLeadAggro(IsoMovingObject other) {
 // TODO: Implement isLeadAggro
 return false;
}

void IsoZombie::spotted(IsoMovingObject other, bool bForced) {
 // TODO: Implement spotted
}

void IsoZombie::Move(Vector2 dir) {
 // TODO: Implement Move
}

void IsoZombie::MoveUnmodded(Vector2 dir) {
 // TODO: Implement MoveUnmodded
}

bool IsoZombie::canBeDeletedUnnoticed(float minDistance) {
 // TODO: Implement canBeDeletedUnnoticed
 return false;
}

void IsoZombie::DoFootstepSound(const std::string& type) {
 // TODO: Implement DoFootstepSound
}

void IsoZombie::DoFootstepSound(float volume) {
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

bool IsoZombie::isPushedByForSeparate(IsoMovingObject other) {
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

void IsoZombie::setVehicleHitLocation(BaseVehicle vehicle) {
 // TODO: Implement setVehicleHitLocation
}

void IsoZombie::updateSearchForCorpse() {
 // TODO: Implement updateSearchForCorpse
}

void IsoZombie::damageSheetRope() {
 // TODO: Implement damageSheetRope
}

void IsoZombie::getZombieWalkTowardSpeed(float speed, float dist, Vector2 temp) {
 // TODO: Implement getZombieWalkTowardSpeed
}

void IsoZombie::getZombieLungeSpeed() {
 // TODO: Implement getZombieLungeSpeed
}

bool IsoZombie::tryThump(IsoGridSquare square) {
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

void IsoZombie::DoZombieInventory(bool boolean0) {
 // TODO: Implement DoZombieInventory
}

void IsoZombie::DoZombieStats() {
 // TODO: Implement DoZombieStats
}

void IsoZombie::setWalkType(const std::string& _walkType) {
 // TODO: Implement setWalkType
}

void IsoZombie::DoZombieSpeeds(float spMod) {
 // TODO: Implement DoZombieSpeeds
}

bool IsoZombie::isFakeDead() {
 // TODO: Implement isFakeDead
 return false;
}

void IsoZombie::setFakeDead(bool _bFakeDead) {
 // TODO: Implement setFakeDead
}

bool IsoZombie::isForceFakeDead() {
 // TODO: Implement isForceFakeDead
 return false;
}

void IsoZombie::setForceFakeDead(bool _bForceFakeDead) {
 // TODO: Implement setForceFakeDead
}

float IsoZombie::Hit(BaseVehicle vehicle, float speed, bool isHitFromBehind, Vector2 hitDir) {
 // TODO: Implement Hit
 return 0;
}

void IsoZombie::addBlood(float speed) {
 // TODO: Implement addBlood
}

void IsoZombie::processHitDirection(HandWeapon weapon, IsoGameCharacter character) {
 // TODO: Implement processHitDirection
}

void IsoZombie::hitConsequences(HandWeapon weapon, IsoGameCharacter wielder, bool bIgnoreDamage, float damage, bool _bRemote) {
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

void IsoZombie::climbFenceWindowHit(int int0, int int1) {
 // TODO: Implement climbFenceWindowHit
}

bool IsoZombie::shouldBecomeCrawler(IsoGameCharacter character) {
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

void IsoZombie::setWasFakeDead(bool wasFakeDead) {
 // TODO: Implement setWasFakeDead
}

void IsoZombie::setCrawler(bool crawling) {
 // TODO: Implement setCrawler
}

bool IsoZombie::isBecomeCrawler() {
 // TODO: Implement isBecomeCrawler
 return false;
}

void IsoZombie::setBecomeCrawler(bool crawler) {
 // TODO: Implement setBecomeCrawler
}

bool IsoZombie::isReanimate() {
 // TODO: Implement isReanimate
 return false;
}

void IsoZombie::setReanimate(bool reanimate) {
 // TODO: Implement setReanimate
}

bool IsoZombie::isReanimatedPlayer() {
 // TODO: Implement isReanimatedPlayer
 return false;
}

void IsoZombie::setReanimatedPlayer(bool reanimated) {
 // TODO: Implement setReanimatedPlayer
}

IsoPlayer IsoZombie::getReanimatedPlayer() {
 // TODO: Implement getReanimatedPlayer
 return nullptr;
}

void IsoZombie::setFemaleEtc(bool female) {
 // TODO: Implement setFemaleEtc
}

void IsoZombie::addRandomBloodDirtHolesEtc() {
 // TODO: Implement addRandomBloodDirtHolesEtc
}

void IsoZombie::useDescriptor(SharedDescriptors.Descriptor _sharedDesc) {
 // TODO: Implement useDescriptor
}

int IsoZombie::getSharedDescriptorID() {
 // TODO: Implement getSharedDescriptorID
 return 0;
}

int IsoZombie::getScreenProperX(int playerIndex) {
 // TODO: Implement getScreenProperX
 return 0;
}

int IsoZombie::getScreenProperY(int playerIndex) {
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

void IsoZombie::getItemVisuals(ItemVisuals _itemVisuals) {
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

void IsoZombie::dressInNamedOutfit(const std::string& outfitName) {
 // TODO: Implement dressInNamedOutfit
}

void IsoZombie::dressInPersistentOutfitID(int outfitID) {
 // TODO: Implement dressInPersistentOutfitID
}

void IsoZombie::dressInClothingItem(const std::string& itemGUID) {
 // TODO: Implement dressInClothingItem
}

void IsoZombie::onWornItemsChanged() {
 // TODO: Implement onWornItemsChanged
}

void IsoZombie::clothingItemChanged(const std::string& itemGuid) {
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

void IsoZombie::setUseless(bool _useless) {
 // TODO: Implement setUseless
}

void IsoZombie::setImmortalTutorialZombie(bool immortal) {
 // TODO: Implement setImmortalTutorialZombie
}

bool IsoZombie::isTargetInCone(float dist, float dot) {
 // TODO: Implement isTargetInCone
 return false;
}

bool IsoZombie::testCollideWithVehicles(BaseVehicle vehicle) {
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

void IsoZombie::setCanCrawlUnderVehicle(bool b) {
 // TODO: Implement setCanCrawlUnderVehicle
}

bool IsoZombie::isCanWalk() {
 // TODO: Implement isCanWalk
 return false;
}

void IsoZombie::setCanWalk(bool bCanStand) {
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

void IsoZombie::knockDown(bool hitFromBehind) {
 // TODO: Implement knockDown
}

void IsoZombie::addItemToSpawnAtDeath(InventoryItem item) {
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

void IsoZombie::setEatBodyTarget(IsoMovingObject _target, bool force) {
 // TODO: Implement setEatBodyTarget
}

void IsoZombie::setEatBodyTarget(IsoMovingObject _target, bool force, float _eatSpeed) {
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

void IsoZombie::setHitAngle(Vector2 _hitAngle) {
 // TODO: Implement setHitAngle
}

int IsoZombie::getCrawlerType() {
 // TODO: Implement getCrawlerType
 return 0;
}

void IsoZombie::setCrawlerType(int _crawlerType) {
 // TODO: Implement setCrawlerType
}

void IsoZombie::addRandomVisualBandages() {
 // TODO: Implement addRandomVisualBandages
}

void IsoZombie::addVisualBandage(BodyPartType bodyPart, bool bloody) {
 // TODO: Implement addVisualBandage
}

void IsoZombie::addRandomVisualDamages() {
 // TODO: Implement addRandomVisualDamages
}

std::string IsoZombie::getPlayerAttackPosition() {
 // TODO: Implement getPlayerAttackPosition
 return "";
}

void IsoZombie::setPlayerAttackPosition(const std::string& _playerAttackPosition) {
 // TODO: Implement setPlayerAttackPosition
}

bool IsoZombie::isSitAgainstWall() {
 // TODO: Implement isSitAgainstWall
 return false;
}

void IsoZombie::setSitAgainstWall(bool _sitAgainstWall) {
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

void IsoZombie::setSkeleton(bool _isSkeleton) {
 // TODO: Implement setSkeleton
}

int IsoZombie::getHitTime() {
 // TODO: Implement getHitTime
 return 0;
}

void IsoZombie::setHitTime(int _hitTime) {
 // TODO: Implement setHitTime
}

int IsoZombie::getThumpTimer() {
 // TODO: Implement getThumpTimer
 return 0;
}

void IsoZombie::setThumpTimer(int _thumpTimer) {
 // TODO: Implement setThumpTimer
}

IsoMovingObject IsoZombie::getTarget() {
 // TODO: Implement getTarget
 return nullptr;
}

void IsoZombie::setTargetSeenTime(float seconds) {
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

bool IsoZombie::isZombieAttacking(IsoMovingObject other) {
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

void IsoZombie::setHitHeadWhileOnFloor(int _hitHeadWhileOnFloor) {
 // TODO: Implement setHitHeadWhileOnFloor
}

bool IsoZombie::isHitLegsWhileOnFloor() {
 // TODO: Implement isHitLegsWhileOnFloor
 return false;
}

void IsoZombie::setHitLegsWhileOnFloor(bool _hitLegsWhileOnFloor) {
 // TODO: Implement setHitLegsWhileOnFloor
}

void IsoZombie::makeInactive(bool binactive) {
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

void IsoZombie::setTarget(IsoMovingObject t) {
 // TODO: Implement setTarget
}

bool IsoZombie::isAlwaysKnockedDown() {
 // TODO: Implement isAlwaysKnockedDown
 return false;
}

void IsoZombie::setAlwaysKnockedDown(bool _alwaysKnockedDown) {
 // TODO: Implement setAlwaysKnockedDown
}

void IsoZombie::setDressInRandomOutfit(bool dressInRandom) {
 // TODO: Implement setDressInRandomOutfit
}

void IsoZombie::setBodyToEat(IsoDeadBody body) {
 // TODO: Implement setBodyToEat
}

bool IsoZombie::isForceEatingAnimation() {
 // TODO: Implement isForceEatingAnimation
 return false;
}

void IsoZombie::setForceEatingAnimation(bool _forceEatingAnimation) {
 // TODO: Implement setForceEatingAnimation
}

bool IsoZombie::isOnlyJawStab() {
 // TODO: Implement isOnlyJawStab
 return false;
}

void IsoZombie::setOnlyJawStab(bool _onlyJawStab) {
 // TODO: Implement setOnlyJawStab
}

bool IsoZombie::isNoTeeth() {
 // TODO: Implement isNoTeeth
 return false;
}

void IsoZombie::setNoTeeth(bool _noTeeth) {
 // TODO: Implement setNoTeeth
}

void IsoZombie::setThumpFlag(int v) {
 // TODO: Implement setThumpFlag
}

void IsoZombie::setThumpCondition(float condition) {
 // TODO: Implement setThumpCondition
}

void IsoZombie::setThumpCondition(int condition, int maxCondition) {
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

void IsoZombie::setStaggerBack(bool _bStaggerBack) {
 // TODO: Implement setStaggerBack
}

bool IsoZombie::isKnifeDeath() {
 // TODO: Implement isKnifeDeath
 return false;
}

void IsoZombie::setKnifeDeath(bool _bKnifeDeath) {
 // TODO: Implement setKnifeDeath
}

bool IsoZombie::isJawStabAttach() {
 // TODO: Implement isJawStabAttach
 return false;
}

void IsoZombie::setJawStabAttach(bool _bJawStabAttach) {
 // TODO: Implement setJawStabAttach
}

void IsoZombie::writeInventory(ByteBuffer b) {
 // TODO: Implement writeInventory
}

void IsoZombie::Kill(IsoGameCharacter killer, bool bGory) {
 // TODO: Implement Kill
}

void IsoZombie::Kill(IsoGameCharacter killer) {
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

bool IsoZombie::isVehicleCollisionActive(BaseVehicle testVehicle) {
 // TODO: Implement isVehicleCollisionActive
 return false;
}

void IsoZombie::applyDamageFromVehicle(float vehicleSpeed, float damage) {
 // TODO: Implement applyDamageFromVehicle
}

float IsoZombie::Hit(BaseVehicle vehicle, float speed, bool isHitFromBehind, float hitDirX, float hitDirY) {
 // TODO: Implement Hit
 return 0;
}

float IsoZombie::calcHitDir(IsoGameCharacter wielder, HandWeapon weapon, Vector2 out) {
 // TODO: Implement calcHitDir
 return 0;
}

public IsoZombie::Aggro(IsoMovingObject arg0, float arg1) {
 // TODO: Implement Aggro
 return nullptr;
}

void IsoZombie::addDamage(float arg0) {
 // TODO: Implement addDamage
}

float IsoZombie::getAggro() {
 // TODO: Implement getAggro
 return 0;
}

void IsoZombie::calculate(Mover moverx, IsoGridSquare square0) {
 // TODO: Implement calculate
}

bool IsoZombie::shouldVisit(int int2, int int3, int int0, int int1) {
 // TODO: Implement shouldVisit
 return false;
}

void IsoZombie::push(int int0, int int1) {
 // TODO: Implement push
}

IsoGridSquare IsoZombie::pop() {
 // TODO: Implement pop
 return nullptr;
}

int IsoZombie::gridX(int int0) {
 // TODO: Implement gridX
 return 0;
}

int IsoZombie::gridY(int int0) {
 // TODO: Implement gridY
 return 0;
}

int IsoZombie::gridX(IsoGridSquare square) {
 // TODO: Implement gridX
 return 0;
}

int IsoZombie::gridY(IsoGridSquare square) {
 // TODO: Implement gridY
 return 0;
}

IsoGridSquare IsoZombie::choose() {
 // TODO: Implement choose
 return nullptr;
}

void IsoZombie::reset() {
 // TODO: Implement reset
}

private IsoZombie::ZombieSound(int int1) {
 // TODO: Implement ZombieSound
 return nullptr;
}

int IsoZombie::radius() {
 // TODO: Implement radius
 return 0;
}

} // namespace characters
} // namespace zombie
