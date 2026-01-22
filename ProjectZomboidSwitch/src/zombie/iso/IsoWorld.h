#pragma once
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODSoundEmitter.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/CollisionManager.h"
#include "zombie/DebugFileWatcher.h"
#include "zombie/FliesSound.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/Lua/LuaManager/GlobalObject.h"
#include "zombie/MapCollisionData.h"
#include "zombie/PersistentOutfits.h"
#include "zombie/PredicatedFileWatcher.h"
#include "zombie/ReanimatedPlayers.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SharedDescriptors.h"
#include "zombie/SoundManager.h"
#include "zombie/SystemDisabler.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/ZomboidGlobals.h"
#include "zombie/ai/ZombieGroupManager.h"
#include "zombie/ai/states/FakeDeadZombieState.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/audio/DummySoundEmitter.h"
#include "zombie/audio/ObjectAmbientEmitters.h"
#include "zombie/characters/HaloTextHelper.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoSurvivor.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/characters/TriggerSetAnimationRecorderFile.h"
#include "zombie/characters/ZombieVocalsManager.h"
#include "zombie/characters/professions/ProfessionFactory.h"
#include "zombie/characters/professions/ProfessionFactory/Profession.h"
#include "zombie/characters/traits/TraitFactory.h"
#include "zombie/characters/traits/TraitFactory/Trait.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/Rand.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/TilePropertyAliasMap.h"
#include "zombie/core/Translator.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/physics/WorldSimulation.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas.h"
#include "zombie/core/skinnedmodel/model/WorldItemAtlas.h"
#include "zombie/core/stash/StashSystem.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/utils/OnceEvery.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/erosion/ErosionGlobals.h"
#include "zombie/gameStates/GameLoadingState.h"
#include "zombie/globalObjects/GlobalObjectLookup.h"
#include "zombie/input/Mouse.h"
#include "zombie/inventory/ItemPickerJava.h"
#include "zombie/inventory/types/MapItem.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/IsoWorld/CompDistToPlayer.h"
#include "zombie/iso/IsoWorld/CompScoreToPlayer.h"
#include "zombie/iso/IsoWorld/s_performance.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/areas/IsoBuilding.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoFireManager.h"
#include "zombie/iso/objects/ObjectRenderEffects.h"
#include "zombie/iso/objects/RainManager.h"
#include "zombie/iso/sprite/IsoDirectionFrame.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteGrid.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/iso/sprite/SkyBox.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/iso/weather/WorldFlares.h"
#include "zombie/iso/weather/fog/ImprovedFog.h"
#include "zombie/iso/weather/fx/WeatherFxMask.h"
#include "zombie/network/BodyDamageSync.h"
#include "zombie/network/ClientServerMap.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/NetChecksum.h"
#include "zombie/network/PassengerMap.h"
#include "zombie/network/ServerMap.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/popman/ZombiePopulationManager.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBBar.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBBasic.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBBurnt.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBBurntCorpse.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBBurntFireman.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBCafe.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBClinic.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBHairSalon.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBKateAndBaldspot.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBLooted.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBOffice.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBOther.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBPileOCrepe.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBPizzaWhirled.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBSafehouse.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBSchool.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBShopLooted.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBSpiffo.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBStripclub.h"
#include "zombie/randomizedWorld/randomizedBuilding/RandomizedBuildingBase.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSAmbulanceCrash.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSBanditRoad.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSBurntCar.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSCarCrash.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSCarCrashCorpse.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSChangingTire.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSConstructionSite.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSCrashHorde.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSFlippedCrash.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSPoliceBlockade.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSPoliceBlockadeShooting.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSTrailerCrash.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RVSUtilityVehicle.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RandomizedVehicleStoryBase.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RZSBBQParty.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RZSBaseball.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RZSBeachParty.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RZSBuryingCamp.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RZSFishingTrip.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RZSForestCamp.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RZSForestCampEaten.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RZSHunterCamp.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RZSMusicFest.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RZSMusicFestStage.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RZSSexyTime.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RZSTrapperCamp.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RandomizedZoneStoryBase.h"
#include "zombie/savefile/ClientPlayerDB.h"
#include "zombie/savefile/PlayerDB.h"
#include "zombie/savefile/PlayerDBHelper.h"
#include "zombie/savefile/ServerPlayerDB.h"
#include "zombie/text/templating/TemplateText.h"
#include "zombie/ui/TutorialManager.h"
#include "zombie/util/AddCoopPlayer.h"
#include "zombie/util/SharedStrings.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include "zombie/vehicles/VehicleIDMap.h"
#include "zombie/vehicles/VehicleManager.h"
#include "zombie/vehicles/VehiclesDB2.h"
#include "zombie/world/WorldDictionary.h"
#include "zombie/world/WorldDictionaryException.h"
#include "zombie/world/moddata/GlobalModData.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>

namespace zombie {
namespace iso {


class IsoWorld {
public:
    std::string weather = "sunny";
    const IsoMetaGrid MetaGrid = std::make_shared<IsoMetaGrid>();
   private const std::vector<RandomizedBuildingBase> randomizedBuildingList = std::make_unique<std::vector<>>();
   private const std::vector<RandomizedZoneStoryBase> randomizedZoneList = std::make_unique<std::vector<>>();
   private const std::vector<RandomizedVehicleStoryBase> randomizedVehicleStoryList = std::make_unique<std::vector<>>();
    const RandomizedBuildingBase RBBasic = std::make_shared<RBBasic>();
   private const std::unordered_map<std::string, std::vector<double>> spawnedZombieZone = std::make_unique<std::unordered_map<>>();
   private const std::unordered_map<std::string, std::vector<std::string>> allTiles = std::make_unique<std::unordered_map<>>();
   private const std::vector<std::string> tileImages = std::make_unique<std::vector<>>();
    float flashIsoCursorA = 1.0F;
    bool flashIsoCursorInc = false;
    SkyBox sky = nullptr;
    static PredicatedFileWatcher m_setAnimationRecordingTriggerWatcher;
    static bool m_animationRecorderActive = false;
    static bool m_animationRecorderDiscard = false;
    int timeSinceLastSurvivorInHorde = 4000;
    int m_frameNo = 0;
    const Helicopter helicopter = std::make_shared<Helicopter>();
    bool bHydroPowerOn = false;
   public const std::vector<IsoGameCharacter> Characters = std::make_unique<std::vector<>>();
   private const ArrayDeque<BaseSoundEmitter> freeEmitters = std::make_unique<ArrayDeque<>>();
   private const std::vector<BaseSoundEmitter> currentEmitters = std::make_unique<std::vector<>>();
   private const std::unordered_map<BaseSoundEmitter, IsoObject> emitterOwners = std::make_unique<std::unordered_map<>>();
    int x = 50;
    int y = 50;
    IsoCell CurrentCell;
    static IsoWorld instance = std::make_shared<IsoWorld>();
    int TotalSurvivorsDead = 0;
    int TotalSurvivorNights = 0;
    int SurvivorSurvivalRecord = 0;
   public std::unordered_map<int, SurvivorDesc> SurvivorDescriptors = std::make_unique<std::unordered_map<>>();
   public std::vector<AddCoopPlayer> AddCoopPlayers = std::make_unique<std::vector<>>();
    static const CompScoreToPlayer compScoreToPlayer = std::make_shared<CompScoreToPlayer>();
    static CompDistToPlayer compDistToPlayer = std::make_shared<CompDistToPlayer>();
    static std::string mapPath = "media/";
    static bool mapUseJar = true;
    bool bLoaded = false;
   public static const std::unordered_map<std::string, std::vector<std::string>> PropertyValueMap = std::make_unique<std::unordered_map<>>();
    static int WorldX = 0;
    static int WorldY = 0;
    SurvivorDesc luaDesc;
   private std::vector<std::string> luatraits;
    int luaSpawnCellX = -1;
    int luaSpawnCellY = -1;
    int luaPosX = -1;
    int luaPosY = -1;
    int luaPosZ = -1;
    static const int WorldVersion = 195;
    static const int WorldVersion_Barricade = 87;
    static const int WorldVersion_SandboxOptions = 88;
    static const int WorldVersion_FliesSound = 121;
    static const int WorldVersion_LootRespawn = 125;
    static const int WorldVersion_OverlappingGenerators = 127;
    static const int WorldVersion_ItemContainerIdenticalItems = 128;
    static const int WorldVersion_VehicleSirenStartTime = 129;
    static const int WorldVersion_CompostLastUpdated = 130;
    static const int WorldVersion_DayLengthHours = 131;
    static const int WorldVersion_LampOnPillar = 132;
    static const int WorldVersion_AlarmClockRingSince = 134;
    static const int WorldVersion_ClimateAdded = 135;
    static const int WorldVersion_VehicleLightFocusing = 135;
    static const int WorldVersion_GeneratorFuelFloat = 138;
    static const int WorldVersion_InfectionTime = 142;
    static const int WorldVersion_ClimateColors = 143;
    static const int WorldVersion_BodyLocation = 144;
    static const int WorldVersion_CharacterModelData = 145;
    static const int WorldVersion_CharacterModelData2 = 146;
    static const int WorldVersion_CharacterModelData3 = 147;
    static const int WorldVersion_HumanVisualBlood = 148;
    static const int WorldVersion_ItemContainerIdenticalItemsInt = 149;
    static const int WorldVersion_PerkName = 152;
    static const int WorldVersion_Thermos = 153;
    static const int WorldVersion_AllPatches = 155;
    static const int WorldVersion_ZombieRotStage = 156;
    static const int WorldVersion_NewSandboxLootModifier = 157;
    static const int WorldVersion_KateBobStorm = 158;
    static const int WorldVersion_DeadBodyAngle = 159;
    static const int WorldVersion_ChunkSpawnedRooms = 160;
    static const int WorldVersion_DeathDragDown = 161;
    static const int WorldVersion_CanUpgradePerk = 162;
    static const int WorldVersion_ItemVisualFullType = 164;
    static const int WorldVersion_VehicleBlood = 165;
    static const int WorldVersion_DeadBodyZombieRotStage = 166;
    static const int WorldVersion_Fitness = 167;
    static const int WorldVersion_DeadBodyFakeDead = 168;
    static const int WorldVersion_Fitness2 = 169;
    static const int WorldVersion_NewFog = 170;
    static const int WorldVersion_DeadBodyPersistentOutfitID = 171;
    static const int WorldVersion_VehicleTowingID = 172;
    static const int WorldVersion_VehicleJNITransform = 173;
    static const int WorldVersion_VehicleTowAttachment = 174;
    static const int WorldVersion_ContainerMaxCapacity = 175;
    static const int WorldVersion_TimedActionInstantCheat = 176;
    static const int WorldVersion_ClothingPatchSaveLoad = 178;
    static const int WorldVersion_AttachedSlotType = 179;
    static const int WorldVersion_NoiseMakerDuration = 180;
    static const int WorldVersion_ChunkVehicles = 91;
    static const int WorldVersion_PlayerVehicleSeat = 91;
    static const int WorldVersion_MediaDisksAndTapes = 181;
    static const int WorldVersion_AlreadyReadBooks1 = 182;
    static const int WorldVersion_LampOnPillar2 = 183;
    static const int WorldVersion_AlreadyReadBooks2 = 184;
    static const int WorldVersion_PolygonZone = 185;
    static const int WorldVersion_PolylineZone = 186;
    static const int WorldVersion_NaturalHairBeardColor = 187;
    static const int WorldVersion_CruiseSpeedSaving = 188;
    static const int WorldVersion_KnownMediaLines = 189;
    static const int WorldVersion_DeadBodyAtlas = 190;
    static const int WorldVersion_Scarecrow = 191;
    static const int WorldVersion_DeadBodyID = 192;
    static const int WorldVersion_IgnoreRemoveSandbox = 193;
    static const int WorldVersion_MapMetaBounds = 194;
    static const int WorldVersion_PreviouslyEntered = 195;
    static int SavedWorldVersion = -1;
    bool bDrawWorld = true;
   private const std::vector<IsoZombie> zombieWithModel = std::make_unique<std::vector<>>();
   private const std::vector<IsoZombie> zombieWithoutModel = std::make_unique<std::vector<>>();
    static bool NoZombies = false;
    static int TotalWorldVersion = -1;
    static int saveoffsetx;
    static int saveoffsety;
    bool bDoChunkMapUpdate = true;
    long emitterUpdateMS;
    bool emitterUpdate;
    int updateSafehousePlayers = 200;

    IsoMetaGrid getMetaGrid() {
      return this.MetaGrid;
   }

    Zone registerZone(const std::string& var1, const std::string& var2, int var3, int var4, int var5, int var6, int var7) {
      return this.MetaGrid.registerZone(var1, var2, var3, var4, var5, var6, var7);
   }

    Zone registerZoneNoOverlap(const std::string& var1, const std::string& var2, int var3, int var4, int var5, int var6, int var7) {
      return this.MetaGrid.registerZoneNoOverlap(var1, var2, var3, var4, var5, var6, var7);
   }

