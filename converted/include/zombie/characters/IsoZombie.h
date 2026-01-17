#pragma once
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/PersistentOutfits.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SharedDescriptors.h"
#include "zombie/SoundManager.h"
#include "zombie/SystemDisabler.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/ai/State.h"
#include "zombie/ai/ZombieGroupManager.h"
#include "zombie/ai/astar/AStarPathFinder.h"
#include "zombie/ai/astar/Mover.h"
#include "zombie/ai/states/AttackNetworkState.h"
#include "zombie/ai/states/AttackState.h"
#include "zombie/ai/states/BumpedState.h"
#include "zombie/ai/states/BurntToDeath.h"
#include "zombie/ai/states/ClimbOverFenceState.h"
#include "zombie/ai/states/ClimbOverWallState.h"
#include "zombie/ai/states/ClimbThroughWindowState.h"
#include "zombie/ai/states/CrawlingZombieTurnState.h"
#include "zombie/ai/states/FakeDeadAttackState.h"
#include "zombie/ai/states/FakeDeadZombieState.h"
#include "zombie/ai/states/IdleState.h"
#include "zombie/ai/states/LungeNetworkState.h"
#include "zombie/ai/states/LungeState.h"
#include "zombie/ai/states/PathFindState.h"
#include "zombie/ai/states/PlayerHitReactionState.h"
#include "zombie/ai/states/StaggerBackState.h"
#include "zombie/ai/states/ThumpState.h"
#include "zombie/ai/states/WalkTowardNetworkState.h"
#include "zombie/ai/states/WalkTowardState.h"
#include "zombie/ai/states/ZombieEatBodyState.h"
#include "zombie/ai/states/ZombieFaceTargetState.h"
#include "zombie/ai/states/ZombieFallDownState.h"
#include "zombie/ai/states/ZombieFallingState.h"
#include "zombie/ai/states/ZombieGetDownState.h"
#include "zombie/ai/states/ZombieGetUpFromCrawlState.h"
#include "zombie/ai/states/ZombieGetUpState.h"
#include "zombie/ai/states/ZombieHitReactionState.h"
#include "zombie/ai/states/ZombieIdleState.h"
#include "zombie/ai/states/ZombieOnGroundState.h"
#include "zombie/ai/states/ZombieReanimateState.h"
#include "zombie/ai/states/ZombieSittingState.h"
#include "zombie/ai/states/ZombieTurnAlerted.h"
#include "zombie/audio/parameters/ParameterCharacterInside.h"
#include "zombie/audio/parameters/ParameterCharacterMovementSpeed.h"
#include "zombie/audio/parameters/ParameterFootstepMaterial.h"
#include "zombie/audio/parameters/ParameterFootstepMaterial2.h"
#include "zombie/audio/parameters/ParameterPlayerDistance.h"
#include "zombie/audio/parameters/ParameterShoeType.h"
#include "zombie/audio/parameters/ParameterVehicleHitLocation.h"
#include "zombie/audio/parameters/ParameterZombieState.h"
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characters/AttachedItems/AttachedItem.h"
#include "zombie/characters/AttachedItems/AttachedItems.h"
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/WornItems/WornItem.h"
#include "zombie/characters/WornItems/WornItems.h"
#include "zombie/characters/action/ActionContext.h"
#include "zombie/characters/action/ActionGroup.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/RenderSettings.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/profiling/PerformanceProfileProbe.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/core/skinnedmodel/animation/sharedskele/SharedSkeleAnimationRepository.h"
#include "zombie/core/skinnedmodel/population/Outfit.h"
#include "zombie/core/skinnedmodel/population/OutfitManager.h"
#include "zombie/core/skinnedmodel/population/OutfitRNG.h"
#include "zombie/core/skinnedmodel/visual/BaseVisual.h"
#include "zombie/core/skinnedmodel/visual/HumanVisual.h"
#include "zombie/core/skinnedmodel/visual/IHumanVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/utils/BooleanGrid.h"
#include "zombie/core/utils/OnceEvery.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/DebugType.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/InventoryContainer.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LightingJNI.h"
#include "zombie/iso/LosUtil.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/areas/IsoBuilding.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoFireManager.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/IsoWindowFrame.h"
#include "zombie/iso/objects/IsoZombieGiblets.h"
#include "zombie/iso/objects/interfaces/Thumpable.h"
#include "zombie/iso/sprite/IsoAnim.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/MPStatistics.h"
#include "zombie/network/NetworkVariables.h"
#include "zombie/network/ServerLOS.h"
#include "zombie/network/ServerMap.h"
#include "zombie/network/packets/ZombiePacket.h"
#include "zombie/popman/NetworkZombieManager.h"
#include "zombie/popman/NetworkZombieSimulator.h"
#include "zombie/popman/ZombieCountOptimiser.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIFont.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/AttackVehicleState.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include "zombie/vehicles/VehiclePart.h"
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IsoZombie : public IsoGameCharacter {
public:
  static const uint8_t SPEED_SPRINTER = 1;
  static const uint8_t SPEED_FAST_SHAMBLER = 2;
  static const uint8_t SPEED_SHAMBLER = 3;
  static const uint8_t SPEED_RANDOM = 4;
  static const uint8_t HEARING_PINPOINT = 1;
  static const uint8_t HEARING_NORMAL = 2;
  static const uint8_t HEARING_POOR = 3;
  static const uint8_t HEARING_RANDOM = 4;
  static const uint8_t THUMP_FLAG_GENERIC = 1;
  static const uint8_t THUMP_FLAG_WINDOW_EXTRA = 2;
  static const uint8_t THUMP_FLAG_WINDOW = 3;
  static const uint8_t THUMP_FLAG_METAL = 4;
  static const uint8_t THUMP_FLAG_GARAGE_DOOR = 5;
  bool alwaysKnockedDown = false;
  bool onlyJawStab = false;
  bool forceEatingAnimation = false;
  bool noTeeth = false;
  static const int AllowRepathDelayMax = 120;
  static const bool SPRINTER_FIXES = true;
  int LastTargetSeenX = -1;
  int LastTargetSeenY = -1;
  int LastTargetSeenZ = -1;
  bool Ghost = false;
  float LungeTimer = 0.0F;
  long LungeSoundTime = 0L;
  IsoMovingObject target;
  float TimeSinceSeenFlesh = 100000.0F;
  float targetSeenTime = 0.0F;
  int FollowCount = 0;
  int ZombieID = 0;
  float BonusSpotTime = 0.0F;
  bool bStaggerBack = false;
  bool bKnifeDeath = false;
  bool bJawStabAttach = false;
  bool bBecomeCrawler = false;
  bool bFakeDead = false;
  bool bForceFakeDead = false;
  bool bWasFakeDead = false;
  bool bReanimate = false;
public
  DeadBodyAtlas.BodyTexture atlasTex = nullptr;
  bool bReanimatedPlayer = false;
  bool bIndoorZombie = false;
  int thumpFlag = 0;
  bool thumpSent = false;
  float thumpCondition = 1.0F;
  static const float EAT_BODY_DIST = 1.0F;
  static const float EAT_BODY_TIME = 3600.0F;
  static const float LUNGE_TIME = 180.0F;
  static const float CRAWLER_DAMAGE_DOT = 0.9F;
  static const float CRAWLER_DAMAGE_RANGE = 1.5F;
  bool useless = false;
  int speedType = -1;
  ZombieGroup group;
  bool inactive = false;
  int strength = -1;
  int cognition = -1;
  int memory = -1;
  int sight = -1;
  int hearing = -1;
private
  ArrayList<InventoryItem> itemsToSpawnAtDeath = nullptr;
  float soundReactDelay = 0.0F;
private
  final IsoGameCharacter.Location delayedSound =
      new IsoGameCharacter.Location(-1, -1, -1);
  bool bSoundSourceRepeating = false;
  void *soundSourceTarget = null;
  float soundAttract = 0.0F;
  float soundAttractTimeout = 0.0F;
  const Vector2 hitAngle = new Vector2();
  bool alerted = false;
  std::string walkType = null;
  float footstepVolume = 1.0F;
protected
  SharedDescriptors.Descriptor sharedDesc;
  bool bDressInRandomOutfit = false;
  std::string pendingOutfitName;
  const HumanVisual humanVisual = new HumanVisual(this);
  int crawlerType = 0;
  std::string playerAttackPosition = null;
  float eatSpeed = 1.0F;
  bool sitAgainstWall = false;
  static const int CHECK_FOR_CORPSE_TIMER_MAX = 10000;
  float checkForCorpseTimer = 10000.0F;
  IsoDeadBody bodyToEat = null;
  IsoMovingObject eatBodyTarget;
  int hitTime = 0;
  int thumpTimer = 0;
  bool hitLegsWhileOnFloor = false;
  bool collideWhileHit = true;
  float m_characterTextureAnimTime = 0.0F;
  float m_characterTextureAnimDuration = 1.0F;
  int lastPlayerHit = -1;
  const ItemVisuals itemVisuals = new ItemVisuals();
  int hitHeadWhileOnFloor = 0;
  BaseVehicle vehicle4testCollision = null;
  std::string SpriteName = "BobZ";
  static const int PALETTE_COUNT = 3;
  const Vector2 vectorToTarget = new Vector2();
  float AllowRepathDelay = 0.0F;
  bool KeepItReal = false;
  bool isSkeleton = false;
  const ParameterCharacterInside parameterCharacterInside =
      new ParameterCharacterInside(this);
  const ParameterCharacterMovementSpeed parameterCharacterMovementSpeed =
      new ParameterCharacterMovementSpeed(this);
  const ParameterFootstepMaterial parameterFootstepMaterial =
      new ParameterFootstepMaterial(this);
  const ParameterFootstepMaterial2 parameterFootstepMaterial2 =
      new ParameterFootstepMaterial2(this);
  const ParameterPlayerDistance parameterPlayerDistance =
      new ParameterPlayerDistance(this);
  const ParameterShoeType parameterShoeType = new ParameterShoeType(this);
  const ParameterVehicleHitLocation parameterVehicleHitLocation =
      new ParameterVehicleHitLocation();
  const ParameterZombieState parameterZombieState =
      new ParameterZombieState(this);
  bool scratch = false;
  bool laceration = false;
  const NetworkZombieAI networkAI;
  UdpConnection authOwner = null;
  IsoPlayer authOwnerPlayer = null;
  ZombiePacket zombiePacket = new ZombiePacket();
  bool zombiePacketUpdated = false;
  long lastChangeOwner = -1L;
  static const SharedSkeleAnimationRepository m_sharedSkeleRepo =
      new SharedSkeleAnimationRepository();
  int palette = 0;
  int AttackAnimTime = 50;
  static int AttackAnimTimeMax = 50;
  IsoMovingObject spottedLast = null;
  IsoZombie.Aggro[] aggroList = new IsoZombie.Aggro[4];
  int spotSoundDelay = 0;
  float movex;
  float movey;
  int stepFrameLast = -1;
  OnceEvery networkUpdate = new OnceEvery(1.0F);
  short lastRemoteUpdate = 0;
  short OnlineID = -1;
private
  static final ArrayList<IsoDeadBody> tempBodies =
      std::make_unique<ArrayList<>>();
  float timeSinceRespondToSound = 1000000.0F;
  std::string walkVariantUse = null;
  std::string walkVariant = "ZombieWalk";
  bool bLunger;
  bool bRunning;
  bool bCrawling;
  bool bCanCrawlUnderVehicle = true;
  bool bCanWalk = true;
  bool bRemote;
private
  static final IsoZombie.FloodFill floodFill = new IsoZombie.FloodFill();
  bool ImmortalTutorialZombie;

  std::string getObjectName() { return "Zombie"; }

  short getOnlineID() { return this.OnlineID; }

  bool isRemoteZombie() { return this.authOwner == nullptr; }

  void setVehicle4TestCollision(BaseVehicle vehicle) {
    this.vehicle4testCollision = vehicle;
  }

public
  IsoZombie(IsoCell cell) { this(cell, nullptr, -1); }

public
  IsoZombie(IsoCell cell, SurvivorDesc desc, int _palette) {
    super(cell, 0.0F, 0.0F, 0.0F);
    this.registerVariableCallbacks();
    this.Health = 1.8F + Rand.Next(0.0F, 0.3F);
    this.weight = 0.7F;
    this.dir = IsoDirections.fromIndex(Rand.Next(8));
    this.humanVisual.randomBlood();
    if (desc != nullptr) {
      this.descriptor = desc;
      this.palette = _palette;
    } else {
      this.descriptor = SurvivorFactory.CreateSurvivor();
      this.palette = Rand.Next(3) + 1;
    }

    this.setFemale(this.descriptor.isFemale());
    this.SpriteName = this.isFemale() ? "KateZ" : "BobZ";
    if (this.palette != 1) {
      this.SpriteName = this.SpriteName + this.palette;
    }

    this.InitSpritePartsZombie();
    this.sprite.def.tintr = 0.95F + Rand.Next(5) / 100.0F;
    this.sprite.def.tintg = 0.95F + Rand.Next(5) / 100.0F;
    this.sprite.def.tintb = 0.95F + Rand.Next(5) / 100.0F;
    this.setDefaultState(ZombieIdleState.instance());
    this.setFakeDead(false);
    this.DoZombieStats();
    this.width = 0.3F;
    this.setAlphaAndTarget(0.0F);
    this.finder.maxSearchDistance = 20;
    if (this.isFemale()) {
      this.hurtSound = "FemaleZombieHurt";
    }

    this.initializeStates();
    this.actionContext.setGroup(ActionGroup.getActionGroup("zombie"));
    this.initWornItems("Human");
    this.initAttachedItems("Human");
    this.networkAI = new NetworkZombieAI(this);
    this.clearAggroList();
  }

  void initializeStates() {
    std::unordered_map hashMap = this.getStateUpdateLookup();
    hashMap.clear();
    hashMap.put("attack-network", AttackNetworkState.instance());
    hashMap.put("attackvehicle-network", IdleState.instance());
    hashMap.put("fakedead-attack-network", IdleState.instance());
    hashMap.put("lunge-network", LungeNetworkState.instance());
    hashMap.put("walktoward-network", WalkTowardNetworkState.instance());
    if (this.bCrawling) {
      hashMap.put("attack", AttackState.instance());
      hashMap.put("fakedead", FakeDeadZombieState.instance());
      hashMap.put("fakedead-attack", FakeDeadAttackState.instance());
      hashMap.put("getup", ZombieGetUpFromCrawlState.instance());
      hashMap.put("hitreaction", ZombieHitReactionState.instance());
      hashMap.put("hitreaction-hit", ZombieHitReactionState.instance());
      hashMap.put("idle", ZombieIdleState.instance());
      hashMap.put("onground", ZombieOnGroundState.instance());
      hashMap.put("pathfind", PathFindState.instance());
      hashMap.put("reanimate", ZombieReanimateState.instance());
      hashMap.put("staggerback", StaggerBackState.instance());
      hashMap.put("thump", ThumpState.instance());
      hashMap.put("turn", CrawlingZombieTurnState.instance());
      hashMap.put("walktoward", WalkTowardState.instance());
    } else {
      hashMap.put("attack", AttackState.instance());
      hashMap.put("attackvehicle", AttackVehicleState.instance());
      hashMap.put("bumped", BumpedState.instance());
      hashMap.put("climbfence", ClimbOverFenceState.instance());
      hashMap.put("climbwindow", ClimbThroughWindowState.instance());
      hashMap.put("eatbody", ZombieEatBodyState.instance());
      hashMap.put("falldown", ZombieFallDownState.instance());
      hashMap.put("falling", ZombieFallingState.instance());
      hashMap.put("face-target", ZombieFaceTargetState.instance());
      hashMap.put("fakedead", FakeDeadZombieState.instance());
      hashMap.put("fakedead-attack", FakeDeadAttackState.instance());
      hashMap.put("getdown", ZombieGetDownState.instance());
      hashMap.put("getup", ZombieGetUpState.instance());
      hashMap.put("hitreaction", ZombieHitReactionState.instance());
      hashMap.put("hitreaction-hit", ZombieHitReactionState.instance());
      hashMap.put("idle", ZombieIdleState.instance());
      hashMap.put("lunge", LungeState.instance());
      hashMap.put("onground", ZombieOnGroundState.instance());
      hashMap.put("pathfind", PathFindState.instance());
      hashMap.put("sitting", ZombieSittingState.instance());
      hashMap.put("staggerback", StaggerBackState.instance());
      hashMap.put("thump", ThumpState.instance());
      hashMap.put("turnalerted", ZombieTurnAlerted.instance());
      hashMap.put("walktoward", WalkTowardState.instance());
    }
  }

  void registerVariableCallbacks() {
    this.setVariable("bClient",
                     ()->GameClient.bClient && this.isRemoteZombie());
    this.setVariable("bMovingNetwork",
                     ()->(this.isLocal() || !this.isBumped()) &&
                         (IsoUtils.DistanceManhatten(this.networkAI.targetX,
                                                     this.networkAI.targetY,
                                                     this.x, this.y) > 0.5F ||
                          this.z != this.networkAI.targetZ));
    this.setVariable("hitHeadType", this ::getHitHeadWhileOnFloor);
    this.setVariable("realState", this ::getRealState);
    this.setVariable(
        "battack", ()->{
          if (SystemDisabler.zombiesDontAttack) {
            return false;
          } else if (this.target != nullptr &&
                     !this.target.isZombiesDontAttack()) {
            if (this.target instanceof IsoGameCharacter) {
              if (this.target.isOnFloor() &&
                  ((IsoGameCharacter)this.target).getCurrentState() !=
                      BumpedState.instance()) {
                this.setTarget(nullptr);
                return false;
              }

              BaseVehicle vehicle =
                  ((IsoGameCharacter)this.target).getVehicle();
              if (vehicle != nullptr) {
                return false;
              }

              if (((IsoGameCharacter)this.target).ReanimatedCorpse != nullptr) {
                return false;
              }

              if (((IsoGameCharacter)this.target)
                      .getStateMachine()
                      .getCurrent() == ClimbOverWallState.instance()) {
                return false;
              }
            }

            if (this.bReanimate) {
              return false;
            } else if (Math.abs(this.target.z - this.z) >= 0.2F) {
              return false;
            } else if (this.target instanceof
                       IsoPlayer && ((IsoPlayer)this.target).isGhostMode()) {
              return false;
            } else if (this.bFakeDead) {
              return !this.isUnderVehicle() && this.DistTo(this.target) < 1.3F;
            } else if (!this.bCrawling) {
              IsoGridSquare square0 = this.getCurrentSquare();
              IsoGridSquare square1 = this.target.getCurrentSquare();
              if (square0 != nullptr && square0.isSomethingTo(square1)) {
                return false;
              } else {
                float float0 = this.bCrawling ? 1.4F : 0.72F;
                float float1 = this.vectorToTarget.getLength();
                return float1 <= float0;
              }
            } else {
              return !this.isUnderVehicle() && this.DistTo(this.target) < 1.3F;
            }
          } else {
            return false;
          }
        });
    this.setVariable("isFacingTarget", this ::isFacingTarget);
    this.setVariable("targetSeenTime", this ::getTargetSeenTime);
    this.setVariable(
        "battackvehicle", ()->{
          if (this.getVariableBoolean("bPathfind")) {
            return false;
          } else if (this.isMoving()) {
            return false;
          } else if (this.target == nullptr) {
            return false;
          } else if (Math.abs(this.target.z - this.z) >= 0.8F) {
            return false;
          } else if (this.target instanceof
                     IsoPlayer && ((IsoPlayer)this.target).isGhostMode()) {
            return false;
          } else if (!(this.target instanceof IsoGameCharacter)) {
            return false;
          } else {
            BaseVehicle vehicle = ((IsoGameCharacter)this.target).getVehicle();
            return vehicle != nullptr && vehicle.isCharacterAdjacentTo(this);
          }
        });
    this.setVariable(
        "beatbodytarget", ()->{
          if (this.isForceEatingAnimation()) {
            return true;
          } else {
            if (!GameServer.bServer) {
              this.updateEatBodyTarget();
            }

            return this.getEatBodyTarget() != nullptr;
          }
        });
    this.setVariable("bbecomecrawler", this ::isBecomeCrawler,
                     this ::setBecomeCrawler);
    this.setVariable("bfakedead", ()->this.bFakeDead);
    this.setVariable("bfalling", ()->this.z > 0.0F && this.fallTime > 2.0F);
    this.setVariable(
        "bhastarget", ()->{
          if (this.target instanceof
              IsoGameCharacter &&
                  ((IsoGameCharacter)this.target).ReanimatedCorpse != nullptr) {
            this.setTarget(nullptr);
          }

          return this.target != nullptr;
        });
    this.setVariable(
        "shouldSprint", ()->{
          if (this.target instanceof
              IsoGameCharacter &&
                  ((IsoGameCharacter)this.target).ReanimatedCorpse != nullptr) {
            this.setTarget(nullptr);
          }

          return this.target != nullptr ||
                 this.soundSourceTarget != nullptr &&
                     !(this.soundSourceTarget instanceof IsoZombie);
        });
    this.setVariable("bknockeddown", this ::isKnockedDown);
    this.setVariable(
        "blunge", ()->{
          if (this.target == nullptr) {
            return false;
          } else if ((int)this.getZ() != (int)this.target.getZ()) {
            return false;
          } else {
            if (this.target instanceof IsoGameCharacter) {
              if (((IsoGameCharacter)this.target).getVehicle() != nullptr) {
                return false;
              }

              if (((IsoGameCharacter)this.target).ReanimatedCorpse != nullptr) {
                return false;
              }
            }

            if (this.target instanceof
                IsoPlayer && ((IsoPlayer)this.target).isGhostMode()) {
              this.setTarget(nullptr);
              return false;
            } else {
              IsoGridSquare square0 = this.getCurrentSquare();
              IsoGridSquare square1 = this.target.getCurrentSquare();
              if (square1 != nullptr && square1.isSomethingTo(square0) &&
                  this.getThumpTarget() != nullptr) {
                return false;
              } else if (this.isCurrentState(ZombieTurnAlerted.instance()) &&
                         !this.isFacingTarget()) {
                return false;
              } else {
                float float0 = this.vectorToTarget.getLength();
                return !(float0 > 3.5F) ||
                       float0 <= 4.0F && this.target instanceof
                    IsoGameCharacter &&
                            ((IsoGameCharacter)this.target).getVehicle() !=
                                nullptr
                        ? !PolygonalMap2.instance.lineClearCollide(
                              this.getX(), this.getY(), this.target.x,
                              this.target.y, (int)this.getZ(), this.target,
                              false, true)
                        : false;
              }
            }
          }
        });
    this.setVariable(
        "bpassengerexposed",
        ()->AttackVehicleState.instance().isPassengerExposed(this));
    this.setVariable(
        "bistargetissmallvehicle",
        ()->this.target != nullptr && this.target instanceof
        IsoPlayer && ((IsoPlayer)this.target).getVehicle() != nullptr
            ? ((IsoPlayer)this.target).getVehicle().getScript().isSmallVehicle
            : true);
    this.setVariable("breanimate", this ::isReanimate, this ::setReanimate);
    this.setVariable("bstaggerback", this ::isStaggerBack);
    this.setVariable(
        "bthump", ()->{
          if (this.getThumpTarget() instanceof
              IsoObject && !(this.getThumpTarget() instanceof BaseVehicle)) {
            IsoObject object = (IsoObject)this.getThumpTarget();
            if (object.getSquare() == nullptr ||
                this.DistToSquared(object.getX() + 0.5F, object.getY() + 0.5F) >
                    9.0F) {
              this.setThumpTarget(nullptr);
            }
          }

          if (this.getThumpTimer() > 0) {
            this.setThumpTarget(nullptr);
          }

          return this.getThumpTarget() != nullptr;
        });
    this.setVariable("bundervehicle", this ::isUnderVehicle);
    this.setVariable("bBeingSteppedOn", this ::isBeingSteppedOn);
    this.setVariable("distancetotarget",
                     ()->this.target == nullptr
                         ? ""
                         : String.valueOf(this.vectorToTarget.getLength() -
                                          this.getWidth() +
                                          this.target.getWidth()));
    this.setVariable("lasttargetseen", ()->this.LastTargetSeenX != -1);
    this.setVariable("lungetimer", ()->this.LungeTimer);
    this.setVariable("reanimatetimer", this ::getReanimateTimer);
    this.setVariable("stateeventdelaytimer", this ::getStateEventDelayTimer);
    this.setVariable(
        "turndirection", ()->{
          if (this.getPath2() != nullptr) {
            return "";
          } else if (this.target != nullptr &&
                     this.vectorToTarget.getLength() != 0.0F) {
            if (this.isRemoteZombie()) {
              tempo.set(this.networkAI.targetX - this.x,
                        this.networkAI.targetY - this.y);
            } else {
              tempo.set(this.vectorToTarget);
            }

            IsoDirections directions0 = IsoDirections.fromAngle(tempo);
            if (this.dir == directions0) {
              return "";
            } else {
              bool boolean0 =
                  CrawlingZombieTurnState.calculateDir(this, directions0);
              return boolean0 ? "left" : "right";
            }
          } else if (this.isCurrentState(WalkTowardState.instance())) {
            WalkTowardState.instance().calculateTargetLocation(this, tempo);
            tempo.x = tempo.x - this.getX();
            tempo.y = tempo.y - this.getY();
            IsoDirections directions1 = IsoDirections.fromAngle(tempo);
            if (this.dir == directions1) {
              return "";
            } else {
              bool boolean1 =
                  CrawlingZombieTurnState.calculateDir(this, directions1);
              return boolean1 ? "left" : "right";
            }
          } else {
            if (this.isCurrentState(PathFindState.instance())) {
            }

            return "";
          }
        });
    this.setVariable("hitforce", this ::getHitForce);
    this.setVariable("alerted", ()->this.alerted);
    this.setVariable("zombiewalktype", ()->this.walkType);
    this.setVariable("crawlertype", ()->this.crawlerType);
    this.setVariable("bGetUpFromCrawl", this ::shouldGetUpFromCrawl);
    this.setVariable("playerattackposition", this ::getPlayerAttackPosition);
    this.setVariable("eatspeed", ()->this.eatSpeed);
    this.setVariable("issitting", this ::isSitAgainstWall);
    this.setVariable("bKnifeDeath", this ::isKnifeDeath, this ::setKnifeDeath);
    this.setVariable("bJawStabAttach", this ::isJawStabAttach,
                     this ::setJawStabAttach);
        this.setVariable("bPathFindPrediction", () -> NetworkVariables.PredictionTypes.PathFind == this.networkAI.predictionType));
        this.setVariable("bCrawling", this ::isCrawling, this ::setCrawler);
  }

  void actionStateChanged(ActionContext sender) {
    super.actionStateChanged(sender);
    if (this.networkAI != nullptr && GameServer.bServer) {
      this.networkAI.extraUpdate();
    }
  }

  ActionContext getActionContext() { return this.actionContext; }

  void onAnimPlayerCreated(AnimationPlayer animationPlayer) {
    super.onAnimPlayerCreated(animationPlayer);
    animationPlayer.setSharedAnimRepo(m_sharedSkeleRepo);
  }

  std::string GetAnimSetName() {
    return this.bCrawling ? "zombie-crawler" : "zombie";
  }

  void InitSpritePartsZombie() {
    SurvivorDesc survivorDesc = this.descriptor;
    this.InitSpritePartsZombie(survivorDesc);
  }

  void InitSpritePartsZombie(SurvivorDesc desc) {
    this.sprite.AnimMap.clear();
    this.sprite.AnimStack.clear();
    this.sprite.CurrentAnim = std::make_unique<IsoAnim>();
    this.sprite.CurrentAnim.name = "REMOVE";
    this.legsSprite = this.sprite;
    this.legsSprite.name = desc.torso;
    this.ZombieID = Rand.Next(10000);
    this.bUseParts = true;
  }

  void pathToCharacter(IsoGameCharacter _target) {
    if (!(this.AllowRepathDelay > 0.0F) ||
        !this.isCurrentState(PathFindState.instance()) &&
            !this.isCurrentState(WalkTowardState.instance()) &&
            !this.isCurrentState(WalkTowardNetworkState.instance())) {
      super.pathToCharacter(_target);
    }
  }

  void pathToLocationF(float x, float y, float z) {
    if (!(this.AllowRepathDelay > 0.0F) ||
        !this.isCurrentState(PathFindState.instance()) &&
            !this.isCurrentState(WalkTowardState.instance()) &&
            !this.isCurrentState(WalkTowardNetworkState.instance())) {
      super.pathToLocationF(x, y, z);
    }
  }

  void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
    super.load(input, WorldVersion, IS_DEBUG_SAVE);
    this.walkVariant = "ZombieWalk";
    this.SpriteName = "BobZ";
    if (this.palette != 1) {
      this.SpriteName = this.SpriteName + this.palette;
    }

    SurvivorDesc survivorDesc = this.descriptor;
    this.setFemale(survivorDesc.isFemale());
    if (this.isFemale()) {
      if (this.palette == 1) {
        this.SpriteName = "KateZ";
      } else {
        this.SpriteName = "KateZ" + this.palette;
      }
    }

    if (this.isFemale()) {
      this.hurtSound = "FemaleZombieHurt";
    } else {
      this.hurtSound = "MaleZombieHurt";
    }

    this.InitSpritePartsZombie(survivorDesc);
    this.sprite.def.tintr = 0.95F + Rand.Next(5) / 100.0F;
    this.sprite.def.tintg = 0.95F + Rand.Next(5) / 100.0F;
    this.sprite.def.tintb = 0.95F + Rand.Next(5) / 100.0F;
    this.setDefaultState(ZombieIdleState.instance());
    this.DoZombieStats();
    input.getFloat();
    this.setWidth(0.3F);
    this.TimeSinceSeenFlesh = input.getInt();
    this.setAlpha(0.0F);
    this.setFakeDead(input.getInt() == 1);
    std::vector arrayList = this.savedInventoryItems;
    uint8_t byte0 = input.get();

    for (int int0 = 0; int0 < byte0; int0++) {
      std::string string = GameWindow.ReadString(input);
      short short0 = input.getShort();
      if (short0 >= 0 && short0 < arrayList.size() &&
          this.wornItems.getBodyLocationGroup().getLocation(string) !=
              nullptr) {
        this.wornItems.setItem(string, (InventoryItem)arrayList.get(short0));
      }
    }

    this.setStateMachineLocked(false);
    this.setDefaultState();
    this.getCell().getZombieList().add(this);
  }

  void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
    super.save(output, IS_DEBUG_SAVE);
    output.putFloat(0.0F);
    output.putInt((int)this.TimeSinceSeenFlesh);
    output.putInt(this.isFakeDead() ? 1 : 0);
    if (this.wornItems.size() > 127) {
      throw new RuntimeException("too many worn items");
    } else {
      output.put((byte)this.wornItems.size());
      this.wornItems.forEach(wornItem->{
        GameWindow.WriteString(output, wornItem.getLocation());
        output.putShort(
            (short)this.savedInventoryItems.indexOf(wornItem.getItem()));
      });
    }
  }

  void collideWith(IsoObject obj) {
    if (!this.Ghost && obj != nullptr) {
      if (obj.rerouteCollide != nullptr) {
        obj = this.rerouteCollide;
      }

      State state = this.getCurrentState();
      boolean boolean0 = this.isCurrentState(PathFindState.instance()) ||
                         this.isCurrentState(LungeState.instance()) ||
                         this.isCurrentState(LungeNetworkState.instance()) ||
                         this.isCurrentState(WalkTowardState.instance()) ||
                         this.isCurrentState(WalkTowardNetworkState.instance());
      IsoWindow window = Type.tryCastTo(obj, IsoWindow.class);
      if (window != nullptr && window.canClimbThrough(this) && boolean0) {
        if (!this.isFacingObject(window, 0.8F)) {
          super.collideWith(obj);
          return;
        }

        if (state != PathFindState.instance() && !this.bCrawling) {
          this.climbThroughWindow(window);
        }
      } else if (obj instanceof IsoThumpable &&
                                    ((IsoThumpable)obj).canClimbThrough(this) &&
                                    boolean0) {
        if (state != PathFindState.instance() && !this.bCrawling) {
          this.climbThroughWindow((IsoThumpable)obj);
        }
      } else if ((!(obj instanceof IsoDoor) || !((IsoDoor)obj).isHoppable()) &&
                 obj != nullptr && obj.getThumpableFor(this) != nullptr &&
                 boolean0) {
        boolean boolean1 =
            (this.isCurrentState(PathFindState.instance()) ||
             this.isCurrentState(WalkTowardState.instance()) ||
             this.isCurrentState(WalkTowardNetworkState.instance())) &&
            this.getPathFindBehavior2().isGoalSound();
        if (!SandboxOptions.instance.Lore.ThumpNoChasing.getValue() &&
            this.target == nullptr && !boolean1) {
          this.setVariable("bPathfind", false);
          this.setVariable("bMoving", false);
        } else {
          if (obj instanceof
              IsoThumpable && !SandboxOptions.instance.Lore.ThumpOnConstruction
                                   .getValue()) {
            return;
          }

          void *object = obj;
          if (obj instanceof IsoWindow &&
                                 obj.getThumpableFor(this) != nullptr &&
                                 obj.isDestroyed()) {
            object = obj.getThumpableFor(this);
          }

          this.setThumpTarget((Thumpable)object);
        }

        this.setPath2(nullptr);
      }

      if (!this.bCrawling && IsoWindowFrame.isWindowFrame(obj) && boolean0 &&
          state != PathFindState.instance()) {
        this.climbThroughWindowFrame(obj);
      }

      super.collideWith(obj);
    }
  }

  float Hit(HandWeapon weapon, IsoGameCharacter wielder, float damageSplit,
            bool bIgnoreDamage, float modDelta, bool _bRemote) {
    if (Core.bTutorial && this.ImmortalTutorialZombie) {
      return 0.0F;
    } else {
      BodyPartType bodyPartType = BodyPartType.FromIndex(
          Rand.Next(BodyPartType.ToIndex(BodyPartType.Torso_Upper),
                    BodyPartType.ToIndex(BodyPartType.Torso_Lower) + 1));
      if (Rand.NextBool(7)) {
        bodyPartType = BodyPartType.Head;
      }

      if (wielder.isCriticalHit() && Rand.NextBool(3)) {
        bodyPartType = BodyPartType.Head;
      }

      LuaEventManager.triggerEvent("OnHitZombie", this, wielder, bodyPartType,
                                   weapon);
      float float0 = super.Hit(weapon, wielder, damageSplit, bIgnoreDamage,
                               modDelta, _bRemote);
      if (GameServer.bServer && !this.isRemoteZombie()) {
        this.addAggro(wielder, float0);
      }

      this.TimeSinceSeenFlesh = 0.0F;
      if (!this.isDead() && !this.isOnFloor() && !bIgnoreDamage &&
              weapon != nullptr &&
              weapon.getScriptItem().getCategories().contains("Blade") &&
              wielder instanceof
          IsoPlayer && this.DistToProper(wielder) <= 0.9F &&
              (this.isCurrentState(AttackState.instance()) ||
               this.isCurrentState(AttackNetworkState.instance()) ||
               this.isCurrentState(LungeState.instance()) ||
               this.isCurrentState(LungeNetworkState.instance()))) {
        this.setHitForce(0.5F);
        this.changeState(StaggerBackState.instance());
      }

      if (GameServer.bServer || GameClient.bClient && this.isDead()) {
        this.lastPlayerHit = wielder.getOnlineID();
      }

      return float0;
    }
  }

  void onMouseLeftClick() {
    if (IsoPlayer.getInstance() != nullptr &&
        !IsoPlayer.getInstance().isAiming()) {
      if (IsoPlayer.getInstance().IsAttackRange(this.getX(), this.getY(),
                                                this.getZ())) {
        Vector2 vector = new Vector2(this.getX(), this.getY());
        vector.x = vector.x - IsoPlayer.getInstance().getX();
        vector.y = vector.y - IsoPlayer.getInstance().getY();
        vector.normalize();
        IsoPlayer.getInstance().DirectionFromVector(vector);
        IsoPlayer.getInstance().AttemptAttack();
      }
    }
  }

  void renderAtlasTexture(float float1, float float2, float float3) {
    if (this.atlasTex != nullptr) {
      if (IsoSprite.globalOffsetX == -1.0F) {
        IsoSprite.globalOffsetX = -IsoCamera.frameState.OffX;
        IsoSprite.globalOffsetY = -IsoCamera.frameState.OffY;
      }

      float float0 = IsoUtils.XToScreen(float1, float2, float3, 0);
      float float4 = IsoUtils.YToScreen(float1, float2, float3, 0);
      this.sx = float0;
      this.sy = float4;
      float0 = this.sx + IsoSprite.globalOffsetX;
      float4 = this.sy + IsoSprite.globalOffsetY;
      ColorInfo colorInfo = inf.set(1.0F, 1.0F, 1.0F, 1.0F);
      if (PerformanceSettings.LightingFrameSkip < 3 &&
          this.getCurrentSquare() != nullptr) {
        this.getCurrentSquare().interpolateLight(
            colorInfo, float1 - this.getCurrentSquare().getX(),
            float2 - this.getCurrentSquare().getY());
      }

      this.atlasTex.render((int)float0, (int)float4, colorInfo.r, colorInfo.g,
                           colorInfo.b, colorInfo.a);
    }
  }

  void render(float x, float y, float z, ColorInfo col, bool bDoChild,
              bool bWallLightingPass, Shader shader) {
    if (this.getCurrentState() == FakeDeadZombieState.instance()) {
      if (this.bDressInRandomOutfit) {
        ModelManager.instance.dressInRandomOutfit(this);
      }

      if (this.atlasTex == nullptr) {
        this.atlasTex = DeadBodyAtlas.instance.getBodyTexture(this);
        DeadBodyAtlas.instance.render();
      }

      if (this.atlasTex != nullptr) {
        this.renderAtlasTexture(x, y, z);
      }
    } else {
      if (this.atlasTex != nullptr) {
        this.atlasTex = nullptr;
      }

      if (IsoCamera.CamCharacter != IsoPlayer.getInstance()) {
        this.setAlphaAndTarget(1.0F);
      }

      super.render(x, y, z, col, bDoChild, bWallLightingPass, shader);
    }
  }

  void renderlast() {
    super.renderlast();
    if (DebugOptions.instance.ZombieRenderCanCrawlUnderVehicle.getValue() &&
        this.isCanCrawlUnderVehicle()) {
      this.renderTextureOverHead("media/ui/FavoriteStar.png");
    }

    if (DebugOptions.instance.ZombieRenderMemory.getValue()) {
      std::string string;
      if (this.target == nullptr) {
        string = "media/ui/Moodles/Moodle_Icon_Bored.png";
      } else if (this.BonusSpotTime == 0.0F) {
        string = "media/ui/Moodles/Moodle_Icon_Angry.png";
      } else {
        string = "media/ui/Moodles/Moodle_Icon_Zombie.png";
      }

      this.renderTextureOverHead(string);
      int int0 = (int)IsoUtils.XToScreenExact(this.x, this.y, this.z, 0);
      int int1 = (int)IsoUtils.YToScreenExact(this.x, this.y, this.z, 0);
      int int2 =
          TextManager.instance.getFontFromEnum(UIFont.Small).getLineHeight();
      int int3;
      TextManager.instance.DrawString(int0, int3 = int1 + int2,
                                      "AllowRepathDelay : " +
                                          this.AllowRepathDelay);
      TextManager.instance.DrawString(int0, int1 = int3 + int2,
                                      "BonusSpotTime : " + this.BonusSpotTime);
      int int4;
      TextManager.instance.DrawString(int0, int4 = int1 + int2,
                                      "TimeSinceSeenFlesh : " +
                                          this.TimeSinceSeenFlesh);
    }
  }

  bool renderTextureInsteadOfModel(float float2, float float3) {
    bool boolean0 = this.isCurrentState(WalkTowardState.instance()) ||
                    this.isCurrentState(PathFindState.instance());
    std::string string0 = "zombie";
    std::string string1 = boolean0 ? "walktoward" : "idle";
    uint8_t byte0 = 4;
    int int0 = (int)(this.m_characterTextureAnimTime /
                     this.m_characterTextureAnimDuration * byte0);
    float float0 = (boolean0 ? 0.67F : 1.0F) * ((float)int0 / byte0);
    DeadBodyAtlas.BodyTexture bodyTexture =
        DeadBodyAtlas.instance.getBodyTexture(this.isFemale(), string0, string1,
                                              this.getDir(), int0, float0);
    if (bodyTexture != nullptr) {
      float float1 = IsoUtils.XToScreen(float2, float3, this.getZ(), 0);
      float float4 = IsoUtils.YToScreen(float2, float3, this.getZ(), 0);
      float1 -= IsoCamera.getOffX();
      float4 -= IsoCamera.getOffY();
      int int1 = IsoCamera.frameState.playerIndex;
      bodyTexture.render(float1, float4, 0.0F, 0.0F, 0.0F, this.getAlpha(int1));
    }

    if (DebugOptions.instance.Character.Debug.Render.Angle.getValue()) {
      tempo.set(this.dir.ToVector());
      this.drawDirectionLine(tempo, 1.2F, 0.0F, 1.0F, 0.0F);
    }

    return true;
  }

  void renderTextureOverHead(const std::string &string) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = IsoUtils.XToScreen(float0, float1, this.getZ(), 0);
    float float3 = IsoUtils.YToScreen(float0, float1, this.getZ(), 0);
    float2 = float2 - IsoCamera.getOffX() - this.offsetX;
    float3 = float3 - IsoCamera.getOffY() - this.offsetY;
    float3 -= 128 / (2 / Core.TileScale);
    Texture texture = Texture.getSharedTexture(string);
    float float4 = Core.getInstance().getZoom(IsoCamera.frameState.playerIndex);
    float4 = Math.max(float4, 1.0F);
    int int0 = (int)(texture.getWidth() * float4);
    int int1 = (int)(texture.getHeight() * float4);
    texture.render((int)float2 - int0 / 2, (int)float3 - int1, int0, int1);
  }

  void updateAlpha(int int0, float float0, float float1) {
    if (this.isFakeDead()) {
      this.setAlphaAndTarget(1.0F);
    } else {
      super.updateAlpha(int0, float0, float1);
    }
  }

  void RespondToSound() {
    if (!this.Ghost) {
      if (!this.isUseless()) {
        if (!GameServer.bServer) {
          if (!GameClient.bClient || !this.isRemoteZombie()) {
            if ((this.getCurrentState() == PathFindState.instance() ||
                 this.getCurrentState() == WalkTowardState.instance()) &&
                this.getPathFindBehavior2().isGoalSound() &&
                (int)this.z == this.getPathTargetZ() &&
                this.bSoundSourceRepeating) {
              float float0 = this.DistToSquared(this.getPathTargetX(),
                                                this.getPathTargetY());
              if (float0 < 25.0F &&
                  LosUtil.lineClear(this.getCell(), (int)this.x, (int)this.y,
                                    (int)this.z, this.getPathTargetX(),
                                    this.getPathTargetY(), (int)this.z,
                                    false) != LosUtil.TestResults.Blocked) {
                this.setVariable("bPathfind", false);
                this.setVariable("bMoving", false);
                this.setPath2(nullptr);
              }
            }

            if (this.soundReactDelay > 0.0F) {
              this.soundReactDelay =
                  this.soundReactDelay -
                  GameTime.getInstance().getMultiplier() / 1.6F;
              if (this.soundReactDelay < 0.0F) {
                this.soundReactDelay = 0.0F;
              }

              if (this.soundReactDelay > 0.0F) {
                return;
              }
            }

            float float1 = 0.0F;
            void *object = null;
            WorldSoundManager.WorldSound worldSound =
                WorldSoundManager.instance.getSoundZomb(this);
            float float2 =
                WorldSoundManager.instance.getSoundAttract(worldSound, this);
            if (float2 <= 0.0F) {
              worldSound = nullptr;
            }

            if (worldSound != nullptr) {
              float1 = float2;
              object = worldSound.source;
              this.soundAttract = float2;
              this.soundAttractTimeout = 60.0F;
            } else if (this.soundAttractTimeout > 0.0F) {
              this.soundAttractTimeout =
                  this.soundAttractTimeout -
                  GameTime.getInstance().getMultiplier() / 1.6F;
              if (this.soundAttractTimeout < 0.0F) {
                this.soundAttractTimeout = 0.0F;
              }
            }

            WorldSoundManager.ResultBiggestSound resultBiggestSound =
                WorldSoundManager.instance.getBiggestSoundZomb(
                    (int)this.getX(), (int)this.getY(), (int)this.getZ(), true,
                    this);
            if (resultBiggestSound.sound != nullptr &&
                (this.soundAttractTimeout == 0.0F ||
                 this.soundAttract * 2.0F < resultBiggestSound.attract)) {
              worldSound = resultBiggestSound.sound;
              float1 = resultBiggestSound.attract;
              object = worldSound.source;
            }

            if (worldSound != nullptr && worldSound.bRepeating &&
                worldSound.z == (int)this.z) {
              float float3 = this.DistToSquared(worldSound.x, worldSound.y);
              if (float3 < 25.0F &&
                  LosUtil.lineClear(this.getCell(), (int)this.x, (int)this.y,
                                    (int)this.z, worldSound.x, worldSound.y,
                                    (int)this.z,
                                    false) != LosUtil.TestResults.Blocked) {
                worldSound = nullptr;
              }
            }

            if (worldSound != nullptr) {
              this.soundAttract = float1;
              this.soundSourceTarget = object;
              this.soundReactDelay = Rand.Next(0, 16);
              this.delayedSound.x = worldSound.x;
              this.delayedSound.y = worldSound.y;
              this.delayedSound.z = worldSound.z;
              this.bSoundSourceRepeating = worldSound.bRepeating;
            }

            if (this.delayedSound.x != -1 && this.soundReactDelay == 0.0F) {
              int int0 = this.delayedSound.x;
              int int1 = this.delayedSound.y;
              int int2 = this.delayedSound.z;
              this.delayedSound.x = -1;
              float float4 = IsoUtils.DistanceManhatten(
                                 this.getX(), this.getY(), int0, int1) /
                             2.5F;
              int0 += Rand.Next((int)(-float4), (int)float4);
              int1 += Rand.Next((int)(-float4), (int)float4);
              if ((this.getCurrentState() == PathFindState.instance() ||
                   this.getCurrentState() == WalkTowardState.instance()) &&
                  (this.getPathFindBehavior2().isGoalLocation() ||
                   this.getPathFindBehavior2().isGoalSound())) {
                if (!IsoUtils.isSimilarDirection(
                        this, int0, int1,
                        this.getPathFindBehavior2().getTargetX(),
                        this.getPathFindBehavior2().getTargetY(), 0.5F)) {
                  this.setTurnAlertedValues(int0, int1);
                  this.pathToSound(int0, int1, int2);
                  this.setLastHeardSound(this.getPathTargetX(),
                                         this.getPathTargetY(),
                                         this.getPathTargetZ());
                  this.AllowRepathDelay = 120.0F;
                  this.timeSinceRespondToSound = 0.0F;
                }

                return;
              }

              if (this.timeSinceRespondToSound < 60.0F) {
                return;
              }

              if (!IsoUtils.isSimilarDirection(
                      this, int0, int1, this.x + this.getForwardDirection().x,
                      this.y + this.getForwardDirection().y, 0.5F)) {
                this.setTurnAlertedValues(int0, int1);
              }

              this.pathToSound(int0, int1, int2);
              this.setLastHeardSound(this.getPathTargetX(),
                                     this.getPathTargetY(),
                                     this.getPathTargetZ());
              this.AllowRepathDelay = 120.0F;
              this.timeSinceRespondToSound = 0.0F;
            }
          }
        }
      }
    }
  }

  void setTurnAlertedValues(int soundX, int soundY) {
    Vector2 vector0 = new Vector2(this.getX() - (soundX + 0.5F),
                                  this.getY() - (soundY + 0.5F));
    float float0 = vector0.getDirectionNeg();
    if (float0 < 0.0F) {
      float0 = Math.abs(float0);
    } else {
      float0 = new Float((Math.PI * 2) - float0);
    }

    double double0 = new Double(Math.toDegrees(float0));
    Vector2 vector1 =
        new Vector2(IsoDirections.reverse(this.getDir()).ToVector().x,
                    IsoDirections.reverse(this.getDir()).ToVector().y);
    vector1.normalize();
    float float1 = vector1.getDirectionNeg();
    if (float1 < 0.0F) {
      float1 = Math.abs(float1);
    } else {
      float1 = (float)(Math.PI * 2) - float1;
    }

    double double1 = Math.toDegrees(float1);
    if ((int)double1 == 360) {
      double1 = 0.0;
    }

    if ((int)double0 == 360) {
      double0 = 0.0;
    }

    std::string string = "0";
    int int0 = 0;
    if (double0 > double1) {
      int0 = (int)(double0 - double1);
      if (int0 > 350 || int0 <= 35) {
        string = "45R";
      }

      if (int0 > 35 && int0 <= 80) {
        string = "90R";
      }

      if (int0 > 80 && int0 <= 125) {
        string = "135R";
      }

      if (int0 > 125 && int0 <= 170) {
        string = "180R";
      }

      if (int0 > 170 && int0 < 215) {
        string = "180L";
      }

      if (int0 >= 215 && int0 < 260) {
        string = "135L";
      }

      if (int0 >= 260 && int0 < 305) {
        string = "90L";
      }

      if (int0 >= 305 && int0 < 350) {
        string = "45L";
      }
    } else {
      int0 = (int)(double1 - double0);
      if (int0 > 10 && int0 <= 55) {
        string = "45L";
      }

      if (int0 > 55 && int0 <= 100) {
        string = "90L";
      }

      if (int0 > 100 && int0 <= 145) {
        string = "135L";
      }

      if (int0 > 145 && int0 <= 190) {
        string = "180L";
      }

      if (int0 > 190 && int0 < 235) {
        string = "180R";
      }

      if (int0 >= 235 && int0 < 280) {
        string = "135R";
      }

      if (int0 >= 280 && int0 < 325) {
        string = "90R";
      }

      if (int0 >= 325 || int0 < 10) {
        string = "45R";
      }
    }

    this.setVariable("turnalertedvalue", string);
    ZombieTurnAlerted.instance().setParams(
        this, vector0.set(soundX + 0.5F - this.x, soundY + 0.5F - this.y)
                  .getDirection());
    this.alerted = true;
    this.networkAI.extraUpdate();
  }

  void clearAggroList() {
    try {
      Arrays.fill(this.aggroList, nullptr);
    } catch (Exception exception) {
    }
  }

  void processAggroList() {
    try {
      for (int int0 = 0; int0 < this.aggroList.length; int0++) {
        if (this.aggroList[int0] != nullptr &&
            this.aggroList[int0].getAggro() <= 0.0F) {
          this.aggroList[int0] = nullptr;
          return;
        }
      }
    } catch (Exception exception) {
    }
  }

  void addAggro(IsoMovingObject other, float damage) {
    try {
      if (this.aggroList[0] == nullptr) {
        this.aggroList[0] = new IsoZombie.Aggro(other, damage);
      } else {
        for (int int0 = 0; int0 < this.aggroList.length; int0++) {
          if (this.aggroList[int0] != nullptr &&
              this.aggroList[int0].obj == other) {
            this.aggroList[int0].addDamage(damage);
            return;
          }
        }

        for (int int1 = 0; int1 < this.aggroList.length; int1++) {
          if (this.aggroList[int1] == nullptr) {
            this.aggroList[int1] = new IsoZombie.Aggro(other, damage);
            return;
          }
        }
      }
    } catch (Exception exception) {
    }
  }

  bool isLeadAggro(IsoMovingObject other) {
    try {
      if (this.aggroList[0] == nullptr) {
        return false;
      } else {
        this.processAggroList();
        if (this.aggroList[0] == nullptr) {
          return false;
        } else {
          IsoMovingObject movingObject = this.aggroList[0].obj;
          float float0 = this.aggroList[0].getAggro();

          for (int int0 = 1; int0 < this.aggroList.length; int0++) {
            if (this.aggroList[int0] != nullptr) {
              if (float0 >= 1.0F && this.aggroList[int0].getAggro() >= 1.0F) {
                return false;
              }

              if (this.aggroList[int0] != nullptr &&
                  float0 < this.aggroList[int0].getAggro()) {
                movingObject = this.aggroList[int0].obj;
                float0 = this.aggroList[int0].getAggro();
              }
            }
          }

          return other = = movingObject && float0 == 1.0F;
        }
      }
    } catch (Exception exception) {
      return false;
    }
  }

  void spotted(IsoMovingObject other, bool bForced) {
    if (GameClient.bClient && this.isRemoteZombie()) {
      if (this.getTarget() != nullptr) {
        this.vectorToTarget.x = this.getTarget().getX();
        this.vectorToTarget.y = this.getTarget().getY();
        this.vectorToTarget.x = this.vectorToTarget.x - this.getX();
        this.vectorToTarget.y = this.vectorToTarget.y - this.getY();
      }
    } else if (this.getCurrentSquare() != nullptr) {
      if (other.getCurrentSquare() != nullptr) {
        if (this.getCurrentSquare().getProperties().Is(IsoFlagType.smoke) ||
            this.isUseless()) {
          this.setTarget(nullptr);
          this.spottedLast = nullptr;
        } else if (!(other instanceof IsoPlayer) ||
                   !((IsoPlayer)other).isGhostMode()) {
          IsoGameCharacter character =
              Type.tryCastTo(other, IsoGameCharacter.class);
          if (character != nullptr && !character.isDead()) {
            if (this.getCurrentSquare() == nullptr) {
              this.ensureOnTile();
            }

            if (other.getCurrentSquare() == nullptr) {
              other.ensureOnTile();
            }

            float float0 = 200.0F;
            int int0 = other instanceof
                IsoPlayer && !GameServer.bServer
                    ? ((IsoPlayer)other).PlayerIndex
                    : 0;
            float float1 =
                (other.getCurrentSquare().lighting[int0].lightInfo().r +
                 other.getCurrentSquare().lighting[int0].lightInfo().g +
                 other.getCurrentSquare().lighting[int0].lightInfo().b) /
                3.0F;
            float float2 =
                RenderSettings.getInstance().getAmbientForPlayer(int0);
            float float3 =
                (this.getCurrentSquare().lighting[int0].lightInfo().r +
                 this.getCurrentSquare().lighting[int0].lightInfo().g +
                 this.getCurrentSquare().lighting[int0].lightInfo().b) /
                3.0F;
            float3 = float3 * float3 * float3;
            if (float1 > 1.0F) {
              float1 = 1.0F;
            }

            if (float1 < 0.0F) {
              float1 = 0.0F;
            }

            if (float3 > 1.0F) {
              float3 = 1.0F;
            }

            if (float3 < 0.0F) {
              float3 = 0.0F;
            }

            float float4 = 1.0F - (float1 - float3);
            if (float1 < 0.2F) {
              float1 = 0.2F;
            }

            if (float2 < 0.2F) {
              float2 = 0.2F;
            }

            if (other.getCurrentSquare().getRoom() !=
                this.getCurrentSquare().getRoom()) {
              float0 = 50.0F;
              if (other.getCurrentSquare().getRoom() != nullptr &&
                      this.getCurrentSquare().getRoom() == nullptr ||
                  other.getCurrentSquare().getRoom() == nullptr &&
                      this.getCurrentSquare().getRoom() != nullptr) {
                float0 = 20.0F;
                if (!character.isAiming() && !character.isSneaking()) {
                  if (other.getMovementLastFrame().getLength() <= 0.04F &&
                      float1 < 0.4F) {
                    float0 = 10.0F;
                  }
                } else if (float1 < 0.4F) {
                  float0 = 0.0F;
                } else {
                  float0 = 10.0F;
                }
              }
            }

            tempo.x = other.getX();
            tempo.y = other.getY();
            tempo.x = tempo.x - this.getX();
            tempo.y = tempo.y - this.getY();
            if (other.getCurrentSquare().getZ() != this.current.getZ()) {
              int int1 = Math.abs(other.getCurrentSquare().getZ() -
                                  this.current.getZ()) *
                         5;
              int1++;
              float0 /= int1;
            }

            float float5 = GameTime.getInstance().getViewDist();
            if (!(tempo.getLength() > float5)) {
              if (GameServer.bServer) {
                this.bIndoorZombie = false;
              }

              if (tempo.getLength() < float5) {
                float5 = tempo.getLength();
              }

              float5 *= 1.1F;
              if (float5 > GameTime.getInstance().getViewDistMax()) {
                float5 = GameTime.getInstance().getViewDistMax();
              }

              tempo.normalize();
              Vector2 vector = this.getLookVector(tempo2);
              float float6 = vector.dot(tempo);
              if (this.DistTo(other) > 20.0F) {
                float0 -= 10000.0F;
              }

              if (float5 > 0.5) {
                if (float6 < -0.4F) {
                  float0 = 0.0F;
                } else if (float6 < -0.2F) {
                  float0 /= 8.0F;
                } else if (float6 < -0.0F) {
                  float0 /= 4.0F;
                } else if (float6 < 0.2F) {
                  float0 /= 2.0F;
                } else if (float6 <= 0.4F) {
                  float0 *= 2.0F;
                } else if (float6 > 0.4F) {
                  float0 *= 8.0F;
                } else if (float6 > 0.6F) {
                  float0 *= 16.0F;
                } else if (float6 > 0.8F) {
                  float0 *= 32.0F;
                }
              }

              if (float0 > 0.0F && this.target instanceof
                  IsoPlayer player && !GameServer.bServer &&
                      player.RemoteID == -1 &&
                      this.current.isCanSee(player.PlayerIndex)) {
                ((IsoPlayer)this.target).targetedByZombie = true;
                ((IsoPlayer)this.target).lastTargeted = 0.0F;
              }

              float0 *= float4;
              int int2 = (int)other.getZ() - (int)this.getZ();
              if (int2 >= 1) {
                float0 /= int2 * 3;
              }

              float float7 = PZMath.clamp(
                  float5 / GameTime.getInstance().getViewDist(), 0.0F, 1.0F);
              float0 *= 1.0F - float7;
              float0 *= 1.0F - float7;
              float0 *= 1.0F - float7;
              float float8 = PZMath.clamp(float5 / 10.0F, 0.0F, 1.0F);
              float0 *= 1.0F + (1.0F - float8) * 10.0F;
              float float9 = other.getMovementLastFrame().getLength();
              if (float9 == 0.0F && float1 <= 0.2F) {
                float1 = 0.0F;
              }

              if (character != nullptr) {
                if (character.getTorchStrength() > 0.0F) {
                  float0 *= 3.0F;
                }

                if (float9 < 0.01F) {
                  float0 *= 0.5F;
                } else if (character.isSneaking()) {
                  float0 *= 0.4F;
                } else if (character.isAiming()) {
                  float0 *= 0.75F;
                } else if (float9 < 0.06F) {
                  float0 *= 0.8F;
                } else if (float9 >= 0.06F) {
                  float0 *= 2.4F;
                }

                if (this.eatBodyTarget != nullptr) {
                  float0 *= 0.6F;
                }

                if (float5 < 5.0F &&
                    (!character.isRunning() && !character.isSneaking() &&
                         !character.isAiming() ||
                     character.isRunning())) {
                  float0 *= 3.0F;
                }

                if (this.spottedLast == other &&
                    this.TimeSinceSeenFlesh < 120.0F) {
                  float0 = 1000.0F;
                }

                float0 *= character.getSneakSpotMod();
                float0 *= float2;
                if (this.target != other && this.target != nullptr) {
                  float float10 = IsoUtils.DistanceManhatten(
                      this.getX(), this.getY(), other.getX(), other.getY());
                  float float11 = IsoUtils.DistanceManhatten(
                      this.getX(), this.getY(), this.target.getX(),
                      this.target.getY());
                  if (float10 > float11) {
                    return;
                  }
                }

                float0 *= 0.3F;
                if (bForced) {
                  float0 = 1000000.0F;
                }

                if (this.BonusSpotTime > 0.0F) {
                  float0 = 1000000.0F;
                }

                float0 *= 1.2F;
                if (this.sight == 1) {
                  float0 *= 2.5F;
                }

                if (this.sight == 3) {
                  float0 *= 0.45F;
                }

                if (this.inactive) {
                  float0 *= 0.25F;
                }

                float0 *= 0.25F;
                if (other instanceof
                    IsoPlayer &&
                        ((IsoPlayer)other).Traits.Inconspicuous.isSet()) {
                  float0 *= 0.5F;
                }

                if (other instanceof
                    IsoPlayer &&
                        ((IsoPlayer)other).Traits.Conspicuous.isSet()) {
                  float0 *= 2.0F;
                }

                float0 *= 1.6F;
                void *object = null;
                IsoGridSquare square = null;
                if (this.getCurrentSquare() != other.getCurrentSquare() &&
                        other instanceof
                    IsoPlayer && ((IsoPlayer)other).isSneaking()) {
                  int int3 = Math.abs(this.getCurrentSquare().getX() -
                                      other.getCurrentSquare().getX());
                  int int4 = Math.abs(this.getCurrentSquare().getY() -
                                      other.getCurrentSquare().getY());
                  if (int3 > int4) {
                    if (this.getCurrentSquare().getX() -
                            other.getCurrentSquare().getX() >
                        0) {
                      object =
                          other.getCurrentSquare().nav[IsoDirections.E.index()];
                    } else {
                      object = other.getCurrentSquare();
                      square =
                          other.getCurrentSquare().nav[IsoDirections.W.index()];
                    }
                  } else if (this.getCurrentSquare().getY() -
                                 other.getCurrentSquare().getY() >
                             0) {
                    object =
                        other.getCurrentSquare().nav[IsoDirections.S.index()];
                  } else {
                    object = other.getCurrentSquare();
                    square =
                        other.getCurrentSquare().nav[IsoDirections.N.index()];
                  }

                  if (object != nullptr && other instanceof IsoGameCharacter) {
                    float float12 = ((IsoGameCharacter)other).checkIsNearWall();
                    if (float12 == 1.0F && square != nullptr) {
                      float12 = square.getGridSneakModifier(true);
                    }

                    if (float12 > 1.0F) {
                      float float13 = other.DistTo(((IsoGridSquare)object).x,
                                                   ((IsoGridSquare)object).y);
                      if (float13 > 1.0F) {
                        float12 /= float13;
                      }

                      float0 /= float12;
                    }
                  }
                }

                float0 = (float)Math.floor(float0);
                bool boolean0 = false;
                float0 = Math.min(float0, 400.0F);
                float0 /= 400.0F;
                float0 = Math.max(0.0F, float0);
                float0 = Math.min(1.0F, float0);
                float float14 = GameTime.instance.getMultiplier();
                float0 = (float)(1.0 - Math.pow(1.0F - float0, float14));
                float0 *= 100.0F;
                if (Rand.Next(10000) / 100.0F < float0) {
                  boolean0 = true;
                }

                if (!GameClient.bClient && !GameServer.bServer ||
                    NetworkZombieManager.canSpotted(this) ||
                    other == this.target) {
                  if (!boolean0) {
                    if (float0 > 20.0F && other instanceof
                        IsoPlayer && float5 < 15.0F) {
                      ((IsoPlayer)other).bCouldBeSeenThisFrame = true;
                    }

                    if (!((IsoPlayer)other).isbCouldBeSeenThisFrame() &&
                        !((IsoPlayer)other).isbSeenThisFrame() &&
                        ((IsoPlayer)other).isSneaking() &&
                        ((IsoPlayer)other).isJustMoved() &&
                        Rand.Next(
                            (int)(1100.0F *
                                  GameTime.instance.getInvMultiplier())) == 0) {
                      if (GameServer.bServer) {
                        GameServer.addXp((IsoPlayer)other,
                                         PerkFactory.Perks.Sneak, 1);
                      } else {
                        ((IsoPlayer)other)
                            .getXp()
                            .AddXP(PerkFactory.Perks.Sneak, 1.0F);
                      }
                    }

                    if (!((IsoPlayer)other).isbCouldBeSeenThisFrame() &&
                        !((IsoPlayer)other).isbSeenThisFrame() &&
                        ((IsoPlayer)other).isSneaking() &&
                        ((IsoPlayer)other).isJustMoved() &&
                        Rand.Next(
                            (int)(1100.0F *
                                  GameTime.instance.getInvMultiplier())) == 0) {
                      if (GameServer.bServer) {
                        GameServer.addXp((IsoPlayer)other,
                                         PerkFactory.Perks.Lightfoot, 1);
                      } else {
                        ((IsoPlayer)other)
                            .getXp()
                            .AddXP(PerkFactory.Perks.Lightfoot, 1.0F);
                      }
                    }
                  } else {
                    if (other instanceof IsoPlayer) {
                      ((IsoPlayer)other).setbSeenThisFrame(true);
                    }

                    if (!bForced) {
                      this.BonusSpotTime = 120.0F;
                    }

                    this.LastTargetSeenX = (int)other.getX();
                    this.LastTargetSeenY = (int)other.getY();
                    this.LastTargetSeenZ = (int)other.getZ();
                    if (this.stateMachine.getCurrent() !=
                        StaggerBackState.instance()) {
                      if (this.target != other) {
                        this.targetSeenTime = 0.0F;
                        if (GameServer.bServer && !this.isRemoteZombie()) {
                          this.addAggro(other, 1.0F);
                        }
                      }

                      this.setTarget(other);
                      this.vectorToTarget.x = other.getX();
                      this.vectorToTarget.y = other.getY();
                      this.vectorToTarget.x =
                          this.vectorToTarget.x - this.getX();
                      this.vectorToTarget.y =
                          this.vectorToTarget.y - this.getY();
                      float float15 = this.vectorToTarget.getLength();
                      if (!bForced) {
                        this.TimeSinceSeenFlesh = 0.0F;
                        this.targetSeenTime =
                            this.targetSeenTime +
                            GameTime.getInstance()
                                .getRealworldSecondsSinceLastUpdate();
                      }

                      if (this.target != this.spottedLast ||
                          this.getCurrentState() != LungeState.instance() ||
                          !(this.LungeTimer > 0.0F)) {
                        if (this.target != this.spottedLast ||
                            this.getCurrentState() !=
                                AttackVehicleState.instance()) {
                          if ((int)this.getZ() == (int)this.target.getZ() &&
                              (float15 <= 3.5F || this.target instanceof
                               IsoGameCharacter &&
                                   ((IsoGameCharacter)this.target)
                                           .getVehicle() != nullptr &&
                                   float15 <= 4.0F) &&
                              this.getStateEventDelayTimer() <= 0.0F &&
                              !PolygonalMap2.instance.lineClearCollide(
                                  this.getX(), this.getY(), other.x, other.y,
                                  (int)this.getZ(), other)) {
                            this.setTarget(other);
                            if (this.getCurrentState() ==
                                LungeState.instance()) {
                              return;
                            }
                          }

                          this.spottedLast = other;
                          if (!this.Ghost &&
                              !this.getCurrentSquare().getProperties().Is(
                                  IsoFlagType.smoke)) {
                            this.setTarget(other);
                            if (this.AllowRepathDelay > 0.0F) {
                              return;
                            }

                            if (this.target instanceof
                                IsoGameCharacter &&
                                    ((IsoGameCharacter)this.target)
                                            .getVehicle() != nullptr) {
                              if ((this.getCurrentState() ==
                                       PathFindState.instance() ||
                                   this.getCurrentState() ==
                                       WalkTowardState.instance()) &&
                                  this.getPathFindBehavior2().getTargetChar() ==
                                      this.target) {
                                return;
                              }

                              if (this.getCurrentState() ==
                                  AttackVehicleState.instance()) {
                                return;
                              }

                              BaseVehicle vehicle =
                                  ((IsoGameCharacter)this.target).getVehicle();
                              if (Math.abs(vehicle.getCurrentSpeedKmHour()) >
                                      0.8F &&
                                  this.DistToSquared(vehicle) <= 16.0F) {
                                return;
                              }

                              this.pathToCharacter(
                                  (IsoGameCharacter)this.target);
                              this.AllowRepathDelay = 10.0F;
                              return;
                            }

                            this.pathToCharacter(character);
                            if (Rand.Next(5) == 0) {
                              this.spotSoundDelay = 200;
                            }

                            this.AllowRepathDelay = 480.0F;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  void Move(Vector2 dir) {
    if (!GameClient.bClient || this.authOwner != nullptr) {
      this.nx = this.nx + dir.x * GameTime.instance.getMultiplier();
      this.ny = this.ny + dir.y * GameTime.instance.getMultiplier();
      this.movex = dir.x;
      this.movey = dir.y;
    }
  }

  void MoveUnmodded(Vector2 dir) {
    if (this.speedType == 1 &&
            (this.isCurrentState(LungeState.instance()) ||
             this.isCurrentState(LungeNetworkState.instance()) ||
             this.isCurrentState(AttackState.instance()) ||
             this.isCurrentState(AttackNetworkState.instance()) ||
             this.isCurrentState(StaggerBackState.instance()) ||
             this.isCurrentState(ZombieHitReactionState.instance())) &&
            this.target instanceof
        IsoGameCharacter) {
      float float0 = this.target.nx - this.x;
      float float1 = this.target.ny - this.y;
      float float2 = (float)Math.sqrt(float0 * float0 + float1 * float1);
      float2 -= this.getWidth() + this.target.getWidth() - 0.1F;
      float2 = Math.max(0.0F, float2);
      if (dir.getLength() > float2) {
        dir.setLength(float2);
      }
    }

    if (this.isRemoteZombie()) {
      float float3 =
          IsoUtils.DistanceTo(this.realx, this.realy, this.networkAI.targetX,
                              this.networkAI.targetY);
      if (float3 > 1.0F) {
        Vector2 vector = new Vector2(this.realx - this.x, this.realy - this.y);
        vector.normalize();
        float float4 = 0.5F + IsoUtils.smoothstep(
                                  0.5F, 1.5F,
                                  IsoUtils.DistanceTo(this.x, this.y,
                                                      this.networkAI.targetX,
                                                      this.networkAI.targetY) /
                                      float3);
        float float5 = dir.getLength();
        dir.normalize();
        PZMath.lerp(dir, dir, vector, 0.5F);
        dir.setLength(float5 * float4);
      }
    }

    super.MoveUnmodded(dir);
  }

  bool canBeDeletedUnnoticed(float minDistance) {
    if (!GameClient.bClient) {
      return false;
    } else {
      float float0 = Float.POSITIVE_INFINITY;
      std::vector arrayList = GameClient.instance.getPlayers();

      for (int int0 = 0; int0 < arrayList.size(); int0++) {
        IsoPlayer player = (IsoPlayer)arrayList.get(int0);
        float float1 =
            player.getDotWithForwardDirection(this.getX(), this.getY());
        float float2 = LightingJNI.calculateVisionCone(player) + 0.2F;
        if (float1 > -float2) {
          return false;
        }

        float float3 =
            IsoUtils.DistanceToSquared(this.x, this.y, player.x, player.y);
        if (float3 < float0) {
          float0 = float3;
        }
      }

      return float0 > minDistance * minDistance;
    }
  }

  void DoFootstepSound(const std::string &type) {
    ParameterCharacterMovementSpeed.MovementType movementType =
        ParameterCharacterMovementSpeed.MovementType.Walk;
    float float0 = 0.5F;
    switch (type) {
    case "sneak_walk":
      float0 = 0.25F;
      movementType = ParameterCharacterMovementSpeed.MovementType.SneakWalk;
      break;
    case "sneak_run":
      float0 = 0.25F;
      movementType = ParameterCharacterMovementSpeed.MovementType.SneakRun;
      break;
    case "strafe":
      float0 = 0.5F;
      movementType = ParameterCharacterMovementSpeed.MovementType.Strafe;
      break;
    case "walk":
      float0 = 0.5F;
      movementType = ParameterCharacterMovementSpeed.MovementType.Walk;
      break;
    case "run":
      float0 = 0.75F;
      movementType = ParameterCharacterMovementSpeed.MovementType.Run;
      break;
    case "sprint":
      float0 = 1.0F;
      movementType = ParameterCharacterMovementSpeed.MovementType.Sprint;
    }

    if (!GameServer.bServer && !this.getFMODParameters().parameterList.contains(
                                   this.parameterCharacterMovementSpeed)) {
      this.getFMODParameters().add(this.parameterCharacterMovementSpeed);
      this.getFMODParameters().add(this.parameterFootstepMaterial);
      this.getFMODParameters().add(this.parameterFootstepMaterial2);
      this.getFMODParameters().add(this.parameterShoeType);
    }

    this.parameterCharacterMovementSpeed.setMovementType(movementType);
    this.DoFootstepSound(float0);
  }

  void DoFootstepSound(float volume) {
    if (!GameServer.bServer) {
      if (!(volume <= 0.0F)) {
        if (this.getCurrentSquare() != nullptr) {
          if (GameClient.bClient && this.authOwner == nullptr) {
            if (this.def != nullptr && this.sprite != nullptr &&
                this.sprite.CurrentAnim != nullptr &&
                (this.sprite.CurrentAnim.name.contains("Run") ||
                 this.sprite.CurrentAnim.name.contains("Walk"))) {
              int int0 = (int)this.def.Frame;
              bool boolean0;
              if (int0 >= 0 && int0 < 5) {
                boolean0 = this.stepFrameLast < 0 || this.stepFrameLast > 5;
              } else {
                boolean0 = this.stepFrameLast < 5;
              }

              if (boolean0) {
                for (int int1 = 0; int1 < IsoPlayer.numPlayers; int1++) {
                  IsoPlayer player = IsoPlayer.players[int1];
                  if (player != nullptr &&
                      player.DistToSquared(this) < 225.0F) {
                    ZombieFootstepManager.instance.addCharacter(this);
                    break;
                  }
                }
              }

              this.stepFrameLast = int0;
            } else {
              this.stepFrameLast = -1;
            }
          } else {
            bool boolean1 = SoundManager.instance.isListenerInRange(
                this.getX(), this.getY(), 15.0F);
            if (boolean1) {
              this.footstepVolume = volume;
              ZombieFootstepManager.instance.addCharacter(this);
            }
          }
        }
      }
    }
  }

  void preupdate() {
    if (GameServer.bServer && this.thumpSent) {
      this.thumpFlag = 0;
      this.thumpSent = false;
    }

    this.FollowCount = 0;
    if (GameClient.bClient) {
      this.networkAI.updateHitVehicle();
      if (!this.isLocal()) {
        this.networkAI.preupdate();
      } else if (this.isKnockedDown() && !this.isOnFloor()) {
        HitReactionNetworkAI hitReactionNetworkAI =
            this.getHitReactionNetworkAI();
        if (hitReactionNetworkAI.isSetup() &&
            !hitReactionNetworkAI.isStarted()) {
          hitReactionNetworkAI.start();
        }
      }
    }

    super.preupdate();
  }

  void postupdate() {
    IsoZombie.s_performance.postUpdate.invokeAndMeasure(
        this, IsoZombie::postUpdateInternal);
  }

  void postUpdateInternal() {
    if (this.target instanceof IsoPlayer) {
      ((IsoPlayer)this.target).getStats().NumChasingZombies++;
    }

    super.postupdate();
    if (this.current == nullptr &&
        (!GameClient.bClient || this.authOwner != nullptr)) {
      this.removeFromWorld();
      this.removeFromSquare();
    }

    if (!GameServer.bServer) {
      IsoPlayer player0 = this.getReanimatedPlayer();
      if (player0 != nullptr) {
        player0.setX(this.getX());
        player0.setY(this.getY());
        player0.setZ(this.getZ());
        player0.setDir(this.getDir());
        player0.setForwardDirection(this.getForwardDirection());
        AnimationPlayer animationPlayer0 = this.getAnimationPlayer();
        AnimationPlayer animationPlayer1 = player0.getAnimationPlayer();
        if (animationPlayer0 != nullptr && animationPlayer0.isReady() &&
            animationPlayer1 != nullptr && animationPlayer1.isReady()) {
          animationPlayer1.setTargetAngle(animationPlayer0.getAngle());
          animationPlayer1.setAngleToTarget();
        }

        player0.setCurrent(this.getCell().getGridSquare(
            (int)player0.x, (int)player0.y, (int)player0.z));
        player0.updateLightInfo();
        if (player0.soundListener != nullptr) {
          player0.soundListener.setPos(player0.getX(), player0.getY(),
                                       player0.getZ());
          player0.soundListener.tick();
        }

        IsoPlayer player1 = IsoPlayer.getInstance();
        IsoPlayer.setInstance(player0);
        player0.updateLOS();
        IsoPlayer.setInstance(player1);
        if (GameClient.bClient && this.authOwner == nullptr &&
            this.networkUpdate.Check()) {
          GameClient.instance.sendPlayer(player0);
        }

        player0.dirtyRecalcGridStackTime = 2.0F;
      }
    }

    if (this.targetSeenTime > 0.0F && !this.isTargetVisible()) {
      this.targetSeenTime = 0.0F;
    }
  }

  bool isSolidForSeparate() {
    if (this.getCurrentState() != FakeDeadZombieState.instance() &&
        this.getCurrentState() != ZombieFallDownState.instance() &&
        this.getCurrentState() != ZombieOnGroundState.instance() &&
        this.getCurrentState() != ZombieGetUpState.instance() &&
        (this.getCurrentState() != ZombieHitReactionState.instance() ||
         this.speedType == 1)) {
      return this.isSitAgainstWall() ? false : super.isSolidForSeparate();
    } else {
      return false;
    }
  }

  bool isPushableForSeparate() {
    if (this.getCurrentState() == ThumpState.instance() ||
        this.getCurrentState() == AttackState.instance() ||
        this.getCurrentState() == AttackVehicleState.instance() ||
        this.getCurrentState() == ZombieEatBodyState.instance() ||
        this.getCurrentState() == ZombieFaceTargetState.instance()) {
      return false;
    } else {
      return this.isSitAgainstWall() ? false : super.isPushableForSeparate();
    }
  }

  bool isPushedByForSeparate(IsoMovingObject other) {
    if (other instanceof IsoZombie &&
                             ((IsoZombie)other).getCurrentState() ==
                                 ZombieHitReactionState.instance() &&
                             !((IsoZombie)other).collideWhileHit) {
      return false;
    } else if (this.getCurrentState() == ZombieHitReactionState.instance() &&
               !this.collideWhileHit) {
      return false;
    } else {
      return GameClient.bClient && other instanceof
          IsoZombie && !NetworkZombieSimulator.getInstance().isZombieSimulated(
                           this.getOnlineID())
              ? false
              : super.isPushedByForSeparate(other);
    }
  }

  void update() {
    IsoZombie.s_performance.update.invokeAndMeasure(this,
                                                    IsoZombie::updateInternal);
  }

  void updateInternal() {
    if (GameClient.bClient && !this.isRemoteZombie()) {
      ZombieCountOptimiser.incrementZombie(this);
      MPStatistics.clientZombieUpdated();
    } else if (GameServer.bServer) {
      MPStatistics.serverZombieUpdated();
    }

    if (SandboxOptions.instance.Lore.ActiveOnly.getValue() > 1) {
      if ((SandboxOptions.instance.Lore.ActiveOnly.getValue() != 2 ||
           GameTime.instance.getHour() < 20 &&
               GameTime.instance.getHour() > 8) &&
          (SandboxOptions.instance.Lore.ActiveOnly.getValue() != 3 ||
           GameTime.instance.getHour() <= 8 ||
           GameTime.instance.getHour() >= 20)) {
        this.makeInactive(true);
      } else {
        this.makeInactive(false);
      }
    }

    if (this.bCrawling) {
      if (this.actionContext.getGroup() !=
          ActionGroup.getActionGroup("zombie-crawler")) {
        this.advancedAnimator.OnAnimDataChanged(false);
        this.initializeStates();
        this.actionContext.setGroup(
            ActionGroup.getActionGroup("zombie-crawler"));
      }
    } else if (this.actionContext.getGroup() !=
               ActionGroup.getActionGroup("zombie")) {
      this.advancedAnimator.OnAnimDataChanged(false);
      this.initializeStates();
      this.actionContext.setGroup(ActionGroup.getActionGroup("zombie"));
    }

    if (this.getThumpTimer() > 0) {
      this.thumpTimer--;
    }

    BaseVehicle vehicle = this.getNearVehicle();
    if (vehicle != nullptr) {
      if (this.target == nullptr && vehicle.hasLightbar() &&
          vehicle.lightbarSirenMode.get() > 0) {
        VehiclePart part = vehicle.getUseablePart(this, false);
        if (part != nullptr && part.getSquare().DistTo(this) < 0.7F) {
          this.setThumpTarget(vehicle);
        }
      }

      if (vehicle.isAlarmed() && !vehicle.isPreviouslyEntered() &&
          Rand.Next(10000) < 1) {
        vehicle.triggerAlarm();
      }
    }

    this.doDeferredMovement();
    this.updateEmitter();
    if (this.spotSoundDelay > 0) {
      this.spotSoundDelay--;
    }

    if (GameClient.bClient && this.authOwner == nullptr) {
      if (this.lastRemoteUpdate > 800 &&
              (this.legsSprite.CurrentAnim.name == "ZombieDeath") ||
          this.legsSprite.CurrentAnim.name == "ZombieStaggerBack")
                        || this.legsSprite.CurrentAnim.name == "ZombieGetUp")
                )) {
                          DebugLog.log(DebugType.Zombie,
                                       "removing stale zombie 800 id=" +
                                           this.OnlineID);
                          VirtualZombieManager.instance.removeZombieFromWorld(
                              this);
                          return;
                        }

      if (GameClient.bFastForward) {
        VirtualZombieManager.instance.removeZombieFromWorld(this);
        return;
      }
    }

    if (GameClient.bClient && this.authOwner == nullptr &&
        this.lastRemoteUpdate < 2000 &&
        this.lastRemoteUpdate + 1000 / PerformanceSettings.getLockFPS() >
            2000) {
      DebugLog.log(DebugType.Zombie,
                   "lastRemoteUpdate 2000+ id=" + this.OnlineID);
    }

    this.lastRemoteUpdate = (short)(this.lastRemoteUpdate +
                                    1000 / PerformanceSettings.getLockFPS());
    if (!GameClient.bClient || this.authOwner != nullptr ||
        this.bRemote && this.lastRemoteUpdate <= 5000) {
      this.sprite = this.legsSprite;
      if (this.sprite != nullptr) {
        this.updateCharacterTextureAnimTime();
        if (GameServer.bServer && this.bIndoorZombie) {
          super.update();
        } else {
          this.BonusSpotTime = PZMath.clamp(
              this.BonusSpotTime - GameTime.instance.getMultiplier(), 0.0F,
              Float.MAX_VALUE);
          this.TimeSinceSeenFlesh = PZMath.clamp(
              this.TimeSinceSeenFlesh + GameTime.instance.getMultiplier(), 0.0F,
              Float.MAX_VALUE);
          if (this.getStateMachine().getCurrent() !=
                  ClimbThroughWindowState.instance() &&
              this.getStateMachine().getCurrent() !=
                  ClimbOverFenceState.instance() &&
              this.getStateMachine().getCurrent() !=
                  CrawlingZombieTurnState.instance() &&
              this.getStateMachine().getCurrent() !=
                  ZombieHitReactionState.instance() &&
              this.getStateMachine().getCurrent() !=
                  ZombieFallDownState.instance()) {
            this.setCollidable(true);
            LuaEventManager.triggerEvent("OnZombieUpdate", this);
            if (Core.bLastStand &&
                this.getStateMachine().getCurrent() != ThumpState.instance() &&
                this.getStateMachine().getCurrent() != AttackState.instance() &&
                this.TimeSinceSeenFlesh > 120.0F && Rand.Next(36000) == 0) {
              IsoPlayer player = null;
              float float0 = 1000000.0F;

              for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
                if (IsoPlayer.players[int0] != nullptr &&
                    IsoPlayer.players[int0].DistTo(this) < float0 &&
                    !IsoPlayer.players[int0].isDead()) {
                  float0 = IsoPlayer.players[int0].DistTo(this);
                  player = IsoPlayer.players[int0];
                }
              }

              if (player != nullptr) {
                this.AllowRepathDelay = -1.0F;
                this.pathToCharacter(player);
              }
            } else {
              if (GameServer.bServer) {
                this.vehicle4testCollision = nullptr;
              } else if (GameClient.bClient) {
                if (this.vehicle4testCollision != nullptr &&
                    this.vehicle4testCollision.updateHitByVehicle(this)) {
                  super.update();
                  this.vehicle4testCollision = nullptr;
                  return;
                }
              } else if (this.Health > 0.0F &&
                         this.vehicle4testCollision != nullptr &&
                         this.testCollideWithVehicles(
                             this.vehicle4testCollision)) {
                this.vehicle4testCollision = nullptr;
                return;
              }

              this.vehicle4testCollision = nullptr;
              if (this.BonusSpotTime > 0.0F && this.spottedLast != nullptr &&
                  !((IsoGameCharacter)this.spottedLast).isDead()) {
                this.spotted(this.spottedLast, true);
              }

              if (GameServer.bServer && this.getStateMachine().getCurrent() ==
                                            BurntToDeath.instance()) {
                DebugLog.log(DebugType.Zombie,
                             "Zombie is burning " + this.OnlineID);
              }

              super.update();
              if (VirtualZombieManager.instance.isReused(this)) {
                DebugLog.log(DebugType.Zombie,
                             "Zombie added to ReusableZombies after "
                             "super.update - RETURNING " +
                                 this);
              } else if (this.getStateMachine().getCurrent() !=
                             ClimbThroughWindowState.instance() &&
                         this.getStateMachine().getCurrent() !=
                             ClimbOverFenceState.instance() &&
                         this.getStateMachine().getCurrent() !=
                             CrawlingZombieTurnState.instance()) {
                this.ensureOnTile();
                State state = this.stateMachine.getCurrent();
                if (state != StaggerBackState.instance() &&
                    state != BurntToDeath.instance() &&
                    state != FakeDeadZombieState.instance() &&
                    state != ZombieFallDownState.instance() &&
                    state != ZombieOnGroundState.instance() &&
                    state != ZombieHitReactionState.instance() &&
                    state != ZombieGetUpState.instance()) {
                  if (GameServer.bServer && this.OnlineID == -1) {
                    this.OnlineID = ServerMap.instance.getUniqueZombieId();
                  } else if (state == PathFindState.instance() &&
                             this.finder.progress ==
                                 AStarPathFinder.PathFindProgress.notyetfound) {
                    if (this.bCrawling) {
                      this.PlayAnim("ZombieCrawl");
                      this.def.AnimFrameIncrease = 0.0F;
                    } else {
                      this.PlayAnim("ZombieIdle");
                      this.def.AnimFrameIncrease =
                          0.08F + Rand.Next(1000) / 8000.0F;
                      this.def.AnimFrameIncrease *= 0.5F;
                    }
                  } else if (state != AttackState.instance() &&
                             state != AttackVehicleState.instance() &&
                             (this.nx != this.x || this.ny != this.y)) {
                    if (this.walkVariantUse == nullptr ||
                        state != LungeState.instance() &&
                            state != LungeNetworkState.instance()) {
                      this.walkVariantUse = this.walkVariant;
                    }

                    if (this.bCrawling) {
                      this.walkVariantUse = "ZombieCrawl";
                    }

                    if (state != ZombieIdleState.instance() &&
                        state != StaggerBackState.instance() &&
                        state != ThumpState.instance() &&
                        state != FakeDeadZombieState.instance()) {
                      if (this.bRunning) {
                        this.PlayAnim("Run");
                        this.def.setFrameSpeedPerFrame(0.33F);
                      } else {
                        this.PlayAnim(this.walkVariantUse);
                        this.def.setFrameSpeedPerFrame(0.26F);
                        this.def.AnimFrameIncrease =
                            this.def.AnimFrameIncrease * this.speedMod;
                      }

                      this.setShootable(true);
                    }
                  }

                  this.shootable = true;
                  this.solid = true;
                  this.tryThump(nullptr);
                  this.damageSheetRope();
                  this.AllowRepathDelay = PZMath.clamp(
                      this.AllowRepathDelay - GameTime.instance.getMultiplier(),
                      0.0F, Float.MAX_VALUE);
                  if (this.TimeSinceSeenFlesh > this.memory &&
                      this.target != nullptr) {
                    this.setTarget(nullptr);
                  }

                  if (this.target instanceof
                      IsoGameCharacter &&
                          ((IsoGameCharacter)this.target).ReanimatedCorpse !=
                              nullptr) {
                    this.setTarget(nullptr);
                  }

                  if (this.target != nullptr) {
                    this.vectorToTarget.x = this.target.getX();
                    this.vectorToTarget.y = this.target.getY();
                    this.vectorToTarget.x = this.vectorToTarget.x - this.getX();
                    this.vectorToTarget.y = this.vectorToTarget.y - this.getY();
                    this.updateZombieTripping();
                  }

                  if (this.getCurrentState() != PathFindState.instance() &&
                      this.getCurrentState() != WalkTowardState.instance() &&
                      this.getCurrentState() !=
                          ClimbThroughWindowState.instance()) {
                    this.setLastHeardSound(-1, -1, -1);
                  }

                  if (this.TimeSinceSeenFlesh > 240.0F &&
                      this.timeSinceRespondToSound > 5.0F) {
                    this.RespondToSound();
                  }

                  this.timeSinceRespondToSound =
                      this.timeSinceRespondToSound +
                      GameTime.getInstance().getMultiplier() / 1.6F;
                  this.separate();
                  this.updateSearchForCorpse();
                  if (this.TimeSinceSeenFlesh > 2000.0F &&
                      this.timeSinceRespondToSound > 2000.0F) {
                    ZombieGroupManager.instance.update(this);
                  }
                }
              }
            }
          } else {
            super.update();
          }
        }
      }
    } else {
      DebugLog.log(DebugType.Zombie,
                   "removing stale zombie 5000 id=" + this.OnlineID);
      DebugLog.log("Zombie: removing stale zombie 5000 id=" + this.OnlineID);
      VirtualZombieManager.instance.removeZombieFromWorld(this);
    }
  }

  void calculateStats() {}

  void updateZombieTripping() {
    if (this.speedType == 1 && StringUtils.isNullOrEmpty(this.getBumpType()) &&
        this.target != nullptr && Rand.NextBool(Rand.AdjustForFramerate(750))) {
      this.setBumpType("trippingFromSprint");
    }
  }

  void updateVocalProperties() {
    if (!GameServer.bServer) {
      bool boolean0 = SoundManager.instance.isListenerInRange(
          this.getX(), this.getY(), 20.0F);
      if (this.vocalEvent != 0L &&
          !this.getEmitter().isPlaying(this.vocalEvent)) {
        this.vocalEvent = 0L;
      }

      if (!this.isDead() && !this.isFakeDead() && boolean0) {
        ZombieVocalsManager.instance.addCharacter(this);
      }

      if (this.vocalEvent != 0L && !this.isDead() && this.isFakeDead() &&
          this.getEmitter().isPlaying(this.vocalEvent)) {
        this.getEmitter().stopSoundLocal(this.vocalEvent);
        this.vocalEvent = 0L;
      }
    }
  }

  void setVehicleHitLocation(BaseVehicle vehicle) {
    if (!this.getFMODParameters().parameterList.contains(
            this.parameterVehicleHitLocation)) {
      this.getFMODParameters().add(this.parameterVehicleHitLocation);
    }

    ParameterVehicleHitLocation.HitLocation hitLocation =
        ParameterVehicleHitLocation.calculateLocation(vehicle, this.getX(),
                                                      this.getY(), this.getZ());
    this.parameterVehicleHitLocation.setLocation(hitLocation);
  }

  void updateSearchForCorpse() {
    if (!this.bCrawling && this.target == nullptr &&
        this.eatBodyTarget == nullptr) {
      if (this.bodyToEat != nullptr) {
        if (this.bodyToEat.getStaticMovingObjectIndex() == -1) {
          this.bodyToEat = nullptr;
        } else if (!this.isEatingOther(this.bodyToEat) &&
                   this.bodyToEat.getEatingZombies().size() >= 3) {
          this.bodyToEat = nullptr;
        }
      }

      if (this.bodyToEat == nullptr) {
        this.checkForCorpseTimer =
            this.checkForCorpseTimer -
            GameTime.getInstance().getMultiplier() / 1.6F;
        if (this.checkForCorpseTimer <= 0.0F) {
          this.checkForCorpseTimer = 10000.0F;
          tempBodies.clear();

          for (int int0 = -10; int0 < 10; int0++) {
            for (int int1 = -10; int1 < 10; int1++) {
              IsoGridSquare square = this.getCell().getGridSquare(
                  (double)(this.getX() + int0), (double)(this.getY() + int1),
                  (double)this.getZ());
              if (square != nullptr) {
                IsoDeadBody deadBody = square.getDeadBody();
                if (deadBody != nullptr && !deadBody.isSkeleton() &&
                    !deadBody.isZombie() &&
                    deadBody.getEatingZombies().size() < 3 &&
                    !PolygonalMap2.instance.lineClearCollide(
                        this.getX(), this.getY(), deadBody.x, deadBody.y,
                        (int)this.getZ(), nullptr, false, true)) {
                  tempBodies.add(deadBody);
                }
              }
            }
          }

          if (!tempBodies.isEmpty()) {
            this.bodyToEat = PZArrayUtil.pickRandom(tempBodies);
            tempBodies.clear();
          }
        }
      }

      if (this.bodyToEat != nullptr &&
          this.isCurrentState(ZombieIdleState.instance())) {
        if (this.DistToSquared(this.bodyToEat) > 1.0F) {
          Vector2 vector =
              tempo.set(this.x - this.bodyToEat.x, this.y - this.bodyToEat.y);
          vector.setLength(0.5F);
          this.pathToLocationF(this.bodyToEat.getX() + vector.x,
                               this.bodyToEat.getY() + vector.y,
                               this.bodyToEat.getZ());
        }
      }
    } else {
      this.checkForCorpseTimer = 10000.0F;
      this.bodyToEat = nullptr;
    }
  }

  void damageSheetRope() {
    if (Rand.Next(30) == 0 && this.current != nullptr &&
        (this.current.Is(IsoFlagType.climbSheetN) ||
         this.current.Is(IsoFlagType.climbSheetE) ||
         this.current.Is(IsoFlagType.climbSheetS) ||
         this.current.Is(IsoFlagType.climbSheetW))) {
      IsoObject object = this.current.getSheetRope();
      if (object != nullptr) {
        object.sheetRopeHealth = object.sheetRopeHealth - Rand.Next(5, 15);
        if (object.sheetRopeHealth < 40.0F) {
          this.current.damageSpriteSheetRopeFromBottom(
              nullptr, this.current.Is(IsoFlagType.climbSheetN) ||
                           this.current.Is(IsoFlagType.climbSheetS));
          this.current.RecalcProperties();
        }

        if (object.sheetRopeHealth <= 0.0F) {
          this.current.removeSheetRopeFromBottom(
              nullptr, this.current.Is(IsoFlagType.climbSheetN) ||
                           this.current.Is(IsoFlagType.climbSheetS));
        }
      }
    }
  }

  void getZombieWalkTowardSpeed(float speed, float dist, Vector2 temp) {
    float float0 = 1.0F;
    float0 = dist / 24.0F;
    if (float0 < 1.0F) {
      float0 = 1.0F;
    }

    if (float0 > 1.3F) {
      float0 = 1.3F;
    }

    temp.setLength((speed * this.getSpeedMod() + 0.006F) * float0);
    if (SandboxOptions.instance.Lore.Speed.getValue() == 1 && !this.inactive ||
        this.speedType == 1) {
      temp.setLength(0.08F);
      this.bRunning = true;
    }

    if (temp.getLength() > dist) {
      temp.setLength(dist);
    }
  }

  void getZombieLungeSpeed() {
    this.bRunning =
        SandboxOptions.instance.Lore.Speed.getValue() == 1 && !this.inactive ||
        this.speedType == 1;
  }

  bool tryThump(IsoGridSquare square) {
    if (this.Ghost) {
      return false;
    } else if (this.bCrawling) {
      return false;
    } else {
      boolean boolean0 = this.isCurrentState(PathFindState.instance()) ||
                         this.isCurrentState(LungeState.instance()) ||
                         this.isCurrentState(LungeNetworkState.instance()) ||
                         this.isCurrentState(WalkTowardState.instance()) ||
                         this.isCurrentState(WalkTowardNetworkState.instance());
      if (!boolean0) {
        return false;
      } else {
        IsoGridSquare _square;
        if (square != nullptr) {
          _square = square;
        } else {
          _square = this.getFeelerTile(this.getFeelersize());
        }

        if (_square != nullptr && this.current != nullptr) {
          IsoObject object = this.current.testCollideSpecialObjects(_square);
          IsoDoor door = Type.tryCastTo(object, IsoDoor.class);
          IsoThumpable thumpable = Type.tryCastTo(object, IsoThumpable.class);
          IsoWindow window = Type.tryCastTo(object, IsoWindow.class);
          if (window != nullptr && window.canClimbThrough(this)) {
            if (!this.isFacingObject(window, 0.8F)) {
              return false;
            } else {
              this.climbThroughWindow(window);
              return true;
            }
          } else if (thumpable != nullptr && thumpable.canClimbThrough(this)) {
            this.climbThroughWindow(thumpable);
            return true;
          } else if (thumpable != nullptr &&
                         thumpable.getThumpableFor(this) != nullptr ||
                     window != nullptr &&
                         window.getThumpableFor(this) != nullptr ||
                     door != nullptr && door.getThumpableFor(this) != nullptr) {
            int int0 = _square.getX() - this.current.getX();
            int int1 = _square.getY() - this.current.getY();
            IsoDirections directions = IsoDirections.N;
            if (int0 < 0 && Math.abs(int0) > Math.abs(int1)) {
              directions = IsoDirections.S;
            }

            if (int0 < 0 && Math.abs(int0) <= Math.abs(int1)) {
              directions = IsoDirections.SW;
            }

            if (int0 > 0 && Math.abs(int0) > Math.abs(int1)) {
              directions = IsoDirections.W;
            }

            if (int0 > 0 && Math.abs(int0) <= Math.abs(int1)) {
              directions = IsoDirections.SE;
            }

            if (int1 < 0 && Math.abs(int0) < Math.abs(int1)) {
              directions = IsoDirections.N;
            }

            if (int1 < 0 && Math.abs(int0) >= Math.abs(int1)) {
              directions = IsoDirections.NW;
            }

            if (int1 > 0 && Math.abs(int0) < Math.abs(int1)) {
              directions = IsoDirections.E;
            }

            if (int1 > 0 && Math.abs(int0) >= Math.abs(int1)) {
              directions = IsoDirections.NE;
            }

            if (this.getDir() == directions) {
              boolean boolean1 =
                  this.getPathFindBehavior2().isGoalSound() &&
                  (this.isCurrentState(PathFindState.instance()) ||
                   this.isCurrentState(WalkTowardState.instance()) ||
                   this.isCurrentState(WalkTowardNetworkState.instance()));
              if (SandboxOptions.instance.Lore.ThumpNoChasing.getValue() ||
                  this.target != nullptr || boolean1) {
                if (window != nullptr &&
                    window.getThumpableFor(this) != nullptr) {
                  object = (IsoObject)window.getThumpableFor(this);
                }

                this.setThumpTarget(object);
                this.setPath2(nullptr);
              }
            }

            return true;
          } else if (object != nullptr &&
                     IsoWindowFrame.isWindowFrame(object)) {
            this.climbThroughWindowFrame(object);
            return true;
          } else {
            return false;
          }
        } else {
          return false;
        }
      }
    }
  }

  void Wander() { this.changeState(ZombieIdleState.instance()); }

  void DoZombieInventory() { this.DoZombieInventory(false); }

  void DoCorpseInventory() { this.DoZombieInventory(true); }

  void DoZombieInventory(bool boolean0) {
    if (!this.isReanimatedPlayer() && !this.wasFakeDead()) {
      if (!GameServer.bServer || boolean0) {
        this.getInventory().removeAllItems();
        this.getInventory().setSourceGrid(this.getCurrentSquare());
        this.wornItems.setFromItemVisuals(this.itemVisuals);
        this.wornItems.addItemsToItemContainer(this.getInventory());

        for (int int0 = 0; int0 < this.attachedItems.size(); int0++) {
          AttachedItem attachedItem = this.attachedItems.get(int0);
          InventoryItem item0 = attachedItem.getItem();
          if (!this.getInventory().contains(item0)) {
            item0.setContainer(this.getInventory());
            this.getInventory().getItems().add(item0);
          }
        }

        IsoBuilding building = this.getCurrentBuilding();
        if (building != nullptr && building.getDef() != nullptr &&
            building.getDef().getKeyId() != -1 && Rand.Next(4) == 0) {
          if (Rand.Next(10) != 1) {
            std::string string0 = "Base.Key" + (Rand.Next(5) + 1);
            InventoryItem item1 = this.inventory.AddItem(string0);
            item1.setKeyId(building.getDef().getKeyId());
          } else if (this.inventory.AddItem("Base.KeyRing") instanceof
                     InventoryContainer inventoryContainer) {
            std::string string1 = "Base.Key" + (Rand.Next(5) + 1);
            InventoryItem item2 =
                inventoryContainer.getInventory().AddItem(string1);
            item2.setKeyId(building.getDef().getKeyId());
          }
        }

        if (this.itemsToSpawnAtDeath != nullptr &&
            !this.itemsToSpawnAtDeath.isEmpty()) {
          for (int int1 = 0; int1 < this.itemsToSpawnAtDeath.size(); int1++) {
            this.inventory.AddItem(this.itemsToSpawnAtDeath.get(int1));
          }

          this.itemsToSpawnAtDeath.clear();
        }

        DebugLog.Death.trace("id=%d, inventory=%d", this.getOnlineID(),
                             this.getInventory().getItems().size());
      }
    }
  }

  void DoZombieStats() {
    if (SandboxOptions.instance.Lore.Cognition.getValue() == 1) {
      this.cognition = 1;
    }

    if (SandboxOptions.instance.Lore.Cognition.getValue() == 4) {
      this.cognition = Rand.Next(0, 2);
    }

    if (this.strength == -1 &&
        SandboxOptions.instance.Lore.Strength.getValue() == 1) {
      this.strength = 5;
    }

    if (this.strength == -1 &&
        SandboxOptions.instance.Lore.Strength.getValue() == 2) {
      this.strength = 3;
    }

    if (this.strength == -1 &&
        SandboxOptions.instance.Lore.Strength.getValue() == 3) {
      this.strength = 1;
    }

    if (this.strength == -1 &&
        SandboxOptions.instance.Lore.Strength.getValue() == 4) {
      this.strength = Rand.Next(1, 5);
    }

    int int0 = SandboxOptions.instance.Lore.Memory.getValue();
    int int1 = -1;
    if (int0 == 5) {
      int1 = Rand.Next(4);
    }

    if (this.memory == -1 && int0 == 1 || int1 == 0) {
      this.memory = 1250;
    }

    if (this.memory == -1 && int0 == 2 || int1 == 1) {
      this.memory = 800;
    }

    if (this.memory == -1 && int0 == 3 || int1 == 2) {
      this.memory = 500;
    }

    if (this.memory == -1 && int0 == 4 || int1 == 3) {
      this.memory = 25;
    }

    if (SandboxOptions.instance.Lore.Sight.getValue() == 4) {
      this.sight = Rand.Next(1, 4);
    } else {
      this.sight = SandboxOptions.instance.Lore.Sight.getValue();
    }

    if (SandboxOptions.instance.Lore.Hearing.getValue() == 4) {
      this.hearing = Rand.Next(1, 4);
    } else {
      this.hearing = SandboxOptions.instance.Lore.Hearing.getValue();
    }

    if (this.speedType == -1) {
      this.speedType = SandboxOptions.instance.Lore.Speed.getValue();
      if (this.speedType == 4) {
        this.speedType = Rand.Next(2);
      }

      if (this.inactive) {
        this.speedType = 3;
      }
    }

    if (this.bCrawling) {
      this.speedMod = 0.3F;
      this.speedMod = this.speedMod + Rand.Next(1500) / 10000.0F;
      this.def.AnimFrameIncrease *= 0.8F;
    } else if (SandboxOptions.instance.Lore.Speed.getValue() != 3 &&
               this.speedType != 3 && Rand.Next(3) == 0) {
      if (SandboxOptions.instance.Lore.Speed.getValue() != 3 ||
          this.speedType != 3) {
        this.bLunger = true;
        this.speedMod = 0.85F;
        this.walkVariant = this.walkVariant + "2";
        this.speedMod = this.speedMod + Rand.Next(1500) / 10000.0F;
        this.def.setFrameSpeedPerFrame(0.24F);
        this.def.AnimFrameIncrease = this.def.AnimFrameIncrease * this.speedMod;
      }
    } else {
      this.speedMod = 0.55F;
      this.speedMod = this.speedMod + Rand.Next(1500) / 10000.0F;
      this.walkVariant = this.walkVariant + "1";
      this.def.setFrameSpeedPerFrame(0.24F);
      this.def.AnimFrameIncrease = this.def.AnimFrameIncrease * this.speedMod;
    }

    this.walkType = Integer.toString(Rand.Next(5) + 1);
    if (this.speedType == 1) {
      this.setTurnDelta(1.0F);
      this.walkType = "sprint" + this.walkType;
    }

    if (this.speedType == 3) {
      this.walkType = Integer.toString(Rand.Next(3) + 1);
      this.walkType = "slow" + this.walkType;
    }

    this.initCanCrawlUnderVehicle();
  }

  void setWalkType(const std::string &_walkType) { this.walkType = _walkType; }

  void DoZombieSpeeds(float spMod) {
    if (this.bCrawling) {
      this.speedMod = spMod;
      this.def.AnimFrameIncrease *= 0.8F;
    } else if (Rand.Next(3) != 0 ||
               SandboxOptions.instance.Lore.Speed.getValue() == 3) {
      this.speedMod = spMod;
      this.speedMod = this.speedMod + Rand.Next(1500) / 10000.0F;
      this.walkVariant = this.walkVariant + "1";
      this.def.setFrameSpeedPerFrame(0.24F);
      this.def.AnimFrameIncrease = this.def.AnimFrameIncrease * this.speedMod;
    } else if (SandboxOptions.instance.Lore.Speed.getValue() != 3) {
      this.bLunger = true;
      this.speedMod = spMod;
      this.walkVariant = this.walkVariant + "2";
      this.def.setFrameSpeedPerFrame(0.24F);
      this.def.AnimFrameIncrease = this.def.AnimFrameIncrease * this.speedMod;
    }
  }

  bool isFakeDead() { return this.bFakeDead; }

  void setFakeDead(bool _bFakeDead) {
    if (_bFakeDead && Rand.Next(2) == 0) {
      this.setCrawlerType(2);
    }

    this.bFakeDead = _bFakeDead;
  }

  bool isForceFakeDead() { return this.bForceFakeDead; }

  void setForceFakeDead(bool _bForceFakeDead) {
    this.bForceFakeDead = _bForceFakeDead;
  }

  float Hit(BaseVehicle vehicle, float speed, bool isHitFromBehind,
            Vector2 hitDir) {
    float float0 = 0.0F;
    this.AttackedBy = vehicle.getDriver();
    this.setHitDir(hitDir);
    this.setHitForce(speed * 0.15F);
    int int0 = (int)(speed * 6.0F);
    this.setTarget(vehicle.getCharacter(0));
    if (!this.bStaggerBack && !this.isOnFloor() &&
        this.getCurrentState() != ZombieGetUpState.instance() &&
        this.getCurrentState() != ZombieOnGroundState.instance()) {
      bool boolean0 = this.isStaggerBack();
      bool boolean1 = this.isKnockedDown();
      bool boolean2 = this.isBecomeCrawler();
      if (isHitFromBehind) {
        this.setHitFromBehind(true);
        if (Rand.Next(100) <= int0) {
          if (Rand.Next(5) == 0) {
            boolean2 = true;
          }

          boolean0 = true;
          boolean1 = true;
        } else {
          boolean0 = true;
        }
      } else if (speed < 3.0F) {
        if (Rand.Next(100) <= int0) {
          if (Rand.Next(8) == 0) {
            boolean2 = true;
          }

          boolean0 = true;
          boolean1 = true;
        } else {
          boolean0 = true;
        }
      } else if (speed < 10.0F) {
        if (Rand.Next(8) == 0) {
          boolean2 = true;
        }

        boolean0 = true;
        boolean1 = true;
      } else {
        float0 = this.getHealth();
        if (!GameServer.bServer && !GameClient.bClient) {
          this.Health -= float0;
          this.Kill(vehicle.getDriver());
        }
      }

      if (DebugOptions.instance.MultiplayerZombieCrawler.getValue()) {
        boolean2 = true;
      }

      if (!GameServer.bServer) {
        this.setStaggerBack(boolean0);
        this.setKnockedDown(boolean1);
        this.setBecomeCrawler(boolean2);
      }
    } else {
      if (this.isFakeDead()) {
        this.setFakeDead(false);
      }

      this.setHitReaction("Floor");
      float0 = speed / 5.0F;
      if (!GameServer.bServer && !GameClient.bClient) {
        this.Health -= float0;
        if (this.isDead()) {
          this.Kill(vehicle.getDriver());
        }
      }
    }

    if (!GameServer.bServer && !GameClient.bClient) {
      this.addBlood(speed);
    }

    return float0;
  }

  void addBlood(float speed) {
    if (!(Rand.Next(10) > speed)) {
      float float0 = 0.6F;
      if (SandboxOptions.instance.BloodLevel.getValue() > 1) {
        int int0 = Rand.Next(4, 10);
        if (int0 < 1) {
          int0 = 1;
        }

        if (Core.bLastStand) {
          int0 *= 3;
        }

        switch (SandboxOptions.instance.BloodLevel.getValue()) {
        case 2:
          int0 /= 2;
        case 3:
        default:
          break;
        case 4:
          int0 *= 2;
          break;
        case 5:
          int0 *= 5;
        }

        for (int int1 = 0; int1 < int0; int1++) {
          this.splatBlood(2, 0.3F);
        }
      }

      if (SandboxOptions.instance.BloodLevel.getValue() > 1) {
        this.splatBloodFloorBig();
      }

      if (SandboxOptions.instance.BloodLevel.getValue() > 1) {
        this.playBloodSplatterSound();
        new IsoZombieGiblets(IsoZombieGiblets.GibletType.A, this.getCell(),
                             this.getX(), this.getY(), this.getZ() + float0,
                             this.getHitDir().x * 1.5F,
                             this.getHitDir().y * 1.5F);
        tempo.x = this.getHitDir().x;
        tempo.y = this.getHitDir().y;
        uint8_t byte0 = 3;
        uint8_t byte1 = 0;
        uint8_t byte2 = 1;
        switch (SandboxOptions.instance.BloodLevel.getValue()) {
        case 1:
          byte2 = 0;
          break;
        case 2:
          byte2 = 1;
          byte0 = 5;
          byte1 = 2;
        case 3:
        default:
          break;
        case 4:
          byte2 = 3;
          byte0 = 2;
          break;
        case 5:
          byte2 = 10;
          byte0 = 0;
        }

        for (int int2 = 0; int2 < byte2; int2++) {
          if (Rand.Next(this.isCloseKilled() ? 8 : byte0) == 0) {
            new IsoZombieGiblets(IsoZombieGiblets.GibletType.A, this.getCell(),
                                 this.getX(), this.getY(), this.getZ() + float0,
                                 this.getHitDir().x * 1.5F,
                                 this.getHitDir().y * 1.5F);
          }

          if (Rand.Next(this.isCloseKilled() ? 8 : byte0) == 0) {
            new IsoZombieGiblets(IsoZombieGiblets.GibletType.A, this.getCell(),
                                 this.getX(), this.getY(), this.getZ() + float0,
                                 this.getHitDir().x * 1.8F,
                                 this.getHitDir().y * 1.8F);
          }

          if (Rand.Next(this.isCloseKilled() ? 8 : byte0) == 0) {
            new IsoZombieGiblets(IsoZombieGiblets.GibletType.A, this.getCell(),
                                 this.getX(), this.getY(), this.getZ() + float0,
                                 this.getHitDir().x * 1.9F,
                                 this.getHitDir().y * 1.9F);
          }

          if (Rand.Next(this.isCloseKilled() ? 4 : byte1) == 0) {
            new IsoZombieGiblets(IsoZombieGiblets.GibletType.A, this.getCell(),
                                 this.getX(), this.getY(), this.getZ() + float0,
                                 this.getHitDir().x * 3.9F,
                                 this.getHitDir().y * 3.9F);
          }

          if (Rand.Next(this.isCloseKilled() ? 4 : byte1) == 0) {
            new IsoZombieGiblets(IsoZombieGiblets.GibletType.A, this.getCell(),
                                 this.getX(), this.getY(), this.getZ() + float0,
                                 this.getHitDir().x * 3.8F,
                                 this.getHitDir().y * 3.8F);
          }

          if (Rand.Next(this.isCloseKilled() ? 9 : 6) == 0) {
            new IsoZombieGiblets(
                IsoZombieGiblets.GibletType.Eye, this.getCell(), this.getX(),
                this.getY(), this.getZ() + float0, this.getHitDir().x * 0.8F,
                this.getHitDir().y * 0.8F);
          }
        }
      }
    }
  }

  void processHitDirection(HandWeapon weapon, IsoGameCharacter character) {
    std::string string0 = character.getVariableString("ZombieHitReaction");
    if ("Shot" == string0)) {
        string0 = "ShotBelly";
        character.setCriticalHit(
            Rand.Next(100) < ((IsoPlayer)character).calculateCritChance(this));
        Vector2 vector0 = character.getForwardDirection();
        Vector2 vector1 = this.getHitAngle();
        double double0 = vector0.x * vector1.y - vector0.y * vector1.x;
        double double1 = double0 >= 0.0 ? 1.0 : -1.0;
        double double2 = vector0.x * vector1.x + vector0.y * vector1.y;
        double double3 = Math.acos(double2) * double1;
        if (double3 < 0.0) {
          double3 += Math.PI * 2;
        }

        std::string string1 = "";
        if (Math.toDegrees(double3) < 45.0) {
          this.setHitFromBehind(true);
          string1 = "S";
          int int0 = Rand.Next(9);
          if (int0 > 6) {
            string1 = "L";
          }

          if (int0 > 4) {
            string1 = "R";
          }
        }

        if (Math.toDegrees(double3) > 45.0 && Math.toDegrees(double3) < 90.0) {
          this.setHitFromBehind(true);
          if (Rand.Next(4) == 0) {
            string1 = "S";
          } else {
            string1 = "R";
          }
        }

        if (Math.toDegrees(double3) > 90.0 && Math.toDegrees(double3) < 135.0) {
          string1 = "R";
        }

        if (Math.toDegrees(double3) > 135.0 &&
            Math.toDegrees(double3) < 180.0) {
          if (Rand.Next(4) == 0) {
            string1 = "N";
          } else {
            string1 = "R";
          }
        }

        if (Math.toDegrees(double3) > 180.0 &&
            Math.toDegrees(double3) < 225.0) {
          string1 = "N";
          int int1 = Rand.Next(9);
          if (int1 > 6) {
            string1 = "L";
          }

          if (int1 > 4) {
            string1 = "R";
          }
        }

        if (Math.toDegrees(double3) > 225.0 &&
            Math.toDegrees(double3) < 270.0) {
          if (Rand.Next(4) == 0) {
            string1 = "N";
          } else {
            string1 = "L";
          }
        }

        if (Math.toDegrees(double3) > 270.0 &&
            Math.toDegrees(double3) < 315.0) {
          this.setHitFromBehind(true);
          string1 = "L";
        }

        if (Math.toDegrees(double3) > 315.0) {
          if (Rand.Next(4) == 0) {
            string1 = "S";
          } else {
            string1 = "L";
          }
        }

        if ("N" == string1)) {
            if (this.isHitFromBehind()) {
              string0 = "ShotBellyStep";
            } else {
              int int2 = Rand.Next(2);
              switch (int2) {
              case 0:
                string0 = "ShotBelly";
                break;
              case 1:
                string0 = "ShotBellyStep";
              }
            }
          }

        if ("S" == string1)) {
                string0 = "ShotBellyStep";
            }

        if ("L" == string1) || "R" == string1)) {
            if (this.isHitFromBehind()) {
              int int3 = Rand.Next(3);
              switch (int3) {
              case 0:
                string0 = "ShotChest";
                break;
              case 1:
                string0 = "ShotLeg";
                break;
              case 2:
                string0 = "ShotShoulderStep";
              }
            } else {
              int int4 = Rand.Next(5);
              switch (int4) {
              case 0:
                string0 = "ShotChest";
                break;
              case 1:
                string0 = "ShotChestStep";
                break;
              case 2:
                string0 = "ShotLeg";
                break;
              case 3:
                string0 = "ShotShoulder";
                break;
              case 4:
                string0 = "ShotShoulderStep";
              }
            }

            string0 = string0 + string1;
          }

        if (character.isCriticalHit()) {
          if ("S" == string1)) {
                    string0 = "ShotHeadFwd";
                }

          if ("N" == string1)) {
                    string0 = "ShotHeadBwd";
                }

          if (("L" == string1) || "R" == string1)) && Rand.Next(4) == 0) {
                    string0 = "ShotHeadBwd";
                }
        }

        if (string0.contains("Head")) {
          this.addBlood(BloodBodyPartType.Head, false, true, true);
        } else if (string0.contains("Chest")) {
          this.addBlood(BloodBodyPartType.Torso_Upper, !this.isCriticalHit(),
                        this.isCriticalHit(), true);
        } else if (string0.contains("Belly")) {
          this.addBlood(BloodBodyPartType.Torso_Lower, !this.isCriticalHit(),
                        this.isCriticalHit(), true);
        } else if (string0.contains("Leg")) {
          bool boolean0 = Rand.Next(2) == 0;
          if ("L" == string1)) {
              this.addBlood(boolean0 ? BloodBodyPartType.LowerLeg_L
                                     : BloodBodyPartType.UpperLeg_L,
                            !this.isCriticalHit(), this.isCriticalHit(), true);
            }
          else {
            this.addBlood(boolean0 ? BloodBodyPartType.LowerLeg_R
                                   : BloodBodyPartType.UpperLeg_R,
                          !this.isCriticalHit(), this.isCriticalHit(), true);
          }
        } else if (string0.contains("Shoulder")) {
          bool boolean1 = Rand.Next(2) == 0;
          if ("L" == string1)) {
              this.addBlood(boolean1 ? BloodBodyPartType.ForeArm_L
                                     : BloodBodyPartType.UpperArm_L,
                            !this.isCriticalHit(), this.isCriticalHit(), true);
            }
          else {
            this.addBlood(boolean1 ? BloodBodyPartType.ForeArm_R
                                   : BloodBodyPartType.UpperArm_R,
                          !this.isCriticalHit(), this.isCriticalHit(), true);
          }
        }
      }
    else if (weapon.getCategories().contains("Blunt")) {
      this.addBlood(BloodBodyPartType.FromIndex(
                        Rand.Next(BloodBodyPartType.UpperArm_L.index(),
                                  BloodBodyPartType.Groin.index())),
                    false, false, true);
    } else if (!weapon.getCategories().contains("Unarmed")) {
      this.addBlood(BloodBodyPartType.FromIndex(
                        Rand.Next(BloodBodyPartType.UpperArm_L.index(),
                                  BloodBodyPartType.Groin.index())),
                    false, true, true);
    }

    if ("ShotHeadFwd" == string0) && Rand.Next(2) == 0) {
            string0 = "ShotHeadFwd02";
        }

    if (this.getEatBodyTarget() != nullptr) {
      if (this.getVariableBoolean("onknees")) {
        string0 = "OnKnees";
      } else {
        string0 = "Eating";
      }
    }

    if ("Floor".equalsIgnoreCase(string0) &&
        this.isCurrentState(ZombieGetUpState.instance()) &&
        this.isFallOnFront()) {
      string0 = "GettingUpFront";
    }

    if (string0 != nullptr && !"" == string0)) {
            this.setHitReaction(string0);
        }
    else {
      this.setStaggerBack(true);
      this.setHitReaction("");
      if ("LEFT" == this.getPlayerAttackPosition()) || "RIGHT" == this.getPlayerAttackPosition())) {
          character.setCriticalHit(false);
        }
    }
  }

  void hitConsequences(HandWeapon weapon, IsoGameCharacter wielder,
                       bool bIgnoreDamage, float damage, bool _bRemote) {
    if (!this.isOnlyJawStab() || this.isCloseKilled()) {
      super.hitConsequences(weapon, wielder, bIgnoreDamage, damage, _bRemote);
      if (Core.bDebug) {
        DebugLog.Combat.debugln("Zombie #" + this.OnlineID + " got hit for " +
                                damage);
      }

      this.actionContext.reportEvent("wasHit");
      if (!_bRemote) {
        this.processHitDirection(weapon, wielder);
      }

      if (!GameClient.bClient || this.target == nullptr ||
          wielder == this.target ||
          !(IsoUtils.DistanceToSquared(this.x, this.y, this.target.x,
                                       this.target.y) < 10.0F)) {
        this.setTarget(wielder);
      }

      if (!GameServer.bServer && !GameClient.bClient ||
              GameClient.bClient && wielder instanceof
          IsoPlayer && ((IsoPlayer)wielder).isLocalPlayer() &&
              !this.isRemoteZombie()) {
        this.setKnockedDown(wielder.isCriticalHit() || this.isOnFloor() ||
                            this.isAlwaysKnockedDown());
      }

      this.checkClimbOverFenceHit();
      this.checkClimbThroughWindowHit();
      if (this.shouldBecomeCrawler(wielder)) {
        this.setBecomeCrawler(true);
      }
    }
  }

  void playHurtSound() {}

  void checkClimbOverFenceHit() {
    if (!this.isOnFloor()) {
      if (this.isCurrentState(ClimbOverFenceState.instance()) &&
          this.getVariableBoolean("ClimbFenceStarted") &&
          !this.isVariable("ClimbFenceOutcome", "fall") &&
          !this.getVariableBoolean("ClimbFenceFlopped")) {
        std::unordered_map hashMap =
            this.StateMachineParams.get(ClimbOverFenceState.instance());
        uint8_t byte0 = 3;
        uint8_t byte1 = 4;
        int int0 = (Integer)hashMap.get(Integer.valueOf(byte0));
        int int1 = (Integer)hashMap.get(Integer.valueOf(byte1));
        this.climbFenceWindowHit(int0, int1);
      }
    }
  }

  void checkClimbThroughWindowHit() {
    if (!this.isOnFloor()) {
      if (this.isCurrentState(ClimbThroughWindowState.instance()) &&
          this.getVariableBoolean("ClimbWindowStarted") &&
          !this.isVariable("ClimbWindowOutcome", "fall") &&
          !this.getVariableBoolean("ClimbWindowFlopped")) {
        std::unordered_map hashMap =
            this.StateMachineParams.get(ClimbThroughWindowState.instance());
        uint8_t byte0 = 12;
        uint8_t byte1 = 13;
        int int0 = (Integer)hashMap.get(Integer.valueOf(byte0));
        int int1 = (Integer)hashMap.get(Integer.valueOf(byte1));
        this.climbFenceWindowHit(int0, int1);
      }
    }
  }

  void climbFenceWindowHit(int int0, int int1) {
    if (this.getDir() == IsoDirections.W) {
      this.setX(int0 + 0.9F);
      this.setLx(this.getX());
    } else if (this.getDir() == IsoDirections.E) {
      this.setX(int0 + 0.1F);
      this.setLx(this.getX());
    } else if (this.getDir() == IsoDirections.N) {
      this.setY(int1 + 0.9F);
      this.setLy(this.getY());
    } else if (this.getDir() == IsoDirections.S) {
      this.setY(int1 + 0.1F);
      this.setLy(this.getY());
    }

    this.setStaggerBack(false);
    this.setKnockedDown(true);
    this.setOnFloor(true);
    this.setFallOnFront(true);
    this.setHitReaction("FenceWindow");
  }

  bool shouldBecomeCrawler(IsoGameCharacter character) {
    if (DebugOptions.instance.MultiplayerZombieCrawler.getValue()) {
      return true;
    } else if (this.isBecomeCrawler()) {
      return true;
    } else if (this.isCrawling()) {
      return false;
    } else if (Core.bLastStand) {
      return false;
    } else if (this.isDead()) {
      return false;
    } else if (this.isCloseKilled()) {
      return false;
    } else {
      IsoPlayer player = Type.tryCastTo(character, IsoPlayer.class);
      if (player != nullptr && !player.isAimAtFloor() && player.bDoShove) {
        return false;
      } else {
        uint8_t byte0 = 30;
        if (player != nullptr && player.isAimAtFloor() && player.bDoShove) {
          if (this.isHitLegsWhileOnFloor()) {
            byte0 = 7;
          } else {
            byte0 = 15;
          }
        }

        return Rand.NextBool(byte0);
      }
    }
  }

  void removeFromWorld() {
    this.getEmitter().stopOrTriggerSoundByName("BurningFlesh");
    this.clearAggroList();
    VirtualZombieManager.instance.RemoveZombie(this);
    this.setPath2(nullptr);
    PolygonalMap2.instance.cancelRequest(this);
    if (this.getFinder().progress !=
            AStarPathFinder.PathFindProgress.notrunning &&
        this.getFinder().progress != AStarPathFinder.PathFindProgress.found) {
      this.getFinder().progress = AStarPathFinder.PathFindProgress.notrunning;
    }

    if (this.group != nullptr) {
      this.group.remove(this);
      this.group = nullptr;
    }

    if (GameServer.bServer && this.OnlineID != -1) {
      ServerMap.instance.ZombieMap.remove(this.OnlineID);
      this.OnlineID = -1;
    }

    if (GameClient.bClient) {
      GameClient.instance.removeZombieFromCache(this);
    }

    this.getCell().getZombieList().remove(this);
    if (GameServer.bServer) {
      if (this.authOwner != nullptr || this.authOwnerPlayer != nullptr) {
        NetworkZombieManager.getInstance().moveZombie(this, nullptr, nullptr);
      }

      this.zombiePacketUpdated = false;
    }

    super.removeFromWorld();
  }

  void resetForReuse() {
    this.setCrawler(false);
    this.initializeStates();
    this.actionContext.setGroup(ActionGroup.getActionGroup("zombie"));
    this.advancedAnimator.OnAnimDataChanged(false);
    this.setStateMachineLocked(false);
    this.setDefaultState();
    if (this.vocalEvent != 0L) {
      this.getEmitter().stopSoundLocal(this.vocalEvent);
      this.vocalEvent = 0L;
    }

    this.parameterZombieState.setState(ParameterZombieState.State.Idle);
    this.setSceneCulled(true);
    this.releaseAnimationPlayer();
    Arrays.fill(this.IsVisibleToPlayer, false);
    this.setCurrent(nullptr);
    this.setLast(nullptr);
    this.setOnFloor(false);
    this.setCanWalk(true);
    this.setFallOnFront(false);
    this.setHitTime(0);
    this.strength = -1;
    this.setImmortalTutorialZombie(false);
    this.setOnlyJawStab(false);
    this.setAlwaysKnockedDown(false);
    this.setForceEatingAnimation(false);
    this.setNoTeeth(false);
    this.cognition = -1;
    this.speedType = -1;
    this.bodyToEat = nullptr;
    this.checkForCorpseTimer = 10000.0F;
    this.clearAttachedItems();
    this.target = nullptr;
    this.setEatBodyTarget(nullptr, false);
    this.setSkeleton(false);
    this.setReanimatedPlayer(false);
    this.setBecomeCrawler(false);
    this.setWasFakeDead(false);
    this.setKnifeDeath(false);
    this.setJawStabAttach(false);
    this.setReanimate(false);
    this.DoZombieStats();
    this.alerted = false;
    this.BonusSpotTime = 0.0F;
    this.TimeSinceSeenFlesh = 100000.0F;
    this.soundReactDelay = 0.0F;
    this.delayedSound.x = this.delayedSound.y = this.delayedSound.z = -1;
    this.bSoundSourceRepeating = false;
    this.soundSourceTarget = nullptr;
    this.soundAttract = 0.0F;
    this.soundAttractTimeout = 0.0F;
    if (SandboxOptions.instance.Lore.Toughness.getValue() == 1) {
      this.setHealth(3.5F + Rand.Next(0.0F, 0.3F));
    }

    if (SandboxOptions.instance.Lore.Toughness.getValue() == 2) {
      this.setHealth(1.8F + Rand.Next(0.0F, 0.3F));
    }

    if (SandboxOptions.instance.Lore.Toughness.getValue() == 3) {
      this.setHealth(0.5F + Rand.Next(0.0F, 0.3F));
    }

    if (SandboxOptions.instance.Lore.Toughness.getValue() == 4) {
      this.setHealth(Rand.Next(0.5F, 3.5F) + Rand.Next(0.0F, 0.3F));
    }

    this.setCollidable(true);
    this.setShootable(true);
    if (this.isOnFire()) {
      IsoFireManager.RemoveBurningCharacter(this);
      this.setOnFire(false);
    }

    if (this.AttachedAnimSprite != nullptr) {
      this.AttachedAnimSprite.clear();
    }

    this.OnlineID = -1;
    this.bIndoorZombie = false;
    this.setVehicle4TestCollision(nullptr);
    this.clearItemsToSpawnAtDeath();
    this.m_persistentOutfitId = 0;
    this.m_bPersistentOutfitInit = false;
    this.sharedDesc = nullptr;
  }

  bool wasFakeDead() { return this.bWasFakeDead; }

  void setWasFakeDead(bool wasFakeDead) { this.bWasFakeDead = wasFakeDead; }

  void setCrawler(bool crawling) { this.bCrawling = crawling; }

  bool isBecomeCrawler() { return this.bBecomeCrawler; }

  void setBecomeCrawler(bool crawler) { this.bBecomeCrawler = crawler; }

  bool isReanimate() { return this.bReanimate; }

  void setReanimate(bool reanimate) { this.bReanimate = reanimate; }

  bool isReanimatedPlayer() { return this.bReanimatedPlayer; }

  void setReanimatedPlayer(bool reanimated) {
    this.bReanimatedPlayer = reanimated;
  }

  IsoPlayer getReanimatedPlayer() {
    for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
      IsoPlayer player = IsoPlayer.players[int0];
      if (player != nullptr && player.ReanimatedCorpse == this) {
        return player;
      }
    }

    return null;
  }

  void setFemaleEtc(bool female) {
    this.setFemale(female);
    if (this.getDescriptor() != nullptr) {
      this.getDescriptor().setFemale(female);
    }

    this.SpriteName = female ? "KateZ" : "BobZ";
    this.hurtSound = female ? "FemaleZombieHurt" : "MaleZombieHurt";
    if (this.vocalEvent != 0L) {
      std::string string =
          female ? "FemaleZombieCombined" : "MaleZombieCombined";
      if (this.getEmitter() != nullptr &&
          !this.getEmitter().isPlaying(string)) {
        this.getEmitter().stopSoundLocal(this.vocalEvent);
        this.vocalEvent = 0L;
      }
    }
  }

  void addRandomBloodDirtHolesEtc() {
    this.addBlood(nullptr, false, true, false);
    this.addDirt(nullptr, OutfitRNG.Next(5, 10), false);
    this.addRandomVisualDamages();
    this.addRandomVisualBandages();
    int int0 = Math.max(8 - (int)IsoWorld.instance.getWorldAgeDays() / 30, 0);

    for (int int1 = 0; int1 < 5; int1++) {
      if (OutfitRNG.NextBool(int0)) {
        this.addBlood(nullptr, false, true, false);
        this.addDirt(nullptr, nullptr, false);
      }
    }

    for (int int2 = 0; int2 < 8; int2++) {
      if (OutfitRNG.NextBool(int0)) {
        BloodBodyPartType bloodBodyPartType = BloodBodyPartType.FromIndex(
            OutfitRNG.Next(0, BloodBodyPartType.MAX.index()));
        this.addHole(bloodBodyPartType);
        this.addBlood(bloodBodyPartType, true, false, false);
      }
    }
  }

  void useDescriptor(SharedDescriptors.Descriptor _sharedDesc) {
    this.getHumanVisual().clear();
    this.itemVisuals.clear();
    this.m_persistentOutfitId =
        _sharedDesc == nullptr ? 0 : _sharedDesc.getPersistentOutfitID();
    this.m_bPersistentOutfitInit = true;
    this.sharedDesc = _sharedDesc;
    if (_sharedDesc != nullptr) {
      this.setFemaleEtc(_sharedDesc.isFemale());
      this.getHumanVisual().copyFrom(_sharedDesc.getHumanVisual());
      this.getWornItems().setFromItemVisuals(_sharedDesc.itemVisuals);
      this.onWornItemsChanged();
    }
  }

