#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_DESCRIPTION.h"
#include "fmod/fmod/IFMODParameterUpdater.h"
#include "gnu/trove/map/hash/THashMap.h"
#include "org/joml/Vector3f.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/AmbientStreamManager.h"
#include "zombie/DebugFileWatcher.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaHookManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/PersistentOutfits.h"
#include "zombie/PredicatedFileWatcher.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SoundManager.h"
#include "zombie/SystemDisabler.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/ZomboidGlobals.h"
#include "zombie/ai/GameCharacterAIBrain.h"
#include "zombie/ai/MapKnowledge.h"
#include "zombie/ai/State.h"
#include "zombie/ai/StateMachine.h"
#include "zombie/ai/astar/AStarPathFinder.h"
#include "zombie/ai/astar/AStarPathFinderResult.h"
#include "zombie/ai/sadisticAIDirector/SleepingEventData.h"
#include "zombie/ai/states/AttackNetworkState.h"
#include "zombie/ai/states/AttackState.h"
#include "zombie/ai/states/BumpedState.h"
#include "zombie/ai/states/ClimbDownSheetRopeState.h"
#include "zombie/ai/states/ClimbOverFenceState.h"
#include "zombie/ai/states/ClimbOverWallState.h"
#include "zombie/ai/states/ClimbSheetRopeState.h"
#include "zombie/ai/states/ClimbThroughWindowState.h"
#include "zombie/ai/states/CloseWindowState.h"
#include "zombie/ai/states/CollideWithWallState.h"
#include "zombie/ai/states/FakeDeadZombieState.h"
#include "zombie/ai/states/IdleState.h"
#include "zombie/ai/states/LungeNetworkState.h"
#include "zombie/ai/states/LungeState.h"
#include "zombie/ai/states/OpenWindowState.h"
#include "zombie/ai/states/PathFindState.h"
#include "zombie/ai/states/PlayerFallDownState.h"
#include "zombie/ai/states/PlayerGetUpState.h"
#include "zombie/ai/states/PlayerHitReactionPVPState.h"
#include "zombie/ai/states/PlayerHitReactionState.h"
#include "zombie/ai/states/PlayerKnockedDown.h"
#include "zombie/ai/states/PlayerOnGroundState.h"
#include "zombie/ai/states/SmashWindowState.h"
#include "zombie/ai/states/StaggerBackState.h"
#include "zombie/ai/states/SwipeStatePlayer.h"
#include "zombie/ai/states/ThumpState.h"
#include "zombie/ai/states/WalkTowardState.h"
#include "zombie/ai/states/ZombieFallDownState.h"
#include "zombie/ai/states/ZombieFallingState.h"
#include "zombie/ai/states/ZombieHitReactionState.h"
#include "zombie/ai/states/ZombieOnGroundState.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/audio/FMODParameter.h"
#include "zombie/audio/FMODParameterList.h"
#include "zombie/audio/GameSoundClip.h"
#include "zombie/audio/parameters/ParameterZombieState.h"
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characterTextures/BloodClothingType.h"
#include "zombie/characters/AttachedItems/AttachedItem.h"
#include "zombie/characters/AttachedItems/AttachedItems.h"
#include "zombie/characters/AttachedItems/AttachedLocationGroup.h"
#include "zombie/characters/AttachedItems/AttachedLocations.h"
#include "zombie/characters/BodyDamage/BodyDamage.h"
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/BodyDamage/BodyPartLast.h"
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/BodyDamage/Metabolics.h"
#include "zombie/characters/BodyDamage/Nutrition.h"
#include "zombie/characters/CharacterTimedActions/BaseAction.h"
#include "zombie/characters/CharacterTimedActions/LuaTimedActionNew.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/characters/Moodles/Moodles.h"
#include "zombie/characters/WornItems/BodyLocationGroup.h"
#include "zombie/characters/WornItems/BodyLocations.h"
#include "zombie/characters/WornItems/WornItem.h"
#include "zombie/characters/WornItems/WornItems.h"
#include "zombie/characters/action/ActionContext.h"
#include "zombie/characters/action/ActionState.h"
#include "zombie/characters/action/ActionStateSnapshot.h"
#include "zombie/characters/action/IActionStateChanged.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/characters/traits/TraitCollection.h"
#include "zombie/characters/traits/TraitFactory.h"
#include "zombie/chat/ChatElement.h"
#include "zombie/chat/ChatElementOwner.h"
#include "zombie/chat/ChatManager.h"
#include "zombie/chat/ChatMessage.h"
#include "zombie/core/BoxedStaticValues.h"
#include "zombie/core/Color.h"
#include "zombie/core/Colors.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/Rand.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/Translator.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/profiling/PerformanceProfileProbe.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/advancedanimation/AdvancedAnimator.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimLayer.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimNode.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimState.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationSet.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationVariableHandle.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationVariableSlotCallbackBool.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationVariableSlotCallbackFloat.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationVariableSlotCallbackInt.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationVariableSlotCallbackString.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationVariableSource.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationVariableType.h"
#include "zombie/core/skinnedmodel/advancedanimation/IAnimEventCallback.h"
#include "zombie/core/skinnedmodel/advancedanimation/IAnimatable.h"
#include "zombie/core/skinnedmodel/advancedanimation/IAnimationVariableMap.h"
#include "zombie/core/skinnedmodel/advancedanimation/IAnimationVariableSlot.h"
#include "zombie/core/skinnedmodel/advancedanimation/LiveAnimNode.h"
#include "zombie/core/skinnedmodel/advancedanimation/debug/AnimatorDebugMonitor.h"
#include "zombie/core/skinnedmodel/animation/AnimationClip.h"
#include "zombie/core/skinnedmodel/animation/AnimationMultiTrack.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/core/skinnedmodel/animation/AnimationTrack.h"
#include "zombie/core/skinnedmodel/animation/debug/AnimationPlayerRecorder.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/core/skinnedmodel/model/ModelInstance.h"
#include "zombie/core/skinnedmodel/model/ModelInstanceTextureCreator.h"
#include "zombie/core/skinnedmodel/population/BeardStyle.h"
#include "zombie/core/skinnedmodel/population/BeardStyles.h"
#include "zombie/core/skinnedmodel/population/ClothingItem.h"
#include "zombie/core/skinnedmodel/population/ClothingItemReference.h"
#include "zombie/core/skinnedmodel/population/HairStyle.h"
#include "zombie/core/skinnedmodel/population/HairStyles.h"
#include "zombie/core/skinnedmodel/population/IClothingItemListener.h"
#include "zombie/core/skinnedmodel/population/Outfit.h"
#include "zombie/core/skinnedmodel/population/OutfitManager.h"
#include "zombie/core/skinnedmodel/population/OutfitRNG.h"
#include "zombie/core/skinnedmodel/visual/BaseVisual.h"
#include "zombie/core/skinnedmodel/visual/HumanVisual.h"
#include "zombie/core/skinnedmodel/visual/IHumanVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/utils/UpdateLimit.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/DebugType.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/gameStates/IngameState.h"
#include "zombie/input/Mouse.h"
#include "zombie/interfaces/IUpdater.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/Clothing.h"
#include "zombie/inventory/types/Drainable.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/InventoryContainer.h"
#include "zombie/inventory/types/Literature.h"
#include "zombie/inventory/types/Radio.h"
#include "zombie/inventory/types/WeaponType.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoLightSource.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoObjectPicker.h"
#include "zombie/iso/IsoRoofFixer.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LightingJNI.h"
#include "zombie/iso/LosUtil.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/Vector3.h"
#include "zombie/iso/areas/IsoBuilding.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/areas/NonPvpZone.h"
#include "zombie/iso/objects/IsoBall.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoFallingClothing.h"
#include "zombie/iso/objects/IsoFireManager.h"
#include "zombie/iso/objects/IsoMolotovCocktail.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoTree.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/IsoWindowFrame.h"
#include "zombie/iso/objects/IsoZombieGiblets.h"
#include "zombie/iso/objects/RainManager.h"
#include "zombie/iso/objects/interfaces/BarricadeAble.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/NetworkVariables.h"
#include "zombie/network/PacketValidator.h"
#include "zombie/network/ServerGUI.h"
#include "zombie/network/ServerMap.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/network/Userlog.h"
#include "zombie/network/chat/ChatServer.h"
#include "zombie/network/chat/ChatType.h"
#include "zombie/network/packets/hit/AttackVars.h"
#include "zombie/network/packets/hit/HitInfo.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/profanity/ProfanityFilter.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/scripting/objects/Recipe.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/ui/ActionProgressBar.h"
#include "zombie/ui/TextDrawObject.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/TutorialManager.h"
#include "zombie/ui/UIFont.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/Pool.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/PathFindBehavior2.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include "zombie/vehicles/VehicleLight.h"
#include "zombie/vehicles/VehiclePart.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoGameCharacter {
public:
 extends IsoMovingObject
 implements Talker,
 ChatElementOwner,
 IAnimatable,
 IAnimationVariableMap,
 IClothingItemListener,
 IActionStateChanged,
 IAnimEventCallback,
 IFMODParameterUpdater,
 ILuaVariableSource,
 ILuaGameCharacter {
 bool ignoreAimingInput = false;
 bool doRenderShadow = true;
 bool doDeathSound = true;
 bool canShout = true;
 bool doDirtBloodEtc = true;
 static int IID = 0;
 static const int RENDER_OFFSET_X = 1;
 static const int RENDER_OFFSET_Y = -89;
 static const float s_maxPossibleTwist = 70.0F;
 private static HashMap<Integer, SurvivorDesc> SurvivorMap = std::make_unique<HashMap<>>();
 private static int[] LevelUpLevels = new int[]{
 25,
 75,
 150,
 225,
 300,
 400,
 500,
 600,
 700,
 800,
 900,
 1000,
 1200,
 1400,
 1600,
 1800,
 2000,
 2200,
 2400,
 2600,
 2800,
 3000,
 3200,
 3400,
 3600,
 3800,
 4000,
 4400,
 4800,
 5200,
 5600,
 6000
 };
 static const Vector2 tempo = new Vector2();
 static const ColorInfo inf = new ColorInfo();
 long vocalEvent;
 long removedFromWorldMS = 0L;
 bool bAutoWalk = false;
 const Vector2 autoWalkDirection = new Vector2();
 bool bSneaking = false;
 static const Vector2 tempo2 = new Vector2();
 static const Vector2 tempVector2_1 = new Vector2();
 static const Vector2 tempVector2_2 = new Vector2();
 static std::string sleepText = nullptr;
 protected ArrayList<InventoryItem> savedInventoryItems = std::make_unique<ArrayList<>>();
 const std::string instancename;
 GameCharacterAIBrain GameCharacterAIBrain;
 public ArrayList<String> amputations = std::make_unique<ArrayList<>>();
 ModelInstance hair;
 ModelInstance beard;
 ModelInstance primaryHandModel;
 ModelInstance secondaryHandModel;
 const ActionContext actionContext = new ActionContext(this);
 const BaseCharacterSoundEmitter emitter;
 const FMODParameterList fmodParameters = new FMODParameterList();
 const AnimationVariableSource m_GameVariables = new AnimationVariableSource();
 AnimationVariableSource m_PlaybackGameVariables = nullptr;
 bool bRunning = false;
 bool bSprinting = false;
 bool m_godMod = false;
 bool m_invisible = false;
 bool m_avoidDamage = false;
 bool callOut = false;
 IsoGameCharacter ReanimatedCorpse;
 int ReanimatedCorpseID = -1;
 AnimationPlayer m_animPlayer = nullptr;
 const AdvancedAnimator advancedAnimator;
 public HashMap<State, HashMap<Object, Object>> StateMachineParams = std::make_unique<HashMap<>>();
 long clientIgnoreCollision = 0L;
 bool isCrit = false;
 bool bKnockedDown = false;
 int bumpNbr = 0;
 bool upKillCount = true;
 private ArrayList<IsoGameCharacter.PerkInfo> PerkList = std::make_unique<ArrayList<>>();
 const Vector2 m_forwardDirection = new Vector2();
 bool Asleep = false;
 bool blockTurning = false;
 float speedMod = 1.0F;
 IsoSprite legsSprite;
 bool bFemale = true;
 float knockbackAttackMod = 1.0F;
 public boolean[] IsVisibleToPlayer = new boolean[4];
 float savedVehicleX;
 float savedVehicleY;
 short savedVehicleSeat = -1;
 bool savedVehicleRunning;
 static const float RecoilDelayDecrease = 0.625F;
 static const float BeenMovingForIncrease = 1.25F;
 static const float BeenMovingForDecrease = 0.625F;
 IsoGameCharacter FollowingTarget = nullptr;
 private ArrayList<IsoMovingObject> LocalList = std::make_unique<ArrayList<>>();
 private ArrayList<IsoMovingObject> LocalNeutralList = std::make_unique<ArrayList<>>();
 private ArrayList<IsoMovingObject> LocalGroupList = std::make_unique<ArrayList<>>();
 private ArrayList<IsoMovingObject> LocalRelevantEnemyList = std::make_unique<ArrayList<>>();
 float dangerLevels = 0.0F;
 static const Vector2 tempVector2 = new Vector2();
 float leaveBodyTimedown = 0.0F;
 bool AllowConversation = true;
 float ReanimateTimer;
 int ReanimAnimFrame;
 int ReanimAnimDelay;
 bool Reanim = false;
 bool VisibleToNPCs = true;
 int DieCount = 0;
 float llx = 0.0F;
 float lly = 0.0F;
 float llz = 0.0F;
 int RemoteID = -1;
 int NumSurvivorsInVicinity = 0;
 float LevelUpMultiplier = 2.5F;
 protected IsoGameCharacter.XP xp = nullptr;
 int LastLocalEnemies = 0;
 private ArrayList<IsoMovingObject> VeryCloseEnemyList = std::make_unique<ArrayList<>>();
 private HashMap<String, IsoGameCharacter.Location> LastKnownLocation = std::make_unique<HashMap<>>();
 IsoGameCharacter AttackedBy = nullptr;
 bool IgnoreStaggerBack = false;
 bool AttackWasSuperAttack = false;
 int TimeThumping = 0;
 int PatienceMax = 150;
 int PatienceMin = 20;
 int Patience = 20;
 protected Stack<BaseAction> CharacterActions = std::make_unique<Stack<>>();
 int ZombieKills = 0;
 int SurvivorKills = 0;
 int LastZombieKills = 0;
 bool superAttack = false;
 float ForceWakeUpTime = -1.0F;
 float fullSpeedMod = 1.0F;
 float runSpeedModifier = 1.0F;
 float walkSpeedModifier = 1.0F;
 float combatSpeedModifier = 1.0F;
 bool bRangedWeaponEmpty = false;
 public ArrayList<InventoryContainer> bagsWorn;
 bool ForceWakeUp;
 const BodyDamage BodyDamage;
 BodyDamage BodyDamageRemote = nullptr;
 State defaultState;
 WornItems wornItems = nullptr;
 AttachedItems attachedItems = nullptr;
 ClothingWetness clothingWetness = nullptr;
 SurvivorDesc descriptor;
 private Stack<IsoBuilding> FamiliarBuildings = std::make_unique<Stack<>>();
 const AStarPathFinderResult finder = new AStarPathFinderResult();
 float FireKillRate = 0.0038F;
 int FireSpreadProbability = 6;
 float Health = 1.0F;
 bool bDead = false;
 bool bKill = false;
 bool bPlayingDeathSound = false;
 bool bDeathDragDown = false;
 std::string hurtSound = "MaleZombieHurt";
 ItemContainer inventory = new ItemContainer();
 InventoryItem leftHandItem;
 int NextWander = 200;
 bool OnFire = false;
 int pathIndex = 0;
 InventoryItem rightHandItem;
 Color SpeakColour = new Color(1.0F, 1.0F, 1.0F, 1.0F);
 float slowFactor = 0.0F;
 float slowTimer = 0.0F;
 bool bUseParts = false;
 bool Speaking = false;
 float SpeakTime = 0.0F;
 float staggerTimeMod = 1.0F;
 const StateMachine stateMachine;
 const Moodles Moodles;
 const Stats stats = new Stats();
 private Stack<String> UsedItemsOn = std::make_unique<Stack<>>();
 HandWeapon useHandWeapon = nullptr;
 IsoGridSquare attackTargetSquare;
 float BloodImpactX = 0.0F;
 float BloodImpactY = 0.0F;
 float BloodImpactZ = 0.0F;
 IsoSprite bloodSplat;
 bool bOnBed = false;
 const Vector2 moveForwardVec = new Vector2();
 bool pathing = false;
 ChatElement chatElement;
 private Stack<IsoGameCharacter> LocalEnemyList = std::make_unique<Stack<>>();
 protected Stack<IsoGameCharacter> EnemyList = std::make_unique<Stack<>>();
 public IsoGameCharacter.CharacterTraits Traits = new IsoGameCharacter.CharacterTraits();
 int maxWeight = 8;
 int maxWeightBase = 8;
 float SleepingTabletDelta = 1.0F;
 float BetaEffect = 0.0F;
 float DepressEffect = 0.0F;
 float SleepingTabletEffect = 0.0F;
 float BetaDelta = 0.0F;
 float DepressDelta = 0.0F;
 float DepressFirstTakeTime = -1.0F;
 float PainEffect = 0.0F;
 float PainDelta = 0.0F;
 bool bDoDefer = true;
 float haloDispTime = 128.0F;
 TextDrawObject userName;
 TextDrawObject haloNote;
 private HashMap<String, String> namesPrefix = std::make_unique<HashMap<>>();
 static const std::string namePvpSuffix = " [img=media/ui/Skull.png]";
 static const std::string nameCarKeySuffix = " [img=media/ui/CarKey.png";
 static const std::string voiceSuffix = "[img=media/ui/voiceon.png] ";
 static const std::string voiceMuteSuffix = "[img=media/ui/voicemuted.png] ";
 IsoPlayer isoPlayer = nullptr;
 bool hasInitTextObjects = false;
 bool canSeeCurrent = false;
 bool drawUserName = false;
 private IsoGameCharacter.Location LastHeardSound = new IsoGameCharacter.Location(-1, -1, -1);
 float lrx = 0.0F;
 float lry = 0.0F;
 bool bClimbing = false;
 bool lastCollidedW = false;
 bool lastCollidedN = false;
 float fallTime = 0.0F;
 float lastFallSpeed = 0.0F;
 bool bFalling = false;
 BaseVehicle vehicle = nullptr;
 bool isNPC = false;
 long lastBump = 0L;
 IsoGameCharacter bumpedChr = nullptr;
 bool m_isCulled = true;
 int age = 25;
 int lastHitCount = 0;
 Safety safety = new Safety(this);
 float meleeDelay = 0.0F;
 float RecoilDelay = 0.0F;
 float BeenMovingFor = 0.0F;
 float BeenSprintingFor = 0.0F;
 bool forceShove = false;
 std::string clickSound = nullptr;
 float reduceInfectionPower = 0.0F;
 private List<String> knownRecipes = std::make_unique<ArrayList<>>();
 private HashSet<String> knownMediaLines = std::make_unique<HashSet<>>();
 int lastHourSleeped = 0;
 float timeOfSleep = 0.0F;
 float delayToActuallySleep = 0.0F;
 std::string bedType = "averageBed";
 IsoObject bed = nullptr;
 bool isReading = false;
 float timeSinceLastSmoke = 0.0F;
 bool wasOnStairs = false;
 ChatMessage lastChatMessage;
 std::string lastSpokenLine;
 bool unlimitedEndurance = false;
 bool unlimitedCarry = false;
 bool buildCheat = false;
 bool farmingCheat = false;
 bool healthCheat = false;
 bool mechanicsCheat = false;
 bool movablesCheat = false;
 bool timedActionInstantCheat = false;
 bool showAdminTag = true;
 long isAnimForecasted = 0L;
 bool fallOnFront = false;
 bool hitFromBehind = false;
 std::string hitReaction = "";
 std::string bumpType = "";
 bool m_isBumpDone = false;
 bool m_bumpFall = false;
 bool m_bumpStaggered = false;
 std::string m_bumpFallType = "";
 int sleepSpeechCnt = 0;
 Radio equipedRadio;
 InventoryItem leftHandCache;
 InventoryItem rightHandCache;
 private ArrayList<IsoGameCharacter.ReadBook> ReadBooks = std::make_unique<ArrayList<>>();
 private IsoGameCharacter.LightInfo lightInfo = new IsoGameCharacter.LightInfo();
 private IsoGameCharacter.LightInfo lightInfo2 = new IsoGameCharacter.LightInfo();
 private PolygonalMap2.Path path2;
 const MapKnowledge mapKnowledge = new MapKnowledge();
 const AttackVars attackVars = new AttackVars();
 public ArrayList<HitInfo> hitList = std::make_unique<ArrayList<>>();
 const PathFindBehavior2 pfb2 = new PathFindBehavior2(this);
 private InventoryItem[] cacheEquiped = new InventoryItem[2];
 bool bAimAtFloor = false;
 int m_persistentOutfitId = 0;
 bool m_bPersistentOutfitInit = false;
 bool bUpdateModelTextures = false;
 ModelInstanceTextureCreator textureCreator = nullptr;
 bool bUpdateEquippedTextures = false;
 private ArrayList<ModelInstance> readyModelData = std::make_unique<ArrayList<>>();
 bool sitOnGround = false;
 bool ignoreMovement = false;
 bool hideWeaponModel = false;
 bool isAiming = false;
 float beardGrowTiming = -1.0F;
 float hairGrowTiming = -1.0F;
 float m_moveDelta = 1.0F;
 float m_turnDeltaNormal = 1.0F;
 float m_turnDeltaRunning = 0.8F;
 float m_turnDeltaSprinting = 0.75F;
 float m_maxTwist = 15.0F;
 bool m_isMoving = false;
 bool m_isTurning = false;
 bool m_isTurningAround = false;
 bool m_isTurning90 = false;
 long lastAutomaticShoot = 0L;
 int shootInARow = 0;
 bool invincible = false;
 float lungeFallTimer = 0.0F;
 SleepingEventData m_sleepingEventData;
 const int HAIR_GROW_TIME = 20;
 const int BEARD_GROW_TIME = 5;
 float realx = 0.0F;
 float realy = 0.0F;
 uint8_t realz = 0;
 public NetworkVariables.ZombieState realState = NetworkVariables.ZombieState.Idle;
 IsoDirections realdir = IsoDirections.fromIndex(0);
 std::string overridePrimaryHandModel = nullptr;
 std::string overrideSecondaryHandModel = nullptr;
 bool forceNullOverride = false;
 const UpdateLimit ulBeatenVehicle = new UpdateLimit(200L);
 float m_momentumScalar = 0.0F;
 private HashMap<String, State> m_stateUpdateLookup = std::make_unique<HashMap<>>();
 bool attackAnim = false;
 NetworkTeleport teleport = nullptr;
 public ArrayList<Integer> invRadioFreq = std::make_unique<ArrayList<>>();
 const PredicatedFileWatcher m_animStateTriggerWatcher;
 const AnimationPlayerRecorder m_animationRecorder;
 const std::string m_UID;
 bool m_bDebugVariablesRegistered = false;
 float effectiveEdibleBuffTimer = 0.0F;
 float m_shadowFM = 0.0F;
 float m_shadowBM = 0.0F;
 long shadowTick = -1L;
 static const ItemVisuals tempItemVisuals = new ItemVisuals();
 private static ArrayList<IsoMovingObject> movingStatic = std::make_unique<ArrayList<>>();
 long m_muzzleFlash = -1L;
 private static IsoGameCharacter.Bandages s_bandages = new IsoGameCharacter.Bandages();
 static const Vector3 tempVector = new Vector3();
 static const Vector3 tempVectorBonePos = new Vector3();
 const NetworkCharacter networkCharacter = new NetworkCharacter();

 public IsoGameCharacter(IsoCell cell, float x, float y, float z) {
 super(cell, false);
 this->m_UID = String.format("%s-%s", this->getClass().getSimpleName(), UUID.randomUUID().toString());
 this->registerVariableCallbacks();
 this->instancename = "Character" + IID;
 IID++;
 if (!(this instanceof IsoSurvivor) {
 this->emitter = (BaseCharacterSoundEmitter)(!Core.SoundDisabled && !GameServer.bServer
 ? new CharacterSoundEmitter(this)
 : new DummyCharacterSoundEmitter(this);
 } else {
 this->emitter = nullptr;
 }

 if (x != 0.0F || y != 0.0F || z != 0.0F) {
 if (this->getCell().isSafeToAdd()) {
 this->getCell().getObjectList().add(this);
 } else {
 this->getCell().getAddList().add(this);
 }
 }

 if (this->def.empty()) {
 this->def = IsoSpriteInstance.get(this->sprite);
 }

 if (this instanceof IsoPlayer) {
 this->BodyDamage = new BodyDamage(this);
 this->Moodles = new Moodles(this);
 this->xp = new IsoGameCharacter.XP(this);
 } else {
 this->BodyDamage = nullptr;
 this->Moodles = nullptr;
 this->xp = nullptr;
 }

 this->Patience = Rand.Next(this->PatienceMin, this->PatienceMax);
 this->x = x + 0.5F;
 this->y = y + 0.5F;
 this->z = z;
 this->scriptnx = this->lx = this->nx = x;
 this->scriptny = this->ly = this->ny = y;
 if (cell != nullptr) {
 this->current = this->getCell().getGridSquare((int)x, (int)y, (int)z);
 }

 this->offsetY = 0.0F;
 this->offsetX = 0.0F;
 this->stateMachine = new StateMachine(this);
 this->setDefaultState(IdleState.instance());
 this->inventory.parent = this;
 this->inventory.setExplored(true);
 this->chatElement = new ChatElement(this, 1, "character");
 if (GameClient.bClient || GameServer.bServer) {
 this->namesPrefix.put("admin", "[col=255,0,0]Admin[/] ");
 this->namesPrefix.put("moderator", "[col=0,128,47]Moderator[/] ");
 this->namesPrefix.put("overseer", "[col=26,26,191]Overseer[/] ");
 this->namesPrefix.put("gm", "[col=213,123,23]GM[/] ");
 this->namesPrefix.put("observer", "[col=128,128,128]Observer[/] ");
 }

 this->m_animationRecorder = new AnimationPlayerRecorder(this);
 this->advancedAnimator = std::make_unique<AdvancedAnimator>();
 this->advancedAnimator.init(this);
 this->advancedAnimator.animCallbackHandlers.add(this);
 this->advancedAnimator.SetAnimSet(AnimationSet.GetAnimationSet(this->GetAnimSetName(), false);
 this->advancedAnimator.setRecorder(this->m_animationRecorder);
 this->actionContext.onStateChanged.add(this);
 this->m_animStateTriggerWatcher = new PredicatedFileWatcher(
 ZomboidFileSystem.instance.getMessagingDirSub("Trigger_SetAnimState.xml"), AnimStateTriggerXmlFile.class, this::onTrigger_setAnimStateToTriggerFile
 );
 }

 void registerVariableCallbacks() {
 this->setVariable("hitreaction", this::getHitReaction, this::setHitReaction);
 this->setVariable("collidetype", this::getCollideType, this::setCollideType);
 this->setVariable("footInjuryType", this::getFootInjuryType);
 this->setVariable("bumptype", this::getBumpType, this::setBumpType);
 this->setVariable("sitonground", this::isSitOnGround, this::setSitOnGround);
 this->setVariable("canclimbdownrope", this::canClimbDownSheetRopeInCurrentSquare);
 this->setVariable("frombehind", this::isHitFromBehind, this::setHitFromBehind);
 this->setVariable("fallonfront", this::isFallOnFront, this::setFallOnFront);
 this->setVariable("hashitreaction", this::hasHitReaction);
 this->setVariable("intrees", this::isInTreesNoBush);
 this->setVariable("bumped", this::isBumped);
 this->setVariable("BumpDone", false, this::isBumpDone, this::setBumpDone);
 this->setVariable("BumpFall", false, this::isBumpFall, this::setBumpFall);
 this->setVariable("BumpFallType", "", this::getBumpFallType, this::setBumpFallType);
 this->setVariable("BumpStaggered", false, this::isBumpStaggered, this::setBumpStaggered);
 this->setVariable("bonfloor", this::isOnFloor, this::setOnFloor);
 this->setVariable("rangedweaponempty", this::isRangedWeaponEmpty, this::setRangedWeaponEmpty);
 this->setVariable("footInjury", this::hasFootInjury);
 this->setVariable("ChopTreeSpeed", 1.0F, this::getChopTreeSpeed);
 this->setVariable("MoveDelta", 1.0F, this::getMoveDelta, this::setMoveDelta);
 this->setVariable("TurnDelta", 1.0F, this::getTurnDelta, this::setTurnDelta);
 this->setVariable("angle", this::getDirectionAngle, this::setDirectionAngle);
 this->setVariable("animAngle", this::getAnimAngle);
 this->setVariable("twist", this::getTwist);
 this->setVariable("targetTwist", this::getTargetTwist);
 this->setVariable("maxTwist", this->m_maxTwist, this::getMaxTwist, this::setMaxTwist);
 this->setVariable("shoulderTwist", this::getShoulderTwist);
 this->setVariable("excessTwist", this::getExcessTwist);
 this->setVariable("angleStepDelta", this::getAnimAngleStepDelta);
 this->setVariable("angleTwistDelta", this::getAnimAngleTwistDelta);
 this->setVariable("isTurning", false, this::isTurning, this::setTurning);
 this->setVariable("isTurning90", false, this::isTurning90, this::setTurning90);
 this->setVariable("isTurningAround", false, this::isTurningAround, this::setTurningAround);
 this->setVariable("bMoving", false, this::isMoving, this::setMoving);
 this->setVariable("beenMovingFor", this::getBeenMovingFor);
 this->setVariable("previousState", this::getPreviousActionContextStateName);
 this->setVariable("momentumScalar", this::getMomentumScalar, this::setMomentumScalar);
 this->setVariable("hasTimedActions", this::hasTimedActions);
 if (DebugOptions.instance.Character.Debug.RegisterDebugVariables.getValue()) {
 this->registerDebugGameVariables();
 }

 this->setVariable("CriticalHit", this::isCriticalHit, this::setCriticalHit);
 this->setVariable("bKnockedDown", this::isKnockedDown, this::setKnockedDown);
 this->setVariable("bdead", this::isDead);
 }

 void updateRecoilVar() {
 this->setVariable("recoilVarY", 0.0F);
 this->setVariable("recoilVarX", 0.0F + this->getPerkLevel(PerkFactory.Perks.Aiming) / 10.0F);
 }

 void registerDebugGameVariables() {
 for (int int0 = 0; int0 < 2; int0++) {
 for (int int1 = 0; int1 < 9; int1++) {
 this->dbgRegisterAnimTrackVariable(int0, int1);
 }
 }

 this->setVariable("dbg.anm.dx", () -> this->getDeferredMovement(tempo).x / GameTime.instance.getMultiplier());
 this->setVariable("dbg.anm.dy", () -> this->getDeferredMovement(tempo).y / GameTime.instance.getMultiplier());
 this->setVariable("dbg.anm.da", () -> this->getDeferredAngleDelta() / GameTime.instance.getMultiplier());
 this->setVariable("dbg.anm.daw", this::getDeferredRotationWeight);
 this->setVariable("dbg.forward", () -> this->getForwardDirection().x + "; " + this->getForwardDirection().y);
 this->setVariable("dbg.anm.blend.fbx_x", () -> DebugOptions.instance.Animation.BlendUseFbx.getValue() ? 1.0F : 0.0F);
 this->m_bDebugVariablesRegistered = true;
 }

 void dbgRegisterAnimTrackVariable(int int0, int int1) {
 this->setVariable(String.format("dbg.anm.track%d%d", int0, int1), () -> this->dbgGetAnimTrackName(int0, int1);
 this->setVariable(String.format("dbg.anm.t.track%d%d", int0, int1), () -> this->dbgGetAnimTrackTime(int0, int1);
 this->setVariable(String.format("dbg.anm.w.track%d%d", int0, int1), () -> this->dbgGetAnimTrackWeight(int0, int1);
 }

 float getMomentumScalar() {
 return this->m_momentumScalar;
 }

 void setMomentumScalar(float val) {
 this->m_momentumScalar = val;
 }

 Vector2 getDeferredMovement(Vector2 out_result) {
 if (this->m_animPlayer.empty()) {
 out_result.set(0.0F, 0.0F);
 return out_result;
 } else {
 this->m_animPlayer.getDeferredMovement(out_result);
 return out_result;
 }
 }

 float getDeferredAngleDelta() {
 return this->m_animPlayer.empty() ? 0.0F : this->m_animPlayer.getDeferredAngleDelta() * (180.0F / (float)Math.PI);
 }

 float getDeferredRotationWeight() {
 return this->m_animPlayer.empty() ? 0.0F : this->m_animPlayer.getDeferredRotationWeight();
 }

 bool isStrafing() {
 return this->getPath2() != nullptr && this->pfb2.isStrafing() ? true : this->isAiming();
 }

 AnimationTrack dbgGetAnimTrack(int layerIdx, int trackIdx) {
 if (this->m_animPlayer.empty()) {
 return nullptr;
 } else {
 AnimationPlayer animationPlayer = this->m_animPlayer;
 AnimationMultiTrack animationMultiTrack = animationPlayer.getMultiTrack();
 std::vector list = animationMultiTrack.getTracks();
 AnimationTrack animationTrack0 = nullptr;
 int int0 = 0;
 int int1 = 0;

 for (int int2 = list.size(); int0 < int2; int0++) {
 AnimationTrack animationTrack1 = (AnimationTrack)list.get(int0);
 int int3 = animationTrack1.getLayerIdx();
 if (int3 == layerIdx) {
 if (int1 == trackIdx) {
 animationTrack0 = animationTrack1;
 break;
 }

 int1++;
 }
 }

 return animationTrack0;
 }
 }

 std::string dbgGetAnimTrackName(int layerIdx, int trackIdx) {
 AnimationTrack animationTrack = this->dbgGetAnimTrack(layerIdx, trackIdx);
 return animationTrack != nullptr ? animationTrack.name : "";
 }

 float dbgGetAnimTrackTime(int layerIdx, int trackIdx) {
 AnimationTrack animationTrack = this->dbgGetAnimTrack(layerIdx, trackIdx);
 return animationTrack != nullptr ? animationTrack.getCurrentTime() : 0.0F;
 }

 float dbgGetAnimTrackWeight(int layerIdx, int trackIdx) {
 AnimationTrack animationTrack = this->dbgGetAnimTrack(layerIdx, trackIdx);
 return animationTrack != nullptr ? animationTrack.BlendDelta : 0.0F;
 }

 /**
 * The character's current twist angle, in degrees.
 */
 float getTwist() {
 return this->m_animPlayer != nullptr ? (180.0F / (float)Math.PI) * this->m_animPlayer.getTwistAngle() : 0.0F;
 }

 /**
 * The character's current shoulder-twist angle, in degrees.
 */
 float getShoulderTwist() {
 return this->m_animPlayer != nullptr ? (180.0F / (float)Math.PI) * this->m_animPlayer.getShoulderTwistAngle() : 0.0F;
 }

 /**
 * The maximum twist angle, in degrees.
 */
 float getMaxTwist() {
 return this->m_maxTwist;
 }

 /**
 * Specify the maximum twist angle, in degrees.
 */
 void setMaxTwist(float degrees) {
 this->m_maxTwist = degrees;
 }

 /**
 * The character's excess twist, in degrees. The excess is > 0 if the character is trying to twist further than their current maximum twist. ie. The amount that the desired twist exceeds the maximum twist. eg. If the character is trying to twist by 90 degrees, but their maximum is set to 70, then excess = 20
 */
 float getExcessTwist() {
 return this->m_animPlayer != nullptr ? (180.0F / (float)Math.PI) * this->m_animPlayer.getExcessTwistAngle() : 0.0F;
 }

 float getAbsoluteExcessTwist() {
 return Math.abs(this->getExcessTwist());
 }

 float getAnimAngleTwistDelta() {
 return this->m_animPlayer != nullptr ? this->m_animPlayer.angleTwistDelta : 0.0F;
 }

 float getAnimAngleStepDelta() {
 return this->m_animPlayer != nullptr ? this->m_animPlayer.angleStepDelta : 0.0F;
 }

 /**
 * The desired twist, unclamped, in degrees.
 */
 float getTargetTwist() {
 return this->m_animPlayer != nullptr ? (180.0F / (float)Math.PI) * this->m_animPlayer.getTargetTwistAngle() : 0.0F;
 }

 bool isRangedWeaponEmpty() {
 return this->bRangedWeaponEmpty;
 }

 void setRangedWeaponEmpty(bool val) {
 this->bRangedWeaponEmpty = val;
 }

 bool hasFootInjury() {
 return !StringUtils.isNullOrWhitespace(this->getFootInjuryType());
 }

 bool isInTrees2(bool ignoreBush) {
 if (this->isCurrentState(BumpedState.instance())) {
 return false;
 } else {
 IsoGridSquare square = this->getCurrentSquare();
 if (square.empty()) {
 return false;
 } else {
 if (square.Has(IsoObjectType.tree) {
 IsoTree tree = square.getTree();
 if (tree.empty() || ignoreBush && tree.getSize() > 2 || !ignoreBush) {
 return true;
 }
 }

 std::string string = square.getProperties().Val("Movement");
 return !"HedgeLow".equalsIgnoreCase(string) && !"HedgeHigh".equalsIgnoreCase(string) ? !ignoreBush && square.getProperties().Is("Bush") : true;
 }
 }
 }

 bool isInTreesNoBush() {
 return this->isInTrees2(true);
 }

 bool isInTrees() {
 return this->isInTrees2(false);
 }

 /**
 * @return the SurvivorMap
 */
 public static HashMap<Integer, SurvivorDesc> getSurvivorMap() {
 return SurvivorMap;
 }

 public static int[] getLevelUpLevels() {
 return LevelUpLevels;
 }

 /**
 * @return the tempo
 */
 static Vector2 getTempo() {
 return tempo;
 }

 /**
 * @return the inf
 */
 static ColorInfo getInf() {
 return inf;
 }

 GameCharacterAIBrain getBrain() {
 return this->GameCharacterAIBrain;
 }

 bool getIsNPC() {
 return this->isNPC;
 }

 void setIsNPC(bool isAI) {
 this->isNPC = isAI;
 }

 BaseCharacterSoundEmitter getEmitter() {
 return this->emitter;
 }

 void updateEmitter() {
 this->getFMODParameters().update();
 if (IsoWorld.instance.emitterUpdate || this->emitter.hasSoundsToStart()) {
 if (this->isZombie() && this->isProne()) {
 SwipeStatePlayer.getBoneWorldPos(this, "Bip01_Head", tempVectorBonePos);
 this->emitter.set(tempVectorBonePos.x, tempVectorBonePos.y, this->z);
 this->emitter.tick();
 } else {
 this->emitter.set(this->x, this->y, this->z);
 this->emitter.tick();
 }
 }
 }

 void doDeferredMovement() {
 if (GameClient.bClient && this->getHitReactionNetworkAI() != nullptr) {
 if (this->getHitReactionNetworkAI().isStarted()) {
 this->getHitReactionNetworkAI().move();
 return;
 }

 if (this->isDead() && this->getHitReactionNetworkAI().isDoSkipMovement()) {
 return;
 }
 }

 AnimationPlayer animationPlayer = this->getAnimationPlayer();
 if (animationPlayer != nullptr) {
 if (this->getPath2() != nullptr && !this->isCurrentState(ClimbOverFenceState.instance()) && !this->isCurrentState(ClimbThroughWindowState.instance())) {
 if (this->isCurrentState(WalkTowardState.instance())) {
 DebugLog.General.warn("WalkTowardState but path2 != nullptr");
 this->setPath2(nullptr);
 }
 } else {
 if (GameClient.bClient) {
 if (this instanceof IsoZombie && ((IsoZombie)this).isRemoteZombie()) {
 if (this->getCurrentState() != ClimbOverFenceState.instance()
 && this->getCurrentState() != ClimbThroughWindowState.instance()
 && this->getCurrentState() != ClimbOverWallState.instance()
 && this->getCurrentState() != StaggerBackState.instance()
 && this->getCurrentState() != ZombieHitReactionState.instance()
 && this->getCurrentState() != ZombieFallDownState.instance()
 && this->getCurrentState() != ZombieFallingState.instance()
 && this->getCurrentState() != ZombieOnGroundState.instance()
 && this->getCurrentState() != AttackNetworkState.instance()) {
 return;
 }
 } else if (this instanceof IsoPlayer
 && !((IsoPlayer)this).isLocalPlayer()
 && !this->isCurrentState(CollideWithWallState.instance())
 && !this->isCurrentState(PlayerGetUpState.instance())
 && !this->isCurrentState(BumpedState.instance())) {
 return;
 }
 }

 Vector2 vector = tempo;
 this->getDeferredMovement(vector);
 if (GameClient.bClient && this instanceof IsoZombie && this->isCurrentState(StaggerBackState.instance())) {
 float float0 = vector.getLength();
 vector.set(this->getHitDir());
 vector.setLength(float0);
 }

 this->MoveUnmodded(vector);
 }
 }
 }

 ActionContext getActionContext() {
 return nullptr;
 }

 std::string getPreviousActionContextStateName() {
 ActionContext actionContextx = this->getActionContext();
 return actionContextx = = nullptr ? "" : actionContextx.getPreviousStateName();
 }

 std::string getCurrentActionContextStateName() {
 ActionContext actionContextx = this->getActionContext();
 return actionContextx = = nullptr ? "" : actionContextx.getCurrentStateName();
 }

 bool hasAnimationPlayer() {
 return this->m_animPlayer != nullptr;
 }

 AnimationPlayer getAnimationPlayer() {
 Model model = ModelManager.instance.getBodyModel(this);
 bool boolean0 = false;
 if (this->m_animPlayer != nullptr && this->m_animPlayer.getModel() != model) {
 boolean0 = this->m_animPlayer.getMultiTrack().getTrackCount() > 0;
 this->m_animPlayer = Pool.tryRelease(this->m_animPlayer);
 }

 if (this->m_animPlayer.empty()) {
 this->m_animPlayer = AnimationPlayer.alloc(model);
 this->onAnimPlayerCreated(this->m_animPlayer);
 if (boolean0) {
 this->getAdvancedAnimator().OnAnimDataChanged(false);
 }
 }

 return this->m_animPlayer;
 }

 void releaseAnimationPlayer() {
 this->m_animPlayer = Pool.tryRelease(this->m_animPlayer);
 }

 void onAnimPlayerCreated(AnimationPlayer animationPlayer) {
 animationPlayer.setRecorder(this->m_animationRecorder);
 animationPlayer.setTwistBones("Bip01_Pelvis", "Bip01_Spine", "Bip01_Spine1", "Bip01_Neck", "Bip01_Head");
 animationPlayer.setCounterRotationBone("Bip01");
 }

 void updateAnimationRecorderState() {
 if (this->m_animPlayer != nullptr) {
 if (IsoWorld.isAnimRecorderDiscardTriggered()) {
 this->m_animPlayer.discardRecording();
 }

 bool boolean0 = IsoWorld.isAnimRecorderActive();
 bool boolean1 = boolean0 && !this->isSceneCulled();
 if (boolean1) {
 this->getAnimationPlayerRecorder().logCharacterPos();
 }

 this->m_animPlayer.setRecording(boolean1);
 }
 }

 AdvancedAnimator getAdvancedAnimator() {
 return this->advancedAnimator;
 }

 ModelInstance getModelInstance() {
 if (this->legsSprite.empty()) {
 return nullptr;
 } else {
 return this->legsSprite.modelSlot.empty() ? nullptr : this->legsSprite.modelSlot.model;
 }
 }

 std::string getCurrentStateName() {
 return this->stateMachine.getCurrent() == nullptr ? nullptr : this->stateMachine.getCurrent().getName();
 }

 std::string getPreviousStateName() {
 return this->stateMachine.getPrevious() == nullptr ? nullptr : this->stateMachine.getPrevious().getName();
 }

 std::string getAnimationDebug() {
 return this->advancedAnimator != nullptr ? this->instancename + "\n" + this->advancedAnimator.GetDebug() : this->instancename + "\n - No Animator";
 }

 std::string getTalkerType() {
 return this->chatElement.getTalkerType();
 }

 bool isAnimForecasted() {
 return System.currentTimeMillis() < this->isAnimForecasted;
 }

 void setAnimForecasted(int timeMs) {
 this->isAnimForecasted = System.currentTimeMillis() + timeMs;
 }

 void resetModel() {
 ModelManager.instance.Reset(this);
 }

 void resetModelNextFrame() {
 ModelManager.instance.ResetNextFrame(this);
 }

 void onTrigger_setClothingToXmlTriggerFile(TriggerXmlFile triggerXmlFile) {
 OutfitManager.Reload();
 if (!StringUtils.isNullOrWhitespace(triggerXmlFile.outfitName) {
 std::string string0 = triggerXmlFile.outfitName;
 DebugLog.Clothing.debugln("Desired outfit name: " + string0);
 Outfit outfit;
 if (triggerXmlFile.isMale) {
 outfit = OutfitManager.instance.FindMaleOutfit(string0);
 } else {
 outfit = OutfitManager.instance.FindFemaleOutfit(string0);
 }

 if (outfit.empty()) {
 DebugLog.Clothing.error("Could not find outfit: " + string0);
 return;
 }

 if (this->bFemale == triggerXmlFile.isMale && this instanceof IHumanVisual) {
 ((IHumanVisual)this).getHumanVisual().clear();
 }

 this->bFemale = !triggerXmlFile.isMale;
 if (this->descriptor != nullptr) {
 this->descriptor.setFemale(this->bFemale);
 }

 this->dressInNamedOutfit(outfit.m_Name);
 this->advancedAnimator.OnAnimDataChanged(false);
 if (this instanceof IsoPlayer) {
 LuaEventManager.triggerEvent("OnClothingUpdated", this);
 }
 } else if (!StringUtils.isNullOrWhitespace(triggerXmlFile.clothingItemGUID) {
 std::string string1 = "game";
 this->dressInClothingItem(string1 + "-" + triggerXmlFile.clothingItemGUID);
 if (this instanceof IsoPlayer) {
 LuaEventManager.triggerEvent("OnClothingUpdated", this);
 }
 }

 ModelManager.instance.Reset(this);
 }

 void onTrigger_setAnimStateToTriggerFile(AnimStateTriggerXmlFile animStateTriggerXmlFile) {
 std::string string = this->GetAnimSetName();
 if (!StringUtils.equalsIgnoreCase(string, animStateTriggerXmlFile.animSet) {
 this->setVariable("dbgForceAnim", false);
 this->restoreAnimatorStateToActionContext();
 } else {
 DebugOptions.instance.Animation.AnimLayer.AllowAnimNodeOverride.setValue(animStateTriggerXmlFile.forceAnim);
 if (this->advancedAnimator.containsState(animStateTriggerXmlFile.stateName) {
 this->setVariable("dbgForceAnim", animStateTriggerXmlFile.forceAnim);
 this->setVariable("dbgForceAnimStateName", animStateTriggerXmlFile.stateName);
 this->setVariable("dbgForceAnimNodeName", animStateTriggerXmlFile.nodeName);
 this->setVariable("dbgForceAnimScalars", animStateTriggerXmlFile.setScalarValues);
 this->setVariable("dbgForceScalar", animStateTriggerXmlFile.scalarValue);
 this->setVariable("dbgForceScalar2", animStateTriggerXmlFile.scalarValue2);
 this->advancedAnimator.SetState(animStateTriggerXmlFile.stateName);
 } else {
 DebugLog.Animation.error("State not found: " + animStateTriggerXmlFile.stateName);
 this->restoreAnimatorStateToActionContext();
 }
 }
 }

 void restoreAnimatorStateToActionContext() {
 if (this->actionContext.getCurrentState() != nullptr) {
 this->advancedAnimator
 .SetState(
 this->actionContext.getCurrentStateName(), PZArrayUtil.listConvert(this->actionContext.getChildStates(), actionState -> actionState.name)
 );
 }
 }

 /**
 * clothingItemChanged Called when a ClothingItem file has changed on disk, causing the OutfitManager to broadcast this event. Checks if this item is currently used by this player's Outfit. Reloads and re-equips if so.
 * 
 * @param itemGuid The item's Globally Unique Identifier (GUID).
 */
 void clothingItemChanged(const std::string& itemGuid) {
 if (this->wornItems != nullptr) {
 for (int int0 = 0; int0 < this->wornItems.size(); int0++) {
 InventoryItem item = this->wornItems.getItemByIndex(int0);
 ClothingItem clothingItem = item.getClothingItem();
 if (clothingItem != nullptr && clothingItem.isReady() && clothingItem.m_GUID == itemGuid) {
 ClothingItemReference clothingItemReference = new ClothingItemReference();
 clothingItemReference.itemGUID = itemGuid;
 clothingItemReference.randomize();
 item.getVisual().synchWithOutfit(clothingItemReference);
 item.synchWithVisual();
 this->resetModelNextFrame();
 }
 }
 }
 }

 void reloadOutfit() {
 ModelManager.instance.Reset(this);
 }

 /**
 * Is this character currently culled from the visible scene graph. Eg. Zombies not seen by the player. Objects outside the rendered window etc.
 * @return TRUE if this character should be drawn. FALSE otherwise.
 */
 bool isSceneCulled() {
 return this->m_isCulled;
 }

 /**
 * Specify whether this character is currently not to be drawn, as it is outside the visible area. Eg. Zombies not seen by the player. Objects outside the rendered window etc.
 */
 void setSceneCulled(bool isCulled) {
 if (this->isSceneCulled() != isCulled) {
 try {
 if (isCulled) {
 ModelManager.instance.Remove(this);
 } else {
 ModelManager.instance.Add(this);
 }
 } catch (Exception exception) {
 System.err.println("Error in IsoGameCharacter.setSceneCulled(" + isCulled + "):");
 ExceptionLogger.logException(exception);
 ModelManager.instance.Remove(this);
 this->legsSprite.modelSlot = nullptr;
 }
 }
 }

 /**
 * Callback from ModelManager.Add/Remove functions.
 * 
 * @param modelManager Event sender.
 * @param isCulled Whether or not this object is culled from the visible scene or not.
 */
 void onCullStateChanged(ModelManager modelManager, bool isCulled) {
 this->m_isCulled = isCulled;
 if (!isCulled) {
 this->restoreAnimatorStateToActionContext();
 DebugFileWatcher.instance.add(this->m_animStateTriggerWatcher);
 OutfitManager.instance.addClothingItemListener(this);
 } else {
 DebugFileWatcher.instance.remove(this->m_animStateTriggerWatcher);
 OutfitManager.instance.removeClothingItemListener(this);
 }
 }

 /**
 * Picks a random outfit from the OutfitManager
 */
 void dressInRandomOutfit() {
 if (DebugLog.isEnabled(DebugType.Clothing) {
 DebugLog.Clothing.println("IsoGameCharacter.dressInRandomOutfit>");
 }

 Outfit outfit = OutfitManager.instance.GetRandomOutfit(this->isFemale());
 if (outfit != nullptr) {
 this->dressInNamedOutfit(outfit.m_Name);
 }
 }

 void dressInNamedOutfit(const std::string& outfitName) {
 }

 void dressInPersistentOutfit(const std::string& outfitName) {
 int int0 = PersistentOutfits.instance.pickOutfit(outfitName, this->isFemale());
 this->dressInPersistentOutfitID(int0);
 }

 void dressInPersistentOutfitID(int outfitID) {
 }

 std::string getOutfitName() {
 if (this instanceof IHumanVisual) {
 HumanVisual humanVisual = ((IHumanVisual)this).getHumanVisual();
 Outfit outfit = humanVisual.getOutfit();
 return outfit = = nullptr ? nullptr : outfit.m_Name;
 } else {
 return nullptr;
 }
 }

 void dressInClothingItem(const std::string& itemGUID) {
 }

 Outfit getRandomDefaultOutfit() {
 IsoGridSquare square = this->getCurrentSquare();
 IsoRoom room = square.empty() ? nullptr : square.getRoom();
 std::string string = room.empty() ? nullptr : room.getName();
 return ZombiesZoneDefinition.getRandomDefaultOutfit(this->isFemale(), string);
 }

 ModelInstance getModel() {
 return this->legsSprite != nullptr && this->legsSprite.modelSlot != nullptr ? this->legsSprite.modelSlot.model : nullptr;
 }

 bool hasActiveModel() {
 return this->legsSprite != nullptr && this->legsSprite.hasActiveModel();
 }

 bool hasItems(const std::string& type, int count) {
 int int0 = this->inventory.getItemCount(type);
 return count <= int0;
 }

 int getLevelUpLevels(int level) {
 return LevelUpLevels.length <= level ? LevelUpLevels[LevelUpLevels.length - 1] : LevelUpLevels[level];
 }

 int getLevelMaxForXp() {
 return LevelUpLevels.length;
 }

 int getXpForLevel(int level) {
 return level < LevelUpLevels.length
 ? (int)(LevelUpLevels[level] * this->LevelUpMultiplier)
 : (int)((LevelUpLevels[LevelUpLevels.length - 1] + (level - LevelUpLevels.length + 1) * 400) * this->LevelUpMultiplier);
 }

 void DoDeath(HandWeapon weapon, IsoGameCharacter wielder) {
 this->DoDeath(weapon, wielder, true);
 }

 void DoDeath(HandWeapon weapon, IsoGameCharacter wielder, bool bGory) {
 this->OnDeath();
 if (this->getAttackedBy() instanceof IsoPlayer && GameServer.bServer && this instanceof IsoPlayer) {
 std::string string0 = "";
 std::string string1 = "";
 if (SteamUtils.isSteamModeEnabled()) {
 string0 = " (" + ((IsoPlayer)this->getAttackedBy()).getSteamID() + ") ";
 string1 = " (" + ((IsoPlayer)this).getSteamID() + ") ";
 }

 LoggerManager.getLogger("pvp")
 .write(
 "user "
 + ((IsoPlayer)this->getAttackedBy()).username
 + string0
 + " killed "
 + ((IsoPlayer)this).username
 + string1
 + " "
 + LoggerManager.getPlayerCoords((IsoPlayer)this),
 "IMPORTANT"
 );
 if (ServerOptions.instance.AnnounceDeath.getValue()) {
 ChatServer.getInstance().sendMessageToServerChat(((IsoPlayer)this->getAttackedBy()).username + " killed " + ((IsoPlayer)this).username + ".");
 }

 ChatServer.getInstance().sendMessageToAdminChat("user " + ((IsoPlayer)this->getAttackedBy()).username + " killed " + ((IsoPlayer)this).username);
 } else {
 if (GameServer.bServer && this instanceof IsoPlayer) {
 LoggerManager.getLogger("user")
 .write("user " + ((IsoPlayer)this).username + " died at " + LoggerManager.getPlayerCoords((IsoPlayer)this) + " (non pvp)");
 }

 if (ServerOptions.instance.AnnounceDeath.getValue() && this instanceof IsoPlayer && GameServer.bServer) {
 ChatServer.getInstance().sendMessageToServerChat(((IsoPlayer)this).username + " is dead.");
 }
 }

 if (this->isDead()) {
 float float0 = 0.5F;
 if (this->isZombie() && (((IsoZombie)this).bCrawling || this->getCurrentState() == ZombieOnGroundState.instance())) {
 float0 = 0.2F;
 }

 if (GameServer.bServer && bGory) {
 bool boolean0 = this->isOnFloor() && wielder instanceof IsoPlayer && weapon != nullptr && "BareHands".equals(weapon.getType());
 GameServer.sendBloodSplatter(weapon, this->getX(), this->getY(), this->getZ() + float0, this->getHitDir(), this->isCloseKilled(), boolean0);
 }

 if (weapon != nullptr && SandboxOptions.instance.BloodLevel.getValue() > 1 && bGory) {
 int int0 = weapon.getSplatNumber();
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
 this->splatBlood(3, 0.3F);
 }
 }

 if (weapon != nullptr && SandboxOptions.instance.BloodLevel.getValue() > 1 && bGory) {
 this->splatBloodFloorBig();
 }

 if (wielder != nullptr && wielder.xp != nullptr) {
 wielder.xp.AddXP(weapon, 3);
 }

 if (SandboxOptions.instance.BloodLevel.getValue() > 1
 && this->isOnFloor()
 && wielder instanceof IsoPlayer
 && weapon == ((IsoPlayer)wielder).bareHands
 && bGory) {
 this->playBloodSplatterSound();

 for (int int2 = -1; int2 <= 1; int2++) {
 for (int int3 = -1; int3 <= 1; int3++) {
 if (int2 != 0 || int3 != 0) {
 new IsoZombieGiblets(
 IsoZombieGiblets.GibletType.A,
 this->getCell(),
 this->getX(),
 this->getY(),
 this->getZ() + float0,
 int2 * Rand.Next(0.25F, 0.5F),
 int3 * Rand.Next(0.25F, 0.5F)
 );
 }
 }
 }

 new IsoZombieGiblets(
 IsoZombieGiblets.GibletType.Eye,
 this->getCell(),
 this->getX(),
 this->getY(),
 this->getZ() + float0,
 this->getHitDir().x * 0.8F,
 this->getHitDir().y * 0.8F
 );
 } else if (SandboxOptions.instance.BloodLevel.getValue() > 1 && bGory) {
 this->playBloodSplatterSound();
 new IsoZombieGiblets(
 IsoZombieGiblets.GibletType.A,
 this->getCell(),
 this->getX(),
 this->getY(),
 this->getZ() + float0,
 this->getHitDir().x * 1.5F,
 this->getHitDir().y * 1.5F
 );
 tempo.x = this->getHitDir().x;
 tempo.y = this->getHitDir().y;
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

 for (int int4 = 0; int4 < byte2; int4++) {
 if (Rand.Next(this->isCloseKilled() ? 8 : byte0) == 0) {
 new IsoZombieGiblets(
 IsoZombieGiblets.GibletType.A,
 this->getCell(),
 this->getX(),
 this->getY(),
 this->getZ() + float0,
 this->getHitDir().x * 1.5F,
 this->getHitDir().y * 1.5F
 );
 }

 if (Rand.Next(this->isCloseKilled() ? 8 : byte0) == 0) {
 new IsoZombieGiblets(
 IsoZombieGiblets.GibletType.A,
 this->getCell(),
 this->getX(),
 this->getY(),
 this->getZ() + float0,
 this->getHitDir().x * 1.5F,
 this->getHitDir().y * 1.5F
 );
 }

 if (Rand.Next(this->isCloseKilled() ? 8 : byte0) == 0) {
 new IsoZombieGiblets(
 IsoZombieGiblets.GibletType.A,
 this->getCell(),
 this->getX(),
 this->getY(),
 this->getZ() + float0,
 this->getHitDir().x * 1.8F,
 this->getHitDir().y * 1.8F
 );
 }

 if (Rand.Next(this->isCloseKilled() ? 8 : byte0) == 0) {
 new IsoZombieGiblets(
 IsoZombieGiblets.GibletType.A,
 this->getCell(),
 this->getX(),
 this->getY(),
 this->getZ() + float0,
 this->getHitDir().x * 1.9F,
 this->getHitDir().y * 1.9F
 );
 }

 if (Rand.Next(this->isCloseKilled() ? 4 : byte1) == 0) {
 new IsoZombieGiblets(
 IsoZombieGiblets.GibletType.A,
 this->getCell(),
 this->getX(),
 this->getY(),
 this->getZ() + float0,
 this->getHitDir().x * 3.5F,
 this->getHitDir().y * 3.5F
 );
 }

 if (Rand.Next(this->isCloseKilled() ? 4 : byte1) == 0) {
 new IsoZombieGiblets(
 IsoZombieGiblets.GibletType.A,
 this->getCell(),
 this->getX(),
 this->getY(),
 this->getZ() + float0,
 this->getHitDir().x * 3.8F,
 this->getHitDir().y * 3.8F
 );
 }

 if (Rand.Next(this->isCloseKilled() ? 4 : byte1) == 0) {
 new IsoZombieGiblets(
 IsoZombieGiblets.GibletType.A,
 this->getCell(),
 this->getX(),
 this->getY(),
 this->getZ() + float0,
 this->getHitDir().x * 3.9F,
 this->getHitDir().y * 3.9F
 );
 }

 if (Rand.Next(this->isCloseKilled() ? 4 : byte1) == 0) {
 new IsoZombieGiblets(
 IsoZombieGiblets.GibletType.A,
 this->getCell(),
 this->getX(),
 this->getY(),
 this->getZ() + float0,
 this->getHitDir().x * 1.5F,
 this->getHitDir().y * 1.5F
 );
 }

 if (Rand.Next(this->isCloseKilled() ? 4 : byte1) == 0) {
 new IsoZombieGiblets(
 IsoZombieGiblets.GibletType.A,
 this->getCell(),
 this->getX(),
 this->getY(),
 this->getZ() + float0,
 this->getHitDir().x * 3.8F,
 this->getHitDir().y * 3.8F
 );
 }

 if (Rand.Next(this->isCloseKilled() ? 4 : byte1) == 0) {
 new IsoZombieGiblets(
 IsoZombieGiblets.GibletType.A,
 this->getCell(),
 this->getX(),
 this->getY(),
 this->getZ() + float0,
 this->getHitDir().x * 3.9F,
 this->getHitDir().y * 3.9F
 );
 }

 if (Rand.Next(this->isCloseKilled() ? 9 : 6) == 0) {
 new IsoZombieGiblets(
 IsoZombieGiblets.GibletType.Eye,
 this->getCell(),
 this->getX(),
 this->getY(),
 this->getZ() + float0,
 this->getHitDir().x * 0.8F,
 this->getHitDir().y * 0.8F
 );
 }
 }
 }
 }

 if (this->isDoDeathSound()) {
 this->playDeadSound();
 }

 this->setDoDeathSound(false);
 }

 bool TestIfSeen(int int0) {
 IsoPlayer player = IsoPlayer.players[int0];
 if (player != nullptr && this != player && !GameServer.bServer) {
 float float0 = this->DistToProper(player);
 if (float0 > GameTime.getInstance().getViewDist()) {
 return false;
 } else {
 bool boolean0 = this->current.isCanSee(int0);
 if (!boolean0 && this->current.isCouldSee(int0) {
 boolean0 = float0 < player.getSeeNearbyCharacterDistance();
 }

 if (!boolean0) {
 return false;
 } else {
 ColorInfo colorInfo = this->getCurrentSquare().lighting[int0].lightInfo();
 float float1 = (colorInfo.r + colorInfo.g + colorInfo.b) / 3.0F;
 if (float1 > 0.6F) {
 float1 = 1.0F;
 }

 float float2 = 1.0F - float0 / GameTime.getInstance().getViewDist();
 if (float1 == 1.0F && float2 > 0.3F) {
 float2 = 1.0F;
 }

 float float3 = player.getDotWithForwardDirection(this->getX(), this->getY());
 if (float3 < 0.5F) {
 float3 = 0.5F;
 }

 float1 *= float3;
 if (float1 < 0.0F) {
 float1 = 0.0F;
 }

 if (float0 <= 1.0F) {
 float2 = 1.0F;
 float1 *= 2.0F;
 }

 float1 *= float2;
 float1 *= 100.0F;
 return float1 > 0.025F;
 }
 }
 } else {
 return false;
 }
 }

 void DoLand() {
 if (!(this->fallTime < 20.0F) && !this->isClimbing()) {
 if (this instanceof IsoPlayer) {
 if (GameServer.bServer) {
 return;
 }

 if (GameClient.bClient && ((IsoPlayer)this).bRemote) {
 return;
 }

 if (((IsoPlayer)this).isGhostMode()) {
 return;
 }
 }

 if (this->isZombie()) {
 if (this->fallTime > 50.0F) {
 this->hitDir.x = this->hitDir.y = 0.0F;
 if (!((IsoZombie)this).bCrawling && (Rand.Next(100) < 80 || this->fallTime > 80.0F) {
 this->setVariable("bHardFall", true);
 }

 this->playHurtSound();
 float float0 = Rand.Next(150) / 1000.0F;
 this->Health = this->Health - float0 * this->fallTime / 50.0F;
 this->setAttackedBy(nullptr);
 }
 } else {
 bool boolean0 = Rand.Next(80) == 0;
 float float1 = this->fallTime;
 float1 *= Math.min(1.8F, this->getInventory().getCapacityWeight() / this->getInventory().getMaxWeight());
 if (this->getCurrentSquare().getFloor() != nullptr
 && this->getCurrentSquare().getFloor().getSprite().getName() != nullptr
 && this->getCurrentSquare().getFloor().getSprite().getName().startsWith("blends_natural")) {
 float1 *= 0.8F;
 if (!boolean0) {
 boolean0 = Rand.Next(65) == 0;
 }
 }

 if (!boolean0) {
 if (this->Traits.Obese.isSet() || this->Traits.Emaciated.isSet()) {
 float1 *= 1.4F;
 }

 if (this->Traits.Overweight.isSet() || this->Traits.VeryUnderweight.isSet()) {
 float1 *= 1.2F;
 }

 float1 *= Math.max(0.1F, 1.0F - this->getPerkLevel(PerkFactory.Perks.Fitness) * 0.1F);
 if (this->fallTime > 135.0F) {
 float1 = 1000.0F;
 }

 this->BodyDamage.ReduceGeneralHealth(float1);
 LuaEventManager.triggerEvent("OnPlayerGetDamage", this, "FALLDOWN", float1);
 if (this->fallTime > 70.0F) {
 int int0 = 100 - (int)(this->fallTime * 0.6);
 if (this->getInventory().getMaxWeight() - this->getInventory().getCapacityWeight() < 2.0F) {
 int0 = (int)(int0 - this->getInventory().getCapacityWeight() / this->getInventory().getMaxWeight() * 100.0F / 5.0F);
 }

 if (this->Traits.Obese.isSet() || this->Traits.Emaciated.isSet()) {
 int0 -= 20;
 }

 if (this->Traits.Overweight.isSet() || this->Traits.VeryUnderweight.isSet()) {
 int0 -= 10;
 }

 if (this->getPerkLevel(PerkFactory.Perks.Fitness) > 4) {
 int0 += (this->getPerkLevel(PerkFactory.Perks.Fitness) - 4) * 3;
 }

 if (Rand.Next(100) >= int0) {
 if (!SandboxOptions.instance.BoneFracture.getValue()) {
 return;
 }

 float float2 = Rand.Next(50, 80);
 if (this->Traits.FastHealer.isSet()) {
 float2 = Rand.Next(30, 50);
 } else if (this->Traits.SlowHealer.isSet()) {
 float2 = Rand.Next(80, 150);
 }

 switch (SandboxOptions.instance.InjurySeverity.getValue()) {
 case 1:
 float2 *= 0.5F;
 break;
 case 3:
 float2 *= 1.5F;
 }

 this->getBodyDamage()
 .getBodyPart(
 BodyPartType.FromIndex(
 Rand.Next(BodyPartType.ToIndex(BodyPartType.UpperLeg_L), BodyPartType.ToIndex(BodyPartType.Foot_R) + 1)
 )
 )
 .setFractureTime(float2);
 } else if (Rand.Next(100) >= int0 - 10) {
 this->getBodyDamage()
 .getBodyPart(
 BodyPartType.FromIndex(
 Rand.Next(BodyPartType.ToIndex(BodyPartType.UpperLeg_L), BodyPartType.ToIndex(BodyPartType.Foot_R) + 1)
 )
 )
 .generateDeepWound();
 }
 }
 }
 }
 }
 }

 /**
 * @return the FollowingTarget
 */
 IsoGameCharacter getFollowingTarget() {
 return this->FollowingTarget;
 }

 /**
 * 
 * @param _FollowingTarget the FollowingTarget to set
 */
 void setFollowingTarget(IsoGameCharacter _FollowingTarget) {
 this->FollowingTarget = _FollowingTarget;
 }

 /**
 * @return the LocalList
 */
 public ArrayList<IsoMovingObject> getLocalList() {
 return this->LocalList;
 }

 /**
 * @return the LocalNeutralList
 */
 public ArrayList<IsoMovingObject> getLocalNeutralList() {
 return this->LocalNeutralList;
 }

 /**
 * @return the LocalGroupList
 */
 public ArrayList<IsoMovingObject> getLocalGroupList() {
 return this->LocalGroupList;
 }

 /**
 * @return the LocalRelevantEnemyList
 */
 public ArrayList<IsoMovingObject> getLocalRelevantEnemyList() {
 return this->LocalRelevantEnemyList;
 }

 /**
 * @return the dangerLevels
 */
 float getDangerLevels() {
 return this->dangerLevels;
 }

 /**
 * 
 * @param _dangerLevels the dangerLevels to set
 */
 void setDangerLevels(float _dangerLevels) {
 this->dangerLevels = _dangerLevels;
 }

 /**
 * @return the PerkList
 */
 public ArrayList<IsoGameCharacter.PerkInfo> getPerkList() {
 return this->PerkList;
 }

 /**
 * @return the leaveBodyTimedown
 */
 float getLeaveBodyTimedown() {
 return this->leaveBodyTimedown;
 }

 /**
 * 
 * @param _leaveBodyTimedown the leaveBodyTimedown to set
 */
 void setLeaveBodyTimedown(float _leaveBodyTimedown) {
 this->leaveBodyTimedown = _leaveBodyTimedown;
 }

 /**
 * @return the AllowConversation
 */
 bool isAllowConversation() {
 return this->AllowConversation;
 }

 /**
 * 
 * @param _AllowConversation the AllowConversation to set
 */
 void setAllowConversation(bool _AllowConversation) {
 this->AllowConversation = _AllowConversation;
 }

 /**
 * @return the ReanimateTimer
 */
 float getReanimateTimer() {
 return this->ReanimateTimer;
 }

 /**
 * 
 * @param _ReanimateTimer the ReanimateTimer to set
 */
 void setReanimateTimer(float _ReanimateTimer) {
 this->ReanimateTimer = _ReanimateTimer;
 }

 /**
 * @return the ReanimAnimFrame
 */
 int getReanimAnimFrame() {
 return this->ReanimAnimFrame;
 }

 /**
 * 
 * @param _ReanimAnimFrame the ReanimAnimFrame to set
 */
 void setReanimAnimFrame(int _ReanimAnimFrame) {
 this->ReanimAnimFrame = _ReanimAnimFrame;
 }

 /**
 * @return the ReanimAnimDelay
 */
 int getReanimAnimDelay() {
 return this->ReanimAnimDelay;
 }

 /**
 * 
 * @param _ReanimAnimDelay the ReanimAnimDelay to set
 */
 void setReanimAnimDelay(int _ReanimAnimDelay) {
 this->ReanimAnimDelay = _ReanimAnimDelay;
 }

 /**
 * @return the Reanim
 */
 bool isReanim() {
 return this->Reanim;
 }

 /**
 * 
 * @param _Reanim the Reanim to set
 */
 void setReanim(bool _Reanim) {
 this->Reanim = _Reanim;
 }

 /**
 * @return the VisibleToNPCs
 */
 bool isVisibleToNPCs() {
 return this->VisibleToNPCs;
 }

 /**
 * 
 * @param _VisibleToNPCs the VisibleToNPCs to set
 */
 void setVisibleToNPCs(bool _VisibleToNPCs) {
 this->VisibleToNPCs = _VisibleToNPCs;
 }

 /**
 * @return the DieCount
 */
 int getDieCount() {
 return this->DieCount;
 }

 /**
 * 
 * @param _DieCount the DieCount to set
 */
 void setDieCount(int _DieCount) {
 this->DieCount = _DieCount;
 }

 /**
 * @return the llx
 */
 float getLlx() {
 return this->llx;
 }

 /**
 * 
 * @param _llx the llx to set
 */
 void setLlx(float _llx) {
 this->llx = _llx;
 }

 /**
 * @return the lly
 */
 float getLly() {
 return this->lly;
 }

 /**
 * 
 * @param _lly the lly to set
 */
 void setLly(float _lly) {
 this->lly = _lly;
 }

 /**
 * @return the llz
 */
 float getLlz() {
 return this->llz;
 }

 /**
 * 
 * @param _llz the llz to set
 */
 void setLlz(float _llz) {
 this->llz = _llz;
 }

 /**
 * @return the RemoteID
 */
 int getRemoteID() {
 return this->RemoteID;
 }

 /**
 * 
 * @param _RemoteID the RemoteID to set
 */
 void setRemoteID(int _RemoteID) {
 this->RemoteID = _RemoteID;
 }

 /**
 * @return the NumSurvivorsInVicinity
 */
 int getNumSurvivorsInVicinity() {
 return this->NumSurvivorsInVicinity;
 }

 /**
 * 
 * @param _NumSurvivorsInVicinity the NumSurvivorsInVicinity to set
 */
 void setNumSurvivorsInVicinity(int _NumSurvivorsInVicinity) {
 this->NumSurvivorsInVicinity = _NumSurvivorsInVicinity;
 }

 /**
 * @return the LevelUpMultiplier
 */
 float getLevelUpMultiplier() {
 return this->LevelUpMultiplier;
 }

 /**
 * 
 * @param _LevelUpMultiplier the LevelUpMultiplier to set
 */
 void setLevelUpMultiplier(float _LevelUpMultiplier) {
 this->LevelUpMultiplier = _LevelUpMultiplier;
 }

 /**
 * @return the xp
 */
 public IsoGameCharacter.XP getXp() {
 return this->xp;
 }

 /**
 * 
 * @param _xp the xp to set
 */
 void setXp(IsoGameCharacter.XP _xp) {
 this->xp = _xp;
 }

 /**
 * @return the LastLocalEnemies
 */
 int getLastLocalEnemies() {
 return this->LastLocalEnemies;
 }

 /**
 * 
 * @param _LastLocalEnemies the LastLocalEnemies to set
 */
 void setLastLocalEnemies(int _LastLocalEnemies) {
 this->LastLocalEnemies = _LastLocalEnemies;
 }

 /**
 * @return the VeryCloseEnemyList
 */
 public ArrayList<IsoMovingObject> getVeryCloseEnemyList() {
 return this->VeryCloseEnemyList;
 }

 /**
 * @return the LastKnownLocation
 */
 public HashMap<String, IsoGameCharacter.Location> getLastKnownLocation() {
 return this->LastKnownLocation;
 }

 /**
 * @return the AttackedBy
 */
 IsoGameCharacter getAttackedBy() {
 return this->AttackedBy;
 }

 /**
 * 
 * @param _AttackedBy the AttackedBy to set
 */
 void setAttackedBy(IsoGameCharacter _AttackedBy) {
 this->AttackedBy = _AttackedBy;
 }

 /**
 * @return the IgnoreStaggerBack
 */
 bool isIgnoreStaggerBack() {
 return this->IgnoreStaggerBack;
 }

 /**
 * 
 * @param _IgnoreStaggerBack the IgnoreStaggerBack to set
 */
 void setIgnoreStaggerBack(bool _IgnoreStaggerBack) {
 this->IgnoreStaggerBack = _IgnoreStaggerBack;
 }

 /**
 * @return the AttackWasSuperAttack
 */
 bool isAttackWasSuperAttack() {
 return this->AttackWasSuperAttack;
 }

 /**
 * 
 * @param _AttackWasSuperAttack the AttackWasSuperAttack to set
 */
 void setAttackWasSuperAttack(bool _AttackWasSuperAttack) {
 this->AttackWasSuperAttack = _AttackWasSuperAttack;
 }

 /**
 * @return the TimeThumping
 */
 int getTimeThumping() {
 return this->TimeThumping;
 }

 /**
 * 
 * @param _TimeThumping the TimeThumping to set
 */
 void setTimeThumping(int _TimeThumping) {
 this->TimeThumping = _TimeThumping;
 }

 /**
 * @return the PatienceMax
 */
 int getPatienceMax() {
 return this->PatienceMax;
 }

 /**
 * 
 * @param _PatienceMax the PatienceMax to set
 */
 void setPatienceMax(int _PatienceMax) {
 this->PatienceMax = _PatienceMax;
 }

 /**
 * @return the PatienceMin
 */
 int getPatienceMin() {
 return this->PatienceMin;
 }

 /**
 * 
 * @param _PatienceMin the PatienceMin to set
 */
 void setPatienceMin(int _PatienceMin) {
 this->PatienceMin = _PatienceMin;
 }

 /**
 * @return the Patience
 */
 int getPatience() {
 return this->Patience;
 }

 /**
 * 
 * @param _Patience the Patience to set
 */
 void setPatience(int _Patience) {
 this->Patience = _Patience;
 }

 /**
 * @return the CharacterActions
 */
 public Stack<BaseAction> getCharacterActions() {
 return this->CharacterActions;
 }

 bool hasTimedActions() {
 return !this->CharacterActions.empty() || this->getVariableBoolean("IsPerformingAnAction");
 }

 /**
 * @return the character's forward direction vector
 */
 Vector2 getForwardDirection() {
 return this->m_forwardDirection;
 }

 /**
 * 
 * @param dir The character's new forward direction.
 */
 void setForwardDirection(Vector2 dir) {
 if (dir != nullptr) {
 this->setForwardDirection(dir.x, dir.y);
 }
 }

 void setForwardDirection(float x, float y) {
 this->m_forwardDirection.x = x;
 this->m_forwardDirection.y = y;
 }

 void zeroForwardDirectionX() {
 this->setForwardDirection(0.0F, 1.0F);
 }

 void zeroForwardDirectionY() {
 this->setForwardDirection(1.0F, 0.0F);
 }

 /**
 * The forward direction angle, in degrees.
 */
 float getDirectionAngle() {
 return (180.0F / (float)Math.PI) * this->getForwardDirection().getDirection();
 }

 void setDirectionAngle(float angleDegrees) {
 float float0 = (float) (Math.PI / 180.0) * angleDegrees;
 Vector2 vector = this->getForwardDirection();
 vector.setDirection(float0);
 }

 float getAnimAngle() {
 return this->m_animPlayer != nullptr && this->m_animPlayer.isReady() && !this->m_animPlayer.isBoneTransformsNeedFirstFrame()
 ? (180.0F / (float)Math.PI) * this->m_animPlayer.getAngle()
 : this->getDirectionAngle();
 }

 float getAnimAngleRadians() {
 return this->m_animPlayer != nullptr && this->m_animPlayer.isReady() && !this->m_animPlayer.isBoneTransformsNeedFirstFrame()
 ? this->m_animPlayer.getAngle()
 : this->m_forwardDirection.getDirection();
 }

 Vector2 getAnimVector(Vector2 out) {
 return out.setLengthAndDirection(this->getAnimAngleRadians(), 1.0F);
 }

 float getLookAngleRadians() {
 return this->m_animPlayer != nullptr && this->m_animPlayer.isReady()
 ? this->m_animPlayer.getAngle() + this->m_animPlayer.getTwistAngle()
 : this->getForwardDirection().getDirection();
 }

 Vector2 getLookVector(Vector2 vector2) {
 return vector2.setLengthAndDirection(this->getLookAngleRadians(), 1.0F);
 }

 float getDotWithForwardDirection(Vector3 bonePos) {
 return this->getDotWithForwardDirection(bonePos.x, bonePos.y);
 }

 float getDotWithForwardDirection(float targetX, float targetY) {
 Vector2 vector0 = IsoGameCharacter.L_getDotWithForwardDirection.v1.set(targetX - this->getX(), targetY - this->getY());
 vector0.normalize();
 Vector2 vector1 = this->getLookVector(IsoGameCharacter.L_getDotWithForwardDirection.v2);
 vector1.normalize();
 return vector0.dot(vector1);
 }

 /**
 * @return the Asleep
 */
 bool isAsleep() {
 return this->Asleep;
 }

 /**
 * 
 * @param _Asleep the Asleep to set
 */
 void setAsleep(bool _Asleep) {
 this->Asleep = _Asleep;
 }

 /**
 * @return the ZombieKills
 */
 int getZombieKills() {
 return this->ZombieKills;
 }

 /**
 * 
 * @param _ZombieKills the ZombieKills to set
 */
 void setZombieKills(int _ZombieKills) {
 this->ZombieKills = _ZombieKills;
 }

 /**
 * @return the LastZombieKills
 */
 int getLastZombieKills() {
 return this->LastZombieKills;
 }

 /**
 * 
 * @param _LastZombieKills the LastZombieKills to set
 */
 void setLastZombieKills(int _LastZombieKills) {
 this->LastZombieKills = _LastZombieKills;
 }

 /**
 * @return the superAttack
 */
 bool isSuperAttack() {
 return this->superAttack;
 }

 /**
 * 
 * @param _superAttack the superAttack to set
 */
 void setSuperAttack(bool _superAttack) {
 this->superAttack = _superAttack;
 }

 /**
 * @return the ForceWakeUpTime
 */
 float getForceWakeUpTime() {
 return this->ForceWakeUpTime;
 }

 /**
 * 
 * @param _ForceWakeUpTime the ForceWakeUpTime to set
 */
 void setForceWakeUpTime(float _ForceWakeUpTime) {
 this->ForceWakeUpTime = _ForceWakeUpTime;
 }

 void forceAwake() {
 if (this->isAsleep()) {
 this->ForceWakeUp = true;
 }
 }

 /**
 * @return the BodyDamage
 */
 BodyDamage getBodyDamage() {
 return this->BodyDamage;
 }

 BodyDamage getBodyDamageRemote() {
 if (this->BodyDamageRemote.empty()) {
 this->BodyDamageRemote = new BodyDamage(nullptr);
 }

 return this->BodyDamageRemote;
 }

 void resetBodyDamageRemote() {
 this->BodyDamageRemote = nullptr;
 }

 /**
 * @return the defaultState
 */
 State getDefaultState() {
 return this->defaultState;
 }

 /**
 * 
 * @param _defaultState the defaultState to set
 */
 void setDefaultState(State _defaultState) {
 this->defaultState = _defaultState;
 }

 /**
 * @return the descriptor
 */
 SurvivorDesc getDescriptor() {
 return this->descriptor;
 }

 /**
 * 
 * @param _descriptor the descriptor to set
 */
 void setDescriptor(SurvivorDesc _descriptor) {
 this->descriptor = _descriptor;
 }

 std::string getFullName() {
 return this->descriptor != nullptr ? this->descriptor.forename + " " + this->descriptor.surname : "Bob Smith";
 }

 BaseVisual getVisual() {
 throw RuntimeException("subclasses must implement this");
 }

 ItemVisuals getItemVisuals() {
 throw RuntimeException("subclasses must implement this");
 }

 void getItemVisuals(ItemVisuals itemVisuals) {
 this->getWornItems().getItemVisuals(itemVisuals);
 }

 bool isUsingWornItems() {
 return this->wornItems != nullptr;
 }

 /**
 * @return the FamiliarBuildings
 */
 public Stack<IsoBuilding> getFamiliarBuildings() {
 return this->FamiliarBuildings;
 }

 /**
 * @return the finder
 */
 AStarPathFinderResult getFinder() {
 return this->finder;
 }

 /**
 * @return the FireKillRate
 */
 float getFireKillRate() {
 return this->FireKillRate;
 }

 /**
 * 
 * @param _FireKillRate the FireKillRate to set
 */
 void setFireKillRate(float _FireKillRate) {
 this->FireKillRate = _FireKillRate;
 }

 /**
 * @return the FireSpreadProbability
 */
 int getFireSpreadProbability() {
 return this->FireSpreadProbability;
 }

 /**
 * 
 * @param _FireSpreadProbability the FireSpreadProbability to set
 */
 void setFireSpreadProbability(int _FireSpreadProbability) {
 this->FireSpreadProbability = _FireSpreadProbability;
 }

 /**
 * @return the Health
 */
 float getHealth() {
 return this->Health;
 }

 /**
 * 
 * @param _Health the Health to set
 */
 void setHealth(float _Health) {
 this->Health = _Health;
 }

 bool isOnDeathDone() {
 return this->bDead;
 }

 void setOnDeathDone(bool done) {
 this->bDead = done;
 }

 bool isOnKillDone() {
 return this->bKill;
 }

 void setOnKillDone(bool done) {
 this->bKill = done;
 }

 bool isDeathDragDown() {
 return this->bDeathDragDown;
 }

 void setDeathDragDown(bool dragDown) {
 this->bDeathDragDown = dragDown;
 }

 bool isPlayingDeathSound() {
 return this->bPlayingDeathSound;
 }

 void setPlayingDeathSound(bool playing) {
 this->bPlayingDeathSound = playing;
 }

 /**
 * @return the hurtSound
 */
 std::string getHurtSound() {
 return this->hurtSound;
 }

 /**
 * 
 * @param _hurtSound the hurtSound to set
 */
 void setHurtSound(const std::string& _hurtSound) {
 this->hurtSound = _hurtSound;
 }

 /**
 * @return the IgnoreMovementForDirection
 */
 bool isIgnoreMovementForDirection() {
 return false;
 }

 /**
 * @return the inventory
 */
 ItemContainer getInventory() {
 return this->inventory;
 }

 /**
 * 
 * @param _inventory the inventory to set
 */
 void setInventory(ItemContainer _inventory) {
 _inventory.parent = this;
 this->inventory = _inventory;
 this->inventory.setExplored(true);
 }

 bool isPrimaryEquipped(const std::string& item) {
 return this->leftHandItem.empty() ? false : this->leftHandItem.getFullType() == item) || this->leftHandItem.getType() == item);
 }

 /**
 * @return the leftHandItem
 */
 InventoryItem getPrimaryHandItem() {
 return this->leftHandItem;
 }

 /**
 * 
 * @param _leftHandItem the leftHandItem to set
 */
 void setPrimaryHandItem(InventoryItem _leftHandItem) {
 this->setEquipParent(this->leftHandItem, _leftHandItem);
 this->leftHandItem = _leftHandItem;
 if (GameClient.bClient && this instanceof IsoPlayer && ((IsoPlayer)this).isLocalPlayer()) {
 GameClient.instance.equip((IsoPlayer)this, 0);
 }

 LuaEventManager.triggerEvent("OnEquipPrimary", this, _leftHandItem);
 this->resetEquippedHandsModels();
 this->setVariable("Weapon", WeaponType.getWeaponType(this).type);
 if (_leftHandItem != nullptr && _leftHandItem instanceof HandWeapon && !StringUtils.isNullOrEmpty(((HandWeapon)_leftHandItem).getFireMode())) {
 this->setVariable("FireMode", ((HandWeapon)_leftHandItem).getFireMode());
 } else {
 this->clearVariable("FireMode");
 }
 }

 void setEquipParent(InventoryItem item0, InventoryItem item1) {
 if (item0 != nullptr) {
 item0.setEquipParent(nullptr);
 }

 if (item1 != nullptr) {
 item1.setEquipParent(this);
 }
 }

 void initWornItems(const std::string& bodyLocationGroupName) {
 BodyLocationGroup bodyLocationGroup = BodyLocations.getGroup(bodyLocationGroupName);
 this->wornItems = new WornItems(bodyLocationGroup);
 }

 WornItems getWornItems() {
 return this->wornItems;
 }

 void setWornItems(WornItems other) {
 this->wornItems = new WornItems(other);
 }

 InventoryItem getWornItem(const std::string& location) {
 return this->wornItems.getItem(location);
 }

 void setWornItem(const std::string& location, InventoryItem item) {
 this->setWornItem(location, item, true);
 }

 void setWornItem(const std::string& location, InventoryItem item, bool forceDropTooHeavy) {
 InventoryItem _item = this->wornItems.getItem(location);
 if (item != _item) {
 IsoCell cell = IsoWorld.instance.CurrentCell;
 if (_item != nullptr && cell != nullptr) {
 cell.addToProcessItemsRemove(_item);
 }

 this->wornItems.setItem(location, item);
 if (item != nullptr && cell != nullptr) {
 if (item.getContainer() != nullptr) {
 item.getContainer().parent = this;
 }

 cell.addToProcessItems(item);
 }

 if (forceDropTooHeavy && _item != nullptr && this instanceof IsoPlayer && !this->getInventory().hasRoomFor(this, _item) {
 IsoGridSquare square = this->getCurrentSquare();
 square = this->getSolidFloorAt(square.x, square.y, square.z);
 if (square != nullptr) {
 float float0 = Rand.Next(0.1F, 0.9F);
 float float1 = Rand.Next(0.1F, 0.9F);
 float float2 = square.getApparentZ(float0, float1) - square.getZ();
 square.AddWorldInventoryItem(_item, float0, float1, float2);
 this->getInventory().Remove(_item);
 }
 }

 this->resetModelNextFrame();
 if (this->clothingWetness != nullptr) {
 this->clothingWetness.changed = true;
 }

 if (GameClient.bClient && this instanceof IsoPlayer && ((IsoPlayer)this).isLocalPlayer()) {
 GameClient.instance.sendClothing((IsoPlayer)this, location, item);
 }

 this->onWornItemsChanged();
 }
 }

 void removeWornItem(InventoryItem item) {
 this->removeWornItem(item, true);
 }

 void removeWornItem(InventoryItem item, bool forceDropTooHeavy) {
 std::string string = this->wornItems.getLocation(item);
 if (string != nullptr) {
 this->setWornItem(string, nullptr, forceDropTooHeavy);
 }
 }

 void clearWornItems() {
 if (this->wornItems != nullptr) {
 this->wornItems.clear();
 if (this->clothingWetness != nullptr) {
 this->clothingWetness.changed = true;
 }

 this->onWornItemsChanged();
 }
 }

 BodyLocationGroup getBodyLocationGroup() {
 return this->wornItems.empty() ? nullptr : this->wornItems.getBodyLocationGroup();
 }

 void onWornItemsChanged() {
 }

 void initAttachedItems(const std::string& groupName) {
 AttachedLocationGroup attachedLocationGroup = AttachedLocations.getGroup(groupName);
 this->attachedItems = new AttachedItems(attachedLocationGroup);
 }

 AttachedItems getAttachedItems() {
 return this->attachedItems;
 }

 void setAttachedItems(AttachedItems other) {
 this->attachedItems = new AttachedItems(other);
 }

 InventoryItem getAttachedItem(const std::string& location) {
 return this->attachedItems.getItem(location);
 }

 void setAttachedItem(const std::string& location, InventoryItem item) {
 InventoryItem _item = this->attachedItems.getItem(location);
 IsoCell cell = IsoWorld.instance.CurrentCell;
 if (_item != nullptr && cell != nullptr) {
 cell.addToProcessItemsRemove(_item);
 }

 this->attachedItems.setItem(location, item);
 if (item != nullptr && cell != nullptr) {
 InventoryContainer inventoryContainer = Type.tryCastTo(item, InventoryContainer.class);
 if (inventoryContainer != nullptr && inventoryContainer.getInventory() != nullptr) {
 inventoryContainer.getInventory().parent = this;
 }

 cell.addToProcessItems(item);
 }

 this->resetEquippedHandsModels();
 IsoPlayer player = Type.tryCastTo(this, IsoPlayer.class);
 if (GameClient.bClient && player != nullptr && player.isLocalPlayer()) {
 GameClient.instance.sendAttachedItem(player, location, item);
 }

 if (!GameServer.bServer && player != nullptr && player.isLocalPlayer()) {
 LuaEventManager.triggerEvent("OnClothingUpdated", this);
 }
 }

 void removeAttachedItem(InventoryItem item) {
 std::string string = this->attachedItems.getLocation(item);
 if (string != nullptr) {
 this->setAttachedItem(string, nullptr);
 }
 }

 void clearAttachedItems() {
 if (this->attachedItems != nullptr) {
 this->attachedItems.clear();
 }
 }

 AttachedLocationGroup getAttachedLocationGroup() {
 return this->attachedItems.empty() ? nullptr : this->attachedItems.getGroup();
 }

 ClothingWetness getClothingWetness() {
 return this->clothingWetness;
 }

 /**
 * @return the ClothingItem_Head
 */
 InventoryItem getClothingItem_Head() {
 return this->getWornItem("Hat");
 }

 /**
 * 
 * @param item the ClothingItem_Head to set
 */
 void setClothingItem_Head(InventoryItem item) {
 this->setWornItem("Hat", item);
 }

 /**
 * @return the ClothingItem_Torso
 */
 InventoryItem getClothingItem_Torso() {
 return this->getWornItem("Tshirt");
 }

 void setClothingItem_Torso(InventoryItem item) {
 this->setWornItem("Tshirt", item);
 }

 InventoryItem getClothingItem_Back() {
 return this->getWornItem("Back");
 }

 void setClothingItem_Back(InventoryItem item) {
 this->setWornItem("Back", item);
 }

 /**
 * @return the ClothingItem_Hands
 */
 InventoryItem getClothingItem_Hands() {
 return this->getWornItem("Hands");
 }

 /**
 * 
 * @param item the ClothingItem_Hands to set
 */
 void setClothingItem_Hands(InventoryItem item) {
 this->setWornItem("Hands", item);
 }

 /**
 * @return the ClothingItem_Legs
 */
 InventoryItem getClothingItem_Legs() {
 return this->getWornItem("Pants");
 }

 /**
 * 
 * @param item the ClothingItem_Legs to set
 */
 void setClothingItem_Legs(InventoryItem item) {
 this->setWornItem("Pants", item);
 }

 /**
 * @return the ClothingItem_Feet
 */
 InventoryItem getClothingItem_Feet() {
 return this->getWornItem("Shoes");
 }

 /**
 * 
 * @param item the ClothingItem_Feet to set
 */
 void setClothingItem_Feet(InventoryItem item) {
 this->setWornItem("Shoes", item);
 }

 /**
 * @return the NextWander
 */
 int getNextWander() {
 return this->NextWander;
 }

 /**
 * 
 * @param _NextWander the NextWander to set
 */
 void setNextWander(int _NextWander) {
 this->NextWander = _NextWander;
 }

 /**
 * @return the OnFire
 */
 bool isOnFire() {
 return this->OnFire;
 }

 /**
 * 
 * @param _OnFire the OnFire to set
 */
 void setOnFire(bool _OnFire) {
 this->OnFire = _OnFire;
 if (GameServer.bServer) {
 if (_OnFire) {
 IsoFireManager.addCharacterOnFire(this);
 } else {
 IsoFireManager.deleteCharacterOnFire(this);
 }
 }
 }

 void removeFromWorld() {
 if (GameServer.bServer) {
 IsoFireManager.deleteCharacterOnFire(this);
 }

 super.removeFromWorld();
 }

 /**
 * @return the pathIndex
 */
 int getPathIndex() {
 return this->pathIndex;
 }

 /**
 * 
 * @param _pathIndex the pathIndex to set
 */
 void setPathIndex(int _pathIndex) {
 this->pathIndex = _pathIndex;
 }

 /**
 * @return the PathTargetX
 */
 int getPathTargetX() {
 return (int)this->getPathFindBehavior2().getTargetX();
 }

 /**
 * @return the PathTargetY
 */
 int getPathTargetY() {
 return (int)this->getPathFindBehavior2().getTargetY();
 }

 /**
 * @return the PathTargetZ
 */
 int getPathTargetZ() {
 return (int)this->getPathFindBehavior2().getTargetZ();
 }

 /**
 * @return the rightHandItem
 */
 InventoryItem getSecondaryHandItem() {
 return this->rightHandItem;
 }

 /**
 * 
 * @param _rightHandItem the rightHandItem to set
 */
 void setSecondaryHandItem(InventoryItem _rightHandItem) {
 this->setEquipParent(this->rightHandItem, _rightHandItem);
 this->rightHandItem = _rightHandItem;
 if (GameClient.bClient && this instanceof IsoPlayer && ((IsoPlayer)this).isLocalPlayer()) {
 GameClient.instance.equip((IsoPlayer)this, 1);
 }

 LuaEventManager.triggerEvent("OnEquipSecondary", this, _rightHandItem);
 this->resetEquippedHandsModels();
 this->setVariable("Weapon", WeaponType.getWeaponType(this).type);
 }

 bool isHandItem(InventoryItem item) {
 return this->isPrimaryHandItem(item) || this->isSecondaryHandItem(item);
 }

 bool isPrimaryHandItem(InventoryItem item) {
 return item != nullptr && this->getPrimaryHandItem() == item;
 }

 bool isSecondaryHandItem(InventoryItem item) {
 return item != nullptr && this->getSecondaryHandItem() == item;
 }

 bool isItemInBothHands(InventoryItem item) {
 return this->isPrimaryHandItem(item) && this->isSecondaryHandItem(item);
 }

 bool removeFromHands(InventoryItem item) {
 bool boolean0 = true;
 if (this->isPrimaryHandItem(item) {
 this->setPrimaryHandItem(nullptr);
 }

 if (this->isSecondaryHandItem(item) {
 this->setSecondaryHandItem(nullptr);
 }

 return boolean0;
 }

 /**
 * @return the SpeakColour
 */
 Color getSpeakColour() {
 return this->SpeakColour;
 }

 /**
 * 
 * @param _SpeakColour the SpeakColour to set
 */
 void setSpeakColour(Color _SpeakColour) {
 this->SpeakColour = _SpeakColour;
 }

 void setSpeakColourInfo(ColorInfo info) {
 this->SpeakColour = new Color(info.r, info.g, info.b, 1.0F);
 }

 /**
 * @return the slowFactor
 */
 float getSlowFactor() {
 return this->slowFactor;
 }

 /**
 * 
 * @param _slowFactor the slowFactor to set
 */
 void setSlowFactor(float _slowFactor) {
 this->slowFactor = _slowFactor;
 }

 /**
 * @return the slowTimer
 */
 float getSlowTimer() {
 return this->slowTimer;
 }

 /**
 * 
 * @param _slowTimer the slowTimer to set
 */
 void setSlowTimer(float _slowTimer) {
 this->slowTimer = _slowTimer;
 }

 /**
 * @return the bUseParts
 */
 bool isbUseParts() {
 return this->bUseParts;
 }

 /**
 * 
 * @param _bUseParts the bUseParts to set
 */
 void setbUseParts(bool _bUseParts) {
 this->bUseParts = _bUseParts;
 }

 /**
 * @return the Speaking
 */
 bool isSpeaking() {
 return this->IsSpeaking();
 }

 /**
 * 
 * @param _Speaking the Speaking to set
 */
 void setSpeaking(bool _Speaking) {
 this->Speaking = _Speaking;
 }

 /**
 * @return the SpeakTime
 */
 float getSpeakTime() {
 return this->SpeakTime;
 }

 /**
 * 
 * @param _SpeakTime the SpeakTime to set
 */
 void setSpeakTime(int _SpeakTime) {
 this->SpeakTime = _SpeakTime;
 }

 /**
 * @return the speedMod
 */
 float getSpeedMod() {
 return this->speedMod;
 }

 /**
 * 
 * @param _speedMod the speedMod to set
 */
 void setSpeedMod(float _speedMod) {
 this->speedMod = _speedMod;
 }

 /**
 * @return the staggerTimeMod
 */
 float getStaggerTimeMod() {
 return this->staggerTimeMod;
 }

 /**
 * 
 * @param _staggerTimeMod the staggerTimeMod to set
 */
 void setStaggerTimeMod(float _staggerTimeMod) {
 this->staggerTimeMod = _staggerTimeMod;
 }

 /**
 * @return the stateMachine
 */
 StateMachine getStateMachine() {
 return this->stateMachine;
 }

 /**
 * @return the Moodles
 */
 Moodles getMoodles() {
 return this->Moodles;
 }

 /**
 * @return the stats
 */
 Stats getStats() {
 return this->stats;
 }

 /**
 * @return the UsedItemsOn
 */
 public Stack<String> getUsedItemsOn() {
 return this->UsedItemsOn;
 }

 /**
 * @return the useHandWeapon
 */
 HandWeapon getUseHandWeapon() {
 return this->useHandWeapon;
 }

 /**
 * 
 * @param _useHandWeapon the useHandWeapon to set
 */
 void setUseHandWeapon(HandWeapon _useHandWeapon) {
 this->useHandWeapon = _useHandWeapon;
 }

 /**
 * @return the legsSprite
 */
 IsoSprite getLegsSprite() {
 return this->legsSprite;
 }

 /**
 * 
 * @param _legsSprite the legsSprite to set
 */
 void setLegsSprite(IsoSprite _legsSprite) {
 this->legsSprite = _legsSprite;
 }

 /**
 * @return the attackTargetSquare
 */
 IsoGridSquare getAttackTargetSquare() {
 return this->attackTargetSquare;
 }

 /**
 * 
 * @param _attackTargetSquare the attackTargetSquare to set
 */
 void setAttackTargetSquare(IsoGridSquare _attackTargetSquare) {
 this->attackTargetSquare = _attackTargetSquare;
 }

 /**
 * @return the BloodImpactX
 */
 float getBloodImpactX() {
 return this->BloodImpactX;
 }

 /**
 * 
 * @param _BloodImpactX the BloodImpactX to set
 */
 void setBloodImpactX(float _BloodImpactX) {
 this->BloodImpactX = _BloodImpactX;
 }

 /**
 * @return the BloodImpactY
 */
 float getBloodImpactY() {
 return this->BloodImpactY;
 }

 /**
 * 
 * @param _BloodImpactY the BloodImpactY to set
 */
 void setBloodImpactY(float _BloodImpactY) {
 this->BloodImpactY = _BloodImpactY;
 }

 /**
 * @return the BloodImpactZ
 */
 float getBloodImpactZ() {
 return this->BloodImpactZ;
 }

 /**
 * 
 * @param _BloodImpactZ the BloodImpactZ to set
 */
 void setBloodImpactZ(float _BloodImpactZ) {
 this->BloodImpactZ = _BloodImpactZ;
 }

 /**
 * @return the bloodSplat
 */
 IsoSprite getBloodSplat() {
 return this->bloodSplat;
 }

 /**
 * 
 * @param _bloodSplat the bloodSplat to set
 */
 void setBloodSplat(IsoSprite _bloodSplat) {
 this->bloodSplat = _bloodSplat;
 }

 /**
 * @return the bOnBed
 */
 bool isbOnBed() {
 return this->bOnBed;
 }

 /**
 * 
 * @param _bOnBed the bOnBed to set
 */
 void setbOnBed(bool _bOnBed) {
 this->bOnBed = _bOnBed;
 }

 /**
 * @return the moveForwardVec
 */
 Vector2 getMoveForwardVec() {
 return this->moveForwardVec;
 }

 /**
 * 
 * @param _moveForwardVec the moveForwardVec to set
 */
 void setMoveForwardVec(Vector2 _moveForwardVec) {
 this->moveForwardVec.set(_moveForwardVec);
 }

 /**
 * @return the pathing
 */
 bool isPathing() {
 return this->pathing;
 }

 /**
 * 
 * @param _pathing the pathing to set
 */
 void setPathing(bool _pathing) {
 this->pathing = _pathing;
 }

 /**
 * @return the LocalEnemyList
 */
 public Stack<IsoGameCharacter> getLocalEnemyList() {
 return this->LocalEnemyList;
 }

 /**
 * @return the EnemyList
 */
 public Stack<IsoGameCharacter> getEnemyList() {
 return this->EnemyList;
 }

 /**
 * @return the Traits
 */
 TraitCollection getTraits() {
 return this->getCharacterTraits();
 }

 /**
 * @return the CharacterTraits, a TraitCollection extended with direct links to known traits
 */
 public IsoGameCharacter.CharacterTraits getCharacterTraits() {
 return this->Traits;
 }

 /**
 * @return the maxWeight
 */
 int getMaxWeight() {
 return this->maxWeight;
 }

 /**
 * 
 * @param _maxWeight the maxWeight to set
 */
 void setMaxWeight(int _maxWeight) {
 this->maxWeight = _maxWeight;
 }

 /**
 * @return the maxWeightBase
 */
 int getMaxWeightBase() {
 return this->maxWeightBase;
 }

 /**
 * 
 * @param _maxWeightBase the maxWeightBase to set
 */
 void setMaxWeightBase(int _maxWeightBase) {
 this->maxWeightBase = _maxWeightBase;
 }

 /**
 * @return the SleepingTabletDelta
 */
 float getSleepingTabletDelta() {
 return this->SleepingTabletDelta;
 }

 /**
 * 
 * @param _SleepingTabletDelta the SleepingTabletDelta to set
 */
 void setSleepingTabletDelta(float _SleepingTabletDelta) {
 this->SleepingTabletDelta = _SleepingTabletDelta;
 }

 /**
 * @return the BetaEffect
 */
 float getBetaEffect() {
 return this->BetaEffect;
 }

 /**
 * 
 * @param _BetaEffect the BetaEffect to set
 */
 void setBetaEffect(float _BetaEffect) {
 this->BetaEffect = _BetaEffect;
 }

 /**
 * @return the DepressEffect
 */
 float getDepressEffect() {
 return this->DepressEffect;
 }

 /**
 * 
 * @param _DepressEffect the DepressEffect to set
 */
 void setDepressEffect(float _DepressEffect) {
 this->DepressEffect = _DepressEffect;
 }

 /**
 * @return the SleepingTabletEffect
 */
 float getSleepingTabletEffect() {
 return this->SleepingTabletEffect;
 }

 /**
 * 
 * @param _SleepingTabletEffect the SleepingTabletEffect to set
 */
 void setSleepingTabletEffect(float _SleepingTabletEffect) {
 this->SleepingTabletEffect = _SleepingTabletEffect;
 }

 /**
 * @return the BetaDelta
 */
 float getBetaDelta() {
 return this->BetaDelta;
 }

 /**
 * 
 * @param _BetaDelta the BetaDelta to set
 */
 void setBetaDelta(float _BetaDelta) {
 this->BetaDelta = _BetaDelta;
 }

 /**
 * @return the DepressDelta
 */
 float getDepressDelta() {
 return this->DepressDelta;
 }

 /**
 * 
 * @param _DepressDelta the DepressDelta to set
 */
 void setDepressDelta(float _DepressDelta) {
 this->DepressDelta = _DepressDelta;
 }

 /**
 * @return the PainEffect
 */
 float getPainEffect() {
 return this->PainEffect;
 }

 /**
 * 
 * @param _PainEffect the PainEffect to set
 */
 void setPainEffect(float _PainEffect) {
 this->PainEffect = _PainEffect;
 }

 /**
 * @return the PainDelta
 */
 float getPainDelta() {
 return this->PainDelta;
 }

 /**
 * 
 * @param _PainDelta the PainDelta to set
 */
 void setPainDelta(float _PainDelta) {
 this->PainDelta = _PainDelta;
 }

 /**
 * @return the bDoDefer
 */
 bool isbDoDefer() {
 return this->bDoDefer;
 }

 /**
 * 
 * @param _bDoDefer the bDoDefer to set
 */
 void setbDoDefer(bool _bDoDefer) {
 this->bDoDefer = _bDoDefer;
 }

 /**
 * @return the LastHeardSound
 */
 public IsoGameCharacter.Location getLastHeardSound() {
 return this->LastHeardSound;
 }

 void setLastHeardSound(int x, int y, int z) {
 this->LastHeardSound.x = x;
 this->LastHeardSound.y = y;
 this->LastHeardSound.z = z;
 }

 /**
 * @return the lrx
 */
 float getLrx() {
 return this->lrx;
 }

 /**
 * 
 * @param _lrx the lrx to set
 */
 void setLrx(float _lrx) {
 this->lrx = _lrx;
 }

 /**
 * @return the lry
 */
 float getLry() {
 return this->lry;
 }

 /**
 * 
 * @param _lry the lry to set
 */
 void setLry(float _lry) {
 this->lry = _lry;
 }

 /**
 * @return the bClimbing
 */
 bool isClimbing() {
 return this->bClimbing;
 }

 /**
 * 
 * @param _bClimbing the bClimbing to set
 */
 void setbClimbing(bool _bClimbing) {
 this->bClimbing = _bClimbing;
 }

 /**
 * @return the lastCollidedW
 */
 bool isLastCollidedW() {
 return this->lastCollidedW;
 }

 /**
 * 
 * @param _lastCollidedW the lastCollidedW to set
 */
 void setLastCollidedW(bool _lastCollidedW) {
 this->lastCollidedW = _lastCollidedW;
 }

 /**
 * @return the lastCollidedN
 */
 bool isLastCollidedN() {
 return this->lastCollidedN;
 }

 /**
 * 
 * @param _lastCollidedN the lastCollidedN to set
 */
 void setLastCollidedN(bool _lastCollidedN) {
 this->lastCollidedN = _lastCollidedN;
 }

 /**
 * @return the fallTime
 */
 float getFallTime() {
 return this->fallTime;
 }

 /**
 * 
 * @param _fallTime the fallTime to set
 */
 void setFallTime(float _fallTime) {
 this->fallTime = _fallTime;
 }

 /**
 * @return the lastFallSpeed
 */
 float getLastFallSpeed() {
 return this->lastFallSpeed;
 }

 /**
 * 
 * @param _lastFallSpeed the lastFallSpeed to set
 */
 void setLastFallSpeed(float _lastFallSpeed) {
 this->lastFallSpeed = _lastFallSpeed;
 }

 /**
 * @return the bFalling
 */
 bool isbFalling() {
 return this->bFalling;
 }

 /**
 * 
 * @param _bFalling the bFalling to set
 */
 void setbFalling(bool _bFalling) {
 this->bFalling = _bFalling;
 }

 IsoBuilding getCurrentBuilding() {
 if (this->current.empty()) {
 return nullptr;
 } else {
 return this->current.getRoom() == nullptr ? nullptr : this->current.getRoom().building;
 }
 }

 BuildingDef getCurrentBuildingDef() {
 if (this->current.empty()) {
 return nullptr;
 } else if (this->current.getRoom() == nullptr) {
 return nullptr;
 } else {
 return this->current.getRoom().building != nullptr ? this->current.getRoom().building.def : nullptr;
 }
 }

 RoomDef getCurrentRoomDef() {
 if (this->current.empty()) {
 return nullptr;
 } else {
 return this->current.getRoom() != nullptr ? this->current.getRoom().def : nullptr;
 }
 }

 float getTorchStrength() {
 return 0.0F;
 }

 void OnAnimEvent(AnimLayer sender, AnimEvent event) {
 if (event.m_EventName != nullptr) {
 if (event.m_EventName.equalsIgnoreCase("SetVariable") && event.m_SetVariable1 != nullptr) {
 this->setVariable(event.m_SetVariable1, event.m_SetVariable2);
 }

 if (event.m_EventName.equalsIgnoreCase("ClearVariable")) {
 this->clearVariable(event.m_ParameterValue);
 }

 if (event.m_EventName.equalsIgnoreCase("PlaySound")) {
 this->getEmitter().playSoundImpl(event.m_ParameterValue, this);
 }

 if (event.m_EventName.equalsIgnoreCase("Footstep")) {
 this->DoFootstepSound(event.m_ParameterValue);
 }

 if (event.m_EventName.equalsIgnoreCase("DamageWhileInTrees")) {
 this->damageWhileInTrees();
 }

 int int0 = sender.getDepth();
 this->actionContext.reportEvent(int0, event.m_EventName);
 this->stateMachine.stateAnimEvent(int0, event);
 }
 }

 void damageWhileInTrees() {
 if (!this->isZombie() && !"Tutorial" == Core.GameMode) {
 int int0 = 50;
 int int1 = Rand.Next(0, BodyPartType.ToIndex(BodyPartType.MAX);
 if (this->isRunning()) {
 int0 = 30;
 }

 if (this->Traits.Outdoorsman.isSet()) {
 int0 += 50;
 }

 int0 += (int)this->getBodyPartClothingDefense(int1, false, false);
 if (Rand.NextBool(int0) {
 this->addHole(BloodBodyPartType.FromIndex(int1);
 uint8_t byte0 = 6;
 if (this->Traits.ThickSkinned.isSet()) {
 byte0 += 7;
 }

 if (this->Traits.ThinSkinned.isSet()) {
 byte0 -= 3;
 }

 if (Rand.NextBool(byte0) && (int)this->getBodyPartClothingDefense(int1, false, false) < 100) {
 BodyPart bodyPart = this->getBodyDamage().getBodyParts().get(int1);
 if (Rand.NextBool(byte0 + 10) {
 bodyPart.setCut(true, true);
 } else {
 bodyPart.setScratched(true, true);
 }
 }
 }
 }
 }

 float getHammerSoundMod() {
 int int0 = this->getPerkLevel(PerkFactory.Perks.Woodwork);
 if (int0 == 2) {
 return 0.8F;
 } else if (int0 == 3) {
 return 0.6F;
 } else if (int0 == 4) {
 return 0.4F;
 } else {
 return int0 >= 5 ? 0.4F : 1.0F;
 }
 }

 float getWeldingSoundMod() {
 int int0 = this->getPerkLevel(PerkFactory.Perks.MetalWelding);
 if (int0 == 2) {
 return 0.8F;
 } else if (int0 == 3) {
 return 0.6F;
 } else if (int0 == 4) {
 return 0.4F;
 } else {
 return int0 >= 5 ? 0.4F : 1.0F;
 }
 }

 float getBarricadeTimeMod() {
 int int0 = this->getPerkLevel(PerkFactory.Perks.Woodwork);
 if (int0 == 1) {
 return 0.8F;
 } else if (int0 == 2) {
 return 0.7F;
 } else if (int0 == 3) {
 return 0.62F;
 } else if (int0 == 4) {
 return 0.56F;
 } else if (int0 == 5) {
 return 0.5F;
 } else if (int0 == 6) {
 return 0.42F;
 } else if (int0 == 7) {
 return 0.36F;
 } else if (int0 == 8) {
 return 0.3F;
 } else if (int0 == 9) {
 return 0.26F;
 } else {
 return int0 = = 10 ? 0.2F : 0.7F;
 }
 }

 float getMetalBarricadeStrengthMod() {
 switch (this->getPerkLevel(PerkFactory.Perks.MetalWelding) {
 case 2:
 return 1.1F;
 case 3:
 return 1.14F;
 case 4:
 return 1.18F;
 case 5:
 return 1.22F;
 case 6:
 return 1.16F;
 case 7:
 return 1.3F;
 case 8:
 return 1.34F;
 case 9:
 return 1.4F;
 case 10:
 return 1.5F;
 default:
 int int0 = this->getPerkLevel(PerkFactory.Perks.Woodwork);
 if (int0 == 2) {
 return 1.1F;
 } else if (int0 == 3) {
 return 1.14F;
 } else if (int0 == 4) {
 return 1.18F;
 } else if (int0 == 5) {
 return 1.22F;
 } else if (int0 == 6) {
 return 1.26F;
 } else if (int0 == 7) {
 return 1.3F;
 } else if (int0 == 8) {
 return 1.34F;
 } else if (int0 == 9) {
 return 1.4F;
 } else {
 return int0 = = 10 ? 1.5F : 1.0F;
 }
 }
 }

 float getBarricadeStrengthMod() {
 int int0 = this->getPerkLevel(PerkFactory.Perks.Woodwork);
 if (int0 == 2) {
 return 1.1F;
 } else if (int0 == 3) {
 return 1.14F;
 } else if (int0 == 4) {
 return 1.18F;
 } else if (int0 == 5) {
 return 1.22F;
 } else if (int0 == 6) {
 return 1.26F;
 } else if (int0 == 7) {
 return 1.3F;
 } else if (int0 == 8) {
 return 1.34F;
 } else if (int0 == 9) {
 return 1.4F;
 } else {
 return int0 = = 10 ? 1.5F : 1.0F;
 }
 }

 float getSneakSpotMod() {
 int int0 = this->getPerkLevel(PerkFactory.Perks.Sneak);
 float float0 = 0.95F;
 if (int0 == 1) {
 float0 = 0.9F;
 }

 if (int0 == 2) {
 float0 = 0.8F;
 }

 if (int0 == 3) {
 float0 = 0.75F;
 }

 if (int0 == 4) {
 float0 = 0.7F;
 }

 if (int0 == 5) {
 float0 = 0.65F;
 }

 if (int0 == 6) {
 float0 = 0.6F;
 }

 if (int0 == 7) {
 float0 = 0.55F;
 }

 if (int0 == 8) {
 float0 = 0.5F;
 }

 if (int0 == 9) {
 float0 = 0.45F;
 }

 if (int0 == 10) {
 float0 = 0.4F;
 }

 return float0 * 1.2F;
 }

 float getNimbleMod() {
 int int0 = this->getPerkLevel(PerkFactory.Perks.Nimble);
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
 return 1.38F;
 } else if (int0 == 9) {
 return 1.42F;
 } else {
 return int0 = = 10 ? 1.5F : 1.0F;
 }
 }

 float getFatigueMod() {
 int int0 = this->getPerkLevel(PerkFactory.Perks.Fitness);
 if (int0 == 1) {
 return 0.95F;
 } else if (int0 == 2) {
 return 0.92F;
 } else if (int0 == 3) {
 return 0.89F;
 } else if (int0 == 4) {
 return 0.87F;
 } else if (int0 == 5) {
 return 0.85F;
 } else if (int0 == 6) {
 return 0.83F;
 } else if (int0 == 7) {
 return 0.81F;
 } else if (int0 == 8) {
 return 0.79F;
 } else if (int0 == 9) {
 return 0.77F;
 } else {
 return int0 = = 10 ? 0.75F : 1.0F;
 }
 }

 float getLightfootMod() {
 int int0 = this->getPerkLevel(PerkFactory.Perks.Lightfoot);
 if (int0 == 1) {
 return 0.9F;
 } else if (int0 == 2) {
 return 0.79F;
 } else if (int0 == 3) {
 return 0.71F;
 } else if (int0 == 4) {
 return 0.65F;
 } else if (int0 == 5) {
 return 0.59F;
 } else if (int0 == 6) {
 return 0.52F;
 } else if (int0 == 7) {
 return 0.45F;
 } else if (int0 == 8) {
 return 0.37F;
 } else if (int0 == 9) {
 return 0.3F;
 } else {
 return int0 = = 10 ? 0.2F : 0.99F;
 }
 }

 float getPacingMod() {
 int int0 = this->getPerkLevel(PerkFactory.Perks.Fitness);
 if (int0 == 1) {
 return 0.8F;
 } else if (int0 == 2) {
 return 0.75F;
 } else if (int0 == 3) {
 return 0.7F;
 } else if (int0 == 4) {
 return 0.65F;
 } else if (int0 == 5) {
 return 0.6F;
 } else if (int0 == 6) {
 return 0.57F;
 } else if (int0 == 7) {
 return 0.53F;
 } else if (int0 == 8) {
 return 0.49F;
 } else if (int0 == 9) {
 return 0.46F;
 } else {
 return int0 = = 10 ? 0.43F : 0.9F;
 }
 }

 float getHyperthermiaMod() {
 float float0 = 1.0F;
 if (this->getMoodles().getMoodleLevel(MoodleType.Hyperthermia) > 1) {
 float0 = 1.0F;
 if (this->getMoodles().getMoodleLevel(MoodleType.Hyperthermia) == 4) {
 float0 = 2.0F;
 }
 }

 return float0;
 }

 float getHittingMod() {
 int int0 = this->getPerkLevel(PerkFactory.Perks.Strength);
 if (int0 == 1) {
 return 0.8F;
 } else if (int0 == 2) {
 return 0.85F;
 } else if (int0 == 3) {
 return 0.9F;
 } else if (int0 == 4) {
 return 0.95F;
 } else if (int0 == 5) {
 return 1.0F;
 } else if (int0 == 6) {
 return 1.05F;
 } else if (int0 == 7) {
 return 1.1F;
 } else if (int0 == 8) {
 return 1.15F;
 } else if (int0 == 9) {
 return 1.2F;
 } else {
 return int0 = = 10 ? 1.25F : 0.75F;
 }
 }

 float getShovingMod() {
 int int0 = this->getPerkLevel(PerkFactory.Perks.Strength);
 if (int0 == 1) {
 return 0.8F;
 } else if (int0 == 2) {
 return 0.85F;
 } else if (int0 == 3) {
 return 0.9F;
 } else if (int0 == 4) {
 return 0.95F;
 } else if (int0 == 5) {
 return 1.0F;
 } else if (int0 == 6) {
 return 1.05F;
 } else if (int0 == 7) {
 return 1.1F;
 } else if (int0 == 8) {
 return 1.15F;
 } else if (int0 == 9) {
 return 1.2F;
 } else {
 return int0 = = 10 ? 1.25F : 0.75F;
 }
 }

 float getRecoveryMod() {
 int int0 = this->getPerkLevel(PerkFactory.Perks.Fitness);
 float float0 = 0.0F;
 if (int0 == 0) {
 float0 = 0.7F;
 }

 if (int0 == 1) {
 float0 = 0.8F;
 }

 if (int0 == 2) {
 float0 = 0.9F;
 }

 if (int0 == 3) {
 float0 = 1.0F;
 }

 if (int0 == 4) {
 float0 = 1.1F;
 }

 if (int0 == 5) {
 float0 = 1.2F;
 }

 if (int0 == 6) {
 float0 = 1.3F;
 }

 if (int0 == 7) {
 float0 = 1.4F;
 }

 if (int0 == 8) {
 float0 = 1.5F;
 }

 if (int0 == 9) {
 float0 = 1.55F;
 }

 if (int0 == 10) {
 float0 = 1.6F;
 }

 if (this->Traits.Obese.isSet()) {
 float0 = (float)(float0 * 0.4);
 }

 if (this->Traits.Overweight.isSet()) {
 float0 = (float)(float0 * 0.7);
 }

 if (this->Traits.VeryUnderweight.isSet()) {
 float0 = (float)(float0 * 0.7);
 }

 if (this->Traits.Emaciated.isSet()) {
 float0 = (float)(float0 * 0.3);
 }

 if (this instanceof IsoPlayer) {
 if (((IsoPlayer)this).getNutrition().getLipids() < -1500.0F) {
 float0 = (float)(float0 * 0.2);
 } else if (((IsoPlayer)this).getNutrition().getLipids() < -1000.0F) {
 float0 = (float)(float0 * 0.5);
 }

 if (((IsoPlayer)this).getNutrition().getProteins() < -1500.0F) {
 float0 = (float)(float0 * 0.2);
 } else if (((IsoPlayer)this).getNutrition().getProteins() < -1000.0F) {
 float0 = (float)(float0 * 0.5);
 }
 }

 return float0;
 }

 float getWeightMod() {
 int int0 = this->getPerkLevel(PerkFactory.Perks.Strength);
 if (int0 == 1) {
 return 0.9F;
 } else if (int0 == 2) {
 return 1.07F;
 } else if (int0 == 3) {
 return 1.24F;
 } else if (int0 == 4) {
 return 1.41F;
 } else if (int0 == 5) {
 return 1.58F;
 } else if (int0 == 6) {
 return 1.75F;
 } else if (int0 == 7) {
 return 1.92F;
 } else if (int0 == 8) {
 return 2.09F;
 } else if (int0 == 9) {
 return 2.26F;
 } else {
 return int0 = = 10 ? 2.5F : 0.8F;
 }
 }

 int getHitChancesMod() {
 int int0 = this->getPerkLevel(PerkFactory.Perks.Aiming);
 if (int0 == 1) {
 return 1;
 } else if (int0 == 2) {
 return 1;
 } else if (int0 == 3) {
 return 2;
 } else if (int0 == 4) {
 return 2;
 } else if (int0 == 5) {
 return 3;
 } else if (int0 == 6) {
 return 3;
 } else if (int0 == 7) {
 return 4;
 } else if (int0 == 8) {
 return 4;
 } else if (int0 == 9) {
 return 5;
 } else {
 return int0 = = 10 ? 5 : 1;
 }
 }

 float getSprintMod() {
 int int0 = this->getPerkLevel(PerkFactory.Perks.Sprinting);
 if (int0 == 1) {
 return 1.1F;
 } else if (int0 == 2) {
 return 1.15F;
 } else if (int0 == 3) {
 return 1.2F;
 } else if (int0 == 4) {
 return 1.25F;
 } else if (int0 == 5) {
 return 1.3F;
 } else if (int0 == 6) {
 return 1.35F;
 } else if (int0 == 7) {
 return 1.4F;
 } else if (int0 == 8) {
 return 1.45F;
 } else if (int0 == 9) {
 return 1.5F;
 } else {
 return int0 = = 10 ? 1.6F : 0.9F;
 }
 }

 /**
 * Return the current lvl of a perk (skill)
 */
 int getPerkLevel(PerkFactory.Perk perks) {
 IsoGameCharacter.PerkInfo perkInfo = this->getPerkInfo(perks);
 return perkInfo != nullptr ? perkInfo.level : 0;
 }

 void setPerkLevelDebug(PerkFactory.Perk perks, int level) {
 IsoGameCharacter.PerkInfo perkInfo = this->getPerkInfo(perks);
 if (perkInfo != nullptr) {
 perkInfo.level = level;
 }

 if (GameClient.bClient && this instanceof IsoPlayer) {
 GameClient.sendPerks((IsoPlayer)this);
 }
 }

 void LoseLevel(PerkFactory.Perk perk) {
 IsoGameCharacter.PerkInfo perkInfo = this->getPerkInfo(perk);
 if (perkInfo != nullptr) {
 perkInfo.level--;
 if (perkInfo.level < 0) {
 perkInfo.level = 0;
 }

 LuaEventManager.triggerEvent("LevelPerk", this, perk, perkInfo.level, false);
 if (perk == PerkFactory.Perks.Sneak && GameClient.bClient && this instanceof IsoPlayer) {
 GameClient.sendPerks((IsoPlayer)this);
 }
 } else {
 LuaEventManager.triggerEvent("LevelPerk", this, perk, 0, false);
 }
 }

 /**
 * Level up a perk (max lvl 5)
 * 
 * @param perk the perk to lvl up
 * @param removePick did we remove a skill pts ? (for example passiv skill automatically lvl up, without consuming skill pts)
 */
 void LevelPerk(PerkFactory.Perk perk, bool removePick) {
 Objects.requireNonNull(perk, "perk is nullptr");
 if (perk == PerkFactory.Perks.MAX) {
 throw IllegalArgumentException("perk == Perks.MAX");
 } else {
 IsoPlayer player = Type.tryCastTo(this, IsoPlayer.class);
 IsoGameCharacter.PerkInfo perkInfo = this->getPerkInfo(perk);
 if (perkInfo != nullptr) {
 perkInfo.level++;
 if (player != nullptr && !"Tutorial" == Core.GameMode) && this->getHoursSurvived() > 0.016666666666666666) {
 HaloTextHelper.addTextWithArrow(player, "+1 " + perk.getName(), true, HaloTextHelper.getColorGreen());
 }

 if (perkInfo.level > 10) {
 perkInfo.level = 10;
 }

 if (GameClient.bClient && player != nullptr) {
 GameClient.instance.sendSyncXp(player);
 }

 LuaEventManager.triggerEventGarbage("LevelPerk", this, perk, perkInfo.level, true);
 if (GameClient.bClient && player != nullptr) {
 GameClient.sendPerks(player);
 }
 } else {
 perkInfo = new IsoGameCharacter.PerkInfo();
 perkInfo.perk = perk;
 perkInfo.level = 1;
 this->PerkList.add(perkInfo);
 if (player != nullptr && !"Tutorial" == Core.GameMode) && this->getHoursSurvived() > 0.016666666666666666) {
 HaloTextHelper.addTextWithArrow(player, "+1 " + perk.getName(), true, HaloTextHelper.getColorGreen());
 }

 if (GameClient.bClient && this instanceof IsoPlayer) {
 GameClient.instance.sendSyncXp(player);
 }

 LuaEventManager.triggerEvent("LevelPerk", this, perk, perkInfo.level, true);
 }
 }
 }

 /**
 * Level up a perk (max lvl 5)
 * 
 * @param perk the perk to lvl up (a skill points is removed)
 */
 void LevelPerk(PerkFactory.Perk perk) {
 this->LevelPerk(perk, true);
 }

 void level0(PerkFactory.Perk perk) {
 IsoGameCharacter.PerkInfo perkInfo = this->getPerkInfo(perk);
 if (perkInfo != nullptr) {
 perkInfo.level = 0;
 }
 }

 public IsoGameCharacter.Location getLastKnownLocationOf(String character) {
 return this->LastKnownLocation.containsKey(character) ? this->LastKnownLocation.get(character) : nullptr;
 }

 /**
 * Used when you read a book, magazine or newspaper
 * 
 * @param literature the book to read
 */
 void ReadLiterature(Literature literature) {
 this->stats.stress = this->stats.stress + literature.getStressChange();
 this->getBodyDamage().JustReadSomething(literature);
 if (literature.getTeachedRecipes() != nullptr) {
 for (int int0 = 0; int0 < literature.getTeachedRecipes().size(); int0++) {
 if (!this->getKnownRecipes().contains(literature.getTeachedRecipes().get(int0) {
 this->getKnownRecipes().add(literature.getTeachedRecipes().get(int0);
 }
 }
 }

 literature.Use();
 }

 void OnDeath() {
 LuaEventManager.triggerEvent("OnCharacterDeath", this);
 }

 void splatBloodFloorBig() {
 if (this->getCurrentSquare() != nullptr && this->getCurrentSquare().getChunk() != nullptr) {
 this->getCurrentSquare().getChunk().addBloodSplat(this->x, this->y, this->z, Rand.Next(20);
 }
 }

 void splatBloodFloor() {
 if (this->getCurrentSquare() != nullptr) {
 if (this->getCurrentSquare().getChunk() != nullptr) {
 if (this->isDead() && Rand.Next(10) == 0) {
 this->getCurrentSquare().getChunk().addBloodSplat(this->x, this->y, this->z, Rand.Next(20);
 }

 if (Rand.Next(14) == 0) {
 this->getCurrentSquare().getChunk().addBloodSplat(this->x, this->y, this->z, Rand.Next(8);
 }

 if (Rand.Next(50) == 0) {
 this->getCurrentSquare().getChunk().addBloodSplat(this->x, this->y, this->z, Rand.Next(20);
 }
 }
 }
 }

 int getThreatLevel() {
 int int0 = this->LocalRelevantEnemyList.size();
 int0 += this->VeryCloseEnemyList.size() * 10;
 if (int0 > 20) {
 return 3;
 } else if (int0 > 10) {
 return 2;
 } else {
 return int0 > 0 ? 1 : 0;
 }
 }

 bool isDead() {
 return this->Health <= 0.0F || this->BodyDamage != nullptr && this->BodyDamage.getHealth() <= 0.0F;
 }

 bool isAlive() {
 return !this->isDead();
 }

 void Seen(Stack<IsoMovingObject> SeenList) {
 synchronized (this->LocalList) {
 this->LocalList.clear();
 this->LocalList.addAll(SeenList);
 }
 }

 bool CanSee(IsoMovingObject obj) {
 return LosUtil.lineClear(this->getCell(), (int)this->getX(), (int)this->getY(), (int)this->getZ(), (int)obj.getX(), (int)obj.getY(), (int)obj.getZ(), false)
 != LosUtil.TestResults.Blocked;
 }

 IsoGridSquare getLowDangerInVicinity(int attempts, int range) {
 float float0 = -1000000.0F;
 IsoGridSquare square0 = nullptr;

 for (int int0 = 0; int0 < attempts; int0++) {
 float float1 = 0.0F;
 int int1 = Rand.Next(-range, range);
 int int2 = Rand.Next(-range, range);
 IsoGridSquare square1 = this->getCell().getGridSquare((int)this->getX() + int1, (int)this->getY() + int2, (int)this->getZ());
 if (square1 != nullptr && square1.isFree(true) {
 float float2 = square1.getMovingObjects().size();
 if (square1.getE() != nullptr) {
 float2 += square1.getE().getMovingObjects().size();
 }

 if (square1.getS() != nullptr) {
 float2 += square1.getS().getMovingObjects().size();
 }

 if (square1.getW() != nullptr) {
 float2 += square1.getW().getMovingObjects().size();
 }

 if (square1.getN() != nullptr) {
 float2 += square1.getN().getMovingObjects().size();
 }

 float1 -= float2 * 1000.0F;
 if (float1 > float0) {
 float0 = float1;
 square0 = square1;
 }
 }
 }

 return square0;
 }

 void Anger(int amount) {
 float float0 = 10.0F;
 if (Rand.Next(100) < float0) {
 amount *= 2;
 }

 amount = (int)(amount * (this->stats.getStress() + 1.0F);
 amount = (int)(amount * (this->BodyDamage.getUnhappynessLevel() / 100.0F + 1.0F);
 this->stats.Anger += amount / 100.0F;
 }

 bool hasEquipped(const std::string& itemType) {
 if (itemType.contains(".")) {
 itemType = itemType.split("\\.")[1];
 }

 return this->leftHandItem != nullptr && this->leftHandItem.getType() == itemType)
 ? true
 : this->rightHandItem != nullptr && this->rightHandItem.getType() == itemType);
 }

 bool hasEquippedTag(const std::string& tag) {
 return this->leftHandItem != nullptr && this->leftHandItem.hasTag(tag) ? true : this->rightHandItem != nullptr && this->rightHandItem.hasTag(tag);
 }

 /**
 * 
 * @param directions the dir to set
 */
 void setDir(IsoDirections directions) {
 this->dir = directions;
 this->getVectorFromDirection(this->m_forwardDirection);
 }

 void Callout(bool doAnim) {
 if (this->isCanShout()) {
 this->Callout();
 if (doAnim) {
 this->playEmote("shout");
 }
 }
 }

 void Callout() {
 std::string string = "";
 uint8_t byte0 = 30;
 if (Core.getInstance().getGameMode() == "Tutorial")) {
 string = Translator.getText("IGUI_PlayerText_CalloutTutorial");
 } else if (this->isSneaking()) {
 byte0 = 6;
 switch (Rand.Next(3) {
 case 0:
 string = Translator.getText("IGUI_PlayerText_Callout1Sneak");
 break;
 case 1:
 string = Translator.getText("IGUI_PlayerText_Callout2Sneak");
 break;
 case 2:
 string = Translator.getText("IGUI_PlayerText_Callout3Sneak");
 }
 } else {
 switch (Rand.Next(3) {
 case 0:
 string = Translator.getText("IGUI_PlayerText_Callout1New");
 break;
 case 1:
 string = Translator.getText("IGUI_PlayerText_Callout2New");
 break;
 case 2:
 string = Translator.getText("IGUI_PlayerText_Callout3New");
 }
 }

 WorldSoundManager.instance.addSound(this, (int)this->x, (int)this->y, (int)this->z, byte0, byte0);
 this->SayShout(string);
 this->callOut = true;
 }

 void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 super.load(input, WorldVersion, IS_DEBUG_SAVE);
 this->getVectorFromDirection(this->m_forwardDirection);
 if (input.get() == 1) {
 this->descriptor = new SurvivorDesc(true);
 this->descriptor.load(input, WorldVersion, this);
 this->bFemale = this->descriptor.isFemale();
 }

 this->getVisual().load(input, WorldVersion);
 std::vector arrayList0 = this->inventory.load(input, WorldVersion);
 this->savedInventoryItems.clear();

 for (int int0 = 0; int0 < arrayList0.size(); int0++) {
 this->savedInventoryItems.add((InventoryItem)arrayList0.get(int0);
 }

 this->Asleep = input.get() == 1;
 this->ForceWakeUpTime = input.getFloat();
 if (!this->isZombie()) {
 this->stats.load(input, WorldVersion);
 this->BodyDamage.load(input, WorldVersion);
 this->xp.load(input, WorldVersion);
 std::vector arrayList1 = this->inventory.IncludingObsoleteItems;
 int int1 = input.getInt();
 if (int1 >= 0 && int1 < arrayList1.size()) {
 this->leftHandItem = (InventoryItem)arrayList1.get(int1);
 }

 int1 = input.getInt();
 if (int1 >= 0 && int1 < arrayList1.size()) {
 this->rightHandItem = (InventoryItem)arrayList1.get(int1);
 }

 this->setEquipParent(nullptr, this->leftHandItem);
 this->setEquipParent(nullptr, this->rightHandItem);
 }

 bool boolean0 = input.get() == 1;
 if (boolean0) {
 this->SetOnFire();
 }

 this->DepressEffect = input.getFloat();
 this->DepressFirstTakeTime = input.getFloat();
 this->BetaEffect = input.getFloat();
 this->BetaDelta = input.getFloat();
 this->PainEffect = input.getFloat();
 this->PainDelta = input.getFloat();
 this->SleepingTabletEffect = input.getFloat();
 this->SleepingTabletDelta = input.getFloat();
 int int2 = input.getInt();

 for (int int3 = 0; int3 < int2; int3++) {
 IsoGameCharacter.ReadBook readBook = new IsoGameCharacter.ReadBook();
 readBook.fullType = GameWindow.ReadString(input);
 readBook.alreadyReadPages = input.getInt();
 this->ReadBooks.add(readBook);
 }

 this->reduceInfectionPower = input.getFloat();
 int int4 = input.getInt();

 for (int int5 = 0; int5 < int4; int5++) {
 this->knownRecipes.add(GameWindow.ReadString(input);
 }

 this->lastHourSleeped = input.getInt();
 this->timeSinceLastSmoke = input.getFloat();
 this->beardGrowTiming = input.getFloat();
 this->hairGrowTiming = input.getFloat();
 this->setUnlimitedCarry(input.get() == 1);
 this->setBuildCheat(input.get() == 1);
 this->setHealthCheat(input.get() == 1);
 this->setMechanicsCheat(input.get() == 1);
 if (WorldVersion >= 176) {
 this->setMovablesCheat(input.get() == 1);
 this->setFarmingCheat(input.get() == 1);
 this->setTimedActionInstantCheat(input.get() == 1);
 this->setUnlimitedEndurance(input.get() == 1);
 }

 if (WorldVersion >= 161) {
 this->setSneaking(input.get() == 1);
 this->setDeathDragDown(input.get() == 1);
 }
 }

 void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 super.save(output, IS_DEBUG_SAVE);
 if (this->descriptor.empty()) {
 output.put((byte)0);
 } else {
 output.put((byte)1);
 this->descriptor.save(output);
 }

 this->getVisual().save(output);
 std::vector arrayList = this->inventory.save(output, this);
 this->savedInventoryItems.clear();

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 this->savedInventoryItems.add((InventoryItem)arrayList.get(int0);
 }

 output.put((byte)(this->Asleep ? 1 : 0);
 output.putFloat(this->ForceWakeUpTime);
 if (!this->isZombie()) {
 this->stats.save(output);
 this->BodyDamage.save(output);
 this->xp.save(output);
 if (this->leftHandItem != nullptr) {
 output.putInt(this->inventory.getItems().indexOf(this->leftHandItem);
 } else {
 output.putInt(-1);
 }

 if (this->rightHandItem != nullptr) {
 output.putInt(this->inventory.getItems().indexOf(this->rightHandItem);
 } else {
 output.putInt(-1);
 }
 }

 output.put((byte)(this->OnFire ? 1 : 0);
 output.putFloat(this->DepressEffect);
 output.putFloat(this->DepressFirstTakeTime);
 output.putFloat(this->BetaEffect);
 output.putFloat(this->BetaDelta);
 output.putFloat(this->PainEffect);
 output.putFloat(this->PainDelta);
 output.putFloat(this->SleepingTabletEffect);
 output.putFloat(this->SleepingTabletDelta);
 output.putInt(this->ReadBooks.size());

 for (int int1 = 0; int1 < this->ReadBooks.size(); int1++) {
 IsoGameCharacter.ReadBook readBook = this->ReadBooks.get(int1);
 GameWindow.WriteString(output, readBook.fullType);
 output.putInt(readBook.alreadyReadPages);
 }

 output.putFloat(this->reduceInfectionPower);
 output.putInt(this->knownRecipes.size());

 for (int int2 = 0; int2 < this->knownRecipes.size(); int2++) {
 std::string string = this->knownRecipes.get(int2);
 GameWindow.WriteString(output, string);
 }

 output.putInt(this->lastHourSleeped);
 output.putFloat(this->timeSinceLastSmoke);
 output.putFloat(this->beardGrowTiming);
 output.putFloat(this->hairGrowTiming);
 output.put((byte)(this->isUnlimitedCarry() ? 1 : 0);
 output.put((byte)(this->isBuildCheat() ? 1 : 0);
 output.put((byte)(this->isHealthCheat() ? 1 : 0);
 output.put((byte)(this->isMechanicsCheat() ? 1 : 0);
 output.put((byte)(this->isMovablesCheat() ? 1 : 0);
 output.put((byte)(this->isFarmingCheat() ? 1 : 0);
 output.put((byte)(this->isTimedActionInstantCheat() ? 1 : 0);
 output.put((byte)(this->isUnlimitedEndurance() ? 1 : 0);
 output.put((byte)(this->isSneaking() ? 1 : 0);
 output.put((byte)(this->isDeathDragDown() ? 1 : 0);
 }

 ChatElement getChatElement() {
 return this->chatElement;
 }

 void StartAction(BaseAction act) {
 this->CharacterActions.clear();
 this->CharacterActions.push(act);
 if (act.valid()) {
 act.waitToStart();
 }
 }

 void QueueAction(BaseAction act) {
 }

 void StopAllActionQueue() {
 if (!this->CharacterActions.empty()) {
 BaseAction baseAction = this->CharacterActions.get(0);
 if (baseAction.bStarted) {
 baseAction.stop();
 }

 this->CharacterActions.clear();
 if (this == IsoPlayer.players[0] || this == IsoPlayer.players[1] || this == IsoPlayer.players[2] || this == IsoPlayer.players[3]) {
 UIManager.getProgressBar(((IsoPlayer)this).getPlayerNum()).setValue(0.0F);
 }
 }
 }

 void StopAllActionQueueRunning() {
 if (!this->CharacterActions.empty()) {
 BaseAction baseAction = this->CharacterActions.get(0);
 if (baseAction.StopOnRun) {
 if (baseAction.bStarted) {
 baseAction.stop();
 }

 this->CharacterActions.clear();
 if (this == IsoPlayer.players[0] || this == IsoPlayer.players[1] || this == IsoPlayer.players[2] || this == IsoPlayer.players[3]) {
 UIManager.getProgressBar(((IsoPlayer)this).getPlayerNum()).setValue(0.0F);
 }
 }
 }
 }

 void StopAllActionQueueAiming() {
 if (this->CharacterActions.size() != 0) {
 BaseAction baseAction = this->CharacterActions.get(0);
 if (baseAction.StopOnAim) {
 if (baseAction.bStarted) {
 baseAction.stop();
 }

 this->CharacterActions.clear();
 if (this == IsoPlayer.players[0] || this == IsoPlayer.players[1] || this == IsoPlayer.players[2] || this == IsoPlayer.players[3]) {
 UIManager.getProgressBar(((IsoPlayer)this).getPlayerNum()).setValue(0.0F);
 }
 }
 }
 }

 void StopAllActionQueueWalking() {
 if (this->CharacterActions.size() != 0) {
 BaseAction baseAction = this->CharacterActions.get(0);
 if (baseAction.StopOnWalk) {
 if (baseAction.bStarted) {
 baseAction.stop();
 }

 this->CharacterActions.clear();
 if (this == IsoPlayer.players[0] || this == IsoPlayer.players[1] || this == IsoPlayer.players[2] || this == IsoPlayer.players[3]) {
 UIManager.getProgressBar(((IsoPlayer)this).getPlayerNum()).setValue(0.0F);
 }
 }
 }
 }

 std::string GetAnimSetName() {
 return "Base";
 }

 void SleepingTablet(float _SleepingTabletDelta) {
 this->SleepingTabletEffect = 6600.0F;
 this->SleepingTabletDelta += _SleepingTabletDelta;
 }

 void BetaBlockers(float delta) {
 this->BetaEffect = 6600.0F;
 this->BetaDelta += delta;
 }

 void BetaAntiDepress(float delta) {
 if (this->DepressEffect == 0.0F) {
 this->DepressFirstTakeTime = 10000.0F;
 }

 this->DepressEffect = 6600.0F;
 this->DepressDelta += delta;
 }

 void PainMeds(float delta) {
 this->PainEffect = 5400.0F;
 this->PainDelta += delta;
 }

 void initSpritePartsEmpty() {
 this->InitSpriteParts(this->descriptor);
 }

 void InitSpriteParts(SurvivorDesc desc) {
 this->sprite.AnimMap.clear();
 this->sprite.AnimStack.clear();
 this->sprite.CurrentAnim = nullptr;
 this->legsSprite = this->sprite;
 this->legsSprite.name = desc.torso;
 this->bUseParts = true;
 }

 bool HasTrait(const std::string& trait) {
 return this->Traits.contains(trait);
 }

 void ApplyInBedOffset(bool apply) {
 if (apply) {
 if (!this->bOnBed) {
 this->offsetX -= 20.0F;
 this->offsetY += 21.0F;
 this->bOnBed = true;
 }
 } else if (this->bOnBed) {
 this->offsetX += 20.0F;
 this->offsetY -= 21.0F;
 this->bOnBed = false;
 }
 }

 void Dressup(SurvivorDesc desc) {
 if (!this->isZombie()) {
 if (this->wornItems != nullptr) {
 ItemVisuals itemVisuals = new ItemVisuals();
 desc.getItemVisuals(itemVisuals);
 this->wornItems.setFromItemVisuals(itemVisuals);
 this->wornItems.addItemsToItemContainer(this->inventory);
 desc.wornItems.clear();
 this->onWornItemsChanged();
 }
 }
 }

 void PlayAnim(const std::string& string) {
 }

 void PlayAnimWithSpeed(const std::string& string, float framesSpeedPerFrame) {
 }

 void PlayAnimUnlooped(const std::string& string) {
 }

 void DirectionFromVector(Vector2 vecA) {
 this->dir = IsoDirections.fromAngle(vecA);
 }

 void DoFootstepSound(const std::string& type) {
 float float0 = 1.0F;
 switch (type) {
 case "sneak_walk":
 float0 = 0.2F;
 break;
 case "sneak_run":
 float0 = 0.5F;
 break;
 case "strafe":
 float0 = this->bSneaking ? 0.2F : 0.3F;
 break;
 case "walk":
 float0 = 0.5F;
 break;
 case "run":
 float0 = 1.3F;
 break;
 case "sprint":
 float0 = 1.8F;
 }

 this->DoFootstepSound(float0);
 }

 void DoFootstepSound(float volume) {
 IsoPlayer player = Type.tryCastTo(this, IsoPlayer.class);
 if (GameClient.bClient && player != nullptr && player.networkAI != nullptr) {
 player.networkAI.footstepSoundRadius = 0;
 }

 if (player.empty() || !player.isGhostMode() || DebugOptions.instance.Character.Debug.PlaySoundWhenInvisible.getValue()) {
 if (this->getCurrentSquare() != nullptr) {
 if (!(volume <= 0.0F) {
 volume *= 1.4F;
 if (this->Traits.Graceful.isSet()) {
 volume *= 0.6F;
 }

 if (this->Traits.Clumsy.isSet()) {
 volume *= 1.2F;
 }

 if (this->getWornItem("Shoes") == nullptr) {
 volume *= 0.5F;
 }

 volume *= this->getLightfootMod();
 volume *= 2.0F - this->getNimbleMod();
 if (this->bSneaking) {
 volume *= this->getSneakSpotMod();
 }

 if (volume > 0.0F) {
 this->emitter.playFootsteps("HumanFootstepsCombined", volume);
 if (player != nullptr && player.isGhostMode()) {
 return;
 }

 int int0 = (int)Math.ceil(volume * 10.0F);
 if (this->bSneaking) {
 int0 = Math.max(1, int0);
 }

 if (this->getCurrentSquare().getRoom() != nullptr) {
 int0 = (int)(int0 * 0.5F);
 }

 int int1 = 2;
 if (this->bSneaking) {
 int1 = Math.min(12, 4 + this->getPerkLevel(PerkFactory.Perks.Lightfoot);
 }

 if (GameClient.bClient && player != nullptr && player.networkAI != nullptr) {
 player.networkAI.footstepSoundRadius = (byte)int0;
 }

 if (Rand.Next(int1) == 0) {
 WorldSoundManager.instance
 .addSound(this, (int)this->getX(), (int)this->getY(), (int)this->getZ(), int0, int0, false, 0.0F, 1.0F, false, false, false);
 }
 }
 }
 }
 }
 }

 bool Eat(InventoryItem info, float percentage) {
 Food food = Type.tryCastTo(info, Food.class);
 if (food.empty()) {
 return false;
 } else {
 percentage = PZMath.clamp(percentage, 0.0F, 1.0F);
 if (food.getRequireInHandOrInventory() != nullptr) {
 InventoryItem item0 = nullptr;

 for (int int0 = 0; int0 < food.getRequireInHandOrInventory().size(); int0++) {
 std::string string0 = food.getRequireInHandOrInventory().get(int0);
 item0 = this->getInventory().FindAndReturn(string0);
 if (item0 != nullptr) {
 item0.Use();
 break;
 }
 }
 }

 float float0 = percentage;
 if (food.getBaseHunger() != 0.0F && food.getHungChange() != 0.0F) {
 float float1 = food.getBaseHunger() * percentage;
 float float2 = float1 / food.getHungChange();
 float2 = PZMath.clamp(float2, 0.0F, 1.0F);
 percentage = float2;
 }

 if (food.getHungChange() < 0.0F && food.getHungChange() * (1.0F - percentage) > -0.01F) {
 percentage = 1.0F;
 }

 if (food.getHungChange() == 0.0F && food.getThirstChange() < 0.0F && food.getThirstChange() * (1.0F - percentage) > -0.01F) {
 percentage = 1.0F;
 }

 this->stats.thirst = this->stats.thirst + food.getThirstChange() * percentage;
 if (this->stats.thirst < 0.0F) {
 this->stats.thirst = 0.0F;
 }

 this->stats.hunger = this->stats.hunger + food.getHungerChange() * percentage;
 this->stats.endurance = this->stats.endurance + food.getEnduranceChange() * percentage;
 this->stats.stress = this->stats.stress + food.getStressChange() * percentage;
 this->stats.fatigue = this->stats.fatigue + food.getFatigueChange() * percentage;
 IsoPlayer player = Type.tryCastTo(this, IsoPlayer.class);
 if (player != nullptr) {
 Nutrition nutrition = player.getNutrition();
 nutrition.setCalories(nutrition.getCalories() + food.getCalories() * percentage);
 nutrition.setCarbohydrates(nutrition.getCarbohydrates() + food.getCarbohydrates() * percentage);
 nutrition.setProteins(nutrition.getProteins() + food.getProteins() * percentage);
 nutrition.setLipids(nutrition.getLipids() + food.getLipids() * percentage);
 }

 this->BodyDamage.setPainReduction(this->BodyDamage.getPainReduction() + food.getPainReduction() * percentage);
 this->BodyDamage.setColdReduction(this->BodyDamage.getColdReduction() + food.getFluReduction() * percentage);
 if (this->BodyDamage.getFoodSicknessLevel() > 0.0F && food.getReduceFoodSickness() > 0.0F && this->effectiveEdibleBuffTimer <= 0.0F) {
 float float3 = this->BodyDamage.getFoodSicknessLevel();
 this->BodyDamage.setFoodSicknessLevel(this->BodyDamage.getFoodSicknessLevel() - food.getReduceFoodSickness() * percentage);
 if (this->BodyDamage.getFoodSicknessLevel() < 0.0F) {
 this->BodyDamage.setFoodSicknessLevel(0.0F);
 }

 float float4 = this->BodyDamage.getPoisonLevel();
 this->BodyDamage.setPoisonLevel(this->BodyDamage.getPoisonLevel() - food.getReduceFoodSickness() * percentage);
 if (this->BodyDamage.getPoisonLevel() < 0.0F) {
 this->BodyDamage.setPoisonLevel(0.0F);
 }

 if (this->Traits.IronGut.isSet()) {
 this->effectiveEdibleBuffTimer = Rand.Next(80.0F, 150.0F);
 } else if (this->Traits.WeakStomach.isSet()) {
 this->effectiveEdibleBuffTimer = Rand.Next(120.0F, 230.0F);
 } else {
 this->effectiveEdibleBuffTimer = Rand.Next(200.0F, 280.0F);
 }
 }

 this->BodyDamage.JustAteFood(food, percentage);
 if (GameClient.bClient && this instanceof IsoPlayer && ((IsoPlayer)this).isLocalPlayer()) {
 GameClient.instance.eatFood((IsoPlayer)this, food, percentage);
 }

 if (food.getOnEat() != nullptr) {
 void* object = LuaManager.getFunctionObject(food.getOnEat());
 if (object != nullptr) {
 LuaManager.caller.pcallvoid(LuaManager.thread, object, info, this, BoxedStaticValues.toDouble(percentage);
 }
 }

 if (percentage == 1.0F) {
 food.setHungChange(0.0F);
 food.UseItem();
 } else {
 float float5 = food.getHungChange();
 float float6 = food.getThirstChange();
 food.multiplyFoodValues(1.0F - percentage);
 if (float5 < 0.0F && food.getHungerChange() > -0.00999) {
 }

 if (float5 == 0.0F && float6 < 0.0F && food.getThirstChange() > -0.01F) {
 food.setHungChange(0.0F);
 food.UseItem();
 return true;
 }

 float float7 = 0.0F;
 if (food.isCustomWeight()) {
 std::string string1 = food.getReplaceOnUseFullType();
 Item item1 = string1.empty() ? nullptr : ScriptManager.instance.getItem(string1);
 if (item1 != nullptr) {
 float7 = item1.getActualWeight();
 }

 food.setWeight(food.getWeight() - float7 - float0 * (food.getWeight() - float7) + float7);
 }
 }

 return true;
 }
 }

 bool Eat(InventoryItem info) {
 return this->Eat(info, 1.0F);
 }

 void FireCheck() {
 if (!this->OnFire) {
 if (!GameServer.bServer || !(this instanceof IsoPlayer) {
 if (!GameClient.bClient || !this->isZombie() || !(this instanceof IsoZombie) || !((IsoZombie)this).isRemoteZombie()) {
 if (this->isZombie() && VirtualZombieManager.instance.isReused((IsoZombie)this) {
 DebugLog.log(DebugType.Zombie, "FireCheck running on REUSABLE ZOMBIE - IGNORED " + this);
 } else if (this->getVehicle() == nullptr) {
 if (this->square != nullptr
 && !GameServer.bServer
 && (
 !GameClient.bClient
 || this instanceof IsoPlayer && ((IsoPlayer)this).isLocalPlayer()
 || this instanceof IsoZombie && !((IsoZombie)this).isRemoteZombie()
 )
 && this->square.getProperties().Is(IsoFlagType.burning) {
 if ((!(this instanceof IsoPlayer) || Rand.Next(Rand.AdjustForFramerate(70) != 0) && !this->isZombie()) {
 if (!(this instanceof IsoPlayer) {
 this->Health = this->Health - this->FireKillRate * GameTime.instance.getMultiplier() / 2.0F;
 this->setAttackedBy(nullptr);
 } else {
 float float0 = this->FireKillRate * GameTime.instance.getMultiplier() * GameTime.instance.getMinutesPerDay() / 1.6F / 2.0F;
 this->BodyDamage.ReduceGeneralHealth(float0);
 LuaEventManager.triggerEvent("OnPlayerGetDamage", this, "FIRE", float0);
 this->BodyDamage.OnFire(true);
 this->forceAwake();
 }

 if (this->isDead()) {
 IsoFireManager.RemoveBurningCharacter(this);
 if (this->isZombie()) {
 LuaEventManager.triggerEvent("OnZombieDead", this);
 if (GameClient.bClient) {
 this->setAttackedBy(IsoWorld.instance.CurrentCell.getFakeZombieForHit());
 }
 }
 }
 } else {
 this->SetOnFire();
 }
 }
 }
 }
 }
 }
 }

 std::string getPrimaryHandType() {
 return this->leftHandItem.empty() ? nullptr : this->leftHandItem.getType();
 }

 float getGlobalMovementMod(bool bDoNoises) {
 return this->getCurrentState() != ClimbOverFenceState.instance()
 && this->getCurrentState() != ClimbThroughWindowState.instance()
 && this->getCurrentState() != ClimbOverWallState.instance()
 ? super.getGlobalMovementMod(bDoNoises)
 : 1.0F;
 }

 float getMoveSpeed() {
 tempo2.x = this->getX() - this->getLx();
 tempo2.y = this->getY() - this->getLy();
 return tempo2.getLength();
 }

 std::string getSecondaryHandType() {
 return this->rightHandItem.empty() ? nullptr : this->rightHandItem.getType();
 }

 bool HasItem(const std::string& string) {
 return string.empty()
 ? true
 : string == this->getSecondaryHandType()) || string == this->getPrimaryHandType()) || this->inventory.contains(string);
 }

 void changeState(State state) {
 this->stateMachine.changeState(state, nullptr);
 }

 State getCurrentState() {
 return this->stateMachine.getCurrent();
 }

 bool isCurrentState(State state) {
 return this->stateMachine.isSubstate(state) ? true : this->stateMachine.getCurrent() == state;
 }

 public HashMap<Object, Object> getStateMachineParams(State state) {
 return this->StateMachineParams.computeIfAbsent(state, var0 -> std::make_unique<HashMap<>>());
 }

 void setStateMachineLocked(bool val) {
 this->stateMachine.setLocked(val);
 }

 float Hit(HandWeapon weapon, IsoGameCharacter wielder, float damageSplit, bool bIgnoreDamage, float modDelta) {
 return this->Hit(weapon, wielder, damageSplit, bIgnoreDamage, modDelta, false);
 }

 float Hit(HandWeapon weapon, IsoGameCharacter wielder, float damageSplit, bool bIgnoreDamage, float modDelta, bool bRemote) {
 if (wielder != nullptr && weapon != nullptr) {
 if (!bIgnoreDamage && this->isZombie()) {
 IsoZombie zombie0 = (IsoZombie)this;
 zombie0.setHitTime(zombie0.getHitTime() + 1);
 if (zombie0.getHitTime() >= 4 && !bRemote) {
 damageSplit = (float)(damageSplit * ((zombie0.getHitTime() - 2) * 1.5);
 }
 }

 if (wielder instanceof IsoPlayer && ((IsoPlayer)wielder).bDoShove && !((IsoPlayer)wielder).isAimAtFloor()) {
 bIgnoreDamage = true;
 modDelta *= 1.5F;
 }

 LuaEventManager.triggerEvent("OnWeaponHitCharacter", wielder, this, weapon, damageSplit);
 LuaEventManager.triggerEvent("OnPlayerGetDamage", this, "WEAPONHIT", damageSplit);
 if (LuaHookManager.TriggerHook("WeaponHitCharacter", wielder, this, weapon, damageSplit) {
 return 0.0F;
 } else if (this->m_avoidDamage) {
 this->m_avoidDamage = false;
 return 0.0F;
 } else {
 if (this->noDamage) {
 bIgnoreDamage = true;
 this->noDamage = false;
 }

 if (this instanceof IsoSurvivor && !this->EnemyList.contains(wielder) {
 this->EnemyList.add(wielder);
 }

 this->staggerTimeMod = weapon.getPushBackMod() * weapon.getKnockbackMod(wielder) * wielder.getShovingMod();
 if (this->isZombie() && Rand.Next(3) == 0 && GameServer.bServer) {
 }

 wielder.addWorldSoundUnlessInvisible(5, 1, false);
 this->hitDir.x = this->getX();
 this->hitDir.y = this->getY();
 this->hitDir.x = this->hitDir.x - wielder.getX();
 this->hitDir.y = this->hitDir.y - wielder.getY();
 this->getHitDir().normalize();
 this->hitDir.x = this->hitDir.x * weapon.getPushBackMod();
 this->hitDir.y = this->hitDir.y * weapon.getPushBackMod();
 this->hitDir.rotate(weapon.HitAngleMod);
 this->setAttackedBy(wielder);
 float float0 = damageSplit;
 if (!bRemote) {
 float0 = this->processHitDamage(weapon, wielder, damageSplit, bIgnoreDamage, modDelta);
 }

 float float1 = 0.0F;
 if (weapon.isTwoHandWeapon() && (wielder.getPrimaryHandItem() != weapon || wielder.getSecondaryHandItem() != weapon) {
 float1 = weapon.getWeight() / 1.5F / 10.0F;
 }

 float float2 = (weapon.getWeight() * 0.28F * weapon.getFatigueMod(wielder) * this->getFatigueMod() * weapon.getEnduranceMod() * 0.3F + float1)
 * 0.04F;
 if (wielder instanceof IsoPlayer && wielder.isAimAtFloor() && ((IsoPlayer)wielder).bDoShove) {
 float2 *= 2.0F;
 }

 float float3;
 if (weapon.isAimedFirearm()) {
 float3 = float0 * 0.7F;
 } else {
 float3 = float0 * 0.15F;
 }

 if (this->getHealth() < float0) {
 float3 = this->getHealth();
 }

 float float4 = float3 / weapon.getMaxDamage();
 if (float4 > 1.0F) {
 float4 = 1.0F;
 }

 if (this->isCloseKilled()) {
 float4 = 0.2F;
 }

 if (weapon.isUseEndurance()) {
 if (float0 <= 0.0F) {
 float4 = 1.0F;
 }

 wielder.getStats().endurance -= float2 * float4;
 }

 this->hitConsequences(weapon, wielder, bIgnoreDamage, float0, bRemote);
 return float0;
 }
 } else {
 return 0.0F;
 }
 }

 float processHitDamage(HandWeapon weapon, IsoGameCharacter wielder, float damageSplit, bool bIgnoreDamage, float modDelta) {
 float float0 = damageSplit * modDelta;
 float float1 = float0;
 if (bIgnoreDamage) {
 float1 = float0 / 2.7F;
 }

 float float2 = float1 * wielder.getShovingMod();
 if (float2 > 1.0F) {
 float2 = 1.0F;
 }

 this->setHitForce(float2);
 if (wielder.Traits.Strong.isSet() && !weapon.isRanged()) {
 this->setHitForce(this->getHitForce() * 1.4F);
 }

 if (wielder.Traits.Weak.isSet() && !weapon.isRanged()) {
 this->setHitForce(this->getHitForce() * 0.6F);
 }

 float float3 = IsoUtils.DistanceTo(wielder.getX(), wielder.getY(), this->getX(), this->getY());
 float3 -= weapon.getMinRange();
 float3 /= weapon.getMaxRange(wielder);
 float3 = 1.0F - float3;
 if (float3 > 1.0F) {
 float3 = 1.0F;
 }

 float float4 = wielder.stats.endurance;
 float4 *= wielder.knockbackAttackMod;
 if (float4 < 0.5F) {
 float4 *= 1.3F;
 if (float4 < 0.4F) {
 float4 = 0.4F;
 }

 this->setHitForce(this->getHitForce() * float4);
 }

 if (!weapon.isRangeFalloff()) {
 float3 = 1.0F;
 }

 if (!weapon.isShareDamage()) {
 damageSplit = 1.0F;
 }

 if (wielder instanceof IsoPlayer && !bIgnoreDamage) {
 this->setHitForce(this->getHitForce() * 2.0F);
 }

 if (wielder instanceof IsoPlayer && !((IsoPlayer)wielder).bDoShove) {
 Vector2 vector0 = tempVector2_1.set(this->getX(), this->getY());
 Vector2 vector1 = tempVector2_2.set(wielder.getX(), wielder.getY());
 vector0.x = vector0.x - vector1.x;
 vector0.y = vector0.y - vector1.y;
 Vector2 vector2 = this->getVectorFromDirection(tempVector2_2);
 vector0.normalize();
 float float5 = vector0.dot(vector2);
 if (float5 > -0.3F) {
 float0 *= 1.5F;
 }
 }

 if (this instanceof IsoPlayer) {
 float0 *= 0.4F;
 } else {
 float0 *= 1.5F;
 }

 int int0 = wielder.getWeaponLevel();
 switch (int0) {
 case -1:
 float0 *= 0.3F;
 break;
 case 0:
 float0 *= 0.3F;
 break;
 case 1:
 float0 *= 0.4F;
 break;
 case 2:
 float0 *= 0.5F;
 break;
 case 3:
 float0 *= 0.6F;
 break;
 case 4:
 float0 *= 0.7F;
 break;
 case 5:
 float0 *= 0.8F;
 break;
 case 6:
 float0 *= 0.9F;
 break;
 case 7:
 float0 *= 1.0F;
 break;
 case 8:
 float0 *= 1.1F;
 break;
 case 9:
 float0 *= 1.2F;
 break;
 case 10:
 float0 *= 1.3F;
 }

 if (wielder instanceof IsoPlayer && wielder.isAimAtFloor() && !bIgnoreDamage && !((IsoPlayer)wielder).bDoShove) {
 float0 *= Math.max(5.0F, weapon.getCritDmgMultiplier());
 }

 if (wielder.isCriticalHit() && !bIgnoreDamage) {
 float0 *= Math.max(2.0F, weapon.getCritDmgMultiplier());
 }

 if (weapon.isTwoHandWeapon() && !wielder.isItemInBothHands(weapon) {
 float0 *= 0.5F;
 }

 return float0;
 }

 void hitConsequences(HandWeapon weapon, IsoGameCharacter wielder, bool bIgnoreDamage, float damage, bool bRemote) {
 if (!bIgnoreDamage) {
 if (weapon.isAimedFirearm()) {
 this->Health -= damage * 0.7F;
 } else {
 this->Health -= damage * 0.15F;
 }
 }

 if (this->isDead()) {
 if (!this->isOnKillDone() && this->shouldDoInventory()) {
 this->Kill(wielder);
 }

 if (this instanceof IsoZombie && ((IsoZombie)this).upKillCount) {
 wielder.setZombieKills(wielder.getZombieKills() + 1);
 }
 } else {
 if (weapon.isSplatBloodOnNoDeath()) {
 this->splatBlood(2, 0.2F);
 }

 if (weapon.isKnockBackOnNoDeath() && wielder.xp != nullptr) {
 wielder.xp.AddXP(PerkFactory.Perks.Strength, 2.0F);
 }
 }
 }

 bool IsAttackRange(float x, float y, float z) {
 float float0 = 1.0F;
 float float1 = 0.0F;
 if (this->leftHandItem != nullptr) {
 InventoryItem item = this->leftHandItem;
 if (item instanceof HandWeapon) {
 float0 = ((HandWeapon)item).getMaxRange(this);
 float1 = ((HandWeapon)item).getMinRange();
 float0 *= ((HandWeapon)this->leftHandItem).getRangeMod(this);
 }
 }

 if (Math.abs(z - this->getZ()) > 0.3F) {
 return false;
 } else {
 float float2 = IsoUtils.DistanceTo(x, y, this->getX(), this->getY());
 return float2 < float0 && float2 > float1;
 }
 }

 /**
 * This use some prediction on the zombie, if he's lunging toward the player attacking it we gonna add more range to our weapon, to avoid playing the "miss" animation
 */
 bool IsAttackRange(HandWeapon we, IsoMovingObject obj, Vector3 bonePos, bool extraRange) {
 if (we.empty()) {
 return false;
 } else {
 float float0 = Math.abs(obj.getZ() - this->getZ());
 if (!we.isRanged() && float0 >= 0.5F) {
 return false;
 } else if (float0 > 3.3F) {
 return false;
 } else {
 float float1 = we.getMaxRange(this);
 float1 *= we.getRangeMod(this);
 float float2 = IsoUtils.DistanceToSquared(this->x, this->y, bonePos.x, bonePos.y);
 if (extraRange) {
 IsoZombie zombie0 = Type.tryCastTo(obj, IsoZombie.class);
 if (zombie0 != nullptr
 && float2 < 4.0F
 && zombie0.target == this
 && (zombie0.isCurrentState(LungeState.instance()) || zombie0.isCurrentState(LungeNetworkState.instance()))) {
 float1++;
 }
 }

 return float2 < float1 * float1;
 }
 }
 }

 bool IsSpeaking() {
 return this->chatElement.IsSpeaking();
 }

 void MoveForward(float dist, float x, float y, float soundDelta) {
 if (!this->isCurrentState(SwipeStatePlayer.instance())) {
 float float0 = GameTime.instance.getMultiplier();
 this->setNx(this->getNx() + x * dist * float0);
 this->setNy(this->getNy() + y * dist * float0);
 this->DoFootstepSound(dist);
 if (!this->isZombie()) {
 }
 }
 }

 void pathToAux(float float0, float float1, float float2) {
 bool boolean0 = true;
 if ((int)float2 == (int)this->getZ() && IsoUtils.DistanceManhatten(float0, float1, this->x, this->y) <= 30.0F) {
 int int0 = (int)float0 / 10;
 int int1 = (int)float1 / 10;
 IsoChunk chunk = GameServer.bServer
 ? ServerMap.instance.getChunk(int0, int1)
 : IsoWorld.instance.CurrentCell.getChunkForGridSquare((int)float0, (int)float1, (int)float2);
 if (chunk != nullptr) {
 int int2 = 1;
 int2 |= 2;
 if (!this->isZombie()) {
 int2 |= 4;
 }

 boolean0 = !PolygonalMap2.instance
 .lineClearCollide(this->getX(), this->getY(), float0, float1, (int)float2, this->getPathFindBehavior2().getTargetChar(), int2);
 }
 }

 if (boolean0 && this->current != nullptr && this->current.HasStairs() && !this->current.isSameStaircase((int)float0, (int)float1, (int)float2) {
 boolean0 = false;
 }

 if (boolean0) {
 this->setVariable("bPathfind", false);
 this->setMoving(true);
 } else {
 this->setVariable("bPathfind", true);
 this->setMoving(false);
 }
 }

 void pathToCharacter(IsoGameCharacter target) {
 this->getPathFindBehavior2().pathToCharacter(target);
 this->pathToAux(target.getX(), target.getY(), target.getZ());
 }

 void pathToLocation(int x, int y, int z) {
 this->getPathFindBehavior2().pathToLocation(x, y, z);
 this->pathToAux(x + 0.5F, y + 0.5F, z);
 }

 void pathToLocationF(float x, float y, float z) {
 this->getPathFindBehavior2().pathToLocationF(x, y, z);
 this->pathToAux(x, y, z);
 }

 void pathToSound(int x, int y, int z) {
 this->getPathFindBehavior2().pathToSound(x, y, z);
 this->pathToAux(x + 0.5F, y + 0.5F, z);
 }

 bool CanAttack() {
 if (!this->isAttackAnim()
 && !this->getVariableBoolean("IsRacking")
 && !this->getVariableBoolean("IsUnloading")
 && StringUtils.isNullOrEmpty(this->getVariableString("RackWeapon"))) {
 if (!GameClient.bClient
 || !(this instanceof IsoPlayer)
 || !((IsoPlayer)this).isLocalPlayer()
 || !this->isCurrentState(PlayerHitReactionState.instance()) && !this->isCurrentState(PlayerHitReactionPVPState.instance())) {
 if (this->isSitOnGround()) {
 return false;
 } else {
 InventoryItem item = this->leftHandItem;
 if (item instanceof HandWeapon && item.getSwingAnim() != nullptr) {
 this->useHandWeapon = (HandWeapon)item;
 }

 if (this->useHandWeapon.empty()) {
 return true;
 } else if (this->useHandWeapon.getCondition() <= 0) {
 this->useHandWeapon = nullptr;
 if (this->rightHandItem == this->leftHandItem) {
 this->setSecondaryHandItem(nullptr);
 }

 this->setPrimaryHandItem(nullptr);
 if (this->getInventory() != nullptr) {
 this->getInventory().setDrawDirty(true);
 }

 return false;
 } else {
 float float0 = 12.0F;
 int int0 = this->Moodles.getMoodleLevel(MoodleType.Endurance);
 return !this->useHandWeapon.isCantAttackWithLowestEndurance() || int0 != 4;
 }
 }
 } else {
 return false;
 }
 } else {
 return false;
 }
 }

 void ReduceHealthWhenBurning() {
 if (this->OnFire) {
 if (this->isGodMod()) {
 this->StopBurning();
 } else if (!GameClient.bClient || !this->isZombie() || !(this instanceof IsoZombie) || !((IsoZombie)this).isRemoteZombie()) {
 if (!GameClient.bClient || !(this instanceof IsoPlayer) || !((IsoPlayer)this).bRemote) {
 if (this->isAlive()) {
 if (!(this instanceof IsoPlayer) {
 if (this->isZombie()) {
 this->Health = this->Health - this->FireKillRate / 20.0F * GameTime.instance.getMultiplier();
 this->setAttackedBy(nullptr);
 } else {
 this->Health = this->Health - this->FireKillRate * GameTime.instance.getMultiplier();
 }
 } else {
 float float0 = this->FireKillRate * GameTime.instance.getMultiplier() * GameTime.instance.getMinutesPerDay() / 1.6F;
 this->BodyDamage.ReduceGeneralHealth(float0);
 LuaEventManager.triggerEvent("OnPlayerGetDamage", this, "FIRE", float0);
 this->BodyDamage.OnFire(true);
 }

 if (this->isDead()) {
 IsoFireManager.RemoveBurningCharacter(this);
 if (this->isZombie()) {
 LuaEventManager.triggerEvent("OnZombieDead", this);
 if (GameClient.bClient) {
 this->setAttackedBy(IsoWorld.instance.CurrentCell.getFakeZombieForHit());
 }
 }
 }
 }

 if (this instanceof IsoPlayer && Rand.Next(Rand.AdjustForFramerate(((IsoPlayer)this).IsRunning() ? 150 : 400) == 0) {
 this->StopBurning();
 }
 }
 }
 }
 }

 void DrawSneezeText() {
 if (this->BodyDamage.IsSneezingCoughing() > 0) {
 std::string string = nullptr;
 if (this->BodyDamage.IsSneezingCoughing() == 1) {
 string = Translator.getText("IGUI_PlayerText_Sneeze");
 }

 if (this->BodyDamage.IsSneezingCoughing() == 2) {
 string = Translator.getText("IGUI_PlayerText_Cough");
 }

 if (this->BodyDamage.IsSneezingCoughing() == 3) {
 string = Translator.getText("IGUI_PlayerText_SneezeMuffled");
 }

 if (this->BodyDamage.IsSneezingCoughing() == 4) {
 string = Translator.getText("IGUI_PlayerText_CoughMuffled");
 }

 float float0 = this->sx;
 float float1 = this->sy;
 float0 = (int)float0;
 float1 = (int)float1;
 float0 -= (int)IsoCamera.getOffX();
 float1 -= (int)IsoCamera.getOffY();
 float1 -= 48.0F;
 if (string != nullptr) {
 TextManager.instance
 .DrawStringCentre(
 UIFont.Dialogue, (int)float0, (int)float1, string, this->SpeakColour.r, this->SpeakColour.g, this->SpeakColour.b, this->SpeakColour.a
 );
 }
 }
 }

 IsoSpriteInstance getSpriteDef() {
 if (this->def.empty()) {
 this->def = std::make_unique<IsoSpriteInstance>();
 }

 return this->def;
 }

 void render(float x, float y, float z, ColorInfo col, bool bDoChild, bool bWallLightingPass, Shader shader) {
 if (!this->isAlphaAndTargetZero()) {
 if (!this->isSeatedInVehicle() || this->getVehicle().showPassenger(this) {
 if (!this->isSpriteInvisible()) {
 if (!this->isAlphaZero()) {
 if (!this->bUseParts && this->def.empty()) {
 this->def = new IsoSpriteInstance(this->sprite);
 }

 SpriteRenderer.instance.glDepthMask(true);
 if (this->bDoDefer && z - (int)z > 0.2F) {
 IsoGridSquare square0 = this->getCell().getGridSquare((int)x, (int)y, (int)z + 1);
 if (square0 != nullptr) {
 square0.addDeferredCharacter(this);
 }
 }

 IsoGridSquare square1 = this->getCurrentSquare();
 if (PerformanceSettings.LightingFrameSkip < 3 && square1 != nullptr) {
 square1.interpolateLight(inf, x - square1.getX(), y - square1.getY());
 } else {
 inf.r = col.r;
 inf.g = col.g;
 inf.b = col.b;
 inf.a = col.a;
 }

 if (Core.bDebug && DebugOptions.instance.PathfindRenderWaiting.getValue() && this->hasActiveModel()) {
 if (this->getCurrentState() == PathFindState.instance() && this->finder.progress == AStarPathFinder.PathFindProgress.notyetfound) {
 this->legsSprite.modelSlot.model.tintR = 1.0F;
 this->legsSprite.modelSlot.model.tintG = 0.0F;
 this->legsSprite.modelSlot.model.tintB = 0.0F;
 } else {
 this->legsSprite.modelSlot.model.tintR = 1.0F;
 this->legsSprite.modelSlot.model.tintG = 1.0F;
 this->legsSprite.modelSlot.model.tintB = 1.0F;
 }
 }

 if (this->dir == IsoDirections.Max) {
 this->dir = IsoDirections.N;
 }

 if (this->sprite != nullptr && !this->legsSprite.hasActiveModel()) {
 this->checkDrawWeaponPre(x, y, z, col);
 }

 lastRenderedRendered = lastRendered;
 lastRendered = this;
 this->checkUpdateModelTextures();
 float float0 = Core.TileScale;
 float float1 = this->offsetX + 1.0F * float0;
 float float2 = this->offsetY + -89.0F * float0;
 if (this->sprite != nullptr) {
 this->def.setScale(float0, float0);
 if (!this->bUseParts) {
 this->sprite.render(this->def, this, x, y, z, this->dir, float1, float2, inf, true);
 } else if (this->legsSprite.hasActiveModel()) {
 this->legsSprite.renderActiveModel();
 } else if (!this->renderTextureInsteadOfModel(x, y) {
 this->def.Flip = false;
 inf.r = 1.0F;
 inf.g = 1.0F;
 inf.b = 1.0F;
 inf.a = this->def.alpha * 0.4F;
 this->legsSprite.renderCurrentAnim(this->def, this, x, y, z, this->dir, float1, float2, inf, false, nullptr);
 }
 }

 if (this->AttachedAnimSprite != nullptr) {
 for (int int0 = 0; int0 < this->AttachedAnimSprite.size(); int0++) {
 IsoSpriteInstance spriteInstance = this->AttachedAnimSprite.get(int0);
 spriteInstance.update();
 float float3 = inf.a;
 inf.a = spriteInstance.alpha;
 spriteInstance.SetTargetAlpha(this->getTargetAlpha());
 spriteInstance.render(this, x, y, z, this->dir, float1, float2, inf);
 inf.a = float3;
 }
 }

 for (int int1 = 0; int1 < this->inventory.Items.size(); int1++) {
 InventoryItem item = this->inventory.Items.get(int1);
 if (item instanceof IUpdater) {
 ((IUpdater)item).render();
 }
 }
 }
 }
 }
 }
 }

 void renderServerGUI() {
 if (this instanceof IsoPlayer) {
 this->setSceneCulled(false);
 }

 if (this->bUpdateModelTextures && this->hasActiveModel()) {
 this->bUpdateModelTextures = false;
 this->textureCreator = ModelInstanceTextureCreator.alloc();
 this->textureCreator.init(this);
 }

 float float0 = Core.TileScale;
 float float1 = this->offsetX + 1.0F * float0;
 float float2 = this->offsetY + -89.0F * float0;
 if (this->sprite != nullptr) {
 this->def.setScale(float0, float0);
 inf.r = 1.0F;
 inf.g = 1.0F;
 inf.b = 1.0F;
 inf.a = this->def.alpha * 0.4F;
 if (!this->isbUseParts()) {
 this->sprite.render(this->def, this, this->x, this->y, this->z, this->dir, float1, float2, inf, true);
 } else {
 this->def.Flip = false;
 this->legsSprite.render(this->def, this, this->x, this->y, this->z, this->dir, float1, float2, inf, true);
 }
 }

 if (Core.bDebug && this->hasActiveModel()) {
 if (this instanceof IsoZombie) {
 int int0 = (int)IsoUtils.XToScreenExact(this->x, this->y, this->z, 0);
 int int1 = (int)IsoUtils.YToScreenExact(this->x, this->y, this->z, 0);
 TextManager.instance.DrawString(int0, int1, "ID: " + this->getOnlineID());
 TextManager.instance.DrawString(int0, int1 + 10, "State: " + this->getCurrentStateName());
 TextManager.instance.DrawString(int0, int1 + 20, "Health: " + this->getHealth());
 }

 Vector2 vector = tempo;
 this->getDeferredMovement(vector);
 this->drawDirectionLine(vector, 1000.0F * vector.getLength() / GameTime.instance.getMultiplier() * 2.0F, 1.0F, 0.5F, 0.5F);
 }
 }

 float getAlphaUpdateRateMul() {
 float float0 = super.getAlphaUpdateRateMul();
 if (IsoCamera.CamCharacter.Traits.ShortSighted.isSet()) {
 float0 /= 2.0F;
 }

 if (IsoCamera.CamCharacter.Traits.EagleEyed.isSet()) {
 float0 *= 1.5F;
 }

 return float0;
 }

 bool isUpdateAlphaEnabled() {
 return !this->isTeleporting();
 }

 bool isUpdateAlphaDuringRender() {
 return false;
 }

 bool isSeatedInVehicle() {
 return this->vehicle != nullptr && this->vehicle.getSeat(this) != -1;
 }

 void renderObjectPicker(float x, float y, float z, ColorInfo _lightInfo) {
 if (!this->bUseParts) {
 this->sprite.renderObjectPicker(this->def, this, this->dir);
 } else {
 this->legsSprite.renderObjectPicker(this->def, this, this->dir);
 }
 }

 static Vector2 closestpointonline(double double4, double double2, double double5, double double1, double double9, double double8, Vector2 vector) {
 double double0 = double1 - double2;
 double double3 = double4 - double5;
 double double6 = (double1 - double2) * double4 + (double4 - double5) * double2;
 double double7 = -double3 * double9 + double0 * double8;
 double double10 = double0 * double0 - -double3 * double3;
 double double11;
 double double12;
 if (double10 != 0.0) {
 double11 = (double0 * double6 - double3 * double7) / double10;
 double12 = (double0 * double7 - -double3 * double6) / double10;
 } else {
 double11 = double9;
 double12 = double8;
 }

 return vector.set((float)double11, (float)double12);
 }

 void renderShadow(float x, float y, float z) {
 if (this->doRenderShadow) {
 if (!this->isAlphaAndTargetZero()) {
 if (!this->isSeatedInVehicle()) {
 IsoGridSquare square = this->getCurrentSquare();
 if (square != nullptr) {
 int int0 = IsoCamera.frameState.playerIndex;
 Vector3f vector3f0 = IsoGameCharacter.L_renderShadow.forward;
 Vector2 vector0 = this->getAnimVector(tempo2);
 vector3f0.set(vector0.x, vector0.y, 0.0F);
 float float0 = 0.45F;
 float float1 = 1.4F;
 float float2 = 1.125F;
 float float3 = this->getAlpha(int0);
 if (this->hasActiveModel() && this->hasAnimationPlayer() && this->getAnimationPlayer().isReady()) {
 AnimationPlayer animationPlayer = this->getAnimationPlayer();
 Vector3 vector1 = IsoGameCharacter.L_renderShadow.v1;
 Model.BoneToWorldCoords(this, animationPlayer.getSkinningBoneIndex("Bip01_Head", -1), vector1);
 float float4 = vector1.x;
 float float5 = vector1.y;
 Model.BoneToWorldCoords(this, animationPlayer.getSkinningBoneIndex("Bip01_L_Foot", -1), vector1);
 float float6 = vector1.x;
 float float7 = vector1.y;
 Model.BoneToWorldCoords(this, animationPlayer.getSkinningBoneIndex("Bip01_R_Foot", -1), vector1);
 float float8 = vector1.x;
 float float9 = vector1.y;
 Vector3f vector3f1 = IsoGameCharacter.L_renderShadow.v3;
 float float10 = 0.0F;
 float float11 = 0.0F;
 Vector2 vector2 = closestpointonline(x, y, x + vector3f0.x, y + vector3f0.y, float4, float5, tempo);
 float float12 = vector2.x;
 float float13 = vector2.y;
 float float14 = vector2.set(float12 - x, float13 - y).getLength();
 if (float14 > 0.001F) {
 vector3f1.set(float12 - x, float13 - y, 0.0F).normalize();
 if (vector3f0.dot(vector3f1) > 0.0F) {
 float10 = Math.max(float10, float14);
 } else {
 float11 = Math.max(float11, float14);
 }
 }

 vector2 = closestpointonline(x, y, x + vector3f0.x, y + vector3f0.y, float6, float7, tempo);
 float12 = vector2.x;
 float13 = vector2.y;
 float14 = vector2.set(float12 - x, float13 - y).getLength();
 if (float14 > 0.001F) {
 vector3f1.set(float12 - x, float13 - y, 0.0F).normalize();
 if (vector3f0.dot(vector3f1) > 0.0F) {
 float10 = Math.max(float10, float14);
 } else {
 float11 = Math.max(float11, float14);
 }
 }

 vector2 = closestpointonline(x, y, x + vector3f0.x, y + vector3f0.y, float8, float9, tempo);
 float12 = vector2.x;
 float13 = vector2.y;
 float14 = vector2.set(float12 - x, float13 - y).getLength();
 if (float14 > 0.001F) {
 vector3f1.set(float12 - x, float13 - y, 0.0F).normalize();
 if (vector3f0.dot(vector3f1) > 0.0F) {
 float10 = Math.max(float10, float14);
 } else {
 float11 = Math.max(float11, float14);
 }
 }

 float1 = (float10 + 0.35F) * 1.35F;
 float2 = (float11 + 0.35F) * 1.35F;
 float float15 = 0.1F * (GameTime.getInstance().getMultiplier() / 1.6F);
 float15 = PZMath.clamp(float15, 0.0F, 1.0F);
 if (this->shadowTick != IngameState.instance.numberTicks - 1L) {
 this->m_shadowFM = float1;
 this->m_shadowBM = float2;
 }

 this->shadowTick = IngameState.instance.numberTicks;
 this->m_shadowFM = PZMath.lerp(this->m_shadowFM, float1, float15);
 float1 = this->m_shadowFM;
 this->m_shadowBM = PZMath.lerp(this->m_shadowBM, float2, float15);
 float2 = this->m_shadowBM;
 } else if (this->isZombie() && this->isCurrentState(FakeDeadZombieState.instance())) {
 float3 = 1.0F;
 } else if (this->isSceneCulled()) {
 return;
 }

 ColorInfo colorInfo = square.lighting[int0].lightInfo();
 IsoDeadBody.renderShadow(x, y, z, vector3f0, float0, float1, float2, colorInfo, float3);
 }
 }
 }
 }
 }

 void checkUpdateModelTextures() {
 if (this->bUpdateModelTextures && this->hasActiveModel()) {
 this->bUpdateModelTextures = false;
 this->textureCreator = ModelInstanceTextureCreator.alloc();
 this->textureCreator.init(this);
 }

 if (this->bUpdateEquippedTextures && this->hasActiveModel()) {
 this->bUpdateEquippedTextures = false;
 if (this->primaryHandModel != nullptr && this->primaryHandModel.getTextureInitializer() != nullptr) {
 this->primaryHandModel.getTextureInitializer().setDirty();
 }

 if (this->secondaryHandModel != nullptr && this->secondaryHandModel.getTextureInitializer() != nullptr) {
 this->secondaryHandModel.getTextureInitializer().setDirty();
 }
 }
 }

 bool isMaskClicked(int x, int y, bool flip) {
 if (this->sprite.empty()) {
 return false;
 } else {
 return !this->bUseParts ? super.isMaskClicked(x, y, flip) : this->legsSprite.isMaskClicked(this->dir, x, y, flip);
 }
 }

 void setHaloNote(const std::string& str) {
 this->setHaloNote(str, this->haloDispTime);
 }

 void setHaloNote(const std::string& str, float dispTime) {
 this->setHaloNote(str, 0, 255, 0, dispTime);
 }

 void setHaloNote(const std::string& str, int r, int g, int b, float dispTime) {
 if (this->haloNote != nullptr && str != nullptr) {
 this->haloDispTime = dispTime;
 this->haloNote.setDefaultColors(r, g, b);
 this->haloNote.ReadString(str);
 this->haloNote.setInternalTickClock(this->haloDispTime);
 }
 }

 float getHaloTimerCount() {
 return this->haloNote != nullptr ? this->haloNote.getInternalClock() : 0.0F;
 }

 void DoSneezeText() {
 if (this->BodyDamage != nullptr) {
 if (this->BodyDamage.IsSneezingCoughing() > 0) {
 std::string string = nullptr;
 int int0 = 0;
 if (this->BodyDamage.IsSneezingCoughing() == 1) {
 string = Translator.getText("IGUI_PlayerText_Sneeze");
 int0 = Rand.Next(2) + 1;
 this->setVariable("Ext", "Sneeze" + int0);
 }

 if (this->BodyDamage.IsSneezingCoughing() == 2) {
 string = Translator.getText("IGUI_PlayerText_Cough");
 this->setVariable("Ext", "Cough");
 }

 if (this->BodyDamage.IsSneezingCoughing() == 3) {
 string = Translator.getText("IGUI_PlayerText_SneezeMuffled");
 int0 = Rand.Next(2) + 1;
 this->setVariable("Ext", "Sneeze" + int0);
 }

 if (this->BodyDamage.IsSneezingCoughing() == 4) {
 string = Translator.getText("IGUI_PlayerText_CoughMuffled");
 this->setVariable("Ext", "Cough");
 }

 if (string != nullptr) {
 this->Say(string);
 this->reportEvent("EventDoExt");
 if (GameClient.bClient && this instanceof IsoPlayer && ((IsoPlayer)this).isLocalPlayer()) {
 GameClient.sendSneezingCoughing(this->getOnlineID(), this->BodyDamage.IsSneezingCoughing(), (byte)int0);
 }
 }
 }
 }
 }

 std::string getSayLine() {
 return this->chatElement.getSayLine();
 }

 /**
 * 
 * @param sayLine the sayLine to set
 */
 void setSayLine(const std::string& sayLine) {
 this->Say(sayLine);
 }

 ChatMessage getLastChatMessage() {
 return this->lastChatMessage;
 }

 void setLastChatMessage(ChatMessage _lastChatMessage) {
 this->lastChatMessage = _lastChatMessage;
 }

 std::string getLastSpokenLine() {
 return this->lastSpokenLine;
 }

 void setLastSpokenLine(const std::string& line) {
 this->lastSpokenLine = line;
 }

 void doSleepSpeech() {
 this->sleepSpeechCnt++;
 if (this->sleepSpeechCnt > 250 * PerformanceSettings.getLockFPS() / 30.0F) {
 this->sleepSpeechCnt = 0;
 if (sleepText.empty()) {
 sleepText = "ZzzZZZzzzz";
 ChatElement.addNoLogText(sleepText);
 }

 this->SayWhisper(sleepText);
 }
 }

 void SayDebug(const std::string& text) {
 this->chatElement.SayDebug(0, text);
 }

 void SayDebug(int n, const std::string& text) {
 this->chatElement.SayDebug(n, text);
 }

 int getMaxChatLines() {
 return this->chatElement.getMaxChatLines();
 }

 void Say(const std::string& line) {
 if (!this->isZombie()) {
 this->ProcessSay(line, this->SpeakColour.r, this->SpeakColour.g, this->SpeakColour.b, 30.0F, 0, "default");
 }
 }

 void Say(const std::string& line, float r, float g, float b, UIFont font, float baseRange, const std::string& customTag) {
 this->ProcessSay(line, r, g, b, baseRange, 0, customTag);
 }

 void SayWhisper(const std::string& line) {
 this->ProcessSay(line, this->SpeakColour.r, this->SpeakColour.g, this->SpeakColour.b, 10.0F, 0, "whisper");
 }

 void SayShout(const std::string& line) {
 this->ProcessSay(line, this->SpeakColour.r, this->SpeakColour.g, this->SpeakColour.b, 60.0F, 0, "shout");
 }

 void SayRadio(const std::string& line, float r, float g, float b, UIFont font, float baseRange, int channel, const std::string& customTag) {
 this->ProcessSay(line, r, g, b, baseRange, channel, customTag);
 }

 void ProcessSay(const std::string& string0, float float0, float float1, float float2, float float3, int int0, const std::string& string1) {
 if (this->AllowConversation) {
 if (TutorialManager.instance.ProfanityFilter) {
 string0 = ProfanityFilter.getInstance().filterString(string0);
 }

 if (string1 == "default")) {
 ChatManager.getInstance().showInfoMessage(((IsoPlayer)this).getUsername(), string0);
 this->lastSpokenLine = string0;
 } else if (string1 == "whisper")) {
 this->lastSpokenLine = string0;
 } else if (string1 == "shout")) {
 ChatManager.getInstance().sendMessageToChat(((IsoPlayer)this).getUsername(), ChatType.shout, string0);
 this->lastSpokenLine = string0;
 } else if (string1 == "radio")) {
 UIFont uIFont = UIFont.Medium;
 bool boolean0 = true;
 bool boolean1 = true;
 bool boolean2 = true;
 bool boolean3 = false;
 bool boolean4 = false;
 bool boolean5 = true;
 this->chatElement
 .addChatLine(string0, float0, float1, float2, uIFont, float3, string1, boolean0, boolean1, boolean2, boolean3, boolean4, boolean5);
 if (ZomboidRadio.isStaticSound(string0) {
 ChatManager.getInstance().showStaticRadioSound(string0);
 } else {
 ChatManager.getInstance().showRadioMessage(string0, int0);
 }
 }
 }
 }

 void addLineChatElement(const std::string& line) {
 this->addLineChatElement(line, 1.0F, 1.0F, 1.0F);
 }

 void addLineChatElement(const std::string& line, float r, float g, float b) {
 this->addLineChatElement(line, r, g, b, UIFont.Dialogue, 30.0F, "default");
 }

 void addLineChatElement(const std::string& line, float r, float g, float b, UIFont font, float baseRange, const std::string& customTag) {
 this->addLineChatElement(line, r, g, b, font, baseRange, customTag, false, false, false, false, false, true);
 }

 public void addLineChatElement(
 String line,
 float r,
 float g,
 float b,
 UIFont font,
 float baseRange,
 String customTag,
 boolean bbcode,
 boolean img,
 boolean icons,
 boolean colors,
 boolean fonts,
 boolean equalizeHeights
 ) {
 this->chatElement.addChatLine(line, r, g, b, font, baseRange, customTag, bbcode, img, icons, colors, fonts, equalizeHeights);
 }

 bool playerIsSelf() {
 return IsoPlayer.getInstance() == this;
 }

 int getUserNameHeight() {
 if (!GameClient.bClient) {
 return 0;
 } else {
 return this->userName != nullptr ? this->userName.getHeight() : 0;
 }
 }

 void initTextObjects() {
 this->hasInitTextObjects = true;
 if (this instanceof IsoPlayer) {
 this->chatElement.setMaxChatLines(5);
 if (IsoPlayer.getInstance() != nullptr) {
 System.out.println("FirstNAME:" + IsoPlayer.getInstance().username);
 }

 this->isoPlayer = (IsoPlayer)this;
 if (this->isoPlayer.username != nullptr) {
 this->userName = std::make_unique<TextDrawObject>();
 this->userName.setAllowAnyImage(true);
 this->userName.setDefaultFont(UIFont.Small);
 this->userName.setDefaultColors(255, 255, 255, 255);
 this->updateUserName();
 }

 if (this->haloNote.empty()) {
 this->haloNote = std::make_unique<TextDrawObject>();
 this->haloNote.setDefaultFont(UIFont.Small);
 this->haloNote.setDefaultColors(0, 255, 0);
 this->haloNote.setDrawBackground(true);
 this->haloNote.setAllowImages(true);
 this->haloNote.setAllowAnyImage(true);
 this->haloNote.setOutlineColors(0.0F, 0.0F, 0.0F, 0.33F);
 }
 }
 }

 void updateUserName() {
 if (this->userName != nullptr && this->isoPlayer != nullptr) {
 std::string string = this->isoPlayer.getUsername(true);
 if (this != IsoPlayer.getInstance()
 && this->isInvisible()
 && IsoPlayer.getInstance() != nullptr
 && IsoPlayer.getInstance().accessLevel == "")
 && (!Core.bDebug || !DebugOptions.instance.CheatPlayerSeeEveryone.getValue())) {
 this->userName.ReadString("");
 return;
 }

 Faction faction = Faction.getPlayerFaction(this->isoPlayer);
 if (faction != nullptr) {
 if (!this->isoPlayer.showTag && this->isoPlayer != IsoPlayer.getInstance() && Faction.getPlayerFaction(IsoPlayer.getInstance()) != faction) {
 this->isoPlayer.tagPrefix = "";
 } else {
 this->isoPlayer.tagPrefix = faction.getTag();
 if (faction.getTagColor() != nullptr) {
 this->isoPlayer.setTagColor(faction.getTagColor());
 }
 }
 } else {
 this->isoPlayer.tagPrefix = "";
 }

 bool boolean0 = this->isoPlayer != nullptr && this->isoPlayer.bRemote || Core.getInstance().isShowYourUsername();
 if (IsoCamera.CamCharacter instanceof IsoPlayer && !((IsoPlayer)IsoCamera.CamCharacter).accessLevel == "")) {
 bool boolean1 = true;
 } else {
 bool boolean2 = false;
 }

 bool boolean3 = IsoCamera.CamCharacter instanceof IsoPlayer && ((IsoPlayer)IsoCamera.CamCharacter).canSeeAll;
 if (!ServerOptions.instance.DisplayUserName.getValue() && !ServerOptions.instance.ShowFirstAndLastName.getValue() && !boolean3) {
 boolean0 = false;
 }

 if (!boolean0) {
 string = "";
 }

 if (boolean0 && this->isoPlayer.tagPrefix != nullptr && !this->isoPlayer.tagPrefix == "")) {
 string = "[col="
 + new Float(this->isoPlayer.getTagColor().r * 255.0F).intValue()
 + ","
 + new Float(this->isoPlayer.getTagColor().g * 255.0F).intValue()
 + ","
 + new Float(this->isoPlayer.getTagColor().b * 255.0F).intValue()
 + "]["
 + this->isoPlayer.tagPrefix
 + "][/] "
 + string;
 }

 if (boolean0 && !this->isoPlayer.accessLevel == "") && this->isoPlayer.isShowAdminTag()) {
 string = this->namesPrefix.get(this->isoPlayer.accessLevel) + string;
 }

 if (boolean0
 && !this->isoPlayer.getSafety().isEnabled()
 && ServerOptions.instance.ShowSafety.getValue()
 && NonPvpZone.getNonPvpZone(PZMath.fastfloor(this->isoPlayer.x), PZMath.fastfloor(this->isoPlayer.y) == nullptr) {
 string = string + " [img=media/ui/Skull.png]";
 }

 if (this->isoPlayer.isSpeek && !this->isoPlayer.isVoiceMute) {
 string = "[img=media/ui/voiceon.png] " + string;
 }

 if (this->isoPlayer.isVoiceMute) {
 string = "[img=media/ui/voicemuted.png] " + string;
 }

 BaseVehicle vehiclex = IsoCamera.CamCharacter == this->isoPlayer ? this->isoPlayer.getNearVehicle() : nullptr;
 if (this->getVehicle() == nullptr
 && vehiclex != nullptr
 && (
 this->isoPlayer.getInventory().haveThisKeyId(vehiclex.getKeyId()) != nullptr
 || vehiclex.isHotwired()
 || SandboxOptions.getInstance().VehicleEasyUse.getValue()
 )) {
 Color color = Color.HSBtoRGB(vehiclex.colorHue, vehiclex.colorSaturation * 0.5F, vehiclex.colorValue);
 string = " [img=media/ui/CarKey.png," + color.getRedByte() + "," + color.getGreenByte() + "," + color.getBlueByte() + "]" + string;
 }

 if (!string == this->userName.getOriginal())) {
 this->userName.ReadString(string);
 }
 }
 }

 void updateTextObjects() {
 if (!GameServer.bServer) {
 if (!this->hasInitTextObjects) {
 this->initTextObjects();
 }

 if (!this->Speaking) {
 this->DoSneezeText();
 if (this->isAsleep() && this->getCurrentSquare() != nullptr && this->getCurrentSquare().getCanSee(0) {
 this->doSleepSpeech();
 }
 }

 if (this->isoPlayer != nullptr) {
 this->radioEquipedCheck();
 }

 this->Speaking = false;
 this->drawUserName = false;
 this->canSeeCurrent = false;
 if (this->haloNote != nullptr && this->haloNote.getInternalClock() > 0.0F) {
 this->haloNote.updateInternalTickClock();
 }

 this->legsSprite.PlayAnim("ZombieWalk1");
 this->chatElement.update();
 this->Speaking = this->chatElement.IsSpeaking();
 if (!this->Speaking || this->isDead()) {
 this->Speaking = false;
 this->callOut = false;
 }
 }
 }

 void renderlast() {
 super.renderlast();
 int int0 = IsoCamera.frameState.playerIndex;
 float float0 = this->x;
 float float1 = this->y;
 if (this->sx == 0.0F && this->def != nullptr) {
 this->sx = IsoUtils.XToScreen(float0 + this->def.offX, float1 + this->def.offY, this->z + this->def.offZ, 0);
 this->sy = IsoUtils.YToScreen(float0 + this->def.offX, float1 + this->def.offY, this->z + this->def.offZ, 0);
 this->sx = this->sx - (this->offsetX - 8.0F);
 this->sy = this->sy - (this->offsetY - 60.0F);
 }

 if (this->hasInitTextObjects && this->isoPlayer != nullptr || this->chatElement.getHasChatToDisplay()) {
 float float2 = IsoUtils.XToScreen(float0, float1, this->getZ(), 0);
 float float3 = IsoUtils.YToScreen(float0, float1, this->getZ(), 0);
 float2 = float2 - IsoCamera.getOffX() - this->offsetX;
 float3 = float3 - IsoCamera.getOffY() - this->offsetY;
 float3 -= 128 / (2 / Core.TileScale);
 float float4 = Core.getInstance().getZoom(int0);
 float2 /= float4;
 float3 /= float4;
 this->canSeeCurrent = true;
 this->drawUserName = false;
 if (this->isoPlayer != nullptr
 && (this == IsoCamera.frameState.CamCharacter || this->getCurrentSquare() != nullptr && this->getCurrentSquare().getCanSee(int0)
 || IsoPlayer.getInstance().isCanSeeAll()) {
 if (this == IsoPlayer.getInstance()) {
 this->canSeeCurrent = true;
 }

 if (GameClient.bClient && this->userName != nullptr && this->doRenderShadow) {
 this->drawUserName = false;
 if (ServerOptions.getInstance().MouseOverToSeeDisplayName.getValue()
 && this != IsoPlayer.getInstance()
 && !IsoPlayer.getInstance().isCanSeeAll()) {
 IsoObjectPicker.ClickObject clickObject = IsoObjectPicker.Instance.ContextPick(Mouse.getXA(), Mouse.getYA());
 if (clickObject != nullptr && clickObject.tile != nullptr) {
 for (int int1 = clickObject.tile.square.getX() - 1; int1 < clickObject.tile.square.getX() + 2; int1++) {
 for (int int2 = clickObject.tile.square.getY() - 1; int2 < clickObject.tile.square.getY() + 2; int2++) {
 IsoGridSquare square = IsoCell.getInstance().getGridSquare(int1, int2, clickObject.tile.square.getZ());
 if (square != nullptr) {
 for (int int3 = 0; int3 < square.getMovingObjects().size(); int3++) {
 IsoMovingObject movingObject = square.getMovingObjects().get(int3);
 if (movingObject instanceof IsoPlayer && this == movingObject) {
 this->drawUserName = true;
 break;
 }
 }

 if (this->drawUserName) {
 break;
 }
 }

 if (this->drawUserName) {
 break;
 }
 }
 }
 }
 } else {
 this->drawUserName = true;
 }

 if (this->drawUserName) {
 this->updateUserName();
 }
 }

 if (!GameClient.bClient && this->isoPlayer != nullptr && this->isoPlayer.getVehicle() == nullptr) {
 std::string string = "";
 BaseVehicle vehiclex = this->isoPlayer.getNearVehicle();
 if (this->getVehicle() == nullptr
 && vehiclex != nullptr
 && vehiclex.getPartById("Engine") != nullptr
 && (
 this->isoPlayer.getInventory().haveThisKeyId(vehiclex.getKeyId()) != nullptr
 || vehiclex.isHotwired()
 || SandboxOptions.getInstance().VehicleEasyUse.getValue()
 )
 && UIManager.VisibleAllUI) {
 Color color0 = Color.HSBtoRGB(
 vehiclex.colorHue, vehiclex.colorSaturation * 0.5F, vehiclex.colorValue, IsoGameCharacter.L_renderLast.color
 );
 string = " [img=media/ui/CarKey.png," + color0.getRedByte() + "," + color0.getGreenByte() + "," + color0.getBlueByte() + "]";
 }

 if (!string == "")) {
 this->userName.ReadString(string);
 this->drawUserName = true;
 }
 }
 }

 if (this->isoPlayer != nullptr && this->hasInitTextObjects && (this->playerIsSelf() || this->canSeeCurrent) {
 if (this->canSeeCurrent && this->drawUserName) {
 float3 -= this->userName.getHeight();
 this->userName.AddBatchedDraw((int)float2, (int)float3, true);
 }

 if (this->playerIsSelf()) {
 ActionProgressBar actionProgressBar = UIManager.getProgressBar(int0);
 if (actionProgressBar != nullptr && actionProgressBar.isVisible()) {
 float3 -= actionProgressBar.getHeight().intValue() + 2;
 }
 }

 if (this->playerIsSelf() && this->haloNote != nullptr && this->haloNote.getInternalClock() > 0.0F) {
 float float5 = this->haloNote.getInternalClock() / (this->haloDispTime / 4.0F);
 float5 = PZMath.min(float5, 1.0F);
 float3 -= this->haloNote.getHeight() + 2;
 this->haloNote.AddBatchedDraw((int)float2, (int)float3, true, float5);
 }
 }

 bool boolean0 = false;
 if (IsoPlayer.getInstance() != this
 && this->equipedRadio != nullptr
 && this->equipedRadio.getDeviceData() != nullptr
 && this->equipedRadio.getDeviceData().getHeadphoneType() >= 0) {
 boolean0 = true;
 }

 if (this->equipedRadio != nullptr && this->equipedRadio.getDeviceData() != nullptr && !this->equipedRadio.getDeviceData().getIsTurnedOn()) {
 boolean0 = true;
 }

 bool boolean1 = GameClient.bClient && IsoCamera.CamCharacter instanceof IsoPlayer && !((IsoPlayer)IsoCamera.CamCharacter).accessLevel.equals("");
 if (!this->m_invisible || this == IsoCamera.frameState.CamCharacter || boolean1) {
 this->chatElement.renderBatched(IsoPlayer.getPlayerIndex(), (int)float2, (int)float3, boolean0);
 }
 }

 if (Core.bDebug && DebugOptions.instance.Character.Debug.Render.Angle.getValue() && this->hasActiveModel()) {
 Vector2 vector0 = tempo;
 AnimationPlayer animationPlayer0 = this->getAnimationPlayer();
 vector0.set(this->dir.ToVector());
 this->drawDirectionLine(vector0, 2.4F, 0.0F, 1.0F, 0.0F);
 vector0.setLengthAndDirection(this->getLookAngleRadians(), 1.0F);
 this->drawDirectionLine(vector0, 2.0F, 1.0F, 1.0F, 1.0F);
 vector0.setLengthAndDirection(this->getAnimAngleRadians(), 1.0F);
 this->drawDirectionLine(vector0, 2.0F, 1.0F, 1.0F, 0.0F);
 float float6 = this->getForwardDirection().getDirection();
 vector0.setLengthAndDirection(float6, 1.0F);
 this->drawDirectionLine(vector0, 2.0F, 0.0F, 0.0F, 1.0F);
 }

 if (Core.bDebug && DebugOptions.instance.Character.Debug.Render.DeferredMovement.getValue() && this->hasActiveModel()) {
 Vector2 vector1 = tempo;
 AnimationPlayer animationPlayer1 = this->getAnimationPlayer();
 this->getDeferredMovement(vector1);
 this->drawDirectionLine(vector1, 1000.0F * vector1.getLength() / GameTime.instance.getMultiplier() * 2.0F, 1.0F, 0.5F, 0.5F);
 }

 if (Core.bDebug && DebugOptions.instance.Character.Debug.Render.DeferredAngles.getValue() && this->hasActiveModel()) {
 Vector2 vector2 = tempo;
 AnimationPlayer animationPlayer2 = this->getAnimationPlayer();
 this->getDeferredMovement(vector2);
 this->drawDirectionLine(vector2, 1000.0F * vector2.getLength() / GameTime.instance.getMultiplier() * 2.0F, 1.0F, 0.5F, 0.5F);
 }

 if (Core.bDebug && DebugOptions.instance.Character.Debug.Render.AimCone.getValue()) {
 this->debugAim();
 }

 if (Core.bDebug && DebugOptions.instance.Character.Debug.Render.TestDotSide.getValue()) {
 this->debugTestDotSide();
 }

 if (Core.bDebug && DebugOptions.instance.Character.Debug.Render.Vision.getValue()) {
 this->debugVision();
 }

 if (Core.bDebug) {
 if (DebugOptions.instance.MultiplayerShowZombieMultiplier.getValue() && this instanceof IsoZombie zombie0) {
 uint8_t byte0 = zombie0.canHaveMultipleHits();
 Color color1;
 if (byte0 == 0) {
 color1 = Colors.Green;
 } else if (byte0 == 1) {
 color1 = Colors.Yellow;
 } else {
 color1 = Colors.Red;
 }

 LineDrawer.DrawIsoCircle(this->x, this->y, this->z, 0.45F, 4, color1.r, color1.g, color1.b, 0.5F);
 TextManager.instance
 .DrawStringCentre(
 UIFont.DebugConsole,
 IsoUtils.XToScreenExact(this->x + 0.4F, this->y + 0.4F, this->z, 0),
 IsoUtils.YToScreenExact(this->x + 0.4F, this->y - 1.4F, this->z, 0),
 String.valueOf(zombie0.OnlineID),
 color1.r,
 color1.g,
 color1.b,
 color1.a
 );
 }

 if (DebugOptions.instance.MultiplayerShowZombieOwner.getValue() && this instanceof IsoZombie zombie1) {
 Color color2;
 if (zombie1.isDead()) {
 color2 = Colors.Yellow;
 } else if (zombie1.isRemoteZombie()) {
 color2 = Colors.OrangeRed;
 } else {
 color2 = Colors.Chartreuse;
 }

 LineDrawer.DrawIsoCircle(this->x, this->y, this->z, 0.45F, 4, color2.r, color2.g, color2.b, 0.5F);
 TextManager.instance
 .DrawStringCentre(
 UIFont.DebugConsole,
 IsoUtils.XToScreenExact(this->x + 0.4F, this->y + 0.4F, this->z, 0),
 IsoUtils.YToScreenExact(this->x + 0.4F, this->y - 1.4F, this->z, 0),
 String.valueOf(zombie1.OnlineID),
 color2.r,
 color2.g,
 color2.b,
 color2.a
 );
 }

 if (DebugOptions.instance.MultiplayerShowZombiePrediction.getValue() && this instanceof IsoZombie zombie2) {
 LineDrawer.DrawIsoTransform(
 this->realx,
 this->realy,
 this->z,
 this->realdir.ToVector().x,
 this->realdir.ToVector().y,
 0.35F,
 16,
 Colors.Blue.r,
 Colors.Blue.g,
 Colors.Blue.b,
 0.35F,
 1
 );
 if (zombie2.networkAI.DebugInterfaceActive) {
 LineDrawer.DrawIsoCircle(this->x, this->y, this->z, 0.4F, 4, 1.0F, 0.1F, 0.1F, 0.35F);
 } else if (!zombie2.isRemoteZombie()) {
 LineDrawer.DrawIsoCircle(this->x, this->y, this->z, 0.3F, 3, Colors.Magenta.r, Colors.Magenta.g, Colors.Magenta.b, 0.35F);
 } else {
 LineDrawer.DrawIsoCircle(this->x, this->y, this->z, 0.3F, 5, Colors.Magenta.r, Colors.Magenta.g, Colors.Magenta.b, 0.35F);
 }

 LineDrawer.DrawIsoTransform(
 zombie2.networkAI.targetX,
 zombie2.networkAI.targetY,
 this->z,
 1.0F,
 0.0F,
 0.4F,
 16,
 Colors.LimeGreen.r,
 Colors.LimeGreen.g,
 Colors.LimeGreen.b,
 0.35F,
 1
 );
 LineDrawer.DrawIsoLine(
 this->x,
 this->y,
 this->z,
 zombie2.networkAI.targetX,
 zombie2.networkAI.targetY,
 this->z,
 Colors.LimeGreen.r,
 Colors.LimeGreen.g,
 Colors.LimeGreen.b,
 0.35F,
 1
 );
 if (IsoUtils.DistanceToSquared(this->x, this->y, this->realx, this->realy) > 4.5F) {
 LineDrawer.DrawIsoLine(
 this->realx, this->realy, this->z, this->x, this->y, this->z, Colors.Magenta.r, Colors.Magenta.g, Colors.Magenta.b, 0.35F, 1
 );
 } else {
 LineDrawer.DrawIsoLine(this->realx, this->realy, this->z, this->x, this->y, this->z, Colors.Blue.r, Colors.Blue.g, Colors.Blue.b, 0.35F, 1);
 }
 }

 if (DebugOptions.instance.MultiplayerShowZombieDesync.getValue() && this instanceof IsoZombie zombie3) {
 float float7 = IsoUtils.DistanceTo(this->getX(), this->getY(), this->realx, this->realy);
 if (zombie3.isRemoteZombie() && float7 > 1.0F) {
 LineDrawer.DrawIsoLine(this->realx, this->realy, this->z, this->x, this->y, this->z, Colors.Blue.r, Colors.Blue.g, Colors.Blue.b, 0.9F, 1);
 LineDrawer.DrawIsoTransform(
 this->realx,
 this->realy,
 this->z,
 this->realdir.ToVector().x,
 this->realdir.ToVector().y,
 0.35F,
 16,
 Colors.Blue.r,
 Colors.Blue.g,
 Colors.Blue.b,
 0.9F,
 1
 );
 LineDrawer.DrawIsoCircle(this->x, this->y, this->z, 0.4F, 4, 1.0F, 1.0F, 1.0F, 0.9F);
 float float8 = IsoUtils.DistanceTo(this->realx, this->realy, zombie3.networkAI.targetX, zombie3.networkAI.targetY);
 float float9 = IsoUtils.DistanceTo(this->x, this->y, zombie3.networkAI.targetX, zombie3.networkAI.targetY) / float8;
 float float10 = IsoUtils.XToScreenExact(this->x, this->y, this->z, 0);
 float float11 = IsoUtils.YToScreenExact(this->x, this->y, this->z, 0);
 TextManager.instance
 .DrawStringCentre(
 UIFont.DebugConsole,
 float10,
 float11,
 String.format("dist:%f scale1:%f", float7, float9),
 Colors.NavajoWhite.r,
 Colors.NavajoWhite.g,
 Colors.NavajoWhite.b,
 0.9F
 );
 }
 }

 if (DebugOptions.instance.MultiplayerShowHit.getValue() && this->getHitReactionNetworkAI() != nullptr && this->getHitReactionNetworkAI().isSetup()) {
 LineDrawer.DrawIsoLine(
 this->x,
 this->y,
 this->z,
 this->x + this->getHitDir().getX(),
 this->y + this->getHitDir().getY(),
 this->z,
 Colors.BlueViolet.r,
 Colors.BlueViolet.g,
 Colors.BlueViolet.b,
 0.8F,
 1
 );
 LineDrawer.DrawIsoLine(
 this->getHitReactionNetworkAI().startPosition.x,
 this->getHitReactionNetworkAI().startPosition.y,
 this->z,
 this->getHitReactionNetworkAI().finalPosition.x,
 this->getHitReactionNetworkAI().finalPosition.y,
 this->z,
 Colors.Salmon.r,
 Colors.Salmon.g,
 Colors.Salmon.b,
 0.8F,
 1
 );
 float float12 = Colors.Salmon.r - 0.2F;
 float float13 = Colors.Salmon.g + 0.2F;
 LineDrawer.DrawIsoTransform(
 this->getHitReactionNetworkAI().startPosition.x,
 this->getHitReactionNetworkAI().startPosition.y,
 this->z,
 this->getHitReactionNetworkAI().startDirection.x,
 this->getHitReactionNetworkAI().startDirection.y,
 0.4F,
 16,
 float12,
 float13,
 Colors.Salmon.b,
 0.8F,
 1
 );
 float13 = Colors.Salmon.g - 0.2F;
 LineDrawer.DrawIsoTransform(
 this->getHitReactionNetworkAI().finalPosition.x,
 this->getHitReactionNetworkAI().finalPosition.y,
 this->z,
 this->getHitReactionNetworkAI().finalDirection.x,
 this->getHitReactionNetworkAI().finalDirection.y,
 0.4F,
 16,
 Colors.Salmon.r,
 float13,
 Colors.Salmon.b,
 0.8F,
 1
 );
 }

 if (DebugOptions.instance.MultiplayerShowPlayerPrediction.getValue() && this instanceof IsoPlayer) {
 if (this->isoPlayer != nullptr && this->isoPlayer.networkAI != nullptr && this->isoPlayer.networkAI.footstepSoundRadius != 0) {
 LineDrawer.DrawIsoCircle(
 this->x, this->y, this->z, this->isoPlayer.networkAI.footstepSoundRadius, 32, Colors.Violet.r, Colors.Violet.g, Colors.Violet.b, 0.5F
 );
 }

 if (this->isoPlayer != nullptr && this->isoPlayer.bRemote) {
 LineDrawer.DrawIsoCircle(this->x, this->y, this->z, 0.3F, 16, Colors.OrangeRed.r, Colors.OrangeRed.g, Colors.OrangeRed.b, 0.5F);
 tempo.set(this->realdir.ToVector());
 LineDrawer.DrawIsoTransform(
 this->realx, this->realy, this->z, tempo.x, tempo.y, 0.35F, 16, Colors.Blue.r, Colors.Blue.g, Colors.Blue.b, 0.5F, 1
 );
 LineDrawer.DrawIsoLine(this->realx, this->realy, this->z, this->x, this->y, this->z, Colors.Blue.r, Colors.Blue.g, Colors.Blue.b, 0.5F, 1);
 tempo.set(((IsoPlayer)this).networkAI.targetX, ((IsoPlayer)this).networkAI.targetY);
 LineDrawer.DrawIsoTransform(
 tempo.x, tempo.y, this->z, 1.0F, 0.0F, 0.4F, 16, Colors.LimeGreen.r, Colors.LimeGreen.g, Colors.LimeGreen.b, 0.5F, 1
 );
 LineDrawer.DrawIsoLine(
 this->x, this->y, this->z, tempo.x, tempo.y, this->z, Colors.LimeGreen.r, Colors.LimeGreen.g, Colors.LimeGreen.b, 0.5F, 1
 );
 }
 }

 if (DebugOptions.instance.MultiplayerShowTeleport.getValue() && this->getNetworkCharacterAI() != nullptr) {
 NetworkTeleport.NetworkTeleportDebug networkTeleportDebug = this->getNetworkCharacterAI().getTeleportDebug();
 if (networkTeleportDebug != nullptr) {
 LineDrawer.DrawIsoLine(
 networkTeleportDebug.lx,
 networkTeleportDebug.ly,
 networkTeleportDebug.lz,
 networkTeleportDebug.nx,
 networkTeleportDebug.ny,
 networkTeleportDebug.nz,
 Colors.NavajoWhite.r,
 Colors.NavajoWhite.g,
 Colors.NavajoWhite.b,
 0.7F,
 3
 );
 LineDrawer.DrawIsoCircle(
 networkTeleportDebug.nx,
 networkTeleportDebug.ny,
 networkTeleportDebug.nz,
 0.2F,
 16,
 Colors.NavajoWhite.r,
 Colors.NavajoWhite.g,
 Colors.NavajoWhite.b,
 0.7F
 );
 float float14 = IsoUtils.XToScreenExact(networkTeleportDebug.lx, networkTeleportDebug.ly, networkTeleportDebug.lz, 0);
 float float15 = IsoUtils.YToScreenExact(networkTeleportDebug.lx, networkTeleportDebug.ly, networkTeleportDebug.lz, 0);
 TextManager.instance
 .DrawStringCentre(
 UIFont.DebugConsole,
 float14,
 float15,
 String.format(
 "%s id=%d",
 this instanceof IsoPlayer ? ((IsoPlayer)this).getUsername() : this->getClass().getSimpleName(),
 networkTeleportDebug.id
 ),
 Colors.NavajoWhite.r,
 Colors.NavajoWhite.g,
 Colors.NavajoWhite.b,
 0.7F
 );
 TextManager.instance
 .DrawStringCentre(
 UIFont.DebugConsole,
 float14,
 float15 + 10.0F,
 networkTeleportDebug.type.name(),
 Colors.NavajoWhite.r,
 Colors.NavajoWhite.g,
 Colors.NavajoWhite.b,
 0.7F
 );
 }
 } else if (this->getNetworkCharacterAI() != nullptr) {
 this->getNetworkCharacterAI().clearTeleportDebug();
 }

 if (DebugOptions.instance.MultiplayerShowZombieStatus.getValue() && this instanceof IsoZombie
 || DebugOptions.instance.MultiplayerShowPlayerStatus.getValue() && this instanceof IsoPlayer && !((IsoPlayer)this).isGodMod()) {
 TextManager.StringDrawer stringDrawer = TextManager.instance::DrawString;
 if (this instanceof IsoPlayer && this->isLocal()) {
 stringDrawer = TextManager.instance::DrawStringRight;
 }

 float float16 = IsoUtils.XToScreenExact(this->x, this->y, this->z, 0);
 float float17 = IsoUtils.YToScreenExact(this->x, this->y, this->z, 0);
 float float18 = 10.0F;
 Color color3 = Colors.GreenYellow;
 float float19;
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float19 = float18 + 11.0F),
 String.format(
 "%d %s : %.03f / %.03f",
 this->getOnlineID(),
 this->isFemale() ? "F" : "M",
 this->getHealth(),
 this instanceof IsoZombie ? 0.0F : this->getBodyDamage().getOverallBodyHealth()
 ),
 color3.r,
 color3.g,
 color3.b,
 color3.a
 );
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float18 = float19 + 11.0F),
 String.format("x=%09.3f ", this->x) + String.format("y=%09.3f ", this->y) + String.format("z=%d", (byte)this->z),
 color3.r,
 color3.g,
 color3.b,
 color3.a
 );
 if (this instanceof IsoPlayer player) {
 Color color4 = Colors.NavajoWhite;
 float float20;
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float20 = float18 + 18.0F),
 String.format("IdleSpeed: %s , targetDist: %s ", player.getVariableString("IdleSpeed"), player.getVariableString("targetDist")),
 color4.r,
 color4.g,
 color4.b,
 1.0
 );
 float float21;
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float21 = float20 + 11.0F),
 String.format("WalkInjury: %s , WalkSpeed: %s", player.getVariableString("WalkInjury"), player.getVariableString("WalkSpeed")),
 color4.r,
 color4.g,
 color4.b,
 1.0
 );
 float float22;
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float22 = float21 + 11.0F),
 String.format("DeltaX: %s , DeltaY: %s", player.getVariableString("DeltaX"), player.getVariableString("DeltaY")),
 color4.r,
 color4.g,
 color4.b,
 1.0
 );
 float float23;
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float23 = float22 + 11.0F),
 String.format(
 "AttackVariationX: %s , AttackVariationY: %s",
 player.getVariableString("AttackVariationX"),
 player.getVariableString("AttackVariationY")
 ),
 color4.r,
 color4.g,
 color4.b,
 1.0
 );
 float float24;
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float24 = float23 + 11.0F),
 String.format(
 "autoShootVarX: %s , autoShootVarY: %s", player.getVariableString("autoShootVarX"), player.getVariableString("autoShootVarY")
 ),
 color4.r,
 color4.g,
 color4.b,
 1.0
 );
 float float25;
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float25 = float24 + 11.0F),
 String.format("recoilVarX: %s , recoilVarY: %s", player.getVariableString("recoilVarX"), player.getVariableString("recoilVarY")),
 color4.r,
 color4.g,
 color4.b,
 1.0
 );
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float18 = float25 + 11.0F),
 String.format("ShoveAimX: %s , ShoveAimY: %s", player.getVariableString("ShoveAimX"), player.getVariableString("ShoveAimY")),
 color4.r,
 color4.g,
 color4.b,
 1.0
 );
 }

 color3 = Colors.Yellow;
 float float26;
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float26 = float18 + 18.0F),
 String.format("isHitFromBehind=%b/%b", this->isHitFromBehind(), this->getVariableBoolean("frombehind")),
 color3.r,
 color3.g,
 color3.b,
 1.0
 );
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float18 = float26 + 11.0F),
 String.format("bKnockedDown=%b/%b", this->isKnockedDown(), this->getVariableBoolean("bknockeddown")),
 color3.r,
 color3.g,
 color3.b,
 1.0
 );
 float float27;
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float27 = float18 + 11.0F),
 String.format("isFallOnFront=%b/%b", this->isFallOnFront(), this->getVariableBoolean("fallonfront")),
 color3.r,
 color3.g,
 color3.b,
 1.0
 );
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float18 = float27 + 11.0F),
 String.format("isOnFloor=%b/%b", this->isOnFloor(), this->getVariableBoolean("bonfloor")),
 color3.r,
 color3.g,
 color3.b,
 1.0
 );
 float float28;
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float28 = float18 + 11.0F),
 String.format("isDead=%b/%b", this->isDead(), this->getVariableBoolean("bdead")),
 color3.r,
 color3.g,
 color3.b,
 1.0
 );
 if (this instanceof IsoZombie) {
 float float29;
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float29 = float28 + 11.0F),
 String.format("bThump=%b", this->getVariableString("bThump")),
 color3.r,
 color3.g,
 color3.b,
 1.0
 );
 float float30;
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float30 = float29 + 11.0F),
 String.format("ThumpType=%s", this->getVariableString("ThumpType")),
 color3.r,
 color3.g,
 color3.b,
 1.0
 );
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float18 = float30 + 11.0F),
 String.format("onknees=%b", this->getVariableBoolean("onknees")),
 color3.r,
 color3.g,
 color3.b,
 1.0
 );
 } else {
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float18 = float28 + 11.0F),
 String.format("isBumped=%b/%s", this->isBumped(), this->getBumpType()),
 color3.r,
 color3.g,
 color3.b,
 1.0
 );
 }

 color3 = Colors.OrangeRed;
 if (this->getReanimateTimer() <= 0.0F) {
 color3 = Colors.LimeGreen;
 } else if (this->isBeingSteppedOn()) {
 color3 = Colors.Blue;
 }

 float float31;
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float31 = float18 + 18.0F),
 "Reanimate: " + this->getReanimateTimer(),
 color3.r,
 color3.g,
 color3.b,
 1.0
 );
 if (this->advancedAnimator.getRootLayer() != nullptr) {
 color3 = Colors.Pink;
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float18 = float31 + 18.0F),
 "Animation set: " + this->advancedAnimator.animSet.m_Name,
 color3.r,
 color3.g,
 color3.b,
 1.0
 );
 float float32;
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float32 = float18 + 11.0F),
 "Animation state: " + this->advancedAnimator.getCurrentStateName(),
 color3.r,
 color3.g,
 color3.b,
 1.0
 );
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float31 = float32 + 11.0F),
 "Animation node: " + this->advancedAnimator.getRootLayer().getDebugNodeName(),
 color3.r,
 color3.g,
 color3.b,
 1.0
 );
 }

 color3 = Colors.LightBlue;
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float18 = float31 + 11.0F),
 String.format("Previous state: %s ( %s )", this->getPreviousStateName(), this->getPreviousActionContextStateName()),
 color3.r,
 color3.g,
 color3.b,
 1.0
 );
 float float33;
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float33 = float18 + 11.0F),
 String.format("Current state: %s ( %s )", this->getCurrentStateName(), this->getCurrentActionContextStateName()),
 color3.r,
 color3.g,
 color3.b,
 1.0
 );
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float18 = float33 + 11.0F),
 String.format(
 "Child state: %s",
 this->getActionContext() != nullptr
 && this->getActionContext().getChildStates() != nullptr
 && this->getActionContext().getChildStates().size() > 0
 && this->getActionContext().getChildStateAt(0) != nullptr
 ? this->getActionContext().getChildStateAt(0).getName()
 : "\"\""
 ),
 color3.r,
 color3.g,
 color3.b,
 1.0
 );
 if (this->CharacterActions != nullptr) {
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float18 += 11.0F),
 String.format("Character actions: %d", this->CharacterActions.size()),
 color3.r,
 color3.g,
 color3.b,
 1.0
 );

 for (BaseAction baseAction : this->CharacterActions) {
 if (baseAction instanceof LuaTimedActionNew) {
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float18 += 11.0F),
 String.format("Action: %s", ((LuaTimedActionNew)baseAction).getMetaType()),
 color3.r,
 color3.g,
 color3.b,
 1.0
 );
 }
 }
 }

 if (this instanceof IsoZombie) {
 color3 = Colors.GreenYellow;
 IsoZombie zombie4 = (IsoZombie)this;
 float float34;
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float34 = float18 + 18.0F),
 "Prediction: " + this->getNetworkCharacterAI().predictionType,
 color3.r,
 color3.g,
 color3.b,
 1.0
 );
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float18 = float34 + 11.0F),
 String.format("Real state: %s", zombie4.realState),
 color3.r,
 color3.g,
 color3.b,
 1.0
 );
 if (zombie4.target instanceof IsoPlayer) {
 float float35;
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float35 = float18 + 11.0F),
 "Target: " + ((IsoPlayer)zombie4.target).username + " =" + zombie4.vectorToTarget.getLength(),
 color3.r,
 color3.g,
 color3.b,
 1.0
 );
 } else {
 float float36;
 stringDrawer.draw(
 UIFont.DebugConsole,
 float16,
 float17 + (float36 = float18 + 11.0F),
 "Target: " + zombie4.target + " =" + zombie4.vectorToTarget.getLength(),
 color3.r,
 color3.g,
 color3.b,
 1.0
 );
 }
 }
 }
 }

 if (this->inventory != nullptr) {
 for (int int4 = 0; int4 < this->inventory.Items.size(); int4++) {
 InventoryItem item = this->inventory.Items.get(int4);
 if (item instanceof IUpdater) {
 ((IUpdater)item).renderlast();
 }
 }

 if (Core.bDebug && DebugOptions.instance.PathfindRenderPath.getValue() && this->pfb2 != nullptr) {
 this->pfb2.render();
 }

 if (Core.bDebug && DebugOptions.instance.CollideWithObstaclesRenderRadius.getValue()) {
 float float37 = 0.3F;
 float float38 = 1.0F;
 float float39 = 1.0F;
 float float40 = 1.0F;
 if (!this->isCollidable()) {
 float40 = 0.0F;
 }

 if ((int)this->z != (int)IsoCamera.frameState.CamCharacterZ) {
 float40 = 0.5F;
 float39 = 0.5F;
 float38 = 0.5F;
 }

 LineDrawer.DrawIsoCircle(this->x, this->y, this->z, float37, 16, float38, float39, float40, 1.0F);
 }

 if (DebugOptions.instance.Animation.Debug.getValue() && this->hasActiveModel()) {
 int int5 = (int)IsoUtils.XToScreenExact(this->x, this->y, this->z, 0);
 int int6 = (int)IsoUtils.YToScreenExact(this->x, this->y, this->z, 0);
 TextManager.instance.DrawString(int5, int6, this->getAnimationDebug());
 }

 if (this->getIsNPC() && this->GameCharacterAIBrain != nullptr) {
 this->GameCharacterAIBrain.renderlast();
 }
 }
 }

 bool renderTextureInsteadOfModel(float var1, float var2) {
 return false;
 }

 void drawDirectionLine(Vector2 dir, float length, float r, float g, float b) {
 float float0 = this->x + dir.x * length;
 float float1 = this->y + dir.y * length;
 float float2 = IsoUtils.XToScreenExact(this->x, this->y, this->z, 0);
 float float3 = IsoUtils.YToScreenExact(this->x, this->y, this->z, 0);
 float float4 = IsoUtils.XToScreenExact(float0, float1, this->z, 0);
 float float5 = IsoUtils.YToScreenExact(float0, float1, this->z, 0);
 LineDrawer.drawLine(float2, float3, float4, float5, r, g, b, 0.5F, 1);
 }

 void drawDebugTextBelow(const std::string& text) {
 int int0 = TextManager.instance.MeasureStringX(UIFont.Small, text) + 32;
 int int1 = TextManager.instance.getFontHeight(UIFont.Small);
 int int2 = (int)Math.ceil(int1 * 1.25);
 float float0 = IsoUtils.XToScreenExact(this->getX() + 0.25F, this->getY() + 0.25F, this->getZ(), 0);
 float float1 = IsoUtils.YToScreenExact(this->getX() + 0.25F, this->getY() + 0.25F, this->getZ(), 0);
 SpriteRenderer.instance.renderi(nullptr, (int)(float0 - int0 / 2), (int)(float1 - (int2 - int1) / 2), int0, int2, 0.0F, 0.0F, 0.0F, 0.5F, nullptr);
 TextManager.instance.DrawStringCentre(UIFont.Small, float0, float1, text, 1.0, 1.0, 1.0, 1.0);
 }

 Radio getEquipedRadio() {
 return this->equipedRadio;
 }

 void radioEquipedCheck() {
 if (this->leftHandItem != this->leftHandCache) {
 this->leftHandCache = this->leftHandItem;
 if (this->leftHandItem != nullptr && (this->equipedRadio.empty() || this->equipedRadio != this->rightHandItem) && this->leftHandItem instanceof Radio) {
 this->equipedRadio = (Radio)this->leftHandItem;
 } else if (this->equipedRadio != nullptr && this->equipedRadio != this->rightHandItem) {
 if (this->equipedRadio.getDeviceData() != nullptr) {
 this->equipedRadio.getDeviceData().cleanSoundsAndEmitter();
 }

 this->equipedRadio = nullptr;
 }
 }

 if (this->rightHandItem != this->rightHandCache) {
 this->rightHandCache = this->rightHandItem;
 if (this->rightHandItem != nullptr && this->rightHandItem instanceof Radio) {
 this->equipedRadio = (Radio)this->rightHandItem;
 } else if (this->equipedRadio != nullptr && this->equipedRadio != this->leftHandItem) {
 if (this->equipedRadio.getDeviceData() != nullptr) {
 this->equipedRadio.getDeviceData().cleanSoundsAndEmitter();
 }

 this->equipedRadio = nullptr;
 }
 }
 }

 void debugAim() {
 if (this == IsoPlayer.getInstance()) {
 IsoPlayer player = (IsoPlayer)this;
 if (player.IsAiming()) {
 HandWeapon weapon = Type.tryCastTo(this->getPrimaryHandItem(), HandWeapon.class);
 if (weapon.empty()) {
 weapon = player.bareHands;
 }

 float float0 = weapon.getMaxRange(player) * weapon.getRangeMod(player);
 float float1 = this->getLookAngleRadians();
 LineDrawer.drawDirectionLine(this->x, this->y, this->z, float0, float1, 1.0F, 1.0F, 1.0F, 0.5F, 1);
 float float2 = weapon.getMinAngle();
 float2 -= weapon.getAimingPerkMinAngleModifier() * (this->getPerkLevel(PerkFactory.Perks.Aiming) / 2.0F);
 LineDrawer.drawDotLines(this->x, this->y, this->z, float0, float1, float2, 1.0F, 1.0F, 1.0F, 0.5F, 1);
 float float3 = weapon.getMinRange();
 LineDrawer.drawArc(this->x, this->y, this->z, float3, float1, float2, 6, 1.0F, 1.0F, 1.0F, 0.5F);
 if (float3 != float0) {
 LineDrawer.drawArc(this->x, this->y, this->z, float0, float1, float2, 6, 1.0F, 1.0F, 1.0F, 0.5F);
 }

 float float4 = PZMath.min(float0 + 1.0F, 2.0F);
 LineDrawer.drawArc(this->x, this->y, this->z, float4, float1, float2, 6, 0.75F, 0.75F, 0.75F, 0.5F);
 float float5 = Core.getInstance().getIgnoreProneZombieRange();
 if (float5 > 0.0F) {
 LineDrawer.drawArc(this->x, this->y, this->z, float5, float1, 0.0F, 12, 0.0F, 0.0F, 1.0F, 0.25F);
 LineDrawer.drawDotLines(this->x, this->y, this->z, float5, float1, 0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 1);
 }

 AttackVars attackVarsx = new AttackVars();
 std::vector arrayList = new ArrayList();
 SwipeStatePlayer.instance().CalcAttackVars((IsoLivingCharacter)this, attackVarsx);
 SwipeStatePlayer.instance().CalcHitList(this, false, attackVarsx, arrayList);
 if (attackVarsx.targetOnGround.getMovingObject() != nullptr) {
 HitInfo hitInfo0 = attackVarsx.targetsProne.get(0);
 LineDrawer.DrawIsoCircle(hitInfo0.x, hitInfo0.y, hitInfo0.z, 0.1F, 8, 1.0F, 1.0F, 0.0F, 1.0F);
 } else if (attackVarsx.targetsStanding.size() > 0) {
 HitInfo hitInfo1 = attackVarsx.targetsStanding.get(0);
 LineDrawer.DrawIsoCircle(hitInfo1.x, hitInfo1.y, hitInfo1.z, 0.1F, 8, 1.0F, 1.0F, 0.0F, 1.0F);
 }

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 HitInfo hitInfo2 = (HitInfo)arrayList.get(int0);
 IsoMovingObject movingObject = hitInfo2.getObject();
 if (movingObject != nullptr) {
 int int1 = hitInfo2.chance;
 float float6 = 1.0F - int1 / 100.0F;
 float float7 = 1.0F - float6;
 float float8 = Math.max(0.2F, int1 / 100.0F) / 2.0F;
 float float9 = IsoUtils.XToScreenExact(movingObject.x - float8, movingObject.y + float8, movingObject.z, 0);
 float float10 = IsoUtils.YToScreenExact(movingObject.x - float8, movingObject.y + float8, movingObject.z, 0);
 float float11 = IsoUtils.XToScreenExact(movingObject.x - float8, movingObject.y - float8, movingObject.z, 0);
 float float12 = IsoUtils.YToScreenExact(movingObject.x - float8, movingObject.y - float8, movingObject.z, 0);
 float float13 = IsoUtils.XToScreenExact(movingObject.x + float8, movingObject.y - float8, movingObject.z, 0);
 float float14 = IsoUtils.YToScreenExact(movingObject.x + float8, movingObject.y - float8, movingObject.z, 0);
 float float15 = IsoUtils.XToScreenExact(movingObject.x + float8, movingObject.y + float8, movingObject.z, 0);
 float float16 = IsoUtils.YToScreenExact(movingObject.x + float8, movingObject.y + float8, movingObject.z, 0);
 SpriteRenderer.instance.renderPoly(float9, float10, float11, float12, float13, float14, float15, float16, float6, float7, 0.0F, 0.5F);
 UIFont uIFont = UIFont.DebugConsole;
 TextManager.instance.DrawStringCentre(uIFont, float15, float16, String.valueOf(hitInfo2.dot), 1.0, 1.0, 1.0, 1.0);
 TextManager.instance
 .DrawStringCentre(uIFont, float15, float16 + TextManager.instance.getFontHeight(uIFont), hitInfo2.chance + "%", 1.0, 1.0, 1.0, 1.0);
 float6 = 1.0F;
 float7 = 1.0F;
 float float17 = 1.0F;
 float float18 = PZMath.sqrt(hitInfo2.distSq);
 if (float18 < weapon.getMinRange()) {
 float17 = 0.0F;
 float6 = 0.0F;
 }

 TextManager.instance
 .DrawStringCentre(
 uIFont, float15, float16 + TextManager.instance.getFontHeight(uIFont) * 2, "DIST: " + float18, float6, float7, float17, 1.0
 );
 }

 if (hitInfo2.window.getObject() != nullptr) {
 hitInfo2.window.getObject().setHighlighted(true);
 }
 }
 }
 }
 }

 void debugTestDotSide() {
 if (this == IsoPlayer.getInstance()) {
 float float0 = this->getLookAngleRadians();
 float float1 = 2.0F;
 float float2 = 0.7F;
 LineDrawer.drawDotLines(this->x, this->y, this->z, float1, float0, float2, 1.0F, 1.0F, 1.0F, 0.5F, 1);
 float2 = -0.5F;
 LineDrawer.drawDotLines(this->x, this->y, this->z, float1, float0, float2, 1.0F, 1.0F, 1.0F, 0.5F, 1);
 LineDrawer.drawArc(this->x, this->y, this->z, float1, float0, -1.0F, 16, 1.0F, 1.0F, 1.0F, 0.5F);
 std::vector arrayList = this->getCell().getZombieList();

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 IsoMovingObject movingObject = (IsoMovingObject)arrayList.get(int0);
 if (this->DistToSquared(movingObject) < float1 * float1) {
 LineDrawer.DrawIsoCircle(movingObject.x, movingObject.y, movingObject.z, 0.3F, 1.0F, 1.0F, 1.0F, 1.0F);
 float float3 = 0.2F;
 float float4 = IsoUtils.XToScreenExact(movingObject.x + float3, movingObject.y + float3, movingObject.z, 0);
 float float5 = IsoUtils.YToScreenExact(movingObject.x + float3, movingObject.y + float3, movingObject.z, 0);
 UIFont uIFont = UIFont.DebugConsole;
 int int1 = TextManager.instance.getFontHeight(uIFont);
 TextManager.instance.DrawStringCentre(uIFont, float4, float5 + int1, "SIDE: " + this->testDotSide(movingObject), 1.0, 1.0, 1.0, 1.0);
 Vector2 vector0 = this->getLookVector(tempo2);
 Vector2 vector1 = tempo.set(movingObject.x - this->x, movingObject.y - this->y);
 vector1.normalize();
 float float6 = PZMath.wrap(vector1.getDirection() - vector0.getDirection(), 0.0F, (float) (Math.PI * 2);
 TextManager.instance.DrawStringCentre(uIFont, float4, float5 + int1 * 2, "ANGLE (0-360): " + PZMath.radToDeg(float6), 1.0, 1.0, 1.0, 1.0);
 float6 = (float)Math.acos(this->getDotWithForwardDirection(movingObject.x, movingObject.y);
 TextManager.instance.DrawStringCentre(uIFont, float4, float5 + int1 * 3, "ANGLE (0-180): " + PZMath.radToDeg(float6), 1.0, 1.0, 1.0, 1.0);
 }
 }
 }
 }

 void debugVision() {
 if (this == IsoPlayer.getInstance()) {
 float float0 = LightingJNI.calculateVisionCone(this);
 LineDrawer.drawDotLines(
 this->x, this->y, this->z, GameTime.getInstance().getViewDist(), this->getLookAngleRadians(), -float0, 1.0F, 1.0F, 1.0F, 0.5F, 1
 );
 LineDrawer.drawArc(this->x, this->y, this->z, GameTime.getInstance().getViewDist(), this->getLookAngleRadians(), -float0, 16, 1.0F, 1.0F, 1.0F, 0.5F);
 float float1 = 3.5F - this->stats.getFatigue();
 LineDrawer.drawArc(this->x, this->y, this->z, float1, this->getLookAngleRadians(), -1.0F, 32, 1.0F, 1.0F, 1.0F, 0.5F);
 }
 }

 void setDefaultState() {
 this->stateMachine.changeState(this->defaultState, nullptr);
 }

 void SetOnFire() {
 if (!this->OnFire) {
 this->setOnFire(true);
 float float0 = Core.TileScale;
 this->AttachAnim(
 "Fire",
 "01",
 4,
 IsoFireManager.FireAnimDelay,
 (int)(-(this->offsetX + 1.0F * float0) + (8 - Rand.Next(16),
 (int)(-(this->offsetY + -89.0F * float0) + (int)((10 + Rand.Next(20) * float0),
 true,
 0,
 false,
 0.7F,
 IsoFireManager.FireTintMod
 );
 IsoFireManager.AddBurningCharacter(this);
 int int0 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Hand_L), BodyPartType.ToIndex(BodyPartType.MAX);
 if (this instanceof IsoPlayer) {
 this->getBodyDamage().getBodyParts().get(int0).setBurned();
 }

 if (float0 == 2.0F) {
 int int1 = this->AttachedAnimSprite.size() - 1;
 this->AttachedAnimSprite.get(int1).setScale(float0, float0);
 }

 if (!this->getEmitter().isPlaying("BurningFlesh")) {
 this->getEmitter().playSoundImpl("BurningFlesh", this);
 }
 }
 }

 void StopBurning() {
 if (this->OnFire) {
 IsoFireManager.RemoveBurningCharacter(this);
 this->setOnFire(false);
 if (this->AttachedAnimSprite != nullptr) {
 this->AttachedAnimSprite.clear();
 }

 this->getEmitter().stopOrTriggerSoundByName("BurningFlesh");
 }
 }

 void sendStopBurning() {
 if (GameClient.bClient) {
 if (this instanceof IsoPlayer player) {
 if (player.isLocalPlayer()) {
 this->StopBurning();
 } else {
 GameClient.sendStopFire(player);
 }
 }

 if (this->isZombie()) {
 IsoZombie zombie0 = (IsoZombie)this;
 GameClient.sendStopFire(zombie0);
 }
 }
 }

 void SpreadFireMP() {
 if (this->OnFire && GameServer.bServer && SandboxOptions.instance.FireSpread.getValue()) {
 IsoGridSquare square = ServerMap.instance.getGridSquare((int)this->x, (int)this->y, (int)this->z);
 if (square != nullptr && !square.getProperties().Is(IsoFlagType.burning) && Rand.Next(Rand.AdjustForFramerate(3000) < this->FireSpreadProbability) {
 IsoFireManager.StartFire(this->getCell(), square, false, 80);
 }
 }
 }

 void SpreadFire() {
 if (this->OnFire && !GameServer.bServer && !GameClient.bClient && SandboxOptions.instance.FireSpread.getValue()) {
 if (this->square != nullptr
 && !this->square.getProperties().Is(IsoFlagType.burning)
 && Rand.Next(Rand.AdjustForFramerate(3000) < this->FireSpreadProbability) {
 IsoFireManager.StartFire(this->getCell(), this->square, false, 80);
 }
 }
 }

 void Throw(HandWeapon weapon) {
 if (this instanceof IsoPlayer && ((IsoPlayer)this).getJoypadBind() != -1) {
 Vector2 vector = tempo.set(this->m_forwardDirection);
 vector.setLength(weapon.getMaxRange());
 this->attackTargetSquare = this->getCell()
 .getGridSquare((double)(this->getX() + vector.getX()), (double)(this->getY() + vector.getY()), (double)this->getZ());
 if (this->attackTargetSquare.empty()) {
 this->attackTargetSquare = this->getCell().getGridSquare((double)(this->getX() + vector.getX()), (double)(this->getY() + vector.getY()), 0.0);
 }
 }

 float float0 = this->attackTargetSquare.getX() - this->getX();
 if (float0 > 0.0F) {
 if (this->attackTargetSquare.getX() - this->getX() > weapon.getMaxRange()) {
 float0 = weapon.getMaxRange();
 }
 } else if (this->attackTargetSquare.getX() - this->getX() < -weapon.getMaxRange()) {
 float0 = -weapon.getMaxRange();
 }

 float float1 = this->attackTargetSquare.getY() - this->getY();
 if (float1 > 0.0F) {
 if (this->attackTargetSquare.getY() - this->getY() > weapon.getMaxRange()) {
 float1 = weapon.getMaxRange();
 }
 } else if (this->attackTargetSquare.getY() - this->getY() < -weapon.getMaxRange()) {
 float1 = -weapon.getMaxRange();
 }

 if (weapon.getPhysicsObject() == "Ball")) {
 new IsoBall();
 } else {
 new IsoMolotovCocktail();
 }

 if (this instanceof IsoPlayer) {
 ((IsoPlayer)this).setAttackAnimThrowTimer(0L);
 }
 }

 void serverRemoveItemFromZombie(const std::string& item) {
 if (GameServer.bServer) {
 IsoZombie zombie0 = Type.tryCastTo(this, IsoZombie.class);
 this->getItemVisuals(tempItemVisuals);

 for (int int0 = 0; int0 < tempItemVisuals.size(); int0++) {
 ItemVisual itemVisual = tempItemVisuals.get(int0);
 Item _item = itemVisual.getScriptItem();
 if (_item != nullptr && _item.name == item) {
 tempItemVisuals.remove(int0--);
 zombie0.itemVisuals.clear();
 zombie0.itemVisuals.addAll(tempItemVisuals);
 }
 }
 }
 }

 bool helmetFall(bool hitHead) {
 return this->helmetFall(hitHead, nullptr);
 }

 bool helmetFall(bool hitHead, const std::string& forcedItem) {
 IsoPlayer player = Type.tryCastTo(this, IsoPlayer.class);
 bool boolean0 = false;
 InventoryItem item0 = nullptr;
 IsoZombie zombie0 = Type.tryCastTo(this, IsoZombie.class);
 if (zombie0 != nullptr && !zombie0.isUsingWornItems()) {
 this->getItemVisuals(tempItemVisuals);

 for (int int0 = 0; int0 < tempItemVisuals.size(); int0++) {
 ItemVisual itemVisual = tempItemVisuals.get(int0);
 Item item1 = itemVisual.getScriptItem();
 if (item1 != nullptr && item1.getType() == Item.Type.Clothing && item1.getChanceToFall() > 0) {
 int int1 = item1.getChanceToFall();
 if (hitHead) {
 int1 += 40;
 }

 if (item1.name == forcedItem) {
 int1 = 100;
 }

 if (Rand.Next(100) > int1) {
 InventoryItem item2 = InventoryItemFactory.CreateItem(item1.getFullName());
 if (item2 != nullptr) {
 if (item2.getVisual() != nullptr) {
 item2.getVisual().copyFrom(itemVisual);
 item2.synchWithVisual();
 }

 IsoFallingClothing fallingClothing0 = new IsoFallingClothing(
 this->getCell(), this->getX(), this->getY(), PZMath.min(this->getZ() + 0.4F, (int)this->getZ() + 0.95F), 0.2F, 0.2F, item2
 );
 if (!StringUtils.isNullOrEmpty(forcedItem) {
 fallingClothing0.addWorldItem = false;
 }

 tempItemVisuals.remove(int0--);
 zombie0.itemVisuals.clear();
 zombie0.itemVisuals.addAll(tempItemVisuals);
 this->resetModelNextFrame();
 this->onWornItemsChanged();
 boolean0 = true;
 item0 = item2;
 }
 }
 }
 }
 } else if (this->getWornItems() != nullptr && !this->getWornItems().empty()) {
 for (int int2 = 0; int2 < this->getWornItems().size(); int2++) {
 WornItem wornItem = this->getWornItems().get(int2);
 InventoryItem item3 = wornItem.getItem();
 std::string string = wornItem.getLocation();
 if (item3 instanceof Clothing) {
 int int3 = ((Clothing)item3).getChanceToFall();
 if (hitHead) {
 int3 += 40;
 }

 if (item3.getType() == forcedItem) {
 int3 = 100;
 }

 if (((Clothing)item3).getChanceToFall() > 0 && Rand.Next(100) <= int3) {
 IsoFallingClothing fallingClothing1 = new IsoFallingClothing(
 this->getCell(),
 this->getX(),
 this->getY(),
 PZMath.min(this->getZ() + 0.4F, (int)this->getZ() + 0.95F),
 Rand.Next(-0.2F, 0.2F),
 Rand.Next(-0.2F, 0.2F),
 item3
 );
 if (!StringUtils.isNullOrEmpty(forcedItem) {
 fallingClothing1.addWorldItem = false;
 }

 this->getInventory().Remove(item3);
 this->getWornItems().remove(item3);
 item0 = item3;
 this->resetModelNextFrame();
 this->onWornItemsChanged();
 boolean0 = true;
 if (GameClient.bClient && player != nullptr && player.isLocalPlayer() && StringUtils.isNullOrEmpty(forcedItem) {
 GameClient.instance.sendClothing(player, string, nullptr);
 }
 }
 }
 }
 }

 if (boolean0 && GameClient.bClient && StringUtils.isNullOrEmpty(forcedItem) && IsoPlayer.getInstance().isLocalPlayer()) {
 GameClient.sendZombieHelmetFall(IsoPlayer.getInstance(), this, item0);
 }

 if (boolean0 && player != nullptr && player.isLocalPlayer()) {
 LuaEventManager.triggerEvent("OnClothingUpdated", this);
 }

 if (boolean0 && this->isZombie()) {
 PersistentOutfits.instance.setFallenHat(this, true);
 }

 return boolean0;
 }

 void smashCarWindow(VehiclePart part) {
 std::unordered_map hashMap = this->getStateMachineParams(SmashWindowState.instance());
 hashMap.clear();
 hashMap.put(0, part.getWindow());
 hashMap.put(1, part.getVehicle());
 hashMap.put(2, part);
 this->actionContext.reportEvent("EventSmashWindow");
 }

 void smashWindow(IsoWindow w) {
 if (!w.isInvincible()) {
 std::unordered_map hashMap = this->getStateMachineParams(SmashWindowState.instance());
 hashMap.clear();
 hashMap.put(0, w);
 this->actionContext.reportEvent("EventSmashWindow");
 }
 }

 void openWindow(IsoWindow w) {
 if (!w.isInvincible()) {
 OpenWindowState.instance().setParams(this, w);
 this->actionContext.reportEvent("EventOpenWindow");
 }
 }

 void closeWindow(IsoWindow w) {
 if (!w.isInvincible()) {
 std::unordered_map hashMap = this->getStateMachineParams(CloseWindowState.instance());
 hashMap.clear();
 hashMap.put(0, w);
 this->actionContext.reportEvent("EventCloseWindow");
 }
 }

 void climbThroughWindow(IsoWindow w) {
 if (w.canClimbThrough(this) {
 float float0 = this->x - (int)this->x;
 float float1 = this->y - (int)this->y;
 uint8_t byte0 = 0;
 uint8_t byte1 = 0;
 if (w.getX() > this->x && !w.north) {
 byte0 = -1;
 }

 if (w.getY() > this->y && w.north) {
 byte1 = -1;
 }

 this->x = w.getX() + float0 + byte0;
 this->y = w.getY() + float1 + byte1;
 ClimbThroughWindowState.instance().setParams(this, w);
 this->actionContext.reportEvent("EventClimbWindow");
 }
 }

 void climbThroughWindow(IsoWindow w, int startingFrame) {
 if (w.canClimbThrough(this) {
 ClimbThroughWindowState.instance().setParams(this, w);
 this->actionContext.reportEvent("EventClimbWindow");
 }
 }

 bool isClosingWindow(IsoWindow window) {
 if (window.empty()) {
 return false;
 } else {
 return !this->isCurrentState(CloseWindowState.instance()) ? false : CloseWindowState.instance().getWindow(this) == window;
 }
 }

 bool isClimbingThroughWindow(IsoWindow window) {
 if (window.empty()) {
 return false;
 } else if (!this->isCurrentState(ClimbThroughWindowState.instance())) {
 return false;
 } else {
 return !this->getVariableBoolean("BlockWindow") ? false : ClimbThroughWindowState.instance().getWindow(this) == window;
 }
 }

 void climbThroughWindowFrame(IsoObject obj) {
 if (IsoWindowFrame.canClimbThrough(obj, this) {
 ClimbThroughWindowState.instance().setParams(this, obj);
 this->actionContext.reportEvent("EventClimbWindow");
 }
 }

 void climbSheetRope() {
 if (this->canClimbSheetRope(this->current) {
 std::unordered_map hashMap = this->getStateMachineParams(ClimbSheetRopeState.instance());
 hashMap.clear();
 this->actionContext.reportEvent("EventClimbRope");
 }
 }

 void climbDownSheetRope() {
 if (this->canClimbDownSheetRope(this->current) {
 this->dropHeavyItems();
 std::unordered_map hashMap = this->getStateMachineParams(ClimbDownSheetRopeState.instance());
 hashMap.clear();
 this->actionContext.reportEvent("EventClimbDownRope");
 }
 }

 bool canClimbSheetRope(IsoGridSquare sq) {
 if (sq.empty()) {
 return false;
 } else {
 int int0 = sq.getZ();

 while (sq != nullptr) {
 if (!IsoWindow.isSheetRopeHere(sq) {
 return false;
 }

 if (!IsoWindow.canClimbHere(sq) {
 return false;
 }

 if (sq.TreatAsSolidFloor() && sq.getZ() > int0) {
 return false;
 }

 if (IsoWindow.isTopOfSheetRopeHere(sq) {
 return true;
 }

 sq = this->getCell().getGridSquare(sq.getX(), sq.getY(), sq.getZ() + 1);
 }

 return false;
 }
 }

 bool canClimbDownSheetRopeInCurrentSquare() {
 return this->canClimbDownSheetRope(this->current);
 }

 bool canClimbDownSheetRope(IsoGridSquare sq) {
 if (sq.empty()) {
 return false;
 } else {
 int int0 = sq.getZ();

 while (sq != nullptr) {
 if (!IsoWindow.isSheetRopeHere(sq) {
 return false;
 }

 if (!IsoWindow.canClimbHere(sq) {
 return false;
 }

 if (sq.TreatAsSolidFloor()) {
 return sq.getZ() < int0;
 }

 sq = this->getCell().getGridSquare(sq.getX(), sq.getY(), sq.getZ() - 1);
 }

 return false;
 }
 }

 void climbThroughWindow(IsoThumpable w) {
 if (w.canClimbThrough(this) {
 float float0 = this->x - (int)this->x;
 float float1 = this->y - (int)this->y;
 uint8_t byte0 = 0;
 uint8_t byte1 = 0;
 if (w.getX() > this->x && !w.north) {
 byte0 = -1;
 }

 if (w.getY() > this->y && w.north) {
 byte1 = -1;
 }

 this->x = w.getX() + float0 + byte0;
 this->y = w.getY() + float1 + byte1;
 ClimbThroughWindowState.instance().setParams(this, w);
 this->actionContext.reportEvent("EventClimbWindow");
 }
 }

 void climbThroughWindow(IsoThumpable w, int startingFrame) {
 if (w.canClimbThrough(this) {
 ClimbThroughWindowState.instance().setParams(this, w);
 this->actionContext.reportEvent("EventClimbWindow");
 }
 }

 void climbOverFence(IsoDirections dir) {
 if (this->current != nullptr) {
 IsoGridSquare square = this->current.nav[dir.index()];
 if (IsoWindow.canClimbThroughHelper(this, this->current, square, dir == IsoDirections.N || dir == IsoDirections.S) {
 ClimbOverFenceState.instance().setParams(this, dir);
 this->actionContext.reportEvent("EventClimbFence");
 }
 }
 }

 bool isAboveTopOfStairs() {
 if (this->z != 0.0F && !(this->z - (int)this->z > 0.01) && (this->current.empty() || !this->current.TreatAsSolidFloor())) {
 IsoGridSquare square = this->getCell().getGridSquare((double)this->x, (double)this->y, (double)(this->z - 1.0F);
 return square != nullptr && (square.Has(IsoObjectType.stairsTN) || square.Has(IsoObjectType.stairsTW);
 } else {
 return false;
 }
 }

 void preupdate() {
 super.preupdate();
 if (!this->m_bDebugVariablesRegistered && DebugOptions.instance.Character.Debug.RegisterDebugVariables.getValue()) {
 this->registerDebugGameVariables();
 }

 this->updateAnimationRecorderState();
 if (this->isAnimationRecorderActive()) {
 int int0 = IsoWorld.instance.getFrameNo();
 this->m_animationRecorder.beginLine(int0);
 }

 if (GameServer.bServer) {
 this->getXp().update();
 }
 }

 void setTeleport(NetworkTeleport _teleport) {
 this->teleport = _teleport;
 }

 NetworkTeleport getTeleport() {
 return this->teleport;
 }

 bool isTeleporting() {
 return this->teleport != nullptr;
 }

 void update() {
 IsoGameCharacter.s_performance.update.invokeAndMeasure(this, IsoGameCharacter::updateInternal);
 }

 void updateInternal() {
 if (this->current != nullptr) {
 if (this->teleport != nullptr) {
 this->teleport.process(IsoPlayer.getPlayerIndex());
 }

 this->updateAlpha();
 if (this->isNPC) {
 if (this->GameCharacterAIBrain.empty()) {
 this->GameCharacterAIBrain = new GameCharacterAIBrain(this);
 }

 this->GameCharacterAIBrain.update();
 }

 if (this->sprite != nullptr) {
 this->legsSprite = this->sprite;
 }

 if (!this->isDead() || this->current != nullptr && this->current.getMovingObjects().contains(this) {
 if (!GameClient.bClient
 && !this->m_invisible
 && this->getCurrentSquare().getTrapPositionX() > -1
 && this->getCurrentSquare().getTrapPositionY() > -1
 && this->getCurrentSquare().getTrapPositionZ() > -1) {
 this->getCurrentSquare().explodeTrap();
 }

 if (this->getBodyDamage() != nullptr && this->getCurrentBuilding() != nullptr && this->getCurrentBuilding().isToxic()) {
 float float0 = GameTime.getInstance().getMultiplier() / 1.6F;
 if (this->getStats().getFatigue() < 1.0F) {
 this->getStats().setFatigue(this->getStats().getFatigue() + 1.0E-4F * float0);
 }

 if (this->getStats().getFatigue() > 0.8) {
 this->getBodyDamage().getBodyPart(BodyPartType.Head).ReduceHealth(0.1F * float0);
 }

 this->getBodyDamage().getBodyPart(BodyPartType.Torso_Upper).ReduceHealth(0.1F * float0);
 }

 if (this->lungeFallTimer > 0.0F) {
 this->lungeFallTimer = this->lungeFallTimer - GameTime.getInstance().getMultiplier() / 1.6F;
 }

 if (this->getMeleeDelay() > 0.0F) {
 this->setMeleeDelay(this->getMeleeDelay() - 0.625F * GameTime.getInstance().getMultiplier());
 }

 if (this->getRecoilDelay() > 0.0F) {
 this->setRecoilDelay(this->getRecoilDelay() - 0.625F * GameTime.getInstance().getMultiplier());
 }

 this->sx = 0.0F;
 this->sy = 0.0F;
 if (this->current.getRoom() != nullptr
 && this->current.getRoom().building.def.bAlarmed
 && (!this->isZombie() || Core.bTutorial)
 && !GameClient.bClient) {
 bool boolean0 = false;
 if (this instanceof IsoPlayer && (((IsoPlayer)this).isInvisible() || ((IsoPlayer)this).isGhostMode())) {
 boolean0 = true;
 }

 if (!boolean0) {
 AmbientStreamManager.instance.doAlarm(this->current.getRoom().def);
 }
 }

 this->updateSeenVisibility();
 this->llx = this->getLx();
 this->lly = this->getLy();
 this->setLx(this->getX());
 this->setLy(this->getY());
 this->setLz(this->getZ());
 this->updateBeardAndHair();
 this->updateFalling();
 if (this->descriptor != nullptr) {
 this->descriptor.Instance = this;
 }

 if (!this->isZombie()) {
 if (this->Traits.Agoraphobic.isSet() && !this->getCurrentSquare().isInARoom()) {
 this->stats.Panic = this->stats.Panic + 0.5F * (GameTime.getInstance().getMultiplier() / 1.6F);
 }

 if (this->Traits.Claustophobic.isSet() && this->getCurrentSquare().isInARoom()) {
 int int0 = this->getCurrentSquare().getRoomSize();
 if (int0 > 0) {
 float float1 = 1.0F;
 float1 = 1.0F - int0 / 70.0F;
 if (float1 < 0.0F) {
 float1 = 0.0F;
 }

 float float2 = 0.6F * float1 * (GameTime.getInstance().getMultiplier() / 1.6F);
 if (float2 > 0.6F) {
 float2 = 0.6F;
 }

 this->stats.Panic += float2;
 }
 }

 if (this->Moodles != nullptr) {
 this->Moodles.Update();
 }

 if (this->Asleep) {
 this->BetaEffect = 0.0F;
 this->SleepingTabletEffect = 0.0F;
 this->StopAllActionQueue();
 }

 if (this->BetaEffect > 0.0F) {
 this->BetaEffect = this->BetaEffect - GameTime.getInstance().getMultiplier() / 1.6F;
 this->stats.Panic = this->stats.Panic - 0.6F * (GameTime.getInstance().getMultiplier() / 1.6F);
 if (this->stats.Panic < 0.0F) {
 this->stats.Panic = 0.0F;
 }
 } else {
 this->BetaDelta = 0.0F;
 }

 if (this->DepressFirstTakeTime > 0.0F || this->DepressEffect > 0.0F) {
 this->DepressFirstTakeTime = this->DepressFirstTakeTime - GameTime.getInstance().getMultiplier() / 1.6F;
 if (this->DepressFirstTakeTime < 0.0F) {
 this->DepressFirstTakeTime = -1.0F;
 this->DepressEffect = this->DepressEffect - GameTime.getInstance().getMultiplier() / 1.6F;
 this->getBodyDamage()
 .setUnhappynessLevel(this->getBodyDamage().getUnhappynessLevel() - 0.03F * (GameTime.getInstance().getMultiplier() / 1.6F);
 if (this->getBodyDamage().getUnhappynessLevel() < 0.0F) {
 this->getBodyDamage().setUnhappynessLevel(0.0F);
 }
 }
 }

 if (this->DepressEffect < 0.0F) {
 this->DepressEffect = 0.0F;
 }

 if (this->SleepingTabletEffect > 0.0F) {
 this->SleepingTabletEffect = this->SleepingTabletEffect - GameTime.getInstance().getMultiplier() / 1.6F;
 this->stats.fatigue = this->stats.fatigue + 0.0016666667F * this->SleepingTabletDelta * (GameTime.getInstance().getMultiplier() / 1.6F);
 } else {
 this->SleepingTabletDelta = 0.0F;
 }

 int int1 = this->Moodles.getMoodleLevel(MoodleType.Panic);
 if (int1 == 2) {
 this->stats.Sanity -= 3.2E-7F;
 } else if (int1 == 3) {
 this->stats.Sanity -= 4.8000004E-7F;
 } else if (int1 == 4) {
 this->stats.Sanity -= 8.0E-7F;
 } else if (int1 == 0) {
 this->stats.Sanity += 1.0E-7F;
 }

 int int2 = this->Moodles.getMoodleLevel(MoodleType.Tired);
 if (int2 == 4) {
 this->stats.Sanity -= 2.0E-6F;
 }

 if (this->stats.Sanity < 0.0F) {
 this->stats.Sanity = 0.0F;
 }

 if (this->stats.Sanity > 1.0F) {
 this->stats.Sanity = 1.0F;
 }
 }

 if (!this->CharacterActions.empty()) {
 BaseAction baseAction = this->CharacterActions.get(0);
 bool boolean1 = baseAction.valid();
 if (boolean1 && !baseAction.bStarted) {
 baseAction.waitToStart();
 } else if (boolean1 && !baseAction.finished() && !baseAction.forceComplete && !baseAction.forceStop) {
 baseAction.update();
 }

 if (!boolean1 || baseAction.finished() || baseAction.forceComplete || baseAction.forceStop) {
 if (baseAction.finished() || baseAction.forceComplete) {
 baseAction.perform();
 boolean1 = true;
 }

 if (baseAction.finished() && !baseAction.loopAction || baseAction.forceComplete || baseAction.forceStop || !boolean1) {
 if (baseAction.bStarted && (baseAction.forceStop || !boolean1) {
 baseAction.stop();
 }

 this->CharacterActions.removeElement(baseAction);
 if (this == IsoPlayer.players[0] || this == IsoPlayer.players[1] || this == IsoPlayer.players[2] || this == IsoPlayer.players[3]) {
 UIManager.getProgressBar(((IsoPlayer)this).getPlayerNum()).setValue(0.0F);
 }
 }
 }

 for (int int3 = 0; int3 < this->EnemyList.size(); int3++) {
 IsoGameCharacter character1 = this->EnemyList.get(int3);
 if (character1.isDead()) {
 this->EnemyList.remove(character1);
 int3--;
 }
 }
 }

 if (SystemDisabler.doCharacterStats && this->BodyDamage != nullptr) {
 this->BodyDamage.Update();
 this->updateBandages();
 }

 if (this == IsoPlayer.getInstance()) {
 if (this->leftHandItem != nullptr && this->leftHandItem.getUses() <= 0) {
 this->leftHandItem = nullptr;
 }

 if (this->rightHandItem != nullptr && this->rightHandItem.getUses() <= 0) {
 this->rightHandItem = nullptr;
 }
 }

 if (SystemDisabler.doCharacterStats) {
 this->calculateStats();
 }

 this->moveForwardVec.x = 0.0F;
 this->moveForwardVec.y = 0.0F;
 if (!this->Asleep || !(this instanceof IsoPlayer) {
 this->setLx(this->getX());
 this->setLy(this->getY());
 this->setLz(this->getZ());
 this->square = this->getCurrentSquare();
 if (this->sprite != nullptr) {
 if (!this->bUseParts) {
 this->sprite.update(this->def);
 } else {
 this->legsSprite.update(this->def);
 }
 }

 this->setStateEventDelayTimer(this->getStateEventDelayTimer() - GameTime.getInstance().getMultiplier() / 1.6F);
 }

 this->stateMachine.update();
 if (this->isZombie() && VirtualZombieManager.instance.isReused((IsoZombie)this) {
 DebugLog.log(DebugType.Zombie, "Zombie added to ReusableZombies after stateMachine.update - RETURNING " + this);
 } else {
 if (this instanceof IsoPlayer) {
 this->ensureOnTile();
 }

 if ((this instanceof IsoPlayer || this instanceof IsoSurvivor)
 && this->RemoteID == -1
 && this instanceof IsoPlayer
 && ((IsoPlayer)this).isLocalPlayer()) {
 RainManager.SetPlayerLocation(((IsoPlayer)this).getPlayerNum(), this->getCurrentSquare());
 }

 this->FireCheck();
 this->SpreadFire();
 this->ReduceHealthWhenBurning();
 this->updateTextObjects();
 if (this->stateMachine.getCurrent() == StaggerBackState.instance()) {
 if (this->getStateEventDelayTimer() > 20.0F) {
 this->BloodImpactX = this->getX();
 this->BloodImpactY = this->getY();
 this->BloodImpactZ = this->getZ();
 }
 } else {
 this->BloodImpactX = this->getX();
 this->BloodImpactY = this->getY();
 this->BloodImpactZ = this->getZ();
 }

 if (!this->isZombie()) {
 this->recursiveItemUpdater(this->inventory);
 }

 this->LastZombieKills = this->ZombieKills;
 if (this->AttachedAnimSprite != nullptr) {
 int int4 = this->AttachedAnimSprite.size();

 for (int int5 = 0; int5 < int4; int5++) {
 IsoSpriteInstance spriteInstance = this->AttachedAnimSprite.get(int5);
 IsoSprite sprite = spriteInstance.parentSprite;
 spriteInstance.update();
 spriteInstance.Frame = spriteInstance.Frame
 + spriteInstance.AnimFrameIncrease * (GameTime.instance.getMultipliedSecondsSinceLastUpdate() * 60.0F);
 if ((int)spriteInstance.Frame >= sprite.CurrentAnim.Frames.size() && sprite.Loop && spriteInstance.Looped) {
 spriteInstance.Frame = 0.0F;
 }
 }
 }

 if (this->isGodMod()) {
 this->getStats().setFatigue(0.0F);
 this->getStats().setEndurance(1.0F);
 this->getBodyDamage().setTemperature(37.0F);
 this->getStats().setHunger(0.0F);
 }

 this->updateMovementMomentum();
 if (this->effectiveEdibleBuffTimer > 0.0F) {
 this->effectiveEdibleBuffTimer = this->effectiveEdibleBuffTimer - GameTime.getInstance().getMultiplier() * 0.015F;
 if (this->effectiveEdibleBuffTimer < 0.0F) {
 this->effectiveEdibleBuffTimer = 0.0F;
 }
 }

 if (!GameServer.bServer || GameClient.bClient) {
 this->updateDirt();
 }
 }
 }
 }
 }

 void updateSeenVisibility() {
 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 this->updateSeenVisibility(int0);
 }
 }

 void updateSeenVisibility(int int0) {
 IsoPlayer player = IsoPlayer.players[int0];
 if (player != nullptr) {
 this->IsVisibleToPlayer[int0] = this->TestIfSeen(int0);
 if (!this->IsVisibleToPlayer[int0]) {
 if (!(this instanceof IsoPlayer) {
 if (!player.isSeeEveryone()) {
 this->setTargetAlpha(int0, 0.0F);
 }
 }
 }
 }
 }

 void recursiveItemUpdater(ItemContainer container) {
 for (int int0 = 0; int0 < container.Items.size(); int0++) {
 InventoryItem item = container.Items.get(int0);
 if (item instanceof InventoryContainer) {
 this->recursiveItemUpdater((InventoryContainer)item);
 }

 if (item instanceof IUpdater) {
 item.update();
 }
 }
 }

 void recursiveItemUpdater(InventoryContainer inventoryContainer) {
 for (int int0 = 0; int0 < inventoryContainer.getInventory().getItems().size(); int0++) {
 InventoryItem item = inventoryContainer.getInventory().getItems().get(int0);
 if (item instanceof InventoryContainer) {
 this->recursiveItemUpdater((InventoryContainer)item);
 }

 if (item instanceof IUpdater) {
 item.update();
 }
 }
 }

 void updateDirt() {
 if (!this->isZombie() && this->getBodyDamage() != nullptr) {
 int int0 = 0;
 if (this->isRunning() && Rand.NextBool(Rand.AdjustForFramerate(3500) {
 int0 = 1;
 }

 if (this->isSprinting() && Rand.NextBool(Rand.AdjustForFramerate(2500) {
 int0 += Rand.Next(1, 3);
 }

 if (this->getBodyDamage().getTemperature() > 37.0F && Rand.NextBool(Rand.AdjustForFramerate(5000) {
 int0++;
 }

 if (this->getBodyDamage().getTemperature() > 38.0F && Rand.NextBool(Rand.AdjustForFramerate(3000) {
 int0++;
 }

 float float0 = this->square.empty() ? 0.0F : this->square.getPuddlesInGround();
 if (this->isMoving() && float0 > 0.09F && Rand.NextBool(Rand.AdjustForFramerate(1500) {
 int0++;
 }

 if (int0 > 0) {
 this->addDirt(nullptr, int0, true);
 }

 IsoPlayer player = Type.tryCastTo(this, IsoPlayer.class);
 if (player != nullptr && player.isPlayerMoving() || player.empty() && this->isMoving()) {
 int0 = 0;
 if (float0 > 0.09F && Rand.NextBool(Rand.AdjustForFramerate(1500) {
 int0++;
 }

 if (this->isInTrees() && Rand.NextBool(Rand.AdjustForFramerate(1500) {
 int0++;
 }

 if (int0 > 0) {
 this->addDirt(nullptr, int0, false);
 }
 }
 }
 }

 void updateMovementMomentum() {
 float float0 = GameTime.instance.getTimeDelta();
 if (this->isPlayerMoving() && !this->isAiming()) {
 float float1 = this->m_momentumScalar * 0.55F;
 if (float1 >= 0.55F) {
 this->m_momentumScalar = 1.0F;
 return;
 }

 float float2 = float1 + float0;
 float float3 = float2 / 0.55F;
 this->m_momentumScalar = PZMath.clamp(float3, 0.0F, 1.0F);
 } else {
 float float4 = (1.0F - this->m_momentumScalar) * 0.25F;
 if (float4 >= 0.25F) {
 this->m_momentumScalar = 0.0F;
 return;
 }

 float float5 = float4 + float0;
 float float6 = float5 / 0.25F;
 float float7 = PZMath.clamp(float6, 0.0F, 1.0F);
 this->m_momentumScalar = 1.0F - float7;
 }
 }

 double getHoursSurvived() {
 return GameTime.instance.getWorldAgeHours();
 }

 void updateBeardAndHair() {
 if (!this->isZombie()) {
 if (!(this instanceof IsoPlayer) || ((IsoPlayer)this).isLocalPlayer()) {
 float float0 = (float)this->getHoursSurvived();
 if (this->beardGrowTiming < 0.0F || this->beardGrowTiming > float0) {
 this->beardGrowTiming = float0;
 }

 if (this->hairGrowTiming < 0.0F || this->hairGrowTiming > float0) {
 this->hairGrowTiming = float0;
 }

 boolean boolean0 = !GameClient.bClient && !GameServer.bServer
 || ServerOptions.instance.SleepAllowed.getValue() && ServerOptions.instance.SleepNeeded.getValue();
 bool boolean1 = false;
 if ((this->isAsleep() || !boolean0) && float0 - this->beardGrowTiming > 120.0F) {
 this->beardGrowTiming = float0;
 BeardStyle beardStyle = BeardStyles.instance.FindStyle(((HumanVisual)this->getVisual()).getBeardModel());
 int int0 = 1;
 if (beardStyle != nullptr) {
 int0 = beardStyle.level;
 }

 std::vector arrayList0 = BeardStyles.instance.getAllStyles();

 for (int int1 = 0; int1 < arrayList0.size(); int1++) {
 if (((BeardStyle)arrayList0.get(int1).growReference && ((BeardStyle)arrayList0.get(int1).level == int0 + 1) {
 ((HumanVisual)this->getVisual()).setBeardModel(((BeardStyle)arrayList0.get(int1).name);
 boolean1 = true;
 break;
 }
 }
 }

 if ((this->isAsleep() || !boolean0) && float0 - this->hairGrowTiming > 480.0F) {
 this->hairGrowTiming = float0;
 HairStyle hairStyle0 = HairStyles.instance.FindMaleStyle(((HumanVisual)this->getVisual()).getHairModel());
 if (this->isFemale()) {
 hairStyle0 = HairStyles.instance.FindFemaleStyle(((HumanVisual)this->getVisual()).getHairModel());
 }

 int int2 = 1;
 if (hairStyle0 != nullptr) {
 int2 = hairStyle0.level;
 }

 std::vector arrayList1 = HairStyles.instance.m_MaleStyles;
 if (this->isFemale()) {
 arrayList1 = HairStyles.instance.m_FemaleStyles;
 }

 for (int int3 = 0; int3 < arrayList1.size(); int3++) {
 HairStyle hairStyle1 = (HairStyle)arrayList1.get(int3);
 if (hairStyle1.growReference && hairStyle1.level == int2 + 1) {
 ((HumanVisual)this->getVisual()).setHairModel(hairStyle1.name);
 ((HumanVisual)this->getVisual()).setNonAttachedHair(nullptr);
 boolean1 = true;
 break;
 }
 }
 }

 if (boolean1) {
 this->resetModelNextFrame();
 LuaEventManager.triggerEvent("OnClothingUpdated", this);
 if (GameClient.bClient) {
 GameClient.instance.sendVisual((IsoPlayer)this);
 }
 }
 }
 }
 }

 void updateFalling() {
 if (this instanceof IsoPlayer && !this->isClimbing()) {
 IsoRoofFixer.FixRoofsAt(this->current);
 }

 if (this->isSeatedInVehicle()) {
 this->fallTime = 0.0F;
 this->lastFallSpeed = 0.0F;
 this->bFalling = false;
 this->wasOnStairs = false;
 } else {
 if (this->z > 0.0F) {
 IsoDirections directions = IsoDirections.Max;
 if (!this->isZombie() && this->isClimbing()) {
 if (this->current.Is(IsoFlagType.climbSheetW) || this->current.Is(IsoFlagType.climbSheetTopW) {
 directions = IsoDirections.W;
 }

 if (this->current.Is(IsoFlagType.climbSheetE) || this->current.Is(IsoFlagType.climbSheetTopE) {
 directions = IsoDirections.E;
 }

 if (this->current.Is(IsoFlagType.climbSheetN) || this->current.Is(IsoFlagType.climbSheetTopN) {
 directions = IsoDirections.N;
 }

 if (this->current.Is(IsoFlagType.climbSheetS) || this->current.Is(IsoFlagType.climbSheetTopS) {
 directions = IsoDirections.S;
 }
 }

 float float0 = 0.125F * (GameTime.getInstance().getMultiplier() / 1.6F);
 if (this->bClimbing) {
 float0 = 0.0F;
 }

 if (this->getCurrentState() == ClimbOverFenceState.instance() || this->getCurrentState() == ClimbThroughWindowState.instance()) {
 this->fallTime = 0.0F;
 float0 = 0.0F;
 }

 this->lastFallSpeed = float0;
 if (!this->current.TreatAsSolidFloor()) {
 if (directions != IsoDirections.Max) {
 this->dir = directions;
 }

 float float1 = 6.0F * (GameTime.getInstance().getMultiplier() / 1.6F);
 float float2 = this->getHeightAboveFloor();
 if (float0 > float2) {
 float1 *= float2 / float0;
 }

 this->fallTime += float1;
 if (directions != IsoDirections.Max) {
 this->fallTime = 0.0F;
 }

 if (this->fallTime < 20.0F && float2 < 0.2F) {
 this->fallTime = 0.0F;
 }

 this->setZ(this->getZ() - float0);
 } else if (!(this->getZ() > (int)this->getZ()) && !(float0 < 0.0F) {
 this->DoLand();
 this->fallTime = 0.0F;
 this->bFalling = false;
 } else {
 if (directions != IsoDirections.Max) {
 this->dir = directions;
 }

 if (!this->current.HasStairs()) {
 if (!this->wasOnStairs) {
 float float3 = 6.0F * (GameTime.getInstance().getMultiplier() / 1.6F);
 float float4 = this->getHeightAboveFloor();
 if (float0 > float4) {
 float3 *= float4 / float0;
 }

 this->fallTime += float3;
 if (directions != IsoDirections.Max) {
 this->fallTime = 0.0F;
 }

 this->setZ(this->getZ() - float0);
 if (this->z < (int)this->llz) {
 this->z = (int)this->llz;
 this->DoLand();
 this->fallTime = 0.0F;
 this->bFalling = false;
 }
 } else {
 this->wasOnStairs = false;
 }
 } else {
 this->fallTime = 0.0F;
 this->bFalling = false;
 this->wasOnStairs = true;
 }
 }
 } else {
 this->DoLand();
 this->fallTime = 0.0F;
 this->bFalling = false;
 }

 this->llz = this->lz;
 }
 }

 float getHeightAboveFloor() {
 if (this->current.empty()) {
 return 1.0F;
 } else {
 if (this->current.HasStairs()) {
 float float0 = this->current.getApparentZ(this->x - (int)this->x, this->y - (int)this->y);
 if (this->getZ() >= float0) {
 return this->getZ() - float0;
 }
 }

 if (this->current.TreatAsSolidFloor()) {
 return this->getZ() - (int)this->getZ();
 } else if (this->current.z == 0) {
 return this->getZ();
 } else {
 IsoGridSquare square = this->getCell().getGridSquare(this->current.x, this->current.y, this->current.z - 1);
 if (square != nullptr && square.HasStairs()) {
 float float1 = square.getApparentZ(this->x - (int)this->x, this->y - (int)this->y);
 return this->getZ() - float1;
 } else {
 return 1.0F;
 }
 }
 }
 }

 void updateMovementRates() {
 }

 float calculateIdleSpeed() {
 float float0 = 0.01F;
 float0 = (float)(float0 + this->getMoodles().getMoodleLevel(MoodleType.Endurance) * 2.5 / 10.0);
 return float0 * GameTime.getAnimSpeedFix();
 }

 float calculateBaseSpeed() {
 float float0 = 0.8F;
 float float1 = 1.0F;
 if (this->getMoodles() != nullptr) {
 float0 -= this->getMoodles().getMoodleLevel(MoodleType.Endurance) * 0.15F;
 float0 -= this->getMoodles().getMoodleLevel(MoodleType.HeavyLoad) * 0.15F;
 }

 if (this->getMoodles().getMoodleLevel(MoodleType.Panic) >= 3 && this->Traits.AdrenalineJunkie.isSet()) {
 int int0 = this->getMoodles().getMoodleLevel(MoodleType.Panic) + 1;
 float0 += int0 / 20.0F;
 }

 for (int int1 = BodyPartType.ToIndex(BodyPartType.Torso_Upper); int1 < BodyPartType.ToIndex(BodyPartType.Neck) + 1; int1++) {
 BodyPart bodyPart0 = this->getBodyDamage().getBodyPart(BodyPartType.FromIndex(int1);
 if (bodyPart0.HasInjury()) {
 float0 -= 0.1F;
 }

 if (bodyPart0.bandaged()) {
 float0 += 0.05F;
 }
 }

 BodyPart bodyPart1 = this->getBodyDamage().getBodyPart(BodyPartType.UpperLeg_L);
 if (bodyPart1.getAdditionalPain(true) > 20.0F) {
 float0 -= (bodyPart1.getAdditionalPain(true) - 20.0F) / 100.0F;
 }

 for (int int2 = 0; int2 < this->bagsWorn.size(); int2++) {
 InventoryContainer inventoryContainer = this->bagsWorn.get(int2);
 float1 += this->calcRunSpeedModByBag(inventoryContainer);
 }

 if (this->getPrimaryHandItem() != nullptr && this->getPrimaryHandItem() instanceof InventoryContainer) {
 float1 += this->calcRunSpeedModByBag((InventoryContainer)this->getPrimaryHandItem());
 }

 if (this->getSecondaryHandItem() != nullptr && this->getSecondaryHandItem() instanceof InventoryContainer) {
 float1 += this->calcRunSpeedModByBag((InventoryContainer)this->getSecondaryHandItem());
 }

 this->fullSpeedMod = this->runSpeedModifier + (float1 - 1.0F);
 return float0 * (1.0F - Math.abs(1.0F - this->fullSpeedMod) / 2.0F);
 }

 float calcRunSpeedModByClothing() {
 float float0 = 0.0F;
 int int0 = 0;

 for (int int1 = 0; int1 < this->wornItems.size(); int1++) {
 InventoryItem item = this->wornItems.getItemByIndex(int1);
 if (item instanceof Clothing && ((Clothing)item).getRunSpeedModifier() != 1.0F) {
 float0 += ((Clothing)item).getRunSpeedModifier();
 int0++;
 }
 }

 if (float0 == 0.0F && int0 == 0) {
 float0 = 1.0F;
 int0 = 1;
 }

 if (this->getWornItem("Shoes") == nullptr) {
 float0 *= 0.8F;
 }

 return float0 / int0;
 }

 float calcRunSpeedModByBag(InventoryContainer inventoryContainer) {
 float float0 = inventoryContainer.getScriptItem().runSpeedModifier - 1.0F;
 float float1 = inventoryContainer.getContentsWeight() / inventoryContainer.getEffectiveCapacity(this);
 return float0 * (1.0F + float1 / 2.0F);
 }

 float calculateCombatSpeed() {
 bool boolean0 = true;
 float float0 = 1.0F;
 HandWeapon weapon = nullptr;
 if (this->getPrimaryHandItem() != nullptr && this->getPrimaryHandItem() instanceof HandWeapon) {
 weapon = (HandWeapon)this->getPrimaryHandItem();
 float0 *= ((HandWeapon)this->getPrimaryHandItem()).getBaseSpeed();
 }

 WeaponType weaponType = WeaponType.getWeaponType(this);
 if (weapon != nullptr && weapon.isTwoHandWeapon() && this->getSecondaryHandItem() != weapon) {
 float0 *= 0.77F;
 }

 if (weapon != nullptr && this->Traits.Axeman.isSet() && weapon.getCategories().contains("Axe")) {
 float0 *= this->getChopTreeSpeed();
 boolean0 = false;
 }

 float0 -= this->getMoodles().getMoodleLevel(MoodleType.Endurance) * 0.07F;
 float0 -= this->getMoodles().getMoodleLevel(MoodleType.HeavyLoad) * 0.07F;
 float0 += this->getWeaponLevel() * 0.03F;
 float0 += this->getPerkLevel(PerkFactory.Perks.Fitness) * 0.02F;
 if (this->getSecondaryHandItem() != nullptr && this->getSecondaryHandItem() instanceof InventoryContainer) {
 float0 *= 0.95F;
 }

 float0 *= Rand.Next(1.1F, 1.2F);
 float0 *= this->combatSpeedModifier;
 float0 *= this->getArmsInjurySpeedModifier();
 if (this->getBodyDamage() != nullptr && this->getBodyDamage().getThermoregulator() != nullptr) {
 float0 *= this->getBodyDamage().getThermoregulator().getCombatModifier();
 }

 float0 = Math.min(1.6F, float0);
 float0 = Math.max(0.8F, float0);
 if (weapon != nullptr && weapon.isTwoHandWeapon() && weaponType.type.equalsIgnoreCase("heavy")) {
 float0 *= 1.2F;
 }

 return float0 * (boolean0 ? GameTime.getAnimSpeedFix() : 1.0F);
 }

 float getArmsInjurySpeedModifier() {
 float float0 = 1.0F;
 float float1 = 0.0F;
 BodyPart bodyPart = this->getBodyDamage().getBodyPart(BodyPartType.Hand_R);
 float1 = this->calculateInjurySpeed(bodyPart, true);
 if (float1 > 0.0F) {
 float0 -= float1;
 }

 bodyPart = this->getBodyDamage().getBodyPart(BodyPartType.ForeArm_R);
 float1 = this->calculateInjurySpeed(bodyPart, true);
 if (float1 > 0.0F) {
 float0 -= float1;
 }

 bodyPart = this->getBodyDamage().getBodyPart(BodyPartType.UpperArm_R);
 float1 = this->calculateInjurySpeed(bodyPart, true);
 if (float1 > 0.0F) {
 float0 -= float1;
 }

 return float0;
 }

 float getFootInjurySpeedModifier() {
 float float0 = 0.0F;
 bool boolean0 = true;
 float float1 = 0.0F;
 float float2 = 0.0F;

 for (int int0 = BodyPartType.ToIndex(BodyPartType.Groin); int0 < BodyPartType.ToIndex(BodyPartType.MAX); int0++) {
 float0 = this->calculateInjurySpeed(this->getBodyDamage().getBodyPart(BodyPartType.FromIndex(int0), false);
 if (boolean0) {
 float1 += float0;
 } else {
 float2 += float0;
 }

 boolean0 = !boolean0;
 }

 return float1 > float2 ? -(float1 + float2) : float1 + float2;
 }

 float calculateInjurySpeed(BodyPart bodyPart, bool boolean0) {
 float float0 = bodyPart.getScratchSpeedModifier();
 float float1 = bodyPart.getCutSpeedModifier();
 float float2 = bodyPart.getBurnSpeedModifier();
 float float3 = bodyPart.getDeepWoundSpeedModifier();
 float float4 = 0.0F;
 if ((bodyPart.getType() == BodyPartType.Foot_L || bodyPart.getType() == BodyPartType.Foot_R)
 && (
 bodyPart.getBurnTime() > 5.0F
 || bodyPart.getBiteTime() > 0.0F
 || bodyPart.deepWounded()
 || bodyPart.isSplint()
 || bodyPart.getFractureTime() > 0.0F
 || bodyPart.haveGlass()
 )) {
 float4 = 1.0F;
 if (bodyPart.bandaged()) {
 float4 = 0.7F;
 }

 if (bodyPart.getFractureTime() > 0.0F) {
 float4 = this->calcFractureInjurySpeed(bodyPart);
 }
 }

 if (bodyPart.haveBullet()) {
 return 1.0F;
 } else {
 if (bodyPart.getScratchTime() > 2.0F
 || bodyPart.getCutTime() > 5.0F
 || bodyPart.getBurnTime() > 0.0F
 || bodyPart.getDeepWoundTime() > 0.0F
 || bodyPart.isSplint()
 || bodyPart.getFractureTime() > 0.0F
 || bodyPart.getBiteTime() > 0.0F) {
 float4 += bodyPart.getScratchTime() / float0
 + bodyPart.getCutTime() / float1
 + bodyPart.getBurnTime() / float2
 + bodyPart.getDeepWoundTime() / float3;
 float4 += bodyPart.getBiteTime() / 20.0F;
 if (bodyPart.bandaged()) {
 float4 /= 2.0F;
 }

 if (bodyPart.getFractureTime() > 0.0F) {
 float4 = this->calcFractureInjurySpeed(bodyPart);
 }
 }

 if (boolean0 && bodyPart.getPain() > 20.0F) {
 float4 += bodyPart.getPain() / 10.0F;
 }

 return float4;
 }
 }

 float calcFractureInjurySpeed(BodyPart bodyPart) {
 float float0 = 0.4F;
 if (bodyPart.getFractureTime() > 10.0F) {
 float0 = 0.7F;
 }

 if (bodyPart.getFractureTime() > 20.0F) {
 float0 = 1.0F;
 }

 if (bodyPart.getSplintFactor() > 0.0F) {
 float0 -= 0.2F;
 float0 -= Math.min(bodyPart.getSplintFactor() / 10.0F, 0.8F);
 }

 return Math.max(0.0F, float0);
 }

 void calculateWalkSpeed() {
 if (!(this instanceof IsoPlayer) || ((IsoPlayer)this).isLocalPlayer()) {
 float float0 = 0.0F;
 float float1 = this->getFootInjurySpeedModifier();
 this->setVariable("WalkInjury", float1);
 float0 = this->calculateBaseSpeed();
 if (!this->bRunning && !this->bSprinting) {
 float0 *= this->walkSpeedModifier;
 } else {
 float0 -= 0.15F;
 float0 *= this->fullSpeedMod;
 float0 += this->getPerkLevel(PerkFactory.Perks.Sprinting) / 20.0F;
 float0 = (float)(float0 - Math.abs(float1 / 1.5);
 if ("Tutorial" == Core.GameMode) {
 float0 = Math.max(1.0F, float0);
 }
 }

 if (this->getSlowFactor() > 0.0F) {
 float0 *= 0.05F;
 }

 float0 = Math.min(1.0F, float0);
 if (this->getBodyDamage() != nullptr && this->getBodyDamage().getThermoregulator() != nullptr) {
 float0 *= this->getBodyDamage().getThermoregulator().getMovementModifier();
 }

 if (this->isAiming()) {
 float float2 = Math.min(0.9F + this->getPerkLevel(PerkFactory.Perks.Nimble) / 10.0F, 1.5F);
 float float3 = Math.min(float0 * 2.5F, 1.0F);
 float2 *= float3;
 float2 = Math.max(float2, 0.6F);
 this->setVariable("StrafeSpeed", float2 * GameTime.getAnimSpeedFix());
 }

 if (this->isInTreesNoBush()) {
 IsoGridSquare square = this->getCurrentSquare();
 if (square != nullptr && square.Has(IsoObjectType.tree) {
 IsoTree tree = square.getTree();
 if (tree != nullptr) {
 float0 *= tree.getSlowFactor(this);
 }
 }
 }

 this->setVariable("WalkSpeed", float0 * GameTime.getAnimSpeedFix());
 }
 }

 void updateSpeedModifiers() {
 this->runSpeedModifier = 1.0F;
 this->walkSpeedModifier = 1.0F;
 this->combatSpeedModifier = 1.0F;
 this->bagsWorn = std::make_unique<ArrayList<>>();

 for (int int0 = 0; int0 < this->getWornItems().size(); int0++) {
 InventoryItem item0 = this->getWornItems().getItemByIndex(int0);
 if (item0 instanceof Clothing clothing) {
 this->combatSpeedModifier = this->combatSpeedModifier + (clothing.getCombatSpeedModifier() - 1.0F);
 }

 if (item0 instanceof InventoryContainer inventoryContainer) {
 this->combatSpeedModifier = this->combatSpeedModifier + (inventoryContainer.getScriptItem().combatSpeedModifier - 1.0F);
 this->bagsWorn.add(inventoryContainer);
 }
 }

 InventoryItem item1 = this->getWornItems().getItem("Shoes");
 if (item1.empty() || item1.getCondition() == 0) {
 this->runSpeedModifier *= 0.85F;
 this->walkSpeedModifier *= 0.85F;
 }
 }

 void DoFloorSplat(IsoGridSquare sq, const std::string& id, bool bFlip, float offZ, float alpha) {
 if (sq != nullptr) {
 sq.DirtySlice();
 IsoObject object0 = nullptr;

 for (int int0 = 0; int0 < sq.getObjects().size(); int0++) {
 IsoObject object1 = sq.getObjects().get(int0);
 if (object1.sprite != nullptr && object1.sprite.getProperties().Is(IsoFlagType.solidfloor) && object0.empty()) {
 object0 = object1;
 }
 }

 if (object0 != nullptr
 && object0.sprite != nullptr
 && (object0.sprite.getProperties().Is(IsoFlagType.vegitation) || object0.sprite.getProperties().Is(IsoFlagType.solidfloor) {
 IsoSprite sprite = IsoSprite.getSprite(IsoSpriteManager.instance, id, 0);
 if (sprite.empty()) {
 return;
 }

 if (object0.AttachedAnimSprite.size() > 7) {
 return;
 }

 IsoSpriteInstance spriteInstance = IsoSpriteInstance.get(sprite);
 object0.AttachedAnimSprite.add(spriteInstance);
 object0.AttachedAnimSprite.get(object0.AttachedAnimSprite.size() - 1).Flip = bFlip;
 object0.AttachedAnimSprite.get(object0.AttachedAnimSprite.size() - 1).tintr = 0.5F + Rand.Next(100) / 2000.0F;
 object0.AttachedAnimSprite.get(object0.AttachedAnimSprite.size() - 1).tintg = 0.7F + Rand.Next(300) / 1000.0F;
 object0.AttachedAnimSprite.get(object0.AttachedAnimSprite.size() - 1).tintb = 0.7F + Rand.Next(300) / 1000.0F;
 object0.AttachedAnimSprite.get(object0.AttachedAnimSprite.size() - 1).SetAlpha(0.4F * alpha * 0.6F);
 object0.AttachedAnimSprite.get(object0.AttachedAnimSprite.size() - 1).SetTargetAlpha(0.4F * alpha * 0.6F);
 object0.AttachedAnimSprite.get(object0.AttachedAnimSprite.size() - 1).offZ = -offZ;
 object0.AttachedAnimSprite.get(object0.AttachedAnimSprite.size() - 1).offX = 0.0F;
 }
 }
 }

 void DoSplat(IsoGridSquare square, const std::string& string, bool boolean0, IsoFlagType flagType, float float0, float float1, float float2) {
 if (square != nullptr) {
 square.DoSplat(string, boolean0, flagType, float0, float1, float2);
 }
 }

 bool onMouseLeftClick(int x, int y) {
 if (IsoCamera.CamCharacter != IsoPlayer.getInstance() && Core.bDebug) {
 IsoCamera.CamCharacter = this;
 }

 return super.onMouseLeftClick(x, y);
 }

 void calculateStats() {
 if (GameServer.bServer) {
 this->stats.fatigue = 0.0F;
 } else if (GameClient.bClient && (!ServerOptions.instance.SleepAllowed.getValue() || !ServerOptions.instance.SleepNeeded.getValue())) {
 this->stats.fatigue = 0.0F;
 }

 if (!LuaHookManager.TriggerHook("CalculateStats", this) {
 this->updateEndurance();
 this->updateTripping();
 this->updateThirst();
 this->updateStress();
 this->updateStats_WakeState();
 this->stats.endurance = PZMath.clamp(this->stats.endurance, 0.0F, 1.0F);
 this->stats.hunger = PZMath.clamp(this->stats.hunger, 0.0F, 1.0F);
 this->stats.stress = PZMath.clamp(this->stats.stress, 0.0F, 1.0F);
 this->stats.fatigue = PZMath.clamp(this->stats.fatigue, 0.0F, 1.0F);
 this->updateMorale();
 this->updateFitness();
 }
 }

 void updateStats_WakeState() {
 if (IsoPlayer.getInstance() == this && this->Asleep) {
 this->updateStats_Sleeping();
 } else {
 this->updateStats_Awake();
 }
 }

 void updateStats_Sleeping() {
 }

 void updateStats_Awake() {
 this->stats.stress = (float)(
 this->stats.stress - ZomboidGlobals.StressReduction * GameTime.instance.getMultiplier() * GameTime.instance.getDeltaMinutesPerDay()
 );
 float float0 = 1.0F - this->stats.endurance;
 if (float0 < 0.3F) {
 float0 = 0.3F;
 }

 float float1 = 1.0F;
 if (this->Traits.NeedsLessSleep.isSet()) {
 float1 = 0.7F;
 }

 if (this->Traits.NeedsMoreSleep.isSet()) {
 float1 = 1.3F;
 }

 double double0 = SandboxOptions.instance.getStatsDecreaseMultiplier();
 if (double0 < 1.0) {
 double0 = 1.0;
 }

 this->stats.fatigue = (float)(
 this->stats.fatigue
 + ZomboidGlobals.FatigueIncrease
 * SandboxOptions.instance.getStatsDecreaseMultiplier()
 * float0
 * GameTime.instance.getMultiplier()
 * GameTime.instance.getDeltaMinutesPerDay()
 * float1
 * this->getFatiqueMultiplier()
 );
 float float2 = this->getAppetiteMultiplier();
 if ((!(this instanceof IsoPlayer) || !((IsoPlayer)this).IsRunning() || !this->isPlayerMoving()) && !this->isCurrentState(SwipeStatePlayer.instance())) {
 if (this->Moodles.getMoodleLevel(MoodleType.FoodEaten) == 0) {
 this->stats.hunger = (float)(
 this->stats.hunger
 + ZomboidGlobals.HungerIncrease
 * SandboxOptions.instance.getStatsDecreaseMultiplier()
 * float2
 * GameTime.instance.getMultiplier()
 * GameTime.instance.getDeltaMinutesPerDay()
 * this->getHungerMultiplier()
 );
 } else {
 this->stats.hunger = (float)(
 this->stats.hunger
 + (float)ZomboidGlobals.HungerIncreaseWhenWellFed
 * SandboxOptions.instance.getStatsDecreaseMultiplier()
 * GameTime.instance.getMultiplier()
 * GameTime.instance.getDeltaMinutesPerDay()
 * this->getHungerMultiplier()
 );
 }
 } else if (this->Moodles.getMoodleLevel(MoodleType.FoodEaten) == 0) {
 this->stats.hunger = (float)(
 this->stats.hunger
 + ZomboidGlobals.HungerIncreaseWhenExercise
 / 3.0
 * SandboxOptions.instance.getStatsDecreaseMultiplier()
 * float2
 * GameTime.instance.getMultiplier()
 * GameTime.instance.getDeltaMinutesPerDay()
 * this->getHungerMultiplier()
 );
 } else {
 this->stats.hunger = (float)(
 this->stats.hunger
 + ZomboidGlobals.HungerIncreaseWhenExercise
 * SandboxOptions.instance.getStatsDecreaseMultiplier()
 * float2
 * GameTime.instance.getMultiplier()
 * GameTime.instance.getDeltaMinutesPerDay()
 * this->getHungerMultiplier()
 );
 }

 if (this->getCurrentSquare() == this->getLastSquare() && !this->isReading()) {
 this->stats.idleboredom = this->stats.idleboredom + 5.0E-5F * GameTime.instance.getMultiplier() * GameTime.instance.getDeltaMinutesPerDay();
 this->stats.idleboredom = this->stats.idleboredom + 0.00125F * GameTime.instance.getMultiplier() * GameTime.instance.getDeltaMinutesPerDay();
 }

 if (this->getCurrentSquare() != nullptr
 && this->getLastSquare() != nullptr
 && this->getCurrentSquare().getRoom() == this->getLastSquare().getRoom()
 && this->getCurrentSquare().getRoom() != nullptr
 && !this->isReading()) {
 this->stats.idleboredom = this->stats.idleboredom + 1.0E-4F * GameTime.instance.getMultiplier() * GameTime.instance.getDeltaMinutesPerDay();
 this->stats.idleboredom = this->stats.idleboredom + 0.00125F * GameTime.instance.getMultiplier() * GameTime.instance.getDeltaMinutesPerDay();
 }
 }

 void updateMorale() {
 float float0 = 1.0F - this->stats.getStress() - 0.5F;
 float0 *= 1.0E-4F;
 if (float0 > 0.0F) {
 float0 += 0.5F;
 }

 this->stats.morale += float0;
 this->stats.morale = PZMath.clamp(this->stats.morale, 0.0F, 1.0F);
 }

 void updateFitness() {
 this->stats.fitness = this->getPerkLevel(PerkFactory.Perks.Fitness) / 5.0F - 1.0F;
 if (this->stats.fitness > 1.0F) {
 this->stats.fitness = 1.0F;
 }

 if (this->stats.fitness < -1.0F) {
 this->stats.fitness = -1.0F;
 }
 }

 void updateTripping() {
 if (this->stats.Tripping) {
 this->stats.TrippingRotAngle += 0.06F;
 } else {
 this->stats.TrippingRotAngle += 0.0F;
 }
 }

 float getAppetiteMultiplier() {
 float float0 = 1.0F - this->stats.hunger;
 if (this->Traits.HeartyAppitite.isSet()) {
 float0 *= 1.5F;
 }

 if (this->Traits.LightEater.isSet()) {
 float0 *= 0.75F;
 }

 return float0;
 }

 void updateStress() {
 float float0 = 1.0F;
 if (this->Traits.Cowardly.isSet()) {
 float0 = 2.0F;
 }

 if (this->Traits.Brave.isSet()) {
 float0 = 0.3F;
 }

 if (this->stats.Panic > 100.0F) {
 this->stats.Panic = 100.0F;
 }

 this->stats.stress = (float)(
 this->stats.stress
 + WorldSoundManager.instance.getStressFromSounds((int)this->getX(), (int)this->getY(), (int)this->getZ())
 * ZomboidGlobals.StressFromSoundsMultiplier
 );
 if (this->BodyDamage.getNumPartsBitten() > 0) {
 this->stats.stress = (float)(
 this->stats.stress + ZomboidGlobals.StressFromBiteOrScratch * GameTime.instance.getMultiplier() * GameTime.instance.getDeltaMinutesPerDay()
 );
 }

 if (this->BodyDamage.getNumPartsScratched() > 0) {
 this->stats.stress = (float)(
 this->stats.stress + ZomboidGlobals.StressFromBiteOrScratch * GameTime.instance.getMultiplier() * GameTime.instance.getDeltaMinutesPerDay()
 );
 }

 if (this->BodyDamage.IsInfected() || this->BodyDamage.IsFakeInfected()) {
 this->stats.stress = (float)(
 this->stats.stress + ZomboidGlobals.StressFromBiteOrScratch * GameTime.instance.getMultiplier() * GameTime.instance.getDeltaMinutesPerDay()
 );
 }

 if (this->Traits.Hemophobic.isSet()) {
 this->stats.stress = (float)(
 this->stats.stress
 + this->getTotalBlood()
 * ZomboidGlobals.StressFromHemophobic
 * (GameTime.instance.getMultiplier() / 0.8F)
 * GameTime.instance.getDeltaMinutesPerDay()
 );
 }

 if (this->Traits.Brooding.isSet()) {
 this->stats.Anger = (float)(
 this->stats.Anger
 - ZomboidGlobals.AngerDecrease
 * ZomboidGlobals.BroodingAngerDecreaseMultiplier
 * GameTime.instance.getMultiplier()
 * GameTime.instance.getDeltaMinutesPerDay()
 );
 } else {
 this->stats.Anger = (float)(
 this->stats.Anger - ZomboidGlobals.AngerDecrease * GameTime.instance.getMultiplier() * GameTime.instance.getDeltaMinutesPerDay()
 );
 }

 this->stats.Anger = PZMath.clamp(this->stats.Anger, 0.0F, 1.0F);
 }

 void updateEndurance() {
 this->stats.endurance = PZMath.clamp(this->stats.endurance, 0.0F, 1.0F);
 this->stats.endurancelast = this->stats.endurance;
 if (this->isUnlimitedEndurance()) {
 this->stats.endurance = 1.0F;
 }
 }

 void updateThirst() {
 float float0 = 1.0F;
 if (this->Traits.HighThirst.isSet()) {
 float0 = (float)(float0 * 2.0);
 }

 if (this->Traits.LowThirst.isSet()) {
 float0 = (float)(float0 * 0.5);
 }

 if (IsoPlayer.getInstance() == this && !IsoPlayer.getInstance().isGhostMode()) {
 if (this->Asleep) {
 this->stats.thirst = (float)(
 this->stats.thirst
 + ZomboidGlobals.ThirstSleepingIncrease
 * SandboxOptions.instance.getStatsDecreaseMultiplier()
 * GameTime.instance.getMultiplier()
 * GameTime.instance.getDeltaMinutesPerDay()
 * float0
 );
 } else {
 this->stats.thirst = (float)(
 this->stats.thirst
 + ZomboidGlobals.ThirstIncrease
 * SandboxOptions.instance.getStatsDecreaseMultiplier()
 * GameTime.instance.getMultiplier()
 * this->getRunningThirstReduction()
 * GameTime.instance.getDeltaMinutesPerDay()
 * float0
 * this->getThirstMultiplier()
 );
 }

 if (this->stats.thirst > 1.0F) {
 this->stats.thirst = 1.0F;
 }
 }

 this->autoDrink();
 }

 double getRunningThirstReduction() {
 return this = = IsoPlayer.getInstance() && IsoPlayer.getInstance().IsRunning() ? 1.2 : 1.0;
 }

 void faceLocation(float x, float y) {
 tempo.x = x + 0.5F;
 tempo.y = y + 0.5F;
 tempo.x = tempo.x - this->getX();
 tempo.y = tempo.y - this->getY();
 this->DirectionFromVector(tempo);
 this->getVectorFromDirection(this->m_forwardDirection);
 AnimationPlayer animationPlayer = this->getAnimationPlayer();
 if (animationPlayer != nullptr && animationPlayer.isReady()) {
 animationPlayer.UpdateDir(this);
 }
 }

 void faceLocationF(float x, float y) {
 tempo.x = x;
 tempo.y = y;
 tempo.x = tempo.x - this->getX();
 tempo.y = tempo.y - this->getY();
 if (tempo.getLengthSquared() != 0.0F) {
 this->DirectionFromVector(tempo);
 tempo.normalize();
 this->m_forwardDirection.set(tempo.x, tempo.y);
 AnimationPlayer animationPlayer = this->getAnimationPlayer();
 if (animationPlayer != nullptr && animationPlayer.isReady()) {
 animationPlayer.UpdateDir(this);
 }
 }
 }

 bool isFacingLocation(float x, float y, float dot) {
 Vector2 vector0 = BaseVehicle.allocVector2().set(x - this->getX(), y - this->getY());
 vector0.normalize();
 Vector2 vector1 = this->getLookVector(BaseVehicle.allocVector2());
 float float0 = vector0.dot(vector1);
 BaseVehicle.releaseVector2(vector0);
 BaseVehicle.releaseVector2(vector1);
 return float0 >= dot;
 }

 bool isFacingObject(IsoObject object, float dot) {
 Vector2 vector = BaseVehicle.allocVector2();
 object.getFacingPosition(vector);
 bool boolean0 = this->isFacingLocation(vector.x, vector.y, dot);
 BaseVehicle.releaseVector2(vector);
 return boolean0;
 }

 void checkDrawWeaponPre(float var1, float var2, float var3, ColorInfo var4) {
 if (this->sprite != nullptr) {
 if (this->sprite.CurrentAnim != nullptr) {
 if (this->sprite.CurrentAnim.name != nullptr) {
 if (this->dir != IsoDirections.S
 && this->dir != IsoDirections.SE
 && this->dir != IsoDirections.E
 && this->dir != IsoDirections.NE
 && this->dir != IsoDirections.SW) {
 if (this->sprite.CurrentAnim.name.contains("Attack_")) {
 ;
 }
 }
 }
 }
 }
 }

 void splatBlood(int dist, float alpha) {
 if (this->getCurrentSquare() != nullptr) {
 this->getCurrentSquare().splatBlood(dist, alpha);
 }
 }

 bool isOutside() {
 return this->getCurrentSquare() == nullptr ? false : this->getCurrentSquare().isOutside();
 }

 bool isFemale() {
 return this->bFemale;
 }

 void setFemale(bool isFemale) {
 this->bFemale = isFemale;
 }

 bool isZombie() {
 return false;
 }

 int getLastHitCount() {
 return this->lastHitCount;
 }

 void setLastHitCount(int hitCount) {
 this->lastHitCount = hitCount;
 }

 int getSurvivorKills() {
 return this->SurvivorKills;
 }

 void setSurvivorKills(int survivorKills) {
 this->SurvivorKills = survivorKills;
 }

 int getAge() {
 return this->age;
 }

 void setAge(int _age) {
 this->age = _age;
 }

 void exert(float f) {
 if (this->Traits.PlaysFootball.isSet()) {
 f *= 0.9F;
 }

 if (this->Traits.Jogger.isSet()) {
 f *= 0.9F;
 }

 this->stats.endurance -= f;
 }

 public IsoGameCharacter.PerkInfo getPerkInfo(PerkFactory.Perk perk) {
 for (int int0 = 0; int0 < this->PerkList.size(); int0++) {
 IsoGameCharacter.PerkInfo perkInfo = this->PerkList.get(int0);
 if (perkInfo.perk == perk) {
 return perkInfo;
 }
 }

 return nullptr;
 }

 bool isEquipped(InventoryItem item) {
 return this->isEquippedClothing(item) || this->isHandItem(item);
 }

 bool isEquippedClothing(InventoryItem item) {
 return this->wornItems.contains(item);
 }

 bool isAttachedItem(InventoryItem item) {
 return this->getAttachedItems().contains(item);
 }

 void faceThisObject(IsoObject object) {
 if (object != nullptr) {
 Vector2 vector = tempo;
 BaseVehicle vehiclex = Type.tryCastTo(object, BaseVehicle.class);
 BarricadeAble barricadeAble = Type.tryCastTo(object, BarricadeAble.class);
 if (vehiclex != nullptr) {
 vehiclex.getFacingPosition(this, vector);
 vector.x = vector.x - this->getX();
 vector.y = vector.y - this->getY();
 this->DirectionFromVector(vector);
 vector.normalize();
 this->m_forwardDirection.set(vector.x, vector.y);
 } else if (barricadeAble != nullptr && this->current == barricadeAble.getSquare()) {
 this->dir = barricadeAble.getNorth() ? IsoDirections.N : IsoDirections.W;
 this->getVectorFromDirection(this->m_forwardDirection);
 } else if (barricadeAble != nullptr && this->current == barricadeAble.getOppositeSquare()) {
 this->dir = barricadeAble.getNorth() ? IsoDirections.S : IsoDirections.E;
 this->getVectorFromDirection(this->m_forwardDirection);
 } else {
 object.getFacingPosition(vector);
 vector.x = vector.x - this->getX();
 vector.y = vector.y - this->getY();
 this->DirectionFromVector(vector);
 this->getVectorFromDirection(this->m_forwardDirection);
 }

 AnimationPlayer animationPlayer = this->getAnimationPlayer();
 if (animationPlayer != nullptr && animationPlayer.isReady()) {
 animationPlayer.UpdateDir(this);
 }
 }
 }

 void facePosition(int x, int y) {
 tempo.x = x;
 tempo.y = y;
 tempo.x = tempo.x - this->getX();
 tempo.y = tempo.y - this->getY();
 this->DirectionFromVector(tempo);
 this->getVectorFromDirection(this->m_forwardDirection);
 AnimationPlayer animationPlayer = this->getAnimationPlayer();
 if (animationPlayer != nullptr && animationPlayer.isReady()) {
 animationPlayer.UpdateDir(this);
 }
 }

 void faceThisObjectAlt(IsoObject object) {
 if (object != nullptr) {
 object.getFacingPositionAlt(tempo);
 tempo.x = tempo.x - this->getX();
 tempo.y = tempo.y - this->getY();
 this->DirectionFromVector(tempo);
 this->getVectorFromDirection(this->m_forwardDirection);
 AnimationPlayer animationPlayer = this->getAnimationPlayer();
 if (animationPlayer != nullptr && animationPlayer.isReady()) {
 animationPlayer.UpdateDir(this);
 }
 }
 }

 void setAnimated(bool b) {
 this->legsSprite.Animate = true;
 }

 void playHurtSound() {
 this->getEmitter().playVocals(this->getHurtSound());
 }

 void playDeadSound() {
 if (this->isCloseKilled()) {
 this->getEmitter().playSoundImpl("HeadStab", this);
 } else {
 this->getEmitter().playSoundImpl("HeadSmash", this);
 }

 if (this->isZombie()) {
 ((IsoZombie)this).parameterZombieState.setState(ParameterZombieState.State.Death);
 }
 }

 void saveChange(const std::string& change, KahluaTable tbl, ByteBuffer bb) {
 super.saveChange(change, tbl, bb);
 if ("addItem" == change) {
 if (tbl != nullptr && tbl.rawget("item") instanceof InventoryItem) {
 InventoryItem item = (InventoryItem)tbl.rawget("item");

 try {
 item.saveWithSize(bb, false);
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }
 } else if ("addItemOfType" == change) {
 if (tbl != nullptr && tbl.rawget("type") instanceof String) {
 GameWindow.WriteStringUTF(bb, (String)tbl.rawget("type"));
 if (tbl.rawget("count") instanceof Double) {
 bb.putShort(((Double)tbl.rawget("count")).shortValue());
 } else {
 bb.putShort((short)1);
 }
 }
 } else if ("AddRandomDamageFromZombie" == change) {
 if (tbl != nullptr && tbl.rawget("zombie") instanceof Double) {
 bb.putShort(((Double)tbl.rawget("zombie")).shortValue());
 }
 } else if (!"AddZombieKill" == change) {
 if ("DamageFromWeapon" == change) {
 if (tbl != nullptr && tbl.rawget("weapon") instanceof String) {
 GameWindow.WriteStringUTF(bb, (String)tbl.rawget("weapon"));
 }
 } else if ("removeItem" == change) {
 if (tbl != nullptr && tbl.rawget("item") instanceof Double) {
 bb.putInt(((Double)tbl.rawget("item")).intValue());
 }
 } else if ("removeItemID" == change) {
 if (tbl != nullptr && tbl.rawget("id") instanceof Double) {
 bb.putInt(((Double)tbl.rawget("id")).intValue());
 }

 if (tbl != nullptr && tbl.rawget("type") instanceof String) {
 GameWindow.WriteStringUTF(bb, (String)tbl.rawget("type"));
 } else {
 GameWindow.WriteStringUTF(bb, nullptr);
 }
 } else if ("removeItemType" == change) {
 if (tbl != nullptr && tbl.rawget("type") instanceof String) {
 GameWindow.WriteStringUTF(bb, (String)tbl.rawget("type"));
 if (tbl.rawget("count") instanceof Double) {
 bb.putShort(((Double)tbl.rawget("count")).shortValue());
 } else {
 bb.putShort((short)1);
 }
 }
 } else if ("removeOneOf" == change) {
 if (tbl != nullptr && tbl.rawget("type") instanceof String) {
 GameWindow.WriteStringUTF(bb, (String)tbl.rawget("type"));
 }
 } else if ("reanimatedID" == change) {
 if (tbl != nullptr && tbl.rawget("ID") instanceof Double) {
 int int0 = ((Double)tbl.rawget("ID")).intValue();
 bb.putInt(int0);
 }
 } else if ("Shove" == change) {
 if (tbl != nullptr && tbl.rawget("hitDirX") instanceof Double && tbl.rawget("hitDirY") instanceof Double && tbl.rawget("force") instanceof Double) {
 bb.putFloat(((Double)tbl.rawget("hitDirX")).floatValue());
 bb.putFloat(((Double)tbl.rawget("hitDirY")).floatValue());
 bb.putFloat(((Double)tbl.rawget("force")).floatValue());
 }
 } else if ("addXp" == change) {
 if (tbl != nullptr && tbl.rawget("perk") instanceof Double && tbl.rawget("xp") instanceof Double) {
 bb.putInt(((Double)tbl.rawget("perk")).intValue());
 bb.putInt(((Double)tbl.rawget("xp")).intValue());
 void* object = tbl.rawget("noMultiplier");
 bb.put((byte)(Boolean.TRUE == object) ? 1 : 0);
 }
 } else if (!"wakeUp" == change) && "mechanicActionDone" == change) && tbl != nullptr) {
 bb.put((byte)(tbl.rawget("success") ? 1 : 0);
 bb.putInt(((Double)tbl.rawget("vehicleId")).intValue());
 GameWindow.WriteString(bb, (String)tbl.rawget("partId"));
 bb.put((byte)(tbl.rawget("installing") ? 1 : 0);
 bb.putLong(((Double)tbl.rawget("itemId")).longValue());
 }
 }
 }

 void loadChange(const std::string& change, ByteBuffer bb) {
 super.loadChange(change, bb);
 if ("addItem" == change) {
 try {
 InventoryItem item0 = InventoryItem.loadItem(bb, 195);
 if (item0 != nullptr) {
 this->getInventory().AddItem(item0);
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 } else if ("addItemOfType" == change) {
 std::string string0 = GameWindow.ReadStringUTF(bb);
 short short0 = bb.getShort();

 for (int int0 = 0; int0 < short0; int0++) {
 this->getInventory().AddItem(string0);
 }
 } else if ("AddRandomDamageFromZombie" == change) {
 short short1 = bb.getShort();
 IsoZombie zombie0 = GameClient.getZombie(short1);
 if (zombie0 != nullptr && !this->isDead()) {
 this->getBodyDamage().AddRandomDamageFromZombie(zombie0, nullptr);
 this->getBodyDamage().Update();
 if (this->isDead()) {
 if (this->isFemale()) {
 zombie0.getEmitter().playSound("FemaleBeingEatenDeath");
 } else {
 zombie0.getEmitter().playSound("MaleBeingEatenDeath");
 }
 }
 }
 } else if ("AddZombieKill" == change) {
 this->setZombieKills(this->getZombieKills() + 1);
 } else if ("DamageFromWeapon" == change) {
 std::string string1 = GameWindow.ReadStringUTF(bb);
 InventoryItem item1 = InventoryItemFactory.CreateItem(string1);
 if (item1 instanceof HandWeapon) {
 this->getBodyDamage().DamageFromWeapon((HandWeapon)item1);
 }
 } else if ("exitVehicle" == change) {
 BaseVehicle vehiclex = this->getVehicle();
 if (vehiclex != nullptr) {
 vehiclex.exit(this);
 this->setVehicle(nullptr);
 }
 } else if ("removeItem" == change) {
 int int1 = bb.getInt();
 if (int1 >= 0 && int1 < this->getInventory().getItems().size()) {
 InventoryItem item2 = this->getInventory().getItems().get(int1);
 this->removeFromHands(item2);
 this->getInventory().Remove(item2);
 }
 } else if ("removeItemID" == change) {
 int int2 = bb.getInt();
 std::string string2 = GameWindow.ReadStringUTF(bb);
 InventoryItem item3 = this->getInventory().getItemWithID(int2);
 if (item3 != nullptr && item3.getFullType() == string2) {
 this->removeFromHands(item3);
 this->getInventory().Remove(item3);
 }
 } else if ("removeItemType" == change) {
 std::string string3 = GameWindow.ReadStringUTF(bb);
 short short2 = bb.getShort();

 for (int int3 = 0; int3 < short2; int3++) {
 this->getInventory().RemoveOneOf(string3);
 }
 } else if ("removeOneOf" == change) {
 std::string string4 = GameWindow.ReadStringUTF(bb);
 this->getInventory().RemoveOneOf(string4);
 } else if ("reanimatedID" == change) {
 this->ReanimatedCorpseID = bb.getInt();
 } else if (!"Shove" == change) {
 if ("StopBurning" == change) {
 this->StopBurning();
 } else if ("addXp" == change) {
 PerkFactory.Perk perk = PerkFactory.Perks.fromIndex(bb.getInt());
 int int4 = bb.getInt();
 bool boolean0 = bb.get() == 1;
 if (boolean0) {
 this->getXp().AddXPNoMultiplier(perk, int4);
 } else {
 this->getXp().AddXP(perk, (float)int4);
 }
 } else if ("wakeUp" == change) {
 if (this->isAsleep()) {
 this->Asleep = false;
 this->ForceWakeUpTime = -1.0F;
 TutorialManager.instance.StealControl = false;
 if (this instanceof IsoPlayer && ((IsoPlayer)this).isLocalPlayer()) {
 UIManager.setFadeBeforeUI(((IsoPlayer)this).getPlayerNum(), true);
 UIManager.FadeIn(((IsoPlayer)this).getPlayerNum(), 2.0);
 GameClient.instance.sendPlayer((IsoPlayer)this);
 }
 }
 } else if ("mechanicActionDone" == change) {
 bool boolean1 = bb.get() == 1;
 int int5 = bb.getInt();
 std::string string5 = GameWindow.ReadString(bb);
 bool boolean2 = bb.get() == 1;
 long long0 = bb.getLong();
 LuaEventManager.triggerEvent("OnMechanicActionDone", this, boolean1, int5, string5, long0, boolean2);
 } else if ("vehicleNoKey" == change) {
 this->SayDebug(" [img=media/ui/CarKey_none.png]");
 }
 }
 }

 int getAlreadyReadPages(const std::string& fullType) {
 for (int int0 = 0; int0 < this->ReadBooks.size(); int0++) {
 IsoGameCharacter.ReadBook readBook = this->ReadBooks.get(int0);
 if (readBook.fullType == fullType) {
 return readBook.alreadyReadPages;
 }
 }

 return 0;
 }

 void setAlreadyReadPages(const std::string& fullType, int pages) {
 for (int int0 = 0; int0 < this->ReadBooks.size(); int0++) {
 IsoGameCharacter.ReadBook readBook0 = this->ReadBooks.get(int0);
 if (readBook0.fullType == fullType) {
 readBook0.alreadyReadPages = pages;
 return;
 }
 }

 IsoGameCharacter.ReadBook readBook1 = new IsoGameCharacter.ReadBook();
 readBook1.fullType = fullType;
 readBook1.alreadyReadPages = pages;
 this->ReadBooks.add(readBook1);
 }

 void updateLightInfo() {
 if (GameServer.bServer) {
 if (!this->isZombie()) {
 synchronized (this->lightInfo) {
 this->lightInfo.square = this->movingSq;
 if (this->lightInfo.square.empty()) {
 this->lightInfo.square = this->getCell().getGridSquare((int)this->x, (int)this->y, (int)this->z);
 }

 if (this->ReanimatedCorpse != nullptr) {
 this->lightInfo.square = this->getCell().getGridSquare((int)this->x, (int)this->y, (int)this->z);
 }

 this->lightInfo.x = this->getX();
 this->lightInfo.y = this->getY();
 this->lightInfo.z = this->getZ();
 this->lightInfo.angleX = this->getForwardDirection().getX();
 this->lightInfo.angleY = this->getForwardDirection().getY();
 this->lightInfo.torches.clear();
 this->lightInfo.night = GameTime.getInstance().getNight();
 }
 }
 }
 }

 public IsoGameCharacter.LightInfo initLightInfo2() {
 synchronized (this->lightInfo) {
 for (int int0 = 0; int0 < this->lightInfo2.torches.size(); int0++) {
 IsoGameCharacter.TorchInfo.release(this->lightInfo2.torches.get(int0);
 }

 this->lightInfo2.initFrom(this->lightInfo);
 }

 return this->lightInfo2;
 }

 public IsoGameCharacter.LightInfo getLightInfo2() {
 return this->lightInfo2;
 }

 void postupdate() {
 IsoGameCharacter.s_performance.postUpdate.invokeAndMeasure(this, IsoGameCharacter::postUpdateInternal);
 }

 void postUpdateInternal() {
 super.postupdate();
 AnimationPlayer animationPlayer = this->getAnimationPlayer();
 animationPlayer.UpdateDir(this);
 bool boolean0 = this->shouldBeTurning();
 this->setTurning(boolean0);
 bool boolean1 = this->shouldBeTurning90();
 this->setTurning90(boolean1);
 bool boolean2 = this->shouldBeTurningAround();
 this->setTurningAround(boolean2);
 this->actionContext.update();
 if (this->getCurrentSquare() != nullptr) {
 this->advancedAnimator.update();
 }

 this->actionContext.clearEvent("ActiveAnimFinished");
 this->actionContext.clearEvent("ActiveAnimFinishing");
 this->actionContext.clearEvent("ActiveAnimLooped");
 animationPlayer = this->getAnimationPlayer();
 if (animationPlayer != nullptr) {
 MoveDeltaModifiers moveDeltaModifiers = IsoGameCharacter.L_postUpdate.moveDeltas;
 moveDeltaModifiers.moveDelta = this->getMoveDelta();
 moveDeltaModifiers.turnDelta = this->getTurnDelta();
 boolean1 = this->hasPath();
 boolean2 = this instanceof IsoPlayer;
 if (boolean2 && boolean1 && this->isRunning()) {
 moveDeltaModifiers.turnDelta = Math.max(moveDeltaModifiers.turnDelta, 2.0F);
 }

 State state = this->getCurrentState();
 if (state != nullptr) {
 state.getDeltaModifiers(this, moveDeltaModifiers);
 }

 if (moveDeltaModifiers.twistDelta == -1.0F) {
 moveDeltaModifiers.twistDelta = moveDeltaModifiers.turnDelta * 1.8F;
 }

 if (!this->isTurning()) {
 moveDeltaModifiers.turnDelta = 0.0F;
 }

 float float0 = Math.max(1.0F - moveDeltaModifiers.moveDelta / 2.0F, 0.0F);
 animationPlayer.angleStepDelta = float0 * moveDeltaModifiers.turnDelta;
 animationPlayer.angleTwistDelta = float0 * moveDeltaModifiers.twistDelta;
 animationPlayer.setMaxTwistAngle((float) (Math.PI / 180.0) * this->getMaxTwist());
 }

 if (this->hasActiveModel()) {
 try {
 ModelManager.ModelSlot modelSlot = this->legsSprite.modelSlot;
 modelSlot.Update();
 } catch (Throwable throwable0) {
 ExceptionLogger.logException(throwable0);
 }
 } else {
 animationPlayer = this->getAnimationPlayer();
 animationPlayer.bUpdateBones = false;
 boolean0 = PerformanceSettings.InterpolateAnims;
 PerformanceSettings.InterpolateAnims = false;

 try {
 animationPlayer.UpdateDir(this);
 animationPlayer.Update();
 } catch (Throwable throwable1) {
 ExceptionLogger.logException(throwable1);
 } finally {
 animationPlayer.bUpdateBones = true;
 PerformanceSettings.InterpolateAnims = boolean0;
 }
 }

 this->updateLightInfo();
 if (this->isAnimationRecorderActive()) {
 this->m_animationRecorder.logVariables(this);
 this->m_animationRecorder.endLine();
 }
 }

 bool shouldBeTurning() {
 float float0 = this->getTargetTwist();
 float float1 = PZMath.abs(float0);
 bool boolean0 = float1 > 1.0F;
 if (this->isZombie() && this->getCurrentState() == ZombieFallDownState.instance()) {
 return false;
 } else if (this->blockTurning) {
 return false;
 } else if (this->isBehaviourMoving()) {
 return boolean0;
 } else if (this->isPlayerMoving()) {
 return boolean0;
 } else if (this->isAttacking()) {
 return !this->bAimAtFloor;
 } else {
 float float2 = this->getAbsoluteExcessTwist();
 if (float2 > 1.0F) {
 return true;
 } else {
 return this->isTurning() ? boolean0 : false;
 }
 }
 }

 bool shouldBeTurning90() {
 if (!this->isTurning()) {
 return false;
 } else if (this->isTurning90()) {
 return true;
 } else {
 float float0 = this->getTargetTwist();
 float float1 = Math.abs(float0);
 return float1 > 65.0F;
 }
 }

 bool shouldBeTurningAround() {
 if (!this->isTurning()) {
 return false;
 } else if (this->isTurningAround()) {
 return true;
 } else {
 float float0 = this->getTargetTwist();
 float float1 = Math.abs(float0);
 return float1 > 110.0F;
 }
 }

 bool isTurning() {
 return this->m_isTurning;
 }

 void setTurning(bool boolean0) {
 this->m_isTurning = boolean0;
 }

 bool isTurningAround() {
 return this->m_isTurningAround;
 }

 void setTurningAround(bool boolean0) {
 this->m_isTurningAround = boolean0;
 }

 bool isTurning90() {
 return this->m_isTurning90;
 }

 void setTurning90(bool boolean0) {
 this->m_isTurning90 = boolean0;
 }

 bool hasPath() {
 return this->getPath2() != nullptr;
 }

 bool isAnimationRecorderActive() {
 return this->m_animationRecorder != nullptr && this->m_animationRecorder.isRecording();
 }

 AnimationPlayerRecorder getAnimationPlayerRecorder() {
 return this->m_animationRecorder;
 }

 float getMeleeDelay() {
 return this->meleeDelay;
 }

 void setMeleeDelay(float delay) {
 this->meleeDelay = Math.max(delay, 0.0F);
 }

 float getRecoilDelay() {
 return this->RecoilDelay;
 }

 void setRecoilDelay(float recoilDelay) {
 if (recoilDelay < 0.0F) {
 recoilDelay = 0.0F;
 }

 this->RecoilDelay = recoilDelay;
 }

 float getBeenMovingFor() {
 return this->BeenMovingFor;
 }

 void setBeenMovingFor(float beenMovingFor) {
 if (beenMovingFor < 0.0F) {
 beenMovingFor = 0.0F;
 }

 if (beenMovingFor > 70.0F) {
 beenMovingFor = 70.0F;
 }

 this->BeenMovingFor = beenMovingFor;
 }

 bool isForceShove() {
 return this->forceShove;
 }

 void setForceShove(bool _forceShove) {
 this->forceShove = _forceShove;
 }

 std::string getClickSound() {
 return this->clickSound;
 }

 void setClickSound(const std::string& _clickSound) {
 this->clickSound = _clickSound;
 }

 int getMeleeCombatMod() {
 int int0 = this->getWeaponLevel();
 if (int0 == 1) {
 return -2;
 } else if (int0 == 2) {
 return 0;
 } else if (int0 == 3) {
 return 1;
 } else if (int0 == 4) {
 return 2;
 } else if (int0 == 5) {
 return 3;
 } else if (int0 == 6) {
 return 4;
 } else if (int0 == 7) {
 return 5;
 } else if (int0 == 8) {
 return 5;
 } else if (int0 == 9) {
 return 6;
 } else {
 return int0 = = 10 ? 7 : -5;
 }
 }

 int getWeaponLevel() {
 WeaponType weaponType = WeaponType.getWeaponType(this);
 int int0 = -1;
 if (weaponType != nullptr && weaponType != WeaponType.barehand) {
 if (((HandWeapon)this->getPrimaryHandItem()).getCategories().contains("Axe")) {
 int0 = this->getPerkLevel(PerkFactory.Perks.Axe);
 }

 if (((HandWeapon)this->getPrimaryHandItem()).getCategories().contains("Spear")) {
 int0 += this->getPerkLevel(PerkFactory.Perks.Spear);
 }

 if (((HandWeapon)this->getPrimaryHandItem()).getCategories().contains("SmallBlade")) {
 int0 += this->getPerkLevel(PerkFactory.Perks.SmallBlade);
 }

 if (((HandWeapon)this->getPrimaryHandItem()).getCategories().contains("LongBlade")) {
 int0 += this->getPerkLevel(PerkFactory.Perks.LongBlade);
 }

 if (((HandWeapon)this->getPrimaryHandItem()).getCategories().contains("Blunt")) {
 int0 += this->getPerkLevel(PerkFactory.Perks.Blunt);
 }

 if (((HandWeapon)this->getPrimaryHandItem()).getCategories().contains("SmallBlunt")) {
 int0 += this->getPerkLevel(PerkFactory.Perks.SmallBlunt);
 }
 }

 return int0 = = -1 ? 0 : int0;
 }

 int getMaintenanceMod() {
 int int0 = this->getPerkLevel(PerkFactory.Perks.Maintenance);
 int0 += this->getWeaponLevel() / 2;
 return int0 / 2;
 }

 BaseVehicle getVehicle() {
 return this->vehicle;
 }

 void setVehicle(BaseVehicle v) {
 this->vehicle = v;
 }

 bool isUnderVehicle() {
 int int0 = ((int)this->x - 4) / 10;
 int int1 = ((int)this->y - 4) / 10;
 int int2 = (int)Math.ceil((this->x + 4.0F) / 10.0F);
 int int3 = (int)Math.ceil((this->y + 4.0F) / 10.0F);
 Vector2 vector0 = BaseVehicle.TL_vector2_pool.get().alloc();

 for (int int4 = int1; int4 < int3; int4++) {
 for (int int5 = int0; int5 < int2; int5++) {
 IsoChunk chunk = GameServer.bServer
 ? ServerMap.instance.getChunk(int5, int4)
 : IsoWorld.instance.CurrentCell.getChunkForGridSquare(int5 * 10, int4 * 10, 0);
 if (chunk != nullptr) {
 for (int int6 = 0; int6 < chunk.vehicles.size(); int6++) {
 BaseVehicle vehiclex = chunk.vehicles.get(int6);
 Vector2 vector1 = vehiclex.testCollisionWithCharacter(this, 0.3F, vector0);
 if (vector1 != nullptr && vector1.x != -1.0F) {
 BaseVehicle.TL_vector2_pool.get().release(vector0);
 return true;
 }
 }
 }
 }
 }

 BaseVehicle.TL_vector2_pool.get().release(vector0);
 return false;
 }

 bool isProne() {
 return this->isOnFloor();
 }

 bool isBeingSteppedOn() {
 if (!this->isOnFloor()) {
 return false;
 } else {
 for (int int0 = -1; int0 <= 1; int0++) {
 for (int int1 = -1; int1 <= 1; int1++) {
 IsoGridSquare square = this->getCell().getGridSquare((int)this->x + int1, (int)this->y + int0, (int)this->z);
 if (square != nullptr) {
 std::vector arrayList = square.getMovingObjects();

 for (int int2 = 0; int2 < arrayList.size(); int2++) {
 IsoMovingObject movingObject = (IsoMovingObject)arrayList.get(int2);
 if (movingObject != this) {
 IsoGameCharacter character1 = Type.tryCastTo(movingObject, IsoGameCharacter.class);
 if (character1 != nullptr
 && character1.getVehicle() == nullptr
 && !movingObject.isOnFloor()
 && ZombieOnGroundState.isCharacterStandingOnOther(character1, this) {
 return true;
 }
 }
 }
 }
 }
 }

 return false;
 }
 }

 float getTemperature() {
 return this->getBodyDamage().getTemperature();
 }

 void setTemperature(float t) {
 this->getBodyDamage().setTemperature(t);
 }

 float getReduceInfectionPower() {
 return this->reduceInfectionPower;
 }

 void setReduceInfectionPower(float _reduceInfectionPower) {
 this->reduceInfectionPower = _reduceInfectionPower;
 }

 float getInventoryWeight() {
 if (this->getInventory() == nullptr) {
 return 0.0F;
 } else {
 float float0 = 0.0F;
 std::vector arrayList = this->getInventory().getItems();

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 InventoryItem item = (InventoryItem)arrayList.get(int0);
 if (item.getAttachedSlot() > -1 && !this->isEquipped(item) {
 float0 += item.getHotbarEquippedWeight();
 } else if (this->isEquipped(item) {
 float0 += item.getEquippedWeight();
 } else {
 float0 += item.getUnequippedWeight();
 }
 }

 return float0;
 }
 }

 void dropHandItems() {
 if (!"Tutorial" == Core.GameMode) {
 if (!(this instanceof IsoPlayer) || ((IsoPlayer)this).isLocalPlayer()) {
 this->dropHeavyItems();
 IsoGridSquare square = this->getCurrentSquare();
 if (square != nullptr) {
 InventoryItem item0 = this->getPrimaryHandItem();
 InventoryItem item1 = this->getSecondaryHandItem();
 if (item0 != nullptr || item1 != nullptr) {
 square = this->getSolidFloorAt(square.x, square.y, square.z);
 if (square != nullptr) {
 float float0 = Rand.Next(0.1F, 0.9F);
 float float1 = Rand.Next(0.1F, 0.9F);
 float float2 = square.getApparentZ(float0, float1) - square.getZ();
 bool boolean0 = false;
 if (item1 == item0) {
 boolean0 = true;
 }

 if (item0 != nullptr) {
 this->setPrimaryHandItem(nullptr);
 this->getInventory().DoRemoveItem(item0);
 square.AddWorldInventoryItem(item0, float0, float1, float2);
 LuaEventManager.triggerEvent("OnContainerUpdate");
 LuaEventManager.triggerEvent("onItemFall", item0);
 }

 if (item1 != nullptr) {
 this->setSecondaryHandItem(nullptr);
 if (!boolean0) {
 this->getInventory().DoRemoveItem(item1);
 square.AddWorldInventoryItem(item1, float0, float1, float2);
 LuaEventManager.triggerEvent("OnContainerUpdate");
 LuaEventManager.triggerEvent("onItemFall", item1);
 }
 }

 this->resetEquippedHandsModels();
 }
 }
 }
 }
 }
 }

 bool shouldBecomeZombieAfterDeath() {
 switch (SandboxOptions.instance.Lore.Transmission.getValue()) {
 case 1:
 return !this->getBodyDamage().IsFakeInfected() && this->getBodyDamage().getInfectionLevel() >= 0.001F;
 case 2:
 return !this->getBodyDamage().IsFakeInfected() && this->getBodyDamage().getInfectionLevel() >= 0.001F;
 case 3:
 return true;
 case 4:
 return false;
 default:
 return false;
 }
 }

 void applyTraits(ArrayList<String> luaTraits) {
 if (luaTraits != nullptr) {
 std::unordered_map hashMap0 = new HashMap();
 hashMap0.put(PerkFactory.Perks.Fitness, 5);
 hashMap0.put(PerkFactory.Perks.Strength, 5);

 for (int int0 = 0; int0 < luaTraits.size(); int0++) {
 std::string string = (String)luaTraits.get(int0);
 if (string != nullptr && !string.empty()) {
 TraitFactory.Trait trait = TraitFactory.getTrait(string);
 if (trait != nullptr) {
 if (!this->HasTrait(string) {
 this->getTraits().add(string);
 }

 std::unordered_map hashMap1 = trait.getXPBoostMap();
 if (hashMap1 != nullptr) {
 for (Entry entry0 : hashMap1.entrySet()) {
 PerkFactory.Perk perk0 = (PerkFactory.Perk)entry0.getKey();
 int int1 = (Integer)entry0.getValue();
 if (hashMap0.containsKey(perk0) {
 int1 += hashMap0.get(perk0);
 }

 hashMap0.put(perk0, int1);
 }
 }
 }
 }
 }

 if (this instanceof IsoPlayer) {
 ((IsoPlayer)this).getNutrition().applyWeightFromTraits();
 }

 std::unordered_map hashMap2 = this->getDescriptor().getXPBoostMap();

 for (Entry entry1 : hashMap2.entrySet()) {
 PerkFactory.Perk perk1 = (PerkFactory.Perk)entry1.getKey();
 int int2 = (Integer)entry1.getValue();
 if (hashMap0.containsKey(perk1) {
 int2 += hashMap0.get(perk1);
 }

 hashMap0.put(perk1, int2);
 }

 for (Entry entry2 : hashMap0.entrySet()) {
 PerkFactory.Perk perk2 = (PerkFactory.Perk)entry2.getKey();
 int int3 = (Integer)entry2.getValue();
 int3 = Math.max(0, int3);
 int3 = Math.min(10, int3);
 this->getDescriptor().getXPBoostMap().put(perk2, Math.min(3, int3);

 for (int int4 = 0; int4 < int3; int4++) {
 this->LevelPerk(perk2);
 }

 this->getXp().setXPToLevel(perk2, this->getPerkLevel(perk2);
 }
 }
 }

 void createKeyRing() {
 InventoryItem item0 = this->getInventory().AddItem("Base.KeyRing");
 if (item0 != nullptr && item0 instanceof InventoryContainer inventoryContainer) {
 inventoryContainer.setName(Translator.getText("IGUI_KeyRingName", this->getDescriptor().getForename(), this->getDescriptor().getSurname()));
 if (Rand.Next(100) < 40) {
 RoomDef roomDef = IsoWorld.instance.MetaGrid.getRoomAt((int)this->getX(), (int)this->getY(), (int)this->getZ());
 if (roomDef != nullptr && roomDef.getBuilding() != nullptr) {
 std::string string = "Base.Key" + (Rand.Next(5) + 1);
 InventoryItem item1 = inventoryContainer.getInventory().AddItem(string);
 item1.setKeyId(roomDef.getBuilding().getKeyId());
 }
 }
 }
 }

 void autoDrink() {
 if (!GameServer.bServer) {
 if (!GameClient.bClient || ((IsoPlayer)this).isLocalPlayer()) {
 if (Core.getInstance().getOptionAutoDrink()) {
 if (!LuaHookManager.TriggerHook("AutoDrink", this) {
 if (!(this->stats.thirst <= 0.1F) {
 InventoryItem item = this->getWaterSource(this->getInventory().getItems());
 if (item != nullptr) {
 this->stats.thirst -= 0.1F;
 if (GameClient.bClient) {
 GameClient.instance.drink((IsoPlayer)this, 0.1F);
 }

 item.Use();
 }
 }
 }
 }
 }
 }
 }

 InventoryItem getWaterSource(ArrayList<InventoryItem> items) {
 InventoryItem item0 = nullptr;
 new ArrayList();

 for (int int0 = 0; int0 < items.size(); int0++) {
 InventoryItem item1 = (InventoryItem)items.get(int0);
 if (item1.isWaterSource() && !item1.isBeingFilled() && !item1.isTaintedWater()) {
 if (item1 instanceof Drainable) {
 if (((Drainable)item1).getUsedDelta() > 0.0F) {
 item0 = item1;
 break;
 }
 } else if (!(item1 instanceof InventoryContainer) {
 item0 = item1;
 break;
 }
 }
 }

 return item0;
 }

 public List<String> getKnownRecipes() {
 return this->knownRecipes;
 }

 bool isRecipeKnown(Recipe recipe) {
 return DebugOptions.instance.CheatRecipeKnowAll.getValue()
 ? true
 : !recipe.needToBeLearn() || this->getKnownRecipes().contains(recipe.getOriginalname());
 }

 bool isRecipeKnown(const std::string& name) {
 Recipe recipe = ScriptManager.instance.getRecipe(name);
 if (recipe.empty()) {
 return DebugOptions.instance.CheatRecipeKnowAll.getValue() ? true : this->getKnownRecipes().contains(name);
 } else {
 return this->isRecipeKnown(recipe);
 }
 }

 bool learnRecipe(const std::string& name) {
 if (!this->isRecipeKnown(name) {
 this->getKnownRecipes().add(name);
 return true;
 } else {
 return false;
 }
 }

 void addKnownMediaLine(const std::string& guid) {
 if (!StringUtils.isNullOrWhitespace(guid) {
 this->knownMediaLines.add(guid.trim());
 }
 }

 void removeKnownMediaLine(const std::string& guid) {
 if (!StringUtils.isNullOrWhitespace(guid) {
 this->knownMediaLines.remove(guid.trim());
 }
 }

 void clearKnownMediaLines() {
 this->knownMediaLines.clear();
 }

 bool isKnownMediaLine(const std::string& guid) {
 return StringUtils.isNullOrWhitespace(guid) ? false : this->knownMediaLines.contains(guid.trim());
 }

 void saveKnownMediaLines(ByteBuffer byteBuffer) {
 byteBuffer.putShort((short)this->knownMediaLines.size());

 for (String string : this->knownMediaLines) {
 GameWindow.WriteStringUTF(byteBuffer, string);
 }
 }

 void loadKnownMediaLines(ByteBuffer byteBuffer, int var2) {
 this->knownMediaLines.clear();
 short short0 = byteBuffer.getShort();

 for (int int0 = 0; int0 < short0; int0++) {
 std::string string = GameWindow.ReadStringUTF(byteBuffer);
 this->knownMediaLines.add(string);
 }
 }

 bool isMoving() {
 return this instanceof IsoPlayer && !((IsoPlayer)this).isAttackAnimThrowTimeOut() ? false : this->m_isMoving;
 }

 bool isBehaviourMoving() {
 State state = this->getCurrentState();
 return state != nullptr && state.isMoving(this);
 }

 bool isPlayerMoving() {
 return false;
 }

 void setMoving(bool val) {
 this->m_isMoving = val;
 if (GameClient.bClient && this instanceof IsoPlayer && ((IsoPlayer)this).bRemote) {
 ((IsoPlayer)this).m_isPlayerMoving = val;
 ((IsoPlayer)this).setJustMoved(val);
 }
 }

 bool isFacingNorthWesterly() {
 return this->dir == IsoDirections.W || this->dir == IsoDirections.NW || this->dir == IsoDirections.N || this->dir == IsoDirections.NE;
 }

 bool isAttacking() {
 return false;
 }

 bool isZombieAttacking() {
 return false;
 }

 bool isZombieAttacking(IsoMovingObject other) {
 return false;
 }

 bool isZombieThumping() {
 return this->isZombie() ? this->getCurrentState() == ThumpState.instance() : false;
 }

 int compareMovePriority(IsoGameCharacter other) {
 if (other.empty()) {
 return 1;
 } else if (this->isZombieThumping() && !other.isZombieThumping()) {
 return 1;
 } else if (!this->isZombieThumping() && other.isZombieThumping()) {
 return -1;
 } else if (other instanceof IsoPlayer) {
 return GameClient.bClient && this->isZombieAttacking(other) ? -1 : 0;
 } else if (this->isZombieAttacking() && !other.isZombieAttacking()) {
 return 1;
 } else if (!this->isZombieAttacking() && other.isZombieAttacking()) {
 return -1;
 } else if (this->isBehaviourMoving() && !other.isBehaviourMoving()) {
 return 1;
 } else if (!this->isBehaviourMoving() && other.isBehaviourMoving()) {
 return -1;
 } else if (this->isFacingNorthWesterly() && !other.isFacingNorthWesterly()) {
 return 1;
 } else {
 return !this->isFacingNorthWesterly() && other.isFacingNorthWesterly() ? -1 : 0;
 }
 }

 long playSound(const std::string& file) {
 return this->getEmitter().playSound(file);
 }

 long playSoundLocal(const std::string& file) {
 return this->getEmitter().playSoundImpl(file, nullptr);
 }

 void stopOrTriggerSound(long eventInstance) {
 this->getEmitter().stopOrTriggerSound(eventInstance);
 }

 void addWorldSoundUnlessInvisible(int radius, int volume, bool bStressHumans) {
 if (!this->isInvisible()) {
 WorldSoundManager.instance.addSound(this, (int)this->getX(), (int)this->getY(), (int)this->getZ(), radius, volume, bStressHumans);
 }
 }

 bool isKnownPoison(InventoryItem item) {
 if (item.hasTag("NoDetect")) {
 return false;
 } else if (item instanceof Food food) {
 if (food.getPoisonPower() <= 0) {
 return false;
 } else if (food.getHerbalistType() != nullptr && !food.getHerbalistType().empty()) {
 return this->isRecipeKnown("Herbalist");
 } else {
 return food.getPoisonDetectionLevel() >= 0 && this->getPerkLevel(PerkFactory.Perks.Cooking) >= 10 - food.getPoisonDetectionLevel()
 ? true
 : food.getPoisonLevelForRecipe() != nullptr;
 }
 } else {
 return false;
 }
 }

 int getLastHourSleeped() {
 return this->lastHourSleeped;
 }

 void setLastHourSleeped(int _lastHourSleeped) {
 this->lastHourSleeped = _lastHourSleeped;
 }

 void setTimeOfSleep(float _timeOfSleep) {
 this->timeOfSleep = _timeOfSleep;
 }

 void setDelayToSleep(float delay) {
 this->delayToActuallySleep = delay;
 }

 std::string getBedType() {
 return this->bedType;
 }

 void setBedType(const std::string& _bedType) {
 this->bedType = _bedType;
 }

 void enterVehicle(BaseVehicle v, int seat, Vector3f offset) {
 if (this->vehicle != nullptr) {
 this->vehicle.exit(this);
 }

 if (v != nullptr) {
 v.enter(seat, this, offset);
 }
 }

 float Hit(BaseVehicle _vehicle, float speed, bool isHitFromBehind, float hitDirX, float hitDirY) {
 this->setHitFromBehind(isHitFromBehind);
 if (GameClient.bClient) {
 this->setAttackedBy(GameClient.IDToPlayerMap.get(_vehicle.getNetPlayerId()));
 } else if (GameServer.bServer) {
 this->setAttackedBy(GameServer.IDToPlayerMap.get(_vehicle.getNetPlayerId()));
 } else {
 this->setAttackedBy(_vehicle.getDriver());
 }

 this->getHitDir().set(hitDirX, hitDirY);
 if (!this->isKnockedDown()) {
 this->setHitForce(Math.max(0.5F, speed * 0.15F);
 } else {
 this->setHitForce(Math.min(2.5F, speed * 0.15F);
 }

 if (GameClient.bClient) {
 HitReactionNetworkAI.CalcHitReactionVehicle(this, _vehicle);
 }

 DebugLog.Damage
 .noise(
 "Vehicle id=%d hit %s id=%d: speed=%f force=%f hitDir=%s",
 _vehicle.getId(),
 this->getClass().getSimpleName(),
 this->getOnlineID(),
 speed,
 this->getHitForce(),
 this->getHitDir()
 );
 return this->getHealth();
 }

 public PolygonalMap2.Path getPath2() {
 return this->path2;
 }

 void setPath2(PolygonalMap2.Path path) {
 this->path2 = path;
 }

 PathFindBehavior2 getPathFindBehavior2() {
 return this->pfb2;
 }

 MapKnowledge getMapKnowledge() {
 return this->mapKnowledge;
 }

 IsoObject getBed() {
 return this->isAsleep() ? this->bed : nullptr;
 }

 void setBed(IsoObject _bed) {
 this->bed = _bed;
 }

 bool avoidDamage() {
 return this->m_avoidDamage;
 }

 void setAvoidDamage(bool avoid) {
 this->m_avoidDamage = avoid;
 }

 bool isReading() {
 return this->isReading;
 }

 void setReading(bool _isReading) {
 this->isReading = _isReading;
 }

 float getTimeSinceLastSmoke() {
 return this->timeSinceLastSmoke;
 }

 void setTimeSinceLastSmoke(float _timeSinceLastSmoke) {
 this->timeSinceLastSmoke = PZMath.clamp(_timeSinceLastSmoke, 0.0F, 10.0F);
 }

 bool isInvisible() {
 return this->m_invisible;
 }

 void setInvisible(bool b) {
 this->m_invisible = b;
 }

 bool isDriving() {
 return this->getVehicle() != nullptr && this->getVehicle().getDriver() == this && !this->getVehicle().isStopped();
 }

 bool isInARoom() {
 return this->square != nullptr && this->square.isInARoom();
 }

 bool isGodMod() {
 return this->m_godMod;
 }

 void setGodMod(bool b) {
 if (!this->isDead()) {
 this->m_godMod = b;
 if (this instanceof IsoPlayer && GameClient.bClient && ((IsoPlayer)this).isLocalPlayer()) {
 this->updateMovementRates();
 GameClient.sendPlayerInjuries((IsoPlayer)this);
 GameClient.sendPlayerDamage((IsoPlayer)this);
 }
 }
 }

 bool isUnlimitedCarry() {
 return this->unlimitedCarry;
 }

 void setUnlimitedCarry(bool _unlimitedCarry) {
 this->unlimitedCarry = _unlimitedCarry;
 }

 bool isBuildCheat() {
 return this->buildCheat;
 }

 void setBuildCheat(bool _buildCheat) {
 this->buildCheat = _buildCheat;
 }

 bool isFarmingCheat() {
 return this->farmingCheat;
 }

 void setFarmingCheat(bool b) {
 this->farmingCheat = b;
 }

 bool isHealthCheat() {
 return this->healthCheat;
 }

 void setHealthCheat(bool _healthCheat) {
 this->healthCheat = _healthCheat;
 }

 bool isMechanicsCheat() {
 return this->mechanicsCheat;
 }

 void setMechanicsCheat(bool _mechanicsCheat) {
 this->mechanicsCheat = _mechanicsCheat;
 }

 bool isMovablesCheat() {
 return this->movablesCheat;
 }

 void setMovablesCheat(bool b) {
 this->movablesCheat = b;
 }

 bool isTimedActionInstantCheat() {
 return this->timedActionInstantCheat;
 }

 void setTimedActionInstantCheat(bool b) {
 this->timedActionInstantCheat = b;
 }

 bool isTimedActionInstant() {
 return Core.bDebug && DebugOptions.instance.CheatTimedActionInstant.getValue() ? true : this->isTimedActionInstantCheat();
 }

 bool isShowAdminTag() {
 return this->showAdminTag;
 }

 void setShowAdminTag(bool _showAdminTag) {
 this->showAdminTag = _showAdminTag;
 }

 /**
 * Description copied from interface: IAnimationVariableSource
 */
 IAnimationVariableSlot getVariable(AnimationVariableHandle handle) {
 return this->getGameVariablesInternal().getVariable(handle);
 }

 /**
 * Description copied from interface: IAnimationVariableSource
 */
 IAnimationVariableSlot getVariable(const std::string& key) {
 return this->getGameVariablesInternal().getVariable(key);
 }

 /**
 * Description copied from interface: IAnimationVariableMap
 */
 IAnimationVariableSlot getOrCreateVariable(const std::string& key) {
 return this->getGameVariablesInternal().getOrCreateVariable(key);
 }

 /**
 * Description copied from interface: IAnimationVariableMap
 */
 void setVariable(IAnimationVariableSlot var) {
 this->getGameVariablesInternal().setVariable(var);
 }

 void setVariable(const std::string& key, const std::string& value) {
 this->getGameVariablesInternal().setVariable(key, value);
 }

 void setVariable(const std::string& key, bool value) {
 this->getGameVariablesInternal().setVariable(key, value);
 }

 void setVariable(const std::string& key, float value) {
 this->getGameVariablesInternal().setVariable(key, value);
 }

 void setVariable(const std::string& string, AnimationVariableSlotCallbackBool.CallbackGetStrongTyped callbackGetStrongTyped) {
 this->getGameVariablesInternal().setVariable(string, callbackGetStrongTyped);
 }

 protected void setVariable(
 String string,
 AnimationVariableSlotCallbackBool.CallbackGetStrongTyped callbackGetStrongTyped,
 AnimationVariableSlotCallbackBool.CallbackSetStrongTyped callbackSetStrongTyped
 ) {
 this->getGameVariablesInternal().setVariable(string, callbackGetStrongTyped, callbackSetStrongTyped);
 }

 void setVariable(const std::string& string, AnimationVariableSlotCallbackString.CallbackGetStrongTyped callbackGetStrongTyped) {
 this->getGameVariablesInternal().setVariable(string, callbackGetStrongTyped);
 }

 protected void setVariable(
 String string,
 AnimationVariableSlotCallbackString.CallbackGetStrongTyped callbackGetStrongTyped,
 AnimationVariableSlotCallbackString.CallbackSetStrongTyped callbackSetStrongTyped
 ) {
 this->getGameVariablesInternal().setVariable(string, callbackGetStrongTyped, callbackSetStrongTyped);
 }

 void setVariable(const std::string& string, AnimationVariableSlotCallbackFloat.CallbackGetStrongTyped callbackGetStrongTyped) {
 this->getGameVariablesInternal().setVariable(string, callbackGetStrongTyped);
 }

 protected void setVariable(
 String string,
 AnimationVariableSlotCallbackFloat.CallbackGetStrongTyped callbackGetStrongTyped,
 AnimationVariableSlotCallbackFloat.CallbackSetStrongTyped callbackSetStrongTyped
 ) {
 this->getGameVariablesInternal().setVariable(string, callbackGetStrongTyped, callbackSetStrongTyped);
 }

 void setVariable(const std::string& string, AnimationVariableSlotCallbackInt.CallbackGetStrongTyped callbackGetStrongTyped) {
 this->getGameVariablesInternal().setVariable(string, callbackGetStrongTyped);
 }

 protected void setVariable(
 String string,
 AnimationVariableSlotCallbackInt.CallbackGetStrongTyped callbackGetStrongTyped,
 AnimationVariableSlotCallbackInt.CallbackSetStrongTyped callbackSetStrongTyped
 ) {
 this->getGameVariablesInternal().setVariable(string, callbackGetStrongTyped, callbackSetStrongTyped);
 }

 /**
 * Strong-typed utility function.
 */
 void setVariable(const std::string& key, bool defaultVal, AnimationVariableSlotCallbackBool.CallbackGetStrongTyped callbackGet) {
 this->getGameVariablesInternal().setVariable(key, defaultVal, callbackGet);
 }

 /**
 * Strong-typed utility function.
 */
 public void setVariable(
 String key,
 boolean defaultVal,
 AnimationVariableSlotCallbackBool.CallbackGetStrongTyped callbackGet,
 AnimationVariableSlotCallbackBool.CallbackSetStrongTyped callbackSet
 ) {
 this->getGameVariablesInternal().setVariable(key, defaultVal, callbackGet, callbackSet);
 }

 /**
 * Strong-typed utility function.
 */
 void setVariable(const std::string& key, const std::string& defaultVal, AnimationVariableSlotCallbackString.CallbackGetStrongTyped callbackGet) {
 this->getGameVariablesInternal().setVariable(key, defaultVal, callbackGet);
 }

 /**
 * Strong-typed utility function.
 */
 public void setVariable(
 String key,
 String defaultVal,
 AnimationVariableSlotCallbackString.CallbackGetStrongTyped callbackGet,
 AnimationVariableSlotCallbackString.CallbackSetStrongTyped callbackSet
 ) {
 this->getGameVariablesInternal().setVariable(key, defaultVal, callbackGet, callbackSet);
 }

 /**
 * Strong-typed utility function.
 */
 void setVariable(const std::string& key, float defaultVal, AnimationVariableSlotCallbackFloat.CallbackGetStrongTyped callbackGet) {
 this->getGameVariablesInternal().setVariable(key, defaultVal, callbackGet);
 }

 /**
 * Strong-typed utility function.
 */
 public void setVariable(
 String key,
 float defaultVal,
 AnimationVariableSlotCallbackFloat.CallbackGetStrongTyped callbackGet,
 AnimationVariableSlotCallbackFloat.CallbackSetStrongTyped callbackSet
 ) {
 this->getGameVariablesInternal().setVariable(key, defaultVal, callbackGet, callbackSet);
 }

 /**
 * Strong-typed utility function.
 */
 void setVariable(const std::string& key, int defaultVal, AnimationVariableSlotCallbackInt.CallbackGetStrongTyped callbackGet) {
 this->getGameVariablesInternal().setVariable(key, defaultVal, callbackGet);
 }

 /**
 * Strong-typed utility function.
 */
 public void setVariable(
 String key,
 int defaultVal,
 AnimationVariableSlotCallbackInt.CallbackGetStrongTyped callbackGet,
 AnimationVariableSlotCallbackInt.CallbackSetStrongTyped callbackSet
 ) {
 this->getGameVariablesInternal().setVariable(key, defaultVal, callbackGet, callbackSet);
 }

 void clearVariable(const std::string& key) {
 this->getGameVariablesInternal().clearVariable(key);
 }

 void clearVariables() {
 this->getGameVariablesInternal().clearVariables();
 }

 /**
 * Description copied from interface: IAnimationVariableSource
 */
 std::string getVariableString(const std::string& name) {
 return this->getGameVariablesInternal().getVariableString(name);
 }

 std::string getFootInjuryType() {
 if (!(this instanceof IsoPlayer) {
 return "";
 } else {
 BodyPart bodyPart0 = this->getBodyDamage().getBodyPart(BodyPartType.Foot_L);
 BodyPart bodyPart1 = this->getBodyDamage().getBodyPart(BodyPartType.Foot_R);
 if (!this->bRunning) {
 if (bodyPart0.haveBullet()
 || bodyPart0.getBurnTime() > 5.0F
 || bodyPart0.bitten()
 || bodyPart0.deepWounded()
 || bodyPart0.isSplint()
 || bodyPart0.getFractureTime() > 0.0F
 || bodyPart0.haveGlass()) {
 return "leftheavy";
 }

 if (bodyPart1.haveBullet()
 || bodyPart1.getBurnTime() > 5.0F
 || bodyPart1.bitten()
 || bodyPart1.deepWounded()
 || bodyPart1.isSplint()
 || bodyPart1.getFractureTime() > 0.0F
 || bodyPart1.haveGlass()) {
 return "rightheavy";
 }
 }

 if (bodyPart0.getScratchTime() > 5.0F || bodyPart0.getCutTime() > 7.0F || bodyPart0.getBurnTime() > 0.0F) {
 return "leftlight";
 } else {
 return !(bodyPart1.getScratchTime() > 5.0F) && !(bodyPart1.getCutTime() > 7.0F) && !(bodyPart1.getBurnTime() > 0.0F) ? "" : "rightlight";
 }
 }
 }

 /**
 * Description copied from interface: IAnimationVariableSource
 */
 float getVariableFloat(const std::string& name, float defaultVal) {
 return this->getGameVariablesInternal().getVariableFloat(name, defaultVal);
 }

 /**
 * Description copied from interface: IAnimationVariableSource
 */
 bool getVariableBoolean(const std::string& name) {
 return this->getGameVariablesInternal().getVariableBoolean(name);
 }

 /**
 * Returns the specified variable, as a boolean. Attempts to convert the string variable to a boolean. If that fails, or if variable not found, returns defaultVal
 */
 bool getVariableBoolean(const std::string& key, bool defaultVal) {
 return this->getGameVariablesInternal().getVariableBoolean(this->name, defaultVal);
 }

 /**
 * Compares (ignoring case) the value of the specified variable. Returns TRUE if they match.
 */
 bool isVariable(const std::string& name, const std::string& val) {
 return this->getGameVariablesInternal().isVariable(name, val);
 }

 bool containsVariable(const std::string& name) {
 return this->getGameVariablesInternal().containsVariable(name);
 }

 /**
 * Description copied from interface: IAnimationVariableSource
 */
 public Iterable<IAnimationVariableSlot> getGameVariables() {
 return this->getGameVariablesInternal().getGameVariables();
 }

 AnimationVariableSource getGameVariablesInternal() {
 return this->m_PlaybackGameVariables != nullptr ? this->m_PlaybackGameVariables : this->m_GameVariables;
 }

 AnimationVariableSource startPlaybackGameVariables() {
 if (this->m_PlaybackGameVariables != nullptr) {
 DebugLog.General.error("Error! PlaybackGameVariables is already active.");
 return this->m_PlaybackGameVariables;
 } else {
 AnimationVariableSource animationVariableSource = new AnimationVariableSource();

 for (IAnimationVariableSlot iAnimationVariableSlot : this->getGameVariables()) {
 AnimationVariableType animationVariableType = iAnimationVariableSlot.getType();
 switch (animationVariableType) {
 case String:
 animationVariableSource.setVariable(iAnimationVariableSlot.getKey(), iAnimationVariableSlot.getValueString());
 break;
 case Float:
 animationVariableSource.setVariable(iAnimationVariableSlot.getKey(), iAnimationVariableSlot.getValueFloat());
 break;
 case Boolean:
 animationVariableSource.setVariable(iAnimationVariableSlot.getKey(), iAnimationVariableSlot.getValueBool());
 case Void:
 break;
 default:
 DebugLog.General.error("Error! Variable type not handled: %s", animationVariableType.toString());
 }
 }

 this->m_PlaybackGameVariables = animationVariableSource;
 return this->m_PlaybackGameVariables;
 }
 }

 void endPlaybackGameVariables(AnimationVariableSource playbackVars) {
 if (this->m_PlaybackGameVariables != playbackVars) {
 DebugLog.General.error("Error! Playback GameVariables do not match.");
 }

 this->m_PlaybackGameVariables = nullptr;
 }

 void playbackSetCurrentStateSnapshot(ActionStateSnapshot snapshot) {
 if (this->actionContext != nullptr) {
 this->actionContext.setPlaybackStateSnapshot(snapshot);
 }
 }

 ActionStateSnapshot playbackRecordCurrentStateSnapshot() {
 return this->actionContext.empty() ? nullptr : this->actionContext.getPlaybackStateSnapshot();
 }

 std::string GetVariable(const std::string& key) {
 return this->getVariableString(key);
 }

 void SetVariable(const std::string& key, const std::string& value) {
 this->setVariable(key, value);
 }

 void ClearVariable(const std::string& key) {
 this->clearVariable(key);
 }

 void actionStateChanged(ActionContext sender) {
 std::vector arrayList0 = IsoGameCharacter.L_actionStateChanged.stateNames;
 PZArrayUtil.listConvert(sender.getChildStates(), arrayList0, actionState -> actionState.name);
 this->advancedAnimator.SetState(sender.getCurrentStateName(), arrayList0);

 try {
 this->stateMachine.activeStateChanged++;
 State state = this->m_stateUpdateLookup.get(sender.getCurrentStateName().toLowerCase());
 if (state.empty()) {
 state = this->defaultState;
 }

 std::vector arrayList1 = IsoGameCharacter.L_actionStateChanged.states;
 PZArrayUtil.listConvert(
 sender.getChildStates(), arrayList1, this->m_stateUpdateLookup, (actionState, hashMap) -> hashMap.get(actionState.name.toLowerCase())
 );
 this->stateMachine.changeState(state, arrayList1);
 } finally {
 this->stateMachine.activeStateChanged--;
 }
 }

 bool isFallOnFront() {
 return this->fallOnFront;
 }

 void setFallOnFront(bool _fallOnFront) {
 this->fallOnFront = _fallOnFront;
 }

 bool isHitFromBehind() {
 return this->hitFromBehind;
 }

 void setHitFromBehind(bool _hitFromBehind) {
 this->hitFromBehind = _hitFromBehind;
 }

 void reportEvent(const std::string& name) {
 this->actionContext.reportEvent(name);
 }

 void StartTimedActionAnim(const std::string& event) {
 this->StartTimedActionAnim(event, nullptr);
 }

 void StartTimedActionAnim(const std::string& event, const std::string& type) {
 this->reportEvent(event);
 if (type != nullptr) {
 this->setVariable("TimedActionType", type);
 }

 this->resetModelNextFrame();
 }

 void StopTimedActionAnim() {
 this->clearVariable("TimedActionType");
 this->reportEvent("Event_TA_Exit");
 this->resetModelNextFrame();
 }

 bool hasHitReaction() {
 return !StringUtils.isNullOrEmpty(this->getHitReaction());
 }

 std::string getHitReaction() {
 return this->hitReaction;
 }

 void setHitReaction(const std::string& _hitReaction) {
 this->hitReaction = _hitReaction;
 }

 void CacheEquipped() {
 this->cacheEquiped[0] = this->getPrimaryHandItem();
 this->cacheEquiped[1] = this->getSecondaryHandItem();
 }

 InventoryItem GetPrimaryEquippedCache() {
 return this->cacheEquiped[0] != nullptr && this->inventory.contains(this->cacheEquiped[0]) ? this->cacheEquiped[0] : nullptr;
 }

 InventoryItem GetSecondaryEquippedCache() {
 return this->cacheEquiped[1] != nullptr && this->inventory.contains(this->cacheEquiped[1]) ? this->cacheEquiped[1] : nullptr;
 }

 void ClearEquippedCache() {
 this->cacheEquiped[0] = nullptr;
 this->cacheEquiped[1] = nullptr;
 }

 bool isBehind(IsoGameCharacter chr) {
 Vector2 vector0 = tempVector2_1.set(this->getX(), this->getY());
 Vector2 vector1 = tempVector2_2.set(chr.getX(), chr.getY());
 vector1.x = vector1.x - vector0.x;
 vector1.y = vector1.y - vector0.y;
 Vector2 vector2 = chr.getForwardDirection();
 vector1.normalize();
 vector2.normalize();
 float float0 = vector1.dot(vector2);
 return float0 > 0.6;
 }

 void resetEquippedHandsModels() {
 if (!GameServer.bServer || ServerGUI.isCreated()) {
 if (this->hasActiveModel()) {
 ModelManager.instance.ResetEquippedNextFrame(this);
 }
 }
 }

 AnimatorDebugMonitor getDebugMonitor() {
 return this->advancedAnimator.getDebugMonitor();
 }

 void setDebugMonitor(AnimatorDebugMonitor monitor) {
 this->advancedAnimator.setDebugMonitor(monitor);
 }

 bool isAimAtFloor() {
 return this->bAimAtFloor;
 }

 void setAimAtFloor(bool b) {
 this->bAimAtFloor = b;
 }

 std::string testDotSide(IsoMovingObject target) {
 Vector2 vector0 = this->getLookVector(IsoGameCharacter.l_testDotSide.v1);
 Vector2 vector1 = IsoGameCharacter.l_testDotSide.v2.set(this->getX(), this->getY());
 Vector2 vector2 = IsoGameCharacter.l_testDotSide.v3.set(target.x - vector1.x, target.y - vector1.y);
 vector2.normalize();
 float float0 = Vector2.dot(vector2.x, vector2.y, vector0.x, vector0.y);
 if (float0 > 0.7) {
 return "FRONT";
 } else if (float0 < 0.0F && float0 < -0.5) {
 return "BEHIND";
 } else {
 float float1 = target.x;
 float float2 = target.y;
 float float3 = vector1.x;
 float float4 = vector1.y;
 float float5 = vector1.x + vector0.x;
 float float6 = vector1.y + vector0.y;
 float float7 = (float1 - float3) * (float6 - float4) - (float2 - float4) * (float5 - float3);
 return float7 > 0.0F ? "RIGHT" : "LEFT";
 }
 }

 void addBasicPatch(BloodBodyPartType part) {
 if (this instanceof IHumanVisual) {
 if (part.empty()) {
 part = BloodBodyPartType.FromIndex(Rand.Next(0, BloodBodyPartType.MAX.index()));
 }

 HumanVisual humanVisual = ((IHumanVisual)this).getHumanVisual();
 this->getItemVisuals(tempItemVisuals);
 BloodClothingType.addBasicPatch(part, humanVisual, tempItemVisuals);
 this->bUpdateModelTextures = true;
 this->bUpdateEquippedTextures = true;
 if (!GameServer.bServer && this instanceof IsoPlayer && ((IsoPlayer)this).isLocalPlayer()) {
 LuaEventManager.triggerEvent("OnClothingUpdated", this);
 }
 }
 }

 bool addHole(BloodBodyPartType part) {
 return this->addHole(part, false);
 }

 bool addHole(BloodBodyPartType part, bool allLayers) {
 if (!(this instanceof IHumanVisual) {
 return false;
 } else {
 if (part.empty()) {
 part = BloodBodyPartType.FromIndex(OutfitRNG.Next(0, BloodBodyPartType.MAX.index()));
 }

 HumanVisual humanVisual = ((IHumanVisual)this).getHumanVisual();
 this->getItemVisuals(tempItemVisuals);
 bool boolean0 = BloodClothingType.addHole(part, humanVisual, tempItemVisuals, allLayers);
 this->bUpdateModelTextures = true;
 if (!GameServer.bServer && this instanceof IsoPlayer && ((IsoPlayer)this).isLocalPlayer()) {
 LuaEventManager.triggerEvent("OnClothingUpdated", this);
 if (GameClient.bClient) {
 GameClient.instance.sendClothing((IsoPlayer)this, "", nullptr);
 }
 }

 return boolean0;
 }
 }

 void addDirt(BloodBodyPartType part, int nbr, bool allLayers) {
 HumanVisual humanVisual = ((IHumanVisual)this).getHumanVisual();
 if (nbr.empty()) {
 nbr = OutfitRNG.Next(5, 10);
 }

 bool boolean0 = false;
 if (part.empty()) {
 boolean0 = true;
 }

 this->getItemVisuals(tempItemVisuals);

 for (int int0 = 0; int0 < nbr; int0++) {
 if (boolean0) {
 part = BloodBodyPartType.FromIndex(OutfitRNG.Next(0, BloodBodyPartType.MAX.index()));
 }

 BloodClothingType.addDirt(part, humanVisual, tempItemVisuals, allLayers);
 }

 this->bUpdateModelTextures = true;
 if (!GameServer.bServer && this instanceof IsoPlayer && ((IsoPlayer)this).isLocalPlayer()) {
 LuaEventManager.triggerEvent("OnClothingUpdated", this);
 }
 }

 void addBlood(BloodBodyPartType part, bool scratched, bool bitten, bool allLayers) {
 HumanVisual humanVisual = ((IHumanVisual)this).getHumanVisual();
 int int0 = 1;
 bool boolean0 = false;
 if (part.empty()) {
 boolean0 = true;
 }

 if (this->getPrimaryHandItem() instanceof HandWeapon) {
 int0 = ((HandWeapon)this->getPrimaryHandItem()).getSplatNumber();
 if (OutfitRNG.Next(15) < this->getWeaponLevel()) {
 int0--;
 }
 }

 if (bitten) {
 int0 = 20;
 }

 if (scratched) {
 int0 = 5;
 }

 if (this->isZombie()) {
 int0 += 8;
 }

 this->getItemVisuals(tempItemVisuals);

 for (int int1 = 0; int1 < int0; int1++) {
 if (boolean0) {
 part = BloodBodyPartType.FromIndex(OutfitRNG.Next(0, BloodBodyPartType.MAX.index()));
 if (this->getPrimaryHandItem() != nullptr && this->getPrimaryHandItem() instanceof HandWeapon) {
 HandWeapon weapon = (HandWeapon)this->getPrimaryHandItem();
 if (weapon.getBloodLevel() < 1.0F) {
 float float0 = weapon.getBloodLevel() + 0.02F;
 weapon.setBloodLevel(float0);
 this->bUpdateEquippedTextures = true;
 }
 }
 }

 BloodClothingType.addBlood(part, humanVisual, tempItemVisuals, allLayers);
 }

 this->bUpdateModelTextures = true;
 if (!GameServer.bServer && this instanceof IsoPlayer && ((IsoPlayer)this).isLocalPlayer()) {
 LuaEventManager.triggerEvent("OnClothingUpdated", this);
 }
 }

 float getBodyPartClothingDefense(int part, bool bite, bool bullet) {
 float float0 = 0.0F;
 this->getItemVisuals(tempItemVisuals);

 for (int int0 = tempItemVisuals.size() - 1; int0 >= 0; int0--) {
 ItemVisual itemVisual = tempItemVisuals.get(int0);
 Item item0 = itemVisual.getScriptItem();
 if (item0 != nullptr) {
 std::vector arrayList0 = item0.getBloodClothingType();
 if (arrayList0 != nullptr) {
 std::vector arrayList1 = BloodClothingType.getCoveredParts(arrayList0);
 if (arrayList1 != nullptr) {
 InventoryItem item1 = itemVisual.getInventoryItem();
 if (item1.empty()) {
 item1 = InventoryItemFactory.CreateItem(itemVisual.getItemType());
 if (item1.empty()) {
 continue;
 }
 }

 for (int int1 = 0; int1 < arrayList1.size(); int1++) {
 if (item1 instanceof Clothing
 && ((BloodBodyPartType)arrayList1.get(int1).index() == part
 && itemVisual.getHole((BloodBodyPartType)arrayList1.get(int1) == 0.0F) {
 Clothing clothing = (Clothing)item1;
 float0 += clothing.getDefForPart((BloodBodyPartType)arrayList1.get(int1), bite, bullet);
 break;
 }
 }
 }
 }
 }
 }

 return Math.min(100.0F, float0);
 }

 bool isBumped() {
 return !StringUtils.isNullOrWhitespace(this->getBumpType());
 }

 bool isBumpDone() {
 return this->m_isBumpDone;
 }

 void setBumpDone(bool val) {
 this->m_isBumpDone = val;
 }

 bool isBumpFall() {
 return this->m_bumpFall;
 }

 void setBumpFall(bool val) {
 this->m_bumpFall = val;
 }

 bool isBumpStaggered() {
 return this->m_bumpStaggered;
 }

 void setBumpStaggered(bool val) {
 this->m_bumpStaggered = val;
 }

 std::string getBumpType() {
 return this->bumpType;
 }

 void setBumpType(const std::string& _bumpType) {
 if (StringUtils.equalsIgnoreCase(this->bumpType, _bumpType) {
 this->bumpType = _bumpType;
 } else {
 bool boolean0 = this->isBumped();
 this->bumpType = _bumpType;
 bool boolean1 = this->isBumped();
 if (boolean1 != boolean0) {
 this->setBumpStaggered(boolean1);
 }
 }
 }

 std::string getBumpFallType() {
 return this->m_bumpFallType;
 }

 void setBumpFallType(const std::string& val) {
 this->m_bumpFallType = val;
 }

 IsoGameCharacter getBumpedChr() {
 return this->bumpedChr;
 }

 void setBumpedChr(IsoGameCharacter _bumpedChr) {
 this->bumpedChr = _bumpedChr;
 }

 long getLastBump() {
 return this->lastBump;
 }

 void setLastBump(long _lastBump) {
 this->lastBump = _lastBump;
 }

 bool isSitOnGround() {
 return this->sitOnGround;
 }

 void setSitOnGround(bool _sitOnGround) {
 this->sitOnGround = _sitOnGround;
 }

 std::string getUID() {
 return this->m_UID;
 }

 protected HashMap<String, State> getStateUpdateLookup() {
 return this->m_stateUpdateLookup;
 }

 bool isRunning() {
 return this->getMoodles() != nullptr && this->getMoodles().getMoodleLevel(MoodleType.Endurance) >= 3 ? false : this->bRunning;
 }

 void setRunning(bool _bRunning) {
 this->bRunning = _bRunning;
 }

 bool isSprinting() {
 return this->bSprinting && !this->canSprint() ? false : this->bSprinting;
 }

 void setSprinting(bool _bSprinting) {
 this->bSprinting = _bSprinting;
 }

 bool canSprint() {
 if (this instanceof IsoPlayer && !((IsoPlayer)this).isAllowSprint()) {
 return false;
 } else if ("Tutorial" == Core.GameMode) {
 return true;
 } else {
 InventoryItem item = this->getPrimaryHandItem();
 if (item != nullptr && item.isEquippedNoSprint()) {
 return false;
 } else {
 item = this->getSecondaryHandItem();
 return item != nullptr && item.isEquippedNoSprint()
 ? false
 : this->getMoodles() == nullptr || this->getMoodles().getMoodleLevel(MoodleType.Endurance) < 2;
 }
 }
 }

 void postUpdateModelTextures() {
 this->bUpdateModelTextures = true;
 }

 ModelInstanceTextureCreator getTextureCreator() {
 return this->textureCreator;
 }

 void setTextureCreator(ModelInstanceTextureCreator _textureCreator) {
 this->textureCreator = _textureCreator;
 }

 void postUpdateEquippedTextures() {
 this->bUpdateEquippedTextures = true;
 }

 public ArrayList<ModelInstance> getReadyModelData() {
 return this->readyModelData;
 }

 bool getIgnoreMovement() {
 return this->ignoreMovement;
 }

 void setIgnoreMovement(bool _ignoreMovement) {
 if (this instanceof IsoPlayer && _ignoreMovement) {
 ((IsoPlayer)this).networkAI.needToUpdate();
 }

 this->ignoreMovement = _ignoreMovement;
 }

 bool isAutoWalk() {
 return this->bAutoWalk;
 }

 void setAutoWalk(bool b) {
 this->bAutoWalk = b;
 }

 void setAutoWalkDirection(Vector2 v) {
 this->autoWalkDirection.set(v);
 }

 Vector2 getAutoWalkDirection() {
 return this->autoWalkDirection;
 }

 bool isSneaking() {
 return this->getVariableFloat("WalkInjury", 0.0F) > 0.5F ? false : this->bSneaking;
 }

 void setSneaking(bool _bSneaking) {
 this->bSneaking = _bSneaking;
 }

 GameCharacterAIBrain getGameCharacterAIBrain() {
 return this->GameCharacterAIBrain;
 }

 float getMoveDelta() {
 return this->m_moveDelta;
 }

 void setMoveDelta(float moveDelta) {
 this->m_moveDelta = moveDelta;
 }

 float getTurnDelta() {
 if (this->isSprinting()) {
 return this->m_turnDeltaSprinting;
 } else {
 return this->isRunning() ? this->m_turnDeltaRunning : this->m_turnDeltaNormal;
 }
 }

 void setTurnDelta(float m_turnDelta) {
 this->m_turnDeltaNormal = m_turnDelta;
 }

 float getChopTreeSpeed() {
 return (this->Traits.Axeman.isSet() ? 1.25F : 1.0F) * GameTime.getAnimSpeedFix();
 }

 /**
 * Test if we're able to defend a zombie bite Can only happen if zombie is attacking from front Calcul include current weapon skills, fitness & strength
 */
 bool testDefense(IsoZombie zomb) {
 if (this->testDotSide(zomb) == "FRONT") && !zomb.bCrawling && this->getSurroundingAttackingZombies() <= 3) {
 int int0 = 0;
 if ("KnifeDeath" == this->getVariableString("ZombieHitReaction"))) {
 int0 += 30;
 }

 int0 += this->getWeaponLevel() * 3;
 int0 += this->getPerkLevel(PerkFactory.Perks.Fitness) * 2;
 int0 += this->getPerkLevel(PerkFactory.Perks.Strength) * 2;
 int0 -= this->getSurroundingAttackingZombies() * 5;
 int0 -= this->getMoodles().getMoodleLevel(MoodleType.Endurance) * 2;
 int0 -= this->getMoodles().getMoodleLevel(MoodleType.HeavyLoad) * 2;
 int0 -= this->getMoodles().getMoodleLevel(MoodleType.Tired) * 3;
 if (SandboxOptions.instance.Lore.Strength.getValue() == 1) {
 int0 -= 7;
 }

 if (SandboxOptions.instance.Lore.Strength.getValue() == 3) {
 int0 += 7;
 }

 if (Rand.Next(100) < int0) {
 this->setAttackedBy(zomb);
 this->setHitReaction(zomb.getVariableString("PlayerHitReaction") + "Defended");
 return true;
 } else {
 return false;
 }
 } else {
 return false;
 }
 }

 int getSurroundingAttackingZombies() {
 movingStatic.clear();
 IsoGridSquare square = this->getCurrentSquare();
 if (square.empty()) {
 return 0;
 } else {
 movingStatic.addAll(square.getMovingObjects());
 if (square.n != nullptr) {
 movingStatic.addAll(square.n.getMovingObjects());
 }

 if (square.s != nullptr) {
 movingStatic.addAll(square.s.getMovingObjects());
 }

 if (square.e != nullptr) {
 movingStatic.addAll(square.e.getMovingObjects());
 }

 if (square.w != nullptr) {
 movingStatic.addAll(square.w.getMovingObjects());
 }

 if (square.nw != nullptr) {
 movingStatic.addAll(square.nw.getMovingObjects());
 }

 if (square.sw != nullptr) {
 movingStatic.addAll(square.sw.getMovingObjects());
 }

 if (square.se != nullptr) {
 movingStatic.addAll(square.se.getMovingObjects());
 }

 if (square.ne != nullptr) {
 movingStatic.addAll(square.ne.getMovingObjects());
 }

 int int0 = 0;

 for (int int1 = 0; int1 < movingStatic.size(); int1++) {
 IsoZombie zombie0 = Type.tryCastTo(movingStatic.get(int1), IsoZombie.class);
 if (zombie0 != nullptr
 && zombie0.target == this
 && !(this->DistToSquared(zombie0) >= 0.80999994F)
 && (
 zombie0.isCurrentState(AttackState.instance())
 || zombie0.isCurrentState(AttackNetworkState.instance())
 || zombie0.isCurrentState(LungeState.instance())
 || zombie0.isCurrentState(LungeNetworkState.instance())
 )) {
 int0++;
 }
 }

 return int0;
 }
 }

 float checkIsNearWall() {
 if (this->bSneaking && this->getCurrentSquare() != nullptr) {
 IsoGridSquare square0 = this->getCurrentSquare().nav[IsoDirections.N.index()];
 IsoGridSquare square1 = this->getCurrentSquare().nav[IsoDirections.S.index()];
 IsoGridSquare square2 = this->getCurrentSquare().nav[IsoDirections.E.index()];
 IsoGridSquare square3 = this->getCurrentSquare().nav[IsoDirections.W.index()];
 float float0 = 0.0F;
 float float1 = 0.0F;
 if (square0 != nullptr) {
 float0 = square0.getGridSneakModifier(true);
 if (float0 > 1.0F) {
 this->setVariable("nearWallCrouching", true);
 return float0;
 }
 }

 if (square1 != nullptr) {
 float0 = square1.getGridSneakModifier(false);
 float1 = square1.getGridSneakModifier(true);
 if (float0 > 1.0F || float1 > 1.0F) {
 this->setVariable("nearWallCrouching", true);
 return float0 > 1.0F ? float0 : float1;
 }
 }

 if (square2 != nullptr) {
 float0 = square2.getGridSneakModifier(false);
 float1 = square2.getGridSneakModifier(true);
 if (float0 > 1.0F || float1 > 1.0F) {
 this->setVariable("nearWallCrouching", true);
 return float0 > 1.0F ? float0 : float1;
 }
 }

 if (square3 != nullptr) {
 float0 = square3.getGridSneakModifier(false);
 float1 = square3.getGridSneakModifier(true);
 if (float0 > 1.0F || float1 > 1.0F) {
 this->setVariable("nearWallCrouching", true);
 return float0 > 1.0F ? float0 : float1;
 }
 }

 float0 = this->getCurrentSquare().getGridSneakModifier(false);
 if (float0 > 1.0F) {
 this->setVariable("nearWallCrouching", true);
 return float0;
 } else if (this instanceof IsoPlayer && ((IsoPlayer)this).isNearVehicle()) {
 this->setVariable("nearWallCrouching", true);
 return 6.0F;
 } else {
 this->setVariable("nearWallCrouching", false);
 return 0.0F;
 }
 } else {
 this->setVariable("nearWallCrouching", false);
 return 0.0F;
 }
 }

 float getBeenSprintingFor() {
 return this->BeenSprintingFor;
 }

 void setBeenSprintingFor(float beenSprintingFor) {
 if (beenSprintingFor < 0.0F) {
 beenSprintingFor = 0.0F;
 }

 if (beenSprintingFor > 100.0F) {
 beenSprintingFor = 100.0F;
 }

 this->BeenSprintingFor = beenSprintingFor;
 }

 bool isHideWeaponModel() {
 return this->hideWeaponModel;
 }

 void setHideWeaponModel(bool _hideWeaponModel) {
 if (this->hideWeaponModel != _hideWeaponModel) {
 this->hideWeaponModel = _hideWeaponModel;
 this->resetEquippedHandsModels();
 }
 }

 void setIsAiming(bool aIsAiming) {
 if (this->ignoreAimingInput) {
 aIsAiming = false;
 }

 if (this instanceof IsoPlayer && !((IsoPlayer)this).isAttackAnimThrowTimeOut() || this->isAttackAnim() || this->getVariableBoolean("ShoveAnim")) {
 aIsAiming = true;
 }

 this->isAiming = aIsAiming;
 }

 bool isAiming() {
 if (GameClient.bClient && this instanceof IsoPlayer && ((IsoPlayer)this).isLocalPlayer() && DebugOptions.instance.MultiplayerAttackPlayer.getValue()) {
 return false;
 } else {
 return this->isNPC ? this->NPCGetAiming() : this->isAiming;
 }
 }

 void resetBeardGrowingTime() {
 this->beardGrowTiming = (float)this->getHoursSurvived();
 if (GameClient.bClient && this instanceof IsoPlayer) {
 GameClient.instance.sendVisual((IsoPlayer)this);
 }
 }

 void resetHairGrowingTime() {
 this->hairGrowTiming = (float)this->getHoursSurvived();
 if (GameClient.bClient && this instanceof IsoPlayer) {
 GameClient.instance.sendVisual((IsoPlayer)this);
 }
 }

 void fallenOnKnees() {
 if (!(this instanceof IsoPlayer) || ((IsoPlayer)this).isLocalPlayer()) {
 if (!this->isInvincible()) {
 this->helmetFall(false);
 BloodBodyPartType bloodBodyPartType0 = BloodBodyPartType.FromIndex(
 Rand.Next(BloodBodyPartType.Hand_L.index(), BloodBodyPartType.Torso_Upper.index())
 );
 if (Rand.NextBool(2) {
 bloodBodyPartType0 = BloodBodyPartType.FromIndex(Rand.Next(BloodBodyPartType.UpperLeg_L.index(), BloodBodyPartType.Back.index()));
 }

 for (int int0 = 0; int0 < 4; int0++) {
 BloodBodyPartType bloodBodyPartType1 = BloodBodyPartType.FromIndex(
 Rand.Next(BloodBodyPartType.Hand_L.index(), BloodBodyPartType.Torso_Upper.index())
 );
 if (Rand.NextBool(2) {
 bloodBodyPartType1 = BloodBodyPartType.FromIndex(Rand.Next(BloodBodyPartType.UpperLeg_L.index(), BloodBodyPartType.Back.index()));
 }

 this->addDirt(bloodBodyPartType1, Rand.Next(2, 6), false);
 }

 if (Rand.NextBool(2) {
 if (Rand.NextBool(4) {
 this->dropHandItems();
 }

 this->addHole(bloodBodyPartType0);
 this->addBlood(bloodBodyPartType0, true, false, false);
 BodyPart bodyPart = this->getBodyDamage().getBodyPart(BodyPartType.FromIndex(bloodBodyPartType0.index()));
 if (bodyPart.scratched()) {
 bodyPart.generateDeepWound();
 } else {
 bodyPart.setScratched(true, true);
 }
 }
 }
 }
 }

 void addVisualDamage(const std::string& itemType) {
 this->addBodyVisualFromItemType("Base." + itemType);
 }

 ItemVisual addBodyVisualFromItemType(const std::string& string) {
 Item item = ScriptManager.instance.getItem(string);
 return item != nullptr && !StringUtils.isNullOrWhitespace(item.getClothingItem()) ? this->addBodyVisualFromClothingItemName(item.getClothingItem()) : nullptr;
 }

 ItemVisual addBodyVisualFromClothingItemName(const std::string& string1) {
 IHumanVisual iHumanVisual = Type.tryCastTo(this, IHumanVisual.class);
 if (iHumanVisual.empty()) {
 return nullptr;
 } else {
 std::string string0 = ScriptManager.instance.getItemTypeForClothingItem(string1);
 if (string0.empty()) {
 return nullptr;
 } else {
 Item item = ScriptManager.instance.getItem(string0);
 if (item.empty()) {
 return nullptr;
 } else {
 ClothingItem clothingItem = item.getClothingItemAsset();
 if (clothingItem.empty()) {
 return nullptr;
 } else {
 ClothingItemReference clothingItemReference = new ClothingItemReference();
 clothingItemReference.itemGUID = clothingItem.m_GUID;
 clothingItemReference.randomize();
 ItemVisual itemVisual = new ItemVisual();
 itemVisual.setItemType(string0);
 itemVisual.synchWithOutfit(clothingItemReference);
 if (!this->isDuplicateBodyVisual(itemVisual) {
 ItemVisuals itemVisuals = iHumanVisual.getHumanVisual().getBodyVisuals();
 itemVisuals.add(itemVisual);
 return itemVisual;
 } else {
 return nullptr;
 }
 }
 }
 }
 }
 }

 bool isDuplicateBodyVisual(ItemVisual itemVisual1) {
 IHumanVisual iHumanVisual = Type.tryCastTo(this, IHumanVisual.class);
 if (iHumanVisual.empty()) {
 return false;
 } else {
 ItemVisuals itemVisuals = iHumanVisual.getHumanVisual().getBodyVisuals();

 for (int int0 = 0; int0 < itemVisuals.size(); int0++) {
 ItemVisual itemVisual0 = itemVisuals.get(int0);
 if (itemVisual1.getClothingItemName() == itemVisual0.getClothingItemName())
 && itemVisual1.getTextureChoice() == itemVisual0.getTextureChoice()
 && itemVisual1.getBaseTexture() == itemVisual0.getBaseTexture()) {
 return true;
 }
 }

 return false;
 }
 }

 bool isCriticalHit() {
 return this->isCrit;
 }

 void setCriticalHit(bool _isCrit) {
 this->isCrit = _isCrit;
 }

 float getRunSpeedModifier() {
 return this->runSpeedModifier;
 }

 void startMuzzleFlash() {
 float float0 = GameTime.getInstance().getNight() * 0.8F;
 float0 = Math.max(float0, 0.2F);
 IsoLightSource lightSource = new IsoLightSource(
 (int)this->getX(), (int)this->getY(), (int)this->getZ(), 0.8F * float0, 0.8F * float0, 0.6F * float0, 18, 6
 );
 IsoWorld.instance.CurrentCell.getLamppostPositions().add(lightSource);
 this->m_muzzleFlash = System.currentTimeMillis();
 }

 bool isMuzzleFlash() {
 return Core.bDebug && DebugOptions.instance.ModelRenderMuzzleflash.getValue() ? true : this->m_muzzleFlash > System.currentTimeMillis() - 50L;
 }

 bool isNPC() {
 return this->isNPC;
 }

 void setNPC(bool newvalue) {
 if (newvalue && this->GameCharacterAIBrain.empty()) {
 this->GameCharacterAIBrain = new GameCharacterAIBrain(this);
 }

 this->isNPC = newvalue;
 }

 void NPCSetRunning(bool newvalue) {
 this->GameCharacterAIBrain.HumanControlVars.bRunning = newvalue;
 }

 bool NPCGetRunning() {
 return this->GameCharacterAIBrain.HumanControlVars.bRunning;
 }

 void NPCSetJustMoved(bool newvalue) {
 this->GameCharacterAIBrain.HumanControlVars.JustMoved = newvalue;
 }

 void NPCSetAiming(bool _isAiming) {
 this->GameCharacterAIBrain.HumanControlVars.bAiming = _isAiming;
 }

 bool NPCGetAiming() {
 return this->GameCharacterAIBrain.HumanControlVars.bAiming;
 }

 void NPCSetAttack(bool newvalue) {
 this->GameCharacterAIBrain.HumanControlVars.initiateAttack = newvalue;
 }

 void NPCSetMelee(bool newvalue) {
 this->GameCharacterAIBrain.HumanControlVars.bMelee = newvalue;
 }

 void setMetabolicTarget(Metabolics m) {
 if (m != nullptr) {
 this->setMetabolicTarget(m.getMet());
 }
 }

 void setMetabolicTarget(float target) {
 if (this->getBodyDamage() != nullptr && this->getBodyDamage().getThermoregulator() != nullptr) {
 this->getBodyDamage().getThermoregulator().setMetabolicTarget(target);
 }
 }

 double getThirstMultiplier() {
 return this->getBodyDamage() != nullptr && this->getBodyDamage().getThermoregulator() != nullptr
 ? this->getBodyDamage().getThermoregulator().getFluidsMultiplier()
 : 1.0;
 }

 double getHungerMultiplier() {
 return 1.0;
 }

 double getFatiqueMultiplier() {
 return this->getBodyDamage() != nullptr && this->getBodyDamage().getThermoregulator() != nullptr
 ? this->getBodyDamage().getThermoregulator().getFatigueMultiplier()
 : 1.0;
 }

 float getTimedActionTimeModifier() {
 return 1.0F;
 }

 bool addHoleFromZombieAttacks(BloodBodyPartType part, bool scratch) {
 this->getItemVisuals(tempItemVisuals);
 ItemVisual itemVisual0 = nullptr;

 for (int int0 = tempItemVisuals.size() - 1; int0 >= 0; int0--) {
 ItemVisual itemVisual1 = tempItemVisuals.get(int0);
 Item item = itemVisual1.getScriptItem();
 if (item != nullptr) {
 std::vector arrayList0 = item.getBloodClothingType();
 if (arrayList0 != nullptr) {
 std::vector arrayList1 = BloodClothingType.getCoveredParts(arrayList0);

 for (int int1 = 0; int1 < arrayList1.size(); int1++) {
 BloodBodyPartType bloodBodyPartType = (BloodBodyPartType)arrayList1.get(int1);
 if (part == bloodBodyPartType) {
 itemVisual0 = itemVisual1;
 break;
 }
 }

 if (itemVisual0 != nullptr) {
 break;
 }
 }
 }
 }

 float float0 = 0.0F;
 bool boolean0 = false;
 if (itemVisual0 != nullptr && itemVisual0.getInventoryItem() != nullptr && itemVisual0.getInventoryItem() instanceof Clothing) {
 Clothing clothing = (Clothing)itemVisual0.getInventoryItem();
 Clothing.ClothingPatch clothingPatch = clothing.getPatchType(part);
 float0 = Math.max(30.0F, 100.0F - clothing.getDefForPart(part, !scratch, false) / 1.5F);
 }

 if (Rand.Next(100) < float0) {
 bool boolean1 = this->addHole(part);
 if (boolean1) {
 this->getEmitter().playSoundImpl("ZombieRipClothing", (IsoObject)nullptr);
 }

 boolean0 = true;
 }

 return boolean0;
 }

 void updateBandages() {
 s_bandages.update(this);
 }

 float getTotalBlood() {
 float float0 = 0.0F;
 if (this->getWornItems() == nullptr) {
 return float0;
 } else {
 for (int int0 = 0; int0 < this->getWornItems().size(); int0++) {
 InventoryItem item = this->getWornItems().get(int0).getItem();
 if (item instanceof Clothing) {
 float0 += ((Clothing)item).getBloodlevel();
 }
 }

 return float0 + ((HumanVisual)this->getVisual()).getTotalBlood();
 }
 }

 void attackFromWindowsLunge(IsoZombie zombie) {
 if (!(this->lungeFallTimer > 0.0F)
 && (int)this->getZ() == (int)zombie.getZ()
 && !zombie.isDead()
 && this->getCurrentSquare() != nullptr
 && !this->getCurrentSquare().isDoorBlockedTo(zombie.getCurrentSquare())
 && !this->getCurrentSquare().isWallTo(zombie.getCurrentSquare())
 && !this->getCurrentSquare().isWindowTo(zombie.getCurrentSquare())) {
 if (this->getVehicle() == nullptr) {
 bool boolean0 = this->DoSwingCollisionBoneCheck(zombie, zombie.getAnimationPlayer().getSkinningBoneIndex("Bip01_R_Hand", -1), 1.0F);
 if (boolean0) {
 zombie.playSound("ZombieCrawlLungeHit");
 this->lungeFallTimer = 200.0F;
 this->setIsAiming(false);
 bool boolean1 = false;
 int int0 = 30;
 int0 += this->getMoodles().getMoodleLevel(MoodleType.Endurance) * 3;
 int0 += this->getMoodles().getMoodleLevel(MoodleType.HeavyLoad) * 5;
 int0 -= this->getPerkLevel(PerkFactory.Perks.Fitness) * 2;
 BodyPart bodyPart = this->getBodyDamage().getBodyPart(BodyPartType.Torso_Lower);
 if (bodyPart.getAdditionalPain(true) > 20.0F) {
 int0 = (int)(int0 + (bodyPart.getAdditionalPain(true) - 20.0F) / 10.0F);
 }

 if (this->Traits.Clumsy.isSet()) {
 int0 += 10;
 }

 if (this->Traits.Graceful.isSet()) {
 int0 -= 10;
 }

 if (this->Traits.VeryUnderweight.isSet()) {
 int0 += 20;
 }

 if (this->Traits.Underweight.isSet()) {
 int0 += 10;
 }

 if (this->Traits.Obese.isSet()) {
 int0 -= 10;
 }

 if (this->Traits.Overweight.isSet()) {
 int0 -= 5;
 }

 int0 = Math.max(5, int0);
 this->clearVariable("BumpFallType");
 this->setBumpType("stagger");
 if (Rand.Next(100) < int0) {
 boolean1 = true;
 }

 this->setBumpDone(false);
 this->setBumpFall(boolean1);
 if (zombie.isBehind(this) {
 this->setBumpFallType("pushedBehind");
 } else {
 this->setBumpFallType("pushedFront");
 }

 this->actionContext.reportEvent("wasBumped");
 }
 }
 }
 }

 bool DoSwingCollisionBoneCheck(IsoGameCharacter zombie, int bone, float tempoLengthTest) {
 Model.BoneToWorldCoords(zombie, bone, tempVectorBonePos);
 float float0 = IsoUtils.DistanceToSquared(tempVectorBonePos.x, tempVectorBonePos.y, this->x, this->y);
 return float0 < tempoLengthTest * tempoLengthTest;
 }

 bool isInvincible() {
 return this->invincible;
 }

 void setInvincible(bool _invincible) {
 this->invincible = _invincible;
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
 BaseVehicle vehiclex = chunk.vehicles.get(int6);
 if (vehiclex.getScript() != nullptr
 && (int)this->getZ() == (int)vehiclex.getZ()
 && (
 !(this instanceof IsoPlayer)
 || !((IsoPlayer)this).isLocalPlayer()
 || vehiclex.getTargetAlpha(((IsoPlayer)this).PlayerIndex) != 0.0F
 )
 && !(this->DistToSquared((int)vehiclex.x, (int)vehiclex.y) >= 16.0F) {
 return vehiclex;
 }
 }
 }
 }
 }

 return nullptr;
 }
 }

 IsoGridSquare getSolidFloorAt(int int1, int int2, int int0) {
 while (int0 >= 0) {
 IsoGridSquare square = this->getCell().getGridSquare(int1, int2, int0);
 if (square != nullptr && square.TreatAsSolidFloor()) {
 return square;
 }

 int0--;
 }

 return nullptr;
 }

 void dropHeavyItems() {
 IsoGridSquare square = this->getCurrentSquare();
 if (square != nullptr) {
 InventoryItem item0 = this->getPrimaryHandItem();
 InventoryItem item1 = this->getSecondaryHandItem();
 if (item0 != nullptr || item1 != nullptr) {
 square = this->getSolidFloorAt(square.x, square.y, square.z);
 if (square != nullptr) {
 bool boolean0 = item0 == item1;
 if (this->isHeavyItem(item0) {
 float float0 = Rand.Next(0.1F, 0.9F);
 float float1 = Rand.Next(0.1F, 0.9F);
 float float2 = square.getApparentZ(float0, float1) - square.getZ();
 this->setPrimaryHandItem(nullptr);
 this->getInventory().DoRemoveItem(item0);
 square.AddWorldInventoryItem(item0, float0, float1, float2);
 LuaEventManager.triggerEvent("OnContainerUpdate");
 LuaEventManager.triggerEvent("onItemFall", item0);
 }

 if (this->isHeavyItem(item1) {
 this->setSecondaryHandItem(nullptr);
 if (!boolean0) {
 float float3 = Rand.Next(0.1F, 0.9F);
 float float4 = Rand.Next(0.1F, 0.9F);
 float float5 = square.getApparentZ(float3, float4) - square.getZ();
 this->getInventory().DoRemoveItem(item1);
 square.AddWorldInventoryItem(item1, float3, float4, float5);
 LuaEventManager.triggerEvent("OnContainerUpdate");
 LuaEventManager.triggerEvent("onItemFall", item1);
 }
 }
 }
 }
 }
 }

 bool isHeavyItem(InventoryItem item) {
 if (item.empty()) {
 return false;
 } else if (item instanceof InventoryContainer) {
 return true;
 } else if (item.hasTag("HeavyItem")) {
 return true;
 } else {
 return !item.getType() == "CorpseMale") && !item.getType() == "CorpseFemale") ? item.getType() == "Generator") : true;
 }
 }

 bool isCanShout() {
 return this->canShout;
 }

 void setCanShout(bool _canShout) {
 this->canShout = _canShout;
 }

 bool isUnlimitedEndurance() {
 return this->unlimitedEndurance;
 }

 void setUnlimitedEndurance(bool _unlimitedEndurance) {
 this->unlimitedEndurance = _unlimitedEndurance;
 }

 void addActiveLightItem(InventoryItem item, ArrayList<InventoryItem> arrayList) {
 if (item != nullptr && item.isEmittingLight() && !arrayList.contains(item) {
 arrayList.add(item);
 }
 }

 public ArrayList<InventoryItem> getActiveLightItems(ArrayList<InventoryItem> items) {
 this->addActiveLightItem(this->getSecondaryHandItem(), items);
 this->addActiveLightItem(this->getPrimaryHandItem(), items);
 AttachedItems attachedItemsx = this->getAttachedItems();

 for (int int0 = 0; int0 < attachedItemsx.size(); int0++) {
 InventoryItem item = attachedItemsx.getItemByIndex(int0);
 this->addActiveLightItem(item, items);
 }

 return items;
 }

 SleepingEventData getOrCreateSleepingEventData() {
 if (this->m_sleepingEventData.empty()) {
 this->m_sleepingEventData = std::make_unique<SleepingEventData>();
 }

 return this->m_sleepingEventData;
 }

 void playEmote(const std::string& emote) {
 this->setVariable("emote", emote);
 this->actionContext.reportEvent("EventEmote");
 }

 std::string getAnimationStateName() {
 return this->advancedAnimator.getCurrentStateName();
 }

 std::string getActionStateName() {
 return this->actionContext.getCurrentStateName();
 }

 bool shouldWaitToStartTimedAction() {
 if (this->isSitOnGround()) {
 AdvancedAnimator advancedAnimatorx = this->getAdvancedAnimator();
 if (advancedAnimatorx.getRootLayer() == nullptr) {
 return false;
 } else if (advancedAnimatorx.animSet != nullptr && advancedAnimatorx.animSet.containsState("sitonground")) {
 AnimState animState = advancedAnimatorx.animSet.GetState("sitonground");
 if (!PZArrayUtil.contains(animState.m_Nodes, animNode -> "sit_action".equalsIgnoreCase(animNode.m_Name) {
 return false;
 } else {
 LiveAnimNode liveAnimNode = PZArrayUtil.find(
 advancedAnimatorx.getRootLayer().getLiveAnimNodes(),
 liveAnimNodex -> liveAnimNodex.isActive() && "sit_action".equalsIgnoreCase(liveAnimNodex.getName())
 );
 return liveAnimNode = = nullptr || !liveAnimNode.isMainAnimActive();
 }
 } else {
 return false;
 }
 } else {
 return false;
 }
 }

 void setPersistentOutfitID(int outfitID) {
 this->setPersistentOutfitID(outfitID, false);
 }

 void setPersistentOutfitID(int outfitID, bool init) {
 this->m_persistentOutfitId = outfitID;
 this->m_bPersistentOutfitInit = init;
 }

 int getPersistentOutfitID() {
 return this->m_persistentOutfitId;
 }

 bool isPersistentOutfitInit() {
 return this->m_bPersistentOutfitInit;
 }

 bool isDoingActionThatCanBeCancelled() {
 return false;
 }

 bool isDoDeathSound() {
 return this->doDeathSound;
 }

 void setDoDeathSound(bool _doDeathSound) {
 this->doDeathSound = _doDeathSound;
 }

 void updateEquippedRadioFreq() {
 this->invRadioFreq.clear();

 for (int int0 = 0; int0 < this->getInventory().getItems().size(); int0++) {
 InventoryItem item = this->getInventory().getItems().get(int0);
 if (item instanceof Radio radio
 && radio.getDeviceData() != nullptr
 && radio.getDeviceData().getIsTurnedOn()
 && !radio.getDeviceData().getMicIsMuted()
 && !this->invRadioFreq.contains(radio.getDeviceData().getChannel())) {
 this->invRadioFreq.add(radio.getDeviceData().getChannel());
 }
 }

 for (int int1 = 0; int1 < this->invRadioFreq.size(); int1++) {
 System.out.println(this->invRadioFreq.get(int1);
 }

 if (this instanceof IsoPlayer && GameClient.bClient) {
 GameClient.sendEquippedRadioFreq((IsoPlayer)this);
 }
 }

 FMODParameterList getFMODParameters() {
 return this->fmodParameters;
 }

 void startEvent(long eventInstance, GameSoundClip clip, BitSet parameterSet) {
 FMODParameterList fMODParameterList = this->getFMODParameters();
 std::vector arrayList = clip.eventDescription.parameters;

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 FMOD_STUDIO_PARAMETER_DESCRIPTION fmod_studio_parameter_description = (FMOD_STUDIO_PARAMETER_DESCRIPTION)arrayList.get(int0);
 if (!parameterSet.get(fmod_studio_parameter_description.globalIndex) {
 FMODParameter fMODParameter = fMODParameterList.get(fmod_studio_parameter_description);
 if (fMODParameter != nullptr) {
 fMODParameter.startEventInstance(eventInstance);
 }
 }
 }
 }

 void updateEvent(long eventInstance, GameSoundClip clip) {
 }

 void stopEvent(long eventInstance, GameSoundClip clip, BitSet parameterSet) {
 FMODParameterList fMODParameterList = this->getFMODParameters();
 std::vector arrayList = clip.eventDescription.parameters;

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 FMOD_STUDIO_PARAMETER_DESCRIPTION fmod_studio_parameter_description = (FMOD_STUDIO_PARAMETER_DESCRIPTION)arrayList.get(int0);
 if (!parameterSet.get(fmod_studio_parameter_description.globalIndex) {
 FMODParameter fMODParameter = fMODParameterList.get(fmod_studio_parameter_description);
 if (fMODParameter != nullptr) {
 fMODParameter.stopEventInstance(eventInstance);
 }
 }
 }
 }

 void playBloodSplatterSound() {
 if (this->getEmitter().isPlaying("BloodSplatter")) {
 }

 this->getEmitter().playSoundImpl("BloodSplatter", this);
 }

 void setIgnoreAimingInput(bool b) {
 this->ignoreAimingInput = b;
 }

 void addBlood(float speed) {
 if (!(Rand.Next(10) > speed) {
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
 this->splatBlood(2, 0.3F);
 }
 }

 if (SandboxOptions.instance.BloodLevel.getValue() > 1) {
 this->splatBloodFloorBig();
 this->playBloodSplatterSound();
 }
 }
 }

 bool isKnockedDown() {
 return this->bKnockedDown;
 }

 void setKnockedDown(bool _bKnockedDown) {
 this->bKnockedDown = _bKnockedDown;
 }

 void writeInventory(ByteBuffer b) {
 std::string string = this->isFemale() ? "inventoryfemale" : "inventorymale";
 GameWindow.WriteString(b, string);
 if (this->getInventory() != nullptr) {
 b.put((byte)1);

 try {
 std::vector arrayList = this->getInventory().save(b);
 WornItems wornItemsx = this->getWornItems();
 if (wornItemsx.empty()) {
 uint8_t byte0 = 0;
 b.put((byte)byte0);
 } else {
 int int0 = wornItemsx.size();
 if (int0 > 127) {
 DebugLog.Multiplayer.warn("Too many worn items");
 int0 = 127;
 }

 b.put((byte)int0);

 for (int int1 = 0; int1 < int0; int1++) {
 WornItem wornItem = wornItemsx.get(int1);
 GameWindow.WriteString(b, wornItem.getLocation());
 b.putShort((short)arrayList.indexOf(wornItem.getItem()));
 }
 }

 AttachedItems attachedItemsx = this->getAttachedItems();
 if (attachedItemsx.empty()) {
 bool boolean0 = false;
 b.put((byte)0);
 } else {
 int int2 = attachedItemsx.size();
 if (int2 > 127) {
 DebugLog.Multiplayer.warn("Too many attached items");
 int2 = 127;
 }

 b.put((byte)int2);

 for (int int3 = 0; int3 < int2; int3++) {
 AttachedItem attachedItem = attachedItemsx.get(int3);
 GameWindow.WriteString(b, attachedItem.getLocation());
 b.putShort((short)arrayList.indexOf(attachedItem.getItem()));
 }
 }
 } catch (IOException iOException) {
 DebugLog.Multiplayer.printException(iOException, "WriteInventory error for character " + this->getOnlineID(), LogSeverity.Error);
 }
 } else {
 b.put((byte)0);
 }
 }

 std::string readInventory(ByteBuffer b) {
 std::string string0 = GameWindow.ReadString(b);
 bool boolean0 = b.get() == 1;
 if (boolean0) {
 try {
 std::vector arrayList = this->getInventory().load(b, IsoWorld.getWorldVersion());
 uint8_t byte0 = b.get();

 for (int int0 = 0; int0 < byte0; int0++) {
 std::string string1 = GameWindow.ReadStringUTF(b);
 short short0 = b.getShort();
 if (short0 >= 0 && short0 < arrayList.size() && this->getBodyLocationGroup().getLocation(string1) != nullptr) {
 this->getWornItems().setItem(string1, (InventoryItem)arrayList.get(short0);
 }
 }

 uint8_t byte1 = b.get();

 for (int int1 = 0; int1 < byte1; int1++) {
 std::string string2 = GameWindow.ReadStringUTF(b);
 short short1 = b.getShort();
 if (short1 >= 0 && short1 < arrayList.size() && this->getAttachedLocationGroup().getLocation(string2) != nullptr) {
 this->getAttachedItems().setItem(string2, (InventoryItem)arrayList.get(short1);
 }
 }
 } catch (IOException iOException) {
 DebugLog.Multiplayer.printException(iOException, "ReadInventory error for character " + this->getOnlineID(), LogSeverity.Error);
 }
 }

 return string0;
 }

 void Kill(IsoGameCharacter killer) {
 DebugLog.Death.trace("id=%d", this->getOnlineID());
 this->setAttackedBy(killer);
 this->setHealth(0.0F);
 this->setOnKillDone(true);
 }

 bool shouldDoInventory() {
 return true;
 }

 void die() {
 if (!this->isOnDeathDone()) {
 if (GameClient.bClient) {
 if (this->shouldDoInventory()) {
 this->becomeCorpse();
 } else {
 this->getNetworkCharacterAI().processDeadBody();
 }
 } else {
 this->becomeCorpse();
 }
 }
 }

 void becomeCorpse() {
 DebugLog.Death.trace("id=%d", this->getOnlineID());
 this->Kill(this->getAttackedBy());
 this->setOnDeathDone(true);
 }

 bool shouldBecomeCorpse() {
 if (GameClient.bClient || GameServer.bServer) {
 if (this->getHitReactionNetworkAI().isSetup() || this->getHitReactionNetworkAI().isStarted()) {
 return false;
 }

 if (GameServer.bServer) {
 return this->getNetworkCharacterAI().isSetDeadBody();
 }

 if (GameClient.bClient) {
 return this->isCurrentState(ZombieOnGroundState.instance()) || this->isCurrentState(PlayerOnGroundState.instance());
 }
 }

 return true;
 }

 HitReactionNetworkAI getHitReactionNetworkAI() {
 return nullptr;
 }

 NetworkCharacterAI getNetworkCharacterAI() {
 return nullptr;
 }

 bool isLocal() {
 return !GameClient.bClient && !GameServer.bServer;
 }

 bool isVehicleCollisionActive(BaseVehicle testVehicle) {
 if (!GameClient.bClient) {
 return false;
 } else if (!this->isAlive()) {
 return false;
 } else if (testVehicle.empty()) {
 return false;
 } else if (!testVehicle.shouldCollideWithCharacters()) {
 return false;
 } else if (testVehicle.isNetPlayerAuthorization(BaseVehicle.Authorization.Server) {
 return false;
 } else if (testVehicle.isEngineRunning()
 || testVehicle.getVehicleTowing() != nullptr && testVehicle.getVehicleTowing().isEngineRunning()
 || testVehicle.getVehicleTowedBy() != nullptr && testVehicle.getVehicleTowedBy().isEngineRunning()) {
 if (testVehicle.getDriver() != nullptr
 || testVehicle.getVehicleTowing() != nullptr && testVehicle.getVehicleTowing().getDriver() != nullptr
 || testVehicle.getVehicleTowedBy() != nullptr && testVehicle.getVehicleTowedBy().getDriver() != nullptr) {
 return Math.abs(testVehicle.x - this->x) < 0.01F || Math.abs(testVehicle.y - this->y) < 0.01F
 ? false
 : (!this->isKnockedDown() || this->isOnFloor()) && (this->getHitReactionNetworkAI() == nullptr || !this->getHitReactionNetworkAI().isStarted());
 } else {
 return false;
 }
 } else {
 return false;
 }
 }

 void doHitByVehicle(BaseVehicle baseVehicle, BaseVehicle.HitVars hitVars) {
 if (GameClient.bClient) {
 IsoPlayer player = GameClient.IDToPlayerMap.get(baseVehicle.getNetPlayerId());
 if (player != nullptr) {
 if (player.isLocal()) {
 SoundManager.instance.PlayWorldSound("VehicleHitCharacter", this->getCurrentSquare(), 0.0F, 20.0F, 0.9F, true);
 float float0 = this->Hit(baseVehicle, hitVars.hitSpeed, hitVars.isTargetHitFromBehind, -hitVars.targetImpulse.x, -hitVars.targetImpulse.z);
 GameClient.sendHitVehicle(
 player,
 this,
 baseVehicle,
 float0,
 hitVars.isTargetHitFromBehind,
 hitVars.vehicleDamage,
 hitVars.hitSpeed,
 hitVars.isVehicleHitFromFront
 );
 } else {
 this->getNetworkCharacterAI().resetVehicleHitTimeout();
 }
 }
 } else if (!GameServer.bServer) {
 BaseSoundEmitter baseSoundEmitter = IsoWorld.instance.getFreeEmitter(this->x, this->y, this->z);
 long long0 = baseSoundEmitter.playSound("VehicleHitCharacter");
 baseSoundEmitter.setParameterValue(long0, FMODManager.instance.getParameterDescription("VehicleSpeed"), baseVehicle.getCurrentSpeedKmHour());
 this->Hit(baseVehicle, hitVars.hitSpeed, hitVars.isTargetHitFromBehind, -hitVars.targetImpulse.x, -hitVars.targetImpulse.z);
 }
 }

 bool isSkipResolveCollision() {
 return this instanceof IsoZombie
 && (
 this->isCurrentState(ZombieHitReactionState.instance())
 || this->isCurrentState(ZombieFallDownState.instance())
 || this->isCurrentState(ZombieOnGroundState.instance())
 || this->isCurrentState(StaggerBackState.instance())
 )
 || this instanceof IsoPlayer
 && !this->isLocal()
 && (
 this->isCurrentState(PlayerFallDownState.instance())
 || this->isCurrentState(BumpedState.instance())
 || this->isCurrentState(PlayerKnockedDown.instance())
 || this->isCurrentState(PlayerHitReactionState.instance())
 || this->isCurrentState(PlayerHitReactionPVPState.instance())
 || this->isCurrentState(PlayerOnGroundState.instance())
 );
 }

 bool isAttackAnim() {
 return this->attackAnim;
 }

 void setAttackAnim(bool _attackAnim) {
 this->attackAnim = _attackAnim;
 }

 float getNextAnimationTranslationLength() {
 if (this->getActionContext() != nullptr && this->getAnimationPlayer() != nullptr && this->getAdvancedAnimator() != nullptr) {
 ActionState actionState = this->getActionContext().getNextState();
 if (actionState != nullptr && !StringUtils.isNullOrEmpty(actionState.getName())) {
 std::vector arrayList = new ArrayList();
 this->getAdvancedAnimator().animSet.GetState(actionState.getName()).getAnimNodes(this, arrayList);

 for (auto& animNode : arrayList) if (!StringUtils.isNullOrEmpty(animNode.m_AnimName) {
 AnimationClip animationClip = this->getAnimationPlayer().getSkinningData().AnimationClips.get(animNode.m_AnimName);
 if (animationClip != nullptr) {
 return animationClip.getTranslationLength(animNode.m_deferredBoneAxis);
 }
 }
 }
 }
 }

 return nullptr;
 }

 float calcHitDir(IsoGameCharacter wielder, HandWeapon weapon, Vector2 out) {
 float float0 = this->getNextAnimationTranslationLength();
 out.set(this->getX() - wielder.getX(), this->getY() - wielder.getY()).normalize();
 if (float0.empty()) {
 out.setLength(this->getHitForce() * 0.1F);
 out.scale(weapon.getPushBackMod());
 out.rotate(weapon.HitAngleMod);
 } else {
 out.scale(float0);
 }

 return nullptr;
 }

 void calcHitDir(Vector2 out) {
 out.set(this->getHitDir());
 out.setLength(this->getHitForce());
 }

 Safety getSafety() {
 return this->safety;
 }

 void setSafety(Safety _safety) {
 this->safety.copyFrom(_safety);
 }

 void burnCorpse(IsoDeadBody corpse) {
 if (GameClient.bClient) {
 GameClient.sendBurnCorpse(this->getOnlineID(), corpse.getObjectID());
 } else {
 IsoFireManager.StartFire(corpse.getCell(), corpse.getSquare(), true, 100, 700);
 }
 }

 private static class Bandages {
 HashMap<String, String> bandageTypeMap = std::make_unique<HashMap<>>();
 THashMap<String, InventoryItem> itemMap = std::make_unique<THashMap<>>();

 std::string getBloodBandageType(const std::string& string1) {
 std::string string0 = this->bandageTypeMap.get(string1);
 if (string0.empty()) {
 this->bandageTypeMap.put(string1, string0 = string1 + "_Blood");
 }

 return string0;
 }

 void update(IsoGameCharacter character) {
 if (!GameServer.bServer) {
 BodyDamage bodyDamage = character.getBodyDamage();
 WornItems wornItems = character.getWornItems();
 if (bodyDamage != nullptr && wornItems != nullptr) {
 assert !(character instanceof IsoZombie);

 this->itemMap.clear();

 for (int int0 = 0; int0 < wornItems.size(); int0++) {
 InventoryItem item = wornItems.getItemByIndex(int0);
 if (item != nullptr) {
 this->itemMap.put(item.getFullType(), item);
 }
 }

 for (int int1 = 0; int1 < BodyPartType.ToIndex(BodyPartType.MAX); int1++) {
 BodyPart bodyPart = bodyDamage.getBodyPart(BodyPartType.FromIndex(int1);
 BodyPartLast bodyPartLast = bodyDamage.getBodyPartsLastState(BodyPartType.FromIndex(int1);
 std::string string0 = bodyPart.getType().getBandageModel();
 if (!StringUtils.isNullOrWhitespace(string0) {
 std::string string1 = this->getBloodBandageType(string0);
 if (bodyPart.bandaged() != bodyPartLast.bandaged()) {
 if (bodyPart.bandaged()) {
 if (bodyPart.isBandageDirty()) {
 this->removeBandageModel(character, string0);
 this->addBandageModel(character, string1);
 } else {
 this->removeBandageModel(character, string1);
 this->addBandageModel(character, string0);
 }
 } else {
 this->removeBandageModel(character, string0);
 this->removeBandageModel(character, string1);
 }
 }

 if (bodyPart.bitten() != bodyPartLast.bitten()) {
 if (bodyPart.bitten()) {
 std::string string2 = bodyPart.getType().getBiteWoundModel(character.isFemale());
 if (StringUtils.isNullOrWhitespace(string2) {
 continue;
 }

 this->addBandageModel(character, string2);
 } else {
 this->removeBandageModel(character, bodyPart.getType().getBiteWoundModel(character.isFemale()));
 }
 }

 if (bodyPart.scratched() != bodyPartLast.scratched()) {
 if (bodyPart.scratched()) {
 std::string string3 = bodyPart.getType().getScratchWoundModel(character.isFemale());
 if (StringUtils.isNullOrWhitespace(string3) {
 continue;
 }

 this->addBandageModel(character, string3);
 } else {
 this->removeBandageModel(character, bodyPart.getType().getScratchWoundModel(character.isFemale()));
 }
 }

 if (bodyPart.isCut() != bodyPartLast.isCut()) {
 if (bodyPart.isCut()) {
 std::string string4 = bodyPart.getType().getCutWoundModel(character.isFemale());
 if (!StringUtils.isNullOrWhitespace(string4) {
 this->addBandageModel(character, string4);
 }
 } else {
 this->removeBandageModel(character, bodyPart.getType().getCutWoundModel(character.isFemale()));
 }
 }
 }
 }
 }
 }
 }

 void addBandageModel(IsoGameCharacter character, const std::string& string) {
 if (!this->itemMap.containsKey(string) {
 if (InventoryItemFactory.CreateItem(string) instanceof Clothing clothing) {
 character.getInventory().addItem(clothing);
 character.setWornItem(clothing.getBodyLocation(), clothing);
 character.resetModelNextFrame();
 }
 }
 }

 void removeBandageModel(IsoGameCharacter character, const std::string& string) {
 InventoryItem item = this->itemMap.get(string);
 if (item != nullptr) {
 character.getWornItems().remove(item);
 character.getInventory().Remove(item);
 character.resetModelNextFrame();
 character.onWornItemsChanged();
 if (GameClient.bClient && character instanceof IsoPlayer && ((IsoPlayer)character).isLocalPlayer()) {
 GameClient.instance.sendClothing((IsoPlayer)character, item.getBodyLocation(), item);
 }
 }
 }
 }

 public static enum BodyLocation {
 Head,
 Leg,
 Arm,
 Chest,
 Stomach,
 Foot,
 Hand;
 }

 class CharacterTraits extends TraitCollection {
 public TraitCollection.TraitSlot Obese = this->getTraitSlot("Obese");
 public TraitCollection.TraitSlot Athletic = this->getTraitSlot("Athletic");
 public TraitCollection.TraitSlot Overweight = this->getTraitSlot("Overweight");
 public TraitCollection.TraitSlot Unfit = this->getTraitSlot("Unfit");
 public TraitCollection.TraitSlot Emaciated = this->getTraitSlot("Emaciated");
 public TraitCollection.TraitSlot Graceful = this->getTraitSlot("Graceful");
 public TraitCollection.TraitSlot Clumsy = this->getTraitSlot("Clumsy");
 public TraitCollection.TraitSlot Strong = this->getTraitSlot("Strong");
 public TraitCollection.TraitSlot Weak = this->getTraitSlot("Weak");
 public TraitCollection.TraitSlot VeryUnderweight = this->getTraitSlot("Very Underweight");
 public TraitCollection.TraitSlot Underweight = this->getTraitSlot("Underweight");
 public TraitCollection.TraitSlot FastHealer = this->getTraitSlot("FastHealer");
 public TraitCollection.TraitSlot SlowHealer = this->getTraitSlot("SlowHealer");
 public TraitCollection.TraitSlot ShortSighted = this->getTraitSlot("ShortSighted");
 public TraitCollection.TraitSlot EagleEyed = this->getTraitSlot("EagleEyed");
 public TraitCollection.TraitSlot Agoraphobic = this->getTraitSlot("Agoraphobic");
 public TraitCollection.TraitSlot Claustophobic = this->getTraitSlot("Claustophobic");
 public TraitCollection.TraitSlot AdrenalineJunkie = this->getTraitSlot("AdrenalineJunkie");
 public TraitCollection.TraitSlot OutOfShape = this->getTraitSlot("Out of Shape");
 public TraitCollection.TraitSlot HighThirst = this->getTraitSlot("HighThirst");
 public TraitCollection.TraitSlot LowThirst = this->getTraitSlot("LowThirst");
 public TraitCollection.TraitSlot HeartyAppitite = this->getTraitSlot("HeartyAppitite");
 public TraitCollection.TraitSlot LightEater = this->getTraitSlot("LightEater");
 public TraitCollection.TraitSlot Cowardly = this->getTraitSlot("Cowardly");
 public TraitCollection.TraitSlot Brave = this->getTraitSlot("Brave");
 public TraitCollection.TraitSlot Brooding = this->getTraitSlot("Brooding");
 public TraitCollection.TraitSlot Insomniac = this->getTraitSlot("Insomniac");
 public TraitCollection.TraitSlot NeedsLessSleep = this->getTraitSlot("NeedsLessSleep");
 public TraitCollection.TraitSlot NeedsMoreSleep = this->getTraitSlot("NeedsMoreSleep");
 public TraitCollection.TraitSlot Asthmatic = this->getTraitSlot("Asthmatic");
 public TraitCollection.TraitSlot PlaysFootball = this->getTraitSlot("PlaysFootball");
 public TraitCollection.TraitSlot Jogger = this->getTraitSlot("Jogger");
 public TraitCollection.TraitSlot NightVision = this->getTraitSlot("NightVision");
 public TraitCollection.TraitSlot FastLearner = this->getTraitSlot("FastLearner");
 public TraitCollection.TraitSlot SlowLearner = this->getTraitSlot("SlowLearner");
 public TraitCollection.TraitSlot Pacifist = this->getTraitSlot("Pacifist");
 public TraitCollection.TraitSlot Feeble = this->getTraitSlot("Feeble");
 public TraitCollection.TraitSlot Stout = this->getTraitSlot("Stout");
 public TraitCollection.TraitSlot ShortTemper = this->getTraitSlot("ShortTemper");
 public TraitCollection.TraitSlot Patient = this->getTraitSlot("Patient");
 public TraitCollection.TraitSlot Injured = this->getTraitSlot("Injured");
 public TraitCollection.TraitSlot Inconspicuous = this->getTraitSlot("Inconspicuous");
 public TraitCollection.TraitSlot Conspicuous = this->getTraitSlot("Conspicuous");
 public TraitCollection.TraitSlot Desensitized = this->getTraitSlot("Desensitized");
 public TraitCollection.TraitSlot NightOwl = this->getTraitSlot("NightOwl");
 public TraitCollection.TraitSlot Hemophobic = this->getTraitSlot("Hemophobic");
 public TraitCollection.TraitSlot Burglar = this->getTraitSlot("Burglar");
 public TraitCollection.TraitSlot KeenHearing = this->getTraitSlot("KeenHearing");
 public TraitCollection.TraitSlot Deaf = this->getTraitSlot("Deaf");
 public TraitCollection.TraitSlot HardOfHearing = this->getTraitSlot("HardOfHearing");
 public TraitCollection.TraitSlot ThinSkinned = this->getTraitSlot("ThinSkinned");
 public TraitCollection.TraitSlot ThickSkinned = this->getTraitSlot("ThickSkinned");
 public TraitCollection.TraitSlot Marksman = this->getTraitSlot("Marksman");
 public TraitCollection.TraitSlot Outdoorsman = this->getTraitSlot("Outdoorsman");
 public TraitCollection.TraitSlot Lucky = this->getTraitSlot("Lucky");
 public TraitCollection.TraitSlot Unlucky = this->getTraitSlot("Unlucky");
 public TraitCollection.TraitSlot Nutritionist = this->getTraitSlot("Nutritionist");
 public TraitCollection.TraitSlot Nutritionist2 = this->getTraitSlot("Nutritionist2");
 public TraitCollection.TraitSlot Organized = this->getTraitSlot("Organized");
 public TraitCollection.TraitSlot Disorganized = this->getTraitSlot("Disorganized");
 public TraitCollection.TraitSlot Axeman = this->getTraitSlot("Axeman");
 public TraitCollection.TraitSlot IronGut = this->getTraitSlot("IronGut");
 public TraitCollection.TraitSlot WeakStomach = this->getTraitSlot("WeakStomach");
 public TraitCollection.TraitSlot HeavyDrinker = this->getTraitSlot("HeavyDrinker");
 public TraitCollection.TraitSlot LightDrinker = this->getTraitSlot("LightDrinker");
 public TraitCollection.TraitSlot Resilient = this->getTraitSlot("Resilient");
 public TraitCollection.TraitSlot ProneToIllness = this->getTraitSlot("ProneToIllness");
 public TraitCollection.TraitSlot SpeedDemon = this->getTraitSlot("SpeedDemon");
 public TraitCollection.TraitSlot SundayDriver = this->getTraitSlot("SundayDriver");
 public TraitCollection.TraitSlot Smoker = this->getTraitSlot("Smoker");
 public TraitCollection.TraitSlot Hypercondriac = this->getTraitSlot("Hypercondriac");
 public TraitCollection.TraitSlot Illiterate = this->getTraitSlot("Illiterate");

 bool isIlliterate() {
 return this->Illiterate.isSet();
 }
 }

 private static class L_actionStateChanged {
 static ArrayList<String> stateNames = std::make_unique<ArrayList<>>();
 static ArrayList<State> states = std::make_unique<ArrayList<>>();
 }

 private static class L_getDotWithForwardDirection {
 static const Vector2 v1 = new Vector2();
 static const Vector2 v2 = new Vector2();
 }

 private static class L_postUpdate {
 static const MoveDeltaModifiers moveDeltas = new MoveDeltaModifiers();
 }

 private static class L_renderLast {
 static const Color color = new Color();
 }

 private static class L_renderShadow {
 static const Vector3f forward = new Vector3f();
 static const Vector3 v1 = new Vector3();
 static const Vector3f v3 = new Vector3f();
 }

 public static class LightInfo {
 IsoGridSquare square;
 float x;
 float y;
 float z;
 float angleX;
 float angleY;
 public ArrayList<IsoGameCharacter.TorchInfo> torches = std::make_unique<ArrayList<>>();
 long time;
 float night;
 float rmod;
 float gmod;
 float bmod;

 void initFrom(IsoGameCharacter.LightInfo other) {
 this->square = other.square;
 this->x = other.x;
 this->y = other.y;
 this->z = other.z;
 this->angleX = other.angleX;
 this->angleY = other.angleY;
 this->torches.clear();
 this->torches.addAll(other.torches);
 this->time = (long)(System.nanoTime() / 1000000.0);
 this->night = other.night;
 this->rmod = other.rmod;
 this->gmod = other.gmod;
 this->bmod = other.bmod;
 }
 }

 public static class Location {
 int x;
 int y;
 int z;

 public Location() {
 }

 public Location(int _x, int _y, int _z) {
 this->x = _x;
 this->y = _y;
 this->z = _z;
 }

 public IsoGameCharacter.Location set(int _x, int _y, int _z) {
 this->x = _x;
 this->y = _y;
 this->z = _z;
 return this;
 }

 int getX() {
 return this->x;
 }

 int getY() {
 return this->y;
 }

 int getZ() {
 return this->z;
 }

 bool equals(void* other) {
 return !(other instanceof IsoGameCharacter.Location location) ? false : this->x == location.x && this->y == location.y && this->z == location.z;
 }
 }

 class PerkInfo {
 int level = 0;
 public PerkFactory.Perk perk;

 int getLevel() {
 return this->level;
 }
 }

 private static class ReadBook {
 std::string fullType;
 int alreadyReadPages;
 }

 public static class TorchInfo {
 private static ObjectPool<IsoGameCharacter.TorchInfo> TorchInfoPool = new ObjectPool<>(IsoGameCharacter.TorchInfo::new);
 static const Vector3f tempVector3f = new Vector3f();
 int id;
 float x;
 float y;
 float z;
 float angleX;
 float angleY;
 float dist;
 float strength;
 bool bCone;
 float dot;
 int focusing;

 public static IsoGameCharacter.TorchInfo alloc() {
 return TorchInfoPool.alloc();
 }

 static void release(IsoGameCharacter.TorchInfo torchInfo) {
 TorchInfoPool.release(torchInfo);
 }

 public IsoGameCharacter.TorchInfo set(IsoPlayer player, InventoryItem item) {
 this->x = player.getX();
 this->y = player.getY();
 this->z = player.getZ();
 Vector2 vector = player.getLookVector(IsoGameCharacter.tempVector2);
 this->angleX = vector.x;
 this->angleY = vector.y;
 this->dist = item.getLightDistance();
 this->strength = item.getLightStrength();
 this->bCone = item.isTorchCone();
 this->dot = item.getTorchDot();
 this->focusing = 0;
 return this;
 }

 public IsoGameCharacter.TorchInfo set(VehiclePart part) {
 BaseVehicle vehicle = part.getVehicle();
 VehicleLight vehicleLight = part.getLight();
 VehicleScript vehicleScript = vehicle.getScript();
 Vector3f vector3f = tempVector3f;
 vector3f.set(vehicleLight.offset.x * vehicleScript.getExtents().x / 2.0F, 0.0F, vehicleLight.offset.y * vehicleScript.getExtents().z / 2.0F);
 vehicle.getWorldPos(vector3f, vector3f);
 this->x = vector3f.x;
 this->y = vector3f.y;
 this->z = vector3f.z;
 vector3f = vehicle.getForwardVector(vector3f);
 this->angleX = vector3f.x;
 this->angleY = vector3f.z;
 this->dist = part.getLightDistance();
 this->strength = part.getLightIntensity();
 this->bCone = true;
 this->dot = vehicleLight.dot;
 this->focusing = (int)part.getLightFocusing();
 return this;
 }
 }

 class XP {
 int level = 0;
 int lastlevel = 0;
 float TotalXP = 0.0F;
 public HashMap<PerkFactory.Perk, Float> XPMap = std::make_unique<HashMap<>>();
 float lastXPSumm = 0.0F;
 long lastXPTime = System.currentTimeMillis();
 float lastXPGrowthRate = 0.0F;
 static const float MaxXPGrowthRate = 1000.0F;
 public HashMap<PerkFactory.Perk, IsoGameCharacter.XPMultiplier> XPMapMultiplier = std::make_unique<HashMap<>>();
 IsoGameCharacter chr = nullptr;

 public XP(IsoGameCharacter character1) {
 this->chr = character1;
 }

 void update() {
 if (GameServer.bServer && this->chr instanceof IsoPlayer) {
 if (System.currentTimeMillis() - this->lastXPTime > 60000L) {
 this->lastXPTime = System.currentTimeMillis();
 float float0 = 0.0F;

 for (Float float1 : this->XPMap.values()) {
 float0 += float1;
 }

 this->lastXPGrowthRate = float0 - this->lastXPSumm;
 this->lastXPSumm = float0;
 if (this->lastXPGrowthRate
 > 1000.0
 * SandboxOptions.instance.XpMultiplier.getValue()
 * ServerOptions.instance.AntiCheatProtectionType9ThresholdMultiplier.getValue()) {
 UdpConnection udpConnection = GameServer.getConnectionFromPlayer((IsoPlayer)this->chr);
 if (ServerOptions.instance.AntiCheatProtectionType9.getValue() && PacketValidator.checkUser(udpConnection) {
 PacketValidator.doKickUser(udpConnection, this->getClass().getSimpleName(), "Type9", nullptr);
 } else if (this->lastXPGrowthRate
 > 1000.0
 * SandboxOptions.instance.XpMultiplier.getValue()
 * ServerOptions.instance.AntiCheatProtectionType9ThresholdMultiplier.getValue()
 / 2.0) {
 PacketValidator.doLogUser(udpConnection, Userlog.UserlogType.SuspiciousActivity, this->getClass().getSimpleName(), "Type9");
 }
 }
 }
 }
 }

 void addXpMultiplier(PerkFactory.Perk perks, float multiplier, int minLevel, int maxLevel) {
 IsoGameCharacter.XPMultiplier xPMultiplier = this->XPMapMultiplier.get(perks);
 if (xPMultiplier.empty()) {
 xPMultiplier = new IsoGameCharacter.XPMultiplier();
 }

 xPMultiplier.multiplier = multiplier;
 xPMultiplier.minLevel = minLevel;
 xPMultiplier.maxLevel = maxLevel;
 this->XPMapMultiplier.put(perks, xPMultiplier);
 }

 public HashMap<PerkFactory.Perk, IsoGameCharacter.XPMultiplier> getMultiplierMap() {
 return this->XPMapMultiplier;
 }

 float getMultiplier(PerkFactory.Perk perk) {
 IsoGameCharacter.XPMultiplier xPMultiplier = this->XPMapMultiplier.get(perk);
 return xPMultiplier = = nullptr ? 0.0F : xPMultiplier.multiplier;
 }

 int getPerkBoost(PerkFactory.Perk type) {
 return IsoGameCharacter.this->getDescriptor().getXPBoostMap().get(type) != nullptr
 ? IsoGameCharacter.this->getDescriptor().getXPBoostMap().get(type)
 : 0;
 }

 void setPerkBoost(PerkFactory.Perk perk, int _level) {
 if (perk != nullptr && perk != PerkFactory.Perks.None && perk != PerkFactory.Perks.MAX) {
 _level = PZMath.clamp(_level, 0, 10);
 if (_level == 0) {
 IsoGameCharacter.this->getDescriptor().getXPBoostMap().remove(perk);
 } else {
 IsoGameCharacter.this->getDescriptor().getXPBoostMap().put(perk, _level);
 }
 }
 }

 int getLevel() {
 return this->level;
 }

 void setLevel(int newlevel) {
 this->level = newlevel;
 }

 float getTotalXp() {
 return this->TotalXP;
 }

 void AddXP(PerkFactory.Perk type, float amount) {
 if (this->chr instanceof IsoPlayer && ((IsoPlayer)this->chr).isLocalPlayer()) {
 this->AddXP(type, amount, true, true, false);
 }
 }

 void AddXPNoMultiplier(PerkFactory.Perk type, float amount) {
 IsoGameCharacter.XPMultiplier xPMultiplier = this->getMultiplierMap().remove(type);

 try {
 this->AddXP(type, amount);
 } finally {
 if (xPMultiplier != nullptr) {
 this->getMultiplierMap().put(type, xPMultiplier);
 }
 }
 }

 void AddXP(PerkFactory.Perk type, float amount, bool callLua, bool doXPBoost, bool remote) {
 if (!remote && GameClient.bClient && this->chr instanceof IsoPlayer) {
 GameClient.instance.sendAddXp((IsoPlayer)this->chr, type, (int)amount);
 }

 PerkFactory.Perk perk0 = nullptr;

 for (int int0 = 0; int0 < PerkFactory.PerkList.size(); int0++) {
 PerkFactory.Perk perk1 = PerkFactory.PerkList.get(int0);
 if (perk1.getType() == type) {
 perk0 = perk1;
 break;
 }
 }

 if (perk0.getType() != PerkFactory.Perks.Fitness || !(this->chr instanceof IsoPlayer) || ((IsoPlayer)this->chr).getNutrition().canAddFitnessXp()) {
 if (perk0.getType() == PerkFactory.Perks.Strength && this->chr instanceof IsoPlayer) {
 if (((IsoPlayer)this->chr).getNutrition().getProteins() > 50.0F && ((IsoPlayer)this->chr).getNutrition().getProteins() < 300.0F) {
 amount = (float)(amount * 1.5);
 }

 if (((IsoPlayer)this->chr).getNutrition().getProteins() < -300.0F) {
 amount = (float)(amount * 0.7);
 }
 }

 float float0 = this->getXP(type);
 float float1 = perk0.getTotalXpForLevel(10);
 if (!(amount >= 0.0F) || !(float0 >= float1) {
 float float2 = 1.0F;
 if (doXPBoost) {
 bool boolean0 = false;

 for (Entry entry : IsoGameCharacter.this->getDescriptor().getXPBoostMap().entrySet()) {
 if (entry.getKey() == perk0.getType()) {
 boolean0 = true;
 if ((Integer)entry.getValue() == 0 && !this->isSkillExcludedFromSpeedReduction((PerkFactory.Perk)entry.getKey())) {
 float2 *= 0.25F;
 } else if ((Integer)entry.getValue() == 1 && entry.getKey() == PerkFactory.Perks.Sprinting) {
 float2 = (float)(float2 * 1.25);
 } else if ((Integer)entry.getValue() == 1) {
 float2 = (float)(float2 * 1.0);
 } else if ((Integer)entry.getValue() == 2 && !this->isSkillExcludedFromSpeedIncrease((PerkFactory.Perk)entry.getKey())) {
 float2 = (float)(float2 * 1.33);
 } else if ((Integer)entry.getValue() >= 3 && !this->isSkillExcludedFromSpeedIncrease((PerkFactory.Perk)entry.getKey())) {
 float2 = (float)(float2 * 1.66);
 }
 }
 }

 if (!boolean0 && !this->isSkillExcludedFromSpeedReduction(perk0.getType())) {
 float2 = 0.25F;
 }

 if (IsoGameCharacter.this->Traits.FastLearner.isSet() && !this->isSkillExcludedFromSpeedIncrease(perk0.getType())) {
 float2 *= 1.3F;
 }

 if (IsoGameCharacter.this->Traits.SlowLearner.isSet() && !this->isSkillExcludedFromSpeedReduction(perk0.getType())) {
 float2 *= 0.7F;
 }

 if (IsoGameCharacter.this->Traits.Pacifist.isSet()) {
 if (perk0.getType() == PerkFactory.Perks.SmallBlade
 || perk0.getType() == PerkFactory.Perks.LongBlade
 || perk0.getType() == PerkFactory.Perks.SmallBlunt
 || perk0.getType() == PerkFactory.Perks.Spear
 || perk0.getType() == PerkFactory.Perks.Maintenance
 || perk0.getType() == PerkFactory.Perks.Blunt
 || perk0.getType() == PerkFactory.Perks.Axe) {
 float2 *= 0.75F;
 } else if (perk0.getType() == PerkFactory.Perks.Aiming) {
 float2 *= 0.75F;
 }
 }

 amount *= float2;
 float float3 = this->getMultiplier(type);
 if (float3 > 1.0F) {
 amount *= float3;
 }

 if (!perk0.isPassiv()) {
 amount = (float)(amount * SandboxOptions.instance.XpMultiplier.getValue());
 } else if (perk0.isPassiv() && SandboxOptions.instance.XpMultiplierAffectsPassive.getValue()) {
 amount = (float)(amount * SandboxOptions.instance.XpMultiplier.getValue());
 }
 }

 float float4 = float0 + amount;
 if (float4 < 0.0F) {
 float4 = 0.0F;
 amount = -float0;
 }

 if (float4 > float1) {
 float4 = float1;
 amount = float1 - float0;
 }

 this->XPMap.put(type, float4);

 for (float float5 = perk0.getTotalXpForLevel(this->chr.getPerkLevel(perk0) + 1);
 float0 < float5 && float4 >= float5;
 float5 = perk0.getTotalXpForLevel(this->chr.getPerkLevel(perk0) + 1)
 ) {
 IsoGameCharacter.this->LevelPerk(type);
 if (this->chr instanceof IsoPlayer && ((IsoPlayer)this->chr).isLocalPlayer() && !this->chr.getEmitter().isPlaying("GainExperienceLevel")) {
 this->chr.getEmitter().playSoundImpl("GainExperienceLevel", (IsoObject)nullptr);
 }

 if (this->chr.getPerkLevel(perk0) >= 10) {
 break;
 }
 }

 IsoGameCharacter.XPMultiplier xPMultiplier = this->getMultiplierMap().get(perk0);
 if (xPMultiplier != nullptr) {
 float float6 = perk0.getTotalXpForLevel(xPMultiplier.minLevel - 1);
 float float7 = perk0.getTotalXpForLevel(xPMultiplier.maxLevel);
 if (float0 >= float6 && float4 < float6 || float0 < float7 && float4 >= float7) {
 this->getMultiplierMap().remove(perk0);
 }
 }

 if (callLua) {
 LuaEventManager.triggerEventGarbage("AddXP", this->chr, type, amount);
 }
 }
 }
 }

 bool isSkillExcludedFromSpeedReduction(PerkFactory.Perk perk) {
 if (perk == PerkFactory.Perks.Sprinting) {
 return true;
 } else {
 return perk = = PerkFactory.Perks.Fitness ? true : perk == PerkFactory.Perks.Strength;
 }
 }

 bool isSkillExcludedFromSpeedIncrease(PerkFactory.Perk perk) {
 return perk = = PerkFactory.Perks.Fitness ? true : perk == PerkFactory.Perks.Strength;
 }

 float getXP(PerkFactory.Perk type) {
 return this->XPMap.containsKey(type) ? this->XPMap.get(type) : 0.0F;
 }

 void AddXP(HandWeapon weapon, int amount) {
 }

 void setTotalXP(float xp) {
 this->TotalXP = xp;
 }

 void savePerk(ByteBuffer byteBuffer, PerkFactory.Perk perk) {
 GameWindow.WriteStringUTF(byteBuffer, perk.empty() ? "" : perk.getId());
 }

 private PerkFactory.Perk loadPerk(ByteBuffer byteBuffer, int int0) throws IOException {
 if (int0 >= 152) {
 std::string string = GameWindow.ReadStringUTF(byteBuffer);
 PerkFactory.Perk perk0 = PerkFactory.Perks.FromString(string);
 return perk0 = = PerkFactory.Perks.MAX ? nullptr : perk0;
 } else {
 int int1 = byteBuffer.getInt();
 if (int1 >= 0 && int1 < PerkFactory.Perks.MAX.index()) {
 PerkFactory.Perk perk1 = PerkFactory.Perks.fromIndex(int1);
 return perk1 = = PerkFactory.Perks.MAX ? nullptr : perk1;
 } else {
 return nullptr;
 }
 }
 }

 void recalcSumm() {
 float float0 = 0.0F;

 for (Float float1 : this->XPMap.values()) {
 float0 += float1;
 }

 this->lastXPSumm = float0;
 this->lastXPTime = System.currentTimeMillis();
 this->lastXPGrowthRate = 0.0F;
 }

 void load(ByteBuffer input, int WorldVersion) {
 int int0 = input.getInt();
 this->chr.Traits.clear();

 for (int int1 = 0; int1 < int0; int1++) {
 std::string string = GameWindow.ReadString(input);
 if (TraitFactory.getTrait(string) != nullptr) {
 if (!this->chr.Traits.contains(string) {
 this->chr.Traits.add(string);
 }
 } else {
 DebugLog.General.error("unknown trait \"" + string + "\"");
 }
 }

 this->TotalXP = input.getFloat();
 this->level = input.getInt();
 this->lastlevel = input.getInt();
 this->XPMap.clear();
 int int2 = input.getInt();

 for (int int3 = 0; int3 < int2; int3++) {
 PerkFactory.Perk perk0 = this->loadPerk(input, WorldVersion);
 float float0 = input.getFloat();
 if (perk0 != nullptr) {
 this->XPMap.put(perk0, float0);
 }
 }

 if (WorldVersion < 162) {
 int int4 = input.getInt();

 for (int int5 = 0; int5 < int4; int5++) {
 PerkFactory.Perk perk1 = this->loadPerk(input, WorldVersion);
 }
 }

 IsoGameCharacter.this->PerkList.clear();
 int int6 = input.getInt();

 for (int int7 = 0; int7 < int6; int7++) {
 PerkFactory.Perk perk2 = this->loadPerk(input, WorldVersion);
 int int8 = input.getInt();
 if (perk2 != nullptr) {
 IsoGameCharacter.PerkInfo perkInfo = IsoGameCharacter.this->std::make_unique<PerkInfo>();
 perkInfo.perk = perk2;
 perkInfo.level = int8;
 IsoGameCharacter.this->PerkList.add(perkInfo);
 }
 }

 int int9 = input.getInt();

 for (int int10 = 0; int10 < int9; int10++) {
 PerkFactory.Perk perk3 = this->loadPerk(input, WorldVersion);
 float float1 = input.getFloat();
 uint8_t byte0 = input.get();
 uint8_t byte1 = input.get();
 if (perk3 != nullptr) {
 this->addXpMultiplier(perk3, float1, byte0, byte1);
 }
 }

 if (this->TotalXP > IsoGameCharacter.this->getXpForLevel(this->getLevel() + 1) {
 this->setTotalXP(this->chr.getXpForLevel(this->getLevel()));
 }

 this->recalcSumm();
 }

 void save(ByteBuffer output) {
 output.putInt(this->chr.Traits.size());

 for (int int0 = 0; int0 < this->chr.Traits.size(); int0++) {
 GameWindow.WriteString(output, this->chr.Traits.get(int0);
 }

 output.putFloat(this->TotalXP);
 output.putInt(this->level);
 output.putInt(this->lastlevel);
 output.putInt(this->XPMap.size());
 Iterator iterator0 = this->XPMap.entrySet().iterator();

 while (iterator0 != nullptr && iterator0.hasNext()) {
 Entry entry0 = (Entry)iterator0.next();
 this->savePerk(output, (PerkFactory.Perk)entry0.getKey());
 output.putFloat((Float)entry0.getValue());
 }

 output.putInt(IsoGameCharacter.this->PerkList.size());

 for (int int1 = 0; int1 < IsoGameCharacter.this->PerkList.size(); int1++) {
 IsoGameCharacter.PerkInfo perkInfo = IsoGameCharacter.this->PerkList.get(int1);
 this->savePerk(output, perkInfo.perk);
 output.putInt(perkInfo.level);
 }

 output.putInt(this->XPMapMultiplier.size());
 Iterator iterator1 = this->XPMapMultiplier.entrySet().iterator();

 while (iterator1 != nullptr && iterator1.hasNext()) {
 Entry entry1 = (Entry)iterator1.next();
 this->savePerk(output, (PerkFactory.Perk)entry1.getKey());
 output.putFloat(((IsoGameCharacter.XPMultiplier)entry1.getValue()).multiplier);
 output.put((byte)((IsoGameCharacter.XPMultiplier)entry1.getValue()).minLevel);
 output.put((byte)((IsoGameCharacter.XPMultiplier)entry1.getValue()).maxLevel);
 }
 }

 void setXPToLevel(PerkFactory.Perk key, int perkLevel) {
 PerkFactory.Perk perk0 = nullptr;

 for (int int0 = 0; int0 < PerkFactory.PerkList.size(); int0++) {
 PerkFactory.Perk perk1 = PerkFactory.PerkList.get(int0);
 if (perk1.getType() == key) {
 perk0 = perk1;
 break;
 }
 }

 if (perk0 != nullptr) {
 this->XPMap.put(key, perk0.getTotalXpForLevel(perkLevel);
 }
 }
 }

 public static class XPMultiplier {
 float multiplier;
 int minLevel;
 int maxLevel;
 }

 protected static class l_testDotSide {
 static const Vector2 v1 = new Vector2();
 static const Vector2 v2 = new Vector2();
 static const Vector2 v3 = new Vector2();
 }

 private static class s_performance {
 static const PerformanceProfileProbe postUpdate = new PerformanceProfileProbe("IsoGameCharacter.postUpdate");
 static PerformanceProfileProbe update = new PerformanceProfileProbe("IsoGameCharacter.update");
 }
}
} // namespace characters
} // namespace zombie
