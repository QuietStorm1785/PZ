#pragma once
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/BaseSoundListener.h"
#include "fmod/fmod/DummySoundListener.h"
#include "fmod/fmod/FMODSoundEmitter.h"
#include "fmod/fmod/SoundListener.h"
#include "org/joml/Vector3f.h"
#include "zombie/DebugFileWatcher.h"
#include "zombie/GameSounds.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/PredicatedFileWatcher.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SoundManager.h"
#include "zombie/SystemDisabler.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/ZomboidGlobals.h"
#include "zombie/ai/State.h"
#include "zombie/ai/sadisticAIDirector/SleepingEvent.h"
#include "zombie/ai/states/BumpedState.h"
#include "zombie/ai/states/ClimbDownSheetRopeState.h"
#include "zombie/ai/states/ClimbOverFenceState.h"
#include "zombie/ai/states/ClimbOverWallState.h"
#include "zombie/ai/states/ClimbSheetRopeState.h"
#include "zombie/ai/states/ClimbThroughWindowState.h"
#include "zombie/ai/states/CloseWindowState.h"
#include "zombie/ai/states/CollideWithWallState.h"
#include "zombie/ai/states/FakeDeadZombieState.h"
#include "zombie/ai/states/FishingState.h"
#include "zombie/ai/states/FitnessState.h"
#include "zombie/ai/states/ForecastBeatenPlayerState.h"
#include "zombie/ai/states/IdleState.h"
#include "zombie/ai/states/OpenWindowState.h"
#include "zombie/ai/states/PathFindState.h"
#include "zombie/ai/states/PlayerActionsState.h"
#include "zombie/ai/states/PlayerAimState.h"
#include "zombie/ai/states/PlayerEmoteState.h"
#include "zombie/ai/states/PlayerExtState.h"
#include "zombie/ai/states/PlayerFallDownState.h"
#include "zombie/ai/states/PlayerFallingState.h"
#include "zombie/ai/states/PlayerGetUpState.h"
#include "zombie/ai/states/PlayerHitReactionPVPState.h"
#include "zombie/ai/states/PlayerHitReactionState.h"
#include "zombie/ai/states/PlayerKnockedDown.h"
#include "zombie/ai/states/PlayerOnGroundState.h"
#include "zombie/ai/states/PlayerSitOnGroundState.h"
#include "zombie/ai/states/PlayerStrafeState.h"
#include "zombie/ai/states/SmashWindowState.h"
#include "zombie/ai/states/StaggerBackState.h"
#include "zombie/ai/states/SwipeStatePlayer.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/audio/DummySoundEmitter.h"
#include "zombie/audio/FMODParameterList.h"
#include "zombie/audio/GameSound.h"
#include "zombie/audio/parameters/ParameterCharacterMovementSpeed.h"
#include "zombie/audio/parameters/ParameterCharacterMovementSpeed/MovementType.h"
#include "zombie/audio/parameters/ParameterEquippedBaggageContainer.h"
#include "zombie/audio/parameters/ParameterEquippedBaggageContainer/ContainerType.h"
#include "zombie/audio/parameters/ParameterFootstepMaterial.h"
#include "zombie/audio/parameters/ParameterFootstepMaterial2.h"
#include "zombie/audio/parameters/ParameterLocalPlayer.h"
#include "zombie/audio/parameters/ParameterMeleeHitSurface.h"
#include "zombie/audio/parameters/ParameterMeleeHitSurface/Material.h"
#include "zombie/audio/parameters/ParameterPlayerHealth.h"
#include "zombie/audio/parameters/ParameterRoomType.h"
#include "zombie/audio/parameters/ParameterShoeType.h"
#include "zombie/audio/parameters/ParameterVehicleHitLocation.h"
#include "zombie/audio/parameters/ParameterVehicleHitLocation/HitLocation.h"
#include "zombie/characters/AttachedItems/AttachedItems.h"
#include "zombie/characters/BodyDamage/BodyDamage.h"
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/BodyDamage/Fitness.h"
#include "zombie/characters/BodyDamage/Nutrition.h"
#include "zombie/characters/CharacterTimedActions/BaseAction.h"
#include "zombie/characters/IsoPlayer/1.h"
#include "zombie/characters/IsoPlayer/2.h"
#include "zombie/characters/IsoPlayer/InputState.h"
#include "zombie/characters/IsoPlayer/MoveVars.h"
#include "zombie/characters/IsoPlayer/VehicleContainer.h"
#include "zombie/characters/IsoPlayer/VehicleContainerData.h"
#include "zombie/characters/IsoPlayer/s_performance.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/characters/Moodles/Moodles.h"
#include "zombie/characters/action/ActionContext.h"
#include "zombie/characters/action/ActionGroup.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/commands/PlayerType.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/Translator.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimLayer.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/core/skinnedmodel/visual/BaseVisual.h"
#include "zombie/core/skinnedmodel/visual/HumanVisual.h"
#include "zombie/core/skinnedmodel/visual/IHumanVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/DebugType.h"
#include "zombie/gameStates/MainScreenState.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/input/JoypadManager.h"
#include "zombie/input/Mouse.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/types/Clothing.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/WeaponType.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoGridSquare/ILighting.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoPhysicsObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SliceY.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/iso/objects/IsoBarricade.h"
#include "zombie/iso/objects/IsoCurtain.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/IsoWindowFrame.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/BodyDamageSync.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PassengerMap.h"
#include "zombie/network/ReplayManager.h"
#include "zombie/network/ServerLOS.h"
#include "zombie/network/ServerMap.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/network/ServerWorldDatabase.h"
#include "zombie/network/packets/EventPacket.h"
#include "zombie/network/packets/hit/AttackVars.h"
#include "zombie/network/packets/hit/HitInfo.h"
#include "zombie/savefile/ClientPlayerDB.h"
#include "zombie/savefile/PlayerDB.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/scripting/objects/VehicleScript/Part.h"
#include "zombie/ui/TutorialManager.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/BaseVehicle/Vector2ObjectPool.h"
#include "zombie/vehicles/PathFindBehavior2.h"
#include "zombie/vehicles/PathFindBehavior2/BehaviorResult.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include "zombie/vehicles/PolygonalMap2/Point.h"
#include "zombie/vehicles/VehiclePart.h"
#include "zombie/vehicles/VehicleWindow.h"
#include "zombie/vehicles/VehiclesDB2.h"
#include "zombie/world/WorldDictionary.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>

namespace zombie {
namespace characters {


class IsoPlayer : public IsoLivingCharacter {
public:
    std::string attackType = nullptr;
    static std::string DEATH_MUSIC_NAME = "PlayerDied";
    bool allowSprint = true;
    bool allowRun = true;
    static bool isTestAIMode = false;
    static const bool NoSound = false;
    static const float TIME_RIGHT_PRESSED_SECONDS = 0.15F;
    static int assumedPlayer = 0;
    static int numPlayers = 1;
    static const short MAX = 4;
   public static const IsoPlayer[] players = new IsoPlayer[4];
    static IsoPlayer instance;
    static const void* instanceLock = "IsoPlayer.instance Lock";
    static const Vector2 testHitPosition = std::make_shared<Vector2>();
    static int FollowDeadCount = 240;
   private static const std::stack<std::string> StaticTraits = std::make_unique<std::stack<>>();
    bool ignoreAutoVault = false;
    int remoteSneakLvl = 0;
    int remoteStrLvl = 0;
    int remoteFitLvl = 0;
    bool canSeeAll = false;
    bool canHearAll = false;
    bool MoodleCantSprint = false;
    static const Vector2 tempo = std::make_shared<Vector2>();
    static const Vector2 tempVector2 = std::make_shared<Vector2>();
    static const std::string forwardStr = "Forward";
    static const std::string backwardStr = "Backward";
    static const std::string leftStr = "Left";
    static const std::string rightStr = "Right";
    static bool CoopPVP = false;
    bool ignoreContextKey = false;
    bool ignoreInputsForDirection = false;
    bool showMPInfos = false;
    long lastRemoteUpdate = 0L;
    bool spottedByPlayer = false;
   private std::unordered_map<int, int> spottedPlayerTimer = std::make_unique<std::unordered_map<>>();
    float extUpdateCount = 0.0F;
    static const int s_randomIdleFidgetInterval = 5000;
    bool attackStarted = false;
   private static const PredicatedFileWatcher m_isoPlayerTriggerWatcher = std::make_shared<PredicatedFileWatcher>(
      ZomboidFileSystem.instance.getMessagingDirSub("Trigger_ResetIsoPlayerModel.xml"), IsoPlayer::onTrigger_ResetIsoPlayerModel
   );
    const PredicatedFileWatcher m_setClothingTriggerWatcher;
    static Vector2 tempVector2_1 = std::make_shared<Vector2>();
    static Vector2 tempVector2_2 = std::make_shared<Vector2>();
    const HumanVisual humanVisual = std::make_shared<HumanVisual>(this);
    const ItemVisuals itemVisuals = std::make_shared<ItemVisuals>();
    bool targetedByZombie = false;
    float lastTargeted = 1.0E8F;
    float TimeSinceOpenDoor;
    bool bRemote;
    int TimeSinceLastNetData = 0;
    std::string accessLevel = "";
    std::string tagPrefix = "";
    bool showTag = true;
    bool factionPvp = false;
    short OnlineID = 1;
    int OnlineChunkGridWidth;
    bool bJoypadMovementActive = true;
    bool bJoypadIgnoreAimUntilCentered;
    bool bJoypadIgnoreChargingRT = false;
    bool bJoypadBDown = false;
    bool bJoypadSprint = false;
    bool mpTorchCone = false;
    float mpTorchDist = 0.0F;
    float mpTorchStrength = 0.0F;
    int PlayerIndex = 0;
    int serverPlayerIndex = 1;
    float useChargeDelta = 0.0F;
    int JoypadBind = -1;
    float ContextPanic = 0.0F;
    float numNearbyBuildingsRooms = 0.0F;
    bool isCharging = false;
    bool isChargingLT = false;
    bool bLookingWhileInVehicle = false;
    bool climbOverWallSuccess;
    bool climbOverWallStruggle;
    bool JustMoved = false;
    bool L3Pressed = false;
    bool R3Pressed = false;
    float maxWeightDelta = 1.0F;
    float CurrentSpeed = 0.0F;
    float MaxSpeed = 0.09F;
    bool bDeathFinished = false;
    bool isSpeek;
    bool isVoiceMute;
    const Vector2 playerMoveDir = std::make_shared<Vector2>(0.0F, 0.0F);
    BaseSoundListener soundListener;
    std::string username = "Bob";
    bool dirtyRecalcGridStack = true;
    float dirtyRecalcGridStackTime = 10.0F;
    float runningTime = 0.0F;
    float timePressedContext = 0.0F;
    float chargeTime = 0.0F;
    float useChargeTime = 0.0F;
    bool bPressContext = false;
    float closestZombie = 1000000.0F;
    const Vector2 lastAngle = std::make_shared<Vector2>();
    std::string SaveFileName;
    bool bBannedAttacking = false;
    int sqlID = -1;
    int ClearSpottedTimer = -1;
    float timeSinceLastStab = 0.0F;
   protected std::stack<IsoMovingObject> LastSpotted = std::make_unique<std::stack<>>();
    bool bChangeCharacterDebounce = false;
    int followID = 0;
   protected const std::stack<IsoGameCharacter> FollowCamStack = std::make_unique<std::stack<>>();
    bool bSeenThisFrame = false;
    bool bCouldBeSeenThisFrame = false;
    float AsleepTime = 0.0F;
   protected const std::stack<IsoMovingObject> spottedList = std::make_unique<std::stack<>>();
    int TicksSinceSeenZombie = 9999999;
    bool Waiting = true;
    IsoSurvivor DragCharacter = nullptr;
    float heartDelay = 30.0F;
    float heartDelayMax = 30.0F;
    long heartEventInstance;
    long worldAmbianceInstance;
    std::string Forname = "Bob";
    std::string Surname = "Smith";
    int DialogMood = 1;
    int ping = 0;
    IsoMovingObject DragObject = nullptr;
    double lastSeenZombieTime = 2.0;
    BaseSoundEmitter testemitter;
    int checkSafehouse = 200;
    bool attackFromBehind = false;
    float TimeRightPressed = 0.0F;
    long aimKeyDownMS = 0L;
    long runKeyDownMS = 0L;
    long sprintKeyDownMS = 0L;
    int hypothermiaCache = -1;
    int hyperthermiaCache = -1;
    float ticksSincePressedMovement = 0.0F;
    bool flickTorch = false;
    float checkNearbyRooms = 0.0F;
    bool bUseVehicle = false;
    bool bUsedVehicle;
    float useVehicleDuration;
    static const Vector3f tempVector3f = std::make_shared<Vector3f>();
    const InputState inputState = std::make_shared<InputState>();
    bool isWearingNightVisionGoggles = false;
    int transactionID = 0;
    float MoveSpeed = 0.06F;
    int offSetXUI = 0;
    int offSetYUI = 0;
    float combatSpeed = 1.0F;
    double HoursSurvived = 0.0;
    bool noClip = false;
    bool authorizeMeleeAction = true;
    bool authorizeShoveStomp = true;
    bool blockMovement = false;
    Nutrition nutrition;
    Fitness fitness;
    bool forceOverrideAnim = false;
    bool initiateAttack = false;
    const ColorInfo tagColor = std::make_shared<ColorInfo>(1.0F, 1.0F, 1.0F, 1.0F);
    std::string displayName = nullptr;
    bool seeNonPvpZone = false;
   private const std::unordered_map<int64_t, int64_t> mechanicsItem = std::make_unique<std::unordered_map<>>();
    int sleepingPillsTaken = 0;
    long lastPillsTaken = 0L;
    long heavyBreathInstance = 0L;
    std::string heavyBreathSoundName = nullptr;
    bool allChatMuted = false;
    bool forceAim = false;
    bool forceRun = false;
    bool forceSprint = false;
    bool bMultiplayer;
    std::string SaveFileIP;
    BaseVehicle vehicle4testCollision = nullptr;
    long steamID;
    const VehicleContainerData vehicleContainerData = std::make_shared<VehicleContainerData>();
    bool isWalking = false;
    int footInjuryTimer = 0;
    bool bSneakDebounce;
    float m_turnDelta = 0.0F;
    bool m_isPlayerMoving = false;
    float m_walkSpeed = 0.0F;
    float m_walkInjury = 0.0F;
    float m_runSpeed = 0.0F;
    float m_idleSpeed = 0.0F;
    float m_deltaX = 0.0F;
    float m_deltaY = 0.0F;
    float m_windspeed = 0.0F;
    float m_windForce = 0.0F;
    float m_IPX = 0.0F;
    float m_IPY = 0.0F;
    float pressedRunTimer = 0.0F;
    bool pressedRun = false;
    bool m_meleePressed = false;
    bool m_lastAttackWasShove = false;
    bool m_isPerformingAnAction = false;
   private std::vector<std::string> alreadyReadBook = std::make_unique<std::vector<>>();
    uint8_t bleedingLevel = 0;
    const NetworkPlayerAI networkAI;
    ReplayManager replay = nullptr;
   private static const std::vector<IsoPlayer> RecentlyRemoved = std::make_unique<std::vector<>>();
    bool pathfindRun = false;
    static const MoveVars s_moveVars = std::make_shared<MoveVars>();
    int atkTimer = 0;
   private static const std::vector<HitInfo> s_targetsProne = std::make_unique<std::vector<>>();
   private static const std::vector<HitInfo> s_targetsStanding = std::make_unique<std::vector<>>();
    bool bReloadButtonDown = false;
    bool bRackButtonDown = false;
    bool bReloadKeyDown = false;
    bool bRackKeyDown = false;
    long AttackAnimThrowTimer = System.currentTimeMillis();
    std::string WeaponT = nullptr;
    const ParameterCharacterMovementSpeed parameterCharacterMovementSpeed = std::make_shared<ParameterCharacterMovementSpeed>(this);
    const ParameterEquippedBaggageContainer parameterEquippedBaggageContainer = std::make_shared<ParameterEquippedBaggageContainer>(this);
    const ParameterFootstepMaterial parameterFootstepMaterial = std::make_shared<ParameterFootstepMaterial>(this);
    const ParameterFootstepMaterial2 parameterFootstepMaterial2 = std::make_shared<ParameterFootstepMaterial2>(this);
    const ParameterLocalPlayer parameterLocalPlayer = std::make_shared<ParameterLocalPlayer>(this);
    const ParameterMeleeHitSurface parameterMeleeHitSurface = std::make_shared<ParameterMeleeHitSurface>(this);
    const ParameterPlayerHealth parameterPlayerHealth = std::make_shared<ParameterPlayerHealth>(this);
    const ParameterVehicleHitLocation parameterVehicleHitLocation = std::make_shared<ParameterVehicleHitLocation>();
    const ParameterShoeType parameterShoeType = std::make_shared<ParameterShoeType>(this);

    public IsoPlayer(IsoCell var1) {
      this(var1, nullptr, 0, 0, 0);
   }

    public IsoPlayer(IsoCell var1, SurvivorDesc var2, int var3, int var4, int var5) {
      super(var1, var3, var4, var5);
      this.registerVariableCallbacks();
      this.Traits.addAll(StaticTraits);
      StaticTraits.clear();
      this.dir = IsoDirections.W;
      this.nutrition = std::make_shared<Nutrition>(this);
      this.fitness = std::make_shared<Fitness>(this);
      this.initWornItems("Human");
      this.initAttachedItems("Human");
      this.clothingWetness = std::make_shared<ClothingWetness>(this);
      if (var2 != nullptr) {
         this.descriptor = var2;
      } else {
         this.descriptor = std::make_unique<SurvivorDesc>();
      }

      this.setFemale(this.descriptor.isFemale());
      this.Dressup(this.descriptor);
      this.getHumanVisual().copyFrom(this.descriptor.humanVisual);
      this.InitSpriteParts(this.descriptor);
      LuaEventManager.triggerEvent("OnCreateLivingCharacter", this, this.descriptor);
      if (!GameClient.bClient && !GameServer.bServer) {
      }

      this.descriptor.Instance = this;
      this.SpeakColour = std::make_shared<Color>(Rand.Next(135) + 120, Rand.Next(135) + 120, Rand.Next(135) + 120, 255);
      if (GameClient.bClient) {
         if (Core.getInstance().getMpTextColor() != nullptr) {
            this.SpeakColour = std::make_shared<Color>(
               Core.getInstance().getMpTextColor().r, Core.getInstance().getMpTextColor().g, Core.getInstance().getMpTextColor().b, 1.0F
            );
         } else {
            Core.getInstance().setMpTextColor(std::make_shared<ColorInfo>(this.SpeakColour.r, this.SpeakColour.g, this.SpeakColour.b, 1.0F));

            try {
               Core.getInstance().saveOptions();
            } catch (IOException var7) {
               var7.printStackTrace();
            }
         }
      }

      if (Core.GameMode == "LastStand")) {
         this.Traits.push_back("Strong");
      }

      if (this.Traits.Strong.isSet()) {
         this.maxWeightDelta = 1.5F;
      }

      if (this.Traits.Weak.isSet()) {
         this.maxWeightDelta = 0.75F;
      }

      if (this.Traits.Feeble.isSet()) {
         this.maxWeightDelta = 0.9F;
      }

      if (this.Traits.Stout.isSet()) {
         this.maxWeightDelta = 1.25F;
      }

      this.descriptor.temper = 5.0F;
      if (this.Traits.ShortTemper.isSet()) {
         this.descriptor.temper = 7.5F;
      } else if (this.Traits.Patient.isSet()) {
         this.descriptor.temper = 2.5F;
      }

      if (this.Traits.Injured.isSet()) {
         this.getBodyDamage().AddRandomDamage();
      }

      this.bMultiplayer = GameServer.bServer || GameClient.bClient;
      this.vehicle4testCollision = nullptr;
      if (Core.bDebug && DebugOptions.instance.CheatPlayerStartInvisible.getValue()) {
         this.setGhostMode(true);
         this.setGodMod(true);
      }

      this.actionContext.setGroup(ActionGroup.getActionGroup("player"));
      this.initializeStates();
      DebugFileWatcher.instance.push_back(m_isoPlayerTriggerWatcher);
      this.m_setClothingTriggerWatcher = std::make_shared<PredicatedFileWatcher>(
         ZomboidFileSystem.instance.getMessagingDirSub("Trigger_SetClothing.xml"), TriggerXmlFile.class, this::onTrigger_setClothingToXmlTriggerFile
      );
      this.networkAI = std::make_shared<NetworkPlayerAI>(this);
      this.initFMODParameters();
   }

    void setOnlineID(short var1) {
      this.OnlineID = var1;
   }

    void registerVariableCallbacks() {
      this.setVariable("CombatSpeed", () -> this.combatSpeed, var1 -> this.combatSpeed = var1);
      this.setVariable("TurnDelta", () -> this.m_turnDelta, var1 -> this.m_turnDelta = var1);
      this.setVariable("sneaking", this::isSneaking, this::setSneaking);
      this.setVariable("initiateAttack", () -> this.initiateAttack, this::setInitiateAttack);
      this.setVariable("isMoving", this::isPlayerMoving);
      this.setVariable("isRunning", this::isRunning, this::setRunning);
      this.setVariable("isSprinting", this::isSprinting, this::setSprinting);
      this.setVariable("run", this::isRunning, this::setRunning);
      this.setVariable("sprint", this::isSprinting, this::setSprinting);
      this.setVariable("isStrafing", this::isStrafing);
      this.setVariable("WalkSpeed", () -> this.m_walkSpeed, var1 -> this.m_walkSpeed = var1);
      this.setVariable("WalkInjury", () -> this.m_walkInjury, var1 -> this.m_walkInjury = var1);
      this.setVariable("RunSpeed", () -> this.m_runSpeed, var1 -> this.m_runSpeed = var1);
      this.setVariable("IdleSpeed", () -> this.m_idleSpeed, var1 -> this.m_idleSpeed = var1);
      this.setVariable("DeltaX", () -> this.m_deltaX, var1 -> this.m_deltaX = var1);
      this.setVariable("DeltaY", () -> this.m_deltaY, var1 -> this.m_deltaY = var1);
      this.setVariable("Windspeed", () -> this.m_windspeed, var1 -> this.m_windspeed = var1);
      this.setVariable("WindForce", () -> this.m_windForce, var1 -> this.m_windForce = var1);
      this.setVariable("IPX", () -> this.m_IPX, var1 -> this.m_IPX = var1);
      this.setVariable("IPY", () -> this.m_IPY, var1 -> this.m_IPY = var1);
      this.setVariable("attacktype", () -> this.attackType);
      this.setVariable("aim", this::isAiming);
      this.setVariable("bdoshove", () -> this.bDoShove);
      this.setVariable("bfalling", () -> this.z > 0.0F && this.fallTime > 2.0F);
      this.setVariable("baimatfloor", this::isAimAtFloor);
      this.setVariable("attackfrombehind", () -> this.attackFromBehind);
      this.setVariable("bundervehicle", this::isUnderVehicle);
      this.setVariable("reanimatetimer", this::getReanimateTimer);
      this.setVariable("isattacking", this::isAttacking);
      this.setVariable("beensprintingfor", this::getBeenSprintingFor);
      this.setVariable("bannedAttacking", () -> this.bBannedAttacking);
      this.setVariable("meleePressed", () -> this.m_meleePressed);
      this.setVariable("AttackAnim", this::isAttackAnim, this::setAttackAnim);
      this.setVariable("Weapon", this::getWeaponType, this::setWeaponType);
      this.setVariable("BumpFall", false);
      this.setVariable("bClient", () -> GameClient.bClient);
      this.setVariable("IsPerformingAnAction", this::isPerformingAnAction, this::setPerformingAnAction);
   }

    Vector2 getDeferredMovement(Vector2 var1) {
      super.getDeferredMovement(var1);
      if (DebugOptions.instance.CheatPlayerInvisibleSprint.getValue()
         && this.isGhostMode()
         && (this.IsRunning() || this.isSprinting())
         && !this.isCurrentState(ClimbOverFenceState.instance())
         && !this.isCurrentState(ClimbThroughWindowState.instance())) {
         if (this.getPath2() == nullptr && !this.pressedMovement(false)) {
            return var1.set(0.0F, 0.0F);
         }

         if (this.getCurrentBuilding() != nullptr) {
            var1.scale(2.5F);
    return var1;
         }

         var1.scale(7.5F);
      }

    return var1;
   }

    float getTurnDelta() {
      return !DebugOptions.instance.CheatPlayerInvisibleSprint.getValue() || !this.isGhostMode() || !this.isRunning() && !this.isSprinting()
         ? super.getTurnDelta()
         : 10.0F;
   }

    void setPerformingAnAction(bool var1) {
      this.m_isPerformingAnAction = var1;
   }

    bool isPerformingAnAction() {
      return this.m_isPerformingAnAction;
   }

    bool isAttacking() {
      return !StringUtils.isNullOrWhitespace(this.getAttackType());
   }

    bool shouldBeTurning() {
      if (this.isPerformingAnAction()) {
      }

      return super.shouldBeTurning();
   }

    static void invokeOnPlayerInstance(Runnable var0) {
      /* synchronized - TODO: add std::mutex */ (instanceLock) {
         if (instance != nullptr) {
            var0.run();
         }
      }
   }

    static IsoPlayer getInstance() {
    return instance;
   }

    static void setInstance(IsoPlayer var0) {
      /* synchronized - TODO: add std::mutex */ (instanceLock) {
         instance = var0;
      }
   }

    static bool hasInstance() {
      return instance != nullptr;
   }

    static void onTrigger_ResetIsoPlayerModel(const std::string& var0) {
      if (instance != nullptr) {
         DebugLog.log(DebugType.General, "DebugFileWatcher Hit. Resetting player model: " + var0);
         instance.resetModel();
      } else {
         DebugLog.log(DebugType.General, "DebugFileWatcher Hit. Player instance nullptr : " + var0);
      }
   }

   public static std::stack<std::string> getStaticTraits() {
    return StaticTraits;
   }

    static int getFollowDeadCount() {
    return FollowDeadCount;
   }

    static void setFollowDeadCount(int var0) {
      FollowDeadCount = var0;
   }

   public static std::vector<std::string> getAllFileNames() {
    std::vector var0 = new std::vector();
    std::string var1 = ZomboidFileSystem.instance.getCurrentSaveDir();

      for (int var2 = 1; var2 < 100; var2++) {
    File var3 = std::make_shared<File>(var1 + File.separator + "map_p" + var2 + ".bin");
         if (var3.exists()) {
            var0.push_back("map_p" + var2 + ".bin");
         }
      }

    return var0;
   }

    static std::string getUniqueFileName() {
    int var0 = 0;
    std::string var1 = ZomboidFileSystem.instance.getCurrentSaveDir();

      for (int var2 = 1; var2 < 100; var2++) {
    File var3 = std::make_shared<File>(var1 + File.separator + "map_p" + var2 + ".bin");
         if (var3.exists()) {
            var0 = var2;
         }
      }

      return ZomboidFileSystem.instance.getFileNameInCurrentSave("map_p" + ++var0 + ".bin");
   }

   public static std::vector<IsoPlayer> getAllSavedPlayers() {
    std::vector var0;
      if (GameClient.bClient) {
         var0 = ClientPlayerDB.getInstance().getAllNetworkPlayers();
      } else {
         var0 = PlayerDB.getInstance().getAllLocalPlayers();
      }

      for (int var1 = var0.size() - 1; var1 >= 0; var1--) {
         if (((IsoPlayer)var0.get(var1)).isDead()) {
            var0.remove(var1);
         }
      }

    return var0;
   }

    static bool isServerPlayerIDValid(const std::string& var0) {
      if (GameClient.bClient) {
    std::string var1 = ServerOptions.instance.ServerPlayerID.getValue();
         return var1 != nullptr && !var1.empty() ? var1 == var0) : true;
      } else {
    return true;
      }
   }

    static int getPlayerIndex() {
    return instance = = nullptr ? assumedPlayer : instance.PlayerIndex;
   }

    static bool allPlayersDead() {
      for (int var0 = 0; var0 < numPlayers; var0++) {
         if (players[var0] != nullptr && !players[var0].isDead()) {
    return false;
         }
      }

      return IsoWorld.instance == nullptr || IsoWorld.instance.AddCoopPlayers.empty();
   }

   public static std::vector<IsoPlayer> getPlayers() {
      return new std::vector<>(Arrays.asList(players));
   }

    static bool allPlayersAsleep() {
    int var0 = 0;
    int var1 = 0;

      for (int var2 = 0; var2 < numPlayers; var2++) {
         if (players[var2] != nullptr && !players[var2].isDead()) {
            var0++;
            if (players[var2] != nullptr && players[var2].isAsleep()) {
               var1++;
            }
         }
      }

      return var0 > 0 && var0 == var1;
   }

    static bool getCoopPVP() {
    return CoopPVP;
   }

    static void setCoopPVP(bool var0) {
      CoopPVP = var0;
   }

    void TestZombieSpotPlayer(IsoMovingObject var1) {
      if (GameServer.bServer && dynamic_cast<IsoZombie*>(var1) != nullptr && ((IsoZombie)var1).target != this && ((IsoZombie)var1).isLeadAggro(this)) {
         GameServer.updateZombieControl((IsoZombie)var1, (short)1, this.OnlineID);
      } else {
         var1.spotted(this, false);
         if (dynamic_cast<IsoZombie*>(var1) != nullptr) {
    float var2 = var1.DistTo(this);
            if (var2 < this.closestZombie && !var1.isOnFloor()) {
               this.closestZombie = var2;
            }
         }
      }
   }

    float getPathSpeed() {
    float var1 = this.getMoveSpeed() * 0.9F;
      switch (this.Moodles.getMoodleLevel(MoodleType.Endurance)) {
         case 1:
            var1 *= 0.95F;
            break;
         case 2:
            var1 *= 0.9F;
            break;
         case 3:
            var1 *= 0.8F;
            break;
         case 4:
            var1 *= 0.6F;
      }

      if (this.stats.enduranceRecharging) {
         var1 *= 0.85F;
      }

      if (this.getMoodles().getMoodleLevel(MoodleType.HeavyLoad) > 0) {
    float var2 = this.getInventory().getCapacityWeight();
    float var3 = this.getMaxWeight();
    float var4 = Math.min(2.0F, var2 / var3) - 1.0F;
         var1 *= 0.65F + 0.35F * (1.0F - var4);
      }

    return var1;
   }

    bool isGhostMode() {
      return this.isInvisible();
   }

    void setGhostMode(bool var1) {
      this.setInvisible(var1);
   }

    bool isSeeEveryone() {
      return Core.bDebug && DebugOptions.instance.CheatPlayerSeeEveryone.getValue();
   }

    bool zombiesSwitchOwnershipEachUpdate() {
      return SystemDisabler.zombiesSwitchOwnershipEachUpdate;
   }

    Vector2 getPlayerMoveDir() {
      return this.playerMoveDir;
   }

    void setPlayerMoveDir(Vector2 var1) {
      this.playerMoveDir.set(var1);
   }

    void MoveUnmodded(Vector2 var1) {
      if (this.getSlowFactor() > 0.0F) {
         var1.x = var1.x * (1.0F - this.getSlowFactor());
         var1.y = var1.y * (1.0F - this.getSlowFactor());
      }

      super.MoveUnmodded(var1);
   }

    void nullifyAiming() {
      if (this.isForceAim()) {
         this.toggleForceAim();
      }

      this.isCharging = false;
      this.setIsAiming(false);
   }

    bool isAimKeyDown() {
      if (this.PlayerIndex != 0) {
    return false;
      } else {
    int var1 = Core.getInstance().getKey("Aim");
    bool var2 = GameKeyboard.isKeyDown(var1);
         if (!var2) {
    return false;
         } else {
    bool var3 = var1 == 29 || var1 == 157;
            return !var3 || !UIManager.isMouseOverInventory();
         }
      }
   }

    void initializeStates() {
    std::unordered_map var1 = this.getStateUpdateLookup();
      var1.clear();
      if (this.getVehicle() == nullptr) {
         var1.put("actions", PlayerActionsState.instance());
         var1.put("aim", PlayerAimState.instance());
         var1.put("climbfence", ClimbOverFenceState.instance());
         var1.put("climbdownrope", ClimbDownSheetRopeState.instance());
         var1.put("climbrope", ClimbSheetRopeState.instance());
         var1.put("climbwall", ClimbOverWallState.instance());
         var1.put("climbwindow", ClimbThroughWindowState.instance());
         var1.put("emote", PlayerEmoteState.instance());
         var1.put("ext", PlayerExtState.instance());
         var1.put("sitext", PlayerExtState.instance());
         var1.put("falldown", PlayerFallDownState.instance());
         var1.put("falling", PlayerFallingState.instance());
         var1.put("getup", PlayerGetUpState.instance());
         var1.put("idle", IdleState.instance());
         var1.put("melee", SwipeStatePlayer.instance());
         var1.put("shove", SwipeStatePlayer.instance());
         var1.put("ranged", SwipeStatePlayer.instance());
         var1.put("onground", PlayerOnGroundState.instance());
         var1.put("knockeddown", PlayerKnockedDown.instance());
         var1.put("openwindow", OpenWindowState.instance());
         var1.put("closewindow", CloseWindowState.instance());
         var1.put("smashwindow", SmashWindowState.instance());
         var1.put("fishing", FishingState.instance());
         var1.put("fitness", FitnessState.instance());
         var1.put("hitreaction", PlayerHitReactionState.instance());
         var1.put("hitreactionpvp", PlayerHitReactionPVPState.instance());
         var1.put("hitreaction-hit", PlayerHitReactionPVPState.instance());
         var1.put("collide", CollideWithWallState.instance());
         var1.put("bumped", BumpedState.instance());
         var1.put("bumped-bump", BumpedState.instance());
         var1.put("sitonground", PlayerSitOnGroundState.instance());
         var1.put("strafe", PlayerStrafeState.instance());
      } else {
         var1.put("aim", PlayerAimState.instance());
         var1.put("idle", IdleState.instance());
         var1.put("melee", SwipeStatePlayer.instance());
         var1.put("shove", SwipeStatePlayer.instance());
         var1.put("ranged", SwipeStatePlayer.instance());
      }
   }