public
  SharedDescriptors.Descriptor getSharedDescriptor() { return this.sharedDesc; }

  int getSharedDescriptorID() { return this.getPersistentOutfitID(); }

  int getScreenProperX(int playerIndex) {
    return (int)(IsoUtils.XToScreen(this.x, this.y, this.z, 0) -
                 IsoCamera.cameras[playerIndex].getOffX());
  }

  int getScreenProperY(int playerIndex) {
    return (int)(IsoUtils.YToScreen(this.x, this.y, this.z, 0) -
                 IsoCamera.cameras[playerIndex].getOffY());
  }

  BaseVisual getVisual() { return this.humanVisual; }

  HumanVisual getHumanVisual() { return this.humanVisual; }

  ItemVisuals getItemVisuals() {
    this.getItemVisuals(this.itemVisuals);
    return this.itemVisuals;
  }

  void getItemVisuals(ItemVisuals _itemVisuals) {
    if (this.isUsingWornItems()) {
      this.getWornItems().getItemVisuals(_itemVisuals);
    } else if (_itemVisuals != this.itemVisuals) {
      _itemVisuals.clear();
      _itemVisuals.addAll(this.itemVisuals);
    }
  }

  bool isUsingWornItems() {
    return this.isOnKillDone() || this.isOnDeathDone() ||
           this.isReanimatedPlayer() || this.wasFakeDead();
  }

  void setAsSurvivor() {
    std::string string = "Survivalist";
    switch (Rand.Next(3)) {
    case 1:
      string = "Survivalist02";
      break;
    case 2:
      string = "Survivalist03";
    }

    this.dressInPersistentOutfit(string);
  }

  /**
   * Description copied from class: IsoGameCharacter
   */
  void dressInRandomOutfit() {
    ZombiesZoneDefinition.dressInRandomOutfit(this);
  }

  void dressInNamedOutfit(const std::string &outfitName) {
    this.wornItems.clear();
    this.getHumanVisual().clear();
    this.itemVisuals.clear();
    Outfit outfit = this.isFemale()
                        ? OutfitManager.instance.FindFemaleOutfit(outfitName)
                        : OutfitManager.instance.FindMaleOutfit(outfitName);
    if (outfit != nullptr) {
      if (outfit.isEmpty()) {
        outfit.loadItems();
        this.pendingOutfitName = outfitName;
      } else {
        this.getHumanVisual().dressInNamedOutfit(outfitName, this.itemVisuals);
        this.getHumanVisual().synchWithOutfit(
            this.getHumanVisual().getOutfit());
        UnderwearDefinition.addRandomUnderwear(this);
        this.onWornItemsChanged();
      }
    }
  }

  void dressInPersistentOutfitID(int outfitID) {
    this.getHumanVisual().clear();
    this.itemVisuals.clear();
    this.m_persistentOutfitId = outfitID;
    this.m_bPersistentOutfitInit = true;
    if (outfitID != 0) {
      this.bDressInRandomOutfit = false;
      PersistentOutfits.instance.dressInOutfit(this, outfitID);
      this.onWornItemsChanged();
    }
  }

  void dressInClothingItem(const std::string &itemGUID) {
    this.wornItems.clear();
    this.getHumanVisual().dressInClothingItem(itemGUID, this.itemVisuals);
    this.onWornItemsChanged();
  }

  void onWornItemsChanged() { this.parameterShoeType.setShoeType(nullptr); }

  /**
   * Description copied from class: IsoGameCharacter
   *
   * @param itemGuid The item's Globally Unique Identifier (GUID).
   */
  void clothingItemChanged(const std::string &itemGuid) {
    super.clothingItemChanged(itemGuid);
    if (!StringUtils.isNullOrWhitespace(this.pendingOutfitName)) {
      Outfit outfit =
          this.isFemale()
              ? OutfitManager.instance.FindFemaleOutfit(this.pendingOutfitName)
              : OutfitManager.instance.FindMaleOutfit(this.pendingOutfitName);
      if (outfit != nullptr && !outfit.isEmpty()) {
        this.dressInNamedOutfit(this.pendingOutfitName);
        this.pendingOutfitName = nullptr;
        this.resetModelNextFrame();
      }
    }
  }

  bool WanderFromWindow() {
    if (this.getCurrentSquare() == nullptr) {
      return false;
    } else {
      IsoZombie.FloodFill floodFillx = floodFill;
      floodFillx.calculate(this, this.getCurrentSquare());
      IsoGridSquare square = floodFillx.choose();
      floodFillx.reset();
      if (square != nullptr) {
        this.pathToLocation(square.getX(), square.getY(), square.getZ());
        return true;
      } else {
        return false;
      }
    }
  }

  bool isUseless() { return this.useless; }

  void setUseless(bool _useless) { this.useless = _useless; }

  void setImmortalTutorialZombie(bool immortal) {
    this.ImmortalTutorialZombie = immortal;
  }

  bool isTargetInCone(float dist, float dot) {
    if (this.target == nullptr) {
      return false;
    } else {
      tempo.set(this.target.getX() - this.getX(),
                this.target.getY() - this.getY());
      float float0 = tempo.getLength();
      if (float0 == 0.0F) {
        return true;
      } else if (float0 > dist) {
        return false;
      } else {
        tempo.normalize();
        this.getVectorFromDirection(tempo2);
        float float1 = tempo.dot(tempo2);
        return float1 >= dot;
      }
    }
  }

  bool testCollideWithVehicles(BaseVehicle vehicle) {
    if (this.Health <= 0.0F) {
      return false;
    } else if (this.isProne()) {
      if (vehicle.getDriver() == nullptr) {
        return false;
      } else {
        int int0 = vehicle.isEngineRunning()
                       ? vehicle.testCollisionWithProneCharacter(this, true)
                       : 0;
        if (int0 > 0) {
          if (!this.emitter.isPlaying(this.getHurtSound())) {
            this.playHurtSound();
          }

          this.AttackedBy = vehicle.getDriver();
          vehicle.hitCharacter(this);
          if (!GameServer.bServer && !GameClient.bClient && this.isDead()) {
            this.Kill(vehicle.getDriver());
          }

          super.update();
          return true;
        } else {
          return false;
        }
      }
    } else {
      if (vehicle.shouldCollideWithCharacters()) {
        Vector2 vector = BaseVehicle.TL_vector2_pool.get().alloc();
        if (vehicle.testCollisionWithCharacter(this, 0.3F, vector) != nullptr) {
          BaseVehicle.TL_vector2_pool.get().release(vector);
          vehicle.hitCharacter(this);
          super.update();
          return true;
        }

        BaseVehicle.TL_vector2_pool.get().release(vector);
      }

      return false;
    }
  }

  bool isCrawling() { return this.bCrawling; }

  bool isCanCrawlUnderVehicle() { return this.bCanCrawlUnderVehicle; }

  void setCanCrawlUnderVehicle(bool b) { this.bCanCrawlUnderVehicle = b; }

  bool isCanWalk() { return this.bCanWalk; }

  void setCanWalk(bool bCanStand) { this.bCanWalk = bCanStand; }

  void initCanCrawlUnderVehicle() {
    uint8_t byte0 = 100;
    switch (SandboxOptions.instance.Lore.CrawlUnderVehicle.getValue()) {
    case 1:
      byte0 = 0;
      break;
    case 2:
      byte0 = 5;
      break;
    case 3:
      byte0 = 10;
      break;
    case 4:
      byte0 = 25;
      break;
    case 5:
      byte0 = 50;
      break;
    case 6:
      byte0 = 75;
      break;
    case 7:
      byte0 = 100;
    }

    this.setCanCrawlUnderVehicle(Rand.Next(100) < byte0);
  }

  bool shouldGetUpFromCrawl() {
    if (this.isCurrentState(ZombieGetUpFromCrawlState.instance())) {
      return true;
    } else if (this.isCurrentState(ZombieGetUpState.instance())) {
      return this.stateMachine.getPrevious() ==
             ZombieGetUpFromCrawlState.instance();
    } else if (!this.isCrawling()) {
      return false;
    } else if (!this.isCanWalk()) {
      return false;
    } else if (this.isCurrentState(PathFindState.instance())) {
      return this.stateMachine.getPrevious() == ZombieGetDownState.instance() &&
                     ZombieGetDownState.instance().isNearStartXY(this)
                 ? false
                 : this.getPathFindBehavior2().shouldGetUpFromCrawl();
    } else {
      if (this.isCurrentState(WalkTowardState.instance())) {
        float float0 = this.getPathFindBehavior2().getTargetX();
        float float1 = this.getPathFindBehavior2().getTargetY();
        if (this.DistToSquared(float0, float1) > 0.010000001F &&
            PolygonalMap2.instance.lineClearCollide(
                this.x, this.y, float0, float1, (int)this.z, nullptr)) {
          return false;
        }
      }

      return this.isCurrentState(ZombieGetDownState.instance())
                 ? false
                 : PolygonalMap2.instance.canStandAt(
                       this.x, this.y, (int)this.z, nullptr, false, true);
    }
  }

  void toggleCrawling() {
    bool boolean0 = this.bCanCrawlUnderVehicle;
    if (this.bCrawling) {
      this.setCrawler(false);
      this.setKnockedDown(false);
      this.setStaggerBack(false);
      this.setFallOnFront(false);
      this.setOnFloor(false);
      this.DoZombieStats();
    } else {
      this.setCrawler(true);
      this.setOnFloor(true);
      this.DoZombieStats();
      this.walkVariant = "ZombieWalk";
    }

    this.bCanCrawlUnderVehicle = boolean0;
  }

  void knockDown(bool hitFromBehind) {
    this.setKnockedDown(true);
    this.setStaggerBack(true);
    this.setHitReaction("");
    this.setPlayerAttackPosition(hitFromBehind ? "BEHIND" : nullptr);
    this.setHitForce(1.0F);
    this.reportEvent("wasHit");
  }

  void addItemToSpawnAtDeath(InventoryItem item) {
    if (this.itemsToSpawnAtDeath == nullptr) {
      this.itemsToSpawnAtDeath = std::make_unique<ArrayList<>>();
    }

    this.itemsToSpawnAtDeath.add(item);
  }

  void clearItemsToSpawnAtDeath() {
    if (this.itemsToSpawnAtDeath != nullptr) {
      this.itemsToSpawnAtDeath.clear();
    }
  }

  IsoMovingObject getEatBodyTarget() { return this.eatBodyTarget; }

  float getEatSpeed() { return this.eatSpeed; }

  void setEatBodyTarget(IsoMovingObject _target, bool force) {
    this.setEatBodyTarget(_target, force,
                          Rand.Next(0.8F, 1.2F) * GameTime.getAnimSpeedFix());
  }

  void setEatBodyTarget(IsoMovingObject _target, bool force, float _eatSpeed) {
    if (_target != this.eatBodyTarget) {
      if (force || _target == nullptr ||
          _target.getEatingZombies().size() < 3) {
        if (this.eatBodyTarget != nullptr) {
          this.eatBodyTarget.getEatingZombies().remove(this);
        }

        this.eatBodyTarget = _target;
        if (_target != nullptr) {
          this.eatBodyTarget.getEatingZombies().add(this);
          this.eatSpeed = _eatSpeed;
        }
      }
    }
  }

  void updateEatBodyTarget() {
    if (this.bodyToEat != nullptr &&
        this.isCurrentState(ZombieIdleState.instance()) &&
        this.DistToSquared(this.bodyToEat) <= 1.0F &&
        (int)this.getZ() == (int)this.bodyToEat.getZ()) {
      this.setEatBodyTarget(this.bodyToEat, false);
      this.bodyToEat = nullptr;
    }

    if (this.eatBodyTarget != nullptr) {
      if (this.eatBodyTarget instanceof
          IsoDeadBody &&
              this.eatBodyTarget.getStaticMovingObjectIndex() == -1) {
        this.setEatBodyTarget(nullptr, false);
      }

      if (this.target != nullptr && !this.target.isOnFloor() &&
          this.target != this.eatBodyTarget) {
        this.setEatBodyTarget(nullptr, false);
      }

      IsoPlayer player = Type.tryCastTo(this.eatBodyTarget, IsoPlayer.class);
      if (player != nullptr && player.ReanimatedCorpse != nullptr) {
        this.setEatBodyTarget(nullptr, false);
      }

      if (player != nullptr && player.isAlive() && !player.isOnFloor() &&
          !player.isCurrentState(PlayerHitReactionState.instance())) {
        this.setEatBodyTarget(nullptr, false);
      }

      if (!this.isCurrentState(ZombieEatBodyState.instance()) &&
          this.eatBodyTarget != nullptr &&
          this.DistToSquared(this.eatBodyTarget) > 1.0F) {
        this.setEatBodyTarget(nullptr, false);
      }

      if (this.eatBodyTarget != nullptr &&
          this.eatBodyTarget.getSquare() != nullptr &&
          this.current != nullptr &&
          this.current.isSomethingTo(this.eatBodyTarget.getSquare())) {
        this.setEatBodyTarget(nullptr, false);
      }
    }
  }

  void updateCharacterTextureAnimTime() {
    bool boolean0 = this.isCurrentState(WalkTowardState.instance()) ||
                    this.isCurrentState(PathFindState.instance());
    this.m_characterTextureAnimDuration = boolean0 ? 0.67F : 2.0F;
    this.m_characterTextureAnimTime =
        this.m_characterTextureAnimTime + GameTime.getInstance().getTimeDelta();
    if (this.m_characterTextureAnimTime > this.m_characterTextureAnimDuration) {
      this.m_characterTextureAnimTime =
          this.m_characterTextureAnimTime % this.m_characterTextureAnimDuration;
    }
  }

  Vector2 getHitAngle() { return this.hitAngle; }

  void setHitAngle(Vector2 _hitAngle) {
    if (_hitAngle != nullptr) {
      this.hitAngle.set(_hitAngle);
    }
  }

  int getCrawlerType() { return this.crawlerType; }

  void setCrawlerType(int _crawlerType) { this.crawlerType = _crawlerType; }

  /**
   * Possibly add visual bandages (bloody) on the zombie  TODO: Make
   * InventoryItem linked to it in DeadBodyAtlas to being able to remove them
   * (like primary/secondary weapons)
   */
  void addRandomVisualBandages() {
    if (!"Tutorial" == Core.getInstance().getGameMode())) {
        for (int int0 = 0; int0 < 5; int0++) {
          if (OutfitRNG.Next(10) == 0) {
            BodyPartType bodyPartType = BodyPartType.getRandom();
            std::string string = bodyPartType.getBandageModel() + "_Blood";
            this.addBodyVisualFromItemType(string);
          }
        }
      }
  }

  void addVisualBandage(BodyPartType bodyPart, bool bloody) {
    std::string string = bodyPart.getBandageModel() + (bloody ? "_Blood" : "");
    this.addBodyVisualFromItemType(string);
  }

  /**
   * Add some random visual damage (clothing actually) to the zombies.  Those
   * items won't appear in inventory.
   */
  void addRandomVisualDamages() {
    for (int int0 = 0; int0 < 5; int0++) {
      if (OutfitRNG.Next(5) == 0) {
        std::string string =
            OutfitRNG.pickRandom(ScriptManager.instance.getZedDmgMap());
        this.addBodyVisualFromItemType("Base." + string);
      }
    }
  }

  std::string getPlayerAttackPosition() { return this.playerAttackPosition; }

  void setPlayerAttackPosition(const std::string &_playerAttackPosition) {
    this.playerAttackPosition = _playerAttackPosition;
  }

  bool isSitAgainstWall() { return this.sitAgainstWall; }

  void setSitAgainstWall(bool _sitAgainstWall) {
    this.sitAgainstWall = _sitAgainstWall;
    this.networkAI.extraUpdate();
  }

  bool isSkeleton() {
    if (Core.bDebug && DebugOptions.instance.ModelSkeleton.getValue()) {
      this.getHumanVisual().setSkinTextureIndex(2);
      return true;
    } else {
      return this.isSkeleton;
    }
  }

  bool isZombie() { return true; }

  void setSkeleton(bool _isSkeleton) {
    this.isSkeleton = _isSkeleton;
    if (_isSkeleton) {
      this.getHumanVisual().setHairModel("");
      this.getHumanVisual().setBeardModel("");
      ModelManager.instance.Reset(this);
    }
  }

  int getHitTime() { return this.hitTime; }

  void setHitTime(int _hitTime) { this.hitTime = _hitTime; }

  int getThumpTimer() { return this.thumpTimer; }

  void setThumpTimer(int _thumpTimer) { this.thumpTimer = _thumpTimer; }

  IsoMovingObject getTarget() { return this.target; }

  void setTargetSeenTime(float seconds) { this.targetSeenTime = seconds; }

  float getTargetSeenTime() { return this.targetSeenTime; }

  bool isTargetVisible() {
    IsoPlayer player = Type.tryCastTo(this.target, IsoPlayer.class);
    if (player != nullptr && this.getCurrentSquare() != nullptr) {
      return GameServer.bServer
                 ? ServerLOS.instance.isCouldSee(player,
                                                 this.getCurrentSquare())
                 : this.getCurrentSquare().isCouldSee(player.getPlayerNum());
    } else {
      return false;
    }
  }

  float getTurnDelta() { return this.m_turnDeltaNormal; }

  bool isAttacking() { return this.isZombieAttacking(); }

  bool isZombieAttacking() {
    State state = this.getCurrentState();
    return state != nullptr && state.isAttacking(this);
  }

  bool isZombieAttacking(IsoMovingObject other) {
    return GameClient.bClient && this.authOwner == nullptr
        ? this.legsSprite != nullptr &&
              this.legsSprite.CurrentAnim != nullptr &&
              "ZombieBite" ==
                  this.legsSprite.CurrentAnim.name)
        : other == this.target &&
        this.isCurrentState(AttackState.instance());
  }

  int getHitHeadWhileOnFloor() { return this.hitHeadWhileOnFloor; }

  std::string getRealState() { return this.realState.toString(); }

  void setHitHeadWhileOnFloor(int _hitHeadWhileOnFloor) {
    this.hitHeadWhileOnFloor = _hitHeadWhileOnFloor;
    this.networkAI.extraUpdate();
  }

  bool isHitLegsWhileOnFloor() { return this.hitLegsWhileOnFloor; }

  void setHitLegsWhileOnFloor(bool _hitLegsWhileOnFloor) {
    this.hitLegsWhileOnFloor = _hitLegsWhileOnFloor;
  }

  void makeInactive(bool binactive) {
    if (binactive != this.inactive) {
      if (binactive) {
        this.walkType = Integer.toString(Rand.Next(3) + 1);
        this.walkType = "slow" + this.walkType;
        this.bRunning = false;
        this.inactive = true;
        this.speedType = 3;
      } else {
        this.speedType = -1;
        this.inactive = false;
        this.DoZombieStats();
      }
    }
  }

  float getFootstepVolume() { return this.footstepVolume; }

  bool isFacingTarget() {
    if (this.target == nullptr) {
      return false;
    } else if (GameClient.bClient && !this.isLocal() && this.isBumped()) {
      return false;
    } else {
      tempo.set(this.target.x - this.x, this.target.y - this.y).normalize();
      if (tempo.getLength() == 0.0F) {
        return true;
      } else {
        this.getLookVector(tempo2);
        float float0 = Vector2.dot(tempo.x, tempo.y, tempo2.x, tempo2.y);
        return float0 >= 0.8;
      }
    }
  }

  bool isTargetLocationKnown() {
    if (this.target == nullptr) {
      return false;
    } else {
      return this.BonusSpotTime > 0.0F ? true : this.TimeSinceSeenFlesh < 1.0F;
    }
  }

  int getSandboxMemoryDuration() {
    int int0 = SandboxOptions.instance.Lore.Memory.getValue();
    short short0 = 160;
    if (this.inactive) {
      short0 = 5;
    } else if (int0 == 1) {
      short0 = 250;
    } else if (int0 == 3) {
      short0 = 100;
    } else if (int0 == 4) {
      short0 = 5;
    }

    return short0 * 5;
  }

  bool shouldDoFenceLunge() {
    if (!SandboxOptions.instance.Lore.ZombiesFenceLunge.getValue()) {
      return false;
    } else if (Rand.NextBool(3)) {
      return false;
    } else {
      IsoGameCharacter character =
          Type.tryCastTo(this.target, IsoGameCharacter.class);
      if (character == nullptr || (int)character.getZ() != (int)this.getZ()) {
        return false;
      } else {
        return character.getVehicle() != nullptr ? false
                                                 : this.DistTo(character) < 3.9;
      }
    }
  }

  bool isProne() {
    if (!this.isOnFloor()) {
      return false;
    } else {
      return this.bCrawling
                 ? true
                 : this.isCurrentState(ZombieOnGroundState.instance()) ||
                       this.isCurrentState(FakeDeadZombieState.instance());
    }
  }

  void setTarget(IsoMovingObject t) {
    if (this.target != t) {
      this.target = t;
      this.networkAI.extraUpdate();
    }
  }

  bool isAlwaysKnockedDown() { return this.alwaysKnockedDown; }

  void setAlwaysKnockedDown(bool _alwaysKnockedDown) {
    this.alwaysKnockedDown = _alwaysKnockedDown;
  }

  void setDressInRandomOutfit(bool dressInRandom) {
    this.bDressInRandomOutfit = dressInRandom;
  }

  void setBodyToEat(IsoDeadBody body) { this.bodyToEat = body; }

  bool isForceEatingAnimation() { return this.forceEatingAnimation; }

  void setForceEatingAnimation(bool _forceEatingAnimation) {
    this.forceEatingAnimation = _forceEatingAnimation;
  }

  bool isOnlyJawStab() { return this.onlyJawStab; }

  void setOnlyJawStab(bool _onlyJawStab) { this.onlyJawStab = _onlyJawStab; }

  bool isNoTeeth() { return this.noTeeth; }

  void setNoTeeth(bool _noTeeth) { this.noTeeth = _noTeeth; }

  void setThumpFlag(int v) {
    if (this.thumpFlag != v) {
      this.thumpFlag = v;
      this.networkAI.extraUpdate();
    }
  }

  void setThumpCondition(float condition) {
    this.thumpCondition = PZMath.clamp_01(condition);
  }

  void setThumpCondition(int condition, int maxCondition) {
    if (maxCondition <= 0) {
      this.thumpCondition = 0.0F;
    } else {
      condition = PZMath.clamp(condition, 0, maxCondition);
      this.thumpCondition = (float)condition / maxCondition;
    }
  }

  float getThumpCondition() { return this.thumpCondition; }

  bool isStaggerBack() { return this.bStaggerBack; }

  void setStaggerBack(bool _bStaggerBack) { this.bStaggerBack = _bStaggerBack; }

  bool isKnifeDeath() { return this.bKnifeDeath; }

  void setKnifeDeath(bool _bKnifeDeath) { this.bKnifeDeath = _bKnifeDeath; }

  bool isJawStabAttach() { return this.bJawStabAttach; }

  void setJawStabAttach(bool _bJawStabAttach) {
    this.bJawStabAttach = _bJawStabAttach;
  }

  void writeInventory(ByteBuffer b) {
    std::string string = this.isFemale() ? "inventoryfemale" : "inventorymale";
    GameWindow.WriteString(b, string);
    if (this.getInventory() != nullptr) {
      b.put((byte)1);

      try {
        int int0 = -1;

        for (InventoryItem item : this.getInventory().getItems()) {
          if (PersistentOutfits.instance.isHatFallen(
                  this.getPersistentOutfitID()) &&
              item.getScriptItem() != nullptr &&
              item.getScriptItem().getChanceToFall() > 0) {
            int0 = item.id;
          }
        }

        if (int0 != -1) {
          this.getInventory().removeItemWithID(int0);
        }

        std::vector arrayList = this.getInventory().save(b);
        WornItems wornItems = this.getWornItems();
        if (wornItems == nullptr) {
          uint8_t byte0 = 0;
          b.put((byte)byte0);
        } else {
          int int1 = wornItems.size();
          if (int1 > 127) {
            DebugLog.Multiplayer.warn("Too many worn items");
            int1 = 127;
          }

          b.put((byte)int1);

          for (int int2 = 0; int2 < int1; int2++) {
            WornItem wornItem = wornItems.get(int2);
            if (PersistentOutfits.instance.isHatFallen(
                    this.getPersistentOutfitID()) &&
                wornItem.getItem().getScriptItem() != nullptr &&
                wornItem.getItem().getScriptItem().getChanceToFall() > 0) {
              GameWindow.WriteStringUTF(b, "");
              b.putShort((short)-1);
            } else {
              GameWindow.WriteStringUTF(b, wornItem.getLocation());
              b.putShort((short)arrayList.indexOf(wornItem.getItem()));
            }
          }
        }

        AttachedItems attachedItems = this.getAttachedItems();
        if (attachedItems == nullptr) {
          uint8_t byte1 = 0;
          b.put((byte)byte1);
        } else {
          int int3 = attachedItems.size();
          if (int3 > 127) {
            DebugLog.Multiplayer.warn("Too many attached items");
            int3 = 127;
          }

          b.put((byte)int3);

          for (int int4 = 0; int4 < int3; int4++) {
            AttachedItem attachedItem = attachedItems.get(int4);
            GameWindow.WriteStringUTF(b, attachedItem.getLocation());
            b.putShort((short)arrayList.indexOf(attachedItem.getItem()));
          }
        }
      } catch (IOException iOException) {
        DebugLog.Multiplayer.printException(iOException,
                                            "WriteInventory error for zombie " +
                                                this.getOnlineID(),
                                            LogSeverity.Error);
      }
    } else {
      b.put((byte)0);
    }
  }

  void Kill(IsoGameCharacter killer, bool bGory) {
    if (!this.isOnKillDone()) {
      super.Kill(killer);
      if (this.shouldDoInventory()) {
        this.DoZombieInventory();
      }

      LuaEventManager.triggerEvent("OnZombieDead", this);
      if (killer == nullptr) {
        this.DoDeath(nullptr, nullptr, bGory);
      } else if (killer.getPrimaryHandItem() instanceof HandWeapon) {
        this.DoDeath((HandWeapon)killer.getPrimaryHandItem(), killer, bGory);
      } else {
        this.DoDeath(this.getUseHandWeapon(), killer, bGory);
      }
    }
  }

  void Kill(IsoGameCharacter killer) { this.Kill(killer, true); }

  bool shouldDoInventory() {
    return !GameClient.bClient || this.getAttackedBy() instanceof
        IsoPlayer && ((IsoPlayer)this.getAttackedBy()).isLocalPlayer() ||
            this.getAttackedBy() ==
                    IsoWorld.instance.CurrentCell.getFakeZombieForHit() &&
                (this.wasLocal() || this.isLocal());
  }

  void becomeCorpse() {
    if (!this.isOnDeathDone()) {
      if (this.shouldBecomeCorpse()) {
        super.becomeCorpse();
        if (GameClient.bClient && this.shouldDoInventory()) {
          GameClient.sendZombieDeath(this);
        }

        if (!GameClient.bClient) {
          IsoDeadBody deadBody = new IsoDeadBody(this);
          if (this.isFakeDead()) {
            deadBody.setCrawling(true);
          }

          if (GameServer.bServer) {
            GameServer.sendBecomeCorpse(deadBody);
          }
        }
      }
    }
  }

  HitReactionNetworkAI getHitReactionNetworkAI() {
    return this.networkAI.hitReaction;
  }

  NetworkCharacterAI getNetworkCharacterAI() { return this.networkAI; }

  bool wasLocal() {
    return this.getNetworkCharacterAI() == nullptr ||
           this.getNetworkCharacterAI().wasLocal();
  }

  bool isLocal() { return super.isLocal() || !this.isRemoteZombie(); }

  bool isVehicleCollisionActive(BaseVehicle testVehicle) {
    return !super.isVehicleCollisionActive(testVehicle)
               ? false
               : !this.isCurrentState(ZombieFallDownState.instance()) &&
                     !this.isCurrentState(ZombieFallingState.instance());
  }

  void applyDamageFromVehicle(float vehicleSpeed, float damage) {
    this.addBlood(vehicleSpeed);
    this.Health -= damage;
    if (this.Health < 0.0F) {
      this.Health = 0.0F;
    }
  }

  float Hit(BaseVehicle vehicle, float speed, bool isHitFromBehind,
            float hitDirX, float hitDirY) {
    float float0 = this.Hit(vehicle, speed, isHitFromBehind,
                            this.getHitDir().set(hitDirX, hitDirY));
    this.applyDamageFromVehicle(speed, float0);
    super.Hit(vehicle, speed, isHitFromBehind, hitDirX, hitDirY);
    return float0;
  }

  float calcHitDir(IsoGameCharacter wielder, HandWeapon weapon, Vector2 out) {
    float float0 = super.calcHitDir(wielder, weapon, out);
    if (this.getAnimationPlayer() != nullptr) {
      float0 = this.getAnimAngleRadians();
    }

    return float0;
  }

