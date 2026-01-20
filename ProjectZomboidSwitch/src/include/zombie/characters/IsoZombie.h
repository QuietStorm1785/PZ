#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/PersistentOutfits.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SharedDescriptors/Descriptor.h"
#include "zombie/SoundManager.h"
#include "zombie/SystemDisabler.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/WorldSoundManager/ResultBiggestSound.h"
#include "zombie/WorldSoundManager/WorldSound.h"
#include "zombie/ai/State.h"
#include "zombie/ai/ZombieGroupManager.h"
#include "zombie/ai/astar/AStarPathFinder/PathFindProgress.h"
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
#include "zombie/audio/parameters/ParameterCharacterMovementSpeed/MovementType.h"
#include "zombie/audio/parameters/ParameterFootstepMaterial.h"
#include "zombie/audio/parameters/ParameterFootstepMaterial2.h"
#include "zombie/audio/parameters/ParameterPlayerDistance.h"
#include "zombie/audio/parameters/ParameterShoeType.h"
#include "zombie/audio/parameters/ParameterVehicleHitLocation.h"
#include "zombie/audio/parameters/ParameterVehicleHitLocation/HitLocation.h"
#include "zombie/audio/parameters/ParameterZombieState.h"
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characters/AttachedItems/AttachedItem.h"
#include "zombie/characters/AttachedItems/AttachedItems.h"
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/IsoGameCharacter/Location.h"
#include "zombie/characters/IsoZombie/Aggro.h"
#include "zombie/characters/IsoZombie/FloodFill.h"
#include "zombie/characters/IsoZombie/s_performance.h"
#include "zombie/characters/WornItems/WornItem.h"
#include "zombie/characters/WornItems/WornItems.h"
#include "zombie/characters/action/ActionContext.h"
#include "zombie/characters/action/ActionGroup.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/RenderSettings.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas/BodyTexture.h"
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
#include "zombie/iso/LosUtil/TestResults.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/areas/IsoBuilding.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoFireManager.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/IsoWindowFrame.h"
#include "zombie/iso/objects/IsoZombieGiblets.h"
#include "zombie/iso/objects/IsoZombieGiblets/GibletType.h"
#include "zombie/iso/objects/interfaces/Thumpable.h"
#include "zombie/iso/sprite/IsoAnim.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/MPStatistics.h"
#include "zombie/network/NetworkVariables/PredictionTypes.h"
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
#include "zombie/vehicles/BaseVehicle/Vector2ObjectPool.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include "zombie/vehicles/VehiclePart.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace characters {


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
    BodyTexture atlasTex = nullptr;
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
   private std::vector<InventoryItem> itemsToSpawnAtDeath = nullptr;
    float soundReactDelay = 0.0F;
    const Location delayedSound = std::make_shared<Location>(-1, -1, -1);
    bool bSoundSourceRepeating = false;
    void* soundSourceTarget = nullptr;
    float soundAttract = 0.0F;
    float soundAttractTimeout = 0.0F;
    const Vector2 hitAngle = std::make_shared<Vector2>();
    bool alerted = false;
    std::string walkType = nullptr;
    float footstepVolume = 1.0F;
    Descriptor sharedDesc;
    bool bDressInRandomOutfit = false;
    std::string pendingOutfitName;
    const HumanVisual humanVisual = std::make_shared<HumanVisual>(this);
    int crawlerType = 0;
    std::string playerAttackPosition = nullptr;
    float eatSpeed = 1.0F;
    bool sitAgainstWall = false;
    static const int CHECK_FOR_CORPSE_TIMER_MAX = 10000;
    float checkForCorpseTimer = 10000.0F;
    IsoDeadBody bodyToEat = nullptr;
    IsoMovingObject eatBodyTarget;
    int hitTime = 0;
    int thumpTimer = 0;
    bool hitLegsWhileOnFloor = false;
    bool collideWhileHit = true;
    float m_characterTextureAnimTime = 0.0F;
    float m_characterTextureAnimDuration = 1.0F;
    int lastPlayerHit = -1;
    const ItemVisuals itemVisuals = std::make_shared<ItemVisuals>();
    int hitHeadWhileOnFloor = 0;
    BaseVehicle vehicle4testCollision = nullptr;
    std::string SpriteName = "BobZ";
    static const int PALETTE_COUNT = 3;
    const Vector2 vectorToTarget = std::make_shared<Vector2>();
    float AllowRepathDelay = 0.0F;
    bool KeepItReal = false;
    bool isSkeleton = false;
    const ParameterCharacterInside parameterCharacterInside = std::make_shared<ParameterCharacterInside>(this);
    const ParameterCharacterMovementSpeed parameterCharacterMovementSpeed = std::make_shared<ParameterCharacterMovementSpeed>(this);
    const ParameterFootstepMaterial parameterFootstepMaterial = std::make_shared<ParameterFootstepMaterial>(this);
    const ParameterFootstepMaterial2 parameterFootstepMaterial2 = std::make_shared<ParameterFootstepMaterial2>(this);
    const ParameterPlayerDistance parameterPlayerDistance = std::make_shared<ParameterPlayerDistance>(this);
    const ParameterShoeType parameterShoeType = std::make_shared<ParameterShoeType>(this);
    const ParameterVehicleHitLocation parameterVehicleHitLocation = std::make_shared<ParameterVehicleHitLocation>();
    const ParameterZombieState parameterZombieState = std::make_shared<ParameterZombieState>(this);
    bool scratch = false;
    bool laceration = false;
    const NetworkZombieAI networkAI;
    UdpConnection authOwner = nullptr;
    IsoPlayer authOwnerPlayer = nullptr;
    ZombiePacket zombiePacket = std::make_shared<ZombiePacket>();
    bool zombiePacketUpdated = false;
    long lastChangeOwner = -1L;
    static const SharedSkeleAnimationRepository m_sharedSkeleRepo = std::make_shared<SharedSkeleAnimationRepository>();
    int palette = 0;
    int AttackAnimTime = 50;
    static int AttackAnimTimeMax = 50;
    IsoMovingObject spottedLast = nullptr;
   Aggro[] aggroList = new Aggro[4];
    int spotSoundDelay = 0;
    float movex;
    float movey;
    int stepFrameLast = -1;
    OnceEvery networkUpdate = std::make_shared<OnceEvery>(1.0F);
    short lastRemoteUpdate = 0;
    short OnlineID = -1;
   private static const std::vector<IsoDeadBody> tempBodies = std::make_unique<std::vector<>>();
    float timeSinceRespondToSound = 1000000.0F;
    std::string walkVariantUse = nullptr;
    std::string walkVariant = "ZombieWalk";
    bool bLunger;
    bool bRunning;
    bool bCrawling;
    bool bCanCrawlUnderVehicle = true;
    bool bCanWalk = true;
    bool bRemote;
    static const FloodFill floodFill = std::make_shared<FloodFill>();
    bool ImmortalTutorialZombie;

    std::string getObjectName() {
      return "Zombie";
   }

    short getOnlineID() {
      return this.OnlineID;
   }

    bool isRemoteZombie() {
      return this.authOwner == nullptr;
   }

    void setVehicle4TestCollision(BaseVehicle var1) {
      this.vehicle4testCollision = var1;
   }

    public IsoZombie(IsoCell var1) {
      this(var1, nullptr, -1);
   }

    public IsoZombie(IsoCell var1, SurvivorDesc var2, int var3) {
      super(var1, 0.0F, 0.0F, 0.0F);
      this.registerVariableCallbacks();
      this.Health = 1.8F + Rand.Next(0.0F, 0.3F);
      this.weight = 0.7F;
      this.dir = IsoDirections.fromIndex(Rand.Next(8));
      this.humanVisual.randomBlood();
      if (var2 != nullptr) {
         this.descriptor = var2;
         this.palette = var3;
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
      this.networkAI = std::make_shared<NetworkZombieAI>(this);
      this.clearAggroList();
   }

    void initializeStates() {
    std::unordered_map var1 = this.getStateUpdateLookup();
      var1.clear();
      var1.put("attack-network", AttackNetworkState.instance());
      var1.put("attackvehicle-network", IdleState.instance());
      var1.put("fakedead-attack-network", IdleState.instance());
      var1.put("lunge-network", LungeNetworkState.instance());
      var1.put("walktoward-network", WalkTowardNetworkState.instance());
      if (this.bCrawling) {
         var1.put("attack", AttackState.instance());
         var1.put("fakedead", FakeDeadZombieState.instance());
         var1.put("fakedead-attack", FakeDeadAttackState.instance());
         var1.put("getup", ZombieGetUpFromCrawlState.instance());
         var1.put("hitreaction", ZombieHitReactionState.instance());
         var1.put("hitreaction-hit", ZombieHitReactionState.instance());
         var1.put("idle", ZombieIdleState.instance());
         var1.put("onground", ZombieOnGroundState.instance());
         var1.put("pathfind", PathFindState.instance());
         var1.put("reanimate", ZombieReanimateState.instance());
         var1.put("staggerback", StaggerBackState.instance());
         var1.put("thump", ThumpState.instance());
         var1.put("turn", CrawlingZombieTurnState.instance());
         var1.put("walktoward", WalkTowardState.instance());
      } else {
         var1.put("attack", AttackState.instance());
         var1.put("attackvehicle", AttackVehicleState.instance());
         var1.put("bumped", BumpedState.instance());
         var1.put("climbfence", ClimbOverFenceState.instance());
         var1.put("climbwindow", ClimbThroughWindowState.instance());
         var1.put("eatbody", ZombieEatBodyState.instance());
         var1.put("falldown", ZombieFallDownState.instance());
         var1.put("falling", ZombieFallingState.instance());
         var1.put("face-target", ZombieFaceTargetState.instance());
         var1.put("fakedead", FakeDeadZombieState.instance());
         var1.put("fakedead-attack", FakeDeadAttackState.instance());
         var1.put("getdown", ZombieGetDownState.instance());
         var1.put("getup", ZombieGetUpState.instance());
         var1.put("hitreaction", ZombieHitReactionState.instance());
         var1.put("hitreaction-hit", ZombieHitReactionState.instance());
         var1.put("idle", ZombieIdleState.instance());
         var1.put("lunge", LungeState.instance());
         var1.put("onground", ZombieOnGroundState.instance());
         var1.put("pathfind", PathFindState.instance());
         var1.put("sitting", ZombieSittingState.instance());
         var1.put("staggerback", StaggerBackState.instance());
         var1.put("thump", ThumpState.instance());
         var1.put("turnalerted", ZombieTurnAlerted.instance());
         var1.put("walktoward", WalkTowardState.instance());
      }
   }

    void registerVariableCallbacks() {
      this.setVariable("bClient", () -> GameClient.bClient && this.isRemoteZombie());
      this.setVariable(
         "bMovingNetwork",
         () -> (this.isLocal() || !this.isBumped())
            && (IsoUtils.DistanceManhatten(this.networkAI.targetX, this.networkAI.targetY, this.x, this.y) > 0.5F || this.z != this.networkAI.targetZ)
      );
      this.setVariable("hitHeadType", this::getHitHeadWhileOnFloor);
      this.setVariable("realState", this::getRealState);
      this.setVariable("battack", () -> {
         if (SystemDisabler.zombiesDontAttack) {
    return false;
         } else if (this.target != nullptr && !this.target.isZombiesDontAttack()) {
            if (this.dynamic_cast<IsoGameCharacter*>(target) != nullptr) {
               if (this.target.isOnFloor() && ((IsoGameCharacter)this.target).getCurrentState() != BumpedState.instance()) {
                  this.setTarget(nullptr);
    return false;
               }

    BaseVehicle var1 = ((IsoGameCharacter)this.target).getVehicle();
               if (var1 != nullptr) {
    return false;
               }

               if (((IsoGameCharacter)this.target).ReanimatedCorpse != nullptr) {
    return false;
               }

               if (((IsoGameCharacter)this.target).getStateMachine().getCurrent() == ClimbOverWallState.instance()) {
    return false;
               }
            }

            if (this.bReanimate) {
    return false;
            } else if (Math.abs(this.target.z - this.z) >= 0.2F) {
    return false;
            } else if (this.dynamic_cast<IsoPlayer*>(target) != nullptr && ((IsoPlayer)this.target).isGhostMode()) {
    return false;
            } else if (this.bFakeDead) {
               return !this.isUnderVehicle() && this.DistTo(this.target) < 1.3F;
            } else if (!this.bCrawling) {
    IsoGridSquare var5 = this.getCurrentSquare();
    IsoGridSquare var2 = this.target.getCurrentSquare();
               if (var5 != nullptr && var5.isSomethingTo(var2)) {
    return false;
               } else {
    float var3 = this.bCrawling ? 1.4F : 0.72F;
    float var4 = this.vectorToTarget.getLength();
                  return var4 <= var3;
               }
            } else {
               return !this.isUnderVehicle() && this.DistTo(this.target) < 1.3F;
            }
         } else {
    return false;
         }
      });
      this.setVariable("isFacingTarget", this::isFacingTarget);
      this.setVariable("targetSeenTime", this::getTargetSeenTime);
      this.setVariable("battackvehicle", () -> {
         if (this.getVariableBoolean("bPathfind")) {
    return false;
         } else if (this.isMoving()) {
    return false;
         } else if (this.target == nullptr) {
    return false;
         } else if (Math.abs(this.target.z - this.z) >= 0.8F) {
    return false;
         } else if (this.dynamic_cast<IsoPlayer*>(target) != nullptr && ((IsoPlayer)this.target).isGhostMode()) {
    return false;
         } else if (!(this.dynamic_cast<IsoGameCharacter*>(target) != nullptr)) {
    return false;
         } else {
    BaseVehicle var1 = ((IsoGameCharacter)this.target).getVehicle();
            return var1 != nullptr && var1.isCharacterAdjacentTo(this);
         }
      });
      this.setVariable("beatbodytarget", () -> {
         if (this.isForceEatingAnimation()) {
    return true;
         } else {
            if (!GameServer.bServer) {
               this.updateEatBodyTarget();
            }

            return this.getEatBodyTarget() != nullptr;
         }
      });
      this.setVariable("bbecomecrawler", this::isBecomeCrawler, this::setBecomeCrawler);
      this.setVariable("bfakedead", () -> this.bFakeDead);
      this.setVariable("bfalling", () -> this.z > 0.0F && this.fallTime > 2.0F);
      this.setVariable("bhastarget", () -> {
         if (this.dynamic_cast<IsoGameCharacter*>(target) != nullptr && ((IsoGameCharacter)this.target).ReanimatedCorpse != nullptr) {
            this.setTarget(nullptr);
         }

         return this.target != nullptr;
      });
      this.setVariable("shouldSprint", () -> {
         if (this.dynamic_cast<IsoGameCharacter*>(target) != nullptr && ((IsoGameCharacter)this.target).ReanimatedCorpse != nullptr) {
            this.setTarget(nullptr);
         }

         return this.target != nullptr || this.soundSourceTarget != nullptr && !(this.dynamic_cast<IsoZombie*>(soundSourceTarget) != nullptr);
      });
      this.setVariable("bknockeddown", this::isKnockedDown);
      this.setVariable(
         "blunge",
         () -> {
            if (this.target == nullptr) {
    return false;
            } else if ((int)this.getZ() != (int)this.target.getZ()) {
    return false;
            } else {
               if (this.dynamic_cast<IsoGameCharacter*>(target) != nullptr) {
                  if (((IsoGameCharacter)this.target).getVehicle() != nullptr) {
    return false;
                  }

                  if (((IsoGameCharacter)this.target).ReanimatedCorpse != nullptr) {
    return false;
                  }
               }

               if (this.dynamic_cast<IsoPlayer*>(target) != nullptr && ((IsoPlayer)this.target).isGhostMode()) {
                  this.setTarget(nullptr);
    return false;
               } else {
    IsoGridSquare var1 = this.getCurrentSquare();
    IsoGridSquare var2 = this.target.getCurrentSquare();
                  if (var2 != nullptr && var2.isSomethingTo(var1) && this.getThumpTarget() != nullptr) {
    return false;
                  } else if (this.isCurrentState(ZombieTurnAlerted.instance()) && !this.isFacingTarget()) {
    return false;
                  } else {
    float var3 = this.vectorToTarget.getLength();
                     return !(var3 > 3.5F) || var3 <= 4.0F && this.dynamic_cast<IsoGameCharacter*>(target) != nullptr && ((IsoGameCharacter)this.target).getVehicle() != nullptr
                        ? !PolygonalMap2.instance
                           .lineClearCollide(this.getX(), this.getY(), this.target.x, this.target.y, (int)this.getZ(), this.target, false, true)
                        : false;
                  }
               }
            }
         }
      );
      this.setVariable("bpassengerexposed", () -> AttackVehicleState.instance().isPassengerExposed(this));
      this.setVariable(
         "bistargetissmallvehicle",
         () -> this.target != nullptr && this.dynamic_cast<IsoPlayer*>(target) != nullptr && ((IsoPlayer)this.target).getVehicle() != nullptr
            ? ((IsoPlayer)this.target).getVehicle().getScript().isSmallVehicle
            : true
      );
      this.setVariable("breanimate", this::isReanimate, this::setReanimate);
      this.setVariable("bstaggerback", this::isStaggerBack);
      this.setVariable("bthump", () -> {
         if (this.getThumpTarget() instanceof IsoObject && !(this.getThumpTarget() instanceof BaseVehicle)) {
    IsoObject var1 = (IsoObject)this.getThumpTarget();
            if (var1.getSquare() == nullptr || this.DistToSquared(var1.getX() + 0.5F, var1.getY() + 0.5F) > 9.0F) {
               this.setThumpTarget(nullptr);
            }
         }

         if (this.getThumpTimer() > 0) {
            this.setThumpTarget(nullptr);
         }

         return this.getThumpTarget() != nullptr;
      });
      this.setVariable("bundervehicle", this::isUnderVehicle);
      this.setVariable("bBeingSteppedOn", this::isBeingSteppedOn);
      this.setVariable(
         "distancetotarget", () -> this.target == nullptr ? "" : std::string.valueOf(this.vectorToTarget.getLength() - this.getWidth() + this.target.getWidth())
      );
      this.setVariable("lasttargetseen", () -> this.LastTargetSeenX != -1);
      this.setVariable("lungetimer", () -> this.LungeTimer);
      this.setVariable("reanimatetimer", this::getReanimateTimer);
      this.setVariable("stateeventdelaytimer", this::getStateEventDelayTimer);
      this.setVariable("turndirection", () -> {
         if (this.getPath2() != nullptr) {
            return "";
         } else if (this.target != nullptr && this.vectorToTarget.getLength() != 0.0F) {
            if (this.isRemoteZombie()) {
               tempo.set(this.networkAI.targetX - this.x, this.networkAI.targetY - this.y);
            } else {
               tempo.set(this.vectorToTarget);
            }

    IsoDirections var3 = IsoDirections.fromAngle(tempo);
            if (this.dir == var3) {
               return "";
            } else {
    bool var4 = CrawlingZombieTurnState.calculateDir(this, var3);
               return var4 ? "left" : "right";
            }
         } else if (this.isCurrentState(WalkTowardState.instance())) {
            WalkTowardState.instance().calculateTargetLocation(this, tempo);
            tempo.x = tempo.x - this.getX();
            tempo.y = tempo.y - this.getY();
    IsoDirections var1 = IsoDirections.fromAngle(tempo);
            if (this.dir == var1) {
               return "";
            } else {
    bool var2 = CrawlingZombieTurnState.calculateDir(this, var1);
               return var2 ? "left" : "right";
            }
         } else {
            if (this.isCurrentState(PathFindState.instance())) {
            }

            return "";
         }
      });
      this.setVariable("hitforce", this::getHitForce);
      this.setVariable("alerted", () -> this.alerted);
      this.setVariable("zombiewalktype", () -> this.walkType);
      this.setVariable("crawlertype", () -> this.crawlerType);
      this.setVariable("bGetUpFromCrawl", this::shouldGetUpFromCrawl);
      this.setVariable("playerattackposition", this::getPlayerAttackPosition);
      this.setVariable("eatspeed", () -> this.eatSpeed);
      this.setVariable("issitting", this::isSitAgainstWall);
      this.setVariable("bKnifeDeath", this::isKnifeDeath, this::setKnifeDeath);
      this.setVariable("bJawStabAttach", this::isJawStabAttach, this::setJawStabAttach);
      this.setVariable("bPathFindPrediction", () -> PredictionTypes.PathFind == this.networkAI.predictionType));
      this.setVariable("bCrawling", this::isCrawling, this::setCrawler);
   }

    void actionStateChanged(ActionContext var1) {
      super.actionStateChanged(var1);
      if (this.networkAI != nullptr && GameServer.bServer) {
         this.networkAI.extraUpdate();
      }
   }

    ActionContext getActionContext() {
      return this.actionContext;
   }

    void onAnimPlayerCreated(AnimationPlayer var1) {
      super.onAnimPlayerCreated(var1);
      var1.setSharedAnimRepo(m_sharedSkeleRepo);
   }

    std::string GetAnimSetName() {
      return this.bCrawling ? "zombie-crawler" : "zombie";
   }

    void InitSpritePartsZombie() {
    SurvivorDesc var1 = this.descriptor;
      this.InitSpritePartsZombie(var1);
   }

    void InitSpritePartsZombie(SurvivorDesc var1) {
      this.sprite.AnimMap.clear();
      this.sprite.AnimStack.clear();
      this.sprite.CurrentAnim = std::make_unique<IsoAnim>();
      this.sprite.CurrentAnim.name = "REMOVE";
      this.legsSprite = this.sprite;
      this.legsSprite.name = var1.torso;
      this.ZombieID = Rand.Next(10000);
      this.bUseParts = true;
   }

    void pathToCharacter(IsoGameCharacter var1) {
      if (!(this.AllowRepathDelay > 0.0F)
         || !this.isCurrentState(PathFindState.instance())
            && !this.isCurrentState(WalkTowardState.instance())
            && !this.isCurrentState(WalkTowardNetworkState.instance())) {
         super.pathToCharacter(var1);
      }
   }

    void pathToLocationF(float var1, float var2, float var3) {
      if (!(this.AllowRepathDelay > 0.0F)
         || !this.isCurrentState(PathFindState.instance())
            && !this.isCurrentState(WalkTowardState.instance())
            && !this.isCurrentState(WalkTowardNetworkState.instance())) {
         super.pathToLocationF(var1, var2, var3);
      }
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
      this.walkVariant = "ZombieWalk";
      this.SpriteName = "BobZ";
      if (this.palette != 1) {
         this.SpriteName = this.SpriteName + this.palette;
      }

    SurvivorDesc var4 = this.descriptor;
      this.setFemale(var4.isFemale());
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

      this.InitSpritePartsZombie(var4);
      this.sprite.def.tintr = 0.95F + Rand.Next(5) / 100.0F;
      this.sprite.def.tintg = 0.95F + Rand.Next(5) / 100.0F;
      this.sprite.def.tintb = 0.95F + Rand.Next(5) / 100.0F;
      this.setDefaultState(ZombieIdleState.instance());
      this.DoZombieStats();
      var1.getFloat();
      this.setWidth(0.3F);
      this.TimeSinceSeenFlesh = var1.getInt();
      this.setAlpha(0.0F);
      this.setFakeDead(var1.getInt() == 1);
    std::vector var5 = this.savedInventoryItems;
    uint8_t var6 = var1.get();

      for (int var7 = 0; var7 < var6; var7++) {
    std::string var8 = GameWindow.ReadString(var1);
    short var9 = var1.getShort();
         if (var9 >= 0 && var9 < var5.size() && this.wornItems.getBodyLocationGroup().getLocation(var8) != nullptr) {
            this.wornItems.setItem(var8, (InventoryItem)var5.get(var9));
         }
      }

      this.setStateMachineLocked(false);
      this.setDefaultState();
      this.getCell().getZombieList().push_back(this);
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      var1.putFloat(0.0F);
      var1.putInt((int)this.TimeSinceSeenFlesh);
      var1.putInt(this.isFakeDead() ? 1 : 0);
      if (this.wornItems.size() > 127) {
         throw RuntimeException("too many worn items");
      } else {
         var1.put((byte)this.wornItems.size());
         this.wornItems.forEach(var2x -> {
            GameWindow.WriteString(var1, var2x.getLocation());
            var1.putShort((short)this.savedInventoryItems.indexOf(var2x.getItem()));
         });
      }
   }

    void collideWith(IsoObject var1) {
      if (!this.Ghost && var1 != nullptr) {
         if (var1.rerouteCollide != nullptr) {
            var1 = this.rerouteCollide;
         }

    State var2 = this.getCurrentState();
         boolean var3 = this.isCurrentState(PathFindState.instance())
            || this.isCurrentState(LungeState.instance())
            || this.isCurrentState(LungeNetworkState.instance())
            || this.isCurrentState(WalkTowardState.instance())
            || this.isCurrentState(WalkTowardNetworkState.instance());
    IsoWindow var4 = (IsoWindow)Type.tryCastTo(var1, IsoWindow.class);
         if (var4 != nullptr && var4.canClimbThrough(this) && var3) {
            if (!this.isFacingObject(var4, 0.8F)) {
               super.collideWith(var1);
               return;
            }

            if (var2 != PathFindState.instance() && !this.bCrawling) {
               this.climbThroughWindow(var4);
            }
         } else if (dynamic_cast<IsoThumpable*>(var1) != nullptr && ((IsoThumpable)var1).canClimbThrough(this) && var3) {
            if (var2 != PathFindState.instance() && !this.bCrawling) {
               this.climbThroughWindow((IsoThumpable)var1);
            }
         } else if ((!(dynamic_cast<IsoDoor*>(var1) != nullptr) || !((IsoDoor)var1).isHoppable()) && var1 != nullptr && var1.getThumpableFor(this) != nullptr && var3) {
            boolean var5 = (
                  this.isCurrentState(PathFindState.instance())
                     || this.isCurrentState(WalkTowardState.instance())
                     || this.isCurrentState(WalkTowardNetworkState.instance())
               )
               && this.getPathFindBehavior2().isGoalSound();
            if (!SandboxOptions.instance.Lore.ThumpNoChasing.getValue() && this.target == nullptr && !var5) {
               this.setVariable("bPathfind", false);
               this.setVariable("bMoving", false);
            } else {
               if (dynamic_cast<IsoThumpable*>(var1) != nullptr && !SandboxOptions.instance.Lore.ThumpOnConstruction.getValue()) {
                  return;
               }

    void* var6 = var1;
               if (dynamic_cast<IsoWindow*>(var1) != nullptr && var1.getThumpableFor(this) != nullptr && var1.isDestroyed()) {
                  var6 = var1.getThumpableFor(this);
               }

               this.setThumpTarget((Thumpable)var6);
            }

            this.setPath2(nullptr);
         }

         if (!this.bCrawling && IsoWindowFrame.isWindowFrame(var1) && var3 && var2 != PathFindState.instance()) {
            this.climbThroughWindowFrame(var1);
         }

         super.collideWith(var1);
      }
   }

    float Hit(HandWeapon var1, IsoGameCharacter var2, float var3, bool var4, float var5, bool var6) {
      if (Core.bTutorial && this.ImmortalTutorialZombie) {
         return 0.0F;
      } else {
         BodyPartType var7 = BodyPartType.FromIndex(
            Rand.Next(BodyPartType.ToIndex(BodyPartType.Torso_Upper), BodyPartType.ToIndex(BodyPartType.Torso_Lower) + 1)
         );
         if (Rand.NextBool(7)) {
            var7 = BodyPartType.Head;
         }

         if (var2.isCriticalHit() && Rand.NextBool(3)) {
            var7 = BodyPartType.Head;
         }

         LuaEventManager.triggerEvent("OnHitZombie", this, var2, var7, var1);
    float var8 = super.Hit(var1, var2, var3, var4, var5, var6);
         if (GameServer.bServer && !this.isRemoteZombie()) {
            this.addAggro(var2, var8);
         }

         this.TimeSinceSeenFlesh = 0.0F;
         if (!this.isDead()
            && !this.isOnFloor()
            && !var4
            && var1 != nullptr
            && var1.getScriptItem().getCategories().contains("Blade")
            && dynamic_cast<IsoPlayer*>(var2) != nullptr
            && this.DistToProper(var2) <= 0.9F
            && (
               this.isCurrentState(AttackState.instance())
                  || this.isCurrentState(AttackNetworkState.instance())
                  || this.isCurrentState(LungeState.instance())
                  || this.isCurrentState(LungeNetworkState.instance())
            )) {
            this.setHitForce(0.5F);
            this.changeState(StaggerBackState.instance());
         }

         if (GameServer.bServer || GameClient.bClient && this.isDead()) {
            this.lastPlayerHit = var2.getOnlineID();
         }

    return var8;
      }
   }

    void onMouseLeftClick() {
      if (IsoPlayer.getInstance() != nullptr && !IsoPlayer.getInstance().isAiming()) {
         if (IsoPlayer.getInstance().IsAttackRange(this.getX(), this.getY(), this.getZ())) {
    Vector2 var1 = std::make_shared<Vector2>(this.getX(), this.getY());
            var1.x = var1.x - IsoPlayer.getInstance().getX();
            var1.y = var1.y - IsoPlayer.getInstance().getY();
            var1.normalize();
            IsoPlayer.getInstance().DirectionFromVector(var1);
            IsoPlayer.getInstance().AttemptAttack();
         }
      }
   }

    void renderAtlasTexture(float var1, float var2, float var3) {
      if (this.atlasTex != nullptr) {
         if (IsoSprite.globalOffsetX == -1.0F) {
            IsoSprite.globalOffsetX = -IsoCamera.frameState.OffX;
            IsoSprite.globalOffsetY = -IsoCamera.frameState.OffY;
         }

    float var4 = IsoUtils.XToScreen(var1, var2, var3, 0);
    float var5 = IsoUtils.YToScreen(var1, var2, var3, 0);
         this.sx = var4;
         this.sy = var5;
         var4 = this.sx + IsoSprite.globalOffsetX;
         var5 = this.sy + IsoSprite.globalOffsetY;
    ColorInfo var6 = inf.set(1.0F, 1.0F, 1.0F, 1.0F);
         if (PerformanceSettings.LightingFrameSkip < 3 && this.getCurrentSquare() != nullptr) {
            this.getCurrentSquare().interpolateLight(var6, var1 - this.getCurrentSquare().getX(), var2 - this.getCurrentSquare().getY());
         }

         this.atlasTex.render((int)var4, (int)var5, var6.r, var6.g, var6.b, var6.a);
      }
   }

    void render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      if (this.getCurrentState() == FakeDeadZombieState.instance()) {
         if (this.bDressInRandomOutfit) {
            ModelManager.instance.dressInRandomOutfit(this);
         }

         if (this.atlasTex == nullptr) {
            this.atlasTex = DeadBodyAtlas.instance.getBodyTexture(this);
            DeadBodyAtlas.instance.render();
         }

         if (this.atlasTex != nullptr) {
            this.renderAtlasTexture(var1, var2, var3);
         }
      } else {
         if (this.atlasTex != nullptr) {
            this.atlasTex = nullptr;
         }

         if (IsoCamera.CamCharacter != IsoPlayer.getInstance()) {
            this.setAlphaAndTarget(1.0F);
         }

         super.render(var1, var2, var3, var4, var5, var6, var7);
      }
   }

    void renderlast() {
      super.renderlast();
      if (DebugOptions.instance.ZombieRenderCanCrawlUnderVehicle.getValue() && this.isCanCrawlUnderVehicle()) {
         this.renderTextureOverHead("media/ui/FavoriteStar.png");
      }

      if (DebugOptions.instance.ZombieRenderMemory.getValue()) {
    std::string var1;
         if (this.target == nullptr) {
            var1 = "media/ui/Moodles/Moodle_Icon_Bored.png";
         } else if (this.BonusSpotTime == 0.0F) {
            var1 = "media/ui/Moodles/Moodle_Icon_Angry.png";
         } else {
            var1 = "media/ui/Moodles/Moodle_Icon_Zombie.png";
         }

         this.renderTextureOverHead(var1);
    int var2 = (int)IsoUtils.XToScreenExact(this.x, this.y, this.z, 0);
    int var3 = (int)IsoUtils.YToScreenExact(this.x, this.y, this.z, 0);
    int var4 = TextManager.instance.getFontFromEnum(UIFont.Small).getLineHeight();
    int var5;
         TextManager.instance.DrawString(var2, var5 = var3 + var4, "AllowRepathDelay : " + this.AllowRepathDelay);
         TextManager.instance.DrawString(var2, var3 = var5 + var4, "BonusSpotTime : " + this.BonusSpotTime);
    int var7;
         TextManager.instance.DrawString(var2, var7 = var3 + var4, "TimeSinceSeenFlesh : " + this.TimeSinceSeenFlesh);
      }
   }

    bool renderTextureInsteadOfModel(float var1, float var2) {
    bool var3 = this.isCurrentState(WalkTowardState.instance()) || this.isCurrentState(PathFindState.instance());
    std::string var4 = "zombie";
    std::string var5 = var3 ? "walktoward" : "idle";
    uint8_t var6 = 4;
    int var7 = (int)(this.m_characterTextureAnimTime / this.m_characterTextureAnimDuration * var6);
    float var8 = (var3 ? 0.67F : 1.0F) * ((float)var7 / var6);
    BodyTexture var9 = DeadBodyAtlas.instance.getBodyTexture(this.isFemale(), var4, var5, this.getDir(), var7, var8);
      if (var9 != nullptr) {
    float var10 = IsoUtils.XToScreen(var1, var2, this.getZ(), 0);
    float var11 = IsoUtils.YToScreen(var1, var2, this.getZ(), 0);
         var10 -= IsoCamera.getOffX();
         var11 -= IsoCamera.getOffY();
    int var12 = IsoCamera.frameState.playerIndex;
         var9.render(var10, var11, 0.0F, 0.0F, 0.0F, this.getAlpha(var12));
      }

      if (DebugOptions.instance.char.Debug.Render.Angle.getValue()) {
         tempo.set(this.dir.ToVector());
         this.drawDirectionLine(tempo, 1.2F, 0.0F, 1.0F, 0.0F);
      }

    return true;
   }

    void renderTextureOverHead(const std::string& var1) {
    float var2 = this.x;
    float var3 = this.y;
    float var4 = IsoUtils.XToScreen(var2, var3, this.getZ(), 0);
    float var5 = IsoUtils.YToScreen(var2, var3, this.getZ(), 0);
      var4 = var4 - IsoCamera.getOffX() - this.offsetX;
      var5 = var5 - IsoCamera.getOffY() - this.offsetY;
      var5 -= 128 / (2 / Core.TileScale);
    Texture var6 = Texture.getSharedTexture(var1);
    float var7 = Core.getInstance().getZoom(IsoCamera.frameState.playerIndex);
      var7 = Math.max(var7, 1.0F);
    int var8 = (int)(var6.getWidth() * var7);
    int var9 = (int)(var6.getHeight() * var7);
      var6.render((int)var4 - var8 / 2, (int)var5 - var9, var8, var9);
   }

    void updateAlpha(int var1, float var2, float var3) {
      if (this.isFakeDead()) {
         this.setAlphaAndTarget(1.0F);
      } else {
         super.updateAlpha(var1, var2, var3);
      }
   }

    void RespondToSound() {
      if (!this.Ghost) {
         if (!this.isUseless()) {
            if (!GameServer.bServer) {
               if (!GameClient.bClient || !this.isRemoteZombie()) {
                  if ((this.getCurrentState() == PathFindState.instance() || this.getCurrentState() == WalkTowardState.instance())
                     && this.getPathFindBehavior2().isGoalSound()
                     && (int)this.z == this.getPathTargetZ()
                     && this.bSoundSourceRepeating) {
    float var1 = this.DistToSquared(this.getPathTargetX(), this.getPathTargetY());
                     if (var1 < 25.0F
                        && LosUtil.lineClear(
                              this.getCell(), (int)this.x, (int)this.y, (int)this.z, this.getPathTargetX(), this.getPathTargetY(), (int)this.z, false
                           )
                           != TestResults.Blocked) {
                        this.setVariable("bPathfind", false);
                        this.setVariable("bMoving", false);
                        this.setPath2(nullptr);
                     }
                  }

                  if (this.soundReactDelay > 0.0F) {
                     this.soundReactDelay = this.soundReactDelay - GameTime.getInstance().getMultiplier() / 1.6F;
                     if (this.soundReactDelay < 0.0F) {
                        this.soundReactDelay = 0.0F;
                     }

                     if (this.soundReactDelay > 0.0F) {
                        return;
                     }
                  }

    float var10 = 0.0F;
    void* var2 = nullptr;
    WorldSound var3 = WorldSoundManager.instance.getSoundZomb(this);
    float var4 = WorldSoundManager.instance.getSoundAttract(var3, this);
                  if (var4 <= 0.0F) {
                     var3 = nullptr;
                  }

                  if (var3 != nullptr) {
                     var10 = var4;
                     var2 = var3.source;
                     this.soundAttract = var4;
                     this.soundAttractTimeout = 60.0F;
                  } else if (this.soundAttractTimeout > 0.0F) {
                     this.soundAttractTimeout = this.soundAttractTimeout - GameTime.getInstance().getMultiplier() / 1.6F;
                     if (this.soundAttractTimeout < 0.0F) {
                        this.soundAttractTimeout = 0.0F;
                     }
                  }

    ResultBiggestSound var5 = WorldSoundManager.instance.getBiggestSoundZomb((int)this.getX(), (int)this.getY(), (int)this.getZ(), true, this);
                  if (var5.sound != nullptr && (this.soundAttractTimeout == 0.0F || this.soundAttract * 2.0F < var5.attract)) {
                     var3 = var5.sound;
                     var10 = var5.attract;
                     var2 = var3.source;
                  }

                  if (var3 != nullptr && var3.bRepeating && var3.z == (int)this.z) {
    float var6 = this.DistToSquared(var3.x, var3.y);
                     if (var6 < 25.0F
                        && LosUtil.lineClear(this.getCell(), (int)this.x, (int)this.y, (int)this.z, var3.x, var3.y, (int)this.z, false) != TestResults.Blocked) {
                        var3 = nullptr;
                     }
                  }

                  if (var3 != nullptr) {
                     this.soundAttract = var10;
                     this.soundSourceTarget = var2;
                     this.soundReactDelay = Rand.Next(0, 16);
                     this.delayedSound.x = var3.x;
                     this.delayedSound.y = var3.y;
                     this.delayedSound.z = var3.z;
                     this.bSoundSourceRepeating = var3.bRepeating;
                  }

                  if (this.delayedSound.x != -1 && this.soundReactDelay == 0.0F) {
    int var11 = this.delayedSound.x;
    int var7 = this.delayedSound.y;
    int var8 = this.delayedSound.z;
                     this.delayedSound.x = -1;
    float var9 = IsoUtils.DistanceManhatten(this.getX(), this.getY(), var11, var7) / 2.5F;
                     var11 += Rand.Next((int)(-var9), (int)var9);
                     var7 += Rand.Next((int)(-var9), (int)var9);
                     if ((this.getCurrentState() == PathFindState.instance() || this.getCurrentState() == WalkTowardState.instance())
                        && (this.getPathFindBehavior2().isGoalLocation() || this.getPathFindBehavior2().isGoalSound())) {
                        if (!IsoUtils.isSimilarDirection(
                           this, var11, var7, this.getPathFindBehavior2().getTargetX(), this.getPathFindBehavior2().getTargetY(), 0.5F
                        )) {
                           this.setTurnAlertedValues(var11, var7);
                           this.pathToSound(var11, var7, var8);
                           this.setLastHeardSound(this.getPathTargetX(), this.getPathTargetY(), this.getPathTargetZ());
                           this.AllowRepathDelay = 120.0F;
                           this.timeSinceRespondToSound = 0.0F;
                        }

                        return;
                     }

                     if (this.timeSinceRespondToSound < 60.0F) {
                        return;
                     }

                     if (!IsoUtils.isSimilarDirection(this, var11, var7, this.x + this.getForwardDirection().x, this.y + this.getForwardDirection().y, 0.5F)) {
                        this.setTurnAlertedValues(var11, var7);
                     }

                     this.pathToSound(var11, var7, var8);
                     this.setLastHeardSound(this.getPathTargetX(), this.getPathTargetY(), this.getPathTargetZ());
                     this.AllowRepathDelay = 120.0F;
                     this.timeSinceRespondToSound = 0.0F;
                  }
               }
            }
         }
      }
   }

    void setTurnAlertedValues(int var1, int var2) {
    Vector2 var3 = std::make_shared<Vector2>(this.getX() - (var1 + 0.5F), this.getY() - (var2 + 0.5F));
    float var4 = var3.getDirectionNeg();
      if (var4 < 0.0F) {
         var4 = Math.abs(var4);
      } else {
         var4 = std::make_shared<float>((Math.PI * 2) - var4);
      }

    double var5 = std::make_shared<double>(Math.toDegrees(var4));
    Vector2 var7 = std::make_shared<Vector2>(IsoDirections.reverse(this.getDir()).ToVector().x, IsoDirections.reverse(this.getDir()).ToVector().y);
      var7.normalize();
    float var8 = var7.getDirectionNeg();
      if (var8 < 0.0F) {
         var8 = Math.abs(var8);
      } else {
         var8 = (float) (Math.PI * 2) - var8;
      }

    double var9 = Math.toDegrees(var8);
      if ((int)var9 == 360) {
         var9 = 0.0;
      }

      if ((int)var5 == 360) {
         var5 = 0.0;
      }

    std::string var11 = "0";
    int var12 = 0;
      if (var5 > var9) {
         var12 = (int)(var5 - var9);
         if (var12 > 350 || var12 <= 35) {
            var11 = "45R";
         }

         if (var12 > 35 && var12 <= 80) {
            var11 = "90R";
         }

         if (var12 > 80 && var12 <= 125) {
            var11 = "135R";
         }

         if (var12 > 125 && var12 <= 170) {
            var11 = "180R";
         }

         if (var12 > 170 && var12 < 215) {
            var11 = "180L";
         }

         if (var12 >= 215 && var12 < 260) {
            var11 = "135L";
         }

         if (var12 >= 260 && var12 < 305) {
            var11 = "90L";
         }

         if (var12 >= 305 && var12 < 350) {
            var11 = "45L";
         }
      } else {
         var12 = (int)(var9 - var5);
         if (var12 > 10 && var12 <= 55) {
            var11 = "45L";
         }

         if (var12 > 55 && var12 <= 100) {
            var11 = "90L";
         }

         if (var12 > 100 && var12 <= 145) {
            var11 = "135L";
         }

         if (var12 > 145 && var12 <= 190) {
            var11 = "180L";
         }

         if (var12 > 190 && var12 < 235) {
            var11 = "180R";
         }

         if (var12 >= 235 && var12 < 280) {
            var11 = "135R";
         }

         if (var12 >= 280 && var12 < 325) {
            var11 = "90R";
         }

         if (var12 >= 325 || var12 < 10) {
            var11 = "45R";
         }
      }

      this.setVariable("turnalertedvalue", var11);
      ZombieTurnAlerted.instance().setParams(this, var3.set(var1 + 0.5F - this.x, var2 + 0.5F - this.y).getDirection());
      this.alerted = true;
      this.networkAI.extraUpdate();
   }

    void clearAggroList() {
      try {
         Arrays.fill(this.aggroList, nullptr);
      } catch (Exception var2) {
      }
   }

    void processAggroList() {
      try {
         for (int var1 = 0; var1 < this.aggroList.length; var1++) {
            if (this.aggroList[var1] != nullptr && this.aggroList[var1].getAggro() <= 0.0F) {
               this.aggroList[var1] = nullptr;
               return;
            }
         }
      } catch (Exception var2) {
      }
   }

    void addAggro(IsoMovingObject var1, float var2) {
      try {
         if (this.aggroList[0] == nullptr) {
            this.aggroList[0] = std::make_shared<Aggro>(var1, var2);
         } else {
            for (int var3 = 0; var3 < this.aggroList.length; var3++) {
               if (this.aggroList[var3] != nullptr && this.aggroList[var3].obj == var1) {
                  this.aggroList[var3].addDamage(var2);
                  return;
               }
            }

            for (int var5 = 0; var5 < this.aggroList.length; var5++) {
               if (this.aggroList[var5] == nullptr) {
                  this.aggroList[var5] = std::make_shared<Aggro>(var1, var2);
                  return;
               }
            }
         }
      } catch (Exception var4) {
      }
   }

    bool isLeadAggro(IsoMovingObject var1) {
      try {
         if (this.aggroList[0] == nullptr) {
    return false;
         } else {
            this.processAggroList();
            if (this.aggroList[0] == nullptr) {
    return false;
            } else {
    IsoMovingObject var2 = this.aggroList[0].obj;
    float var3 = this.aggroList[0].getAggro();

               for (int var4 = 1; var4 < this.aggroList.length; var4++) {
                  if (this.aggroList[var4] != nullptr) {
                     if (var3 >= 1.0F && this.aggroList[var4].getAggro() >= 1.0F) {
    return false;
                     }

                     if (this.aggroList[var4] != nullptr && var3 < this.aggroList[var4].getAggro()) {
                        var2 = this.aggroList[var4].obj;
                        var3 = this.aggroList[var4].getAggro();
                     }
                  }
               }

    return var1 = = var2 && var3 == 1.0F;
            }
         }
      } catch (Exception var5) {
    return false;
      }
   }

    void spotted(IsoMovingObject var1, bool var2) {
      if (GameClient.bClient && this.isRemoteZombie()) {
         if (this.getTarget() != nullptr) {
            this.vectorToTarget.x = this.getTarget().getX();
            this.vectorToTarget.y = this.getTarget().getY();
            this.vectorToTarget.x = this.vectorToTarget.x - this.getX();
            this.vectorToTarget.y = this.vectorToTarget.y - this.getY();
         }
      } else if (this.getCurrentSquare() != nullptr) {
         if (var1.getCurrentSquare() != nullptr) {
            if (this.getCurrentSquare().getProperties().Is(IsoFlagType.smoke) || this.isUseless()) {
               this.setTarget(nullptr);
               this.spottedLast = nullptr;
            } else if (!(dynamic_cast<IsoPlayer*>(var1) != nullptr) || !((IsoPlayer)var1).isGhostMode()) {
    IsoGameCharacter var3 = (IsoGameCharacter)Type.tryCastTo(var1, IsoGameCharacter.class);
               if (var3 != nullptr && !var3.isDead()) {
                  if (this.getCurrentSquare() == nullptr) {
                     this.ensureOnTile();
                  }

                  if (var1.getCurrentSquare() == nullptr) {
                     var1.ensureOnTile();
                  }

    float var4 = 200.0F;
    int var5 = dynamic_cast<IsoPlayer*>(var1) != nullptr && !GameServer.bServer ? ((IsoPlayer)var1).PlayerIndex : 0;
                  float var6 = (
                        var1.getCurrentSquare().lighting[var5].lightInfo().r
                           + var1.getCurrentSquare().lighting[var5].lightInfo().g
                           + var1.getCurrentSquare().lighting[var5].lightInfo().b
                     )
                     / 3.0F;
    float var7 = RenderSettings.getInstance().getAmbientForPlayer(var5);
                  float var8 = (
                        this.getCurrentSquare().lighting[var5].lightInfo().r
                           + this.getCurrentSquare().lighting[var5].lightInfo().g
                           + this.getCurrentSquare().lighting[var5].lightInfo().b
                     )
                     / 3.0F;
                  var8 = var8 * var8 * var8;
                  if (var6 > 1.0F) {
                     var6 = 1.0F;
                  }

                  if (var6 < 0.0F) {
                     var6 = 0.0F;
                  }

                  if (var8 > 1.0F) {
                     var8 = 1.0F;
                  }

                  if (var8 < 0.0F) {
                     var8 = 0.0F;
                  }

    float var9 = 1.0F - (var6 - var8);
                  if (var6 < 0.2F) {
                     var6 = 0.2F;
                  }

                  if (var7 < 0.2F) {
                     var7 = 0.2F;
                  }

                  if (var1.getCurrentSquare().getRoom() != this.getCurrentSquare().getRoom()) {
                     var4 = 50.0F;
                     if (var1.getCurrentSquare().getRoom() != nullptr && this.getCurrentSquare().getRoom() == nullptr
                        || var1.getCurrentSquare().getRoom() == nullptr && this.getCurrentSquare().getRoom() != nullptr) {
                        var4 = 20.0F;
                        if (!var3.isAiming() && !var3.isSneaking()) {
                           if (var1.getMovementLastFrame().getLength() <= 0.04F && var6 < 0.4F) {
                              var4 = 10.0F;
                           }
                        } else if (var6 < 0.4F) {
                           var4 = 0.0F;
                        } else {
                           var4 = 10.0F;
                        }
                     }
                  }

                  tempo.x = var1.getX();
                  tempo.y = var1.getY();
                  tempo.x = tempo.x - this.getX();
                  tempo.y = tempo.y - this.getY();
                  if (var1.getCurrentSquare().getZ() != this.current.getZ()) {
    int var10 = Math.abs(var1.getCurrentSquare().getZ() - this.current.getZ()) * 5;
                     var10++;
                     var4 /= var10;
                  }

    float var44 = GameTime.getInstance().getViewDist();
                  if (!(tempo.getLength() > var44)) {
                     if (GameServer.bServer) {
                        this.bIndoorZombie = false;
                     }

                     if (tempo.getLength() < var44) {
                        var44 = tempo.getLength();
                     }

                     var44 *= 1.1F;
                     if (var44 > GameTime.getInstance().getViewDistMax()) {
                        var44 = GameTime.getInstance().getViewDistMax();
                     }

                     tempo.normalize();
    Vector2 var11 = this.getLookVector(tempo2);
    float var12 = var11.dot(tempo);
                     if (this.DistTo(var1) > 20.0F) {
                        var4 -= 10000.0F;
                     }

                     if (var44 > 0.5) {
                        if (var12 < -0.4F) {
                           var4 = 0.0F;
                        } else if (var12 < -0.2F) {
                           var4 /= 8.0F;
                        } else if (var12 < -0.0F) {
                           var4 /= 4.0F;
                        } else if (var12 < 0.2F) {
                           var4 /= 2.0F;
                        } else if (var12 <= 0.4F) {
                           var4 *= 2.0F;
                        } else if (var12 > 0.4F) {
                           var4 *= 8.0F;
                        } else if (var12 > 0.6F) {
                           var4 *= 16.0F;
                        } else if (var12 > 0.8F) {
                           var4 *= 32.0F;
                        }
                     }

                     if (var4 > 0.0F
                        && this.dynamic_cast<IsoPlayer*>(target) != nullptr var13
                        && !GameServer.bServer
                        && var13.RemoteID == -1
                        && this.current.isCanSee(var13.PlayerIndex)) {
                        ((IsoPlayer)this.target).targetedByZombie = true;
                        ((IsoPlayer)this.target).lastTargeted = 0.0F;
                     }

                     var4 *= var9;
    int var46 = (int)var1.getZ() - (int)this.getZ();
                     if (var46 >= 1) {
                        var4 /= var46 * 3;
                     }

    float var14 = PZMath.clamp(var44 / GameTime.getInstance().getViewDist(), 0.0F, 1.0F);
                     var4 *= 1.0F - var14;
                     var4 *= 1.0F - var14;
                     var4 *= 1.0F - var14;
    float var15 = PZMath.clamp(var44 / 10.0F, 0.0F, 1.0F);
                     var4 *= 1.0F + (1.0F - var15) * 10.0F;
    float var16 = var1.getMovementLastFrame().getLength();
                     if (var16 == 0.0F && var6 <= 0.2F) {
                        var6 = 0.0F;
                     }

                     if (var3 != nullptr) {
                        if (var3.getTorchStrength() > 0.0F) {
                           var4 *= 3.0F;
                        }

                        if (var16 < 0.01F) {
                           var4 *= 0.5F;
                        } else if (var3.isSneaking()) {
                           var4 *= 0.4F;
                        } else if (var3.isAiming()) {
                           var4 *= 0.75F;
                        } else if (var16 < 0.06F) {
                           var4 *= 0.8F;
                        } else if (var16 >= 0.06F) {
                           var4 *= 2.4F;
                        }

                        if (this.eatBodyTarget != nullptr) {
                           var4 *= 0.6F;
                        }

                        if (var44 < 5.0F && (!var3.isRunning() && !var3.isSneaking() && !var3.isAiming() || var3.isRunning())) {
                           var4 *= 3.0F;
                        }

                        if (this.spottedLast == var1 && this.TimeSinceSeenFlesh < 120.0F) {
                           var4 = 1000.0F;
                        }

                        var4 *= var3.getSneakSpotMod();
                        var4 *= var7;
                        if (this.target != var1 && this.target != nullptr) {
    float var17 = IsoUtils.DistanceManhatten(this.getX(), this.getY(), var1.getX(), var1.getY());
    float var18 = IsoUtils.DistanceManhatten(this.getX(), this.getY(), this.target.getX(), this.target.getY());
                           if (var17 > var18) {
                              return;
                           }
                        }

                        var4 *= 0.3F;
                        if (var2) {
                           var4 = 1000000.0F;
                        }

                        if (this.BonusSpotTime > 0.0F) {
                           var4 = 1000000.0F;
                        }

                        var4 *= 1.2F;
                        if (this.sight == 1) {
                           var4 *= 2.5F;
                        }

                        if (this.sight == 3) {
                           var4 *= 0.45F;
                        }

                        if (this.inactive) {
                           var4 *= 0.25F;
                        }

                        var4 *= 0.25F;
                        if (dynamic_cast<IsoPlayer*>(var1) != nullptr && ((IsoPlayer)var1).Traits.Inconspicuous.isSet()) {
                           var4 *= 0.5F;
                        }

                        if (dynamic_cast<IsoPlayer*>(var1) != nullptr && ((IsoPlayer)var1).Traits.Conspicuous.isSet()) {
                           var4 *= 2.0F;
                        }

                        var4 *= 1.6F;
    void* var47 = nullptr;
    IsoGridSquare var49 = nullptr;
                        if (this.getCurrentSquare() != var1.getCurrentSquare() && dynamic_cast<IsoPlayer*>(var1) != nullptr && ((IsoPlayer)var1).isSneaking()) {
    int var19 = Math.abs(this.getCurrentSquare().getX() - var1.getCurrentSquare().getX());
    int var20 = Math.abs(this.getCurrentSquare().getY() - var1.getCurrentSquare().getY());
                           if (var19 > var20) {
                              if (this.getCurrentSquare().getX() - var1.getCurrentSquare().getX() > 0) {
                                 var47 = var1.getCurrentSquare().nav[IsoDirections.E.index()];
                              } else {
                                 var47 = var1.getCurrentSquare();
                                 var49 = var1.getCurrentSquare().nav[IsoDirections.W.index()];
                              }
                           } else if (this.getCurrentSquare().getY() - var1.getCurrentSquare().getY() > 0) {
                              var47 = var1.getCurrentSquare().nav[IsoDirections.S.index()];
                           } else {
                              var47 = var1.getCurrentSquare();
                              var49 = var1.getCurrentSquare().nav[IsoDirections.N.index()];
                           }

                           if (var47 != nullptr && dynamic_cast<IsoGameCharacter*>(var1) != nullptr) {
    float var21 = ((IsoGameCharacter)var1).checkIsNearWall();
                              if (var21 == 1.0F && var49 != nullptr) {
                                 var21 = var49.getGridSneakModifier(true);
                              }

                              if (var21 > 1.0F) {
    float var22 = var1.DistTo(((IsoGridSquare)var47).x, ((IsoGridSquare)var47).y);
                                 if (var22 > 1.0F) {
                                    var21 /= var22;
                                 }

                                 var4 /= var21;
                              }
                           }
                        }

                        var4 = (float)Math.floor(var4);
    bool var50 = false;
                        var4 = Math.min(var4, 400.0F);
                        var4 /= 400.0F;
                        var4 = Math.max(0.0F, var4);
                        var4 = Math.min(1.0F, var4);
    float var51 = GameTime.instance.getMultiplier();
                        var4 = (float)(1.0 - Math.pow(1.0F - var4, var51));
                        var4 *= 100.0F;
                        if (Rand.Next(10000) / 100.0F < var4) {
                           var50 = true;
                        }

                        if (!GameClient.bClient && !GameServer.bServer || NetworkZombieManager.canSpotted(this) || var1 == this.target) {
                           if (!var50) {
                              if (var4 > 20.0F && dynamic_cast<IsoPlayer*>(var1) != nullptr && var44 < 15.0F) {
                                 ((IsoPlayer)var1).bCouldBeSeenThisFrame = true;
                              }

                              if (!((IsoPlayer)var1).isbCouldBeSeenThisFrame()
                                 && !((IsoPlayer)var1).isbSeenThisFrame()
                                 && ((IsoPlayer)var1).isSneaking()
                                 && ((IsoPlayer)var1).isJustMoved()
                                 && Rand.Next((int)(1100.0F * GameTime.instance.getInvMultiplier())) == 0) {
                                 if (GameServer.bServer) {
                                    GameServer.addXp((IsoPlayer)var1, Perks.Sneak, 1);
                                 } else {
                                    ((IsoPlayer)var1).getXp().AddXP(Perks.Sneak, 1.0F);
                                 }
                              }

                              if (!((IsoPlayer)var1).isbCouldBeSeenThisFrame()
                                 && !((IsoPlayer)var1).isbSeenThisFrame()
                                 && ((IsoPlayer)var1).isSneaking()
                                 && ((IsoPlayer)var1).isJustMoved()
                                 && Rand.Next((int)(1100.0F * GameTime.instance.getInvMultiplier())) == 0) {
                                 if (GameServer.bServer) {
                                    GameServer.addXp((IsoPlayer)var1, Perks.Lightfoot, 1);
                                 } else {
                                    ((IsoPlayer)var1).getXp().AddXP(Perks.Lightfoot, 1.0F);
                                 }
                              }
                           } else {
                              if (dynamic_cast<IsoPlayer*>(var1) != nullptr) {
                                 ((IsoPlayer)var1).setbSeenThisFrame(true);
                              }

                              if (!var2) {
                                 this.BonusSpotTime = 120.0F;
                              }

                              this.LastTargetSeenX = (int)var1.getX();
                              this.LastTargetSeenY = (int)var1.getY();
                              this.LastTargetSeenZ = (int)var1.getZ();
                              if (this.stateMachine.getCurrent() != StaggerBackState.instance()) {
                                 if (this.target != var1) {
                                    this.targetSeenTime = 0.0F;
                                    if (GameServer.bServer && !this.isRemoteZombie()) {
                                       this.addAggro(var1, 1.0F);
                                    }
                                 }

                                 this.setTarget(var1);
                                 this.vectorToTarget.x = var1.getX();
                                 this.vectorToTarget.y = var1.getY();
                                 this.vectorToTarget.x = this.vectorToTarget.x - this.getX();
                                 this.vectorToTarget.y = this.vectorToTarget.y - this.getY();
    float var52 = this.vectorToTarget.getLength();
                                 if (!var2) {
                                    this.TimeSinceSeenFlesh = 0.0F;
                                    this.targetSeenTime = this.targetSeenTime + GameTime.getInstance().getRealworldSecondsSinceLastUpdate();
                                 }

                                 if (this.target != this.spottedLast || this.getCurrentState() != LungeState.instance() || !(this.LungeTimer > 0.0F)) {
                                    if (this.target != this.spottedLast || this.getCurrentState() != AttackVehicleState.instance()) {
                                       if ((int)this.getZ() == (int)this.target.getZ()
                                          && (
                                             var52 <= 3.5F
                                                || this.dynamic_cast<IsoGameCharacter*>(target) != nullptr
                                                   && ((IsoGameCharacter)this.target).getVehicle() != nullptr
                                                   && var52 <= 4.0F
                                          )
                                          && this.getStateEventDelayTimer() <= 0.0F
                                          && !PolygonalMap2.instance.lineClearCollide(this.getX(), this.getY(), var1.x, var1.y, (int)this.getZ(), var1)) {
                                          this.setTarget(var1);
                                          if (this.getCurrentState() == LungeState.instance()) {
                                             return;
                                          }
                                       }

                                       this.spottedLast = var1;
                                       if (!this.Ghost && !this.getCurrentSquare().getProperties().Is(IsoFlagType.smoke)) {
                                          this.setTarget(var1);
                                          if (this.AllowRepathDelay > 0.0F) {
                                             return;
                                          }

                                          if (this.dynamic_cast<IsoGameCharacter*>(target) != nullptr && ((IsoGameCharacter)this.target).getVehicle() != nullptr) {
                                             if ((this.getCurrentState() == PathFindState.instance() || this.getCurrentState() == WalkTowardState.instance())
                                                && this.getPathFindBehavior2().getTargetChar() == this.target) {
                                                return;
                                             }

                                             if (this.getCurrentState() == AttackVehicleState.instance()) {
                                                return;
                                             }

    BaseVehicle var53 = ((IsoGameCharacter)this.target).getVehicle();
                                             if (Math.abs(var53.getCurrentSpeedKmHour()) > 0.8F && this.DistToSquared(var53) <= 16.0F) {
                                                return;
                                             }

                                             this.pathToCharacter((IsoGameCharacter)this.target);
                                             this.AllowRepathDelay = 10.0F;
                                             return;
                                          }

                                          this.pathToCharacter(var3);
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

    void Move(Vector2 var1) {
      if (!GameClient.bClient || this.authOwner != nullptr) {
         this.nx = this.nx + var1.x * GameTime.instance.getMultiplier();
         this.ny = this.ny + var1.y * GameTime.instance.getMultiplier();
         this.movex = var1.x;
         this.movey = var1.y;
      }
   }

    void MoveUnmodded(Vector2 var1) {
      if (this.speedType == 1
         && (
            this.isCurrentState(LungeState.instance())
               || this.isCurrentState(LungeNetworkState.instance())
               || this.isCurrentState(AttackState.instance())
               || this.isCurrentState(AttackNetworkState.instance())
               || this.isCurrentState(StaggerBackState.instance())
               || this.isCurrentState(ZombieHitReactionState.instance())
         )
         && this.dynamic_cast<IsoGameCharacter*>(target) != nullptr) {
    float var2 = this.target.nx - this.x;
    float var3 = this.target.ny - this.y;
    float var4 = (float)Math.sqrt(var2 * var2 + var3 * var3);
         var4 -= this.getWidth() + this.target.getWidth() - 0.1F;
         var4 = Math.max(0.0F, var4);
         if (var1.getLength() > var4) {
            var1.setLength(var4);
         }
      }

      if (this.isRemoteZombie()) {
    float var6 = IsoUtils.DistanceTo(this.realx, this.realy, this.networkAI.targetX, this.networkAI.targetY);
         if (var6 > 1.0F) {
    Vector2 var7 = std::make_shared<Vector2>(this.realx - this.x, this.realy - this.y);
            var7.normalize();
    float var10 = 0.5F + IsoUtils.smoothstep(0.5F, 1.5F, IsoUtils.DistanceTo(this.x, this.y, this.networkAI.targetX, this.networkAI.targetY) / var6);
    float var5 = var1.getLength();
            var1.normalize();
            PZMath.lerp(var1, var1, var7, 0.5F);
            var1.setLength(var5 * var10);
         }
      }

      super.MoveUnmodded(var1);
   }

    bool canBeDeletedUnnoticed(float var1) {
      if (!GameClient.bClient) {
    return false;
      } else {
    float var2 = float.POSITIVE_INFINITY;
    std::vector var3 = GameClient.instance.getPlayers();

         for (int var4 = 0; var4 < var3.size(); var4++) {
    IsoPlayer var5 = (IsoPlayer)var3.get(var4);
    float var6 = var5.getDotWithForwardDirection(this.getX(), this.getY());
    float var7 = LightingJNI.calculateVisionCone(var5) + 0.2F;
            if (var6 > -var7) {
    return false;
            }

    float var8 = IsoUtils.DistanceToSquared(this.x, this.y, var5.x, var5.y);
            if (var8 < var2) {
               var2 = var8;
            }
         }

         return var2 > var1 * var1;
      }
   }

    void DoFootstepSound(const std::string& var1) {
    MovementType var2 = MovementType.Walk;
    float var3 = 0.5F;
      switch (var1) {
         case "sneak_walk":
            var3 = 0.25F;
            var2 = MovementType.SneakWalk;
            break;
         case "sneak_run":
            var3 = 0.25F;
            var2 = MovementType.SneakRun;
            break;
         case "strafe":
            var3 = 0.5F;
            var2 = MovementType.Strafe;
            break;
         case "walk":
            var3 = 0.5F;
            var2 = MovementType.Walk;
            break;
         case "run":
            var3 = 0.75F;
            var2 = MovementType.Run;
            break;
         case "sprint":
            var3 = 1.0F;
            var2 = MovementType.Sprint;
      }

      if (!GameServer.bServer && !this.getFMODParameters().parameterList.contains(this.parameterCharacterMovementSpeed)) {
         this.getFMODParameters().push_back(this.parameterCharacterMovementSpeed);
         this.getFMODParameters().push_back(this.parameterFootstepMaterial);
         this.getFMODParameters().push_back(this.parameterFootstepMaterial2);
         this.getFMODParameters().push_back(this.parameterShoeType);
      }

      this.parameterCharacterMovementSpeed.setMovementType(var2);
      this.DoFootstepSound(var3);
   }

    void DoFootstepSound(float var1) {
      if (!GameServer.bServer) {
         if (!(var1 <= 0.0F)) {
            if (this.getCurrentSquare() != nullptr) {
               if (GameClient.bClient && this.authOwner == nullptr) {
                  if (this.def != nullptr
                     && this.sprite != nullptr
                     && this.sprite.CurrentAnim != nullptr
                     && (this.sprite.CurrentAnim.name.contains("Run") || this.sprite.CurrentAnim.name.contains("Walk"))) {
    int var6 = (int)this.def.Frame;
    bool var3;
                     if (var6 >= 0 && var6 < 5) {
                        var3 = this.stepFrameLast < 0 || this.stepFrameLast > 5;
                     } else {
                        var3 = this.stepFrameLast < 5;
                     }

                     if (var3) {
                        for (int var4 = 0; var4 < IsoPlayer.numPlayers; var4++) {
    IsoPlayer var5 = IsoPlayer.players[var4];
                           if (var5 != nullptr && var5.DistToSquared(this) < 225.0F) {
                              ZombieFootstepManager.instance.addCharacter(this);
                              break;
                           }
                        }
                     }

                     this.stepFrameLast = var6;
                  } else {
                     this.stepFrameLast = -1;
                  }
               } else {
    bool var2 = SoundManager.instance.isListenerInRange(this.getX(), this.getY(), 15.0F);
                  if (var2) {
                     this.footstepVolume = var1;
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
    HitReactionNetworkAI var1 = this.getHitReactionNetworkAI();
            if (var1.isSetup() && !var1.isStarted()) {
               var1.start();
            }
         }
      }

      super.preupdate();
   }

    void postupdate() {
      s_performance.postUpdate.invokeAndMeasure(this, IsoZombie::postUpdateInternal);
   }

    void postUpdateInternal() {
      if (this.dynamic_cast<IsoPlayer*>(target) != nullptr) {
         ((IsoPlayer)this.target).getStats().NumChasingZombies++;
      }

      super.postupdate();
      if (this.current == nullptr && (!GameClient.bClient || this.authOwner != nullptr)) {
         this.removeFromWorld();
         this.removeFromSquare();
      }

      if (!GameServer.bServer) {
    IsoPlayer var1 = this.getReanimatedPlayer();
         if (var1 != nullptr) {
            var1.setX(this.getX());
            var1.setY(this.getY());
            var1.setZ(this.getZ());
            var1.setDir(this.getDir());
            var1.setForwardDirection(this.getForwardDirection());
    AnimationPlayer var2 = this.getAnimationPlayer();
    AnimationPlayer var3 = var1.getAnimationPlayer();
            if (var2 != nullptr && var2.isReady() && var3 != nullptr && var3.isReady()) {
               var3.setTargetAngle(var2.getAngle());
               var3.setAngleToTarget();
            }

            var1.setCurrent(this.getCell().getGridSquare((int)var1.x, (int)var1.y, (int)var1.z));
            var1.updateLightInfo();
            if (var1.soundListener != nullptr) {
               var1.soundListener.setPos(var1.getX(), var1.getY(), var1.getZ());
               var1.soundListener.tick();
            }

    IsoPlayer var4 = IsoPlayer.getInstance();
            IsoPlayer.setInstance(var1);
            var1.updateLOS();
            IsoPlayer.setInstance(var4);
            if (GameClient.bClient && this.authOwner == nullptr && this.networkUpdate.Check()) {
               GameClient.instance.sendPlayer(var1);
            }

            var1.dirtyRecalcGridStackTime = 2.0F;
         }
      }

      if (this.targetSeenTime > 0.0F && !this.isTargetVisible()) {
         this.targetSeenTime = 0.0F;
      }
   }

    bool isSolidForSeparate() {
      if (this.getCurrentState() != FakeDeadZombieState.instance()
         && this.getCurrentState() != ZombieFallDownState.instance()
         && this.getCurrentState() != ZombieOnGroundState.instance()
         && this.getCurrentState() != ZombieGetUpState.instance()
         && (this.getCurrentState() != ZombieHitReactionState.instance() || this.speedType == 1)) {
         return this.isSitAgainstWall() ? false : super.isSolidForSeparate();
      } else {
    return false;
      }
   }

    bool isPushableForSeparate() {
      if (this.getCurrentState() == ThumpState.instance()
         || this.getCurrentState() == AttackState.instance()
         || this.getCurrentState() == AttackVehicleState.instance()
         || this.getCurrentState() == ZombieEatBodyState.instance()
         || this.getCurrentState() == ZombieFaceTargetState.instance()) {
    return false;
      } else {
         return this.isSitAgainstWall() ? false : super.isPushableForSeparate();
      }
   }

    bool isPushedByForSeparate(IsoMovingObject var1) {
      if (dynamic_cast<IsoZombie*>(var1) != nullptr && ((IsoZombie)var1).getCurrentState() == ZombieHitReactionState.instance() && !((IsoZombie)var1).collideWhileHit) {
    return false;
      } else if (this.getCurrentState() == ZombieHitReactionState.instance() && !this.collideWhileHit) {
    return false;
      } else {
         return GameClient.bClient && dynamic_cast<IsoZombie*>(var1) != nullptr && !NetworkZombieSimulator.getInstance().isZombieSimulated(this.getOnlineID())
            ? false
            : super.isPushedByForSeparate(var1);
      }
   }

    void update() {
      s_performance.update.invokeAndMeasure(this, IsoZombie::updateInternal);
   }

    void updateInternal() {
      if (GameClient.bClient && !this.isRemoteZombie()) {
         ZombieCountOptimiser.incrementZombie(this);
         MPStatistics.clientZombieUpdated();
      } else if (GameServer.bServer) {
         MPStatistics.serverZombieUpdated();
      }

      if (SandboxOptions.instance.Lore.ActiveOnly.getValue() > 1) {
         if ((SandboxOptions.instance.Lore.ActiveOnly.getValue() != 2 || GameTime.instance.getHour() < 20 && GameTime.instance.getHour() > 8)
            && (SandboxOptions.instance.Lore.ActiveOnly.getValue() != 3 || GameTime.instance.getHour() <= 8 || GameTime.instance.getHour() >= 20)) {
            this.makeInactive(true);
         } else {
            this.makeInactive(false);
         }
      }

      if (this.bCrawling) {
         if (this.actionContext.getGroup() != ActionGroup.getActionGroup("zombie-crawler")) {
            this.advancedAnimator.OnAnimDataChanged(false);
            this.initializeStates();
            this.actionContext.setGroup(ActionGroup.getActionGroup("zombie-crawler"));
         }
      } else if (this.actionContext.getGroup() != ActionGroup.getActionGroup("zombie")) {
         this.advancedAnimator.OnAnimDataChanged(false);
         this.initializeStates();
         this.actionContext.setGroup(ActionGroup.getActionGroup("zombie"));
      }

      if (this.getThumpTimer() > 0) {
         this.thumpTimer--;
      }

    BaseVehicle var1 = this.getNearVehicle();
      if (var1 != nullptr) {
         if (this.target == nullptr && var1.hasLightbar() && var1.lightbarSirenMode.get() > 0) {
    VehiclePart var2 = var1.getUseablePart(this, false);
            if (var2 != nullptr && var2.getSquare().DistTo(this) < 0.7F) {
               this.setThumpTarget(var1);
            }
         }

         if (var1.isAlarmed() && !var1.isPreviouslyEntered() && Rand.Next(10000) < 1) {
            var1.triggerAlarm();
         }
      }

      this.doDeferredMovement();
      this.updateEmitter();
      if (this.spotSoundDelay > 0) {
         this.spotSoundDelay--;
      }

      if (GameClient.bClient && this.authOwner == nullptr) {
         if (this.lastRemoteUpdate > 800
            && (
               this.legsSprite.CurrentAnim.name == "ZombieDeath")
                  || this.legsSprite.CurrentAnim.name == "ZombieStaggerBack")
                  || this.legsSprite.CurrentAnim.name == "ZombieGetUp")
            )) {
            DebugLog.log(DebugType.Zombie, "removing stale zombie 800 id=" + this.OnlineID);
            VirtualZombieManager.instance.removeZombieFromWorld(this);
            return;
         }

         if (GameClient.bFastForward) {
            VirtualZombieManager.instance.removeZombieFromWorld(this);
            return;
         }
      }

      if (GameClient.bClient
         && this.authOwner == nullptr
         && this.lastRemoteUpdate < 2000
         && this.lastRemoteUpdate + 1000 / PerformanceSettings.getLockFPS() > 2000) {
         DebugLog.log(DebugType.Zombie, "lastRemoteUpdate 2000+ id=" + this.OnlineID);
      }

      this.lastRemoteUpdate = (short)(this.lastRemoteUpdate + 1000 / PerformanceSettings.getLockFPS());
      if (!GameClient.bClient || this.authOwner != nullptr || this.bRemote && this.lastRemoteUpdate <= 5000) {
         this.sprite = this.legsSprite;
         if (this.sprite != nullptr) {
            this.updateCharacterTextureAnimTime();
            if (GameServer.bServer && this.bIndoorZombie) {
               super.update();
            } else {
               this.BonusSpotTime = PZMath.clamp(this.BonusSpotTime - GameTime.instance.getMultiplier(), 0.0F, float.MAX_VALUE);
               this.TimeSinceSeenFlesh = PZMath.clamp(this.TimeSinceSeenFlesh + GameTime.instance.getMultiplier(), 0.0F, float.MAX_VALUE);
               if (this.getStateMachine().getCurrent() != ClimbThroughWindowState.instance()
                  && this.getStateMachine().getCurrent() != ClimbOverFenceState.instance()
                  && this.getStateMachine().getCurrent() != CrawlingZombieTurnState.instance()
                  && this.getStateMachine().getCurrent() != ZombieHitReactionState.instance()
                  && this.getStateMachine().getCurrent() != ZombieFallDownState.instance()) {
                  this.setCollidable(true);
                  LuaEventManager.triggerEvent("OnZombieUpdate", this);
                  if (Core.bLastStand
                     && this.getStateMachine().getCurrent() != ThumpState.instance()
                     && this.getStateMachine().getCurrent() != AttackState.instance()
                     && this.TimeSinceSeenFlesh > 120.0F
                     && Rand.Next(36000) == 0) {
    IsoPlayer var6 = nullptr;
    float var3 = 1000000.0F;

                     for (int var4 = 0; var4 < IsoPlayer.numPlayers; var4++) {
                        if (IsoPlayer.players[var4] != nullptr && IsoPlayer.players[var4].DistTo(this) < var3 && !IsoPlayer.players[var4].isDead()) {
                           var3 = IsoPlayer.players[var4].DistTo(this);
                           var6 = IsoPlayer.players[var4];
                        }
                     }

                     if (var6 != nullptr) {
                        this.AllowRepathDelay = -1.0F;
                        this.pathToCharacter(var6);
                     }
                  } else {
                     if (GameServer.bServer) {
                        this.vehicle4testCollision = nullptr;
                     } else if (GameClient.bClient) {
                        if (this.vehicle4testCollision != nullptr && this.vehicle4testCollision.updateHitByVehicle(this)) {
                           super.update();
                           this.vehicle4testCollision = nullptr;
                           return;
                        }
                     } else if (this.Health > 0.0F && this.vehicle4testCollision != nullptr && this.testCollideWithVehicles(this.vehicle4testCollision)) {
                        this.vehicle4testCollision = nullptr;
                        return;
                     }

                     this.vehicle4testCollision = nullptr;
                     if (this.BonusSpotTime > 0.0F && this.spottedLast != nullptr && !((IsoGameCharacter)this.spottedLast).isDead()) {
                        this.spotted(this.spottedLast, true);
                     }

                     if (GameServer.bServer && this.getStateMachine().getCurrent() == BurntToDeath.instance()) {
                        DebugLog.log(DebugType.Zombie, "Zombie is burning " + this.OnlineID);
                     }

                     super.update();
                     if (VirtualZombieManager.instance.isReused(this)) {
                        DebugLog.log(DebugType.Zombie, "Zombie added to ReusableZombies after super.update - RETURNING " + this);
                     } else if (this.getStateMachine().getCurrent() != ClimbThroughWindowState.instance()
                        && this.getStateMachine().getCurrent() != ClimbOverFenceState.instance()
                        && this.getStateMachine().getCurrent() != CrawlingZombieTurnState.instance()) {
                        this.ensureOnTile();
    State var5 = this.stateMachine.getCurrent();
                        if (var5 != StaggerBackState.instance()
                           && var5 != BurntToDeath.instance()
                           && var5 != FakeDeadZombieState.instance()
                           && var5 != ZombieFallDownState.instance()
                           && var5 != ZombieOnGroundState.instance()
                           && var5 != ZombieHitReactionState.instance()
                           && var5 != ZombieGetUpState.instance()) {
                           if (GameServer.bServer && this.OnlineID == -1) {
                              this.OnlineID = ServerMap.instance.getUniqueZombieId();
                           } else if (var5 == PathFindState.instance() && this.finder.progress == PathFindProgress.notyetfound) {
                              if (this.bCrawling) {
                                 this.PlayAnim("ZombieCrawl");
                                 this.def.AnimFrameIncrease = 0.0F;
                              } else {
                                 this.PlayAnim("ZombieIdle");
                                 this.def.AnimFrameIncrease = 0.08F + Rand.Next(1000) / 8000.0F;
                                 this.def.AnimFrameIncrease *= 0.5F;
                              }
                           } else if (var5 != AttackState.instance() && var5 != AttackVehicleState.instance() && (this.nx != this.x || this.ny != this.y)) {
                              if (this.walkVariantUse == nullptr || var5 != LungeState.instance() && var5 != LungeNetworkState.instance()) {
                                 this.walkVariantUse = this.walkVariant;
                              }

                              if (this.bCrawling) {
                                 this.walkVariantUse = "ZombieCrawl";
                              }

                              if (var5 != ZombieIdleState.instance()
                                 && var5 != StaggerBackState.instance()
                                 && var5 != ThumpState.instance()
                                 && var5 != FakeDeadZombieState.instance()) {
                                 if (this.bRunning) {
                                    this.PlayAnim("Run");
                                    this.def.setFrameSpeedPerFrame(0.33F);
                                 } else {
                                    this.PlayAnim(this.walkVariantUse);
                                    this.def.setFrameSpeedPerFrame(0.26F);
                                    this.def.AnimFrameIncrease = this.def.AnimFrameIncrease * this.speedMod;
                                 }

                                 this.setShootable(true);
                              }
                           }

                           this.shootable = true;
                           this.solid = true;
                           this.tryThump(nullptr);
                           this.damageSheetRope();
                           this.AllowRepathDelay = PZMath.clamp(this.AllowRepathDelay - GameTime.instance.getMultiplier(), 0.0F, float.MAX_VALUE);
                           if (this.TimeSinceSeenFlesh > this.memory && this.target != nullptr) {
                              this.setTarget(nullptr);
                           }

                           if (this.dynamic_cast<IsoGameCharacter*>(target) != nullptr && ((IsoGameCharacter)this.target).ReanimatedCorpse != nullptr) {
                              this.setTarget(nullptr);
                           }

                           if (this.target != nullptr) {
                              this.vectorToTarget.x = this.target.getX();
                              this.vectorToTarget.y = this.target.getY();
                              this.vectorToTarget.x = this.vectorToTarget.x - this.getX();
                              this.vectorToTarget.y = this.vectorToTarget.y - this.getY();
                              this.updateZombieTripping();
                           }

                           if (this.getCurrentState() != PathFindState.instance()
                              && this.getCurrentState() != WalkTowardState.instance()
                              && this.getCurrentState() != ClimbThroughWindowState.instance()) {
                              this.setLastHeardSound(-1, -1, -1);
                           }

                           if (this.TimeSinceSeenFlesh > 240.0F && this.timeSinceRespondToSound > 5.0F) {
                              this.RespondToSound();
                           }

                           this.timeSinceRespondToSound = this.timeSinceRespondToSound + GameTime.getInstance().getMultiplier() / 1.6F;
                           this.separate();
                           this.updateSearchForCorpse();
                           if (this.TimeSinceSeenFlesh > 2000.0F && this.timeSinceRespondToSound > 2000.0F) {
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
         DebugLog.log(DebugType.Zombie, "removing stale zombie 5000 id=" + this.OnlineID);
         DebugLog.log("Zombie: removing stale zombie 5000 id=" + this.OnlineID);
         VirtualZombieManager.instance.removeZombieFromWorld(this);
      }
   }

    void calculateStats() {
   }

    void updateZombieTripping() {
      if (this.speedType == 1 && StringUtils.isNullOrEmpty(this.getBumpType()) && this.target != nullptr && Rand.NextBool(Rand.AdjustForFramerate(750))) {
         this.setBumpType("trippingFromSprint");
      }
   }

    void updateVocalProperties() {
      if (!GameServer.bServer) {
    bool var1 = SoundManager.instance.isListenerInRange(this.getX(), this.getY(), 20.0F);
         if (this.vocalEvent != 0L && !this.getEmitter().isPlaying(this.vocalEvent)) {
            this.vocalEvent = 0L;
         }

         if (!this.isDead() && !this.isFakeDead() && var1) {
            ZombieVocalsManager.instance.addCharacter(this);
         }

         if (this.vocalEvent != 0L && !this.isDead() && this.isFakeDead() && this.getEmitter().isPlaying(this.vocalEvent)) {
            this.getEmitter().stopSoundLocal(this.vocalEvent);
            this.vocalEvent = 0L;
         }
      }
   }

    void setVehicleHitLocation(BaseVehicle var1) {
      if (!this.getFMODParameters().parameterList.contains(this.parameterVehicleHitLocation)) {
         this.getFMODParameters().push_back(this.parameterVehicleHitLocation);
      }

    HitLocation var2 = ParameterVehicleHitLocation.calculateLocation(var1, this.getX(), this.getY(), this.getZ());
      this.parameterVehicleHitLocation.setLocation(var2);
   }

    void updateSearchForCorpse() {
      if (!this.bCrawling && this.target == nullptr && this.eatBodyTarget == nullptr) {
         if (this.bodyToEat != nullptr) {
            if (this.bodyToEat.getStaticMovingObjectIndex() == -1) {
               this.bodyToEat = nullptr;
            } else if (!this.isEatingOther(this.bodyToEat) && this.bodyToEat.getEatingZombies().size() >= 3) {
               this.bodyToEat = nullptr;
            }
         }

         if (this.bodyToEat == nullptr) {
            this.checkForCorpseTimer = this.checkForCorpseTimer - GameTime.getInstance().getMultiplier() / 1.6F;
            if (this.checkForCorpseTimer <= 0.0F) {
               this.checkForCorpseTimer = 10000.0F;
               tempBodies.clear();

               for (int var1 = -10; var1 < 10; var1++) {
                  for (int var2 = -10; var2 < 10; var2++) {
    IsoGridSquare var3 = this.getCell().getGridSquare(this.getX() + var1, this.getY() + var2, this.getZ());
                     if (var3 != nullptr) {
    IsoDeadBody var4 = var3.getDeadBody();
                        if (var4 != nullptr
                           && !var4.isSkeleton()
                           && !var4.isZombie()
                           && var4.getEatingZombies().size() < 3
                           && !PolygonalMap2.instance.lineClearCollide(this.getX(), this.getY(), var4.x, var4.y, (int)this.getZ(), nullptr, false, true)) {
                           tempBodies.push_back(var4);
                        }
                     }
                  }
               }

               if (!tempBodies.empty()) {
                  this.bodyToEat = (IsoDeadBody)PZArrayUtil.pickRandom(tempBodies);
                  tempBodies.clear();
               }
            }
         }

         if (this.bodyToEat != nullptr && this.isCurrentState(ZombieIdleState.instance())) {
            if (this.DistToSquared(this.bodyToEat) > 1.0F) {
    Vector2 var5 = tempo.set(this.x - this.bodyToEat.x, this.y - this.bodyToEat.y);
               var5.setLength(0.5F);
               this.pathToLocationF(this.bodyToEat.getX() + var5.x, this.bodyToEat.getY() + var5.y, this.bodyToEat.getZ());
            }
         }
      } else {
         this.checkForCorpseTimer = 10000.0F;
         this.bodyToEat = nullptr;
      }
   }

    void damageSheetRope() {
      if (Rand.Next(30) == 0
         && this.current != nullptr
         && (
            this.current.Is(IsoFlagType.climbSheetN)
               || this.current.Is(IsoFlagType.climbSheetE)
               || this.current.Is(IsoFlagType.climbSheetS)
               || this.current.Is(IsoFlagType.climbSheetW)
         )) {
    IsoObject var1 = this.current.getSheetRope();
         if (var1 != nullptr) {
            var1.sheetRopeHealth = var1.sheetRopeHealth - Rand.Next(5, 15);
            if (var1.sheetRopeHealth < 40.0F) {
               this.current.damageSpriteSheetRopeFromBottom(nullptr, this.current.Is(IsoFlagType.climbSheetN) || this.current.Is(IsoFlagType.climbSheetS));
               this.current.RecalcProperties();
            }

            if (var1.sheetRopeHealth <= 0.0F) {
               this.current.removeSheetRopeFromBottom(nullptr, this.current.Is(IsoFlagType.climbSheetN) || this.current.Is(IsoFlagType.climbSheetS));
            }
         }
      }
   }

    void getZombieWalkTowardSpeed(float var1, float var2, Vector2 var3) {
    float var4 = 1.0F;
      var4 = var2 / 24.0F;
      if (var4 < 1.0F) {
         var4 = 1.0F;
      }

      if (var4 > 1.3F) {
         var4 = 1.3F;
      }

      var3.setLength((var1 * this.getSpeedMod() + 0.006F) * var4);
      if (SandboxOptions.instance.Lore.Speed.getValue() == 1 && !this.inactive || this.speedType == 1) {
         var3.setLength(0.08F);
         this.bRunning = true;
      }

      if (var3.getLength() > var2) {
         var3.setLength(var2);
      }
   }

    void getZombieLungeSpeed() {
      this.bRunning = SandboxOptions.instance.Lore.Speed.getValue() == 1 && !this.inactive || this.speedType == 1;
   }

    bool tryThump(IsoGridSquare var1) {
      if (this.Ghost) {
    return false;
      } else if (this.bCrawling) {
    return false;
      } else {
         boolean var2 = this.isCurrentState(PathFindState.instance())
            || this.isCurrentState(LungeState.instance())
            || this.isCurrentState(LungeNetworkState.instance())
            || this.isCurrentState(WalkTowardState.instance())
            || this.isCurrentState(WalkTowardNetworkState.instance());
         if (!var2) {
    return false;
         } else {
    IsoGridSquare var3;
            if (var1 != nullptr) {
               var3 = var1;
            } else {
               var3 = this.getFeelerTile(this.getFeelersize());
            }

            if (var3 != nullptr && this.current != nullptr) {
    IsoObject var4 = this.current.testCollideSpecialObjects(var3);
    IsoDoor var5 = (IsoDoor)Type.tryCastTo(var4, IsoDoor.class);
    IsoThumpable var6 = (IsoThumpable)Type.tryCastTo(var4, IsoThumpable.class);
    IsoWindow var7 = (IsoWindow)Type.tryCastTo(var4, IsoWindow.class);
               if (var7 != nullptr && var7.canClimbThrough(this)) {
                  if (!this.isFacingObject(var7, 0.8F)) {
    return false;
                  } else {
                     this.climbThroughWindow(var7);
    return true;
                  }
               } else if (var6 != nullptr && var6.canClimbThrough(this)) {
                  this.climbThroughWindow(var6);
    return true;
               } else if (var6 != nullptr && var6.getThumpableFor(this) != nullptr
                  || var7 != nullptr && var7.getThumpableFor(this) != nullptr
                  || var5 != nullptr && var5.getThumpableFor(this) != nullptr) {
    int var8 = var3.getX() - this.current.getX();
    int var9 = var3.getY() - this.current.getY();
    IsoDirections var10 = IsoDirections.N;
                  if (var8 < 0 && Math.abs(var8) > Math.abs(var9)) {
                     var10 = IsoDirections.S;
                  }

                  if (var8 < 0 && Math.abs(var8) <= Math.abs(var9)) {
                     var10 = IsoDirections.SW;
                  }

                  if (var8 > 0 && Math.abs(var8) > Math.abs(var9)) {
                     var10 = IsoDirections.W;
                  }

                  if (var8 > 0 && Math.abs(var8) <= Math.abs(var9)) {
                     var10 = IsoDirections.SE;
                  }

                  if (var9 < 0 && Math.abs(var8) < Math.abs(var9)) {
                     var10 = IsoDirections.N;
                  }

                  if (var9 < 0 && Math.abs(var8) >= Math.abs(var9)) {
                     var10 = IsoDirections.NW;
                  }

                  if (var9 > 0 && Math.abs(var8) < Math.abs(var9)) {
                     var10 = IsoDirections.E;
                  }

                  if (var9 > 0 && Math.abs(var8) >= Math.abs(var9)) {
                     var10 = IsoDirections.NE;
                  }

                  if (this.getDir() == var10) {
                     boolean var11 = this.getPathFindBehavior2().isGoalSound()
                        && (
                           this.isCurrentState(PathFindState.instance())
                              || this.isCurrentState(WalkTowardState.instance())
                              || this.isCurrentState(WalkTowardNetworkState.instance())
                        );
                     if (SandboxOptions.instance.Lore.ThumpNoChasing.getValue() || this.target != nullptr || var11) {
                        if (var7 != nullptr && var7.getThumpableFor(this) != nullptr) {
                           var4 = (IsoObject)var7.getThumpableFor(this);
                        }

                        this.setThumpTarget(var4);
                        this.setPath2(nullptr);
                     }
                  }

    return true;
               } else if (var4 != nullptr && IsoWindowFrame.isWindowFrame(var4)) {
                  this.climbThroughWindowFrame(var4);
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

    void Wander() {
      this.changeState(ZombieIdleState.instance());
   }

    void DoZombieInventory() {
      this.DoZombieInventory(false);
   }

    void DoCorpseInventory() {
      this.DoZombieInventory(true);
   }

    void DoZombieInventory(bool var1) {
      if (!this.isReanimatedPlayer() && !this.wasFakeDead()) {
         if (!GameServer.bServer || var1) {
            this.getInventory().removeAllItems();
            this.getInventory().setSourceGrid(this.getCurrentSquare());
            this.wornItems.setFromItemVisuals(this.itemVisuals);
            this.wornItems.addItemsToItemContainer(this.getInventory());

            for (int var2 = 0; var2 < this.attachedItems.size(); var2++) {
    AttachedItem var3 = this.attachedItems.get(var2);
    InventoryItem var4 = var3.getItem();
               if (!this.getInventory().contains(var4)) {
                  var4.setContainer(this.getInventory());
                  this.getInventory().getItems().push_back(var4);
               }
            }

    IsoBuilding var7 = this.getCurrentBuilding();
            if (var7 != nullptr && var7.getDef() != nullptr && var7.getDef().getKeyId() != -1 && Rand.Next(4) == 0) {
               if (Rand.Next(10) != 1) {
    std::string var8 = "Base.Key" + (Rand.Next(5) + 1);
    InventoryItem var11 = this.inventory.AddItem(var8);
                  var11.setKeyId(var7.getDef().getKeyId());
               } else if (this.inventory.AddItem("Base.KeyRing") instanceof InventoryContainer var12) {
    std::string var5 = "Base.Key" + (Rand.Next(5) + 1);
    InventoryItem var6 = var12.getInventory().AddItem(var5);
                  var6.setKeyId(var7.getDef().getKeyId());
               }
            }

            if (this.itemsToSpawnAtDeath != nullptr && !this.itemsToSpawnAtDeath.empty()) {
               for (int var10 = 0; var10 < this.itemsToSpawnAtDeath.size(); var10++) {
                  this.inventory.AddItem(this.itemsToSpawnAtDeath.get(var10));
               }

               this.itemsToSpawnAtDeath.clear();
            }

            DebugLog.Death.trace("id=%d, inventory=%d", this.getOnlineID(), this.getInventory().getItems().size());
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

      if (this.strength == -1 && SandboxOptions.instance.Lore.Strength.getValue() == 1) {
         this.strength = 5;
      }

      if (this.strength == -1 && SandboxOptions.instance.Lore.Strength.getValue() == 2) {
         this.strength = 3;
      }

      if (this.strength == -1 && SandboxOptions.instance.Lore.Strength.getValue() == 3) {
         this.strength = 1;
      }

      if (this.strength == -1 && SandboxOptions.instance.Lore.Strength.getValue() == 4) {
         this.strength = Rand.Next(1, 5);
      }

    int var1 = SandboxOptions.instance.Lore.Memory.getValue();
    int var2 = -1;
      if (var1 == 5) {
         var2 = Rand.Next(4);
      }

      if (this.memory == -1 && var1 == 1 || var2 == 0) {
         this.memory = 1250;
      }

      if (this.memory == -1 && var1 == 2 || var2 == 1) {
         this.memory = 800;
      }

      if (this.memory == -1 && var1 == 3 || var2 == 2) {
         this.memory = 500;
      }

      if (this.memory == -1 && var1 == 4 || var2 == 3) {
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
      } else if (SandboxOptions.instance.Lore.Speed.getValue() != 3 && this.speedType != 3 && Rand.Next(3) == 0) {
         if (SandboxOptions.instance.Lore.Speed.getValue() != 3 || this.speedType != 3) {
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

      this.walkType = int.toString(Rand.Next(5) + 1);
      if (this.speedType == 1) {
         this.setTurnDelta(1.0F);
         this.walkType = "sprint" + this.walkType;
      }

      if (this.speedType == 3) {
         this.walkType = int.toString(Rand.Next(3) + 1);
         this.walkType = "slow" + this.walkType;
      }

      this.initCanCrawlUnderVehicle();
   }

    void setWalkType(const std::string& var1) {
      this.walkType = var1;
   }

    void DoZombieSpeeds(float var1) {
      if (this.bCrawling) {
         this.speedMod = var1;
         this.def.AnimFrameIncrease *= 0.8F;
      } else if (Rand.Next(3) != 0 || SandboxOptions.instance.Lore.Speed.getValue() == 3) {
         this.speedMod = var1;
         this.speedMod = this.speedMod + Rand.Next(1500) / 10000.0F;
         this.walkVariant = this.walkVariant + "1";
         this.def.setFrameSpeedPerFrame(0.24F);
         this.def.AnimFrameIncrease = this.def.AnimFrameIncrease * this.speedMod;
      } else if (SandboxOptions.instance.Lore.Speed.getValue() != 3) {
         this.bLunger = true;
         this.speedMod = var1;
         this.walkVariant = this.walkVariant + "2";
         this.def.setFrameSpeedPerFrame(0.24F);
         this.def.AnimFrameIncrease = this.def.AnimFrameIncrease * this.speedMod;
      }
   }

    bool isFakeDead() {
      return this.bFakeDead;
   }

    void setFakeDead(bool var1) {
      if (var1 && Rand.Next(2) == 0) {
         this.setCrawlerType(2);
      }

      this.bFakeDead = var1;
   }

    bool isForceFakeDead() {
      return this.bForceFakeDead;
   }

    void setForceFakeDead(bool var1) {
      this.bForceFakeDead = var1;
   }

    float Hit(BaseVehicle var1, float var2, bool var3, Vector2 var4) {
    float var5 = 0.0F;
      this.AttackedBy = var1.getDriver();
      this.setHitDir(var4);
      this.setHitForce(var2 * 0.15F);
    int var6 = (int)(var2 * 6.0F);
      this.setTarget(var1.getCharacter(0));
      if (!this.bStaggerBack
         && !this.isOnFloor()
         && this.getCurrentState() != ZombieGetUpState.instance()
         && this.getCurrentState() != ZombieOnGroundState.instance()) {
    bool var7 = this.isStaggerBack();
    bool var8 = this.isKnockedDown();
    bool var9 = this.isBecomeCrawler();
         if (var3) {
            this.setHitFromBehind(true);
            if (Rand.Next(100) <= var6) {
               if (Rand.Next(5) == 0) {
                  var9 = true;
               }

               var7 = true;
               var8 = true;
            } else {
               var7 = true;
            }
         } else if (var2 < 3.0F) {
            if (Rand.Next(100) <= var6) {
               if (Rand.Next(8) == 0) {
                  var9 = true;
               }

               var7 = true;
               var8 = true;
            } else {
               var7 = true;
            }
         } else if (var2 < 10.0F) {
            if (Rand.Next(8) == 0) {
               var9 = true;
            }

            var7 = true;
            var8 = true;
         } else {
            var5 = this.getHealth();
            if (!GameServer.bServer && !GameClient.bClient) {
               this.Health -= var5;
               this.Kill(var1.getDriver());
            }
         }

         if (DebugOptions.instance.MultiplayerZombieCrawler.getValue()) {
            var9 = true;
         }

         if (!GameServer.bServer) {
            this.setStaggerBack(var7);
            this.setKnockedDown(var8);
            this.setBecomeCrawler(var9);
         }
      } else {
         if (this.isFakeDead()) {
            this.setFakeDead(false);
         }

         this.setHitReaction("Floor");
         var5 = var2 / 5.0F;
         if (!GameServer.bServer && !GameClient.bClient) {
            this.Health -= var5;
            if (this.isDead()) {
               this.Kill(var1.getDriver());
            }
         }
      }

      if (!GameServer.bServer && !GameClient.bClient) {
         this.addBlood(var2);
      }

    return var5;
   }

    void addBlood(float var1) {
      if (!(Rand.Next(10) > var1)) {
    float var2 = 0.6F;
         if (SandboxOptions.instance.BloodLevel.getValue() > 1) {
    int var3 = Rand.Next(4, 10);
            if (var3 < 1) {
               var3 = 1;
            }

            if (Core.bLastStand) {
               var3 *= 3;
            }

            switch (SandboxOptions.instance.BloodLevel.getValue()) {
               case 2:
                  var3 /= 2;
               case 3:
               default:
                  break;
               case 4:
                  var3 *= 2;
                  break;
               case 5:
                  var3 *= 5;
            }

            for (int var4 = 0; var4 < var3; var4++) {
               this.splatBlood(2, 0.3F);
            }
         }

         if (SandboxOptions.instance.BloodLevel.getValue() > 1) {
            this.splatBloodFloorBig();
         }

         if (SandboxOptions.instance.BloodLevel.getValue() > 1) {
            this.playBloodSplatterSound();
            std::make_shared<IsoZombieGiblets>(
               GibletType.A, this.getCell(), this.getX(), this.getY(), this.getZ() + var2, this.getHitDir().x * 1.5F, this.getHitDir().y * 1.5F
            );
            tempo.x = this.getHitDir().x;
            tempo.y = this.getHitDir().y;
    uint8_t var7 = 3;
    uint8_t var8 = 0;
    uint8_t var5 = 1;
            switch (SandboxOptions.instance.BloodLevel.getValue()) {
               case 1:
                  var5 = 0;
                  break;
               case 2:
                  var5 = 1;
                  var7 = 5;
                  var8 = 2;
               case 3:
               default:
                  break;
               case 4:
                  var5 = 3;
                  var7 = 2;
                  break;
               case 5:
                  var5 = 10;
                  var7 = 0;
            }

            for (int var6 = 0; var6 < var5; var6++) {
               if (Rand.Next(this.isCloseKilled() ? 8 : var7) == 0) {
                  std::make_shared<IsoZombieGiblets>(
                     GibletType.A, this.getCell(), this.getX(), this.getY(), this.getZ() + var2, this.getHitDir().x * 1.5F, this.getHitDir().y * 1.5F
                  );
               }

               if (Rand.Next(this.isCloseKilled() ? 8 : var7) == 0) {
                  std::make_shared<IsoZombieGiblets>(
                     GibletType.A, this.getCell(), this.getX(), this.getY(), this.getZ() + var2, this.getHitDir().x * 1.8F, this.getHitDir().y * 1.8F
                  );
               }

               if (Rand.Next(this.isCloseKilled() ? 8 : var7) == 0) {
                  std::make_shared<IsoZombieGiblets>(
                     GibletType.A, this.getCell(), this.getX(), this.getY(), this.getZ() + var2, this.getHitDir().x * 1.9F, this.getHitDir().y * 1.9F
                  );
               }

               if (Rand.Next(this.isCloseKilled() ? 4 : var8) == 0) {
                  std::make_shared<IsoZombieGiblets>(
                     GibletType.A, this.getCell(), this.getX(), this.getY(), this.getZ() + var2, this.getHitDir().x * 3.9F, this.getHitDir().y * 3.9F
                  );
               }

               if (Rand.Next(this.isCloseKilled() ? 4 : var8) == 0) {
                  std::make_shared<IsoZombieGiblets>(
                     GibletType.A, this.getCell(), this.getX(), this.getY(), this.getZ() + var2, this.getHitDir().x * 3.8F, this.getHitDir().y * 3.8F
                  );
               }

               if (Rand.Next(this.isCloseKilled() ? 9 : 6) == 0) {
                  std::make_shared<IsoZombieGiblets>(
                     GibletType.Eye, this.getCell(), this.getX(), this.getY(), this.getZ() + var2, this.getHitDir().x * 0.8F, this.getHitDir().y * 0.8F
                  );
               }
            }
         }
      }
   }

    void processHitDirection(HandWeapon var1, IsoGameCharacter var2) {
    std::string var3 = var2.getVariableString("ZombieHitReaction");
      if ("Shot" == var3)) {
         var3 = "ShotBelly";
         var2.setCriticalHit(Rand.Next(100) < ((IsoPlayer)var2).calculateCritChance(this));
    Vector2 var4 = var2.getForwardDirection();
    Vector2 var5 = this.getHitAngle();
    double var6 = var4.x * var5.y - var4.y * var5.x;
    double var8 = var6 >= 0.0 ? 1.0 : -1.0;
    double var10 = var4.x * var5.x + var4.y * var5.y;
    double var12 = Math.acos(var10) * var8;
         if (var12 < 0.0) {
            var12 += Math.PI * 2;
         }

    std::string var14 = "";
         if (Math.toDegrees(var12) < 45.0) {
            this.setHitFromBehind(true);
            var14 = "S";
    int var15 = Rand.Next(9);
            if (var15 > 6) {
               var14 = "L";
            }

            if (var15 > 4) {
               var14 = "R";
            }
         }

         if (Math.toDegrees(var12) > 45.0 && Math.toDegrees(var12) < 90.0) {
            this.setHitFromBehind(true);
            if (Rand.Next(4) == 0) {
               var14 = "S";
            } else {
               var14 = "R";
            }
         }

         if (Math.toDegrees(var12) > 90.0 && Math.toDegrees(var12) < 135.0) {
            var14 = "R";
         }

         if (Math.toDegrees(var12) > 135.0 && Math.toDegrees(var12) < 180.0) {
            if (Rand.Next(4) == 0) {
               var14 = "N";
            } else {
               var14 = "R";
            }
         }

         if (Math.toDegrees(var12) > 180.0 && Math.toDegrees(var12) < 225.0) {
            var14 = "N";
    int var16 = Rand.Next(9);
            if (var16 > 6) {
               var14 = "L";
            }

            if (var16 > 4) {
               var14 = "R";
            }
         }

         if (Math.toDegrees(var12) > 225.0 && Math.toDegrees(var12) < 270.0) {
            if (Rand.Next(4) == 0) {
               var14 = "N";
            } else {
               var14 = "L";
            }
         }

         if (Math.toDegrees(var12) > 270.0 && Math.toDegrees(var12) < 315.0) {
            this.setHitFromBehind(true);
            var14 = "L";
         }

         if (Math.toDegrees(var12) > 315.0) {
            if (Rand.Next(4) == 0) {
               var14 = "S";
            } else {
               var14 = "L";
            }
         }

         if ("N" == var14)) {
            if (this.isHitFromBehind()) {
               var3 = "ShotBellyStep";
            } else {
    int var17 = Rand.Next(2);
               switch (var17) {
                  case 0:
                     var3 = "ShotBelly";
                     break;
                  case 1:
                     var3 = "ShotBellyStep";
               }
            }
         }

         if ("S" == var14)) {
            var3 = "ShotBellyStep";
         }

         if ("L" == var14) || "R" == var14)) {
            if (this.isHitFromBehind()) {
    int var18 = Rand.Next(3);
               switch (var18) {
                  case 0:
                     var3 = "ShotChest";
                     break;
                  case 1:
                     var3 = "ShotLeg";
                     break;
                  case 2:
                     var3 = "ShotShoulderStep";
               }
            } else {
    int var19 = Rand.Next(5);
               switch (var19) {
                  case 0:
                     var3 = "ShotChest";
                     break;
                  case 1:
                     var3 = "ShotChestStep";
                     break;
                  case 2:
                     var3 = "ShotLeg";
                     break;
                  case 3:
                     var3 = "ShotShoulder";
                     break;
                  case 4:
                     var3 = "ShotShoulderStep";
               }
            }

            var3 = var3 + var14;
         }

         if (var2.isCriticalHit()) {
            if ("S" == var14)) {
               var3 = "ShotHeadFwd";
            }

            if ("N" == var14)) {
               var3 = "ShotHeadBwd";
            }

            if (("L" == var14) || "R" == var14)) && Rand.Next(4) == 0) {
               var3 = "ShotHeadBwd";
            }
         }

         if (var3.contains("Head")) {
            this.addBlood(BloodBodyPartType.Head, false, true, true);
         } else if (var3.contains("Chest")) {
            this.addBlood(BloodBodyPartType.Torso_Upper, !this.isCriticalHit(), this.isCriticalHit(), true);
         } else if (var3.contains("Belly")) {
            this.addBlood(BloodBodyPartType.Torso_Lower, !this.isCriticalHit(), this.isCriticalHit(), true);
         } else if (var3.contains("Leg")) {
    bool var20 = Rand.Next(2) == 0;
            if ("L" == var14)) {
               this.addBlood(var20 ? BloodBodyPartType.LowerLeg_L : BloodBodyPartType.UpperLeg_L, !this.isCriticalHit(), this.isCriticalHit(), true);
            } else {
               this.addBlood(var20 ? BloodBodyPartType.LowerLeg_R : BloodBodyPartType.UpperLeg_R, !this.isCriticalHit(), this.isCriticalHit(), true);
            }
         } else if (var3.contains("Shoulder")) {
    bool var21 = Rand.Next(2) == 0;
            if ("L" == var14)) {
               this.addBlood(var21 ? BloodBodyPartType.ForeArm_L : BloodBodyPartType.UpperArm_L, !this.isCriticalHit(), this.isCriticalHit(), true);
            } else {
               this.addBlood(var21 ? BloodBodyPartType.ForeArm_R : BloodBodyPartType.UpperArm_R, !this.isCriticalHit(), this.isCriticalHit(), true);
            }
         }
      } else if (var1.getCategories().contains("Blunt")) {
         this.addBlood(BloodBodyPartType.FromIndex(Rand.Next(BloodBodyPartType.UpperArm_L.index(), BloodBodyPartType.Groin.index())), false, false, true);
      } else if (!var1.getCategories().contains("Unarmed")) {
         this.addBlood(BloodBodyPartType.FromIndex(Rand.Next(BloodBodyPartType.UpperArm_L.index(), BloodBodyPartType.Groin.index())), false, true, true);
      }

      if ("ShotHeadFwd" == var3) && Rand.Next(2) == 0) {
         var3 = "ShotHeadFwd02";
      }

      if (this.getEatBodyTarget() != nullptr) {
         if (this.getVariableBoolean("onknees")) {
            var3 = "OnKnees";
         } else {
            var3 = "Eating";
         }
      }

      if ("Floor".equalsIgnoreCase(var3) && this.isCurrentState(ZombieGetUpState.instance()) && this.isFallOnFront()) {
         var3 = "GettingUpFront";
      }

      if (var3 != nullptr && !"" == var3)) {
         this.setHitReaction(var3);
      } else {
         this.setStaggerBack(true);
         this.setHitReaction("");
         if ("LEFT" == this.getPlayerAttackPosition()) || "RIGHT" == this.getPlayerAttackPosition())) {
            var2.setCriticalHit(false);
         }
      }
   }

    void hitConsequences(HandWeapon var1, IsoGameCharacter var2, bool var3, float var4, bool var5) {
      if (!this.isOnlyJawStab() || this.isCloseKilled()) {
         super.hitConsequences(var1, var2, var3, var4, var5);
         if (Core.bDebug) {
            DebugLog.Combat.debugln("Zombie #" + this.OnlineID + " got hit for " + var4);
         }

         this.actionContext.reportEvent("wasHit");
         if (!var5) {
            this.processHitDirection(var1, var2);
         }

         if (!GameClient.bClient
            || this.target == nullptr
            || var2 == this.target
            || !(IsoUtils.DistanceToSquared(this.x, this.y, this.target.x, this.target.y) < 10.0F)) {
            this.setTarget(var2);
         }

         if (!GameServer.bServer && !GameClient.bClient
            || GameClient.bClient && dynamic_cast<IsoPlayer*>(var2) != nullptr && ((IsoPlayer)var2).isLocalPlayer() && !this.isRemoteZombie()) {
            this.setKnockedDown(var2.isCriticalHit() || this.isOnFloor() || this.isAlwaysKnockedDown());
         }

         this.checkClimbOverFenceHit();
         this.checkClimbThroughWindowHit();
         if (this.shouldBecomeCrawler(var2)) {
            this.setBecomeCrawler(true);
         }
      }
   }

    void playHurtSound() {
   }

    void checkClimbOverFenceHit() {
      if (!this.isOnFloor()) {
         if (this.isCurrentState(ClimbOverFenceState.instance())
            && this.getVariableBoolean("ClimbFenceStarted")
            && !this.isVariable("ClimbFenceOutcome", "fall")
            && !this.getVariableBoolean("ClimbFenceFlopped")) {
    std::unordered_map var1 = (std::unordered_map)this.StateMachineParams.get(ClimbOverFenceState.instance());
    uint8_t var2 = 3;
    uint8_t var3 = 4;
    int var4 = (int)var1.get(int.valueOf(var2));
    int var5 = (int)var1.get(int.valueOf(var3));
            this.climbFenceWindowHit(var4, var5);
         }
      }
   }

    void checkClimbThroughWindowHit() {
      if (!this.isOnFloor()) {
         if (this.isCurrentState(ClimbThroughWindowState.instance())
            && this.getVariableBoolean("ClimbWindowStarted")
            && !this.isVariable("ClimbWindowOutcome", "fall")
            && !this.getVariableBoolean("ClimbWindowFlopped")) {
    std::unordered_map var1 = (std::unordered_map)this.StateMachineParams.get(ClimbThroughWindowState.instance());
    uint8_t var2 = 12;
    uint8_t var3 = 13;
    int var4 = (int)var1.get(int.valueOf(var2));
    int var5 = (int)var1.get(int.valueOf(var3));
            this.climbFenceWindowHit(var4, var5);
         }
      }
   }

    void climbFenceWindowHit(int var1, int var2) {
      if (this.getDir() == IsoDirections.W) {
         this.setX(var1 + 0.9F);
         this.setLx(this.getX());
      } else if (this.getDir() == IsoDirections.E) {
         this.setX(var1 + 0.1F);
         this.setLx(this.getX());
      } else if (this.getDir() == IsoDirections.N) {
         this.setY(var2 + 0.9F);
         this.setLy(this.getY());
      } else if (this.getDir() == IsoDirections.S) {
         this.setY(var2 + 0.1F);
         this.setLy(this.getY());
      }

      this.setStaggerBack(false);
      this.setKnockedDown(true);
      this.setOnFloor(true);
      this.setFallOnFront(true);
      this.setHitReaction("FenceWindow");
   }

    bool shouldBecomeCrawler(IsoGameCharacter var1) {
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
    IsoPlayer var2 = (IsoPlayer)Type.tryCastTo(var1, IsoPlayer.class);
         if (var2 != nullptr && !var2.isAimAtFloor() && var2.bDoShove) {
    return false;
         } else {
    uint8_t var3 = 30;
            if (var2 != nullptr && var2.isAimAtFloor() && var2.bDoShove) {
               if (this.isHitLegsWhileOnFloor()) {
                  var3 = 7;
               } else {
                  var3 = 15;
               }
            }

            return Rand.NextBool(var3);
         }
      }
   }

    void removeFromWorld() {
      this.getEmitter().stopOrTriggerSoundByName("BurningFlesh");
      this.clearAggroList();
      VirtualZombieManager.instance.RemoveZombie(this);
      this.setPath2(nullptr);
      PolygonalMap2.instance.cancelRequest(this);
      if (this.getFinder().progress != PathFindProgress.notrunning && this.getFinder().progress != PathFindProgress.found) {
         this.getFinder().progress = PathFindProgress.notrunning;
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

      this.parameterZombieState.setState(zombie.audio.parameters.ParameterZombieState.State.Idle);
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

    bool wasFakeDead() {
      return this.bWasFakeDead;
   }

    void setWasFakeDead(bool var1) {
      this.bWasFakeDead = var1;
   }

    void setCrawler(bool var1) {
      this.bCrawling = var1;
   }

    bool isBecomeCrawler() {
      return this.bBecomeCrawler;
   }

    void setBecomeCrawler(bool var1) {
      this.bBecomeCrawler = var1;
   }

    bool isReanimate() {
      return this.bReanimate;
   }

    void setReanimate(bool var1) {
      this.bReanimate = var1;
   }

    bool isReanimatedPlayer() {
      return this.bReanimatedPlayer;
   }

    void setReanimatedPlayer(bool var1) {
      this.bReanimatedPlayer = var1;
   }

    IsoPlayer getReanimatedPlayer() {
      for (int var1 = 0; var1 < IsoPlayer.numPlayers; var1++) {
    IsoPlayer var2 = IsoPlayer.players[var1];
         if (var2 != nullptr && var2.ReanimatedCorpse == this) {
    return var2;
         }
      }

    return nullptr;
   }

    void setFemaleEtc(bool var1) {
      this.setFemale(var1);
      if (this.getDescriptor() != nullptr) {
         this.getDescriptor().setFemale(var1);
      }

      this.SpriteName = var1 ? "KateZ" : "BobZ";
      this.hurtSound = var1 ? "FemaleZombieHurt" : "MaleZombieHurt";
      if (this.vocalEvent != 0L) {
    std::string var2 = var1 ? "FemaleZombieCombined" : "MaleZombieCombined";
         if (this.getEmitter() != nullptr && !this.getEmitter().isPlaying(var2)) {
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
    int var1 = Math.max(8 - (int)IsoWorld.instance.getWorldAgeDays() / 30, 0);

      for (int var2 = 0; var2 < 5; var2++) {
         if (OutfitRNG.NextBool(var1)) {
            this.addBlood(nullptr, false, true, false);
            this.addDirt(nullptr, nullptr, false);
         }
      }

      for (int var4 = 0; var4 < 8; var4++) {
         if (OutfitRNG.NextBool(var1)) {
    BloodBodyPartType var3 = BloodBodyPartType.FromIndex(OutfitRNG.Next(0, BloodBodyPartType.MAX.index()));
            this.addHole(var3);
            this.addBlood(var3, true, false, false);
         }
      }
   }

    void useDescriptor(Descriptor var1) {
      this.getHumanVisual().clear();
      this.itemVisuals.clear();
      this.m_persistentOutfitId = var1 == nullptr ? 0 : var1.getPersistentOutfitID();
      this.m_bPersistentOutfitInit = true;
      this.sharedDesc = var1;
      if (var1 != nullptr) {
         this.setFemaleEtc(var1.isFemale());
         this.getHumanVisual().copyFrom(var1.getHumanVisual());
         this.getWornItems().setFromItemVisuals(var1.itemVisuals);
         this.onWornItemsChanged();
      }
   }

    Descriptor getSharedDescriptor() {
      return this.sharedDesc;
   }

    int getSharedDescriptorID() {
      return this.getPersistentOutfitID();
   }

    int getScreenProperX(int var1) {
      return (int)(IsoUtils.XToScreen(this.x, this.y, this.z, 0) - IsoCamera.cameras[var1].getOffX());
   }

    int getScreenProperY(int var1) {
      return (int)(IsoUtils.YToScreen(this.x, this.y, this.z, 0) - IsoCamera.cameras[var1].getOffY());
   }

    BaseVisual getVisual() {
      return this.humanVisual;
   }

    HumanVisual getHumanVisual() {
      return this.humanVisual;
   }

    ItemVisuals getItemVisuals() {
      this.getItemVisuals(this.itemVisuals);
      return this.itemVisuals;
   }

    void getItemVisuals(ItemVisuals var1) {
      if (this.isUsingWornItems()) {
         this.getWornItems().getItemVisuals(var1);
      } else if (var1 != this.itemVisuals) {
         var1.clear();
         var1.addAll(this.itemVisuals);
      }
   }

    bool isUsingWornItems() {
      return this.isOnKillDone() || this.isOnDeathDone() || this.isReanimatedPlayer() || this.wasFakeDead();
   }

    void setAsSurvivor() {
    std::string var1 = "Survivalist";
      switch (Rand.Next(3)) {
         case 1:
            var1 = "Survivalist02";
            break;
         case 2:
            var1 = "Survivalist03";
      }

      this.dressInPersistentOutfit(var1);
   }

    void dressInRandomOutfit() {
      ZombiesZoneDefinition.dressInRandomOutfit(this);
   }

    void dressInNamedOutfit(const std::string& var1) {
      this.wornItems.clear();
      this.getHumanVisual().clear();
      this.itemVisuals.clear();
    Outfit var2 = this.isFemale() ? OutfitManager.instance.FindFemaleOutfit(var1) : OutfitManager.instance.FindMaleOutfit(var1);
      if (var2 != nullptr) {
         if (var2.empty()) {
            var2.loadItems();
            this.pendingOutfitName = var1;
         } else {
            this.getHumanVisual().dressInNamedOutfit(var1, this.itemVisuals);
            this.getHumanVisual().synchWithOutfit(this.getHumanVisual().getOutfit());
            UnderwearDefinition.addRandomUnderwear(this);
            this.onWornItemsChanged();
         }
      }
   }

    void dressInPersistentOutfitID(int var1) {
      this.getHumanVisual().clear();
      this.itemVisuals.clear();
      this.m_persistentOutfitId = var1;
      this.m_bPersistentOutfitInit = true;
      if (var1 != 0) {
         this.bDressInRandomOutfit = false;
         PersistentOutfits.instance.dressInOutfit(this, var1);
         this.onWornItemsChanged();
      }
   }

    void dressInClothingItem(const std::string& var1) {
      this.wornItems.clear();
      this.getHumanVisual().dressInClothingItem(var1, this.itemVisuals);
      this.onWornItemsChanged();
   }

    void onWornItemsChanged() {
      this.parameterShoeType.setShoeType(nullptr);
   }

    void clothingItemChanged(const std::string& var1) {
      super.clothingItemChanged(var1);
      if (!StringUtils.isNullOrWhitespace(this.pendingOutfitName)) {
         Outfit var2 = this.isFemale()
            ? OutfitManager.instance.FindFemaleOutfit(this.pendingOutfitName)
            : OutfitManager.instance.FindMaleOutfit(this.pendingOutfitName);
         if (var2 != nullptr && !var2.empty()) {
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
    FloodFill var1 = floodFill;
         var1.calculate(this, this.getCurrentSquare());
    IsoGridSquare var2 = var1.choose();
         var1.reset();
         if (var2 != nullptr) {
            this.pathToLocation(var2.getX(), var2.getY(), var2.getZ());
    return true;
         } else {
    return false;
         }
      }
   }

    bool isUseless() {
      return this.useless;
   }

    void setUseless(bool var1) {
      this.useless = var1;
   }

    void setImmortalTutorialZombie(bool var1) {
      this.ImmortalTutorialZombie = var1;
   }

    bool isTargetInCone(float var1, float var2) {
      if (this.target == nullptr) {
    return false;
      } else {
         tempo.set(this.target.getX() - this.getX(), this.target.getY() - this.getY());
    float var3 = tempo.getLength();
         if (var3 == 0.0F) {
    return true;
         } else if (var3 > var1) {
    return false;
         } else {
            tempo.normalize();
            this.getVectorFromDirection(tempo2);
    float var4 = tempo.dot(tempo2);
            return var4 >= var2;
         }
      }
   }

    bool testCollideWithVehicles(BaseVehicle var1) {
      if (this.Health <= 0.0F) {
    return false;
      } else if (this.isProne()) {
         if (var1.getDriver() == nullptr) {
    return false;
         } else {
    int var3 = var1.isEngineRunning() ? var1.testCollisionWithProneCharacter(this, true) : 0;
            if (var3 > 0) {
               if (!this.emitter.isPlaying(this.getHurtSound())) {
                  this.playHurtSound();
               }

               this.AttackedBy = var1.getDriver();
               var1.hitCharacter(this);
               if (!GameServer.bServer && !GameClient.bClient && this.isDead()) {
                  this.Kill(var1.getDriver());
               }

               super.update();
    return true;
            } else {
    return false;
            }
         }
      } else {
         if (var1.shouldCollideWithCharacters()) {
    Vector2 var2 = (Vector2)((Vector2ObjectPool)BaseVehicle.TL_vector2_pool.get()).alloc();
            if (var1.testCollisionWithCharacter(this, 0.3F, var2) != nullptr) {
               ((Vector2ObjectPool)BaseVehicle.TL_vector2_pool.get()).release(var2);
               var1.hitCharacter(this);
               super.update();
    return true;
            }

            ((Vector2ObjectPool)BaseVehicle.TL_vector2_pool.get()).release(var2);
         }

    return false;
      }
   }

    bool isCrawling() {
      return this.bCrawling;
   }

    bool isCanCrawlUnderVehicle() {
      return this.bCanCrawlUnderVehicle;
   }

    void setCanCrawlUnderVehicle(bool var1) {
      this.bCanCrawlUnderVehicle = var1;
   }

    bool isCanWalk() {
      return this.bCanWalk;
   }

    void setCanWalk(bool var1) {
      this.bCanWalk = var1;
   }

    void initCanCrawlUnderVehicle() {
    uint8_t var1 = 100;
      switch (SandboxOptions.instance.Lore.CrawlUnderVehicle.getValue()) {
         case 1:
            var1 = 0;
            break;
         case 2:
            var1 = 5;
            break;
         case 3:
            var1 = 10;
            break;
         case 4:
            var1 = 25;
            break;
         case 5:
            var1 = 50;
            break;
         case 6:
            var1 = 75;
            break;
         case 7:
            var1 = 100;
      }

      this.setCanCrawlUnderVehicle(Rand.Next(100) < var1);
   }

    bool shouldGetUpFromCrawl() {
      if (this.isCurrentState(ZombieGetUpFromCrawlState.instance())) {
    return true;
      } else if (this.isCurrentState(ZombieGetUpState.instance())) {
         return this.stateMachine.getPrevious() == ZombieGetUpFromCrawlState.instance();
      } else if (!this.isCrawling()) {
    return false;
      } else if (!this.isCanWalk()) {
    return false;
      } else if (this.isCurrentState(PathFindState.instance())) {
         return this.stateMachine.getPrevious() == ZombieGetDownState.instance() && ZombieGetDownState.instance().isNearStartXY(this)
            ? false
            : this.getPathFindBehavior2().shouldGetUpFromCrawl();
      } else {
         if (this.isCurrentState(WalkTowardState.instance())) {
    float var1 = this.getPathFindBehavior2().getTargetX();
    float var2 = this.getPathFindBehavior2().getTargetY();
            if (this.DistToSquared(var1, var2) > 0.010000001F && PolygonalMap2.instance.lineClearCollide(this.x, this.y, var1, var2, (int)this.z, nullptr)) {
    return false;
            }
         }

         return this.isCurrentState(ZombieGetDownState.instance()) ? false : PolygonalMap2.instance.canStandAt(this.x, this.y, (int)this.z, nullptr, false, true);
      }
   }

    void toggleCrawling() {
    bool var1 = this.bCanCrawlUnderVehicle;
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

      this.bCanCrawlUnderVehicle = var1;
   }

    void knockDown(bool var1) {
      this.setKnockedDown(true);
      this.setStaggerBack(true);
      this.setHitReaction("");
      this.setPlayerAttackPosition(var1 ? "BEHIND" : nullptr);
      this.setHitForce(1.0F);
      this.reportEvent("wasHit");
   }

    void addItemToSpawnAtDeath(InventoryItem var1) {
      if (this.itemsToSpawnAtDeath == nullptr) {
         this.itemsToSpawnAtDeath = std::make_unique<std::vector<>>();
      }

      this.itemsToSpawnAtDeath.push_back(var1);
   }

    void clearItemsToSpawnAtDeath() {
      if (this.itemsToSpawnAtDeath != nullptr) {
         this.itemsToSpawnAtDeath.clear();
      }
   }

    IsoMovingObject getEatBodyTarget() {
      return this.eatBodyTarget;
   }

    float getEatSpeed() {
      return this.eatSpeed;
   }

    void setEatBodyTarget(IsoMovingObject var1, bool var2) {
      this.setEatBodyTarget(var1, var2, Rand.Next(0.8F, 1.2F) * GameTime.getAnimSpeedFix());
   }

    void setEatBodyTarget(IsoMovingObject var1, bool var2, float var3) {
      if (var1 != this.eatBodyTarget) {
         if (var2 || var1 == nullptr || var1.getEatingZombies().size() < 3) {
            if (this.eatBodyTarget != nullptr) {
               this.eatBodyTarget.getEatingZombies().remove(this);
            }

            this.eatBodyTarget = var1;
            if (var1 != nullptr) {
               this.eatBodyTarget.getEatingZombies().push_back(this);
               this.eatSpeed = var3;
            }
         }
      }
   }

    void updateEatBodyTarget() {
      if (this.bodyToEat != nullptr
         && this.isCurrentState(ZombieIdleState.instance())
         && this.DistToSquared(this.bodyToEat) <= 1.0F
         && (int)this.getZ() == (int)this.bodyToEat.getZ()) {
         this.setEatBodyTarget(this.bodyToEat, false);
         this.bodyToEat = nullptr;
      }

      if (this.eatBodyTarget != nullptr) {
         if (this.dynamic_cast<IsoDeadBody*>(eatBodyTarget) != nullptr && this.eatBodyTarget.getStaticMovingObjectIndex() == -1) {
            this.setEatBodyTarget(nullptr, false);
         }

         if (this.target != nullptr && !this.target.isOnFloor() && this.target != this.eatBodyTarget) {
            this.setEatBodyTarget(nullptr, false);
         }

    IsoPlayer var1 = (IsoPlayer)Type.tryCastTo(this.eatBodyTarget, IsoPlayer.class);
         if (var1 != nullptr && var1.ReanimatedCorpse != nullptr) {
            this.setEatBodyTarget(nullptr, false);
         }

         if (var1 != nullptr && var1.isAlive() && !var1.isOnFloor() && !var1.isCurrentState(PlayerHitReactionState.instance())) {
            this.setEatBodyTarget(nullptr, false);
         }

         if (!this.isCurrentState(ZombieEatBodyState.instance()) && this.eatBodyTarget != nullptr && this.DistToSquared(this.eatBodyTarget) > 1.0F) {
            this.setEatBodyTarget(nullptr, false);
         }

         if (this.eatBodyTarget != nullptr
            && this.eatBodyTarget.getSquare() != nullptr
            && this.current != nullptr
            && this.current.isSomethingTo(this.eatBodyTarget.getSquare())) {
            this.setEatBodyTarget(nullptr, false);
         }
      }
   }

    void updateCharacterTextureAnimTime() {
    bool var1 = this.isCurrentState(WalkTowardState.instance()) || this.isCurrentState(PathFindState.instance());
      this.m_characterTextureAnimDuration = var1 ? 0.67F : 2.0F;
      this.m_characterTextureAnimTime = this.m_characterTextureAnimTime + GameTime.getInstance().getTimeDelta();
      if (this.m_characterTextureAnimTime > this.m_characterTextureAnimDuration) {
         this.m_characterTextureAnimTime = this.m_characterTextureAnimTime % this.m_characterTextureAnimDuration;
      }
   }

    Vector2 getHitAngle() {
      return this.hitAngle;
   }

    void setHitAngle(Vector2 var1) {
      if (var1 != nullptr) {
         this.hitAngle.set(var1);
      }
   }

    int getCrawlerType() {
      return this.crawlerType;
   }

    void setCrawlerType(int var1) {
      this.crawlerType = var1;
   }

    void addRandomVisualBandages() {
      if (!"Tutorial" == Core.getInstance().getGameMode())) {
         for (int var1 = 0; var1 < 5; var1++) {
            if (OutfitRNG.Next(10) == 0) {
    BodyPartType var2 = BodyPartType.getRandom();
    std::string var3 = var2.getBandageModel() + "_Blood";
               this.addBodyVisualFromItemType(var3);
            }
         }
      }
   }

    void addVisualBandage(BodyPartType var1, bool var2) {
    std::string var3 = var1.getBandageModel() + (var2 ? "_Blood" : "");
      this.addBodyVisualFromItemType(var3);
   }

    void addRandomVisualDamages() {
      for (int var1 = 0; var1 < 5; var1++) {
         if (OutfitRNG.Next(5) == 0) {
    std::string var2 = (std::string)OutfitRNG.pickRandom(ScriptManager.instance.getZedDmgMap());
            this.addBodyVisualFromItemType("Base." + var2);
         }
      }
   }

    std::string getPlayerAttackPosition() {
      return this.playerAttackPosition;
   }

    void setPlayerAttackPosition(const std::string& var1) {
      this.playerAttackPosition = var1;
   }

    bool isSitAgainstWall() {
      return this.sitAgainstWall;
   }

    void setSitAgainstWall(bool var1) {
      this.sitAgainstWall = var1;
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

    bool isZombie() {
    return true;
   }

    void setSkeleton(bool var1) {
      this.isSkeleton = var1;
      if (var1) {
         this.getHumanVisual().setHairModel("");
         this.getHumanVisual().setBeardModel("");
         ModelManager.instance.Reset(this);
      }
   }

    int getHitTime() {
      return this.hitTime;
   }

    void setHitTime(int var1) {
      this.hitTime = var1;
   }

    int getThumpTimer() {
      return this.thumpTimer;
   }

    void setThumpTimer(int var1) {
      this.thumpTimer = var1;
   }

    IsoMovingObject getTarget() {
      return this.target;
   }

    void setTargetSeenTime(float var1) {
      this.targetSeenTime = var1;
   }

    float getTargetSeenTime() {
      return this.targetSeenTime;
   }

    bool isTargetVisible() {
    IsoPlayer var1 = (IsoPlayer)Type.tryCastTo(this.target, IsoPlayer.class);
      if (var1 != nullptr && this.getCurrentSquare() != nullptr) {
         return GameServer.bServer ? ServerLOS.instance.isCouldSee(var1, this.getCurrentSquare()) : this.getCurrentSquare().isCouldSee(var1.getPlayerNum());
      } else {
    return false;
      }
   }

    float getTurnDelta() {
      return this.m_turnDeltaNormal;
   }

    bool isAttacking() {
      return this.isZombieAttacking();
   }

    bool isZombieAttacking() {
    State var1 = this.getCurrentState();
      return var1 != nullptr && var1.isAttacking(this);
   }

    bool isZombieAttacking(IsoMovingObject var1) {
      return GameClient.bClient && this.authOwner == nullptr
         ? this.legsSprite != nullptr && this.legsSprite.CurrentAnim != nullptr && "ZombieBite" == this.legsSprite.CurrentAnim.name)
         : var1 == this.target && this.isCurrentState(AttackState.instance());
   }

    int getHitHeadWhileOnFloor() {
      return this.hitHeadWhileOnFloor;
   }

    std::string getRealState() {
      return this.realState;
   }

    void setHitHeadWhileOnFloor(int var1) {
      this.hitHeadWhileOnFloor = var1;
      this.networkAI.extraUpdate();
   }

    bool isHitLegsWhileOnFloor() {
      return this.hitLegsWhileOnFloor;
   }

    void setHitLegsWhileOnFloor(bool var1) {
      this.hitLegsWhileOnFloor = var1;
   }

    void makeInactive(bool var1) {
      if (var1 != this.inactive) {
         if (var1) {
            this.walkType = int.toString(Rand.Next(3) + 1);
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

    float getFootstepVolume() {
      return this.footstepVolume;
   }

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
    float var1 = Vector2.dot(tempo.x, tempo.y, tempo2.x, tempo2.y);
            return var1 >= 0.8;
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
    int var1 = SandboxOptions.instance.Lore.Memory.getValue();
    short var2 = 160;
      if (this.inactive) {
         var2 = 5;
      } else if (var1 == 1) {
         var2 = 250;
      } else if (var1 == 3) {
         var2 = 100;
      } else if (var1 == 4) {
         var2 = 5;
      }

      return var2 * 5;
   }

    bool shouldDoFenceLunge() {
      if (!SandboxOptions.instance.Lore.ZombiesFenceLunge.getValue()) {
    return false;
      } else if (Rand.NextBool(3)) {
    return false;
      } else {
    IsoGameCharacter var1 = (IsoGameCharacter)Type.tryCastTo(this.target, IsoGameCharacter.class);
         if (var1 == nullptr || (int)var1.getZ() != (int)this.getZ()) {
    return false;
         } else {
            return var1.getVehicle() != nullptr ? false : this.DistTo(var1) < 3.9;
         }
      }
   }

    bool isProne() {
      if (!this.isOnFloor()) {
    return false;
      } else {
         return this.bCrawling ? true : this.isCurrentState(ZombieOnGroundState.instance()) || this.isCurrentState(FakeDeadZombieState.instance());
      }
   }

    void setTarget(IsoMovingObject var1) {
      if (this.target != var1) {
         this.target = var1;
         this.networkAI.extraUpdate();
      }
   }

    bool isAlwaysKnockedDown() {
      return this.alwaysKnockedDown;
   }

    void setAlwaysKnockedDown(bool var1) {
      this.alwaysKnockedDown = var1;
   }

    void setDressInRandomOutfit(bool var1) {
      this.bDressInRandomOutfit = var1;
   }

    void setBodyToEat(IsoDeadBody var1) {
      this.bodyToEat = var1;
   }

    bool isForceEatingAnimation() {
      return this.forceEatingAnimation;
   }

    void setForceEatingAnimation(bool var1) {
      this.forceEatingAnimation = var1;
   }

    bool isOnlyJawStab() {
      return this.onlyJawStab;
   }

    void setOnlyJawStab(bool var1) {
      this.onlyJawStab = var1;
   }

    bool isNoTeeth() {
      return this.noTeeth;
   }

    void setNoTeeth(bool var1) {
      this.noTeeth = var1;
   }

    void setThumpFlag(int var1) {
      if (this.thumpFlag != var1) {
         this.thumpFlag = var1;
         this.networkAI.extraUpdate();
      }
   }

    void setThumpCondition(float var1) {
      this.thumpCondition = PZMath.clamp_01(var1);
   }

    void setThumpCondition(int var1, int var2) {
      if (var2 <= 0) {
         this.thumpCondition = 0.0F;
      } else {
         var1 = PZMath.clamp(var1, 0, var2);
         this.thumpCondition = (float)var1 / var2;
      }
   }

    float getThumpCondition() {
      return this.thumpCondition;
   }

    bool isStaggerBack() {
      return this.bStaggerBack;
   }

    void setStaggerBack(bool var1) {
      this.bStaggerBack = var1;
   }

    bool isKnifeDeath() {
      return this.bKnifeDeath;
   }

    void setKnifeDeath(bool var1) {
      this.bKnifeDeath = var1;
   }

    bool isJawStabAttach() {
      return this.bJawStabAttach;
   }

    void setJawStabAttach(bool var1) {
      this.bJawStabAttach = var1;
   }

    void writeInventory(ByteBuffer var1) {
    std::string var2 = this.isFemale() ? "inventoryfemale" : "inventorymale";
      GameWindow.WriteString(var1, var2);
      if (this.getInventory() != nullptr) {
         var1.put((byte)1);

         try {
    int var3 = -1;

            for (InventoryItem var5 : this.getInventory().getItems()) {
               if (PersistentOutfits.instance.isHatFallen(this.getPersistentOutfitID())
                  && var5.getScriptItem() != nullptr
                  && var5.getScriptItem().getChanceToFall() > 0) {
                  var3 = var5.id;
               }
            }

            if (var3 != -1) {
               this.getInventory().removeItemWithID(var3);
            }

    std::vector var12 = this.getInventory().save(var1);
    WornItems var6 = this.getWornItems();
            if (var6 == nullptr) {
    uint8_t var14 = 0;
               var1.put((byte)var14);
            } else {
    int var13 = var6.size();
               if (var13 > 127) {
                  DebugLog.Multiplayer.warn("Too many worn items");
                  var13 = 127;
               }

               var1.put((byte)var13);

               for (int var7 = 0; var7 < var13; var7++) {
    WornItem var8 = var6.get(var7);
                  if (PersistentOutfits.instance.isHatFallen(this.getPersistentOutfitID())
                     && var8.getItem().getScriptItem() != nullptr
                     && var8.getItem().getScriptItem().getChanceToFall() > 0) {
                     GameWindow.WriteStringUTF(var1, "");
                     var1.putShort((short)-1);
                  } else {
                     GameWindow.WriteStringUTF(var1, var8.getLocation());
                     var1.putShort((short)var12.indexOf(var8.getItem()));
                  }
               }
            }

    AttachedItems var17 = this.getAttachedItems();
            if (var17 == nullptr) {
    uint8_t var15 = 0;
               var1.put((byte)var15);
            } else {
    int var16 = var17.size();
               if (var16 > 127) {
                  DebugLog.Multiplayer.warn("Too many attached items");
                  var16 = 127;
               }

               var1.put((byte)var16);

               for (int var9 = 0; var9 < var16; var9++) {
    AttachedItem var10 = var17.get(var9);
                  GameWindow.WriteStringUTF(var1, var10.getLocation());
                  var1.putShort((short)var12.indexOf(var10.getItem()));
               }
            }
         } catch (IOException var11) {
            DebugLog.Multiplayer.printException(var11, "WriteInventory error for zombie " + this.getOnlineID(), LogSeverity.Error);
         }
      } else {
         var1.put((byte)0);
      }
   }

    void Kill(IsoGameCharacter var1, bool var2) {
      if (!this.isOnKillDone()) {
         super.Kill(var1);
         if (this.shouldDoInventory()) {
            this.DoZombieInventory();
         }

         LuaEventManager.triggerEvent("OnZombieDead", this);
         if (var1 == nullptr) {
            this.DoDeath(nullptr, nullptr, var2);
         } else if (var1.getPrimaryHandItem() instanceof HandWeapon) {
            this.DoDeath((HandWeapon)var1.getPrimaryHandItem(), var1, var2);
         } else {
            this.DoDeath(this.getUseHandWeapon(), var1, var2);
         }
      }
   }

    void Kill(IsoGameCharacter var1) {
      this.Kill(var1, true);
   }

    bool shouldDoInventory() {
      return !GameClient.bClient
         || this.getAttackedBy() instanceof IsoPlayer && ((IsoPlayer)this.getAttackedBy()).isLocalPlayer()
         || this.getAttackedBy() == IsoWorld.instance.CurrentCell.getFakeZombieForHit() && (this.wasLocal() || this.isLocal());
   }

    void becomeCorpse() {
      if (!this.isOnDeathDone()) {
         if (this.shouldBecomeCorpse()) {
            super.becomeCorpse();
            if (GameClient.bClient && this.shouldDoInventory()) {
               GameClient.sendZombieDeath(this);
            }

            if (!GameClient.bClient) {
    IsoDeadBody var1 = std::make_shared<IsoDeadBody>(this);
               if (this.isFakeDead()) {
                  var1.setCrawling(true);
               }

               if (GameServer.bServer) {
                  GameServer.sendBecomeCorpse(var1);
               }
            }
         }
      }
   }

    HitReactionNetworkAI getHitReactionNetworkAI() {
      return this.networkAI.hitReaction;
   }

    NetworkCharacterAI getNetworkCharacterAI() {
      return this.networkAI;
   }

    bool wasLocal() {
      return this.getNetworkCharacterAI() == nullptr || this.getNetworkCharacterAI().wasLocal();
   }

    bool isLocal() {
      return super.isLocal() || !this.isRemoteZombie();
   }

    bool isVehicleCollisionActive(BaseVehicle var1) {
      return !super.isVehicleCollisionActive(var1)
         ? false
         : !this.isCurrentState(ZombieFallDownState.instance()) && !this.isCurrentState(ZombieFallingState.instance());
   }

    void applyDamageFromVehicle(float var1, float var2) {
      this.addBlood(var1);
      this.Health -= var2;
      if (this.Health < 0.0F) {
         this.Health = 0.0F;
      }
   }

    float Hit(BaseVehicle var1, float var2, bool var3, float var4, float var5) {
    float var6 = this.Hit(var1, var2, var3, this.getHitDir().set(var4, var5));
      this.applyDamageFromVehicle(var2, var6);
      super.Hit(var1, var2, var3, var4, var5);
    return var6;
   }

    float calcHitDir(IsoGameCharacter var1, HandWeapon var2, Vector2 var3) {
    float var4 = super.calcHitDir(var1, var2, var3);
      if (this.getAnimationPlayer() != nullptr) {
         var4 = this.getAnimAngleRadians();
      }

    return var4;
   }
}
} // namespace characters
} // namespace zombie
