#pragma once
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_DESCRIPTION.h"
#include "fmod/fmod/IFMODParameterUpdater.h"
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
#include "zombie/ai/astar/AStarPathFinder/PathFindProgress.h"
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
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characterTextures/BloodClothingType.h"
#include "zombie/characters/AttachedItems/AttachedItem.h"
#include "zombie/characters/AttachedItems/AttachedItems.h"
#include "zombie/characters/AttachedItems/AttachedLocationGroup.h"
#include "zombie/characters/AttachedItems/AttachedLocations.h"
#include "zombie/characters/BodyDamage/BodyDamage.h"
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/BodyDamage/Metabolics.h"
#include "zombie/characters/BodyDamage/Nutrition.h"
#include "zombie/characters/CharacterTimedActions/BaseAction.h"
#include "zombie/characters/CharacterTimedActions/LuaTimedActionNew.h"
#include "zombie/characters/IsoGameCharacter/1.h"
#include "zombie/characters/IsoGameCharacter/Bandages.h"
#include "zombie/characters/IsoGameCharacter/CharacterTraits.h"
#include "zombie/characters/IsoGameCharacter/L_actionStateChanged.h"
#include "zombie/characters/IsoGameCharacter/L_getDotWithForwardDirection.h"
#include "zombie/characters/IsoGameCharacter/L_postUpdate.h"
#include "zombie/characters/IsoGameCharacter/L_renderLast.h"
#include "zombie/characters/IsoGameCharacter/L_renderShadow.h"
#include "zombie/characters/IsoGameCharacter/LightInfo.h"
#include "zombie/characters/IsoGameCharacter/Location.h"
#include "zombie/characters/IsoGameCharacter/PerkInfo.h"
#include "zombie/characters/IsoGameCharacter/ReadBook.h"
#include "zombie/characters/IsoGameCharacter/TorchInfo.h"
#include "zombie/characters/IsoGameCharacter/XP.h"
#include "zombie/characters/IsoGameCharacter/l_testDotSide.h"
#include "zombie/characters/IsoGameCharacter/s_performance.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/characters/Moodles/Moodles.h"
#include "zombie/characters/NetworkTeleport/NetworkTeleportDebug.h"
#include "zombie/characters/WornItems/BodyLocationGroup.h"
#include "zombie/characters/WornItems/BodyLocations.h"
#include "zombie/characters/WornItems/WornItem.h"
#include "zombie/characters/WornItems/WornItems.h"
#include "zombie/characters/action/ActionContext.h"
#include "zombie/characters/action/ActionState.h"
#include "zombie/characters/action/ActionStateSnapshot.h"
#include "zombie/characters/action/IActionStateChanged.h"
#include "zombie/characters/skills/PerkFactory/Perk.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/characters/traits/TraitCollection.h"
#include "zombie/characters/traits/TraitFactory.h"
#include "zombie/characters/traits/TraitFactory/Trait.h"
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
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/ModelManager/ModelSlot.h"
#include "zombie/core/skinnedmodel/advancedanimation/AdvancedAnimator.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimLayer.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimNode.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimState.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationSet.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationVariableHandle.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationVariableSlotCallbackBool/CallbackSetStrongTyped.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationVariableSlotCallbackFloat/CallbackGetStrongTyped.h"
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
#include "zombie/inventory/types/Clothing/ClothingPatch.h"
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
#include "zombie/iso/IsoObjectPicker/ClickObject.h"
#include "zombie/iso/IsoRoofFixer.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LightingJNI.h"
#include "zombie/iso/LosUtil.h"
#include "zombie/iso/LosUtil/TestResults.h"
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
#include "zombie/iso/objects/IsoZombieGiblets/GibletType.h"
#include "zombie/iso/objects/RainManager.h"
#include "zombie/iso/objects/interfaces/BarricadeAble.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/NetworkVariables/ZombieState.h"
#include "zombie/network/ServerGUI.h"
#include "zombie/network/ServerMap.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/network/chat/ChatServer.h"
#include "zombie/network/chat/ChatType.h"
#include "zombie/network/packets/hit/AttackVars.h"
#include "zombie/network/packets/hit/HitInfo.h"
#include "zombie/profanity/ProfanityFilter.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/scripting/objects/Recipe.h"
#include "zombie/ui/ActionProgressBar.h"
#include "zombie/ui/TextDrawObject.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/TextManager/StringDrawer.h"
#include "zombie/ui/TutorialManager.h"
#include "zombie/ui/UIFont.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/Pool.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/BaseVehicle/Authorization.h"
#include "zombie/vehicles/BaseVehicle/HitVars.h"
#include "zombie/vehicles/BaseVehicle/Vector2ObjectPool.h"
#include "zombie/vehicles/PathFindBehavior2.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include "zombie/vehicles/PolygonalMap2/Path.h"
#include "zombie/vehicles/VehiclePart.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace characters {


class IsoGameCharacter {
public:
   : public IsoMovingObject
   , public Talker,
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
   private static const std::unordered_map<int, SurvivorDesc> SurvivorMap = std::make_unique<std::unordered_map<>>();
   private static const int[] LevelUpLevels = new int[]{
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
    static const Vector2 tempo = std::make_shared<Vector2>();
    static const ColorInfo inf = std::make_shared<ColorInfo>();
    long vocalEvent;
    long removedFromWorldMS = 0L;
    bool bAutoWalk = false;
    const Vector2 autoWalkDirection = std::make_shared<Vector2>();
    bool bSneaking = false;
    static const Vector2 tempo2 = std::make_shared<Vector2>();
    static const Vector2 tempVector2_1 = std::make_shared<Vector2>();
    static const Vector2 tempVector2_2 = std::make_shared<Vector2>();
    static std::string sleepText = nullptr;
   protected const std::vector<InventoryItem> savedInventoryItems = std::make_unique<std::vector<>>();
    const std::string instancename;
    GameCharacterAIBrain GameCharacterAIBrain;
   public const std::vector<std::string> amputations = std::make_unique<std::vector<>>();
    ModelInstance hair;
    ModelInstance beard;
    ModelInstance primaryHandModel;
    ModelInstance secondaryHandModel;
    const ActionContext actionContext = std::make_shared<ActionContext>(this);
    const BaseCharacterSoundEmitter emitter;
    const FMODParameterList fmodParameters = std::make_shared<FMODParameterList>();
    const AnimationVariableSource m_GameVariables = std::make_shared<AnimationVariableSource>();
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
   public const std::unordered_map<State, std::unordered_map<Object, Object>> StateMachineParams = std::make_unique<std::unordered_map<>>();
    long clientIgnoreCollision = 0L;
    bool isCrit = false;
    bool bKnockedDown = false;
    int bumpNbr = 0;
    bool upKillCount = true;
   private const std::vector<PerkInfo> PerkList = std::make_unique<std::vector<>>();
    const Vector2 m_forwardDirection = std::make_shared<Vector2>();
    bool Asleep = false;
    bool blockTurning = false;
    float speedMod = 1.0F;
    IsoSprite legsSprite;
    bool bFemale = true;
    float knockbackAttackMod = 1.0F;
   public const boolean[] IsVisibleToPlayer = new boolean[4];
    float savedVehicleX;
    float savedVehicleY;
    short savedVehicleSeat = -1;
    bool savedVehicleRunning;
    static const float RecoilDelayDecrease = 0.625F;
    static const float BeenMovingForIncrease = 1.25F;
    static const float BeenMovingForDecrease = 0.625F;
    IsoGameCharacter FollowingTarget = nullptr;
   private const std::vector<IsoMovingObject> LocalList = std::make_unique<std::vector<>>();
   private const std::vector<IsoMovingObject> LocalNeutralList = std::make_unique<std::vector<>>();
   private const std::vector<IsoMovingObject> LocalGroupList = std::make_unique<std::vector<>>();
   private const std::vector<IsoMovingObject> LocalRelevantEnemyList = std::make_unique<std::vector<>>();
    float dangerLevels = 0.0F;
    static const Vector2 tempVector2 = std::make_shared<Vector2>();
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
    XP xp = nullptr;
    int LastLocalEnemies = 0;
   private const std::vector<IsoMovingObject> VeryCloseEnemyList = std::make_unique<std::vector<>>();
   private const std::unordered_map<std::string, Location> LastKnownLocation = std::make_unique<std::unordered_map<>>();
    IsoGameCharacter AttackedBy = nullptr;
    bool IgnoreStaggerBack = false;
    bool AttackWasSuperAttack = false;
    int TimeThumping = 0;
    int PatienceMax = 150;
    int PatienceMin = 20;
    int Patience = 20;
   protected const std::stack<BaseAction> CharacterActions = std::make_unique<std::stack<>>();
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
   public std::vector<InventoryContainer> bagsWorn;
    bool ForceWakeUp;
    const BodyDamage BodyDamage;
    BodyDamage BodyDamageRemote = nullptr;
    State defaultState;
    WornItems wornItems = nullptr;
    AttachedItems attachedItems = nullptr;
    ClothingWetness clothingWetness = nullptr;
    SurvivorDesc descriptor;
   private const std::stack<IsoBuilding> FamiliarBuildings = std::make_unique<std::stack<>>();
    const AStarPathFinderResult finder = std::make_shared<AStarPathFinderResult>();
    float FireKillRate = 0.0038F;
    int FireSpreadProbability = 6;
    float Health = 1.0F;
    bool bDead = false;
    bool bKill = false;
    bool bPlayingDeathSound = false;
    bool bDeathDragDown = false;
    std::string hurtSound = "MaleZombieHurt";
    ItemContainer inventory = std::make_shared<ItemContainer>();
    InventoryItem leftHandItem;
    int NextWander = 200;
    bool OnFire = false;
    int pathIndex = 0;
    InventoryItem rightHandItem;
    Color SpeakColour = std::make_shared<Color>(1.0F, 1.0F, 1.0F, 1.0F);
    float slowFactor = 0.0F;
    float slowTimer = 0.0F;
    bool bUseParts = false;
    bool Speaking = false;
    float SpeakTime = 0.0F;
    float staggerTimeMod = 1.0F;
    const StateMachine stateMachine;
    const Moodles Moodles;
    const Stats stats = std::make_shared<Stats>();
   private const std::stack<std::string> UsedItemsOn = std::make_unique<std::stack<>>();
    HandWeapon useHandWeapon = nullptr;
    IsoGridSquare attackTargetSquare;
    float BloodImpactX = 0.0F;
    float BloodImpactY = 0.0F;
    float BloodImpactZ = 0.0F;
    IsoSprite bloodSplat;
    bool bOnBed = false;
    const Vector2 moveForwardVec = std::make_shared<Vector2>();
    bool pathing = false;
    ChatElement chatElement;
   private const std::stack<IsoGameCharacter> LocalEnemyList = std::make_unique<std::stack<>>();
   protected const std::stack<IsoGameCharacter> EnemyList = std::make_unique<std::stack<>>();
    const CharacterTraits Traits = std::make_shared<CharacterTraits>(this);
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
   private const std::unordered_map<std::string, std::string> namesPrefix = std::make_unique<std::unordered_map<>>();
    static const std::string namePvpSuffix = " [img=media/ui/Skull.png]";
    static const std::string nameCarKeySuffix = " [img=media/ui/CarKey.png";
    static const std::string voiceSuffix = "[img=media/ui/voiceon.png] ";
    static const std::string voiceMuteSuffix = "[img=media/ui/voicemuted.png] ";
    IsoPlayer isoPlayer = nullptr;
    bool hasInitTextObjects = false;
    bool canSeeCurrent = false;
    bool drawUserName = false;
    const Location LastHeardSound = std::make_shared<Location>(-1, -1, -1);
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
    Safety safety = std::make_shared<Safety>(this);
    float meleeDelay = 0.0F;
    float RecoilDelay = 0.0F;
    float BeenMovingFor = 0.0F;
    float BeenSprintingFor = 0.0F;
    bool forceShove = false;
    std::string clickSound = nullptr;
    float reduceInfectionPower = 0.0F;
   private const List<std::string> knownRecipes = std::make_unique<std::vector<>>();
   private const std::unordered_set<std::string> knownMediaLines = std::make_unique<std::unordered_set<>>();
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
   private const std::vector<ReadBook> ReadBooks = std::make_unique<std::vector<>>();
    const LightInfo lightInfo = std::make_shared<LightInfo>();
    const LightInfo lightInfo2 = std::make_shared<LightInfo>();
    Path path2;
    const MapKnowledge mapKnowledge = std::make_shared<MapKnowledge>();
    const AttackVars attackVars = std::make_shared<AttackVars>();
   public const std::vector<HitInfo> hitList = std::make_unique<std::vector<>>();
    const PathFindBehavior2 pfb2 = std::make_shared<PathFindBehavior2>(this);
   private const InventoryItem[] cacheEquiped = new InventoryItem[2];
    bool bAimAtFloor = false;
    int m_persistentOutfitId = 0;
    bool m_bPersistentOutfitInit = false;
    bool bUpdateModelTextures = false;
    ModelInstanceTextureCreator textureCreator = nullptr;
    bool bUpdateEquippedTextures = false;
   private const std::vector<ModelInstance> readyModelData = std::make_unique<std::vector<>>();
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
    ZombieState realState = ZombieState.Idle;
    IsoDirections realdir = IsoDirections.fromIndex(0);
    std::string overridePrimaryHandModel = nullptr;
    std::string overrideSecondaryHandModel = nullptr;
    bool forceNullOverride = false;
    const UpdateLimit ulBeatenVehicle = std::make_shared<UpdateLimit>(200L);
    float m_momentumScalar = 0.0F;
   private const std::unordered_map<std::string, State> m_stateUpdateLookup = std::make_unique<std::unordered_map<>>();
    bool attackAnim = false;
    NetworkTeleport teleport = nullptr;
   public std::vector<int> invRadioFreq = std::make_unique<std::vector<>>();
    const PredicatedFileWatcher m_animStateTriggerWatcher;
    const AnimationPlayerRecorder m_animationRecorder;
    const std::string m_UID;
    bool m_bDebugVariablesRegistered = false;
    float effectiveEdibleBuffTimer = 0.0F;
    float m_shadowFM = 0.0F;
    float m_shadowBM = 0.0F;
    long shadowTick = -1L;
    static const ItemVisuals tempItemVisuals = std::make_shared<ItemVisuals>();
   private static const std::vector<IsoMovingObject> movingStatic = std::make_unique<std::vector<>>();
    long m_muzzleFlash = -1L;
    static const Bandages s_bandages = std::make_shared<Bandages>();
    static const Vector3 tempVector = std::make_shared<Vector3>();
    static const Vector3 tempVectorBonePos = std::make_shared<Vector3>();
    const NetworkCharacter networkCharacter = std::make_shared<NetworkCharacter>();

    public IsoGameCharacter(IsoCell var1, float var2, float var3, float var4) {
      super(var1, false);
      this.m_UID = std::string.format("%s-%s", this.getClass().getSimpleName(), UUID.randomUUID());
      this.registerVariableCallbacks();
      this.instancename = "char" + IID;
      IID++;
      if (!(dynamic_cast<IsoSurvivor*>(this) != nullptr)) {
         this.emitter = (BaseCharacterSoundEmitter)(!Core.SoundDisabled && !GameServer.bServer
            ? std::make_shared<CharacterSoundEmitter>(this)
            : std::make_shared<DummyCharacterSoundEmitter>(this));
      } else {
         this.emitter = nullptr;
      }

      if (var2 != 0.0F || var3 != 0.0F || var4 != 0.0F) {
         if (this.getCell().isSafeToAdd()) {
            this.getCell().getObjectList().push_back(this);
         } else {
            this.getCell().getAddList().push_back(this);
         }
      }

      if (this.def == nullptr) {
         this.def = IsoSpriteInstance.get(this.sprite);
      }

      if (dynamic_cast<IsoPlayer*>(this) != nullptr) {
         this.BodyDamage = std::make_shared<BodyDamage>(this);
         this.Moodles = std::make_shared<Moodles>(this);
         this.xp = std::make_shared<XP>(this, this);
      } else {
         this.BodyDamage = nullptr;
         this.Moodles = nullptr;
         this.xp = nullptr;
      }

      this.Patience = Rand.Next(this.PatienceMin, this.PatienceMax);
      this.x = var2 + 0.5F;
      this.y = var3 + 0.5F;
      this.z = var4;
      this.scriptnx = this.lx = this.nx = var2;
      this.scriptny = this.ly = this.ny = var3;
      if (var1 != nullptr) {
         this.current = this.getCell().getGridSquare((int)var2, (int)var3, (int)var4);
      }

      this.offsetY = 0.0F;
      this.offsetX = 0.0F;
      this.stateMachine = std::make_shared<StateMachine>(this);
      this.setDefaultState(IdleState.instance());
      this.inventory.parent = this;
      this.inventory.setExplored(true);
      this.chatElement = std::make_shared<ChatElement>(this, 1, "character");
      if (GameClient.bClient || GameServer.bServer) {
         this.namesPrefix.put("admin", "[col=255,0,0]Admin[/] ");
         this.namesPrefix.put("moderator", "[col=0,128,47]Moderator[/] ");
         this.namesPrefix.put("overseer", "[col=26,26,191]Overseer[/] ");
         this.namesPrefix.put("gm", "[col=213,123,23]GM[/] ");
         this.namesPrefix.put("observer", "[col=128,128,128]Observer[/] ");
      }

      this.m_animationRecorder = std::make_shared<AnimationPlayerRecorder>(this);
      this.advancedAnimator = std::make_unique<AdvancedAnimator>();
      this.advancedAnimator.init(this);
      this.advancedAnimator.animCallbackHandlers.push_back(this);
      this.advancedAnimator.SetAnimSet(AnimationSet.GetAnimationSet(this.GetAnimSetName(), false));
      this.advancedAnimator.setRecorder(this.m_animationRecorder);
      this.actionContext.onStateChanged.push_back(this);
      this.m_animStateTriggerWatcher = std::make_shared<PredicatedFileWatcher>(
         ZomboidFileSystem.instance.getMessagingDirSub("Trigger_SetAnimState.xml"), AnimStateTriggerXmlFile.class, this::onTrigger_setAnimStateToTriggerFile
      );
   }

    void registerVariableCallbacks() {
      this.setVariable("hitreaction", this::getHitReaction, this::setHitReaction);
      this.setVariable("collidetype", this::getCollideType, this::setCollideType);
      this.setVariable("footInjuryType", this::getFootInjuryType);
      this.setVariable("bumptype", this::getBumpType, this::setBumpType);
      this.setVariable("sitonground", this::isSitOnGround, this::setSitOnGround);
      this.setVariable("canclimbdownrope", this::canClimbDownSheetRopeInCurrentSquare);
      this.setVariable("frombehind", this::isHitFromBehind, this::setHitFromBehind);
      this.setVariable("fallonfront", this::isFallOnFront, this::setFallOnFront);
      this.setVariable("hashitreaction", this::hasHitReaction);
      this.setVariable("intrees", this::isInTreesNoBush);
      this.setVariable("bumped", this::isBumped);
      this.setVariable("BumpDone", false, this::isBumpDone, this::setBumpDone);
      this.setVariable("BumpFall", false, this::isBumpFall, this::setBumpFall);
      this.setVariable("BumpFallType", "", this::getBumpFallType, this::setBumpFallType);
      this.setVariable("BumpStaggered", false, this::isBumpStaggered, this::setBumpStaggered);
      this.setVariable("bonfloor", this::isOnFloor, this::setOnFloor);
      this.setVariable("rangedweaponempty", this::isRangedWeaponEmpty, this::setRangedWeaponEmpty);
      this.setVariable("footInjury", this::hasFootInjury);
      this.setVariable("ChopTreeSpeed", 1.0F, this::getChopTreeSpeed);
      this.setVariable("MoveDelta", 1.0F, this::getMoveDelta, this::setMoveDelta);
      this.setVariable("TurnDelta", 1.0F, this::getTurnDelta, this::setTurnDelta);
      this.setVariable("angle", this::getDirectionAngle, this::setDirectionAngle);
      this.setVariable("animAngle", this::getAnimAngle);
      this.setVariable("twist", this::getTwist);
      this.setVariable("targetTwist", this::getTargetTwist);
      this.setVariable("maxTwist", this.m_maxTwist, this::getMaxTwist, this::setMaxTwist);
      this.setVariable("shoulderTwist", this::getShoulderTwist);
      this.setVariable("excessTwist", this::getExcessTwist);
      this.setVariable("angleStepDelta", this::getAnimAngleStepDelta);
      this.setVariable("angleTwistDelta", this::getAnimAngleTwistDelta);
      this.setVariable("isTurning", false, this::isTurning, this::setTurning);
      this.setVariable("isTurning90", false, this::isTurning90, this::setTurning90);
      this.setVariable("isTurningAround", false, this::isTurningAround, this::setTurningAround);
      this.setVariable("bMoving", false, this::isMoving, this::setMoving);
      this.setVariable("beenMovingFor", this::getBeenMovingFor);
      this.setVariable("previousState", this::getPreviousActionContextStateName);
      this.setVariable("momentumScalar", this::getMomentumScalar, this::setMomentumScalar);
      this.setVariable("hasTimedActions", this::hasTimedActions);
      if (DebugOptions.instance.char.Debug.RegisterDebugVariables.getValue()) {
         this.registerDebugGameVariables();
      }

      this.setVariable("CriticalHit", this::isCriticalHit, this::setCriticalHit);
      this.setVariable("bKnockedDown", this::isKnockedDown, this::setKnockedDown);
      this.setVariable("bdead", this::isDead);
   }

    void updateRecoilVar() {
      this.setVariable("recoilVarY", 0.0F);
      this.setVariable("recoilVarX", 0.0F + this.getPerkLevel(Perks.Aiming) / 10.0F);
   }

    void registerDebugGameVariables() {
      for (int var1 = 0; var1 < 2; var1++) {
         for (int var2 = 0; var2 < 9; var2++) {
            this.dbgRegisterAnimTrackVariable(var1, var2);
         }
      }

      this.setVariable("dbg.anm.dx", (CallbackGetStrongTyped)(() -> this.getDeferredMovement(tempo).x / GameTime.instance.getMultiplier()));
      this.setVariable("dbg.anm.dy", (CallbackGetStrongTyped)(() -> this.getDeferredMovement(tempo).y / GameTime.instance.getMultiplier()));
      this.setVariable("dbg.anm.da", (CallbackGetStrongTyped)(() -> this.getDeferredAngleDelta() / GameTime.instance.getMultiplier()));
      this.setVariable("dbg.anm.daw", this::getDeferredRotationWeight);
      this.setVariable(
         "dbg.forward",
         (zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackString.CallbackGetStrongTyped)(() -> this.getForwardDirection().x
            + "; "
            + this.getForwardDirection().y)
      );
      this.setVariable("dbg.anm.blend.fbx_x", (CallbackGetStrongTyped)(() -> DebugOptions.instance.Animation.BlendUseFbx.getValue() ? 1.0F : 0.0F));
      this.m_bDebugVariablesRegistered = true;
   }

    void dbgRegisterAnimTrackVariable(int var1, int var2) {
      this.setVariable(
         std::string.format("dbg.anm.track%d%d", var1, var2),
         (zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackString.CallbackGetStrongTyped)(() -> this.dbgGetAnimTrackName(var1, var2))
      );
      this.setVariable(std::string.format("dbg.anm.t.track%d%d", var1, var2), (CallbackGetStrongTyped)(() -> this.dbgGetAnimTrackTime(var1, var2)));
      this.setVariable(std::string.format("dbg.anm.w.track%d%d", var1, var2), (CallbackGetStrongTyped)(() -> this.dbgGetAnimTrackWeight(var1, var2)));
   }

    float getMomentumScalar() {
      return this.m_momentumScalar;
   }

    void setMomentumScalar(float var1) {
      this.m_momentumScalar = var1;
   }

    Vector2 getDeferredMovement(Vector2 var1) {
      if (this.m_animPlayer == nullptr) {
         var1.set(0.0F, 0.0F);
    return var1;
      } else {
         this.m_animPlayer.getDeferredMovement(var1);
    return var1;
      }
   }

    float getDeferredAngleDelta() {
      return this.m_animPlayer == nullptr ? 0.0F : this.m_animPlayer.getDeferredAngleDelta() * (180.0F / (float)Math.PI);
   }

    float getDeferredRotationWeight() {
      return this.m_animPlayer == nullptr ? 0.0F : this.m_animPlayer.getDeferredRotationWeight();
   }

    bool isStrafing() {
      return this.getPath2() != nullptr && this.pfb2.isStrafing() ? true : this.isAiming();
   }

    AnimationTrack dbgGetAnimTrack(int var1, int var2) {
      if (this.m_animPlayer == nullptr) {
    return nullptr;
      } else {
    AnimationPlayer var3 = this.m_animPlayer;
    AnimationMultiTrack var4 = var3.getMultiTrack();
    std::vector var5 = var4.getTracks();
    AnimationTrack var6 = nullptr;
    int var7 = 0;
    int var8 = 0;

         for (int var9 = var5.size(); var7 < var9; var7++) {
    AnimationTrack var10 = (AnimationTrack)var5.get(var7);
    int var11 = var10.getLayerIdx();
            if (var11 == var1) {
               if (var8 == var2) {
                  var6 = var10;
                  break;
               }

               var8++;
            }
         }

    return var6;
      }
   }

    std::string dbgGetAnimTrackName(int var1, int var2) {
    AnimationTrack var3 = this.dbgGetAnimTrack(var1, var2);
      return var3 != nullptr ? var3.name : "";
   }

    float dbgGetAnimTrackTime(int var1, int var2) {
    AnimationTrack var3 = this.dbgGetAnimTrack(var1, var2);
      return var3 != nullptr ? var3.getCurrentTime() : 0.0F;
   }

    float dbgGetAnimTrackWeight(int var1, int var2) {
    AnimationTrack var3 = this.dbgGetAnimTrack(var1, var2);
      return var3 != nullptr ? var3.BlendDelta : 0.0F;
   }

    float getTwist() {
      return this.m_animPlayer != nullptr ? (180.0F / (float)Math.PI) * this.m_animPlayer.getTwistAngle() : 0.0F;
   }

    float getShoulderTwist() {
      return this.m_animPlayer != nullptr ? (180.0F / (float)Math.PI) * this.m_animPlayer.getShoulderTwistAngle() : 0.0F;
   }

    float getMaxTwist() {
      return this.m_maxTwist;
   }

    void setMaxTwist(float var1) {
      this.m_maxTwist = var1;
   }

    float getExcessTwist() {
      return this.m_animPlayer != nullptr ? (180.0F / (float)Math.PI) * this.m_animPlayer.getExcessTwistAngle() : 0.0F;
   }

    float getAbsoluteExcessTwist() {
      return Math.abs(this.getExcessTwist());
   }

    float getAnimAngleTwistDelta() {
      return this.m_animPlayer != nullptr ? this.m_animPlayer.angleTwistDelta : 0.0F;
   }

    float getAnimAngleStepDelta() {
      return this.m_animPlayer != nullptr ? this.m_animPlayer.angleStepDelta : 0.0F;
   }

    float getTargetTwist() {
      return this.m_animPlayer != nullptr ? (180.0F / (float)Math.PI) * this.m_animPlayer.getTargetTwistAngle() : 0.0F;
   }

    bool isRangedWeaponEmpty() {
      return this.bRangedWeaponEmpty;
   }

    void setRangedWeaponEmpty(bool var1) {
      this.bRangedWeaponEmpty = var1;
   }

    bool hasFootInjury() {
      return !StringUtils.isNullOrWhitespace(this.getFootInjuryType());
   }

    bool isInTrees2(bool var1) {
      if (this.isCurrentState(BumpedState.instance())) {
    return false;
      } else {
    IsoGridSquare var2 = this.getCurrentSquare();
         if (var2 == nullptr) {
    return false;
         } else {
            if (var2.Has(IsoObjectType.tree)) {
    IsoTree var3 = var2.getTree();
               if (var3 == nullptr || var1 && var3.getSize() > 2 || !var1) {
    return true;
               }
            }

    std::string var4 = var2.getProperties().Val("Movement");
            return !"HedgeLow".equalsIgnoreCase(var4) && !"HedgeHigh".equalsIgnoreCase(var4) ? !var1 && var2.getProperties().Is("Bush") : true;
         }
      }
   }

    bool isInTreesNoBush() {
      return this.isInTrees2(true);
   }

    bool isInTrees() {
      return this.isInTrees2(false);
   }

   public static std::unordered_map<int, SurvivorDesc> getSurvivorMap() {
    return SurvivorMap;
   }

   public static int[] getLevelUpLevels() {
    return LevelUpLevels;
   }

    static Vector2 getTempo() {
    return tempo;
   }

    static ColorInfo getInf() {
    return inf;
   }

    GameCharacterAIBrain getBrain() {
      return this.GameCharacterAIBrain;
   }

    bool getIsNPC() {
      return this.isNPC;
   }

    void setIsNPC(bool var1) {
      this.isNPC = var1;
   }

    BaseCharacterSoundEmitter getEmitter() {
      return this.emitter;
   }

    void updateEmitter() {
      this.getFMODParameters().update();
      if (IsoWorld.instance.emitterUpdate || this.emitter.hasSoundsToStart()) {
         if (this.isZombie() && this.isProne()) {
            SwipeStatePlayer.getBoneWorldPos(this, "Bip01_Head", tempVectorBonePos);
            this.emitter.set(tempVectorBonePos.x, tempVectorBonePos.y, this.z);
            this.emitter.tick();
         } else {
            this.emitter.set(this.x, this.y, this.z);
            this.emitter.tick();
         }
      }
   }

    void doDeferredMovement() {
      if (GameClient.bClient && this.getHitReactionNetworkAI() != nullptr) {
         if (this.getHitReactionNetworkAI().isStarted()) {
            this.getHitReactionNetworkAI().move();
            return;
         }

         if (this.isDead() && this.getHitReactionNetworkAI().isDoSkipMovement()) {
            return;
         }
      }

    AnimationPlayer var1 = this.getAnimationPlayer();
      if (var1 != nullptr) {
         if (this.getPath2() != nullptr && !this.isCurrentState(ClimbOverFenceState.instance()) && !this.isCurrentState(ClimbThroughWindowState.instance())) {
            if (this.isCurrentState(WalkTowardState.instance())) {
               DebugLog.General.warn("WalkTowardState but path2 != nullptr");
               this.setPath2(nullptr);
            }
         } else {
            if (GameClient.bClient) {
               if (dynamic_cast<IsoZombie*>(this) != nullptr && ((IsoZombie)this).isRemoteZombie()) {
                  if (this.getCurrentState() != ClimbOverFenceState.instance()
                     && this.getCurrentState() != ClimbThroughWindowState.instance()
                     && this.getCurrentState() != ClimbOverWallState.instance()
                     && this.getCurrentState() != StaggerBackState.instance()
                     && this.getCurrentState() != ZombieHitReactionState.instance()
                     && this.getCurrentState() != ZombieFallDownState.instance()
                     && this.getCurrentState() != ZombieFallingState.instance()
                     && this.getCurrentState() != ZombieOnGroundState.instance()
                     && this.getCurrentState() != AttackNetworkState.instance()) {
                     return;
                  }
               } else if (dynamic_cast<IsoPlayer*>(this) != nullptr
                  && !((IsoPlayer)this).isLocalPlayer()
                  && !this.isCurrentState(CollideWithWallState.instance())
                  && !this.isCurrentState(PlayerGetUpState.instance())
                  && !this.isCurrentState(BumpedState.instance())) {
                  return;
               }
            }

    Vector2 var2 = tempo;
            this.getDeferredMovement(var2);
            if (GameClient.bClient && dynamic_cast<IsoZombie*>(this) != nullptr && this.isCurrentState(StaggerBackState.instance())) {
    float var3 = var2.getLength();
               var2.set(this.getHitDir());
               var2.setLength(var3);
            }

            this.MoveUnmodded(var2);
         }
      }
   }

    ActionContext getActionContext() {
    return nullptr;
   }

    std::string getPreviousActionContextStateName() {
    ActionContext var1 = this.getActionContext();
    return var1 = = nullptr ? "" : var1.getPreviousStateName();
   }

    std::string getCurrentActionContextStateName() {
    ActionContext var1 = this.getActionContext();
    return var1 = = nullptr ? "" : var1.getCurrentStateName();
   }

    bool hasAnimationPlayer() {
      return this.m_animPlayer != nullptr;
   }

    AnimationPlayer getAnimationPlayer() {
    Model var1 = ModelManager.instance.getBodyModel(this);
    bool var2 = false;
      if (this.m_animPlayer != nullptr && this.m_animPlayer.getModel() != var1) {
         var2 = this.m_animPlayer.getMultiTrack().getTrackCount() > 0;
         this.m_animPlayer = (AnimationPlayer)Pool.tryRelease(this.m_animPlayer);
      }

      if (this.m_animPlayer == nullptr) {
         this.m_animPlayer = AnimationPlayer.alloc(var1);
         this.onAnimPlayerCreated(this.m_animPlayer);
         if (var2) {
            this.getAdvancedAnimator().OnAnimDataChanged(false);
         }
      }

      return this.m_animPlayer;
   }

    void releaseAnimationPlayer() {
      this.m_animPlayer = (AnimationPlayer)Pool.tryRelease(this.m_animPlayer);
   }

    void onAnimPlayerCreated(AnimationPlayer var1) {
      var1.setRecorder(this.m_animationRecorder);
      var1.setTwistBones(new std::string[]{"Bip01_Pelvis", "Bip01_Spine", "Bip01_Spine1", "Bip01_Neck", "Bip01_Head"});
      var1.setCounterRotationBone("Bip01");
   }

    void updateAnimationRecorderState() {
      if (this.m_animPlayer != nullptr) {
         if (IsoWorld.isAnimRecorderDiscardTriggered()) {
            this.m_animPlayer.discardRecording();
         }

    bool var1 = IsoWorld.isAnimRecorderActive();
    bool var2 = var1 && !this.isSceneCulled();
         if (var2) {
            this.getAnimationPlayerRecorder().logCharacterPos();
         }

         this.m_animPlayer.setRecording(var2);
      }
   }

    AdvancedAnimator getAdvancedAnimator() {
      return this.advancedAnimator;
   }

    ModelInstance getModelInstance() {
      if (this.legsSprite == nullptr) {
    return nullptr;
      } else {
         return this.legsSprite.modelSlot == nullptr ? nullptr : this.legsSprite.modelSlot.model;
      }
   }

    std::string getCurrentStateName() {
      return this.stateMachine.getCurrent() == nullptr ? nullptr : this.stateMachine.getCurrent().getName();
   }

    std::string getPreviousStateName() {
      return this.stateMachine.getPrevious() == nullptr ? nullptr : this.stateMachine.getPrevious().getName();
   }

    std::string getAnimationDebug() {
      return this.advancedAnimator != nullptr ? this.instancename + "\n" + this.advancedAnimator.GetDebug() : this.instancename + "\n - No Animator";
   }

    std::string getTalkerType() {
      return this.chatElement.getTalkerType();
   }

    bool isAnimForecasted() {
      return System.currentTimeMillis() < this.isAnimForecasted;
   }

    void setAnimForecasted(int var1) {
      this.isAnimForecasted = System.currentTimeMillis() + var1;
   }

    void resetModel() {
      ModelManager.instance.Reset(this);
   }

    void resetModelNextFrame() {
      ModelManager.instance.ResetNextFrame(this);
   }

    void onTrigger_setClothingToXmlTriggerFile(TriggerXmlFile var1) {
      OutfitManager.Reload();
      if (!StringUtils.isNullOrWhitespace(var1.outfitName)) {
    std::string var2 = var1.outfitName;
         DebugLog.Clothing.debugln("Desired outfit name: " + var2);
    Outfit var3;
         if (var1.isMale) {
            var3 = OutfitManager.instance.FindMaleOutfit(var2);
         } else {
            var3 = OutfitManager.instance.FindFemaleOutfit(var2);
         }

         if (var3 == nullptr) {
            DebugLog.Clothing.error("Could not find outfit: " + var2);
            return;
         }

         if (this.bFemale == var1.isMale && dynamic_cast<IHumanVisual*>(this) != nullptr) {
            ((IHumanVisual)this).getHumanVisual().clear();
         }

         this.bFemale = !var1.isMale;
         if (this.descriptor != nullptr) {
            this.descriptor.setFemale(this.bFemale);
         }

         this.dressInNamedOutfit(var3.m_Name);
         this.advancedAnimator.OnAnimDataChanged(false);
         if (dynamic_cast<IsoPlayer*>(this) != nullptr) {
            LuaEventManager.triggerEvent("OnClothingUpdated", this);
         }
      } else if (!StringUtils.isNullOrWhitespace(var1.clothingItemGUID)) {
    std::string var4 = "game";
         this.dressInClothingItem(var4 + "-" + var1.clothingItemGUID);
         if (dynamic_cast<IsoPlayer*>(this) != nullptr) {
            LuaEventManager.triggerEvent("OnClothingUpdated", this);
         }
      }

      ModelManager.instance.Reset(this);
   }

    void onTrigger_setAnimStateToTriggerFile(AnimStateTriggerXmlFile var1) {
    std::string var2 = this.GetAnimSetName();
      if (!StringUtils.equalsIgnoreCase(var2, var1.animSet)) {
         this.setVariable("dbgForceAnim", false);
         this.restoreAnimatorStateToActionContext();
      } else {
         DebugOptions.instance.Animation.AnimLayer.AllowAnimNodeOverride.setValue(var1.forceAnim);
         if (this.advancedAnimator.containsState(var1.stateName)) {
            this.setVariable("dbgForceAnim", var1.forceAnim);
            this.setVariable("dbgForceAnimStateName", var1.stateName);
            this.setVariable("dbgForceAnimNodeName", var1.nodeName);
            this.setVariable("dbgForceAnimScalars", var1.setScalarValues);
            this.setVariable("dbgForceScalar", var1.scalarValue);
            this.setVariable("dbgForceScalar2", var1.scalarValue2);
            this.advancedAnimator.SetState(var1.stateName);
         } else {
            DebugLog.Animation.error("State not found: " + var1.stateName);
            this.restoreAnimatorStateToActionContext();
         }
      }
   }

    void restoreAnimatorStateToActionContext() {
      if (this.actionContext.getCurrentState() != nullptr) {
         this.advancedAnimator
            .SetState(this.actionContext.getCurrentStateName(), PZArrayUtil.listConvert(this.actionContext.getChildStates(), var0 -> var0.name));
      }
   }

    void clothingItemChanged(const std::string& var1) {
      if (this.wornItems != nullptr) {
         for (int var2 = 0; var2 < this.wornItems.size(); var2++) {
    InventoryItem var3 = this.wornItems.getItemByIndex(var2);
    ClothingItem var4 = var3.getClothingItem();
            if (var4 != nullptr && var4.isReady() && var4.m_GUID == var1)) {
    ClothingItemReference var5 = std::make_shared<ClothingItemReference>();
               var5.itemGUID = var1;
               var5.randomize();
               var3.getVisual().synchWithOutfit(var5);
               var3.synchWithVisual();
               this.resetModelNextFrame();
            }
         }
      }
   }

    void reloadOutfit() {
      ModelManager.instance.Reset(this);
   }

    bool isSceneCulled() {
      return this.m_isCulled;
   }

    void setSceneCulled(bool var1) {
      if (this.isSceneCulled() != var1) {
         try {
            if (var1) {
               ModelManager.instance.Remove(this);
            } else {
               ModelManager.instance.Add(this);
            }
         } catch (Exception var3) {
            System.err.println("Error in IsoGameCharacter.setSceneCulled(" + var1 + "):");
            ExceptionLogger.logException(var3);
            ModelManager.instance.Remove(this);
            this.legsSprite.modelSlot = nullptr;
         }
      }
   }

    void onCullStateChanged(ModelManager var1, bool var2) {
      this.m_isCulled = var2;
      if (!var2) {
         this.restoreAnimatorStateToActionContext();
         DebugFileWatcher.instance.push_back(this.m_animStateTriggerWatcher);
         OutfitManager.instance.addClothingItemListener(this);
      } else {
         DebugFileWatcher.instance.remove(this.m_animStateTriggerWatcher);
         OutfitManager.instance.removeClothingItemListener(this);
      }
   }

    void dressInRandomOutfit() {
      if (DebugLog.isEnabled(DebugType.Clothing)) {
         DebugLog.Clothing.println("IsoGameCharacter.dressInRandomOutfit>");
      }

    Outfit var1 = OutfitManager.instance.GetRandomOutfit(this.isFemale());
      if (var1 != nullptr) {
         this.dressInNamedOutfit(var1.m_Name);
      }
   }

    void dressInNamedOutfit(const std::string& var1) {
   }

    void dressInPersistentOutfit(const std::string& var1) {
    int var2 = PersistentOutfits.instance.pickOutfit(var1, this.isFemale());
      this.dressInPersistentOutfitID(var2);
   }

    void dressInPersistentOutfitID(int var1) {
   }

    std::string getOutfitName() {
      if (dynamic_cast<IHumanVisual*>(this) != nullptr) {
    HumanVisual var1 = ((IHumanVisual)this).getHumanVisual();
    Outfit var2 = var1.getOutfit();
    return var2 = = nullptr ? nullptr : var2.m_Name;
      } else {
    return nullptr;
      }
   }

    void dressInClothingItem(const std::string& var1) {
   }

    Outfit getRandomDefaultOutfit() {
    IsoGridSquare var1 = this.getCurrentSquare();
    IsoRoom var2 = var1 == nullptr ? nullptr : var1.getRoom();
    std::string var3 = var2 == nullptr ? nullptr : var2.getName();
      return ZombiesZoneDefinition.getRandomDefaultOutfit(this.isFemale(), var3);
   }

    ModelInstance getModel() {
      return this.legsSprite != nullptr && this.legsSprite.modelSlot != nullptr ? this.legsSprite.modelSlot.model : nullptr;
   }

    bool hasActiveModel() {
      return this.legsSprite != nullptr && this.legsSprite.hasActiveModel();
   }

    bool hasItems(const std::string& var1, int var2) {
    int var3 = this.inventory.getItemCount(var1);
      return var2 <= var3;
   }

    int getLevelUpLevels(int var1) {
      return LevelUpLevels.length <= var1 ? LevelUpLevels[LevelUpLevels.length - 1] : LevelUpLevels[var1];
   }

    int getLevelMaxForXp() {
      return LevelUpLevels.length;
   }

    int getXpForLevel(int var1) {
      return var1 < LevelUpLevels.length
         ? (int)(LevelUpLevels[var1] * this.LevelUpMultiplier)
         : (int)((LevelUpLevels[LevelUpLevels.length - 1] + (var1 - LevelUpLevels.length + 1) * 400) * this.LevelUpMultiplier);
   }

    void DoDeath(HandWeapon var1, IsoGameCharacter var2) {
      this.DoDeath(var1, var2, true);
   }

    void DoDeath(HandWeapon var1, IsoGameCharacter var2, bool var3) {
      this.OnDeath();
      if (this.getAttackedBy() instanceof IsoPlayer && GameServer.bServer && dynamic_cast<IsoPlayer*>(this) != nullptr) {
    std::string var4 = "";
    std::string var5 = "";
         if (SteamUtils.isSteamModeEnabled()) {
            var4 = " (" + ((IsoPlayer)this.getAttackedBy()).getSteamID() + ") ";
            var5 = " (" + ((IsoPlayer)this).getSteamID() + ") ";
         }

         LoggerManager.getLogger("pvp")
            .write(
               "user "
                  + ((IsoPlayer)this.getAttackedBy()).username
                  + var4
                  + " killed "
                  + ((IsoPlayer)this).username
                  + var5
                  + " "
                  + LoggerManager.getPlayerCoords((IsoPlayer)this),
               "IMPORTANT"
            );
         if (ServerOptions.instance.AnnounceDeath.getValue()) {
            ChatServer.getInstance().sendMessageToServerChat(((IsoPlayer)this.getAttackedBy()).username + " killed " + ((IsoPlayer)this).username + ".");
         }

         ChatServer.getInstance().sendMessageToAdminChat("user " + ((IsoPlayer)this.getAttackedBy()).username + " killed " + ((IsoPlayer)this).username);
      } else {
         if (GameServer.bServer && dynamic_cast<IsoPlayer*>(this) != nullptr) {
            LoggerManager.getLogger("user")
               .write("user " + ((IsoPlayer)this).username + " died at " + LoggerManager.getPlayerCoords((IsoPlayer)this) + " (non pvp)");
         }

         if (ServerOptions.instance.AnnounceDeath.getValue() && dynamic_cast<IsoPlayer*>(this) != nullptr && GameServer.bServer) {
            ChatServer.getInstance().sendMessageToServerChat(((IsoPlayer)this).username + " is dead.");
         }
      }

      if (this.isDead()) {
    float var9 = 0.5F;
         if (this.isZombie() && (((IsoZombie)this).bCrawling || this.getCurrentState() == ZombieOnGroundState.instance())) {
            var9 = 0.2F;
         }

         if (GameServer.bServer && var3) {
    bool var10 = this.isOnFloor() && dynamic_cast<IsoPlayer*>(var2) != nullptr && var1 != nullptr && "BareHands" == var1.getType());
            GameServer.sendBloodSplatter(var1, this.getX(), this.getY(), this.getZ() + var9, this.getHitDir(), this.isCloseKilled(), var10);
         }

         if (var1 != nullptr && SandboxOptions.instance.BloodLevel.getValue() > 1 && var3) {
    int var11 = var1.getSplatNumber();
            if (var11 < 1) {
               var11 = 1;
            }

            if (Core.bLastStand) {
               var11 *= 3;
            }

            switch (SandboxOptions.instance.BloodLevel.getValue()) {
               case 2:
                  var11 /= 2;
               case 3:
               default:
                  break;
               case 4:
                  var11 *= 2;
                  break;
               case 5:
                  var11 *= 5;
            }

            for (int var6 = 0; var6 < var11; var6++) {
               this.splatBlood(3, 0.3F);
            }
         }

         if (var1 != nullptr && SandboxOptions.instance.BloodLevel.getValue() > 1 && var3) {
            this.splatBloodFloorBig();
         }

         if (var2 != nullptr && var2.xp != nullptr) {
            var2.xp.AddXP(var1, 3);
         }

         if (SandboxOptions.instance.BloodLevel.getValue() > 1 && this.isOnFloor() && dynamic_cast<IsoPlayer*>(var2) != nullptr && var1 == ((IsoPlayer)var2).bareHands && var3) {
            this.playBloodSplatterSound();

            for (int var13 = -1; var13 <= 1; var13++) {
               for (int var15 = -1; var15 <= 1; var15++) {
                  if (var13 != 0 || var15 != 0) {
                     std::make_shared<IsoZombieGiblets>(
                        GibletType.A,
                        this.getCell(),
                        this.getX(),
                        this.getY(),
                        this.getZ() + var9,
                        var13 * Rand.Next(0.25F, 0.5F),
                        var15 * Rand.Next(0.25F, 0.5F)
                     );
                  }
               }
            }

            std::make_shared<IsoZombieGiblets>(
               GibletType.Eye, this.getCell(), this.getX(), this.getY(), this.getZ() + var9, this.getHitDir().x * 0.8F, this.getHitDir().y * 0.8F
            );
         } else if (SandboxOptions.instance.BloodLevel.getValue() > 1 && var3) {
            this.playBloodSplatterSound();
            std::make_shared<IsoZombieGiblets>(
               GibletType.A, this.getCell(), this.getX(), this.getY(), this.getZ() + var9, this.getHitDir().x * 1.5F, this.getHitDir().y * 1.5F
            );
            tempo.x = this.getHitDir().x;
            tempo.y = this.getHitDir().y;
    uint8_t var12 = 3;
    uint8_t var14 = 0;
    uint8_t var7 = 1;
            switch (SandboxOptions.instance.BloodLevel.getValue()) {
               case 1:
                  var7 = 0;
                  break;
               case 2:
                  var7 = 1;
                  var12 = 5;
                  var14 = 2;
               case 3:
               default:
                  break;
               case 4:
                  var7 = 3;
                  var12 = 2;
                  break;
               case 5:
                  var7 = 10;
                  var12 = 0;
            }

            for (int var8 = 0; var8 < var7; var8++) {
               if (Rand.Next(this.isCloseKilled() ? 8 : var12) == 0) {
                  std::make_shared<IsoZombieGiblets>(
                     GibletType.A, this.getCell(), this.getX(), this.getY(), this.getZ() + var9, this.getHitDir().x * 1.5F, this.getHitDir().y * 1.5F
                  );
               }

               if (Rand.Next(this.isCloseKilled() ? 8 : var12) == 0) {
                  std::make_shared<IsoZombieGiblets>(
                     GibletType.A, this.getCell(), this.getX(), this.getY(), this.getZ() + var9, this.getHitDir().x * 1.5F, this.getHitDir().y * 1.5F
                  );
               }

               if (Rand.Next(this.isCloseKilled() ? 8 : var12) == 0) {
                  std::make_shared<IsoZombieGiblets>(
                     GibletType.A, this.getCell(), this.getX(), this.getY(), this.getZ() + var9, this.getHitDir().x * 1.8F, this.getHitDir().y * 1.8F
                  );
               }

               if (Rand.Next(this.isCloseKilled() ? 8 : var12) == 0) {
                  std::make_shared<IsoZombieGiblets>(
                     GibletType.A, this.getCell(), this.getX(), this.getY(), this.getZ() + var9, this.getHitDir().x * 1.9F, this.getHitDir().y * 1.9F
                  );
               }

               if (Rand.Next(this.isCloseKilled() ? 4 : var14) == 0) {
                  std::make_shared<IsoZombieGiblets>(
                     GibletType.A, this.getCell(), this.getX(), this.getY(), this.getZ() + var9, this.getHitDir().x * 3.5F, this.getHitDir().y * 3.5F
                  );
               }

               if (Rand.Next(this.isCloseKilled() ? 4 : var14) == 0) {
                  std::make_shared<IsoZombieGiblets>(
                     GibletType.A, this.getCell(), this.getX(), this.getY(), this.getZ() + var9, this.getHitDir().x * 3.8F, this.getHitDir().y * 3.8F
                  );
               }

               if (Rand.Next(this.isCloseKilled() ? 4 : var14) == 0) {
                  std::make_shared<IsoZombieGiblets>(
                     GibletType.A, this.getCell(), this.getX(), this.getY(), this.getZ() + var9, this.getHitDir().x * 3.9F, this.getHitDir().y * 3.9F
                  );
               }

               if (Rand.Next(this.isCloseKilled() ? 4 : var14) == 0) {
                  std::make_shared<IsoZombieGiblets>(
                     GibletType.A, this.getCell(), this.getX(), this.getY(), this.getZ() + var9, this.getHitDir().x * 1.5F, this.getHitDir().y * 1.5F
                  );
               }

               if (Rand.Next(this.isCloseKilled() ? 4 : var14) == 0) {
                  std::make_shared<IsoZombieGiblets>(
                     GibletType.A, this.getCell(), this.getX(), this.getY(), this.getZ() + var9, this.getHitDir().x * 3.8F, this.getHitDir().y * 3.8F
                  );
               }

               if (Rand.Next(this.isCloseKilled() ? 4 : var14) == 0) {
                  std::make_shared<IsoZombieGiblets>(
                     GibletType.A, this.getCell(), this.getX(), this.getY(), this.getZ() + var9, this.getHitDir().x * 3.9F, this.getHitDir().y * 3.9F
                  );
               }

               if (Rand.Next(this.isCloseKilled() ? 9 : 6) == 0) {
                  std::make_shared<IsoZombieGiblets>(
                     GibletType.Eye, this.getCell(), this.getX(), this.getY(), this.getZ() + var9, this.getHitDir().x * 0.8F, this.getHitDir().y * 0.8F
                  );
               }
            }
         }
      }

      if (this.isDoDeathSound()) {
         this.playDeadSound();
      }

      this.setDoDeathSound(false);
   }

    bool TestIfSeen(int var1) {
    IsoPlayer var2 = IsoPlayer.players[var1];
      if (var2 != nullptr && this != var2 && !GameServer.bServer) {
    float var3 = this.DistToProper(var2);
         if (var3 > GameTime.getInstance().getViewDist()) {
    return false;
         } else {
    bool var4 = this.current.isCanSee(var1);
            if (!var4 && this.current.isCouldSee(var1)) {
               var4 = var3 < var2.getSeeNearbyCharacterDistance();
            }

            if (!var4) {
    return false;
            } else {
    ColorInfo var5 = this.getCurrentSquare().lighting[var1].lightInfo();
    float var6 = (var5.r + var5.g + var5.b) / 3.0F;
               if (var6 > 0.6F) {
                  var6 = 1.0F;
               }

    float var7 = 1.0F - var3 / GameTime.getInstance().getViewDist();
               if (var6 == 1.0F && var7 > 0.3F) {
                  var7 = 1.0F;
               }

    float var8 = var2.getDotWithForwardDirection(this.getX(), this.getY());
               if (var8 < 0.5F) {
                  var8 = 0.5F;
               }

               var6 *= var8;
               if (var6 < 0.0F) {
                  var6 = 0.0F;
               }

               if (var3 <= 1.0F) {
                  var7 = 1.0F;
                  var6 *= 2.0F;
               }

               var6 *= var7;
               var6 *= 100.0F;
               return var6 > 0.025F;
            }
         }
      } else {
    return false;
      }
   }

    void DoLand() {
      if (!(this.fallTime < 20.0F) && !this.isClimbing()) {
         if (dynamic_cast<IsoPlayer*>(this) != nullptr) {
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

         if (this.isZombie()) {
            if (this.fallTime > 50.0F) {
               this.hitDir.x = this.hitDir.y = 0.0F;
               if (!((IsoZombie)this).bCrawling && (Rand.Next(100) < 80 || this.fallTime > 80.0F)) {
                  this.setVariable("bHardFall", true);
               }

               this.playHurtSound();
    float var5 = Rand.Next(150) / 1000.0F;
               this.Health = this.Health - var5 * this.fallTime / 50.0F;
               this.setAttackedBy(nullptr);
            }
         } else {
    bool var1 = Rand.Next(80) == 0;
    float var2 = this.fallTime;
            var2 *= Math.min(1.8F, this.getInventory().getCapacityWeight() / this.getInventory().getMaxWeight());
            if (this.getCurrentSquare().getFloor() != nullptr
               && this.getCurrentSquare().getFloor().getSprite().getName() != nullptr
               && this.getCurrentSquare().getFloor().getSprite().getName().startsWith("blends_natural")) {
               var2 *= 0.8F;
               if (!var1) {
                  var1 = Rand.Next(65) == 0;
               }
            }

            if (!var1) {
               if (this.Traits.Obese.isSet() || this.Traits.Emaciated.isSet()) {
                  var2 *= 1.4F;
               }

               if (this.Traits.Overweight.isSet() || this.Traits.VeryUnderweight.isSet()) {
                  var2 *= 1.2F;
               }

               var2 *= Math.max(0.1F, 1.0F - this.getPerkLevel(Perks.Fitness) * 0.1F);
               if (this.fallTime > 135.0F) {
                  var2 = 1000.0F;
               }

               this.BodyDamage.ReduceGeneralHealth(var2);
               LuaEventManager.triggerEvent("OnPlayerGetDamage", this, "FALLDOWN", var2);
               if (this.fallTime > 70.0F) {
    int var3 = 100 - (int)(this.fallTime * 0.6);
                  if (this.getInventory().getMaxWeight() - this.getInventory().getCapacityWeight() < 2.0F) {
                     var3 = (int)(var3 - this.getInventory().getCapacityWeight() / this.getInventory().getMaxWeight() * 100.0F / 5.0F);
                  }

                  if (this.Traits.Obese.isSet() || this.Traits.Emaciated.isSet()) {
                     var3 -= 20;
                  }

                  if (this.Traits.Overweight.isSet() || this.Traits.VeryUnderweight.isSet()) {
                     var3 -= 10;
                  }

                  if (this.getPerkLevel(Perks.Fitness) > 4) {
                     var3 += (this.getPerkLevel(Perks.Fitness) - 4) * 3;
                  }

                  if (Rand.Next(100) >= var3) {
                     if (!SandboxOptions.instance.BoneFracture.getValue()) {
                        return;
                     }

    float var4 = Rand.Next(50, 80);
                     if (this.Traits.FastHealer.isSet()) {
                        var4 = Rand.Next(30, 50);
                     } else if (this.Traits.SlowHealer.isSet()) {
                        var4 = Rand.Next(80, 150);
                     }

                     switch (SandboxOptions.instance.InjurySeverity.getValue()) {
                        case 1:
                           var4 *= 0.5F;
                           break;
                        case 3:
                           var4 *= 1.5F;
                     }

                     this.getBodyDamage()
                        .getBodyPart(
                           BodyPartType.FromIndex(Rand.Next(BodyPartType.ToIndex(BodyPartType.UpperLeg_L), BodyPartType.ToIndex(BodyPartType.Foot_R) + 1))
                        )
                        .setFractureTime(var4);
                  } else if (Rand.Next(100) >= var3 - 10) {
                     this.getBodyDamage()
                        .getBodyPart(
                           BodyPartType.FromIndex(Rand.Next(BodyPartType.ToIndex(BodyPartType.UpperLeg_L), BodyPartType.ToIndex(BodyPartType.Foot_R) + 1))
                        )
                        .generateDeepWound();
                  }
               }
            }
         }
      }
   }

    IsoGameCharacter getFollowingTarget() {
      return this.FollowingTarget;
   }

    void setFollowingTarget(IsoGameCharacter var1) {
      this.FollowingTarget = var1;
   }

   public std::vector<IsoMovingObject> getLocalList() {
      return this.LocalList;
   }

   public std::vector<IsoMovingObject> getLocalNeutralList() {
      return this.LocalNeutralList;
   }

   public std::vector<IsoMovingObject> getLocalGroupList() {
      return this.LocalGroupList;
   }

   public std::vector<IsoMovingObject> getLocalRelevantEnemyList() {
      return this.LocalRelevantEnemyList;
   }

    float getDangerLevels() {
      return this.dangerLevels;
   }

    void setDangerLevels(float var1) {
      this.dangerLevels = var1;
   }

   public std::vector<PerkInfo> getPerkList() {
      return this.PerkList;
   }

    float getLeaveBodyTimedown() {
      return this.leaveBodyTimedown;
   }

    void setLeaveBodyTimedown(float var1) {
      this.leaveBodyTimedown = var1;
   }

    bool isAllowConversation() {
      return this.AllowConversation;
   }

    void setAllowConversation(bool var1) {
      this.AllowConversation = var1;
   }

    float getReanimateTimer() {
      return this.ReanimateTimer;
   }

    void setReanimateTimer(float var1) {
      this.ReanimateTimer = var1;
   }

    int getReanimAnimFrame() {
      return this.ReanimAnimFrame;
   }

    void setReanimAnimFrame(int var1) {
      this.ReanimAnimFrame = var1;
   }

    int getReanimAnimDelay() {
      return this.ReanimAnimDelay;
   }

    void setReanimAnimDelay(int var1) {
      this.ReanimAnimDelay = var1;
   }

    bool isReanim() {
      return this.Reanim;
   }

    void setReanim(bool var1) {
      this.Reanim = var1;
   }

    bool isVisibleToNPCs() {
      return this.VisibleToNPCs;
   }

    void setVisibleToNPCs(bool var1) {
      this.VisibleToNPCs = var1;
   }

    int getDieCount() {
      return this.DieCount;
   }

    void setDieCount(int var1) {
      this.DieCount = var1;
   }

    float getLlx() {
      return this.llx;
   }

    void setLlx(float var1) {
      this.llx = var1;
   }

    float getLly() {
      return this.lly;
   }

    void setLly(float var1) {
      this.lly = var1;
   }

    float getLlz() {
      return this.llz;
   }

    void setLlz(float var1) {
      this.llz = var1;
   }

    int getRemoteID() {
      return this.RemoteID;
   }

    void setRemoteID(int var1) {
      this.RemoteID = var1;
   }

    int getNumSurvivorsInVicinity() {
      return this.NumSurvivorsInVicinity;
   }

    void setNumSurvivorsInVicinity(int var1) {
      this.NumSurvivorsInVicinity = var1;
   }

    float getLevelUpMultiplier() {
      return this.LevelUpMultiplier;
   }

    void setLevelUpMultiplier(float var1) {
      this.LevelUpMultiplier = var1;
   }

    XP getXp() {
      return this.xp;
   }

    void setXp(XP var1) {
      this.xp = var1;
   }

    int getLastLocalEnemies() {
      return this.LastLocalEnemies;
   }

    void setLastLocalEnemies(int var1) {
      this.LastLocalEnemies = var1;
   }

   public std::vector<IsoMovingObject> getVeryCloseEnemyList() {
      return this.VeryCloseEnemyList;
   }

   public std::unordered_map<std::string, Location> getLastKnownLocation() {
      return this.LastKnownLocation;
   }

    IsoGameCharacter getAttackedBy() {
      return this.AttackedBy;
   }

    void setAttackedBy(IsoGameCharacter var1) {
      this.AttackedBy = var1;
   }

    bool isIgnoreStaggerBack() {
      return this.IgnoreStaggerBack;
   }

    void setIgnoreStaggerBack(bool var1) {
      this.IgnoreStaggerBack = var1;
   }

    bool isAttackWasSuperAttack() {
      return this.AttackWasSuperAttack;
   }

    void setAttackWasSuperAttack(bool var1) {
      this.AttackWasSuperAttack = var1;
   }

    int getTimeThumping() {
      return this.TimeThumping;
   }

    void setTimeThumping(int var1) {
      this.TimeThumping = var1;
   }

    int getPatienceMax() {
      return this.PatienceMax;
   }

    void setPatienceMax(int var1) {
      this.PatienceMax = var1;
   }

    int getPatienceMin() {
      return this.PatienceMin;
   }

    void setPatienceMin(int var1) {
      this.PatienceMin = var1;
   }

    int getPatience() {
      return this.Patience;
   }

    void setPatience(int var1) {
      this.Patience = var1;
   }

   public std::stack<BaseAction> getCharacterActions() {
      return this.CharacterActions;
   }

    bool hasTimedActions() {
      return !this.CharacterActions.empty() || this.getVariableBoolean("IsPerformingAnAction");
   }

    Vector2 getForwardDirection() {
      return this.m_forwardDirection;
   }

    void setForwardDirection(Vector2 var1) {
      if (var1 != nullptr) {
         this.setForwardDirection(var1.x, var1.y);
      }
   }

    void setForwardDirection(float var1, float var2) {
      this.m_forwardDirection.x = var1;
      this.m_forwardDirection.y = var2;
   }

    void zeroForwardDirectionX() {
      this.setForwardDirection(0.0F, 1.0F);
   }

    void zeroForwardDirectionY() {
      this.setForwardDirection(1.0F, 0.0F);
   }

    float getDirectionAngle() {
      return (180.0F / (float)Math.PI) * this.getForwardDirection().getDirection();
   }

    void setDirectionAngle(float var1) {
    float var2 = (float) (Math.PI / 180.0) * var1;
    Vector2 var3 = this.getForwardDirection();
      var3.setDirection(var2);
   }

    float getAnimAngle() {
      return this.m_animPlayer != nullptr && this.m_animPlayer.isReady() && !this.m_animPlayer.isBoneTransformsNeedFirstFrame()
         ? (180.0F / (float)Math.PI) * this.m_animPlayer.getAngle()
         : this.getDirectionAngle();
   }

    float getAnimAngleRadians() {
      return this.m_animPlayer != nullptr && this.m_animPlayer.isReady() && !this.m_animPlayer.isBoneTransformsNeedFirstFrame()
         ? this.m_animPlayer.getAngle()
         : this.m_forwardDirection.getDirection();
   }

    Vector2 getAnimVector(Vector2 var1) {
      return var1.setLengthAndDirection(this.getAnimAngleRadians(), 1.0F);
   }

    float getLookAngleRadians() {
      return this.m_animPlayer != nullptr && this.m_animPlayer.isReady()
         ? this.m_animPlayer.getAngle() + this.m_animPlayer.getTwistAngle()
         : this.getForwardDirection().getDirection();
   }

    Vector2 getLookVector(Vector2 var1) {
      return var1.setLengthAndDirection(this.getLookAngleRadians(), 1.0F);
   }

    float getDotWithForwardDirection(Vector3 var1) {
      return this.getDotWithForwardDirection(var1.x, var1.y);
   }

    float getDotWithForwardDirection(float var1, float var2) {
    Vector2 var3 = L_getDotWithForwardDirection.v1.set(var1 - this.getX(), var2 - this.getY());
      var3.normalize();
    Vector2 var4 = this.getLookVector(L_getDotWithForwardDirection.v2);
      var4.normalize();
      return var3.dot(var4);
   }

    bool isAsleep() {
      return this.Asleep;
   }

    void setAsleep(bool var1) {
      this.Asleep = var1;
   }

    int getZombieKills() {
      return this.ZombieKills;
   }

    void setZombieKills(int var1) {
      this.ZombieKills = var1;
   }

    int getLastZombieKills() {
      return this.LastZombieKills;
   }

    void setLastZombieKills(int var1) {
      this.LastZombieKills = var1;
   }

    bool isSuperAttack() {
      return this.superAttack;
   }

    void setSuperAttack(bool var1) {
      this.superAttack = var1;
   }

    float getForceWakeUpTime() {
      return this.ForceWakeUpTime;
   }

    void setForceWakeUpTime(float var1) {
      this.ForceWakeUpTime = var1;
   }

    void forceAwake() {
      if (this.isAsleep()) {
         this.ForceWakeUp = true;
      }
   }

    BodyDamage getBodyDamage() {
      return this.BodyDamage;
   }

    BodyDamage getBodyDamageRemote() {
      if (this.BodyDamageRemote == nullptr) {
         this.BodyDamageRemote = std::make_shared<BodyDamage>(nullptr);
      }

      return this.BodyDamageRemote;
   }

    void resetBodyDamageRemote() {
      this.BodyDamageRemote = nullptr;
   }

    State getDefaultState() {
      return this.defaultState;
   }

    void setDefaultState(State var1) {
      this.defaultState = var1;
   }

    SurvivorDesc getDescriptor() {
      return this.descriptor;
   }

    void setDescriptor(SurvivorDesc var1) {
      this.descriptor = var1;
   }

    std::string getFullName() {
      return this.descriptor != nullptr ? this.descriptor.forename + " " + this.descriptor.surname : "Bob Smith";
   }

    BaseVisual getVisual() {
      throw RuntimeException("subclasses must implement this");
   }

    ItemVisuals getItemVisuals() {
      throw RuntimeException("subclasses must implement this");
   }

    void getItemVisuals(ItemVisuals var1) {
      this.getWornItems().getItemVisuals(var1);
   }

    bool isUsingWornItems() {
      return this.wornItems != nullptr;
   }

   public std::stack<IsoBuilding> getFamiliarBuildings() {
      return this.FamiliarBuildings;
   }

    AStarPathFinderResult getFinder() {
      return this.finder;
   }

    float getFireKillRate() {
      return this.FireKillRate;
   }

    void setFireKillRate(float var1) {
      this.FireKillRate = var1;
   }

    int getFireSpreadProbability() {
      return this.FireSpreadProbability;
   }

    void setFireSpreadProbability(int var1) {
      this.FireSpreadProbability = var1;
   }

    float getHealth() {
      return this.Health;
   }

    void setHealth(float var1) {
      this.Health = var1;
   }

    bool isOnDeathDone() {
      return this.bDead;
   }

    void setOnDeathDone(bool var1) {
      this.bDead = var1;
   }

    bool isOnKillDone() {
      return this.bKill;
   }

    void setOnKillDone(bool var1) {
      this.bKill = var1;
   }

    bool isDeathDragDown() {
      return this.bDeathDragDown;
   }

    void setDeathDragDown(bool var1) {
      this.bDeathDragDown = var1;
   }

    bool isPlayingDeathSound() {
      return this.bPlayingDeathSound;
   }

    void setPlayingDeathSound(bool var1) {
      this.bPlayingDeathSound = var1;
   }

    std::string getHurtSound() {
      return this.hurtSound;
   }

    void setHurtSound(const std::string& var1) {
      this.hurtSound = var1;
   }

    bool isIgnoreMovementForDirection() {
    return false;
   }

    ItemContainer getInventory() {
      return this.inventory;
   }

    void setInventory(ItemContainer var1) {
      var1.parent = this;
      this.inventory = var1;
      this.inventory.setExplored(true);
   }

    bool isPrimaryEquipped(const std::string& var1) {
      return this.leftHandItem == nullptr ? false : this.leftHandItem.getFullType() == var1) || this.leftHandItem.getType() == var1);
   }

    InventoryItem getPrimaryHandItem() {
      return this.leftHandItem;
   }

    void setPrimaryHandItem(InventoryItem var1) {
      this.setEquipParent(this.leftHandItem, var1);
      this.leftHandItem = var1;
      if (GameClient.bClient && dynamic_cast<IsoPlayer*>(this) != nullptr && ((IsoPlayer)this).isLocalPlayer()) {
         GameClient.instance.equip((IsoPlayer)this, 0);
      }

      LuaEventManager.triggerEvent("OnEquipPrimary", this, var1);
      this.resetEquippedHandsModels();
      this.setVariable("Weapon", WeaponType.getWeaponType(this).type);
      if (var1 != nullptr && dynamic_cast<HandWeapon*>(var1) != nullptr && !StringUtils.isNullOrEmpty(((HandWeapon)var1).getFireMode())) {
         this.setVariable("FireMode", ((HandWeapon)var1).getFireMode());
      } else {
         this.clearVariable("FireMode");
      }
   }

    void setEquipParent(InventoryItem var1, InventoryItem var2) {
      if (var1 != nullptr) {
         var1.setEquipParent(nullptr);
      }

      if (var2 != nullptr) {
         var2.setEquipParent(this);
      }
   }

    void initWornItems(const std::string& var1) {
    BodyLocationGroup var2 = BodyLocations.getGroup(var1);
      this.wornItems = std::make_shared<WornItems>(var2);
   }

    WornItems getWornItems() {
      return this.wornItems;
   }

    void setWornItems(WornItems var1) {
      this.wornItems = std::make_shared<WornItems>(var1);
   }

    InventoryItem getWornItem(const std::string& var1) {
      return this.wornItems.getItem(var1);
   }

    void setWornItem(const std::string& var1, InventoryItem var2) {
      this.setWornItem(var1, var2, true);
   }

    void setWornItem(const std::string& var1, InventoryItem var2, bool var3) {
    InventoryItem var4 = this.wornItems.getItem(var1);
      if (var2 != var4) {
    IsoCell var5 = IsoWorld.instance.CurrentCell;
         if (var4 != nullptr && var5 != nullptr) {
            var5.addToProcessItemsRemove(var4);
         }

         this.wornItems.setItem(var1, var2);
         if (var2 != nullptr && var5 != nullptr) {
            if (var2.getContainer() != nullptr) {
               var2.getContainer().parent = this;
            }

            var5.addToProcessItems(var2);
         }

         if (var3 && var4 != nullptr && dynamic_cast<IsoPlayer*>(this) != nullptr && !this.getInventory().hasRoomFor(this, var4)) {
    IsoGridSquare var6 = this.getCurrentSquare();
            var6 = this.getSolidFloorAt(var6.x, var6.y, var6.z);
            if (var6 != nullptr) {
    float var7 = Rand.Next(0.1F, 0.9F);
    float var8 = Rand.Next(0.1F, 0.9F);
    float var9 = var6.getApparentZ(var7, var8) - var6.getZ();
               var6.AddWorldInventoryItem(var4, var7, var8, var9);
               this.getInventory().Remove(var4);
            }
         }

         this.resetModelNextFrame();
         if (this.clothingWetness != nullptr) {
            this.clothingWetness.changed = true;
         }

         if (GameClient.bClient && dynamic_cast<IsoPlayer*>(this) != nullptr && ((IsoPlayer)this).isLocalPlayer()) {
            GameClient.instance.sendClothing((IsoPlayer)this, var1, var2);
         }

         this.onWornItemsChanged();
      }
   }

    void removeWornItem(InventoryItem var1) {
      this.removeWornItem(var1, true);
   }

    void removeWornItem(InventoryItem var1, bool var2) {
    std::string var3 = this.wornItems.getLocation(var1);
      if (var3 != nullptr) {
         this.setWornItem(var3, nullptr, var2);
      }
   }

    void clearWornItems() {
      if (this.wornItems != nullptr) {
         this.wornItems.clear();
         if (this.clothingWetness != nullptr) {
            this.clothingWetness.changed = true;
         }

         this.onWornItemsChanged();
      }
   }

    BodyLocationGroup getBodyLocationGroup() {
      return this.wornItems == nullptr ? nullptr : this.wornItems.getBodyLocationGroup();
   }

    void onWornItemsChanged() {
   }

    void initAttachedItems(const std::string& var1) {
    AttachedLocationGroup var2 = AttachedLocations.getGroup(var1);
      this.attachedItems = std::make_shared<AttachedItems>(var2);
   }

    AttachedItems getAttachedItems() {
      return this.attachedItems;
   }

    void setAttachedItems(AttachedItems var1) {
      this.attachedItems = std::make_shared<AttachedItems>(var1);
   }

    InventoryItem getAttachedItem(const std::string& var1) {
      return this.attachedItems.getItem(var1);
   }

    void setAttachedItem(const std::string& var1, InventoryItem var2) {
    InventoryItem var3 = this.attachedItems.getItem(var1);
    IsoCell var4 = IsoWorld.instance.CurrentCell;
      if (var3 != nullptr && var4 != nullptr) {
         var4.addToProcessItemsRemove(var3);
      }

      this.attachedItems.setItem(var1, var2);
      if (var2 != nullptr && var4 != nullptr) {
    InventoryContainer var5 = (InventoryContainer)Type.tryCastTo(var2, InventoryContainer.class);
         if (var5 != nullptr && var5.getInventory() != nullptr) {
            var5.getInventory().parent = this;
         }

         var4.addToProcessItems(var2);
      }

      this.resetEquippedHandsModels();
    IsoPlayer var6 = (IsoPlayer)Type.tryCastTo(this, IsoPlayer.class);
      if (GameClient.bClient && var6 != nullptr && var6.isLocalPlayer()) {
         GameClient.instance.sendAttachedItem(var6, var1, var2);
      }

      if (!GameServer.bServer && var6 != nullptr && var6.isLocalPlayer()) {
         LuaEventManager.triggerEvent("OnClothingUpdated", this);
      }
   }

    void removeAttachedItem(InventoryItem var1) {
    std::string var2 = this.attachedItems.getLocation(var1);
      if (var2 != nullptr) {
         this.setAttachedItem(var2, nullptr);
      }
   }

    void clearAttachedItems() {
      if (this.attachedItems != nullptr) {
         this.attachedItems.clear();
      }
   }

    AttachedLocationGroup getAttachedLocationGroup() {
      return this.attachedItems == nullptr ? nullptr : this.attachedItems.getGroup();
   }

    ClothingWetness getClothingWetness() {
      return this.clothingWetness;
   }

    InventoryItem getClothingItem_Head() {
      return this.getWornItem("Hat");
   }

    void setClothingItem_Head(InventoryItem var1) {
      this.setWornItem("Hat", var1);
   }

    InventoryItem getClothingItem_Torso() {
      return this.getWornItem("Tshirt");
   }

    void setClothingItem_Torso(InventoryItem var1) {
      this.setWornItem("Tshirt", var1);
   }

    InventoryItem getClothingItem_Back() {
      return this.getWornItem("Back");
   }

    void setClothingItem_Back(InventoryItem var1) {
      this.setWornItem("Back", var1);
   }

    InventoryItem getClothingItem_Hands() {
      return this.getWornItem("Hands");
   }

    void setClothingItem_Hands(InventoryItem var1) {
      this.setWornItem("Hands", var1);
   }

    InventoryItem getClothingItem_Legs() {
      return this.getWornItem("Pants");
   }

    void setClothingItem_Legs(InventoryItem var1) {
      this.setWornItem("Pants", var1);
   }

    InventoryItem getClothingItem_Feet() {
      return this.getWornItem("Shoes");
   }

    void setClothingItem_Feet(InventoryItem var1) {
      this.setWornItem("Shoes", var1);
   }

    int getNextWander() {
      return this.NextWander;
   }

    void setNextWander(int var1) {
      this.NextWander = var1;
   }

    bool isOnFire() {
      return this.OnFire;
   }

    void setOnFire(bool var1) {
      this.OnFire = var1;
      if (GameServer.bServer) {
         if (var1) {
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

    int getPathIndex() {
      return this.pathIndex;
   }

    void setPathIndex(int var1) {
      this.pathIndex = var1;
   }

    int getPathTargetX() {
      return (int)this.getPathFindBehavior2().getTargetX();
   }

    int getPathTargetY() {
      return (int)this.getPathFindBehavior2().getTargetY();
   }

    int getPathTargetZ() {
      return (int)this.getPathFindBehavior2().getTargetZ();
   }

    InventoryItem getSecondaryHandItem() {
      return this.rightHandItem;
   }

    void setSecondaryHandItem(InventoryItem var1) {
      this.setEquipParent(this.rightHandItem, var1);
      this.rightHandItem = var1;
      if (GameClient.bClient && dynamic_cast<IsoPlayer*>(this) != nullptr && ((IsoPlayer)this).isLocalPlayer()) {
         GameClient.instance.equip((IsoPlayer)this, 1);
      }

      LuaEventManager.triggerEvent("OnEquipSecondary", this, var1);
      this.resetEquippedHandsModels();
      this.setVariable("Weapon", WeaponType.getWeaponType(this).type);
   }

    bool isHandItem(InventoryItem var1) {
      return this.isPrimaryHandItem(var1) || this.isSecondaryHandItem(var1);
   }

    bool isPrimaryHandItem(InventoryItem var1) {
      return var1 != nullptr && this.getPrimaryHandItem() == var1;
   }

    bool isSecondaryHandItem(InventoryItem var1) {
      return var1 != nullptr && this.getSecondaryHandItem() == var1;
   }

    bool isItemInBothHands(InventoryItem var1) {
      return this.isPrimaryHandItem(var1) && this.isSecondaryHandItem(var1);
   }

    bool removeFromHands(InventoryItem var1) {
    bool var2 = true;
      if (this.isPrimaryHandItem(var1)) {
         this.setPrimaryHandItem(nullptr);
      }

      if (this.isSecondaryHandItem(var1)) {
         this.setSecondaryHandItem(nullptr);
      }

    return var2;
   }

    Color getSpeakColour() {
      return this.SpeakColour;
   }

    void setSpeakColour(Color var1) {
      this.SpeakColour = var1;
   }

    void setSpeakColourInfo(ColorInfo var1) {
      this.SpeakColour = std::make_shared<Color>(var1.r, var1.g, var1.b, 1.0F);
   }

    float getSlowFactor() {
      return this.slowFactor;
   }

    void setSlowFactor(float var1) {
      this.slowFactor = var1;
   }

    float getSlowTimer() {
      return this.slowTimer;
   }

    void setSlowTimer(float var1) {
      this.slowTimer = var1;
   }

    bool isbUseParts() {
      return this.bUseParts;
   }

    void setbUseParts(bool var1) {
      this.bUseParts = var1;
   }

    bool isSpeaking() {
      return this.IsSpeaking();
   }

    void setSpeaking(bool var1) {
      this.Speaking = var1;
   }

    float getSpeakTime() {
      return this.SpeakTime;
   }

    void setSpeakTime(int var1) {
      this.SpeakTime = var1;
   }

    float getSpeedMod() {
      return this.speedMod;
   }

    void setSpeedMod(float var1) {
      this.speedMod = var1;
   }

    float getStaggerTimeMod() {
      return this.staggerTimeMod;
   }

    void setStaggerTimeMod(float var1) {
      this.staggerTimeMod = var1;
   }

    StateMachine getStateMachine() {
      return this.stateMachine;
   }

    Moodles getMoodles() {
      return this.Moodles;
   }

    Stats getStats() {
      return this.stats;
   }

   public std::stack<std::string> getUsedItemsOn() {
      return this.UsedItemsOn;
   }

    HandWeapon getUseHandWeapon() {
      return this.useHandWeapon;
   }

    void setUseHandWeapon(HandWeapon var1) {
      this.useHandWeapon = var1;
   }

    IsoSprite getLegsSprite() {
      return this.legsSprite;
   }

    void setLegsSprite(IsoSprite var1) {
      this.legsSprite = var1;
   }

    IsoGridSquare getAttackTargetSquare() {
      return this.attackTargetSquare;
   }

    void setAttackTargetSquare(IsoGridSquare var1) {
      this.attackTargetSquare = var1;
   }

    float getBloodImpactX() {
      return this.BloodImpactX;
   }

    void setBloodImpactX(float var1) {
      this.BloodImpactX = var1;
   }

    float getBloodImpactY() {
      return this.BloodImpactY;
   }

    void setBloodImpactY(float var1) {
      this.BloodImpactY = var1;
   }

    float getBloodImpactZ() {
      return this.BloodImpactZ;
   }

    void setBloodImpactZ(float var1) {
      this.BloodImpactZ = var1;
   }

    IsoSprite getBloodSplat() {
      return this.bloodSplat;
   }

    void setBloodSplat(IsoSprite var1) {
      this.bloodSplat = var1;
   }

    bool isbOnBed() {
      return this.bOnBed;
   }

    void setbOnBed(bool var1) {
      this.bOnBed = var1;
   }

    Vector2 getMoveForwardVec() {
      return this.moveForwardVec;
   }

    void setMoveForwardVec(Vector2 var1) {
      this.moveForwardVec.set(var1);
   }

    bool isPathing() {
      return this.pathing;
   }

    void setPathing(bool var1) {
      this.pathing = var1;
   }

   public std::stack<IsoGameCharacter> getLocalEnemyList() {
      return this.LocalEnemyList;
   }

   public std::stack<IsoGameCharacter> getEnemyList() {
      return this.EnemyList;
   }

    TraitCollection getTraits() {
      return this.getCharacterTraits();
   }

    CharacterTraits getCharacterTraits() {
      return this.Traits;
   }

    int getMaxWeight() {
      return this.maxWeight;
   }

    void setMaxWeight(int var1) {
      this.maxWeight = var1;
   }

    int getMaxWeightBase() {
      return this.maxWeightBase;
   }

    void setMaxWeightBase(int var1) {
      this.maxWeightBase = var1;
   }

    float getSleepingTabletDelta() {
      return this.SleepingTabletDelta;
   }

    void setSleepingTabletDelta(float var1) {
      this.SleepingTabletDelta = var1;
   }

    float getBetaEffect() {
      return this.BetaEffect;
   }

    void setBetaEffect(float var1) {
      this.BetaEffect = var1;
   }

    float getDepressEffect() {
      return this.DepressEffect;
   }

    void setDepressEffect(float var1) {
      this.DepressEffect = var1;
   }

    float getSleepingTabletEffect() {
      return this.SleepingTabletEffect;
   }

    void setSleepingTabletEffect(float var1) {
      this.SleepingTabletEffect = var1;
   }

    float getBetaDelta() {
      return this.BetaDelta;
   }

    void setBetaDelta(float var1) {
      this.BetaDelta = var1;
   }

    float getDepressDelta() {
      return this.DepressDelta;
   }

    void setDepressDelta(float var1) {
      this.DepressDelta = var1;
   }

    float getPainEffect() {
      return this.PainEffect;
   }

    void setPainEffect(float var1) {
      this.PainEffect = var1;
   }

    float getPainDelta() {
      return this.PainDelta;
   }

    void setPainDelta(float var1) {
      this.PainDelta = var1;
   }

    bool isbDoDefer() {
      return this.bDoDefer;
   }

    void setbDoDefer(bool var1) {
      this.bDoDefer = var1;
   }

    Location getLastHeardSound() {
      return this.LastHeardSound;
   }

    void setLastHeardSound(int var1, int var2, int var3) {
      this.LastHeardSound.x = var1;
      this.LastHeardSound.y = var2;
      this.LastHeardSound.z = var3;
   }

    float getLrx() {
      return this.lrx;
   }

    void setLrx(float var1) {
      this.lrx = var1;
   }

    float getLry() {
      return this.lry;
   }

    void setLry(float var1) {
      this.lry = var1;
   }

    bool isClimbing() {
      return this.bClimbing;
   }

    void setbClimbing(bool var1) {
      this.bClimbing = var1;
   }

    bool isLastCollidedW() {
      return this.lastCollidedW;
   }

    void setLastCollidedW(bool var1) {
      this.lastCollidedW = var1;
   }

    bool isLastCollidedN() {
      return this.lastCollidedN;
   }

    void setLastCollidedN(bool var1) {
      this.lastCollidedN = var1;
   }

    float getFallTime() {
      return this.fallTime;
   }

    void setFallTime(float var1) {
      this.fallTime = var1;
   }

    float getLastFallSpeed() {
      return this.lastFallSpeed;
   }

    void setLastFallSpeed(float var1) {
      this.lastFallSpeed = var1;
   }

    bool isbFalling() {
      return this.bFalling;
   }

    void setbFalling(bool var1) {
      this.bFalling = var1;
   }

    IsoBuilding getCurrentBuilding() {
      if (this.current == nullptr) {
    return nullptr;
      } else {
         return this.current.getRoom() == nullptr ? nullptr : this.current.getRoom().building;
      }
   }

    BuildingDef getCurrentBuildingDef() {
      if (this.current == nullptr) {
    return nullptr;
      } else if (this.current.getRoom() == nullptr) {
    return nullptr;
      } else {
         return this.current.getRoom().building != nullptr ? this.current.getRoom().building.def : nullptr;
      }
   }

    RoomDef getCurrentRoomDef() {
      if (this.current == nullptr) {
    return nullptr;
      } else {
         return this.current.getRoom() != nullptr ? this.current.getRoom().def : nullptr;
      }
   }

    float getTorchStrength() {
      return 0.0F;
   }

    void OnAnimEvent(AnimLayer var1, AnimEvent var2) {
      if (var2.m_EventName != nullptr) {
         if (var2.m_EventName.equalsIgnoreCase("SetVariable") && var2.m_SetVariable1 != nullptr) {
            this.setVariable(var2.m_SetVariable1, var2.m_SetVariable2);
         }

         if (var2.m_EventName.equalsIgnoreCase("ClearVariable")) {
            this.clearVariable(var2.m_ParameterValue);
         }

         if (var2.m_EventName.equalsIgnoreCase("PlaySound")) {
            this.getEmitter().playSoundImpl(var2.m_ParameterValue, this);
         }

         if (var2.m_EventName.equalsIgnoreCase("Footstep")) {
            this.DoFootstepSound(var2.m_ParameterValue);
         }

         if (var2.m_EventName.equalsIgnoreCase("DamageWhileInTrees")) {
            this.damageWhileInTrees();
         }

    int var3 = var1.getDepth();
         this.actionContext.reportEvent(var3, var2.m_EventName);
         this.stateMachine.stateAnimEvent(var3, var2);
      }
   }

    void damageWhileInTrees() {
      if (!this.isZombie() && !"Tutorial" == Core.GameMode)) {
    int var1 = 50;
    int var2 = Rand.Next(0, BodyPartType.ToIndex(BodyPartType.MAX));
         if (this.isRunning()) {
            var1 = 30;
         }

         if (this.Traits.Outdoorsman.isSet()) {
            var1 += 50;
         }

         var1 += (int)this.getBodyPartClothingDefense(var2, false, false);
         if (Rand.NextBool(var1)) {
            this.addHole(BloodBodyPartType.FromIndex(var2));
    uint8_t var5 = 6;
            if (this.Traits.ThickSkinned.isSet()) {
               var5 += 7;
            }

            if (this.Traits.ThinSkinned.isSet()) {
               var5 -= 3;
            }

            if (Rand.NextBool(var5) && (int)this.getBodyPartClothingDefense(var2, false, false) < 100) {
    BodyPart var3 = (BodyPart)this.getBodyDamage().getBodyParts().get(var2);
               if (Rand.NextBool(var5 + 10)) {
                  var3.setCut(true, true);
               } else {
                  var3.setScratched(true, true);
               }
            }
         }
      }
   }

    float getHammerSoundMod() {
    int var1 = this.getPerkLevel(Perks.Woodwork);
      if (var1 == 2) {
         return 0.8F;
      } else if (var1 == 3) {
         return 0.6F;
      } else if (var1 == 4) {
         return 0.4F;
      } else {
         return var1 >= 5 ? 0.4F : 1.0F;
      }
   }

    float getWeldingSoundMod() {
    int var1 = this.getPerkLevel(Perks.MetalWelding);
      if (var1 == 2) {
         return 0.8F;
      } else if (var1 == 3) {
         return 0.6F;
      } else if (var1 == 4) {
         return 0.4F;
      } else {
         return var1 >= 5 ? 0.4F : 1.0F;
      }
   }

    float getBarricadeTimeMod() {
    int var1 = this.getPerkLevel(Perks.Woodwork);
      if (var1 == 1) {
         return 0.8F;
      } else if (var1 == 2) {
         return 0.7F;
      } else if (var1 == 3) {
         return 0.62F;
      } else if (var1 == 4) {
         return 0.56F;
      } else if (var1 == 5) {
         return 0.5F;
      } else if (var1 == 6) {
         return 0.42F;
      } else if (var1 == 7) {
         return 0.36F;
      } else if (var1 == 8) {
         return 0.3F;
      } else if (var1 == 9) {
         return 0.26F;
      } else {
    return var1 = = 10 ? 0.2F : 0.7F;
      }
   }

    float getMetalBarricadeStrengthMod() {
      switch (this.getPerkLevel(Perks.MetalWelding)) {
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
    int var1 = this.getPerkLevel(Perks.Woodwork);
            if (var1 == 2) {
               return 1.1F;
            } else if (var1 == 3) {
               return 1.14F;
            } else if (var1 == 4) {
               return 1.18F;
            } else if (var1 == 5) {
               return 1.22F;
            } else if (var1 == 6) {
               return 1.26F;
            } else if (var1 == 7) {
               return 1.3F;
            } else if (var1 == 8) {
               return 1.34F;
            } else if (var1 == 9) {
               return 1.4F;
            } else {
    return var1 = = 10 ? 1.5F : 1.0F;
            }
      }
   }

    float getBarricadeStrengthMod() {
    int var1 = this.getPerkLevel(Perks.Woodwork);
      if (var1 == 2) {
         return 1.1F;
      } else if (var1 == 3) {
         return 1.14F;
      } else if (var1 == 4) {
         return 1.18F;
      } else if (var1 == 5) {
         return 1.22F;
      } else if (var1 == 6) {
         return 1.26F;
      } else if (var1 == 7) {
         return 1.3F;
      } else if (var1 == 8) {
         return 1.34F;
      } else if (var1 == 9) {
         return 1.4F;
      } else {
    return var1 = = 10 ? 1.5F : 1.0F;
      }
   }

    float getSneakSpotMod() {
    int var1 = this.getPerkLevel(Perks.Sneak);
    float var2 = 0.95F;
      if (var1 == 1) {
         var2 = 0.9F;
      }

      if (var1 == 2) {
         var2 = 0.8F;
      }

      if (var1 == 3) {
         var2 = 0.75F;
      }

      if (var1 == 4) {
         var2 = 0.7F;
      }

      if (var1 == 5) {
         var2 = 0.65F;
      }

      if (var1 == 6) {
         var2 = 0.6F;
      }

      if (var1 == 7) {
         var2 = 0.55F;
      }

      if (var1 == 8) {
         var2 = 0.5F;
      }

      if (var1 == 9) {
         var2 = 0.45F;
      }

      if (var1 == 10) {
         var2 = 0.4F;
      }

      return var2 * 1.2F;
   }

    float getNimbleMod() {
    int var1 = this.getPerkLevel(Perks.Nimble);
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
         return 1.38F;
      } else if (var1 == 9) {
         return 1.42F;
      } else {
    return var1 = = 10 ? 1.5F : 1.0F;
      }
   }

    float getFatigueMod() {
    int var1 = this.getPerkLevel(Perks.Fitness);
      if (var1 == 1) {
         return 0.95F;
      } else if (var1 == 2) {
         return 0.92F;
      } else if (var1 == 3) {
         return 0.89F;
      } else if (var1 == 4) {
         return 0.87F;
      } else if (var1 == 5) {
         return 0.85F;
      } else if (var1 == 6) {
         return 0.83F;
      } else if (var1 == 7) {
         return 0.81F;
      } else if (var1 == 8) {
         return 0.79F;
      } else if (var1 == 9) {
         return 0.77F;
      } else {
    return var1 = = 10 ? 0.75F : 1.0F;
      }
   }

    float getLightfootMod() {
    int var1 = this.getPerkLevel(Perks.Lightfoot);
      if (var1 == 1) {
         return 0.9F;
      } else if (var1 == 2) {
         return 0.79F;
      } else if (var1 == 3) {
         return 0.71F;
      } else if (var1 == 4) {
         return 0.65F;
      } else if (var1 == 5) {
         return 0.59F;
      } else if (var1 == 6) {
         return 0.52F;
      } else if (var1 == 7) {
         return 0.45F;
      } else if (var1 == 8) {
         return 0.37F;
      } else if (var1 == 9) {
         return 0.3F;
      } else {
    return var1 = = 10 ? 0.2F : 0.99F;
      }
   }

    float getPacingMod() {
    int var1 = this.getPerkLevel(Perks.Fitness);
      if (var1 == 1) {
         return 0.8F;
      } else if (var1 == 2) {
         return 0.75F;
      } else if (var1 == 3) {
         return 0.7F;
      } else if (var1 == 4) {
         return 0.65F;
      } else if (var1 == 5) {
         return 0.6F;
      } else if (var1 == 6) {
         return 0.57F;
      } else if (var1 == 7) {
         return 0.53F;
      } else if (var1 == 8) {
         return 0.49F;
      } else if (var1 == 9) {
         return 0.46F;
      } else {
    return var1 = = 10 ? 0.43F : 0.9F;
      }
   }

    float getHyperthermiaMod() {
    float var1 = 1.0F;
      if (this.getMoodles().getMoodleLevel(MoodleType.Hyperthermia) > 1) {
         var1 = 1.0F;
         if (this.getMoodles().getMoodleLevel(MoodleType.Hyperthermia) == 4) {
            var1 = 2.0F;
         }
      }

    return var1;
   }

    float getHittingMod() {
    int var1 = this.getPerkLevel(Perks.Strength);
      if (var1 == 1) {
         return 0.8F;
      } else if (var1 == 2) {
         return 0.85F;
      } else if (var1 == 3) {
         return 0.9F;
      } else if (var1 == 4) {
         return 0.95F;
      } else if (var1 == 5) {
         return 1.0F;
      } else if (var1 == 6) {
         return 1.05F;
      } else if (var1 == 7) {
         return 1.1F;
      } else if (var1 == 8) {
         return 1.15F;
      } else if (var1 == 9) {
         return 1.2F;
      } else {
    return var1 = = 10 ? 1.25F : 0.75F;
      }
   }

    float getShovingMod() {
    int var1 = this.getPerkLevel(Perks.Strength);
      if (var1 == 1) {
         return 0.8F;
      } else if (var1 == 2) {
         return 0.85F;
      } else if (var1 == 3) {
         return 0.9F;
      } else if (var1 == 4) {
         return 0.95F;
      } else if (var1 == 5) {
         return 1.0F;
      } else if (var1 == 6) {
         return 1.05F;
      } else if (var1 == 7) {
         return 1.1F;
      } else if (var1 == 8) {
         return 1.15F;
      } else if (var1 == 9) {
         return 1.2F;
      } else {
    return var1 = = 10 ? 1.25F : 0.75F;
      }
   }

    float getRecoveryMod() {
    int var1 = this.getPerkLevel(Perks.Fitness);
    float var2 = 0.0F;
      if (var1 == 0) {
         var2 = 0.7F;
      }

      if (var1 == 1) {
         var2 = 0.8F;
      }

      if (var1 == 2) {
         var2 = 0.9F;
      }

      if (var1 == 3) {
         var2 = 1.0F;
      }

      if (var1 == 4) {
         var2 = 1.1F;
      }

      if (var1 == 5) {
         var2 = 1.2F;
      }

      if (var1 == 6) {
         var2 = 1.3F;
      }

      if (var1 == 7) {
         var2 = 1.4F;
      }

      if (var1 == 8) {
         var2 = 1.5F;
      }

      if (var1 == 9) {
         var2 = 1.55F;
      }

      if (var1 == 10) {
         var2 = 1.6F;
      }

      if (this.Traits.Obese.isSet()) {
         var2 = (float)(var2 * 0.4);
      }

      if (this.Traits.Overweight.isSet()) {
         var2 = (float)(var2 * 0.7);
      }

      if (this.Traits.VeryUnderweight.isSet()) {
         var2 = (float)(var2 * 0.7);
      }

      if (this.Traits.Emaciated.isSet()) {
         var2 = (float)(var2 * 0.3);
      }

      if (dynamic_cast<IsoPlayer*>(this) != nullptr) {
         if (((IsoPlayer)this).getNutrition().getLipids() < -1500.0F) {
            var2 = (float)(var2 * 0.2);
         } else if (((IsoPlayer)this).getNutrition().getLipids() < -1000.0F) {
            var2 = (float)(var2 * 0.5);
         }

         if (((IsoPlayer)this).getNutrition().getProteins() < -1500.0F) {
            var2 = (float)(var2 * 0.2);
         } else if (((IsoPlayer)this).getNutrition().getProteins() < -1000.0F) {
            var2 = (float)(var2 * 0.5);
         }
      }

    return var2;
   }

    float getWeightMod() {
    int var1 = this.getPerkLevel(Perks.Strength);
      if (var1 == 1) {
         return 0.9F;
      } else if (var1 == 2) {
         return 1.07F;
      } else if (var1 == 3) {
         return 1.24F;
      } else if (var1 == 4) {
         return 1.41F;
      } else if (var1 == 5) {
         return 1.58F;
      } else if (var1 == 6) {
         return 1.75F;
      } else if (var1 == 7) {
         return 1.92F;
      } else if (var1 == 8) {
         return 2.09F;
      } else if (var1 == 9) {
         return 2.26F;
      } else {
    return var1 = = 10 ? 2.5F : 0.8F;
      }
   }

    int getHitChancesMod() {
    int var1 = this.getPerkLevel(Perks.Aiming);
      if (var1 == 1) {
    return 1;
      } else if (var1 == 2) {
    return 1;
      } else if (var1 == 3) {
    return 2;
      } else if (var1 == 4) {
    return 2;
      } else if (var1 == 5) {
    return 3;
      } else if (var1 == 6) {
    return 3;
      } else if (var1 == 7) {
    return 4;
      } else if (var1 == 8) {
    return 4;
      } else if (var1 == 9) {
    return 5;
      } else {
    return var1 = = 10 ? 5 : 1;
      }
   }

    float getSprintMod() {
    int var1 = this.getPerkLevel(Perks.Sprinting);
      if (var1 == 1) {
         return 1.1F;
      } else if (var1 == 2) {
         return 1.15F;
      } else if (var1 == 3) {
         return 1.2F;
      } else if (var1 == 4) {
         return 1.25F;
      } else if (var1 == 5) {
         return 1.3F;
      } else if (var1 == 6) {
         return 1.35F;
      } else if (var1 == 7) {
         return 1.4F;
      } else if (var1 == 8) {
         return 1.45F;
      } else if (var1 == 9) {
         return 1.5F;
      } else {
    return var1 = = 10 ? 1.6F : 0.9F;
      }
   }

    int getPerkLevel(Perk var1) {
    PerkInfo var2 = this.getPerkInfo(var1);
      return var2 != nullptr ? var2.level : 0;
   }

    void setPerkLevelDebug(Perk var1, int var2) {
    PerkInfo var3 = this.getPerkInfo(var1);
      if (var3 != nullptr) {
         var3.level = var2;
      }

      if (GameClient.bClient && dynamic_cast<IsoPlayer*>(this) != nullptr) {
         GameClient.sendPerks((IsoPlayer)this);
      }
   }

    void LoseLevel(Perk var1) {
    PerkInfo var2 = this.getPerkInfo(var1);
      if (var2 != nullptr) {
         var2.level--;
         if (var2.level < 0) {
            var2.level = 0;
         }

         LuaEventManager.triggerEvent("LevelPerk", this, var1, var2.level, false);
         if (var1 == Perks.Sneak && GameClient.bClient && dynamic_cast<IsoPlayer*>(this) != nullptr) {
            GameClient.sendPerks((IsoPlayer)this);
         }
      } else {
         LuaEventManager.triggerEvent("LevelPerk", this, var1, 0, false);
      }
   }

    void LevelPerk(Perk var1, bool var2) {
      Objects.requireNonNull(var1, "perk is nullptr");
      if (var1 == Perks.MAX) {
         throw IllegalArgumentException("perk == Perks.MAX");
      } else {
    IsoPlayer var3 = (IsoPlayer)Type.tryCastTo(this, IsoPlayer.class);
    PerkInfo var4 = this.getPerkInfo(var1);
         if (var4 != nullptr) {
            var4.level++;
            if (var3 != nullptr && !"Tutorial" == Core.GameMode) && this.getHoursSurvived() > 0.016666666666666666) {
               HaloTextHelper.addTextWithArrow(var3, "+1 " + var1.getName(), true, HaloTextHelper.getColorGreen());
            }

            if (var4.level > 10) {
               var4.level = 10;
            }

            if (GameClient.bClient && var3 != nullptr) {
               GameClient.instance.sendSyncXp(var3);
            }

            LuaEventManager.triggerEventGarbage("LevelPerk", this, var1, var4.level, true);
            if (GameClient.bClient && var3 != nullptr) {
               GameClient.sendPerks(var3);
            }
         } else {
            var4 = std::make_shared<PerkInfo>(this);
            var4.perk = var1;
            var4.level = 1;
            this.PerkList.push_back(var4);
            if (var3 != nullptr && !"Tutorial" == Core.GameMode) && this.getHoursSurvived() > 0.016666666666666666) {
               HaloTextHelper.addTextWithArrow(var3, "+1 " + var1.getName(), true, HaloTextHelper.getColorGreen());
            }

            if (GameClient.bClient && dynamic_cast<IsoPlayer*>(this) != nullptr) {
               GameClient.instance.sendSyncXp(var3);
            }

            LuaEventManager.triggerEvent("LevelPerk", this, var1, var4.level, true);
         }
      }
   }

    void LevelPerk(Perk var1) {
      this.LevelPerk(var1, true);
   }

    void level0(Perk var1) {
    PerkInfo var2 = this.getPerkInfo(var1);
      if (var2 != nullptr) {
         var2.level = 0;
      }
   }

    Location getLastKnownLocationOf(const std::string& var1) {
      return this.LastKnownLocation.containsKey(var1) ? this.LastKnownLocation.get(var1) : nullptr;
   }

    void ReadLiterature(Literature var1) {
      this.stats.stress = this.stats.stress + var1.getStressChange();
      this.getBodyDamage().JustReadSomething(var1);
      if (var1.getTeachedRecipes() != nullptr) {
         for (int var2 = 0; var2 < var1.getTeachedRecipes().size(); var2++) {
            if (!this.getKnownRecipes().contains(var1.getTeachedRecipes().get(var2))) {
               this.getKnownRecipes().push_back((std::string)var1.getTeachedRecipes().get(var2));
            }
         }
      }

      var1.Use();
   }

    void OnDeath() {
      LuaEventManager.triggerEvent("OnCharacterDeath", this);
   }

    void splatBloodFloorBig() {
      if (this.getCurrentSquare() != nullptr && this.getCurrentSquare().getChunk() != nullptr) {
         this.getCurrentSquare().getChunk().addBloodSplat(this.x, this.y, this.z, Rand.Next(20));
      }
   }

    void splatBloodFloor() {
      if (this.getCurrentSquare() != nullptr) {
         if (this.getCurrentSquare().getChunk() != nullptr) {
            if (this.isDead() && Rand.Next(10) == 0) {
               this.getCurrentSquare().getChunk().addBloodSplat(this.x, this.y, this.z, Rand.Next(20));
            }

            if (Rand.Next(14) == 0) {
               this.getCurrentSquare().getChunk().addBloodSplat(this.x, this.y, this.z, Rand.Next(8));
            }

            if (Rand.Next(50) == 0) {
               this.getCurrentSquare().getChunk().addBloodSplat(this.x, this.y, this.z, Rand.Next(20));
            }
         }
      }
   }

    int getThreatLevel() {
    int var1 = this.LocalRelevantEnemyList.size();
      var1 += this.VeryCloseEnemyList.size() * 10;
      if (var1 > 20) {
    return 3;
      } else if (var1 > 10) {
    return 2;
      } else {
         return var1 > 0 ? 1 : 0;
      }
   }

    bool isDead() {
      return this.Health <= 0.0F || this.BodyDamage != nullptr && this.BodyDamage.getHealth() <= 0.0F;
   }

    bool isAlive() {
      return !this.isDead();
   }

    void Seen(std::stack<IsoMovingObject> var1) {
      /* synchronized - TODO: add std::mutex */ (this.LocalList) {
         this.LocalList.clear();
         this.LocalList.addAll(var1);
      }
   }

    bool CanSee(IsoMovingObject var1) {
      return LosUtil.lineClear(
            this.getCell(), (int)this.getX(), (int)this.getY(), (int)this.getZ(), (int)var1.getX(), (int)var1.getY(), (int)var1.getZ(), false
         )
         != TestResults.Blocked;
   }

    IsoGridSquare getLowDangerInVicinity(int var1, int var2) {
    float var3 = -1000000.0F;
    IsoGridSquare var4 = nullptr;

      for (int var5 = 0; var5 < var1; var5++) {
    float var6 = 0.0F;
    int var7 = Rand.Next(-var2, var2);
    int var8 = Rand.Next(-var2, var2);
    IsoGridSquare var9 = this.getCell().getGridSquare((int)this.getX() + var7, (int)this.getY() + var8, (int)this.getZ());
         if (var9 != nullptr && var9.isFree(true)) {
    float var10 = var9.getMovingObjects().size();
            if (var9.getE() != nullptr) {
               var10 += var9.getE().getMovingObjects().size();
            }

            if (var9.getS() != nullptr) {
               var10 += var9.getS().getMovingObjects().size();
            }

            if (var9.getW() != nullptr) {
               var10 += var9.getW().getMovingObjects().size();
            }

            if (var9.getN() != nullptr) {
               var10 += var9.getN().getMovingObjects().size();
            }

            var6 -= var10 * 1000.0F;
            if (var6 > var3) {
               var3 = var6;
               var4 = var9;
            }
         }
      }

    return var4;
   }

    void Anger(int var1) {
    float var2 = 10.0F;
      if (Rand.Next(100) < var2) {
         var1 *= 2;
      }

      var1 = (int)(var1 * (this.stats.getStress() + 1.0F));
      var1 = (int)(var1 * (this.BodyDamage.getUnhappynessLevel() / 100.0F + 1.0F));
      this.stats.Anger += var1 / 100.0F;
   }

    bool hasEquipped(const std::string& var1) {
      if (var1.contains(".")) {
         var1 = var1.split("\\.")[1];
      }

      return this.leftHandItem != nullptr && this.leftHandItem.getType() == var1)
         ? true
         : this.rightHandItem != nullptr && this.rightHandItem.getType() == var1);
   }

    bool hasEquippedTag(const std::string& var1) {
      return this.leftHandItem != nullptr && this.leftHandItem.hasTag(var1) ? true : this.rightHandItem != nullptr && this.rightHandItem.hasTag(var1);
   }

    void setDir(IsoDirections var1) {
      this.dir = var1;
      this.getVectorFromDirection(this.m_forwardDirection);
   }

    void Callout(bool var1) {
      if (this.isCanShout()) {
         this.Callout();
         if (var1) {
            this.playEmote("shout");
         }
      }
   }

    void Callout() {
    std::string var1 = "";
    uint8_t var2 = 30;
      if (Core.getInstance().getGameMode() == "Tutorial")) {
         var1 = Translator.getText("IGUI_PlayerText_CalloutTutorial");
      } else if (this.isSneaking()) {
         var2 = 6;
         switch (Rand.Next(3)) {
            case 0:
               var1 = Translator.getText("IGUI_PlayerText_Callout1Sneak");
               break;
            case 1:
               var1 = Translator.getText("IGUI_PlayerText_Callout2Sneak");
               break;
            case 2:
               var1 = Translator.getText("IGUI_PlayerText_Callout3Sneak");
         }
      } else {
         switch (Rand.Next(3)) {
            case 0:
               var1 = Translator.getText("IGUI_PlayerText_Callout1New");
               break;
            case 1:
               var1 = Translator.getText("IGUI_PlayerText_Callout2New");
               break;
            case 2:
               var1 = Translator.getText("IGUI_PlayerText_Callout3New");
         }
      }

      WorldSoundManager.instance.addSound(this, (int)this.x, (int)this.y, (int)this.z, var2, var2);
      this.SayShout(var1);
      this.callOut = true;
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
      this.getVectorFromDirection(this.m_forwardDirection);
      if (var1.get() == 1) {
         this.descriptor = std::make_shared<SurvivorDesc>(true);
         this.descriptor.load(var1, var2, this);
         this.bFemale = this.descriptor.isFemale();
      }

      this.getVisual().load(var1, var2);
    std::vector var4 = this.inventory.load(var1, var2);
      this.savedInventoryItems.clear();

      for (int var5 = 0; var5 < var4.size(); var5++) {
         this.savedInventoryItems.push_back((InventoryItem)var4.get(var5));
      }

      this.Asleep = var1.get() == 1;
      this.ForceWakeUpTime = var1.getFloat();
      if (!this.isZombie()) {
         this.stats.load(var1, var2);
         this.BodyDamage.load(var1, var2);
         this.xp.load(var1, var2);
    std::vector var9 = this.inventory.IncludingObsoleteItems;
    int var6 = var1.getInt();
         if (var6 >= 0 && var6 < var9.size()) {
            this.leftHandItem = (InventoryItem)var9.get(var6);
         }

         var6 = var1.getInt();
         if (var6 >= 0 && var6 < var9.size()) {
            this.rightHandItem = (InventoryItem)var9.get(var6);
         }

         this.setEquipParent(nullptr, this.leftHandItem);
         this.setEquipParent(nullptr, this.rightHandItem);
      }

    bool var10 = var1.get() == 1;
      if (var10) {
         this.SetOnFire();
      }

      this.DepressEffect = var1.getFloat();
      this.DepressFirstTakeTime = var1.getFloat();
      this.BetaEffect = var1.getFloat();
      this.BetaDelta = var1.getFloat();
      this.PainEffect = var1.getFloat();
      this.PainDelta = var1.getFloat();
      this.SleepingTabletEffect = var1.getFloat();
      this.SleepingTabletDelta = var1.getFloat();
    int var12 = var1.getInt();

      for (int var7 = 0; var7 < var12; var7++) {
    ReadBook var8 = std::make_shared<ReadBook>();
         var8.fullType = GameWindow.ReadString(var1);
         var8.alreadyReadPages = var1.getInt();
         this.ReadBooks.push_back(var8);
      }

      this.reduceInfectionPower = var1.getFloat();
    int var13 = var1.getInt();

      for (int var14 = 0; var14 < var13; var14++) {
         this.knownRecipes.push_back(GameWindow.ReadString(var1));
      }

      this.lastHourSleeped = var1.getInt();
      this.timeSinceLastSmoke = var1.getFloat();
      this.beardGrowTiming = var1.getFloat();
      this.hairGrowTiming = var1.getFloat();
      this.setUnlimitedCarry(var1.get() == 1);
      this.setBuildCheat(var1.get() == 1);
      this.setHealthCheat(var1.get() == 1);
      this.setMechanicsCheat(var1.get() == 1);
      if (var2 >= 176) {
         this.setMovablesCheat(var1.get() == 1);
         this.setFarmingCheat(var1.get() == 1);
         this.setTimedActionInstantCheat(var1.get() == 1);
         this.setUnlimitedEndurance(var1.get() == 1);
      }

      if (var2 >= 161) {
         this.setSneaking(var1.get() == 1);
         this.setDeathDragDown(var1.get() == 1);
      }
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      if (this.descriptor == nullptr) {
         var1.put((byte)0);
      } else {
         var1.put((byte)1);
         this.descriptor.save(var1);
      }

      this.getVisual().save(var1);
    std::vector var3 = this.inventory.save(var1, this);
      this.savedInventoryItems.clear();

      for (int var4 = 0; var4 < var3.size(); var4++) {
         this.savedInventoryItems.push_back((InventoryItem)var3.get(var4));
      }

      var1.put((byte)(this.Asleep ? 1 : 0));
      var1.putFloat(this.ForceWakeUpTime);
      if (!this.isZombie()) {
         this.stats.save(var1);
         this.BodyDamage.save(var1);
         this.xp.save(var1);
         if (this.leftHandItem != nullptr) {
            var1.putInt(this.inventory.getItems().indexOf(this.leftHandItem));
         } else {
            var1.putInt(-1);
         }

         if (this.rightHandItem != nullptr) {
            var1.putInt(this.inventory.getItems().indexOf(this.rightHandItem));
         } else {
            var1.putInt(-1);
         }
      }

      var1.put((byte)(this.OnFire ? 1 : 0));
      var1.putFloat(this.DepressEffect);
      var1.putFloat(this.DepressFirstTakeTime);
      var1.putFloat(this.BetaEffect);
      var1.putFloat(this.BetaDelta);
      var1.putFloat(this.PainEffect);
      var1.putFloat(this.PainDelta);
      var1.putFloat(this.SleepingTabletEffect);
      var1.putFloat(this.SleepingTabletDelta);
      var1.putInt(this.ReadBooks.size());

      for (int var6 = 0; var6 < this.ReadBooks.size(); var6++) {
    ReadBook var5 = this.ReadBooks.get(var6);
         GameWindow.WriteString(var1, var5.fullType);
         var1.putInt(var5.alreadyReadPages);
      }

      var1.putFloat(this.reduceInfectionPower);
      var1.putInt(this.knownRecipes.size());

      for (int var7 = 0; var7 < this.knownRecipes.size(); var7++) {
    std::string var8 = this.knownRecipes.get(var7);
         GameWindow.WriteString(var1, var8);
      }

      var1.putInt(this.lastHourSleeped);
      var1.putFloat(this.timeSinceLastSmoke);
      var1.putFloat(this.beardGrowTiming);
      var1.putFloat(this.hairGrowTiming);
      var1.put((byte)(this.isUnlimitedCarry() ? 1 : 0));
      var1.put((byte)(this.isBuildCheat() ? 1 : 0));
      var1.put((byte)(this.isHealthCheat() ? 1 : 0));
      var1.put((byte)(this.isMechanicsCheat() ? 1 : 0));
      var1.put((byte)(this.isMovablesCheat() ? 1 : 0));
      var1.put((byte)(this.isFarmingCheat() ? 1 : 0));
      var1.put((byte)(this.isTimedActionInstantCheat() ? 1 : 0));
      var1.put((byte)(this.isUnlimitedEndurance() ? 1 : 0));
      var1.put((byte)(this.isSneaking() ? 1 : 0));
      var1.put((byte)(this.isDeathDragDown() ? 1 : 0));
   }

    ChatElement getChatElement() {
      return this.chatElement;
   }

    void StartAction(BaseAction var1) {
      this.CharacterActions.clear();
      this.CharacterActions.push(var1);
      if (var1.valid()) {
         var1.waitToStart();
      }
   }

    void QueueAction(BaseAction var1) {
   }

    void StopAllActionQueue() {
      if (!this.CharacterActions.empty()) {
    BaseAction var1 = this.CharacterActions.get(0);
         if (var1.bStarted) {
            var1.stop();
         }

         this.CharacterActions.clear();
         if (this == IsoPlayer.players[0] || this == IsoPlayer.players[1] || this == IsoPlayer.players[2] || this == IsoPlayer.players[3]) {
            UIManager.getProgressBar(((IsoPlayer)this).getPlayerNum()).setValue(0.0F);
         }
      }
   }

    void StopAllActionQueueRunning() {
      if (!this.CharacterActions.empty()) {
    BaseAction var1 = this.CharacterActions.get(0);
         if (var1.StopOnRun) {
            if (var1.bStarted) {
               var1.stop();
            }

            this.CharacterActions.clear();
            if (this == IsoPlayer.players[0] || this == IsoPlayer.players[1] || this == IsoPlayer.players[2] || this == IsoPlayer.players[3]) {
               UIManager.getProgressBar(((IsoPlayer)this).getPlayerNum()).setValue(0.0F);
            }
         }
      }
   }

    void StopAllActionQueueAiming() {
      if (this.CharacterActions.size() != 0) {
    BaseAction var1 = this.CharacterActions.get(0);
         if (var1.StopOnAim) {
            if (var1.bStarted) {
               var1.stop();
            }

            this.CharacterActions.clear();
            if (this == IsoPlayer.players[0] || this == IsoPlayer.players[1] || this == IsoPlayer.players[2] || this == IsoPlayer.players[3]) {
               UIManager.getProgressBar(((IsoPlayer)this).getPlayerNum()).setValue(0.0F);
            }
         }
      }
   }

    void StopAllActionQueueWalking() {
      if (this.CharacterActions.size() != 0) {
    BaseAction var1 = this.CharacterActions.get(0);
         if (var1.StopOnWalk) {
            if (var1.bStarted) {
               var1.stop();
            }

            this.CharacterActions.clear();
            if (this == IsoPlayer.players[0] || this == IsoPlayer.players[1] || this == IsoPlayer.players[2] || this == IsoPlayer.players[3]) {
               UIManager.getProgressBar(((IsoPlayer)this).getPlayerNum()).setValue(0.0F);
            }
         }
      }
   }

    std::string GetAnimSetName() {
      return "Base";
   }

    void SleepingTablet(float var1) {
      this.SleepingTabletEffect = 6600.0F;
      this.SleepingTabletDelta += var1;
   }

    void BetaBlockers(float var1) {
      this.BetaEffect = 6600.0F;
      this.BetaDelta += var1;
   }

    void BetaAntiDepress(float var1) {
      if (this.DepressEffect == 0.0F) {
         this.DepressFirstTakeTime = 10000.0F;
      }

      this.DepressEffect = 6600.0F;
      this.DepressDelta += var1;
   }

    void PainMeds(float var1) {
      this.PainEffect = 5400.0F;
      this.PainDelta += var1;
   }

    void initSpritePartsEmpty() {
      this.InitSpriteParts(this.descriptor);
   }

    void InitSpriteParts(SurvivorDesc var1) {
      this.sprite.AnimMap.clear();
      this.sprite.AnimStack.clear();
      this.sprite.CurrentAnim = nullptr;
      this.legsSprite = this.sprite;
      this.legsSprite.name = var1.torso;
      this.bUseParts = true;
   }

    bool HasTrait(const std::string& var1) {
      return this.Traits.contains(var1);
   }

    void ApplyInBedOffset(bool var1) {
      if (var1) {
         if (!this.bOnBed) {
            this.offsetX -= 20.0F;
            this.offsetY += 21.0F;
            this.bOnBed = true;
         }
      } else if (this.bOnBed) {
         this.offsetX += 20.0F;
         this.offsetY -= 21.0F;
         this.bOnBed = false;
      }
   }

    void Dressup(SurvivorDesc var1) {
      if (!this.isZombie()) {
         if (this.wornItems != nullptr) {
    ItemVisuals var2 = std::make_shared<ItemVisuals>();
            var1.getItemVisuals(var2);
            this.wornItems.setFromItemVisuals(var2);
            this.wornItems.addItemsToItemContainer(this.inventory);
            var1.wornItems.clear();
            this.onWornItemsChanged();
         }
      }
   }

    void PlayAnim(const std::string& var1) {
   }

    void PlayAnimWithSpeed(const std::string& var1, float var2) {
   }

    void PlayAnimUnlooped(const std::string& var1) {
   }

    void DirectionFromVector(Vector2 var1) {
      this.dir = IsoDirections.fromAngle(var1);
   }

    void DoFootstepSound(const std::string& var1) {
    float var2 = 1.0F;
      switch (var1) {
         case "sneak_walk":
            var2 = 0.2F;
            break;
         case "sneak_run":
            var2 = 0.5F;
            break;
         case "strafe":
            var2 = this.bSneaking ? 0.2F : 0.3F;
            break;
         case "walk":
            var2 = 0.5F;
            break;
         case "run":
            var2 = 1.3F;
            break;
         case "sprint":
            var2 = 1.8F;
      }

      this.DoFootstepSound(var2);
   }

    void DoFootstepSound(float var1) {
    IsoPlayer var2 = (IsoPlayer)Type.tryCastTo(this, IsoPlayer.class);
      if (GameClient.bClient && var2 != nullptr && var2.networkAI != nullptr) {
         var2.networkAI.footstepSoundRadius = 0;
      }

      if (var2 == nullptr || !var2.isGhostMode() || DebugOptions.instance.char.Debug.PlaySoundWhenInvisible.getValue()) {
         if (this.getCurrentSquare() != nullptr) {
            if (!(var1 <= 0.0F)) {
               var1 *= 1.4F;
               if (this.Traits.Graceful.isSet()) {
                  var1 *= 0.6F;
               }

               if (this.Traits.Clumsy.isSet()) {
                  var1 *= 1.2F;
               }

               if (this.getWornItem("Shoes") == nullptr) {
                  var1 *= 0.5F;
               }

               var1 *= this.getLightfootMod();
               var1 *= 2.0F - this.getNimbleMod();
               if (this.bSneaking) {
                  var1 *= this.getSneakSpotMod();
               }

               if (var1 > 0.0F) {
                  this.emitter.playFootsteps("HumanFootstepsCombined", var1);
                  if (var2 != nullptr && var2.isGhostMode()) {
                     return;
                  }

    int var4 = (int)Math.ceil(var1 * 10.0F);
                  if (this.bSneaking) {
                     var4 = Math.max(1, var4);
                  }

                  if (this.getCurrentSquare().getRoom() != nullptr) {
                     var4 = (int)(var4 * 0.5F);
                  }

    int var5 = 2;
                  if (this.bSneaking) {
                     var5 = Math.min(12, 4 + this.getPerkLevel(Perks.Lightfoot));
                  }

                  if (GameClient.bClient && var2 != nullptr && var2.networkAI != nullptr) {
                     var2.networkAI.footstepSoundRadius = (byte)var4;
                  }

                  if (Rand.Next(var5) == 0) {
                     WorldSoundManager.instance
                        .addSound(this, (int)this.getX(), (int)this.getY(), (int)this.getZ(), var4, var4, false, 0.0F, 1.0F, false, false, false);
                  }
               }
            }
         }
      }
   }

    bool Eat(InventoryItem var1, float var2) {
    Food var3 = (Food)Type.tryCastTo(var1, Food.class);
      if (var3 == nullptr) {
    return false;
      } else {
         var2 = PZMath.clamp(var2, 0.0F, 1.0F);
         if (var3.getRequireInHandOrInventory() != nullptr) {
    InventoryItem var4 = nullptr;

            for (int var5 = 0; var5 < var3.getRequireInHandOrInventory().size(); var5++) {
    std::string var6 = (std::string)var3.getRequireInHandOrInventory().get(var5);
               var4 = this.getInventory().FindAndReturn(var6);
               if (var4 != nullptr) {
                  var4.Use();
                  break;
               }
            }
         }

    float var13 = var2;
         if (var3.getBaseHunger() != 0.0F && var3.getHungChange() != 0.0F) {
    float var14 = var3.getBaseHunger() * var2;
    float var16 = var14 / var3.getHungChange();
            var16 = PZMath.clamp(var16, 0.0F, 1.0F);
            var2 = var16;
         }

         if (var3.getHungChange() < 0.0F && var3.getHungChange() * (1.0F - var2) > -0.01F) {
            var2 = 1.0F;
         }

         if (var3.getHungChange() == 0.0F && var3.getThirstChange() < 0.0F && var3.getThirstChange() * (1.0F - var2) > -0.01F) {
            var2 = 1.0F;
         }

         this.stats.thirst = this.stats.thirst + var3.getThirstChange() * var2;
         if (this.stats.thirst < 0.0F) {
            this.stats.thirst = 0.0F;
         }

         this.stats.hunger = this.stats.hunger + var3.getHungerChange() * var2;
         this.stats.endurance = this.stats.endurance + var3.getEnduranceChange() * var2;
         this.stats.stress = this.stats.stress + var3.getStressChange() * var2;
         this.stats.fatigue = this.stats.fatigue + var3.getFatigueChange() * var2;
    IsoPlayer var15 = (IsoPlayer)Type.tryCastTo(this, IsoPlayer.class);
         if (var15 != nullptr) {
    Nutrition var18 = var15.getNutrition();
            var18.setCalories(var18.getCalories() + var3.getCalories() * var2);
            var18.setCarbohydrates(var18.getCarbohydrates() + var3.getCarbohydrates() * var2);
            var18.setProteins(var18.getProteins() + var3.getProteins() * var2);
            var18.setLipids(var18.getLipids() + var3.getLipids() * var2);
         }

         this.BodyDamage.setPainReduction(this.BodyDamage.getPainReduction() + var3.getPainReduction() * var2);
         this.BodyDamage.setColdReduction(this.BodyDamage.getColdReduction() + var3.getFluReduction() * var2);
         if (this.BodyDamage.getFoodSicknessLevel() > 0.0F && var3.getReduceFoodSickness() > 0.0F && this.effectiveEdibleBuffTimer <= 0.0F) {
    float var19 = this.BodyDamage.getFoodSicknessLevel();
            this.BodyDamage.setFoodSicknessLevel(this.BodyDamage.getFoodSicknessLevel() - var3.getReduceFoodSickness() * var2);
            if (this.BodyDamage.getFoodSicknessLevel() < 0.0F) {
               this.BodyDamage.setFoodSicknessLevel(0.0F);
            }

    float var7 = this.BodyDamage.getPoisonLevel();
            this.BodyDamage.setPoisonLevel(this.BodyDamage.getPoisonLevel() - var3.getReduceFoodSickness() * var2);
            if (this.BodyDamage.getPoisonLevel() < 0.0F) {
               this.BodyDamage.setPoisonLevel(0.0F);
            }

            if (this.Traits.IronGut.isSet()) {
               this.effectiveEdibleBuffTimer = Rand.Next(80.0F, 150.0F);
            } else if (this.Traits.WeakStomach.isSet()) {
               this.effectiveEdibleBuffTimer = Rand.Next(120.0F, 230.0F);
            } else {
               this.effectiveEdibleBuffTimer = Rand.Next(200.0F, 280.0F);
            }
         }

         this.BodyDamage.JustAteFood(var3, var2);
         if (GameClient.bClient && dynamic_cast<IsoPlayer*>(this) != nullptr && ((IsoPlayer)this).isLocalPlayer()) {
            GameClient.instance.eatFood((IsoPlayer)this, var3, var2);
         }

         if (var3.getOnEat() != nullptr) {
    void* var20 = LuaManager.getFunctionObject(var3.getOnEat());
            if (var20 != nullptr) {
               LuaManager.caller.pcallvoid(LuaManager.thread, var20, var1, this, BoxedStaticValues.toDouble(var2));
            }
         }

         if (var2 == 1.0F) {
            var3.setHungChange(0.0F);
            var3.UseItem();
         } else {
    float var21 = var3.getHungChange();
    float var22 = var3.getThirstChange();
            var3.multiplyFoodValues(1.0F - var2);
            if (var21 < 0.0F && var3.getHungerChange() > -0.00999) {
            }

            if (var21 == 0.0F && var22 < 0.0F && var3.getThirstChange() > -0.01F) {
               var3.setHungChange(0.0F);
               var3.UseItem();
    return true;
            }

    float var8 = 0.0F;
            if (var3.isCustomWeight()) {
    std::string var9 = var3.getReplaceOnUseFullType();
    Item var10 = var9 == nullptr ? nullptr : ScriptManager.instance.getItem(var9);
               if (var10 != nullptr) {
                  var8 = var10.getActualWeight();
               }

               var3.setWeight(var3.getWeight() - var8 - var13 * (var3.getWeight() - var8) + var8);
            }
         }

    return true;
      }
   }

    bool Eat(InventoryItem var1) {
      return this.Eat(var1, 1.0F);
   }

    void FireCheck() {
      if (!this.OnFire) {
         if (!GameServer.bServer || !(dynamic_cast<IsoPlayer*>(this) != nullptr)) {
            if (!GameClient.bClient || !this.isZombie() || !(dynamic_cast<IsoZombie*>(this) != nullptr) || !((IsoZombie)this).isRemoteZombie()) {
               if (this.isZombie() && VirtualZombieManager.instance.isReused((IsoZombie)this)) {
                  DebugLog.log(DebugType.Zombie, "FireCheck running on REUSABLE ZOMBIE - IGNORED " + this);
               } else if (this.getVehicle() == nullptr) {
                  if (this.square != nullptr
                     && !GameServer.bServer
                     && (
                        !GameClient.bClient
                           || dynamic_cast<IsoPlayer*>(this) != nullptr && ((IsoPlayer)this).isLocalPlayer()
                           || dynamic_cast<IsoZombie*>(this) != nullptr && !((IsoZombie)this).isRemoteZombie()
                     )
                     && this.square.getProperties().Is(IsoFlagType.burning)) {
                     if ((!(dynamic_cast<IsoPlayer*>(this) != nullptr) || Rand.Next(Rand.AdjustForFramerate(70)) != 0) && !this.isZombie()) {
                        if (!(dynamic_cast<IsoPlayer*>(this) != nullptr)) {
                           this.Health = this.Health - this.FireKillRate * GameTime.instance.getMultiplier() / 2.0F;
                           this.setAttackedBy(nullptr);
                        } else {
    float var1 = this.FireKillRate * GameTime.instance.getMultiplier() * GameTime.instance.getMinutesPerDay() / 1.6F / 2.0F;
                           this.BodyDamage.ReduceGeneralHealth(var1);
                           LuaEventManager.triggerEvent("OnPlayerGetDamage", this, "FIRE", var1);
                           this.BodyDamage.OnFire(true);
                           this.forceAwake();
                        }

                        if (this.isDead()) {
                           IsoFireManager.RemoveBurningCharacter(this);
                           if (this.isZombie()) {
                              LuaEventManager.triggerEvent("OnZombieDead", this);
                              if (GameClient.bClient) {
                                 this.setAttackedBy(IsoWorld.instance.CurrentCell.getFakeZombieForHit());
                              }
                           }
                        }
                     } else {
                        this.SetOnFire();
                     }
                  }
               }
            }
         }
      }
   }

    std::string getPrimaryHandType() {
      return this.leftHandItem == nullptr ? nullptr : this.leftHandItem.getType();
   }

    float getGlobalMovementMod(bool var1) {
      return this.getCurrentState() != ClimbOverFenceState.instance()
            && this.getCurrentState() != ClimbThroughWindowState.instance()
            && this.getCurrentState() != ClimbOverWallState.instance()
         ? super.getGlobalMovementMod(var1)
         : 1.0F;
   }

    float getMoveSpeed() {
      tempo2.x = this.getX() - this.getLx();
      tempo2.y = this.getY() - this.getLy();
      return tempo2.getLength();
   }

    std::string getSecondaryHandType() {
      return this.rightHandItem == nullptr ? nullptr : this.rightHandItem.getType();
   }

    bool HasItem(const std::string& var1) {
    return var1 = = nullptr ? true : var1 == this.getSecondaryHandType()) || var1 == this.getPrimaryHandType()) || this.inventory.contains(var1);
   }

    void changeState(State var1) {
      this.stateMachine.changeState(var1, nullptr);
   }

    State getCurrentState() {
      return this.stateMachine.getCurrent();
   }

    bool isCurrentState(State var1) {
      return this.stateMachine.isSubstate(var1) ? true : this.stateMachine.getCurrent() == var1;
   }

   public std::unordered_map<Object, Object> getStateMachineParams(State var1) {
      return this.StateMachineParams.computeIfAbsent(var1, var0 -> std::make_unique<std::unordered_map<>>());
   }

    void setStateMachineLocked(bool var1) {
      this.stateMachine.setLocked(var1);
   }

    float Hit(HandWeapon var1, IsoGameCharacter var2, float var3, bool var4, float var5) {
      return this.Hit(var1, var2, var3, var4, var5, false);
   }

    float Hit(HandWeapon var1, IsoGameCharacter var2, float var3, bool var4, float var5, bool var6) {
      if (var2 != nullptr && var1 != nullptr) {
         if (!var4 && this.isZombie()) {
    IsoZombie var7 = (IsoZombie)this;
            var7.setHitTime(var7.getHitTime() + 1);
            if (var7.getHitTime() >= 4 && !var6) {
               var3 = (float)(var3 * ((var7.getHitTime() - 2) * 1.5));
            }
         }

         if (dynamic_cast<IsoPlayer*>(var2) != nullptr && ((IsoPlayer)var2).bDoShove && !((IsoPlayer)var2).isAimAtFloor()) {
            var4 = true;
            var5 *= 1.5F;
         }

         LuaEventManager.triggerEvent("OnWeaponHitCharacter", var2, this, var1, var3);
         LuaEventManager.triggerEvent("OnPlayerGetDamage", this, "WEAPONHIT", var3);
         if (LuaHookManager.TriggerHook("WeaponHitCharacter", var2, this, var1, var3)) {
            return 0.0F;
         } else if (this.m_avoidDamage) {
            this.m_avoidDamage = false;
            return 0.0F;
         } else {
            if (this.noDamage) {
               var4 = true;
               this.noDamage = false;
            }

            if (dynamic_cast<IsoSurvivor*>(this) != nullptr && !this.EnemyList.contains(var2)) {
               this.EnemyList.push_back(var2);
            }

            this.staggerTimeMod = var1.getPushBackMod() * var1.getKnockbackMod(var2) * var2.getShovingMod();
            if (this.isZombie() && Rand.Next(3) == 0 && GameServer.bServer) {
            }

            var2.addWorldSoundUnlessInvisible(5, 1, false);
            this.hitDir.x = this.getX();
            this.hitDir.y = this.getY();
            this.hitDir.x = this.hitDir.x - var2.getX();
            this.hitDir.y = this.hitDir.y - var2.getY();
            this.getHitDir().normalize();
            this.hitDir.x = this.hitDir.x * var1.getPushBackMod();
            this.hitDir.y = this.hitDir.y * var1.getPushBackMod();
            this.hitDir.rotate(var1.HitAngleMod);
            this.setAttackedBy(var2);
    float var12 = var3;
            if (!var6) {
               var12 = this.processHitDamage(var1, var2, var3, var4, var5);
            }

    float var8 = 0.0F;
            if (var1.isTwoHandWeapon() && (var2.getPrimaryHandItem() != var1 || var2.getSecondaryHandItem() != var1)) {
               var8 = var1.getWeight() / 1.5F / 10.0F;
            }

    float var9 = (var1.getWeight() * 0.28F * var1.getFatigueMod(var2) * this.getFatigueMod() * var1.getEnduranceMod() * 0.3F + var8) * 0.04F;
            if (dynamic_cast<IsoPlayer*>(var2) != nullptr && var2.isAimAtFloor() && ((IsoPlayer)var2).bDoShove) {
               var9 *= 2.0F;
            }

    float var10;
            if (var1.isAimedFirearm()) {
               var10 = var12 * 0.7F;
            } else {
               var10 = var12 * 0.15F;
            }

            if (this.getHealth() < var12) {
               var10 = this.getHealth();
            }

    float var11 = var10 / var1.getMaxDamage();
            if (var11 > 1.0F) {
               var11 = 1.0F;
            }

            if (this.isCloseKilled()) {
               var11 = 0.2F;
            }

            if (var1.isUseEndurance()) {
               if (var12 <= 0.0F) {
                  var11 = 1.0F;
               }

               var2.getStats().endurance -= var9 * var11;
            }

            this.hitConsequences(var1, var2, var4, var12, var6);
    return var12;
         }
      } else {
         return 0.0F;
      }
   }

    float processHitDamage(HandWeapon var1, IsoGameCharacter var2, float var3, bool var4, float var5) {
    float var6 = var3 * var5;
    float var7 = var6;
      if (var4) {
         var7 = var6 / 2.7F;
      }

    float var8 = var7 * var2.getShovingMod();
      if (var8 > 1.0F) {
         var8 = 1.0F;
      }

      this.setHitForce(var8);
      if (var2.Traits.Strong.isSet() && !var1.isRanged()) {
         this.setHitForce(this.getHitForce() * 1.4F);
      }

      if (var2.Traits.Weak.isSet() && !var1.isRanged()) {
         this.setHitForce(this.getHitForce() * 0.6F);
      }

    float var9 = IsoUtils.DistanceTo(var2.getX(), var2.getY(), this.getX(), this.getY());
      var9 -= var1.getMinRange();
      var9 /= var1.getMaxRange(var2);
      var9 = 1.0F - var9;
      if (var9 > 1.0F) {
         var9 = 1.0F;
      }

    float var10 = var2.stats.endurance;
      var10 *= var2.knockbackAttackMod;
      if (var10 < 0.5F) {
         var10 *= 1.3F;
         if (var10 < 0.4F) {
            var10 = 0.4F;
         }

         this.setHitForce(this.getHitForce() * var10);
      }

      if (!var1.isRangeFalloff()) {
         var9 = 1.0F;
      }

      if (!var1.isShareDamage()) {
         var3 = 1.0F;
      }

      if (dynamic_cast<IsoPlayer*>(var2) != nullptr && !var4) {
         this.setHitForce(this.getHitForce() * 2.0F);
      }

      if (dynamic_cast<IsoPlayer*>(var2) != nullptr && !((IsoPlayer)var2).bDoShove) {
    Vector2 var11 = tempVector2_1.set(this.getX(), this.getY());
    Vector2 var12 = tempVector2_2.set(var2.getX(), var2.getY());
         var11.x = var11.x - var12.x;
         var11.y = var11.y - var12.y;
    Vector2 var13 = this.getVectorFromDirection(tempVector2_2);
         var11.normalize();
    float var14 = var11.dot(var13);
         if (var14 > -0.3F) {
            var6 *= 1.5F;
         }
      }

      if (dynamic_cast<IsoPlayer*>(this) != nullptr) {
         var6 *= 0.4F;
      } else {
         var6 *= 1.5F;
      }

    int var24 = var2.getWeaponLevel();
      switch (var24) {
         case -1:
            var6 *= 0.3F;
            break;
         case 0:
            var6 *= 0.3F;
            break;
         case 1:
            var6 *= 0.4F;
            break;
         case 2:
            var6 *= 0.5F;
            break;
         case 3:
            var6 *= 0.6F;
            break;
         case 4:
            var6 *= 0.7F;
            break;
         case 5:
            var6 *= 0.8F;
            break;
         case 6:
            var6 *= 0.9F;
            break;
         case 7:
            var6 *= 1.0F;
            break;
         case 8:
            var6 *= 1.1F;
            break;
         case 9:
            var6 *= 1.2F;
            break;
         case 10:
            var6 *= 1.3F;
      }

      if (dynamic_cast<IsoPlayer*>(var2) != nullptr && var2.isAimAtFloor() && !var4 && !((IsoPlayer)var2).bDoShove) {
         var6 *= Math.max(5.0F, var1.getCritDmgMultiplier());
      }

      if (var2.isCriticalHit() && !var4) {
         var6 *= Math.max(2.0F, var1.getCritDmgMultiplier());
      }

      if (var1.isTwoHandWeapon() && !var2.isItemInBothHands(var1)) {
         var6 *= 0.5F;
      }

    return var6;
   }

    void hitConsequences(HandWeapon var1, IsoGameCharacter var2, bool var3, float var4, bool var5) {
      if (!var3) {
         if (var1.isAimedFirearm()) {
            this.Health -= var4 * 0.7F;
         } else {
            this.Health -= var4 * 0.15F;
         }
      }

      if (this.isDead()) {
         if (!this.isOnKillDone() && this.shouldDoInventory()) {
            this.Kill(var2);
         }

         if (dynamic_cast<IsoZombie*>(this) != nullptr && ((IsoZombie)this).upKillCount) {
            var2.setZombieKills(var2.getZombieKills() + 1);
         }
      } else {
         if (var1.isSplatBloodOnNoDeath()) {
            this.splatBlood(2, 0.2F);
         }

         if (var1.isKnockBackOnNoDeath() && var2.xp != nullptr) {
            var2.xp.AddXP(Perks.Strength, 2.0F);
         }
      }
   }

    bool IsAttackRange(float var1, float var2, float var3) {
    float var4 = 1.0F;
    float var5 = 0.0F;
      if (this.leftHandItem != nullptr) {
    InventoryItem var6 = this.leftHandItem;
         if (dynamic_cast<HandWeapon*>(var6) != nullptr) {
            var4 = ((HandWeapon)var6).getMaxRange(this);
            var5 = ((HandWeapon)var6).getMinRange();
            var4 *= ((HandWeapon)this.leftHandItem).getRangeMod(this);
         }
      }

      if (Math.abs(var3 - this.getZ()) > 0.3F) {
    return false;
      } else {
    float var8 = IsoUtils.DistanceTo(var1, var2, this.getX(), this.getY());
         return var8 < var4 && var8 > var5;
      }
   }

    bool IsAttackRange(HandWeapon var1, IsoMovingObject var2, Vector3 var3, bool var4) {
      if (var1 == nullptr) {
    return false;
      } else {
    float var5 = Math.abs(var2.getZ() - this.getZ());
         if (!var1.isRanged() && var5 >= 0.5F) {
    return false;
         } else if (var5 > 3.3F) {
    return false;
         } else {
    float var6 = var1.getMaxRange(this);
            var6 *= var1.getRangeMod(this);
    float var7 = IsoUtils.DistanceToSquared(this.x, this.y, var3.x, var3.y);
            if (var4) {
    IsoZombie var8 = (IsoZombie)Type.tryCastTo(var2, IsoZombie.class);
               if (var8 != nullptr
                  && var7 < 4.0F
                  && var8.target == this
                  && (var8.isCurrentState(LungeState.instance()) || var8.isCurrentState(LungeNetworkState.instance()))) {
                  var6++;
               }
            }

            return var7 < var6 * var6;
         }
      }
   }

    bool IsSpeaking() {
      return this.chatElement.IsSpeaking();
   }

    void MoveForward(float var1, float var2, float var3, float var4) {
      if (!this.isCurrentState(SwipeStatePlayer.instance())) {
    float var5 = GameTime.instance.getMultiplier();
         this.setNx(this.getNx() + var2 * var1 * var5);
         this.setNy(this.getNy() + var3 * var1 * var5);
         this.DoFootstepSound(var1);
         if (!this.isZombie()) {
         }
      }
   }

    void pathToAux(float var1, float var2, float var3) {
    bool var4 = true;
      if ((int)var3 == (int)this.getZ() && IsoUtils.DistanceManhatten(var1, var2, this.x, this.y) <= 30.0F) {
    int var5 = (int)var1 / 10;
    int var6 = (int)var2 / 10;
         IsoChunk var7 = GameServer.bServer
            ? ServerMap.instance.getChunk(var5, var6)
            : IsoWorld.instance.CurrentCell.getChunkForGridSquare((int)var1, (int)var2, (int)var3);
         if (var7 != nullptr) {
    int var8 = 1;
            var8 |= 2;
            if (!this.isZombie()) {
               var8 |= 4;
            }

            var4 = !PolygonalMap2.instance.lineClearCollide(this.getX(), this.getY(), var1, var2, (int)var3, this.getPathFindBehavior2().getTargetChar(), var8);
         }
      }

      if (var4 && this.current != nullptr && this.current.HasStairs() && !this.current.isSameStaircase((int)var1, (int)var2, (int)var3)) {
         var4 = false;
      }

      if (var4) {
         this.setVariable("bPathfind", false);
         this.setMoving(true);
      } else {
         this.setVariable("bPathfind", true);
         this.setMoving(false);
      }
   }

    void pathToCharacter(IsoGameCharacter var1) {
      this.getPathFindBehavior2().pathToCharacter(var1);
      this.pathToAux(var1.getX(), var1.getY(), var1.getZ());
   }

    void pathToLocation(int var1, int var2, int var3) {
      this.getPathFindBehavior2().pathToLocation(var1, var2, var3);
      this.pathToAux(var1 + 0.5F, var2 + 0.5F, var3);
   }

    void pathToLocationF(float var1, float var2, float var3) {
      this.getPathFindBehavior2().pathToLocationF(var1, var2, var3);
      this.pathToAux(var1, var2, var3);
   }

    void pathToSound(int var1, int var2, int var3) {
      this.getPathFindBehavior2().pathToSound(var1, var2, var3);
      this.pathToAux(var1 + 0.5F, var2 + 0.5F, var3);
   }

    bool CanAttack() {
      if (!this.isAttackAnim()
         && !this.getVariableBoolean("IsRacking")
         && !this.getVariableBoolean("IsUnloading")
         && StringUtils.isNullOrEmpty(this.getVariableString("RackWeapon"))) {
         if (!GameClient.bClient
            || !(dynamic_cast<IsoPlayer*>(this) != nullptr)
            || !((IsoPlayer)this).isLocalPlayer()
            || !this.isCurrentState(PlayerHitReactionState.instance()) && !this.isCurrentState(PlayerHitReactionPVPState.instance())) {
            if (this.isSitOnGround()) {
    return false;
            } else {
    InventoryItem var1 = this.leftHandItem;
               if (dynamic_cast<HandWeapon*>(var1) != nullptr && var1.getSwingAnim() != nullptr) {
                  this.useHandWeapon = (HandWeapon)var1;
               }

               if (this.useHandWeapon == nullptr) {
    return true;
               } else if (this.useHandWeapon.getCondition() <= 0) {
                  this.useHandWeapon = nullptr;
                  if (this.rightHandItem == this.leftHandItem) {
                     this.setSecondaryHandItem(nullptr);
                  }

                  this.setPrimaryHandItem(nullptr);
                  if (this.getInventory() != nullptr) {
                     this.getInventory().setDrawDirty(true);
                  }

    return false;
               } else {
    float var2 = 12.0F;
    int var3 = this.Moodles.getMoodleLevel(MoodleType.Endurance);
                  return !this.useHandWeapon.isCantAttackWithLowestEndurance() || var3 != 4;
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
      if (this.OnFire) {
         if (this.isGodMod()) {
            this.StopBurning();
         } else if (!GameClient.bClient || !this.isZombie() || !(dynamic_cast<IsoZombie*>(this) != nullptr) || !((IsoZombie)this).isRemoteZombie()) {
            if (!GameClient.bClient || !(dynamic_cast<IsoPlayer*>(this) != nullptr) || !((IsoPlayer)this).bRemote) {
               if (this.isAlive()) {
                  if (!(dynamic_cast<IsoPlayer*>(this) != nullptr)) {
                     if (this.isZombie()) {
                        this.Health = this.Health - this.FireKillRate / 20.0F * GameTime.instance.getMultiplier();
                        this.setAttackedBy(nullptr);
                     } else {
                        this.Health = this.Health - this.FireKillRate * GameTime.instance.getMultiplier();
                     }
                  } else {
    float var1 = this.FireKillRate * GameTime.instance.getMultiplier() * GameTime.instance.getMinutesPerDay() / 1.6F;
                     this.BodyDamage.ReduceGeneralHealth(var1);
                     LuaEventManager.triggerEvent("OnPlayerGetDamage", this, "FIRE", var1);
                     this.BodyDamage.OnFire(true);
                  }

                  if (this.isDead()) {
                     IsoFireManager.RemoveBurningCharacter(this);
                     if (this.isZombie()) {
                        LuaEventManager.triggerEvent("OnZombieDead", this);
                        if (GameClient.bClient) {
                           this.setAttackedBy(IsoWorld.instance.CurrentCell.getFakeZombieForHit());
                        }
                     }
                  }
               }

               if (dynamic_cast<IsoPlayer*>(this) != nullptr && Rand.Next(Rand.AdjustForFramerate(((IsoPlayer)this).IsRunning() ? 150 : 400)) == 0) {
                  this.StopBurning();
               }
            }
         }
      }
   }

    void DrawSneezeText() {
      if (this.BodyDamage.IsSneezingCoughing() > 0) {
    std::string var1 = nullptr;
         if (this.BodyDamage.IsSneezingCoughing() == 1) {
            var1 = Translator.getText("IGUI_PlayerText_Sneeze");
         }

         if (this.BodyDamage.IsSneezingCoughing() == 2) {
            var1 = Translator.getText("IGUI_PlayerText_Cough");
         }

         if (this.BodyDamage.IsSneezingCoughing() == 3) {
            var1 = Translator.getText("IGUI_PlayerText_SneezeMuffled");
         }

         if (this.BodyDamage.IsSneezingCoughing() == 4) {
            var1 = Translator.getText("IGUI_PlayerText_CoughMuffled");
         }

    float var2 = this.sx;
    float var3 = this.sy;
         var2 = (int)var2;
         var3 = (int)var3;
         var2 -= (int)IsoCamera.getOffX();
         var3 -= (int)IsoCamera.getOffY();
         var3 -= 48.0F;
         if (var1 != nullptr) {
            TextManager.instance
               .DrawStringCentre(UIFont.Dialogue, (int)var2, (int)var3, var1, this.SpeakColour.r, this.SpeakColour.g, this.SpeakColour.b, this.SpeakColour.a);
         }
      }
   }

    IsoSpriteInstance getSpriteDef() {
      if (this.def == nullptr) {
         this.def = std::make_unique<IsoSpriteInstance>();
      }

      return this.def;
   }

    void render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      if (!this.isAlphaAndTargetZero()) {
         if (!this.isSeatedInVehicle() || this.getVehicle().showPassenger(this)) {
            if (!this.isSpriteInvisible()) {
               if (!this.isAlphaZero()) {
                  if (!this.bUseParts && this.def == nullptr) {
                     this.def = std::make_shared<IsoSpriteInstance>(this.sprite);
                  }

                  SpriteRenderer.instance.glDepthMask(true);
                  if (this.bDoDefer && var3 - (int)var3 > 0.2F) {
    IsoGridSquare var8 = this.getCell().getGridSquare((int)var1, (int)var2, (int)var3 + 1);
                     if (var8 != nullptr) {
                        var8.addDeferredCharacter(this);
                     }
                  }

    IsoGridSquare var15 = this.getCurrentSquare();
                  if (PerformanceSettings.LightingFrameSkip < 3 && var15 != nullptr) {
                     var15.interpolateLight(inf, var1 - var15.getX(), var2 - var15.getY());
                  } else {
                     inf.r = var4.r;
                     inf.g = var4.g;
                     inf.b = var4.b;
                     inf.a = var4.a;
                  }

                  if (Core.bDebug && DebugOptions.instance.PathfindRenderWaiting.getValue() && this.hasActiveModel()) {
                     if (this.getCurrentState() == PathFindState.instance() && this.finder.progress == PathFindProgress.notyetfound) {
                        this.legsSprite.modelSlot.model.tintR = 1.0F;
                        this.legsSprite.modelSlot.model.tintG = 0.0F;
                        this.legsSprite.modelSlot.model.tintB = 0.0F;
                     } else {
                        this.legsSprite.modelSlot.model.tintR = 1.0F;
                        this.legsSprite.modelSlot.model.tintG = 1.0F;
                        this.legsSprite.modelSlot.model.tintB = 1.0F;
                     }
                  }

                  if (this.dir == IsoDirections.Max) {
                     this.dir = IsoDirections.N;
                  }

                  if (this.sprite != nullptr && !this.legsSprite.hasActiveModel()) {
                     this.checkDrawWeaponPre(var1, var2, var3, var4);
                  }

                  lastRenderedRendered = lastRendered;
                  lastRendered = this;
                  this.checkUpdateModelTextures();
    float var9 = Core.TileScale;
    float var10 = this.offsetX + 1.0F * var9;
    float var11 = this.offsetY + -89.0F * var9;
                  if (this.sprite != nullptr) {
                     this.def.setScale(var9, var9);
                     if (!this.bUseParts) {
                        this.sprite.render(this.def, this, var1, var2, var3, this.dir, var10, var11, inf, true);
                     } else if (this.legsSprite.hasActiveModel()) {
                        this.legsSprite.renderActiveModel();
                     } else if (!this.renderTextureInsteadOfModel(var1, var2)) {
                        this.def.Flip = false;
                        inf.r = 1.0F;
                        inf.g = 1.0F;
                        inf.b = 1.0F;
                        inf.a = this.def.alpha * 0.4F;
                        this.legsSprite.renderCurrentAnim(this.def, this, var1, var2, var3, this.dir, var10, var11, inf, false, nullptr);
                     }
                  }

                  if (this.AttachedAnimSprite != nullptr) {
                     for (int var12 = 0; var12 < this.AttachedAnimSprite.size(); var12++) {
    IsoSpriteInstance var13 = (IsoSpriteInstance)this.AttachedAnimSprite.get(var12);
                        var13.update();
    float var14 = inf.a;
                        inf.a = var13.alpha;
                        var13.SetTargetAlpha(this.getTargetAlpha());
                        var13.render(this, var1, var2, var3, this.dir, var10, var11, inf);
                        inf.a = var14;
                     }
                  }

                  for (int var16 = 0; var16 < this.inventory.Items.size(); var16++) {
    InventoryItem var17 = (InventoryItem)this.inventory.Items.get(var16);
                     if (dynamic_cast<IUpdater*>(var17) != nullptr) {
                        ((IUpdater)var17).render();
                     }
                  }
               }
            }
         }
      }
   }

    void renderServerGUI() {
      if (dynamic_cast<IsoPlayer*>(this) != nullptr) {
         this.setSceneCulled(false);
      }

      if (this.bUpdateModelTextures && this.hasActiveModel()) {
         this.bUpdateModelTextures = false;
         this.textureCreator = ModelInstanceTextureCreator.alloc();
         this.textureCreator.init(this);
      }

    float var1 = Core.TileScale;
    float var2 = this.offsetX + 1.0F * var1;
    float var3 = this.offsetY + -89.0F * var1;
      if (this.sprite != nullptr) {
         this.def.setScale(var1, var1);
         inf.r = 1.0F;
         inf.g = 1.0F;
         inf.b = 1.0F;
         inf.a = this.def.alpha * 0.4F;
         if (!this.isbUseParts()) {
            this.sprite.render(this.def, this, this.x, this.y, this.z, this.dir, var2, var3, inf, true);
         } else {
            this.def.Flip = false;
            this.legsSprite.render(this.def, this, this.x, this.y, this.z, this.dir, var2, var3, inf, true);
         }
      }

      if (Core.bDebug && this.hasActiveModel()) {
         if (dynamic_cast<IsoZombie*>(this) != nullptr) {
    int var4 = (int)IsoUtils.XToScreenExact(this.x, this.y, this.z, 0);
    int var5 = (int)IsoUtils.YToScreenExact(this.x, this.y, this.z, 0);
            TextManager.instance.DrawString(var4, var5, "ID: " + this.getOnlineID());
            TextManager.instance.DrawString(var4, var5 + 10, "State: " + this.getCurrentStateName());
            TextManager.instance.DrawString(var4, var5 + 20, "Health: " + this.getHealth());
         }

    Vector2 var6 = tempo;
         this.getDeferredMovement(var6);
         this.drawDirectionLine(var6, 1000.0F * var6.getLength() / GameTime.instance.getMultiplier() * 2.0F, 1.0F, 0.5F, 0.5F);
      }
   }

    float getAlphaUpdateRateMul() {
    float var1 = super.getAlphaUpdateRateMul();
      if (IsoCamera.CamCharacter.Traits.ShortSighted.isSet()) {
         var1 /= 2.0F;
      }

      if (IsoCamera.CamCharacter.Traits.EagleEyed.isSet()) {
         var1 *= 1.5F;
      }

    return var1;
   }

    bool isUpdateAlphaEnabled() {
      return !this.isTeleporting();
   }

    bool isUpdateAlphaDuringRender() {
    return false;
   }

    bool isSeatedInVehicle() {
      return this.vehicle != nullptr && this.vehicle.getSeat(this) != -1;
   }

    void renderObjectPicker(float var1, float var2, float var3, ColorInfo var4) {
      if (!this.bUseParts) {
         this.sprite.renderObjectPicker(this.def, this, this.dir);
      } else {
         this.legsSprite.renderObjectPicker(this.def, this, this.dir);
      }
   }

    static Vector2 closestpointonline(double var0, double var2, double var4, double var6, double var8, double var10, Vector2 var12) {
    double var13 = var6 - var2;
    double var15 = var0 - var4;
    double var17 = (var6 - var2) * var0 + (var0 - var4) * var2;
    double var19 = -var15 * var8 + var13 * var10;
    double var21 = var13 * var13 - -var15 * var15;
    double var23;
    double var25;
      if (var21 != 0.0) {
         var23 = (var13 * var17 - var15 * var19) / var21;
         var25 = (var13 * var19 - -var15 * var17) / var21;
      } else {
         var23 = var8;
         var25 = var10;
      }

      return var12.set((float)var23, (float)var25);
   }

    void renderShadow(float var1, float var2, float var3) {
      if (this.doRenderShadow) {
         if (!this.isAlphaAndTargetZero()) {
            if (!this.isSeatedInVehicle()) {
    IsoGridSquare var4 = this.getCurrentSquare();
               if (var4 != nullptr) {
    int var5 = IsoCamera.frameState.playerIndex;
    Vector3f var6 = L_renderShadow.forward;
    Vector2 var7 = this.getAnimVector(tempo2);
                  var6.set(var7.x, var7.y, 0.0F);
    float var8 = 0.45F;
    float var9 = 1.4F;
    float var10 = 1.125F;
    float var11 = this.getAlpha(var5);
                  if (this.hasActiveModel() && this.hasAnimationPlayer() && this.getAnimationPlayer().isReady()) {
    AnimationPlayer var12 = this.getAnimationPlayer();
    Vector3 var13 = L_renderShadow.v1;
                     Model.BoneToWorldCoords(this, var12.getSkinningBoneIndex("Bip01_Head", -1), var13);
    float var14 = var13.x;
    float var15 = var13.y;
                     Model.BoneToWorldCoords(this, var12.getSkinningBoneIndex("Bip01_L_Foot", -1), var13);
    float var16 = var13.x;
    float var17 = var13.y;
                     Model.BoneToWorldCoords(this, var12.getSkinningBoneIndex("Bip01_R_Foot", -1), var13);
    float var18 = var13.x;
    float var19 = var13.y;
    Vector3f var20 = L_renderShadow.v3;
    float var21 = 0.0F;
    float var22 = 0.0F;
    Vector2 var23 = closestpointonline(var1, var2, var1 + var6.x, var2 + var6.y, var14, var15, tempo);
    float var24 = var23.x;
    float var25 = var23.y;
    float var26 = var23.set(var24 - var1, var25 - var2).getLength();
                     if (var26 > 0.001F) {
                        var20.set(var24 - var1, var25 - var2, 0.0F).normalize();
                        if (var6.dot(var20) > 0.0F) {
                           var21 = Math.max(var21, var26);
                        } else {
                           var22 = Math.max(var22, var26);
                        }
                     }

                     var23 = closestpointonline(var1, var2, var1 + var6.x, var2 + var6.y, var16, var17, tempo);
                     var24 = var23.x;
                     var25 = var23.y;
                     var26 = var23.set(var24 - var1, var25 - var2).getLength();
                     if (var26 > 0.001F) {
                        var20.set(var24 - var1, var25 - var2, 0.0F).normalize();
                        if (var6.dot(var20) > 0.0F) {
                           var21 = Math.max(var21, var26);
                        } else {
                           var22 = Math.max(var22, var26);
                        }
                     }

                     var23 = closestpointonline(var1, var2, var1 + var6.x, var2 + var6.y, var18, var19, tempo);
                     var24 = var23.x;
                     var25 = var23.y;
                     var26 = var23.set(var24 - var1, var25 - var2).getLength();
                     if (var26 > 0.001F) {
                        var20.set(var24 - var1, var25 - var2, 0.0F).normalize();
                        if (var6.dot(var20) > 0.0F) {
                           var21 = Math.max(var21, var26);
                        } else {
                           var22 = Math.max(var22, var26);
                        }
                     }

                     var9 = (var21 + 0.35F) * 1.35F;
                     var10 = (var22 + 0.35F) * 1.35F;
    float var27 = 0.1F * (GameTime.getInstance().getMultiplier() / 1.6F);
                     var27 = PZMath.clamp(var27, 0.0F, 1.0F);
                     if (this.shadowTick != IngameState.instance.numberTicks - 1L) {
                        this.m_shadowFM = var9;
                        this.m_shadowBM = var10;
                     }

                     this.shadowTick = IngameState.instance.numberTicks;
                     this.m_shadowFM = PZMath.lerp(this.m_shadowFM, var9, var27);
                     var9 = this.m_shadowFM;
                     this.m_shadowBM = PZMath.lerp(this.m_shadowBM, var10, var27);
                     var10 = this.m_shadowBM;
                  } else if (this.isZombie() && this.isCurrentState(FakeDeadZombieState.instance())) {
                     var11 = 1.0F;
                  } else if (this.isSceneCulled()) {
                     return;
                  }

    ColorInfo var30 = var4.lighting[var5].lightInfo();
                  IsoDeadBody.renderShadow(var1, var2, var3, var6, var8, var9, var10, var30, var11);
               }
            }
         }
      }
   }

    void checkUpdateModelTextures() {
      if (this.bUpdateModelTextures && this.hasActiveModel()) {
         this.bUpdateModelTextures = false;
         this.textureCreator = ModelInstanceTextureCreator.alloc();
         this.textureCreator.init(this);
      }

      if (this.bUpdateEquippedTextures && this.hasActiveModel()) {
         this.bUpdateEquippedTextures = false;
         if (this.primaryHandModel != nullptr && this.primaryHandModel.getTextureInitializer() != nullptr) {
            this.primaryHandModel.getTextureInitializer().setDirty();
         }

         if (this.secondaryHandModel != nullptr && this.secondaryHandModel.getTextureInitializer() != nullptr) {
            this.secondaryHandModel.getTextureInitializer().setDirty();
         }
      }
   }

    bool isMaskClicked(int var1, int var2, bool var3) {
      if (this.sprite == nullptr) {
    return false;
      } else {
         return !this.bUseParts ? super.isMaskClicked(var1, var2, var3) : this.legsSprite.isMaskClicked(this.dir, var1, var2, var3);
      }
   }

    void setHaloNote(const std::string& var1) {
      this.setHaloNote(var1, this.haloDispTime);
   }

    void setHaloNote(const std::string& var1, float var2) {
      this.setHaloNote(var1, 0, 255, 0, var2);
   }

    void setHaloNote(const std::string& var1, int var2, int var3, int var4, float var5) {
      if (this.haloNote != nullptr && var1 != nullptr) {
         this.haloDispTime = var5;
         this.haloNote.setDefaultColors(var2, var3, var4);
         this.haloNote.ReadString(var1);
         this.haloNote.setInternalTickClock(this.haloDispTime);
      }
   }

    float getHaloTimerCount() {
      return this.haloNote != nullptr ? this.haloNote.getInternalClock() : 0.0F;
   }

    void DoSneezeText() {
      if (this.BodyDamage != nullptr) {
         if (this.BodyDamage.IsSneezingCoughing() > 0) {
    std::string var1 = nullptr;
    int var2 = 0;
            if (this.BodyDamage.IsSneezingCoughing() == 1) {
               var1 = Translator.getText("IGUI_PlayerText_Sneeze");
               var2 = Rand.Next(2) + 1;
               this.setVariable("Ext", "Sneeze" + var2);
            }

            if (this.BodyDamage.IsSneezingCoughing() == 2) {
               var1 = Translator.getText("IGUI_PlayerText_Cough");
               this.setVariable("Ext", "Cough");
            }

            if (this.BodyDamage.IsSneezingCoughing() == 3) {
               var1 = Translator.getText("IGUI_PlayerText_SneezeMuffled");
               var2 = Rand.Next(2) + 1;
               this.setVariable("Ext", "Sneeze" + var2);
            }

            if (this.BodyDamage.IsSneezingCoughing() == 4) {
               var1 = Translator.getText("IGUI_PlayerText_CoughMuffled");
               this.setVariable("Ext", "Cough");
            }

            if (var1 != nullptr) {
               this.Say(var1);
               this.reportEvent("EventDoExt");
               if (GameClient.bClient && dynamic_cast<IsoPlayer*>(this) != nullptr && ((IsoPlayer)this).isLocalPlayer()) {
                  GameClient.sendSneezingCoughing(this.getOnlineID(), this.BodyDamage.IsSneezingCoughing(), (byte)var2);
               }
            }
         }
      }
   }

    std::string getSayLine() {
      return this.chatElement.getSayLine();
   }

    void setSayLine(const std::string& var1) {
      this.Say(var1);
   }

    ChatMessage getLastChatMessage() {
      return this.lastChatMessage;
   }

    void setLastChatMessage(ChatMessage var1) {
      this.lastChatMessage = var1;
   }

    std::string getLastSpokenLine() {
      return this.lastSpokenLine;
   }

    void setLastSpokenLine(const std::string& var1) {
      this.lastSpokenLine = var1;
   }

    void doSleepSpeech() {
      this.sleepSpeechCnt++;
      if (this.sleepSpeechCnt > 250 * PerformanceSettings.getLockFPS() / 30.0F) {
         this.sleepSpeechCnt = 0;
         if (sleepText == nullptr) {
            sleepText = "ZzzZZZzzzz";
            ChatElement.addNoLogText(sleepText);
         }

         this.SayWhisper(sleepText);
      }
   }

    void SayDebug(const std::string& var1) {
      this.chatElement.SayDebug(0, var1);
   }

    void SayDebug(int var1, const std::string& var2) {
      this.chatElement.SayDebug(var1, var2);
   }

    int getMaxChatLines() {
      return this.chatElement.getMaxChatLines();
   }

    void Say(const std::string& var1) {
      if (!this.isZombie()) {
         this.ProcessSay(var1, this.SpeakColour.r, this.SpeakColour.g, this.SpeakColour.b, 30.0F, 0, "default");
      }
   }

    void Say(const std::string& var1, float var2, float var3, float var4, UIFont var5, float var6, const std::string& var7) {
      this.ProcessSay(var1, var2, var3, var4, var6, 0, var7);
   }

    void SayWhisper(const std::string& var1) {
      this.ProcessSay(var1, this.SpeakColour.r, this.SpeakColour.g, this.SpeakColour.b, 10.0F, 0, "whisper");
   }

    void SayShout(const std::string& var1) {
      this.ProcessSay(var1, this.SpeakColour.r, this.SpeakColour.g, this.SpeakColour.b, 60.0F, 0, "shout");
   }

    void SayRadio(const std::string& var1, float var2, float var3, float var4, UIFont var5, float var6, int var7, const std::string& var8) {
      this.ProcessSay(var1, var2, var3, var4, var6, var7, var8);
   }

    void ProcessSay(const std::string& var1, float var2, float var3, float var4, float var5, int var6, const std::string& var7) {
      if (this.AllowConversation) {
         if (TutorialManager.instance.ProfanityFilter) {
            var1 = ProfanityFilter.getInstance().filterString(var1);
         }

         if (var7 == "default")) {
            ChatManager.getInstance().showInfoMessage(((IsoPlayer)this).getUsername(), var1);
            this.lastSpokenLine = var1;
         } else if (var7 == "whisper")) {
            this.lastSpokenLine = var1;
         } else if (var7 == "shout")) {
            ChatManager.getInstance().sendMessageToChat(((IsoPlayer)this).getUsername(), ChatType.shout, var1);
            this.lastSpokenLine = var1;
         } else if (var7 == "radio")) {
    UIFont var8 = UIFont.Medium;
    bool var9 = true;
    bool var10 = true;
    bool var11 = true;
    bool var12 = false;
    bool var13 = false;
    bool var14 = true;
            this.chatElement.addChatLine(var1, var2, var3, var4, var8, var5, var7, var9, var10, var11, var12, var13, var14);
            if (ZomboidRadio.isStaticSound(var1)) {
               ChatManager.getInstance().showStaticRadioSound(var1);
            } else {
               ChatManager.getInstance().showRadioMessage(var1, var6);
            }
         }
      }
   }

    void addLineChatElement(const std::string& var1) {
      this.addLineChatElement(var1, 1.0F, 1.0F, 1.0F);
   }

    void addLineChatElement(const std::string& var1, float var2, float var3, float var4) {
      this.addLineChatElement(var1, var2, var3, var4, UIFont.Dialogue, 30.0F, "default");
   }

    void addLineChatElement(const std::string& var1, float var2, float var3, float var4, UIFont var5, float var6, const std::string& var7) {
      this.addLineChatElement(var1, var2, var3, var4, var5, var6, var7, false, false, false, false, false, true);
   }

   public void addLineChatElement(
      std::string var1,
      float var2,
      float var3,
      float var4,
      UIFont var5,
      float var6,
      std::string var7,
      boolean var8,
      boolean var9,
      boolean var10,
      boolean var11,
      boolean var12,
      boolean var13
   ) {
      this.chatElement.addChatLine(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13);
   }

    bool playerIsSelf() {
      return IsoPlayer.getInstance() == this;
   }

    int getUserNameHeight() {
      if (!GameClient.bClient) {
    return 0;
      } else {
         return this.userName != nullptr ? this.userName.getHeight() : 0;
      }
   }

    void initTextObjects() {
      this.hasInitTextObjects = true;
      if (dynamic_cast<IsoPlayer*>(this) != nullptr) {
         this.chatElement.setMaxChatLines(5);
         if (IsoPlayer.getInstance() != nullptr) {
            System.out.println("FirstNAME:" + IsoPlayer.getInstance().username);
         }

         this.isoPlayer = (IsoPlayer)this;
         if (this.isoPlayer.username != nullptr) {
            this.userName = std::make_unique<TextDrawObject>();
            this.userName.setAllowAnyImage(true);
            this.userName.setDefaultFont(UIFont.Small);
            this.userName.setDefaultColors(255, 255, 255, 255);
            this.updateUserName();
         }

         if (this.haloNote == nullptr) {
            this.haloNote = std::make_unique<TextDrawObject>();
            this.haloNote.setDefaultFont(UIFont.Small);
            this.haloNote.setDefaultColors(0, 255, 0);
            this.haloNote.setDrawBackground(true);
            this.haloNote.setAllowImages(true);
            this.haloNote.setAllowAnyImage(true);
            this.haloNote.setOutlineColors(0.0F, 0.0F, 0.0F, 0.33F);
         }
      }
   }

    void updateUserName() {
      if (this.userName != nullptr && this.isoPlayer != nullptr) {
    std::string var1 = this.isoPlayer.getUsername(true);
         if (this != IsoPlayer.getInstance()
            && this.isInvisible()
            && IsoPlayer.getInstance() != nullptr
            && IsoPlayer.getInstance().accessLevel == "")
            && (!Core.bDebug || !DebugOptions.instance.CheatPlayerSeeEveryone.getValue())) {
            this.userName.ReadString("");
            return;
         }

    Faction var2 = Faction.getPlayerFaction(this.isoPlayer);
         if (var2 != nullptr) {
            if (!this.isoPlayer.showTag && this.isoPlayer != IsoPlayer.getInstance() && Faction.getPlayerFaction(IsoPlayer.getInstance()) != var2) {
               this.isoPlayer.tagPrefix = "";
            } else {
               this.isoPlayer.tagPrefix = var2.getTag();
               if (var2.getTagColor() != nullptr) {
                  this.isoPlayer.setTagColor(var2.getTagColor());
               }
            }
         } else {
            this.isoPlayer.tagPrefix = "";
         }

    bool var3 = this.isoPlayer != nullptr && this.isoPlayer.bRemote || Core.getInstance().isShowYourUsername();
         if (IsoCamera.dynamic_cast<IsoPlayer*>(CamCharacter) != nullptr && !((IsoPlayer)IsoCamera.CamCharacter).accessLevel == "")) {
    bool var8 = true;
         } else {
    bool var10000 = false;
         }

    bool var5 = IsoCamera.dynamic_cast<IsoPlayer*>(CamCharacter) != nullptr && ((IsoPlayer)IsoCamera.CamCharacter).canSeeAll;
         if (!ServerOptions.instance.DisplayUserName.getValue() && !ServerOptions.instance.ShowFirstAndLastName.getValue() && !var5) {
            var3 = false;
         }

         if (!var3) {
            var1 = "";
         }

         if (var3 && this.isoPlayer.tagPrefix != nullptr && !this.isoPlayer.tagPrefix == "")) {
            var1 = "[col="
               + std::make_shared<float>(this.isoPlayer.getTagColor().r * 255.0F).intValue()
               + ","
               + std::make_shared<float>(this.isoPlayer.getTagColor().g * 255.0F).intValue()
               + ","
               + std::make_shared<float>(this.isoPlayer.getTagColor().b * 255.0F).intValue()
               + "]["
               + this.isoPlayer.tagPrefix
               + "][/] "
               + var1;
         }

         if (var3 && !this.isoPlayer.accessLevel == "") && this.isoPlayer.isShowAdminTag()) {
            var1 = this.namesPrefix.get(this.isoPlayer.accessLevel) + var1;
         }

         if (var3
            && !this.isoPlayer.getSafety().isEnabled()
            && ServerOptions.instance.ShowSafety.getValue()
            && NonPvpZone.getNonPvpZone(PZMath.fastfloor(this.isoPlayer.x), PZMath.fastfloor(this.isoPlayer.y)) == nullptr) {
            var1 = var1 + " [img=media/ui/Skull.png]";
         }

         if (this.isoPlayer.isSpeek && !this.isoPlayer.isVoiceMute) {
            var1 = "[img=media/ui/voiceon.png] " + var1;
         }

         if (this.isoPlayer.isVoiceMute) {
            var1 = "[img=media/ui/voicemuted.png] " + var1;
         }

    BaseVehicle var6 = IsoCamera.CamCharacter == this.isoPlayer ? this.isoPlayer.getNearVehicle() : nullptr;
         if (this.getVehicle() == nullptr
            && var6 != nullptr
            && (
               this.isoPlayer.getInventory().haveThisKeyId(var6.getKeyId()) != nullptr
                  || var6.isHotwired()
                  || SandboxOptions.getInstance().VehicleEasyUse.getValue()
            )) {
    Color var7 = Color.HSBtoRGB(var6.colorHue, var6.colorSaturation * 0.5F, var6.colorValue);
            var1 = " [img=media/ui/CarKey.png," + var7.getRedByte() + "," + var7.getGreenByte() + "," + var7.getBlueByte() + "]" + var1;
         }

         if (!var1 == this.userName.getOriginal())) {
            this.userName.ReadString(var1);
         }
      }
   }

    void updateTextObjects() {
      if (!GameServer.bServer) {
         if (!this.hasInitTextObjects) {
            this.initTextObjects();
         }

         if (!this.Speaking) {
            this.DoSneezeText();
            if (this.isAsleep() && this.getCurrentSquare() != nullptr && this.getCurrentSquare().getCanSee(0)) {
               this.doSleepSpeech();
            }
         }

         if (this.isoPlayer != nullptr) {
            this.radioEquipedCheck();
         }

         this.Speaking = false;
         this.drawUserName = false;
         this.canSeeCurrent = false;
         if (this.haloNote != nullptr && this.haloNote.getInternalClock() > 0.0F) {
            this.haloNote.updateInternalTickClock();
         }

         this.legsSprite.PlayAnim("ZombieWalk1");
         this.chatElement.update();
         this.Speaking = this.chatElement.IsSpeaking();
         if (!this.Speaking || this.isDead()) {
            this.Speaking = false;
            this.callOut = false;
         }
      }
   }

    void renderlast() {
      super.renderlast();
    int var1 = IsoCamera.frameState.playerIndex;
    float var2 = this.x;
    float var3 = this.y;
      if (this.sx == 0.0F && this.def != nullptr) {
         this.sx = IsoUtils.XToScreen(var2 + this.def.offX, var3 + this.def.offY, this.z + this.def.offZ, 0);
         this.sy = IsoUtils.YToScreen(var2 + this.def.offX, var3 + this.def.offY, this.z + this.def.offZ, 0);
         this.sx = this.sx - (this.offsetX - 8.0F);
         this.sy = this.sy - (this.offsetY - 60.0F);
      }

      if (this.hasInitTextObjects && this.isoPlayer != nullptr || this.chatElement.getHasChatToDisplay()) {
    float var4 = IsoUtils.XToScreen(var2, var3, this.getZ(), 0);
    float var5 = IsoUtils.YToScreen(var2, var3, this.getZ(), 0);
         var4 = var4 - IsoCamera.getOffX() - this.offsetX;
         var5 = var5 - IsoCamera.getOffY() - this.offsetY;
         var5 -= 128 / (2 / Core.TileScale);
    float var6 = Core.getInstance().getZoom(var1);
         var4 /= var6;
         var5 /= var6;
         this.canSeeCurrent = true;
         this.drawUserName = false;
         if (this.isoPlayer != nullptr
               && (this == IsoCamera.frameState.CamCharacter || this.getCurrentSquare() != nullptr && this.getCurrentSquare().getCanSee(var1))
            || IsoPlayer.getInstance().isCanSeeAll()) {
            if (this == IsoPlayer.getInstance()) {
               this.canSeeCurrent = true;
            }

            if (GameClient.bClient && this.userName != nullptr && this.doRenderShadow) {
               this.drawUserName = false;
               if (ServerOptions.getInstance().MouseOverToSeeDisplayName.getValue()
                  && this != IsoPlayer.getInstance()
                  && !IsoPlayer.getInstance().isCanSeeAll()) {
    ClickObject var7 = IsoObjectPicker.Instance.ContextPick(Mouse.getXA(), Mouse.getYA());
                  if (var7 != nullptr && var7.tile != nullptr) {
                     for (int var8 = var7.tile.square.getX() - 1; var8 < var7.tile.square.getX() + 2; var8++) {
                        for (int var9 = var7.tile.square.getY() - 1; var9 < var7.tile.square.getY() + 2; var9++) {
    IsoGridSquare var10 = IsoCell.getInstance().getGridSquare(var8, var9, var7.tile.square.getZ());
                           if (var10 != nullptr) {
                              for (int var11 = 0; var11 < var10.getMovingObjects().size(); var11++) {
    IsoMovingObject var12 = (IsoMovingObject)var10.getMovingObjects().get(var11);
                                 if (dynamic_cast<IsoPlayer*>(var12) != nullptr && this == var12) {
                                    this.drawUserName = true;
                                    break;
                                 }
                              }

                              if (this.drawUserName) {
                                 break;
                              }
                           }

                           if (this.drawUserName) {
                              break;
                           }
                        }
                     }
                  }
               } else {
                  this.drawUserName = true;
               }

               if (this.drawUserName) {
                  this.updateUserName();
               }
            }

            if (!GameClient.bClient && this.isoPlayer != nullptr && this.isoPlayer.getVehicle() == nullptr) {
    std::string var47 = "";
    BaseVehicle var81 = this.isoPlayer.getNearVehicle();
               if (this.getVehicle() == nullptr
                  && var81 != nullptr
                  && var81.getPartById("Engine") != nullptr
                  && (
                     this.isoPlayer.getInventory().haveThisKeyId(var81.getKeyId()) != nullptr
                        || var81.isHotwired()
                        || SandboxOptions.getInstance().VehicleEasyUse.getValue()
                  )
                  && UIManager.VisibleAllUI) {
    Color var91 = Color.HSBtoRGB(var81.colorHue, var81.colorSaturation * 0.5F, var81.colorValue, L_renderLast.color);
                  var47 = " [img=media/ui/CarKey.png," + var91.getRedByte() + "," + var91.getGreenByte() + "," + var91.getBlueByte() + "]";
               }

               if (!var47 == "")) {
                  this.userName.ReadString(var47);
                  this.drawUserName = true;
               }
            }
         }

         if (this.isoPlayer != nullptr && this.hasInitTextObjects && (this.playerIsSelf() || this.canSeeCurrent)) {
            if (this.canSeeCurrent && this.drawUserName) {
               var5 -= this.userName.getHeight();
               this.userName.AddBatchedDraw((int)var4, (int)var5, true);
            }

            if (this.playerIsSelf()) {
    ActionProgressBar var48 = UIManager.getProgressBar(var1);
               if (var48 != nullptr && var48.isVisible()) {
                  var5 -= var48.getHeight().intValue() + 2;
               }
            }

            if (this.playerIsSelf() && this.haloNote != nullptr && this.haloNote.getInternalClock() > 0.0F) {
    float var49 = this.haloNote.getInternalClock() / (this.haloDispTime / 4.0F);
               var49 = PZMath.min(var49, 1.0F);
               var5 -= this.haloNote.getHeight() + 2;
               this.haloNote.AddBatchedDraw((int)var4, (int)var5, true, var49);
            }
         }

    bool var51 = false;
         if (IsoPlayer.getInstance() != this
            && this.equipedRadio != nullptr
            && this.equipedRadio.getDeviceData() != nullptr
            && this.equipedRadio.getDeviceData().getHeadphoneType() >= 0) {
            var51 = true;
         }

         if (this.equipedRadio != nullptr && this.equipedRadio.getDeviceData() != nullptr && !this.equipedRadio.getDeviceData().getIsTurnedOn()) {
            var51 = true;
         }

    bool var82 = GameClient.bClient && IsoCamera.dynamic_cast<IsoPlayer*>(CamCharacter) != nullptr && !((IsoPlayer)IsoCamera.CamCharacter).accessLevel == "");
         if (!this.m_invisible || this == IsoCamera.frameState.CamCharacter || var82) {
            this.chatElement.renderBatched(IsoPlayer.getPlayerIndex(), (int)var4, (int)var5, var51);
         }
      }

      if (Core.bDebug && DebugOptions.instance.char.Debug.Render.Angle.getValue() && this.hasActiveModel()) {
    Vector2 var15 = tempo;
    AnimationPlayer var30 = this.getAnimationPlayer();
         var15.set(this.dir.ToVector());
         this.drawDirectionLine(var15, 2.4F, 0.0F, 1.0F, 0.0F);
         var15.setLengthAndDirection(this.getLookAngleRadians(), 1.0F);
         this.drawDirectionLine(var15, 2.0F, 1.0F, 1.0F, 1.0F);
         var15.setLengthAndDirection(this.getAnimAngleRadians(), 1.0F);
         this.drawDirectionLine(var15, 2.0F, 1.0F, 1.0F, 0.0F);
    float var41 = this.getForwardDirection().getDirection();
         var15.setLengthAndDirection(var41, 1.0F);
         this.drawDirectionLine(var15, 2.0F, 0.0F, 0.0F, 1.0F);
      }

      if (Core.bDebug && DebugOptions.instance.char.Debug.Render.DeferredMovement.getValue() && this.hasActiveModel()) {
    Vector2 var16 = tempo;
    AnimationPlayer var31 = this.getAnimationPlayer();
         this.getDeferredMovement(var16);
         this.drawDirectionLine(var16, 1000.0F * var16.getLength() / GameTime.instance.getMultiplier() * 2.0F, 1.0F, 0.5F, 0.5F);
      }

      if (Core.bDebug && DebugOptions.instance.char.Debug.Render.DeferredAngles.getValue() && this.hasActiveModel()) {
    Vector2 var17 = tempo;
    AnimationPlayer var32 = this.getAnimationPlayer();
         this.getDeferredMovement(var17);
         this.drawDirectionLine(var17, 1000.0F * var17.getLength() / GameTime.instance.getMultiplier() * 2.0F, 1.0F, 0.5F, 0.5F);
      }

      if (Core.bDebug && DebugOptions.instance.char.Debug.Render.AimCone.getValue()) {
         this.debugAim();
      }

      if (Core.bDebug && DebugOptions.instance.char.Debug.Render.TestDotSide.getValue()) {
         this.debugTestDotSide();
      }

      if (Core.bDebug && DebugOptions.instance.char.Debug.Render.Vision.getValue()) {
         this.debugVision();
      }

      if (Core.bDebug) {
         if (DebugOptions.instance.MultiplayerShowZombieMultiplier.getValue() && dynamic_cast<IsoZombie*>(this) != nullptr var18) {
    uint8_t var42 = var18.canHaveMultipleHits();
    Color var33;
            if (var42 == 0) {
               var33 = Colors.Green;
            } else if (var42 == 1) {
               var33 = Colors.Yellow;
            } else {
               var33 = Colors.Red;
            }

            LineDrawer.DrawIsoCircle(this.x, this.y, this.z, 0.45F, 4, var33.r, var33.g, var33.b, 0.5F);
            TextManager.instance
               .DrawStringCentre(
                  UIFont.DebugConsole,
                  IsoUtils.XToScreenExact(this.x + 0.4F, this.y + 0.4F, this.z, 0),
                  IsoUtils.YToScreenExact(this.x + 0.4F, this.y - 1.4F, this.z, 0),
                  std::string.valueOf(var18.OnlineID),
                  var33.r,
                  var33.g,
                  var33.b,
                  var33.a
               );
         }

         if (DebugOptions.instance.MultiplayerShowZombieOwner.getValue() && dynamic_cast<IsoZombie*>(this) != nullptr var19) {
    Color var34;
            if (var19.isDead()) {
               var34 = Colors.Yellow;
            } else if (var19.isRemoteZombie()) {
               var34 = Colors.OrangeRed;
            } else {
               var34 = Colors.Chartreuse;
            }

            LineDrawer.DrawIsoCircle(this.x, this.y, this.z, 0.45F, 4, var34.r, var34.g, var34.b, 0.5F);
            TextManager.instance
               .DrawStringCentre(
                  UIFont.DebugConsole,
                  IsoUtils.XToScreenExact(this.x + 0.4F, this.y + 0.4F, this.z, 0),
                  IsoUtils.YToScreenExact(this.x + 0.4F, this.y - 1.4F, this.z, 0),
                  std::string.valueOf(var19.OnlineID),
                  var34.r,
                  var34.g,
                  var34.b,
                  var34.a
               );
         }

         if (DebugOptions.instance.MultiplayerShowZombiePrediction.getValue() && dynamic_cast<IsoZombie*>(this) != nullptr var20) {
            LineDrawer.DrawIsoTransform(
               this.realx,
               this.realy,
               this.z,
               this.realdir.ToVector().x,
               this.realdir.ToVector().y,
               0.35F,
               16,
               Colors.Blue.r,
               Colors.Blue.g,
               Colors.Blue.b,
               0.35F,
               1
            );
            if (var20.networkAI.DebugInterfaceActive) {
               LineDrawer.DrawIsoCircle(this.x, this.y, this.z, 0.4F, 4, 1.0F, 0.1F, 0.1F, 0.35F);
            } else if (!var20.isRemoteZombie()) {
               LineDrawer.DrawIsoCircle(this.x, this.y, this.z, 0.3F, 3, Colors.Magenta.r, Colors.Magenta.g, Colors.Magenta.b, 0.35F);
            } else {
               LineDrawer.DrawIsoCircle(this.x, this.y, this.z, 0.3F, 5, Colors.Magenta.r, Colors.Magenta.g, Colors.Magenta.b, 0.35F);
            }

            LineDrawer.DrawIsoTransform(
               var20.networkAI.targetX,
               var20.networkAI.targetY,
               this.z,
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
               this.x,
               this.y,
               this.z,
               var20.networkAI.targetX,
               var20.networkAI.targetY,
               this.z,
               Colors.LimeGreen.r,
               Colors.LimeGreen.g,
               Colors.LimeGreen.b,
               0.35F,
               1
            );
            if (IsoUtils.DistanceToSquared(this.x, this.y, this.realx, this.realy) > 4.5F) {
               LineDrawer.DrawIsoLine(this.realx, this.realy, this.z, this.x, this.y, this.z, Colors.Magenta.r, Colors.Magenta.g, Colors.Magenta.b, 0.35F, 1);
            } else {
               LineDrawer.DrawIsoLine(this.realx, this.realy, this.z, this.x, this.y, this.z, Colors.Blue.r, Colors.Blue.g, Colors.Blue.b, 0.35F, 1);
            }
         }

         if (DebugOptions.instance.MultiplayerShowZombieDesync.getValue() && dynamic_cast<IsoZombie*>(this) != nullptr var21) {
    float var35 = IsoUtils.DistanceTo(this.getX(), this.getY(), this.realx, this.realy);
            if (var21.isRemoteZombie() && var35 > 1.0F) {
               LineDrawer.DrawIsoLine(this.realx, this.realy, this.z, this.x, this.y, this.z, Colors.Blue.r, Colors.Blue.g, Colors.Blue.b, 0.9F, 1);
               LineDrawer.DrawIsoTransform(
                  this.realx,
                  this.realy,
                  this.z,
                  this.realdir.ToVector().x,
                  this.realdir.ToVector().y,
                  0.35F,
                  16,
                  Colors.Blue.r,
                  Colors.Blue.g,
                  Colors.Blue.b,
                  0.9F,
                  1
               );
               LineDrawer.DrawIsoCircle(this.x, this.y, this.z, 0.4F, 4, 1.0F, 1.0F, 1.0F, 0.9F);
    float var43 = IsoUtils.DistanceTo(this.realx, this.realy, var21.networkAI.targetX, var21.networkAI.targetY);
    float var52 = IsoUtils.DistanceTo(this.x, this.y, var21.networkAI.targetX, var21.networkAI.targetY) / var43;
    float var83 = IsoUtils.XToScreenExact(this.x, this.y, this.z, 0);
    float var92 = IsoUtils.YToScreenExact(this.x, this.y, this.z, 0);
               TextManager.instance
                  .DrawStringCentre(
                     UIFont.DebugConsole,
                     var83,
                     var92,
                     std::string.format("dist:%f scale1:%f", var35, var52),
                     Colors.NavajoWhite.r,
                     Colors.NavajoWhite.g,
                     Colors.NavajoWhite.b,
                     0.9F
                  );
            }
         }

         if (DebugOptions.instance.MultiplayerShowHit.getValue() && this.getHitReactionNetworkAI() != nullptr && this.getHitReactionNetworkAI().isSetup()) {
            LineDrawer.DrawIsoLine(
               this.x,
               this.y,
               this.z,
               this.x + this.getHitDir().getX(),
               this.y + this.getHitDir().getY(),
               this.z,
               Colors.BlueViolet.r,
               Colors.BlueViolet.g,
               Colors.BlueViolet.b,
               0.8F,
               1
            );
            LineDrawer.DrawIsoLine(
               this.getHitReactionNetworkAI().startPosition.x,
               this.getHitReactionNetworkAI().startPosition.y,
               this.z,
               this.getHitReactionNetworkAI().finalPosition.x,
               this.getHitReactionNetworkAI().finalPosition.y,
               this.z,
               Colors.Salmon.r,
               Colors.Salmon.g,
               Colors.Salmon.b,
               0.8F,
               1
            );
    float var10007 = Colors.Salmon.r - 0.2F;
    float var10008 = Colors.Salmon.g + 0.2F;
            LineDrawer.DrawIsoTransform(
               this.getHitReactionNetworkAI().startPosition.x,
               this.getHitReactionNetworkAI().startPosition.y,
               this.z,
               this.getHitReactionNetworkAI().startDirection.x,
               this.getHitReactionNetworkAI().startDirection.y,
               0.4F,
               16,
               var10007,
               var10008,
               Colors.Salmon.b,
               0.8F,
               1
            );
            var10008 = Colors.Salmon.g - 0.2F;
            LineDrawer.DrawIsoTransform(
               this.getHitReactionNetworkAI().finalPosition.x,
               this.getHitReactionNetworkAI().finalPosition.y,
               this.z,
               this.getHitReactionNetworkAI().finalDirection.x,
               this.getHitReactionNetworkAI().finalDirection.y,
               0.4F,
               16,
               Colors.Salmon.r,
               var10008,
               Colors.Salmon.b,
               0.8F,
               1
            );
         }

         if (DebugOptions.instance.MultiplayerShowPlayerPrediction.getValue() && dynamic_cast<IsoPlayer*>(this) != nullptr) {
            if (this.isoPlayer != nullptr && this.isoPlayer.networkAI != nullptr && this.isoPlayer.networkAI.footstepSoundRadius != 0) {
               LineDrawer.DrawIsoCircle(
                  this.x, this.y, this.z, this.isoPlayer.networkAI.footstepSoundRadius, 32, Colors.Violet.r, Colors.Violet.g, Colors.Violet.b, 0.5F
               );
            }

            if (this.isoPlayer != nullptr && this.isoPlayer.bRemote) {
               LineDrawer.DrawIsoCircle(this.x, this.y, this.z, 0.3F, 16, Colors.OrangeRed.r, Colors.OrangeRed.g, Colors.OrangeRed.b, 0.5F);
               tempo.set(this.realdir.ToVector());
               LineDrawer.DrawIsoTransform(this.realx, this.realy, this.z, tempo.x, tempo.y, 0.35F, 16, Colors.Blue.r, Colors.Blue.g, Colors.Blue.b, 0.5F, 1);
               LineDrawer.DrawIsoLine(this.realx, this.realy, this.z, this.x, this.y, this.z, Colors.Blue.r, Colors.Blue.g, Colors.Blue.b, 0.5F, 1);
               tempo.set(((IsoPlayer)this).networkAI.targetX, ((IsoPlayer)this).networkAI.targetY);
               LineDrawer.DrawIsoTransform(tempo.x, tempo.y, this.z, 1.0F, 0.0F, 0.4F, 16, Colors.LimeGreen.r, Colors.LimeGreen.g, Colors.LimeGreen.b, 0.5F, 1);
               LineDrawer.DrawIsoLine(this.x, this.y, this.z, tempo.x, tempo.y, this.z, Colors.LimeGreen.r, Colors.LimeGreen.g, Colors.LimeGreen.b, 0.5F, 1);
            }
         }

         if (DebugOptions.instance.MultiplayerShowTeleport.getValue() && this.getNetworkCharacterAI() != nullptr) {
    NetworkTeleportDebug var22 = this.getNetworkCharacterAI().getTeleportDebug();
            if (var22 != nullptr) {
               LineDrawer.DrawIsoLine(
                  var22.lx, var22.ly, var22.lz, var22.nx, var22.ny, var22.nz, Colors.NavajoWhite.r, Colors.NavajoWhite.g, Colors.NavajoWhite.b, 0.7F, 3
               );
               LineDrawer.DrawIsoCircle(var22.nx, var22.ny, var22.nz, 0.2F, 16, Colors.NavajoWhite.r, Colors.NavajoWhite.g, Colors.NavajoWhite.b, 0.7F);
    float var36 = IsoUtils.XToScreenExact(var22.lx, var22.ly, var22.lz, 0);
    float var44 = IsoUtils.YToScreenExact(var22.lx, var22.ly, var22.lz, 0);
               TextManager.instance
                  .DrawStringCentre(
                     UIFont.DebugConsole,
                     var36,
                     var44,
                     std::string.format("%s id=%d", dynamic_cast<IsoPlayer*>(this) != nullptr ? ((IsoPlayer)this).getUsername() : this.getClass().getSimpleName(), var22.id),
                     Colors.NavajoWhite.r,
                     Colors.NavajoWhite.g,
                     Colors.NavajoWhite.b,
                     0.7F
                  );
               TextManager.instance
                  .DrawStringCentre(
                     UIFont.DebugConsole, var36, var44 + 10.0F, var22.type.name(), Colors.NavajoWhite.r, Colors.NavajoWhite.g, Colors.NavajoWhite.b, 0.7F
                  );
            }
         } else if (this.getNetworkCharacterAI() != nullptr) {
            this.getNetworkCharacterAI().clearTeleportDebug();
         }

         if (DebugOptions.instance.MultiplayerShowZombieStatus.getValue() && dynamic_cast<IsoZombie*>(this) != nullptr
            || DebugOptions.instance.MultiplayerShowPlayerStatus.getValue() && dynamic_cast<IsoPlayer*>(this) != nullptr && !((IsoPlayer)this).isGodMod()) {
    StringDrawer var23 = TextManager.instance::DrawString;
            if (dynamic_cast<IsoPlayer*>(this) != nullptr && this.isLocal()) {
               var23 = TextManager.instance::DrawStringRight;
            }

    float var37 = IsoUtils.XToScreenExact(this.x, this.y, this.z, 0);
    float var45 = IsoUtils.YToScreenExact(this.x, this.y, this.z, 0);
    float var53 = 10.0F;
    Color var84 = Colors.GreenYellow;
    float var54;
            var23.draw(
               UIFont.DebugConsole,
               var37,
               var45 + (var54 = var53 + 11.0F),
               std::string.format(
                  "%d %s : %.03f / %.03f",
                  this.getOnlineID(),
                  this.isFemale() ? "F" : "M",
                  this.getHealth(),
                  dynamic_cast<IsoZombie*>(this) != nullptr ? 0.0F : this.getBodyDamage().getOverallBodyHealth()
               ),
               var84.r,
               var84.g,
               var84.b,
               var84.a
            );
            var23.draw(
               UIFont.DebugConsole,
               var37,
               var45 + (var53 = var54 + 11.0F),
               std::string.format("x=%09.3f ", this.x) + std::string.format("y=%09.3f ", this.y) + std::string.format("z=%d", (byte)this.z),
               var84.r,
               var84.g,
               var84.b,
               var84.a
            );
            if (dynamic_cast<IsoPlayer*>(this) != nullptr var85) {
    Color var93 = Colors.NavajoWhite;
    float var56;
               var23.draw(
                  UIFont.DebugConsole,
                  var37,
                  var45 + (var56 = var53 + 18.0F),
                  std::string.format("IdleSpeed: %s , targetDist: %s ", var85.getVariableString("IdleSpeed"), var85.getVariableString("targetDist")),
                  var93.r,
                  var93.g,
                  var93.b,
                  1.0
               );
    float var57;
               var23.draw(
                  UIFont.DebugConsole,
                  var37,
                  var45 + (var57 = var56 + 11.0F),
                  std::string.format("WalkInjury: %s , WalkSpeed: %s", var85.getVariableString("WalkInjury"), var85.getVariableString("WalkSpeed")),
                  var93.r,
                  var93.g,
                  var93.b,
                  1.0
               );
    float var58;
               var23.draw(
                  UIFont.DebugConsole,
                  var37,
                  var45 + (var58 = var57 + 11.0F),
                  std::string.format("DeltaX: %s , DeltaY: %s", var85.getVariableString("DeltaX"), var85.getVariableString("DeltaY")),
                  var93.r,
                  var93.g,
                  var93.b,
                  1.0
               );
    float var59;
               var23.draw(
                  UIFont.DebugConsole,
                  var37,
                  var45 + (var59 = var58 + 11.0F),
                  std::string.format(
                     "AttackVariationX: %s , AttackVariationY: %s", var85.getVariableString("AttackVariationX"), var85.getVariableString("AttackVariationY")
                  ),
                  var93.r,
                  var93.g,
                  var93.b,
                  1.0
               );
    float var60;
               var23.draw(
                  UIFont.DebugConsole,
                  var37,
                  var45 + (var60 = var59 + 11.0F),
                  std::string.format("autoShootVarX: %s , autoShootVarY: %s", var85.getVariableString("autoShootVarX"), var85.getVariableString("autoShootVarY")),
                  var93.r,
                  var93.g,
                  var93.b,
                  1.0
               );
    float var61;
               var23.draw(
                  UIFont.DebugConsole,
                  var37,
                  var45 + (var61 = var60 + 11.0F),
                  std::string.format("recoilVarX: %s , recoilVarY: %s", var85.getVariableString("recoilVarX"), var85.getVariableString("recoilVarY")),
                  var93.r,
                  var93.g,
                  var93.b,
                  1.0
               );
               var23.draw(
                  UIFont.DebugConsole,
                  var37,
                  var45 + (var53 = var61 + 11.0F),
                  std::string.format("ShoveAimX: %s , ShoveAimY: %s", var85.getVariableString("ShoveAimX"), var85.getVariableString("ShoveAimY")),
                  var93.r,
                  var93.g,
                  var93.b,
                  1.0
               );
            }

            var84 = Colors.Yellow;
    float var62;
            var23.draw(
               UIFont.DebugConsole,
               var37,
               var45 + (var62 = var53 + 18.0F),
               std::string.format("isHitFromBehind=%b/%b", this.isHitFromBehind(), this.getVariableBoolean("frombehind")),
               var84.r,
               var84.g,
               var84.b,
               1.0
            );
            var23.draw(
               UIFont.DebugConsole,
               var37,
               var45 + (var53 = var62 + 11.0F),
               std::string.format("bKnockedDown=%b/%b", this.isKnockedDown(), this.getVariableBoolean("bknockeddown")),
               var84.r,
               var84.g,
               var84.b,
               1.0
            );
    float var64;
            var23.draw(
               UIFont.DebugConsole,
               var37,
               var45 + (var64 = var53 + 11.0F),
               std::string.format("isFallOnFront=%b/%b", this.isFallOnFront(), this.getVariableBoolean("fallonfront")),
               var84.r,
               var84.g,
               var84.b,
               1.0
            );
            var23.draw(
               UIFont.DebugConsole,
               var37,
               var45 + (var53 = var64 + 11.0F),
               std::string.format("isOnFloor=%b/%b", this.isOnFloor(), this.getVariableBoolean("bonfloor")),
               var84.r,
               var84.g,
               var84.b,
               1.0
            );
    float var66;
            var23.draw(
               UIFont.DebugConsole,
               var37,
               var45 + (var66 = var53 + 11.0F),
               std::string.format("isDead=%b/%b", this.isDead(), this.getVariableBoolean("bdead")),
               var84.r,
               var84.g,
               var84.b,
               1.0
            );
            if (dynamic_cast<IsoZombie*>(this) != nullptr) {
    float var67;
               var23.draw(
                  UIFont.DebugConsole,
                  var37,
                  var45 + (var67 = var66 + 11.0F),
                  std::string.format("bThump=%b", this.getVariableString("bThump")),
                  var84.r,
                  var84.g,
                  var84.b,
                  1.0
               );
    float var68;
               var23.draw(
                  UIFont.DebugConsole,
                  var37,
                  var45 + (var68 = var67 + 11.0F),
                  std::string.format("ThumpType=%s", this.getVariableString("ThumpType")),
                  var84.r,
                  var84.g,
                  var84.b,
                  1.0
               );
               var23.draw(
                  UIFont.DebugConsole,
                  var37,
                  var45 + (var53 = var68 + 11.0F),
                  std::string.format("onknees=%b", this.getVariableBoolean("onknees")),
                  var84.r,
                  var84.g,
                  var84.b,
                  1.0
               );
            } else {
               var23.draw(
                  UIFont.DebugConsole,
                  var37,
                  var45 + (var53 = var66 + 11.0F),
                  std::string.format("isBumped=%b/%s", this.isBumped(), this.getBumpType()),
                  var84.r,
                  var84.g,
                  var84.b,
                  1.0
               );
            }

            var84 = Colors.OrangeRed;
            if (this.getReanimateTimer() <= 0.0F) {
               var84 = Colors.LimeGreen;
            } else if (this.isBeingSteppedOn()) {
               var84 = Colors.Blue;
            }

    float var70;
            var23.draw(UIFont.DebugConsole, var37, var45 + (var70 = var53 + 18.0F), "Reanimate: " + this.getReanimateTimer(), var84.r, var84.g, var84.b, 1.0);
            if (this.advancedAnimator.getRootLayer() != nullptr) {
               var84 = Colors.Pink;
               var23.draw(
                  UIFont.DebugConsole,
                  var37,
                  var45 + (var53 = var70 + 18.0F),
                  "Animation set: " + this.advancedAnimator.animSet.m_Name,
                  var84.r,
                  var84.g,
                  var84.b,
                  1.0
               );
    float var72;
               var23.draw(
                  UIFont.DebugConsole,
                  var37,
                  var45 + (var72 = var53 + 11.0F),
                  "Animation state: " + this.advancedAnimator.getCurrentStateName(),
                  var84.r,
                  var84.g,
                  var84.b,
                  1.0
               );
               var23.draw(
                  UIFont.DebugConsole,
                  var37,
                  var45 + (var70 = var72 + 11.0F),
                  "Animation node: " + this.advancedAnimator.getRootLayer().getDebugNodeName(),
                  var84.r,
                  var84.g,
                  var84.b,
                  1.0
               );
            }

            var84 = Colors.LightBlue;
            var23.draw(
               UIFont.DebugConsole,
               var37,
               var45 + (var53 = var70 + 11.0F),
               std::string.format("Previous state: %s ( %s )", this.getPreviousStateName(), this.getPreviousActionContextStateName()),
               var84.r,
               var84.g,
               var84.b,
               1.0
            );
    float var74;
            var23.draw(
               UIFont.DebugConsole,
               var37,
               var45 + (var74 = var53 + 11.0F),
               std::string.format("Current state: %s ( %s )", this.getCurrentStateName(), this.getCurrentActionContextStateName()),
               var84.r,
               var84.g,
               var84.b,
               1.0
            );
            var23.draw(
               UIFont.DebugConsole,
               var37,
               var45 + (var53 = var74 + 11.0F),
               std::string.format(
                  "Child state: %s",
                  this.getActionContext() != nullptr
                        && this.getActionContext().getChildStates() != nullptr
                        && this.getActionContext().getChildStates().size() > 0
                        && this.getActionContext().getChildStateAt(0) != nullptr
                     ? this.getActionContext().getChildStateAt(0).getName()
                     : "\"\""
               ),
               var84.r,
               var84.g,
               var84.b,
               1.0
            );
            if (this.CharacterActions != nullptr) {
               var23.draw(
                  UIFont.DebugConsole,
                  var37,
                  var45 + (var53 += 11.0F),
                  std::string.format("char actions: %d", this.CharacterActions.size()),
                  var84.r,
                  var84.g,
                  var84.b,
                  1.0
               );

               for (BaseAction var96 : this.CharacterActions) {
                  if (dynamic_cast<LuaTimedActionNew*>(var96) != nullptr) {
                     var23.draw(
                        UIFont.DebugConsole,
                        var37,
                        var45 + (var53 += 11.0F),
                        std::string.format("Action: %s", ((LuaTimedActionNew)var96).getMetaType()),
                        var84.r,
                        var84.g,
                        var84.b,
                        1.0
                     );
                  }
               }
            }

            if (dynamic_cast<IsoZombie*>(this) != nullptr) {
               var84 = Colors.GreenYellow;
    IsoZombie var95 = (IsoZombie)this;
    float var76;
               var23.draw(
                  UIFont.DebugConsole,
                  var37,
                  var45 + (var76 = var53 + 18.0F),
                  "Prediction: " + this.getNetworkCharacterAI().predictionType,
                  var84.r,
                  var84.g,
                  var84.b,
                  1.0
               );
               var23.draw(
                  UIFont.DebugConsole, var37, var45 + (var53 = var76 + 11.0F), std::string.format("Real state: %s", var95.realState), var84.r, var84.g, var84.b, 1.0
               );
               if (var95.dynamic_cast<IsoPlayer*>(target) != nullptr) {
    float var78;
                  var23.draw(
                     UIFont.DebugConsole,
                     var37,
                     var45 + (var78 = var53 + 11.0F),
                     "Target: " + ((IsoPlayer)var95.target).username + "  =" + var95.vectorToTarget.getLength(),
                     var84.r,
                     var84.g,
                     var84.b,
                     1.0
                  );
               } else {
    float var79;
                  var23.draw(
                     UIFont.DebugConsole,
                     var37,
                     var45 + (var79 = var53 + 11.0F),
                     "Target: " + var95.target + "  =" + var95.vectorToTarget.getLength(),
                     var84.r,
                     var84.g,
                     var84.b,
                     1.0
                  );
               }
            }
         }
      }

      if (this.inventory != nullptr) {
         for (int var24 = 0; var24 < this.inventory.Items.size(); var24++) {
    InventoryItem var38 = (InventoryItem)this.inventory.Items.get(var24);
            if (dynamic_cast<IUpdater*>(var38) != nullptr) {
               ((IUpdater)var38).renderlast();
            }
         }

         if (Core.bDebug && DebugOptions.instance.PathfindRenderPath.getValue() && this.pfb2 != nullptr) {
            this.pfb2.render();
         }

         if (Core.bDebug && DebugOptions.instance.CollideWithObstaclesRenderRadius.getValue()) {
    float var25 = 0.3F;
    float var39 = 1.0F;
    float var46 = 1.0F;
    float var80 = 1.0F;
            if (!this.isCollidable()) {
               var80 = 0.0F;
            }

            if ((int)this.z != (int)IsoCamera.frameState.CamCharacterZ) {
               var80 = 0.5F;
               var46 = 0.5F;
               var39 = 0.5F;
            }

            LineDrawer.DrawIsoCircle(this.x, this.y, this.z, var25, 16, var39, var46, var80, 1.0F);
         }

         if (DebugOptions.instance.Animation.Debug.getValue() && this.hasActiveModel()) {
    int var26 = (int)IsoUtils.XToScreenExact(this.x, this.y, this.z, 0);
    int var40 = (int)IsoUtils.YToScreenExact(this.x, this.y, this.z, 0);
            TextManager.instance.DrawString(var26, var40, this.getAnimationDebug());
         }

         if (this.getIsNPC() && this.GameCharacterAIBrain != nullptr) {
            this.GameCharacterAIBrain.renderlast();
         }
      }
   }

    bool renderTextureInsteadOfModel(float var1, float var2) {
    return false;
   }

    void drawDirectionLine(Vector2 var1, float var2, float var3, float var4, float var5) {
    float var6 = this.x + var1.x * var2;
    float var7 = this.y + var1.y * var2;
    float var8 = IsoUtils.XToScreenExact(this.x, this.y, this.z, 0);
    float var9 = IsoUtils.YToScreenExact(this.x, this.y, this.z, 0);
    float var10 = IsoUtils.XToScreenExact(var6, var7, this.z, 0);
    float var11 = IsoUtils.YToScreenExact(var6, var7, this.z, 0);
      LineDrawer.drawLine(var8, var9, var10, var11, var3, var4, var5, 0.5F, 1);
   }

    void drawDebugTextBelow(const std::string& var1) {
    int var2 = TextManager.instance.MeasureStringX(UIFont.Small, var1) + 32;
    int var3 = TextManager.instance.getFontHeight(UIFont.Small);
    int var4 = (int)Math.ceil(var3 * 1.25);
    float var5 = IsoUtils.XToScreenExact(this.getX() + 0.25F, this.getY() + 0.25F, this.getZ(), 0);
    float var6 = IsoUtils.YToScreenExact(this.getX() + 0.25F, this.getY() + 0.25F, this.getZ(), 0);
      SpriteRenderer.instance.renderi(nullptr, (int)(var5 - var2 / 2), (int)(var6 - (var4 - var3) / 2), var2, var4, 0.0F, 0.0F, 0.0F, 0.5F, nullptr);
      TextManager.instance.DrawStringCentre(UIFont.Small, var5, var6, var1, 1.0, 1.0, 1.0, 1.0);
   }

    Radio getEquipedRadio() {
      return this.equipedRadio;
   }

    void radioEquipedCheck() {
      if (this.leftHandItem != this.leftHandCache) {
         this.leftHandCache = this.leftHandItem;
         if (this.leftHandItem != nullptr && (this.equipedRadio == nullptr || this.equipedRadio != this.rightHandItem) && this.dynamic_cast<Radio*>(leftHandItem) != nullptr) {
            this.equipedRadio = (Radio)this.leftHandItem;
         } else if (this.equipedRadio != nullptr && this.equipedRadio != this.rightHandItem) {
            if (this.equipedRadio.getDeviceData() != nullptr) {
               this.equipedRadio.getDeviceData().cleanSoundsAndEmitter();
            }

            this.equipedRadio = nullptr;
         }
      }

      if (this.rightHandItem != this.rightHandCache) {
         this.rightHandCache = this.rightHandItem;
         if (this.rightHandItem != nullptr && this.dynamic_cast<Radio*>(rightHandItem) != nullptr) {
            this.equipedRadio = (Radio)this.rightHandItem;
         } else if (this.equipedRadio != nullptr && this.equipedRadio != this.leftHandItem) {
            if (this.equipedRadio.getDeviceData() != nullptr) {
               this.equipedRadio.getDeviceData().cleanSoundsAndEmitter();
            }

            this.equipedRadio = nullptr;
         }
      }
   }

    void debugAim() {
      if (this == IsoPlayer.getInstance()) {
    IsoPlayer var1 = (IsoPlayer)this;
         if (var1.IsAiming()) {
    HandWeapon var2 = (HandWeapon)Type.tryCastTo(this.getPrimaryHandItem(), HandWeapon.class);
            if (var2 == nullptr) {
               var2 = var1.bareHands;
            }

    float var3 = var2.getMaxRange(var1) * var2.getRangeMod(var1);
    float var4 = this.getLookAngleRadians();
            LineDrawer.drawDirectionLine(this.x, this.y, this.z, var3, var4, 1.0F, 1.0F, 1.0F, 0.5F, 1);
    float var5 = var2.getMinAngle();
            var5 -= var2.getAimingPerkMinAngleModifier() * (this.getPerkLevel(Perks.Aiming) / 2.0F);
            LineDrawer.drawDotLines(this.x, this.y, this.z, var3, var4, var5, 1.0F, 1.0F, 1.0F, 0.5F, 1);
    float var6 = var2.getMinRange();
            LineDrawer.drawArc(this.x, this.y, this.z, var6, var4, var5, 6, 1.0F, 1.0F, 1.0F, 0.5F);
            if (var6 != var3) {
               LineDrawer.drawArc(this.x, this.y, this.z, var3, var4, var5, 6, 1.0F, 1.0F, 1.0F, 0.5F);
            }

    float var7 = PZMath.min(var3 + 1.0F, 2.0F);
            LineDrawer.drawArc(this.x, this.y, this.z, var7, var4, var5, 6, 0.75F, 0.75F, 0.75F, 0.5F);
    float var8 = Core.getInstance().getIgnoreProneZombieRange();
            if (var8 > 0.0F) {
               LineDrawer.drawArc(this.x, this.y, this.z, var8, var4, 0.0F, 12, 0.0F, 0.0F, 1.0F, 0.25F);
               LineDrawer.drawDotLines(this.x, this.y, this.z, var8, var4, 0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 1);
            }

    AttackVars var9 = std::make_shared<AttackVars>();
    std::vector var10 = new std::vector();
            SwipeStatePlayer.instance().CalcAttackVars((IsoLivingCharacter)this, var9);
            SwipeStatePlayer.instance().CalcHitList(this, false, var9, var10);
            if (var9.targetOnGround.getMovingObject() != nullptr) {
    HitInfo var11 = (HitInfo)var9.targetsProne.get(0);
               LineDrawer.DrawIsoCircle(var11.x, var11.y, var11.z, 0.1F, 8, 1.0F, 1.0F, 0.0F, 1.0F);
            } else if (var9.targetsStanding.size() > 0) {
    HitInfo var30 = (HitInfo)var9.targetsStanding.get(0);
               LineDrawer.DrawIsoCircle(var30.x, var30.y, var30.z, 0.1F, 8, 1.0F, 1.0F, 0.0F, 1.0F);
            }

            for (int var31 = 0; var31 < var10.size(); var31++) {
    HitInfo var12 = (HitInfo)var10.get(var31);
    IsoMovingObject var13 = var12.getObject();
               if (var13 != nullptr) {
    int var14 = var12.chance;
    float var15 = 1.0F - var14 / 100.0F;
    float var16 = 1.0F - var15;
    float var17 = Math.max(0.2F, var14 / 100.0F) / 2.0F;
    float var18 = IsoUtils.XToScreenExact(var13.x - var17, var13.y + var17, var13.z, 0);
    float var19 = IsoUtils.YToScreenExact(var13.x - var17, var13.y + var17, var13.z, 0);
    float var20 = IsoUtils.XToScreenExact(var13.x - var17, var13.y - var17, var13.z, 0);
    float var21 = IsoUtils.YToScreenExact(var13.x - var17, var13.y - var17, var13.z, 0);
    float var22 = IsoUtils.XToScreenExact(var13.x + var17, var13.y - var17, var13.z, 0);
    float var23 = IsoUtils.YToScreenExact(var13.x + var17, var13.y - var17, var13.z, 0);
    float var24 = IsoUtils.XToScreenExact(var13.x + var17, var13.y + var17, var13.z, 0);
    float var25 = IsoUtils.YToScreenExact(var13.x + var17, var13.y + var17, var13.z, 0);
                  SpriteRenderer.instance.renderPoly(var18, var19, var20, var21, var22, var23, var24, var25, var15, var16, 0.0F, 0.5F);
    UIFont var26 = UIFont.DebugConsole;
                  TextManager.instance.DrawStringCentre(var26, var24, var25, std::string.valueOf(var12.dot), 1.0, 1.0, 1.0, 1.0);
                  TextManager.instance
                     .DrawStringCentre(var26, var24, var25 + TextManager.instance.getFontHeight(var26), var12.chance + "%", 1.0, 1.0, 1.0, 1.0);
                  var15 = 1.0F;
                  var16 = 1.0F;
    float var27 = 1.0F;
    float var28 = PZMath.sqrt(var12.distSq);
                  if (var28 < var2.getMinRange()) {
                     var27 = 0.0F;
                     var15 = 0.0F;
                  }

                  TextManager.instance
                     .DrawStringCentre(var26, var24, var25 + TextManager.instance.getFontHeight(var26) * 2, "DIST: " + var28, var15, var16, var27, 1.0);
               }

               if (var12.window.getObject() != nullptr) {
                  var12.window.getObject().setHighlighted(true);
               }
            }
         }
      }
   }

    void debugTestDotSide() {
      if (this == IsoPlayer.getInstance()) {
    float var1 = this.getLookAngleRadians();
    float var2 = 2.0F;
    float var3 = 0.7F;
         LineDrawer.drawDotLines(this.x, this.y, this.z, var2, var1, var3, 1.0F, 1.0F, 1.0F, 0.5F, 1);
         var3 = -0.5F;
         LineDrawer.drawDotLines(this.x, this.y, this.z, var2, var1, var3, 1.0F, 1.0F, 1.0F, 0.5F, 1);
         LineDrawer.drawArc(this.x, this.y, this.z, var2, var1, -1.0F, 16, 1.0F, 1.0F, 1.0F, 0.5F);
    std::vector var4 = this.getCell().getZombieList();

         for (int var5 = 0; var5 < var4.size(); var5++) {
    IsoMovingObject var6 = (IsoMovingObject)var4.get(var5);
            if (this.DistToSquared(var6) < var2 * var2) {
               LineDrawer.DrawIsoCircle(var6.x, var6.y, var6.z, 0.3F, 1.0F, 1.0F, 1.0F, 1.0F);
    float var7 = 0.2F;
    float var8 = IsoUtils.XToScreenExact(var6.x + var7, var6.y + var7, var6.z, 0);
    float var9 = IsoUtils.YToScreenExact(var6.x + var7, var6.y + var7, var6.z, 0);
    UIFont var10 = UIFont.DebugConsole;
    int var11 = TextManager.instance.getFontHeight(var10);
               TextManager.instance.DrawStringCentre(var10, var8, var9 + var11, "SIDE: " + this.testDotSide(var6), 1.0, 1.0, 1.0, 1.0);
    Vector2 var12 = this.getLookVector(tempo2);
    Vector2 var13 = tempo.set(var6.x - this.x, var6.y - this.y);
               var13.normalize();
    float var14 = PZMath.wrap(var13.getDirection() - var12.getDirection(), 0.0F, (float) (Math.PI * 2));
               TextManager.instance.DrawStringCentre(var10, var8, var9 + var11 * 2, "ANGLE (0-360): " + PZMath.radToDeg(var14), 1.0, 1.0, 1.0, 1.0);
               var14 = (float)Math.acos(this.getDotWithForwardDirection(var6.x, var6.y));
               TextManager.instance.DrawStringCentre(var10, var8, var9 + var11 * 3, "ANGLE (0-180): " + PZMath.radToDeg(var14), 1.0, 1.0, 1.0, 1.0);
            }
         }
      }
   }

    void debugVision() {
      if (this == IsoPlayer.getInstance()) {
    float var1 = LightingJNI.calculateVisionCone(this);
         LineDrawer.drawDotLines(this.x, this.y, this.z, GameTime.getInstance().getViewDist(), this.getLookAngleRadians(), -var1, 1.0F, 1.0F, 1.0F, 0.5F, 1);
         LineDrawer.drawArc(this.x, this.y, this.z, GameTime.getInstance().getViewDist(), this.getLookAngleRadians(), -var1, 16, 1.0F, 1.0F, 1.0F, 0.5F);
    float var2 = 3.5F - this.stats.getFatigue();
         LineDrawer.drawArc(this.x, this.y, this.z, var2, this.getLookAngleRadians(), -1.0F, 32, 1.0F, 1.0F, 1.0F, 0.5F);
      }
   }

    void setDefaultState() {
      this.stateMachine.changeState(this.defaultState, nullptr);
   }

    void SetOnFire() {
      if (!this.OnFire) {
         this.setOnFire(true);
    float var1 = Core.TileScale;
         this.AttachAnim(
            "Fire",
            "01",
            4,
            IsoFireManager.FireAnimDelay,
            (int)(-(this.offsetX + 1.0F * var1)) + (8 - Rand.Next(16)),
            (int)(-(this.offsetY + -89.0F * var1)) + (int)((10 + Rand.Next(20)) * var1),
            true,
            0,
            false,
            0.7F,
            IsoFireManager.FireTintMod
         );
         IsoFireManager.AddBurningCharacter(this);
    int var2 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Hand_L), BodyPartType.ToIndex(BodyPartType.MAX));
         if (dynamic_cast<IsoPlayer*>(this) != nullptr) {
            ((BodyPart)this.getBodyDamage().getBodyParts().get(var2)).setBurned();
         }

         if (var1 == 2.0F) {
    int var3 = this.AttachedAnimSprite.size() - 1;
            ((IsoSpriteInstance)this.AttachedAnimSprite.get(var3)).setScale(var1, var1);
         }

         if (!this.getEmitter().isPlaying("BurningFlesh")) {
            this.getEmitter().playSoundImpl("BurningFlesh", this);
         }
      }
   }

    void StopBurning() {
      if (this.OnFire) {
         IsoFireManager.RemoveBurningCharacter(this);
         this.setOnFire(false);
         if (this.AttachedAnimSprite != nullptr) {
            this.AttachedAnimSprite.clear();
         }

         this.getEmitter().stopOrTriggerSoundByName("BurningFlesh");
      }
   }

    void sendStopBurning() {
      if (GameClient.bClient) {
         if (dynamic_cast<IsoPlayer*>(this) != nullptr var1) {
            if (var1.isLocalPlayer()) {
               this.StopBurning();
            } else {
               GameClient.sendStopFire(var1);
            }
         }

         if (this.isZombie()) {
    IsoZombie var2 = (IsoZombie)this;
            GameClient.sendStopFire(var2);
         }
      }
   }

    void SpreadFireMP() {
      if (this.OnFire && GameServer.bServer && SandboxOptions.instance.FireSpread.getValue()) {
    IsoGridSquare var1 = ServerMap.instance.getGridSquare((int)this.x, (int)this.y, (int)this.z);
         if (var1 != nullptr && !var1.getProperties().Is(IsoFlagType.burning) && Rand.Next(Rand.AdjustForFramerate(3000)) < this.FireSpreadProbability) {
            IsoFireManager.StartFire(this.getCell(), var1, false, 80);
         }
      }
   }

    void SpreadFire() {
      if (this.OnFire && !GameServer.bServer && !GameClient.bClient && SandboxOptions.instance.FireSpread.getValue()) {
         if (this.square != nullptr
            && !this.square.getProperties().Is(IsoFlagType.burning)
            && Rand.Next(Rand.AdjustForFramerate(3000)) < this.FireSpreadProbability) {
            IsoFireManager.StartFire(this.getCell(), this.square, false, 80);
         }
      }
   }

    void Throw(HandWeapon var1) {
      if (dynamic_cast<IsoPlayer*>(this) != nullptr && ((IsoPlayer)this).getJoypadBind() != -1) {
    Vector2 var2 = tempo.set(this.m_forwardDirection);
         var2.setLength(var1.getMaxRange());
         this.attackTargetSquare = this.getCell().getGridSquare(this.getX() + var2.getX(), this.getY() + var2.getY(), this.getZ());
         if (this.attackTargetSquare == nullptr) {
            this.attackTargetSquare = this.getCell().getGridSquare(this.getX() + var2.getX(), this.getY() + var2.getY(), 0.0);
         }
      }

    float var5 = this.attackTargetSquare.getX() - this.getX();
      if (var5 > 0.0F) {
         if (this.attackTargetSquare.getX() - this.getX() > var1.getMaxRange()) {
            var5 = var1.getMaxRange();
         }
      } else if (this.attackTargetSquare.getX() - this.getX() < -var1.getMaxRange()) {
         var5 = -var1.getMaxRange();
      }

    float var3 = this.attackTargetSquare.getY() - this.getY();
      if (var3 > 0.0F) {
         if (this.attackTargetSquare.getY() - this.getY() > var1.getMaxRange()) {
            var3 = var1.getMaxRange();
         }
      } else if (this.attackTargetSquare.getY() - this.getY() < -var1.getMaxRange()) {
         var3 = -var1.getMaxRange();
      }

      if (var1.getPhysicsObject() == "Ball")) {
    std::make_shared<IsoBall>();
      } else {
    std::make_shared<IsoMolotovCocktail>();
      }

      if (dynamic_cast<IsoPlayer*>(this) != nullptr) {
         ((IsoPlayer)this).setAttackAnimThrowTimer(0L);
      }
   }

    void serverRemoveItemFromZombie(const std::string& var1) {
      if (GameServer.bServer) {
    IsoZombie var2 = (IsoZombie)Type.tryCastTo(this, IsoZombie.class);
         this.getItemVisuals(tempItemVisuals);

         for (int var3 = 0; var3 < tempItemVisuals.size(); var3++) {
    ItemVisual var4 = (ItemVisual)tempItemVisuals.get(var3);
    Item var5 = var4.getScriptItem();
            if (var5 != nullptr && var5.name == var1)) {
               tempItemVisuals.remove(var3--);
               var2.itemVisuals.clear();
               var2.itemVisuals.addAll(tempItemVisuals);
            }
         }
      }
   }

    bool helmetFall(bool var1) {
      return this.helmetFall(var1, nullptr);
   }

    bool helmetFall(bool var1, const std::string& var2) {
    IsoPlayer var3 = (IsoPlayer)Type.tryCastTo(this, IsoPlayer.class);
    bool var4 = false;
    InventoryItem var5 = nullptr;
    IsoZombie var6 = (IsoZombie)Type.tryCastTo(this, IsoZombie.class);
      if (var6 != nullptr && !var6.isUsingWornItems()) {
         this.getItemVisuals(tempItemVisuals);

         for (int var13 = 0; var13 < tempItemVisuals.size(); var13++) {
    ItemVisual var14 = (ItemVisual)tempItemVisuals.get(var13);
    Item var15 = var14.getScriptItem();
            if (var15 != nullptr && var15.getType() == zombie.scripting.objects.Item.Type.Clothing && var15.getChanceToFall() > 0) {
    int var16 = var15.getChanceToFall();
               if (var1) {
                  var16 += 40;
               }

               if (var15.name == var2)) {
                  var16 = 100;
               }

               if (Rand.Next(100) > var16) {
    InventoryItem var17 = InventoryItemFactory.CreateItem(var15.getFullName());
                  if (var17 != nullptr) {
                     if (var17.getVisual() != nullptr) {
                        var17.getVisual().copyFrom(var14);
                        var17.synchWithVisual();
                     }

                     IsoFallingClothing var18 = std::make_shared<IsoFallingClothing>(
                        this.getCell(), this.getX(), this.getY(), PZMath.min(this.getZ() + 0.4F, (int)this.getZ() + 0.95F), 0.2F, 0.2F, var17
                     );
                     if (!StringUtils.isNullOrEmpty(var2)) {
                        var18.addWorldItem = false;
                     }

                     tempItemVisuals.remove(var13--);
                     var6.itemVisuals.clear();
                     var6.itemVisuals.addAll(tempItemVisuals);
                     this.resetModelNextFrame();
                     this.onWornItemsChanged();
                     var4 = true;
                     var5 = var17;
                  }
               }
            }
         }
      } else if (this.getWornItems() != nullptr && !this.getWornItems().empty()) {
         for (int var7 = 0; var7 < this.getWornItems().size(); var7++) {
    WornItem var8 = this.getWornItems().get(var7);
    InventoryItem var9 = var8.getItem();
    std::string var10 = var8.getLocation();
            if (dynamic_cast<Clothing*>(var9) != nullptr) {
    int var11 = ((Clothing)var9).getChanceToFall();
               if (var1) {
                  var11 += 40;
               }

               if (var9.getType() == var2)) {
                  var11 = 100;
               }

               if (((Clothing)var9).getChanceToFall() > 0 && Rand.Next(100) <= var11) {
                  IsoFallingClothing var12 = std::make_shared<IsoFallingClothing>(
                     this.getCell(),
                     this.getX(),
                     this.getY(),
                     PZMath.min(this.getZ() + 0.4F, (int)this.getZ() + 0.95F),
                     Rand.Next(-0.2F, 0.2F),
                     Rand.Next(-0.2F, 0.2F),
                     var9
                  );
                  if (!StringUtils.isNullOrEmpty(var2)) {
                     var12.addWorldItem = false;
                  }

                  this.getInventory().Remove(var9);
                  this.getWornItems().remove(var9);
                  var5 = var9;
                  this.resetModelNextFrame();
                  this.onWornItemsChanged();
                  var4 = true;
                  if (GameClient.bClient && var3 != nullptr && var3.isLocalPlayer() && StringUtils.isNullOrEmpty(var2)) {
                     GameClient.instance.sendClothing(var3, var10, nullptr);
                  }
               }
            }
         }
      }

      if (var4 && GameClient.bClient && StringUtils.isNullOrEmpty(var2) && IsoPlayer.getInstance().isLocalPlayer()) {
         GameClient.sendZombieHelmetFall(IsoPlayer.getInstance(), this, var5);
      }

      if (var4 && var3 != nullptr && var3.isLocalPlayer()) {
         LuaEventManager.triggerEvent("OnClothingUpdated", this);
      }

      if (var4 && this.isZombie()) {
         PersistentOutfits.instance.setFallenHat(this, true);
      }

    return var4;
   }

    void smashCarWindow(VehiclePart var1) {
    std::unordered_map var2 = this.getStateMachineParams(SmashWindowState.instance());
      var2.clear();
      var2.put(0, var1.getWindow());
      var2.put(1, var1.getVehicle());
      var2.put(2, var1);
      this.actionContext.reportEvent("EventSmashWindow");
   }

    void smashWindow(IsoWindow var1) {
      if (!var1.isInvincible()) {
    std::unordered_map var2 = this.getStateMachineParams(SmashWindowState.instance());
         var2.clear();
         var2.put(0, var1);
         this.actionContext.reportEvent("EventSmashWindow");
      }
   }

    void openWindow(IsoWindow var1) {
      if (!var1.isInvincible()) {
         OpenWindowState.instance().setParams(this, var1);
         this.actionContext.reportEvent("EventOpenWindow");
      }
   }

    void closeWindow(IsoWindow var1) {
      if (!var1.isInvincible()) {
    std::unordered_map var2 = this.getStateMachineParams(CloseWindowState.instance());
         var2.clear();
         var2.put(0, var1);
         this.actionContext.reportEvent("EventCloseWindow");
      }
   }

    void climbThroughWindow(IsoWindow var1) {
      if (var1.canClimbThrough(this)) {
    float var2 = this.x - (int)this.x;
    float var3 = this.y - (int)this.y;
    uint8_t var4 = 0;
    uint8_t var5 = 0;
         if (var1.getX() > this.x && !var1.north) {
            var4 = -1;
         }

         if (var1.getY() > this.y && var1.north) {
            var5 = -1;
         }

         this.x = var1.getX() + var2 + var4;
         this.y = var1.getY() + var3 + var5;
         ClimbThroughWindowState.instance().setParams(this, var1);
         this.actionContext.reportEvent("EventClimbWindow");
      }
   }

    void climbThroughWindow(IsoWindow var1, int var2) {
      if (var1.canClimbThrough(this)) {
         ClimbThroughWindowState.instance().setParams(this, var1);
         this.actionContext.reportEvent("EventClimbWindow");
      }
   }

    bool isClosingWindow(IsoWindow var1) {
      if (var1 == nullptr) {
    return false;
      } else {
         return !this.isCurrentState(CloseWindowState.instance()) ? false : CloseWindowState.instance().getWindow(this) == var1;
      }
   }

    bool isClimbingThroughWindow(IsoWindow var1) {
      if (var1 == nullptr) {
    return false;
      } else if (!this.isCurrentState(ClimbThroughWindowState.instance())) {
    return false;
      } else {
         return !this.getVariableBoolean("BlockWindow") ? false : ClimbThroughWindowState.instance().getWindow(this) == var1;
      }
   }

    void climbThroughWindowFrame(IsoObject var1) {
      if (IsoWindowFrame.canClimbThrough(var1, this)) {
         ClimbThroughWindowState.instance().setParams(this, var1);
         this.actionContext.reportEvent("EventClimbWindow");
      }
   }

    void climbSheetRope() {
      if (this.canClimbSheetRope(this.current)) {
    std::unordered_map var1 = this.getStateMachineParams(ClimbSheetRopeState.instance());
         var1.clear();
         this.actionContext.reportEvent("EventClimbRope");
      }
   }

    void climbDownSheetRope() {
      if (this.canClimbDownSheetRope(this.current)) {
         this.dropHeavyItems();
    std::unordered_map var1 = this.getStateMachineParams(ClimbDownSheetRopeState.instance());
         var1.clear();
         this.actionContext.reportEvent("EventClimbDownRope");
      }
   }

    bool canClimbSheetRope(IsoGridSquare var1) {
      if (var1 == nullptr) {
    return false;
      } else {
    int var2 = var1.getZ();

         while (var1 != nullptr) {
            if (!IsoWindow.isSheetRopeHere(var1)) {
    return false;
            }

            if (!IsoWindow.canClimbHere(var1)) {
    return false;
            }

            if (var1.TreatAsSolidFloor() && var1.getZ() > var2) {
    return false;
            }

            if (IsoWindow.isTopOfSheetRopeHere(var1)) {
    return true;
            }

            var1 = this.getCell().getGridSquare(var1.getX(), var1.getY(), var1.getZ() + 1);
         }

    return false;
      }
   }

    bool canClimbDownSheetRopeInCurrentSquare() {
      return this.canClimbDownSheetRope(this.current);
   }

    bool canClimbDownSheetRope(IsoGridSquare var1) {
      if (var1 == nullptr) {
    return false;
      } else {
    int var2 = var1.getZ();

         while (var1 != nullptr) {
            if (!IsoWindow.isSheetRopeHere(var1)) {
    return false;
            }

            if (!IsoWindow.canClimbHere(var1)) {
    return false;
            }

            if (var1.TreatAsSolidFloor()) {
               return var1.getZ() < var2;
            }

            var1 = this.getCell().getGridSquare(var1.getX(), var1.getY(), var1.getZ() - 1);
         }

    return false;
      }
   }

    void climbThroughWindow(IsoThumpable var1) {
      if (var1.canClimbThrough(this)) {
    float var2 = this.x - (int)this.x;
    float var3 = this.y - (int)this.y;
    uint8_t var4 = 0;
    uint8_t var5 = 0;
         if (var1.getX() > this.x && !var1.north) {
            var4 = -1;
         }

         if (var1.getY() > this.y && var1.north) {
            var5 = -1;
         }

         this.x = var1.getX() + var2 + var4;
         this.y = var1.getY() + var3 + var5;
         ClimbThroughWindowState.instance().setParams(this, var1);
         this.actionContext.reportEvent("EventClimbWindow");
      }
   }

    void climbThroughWindow(IsoThumpable var1, int var2) {
      if (var1.canClimbThrough(this)) {
         ClimbThroughWindowState.instance().setParams(this, var1);
         this.actionContext.reportEvent("EventClimbWindow");
      }
   }

    void climbOverFence(IsoDirections var1) {
      if (this.current != nullptr) {
    IsoGridSquare var2 = this.current.nav[var1.index()];
         if (IsoWindow.canClimbThroughHelper(this, this.current, var2, var1 == IsoDirections.N || var1 == IsoDirections.S)) {
            ClimbOverFenceState.instance().setParams(this, var1);
            this.actionContext.reportEvent("EventClimbFence");
         }
      }
   }

    bool isAboveTopOfStairs() {
      if (this.z != 0.0F && !(this.z - (int)this.z > 0.01) && (this.current == nullptr || !this.current.TreatAsSolidFloor())) {
    IsoGridSquare var1 = this.getCell().getGridSquare(this.x, this.y, this.z - 1.0F);
         return var1 != nullptr && (var1.Has(IsoObjectType.stairsTN) || var1.Has(IsoObjectType.stairsTW));
      } else {
    return false;
      }
   }

    void preupdate() {
      super.preupdate();
      if (!this.m_bDebugVariablesRegistered && DebugOptions.instance.char.Debug.RegisterDebugVariables.getValue()) {
         this.registerDebugGameVariables();
      }

      this.updateAnimationRecorderState();
      if (this.isAnimationRecorderActive()) {
    int var1 = IsoWorld.instance.getFrameNo();
         this.m_animationRecorder.beginLine(var1);
      }

      if (GameServer.bServer) {
         this.getXp().update();
      }
   }

    void setTeleport(NetworkTeleport var1) {
      this.teleport = var1;
   }

    NetworkTeleport getTeleport() {
      return this.teleport;
   }

    bool isTeleporting() {
      return this.teleport != nullptr;
   }

    void update() {
      s_performance.update.invokeAndMeasure(this, IsoGameCharacter::updateInternal);
   }

    void updateInternal() {
      if (this.current != nullptr) {
         if (this.teleport != nullptr) {
            this.teleport.process(IsoPlayer.getPlayerIndex());
         }

         this.updateAlpha();
         if (this.isNPC) {
            if (this.GameCharacterAIBrain == nullptr) {
               this.GameCharacterAIBrain = std::make_shared<GameCharacterAIBrain>(this);
            }

            this.GameCharacterAIBrain.update();
         }

         if (this.sprite != nullptr) {
            this.legsSprite = this.sprite;
         }

         if (!this.isDead() || this.current != nullptr && this.current.getMovingObjects().contains(this)) {
            if (!GameClient.bClient
               && !this.m_invisible
               && this.getCurrentSquare().getTrapPositionX() > -1
               && this.getCurrentSquare().getTrapPositionY() > -1
               && this.getCurrentSquare().getTrapPositionZ() > -1) {
               this.getCurrentSquare().explodeTrap();
            }

            if (this.getBodyDamage() != nullptr && this.getCurrentBuilding() != nullptr && this.getCurrentBuilding().isToxic()) {
    float var1 = GameTime.getInstance().getMultiplier() / 1.6F;
               if (this.getStats().getFatigue() < 1.0F) {
                  this.getStats().setFatigue(this.getStats().getFatigue() + 1.0E-4F * var1);
               }

               if (this.getStats().getFatigue() > 0.8) {
                  this.getBodyDamage().getBodyPart(BodyPartType.Head).ReduceHealth(0.1F * var1);
               }

               this.getBodyDamage().getBodyPart(BodyPartType.Torso_Upper).ReduceHealth(0.1F * var1);
            }

            if (this.lungeFallTimer > 0.0F) {
               this.lungeFallTimer = this.lungeFallTimer - GameTime.getInstance().getMultiplier() / 1.6F;
            }

            if (this.getMeleeDelay() > 0.0F) {
               this.setMeleeDelay(this.getMeleeDelay() - 0.625F * GameTime.getInstance().getMultiplier());
            }

            if (this.getRecoilDelay() > 0.0F) {
               this.setRecoilDelay(this.getRecoilDelay() - 0.625F * GameTime.getInstance().getMultiplier());
            }

            this.sx = 0.0F;
            this.sy = 0.0F;
            if (this.current.getRoom() != nullptr && this.current.getRoom().building.def.bAlarmed && (!this.isZombie() || Core.bTutorial) && !GameClient.bClient) {
    bool var5 = false;
               if (dynamic_cast<IsoPlayer*>(this) != nullptr && (((IsoPlayer)this).isInvisible() || ((IsoPlayer)this).isGhostMode())) {
                  var5 = true;
               }

               if (!var5) {
                  AmbientStreamManager.instance.doAlarm(this.current.getRoom().def);
               }
            }

            this.updateSeenVisibility();
            this.llx = this.getLx();
            this.lly = this.getLy();
            this.setLx(this.getX());
            this.setLy(this.getY());
            this.setLz(this.getZ());
            this.updateBeardAndHair();
            this.updateFalling();
            if (this.descriptor != nullptr) {
               this.descriptor.Instance = this;
            }

            if (!this.isZombie()) {
               if (this.Traits.Agoraphobic.isSet() && !this.getCurrentSquare().isInARoom()) {
                  this.stats.Panic = this.stats.Panic + 0.5F * (GameTime.getInstance().getMultiplier() / 1.6F);
               }

               if (this.Traits.Claustophobic.isSet() && this.getCurrentSquare().isInARoom()) {
    int var6 = this.getCurrentSquare().getRoomSize();
                  if (var6 > 0) {
    float var2 = 1.0F;
                     var2 = 1.0F - var6 / 70.0F;
                     if (var2 < 0.0F) {
                        var2 = 0.0F;
                     }

    float var3 = 0.6F * var2 * (GameTime.getInstance().getMultiplier() / 1.6F);
                     if (var3 > 0.6F) {
                        var3 = 0.6F;
                     }

                     this.stats.Panic += var3;
                  }
               }

               if (this.Moodles != nullptr) {
                  this.Moodles.Update();
               }

               if (this.Asleep) {
                  this.BetaEffect = 0.0F;
                  this.SleepingTabletEffect = 0.0F;
                  this.StopAllActionQueue();
               }

               if (this.BetaEffect > 0.0F) {
                  this.BetaEffect = this.BetaEffect - GameTime.getInstance().getMultiplier() / 1.6F;
                  this.stats.Panic = this.stats.Panic - 0.6F * (GameTime.getInstance().getMultiplier() / 1.6F);
                  if (this.stats.Panic < 0.0F) {
                     this.stats.Panic = 0.0F;
                  }
               } else {
                  this.BetaDelta = 0.0F;
               }

               if (this.DepressFirstTakeTime > 0.0F || this.DepressEffect > 0.0F) {
                  this.DepressFirstTakeTime = this.DepressFirstTakeTime - GameTime.getInstance().getMultiplier() / 1.6F;
                  if (this.DepressFirstTakeTime < 0.0F) {
                     this.DepressFirstTakeTime = -1.0F;
                     this.DepressEffect = this.DepressEffect - GameTime.getInstance().getMultiplier() / 1.6F;
                     this.getBodyDamage()
                        .setUnhappynessLevel(this.getBodyDamage().getUnhappynessLevel() - 0.03F * (GameTime.getInstance().getMultiplier() / 1.6F));
                     if (this.getBodyDamage().getUnhappynessLevel() < 0.0F) {
                        this.getBodyDamage().setUnhappynessLevel(0.0F);
                     }
                  }
               }

               if (this.DepressEffect < 0.0F) {
                  this.DepressEffect = 0.0F;
               }

               if (this.SleepingTabletEffect > 0.0F) {
                  this.SleepingTabletEffect = this.SleepingTabletEffect - GameTime.getInstance().getMultiplier() / 1.6F;
                  this.stats.fatigue = this.stats.fatigue + 0.0016666667F * this.SleepingTabletDelta * (GameTime.getInstance().getMultiplier() / 1.6F);
               } else {
                  this.SleepingTabletDelta = 0.0F;
               }

    int var7 = this.Moodles.getMoodleLevel(MoodleType.Panic);
               if (var7 == 2) {
                  this.stats.Sanity -= 3.2E-7F;
               } else if (var7 == 3) {
                  this.stats.Sanity -= 4.8000004E-7F;
               } else if (var7 == 4) {
                  this.stats.Sanity -= 8.0E-7F;
               } else if (var7 == 0) {
                  this.stats.Sanity += 1.0E-7F;
               }

    int var11 = this.Moodles.getMoodleLevel(MoodleType.Tired);
               if (var11 == 4) {
                  this.stats.Sanity -= 2.0E-6F;
               }

               if (this.stats.Sanity < 0.0F) {
                  this.stats.Sanity = 0.0F;
               }

               if (this.stats.Sanity > 1.0F) {
                  this.stats.Sanity = 1.0F;
               }
            }

            if (!this.CharacterActions.empty()) {
    BaseAction var8 = this.CharacterActions.get(0);
    bool var12 = var8.valid();
               if (var12 && !var8.bStarted) {
                  var8.waitToStart();
               } else if (var12 && !var8.finished() && !var8.forceComplete && !var8.forceStop) {
                  var8.update();
               }

               if (!var12 || var8.finished() || var8.forceComplete || var8.forceStop) {
                  if (var8.finished() || var8.forceComplete) {
                     var8.perform();
                     var12 = true;
                  }

                  if (var8.finished() && !var8.loopAction || var8.forceComplete || var8.forceStop || !var12) {
                     if (var8.bStarted && (var8.forceStop || !var12)) {
                        var8.stop();
                     }

                     this.CharacterActions.removeElement(var8);
                     if (this == IsoPlayer.players[0] || this == IsoPlayer.players[1] || this == IsoPlayer.players[2] || this == IsoPlayer.players[3]) {
                        UIManager.getProgressBar(((IsoPlayer)this).getPlayerNum()).setValue(0.0F);
                     }
                  }
               }

               for (int var14 = 0; var14 < this.EnemyList.size(); var14++) {
    IsoGameCharacter var4 = this.EnemyList.get(var14);
                  if (var4.isDead()) {
                     this.EnemyList.remove(var4);
                     var14--;
                  }
               }
            }

            if (SystemDisabler.doCharacterStats && this.BodyDamage != nullptr) {
               this.BodyDamage.Update();
               this.updateBandages();
            }

            if (this == IsoPlayer.getInstance()) {
               if (this.leftHandItem != nullptr && this.leftHandItem.getUses() <= 0) {
                  this.leftHandItem = nullptr;
               }

               if (this.rightHandItem != nullptr && this.rightHandItem.getUses() <= 0) {
                  this.rightHandItem = nullptr;
               }
            }

            if (SystemDisabler.doCharacterStats) {
               this.calculateStats();
            }

            this.moveForwardVec.x = 0.0F;
            this.moveForwardVec.y = 0.0F;
            if (!this.Asleep || !(dynamic_cast<IsoPlayer*>(this) != nullptr)) {
               this.setLx(this.getX());
               this.setLy(this.getY());
               this.setLz(this.getZ());
               this.square = this.getCurrentSquare();
               if (this.sprite != nullptr) {
                  if (!this.bUseParts) {
                     this.sprite.update(this.def);
                  } else {
                     this.legsSprite.update(this.def);
                  }
               }

               this.setStateEventDelayTimer(this.getStateEventDelayTimer() - GameTime.getInstance().getMultiplier() / 1.6F);
            }

            this.stateMachine.update();
            if (this.isZombie() && VirtualZombieManager.instance.isReused((IsoZombie)this)) {
               DebugLog.log(DebugType.Zombie, "Zombie added to ReusableZombies after stateMachine.update - RETURNING " + this);
            } else {
               if (dynamic_cast<IsoPlayer*>(this) != nullptr) {
                  this.ensureOnTile();
               }

               if ((dynamic_cast<IsoPlayer*>(this) != nullptr || dynamic_cast<IsoSurvivor*>(this) != nullptr)
                  && this.RemoteID == -1
                  && dynamic_cast<IsoPlayer*>(this) != nullptr
                  && ((IsoPlayer)this).isLocalPlayer()) {
                  RainManager.SetPlayerLocation(((IsoPlayer)this).getPlayerNum(), this.getCurrentSquare());
               }

               this.FireCheck();
               this.SpreadFire();
               this.ReduceHealthWhenBurning();
               this.updateTextObjects();
               if (this.stateMachine.getCurrent() == StaggerBackState.instance()) {
                  if (this.getStateEventDelayTimer() > 20.0F) {
                     this.BloodImpactX = this.getX();
                     this.BloodImpactY = this.getY();
                     this.BloodImpactZ = this.getZ();
                  }
               } else {
                  this.BloodImpactX = this.getX();
                  this.BloodImpactY = this.getY();
                  this.BloodImpactZ = this.getZ();
               }

               if (!this.isZombie()) {
                  this.recursiveItemUpdater(this.inventory);
               }

               this.LastZombieKills = this.ZombieKills;
               if (this.AttachedAnimSprite != nullptr) {
    int var9 = this.AttachedAnimSprite.size();

                  for (int var13 = 0; var13 < var9; var13++) {
    IsoSpriteInstance var15 = (IsoSpriteInstance)this.AttachedAnimSprite.get(var13);
    IsoSprite var16 = var15.parentSprite;
                     var15.update();
                     var15.Frame = var15.Frame + var15.AnimFrameIncrease * (GameTime.instance.getMultipliedSecondsSinceLastUpdate() * 60.0F);
                     if ((int)var15.Frame >= var16.CurrentAnim.Frames.size() && var16.Loop && var15.Looped) {
                        var15.Frame = 0.0F;
                     }
                  }
               }

               if (this.isGodMod()) {
                  this.getStats().setFatigue(0.0F);
                  this.getStats().setEndurance(1.0F);
                  this.getBodyDamage().setTemperature(37.0F);
                  this.getStats().setHunger(0.0F);
               }

               this.updateMovementMomentum();
               if (this.effectiveEdibleBuffTimer > 0.0F) {
                  this.effectiveEdibleBuffTimer = this.effectiveEdibleBuffTimer - GameTime.getInstance().getMultiplier() * 0.015F;
                  if (this.effectiveEdibleBuffTimer < 0.0F) {
                     this.effectiveEdibleBuffTimer = 0.0F;
                  }
               }

               if (!GameServer.bServer || GameClient.bClient) {
                  this.updateDirt();
               }
            }
         }
      }
   }

    void updateSeenVisibility() {
      for (int var1 = 0; var1 < IsoPlayer.numPlayers; var1++) {
         this.updateSeenVisibility(var1);
      }
   }

    void updateSeenVisibility(int var1) {
    IsoPlayer var2 = IsoPlayer.players[var1];
      if (var2 != nullptr) {
         this.IsVisibleToPlayer[var1] = this.TestIfSeen(var1);
         if (!this.IsVisibleToPlayer[var1]) {
            if (!(dynamic_cast<IsoPlayer*>(this) != nullptr)) {
               if (!var2.isSeeEveryone()) {
                  this.setTargetAlpha(var1, 0.0F);
               }
            }
         }
      }
   }

    void recursiveItemUpdater(ItemContainer var1) {
      for (int var2 = 0; var2 < var1.Items.size(); var2++) {
    InventoryItem var3 = (InventoryItem)var1.Items.get(var2);
         if (dynamic_cast<InventoryContainer*>(var3) != nullptr) {
            this.recursiveItemUpdater((InventoryContainer)var3);
         }

         if (dynamic_cast<IUpdater*>(var3) != nullptr) {
            var3.update();
         }
      }
   }

    void recursiveItemUpdater(InventoryContainer var1) {
      for (int var2 = 0; var2 < var1.getInventory().getItems().size(); var2++) {
    InventoryItem var3 = (InventoryItem)var1.getInventory().getItems().get(var2);
         if (dynamic_cast<InventoryContainer*>(var3) != nullptr) {
            this.recursiveItemUpdater((InventoryContainer)var3);
         }

         if (dynamic_cast<IUpdater*>(var3) != nullptr) {
            var3.update();
         }
      }
   }

    void updateDirt() {
      if (!this.isZombie() && this.getBodyDamage() != nullptr) {
    int var1 = 0;
         if (this.isRunning() && Rand.NextBool(Rand.AdjustForFramerate(3500))) {
            var1 = 1;
         }

         if (this.isSprinting() && Rand.NextBool(Rand.AdjustForFramerate(2500))) {
            var1 += Rand.Next(1, 3);
         }

         if (this.getBodyDamage().getTemperature() > 37.0F && Rand.NextBool(Rand.AdjustForFramerate(5000))) {
            var1++;
         }

         if (this.getBodyDamage().getTemperature() > 38.0F && Rand.NextBool(Rand.AdjustForFramerate(3000))) {
            var1++;
         }

    float var2 = this.square == nullptr ? 0.0F : this.square.getPuddlesInGround();
         if (this.isMoving() && var2 > 0.09F && Rand.NextBool(Rand.AdjustForFramerate(1500))) {
            var1++;
         }

         if (var1 > 0) {
            this.addDirt(nullptr, var1, true);
         }

    IsoPlayer var3 = (IsoPlayer)Type.tryCastTo(this, IsoPlayer.class);
         if (var3 != nullptr && var3.isPlayerMoving() || var3 == nullptr && this.isMoving()) {
            var1 = 0;
            if (var2 > 0.09F && Rand.NextBool(Rand.AdjustForFramerate(1500))) {
               var1++;
            }

            if (this.isInTrees() && Rand.NextBool(Rand.AdjustForFramerate(1500))) {
               var1++;
            }

            if (var1 > 0) {
               this.addDirt(nullptr, var1, false);
            }
         }
      }
   }

    void updateMovementMomentum() {
    float var1 = GameTime.instance.getTimeDelta();
      if (this.isPlayerMoving() && !this.isAiming()) {
    float var6 = this.m_momentumScalar * 0.55F;
         if (var6 >= 0.55F) {
            this.m_momentumScalar = 1.0F;
            return;
         }

    float var7 = var6 + var1;
    float var8 = var7 / 0.55F;
         this.m_momentumScalar = PZMath.clamp(var8, 0.0F, 1.0F);
      } else {
    float var2 = (1.0F - this.m_momentumScalar) * 0.25F;
         if (var2 >= 0.25F) {
            this.m_momentumScalar = 0.0F;
            return;
         }

    float var3 = var2 + var1;
    float var4 = var3 / 0.25F;
    float var5 = PZMath.clamp(var4, 0.0F, 1.0F);
         this.m_momentumScalar = 1.0F - var5;
      }
   }

    double getHoursSurvived() {
      return GameTime.instance.getWorldAgeHours();
   }

    void updateBeardAndHair() {
      if (!this.isZombie()) {
         if (!(dynamic_cast<IsoPlayer*>(this) != nullptr) || ((IsoPlayer)this).isLocalPlayer()) {
    float var1 = (float)this.getHoursSurvived();
            if (this.beardGrowTiming < 0.0F || this.beardGrowTiming > var1) {
               this.beardGrowTiming = var1;
            }

            if (this.hairGrowTiming < 0.0F || this.hairGrowTiming > var1) {
               this.hairGrowTiming = var1;
            }

            boolean var2 = !GameClient.bClient && !GameServer.bServer
               || ServerOptions.instance.SleepAllowed.getValue() && ServerOptions.instance.SleepNeeded.getValue();
    bool var3 = false;
            if ((this.isAsleep() || !var2) && var1 - this.beardGrowTiming > 120.0F) {
               this.beardGrowTiming = var1;
    BeardStyle var4 = BeardStyles.instance.FindStyle(((HumanVisual)this.getVisual()).getBeardModel());
    int var5 = 1;
               if (var4 != nullptr) {
                  var5 = var4.level;
               }

    std::vector var6 = BeardStyles.instance.getAllStyles();

               for (int var7 = 0; var7 < var6.size(); var7++) {
                  if (((BeardStyle)var6.get(var7)).growReference && ((BeardStyle)var6.get(var7)).level == var5 + 1) {
                     ((HumanVisual)this.getVisual()).setBeardModel(((BeardStyle)var6.get(var7)).name);
                     var3 = true;
                     break;
                  }
               }
            }

            if ((this.isAsleep() || !var2) && var1 - this.hairGrowTiming > 480.0F) {
               this.hairGrowTiming = var1;
    HairStyle var9 = HairStyles.instance.FindMaleStyle(((HumanVisual)this.getVisual()).getHairModel());
               if (this.isFemale()) {
                  var9 = HairStyles.instance.FindFemaleStyle(((HumanVisual)this.getVisual()).getHairModel());
               }

    int var10 = 1;
               if (var9 != nullptr) {
                  var10 = var9.level;
               }

    std::vector var11 = HairStyles.instance.m_MaleStyles;
               if (this.isFemale()) {
                  var11 = HairStyles.instance.m_FemaleStyles;
               }

               for (int var12 = 0; var12 < var11.size(); var12++) {
    HairStyle var8 = (HairStyle)var11.get(var12);
                  if (var8.growReference && var8.level == var10 + 1) {
                     ((HumanVisual)this.getVisual()).setHairModel(var8.name);
                     ((HumanVisual)this.getVisual()).setNonAttachedHair(nullptr);
                     var3 = true;
                     break;
                  }
               }
            }

            if (var3) {
               this.resetModelNextFrame();
               LuaEventManager.triggerEvent("OnClothingUpdated", this);
               if (GameClient.bClient) {
                  GameClient.instance.sendVisual((IsoPlayer)this);
               }
            }
         }
      }
   }

    void updateFalling() {
      if (dynamic_cast<IsoPlayer*>(this) != nullptr && !this.isClimbing()) {
         IsoRoofFixer.FixRoofsAt(this.current);
      }

      if (this.isSeatedInVehicle()) {
         this.fallTime = 0.0F;
         this.lastFallSpeed = 0.0F;
         this.bFalling = false;
         this.wasOnStairs = false;
      } else {
         if (this.z > 0.0F) {
    IsoDirections var1 = IsoDirections.Max;
            if (!this.isZombie() && this.isClimbing()) {
               if (this.current.Is(IsoFlagType.climbSheetW) || this.current.Is(IsoFlagType.climbSheetTopW)) {
                  var1 = IsoDirections.W;
               }

               if (this.current.Is(IsoFlagType.climbSheetE) || this.current.Is(IsoFlagType.climbSheetTopE)) {
                  var1 = IsoDirections.E;
               }

               if (this.current.Is(IsoFlagType.climbSheetN) || this.current.Is(IsoFlagType.climbSheetTopN)) {
                  var1 = IsoDirections.N;
               }

               if (this.current.Is(IsoFlagType.climbSheetS) || this.current.Is(IsoFlagType.climbSheetTopS)) {
                  var1 = IsoDirections.S;
               }
            }

    float var2 = 0.125F * (GameTime.getInstance().getMultiplier() / 1.6F);
            if (this.bClimbing) {
               var2 = 0.0F;
            }

            if (this.getCurrentState() == ClimbOverFenceState.instance() || this.getCurrentState() == ClimbThroughWindowState.instance()) {
               this.fallTime = 0.0F;
               var2 = 0.0F;
            }

            this.lastFallSpeed = var2;
            if (!this.current.TreatAsSolidFloor()) {
               if (var1 != IsoDirections.Max) {
                  this.dir = var1;
               }

    float var3 = 6.0F * (GameTime.getInstance().getMultiplier() / 1.6F);
    float var4 = this.getHeightAboveFloor();
               if (var2 > var4) {
                  var3 *= var4 / var2;
               }

               this.fallTime += var3;
               if (var1 != IsoDirections.Max) {
                  this.fallTime = 0.0F;
               }

               if (this.fallTime < 20.0F && var4 < 0.2F) {
                  this.fallTime = 0.0F;
               }

               this.setZ(this.getZ() - var2);
            } else if (!(this.getZ() > (int)this.getZ()) && !(var2 < 0.0F)) {
               this.DoLand();
               this.fallTime = 0.0F;
               this.bFalling = false;
            } else {
               if (var1 != IsoDirections.Max) {
                  this.dir = var1;
               }

               if (!this.current.HasStairs()) {
                  if (!this.wasOnStairs) {
    float var5 = 6.0F * (GameTime.getInstance().getMultiplier() / 1.6F);
    float var6 = this.getHeightAboveFloor();
                     if (var2 > var6) {
                        var5 *= var6 / var2;
                     }

                     this.fallTime += var5;
                     if (var1 != IsoDirections.Max) {
                        this.fallTime = 0.0F;
                     }

                     this.setZ(this.getZ() - var2);
                     if (this.z < (int)this.llz) {
                        this.z = (int)this.llz;
                        this.DoLand();
                        this.fallTime = 0.0F;
                        this.bFalling = false;
                     }
                  } else {
                     this.wasOnStairs = false;
                  }
               } else {
                  this.fallTime = 0.0F;
                  this.bFalling = false;
                  this.wasOnStairs = true;
               }
            }
         } else {
            this.DoLand();
            this.fallTime = 0.0F;
            this.bFalling = false;
         }

         this.llz = this.lz;
      }
   }

    float getHeightAboveFloor() {
      if (this.current == nullptr) {
         return 1.0F;
      } else {
         if (this.current.HasStairs()) {
    float var1 = this.current.getApparentZ(this.x - (int)this.x, this.y - (int)this.y);
            if (this.getZ() >= var1) {
               return this.getZ() - var1;
            }
         }

         if (this.current.TreatAsSolidFloor()) {
            return this.getZ() - (int)this.getZ();
         } else if (this.current.z == 0) {
            return this.getZ();
         } else {
    IsoGridSquare var3 = this.getCell().getGridSquare(this.current.x, this.current.y, this.current.z - 1);
            if (var3 != nullptr && var3.HasStairs()) {
    float var2 = var3.getApparentZ(this.x - (int)this.x, this.y - (int)this.y);
               return this.getZ() - var2;
            } else {
               return 1.0F;
            }
         }
      }
   }

    void updateMovementRates() {
   }

    float calculateIdleSpeed() {
    float var1 = 0.01F;
      var1 = (float)(var1 + this.getMoodles().getMoodleLevel(MoodleType.Endurance) * 2.5 / 10.0);
      return var1 * GameTime.getAnimSpeedFix();
   }

    float calculateBaseSpeed() {
    float var1 = 0.8F;
    float var2 = 1.0F;
      if (this.getMoodles() != nullptr) {
         var1 -= this.getMoodles().getMoodleLevel(MoodleType.Endurance) * 0.15F;
         var1 -= this.getMoodles().getMoodleLevel(MoodleType.HeavyLoad) * 0.15F;
      }

      if (this.getMoodles().getMoodleLevel(MoodleType.Panic) >= 3 && this.Traits.AdrenalineJunkie.isSet()) {
    int var3 = this.getMoodles().getMoodleLevel(MoodleType.Panic) + 1;
         var1 += var3 / 20.0F;
      }

      for (int var7 = BodyPartType.ToIndex(BodyPartType.Torso_Upper); var7 < BodyPartType.ToIndex(BodyPartType.Neck) + 1; var7++) {
    BodyPart var4 = this.getBodyDamage().getBodyPart(BodyPartType.FromIndex(var7));
         if (var4.HasInjury()) {
            var1 -= 0.1F;
         }

         if (var4.bandaged()) {
            var1 += 0.05F;
         }
      }

    BodyPart var8 = this.getBodyDamage().getBodyPart(BodyPartType.UpperLeg_L);
      if (var8.getAdditionalPain(true) > 20.0F) {
         var1 -= (var8.getAdditionalPain(true) - 20.0F) / 100.0F;
      }

      for (int var9 = 0; var9 < this.bagsWorn.size(); var9++) {
    InventoryContainer var5 = this.bagsWorn.get(var9);
         var2 += this.calcRunSpeedModByBag(var5);
      }

      if (this.getPrimaryHandItem() != nullptr && this.getPrimaryHandItem() instanceof InventoryContainer) {
         var2 += this.calcRunSpeedModByBag((InventoryContainer)this.getPrimaryHandItem());
      }

      if (this.getSecondaryHandItem() != nullptr && this.getSecondaryHandItem() instanceof InventoryContainer) {
         var2 += this.calcRunSpeedModByBag((InventoryContainer)this.getSecondaryHandItem());
      }

      this.fullSpeedMod = this.runSpeedModifier + (var2 - 1.0F);
      return var1 * (1.0F - Math.abs(1.0F - this.fullSpeedMod) / 2.0F);
   }

    float calcRunSpeedModByClothing() {
    float var1 = 0.0F;
    int var2 = 0;

      for (int var3 = 0; var3 < this.wornItems.size(); var3++) {
    InventoryItem var4 = this.wornItems.getItemByIndex(var3);
         if (dynamic_cast<Clothing*>(var4) != nullptr && ((Clothing)var4).getRunSpeedModifier() != 1.0F) {
            var1 += ((Clothing)var4).getRunSpeedModifier();
            var2++;
         }
      }

      if (var1 == 0.0F && var2 == 0) {
         var1 = 1.0F;
         var2 = 1;
      }

      if (this.getWornItem("Shoes") == nullptr) {
         var1 *= 0.8F;
      }

      return var1 / var2;
   }

    float calcRunSpeedModByBag(InventoryContainer var1) {
    float var2 = var1.getScriptItem().runSpeedModifier - 1.0F;
    float var3 = var1.getContentsWeight() / var1.getEffectiveCapacity(this);
      return var2 * (1.0F + var3 / 2.0F);
   }

    float calculateCombatSpeed() {
    bool var1 = true;
    float var2 = 1.0F;
    HandWeapon var3 = nullptr;
      if (this.getPrimaryHandItem() != nullptr && this.getPrimaryHandItem() instanceof HandWeapon) {
         var3 = (HandWeapon)this.getPrimaryHandItem();
         var2 *= ((HandWeapon)this.getPrimaryHandItem()).getBaseSpeed();
      }

    WeaponType var4 = WeaponType.getWeaponType(this);
      if (var3 != nullptr && var3.isTwoHandWeapon() && this.getSecondaryHandItem() != var3) {
         var2 *= 0.77F;
      }

      if (var3 != nullptr && this.Traits.Axeman.isSet() && var3.getCategories().contains("Axe")) {
         var2 *= this.getChopTreeSpeed();
         var1 = false;
      }

      var2 -= this.getMoodles().getMoodleLevel(MoodleType.Endurance) * 0.07F;
      var2 -= this.getMoodles().getMoodleLevel(MoodleType.HeavyLoad) * 0.07F;
      var2 += this.getWeaponLevel() * 0.03F;
      var2 += this.getPerkLevel(Perks.Fitness) * 0.02F;
      if (this.getSecondaryHandItem() != nullptr && this.getSecondaryHandItem() instanceof InventoryContainer) {
         var2 *= 0.95F;
      }

      var2 *= Rand.Next(1.1F, 1.2F);
      var2 *= this.combatSpeedModifier;
      var2 *= this.getArmsInjurySpeedModifier();
      if (this.getBodyDamage() != nullptr && this.getBodyDamage().getThermoregulator() != nullptr) {
         var2 *= this.getBodyDamage().getThermoregulator().getCombatModifier();
      }

      var2 = Math.min(1.6F, var2);
      var2 = Math.max(0.8F, var2);
      if (var3 != nullptr && var3.isTwoHandWeapon() && var4.type.equalsIgnoreCase("heavy")) {
         var2 *= 1.2F;
      }

      return var2 * (var1 ? GameTime.getAnimSpeedFix() : 1.0F);
   }

    float getArmsInjurySpeedModifier() {
    float var1 = 1.0F;
    float var2 = 0.0F;
    BodyPart var3 = this.getBodyDamage().getBodyPart(BodyPartType.Hand_R);
      var2 = this.calculateInjurySpeed(var3, true);
      if (var2 > 0.0F) {
         var1 -= var2;
      }

      var3 = this.getBodyDamage().getBodyPart(BodyPartType.ForeArm_R);
      var2 = this.calculateInjurySpeed(var3, true);
      if (var2 > 0.0F) {
         var1 -= var2;
      }

      var3 = this.getBodyDamage().getBodyPart(BodyPartType.UpperArm_R);
      var2 = this.calculateInjurySpeed(var3, true);
      if (var2 > 0.0F) {
         var1 -= var2;
      }

    return var1;
   }

    float getFootInjurySpeedModifier() {
    float var1 = 0.0F;
    bool var2 = true;
    float var3 = 0.0F;
    float var4 = 0.0F;

      for (int var5 = BodyPartType.ToIndex(BodyPartType.Groin); var5 < BodyPartType.ToIndex(BodyPartType.MAX); var5++) {
         var1 = this.calculateInjurySpeed(this.getBodyDamage().getBodyPart(BodyPartType.FromIndex(var5)), false);
         if (var2) {
            var3 += var1;
         } else {
            var4 += var1;
         }

         var2 = !var2;
      }

      return var3 > var4 ? -(var3 + var4) : var3 + var4;
   }

    float calculateInjurySpeed(BodyPart var1, bool var2) {
    float var3 = var1.getScratchSpeedModifier();
    float var4 = var1.getCutSpeedModifier();
    float var5 = var1.getBurnSpeedModifier();
    float var6 = var1.getDeepWoundSpeedModifier();
    float var7 = 0.0F;
      if ((var1.getType() == BodyPartType.Foot_L || var1.getType() == BodyPartType.Foot_R)
         && (
            var1.getBurnTime() > 5.0F
               || var1.getBiteTime() > 0.0F
               || var1.deepWounded()
               || var1.isSplint()
               || var1.getFractureTime() > 0.0F
               || var1.haveGlass()
         )) {
         var7 = 1.0F;
         if (var1.bandaged()) {
            var7 = 0.7F;
         }

         if (var1.getFractureTime() > 0.0F) {
            var7 = this.calcFractureInjurySpeed(var1);
         }
      }

      if (var1.haveBullet()) {
         return 1.0F;
      } else {
         if (var1.getScratchTime() > 2.0F
            || var1.getCutTime() > 5.0F
            || var1.getBurnTime() > 0.0F
            || var1.getDeepWoundTime() > 0.0F
            || var1.isSplint()
            || var1.getFractureTime() > 0.0F
            || var1.getBiteTime() > 0.0F) {
            var7 += var1.getScratchTime() / var3 + var1.getCutTime() / var4 + var1.getBurnTime() / var5 + var1.getDeepWoundTime() / var6;
            var7 += var1.getBiteTime() / 20.0F;
            if (var1.bandaged()) {
               var7 /= 2.0F;
            }

            if (var1.getFractureTime() > 0.0F) {
               var7 = this.calcFractureInjurySpeed(var1);
            }
         }

         if (var2 && var1.getPain() > 20.0F) {
            var7 += var1.getPain() / 10.0F;
         }

    return var7;
      }
   }

    float calcFractureInjurySpeed(BodyPart var1) {
    float var2 = 0.4F;
      if (var1.getFractureTime() > 10.0F) {
         var2 = 0.7F;
      }

      if (var1.getFractureTime() > 20.0F) {
         var2 = 1.0F;
      }

      if (var1.getSplintFactor() > 0.0F) {
         var2 -= 0.2F;
         var2 -= Math.min(var1.getSplintFactor() / 10.0F, 0.8F);
      }

      return Math.max(0.0F, var2);
   }

    void calculateWalkSpeed() {
      if (!(dynamic_cast<IsoPlayer*>(this) != nullptr) || ((IsoPlayer)this).isLocalPlayer()) {
    float var1 = 0.0F;
    float var2 = this.getFootInjurySpeedModifier();
         this.setVariable("WalkInjury", var2);
         var1 = this.calculateBaseSpeed();
         if (!this.bRunning && !this.bSprinting) {
            var1 *= this.walkSpeedModifier;
         } else {
            var1 -= 0.15F;
            var1 *= this.fullSpeedMod;
            var1 += this.getPerkLevel(Perks.Sprinting) / 20.0F;
            var1 = (float)(var1 - Math.abs(var2 / 1.5));
            if ("Tutorial" == Core.GameMode)) {
               var1 = Math.max(1.0F, var1);
            }
         }

         if (this.getSlowFactor() > 0.0F) {
            var1 *= 0.05F;
         }

         var1 = Math.min(1.0F, var1);
         if (this.getBodyDamage() != nullptr && this.getBodyDamage().getThermoregulator() != nullptr) {
            var1 *= this.getBodyDamage().getThermoregulator().getMovementModifier();
         }

         if (this.isAiming()) {
    float var3 = Math.min(0.9F + this.getPerkLevel(Perks.Nimble) / 10.0F, 1.5F);
    float var4 = Math.min(var1 * 2.5F, 1.0F);
            var3 *= var4;
            var3 = Math.max(var3, 0.6F);
            this.setVariable("StrafeSpeed", var3 * GameTime.getAnimSpeedFix());
         }

         if (this.isInTreesNoBush()) {
    IsoGridSquare var13 = this.getCurrentSquare();
            if (var13 != nullptr && var13.Has(IsoObjectType.tree)) {
    IsoTree var14 = var13.getTree();
               if (var14 != nullptr) {
                  var1 *= var14.getSlowFactor(this);
               }
            }
         }

         this.setVariable("WalkSpeed", var1 * GameTime.getAnimSpeedFix());
      }
   }

    void updateSpeedModifiers() {
      this.runSpeedModifier = 1.0F;
      this.walkSpeedModifier = 1.0F;
      this.combatSpeedModifier = 1.0F;
      this.bagsWorn = std::make_unique<std::vector<>>();

      for (int var1 = 0; var1 < this.getWornItems().size(); var1++) {
    InventoryItem var2 = this.getWornItems().getItemByIndex(var1);
         if (dynamic_cast<Clothing*>(var2) != nullptr var3) {
            this.combatSpeedModifier = this.combatSpeedModifier + (var3.getCombatSpeedModifier() - 1.0F);
         }

         if (dynamic_cast<InventoryContainer*>(var2) != nullptr var5) {
            this.combatSpeedModifier = this.combatSpeedModifier + (var5.getScriptItem().combatSpeedModifier - 1.0F);
            this.bagsWorn.push_back(var5);
         }
      }

    InventoryItem var4 = this.getWornItems().getItem("Shoes");
      if (var4 == nullptr || var4.getCondition() == 0) {
         this.runSpeedModifier *= 0.85F;
         this.walkSpeedModifier *= 0.85F;
      }
   }

    void DoFloorSplat(IsoGridSquare var1, const std::string& var2, bool var3, float var4, float var5) {
      if (var1 != nullptr) {
         var1.DirtySlice();
    IsoObject var6 = nullptr;

         for (int var7 = 0; var7 < var1.getObjects().size(); var7++) {
    IsoObject var8 = (IsoObject)var1.getObjects().get(var7);
            if (var8.sprite != nullptr && var8.sprite.getProperties().Is(IsoFlagType.solidfloor) && var6 == nullptr) {
               var6 = var8;
            }
         }

         if (var6 != nullptr
            && var6.sprite != nullptr
            && (var6.sprite.getProperties().Is(IsoFlagType.vegitation) || var6.sprite.getProperties().Is(IsoFlagType.solidfloor))) {
    IsoSprite var9 = IsoSprite.getSprite(IsoSpriteManager.instance, var2, 0);
            if (var9 == nullptr) {
               return;
            }

            if (var6.AttachedAnimSprite.size() > 7) {
               return;
            }

    IsoSpriteInstance var10 = IsoSpriteInstance.get(var9);
            var6.AttachedAnimSprite.push_back(var10);
            ((IsoSpriteInstance)var6.AttachedAnimSprite.get(var6.AttachedAnimSprite.size() - 1)).Flip = var3;
            ((IsoSpriteInstance)var6.AttachedAnimSprite.get(var6.AttachedAnimSprite.size() - 1)).tintr = 0.5F + Rand.Next(100) / 2000.0F;
            ((IsoSpriteInstance)var6.AttachedAnimSprite.get(var6.AttachedAnimSprite.size() - 1)).tintg = 0.7F + Rand.Next(300) / 1000.0F;
            ((IsoSpriteInstance)var6.AttachedAnimSprite.get(var6.AttachedAnimSprite.size() - 1)).tintb = 0.7F + Rand.Next(300) / 1000.0F;
            ((IsoSpriteInstance)var6.AttachedAnimSprite.get(var6.AttachedAnimSprite.size() - 1)).SetAlpha(0.4F * var5 * 0.6F);
            ((IsoSpriteInstance)var6.AttachedAnimSprite.get(var6.AttachedAnimSprite.size() - 1)).SetTargetAlpha(0.4F * var5 * 0.6F);
            ((IsoSpriteInstance)var6.AttachedAnimSprite.get(var6.AttachedAnimSprite.size() - 1)).offZ = -var4;
            ((IsoSpriteInstance)var6.AttachedAnimSprite.get(var6.AttachedAnimSprite.size() - 1)).offX = 0.0F;
         }
      }
   }

    void DoSplat(IsoGridSquare var1, const std::string& var2, bool var3, IsoFlagType var4, float var5, float var6, float var7) {
      if (var1 != nullptr) {
         var1.DoSplat(var2, var3, var4, var5, var6, var7);
      }
   }

    bool onMouseLeftClick(int var1, int var2) {
      if (IsoCamera.CamCharacter != IsoPlayer.getInstance() && Core.bDebug) {
         IsoCamera.CamCharacter = this;
      }

      return super.onMouseLeftClick(var1, var2);
   }

    void calculateStats() {
      if (GameServer.bServer) {
         this.stats.fatigue = 0.0F;
      } else if (GameClient.bClient && (!ServerOptions.instance.SleepAllowed.getValue() || !ServerOptions.instance.SleepNeeded.getValue())) {
         this.stats.fatigue = 0.0F;
      }

      if (!LuaHookManager.TriggerHook("CalculateStats", this)) {
         this.updateEndurance();
         this.updateTripping();
         this.updateThirst();
         this.updateStress();
         this.updateStats_WakeState();
         this.stats.endurance = PZMath.clamp(this.stats.endurance, 0.0F, 1.0F);
         this.stats.hunger = PZMath.clamp(this.stats.hunger, 0.0F, 1.0F);
         this.stats.stress = PZMath.clamp(this.stats.stress, 0.0F, 1.0F);
         this.stats.fatigue = PZMath.clamp(this.stats.fatigue, 0.0F, 1.0F);
         this.updateMorale();
         this.updateFitness();
      }
   }

    void updateStats_WakeState() {
      if (IsoPlayer.getInstance() == this && this.Asleep) {
         this.updateStats_Sleeping();
      } else {
         this.updateStats_Awake();
      }
   }

    void updateStats_Sleeping() {
   }

    void updateStats_Awake() {
      this.stats.stress = (float)(
         this.stats.stress - ZomboidGlobals.StressReduction * GameTime.instance.getMultiplier() * GameTime.instance.getDeltaMinutesPerDay()
      );
    float var1 = 1.0F - this.stats.endurance;
      if (var1 < 0.3F) {
         var1 = 0.3F;
      }

    float var2 = 1.0F;
      if (this.Traits.NeedsLessSleep.isSet()) {
         var2 = 0.7F;
      }

      if (this.Traits.NeedsMoreSleep.isSet()) {
         var2 = 1.3F;
      }

    double var3 = SandboxOptions.instance.getStatsDecreaseMultiplier();
      if (var3 < 1.0) {
         var3 = 1.0;
      }

      this.stats.fatigue = (float)(
         this.stats.fatigue
            + ZomboidGlobals.FatigueIncrease
               * SandboxOptions.instance.getStatsDecreaseMultiplier()
               * var1
               * GameTime.instance.getMultiplier()
               * GameTime.instance.getDeltaMinutesPerDay()
               * var2
               * this.getFatiqueMultiplier()
      );
    float var5 = this.getAppetiteMultiplier();
      if ((!(dynamic_cast<IsoPlayer*>(this) != nullptr) || !((IsoPlayer)this).IsRunning() || !this.isPlayerMoving()) && !this.isCurrentState(SwipeStatePlayer.instance())) {
         if (this.Moodles.getMoodleLevel(MoodleType.FoodEaten) == 0) {
            this.stats.hunger = (float)(
               this.stats.hunger
                  + ZomboidGlobals.HungerIncrease
                     * SandboxOptions.instance.getStatsDecreaseMultiplier()
                     * var5
                     * GameTime.instance.getMultiplier()
                     * GameTime.instance.getDeltaMinutesPerDay()
                     * this.getHungerMultiplier()
            );
         } else {
            this.stats.hunger = (float)(
               this.stats.hunger
                  + (float)ZomboidGlobals.HungerIncreaseWhenWellFed
                     * SandboxOptions.instance.getStatsDecreaseMultiplier()
                     * GameTime.instance.getMultiplier()
                     * GameTime.instance.getDeltaMinutesPerDay()
                     * this.getHungerMultiplier()
            );
         }
      } else if (this.Moodles.getMoodleLevel(MoodleType.FoodEaten) == 0) {
         this.stats.hunger = (float)(
            this.stats.hunger
               + ZomboidGlobals.HungerIncreaseWhenExercise
                  / 3.0
                  * SandboxOptions.instance.getStatsDecreaseMultiplier()
                  * var5
                  * GameTime.instance.getMultiplier()
                  * GameTime.instance.getDeltaMinutesPerDay()
                  * this.getHungerMultiplier()
         );
      } else {
         this.stats.hunger = (float)(
            this.stats.hunger
               + ZomboidGlobals.HungerIncreaseWhenExercise
                  * SandboxOptions.instance.getStatsDecreaseMultiplier()
                  * var5
                  * GameTime.instance.getMultiplier()
                  * GameTime.instance.getDeltaMinutesPerDay()
                  * this.getHungerMultiplier()
         );
      }

      if (this.getCurrentSquare() == this.getLastSquare() && !this.isReading()) {
         this.stats.idleboredom = this.stats.idleboredom + 5.0E-5F * GameTime.instance.getMultiplier() * GameTime.instance.getDeltaMinutesPerDay();
         this.stats.idleboredom = this.stats.idleboredom + 0.00125F * GameTime.instance.getMultiplier() * GameTime.instance.getDeltaMinutesPerDay();
      }

      if (this.getCurrentSquare() != nullptr
         && this.getLastSquare() != nullptr
         && this.getCurrentSquare().getRoom() == this.getLastSquare().getRoom()
         && this.getCurrentSquare().getRoom() != nullptr
         && !this.isReading()) {
         this.stats.idleboredom = this.stats.idleboredom + 1.0E-4F * GameTime.instance.getMultiplier() * GameTime.instance.getDeltaMinutesPerDay();
         this.stats.idleboredom = this.stats.idleboredom + 0.00125F * GameTime.instance.getMultiplier() * GameTime.instance.getDeltaMinutesPerDay();
      }
   }

    void updateMorale() {
    float var1 = 1.0F - this.stats.getStress() - 0.5F;
      var1 *= 1.0E-4F;
      if (var1 > 0.0F) {
         var1 += 0.5F;
      }

      this.stats.morale += var1;
      this.stats.morale = PZMath.clamp(this.stats.morale, 0.0F, 1.0F);
   }

    void updateFitness() {
      this.stats.fitness = this.getPerkLevel(Perks.Fitness) / 5.0F - 1.0F;
      if (this.stats.fitness > 1.0F) {
         this.stats.fitness = 1.0F;
      }

      if (this.stats.fitness < -1.0F) {
         this.stats.fitness = -1.0F;
      }
   }

    void updateTripping() {
      if (this.stats.Tripping) {
         this.stats.TrippingRotAngle += 0.06F;
      } else {
         this.stats.TrippingRotAngle += 0.0F;
      }
   }

    float getAppetiteMultiplier() {
    float var1 = 1.0F - this.stats.hunger;
      if (this.Traits.HeartyAppitite.isSet()) {
         var1 *= 1.5F;
      }

      if (this.Traits.LightEater.isSet()) {
         var1 *= 0.75F;
      }

    return var1;
   }

    void updateStress() {
    float var1 = 1.0F;
      if (this.Traits.Cowardly.isSet()) {
         var1 = 2.0F;
      }

      if (this.Traits.Brave.isSet()) {
         var1 = 0.3F;
      }

      if (this.stats.Panic > 100.0F) {
         this.stats.Panic = 100.0F;
      }

      this.stats.stress = (float)(
         this.stats.stress
            + WorldSoundManager.instance.getStressFromSounds((int)this.getX(), (int)this.getY(), (int)this.getZ()) * ZomboidGlobals.StressFromSoundsMultiplier
      );
      if (this.BodyDamage.getNumPartsBitten() > 0) {
         this.stats.stress = (float)(
            this.stats.stress + ZomboidGlobals.StressFromBiteOrScratch * GameTime.instance.getMultiplier() * GameTime.instance.getDeltaMinutesPerDay()
         );
      }

      if (this.BodyDamage.getNumPartsScratched() > 0) {
         this.stats.stress = (float)(
            this.stats.stress + ZomboidGlobals.StressFromBiteOrScratch * GameTime.instance.getMultiplier() * GameTime.instance.getDeltaMinutesPerDay()
         );
      }

      if (this.BodyDamage.IsInfected() || this.BodyDamage.IsFakeInfected()) {
         this.stats.stress = (float)(
            this.stats.stress + ZomboidGlobals.StressFromBiteOrScratch * GameTime.instance.getMultiplier() * GameTime.instance.getDeltaMinutesPerDay()
         );
      }

      if (this.Traits.Hemophobic.isSet()) {
         this.stats.stress = (float)(
            this.stats.stress
               + this.getTotalBlood()
                  * ZomboidGlobals.StressFromHemophobic
                  * (GameTime.instance.getMultiplier() / 0.8F)
                  * GameTime.instance.getDeltaMinutesPerDay()
         );
      }

      if (this.Traits.Brooding.isSet()) {
         this.stats.Anger = (float)(
            this.stats.Anger
               - ZomboidGlobals.AngerDecrease
                  * ZomboidGlobals.BroodingAngerDecreaseMultiplier
                  * GameTime.instance.getMultiplier()
                  * GameTime.instance.getDeltaMinutesPerDay()
         );
      } else {
         this.stats.Anger = (float)(
            this.stats.Anger - ZomboidGlobals.AngerDecrease * GameTime.instance.getMultiplier() * GameTime.instance.getDeltaMinutesPerDay()
         );
      }

      this.stats.Anger = PZMath.clamp(this.stats.Anger, 0.0F, 1.0F);
   }

    void updateEndurance() {
      this.stats.endurance = PZMath.clamp(this.stats.endurance, 0.0F, 1.0F);
      this.stats.endurancelast = this.stats.endurance;
      if (this.isUnlimitedEndurance()) {
         this.stats.endurance = 1.0F;
      }
   }

    void updateThirst() {
    float var1 = 1.0F;
      if (this.Traits.HighThirst.isSet()) {
         var1 = (float)(var1 * 2.0);
      }

      if (this.Traits.LowThirst.isSet()) {
         var1 = (float)(var1 * 0.5);
      }

      if (IsoPlayer.getInstance() == this && !IsoPlayer.getInstance().isGhostMode()) {
         if (this.Asleep) {
            this.stats.thirst = (float)(
               this.stats.thirst
                  + ZomboidGlobals.ThirstSleepingIncrease
                     * SandboxOptions.instance.getStatsDecreaseMultiplier()
                     * GameTime.instance.getMultiplier()
                     * GameTime.instance.getDeltaMinutesPerDay()
                     * var1
            );
         } else {
            this.stats.thirst = (float)(
               this.stats.thirst
                  + ZomboidGlobals.ThirstIncrease
                     * SandboxOptions.instance.getStatsDecreaseMultiplier()
                     * GameTime.instance.getMultiplier()
                     * this.getRunningThirstReduction()
                     * GameTime.instance.getDeltaMinutesPerDay()
                     * var1
                     * this.getThirstMultiplier()
            );
         }

         if (this.stats.thirst > 1.0F) {
            this.stats.thirst = 1.0F;
         }
      }

      this.autoDrink();
   }

    double getRunningThirstReduction() {
    return this = = IsoPlayer.getInstance() && IsoPlayer.getInstance().IsRunning() ? 1.2 : 1.0;
   }

    void faceLocation(float var1, float var2) {
      tempo.x = var1 + 0.5F;
      tempo.y = var2 + 0.5F;
      tempo.x = tempo.x - this.getX();
      tempo.y = tempo.y - this.getY();
      this.DirectionFromVector(tempo);
      this.getVectorFromDirection(this.m_forwardDirection);
    AnimationPlayer var3 = this.getAnimationPlayer();
      if (var3 != nullptr && var3.isReady()) {
         var3.UpdateDir(this);
      }
   }

    void faceLocationF(float var1, float var2) {
      tempo.x = var1;
      tempo.y = var2;
      tempo.x = tempo.x - this.getX();
      tempo.y = tempo.y - this.getY();
      if (tempo.getLengthSquared() != 0.0F) {
         this.DirectionFromVector(tempo);
         tempo.normalize();
         this.m_forwardDirection.set(tempo.x, tempo.y);
    AnimationPlayer var3 = this.getAnimationPlayer();
         if (var3 != nullptr && var3.isReady()) {
            var3.UpdateDir(this);
         }
      }
   }

    bool isFacingLocation(float var1, float var2, float var3) {
    Vector2 var4 = BaseVehicle.allocVector2().set(var1 - this.getX(), var2 - this.getY());
      var4.normalize();
    Vector2 var5 = this.getLookVector(BaseVehicle.allocVector2());
    float var6 = var4.dot(var5);
      BaseVehicle.releaseVector2(var4);
      BaseVehicle.releaseVector2(var5);
      return var6 >= var3;
   }

    bool isFacingObject(IsoObject var1, float var2) {
    Vector2 var3 = BaseVehicle.allocVector2();
      var1.getFacingPosition(var3);
    bool var4 = this.isFacingLocation(var3.x, var3.y, var2);
      BaseVehicle.releaseVector2(var3);
    return var4;
   }

    void checkDrawWeaponPre(float var1, float var2, float var3, ColorInfo var4) {
      if (this.sprite != nullptr) {
         if (this.sprite.CurrentAnim != nullptr) {
            if (this.sprite.CurrentAnim.name != nullptr) {
               if (this.dir != IsoDirections.S
                  && this.dir != IsoDirections.SE
                  && this.dir != IsoDirections.E
                  && this.dir != IsoDirections.NE
                  && this.dir != IsoDirections.SW) {
                  if (this.sprite.CurrentAnim.name.contains("Attack_")) {
                     ;
                  }
               }
            }
         }
      }
   }

    void splatBlood(int var1, float var2) {
      if (this.getCurrentSquare() != nullptr) {
         this.getCurrentSquare().splatBlood(var1, var2);
      }
   }

    bool isOutside() {
      return this.getCurrentSquare() == nullptr ? false : this.getCurrentSquare().isOutside();
   }

    bool isFemale() {
      return this.bFemale;
   }

    void setFemale(bool var1) {
      this.bFemale = var1;
   }

    bool isZombie() {
    return false;
   }

    int getLastHitCount() {
      return this.lastHitCount;
   }

    void setLastHitCount(int var1) {
      this.lastHitCount = var1;
   }

    int getSurvivorKills() {
      return this.SurvivorKills;
   }

    void setSurvivorKills(int var1) {
      this.SurvivorKills = var1;
   }

    int getAge() {
      return this.age;
   }

    void setAge(int var1) {
      this.age = var1;
   }

    void exert(float var1) {
      if (this.Traits.PlaysFootball.isSet()) {
         var1 *= 0.9F;
      }

      if (this.Traits.Jogger.isSet()) {
         var1 *= 0.9F;
      }

      this.stats.endurance -= var1;
   }

    PerkInfo getPerkInfo(Perk var1) {
      for (int var2 = 0; var2 < this.PerkList.size(); var2++) {
    PerkInfo var3 = this.PerkList.get(var2);
         if (var3.perk == var1) {
    return var3;
         }
      }

    return nullptr;
   }

    bool isEquipped(InventoryItem var1) {
      return this.isEquippedClothing(var1) || this.isHandItem(var1);
   }

    bool isEquippedClothing(InventoryItem var1) {
      return this.wornItems.contains(var1);
   }

    bool isAttachedItem(InventoryItem var1) {
      return this.getAttachedItems().contains(var1);
   }

    void faceThisObject(IsoObject var1) {
      if (var1 != nullptr) {
    Vector2 var2 = tempo;
    BaseVehicle var3 = (BaseVehicle)Type.tryCastTo(var1, BaseVehicle.class);
    BarricadeAble var4 = (BarricadeAble)Type.tryCastTo(var1, BarricadeAble.class);
         if (var3 != nullptr) {
            var3.getFacingPosition(this, var2);
            var2.x = var2.x - this.getX();
            var2.y = var2.y - this.getY();
            this.DirectionFromVector(var2);
            var2.normalize();
            this.m_forwardDirection.set(var2.x, var2.y);
         } else if (var4 != nullptr && this.current == var4.getSquare()) {
            this.dir = var4.getNorth() ? IsoDirections.N : IsoDirections.W;
            this.getVectorFromDirection(this.m_forwardDirection);
         } else if (var4 != nullptr && this.current == var4.getOppositeSquare()) {
            this.dir = var4.getNorth() ? IsoDirections.S : IsoDirections.E;
            this.getVectorFromDirection(this.m_forwardDirection);
         } else {
            var1.getFacingPosition(var2);
            var2.x = var2.x - this.getX();
            var2.y = var2.y - this.getY();
            this.DirectionFromVector(var2);
            this.getVectorFromDirection(this.m_forwardDirection);
         }

    AnimationPlayer var5 = this.getAnimationPlayer();
         if (var5 != nullptr && var5.isReady()) {
            var5.UpdateDir(this);
         }
      }
   }

    void facePosition(int var1, int var2) {
      tempo.x = var1;
      tempo.y = var2;
      tempo.x = tempo.x - this.getX();
      tempo.y = tempo.y - this.getY();
      this.DirectionFromVector(tempo);
      this.getVectorFromDirection(this.m_forwardDirection);
    AnimationPlayer var3 = this.getAnimationPlayer();
      if (var3 != nullptr && var3.isReady()) {
         var3.UpdateDir(this);
      }
   }

    void faceThisObjectAlt(IsoObject var1) {
      if (var1 != nullptr) {
         var1.getFacingPositionAlt(tempo);
         tempo.x = tempo.x - this.getX();
         tempo.y = tempo.y - this.getY();
         this.DirectionFromVector(tempo);
         this.getVectorFromDirection(this.m_forwardDirection);
    AnimationPlayer var2 = this.getAnimationPlayer();
         if (var2 != nullptr && var2.isReady()) {
            var2.UpdateDir(this);
         }
      }
   }

    void setAnimated(bool var1) {
      this.legsSprite.Animate = true;
   }

    void playHurtSound() {
      this.getEmitter().playVocals(this.getHurtSound());
   }

    void playDeadSound() {
      if (this.isCloseKilled()) {
         this.getEmitter().playSoundImpl("HeadStab", this);
      } else {
         this.getEmitter().playSoundImpl("HeadSmash", this);
      }

      if (this.isZombie()) {
         ((IsoZombie)this).parameterZombieState.setState(zombie.audio.parameters.ParameterZombieState.State.Death);
      }
   }

    void saveChange(const std::string& var1, KahluaTable var2, ByteBuffer var3) {
      super.saveChange(var1, var2, var3);
      if ("addItem" == var1)) {
         if (var2 != nullptr && var2.rawget("item") instanceof InventoryItem) {
    InventoryItem var4 = (InventoryItem)var2.rawget("item");

            try {
               var4.saveWithSize(var3, false);
            } catch (Exception var6) {
               var6.printStackTrace();
            }
         }
      } else if ("addItemOfType" == var1)) {
         if (var2 != nullptr && var2.rawget("type") instanceof std::string) {
            GameWindow.WriteStringUTF(var3, (std::string)var2.rawget("type"));
            if (var2.rawget("count") instanceof double) {
               var3.putShort(((double)var2.rawget("count")).shortValue());
            } else {
               var3.putShort((short)1);
            }
         }
      } else if ("AddRandomDamageFromZombie" == var1)) {
         if (var2 != nullptr && var2.rawget("zombie") instanceof double) {
            var3.putShort(((double)var2.rawget("zombie")).shortValue());
         }
      } else if (!"AddZombieKill" == var1)) {
         if ("DamageFromWeapon" == var1)) {
            if (var2 != nullptr && var2.rawget("weapon") instanceof std::string) {
               GameWindow.WriteStringUTF(var3, (std::string)var2.rawget("weapon"));
            }
         } else if ("removeItem" == var1)) {
            if (var2 != nullptr && var2.rawget("item") instanceof double) {
               var3.putInt(((double)var2.rawget("item")).intValue());
            }
         } else if ("removeItemID" == var1)) {
            if (var2 != nullptr && var2.rawget("id") instanceof double) {
               var3.putInt(((double)var2.rawget("id")).intValue());
            }

            if (var2 != nullptr && var2.rawget("type") instanceof std::string) {
               GameWindow.WriteStringUTF(var3, (std::string)var2.rawget("type"));
            } else {
               GameWindow.WriteStringUTF(var3, nullptr);
            }
         } else if ("removeItemType" == var1)) {
            if (var2 != nullptr && var2.rawget("type") instanceof std::string) {
               GameWindow.WriteStringUTF(var3, (std::string)var2.rawget("type"));
               if (var2.rawget("count") instanceof double) {
                  var3.putShort(((double)var2.rawget("count")).shortValue());
               } else {
                  var3.putShort((short)1);
               }
            }
         } else if ("removeOneOf" == var1)) {
            if (var2 != nullptr && var2.rawget("type") instanceof std::string) {
               GameWindow.WriteStringUTF(var3, (std::string)var2.rawget("type"));
            }
         } else if ("reanimatedID" == var1)) {
            if (var2 != nullptr && var2.rawget("ID") instanceof double) {
    int var7 = ((double)var2.rawget("ID")).intValue();
               var3.putInt(var7);
            }
         } else if ("Shove" == var1)) {
            if (var2 != nullptr && var2.rawget("hitDirX") instanceof double && var2.rawget("hitDirY") instanceof double && var2.rawget("force") instanceof double) {
               var3.putFloat(((double)var2.rawget("hitDirX")).floatValue());
               var3.putFloat(((double)var2.rawget("hitDirY")).floatValue());
               var3.putFloat(((double)var2.rawget("force")).floatValue());
            }
         } else if ("addXp" == var1)) {
            if (var2 != nullptr && var2.rawget("perk") instanceof double && var2.rawget("xp") instanceof double) {
               var3.putInt(((double)var2.rawget("perk")).intValue());
               var3.putInt(((double)var2.rawget("xp")).intValue());
    void* var8 = var2.rawget("noMultiplier");
               var3.put((byte)(bool.TRUE == var8) ? 1 : 0));
            }
         } else if (!"wakeUp" == var1) && "mechanicActionDone" == var1) && var2 != nullptr) {
            var3.put((byte)(var2.rawget("success") ? 1 : 0));
            var3.putInt(((double)var2.rawget("vehicleId")).intValue());
            GameWindow.WriteString(var3, (std::string)var2.rawget("partId"));
            var3.put((byte)(var2.rawget("installing") ? 1 : 0));
            var3.putLong(((double)var2.rawget("itemId")).longValue());
         }
      }
   }

    void loadChange(const std::string& var1, ByteBuffer var2) {
      super.loadChange(var1, var2);
      if ("addItem" == var1)) {
         try {
    InventoryItem var3 = InventoryItem.loadItem(var2, 195);
            if (var3 != nullptr) {
               this.getInventory().AddItem(var3);
            }
         } catch (Exception var9) {
            var9.printStackTrace();
         }
      } else if ("addItemOfType" == var1)) {
    std::string var10 = GameWindow.ReadStringUTF(var2);
    short var4 = var2.getShort();

         for (int var5 = 0; var5 < var4; var5++) {
            this.getInventory().AddItem(var10);
         }
      } else if ("AddRandomDamageFromZombie" == var1)) {
    short var11 = var2.getShort();
    IsoZombie var20 = GameClient.getZombie(var11);
         if (var20 != nullptr && !this.isDead()) {
            this.getBodyDamage().AddRandomDamageFromZombie(var20, nullptr);
            this.getBodyDamage().Update();
            if (this.isDead()) {
               if (this.isFemale()) {
                  var20.getEmitter().playSound("FemaleBeingEatenDeath");
               } else {
                  var20.getEmitter().playSound("MaleBeingEatenDeath");
               }
            }
         }
      } else if ("AddZombieKill" == var1)) {
         this.setZombieKills(this.getZombieKills() + 1);
      } else if ("DamageFromWeapon" == var1)) {
    std::string var12 = GameWindow.ReadStringUTF(var2);
    InventoryItem var21 = InventoryItemFactory.CreateItem(var12);
         if (dynamic_cast<HandWeapon*>(var21) != nullptr) {
            this.getBodyDamage().DamageFromWeapon((HandWeapon)var21);
         }
      } else if ("exitVehicle" == var1)) {
    BaseVehicle var13 = this.getVehicle();
         if (var13 != nullptr) {
            var13.exit(this);
            this.setVehicle(nullptr);
         }
      } else if ("removeItem" == var1)) {
    int var14 = var2.getInt();
         if (var14 >= 0 && var14 < this.getInventory().getItems().size()) {
    InventoryItem var22 = (InventoryItem)this.getInventory().getItems().get(var14);
            this.removeFromHands(var22);
            this.getInventory().Remove(var22);
         }
      } else if ("removeItemID" == var1)) {
    int var15 = var2.getInt();
    std::string var23 = GameWindow.ReadStringUTF(var2);
    InventoryItem var27 = this.getInventory().getItemWithID(var15);
         if (var27 != nullptr && var27.getFullType() == var23)) {
            this.removeFromHands(var27);
            this.getInventory().Remove(var27);
         }
      } else if ("removeItemType" == var1)) {
    std::string var16 = GameWindow.ReadStringUTF(var2);
    short var24 = var2.getShort();

         for (int var28 = 0; var28 < var24; var28++) {
            this.getInventory().RemoveOneOf(var16);
         }
      } else if ("removeOneOf" == var1)) {
    std::string var17 = GameWindow.ReadStringUTF(var2);
         this.getInventory().RemoveOneOf(var17);
      } else if ("reanimatedID" == var1)) {
         this.ReanimatedCorpseID = var2.getInt();
      } else if (!"Shove" == var1)) {
         if ("StopBurning" == var1)) {
            this.StopBurning();
         } else if ("addXp" == var1)) {
    Perk var18 = Perks.fromIndex(var2.getInt());
    int var25 = var2.getInt();
    bool var29 = var2.get() == 1;
            if (var29) {
               this.getXp().AddXPNoMultiplier(var18, var25);
            } else {
               this.getXp().AddXP(var18, var25);
            }
         } else if ("wakeUp" == var1)) {
            if (this.isAsleep()) {
               this.Asleep = false;
               this.ForceWakeUpTime = -1.0F;
               TutorialManager.instance.StealControl = false;
               if (dynamic_cast<IsoPlayer*>(this) != nullptr && ((IsoPlayer)this).isLocalPlayer()) {
                  UIManager.setFadeBeforeUI(((IsoPlayer)this).getPlayerNum(), true);
                  UIManager.FadeIn(((IsoPlayer)this).getPlayerNum(), 2.0);
                  GameClient.instance.sendPlayer((IsoPlayer)this);
               }
            }
         } else if ("mechanicActionDone" == var1)) {
    bool var19 = var2.get() == 1;
    int var26 = var2.getInt();
    std::string var30 = GameWindow.ReadString(var2);
    bool var6 = var2.get() == 1;
    long var7 = var2.getLong();
            LuaEventManager.triggerEvent("OnMechanicActionDone", this, var19, var26, var30, var7, var6);
         } else if ("vehicleNoKey" == var1)) {
            this.SayDebug(" [img=media/ui/CarKey_none.png]");
         }
      }
   }

    int getAlreadyReadPages(const std::string& var1) {
      for (int var2 = 0; var2 < this.ReadBooks.size(); var2++) {
    ReadBook var3 = this.ReadBooks.get(var2);
         if (var3.fullType == var1)) {
            return var3.alreadyReadPages;
         }
      }

    return 0;
   }

    void setAlreadyReadPages(const std::string& var1, int var2) {
      for (int var3 = 0; var3 < this.ReadBooks.size(); var3++) {
    ReadBook var4 = this.ReadBooks.get(var3);
         if (var4.fullType == var1)) {
            var4.alreadyReadPages = var2;
            return;
         }
      }

    ReadBook var5 = std::make_shared<ReadBook>();
      var5.fullType = var1;
      var5.alreadyReadPages = var2;
      this.ReadBooks.push_back(var5);
   }

    void updateLightInfo() {
      if (GameServer.bServer) {
         if (!this.isZombie()) {
            /* synchronized - TODO: add std::mutex */ (this.lightInfo) {
               this.lightInfo.square = this.movingSq;
               if (this.lightInfo.square == nullptr) {
                  this.lightInfo.square = this.getCell().getGridSquare((int)this.x, (int)this.y, (int)this.z);
               }

               if (this.ReanimatedCorpse != nullptr) {
                  this.lightInfo.square = this.getCell().getGridSquare((int)this.x, (int)this.y, (int)this.z);
               }

               this.lightInfo.x = this.getX();
               this.lightInfo.y = this.getY();
               this.lightInfo.z = this.getZ();
               this.lightInfo.angleX = this.getForwardDirection().getX();
               this.lightInfo.angleY = this.getForwardDirection().getY();
               this.lightInfo.torches.clear();
               this.lightInfo.night = GameTime.getInstance().getNight();
            }
         }
      }
   }

    LightInfo initLightInfo2() {
      /* synchronized - TODO: add std::mutex */ (this.lightInfo) {
         for (int var2 = 0; var2 < this.lightInfo2.torches.size(); var2++) {
            TorchInfo.release((TorchInfo)this.lightInfo2.torches.get(var2));
         }

         this.lightInfo2.initFrom(this.lightInfo);
      }

      return this.lightInfo2;
   }

    LightInfo getLightInfo2() {
      return this.lightInfo2;
   }

    void postupdate() {
      s_performance.postUpdate.invokeAndMeasure(this, IsoGameCharacter::postUpdateInternal);
   }

    void postUpdateInternal() {
      super.postupdate();
    AnimationPlayer var1 = this.getAnimationPlayer();
      var1.UpdateDir(this);
    bool var2 = this.shouldBeTurning();
      this.setTurning(var2);
    bool var3 = this.shouldBeTurning90();
      this.setTurning90(var3);
    bool var4 = this.shouldBeTurningAround();
      this.setTurningAround(var4);
      this.actionContext.update();
      if (this.getCurrentSquare() != nullptr) {
         this.advancedAnimator.update();
      }

      this.actionContext.clearEvent("ActiveAnimFinished");
      this.actionContext.clearEvent("ActiveAnimFinishing");
      this.actionContext.clearEvent("ActiveAnimLooped");
      var1 = this.getAnimationPlayer();
      if (var1 != nullptr) {
    MoveDeltaModifiers var17 = L_postUpdate.moveDeltas;
         var17.moveDelta = this.getMoveDelta();
         var17.turnDelta = this.getTurnDelta();
         var3 = this.hasPath();
         var4 = dynamic_cast<IsoPlayer*>(this) != nullptr;
         if (var4 && var3 && this.isRunning()) {
            var17.turnDelta = Math.max(var17.turnDelta, 2.0F);
         }

    State var5 = this.getCurrentState();
         if (var5 != nullptr) {
            var5.getDeltaModifiers(this, var17);
         }

         if (var17.twistDelta == -1.0F) {
            var17.twistDelta = var17.turnDelta * 1.8F;
         }

         if (!this.isTurning()) {
            var17.turnDelta = 0.0F;
         }

    float var6 = Math.max(1.0F - var17.moveDelta / 2.0F, 0.0F);
         var1.angleStepDelta = var6 * var17.turnDelta;
         var1.angleTwistDelta = var6 * var17.twistDelta;
         var1.setMaxTwistAngle((float) (Math.PI / 180.0) * this.getMaxTwist());
      }

      if (this.hasActiveModel()) {
         try {
    ModelSlot var15 = this.legsSprite.modelSlot;
            var15.Update();
         } catch (Throwable var13) {
            ExceptionLogger.logException(var13);
         }
      } else {
         var1 = this.getAnimationPlayer();
         var1.bUpdateBones = false;
         var2 = PerformanceSettings.InterpolateAnims;
         PerformanceSettings.InterpolateAnims = false;

         try {
            var1.UpdateDir(this);
            var1.Update();
         } catch (Throwable var11) {
            ExceptionLogger.logException(var11);
         } finally {
            var1.bUpdateBones = true;
            PerformanceSettings.InterpolateAnims = var2;
         }
      }

      this.updateLightInfo();
      if (this.isAnimationRecorderActive()) {
         this.m_animationRecorder.logVariables(this);
         this.m_animationRecorder.endLine();
      }
   }

    bool shouldBeTurning() {
    float var1 = this.getTargetTwist();
    float var2 = PZMath.abs(var1);
    bool var3 = var2 > 1.0F;
      if (this.isZombie() && this.getCurrentState() == ZombieFallDownState.instance()) {
    return false;
      } else if (this.blockTurning) {
    return false;
      } else if (this.isBehaviourMoving()) {
    return var3;
      } else if (this.isPlayerMoving()) {
    return var3;
      } else if (this.isAttacking()) {
         return !this.bAimAtFloor;
      } else {
    float var4 = this.getAbsoluteExcessTwist();
         if (var4 > 1.0F) {
    return true;
         } else {
            return this.isTurning() ? var3 : false;
         }
      }
   }

    bool shouldBeTurning90() {
      if (!this.isTurning()) {
    return false;
      } else if (this.isTurning90()) {
    return true;
      } else {
    float var1 = this.getTargetTwist();
    float var2 = Math.abs(var1);
         return var2 > 65.0F;
      }
   }

    bool shouldBeTurningAround() {
      if (!this.isTurning()) {
    return false;
      } else if (this.isTurningAround()) {
    return true;
      } else {
    float var1 = this.getTargetTwist();
    float var2 = Math.abs(var1);
         return var2 > 110.0F;
      }
   }

    bool isTurning() {
      return this.m_isTurning;
   }

    void setTurning(bool var1) {
      this.m_isTurning = var1;
   }

    bool isTurningAround() {
      return this.m_isTurningAround;
   }

    void setTurningAround(bool var1) {
      this.m_isTurningAround = var1;
   }

    bool isTurning90() {
      return this.m_isTurning90;
   }

    void setTurning90(bool var1) {
      this.m_isTurning90 = var1;
   }

    bool hasPath() {
      return this.getPath2() != nullptr;
   }

    bool isAnimationRecorderActive() {
      return this.m_animationRecorder != nullptr && this.m_animationRecorder.isRecording();
   }

    AnimationPlayerRecorder getAnimationPlayerRecorder() {
      return this.m_animationRecorder;
   }

    float getMeleeDelay() {
      return this.meleeDelay;
   }

    void setMeleeDelay(float var1) {
      this.meleeDelay = Math.max(var1, 0.0F);
   }

    float getRecoilDelay() {
      return this.RecoilDelay;
   }

    void setRecoilDelay(float var1) {
      if (var1 < 0.0F) {
         var1 = 0.0F;
      }

      this.RecoilDelay = var1;
   }

    float getBeenMovingFor() {
      return this.BeenMovingFor;
   }

    void setBeenMovingFor(float var1) {
      if (var1 < 0.0F) {
         var1 = 0.0F;
      }

      if (var1 > 70.0F) {
         var1 = 70.0F;
      }

      this.BeenMovingFor = var1;
   }

    bool isForceShove() {
      return this.forceShove;
   }

    void setForceShove(bool var1) {
      this.forceShove = var1;
   }

    std::string getClickSound() {
      return this.clickSound;
   }

    void setClickSound(const std::string& var1) {
      this.clickSound = var1;
   }

    int getMeleeCombatMod() {
    int var1 = this.getWeaponLevel();
      if (var1 == 1) {
         return -2;
      } else if (var1 == 2) {
    return 0;
      } else if (var1 == 3) {
    return 1;
      } else if (var1 == 4) {
    return 2;
      } else if (var1 == 5) {
    return 3;
      } else if (var1 == 6) {
    return 4;
      } else if (var1 == 7) {
    return 5;
      } else if (var1 == 8) {
    return 5;
      } else if (var1 == 9) {
    return 6;
      } else {
    return var1 = = 10 ? 7 : -5;
      }
   }

    int getWeaponLevel() {
    WeaponType var1 = WeaponType.getWeaponType(this);
    int var2 = -1;
      if (var1 != nullptr && var1 != WeaponType.barehand) {
         if (((HandWeapon)this.getPrimaryHandItem()).getCategories().contains("Axe")) {
            var2 = this.getPerkLevel(Perks.Axe);
         }

         if (((HandWeapon)this.getPrimaryHandItem()).getCategories().contains("Spear")) {
            var2 += this.getPerkLevel(Perks.Spear);
         }

         if (((HandWeapon)this.getPrimaryHandItem()).getCategories().contains("SmallBlade")) {
            var2 += this.getPerkLevel(Perks.SmallBlade);
         }

         if (((HandWeapon)this.getPrimaryHandItem()).getCategories().contains("LongBlade")) {
            var2 += this.getPerkLevel(Perks.LongBlade);
         }

         if (((HandWeapon)this.getPrimaryHandItem()).getCategories().contains("Blunt")) {
            var2 += this.getPerkLevel(Perks.Blunt);
         }

         if (((HandWeapon)this.getPrimaryHandItem()).getCategories().contains("SmallBlunt")) {
            var2 += this.getPerkLevel(Perks.SmallBlunt);
         }
      }

    return var2 = = -1 ? 0 : var2;
   }

    int getMaintenanceMod() {
    int var1 = this.getPerkLevel(Perks.Maintenance);
      var1 += this.getWeaponLevel() / 2;
      return var1 / 2;
   }

    BaseVehicle getVehicle() {
      return this.vehicle;
   }

    void setVehicle(BaseVehicle var1) {
      this.vehicle = var1;
   }

    bool isUnderVehicle() {
    int var1 = ((int)this.x - 4) / 10;
    int var2 = ((int)this.y - 4) / 10;
    int var3 = (int)Math.ceil((this.x + 4.0F) / 10.0F);
    int var4 = (int)Math.ceil((this.y + 4.0F) / 10.0F);
    Vector2 var5 = (Vector2)((Vector2ObjectPool)BaseVehicle.TL_vector2_pool.get()).alloc();

      for (int var6 = var2; var6 < var4; var6++) {
         for (int var7 = var1; var7 < var3; var7++) {
            IsoChunk var8 = GameServer.bServer
               ? ServerMap.instance.getChunk(var7, var6)
               : IsoWorld.instance.CurrentCell.getChunkForGridSquare(var7 * 10, var6 * 10, 0);
            if (var8 != nullptr) {
               for (int var9 = 0; var9 < var8.vehicles.size(); var9++) {
    BaseVehicle var10 = (BaseVehicle)var8.vehicles.get(var9);
    Vector2 var11 = var10.testCollisionWithCharacter(this, 0.3F, var5);
                  if (var11 != nullptr && var11.x != -1.0F) {
                     ((Vector2ObjectPool)BaseVehicle.TL_vector2_pool.get()).release(var5);
    return true;
                  }
               }
            }
         }
      }

      ((Vector2ObjectPool)BaseVehicle.TL_vector2_pool.get()).release(var5);
    return false;
   }

    bool isProne() {
      return this.isOnFloor();
   }

    bool isBeingSteppedOn() {
      if (!this.isOnFloor()) {
    return false;
      } else {
         for (int var1 = -1; var1 <= 1; var1++) {
            for (int var2 = -1; var2 <= 1; var2++) {
    IsoGridSquare var3 = this.getCell().getGridSquare((int)this.x + var2, (int)this.y + var1, (int)this.z);
               if (var3 != nullptr) {
    std::vector var4 = var3.getMovingObjects();

                  for (int var5 = 0; var5 < var4.size(); var5++) {
    IsoMovingObject var6 = (IsoMovingObject)var4.get(var5);
                     if (var6 != this) {
    IsoGameCharacter var7 = (IsoGameCharacter)Type.tryCastTo(var6, IsoGameCharacter.class);
                        if (var7 != nullptr && var7.getVehicle() == nullptr && !var6.isOnFloor() && ZombieOnGroundState.isCharacterStandingOnOther(var7, this)) {
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
      return this.getBodyDamage().getTemperature();
   }

    void setTemperature(float var1) {
      this.getBodyDamage().setTemperature(var1);
   }

    float getReduceInfectionPower() {
      return this.reduceInfectionPower;
   }

    void setReduceInfectionPower(float var1) {
      this.reduceInfectionPower = var1;
   }

    float getInventoryWeight() {
      if (this.getInventory() == nullptr) {
         return 0.0F;
      } else {
    float var1 = 0.0F;
    std::vector var2 = this.getInventory().getItems();

         for (int var3 = 0; var3 < var2.size(); var3++) {
    InventoryItem var4 = (InventoryItem)var2.get(var3);
            if (var4.getAttachedSlot() > -1 && !this.isEquipped(var4)) {
               var1 += var4.getHotbarEquippedWeight();
            } else if (this.isEquipped(var4)) {
               var1 += var4.getEquippedWeight();
            } else {
               var1 += var4.getUnequippedWeight();
            }
         }

    return var1;
      }
   }

    void dropHandItems() {
      if (!"Tutorial" == Core.GameMode)) {
         if (!(dynamic_cast<IsoPlayer*>(this) != nullptr) || ((IsoPlayer)this).isLocalPlayer()) {
            this.dropHeavyItems();
    IsoGridSquare var1 = this.getCurrentSquare();
            if (var1 != nullptr) {
    InventoryItem var2 = this.getPrimaryHandItem();
    InventoryItem var3 = this.getSecondaryHandItem();
               if (var2 != nullptr || var3 != nullptr) {
                  var1 = this.getSolidFloorAt(var1.x, var1.y, var1.z);
                  if (var1 != nullptr) {
    float var4 = Rand.Next(0.1F, 0.9F);
    float var5 = Rand.Next(0.1F, 0.9F);
    float var6 = var1.getApparentZ(var4, var5) - var1.getZ();
    bool var7 = false;
                     if (var3 == var2) {
                        var7 = true;
                     }

                     if (var2 != nullptr) {
                        this.setPrimaryHandItem(nullptr);
                        this.getInventory().DoRemoveItem(var2);
                        var1.AddWorldInventoryItem(var2, var4, var5, var6);
                        LuaEventManager.triggerEvent("OnContainerUpdate");
                        LuaEventManager.triggerEvent("onItemFall", var2);
                     }

                     if (var3 != nullptr) {
                        this.setSecondaryHandItem(nullptr);
                        if (!var7) {
                           this.getInventory().DoRemoveItem(var3);
                           var1.AddWorldInventoryItem(var3, var4, var5, var6);
                           LuaEventManager.triggerEvent("OnContainerUpdate");
                           LuaEventManager.triggerEvent("onItemFall", var3);
                        }
                     }

                     this.resetEquippedHandsModels();
                  }
               }
            }
         }
      }
   }

    bool shouldBecomeZombieAfterDeath() {
      switch (SandboxOptions.instance.Lore.Transmission.getValue()) {
         case 1:
            return !this.getBodyDamage().IsFakeInfected() && this.getBodyDamage().getInfectionLevel() >= 0.001F;
         case 2:
            return !this.getBodyDamage().IsFakeInfected() && this.getBodyDamage().getInfectionLevel() >= 0.001F;
         case 3:
    return true;
         case 4:
    return false;
         default:
    return false;
      }
   }

    void applyTraits(std::vector<std::string> var1) {
      if (var1 != nullptr) {
    std::unordered_map var2 = new std::unordered_map();
         var2.put(Perks.Fitness, 5);
         var2.put(Perks.Strength, 5);

         for (int var3 = 0; var3 < var1.size(); var3++) {
    std::string var4 = (std::string)var1.get(var3);
            if (var4 != nullptr && !var4.empty()) {
    Trait var5 = TraitFactory.getTrait(var4);
               if (var5 != nullptr) {
                  if (!this.HasTrait(var4)) {
                     this.getTraits().push_back(var4);
                  }

    std::unordered_map var6 = var5.getXPBoostMap();
                  if (var6 != nullptr) {
                     for (Entry var8 : var6.entrySet()) {
    Perk var9 = (Perk)var8.getKey();
    int var10 = (int)var8.getValue();
                        if (var2.containsKey(var9)) {
                           var10 += var2.get(var9);
                        }

                        var2.put(var9, var10);
                     }
                  }
               }
            }
         }

         if (dynamic_cast<IsoPlayer*>(this) != nullptr) {
            ((IsoPlayer)this).getNutrition().applyWeightFromTraits();
         }

    std::unordered_map var11 = this.getDescriptor().getXPBoostMap();

         for (Entry var14 : var11.entrySet()) {
    Perk var16 = (Perk)var14.getKey();
    int var18 = (int)var14.getValue();
            if (var2.containsKey(var16)) {
               var18 += var2.get(var16);
            }

            var2.put(var16, var18);
         }

         for (Entry var15 : var2.entrySet()) {
    Perk var17 = (Perk)var15.getKey();
    int var19 = (int)var15.getValue();
            var19 = Math.max(0, var19);
            var19 = Math.min(10, var19);
            this.getDescriptor().getXPBoostMap().put(var17, Math.min(3, var19));

            for (int var22 = 0; var22 < var19; var22++) {
               this.LevelPerk(var17);
            }

            this.getXp().setXPToLevel(var17, this.getPerkLevel(var17));
         }
      }
   }

    void createKeyRing() {
    InventoryItem var1 = this.getInventory().AddItem("Base.KeyRing");
      if (var1 != nullptr && dynamic_cast<InventoryContainer*>(var1) != nullptr var2) {
         var2.setName(Translator.getText("IGUI_KeyRingName", this.getDescriptor().getForename(), this.getDescriptor().getSurname()));
         if (Rand.Next(100) < 40) {
    RoomDef var3 = IsoWorld.instance.MetaGrid.getRoomAt((int)this.getX(), (int)this.getY(), (int)this.getZ());
            if (var3 != nullptr && var3.getBuilding() != nullptr) {
    std::string var4 = "Base.Key" + (Rand.Next(5) + 1);
    InventoryItem var5 = var2.getInventory().AddItem(var4);
               var5.setKeyId(var3.getBuilding().getKeyId());
            }
         }
      }
   }

    void autoDrink() {
      if (!GameServer.bServer) {
         if (!GameClient.bClient || ((IsoPlayer)this).isLocalPlayer()) {
            if (Core.getInstance().getOptionAutoDrink()) {
               if (!LuaHookManager.TriggerHook("AutoDrink", this)) {
                  if (!(this.stats.thirst <= 0.1F)) {
    InventoryItem var1 = this.getWaterSource(this.getInventory().getItems());
                     if (var1 != nullptr) {
                        this.stats.thirst -= 0.1F;
                        if (GameClient.bClient) {
                           GameClient.instance.drink((IsoPlayer)this, 0.1F);
                        }

                        var1.Use();
                     }
                  }
               }
            }
         }
      }
   }

    InventoryItem getWaterSource(std::vector<InventoryItem> var1) {
    InventoryItem var2 = nullptr;
    new std::vector();

      for (int var4 = 0; var4 < var1.size(); var4++) {
    InventoryItem var5 = (InventoryItem)var1.get(var4);
         if (var5.isWaterSource() && !var5.isBeingFilled() && !var5.isTaintedWater()) {
            if (dynamic_cast<Drainable*>(var5) != nullptr) {
               if (((Drainable)var5).getUsedDelta() > 0.0F) {
                  var2 = var5;
                  break;
               }
            } else if (!(dynamic_cast<InventoryContainer*>(var5) != nullptr)) {
               var2 = var5;
               break;
            }
         }
      }

    return var2;
   }

   public List<std::string> getKnownRecipes() {
      return this.knownRecipes;
   }

    bool isRecipeKnown(Recipe var1) {
      return DebugOptions.instance.CheatRecipeKnowAll.getValue() ? true : !var1.needToBeLearn() || this.getKnownRecipes().contains(var1.getOriginalname());
   }

    bool isRecipeKnown(const std::string& var1) {
    Recipe var2 = ScriptManager.instance.getRecipe(var1);
      if (var2 == nullptr) {
         return DebugOptions.instance.CheatRecipeKnowAll.getValue() ? true : this.getKnownRecipes().contains(var1);
      } else {
         return this.isRecipeKnown(var2);
      }
   }

    bool learnRecipe(const std::string& var1) {
      if (!this.isRecipeKnown(var1)) {
         this.getKnownRecipes().push_back(var1);
    return true;
      } else {
    return false;
      }
   }

    void addKnownMediaLine(const std::string& var1) {
      if (!StringUtils.isNullOrWhitespace(var1)) {
         this.knownMediaLines.push_back(var1.trim());
      }
   }

    void removeKnownMediaLine(const std::string& var1) {
      if (!StringUtils.isNullOrWhitespace(var1)) {
         this.knownMediaLines.remove(var1.trim());
      }
   }

    void clearKnownMediaLines() {
      this.knownMediaLines.clear();
   }

    bool isKnownMediaLine(const std::string& var1) {
      return StringUtils.isNullOrWhitespace(var1) ? false : this.knownMediaLines.contains(var1.trim());
   }

    void saveKnownMediaLines(ByteBuffer var1) {
      var1.putShort((short)this.knownMediaLines.size());

      for (std::string var3 : this.knownMediaLines) {
         GameWindow.WriteStringUTF(var1, var3);
      }
   }

    void loadKnownMediaLines(ByteBuffer var1, int var2) {
      this.knownMediaLines.clear();
    short var3 = var1.getShort();

      for (int var4 = 0; var4 < var3; var4++) {
    std::string var5 = GameWindow.ReadStringUTF(var1);
         this.knownMediaLines.push_back(var5);
      }
   }

    bool isMoving() {
      return dynamic_cast<IsoPlayer*>(this) != nullptr && !((IsoPlayer)this).isAttackAnimThrowTimeOut() ? false : this.m_isMoving;
   }

    bool isBehaviourMoving() {
    State var1 = this.getCurrentState();
      return var1 != nullptr && var1.isMoving(this);
   }

    bool isPlayerMoving() {
    return false;
   }

    void setMoving(bool var1) {
      this.m_isMoving = var1;
      if (GameClient.bClient && dynamic_cast<IsoPlayer*>(this) != nullptr && ((IsoPlayer)this).bRemote) {
         ((IsoPlayer)this).m_isPlayerMoving = var1;
         ((IsoPlayer)this).setJustMoved(var1);
      }
   }

    bool isFacingNorthWesterly() {
      return this.dir == IsoDirections.W || this.dir == IsoDirections.NW || this.dir == IsoDirections.N || this.dir == IsoDirections.NE;
   }

    bool isAttacking() {
    return false;
   }

    bool isZombieAttacking() {
    return false;
   }

    bool isZombieAttacking(IsoMovingObject var1) {
    return false;
   }

    bool isZombieThumping() {
      return this.isZombie() ? this.getCurrentState() == ThumpState.instance() : false;
   }

    int compareMovePriority(IsoGameCharacter var1) {
      if (var1 == nullptr) {
    return 1;
      } else if (this.isZombieThumping() && !var1.isZombieThumping()) {
    return 1;
      } else if (!this.isZombieThumping() && var1.isZombieThumping()) {
         return -1;
      } else if (dynamic_cast<IsoPlayer*>(var1) != nullptr) {
         return GameClient.bClient && this.isZombieAttacking(var1) ? -1 : 0;
      } else if (this.isZombieAttacking() && !var1.isZombieAttacking()) {
    return 1;
      } else if (!this.isZombieAttacking() && var1.isZombieAttacking()) {
         return -1;
      } else if (this.isBehaviourMoving() && !var1.isBehaviourMoving()) {
    return 1;
      } else if (!this.isBehaviourMoving() && var1.isBehaviourMoving()) {
         return -1;
      } else if (this.isFacingNorthWesterly() && !var1.isFacingNorthWesterly()) {
    return 1;
      } else {
         return !this.isFacingNorthWesterly() && var1.isFacingNorthWesterly() ? -1 : 0;
      }
   }

    long playSound(const std::string& var1) {
      return this.getEmitter().playSound(var1);
   }

    long playSoundLocal(const std::string& var1) {
      return this.getEmitter().playSoundImpl(var1, nullptr);
   }

    void stopOrTriggerSound(long var1) {
      this.getEmitter().stopOrTriggerSound(var1);
   }

    void addWorldSoundUnlessInvisible(int var1, int var2, bool var3) {
      if (!this.isInvisible()) {
         WorldSoundManager.instance.addSound(this, (int)this.getX(), (int)this.getY(), (int)this.getZ(), var1, var2, var3);
      }
   }

    bool isKnownPoison(InventoryItem var1) {
      if (var1.hasTag("NoDetect")) {
    return false;
      } else if (dynamic_cast<Food*>(var1) != nullptr var2) {
         if (var2.getPoisonPower() <= 0) {
    return false;
         } else if (var2.getHerbalistType() != nullptr && !var2.getHerbalistType().empty()) {
            return this.isRecipeKnown("Herbalist");
         } else {
            return var2.getPoisonDetectionLevel() >= 0 && this.getPerkLevel(Perks.Cooking) >= 10 - var2.getPoisonDetectionLevel()
               ? true
               : var2.getPoisonLevelForRecipe() != nullptr;
         }
      } else {
    return false;
      }
   }

    int getLastHourSleeped() {
      return this.lastHourSleeped;
   }

    void setLastHourSleeped(int var1) {
      this.lastHourSleeped = var1;
   }

    void setTimeOfSleep(float var1) {
      this.timeOfSleep = var1;
   }

    void setDelayToSleep(float var1) {
      this.delayToActuallySleep = var1;
   }

    std::string getBedType() {
      return this.bedType;
   }

    void setBedType(const std::string& var1) {
      this.bedType = var1;
   }

    void enterVehicle(BaseVehicle var1, int var2, Vector3f var3) {
      if (this.vehicle != nullptr) {
         this.vehicle.exit(this);
      }

      if (var1 != nullptr) {
         var1.enter(var2, this, var3);
      }
   }

    float Hit(BaseVehicle var1, float var2, bool var3, float var4, float var5) {
      this.setHitFromBehind(var3);
      if (GameClient.bClient) {
         this.setAttackedBy((IsoGameCharacter)GameClient.IDToPlayerMap.get(var1.getNetPlayerId()));
      } else if (GameServer.bServer) {
         this.setAttackedBy((IsoGameCharacter)GameServer.IDToPlayerMap.get(var1.getNetPlayerId()));
      } else {
         this.setAttackedBy(var1.getDriver());
      }

      this.getHitDir().set(var4, var5);
      if (!this.isKnockedDown()) {
         this.setHitForce(Math.max(0.5F, var2 * 0.15F));
      } else {
         this.setHitForce(Math.min(2.5F, var2 * 0.15F));
      }

      if (GameClient.bClient) {
         HitReactionNetworkAI.CalcHitReactionVehicle(this, var1);
      }

      DebugLog.Damage
         .noise(
            "Vehicle id=%d hit %s id=%d: speed=%f force=%f hitDir=%s",
            var1.getId(),
            this.getClass().getSimpleName(),
            this.getOnlineID(),
            var2,
            this.getHitForce(),
            this.getHitDir()
         );
      return this.getHealth();
   }

    Path getPath2() {
      return this.path2;
   }

    void setPath2(Path var1) {
      this.path2 = var1;
   }

    PathFindBehavior2 getPathFindBehavior2() {
      return this.pfb2;
   }

    MapKnowledge getMapKnowledge() {
      return this.mapKnowledge;
   }

    IsoObject getBed() {
      return this.isAsleep() ? this.bed : nullptr;
   }

    void setBed(IsoObject var1) {
      this.bed = var1;
   }

    bool avoidDamage() {
      return this.m_avoidDamage;
   }

    void setAvoidDamage(bool var1) {
      this.m_avoidDamage = var1;
   }

    bool isReading() {
      return this.isReading;
   }

    void setReading(bool var1) {
      this.isReading = var1;
   }

    float getTimeSinceLastSmoke() {
      return this.timeSinceLastSmoke;
   }

    void setTimeSinceLastSmoke(float var1) {
      this.timeSinceLastSmoke = PZMath.clamp(var1, 0.0F, 10.0F);
   }

    bool isInvisible() {
      return this.m_invisible;
   }

    void setInvisible(bool var1) {
      this.m_invisible = var1;
   }

    bool isDriving() {
      return this.getVehicle() != nullptr && this.getVehicle().getDriver() == this && !this.getVehicle().isStopped();
   }

    bool isInARoom() {
      return this.square != nullptr && this.square.isInARoom();
   }

    bool isGodMod() {
      return this.m_godMod;
   }

    void setGodMod(bool var1) {
      if (!this.isDead()) {
         this.m_godMod = var1;
         if (dynamic_cast<IsoPlayer*>(this) != nullptr && GameClient.bClient && ((IsoPlayer)this).isLocalPlayer()) {
            this.updateMovementRates();
            GameClient.sendPlayerInjuries((IsoPlayer)this);
            GameClient.sendPlayerDamage((IsoPlayer)this);
         }
      }
   }

    bool isUnlimitedCarry() {
      return this.unlimitedCarry;
   }

    void setUnlimitedCarry(bool var1) {
      this.unlimitedCarry = var1;
   }

    bool isBuildCheat() {
      return this.buildCheat;
   }

    void setBuildCheat(bool var1) {
      this.buildCheat = var1;
   }

    bool isFarmingCheat() {
      return this.farmingCheat;
   }

    void setFarmingCheat(bool var1) {
      this.farmingCheat = var1;
   }

    bool isHealthCheat() {
      return this.healthCheat;
   }

    void setHealthCheat(bool var1) {
      this.healthCheat = var1;
   }

    bool isMechanicsCheat() {
      return this.mechanicsCheat;
   }

    void setMechanicsCheat(bool var1) {
      this.mechanicsCheat = var1;
   }

    bool isMovablesCheat() {
      return this.movablesCheat;
   }

    void setMovablesCheat(bool var1) {
      this.movablesCheat = var1;
   }

    bool isTimedActionInstantCheat() {
      return this.timedActionInstantCheat;
   }

    void setTimedActionInstantCheat(bool var1) {
      this.timedActionInstantCheat = var1;
   }

    bool isTimedActionInstant() {
      return Core.bDebug && DebugOptions.instance.CheatTimedActionInstant.getValue() ? true : this.isTimedActionInstantCheat();
   }

    bool isShowAdminTag() {
      return this.showAdminTag;
   }

    void setShowAdminTag(bool var1) {
      this.showAdminTag = var1;
   }

    IAnimationVariableSlot getVariable(AnimationVariableHandle var1) {
      return this.getGameVariablesInternal().getVariable(var1);
   }

    IAnimationVariableSlot getVariable(const std::string& var1) {
      return this.getGameVariablesInternal().getVariable(var1);
   }

    IAnimationVariableSlot getOrCreateVariable(const std::string& var1) {
      return this.getGameVariablesInternal().getOrCreateVariable(var1);
   }

    void setVariable(IAnimationVariableSlot var1) {
      this.getGameVariablesInternal().setVariable(var1);
   }

    void setVariable(const std::string& var1, const std::string& var2) {
      this.getGameVariablesInternal().setVariable(var1, var2);
   }

    void setVariable(const std::string& var1, bool var2) {
      this.getGameVariablesInternal().setVariable(var1, var2);
   }

    void setVariable(const std::string& var1, float var2) {
      this.getGameVariablesInternal().setVariable(var1, var2);
   }

    void setVariable(const std::string& var1, zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackBool.CallbackGetStrongTyped var2) {
      this.getGameVariablesInternal().setVariable(var1, var2);
   }

   protected void setVariable(
      std::string var1, zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackBool.CallbackGetStrongTyped var2, CallbackSetStrongTyped var3
   ) {
      this.getGameVariablesInternal().setVariable(var1, var2, var3);
   }

    void setVariable(const std::string& var1, zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackString.CallbackGetStrongTyped var2) {
      this.getGameVariablesInternal().setVariable(var1, var2);
   }

   protected void setVariable(
      std::string var1,
      zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackString.CallbackGetStrongTyped var2,
      zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackString.CallbackSetStrongTyped var3
   ) {
      this.getGameVariablesInternal().setVariable(var1, var2, var3);
   }

    void setVariable(const std::string& var1, CallbackGetStrongTyped var2) {
      this.getGameVariablesInternal().setVariable(var1, var2);
   }

   protected void setVariable(
      std::string var1, CallbackGetStrongTyped var2, zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackFloat.CallbackSetStrongTyped var3
   ) {
      this.getGameVariablesInternal().setVariable(var1, var2, var3);
   }

    void setVariable(const std::string& var1, zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackInt.CallbackGetStrongTyped var2) {
      this.getGameVariablesInternal().setVariable(var1, var2);
   }

   protected void setVariable(
      std::string var1,
      zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackInt.CallbackGetStrongTyped var2,
      zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackInt.CallbackSetStrongTyped var3
   ) {
      this.getGameVariablesInternal().setVariable(var1, var2, var3);
   }

    void setVariable(const std::string& var1, bool var2, zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackBool.CallbackGetStrongTyped var3) {
      this.getGameVariablesInternal().setVariable(var1, var2, var3);
   }

   public void setVariable(
      std::string var1,
      boolean var2,
      zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackBool.CallbackGetStrongTyped var3,
      CallbackSetStrongTyped var4
   ) {
      this.getGameVariablesInternal().setVariable(var1, var2, var3, var4);
   }

    void setVariable(const std::string& var1, const std::string& var2, zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackString.CallbackGetStrongTyped var3) {
      this.getGameVariablesInternal().setVariable(var1, var2, var3);
   }

   public void setVariable(
      std::string var1,
      std::string var2,
      zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackString.CallbackGetStrongTyped var3,
      zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackString.CallbackSetStrongTyped var4
   ) {
      this.getGameVariablesInternal().setVariable(var1, var2, var3, var4);
   }

    void setVariable(const std::string& var1, float var2, CallbackGetStrongTyped var3) {
      this.getGameVariablesInternal().setVariable(var1, var2, var3);
   }

   public void setVariable(
      std::string var1,
      float var2,
      CallbackGetStrongTyped var3,
      zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackFloat.CallbackSetStrongTyped var4
   ) {
      this.getGameVariablesInternal().setVariable(var1, var2, var3, var4);
   }

    void setVariable(const std::string& var1, int var2, zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackInt.CallbackGetStrongTyped var3) {
      this.getGameVariablesInternal().setVariable(var1, var2, var3);
   }

   public void setVariable(
      std::string var1,
      int var2,
      zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackInt.CallbackGetStrongTyped var3,
      zombie.core.skinnedmodel.advancedanimation.AnimationVariableSlotCallbackInt.CallbackSetStrongTyped var4
   ) {
      this.getGameVariablesInternal().setVariable(var1, var2, var3, var4);
   }

    void clearVariable(const std::string& var1) {
      this.getGameVariablesInternal().clearVariable(var1);
   }

    void clearVariables() {
      this.getGameVariablesInternal().clearVariables();
   }

    std::string getVariableString(const std::string& var1) {
      return this.getGameVariablesInternal().getVariableString(var1);
   }

    std::string getFootInjuryType() {
      if (!(dynamic_cast<IsoPlayer*>(this) != nullptr)) {
         return "";
      } else {
    BodyPart var1 = this.getBodyDamage().getBodyPart(BodyPartType.Foot_L);
    BodyPart var2 = this.getBodyDamage().getBodyPart(BodyPartType.Foot_R);
         if (!this.bRunning) {
            if (var1.haveBullet()
               || var1.getBurnTime() > 5.0F
               || var1.bitten()
               || var1.deepWounded()
               || var1.isSplint()
               || var1.getFractureTime() > 0.0F
               || var1.haveGlass()) {
               return "leftheavy";
            }

            if (var2.haveBullet()
               || var2.getBurnTime() > 5.0F
               || var2.bitten()
               || var2.deepWounded()
               || var2.isSplint()
               || var2.getFractureTime() > 0.0F
               || var2.haveGlass()) {
               return "rightheavy";
            }
         }

         if (var1.getScratchTime() > 5.0F || var1.getCutTime() > 7.0F || var1.getBurnTime() > 0.0F) {
            return "leftlight";
         } else {
            return !(var2.getScratchTime() > 5.0F) && !(var2.getCutTime() > 7.0F) && !(var2.getBurnTime() > 0.0F) ? "" : "rightlight";
         }
      }
   }

    float getVariableFloat(const std::string& var1, float var2) {
      return this.getGameVariablesInternal().getVariableFloat(var1, var2);
   }

    bool getVariableBoolean(const std::string& var1) {
      return this.getGameVariablesInternal().getVariableBoolean(var1);
   }

    bool getVariableBoolean(const std::string& var1, bool var2) {
      return this.getGameVariablesInternal().getVariableBoolean(this.name, var2);
   }

    bool isVariable(const std::string& var1, const std::string& var2) {
      return this.getGameVariablesInternal().isVariable(var1, var2);
   }

    bool containsVariable(const std::string& var1) {
      return this.getGameVariablesInternal().containsVariable(var1);
   }

   public Iterable<IAnimationVariableSlot> getGameVariables() {
      return this.getGameVariablesInternal().getGameVariables();
   }

    AnimationVariableSource getGameVariablesInternal() {
      return this.m_PlaybackGameVariables != nullptr ? this.m_PlaybackGameVariables : this.m_GameVariables;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    AnimationVariableSource startPlaybackGameVariables() {
      if (this.m_PlaybackGameVariables != nullptr) {
         DebugLog.General.error("Error! PlaybackGameVariables is already active.");
         return this.m_PlaybackGameVariables;
      } else {
    AnimationVariableSource var1 = std::make_shared<AnimationVariableSource>();

         for (IAnimationVariableSlot var3 : this.getGameVariables()) {
    AnimationVariableType var4 = var3.getType();
            switch (1.$SwitchMap$zombie$core$skinnedmodel$advancedanimation$AnimationVariableType[var4.ordinal()]) {
               case 1:
                  var1.setVariable(var3.getKey(), var3.getValueString());
                  break;
               case 2:
                  var1.setVariable(var3.getKey(), var3.getValueFloat());
                  break;
               case 3:
                  var1.setVariable(var3.getKey(), var3.getValueBool());
               case 4:
                  break;
               default:
                  DebugLog.General.error("Error! Variable type not handled: %s", new Object[]{var4});
            }
         }

         this.m_PlaybackGameVariables = var1;
         return this.m_PlaybackGameVariables;
      }
   }

    void endPlaybackGameVariables(AnimationVariableSource var1) {
      if (this.m_PlaybackGameVariables != var1) {
         DebugLog.General.error("Error! Playback GameVariables do not match.");
      }

      this.m_PlaybackGameVariables = nullptr;
   }

    void playbackSetCurrentStateSnapshot(ActionStateSnapshot var1) {
      if (this.actionContext != nullptr) {
         this.actionContext.setPlaybackStateSnapshot(var1);
      }
   }

    ActionStateSnapshot playbackRecordCurrentStateSnapshot() {
      return this.actionContext == nullptr ? nullptr : this.actionContext.getPlaybackStateSnapshot();
   }

    std::string GetVariable(const std::string& var1) {
      return this.getVariableString(var1);
   }

    void SetVariable(const std::string& var1, const std::string& var2) {
      this.setVariable(var1, var2);
   }

    void ClearVariable(const std::string& var1) {
      this.clearVariable(var1);
   }

    void actionStateChanged(ActionContext var1) {
    std::vector var2 = L_actionStateChanged.stateNames;
      PZArrayUtil.listConvert(var1.getChildStates(), var2, var0 -> var0.name);
      this.advancedAnimator.SetState(var1.getCurrentStateName(), var2);

      try {
         this.stateMachine.activeStateChanged++;
    State var3 = this.m_stateUpdateLookup.get(var1.getCurrentStateName().toLowerCase());
         if (var3 == nullptr) {
            var3 = this.defaultState;
         }

    std::vector var4 = L_actionStateChanged.states;
         PZArrayUtil.listConvert(var1.getChildStates(), var4, this.m_stateUpdateLookup, (var0, var1x) -> (State)var1x.get(var0.name.toLowerCase()));
         this.stateMachine.changeState(var3, var4);
      } finally {
         this.stateMachine.activeStateChanged--;
      }
   }

    bool isFallOnFront() {
      return this.fallOnFront;
   }

    void setFallOnFront(bool var1) {
      this.fallOnFront = var1;
   }

    bool isHitFromBehind() {
      return this.hitFromBehind;
   }

    void setHitFromBehind(bool var1) {
      this.hitFromBehind = var1;
   }

    void reportEvent(const std::string& var1) {
      this.actionContext.reportEvent(var1);
   }

    void StartTimedActionAnim(const std::string& var1) {
      this.StartTimedActionAnim(var1, nullptr);
   }

    void StartTimedActionAnim(const std::string& var1, const std::string& var2) {
      this.reportEvent(var1);
      if (var2 != nullptr) {
         this.setVariable("TimedActionType", var2);
      }

      this.resetModelNextFrame();
   }

    void StopTimedActionAnim() {
      this.clearVariable("TimedActionType");
      this.reportEvent("Event_TA_Exit");
      this.resetModelNextFrame();
   }

    bool hasHitReaction() {
      return !StringUtils.isNullOrEmpty(this.getHitReaction());
   }

    std::string getHitReaction() {
      return this.hitReaction;
   }

    void setHitReaction(const std::string& var1) {
      this.hitReaction = var1;
   }

    void CacheEquipped() {
      this.cacheEquiped[0] = this.getPrimaryHandItem();
      this.cacheEquiped[1] = this.getSecondaryHandItem();
   }

    InventoryItem GetPrimaryEquippedCache() {
      return this.cacheEquiped[0] != nullptr && this.inventory.contains(this.cacheEquiped[0]) ? this.cacheEquiped[0] : nullptr;
   }

    InventoryItem GetSecondaryEquippedCache() {
      return this.cacheEquiped[1] != nullptr && this.inventory.contains(this.cacheEquiped[1]) ? this.cacheEquiped[1] : nullptr;
   }

    void ClearEquippedCache() {
      this.cacheEquiped[0] = nullptr;
      this.cacheEquiped[1] = nullptr;
   }

    bool isBehind(IsoGameCharacter var1) {
    Vector2 var2 = tempVector2_1.set(this.getX(), this.getY());
    Vector2 var3 = tempVector2_2.set(var1.getX(), var1.getY());
      var3.x = var3.x - var2.x;
      var3.y = var3.y - var2.y;
    Vector2 var4 = var1.getForwardDirection();
      var3.normalize();
      var4.normalize();
    float var5 = var3.dot(var4);
      return var5 > 0.6;
   }

    void resetEquippedHandsModels() {
      if (!GameServer.bServer || ServerGUI.isCreated()) {
         if (this.hasActiveModel()) {
            ModelManager.instance.ResetEquippedNextFrame(this);
         }
      }
   }

    AnimatorDebugMonitor getDebugMonitor() {
      return this.advancedAnimator.getDebugMonitor();
   }

    void setDebugMonitor(AnimatorDebugMonitor var1) {
      this.advancedAnimator.setDebugMonitor(var1);
   }

    bool isAimAtFloor() {
      return this.bAimAtFloor;
   }

    void setAimAtFloor(bool var1) {
      this.bAimAtFloor = var1;
   }

    std::string testDotSide(IsoMovingObject var1) {
    Vector2 var2 = this.getLookVector(l_testDotSide.v1);
    Vector2 var3 = l_testDotSide.v2.set(this.getX(), this.getY());
    Vector2 var4 = l_testDotSide.v3.set(var1.x - var3.x, var1.y - var3.y);
      var4.normalize();
    float var5 = Vector2.dot(var4.x, var4.y, var2.x, var2.y);
      if (var5 > 0.7) {
         return "FRONT";
      } else if (var5 < 0.0F && var5 < -0.5) {
         return "BEHIND";
      } else {
    float var6 = var1.x;
    float var7 = var1.y;
    float var8 = var3.x;
    float var9 = var3.y;
    float var10 = var3.x + var2.x;
    float var11 = var3.y + var2.y;
    float var12 = (var6 - var8) * (var11 - var9) - (var7 - var9) * (var10 - var8);
         return var12 > 0.0F ? "RIGHT" : "LEFT";
      }
   }

    void addBasicPatch(BloodBodyPartType var1) {
      if (dynamic_cast<IHumanVisual*>(this) != nullptr) {
         if (var1 == nullptr) {
            var1 = BloodBodyPartType.FromIndex(Rand.Next(0, BloodBodyPartType.MAX.index()));
         }

    HumanVisual var2 = ((IHumanVisual)this).getHumanVisual();
         this.getItemVisuals(tempItemVisuals);
         BloodClothingType.addBasicPatch(var1, var2, tempItemVisuals);
         this.bUpdateModelTextures = true;
         this.bUpdateEquippedTextures = true;
         if (!GameServer.bServer && dynamic_cast<IsoPlayer*>(this) != nullptr && ((IsoPlayer)this).isLocalPlayer()) {
            LuaEventManager.triggerEvent("OnClothingUpdated", this);
         }
      }
   }

    bool addHole(BloodBodyPartType var1) {
      return this.addHole(var1, false);
   }

    bool addHole(BloodBodyPartType var1, bool var2) {
      if (!(dynamic_cast<IHumanVisual*>(this) != nullptr)) {
    return false;
      } else {
         if (var1 == nullptr) {
            var1 = BloodBodyPartType.FromIndex(OutfitRNG.Next(0, BloodBodyPartType.MAX.index()));
         }

    HumanVisual var3 = ((IHumanVisual)this).getHumanVisual();
         this.getItemVisuals(tempItemVisuals);
    bool var4 = BloodClothingType.addHole(var1, var3, tempItemVisuals, var2);
         this.bUpdateModelTextures = true;
         if (!GameServer.bServer && dynamic_cast<IsoPlayer*>(this) != nullptr && ((IsoPlayer)this).isLocalPlayer()) {
            LuaEventManager.triggerEvent("OnClothingUpdated", this);
            if (GameClient.bClient) {
               GameClient.instance.sendClothing((IsoPlayer)this, "", nullptr);
            }
         }

    return var4;
      }
   }

    void addDirt(BloodBodyPartType var1, int var2, bool var3) {
    HumanVisual var4 = ((IHumanVisual)this).getHumanVisual();
      if (var2 == nullptr) {
         var2 = OutfitRNG.Next(5, 10);
      }

    bool var5 = false;
      if (var1 == nullptr) {
         var5 = true;
      }

      this.getItemVisuals(tempItemVisuals);

      for (int var6 = 0; var6 < var2; var6++) {
         if (var5) {
            var1 = BloodBodyPartType.FromIndex(OutfitRNG.Next(0, BloodBodyPartType.MAX.index()));
         }

         BloodClothingType.addDirt(var1, var4, tempItemVisuals, var3);
      }

      this.bUpdateModelTextures = true;
      if (!GameServer.bServer && dynamic_cast<IsoPlayer*>(this) != nullptr && ((IsoPlayer)this).isLocalPlayer()) {
         LuaEventManager.triggerEvent("OnClothingUpdated", this);
      }
   }

    void addBlood(BloodBodyPartType var1, bool var2, bool var3, bool var4) {
    HumanVisual var5 = ((IHumanVisual)this).getHumanVisual();
    int var6 = 1;
    bool var7 = false;
      if (var1 == nullptr) {
         var7 = true;
      }

      if (this.getPrimaryHandItem() instanceof HandWeapon) {
         var6 = ((HandWeapon)this.getPrimaryHandItem()).getSplatNumber();
         if (OutfitRNG.Next(15) < this.getWeaponLevel()) {
            var6--;
         }
      }

      if (var3) {
         var6 = 20;
      }

      if (var2) {
         var6 = 5;
      }

      if (this.isZombie()) {
         var6 += 8;
      }

      this.getItemVisuals(tempItemVisuals);

      for (int var8 = 0; var8 < var6; var8++) {
         if (var7) {
            var1 = BloodBodyPartType.FromIndex(OutfitRNG.Next(0, BloodBodyPartType.MAX.index()));
            if (this.getPrimaryHandItem() != nullptr && this.getPrimaryHandItem() instanceof HandWeapon) {
    HandWeapon var9 = (HandWeapon)this.getPrimaryHandItem();
               if (var9.getBloodLevel() < 1.0F) {
    float var10 = var9.getBloodLevel() + 0.02F;
                  var9.setBloodLevel(var10);
                  this.bUpdateEquippedTextures = true;
               }
            }
         }

         BloodClothingType.addBlood(var1, var5, tempItemVisuals, var4);
      }

      this.bUpdateModelTextures = true;
      if (!GameServer.bServer && dynamic_cast<IsoPlayer*>(this) != nullptr && ((IsoPlayer)this).isLocalPlayer()) {
         LuaEventManager.triggerEvent("OnClothingUpdated", this);
      }
   }

    float getBodyPartClothingDefense(int var1, bool var2, bool var3) {
    float var4 = 0.0F;
      this.getItemVisuals(tempItemVisuals);

      for (int var5 = tempItemVisuals.size() - 1; var5 >= 0; var5--) {
    ItemVisual var6 = (ItemVisual)tempItemVisuals.get(var5);
    Item var7 = var6.getScriptItem();
         if (var7 != nullptr) {
    std::vector var8 = var7.getBloodClothingType();
            if (var8 != nullptr) {
    std::vector var9 = BloodClothingType.getCoveredParts(var8);
               if (var9 != nullptr) {
    InventoryItem var10 = var6.getInventoryItem();
                  if (var10 == nullptr) {
                     var10 = InventoryItemFactory.CreateItem(var6.getItemType());
                     if (var10 == nullptr) {
                        continue;
                     }
                  }

                  for (int var11 = 0; var11 < var9.size(); var11++) {
                     if (dynamic_cast<Clothing*>(var10) != nullptr
                        && ((BloodBodyPartType)var9.get(var11)).index() == var1
                        && var6.getHole((BloodBodyPartType)var9.get(var11)) == 0.0F) {
    Clothing var12 = (Clothing)var10;
                        var4 += var12.getDefForPart((BloodBodyPartType)var9.get(var11), var2, var3);
                        break;
                     }
                  }
               }
            }
         }
      }

      return Math.min(100.0F, var4);
   }

    bool isBumped() {
      return !StringUtils.isNullOrWhitespace(this.getBumpType());
   }

    bool isBumpDone() {
      return this.m_isBumpDone;
   }

    void setBumpDone(bool var1) {
      this.m_isBumpDone = var1;
   }

    bool isBumpFall() {
      return this.m_bumpFall;
   }

    void setBumpFall(bool var1) {
      this.m_bumpFall = var1;
   }

    bool isBumpStaggered() {
      return this.m_bumpStaggered;
   }

    void setBumpStaggered(bool var1) {
      this.m_bumpStaggered = var1;
   }

    std::string getBumpType() {
      return this.bumpType;
   }

    void setBumpType(const std::string& var1) {
      if (StringUtils.equalsIgnoreCase(this.bumpType, var1)) {
         this.bumpType = var1;
      } else {
    bool var2 = this.isBumped();
         this.bumpType = var1;
    bool var3 = this.isBumped();
         if (var3 != var2) {
            this.setBumpStaggered(var3);
         }
      }
   }

    std::string getBumpFallType() {
      return this.m_bumpFallType;
   }

    void setBumpFallType(const std::string& var1) {
      this.m_bumpFallType = var1;
   }

    IsoGameCharacter getBumpedChr() {
      return this.bumpedChr;
   }

    void setBumpedChr(IsoGameCharacter var1) {
      this.bumpedChr = var1;
   }

    long getLastBump() {
      return this.lastBump;
   }

    void setLastBump(long var1) {
      this.lastBump = var1;
   }

    bool isSitOnGround() {
      return this.sitOnGround;
   }

    void setSitOnGround(bool var1) {
      this.sitOnGround = var1;
   }

    std::string getUID() {
      return this.m_UID;
   }

   protected std::unordered_map<std::string, State> getStateUpdateLookup() {
      return this.m_stateUpdateLookup;
   }

    bool isRunning() {
      return this.getMoodles() != nullptr && this.getMoodles().getMoodleLevel(MoodleType.Endurance) >= 3 ? false : this.bRunning;
   }

    void setRunning(bool var1) {
      this.bRunning = var1;
   }

    bool isSprinting() {
      return this.bSprinting && !this.canSprint() ? false : this.bSprinting;
   }

    void setSprinting(bool var1) {
      this.bSprinting = var1;
   }

    bool canSprint() {
      if (dynamic_cast<IsoPlayer*>(this) != nullptr && !((IsoPlayer)this).isAllowSprint()) {
    return false;
      } else if ("Tutorial" == Core.GameMode)) {
    return true;
      } else {
    InventoryItem var1 = this.getPrimaryHandItem();
         if (var1 != nullptr && var1.isEquippedNoSprint()) {
    return false;
         } else {
            var1 = this.getSecondaryHandItem();
            return var1 != nullptr && var1.isEquippedNoSprint() ? false : this.getMoodles() == nullptr || this.getMoodles().getMoodleLevel(MoodleType.Endurance) < 2;
         }
      }
   }

    void postUpdateModelTextures() {
      this.bUpdateModelTextures = true;
   }

    ModelInstanceTextureCreator getTextureCreator() {
      return this.textureCreator;
   }

    void setTextureCreator(ModelInstanceTextureCreator var1) {
      this.textureCreator = var1;
   }

    void postUpdateEquippedTextures() {
      this.bUpdateEquippedTextures = true;
   }

   public std::vector<ModelInstance> getReadyModelData() {
      return this.readyModelData;
   }

    bool getIgnoreMovement() {
      return this.ignoreMovement;
   }

    void setIgnoreMovement(bool var1) {
      if (dynamic_cast<IsoPlayer*>(this) != nullptr && var1) {
         ((IsoPlayer)this).networkAI.needToUpdate();
      }

      this.ignoreMovement = var1;
   }

    bool isAutoWalk() {
      return this.bAutoWalk;
   }

    void setAutoWalk(bool var1) {
      this.bAutoWalk = var1;
   }

    void setAutoWalkDirection(Vector2 var1) {
      this.autoWalkDirection.set(var1);
   }

    Vector2 getAutoWalkDirection() {
      return this.autoWalkDirection;
   }

    bool isSneaking() {
      return this.getVariableFloat("WalkInjury", 0.0F) > 0.5F ? false : this.bSneaking;
   }

    void setSneaking(bool var1) {
      this.bSneaking = var1;
   }

    GameCharacterAIBrain getGameCharacterAIBrain() {
      return this.GameCharacterAIBrain;
   }

    float getMoveDelta() {
      return this.m_moveDelta;
   }

    void setMoveDelta(float var1) {
      this.m_moveDelta = var1;
   }

    float getTurnDelta() {
      if (this.isSprinting()) {
         return this.m_turnDeltaSprinting;
      } else {
         return this.isRunning() ? this.m_turnDeltaRunning : this.m_turnDeltaNormal;
      }
   }

    void setTurnDelta(float var1) {
      this.m_turnDeltaNormal = var1;
   }

    float getChopTreeSpeed() {
      return (this.Traits.Axeman.isSet() ? 1.25F : 1.0F) * GameTime.getAnimSpeedFix();
   }

    bool testDefense(IsoZombie var1) {
      if (this.testDotSide(var1) == "FRONT") && !var1.bCrawling && this.getSurroundingAttackingZombies() <= 3) {
    int var2 = 0;
         if ("KnifeDeath" == this.getVariableString("ZombieHitReaction"))) {
            var2 += 30;
         }

         var2 += this.getWeaponLevel() * 3;
         var2 += this.getPerkLevel(Perks.Fitness) * 2;
         var2 += this.getPerkLevel(Perks.Strength) * 2;
         var2 -= this.getSurroundingAttackingZombies() * 5;
         var2 -= this.getMoodles().getMoodleLevel(MoodleType.Endurance) * 2;
         var2 -= this.getMoodles().getMoodleLevel(MoodleType.HeavyLoad) * 2;
         var2 -= this.getMoodles().getMoodleLevel(MoodleType.Tired) * 3;
         if (SandboxOptions.instance.Lore.Strength.getValue() == 1) {
            var2 -= 7;
         }

         if (SandboxOptions.instance.Lore.Strength.getValue() == 3) {
            var2 += 7;
         }

         if (Rand.Next(100) < var2) {
            this.setAttackedBy(var1);
            this.setHitReaction(var1.getVariableString("PlayerHitReaction") + "Defended");
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
    IsoGridSquare var1 = this.getCurrentSquare();
      if (var1 == nullptr) {
    return 0;
      } else {
         movingStatic.addAll(var1.getMovingObjects());
         if (var1.n != nullptr) {
            movingStatic.addAll(var1.n.getMovingObjects());
         }

         if (var1.s != nullptr) {
            movingStatic.addAll(var1.s.getMovingObjects());
         }

         if (var1.e != nullptr) {
            movingStatic.addAll(var1.e.getMovingObjects());
         }

         if (var1.w != nullptr) {
            movingStatic.addAll(var1.w.getMovingObjects());
         }

         if (var1.nw != nullptr) {
            movingStatic.addAll(var1.nw.getMovingObjects());
         }

         if (var1.sw != nullptr) {
            movingStatic.addAll(var1.sw.getMovingObjects());
         }

         if (var1.se != nullptr) {
            movingStatic.addAll(var1.se.getMovingObjects());
         }

         if (var1.ne != nullptr) {
            movingStatic.addAll(var1.ne.getMovingObjects());
         }

    int var2 = 0;

         for (int var3 = 0; var3 < movingStatic.size(); var3++) {
    IsoZombie var4 = (IsoZombie)Type.tryCastTo(movingStatic.get(var3), IsoZombie.class);
            if (var4 != nullptr
               && var4.target == this
               && !(this.DistToSquared(var4) >= 0.80999994F)
               && (
                  var4.isCurrentState(AttackState.instance())
                     || var4.isCurrentState(AttackNetworkState.instance())
                     || var4.isCurrentState(LungeState.instance())
                     || var4.isCurrentState(LungeNetworkState.instance())
               )) {
               var2++;
            }
         }

    return var2;
      }
   }

    float checkIsNearWall() {
      if (this.bSneaking && this.getCurrentSquare() != nullptr) {
    IsoGridSquare var1 = this.getCurrentSquare().nav[IsoDirections.N.index()];
    IsoGridSquare var2 = this.getCurrentSquare().nav[IsoDirections.S.index()];
    IsoGridSquare var3 = this.getCurrentSquare().nav[IsoDirections.E.index()];
    IsoGridSquare var4 = this.getCurrentSquare().nav[IsoDirections.W.index()];
    float var5 = 0.0F;
    float var6 = 0.0F;
         if (var1 != nullptr) {
            var5 = var1.getGridSneakModifier(true);
            if (var5 > 1.0F) {
               this.setVariable("nearWallCrouching", true);
    return var5;
            }
         }

         if (var2 != nullptr) {
            var5 = var2.getGridSneakModifier(false);
            var6 = var2.getGridSneakModifier(true);
            if (var5 > 1.0F || var6 > 1.0F) {
               this.setVariable("nearWallCrouching", true);
               return var5 > 1.0F ? var5 : var6;
            }
         }

         if (var3 != nullptr) {
            var5 = var3.getGridSneakModifier(false);
            var6 = var3.getGridSneakModifier(true);
            if (var5 > 1.0F || var6 > 1.0F) {
               this.setVariable("nearWallCrouching", true);
               return var5 > 1.0F ? var5 : var6;
            }
         }

         if (var4 != nullptr) {
            var5 = var4.getGridSneakModifier(false);
            var6 = var4.getGridSneakModifier(true);
            if (var5 > 1.0F || var6 > 1.0F) {
               this.setVariable("nearWallCrouching", true);
               return var5 > 1.0F ? var5 : var6;
            }
         }

         var5 = this.getCurrentSquare().getGridSneakModifier(false);
         if (var5 > 1.0F) {
            this.setVariable("nearWallCrouching", true);
    return var5;
         } else if (dynamic_cast<IsoPlayer*>(this) != nullptr && ((IsoPlayer)this).isNearVehicle()) {
            this.setVariable("nearWallCrouching", true);
            return 6.0F;
         } else {
            this.setVariable("nearWallCrouching", false);
            return 0.0F;
         }
      } else {
         this.setVariable("nearWallCrouching", false);
         return 0.0F;
      }
   }

    float getBeenSprintingFor() {
      return this.BeenSprintingFor;
   }

    void setBeenSprintingFor(float var1) {
      if (var1 < 0.0F) {
         var1 = 0.0F;
      }

      if (var1 > 100.0F) {
         var1 = 100.0F;
      }

      this.BeenSprintingFor = var1;
   }

    bool isHideWeaponModel() {
      return this.hideWeaponModel;
   }

    void setHideWeaponModel(bool var1) {
      if (this.hideWeaponModel != var1) {
         this.hideWeaponModel = var1;
         this.resetEquippedHandsModels();
      }
   }

    void setIsAiming(bool var1) {
      if (this.ignoreAimingInput) {
         var1 = false;
      }

      if (dynamic_cast<IsoPlayer*>(this) != nullptr && !((IsoPlayer)this).isAttackAnimThrowTimeOut() || this.isAttackAnim() || this.getVariableBoolean("ShoveAnim")) {
         var1 = true;
      }

      this.isAiming = var1;
   }

    bool isAiming() {
      if (GameClient.bClient && dynamic_cast<IsoPlayer*>(this) != nullptr && ((IsoPlayer)this).isLocalPlayer() && DebugOptions.instance.MultiplayerAttackPlayer.getValue()) {
    return false;
      } else {
         return this.isNPC ? this.NPCGetAiming() : this.isAiming;
      }
   }

    void resetBeardGrowingTime() {
      this.beardGrowTiming = (float)this.getHoursSurvived();
      if (GameClient.bClient && dynamic_cast<IsoPlayer*>(this) != nullptr) {
         GameClient.instance.sendVisual((IsoPlayer)this);
      }
   }

    void resetHairGrowingTime() {
      this.hairGrowTiming = (float)this.getHoursSurvived();
      if (GameClient.bClient && dynamic_cast<IsoPlayer*>(this) != nullptr) {
         GameClient.instance.sendVisual((IsoPlayer)this);
      }
   }

    void fallenOnKnees() {
      if (!(dynamic_cast<IsoPlayer*>(this) != nullptr) || ((IsoPlayer)this).isLocalPlayer()) {
         if (!this.isInvincible()) {
            this.helmetFall(false);
    BloodBodyPartType var1 = BloodBodyPartType.FromIndex(Rand.Next(BloodBodyPartType.Hand_L.index(), BloodBodyPartType.Torso_Upper.index()));
            if (Rand.NextBool(2)) {
               var1 = BloodBodyPartType.FromIndex(Rand.Next(BloodBodyPartType.UpperLeg_L.index(), BloodBodyPartType.Back.index()));
            }

            for (int var2 = 0; var2 < 4; var2++) {
    BloodBodyPartType var3 = BloodBodyPartType.FromIndex(Rand.Next(BloodBodyPartType.Hand_L.index(), BloodBodyPartType.Torso_Upper.index()));
               if (Rand.NextBool(2)) {
                  var3 = BloodBodyPartType.FromIndex(Rand.Next(BloodBodyPartType.UpperLeg_L.index(), BloodBodyPartType.Back.index()));
               }

               this.addDirt(var3, Rand.Next(2, 6), false);
            }

            if (Rand.NextBool(2)) {
               if (Rand.NextBool(4)) {
                  this.dropHandItems();
               }

               this.addHole(var1);
               this.addBlood(var1, true, false, false);
    BodyPart var4 = this.getBodyDamage().getBodyPart(BodyPartType.FromIndex(var1.index()));
               if (var4.scratched()) {
                  var4.generateDeepWound();
               } else {
                  var4.setScratched(true, true);
               }
            }
         }
      }
   }

    void addVisualDamage(const std::string& var1) {
      this.addBodyVisualFromItemType("Base." + var1);
   }

    ItemVisual addBodyVisualFromItemType(const std::string& var1) {
    Item var2 = ScriptManager.instance.getItem(var1);
      return var2 != nullptr && !StringUtils.isNullOrWhitespace(var2.getClothingItem()) ? this.addBodyVisualFromClothingItemName(var2.getClothingItem()) : nullptr;
   }

    ItemVisual addBodyVisualFromClothingItemName(const std::string& var1) {
    IHumanVisual var2 = (IHumanVisual)Type.tryCastTo(this, IHumanVisual.class);
      if (var2 == nullptr) {
    return nullptr;
      } else {
    std::string var3 = ScriptManager.instance.getItemTypeForClothingItem(var1);
         if (var3 == nullptr) {
    return nullptr;
         } else {
    Item var4 = ScriptManager.instance.getItem(var3);
            if (var4 == nullptr) {
    return nullptr;
            } else {
    ClothingItem var5 = var4.getClothingItemAsset();
               if (var5 == nullptr) {
    return nullptr;
               } else {
    ClothingItemReference var6 = std::make_shared<ClothingItemReference>();
                  var6.itemGUID = var5.m_GUID;
                  var6.randomize();
    ItemVisual var7 = std::make_shared<ItemVisual>();
                  var7.setItemType(var3);
                  var7.synchWithOutfit(var6);
                  if (!this.isDuplicateBodyVisual(var7)) {
    ItemVisuals var8 = var2.getHumanVisual().getBodyVisuals();
                     var8.push_back(var7);
    return var7;
                  } else {
    return nullptr;
                  }
               }
            }
         }
      }
   }

    bool isDuplicateBodyVisual(ItemVisual var1) {
    IHumanVisual var2 = (IHumanVisual)Type.tryCastTo(this, IHumanVisual.class);
      if (var2 == nullptr) {
    return false;
      } else {
    ItemVisuals var3 = var2.getHumanVisual().getBodyVisuals();

         for (int var4 = 0; var4 < var3.size(); var4++) {
    ItemVisual var5 = (ItemVisual)var3.get(var4);
            if (var1.getClothingItemName() == var5.getClothingItemName())
               && var1.getTextureChoice() == var5.getTextureChoice()
               && var1.getBaseTexture() == var5.getBaseTexture()) {
    return true;
            }
         }

    return false;
      }
   }

    bool isCriticalHit() {
      return this.isCrit;
   }

    void setCriticalHit(bool var1) {
      this.isCrit = var1;
   }

    float getRunSpeedModifier() {
      return this.runSpeedModifier;
   }

    void startMuzzleFlash() {
    float var1 = GameTime.getInstance().getNight() * 0.8F;
      var1 = Math.max(var1, 0.2F);
    IsoLightSource var2 = std::make_shared<IsoLightSource>((int)this.getX(), (int)this.getY(), (int)this.getZ(), 0.8F * var1, 0.8F * var1, 0.6F * var1, 18, 6);
      IsoWorld.instance.CurrentCell.getLamppostPositions().push_back(var2);
      this.m_muzzleFlash = System.currentTimeMillis();
   }

    bool isMuzzleFlash() {
      return Core.bDebug && DebugOptions.instance.ModelRenderMuzzleflash.getValue() ? true : this.m_muzzleFlash > System.currentTimeMillis() - 50L;
   }

    bool isNPC() {
      return this.isNPC;
   }

    void setNPC(bool var1) {
      if (var1 && this.GameCharacterAIBrain == nullptr) {
         this.GameCharacterAIBrain = std::make_shared<GameCharacterAIBrain>(this);
      }

      this.isNPC = var1;
   }

    void NPCSetRunning(bool var1) {
      this.GameCharacterAIBrain.HumanControlVars.bRunning = var1;
   }

    bool NPCGetRunning() {
      return this.GameCharacterAIBrain.HumanControlVars.bRunning;
   }

    void NPCSetJustMoved(bool var1) {
      this.GameCharacterAIBrain.HumanControlVars.JustMoved = var1;
   }

    void NPCSetAiming(bool var1) {
      this.GameCharacterAIBrain.HumanControlVars.bAiming = var1;
   }

    bool NPCGetAiming() {
      return this.GameCharacterAIBrain.HumanControlVars.bAiming;
   }

    void NPCSetAttack(bool var1) {
      this.GameCharacterAIBrain.HumanControlVars.initiateAttack = var1;
   }

    void NPCSetMelee(bool var1) {
      this.GameCharacterAIBrain.HumanControlVars.bMelee = var1;
   }

    void setMetabolicTarget(Metabolics var1) {
      if (var1 != nullptr) {
         this.setMetabolicTarget(var1.getMet());
      }
   }

    void setMetabolicTarget(float var1) {
      if (this.getBodyDamage() != nullptr && this.getBodyDamage().getThermoregulator() != nullptr) {
         this.getBodyDamage().getThermoregulator().setMetabolicTarget(var1);
      }
   }

    double getThirstMultiplier() {
      return this.getBodyDamage() != nullptr && this.getBodyDamage().getThermoregulator() != nullptr
         ? this.getBodyDamage().getThermoregulator().getFluidsMultiplier()
         : 1.0;
   }

    double getHungerMultiplier() {
      return 1.0;
   }

    double getFatiqueMultiplier() {
      return this.getBodyDamage() != nullptr && this.getBodyDamage().getThermoregulator() != nullptr
         ? this.getBodyDamage().getThermoregulator().getFatigueMultiplier()
         : 1.0;
   }

    float getTimedActionTimeModifier() {
      return 1.0F;
   }

    bool addHoleFromZombieAttacks(BloodBodyPartType var1, bool var2) {
      this.getItemVisuals(tempItemVisuals);
    ItemVisual var3 = nullptr;

      for (int var4 = tempItemVisuals.size() - 1; var4 >= 0; var4--) {
    ItemVisual var5 = (ItemVisual)tempItemVisuals.get(var4);
    Item var6 = var5.getScriptItem();
         if (var6 != nullptr) {
    std::vector var7 = var6.getBloodClothingType();
            if (var7 != nullptr) {
    std::vector var8 = BloodClothingType.getCoveredParts(var7);

               for (int var9 = 0; var9 < var8.size(); var9++) {
    BloodBodyPartType var10 = (BloodBodyPartType)var8.get(var9);
                  if (var1 == var10) {
                     var3 = var5;
                     break;
                  }
               }

               if (var3 != nullptr) {
                  break;
               }
            }
         }
      }

    float var11 = 0.0F;
    bool var12 = false;
      if (var3 != nullptr && var3.getInventoryItem() != nullptr && var3.getInventoryItem() instanceof Clothing) {
    Clothing var13 = (Clothing)var3.getInventoryItem();
    ClothingPatch var15 = var13.getPatchType(var1);
         var11 = Math.max(30.0F, 100.0F - var13.getDefForPart(var1, !var2, false) / 1.5F);
      }

      if (Rand.Next(100) < var11) {
    bool var14 = this.addHole(var1);
         if (var14) {
            this.getEmitter().playSoundImpl("ZombieRipClothing", (IsoObject)nullptr);
         }

         var12 = true;
      }

    return var12;
   }

    void updateBandages() {
      s_bandages.update(this);
   }

    float getTotalBlood() {
    float var1 = 0.0F;
      if (this.getWornItems() == nullptr) {
    return var1;
      } else {
         for (int var2 = 0; var2 < this.getWornItems().size(); var2++) {
    InventoryItem var3 = this.getWornItems().get(var2).getItem();
            if (dynamic_cast<Clothing*>(var3) != nullptr) {
               var1 += ((Clothing)var3).getBloodlevel();
            }
         }

         return var1 + ((HumanVisual)this.getVisual()).getTotalBlood();
      }
   }

    void attackFromWindowsLunge(IsoZombie var1) {
      if (!(this.lungeFallTimer > 0.0F)
         && (int)this.getZ() == (int)var1.getZ()
         && !var1.isDead()
         && this.getCurrentSquare() != nullptr
         && !this.getCurrentSquare().isDoorBlockedTo(var1.getCurrentSquare())
         && !this.getCurrentSquare().isWallTo(var1.getCurrentSquare())
         && !this.getCurrentSquare().isWindowTo(var1.getCurrentSquare())) {
         if (this.getVehicle() == nullptr) {
    bool var2 = this.DoSwingCollisionBoneCheck(var1, var1.getAnimationPlayer().getSkinningBoneIndex("Bip01_R_Hand", -1), 1.0F);
            if (var2) {
               var1.playSound("ZombieCrawlLungeHit");
               this.lungeFallTimer = 200.0F;
               this.setIsAiming(false);
    bool var3 = false;
    int var4 = 30;
               var4 += this.getMoodles().getMoodleLevel(MoodleType.Endurance) * 3;
               var4 += this.getMoodles().getMoodleLevel(MoodleType.HeavyLoad) * 5;
               var4 -= this.getPerkLevel(Perks.Fitness) * 2;
    BodyPart var5 = this.getBodyDamage().getBodyPart(BodyPartType.Torso_Lower);
               if (var5.getAdditionalPain(true) > 20.0F) {
                  var4 = (int)(var4 + (var5.getAdditionalPain(true) - 20.0F) / 10.0F);
               }

               if (this.Traits.Clumsy.isSet()) {
                  var4 += 10;
               }

               if (this.Traits.Graceful.isSet()) {
                  var4 -= 10;
               }

               if (this.Traits.VeryUnderweight.isSet()) {
                  var4 += 20;
               }

               if (this.Traits.Underweight.isSet()) {
                  var4 += 10;
               }

               if (this.Traits.Obese.isSet()) {
                  var4 -= 10;
               }

               if (this.Traits.Overweight.isSet()) {
                  var4 -= 5;
               }

               var4 = Math.max(5, var4);
               this.clearVariable("BumpFallType");
               this.setBumpType("stagger");
               if (Rand.Next(100) < var4) {
                  var3 = true;
               }

               this.setBumpDone(false);
               this.setBumpFall(var3);
               if (var1.isBehind(this)) {
                  this.setBumpFallType("pushedBehind");
               } else {
                  this.setBumpFallType("pushedFront");
               }

               this.actionContext.reportEvent("wasBumped");
            }
         }
      }
   }

    bool DoSwingCollisionBoneCheck(IsoGameCharacter var1, int var2, float var3) {
      Model.BoneToWorldCoords(var1, var2, tempVectorBonePos);
    float var4 = IsoUtils.DistanceToSquared(tempVectorBonePos.x, tempVectorBonePos.y, this.x, this.y);
      return var4 < var3 * var3;
   }

    bool isInvincible() {
      return this.invincible;
   }

    void setInvincible(bool var1) {
      this.invincible = var1;
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
                        && (!(dynamic_cast<IsoPlayer*>(this) != nullptr) || !((IsoPlayer)this).isLocalPlayer() || var9.getTargetAlpha(((IsoPlayer)this).PlayerIndex) != 0.0F)
                        && !(this.DistToSquared((int)var9.x, (int)var9.y) >= 16.0F)) {
    return var9;
                     }
                  }
               }
            }
         }

    return nullptr;
      }
   }

    IsoGridSquare getSolidFloorAt(int var1, int var2, int var3) {
      while (var3 >= 0) {
    IsoGridSquare var4 = this.getCell().getGridSquare(var1, var2, var3);
         if (var4 != nullptr && var4.TreatAsSolidFloor()) {
    return var4;
         }

         var3--;
      }

    return nullptr;
   }

    void dropHeavyItems() {
    IsoGridSquare var1 = this.getCurrentSquare();
      if (var1 != nullptr) {
    InventoryItem var2 = this.getPrimaryHandItem();
    InventoryItem var3 = this.getSecondaryHandItem();
         if (var2 != nullptr || var3 != nullptr) {
            var1 = this.getSolidFloorAt(var1.x, var1.y, var1.z);
            if (var1 != nullptr) {
    bool var4 = var2 == var3;
               if (this.isHeavyItem(var2)) {
    float var5 = Rand.Next(0.1F, 0.9F);
    float var6 = Rand.Next(0.1F, 0.9F);
    float var7 = var1.getApparentZ(var5, var6) - var1.getZ();
                  this.setPrimaryHandItem(nullptr);
                  this.getInventory().DoRemoveItem(var2);
                  var1.AddWorldInventoryItem(var2, var5, var6, var7);
                  LuaEventManager.triggerEvent("OnContainerUpdate");
                  LuaEventManager.triggerEvent("onItemFall", var2);
               }

               if (this.isHeavyItem(var3)) {
                  this.setSecondaryHandItem(nullptr);
                  if (!var4) {
    float var9 = Rand.Next(0.1F, 0.9F);
    float var10 = Rand.Next(0.1F, 0.9F);
    float var11 = var1.getApparentZ(var9, var10) - var1.getZ();
                     this.getInventory().DoRemoveItem(var3);
                     var1.AddWorldInventoryItem(var3, var9, var10, var11);
                     LuaEventManager.triggerEvent("OnContainerUpdate");
                     LuaEventManager.triggerEvent("onItemFall", var3);
                  }
               }
            }
         }
      }
   }

    bool isHeavyItem(InventoryItem var1) {
      if (var1 == nullptr) {
    return false;
      } else if (dynamic_cast<InventoryContainer*>(var1) != nullptr) {
    return true;
      } else if (var1.hasTag("HeavyItem")) {
    return true;
      } else {
         return !var1.getType() == "CorpseMale") && !var1.getType() == "CorpseFemale") ? var1.getType() == "Generator") : true;
      }
   }

    bool isCanShout() {
      return this.canShout;
   }

    void setCanShout(bool var1) {
      this.canShout = var1;
   }

    bool isUnlimitedEndurance() {
      return this.unlimitedEndurance;
   }

    void setUnlimitedEndurance(bool var1) {
      this.unlimitedEndurance = var1;
   }

    void addActiveLightItem(InventoryItem var1, std::vector<InventoryItem> var2) {
      if (var1 != nullptr && var1.isEmittingLight() && !var2.contains(var1)) {
         var2.push_back(var1);
      }
   }

   public std::vector<InventoryItem> getActiveLightItems(std::vector<InventoryItem> var1) {
      this.addActiveLightItem(this.getSecondaryHandItem(), var1);
      this.addActiveLightItem(this.getPrimaryHandItem(), var1);
    AttachedItems var2 = this.getAttachedItems();

      for (int var3 = 0; var3 < var2.size(); var3++) {
    InventoryItem var4 = var2.getItemByIndex(var3);
         this.addActiveLightItem(var4, var1);
      }

    return var1;
   }

    SleepingEventData getOrCreateSleepingEventData() {
      if (this.m_sleepingEventData == nullptr) {
         this.m_sleepingEventData = std::make_unique<SleepingEventData>();
      }

      return this.m_sleepingEventData;
   }

    void playEmote(const std::string& var1) {
      this.setVariable("emote", var1);
      this.actionContext.reportEvent("EventEmote");
   }

    std::string getAnimationStateName() {
      return this.advancedAnimator.getCurrentStateName();
   }

    std::string getActionStateName() {
      return this.actionContext.getCurrentStateName();
   }

    bool shouldWaitToStartTimedAction() {
      if (this.isSitOnGround()) {
    AdvancedAnimator var1 = this.getAdvancedAnimator();
         if (var1.getRootLayer() == nullptr) {
    return false;
         } else if (var1.animSet != nullptr && var1.animSet.containsState("sitonground")) {
    AnimState var2 = var1.animSet.GetState("sitonground");
            if (!PZArrayUtil.contains(var2.m_Nodes, var0 -> "sit_action".equalsIgnoreCase(var0.m_Name))) {
    return false;
            } else {
               LiveAnimNode var3 = (LiveAnimNode)PZArrayUtil.find(
                  var1.getRootLayer().getLiveAnimNodes(), var0 -> var0.isActive() && "sit_action".equalsIgnoreCase(var0.getName())
               );
    return var3 = = nullptr || !var3.isMainAnimActive();
            }
         } else {
    return false;
         }
      } else {
    return false;
      }
   }

    void setPersistentOutfitID(int var1) {
      this.setPersistentOutfitID(var1, false);
   }

    void setPersistentOutfitID(int var1, bool var2) {
      this.m_persistentOutfitId = var1;
      this.m_bPersistentOutfitInit = var2;
   }

    int getPersistentOutfitID() {
      return this.m_persistentOutfitId;
   }

    bool isPersistentOutfitInit() {
      return this.m_bPersistentOutfitInit;
   }

    bool isDoingActionThatCanBeCancelled() {
    return false;
   }

    bool isDoDeathSound() {
      return this.doDeathSound;
   }

    void setDoDeathSound(bool var1) {
      this.doDeathSound = var1;
   }

    void updateEquippedRadioFreq() {
      this.invRadioFreq.clear();

      for (int var1 = 0; var1 < this.getInventory().getItems().size(); var1++) {
    InventoryItem var2 = (InventoryItem)this.getInventory().getItems().get(var1);
         if (dynamic_cast<Radio*>(var2) != nullptr var3
            && var3.getDeviceData() != nullptr
            && var3.getDeviceData().getIsTurnedOn()
            && !var3.getDeviceData().getMicIsMuted()
            && !this.invRadioFreq.contains(var3.getDeviceData().getChannel())) {
            this.invRadioFreq.push_back(var3.getDeviceData().getChannel());
         }
      }

      for (int var4 = 0; var4 < this.invRadioFreq.size(); var4++) {
         System.out.println(this.invRadioFreq.get(var4));
      }

      if (dynamic_cast<IsoPlayer*>(this) != nullptr && GameClient.bClient) {
         GameClient.sendEquippedRadioFreq((IsoPlayer)this);
      }
   }

    FMODParameterList getFMODParameters() {
      return this.fmodParameters;
   }

    void startEvent(long var1, GameSoundClip var3, BitSet var4) {
    FMODParameterList var5 = this.getFMODParameters();
    std::vector var6 = var3.eventDescription.parameters;

      for (int var7 = 0; var7 < var6.size(); var7++) {
    FMOD_STUDIO_PARAMETER_DESCRIPTION var8 = (FMOD_STUDIO_PARAMETER_DESCRIPTION)var6.get(var7);
         if (!var4.get(var8.globalIndex)) {
    FMODParameter var9 = var5.get(var8);
            if (var9 != nullptr) {
               var9.startEventInstance(var1);
            }
         }
      }
   }

    void updateEvent(long var1, GameSoundClip var3) {
   }

    void stopEvent(long var1, GameSoundClip var3, BitSet var4) {
    FMODParameterList var5 = this.getFMODParameters();
    std::vector var6 = var3.eventDescription.parameters;

      for (int var7 = 0; var7 < var6.size(); var7++) {
    FMOD_STUDIO_PARAMETER_DESCRIPTION var8 = (FMOD_STUDIO_PARAMETER_DESCRIPTION)var6.get(var7);
         if (!var4.get(var8.globalIndex)) {
    FMODParameter var9 = var5.get(var8);
            if (var9 != nullptr) {
               var9.stopEventInstance(var1);
            }
         }
      }
   }

    void playBloodSplatterSound() {
      if (this.getEmitter().isPlaying("BloodSplatter")) {
      }

      this.getEmitter().playSoundImpl("BloodSplatter", this);
   }

    void setIgnoreAimingInput(bool var1) {
      this.ignoreAimingInput = var1;
   }

    void addBlood(float var1) {
      if (!(Rand.Next(10) > var1)) {
         if (SandboxOptions.instance.BloodLevel.getValue() > 1) {
    int var2 = Rand.Next(4, 10);
            if (var2 < 1) {
               var2 = 1;
            }

            if (Core.bLastStand) {
               var2 *= 3;
            }

            switch (SandboxOptions.instance.BloodLevel.getValue()) {
               case 2:
                  var2 /= 2;
               case 3:
               default:
                  break;
               case 4:
                  var2 *= 2;
                  break;
               case 5:
                  var2 *= 5;
            }

            for (int var3 = 0; var3 < var2; var3++) {
               this.splatBlood(2, 0.3F);
            }
         }

         if (SandboxOptions.instance.BloodLevel.getValue() > 1) {
            this.splatBloodFloorBig();
            this.playBloodSplatterSound();
         }
      }
   }

    bool isKnockedDown() {
      return this.bKnockedDown;
   }

    void setKnockedDown(bool var1) {
      this.bKnockedDown = var1;
   }

    void writeInventory(ByteBuffer var1) {
    std::string var2 = this.isFemale() ? "inventoryfemale" : "inventorymale";
      GameWindow.WriteString(var1, var2);
      if (this.getInventory() != nullptr) {
         var1.put((byte)1);

         try {
    std::vector var3 = this.getInventory().save(var1);
    WornItems var5 = this.getWornItems();
            if (var5 == nullptr) {
    uint8_t var11 = 0;
               var1.put((byte)var11);
            } else {
    int var4 = var5.size();
               if (var4 > 127) {
                  DebugLog.Multiplayer.warn("Too many worn items");
                  var4 = 127;
               }

               var1.put((byte)var4);

               for (int var6 = 0; var6 < var4; var6++) {
    WornItem var7 = var5.get(var6);
                  GameWindow.WriteString(var1, var7.getLocation());
                  var1.putShort((short)var3.indexOf(var7.getItem()));
               }
            }

    AttachedItems var14 = this.getAttachedItems();
            if (var14 == nullptr) {
    bool var12 = false;
               var1.put((byte)0);
            } else {
    int var13 = var14.size();
               if (var13 > 127) {
                  DebugLog.Multiplayer.warn("Too many attached items");
                  var13 = 127;
               }

               var1.put((byte)var13);

               for (int var8 = 0; var8 < var13; var8++) {
    AttachedItem var9 = var14.get(var8);
                  GameWindow.WriteString(var1, var9.getLocation());
                  var1.putShort((short)var3.indexOf(var9.getItem()));
               }
            }
         } catch (IOException var10) {
            DebugLog.Multiplayer.printException(var10, "WriteInventory error for character " + this.getOnlineID(), LogSeverity.Error);
         }
      } else {
         var1.put((byte)0);
      }
   }

    std::string readInventory(ByteBuffer var1) {
    std::string var2 = GameWindow.ReadString(var1);
    bool var3 = var1.get() == 1;
      if (var3) {
         try {
    std::vector var4 = this.getInventory().load(var1, IsoWorld.getWorldVersion());
    uint8_t var5 = var1.get();

            for (int var6 = 0; var6 < var5; var6++) {
    std::string var7 = GameWindow.ReadStringUTF(var1);
    short var8 = var1.getShort();
               if (var8 >= 0 && var8 < var4.size() && this.getBodyLocationGroup().getLocation(var7) != nullptr) {
                  this.getWornItems().setItem(var7, (InventoryItem)var4.get(var8));
               }
            }

    uint8_t var11 = var1.get();

            for (int var12 = 0; var12 < var11; var12++) {
    std::string var13 = GameWindow.ReadStringUTF(var1);
    short var9 = var1.getShort();
               if (var9 >= 0 && var9 < var4.size() && this.getAttachedLocationGroup().getLocation(var13) != nullptr) {
                  this.getAttachedItems().setItem(var13, (InventoryItem)var4.get(var9));
               }
            }
         } catch (IOException var10) {
            DebugLog.Multiplayer.printException(var10, "ReadInventory error for character " + this.getOnlineID(), LogSeverity.Error);
         }
      }

    return var2;
   }

    void Kill(IsoGameCharacter var1) {
      DebugLog.Death.trace("id=%d", this.getOnlineID());
      this.setAttackedBy(var1);
      this.setHealth(0.0F);
      this.setOnKillDone(true);
   }

    bool shouldDoInventory() {
    return true;
   }

    void die() {
      if (!this.isOnDeathDone()) {
         if (GameClient.bClient) {
            if (this.shouldDoInventory()) {
               this.becomeCorpse();
            } else {
               this.getNetworkCharacterAI().processDeadBody();
            }
         } else {
            this.becomeCorpse();
         }
      }
   }

    void becomeCorpse() {
      DebugLog.Death.trace("id=%d", this.getOnlineID());
      this.Kill(this.getAttackedBy());
      this.setOnDeathDone(true);
   }

    bool shouldBecomeCorpse() {
      if (GameClient.bClient || GameServer.bServer) {
         if (this.getHitReactionNetworkAI().isSetup() || this.getHitReactionNetworkAI().isStarted()) {
    return false;
         }

         if (GameServer.bServer) {
            return this.getNetworkCharacterAI().isSetDeadBody();
         }

         if (GameClient.bClient) {
            return this.isCurrentState(ZombieOnGroundState.instance()) || this.isCurrentState(PlayerOnGroundState.instance());
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

    bool isVehicleCollisionActive(BaseVehicle var1) {
      if (!GameClient.bClient) {
    return false;
      } else if (!this.isAlive()) {
    return false;
      } else if (var1 == nullptr) {
    return false;
      } else if (!var1.shouldCollideWithCharacters()) {
    return false;
      } else if (var1.isNetPlayerAuthorization(Authorization.Server)) {
    return false;
      } else if (var1.isEngineRunning()
         || var1.getVehicleTowing() != nullptr && var1.getVehicleTowing().isEngineRunning()
         || var1.getVehicleTowedBy() != nullptr && var1.getVehicleTowedBy().isEngineRunning()) {
         if (var1.getDriver() != nullptr
            || var1.getVehicleTowing() != nullptr && var1.getVehicleTowing().getDriver() != nullptr
            || var1.getVehicleTowedBy() != nullptr && var1.getVehicleTowedBy().getDriver() != nullptr) {
            return Math.abs(var1.x - this.x) < 0.01F || Math.abs(var1.y - this.y) < 0.01F
               ? false
               : (!this.isKnockedDown() || this.isOnFloor()) && (this.getHitReactionNetworkAI() == nullptr || !this.getHitReactionNetworkAI().isStarted());
         } else {
    return false;
         }
      } else {
    return false;
      }
   }

    void doHitByVehicle(BaseVehicle var1, HitVars var2) {
      if (GameClient.bClient) {
    IsoPlayer var3 = (IsoPlayer)GameClient.IDToPlayerMap.get(var1.getNetPlayerId());
         if (var3 != nullptr) {
            if (var3.isLocal()) {
               SoundManager.instance.PlayWorldSound("VehicleHitCharacter", this.getCurrentSquare(), 0.0F, 20.0F, 0.9F, true);
    float var4 = this.Hit(var1, var2.hitSpeed, var2.isTargetHitFromBehind, -var2.targetImpulse.x, -var2.targetImpulse.z);
               GameClient.sendHitVehicle(var3, this, var1, var4, var2.isTargetHitFromBehind, var2.vehicleDamage, var2.hitSpeed, var2.isVehicleHitFromFront);
            } else {
               this.getNetworkCharacterAI().resetVehicleHitTimeout();
            }
         }
      } else if (!GameServer.bServer) {
    BaseSoundEmitter var6 = IsoWorld.instance.getFreeEmitter(this.x, this.y, this.z);
    long var7 = var6.playSound("VehicleHitCharacter");
         var6.setParameterValue(var7, FMODManager.instance.getParameterDescription("VehicleSpeed"), var1.getCurrentSpeedKmHour());
         this.Hit(var1, var2.hitSpeed, var2.isTargetHitFromBehind, -var2.targetImpulse.x, -var2.targetImpulse.z);
      }
   }

    bool isSkipResolveCollision() {
      return dynamic_cast<IsoZombie*>(this) != nullptr
            && (
               this.isCurrentState(ZombieHitReactionState.instance())
                  || this.isCurrentState(ZombieFallDownState.instance())
                  || this.isCurrentState(ZombieOnGroundState.instance())
                  || this.isCurrentState(StaggerBackState.instance())
            )
         || dynamic_cast<IsoPlayer*>(this) != nullptr
            && !this.isLocal()
            && (
               this.isCurrentState(PlayerFallDownState.instance())
                  || this.isCurrentState(BumpedState.instance())
                  || this.isCurrentState(PlayerKnockedDown.instance())
                  || this.isCurrentState(PlayerHitReactionState.instance())
                  || this.isCurrentState(PlayerHitReactionPVPState.instance())
                  || this.isCurrentState(PlayerOnGroundState.instance())
            );
   }

    bool isAttackAnim() {
      return this.attackAnim;
   }

    void setAttackAnim(bool var1) {
      this.attackAnim = var1;
   }

    float getNextAnimationTranslationLength() {
      if (this.getActionContext() != nullptr && this.getAnimationPlayer() != nullptr && this.getAdvancedAnimator() != nullptr) {
    ActionState var1 = this.getActionContext().getNextState();
         if (var1 != nullptr && !StringUtils.isNullOrEmpty(var1.getName())) {
    std::vector var2 = new std::vector();
            this.getAdvancedAnimator().animSet.GetState(var1.getName()).getAnimNodes(this, var2);

    for (auto& var4 : var2)               if (!StringUtils.isNullOrEmpty(var4.m_AnimName)) {
    AnimationClip var5 = (AnimationClip)this.getAnimationPlayer().getSkinningData().AnimationClips.get(var4.m_AnimName);
                  if (var5 != nullptr) {
                     return var5.getTranslationLength(var4.m_deferredBoneAxis);
                  }
               }
            }
         }
      }

    return nullptr;
   }

    float calcHitDir(IsoGameCharacter var1, HandWeapon var2, Vector2 var3) {
    float var4 = this.getNextAnimationTranslationLength();
      var3.set(this.getX() - var1.getX(), this.getY() - var1.getY()).normalize();
      if (var4 == nullptr) {
         var3.setLength(this.getHitForce() * 0.1F);
         var3.scale(var2.getPushBackMod());
         var3.rotate(var2.HitAngleMod);
      } else {
         var3.scale(var4);
      }

    return nullptr;
   }

    void calcHitDir(Vector2 var1) {
      var1.set(this.getHitDir());
      var1.setLength(this.getHitForce());
   }

    Safety getSafety() {
      return this.safety;
   }

    void setSafety(Safety var1) {
      this.safety.copyFrom(var1);
   }

    void burnCorpse(IsoDeadBody var1) {
      if (GameClient.bClient) {
         GameClient.sendBurnCorpse(this.getOnlineID(), var1.getObjectID());
      } else {
         IsoFireManager.StartFire(var1.getCell(), var1.getSquare(), true, 100, 700);
      }
   }
}
} // namespace characters
} // namespace zombie