private
  static class Aggro {
    IsoMovingObject obj;
    float damage;
    long lastDamage;

  public
    Aggro(IsoMovingObject arg0, float arg1) {
      this.obj = arg0;
      this.damage = arg1;
      this.lastDamage = System.currentTimeMillis();
    }

    void addDamage(float arg0) {
      this.damage += arg0;
      this.lastDamage = System.currentTimeMillis();
    }

    float getAggro() {
      float float0 = (float)(System.currentTimeMillis() - this.lastDamage);
      float float1 =
          Math.min(1.0F, Math.max(0.0F, (10000.0F - float0) / 5000.0F));
      return Math.min(1.0F, Math.max(0.0F, float1 * this.damage * 0.5F));
    }
  }

  private static final class FloodFill {
    IsoGridSquare start = null;
    const int FLOOD_SIZE = 11;
    const BooleanGrid visited = new BooleanGrid(11, 11);
  private
    final Stack<IsoGridSquare> stack = std::make_unique<Stack<>>();
    IsoBuilding building = null;
    Mover mover = null;
  private
    final ArrayList<IsoGridSquare> choices = new ArrayList<>(121);

    void calculate(Mover moverx, IsoGridSquare square0) {
      this.start = square0;
      this.mover = moverx;
      if (this.start.getRoom() != nullptr) {
        this.building = this.start.getRoom().getBuilding();
      }

      bool boolean0 = false;
      bool boolean1 = false;
      this.push(this.start.getX(), this.start.getY());

      while ((square0 = this.pop()) != nullptr) {
        int int0 = square0.getX();
        int int1 = square0.getY();

        while (this.shouldVisit(int0, int1, int0, int1 - 1)) {
          int1--;
        }

        boolean1 = false;
        boolean0 = false;

        do {
          this.visited.setValue(this.gridX(int0), this.gridY(int1), true);
          IsoGridSquare square1 = IsoWorld.instance.CurrentCell.getGridSquare(
              int0, int1, this.start.getZ());
          if (square1 != nullptr) {
            this.choices.add(square1);
          }

          if (!boolean0 && this.shouldVisit(int0, int1, int0 - 1, int1)) {
            this.push(int0 - 1, int1);
            boolean0 = true;
          } else if (boolean0 &&
                     !this.shouldVisit(int0, int1, int0 - 1, int1)) {
            boolean0 = false;
          } else if (boolean0 &&
                     !this.shouldVisit(int0 - 1, int1, int0 - 1, int1 - 1)) {
            this.push(int0 - 1, int1);
          }

          if (!boolean1 && this.shouldVisit(int0, int1, int0 + 1, int1)) {
            this.push(int0 + 1, int1);
            boolean1 = true;
          } else if (boolean1 &&
                     !this.shouldVisit(int0, int1, int0 + 1, int1)) {
            boolean1 = false;
          } else if (boolean1 &&
                     !this.shouldVisit(int0 + 1, int1, int0 + 1, int1 - 1)) {
            this.push(int0 + 1, int1);
          }

          int1++;
        } while (!this.shouldVisit(int0, int1 - 1, int0, int1));
      }
    }

    bool shouldVisit(int int2, int int3, int int0, int int1) {
      if (this.gridX(int0) < 11 && this.gridX(int0) >= 0) {
        if (this.gridY(int1) < 11 && this.gridY(int1) >= 0) {
          if (this.visited.getValue(this.gridX(int0), this.gridY(int1))) {
            return false;
          } else {
            IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(
                int0, int1, this.start.getZ());
            if (square == nullptr) {
              return false;
            } else if (square.Has(IsoObjectType.stairsBN) ||
                       square.Has(IsoObjectType.stairsMN) ||
                       square.Has(IsoObjectType.stairsTN)) {
              return false;
            } else if (square.Has(IsoObjectType.stairsBW) ||
                       square.Has(IsoObjectType.stairsMW) ||
                       square.Has(IsoObjectType.stairsTW)) {
              return false;
            } else if (square.getRoom() != nullptr &&
                       this.building == nullptr) {
              return false;
            } else {
              return square.getRoom() == nullptr && this.building != nullptr
                         ? false
                         : !IsoWorld.instance.CurrentCell.blocked(
                               this.mover, int0, int1, this.start.getZ(), int2,
                               int3, this.start.getZ());
            }
          }
        } else {
          return false;
        }
      } else {
        return false;
      }
    }

    void push(int int0, int int1) {
      IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(
          int0, int1, this.start.getZ());
      this.stack.push(square);
    }

    IsoGridSquare pop() {
      return this.stack.isEmpty() ? nullptr : this.stack.pop();
    }

    int gridX(int int0) { return int0 - (this.start.getX() - 5); }

    int gridY(int int0) { return int0 - (this.start.getY() - 5); }

    int gridX(IsoGridSquare square) {
      return square.getX() - (this.start.getX() - 5);
    }

    int gridY(IsoGridSquare square) {
      return square.getY() - (this.start.getY() - 5);
    }

    IsoGridSquare choose() {
      if (this.choices.isEmpty()) {
        return null;
      } else {
        int int0 = Rand.Next(this.choices.size());
        return this.choices.get(int0);
      }
    }

    void reset() {
      this.building = nullptr;
      this.choices.clear();
      this.stack.clear();
      this.visited.clear();
    }
  }

  public static enum ZombieSound {
    Burned(10), DeadCloseKilled(10), DeadNotCloseKilled(10), Hurt(10), Idle(15),
    Lunge(40), MAX(-1);

    int radius; private static final IsoZombie.ZombieSound[] values = values();

    private ZombieSound(int int1){this.radius = int1;}

  int radius() { return this.radius; }

public
  static IsoZombie.ZombieSound fromIndex(int int0) {
    return int0 >= 0 && int0 < values.length ? values[int0] : MAX;
  }
}

private static class s_performance {
  static const PerformanceProfileProbe update =
      new PerformanceProfileProbe("IsoZombie.update");
  static const PerformanceProfileProbe postUpdate =
      new PerformanceProfileProbe("IsoZombie.postUpdate");
}
} // namespace characters
} // namespace zombie
} // namespace zombie
