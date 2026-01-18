#pragma once
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
#include "zombie/audio/parameters/ParameterEquippedBaggageContainer.h"
#include "zombie/audio/parameters/ParameterFootstepMaterial.h"
#include "zombie/audio/parameters/ParameterFootstepMaterial2.h"
#include "zombie/audio/parameters/ParameterLocalPlayer.h"
#include "zombie/audio/parameters/ParameterMeleeHitSurface.h"
#include "zombie/audio/parameters/ParameterPlayerHealth.h"
#include "zombie/audio/parameters/ParameterRoomType.h"
#include "zombie/audio/parameters/ParameterShoeType.h"
#include "zombie/audio/parameters/ParameterVehicleHitLocation.h"
#include "zombie/characters/AttachedItems/AttachedItems.h"
#include "zombie/characters/BodyDamage/BodyDamage.h"
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/BodyDamage/Fitness.h"
#include "zombie/characters/BodyDamage/Nutrition.h"
#include "zombie/characters/CharacterTimedActions/BaseAction.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/characters/Moodles/Moodles.h"
#include "zombie/characters/action/ActionContext.h"
#include "zombie/characters/action/ActionGroup.h"
#include "zombie/characters/skills/PerkFactory.h"
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
#include "zombie/core/profiling/PerformanceProfileProbe.h"
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
#include "zombie/iso/IsoMetaGrid.h"
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
#include "zombie/ui/TutorialManager.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/PathFindBehavior2.h"
#include "zombie/vehicles/PolygonalMap2.h"
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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


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
 public static IsoPlayer[] players = new IsoPlayer[4];
 static IsoPlayer instance;
 static const void* instanceLock = "IsoPlayer.instance Lock";
 static const Vector2 testHitPosition = new Vector2();
 static int FollowDeadCount = 240;
 private static Stack<String> StaticTraits = std::make_unique<Stack<>>();
 bool ignoreAutoVault = false;
 int remoteSneakLvl = 0;
 int remoteStrLvl = 0;
 int remoteFitLvl = 0;
 bool canSeeAll = false;
 bool canHearAll = false;
 bool MoodleCantSprint = false;
 static const Vector2 tempo = new Vector2();
 static const Vector2 tempVector2 = new Vector2();
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
 private HashMap<Integer, Integer> spottedPlayerTimer = std::make_unique<HashMap<>>();
 float extUpdateCount = 0.0F;
 static const int s_randomIdleFidgetInterval = 5000;
 bool attackStarted = false;
 private static PredicatedFileWatcher m_isoPlayerTriggerWatcher = new PredicatedFileWatcher(
 ZomboidFileSystem.instance.getMessagingDirSub("Trigger_ResetIsoPlayerModel.xml"), IsoPlayer::onTrigger_ResetIsoPlayerModel
 );
 const PredicatedFileWatcher m_setClothingTriggerWatcher;
 static Vector2 tempVector2_1 = new Vector2();
 static Vector2 tempVector2_2 = new Vector2();
 const HumanVisual humanVisual = new HumanVisual(this);
 const ItemVisuals itemVisuals = new ItemVisuals();
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
 const Vector2 playerMoveDir = new Vector2(0.0F, 0.0F);
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
 const Vector2 lastAngle = new Vector2();
 std::string SaveFileName;
 bool bBannedAttacking = false;
 int sqlID = -1;
 int ClearSpottedTimer = -1;
 float timeSinceLastStab = 0.0F;
 protected Stack<IsoMovingObject> LastSpotted = std::make_unique<Stack<>>();
 bool bChangeCharacterDebounce = false;
 int followID = 0;
 protected Stack<IsoGameCharacter> FollowCamStack = std::make_unique<Stack<>>();
 bool bSeenThisFrame = false;
 bool bCouldBeSeenThisFrame = false;
 float AsleepTime = 0.0F;
 protected Stack<IsoMovingObject> spottedList = std::make_unique<Stack<>>();
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
 static const Vector3f tempVector3f = new Vector3f();
 private IsoPlayer.InputState inputState = new IsoPlayer.InputState();
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
 const ColorInfo tagColor = new ColorInfo(1.0F, 1.0F, 1.0F, 1.0F);
 std::string displayName = nullptr;
 bool seeNonPvpZone = false;
 private HashMap<Long, Long> mechanicsItem = std::make_unique<HashMap<>>();
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
 private IsoPlayer.VehicleContainerData vehicleContainerData = new IsoPlayer.VehicleContainerData();
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
 private ArrayList<String> alreadyReadBook = std::make_unique<ArrayList<>>();
 uint8_t bleedingLevel = 0;
 const NetworkPlayerAI networkAI;
 ReplayManager replay = nullptr;
 private static ArrayList<IsoPlayer> RecentlyRemoved = std::make_unique<ArrayList<>>();
 bool pathfindRun = false;
 private static IsoPlayer.MoveVars s_moveVars = new IsoPlayer.MoveVars();
 int atkTimer = 0;
 private static ArrayList<HitInfo> s_targetsProne = std::make_unique<ArrayList<>>();
 private static ArrayList<HitInfo> s_targetsStanding = std::make_unique<ArrayList<>>();
 bool bReloadButtonDown = false;
 bool bRackButtonDown = false;
 bool bReloadKeyDown = false;
 bool bRackKeyDown = false;
 long AttackAnimThrowTimer = System.currentTimeMillis();
 std::string WeaponT = nullptr;
 const ParameterCharacterMovementSpeed parameterCharacterMovementSpeed = new ParameterCharacterMovementSpeed(this);
 const ParameterEquippedBaggageContainer parameterEquippedBaggageContainer = new ParameterEquippedBaggageContainer(this);
 const ParameterFootstepMaterial parameterFootstepMaterial = new ParameterFootstepMaterial(this);
 const ParameterFootstepMaterial2 parameterFootstepMaterial2 = new ParameterFootstepMaterial2(this);
 const ParameterLocalPlayer parameterLocalPlayer = new ParameterLocalPlayer(this);
 const ParameterMeleeHitSurface parameterMeleeHitSurface = new ParameterMeleeHitSurface(this);
 const ParameterPlayerHealth parameterPlayerHealth = new ParameterPlayerHealth(this);
 const ParameterVehicleHitLocation parameterVehicleHitLocation = new ParameterVehicleHitLocation();
 const ParameterShoeType parameterShoeType = new ParameterShoeType(this);

 public IsoPlayer(IsoCell cell) {
 this(cell, nullptr, 0, 0, 0);
 }

 public IsoPlayer(IsoCell cell, SurvivorDesc desc, int x, int y, int z) {
 super(cell, x, y, z);
 this->registerVariableCallbacks();
 this->Traits.addAll(StaticTraits);
 StaticTraits.clear();
 this->dir = IsoDirections.W;
 this->nutrition = new Nutrition(this);
 this->fitness = new Fitness(this);
 this->initWornItems("Human");
 this->initAttachedItems("Human");
 this->clothingWetness = new ClothingWetness(this);
 if (desc != nullptr) {
 this->descriptor = desc;
 } else {
 this->descriptor = std::make_unique<SurvivorDesc>();
 }

 this->setFemale(this->descriptor.isFemale());
 this->Dressup(this->descriptor);
 this->getHumanVisual().copyFrom(this->descriptor.humanVisual);
 this->InitSpriteParts(this->descriptor);
 LuaEventManager.triggerEvent("OnCreateLivingCharacter", this, this->descriptor);
 if (!GameClient.bClient && !GameServer.bServer) {
 }

 this->descriptor.Instance = this;
 this->SpeakColour = new Color(Rand.Next(135) + 120, Rand.Next(135) + 120, Rand.Next(135) + 120, 255);
 if (GameClient.bClient) {
 if (Core.getInstance().getMpTextColor() != nullptr) {
 this->SpeakColour = new Color(
 Core.getInstance().getMpTextColor().r, Core.getInstance().getMpTextColor().g, Core.getInstance().getMpTextColor().b, 1.0F
 );
 } else {
 Core.getInstance().setMpTextColor(new ColorInfo(this->SpeakColour.r, this->SpeakColour.g, this->SpeakColour.b, 1.0F);

 try {
 Core.getInstance().saveOptions();
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }
 }
 }

 if (Core.GameMode == "LastStand")) {
 this->Traits.add("Strong");
 }

 if (this->Traits.Strong.isSet()) {
 this->maxWeightDelta = 1.5F;
 }

 if (this->Traits.Weak.isSet()) {
 this->maxWeightDelta = 0.75F;
 }

 if (this->Traits.Feeble.isSet()) {
 this->maxWeightDelta = 0.9F;
 }

 if (this->Traits.Stout.isSet()) {
 this->maxWeightDelta = 1.25F;
 }

 this->descriptor.temper = 5.0F;
 if (this->Traits.ShortTemper.isSet()) {
 this->descriptor.temper = 7.5F;
 } else if (this->Traits.Patient.isSet()) {
 this->descriptor.temper = 2.5F;
 }

 if (this->Traits.Injured.isSet()) {
 this->getBodyDamage().AddRandomDamage();
 }

 this->bMultiplayer = GameServer.bServer || GameClient.bClient;
 this->vehicle4testCollision = nullptr;
 if (Core.bDebug && DebugOptions.instance.CheatPlayerStartInvisible.getValue()) {
 this->setGhostMode(true);
 this->setGodMod(true);
 }

 this->actionContext.setGroup(ActionGroup.getActionGroup("player"));
 this->initializeStates();
 DebugFileWatcher.instance.add(m_isoPlayerTriggerWatcher);
 this->m_setClothingTriggerWatcher = new PredicatedFileWatcher(
 ZomboidFileSystem.instance.getMessagingDirSub("Trigger_SetClothing.xml"), TriggerXmlFile.class, this::onTrigger_setClothingToXmlTriggerFile
 );
 this->networkAI = new NetworkPlayerAI(this);
 this->initFMODParameters();
 }

 void setOnlineID(short value) {
 this->OnlineID = value;
 }

 void registerVariableCallbacks() {
 this->setVariable("CombatSpeed", () -> this->combatSpeed, float0 -> this->combatSpeed = float0);
 this->setVariable("TurnDelta", () -> this->m_turnDelta, float0 -> this->m_turnDelta = float0);
 this->setVariable("sneaking", this::isSneaking, this::setSneaking);
 this->setVariable("initiateAttack", () -> this->initiateAttack, this::setInitiateAttack);
 this->setVariable("isMoving", this::isPlayerMoving);
 this->setVariable("isRunning", this::isRunning, this::setRunning);
 this->setVariable("isSprinting", this::isSprinting, this::setSprinting);
 this->setVariable("run", this::isRunning, this::setRunning);
 this->setVariable("sprint", this::isSprinting, this::setSprinting);
 this->setVariable("isStrafing", this::isStrafing);
 this->setVariable("WalkSpeed", () -> this->m_walkSpeed, float0 -> this->m_walkSpeed = float0);
 this->setVariable("WalkInjury", () -> this->m_walkInjury, float0 -> this->m_walkInjury = float0);
 this->setVariable("RunSpeed", () -> this->m_runSpeed, float0 -> this->m_runSpeed = float0);
 this->setVariable("IdleSpeed", () -> this->m_idleSpeed, float0 -> this->m_idleSpeed = float0);
 this->setVariable("DeltaX", () -> this->m_deltaX, float0 -> this->m_deltaX = float0);
 this->setVariable("DeltaY", () -> this->m_deltaY, float0 -> this->m_deltaY = float0);
 this->setVariable("Windspeed", () -> this->m_windspeed, float0 -> this->m_windspeed = float0);
 this->setVariable("WindForce", () -> this->m_windForce, float0 -> this->m_windForce = float0);
 this->setVariable("IPX", () -> this->m_IPX, float0 -> this->m_IPX = float0);
 this->setVariable("IPY", () -> this->m_IPY, float0 -> this->m_IPY = float0);
 this->setVariable("attacktype", () -> this->attackType);
 this->setVariable("aim", this::isAiming);
 this->setVariable("bdoshove", () -> this->bDoShove);
 this->setVariable("bfalling", () -> this->z > 0.0F && this->fallTime > 2.0F);
 this->setVariable("baimatfloor", this::isAimAtFloor);
 this->setVariable("attackfrombehind", () -> this->attackFromBehind);
 this->setVariable("bundervehicle", this::isUnderVehicle);
 this->setVariable("reanimatetimer", this::getReanimateTimer);
 this->setVariable("isattacking", this::isAttacking);
 this->setVariable("beensprintingfor", this::getBeenSprintingFor);
 this->setVariable("bannedAttacking", () -> this->bBannedAttacking);
 this->setVariable("meleePressed", () -> this->m_meleePressed);
 this->setVariable("AttackAnim", this::isAttackAnim, this::setAttackAnim);
 this->setVariable("Weapon", this::getWeaponType, this::setWeaponType);
 this->setVariable("BumpFall", false);
 this->setVariable("bClient", () -> GameClient.bClient);
 this->setVariable("IsPerformingAnAction", this::isPerformingAnAction, this::setPerformingAnAction);
 }

 Vector2 getDeferredMovement(Vector2 out_result) {
 super.getDeferredMovement(out_result);
 if (DebugOptions.instance.CheatPlayerInvisibleSprint.getValue()
 && this->isGhostMode()
 && (this->IsRunning() || this->isSprinting())
 && !this->isCurrentState(ClimbOverFenceState.instance())
 && !this->isCurrentState(ClimbThroughWindowState.instance())) {
 if (this->getPath2() == nullptr && !this->pressedMovement(false) {
 return out_result.set(0.0F, 0.0F);
 }

 if (this->getCurrentBuilding() != nullptr) {
 out_result.scale(2.5F);
 return out_result;
 }

 out_result.scale(7.5F);
 }

 return out_result;
 }

 float getTurnDelta() {
 return !DebugOptions.instance.CheatPlayerInvisibleSprint.getValue() || !this->isGhostMode() || !this->isRunning() && !this->isSprinting()
 ? super.getTurnDelta()
 : 10.0F;
 }

 void setPerformingAnAction(bool val) {
 this->m_isPerformingAnAction = val;
 }

 bool isPerformingAnAction() {
 return this->m_isPerformingAnAction;
 }

 bool isAttacking() {
 return !StringUtils.isNullOrWhitespace(this->getAttackType());
 }

 bool shouldBeTurning() {
 if (this->isPerformingAnAction()) {
 }

 return super.shouldBeTurning();
 }

 /**
 * The IsoPlayer.instance thread-safe invoke. Calls the supplied callback if the IsoPlayer.instance is non-nullptr. Performs this in a thread-safe manner. It is intended that, should any thread intend to use the IsoPlayer.instance, and does not want another thread to change the ptr in the meanwhile, it should call invokeOnPlayerInstance(Runnable callback) eg. IsoPlayer.invokeOnPlayerInstance(()-> { IsoPlayer.instance.doStuff(); }
 */
 static void invokeOnPlayerInstance(Runnable callback) {
 synchronized (instanceLock) {
 if (instance != nullptr) {
 callback.run();
 }
 }
 }

 static IsoPlayer getInstance() {
 return instance;
 }

 static void setInstance(IsoPlayer newInstance) {
 synchronized (instanceLock) {
 instance = newInstance;
 }
 }

 static bool hasInstance() {
 return instance != nullptr;
 }

 static void onTrigger_ResetIsoPlayerModel(const std::string& string) {
 if (instance != nullptr) {
 DebugLog.log(DebugType.General, "DebugFileWatcher Hit. Resetting player model: " + string);
 instance.resetModel();
 } else {
 DebugLog.log(DebugType.General, "DebugFileWatcher Hit. Player instance nullptr : " + string);
 }
 }

 public static Stack<String> getStaticTraits() {
 return StaticTraits;
 }

 static int getFollowDeadCount() {
 return FollowDeadCount;
 }

 static void setFollowDeadCount(int aFollowDeadCount) {
 FollowDeadCount = aFollowDeadCount;
 }

 public static ArrayList<String> getAllFileNames() {
 std::vector arrayList = new ArrayList();
 std::string string = ZomboidFileSystem.instance.getCurrentSaveDir();

 for (int int0 = 1; int0 < 100; int0++) {
 File file = new File(string + File.separator + "map_p" + int0 + ".bin");
 if (file.exists()) {
 arrayList.add("map_p" + int0 + ".bin");
 }
 }

 return arrayList;
 }

 static std::string getUniqueFileName() {
 int int0 = 0;
 std::string string = ZomboidFileSystem.instance.getCurrentSaveDir();

 for (int int1 = 1; int1 < 100; int1++) {
 File file = new File(string + File.separator + "map_p" + int1 + ".bin");
 if (file.exists()) {
 int0 = int1;
 }
 }

 return ZomboidFileSystem.instance.getFileNameInCurrentSave("map_p" + ++int0 + ".bin");
 }

 public static ArrayList<IsoPlayer> getAllSavedPlayers() {
 std::vector arrayList;
 if (GameClient.bClient) {
 arrayList = ClientPlayerDB.getInstance().getAllNetworkPlayers();
 } else {
 arrayList = PlayerDB.getInstance().getAllLocalPlayers();
 }

 for (int int0 = arrayList.size() - 1; int0 >= 0; int0--) {
 if (((IsoPlayer)arrayList.get(int0).isDead()) {
 arrayList.remove(int0);
 }
 }

 return arrayList;
 }

 static bool isServerPlayerIDValid(const std::string& id) {
 if (GameClient.bClient) {
 std::string string = ServerOptions.instance.ServerPlayerID.getValue();
 return string != nullptr && !string.empty() ? string == id) : true;
 } else {
 return true;
 }
 }

 static int getPlayerIndex() {
 return instance = = nullptr ? assumedPlayer : instance.PlayerIndex;
 }

 static bool allPlayersDead() {
 for (int int0 = 0; int0 < numPlayers; int0++) {
 if (players[int0] != nullptr && !players[int0].isDead()) {
 return false;
 }
 }

 return IsoWorld.instance.empty() || IsoWorld.instance.AddCoopPlayers.empty();
 }

 public static ArrayList<IsoPlayer> getPlayers() {
 return new ArrayList<>(Arrays.asList(players);
 }

 static bool allPlayersAsleep() {
 int int0 = 0;
 int int1 = 0;

 for (int int2 = 0; int2 < numPlayers; int2++) {
 if (players[int2] != nullptr && !players[int2].isDead()) {
 int0++;
 if (players[int2] != nullptr && players[int2].isAsleep()) {
 int1++;
 }
 }
 }

 return int0 > 0 && int0 == int1;
 }

 static bool getCoopPVP() {
 return CoopPVP;
 }

 static void setCoopPVP(bool enabled) {
 CoopPVP = enabled;
 }

 void TestZombieSpotPlayer(IsoMovingObject chr) {
 if (GameServer.bServer && chr instanceof IsoZombie && ((IsoZombie)chr).target != this && ((IsoZombie)chr).isLeadAggro(this) {
 GameServer.updateZombieControl((IsoZombie)chr, (short)1, this->OnlineID);
 } else {
 chr.spotted(this, false);
 if (chr instanceof IsoZombie) {
 float float0 = chr.DistTo(this);
 if (float0 < this->closestZombie && !chr.isOnFloor()) {
 this->closestZombie = float0;
 }
 }
 }
 }

 float getPathSpeed() {
 float float0 = this->getMoveSpeed() * 0.9F;
 switch (this->Moodles.getMoodleLevel(MoodleType.Endurance) {
 case 1:
 float0 *= 0.95F;
 break;
 case 2:
 float0 *= 0.9F;
 break;
 case 3:
 float0 *= 0.8F;
 break;
 case 4:
 float0 *= 0.6F;
 }

 if (this->stats.enduranceRecharging) {
 float0 *= 0.85F;
 }

 if (this->getMoodles().getMoodleLevel(MoodleType.HeavyLoad) > 0) {
 float float1 = this->getInventory().getCapacityWeight();
 float float2 = this->getMaxWeight();
 float float3 = Math.min(2.0F, float1 / float2) - 1.0F;
 float0 *= 0.65F + 0.35F * (1.0F - float3);
 }

 return float0;
 }

 bool isGhostMode() {
 return this->isInvisible();
 }

 void setGhostMode(bool aGhostMode) {
 this->setInvisible(aGhostMode);
 }

 bool isSeeEveryone() {
 return Core.bDebug && DebugOptions.instance.CheatPlayerSeeEveryone.getValue();
 }

 bool zombiesSwitchOwnershipEachUpdate() {
 return SystemDisabler.zombiesSwitchOwnershipEachUpdate;
 }

 Vector2 getPlayerMoveDir() {
 return this->playerMoveDir;
 }

 void setPlayerMoveDir(Vector2 aPlayerMoveDir) {
 this->playerMoveDir.set(aPlayerMoveDir);
 }

 void MoveUnmodded(Vector2 dir) {
 if (this->getSlowFactor() > 0.0F) {
 dir.x = dir.x * (1.0F - this->getSlowFactor());
 dir.y = dir.y * (1.0F - this->getSlowFactor());
 }

 super.MoveUnmodded(dir);
 }

 void nullifyAiming() {
 if (this->isForceAim()) {
 this->toggleForceAim();
 }

 this->isCharging = false;
 this->setIsAiming(false);
 }

 bool isAimKeyDown() {
 if (this->PlayerIndex != 0) {
 return false;
 } else {
 int int0 = Core.getInstance().getKey("Aim");
 bool boolean0 = GameKeyboard.isKeyDown(int0);
 if (!boolean0) {
 return false;
 } else {
 bool boolean1 = int0 == 29 || int0 == 157;
 return !boolean1 || !UIManager.isMouseOverInventory();
 }
 }
 }

 void initializeStates() {
 std::unordered_map hashMap = this->getStateUpdateLookup();
 hashMap.clear();
 if (this->getVehicle() == nullptr) {
 hashMap.put("actions", PlayerActionsState.instance());
 hashMap.put("aim", PlayerAimState.instance());
 hashMap.put("climbfence", ClimbOverFenceState.instance());
 hashMap.put("climbdownrope", ClimbDownSheetRopeState.instance());
 hashMap.put("climbrope", ClimbSheetRopeState.instance());
 hashMap.put("climbwall", ClimbOverWallState.instance());
 hashMap.put("climbwindow", ClimbThroughWindowState.instance());
 hashMap.put("emote", PlayerEmoteState.instance());
 hashMap.put("ext", PlayerExtState.instance());
 hashMap.put("sitext", PlayerExtState.instance());
 hashMap.put("falldown", PlayerFallDownState.instance());
 hashMap.put("falling", PlayerFallingState.instance());
 hashMap.put("getup", PlayerGetUpState.instance());
 hashMap.put("idle", IdleState.instance());
 hashMap.put("melee", SwipeStatePlayer.instance());
 hashMap.put("shove", SwipeStatePlayer.instance());
 hashMap.put("ranged", SwipeStatePlayer.instance());
 hashMap.put("onground", PlayerOnGroundState.instance());
 hashMap.put("knockeddown", PlayerKnockedDown.instance());
 hashMap.put("openwindow", OpenWindowState.instance());
 hashMap.put("closewindow", CloseWindowState.instance());
 hashMap.put("smashwindow", SmashWindowState.instance());
 hashMap.put("fishing", FishingState.instance());
 hashMap.put("fitness", FitnessState.instance());
 hashMap.put("hitreaction", PlayerHitReactionState.instance());
 hashMap.put("hitreactionpvp", PlayerHitReactionPVPState.instance());
 hashMap.put("hitreaction-hit", PlayerHitReactionPVPState.instance());
 hashMap.put("collide", CollideWithWallState.instance());
 hashMap.put("bumped", BumpedState.instance());
 hashMap.put("bumped-bump", BumpedState.instance());
 hashMap.put("sitonground", PlayerSitOnGroundState.instance());
 hashMap.put("strafe", PlayerStrafeState.instance());
 } else {
 hashMap.put("aim", PlayerAimState.instance());
 hashMap.put("idle", IdleState.instance());
 hashMap.put("melee", SwipeStatePlayer.instance());
 hashMap.put("shove", SwipeStatePlayer.instance());
 hashMap.put("ranged", SwipeStatePlayer.instance());
 }
 }

 ActionContext getActionContext() {
 return this->actionContext;
 }

 void onAnimPlayerCreated(AnimationPlayer animationPlayer) {
 super.onAnimPlayerCreated(animationPlayer);
 animationPlayer.addBoneReparent("Bip01_L_Thigh", "Bip01");
 animationPlayer.addBoneReparent("Bip01_R_Thigh", "Bip01");
 animationPlayer.addBoneReparent("Bip01_L_Clavicle", "Bip01_Spine1");
 animationPlayer.addBoneReparent("Bip01_R_Clavicle", "Bip01_Spine1");
 animationPlayer.addBoneReparent("Bip01_Prop1", "Bip01_R_Hand");
 animationPlayer.addBoneReparent("Bip01_Prop2", "Bip01_L_Hand");
 }

 std::string GetAnimSetName() {
 return this->getVehicle() == nullptr ? "player" : "player-vehicle";
 }

 bool IsInMeleeAttack() {
 return this->isCurrentState(SwipeStatePlayer.instance());
 }

 void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 uint8_t byte0 = input.get();
 uint8_t byte1 = input.get();
 super.load(input, WorldVersion, IS_DEBUG_SAVE);
 this->setHoursSurvived(input.getDouble());
 SurvivorDesc survivorDesc = this->descriptor;
 this->setFemale(survivorDesc.isFemale());
 this->InitSpriteParts(survivorDesc);
 this->SpeakColour = new Color(Rand.Next(135) + 120, Rand.Next(135) + 120, Rand.Next(135) + 120, 255);
 if (GameClient.bClient) {
 if (Core.getInstance().getMpTextColor() != nullptr) {
 this->SpeakColour = new Color(
 Core.getInstance().getMpTextColor().r, Core.getInstance().getMpTextColor().g, Core.getInstance().getMpTextColor().b, 1.0F
 );
 } else {
 Core.getInstance().setMpTextColor(new ColorInfo(this->SpeakColour.r, this->SpeakColour.g, this->SpeakColour.b, 1.0F);

 try {
 Core.getInstance().saveOptions();
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }
 }
 }

 this->setZombieKills(input.getInt());
 std::vector arrayList = this->savedInventoryItems;
 uint8_t byte2 = input.get();

 for (int int0 = 0; int0 < byte2; int0++) {
 std::string string0 = GameWindow.ReadString(input);
 short short0 = input.getShort();
 if (short0 >= 0 && short0 < arrayList.size() && this->wornItems.getBodyLocationGroup().getLocation(string0) != nullptr) {
 this->wornItems.setItem(string0, (InventoryItem)arrayList.get(short0);
 }
 }

 short short1 = input.getShort();
 if (short1 >= 0 && short1 < arrayList.size()) {
 this->leftHandItem = (InventoryItem)arrayList.get(short1);
 }

 short1 = input.getShort();
 if (short1 >= 0 && short1 < arrayList.size()) {
 this->rightHandItem = (InventoryItem)arrayList.get(short1);
 }

 this->setVariable("Weapon", WeaponType.getWeaponType(this).type);
 this->setSurvivorKills(input.getInt());
 this->initSpritePartsEmpty();
 this->nutrition.load(input);
 this->setAllChatMuted(input.get() == 1);
 this->tagPrefix = GameWindow.ReadString(input);
 this->setTagColor(new ColorInfo(input.getFloat(), input.getFloat(), input.getFloat(), 1.0F);
 this->setDisplayName(GameWindow.ReadString(input);
 this->showTag = input.get() == 1;
 this->factionPvp = input.get() == 1;
 if (WorldVersion >= 176) {
 this->noClip = input.get() == 1;
 }

 if (input.get() == 1) {
 this->savedVehicleX = input.getFloat();
 this->savedVehicleY = input.getFloat();
 this->savedVehicleSeat = input.get();
 this->savedVehicleRunning = input.get() == 1;
 this->z = 0.0F;
 }

 int int1 = input.getInt();

 for (int int2 = 0; int2 < int1; int2++) {
 this->mechanicsItem.put(input.getLong(), input.getLong());
 }

 this->fitness.load(input, WorldVersion);
 if (WorldVersion >= 184) {
 short short2 = input.getShort();

 for (int int3 = 0; int3 < short2; int3++) {
 short short3 = input.getShort();
 std::string string1 = WorldDictionary.getItemTypeFromID(short3);
 if (string1 != nullptr) {
 this->alreadyReadBook.add(string1);
 }
 }
 } else if (WorldVersion >= 182) {
 int int4 = input.getInt();

 for (int int5 = 0; int5 < int4; int5++) {
 this->alreadyReadBook.add(GameWindow.ReadString(input);
 }
 }

 if (WorldVersion >= 189) {
 this->loadKnownMediaLines(input, WorldVersion);
 }
 }

 void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 IsoPlayer player = instance;
 instance = this;

 try {
 super.save(output, IS_DEBUG_SAVE);
 } finally {
 instance = player;
 }

 output.putDouble(this->getHoursSurvived());
 output.putInt(this->getZombieKills());
 if (this->wornItems.size() > 127) {
 throw RuntimeException("too many worn items");
 } else {
 output.put((byte)this->wornItems.size());
 this->wornItems.forEach(wornItem -> {
 GameWindow.WriteString(output, wornItem.getLocation());
 output.putShort((short)this->savedInventoryItems.indexOf(wornItem.getItem()));
 });
 output.putShort((short)this->savedInventoryItems.indexOf(this->getPrimaryHandItem()));
 output.putShort((short)this->savedInventoryItems.indexOf(this->getSecondaryHandItem()));
 output.putInt(this->getSurvivorKills());
 this->nutrition.save(output);
 output.put((byte)(this->isAllChatMuted() ? 1 : 0);
 GameWindow.WriteString(output, this->tagPrefix);
 output.putFloat(this->getTagColor().r);
 output.putFloat(this->getTagColor().g);
 output.putFloat(this->getTagColor().b);
 GameWindow.WriteString(output, this->displayName);
 output.put((byte)(this->showTag ? 1 : 0);
 output.put((byte)(this->factionPvp ? 1 : 0);
 output.put((byte)(this->isNoClip() ? 1 : 0);
 if (this->vehicle != nullptr) {
 output.put((byte)1);
 output.putFloat(this->vehicle.x);
 output.putFloat(this->vehicle.y);
 output.put((byte)this->vehicle.getSeat(this);
 output.put((byte)(this->vehicle.isEngineRunning() ? 1 : 0);
 } else {
 output.put((byte)0);
 }

 output.putInt(this->mechanicsItem.size());

 for (Long long0 : this->mechanicsItem.keySet()) {
 output.putLong(long0);
 output.putLong(this->mechanicsItem.get(long0);
 }

 this->fitness.save(output);
 output.putShort((short)this->alreadyReadBook.size());

 for (int int0 = 0; int0 < this->alreadyReadBook.size(); int0++) {
 output.putShort(WorldDictionary.getItemRegistryID(this->alreadyReadBook.get(int0);
 }

 this->saveKnownMediaLines(output);
 }
 }

 void save() {
 synchronized (SliceY.SliceBufferLock) {
 ByteBuffer byteBuffer = SliceY.SliceBuffer;
 byteBuffer.clear();
 byteBuffer.put((byte)80);
 byteBuffer.put((byte)76);
 byteBuffer.put((byte)89);
 byteBuffer.put((byte)82);
 byteBuffer.putInt(195);
 GameWindow.WriteString(byteBuffer, this->bMultiplayer ? ServerOptions.instance.ServerPlayerID.getValue() : "");
 byteBuffer.putInt((int)(this->x / 10.0F);
 byteBuffer.putInt((int)(this->y / 10.0F);
 byteBuffer.putInt((int)this->x);
 byteBuffer.putInt((int)this->y);
 byteBuffer.putInt((int)this->z);
 this->save(byteBuffer);
 File file = new File(ZomboidFileSystem.instance.getFileNameInCurrentSave("map_p.bin"));
 if (!Core.getInstance().isNoSave()) {
 try (
 FileOutputStream fileOutputStream = new FileOutputStream(file);
 BufferedOutputStream bufferedOutputStream = new BufferedOutputStream(fileOutputStream);
 ) {
 bufferedOutputStream.write(byteBuffer.array(), 0, byteBuffer.position());
 }
 }

 if (this->getVehicle() != nullptr && !GameClient.bClient) {
 VehiclesDB2.instance.updateVehicleAndTrailer(this->getVehicle());
 }
 }
 }

 void save(const std::string& fileName) {
 this->SaveFileName = fileName;
 synchronized (SliceY.SliceBufferLock) {
 SliceY.SliceBuffer.clear();
 SliceY.SliceBuffer.putInt(195);
 GameWindow.WriteString(SliceY.SliceBuffer, this->bMultiplayer ? ServerOptions.instance.ServerPlayerID.getValue() : "");
 this->save(SliceY.SliceBuffer);
 File file = new File(fileName).getAbsoluteFile();

 try (
 FileOutputStream fileOutputStream = new FileOutputStream(file);
 BufferedOutputStream bufferedOutputStream = new BufferedOutputStream(fileOutputStream);
 ) {
 bufferedOutputStream.write(SliceY.SliceBuffer.array(), 0, SliceY.SliceBuffer.position());
 }
 }
 }

 void load(const std::string& fileName) {
 File file = new File(fileName).getAbsoluteFile();
 if (file.exists()) {
 this->SaveFileName = fileName;

 try (
 FileInputStream fileInputStream = new FileInputStream(file);
 BufferedInputStream bufferedInputStream = new BufferedInputStream(fileInputStream);
 ) {
 synchronized (SliceY.SliceBufferLock) {
 SliceY.SliceBuffer.clear();
 int int0 = bufferedInputStream.read(SliceY.SliceBuffer.array());
 SliceY.SliceBuffer.limit(int0);
 int int1 = SliceY.SliceBuffer.getInt();
 if (int1 >= 69) {
 this->SaveFileIP = GameWindow.ReadStringUTF(SliceY.SliceBuffer);
 if (int1 < 71) {
 this->SaveFileIP = ServerOptions.instance.ServerPlayerID.getValue();
 }
 } else if (GameClient.bClient) {
 this->SaveFileIP = ServerOptions.instance.ServerPlayerID.getValue();
 }

 this->load(SliceY.SliceBuffer, int1);
 }
 }
 }
 }

 void removeFromWorld() {
 this->getEmitter().stopOrTriggerSoundByName("BurningFlesh");
 this->removedFromWorldMS = System.currentTimeMillis();
 if (!RecentlyRemoved.contains(this) {
 RecentlyRemoved.add(this);
 }

 super.removeFromWorld();
 }

 static void UpdateRemovedEmitters() {
 IsoCell cell = IsoWorld.instance.CurrentCell;
 long long0 = System.currentTimeMillis();

 for (int int0 = RecentlyRemoved.size() - 1; int0 >= 0; int0--) {
 IsoPlayer player = RecentlyRemoved.get(int0);
 if ((cell.getObjectList().contains(player) || cell.getAddList().contains(player) && !cell.getRemoveList().contains(player) {
 RecentlyRemoved.remove(int0);
 } else {
 player.getFMODParameters().update();
 player.getEmitter().tick();
 if (long0 - player.removedFromWorldMS > 5000L) {
 player.getEmitter().stopAll();
 RecentlyRemoved.remove(int0);
 }
 }
 }
 }

 static void Reset() {
 RecentlyRemoved.clear();
 }

 void setVehicle4TestCollision(BaseVehicle vehicle) {
 this->vehicle4testCollision = vehicle;
 }

 bool isSaveFileInUse() {
 for (int int0 = 0; int0 < numPlayers; int0++) {
 IsoPlayer player0 = players[int0];
 if (player0 != nullptr) {
 if (this->sqlID != -1 && this->sqlID == player0.sqlID) {
 return true;
 }

 if (this->SaveFileName != nullptr && this->SaveFileName == player0.SaveFileName) {
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

 if (this->isNPC() && this->SaveFileName != nullptr) {
 File file = new File(this->SaveFileName).getAbsoluteFile();
 if (file.exists()) {
 file.delete();
 }
 }
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }
 }

 bool isSaveFileIPValid() {
 return isServerPlayerIDValid();
 }

 std::string getObjectName() {
 return "Player";
 }

 int getJoypadBind() {
 return this->JoypadBind;
 }

 bool isLBPressed() {
 return this->JoypadBind == -1 ? false : JoypadManager.instance.isLBPressed(this->JoypadBind);
 }

 Vector2 getControllerAimDir(Vector2 vec) {
 if (GameWindow.ActivatedJoyPad != nullptr && this->JoypadBind != -1 && this->bJoypadMovementActive) {
 float float0 = JoypadManager.instance.getAimingAxisX(this->JoypadBind);
 float float1 = JoypadManager.instance.getAimingAxisY(this->JoypadBind);
 if (this->bJoypadIgnoreAimUntilCentered) {
 if (vec.set(float0, float1).getLengthSquared() > 0.0F) {
 return vec.set(0.0F, 0.0F);
 }

 this->bJoypadIgnoreAimUntilCentered = false;
 }

 if (vec.set(float0, float1).getLength() < 0.3F) {
 float1 = 0.0F;
 float0 = 0.0F;
 }

 if (float0 == 0.0F && float1 == 0.0F) {
 return vec.set(0.0F, 0.0F);
 }

 vec.set(float0, float1);
 vec.normalize();
 vec.rotate((float) (-Math.PI / 4);
 }

 return vec;
 }

 Vector2 getMouseAimVector(Vector2 vec) {
 int int0 = Mouse.getX();
 int int1 = Mouse.getY();
 vec.x = IsoUtils.XToIso(int0, int1 + 55.0F * this->def.getScaleY(), this->getZ()) - this->getX();
 vec.y = IsoUtils.YToIso(int0, int1 + 55.0F * this->def.getScaleY(), this->getZ()) - this->getY();
 vec.normalize();
 return vec;
 }

 Vector2 getAimVector(Vector2 vec) {
 return this->JoypadBind == -1 ? this->getMouseAimVector(vec) : this->getControllerAimDir(vec);
 }

 float getGlobalMovementMod(bool bDoNoises) {
 return !this->isGhostMode() && !this->isNoClip() ? super.getGlobalMovementMod(bDoNoises) : 1.0F;
 }

 bool isInTrees2(bool ignoreBush) {
 return !this->isGhostMode() && !this->isNoClip() ? super.isInTrees2(ignoreBush) : false;
 }

 float getMoveSpeed() {
 float float0 = 1.0F;

 for (int int0 = BodyPartType.ToIndex(BodyPartType.UpperLeg_L); int0 <= BodyPartType.ToIndex(BodyPartType.Foot_R); int0++) {
 BodyPart bodyPart = this->getBodyDamage().getBodyPart(BodyPartType.FromIndex(int0);
 float float1 = 1.0F;
 if (bodyPart.getFractureTime() > 20.0F) {
 float1 = 0.4F;
 if (bodyPart.getFractureTime() > 50.0F) {
 float1 = 0.3F;
 }

 if (bodyPart.getSplintFactor() > 0.0F) {
 float1 += bodyPart.getSplintFactor() / 10.0F;
 }
 }

 if (bodyPart.getFractureTime() < 20.0F && bodyPart.getSplintFactor() > 0.0F) {
 float1 = 0.8F;
 }

 if (float1 > 0.7F && bodyPart.getDeepWoundTime() > 0.0F) {
 float1 = 0.7F;
 if (bodyPart.bandaged()) {
 float1 += 0.2F;
 }
 }

 if (float1 < float0) {
 float0 = float1;
 }
 }

 if (float0 != 1.0F) {
 return this->MoveSpeed * float0;
 } else if (this->getMoodles().getMoodleLevel(MoodleType.Panic) >= 4 && this->Traits.AdrenalineJunkie.isSet()) {
 float float2 = 1.0F;
 int int1 = this->getMoodles().getMoodleLevel(MoodleType.Panic) + 1;
 float2 += int1 / 50.0F;
 return this->MoveSpeed * float2;
 } else {
 return this->MoveSpeed;
 }
 }

 void setMoveSpeed(float moveSpeed) {
 this->MoveSpeed = moveSpeed;
 }

 float getTorchStrength() {
 if (this->bRemote) {
 return this->mpTorchStrength;
 } else {
 InventoryItem item = this->getActiveLightItem();
 return item != nullptr ? item.getLightStrength() : 0.0F;
 }
 }

 float getInvAimingMod() {
 int int0 = this->getPerkLevel(PerkFactory.Perks.Aiming);
 if (int0 == 1) {
 return 0.9F;
 } else if (int0 == 2) {
 return 0.86F;
 } else if (int0 == 3) {
 return 0.82F;
 } else if (int0 == 4) {
 return 0.74F;
 } else if (int0 == 5) {
 return 0.7F;
 } else if (int0 == 6) {
 return 0.66F;
 } else if (int0 == 7) {
 return 0.62F;
 } else if (int0 == 8) {
 return 0.58F;
 } else if (int0 == 9) {
 return 0.54F;
 } else {
 return int0 = = 10 ? 0.5F : 0.9F;
 }
 }

 float getAimingMod() {
 int int0 = this->getPerkLevel(PerkFactory.Perks.Aiming);
 if (int0 == 1) {
 return 1.1F;
 } else if (int0 == 2) {
 return 1.14F;
 } else if (int0 == 3) {
 return 1.18F;
 } else if (int0 == 4) {
 return 1.22F;
 } else if (int0 == 5) {
 return 1.26F;
 } else if (int0 == 6) {
 return 1.3F;
 } else if (int0 == 7) {
 return 1.34F;
 } else if (int0 == 8) {
 return 1.36F;
 } else if (int0 == 9) {
 return 1.4F;
 } else {
 return int0 = = 10 ? 1.5F : 1.0F;
 }
 }

 float getReloadingMod() {
 int int0 = this->getPerkLevel(PerkFactory.Perks.Reloading);
 return 3.5F - int0 * 0.25F;
 }

 float getAimingRangeMod() {
 int int0 = this->getPerkLevel(PerkFactory.Perks.Aiming);
 if (int0 == 1) {
 return 1.2F;
 } else if (int0 == 2) {
 return 1.28F;
 } else if (int0 == 3) {
 return 1.36F;
 } else if (int0 == 4) {
 return 1.42F;
 } else if (int0 == 5) {
 return 1.5F;
 } else if (int0 == 6) {
 return 1.58F;
 } else if (int0 == 7) {
 return 1.66F;
 } else if (int0 == 8) {
 return 1.72F;
 } else if (int0 == 9) {
 return 1.8F;
 } else {
 return int0 = = 10 ? 2.0F : 1.1F;
 }
 }

 bool isPathfindRunning() {
 return this->pathfindRun;
 }

 void setPathfindRunning(bool newvalue) {
 this->pathfindRun = newvalue;
 }

 bool isBannedAttacking() {
 return this->bBannedAttacking;
 }

 void setBannedAttacking(bool b) {
 this->bBannedAttacking = b;
 }

 float getInvAimingRangeMod() {
 int int0 = this->getPerkLevel(PerkFactory.Perks.Aiming);
 if (int0 == 1) {
 return 0.8F;
 } else if (int0 == 2) {
 return 0.7F;
 } else if (int0 == 3) {
 return 0.62F;
 } else if (int0 == 4) {
 return 0.56F;
 } else if (int0 == 5) {
 return 0.45F;
 } else if (int0 == 6) {
 return 0.38F;
 } else if (int0 == 7) {
 return 0.31F;
 } else if (int0 == 8) {
 return 0.24F;
 } else if (int0 == 9) {
 return 0.17F;
 } else {
 return int0 = = 10 ? 0.1F : 0.8F;
 }
 }

 void updateCursorVisibility() {
 if (this->isAiming()) {
 if (this->PlayerIndex == 0 && this->JoypadBind == -1 && !this->isDead()) {
 if (!Core.getInstance().getOptionShowCursorWhileAiming()) {
 if (Core.getInstance().getIsoCursorVisibility() != 0) {
 if (!UIManager.isForceCursorVisible()) {
 int int0 = Mouse.getXA();
 int int1 = Mouse.getYA();
 if (int0 >= IsoCamera.getScreenLeft(0) && int0 <= IsoCamera.getScreenLeft(0) + IsoCamera.getScreenWidth(0) {
 if (int1 >= IsoCamera.getScreenTop(0) && int1 <= IsoCamera.getScreenTop(0) + IsoCamera.getScreenHeight(0) {
 Mouse.setCursorVisible(false);
 }
 }
 }
 }
 }
 }
 }
 }

 void render(float x, float y, float z, ColorInfo col, bool bDoChild, bool bWallLightingPass, Shader shader) {
 if (DebugOptions.instance.Character.Debug.Render.DisplayRoomAndZombiesZone.getValue()) {
 std::string string = "";
 if (this->getCurrentRoomDef() != nullptr) {
 string = this->getCurrentRoomDef().name;
 }

 IsoMetaGrid.Zone zone = ZombiesZoneDefinition.getDefinitionZoneAt((int)x, (int)y, (int)z);
 if (zone != nullptr) {
 string = string + " - " + zone.name + " / " + zone.type;
 }

 this->Say(string);
 }

 if (!getInstance().checkCanSeeClient(this) {
 this->setTargetAlpha(0.0F);
 getInstance().spottedPlayerTimer.remove(this->getRemoteID());
 } else {
 this->setTargetAlpha(1.0F);
 }

 super.render(x, y, z, col, bDoChild, bWallLightingPass, shader);
 }

 void renderlast() {
 super.renderlast();
 if (DebugOptions.instance.Character.Debug.Render.FMODRoomType.getValue() && this->isLocalPlayer()) {
 ParameterRoomType.render(this);
 }
 }

 float doBeatenVehicle(float vehicleSpeed) {
 if (GameClient.bClient && this->isLocalPlayer()) {
 this->changeState(ForecastBeatenPlayerState.instance());
 return 0.0F;
 } else if (!GameClient.bClient && !this->isLocalPlayer()) {
 return 0.0F;
 } else {
 float float0 = this->getDamageFromHitByACar(vehicleSpeed);
 LuaEventManager.triggerEvent("OnPlayerGetDamage", this, "CARHITDAMAGE", float0);
 if (this->isAlive()) {
 if (GameClient.bClient) {
 if (this->isCurrentState(PlayerSitOnGroundState.instance())) {
 this->setKnockedDown(true);
 this->setReanimateTimer(20.0F);
 } else if (!this->isOnFloor()
 && !(vehicleSpeed > 15.0F)
 && !this->isCurrentState(PlayerHitReactionState.instance())
 && !this->isCurrentState(PlayerGetUpState.instance())
 && !this->isCurrentState(PlayerOnGroundState.instance())) {
 this->setHitReaction("HitReaction");
 this->actionContext.reportEvent("washit");
 this->setVariable("hitpvp", false);
 } else {
 this->setHitReaction("HitReaction");
 this->actionContext.reportEvent("washit");
 this->setVariable("hitpvp", false);
 this->setKnockedDown(true);
 this->setReanimateTimer(20.0F);
 }
 } else if (this->getCurrentState() != PlayerHitReactionState.instance()
 && this->getCurrentState() != PlayerFallDownState.instance()
 && this->getCurrentState() != PlayerOnGroundState.instance()
 && !this->isKnockedDown()) {
 if (float0 > 15.0F) {
 this->setKnockedDown(true);
 this->setReanimateTimer(20 + Rand.Next(60);
 }

 this->setHitReaction("HitReaction");
 this->actionContext.reportEvent("washit");
 }
 }

 return float0;
 }
 }

 void update() {
 IsoPlayer.s_performance.update.invokeAndMeasure(this, IsoPlayer::updateInternal1);
 }

 void updateInternal1() {
 if (GameClient.bClient && !this->isLocal() && System.currentTimeMillis() - this->lastRemoteUpdate > 5000L) {
 GameClient.receivePlayerTimeout(this->OnlineID);
 }

 if (this->replay != nullptr) {
 this->replay.update();
 }

 bool boolean0 = this->updateInternal2();
 GameClient.instance.sendPlayer2(this);
 if (boolean0) {
 if (!this->bRemote) {
 this->updateLOS();
 }

 super.update();
 }
 }

 void setBeenMovingSprinting() {
 if (this->isJustMoved()) {
 this->setBeenMovingFor(this->getBeenMovingFor() + 1.25F * GameTime.getInstance().getMultiplier());
 } else {
 this->setBeenMovingFor(this->getBeenMovingFor() - 0.625F * GameTime.getInstance().getMultiplier());
 }

 if (this->isJustMoved() && this->isSprinting()) {
 this->setBeenSprintingFor(this->getBeenSprintingFor() + 1.25F * GameTime.getInstance().getMultiplier());
 } else {
 this->setBeenSprintingFor(0.0F);
 }
 }

 bool updateInternal2() {
 if (isTestAIMode) {
 this->isNPC = true;
 }

 if (!this->attackStarted) {
 this->setInitiateAttack(false);
 this->setAttackType(nullptr);
 }

 if ((this->isRunning() || this->isSprinting()) && this->getDeferredMovement(tempo).getLengthSquared() > 0.0F) {
 this->runningTime = this->runningTime + GameTime.getInstance().getMultiplier() / 1.6F;
 } else {
 this->runningTime = 0.0F;
 }

 if (this->getLastCollideTime() > 0.0F) {
 this->setLastCollideTime(this->getLastCollideTime() - GameTime.getInstance().getMultiplier() / 1.6F);
 }

 this->updateDeathDragDown();
 this->updateGodModeKey();
 if (GameClient.bClient) {
 this->networkAI.update();
 }

 this->doDeferredMovement();
 if (GameServer.bServer) {
 this->vehicle4testCollision = nullptr;
 } else if (GameClient.bClient) {
 if (this->vehicle4testCollision != nullptr) {
 if (!this->isLocal()) {
 this->vehicle4testCollision.updateHitByVehicle(this);
 }

 this->vehicle4testCollision = nullptr;
 }
 } else {
 this->updateHitByVehicle();
 this->vehicle4testCollision = nullptr;
 }

 this->updateEmitter();
 this->updateMechanicsItems();
 this->updateHeavyBreathing();
 this->updateTemperatureCheck();
 this->updateAimingStance();
 if (SystemDisabler.doCharacterStats) {
 this->nutrition.update();
 }

 this->fitness.update();
 this->updateSoundListener();
 SafetySystemManager.update(this);
 if (!GameClient.bClient && !GameServer.bServer && this->bDeathFinished) {
 return false;
 } else {
 if (!GameClient.bClient && this->getCurrentBuildingDef() != nullptr && !this->isInvisible()) {
 this->getCurrentBuildingDef().setHasBeenVisited(true);
 }

 if (this->checkSafehouse > 0 && GameServer.bServer) {
 this->checkSafehouse--;
 if (this->checkSafehouse == 0) {
 this->checkSafehouse = 200;
 SafeHouse safeHouse = SafeHouse.isSafeHouse(this->getCurrentSquare(), nullptr, false);
 if (safeHouse != nullptr) {
 safeHouse.updateSafehouse(this);
 safeHouse.checkTrespass(this);
 }
 }
 }

 if (this->bRemote && this->TimeSinceLastNetData > 600) {
 IsoWorld.instance.CurrentCell.getObjectList().remove(this);
 if (this->movingSq != nullptr) {
 this->movingSq.getMovingObjects().remove(this);
 }
 }

 this->TimeSinceLastNetData = (int)(this->TimeSinceLastNetData + GameTime.instance.getMultiplier());
 this->TimeSinceOpenDoor = this->TimeSinceOpenDoor + GameTime.instance.getMultiplier();
 this->lastTargeted = this->lastTargeted + GameTime.instance.getMultiplier();
 this->targetedByZombie = false;
 this->checkActionGroup();
 if (this->updateRemotePlayer()) {
 if (this->updateWhileDead()) {
 return true;
 } else {
 this->updateHeartSound();
 this->checkIsNearWall();
 this->updateExt();
 this->setBeenMovingSprinting();
 return true;
 }
 } else {
 assert !GameServer.bServer;

 assert !this->bRemote;

 assert !GameClient.bClient || this->isLocalPlayer();

 IsoCamera.CamCharacter = this;
 instance = this;
 if (this->isLocalPlayer()) {
 IsoCamera.cameras[this->PlayerIndex].update();
 if (UIManager.getMoodleUI(this->PlayerIndex) != nullptr) {
 UIManager.getMoodleUI(this->PlayerIndex).setCharacter(this);
 }
 }

 if (this->closestZombie > 1.2F) {
 this->slowTimer = -1.0F;
 this->slowFactor = 0.0F;
 }

 this->ContextPanic = this->ContextPanic - 1.5F * GameTime.instance.getTimeDelta();
 if (this->ContextPanic < 0.0F) {
 this->ContextPanic = 0.0F;
 }

 this->lastSeenZombieTime = this->lastSeenZombieTime + GameTime.instance.getGameWorldSecondsSinceLastUpdate() / 60.0F / 60.0F;
 LuaEventManager.triggerEvent("OnPlayerUpdate", this);
 if (this->pressedMovement(false) {
 this->ContextPanic = 0.0F;
 this->ticksSincePressedMovement = 0.0F;
 } else {
 this->ticksSincePressedMovement = this->ticksSincePressedMovement + GameTime.getInstance().getMultiplier() / 1.6F;
 }

 this->setVariable("pressedMovement", this->pressedMovement(true);
 if (this->updateWhileDead()) {
 return true;
 } else {
 this->updateHeartSound();
 this->updateEquippedBaggageContainer();
 this->updateWorldAmbiance();
 this->updateSneakKey();
 this->checkIsNearWall();
 this->updateExt();
 this->updateInteractKeyPanic();
 if (this->isAsleep()) {
 this->m_isPlayerMoving = false;
 }

 if ((
 this->getVehicle() == nullptr
 || !this->getVehicle().isDriver(this)
 || !this->getVehicle().hasHorn()
 || Core.getInstance().getKey("Shout") != Core.getInstance().getKey("VehicleHorn")
 )
 && !this->isAsleep()
 && this->PlayerIndex == 0
 && !this->Speaking
 && GameKeyboard.isKeyDown(Core.getInstance().getKey("Shout"))
 && !this->isNPC) {
 }

 if (this->getIgnoreMovement() || this->isAsleep()) {
 return true;
 } else if (this->checkActionsBlockingMovement()) {
 if (this->getVehicle() != nullptr && this->getVehicle().getDriver() == this && this->getVehicle().getController() != nullptr) {
 this->getVehicle().getController().clientControls.reset();
 this->getVehicle().updatePhysics();
 }

 return true;
 } else {
 this->enterExitVehicle();
 this->checkActionGroup();
 this->checkReloading();
 this->checkWalkTo();
 if (this->checkActionsBlockingMovement()) {
 return true;
 } else if (this->getVehicle() != nullptr) {
 this->updateWhileInVehicle();
 return true;
 } else {
 this->checkVehicleContainers();
 this->setCollidable(true);
 this->updateCursorVisibility();
 this->bSeenThisFrame = false;
 this->bCouldBeSeenThisFrame = false;
 if (IsoCamera.CamCharacter.empty() && GameClient.bClient) {
 IsoCamera.CamCharacter = instance;
 }

 if (this->updateUseKey()) {
 return true;
 } else {
 this->updateEnableModelsKey();
 this->updateChangeCharacterKey();
 bool boolean0 = false;
 bool boolean1 = false;
 this->setRunning(false);
 this->setSprinting(false);
 this->useChargeTime = this->chargeTime;
 if (!this->isBlockMovement() && !this->isNPC) {
 if (!this->isCharging && !this->isChargingLT) {
 this->chargeTime = 0.0F;
 } else {
 this->chargeTime = this->chargeTime + 1.0F * GameTime.instance.getMultiplier();
 }

 this->UpdateInputState(this->inputState);
 boolean1 = this->inputState.bMelee;
 boolean0 = this->inputState.isAttacking;
 this->setRunning(this->inputState.bRunning);
 this->setSprinting(this->inputState.bSprinting);
 if (this->isSprinting() && !this->isJustMoved()) {
 this->setSprinting(false);
 }

 if (this->isSprinting()) {
 this->setRunning(false);
 }

 if (this->inputState.bSprinting && !this->isSprinting()) {
 this->setRunning(true);
 }

 this->setIsAiming(this->inputState.isAiming);
 this->isCharging = this->inputState.isCharging;
 this->isChargingLT = this->inputState.isChargingLT;
 this->updateMovementRates();
 if (this->isAiming()) {
 this->StopAllActionQueueAiming();
 }

 if (boolean0) {
 this->setIsAiming(true);
 }

 this->Waiting = false;
 if (this->isAiming()) {
 this->setMoving(false);
 this->setRunning(false);
 this->setSprinting(false);
 }

 this->TicksSinceSeenZombie++;
 }

 if (this->playerMoveDir.x == 0.0 && this->playerMoveDir.y == 0.0) {
 this->setForceRun(false);
 this->setForceSprint(false);
 }

 this->movementLastFrame.x = this->playerMoveDir.x;
 this->movementLastFrame.y = this->playerMoveDir.y;
 if (this->stateMachine.getCurrent() != StaggerBackState.instance()
 && this->stateMachine.getCurrent() != FakeDeadZombieState.instance()
 && UIManager.speedControls != nullptr) {
 if (GameKeyboard.isKeyDown(88) && Translator.debug) {
 Translator.loadFiles();
 }

 this->setJustMoved(false);
 IsoPlayer.MoveVars moveVars = s_moveVars;
 this->updateMovementFromInput(moveVars);
 if (!this->JustMoved && this->hasPath() && !this->getPathFindBehavior2().bStopping) {
 this->JustMoved = true;
 }

 float float0 = moveVars.strafeX;
 float float1 = moveVars.strafeY;
 if (this->isJustMoved() && !this->isNPC && !this->hasPath()) {
 if (UIManager.getSpeedControls().getCurrentGameSpeed() > 1) {
 UIManager.getSpeedControls().SetCurrentGameSpeed(1);
 }
 } else if (this->stats.endurance < this->stats.endurancedanger
 && Rand.Next((int)(300.0F * GameTime.instance.getInvMultiplier())) == 0) {
 this->xp.AddXP(PerkFactory.Perks.Fitness, 1.0F);
 }

 this->setBeenMovingSprinting();
 float float2 = 1.0F;
 float float3 = 0.0F;
 if (this->isJustMoved() && !this->isNPC) {
 if (!this->isRunning() && !this->isSprinting()) {
 float3 = 1.0F;
 } else {
 float3 = 1.5F;
 }
 }

 float2 *= float3;
 if (float2 > 1.0F) {
 float2 *= this->getSprintMod();
 }

 if (float2 > 1.0F && this->Traits.Athletic.isSet()) {
 float2 *= 1.2F;
 }

 if (float2 > 1.0F) {
 if (this->Traits.Overweight.isSet()) {
 float2 *= 0.99F;
 }

 if (this->Traits.Obese.isSet()) {
 float2 *= 0.85F;
 }

 if (this->getNutrition().getWeight() > 120.0) {
 float2 *= 0.97F;
 }

 if (this->Traits.OutOfShape.isSet()) {
 float2 *= 0.99F;
 }

 if (this->Traits.Unfit.isSet()) {
 float2 *= 0.8F;
 }
 }

 this->updateEndurance(float2);
 if (this->isAiming() && this->isJustMoved()) {
 float2 *= 0.7F;
 }

 if (this->isAiming()) {
 float2 *= this->getNimbleMod();
 }

 this->isWalking = false;
 if (float2 > 0.0F && !this->isNPC) {
 this->isWalking = true;
 LuaEventManager.triggerEvent("OnPlayerMove", this);
 }

 if (this->isJustMoved()) {
 this->sprite.Animate = true;
 }

 if (this->isNPC && this->GameCharacterAIBrain != nullptr) {
 boolean1 = this->GameCharacterAIBrain.HumanControlVars.bMelee;
 this->bBannedAttacking = this->GameCharacterAIBrain.HumanControlVars.bBannedAttacking;
 }

 this->m_meleePressed = boolean1;
 if (boolean1) {
 if (!this->m_lastAttackWasShove) {
 this->setMeleeDelay(Math.min(this->getMeleeDelay(), 2.0F);
 }

 if (!this->bBannedAttacking && this->isAuthorizeShoveStomp() && this->CanAttack() && this->getMeleeDelay() <= 0.0F) {
 this->setDoShove(true);
 if (!this->isCharging && !this->isChargingLT) {
 this->setIsAiming(false);
 }

 this->AttemptAttack(this->useChargeTime);
 this->useChargeTime = 0.0F;
 this->chargeTime = 0.0F;
 }
 } else if (this->isAiming() && this->CanAttack()) {
 if (this->DragCharacter != nullptr) {
 this->DragObject = nullptr;
 this->DragCharacter.Dragging = false;
 this->DragCharacter = nullptr;
 }

 if (boolean0 && !this->bBannedAttacking) {
 this->sprite.Animate = true;
 if (this->getRecoilDelay() <= 0.0F && this->getMeleeDelay() <= 0.0F) {
 this->AttemptAttack(this->useChargeTime);
 }

 this->useChargeTime = 0.0F;
 this->chargeTime = 0.0F;
 }
 }

 if (this->isAiming() && !this->isNPC) {
 if (this->JoypadBind != -1 && !this->bJoypadMovementActive) {
 if (this->getForwardDirection().getLengthSquared() > 0.0F) {
 this->DirectionFromVector(this->getForwardDirection());
 }
 } else {
 Vector2 vector = tempVector2.set(0.0F, 0.0F);
 if (GameWindow.ActivatedJoyPad != nullptr && this->JoypadBind != -1) {
 this->getControllerAimDir(vector);
 } else {
 this->getMouseAimVector(vector);
 }

 if (vector.getLengthSquared() > 0.0F) {
 this->DirectionFromVector(vector);
 this->setForwardDirection(vector);
 }
 }

 moveVars.NewFacing = this->dir;
 }

 if (this->getForwardDirection().x == 0.0F && this->getForwardDirection().y == 0.0F) {
 this->setForwardDirection(this->dir.ToVector());
 }

 if (this->lastAngle.x != this->getForwardDirection().x || this->lastAngle.y != this->getForwardDirection().y) {
 this->lastAngle.x = this->getForwardDirection().x;
 this->lastAngle.y = this->getForwardDirection().y;
 this->dirtyRecalcGridStackTime = 2.0F;
 }

 this->stats.endurance = PZMath.clamp(this->stats.endurance, 0.0F, 1.0F);
 AnimationPlayer animationPlayer = this->getAnimationPlayer();
 if (animationPlayer != nullptr && animationPlayer.isReady()) {
 float float4 = animationPlayer.getAngle() + animationPlayer.getTwistAngle();
 this->dir = IsoDirections.fromAngle(tempVector2.setLengthAndDirection(float4, 1.0F);
 } else if (!this->bFalling && !this->isAiming() && !boolean0) {
 this->dir = moveVars.NewFacing;
 }

 if (this->isAiming() && (GameWindow.ActivatedJoyPad.empty() || this->JoypadBind == -1) {
 this->playerMoveDir.x = moveVars.moveX;
 this->playerMoveDir.y = moveVars.moveY;
 }

 if (!this->isAiming() && this->isJustMoved()) {
 this->playerMoveDir.x = this->getForwardDirection().x;
 this->playerMoveDir.y = this->getForwardDirection().y;
 }

 if (this->isJustMoved()) {
 if (this->isSprinting()) {
 this->CurrentSpeed = 1.5F;
 } else if (this->isRunning()) {
 this->CurrentSpeed = 1.0F;
 } else {
 this->CurrentSpeed = 0.5F;
 }
 } else {
 this->CurrentSpeed = 0.0F;
 }

 bool boolean2 = this->IsInMeleeAttack();
 if (!this->CharacterActions.empty()) {
 BaseAction baseAction = this->CharacterActions.get(0);
 if (baseAction.overrideAnimation) {
 boolean2 = true;
 }
 }

 if (!boolean2 && !this->isForceOverrideAnim()) {
 if (this->getPath2() == nullptr) {
 if (this->CurrentSpeed > 0.0F && (!this->bClimbing || this->lastFallSpeed > 0.0F) {
 if (!this->isRunning() && !this->isSprinting()) {
 this->StopAllActionQueueWalking();
 } else {
 this->StopAllActionQueueRunning();
 }
 }
 } else {
 this->StopAllActionQueueWalking();
 }
 }

 if (this->slowTimer > 0.0F) {
 this->slowTimer = this->slowTimer - GameTime.instance.getRealworldSecondsSinceLastUpdate();
 this->CurrentSpeed = this->CurrentSpeed * (1.0F - this->slowFactor);
 this->slowFactor = this->slowFactor - GameTime.instance.getMultiplier() / 100.0F;
 if (this->slowFactor < 0.0F) {
 this->slowFactor = 0.0F;
 }
 } else {
 this->slowFactor = 0.0F;
 }

 this->playerMoveDir.setLength(this->CurrentSpeed);
 if (this->playerMoveDir.x != 0.0F || this->playerMoveDir.y != 0.0F) {
 this->dirtyRecalcGridStackTime = 10.0F;
 }

 if (this->getPath2() != nullptr && this->current != this->last) {
 this->dirtyRecalcGridStackTime = 10.0F;
 }

 this->closestZombie = 1000000.0F;
 this->weight = 0.3F;
 this->separate();
 this->updateSleepingPillsTaken();
 this->updateTorchStrength();
 if (this->isNPC && this->GameCharacterAIBrain != nullptr) {
 this->GameCharacterAIBrain.postUpdateHuman(this);
 this->setInitiateAttack(this->GameCharacterAIBrain.HumanControlVars.initiateAttack);
 this->setRunning(this->GameCharacterAIBrain.HumanControlVars.bRunning);
 float0 = this->GameCharacterAIBrain.HumanControlVars.strafeX;
 float1 = this->GameCharacterAIBrain.HumanControlVars.strafeY;
 this->setJustMoved(this->GameCharacterAIBrain.HumanControlVars.JustMoved);
 this->updateMovementRates();
 }

 this->m_isPlayerMoving = this->isJustMoved() || this->getPath2() != nullptr && !this->getPathFindBehavior2().bStopping;
 bool boolean3 = this->isInTrees();
 if (boolean3) {
 float float5 = "parkranger".equals(this->getDescriptor().getProfession()) ? 1.3F : 1.0F;
 float5 = "lumberjack" == this->getDescriptor().getProfession()) ? 1.15F : float5;
 if (this->isRunning()) {
 float5 *= 1.1F;
 }

 this->setVariable("WalkSpeedTrees", float5);
 }

 if ((boolean3 || this->m_walkSpeed < 0.4F || this->m_walkInjury > 0.5F) && this->isSprinting() && !this->isGhostMode()) {
 if (this->runSpeedModifier < 1.0) {
 this->setMoodleCantSprint(true);
 }

 this->setSprinting(false);
 this->setRunning(true);
 if (this->isInTreesNoBush()) {
 this->setForceSprint(false);
 this->setBumpType("left");
 this->setVariable("BumpDone", false);
 this->setVariable("BumpFall", true);
 this->setVariable("TripObstacleType", "tree");
 this->actionContext.reportEvent("wasBumped");
 }
 }

 this->m_deltaX = float0;
 this->m_deltaY = float1;
 this->m_windspeed = ClimateManager.getInstance().getWindSpeedMovement();
 float float6 = this->getForwardDirection().getDirectionNeg();
 this->m_windForce = ClimateManager.getInstance().getWindForceMovement(this, float6);
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

 void updateMovementFromInput(IsoPlayer.MoveVars moveVars) {
 moveVars.moveX = 0.0F;
 moveVars.moveY = 0.0F;
 moveVars.strafeX = 0.0F;
 moveVars.strafeY = 0.0F;
 moveVars.NewFacing = this->dir;
 if (!TutorialManager.instance.StealControl) {
 if (!this->isBlockMovement()) {
 if (!this->isNPC) {
 if (!MPDebugAI.updateMovementFromInput(this, moveVars) {
 if (!(this->fallTime > 2.0F) {
 if (GameWindow.ActivatedJoyPad != nullptr && this->JoypadBind != -1) {
 this->updateMovementFromJoypad(moveVars);
 }

 if (this->PlayerIndex == 0 && this->JoypadBind == -1) {
 this->updateMovementFromKeyboardMouse(moveVars);
 }

 if (this->isJustMoved()) {
 this->getForwardDirection().normalize();
 UIManager.speedControls.SetCurrentGameSpeed(1);
 }
 }
 }
 }
 }
 }
 }

 void updateMovementFromJoypad(IsoPlayer.MoveVars moveVars) {
 this->playerMoveDir.x = 0.0F;
 this->playerMoveDir.y = 0.0F;
 this->getJoypadAimVector(tempVector2);
 float float0 = tempVector2.x;
 float float1 = tempVector2.y;
 Vector2 vector0 = this->getJoypadMoveVector(tempVector2);
 if (vector0.getLength() > 1.0F) {
 vector0.setLength(1.0F);
 }

 if (this->isAutoWalk()) {
 if (vector0.getLengthSquared() < 0.25F) {
 vector0.set(this->getAutoWalkDirection());
 } else {
 this->setAutoWalkDirection(vector0);
 this->getAutoWalkDirection().normalize();
 }
 }

 float float2 = vector0.x;
 float float3 = vector0.y;
 if (Math.abs(float2) > 0.0F) {
 this->playerMoveDir.x += 0.04F * float2;
 this->playerMoveDir.y -= 0.04F * float2;
 this->setJustMoved(true);
 }

 if (Math.abs(float3) > 0.0F) {
 this->playerMoveDir.y += 0.04F * float3;
 this->playerMoveDir.x += 0.04F * float3;
 this->setJustMoved(true);
 }

 this->playerMoveDir.setLength(0.05F * (float)Math.pow(vector0.getLength(), 9.0);
 if (float0 != 0.0F || float1 != 0.0F) {
 Vector2 vector1 = tempVector2.set(float0, float1);
 vector1.normalize();
 moveVars.NewFacing = IsoDirections.fromAngle(vector1);
 } else if ((float2 != 0.0F || float3 != 0.0F) && this->playerMoveDir.getLengthSquared() > 0.0F) {
 vector0 = tempVector2.set(this->playerMoveDir);
 vector0.normalize();
 moveVars.NewFacing = IsoDirections.fromAngle(vector0);
 }

 PathFindBehavior2 pathFindBehavior2 = this->getPathFindBehavior2();
 if (this->playerMoveDir.x == 0.0F
 && this->playerMoveDir.y == 0.0F
 && this->getPath2() != nullptr
 && pathFindBehavior2.isStrafing()
 && !pathFindBehavior2.bStopping) {
 this->playerMoveDir.set(pathFindBehavior2.getTargetX() - this->x, pathFindBehavior2.getTargetY() - this->y);
 this->playerMoveDir.normalize();
 }

 if (this->playerMoveDir.x != 0.0F || this->playerMoveDir.y != 0.0F) {
 if (this->isStrafing()) {
 tempo.set(this->playerMoveDir.x, -this->playerMoveDir.y);
 tempo.normalize();
 float float4 = this->legsSprite.modelSlot.model.AnimPlayer.getRenderedAngle();
 if (float4 > Math.PI * 2) {
 float4 = (float)(float4 - (Math.PI * 2);
 }

 if (float4 < 0.0F) {
 float4 = (float)(float4 + (Math.PI * 2);
 }

 tempo.rotate(float4);
 moveVars.strafeX = tempo.x;
 moveVars.strafeY = tempo.y;
 this->m_IPX = this->playerMoveDir.x;
 this->m_IPY = this->playerMoveDir.y;
 } else {
 moveVars.moveX = this->playerMoveDir.x;
 moveVars.moveY = this->playerMoveDir.y;
 tempo.set(this->playerMoveDir);
 tempo.normalize();
 this->setForwardDirection(tempo);
 }
 }
 }

 void updateMovementFromKeyboardMouse(IsoPlayer.MoveVars moveVars) {
 int int0 = Core.getInstance().getKey("Left");
 int int1 = Core.getInstance().getKey("Right");
 int int2 = Core.getInstance().getKey("Forward");
 int int3 = Core.getInstance().getKey("Backward");
 bool boolean0 = GameKeyboard.isKeyDown(int0);
 bool boolean1 = GameKeyboard.isKeyDown(int1);
 bool boolean2 = GameKeyboard.isKeyDown(int2);
 bool boolean3 = GameKeyboard.isKeyDown(int3);
 if (!boolean0 && !boolean1 && !boolean2 && !boolean3
 || int0 != 30 && int1 != 30 && int2 != 30 && int3 != 30
 || !GameKeyboard.isKeyDown(29) && !GameKeyboard.isKeyDown(157)
 || !UIManager.isMouseOverInventory()
 || !Core.getInstance().isSelectingAll()) {
 if (!this->isIgnoreInputsForDirection()) {
 if (Core.bAltMoveMethod) {
 if (boolean0 && !boolean1) {
 moveVars.moveX -= 0.04F;
 moveVars.NewFacing = IsoDirections.W;
 }

 if (boolean1 && !boolean0) {
 moveVars.moveX += 0.04F;
 moveVars.NewFacing = IsoDirections.E;
 }

 if (boolean2 && !boolean3) {
 moveVars.moveY -= 0.04F;
 if (moveVars.NewFacing == IsoDirections.W) {
 moveVars.NewFacing = IsoDirections.NW;
 } else if (moveVars.NewFacing == IsoDirections.E) {
 moveVars.NewFacing = IsoDirections.NE;
 } else {
 moveVars.NewFacing = IsoDirections.N;
 }
 }

 if (boolean3 && !boolean2) {
 moveVars.moveY += 0.04F;
 if (moveVars.NewFacing == IsoDirections.W) {
 moveVars.NewFacing = IsoDirections.SW;
 } else if (moveVars.NewFacing == IsoDirections.E) {
 moveVars.NewFacing = IsoDirections.SE;
 } else {
 moveVars.NewFacing = IsoDirections.S;
 }
 }
 } else {
 if (boolean0) {
 moveVars.moveX = -1.0F;
 } else if (boolean1) {
 moveVars.moveX = 1.0F;
 }

 if (boolean2) {
 moveVars.moveY = 1.0F;
 } else if (boolean3) {
 moveVars.moveY = -1.0F;
 }

 if (moveVars.moveX != 0.0F || moveVars.moveY != 0.0F) {
 tempo.set(moveVars.moveX, moveVars.moveY);
 tempo.normalize();
 moveVars.NewFacing = IsoDirections.fromAngle(tempo);
 }
 }
 }

 PathFindBehavior2 pathFindBehavior2 = this->getPathFindBehavior2();
 if (moveVars.moveX == 0.0F
 && moveVars.moveY == 0.0F
 && this->getPath2() != nullptr
 && (pathFindBehavior2.isStrafing() || this->isAiming())
 && !pathFindBehavior2.bStopping) {
 Vector2 vector0 = tempo.set(pathFindBehavior2.getTargetX() - this->x, pathFindBehavior2.getTargetY() - this->y);
 Vector2 vector1 = tempo2.set(-1.0F, 0.0F);
 float float0 = 1.0F;
 float float1 = vector0.dot(vector1);
 float float2 = float1 / float0;
 vector1 = tempo2.set(0.0F, -1.0F);
 float1 = vector0.dot(vector1);
 float float3 = float1 / float0;
 tempo.set(float3, float2);
 tempo.normalize();
 tempo.rotate((float) (Math.PI / 4);
 moveVars.moveX = tempo.x;
 moveVars.moveY = tempo.y;
 }

 if (moveVars.moveX != 0.0F || moveVars.moveY != 0.0F) {
 if (this->stateMachine.getCurrent() == PathFindState.instance()) {
 this->setDefaultState();
 }

 this->setJustMoved(true);
 this->setMoveDelta(1.0F);
 if (this->isStrafing()) {
 tempo.set(moveVars.moveX, moveVars.moveY);
 tempo.normalize();
 float float4 = this->legsSprite.modelSlot.model.AnimPlayer.getRenderedAngle();
 float4 = (float)(float4 + (Math.PI / 4);
 if (float4 > Math.PI * 2) {
 float4 = (float)(float4 - (Math.PI * 2);
 }

 if (float4 < 0.0F) {
 float4 = (float)(float4 + (Math.PI * 2);
 }

 tempo.rotate(float4);
 moveVars.strafeX = tempo.x;
 moveVars.strafeY = tempo.y;
 this->m_IPX = moveVars.moveX;
 this->m_IPY = moveVars.moveY;
 } else {
 tempo.set(moveVars.moveX, -moveVars.moveY);
 tempo.normalize();
 tempo.rotate((float) (-Math.PI / 4);
 this->setForwardDirection(tempo);
 }
 }
 }
 }

 void updateAimingStance() {
 if (this->isVariable("LeftHandMask", "RaiseHand")) {
 this->clearVariable("LeftHandMask");
 }

 if (this->isAiming() && !this->isCurrentState(SwipeStatePlayer.instance())) {
 HandWeapon weapon = Type.tryCastTo(this->getPrimaryHandItem(), HandWeapon.class);
 weapon = weapon.empty() ? this->bareHands : weapon;
 SwipeStatePlayer.instance().calcValidTargets(this, weapon, true, s_targetsProne, s_targetsStanding);
 HitInfo hitInfo0 = s_targetsStanding.empty() ? nullptr : s_targetsStanding.get(0);
 HitInfo hitInfo1 = s_targetsProne.empty() ? nullptr : s_targetsProne.get(0);
 if (SwipeStatePlayer.instance().isProneTargetBetter(this, hitInfo0, hitInfo1) {
 hitInfo0 = nullptr;
 }

 bool boolean0 = this->isAttackAnim() || this->getVariableBoolean("ShoveAnim") || this->getVariableBoolean("StompAnim");
 if (!boolean0) {
 this->setAimAtFloor(false);
 }

 if (hitInfo0 != nullptr) {
 if (!boolean0) {
 this->setAimAtFloor(false);
 }
 } else if (hitInfo1 != nullptr && !boolean0) {
 this->setAimAtFloor(true);
 }

 if (hitInfo0 != nullptr) {
 boolean boolean1 = !this->isAttackAnim()
 && weapon.getSwingAnim() != nullptr
 && weapon.CloseKillMove != nullptr
 && hitInfo0.distSq < weapon.getMinRange() * weapon.getMinRange();
 if (boolean1 && (this->getSecondaryHandItem() == nullptr || this->getSecondaryHandItem().getItemReplacementSecondHand() == nullptr) {
 this->setVariable("LeftHandMask", "RaiseHand");
 }
 }

 SwipeStatePlayer.instance().hitInfoPool.release(s_targetsStanding);
 SwipeStatePlayer.instance().hitInfoPool.release(s_targetsProne);
 s_targetsStanding.clear();
 s_targetsProne.clear();
 }
 }

 void calculateStats() {
 if (!this->bRemote) {
 super.calculateStats();
 }
 }

 void updateStats_Sleeping() {
 float float0 = 2.0F;
 if (allPlayersAsleep()) {
 float0 *= GameTime.instance.getDeltaMinutesPerDay();
 }

 this->stats.endurance = (float)(
 this->stats.endurance
 + ZomboidGlobals.ImobileEnduranceReduce
 * SandboxOptions.instance.getEnduranceRegenMultiplier()
 * this->getRecoveryMod()
 * GameTime.instance.getMultiplier()
 * float0
 );
 if (this->stats.endurance > 1.0F) {
 this->stats.endurance = 1.0F;
 }

 if (this->stats.fatigue > 0.0F) {
 float float1 = 1.0F;
 if (this->Traits.Insomniac.isSet()) {
 float1 *= 0.5F;
 }

 if (this->Traits.NightOwl.isSet()) {
 float1 *= 1.4F;
 }

 float float2 = 1.0F;
 if ("goodBed" == this->getBedType())) {
 float2 = 1.1F;
 }

 if ("badBed" == this->getBedType())) {
 float2 = 0.9F;
 }

 if ("floor" == this->getBedType())) {
 float2 = 0.6F;
 }

 float float3 = 1.0F / GameTime.instance.getMinutesPerDay() / 60.0F * GameTime.instance.getMultiplier() / 2.0F;
 this->timeOfSleep += float3;
 if (this->timeOfSleep > this->delayToActuallySleep) {
 float float4 = 1.0F;
 if (this->Traits.NeedsLessSleep.isSet()) {
 float4 *= 0.75F;
 } else if (this->Traits.NeedsMoreSleep.isSet()) {
 float4 *= 1.18F;
 }

 float float5 = 1.0F;
 if (this->stats.fatigue <= 0.3F) {
 float5 = 7.0F * float4;
 this->stats.fatigue -= float3 / float5 * 0.3F * float1 * float2;
 } else {
 float5 = 5.0F * float4;
 this->stats.fatigue -= float3 / float5 * 0.7F * float1 * float2;
 }
 }

 if (this->stats.fatigue < 0.0F) {
 this->stats.fatigue = 0.0F;
 }
 }

 if (this->Moodles.getMoodleLevel(MoodleType.FoodEaten) == 0) {
 float float6 = this->getAppetiteMultiplier();
 this->stats.hunger = (float)(
 this->stats.hunger
 + ZomboidGlobals.HungerIncreaseWhileAsleep
 * SandboxOptions.instance.getStatsDecreaseMultiplier()
 * float6
 * GameTime.instance.getMultiplier()
 * GameTime.instance.getDeltaMinutesPerDay()
 * this->getHungerMultiplier()
 );
 } else {
 this->stats.hunger = this->stats.hunger
 + (float)(
 ZomboidGlobals.HungerIncreaseWhenWellFed
 * SandboxOptions.instance.getStatsDecreaseMultiplier()
 * ZomboidGlobals.HungerIncreaseWhileAsleep
 * SandboxOptions.instance.getStatsDecreaseMultiplier()
 * GameTime.instance.getMultiplier()
 * this->getHungerMultiplier()
 * GameTime.instance.getDeltaMinutesPerDay()
 );
 }

 if (this->ForceWakeUpTime == 0.0F) {
 this->ForceWakeUpTime = 9.0F;
 }

 float float7 = GameTime.getInstance().getTimeOfDay();
 float float8 = GameTime.getInstance().getLastTimeOfDay();
 if (float8 > float7) {
 if (float8 < this->ForceWakeUpTime) {
 float7 += 24.0F;
 } else {
 float8 -= 24.0F;
 }
 }

 bool boolean0 = float7 >= this->ForceWakeUpTime && float8 < this->ForceWakeUpTime;
 if (this->getAsleepTime() > 16.0F) {
 boolean0 = true;
 }

 if (GameClient.bClient || numPlayers > 1) {
 boolean0 = boolean0 || this->pressedAim() || this->pressedMovement(false);
 }

 if (this->ForceWakeUp) {
 boolean0 = true;
 }

 if (this->Asleep && boolean0) {
 this->ForceWakeUp = false;
 SoundManager.instance.setMusicWakeState(this, "WakeNormal");
 SleepingEvent.instance.wakeUp(this);
 this->ForceWakeUpTime = -1.0F;
 if (GameClient.bClient) {
 GameClient.instance.sendPlayer(this);
 }

 this->dirtyRecalcGridStackTime = 20.0F;
 }
 }

 void updateEnduranceWhileSitting() {
 float float0 = (float)ZomboidGlobals.SittingEnduranceMultiplier;
 float0 *= 1.0F - this->stats.fatigue;
 float0 *= GameTime.instance.getMultiplier();
 this->stats.endurance = (float)(
 this->stats.endurance
 + ZomboidGlobals.ImobileEnduranceReduce * SandboxOptions.instance.getEnduranceRegenMultiplier() * this->getRecoveryMod() * float0
 );
 this->stats.endurance = PZMath.clamp(this->stats.endurance, 0.0F, 1.0F);
 }

 void updateEndurance(float float7) {
 if (this->isSitOnGround()) {
 this->updateEnduranceWhileSitting();
 } else {
 float float0 = 1.0F;
 if (this->isSneaking()) {
 float0 = 1.5F;
 }

 if (this->CurrentSpeed > 0.0F && (this->isRunning() || this->isSprinting())) {
 double double0 = ZomboidGlobals.RunningEnduranceReduce;
 if (this->isSprinting()) {
 double0 = ZomboidGlobals.SprintingEnduranceReduce;
 }

 float float1 = 1.4F;
 if (this->Traits.Overweight.isSet()) {
 float1 = 2.9F;
 }

 if (this->Traits.Athletic.isSet()) {
 float1 = 0.8F;
 }

 float1 *= 2.3F;
 float1 *= this->getPacingMod();
 float1 *= this->getHyperthermiaMod();
 float float2 = 0.7F;
 if (this->Traits.Asthmatic.isSet()) {
 float2 = 1.4F;
 }

 if (this->Moodles.getMoodleLevel(MoodleType.HeavyLoad) == 0) {
 this->stats.endurance = (float)(this->stats.endurance - double0 * float1 * 0.5 * float2 * GameTime.instance.getMultiplier() * float0);
 } else {
 float float3 = 2.8F;
 switch (this->Moodles.getMoodleLevel(MoodleType.HeavyLoad) {
 case 1:
 float3 = 1.5F;
 break;
 case 2:
 float3 = 1.9F;
 break;
 case 3:
 float3 = 2.3F;
 }

 this->stats.endurance = (float)(this->stats.endurance - double0 * float1 * 0.5 * float2 * GameTime.instance.getMultiplier() * float3 * float0);
 }
 } else if (this->CurrentSpeed > 0.0F && this->Moodles.getMoodleLevel(MoodleType.HeavyLoad) > 2) {
 float float4 = 0.7F;
 if (this->Traits.Asthmatic.isSet()) {
 float4 = 1.4F;
 }

 float float5 = 1.4F;
 if (this->Traits.Overweight.isSet()) {
 float5 = 2.9F;
 }

 if (this->Traits.Athletic.isSet()) {
 float5 = 0.8F;
 }

 float5 *= 3.0F;
 float5 *= this->getPacingMod();
 float5 *= this->getHyperthermiaMod();
 float float6 = 2.8F;
 switch (this->Moodles.getMoodleLevel(MoodleType.HeavyLoad) {
 case 2:
 float6 = 1.5F;
 break;
 case 3:
 float6 = 1.9F;
 break;
 case 4:
 float6 = 2.3F;
 }

 this->stats.endurance = (float)(
 this->stats.endurance
 - ZomboidGlobals.RunningEnduranceReduce * float5 * 0.5 * float4 * float0 * GameTime.instance.getMultiplier() * float6 / 2.0
 );
 }

 switch (this->Moodles.getMoodleLevel(MoodleType.Endurance) {
 case 1:
 float7 *= 0.95F;
 break;
 case 2:
 float7 *= 0.9F;
 break;
 case 3:
 float7 *= 0.8F;
 break;
 case 4:
 float7 *= 0.6F;
 }

 if (this->stats.enduranceRecharging) {
 float7 *= 0.85F;
 }

 if (!this->isPlayerMoving()) {
 float float8 = 1.0F;
 float8 *= 1.0F - this->stats.fatigue;
 float8 *= GameTime.instance.getMultiplier();
 if (this->Moodles.getMoodleLevel(MoodleType.HeavyLoad) <= 1) {
 this->stats.endurance = (float)(
 this->stats.endurance
 + ZomboidGlobals.ImobileEnduranceReduce * SandboxOptions.instance.getEnduranceRegenMultiplier() * this->getRecoveryMod() * float8
 );
 }
 }

 if (!this->isSprinting() && !this->isRunning() && this->CurrentSpeed > 0.0F) {
 float float9 = 1.0F;
 float9 *= 1.0F - this->stats.fatigue;
 float9 *= GameTime.instance.getMultiplier();
 if (this->getMoodles().getMoodleLevel(MoodleType.Endurance) < 2) {
 if (this->Moodles.getMoodleLevel(MoodleType.HeavyLoad) <= 1) {
 this->stats.endurance = (float)(
 this->stats.endurance
 + ZomboidGlobals.ImobileEnduranceReduce
 / 4.0
 * SandboxOptions.instance.getEnduranceRegenMultiplier()
 * this->getRecoveryMod()
 * float9
 );
 }
 } else {
 this->stats.endurance = (float)(this->stats.endurance - ZomboidGlobals.RunningEnduranceReduce / 7.0 * float0);
 }
 }
 }
 }

 bool checkActionsBlockingMovement() {
 if (this->CharacterActions.empty()) {
 return false;
 } else {
 BaseAction baseAction = this->CharacterActions.get(0);
 return baseAction.blockMovementEtc;
 }
 }

 void updateInteractKeyPanic() {
 if (this->PlayerIndex == 0) {
 if (GameKeyboard.isKeyPressed(Core.getInstance().getKey("Interact"))) {
 this->ContextPanic += 0.6F;
 }
 }
 }

 void updateSneakKey() {
 if (this->PlayerIndex != 0) {
 this->bSneakDebounce = false;
 } else {
 if (this->isBlockMovement() || !GameKeyboard.isKeyDown(Core.getInstance().getKey("Crouch"))) {
 this->bSneakDebounce = false;
 } else if (!this->bSneakDebounce) {
 this->setSneaking(!this->isSneaking());
 this->bSneakDebounce = true;
 }
 }
 }

 void updateChangeCharacterKey() {
 if (Core.bDebug) {
 if (this->PlayerIndex == 0 && GameKeyboard.isKeyDown(22) {
 if (!this->bChangeCharacterDebounce) {
 this->FollowCamStack.clear();
 this->bChangeCharacterDebounce = true;

 for (int int0 = 0; int0 < this->getCell().getObjectList().size(); int0++) {
 IsoMovingObject movingObject = this->getCell().getObjectList().get(int0);
 if (movingObject instanceof IsoSurvivor) {
 this->FollowCamStack.add((IsoSurvivor)movingObject);
 }
 }

 if (!this->FollowCamStack.empty()) {
 if (this->followID >= this->FollowCamStack.size()) {
 this->followID = 0;
 }

 IsoCamera.SetCharacterToFollow(this->FollowCamStack.get(this->followID);
 this->followID++;
 }
 }
 } else {
 this->bChangeCharacterDebounce = false;
 }
 }
 }

 void updateEnableModelsKey() {
 if (Core.bDebug) {
 if (this->PlayerIndex == 0 && GameKeyboard.isKeyPressed(Core.getInstance().getKey("ToggleModelsEnabled"))) {
 ModelManager.instance.bDebugEnableModels = !ModelManager.instance.bDebugEnableModels;
 }
 }
 }

 void updateDeathDragDown() {
 if (!this->isDead()) {
 if (this->isDeathDragDown()) {
 if (this->isGodMod()) {
 this->setDeathDragDown(false);
 } else if (!"EndDeath" == this->getHitReaction())) {
 for (int int0 = -1; int0 <= 1; int0++) {
 for (int int1 = -1; int1 <= 1; int1++) {
 IsoGridSquare square = this->getCell().getGridSquare((int)this->x + int1, (int)this->y + int0, (int)this->z);
 if (square != nullptr) {
 for (int int2 = 0; int2 < square.getMovingObjects().size(); int2++) {
 IsoMovingObject movingObject = square.getMovingObjects().get(int2);
 IsoZombie zombie0 = Type.tryCastTo(movingObject, IsoZombie.class);
 if (zombie0 != nullptr && zombie0.isAlive() && !zombie0.isOnFloor()) {
 this->setAttackedBy(zombie0);
 this->setHitReaction("EndDeath");
 this->setBlockMovement(true);
 return;
 }
 }
 }
 }
 }

 this->setDeathDragDown(false);
 if (GameClient.bClient) {
 DebugLog.Multiplayer.warn("UpdateDeathDragDown: no zombies found around player \"%s\"", this->getUsername());
 this->setHitFromBehind(false);
 this->Kill(nullptr);
 }
 }
 }
 }
 }

 void updateGodModeKey() {
 if (Core.bDebug) {
 if (GameKeyboard.isKeyPressed(Core.getInstance().getKey("ToggleGodModeInvisible"))) {
 IsoPlayer player0 = nullptr;

 for (int int0 = 0; int0 < numPlayers; int0++) {
 if (players[int0] != nullptr && !players[int0].isDead()) {
 player0 = players[int0];
 break;
 }
 }

 if (this == player0) {
 bool boolean0 = !player0.isGodMod();
 DebugLog.General.println("Toggle GodMode: %s", boolean0 ? "ON" : "OFF");
 player0.setInvisible(boolean0);
 player0.setGhostMode(boolean0);
 player0.setGodMod(boolean0);

 for (int int1 = 0; int1 < numPlayers; int1++) {
 if (players[int1] != nullptr && players[int1] != player0) {
 players[int1].setInvisible(boolean0);
 players[int1].setGhostMode(boolean0);
 players[int1].setGodMod(boolean0);
 }
 }

 if (GameClient.bClient) {
 GameClient.sendPlayerExtraInfo(player0);
 }
 }
 }
 }
 }

 void checkReloading() {
 HandWeapon weapon = Type.tryCastTo(this->getPrimaryHandItem(), HandWeapon.class);
 if (weapon != nullptr && weapon.isReloadable(this) {
 bool boolean0 = false;
 bool boolean1 = false;
 if (this->JoypadBind != -1 && this->bJoypadMovementActive) {
 bool boolean2 = JoypadManager.instance.isRBPressed(this->JoypadBind);
 if (boolean2) {
 boolean0 = !this->bReloadButtonDown;
 }

 this->bReloadButtonDown = boolean2;
 boolean2 = JoypadManager.instance.isLBPressed(this->JoypadBind);
 if (boolean2) {
 boolean1 = !this->bRackButtonDown;
 }

 this->bRackButtonDown = boolean2;
 }

 if (this->PlayerIndex == 0) {
 bool boolean3 = GameKeyboard.isKeyDown(Core.getInstance().getKey("ReloadWeapon"));
 if (boolean3) {
 boolean0 = !this->bReloadKeyDown;
 }

 this->bReloadKeyDown = boolean3;
 boolean3 = GameKeyboard.isKeyDown(Core.getInstance().getKey("Rack Firearm"));
 if (boolean3) {
 boolean1 = !this->bRackKeyDown;
 }

 this->bRackKeyDown = boolean3;
 }

 if (boolean0) {
 this->setVariable("WeaponReloadType", weapon.getWeaponReloadType());
 LuaEventManager.triggerEvent("OnPressReloadButton", this, weapon);
 } else if (boolean1) {
 this->setVariable("WeaponReloadType", weapon.getWeaponReloadType());
 LuaEventManager.triggerEvent("OnPressRackButton", this, weapon);
 }
 }
 }

 void postupdate() {
 IsoPlayer.s_performance.postUpdate.invokeAndMeasure(this, IsoPlayer::postupdateInternal);
 }

 void postupdateInternal() {
 bool boolean0 = this->hasHitReaction();
 super.postupdate();
 if (boolean0
 && this->hasHitReaction()
 && !this->isCurrentState(PlayerHitReactionState.instance())
 && !this->isCurrentState(PlayerHitReactionPVPState.instance())) {
 this->setHitReaction("");
 }

 this->highlightRangedTargets();
 if (this->isNPC) {
 GameTime gameTime = GameTime.getInstance();
 float float0 = 1.0F / gameTime.getMinutesPerDay() / 60.0F * gameTime.getMultiplier() / 2.0F;
 if (Core.bLastStand) {
 float0 = 1.0F / gameTime.getMinutesPerDay() / 60.0F * gameTime.getUnmoddedMultiplier() / 2.0F;
 }

 this->setHoursSurvived(this->getHoursSurvived() + float0);
 }

 this->getBodyDamage().setBodyPartsLastState();
 }

 void highlightRangedTargets() {
 if (this->isLocalPlayer() && !this->isNPC) {
 if (this->isAiming()) {
 if (Core.getInstance().getOptionAimOutline() != 1) {
 IsoPlayer.s_performance.highlightRangedTargets.invokeAndMeasure(this, IsoPlayer::highlightRangedTargetsInternal);
 }
 }
 }
 }

 void highlightRangedTargetsInternal() {
 HandWeapon weapon0 = Type.tryCastTo(this->getPrimaryHandItem(), HandWeapon.class);
 if (weapon0.empty() || weapon0.getSwingAnim() == nullptr || weapon0.getCondition() <= 0) {
 weapon0 = this->bareHands;
 }

 if (Core.getInstance().getOptionAimOutline() != 2 || weapon0.isRanged()) {
 AttackVars attackVars = new AttackVars();
 std::vector arrayList = new ArrayList();
 bool boolean0 = this->bDoShove;
 HandWeapon weapon1 = this->getUseHandWeapon();
 this->setDoShove(false);
 this->setUseHandWeapon(weapon0);
 SwipeStatePlayer.instance().CalcAttackVars(this, attackVars);
 SwipeStatePlayer.instance().CalcHitList(this, false, attackVars, arrayList);

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 HitInfo hitInfo = (HitInfo)arrayList.get(int0);
 IsoMovingObject movingObject = hitInfo.getObject();
 if (movingObject instanceof IsoZombie || movingObject instanceof IsoPlayer) {
 ColorInfo colorInfo = new ColorInfo();
 Core.getInstance().getBadHighlitedColor().interp(Core.getInstance().getGoodHighlitedColor(), hitInfo.chance / 100.0F, colorInfo);
 movingObject.bOutline[this->PlayerIndex] = true;
 if (movingObject.outlineColor[this->PlayerIndex] == nullptr) {
 movingObject.outlineColor[this->PlayerIndex] = std::make_unique<ColorInfo>();
 }

 movingObject.outlineColor[this->PlayerIndex].set(colorInfo);
 }

 if (hitInfo.window.getObject() != nullptr) {
 hitInfo.window.getObject().setHighlightColor(0.8F, 0.1F, 0.1F, 0.5F);
 hitInfo.window.getObject().setHighlighted(true);
 }
 }

 this->setDoShove(boolean0);
 this->setUseHandWeapon(weapon1);
 }
 }

 bool isSolidForSeparate() {
 return this->isGhostMode() ? false : super.isSolidForSeparate();
 }

 bool isPushableForSeparate() {
 if (this->isCurrentState(PlayerHitReactionState.instance())) {
 return false;
 } else {
 return this->isCurrentState(SwipeStatePlayer.instance()) ? false : super.isPushableForSeparate();
 }
 }

 bool isPushedByForSeparate(IsoMovingObject other) {
 if (!this->isPlayerMoving() && other.isZombie() && ((IsoZombie)other).isAttacking()) {
 return false;
 } else {
 return !GameClient.bClient || this->isLocalPlayer() && this->isJustMoved() ? super.isPushedByForSeparate(other) : false;
 }
 }

 void updateExt() {
 if (!this->isSneaking()) {
 this->extUpdateCount = this->extUpdateCount + GameTime.getInstance().getMultiplier() / 0.8F;
 if (!this->getAdvancedAnimator().containsAnyIdleNodes() && !this->isSitOnGround()) {
 this->extUpdateCount = 0.0F;
 }

 if (!(this->extUpdateCount <= 5000.0F) {
 this->extUpdateCount = 0.0F;
 if (this->stats.NumVisibleZombies == 0 && this->stats.NumChasingZombies == 0) {
 if (Rand.NextBool(3) {
 if (this->getAdvancedAnimator().containsAnyIdleNodes() || this->isSitOnGround()) {
 this->onIdlePerformFidgets();
 this->reportEvent("EventDoExt");
 }
 }
 }
 }
 }
 }

 void onIdlePerformFidgets() {
 Moodles moodles = this->getMoodles();
 BodyDamage bodyDamage = this->getBodyDamage();
 if (moodles.getMoodleLevel(MoodleType.Hypothermia) > 0 && Rand.NextBool(7) {
 this->setVariable("Ext", "Shiver");
 } else if (moodles.getMoodleLevel(MoodleType.Hyperthermia) > 0 && Rand.NextBool(7) {
 this->setVariable("Ext", "WipeBrow");
 } else if (moodles.getMoodleLevel(MoodleType.Sick) > 0 && Rand.NextBool(7) {
 if (Rand.NextBool(4) {
 this->setVariable("Ext", "Cough");
 } else {
 this->setVariable("Ext", "PainStomach" + (Rand.Next(2) + 1);
 }
 } else if (moodles.getMoodleLevel(MoodleType.Endurance) > 2 && Rand.NextBool(10) {
 if (Rand.NextBool(5) && !this->isSitOnGround()) {
 this->setVariable("Ext", "BentDouble");
 } else {
 this->setVariable("Ext", "WipeBrow");
 }
 } else if (moodles.getMoodleLevel(MoodleType.Tired) > 2 && Rand.NextBool(10) {
 if (Rand.NextBool(7) {
 this->setVariable("Ext", "TiredStretch");
 } else if (Rand.NextBool(7) {
 this->setVariable("Ext", "Sway");
 } else {
 this->setVariable("Ext", "Yawn");
 }
 } else if (bodyDamage.doBodyPartsHaveInjuries(BodyPartType.Head, BodyPartType.Neck) && Rand.NextBool(7) {
 if (bodyDamage.areBodyPartsBleeding(BodyPartType.Head, BodyPartType.Neck) && Rand.NextBool(2) {
 this->setVariable("Ext", "WipeHead");
 } else {
 this->setVariable("Ext", "PainHead" + (Rand.Next(2) + 1);
 }
 } else if (bodyDamage.doBodyPartsHaveInjuries(BodyPartType.UpperArm_L, BodyPartType.ForeArm_L) && Rand.NextBool(7) {
 if (bodyDamage.areBodyPartsBleeding(BodyPartType.UpperArm_L, BodyPartType.ForeArm_L) && Rand.NextBool(2) {
 this->setVariable("Ext", "WipeArmL");
 } else {
 this->setVariable("Ext", "PainArmL");
 }
 } else if (bodyDamage.doBodyPartsHaveInjuries(BodyPartType.UpperArm_R, BodyPartType.ForeArm_R) && Rand.NextBool(7) {
 if (bodyDamage.areBodyPartsBleeding(BodyPartType.UpperArm_R, BodyPartType.ForeArm_R) && Rand.NextBool(2) {
 this->setVariable("Ext", "WipeArmR");
 } else {
 this->setVariable("Ext", "PainArmR");
 }
 } else if (bodyDamage.doesBodyPartHaveInjury(BodyPartType.Hand_L) && Rand.NextBool(7) {
 this->setVariable("Ext", "PainHandL");
 } else if (bodyDamage.doesBodyPartHaveInjury(BodyPartType.Hand_R) && Rand.NextBool(7) {
 this->setVariable("Ext", "PainHandR");
 } else if (!this->isSitOnGround() && bodyDamage.doBodyPartsHaveInjuries(BodyPartType.UpperLeg_L, BodyPartType.LowerLeg_L) && Rand.NextBool(7) {
 if (bodyDamage.areBodyPartsBleeding(BodyPartType.UpperLeg_L, BodyPartType.LowerLeg_L) && Rand.NextBool(2) {
 this->setVariable("Ext", "WipeLegL");
 } else {
 this->setVariable("Ext", "PainLegL");
 }
 } else if (!this->isSitOnGround() && bodyDamage.doBodyPartsHaveInjuries(BodyPartType.UpperLeg_R, BodyPartType.LowerLeg_R) && Rand.NextBool(7) {
 if (bodyDamage.areBodyPartsBleeding(BodyPartType.UpperLeg_R, BodyPartType.LowerLeg_R) && Rand.NextBool(2) {
 this->setVariable("Ext", "WipeLegR");
 } else {
 this->setVariable("Ext", "PainLegR");
 }
 } else if (bodyDamage.doBodyPartsHaveInjuries(BodyPartType.Torso_Upper, BodyPartType.Torso_Lower) && Rand.NextBool(7) {
 if (bodyDamage.areBodyPartsBleeding(BodyPartType.Torso_Upper, BodyPartType.Torso_Lower) && Rand.NextBool(2) {
 this->setVariable("Ext", "WipeTorso" + (Rand.Next(2) + 1);
 } else {
 this->setVariable("Ext", "PainTorso");
 }
 } else if (WeaponType.getWeaponType(this) != WeaponType.barehand) {
 this->setVariable("Ext", Rand.Next(5) + 1 + "");
 } else if (Rand.NextBool(10) {
 this->setVariable("Ext", "ChewNails");
 } else if (Rand.NextBool(10) {
 this->setVariable("Ext", "ShiftWeight");
 } else if (Rand.NextBool(10) {
 this->setVariable("Ext", "PullAtColar");
 } else if (Rand.NextBool(10) {
 this->setVariable("Ext", "BridgeNose");
 } else {
 this->setVariable("Ext", Rand.Next(5) + 1 + "");
 }
 }

 bool updateUseKey() {
 if (GameServer.bServer) {
 return false;
 } else if (!this->isLocalPlayer()) {
 return false;
 } else if (this->PlayerIndex != 0) {
 return false;
 } else {
 this->timePressedContext = this->timePressedContext + GameTime.instance.getRealworldSecondsSinceLastUpdate();
 bool boolean0 = GameKeyboard.isKeyDown(Core.getInstance().getKey("Interact"));
 if (boolean0 && this->timePressedContext < 0.5F) {
 this->bPressContext = true;
 } else {
 if (this->bPressContext && (Core.CurrentTextEntryBox != nullptr && Core.CurrentTextEntryBox.DoingTextEntry || !GameKeyboard.doLuaKeyPressed) {
 this->bPressContext = false;
 }

 if (this->bPressContext && this->doContext(this->dir) {
 this->timePressedContext = 0.0F;
 this->bPressContext = false;
 return true;
 }

 if (!boolean0) {
 this->bPressContext = false;
 this->timePressedContext = 0.0F;
 }
 }

 return false;
 }
 }

 void updateHitByVehicle() {
 if (!GameServer.bServer) {
 if (this->isLocalPlayer()) {
 if (this->vehicle4testCollision != nullptr && this->ulBeatenVehicle.Check() && SandboxOptions.instance.DamageToPlayerFromHitByACar.getValue() > 1) {
 BaseVehicle vehicle = this->vehicle4testCollision;
 this->vehicle4testCollision = nullptr;
 if (vehicle.isEngineRunning() && this->getVehicle() != vehicle) {
 float float0 = vehicle.jniLinearVelocity.x;
 float float1 = vehicle.jniLinearVelocity.z;
 float float2 = (float)Math.sqrt(float0 * float0 + float1 * float1);
 Vector2 vector0 = BaseVehicle.TL_vector2_pool.get().alloc();
 Vector2 vector1 = vehicle.testCollisionWithCharacter(this, 0.20000002F, vector0);
 if (vector1 != nullptr && vector1.x != -1.0F) {
 vector1.x = (vector1.x - vehicle.x) * float2 * 1.0F + this->x;
 vector1.y = (vector1.y - vehicle.y) * float2 * 1.0F + this->x;
 if (this->isOnFloor()) {
 int int0 = vehicle.testCollisionWithProneCharacter(this, false);
 if (int0 > 0) {
 this->doBeatenVehicle(Math.max(float2 * 6.0F, 5.0F);
 }

 this->doBeatenVehicle(0.0F);
 } else if (this->getCurrentState() != PlayerFallDownState.instance() && float2 > 0.1F) {
 this->doBeatenVehicle(Math.max(float2 * 2.0F, 5.0F);
 }
 }

 BaseVehicle.TL_vector2_pool.get().release(vector0);
 }
 }
 }
 }
 }

 void updateSoundListener() {
 if (!GameServer.bServer) {
 if (this->isLocalPlayer()) {
 if (this->soundListener.empty()) {
 this->soundListener = (BaseSoundListener)(Core.SoundDisabled
 ? new DummySoundListener(this->PlayerIndex)
 : new SoundListener(this->PlayerIndex);
 }

 this->soundListener.setPos(this->x, this->y, this->z);
 this->checkNearbyRooms = this->checkNearbyRooms - GameTime.getInstance().getMultiplier() / 1.6F;
 if (this->checkNearbyRooms <= 0.0F) {
 this->checkNearbyRooms = 30.0F;
 this->numNearbyBuildingsRooms = IsoWorld.instance.MetaGrid.countNearbyBuildingsRooms(this);
 }

 if (this->testemitter.empty()) {
 this->testemitter = (BaseSoundEmitter)(Core.SoundDisabled ? std::make_unique<DummySoundEmitter>() : std::make_unique<FMODSoundEmitter>());
 this->testemitter.setPos(this->x, this->y, this->z);
 }

 this->soundListener.tick();
 this->testemitter.tick();
 }
 }
 }

 void updateMovementRates() {
 this->calculateWalkSpeed();
 this->m_idleSpeed = this->calculateIdleSpeed();
 this->updateFootInjuries();
 }

 void pressedAttack(bool calcAttackVars) {
 bool boolean0 = GameClient.bClient && !this->isLocalPlayer();
 bool boolean1 = this->isSprinting();
 this->setSprinting(false);
 this->setForceSprint(false);
 if (!this->attackStarted && !this->isCurrentState(PlayerHitReactionState.instance())) {
 if (!GameClient.bClient || !this->isCurrentState(PlayerHitReactionPVPState.instance()) || ServerOptions.instance.PVPMeleeWhileHitReaction.getValue()
 )
 {
 if (this->primaryHandModel != nullptr
 && !StringUtils.isNullOrEmpty(this->primaryHandModel.maskVariableValue)
 && this->secondaryHandModel != nullptr
 && !StringUtils.isNullOrEmpty(this->secondaryHandModel.maskVariableValue) {
 this->setDoShove(false);
 this->setForceShove(false);
 this->setInitiateAttack(false);
 this->attackStarted = false;
 this->setAttackType(nullptr);
 } else if (this->getPrimaryHandItem() != nullptr
 && this->getPrimaryHandItem().getItemReplacementPrimaryHand() != nullptr
 && this->getSecondaryHandItem() != nullptr
 && this->getSecondaryHandItem().getItemReplacementSecondHand() != nullptr) {
 this->setDoShove(false);
 this->setForceShove(false);
 this->setInitiateAttack(false);
 this->attackStarted = false;
 this->setAttackType(nullptr);
 } else {
 if (!this->attackStarted) {
 this->setVariable("StartedAttackWhileSprinting", boolean1);
 }

 this->setInitiateAttack(true);
 this->attackStarted = true;
 if (!boolean0) {
 this->setCriticalHit(false);
 }

 this->setAttackFromBehind(false);
 WeaponType weaponType = WeaponType.getWeaponType(this);
 if (!GameClient.bClient || this->isLocalPlayer()) {
 this->setAttackType(PZArrayUtil.pickRandom(weaponType.possibleAttack);
 }

 if (!GameClient.bClient || this->isLocalPlayer()) {
 this->combatSpeed = this->calculateCombatSpeed();
 }

 if (calcAttackVars) {
 SwipeStatePlayer.instance().CalcAttackVars(this, this->attackVars);
 }

 std::string string = this->getVariableString("Weapon");
 if (string != nullptr && string == "throwing") && !this->attackVars.bDoShove) {
 this->setAttackAnimThrowTimer(2000L);
 this->setIsAiming(true);
 }

 if (boolean0) {
 this->attackVars.bDoShove = this->isDoShove();
 this->attackVars.bAimAtFloor = this->isAimAtFloor();
 }

 if (this->attackVars.bDoShove && !this->isAuthorizeShoveStomp()) {
 this->setDoShove(false);
 this->setForceShove(false);
 this->setInitiateAttack(false);
 this->attackStarted = false;
 this->setAttackType(nullptr);
 } else {
 this->useHandWeapon = this->attackVars.getWeapon(this);
 this->setAimAtFloor(this->attackVars.bAimAtFloor);
 this->setDoShove(this->attackVars.bDoShove);
 this->targetOnGround = (IsoGameCharacter)this->attackVars.targetOnGround.getMovingObject();
 if (this->attackVars.getWeapon(this) != nullptr && !StringUtils.isNullOrEmpty(this->attackVars.getWeapon(this).getFireMode())) {
 this->setVariable("FireMode", this->attackVars.getWeapon(this).getFireMode());
 } else {
 this->clearVariable("FireMode");
 }

 if (this->useHandWeapon != nullptr && weaponType.isRanged && !this->bDoShove) {
 int int0 = this->useHandWeapon.getRecoilDelay();
 float float0 = int0 * (1.0F - this->getPerkLevel(PerkFactory.Perks.Aiming) / 30.0F);
 this->setRecoilDelay(float0.intValue());
 }

 int int1 = Rand.Next(0, 3);
 if (int1 == 0) {
 this->setVariable("AttackVariationX", Rand.Next(-1.0F, -0.5F);
 }

 if (int1 == 1) {
 this->setVariable("AttackVariationX", 0.0F);
 }

 if (int1 == 2) {
 this->setVariable("AttackVariationX", Rand.Next(0.5F, 1.0F);
 }

 this->setVariable("AttackVariationY", 0.0F);
 if (calcAttackVars) {
 SwipeStatePlayer.instance().CalcHitList(this, true, this->attackVars, this->hitList);
 }

 IsoGameCharacter character = nullptr;
 if (!this->hitList.empty()) {
 character = Type.tryCastTo(this->hitList.get(0).getObject(), IsoGameCharacter.class);
 }

 if (character.empty()) {
 if (this->isAiming() && !this->m_meleePressed && this->useHandWeapon != this->bareHands) {
 this->setDoShove(false);
 this->setForceShove(false);
 }

 this->m_lastAttackWasShove = this->bDoShove;
 if (weaponType.canMiss && !this->isAimAtFloor() && (!GameClient.bClient || this->isLocalPlayer())) {
 this->setAttackType("miss");
 }

 if (this->isAiming() && this->bDoShove) {
 this->setVariable("bShoveAiming", true);
 } else {
 this->clearVariable("bShoveAiming");
 }
 } else {
 if (!GameClient.bClient || this->isLocalPlayer()) {
 this->setAttackFromBehind(this->isBehind(character);
 }

 float float1 = IsoUtils.DistanceTo(character.x, character.y, this->x, this->y);
 this->setVariable("TargetDist", float1);
 int int2 = this->calculateCritChance(character);
 if (character instanceof IsoZombie) {
 IsoZombie zombie0 = this->getClosestZombieToOtherZombie((IsoZombie)character);
 if (!this->attackVars.bAimAtFloor
 && float1 > 1.25
 && weaponType == WeaponType.spear
 && (zombie0.empty() || IsoUtils.DistanceTo(character.x, character.y, zombie0.x, zombie0.y) > 1.7) {
 if (!GameClient.bClient || this->isLocalPlayer()) {
 this->setAttackType("overhead");
 }

 int2 += 30;
 }
 }

 if (this->isLocalPlayer() && !character.isOnFloor()) {
 character.setHitFromBehind(this->isAttackFromBehind());
 }

 if (this->isAttackFromBehind()) {
 if (character instanceof IsoZombie && ((IsoZombie)character).target.empty()) {
 int2 += 30;
 } else {
 int2 += 5;
 }
 }

 if (character instanceof IsoPlayer && weaponType.isRanged && !this->bDoShove) {
 int2 = (int)(this->attackVars.getWeapon(this).getStopPower() * (1.0F + this->getPerkLevel(PerkFactory.Perks.Aiming) / 15.0F);
 }

 if (!GameClient.bClient || this->isLocalPlayer()) {
 this->setCriticalHit(Rand.Next(100) < int2);
 if (DebugOptions.instance.MultiplayerCriticalHit.getValue()) {
 this->setCriticalHit(true);
 }

 if (this->isAttackFromBehind()
 && this->attackVars.bCloseKill
 && character instanceof IsoZombie
 && ((IsoZombie)character).target.empty()) {
 this->setCriticalHit(true);
 }

 if (this->isCriticalHit() && !this->attackVars.bCloseKill && !this->bDoShove && weaponType == WeaponType.knife) {
 this->setCriticalHit(false);
 }

 this->setAttackWasSuperAttack(false);
 if (this->stats.NumChasingZombies > 1 && this->attackVars.bCloseKill && !this->bDoShove && weaponType == WeaponType.knife) {
 this->setCriticalHit(false);
 }
 }

 if (this->isCriticalHit()) {
 this->combatSpeed *= 1.1F;
 }

 if (Core.bDebug) {
 DebugLog.Combat
 .debugln(
 "Hit zombie dist: "
 + float1
 + " crit: "
 + this->isCriticalHit()
 + " ("
 + int2
 + "%) from behind: "
 + this->isAttackFromBehind()
 );
 }

 if (this->isAiming() && this->bDoShove) {
 this->setVariable("bShoveAiming", true);
 } else {
 this->clearVariable("bShoveAiming");
 }

 if (this->useHandWeapon != nullptr && weaponType.isRanged) {
 this->setRecoilDelay(this->useHandWeapon.getRecoilDelay() - this->getPerkLevel(PerkFactory.Perks.Aiming) * 2);
 }

 this->m_lastAttackWasShove = this->bDoShove;
 }
 }
 }
 }
 }
 }

 void setAttackAnimThrowTimer(long dt) {
 this->AttackAnimThrowTimer = System.currentTimeMillis() + dt;
 }

 bool isAttackAnimThrowTimeOut() {
 return this->AttackAnimThrowTimer <= System.currentTimeMillis();
 }

 bool getAttackAnim() {
 return false;
 }

 std::string getWeaponType() {
 return !this->isAttackAnimThrowTimeOut() ? "throwing" : this->WeaponT;
 }

 void setWeaponType(const std::string& string) {
 this->WeaponT = string;
 }

 int calculateCritChance(IsoGameCharacter target) {
 if (this->bDoShove) {
 int int0 = 35;
 if (target instanceof IsoPlayer player0) {
 int0 = 20;
 if (GameClient.bClient && !player0.isLocalPlayer()) {
 int0 = (int)(int0 - player0.remoteStrLvl * 1.5);
 if (player0.getNutrition().getWeight() < 80.0) {
 int0 = (int)(int0 + Math.abs((player0.getNutrition().getWeight() - 80.0) / 2.0);
 } else {
 int0 = (int)(int0 - (player0.getNutrition().getWeight() - 80.0) / 2.0);
 }
 }
 }

 int0 -= this->getMoodles().getMoodleLevel(MoodleType.Endurance) * 5;
 int0 -= this->getMoodles().getMoodleLevel(MoodleType.HeavyLoad) * 5;
 int0 = (int)(int0 - this->getMoodles().getMoodleLevel(MoodleType.Panic) * 1.3);
 return int0 + this->getPerkLevel(PerkFactory.Perks.Strength) * 2;
 } else if (this->bDoShove && target.getStateMachine().getCurrent() == StaggerBackState.instance() && target instanceof IsoZombie) {
 return 100;
 } else if (this->getPrimaryHandItem() != nullptr && this->getPrimaryHandItem() instanceof HandWeapon) {
 HandWeapon weapon = (HandWeapon)this->getPrimaryHandItem();
 int int1 = (int)weapon.getCriticalChance();
 if (weapon.isAlwaysKnockdown()) {
 return 100;
 } else {
 WeaponType weaponType = WeaponType.getWeaponType(this);
 if (weaponType.isRanged) {
 int1 = (int)(int1 + weapon.getAimingPerkCritModifier() * (this->getPerkLevel(PerkFactory.Perks.Aiming) / 2.0F);
 if (this->getBeenMovingFor() > weapon.getAimingTime() + this->getPerkLevel(PerkFactory.Perks.Aiming) * 2) {
 int1 = (int)(int1 - (this->getBeenMovingFor() - (weapon.getAimingTime() + this->getPerkLevel(PerkFactory.Perks.Aiming) * 2);
 }

 int1 += this->getPerkLevel(PerkFactory.Perks.Aiming) * 3;
 float float0 = this->DistToProper(target);
 if (float0 < 4.0F) {
 int1 = (int)(int1 + (4.0F - float0) * 7.0F);
 } else if (float0 >= 4.0F) {
 int1 = (int)(int1 - (float0 - 4.0F) * 7.0F);
 }

 if ("Auto" == this->getVariableString("FireMode"))) {
 int1 -= this->shootInARow * 10;
 }
 } else {
 if (weapon.isTwoHandWeapon() && (this->getPrimaryHandItem() != weapon || this->getSecondaryHandItem() != weapon) {
 int1 -= int1 / 3;
 }

 if (this->chargeTime < 2.0F) {
 int1 -= int1 / 5;
 }

 int int2 = this->getPerkLevel(PerkFactory.Perks.Blunt);
 if (weapon.getCategories().contains("Axe")) {
 int2 = this->getPerkLevel(PerkFactory.Perks.Axe);
 }

 if (weapon.getCategories().contains("LongBlade")) {
 int2 = this->getPerkLevel(PerkFactory.Perks.LongBlade);
 }

 if (weapon.getCategories().contains("Spear")) {
 int2 = this->getPerkLevel(PerkFactory.Perks.Spear);
 }

 if (weapon.getCategories().contains("SmallBlade")) {
 int2 = this->getPerkLevel(PerkFactory.Perks.SmallBlade);
 }

 if (weapon.getCategories().contains("SmallBlunt")) {
 int2 = this->getPerkLevel(PerkFactory.Perks.SmallBlunt);
 }

 int1 += int2 * 3;
 if (target instanceof IsoPlayer player1 && GameClient.bClient && !player1.isLocalPlayer()) {
 int1 = (int)(int1 - player1.remoteStrLvl * 1.5);
 if (player1.getNutrition().getWeight() < 80.0) {
 int1 = (int)(int1 + Math.abs((player1.getNutrition().getWeight() - 80.0) / 2.0);
 } else {
 int1 = (int)(int1 - (player1.getNutrition().getWeight() - 80.0) / 2.0);
 }
 }
 }

 int1 -= this->getMoodles().getMoodleLevel(MoodleType.Endurance) * 5;
 int1 -= this->getMoodles().getMoodleLevel(MoodleType.HeavyLoad) * 5;
 int1 = (int)(int1 - this->getMoodles().getMoodleLevel(MoodleType.Panic) * 1.3);
 if (SandboxOptions.instance.Lore.Toughness.getValue() == 1) {
 int1 -= 6;
 }

 if (SandboxOptions.instance.Lore.Toughness.getValue() == 3) {
 int1 += 6;
 }

 if (int1 < 10) {
 int1 = 10;
 }

 if (int1 > 90) {
 int1 = 90;
 }

 return int1;
 }
 } else {
 return 0;
 }
 }

 void checkJoypadIgnoreAimUntilCentered() {
 if (this->bJoypadIgnoreAimUntilCentered) {
 if (GameWindow.ActivatedJoyPad != nullptr && this->JoypadBind != -1 && this->bJoypadMovementActive) {
 float float0 = JoypadManager.instance.getAimingAxisX(this->JoypadBind);
 float float1 = JoypadManager.instance.getAimingAxisY(this->JoypadBind);
 if (float0 * float0 + float1 + float1 <= 0.0F) {
 this->bJoypadIgnoreAimUntilCentered = false;
 }
 }
 }
 }

 bool isAimControlActive() {
 if (this->isForceAim()) {
 return true;
 } else {
 return this->isAimKeyDown()
 ? true
 : GameWindow.ActivatedJoyPad != nullptr
 && this->JoypadBind != -1
 && this->bJoypadMovementActive
 && this->getJoypadAimVector(tempo).getLengthSquared() > 0.0F;
 }
 }

 Vector2 getJoypadAimVector(Vector2 vector) {
 if (this->bJoypadIgnoreAimUntilCentered) {
 return vector.set(0.0F, 0.0F);
 } else {
 float float0 = JoypadManager.instance.getAimingAxisY(this->JoypadBind);
 float float1 = JoypadManager.instance.getAimingAxisX(this->JoypadBind);
 float float2 = JoypadManager.instance.getDeadZone(this->JoypadBind, 0);
 if (float1 * float1 + float0 * float0 < float2 * float2) {
 float0 = 0.0F;
 float1 = 0.0F;
 }

 return vector.set(float1, float0);
 }
 }

 Vector2 getJoypadMoveVector(Vector2 vector) {
 float float0 = JoypadManager.instance.getMovementAxisY(this->JoypadBind);
 float float1 = JoypadManager.instance.getMovementAxisX(this->JoypadBind);
 float float2 = JoypadManager.instance.getDeadZone(this->JoypadBind, 0);
 if (float1 * float1 + float0 * float0 < float2 * float2) {
 float0 = 0.0F;
 float1 = 0.0F;
 }

 vector.set(float1, float0);
 if (this->isIgnoreInputsForDirection()) {
 vector.set(0.0F, 0.0F);
 }

 return vector;
 }

 void updateToggleToAim() {
 if (this->PlayerIndex == 0) {
 if (!Core.getInstance().isToggleToAim()) {
 this->setForceAim(false);
 } else {
 bool boolean0 = this->isAimKeyDown();
 long long0 = System.currentTimeMillis();
 if (boolean0) {
 if (this->aimKeyDownMS == 0L) {
 this->aimKeyDownMS = long0;
 }
 } else {
 if (this->aimKeyDownMS != 0L && long0 - this->aimKeyDownMS < 500L) {
 this->toggleForceAim();
 } else if (this->isForceAim()) {
 if (this->aimKeyDownMS != 0L) {
 this->toggleForceAim();
 } else {
 int int0 = Core.getInstance().getKey("Aim");
 bool boolean1 = int0 == 29 || int0 == 157;
 if (boolean1 && UIManager.isMouseOverInventory()) {
 this->toggleForceAim();
 }
 }
 }

 this->aimKeyDownMS = 0L;
 }
 }
 }
 }

 void UpdateInputState(IsoPlayer.InputState inputStatex) {
 inputStatex.bMelee = false;
 if (!MPDebugAI.updateInputState(this, inputStatex) {
 if (GameWindow.ActivatedJoyPad != nullptr && this->JoypadBind != -1) {
 if (this->bJoypadMovementActive) {
 inputStatex.isAttacking = this->isCharging;
 if (this->bJoypadIgnoreChargingRT) {
 inputStatex.isAttacking = false;
 }

 if (this->bJoypadIgnoreAimUntilCentered) {
 float float0 = JoypadManager.instance.getAimingAxisX(this->JoypadBind);
 float float1 = JoypadManager.instance.getAimingAxisY(this->JoypadBind);
 if (float0 == 0.0F && float1 == 0.0F) {
 this->bJoypadIgnoreAimUntilCentered = false;
 }
 }
 }

 if (this->isChargingLT) {
 inputStatex.bMelee = true;
 inputStatex.isAttacking = false;
 }
 } else {
 inputStatex.isAttacking = this->isCharging && Mouse.isButtonDownUICheck(0);
 if (GameKeyboard.isKeyDown(Core.getInstance().getKey("Melee")) && this->authorizeMeleeAction) {
 inputStatex.bMelee = true;
 inputStatex.isAttacking = false;
 }
 }

 if (GameWindow.ActivatedJoyPad != nullptr && this->JoypadBind != -1) {
 if (this->bJoypadMovementActive) {
 inputStatex.isCharging = JoypadManager.instance.isRTPressed(this->JoypadBind);
 inputStatex.isChargingLT = JoypadManager.instance.isLTPressed(this->JoypadBind);
 if (this->bJoypadIgnoreChargingRT && !inputStatex.isCharging) {
 this->bJoypadIgnoreChargingRT = false;
 }
 }

 inputStatex.isAiming = false;
 inputStatex.bRunning = false;
 inputStatex.bSprinting = false;
 Vector2 vector0 = this->getJoypadAimVector(tempVector2);
 if (vector0.x == 0.0F && vector0.y == 0.0F) {
 inputStatex.isCharging = false;
 Vector2 vector1 = this->getJoypadMoveVector(tempVector2);
 if (this->isAutoWalk() && vector1.getLengthSquared() == 0.0F) {
 vector1.set(this->getAutoWalkDirection());
 }

 if (vector1.x != 0.0F || vector1.y != 0.0F) {
 if (this->isAllowRun()) {
 inputStatex.bRunning = JoypadManager.instance.isRTPressed(this->JoypadBind);
 }

 inputStatex.isAttacking = false;
 inputStatex.bMelee = false;
 this->bJoypadIgnoreChargingRT = true;
 inputStatex.isCharging = false;
 bool boolean0 = JoypadManager.instance.isBPressed(this->JoypadBind);
 if (inputStatex.bRunning && boolean0 && !this->bJoypadBDown) {
 this->bJoypadSprint = !this->bJoypadSprint;
 }

 this->bJoypadBDown = boolean0;
 inputStatex.bSprinting = this->bJoypadSprint;
 }
 } else {
 inputStatex.isAiming = true;
 }

 if (!inputStatex.bRunning) {
 this->bJoypadBDown = false;
 this->bJoypadSprint = false;
 }
 } else {
 inputStatex.isAiming = (this->isAimKeyDown() || Mouse.isButtonDownUICheck(1) && this->TimeRightPressed >= 0.15F)
 && this->getPlayerNum() == 0
 && StringUtils.isNullOrEmpty(this->getVariableString("BumpFallType"));
 if (Mouse.isButtonDown(1) {
 this->TimeRightPressed = this->TimeRightPressed + GameTime.getInstance().getRealworldSecondsSinceLastUpdate();
 } else {
 this->TimeRightPressed = 0.0F;
 }

 if (!this->isCharging) {
 inputStatex.isCharging = Mouse.isButtonDownUICheck(1) && this->TimeRightPressed >= 0.15F || this->isAimKeyDown();
 } else {
 inputStatex.isCharging = Mouse.isButtonDown(1) || this->isAimKeyDown();
 }

 int int0 = Core.getInstance().getKey("Run");
 int int1 = Core.getInstance().getKey("Sprint");
 if (this->isAllowRun()) {
 inputStatex.bRunning = GameKeyboard.isKeyDown(int0);
 }

 if (this->isAllowSprint()) {
 if (!Core.OptiondblTapJogToSprint) {
 if (GameKeyboard.isKeyDown(int1) {
 inputStatex.bSprinting = true;
 this->pressedRunTimer = 1.0F;
 } else {
 inputStatex.bSprinting = false;
 }
 } else {
 if (!GameKeyboard.wasKeyDown(int0) && GameKeyboard.isKeyDown(int0) && this->pressedRunTimer < 30.0F && this->pressedRun) {
 inputStatex.bSprinting = true;
 }

 if (GameKeyboard.wasKeyDown(int0) && !GameKeyboard.isKeyDown(int0) {
 inputStatex.bSprinting = false;
 this->pressedRun = true;
 }

 if (!inputStatex.bRunning) {
 inputStatex.bSprinting = false;
 }

 if (this->pressedRun) {
 this->pressedRunTimer++;
 }

 if (this->pressedRunTimer > 30.0F) {
 this->pressedRunTimer = 0.0F;
 this->pressedRun = false;
 }
 }
 }

 this->updateToggleToAim();
 if (inputStatex.bRunning || inputStatex.bSprinting) {
 this->setForceAim(false);
 }

 if (this->PlayerIndex == 0 && Core.getInstance().isToggleToRun()) {
 bool boolean1 = GameKeyboard.isKeyDown(int0);
 bool boolean2 = GameKeyboard.wasKeyDown(int0);
 long long0 = System.currentTimeMillis();
 if (boolean1 && !boolean2) {
 this->runKeyDownMS = long0;
 } else if (!boolean1 && boolean2 && long0 - this->runKeyDownMS < 500L) {
 this->toggleForceRun();
 }
 }

 if (this->PlayerIndex == 0 && Core.getInstance().isToggleToSprint()) {
 bool boolean3 = GameKeyboard.isKeyDown(int1);
 bool boolean4 = GameKeyboard.wasKeyDown(int1);
 long long1 = System.currentTimeMillis();
 if (boolean3 && !boolean4) {
 this->sprintKeyDownMS = long1;
 } else if (!boolean3 && boolean4 && long1 - this->sprintKeyDownMS < 500L) {
 this->toggleForceSprint();
 }
 }

 if (this->isForceAim()) {
 inputStatex.isAiming = true;
 inputStatex.isCharging = true;
 }

 if (this->isForceRun()) {
 inputStatex.bRunning = true;
 }

 if (this->isForceSprint()) {
 inputStatex.bSprinting = true;
 }
 }
 }
 }

 IsoZombie getClosestZombieToOtherZombie(IsoZombie closestTo) {
 IsoZombie zombie0 = nullptr;
 std::vector arrayList0 = new ArrayList();
 std::vector arrayList1 = IsoWorld.instance.CurrentCell.getObjectList();

 for (int int0 = 0; int0 < arrayList1.size(); int0++) {
 IsoMovingObject movingObject = (IsoMovingObject)arrayList1.get(int0);
 if (movingObject != closestTo && movingObject instanceof IsoZombie) {
 arrayList0.add((IsoZombie)movingObject);
 }
 }

 float float0 = 0.0F;

 for (int int1 = 0; int1 < arrayList0.size(); int1++) {
 IsoZombie zombie1 = (IsoZombie)arrayList0.get(int1);
 float float1 = IsoUtils.DistanceTo(zombie1.x, zombie1.y, closestTo.x, closestTo.y);
 if (zombie0.empty() || float1 < float0) {
 zombie0 = zombie1;
 float0 = float1;
 }
 }

 return zombie0;
 }

 IsoGameCharacter getClosestZombieDist() {
 float float0 = 0.4F;
 bool boolean0 = false;
 testHitPosition.x = this->x + this->getForwardDirection().x * float0;
 testHitPosition.y = this->y + this->getForwardDirection().y * float0;
 HandWeapon weapon = this->getWeapon();
 std::vector arrayList = new ArrayList();

 for (int int0 = (int)testHitPosition.x - (int)weapon.getMaxRange(); int0 <= (int)testHitPosition.x + (int)weapon.getMaxRange(); int0++) {
 for (int int1 = (int)testHitPosition.y - (int)weapon.getMaxRange(); int1 <= (int)testHitPosition.y + (int)weapon.getMaxRange(); int1++) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare((double)int0, (double)int1, (double)this->z);
 if (square != nullptr && square.getMovingObjects().size() > 0) {
 for (int int2 = 0; int2 < square.getMovingObjects().size(); int2++) {
 IsoMovingObject movingObject = square.getMovingObjects().get(int2);
 if (movingObject instanceof IsoZombie) {
 Vector2 vector0 = tempVector2_1.set(this->getX(), this->getY());
 Vector2 vector1 = tempVector2_2.set(movingObject.getX(), movingObject.getY());
 vector1.x = vector1.x - vector0.x;
 vector1.y = vector1.y - vector0.y;
 Vector2 vector2 = this->getForwardDirection();
 vector1.normalize();
 vector2.normalize();
 float float1 = vector1.dot(vector2);
 if (float1 >= weapon.getMinAngle() || movingObject.isOnFloor()) {
 boolean0 = true;
 }

 if (boolean0 && ((IsoZombie)movingObject).Health > 0.0F) {
 ((IsoZombie)movingObject).setHitFromBehind(this->isBehind((IsoZombie)movingObject);
 ((IsoZombie)movingObject).setHitAngle(((IsoZombie)movingObject).getForwardDirection());
 ((IsoZombie)movingObject).setPlayerAttackPosition(((IsoZombie)movingObject).testDotSide(this);
 float float2 = IsoUtils.DistanceTo(movingObject.x, movingObject.y, this->x, this->y);
 if (float2 < weapon.getMaxRange()) {
 arrayList.add((IsoZombie)movingObject);
 }
 }
 }
 }
 }
 }
 }

 if (!arrayList.empty()) {
 Collections.sort(arrayList, std::make_unique<Comparator<IsoGameCharacter>>() {
 int compare(IsoGameCharacter character0, IsoGameCharacter character1) {
 float float0x = IsoUtils.DistanceTo(character0.x, character0.y, IsoPlayer.testHitPosition.x, IsoPlayer.testHitPosition.y);
 float float1x = IsoUtils.DistanceTo(character1.x, character1.y, IsoPlayer.testHitPosition.x, IsoPlayer.testHitPosition.y);
 if (float0x > float1x) {
 return 1;
 } else {
 return float1x > float0x ? -1 : 0;
 }
 }
 });
 return (IsoGameCharacter)arrayList.get(0);
 } else {
 return nullptr;
 }
 }

 void hitConsequences(HandWeapon weapon, IsoGameCharacter wielder, bool bIgnoreDamage, float damage, bool _bRemote) {
 std::string string0 = wielder.getVariableString("ZombieHitReaction");
 if ("Shot" == string0) {
 wielder.setCriticalHit(Rand.Next(100) < ((IsoPlayer)wielder).calculateCritChance(this);
 }

 if (wielder instanceof IsoPlayer && (GameServer.bServer || GameClient.bClient) {
 if (ServerOptions.getInstance().KnockedDownAllowed.getValue()) {
 this->setKnockedDown(wielder.isCriticalHit());
 }
 } else {
 this->setKnockedDown(wielder.isCriticalHit());
 }

 if (wielder instanceof IsoPlayer) {
 if (!StringUtils.isNullOrEmpty(this->getHitReaction())) {
 this->actionContext.reportEvent("washitpvpagain");
 }

 this->actionContext.reportEvent("washitpvp");
 this->setVariable("hitpvp", true);
 } else {
 this->actionContext.reportEvent("washit");
 }

 if (bIgnoreDamage) {
 if (!GameServer.bServer) {
 wielder.xp.AddXP(PerkFactory.Perks.Strength, 2.0F);
 this->setHitForce(Math.min(0.5F, this->getHitForce()));
 this->setHitReaction("HitReaction");
 std::string string1 = this->testDotSide(wielder);
 this->setHitFromBehind("BEHIND" == string1);
 }
 } else {
 if (GameServer.bServer || GameClient.bClient && !this->isLocalPlayer()) {
 if (!GameServer.bServer && !this->isLocalPlayer()) {
 this->BodyDamage.splatBloodFloorBig();
 }
 } else {
 this->BodyDamage.DamageFromWeapon(weapon);
 }

 if ("Bite" == string0) {
 std::string string2 = this->testDotSide(wielder);
 bool boolean0 = string2.equals("FRONT");
 bool boolean1 = string2.equals("BEHIND");
 if (string2 == "RIGHT")) {
 string0 = string0 + "LEFT";
 }

 if (string2 == "LEFT")) {
 string0 = string0 + "RIGHT";
 }

 if (string0 != nullptr && !"" == string0) {
 this->setHitReaction(string0);
 }
 } else if (!this->isKnockedDown()) {
 this->setHitReaction("HitReaction");
 }
 }
 }

 HandWeapon getWeapon() {
 if (this->getPrimaryHandItem() instanceof HandWeapon) {
 return (HandWeapon)this->getPrimaryHandItem();
 } else {
 return this->getSecondaryHandItem() instanceof HandWeapon
 ? (HandWeapon)this->getSecondaryHandItem()
 : (HandWeapon)InventoryItemFactory.CreateItem("BareHands");
 }
 }

 void updateMechanicsItems() {
 if (!GameServer.bServer && !this->mechanicsItem.empty()) {
 Iterator iterator = this->mechanicsItem.keySet().iterator();
 std::vector arrayList = new ArrayList();

 while (iterator.hasNext()) {
 long long0 = (Long)iterator.next();
 long long1 = this->mechanicsItem.get(long0);
 if (GameTime.getInstance().getCalender().getTimeInMillis() > long1 + 86400000L) {
 arrayList.add(long0);
 }
 }

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 this->mechanicsItem.remove(arrayList.get(int0);
 }
 }
 }

 void enterExitVehicle() {
 bool boolean0 = this->PlayerIndex == 0 && GameKeyboard.isKeyDown(Core.getInstance().getKey("Interact"));
 if (boolean0) {
 this->bUseVehicle = true;
 this->useVehicleDuration = this->useVehicleDuration + GameTime.instance.getRealworldSecondsSinceLastUpdate();
 }

 if (!this->bUsedVehicle && this->bUseVehicle && (!boolean0 || this->useVehicleDuration > 0.5F) {
 this->bUsedVehicle = true;
 if (this->getVehicle() != nullptr) {
 LuaEventManager.triggerEvent("OnUseVehicle", this, this->getVehicle(), this->useVehicleDuration > 0.5F);
 } else {
 for (int int0 = 0; int0 < this->getCell().vehicles.size(); int0++) {
 BaseVehicle vehicle = this->getCell().vehicles.get(int0);
 if (vehicle.getUseablePart(this) != nullptr) {
 LuaEventManager.triggerEvent("OnUseVehicle", this, vehicle, this->useVehicleDuration > 0.5F);
 break;
 }
 }
 }
 }

 if (!boolean0) {
 this->bUseVehicle = false;
 this->bUsedVehicle = false;
 this->useVehicleDuration = 0.0F;
 }
 }

 void checkActionGroup() {
 ActionGroup actionGroup0 = this->actionContext.getGroup();
 if (this->getVehicle() == nullptr) {
 ActionGroup actionGroup1 = ActionGroup.getActionGroup("player");
 if (actionGroup0 != actionGroup1) {
 this->advancedAnimator.OnAnimDataChanged(false);
 this->initializeStates();
 this->actionContext.setGroup(actionGroup1);
 this->clearVariable("bEnteringVehicle");
 this->clearVariable("EnterAnimationFinished");
 this->clearVariable("bExitingVehicle");
 this->clearVariable("ExitAnimationFinished");
 this->clearVariable("bSwitchingSeat");
 this->clearVariable("SwitchSeatAnimationFinished");
 this->setHitReaction("");
 }
 } else {
 ActionGroup actionGroup2 = ActionGroup.getActionGroup("player-vehicle");
 if (actionGroup0 != actionGroup2) {
 this->advancedAnimator.OnAnimDataChanged(false);
 this->initializeStates();
 this->actionContext.setGroup(actionGroup2);
 }
 }
 }

 BaseVehicle getUseableVehicle() {
 if (this->getVehicle() != nullptr) {
 return nullptr;
 } else {
 int int0 = ((int)this->x - 4) / 10 - 1;
 int int1 = ((int)this->y - 4) / 10 - 1;
 int int2 = (int)Math.ceil((this->x + 4.0F) / 10.0F) + 1;
 int int3 = (int)Math.ceil((this->y + 4.0F) / 10.0F) + 1;

 for (int int4 = int1; int4 < int3; int4++) {
 for (int int5 = int0; int5 < int2; int5++) {
 IsoChunk chunk = GameServer.bServer
 ? ServerMap.instance.getChunk(int5, int4)
 : IsoWorld.instance.CurrentCell.getChunkForGridSquare(int5 * 10, int4 * 10, 0);
 if (chunk != nullptr) {
 for (int int6 = 0; int6 < chunk.vehicles.size(); int6++) {
 BaseVehicle vehicle = chunk.vehicles.get(int6);
 if (vehicle.getUseablePart(this) != nullptr || vehicle.getBestSeat(this) != -1) {
 return vehicle;
 }
 }
 }
 }
 }

 return nullptr;
 }
 }

 bool isNearVehicle() {
 if (this->getVehicle() != nullptr) {
 return false;
 } else {
 int int0 = ((int)this->x - 4) / 10 - 1;
 int int1 = ((int)this->y - 4) / 10 - 1;
 int int2 = (int)Math.ceil((this->x + 4.0F) / 10.0F) + 1;
 int int3 = (int)Math.ceil((this->y + 4.0F) / 10.0F) + 1;

 for (int int4 = int1; int4 < int3; int4++) {
 for (int int5 = int0; int5 < int2; int5++) {
 IsoChunk chunk = GameServer.bServer
 ? ServerMap.instance.getChunk(int5, int4)
 : IsoWorld.instance.CurrentCell.getChunkForGridSquare(int5 * 10, int4 * 10, 0);
 if (chunk != nullptr) {
 for (int int6 = 0; int6 < chunk.vehicles.size(); int6++) {
 BaseVehicle vehicle = chunk.vehicles.get(int6);
 if (vehicle.getScript() != nullptr && vehicle.DistTo(this) < 3.5) {
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
 if (this->getVehicle() != nullptr) {
 return nullptr;
 } else {
 int int0 = ((int)this->x - 4) / 10 - 1;
 int int1 = ((int)this->y - 4) / 10 - 1;
 int int2 = (int)Math.ceil((this->x + 4.0F) / 10.0F) + 1;
 int int3 = (int)Math.ceil((this->y + 4.0F) / 10.0F) + 1;

 for (int int4 = int1; int4 < int3; int4++) {
 for (int int5 = int0; int5 < int2; int5++) {
 IsoChunk chunk = GameServer.bServer ? ServerMap.instance.getChunk(int5, int4) : IsoWorld.instance.CurrentCell.getChunk(int5, int4);
 if (chunk != nullptr) {
 for (int int6 = 0; int6 < chunk.vehicles.size(); int6++) {
 BaseVehicle vehicle = chunk.vehicles.get(int6);
 if (vehicle.getScript() != nullptr
 && (int)this->getZ() == (int)vehicle.getZ()
 && (!this->isLocalPlayer() || vehicle.getTargetAlpha(this->PlayerIndex) != 0.0F)
 && !(this->DistToSquared((int)vehicle.x, (int)vehicle.y) >= 16.0F)
 && PolygonalMap2.instance
 .intersectLineWithVehicle(
 this->x,
 this->y,
 this->x + this->getForwardDirection().x * 4.0F,
 this->y + this->getForwardDirection().y * 4.0F,
 vehicle,
 tempVector2
 )
 && !PolygonalMap2.instance.lineClearCollide(this->x, this->y, tempVector2.x, tempVector2.y, (int)this->z, vehicle, false, true) {
 return vehicle;
 }
 }
 }
 }
 }

 return nullptr;
 }
 }

 void updateWhileInVehicle() {
 this->bLookingWhileInVehicle = false;
 ActionGroup actionGroup0 = this->actionContext.getGroup();
 ActionGroup actionGroup1 = ActionGroup.getActionGroup("player-vehicle");
 if (actionGroup0 != actionGroup1) {
 this->advancedAnimator.OnAnimDataChanged(false);
 this->initializeStates();
 this->actionContext.setGroup(actionGroup1);
 }

 if (GameClient.bClient && this->getVehicle().getSeat(this) == -1) {
 DebugLog.log("forced " + this->getUsername() + " out of vehicle seat -1");
 this->setVehicle(nullptr);
 } else {
 this->dirtyRecalcGridStackTime = 10.0F;
 if (this->getVehicle().isDriver(this) {
 this->getVehicle().updatePhysics();
 bool boolean0 = true;
 if (this->isAiming()) {
 WeaponType weaponType = WeaponType.getWeaponType(this);
 if (weaponType == WeaponType.firearm) {
 boolean0 = false;
 }
 }

 if (this->getVariableBoolean("isLoading")) {
 boolean0 = false;
 }

 if (boolean0) {
 this->getVehicle().updateControls();
 }
 } else {
 BaseVehicle vehicle = this->getVehicle();
 if (vehicle.getDriver() == nullptr && vehicle.engineSpeed > vehicle.getScript().getEngineIdleSpeed()) {
 vehicle.engineSpeed = Math.max(
 vehicle.engineSpeed - 50.0F * (GameTime.getInstance().getMultiplier() / 0.8F), (double)vehicle.getScript().getEngineIdleSpeed()
 );
 }

 if (GameClient.connection != nullptr) {
 PassengerMap.updatePassenger(this);
 }
 }

 this->fallTime = 0.0F;
 this->bSeenThisFrame = false;
 this->bCouldBeSeenThisFrame = false;
 this->closestZombie = 1000000.0F;
 this->setBeenMovingFor(this->getBeenMovingFor() - 0.625F * GameTime.getInstance().getMultiplier());
 if (!this->Asleep) {
 float float0 = (float)ZomboidGlobals.SittingEnduranceMultiplier;
 float0 *= 1.0F - this->stats.fatigue;
 float0 *= GameTime.instance.getMultiplier();
 this->stats.endurance = (float)(
 this->stats.endurance
 + ZomboidGlobals.ImobileEnduranceReduce * SandboxOptions.instance.getEnduranceRegenMultiplier() * this->getRecoveryMod() * float0
 );
 this->stats.endurance = PZMath.clamp(this->stats.endurance, 0.0F, 1.0F);
 }

 this->updateToggleToAim();
 if (this->vehicle != nullptr) {
 Vector3f vector3f = this->vehicle.getForwardVector(tempVector3f);
 bool boolean1 = this->isAimControlActive();
 if (this->PlayerIndex == 0) {
 if (Mouse.isButtonDown(1) {
 this->TimeRightPressed = this->TimeRightPressed + GameTime.getInstance().getRealworldSecondsSinceLastUpdate();
 } else {
 this->TimeRightPressed = 0.0F;
 }

 boolean1 |= Mouse.isButtonDownUICheck(1) && this->TimeRightPressed >= 0.15F;
 }

 if (!boolean1 && this->isCurrentState(IdleState.instance())) {
 this->setForwardDirection(vector3f.x, vector3f.z);
 this->getForwardDirection().normalize();
 }

 if (this->lastAngle.x != this->getForwardDirection().x || this->lastAngle.y != this->getForwardDirection().y) {
 this->dirtyRecalcGridStackTime = 10.0F;
 }

 this->DirectionFromVector(this->getForwardDirection());
 AnimationPlayer animationPlayer = this->getAnimationPlayer();
 if (animationPlayer != nullptr && animationPlayer.isReady()) {
 animationPlayer.SetForceDir(this->getForwardDirection());
 float float1 = animationPlayer.getAngle() + animationPlayer.getTwistAngle();
 this->dir = IsoDirections.fromAngle(tempVector2.setLengthAndDirection(float1, 1.0F);
 }

 bool boolean2 = false;
 int int0 = this->vehicle.getSeat(this);
 VehiclePart part = this->vehicle.getPassengerDoor(int0);
 if (part != nullptr) {
 VehicleWindow vehicleWindow = part.findWindow();
 if (vehicleWindow != nullptr && !vehicleWindow.isHittable()) {
 boolean2 = true;
 }
 }

 if (boolean2) {
 this->attackWhileInVehicle();
 } else if (boolean1) {
 this->bLookingWhileInVehicle = true;
 this->setAngleFromAim();
 } else {
 this->checkJoypadIgnoreAimUntilCentered();
 this->setIsAiming(false);
 }
 }

 this->updateCursorVisibility();
 }
 }

 void attackWhileInVehicle() {
 this->setIsAiming(false);
 bool boolean0 = false;
 bool boolean1 = false;
 if (GameWindow.ActivatedJoyPad != nullptr && this->JoypadBind != -1) {
 if (!this->bJoypadMovementActive) {
 return;
 }

 if (this->isChargingLT && !JoypadManager.instance.isLTPressed(this->JoypadBind) {
 boolean1 = true;
 } else {
 boolean0 = this->isCharging && !JoypadManager.instance.isRTPressed(this->JoypadBind);
 }

 float float0 = JoypadManager.instance.getAimingAxisX(this->JoypadBind);
 float float1 = JoypadManager.instance.getAimingAxisY(this->JoypadBind);
 if (this->bJoypadIgnoreAimUntilCentered) {
 if (float0 == 0.0F && float1 == 0.0F) {
 this->bJoypadIgnoreAimUntilCentered = false;
 } else {
 float1 = 0.0F;
 float0 = 0.0F;
 }
 }

 this->setIsAiming(float0 * float0 + float1 * float1 >= 0.09F);
 this->isCharging = this->isAiming() && JoypadManager.instance.isRTPressed(this->JoypadBind);
 this->isChargingLT = this->isAiming() && JoypadManager.instance.isLTPressed(this->JoypadBind);
 } else {
 bool boolean2 = this->isAimKeyDown();
 this->setIsAiming(boolean2 || Mouse.isButtonDownUICheck(1) && this->TimeRightPressed >= 0.15F);
 if (this->isCharging) {
 this->isCharging = boolean2 || Mouse.isButtonDown(1);
 } else {
 this->isCharging = boolean2 || Mouse.isButtonDownUICheck(1) && this->TimeRightPressed >= 0.15F;
 }

 if (this->isForceAim()) {
 this->setIsAiming(true);
 this->isCharging = true;
 }

 if (GameKeyboard.isKeyDown(Core.getInstance().getKey("Melee")) && this->authorizeMeleeAction) {
 boolean1 = true;
 } else {
 boolean0 = this->isCharging && Mouse.isButtonDownUICheck(0);
 if (boolean0) {
 this->setIsAiming(true);
 }
 }
 }

 if (!this->isCharging && !this->isChargingLT) {
 this->chargeTime = 0.0F;
 }

 if (this->isAiming() && !this->bBannedAttacking && this->CanAttack()) {
 this->chargeTime = this->chargeTime + GameTime.instance.getMultiplier();
 this->useChargeTime = this->chargeTime;
 this->m_meleePressed = boolean1;
 this->setAngleFromAim();
 if (boolean1) {
 this->sprite.Animate = true;
 this->setDoShove(true);
 this->AttemptAttack(this->useChargeTime);
 this->useChargeTime = 0.0F;
 this->chargeTime = 0.0F;
 } else if (boolean0) {
 this->sprite.Animate = true;
 if (this->getRecoilDelay() <= 0.0F) {
 this->AttemptAttack(this->useChargeTime);
 }

 this->useChargeTime = 0.0F;
 this->chargeTime = 0.0F;
 }
 }
 }

 void setAngleFromAim() {
 Vector2 vector = tempVector2;
 if (GameWindow.ActivatedJoyPad != nullptr && this->JoypadBind != -1) {
 this->getControllerAimDir(vector);
 } else {
 vector.set(this->getX(), this->getY());
 int int0 = Mouse.getX();
 int int1 = Mouse.getY();
 vector.x = vector.x - IsoUtils.XToIso(int0, int1 + 55.0F * this->def.getScaleY(), this->getZ());
 vector.y = vector.y - IsoUtils.YToIso(int0, int1 + 55.0F * this->def.getScaleY(), this->getZ());
 vector.x = -vector.x;
 vector.y = -vector.y;
 }

 if (vector.getLengthSquared() > 0.0F) {
 vector.normalize();
 this->DirectionFromVector(vector);
 this->setForwardDirection(vector);
 if (this->lastAngle.x != vector.x || this->lastAngle.y != vector.y) {
 this->lastAngle.x = vector.x;
 this->lastAngle.y = vector.y;
 this->dirtyRecalcGridStackTime = 10.0F;
 }
 }
 }

 void updateTorchStrength() {
 if (this->getTorchStrength() > 0.0F || this->flickTorch) {
 DrainableComboItem drainableComboItem = Type.tryCastTo(this->getActiveLightItem(), DrainableComboItem.class);
 if (drainableComboItem.empty()) {
 return;
 }

 if (Rand.Next(600 - (int)(0.4 / drainableComboItem.getUsedDelta() * 100.0) == 0) {
 this->flickTorch = true;
 }

 this->flickTorch = false;
 if (this->flickTorch) {
 if (Rand.Next(6) == 0) {
 drainableComboItem.setActivated(false);
 } else {
 drainableComboItem.setActivated(true);
 }

 if (Rand.Next(40) == 0) {
 this->flickTorch = false;
 drainableComboItem.setActivated(true);
 }
 }
 }
 }

 /**
 * @return the cell
 */
 IsoCell getCell() {
 return IsoWorld.instance.CurrentCell;
 }

 void calculateContext() {
 float float0 = this->x;
 float float1 = this->y;
 float float2 = this->x;
 IsoGridSquare[] squares = new IsoGridSquare[4];
 if (this->dir == IsoDirections.N) {
 squares[2] = this->getCell().getGridSquare((double)(float0 - 1.0F), (double)(float1 - 1.0F), (double)float2);
 squares[1] = this->getCell().getGridSquare((double)float0, (double)(float1 - 1.0F), (double)float2);
 squares[3] = this->getCell().getGridSquare((double)(float0 + 1.0F), (double)(float1 - 1.0F), (double)float2);
 } else if (this->dir == IsoDirections.NE) {
 squares[2] = this->getCell().getGridSquare((double)float0, (double)(float1 - 1.0F), (double)float2);
 squares[1] = this->getCell().getGridSquare((double)(float0 + 1.0F), (double)(float1 - 1.0F), (double)float2);
 squares[3] = this->getCell().getGridSquare((double)(float0 + 1.0F), (double)float1, (double)float2);
 } else if (this->dir == IsoDirections.E) {
 squares[2] = this->getCell().getGridSquare((double)(float0 + 1.0F), (double)(float1 - 1.0F), (double)float2);
 squares[1] = this->getCell().getGridSquare((double)(float0 + 1.0F), (double)float1, (double)float2);
 squares[3] = this->getCell().getGridSquare((double)(float0 + 1.0F), (double)(float1 + 1.0F), (double)float2);
 } else if (this->dir == IsoDirections.SE) {
 squares[2] = this->getCell().getGridSquare((double)(float0 + 1.0F), (double)float1, (double)float2);
 squares[1] = this->getCell().getGridSquare((double)(float0 + 1.0F), (double)(float1 + 1.0F), (double)float2);
 squares[3] = this->getCell().getGridSquare((double)float0, (double)(float1 + 1.0F), (double)float2);
 } else if (this->dir == IsoDirections.S) {
 squares[2] = this->getCell().getGridSquare((double)(float0 + 1.0F), (double)(float1 + 1.0F), (double)float2);
 squares[1] = this->getCell().getGridSquare((double)float0, (double)(float1 + 1.0F), (double)float2);
 squares[3] = this->getCell().getGridSquare((double)(float0 - 1.0F), (double)(float1 + 1.0F), (double)float2);
 } else if (this->dir == IsoDirections.SW) {
 squares[2] = this->getCell().getGridSquare((double)float0, (double)(float1 + 1.0F), (double)float2);
 squares[1] = this->getCell().getGridSquare((double)(float0 - 1.0F), (double)(float1 + 1.0F), (double)float2);
 squares[3] = this->getCell().getGridSquare((double)(float0 - 1.0F), (double)float1, (double)float2);
 } else if (this->dir == IsoDirections.W) {
 squares[2] = this->getCell().getGridSquare((double)(float0 - 1.0F), (double)(float1 + 1.0F), (double)float2);
 squares[1] = this->getCell().getGridSquare((double)(float0 - 1.0F), (double)float1, (double)float2);
 squares[3] = this->getCell().getGridSquare((double)(float0 - 1.0F), (double)(float1 - 1.0F), (double)float2);
 } else if (this->dir == IsoDirections.NW) {
 squares[2] = this->getCell().getGridSquare((double)(float0 - 1.0F), (double)float1, (double)float2);
 squares[1] = this->getCell().getGridSquare((double)(float0 - 1.0F), (double)(float1 - 1.0F), (double)float2);
 squares[3] = this->getCell().getGridSquare((double)float0, (double)(float1 - 1.0F), (double)float2);
 }

 squares[0] = this->current;

 for (int int0 = 0; int0 < 4; int0++) {
 IsoGridSquare square = squares[int0];
 if (square.empty()) {
 }
 }
 }

 bool isSafeToClimbOver(IsoDirections dir) {
 void* object = nullptr;
 switch (dir) {
 case N:
 object = this->getCell().getGridSquare((double)this->x, (double)(this->y - 1.0F), (double)this->z);
 break;
 case S:
 object = this->getCell().getGridSquare((double)this->x, (double)(this->y + 1.0F), (double)this->z);
 break;
 case W:
 object = this->getCell().getGridSquare((double)(this->x - 1.0F), (double)this->y, (double)this->z);
 break;
 case E:
 object = this->getCell().getGridSquare((double)(this->x + 1.0F), (double)this->y, (double)this->z);
 break;
 default:
 return false;
 }

 if (object.empty()) {
 return false;
 } else if (((IsoGridSquare)object).Is(IsoFlagType.water) {
 return false;
 } else {
 return !((IsoGridSquare)object).TreatAsSolidFloor() ? ((IsoGridSquare)object).HasStairsBelow() : true;
 }
 }

 bool doContext(IsoDirections dir) {
 if (this->isIgnoreContextKey()) {
 return false;
 } else if (this->isBlockMovement()) {
 return false;
 } else {
 for (int int0 = 0; int0 < this->getCell().vehicles.size(); int0++) {
 BaseVehicle vehicle = this->getCell().vehicles.get(int0);
 if (vehicle.getUseablePart(this) != nullptr) {
 return false;
 }
 }

 float float0 = this->x - (int)this->x;
 float float1 = this->y - (int)this->y;
 IsoDirections directions0 = IsoDirections.Max;
 IsoDirections directions1 = IsoDirections.Max;
 if (dir == IsoDirections.NW) {
 if (float1 < float0) {
 if (this->doContextNSWE(IsoDirections.N) {
 return true;
 }

 if (this->doContextNSWE(IsoDirections.W) {
 return true;
 }

 directions0 = IsoDirections.S;
 directions1 = IsoDirections.E;
 } else {
 if (this->doContextNSWE(IsoDirections.W) {
 return true;
 }

 if (this->doContextNSWE(IsoDirections.N) {
 return true;
 }

 directions0 = IsoDirections.E;
 directions1 = IsoDirections.S;
 }
 } else if (dir == IsoDirections.NE) {
 float0 = 1.0F - float0;
 if (float1 < float0) {
 if (this->doContextNSWE(IsoDirections.N) {
 return true;
 }

 if (this->doContextNSWE(IsoDirections.E) {
 return true;
 }

 directions0 = IsoDirections.S;
 directions1 = IsoDirections.W;
 } else {
 if (this->doContextNSWE(IsoDirections.E) {
 return true;
 }

 if (this->doContextNSWE(IsoDirections.N) {
 return true;
 }

 directions0 = IsoDirections.W;
 directions1 = IsoDirections.S;
 }
 } else if (dir == IsoDirections.SE) {
 float0 = 1.0F - float0;
 float1 = 1.0F - float1;
 if (float1 < float0) {
 if (this->doContextNSWE(IsoDirections.S) {
 return true;
 }

 if (this->doContextNSWE(IsoDirections.E) {
 return true;
 }

 directions0 = IsoDirections.N;
 directions1 = IsoDirections.W;
 } else {
 if (this->doContextNSWE(IsoDirections.E) {
 return true;
 }

 if (this->doContextNSWE(IsoDirections.S) {
 return true;
 }

 directions0 = IsoDirections.W;
 directions1 = IsoDirections.N;
 }
 } else if (dir == IsoDirections.SW) {
 float1 = 1.0F - float1;
 if (float1 < float0) {
 if (this->doContextNSWE(IsoDirections.S) {
 return true;
 }

 if (this->doContextNSWE(IsoDirections.W) {
 return true;
 }

 directions0 = IsoDirections.N;
 directions1 = IsoDirections.E;
 } else {
 if (this->doContextNSWE(IsoDirections.W) {
 return true;
 }

 if (this->doContextNSWE(IsoDirections.S) {
 return true;
 }

 directions0 = IsoDirections.E;
 directions1 = IsoDirections.N;
 }
 } else {
 if (this->doContextNSWE(dir) {
 return true;
 }

 directions0 = dir.RotLeft(4);
 }

 if (directions0 != IsoDirections.Max) {
 IsoObject object0 = this->getContextDoorOrWindowOrWindowFrame(directions0);
 if (object0 != nullptr) {
 this->doContextDoorOrWindowOrWindowFrame(directions0, object0);
 return true;
 }
 }

 if (directions1 != IsoDirections.Max) {
 IsoObject object1 = this->getContextDoorOrWindowOrWindowFrame(directions1);
 if (object1 != nullptr) {
 this->doContextDoorOrWindowOrWindowFrame(directions1, object1);
 return true;
 }
 }

 return false;
 }
 }

 bool doContextNSWE(IsoDirections directions) {
 assert directions = = IsoDirections.N || directions == IsoDirections.S || directions == IsoDirections.W || directions == IsoDirections.E;

 if (this->current.empty()) {
 return false;
 } else if (directions == IsoDirections.N && this->current.Is(IsoFlagType.climbSheetN) && this->canClimbSheetRope(this->current) {
 this->climbSheetRope();
 return true;
 } else if (directions == IsoDirections.S && this->current.Is(IsoFlagType.climbSheetS) && this->canClimbSheetRope(this->current) {
 this->climbSheetRope();
 return true;
 } else if (directions == IsoDirections.W && this->current.Is(IsoFlagType.climbSheetW) && this->canClimbSheetRope(this->current) {
 this->climbSheetRope();
 return true;
 } else if (directions == IsoDirections.E && this->current.Is(IsoFlagType.climbSheetE) && this->canClimbSheetRope(this->current) {
 this->climbSheetRope();
 return true;
 } else {
 IsoGridSquare square0 = this->current.nav[directions.index()];
 bool boolean0 = IsoWindow.isTopOfSheetRopeHere(square0) && this->canClimbDownSheetRope(square0);
 IsoObject object0 = this->getContextDoorOrWindowOrWindowFrame(directions);
 if (object0 != nullptr) {
 this->doContextDoorOrWindowOrWindowFrame(directions, object0);
 return true;
 } else {
 if (GameKeyboard.isKeyDown(42) && this->current != nullptr && this->ticksSincePressedMovement > 15.0F) {
 IsoObject object1 = this->current.getDoor(true);
 if (object1 instanceof IsoDoor && ((IsoDoor)object1).isFacingSheet(this) {
 ((IsoDoor)object1).toggleCurtain();
 return true;
 }

 IsoObject object2 = this->current.getDoor(false);
 if (object2 instanceof IsoDoor && ((IsoDoor)object2).isFacingSheet(this) {
 ((IsoDoor)object2).toggleCurtain();
 return true;
 }

 if (directions == IsoDirections.E) {
 IsoGridSquare square1 = IsoWorld.instance.CurrentCell.getGridSquare((double)(this->x + 1.0F), (double)this->y, (double)this->z);
 IsoObject object3 = square1 != nullptr ? square1.getDoor(true) : nullptr;
 if (object3 instanceof IsoDoor && ((IsoDoor)object3).isFacingSheet(this) {
 ((IsoDoor)object3).toggleCurtain();
 return true;
 }
 }

 if (directions == IsoDirections.S) {
 IsoGridSquare square2 = IsoWorld.instance.CurrentCell.getGridSquare((double)this->x, (double)(this->y + 1.0F), (double)this->z);
 IsoObject object4 = square2 != nullptr ? square2.getDoor(false) : nullptr;
 if (object4 instanceof IsoDoor && ((IsoDoor)object4).isFacingSheet(this) {
 ((IsoDoor)object4).toggleCurtain();
 return true;
 }
 }
 }

 bool boolean1 = this->isSafeToClimbOver(directions);
 if (this->z > 0.0F && boolean0) {
 boolean1 = true;
 }

 if (this->timePressedContext < 0.5F && !boolean1) {
 return false;
 } else if (this->ignoreAutoVault) {
 return false;
 } else if (directions == IsoDirections.N && this->getCurrentSquare().Is(IsoFlagType.HoppableN) {
 this->climbOverFence(directions);
 return true;
 } else if (directions == IsoDirections.W && this->getCurrentSquare().Is(IsoFlagType.HoppableW) {
 this->climbOverFence(directions);
 return true;
 } else if (directions == IsoDirections.S
 && IsoWorld.instance.CurrentCell.getGridSquare((double)this->x, (double)(this->y + 1.0F), (double)this->z) != nullptr
 && IsoWorld.instance.CurrentCell.getGridSquare((double)this->x, (double)(this->y + 1.0F), (double)this->z).Is(IsoFlagType.HoppableN) {
 this->climbOverFence(directions);
 return true;
 } else if (directions == IsoDirections.E
 && IsoWorld.instance.CurrentCell.getGridSquare((double)(this->x + 1.0F), (double)this->y, (double)this->z) != nullptr
 && IsoWorld.instance.CurrentCell.getGridSquare((double)(this->x + 1.0F), (double)this->y, (double)this->z).Is(IsoFlagType.HoppableW) {
 this->climbOverFence(directions);
 return true;
 } else {
 return this->climbOverWall(directions);
 }
 }
 }
 }

 IsoObject getContextDoorOrWindowOrWindowFrame(IsoDirections assumedDir) {
 if (this->current != nullptr && assumedDir != nullptr) {
 IsoGridSquare square = this->current.nav[assumedDir.index()];
 IsoObject object = nullptr;
 switch (assumedDir) {
 case N:
 object = this->current.getOpenDoor(assumedDir);
 if (object != nullptr) {
 return object;
 }

 object = this->current.getDoorOrWindowOrWindowFrame(assumedDir, true);
 if (object != nullptr) {
 return object;
 }

 object = this->current.getDoor(true);
 if (object != nullptr) {
 return object;
 }

 if (square != nullptr && !this->current.isBlockedTo(square) {
 object = square.getOpenDoor(IsoDirections.S);
 }
 break;
 case S:
 object = this->current.getOpenDoor(assumedDir);
 if (object != nullptr) {
 return object;
 }

 if (square != nullptr) {
 bool boolean1 = this->current.isBlockedTo(square);
 object = square.getDoorOrWindowOrWindowFrame(IsoDirections.N, boolean1);
 if (object != nullptr) {
 return object;
 }

 object = square.getDoor(true);
 }
 break;
 case W:
 object = this->current.getOpenDoor(assumedDir);
 if (object != nullptr) {
 return object;
 }

 object = this->current.getDoorOrWindowOrWindowFrame(assumedDir, true);
 if (object != nullptr) {
 return object;
 }

 object = this->current.getDoor(false);
 if (object != nullptr) {
 return object;
 }

 if (square != nullptr && !this->current.isBlockedTo(square) {
 object = square.getOpenDoor(IsoDirections.E);
 }
 break;
 case E:
 object = this->current.getOpenDoor(assumedDir);
 if (object != nullptr) {
 return object;
 }

 if (square != nullptr) {
 bool boolean0 = this->current.isBlockedTo(square);
 object = square.getDoorOrWindowOrWindowFrame(IsoDirections.W, boolean0);
 if (object != nullptr) {
 return object;
 }

 object = square.getDoor(false);
 }
 }

 return object;
 } else {
 return nullptr;
 }
 }

 void doContextDoorOrWindowOrWindowFrame(IsoDirections directions, IsoObject object) {
 IsoGridSquare square = this->current.nav[directions.index()];
 bool boolean0 = IsoWindow.isTopOfSheetRopeHere(square) && this->canClimbDownSheetRope(square);
 if (object instanceof IsoDoor door) {
 if (GameKeyboard.isKeyDown(42) && door.HasCurtains() != nullptr && door.isFacingSheet(this) && this->ticksSincePressedMovement > 15.0F) {
 door.toggleCurtain();
 } else if (this->timePressedContext >= 0.5F) {
 if (door.isHoppable() && !this->isIgnoreAutoVault()) {
 this->climbOverFence(directions);
 } else {
 door.ToggleDoor(this);
 }
 } else {
 door.ToggleDoor(this);
 }
 } else if (object instanceof IsoThumpable && ((IsoThumpable)object).isDoor()) {
 IsoThumpable thumpable0 = (IsoThumpable)object;
 if (this->timePressedContext >= 0.5F) {
 if (thumpable0.isHoppable() && !this->isIgnoreAutoVault()) {
 this->climbOverFence(directions);
 } else {
 thumpable0.ToggleDoor(this);
 }
 } else {
 thumpable0.ToggleDoor(this);
 }
 } else if (object instanceof IsoWindow && !object.getSquare().getProperties().Is(IsoFlagType.makeWindowInvincible) {
 IsoWindow window = (IsoWindow)object;
 if (GameKeyboard.isKeyDown(42) {
 IsoCurtain curtain0 = window.HasCurtains();
 if (curtain0 != nullptr && this->current != nullptr && !curtain0.getSquare().isBlockedTo(this->current) {
 curtain0.ToggleDoor(this);
 }
 } else if (this->timePressedContext >= 0.5F) {
 if (window.canClimbThrough(this) {
 this->climbThroughWindow(window);
 } else if (!window.PermaLocked && !window.isBarricaded() && !window.IsOpen() && !window.isDestroyed()) {
 this->openWindow(window);
 }
 } else if (window.Health > 0 && !window.isDestroyed()) {
 IsoBarricade barricade = window.getBarricadeForCharacter(this);
 if (!window.open && barricade.empty()) {
 this->openWindow(window);
 } else if (barricade.empty()) {
 this->closeWindow(window);
 }
 } else if (window.isGlassRemoved()) {
 if (!this->isSafeToClimbOver(directions) && !object.getSquare().haveSheetRope && !boolean0) {
 return;
 }

 if (!window.isBarricaded()) {
 this->climbThroughWindow(window);
 }
 }
 } else if (object instanceof IsoThumpable && !object.getSquare().getProperties().Is(IsoFlagType.makeWindowInvincible) {
 IsoThumpable thumpable1 = (IsoThumpable)object;
 if (GameKeyboard.isKeyDown(42) {
 IsoCurtain curtain1 = thumpable1.HasCurtains();
 if (curtain1 != nullptr && this->current != nullptr && !curtain1.getSquare().isBlockedTo(this->current) {
 curtain1.ToggleDoor(this);
 }
 } else if (this->timePressedContext >= 0.5F) {
 if (thumpable1.canClimbThrough(this) {
 this->climbThroughWindow(thumpable1);
 }
 } else {
 if (!this->isSafeToClimbOver(directions) && !object.getSquare().haveSheetRope && !boolean0) {
 return;
 }

 if (thumpable1.canClimbThrough(this) {
 this->climbThroughWindow(thumpable1);
 }
 }
 } else if (IsoWindowFrame.isWindowFrame(object) {
 if (GameKeyboard.isKeyDown(42) {
 IsoCurtain curtain2 = IsoWindowFrame.getCurtain(object);
 if (curtain2 != nullptr && this->current != nullptr && !curtain2.getSquare().isBlockedTo(this->current) {
 curtain2.ToggleDoor(this);
 }
 } else if ((this->timePressedContext >= 0.5F || this->isSafeToClimbOver(directions) || boolean0) && IsoWindowFrame.canClimbThrough(object, this) {
 this->climbThroughWindowFrame(object);
 }
 }
 }

 bool hopFence(IsoDirections dir, bool bTest) {
 float float0 = this->x - (int)this->x;
 float float1 = this->y - (int)this->y;
 if (dir == IsoDirections.NW) {
 if (float1 < float0) {
 return this->hopFence(IsoDirections.N, bTest) ? true : this->hopFence(IsoDirections.W, bTest);
 } else {
 return this->hopFence(IsoDirections.W, bTest) ? true : this->hopFence(IsoDirections.N, bTest);
 }
 } else if (dir == IsoDirections.NE) {
 float0 = 1.0F - float0;
 if (float1 < float0) {
 return this->hopFence(IsoDirections.N, bTest) ? true : this->hopFence(IsoDirections.E, bTest);
 } else {
 return this->hopFence(IsoDirections.E, bTest) ? true : this->hopFence(IsoDirections.N, bTest);
 }
 } else if (dir == IsoDirections.SE) {
 float0 = 1.0F - float0;
 float1 = 1.0F - float1;
 if (float1 < float0) {
 return this->hopFence(IsoDirections.S, bTest) ? true : this->hopFence(IsoDirections.E, bTest);
 } else {
 return this->hopFence(IsoDirections.E, bTest) ? true : this->hopFence(IsoDirections.S, bTest);
 }
 } else if (dir == IsoDirections.SW) {
 float1 = 1.0F - float1;
 if (float1 < float0) {
 return this->hopFence(IsoDirections.S, bTest) ? true : this->hopFence(IsoDirections.W, bTest);
 } else {
 return this->hopFence(IsoDirections.W, bTest) ? true : this->hopFence(IsoDirections.S, bTest);
 }
 } else if (this->current.empty()) {
 return false;
 } else {
 IsoGridSquare square = this->current.nav[dir.index()];
 if (square != nullptr && !square.Is(IsoFlagType.water) {
 if (dir == IsoDirections.N && this->getCurrentSquare().Is(IsoFlagType.HoppableN) {
 if (bTest) {
 return true;
 } else {
 this->climbOverFence(dir);
 return true;
 }
 } else if (dir == IsoDirections.W && this->getCurrentSquare().Is(IsoFlagType.HoppableW) {
 if (bTest) {
 return true;
 } else {
 this->climbOverFence(dir);
 return true;
 }
 } else if (dir == IsoDirections.S
 && IsoWorld.instance.CurrentCell.getGridSquare((double)this->x, (double)(this->y + 1.0F), (double)this->z) != nullptr
 && IsoWorld.instance.CurrentCell.getGridSquare((double)this->x, (double)(this->y + 1.0F), (double)this->z).Is(IsoFlagType.HoppableN) {
 if (bTest) {
 return true;
 } else {
 this->climbOverFence(dir);
 return true;
 }
 } else if (dir != IsoDirections.E
 || IsoWorld.instance.CurrentCell.getGridSquare((double)(this->x + 1.0F), (double)this->y, (double)this->z) == nullptr
 || !IsoWorld.instance.CurrentCell.getGridSquare((double)(this->x + 1.0F), (double)this->y, (double)this->z).Is(IsoFlagType.HoppableW) {
 return false;
 } else if (bTest) {
 return true;
 } else {
 this->climbOverFence(dir);
 return true;
 }
 } else {
 return false;
 }
 }
 }

 bool canClimbOverWall(IsoDirections dir) {
 if (this->isSprinting()) {
 return false;
 } else if (!this->isSafeToClimbOver(dir) || this->current.empty()) {
 return false;
 } else if (this->current.haveRoof) {
 return false;
 } else if (this->current.getBuilding() != nullptr) {
 return false;
 } else {
 IsoGridSquare square0 = IsoWorld.instance.CurrentCell.getGridSquare(this->current.x, this->current.y, this->current.z + 1);
 if (square0 != nullptr && square0.HasSlopedRoof()) {
 return false;
 } else {
 IsoGridSquare square1 = this->current.nav[dir.index()];
 if (square1.haveRoof) {
 return false;
 } else if (square1.isSolid() || square1.isSolidTrans()) {
 return false;
 } else if (square1.getBuilding() != nullptr) {
 return false;
 } else {
 IsoGridSquare square2 = IsoWorld.instance.CurrentCell.getGridSquare(square1.x, square1.y, square1.z + 1);
 if (square2 != nullptr && square2.HasSlopedRoof()) {
 return false;
 } else {
 switch (dir) {
 case N:
 if (this->current.Is(IsoFlagType.CantClimb) {
 return false;
 }

 if (!this->current.Has(IsoObjectType.wall) {
 return false;
 }

 if (!this->current.Is(IsoFlagType.collideN) {
 return false;
 }

 if (this->current.Is(IsoFlagType.HoppableN) {
 return false;
 }

 if (square0 != nullptr && square0.Is(IsoFlagType.collideN) {
 return false;
 }
 break;
 case S:
 if (square1.Is(IsoFlagType.CantClimb) {
 return false;
 }

 if (!square1.Has(IsoObjectType.wall) {
 return false;
 }

 if (!square1.Is(IsoFlagType.collideN) {
 return false;
 }

 if (square1.Is(IsoFlagType.HoppableN) {
 return false;
 }

 if (square2 != nullptr && square2.Is(IsoFlagType.collideN) {
 return false;
 }
 break;
 case W:
 if (this->current.Is(IsoFlagType.CantClimb) {
 return false;
 }

 if (!this->current.Has(IsoObjectType.wall) {
 return false;
 }

 if (!this->current.Is(IsoFlagType.collideW) {
 return false;
 }

 if (this->current.Is(IsoFlagType.HoppableW) {
 return false;
 }

 if (square0 != nullptr && square0.Is(IsoFlagType.collideW) {
 return false;
 }
 break;
 case E:
 if (square1.Is(IsoFlagType.CantClimb) {
 return false;
 }

 if (!square1.Has(IsoObjectType.wall) {
 return false;
 }

 if (!square1.Is(IsoFlagType.collideW) {
 return false;
 }

 if (square1.Is(IsoFlagType.HoppableW) {
 return false;
 }

 if (square2 != nullptr && square2.Is(IsoFlagType.collideW) {
 return false;
 }
 break;
 default:
 return false;
 }

 return IsoWindow.canClimbThroughHelper(this, this->current, square1, dir == IsoDirections.N || dir == IsoDirections.S);
 }
 }
 }
 }
 }

 bool climbOverWall(IsoDirections dir) {
 if (!this->canClimbOverWall(dir) {
 return false;
 } else {
 this->dropHeavyItems();
 ClimbOverWallState.instance().setParams(this, dir);
 this->actionContext.reportEvent("EventClimbWall");
 return true;
 }
 }

 void updateSleepingPillsTaken() {
 if (this->getSleepingPillsTaken() > 0 && this->lastPillsTaken > 0L && GameTime.instance.Calender.getTimeInMillis() - this->lastPillsTaken > 7200000L) {
 this->setSleepingPillsTaken(this->getSleepingPillsTaken() - 1);
 }
 }

 bool AttemptAttack() {
 return this->DoAttack(this->useChargeTime);
 }

 bool DoAttack(float chargeDelta) {
 return this->DoAttack(chargeDelta, false, nullptr);
 }

 bool DoAttack(float chargeDelta, bool forceShove, const std::string& clickSound) {
 if (!this->authorizeMeleeAction) {
 return false;
 } else {
 this->setForceShove(forceShove);
 this->setClickSound(clickSound);
 this->pressedAttack(true);
 return false;
 }
 }

 int getPlayerNum() {
 return this->PlayerIndex;
 }

 void updateLOS() {
 this->spottedList.clear();
 this->stats.NumVisibleZombies = 0;
 this->stats.LastNumChasingZombies = this->stats.NumChasingZombies;
 this->stats.NumChasingZombies = 0;
 this->stats.MusicZombiesTargeting = 0;
 this->stats.MusicZombiesVisible = 0;
 this->NumSurvivorsInVicinity = 0;
 if (this->getCurrentSquare() != nullptr) {
 bool boolean0 = GameServer.bServer;
 bool boolean1 = GameClient.bClient;
 int int0 = this->PlayerIndex;
 IsoPlayer player1 = getInstance();
 float float0 = this->getX();
 float float1 = this->getY();
 float float2 = this->getZ();
 int int1 = 0;
 int int2 = 0;
 int int3 = this->getCell().getObjectList().size();

 for (int int4 = 0; int4 < int3; int4++) {
 IsoMovingObject movingObject = this->getCell().getObjectList().get(int4);
 if (!(movingObject instanceof IsoPhysicsObject) && !(movingObject instanceof BaseVehicle) {
 if (movingObject == this) {
 this->spottedList.add(movingObject);
 } else {
 float float3 = movingObject.getX();
 float float4 = movingObject.getY();
 float float5 = movingObject.getZ();
 float float6 = IsoUtils.DistanceTo(float3, float4, float0, float1);
 if (float6 < 20.0F) {
 int1++;
 }

 IsoGridSquare square = movingObject.getCurrentSquare();
 if (square != nullptr) {
 if (this->isSeeEveryone()) {
 movingObject.setAlphaAndTarget(int0, 1.0F);
 } else {
 IsoGameCharacter character = Type.tryCastTo(movingObject, IsoGameCharacter.class);
 IsoPlayer player2 = Type.tryCastTo(character, IsoPlayer.class);
 IsoZombie zombie0 = Type.tryCastTo(character, IsoZombie.class);
 if (player1 != nullptr && movingObject != player1 && character != nullptr && character.isInvisible() && player1.accessLevel.empty()
 )
 {
 character.setAlphaAndTarget(int0, 0.0F);
 } else {
 float float7 = this->getSeeNearbyCharacterDistance();
 bool boolean2;
 if (boolean0) {
 boolean2 = ServerLOS.instance.isCouldSee(this, square);
 } else {
 boolean2 = square.isCouldSee(int0);
 }

 bool boolean3;
 if (boolean1 && player2 != nullptr) {
 boolean3 = true;
 } else if (!boolean0) {
 boolean3 = square.isCanSee(int0);
 } else {
 boolean3 = boolean2;
 }

 if (!this->isAsleep() && (boolean3 || float6 < float7 && boolean2) {
 this->TestZombieSpotPlayer(movingObject);
 if (character != nullptr && character.IsVisibleToPlayer[int0]) {
 if (character instanceof IsoSurvivor) {
 this->NumSurvivorsInVicinity++;
 }

 if (zombie0 != nullptr) {
 this->lastSeenZombieTime = 0.0;
 if (float5 >= float2 - 1.0F
 && float6 < 7.0F
 && !zombie0.Ghost
 && !zombie0.isFakeDead()
 && square.getRoom() == this->getCurrentSquare().getRoom()) {
 this->TicksSinceSeenZombie = 0;
 this->stats.NumVisibleZombies++;
 }

 if (float6 < 3.0F) {
 int2++;
 }

 if (!zombie0.isSceneCulled()) {
 this->stats.MusicZombiesVisible++;
 if (zombie0.target == this) {
 this->stats.MusicZombiesTargeting++;
 }
 }
 }

 this->spottedList.add(character);
 if (!(player2 instanceof IsoPlayer) && !this->bRemote) {
 if (player2 != nullptr && player2 != player1) {
 player2.setTargetAlpha(int0, 1.0F);
 } else {
 character.setTargetAlpha(int0, 1.0F);
 }
 }

 float float8 = 4.0F;
 if (this->stats.NumVisibleZombies > 4) {
 float8 = 7.0F;
 }

 if (float6 < float8
 && character instanceof IsoZombie
 && (int)float5 == (int)float2
 && !this->isGhostMode()
 && !boolean1) {
 GameTime.instance.setMultiplier(1.0F);
 if (!boolean0) {
 UIManager.getSpeedControls().SetCurrentGameSpeed(1);
 }
 }

 if (float6 < float8
 && character instanceof IsoZombie
 && (int)float5 == (int)float2
 && !this->LastSpotted.contains(character) {
 this->stats.NumVisibleZombies += 2;
 }
 }
 } else {
 if (movingObject != instance) {
 movingObject.setTargetAlpha(int0, 0.0F);
 }

 if (boolean2) {
 this->TestZombieSpotPlayer(movingObject);
 }
 }

 if (float6 < 2.0F && movingObject.getTargetAlpha(int0) == 1.0F && !this->bRemote) {
 movingObject.setAlpha(int0, 1.0F);
 }
 }
 }
 }
 }
 }
 }

 if (this->isAlive()
 && int2 > 0
 && this->stats.LastVeryCloseZombies == 0
 && this->stats.NumVisibleZombies > 0
 && this->stats.LastNumVisibleZombies == 0
 && this->timeSinceLastStab >= 600.0F) {
 this->timeSinceLastStab = 0.0F;
 long long0 = this->getEmitter().playSoundImpl("ZombieSurprisedPlayer", nullptr);
 this->getEmitter().setVolume(long0, Core.getInstance().getOptionJumpScareVolume() / 10.0F);
 }

 if (this->stats.NumVisibleZombies > 0) {
 this->timeSinceLastStab = 0.0F;
 }

 if (this->timeSinceLastStab < 600.0F) {
 this->timeSinceLastStab = this->timeSinceLastStab + GameTime.getInstance().getMultiplier() / 1.6F;
 }

 float float9 = int1 / 20.0F;
 if (float9 > 1.0F) {
 float9 = 1.0F;
 }

 float9 *= 0.6F;
 SoundManager.instance.BlendVolume(MainScreenState.ambient, float9);
 int int5 = 0;

 for (int int6 = 0; int6 < this->spottedList.size(); int6++) {
 if (!this->LastSpotted.contains(this->spottedList.get(int6) {
 this->LastSpotted.add(this->spottedList.get(int6);
 }

 if (this->spottedList.get(int6) instanceof IsoZombie) {
 int5++;
 }
 }

 if (this->ClearSpottedTimer <= 0 && int5 == 0) {
 this->LastSpotted.clear();
 this->ClearSpottedTimer = 1000;
 } else {
 this->ClearSpottedTimer--;
 }

 this->stats.LastNumVisibleZombies = this->stats.NumVisibleZombies;
 this->stats.LastVeryCloseZombies = int2;
 }
 }

 float getSeeNearbyCharacterDistance() {
 return 3.5F - this->stats.getFatigue();
 }

 bool checkSpottedPLayerTimer(IsoPlayer player0) {
 if (!player0.spottedByPlayer) {
 return false;
 } else {
 if (this->spottedPlayerTimer.containsKey(player0.getRemoteID())) {
 this->spottedPlayerTimer.put(player0.getRemoteID(), this->spottedPlayerTimer.get(player0.getRemoteID()) + 1);
 } else {
 this->spottedPlayerTimer.put(player0.getRemoteID(), 1);
 }

 if (this->spottedPlayerTimer.get(player0.getRemoteID()) > 100) {
 player0.spottedByPlayer = false;
 player0.doRenderShadow = false;
 return false;
 } else {
 return true;
 }
 }
 }

 bool checkCanSeeClient(UdpConnection remoteConnection) {
 return remoteConnection.accessLevel > 1 ? true : !this->isInvisible();
 }

 bool checkCanSeeClient(IsoPlayer remoteChr) {
 remoteChr.doRenderShadow = true;
 Vector2 vector0 = tempVector2_1.set(this->getX(), this->getY());
 Vector2 vector1 = tempVector2_2.set(remoteChr.getX(), remoteChr.getY());
 vector1.x = vector1.x - vector0.x;
 vector1.y = vector1.y - vector0.y;
 Vector2 vector2 = this->getForwardDirection();
 vector1.normalize();
 vector2.normalize();
 vector2.normalize();
 float float0 = vector1.dot(vector2);
 if (!GameClient.bClient || remoteChr == this || !this->isLocalPlayer()) {
 return true;
 } else if (!this->isAccessLevel("None") && this->canSeeAll) {
 remoteChr.spottedByPlayer = true;
 return true;
 } else {
 float float1 = this->current.empty() ? 0.0F : remoteChr.getCurrentSquare().DistTo(this->getCurrentSquare());
 if (float1 <= 2.0F) {
 remoteChr.spottedByPlayer = true;
 return true;
 } else if (ServerOptions.getInstance().HidePlayersBehindYou.getValue() && float0 < -0.5) {
 return this->checkSpottedPLayerTimer(remoteChr);
 } else if (remoteChr.isGhostMode() && this->isAccessLevel("None")) {
 remoteChr.doRenderShadow = false;
 remoteChr.spottedByPlayer = false;
 return false;
 } else {
 IsoGridSquare.ILighting iLighting = remoteChr.getCurrentSquare().lighting[this->getPlayerNum()];
 if (!iLighting.bCouldSee()) {
 return this->checkSpottedPLayerTimer(remoteChr);
 } else if (remoteChr.isSneaking() && ServerOptions.getInstance().SneakModeHideFromOtherPlayers.getValue() && !remoteChr.isSprinting()) {
 if (float1 > 30.0F) {
 remoteChr.spottedByPlayer = false;
 }

 if (remoteChr.spottedByPlayer) {
 return true;
 } else {
 remoteChr.doRenderShadow = true;
 float float2 = (float)(Math.pow(Math.max(40.0F - float1, 0.0F), 3.0) / 12000.0);
 float float3 = (float)(1.0 - remoteChr.remoteSneakLvl / 10.0F * 0.9 + 0.3);
 float float4 = 1.0F;
 if (float0 < 0.8) {
 float4 = 0.3F;
 }

 if (float0 < 0.6) {
 float4 = 0.05F;
 }

 float float5 = (iLighting.lightInfo().getR() + iLighting.lightInfo().getG() + iLighting.lightInfo().getB()) / 3.0F;
 float float6 = (float)((1.0 - this->getMoodles().getMoodleLevel(MoodleType.Tired) / 5.0F) * 0.7 + 0.3);
 float float7 = 0.1F;
 if (remoteChr.isPlayerMoving()) {
 float7 = 0.35F;
 }

 if (remoteChr.isRunning()) {
 float7 = 1.0F;
 }

 ArrayList arrayList = PolygonalMap2.instance
 .getPointInLine(remoteChr.getX(), remoteChr.getY(), this->getX(), this->getY(), (int)this->getZ());
 IsoGridSquare square = nullptr;
 float float8 = 0.0F;
 float float9 = 0.0F;
 bool boolean0 = false;

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 PolygonalMap2.Point point = (PolygonalMap2.Point)arrayList.get(int0);
 square = IsoCell.getInstance().getGridSquare((double)point.x, (double)point.y, (double)this->getZ());
 if (square != nullptr) {
 float float10 = square.getGridSneakModifier(false);
 if (float10 > 1.0F) {
 boolean0 = true;
 break;
 }

 for (int int1 = 0; int1 < square.getObjects().size(); int1++) {
 IsoObject object = square.getObjects().get(int1);
 if (object.getSprite().getProperties().Is(IsoFlagType.solidtrans)
 || object.getSprite().getProperties().Is(IsoFlagType.solid)
 || object.getSprite().getProperties().Is(IsoFlagType.windowW)
 || object.getSprite().getProperties().Is(IsoFlagType.windowN) {
 boolean0 = true;
 break;
 }
 }

 if (boolean0) {
 break;
 }
 }
 }

 if (boolean0) {
 float8 = square.DistTo(remoteChr.getCurrentSquare());
 float9 = square.DistTo(this->getCurrentSquare());
 }

 float float11 = float9 < 2.0F ? 5.0F : Math.min(float8, 5.0F);
 float11 = Math.max(0.0F, float11 - 1.0F);
 float11 = (float)(float11 / 5.0 * 0.9 + 0.1);
 float float12 = Math.max(0.1F, 1.0F - ClimateManager.getInstance().getFogIntensity());
 float float13 = float4 * float2 * float5 * float3 * float6 * float7 * float11 * float12;
 if (float13 >= 1.0F) {
 remoteChr.spottedByPlayer = true;
 return true;
 } else {
 float13 = (float)(1.0 - Math.pow(1.0F - float13, GameTime.getInstance().getMultiplier()));
 float13 *= 0.5F;
 bool boolean1 = Rand.Next(0.0F, 1.0F) < float13;
 remoteChr.spottedByPlayer = boolean1;
 if (!boolean1) {
 remoteChr.doRenderShadow = false;
 }

 return boolean1;
 }
 }
 } else {
 remoteChr.spottedByPlayer = true;
 return true;
 }
 }
 }
 }

 std::string getTimeSurvived() {
 std::string string0 = "";
 int int0 = (int)this->getHoursSurvived();
 int int1 = int0 / 24;
 int int2 = int0 % 24;
 int int3 = int1 / 30;
 int1 %= 30;
 int int4 = int3 / 12;
 int3 %= 12;
 std::string string1 = Translator.getText("IGUI_Gametime_day");
 std::string string2 = Translator.getText("IGUI_Gametime_year");
 std::string string3 = Translator.getText("IGUI_Gametime_hour");
 std::string string4 = Translator.getText("IGUI_Gametime_month");
 if (int4 != 0) {
 if (int4 > 1) {
 string2 = Translator.getText("IGUI_Gametime_years");
 }

 if (string0.length() > 0) {
 string0 = string0 + ", ";
 }

 string0 = string0 + int4 + " " + string2;
 }

 if (int3 != 0) {
 if (int3 > 1) {
 string4 = Translator.getText("IGUI_Gametime_months");
 }

 if (string0.length() > 0) {
 string0 = string0 + ", ";
 }

 string0 = string0 + int3 + " " + string4;
 }

 if (int1 != 0) {
 if (int1 > 1) {
 string1 = Translator.getText("IGUI_Gametime_days");
 }

 if (string0.length() > 0) {
 string0 = string0 + ", ";
 }

 string0 = string0 + int1 + " " + string1;
 }

 if (int2 != 0) {
 if (int2 > 1) {
 string3 = Translator.getText("IGUI_Gametime_hours");
 }

 if (string0.length() > 0) {
 string0 = string0 + ", ";
 }

 string0 = string0 + int2 + " " + string3;
 }

 if (string0.empty()) {
 int int5 = (int)(this->HoursSurvived * 60.0);
 string0 = int5 + " " + Translator.getText("IGUI_Gametime_minutes");
 }

 return string0;
 }

 bool IsUsingAimWeapon() {
 if (this->leftHandItem.empty()) {
 return false;
 } else if (!(this->leftHandItem instanceof HandWeapon) {
 return false;
 } else {
 return !this->isAiming() ? false : ((HandWeapon)this->leftHandItem).bIsAimedFirearm;
 }
 }

 bool IsUsingAimHandWeapon() {
 if (this->leftHandItem.empty()) {
 return false;
 } else if (!(this->leftHandItem instanceof HandWeapon) {
 return false;
 } else {
 return !this->isAiming() ? false : ((HandWeapon)this->leftHandItem).bIsAimedHandWeapon;
 }
 }

 bool DoAimAnimOnAiming() {
 return this->IsUsingAimWeapon();
 }

 int getSleepingPillsTaken() {
 return this->sleepingPillsTaken;
 }

 /**
 * If you've take more than 10 sleeping pills you lose some health If you're drunk, 1 pills = 2
 */
 void setSleepingPillsTaken(int _sleepingPillsTaken) {
 this->sleepingPillsTaken = _sleepingPillsTaken;
 if (this->getStats().Drunkenness > 10.0F) {
 this->sleepingPillsTaken++;
 }

 this->lastPillsTaken = GameTime.instance.Calender.getTimeInMillis();
 }

 bool isOutside() {
 return this->getCurrentSquare() != nullptr && this->getCurrentSquare().getRoom() == nullptr && !this->isInARoom();
 }

 double getLastSeenZomboidTime() {
 return this->lastSeenZombieTime;
 }

 /**
 * Return the amount of temperature given by clothes wear
 * @return temperature
 */
 float getPlayerClothingTemperature() {
 float float0 = 0.0F;
 if (this->getClothingItem_Feet() != nullptr) {
 float0 += ((Clothing)this->getClothingItem_Feet()).getTemperature();
 }

 if (this->getClothingItem_Hands() != nullptr) {
 float0 += ((Clothing)this->getClothingItem_Hands()).getTemperature();
 }

 if (this->getClothingItem_Head() != nullptr) {
 float0 += ((Clothing)this->getClothingItem_Head()).getTemperature();
 }

 if (this->getClothingItem_Legs() != nullptr) {
 float0 += ((Clothing)this->getClothingItem_Legs()).getTemperature();
 }

 if (this->getClothingItem_Torso() != nullptr) {
 float0 += ((Clothing)this->getClothingItem_Torso()).getTemperature();
 }

 return float0;
 }

 float getPlayerClothingInsulation() {
 float float0 = 0.0F;
 if (this->getClothingItem_Feet() != nullptr) {
 float0 += ((Clothing)this->getClothingItem_Feet()).getInsulation() * 0.1F;
 }

 if (this->getClothingItem_Hands() != nullptr) {
 float0 += ((Clothing)this->getClothingItem_Hands()).getInsulation() * 0.0F;
 }

 if (this->getClothingItem_Head() != nullptr) {
 float0 += ((Clothing)this->getClothingItem_Head()).getInsulation() * 0.0F;
 }

 if (this->getClothingItem_Legs() != nullptr) {
 float0 += ((Clothing)this->getClothingItem_Legs()).getInsulation() * 0.3F;
 }

 if (this->getClothingItem_Torso() != nullptr) {
 float0 += ((Clothing)this->getClothingItem_Torso()).getInsulation() * 0.6F;
 }

 return float0;
 }

 InventoryItem getActiveLightItem() {
 if (this->rightHandItem != nullptr && this->rightHandItem.isEmittingLight()) {
 return this->rightHandItem;
 } else if (this->leftHandItem != nullptr && this->leftHandItem.isEmittingLight()) {
 return this->leftHandItem;
 } else {
 AttachedItems attachedItems = this->getAttachedItems();

 for (int int0 = 0; int0 < attachedItems.size(); int0++) {
 InventoryItem item = attachedItems.getItemByIndex(int0);
 if (item.isEmittingLight()) {
 return item;
 }
 }

 return nullptr;
 }
 }

 bool isTorchCone() {
 if (this->bRemote) {
 return this->mpTorchCone;
 } else {
 InventoryItem item = this->getActiveLightItem();
 return item != nullptr && item.isTorchCone();
 }
 }

 float getTorchDot() {
 if (this->bRemote) {
 }

 InventoryItem item = this->getActiveLightItem();
 return item != nullptr ? item.getTorchDot() : 0.0F;
 }

 float getLightDistance() {
 if (this->bRemote) {
 return this->mpTorchDist;
 } else {
 InventoryItem item = this->getActiveLightItem();
 return item != nullptr ? item.getLightDistance() : 0.0F;
 }
 }

 bool pressedMovement(bool ignoreBlock) {
 if (this->isNPC) {
 return false;
 } else if (GameClient.bClient && !this->isLocal()) {
 return this->networkAI.isPressedMovement();
 } else {
 bool boolean0 = false;
 if (this->PlayerIndex == 0) {
 boolean0 = GameKeyboard.isKeyDown(Core.getInstance().getKey("Run"));
 }

 if (this->JoypadBind != -1) {
 boolean0 |= JoypadManager.instance.isRTPressed(this->JoypadBind);
 }

 this->setVariable("pressedRunButton", boolean0);
 if (ignoreBlock || !this->isBlockMovement() && !this->isIgnoreInputsForDirection()) {
 if (this->PlayerIndex != 0
 || !GameKeyboard.isKeyDown(Core.getInstance().getKey("Left"))
 && !GameKeyboard.isKeyDown(Core.getInstance().getKey("Right"))
 && !GameKeyboard.isKeyDown(Core.getInstance().getKey("Forward"))
 && !GameKeyboard.isKeyDown(Core.getInstance().getKey("Backward"))) {
 if (this->JoypadBind != -1) {
 float float0 = JoypadManager.instance.getMovementAxisY(this->JoypadBind);
 float float1 = JoypadManager.instance.getMovementAxisX(this->JoypadBind);
 float float2 = JoypadManager.instance.getDeadZone(this->JoypadBind, 0);
 if (Math.abs(float0) > float2 || Math.abs(float1) > float2) {
 if (GameClient.bClient && this->isLocal()) {
 this->networkAI.setPressedMovement(true);
 }

 return true;
 }
 }

 if (GameClient.bClient && this->isLocal()) {
 this->networkAI.setPressedMovement(false);
 }

 return false;
 } else {
 if (GameClient.bClient && this->isLocal()) {
 this->networkAI.setPressedMovement(true);
 }

 return true;
 }
 } else {
 if (GameClient.bClient && this->isLocal()) {
 this->networkAI.setPressedMovement(false);
 }

 return false;
 }
 }
 }

 bool pressedCancelAction() {
 if (this->isNPC) {
 return false;
 } else if (GameClient.bClient && !this->isLocal()) {
 return this->networkAI.isPressedCancelAction();
 } else if (this->PlayerIndex == 0 && GameKeyboard.isKeyDown(Core.getInstance().getKey("CancelAction"))) {
 if (GameClient.bClient && this->isLocal()) {
 this->networkAI.setPressedCancelAction(true);
 }

 return true;
 } else if (this->JoypadBind != -1) {
 bool boolean0 = JoypadManager.instance.isBButtonStartPress(this->JoypadBind);
 if (GameClient.bClient && this->isLocal()) {
 this->networkAI.setPressedCancelAction(boolean0);
 }

 return boolean0;
 } else {
 if (GameClient.bClient && this->isLocal()) {
 this->networkAI.setPressedCancelAction(false);
 }

 return false;
 }
 }

 bool checkWalkTo() {
 if (this->isNPC) {
 return false;
 } else if (this->PlayerIndex == 0 && GameKeyboard.isKeyDown(Core.getInstance().getKey("WalkTo"))) {
 LuaEventManager.triggerEvent("OnPressWalkTo", 0, 0, 0);
 return true;
 } else {
 return false;
 }
 }

 bool pressedAim() {
 if (this->isNPC) {
 return false;
 } else {
 if (this->PlayerIndex == 0) {
 if (this->isAimKeyDown()) {
 return true;
 }

 if (Mouse.isButtonDownUICheck(1) {
 return true;
 }
 }

 if (this->JoypadBind == -1) {
 return false;
 } else {
 float float0 = JoypadManager.instance.getAimingAxisY(this->JoypadBind);
 float float1 = JoypadManager.instance.getAimingAxisX(this->JoypadBind);
 return Math.abs(float0) > 0.1F || Math.abs(float1) > 0.1F;
 }
 }
 }

 bool isDoingActionThatCanBeCancelled() {
 if (this->isDead()) {
 return false;
 } else if (!this->getCharacterActions().empty()) {
 return true;
 } else {
 State state = this->getCurrentState();
 if (state != nullptr && state.isDoingActionThatCanBeCancelled()) {
 return true;
 } else {
 for (int int0 = 0; int0 < this->stateMachine.getSubStateCount(); int0++) {
 state = this->stateMachine.getSubStateAt(int0);
 if (state != nullptr && state.isDoingActionThatCanBeCancelled()) {
 return true;
 }
 }

 return false;
 }
 }
 }

 long getSteamID() {
 return this->steamID;
 }

 void setSteamID(long _steamID) {
 this->steamID = _steamID;
 }

 bool isTargetedByZombie() {
 return this->targetedByZombie;
 }

 bool isMaskClicked(int x, int y, bool flip) {
 return this->sprite.empty() ? false : this->sprite.isMaskClicked(this->dir, x, y, flip);
 }

 int getOffSetXUI() {
 return this->offSetXUI;
 }

 void setOffSetXUI(int _offSetXUI) {
 this->offSetXUI = _offSetXUI;
 }

 int getOffSetYUI() {
 return this->offSetYUI;
 }

 void setOffSetYUI(int _offSetYUI) {
 this->offSetYUI = _offSetYUI;
 }

 std::string getUsername() {
 return this->getUsername(false);
 }

 std::string getUsername(bool canShowFirstname) {
 std::string string = this->username;
 if (canShowFirstname && GameClient.bClient && ServerOptions.instance.ShowFirstAndLastName.getValue() && this->isAccessLevel("None")) {
 string = this->getDescriptor().getForename() + " " + this->getDescriptor().getSurname();
 if (ServerOptions.instance.DisplayUserName.getValue()) {
 string = string + " (" + this->username + ")";
 }
 }

 return string;
 }

 void setUsername(const std::string& newUsername) {
 this->username = newUsername;
 }

 void updateUsername() {
 if (!GameClient.bClient && !GameServer.bServer) {
 this->username = this->getDescriptor().getForename() + this->getDescriptor().getSurname();
 }
 }

 short getOnlineID() {
 return this->OnlineID;
 }

 bool isLocalPlayer() {
 if (GameServer.bServer) {
 return false;
 } else {
 for (int int0 = 0; int0 < numPlayers; int0++) {
 if (players[int0] == this) {
 return true;
 }
 }

 return false;
 }
 }

 static void setLocalPlayer(int index, IsoPlayer newPlayerObj) {
 players[index] = newPlayerObj;
 }

 static IsoPlayer getLocalPlayerByOnlineID(short ID) {
 for (int int0 = 0; int0 < numPlayers; int0++) {
 IsoPlayer player = players[int0];
 if (player != nullptr && player.OnlineID == ID) {
 return player;
 }
 }

 return nullptr;
 }

 bool isOnlyPlayerAsleep() {
 if (!this->isAsleep()) {
 return false;
 } else {
 for (int int0 = 0; int0 < numPlayers; int0++) {
 if (players[int0] != nullptr && !players[int0].isDead() && players[int0] != this && players[int0].isAsleep()) {
 return false;
 }
 }

 return true;
 }
 }

 void OnDeath() {
 super.OnDeath();
 if (!GameServer.bServer) {
 this->StopAllActionQueue();
 if (this->isAsleep()) {
 UIManager.FadeIn(this->getPlayerNum(), 0.5);
 this->setAsleep(false);
 }

 this->dropHandItems();
 if (allPlayersDead()) {
 SoundManager.instance.playMusic(DEATH_MUSIC_NAME);
 }

 if (this->isLocalPlayer()) {
 LuaEventManager.triggerEvent("OnPlayerDeath", this);
 }

 if (this->isLocalPlayer() && this->getVehicle() != nullptr) {
 this->getVehicle().exit(this);
 }

 this->removeSaveFile();
 if (this->shouldBecomeZombieAfterDeath()) {
 this->forceAwake();
 }

 this->getMoodles().Update();
 this->getCell().setDrag(nullptr, this->getPlayerNum());
 }
 }

 bool isNoClip() {
 return this->noClip;
 }

 void setNoClip(bool _noClip) {
 this->noClip = _noClip;
 }

 void setAuthorizeMeleeAction(bool enabled) {
 this->authorizeMeleeAction = enabled;
 }

 bool isAuthorizeMeleeAction() {
 return this->authorizeMeleeAction;
 }

 void setAuthorizeShoveStomp(bool enabled) {
 this->authorizeShoveStomp = enabled;
 }

 bool isAuthorizeShoveStomp() {
 return this->authorizeShoveStomp;
 }

 bool isBlockMovement() {
 return this->blockMovement;
 }

 void setBlockMovement(bool _blockMovement) {
 this->blockMovement = _blockMovement;
 }

 void startReceivingBodyDamageUpdates(IsoPlayer other) {
 if (GameClient.bClient && other != nullptr && other != this && this->isLocalPlayer() && !other.isLocalPlayer()) {
 other.resetBodyDamageRemote();
 BodyDamageSync.instance.startReceivingUpdates(other.getOnlineID());
 }
 }

 void stopReceivingBodyDamageUpdates(IsoPlayer other) {
 if (GameClient.bClient && other != nullptr && other != this && !other.isLocalPlayer()) {
 BodyDamageSync.instance.stopReceivingUpdates(other.getOnlineID());
 }
 }

 Nutrition getNutrition() {
 return this->nutrition;
 }

 Fitness getFitness() {
 return this->fitness;
 }

 bool updateRemotePlayer() {
 if (!this->bRemote) {
 return false;
 } else {
 if (GameServer.bServer) {
 ServerLOS.instance.doServerZombieLOS(this);
 ServerLOS.instance.updateLOS(this);
 if (this->isDead()) {
 return true;
 }

 this->removeFromSquare();
 this->setX(this->realx);
 this->setY(this->realy);
 this->setZ(this->realz);
 this->setLx(this->realx);
 this->setLy(this->realy);
 this->setLz(this->realz);
 this->ensureOnTile();
 if (this->slowTimer > 0.0F) {
 this->slowTimer = this->slowTimer - GameTime.instance.getRealworldSecondsSinceLastUpdate();
 this->slowFactor = this->slowFactor - GameTime.instance.getMultiplier() / 100.0F;
 if (this->slowFactor < 0.0F) {
 this->slowFactor = 0.0F;
 }
 } else {
 this->slowFactor = 0.0F;
 }
 }

 if (GameClient.bClient) {
 if (this->isCurrentState(BumpedState.instance())) {
 return true;
 }

 float float0;
 float float1;
 float float2;
 if (!this->networkAI.isCollisionEnabled() && !this->networkAI.isNoCollisionTimeout()) {
 this->setCollidable(false);
 float0 = this->realx;
 float1 = this->realy;
 float2 = this->realz;
 } else {
 this->setCollidable(true);
 float0 = this->networkAI.targetX;
 float1 = this->networkAI.targetY;
 float2 = this->networkAI.targetZ;
 }

 this->updateMovementRates();
 PathFindBehavior2 pathFindBehavior2 = this->getPathFindBehavior2();
 bool boolean0 = false;
 if (!this->networkAI.events.empty()) {
 Iterator iterator = this->networkAI.events.iterator();

 while (iterator.hasNext()) {
 EventPacket eventPacket = (EventPacket)iterator.next();
 if (eventPacket.process(this) {
 this->m_isPlayerMoving = this->networkAI.moving = false;
 this->setJustMoved(false);
 if (this->networkAI.usePathFind) {
 pathFindBehavior2.reset();
 this->setPath2(nullptr);
 this->networkAI.usePathFind = false;
 }

 iterator.remove();
 return true;
 }

 if (!eventPacket.isMovableEvent()) {
 tempo.set(eventPacket.x - this->x, eventPacket.y - this->y);
 float0 = eventPacket.x;
 float1 = eventPacket.y;
 float2 = eventPacket.z;
 boolean0 = true;
 }

 if (eventPacket.isTimeout()) {
 this->m_isPlayerMoving = this->networkAI.moving = false;
 this->setJustMoved(false);
 if (this->networkAI.usePathFind) {
 pathFindBehavior2.reset();
 this->setPath2(nullptr);
 this->networkAI.usePathFind = false;
 }

 if (Core.bDebug) {
 DebugLog.log(
 DebugType.Multiplayer, String.format("Event timeout (%d) : %s", this->networkAI.events.size(), eventPacket.getDescription())
 );
 }

 iterator.remove();
 return true;
 }
 }
 }

 if (!boolean0
 && this->networkAI.collidePointX > -1.0F
 && this->networkAI.collidePointY > -1.0F
 && ((int)this->x != (int)this->networkAI.collidePointX || (int)this->y != (int)this->networkAI.collidePointY) {
 float0 = this->networkAI.collidePointX;
 float1 = this->networkAI.collidePointY;
 DebugLog.log(
 DebugType.ActionSystem,
 "Player " + this->username + ": collide point (" + float0 + ", " + float1 + ") has not been reached, so move to it"
 );
 }

 if (DebugOptions.instance.MultiplayerShowPlayerPrediction.getValue()) {
 this->networkAI.targetX = float0;
 this->networkAI.targetY = float1;
 }

 if (!this->networkAI.forcePathFinder && this->isCollidedThisFrame() && IsoUtils.DistanceManhatten(float0, float1, this->x, this->y) > 3.0F) {
 this->networkAI.forcePathFinder = true;
 }

 if (this->networkAI.forcePathFinder
 && !PolygonalMap2.instance.lineClearCollide(this->x, this->y, float0, float1, (int)this->z, this->vehicle, false, true)
 && IsoUtils.DistanceManhatten(float0, float1, this->x, this->y) < 2.0F
 || this->getCurrentState() == ClimbOverFenceState.instance()
 || this->getCurrentState() == ClimbThroughWindowState.instance()
 || this->getCurrentState() == ClimbOverWallState.instance()) {
 this->networkAI.forcePathFinder = false;
 }

 if (!this->networkAI.needToMovingUsingPathFinder && !this->networkAI.forcePathFinder) {
 if (this->networkAI.usePathFind) {
 pathFindBehavior2.reset();
 this->setPath2(nullptr);
 this->networkAI.usePathFind = false;
 }

 pathFindBehavior2.walkingOnTheSpot.reset(this->x, this->y);
 this->getDeferredMovement(tempVector2_2);
 if (this->getCurrentState() != ClimbOverWallState.instance() && this->getCurrentState() != ClimbOverFenceState.instance()) {
 float float3 = IsoUtils.DistanceTo(this->x, this->y, this->networkAI.targetX, this->networkAI.targetY)
 / IsoUtils.DistanceTo(this->realx, this->realy, this->networkAI.targetX, this->networkAI.targetY);
 float float4 = 0.8F + 0.4F * IsoUtils.smoothstep(0.8F, 1.2F, float3);
 pathFindBehavior2.moveToPoint(float0, float1, float4);
 } else {
 this->MoveUnmodded(tempVector2_2);
 }

 this->m_isPlayerMoving = !boolean0 && IsoUtils.DistanceManhatten(float0, float1, this->x, this->y) > 0.2F
 || (int)float0 != (int)this->x
 || (int)float1 != (int)this->y
 || (int)this->z != (int)float2;
 if (!this->m_isPlayerMoving) {
 this->DirectionFromVector(this->networkAI.direction);
 this->setForwardDirection(this->networkAI.direction);
 this->networkAI.forcePathFinder = false;
 if (this->networkAI.usePathFind) {
 pathFindBehavior2.reset();
 this->setPath2(nullptr);
 this->networkAI.usePathFind = false;
 }
 }

 this->setJustMoved(this->m_isPlayerMoving);
 this->m_deltaX = 0.0F;
 this->m_deltaY = 0.0F;
 } else {
 if (!this->networkAI.usePathFind || float0 != pathFindBehavior2.getTargetX() || float1 != pathFindBehavior2.getTargetY()) {
 pathFindBehavior2.pathToLocationF(float0, float1, float2);
 pathFindBehavior2.walkingOnTheSpot.reset(this->x, this->y);
 this->networkAI.usePathFind = true;
 }

 PathFindBehavior2.BehaviorResult behaviorResult = pathFindBehavior2.update();
 if (behaviorResult == PathFindBehavior2.BehaviorResult.Failed) {
 this->setPathFindIndex(-1);
 if (this->networkAI.forcePathFinder) {
 this->networkAI.forcePathFinder = false;
 } else if (NetworkTeleport.teleport(this, NetworkTeleport.Type.teleportation, float0, float1, (byte)float2, 1.0F) && GameServer.bServer
 )
 {
 DebugLog.Multiplayer
 .warn(
 String.format(
 "Player %d teleport from (%.2f, %.2f, %.2f) to (%.2f, %.2f, %.2f)",
 this->getOnlineID(),
 this->x,
 this->y,
 this->z,
 float0,
 float1,
 float2
 )
 );
 }
 } else if (behaviorResult == PathFindBehavior2.BehaviorResult.Succeeded) {
 int int0 = (int)pathFindBehavior2.getTargetX();
 int int1 = (int)pathFindBehavior2.getTargetY();
 if (GameServer.bServer) {
 ServerMap.instance.getChunk(int0 / 10, int1 / 10);
 } else {
 IsoWorld.instance.CurrentCell.getChunkForGridSquare(int0, int1, 0);
 }

 this->m_isPlayerMoving = true;
 this->setJustMoved(true);
 }

 this->m_deltaX = 0.0F;
 this->m_deltaY = 0.0F;
 }

 if (!this->m_isPlayerMoving || this->isAiming()) {
 this->DirectionFromVector(this->networkAI.direction);
 this->setForwardDirection(this->networkAI.direction);
 tempo.set(float0 - this->nx, -(float1 - this->ny);
 tempo.normalize();
 float float5 = this->legsSprite.modelSlot.model.AnimPlayer.getRenderedAngle();
 if (float5 > Math.PI * 2) {
 float5 = (float)(float5 - (Math.PI * 2);
 }

 if (float5 < 0.0F) {
 float5 = (float)(float5 + (Math.PI * 2);
 }

 tempo.rotate(float5);
 tempo.setLength(Math.min(IsoUtils.DistanceTo(float0, float1, this->x, this->y), 1.0F);
 this->m_deltaX = tempo.x;
 this->m_deltaY = tempo.y;
 }
 }

 return true;
 }
 }

 bool updateWhileDead() {
 if (GameServer.bServer) {
 return false;
 } else if (!this->isLocalPlayer()) {
 return false;
 } else if (!this->isDead()) {
 return false;
 } else {
 this->setVariable("bPathfind", false);
 this->setMoving(false);
 this->m_isPlayerMoving = false;
 if (this->getVehicle() != nullptr) {
 this->getVehicle().exit(this);
 }

 if (this->heartEventInstance != 0L) {
 this->getEmitter().stopSound(this->heartEventInstance);
 this->heartEventInstance = 0L;
 }

 return true;
 }
 }

 void initFMODParameters() {
 FMODParameterList fMODParameterList = this->getFMODParameters();
 fMODParameterList.add(this->parameterCharacterMovementSpeed);
 fMODParameterList.add(this->parameterEquippedBaggageContainer);
 fMODParameterList.add(this->parameterFootstepMaterial);
 fMODParameterList.add(this->parameterFootstepMaterial2);
 fMODParameterList.add(this->parameterLocalPlayer);
 fMODParameterList.add(this->parameterMeleeHitSurface);
 fMODParameterList.add(this->parameterPlayerHealth);
 fMODParameterList.add(this->parameterShoeType);
 fMODParameterList.add(this->parameterVehicleHitLocation);
 }

 ParameterCharacterMovementSpeed getParameterCharacterMovementSpeed() {
 return this->parameterCharacterMovementSpeed;
 }

 void setMeleeHitSurface(ParameterMeleeHitSurface.Material material) {
 this->parameterMeleeHitSurface.setMaterial(material);
 }

 void setMeleeHitSurface(const std::string& material) {
 try {
 this->parameterMeleeHitSurface.setMaterial(ParameterMeleeHitSurface.Material.valueOf(material);
 } catch (IllegalArgumentException illegalArgumentException) {
 this->parameterMeleeHitSurface.setMaterial(ParameterMeleeHitSurface.Material.Default);
 }
 }

 void setVehicleHitLocation(BaseVehicle vehicle) {
 ParameterVehicleHitLocation.HitLocation hitLocation = ParameterVehicleHitLocation.calculateLocation(vehicle, this->getX(), this->getY(), this->getZ());
 this->parameterVehicleHitLocation.setLocation(hitLocation);
 }

 void updateHeartSound() {
 if (!GameServer.bServer) {
 if (this->isLocalPlayer()) {
 GameSound gameSound = GameSounds.getSound("HeartBeat");
 bool boolean0 = gameSound != nullptr && gameSound.getUserVolume() > 0.0F && this->stats.Panic > 0.0F;
 if (!this->Asleep && boolean0 && GameTime.getInstance().getTrueMultiplier() == 1.0F) {
 this->heartDelay = this->heartDelay - GameTime.getInstance().getMultiplier() / 1.6F;
 if (this->heartEventInstance == 0L || !this->getEmitter().isPlaying(this->heartEventInstance) {
 this->heartEventInstance = this->getEmitter().playSoundImpl("HeartBeat", nullptr);
 this->getEmitter().setVolume(this->heartEventInstance, 0.0F);
 }

 if (this->heartDelay <= 0.0F) {
 this->heartDelayMax = (int)((1.0F - this->stats.Panic / 100.0F * 0.7F) * 25.0F) * 2;
 this->heartDelay = this->heartDelayMax;
 if (this->heartEventInstance != 0L) {
 this->getEmitter().setVolume(this->heartEventInstance, this->stats.Panic / 100.0F);
 }
 }
 } else if (this->heartEventInstance != 0L) {
 this->getEmitter().setVolume(this->heartEventInstance, 0.0F);
 }
 }
 }
 }

 void updateWorldAmbiance() {
 if (!GameServer.bServer) {
 if (this->isLocalPlayer()) {
 if (this->getPlayerNum() == 0 && (this->worldAmbianceInstance == 0L || !this->getEmitter().isPlaying(this->worldAmbianceInstance) {
 this->worldAmbianceInstance = this->getEmitter().playSoundImpl("WorldAmbiance", nullptr);
 this->getEmitter().setVolume(this->worldAmbianceInstance, 1.0F);
 }
 }
 }
 }

 void updateEquippedBaggageContainer() {
 if (!GameServer.bServer) {
 if (this->isLocalPlayer()) {
 InventoryItem item = this->getClothingItem_Back();
 if (item != nullptr && item.IsInventoryContainer()) {
 std::string string0 = item.getSoundParameter("EquippedBaggageContainer");
 this->parameterEquippedBaggageContainer.setContainerType(string0);
 } else {
 item = this->getSecondaryHandItem();
 if (item != nullptr && item.IsInventoryContainer()) {
 std::string string1 = item.getSoundParameter("EquippedBaggageContainer");
 this->parameterEquippedBaggageContainer.setContainerType(string1);
 } else {
 item = this->getPrimaryHandItem();
 if (item != nullptr && item.IsInventoryContainer()) {
 std::string string2 = item.getSoundParameter("EquippedBaggageContainer");
 this->parameterEquippedBaggageContainer.setContainerType(string2);
 } else {
 this->parameterEquippedBaggageContainer.setContainerType(ParameterEquippedBaggageContainer.ContainerType.None);
 }
 }
 }
 }
 }
 }

 void DoFootstepSound(const std::string& type) {
 ParameterCharacterMovementSpeed.MovementType movementType = ParameterCharacterMovementSpeed.MovementType.Walk;
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

 this->parameterCharacterMovementSpeed.setMovementType(movementType);
 super.DoFootstepSound(float0);
 }

 void updateHeavyBreathing() {
 }

 void checkVehicleContainers() {
 std::vector arrayList = this->vehicleContainerData.tempContainers;
 arrayList.clear();
 int int0 = (int)this->getX() - 4;
 int int1 = (int)this->getY() - 4;
 int int2 = (int)this->getX() + 4;
 int int3 = (int)this->getY() + 4;
 int int4 = int0 / 10;
 int int5 = int1 / 10;
 int int6 = (int)Math.ceil(int2 / 10.0F);
 int int7 = (int)Math.ceil(int3 / 10.0F);

 for (int int8 = int5; int8 < int7; int8++) {
 for (int int9 = int4; int9 < int6; int9++) {
 IsoChunk chunk = GameServer.bServer
 ? ServerMap.instance.getChunk(int9, int8)
 : IsoWorld.instance.CurrentCell.getChunkForGridSquare(int9 * 10, int8 * 10, 0);
 if (chunk != nullptr) {
 for (int int10 = 0; int10 < chunk.vehicles.size(); int10++) {
 BaseVehicle vehicle = chunk.vehicles.get(int10);
 VehicleScript vehicleScript = vehicle.getScript();
 if (vehicleScript != nullptr) {
 for (int int11 = 0; int11 < vehicleScript.getPartCount(); int11++) {
 VehicleScript.Part part = vehicleScript.getPart(int11);
 if (part.container != nullptr && part.area != nullptr && vehicle.isInArea(part.area, this) {
 IsoPlayer.VehicleContainer vehicleContainer0 = this->vehicleContainerData.freeContainers.empty()
 ? new IsoPlayer.VehicleContainer()
 : this->vehicleContainerData.freeContainers.pop();
 arrayList.add(vehicleContainer0.set(vehicle, int11);
 }
 }
 }
 }
 }
 }
 }

 if (arrayList.size() != this->vehicleContainerData.containers.size()) {
 this->vehicleContainerData.freeContainers.addAll(this->vehicleContainerData.containers);
 this->vehicleContainerData.containers.clear();
 this->vehicleContainerData.containers.addAll(arrayList);
 LuaEventManager.triggerEvent("OnContainerUpdate");
 } else {
 for (int int12 = 0; int12 < arrayList.size(); int12++) {
 IsoPlayer.VehicleContainer vehicleContainer1 = (IsoPlayer.VehicleContainer)arrayList.get(int12);
 IsoPlayer.VehicleContainer vehicleContainer2 = this->vehicleContainerData.containers.get(int12);
 if (!vehicleContainer1 == vehicleContainer2) {
 this->vehicleContainerData.freeContainers.addAll(this->vehicleContainerData.containers);
 this->vehicleContainerData.containers.clear();
 this->vehicleContainerData.containers.addAll(arrayList);
 LuaEventManager.triggerEvent("OnContainerUpdate");
 break;
 }
 }
 }
 }

 void setJoypadIgnoreAimUntilCentered(bool ignore) {
 this->bJoypadIgnoreAimUntilCentered = ignore;
 }

 bool canSeePlayerStats() {
 return this->accessLevel != "";
 }

 ByteBufferWriter createPlayerStats(ByteBufferWriter b, const std::string& adminUsername) {
 b.putShort(this->getOnlineID());
 b.putUTF(adminUsername);
 b.putUTF(this->getDisplayName());
 b.putUTF(this->getDescriptor().getForename());
 b.putUTF(this->getDescriptor().getSurname());
 b.putUTF(this->getDescriptor().getProfession());
 if (!StringUtils.isNullOrEmpty(this->getTagPrefix())) {
 b.putByte((byte)1);
 b.putUTF(this->getTagPrefix());
 } else {
 b.putByte((byte)0);
 }

 b.putBoolean(this->isAllChatMuted());
 b.putFloat(this->getTagColor().r);
 b.putFloat(this->getTagColor().g);
 b.putFloat(this->getTagColor().b);
 b.putByte((byte)(this->showTag ? 1 : 0);
 b.putByte((byte)(this->factionPvp ? 1 : 0);
 return b;
 }

 std::string setPlayerStats(ByteBuffer bb, const std::string& adminUsername) {
 std::string string0 = GameWindow.ReadString(bb);
 std::string string1 = GameWindow.ReadString(bb);
 std::string string2 = GameWindow.ReadString(bb);
 std::string string3 = GameWindow.ReadString(bb);
 std::string string4 = "";
 if (bb.get() == 1) {
 string4 = GameWindow.ReadString(bb);
 }

 bool boolean0 = bb.get() == 1;
 float float0 = bb.getFloat();
 float float1 = bb.getFloat();
 float float2 = bb.getFloat();
 std::string string5 = "";
 this->setTagColor(new ColorInfo(float0, float1, float2, 1.0F);
 this->setTagPrefix(string4);
 this->showTag = bb.get() == 1;
 this->factionPvp = bb.get() == 1;
 if (!string1 == this->getDescriptor().getForename())) {
 if (GameServer.bServer) {
 string5 = adminUsername + " Changed " + string0 + " forname in " + string1;
 } else {
 string5 = "Changed your forname in " + string1;
 }
 }

 this->getDescriptor().setForename(string1);
 if (!string2 == this->getDescriptor().getSurname())) {
 if (GameServer.bServer) {
 string5 = adminUsername + " Changed " + string0 + " surname in " + string2;
 } else {
 string5 = "Changed your surname in " + string2;
 }
 }

 this->getDescriptor().setSurname(string2);
 if (!string3 == this->getDescriptor().getProfession())) {
 if (GameServer.bServer) {
 string5 = adminUsername + " Changed " + string0 + " profession to " + string3;
 } else {
 string5 = "Changed your profession in " + string3;
 }
 }

 this->getDescriptor().setProfession(string3);
 if (!this->getDisplayName() == string0) {
 if (GameServer.bServer) {
 string5 = adminUsername + " Changed display name \"" + this->getDisplayName() + "\" to \"" + string0 + "\"";
 ServerWorldDatabase.instance.updateDisplayName(this->username, string0);
 } else {
 string5 = "Changed your display name to " + string0;
 }

 this->setDisplayName(string0);
 }

 if (boolean0 != this->isAllChatMuted()) {
 if (boolean0) {
 if (GameServer.bServer) {
 string5 = adminUsername + " Banned " + string0 + " from using /all chat";
 } else {
 string5 = "Banned you from using /all chat";
 }
 } else if (GameServer.bServer) {
 string5 = adminUsername + " Allowed " + string0 + " to use /all chat";
 } else {
 string5 = "Now allowed you to use /all chat";
 }
 }

 this->setAllChatMuted(boolean0);
 if (GameServer.bServer && !"" == string5) {
 LoggerManager.getLogger("admin").write(string5);
 }

 if (GameClient.bClient) {
 LuaEventManager.triggerEvent("OnMiniScoreboardUpdate");
 }

 return string5;
 }

 bool isAllChatMuted() {
 return this->allChatMuted;
 }

 void setAllChatMuted(bool _allChatMuted) {
 this->allChatMuted = _allChatMuted;
 }

 std::string getAccessLevel() {
 std::string string = this->accessLevel;
 switch (string) {
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

 bool isAccessLevel(const std::string& level) {
 return this->getAccessLevel().equalsIgnoreCase(level);
 }

 void setAccessLevel(const std::string& newLvl) {
 uint8_t byte0 = PlayerType.fromString(newLvl.trim().toLowerCase());
 if (byte0 == 1) {
 GameClient.SendCommandToServer("/setaccesslevel \"" + this->username + "\" \"none\"");
 } else {
 GameClient.SendCommandToServer("/setaccesslevel \"" + this->username + "\" \"" + PlayerType.toString(byte0) + "\"");
 }
 }

 void addMechanicsItem(const std::string& itemid, VehiclePart part, long milli) {
 uint8_t byte0 = 1;
 uint8_t byte1 = 1;
 if (this->mechanicsItem.get(Long.parseLong(itemid) == nullptr) {
 if (part.getTable("uninstall") != nullptr && part.getTable("uninstall").rawget("skills") != nullptr) {
 String[] strings = ((String)part.getTable("uninstall").rawget("skills")).split(";");

 for (auto& string : strings) if (string.contains("Mechanics")) {
 int int0 = Integer.parseInt(string.split(":")[1]);
 if (int0 >= 6) {
 byte0 = 3;
 byte1 = 7;
 } else if (int0 >= 4) {
 byte0 = 3;
 byte1 = 5;
 } else if (int0 >= 2) {
 byte0 = 2;
 byte1 = 4;
 } else if (Rand.Next(3) == 0) {
 byte0 = 2;
 byte1 = 2;
 }
 }
 }
 }

 this->getXp().AddXP(PerkFactory.Perks.Mechanics, (float)Rand.Next((int)byte0, (int)byte1);
 }

 this->mechanicsItem.put(Long.parseLong(itemid), milli);
 }

 void setPosition(float ax, float ay, float az) {
 this->setX(ax);
 this->setY(ay);
 this->setZ(az);
 }

 void updateTemperatureCheck() {
 int int0 = this->Moodles.getMoodleLevel(MoodleType.Hypothermia);
 if (this->hypothermiaCache == -1 || this->hypothermiaCache != int0) {
 if (int0 >= 3 && int0 > this->hypothermiaCache && this->isAsleep() && !this->ForceWakeUp) {
 this->forceAwake();
 }

 this->hypothermiaCache = int0;
 }

 int int1 = this->Moodles.getMoodleLevel(MoodleType.Hyperthermia);
 if (this->hyperthermiaCache == -1 || this->hyperthermiaCache != int1) {
 if (int1 >= 3 && int1 > this->hyperthermiaCache && this->isAsleep() && !this->ForceWakeUp) {
 this->forceAwake();
 }

 this->hyperthermiaCache = int1;
 }
 }

 float getZombieRelevenceScore(IsoZombie z) {
 if (z.getCurrentSquare() == nullptr) {
 return -10000.0F;
 } else {
 float float0 = 0.0F;
 if (z.getCurrentSquare().getCanSee(this->PlayerIndex) {
 float0 += 100.0F;
 } else if (z.getCurrentSquare().isCouldSee(this->PlayerIndex) {
 float0 += 10.0F;
 }

 if (z.getCurrentSquare().getRoom() != nullptr && this->current.getRoom() == nullptr) {
 float0 -= 20.0F;
 }

 if (z.getCurrentSquare().getRoom() == nullptr && this->current.getRoom() != nullptr) {
 float0 -= 20.0F;
 }

 if (z.getCurrentSquare().getRoom() != this->current.getRoom()) {
 float0 -= 20.0F;
 }

 float float1 = z.DistTo(this);
 float0 -= float1;
 if (float1 < 20.0F) {
 float0 += 300.0F;
 }

 if (float1 < 15.0F) {
 float0 += 300.0F;
 }

 if (float1 < 10.0F) {
 float0 += 1000.0F;
 }

 if (z.getTargetAlpha() < 1.0F && float0 > 0.0F) {
 float0 *= z.getTargetAlpha();
 }

 return float0;
 }
 }

 BaseVisual getVisual() {
 return this->humanVisual;
 }

 HumanVisual getHumanVisual() {
 return this->humanVisual;
 }

 ItemVisuals getItemVisuals() {
 return this->itemVisuals;
 }

 void getItemVisuals(ItemVisuals _itemVisuals) {
 if (!this->bRemote) {
 this->getWornItems().getItemVisuals(_itemVisuals);
 } else {
 _itemVisuals.clear();
 _itemVisuals.addAll(this->itemVisuals);
 }
 }

 void dressInNamedOutfit(const std::string& outfitName) {
 this->getHumanVisual().dressInNamedOutfit(outfitName, this->itemVisuals);
 this->onClothingOutfitPreviewChanged();
 }

 void dressInClothingItem(const std::string& itemGUID) {
 this->getHumanVisual().dressInClothingItem(itemGUID, this->itemVisuals);
 this->onClothingOutfitPreviewChanged();
 }

 void onClothingOutfitPreviewChanged() {
 if (this->isLocalPlayer()) {
 this->getInventory().clear();
 this->wornItems.setFromItemVisuals(this->itemVisuals);
 this->wornItems.addItemsToItemContainer(this->getInventory());
 this->itemVisuals.clear();
 this->resetModel();
 this->onWornItemsChanged();
 }
 }

 void onWornItemsChanged() {
 this->parameterShoeType.setShoeType(nullptr);
 }

 void actionStateChanged(ActionContext sender) {
 super.actionStateChanged(sender);
 }

 Vector2 getLastAngle() {
 return this->lastAngle;
 }

 void setLastAngle(Vector2 _lastAngle) {
 this->lastAngle.set(_lastAngle);
 }

 int getDialogMood() {
 return this->DialogMood;
 }

 void setDialogMood(int _DialogMood) {
 this->DialogMood = _DialogMood;
 }

 int getPing() {
 return this->ping;
 }

 void setPing(int _ping) {
 this->ping = _ping;
 }

 IsoMovingObject getDragObject() {
 return this->DragObject;
 }

 void setDragObject(IsoMovingObject _DragObject) {
 this->DragObject = _DragObject;
 }

 float getAsleepTime() {
 return this->AsleepTime;
 }

 void setAsleepTime(float _AsleepTime) {
 this->AsleepTime = _AsleepTime;
 }

 public Stack<IsoMovingObject> getSpottedList() {
 return this->spottedList;
 }

 int getTicksSinceSeenZombie() {
 return this->TicksSinceSeenZombie;
 }

 void setTicksSinceSeenZombie(int _TicksSinceSeenZombie) {
 this->TicksSinceSeenZombie = _TicksSinceSeenZombie;
 }

 bool isWaiting() {
 return this->Waiting;
 }

 void setWaiting(bool _Waiting) {
 this->Waiting = _Waiting;
 }

 IsoSurvivor getDragCharacter() {
 return this->DragCharacter;
 }

 void setDragCharacter(IsoSurvivor _DragCharacter) {
 this->DragCharacter = _DragCharacter;
 }

 float getHeartDelay() {
 return this->heartDelay;
 }

 void setHeartDelay(float _heartDelay) {
 this->heartDelay = _heartDelay;
 }

 float getHeartDelayMax() {
 return this->heartDelayMax;
 }

 void setHeartDelayMax(int _heartDelayMax) {
 this->heartDelayMax = _heartDelayMax;
 }

 double getHoursSurvived() {
 return this->HoursSurvived;
 }

 void setHoursSurvived(double hrs) {
 this->HoursSurvived = hrs;
 }

 float getMaxWeightDelta() {
 return this->maxWeightDelta;
 }

 void setMaxWeightDelta(float _maxWeightDelta) {
 this->maxWeightDelta = _maxWeightDelta;
 }

 std::string getForname() {
 return this->Forname;
 }

 void setForname(const std::string& _Forname) {
 this->Forname = _Forname;
 }

 std::string getSurname() {
 return this->Surname;
 }

 void setSurname(const std::string& _Surname) {
 this->Surname = _Surname;
 }

 bool isbChangeCharacterDebounce() {
 return this->bChangeCharacterDebounce;
 }

 void setbChangeCharacterDebounce(bool _bChangeCharacterDebounce) {
 this->bChangeCharacterDebounce = _bChangeCharacterDebounce;
 }

 int getFollowID() {
 return this->followID;
 }

 void setFollowID(int _followID) {
 this->followID = _followID;
 }

 bool isbSeenThisFrame() {
 return this->bSeenThisFrame;
 }

 void setbSeenThisFrame(bool _bSeenThisFrame) {
 this->bSeenThisFrame = _bSeenThisFrame;
 }

 bool isbCouldBeSeenThisFrame() {
 return this->bCouldBeSeenThisFrame;
 }

 void setbCouldBeSeenThisFrame(bool _bCouldBeSeenThisFrame) {
 this->bCouldBeSeenThisFrame = _bCouldBeSeenThisFrame;
 }

 float getTimeSinceLastStab() {
 return this->timeSinceLastStab;
 }

 void setTimeSinceLastStab(float _timeSinceLastStab) {
 this->timeSinceLastStab = _timeSinceLastStab;
 }

 public Stack<IsoMovingObject> getLastSpotted() {
 return this->LastSpotted;
 }

 void setLastSpotted(Stack<IsoMovingObject> _LastSpotted) {
 this->LastSpotted = _LastSpotted;
 }

 int getClearSpottedTimer() {
 return this->ClearSpottedTimer;
 }

 void setClearSpottedTimer(int _ClearSpottedTimer) {
 this->ClearSpottedTimer = _ClearSpottedTimer;
 }

 bool IsRunning() {
 return this->isRunning();
 }

 void InitSpriteParts() {
 }

 bool IsAiming() {
 return this->isAiming();
 }

 std::string getTagPrefix() {
 return this->tagPrefix;
 }

 void setTagPrefix(const std::string& newTag) {
 this->tagPrefix = newTag;
 }

 ColorInfo getTagColor() {
 return this->tagColor;
 }

 void setTagColor(ColorInfo _tagColor) {
 this->tagColor.set(_tagColor);
 }

 int getTransactionID() {
 return this->transactionID;
 }

 void setTransactionID(int _transactionID) {
 this->transactionID = _transactionID;
 }

 std::string getDisplayName() {
 if (GameClient.bClient) {
 if (this->displayName.empty() || this->displayName == "")) {
 this->displayName = this->getUsername();
 }
 } else if (!GameServer.bServer) {
 this->displayName = this->getUsername();
 }

 return this->displayName;
 }

 void setDisplayName(const std::string& _displayName) {
 this->displayName = _displayName;
 }

 bool isSeeNonPvpZone() {
 return this->seeNonPvpZone || DebugOptions.instance.MultiplayerSeeNonPvpZones.getValue();
 }

 void setSeeNonPvpZone(bool _seeNonPvpZone) {
 this->seeNonPvpZone = _seeNonPvpZone;
 }

 bool isShowTag() {
 return this->showTag;
 }

 void setShowTag(bool show) {
 this->showTag = show;
 }

 bool isFactionPvp() {
 return this->factionPvp;
 }

 void setFactionPvp(bool pvp) {
 this->factionPvp = pvp;
 }

 bool isForceAim() {
 return this->forceAim;
 }

 void setForceAim(bool _forceAim) {
 this->forceAim = _forceAim;
 }

 bool toggleForceAim() {
 this->forceAim = !this->forceAim;
 return this->forceAim;
 }

 bool isForceSprint() {
 return this->forceSprint;
 }

 void setForceSprint(bool _forceSprint) {
 this->forceSprint = _forceSprint;
 }

 bool toggleForceSprint() {
 this->forceSprint = !this->forceSprint;
 return this->forceSprint;
 }

 bool isForceRun() {
 return this->forceRun;
 }

 void setForceRun(bool _forceRun) {
 this->forceRun = _forceRun;
 }

 bool toggleForceRun() {
 this->forceRun = !this->forceRun;
 return this->forceRun;
 }

 bool isDeaf() {
 return this->Traits.Deaf.isSet();
 }

 bool isForceOverrideAnim() {
 return this->forceOverrideAnim;
 }

 void setForceOverrideAnim(bool forceOverride) {
 this->forceOverrideAnim = forceOverride;
 }

 long getMechanicsItem(const std::string& itemId) {
 return this->mechanicsItem.get(Long.parseLong(itemId);
 }

 bool isWearingNightVisionGoggles() {
 return this->isWearingNightVisionGoggles;
 }

 void setWearingNightVisionGoggles(bool b) {
 this->isWearingNightVisionGoggles = b;
 }

 void OnAnimEvent(AnimLayer sender, AnimEvent event) {
 super.OnAnimEvent(sender, event);
 if (!this->CharacterActions.empty()) {
 BaseAction baseAction = this->CharacterActions.get(0);
 baseAction.OnAnimEvent(event);
 }
 }

 /**
 * Callback from ModelManager.Add/Remove functions.
 * 
 * @param modelManager Event sender.
 * @param isCulled Whether or not this object is culled from the visible scene or not.
 */
 void onCullStateChanged(ModelManager modelManager, bool isCulled) {
 super.onCullStateChanged(modelManager, isCulled);
 if (!isCulled) {
 DebugFileWatcher.instance.add(this->m_setClothingTriggerWatcher);
 } else {
 DebugFileWatcher.instance.remove(this->m_setClothingTriggerWatcher);
 }
 }

 bool isTimedActionInstant() {
 return (GameClient.bClient || GameServer.bServer) && this->isAccessLevel("None") ? false : super.isTimedActionInstant();
 }

 bool isSkeleton() {
 return false;
 }

 void addWorldSoundUnlessInvisible(int radius, int volume, bool bStressHumans) {
 if (!this->isGhostMode()) {
 super.addWorldSoundUnlessInvisible(radius, volume, bStressHumans);
 }
 }

 void updateFootInjuries() {
 InventoryItem item = this->getWornItems().getItem("Shoes");
 if (item.empty() || item.getCondition() <= 0) {
 if (this->getCurrentSquare() != nullptr) {
 if (this->getCurrentSquare().getBrokenGlass() != nullptr) {
 BodyPartType bodyPartType0 = BodyPartType.FromIndex(
 Rand.Next(BodyPartType.ToIndex(BodyPartType.Foot_L), BodyPartType.ToIndex(BodyPartType.Foot_R) + 1)
 );
 BodyPart bodyPart0 = this->getBodyDamage().getBodyPart(bodyPartType0);
 bodyPart0.generateDeepShardWound();
 }

 uint8_t byte0 = 0;
 bool boolean0 = false;
 if (this->getCurrentSquare().getZone() != nullptr
 && (this->getCurrentSquare().getZone().getType() == "Forest") || this->getCurrentSquare().getZone().getType() == "DeepForest"))) {
 boolean0 = true;
 }

 IsoObject object = this->getCurrentSquare().getFloor();
 if (object != nullptr && object.getSprite() != nullptr && object.getSprite().getName() != nullptr) {
 std::string string = object.getSprite().getName();
 if (string.contains("blends_natural_01") && boolean0) {
 byte0 = 2;
 } else if (!string.contains("blends_natural_01") && this->getCurrentSquare().getBuilding() == nullptr) {
 byte0 = 1;
 }
 }

 if (byte0 != 0) {
 if (this->isWalking && !this->isRunning() && !this->isSprinting()) {
 this->footInjuryTimer += byte0;
 } else if (this->isRunning() && !this->isSprinting()) {
 this->footInjuryTimer += byte0 + 2;
 } else {
 if (!this->isSprinting()) {
 if (this->footInjuryTimer > 0 && Rand.Next(3) == 0) {
 this->footInjuryTimer--;
 }

 return;
 }

 this->footInjuryTimer += byte0 + 5;
 }

 if (Rand.Next(Rand.AdjustForFramerate(8500 - this->footInjuryTimer) <= 0) {
 this->footInjuryTimer = 0;
 BodyPartType bodyPartType1 = BodyPartType.FromIndex(
 Rand.Next(BodyPartType.ToIndex(BodyPartType.Foot_L), BodyPartType.ToIndex(BodyPartType.Foot_R) + 1)
 );
 BodyPart bodyPart1 = this->getBodyDamage().getBodyPart(bodyPartType1);
 if (bodyPart1.getScratchTime() > 30.0F) {
 if (!bodyPart1.isCut()) {
 bodyPart1.setCut(true);
 bodyPart1.setCutTime(Rand.Next(1.0F, 3.0F);
 } else {
 bodyPart1.setCutTime(bodyPart1.getCutTime() + Rand.Next(1.0F, 3.0F);
 }
 } else {
 if (!bodyPart1.scratched()) {
 bodyPart1.setScratched(true, true);
 bodyPart1.setScratchTime(Rand.Next(1.0F, 3.0F);
 } else {
 bodyPart1.setScratchTime(bodyPart1.getScratchTime() + Rand.Next(1.0F, 3.0F);
 }

 if (bodyPart1.getScratchTime() > 20.0F && bodyPart1.getBleedingTime() == 0.0F) {
 bodyPart1.setBleedingTime(Rand.Next(3.0F, 10.0F);
 }
 }
 }
 }
 }
 }
 }

 int getMoodleLevel(MoodleType type) {
 return this->getMoodles().getMoodleLevel(type);
 }

 bool isAttackStarted() {
 return this->attackStarted;
 }

 bool isBehaviourMoving() {
 return this->hasPath() || super.isBehaviourMoving();
 }

 bool isJustMoved() {
 return this->JustMoved;
 }

 void setJustMoved(bool val) {
 this->JustMoved = val;
 }

 bool isPlayerMoving() {
 return this->m_isPlayerMoving;
 }

 float getTimedActionTimeModifier() {
 return this->getBodyDamage().getThermoregulator() != nullptr ? this->getBodyDamage().getThermoregulator().getTimedActionTimeModifier() : 1.0F;
 }

 bool isLookingWhileInVehicle() {
 return this->getVehicle() != nullptr && this->bLookingWhileInVehicle;
 }

 void setInitiateAttack(bool initiate) {
 this->initiateAttack = initiate;
 }

 bool isIgnoreInputsForDirection() {
 return this->ignoreInputsForDirection;
 }

 void setIgnoreInputsForDirection(bool _ignoreInputsForDirection) {
 this->ignoreInputsForDirection = _ignoreInputsForDirection;
 }

 bool isIgnoreContextKey() {
 return this->ignoreContextKey;
 }

 void setIgnoreContextKey(bool _ignoreContextKey) {
 this->ignoreContextKey = _ignoreContextKey;
 }

 bool isIgnoreAutoVault() {
 return this->ignoreAutoVault;
 }

 void setIgnoreAutoVault(bool _ignoreAutoVault) {
 this->ignoreAutoVault = _ignoreAutoVault;
 }

 bool isAllowSprint() {
 return this->allowSprint;
 }

 void setAllowSprint(bool _allowSprint) {
 this->allowSprint = _allowSprint;
 }

 bool isAllowRun() {
 return this->allowRun;
 }

 void setAllowRun(bool _allowRun) {
 this->allowRun = _allowRun;
 }

 std::string getAttackType() {
 return this->attackType;
 }

 void setAttackType(const std::string& _attackType) {
 this->attackType = _attackType;
 }

 void clearNetworkEvents() {
 this->networkAI.events.clear();
 this->clearVariable("PerformingAction");
 this->clearVariable("IsPerformingAnAction");
 this->overridePrimaryHandModel = nullptr;
 this->overrideSecondaryHandModel = nullptr;
 this->resetModelNextFrame();
 }

 bool isCanSeeAll() {
 return this->canSeeAll;
 }

 void setCanSeeAll(bool b) {
 this->canSeeAll = b;
 }

 bool isNetworkTeleportEnabled() {
 return NetworkTeleport.enable;
 }

 void setNetworkTeleportEnabled(bool b) {
 NetworkTeleport.enable = b;
 }

 bool isCheatPlayerSeeEveryone() {
 return DebugOptions.instance.CheatPlayerSeeEveryone.getValue();
 }

 float getRelevantAndDistance(float x, float y, float RelevantRange) {
 return Math.abs(this->x - x) <= RelevantRange * 10.0F && Math.abs(this->y - y) <= RelevantRange * 10.0F
 ? IsoUtils.DistanceTo(this->x, this->y, x, y)
 : Float.POSITIVE_INFINITY;
 }

 bool isCanHearAll() {
 return this->canHearAll;
 }

 void setCanHearAll(bool b) {
 this->canHearAll = b;
 }

 public ArrayList<String> getAlreadyReadBook() {
 return this->alreadyReadBook;
 }

 void setMoodleCantSprint(bool b) {
 this->MoodleCantSprint = b;
 }

 void setAttackFromBehind(bool _attackFromBehind) {
 this->attackFromBehind = _attackFromBehind;
 }

 bool isAttackFromBehind() {
 return this->attackFromBehind;
 }

 float getDamageFromHitByACar(float vehicleSpeed) {
 float float0 = 1.0F;
 switch (SandboxOptions.instance.DamageToPlayerFromHitByACar.getValue()) {
 case 1:
 float0 = 0.0F;
 break;
 case 2:
 float0 = 0.5F;
 case 3:
 default:
 break;
 case 4:
 float0 = 2.0F;
 break;
 case 5:
 float0 = 5.0F;
 }

 float float1 = vehicleSpeed * float0;
 if (DebugOptions.instance.MultiplayerCriticalHit.getValue()) {
 float1 += 10.0F;
 }

 if (float1 > 0.0F) {
 int int0 = (int)(2.0F + float1 * 0.07F);

 for (int int1 = 0; int1 < int0; int1++) {
 int int2 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Hand_L), BodyPartType.ToIndex(BodyPartType.MAX);
 BodyPart bodyPart = this->getBodyDamage().getBodyPart(BodyPartType.FromIndex(int2);
 float float2 = Math.max(Rand.Next(float1 - 15.0F, float1), 5.0F);
 if (this->Traits.FastHealer.isSet()) {
 float2 = (float)(float2 * 0.8);
 } else if (this->Traits.SlowHealer.isSet()) {
 float2 = (float)(float2 * 1.2);
 }

 switch (SandboxOptions.instance.InjurySeverity.getValue()) {
 case 1:
 float2 *= 0.5F;
 break;
 case 3:
 float2 *= 1.5F;
 }

 float2 = (float)(float2 * 0.9);
 bodyPart.AddDamage(float2);
 if (float2 > 40.0F && Rand.Next(12) == 0) {
 bodyPart.generateDeepWound();
 }

 if (float2 > 10.0F && Rand.Next(100) <= 10 && SandboxOptions.instance.BoneFracture.getValue()) {
 bodyPart.setFractureTime(Rand.Next(Rand.Next(10.0F, float2 + 10.0F), Rand.Next(float2 + 20.0F, float2 + 30.0F);
 }

 if (float2 > 30.0F
 && Rand.Next(100) <= 80
 && SandboxOptions.instance.BoneFracture.getValue()
 && int2 == BodyPartType.ToIndex(BodyPartType.Head) {
 bodyPart.setFractureTime(Rand.Next(Rand.Next(10.0F, float2 + 10.0F), Rand.Next(float2 + 20.0F, float2 + 30.0F);
 }

 if (float2 > 10.0F
 && Rand.Next(100) <= 60
 && SandboxOptions.instance.BoneFracture.getValue()
 && int2 > BodyPartType.ToIndex(BodyPartType.Groin) {
 bodyPart.setFractureTime(Rand.Next(Rand.Next(10.0F, float2 + 20.0F), Rand.Next(float2 + 30.0F, float2 + 40.0F);
 }
 }

 this->getBodyDamage().Update();
 }

 this->addBlood(vehicleSpeed);
 if (GameClient.bClient && this->isLocal()) {
 this->updateMovementRates();
 GameClient.sendPlayerInjuries(this);
 GameClient.sendPlayerDamage(this);
 }

 return float1;
 }

 float Hit(BaseVehicle vehicle, float speed, bool isHitFromBehind, float hitDirX, float hitDirY) {
 float float0 = this->doBeatenVehicle(speed);
 super.Hit(vehicle, speed, isHitFromBehind, hitDirX, hitDirY);
 return float0;
 }

 void Kill(IsoGameCharacter killer) {
 if (!this->isOnKillDone()) {
 super.Kill(killer);
 this->getBodyDamage().setOverallBodyHealth(0.0F);
 if (DebugOptions.instance.MultiplayerPlayerZombie.getValue()) {
 this->getBodyDamage().setInfectionLevel(100.0F);
 }

 if (killer.empty()) {
 this->DoDeath(nullptr, nullptr);
 } else {
 this->DoDeath(killer.getUseHandWeapon(), killer);
 }

 if (GameClient.bClient) {
 ClientPlayerDB.getInstance().clientSendNetworkPlayerInt(this);
 }
 }
 }

 bool shouldDoInventory() {
 return this->isLocalPlayer();
 }

 void becomeCorpse() {
 if (!this->isOnDeathDone()) {
 if (this->shouldBecomeCorpse() || this->isLocalPlayer()) {
 super.becomeCorpse();
 if (GameClient.bClient && this->shouldDoInventory()) {
 GameClient.sendPlayerDeath(this);
 }

 if (!GameClient.bClient) {
 IsoDeadBody deadBody = new IsoDeadBody(this);
 if (this->shouldBecomeZombieAfterDeath()) {
 deadBody.reanimateLater();
 }

 if (GameServer.bServer) {
 GameServer.sendBecomeCorpse(deadBody);
 }
 }
 }
 }
 }

 void preupdate() {
 if (GameClient.bClient) {
 this->networkAI.updateHitVehicle();
 if (!this->isLocal() && this->isKnockedDown() && !this->isOnFloor()) {
 HitReactionNetworkAI hitReactionNetworkAI = this->getHitReactionNetworkAI();
 if (hitReactionNetworkAI.isSetup() && !hitReactionNetworkAI.isStarted()) {
 hitReactionNetworkAI.start();
 }
 }
 }

 super.preupdate();
 }

 HitReactionNetworkAI getHitReactionNetworkAI() {
 return this->networkAI.hitReaction;
 }

 NetworkCharacterAI getNetworkCharacterAI() {
 return this->networkAI;
 }

 void setFitnessSpeed() {
 this->clearVariable("FitnessStruggle");
 float float0 = this->getPerkLevel(PerkFactory.Perks.Fitness) / 5.0F / 1.1F - this->getMoodleLevel(MoodleType.Endurance) / 20.0F;
 if (float0 > 1.5F) {
 float0 = 1.5F;
 }

 if (float0 < 0.85F) {
 float0 = 1.0F;
 this->setVariable("FitnessStruggle", true);
 }

 this->setVariable("FitnessSpeed", float0);
 }

 bool isLocal() {
 return super.isLocal() || this->isLocalPlayer();
 }

 bool isClimbOverWallSuccess() {
 return this->climbOverWallSuccess;
 }

 void setClimbOverWallSuccess(bool _climbOverWallSuccess) {
 this->climbOverWallSuccess = _climbOverWallSuccess;
 }

 bool isClimbOverWallStruggle() {
 return this->climbOverWallStruggle;
 }

 void setClimbOverWallStruggle(bool _climbOverWallStruggle) {
 this->climbOverWallStruggle = _climbOverWallStruggle;
 }

 bool isVehicleCollisionActive(BaseVehicle testVehicle) {
 if (!super.isVehicleCollisionActive(testVehicle) {
 return false;
 } else if (this->isGodMod()) {
 return false;
 } else {
 IsoPlayer player = GameClient.IDToPlayerMap.get(this->vehicle4testCollision.getNetPlayerId());
 if (!SwipeStatePlayer.checkPVP(player, this) {
 return false;
 } else if (SandboxOptions.instance.DamageToPlayerFromHitByACar.getValue() < 1) {
 return false;
 } else {
 return this->getVehicle() == testVehicle
 ? false
 : !this->isCurrentState(PlayerFallDownState.instance())
 && !this->isCurrentState(PlayerFallingState.instance())
 && !this->isCurrentState(PlayerKnockedDown.instance());
 }
 }
 }

 bool isShowMPInfos() {
 return this->showMPInfos;
 }

 void setShowMPInfos(bool b) {
 this->showMPInfos = b;
 }

 static class InputState {
 bool bMelee;
 bool isAttacking;
 bool bRunning;
 bool bSprinting;
 bool isAiming;
 bool isCharging;
 bool isChargingLT;
 }

 static class MoveVars {
 float moveX;
 float moveY;
 float strafeX;
 float strafeY;
 IsoDirections NewFacing;
 }

 private static class VehicleContainer {
 BaseVehicle vehicle;
 int containerIndex;

 public IsoPlayer.VehicleContainer set(BaseVehicle vehiclex, int int0) {
 this->vehicle = vehiclex;
 this->containerIndex = int0;
 return this;
 }

 bool equals(void* object) {
 return object instanceof IsoPlayer.VehicleContainer
 && this->vehicle == ((IsoPlayer.VehicleContainer)object).vehicle
 && this->containerIndex == ((IsoPlayer.VehicleContainer)object).containerIndex;
 }
 }

 private static class VehicleContainerData {
 ArrayList<IsoPlayer.VehicleContainer> tempContainers = std::make_unique<ArrayList<>>();
 ArrayList<IsoPlayer.VehicleContainer> containers = std::make_unique<ArrayList<>>();
 Stack<IsoPlayer.VehicleContainer> freeContainers = std::make_unique<Stack<>>();
 }

 private static class s_performance {
 static const PerformanceProfileProbe postUpdate = new PerformanceProfileProbe("IsoPlayer.postUpdate");
 static const PerformanceProfileProbe highlightRangedTargets = new PerformanceProfileProbe("IsoPlayer.highlightRangedTargets");
 static const PerformanceProfileProbe update = new PerformanceProfileProbe("IsoPlayer.update");
 }
}
} // namespace characters
} // namespace zombie