    ActionContext getActionContext() {
      return this.actionContext;
   }

    void onAnimPlayerCreated(AnimationPlayer var1) {
      super.onAnimPlayerCreated(var1);
      var1.addBoneReparent("Bip01_L_Thigh", "Bip01");
      var1.addBoneReparent("Bip01_R_Thigh", "Bip01");
      var1.addBoneReparent("Bip01_L_Clavicle", "Bip01_Spine1");
      var1.addBoneReparent("Bip01_R_Clavicle", "Bip01_Spine1");
      var1.addBoneReparent("Bip01_Prop1", "Bip01_R_Hand");
      var1.addBoneReparent("Bip01_Prop2", "Bip01_L_Hand");
   }

    std::string GetAnimSetName() {
      return this.getVehicle() == nullptr ? "player" : "player-vehicle";
   }

    bool IsInMeleeAttack() {
      return this.isCurrentState(SwipeStatePlayer.instance());
   }

    void load(ByteBuffer var1, int var2, bool var3) {
    uint8_t var4 = var1.get();
    uint8_t var5 = var1.get();
      super.load(var1, var2, var3);
      this.setHoursSurvived(var1.getDouble());
    SurvivorDesc var6 = this.descriptor;
      this.setFemale(var6.isFemale());
      this.InitSpriteParts(var6);
      this.SpeakColour = std::make_shared<Color>(Rand.Next(135) + 120, Rand.Next(135) + 120, Rand.Next(135) + 120, 255);
      if (GameClient.bClient) {
         if (Core.getInstance().getMpTextColor() != nullptr) {
            this.SpeakColour = std::make_shared<Color>(
               Core.getInstance().getMpTextColor().r, Core.getInstance().getMpTextColor().g, Core.getInstance().getMpTextColor().b, 1.0F
            );
         } else {
            Core.getInstance().setMpTextColor(std::make_shared<ColorInfo>(this.SpeakColour.r, this.SpeakColour.g, this.SpeakColour.b, 1.0F));

            try {
               Core.getInstance().saveOptions();
            } catch (IOException var15) {
               var15.printStackTrace();
            }
         }
      }

      this.setZombieKills(var1.getInt());
    std::vector var7 = this.savedInventoryItems;
    uint8_t var8 = var1.get();

      for (int var9 = 0; var9 < var8; var9++) {
    std::string var10 = GameWindow.ReadString(var1);
    short var11 = var1.getShort();
         if (var11 >= 0 && var11 < var7.size() && this.wornItems.getBodyLocationGroup().getLocation(var10) != nullptr) {
            this.wornItems.setItem(var10, (InventoryItem)var7.get(var11));
         }
      }

    short var16 = var1.getShort();
      if (var16 >= 0 && var16 < var7.size()) {
         this.leftHandItem = (InventoryItem)var7.get(var16);
      }

      var16 = var1.getShort();
      if (var16 >= 0 && var16 < var7.size()) {
         this.rightHandItem = (InventoryItem)var7.get(var16);
      }

      this.setVariable("Weapon", WeaponType.getWeaponType(this).type);
      this.setSurvivorKills(var1.getInt());
      this.initSpritePartsEmpty();
      this.nutrition.load(var1);
      this.setAllChatMuted(var1.get() == 1);
      this.tagPrefix = GameWindow.ReadString(var1);
      this.setTagColor(std::make_shared<ColorInfo>(var1.getFloat(), var1.getFloat(), var1.getFloat(), 1.0F));
      this.setDisplayName(GameWindow.ReadString(var1));
      this.showTag = var1.get() == 1;
      this.factionPvp = var1.get() == 1;
      if (var2 >= 176) {
         this.noClip = var1.get() == 1;
      }

      if (var1.get() == 1) {
         this.savedVehicleX = var1.getFloat();
         this.savedVehicleY = var1.getFloat();
         this.savedVehicleSeat = var1.get();
         this.savedVehicleRunning = var1.get() == 1;
         this.z = 0.0F;
      }

    int var18 = var1.getInt();

      for (int var19 = 0; var19 < var18; var19++) {
         this.mechanicsItem.put(var1.getLong(), var1.getLong());
      }

      this.fitness.load(var1, var2);
      if (var2 >= 184) {
    short var20 = var1.getShort();

         for (int var12 = 0; var12 < var20; var12++) {
    short var13 = var1.getShort();
    std::string var14 = WorldDictionary.getItemTypeFromID(var13);
            if (var14 != nullptr) {
               this.alreadyReadBook.push_back(var14);
            }
         }
      } else if (var2 >= 182) {
    int var21 = var1.getInt();

         for (int var22 = 0; var22 < var21; var22++) {
            this.alreadyReadBook.push_back(GameWindow.ReadString(var1));
         }
      }

      if (var2 >= 189) {
         this.loadKnownMediaLines(var1, var2);
      }
   }

    void save(ByteBuffer var1, bool var2) {
    IsoPlayer var3 = instance;
      instance = this;

      try {
         super.save(var1, var2);
      } finally {
         instance = var3;
      }

      var1.putDouble(this.getHoursSurvived());
      var1.putInt(this.getZombieKills());
      if (this.wornItems.size() > 127) {
         throw RuntimeException("too many worn items");
      } else {
         var1.put((byte)this.wornItems.size());
         this.wornItems.forEach(var2x -> {
            GameWindow.WriteString(var1, var2x.getLocation());
            var1.putShort((short)this.savedInventoryItems.indexOf(var2x.getItem()));
         });
         var1.putShort((short)this.savedInventoryItems.indexOf(this.getPrimaryHandItem()));
         var1.putShort((short)this.savedInventoryItems.indexOf(this.getSecondaryHandItem()));
         var1.putInt(this.getSurvivorKills());
         this.nutrition.save(var1);
         var1.put((byte)(this.isAllChatMuted() ? 1 : 0));
         GameWindow.WriteString(var1, this.tagPrefix);
         var1.putFloat(this.getTagColor().r);
         var1.putFloat(this.getTagColor().g);
         var1.putFloat(this.getTagColor().b);
         GameWindow.WriteString(var1, this.displayName);
         var1.put((byte)(this.showTag ? 1 : 0));
         var1.put((byte)(this.factionPvp ? 1 : 0));
         var1.put((byte)(this.isNoClip() ? 1 : 0));
         if (this.vehicle != nullptr) {
            var1.put((byte)1);
            var1.putFloat(this.vehicle.x);
            var1.putFloat(this.vehicle.y);
            var1.put((byte)this.vehicle.getSeat(this));
            var1.put((byte)(this.vehicle.isEngineRunning() ? 1 : 0));
         } else {
            var1.put((byte)0);
         }

         var1.putInt(this.mechanicsItem.size());

         for (int64_t var5 : this.mechanicsItem.keySet()) {
            var1.putLong(var5);
            var1.putLong(this.mechanicsItem.get(var5));
         }

         this.fitness.save(var1);
         var1.putShort((short)this.alreadyReadBook.size());

         for (int var8 = 0; var8 < this.alreadyReadBook.size(); var8++) {
            var1.putShort(WorldDictionary.getItemRegistryID(this.alreadyReadBook.get(var8)));
         }

         this.saveKnownMediaLines(var1);
      }
   }

    void save() {
      /* synchronized - TODO: add std::mutex */ (SliceY.SliceBufferLock) {
    ByteBuffer var2 = SliceY.SliceBuffer;
         var2.clear();
         var2.put((byte)80);
         var2.put((byte)76);
         var2.put((byte)89);
         var2.put((byte)82);
         var2.putInt(195);
         GameWindow.WriteString(var2, this.bMultiplayer ? ServerOptions.instance.ServerPlayerID.getValue() : "");
         var2.putInt((int)(this.x / 10.0F));
         var2.putInt((int)(this.y / 10.0F));
         var2.putInt((int)this.x);
         var2.putInt((int)this.y);
         var2.putInt((int)this.z);
         this.save(var2);
    File var3 = std::make_shared<File>(ZomboidFileSystem.instance.getFileNameInCurrentSave("map_p.bin"));
         if (!Core.getInstance().isNoSave()) {
            try (
    FileOutputStream var4 = std::make_shared<FileOutputStream>(var3);
    BufferedOutputStream var5 = std::make_shared<BufferedOutputStream>(var4);
            ) {
               var5.write(var2.array(), 0, var2.position());
            }
         }

         if (this.getVehicle() != nullptr && !GameClient.bClient) {
            VehiclesDB2.instance.updateVehicleAndTrailer(this.getVehicle());
         }
      }
   }

    void save(const std::string& var1) {
      this.SaveFileName = var1;
      /* synchronized - TODO: add std::mutex */ (SliceY.SliceBufferLock) {
         SliceY.SliceBuffer.clear();
         SliceY.SliceBuffer.putInt(195);
         GameWindow.WriteString(SliceY.SliceBuffer, this.bMultiplayer ? ServerOptions.instance.ServerPlayerID.getValue() : "");
         this.save(SliceY.SliceBuffer);
    File var3 = std::make_shared<File>(var1).getAbsoluteFile();

         try (
    FileOutputStream var4 = std::make_shared<FileOutputStream>(var3);
    BufferedOutputStream var5 = std::make_shared<BufferedOutputStream>(var4);
         ) {
            var5.write(SliceY.SliceBuffer.array(), 0, SliceY.SliceBuffer.position());
         }
      }
   }

    void load(const std::string& var1) {
    File var2 = std::make_shared<File>(var1).getAbsoluteFile();
      if (var2.exists()) {
         this.SaveFileName = var1;

         try (
    FileInputStream var3 = std::make_shared<FileInputStream>(var2);
    BufferedInputStream var4 = std::make_shared<BufferedInputStream>(var3);
         ) {
            /* synchronized - TODO: add std::mutex */ (SliceY.SliceBufferLock) {
               SliceY.SliceBuffer.clear();
    int var6 = var4.read(SliceY.SliceBuffer.array());
               SliceY.SliceBuffer.limit(var6);
    int var7 = SliceY.SliceBuffer.getInt();
               if (var7 >= 69) {
                  this.SaveFileIP = GameWindow.ReadStringUTF(SliceY.SliceBuffer);
                  if (var7 < 71) {
                     this.SaveFileIP = ServerOptions.instance.ServerPlayerID.getValue();
                  }
               } else if (GameClient.bClient) {
                  this.SaveFileIP = ServerOptions.instance.ServerPlayerID.getValue();
               }

               this.load(SliceY.SliceBuffer, var7);
            }
         }
      }
   }

    void removeFromWorld() {
      this.getEmitter().stopOrTriggerSoundByName("BurningFlesh");
      this.removedFromWorldMS = System.currentTimeMillis();
      if (!RecentlyRemoved.contains(this)) {
         RecentlyRemoved.push_back(this);
      }

      super.removeFromWorld();
   }

    static void UpdateRemovedEmitters() {
    IsoCell var0 = IsoWorld.instance.CurrentCell;
    long var1 = System.currentTimeMillis();

      for (int var3 = RecentlyRemoved.size() - 1; var3 >= 0; var3--) {
    IsoPlayer var4 = RecentlyRemoved.get(var3);
         if ((var0.getObjectList().contains(var4) || var0.getAddList().contains(var4)) && !var0.getRemoveList().contains(var4)) {
            RecentlyRemoved.remove(var3);
         } else {
            var4.getFMODParameters().update();
            var4.getEmitter().tick();
            if (var1 - var4.removedFromWorldMS > 5000L) {
               var4.getEmitter().stopAll();
               RecentlyRemoved.remove(var3);
            }
         }
      }
   }

    static void Reset() {
      RecentlyRemoved.clear();
   }

    void setVehicle4TestCollision(BaseVehicle var1) {
      this.vehicle4testCollision = var1;
   }

    bool isSaveFileInUse() {
      for (int var1 = 0; var1 < numPlayers; var1++) {
    IsoPlayer var2 = players[var1];
         if (var2 != nullptr) {
            if (this.sqlID != -1 && this.sqlID == var2.sqlID) {
    return true;
            }

            if (this.SaveFileName != nullptr && this.SaveFileName == var2.SaveFileName)) {
    return true;
            }
         }
      }