    void removeZonesForLotDirectory(const std::string& var1) {
      this.MetaGrid.removeZonesForLotDirectory(var1);
   }

    BaseSoundEmitter getFreeEmitter() {
    void* var1 = nullptr;
      if (this.freeEmitters.empty()) {
         var1 = Core.SoundDisabled ? std::make_unique<DummySoundEmitter>() : std::make_unique<FMODSoundEmitter>();
      } else {
         var1 = this.freeEmitters.pop();
      }

      this.currentEmitters.push_back((BaseSoundEmitter)var1);
      return (BaseSoundEmitter)var1;
   }

    BaseSoundEmitter getFreeEmitter(float var1, float var2, float var3) {
    BaseSoundEmitter var4 = this.getFreeEmitter();
      var4.setPos(var1, var2, var3);
    return var4;
   }

    void takeOwnershipOfEmitter(BaseSoundEmitter var1) {
      this.currentEmitters.remove(var1);
   }

    void setEmitterOwner(BaseSoundEmitter var1, IsoObject var2) {
      if (var1 != nullptr && var2 != nullptr) {
         if (!this.emitterOwners.containsKey(var1)) {
            this.emitterOwners.put(var1, var2);
         }
      }
   }

    void returnOwnershipOfEmitter(BaseSoundEmitter var1) {
      if (var1 != nullptr) {
         if (!this.currentEmitters.contains(var1) && !this.freeEmitters.contains(var1)) {
            if (var1.empty()) {
    FMODSoundEmitter var2 = (FMODSoundEmitter)Type.tryCastTo(var1, FMODSoundEmitter.class);
               if (var2 != nullptr) {
                  var2.clearParameters();
               }

               this.freeEmitters.push_back(var1);
            } else {
               this.currentEmitters.push_back(var1);
            }
         }
      }
   }

    Zone registerVehiclesZone(const std::string& var1, const std::string& var2, int var3, int var4, int var5, int var6, int var7, KahluaTable var8) {
      return this.MetaGrid.registerVehiclesZone(var1, var2, var3, var4, var5, var6, var7, var8);
   }

    Zone registerMannequinZone(const std::string& var1, const std::string& var2, int var3, int var4, int var5, int var6, int var7, KahluaTable var8) {
      return this.MetaGrid.registerMannequinZone(var1, var2, var3, var4, var5, var6, var7, var8);
   }

    void registerRoomTone(const std::string& var1, const std::string& var2, int var3, int var4, int var5, int var6, int var7, KahluaTable var8) {
      this.MetaGrid.registerRoomTone(var1, var2, var3, var4, var5, var6, var7, var8);
   }

    void registerSpawnOrigin(int var1, int var2, int var3, int var4, KahluaTable var5) {
      ZombiePopulationManager.instance.registerSpawnOrigin(var1, var2, var3, var4, var5);
   }

    void registerWaterFlow(float var1, float var2, float var3, float var4) {
      IsoWaterFlow.addFlow(var1, var2, var3, var4);
   }

    void registerWaterZone(float var1, float var2, float var3, float var4, float var5, float var6) {
      IsoWaterFlow.addZone(var1, var2, var3, var4, var5, var6);
   }

    void checkVehiclesZones() {
      this.MetaGrid.checkVehiclesZones();
   }

    void setGameMode(const std::string& var1) {
      Core.GameMode = var1;
      Core.bLastStand = "LastStand" == var1);
      Core.getInstance().setChallenge(false);
      Core.ChallengeID = nullptr;
   }

    std::string getGameMode() {
      return Core.GameMode;
   }

    void setWorld(const std::string& var1) {
      Core.GameSaveWorld = var1.trim();
   }

    void setMap(const std::string& var1) {
      Core.GameMap = var1;
   }

    std::string getMap() {
      return Core.GameMap;
   }

    void renderTerrain() {
   }

    int getFrameNo() {
      return this.m_frameNo;
   }

    IsoObject getItemFromXYZIndexBuffer(ByteBuffer var1) {
    int var2 = var1.getInt();
    int var3 = var1.getInt();
    int var4 = var1.getInt();
    IsoGridSquare var5 = this.CurrentCell.getGridSquare(var2, var3, var4);
      if (var5 == nullptr) {
    return nullptr;
      } else {
    uint8_t var6 = var1.get();
         return var6 >= 0 && var6 < var5.getObjects().size() ? (IsoObject)var5.getObjects().get(var6) : nullptr;
      }
   }

    public IsoWorld() {
      if (!GameServer.bServer) {
      }
   }

    static void initMessaging() {
      if (m_setAnimationRecordingTriggerWatcher == nullptr) {
         m_setAnimationRecordingTriggerWatcher = std::make_shared<PredicatedFileWatcher>(
            ZomboidFileSystem.instance.getMessagingDirSub("Trigger_AnimationRecorder.xml"),
            TriggerSetAnimationRecorderFile.class,
            IsoWorld::onTrigger_setAnimationRecorderTriggerFile
         );
         DebugFileWatcher.instance.push_back(m_setAnimationRecordingTriggerWatcher);
      }
   }

    static void onTrigger_setAnimationRecorderTriggerFile(TriggerSetAnimationRecorderFile var0) {
      m_animationRecorderActive = var0.isRecording;
      m_animationRecorderDiscard = var0.discard;
   }

    static bool isAnimRecorderActive() {
    return m_animationRecorderActive;
   }

    static bool isAnimRecorderDiscardTriggered() {
    return m_animationRecorderDiscard;
   }

    IsoSurvivor CreateRandomSurvivor(SurvivorDesc var1, IsoGridSquare var2, IsoPlayer var3) {
    return nullptr;
   }

    void CreateSwarm(int var1, int var2, int var3, int var4, int var5) {
   }

    void ForceKillAllZombies() {
      GameTime.getInstance().RemoveZombiesIndiscriminate(1000);
   }

    static int readInt(RandomAccessFile var0) {
    int var1 = var0.read();
    int var2 = var0.read();
    int var3 = var0.read();
    int var4 = var0.read();
      if ((var1 | var2 | var3 | var4) < 0) {
         throw std::make_unique<EOFException>();
      } else {
         return (var1 << 0) + (var2 << 8) + (var3 << 16) + (var4 << 24);
      }
   }

    static std::string readString(RandomAccessFile var0) {
      return var0.readLine();
   }

    static int readInt(InputStream var0) {
    int var1 = var0.read();
    int var2 = var0.read();
    int var3 = var0.read();
    int var4 = var0.read();
      if ((var1 | var2 | var3 | var4) < 0) {
         throw std::make_unique<EOFException>();
      } else {
         return (var1 << 0) + (var2 << 8) + (var3 << 16) + (var4 << 24);
      }
   }

    static std::string readString(InputStream var0) {
    std::stringstream var1 = new std::stringstream();
    int var2 = -1;
    bool var3 = false;

      while (!var3) {
         switch (var2 = var0.read()) {
            case -1:
            case 10:
               var3 = true;
               break;
            case 13:
               throw IllegalStateException("\r\n unsupported");
            default:
               var1.append((char)var2);
         }
      }

    return var2 = = -1 && var1.length() == 0 ? nullptr : var1;
   }