    return false;
   }

    void removeSaveFile() {
      try {
         if (PlayerDB.isAvailable()) {
            PlayerDB.getInstance().saveLocalPlayersForce();
         }

         if (this.isNPC() && this.SaveFileName != nullptr) {
    File var1 = std::make_shared<File>(this.SaveFileName).getAbsoluteFile();
            if (var1.exists()) {
               var1.delete();
            }
         }
      } catch (Exception var2) {
         ExceptionLogger.logException(var2);
      }
   }

    bool isSaveFileIPValid() {
    return isServerPlayerIDValid();
   }

    std::string getObjectName() {
      return "Player";
   }

    int getJoypadBind() {
      return this.JoypadBind;
   }

    bool isLBPressed() {
      return this.JoypadBind == -1 ? false : JoypadManager.instance.isLBPressed(this.JoypadBind);
   }

    Vector2 getControllerAimDir(Vector2 var1) {
      if (GameWindow.ActivatedJoyPad != nullptr && this.JoypadBind != -1 && this.bJoypadMovementActive) {
    float var2 = JoypadManager.instance.getAimingAxisX(this.JoypadBind);
    float var3 = JoypadManager.instance.getAimingAxisY(this.JoypadBind);
         if (this.bJoypadIgnoreAimUntilCentered) {
            if (var1.set(var2, var3).getLengthSquared() > 0.0F) {
               return var1.set(0.0F, 0.0F);
            }

            this.bJoypadIgnoreAimUntilCentered = false;
         }

         if (var1.set(var2, var3).getLength() < 0.3F) {
            var3 = 0.0F;
            var2 = 0.0F;
         }

         if (var2 == 0.0F && var3 == 0.0F) {
            return var1.set(0.0F, 0.0F);
         }

         var1.set(var2, var3);
         var1.normalize();
         var1.rotate((float) (-Math.PI / 4));
      }

    return var1;
   }

    Vector2 getMouseAimVector(Vector2 var1) {
    int var2 = Mouse.getX();
    int var3 = Mouse.getY();
      var1.x = IsoUtils.XToIso(var2, var3 + 55.0F * this.def.getScaleY(), this.getZ()) - this.getX();
      var1.y = IsoUtils.YToIso(var2, var3 + 55.0F * this.def.getScaleY(), this.getZ()) - this.getY();
      var1.normalize();
    return var1;
   }

    Vector2 getAimVector(Vector2 var1) {
      return this.JoypadBind == -1 ? this.getMouseAimVector(var1) : this.getControllerAimDir(var1);
   }

    float getGlobalMovementMod(bool var1) {
      return !this.isGhostMode() && !this.isNoClip() ? super.getGlobalMovementMod(var1) : 1.0F;
   }

    bool isInTrees2(bool var1) {
      return !this.isGhostMode() && !this.isNoClip() ? super.isInTrees2(var1) : false;
   }

    float getMoveSpeed() {
    float var1 = 1.0F;

      for (int var2 = BodyPartType.ToIndex(BodyPartType.UpperLeg_L); var2 <= BodyPartType.ToIndex(BodyPartType.Foot_R); var2++) {
    BodyPart var3 = this.getBodyDamage().getBodyPart(BodyPartType.FromIndex(var2));
    float var4 = 1.0F;
         if (var3.getFractureTime() > 20.0F) {
            var4 = 0.4F;
            if (var3.getFractureTime() > 50.0F) {
               var4 = 0.3F;
            }

            if (var3.getSplintFactor() > 0.0F) {
               var4 += var3.getSplintFactor() / 10.0F;
            }
         }

         if (var3.getFractureTime() < 20.0F && var3.getSplintFactor() > 0.0F) {
            var4 = 0.8F;
         }

         if (var4 > 0.7F && var3.getDeepWoundTime() > 0.0F) {
            var4 = 0.7F;
            if (var3.bandaged()) {
               var4 += 0.2F;
            }
         }

         if (var4 < var1) {
            var1 = var4;
         }
      }

      if (var1 != 1.0F) {
         return this.MoveSpeed * var1;
      } else if (this.getMoodles().getMoodleLevel(MoodleType.Panic) >= 4 && this.Traits.AdrenalineJunkie.isSet()) {
    float var5 = 1.0F;
    int var7 = this.getMoodles().getMoodleLevel(MoodleType.Panic) + 1;
         var5 += var7 / 50.0F;
         return this.MoveSpeed * var5;
      } else {
         return this.MoveSpeed;
      }
   }

    void setMoveSpeed(float var1) {
      this.MoveSpeed = var1;
   }

    float getTorchStrength() {
      if (this.bRemote) {
         return this.mpTorchStrength;
      } else {
    InventoryItem var1 = this.getActiveLightItem();
         return var1 != nullptr ? var1.getLightStrength() : 0.0F;
      }
   }

    float getInvAimingMod() {
    int var1 = this.getPerkLevel(Perks.Aiming);
      if (var1 == 1) {
         return 0.9F;
      } else if (var1 == 2) {
         return 0.86F;
      } else if (var1 == 3) {
         return 0.82F;
      } else if (var1 == 4) {
         return 0.74F;
      } else if (var1 == 5) {
         return 0.7F;
      } else if (var1 == 6) {
         return 0.66F;
      } else if (var1 == 7) {
         return 0.62F;
      } else if (var1 == 8) {
         return 0.58F;
      } else if (var1 == 9) {
         return 0.54F;
      } else {
    return var1 = = 10 ? 0.5F : 0.9F;
      }
   }

    float getAimingMod() {
    int var1 = this.getPerkLevel(Perks.Aiming);
      if (var1 == 1) {
         return 1.1F;
      } else if (var1 == 2) {
         return 1.14F;
      } else if (var1 == 3) {
         return 1.18F;
      } else if (var1 == 4) {
         return 1.22F;
      } else if (var1 == 5) {
         return 1.26F;
      } else if (var1 == 6) {
         return 1.3F;
      } else if (var1 == 7) {
         return 1.34F;
      } else if (var1 == 8) {
         return 1.36F;
      } else if (var1 == 9) {
         return 1.4F;
      } else {
    return var1 = = 10 ? 1.5F : 1.0F;
      }
   }

    float getReloadingMod() {
    int var1 = this.getPerkLevel(Perks.Reloading);
      return 3.5F - var1 * 0.25F;
   }

    float getAimingRangeMod() {
    int var1 = this.getPerkLevel(Perks.Aiming);
      if (var1 == 1) {
         return 1.2F;
      } else if (var1 == 2) {
         return 1.28F;
      } else if (var1 == 3) {
         return 1.36F;
      } else if (var1 == 4) {
         return 1.42F;
      } else if (var1 == 5) {
         return 1.5F;
      } else if (var1 == 6) {
         return 1.58F;
      } else if (var1 == 7) {
         return 1.66F;
      } else if (var1 == 8) {
         return 1.72F;
      } else if (var1 == 9) {
         return 1.8F;
      } else {
    return var1 = = 10 ? 2.0F : 1.1F;
      }
   }

    bool isPathfindRunning() {
      return this.pathfindRun;
   }

    void setPathfindRunning(bool var1) {
      this.pathfindRun = var1;
   }

    bool isBannedAttacking() {
      return this.bBannedAttacking;
   }

    void setBannedAttacking(bool var1) {
      this.bBannedAttacking = var1;
   }

    float getInvAimingRangeMod() {
    int var1 = this.getPerkLevel(Perks.Aiming);
      if (var1 == 1) {
         return 0.8F;
      } else if (var1 == 2) {
         return 0.7F;
      } else if (var1 == 3) {
         return 0.62F;
      } else if (var1 == 4) {
         return 0.56F;
      } else if (var1 == 5) {
         return 0.45F;
      } else if (var1 == 6) {
         return 0.38F;
      } else if (var1 == 7) {
         return 0.31F;
      } else if (var1 == 8) {
         return 0.24F;
      } else if (var1 == 9) {
         return 0.17F;
      } else {
    return var1 = = 10 ? 0.1F : 0.8F;
      }
   }

    void updateCursorVisibility() {
      if (this.isAiming()) {
         if (this.PlayerIndex == 0 && this.JoypadBind == -1 && !this.isDead()) {
            if (!Core.getInstance().getOptionShowCursorWhileAiming()) {
               if (Core.getInstance().getIsoCursorVisibility() != 0) {
                  if (!UIManager.isForceCursorVisible()) {
    int var1 = Mouse.getXA();
    int var2 = Mouse.getYA();
                     if (var1 >= IsoCamera.getScreenLeft(0) && var1 <= IsoCamera.getScreenLeft(0) + IsoCamera.getScreenWidth(0)) {
                        if (var2 >= IsoCamera.getScreenTop(0) && var2 <= IsoCamera.getScreenTop(0) + IsoCamera.getScreenHeight(0)) {
                           Mouse.setCursorVisible(false);
                        }
                     }
                  }
               }
            }
         }
      }
   }

    void render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      if (DebugOptions.instance.char.Debug.Render.DisplayRoomAndZombiesZone.getValue()) {
    std::string var8 = "";
         if (this.getCurrentRoomDef() != nullptr) {
            var8 = this.getCurrentRoomDef().name;
         }

    Zone var9 = ZombiesZoneDefinition.getDefinitionZoneAt((int)var1, (int)var2, (int)var3);
         if (var9 != nullptr) {
            var8 = var8 + " - " + var9.name + " / " + var9.type;
         }

         this.Say(var8);
      }

      if (!getInstance().checkCanSeeClient(this)) {
         this.setTargetAlpha(0.0F);
         getInstance().spottedPlayerTimer.remove(this.getRemoteID());
      } else {
         this.setTargetAlpha(1.0F);
      }

      super.render(var1, var2, var3, var4, var5, var6, var7);
   }

    void renderlast() {
      super.renderlast();
      if (DebugOptions.instance.char.Debug.Render.FMODRoomType.getValue() && this.isLocalPlayer()) {
         ParameterRoomType.render(this);
      }
   }

    float doBeatenVehicle(float var1) {
      if (GameClient.bClient && this.isLocalPlayer()) {
         this.changeState(ForecastBeatenPlayerState.instance());
         return 0.0F;
      } else if (!GameClient.bClient && !this.isLocalPlayer()) {
         return 0.0F;
      } else {
    float var2 = this.getDamageFromHitByACar(var1);
         LuaEventManager.triggerEvent("OnPlayerGetDamage", this, "CARHITDAMAGE", var2);
         if (this.isAlive()) {
            if (GameClient.bClient) {
               if (this.isCurrentState(PlayerSitOnGroundState.instance())) {
                  this.setKnockedDown(true);
                  this.setReanimateTimer(20.0F);
               } else if (!this.isOnFloor()
                  && !(var1 > 15.0F)
                  && !this.isCurrentState(PlayerHitReactionState.instance())
                  && !this.isCurrentState(PlayerGetUpState.instance())
                  && !this.isCurrentState(PlayerOnGroundState.instance())) {
                  this.setHitReaction("HitReaction");
                  this.actionContext.reportEvent("washit");
                  this.setVariable("hitpvp", false);
               } else {
                  this.setHitReaction("HitReaction");
                  this.actionContext.reportEvent("washit");
                  this.setVariable("hitpvp", false);
                  this.setKnockedDown(true);
                  this.setReanimateTimer(20.0F);
               }
            } else if (this.getCurrentState() != PlayerHitReactionState.instance()
               && this.getCurrentState() != PlayerFallDownState.instance()
               && this.getCurrentState() != PlayerOnGroundState.instance()
               && !this.isKnockedDown()) {
               if (var2 > 15.0F) {
                  this.setKnockedDown(true);
                  this.setReanimateTimer(20 + Rand.Next(60));
               }

               this.setHitReaction("HitReaction");
               this.actionContext.reportEvent("washit");
            }
         }

    return var2;
      }
   }

    void update() {
      s_performance.update.invokeAndMeasure(this, IsoPlayer::updateInternal1);
   }

    void updateInternal1() {
      if (GameClient.bClient && !this.isLocal() && System.currentTimeMillis() - this.lastRemoteUpdate > 5000L) {
         GameClient.receivePlayerTimeout(this.OnlineID);
      }

      if (this.replay != nullptr) {
         this.replay.update();
      }

    bool var1 = this.updateInternal2();
      GameClient.instance.sendPlayer2(this);
      if (var1) {
         if (!this.bRemote) {
            this.updateLOS();
         }

         super.update();
      }
   }

    void setBeenMovingSprinting() {
      if (this.isJustMoved()) {
         this.setBeenMovingFor(this.getBeenMovingFor() + 1.25F * GameTime.getInstance().getMultiplier());
      } else {
         this.setBeenMovingFor(this.getBeenMovingFor() - 0.625F * GameTime.getInstance().getMultiplier());
      }

      if (this.isJustMoved() && this.isSprinting()) {
         this.setBeenSprintingFor(this.getBeenSprintingFor() + 1.25F * GameTime.getInstance().getMultiplier());
      } else {
         this.setBeenSprintingFor(0.0F);
      }
   }

    bool updateInternal2() {
      if (isTestAIMode) {
         this.isNPC = true;
      }

      if (!this.attackStarted) {
         this.setInitiateAttack(false);
         this.setAttackType(nullptr);
      }

      if ((this.isRunning() || this.isSprinting()) && this.getDeferredMovement(tempo).getLengthSquared() > 0.0F) {
         this.runningTime = this.runningTime + GameTime.getInstance().getMultiplier() / 1.6F;
      } else {
         this.runningTime = 0.0F;
      }

      if (this.getLastCollideTime() > 0.0F) {
         this.setLastCollideTime(this.getLastCollideTime() - GameTime.getInstance().getMultiplier() / 1.6F);
      }

      this.updateDeathDragDown();
      this.updateGodModeKey();
      if (GameClient.bClient) {
         this.networkAI.update();
      }

      this.doDeferredMovement();
      if (GameServer.bServer) {
         this.vehicle4testCollision = nullptr;
      } else if (GameClient.bClient) {
         if (this.vehicle4testCollision != nullptr) {
            if (!this.isLocal()) {
               this.vehicle4testCollision.updateHitByVehicle(this);
            }

            this.vehicle4testCollision = nullptr;
         }
      } else {
         this.updateHitByVehicle();
         this.vehicle4testCollision = nullptr;
      }

      this.updateEmitter();
      this.updateMechanicsItems();
      this.updateHeavyBreathing();
      this.updateTemperatureCheck();
      this.updateAimingStance();
      if (SystemDisabler.doCharacterStats) {
         this.nutrition.update();
      }

      this.fitness.update();
      this.updateSoundListener();
      SafetySystemManager.update(this);
      if (!GameClient.bClient && !GameServer.bServer && this.bDeathFinished) {
    return false;
      } else {
         if (!GameClient.bClient && this.getCurrentBuildingDef() != nullptr && !this.isInvisible()) {
            this.getCurrentBuildingDef().setHasBeenVisited(true);
         }

         if (this.checkSafehouse > 0 && GameServer.bServer) {
            this.checkSafehouse--;
            if (this.checkSafehouse == 0) {
               this.checkSafehouse = 200;
    SafeHouse var1 = SafeHouse.isSafeHouse(this.getCurrentSquare(), nullptr, false);
               if (var1 != nullptr) {
                  var1.updateSafehouse(this);
                  var1.checkTrespass(this);
               }
            }
         }

         if (this.bRemote && this.TimeSinceLastNetData > 600) {
            IsoWorld.instance.CurrentCell.getObjectList().remove(this);
            if (this.movingSq != nullptr) {
               this.movingSq.getMovingObjects().remove(this);
            }
         }

         this.TimeSinceLastNetData = (int)(this.TimeSinceLastNetData + GameTime.instance.getMultiplier());
         this.TimeSinceOpenDoor = this.TimeSinceOpenDoor + GameTime.instance.getMultiplier();
         this.lastTargeted = this.lastTargeted + GameTime.instance.getMultiplier();
         this.targetedByZombie = false;
         this.checkActionGroup();
         if (this.updateRemotePlayer()) {
            if (this.updateWhileDead()) {
    return true;
            } else {
               this.updateHeartSound();
               this.checkIsNearWall();
               this.updateExt();
               this.setBeenMovingSprinting();
    return true;
            }
         } else {
            assert !GameServer.bServer;

            assert !this.bRemote;

            assert !GameClient.bClient || this.isLocalPlayer();

            IsoCamera.CamCharacter = this;
            instance = this;
            if (this.isLocalPlayer()) {
               IsoCamera.cameras[this.PlayerIndex].update();
               if (UIManager.getMoodleUI(this.PlayerIndex) != nullptr) {
                  UIManager.getMoodleUI(this.PlayerIndex).setCharacter(this);
               }
            }

            if (this.closestZombie > 1.2F) {
               this.slowTimer = -1.0F;
               this.slowFactor = 0.0F;
            }

            this.ContextPanic = this.ContextPanic - 1.5F * GameTime.instance.getTimeDelta();
            if (this.ContextPanic < 0.0F) {
               this.ContextPanic = 0.0F;
            }

            this.lastSeenZombieTime = this.lastSeenZombieTime + GameTime.instance.getGameWorldSecondsSinceLastUpdate() / 60.0F / 60.0F;
            LuaEventManager.triggerEvent("OnPlayerUpdate", this);
            if (this.pressedMovement(false)) {
               this.ContextPanic = 0.0F;
               this.ticksSincePressedMovement = 0.0F;
            } else {
               this.ticksSincePressedMovement = this.ticksSincePressedMovement + GameTime.getInstance().getMultiplier() / 1.6F;
            }

            this.setVariable("pressedMovement", this.pressedMovement(true));
            if (this.updateWhileDead()) {
    return true;
            } else {
               this.updateHeartSound();
               this.updateEquippedBaggageContainer();
               this.updateWorldAmbiance();
               this.updateSneakKey();
               this.checkIsNearWall();
               this.updateExt();
               this.updateInteractKeyPanic();
               if (this.isAsleep()) {
                  this.m_isPlayerMoving = false;
               }

               if ((
                     this.getVehicle() == nullptr
                        || !this.getVehicle().isDriver(this)
                        || !this.getVehicle().hasHorn()
                        || Core.getInstance().getKey("Shout") != Core.getInstance().getKey("VehicleHorn")
                  )
                  && !this.isAsleep()
                  && this.PlayerIndex == 0
                  && !this.Speaking
                  && GameKeyboard.isKeyDown(Core.getInstance().getKey("Shout"))
                  && !this.isNPC) {
               }

               if (this.getIgnoreMovement() || this.isAsleep()) {
    return true;
               } else if (this.checkActionsBlockingMovement()) {
                  if (this.getVehicle() != nullptr && this.getVehicle().getDriver() == this && this.getVehicle().getController() != nullptr) {
                     this.getVehicle().getController().clientControls.reset();
                     this.getVehicle().updatePhysics();
                  }

    return true;
               } else {
                  this.enterExitVehicle();
                  this.checkActionGroup();
                  this.checkReloading();
                  this.checkWalkTo();
                  if (this.checkActionsBlockingMovement()) {
    return true;
                  } else if (this.getVehicle() != nullptr) {
                     this.updateWhileInVehicle();
    return true;
                  } else {
                     this.checkVehicleContainers();
                     this.setCollidable(true);
                     this.updateCursorVisibility();
                     this.bSeenThisFrame = false;
                     this.bCouldBeSeenThisFrame = false;
                     if (IsoCamera.CamCharacter == nullptr && GameClient.bClient) {
                        IsoCamera.CamCharacter = instance;
                     }

                     if (this.updateUseKey()) {
    return true;
                     } else {
                        this.updateEnableModelsKey();
                        this.updateChangeCharacterKey();
    bool var12 = false;
    bool var2 = false;
                        this.setRunning(false);
                        this.setSprinting(false);
                        this.useChargeTime = this.chargeTime;
                        if (!this.isBlockMovement() && !this.isNPC) {
                           if (!this.isCharging && !this.isChargingLT) {
                              this.chargeTime = 0.0F;
                           } else {
                              this.chargeTime = this.chargeTime + 1.0F * GameTime.instance.getMultiplier();
                           }

                           this.UpdateInputState(this.inputState);
                           var2 = this.inputState.bMelee;
                           var12 = this.inputState.isAttacking;
                           this.setRunning(this.inputState.bRunning);
                           this.setSprinting(this.inputState.bSprinting);
                           if (this.isSprinting() && !this.isJustMoved()) {
                              this.setSprinting(false);
                           }

                           if (this.isSprinting()) {
                              this.setRunning(false);
                           }

                           if (this.inputState.bSprinting && !this.isSprinting()) {
                              this.setRunning(true);
                           }

                           this.setIsAiming(this.inputState.isAiming);
                           this.isCharging = this.inputState.isCharging;
                           this.isChargingLT = this.inputState.isChargingLT;
                           this.updateMovementRates();
                           if (this.isAiming()) {
                              this.StopAllActionQueueAiming();
                           }

                           if (var12) {
                              this.setIsAiming(true);
                           }

                           this.Waiting = false;
                           if (this.isAiming()) {
                              this.setMoving(false);
                              this.setRunning(false);
                              this.setSprinting(false);
                           }

                           this.TicksSinceSeenZombie++;
                        }

                        if (this.playerMoveDir.x == 0.0 && this.playerMoveDir.y == 0.0) {
                           this.setForceRun(false);
                           this.setForceSprint(false);
                        }

                        this.movementLastFrame.x = this.playerMoveDir.x;
                        this.movementLastFrame.y = this.playerMoveDir.y;
                        if (this.stateMachine.getCurrent() != StaggerBackState.instance()
                           && this.stateMachine.getCurrent() != FakeDeadZombieState.instance()
                           && UIManager.speedControls != nullptr) {
                           if (GameKeyboard.isKeyDown(88) && Translator.debug) {
                              Translator.loadFiles();
                           }

                           this.setJustMoved(false);
    MoveVars var3 = s_moveVars;
                           this.updateMovementFromInput(var3);
                           if (!this.JustMoved && this.hasPath() && !this.getPathFindBehavior2().bStopping) {
                              this.JustMoved = true;
                           }

    float var4 = var3.strafeX;
    float var5 = var3.strafeY;
                           if (this.isJustMoved() && !this.isNPC && !this.hasPath()) {
                              if (UIManager.getSpeedControls().getCurrentGameSpeed() > 1) {
                                 UIManager.getSpeedControls().SetCurrentGameSpeed(1);
                              }
                           } else if (this.stats.endurance < this.stats.endurancedanger && Rand.Next((int)(300.0F * GameTime.instance.getInvMultiplier())) == 0
                              )
                            {
                              this.xp.AddXP(Perks.Fitness, 1.0F);
                           }

                           this.setBeenMovingSprinting();
    float var6 = 1.0F;
    float var7 = 0.0F;
                           if (this.isJustMoved() && !this.isNPC) {
                              if (!this.isRunning() && !this.isSprinting()) {
                                 var7 = 1.0F;
                              } else {
                                 var7 = 1.5F;
                              }
                           }

                           var6 *= var7;
                           if (var6 > 1.0F) {
                              var6 *= this.getSprintMod();
                           }

                           if (var6 > 1.0F && this.Traits.Athletic.isSet()) {
                              var6 *= 1.2F;
                           }

                           if (var6 > 1.0F) {
                              if (this.Traits.Overweight.isSet()) {
                                 var6 *= 0.99F;
                              }

                              if (this.Traits.Obese.isSet()) {
                                 var6 *= 0.85F;
                              }

                              if (this.getNutrition().getWeight() > 120.0) {
                                 var6 *= 0.97F;
                              }

                              if (this.Traits.OutOfShape.isSet()) {
                                 var6 *= 0.99F;
                              }

                              if (this.Traits.Unfit.isSet()) {
                                 var6 *= 0.8F;
                              }
                           }

                           this.updateEndurance(var6);
                           if (this.isAiming() && this.isJustMoved()) {
                              var6 *= 0.7F;
                           }

                           if (this.isAiming()) {
                              var6 *= this.getNimbleMod();
                           }

                           this.isWalking = false;
                           if (var6 > 0.0F && !this.isNPC) {
                              this.isWalking = true;
                              LuaEventManager.triggerEvent("OnPlayerMove", this);
                           }

                           if (this.isJustMoved()) {
                              this.sprite.Animate = true;
                           }

                           if (this.isNPC && this.GameCharacterAIBrain != nullptr) {
                              var2 = this.GameCharacterAIBrain.HumanControlVars.bMelee;
                              this.bBannedAttacking = this.GameCharacterAIBrain.HumanControlVars.bBannedAttacking;
                           }

                           this.m_meleePressed = var2;
                           if (var2) {
                              if (!this.m_lastAttackWasShove) {
                                 this.setMeleeDelay(Math.min(this.getMeleeDelay(), 2.0F));
                              }

                              if (!this.bBannedAttacking && this.isAuthorizeShoveStomp() && this.CanAttack() && this.getMeleeDelay() <= 0.0F) {
                                 this.setDoShove(true);
                                 if (!this.isCharging && !this.isChargingLT) {
                                    this.setIsAiming(false);
                                 }

                                 this.AttemptAttack(this.useChargeTime);
                                 this.useChargeTime = 0.0F;
                                 this.chargeTime = 0.0F;
                              }
                           } else if (this.isAiming() && this.CanAttack()) {
                              if (this.DragCharacter != nullptr) {
                                 this.DragObject = nullptr;
                                 this.DragCharacter.Dragging = false;
                                 this.DragCharacter = nullptr;
                              }

                              if (var12 && !this.bBannedAttacking) {
                                 this.sprite.Animate = true;
                                 if (this.getRecoilDelay() <= 0.0F && this.getMeleeDelay() <= 0.0F) {
                                    this.AttemptAttack(this.useChargeTime);
                                 }

                                 this.useChargeTime = 0.0F;
                                 this.chargeTime = 0.0F;
                              }
                           }

                           if (this.isAiming() && !this.isNPC) {
                              if (this.JoypadBind != -1 && !this.bJoypadMovementActive) {
                                 if (this.getForwardDirection().getLengthSquared() > 0.0F) {
                                    this.DirectionFromVector(this.getForwardDirection());
                                 }
                              } else {
    Vector2 var8 = tempVector2.set(0.0F, 0.0F);
                                 if (GameWindow.ActivatedJoyPad != nullptr && this.JoypadBind != -1) {
                                    this.getControllerAimDir(var8);
                                 } else {
                                    this.getMouseAimVector(var8);
                                 }

                                 if (var8.getLengthSquared() > 0.0F) {
                                    this.DirectionFromVector(var8);
                                    this.setForwardDirection(var8);
                                 }
                              }

                              var3.NewFacing = this.dir;
                           }

                           if (this.getForwardDirection().x == 0.0F && this.getForwardDirection().y == 0.0F) {
                              this.setForwardDirection(this.dir.ToVector());
                           }

                           if (this.lastAngle.x != this.getForwardDirection().x || this.lastAngle.y != this.getForwardDirection().y) {
                              this.lastAngle.x = this.getForwardDirection().x;
                              this.lastAngle.y = this.getForwardDirection().y;
                              this.dirtyRecalcGridStackTime = 2.0F;
                           }

                           this.stats.endurance = PZMath.clamp(this.stats.endurance, 0.0F, 1.0F);
    AnimationPlayer var14 = this.getAnimationPlayer();
                           if (var14 != nullptr && var14.isReady()) {
    float var9 = var14.getAngle() + var14.getTwistAngle();
                              this.dir = IsoDirections.fromAngle(tempVector2.setLengthAndDirection(var9, 1.0F));
                           } else if (!this.bFalling && !this.isAiming() && !var12) {
                              this.dir = var3.NewFacing;
                           }

                           if (this.isAiming() && (GameWindow.ActivatedJoyPad == nullptr || this.JoypadBind == -1)) {
                              this.playerMoveDir.x = var3.moveX;
                              this.playerMoveDir.y = var3.moveY;
                           }

                           if (!this.isAiming() && this.isJustMoved()) {
                              this.playerMoveDir.x = this.getForwardDirection().x;
                              this.playerMoveDir.y = this.getForwardDirection().y;
                           }

                           if (this.isJustMoved()) {
                              if (this.isSprinting()) {
                                 this.CurrentSpeed = 1.5F;
                              } else if (this.isRunning()) {
                                 this.CurrentSpeed = 1.0F;
                              } else {
                                 this.CurrentSpeed = 0.5F;
                              }
                           } else {
                              this.CurrentSpeed = 0.0F;
                           }

    bool var15 = this.IsInMeleeAttack();
                           if (!this.CharacterActions.empty()) {
    BaseAction var10 = (BaseAction)this.CharacterActions.get(0);
                              if (var10.overrideAnimation) {
                                 var15 = true;
                              }
                           }

                           if (!var15 && !this.isForceOverrideAnim()) {
                              if (this.getPath2() == nullptr) {
                                 if (this.CurrentSpeed > 0.0F && (!this.bClimbing || this.lastFallSpeed > 0.0F)) {
                                    if (!this.isRunning() && !this.isSprinting()) {
                                       this.StopAllActionQueueWalking();
                                    } else {
                                       this.StopAllActionQueueRunning();
                                    }
                                 }
                              } else {
                                 this.StopAllActionQueueWalking();
                              }
                           }

                           if (this.slowTimer > 0.0F) {
                              this.slowTimer = this.slowTimer - GameTime.instance.getRealworldSecondsSinceLastUpdate();
                              this.CurrentSpeed = this.CurrentSpeed * (1.0F - this.slowFactor);
                              this.slowFactor = this.slowFactor - GameTime.instance.getMultiplier() / 100.0F;
                              if (this.slowFactor < 0.0F) {
                                 this.slowFactor = 0.0F;
                              }
                           } else {
                              this.slowFactor = 0.0F;
                           }

                           this.playerMoveDir.setLength(this.CurrentSpeed);
                           if (this.playerMoveDir.x != 0.0F || this.playerMoveDir.y != 0.0F) {
                              this.dirtyRecalcGridStackTime = 10.0F;
                           }

                           if (this.getPath2() != nullptr && this.current != this.last) {
                              this.dirtyRecalcGridStackTime = 10.0F;
                           }

                           this.closestZombie = 1000000.0F;
                           this.weight = 0.3F;
                           this.separate();
                           this.updateSleepingPillsTaken();
                           this.updateTorchStrength();
                           if (this.isNPC && this.GameCharacterAIBrain != nullptr) {
                              this.GameCharacterAIBrain.postUpdateHuman(this);
                              this.setInitiateAttack(this.GameCharacterAIBrain.HumanControlVars.initiateAttack);
                              this.setRunning(this.GameCharacterAIBrain.HumanControlVars.bRunning);
                              var4 = this.GameCharacterAIBrain.HumanControlVars.strafeX;
                              var5 = this.GameCharacterAIBrain.HumanControlVars.strafeY;
                              this.setJustMoved(this.GameCharacterAIBrain.HumanControlVars.JustMoved);
                              this.updateMovementRates();
                           }

                           this.m_isPlayerMoving = this.isJustMoved() || this.getPath2() != nullptr && !this.getPathFindBehavior2().bStopping;
    bool var16 = this.isInTrees();
                           if (var16) {
    float var11 = "parkranger" == this.getDescriptor().getProfession()) ? 1.3F : 1.0F;
                              var11 = "lumberjack" == this.getDescriptor().getProfession()) ? 1.15F : var11;
                              if (this.isRunning()) {
                                 var11 *= 1.1F;
                              }

                              this.setVariable("WalkSpeedTrees", var11);
                           }

                           if ((var16 || this.m_walkSpeed < 0.4F || this.m_walkInjury > 0.5F) && this.isSprinting() && !this.isGhostMode()) {
                              if (this.runSpeedModifier < 1.0) {
                                 this.setMoodleCantSprint(true);
                              }

                              this.setSprinting(false);
                              this.setRunning(true);
                              if (this.isInTreesNoBush()) {
                                 this.setForceSprint(false);
                                 this.setBumpType("left");
                                 this.setVariable("BumpDone", false);
                                 this.setVariable("BumpFall", true);
                                 this.setVariable("TripObstacleType", "tree");
                                 this.actionContext.reportEvent("wasBumped");
                              }
                           }

                           this.m_deltaX = var4;
                           this.m_deltaY = var5;
                           this.m_windspeed = ClimateManager.getInstance().getWindSpeedMovement();
    float var18 = this.getForwardDirection().getDirectionNeg();
                           this.m_windForce = ClimateManager.getInstance().getWindForceMovement(this, var18);
    return true;
                        } else {
    return true;
                        }
                     }
                  }
               }
            }
         }
      }
   }

    void updateMovementFromInput(MoveVars var1) {
      var1.moveX = 0.0F;
      var1.moveY = 0.0F;
      var1.strafeX = 0.0F;
      var1.strafeY = 0.0F;
      var1.NewFacing = this.dir;
      if (!TutorialManager.instance.StealControl) {
         if (!this.isBlockMovement()) {
            if (!this.isNPC) {
               if (!MPDebugAI.updateMovementFromInput(this, var1)) {
                  if (!(this.fallTime > 2.0F)) {
                     if (GameWindow.ActivatedJoyPad != nullptr && this.JoypadBind != -1) {
                        this.updateMovementFromJoypad(var1);
                     }

                     if (this.PlayerIndex == 0 && this.JoypadBind == -1) {
                        this.updateMovementFromKeyboardMouse(var1);
                     }

                     if (this.isJustMoved()) {
                        this.getForwardDirection().normalize();
                        UIManager.speedControls.SetCurrentGameSpeed(1);
                     }
                  }
               }
            }
         }
      }
   }

    void updateMovementFromJoypad(MoveVars var1) {
      this.playerMoveDir.x = 0.0F;
      this.playerMoveDir.y = 0.0F;
      this.getJoypadAimVector(tempVector2);
    float var2 = tempVector2.x;
    float var3 = tempVector2.y;
    Vector2 var4 = this.getJoypadMoveVector(tempVector2);
      if (var4.getLength() > 1.0F) {
         var4.setLength(1.0F);
      }

      if (this.isAutoWalk()) {
         if (var4.getLengthSquared() < 0.25F) {
            var4.set(this.getAutoWalkDirection());
         } else {
            this.setAutoWalkDirection(var4);
            this.getAutoWalkDirection().normalize();
         }
      }

    float var5 = var4.x;
    float var6 = var4.y;
      if (Math.abs(var5) > 0.0F) {
         this.playerMoveDir.x += 0.04F * var5;
         this.playerMoveDir.y -= 0.04F * var5;
         this.setJustMoved(true);
      }

      if (Math.abs(var6) > 0.0F) {
         this.playerMoveDir.y += 0.04F * var6;
         this.playerMoveDir.x += 0.04F * var6;
         this.setJustMoved(true);
      }

      this.playerMoveDir.setLength(0.05F * (float)Math.pow(var4.getLength(), 9.0));
      if (var2 != 0.0F || var3 != 0.0F) {
    Vector2 var7 = tempVector2.set(var2, var3);
         var7.normalize();
         var1.NewFacing = IsoDirections.fromAngle(var7);
      } else if ((var5 != 0.0F || var6 != 0.0F) && this.playerMoveDir.getLengthSquared() > 0.0F) {
         var4 = tempVector2.set(this.playerMoveDir);
         var4.normalize();
         var1.NewFacing = IsoDirections.fromAngle(var4);
      }

    PathFindBehavior2 var10 = this.getPathFindBehavior2();
      if (this.playerMoveDir.x == 0.0F && this.playerMoveDir.y == 0.0F && this.getPath2() != nullptr && var10.isStrafing() && !var10.bStopping) {
         this.playerMoveDir.set(var10.getTargetX() - this.x, var10.getTargetY() - this.y);
         this.playerMoveDir.normalize();
      }

      if (this.playerMoveDir.x != 0.0F || this.playerMoveDir.y != 0.0F) {
         if (this.isStrafing()) {
            tempo.set(this.playerMoveDir.x, -this.playerMoveDir.y);
            tempo.normalize();
    float var8 = this.legsSprite.modelSlot.model.AnimPlayer.getRenderedAngle();
            if (var8 > Math.PI * 2) {
               var8 = (float)(var8 - (Math.PI * 2));
            }

            if (var8 < 0.0F) {
               var8 = (float)(var8 + (Math.PI * 2));
            }

            tempo.rotate(var8);
            var1.strafeX = tempo.x;
            var1.strafeY = tempo.y;
            this.m_IPX = this.playerMoveDir.x;
            this.m_IPY = this.playerMoveDir.y;
         } else {
            var1.moveX = this.playerMoveDir.x;
            var1.moveY = this.playerMoveDir.y;
            tempo.set(this.playerMoveDir);
            tempo.normalize();
            this.setForwardDirection(tempo);
         }
      }
   }

    void updateMovementFromKeyboardMouse(MoveVars var1) {
    int var2 = Core.getInstance().getKey("Left");
    int var3 = Core.getInstance().getKey("Right");
    int var4 = Core.getInstance().getKey("Forward");
    int var5 = Core.getInstance().getKey("Backward");
    bool var6 = GameKeyboard.isKeyDown(var2);
    bool var7 = GameKeyboard.isKeyDown(var3);
    bool var8 = GameKeyboard.isKeyDown(var4);
    bool var9 = GameKeyboard.isKeyDown(var5);
      if (!var6 && !var7 && !var8 && !var9
         || var2 != 30 && var3 != 30 && var4 != 30 && var5 != 30
         || !GameKeyboard.isKeyDown(29) && !GameKeyboard.isKeyDown(157)
         || !UIManager.isMouseOverInventory()
         || !Core.getInstance().isSelectingAll()) {
         if (!this.isIgnoreInputsForDirection()) {
            if (Core.bAltMoveMethod) {
               if (var6 && !var7) {
                  var1.moveX -= 0.04F;
                  var1.NewFacing = IsoDirections.W;
               }

               if (var7 && !var6) {
                  var1.moveX += 0.04F;
                  var1.NewFacing = IsoDirections.E;
               }

               if (var8 && !var9) {
                  var1.moveY -= 0.04F;
                  if (var1.NewFacing == IsoDirections.W) {
                     var1.NewFacing = IsoDirections.NW;
                  } else if (var1.NewFacing == IsoDirections.E) {
                     var1.NewFacing = IsoDirections.NE;
                  } else {
                     var1.NewFacing = IsoDirections.N;
                  }
               }

               if (var9 && !var8) {
                  var1.moveY += 0.04F;
                  if (var1.NewFacing == IsoDirections.W) {
                     var1.NewFacing = IsoDirections.SW;
                  } else if (var1.NewFacing == IsoDirections.E) {
                     var1.NewFacing = IsoDirections.SE;
                  } else {
                     var1.NewFacing = IsoDirections.S;
                  }
               }
            } else {
               if (var6) {
                  var1.moveX = -1.0F;
               } else if (var7) {
                  var1.moveX = 1.0F;
               }

               if (var8) {
                  var1.moveY = 1.0F;
               } else if (var9) {
                  var1.moveY = -1.0F;
               }

               if (var1.moveX != 0.0F || var1.moveY != 0.0F) {
                  tempo.set(var1.moveX, var1.moveY);
                  tempo.normalize();
                  var1.NewFacing = IsoDirections.fromAngle(tempo);
               }
            }
         }

    PathFindBehavior2 var10 = this.getPathFindBehavior2();
         if (var1.moveX == 0.0F && var1.moveY == 0.0F && this.getPath2() != nullptr && (var10.isStrafing() || this.isAiming()) && !var10.bStopping) {
    Vector2 var11 = tempo.set(var10.getTargetX() - this.x, var10.getTargetY() - this.y);
    Vector2 var12 = tempo2.set(-1.0F, 0.0F);
    float var13 = 1.0F;
    float var14 = var11.dot(var12);
    float var15 = var14 / var13;
            var12 = tempo2.set(0.0F, -1.0F);
            var14 = var11.dot(var12);
    float var16 = var14 / var13;
            tempo.set(var16, var15);
            tempo.normalize();
            tempo.rotate((float) (Math.PI / 4));
            var1.moveX = tempo.x;
            var1.moveY = tempo.y;
         }

         if (var1.moveX != 0.0F || var1.moveY != 0.0F) {
            if (this.stateMachine.getCurrent() == PathFindState.instance()) {
               this.setDefaultState();
            }

            this.setJustMoved(true);
            this.setMoveDelta(1.0F);
            if (this.isStrafing()) {
               tempo.set(var1.moveX, var1.moveY);
               tempo.normalize();
    float var17 = this.legsSprite.modelSlot.model.AnimPlayer.getRenderedAngle();
               var17 = (float)(var17 + (Math.PI / 4));
               if (var17 > Math.PI * 2) {
                  var17 = (float)(var17 - (Math.PI * 2));
               }

               if (var17 < 0.0F) {
                  var17 = (float)(var17 + (Math.PI * 2));
               }

               tempo.rotate(var17);
               var1.strafeX = tempo.x;
               var1.strafeY = tempo.y;
               this.m_IPX = var1.moveX;
               this.m_IPY = var1.moveY;
            } else {
               tempo.set(var1.moveX, -var1.moveY);
               tempo.normalize();
               tempo.rotate((float) (-Math.PI / 4));
               this.setForwardDirection(tempo);
            }
         }
      }
   }

    void updateAimingStance() {
      if (this.isVariable("LeftHandMask", "RaiseHand")) {
         this.clearVariable("LeftHandMask");
      }

      if (this.isAiming() && !this.isCurrentState(SwipeStatePlayer.instance())) {
    HandWeapon var1 = (HandWeapon)Type.tryCastTo(this.getPrimaryHandItem(), HandWeapon.class);
         var1 = var1 == nullptr ? this.bareHands : var1;
         SwipeStatePlayer.instance().calcValidTargets(this, var1, true, s_targetsProne, s_targetsStanding);
    HitInfo var2 = s_targetsStanding.empty() ? nullptr : s_targetsStanding.get(0);
    HitInfo var3 = s_targetsProne.empty() ? nullptr : s_targetsProne.get(0);
         if (SwipeStatePlayer.instance().isProneTargetBetter(this, var2, var3)) {
            var2 = nullptr;
         }

    bool var4 = this.isAttackAnim() || this.getVariableBoolean("ShoveAnim") || this.getVariableBoolean("StompAnim");
         if (!var4) {
            this.setAimAtFloor(false);
         }

         if (var2 != nullptr) {
            if (!var4) {
               this.setAimAtFloor(false);
            }
         } else if (var3 != nullptr && !var4) {
            this.setAimAtFloor(true);
         }

         if (var2 != nullptr) {
            boolean var5 = !this.isAttackAnim()
               && var1.getSwingAnim() != nullptr
               && var1.CloseKillMove != nullptr
               && var2.distSq < var1.getMinRange() * var1.getMinRange();
            if (var5 && (this.getSecondaryHandItem() == nullptr || this.getSecondaryHandItem().getItemReplacementSecondHand() == nullptr)) {
               this.setVariable("LeftHandMask", "RaiseHand");
            }
         }

         SwipeStatePlayer.instance().hitInfoPool.release(s_targetsStanding);
         SwipeStatePlayer.instance().hitInfoPool.release(s_targetsProne);
         s_targetsStanding.clear();
         s_targetsProne.clear();
      }
   }

    void calculateStats() {
      if (!this.bRemote) {
         super.calculateStats();
      }
   }

    void updateStats_Sleeping() {
    float var1 = 2.0F;
      if (allPlayersAsleep()) {
         var1 *= GameTime.instance.getDeltaMinutesPerDay();
      }

      this.stats.endurance = (float)(
         this.stats.endurance
            + ZomboidGlobals.ImobileEnduranceReduce
               * SandboxOptions.instance.getEnduranceRegenMultiplier()
               * this.getRecoveryMod()
               * GameTime.instance.getMultiplier()
               * var1
      );
      if (this.stats.endurance > 1.0F) {
         this.stats.endurance = 1.0F;
      }

      if (this.stats.fatigue > 0.0F) {
    float var2 = 1.0F;
         if (this.Traits.Insomniac.isSet()) {
            var2 *= 0.5F;
         }

         if (this.Traits.NightOwl.isSet()) {
            var2 *= 1.4F;
         }

    float var3 = 1.0F;
         if ("goodBed" == this.getBedType())) {
            var3 = 1.1F;
         }

         if ("badBed" == this.getBedType())) {
            var3 = 0.9F;
         }

         if ("floor" == this.getBedType())) {
            var3 = 0.6F;
         }

    float var4 = 1.0F / GameTime.instance.getMinutesPerDay() / 60.0F * GameTime.instance.getMultiplier() / 2.0F;
         this.timeOfSleep += var4;
         if (this.timeOfSleep > this.delayToActuallySleep) {
    float var5 = 1.0F;
            if (this.Traits.NeedsLessSleep.isSet()) {
               var5 *= 0.75F;
            } else if (this.Traits.NeedsMoreSleep.isSet()) {
               var5 *= 1.18F;
            }

    float var6 = 1.0F;
            if (this.stats.fatigue <= 0.3F) {
               var6 = 7.0F * var5;
               this.stats.fatigue -= var4 / var6 * 0.3F * var2 * var3;
            } else {
               var6 = 5.0F * var5;
               this.stats.fatigue -= var4 / var6 * 0.7F * var2 * var3;
            }
         }

         if (this.stats.fatigue < 0.0F) {
            this.stats.fatigue = 0.0F;
         }
      }

      if (this.Moodles.getMoodleLevel(MoodleType.FoodEaten) == 0) {
    float var7 = this.getAppetiteMultiplier();
         this.stats.hunger = (float)(
            this.stats.hunger
               + ZomboidGlobals.HungerIncreaseWhileAsleep
                  * SandboxOptions.instance.getStatsDecreaseMultiplier()
                  * var7
                  * GameTime.instance.getMultiplier()
                  * GameTime.instance.getDeltaMinutesPerDay()
                  * this.getHungerMultiplier()
         );
      } else {
         this.stats.hunger = this.stats.hunger
            + (float)(
               ZomboidGlobals.HungerIncreaseWhenWellFed
                  * SandboxOptions.instance.getStatsDecreaseMultiplier()
                  * ZomboidGlobals.HungerIncreaseWhileAsleep
                  * SandboxOptions.instance.getStatsDecreaseMultiplier()
                  * GameTime.instance.getMultiplier()
                  * this.getHungerMultiplier()
                  * GameTime.instance.getDeltaMinutesPerDay()
            );
      }

      if (this.ForceWakeUpTime == 0.0F) {
         this.ForceWakeUpTime = 9.0F;
      }

    float var8 = GameTime.getInstance().getTimeOfDay();
    float var9 = GameTime.getInstance().getLastTimeOfDay();
      if (var9 > var8) {
         if (var9 < this.ForceWakeUpTime) {
            var8 += 24.0F;
         } else {
            var9 -= 24.0F;
         }
      }

    bool var10 = var8 >= this.ForceWakeUpTime && var9 < this.ForceWakeUpTime;
      if (this.getAsleepTime() > 16.0F) {
         var10 = true;
      }

      if (GameClient.bClient || numPlayers > 1) {
         var10 = var10 || this.pressedAim() || this.pressedMovement(false);
      }

      if (this.ForceWakeUp) {
         var10 = true;
      }

      if (this.Asleep && var10) {
         this.ForceWakeUp = false;
         SoundManager.instance.setMusicWakeState(this, "WakeNormal");
         SleepingEvent.instance.wakeUp(this);
         this.ForceWakeUpTime = -1.0F;
         if (GameClient.bClient) {
            GameClient.instance.sendPlayer(this);
         }

         this.dirtyRecalcGridStackTime = 20.0F;
      }
   }

    void updateEnduranceWhileSitting() {
    float var1 = (float)ZomboidGlobals.SittingEnduranceMultiplier;
      var1 *= 1.0F - this.stats.fatigue;
      var1 *= GameTime.instance.getMultiplier();
      this.stats.endurance = (float)(
         this.stats.endurance + ZomboidGlobals.ImobileEnduranceReduce * SandboxOptions.instance.getEnduranceRegenMultiplier() * this.getRecoveryMod() * var1
      );
      this.stats.endurance = PZMath.clamp(this.stats.endurance, 0.0F, 1.0F);
   }

    void updateEndurance(float var1) {
      if (this.isSitOnGround()) {
         this.updateEnduranceWhileSitting();
      } else {
    float var2 = 1.0F;
         if (this.isSneaking()) {
            var2 = 1.5F;
         }

         if (this.CurrentSpeed > 0.0F && (this.isRunning() || this.isSprinting())) {
    double var9 = ZomboidGlobals.RunningEnduranceReduce;
            if (this.isSprinting()) {
               var9 = ZomboidGlobals.SprintingEnduranceReduce;
            }

    float var19 = 1.4F;
            if (this.Traits.Overweight.isSet()) {
               var19 = 2.9F;
            }

            if (this.Traits.Athletic.isSet()) {
               var19 = 0.8F;
            }

            var19 *= 2.3F;
            var19 *= this.getPacingMod();
            var19 *= this.getHyperthermiaMod();
    float var6 = 0.7F;
            if (this.Traits.Asthmatic.isSet()) {
               var6 = 1.4F;
            }

            if (this.Moodles.getMoodleLevel(MoodleType.HeavyLoad) == 0) {
               this.stats.endurance = (float)(this.stats.endurance - var9 * var19 * 0.5 * var6 * GameTime.instance.getMultiplier() * var2);
            } else {
    float var7 = 2.8F;
               switch (this.Moodles.getMoodleLevel(MoodleType.HeavyLoad)) {
                  case 1:
                     var7 = 1.5F;
                     break;
                  case 2:
                     var7 = 1.9F;
                     break;
                  case 3:
                     var7 = 2.3F;
               }

               this.stats.endurance = (float)(this.stats.endurance - var9 * var19 * 0.5 * var6 * GameTime.instance.getMultiplier() * var7 * var2);
            }
         } else if (this.CurrentSpeed > 0.0F && this.Moodles.getMoodleLevel(MoodleType.HeavyLoad) > 2) {
    float var3 = 0.7F;
            if (this.Traits.Asthmatic.isSet()) {
               var3 = 1.4F;
            }

    float var4 = 1.4F;
            if (this.Traits.Overweight.isSet()) {
               var4 = 2.9F;
            }

            if (this.Traits.Athletic.isSet()) {
               var4 = 0.8F;
            }

            var4 *= 3.0F;
            var4 *= this.getPacingMod();
            var4 *= this.getHyperthermiaMod();
    float var5 = 2.8F;
            switch (this.Moodles.getMoodleLevel(MoodleType.HeavyLoad)) {
               case 2:
                  var5 = 1.5F;
                  break;
               case 3:
                  var5 = 1.9F;
                  break;
               case 4:
                  var5 = 2.3F;
            }

            this.stats.endurance = (float)(
               this.stats.endurance - ZomboidGlobals.RunningEnduranceReduce * var4 * 0.5 * var3 * var2 * GameTime.instance.getMultiplier() * var5 / 2.0
            );
         }

         switch (this.Moodles.getMoodleLevel(MoodleType.Endurance)) {
            case 1:
               var1 *= 0.95F;
               break;
            case 2:
               var1 *= 0.9F;
               break;
            case 3:
               var1 *= 0.8F;
               break;
            case 4:
               var1 *= 0.6F;
         }

         if (this.stats.enduranceRecharging) {
            var1 *= 0.85F;
         }

         if (!this.isPlayerMoving()) {
    float var10 = 1.0F;
            var10 *= 1.0F - this.stats.fatigue;
            var10 *= GameTime.instance.getMultiplier();
            if (this.Moodles.getMoodleLevel(MoodleType.HeavyLoad) <= 1) {
               this.stats.endurance = (float)(
                  this.stats.endurance
                     + ZomboidGlobals.ImobileEnduranceReduce * SandboxOptions.instance.getEnduranceRegenMultiplier() * this.getRecoveryMod() * var10
               );
            }
         }

         if (!this.isSprinting() && !this.isRunning() && this.CurrentSpeed > 0.0F) {
    float var13 = 1.0F;
            var13 *= 1.0F - this.stats.fatigue;
            var13 *= GameTime.instance.getMultiplier();
            if (this.getMoodles().getMoodleLevel(MoodleType.Endurance) < 2) {
               if (this.Moodles.getMoodleLevel(MoodleType.HeavyLoad) <= 1) {
                  this.stats.endurance = (float)(
                     this.stats.endurance
                        + ZomboidGlobals.ImobileEnduranceReduce / 4.0 * SandboxOptions.instance.getEnduranceRegenMultiplier() * this.getRecoveryMod() * var13
                  );
               }
            } else {
               this.stats.endurance = (float)(this.stats.endurance - ZomboidGlobals.RunningEnduranceReduce / 7.0 * var2);
            }
         }
      }
   }

    bool checkActionsBlockingMovement() {
      if (this.CharacterActions.empty()) {
    return false;
      } else {
    BaseAction var1 = (BaseAction)this.CharacterActions.get(0);
         return var1.blockMovementEtc;
      }
   }

    void updateInteractKeyPanic() {
      if (this.PlayerIndex == 0) {
         if (GameKeyboard.isKeyPressed(Core.getInstance().getKey("Interact"))) {
            this.ContextPanic += 0.6F;
         }
      }
   }

    void updateSneakKey() {
      if (this.PlayerIndex != 0) {
         this.bSneakDebounce = false;
      } else {
         if (this.isBlockMovement() || !GameKeyboard.isKeyDown(Core.getInstance().getKey("Crouch"))) {
            this.bSneakDebounce = false;
         } else if (!this.bSneakDebounce) {
            this.setSneaking(!this.isSneaking());
            this.bSneakDebounce = true;
         }
      }
   }

    void updateChangeCharacterKey() {
      if (Core.bDebug) {
         if (this.PlayerIndex == 0 && GameKeyboard.isKeyDown(22)) {
            if (!this.bChangeCharacterDebounce) {
               this.FollowCamStack.clear();
               this.bChangeCharacterDebounce = true;

               for (int var2 = 0; var2 < this.getCell().getObjectList().size(); var2++) {
    IsoMovingObject var1 = (IsoMovingObject)this.getCell().getObjectList().get(var2);
                  if (dynamic_cast<IsoSurvivor*>(var1) != nullptr) {
                     this.FollowCamStack.push_back((IsoSurvivor)var1);
                  }
               }

               if (!this.FollowCamStack.empty()) {
                  if (this.followID >= this.FollowCamStack.size()) {
                     this.followID = 0;
                  }

                  IsoCamera.SetCharacterToFollow(this.FollowCamStack.get(this.followID));
                  this.followID++;
               }
            }
         } else {
            this.bChangeCharacterDebounce = false;
         }
      }
   }

    void updateEnableModelsKey() {
      if (Core.bDebug) {
         if (this.PlayerIndex == 0 && GameKeyboard.isKeyPressed(Core.getInstance().getKey("ToggleModelsEnabled"))) {
            ModelManager.instance.bDebugEnableModels = !ModelManager.instance.bDebugEnableModels;
         }
      }
   }

    void updateDeathDragDown() {
      if (!this.isDead()) {
         if (this.isDeathDragDown()) {
            if (this.isGodMod()) {
               this.setDeathDragDown(false);
            } else if (!"EndDeath" == this.getHitReaction())) {
               for (int var1 = -1; var1 <= 1; var1++) {
                  for (int var2 = -1; var2 <= 1; var2++) {
    IsoGridSquare var3 = this.getCell().getGridSquare((int)this.x + var2, (int)this.y + var1, (int)this.z);
                     if (var3 != nullptr) {
                        for (int var4 = 0; var4 < var3.getMovingObjects().size(); var4++) {
    IsoMovingObject var5 = (IsoMovingObject)var3.getMovingObjects().get(var4);
    IsoZombie var6 = (IsoZombie)Type.tryCastTo(var5, IsoZombie.class);
                           if (var6 != nullptr && var6.isAlive() && !var6.isOnFloor()) {
                              this.setAttackedBy(var6);
                              this.setHitReaction("EndDeath");
                              this.setBlockMovement(true);
                              return;
                           }
                        }
                     }
                  }
               }

               this.setDeathDragDown(false);
               if (GameClient.bClient) {
                  DebugLog.Multiplayer.warn("UpdateDeathDragDown: no zombies found around player \"%s\"", new Object[]{this.getUsername()});
                  this.setHitFromBehind(false);
                  this.Kill(nullptr);
               }
            }
         }
      }
   }

    void updateGodModeKey() {
      if (Core.bDebug) {
         if (GameKeyboard.isKeyPressed(Core.getInstance().getKey("ToggleGodModeInvisible"))) {
    IsoPlayer var1 = nullptr;

            for (int var2 = 0; var2 < numPlayers; var2++) {
               if (players[var2] != nullptr && !players[var2].isDead()) {
                  var1 = players[var2];
                  break;
               }
            }

            if (this == var1) {
    bool var4 = !var1.isGodMod();
               DebugLog.General.println("Toggle GodMode: %s", var4 ? "ON" : "OFF");
               var1.setInvisible(var4);
               var1.setGhostMode(var4);
               var1.setGodMod(var4);

               for (int var3 = 0; var3 < numPlayers; var3++) {
                  if (players[var3] != nullptr && players[var3] != var1) {
                     players[var3].setInvisible(var4);
                     players[var3].setGhostMode(var4);
                     players[var3].setGodMod(var4);
                  }
               }

               if (GameClient.bClient) {
                  GameClient.sendPlayerExtraInfo(var1);
               }
            }
         }
      }
   }

    void checkReloading() {
    HandWeapon var1 = (HandWeapon)Type.tryCastTo(this.getPrimaryHandItem(), HandWeapon.class);
      if (var1 != nullptr && var1.isReloadable(this)) {
    bool var2 = false;
    bool var3 = false;
         if (this.JoypadBind != -1 && this.bJoypadMovementActive) {
    bool var4 = JoypadManager.instance.isRBPressed(this.JoypadBind);
            if (var4) {
               var2 = !this.bReloadButtonDown;
            }

            this.bReloadButtonDown = var4;
            var4 = JoypadManager.instance.isLBPressed(this.JoypadBind);
            if (var4) {
               var3 = !this.bRackButtonDown;
            }

            this.bRackButtonDown = var4;
         }

         if (this.PlayerIndex == 0) {
    bool var6 = GameKeyboard.isKeyDown(Core.getInstance().getKey("ReloadWeapon"));
            if (var6) {
               var2 = !this.bReloadKeyDown;
            }

            this.bReloadKeyDown = var6;
            var6 = GameKeyboard.isKeyDown(Core.getInstance().getKey("Rack Firearm"));
            if (var6) {
               var3 = !this.bRackKeyDown;
            }

            this.bRackKeyDown = var6;
         }

         if (var2) {
            this.setVariable("WeaponReloadType", var1.getWeaponReloadType());
            LuaEventManager.triggerEvent("OnPressReloadButton", this, var1);
         } else if (var3) {
            this.setVariable("WeaponReloadType", var1.getWeaponReloadType());
            LuaEventManager.triggerEvent("OnPressRackButton", this, var1);
         }
      }
   }

    void postupdate() {
      s_performance.postUpdate.invokeAndMeasure(this, IsoPlayer::postupdateInternal);
   }

    void postupdateInternal() {
    bool var1 = this.hasHitReaction();
      super.postupdate();
      if (var1
         && this.hasHitReaction()
         && !this.isCurrentState(PlayerHitReactionState.instance())
         && !this.isCurrentState(PlayerHitReactionPVPState.instance())) {
         this.setHitReaction("");
      }

      this.highlightRangedTargets();
      if (this.isNPC) {
    GameTime var2 = GameTime.getInstance();
    float var3 = 1.0F / var2.getMinutesPerDay() / 60.0F * var2.getMultiplier() / 2.0F;
         if (Core.bLastStand) {
            var3 = 1.0F / var2.getMinutesPerDay() / 60.0F * var2.getUnmoddedMultiplier() / 2.0F;
         }

         this.setHoursSurvived(this.getHoursSurvived() + var3);
      }

      this.getBodyDamage().setBodyPartsLastState();
   }

    void highlightRangedTargets() {
      if (this.isLocalPlayer() && !this.isNPC) {
         if (this.isAiming()) {
            if (Core.getInstance().getOptionAimOutline() != 1) {
               s_performance.highlightRangedTargets.invokeAndMeasure(this, IsoPlayer::highlightRangedTargetsInternal);
            }
         }
      }
   }

    void highlightRangedTargetsInternal() {
    HandWeapon var1 = (HandWeapon)Type.tryCastTo(this.getPrimaryHandItem(), HandWeapon.class);
      if (var1 == nullptr || var1.getSwingAnim() == nullptr || var1.getCondition() <= 0) {
         var1 = this.bareHands;
      }

      if (Core.getInstance().getOptionAimOutline() != 2 || var1.isRanged()) {
    AttackVars var2 = std::make_shared<AttackVars>();
    std::vector var3 = new std::vector();
    bool var4 = this.bDoShove;
    HandWeapon var5 = this.getUseHandWeapon();
         this.setDoShove(false);
         this.setUseHandWeapon(var1);
         SwipeStatePlayer.instance().CalcAttackVars(this, var2);
         SwipeStatePlayer.instance().CalcHitList(this, false, var2, var3);

         for (int var6 = 0; var6 < var3.size(); var6++) {
    HitInfo var7 = (HitInfo)var3.get(var6);
    IsoMovingObject var8 = var7.getObject();
            if (dynamic_cast<IsoZombie*>(var8) != nullptr || dynamic_cast<IsoPlayer*>(var8) != nullptr) {
    ColorInfo var9 = std::make_shared<ColorInfo>();
               Core.getInstance().getBadHighlitedColor().interp(Core.getInstance().getGoodHighlitedColor(), var7.chance / 100.0F, var9);
               var8.bOutline[this.PlayerIndex] = true;
               if (var8.outlineColor[this.PlayerIndex] == nullptr) {
                  var8.outlineColor[this.PlayerIndex] = std::make_unique<ColorInfo>();
               }

               var8.outlineColor[this.PlayerIndex].set(var9);
            }

            if (var7.window.getObject() != nullptr) {
               var7.window.getObject().setHighlightColor(0.8F, 0.1F, 0.1F, 0.5F);
               var7.window.getObject().setHighlighted(true);
            }
         }

         this.setDoShove(var4);
         this.setUseHandWeapon(var5);
      }
   }

    bool isSolidForSeparate() {
      return this.isGhostMode() ? false : super.isSolidForSeparate();
   }

    bool isPushableForSeparate() {
      if (this.isCurrentState(PlayerHitReactionState.instance())) {
    return false;
      } else {
         return this.isCurrentState(SwipeStatePlayer.instance()) ? false : super.isPushableForSeparate();
      }
   }

    bool isPushedByForSeparate(IsoMovingObject var1) {
      if (!this.isPlayerMoving() && var1.isZombie() && ((IsoZombie)var1).isAttacking()) {
    return false;
      } else {
         return !GameClient.bClient || this.isLocalPlayer() && this.isJustMoved() ? super.isPushedByForSeparate(var1) : false;
      }
   }

    void updateExt() {
      if (!this.isSneaking()) {
         this.extUpdateCount = this.extUpdateCount + GameTime.getInstance().getMultiplier() / 0.8F;
         if (!this.getAdvancedAnimator().containsAnyIdleNodes() && !this.isSitOnGround()) {
            this.extUpdateCount = 0.0F;
         }

         if (!(this.extUpdateCount <= 5000.0F)) {
            this.extUpdateCount = 0.0F;
            if (this.stats.NumVisibleZombies == 0 && this.stats.NumChasingZombies == 0) {
               if (Rand.NextBool(3)) {
                  if (this.getAdvancedAnimator().containsAnyIdleNodes() || this.isSitOnGround()) {
                     this.onIdlePerformFidgets();
                     this.reportEvent("EventDoExt");
                  }
               }
            }
         }
      }
   }

    void onIdlePerformFidgets() {
    Moodles var1 = this.getMoodles();
    BodyDamage var2 = this.getBodyDamage();
      if (var1.getMoodleLevel(MoodleType.Hypothermia) > 0 && Rand.NextBool(7)) {
         this.setVariable("Ext", "Shiver");
      } else if (var1.getMoodleLevel(MoodleType.Hyperthermia) > 0 && Rand.NextBool(7)) {
         this.setVariable("Ext", "WipeBrow");
      } else if (var1.getMoodleLevel(MoodleType.Sick) > 0 && Rand.NextBool(7)) {
         if (Rand.NextBool(4)) {
            this.setVariable("Ext", "Cough");
         } else {
            this.setVariable("Ext", "PainStomach" + (Rand.Next(2) + 1));
         }
      } else if (var1.getMoodleLevel(MoodleType.Endurance) > 2 && Rand.NextBool(10)) {
         if (Rand.NextBool(5) && !this.isSitOnGround()) {
            this.setVariable("Ext", "BentDouble");
         } else {
            this.setVariable("Ext", "WipeBrow");
         }
      } else if (var1.getMoodleLevel(MoodleType.Tired) > 2 && Rand.NextBool(10)) {
         if (Rand.NextBool(7)) {
            this.setVariable("Ext", "TiredStretch");
         } else if (Rand.NextBool(7)) {
            this.setVariable("Ext", "Sway");
         } else {
            this.setVariable("Ext", "Yawn");
         }
      } else if (var2.doBodyPartsHaveInjuries(BodyPartType.Head, BodyPartType.Neck) && Rand.NextBool(7)) {
         if (var2.areBodyPartsBleeding(BodyPartType.Head, BodyPartType.Neck) && Rand.NextBool(2)) {
            this.setVariable("Ext", "WipeHead");
         } else {
            this.setVariable("Ext", "PainHead" + (Rand.Next(2) + 1));
         }
      } else if (var2.doBodyPartsHaveInjuries(BodyPartType.UpperArm_L, BodyPartType.ForeArm_L) && Rand.NextBool(7)) {
         if (var2.areBodyPartsBleeding(BodyPartType.UpperArm_L, BodyPartType.ForeArm_L) && Rand.NextBool(2)) {
            this.setVariable("Ext", "WipeArmL");
         } else {
            this.setVariable("Ext", "PainArmL");
         }
      } else if (var2.doBodyPartsHaveInjuries(BodyPartType.UpperArm_R, BodyPartType.ForeArm_R) && Rand.NextBool(7)) {
         if (var2.areBodyPartsBleeding(BodyPartType.UpperArm_R, BodyPartType.ForeArm_R) && Rand.NextBool(2)) {
            this.setVariable("Ext", "WipeArmR");
         } else {
            this.setVariable("Ext", "PainArmR");
         }
      } else if (var2.doesBodyPartHaveInjury(BodyPartType.Hand_L) && Rand.NextBool(7)) {
         this.setVariable("Ext", "PainHandL");
      } else if (var2.doesBodyPartHaveInjury(BodyPartType.Hand_R) && Rand.NextBool(7)) {
         this.setVariable("Ext", "PainHandR");
      } else if (!this.isSitOnGround() && var2.doBodyPartsHaveInjuries(BodyPartType.UpperLeg_L, BodyPartType.LowerLeg_L) && Rand.NextBool(7)) {
         if (var2.areBodyPartsBleeding(BodyPartType.UpperLeg_L, BodyPartType.LowerLeg_L) && Rand.NextBool(2)) {
            this.setVariable("Ext", "WipeLegL");
         } else {
            this.setVariable("Ext", "PainLegL");
         }
      } else if (!this.isSitOnGround() && var2.doBodyPartsHaveInjuries(BodyPartType.UpperLeg_R, BodyPartType.LowerLeg_R) && Rand.NextBool(7)) {
         if (var2.areBodyPartsBleeding(BodyPartType.UpperLeg_R, BodyPartType.LowerLeg_R) && Rand.NextBool(2)) {
            this.setVariable("Ext", "WipeLegR");
         } else {
            this.setVariable("Ext", "PainLegR");
         }
      } else if (var2.doBodyPartsHaveInjuries(BodyPartType.Torso_Upper, BodyPartType.Torso_Lower) && Rand.NextBool(7)) {
         if (var2.areBodyPartsBleeding(BodyPartType.Torso_Upper, BodyPartType.Torso_Lower) && Rand.NextBool(2)) {
            this.setVariable("Ext", "WipeTorso" + (Rand.Next(2) + 1));
         } else {
            this.setVariable("Ext", "PainTorso");
         }
      } else if (WeaponType.getWeaponType(this) != WeaponType.barehand) {
         this.setVariable("Ext", Rand.Next(5) + 1 + "");
      } else if (Rand.NextBool(10)) {
         this.setVariable("Ext", "ChewNails");
      } else if (Rand.NextBool(10)) {
         this.setVariable("Ext", "ShiftWeight");
      } else if (Rand.NextBool(10)) {
         this.setVariable("Ext", "PullAtColar");
      } else if (Rand.NextBool(10)) {
         this.setVariable("Ext", "BridgeNose");
      } else {
         this.setVariable("Ext", Rand.Next(5) + 1 + "");
      }
   }

    bool updateUseKey() {
      if (GameServer.bServer) {
    return false;
      } else if (!this.isLocalPlayer()) {
    return false;
      } else if (this.PlayerIndex != 0) {
    return false;
      } else {
         this.timePressedContext = this.timePressedContext + GameTime.instance.getRealworldSecondsSinceLastUpdate();
    bool var1 = GameKeyboard.isKeyDown(Core.getInstance().getKey("Interact"));
         if (var1 && this.timePressedContext < 0.5F) {
            this.bPressContext = true;
         } else {
            if (this.bPressContext && (Core.CurrentTextEntryBox != nullptr && Core.CurrentTextEntryBox.DoingTextEntry || !GameKeyboard.doLuaKeyPressed)) {
               this.bPressContext = false;
            }

            if (this.bPressContext && this.doContext(this.dir)) {
               this.timePressedContext = 0.0F;
               this.bPressContext = false;
    return true;
            }

            if (!var1) {
               this.bPressContext = false;
               this.timePressedContext = 0.0F;
            }
         }

    return false;
      }
   }

    void updateHitByVehicle() {
      if (!GameServer.bServer) {
         if (this.isLocalPlayer()) {
            if (this.vehicle4testCollision != nullptr && this.ulBeatenVehicle.Check() && SandboxOptions.instance.DamageToPlayerFromHitByACar.getValue() > 1) {
    BaseVehicle var1 = this.vehicle4testCollision;
               this.vehicle4testCollision = nullptr;
               if (var1.isEngineRunning() && this.getVehicle() != var1) {
    float var2 = var1.jniLinearVelocity.x;
    float var3 = var1.jniLinearVelocity.z;
    float var4 = (float)Math.sqrt(var2 * var2 + var3 * var3);
    Vector2 var5 = (Vector2)((Vector2ObjectPool)BaseVehicle.TL_vector2_pool.get()).alloc();
    Vector2 var6 = var1.testCollisionWithCharacter(this, 0.20000002F, var5);
                  if (var6 != nullptr && var6.x != -1.0F) {
                     var6.x = (var6.x - var1.x) * var4 * 1.0F + this.x;
                     var6.y = (var6.y - var1.y) * var4 * 1.0F + this.x;
                     if (this.isOnFloor()) {
    int var7 = var1.testCollisionWithProneCharacter(this, false);
                        if (var7 > 0) {
                           this.doBeatenVehicle(Math.max(var4 * 6.0F, 5.0F));
                        }

                        this.doBeatenVehicle(0.0F);
                     } else if (this.getCurrentState() != PlayerFallDownState.instance() && var4 > 0.1F) {
                        this.doBeatenVehicle(Math.max(var4 * 2.0F, 5.0F));
                     }
                  }

                  ((Vector2ObjectPool)BaseVehicle.TL_vector2_pool.get()).release(var5);
               }
            }
         }
      }
   }

    void updateSoundListener() {
      if (!GameServer.bServer) {
         if (this.isLocalPlayer()) {
            if (this.soundListener == nullptr) {
               this.soundListener = (BaseSoundListener)(Core.SoundDisabled ? std::make_shared<DummySoundListener>(this.PlayerIndex) : std::make_shared<SoundListener>(this.PlayerIndex));
            }

            this.soundListener.setPos(this.x, this.y, this.z);
            this.checkNearbyRooms = this.checkNearbyRooms - GameTime.getInstance().getMultiplier() / 1.6F;
            if (this.checkNearbyRooms <= 0.0F) {
               this.checkNearbyRooms = 30.0F;
               this.numNearbyBuildingsRooms = IsoWorld.instance.MetaGrid.countNearbyBuildingsRooms(this);
            }

            if (this.testemitter == nullptr) {
               this.testemitter = (BaseSoundEmitter)(Core.SoundDisabled ? std::make_unique<DummySoundEmitter>() : std::make_unique<FMODSoundEmitter>());
               this.testemitter.setPos(this.x, this.y, this.z);
            }

            this.soundListener.tick();
            this.testemitter.tick();
         }
      }
   }

    void updateMovementRates() {
      this.calculateWalkSpeed();
      this.m_idleSpeed = this.calculateIdleSpeed();
      this.updateFootInjuries();
   }

    void pressedAttack(bool var1) {
    bool var2 = GameClient.bClient && !this.isLocalPlayer();
    bool var3 = this.isSprinting();
      this.setSprinting(false);
      this.setForceSprint(false);
      if (!this.attackStarted && !this.isCurrentState(PlayerHitReactionState.instance())) {
         if (!GameClient.bClient || !this.isCurrentState(PlayerHitReactionPVPState.instance()) || ServerOptions.instance.PVPMeleeWhileHitReaction.getValue()) {
            if (this.primaryHandModel != nullptr
               && !StringUtils.isNullOrEmpty(this.primaryHandModel.maskVariableValue)
               && this.secondaryHandModel != nullptr
               && !StringUtils.isNullOrEmpty(this.secondaryHandModel.maskVariableValue)) {
               this.setDoShove(false);
               this.setForceShove(false);
               this.setInitiateAttack(false);
               this.attackStarted = false;
               this.setAttackType(nullptr);
            } else if (this.getPrimaryHandItem() != nullptr
               && this.getPrimaryHandItem().getItemReplacementPrimaryHand() != nullptr
               && this.getSecondaryHandItem() != nullptr
               && this.getSecondaryHandItem().getItemReplacementSecondHand() != nullptr) {
               this.setDoShove(false);
               this.setForceShove(false);
               this.setInitiateAttack(false);
               this.attackStarted = false;
               this.setAttackType(nullptr);
            } else {
               if (!this.attackStarted) {
                  this.setVariable("StartedAttackWhileSprinting", var3);
               }

               this.setInitiateAttack(true);
               this.attackStarted = true;
               if (!var2) {
                  this.setCriticalHit(false);
               }

               this.setAttackFromBehind(false);
    WeaponType var4 = WeaponType.getWeaponType(this);
               if (!GameClient.bClient || this.isLocalPlayer()) {
                  this.setAttackType((std::string)PZArrayUtil.pickRandom(var4.possibleAttack));
               }

               if (!GameClient.bClient || this.isLocalPlayer()) {
                  this.combatSpeed = this.calculateCombatSpeed();
               }

               if (var1) {
                  SwipeStatePlayer.instance().CalcAttackVars(this, this.attackVars);
               }

    std::string var5 = this.getVariableString("Weapon");
               if (var5 != nullptr && var5 == "throwing") && !this.attackVars.bDoShove) {
                  this.setAttackAnimThrowTimer(2000L);
                  this.setIsAiming(true);
               }

               if (var2) {
                  this.attackVars.bDoShove = this.isDoShove();
                  this.attackVars.bAimAtFloor = this.isAimAtFloor();
               }

               if (this.attackVars.bDoShove && !this.isAuthorizeShoveStomp()) {
                  this.setDoShove(false);
                  this.setForceShove(false);
                  this.setInitiateAttack(false);
                  this.attackStarted = false;
                  this.setAttackType(nullptr);
               } else {
                  this.useHandWeapon = this.attackVars.getWeapon(this);
                  this.setAimAtFloor(this.attackVars.bAimAtFloor);
                  this.setDoShove(this.attackVars.bDoShove);
                  this.targetOnGround = (IsoGameCharacter)this.attackVars.targetOnGround.getMovingObject();
                  if (this.attackVars.getWeapon(this) != nullptr && !StringUtils.isNullOrEmpty(this.attackVars.getWeapon(this).getFireMode())) {
                     this.setVariable("FireMode", this.attackVars.getWeapon(this).getFireMode());
                  } else {
                     this.clearVariable("FireMode");
                  }

                  if (this.useHandWeapon != nullptr && var4.isRanged && !this.bDoShove) {
    int var6 = this.useHandWeapon.getRecoilDelay();
    float var7 = var6 * (1.0F - this.getPerkLevel(Perks.Aiming) / 30.0F);
                     this.setRecoilDelay(var7.intValue());
                  }

    int var11 = Rand.Next(0, 3);
                  if (var11 == 0) {
                     this.setVariable("AttackVariationX", Rand.Next(-1.0F, -0.5F));
                  }

                  if (var11 == 1) {
                     this.setVariable("AttackVariationX", 0.0F);
                  }

                  if (var11 == 2) {
                     this.setVariable("AttackVariationX", Rand.Next(0.5F, 1.0F));
                  }

                  this.setVariable("AttackVariationY", 0.0F);
                  if (var1) {
                     SwipeStatePlayer.instance().CalcHitList(this, true, this.attackVars, this.hitList);
                  }

    IsoGameCharacter var12 = nullptr;
                  if (!this.hitList.empty()) {
                     var12 = (IsoGameCharacter)Type.tryCastTo(((HitInfo)this.hitList.get(0)).getObject(), IsoGameCharacter.class);
                  }

                  if (var12 == nullptr) {
                     if (this.isAiming() && !this.m_meleePressed && this.useHandWeapon != this.bareHands) {
                        this.setDoShove(false);
                        this.setForceShove(false);
                     }

                     this.m_lastAttackWasShove = this.bDoShove;
                     if (var4.canMiss && !this.isAimAtFloor() && (!GameClient.bClient || this.isLocalPlayer())) {
                        this.setAttackType("miss");
                     }

                     if (this.isAiming() && this.bDoShove) {
                        this.setVariable("bShoveAiming", true);
                     } else {
                        this.clearVariable("bShoveAiming");
                     }
                  } else {
                     if (!GameClient.bClient || this.isLocalPlayer()) {
                        this.setAttackFromBehind(this.isBehind(var12));
                     }

    float var8 = IsoUtils.DistanceTo(var12.x, var12.y, this.x, this.y);
                     this.setVariable("TargetDist", var8);
    int var9 = this.calculateCritChance(var12);
                     if (dynamic_cast<IsoZombie*>(var12) != nullptr) {
    IsoZombie var10 = this.getClosestZombieToOtherZombie((IsoZombie)var12);
                        if (!this.attackVars.bAimAtFloor
                           && var8 > 1.25
                           && var4 == WeaponType.spear
                           && (var10 == nullptr || IsoUtils.DistanceTo(var12.x, var12.y, var10.x, var10.y) > 1.7)) {
                           if (!GameClient.bClient || this.isLocalPlayer()) {
                              this.setAttackType("overhead");
                           }

                           var9 += 30;
                        }
                     }

                     if (this.isLocalPlayer() && !var12.isOnFloor()) {
                        var12.setHitFromBehind(this.isAttackFromBehind());
                     }

                     if (this.isAttackFromBehind()) {
                        if (dynamic_cast<IsoZombie*>(var12) != nullptr && ((IsoZombie)var12).target == nullptr) {
                           var9 += 30;
                        } else {
                           var9 += 5;
                        }
                     }

                     if (dynamic_cast<IsoPlayer*>(var12) != nullptr && var4.isRanged && !this.bDoShove) {
                        var9 = (int)(this.attackVars.getWeapon(this).getStopPower() * (1.0F + this.getPerkLevel(Perks.Aiming) / 15.0F));
                     }

                     if (!GameClient.bClient || this.isLocalPlayer()) {
                        this.setCriticalHit(Rand.Next(100) < var9);
                        if (DebugOptions.instance.MultiplayerCriticalHit.getValue()) {
                           this.setCriticalHit(true);
                        }

                        if (this.isAttackFromBehind() && this.attackVars.bCloseKill && dynamic_cast<IsoZombie*>(var12) != nullptr && ((IsoZombie)var12).target == nullptr) {
                           this.setCriticalHit(true);
                        }

                        if (this.isCriticalHit() && !this.attackVars.bCloseKill && !this.bDoShove && var4 == WeaponType.knife) {
                           this.setCriticalHit(false);
                        }

                        this.setAttackWasSuperAttack(false);
                        if (this.stats.NumChasingZombies > 1 && this.attackVars.bCloseKill && !this.bDoShove && var4 == WeaponType.knife) {
                           this.setCriticalHit(false);
                        }
                     }

                     if (this.isCriticalHit()) {
                        this.combatSpeed *= 1.1F;
                     }

                     if (Core.bDebug) {
                        DebugLog.Combat
                           .debugln(
                              "Hit zombie dist: " + var8 + " crit: " + this.isCriticalHit() + " (" + var9 + "%) from behind: " + this.isAttackFromBehind()
                           );
                     }

                     if (this.isAiming() && this.bDoShove) {
                        this.setVariable("bShoveAiming", true);
                     } else {
                        this.clearVariable("bShoveAiming");
                     }

                     if (this.useHandWeapon != nullptr && var4.isRanged) {
                        this.setRecoilDelay(this.useHandWeapon.getRecoilDelay() - this.getPerkLevel(Perks.Aiming) * 2);
                     }

                     this.m_lastAttackWasShove = this.bDoShove;
                  }
               }
            }
         }
      }
   }

    void setAttackAnimThrowTimer(long var1) {
      this.AttackAnimThrowTimer = System.currentTimeMillis() + var1;
   }

    bool isAttackAnimThrowTimeOut() {
      return this.AttackAnimThrowTimer <= System.currentTimeMillis();
   }

    bool getAttackAnim() {
    return false;
   }

    std::string getWeaponType() {
      return !this.isAttackAnimThrowTimeOut() ? "throwing" : this.WeaponT;
   }

    void setWeaponType(const std::string& var1) {
      this.WeaponT = var1;
   }

    int calculateCritChance(IsoGameCharacter var1) {
      if (this.bDoShove) {
    int var7 = 35;
         if (dynamic_cast<IsoPlayer*>(var1) != nullptr var18) {
            var7 = 20;
            if (GameClient.bClient && !var18.isLocalPlayer()) {
               var7 = (int)(var7 - var18.remoteStrLvl * 1.5);
               if (var18.getNutrition().getWeight() < 80.0) {
                  var7 = (int)(var7 + Math.abs((var18.getNutrition().getWeight() - 80.0) / 2.0));
               } else {
                  var7 = (int)(var7 - (var18.getNutrition().getWeight() - 80.0) / 2.0);
               }
            }
         }

         var7 -= this.getMoodles().getMoodleLevel(MoodleType.Endurance) * 5;
         var7 -= this.getMoodles().getMoodleLevel(MoodleType.HeavyLoad) * 5;
         var7 = (int)(var7 - this.getMoodles().getMoodleLevel(MoodleType.Panic) * 1.3);
         return var7 + this.getPerkLevel(Perks.Strength) * 2;
      } else if (this.bDoShove && var1.getStateMachine().getCurrent() == StaggerBackState.instance() && dynamic_cast<IsoZombie*>(var1) != nullptr) {
    return 100;
      } else if (this.getPrimaryHandItem() != nullptr && this.getPrimaryHandItem() instanceof HandWeapon) {
    HandWeapon var2 = (HandWeapon)this.getPrimaryHandItem();
    int var3 = (int)var2.getCriticalChance();
         if (var2.isAlwaysKnockdown()) {
    return 100;
         } else {
    WeaponType var4 = WeaponType.getWeaponType(this);
            if (var4.isRanged) {
               var3 = (int)(var3 + var2.getAimingPerkCritModifier() * (this.getPerkLevel(Perks.Aiming) / 2.0F));
               if (this.getBeenMovingFor() > var2.getAimingTime() + this.getPerkLevel(Perks.Aiming) * 2) {
                  var3 = (int)(var3 - (this.getBeenMovingFor() - (var2.getAimingTime() + this.getPerkLevel(Perks.Aiming) * 2)));
               }

               var3 += this.getPerkLevel(Perks.Aiming) * 3;
    float var5 = this.DistToProper(var1);
               if (var5 < 4.0F) {
                  var3 = (int)(var3 + (4.0F - var5) * 7.0F);
               } else if (var5 >= 4.0F) {
                  var3 = (int)(var3 - (var5 - 4.0F) * 7.0F);
               }

               if ("Auto" == this.getVariableString("FireMode"))) {
                  var3 -= this.shootInARow * 10;
               }
            } else {
               if (var2.isTwoHandWeapon() && (this.getPrimaryHandItem() != var2 || this.getSecondaryHandItem() != var2)) {
                  var3 -= var3 / 3;
               }

               if (this.chargeTime < 2.0F) {
                  var3 -= var3 / 5;
               }

    int var19 = this.getPerkLevel(Perks.Blunt);
               if (var2.getCategories().contains("Axe")) {
                  var19 = this.getPerkLevel(Perks.Axe);
               }

               if (var2.getCategories().contains("LongBlade")) {
                  var19 = this.getPerkLevel(Perks.LongBlade);
               }

               if (var2.getCategories().contains("Spear")) {
                  var19 = this.getPerkLevel(Perks.Spear);
               }

               if (var2.getCategories().contains("SmallBlade")) {
                  var19 = this.getPerkLevel(Perks.SmallBlade);
               }

               if (var2.getCategories().contains("SmallBlunt")) {
                  var19 = this.getPerkLevel(Perks.SmallBlunt);
               }

               var3 += var19 * 3;
               if (dynamic_cast<IsoPlayer*>(var1) != nullptr var6 && GameClient.bClient && !var6.isLocalPlayer()) {
                  var3 = (int)(var3 - var6.remoteStrLvl * 1.5);
                  if (var6.getNutrition().getWeight() < 80.0) {
                     var3 = (int)(var3 + Math.abs((var6.getNutrition().getWeight() - 80.0) / 2.0));
                  } else {
                     var3 = (int)(var3 - (var6.getNutrition().getWeight() - 80.0) / 2.0);
                  }
               }
            }

            var3 -= this.getMoodles().getMoodleLevel(MoodleType.Endurance) * 5;
            var3 -= this.getMoodles().getMoodleLevel(MoodleType.HeavyLoad) * 5;
            var3 = (int)(var3 - this.getMoodles().getMoodleLevel(MoodleType.Panic) * 1.3);
            if (SandboxOptions.instance.Lore.Toughness.getValue() == 1) {
               var3 -= 6;
            }

            if (SandboxOptions.instance.Lore.Toughness.getValue() == 3) {
               var3 += 6;
            }

            if (var3 < 10) {
               var3 = 10;
            }

            if (var3 > 90) {
               var3 = 90;
            }

    return var3;
         }
      } else {
    return 0;
      }
   }

    void checkJoypadIgnoreAimUntilCentered() {
      if (this.bJoypadIgnoreAimUntilCentered) {
         if (GameWindow.ActivatedJoyPad != nullptr && this.JoypadBind != -1 && this.bJoypadMovementActive) {
    float var1 = JoypadManager.instance.getAimingAxisX(this.JoypadBind);
    float var2 = JoypadManager.instance.getAimingAxisY(this.JoypadBind);
            if (var1 * var1 + var2 + var2 <= 0.0F) {
               this.bJoypadIgnoreAimUntilCentered = false;
            }
         }
      }
   }

    bool isAimControlActive() {
      if (this.isForceAim()) {
    return true;
      } else {
         return this.isAimKeyDown()
            ? true
            : GameWindow.ActivatedJoyPad != nullptr
               && this.JoypadBind != -1
               && this.bJoypadMovementActive
               && this.getJoypadAimVector(tempo).getLengthSquared() > 0.0F;
      }
   }

    Vector2 getJoypadAimVector(Vector2 var1) {
      if (this.bJoypadIgnoreAimUntilCentered) {
         return var1.set(0.0F, 0.0F);
      } else {
    float var2 = JoypadManager.instance.getAimingAxisY(this.JoypadBind);
    float var3 = JoypadManager.instance.getAimingAxisX(this.JoypadBind);
    float var4 = JoypadManager.instance.getDeadZone(this.JoypadBind, 0);
         if (var3 * var3 + var2 * var2 < var4 * var4) {
            var2 = 0.0F;
            var3 = 0.0F;
         }

         return var1.set(var3, var2);
      }
   }

    Vector2 getJoypadMoveVector(Vector2 var1) {
    float var2 = JoypadManager.instance.getMovementAxisY(this.JoypadBind);
    float var3 = JoypadManager.instance.getMovementAxisX(this.JoypadBind);
    float var4 = JoypadManager.instance.getDeadZone(this.JoypadBind, 0);
      if (var3 * var3 + var2 * var2 < var4 * var4) {
         var2 = 0.0F;
         var3 = 0.0F;
      }

      var1.set(var3, var2);
      if (this.isIgnoreInputsForDirection()) {
         var1.set(0.0F, 0.0F);
      }

    return var1;
   }

    void updateToggleToAim() {
      if (this.PlayerIndex == 0) {
         if (!Core.getInstance().isToggleToAim()) {
            this.setForceAim(false);
         } else {
    bool var1 = this.isAimKeyDown();
    long var2 = System.currentTimeMillis();
            if (var1) {
               if (this.aimKeyDownMS == 0L) {
                  this.aimKeyDownMS = var2;
               }
            } else {
               if (this.aimKeyDownMS != 0L && var2 - this.aimKeyDownMS < 500L) {
                  this.toggleForceAim();
               } else if (this.isForceAim()) {
                  if (this.aimKeyDownMS != 0L) {
                     this.toggleForceAim();
                  } else {
    int var4 = Core.getInstance().getKey("Aim");
    bool var5 = var4 == 29 || var4 == 157;
                     if (var5 && UIManager.isMouseOverInventory()) {
                        this.toggleForceAim();
                     }
                  }
               }

               this.aimKeyDownMS = 0L;
            }
         }
      }
   }

    void UpdateInputState(InputState var1) {
      var1.bMelee = false;
      if (!MPDebugAI.updateInputState(this, var1)) {
         if (GameWindow.ActivatedJoyPad != nullptr && this.JoypadBind != -1) {
            if (this.bJoypadMovementActive) {
               var1.isAttacking = this.isCharging;
               if (this.bJoypadIgnoreChargingRT) {
                  var1.isAttacking = false;
               }

               if (this.bJoypadIgnoreAimUntilCentered) {
    float var2 = JoypadManager.instance.getAimingAxisX(this.JoypadBind);
    float var3 = JoypadManager.instance.getAimingAxisY(this.JoypadBind);
                  if (var2 == 0.0F && var3 == 0.0F) {
                     this.bJoypadIgnoreAimUntilCentered = false;
                  }
               }
            }

            if (this.isChargingLT) {
               var1.bMelee = true;
               var1.isAttacking = false;
            }
         } else {
            var1.isAttacking = this.isCharging && Mouse.isButtonDownUICheck(0);
            if (GameKeyboard.isKeyDown(Core.getInstance().getKey("Melee")) && this.authorizeMeleeAction) {
               var1.bMelee = true;
               var1.isAttacking = false;
            }
         }

         if (GameWindow.ActivatedJoyPad != nullptr && this.JoypadBind != -1) {
            if (this.bJoypadMovementActive) {
               var1.isCharging = JoypadManager.instance.isRTPressed(this.JoypadBind);
               var1.isChargingLT = JoypadManager.instance.isLTPressed(this.JoypadBind);
               if (this.bJoypadIgnoreChargingRT && !var1.isCharging) {
                  this.bJoypadIgnoreChargingRT = false;
               }
            }

            var1.isAiming = false;
            var1.bRunning = false;
            var1.bSprinting = false;
    Vector2 var9 = this.getJoypadAimVector(tempVector2);
            if (var9.x == 0.0F && var9.y == 0.0F) {
               var1.isCharging = false;
    Vector2 var11 = this.getJoypadMoveVector(tempVector2);
               if (this.isAutoWalk() && var11.getLengthSquared() == 0.0F) {
                  var11.set(this.getAutoWalkDirection());
               }

               if (var11.x != 0.0F || var11.y != 0.0F) {
                  if (this.isAllowRun()) {
                     var1.bRunning = JoypadManager.instance.isRTPressed(this.JoypadBind);
                  }

                  var1.isAttacking = false;
                  var1.bMelee = false;
                  this.bJoypadIgnoreChargingRT = true;
                  var1.isCharging = false;
    bool var13 = JoypadManager.instance.isBPressed(this.JoypadBind);
                  if (var1.bRunning && var13 && !this.bJoypadBDown) {
                     this.bJoypadSprint = !this.bJoypadSprint;
                  }

                  this.bJoypadBDown = var13;
                  var1.bSprinting = this.bJoypadSprint;
               }
            } else {
               var1.isAiming = true;
            }

            if (!var1.bRunning) {
               this.bJoypadBDown = false;
               this.bJoypadSprint = false;
            }
         } else {
            var1.isAiming = (this.isAimKeyDown() || Mouse.isButtonDownUICheck(1) && this.TimeRightPressed >= 0.15F)
               && this.getPlayerNum() == 0
               && StringUtils.isNullOrEmpty(this.getVariableString("BumpFallType"));
            if (Mouse.isButtonDown(1)) {
               this.TimeRightPressed = this.TimeRightPressed + GameTime.getInstance().getRealworldSecondsSinceLastUpdate();
            } else {
               this.TimeRightPressed = 0.0F;
            }

            if (!this.isCharging) {
               var1.isCharging = Mouse.isButtonDownUICheck(1) && this.TimeRightPressed >= 0.15F || this.isAimKeyDown();
            } else {
               var1.isCharging = Mouse.isButtonDown(1) || this.isAimKeyDown();
            }

    int var8 = Core.getInstance().getKey("Run");
    int var10 = Core.getInstance().getKey("Sprint");
            if (this.isAllowRun()) {
               var1.bRunning = GameKeyboard.isKeyDown(var8);
            }

            if (this.isAllowSprint()) {
               if (!Core.OptiondblTapJogToSprint) {
                  if (GameKeyboard.isKeyDown(var10)) {
                     var1.bSprinting = true;
                     this.pressedRunTimer = 1.0F;
                  } else {
                     var1.bSprinting = false;
                  }
               } else {
                  if (!GameKeyboard.wasKeyDown(var8) && GameKeyboard.isKeyDown(var8) && this.pressedRunTimer < 30.0F && this.pressedRun) {
                     var1.bSprinting = true;
                  }

                  if (GameKeyboard.wasKeyDown(var8) && !GameKeyboard.isKeyDown(var8)) {
                     var1.bSprinting = false;
                     this.pressedRun = true;
                  }

                  if (!var1.bRunning) {
                     var1.bSprinting = false;
                  }

                  if (this.pressedRun) {
                     this.pressedRunTimer++;
                  }

                  if (this.pressedRunTimer > 30.0F) {
                     this.pressedRunTimer = 0.0F;
                     this.pressedRun = false;
                  }
               }
            }

            this.updateToggleToAim();
            if (var1.bRunning || var1.bSprinting) {
               this.setForceAim(false);
            }

            if (this.PlayerIndex == 0 && Core.getInstance().isToggleToRun()) {
    bool var4 = GameKeyboard.isKeyDown(var8);
    bool var5 = GameKeyboard.wasKeyDown(var8);
    long var6 = System.currentTimeMillis();
               if (var4 && !var5) {
                  this.runKeyDownMS = var6;
               } else if (!var4 && var5 && var6 - this.runKeyDownMS < 500L) {
                  this.toggleForceRun();
               }
            }

            if (this.PlayerIndex == 0 && Core.getInstance().isToggleToSprint()) {
    bool var12 = GameKeyboard.isKeyDown(var10);
    bool var14 = GameKeyboard.wasKeyDown(var10);
    long var15 = System.currentTimeMillis();
               if (var12 && !var14) {
                  this.sprintKeyDownMS = var15;
               } else if (!var12 && var14 && var15 - this.sprintKeyDownMS < 500L) {
                  this.toggleForceSprint();
               }
            }

            if (this.isForceAim()) {
               var1.isAiming = true;
               var1.isCharging = true;
            }

            if (this.isForceRun()) {
               var1.bRunning = true;
            }

            if (this.isForceSprint()) {
               var1.bSprinting = true;
            }
         }
      }
   }

    IsoZombie getClosestZombieToOtherZombie(IsoZombie var1) {
    IsoZombie var2 = nullptr;
    std::vector var3 = new std::vector();
    std::vector var4 = IsoWorld.instance.CurrentCell.getObjectList();

      for (int var5 = 0; var5 < var4.size(); var5++) {
    IsoMovingObject var6 = (IsoMovingObject)var4.get(var5);
         if (var6 != var1 && dynamic_cast<IsoZombie*>(var6) != nullptr) {
            var3.push_back((IsoZombie)var6);
         }
      }

    float var9 = 0.0F;

      for (int var10 = 0; var10 < var3.size(); var10++) {
    IsoZombie var7 = (IsoZombie)var3.get(var10);
    float var8 = IsoUtils.DistanceTo(var7.x, var7.y, var1.x, var1.y);
         if (var2 == nullptr || var8 < var9) {
            var2 = var7;
            var9 = var8;
         }
      }

    return var2;
   }

    IsoGameCharacter getClosestZombieDist() {
    float var1 = 0.4F;
    bool var2 = false;
      testHitPosition.x = this.x + this.getForwardDirection().x * var1;
      testHitPosition.y = this.y + this.getForwardDirection().y * var1;
    HandWeapon var3 = this.getWeapon();
    std::vector var4 = new std::vector();

      for (int var5 = (int)testHitPosition.x - (int)var3.getMaxRange(); var5 <= (int)testHitPosition.x + (int)var3.getMaxRange(); var5++) {
         for (int var6 = (int)testHitPosition.y - (int)var3.getMaxRange(); var6 <= (int)testHitPosition.y + (int)var3.getMaxRange(); var6++) {
    IsoGridSquare var7 = IsoWorld.instance.CurrentCell.getGridSquare(var5, var6, this.z);
            if (var7 != nullptr && var7.getMovingObjects().size() > 0) {
               for (int var8 = 0; var8 < var7.getMovingObjects().size(); var8++) {
    IsoMovingObject var9 = (IsoMovingObject)var7.getMovingObjects().get(var8);
                  if (dynamic_cast<IsoZombie*>(var9) != nullptr) {
    Vector2 var10 = tempVector2_1.set(this.getX(), this.getY());
    Vector2 var11 = tempVector2_2.set(var9.getX(), var9.getY());
                     var11.x = var11.x - var10.x;
                     var11.y = var11.y - var10.y;
    Vector2 var12 = this.getForwardDirection();
                     var11.normalize();
                     var12.normalize();
    float var13 = var11.dot(var12);
                     if (var13 >= var3.getMinAngle() || var9.isOnFloor()) {
                        var2 = true;
                     }

                     if (var2 && ((IsoZombie)var9).Health > 0.0F) {
                        ((IsoZombie)var9).setHitFromBehind(this.isBehind((IsoZombie)var9));
                        ((IsoZombie)var9).setHitAngle(((IsoZombie)var9).getForwardDirection());
                        ((IsoZombie)var9).setPlayerAttackPosition(((IsoZombie)var9).testDotSide(this));
    float var14 = IsoUtils.DistanceTo(var9.x, var9.y, this.x, this.y);
                        if (var14 < var3.getMaxRange()) {
                           var4.push_back((IsoZombie)var9);
                        }
                     }
                  }
               }
            }
         }
      }

      if (!var4.empty()) {
         Collections.sort(var4, std::make_shared<1>(this));
         return (IsoGameCharacter)var4.get(0);
      } else {
    return nullptr;
      }
   }

    void hitConsequences(HandWeapon var1, IsoGameCharacter var2, bool var3, float var4, bool var5) {
    std::string var6 = var2.getVariableString("ZombieHitReaction");
      if ("Shot" == var6)) {
         var2.setCriticalHit(Rand.Next(100) < ((IsoPlayer)var2).calculateCritChance(this));
      }

      if (dynamic_cast<IsoPlayer*>(var2) != nullptr && (GameServer.bServer || GameClient.bClient)) {
         if (ServerOptions.getInstance().KnockedDownAllowed.getValue()) {
            this.setKnockedDown(var2.isCriticalHit());
         }
      } else {
         this.setKnockedDown(var2.isCriticalHit());
      }

      if (dynamic_cast<IsoPlayer*>(var2) != nullptr) {
         if (!StringUtils.isNullOrEmpty(this.getHitReaction())) {
            this.actionContext.reportEvent("washitpvpagain");
         }

         this.actionContext.reportEvent("washitpvp");
         this.setVariable("hitpvp", true);
      } else {
         this.actionContext.reportEvent("washit");
      }

      if (var3) {
         if (!GameServer.bServer) {
            var2.xp.AddXP(Perks.Strength, 2.0F);
            this.setHitForce(Math.min(0.5F, this.getHitForce()));
            this.setHitReaction("HitReaction");
    std::string var10 = this.testDotSide(var2);
            this.setHitFromBehind("BEHIND" == var10));
         }
      } else {
         if (GameServer.bServer || GameClient.bClient && !this.isLocalPlayer()) {
            if (!GameServer.bServer && !this.isLocalPlayer()) {
               this.BodyDamage.splatBloodFloorBig();
            }
         } else {
            this.BodyDamage.DamageFromWeapon(var1);
         }

         if ("Bite" == var6)) {
    std::string var7 = this.testDotSide(var2);
    bool var8 = var7 == "FRONT");
    bool var9 = var7 == "BEHIND");
            if (var7 == "RIGHT")) {
               var6 = var6 + "LEFT";
            }

            if (var7 == "LEFT")) {
               var6 = var6 + "RIGHT";
            }

            if (var6 != nullptr && !"" == var6)) {
               this.setHitReaction(var6);
            }
         } else if (!this.isKnockedDown()) {
            this.setHitReaction("HitReaction");
         }
      }
   }

    HandWeapon getWeapon() {
      if (this.getPrimaryHandItem() instanceof HandWeapon) {
         return (HandWeapon)this.getPrimaryHandItem();
      } else {
         return this.getSecondaryHandItem() instanceof HandWeapon
            ? (HandWeapon)this.getSecondaryHandItem()
            : (HandWeapon)InventoryItemFactory.CreateItem("BareHands");
      }
   }

    void updateMechanicsItems() {
      if (!GameServer.bServer && !this.mechanicsItem.empty()) {
    Iterator var1 = this.mechanicsItem.keySet().iterator();
    std::vector var2 = new std::vector();

         while (var1.hasNext()) {
    long var3 = (int64_t)var1.next();
    long var4 = this.mechanicsItem.get(var3);
            if (GameTime.getInstance().getCalender().getTimeInMillis() > var4 + 86400000L) {
               var2.push_back(var3);
            }
         }

         for (int var5 = 0; var5 < var2.size(); var5++) {
            this.mechanicsItem.remove(var2.get(var5));
         }
      }
   }

    void enterExitVehicle() {
    bool var1 = this.PlayerIndex == 0 && GameKeyboard.isKeyDown(Core.getInstance().getKey("Interact"));
      if (var1) {
         this.bUseVehicle = true;
         this.useVehicleDuration = this.useVehicleDuration + GameTime.instance.getRealworldSecondsSinceLastUpdate();
      }

      if (!this.bUsedVehicle && this.bUseVehicle && (!var1 || this.useVehicleDuration > 0.5F)) {
         this.bUsedVehicle = true;
         if (this.getVehicle() != nullptr) {
            LuaEventManager.triggerEvent("OnUseVehicle", this, this.getVehicle(), this.useVehicleDuration > 0.5F);
         } else {
            for (int var2 = 0; var2 < this.getCell().vehicles.size(); var2++) {
    BaseVehicle var3 = (BaseVehicle)this.getCell().vehicles.get(var2);
               if (var3.getUseablePart(this) != nullptr) {
                  LuaEventManager.triggerEvent("OnUseVehicle", this, var3, this.useVehicleDuration > 0.5F);
                  break;
               }
            }
         }
      }

      if (!var1) {
         this.bUseVehicle = false;
         this.bUsedVehicle = false;
         this.useVehicleDuration = 0.0F;
      }
   }

    void checkActionGroup() {
    ActionGroup var1 = this.actionContext.getGroup();
      if (this.getVehicle() == nullptr) {
    ActionGroup var2 = ActionGroup.getActionGroup("player");
         if (var1 != var2) {
            this.advancedAnimator.OnAnimDataChanged(false);
            this.initializeStates();
            this.actionContext.setGroup(var2);
            this.clearVariable("bEnteringVehicle");
            this.clearVariable("EnterAnimationFinished");
            this.clearVariable("bExitingVehicle");
            this.clearVariable("ExitAnimationFinished");
            this.clearVariable("bSwitchingSeat");
            this.clearVariable("SwitchSeatAnimationFinished");
            this.setHitReaction("");
         }
      } else {
    ActionGroup var3 = ActionGroup.getActionGroup("player-vehicle");
         if (var1 != var3) {
            this.advancedAnimator.OnAnimDataChanged(false);
            this.initializeStates();
            this.actionContext.setGroup(var3);
         }
      }
   }

    BaseVehicle getUseableVehicle() {
      if (this.getVehicle() != nullptr) {
    return nullptr;
      } else {
    int var1 = ((int)this.x - 4) / 10 - 1;
    int var2 = ((int)this.y - 4) / 10 - 1;
    int var3 = (int)Math.ceil((this.x + 4.0F) / 10.0F) + 1;
    int var4 = (int)Math.ceil((this.y + 4.0F) / 10.0F) + 1;

         for (int var5 = var2; var5 < var4; var5++) {
            for (int var6 = var1; var6 < var3; var6++) {
               IsoChunk var7 = GameServer.bServer
                  ? ServerMap.instance.getChunk(var6, var5)
                  : IsoWorld.instance.CurrentCell.getChunkForGridSquare(var6 * 10, var5 * 10, 0);
               if (var7 != nullptr) {
                  for (int var8 = 0; var8 < var7.vehicles.size(); var8++) {
    BaseVehicle var9 = (BaseVehicle)var7.vehicles.get(var8);
                     if (var9.getUseablePart(this) != nullptr || var9.getBestSeat(this) != -1) {
    return var9;
                     }
                  }
               }
            }
         }

    return nullptr;
      }
   }

    bool isNearVehicle() {
      if (this.getVehicle() != nullptr) {
    return false;
      } else {
    int var1 = ((int)this.x - 4) / 10 - 1;
    int var2 = ((int)this.y - 4) / 10 - 1;
    int var3 = (int)Math.ceil((this.x + 4.0F) / 10.0F) + 1;
    int var4 = (int)Math.ceil((this.y + 4.0F) / 10.0F) + 1;

         for (int var5 = var2; var5 < var4; var5++) {
            for (int var6 = var1; var6 < var3; var6++) {
               IsoChunk var7 = GameServer.bServer
                  ? ServerMap.instance.getChunk(var6, var5)
                  : IsoWorld.instance.CurrentCell.getChunkForGridSquare(var6 * 10, var5 * 10, 0);
               if (var7 != nullptr) {
                  for (int var8 = 0; var8 < var7.vehicles.size(); var8++) {
    BaseVehicle var9 = (BaseVehicle)var7.vehicles.get(var8);
                     if (var9.getScript() != nullptr && var9.DistTo(this) < 3.5) {
    return true;
                     }
                  }
               }
            }
         }

    return false;
      }
   }

    BaseVehicle getNearVehicle() {
      if (this.getVehicle() != nullptr) {
    return nullptr;
      } else {
    int var1 = ((int)this.x - 4) / 10 - 1;
    int var2 = ((int)this.y - 4) / 10 - 1;
    int var3 = (int)Math.ceil((this.x + 4.0F) / 10.0F) + 1;
    int var4 = (int)Math.ceil((this.y + 4.0F) / 10.0F) + 1;

         for (int var5 = var2; var5 < var4; var5++) {
            for (int var6 = var1; var6 < var3; var6++) {
    IsoChunk var7 = GameServer.bServer ? ServerMap.instance.getChunk(var6, var5) : IsoWorld.instance.CurrentCell.getChunk(var6, var5);
               if (var7 != nullptr) {
                  for (int var8 = 0; var8 < var7.vehicles.size(); var8++) {
    BaseVehicle var9 = (BaseVehicle)var7.vehicles.get(var8);
                     if (var9.getScript() != nullptr
                        && (int)this.getZ() == (int)var9.getZ()
                        && (!this.isLocalPlayer() || var9.getTargetAlpha(this.PlayerIndex) != 0.0F)
                        && !(this.DistToSquared((int)var9.x, (int)var9.y) >= 16.0F)
                        && PolygonalMap2.instance
                           .intersectLineWithVehicle(
                              this.x, this.y, this.x + this.getForwardDirection().x * 4.0F, this.y + this.getForwardDirection().y * 4.0F, var9, tempVector2
                           )
                        && !PolygonalMap2.instance.lineClearCollide(this.x, this.y, tempVector2.x, tempVector2.y, (int)this.z, var9, false, true)) {
    return var9;
                     }
                  }
               }
            }
         }

    return nullptr;
      }
   }

    void updateWhileInVehicle() {
      this.bLookingWhileInVehicle = false;
    ActionGroup var1 = this.actionContext.getGroup();
    ActionGroup var2 = ActionGroup.getActionGroup("player-vehicle");
      if (var1 != var2) {
         this.advancedAnimator.OnAnimDataChanged(false);
         this.initializeStates();
         this.actionContext.setGroup(var2);
      }

      if (GameClient.bClient && this.getVehicle().getSeat(this) == -1) {
         DebugLog.log("forced " + this.getUsername() + " out of vehicle seat -1");
         this.setVehicle(nullptr);
      } else {
         this.dirtyRecalcGridStackTime = 10.0F;
         if (this.getVehicle().isDriver(this)) {
            this.getVehicle().updatePhysics();
    bool var3 = true;
            if (this.isAiming()) {
    WeaponType var4 = WeaponType.getWeaponType(this);
               if (var4 == WeaponType.firearm)) {
                  var3 = false;
               }
            }

            if (this.getVariableBoolean("isLoading")) {
               var3 = false;
            }

            if (var3) {
               this.getVehicle().updateControls();
            }
         } else {
    BaseVehicle var10 = this.getVehicle();
            if (var10.getDriver() == nullptr && var10.engineSpeed > var10.getScript().getEngineIdleSpeed()) {
               var10.engineSpeed = Math.max(
                  var10.engineSpeed - 50.0F * (GameTime.getInstance().getMultiplier() / 0.8F), (double)var10.getScript().getEngineIdleSpeed()
               );
            }

            if (GameClient.connection != nullptr) {
               PassengerMap.updatePassenger(this);
            }
         }

         this.fallTime = 0.0F;
         this.bSeenThisFrame = false;
         this.bCouldBeSeenThisFrame = false;
         this.closestZombie = 1000000.0F;
         this.setBeenMovingFor(this.getBeenMovingFor() - 0.625F * GameTime.getInstance().getMultiplier());
         if (!this.Asleep) {
    float var11 = (float)ZomboidGlobals.SittingEnduranceMultiplier;
            var11 *= 1.0F - this.stats.fatigue;
            var11 *= GameTime.instance.getMultiplier();
            this.stats.endurance = (float)(
               this.stats.endurance
                  + ZomboidGlobals.ImobileEnduranceReduce * SandboxOptions.instance.getEnduranceRegenMultiplier() * this.getRecoveryMod() * var11
            );
            this.stats.endurance = PZMath.clamp(this.stats.endurance, 0.0F, 1.0F);
         }

         this.updateToggleToAim();
         if (this.vehicle != nullptr) {
    Vector3f var14 = this.vehicle.getForwardVector(tempVector3f);
    bool var15 = this.isAimControlActive();
            if (this.PlayerIndex == 0) {
               if (Mouse.isButtonDown(1)) {
                  this.TimeRightPressed = this.TimeRightPressed + GameTime.getInstance().getRealworldSecondsSinceLastUpdate();
               } else {
                  this.TimeRightPressed = 0.0F;
               }

               var15 |= Mouse.isButtonDownUICheck(1) && this.TimeRightPressed >= 0.15F;
            }

            if (!var15 && this.isCurrentState(IdleState.instance())) {
               this.setForwardDirection(var14.x, var14.z);
               this.getForwardDirection().normalize();
            }

            if (this.lastAngle.x != this.getForwardDirection().x || this.lastAngle.y != this.getForwardDirection().y) {
               this.dirtyRecalcGridStackTime = 10.0F;
            }

            this.DirectionFromVector(this.getForwardDirection());
    AnimationPlayer var5 = this.getAnimationPlayer();
            if (var5 != nullptr && var5.isReady()) {
               var5.SetForceDir(this.getForwardDirection());
    float var6 = var5.getAngle() + var5.getTwistAngle();
               this.dir = IsoDirections.fromAngle(tempVector2.setLengthAndDirection(var6, 1.0F));
            }

    bool var16 = false;
    int var7 = this.vehicle.getSeat(this);
    VehiclePart var8 = this.vehicle.getPassengerDoor(var7);
            if (var8 != nullptr) {
    VehicleWindow var9 = var8.findWindow();
               if (var9 != nullptr && !var9.isHittable()) {
                  var16 = true;
               }
            }

            if (var16) {
               this.attackWhileInVehicle();
            } else if (var15) {
               this.bLookingWhileInVehicle = true;
               this.setAngleFromAim();
            } else {
               this.checkJoypadIgnoreAimUntilCentered();
               this.setIsAiming(false);
            }
         }

         this.updateCursorVisibility();
      }
   }

    void attackWhileInVehicle() {
      this.setIsAiming(false);
    bool var1 = false;
    bool var2 = false;
      if (GameWindow.ActivatedJoyPad != nullptr && this.JoypadBind != -1) {
         if (!this.bJoypadMovementActive) {
            return;
         }

         if (this.isChargingLT && !JoypadManager.instance.isLTPressed(this.JoypadBind)) {
            var2 = true;
         } else {
            var1 = this.isCharging && !JoypadManager.instance.isRTPressed(this.JoypadBind);
         }

    float var5 = JoypadManager.instance.getAimingAxisX(this.JoypadBind);
    float var4 = JoypadManager.instance.getAimingAxisY(this.JoypadBind);
         if (this.bJoypadIgnoreAimUntilCentered) {
            if (var5 == 0.0F && var4 == 0.0F) {
               this.bJoypadIgnoreAimUntilCentered = false;
            } else {
               var4 = 0.0F;
               var5 = 0.0F;
            }
         }

         this.setIsAiming(var5 * var5 + var4 * var4 >= 0.09F);
         this.isCharging = this.isAiming() && JoypadManager.instance.isRTPressed(this.JoypadBind);
         this.isChargingLT = this.isAiming() && JoypadManager.instance.isLTPressed(this.JoypadBind);
      } else {
    bool var3 = this.isAimKeyDown();
         this.setIsAiming(var3 || Mouse.isButtonDownUICheck(1) && this.TimeRightPressed >= 0.15F);
         if (this.isCharging) {
            this.isCharging = var3 || Mouse.isButtonDown(1);
         } else {
            this.isCharging = var3 || Mouse.isButtonDownUICheck(1) && this.TimeRightPressed >= 0.15F;
         }

         if (this.isForceAim()) {
            this.setIsAiming(true);
            this.isCharging = true;
         }

         if (GameKeyboard.isKeyDown(Core.getInstance().getKey("Melee")) && this.authorizeMeleeAction) {
            var2 = true;
         } else {
            var1 = this.isCharging && Mouse.isButtonDownUICheck(0);
            if (var1) {
               this.setIsAiming(true);
            }
         }
      }

      if (!this.isCharging && !this.isChargingLT) {
         this.chargeTime = 0.0F;
      }

      if (this.isAiming() && !this.bBannedAttacking && this.CanAttack()) {
         this.chargeTime = this.chargeTime + GameTime.instance.getMultiplier();
         this.useChargeTime = this.chargeTime;
         this.m_meleePressed = var2;
         this.setAngleFromAim();
         if (var2) {
            this.sprite.Animate = true;
            this.setDoShove(true);
            this.AttemptAttack(this.useChargeTime);
            this.useChargeTime = 0.0F;
            this.chargeTime = 0.0F;
         } else if (var1) {
            this.sprite.Animate = true;
            if (this.getRecoilDelay() <= 0.0F) {
               this.AttemptAttack(this.useChargeTime);
            }

            this.useChargeTime = 0.0F;
            this.chargeTime = 0.0F;
         }
      }
   }

    void setAngleFromAim() {
    Vector2 var1 = tempVector2;
      if (GameWindow.ActivatedJoyPad != nullptr && this.JoypadBind != -1) {
         this.getControllerAimDir(var1);
      } else {
         var1.set(this.getX(), this.getY());
    int var2 = Mouse.getX();
    int var3 = Mouse.getY();
         var1.x = var1.x - IsoUtils.XToIso(var2, var3 + 55.0F * this.def.getScaleY(), this.getZ());
         var1.y = var1.y - IsoUtils.YToIso(var2, var3 + 55.0F * this.def.getScaleY(), this.getZ());
         var1.x = -var1.x;
         var1.y = -var1.y;
      }

      if (var1.getLengthSquared() > 0.0F) {
         var1.normalize();
         this.DirectionFromVector(var1);
         this.setForwardDirection(var1);
         if (this.lastAngle.x != var1.x || this.lastAngle.y != var1.y) {
            this.lastAngle.x = var1.x;
            this.lastAngle.y = var1.y;
            this.dirtyRecalcGridStackTime = 10.0F;
         }
      }
   }

    void updateTorchStrength() {
      if (this.getTorchStrength() > 0.0F || this.flickTorch) {
    DrainableComboItem var1 = (DrainableComboItem)Type.tryCastTo(this.getActiveLightItem(), DrainableComboItem.class);
         if (var1 == nullptr) {
            return;
         }

         if (Rand.Next(600 - (int)(0.4 / var1.getUsedDelta() * 100.0)) == 0) {
            this.flickTorch = true;
         }

         this.flickTorch = false;
         if (this.flickTorch) {
            if (Rand.Next(6) == 0) {
               var1.setActivated(false);
            } else {
               var1.setActivated(true);
            }

            if (Rand.Next(40) == 0) {
               this.flickTorch = false;
               var1.setActivated(true);
            }
         }
      }
   }

    IsoCell getCell() {
      return IsoWorld.instance.CurrentCell;
   }

    void calculateContext() {
    float var1 = this.x;
    float var2 = this.y;
    float var3 = this.x;
      IsoGridSquare[] var4 = new IsoGridSquare[4];
      if (this.dir == IsoDirections.N) {
         var4[2] = this.getCell().getGridSquare(var1 - 1.0F, var2 - 1.0F, var3);
         var4[1] = this.getCell().getGridSquare(var1, var2 - 1.0F, var3);
         var4[3] = this.getCell().getGridSquare(var1 + 1.0F, var2 - 1.0F, var3);
      } else if (this.dir == IsoDirections.NE) {
         var4[2] = this.getCell().getGridSquare(var1, var2 - 1.0F, var3);
         var4[1] = this.getCell().getGridSquare(var1 + 1.0F, var2 - 1.0F, var3);
         var4[3] = this.getCell().getGridSquare(var1 + 1.0F, var2, var3);
      } else if (this.dir == IsoDirections.E) {
         var4[2] = this.getCell().getGridSquare(var1 + 1.0F, var2 - 1.0F, var3);
         var4[1] = this.getCell().getGridSquare(var1 + 1.0F, var2, var3);
         var4[3] = this.getCell().getGridSquare(var1 + 1.0F, var2 + 1.0F, var3);
      } else if (this.dir == IsoDirections.SE) {
         var4[2] = this.getCell().getGridSquare(var1 + 1.0F, var2, var3);
         var4[1] = this.getCell().getGridSquare(var1 + 1.0F, var2 + 1.0F, var3);
         var4[3] = this.getCell().getGridSquare(var1, var2 + 1.0F, var3);
      } else if (this.dir == IsoDirections.S) {
         var4[2] = this.getCell().getGridSquare(var1 + 1.0F, var2 + 1.0F, var3);
         var4[1] = this.getCell().getGridSquare(var1, var2 + 1.0F, var3);
         var4[3] = this.getCell().getGridSquare(var1 - 1.0F, var2 + 1.0F, var3);
      } else if (this.dir == IsoDirections.SW) {
         var4[2] = this.getCell().getGridSquare(var1, var2 + 1.0F, var3);
         var4[1] = this.getCell().getGridSquare(var1 - 1.0F, var2 + 1.0F, var3);
         var4[3] = this.getCell().getGridSquare(var1 - 1.0F, var2, var3);
      } else if (this.dir == IsoDirections.W) {
         var4[2] = this.getCell().getGridSquare(var1 - 1.0F, var2 + 1.0F, var3);
         var4[1] = this.getCell().getGridSquare(var1 - 1.0F, var2, var3);
         var4[3] = this.getCell().getGridSquare(var1 - 1.0F, var2 - 1.0F, var3);
      } else if (this.dir == IsoDirections.NW) {
         var4[2] = this.getCell().getGridSquare(var1 - 1.0F, var2, var3);
         var4[1] = this.getCell().getGridSquare(var1 - 1.0F, var2 - 1.0F, var3);
         var4[3] = this.getCell().getGridSquare(var1, var2 - 1.0F, var3);
      }

      var4[0] = this.current;

      for (int var5 = 0; var5 < 4; var5++) {
    IsoGridSquare var6 = var4[var5];
         if (var6 == nullptr) {
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    bool isSafeToClimbOver(IsoDirections var1) {
    void* var2 = nullptr;
      switch (2.$SwitchMap$zombie$iso$IsoDirections[var1.ordinal()]) {
         case 1:
            var2 = this.getCell().getGridSquare(this.x, this.y - 1.0F, this.z);
            break;
         case 2:
            var2 = this.getCell().getGridSquare(this.x, this.y + 1.0F, this.z);
            break;
         case 3:
            var2 = this.getCell().getGridSquare(this.x - 1.0F, this.y, this.z);
            break;
         case 4:
            var2 = this.getCell().getGridSquare(this.x + 1.0F, this.y, this.z);
            break;
         default:
    return false;
      }

      if (var2 == nullptr) {
    return false;
      } else if (var2.Is(IsoFlagType.water)) {
    return false;
      } else {
         return !var2.TreatAsSolidFloor() ? var2.HasStairsBelow() : true;
      }
   }

    bool doContext(IsoDirections var1) {
      if (this.isIgnoreContextKey()) {
    return false;
      } else if (this.isBlockMovement()) {
    return false;
      } else {
         for (int var2 = 0; var2 < this.getCell().vehicles.size(); var2++) {
    BaseVehicle var3 = (BaseVehicle)this.getCell().vehicles.get(var2);
            if (var3.getUseablePart(this) != nullptr) {
    return false;
            }
         }

    float var7 = this.x - (int)this.x;
    float var10 = this.y - (int)this.y;
    IsoDirections var4 = IsoDirections.Max;
    IsoDirections var5 = IsoDirections.Max;
         if (var1 == IsoDirections.NW) {
            if (var10 < var7) {
               if (this.doContextNSWE(IsoDirections.N)) {
    return true;
               }

               if (this.doContextNSWE(IsoDirections.W)) {
    return true;
               }

               var4 = IsoDirections.S;
               var5 = IsoDirections.E;
            } else {
               if (this.doContextNSWE(IsoDirections.W)) {
    return true;
               }

               if (this.doContextNSWE(IsoDirections.N)) {
    return true;
               }

               var4 = IsoDirections.E;
               var5 = IsoDirections.S;
            }
         } else if (var1 == IsoDirections.NE) {
            var7 = 1.0F - var7;
            if (var10 < var7) {
               if (this.doContextNSWE(IsoDirections.N)) {
    return true;
               }

               if (this.doContextNSWE(IsoDirections.E)) {
    return true;
               }

               var4 = IsoDirections.S;
               var5 = IsoDirections.W;
            } else {
               if (this.doContextNSWE(IsoDirections.E)) {
    return true;
               }

               if (this.doContextNSWE(IsoDirections.N)) {
    return true;
               }

               var4 = IsoDirections.W;
               var5 = IsoDirections.S;
            }
         } else if (var1 == IsoDirections.SE) {
            var7 = 1.0F - var7;
            var10 = 1.0F - var10;
            if (var10 < var7) {
               if (this.doContextNSWE(IsoDirections.S)) {
    return true;
               }

               if (this.doContextNSWE(IsoDirections.E)) {
    return true;
               }

               var4 = IsoDirections.N;
               var5 = IsoDirections.W;
            } else {
               if (this.doContextNSWE(IsoDirections.E)) {
    return true;
               }

               if (this.doContextNSWE(IsoDirections.S)) {
    return true;
               }

               var4 = IsoDirections.W;
               var5 = IsoDirections.N;
            }
         } else if (var1 == IsoDirections.SW) {
            var10 = 1.0F - var10;
            if (var10 < var7) {
               if (this.doContextNSWE(IsoDirections.S)) {
    return true;
               }

               if (this.doContextNSWE(IsoDirections.W)) {
    return true;
               }

               var4 = IsoDirections.N;
               var5 = IsoDirections.E;
            } else {
               if (this.doContextNSWE(IsoDirections.W)) {
    return true;
               }

               if (this.doContextNSWE(IsoDirections.S)) {
    return true;
               }

               var4 = IsoDirections.E;
               var5 = IsoDirections.N;
            }
         } else {
            if (this.doContextNSWE(var1)) {
    return true;
            }

            var4 = var1.RotLeft(4);
         }

         if (var4 != IsoDirections.Max) {
    IsoObject var6 = this.getContextDoorOrWindowOrWindowFrame(var4);
            if (var6 != nullptr) {
               this.doContextDoorOrWindowOrWindowFrame(var4, var6);
    return true;
            }
         }

         if (var5 != IsoDirections.Max) {
    IsoObject var14 = this.getContextDoorOrWindowOrWindowFrame(var5);
            if (var14 != nullptr) {
               this.doContextDoorOrWindowOrWindowFrame(var5, var14);
    return true;
            }
         }

    return false;
      }
   }

    bool doContextNSWE(IsoDirections var1) {
    assert var1 = = IsoDirections.N || var1 == IsoDirections.S || var1 == IsoDirections.W || var1 == IsoDirections.E;

      if (this.current == nullptr) {
    return false;
      } else if (var1 == IsoDirections.N && this.current.Is(IsoFlagType.climbSheetN) && this.canClimbSheetRope(this.current)) {
         this.climbSheetRope();
    return true;
      } else if (var1 == IsoDirections.S && this.current.Is(IsoFlagType.climbSheetS) && this.canClimbSheetRope(this.current)) {
         this.climbSheetRope();
    return true;
      } else if (var1 == IsoDirections.W && this.current.Is(IsoFlagType.climbSheetW) && this.canClimbSheetRope(this.current)) {
         this.climbSheetRope();
    return true;
      } else if (var1 == IsoDirections.E && this.current.Is(IsoFlagType.climbSheetE) && this.canClimbSheetRope(this.current)) {
         this.climbSheetRope();
    return true;
      } else {
    IsoGridSquare var2 = this.current.nav[var1.index()];
    bool var3 = IsoWindow.isTopOfSheetRopeHere(var2) && this.canClimbDownSheetRope(var2);
    IsoObject var4 = this.getContextDoorOrWindowOrWindowFrame(var1);
         if (var4 != nullptr) {
            this.doContextDoorOrWindowOrWindowFrame(var1, var4);
    return true;
         } else {
            if (GameKeyboard.isKeyDown(42) && this.current != nullptr && this.ticksSincePressedMovement > 15.0F) {
    IsoObject var5 = this.current.getDoor(true);
               if (dynamic_cast<IsoDoor*>(var5) != nullptr && ((IsoDoor)var5).isFacingSheet(this)) {
                  ((IsoDoor)var5).toggleCurtain();
    return true;
               }

    IsoObject var6 = this.current.getDoor(false);
               if (dynamic_cast<IsoDoor*>(var6) != nullptr && ((IsoDoor)var6).isFacingSheet(this)) {
                  ((IsoDoor)var6).toggleCurtain();
    return true;
               }

               if (var1 == IsoDirections.E) {
    IsoGridSquare var7 = IsoWorld.instance.CurrentCell.getGridSquare(this.x + 1.0F, this.y, this.z);
    IsoObject var8 = var7 != nullptr ? var7.getDoor(true) : nullptr;
                  if (dynamic_cast<IsoDoor*>(var8) != nullptr && ((IsoDoor)var8).isFacingSheet(this)) {
                     ((IsoDoor)var8).toggleCurtain();
    return true;
                  }
               }

               if (var1 == IsoDirections.S) {
    IsoGridSquare var10 = IsoWorld.instance.CurrentCell.getGridSquare(this.x, this.y + 1.0F, this.z);
    IsoObject var11 = var10 != nullptr ? var10.getDoor(false) : nullptr;
                  if (dynamic_cast<IsoDoor*>(var11) != nullptr && ((IsoDoor)var11).isFacingSheet(this)) {
                     ((IsoDoor)var11).toggleCurtain();
    return true;
                  }
               }
            }

    bool var9 = this.isSafeToClimbOver(var1);
            if (this.z > 0.0F && var3) {
               var9 = true;
            }

            if (this.timePressedContext < 0.5F && !var9) {
    return false;
            } else if (this.ignoreAutoVault) {
    return false;
            } else if (var1 == IsoDirections.N && this.getCurrentSquare().Is(IsoFlagType.HoppableN)) {
               this.climbOverFence(var1);
    return true;
            } else if (var1 == IsoDirections.W && this.getCurrentSquare().Is(IsoFlagType.HoppableW)) {
               this.climbOverFence(var1);
    return true;
            } else if (var1 == IsoDirections.S
               && IsoWorld.instance.CurrentCell.getGridSquare(this.x, this.y + 1.0F, this.z) != nullptr
               && IsoWorld.instance.CurrentCell.getGridSquare(this.x, this.y + 1.0F, this.z).Is(IsoFlagType.HoppableN)) {
               this.climbOverFence(var1);
    return true;
            } else if (var1 == IsoDirections.E
               && IsoWorld.instance.CurrentCell.getGridSquare(this.x + 1.0F, this.y, this.z) != nullptr
               && IsoWorld.instance.CurrentCell.getGridSquare(this.x + 1.0F, this.y, this.z).Is(IsoFlagType.HoppableW)) {
               this.climbOverFence(var1);
    return true;
            } else {
               return this.climbOverWall(var1);
            }
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    IsoObject getContextDoorOrWindowOrWindowFrame(IsoDirections var1) {
      if (this.current != nullptr && var1 != nullptr) {
    IsoGridSquare var2 = this.current.nav[var1.index()];
    IsoObject var3 = nullptr;
         switch (2.$SwitchMap$zombie$iso$IsoDirections[var1.ordinal()]) {
            case 1:
               var3 = this.current.getOpenDoor(var1);
               if (var3 != nullptr) {
    return var3;
               }

               var3 = this.current.getDoorOrWindowOrWindowFrame(var1, true);
               if (var3 != nullptr) {
    return var3;
               }

               var3 = this.current.getDoor(true);
               if (var3 != nullptr) {
    return var3;
               }

               if (var2 != nullptr && !this.current.isBlockedTo(var2)) {
                  var3 = var2.getOpenDoor(IsoDirections.S);
               }
               break;
            case 2:
               var3 = this.current.getOpenDoor(var1);
               if (var3 != nullptr) {
    return var3;
               }

               if (var2 != nullptr) {
    bool var4 = this.current.isBlockedTo(var2);
                  var3 = var2.getDoorOrWindowOrWindowFrame(IsoDirections.N, var4);
                  if (var3 != nullptr) {
    return var3;
                  }

                  var3 = var2.getDoor(true);
               }
               break;
            case 3:
               var3 = this.current.getOpenDoor(var1);
               if (var3 != nullptr) {
    return var3;
               }

               var3 = this.current.getDoorOrWindowOrWindowFrame(var1, true);
               if (var3 != nullptr) {
    return var3;
               }

               var3 = this.current.getDoor(false);
               if (var3 != nullptr) {
    return var3;
               }

               if (var2 != nullptr && !this.current.isBlockedTo(var2)) {
                  var3 = var2.getOpenDoor(IsoDirections.E);
               }
               break;
            case 4:
               var3 = this.current.getOpenDoor(var1);
               if (var3 != nullptr) {
    return var3;
               }

               if (var2 != nullptr) {
    bool var5 = this.current.isBlockedTo(var2);
                  var3 = var2.getDoorOrWindowOrWindowFrame(IsoDirections.W, var5);
                  if (var3 != nullptr) {
    return var3;
                  }

                  var3 = var2.getDoor(false);
               }
         }

    return var3;
      } else {
    return nullptr;
      }
   }

    void doContextDoorOrWindowOrWindowFrame(IsoDirections var1, IsoObject var2) {
    IsoGridSquare var3 = this.current.nav[var1.index()];
    bool var4 = IsoWindow.isTopOfSheetRopeHere(var3) && this.canClimbDownSheetRope(var3);
      if (dynamic_cast<IsoDoor*>(var2) != nullptr var5) {
         if (GameKeyboard.isKeyDown(42) && var5.HasCurtains() != nullptr && var5.isFacingSheet(this) && this.ticksSincePressedMovement > 15.0F) {
            var5.toggleCurtain();
         } else if (this.timePressedContext >= 0.5F) {
            if (var5.isHoppable() && !this.isIgnoreAutoVault()) {
               this.climbOverFence(var1);
            } else {
               var5.ToggleDoor(this);
            }
         } else {
            var5.ToggleDoor(this);
         }
      } else if (dynamic_cast<IsoThumpable*>(var2) != nullptr && ((IsoThumpable)var2).isDoor()) {
    IsoThumpable var10 = (IsoThumpable)var2;
         if (this.timePressedContext >= 0.5F) {
            if (var10.isHoppable() && !this.isIgnoreAutoVault()) {
               this.climbOverFence(var1);
            } else {
               var10.ToggleDoor(this);
            }
         } else {
            var10.ToggleDoor(this);
         }
      } else if (dynamic_cast<IsoWindow*>(var2) != nullptr && !var2.getSquare().getProperties().Is(IsoFlagType.makeWindowInvincible)) {
    IsoWindow var9 = (IsoWindow)var2;
         if (GameKeyboard.isKeyDown(42)) {
    IsoCurtain var11 = var9.HasCurtains();
            if (var11 != nullptr && this.current != nullptr && !var11.getSquare().isBlockedTo(this.current)) {
               var11.ToggleDoor(this);
            }
         } else if (this.timePressedContext >= 0.5F) {
            if (var9.canClimbThrough(this)) {
               this.climbThroughWindow(var9);
            } else if (!var9.PermaLocked && !var9.isBarricaded() && !var9.IsOpen() && !var9.isDestroyed()) {
               this.openWindow(var9);
            }
         } else if (var9.Health > 0 && !var9.isDestroyed()) {
    IsoBarricade var12 = var9.getBarricadeForCharacter(this);
            if (!var9.open && var12 == nullptr) {
               this.openWindow(var9);
            } else if (var12 == nullptr) {
               this.closeWindow(var9);
            }
         } else if (var9.isGlassRemoved()) {
            if (!this.isSafeToClimbOver(var1) && !var2.getSquare().haveSheetRope && !var4) {
               return;
            }

            if (!var9.isBarricaded()) {
               this.climbThroughWindow(var9);
            }
         }
      } else if (dynamic_cast<IsoThumpable*>(var2) != nullptr && !var2.getSquare().getProperties().Is(IsoFlagType.makeWindowInvincible)) {
    IsoThumpable var8 = (IsoThumpable)var2;
         if (GameKeyboard.isKeyDown(42)) {
    IsoCurtain var6 = var8.HasCurtains();
            if (var6 != nullptr && this.current != nullptr && !var6.getSquare().isBlockedTo(this.current)) {
               var6.ToggleDoor(this);
            }
         } else if (this.timePressedContext >= 0.5F) {
            if (var8.canClimbThrough(this)) {
               this.climbThroughWindow(var8);
            }
         } else {
            if (!this.isSafeToClimbOver(var1) && !var2.getSquare().haveSheetRope && !var4) {
               return;
            }

            if (var8.canClimbThrough(this)) {
               this.climbThroughWindow(var8);
            }
         }
      } else if (IsoWindowFrame.isWindowFrame(var2)) {
         if (GameKeyboard.isKeyDown(42)) {
    IsoCurtain var7 = IsoWindowFrame.getCurtain(var2);
            if (var7 != nullptr && this.current != nullptr && !var7.getSquare().isBlockedTo(this.current)) {
               var7.ToggleDoor(this);
            }
         } else if ((this.timePressedContext >= 0.5F || this.isSafeToClimbOver(var1) || var4) && IsoWindowFrame.canClimbThrough(var2, this)) {
            this.climbThroughWindowFrame(var2);
         }
      }
   }

    bool hopFence(IsoDirections var1, bool var2) {
    float var4 = this.x - (int)this.x;
    float var5 = this.y - (int)this.y;
      if (var1 == IsoDirections.NW) {
         if (var5 < var4) {
            return this.hopFence(IsoDirections.N, var2) ? true : this.hopFence(IsoDirections.W, var2);
         } else {
            return this.hopFence(IsoDirections.W, var2) ? true : this.hopFence(IsoDirections.N, var2);
         }
      } else if (var1 == IsoDirections.NE) {
         var4 = 1.0F - var4;
         if (var5 < var4) {
            return this.hopFence(IsoDirections.N, var2) ? true : this.hopFence(IsoDirections.E, var2);
         } else {
            return this.hopFence(IsoDirections.E, var2) ? true : this.hopFence(IsoDirections.N, var2);
         }
      } else if (var1 == IsoDirections.SE) {
         var4 = 1.0F - var4;
         var5 = 1.0F - var5;
         if (var5 < var4) {
            return this.hopFence(IsoDirections.S, var2) ? true : this.hopFence(IsoDirections.E, var2);
         } else {
            return this.hopFence(IsoDirections.E, var2) ? true : this.hopFence(IsoDirections.S, var2);
         }
      } else if (var1 == IsoDirections.SW) {
         var5 = 1.0F - var5;
         if (var5 < var4) {
            return this.hopFence(IsoDirections.S, var2) ? true : this.hopFence(IsoDirections.W, var2);
         } else {
            return this.hopFence(IsoDirections.W, var2) ? true : this.hopFence(IsoDirections.S, var2);
         }
      } else if (this.current == nullptr) {
    return false;
      } else {
    IsoGridSquare var6 = this.current.nav[var1.index()];
         if (var6 != nullptr && !var6.Is(IsoFlagType.water)) {
            if (var1 == IsoDirections.N && this.getCurrentSquare().Is(IsoFlagType.HoppableN)) {
               if (var2) {
    return true;
               } else {
                  this.climbOverFence(var1);
    return true;
               }
            } else if (var1 == IsoDirections.W && this.getCurrentSquare().Is(IsoFlagType.HoppableW)) {
               if (var2) {
    return true;
               } else {
                  this.climbOverFence(var1);
    return true;
               }
            } else if (var1 == IsoDirections.S
               && IsoWorld.instance.CurrentCell.getGridSquare(this.x, this.y + 1.0F, this.z) != nullptr
               && IsoWorld.instance.CurrentCell.getGridSquare(this.x, this.y + 1.0F, this.z).Is(IsoFlagType.HoppableN)) {
               if (var2) {
    return true;
               } else {
                  this.climbOverFence(var1);
    return true;
               }
            } else if (var1 != IsoDirections.E
               || IsoWorld.instance.CurrentCell.getGridSquare(this.x + 1.0F, this.y, this.z) == nullptr
               || !IsoWorld.instance.CurrentCell.getGridSquare(this.x + 1.0F, this.y, this.z).Is(IsoFlagType.HoppableW)) {
    return false;
            } else if (var2) {
    return true;
            } else {
               this.climbOverFence(var1);
    return true;
            }
         } else {
    return false;
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    bool canClimbOverWall(IsoDirections var1) {
      if (this.isSprinting()) {
    return false;
      } else if (!this.isSafeToClimbOver(var1) || this.current == nullptr) {
    return false;
      } else if (this.current.haveRoof) {
    return false;
      } else if (this.current.getBuilding() != nullptr) {
    return false;
      } else {
    IsoGridSquare var2 = IsoWorld.instance.CurrentCell.getGridSquare(this.current.x, this.current.y, this.current.z + 1);
         if (var2 != nullptr && var2.HasSlopedRoof()) {
    return false;
         } else {
    IsoGridSquare var3 = this.current.nav[var1.index()];
            if (var3.haveRoof) {
    return false;
            } else if (var3.isSolid() || var3.isSolidTrans()) {
    return false;
            } else if (var3.getBuilding() != nullptr) {
    return false;
            } else {
    IsoGridSquare var4 = IsoWorld.instance.CurrentCell.getGridSquare(var3.x, var3.y, var3.z + 1);
               if (var4 != nullptr && var4.HasSlopedRoof()) {
    return false;
               } else {
                  switch (2.$SwitchMap$zombie$iso$IsoDirections[var1.ordinal()]) {
                     case 1:
                        if (this.current.Is(IsoFlagType.CantClimb)) {
    return false;
                        }

                        if (!this.current.Has(IsoObjectType.wall)) {
    return false;
                        }

                        if (!this.current.Is(IsoFlagType.collideN)) {
    return false;
                        }

                        if (this.current.Is(IsoFlagType.HoppableN)) {
    return false;
                        }

                        if (var2 != nullptr && var2.Is(IsoFlagType.collideN)) {
    return false;
                        }
                        break;
                     case 2:
                        if (var3.Is(IsoFlagType.CantClimb)) {
    return false;
                        }

                        if (!var3.Has(IsoObjectType.wall)) {
    return false;
                        }

                        if (!var3.Is(IsoFlagType.collideN)) {
    return false;
                        }

                        if (var3.Is(IsoFlagType.HoppableN)) {
    return false;
                        }

                        if (var4 != nullptr && var4.Is(IsoFlagType.collideN)) {
    return false;
                        }
                        break;
                     case 3:
                        if (this.current.Is(IsoFlagType.CantClimb)) {
    return false;
                        }

                        if (!this.current.Has(IsoObjectType.wall)) {
    return false;
                        }

                        if (!this.current.Is(IsoFlagType.collideW)) {
    return false;
                        }

                        if (this.current.Is(IsoFlagType.HoppableW)) {
    return false;
                        }

                        if (var2 != nullptr && var2.Is(IsoFlagType.collideW)) {
    return false;
                        }
                        break;
                     case 4:
                        if (var3.Is(IsoFlagType.CantClimb)) {
    return false;
                        }

                        if (!var3.Has(IsoObjectType.wall)) {
    return false;
                        }

                        if (!var3.Is(IsoFlagType.collideW)) {
    return false;
                        }

                        if (var3.Is(IsoFlagType.HoppableW)) {
    return false;
                        }

                        if (var4 != nullptr && var4.Is(IsoFlagType.collideW)) {
    return false;
                        }
                        break;
                     default:
    return false;
                  }

                  return IsoWindow.canClimbThroughHelper(this, this.current, var3, var1 == IsoDirections.N || var1 == IsoDirections.S);
               }
            }
         }
      }
   }

    bool climbOverWall(IsoDirections var1) {
      if (!this.canClimbOverWall(var1)) {
    return false;
      } else {
         this.dropHeavyItems();
         ClimbOverWallState.instance().setParams(this, var1);
         this.actionContext.reportEvent("EventClimbWall");
    return true;
      }
   }

    void updateSleepingPillsTaken() {
      if (this.getSleepingPillsTaken() > 0 && this.lastPillsTaken > 0L && GameTime.instance.Calender.getTimeInMillis() - this.lastPillsTaken > 7200000L) {
         this.setSleepingPillsTaken(this.getSleepingPillsTaken() - 1);
      }
   }

    bool AttemptAttack() {
      return this.DoAttack(this.useChargeTime);
   }

    bool DoAttack(float var1) {
      return this.DoAttack(var1, false, nullptr);
   }

    bool DoAttack(float var1, bool var2, const std::string& var3) {
      if (!this.authorizeMeleeAction) {
    return false;
      } else {
         this.setForceShove(var2);
         this.setClickSound(var3);
         this.pressedAttack(true);
    return false;
      }
   }

    int getPlayerNum() {
      return this.PlayerIndex;
   }

    void updateLOS() {
      this.spottedList.clear();
      this.stats.NumVisibleZombies = 0;
      this.stats.LastNumChasingZombies = this.stats.NumChasingZombies;
      this.stats.NumChasingZombies = 0;
      this.stats.MusicZombiesTargeting = 0;
      this.stats.MusicZombiesVisible = 0;
      this.NumSurvivorsInVicinity = 0;
      if (this.getCurrentSquare() != nullptr) {
    bool var1 = GameServer.bServer;
    bool var2 = GameClient.bClient;
    int var3 = this.PlayerIndex;
    IsoPlayer var4 = getInstance();
    float var5 = this.getX();
    float var6 = this.getY();
    float var7 = this.getZ();
    int var8 = 0;
    int var9 = 0;
    int var10 = this.getCell().getObjectList().size();

         for (int var11 = 0; var11 < var10; var11++) {
    IsoMovingObject var12 = (IsoMovingObject)this.getCell().getObjectList().get(var11);
            if (!(dynamic_cast<IsoPhysicsObject*>(var12) != nullptr) && !(dynamic_cast<BaseVehicle*>(var12) != nullptr)) {
               if (var12 == this) {
                  this.spottedList.push_back(var12);
               } else {
    float var13 = var12.getX();
    float var14 = var12.getY();
    float var15 = var12.getZ();
    float var16 = IsoUtils.DistanceTo(var13, var14, var5, var6);
                  if (var16 < 20.0F) {
                     var8++;
                  }

    IsoGridSquare var17 = var12.getCurrentSquare();
                  if (var17 != nullptr) {
                     if (this.isSeeEveryone()) {
                        var12.setAlphaAndTarget(var3, 1.0F);
                     } else {
    IsoGameCharacter var18 = (IsoGameCharacter)Type.tryCastTo(var12, IsoGameCharacter.class);
    IsoPlayer var19 = (IsoPlayer)Type.tryCastTo(var18, IsoPlayer.class);
    IsoZombie var20 = (IsoZombie)Type.tryCastTo(var18, IsoZombie.class);
                        if (var4 != nullptr && var12 != var4 && var18 != nullptr && var18.isInvisible() && var4.accessLevel.empty()) {
                           var18.setAlphaAndTarget(var3, 0.0F);
                        } else {
    float var21 = this.getSeeNearbyCharacterDistance();
    bool var22;
                           if (var1) {
                              var22 = ServerLOS.instance.isCouldSee(this, var17);
                           } else {
                              var22 = var17.isCouldSee(var3);
                           }

    bool var23;
                           if (var2 && var19 != nullptr) {
                              var23 = true;
                           } else if (!var1) {
                              var23 = var17.isCanSee(var3);
                           } else {
                              var23 = var22;
                           }

                           if (!this.isAsleep() && (var23 || var16 < var21 && var22)) {
                              this.TestZombieSpotPlayer(var12);
                              if (var18 != nullptr && var18.IsVisibleToPlayer[var3]) {
                                 if (dynamic_cast<IsoSurvivor*>(var18) != nullptr) {
                                    this.NumSurvivorsInVicinity++;
                                 }

                                 if (var20 != nullptr) {
                                    this.lastSeenZombieTime = 0.0;
                                    if (var15 >= var7 - 1.0F
                                       && var16 < 7.0F
                                       && !var20.Ghost
                                       && !var20.isFakeDead()
                                       && var17.getRoom() == this.getCurrentSquare().getRoom()) {
                                       this.TicksSinceSeenZombie = 0;
                                       this.stats.NumVisibleZombies++;
                                    }

                                    if (var16 < 3.0F) {
                                       var9++;
                                    }

                                    if (!var20.isSceneCulled()) {
                                       this.stats.MusicZombiesVisible++;
                                       if (var20.target == this) {
                                          this.stats.MusicZombiesTargeting++;
                                       }
                                    }
                                 }

                                 this.spottedList.push_back(var18);
                                 if (!(dynamic_cast<IsoPlayer*>(var19) != nullptr) && !this.bRemote) {
                                    if (var19 != nullptr && var19 != var4) {
                                       var19.setTargetAlpha(var3, 1.0F);
                                    } else {
                                       var18.setTargetAlpha(var3, 1.0F);
                                    }
                                 }

    float var24 = 4.0F;
                                 if (this.stats.NumVisibleZombies > 4) {
                                    var24 = 7.0F;
                                 }

                                 if (var16 < var24 && dynamic_cast<IsoZombie*>(var18) != nullptr && (int)var15 == (int)var7 && !this.isGhostMode() && !var2) {
                                    GameTime.instance.setMultiplier(1.0F);
                                    if (!var1) {
                                       UIManager.getSpeedControls().SetCurrentGameSpeed(1);
                                    }
                                 }

                                 if (var16 < var24 && dynamic_cast<IsoZombie*>(var18) != nullptr && (int)var15 == (int)var7 && !this.LastSpotted.contains(var18)) {
                                    this.stats.NumVisibleZombies += 2;
                                 }
                              }
                           } else {
                              if (var12 != instance) {
                                 var12.setTargetAlpha(var3, 0.0F);
                              }

                              if (var22) {
                                 this.TestZombieSpotPlayer(var12);
                              }
                           }

                           if (var16 < 2.0F && var12.getTargetAlpha(var3) == 1.0F && !this.bRemote) {
                              var12.setAlpha(var3, 1.0F);
                           }
                        }
                     }
                  }
               }
            }
         }

         if (this.isAlive()
            && var9 > 0
            && this.stats.LastVeryCloseZombies == 0
            && this.stats.NumVisibleZombies > 0
            && this.stats.LastNumVisibleZombies == 0
            && this.timeSinceLastStab >= 600.0F) {
            this.timeSinceLastStab = 0.0F;
    long var25 = this.getEmitter().playSoundImpl("ZombieSurprisedPlayer", nullptr);
            this.getEmitter().setVolume(var25, Core.getInstance().getOptionJumpScareVolume() / 10.0F);
         }

         if (this.stats.NumVisibleZombies > 0) {
            this.timeSinceLastStab = 0.0F;
         }

         if (this.timeSinceLastStab < 600.0F) {
            this.timeSinceLastStab = this.timeSinceLastStab + GameTime.getInstance().getMultiplier() / 1.6F;
         }

    float var26 = var8 / 20.0F;
         if (var26 > 1.0F) {
            var26 = 1.0F;
         }

         var26 *= 0.6F;
         SoundManager.instance.BlendVolume(MainScreenState.ambient, var26);
    int var28 = 0;

         for (int var29 = 0; var29 < this.spottedList.size(); var29++) {
            if (!this.LastSpotted.contains(this.spottedList.get(var29))) {
               this.LastSpotted.push_back(this.spottedList.get(var29));
            }

            if (this.spottedList.get(var29) instanceof IsoZombie) {
               var28++;
            }
         }

         if (this.ClearSpottedTimer <= 0 && var28 == 0) {
            this.LastSpotted.clear();
            this.ClearSpottedTimer = 1000;
         } else {
            this.ClearSpottedTimer--;
         }

         this.stats.LastNumVisibleZombies = this.stats.NumVisibleZombies;
         this.stats.LastVeryCloseZombies = var9;
      }
   }

    float getSeeNearbyCharacterDistance() {
      return 3.5F - this.stats.getFatigue();
   }

    bool checkSpottedPLayerTimer(IsoPlayer var1) {
      if (!var1.spottedByPlayer) {
    return false;
      } else {
         if (this.spottedPlayerTimer.containsKey(var1.getRemoteID())) {
            this.spottedPlayerTimer.put(var1.getRemoteID(), this.spottedPlayerTimer.get(var1.getRemoteID()) + 1);
         } else {
            this.spottedPlayerTimer.put(var1.getRemoteID(), 1);
         }

         if (this.spottedPlayerTimer.get(var1.getRemoteID()) > 100) {
            var1.spottedByPlayer = false;
            var1.doRenderShadow = false;
    return false;
         } else {
    return true;
         }
      }
   }

    bool checkCanSeeClient(UdpConnection var1) {
      return var1.accessLevel > 1 ? true : !this.isInvisible();
   }

    bool checkCanSeeClient(IsoPlayer var1) {
      var1.doRenderShadow = true;
    Vector2 var2 = tempVector2_1.set(this.getX(), this.getY());
    Vector2 var3 = tempVector2_2.set(var1.getX(), var1.getY());
      var3.x = var3.x - var2.x;
      var3.y = var3.y - var2.y;
    Vector2 var4 = this.getForwardDirection();
      var3.normalize();
      var4.normalize();
      var4.normalize();
    float var5 = var3.dot(var4);
      if (!GameClient.bClient || var1 == this || !this.isLocalPlayer()) {
    return true;
      } else if (!this.isAccessLevel("None") && this.canSeeAll) {
         var1.spottedByPlayer = true;
    return true;
      } else {
    float var6 = this.current == nullptr ? 0.0F : var1.getCurrentSquare().DistTo(this.getCurrentSquare());
         if (var6 <= 2.0F) {
            var1.spottedByPlayer = true;
    return true;
         } else if (ServerOptions.getInstance().HidePlayersBehindYou.getValue() && var5 < -0.5) {
            return this.checkSpottedPLayerTimer(var1);
         } else if (var1.isGhostMode() && this.isAccessLevel("None")) {
            var1.doRenderShadow = false;
            var1.spottedByPlayer = false;
    return false;
         } else {
    ILighting var7 = var1.getCurrentSquare().lighting[this.getPlayerNum()];
            if (!var7.bCouldSee()) {
               return this.checkSpottedPLayerTimer(var1);
            } else if (var1.isSneaking() && ServerOptions.getInstance().SneakModeHideFromOtherPlayers.getValue() && !var1.isSprinting()) {
               if (var6 > 30.0F) {
                  var1.spottedByPlayer = false;
               }

               if (var1.spottedByPlayer) {
    return true;
               } else {
                  var1.doRenderShadow = true;
    float var8 = (float)(Math.pow(Math.max(40.0F - var6, 0.0F), 3.0) / 12000.0);
    float var9 = (float)(1.0 - var1.remoteSneakLvl / 10.0F * 0.9 + 0.3);
    float var10 = 1.0F;
                  if (var5 < 0.8) {
                     var10 = 0.3F;
                  }

                  if (var5 < 0.6) {
                     var10 = 0.05F;
                  }

    float var11 = (var7.lightInfo().getR() + var7.lightInfo().getG() + var7.lightInfo().getB()) / 3.0F;
    float var12 = (float)((1.0 - this.getMoodles().getMoodleLevel(MoodleType.Tired) / 5.0F) * 0.7 + 0.3);
    float var13 = 0.1F;
                  if (var1.isPlayerMoving()) {
                     var13 = 0.35F;
                  }

                  if (var1.isRunning()) {
                     var13 = 1.0F;
                  }

    std::vector var14 = PolygonalMap2.instance.getPointInLine(var1.getX(), var1.getY(), this.getX(), this.getY(), (int)this.getZ());
    IsoGridSquare var15 = nullptr;
    float var16 = 0.0F;
    float var17 = 0.0F;
    bool var18 = false;

                  for (int var19 = 0; var19 < var14.size(); var19++) {
    Point var20 = (Point)var14.get(var19);
                     var15 = IsoCell.getInstance().getGridSquare(var20.x, var20.y, this.getZ());
                     if (var15 != nullptr) {
    float var21 = var15.getGridSneakModifier(false);
                        if (var21 > 1.0F) {
                           var18 = true;
                           break;
                        }

                        for (int var22 = 0; var22 < var15.getObjects().size(); var22++) {
    IsoObject var23 = (IsoObject)var15.getObjects().get(var22);
                           if (var23.getSprite().getProperties().Is(IsoFlagType.solidtrans)
                              || var23.getSprite().getProperties().Is(IsoFlagType.solid)
                              || var23.getSprite().getProperties().Is(IsoFlagType.windowW)
                              || var23.getSprite().getProperties().Is(IsoFlagType.windowN)) {
                              var18 = true;
                              break;
                           }
                        }

                        if (var18) {
                           break;
                        }
                     }
                  }

                  if (var18) {
                     var16 = var15.DistTo(var1.getCurrentSquare());
                     var17 = var15.DistTo(this.getCurrentSquare());
                  }

    float var24 = var17 < 2.0F ? 5.0F : Math.min(var16, 5.0F);
                  var24 = Math.max(0.0F, var24 - 1.0F);
                  var24 = (float)(var24 / 5.0 * 0.9 + 0.1);
    float var27 = Math.max(0.1F, 1.0F - ClimateManager.getInstance().getFogIntensity());
    float var28 = var10 * var8 * var11 * var9 * var12 * var13 * var24 * var27;
                  if (var28 >= 1.0F) {
                     var1.spottedByPlayer = true;
    return true;
                  } else {
                     var28 = (float)(1.0 - Math.pow(1.0F - var28, GameTime.getInstance().getMultiplier()));
                     var28 *= 0.5F;
    bool var31 = Rand.Next(0.0F, 1.0F) < var28;
                     var1.spottedByPlayer = var31;
                     if (!var31) {
                        var1.doRenderShadow = false;
                     }

    return var31;
                  }
               }
            } else {
               var1.spottedByPlayer = true;
    return true;
            }
         }
      }
   }

    std::string getTimeSurvived() {
    std::string var1 = "";
    int var2 = (int)this.getHoursSurvived();
    int var4 = var2 / 24;
    int var3 = var2 % 24;
    int var5 = var4 / 30;
      var4 %= 30;
    int var6 = var5 / 12;
      var5 %= 12;
    std::string var7 = Translator.getText("IGUI_Gametime_day");
    std::string var8 = Translator.getText("IGUI_Gametime_year");
    std::string var9 = Translator.getText("IGUI_Gametime_hour");
    std::string var10 = Translator.getText("IGUI_Gametime_month");
      if (var6 != 0) {
         if (var6 > 1) {
            var8 = Translator.getText("IGUI_Gametime_years");
         }

         if (var1.length() > 0) {
            var1 = var1 + ", ";
         }

         var1 = var1 + var6 + " " + var8;
      }

      if (var5 != 0) {
         if (var5 > 1) {
            var10 = Translator.getText("IGUI_Gametime_months");
         }

         if (var1.length() > 0) {
            var1 = var1 + ", ";
         }

         var1 = var1 + var5 + " " + var10;
      }

      if (var4 != 0) {
         if (var4 > 1) {
            var7 = Translator.getText("IGUI_Gametime_days");
         }

         if (var1.length() > 0) {
            var1 = var1 + ", ";
         }

         var1 = var1 + var4 + " " + var7;
      }

      if (var3 != 0) {
         if (var3 > 1) {
            var9 = Translator.getText("IGUI_Gametime_hours");
         }

         if (var1.length() > 0) {
            var1 = var1 + ", ";
         }

         var1 = var1 + var3 + " " + var9;
      }

      if (var1.empty()) {
    int var11 = (int)(this.HoursSurvived * 60.0);
         var1 = var11 + " " + Translator.getText("IGUI_Gametime_minutes");
      }

    return var1;
   }

    bool IsUsingAimWeapon() {
      if (this.leftHandItem == nullptr) {
    return false;
      } else if (!(this.dynamic_cast<HandWeapon*>(leftHandItem) != nullptr)) {
    return false;
      } else {
         return !this.isAiming() ? false : ((HandWeapon)this.leftHandItem).bIsAimedFirearm;
      }
   }

    bool IsUsingAimHandWeapon() {
      if (this.leftHandItem == nullptr) {
    return false;
      } else if (!(this.dynamic_cast<HandWeapon*>(leftHandItem) != nullptr)) {
    return false;
      } else {
         return !this.isAiming() ? false : ((HandWeapon)this.leftHandItem).bIsAimedHandWeapon;
      }
   }

    bool DoAimAnimOnAiming() {
      return this.IsUsingAimWeapon();
   }

    int getSleepingPillsTaken() {
      return this.sleepingPillsTaken;
   }

    void setSleepingPillsTaken(int var1) {
      this.sleepingPillsTaken = var1;
      if (this.getStats().Drunkenness > 10.0F) {
         this.sleepingPillsTaken++;
      }

      this.lastPillsTaken = GameTime.instance.Calender.getTimeInMillis();
   }

    bool isOutside() {
      return this.getCurrentSquare() != nullptr && this.getCurrentSquare().getRoom() == nullptr && !this.isInARoom();
   }

    double getLastSeenZomboidTime() {
      return this.lastSeenZombieTime;
   }

    float getPlayerClothingTemperature() {
    float var1 = 0.0F;
      if (this.getClothingItem_Feet() != nullptr) {
         var1 += ((Clothing)this.getClothingItem_Feet()).getTemperature();
      }

      if (this.getClothingItem_Hands() != nullptr) {
         var1 += ((Clothing)this.getClothingItem_Hands()).getTemperature();
      }

      if (this.getClothingItem_Head() != nullptr) {
         var1 += ((Clothing)this.getClothingItem_Head()).getTemperature();
      }

      if (this.getClothingItem_Legs() != nullptr) {
         var1 += ((Clothing)this.getClothingItem_Legs()).getTemperature();
      }

      if (this.getClothingItem_Torso() != nullptr) {
         var1 += ((Clothing)this.getClothingItem_Torso()).getTemperature();
      }

    return var1;
   }

    float getPlayerClothingInsulation() {
    float var1 = 0.0F;
      if (this.getClothingItem_Feet() != nullptr) {
         var1 += ((Clothing)this.getClothingItem_Feet()).getInsulation() * 0.1F;
      }

      if (this.getClothingItem_Hands() != nullptr) {
         var1 += ((Clothing)this.getClothingItem_Hands()).getInsulation() * 0.0F;
      }

      if (this.getClothingItem_Head() != nullptr) {
         var1 += ((Clothing)this.getClothingItem_Head()).getInsulation() * 0.0F;
      }

      if (this.getClothingItem_Legs() != nullptr) {
         var1 += ((Clothing)this.getClothingItem_Legs()).getInsulation() * 0.3F;
      }

      if (this.getClothingItem_Torso() != nullptr) {
         var1 += ((Clothing)this.getClothingItem_Torso()).getInsulation() * 0.6F;
      }

    return var1;
   }

    InventoryItem getActiveLightItem() {
      if (this.rightHandItem != nullptr && this.rightHandItem.isEmittingLight()) {
         return this.rightHandItem;
      } else if (this.leftHandItem != nullptr && this.leftHandItem.isEmittingLight()) {
         return this.leftHandItem;
      } else {
    AttachedItems var1 = this.getAttachedItems();

         for (int var2 = 0; var2 < var1.size(); var2++) {
    InventoryItem var3 = var1.getItemByIndex(var2);
            if (var3.isEmittingLight()) {
    return var3;
            }
         }

    return nullptr;
      }
   }

    bool isTorchCone() {
      if (this.bRemote) {
         return this.mpTorchCone;
      } else {
    InventoryItem var1 = this.getActiveLightItem();
         return var1 != nullptr && var1.isTorchCone();
      }
   }

    float getTorchDot() {
      if (this.bRemote) {
      }

    InventoryItem var1 = this.getActiveLightItem();
      return var1 != nullptr ? var1.getTorchDot() : 0.0F;
   }

    float getLightDistance() {
      if (this.bRemote) {
         return this.mpTorchDist;
      } else {
    InventoryItem var1 = this.getActiveLightItem();
         return var1 != nullptr ? var1.getLightDistance() : 0.0F;
      }
   }

    bool pressedMovement(bool var1) {
      if (this.isNPC) {
    return false;
      } else if (GameClient.bClient && !this.isLocal()) {
         return this.networkAI.isPressedMovement();
      } else {
    bool var2 = false;
         if (this.PlayerIndex == 0) {
            var2 = GameKeyboard.isKeyDown(Core.getInstance().getKey("Run"));
         }

         if (this.JoypadBind != -1) {
            var2 |= JoypadManager.instance.isRTPressed(this.JoypadBind);
         }

         this.setVariable("pressedRunButton", var2);
         if (var1 || !this.isBlockMovement() && !this.isIgnoreInputsForDirection()) {
            if (this.PlayerIndex != 0
               || !GameKeyboard.isKeyDown(Core.getInstance().getKey("Left"))
                  && !GameKeyboard.isKeyDown(Core.getInstance().getKey("Right"))
                  && !GameKeyboard.isKeyDown(Core.getInstance().getKey("Forward"))
                  && !GameKeyboard.isKeyDown(Core.getInstance().getKey("Backward"))) {
               if (this.JoypadBind != -1) {
    float var3 = JoypadManager.instance.getMovementAxisY(this.JoypadBind);
    float var4 = JoypadManager.instance.getMovementAxisX(this.JoypadBind);
    float var5 = JoypadManager.instance.getDeadZone(this.JoypadBind, 0);
                  if (Math.abs(var3) > var5 || Math.abs(var4) > var5) {
                     if (GameClient.bClient && this.isLocal()) {
                        this.networkAI.setPressedMovement(true);
                     }

    return true;
                  }
               }

               if (GameClient.bClient && this.isLocal()) {
                  this.networkAI.setPressedMovement(false);
               }

    return false;
            } else {
               if (GameClient.bClient && this.isLocal()) {
                  this.networkAI.setPressedMovement(true);
               }

    return true;
            }
         } else {
            if (GameClient.bClient && this.isLocal()) {
               this.networkAI.setPressedMovement(false);
            }

    return false;
         }
      }
   }

    bool pressedCancelAction() {
      if (this.isNPC) {
    return false;
      } else if (GameClient.bClient && !this.isLocal()) {
         return this.networkAI.isPressedCancelAction();
      } else if (this.PlayerIndex == 0 && GameKeyboard.isKeyDown(Core.getInstance().getKey("CancelAction"))) {
         if (GameClient.bClient && this.isLocal()) {
            this.networkAI.setPressedCancelAction(true);
         }

    return true;
      } else if (this.JoypadBind != -1) {
    bool var1 = JoypadManager.instance.isBButtonStartPress(this.JoypadBind);
         if (GameClient.bClient && this.isLocal()) {
            this.networkAI.setPressedCancelAction(var1);
         }

    return var1;
      } else {
         if (GameClient.bClient && this.isLocal()) {
            this.networkAI.setPressedCancelAction(false);
         }

    return false;
      }
   }

    bool checkWalkTo() {
      if (this.isNPC) {
    return false;
      } else if (this.PlayerIndex == 0 && GameKeyboard.isKeyDown(Core.getInstance().getKey("WalkTo"))) {
         LuaEventManager.triggerEvent("OnPressWalkTo", 0, 0, 0);
    return true;
      } else {
    return false;
      }
   }

    bool pressedAim() {
      if (this.isNPC) {
    return false;
      } else {
         if (this.PlayerIndex == 0) {
            if (this.isAimKeyDown()) {
    return true;
            }

            if (Mouse.isButtonDownUICheck(1)) {
    return true;
            }
         }

         if (this.JoypadBind == -1) {
    return false;
         } else {
    float var1 = JoypadManager.instance.getAimingAxisY(this.JoypadBind);
    float var2 = JoypadManager.instance.getAimingAxisX(this.JoypadBind);
            return Math.abs(var1) > 0.1F || Math.abs(var2) > 0.1F;
         }
      }
   }

    bool isDoingActionThatCanBeCancelled() {
      if (this.isDead()) {
    return false;
      } else if (!this.getCharacterActions().empty()) {
    return true;
      } else {
    State var1 = this.getCurrentState();
         if (var1 != nullptr && var1.isDoingActionThatCanBeCancelled()) {
    return true;
         } else {
            for (int var2 = 0; var2 < this.stateMachine.getSubStateCount(); var2++) {
               var1 = this.stateMachine.getSubStateAt(var2);
               if (var1 != nullptr && var1.isDoingActionThatCanBeCancelled()) {
    return true;
               }
            }

    return false;
         }
      }
   }

    long getSteamID() {
      return this.steamID;
   }

    void setSteamID(long var1) {
      this.steamID = var1;
   }

    bool isTargetedByZombie() {
      return this.targetedByZombie;
   }

    bool isMaskClicked(int var1, int var2, bool var3) {
      return this.sprite == nullptr ? false : this.sprite.isMaskClicked(this.dir, var1, var2, var3);
   }

    int getOffSetXUI() {
      return this.offSetXUI;
   }

    void setOffSetXUI(int var1) {
      this.offSetXUI = var1;
   }

    int getOffSetYUI() {
      return this.offSetYUI;
   }

    void setOffSetYUI(int var1) {
      this.offSetYUI = var1;
   }

    std::string getUsername() {
      return this.getUsername(false);
   }

    std::string getUsername(bool var1) {
    std::string var2 = this.username;
      if (var1 && GameClient.bClient && ServerOptions.instance.ShowFirstAndLastName.getValue() && this.isAccessLevel("None")) {
         var2 = this.getDescriptor().getForename() + " " + this.getDescriptor().getSurname();
         if (ServerOptions.instance.DisplayUserName.getValue()) {
            var2 = var2 + " (" + this.username + ")";
         }
      }

    return var2;
   }

    void setUsername(const std::string& var1) {
      this.username = var1;
   }

    void updateUsername() {
      if (!GameClient.bClient && !GameServer.bServer) {
         this.username = this.getDescriptor().getForename() + this.getDescriptor().getSurname();
      }
   }

    short getOnlineID() {
      return this.OnlineID;
   }

    bool isLocalPlayer() {
      if (GameServer.bServer) {
    return false;
      } else {
         for (int var1 = 0; var1 < numPlayers; var1++) {
            if (players[var1] == this) {
    return true;
            }
         }

    return false;
      }
   }

    static void setLocalPlayer(int var0, IsoPlayer var1) {
      players[var0] = var1;
   }

    static IsoPlayer getLocalPlayerByOnlineID(short var0) {
      for (int var1 = 0; var1 < numPlayers; var1++) {
    IsoPlayer var2 = players[var1];
         if (var2 != nullptr && var2.OnlineID == var0) {
    return var2;
         }
      }

    return nullptr;
   }

    bool isOnlyPlayerAsleep() {
      if (!this.isAsleep()) {
    return false;
      } else {
         for (int var1 = 0; var1 < numPlayers; var1++) {
            if (players[var1] != nullptr && !players[var1].isDead() && players[var1] != this && players[var1].isAsleep()) {
    return false;
            }
         }

    return true;
      }
   }

    void OnDeath() {
      super.OnDeath();
      if (!GameServer.bServer) {
         this.StopAllActionQueue();
         if (this.isAsleep()) {
            UIManager.FadeIn(this.getPlayerNum(), 0.5);
            this.setAsleep(false);
         }

         this.dropHandItems();
         if (allPlayersDead()) {
            SoundManager.instance.playMusic(DEATH_MUSIC_NAME);
         }

         if (this.isLocalPlayer()) {
            LuaEventManager.triggerEvent("OnPlayerDeath", this);
         }

         if (this.isLocalPlayer() && this.getVehicle() != nullptr) {
            this.getVehicle().exit(this);
         }

         this.removeSaveFile();
         if (this.shouldBecomeZombieAfterDeath()) {
            this.forceAwake();
         }

         this.getMoodles().Update();
         this.getCell().setDrag(nullptr, this.getPlayerNum());
      }
   }

    bool isNoClip() {
      return this.noClip;
   }

    void setNoClip(bool var1) {
      this.noClip = var1;
   }

    void setAuthorizeMeleeAction(bool var1) {
      this.authorizeMeleeAction = var1;
   }

    bool isAuthorizeMeleeAction() {
      return this.authorizeMeleeAction;
   }

    void setAuthorizeShoveStomp(bool var1) {
      this.authorizeShoveStomp = var1;
   }

    bool isAuthorizeShoveStomp() {
      return this.authorizeShoveStomp;
   }

    bool isBlockMovement() {
      return this.blockMovement;
   }

    void setBlockMovement(bool var1) {
      this.blockMovement = var1;
   }

    void startReceivingBodyDamageUpdates(IsoPlayer var1) {
      if (GameClient.bClient && var1 != nullptr && var1 != this && this.isLocalPlayer() && !var1.isLocalPlayer()) {
         var1.resetBodyDamageRemote();
         BodyDamageSync.instance.startReceivingUpdates(var1.getOnlineID());
      }
   }

    void stopReceivingBodyDamageUpdates(IsoPlayer var1) {
      if (GameClient.bClient && var1 != nullptr && var1 != this && !var1.isLocalPlayer()) {
         BodyDamageSync.instance.stopReceivingUpdates(var1.getOnlineID());
      }
   }

    Nutrition getNutrition() {
      return this.nutrition;
   }

    Fitness getFitness() {
      return this.fitness;
   }

    bool updateRemotePlayer() {
      if (!this.bRemote) {
    return false;
      } else {
         if (GameServer.bServer) {
            ServerLOS.instance.doServerZombieLOS(this);
            ServerLOS.instance.updateLOS(this);
            if (this.isDead()) {
    return true;
            }

            this.removeFromSquare();
            this.setX(this.realx);
            this.setY(this.realy);
            this.setZ(this.realz);
            this.setLx(this.realx);
            this.setLy(this.realy);
            this.setLz(this.realz);
            this.ensureOnTile();
            if (this.slowTimer > 0.0F) {
               this.slowTimer = this.slowTimer - GameTime.instance.getRealworldSecondsSinceLastUpdate();
               this.slowFactor = this.slowFactor - GameTime.instance.getMultiplier() / 100.0F;
               if (this.slowFactor < 0.0F) {
                  this.slowFactor = 0.0F;
               }
            } else {
               this.slowFactor = 0.0F;
            }
         }

         if (GameClient.bClient) {
            if (this.isCurrentState(BumpedState.instance())) {
    return true;
            }

    float var1;
    float var2;
    float var3;
            if (!this.networkAI.isCollisionEnabled() && !this.networkAI.isNoCollisionTimeout()) {
               this.setCollidable(false);
               var1 = this.realx;
               var2 = this.realy;
               var3 = this.realz;
            } else {
               this.setCollidable(true);
               var1 = this.networkAI.targetX;
               var2 = this.networkAI.targetY;
               var3 = this.networkAI.targetZ;
            }

            this.updateMovementRates();
    PathFindBehavior2 var4 = this.getPathFindBehavior2();
    bool var5 = false;
            if (!this.networkAI.events.empty()) {
    Iterator var6 = this.networkAI.events.iterator();

               while (var6.hasNext()) {
    EventPacket var7 = (EventPacket)var6.next();
                  if (var7.process(this)) {
                     this.m_isPlayerMoving = this.networkAI.moving = false;
                     this.setJustMoved(false);
                     if (this.networkAI.usePathFind) {
                        var4.reset();
                        this.setPath2(nullptr);
                        this.networkAI.usePathFind = false;
                     }

                     var6.remove();
    return true;
                  }

                  if (!var7.isMovableEvent()) {
                     tempo.set(var7.x - this.x, var7.y - this.y);
                     var1 = var7.x;
                     var2 = var7.y;
                     var3 = var7.z;
                     var5 = true;
                  }

                  if (var7.isTimeout()) {
                     this.m_isPlayerMoving = this.networkAI.moving = false;
                     this.setJustMoved(false);
                     if (this.networkAI.usePathFind) {
                        var4.reset();
                        this.setPath2(nullptr);
                        this.networkAI.usePathFind = false;
                     }

                     if (Core.bDebug) {
                        DebugLog.log(DebugType.Multiplayer, std::string.format("Event timeout (%d) : %s", this.networkAI.events.size(), var7.getDescription()));
                     }

                     var6.remove();
    return true;
                  }
               }
            }

            if (!var5
               && this.networkAI.collidePointX > -1.0F
               && this.networkAI.collidePointY > -1.0F
               && ((int)this.x != (int)this.networkAI.collidePointX || (int)this.y != (int)this.networkAI.collidePointY)) {
               var1 = this.networkAI.collidePointX;
               var2 = this.networkAI.collidePointY;
               DebugLog.log(
                  DebugType.ActionSystem, "Player " + this.username + ": collide point (" + var1 + ", " + var2 + ") has not been reached, so move to it"
               );
            }

            if (DebugOptions.instance.MultiplayerShowPlayerPrediction.getValue()) {
               this.networkAI.targetX = var1;
               this.networkAI.targetY = var2;
            }

            if (!this.networkAI.forcePathFinder && this.isCollidedThisFrame() && IsoUtils.DistanceManhatten(var1, var2, this.x, this.y) > 3.0F) {
               this.networkAI.forcePathFinder = true;
            }

            if (this.networkAI.forcePathFinder
                  && !PolygonalMap2.instance.lineClearCollide(this.x, this.y, var1, var2, (int)this.z, this.vehicle, false, true)
                  && IsoUtils.DistanceManhatten(var1, var2, this.x, this.y) < 2.0F
               || this.getCurrentState() == ClimbOverFenceState.instance()
               || this.getCurrentState() == ClimbThroughWindowState.instance()
               || this.getCurrentState() == ClimbOverWallState.instance()) {
               this.networkAI.forcePathFinder = false;
            }

            if (!this.networkAI.needToMovingUsingPathFinder && !this.networkAI.forcePathFinder) {
               if (this.networkAI.usePathFind) {
                  var4.reset();
                  this.setPath2(nullptr);
                  this.networkAI.usePathFind = false;
               }

               var4.walkingOnTheSpot.reset(this.x, this.y);
               this.getDeferredMovement(tempVector2_2);
               if (this.getCurrentState() != ClimbOverWallState.instance() && this.getCurrentState() != ClimbOverFenceState.instance()) {
                  float var11 = IsoUtils.DistanceTo(this.x, this.y, this.networkAI.targetX, this.networkAI.targetY)
                     / IsoUtils.DistanceTo(this.realx, this.realy, this.networkAI.targetX, this.networkAI.targetY);
    float var14 = 0.8F + 0.4F * IsoUtils.smoothstep(0.8F, 1.2F, var11);
                  var4.moveToPoint(var1, var2, var14);
               } else {
                  this.MoveUnmodded(tempVector2_2);
               }

               this.m_isPlayerMoving = !var5 && IsoUtils.DistanceManhatten(var1, var2, this.x, this.y) > 0.2F
                  || (int)var1 != (int)this.x
                  || (int)var2 != (int)this.y
                  || (int)this.z != (int)var3;
               if (!this.m_isPlayerMoving) {
                  this.DirectionFromVector(this.networkAI.direction);
                  this.setForwardDirection(this.networkAI.direction);
                  this.networkAI.forcePathFinder = false;
                  if (this.networkAI.usePathFind) {
                     var4.reset();
                     this.setPath2(nullptr);
                     this.networkAI.usePathFind = false;
                  }
               }

               this.setJustMoved(this.m_isPlayerMoving);
               this.m_deltaX = 0.0F;
               this.m_deltaY = 0.0F;
            } else {
               if (!this.networkAI.usePathFind || var1 != var4.getTargetX() || var2 != var4.getTargetY()) {
                  var4.pathToLocationF(var1, var2, var3);
                  var4.walkingOnTheSpot.reset(this.x, this.y);
                  this.networkAI.usePathFind = true;
               }

    BehaviorResult var10 = var4.update();
               if (var10 == BehaviorResult.Failed) {
                  this.setPathFindIndex(-1);
                  if (this.networkAI.forcePathFinder) {
                     this.networkAI.forcePathFinder = false;
                  } else if (NetworkTeleport.teleport(this, zombie.characters.NetworkTeleport.Type.teleportation, var1, var2, (byte)var3, 1.0F)
                     && GameServer.bServer) {
                     DebugLog.Multiplayer
                        .warn(
                           std::string.format(
                              "Player %d teleport from (%.2f, %.2f, %.2f) to (%.2f, %.2f, %.2f)", this.getOnlineID(), this.x, this.y, this.z, var1, var2, var3
                           )
                        );
                  }
               } else if (var10 == BehaviorResult.Succeeded) {
    int var13 = (int)var4.getTargetX();
    int var8 = (int)var4.getTargetY();
                  if (GameServer.bServer) {
                     ServerMap.instance.getChunk(var13 / 10, var8 / 10);
                  } else {
                     IsoWorld.instance.CurrentCell.getChunkForGridSquare(var13, var8, 0);
                  }

                  this.m_isPlayerMoving = true;
                  this.setJustMoved(true);
               }

               this.m_deltaX = 0.0F;
               this.m_deltaY = 0.0F;
            }

            if (!this.m_isPlayerMoving || this.isAiming()) {
               this.DirectionFromVector(this.networkAI.direction);
               this.setForwardDirection(this.networkAI.direction);
               tempo.set(var1 - this.nx, -(var2 - this.ny));
               tempo.normalize();
    float var12 = this.legsSprite.modelSlot.model.AnimPlayer.getRenderedAngle();
               if (var12 > Math.PI * 2) {
                  var12 = (float)(var12 - (Math.PI * 2));
               }

               if (var12 < 0.0F) {
                  var12 = (float)(var12 + (Math.PI * 2));
               }

               tempo.rotate(var12);
               tempo.setLength(Math.min(IsoUtils.DistanceTo(var1, var2, this.x, this.y), 1.0F));
               this.m_deltaX = tempo.x;
               this.m_deltaY = tempo.y;
            }
         }

    return true;
      }
   }

    bool updateWhileDead() {
      if (GameServer.bServer) {
    return false;
      } else if (!this.isLocalPlayer()) {
    return false;
      } else if (!this.isDead()) {
    return false;
      } else {
         this.setVariable("bPathfind", false);
         this.setMoving(false);
         this.m_isPlayerMoving = false;
         if (this.getVehicle() != nullptr) {
            this.getVehicle().exit(this);
         }

         if (this.heartEventInstance != 0L) {
            this.getEmitter().stopSound(this.heartEventInstance);
            this.heartEventInstance = 0L;
         }

    return true;
      }
   }

    void initFMODParameters() {
    FMODParameterList var1 = this.getFMODParameters();
      var1.push_back(this.parameterCharacterMovementSpeed);
      var1.push_back(this.parameterEquippedBaggageContainer);
      var1.push_back(this.parameterFootstepMaterial);
      var1.push_back(this.parameterFootstepMaterial2);
      var1.push_back(this.parameterLocalPlayer);
      var1.push_back(this.parameterMeleeHitSurface);
      var1.push_back(this.parameterPlayerHealth);
      var1.push_back(this.parameterShoeType);
      var1.push_back(this.parameterVehicleHitLocation);
   }

    ParameterCharacterMovementSpeed getParameterCharacterMovementSpeed() {
      return this.parameterCharacterMovementSpeed;
   }

    void setMeleeHitSurface(Material var1) {
      this.parameterMeleeHitSurface.setMaterial(var1);
   }

    void setMeleeHitSurface(const std::string& var1) {
      try {
         this.parameterMeleeHitSurface.setMaterial(Material.valueOf(var1));
      } catch (IllegalArgumentException var3) {
         this.parameterMeleeHitSurface.setMaterial(Material.Default);
      }
   }

    void setVehicleHitLocation(BaseVehicle var1) {
    HitLocation var2 = ParameterVehicleHitLocation.calculateLocation(var1, this.getX(), this.getY(), this.getZ());
      this.parameterVehicleHitLocation.setLocation(var2);
   }

    void updateHeartSound() {
      if (!GameServer.bServer) {
         if (this.isLocalPlayer()) {
    GameSound var1 = GameSounds.getSound("HeartBeat");
    bool var2 = var1 != nullptr && var1.getUserVolume() > 0.0F && this.stats.Panic > 0.0F;
            if (!this.Asleep && var2 && GameTime.getInstance().getTrueMultiplier() == 1.0F) {
               this.heartDelay = this.heartDelay - GameTime.getInstance().getMultiplier() / 1.6F;
               if (this.heartEventInstance == 0L || !this.getEmitter().isPlaying(this.heartEventInstance)) {
                  this.heartEventInstance = this.getEmitter().playSoundImpl("HeartBeat", nullptr);
                  this.getEmitter().setVolume(this.heartEventInstance, 0.0F);
               }

               if (this.heartDelay <= 0.0F) {
                  this.heartDelayMax = (int)((1.0F - this.stats.Panic / 100.0F * 0.7F) * 25.0F) * 2;
                  this.heartDelay = this.heartDelayMax;
                  if (this.heartEventInstance != 0L) {
                     this.getEmitter().setVolume(this.heartEventInstance, this.stats.Panic / 100.0F);
                  }
               }
            } else if (this.heartEventInstance != 0L) {
               this.getEmitter().setVolume(this.heartEventInstance, 0.0F);
            }
         }
      }
   }

    void updateWorldAmbiance() {
      if (!GameServer.bServer) {
         if (this.isLocalPlayer()) {
            if (this.getPlayerNum() == 0 && (this.worldAmbianceInstance == 0L || !this.getEmitter().isPlaying(this.worldAmbianceInstance))) {
               this.worldAmbianceInstance = this.getEmitter().playSoundImpl("WorldAmbiance", nullptr);
               this.getEmitter().setVolume(this.worldAmbianceInstance, 1.0F);
            }
         }
      }
   }

    void updateEquippedBaggageContainer() {
      if (!GameServer.bServer) {
         if (this.isLocalPlayer()) {
    InventoryItem var1 = this.getClothingItem_Back();
            if (var1 != nullptr && var1.IsInventoryContainer()) {
    std::string var6 = var1.getSoundParameter("EquippedBaggageContainer");
               this.parameterEquippedBaggageContainer.setContainerType(var6);
            } else {
               var1 = this.getSecondaryHandItem();
               if (var1 != nullptr && var1.IsInventoryContainer()) {
    std::string var5 = var1.getSoundParameter("EquippedBaggageContainer");
                  this.parameterEquippedBaggageContainer.setContainerType(var5);
               } else {
                  var1 = this.getPrimaryHandItem();
                  if (var1 != nullptr && var1.IsInventoryContainer()) {
    std::string var2 = var1.getSoundParameter("EquippedBaggageContainer");
                     this.parameterEquippedBaggageContainer.setContainerType(var2);
                  } else {
                     this.parameterEquippedBaggageContainer.setContainerType(ContainerType.None);
                  }
               }
            }
         }
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

      this.parameterCharacterMovementSpeed.setMovementType(var2);
      super.DoFootstepSound(var3);
   }

    void updateHeavyBreathing() {
   }

    void checkVehicleContainers() {
    std::vector var1 = this.vehicleContainerData.tempContainers;
      var1.clear();
    int var2 = (int)this.getX() - 4;
    int var3 = (int)this.getY() - 4;
    int var4 = (int)this.getX() + 4;
    int var5 = (int)this.getY() + 4;
    int var6 = var2 / 10;
    int var7 = var3 / 10;
    int var8 = (int)Math.ceil(var4 / 10.0F);
    int var9 = (int)Math.ceil(var5 / 10.0F);

      for (int var10 = var7; var10 < var9; var10++) {
         for (int var11 = var6; var11 < var8; var11++) {
            IsoChunk var12 = GameServer.bServer
               ? ServerMap.instance.getChunk(var11, var10)
               : IsoWorld.instance.CurrentCell.getChunkForGridSquare(var11 * 10, var10 * 10, 0);
            if (var12 != nullptr) {
               for (int var13 = 0; var13 < var12.vehicles.size(); var13++) {
    BaseVehicle var14 = (BaseVehicle)var12.vehicles.get(var13);
    VehicleScript var15 = var14.getScript();
                  if (var15 != nullptr) {
                     for (int var16 = 0; var16 < var15.getPartCount(); var16++) {
    Part var17 = var15.getPart(var16);
                        if (var17.container != nullptr && var17.area != nullptr && var14.isInArea(var17.area, this)) {
                           VehicleContainer var18 = this.vehicleContainerData.freeContainers.empty()
                              ? std::make_unique<VehicleContainer>()
                              : (VehicleContainer)this.vehicleContainerData.freeContainers.pop();
                           var1.push_back(var18.set(var14, var16));
                        }
                     }
                  }
               }
            }
         }
      }

      if (var1.size() != this.vehicleContainerData.containers.size()) {
         this.vehicleContainerData.freeContainers.addAll(this.vehicleContainerData.containers);
         this.vehicleContainerData.containers.clear();
         this.vehicleContainerData.containers.addAll(var1);
         LuaEventManager.triggerEvent("OnContainerUpdate");
      } else {
         for (int var19 = 0; var19 < var1.size(); var19++) {
    VehicleContainer var20 = (VehicleContainer)var1.get(var19);
    VehicleContainer var21 = (VehicleContainer)this.vehicleContainerData.containers.get(var19);
            if (!var20 == var21)) {
               this.vehicleContainerData.freeContainers.addAll(this.vehicleContainerData.containers);
               this.vehicleContainerData.containers.clear();
               this.vehicleContainerData.containers.addAll(var1);
               LuaEventManager.triggerEvent("OnContainerUpdate");
               break;
            }
         }
      }
   }

    void setJoypadIgnoreAimUntilCentered(bool var1) {
      this.bJoypadIgnoreAimUntilCentered = var1;
   }

    bool canSeePlayerStats() {
      return this.accessLevel != "";
   }

    ByteBufferWriter createPlayerStats(ByteBufferWriter var1, const std::string& var2) {
      var1.putShort(this.getOnlineID());
      var1.putUTF(var2);
      var1.putUTF(this.getDisplayName());
      var1.putUTF(this.getDescriptor().getForename());
      var1.putUTF(this.getDescriptor().getSurname());
      var1.putUTF(this.getDescriptor().getProfession());
      if (!StringUtils.isNullOrEmpty(this.getTagPrefix())) {
         var1.putByte((byte)1);
         var1.putUTF(this.getTagPrefix());
      } else {
         var1.putByte((byte)0);
      }

      var1.putBoolean(this.isAllChatMuted());
      var1.putFloat(this.getTagColor().r);
      var1.putFloat(this.getTagColor().g);
      var1.putFloat(this.getTagColor().b);
      var1.putByte((byte)(this.showTag ? 1 : 0));
      var1.putByte((byte)(this.factionPvp ? 1 : 0));
    return var1;
   }

    std::string setPlayerStats(ByteBuffer var1, const std::string& var2) {
    std::string var3 = GameWindow.ReadString(var1);
    std::string var4 = GameWindow.ReadString(var1);
    std::string var5 = GameWindow.ReadString(var1);
    std::string var6 = GameWindow.ReadString(var1);
    std::string var7 = "";
      if (var1.get() == 1) {
         var7 = GameWindow.ReadString(var1);
      }

    bool var8 = var1.get() == 1;
    float var9 = var1.getFloat();
    float var10 = var1.getFloat();
    float var11 = var1.getFloat();
    std::string var12 = "";
      this.setTagColor(std::make_shared<ColorInfo>(var9, var10, var11, 1.0F));
      this.setTagPrefix(var7);
      this.showTag = var1.get() == 1;
      this.factionPvp = var1.get() == 1;
      if (!var4 == this.getDescriptor().getForename())) {
         if (GameServer.bServer) {
            var12 = var2 + " Changed " + var3 + " forname in " + var4;
         } else {
            var12 = "Changed your forname in " + var4;
         }
      }

      this.getDescriptor().setForename(var4);
      if (!var5 == this.getDescriptor().getSurname())) {
         if (GameServer.bServer) {
            var12 = var2 + " Changed " + var3 + " surname in " + var5;
         } else {
            var12 = "Changed your surname in " + var5;
         }
      }

      this.getDescriptor().setSurname(var5);
      if (!var6 == this.getDescriptor().getProfession())) {
         if (GameServer.bServer) {
            var12 = var2 + " Changed " + var3 + " profession to " + var6;
         } else {
            var12 = "Changed your profession in " + var6;
         }
      }

      this.getDescriptor().setProfession(var6);
      if (!this.getDisplayName() == var3)) {
         if (GameServer.bServer) {
            var12 = var2 + " Changed display name \"" + this.getDisplayName() + "\" to \"" + var3 + "\"";
            ServerWorldDatabase.instance.updateDisplayName(this.username, var3);
         } else {
            var12 = "Changed your display name to " + var3;
         }

         this.setDisplayName(var3);
      }

      if (var8 != this.isAllChatMuted()) {
         if (var8) {
            if (GameServer.bServer) {
               var12 = var2 + " Banned " + var3 + " from using /all chat";
            } else {
               var12 = "Banned you from using /all chat";
            }
         } else if (GameServer.bServer) {
            var12 = var2 + " Allowed " + var3 + " to use /all chat";
         } else {
            var12 = "Now allowed you to use /all chat";
         }
      }

      this.setAllChatMuted(var8);
      if (GameServer.bServer && !"" == var12)) {
         LoggerManager.getLogger("admin").write(var12);
      }

      if (GameClient.bClient) {
         LuaEventManager.triggerEvent("OnMiniScoreboardUpdate");
      }

    return var12;
   }

    bool isAllChatMuted() {
      return this.allChatMuted;
   }

    void setAllChatMuted(bool var1) {
      this.allChatMuted = var1;
   }

    std::string getAccessLevel() {
    std::string var1 = this.accessLevel;
      switch (var1) {
         case "admin":
            return "Admin";
         case "moderator":
            return "Moderator";
         case "overseer":
            return "Overseer";
         case "gm":
            return "GM";
         case "observer":
            return "Observer";
         default:
            return "None";
      }
   }

    bool isAccessLevel(const std::string& var1) {
      return this.getAccessLevel().equalsIgnoreCase(var1);
   }

    void setAccessLevel(const std::string& var1) {
    uint8_t var2 = PlayerType.fromString(var1.trim().toLowerCase());
      if (var2 == 1) {
         GameClient.SendCommandToServer("/setaccesslevel \"" + this.username + "\" \"none\"");
      } else {
         GameClient.SendCommandToServer("/setaccesslevel \"" + this.username + "\" \"" + PlayerType.toString(var2) + "\"");
      }
   }

    void addMechanicsItem(const std::string& var1, VehiclePart var2, long var3) {
    uint8_t var4 = 1;
    uint8_t var5 = 1;
      if (this.mechanicsItem.get(int64_t.parseLong(var1)) == nullptr) {
         if (var2.getTable("uninstall") != nullptr && var2.getTable("uninstall").rawget("skills") != nullptr) {
            std::string[] var6 = ((std::string)var2.getTable("uninstall").rawget("skills")).split(";");

    for (auto& var10 : var6)               if (var10.contains("Mechanics")) {
    int var11 = int.parseInt(var10.split(":")[1]);
                  if (var11 >= 6) {
                     var4 = 3;
                     var5 = 7;
                  } else if (var11 >= 4) {
                     var4 = 3;
                     var5 = 5;
                  } else if (var11 >= 2) {
                     var4 = 2;
                     var5 = 4;
                  } else if (Rand.Next(3) == 0) {
                     var4 = 2;
                     var5 = 2;
                  }
               }
            }
         }

         this.getXp().AddXP(Perks.Mechanics, Rand.Next(var4, var5));
      }

      this.mechanicsItem.put(int64_t.parseLong(var1), var3);
   }

    void setPosition(float var1, float var2, float var3) {
      this.setX(var1);
      this.setY(var2);
      this.setZ(var3);
   }

    void updateTemperatureCheck() {
    int var1 = this.Moodles.getMoodleLevel(MoodleType.Hypothermia);
      if (this.hypothermiaCache == -1 || this.hypothermiaCache != var1) {
         if (var1 >= 3 && var1 > this.hypothermiaCache && this.isAsleep() && !this.ForceWakeUp) {
            this.forceAwake();
         }

         this.hypothermiaCache = var1;
      }

    int var2 = this.Moodles.getMoodleLevel(MoodleType.Hyperthermia);
      if (this.hyperthermiaCache == -1 || this.hyperthermiaCache != var2) {
         if (var2 >= 3 && var2 > this.hyperthermiaCache && this.isAsleep() && !this.ForceWakeUp) {
            this.forceAwake();
         }

         this.hyperthermiaCache = var2;
      }
   }

    float getZombieRelevenceScore(IsoZombie var1) {
      if (var1.getCurrentSquare() == nullptr) {
         return -10000.0F;
      } else {
    float var2 = 0.0F;
         if (var1.getCurrentSquare().getCanSee(this.PlayerIndex)) {
            var2 += 100.0F;
         } else if (var1.getCurrentSquare().isCouldSee(this.PlayerIndex)) {
            var2 += 10.0F;
         }

         if (var1.getCurrentSquare().getRoom() != nullptr && this.current.getRoom() == nullptr) {
            var2 -= 20.0F;
         }

         if (var1.getCurrentSquare().getRoom() == nullptr && this.current.getRoom() != nullptr) {
            var2 -= 20.0F;
         }

         if (var1.getCurrentSquare().getRoom() != this.current.getRoom()) {
            var2 -= 20.0F;
         }

    float var3 = var1.DistTo(this);
         var2 -= var3;
         if (var3 < 20.0F) {
            var2 += 300.0F;
         }

         if (var3 < 15.0F) {
            var2 += 300.0F;
         }

         if (var3 < 10.0F) {
            var2 += 1000.0F;
         }

         if (var1.getTargetAlpha() < 1.0F && var2 > 0.0F) {
            var2 *= var1.getTargetAlpha();
         }

    return var2;
      }
   }

    BaseVisual getVisual() {
      return this.humanVisual;
   }

    HumanVisual getHumanVisual() {
      return this.humanVisual;
   }

    ItemVisuals getItemVisuals() {
      return this.itemVisuals;
   }

    void getItemVisuals(ItemVisuals var1) {
      if (!this.bRemote) {
         this.getWornItems().getItemVisuals(var1);
      } else {
         var1.clear();
         var1.addAll(this.itemVisuals);
      }
   }

    void dressInNamedOutfit(const std::string& var1) {
      this.getHumanVisual().dressInNamedOutfit(var1, this.itemVisuals);
      this.onClothingOutfitPreviewChanged();
   }

    void dressInClothingItem(const std::string& var1) {
      this.getHumanVisual().dressInClothingItem(var1, this.itemVisuals);
      this.onClothingOutfitPreviewChanged();
   }

    void onClothingOutfitPreviewChanged() {
      if (this.isLocalPlayer()) {
         this.getInventory().clear();
         this.wornItems.setFromItemVisuals(this.itemVisuals);
         this.wornItems.addItemsToItemContainer(this.getInventory());
         this.itemVisuals.clear();
         this.resetModel();
         this.onWornItemsChanged();
      }
   }

    void onWornItemsChanged() {
      this.parameterShoeType.setShoeType(nullptr);
   }

    void actionStateChanged(ActionContext var1) {
      super.actionStateChanged(var1);
   }

    Vector2 getLastAngle() {
      return this.lastAngle;
   }

    void setLastAngle(Vector2 var1) {
      this.lastAngle.set(var1);
   }

    int getDialogMood() {
      return this.DialogMood;
   }

    void setDialogMood(int var1) {
      this.DialogMood = var1;
   }

    int getPing() {
      return this.ping;
   }

    void setPing(int var1) {
      this.ping = var1;
   }

    IsoMovingObject getDragObject() {
      return this.DragObject;
   }

    void setDragObject(IsoMovingObject var1) {
      this.DragObject = var1;
   }

    float getAsleepTime() {
      return this.AsleepTime;
   }

    void setAsleepTime(float var1) {
      this.AsleepTime = var1;
   }

   public std::stack<IsoMovingObject> getSpottedList() {
      return this.spottedList;
   }

    int getTicksSinceSeenZombie() {
      return this.TicksSinceSeenZombie;
   }

    void setTicksSinceSeenZombie(int var1) {
      this.TicksSinceSeenZombie = var1;
   }

    bool isWaiting() {
      return this.Waiting;
   }

    void setWaiting(bool var1) {
      this.Waiting = var1;
   }

    IsoSurvivor getDragCharacter() {
      return this.DragCharacter;
   }

    void setDragCharacter(IsoSurvivor var1) {
      this.DragCharacter = var1;
   }

    float getHeartDelay() {
      return this.heartDelay;
   }

    void setHeartDelay(float var1) {
      this.heartDelay = var1;
   }

    float getHeartDelayMax() {
      return this.heartDelayMax;
   }

    void setHeartDelayMax(int var1) {
      this.heartDelayMax = var1;
   }

    double getHoursSurvived() {
      return this.HoursSurvived;
   }

    void setHoursSurvived(double var1) {
      this.HoursSurvived = var1;
   }

    float getMaxWeightDelta() {
      return this.maxWeightDelta;
   }

    void setMaxWeightDelta(float var1) {
      this.maxWeightDelta = var1;
   }

    std::string getForname() {
      return this.Forname;
   }

    void setForname(const std::string& var1) {
      this.Forname = var1;
   }

    std::string getSurname() {
      return this.Surname;
   }

    void setSurname(const std::string& var1) {
      this.Surname = var1;
   }

    bool isbChangeCharacterDebounce() {
      return this.bChangeCharacterDebounce;
   }

    void setbChangeCharacterDebounce(bool var1) {
      this.bChangeCharacterDebounce = var1;
   }

    int getFollowID() {
      return this.followID;
   }

    void setFollowID(int var1) {
      this.followID = var1;
   }

    bool isbSeenThisFrame() {
      return this.bSeenThisFrame;
   }

    void setbSeenThisFrame(bool var1) {
      this.bSeenThisFrame = var1;
   }

    bool isbCouldBeSeenThisFrame() {
      return this.bCouldBeSeenThisFrame;
   }

    void setbCouldBeSeenThisFrame(bool var1) {
      this.bCouldBeSeenThisFrame = var1;
   }

    float getTimeSinceLastStab() {
      return this.timeSinceLastStab;
   }

    void setTimeSinceLastStab(float var1) {
      this.timeSinceLastStab = var1;
   }

   public std::stack<IsoMovingObject> getLastSpotted() {
      return this.LastSpotted;
   }

    void setLastSpotted(std::stack<IsoMovingObject> var1) {
      this.LastSpotted = var1;
   }

    int getClearSpottedTimer() {
      return this.ClearSpottedTimer;
   }

    void setClearSpottedTimer(int var1) {
      this.ClearSpottedTimer = var1;
   }

    bool IsRunning() {
      return this.isRunning();
   }

    void InitSpriteParts() {
   }

    bool IsAiming() {
      return this.isAiming();
   }

    std::string getTagPrefix() {
      return this.tagPrefix;
   }

    void setTagPrefix(const std::string& var1) {
      this.tagPrefix = var1;
   }

    ColorInfo getTagColor() {
      return this.tagColor;
   }

    void setTagColor(ColorInfo var1) {
      this.tagColor.set(var1);
   }

    int getTransactionID() {
      return this.transactionID;
   }

    void setTransactionID(int var1) {
      this.transactionID = var1;
   }

    std::string getDisplayName() {
      if (GameClient.bClient) {
         if (this.displayName == nullptr || this.displayName == "")) {
            this.displayName = this.getUsername();
         }
      } else if (!GameServer.bServer) {
         this.displayName = this.getUsername();
      }

      return this.displayName;
   }

    void setDisplayName(const std::string& var1) {
      this.displayName = var1;
   }

    bool isSeeNonPvpZone() {
      return this.seeNonPvpZone || DebugOptions.instance.MultiplayerSeeNonPvpZones.getValue();
   }

    void setSeeNonPvpZone(bool var1) {
      this.seeNonPvpZone = var1;
   }

    bool isShowTag() {
      return this.showTag;
   }

    void setShowTag(bool var1) {
      this.showTag = var1;
   }

    bool isFactionPvp() {
      return this.factionPvp;
   }

    void setFactionPvp(bool var1) {
      this.factionPvp = var1;
   }

    bool isForceAim() {
      return this.forceAim;
   }

    void setForceAim(bool var1) {
      this.forceAim = var1;
   }

    bool toggleForceAim() {
      this.forceAim = !this.forceAim;
      return this.forceAim;
   }

    bool isForceSprint() {
      return this.forceSprint;
   }

    void setForceSprint(bool var1) {
      this.forceSprint = var1;
   }

    bool toggleForceSprint() {
      this.forceSprint = !this.forceSprint;
      return this.forceSprint;
   }

    bool isForceRun() {
      return this.forceRun;
   }

    void setForceRun(bool var1) {
      this.forceRun = var1;
   }

    bool toggleForceRun() {
      this.forceRun = !this.forceRun;
      return this.forceRun;
   }

    bool isDeaf() {
      return this.Traits.Deaf.isSet();
   }

    bool isForceOverrideAnim() {
      return this.forceOverrideAnim;
   }

    void setForceOverrideAnim(bool var1) {
      this.forceOverrideAnim = var1;
   }

    long getMechanicsItem(const std::string& var1) {
      return this.mechanicsItem.get(int64_t.parseLong(var1));
   }

    bool isWearingNightVisionGoggles() {
      return this.isWearingNightVisionGoggles;
   }

    void setWearingNightVisionGoggles(bool var1) {
      this.isWearingNightVisionGoggles = var1;
   }

    void OnAnimEvent(AnimLayer var1, AnimEvent var2) {
      super.OnAnimEvent(var1, var2);
      if (!this.CharacterActions.empty()) {
    BaseAction var3 = (BaseAction)this.CharacterActions.get(0);
         var3.OnAnimEvent(var2);
      }
   }

    void onCullStateChanged(ModelManager var1, bool var2) {
      super.onCullStateChanged(var1, var2);
      if (!var2) {
         DebugFileWatcher.instance.push_back(this.m_setClothingTriggerWatcher);
      } else {
         DebugFileWatcher.instance.remove(this.m_setClothingTriggerWatcher);
      }
   }

    bool isTimedActionInstant() {
      return (GameClient.bClient || GameServer.bServer) && this.isAccessLevel("None") ? false : super.isTimedActionInstant();
   }

    bool isSkeleton() {
    return false;
   }

    void addWorldSoundUnlessInvisible(int var1, int var2, bool var3) {
      if (!this.isGhostMode()) {
         super.addWorldSoundUnlessInvisible(var1, var2, var3);
      }
   }

    void updateFootInjuries() {
    InventoryItem var1 = this.getWornItems().getItem("Shoes");
      if (var1 == nullptr || var1.getCondition() <= 0) {
         if (this.getCurrentSquare() != nullptr) {
            if (this.getCurrentSquare().getBrokenGlass() != nullptr) {
    BodyPartType var2 = BodyPartType.FromIndex(Rand.Next(BodyPartType.ToIndex(BodyPartType.Foot_L), BodyPartType.ToIndex(BodyPartType.Foot_R) + 1));
    BodyPart var3 = this.getBodyDamage().getBodyPart(var2);
               var3.generateDeepShardWound();
            }

    uint8_t var7 = 0;
    bool var8 = false;
            if (this.getCurrentSquare().getZone() != nullptr
               && (this.getCurrentSquare().getZone().getType() == "Forest") || this.getCurrentSquare().getZone().getType() == "DeepForest"))) {
               var8 = true;
            }

    IsoObject var4 = this.getCurrentSquare().getFloor();
            if (var4 != nullptr && var4.getSprite() != nullptr && var4.getSprite().getName() != nullptr) {
    std::string var5 = var4.getSprite().getName();
               if (var5.contains("blends_natural_01") && var8) {
                  var7 = 2;
               } else if (!var5.contains("blends_natural_01") && this.getCurrentSquare().getBuilding() == nullptr) {
                  var7 = 1;
               }
            }

            if (var7 != 0) {
               if (this.isWalking && !this.isRunning() && !this.isSprinting()) {
                  this.footInjuryTimer += var7;
               } else if (this.isRunning() && !this.isSprinting()) {
                  this.footInjuryTimer += var7 + 2;
               } else {
                  if (!this.isSprinting()) {
                     if (this.footInjuryTimer > 0 && Rand.Next(3) == 0) {
                        this.footInjuryTimer--;
                     }

                     return;
                  }

                  this.footInjuryTimer += var7 + 5;
               }

               if (Rand.Next(Rand.AdjustForFramerate(8500 - this.footInjuryTimer)) <= 0) {
                  this.footInjuryTimer = 0;
                  BodyPartType var9 = BodyPartType.FromIndex(
                     Rand.Next(BodyPartType.ToIndex(BodyPartType.Foot_L), BodyPartType.ToIndex(BodyPartType.Foot_R) + 1)
                  );
    BodyPart var6 = this.getBodyDamage().getBodyPart(var9);
                  if (var6.getScratchTime() > 30.0F) {
                     if (!var6.isCut()) {
                        var6.setCut(true);
                        var6.setCutTime(Rand.Next(1.0F, 3.0F));
                     } else {
                        var6.setCutTime(var6.getCutTime() + Rand.Next(1.0F, 3.0F));
                     }
                  } else {
                     if (!var6.scratched()) {
                        var6.setScratched(true, true);
                        var6.setScratchTime(Rand.Next(1.0F, 3.0F));
                     } else {
                        var6.setScratchTime(var6.getScratchTime() + Rand.Next(1.0F, 3.0F));
                     }

                     if (var6.getScratchTime() > 20.0F && var6.getBleedingTime() == 0.0F) {
                        var6.setBleedingTime(Rand.Next(3.0F, 10.0F));
                     }
                  }
               }
            }
         }
      }
   }

    int getMoodleLevel(MoodleType var1) {
      return this.getMoodles().getMoodleLevel(var1);
   }

    bool isAttackStarted() {
      return this.attackStarted;
   }

    bool isBehaviourMoving() {
      return this.hasPath() || super.isBehaviourMoving();
   }

    bool isJustMoved() {
      return this.JustMoved;
   }

    void setJustMoved(bool var1) {
      this.JustMoved = var1;
   }

    bool isPlayerMoving() {
      return this.m_isPlayerMoving;
   }

    float getTimedActionTimeModifier() {
      return this.getBodyDamage().getThermoregulator() != nullptr ? this.getBodyDamage().getThermoregulator().getTimedActionTimeModifier() : 1.0F;
   }

    bool isLookingWhileInVehicle() {
      return this.getVehicle() != nullptr && this.bLookingWhileInVehicle;
   }

    void setInitiateAttack(bool var1) {
      this.initiateAttack = var1;
   }

    bool isIgnoreInputsForDirection() {
      return this.ignoreInputsForDirection;
   }

    void setIgnoreInputsForDirection(bool var1) {
      this.ignoreInputsForDirection = var1;
   }

    bool isIgnoreContextKey() {
      return this.ignoreContextKey;
   }

    void setIgnoreContextKey(bool var1) {
      this.ignoreContextKey = var1;
   }

    bool isIgnoreAutoVault() {
      return this.ignoreAutoVault;
   }

    void setIgnoreAutoVault(bool var1) {
      this.ignoreAutoVault = var1;
   }

    bool isAllowSprint() {
      return this.allowSprint;
   }

    void setAllowSprint(bool var1) {
      this.allowSprint = var1;
   }

    bool isAllowRun() {
      return this.allowRun;
   }

    void setAllowRun(bool var1) {
      this.allowRun = var1;
   }

    std::string getAttackType() {
      return this.attackType;
   }

    void setAttackType(const std::string& var1) {
      this.attackType = var1;
   }

    void clearNetworkEvents() {
      this.networkAI.events.clear();
      this.clearVariable("PerformingAction");
      this.clearVariable("IsPerformingAnAction");
      this.overridePrimaryHandModel = nullptr;
      this.overrideSecondaryHandModel = nullptr;
      this.resetModelNextFrame();
   }

    bool isCanSeeAll() {
      return this.canSeeAll;
   }

    void setCanSeeAll(bool var1) {
      this.canSeeAll = var1;
   }

    bool isNetworkTeleportEnabled() {
      return NetworkTeleport.enable;
   }

    void setNetworkTeleportEnabled(bool var1) {
      NetworkTeleport.enable = var1;
   }

    bool isCheatPlayerSeeEveryone() {
      return DebugOptions.instance.CheatPlayerSeeEveryone.getValue();
   }

    float getRelevantAndDistance(float var1, float var2, float var3) {
      return Math.abs(this.x - var1) <= var3 * 10.0F && Math.abs(this.y - var2) <= var3 * 10.0F
         ? IsoUtils.DistanceTo(this.x, this.y, var1, var2)
         : float.POSITIVE_INFINITY;
   }

    bool isCanHearAll() {
      return this.canHearAll;
   }

    void setCanHearAll(bool var1) {
      this.canHearAll = var1;
   }

   public std::vector<std::string> getAlreadyReadBook() {
      return this.alreadyReadBook;
   }

    void setMoodleCantSprint(bool var1) {
      this.MoodleCantSprint = var1;
   }

    void setAttackFromBehind(bool var1) {
      this.attackFromBehind = var1;
   }

    bool isAttackFromBehind() {
      return this.attackFromBehind;
   }

    float getDamageFromHitByACar(float var1) {
    float var2 = 1.0F;
      switch (SandboxOptions.instance.DamageToPlayerFromHitByACar.getValue()) {
         case 1:
            var2 = 0.0F;
            break;
         case 2:
            var2 = 0.5F;
         case 3:
         default:
            break;
         case 4:
            var2 = 2.0F;
            break;
         case 5:
            var2 = 5.0F;
      }

    float var3 = var1 * var2;
      if (DebugOptions.instance.MultiplayerCriticalHit.getValue()) {
         var3 += 10.0F;
      }

      if (var3 > 0.0F) {
    int var4 = (int)(2.0F + var3 * 0.07F);

         for (int var5 = 0; var5 < var4; var5++) {
    int var6 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Hand_L), BodyPartType.ToIndex(BodyPartType.MAX));
    BodyPart var7 = this.getBodyDamage().getBodyPart(BodyPartType.FromIndex(var6));
    float var8 = Math.max(Rand.Next(var3 - 15.0F, var3), 5.0F);
            if (this.Traits.FastHealer.isSet()) {
               var8 = (float)(var8 * 0.8);
            } else if (this.Traits.SlowHealer.isSet()) {
               var8 = (float)(var8 * 1.2);
            }

            switch (SandboxOptions.instance.InjurySeverity.getValue()) {
               case 1:
                  var8 *= 0.5F;
                  break;
               case 3:
                  var8 *= 1.5F;
            }

            var8 = (float)(var8 * 0.9);
            var7.AddDamage(var8);
            if (var8 > 40.0F && Rand.Next(12) == 0) {
               var7.generateDeepWound();
            }

            if (var8 > 10.0F && Rand.Next(100) <= 10 && SandboxOptions.instance.BoneFracture.getValue()) {
               var7.setFractureTime(Rand.Next(Rand.Next(10.0F, var8 + 10.0F), Rand.Next(var8 + 20.0F, var8 + 30.0F)));
            }

            if (var8 > 30.0F && Rand.Next(100) <= 80 && SandboxOptions.instance.BoneFracture.getValue() && var6 == BodyPartType.ToIndex(BodyPartType.Head)) {
               var7.setFractureTime(Rand.Next(Rand.Next(10.0F, var8 + 10.0F), Rand.Next(var8 + 20.0F, var8 + 30.0F)));
            }

            if (var8 > 10.0F && Rand.Next(100) <= 60 && SandboxOptions.instance.BoneFracture.getValue() && var6 > BodyPartType.ToIndex(BodyPartType.Groin)) {
               var7.setFractureTime(Rand.Next(Rand.Next(10.0F, var8 + 20.0F), Rand.Next(var8 + 30.0F, var8 + 40.0F)));
            }
         }

         this.getBodyDamage().Update();
      }

      this.addBlood(var1);
      if (GameClient.bClient && this.isLocal()) {
         this.updateMovementRates();
         GameClient.sendPlayerInjuries(this);
         GameClient.sendPlayerDamage(this);
      }

    return var3;
   }

    float Hit(BaseVehicle var1, float var2, bool var3, float var4, float var5) {
    float var6 = this.doBeatenVehicle(var2);
      super.Hit(var1, var2, var3, var4, var5);
    return var6;
   }

    void Kill(IsoGameCharacter var1) {
      if (!this.isOnKillDone()) {
         super.Kill(var1);
         this.getBodyDamage().setOverallBodyHealth(0.0F);
         if (DebugOptions.instance.MultiplayerPlayerZombie.getValue()) {
            this.getBodyDamage().setInfectionLevel(100.0F);
         }

         if (var1 == nullptr) {
            this.DoDeath(nullptr, nullptr);
         } else {
            this.DoDeath(var1.getUseHandWeapon(), var1);
         }

         if (GameClient.bClient) {
            ClientPlayerDB.getInstance().clientSendNetworkPlayerInt(this);
         }
      }
   }

    bool shouldDoInventory() {
      return this.isLocalPlayer();
   }

    void becomeCorpse() {
      if (!this.isOnDeathDone()) {
         if (this.shouldBecomeCorpse() || this.isLocalPlayer()) {
            super.becomeCorpse();
            if (GameClient.bClient && this.shouldDoInventory()) {
               GameClient.sendPlayerDeath(this);
            }

            if (!GameClient.bClient) {
    IsoDeadBody var1 = std::make_shared<IsoDeadBody>(this);
               if (this.shouldBecomeZombieAfterDeath()) {
                  var1.reanimateLater();
               }

               if (GameServer.bServer) {
                  GameServer.sendBecomeCorpse(var1);
               }
            }
         }
      }
   }

    void preupdate() {
      if (GameClient.bClient) {
         this.networkAI.updateHitVehicle();
         if (!this.isLocal() && this.isKnockedDown() && !this.isOnFloor()) {
    HitReactionNetworkAI var1 = this.getHitReactionNetworkAI();
            if (var1.isSetup() && !var1.isStarted()) {
               var1.start();
            }
         }
      }

      super.preupdate();
   }

    HitReactionNetworkAI getHitReactionNetworkAI() {
      return this.networkAI.hitReaction;
   }

    NetworkCharacterAI getNetworkCharacterAI() {
      return this.networkAI;
   }

    void setFitnessSpeed() {
      this.clearVariable("FitnessStruggle");
    float var1 = this.getPerkLevel(Perks.Fitness) / 5.0F / 1.1F - this.getMoodleLevel(MoodleType.Endurance) / 20.0F;
      if (var1 > 1.5F) {
         var1 = 1.5F;
      }

      if (var1 < 0.85F) {
         var1 = 1.0F;
         this.setVariable("FitnessStruggle", true);
      }

      this.setVariable("FitnessSpeed", var1);
   }

    bool isLocal() {
      return super.isLocal() || this.isLocalPlayer();
   }

    bool isClimbOverWallSuccess() {
      return this.climbOverWallSuccess;
   }

    void setClimbOverWallSuccess(bool var1) {
      this.climbOverWallSuccess = var1;
   }

    bool isClimbOverWallStruggle() {
      return this.climbOverWallStruggle;
   }

    void setClimbOverWallStruggle(bool var1) {
      this.climbOverWallStruggle = var1;
   }

    bool isVehicleCollisionActive(BaseVehicle var1) {
      if (!super.isVehicleCollisionActive(var1)) {
    return false;
      } else if (this.isGodMod()) {
    return false;
      } else {
    IsoPlayer var2 = (IsoPlayer)GameClient.IDToPlayerMap.get(this.vehicle4testCollision.getNetPlayerId());
         if (!SwipeStatePlayer.checkPVP(var2, this)) {
    return false;
         } else if (SandboxOptions.instance.DamageToPlayerFromHitByACar.getValue() < 1) {
    return false;
         } else {
            return this.getVehicle() == var1
               ? false
               : !this.isCurrentState(PlayerFallDownState.instance())
                  && !this.isCurrentState(PlayerFallingState.instance())
                  && !this.isCurrentState(PlayerKnockedDown.instance());
         }
      }
   }

    bool isShowMPInfos() {
      return this.showMPInfos;
   }

    void setShowMPInfos(bool var1) {
      this.showMPInfos = var1;
   }
}
} // namespace characters
} // namespace zombie