    void LoadTileDefinitions(IsoSpriteManager var1, const std::string& var2, int var3) {
      DebugLog.log("tiledef: loading " + var2);
    bool var4 = var2.endsWith(".patch.tiles");

      try (
    FileInputStream var5 = std::make_shared<FileInputStream>(var2);
    BufferedInputStream var6 = std::make_shared<BufferedInputStream>(var5);
      ) {
    int var7 = readInt(var6);
    int var8 = readInt(var6);
    int var9 = readInt(var6);
    SharedStrings var10 = std::make_shared<SharedStrings>();
    bool var11 = false;
    bool var12 = false;
    bool var13 = Core.bDebug && Translator.getLanguage() == Translator.getDefaultLanguage();
    std::vector var14 = new std::vector();
    std::unordered_map var15 = new std::unordered_map();
    std::unordered_map var16 = new std::unordered_map();
         std::string[] var17 = new std::string[]{"N", "E", "S", "W"};

         for (int var18 = 0; var18 < var17.length; var18++) {
            var16.put(var17[var18], std::make_unique<std::vector>());
         }

    std::vector var57 = new std::vector();
    std::unordered_map var19 = new std::unordered_map();
    int var20 = 0;
    int var21 = 0;
    int var22 = 0;
    int var23 = 0;
    std::unordered_set var24 = new std::unordered_set();

         for (int var25 = 0; var25 < var9; var25++) {
    std::string var26 = readString(var6);
    std::string var27 = var26.trim();
    std::string var28 = readString(var6);
    int var29 = readInt(var6);
    int var30 = readInt(var6);
    int var31 = readInt(var6);
    int var32 = readInt(var6);

            for (int var33 = 0; var33 < var32; var33++) {
    IsoSprite var34;
               if (var4) {
                  var34 = (IsoSprite)var1.NamedMap.get(var27 + "_" + var33);
                  if (var34 == nullptr) {
                     continue;
                  }
               } else if (var3 < 2) {
                  var34 = var1.AddSprite(var27 + "_" + var33, var3 * 100 * 1000 + 10000 + var31 * 1000 + var33);
               } else {
                  var34 = var1.AddSprite(var27 + "_" + var33, var3 * 512 * 512 + var31 * 512 + var33);
               }

               if (Core.bDebug) {
                  if (this.allTiles.containsKey(var27)) {
                     if (!var4) {
                        this.allTiles.get(var27).push_back(var27 + "_" + var33);
                     }
                  } else {
    std::vector var35 = new std::vector();
                     var35.push_back(var27 + "_" + var33);
                     this.allTiles.put(var27, var35);
                  }
               }

               var14.push_back(var34);
               if (!var4) {
                  var34.setName(var27 + "_" + var33);
                  var34.tileSheetIndex = var33;
               }

               if (var34.name.contains("damaged") || var34.name.contains("trash_")) {
                  var34.attachedFloor = true;
                  var34.getProperties().Set("attachedFloor", "true");
               }

               if (var34.name.startsWith("f_bushes") && var33 <= 31) {
                  var34.isBush = true;
                  var34.attachedFloor = true;
               }

    int var72 = readInt(var6);

               for (int var36 = 0; var36 < var72; var36++) {
                  var26 = readString(var6);
    std::string var37 = var26.trim();
                  var26 = readString(var6);
    std::string var38 = var26.trim();
    IsoObjectType var39 = IsoObjectType.FromString(var37);
                  if (var39 != IsoObjectType.MAX) {
                     if (var34.getType() != IsoObjectType.doorW && var34.getType() != IsoObjectType.doorN || var39 != IsoObjectType.wall) {
                        var34.setType(var39);
                     }

                     if (var39 == IsoObjectType.doorW) {
                        var34.getProperties().Set(IsoFlagType.doorW);
                     } else if (var39 == IsoObjectType.doorN) {
                        var34.getProperties().Set(IsoFlagType.doorN);
                     }
                  } else {
                     var37 = var10.get(var37);
                     if (var37 == "firerequirement")) {
                        var34.firerequirement = int.parseInt(var38);
                     } else if (var37 == "fireRequirement")) {
                        var34.firerequirement = int.parseInt(var38);
                     } else if (var37 == "BurntTile")) {
                        var34.burntTile = var38;
                     } else if (var37 == "ForceAmbient")) {
                        var34.forceAmbient = true;
                        var34.getProperties().Set(var37, var38);
                     } else if (var37 == "solidfloor")) {
                        var34.solidfloor = true;
                        var34.getProperties().Set(var37, var38);
                     } else if (var37 == "canBeRemoved")) {
                        var34.canBeRemoved = true;
                        var34.getProperties().Set(var37, var38);
                     } else if (var37 == "attachedFloor")) {
                        var34.attachedFloor = true;
                        var34.getProperties().Set(var37, var38);
                     } else if (var37 == "cutW")) {
                        var34.cutW = true;
                        var34.getProperties().Set(var37, var38);
                     } else if (var37 == "cutN")) {
                        var34.cutN = true;
                        var34.getProperties().Set(var37, var38);
                     } else if (var37 == "solid")) {
                        var34.solid = true;
                        var34.getProperties().Set(var37, var38);
                     } else if (var37 == "solidTrans")) {
                        var34.solidTrans = true;
                        var34.getProperties().Set(var37, var38);
                     } else if (var37 == "invisible")) {
                        var34.invisible = true;
                        var34.getProperties().Set(var37, var38);
                     } else if (var37 == "alwaysDraw")) {
                        var34.alwaysDraw = true;
                        var34.getProperties().Set(var37, var38);
                     } else if (var37 == "forceRender")) {
                        var34.forceRender = true;
                        var34.getProperties().Set(var37, var38);
                     } else if ("FloorHeight" == var37)) {
                        if ("OneThird" == var38)) {
                           var34.getProperties().Set(IsoFlagType.FloorHeightOneThird);
                        } else if ("TwoThirds" == var38)) {
                           var34.getProperties().Set(IsoFlagType.FloorHeightTwoThirds);
                        }
                     } else if (var37 == "MoveWithWind")) {
                        var34.moveWithWind = true;
                        var34.getProperties().Set(var37, var38);
                     } else if (var37 == "WindType")) {
                        var34.windType = int.parseInt(var38);
                        var34.getProperties().Set(var37, var38);
                     } else if (var37 == "RenderLayer")) {
                        var34.getProperties().Set(var37, var38);
                        if ("Default" == var38)) {
                           var34.renderLayer = 0;
                        } else if ("Floor" == var38)) {
                           var34.renderLayer = 1;
                        }
                     } else if (var37 == "TreatAsWallOrder")) {
                        var34.treatAsWallOrder = true;
                        var34.getProperties().Set(var37, var38);
                     } else {
                        var34.getProperties().Set(var37, var38);
                        if ("WindowN" == var37) || "WindowW" == var37)) {
                           var34.getProperties().Set(var37, var38, false);
                        }
                     }
                  }

                  if (var39 == IsoObjectType.tree) {
                     if (var34.name == "e_riverbirch_1_1")) {
                        var38 = "1";
                     }

                     var34.getProperties().Set("tree", var38);
                     var34.getProperties().UnSet(IsoFlagType.solid);
                     var34.getProperties().Set(IsoFlagType.blocksight);
    int var40 = int.parseInt(var38);
                     if (var27.startsWith("vegetation_trees")) {
                        var40 = 4;
                     }

                     if (var40 < 1) {
                        var40 = 1;
                     }

                     if (var40 > 4) {
                        var40 = 4;
                     }

                     if (var40 == 1 || var40 == 2) {
                        var34.getProperties().UnSet(IsoFlagType.blocksight);
                     }
                  }

                  if (var37 == "interior") && var38 == "false")) {
                     var34.getProperties().Set(IsoFlagType.exterior);
                  }

                  if (var37 == "HoppableN")) {
                     var34.getProperties().Set(IsoFlagType.collideN);
                     var34.getProperties().Set(IsoFlagType.canPathN);
                     var34.getProperties().Set(IsoFlagType.transparentN);
                  }

                  if (var37 == "HoppableW")) {
                     var34.getProperties().Set(IsoFlagType.collideW);
                     var34.getProperties().Set(IsoFlagType.canPathW);
                     var34.getProperties().Set(IsoFlagType.transparentW);
                  }

                  if (var37 == "WallN")) {
                     var34.getProperties().Set(IsoFlagType.collideN);
                     var34.getProperties().Set(IsoFlagType.cutN);
                     var34.setType(IsoObjectType.wall);
                     var34.cutN = true;
                     var34.getProperties().Set("WallN", "", false);
                  }

                  if (var37 == "CantClimb")) {
                     var34.getProperties().Set(IsoFlagType.CantClimb);
                  } else if (var37 == "container")) {
                     var34.getProperties().Set(var37, var38, false);
                  } else if (var37 == "WallNTrans")) {
                     var34.getProperties().Set(IsoFlagType.collideN);
                     var34.getProperties().Set(IsoFlagType.cutN);
                     var34.getProperties().Set(IsoFlagType.transparentN);
                     var34.setType(IsoObjectType.wall);
                     var34.cutN = true;
                     var34.getProperties().Set("WallNTrans", "", false);
                  } else if (var37 == "WallW")) {
                     var34.getProperties().Set(IsoFlagType.collideW);
                     var34.getProperties().Set(IsoFlagType.cutW);
                     var34.setType(IsoObjectType.wall);
                     var34.cutW = true;
                     var34.getProperties().Set("WallW", "", false);
                  } else if (var37 == "windowN")) {
                     var34.getProperties().Set("WindowN", "WindowN");
                     var34.getProperties().Set(IsoFlagType.transparentN);
                     var34.getProperties().Set("WindowN", "WindowN", false);
                  } else if (var37 == "windowW")) {
                     var34.getProperties().Set("WindowW", "WindowW");
                     var34.getProperties().Set(IsoFlagType.transparentW);
                     var34.getProperties().Set("WindowW", "WindowW", false);
                  } else if (var37 == "cutW")) {
                     var34.getProperties().Set(IsoFlagType.cutW);
                     var34.cutW = true;
                  } else if (var37 == "cutN")) {
                     var34.getProperties().Set(IsoFlagType.cutN);
                     var34.cutN = true;
                  } else if (var37 == "WallWTrans")) {
                     var34.getProperties().Set(IsoFlagType.collideW);
                     var34.getProperties().Set(IsoFlagType.transparentW);
                     var34.getProperties().Set(IsoFlagType.cutW);
                     var34.setType(IsoObjectType.wall);
                     var34.cutW = true;
                     var34.getProperties().Set("WallWTrans", "", false);
                  } else if (var37 == "DoorWallN")) {
                     var34.getProperties().Set(IsoFlagType.cutN);
                     var34.cutN = true;
                     var34.getProperties().Set("DoorWallN", "", false);
                  } else if (var37 == "DoorWallNTrans")) {
                     var34.getProperties().Set(IsoFlagType.cutN);
                     var34.getProperties().Set(IsoFlagType.transparentN);
                     var34.cutN = true;
                     var34.getProperties().Set("DoorWallNTrans", "", false);
                  } else if (var37 == "DoorWallW")) {
                     var34.getProperties().Set(IsoFlagType.cutW);
                     var34.cutW = true;
                     var34.getProperties().Set("DoorWallW", "", false);
                  } else if (var37 == "DoorWallWTrans")) {
                     var34.getProperties().Set(IsoFlagType.cutW);
                     var34.getProperties().Set(IsoFlagType.transparentW);
                     var34.cutW = true;
                     var34.getProperties().Set("DoorWallWTrans", "", false);
                  } else if (var37 == "WallNW")) {
                     var34.getProperties().Set(IsoFlagType.collideN);
                     var34.getProperties().Set(IsoFlagType.cutN);
                     var34.getProperties().Set(IsoFlagType.collideW);
                     var34.getProperties().Set(IsoFlagType.cutW);
                     var34.setType(IsoObjectType.wall);
                     var34.cutW = true;
                     var34.cutN = true;
                     var34.getProperties().Set("WallNW", "", false);
                  } else if (var37 == "WallNWTrans")) {
                     var34.getProperties().Set(IsoFlagType.collideN);
                     var34.getProperties().Set(IsoFlagType.cutN);
                     var34.getProperties().Set(IsoFlagType.collideW);
                     var34.getProperties().Set(IsoFlagType.transparentN);
                     var34.getProperties().Set(IsoFlagType.transparentW);
                     var34.getProperties().Set(IsoFlagType.cutW);
                     var34.setType(IsoObjectType.wall);
                     var34.cutW = true;
                     var34.cutN = true;
                     var34.getProperties().Set("WallNWTrans", "", false);
                  } else if (var37 == "WallSE")) {
                     var34.getProperties().Set(IsoFlagType.cutW);
                     var34.getProperties().Set(IsoFlagType.WallSE);
                     var34.getProperties().Set("WallSE", "WallSE");
                     var34.cutW = true;
                  } else if (var37 == "WindowW")) {
                     var34.getProperties().Set(IsoFlagType.canPathW);
                     var34.getProperties().Set(IsoFlagType.collideW);
                     var34.getProperties().Set(IsoFlagType.cutW);
                     var34.getProperties().Set(IsoFlagType.transparentW);
                     var34.setType(IsoObjectType.windowFW);
                     if (var34.getProperties().Is(IsoFlagType.HoppableW)) {
                        if (Core.bDebug) {
                           DebugLog.log("ERROR: WindowW sprite shouldn't have HoppableW (" + var34.getName() + ")");
                        }

                        var34.getProperties().UnSet(IsoFlagType.HoppableW);
                     }

                     var34.cutW = true;
                  } else if (var37 == "WindowN")) {
                     var34.getProperties().Set(IsoFlagType.canPathN);
                     var34.getProperties().Set(IsoFlagType.collideN);
                     var34.getProperties().Set(IsoFlagType.cutN);
                     var34.getProperties().Set(IsoFlagType.transparentN);
                     var34.setType(IsoObjectType.windowFN);
                     if (var34.getProperties().Is(IsoFlagType.HoppableN)) {
                        if (Core.bDebug) {
                           DebugLog.log("ERROR: WindowN sprite shouldn't have HoppableN (" + var34.getName() + ")");
                        }

                        var34.getProperties().UnSet(IsoFlagType.HoppableN);
                     }

                     var34.cutN = true;
                  } else if (var37 == "UnbreakableWindowW")) {
                     var34.getProperties().Set(IsoFlagType.canPathW);
                     var34.getProperties().Set(IsoFlagType.collideW);
                     var34.getProperties().Set(IsoFlagType.cutW);
                     var34.getProperties().Set(IsoFlagType.transparentW);
                     var34.getProperties().Set(IsoFlagType.collideW);
                     var34.setType(IsoObjectType.wall);
                     var34.cutW = true;
                  } else if (var37 == "UnbreakableWindowN")) {
                     var34.getProperties().Set(IsoFlagType.canPathN);
                     var34.getProperties().Set(IsoFlagType.collideN);
                     var34.getProperties().Set(IsoFlagType.cutN);
                     var34.getProperties().Set(IsoFlagType.transparentN);
                     var34.getProperties().Set(IsoFlagType.collideN);
                     var34.setType(IsoObjectType.wall);
                     var34.cutN = true;
                  } else if (var37 == "UnbreakableWindowNW")) {
                     var34.getProperties().Set(IsoFlagType.cutN);
                     var34.getProperties().Set(IsoFlagType.transparentN);
                     var34.getProperties().Set(IsoFlagType.collideN);
                     var34.getProperties().Set(IsoFlagType.cutN);
                     var34.getProperties().Set(IsoFlagType.collideW);
                     var34.getProperties().Set(IsoFlagType.cutW);
                     var34.setType(IsoObjectType.wall);
                     var34.cutW = true;
                     var34.cutN = true;
                  } else if ("NoWallLighting" == var37)) {
                     var34.getProperties().Set(IsoFlagType.NoWallLighting);
                  } else if ("ForceAmbient" == var37)) {
                     var34.getProperties().Set(IsoFlagType.ForceAmbient);
                  }

                  if (var37 == "name")) {
                     var34.setParentObjectName(var38);
                  }
               }

               if (var34.getProperties().Is("lightR") || var34.getProperties().Is("lightG") || var34.getProperties().Is("lightB")) {
                  if (!var34.getProperties().Is("lightR")) {
                     var34.getProperties().Set("lightR", "0");
                  }

                  if (!var34.getProperties().Is("lightG")) {
                     var34.getProperties().Set("lightG", "0");
                  }

                  if (!var34.getProperties().Is("lightB")) {
                     var34.getProperties().Set("lightB", "0");
                  }
               }

               var34.getProperties().CreateKeySet();
               if (Core.bDebug && var34.getProperties().Is("SmashedTileOffset") && !var34.getProperties().Is("GlassRemovedOffset")) {
                  DebugLog.General.error("Window sprite has SmashedTileOffset but no GlassRemovedOffset (" + var34.getName() + ")");
               }
            }

            this.setOpenDoorProperties(var27, var14);
            var15.clear();

    for (auto& var70 : var14)               if (var70.getProperties().Is("StopCar")) {
                  var70.setType(IsoObjectType.isMoveAbleObject);
               }

               if (var70.getProperties().Is("IsMoveAble")) {
                  if (var70.getProperties().Is("CustomName") && !var70.getProperties().Val("CustomName") == "")) {
                     var20++;
                     if (var70.getProperties().Is("GroupName")) {
    std::string var73 = var70.getProperties().Val("GroupName") + " " + var70.getProperties().Val("CustomName");
                        if (!var15.containsKey(var73)) {
                           var15.put(var73, std::make_unique<std::vector>());
                        }

                        ((std::vector)var15.get(var73)).push_back(var70);
                        var24.push_back(var73);
                     } else {
                        if (!var19.containsKey(var27)) {
                           var19.put(var27, std::make_unique<std::vector>());
                        }

                        if (!((std::vector)var19.get(var27)).contains(var70.getProperties().Val("CustomName"))) {
                           ((std::vector)var19.get(var27)).push_back(var70.getProperties().Val("CustomName"));
                        }

                        var21++;
                        var24.push_back(var70.getProperties().Val("CustomName"));
                     }
                  } else {
                     DebugLog.log("[IMPORTANT] MOVABLES: Object has no custom name defined: sheet = " + var27);
                  }
               }
            }

            for (Entry var71 : var15.entrySet()) {
    std::string var74 = (std::string)var71.getKey();
               if (!var19.containsKey(var27)) {
                  var19.put(var27, std::make_unique<std::vector>());
               }

               if (!((std::vector)var19.get(var27)).contains(var74)) {
                  ((std::vector)var19.get(var27)).push_back(var74);
               }

    std::vector var75 = (std::vector)var71.getValue();
               if (var75.size() == 1) {
                  DebugLog.log("MOVABLES: Object has only one face defined for group: (" + var74 + ") sheet = " + var27);
               }

               if (var75.size() == 3) {
                  DebugLog.log("MOVABLES: Object only has 3 sprites, _might_ have a error in settings, group: (" + var74 + ") sheet = " + var27);
               }

    for (auto& var85 : var17)                  ((std::vector)var16.get(var85)).clear();
               }

               boolean var77 = ((IsoSprite)var75.get(0)).getProperties().Is("SpriteGridPos")
                  && !((IsoSprite)var75.get(0)).getProperties().Val("SpriteGridPos") == "None");
    bool var79 = true;

    for (auto& var86 : var75)    bool var41 = var86.getProperties().Is("SpriteGridPos") && !var86.getProperties().Val("SpriteGridPos") == "None");
                  if (var77 != var41) {
                     var79 = false;
                     DebugLog.log("MOVABLES: Difference in SpriteGrid settings for members of group: (" + var74 + ") sheet = " + var27);
                     break;
                  }

                  if (!var86.getProperties().Is("Facing")) {
                     var79 = false;
                  } else {
    std::string var42 = var86.getProperties().Val("Facing");
                     switch (var42) {
                        case "N":
                           ((std::vector)var16.get("N")).push_back(var86);
                           break;
                        case "E":
                           ((std::vector)var16.get("E")).push_back(var86);
                           break;
                        case "S":
                           ((std::vector)var16.get("S")).push_back(var86);
                           break;
                        case "W":
                           ((std::vector)var16.get("W")).push_back(var86);
                           break;
                        default:
                           DebugLog.log("MOVABLES: Invalid face (" + var86.getProperties().Val("Facing") + ") for group: (" + var74 + ") sheet = " + var27);
                           var79 = false;
                     }
                  }

                  if (!var79) {
                     DebugLog.log("MOVABLES: Not all members have a valid face defined for group: (" + var74 + ") sheet = " + var27);
                     break;
                  }
               }

               if (var79) {
                  if (var77) {
    int var82 = 0;
                     IsoSpriteGrid[] var87 = new IsoSpriteGrid[var17.length];

                     label676:
                     for (int var90 = 0; var90 < var17.length; var90++) {
    std::vector var94 = (std::vector)var16.get(var17[var90]);
                        if (var94.size() > 0) {
                           if (var82 == 0) {
                              var82 = var94.size();
                           }

                           if (var82 != var94.size()) {
                              DebugLog.log("MOVABLES: Sprite count mismatch for multi sprite movable, group: (" + var74 + ") sheet = " + var27);
                              var79 = false;
                              break;
                           }

                           var57.clear();
    int var98 = -1;
    int var44 = -1;
    Iterator var45 = var94.iterator();

                           while (true) {
                              if (var45.hasNext()) {
    IsoSprite var46 = (IsoSprite)var45.next();
    std::string var47 = var46.getProperties().Val("SpriteGridPos");
                                 if (!var57.contains(var47)) {
                                    var57.push_back(var47);
                                    std::string[] var48 = var47.split(",");
                                    if (var48.length == 2) {
    int var49 = int.parseInt(var48[0]);
    int var50 = int.parseInt(var48[1]);
                                       if (var49 > var98) {
                                          var98 = var49;
                                       }

                                       if (var50 > var44) {
                                          var44 = var50;
                                       }
                                       continue;
                                    }

                                    DebugLog.log("MOVABLES: SpriteGrid position error for multi sprite movable, group: (" + var74 + ") sheet = " + var27);
                                    var79 = false;
                                 } else {
                                    DebugLog.log(
                                       "MOVABLES: double SpriteGrid position (" + var47 + ") for multi sprite movable, group: (" + var74 + ") sheet = " + var27
                                    );
                                    var79 = false;
                                 }
                              }

                              if (var98 == -1 || var44 == -1 || (var98 + 1) * (var44 + 1) != var94.size()) {
                                 DebugLog.log("MOVABLES: SpriteGrid dimensions error for multi sprite movable, group: (" + var74 + ") sheet = " + var27);
                                 var79 = false;
    break label676;
                              }

                              if (!var79) {
    break label676;
                              }

                              var87[var90] = std::make_shared<IsoSpriteGrid>(var98 + 1, var44 + 1);

    for (auto& var106 : var94)    std::string var108 = var106.getProperties().Val("SpriteGridPos");
                                 std::string[] var110 = var108.split(",");
    int var111 = int.parseInt(var110[0]);
    int var112 = int.parseInt(var110[1]);
                                 var87[var90].setSprite(var111, var112, var106);
                              }

                              if (!var87[var90].validate()) {
                                 DebugLog.log("MOVABLES: SpriteGrid didn't validate for multi sprite movable, group: (" + var74 + ") sheet = " + var27);
                                 var79 = false;
    break label676;
                              }
                              break;
                           }
                        }
                     }

                     if (var79 && var82 != 0) {
                        var23++;

                        for (int var91 = 0; var91 < var17.length; var91++) {
    IsoSpriteGrid var95 = var87[var91];
                           if (var95 != nullptr) {
                              for (IsoSprite var107 : var95.getSprites()) {
                                 var107.setSpriteGrid(var95);

                                 for (int var109 = 0; var109 < var17.length; var109++) {
                                    if (var109 != var91 && var87[var109] != nullptr) {
                                       var107.getProperties()
                                          .Set(
                                             var17[var109] + "offset", int.toString(var14.indexOf(var87[var109].getAnchorSprite()) - var14.indexOf(var107))
                                          );
                                    }
                                 }
                              }
                           }
                        }
                     } else {
                        DebugLog.log("MOVABLES: Error in multi sprite movable, group: (" + var74 + ") sheet = " + var27);
                     }
                  } else if (var75.size() > 4) {
                     DebugLog.log("MOVABLES: Object has too many faces defined for group: (" + var74 + ") sheet = " + var27);
                  } else {
    for (auto& var96 : var17)                        if (((std::vector)var16.get(var96)).size() > 1) {
                           DebugLog.log("MOVABLES: " + var96 + " face defined more than once for group: (" + var74 + ") sheet = " + var27);
                           var79 = false;
                        }
                     }

                     if (var79) {
                        var22++;

    for (auto& var89 : var75)    for (auto& var102 : var17)    std::vector var105 = (std::vector)var16.get(var102);
                              if (var105.size() > 0 && var105.get(0) != var89) {
                                 var89.getProperties().Set(var102 + "offset", int.toString(var14.indexOf(var105.get(0)) - var14.indexOf(var89)));
                              }
                           }
                        }
                     }
                  }
               }
            }

            var14.clear();
         }

         if (var12) {
    std::vector var58 = new std::vector(var24);
            Collections.sort(var58);

    for (auto& var64 : var58)               System.out.println(var64.replaceAll(" ", "_").replaceAll("-", "_").replaceAll("'", "").replaceAll("\\.", "") + " = \"" + var64 + "\",");
            }
         }

         if (var13) {
    std::vector var59 = new std::vector(var24);
            Collections.sort(var59);
    std::stringstream var63 = new std::stringstream();

    for (auto& var67 : var59)               if (Translator.getMoveableDisplayNameOrNull(var67) == nullptr) {
                  var63.append(var67.replaceAll(" ", "_").replaceAll("-", "_").replaceAll("'", "").replaceAll("\\.", "") + " = \"" + var67 + "\",\n");
               }
            }

    std::string var66 = var63;
            if (!var66.empty() && Core.bDebug) {
               System.out.println("Missing translations in Moveables_EN.txt:\n" + var66);
            }
         }

         if (var11) {
            try {
               this.saveMovableStats(var19, var3, var21, var22, var23, var20);
            } catch (Exception var53) {
            }
         }
      } catch (Exception var56) {
         ExceptionLogger.logException(var56);
      }
   }

    void GenerateTilePropertyLookupTables() {
      TilePropertyAliasMap.instance.Generate(PropertyValueMap);
      PropertyValueMap.clear();
   }

    void LoadTileDefinitionsPropertyStrings(IsoSpriteManager var1, const std::string& var2, int var3) {
      DebugLog.log("tiledef: loading " + var2);
      if (!GameServer.bServer) {
         Thread.yield();
         Core.getInstance().DoFrameReady();
      }

      try (
    FileInputStream var4 = std::make_shared<FileInputStream>(var2);
    BufferedInputStream var5 = std::make_shared<BufferedInputStream>(var4);
      ) {
    int var6 = readInt(var5);
    int var7 = readInt(var5);
    int var8 = readInt(var5);
    SharedStrings var9 = std::make_shared<SharedStrings>();

         for (int var10 = 0; var10 < var8; var10++) {
    std::string var11 = readString(var5);
    std::string var12 = var11.trim();
    std::string var13 = readString(var5);
            this.tileImages.push_back(var13);
    int var14 = readInt(var5);
    int var15 = readInt(var5);
    int var16 = readInt(var5);
    int var17 = readInt(var5);

            for (int var18 = 0; var18 < var17; var18++) {
    int var19 = readInt(var5);

               for (int var20 = 0; var20 < var19; var20++) {
                  var11 = readString(var5);
    std::string var21 = var11.trim();
                  var11 = readString(var5);
    std::string var22 = var11.trim();
    IsoObjectType var23 = IsoObjectType.FromString(var21);
                  var21 = var9.get(var21);
    std::vector var24 = nullptr;
                  if (PropertyValueMap.containsKey(var21)) {
                     var24 = PropertyValueMap.get(var21);
                  } else {
                     var24 = std::make_unique<std::vector>();
                     PropertyValueMap.put(var21, var24);
                  }

                  if (!var24.contains(var22)) {
                     var24.push_back(var22);
                  }
               }
            }
         }
      } catch (Exception var29) {
         Logger.getLogger(GameWindow.class.getName()).log(Level.SEVERE, nullptr, var29);
      }
   }

    void SetCustomPropertyValues() {
      PropertyValueMap.get("WindowN").push_back("WindowN");
      PropertyValueMap.get("WindowW").push_back("WindowW");
      PropertyValueMap.get("DoorWallN").push_back("DoorWallN");
      PropertyValueMap.get("DoorWallW").push_back("DoorWallW");
      PropertyValueMap.get("WallSE").push_back("WallSE");
    std::vector var1 = new std::vector();

      for (int var2 = -96; var2 <= 96; var2++) {
    std::string var3 = int.toString(var2);
         var1.push_back(var3);
      }

      PropertyValueMap.put("Noffset", var1);
      PropertyValueMap.put("Soffset", var1);
      PropertyValueMap.put("Woffset", var1);
      PropertyValueMap.put("Eoffset", var1);
      PropertyValueMap.get("tree").push_back("5");
      PropertyValueMap.get("tree").push_back("6");
      PropertyValueMap.get("lightR").push_back("0");
      PropertyValueMap.get("lightG").push_back("0");
      PropertyValueMap.get("lightB").push_back("0");
   }

    void setOpenDoorProperties(const std::string& var1, std::vector<IsoSprite> var2) {
      for (int var3 = 0; var3 < var2.size(); var3++) {
    IsoSprite var4 = (IsoSprite)var2.get(var3);
         if ((var4.getType() == IsoObjectType.doorN || var4.getType() == IsoObjectType.doorW) && !var4.getProperties().Is(IsoFlagType.open)) {
    std::string var5 = var4.getProperties().Val("DoubleDoor");
            if (var5 != nullptr) {
    int var6 = PZMath.tryParseInt(var5, -1);
               if (var6 >= 5) {
                  var4.getProperties().Set(IsoFlagType.open);
               }
            } else {
    std::string var8 = var4.getProperties().Val("GarageDoor");
               if (var8 != nullptr) {
    int var7 = PZMath.tryParseInt(var8, -1);
                  if (var7 >= 4) {
                     var4.getProperties().Set(IsoFlagType.open);
                  }
               } else {
    IsoSprite var9 = (IsoSprite)IsoSpriteManager.instance.NamedMap.get(var1 + "_" + (var4.tileSheetIndex + 2));
                  if (var9 != nullptr) {
                     var9.setType(var4.getType());
                     var9.getProperties().Set(var4.getType() == IsoObjectType.doorN ? IsoFlagType.doorN : IsoFlagType.doorW);
                     var9.getProperties().Set(IsoFlagType.open);
                  }
               }
            }
         }
      }
   }

    void saveMovableStats(std::vector<std::string>> var1, int var2, int var3, int var4, int var5, int var6) {
    File var7 = std::make_shared<File>(ZomboidFileSystem.instance.getCacheDir());
      if (var7.exists() && var7.isDirectory()) {
    File var8 = std::make_shared<File>(ZomboidFileSystem.instance.getCacheDir() + File.separator + "movables_stats_" + var2 + ".txt");

         try (FileWriter var9 = std::make_shared<FileWriter>(var8, false)) {
            var9.write("### Movable objects ###" + System.lineSeparator());
            var9.write("Single Face: " + var3 + System.lineSeparator());
            var9.write("Multi Face: " + var4 + System.lineSeparator());
            var9.write("Multi Face & Multi Sprite: " + var5 + System.lineSeparator());
            var9.write("Total objects : " + (var3 + var4 + var5) + System.lineSeparator());
            var9.write(" " + System.lineSeparator());
            var9.write("Total sprites : " + var6 + System.lineSeparator());
            var9.write(" " + System.lineSeparator());

            for (Entry var11 : var1.entrySet()) {
               var9.write((std::string)var11.getKey() + System.lineSeparator());

               for (std::string var13 : (std::vector)var11.getValue()) {
                  var9.write("\t" + var13 + System.lineSeparator());
               }
            }
         } catch (Exception var16) {
            var16.printStackTrace();
         }
      }
   }

    void addJumboTreeTileset(IsoSpriteManager var1, int var2, const std::string& var3, int var4, int var5, int var6) {
    uint8_t var7 = 2;

      for (int var8 = 0; var8 < var5; var8++) {
         for (int var9 = 0; var9 < var7; var9++) {
    std::string var10 = "e_" + var3 + "JUMBO_1";
    int var11 = var8 * var7 + var9;
    IsoSprite var12 = var1.AddSprite(var10 + "_" + var11, var2 * 512 * 512 + var4 * 512 + var11);

            assert GameServer.bServer
               || !var12.CurrentAnim.Frames.empty() && ((IsoDirectionFrame)var12.CurrentAnim.Frames.get(0)).getTexture(IsoDirections.N) != nullptr;

            var12.setName(var10 + "_" + var11);
            var12.setType(IsoObjectType.tree);
            var12.getProperties().Set("tree", var9 == 0 ? "5" : "6");
            var12.getProperties().UnSet(IsoFlagType.solid);
            var12.getProperties().Set(IsoFlagType.blocksight);
            var12.getProperties().CreateKeySet();
            var12.moveWithWind = true;
            var12.windType = var6;
         }
      }
   }

    void JumboTreeDefinitions(IsoSpriteManager var1, int var2) {
      this.addJumboTreeTileset(var1, var2, "americanholly", 1, 2, 3);
      this.addJumboTreeTileset(var1, var2, "americanlinden", 2, 6, 2);
      this.addJumboTreeTileset(var1, var2, "canadianhemlock", 3, 2, 3);
      this.addJumboTreeTileset(var1, var2, "carolinasilverbell", 4, 6, 1);
      this.addJumboTreeTileset(var1, var2, "cockspurhawthorn", 5, 6, 2);
      this.addJumboTreeTileset(var1, var2, "dogwood", 6, 6, 2);
      this.addJumboTreeTileset(var1, var2, "easternredbud", 7, 6, 2);
      this.addJumboTreeTileset(var1, var2, "redmaple", 8, 6, 2);
      this.addJumboTreeTileset(var1, var2, "riverbirch", 9, 6, 1);
      this.addJumboTreeTileset(var1, var2, "virginiapine", 10, 2, 1);
      this.addJumboTreeTileset(var1, var2, "yellowwood", 11, 6, 2);
    uint8_t var3 = 12;
    uint8_t var4 = 0;
    IsoSprite var5 = var1.AddSprite("jumbo_tree_01_" + var4, var2 * 512 * 512 + var3 * 512 + var4);
      var5.setName("jumbo_tree_01_" + var4);
      var5.setType(IsoObjectType.tree);
      var5.getProperties().Set("tree", "4");
      var5.getProperties().UnSet(IsoFlagType.solid);
      var5.getProperties().Set(IsoFlagType.blocksight);
   }

    void loadedTileDefinitions() {
      CellLoader.smashedWindowSpriteMap.clear();

      for (IsoSprite var2 : IsoSpriteManager.instance.NamedMap.values()) {
    PropertyContainer var3 = var2.getProperties();
         if (var3.Is(IsoFlagType.windowW) || var3.Is(IsoFlagType.windowN)) {
    std::string var4 = var3.Val("SmashedTileOffset");
            if (var4 != nullptr) {
    int var5 = PZMath.tryParseInt(var4, 0);
               if (var5 != 0) {
    IsoSprite var6 = IsoSprite.getSprite(IsoSpriteManager.instance, var2, var5);
                  if (var6 != nullptr) {
                     CellLoader.smashedWindowSpriteMap.put(var6, var2);
                  }
               }
            }
         }
      }
   }

    bool LoadPlayerForInfo() {
      if (GameClient.bClient) {
         return ClientPlayerDB.getInstance().loadNetworkPlayerInfo(1);
      } else {
    File var1 = ZomboidFileSystem.instance.getFileInCurrentSave("map_p.bin");
         if (!var1.exists()) {
            PlayerDB.getInstance().importPlayersFromVehiclesDB();
            return PlayerDB.getInstance().loadLocalPlayerInfo(1);
         } else {
    FileInputStream var2 = std::make_shared<FileInputStream>(var1);
    BufferedInputStream var3 = std::make_shared<BufferedInputStream>(var2);
            /* synchronized - TODO: add std::mutex */ (SliceY.SliceBufferLock) {
               SliceY.SliceBuffer.clear();
    int var5 = var3.read(SliceY.SliceBuffer.array());
               SliceY.SliceBuffer.limit(var5);
               var3.close();
    uint8_t var6 = SliceY.SliceBuffer.get();
    uint8_t var7 = SliceY.SliceBuffer.get();
    uint8_t var8 = SliceY.SliceBuffer.get();
    uint8_t var9 = SliceY.SliceBuffer.get();
    int var10 = -1;
               if (var6 == 80 && var7 == 76 && var8 == 89 && var9 == 82) {
                  var10 = SliceY.SliceBuffer.getInt();
               } else {
                  SliceY.SliceBuffer.rewind();
               }

               if (var10 >= 69) {
    std::string var11 = GameWindow.ReadString(SliceY.SliceBuffer);
                  if (GameClient.bClient && var10 < 71) {
                     var11 = ServerOptions.instance.ServerPlayerID.getValue();
                  }

                  if (GameClient.bClient && !IsoPlayer.isServerPlayerIDValid(var11)) {
                     GameLoadingState.GameLoadingString = Translator.getText("IGUI_MP_ServerPlayerIDMismatch");
                     GameLoadingState.playerWrongIP = true;
    return false;
                  }
               } else if (GameClient.bClient && ServerOptions.instance.ServerPlayerID.getValue().empty()) {
                  GameLoadingState.GameLoadingString = Translator.getText("IGUI_MP_ServerPlayerIDMissing");
                  GameLoadingState.playerWrongIP = true;
    return false;
               }

               WorldX = SliceY.SliceBuffer.getInt();
               WorldY = SliceY.SliceBuffer.getInt();
               IsoChunkMap.WorldXA = SliceY.SliceBuffer.getInt();
               IsoChunkMap.WorldYA = SliceY.SliceBuffer.getInt();
               IsoChunkMap.WorldZA = SliceY.SliceBuffer.getInt();
               IsoChunkMap.WorldXA = IsoChunkMap.WorldXA + 300 * saveoffsetx;
               IsoChunkMap.WorldYA = IsoChunkMap.WorldYA + 300 * saveoffsety;
               IsoChunkMap.SWorldX[0] = WorldX;
               IsoChunkMap.SWorldY[0] = WorldY;
               IsoChunkMap.SWorldX[0] = IsoChunkMap.SWorldX[0] + 30 * saveoffsetx;
               IsoChunkMap.SWorldY[0] = IsoChunkMap.SWorldY[0] + 30 * saveoffsety;
    return true;
            }
         }
      }
   }

    void init() {
      if (!Core.bTutorial) {
         this.randomizedBuildingList.push_back(std::make_unique<RBSafehouse>());
         this.randomizedBuildingList.push_back(std::make_unique<RBBurnt>());
         this.randomizedBuildingList.push_back(std::make_unique<RBOther>());
         this.randomizedBuildingList.push_back(std::make_unique<RBLooted>());
         this.randomizedBuildingList.push_back(std::make_unique<RBBurntFireman>());
         this.randomizedBuildingList.push_back(std::make_unique<RBBurntCorpse>());
         this.randomizedBuildingList.push_back(std::make_unique<RBShopLooted>());
         this.randomizedBuildingList.push_back(std::make_unique<RBKateAndBaldspot>());
         this.randomizedBuildingList.push_back(std::make_unique<RBStripclub>());
         this.randomizedBuildingList.push_back(std::make_unique<RBSchool>());
         this.randomizedBuildingList.push_back(std::make_unique<RBSpiffo>());
         this.randomizedBuildingList.push_back(std::make_unique<RBPizzaWhirled>());
         this.randomizedBuildingList.push_back(std::make_unique<RBPileOCrepe>());
         this.randomizedBuildingList.push_back(std::make_unique<RBCafe>());
         this.randomizedBuildingList.push_back(std::make_unique<RBBar>());
         this.randomizedBuildingList.push_back(std::make_unique<RBOffice>());
         this.randomizedBuildingList.push_back(std::make_unique<RBHairSalon>());
         this.randomizedBuildingList.push_back(std::make_unique<RBClinic>());
         this.randomizedVehicleStoryList.push_back(std::make_unique<RVSUtilityVehicle>());
         this.randomizedVehicleStoryList.push_back(std::make_unique<RVSConstructionSite>());
         this.randomizedVehicleStoryList.push_back(std::make_unique<RVSBurntCar>());
         this.randomizedVehicleStoryList.push_back(std::make_unique<RVSPoliceBlockadeShooting>());
         this.randomizedVehicleStoryList.push_back(std::make_unique<RVSPoliceBlockade>());
         this.randomizedVehicleStoryList.push_back(std::make_unique<RVSCarCrash>());
         this.randomizedVehicleStoryList.push_back(std::make_unique<RVSAmbulanceCrash>());
         this.randomizedVehicleStoryList.push_back(std::make_unique<RVSCarCrashCorpse>());
         this.randomizedVehicleStoryList.push_back(std::make_unique<RVSChangingTire>());
         this.randomizedVehicleStoryList.push_back(std::make_unique<RVSFlippedCrash>());
         this.randomizedVehicleStoryList.push_back(std::make_unique<RVSBanditRoad>());
         this.randomizedVehicleStoryList.push_back(std::make_unique<RVSTrailerCrash>());
         this.randomizedVehicleStoryList.push_back(std::make_unique<RVSCrashHorde>());
         this.randomizedZoneList.push_back(std::make_unique<RZSForestCamp>());
         this.randomizedZoneList.push_back(std::make_unique<RZSForestCampEaten>());
         this.randomizedZoneList.push_back(std::make_unique<RZSBuryingCamp>());
         this.randomizedZoneList.push_back(std::make_unique<RZSBeachParty>());
         this.randomizedZoneList.push_back(std::make_unique<RZSFishingTrip>());
         this.randomizedZoneList.push_back(std::make_unique<RZSBBQParty>());
         this.randomizedZoneList.push_back(std::make_unique<RZSHunterCamp>());
         this.randomizedZoneList.push_back(std::make_unique<RZSSexyTime>());
         this.randomizedZoneList.push_back(std::make_unique<RZSTrapperCamp>());
         this.randomizedZoneList.push_back(std::make_unique<RZSBaseball>());
         this.randomizedZoneList.push_back(std::make_unique<RZSMusicFestStage>());
         this.randomizedZoneList.push_back(std::make_unique<RZSMusicFest>());
      }

      zombie.randomizedWorld.randomizedBuilding.RBBasic.getUniqueRDSSpawned().clear();
      if (!GameClient.bClient && !GameServer.bServer) {
         BodyDamageSync.instance = nullptr;
      } else {
         BodyDamageSync.instance = std::make_unique<BodyDamageSync>();
      }

      if (GameServer.bServer) {
         Core.GameSaveWorld = GameServer.ServerName;
    std::string var1 = ZomboidFileSystem.instance.getCurrentSaveDir();
    File var2 = std::make_shared<File>(var1);
         if (!var2.exists()) {
            GameServer.ResetID = Rand.Next(10000000);
            ServerOptions.instance.putSaveOption("ResetID", std::string.valueOf(GameServer.ResetID));
         }

         GlobalObject.createWorld(Core.GameSaveWorld);
      }

      SavedWorldVersion = this.readWorldVersion();
      if (!GameServer.bServer) {
    File var31 = ZomboidFileSystem.instance.getFileInCurrentSave("map_ver.bin");

         try (
    FileInputStream var34 = std::make_shared<FileInputStream>(var31);
    DataInputStream var3 = std::make_shared<DataInputStream>(var34);
         ) {
    int var4 = var3.readInt();
            if (var4 >= 25) {
    std::string var5 = GameWindow.ReadString(var3);
               if (!GameClient.bClient) {
                  Core.GameMap = var5;
               }
            }

            if (var4 >= 74) {
               this.setDifficulty(GameWindow.ReadString(var3));
            }
         } catch (FileNotFoundException var30) {
         }
      }

      if (!GameServer.bServer || !GameServer.bSoftReset) {
         this.MetaGrid.CreateStep1();
      }

      LuaEventManager.triggerEvent("OnPreDistributionMerge");
      LuaEventManager.triggerEvent("OnDistributionMerge");
      LuaEventManager.triggerEvent("OnPostDistributionMerge");
      ItemPickerJava.Parse();
      VehiclesDB2.instance.init();
      LuaEventManager.triggerEvent("OnInitWorld");
      if (!GameClient.bClient) {
         SandboxOptions.instance.load();
      }

      this.bHydroPowerOn = GameTime.getInstance().NightsSurvived < SandboxOptions.getInstance().getElecShutModifier();
      ZomboidGlobals.toLua();
      ItemPickerJava.InitSandboxLootSettings();
      this.SurvivorDescriptors.clear();
      IsoSpriteManager.instance.Dispose();
      if (GameClient.bClient && ServerOptions.instance.DoLuaChecksum.getValue()) {
         try {
            NetChecksum.comparer.beginCompare();
            GameLoadingState.GameLoadingString = Translator.getText("IGUI_MP_Checksum");
    long var32 = System.currentTimeMillis();
    long var36 = var32;

            while (!GameClient.checksumValid) {
               if (GameWindow.bServerDisconnected) {
                  return;
               }

               if (System.currentTimeMillis() > var32 + 8000L) {
                  DebugLog.log("checksum: timed out waiting for the server to respond");
                  GameClient.connection.forceDisconnect("world-timeout-response");
                  GameWindow.bServerDisconnected = true;
                  GameWindow.kickReason = Translator.getText("UI_GameLoad_TimedOut");
                  return;
               }

               if (System.currentTimeMillis() > var36 + 1000L) {
                  DebugLog.log("checksum: waited one second");
                  var36 += 1000L;
               }

               NetChecksum.comparer.update();
               if (GameClient.checksumValid) {
                  break;
               }

               Thread.sleep(100L);
            }
         } catch (Exception var27) {
            var27.printStackTrace();
         }
      }

      GameLoadingState.GameLoadingString = Translator.getText("IGUI_MP_LoadTileDef");
    IsoSpriteManager var33 = IsoSpriteManager.instance;
      this.tileImages.clear();
    ZomboidFileSystem var35 = ZomboidFileSystem.instance;
      this.LoadTileDefinitionsPropertyStrings(var33, var35.getMediaPath("tiledefinitions.tiles"), 0);
      this.LoadTileDefinitionsPropertyStrings(var33, var35.getMediaPath("newtiledefinitions.tiles"), 1);
      this.LoadTileDefinitionsPropertyStrings(var33, var35.getMediaPath("tiledefinitions_erosion.tiles"), 2);
      this.LoadTileDefinitionsPropertyStrings(var33, var35.getMediaPath("tiledefinitions_apcom.tiles"), 3);
      this.LoadTileDefinitionsPropertyStrings(var33, var35.getMediaPath("tiledefinitions_overlays.tiles"), 4);
      this.LoadTileDefinitionsPropertyStrings(var33, var35.getMediaPath("tiledefinitions_noiseworks.patch.tiles"), -1);
      ZomboidFileSystem.instance.loadModTileDefPropertyStrings();
      this.SetCustomPropertyValues();
      this.GenerateTilePropertyLookupTables();
      this.LoadTileDefinitions(var33, var35.getMediaPath("tiledefinitions.tiles"), 0);
      this.LoadTileDefinitions(var33, var35.getMediaPath("newtiledefinitions.tiles"), 1);
      this.LoadTileDefinitions(var33, var35.getMediaPath("tiledefinitions_erosion.tiles"), 2);
      this.LoadTileDefinitions(var33, var35.getMediaPath("tiledefinitions_apcom.tiles"), 3);
      this.LoadTileDefinitions(var33, var35.getMediaPath("tiledefinitions_overlays.tiles"), 4);
      this.LoadTileDefinitions(var33, var35.getMediaPath("tiledefinitions_noiseworks.patch.tiles"), -1);
      this.JumboTreeDefinitions(var33, 5);
      ZomboidFileSystem.instance.loadModTileDefs();
      GameLoadingState.GameLoadingString = "";
      var33.AddSprite("media/ui/missing-tile.png");
      LuaEventManager.triggerEvent("OnLoadedTileDefinitions", var33);
      this.loadedTileDefinitions();
      if (GameServer.bServer && GameServer.bSoftReset) {
         WorldConverter.instance.softreset();
      }

      try {
         WeatherFxMask.init();
      } catch (Exception var23) {
         System.out.print(var23.getStackTrace());
      }

      TemplateText.Initialize();
      IsoRegions.init();
      ObjectRenderEffects.init();
      WorldConverter.instance.convert(Core.GameSaveWorld, var33);
      if (!GameLoadingState.build23Stop) {
         SandboxOptions.instance.handleOldZombiesFile2();
         GameTime.getInstance().init();
         GameTime.getInstance().load();
         ImprovedFog.init();
         ZomboidRadio.getInstance().Init(SavedWorldVersion);
         GlobalModData.instance.init();
         if (GameServer.bServer && Core.getInstance().getPoisonousBerry() == nullptr) {
            Core.getInstance().initPoisonousBerry();
         }

         if (GameServer.bServer && Core.getInstance().getPoisonousMushroom() == nullptr) {
            Core.getInstance().initPoisonousMushroom();
         }

         ErosionGlobals.Boot(var33);
         WorldDictionary.init();
         WorldMarkers.instance.init();
         if (GameServer.bServer) {
            SharedDescriptors.initSharedDescriptors();
         }

         PersistentOutfits.instance.init();
         VirtualZombieManager.instance.init();
         VehicleIDMap.instance.Reset();
         VehicleManager.instance = std::make_unique<VehicleManager>();
         GameLoadingState.GameLoadingString = Translator.getText("IGUI_MP_InitMap");
         this.MetaGrid.CreateStep2();
         ClimateManager.getInstance().init(this.MetaGrid);
         SafeHouse.init();
         if (!GameClient.bClient) {
            StashSystem.init();
         }

         LuaEventManager.triggerEvent("OnLoadMapZones");
         this.MetaGrid.load();
         this.MetaGrid.loadZones();
         this.MetaGrid.processZones();
         LuaEventManager.triggerEvent("OnLoadedMapZones");
         if (GameServer.bServer) {
            ServerMap.instance.init(this.MetaGrid);
         }

    int var37 = 0;
    int var40 = 0;
         if (GameClient.bClient) {
            if (ClientPlayerDB.getInstance().clientLoadNetworkPlayer() && ClientPlayerDB.getInstance().isAliveMainNetworkPlayer()) {
               var40 = 1;
            }
         } else {
            var40 = PlayerDBHelper.isPlayerAlive(ZomboidFileSystem.instance.getCurrentSaveDir(), 1);
         }

         if (GameServer.bServer) {
            ServerPlayerDB.setAllow(true);
         }

         if (!GameClient.bClient && !GameServer.bServer) {
            PlayerDB.setAllow(true);
         }

    int var42 = 0;
    int var6 = 0;
    int var7 = 0;
         if (var40) {
            var37 = (boolean)1;
            if (!this.LoadPlayerForInfo()) {
               return;
            }

            WorldX = IsoChunkMap.SWorldX[IsoPlayer.getPlayerIndex()];
            WorldY = IsoChunkMap.SWorldY[IsoPlayer.getPlayerIndex()];
            var42 = IsoChunkMap.WorldXA;
            var6 = IsoChunkMap.WorldYA;
            var7 = IsoChunkMap.WorldZA;
         } else {
            var37 = (boolean)0;
            if (GameClient.bClient && !ServerOptions.instance.SpawnPoint.getValue().empty()) {
               std::string[] var8 = ServerOptions.instance.SpawnPoint.getValue().split(",");
               if (var8.length == 3) {
                  try {
                     IsoChunkMap.MPWorldXA = std::make_shared<int>(var8[0].trim());
                     IsoChunkMap.MPWorldYA = std::make_shared<int>(var8[1].trim());
                     IsoChunkMap.MPWorldZA = std::make_shared<int>(var8[2].trim());
                  } catch (NumberFormatException var22) {
                     DebugLog.log("ERROR: SpawnPoint must be x,y,z, got \"" + ServerOptions.instance.SpawnPoint.getValue() + "\"");
                     IsoChunkMap.MPWorldXA = 0;
                     IsoChunkMap.MPWorldYA = 0;
                     IsoChunkMap.MPWorldZA = 0;
                  }
               } else {
                  DebugLog.log("ERROR: SpawnPoint must be x,y,z, got \"" + ServerOptions.instance.SpawnPoint.getValue() + "\"");
               }
            }

            if (this.getLuaSpawnCellX() >= 0 && (!GameClient.bClient || IsoChunkMap.MPWorldXA == 0 && IsoChunkMap.MPWorldYA == 0)) {
               IsoChunkMap.WorldXA = this.getLuaPosX() + 300 * this.getLuaSpawnCellX();
               IsoChunkMap.WorldYA = this.getLuaPosY() + 300 * this.getLuaSpawnCellY();
               IsoChunkMap.WorldZA = this.getLuaPosZ();
               if (GameClient.bClient && ServerOptions.instance.SafehouseAllowRespawn.getValue()) {
                  for (int var48 = 0; var48 < SafeHouse.getSafehouseList().size(); var48++) {
    SafeHouse var9 = (SafeHouse)SafeHouse.getSafehouseList().get(var48);
                     if (var9.getPlayers().contains(GameClient.username) && var9.isRespawnInSafehouse(GameClient.username)) {
                        IsoChunkMap.WorldXA = var9.getX() + var9.getH() / 2;
                        IsoChunkMap.WorldYA = var9.getY() + var9.getW() / 2;
                        IsoChunkMap.WorldZA = 0;
                     }
                  }
               }

               WorldX = IsoChunkMap.WorldXA / 10;
               WorldY = IsoChunkMap.WorldYA / 10;
            } else if (GameClient.bClient) {
               IsoChunkMap.WorldXA = IsoChunkMap.MPWorldXA;
               IsoChunkMap.WorldYA = IsoChunkMap.MPWorldYA;
               IsoChunkMap.WorldZA = IsoChunkMap.MPWorldZA;
               WorldX = IsoChunkMap.WorldXA / 10;
               WorldY = IsoChunkMap.WorldYA / 10;
            }
         }

         Core.getInstance();
    KahluaTable var49 = (KahluaTable)LuaManager.env.rawget("selectedDebugScenario");
         if (var49 != nullptr) {
    KahluaTable var51 = (KahluaTable)var49.rawget("startLoc");
    int var10 = ((double)var51.rawget("x")).intValue();
    int var11 = ((double)var51.rawget("y")).intValue();
    int var12 = ((double)var51.rawget("z")).intValue();
            IsoChunkMap.WorldXA = var10;
            IsoChunkMap.WorldYA = var11;
            IsoChunkMap.WorldZA = var12;
            WorldX = IsoChunkMap.WorldXA / 10;
            WorldY = IsoChunkMap.WorldYA / 10;
         }

         MapCollisionData.instance.init(instance.getMetaGrid());
         ZombiePopulationManager.instance.init(instance.getMetaGrid());
         PolygonalMap2.instance.init(instance.getMetaGrid());
         GlobalObjectLookup.init(instance.getMetaGrid());
         if (!GameServer.bServer) {
            SpawnPoints.instance.initSinglePlayer();
         }

         WorldStreamer.instance.create();
         this.CurrentCell = CellLoader.LoadCellBinaryChunk(var33, WorldX, WorldY);
         ClimateManager.getInstance().postCellLoadSetSnow();
         GameLoadingState.GameLoadingString = Translator.getText("IGUI_MP_LoadWorld");
         MapCollisionData.instance.start();
         MapItem.LoadWorldMap();

         while (WorldStreamer.instance.isBusy()) {
            try {
               Thread.sleep(100L);
            } catch (InterruptedException var21) {
               var21.printStackTrace();
            }
         }

    std::vector var50 = new std::vector();
         var50.addAll(IsoChunk.loadGridSquare);

    for (auto& var55 : var50)            this.CurrentCell.ChunkMap[0].setChunkDirect(var55, false);
         }

         IsoChunk.bDoServerRequests = true;
         if (var37 && SystemDisabler.doPlayerCreation) {
            this.CurrentCell.LoadPlayer(SavedWorldVersion);
            if (GameClient.bClient) {
               IsoPlayer.getInstance().setUsername(GameClient.username);
            }

            ZomboidRadio.getInstance().getRecordedMedia().handleLegacyListenedLines(IsoPlayer.getInstance());
         } else {
            ZomboidRadio.getInstance().getRecordedMedia().handleLegacyListenedLines(nullptr);
    IsoGridSquare var53 = nullptr;
            if (IsoPlayer.numPlayers == 0) {
               IsoPlayer.numPlayers = 1;
            }

    int var56 = IsoChunkMap.WorldXA;
    int var57 = IsoChunkMap.WorldYA;
    int var58 = IsoChunkMap.WorldZA;
            if (GameClient.bClient && !ServerOptions.instance.SpawnPoint.getValue().empty()) {
               std::string[] var13 = ServerOptions.instance.SpawnPoint.getValue().split(",");
               if (var13.length != 3) {
                  DebugLog.log("ERROR: SpawnPoint must be x,y,z, got \"" + ServerOptions.instance.SpawnPoint.getValue() + "\"");
               } else {
                  try {
    int var14 = std::make_shared<int>(var13[0].trim());
    int var15 = std::make_shared<int>(var13[1].trim());
    int var16 = std::make_shared<int>(var13[2].trim());
                     if (GameClient.bClient && ServerOptions.instance.SafehouseAllowRespawn.getValue()) {
                        for (int var17 = 0; var17 < SafeHouse.getSafehouseList().size(); var17++) {
    SafeHouse var18 = (SafeHouse)SafeHouse.getSafehouseList().get(var17);
                           if (var18.getPlayers().contains(GameClient.username) && var18.isRespawnInSafehouse(GameClient.username)) {
                              var14 = var18.getX() + var18.getH() / 2;
                              var15 = var18.getY() + var18.getW() / 2;
                              var16 = 0;
                           }
                        }
                     }

                     if (this.CurrentCell.getGridSquare(var14, var15, var16) != nullptr) {
                        var56 = var14;
                        var57 = var15;
                        var58 = var16;
                     }
                  } catch (NumberFormatException var26) {
                     DebugLog.log("ERROR: SpawnPoint must be x,y,z, got \"" + ServerOptions.instance.SpawnPoint.getValue() + "\"");
                  }
               }
            }

            var53 = this.CurrentCell.getGridSquare(var56, var57, var58);
            if (SystemDisabler.doPlayerCreation && !GameServer.bServer) {
               if (var53 != nullptr && var53.isFree(false) && var53.getRoom() != nullptr) {
    IsoGridSquare var59 = var53;
                  var53 = var53.getRoom().getFreeTile();
                  if (var53 == nullptr) {
                     var53 = var59;
                  }
               }

    IsoPlayer var60 = nullptr;
               if (this.getLuaPlayerDesc() != nullptr) {
                  if (GameClient.bClient && ServerOptions.instance.SafehouseAllowRespawn.getValue()) {
                     var53 = this.CurrentCell.getGridSquare(IsoChunkMap.WorldXA, IsoChunkMap.WorldYA, IsoChunkMap.WorldZA);
                     if (var53 != nullptr && var53.isFree(false) && var53.getRoom() != nullptr) {
    IsoGridSquare var61 = var53;
                        var53 = var53.getRoom().getFreeTile();
                        if (var53 == nullptr) {
                           var53 = var61;
                        }
                     }
                  }

                  if (var53 == nullptr) {
                     throw RuntimeException("can't create player at x,y,z=" + var56 + "," + var57 + "," + var58 + " because the square is nullptr");
                  }

                  WorldSimulation.instance.create();
                  var60 = std::make_shared<IsoPlayer>(instance.CurrentCell, this.getLuaPlayerDesc(), var53.getX(), var53.getY(), var53.getZ());
                  if (GameClient.bClient) {
                     var60.setUsername(GameClient.username);
                  }

                  var60.setDir(IsoDirections.SE);
                  var60.sqlID = 1;
                  IsoPlayer.players[0] = var60;
                  IsoPlayer.setInstance(var60);
                  IsoCamera.CamCharacter = var60;
               }

    IsoPlayer var62 = IsoPlayer.getInstance();
               var62.applyTraits(this.getLuaTraits());
    Profession var63 = ProfessionFactory.getProfession(var62.getDescriptor().getProfession());
               if (var63 != nullptr && !var63.getFreeRecipes().empty()) {
                  for (std::string var66 : var63.getFreeRecipes()) {
                     var62.getKnownRecipes().push_back(var66);
                  }
               }

               for (std::string var67 : this.getLuaTraits()) {
    Trait var68 = TraitFactory.getTrait(var67);
                  if (var68 != nullptr && !var68.getFreeRecipes().empty()) {
                     for (std::string var20 : var68.getFreeRecipes()) {
                        var62.getKnownRecipes().push_back(var20);
                     }
                  }
               }

               if (var53 != nullptr && var53.getRoom() != nullptr) {
                  var53.getRoom().def.setExplored(true);
                  var53.getRoom().building.setAllExplored(true);
                  if (!GameServer.bServer && !GameClient.bClient) {
                     ZombiePopulationManager.instance.playerSpawnedAt(var53.getX(), var53.getY(), var53.getZ());
                  }
               }

               var62.createKeyRing();
               if (!GameClient.bClient) {
                  Core.getInstance().initPoisonousBerry();
                  Core.getInstance().initPoisonousMushroom();
               }

               LuaEventManager.triggerEvent("OnNewGame", var60, var53);
            }
         }

         if (PlayerDB.isAllow()) {
            PlayerDB.getInstance().m_canSavePlayers = true;
         }

         if (ClientPlayerDB.isAllow()) {
            ClientPlayerDB.getInstance().canSavePlayers = true;
         }

         TutorialManager.instance.ActiveControlZombies = false;
         ReanimatedPlayers.instance.loadReanimatedPlayers();
         if (IsoPlayer.getInstance() != nullptr) {
            if (GameClient.bClient) {
               var37 = (int)IsoPlayer.getInstance().getX();
               var40 = (int)IsoPlayer.getInstance().getY();
               var42 = (int)IsoPlayer.getInstance().getZ();

               while (var42 > 0) {
    IsoGridSquare var46 = this.CurrentCell.getGridSquare(var37, var40, var42);
                  if (var46 != nullptr && var46.TreatAsSolidFloor()) {
                     break;
                  }

                  IsoPlayer.getInstance().setZ(--var42);
               }
            }

            IsoPlayer.getInstance()
               .setCurrent(
                  this.CurrentCell.getGridSquare((int)IsoPlayer.getInstance().getX(), (int)IsoPlayer.getInstance().getY(), (int)IsoPlayer.getInstance().getZ())
               );
         }

         if (!this.bLoaded) {
            if (!this.CurrentCell.getBuildingList().empty()) {
            }

            if (!this.bLoaded) {
               this.PopulateCellWithSurvivors();
            }
         }

         if (IsoPlayer.players[0] != nullptr && !this.CurrentCell.getObjectList().contains(IsoPlayer.players[0])) {
            this.CurrentCell.getObjectList().push_back(IsoPlayer.players[0]);
         }

         LightingThread.instance.create();
         GameLoadingState.GameLoadingString = "";
         initMessaging();
         WorldDictionary.onWorldLoaded();
      }
   }

    int readWorldVersion() {
      if (GameServer.bServer) {
    File var21 = ZomboidFileSystem.instance.getFileInCurrentSave("map_t.bin");

         try (
    FileInputStream var22 = std::make_shared<FileInputStream>(var21);
    DataInputStream var23 = std::make_shared<DataInputStream>(var22);
         ) {
    uint8_t var24 = var23.readByte();
    uint8_t var5 = var23.readByte();
    uint8_t var6 = var23.readByte();
    uint8_t var7 = var23.readByte();
            if (var24 == 71 && var5 == 77 && var6 == 84 && var7 == 77) {
               return var23.readInt();
            }

            return -1;
         } catch (FileNotFoundException var19) {
         } catch (IOException var20) {
            ExceptionLogger.logException(var20);
         }

         return -1;
      } else {
    File var1 = ZomboidFileSystem.instance.getFileInCurrentSave("map_ver.bin");

         try {
    int var4;
            try (
    FileInputStream var2 = std::make_shared<FileInputStream>(var1);
    DataInputStream var3 = std::make_shared<DataInputStream>(var2);
            ) {
               var4 = var3.readInt();
            }

    return var4;
         } catch (FileNotFoundException var15) {
         } catch (IOException var16) {
            ExceptionLogger.logException(var16);
         }

         return -1;
      }
   }

   public std::vector<std::string> getLuaTraits() {
      if (this.luatraits == nullptr) {
         this.luatraits = std::make_unique<std::vector<>>();
      }

      return this.luatraits;
   }

    void addLuaTrait(const std::string& var1) {
      this.getLuaTraits().push_back(var1);
   }

    SurvivorDesc getLuaPlayerDesc() {
      return this.luaDesc;
   }

    void setLuaPlayerDesc(SurvivorDesc var1) {
      this.luaDesc = var1;
   }

    void KillCell() {
      this.helicopter.deactivate();
      CollisionManager.instance.ContactMap.clear();
      IsoDeadBody.Reset();
      FliesSound.instance.Reset();
      IsoObjectPicker.Instance.Init();
      IsoChunkMap.SharedChunks.clear();
      SoundManager.instance.StopMusic();
      WorldSoundManager.instance.KillCell();
      ZombieGroupManager.instance.Reset();
      this.CurrentCell.Dispose();
      IsoSpriteManager.instance.Dispose();
      this.CurrentCell = nullptr;
      CellLoader.wanderRoom = nullptr;
      IsoLot.Dispose();
      IsoGameCharacter.getSurvivorMap().clear();
      IsoPlayer.getInstance().setCurrent(nullptr);
      IsoPlayer.getInstance().setLast(nullptr);
      IsoPlayer.getInstance().square = nullptr;
      RainManager.reset();
      IsoFireManager.Reset();
      ObjectAmbientEmitters.Reset();
      ZombieVocalsManager.Reset();
      IsoWaterFlow.Reset();
      this.MetaGrid.Dispose();
      instance = std::make_unique<IsoWorld>();
   }

    void setDrawWorld(bool var1) {
      this.bDrawWorld = var1;
   }

    void sceneCullZombies() {
      this.zombieWithModel.clear();
      this.zombieWithoutModel.clear();

      for (int var1 = 0; var1 < this.CurrentCell.getZombieList().size(); var1++) {
    IsoZombie var2 = (IsoZombie)this.CurrentCell.getZombieList().get(var1);
    bool var3 = false;

         for (int var4 = 0; var4 < IsoPlayer.numPlayers; var4++) {
    IsoPlayer var5 = IsoPlayer.players[var4];
            if (var5 != nullptr && var2.current != nullptr) {
    float var6 = var2.getScreenProperX(var4);
    float var7 = var2.getScreenProperY(var4);
               if (!(var6 < -100.0F)
                  && !(var7 < -100.0F)
                  && !(var6 > Core.getInstance().getOffscreenWidth(var4) + 100)
                  && !(var7 > Core.getInstance().getOffscreenHeight(var4) + 100)
                  && (var2.getAlpha(var4) != 0.0F && var2.legsSprite.def.alpha != 0.0F || var2.current.isCouldSee(var4))) {
                  var3 = true;
                  break;
               }
            }
         }

         if (var3 && var2.isCurrentState(FakeDeadZombieState.instance())) {
            var3 = false;
         }

         if (var3) {
            this.zombieWithModel.push_back(var2);
         } else {
            this.zombieWithoutModel.push_back(var2);
         }
      }

      Collections.sort(this.zombieWithModel, compScoreToPlayer);
    int var8 = 0;
    int var9 = 0;
    int var10 = 0;
    short var11 = 510;
      PerformanceSettings.AnimationSkip = 0;

      for (int var12 = 0; var12 < this.zombieWithModel.size(); var12++) {
    IsoZombie var14 = this.zombieWithModel.get(var12);
         if (var10 < var11) {
            if (!var14.Ghost) {
               var9++;
               var10++;
               var14.setSceneCulled(false);
               if (var14.legsSprite != nullptr && var14.legsSprite.modelSlot != nullptr) {
                  if (var9 > PerformanceSettings.ZombieAnimationSpeedFalloffCount) {
                     var8++;
                     var9 = 0;
                  }

                  if (var10 < PerformanceSettings.ZombieBonusFullspeedFalloff) {
                     var14.legsSprite.modelSlot.model.setInstanceSkip(var9 / PerformanceSettings.ZombieBonusFullspeedFalloff);
                     var9 = 0;
                  } else {
                     var14.legsSprite.modelSlot.model.setInstanceSkip(var8 + PerformanceSettings.AnimationSkip);
                  }

                  if (var14.legsSprite.modelSlot.model.AnimPlayer != nullptr) {
                     if (var10 < PerformanceSettings.numberZombiesBlended) {
                        var14.legsSprite.modelSlot.model.AnimPlayer.bDoBlending = !var14.isAlphaAndTargetZero(0)
                           || !var14.isAlphaAndTargetZero(1)
                           || !var14.isAlphaAndTargetZero(2)
                           || !var14.isAlphaAndTargetZero(3);
                     } else {
                        var14.legsSprite.modelSlot.model.AnimPlayer.bDoBlending = false;
                     }
                  }
               }
            }
         } else {
            var14.setSceneCulled(true);
            if (var14.hasAnimationPlayer()) {
               var14.getAnimationPlayer().bDoBlending = false;
            }
         }
      }

      for (int var13 = 0; var13 < this.zombieWithoutModel.size(); var13++) {
    IsoZombie var15 = this.zombieWithoutModel.get(var13);
         if (var15.hasActiveModel()) {
            var15.setSceneCulled(true);
         }

         if (var15.hasAnimationPlayer()) {
            var15.getAnimationPlayer().bDoBlending = false;
         }
      }
   }

    void render() {
      s_performance.isoWorldRender.invokeAndMeasure(this, IsoWorld::renderInternal);
   }

    void renderInternal() {
      if (this.bDrawWorld) {
         if (IsoCamera.CamCharacter != nullptr) {
            SpriteRenderer.instance.doCoreIntParam(0, IsoCamera.CamCharacter.x);
            SpriteRenderer.instance.doCoreIntParam(1, IsoCamera.CamCharacter.y);
            SpriteRenderer.instance.doCoreIntParam(2, IsoCamera.CamCharacter.z);

            try {
               this.sceneCullZombies();
            } catch (Throwable var3) {
               ExceptionLogger.logException(var3);
            }

            try {
               WeatherFxMask.initMask();
               DeadBodyAtlas.instance.render();
               WorldItemAtlas.instance.render();
               this.CurrentCell.render();
               this.DrawIsoCursorHelper();
               DeadBodyAtlas.instance.renderDebug();
               PolygonalMap2.instance.render();
               WorldSoundManager.instance.render();
               WorldFlares.debugRender();
               WorldMarkers.instance.debugRender();
               ObjectAmbientEmitters.getInstance().render();
               ZombieVocalsManager.instance.render();
               LineDrawer.render();
               WeatherFxMask.renderFxMask(IsoCamera.frameState.playerIndex);
               if (GameClient.bClient) {
                  ClientServerMap.render(IsoCamera.frameState.playerIndex);
                  PassengerMap.render(IsoCamera.frameState.playerIndex);
               }

               SkyBox.getInstance().render();
            } catch (Throwable var2) {
               ExceptionLogger.logException(var2);
            }
         }
      }
   }

    void DrawIsoCursorHelper() {
      if (Core.getInstance().getOffscreenBuffer() == nullptr) {
    IsoPlayer var1 = IsoPlayer.getInstance();
         if (var1 != nullptr && !var1.isDead() && var1.isAiming() && var1.PlayerIndex == 0 && var1.JoypadBind == -1) {
            if (!GameTime.isGamePaused()) {
    float var2 = 0.05F;
               switch (Core.getInstance().getIsoCursorVisibility()) {
                  case 0:
                     return;
                  case 1:
                     var2 = 0.05F;
                     break;
                  case 2:
                     var2 = 0.1F;
                     break;
                  case 3:
                     var2 = 0.15F;
                     break;
                  case 4:
                     var2 = 0.3F;
                     break;
                  case 5:
                     var2 = 0.5F;
                     break;
                  case 6:
                     var2 = 0.75F;
               }

               if (Core.getInstance().isFlashIsoCursor()) {
                  if (this.flashIsoCursorInc) {
                     this.flashIsoCursorA += 0.1F;
                     if (this.flashIsoCursorA >= 1.0F) {
                        this.flashIsoCursorInc = false;
                     }
                  } else {
                     this.flashIsoCursorA -= 0.1F;
                     if (this.flashIsoCursorA <= 0.0F) {
                        this.flashIsoCursorInc = true;
                     }
                  }

                  var2 = this.flashIsoCursorA;
               }

    Texture var3 = Texture.getSharedTexture("media/ui/isocursor.png");
    int var4 = (int)(var3.getWidth() * Core.TileScale / 2.0F);
    int var5 = (int)(var3.getHeight() * Core.TileScale / 2.0F);
               SpriteRenderer.instance.setDoAdditive(true);
               SpriteRenderer.instance.renderi(var3, Mouse.getX() - var4 / 2, Mouse.getY() - var5 / 2, var4, var5, var2, var2, var2, var2, nullptr);
               SpriteRenderer.instance.setDoAdditive(false);
            }
         }
      }
   }

    void update() {
      s_performance.isoWorldUpdate.invokeAndMeasure(this, IsoWorld::updateInternal);
   }

    void updateInternal() {
      this.m_frameNo++;

      try {
         if (GameServer.bServer) {
            VehicleManager.instance.serverUpdate();
         }
      } catch (Exception var8) {
         var8.printStackTrace();
      }

      WorldSimulation.instance.update();
      ImprovedFog.update();
      this.helicopter.update();
    long var1 = System.currentTimeMillis();
      if (var1 - this.emitterUpdateMS >= 30L) {
         this.emitterUpdateMS = var1;
         this.emitterUpdate = true;
      } else {
         this.emitterUpdate = false;
      }

      for (int var3 = 0; var3 < this.currentEmitters.size(); var3++) {
    BaseSoundEmitter var4 = this.currentEmitters.get(var3);
         if (this.emitterUpdate || var4.hasSoundsToStart()) {
            var4.tick();
         }

         if (var4.empty()) {
    FMODSoundEmitter var5 = (FMODSoundEmitter)Type.tryCastTo(var4, FMODSoundEmitter.class);
            if (var5 != nullptr) {
               var5.clearParameters();
            }

            this.currentEmitters.remove(var3);
            this.freeEmitters.push(var4);
    IsoObject var6 = this.emitterOwners.remove(var4);
            if (var6 != nullptr && var6.emitter == var4) {
               var6.emitter = nullptr;
            }

            var3--;
         }
      }

      if (!GameClient.bClient && !GameServer.bServer) {
    IsoMetaCell var9 = this.MetaGrid.getCurrentCellData();
         if (var9 != nullptr) {
            var9.checkTriggers();
         }
      }

      WorldSoundManager.instance.initFrame();
      ZombieGroupManager.instance.preupdate();
      OnceEvery.update();
      CollisionManager.instance.initUpdate();

      for (int var10 = 0; var10 < this.CurrentCell.getBuildingList().size(); var10++) {
         ((IsoBuilding)this.CurrentCell.getBuildingList().get(var10)).update();
      }

      ClimateManager.getInstance().update();
      ObjectRenderEffects.updateStatic();
      this.CurrentCell.update();
      IsoRegions.update();
      HaloTextHelper.update();
      CollisionManager.instance.ResolveContacts();

      for (int var11 = 0; var11 < this.AddCoopPlayers.size(); var11++) {
    AddCoopPlayer var12 = this.AddCoopPlayers.get(var11);
         var12.update();
         if (var12.isFinished()) {
            this.AddCoopPlayers.remove(var11--);
         }
      }

      if (!GameServer.bServer) {
         IsoPlayer.UpdateRemovedEmitters();
      }

      try {
         if (PlayerDB.isAvailable()) {
            PlayerDB.getInstance().updateMain();
         }

         if (ClientPlayerDB.isAvailable()) {
            ClientPlayerDB.getInstance().updateMain();
         }

         VehiclesDB2.instance.updateMain();
      } catch (Exception var7) {
         ExceptionLogger.logException(var7);
      }

      if (this.updateSafehousePlayers > 0 && (GameServer.bServer || GameClient.bClient)) {
         this.updateSafehousePlayers--;
         if (this.updateSafehousePlayers == 0) {
            this.updateSafehousePlayers = 200;
            SafeHouse.updateSafehousePlayersConnected();
         }
      }

      m_animationRecorderDiscard = false;
   }

    IsoCell getCell() {
      return this.CurrentCell;
   }

    void PopulateCellWithSurvivors() {
   }

    int getWorldSquareY() {
      return this.CurrentCell.ChunkMap[IsoPlayer.getPlayerIndex()].WorldY * 10;
   }

    int getWorldSquareX() {
      return this.CurrentCell.ChunkMap[IsoPlayer.getPlayerIndex()].WorldX * 10;
   }

    IsoMetaChunk getMetaChunk(int var1, int var2) {
      return this.MetaGrid.getChunkData(var1, var2);
   }

    IsoMetaChunk getMetaChunkFromTile(int var1, int var2) {
      return this.MetaGrid.getChunkDataFromTile(var1, var2);
   }

    float getGlobalTemperature() {
      return ClimateManager.getInstance().getTemperature();
   }

    void setGlobalTemperature(float var1) {
   }

    std::string getWeather() {
      return this.weather;
   }

    void setWeather(const std::string& var1) {
      this.weather = var1;
   }

    int getLuaSpawnCellX() {
      return this.luaSpawnCellX;
   }

    void setLuaSpawnCellX(int var1) {
      this.luaSpawnCellX = var1;
   }

    int getLuaSpawnCellY() {
      return this.luaSpawnCellY;
   }

    void setLuaSpawnCellY(int var1) {
      this.luaSpawnCellY = var1;
   }

    int getLuaPosX() {
      return this.luaPosX;
   }

    void setLuaPosX(int var1) {
      this.luaPosX = var1;
   }

    int getLuaPosY() {
      return this.luaPosY;
   }

    void setLuaPosY(int var1) {
      this.luaPosY = var1;
   }

    int getLuaPosZ() {
      return this.luaPosZ;
   }

    void setLuaPosZ(int var1) {
      this.luaPosZ = var1;
   }

    std::string getWorld() {
      return Core.GameSaveWorld;
   }

    void transmitWeather() {
      if (GameServer.bServer) {
         GameServer.sendWeather();
      }
   }

    bool isValidSquare(int var1, int var2, int var3) {
      return var3 >= 0 && var3 < 8 ? this.MetaGrid.isValidSquare(var1, var2) : false;
   }

   public std::vector<RandomizedZoneStoryBase> getRandomizedZoneList() {
      return this.randomizedZoneList;
   }

   public std::vector<RandomizedBuildingBase> getRandomizedBuildingList() {
      return this.randomizedBuildingList;
   }

   public std::vector<RandomizedVehicleStoryBase> getRandomizedVehicleStoryList() {
      return this.randomizedVehicleStoryList;
   }

    RandomizedVehicleStoryBase getRandomizedVehicleStoryByName(const std::string& var1) {
      for (int var2 = 0; var2 < this.randomizedVehicleStoryList.size(); var2++) {
    RandomizedVehicleStoryBase var3 = this.randomizedVehicleStoryList.get(var2);
         if (var3.getName().equalsIgnoreCase(var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    RandomizedBuildingBase getRBBasic() {
      return this.RBBasic;
   }

    std::string getDifficulty() {
      return Core.getDifficulty();
   }

    void setDifficulty(const std::string& var1) {
      Core.setDifficulty(var1);
   }

    static bool getZombiesDisabled() {
      return NoZombies || !SystemDisabler.doZombieCreation || SandboxOptions.instance.Zombies.getValue() == 6;
   }

    static bool getZombiesEnabled() {
      return !getZombiesDisabled();
   }

    ClimateManager getClimateManager() {
      return ClimateManager.getInstance();
   }

    IsoPuddles getPuddlesManager() {
      return IsoPuddles.getInstance();
   }

    static int getWorldVersion() {
    return 195;
   }

   public std::unordered_map<std::string, std::vector<double>> getSpawnedZombieZone() {
      return this.spawnedZombieZone;
   }

    int getTimeSinceLastSurvivorInHorde() {
      return this.timeSinceLastSurvivorInHorde;
   }

    void setTimeSinceLastSurvivorInHorde(int var1) {
      this.timeSinceLastSurvivorInHorde = var1;
   }

    float getWorldAgeDays() {
    float var1 = (float)GameTime.getInstance().getWorldAgeHours() / 24.0F;
      return var1 + (SandboxOptions.instance.TimeSinceApo.getValue() - 1) * 30;
   }

   public std::unordered_map<std::string, std::vector<std::string>> getAllTiles() {
      return this.allTiles;
   }

   public std::vector<std::string> getAllTilesName() {
    std::vector var1 = new std::vector();
    Iterator var2 = this.allTiles.keySet().iterator();

      while (var2.hasNext()) {
         var1.push_back((std::string)var2.next());
      }

      Collections.sort(var1);
    return var1;
   }

   public std::vector<std::string> getAllTiles(std::string var1) {
      return this.allTiles.get(var1);
   }

    bool isHydroPowerOn() {
      return this.bHydroPowerOn;
   }

    void setHydroPowerOn(bool var1) {
      this.bHydroPowerOn = var1;
   }

   public std::vector<std::string> getTileImageNames() {
      return this.tileImages;
   }
}
} // namespace iso
} // namespace zombie
