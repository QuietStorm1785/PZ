#pragma once
#include <mutex>
#include "fmod/fmod/FMODSoundEmitter.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/CollisionManager.h"
#include "zombie/DebugFileWatcher.h"
#include "zombie/FliesSound.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
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
#include "zombie/characters/traits/TraitFactory.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/Rand.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/TilePropertyAliasMap.h"
#include "zombie/core/Translator.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/physics/WorldSimulation.h"
#include "zombie/core/profiling/PerformanceProfileProbe.h"
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
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoFireManager.h"
#include "zombie/iso/objects/ObjectRenderEffects.h"
#include "zombie/iso/objects/RainManager.h"
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
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IsoWorld {
public:
 std::string weather = "sunny";
 const IsoMetaGrid MetaGrid = new IsoMetaGrid();
private
 ArrayList<RandomizedBuildingBase> randomizedBuildingList =
 std::make_unique<ArrayList<>>();
private
 ArrayList<RandomizedZoneStoryBase> randomizedZoneList =
 std::make_unique<ArrayList<>>();
private
 ArrayList<RandomizedVehicleStoryBase> randomizedVehicleStoryList =
 std::make_unique<ArrayList<>>();
 const RandomizedBuildingBase RBBasic = new RBBasic();
private
 HashMap<String, ArrayList<Double>> spawnedZombieZone =
 std::make_unique<HashMap<>>();
private
 HashMap<String, ArrayList<String>> allTiles =
 std::make_unique<HashMap<>>();
private
 ArrayList<String> tileImages = std::make_unique<ArrayList<>>();
 float flashIsoCursorA = 1.0F;
 bool flashIsoCursorInc = false;
 SkyBox sky = nullptr;
 static PredicatedFileWatcher m_setAnimationRecordingTriggerWatcher;
 static bool m_animationRecorderActive = false;
 static bool m_animationRecorderDiscard = false;
 int timeSinceLastSurvivorInHorde = 4000;
 int m_frameNo = 0;
 const Helicopter helicopter = new Helicopter();
 bool bHydroPowerOn = false;
public
 ArrayList<IsoGameCharacter> Characters =
 std::make_unique<ArrayList<>>();
private
 ArrayDeque<BaseSoundEmitter> freeEmitters =
 std::make_unique<ArrayDeque<>>();
private
 ArrayList<BaseSoundEmitter> currentEmitters =
 std::make_unique<ArrayList<>>();
private
 HashMap<BaseSoundEmitter, IsoObject> emitterOwners =
 std::make_unique<HashMap<>>();
 int x = 50;
 int y = 50;
 IsoCell CurrentCell;
 static IsoWorld instance = new IsoWorld();
 int TotalSurvivorsDead = 0;
 int TotalSurvivorNights = 0;
 int SurvivorSurvivalRecord = 0;
public
 HashMap<Integer, SurvivorDesc> SurvivorDescriptors =
 std::make_unique<HashMap<>>();
public
 ArrayList<AddCoopPlayer> AddCoopPlayers = std::make_unique<ArrayList<>>();
private
 static IsoWorld.CompScoreToPlayer compScoreToPlayer =
 new IsoWorld.CompScoreToPlayer();
 static IsoWorld.CompDistToPlayer compDistToPlayer =
 new IsoWorld.CompDistToPlayer();
 static std::string mapPath = "media/";
 static bool mapUseJar = true;
 bool bLoaded = false;
public
 static HashMap<String, ArrayList<String>> PropertyValueMap =
 std::make_unique<HashMap<>>();
 static int WorldX = 0;
 static int WorldY = 0;
 SurvivorDesc luaDesc;
private
 ArrayList<String> luatraits;
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
private
 ArrayList<IsoZombie> zombieWithModel = std::make_unique<ArrayList<>>();
private
 ArrayList<IsoZombie> zombieWithoutModel =
 std::make_unique<ArrayList<>>();
 static bool NoZombies = false;
 static int TotalWorldVersion = -1;
 static int saveoffsetx;
 static int saveoffsety;
 bool bDoChunkMapUpdate = true;
 long emitterUpdateMS;
 bool emitterUpdate;
 int updateSafehousePlayers = 200;

 IsoMetaGrid getMetaGrid() { return this->MetaGrid; }

public
 IsoMetaGrid.Zone registerZone(String name, String type, int _x, int _y, int z,
 int width, int height) {
 return this->MetaGrid.registerZone(name, type, _x, _y, z, width, height);
 }

public
 IsoMetaGrid.Zone registerZoneNoOverlap(String name, String type, int _x,
 int _y, int z, int width, int height) {
 return this->MetaGrid.registerZoneNoOverlap(name, type, _x, _y, z, width,
 height);
 }

 void removeZonesForLotDirectory(std::string_view lotDir) {
 this->MetaGrid.removeZonesForLotDirectory(lotDir);
 }

 BaseSoundEmitter getFreeEmitter() {
 void *object = nullptr;
 if (this->freeEmitters.empty()) {
 object = Core.SoundDisabled ? std::make_unique<DummySoundEmitter>()
 : std::make_unique<FMODSoundEmitter>();
 } else {
 object = this->freeEmitters.pop();
 }

 this->currentEmitters.add((BaseSoundEmitter)object);
 return (BaseSoundEmitter)object;
 }

 BaseSoundEmitter getFreeEmitter(float _x, float _y, float z) {
 BaseSoundEmitter baseSoundEmitter = this->getFreeEmitter();
 baseSoundEmitter.setPos(_x, _y, z);
 return baseSoundEmitter;
 }

 void takeOwnershipOfEmitter(BaseSoundEmitter emitter) {
 this->currentEmitters.remove(emitter);
 }

 void setEmitterOwner(BaseSoundEmitter emitter, IsoObject object) {
 if (emitter != nullptr && object != nullptr) {
 if (!this->emitterOwners.containsKey(emitter) {
 this->emitterOwners.put(emitter, object);
 }
 }
 }

 void returnOwnershipOfEmitter(BaseSoundEmitter emitter) {
 if (emitter != nullptr) {
 if (!this->currentEmitters.contains(emitter) &&
 !this->freeEmitters.contains(emitter) {
 if (emitter.empty()) {
 FMODSoundEmitter fMODSoundEmitter =
 Type.tryCastTo(emitter, FMODSoundEmitter.class);
 if (fMODSoundEmitter != nullptr) {
 fMODSoundEmitter.clearParameters();
 }

 this->freeEmitters.add(emitter);
 } else {
 this->currentEmitters.add(emitter);
 }
 }
 }
 }

public
 IsoMetaGrid.Zone registerVehiclesZone(String name, String type, int _x,
 int _y, int z, int width, int height,
 KahluaTable properties) {
 return this->MetaGrid.registerVehiclesZone(name, type, _x, _y, z, width,
 height, properties);
 }

public
 IsoMetaGrid.Zone registerMannequinZone(String name, String type, int _x,
 int _y, int z, int width, int height,
 KahluaTable properties) {
 return this->MetaGrid.registerMannequinZone(name, type, _x, _y, z, width,
 height, properties);
 }

 void registerRoomTone(std::string_view name, std::string_view type,
 int _x, int _y, int z, int width, int height,
 KahluaTable properties) {
 this->MetaGrid.registerRoomTone(name, type, _x, _y, z, width, height,
 properties);
 }

 void registerSpawnOrigin(int _x, int _y, int width, int height,
 KahluaTable properties) {
 ZombiePopulationManager.instance.registerSpawnOrigin(_x, _y, width, height,
 properties);
 }

 void registerWaterFlow(float _x, float _y, float flow, float speed) {
 IsoWaterFlow.addFlow(_x, _y, flow, speed);
 }

 void registerWaterZone(float x1, float y1, float x2, float y2, float shore,
 float water_ground) {
 IsoWaterFlow.addZone(x1, y1, x2, y2, shore, water_ground);
 }

 void checkVehiclesZones() { this->MetaGrid.checkVehiclesZones(); }

 void setGameMode(std::string_view mode) {
 Core.GameMode = mode;
 Core.bLastStand = "LastStand" == mode);
 Core.getInstance().setChallenge(false);
 Core.ChallengeID = nullptr;
 }

 std::string getGameMode() { return Core.GameMode; }

 void setWorld(std::string_view world) { Core.GameSaveWorld = world.trim(); }

 void setMap(std::string_view world) { Core.GameMap = world; }

 std::string getMap() { return Core.GameMap; }

 void renderTerrain() {}

 int getFrameNo() { return this->m_frameNo; }

 IsoObject getItemFromXYZIndexBuffer(ByteBuffer bb) {
 int int0 = bb.getInt();
 int int1 = bb.getInt();
 int int2 = bb.getInt();
 IsoGridSquare square = this->CurrentCell.getGridSquare(int0, int1, int2);
 if (square.empty()) {
 return nullptr;
 } else {
 uint8_t byte0 = bb.get();
 return byte0 >= 0 && byte0 < square.getObjects().size()
 ? square.getObjects().get(byte0)
 : nullptr;
 }
 }

public
 IsoWorld() {
 if (!GameServer.bServer) {
 }
 }

 static void initMessaging() {
 if (m_setAnimationRecordingTriggerWatcher.empty()) {
 m_setAnimationRecordingTriggerWatcher = new PredicatedFileWatcher(
 ZomboidFileSystem.instance.getMessagingDirSub(
 "Trigger_AnimationRecorder.xml"),
 TriggerSetAnimationRecorderFile.class,
 IsoWorld::onTrigger_setAnimationRecorderTriggerFile);
 DebugFileWatcher.instance.add(m_setAnimationRecordingTriggerWatcher);
 }
 }

 static void onTrigger_setAnimationRecorderTriggerFile(
 TriggerSetAnimationRecorderFile triggerSetAnimationRecorderFile) {
 m_animationRecorderActive = triggerSetAnimationRecorderFile.isRecording;
 m_animationRecorderDiscard = triggerSetAnimationRecorderFile.discard;
 }

 static bool isAnimRecorderActive() { return m_animationRecorderActive; }

 static bool isAnimRecorderDiscardTriggered() {
 return m_animationRecorderDiscard;
 }

 IsoSurvivor CreateRandomSurvivor(SurvivorDesc desc, IsoGridSquare sq,
 IsoPlayer player) {
 return nullptr;
 }

 void CreateSwarm(int num, int x1, int y1, int x2, int y2) {}

 void ForceKillAllZombies() {
 GameTime.getInstance().RemoveZombiesIndiscriminate(1000);
 }

 static int readInt(RandomAccessFile __in__) {
 int int0 = __in__.read();
 int int1 = __in__.read();
 int int2 = __in__.read();
 int int3 = __in__.read();
 if ((int0 | int1 | int2 | int3) < 0) {
 throw std::make_unique<EOFException>();
 } else {
 return (int0 << 0) + (int1 << 8) + (int2 << 16) + (int3 << 24);
 }
 }

 static std::string readString(RandomAccessFile __in__) {
 return __in__.readLine();
 }

 static int readInt(InputStream __in__) {
 int int0 = __in__.read();
 int int1 = __in__.read();
 int int2 = __in__.read();
 int int3 = __in__.read();
 if ((int0 | int1 | int2 | int3) < 0) {
 throw std::make_unique<EOFException>();
 } else {
 return (int0 << 0) + (int1 << 8) + (int2 << 16) + (int3 << 24);
 }
 }

 static std::string readString(InputStream __in__) {
 StringBuilder stringBuilder = new StringBuilder();
 int int0 = -1;
 bool boolean0 = false;

 while (!boolean0) {
 switch (int0 = __in__.read()) {
 case -1:
 case 10:
 boolean0 = true;
 break;
 case 13:
 throw IllegalStateException("\r\n unsupported");
 default:
 stringBuilder.append((char)int0);
 }
 }

 return int0 = = -1 && stringBuilder.length() == 0
 ? nullptr
 : stringBuilder.toString();
 }

 void LoadTileDefinitions(IsoSpriteManager sprMan, std::string_view filename,
 int fileNumber) {
 DebugLog.log("tiledef: loading " + filename);
 bool boolean0 = filename.endsWith(".patch.tiles");

 try(FileInputStream fileInputStream = new FileInputStream(filename);
 BufferedInputStream bufferedInputStream =
 new BufferedInputStream(fileInputStream);) {
 int int0 = readInt(bufferedInputStream);
 int int1 = readInt(bufferedInputStream);
 int int2 = readInt(bufferedInputStream);
 SharedStrings sharedStrings = new SharedStrings();
 bool boolean1 = false;
 bool boolean2 = false;
 bool boolean3 = Core.bDebug && Translator.getLanguage() ==
 Translator.getDefaultLanguage();
 std::vector arrayList0 = new ArrayList();
 std::unordered_map hashMap0 = new HashMap();
 std::unordered_map hashMap1 = new HashMap();
 String[] strings0 = new String[]{"N", "E", "S", "W"};

 for (int int3 = 0; int3 < strings0.length; int3++) {
 hashMap1.put(strings0[int3], std::make_unique<ArrayList>());
 }

 std::vector arrayList1 = new ArrayList();
 std::unordered_map hashMap2 = new HashMap();
 int int4 = 0;
 int int5 = 0;
 int int6 = 0;
 int int7 = 0;
 std::unordered_set hashSet = new HashSet();

 for (int int8 = 0; int8 < int2; int8++) {
 std::string string0 = readString(bufferedInputStream);
 std::string string1 = string0.trim();
 std::string string2 = readString(bufferedInputStream);
 int int9 = readInt(bufferedInputStream);
 int int10 = readInt(bufferedInputStream);
 int int11 = readInt(bufferedInputStream);
 int int12 = readInt(bufferedInputStream);

 for (int int13 = 0; int13 < int12; int13++) {
 IsoSprite sprite0;
 if (boolean0) {
 sprite0 = sprMan.NamedMap.get(string1 + "_" + int13);
 if (sprite0.empty()) {
 continue;
 }
 } else if (fileNumber < 2) {
 sprite0 = sprMan.AddSprite(string1 + "_" + int13,
 fileNumber * 100 * 1000 + 10000 +
 int11 * 1000 + int13);
 } else {
 sprite0 =
 sprMan.AddSprite(string1 + "_" + int13,
 fileNumber * 512 * 512 + int11 * 512 + int13);
 }

 if (Core.bDebug) {
 if (this->allTiles.containsKey(string1) {
 if (!boolean0) {
 this->allTiles.get(string1).add(string1 + "_" + int13);
 }
 } else {
 std::vector arrayList2 = new ArrayList();
 arrayList2.add(string1 + "_" + int13);
 this->allTiles.put(string1, arrayList2);
 }
 }

 arrayList0.add(sprite0);
 if (!boolean0) {
 sprite0.setName(string1 + "_" + int13);
 sprite0.tileSheetIndex = int13;
 }

 if (sprite0.name.contains("damaged") ||
 sprite0.name.contains("trash_")) {
 sprite0.attachedFloor = true;
 sprite0.getProperties().Set("attachedFloor", "true");
 }

 if (sprite0.name.startsWith("f_bushes") && int13 <= 31) {
 sprite0.isBush = true;
 sprite0.attachedFloor = true;
 }

 int int14 = readInt(bufferedInputStream);

 for (int int15 = 0; int15 < int14; int15++) {
 string0 = readString(bufferedInputStream);
 std::string string3 = string0.trim();
 string0 = readString(bufferedInputStream);
 std::string string4 = string0.trim();
 IsoObjectType objectType = IsoObjectType.FromString(string3);
 if (objectType != IsoObjectType.MAX) {
 if (sprite0.getType() != IsoObjectType.doorW &&
 sprite0.getType() != IsoObjectType.doorN ||
 objectType != IsoObjectType.wall) {
 sprite0.setType(objectType);
 }

 if (objectType == IsoObjectType.doorW) {
 sprite0.getProperties().Set(IsoFlagType.doorW);
 } else if (objectType == IsoObjectType.doorN) {
 sprite0.getProperties().Set(IsoFlagType.doorN);
 }
 } else {
 string3 = sharedStrings.get(string3);
 if (string3 == "firerequirement")) {
 sprite0.firerequirement = Integer.parseInt(string4);
 }
 else if (string3 == "fireRequirement")) {
 sprite0.firerequirement = Integer.parseInt(string4);
 }
 else if (string3 == "BurntTile")) {
 sprite0.burntTile = string4;
 }
 else if (string3 == "ForceAmbient")) {
 sprite0.forceAmbient = true;
 sprite0.getProperties().Set(string3, string4);
 }
 else if (string3 == "solidfloor")) {
 sprite0.solidfloor = true;
 sprite0.getProperties().Set(string3, string4);
 }
 else if (string3 == "canBeRemoved")) {
 sprite0.canBeRemoved = true;
 sprite0.getProperties().Set(string3, string4);
 }
 else if (string3 == "attachedFloor")) {
 sprite0.attachedFloor = true;
 sprite0.getProperties().Set(string3, string4);
 }
 else if (string3 == "cutW")) {
 sprite0.cutW = true;
 sprite0.getProperties().Set(string3, string4);
 }
 else if (string3 == "cutN")) {
 sprite0.cutN = true;
 sprite0.getProperties().Set(string3, string4);
 }
 else if (string3 == "solid")) {
 sprite0.solid = true;
 sprite0.getProperties().Set(string3, string4);
 }
 else if (string3 == "solidTrans")) {
 sprite0.solidTrans = true;
 sprite0.getProperties().Set(string3, string4);
 }
 else if (string3 == "invisible")) {
 sprite0.invisible = true;
 sprite0.getProperties().Set(string3, string4);
 }
 else if (string3 == "alwaysDraw")) {
 sprite0.alwaysDraw = true;
 sprite0.getProperties().Set(string3, string4);
 }
 else if (string3 == "forceRender")) {
 sprite0.forceRender = true;
 sprite0.getProperties().Set(string3, string4);
 }
 else if ("FloorHeight" == string3) {
 if ("OneThird" == string4) {
 sprite0.getProperties().Set(
 IsoFlagType.FloorHeightOneThird);
 }
 else if ("TwoThirds" == string4) {
 sprite0.getProperties().Set(
 IsoFlagType.FloorHeightTwoThirds);
 }
 }
 else if (string3 == "MoveWithWind")) {
 sprite0.moveWithWind = true;
 sprite0.getProperties().Set(string3, string4);
 }
 else if (string3 == "WindType")) {
 sprite0.windType = Integer.parseInt(string4);
 sprite0.getProperties().Set(string3, string4);
 }
 else if (string3 == "RenderLayer")) {
 sprite0.getProperties().Set(string3, string4);
 if ("Default" == string4) {
 sprite0.renderLayer = 0;
 }
 else if ("Floor" == string4) {
 sprite0.renderLayer = 1;
 }
 }
 else if (string3 == "TreatAsWallOrder")) {
 sprite0.treatAsWallOrder = true;
 sprite0.getProperties().Set(string3, string4);
 }
 else {
 sprite0.getProperties().Set(string3, string4);
 if ("WindowN" == string3) || "WindowW" == string3) {
 sprite0.getProperties().Set(string3, string4, false);
 }
 }
 }

 if (objectType == IsoObjectType.tree) {
 if (sprite0.name == "e_riverbirch_1_1")) {
 string4 = "1";
 }

 sprite0.getProperties().Set("tree", string4);
 sprite0.getProperties().UnSet(IsoFlagType.solid);
 sprite0.getProperties().Set(IsoFlagType.blocksight);
 int int16 = Integer.parseInt(string4);
 if (string1.startsWith("vegetation_trees")) {
 int16 = 4;
 }

 if (int16 < 1) {
 int16 = 1;
 }

 if (int16 > 4) {
 int16 = 4;
 }

 if (int16 == 1 || int16 == 2) {
 sprite0.getProperties().UnSet(IsoFlagType.blocksight);
 }
 }

 if (string3 == "interior") && string4 == "false")) {
 sprite0.getProperties().Set(IsoFlagType.exterior);
 }

 if (string3 == "HoppableN")) {
 sprite0.getProperties().Set(IsoFlagType.collideN);
 sprite0.getProperties().Set(IsoFlagType.canPathN);
 sprite0.getProperties().Set(IsoFlagType.transparentN);
 }

 if (string3 == "HoppableW")) {
 sprite0.getProperties().Set(IsoFlagType.collideW);
 sprite0.getProperties().Set(IsoFlagType.canPathW);
 sprite0.getProperties().Set(IsoFlagType.transparentW);
 }

 if (string3 == "WallN")) {
 sprite0.getProperties().Set(IsoFlagType.collideN);
 sprite0.getProperties().Set(IsoFlagType.cutN);
 sprite0.setType(IsoObjectType.wall);
 sprite0.cutN = true;
 sprite0.getProperties().Set("WallN", "", false);
 }

 if (string3 == "CantClimb")) {
 sprite0.getProperties().Set(IsoFlagType.CantClimb);
 }
 else if (string3 == "container")) {
 sprite0.getProperties().Set(string3, string4, false);
 }
 else if (string3 == "WallNTrans")) {
 sprite0.getProperties().Set(IsoFlagType.collideN);
 sprite0.getProperties().Set(IsoFlagType.cutN);
 sprite0.getProperties().Set(IsoFlagType.transparentN);
 sprite0.setType(IsoObjectType.wall);
 sprite0.cutN = true;
 sprite0.getProperties().Set("WallNTrans", "", false);
 }
 else if (string3 == "WallW")) {
 sprite0.getProperties().Set(IsoFlagType.collideW);
 sprite0.getProperties().Set(IsoFlagType.cutW);
 sprite0.setType(IsoObjectType.wall);
 sprite0.cutW = true;
 sprite0.getProperties().Set("WallW", "", false);
 }
 else if (string3 == "windowN")) {
 sprite0.getProperties().Set("WindowN", "WindowN");
 sprite0.getProperties().Set(IsoFlagType.transparentN);
 sprite0.getProperties().Set("WindowN", "WindowN", false);
 }
 else if (string3 == "windowW")) {
 sprite0.getProperties().Set("WindowW", "WindowW");
 sprite0.getProperties().Set(IsoFlagType.transparentW);
 sprite0.getProperties().Set("WindowW", "WindowW", false);
 }
 else if (string3 == "cutW")) {
 sprite0.getProperties().Set(IsoFlagType.cutW);
 sprite0.cutW = true;
 }
 else if (string3 == "cutN")) {
 sprite0.getProperties().Set(IsoFlagType.cutN);
 sprite0.cutN = true;
 }
 else if (string3 == "WallWTrans")) {
 sprite0.getProperties().Set(IsoFlagType.collideW);
 sprite0.getProperties().Set(IsoFlagType.transparentW);
 sprite0.getProperties().Set(IsoFlagType.cutW);
 sprite0.setType(IsoObjectType.wall);
 sprite0.cutW = true;
 sprite0.getProperties().Set("WallWTrans", "", false);
 }
 else if (string3 == "DoorWallN")) {
 sprite0.getProperties().Set(IsoFlagType.cutN);
 sprite0.cutN = true;
 sprite0.getProperties().Set("DoorWallN", "", false);
 }
 else if (string3 == "DoorWallNTrans")) {
 sprite0.getProperties().Set(IsoFlagType.cutN);
 sprite0.getProperties().Set(IsoFlagType.transparentN);
 sprite0.cutN = true;
 sprite0.getProperties().Set("DoorWallNTrans", "", false);
 }
 else if (string3 == "DoorWallW")) {
 sprite0.getProperties().Set(IsoFlagType.cutW);
 sprite0.cutW = true;
 sprite0.getProperties().Set("DoorWallW", "", false);
 }
 else if (string3 == "DoorWallWTrans")) {
 sprite0.getProperties().Set(IsoFlagType.cutW);
 sprite0.getProperties().Set(IsoFlagType.transparentW);
 sprite0.cutW = true;
 sprite0.getProperties().Set("DoorWallWTrans", "", false);
 }
 else if (string3 == "WallNW")) {
 sprite0.getProperties().Set(IsoFlagType.collideN);
 sprite0.getProperties().Set(IsoFlagType.cutN);
 sprite0.getProperties().Set(IsoFlagType.collideW);
 sprite0.getProperties().Set(IsoFlagType.cutW);
 sprite0.setType(IsoObjectType.wall);
 sprite0.cutW = true;
 sprite0.cutN = true;
 sprite0.getProperties().Set("WallNW", "", false);
 }
 else if (string3 == "WallNWTrans")) {
 sprite0.getProperties().Set(IsoFlagType.collideN);
 sprite0.getProperties().Set(IsoFlagType.cutN);
 sprite0.getProperties().Set(IsoFlagType.collideW);
 sprite0.getProperties().Set(IsoFlagType.transparentN);
 sprite0.getProperties().Set(IsoFlagType.transparentW);
 sprite0.getProperties().Set(IsoFlagType.cutW);
 sprite0.setType(IsoObjectType.wall);
 sprite0.cutW = true;
 sprite0.cutN = true;
 sprite0.getProperties().Set("WallNWTrans", "", false);
 }
 else if (string3 == "WallSE")) {
 sprite0.getProperties().Set(IsoFlagType.cutW);
 sprite0.getProperties().Set(IsoFlagType.WallSE);
 sprite0.getProperties().Set("WallSE", "WallSE");
 sprite0.cutW = true;
 }
 else if (string3 == "WindowW")) {
 sprite0.getProperties().Set(IsoFlagType.canPathW);
 sprite0.getProperties().Set(IsoFlagType.collideW);
 sprite0.getProperties().Set(IsoFlagType.cutW);
 sprite0.getProperties().Set(IsoFlagType.transparentW);
 sprite0.setType(IsoObjectType.windowFW);
 if (sprite0.getProperties().Is(IsoFlagType.HoppableW) {
 if (Core.bDebug) {
 DebugLog.log(
 "ERROR: WindowW sprite shouldn't have HoppableW (" +
 sprite0.getName() + ")");
 }

 sprite0.getProperties().UnSet(IsoFlagType.HoppableW);
 }

 sprite0.cutW = true;
 }
 else if (string3 == "WindowN")) {
 sprite0.getProperties().Set(IsoFlagType.canPathN);
 sprite0.getProperties().Set(IsoFlagType.collideN);
 sprite0.getProperties().Set(IsoFlagType.cutN);
 sprite0.getProperties().Set(IsoFlagType.transparentN);
 sprite0.setType(IsoObjectType.windowFN);
 if (sprite0.getProperties().Is(IsoFlagType.HoppableN) {
 if (Core.bDebug) {
 DebugLog.log(
 "ERROR: WindowN sprite shouldn't have HoppableN (" +
 sprite0.getName() + ")");
 }

 sprite0.getProperties().UnSet(IsoFlagType.HoppableN);
 }

 sprite0.cutN = true;
 }
 else if (string3 == "UnbreakableWindowW")) {
 sprite0.getProperties().Set(IsoFlagType.canPathW);
 sprite0.getProperties().Set(IsoFlagType.collideW);
 sprite0.getProperties().Set(IsoFlagType.cutW);
 sprite0.getProperties().Set(IsoFlagType.transparentW);
 sprite0.getProperties().Set(IsoFlagType.collideW);
 sprite0.setType(IsoObjectType.wall);
 sprite0.cutW = true;
 }
 else if (string3 == "UnbreakableWindowN")) {
 sprite0.getProperties().Set(IsoFlagType.canPathN);
 sprite0.getProperties().Set(IsoFlagType.collideN);
 sprite0.getProperties().Set(IsoFlagType.cutN);
 sprite0.getProperties().Set(IsoFlagType.transparentN);
 sprite0.getProperties().Set(IsoFlagType.collideN);
 sprite0.setType(IsoObjectType.wall);
 sprite0.cutN = true;
 }
 else if (string3 == "UnbreakableWindowNW")) {
 sprite0.getProperties().Set(IsoFlagType.cutN);
 sprite0.getProperties().Set(IsoFlagType.transparentN);
 sprite0.getProperties().Set(IsoFlagType.collideN);
 sprite0.getProperties().Set(IsoFlagType.cutN);
 sprite0.getProperties().Set(IsoFlagType.collideW);
 sprite0.getProperties().Set(IsoFlagType.cutW);
 sprite0.setType(IsoObjectType.wall);
 sprite0.cutW = true;
 sprite0.cutN = true;
 }
 else if ("NoWallLighting" == string3) {
 sprite0.getProperties().Set(IsoFlagType.NoWallLighting);
 }
 else if ("ForceAmbient" == string3) {
 sprite0.getProperties().Set(IsoFlagType.ForceAmbient);
 }

 if (string3 == "name")) {
 sprite0.setParentObjectName(string4);
 }
 }

 if (sprite0.getProperties().Is("lightR") ||
 sprite0.getProperties().Is("lightG") ||
 sprite0.getProperties().Is("lightB")) {
 if (!sprite0.getProperties().Is("lightR")) {
 sprite0.getProperties().Set("lightR", "0");
 }

 if (!sprite0.getProperties().Is("lightG")) {
 sprite0.getProperties().Set("lightG", "0");
 }

 if (!sprite0.getProperties().Is("lightB")) {
 sprite0.getProperties().Set("lightB", "0");
 }
 }

 sprite0.getProperties().CreateKeySet();
 if (Core.bDebug && sprite0.getProperties().Is("SmashedTileOffset") &&
 !sprite0.getProperties().Is("GlassRemovedOffset")) {
 DebugLog.General.error("Window sprite has SmashedTileOffset but no "
 "GlassRemovedOffset (" +
 sprite0.getName() + ")");
 }
 }

 this->setOpenDoorProperties(string1, arrayList0);
 hashMap0.clear();

 for (auto &sprite1 : arrayList0)
 if (sprite1.getProperties().Is("StopCar")) {
 sprite1.setType(IsoObjectType.isMoveAbleObject);
 }

 if (sprite1.getProperties().Is("IsMoveAble")) {
 if (sprite1.getProperties().Is("CustomName") &&
 !sprite1.getProperties().Val("CustomName") == "")) {
 int4++;
 if (sprite1.getProperties().Is("GroupName")) {
 std::string string5 = sprite1.getProperties().Val("GroupName") +
 " " +
 sprite1.getProperties().Val("CustomName");
 if (!hashMap0.containsKey(string5) {
 hashMap0.put(string5, std::make_unique<ArrayList>());
 }

 ((ArrayList)hashMap0.get(string5).add(sprite1);
 hashSet.add(string5);
 } else {
 if (!hashMap2.containsKey(string1) {
 hashMap2.put(string1, std::make_unique<ArrayList>());
 }

 if (!((ArrayList)hashMap2.get(string1)
 .contains(sprite1.getProperties().Val("CustomName"))) {
 ((ArrayList)hashMap2.get(string1)
 .add(sprite1.getProperties().Val("CustomName"));
 }

 int5++;
 hashSet.add(sprite1.getProperties().Val("CustomName"));
 }
 }
 else {
 DebugLog.log("[IMPORTANT] MOVABLES: Object has no custom name "
 "defined: sheet = " +
 string1);
 }
 }
 }

 for (Entry entry : hashMap0.entrySet()) {
 std::string string6 = (String)entry.getKey();
 if (!hashMap2.containsKey(string1) {
 hashMap2.put(string1, std::make_unique<ArrayList>());
 }

 if (!((ArrayList)hashMap2.get(string1).contains(string6) {
 ((ArrayList)hashMap2.get(string1).add(string6);
 }

 std::vector arrayList3 = (ArrayList)entry.getValue();
 if (arrayList3.size() == 1) {
 DebugLog.log(
 "MOVABLES: Object has only one face defined for group: (" +
 string6 + ") sheet = " + string1);
 }

 if (arrayList3.size() == 3) {
 DebugLog.log("MOVABLES: Object only has 3 sprites, _might_ have a "
 "error in settings, group: (" +
 string6 + ") sheet = " + string1);
 }

 for (auto &string7 : strings0)
 ((ArrayList)hashMap1.get(string7).clear();
 }

 boolean boolean4 = ((IsoSprite)arrayList3.get(0).getProperties().Is("SpriteGridPos")
 && !((IsoSprite)arrayList3.get(0).getProperties().Val("SpriteGridPos") == "None");
 bool boolean5 = true;

 for (auto &sprite2 : arrayList3)
 bool boolean6 =
 sprite2.getProperties().Is("SpriteGridPos") &&
 !sprite2.getProperties()
 .Val("SpriteGridPos")
 .equals("None");
 if (boolean4 != boolean6) {
 boolean5 = false;
 DebugLog.log("MOVABLES: Difference in SpriteGrid "
 "settings for members of group: (" +
 string6 + ") sheet = " + string1);
 break;
 }

 if (!sprite2.getProperties().Is("Facing")) {
 boolean5 = false;
 } else {
 std::string string8 =
 sprite2.getProperties().Val("Facing");
 switch (string8) {
 case "N":
 ((ArrayList)hashMap1.get("N")).add(sprite2);
 break;
 case "E":
 ((ArrayList)hashMap1.get("E")).add(sprite2);
 break;
 case "S":
 ((ArrayList)hashMap1.get("S")).add(sprite2);
 break;
 case "W":
 ((ArrayList)hashMap1.get("W")).add(sprite2);
 break;
 default:
 DebugLog.log("MOVABLES: Invalid face (" +
 sprite2.getProperties().Val("Facing") +
 ") for group: (" + string6 +
 ") sheet = " + string1);
 boolean5 = false;
 }
 }

 if (!boolean5) {
 DebugLog.log("MOVABLES: Not all members have a valid "
 "face defined for group: (" +
 string6 + ") sheet = " + string1);
 break;
 }
 }

 if (boolean5) {
 if (boolean4) {
 int int17 = 0;
 IsoSpriteGrid[] spriteGrids = new IsoSpriteGrid[strings0.length];

 label676:
 for (int int18 = 0; int18 < strings0.length; int18++) {
 std::vector arrayList4 = (ArrayList)hashMap1.get(strings0[int18]);
 if (arrayList4.size() > 0) {
 if (int17 == 0) {
 int17 = arrayList4.size();
 }

 if (int17 != arrayList4.size()) {
 DebugLog.log("MOVABLES: Sprite count mismatch for multi sprite "
 "movable, group: (" +
 string6 + ") sheet = " + string1);
 boolean5 = false;
 break;
 }

 arrayList1.clear();
 int int19 = -1;
 int int20 = -1;
 Iterator iterator = arrayList4.iterator();

 while (true) {
 if (iterator.hasNext()) {
 IsoSprite sprite3 = (IsoSprite)iterator.next();
 std::string string9 =
 sprite3.getProperties().Val("SpriteGridPos");
 if (!arrayList1.contains(string9) {
 arrayList1.add(string9);
 String[] strings1 = string9.split(",");
 if (strings1.length == 2) {
 int int21 = Integer.parseInt(strings1[0]);
 int int22 = Integer.parseInt(strings1[1]);
 if (int21 > int19) {
 int19 = int21;
 }

 if (int22 > int20) {
 int20 = int22;
 }
 continue;
 }

 DebugLog.log("MOVABLES: SpriteGrid position error for multi "
 "sprite movable, group: (" +
 string6 + ") sheet = " + string1);
 boolean5 = false;
 } else {
 DebugLog.log("MOVABLES: double SpriteGrid position (" +
 string9 +
 ") for multi sprite movable, group: (" +
 string6 + ") sheet = " + string1);
 boolean5 = false;
 }
 }

 if (int19 == -1 || int20 == -1 ||
 (int19 + 1) * (int20 + 1) != arrayList4.size()) {
 DebugLog.log("MOVABLES: SpriteGrid dimensions error for multi "
 "sprite movable, group: (" +
 string6 + ") sheet = " + string1);
 boolean5 = false;
 break label676;
 }

 if (!boolean5) {
 break label676;
 }

 spriteGrids[int18] = new IsoSpriteGrid(int19 + 1, int20 + 1);

 for (auto &sprite4 : arrayList4)
 std::string string10 =
 sprite4.getProperties().Val("SpriteGridPos");
 String[] strings2 = string10.split(",");
 int int23 = Integer.parseInt(strings2[0]);
 int int24 = Integer.parseInt(strings2[1]);
 spriteGrids[int18].setSprite(int23, int24, sprite4);
 }

 if (!spriteGrids[int18].validate()) {
 DebugLog.log("MOVABLES: SpriteGrid didn't validate for multi "
 "sprite movable, group: (" +
 string6 + ") sheet = " + string1);
 boolean5 = false;
 break label676;
 }
 break;
 }
 }
 }

 if (boolean5 && int17 != 0) {
 int7++;

 for (int int25 = 0; int25 < strings0.length; int25++) {
 IsoSpriteGrid spriteGrid = spriteGrids[int25];
 if (spriteGrid != nullptr) {
 for (IsoSprite sprite5 : spriteGrid.getSprites()) {
 sprite5.setSpriteGrid(spriteGrid);

 for (int int26 = 0; int26 < strings0.length; int26++) {
 if (int26 != int25 && spriteGrids[int26] != nullptr) {
 sprite5.getProperties().Set(
 strings0[int26] + "offset",
 Integer.toString(
 arrayList0.indexOf(
 spriteGrids[int26].getAnchorSprite()) -
 arrayList0.indexOf(sprite5));
 }
 }
 }
 }
 }
 } else {
 DebugLog.log("MOVABLES: Error in multi sprite movable, group: (" +
 string6 + ") sheet = " + string1);
 }
 } else if (arrayList3.size() > 4) {
 DebugLog.log("MOVABLES: Object has too many faces defined for group: (" +
 string6 + ") sheet = " + string1);
 } else {
 for (auto &string11 : strings0)
 if (((ArrayList)hashMap1.get(string11).size() > 1) {
 DebugLog.log("MOVABLES: " + string11 +
 " face defined more than once for group: (" + string6 +
 ") sheet = " + string1);
 boolean5 = false;
 }
 }

 if (boolean5) {
 int6++;

 for (auto &sprite6 : arrayList3)
 for (auto &string12 : strings0)
 std::vector arrayList5 = (ArrayList)hashMap1.get(string12);
 if (arrayList5.size() > 0 && arrayList5.get(0) != sprite6) {
 sprite6.getProperties().Set(
 string12 + "offset",
 Integer.toString(arrayList0.indexOf(arrayList5.get(0) -
 arrayList0.indexOf(sprite6));
 }
 }
 }
}
}
}
}

arrayList0.clear();
}

if (boolean2) {
 std::vector arrayList6 = new ArrayList(hashSet);
 Collections.sort(arrayList6);

 for (auto &string13 : arrayList6)
 System.out.println(string13.replaceAll(" ", "_")
 .replaceAll("-", "_")
 .replaceAll("'", "")
 .replaceAll("\\.", "") +
 " = \"" + string13 + "\",");
}
}

if (boolean3) {
 std::vector arrayList7 = new ArrayList(hashSet);
 Collections.sort(arrayList7);
 StringBuilder stringBuilder = new StringBuilder();

 for (auto &string14 : arrayList7)
 if (Translator.getMoveableDisplayNameOrNull(string14) == nullptr) {
 stringBuilder.append(string14.replaceAll(" ", "_")
 .replaceAll("-", "_")
 .replaceAll("'", "")
 .replaceAll("\\.", "") +
 " = \"" + string14 + "\",\n");
 }
}

std::string string15 = stringBuilder.toString();
if (!string15.empty() && Core.bDebug) {
 System.out.println("Missing translations in Moveables_EN.txt:\n" + string15);
}
}

if (boolean1) {
 try {
 this->saveMovableStats(hashMap2, fileNumber, int5, int6, int7, int4);
 } catch (Exception exception0) {
 }
}
}
catch (Exception exception1) {
 ExceptionLogger.logException(exception1);
}
}

void GenerateTilePropertyLookupTables() {
 TilePropertyAliasMap.instance.Generate(PropertyValueMap);
 PropertyValueMap.clear();
}

void LoadTileDefinitionsPropertyStrings(IsoSpriteManager sprMan,
 std::string_view filename,
 int fileNumber) {
 DebugLog.log("tiledef: loading " + filename);
 if (!GameServer.bServer) {
 Thread.yield();
 Core.getInstance().DoFrameReady();
 }

 try(FileInputStream fileInputStream = new FileInputStream(filename);
 BufferedInputStream bufferedInputStream =
 new BufferedInputStream(fileInputStream);) {
 int int0 = readInt(bufferedInputStream);
 int int1 = readInt(bufferedInputStream);
 int int2 = readInt(bufferedInputStream);
 SharedStrings sharedStrings = new SharedStrings();

 for (int int3 = 0; int3 < int2; int3++) {
 std::string string0 = readString(bufferedInputStream);
 std::string string1 = string0.trim();
 std::string string2 = readString(bufferedInputStream);
 this->tileImages.add(string2);
 int int4 = readInt(bufferedInputStream);
 int int5 = readInt(bufferedInputStream);
 int int6 = readInt(bufferedInputStream);
 int int7 = readInt(bufferedInputStream);

 for (int int8 = 0; int8 < int7; int8++) {
 int int9 = readInt(bufferedInputStream);

 for (int int10 = 0; int10 < int9; int10++) {
 string0 = readString(bufferedInputStream);
 std::string string3 = string0.trim();
 string0 = readString(bufferedInputStream);
 std::string string4 = string0.trim();
 IsoObjectType objectType = IsoObjectType.FromString(string3);
 string3 = sharedStrings.get(string3);
 std::vector arrayList = nullptr;
 if (PropertyValueMap.containsKey(string3) {
 arrayList = PropertyValueMap.get(string3);
 } else {
 arrayList = std::make_unique<ArrayList>();
 PropertyValueMap.put(string3, arrayList);
 }

 if (!arrayList.contains(string4) {
 arrayList.add(string4);
 }
 }
 }
 }
 }
 catch (Exception exception) {
 Logger.getLogger(GameWindow.class.getName())
 .log(Level.SEVERE, nullptr, exception);
 }
}

void SetCustomPropertyValues() {
 PropertyValueMap.get("WindowN").add("WindowN");
 PropertyValueMap.get("WindowW").add("WindowW");
 PropertyValueMap.get("DoorWallN").add("DoorWallN");
 PropertyValueMap.get("DoorWallW").add("DoorWallW");
 PropertyValueMap.get("WallSE").add("WallSE");
 std::vector arrayList = new ArrayList();

 for (int int0 = -96; int0 <= 96; int0++) {
 std::string string = Integer.toString(int0);
 arrayList.add(string);
 }

 PropertyValueMap.put("Noffset", arrayList);
 PropertyValueMap.put("Soffset", arrayList);
 PropertyValueMap.put("Woffset", arrayList);
 PropertyValueMap.put("Eoffset", arrayList);
 PropertyValueMap.get("tree").add("5");
 PropertyValueMap.get("tree").add("6");
 PropertyValueMap.get("lightR").add("0");
 PropertyValueMap.get("lightG").add("0");
 PropertyValueMap.get("lightB").add("0");
}

void setOpenDoorProperties(std::string_view string2,
 ArrayList<IsoSprite> arrayList) {
 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 IsoSprite sprite0 = (IsoSprite)arrayList.get(int0);
 if ((sprite0.getType() == IsoObjectType.doorN ||
 sprite0.getType() == IsoObjectType.doorW) &&
 !sprite0.getProperties().Is(IsoFlagType.open) {
 std::string string0 = sprite0.getProperties().Val("DoubleDoor");
 if (string0 != nullptr) {
 int int1 = PZMath.tryParseInt(string0, -1);
 if (int1 >= 5) {
 sprite0.getProperties().Set(IsoFlagType.open);
 }
 } else {
 std::string string1 = sprite0.getProperties().Val("GarageDoor");
 if (string1 != nullptr) {
 int int2 = PZMath.tryParseInt(string1, -1);
 if (int2 >= 4) {
 sprite0.getProperties().Set(IsoFlagType.open);
 }
 } else {
 IsoSprite sprite1 = IsoSpriteManager.instance.NamedMap.get(
 string2 + "_" + (sprite0.tileSheetIndex + 2);
 if (sprite1 != nullptr) {
 sprite1.setType(sprite0.getType());
 sprite1.getProperties().Set(sprite0.getType() == IsoObjectType.doorN
 ? IsoFlagType.doorN
 : IsoFlagType.doorW);
 sprite1.getProperties().Set(IsoFlagType.open);
 }
 }
 }
 }
 }
}

void saveMovableStats(ArrayList < String >> map, int int0, int int1, int int2,
 int int3, int int4) {
 File file0 = new File(ZomboidFileSystem.instance.getCacheDir());
 if (file0.exists() && file0.isDirectory()) {
 File file1 = new File(ZomboidFileSystem.instance.getCacheDir() +
 File.separator + "movables_stats_" + int0 + ".txt");

 try(FileWriter fileWriter = new FileWriter(file1, false) {
 fileWriter.write("### Movable objects ###" + System.lineSeparator());
 fileWriter.write("Single Face: " + int1 + System.lineSeparator());
 fileWriter.write("Multi Face: " + int2 + System.lineSeparator());
 fileWriter.write("Multi Face & Multi Sprite: " + int3 +
 System.lineSeparator());
 fileWriter.write("Total objects : " + (int1 + int2 + int3) +
 System.lineSeparator());
 fileWriter.write(" " + System.lineSeparator());
 fileWriter.write("Total sprites : " + int4 + System.lineSeparator());
 fileWriter.write(" " + System.lineSeparator());

 for (Entry entry : map.entrySet()) {
 fileWriter.write((String)entry.getKey() + System.lineSeparator());

 for (String string : (ArrayList)entry.getValue()) {
 fileWriter.write("\t" + string + System.lineSeparator());
 }
 }
 }
 catch (Exception exception) {
 exception.printStackTrace();
 }
 }
}

void addJumboTreeTileset(IsoSpriteManager spriteManager, int int5,
 std::string_view string1, int int4, int int1,
 int int6) {
 uint8_t byte0 = 2;

 for (int int0 = 0; int0 < int1; int0++) {
 for (int int2 = 0; int2 < byte0; int2++) {
 std::string string0 = "e_" + string1 + "JUMBO_1";
 int int3 = int0 * byte0 + int2;
 IsoSprite sprite = spriteManager.AddSprite(
 string0 + "_" + int3, int5 * 512 * 512 + int4 * 512 + int3);

 assert GameServer.bServer ||
 !sprite.CurrentAnim.Frames.empty() &&
 sprite.CurrentAnim.Frames.get(0).getTexture(IsoDirections.N) !=
 nullptr;

 sprite.setName(string0 + "_" + int3);
 sprite.setType(IsoObjectType.tree);
 sprite.getProperties().Set("tree", int2 == 0 ? "5" : "6");
 sprite.getProperties().UnSet(IsoFlagType.solid);
 sprite.getProperties().Set(IsoFlagType.blocksight);
 sprite.getProperties().CreateKeySet();
 sprite.moveWithWind = true;
 sprite.windType = int6;
 }
 }
}

void JumboTreeDefinitions(IsoSpriteManager spriteManager, int int0) {
 this->addJumboTreeTileset(spriteManager, int0, "americanholly", 1, 2, 3);
 this->addJumboTreeTileset(spriteManager, int0, "americanlinden", 2, 6, 2);
 this->addJumboTreeTileset(spriteManager, int0, "canadianhemlock", 3, 2, 3);
 this->addJumboTreeTileset(spriteManager, int0, "carolinasilverbell", 4, 6, 1);
 this->addJumboTreeTileset(spriteManager, int0, "cockspurhawthorn", 5, 6, 2);
 this->addJumboTreeTileset(spriteManager, int0, "dogwood", 6, 6, 2);
 this->addJumboTreeTileset(spriteManager, int0, "easternredbud", 7, 6, 2);
 this->addJumboTreeTileset(spriteManager, int0, "redmaple", 8, 6, 2);
 this->addJumboTreeTileset(spriteManager, int0, "riverbirch", 9, 6, 1);
 this->addJumboTreeTileset(spriteManager, int0, "virginiapine", 10, 2, 1);
 this->addJumboTreeTileset(spriteManager, int0, "yellowwood", 11, 6, 2);
 uint8_t byte0 = 12;
 uint8_t byte1 = 0;
 IsoSprite sprite = spriteManager.AddSprite(
 "jumbo_tree_01_" + byte1, int0 * 512 * 512 + byte0 * 512 + byte1);
 sprite.setName("jumbo_tree_01_" + byte1);
 sprite.setType(IsoObjectType.tree);
 sprite.getProperties().Set("tree", "4");
 sprite.getProperties().UnSet(IsoFlagType.solid);
 sprite.getProperties().Set(IsoFlagType.blocksight);
}

void loadedTileDefinitions() {
 CellLoader.smashedWindowSpriteMap.clear();

 for (IsoSprite sprite0 : IsoSpriteManager.instance.NamedMap.values()) {
 PropertyContainer propertyContainer = sprite0.getProperties();
 if (propertyContainer.Is(IsoFlagType.windowW) ||
 propertyContainer.Is(IsoFlagType.windowN) {
 std::string string = propertyContainer.Val("SmashedTileOffset");
 if (string != nullptr) {
 int int0 = PZMath.tryParseInt(string, 0);
 if (int0 != 0) {
 IsoSprite sprite1 =
 IsoSprite.getSprite(IsoSpriteManager.instance, sprite0, int0);
 if (sprite1 != nullptr) {
 CellLoader.smashedWindowSpriteMap.put(sprite1, sprite0);
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
 File file = ZomboidFileSystem.instance.getFileInCurrentSave("map_p.bin");
 if (!file.exists()) {
 PlayerDB.getInstance().importPlayersFromVehiclesDB();
 return PlayerDB.getInstance().loadLocalPlayerInfo(1);
 } else {
 FileInputStream fileInputStream = new FileInputStream(file);
 BufferedInputStream bufferedInputStream =
 new BufferedInputStream(fileInputStream);
 { std::lock_guard<std::mutex> __sync_lock__(SliceY.SliceBufferLock_mutex);
 SliceY.SliceBuffer.clear();
 int int0 = bufferedInputStream.read(SliceY.SliceBuffer.array());
 SliceY.SliceBuffer.limit(int0);
 bufferedInputStream.close();
 uint8_t byte0 = SliceY.SliceBuffer.get();
 uint8_t byte1 = SliceY.SliceBuffer.get();
 uint8_t byte2 = SliceY.SliceBuffer.get();
 uint8_t byte3 = SliceY.SliceBuffer.get();
 int int1 = -1;
 if (byte0 == 80 && byte1 == 76 && byte2 == 89 && byte3 == 82) {
 int1 = SliceY.SliceBuffer.getInt();
 } else {
 SliceY.SliceBuffer.rewind();
 }

 if (int1 >= 69) {
 std::string string = GameWindow.ReadString(SliceY.SliceBuffer);
 if (GameClient.bClient && int1 < 71) {
 string = ServerOptions.instance.ServerPlayerID.getValue();
 }

 if (GameClient.bClient && !IsoPlayer.isServerPlayerIDValid(string) {
 GameLoadingState.GameLoadingString =
 Translator.getText("IGUI_MP_ServerPlayerIDMismatch");
 GameLoadingState.playerWrongIP = true;
 return false;
 }
 } else if (GameClient.bClient &&
 ServerOptions.instance.ServerPlayerID.getValue().empty()) {
 GameLoadingState.GameLoadingString =
 Translator.getText("IGUI_MP_ServerPlayerIDMissing");
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
 this->randomizedBuildingList.add(std::make_unique<RBSafehouse>());
 this->randomizedBuildingList.add(std::make_unique<RBBurnt>());
 this->randomizedBuildingList.add(std::make_unique<RBOther>());
 this->randomizedBuildingList.add(std::make_unique<RBLooted>());
 this->randomizedBuildingList.add(std::make_unique<RBBurntFireman>());
 this->randomizedBuildingList.add(std::make_unique<RBBurntCorpse>());
 this->randomizedBuildingList.add(std::make_unique<RBShopLooted>());
 this->randomizedBuildingList.add(std::make_unique<RBKateAndBaldspot>());
 this->randomizedBuildingList.add(std::make_unique<RBStripclub>());
 this->randomizedBuildingList.add(std::make_unique<RBSchool>());
 this->randomizedBuildingList.add(std::make_unique<RBSpiffo>());
 this->randomizedBuildingList.add(std::make_unique<RBPizzaWhirled>());
 this->randomizedBuildingList.add(std::make_unique<RBPileOCrepe>());
 this->randomizedBuildingList.add(std::make_unique<RBCafe>());
 this->randomizedBuildingList.add(std::make_unique<RBBar>());
 this->randomizedBuildingList.add(std::make_unique<RBOffice>());
 this->randomizedBuildingList.add(std::make_unique<RBHairSalon>());
 this->randomizedBuildingList.add(std::make_unique<RBClinic>());
 this->randomizedVehicleStoryList.add(std::make_unique<RVSUtilityVehicle>());
 this->randomizedVehicleStoryList.add(
 std::make_unique<RVSConstructionSite>());
 this->randomizedVehicleStoryList.add(std::make_unique<RVSBurntCar>());
 this->randomizedVehicleStoryList.add(
 std::make_unique<RVSPoliceBlockadeShooting>());
 this->randomizedVehicleStoryList.add(std::make_unique<RVSPoliceBlockade>());
 this->randomizedVehicleStoryList.add(std::make_unique<RVSCarCrash>());
 this->randomizedVehicleStoryList.add(std::make_unique<RVSAmbulanceCrash>());
 this->randomizedVehicleStoryList.add(std::make_unique<RVSCarCrashCorpse>());
 this->randomizedVehicleStoryList.add(std::make_unique<RVSChangingTire>());
 this->randomizedVehicleStoryList.add(std::make_unique<RVSFlippedCrash>());
 this->randomizedVehicleStoryList.add(std::make_unique<RVSBanditRoad>());
 this->randomizedVehicleStoryList.add(std::make_unique<RVSTrailerCrash>());
 this->randomizedVehicleStoryList.add(std::make_unique<RVSCrashHorde>());
 this->randomizedZoneList.add(std::make_unique<RZSForestCamp>());
 this->randomizedZoneList.add(std::make_unique<RZSForestCampEaten>());
 this->randomizedZoneList.add(std::make_unique<RZSBuryingCamp>());
 this->randomizedZoneList.add(std::make_unique<RZSBeachParty>());
 this->randomizedZoneList.add(std::make_unique<RZSFishingTrip>());
 this->randomizedZoneList.add(std::make_unique<RZSBBQParty>());
 this->randomizedZoneList.add(std::make_unique<RZSHunterCamp>());
 this->randomizedZoneList.add(std::make_unique<RZSSexyTime>());
 this->randomizedZoneList.add(std::make_unique<RZSTrapperCamp>());
 this->randomizedZoneList.add(std::make_unique<RZSBaseball>());
 this->randomizedZoneList.add(std::make_unique<RZSMusicFestStage>());
 this->randomizedZoneList.add(std::make_unique<RZSMusicFest>());
 }

 zombie.randomizedWorld.randomizedBuilding.RBBasic.getUniqueRDSSpawned()
 .clear();
 if (!GameClient.bClient && !GameServer.bServer) {
 BodyDamageSync.instance = nullptr;
 } else {
 BodyDamageSync.instance = std::make_unique<BodyDamageSync>();
 }

 if (GameServer.bServer) {
 Core.GameSaveWorld = GameServer.ServerName;
 std::string string0 = ZomboidFileSystem.instance.getCurrentSaveDir();
 File file0 = new File(string0);
 if (!file0.exists()) {
 GameServer.ResetID = Rand.Next(10000000);
 ServerOptions.instance.putSaveOption("ResetID",
 String.valueOf(GameServer.ResetID);
 }

 LuaManager.GlobalObject.createWorld(Core.GameSaveWorld);
 }

 SavedWorldVersion = this->readWorldVersion();
 if (!GameServer.bServer) {
 File file1 = ZomboidFileSystem.instance.getFileInCurrentSave("map_ver.bin");

 try(FileInputStream fileInputStream = new FileInputStream(file1);
 DataInputStream dataInputStream =
 new DataInputStream(fileInputStream);) {
 int int0 = dataInputStream.readInt();
 if (int0 >= 25) {
 std::string string1 = GameWindow.ReadString(dataInputStream);
 if (!GameClient.bClient) {
 Core.GameMap = string1;
 }
 }

 if (int0 >= 74) {
 this->setDifficulty(GameWindow.ReadString(dataInputStream);
 }
 }
 catch (FileNotFoundException fileNotFoundException) {
 }
 }

 if (!GameServer.bServer || !GameServer.bSoftReset) {
 this->MetaGrid.CreateStep1();
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

 this->bHydroPowerOn = GameTime.getInstance().NightsSurvived <
 SandboxOptions.getInstance().getElecShutModifier();
 ZomboidGlobals.toLua();
 ItemPickerJava.InitSandboxLootSettings();
 this->SurvivorDescriptors.clear();
 IsoSpriteManager.instance.Dispose();
 if (GameClient.bClient && ServerOptions.instance.DoLuaChecksum.getValue()) {
 try {
 NetChecksum.comparer.beginCompare();
 GameLoadingState.GameLoadingString =
 Translator.getText("IGUI_MP_Checksum");
 long long0 = System.currentTimeMillis();
 long long1 = long0;

 while (!GameClient.checksumValid) {
 if (GameWindow.bServerDisconnected) {
 return;
 }

 if (System.currentTimeMillis() > long0 + 8000L) {
 DebugLog.log("checksum: timed out waiting for the server to respond");
 GameClient.connection.forceDisconnect("world-timeout-response");
 GameWindow.bServerDisconnected = true;
 GameWindow.kickReason = Translator.getText("UI_GameLoad_TimedOut");
 return;
 }

 if (System.currentTimeMillis() > long1 + 1000L) {
 DebugLog.log("checksum: waited one second");
 long1 += 1000L;
 }

 NetChecksum.comparer.update();
 if (GameClient.checksumValid) {
 break;
 }

 Thread.sleep(100L);
 }
 } catch (Exception exception0) {
 exception0.printStackTrace();
 }
 }

 GameLoadingState.GameLoadingString =
 Translator.getText("IGUI_MP_LoadTileDef");
 IsoSpriteManager spriteManager = IsoSpriteManager.instance;
 this->tileImages.clear();
 ZomboidFileSystem zomboidFileSystem = ZomboidFileSystem.instance;
 this->LoadTileDefinitionsPropertyStrings(
 spriteManager, zomboidFileSystem.getMediaPath("tiledefinitions.tiles"),
 0);
 this->LoadTileDefinitionsPropertyStrings(
 spriteManager, zomboidFileSystem.getMediaPath("newtiledefinitions.tiles"),
 1);
 this->LoadTileDefinitionsPropertyStrings(
 spriteManager,
 zomboidFileSystem.getMediaPath("tiledefinitions_erosion.tiles"), 2);
 this->LoadTileDefinitionsPropertyStrings(
 spriteManager,
 zomboidFileSystem.getMediaPath("tiledefinitions_apcom.tiles"), 3);
 this->LoadTileDefinitionsPropertyStrings(
 spriteManager,
 zomboidFileSystem.getMediaPath("tiledefinitions_overlays.tiles"), 4);
 this->LoadTileDefinitionsPropertyStrings(
 spriteManager,
 zomboidFileSystem.getMediaPath("tiledefinitions_noiseworks.patch.tiles"),
 -1);
 ZomboidFileSystem.instance.loadModTileDefPropertyStrings();
 this->SetCustomPropertyValues();
 this->GenerateTilePropertyLookupTables();
 this->LoadTileDefinitions(
 spriteManager, zomboidFileSystem.getMediaPath("tiledefinitions.tiles"),
 0);
 this->LoadTileDefinitions(
 spriteManager, zomboidFileSystem.getMediaPath("newtiledefinitions.tiles"),
 1);
 this->LoadTileDefinitions(
 spriteManager,
 zomboidFileSystem.getMediaPath("tiledefinitions_erosion.tiles"), 2);
 this->LoadTileDefinitions(
 spriteManager,
 zomboidFileSystem.getMediaPath("tiledefinitions_apcom.tiles"), 3);
 this->LoadTileDefinitions(
 spriteManager,
 zomboidFileSystem.getMediaPath("tiledefinitions_overlays.tiles"), 4);
 this->LoadTileDefinitions(
 spriteManager,
 zomboidFileSystem.getMediaPath("tiledefinitions_noiseworks.patch.tiles"),
 -1);
 this->JumboTreeDefinitions(spriteManager, 5);
 ZomboidFileSystem.instance.loadModTileDefs();
 GameLoadingState.GameLoadingString = "";
 spriteManager.AddSprite("media/ui/missing-tile.png");
 LuaEventManager.triggerEvent("OnLoadedTileDefinitions", spriteManager);
 this->loadedTileDefinitions();
 if (GameServer.bServer && GameServer.bSoftReset) {
 WorldConverter.instance.softreset();
 }

 try {
 WeatherFxMask.init();
 } catch (Exception exception1) {
 System.out.print(exception1.getStackTrace());
 }

 TemplateText.Initialize();
 IsoRegions.init();
 ObjectRenderEffects.init();
 WorldConverter.instance.convert(Core.GameSaveWorld, spriteManager);
 if (!GameLoadingState.build23Stop) {
 SandboxOptions.instance.handleOldZombiesFile2();
 GameTime.getInstance().init();
 GameTime.getInstance().load();
 ImprovedFog.init();
 ZomboidRadio.getInstance().Init(SavedWorldVersion);
 GlobalModData.instance.init();
 if (GameServer.bServer &&
 Core.getInstance().getPoisonousBerry() == nullptr) {
 Core.getInstance().initPoisonousBerry();
 }

 if (GameServer.bServer &&
 Core.getInstance().getPoisonousMushroom() == nullptr) {
 Core.getInstance().initPoisonousMushroom();
 }

 ErosionGlobals.Boot(spriteManager);
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
 this->MetaGrid.CreateStep2();
 ClimateManager.getInstance().init(this->MetaGrid);
 SafeHouse.init();
 if (!GameClient.bClient) {
 StashSystem.init();
 }

 LuaEventManager.triggerEvent("OnLoadMapZones");
 this->MetaGrid.load();
 this->MetaGrid.loadZones();
 this->MetaGrid.processZones();
 LuaEventManager.triggerEvent("OnLoadedMapZones");
 if (GameServer.bServer) {
 ServerMap.instance.init(this->MetaGrid);
 }

 int int1 = 0;
 int int2 = 0;
 if (GameClient.bClient) {
 if (ClientPlayerDB.getInstance().clientLoadNetworkPlayer() &&
 ClientPlayerDB.getInstance().isAliveMainNetworkPlayer()) {
 int2 = 1;
 }
 } else {
 int2 = PlayerDBHelper.isPlayerAlive(
 ZomboidFileSystem.instance.getCurrentSaveDir(), 1);
 }

 if (GameServer.bServer) {
 ServerPlayerDB.setAllow(true);
 }

 if (!GameClient.bClient && !GameServer.bServer) {
 PlayerDB.setAllow(true);
 }

 int int3 = 0;
 int int4 = 0;
 int int5 = 0;
 if (int2) {
 int1 = (boolean)1;
 if (!this->LoadPlayerForInfo()) {
 return;
 }

 WorldX = IsoChunkMap.SWorldX[IsoPlayer.getPlayerIndex()];
 WorldY = IsoChunkMap.SWorldY[IsoPlayer.getPlayerIndex()];
 int3 = IsoChunkMap.WorldXA;
 int4 = IsoChunkMap.WorldYA;
 int5 = IsoChunkMap.WorldZA;
 } else {
 int1 = (boolean)0;
 if (GameClient.bClient &&
 !ServerOptions.instance.SpawnPoint.getValue().empty()) {
 String[] strings0 =
 ServerOptions.instance.SpawnPoint.getValue().split(",");
 if (strings0.length == 3) {
 try {
 IsoChunkMap.MPWorldXA = new Integer(strings0[0].trim());
 IsoChunkMap.MPWorldYA = new Integer(strings0[1].trim());
 IsoChunkMap.MPWorldZA = new Integer(strings0[2].trim());
 } catch (NumberFormatException numberFormatException0) {
 DebugLog.log("ERROR: SpawnPoint must be x,y,z, got \"" +
 ServerOptions.instance.SpawnPoint.getValue() + "\"");
 IsoChunkMap.MPWorldXA = 0;
 IsoChunkMap.MPWorldYA = 0;
 IsoChunkMap.MPWorldZA = 0;
 }
 } else {
 DebugLog.log("ERROR: SpawnPoint must be x,y,z, got \"" +
 ServerOptions.instance.SpawnPoint.getValue() + "\"");
 }
 }

 if (this->getLuaSpawnCellX() >= 0 &&
 (!GameClient.bClient ||
 IsoChunkMap.MPWorldXA == 0 && IsoChunkMap.MPWorldYA == 0) {
 IsoChunkMap.WorldXA = this->getLuaPosX() + 300 * this->getLuaSpawnCellX();
 IsoChunkMap.WorldYA = this->getLuaPosY() + 300 * this->getLuaSpawnCellY();
 IsoChunkMap.WorldZA = this->getLuaPosZ();
 if (GameClient.bClient &&
 ServerOptions.instance.SafehouseAllowRespawn.getValue()) {
 for (int int6 = 0; int6 < SafeHouse.getSafehouseList().size();
 int6++) {
 SafeHouse safeHouse0 = SafeHouse.getSafehouseList().get(int6);
 if (safeHouse0.getPlayers().contains(GameClient.username) &&
 safeHouse0.isRespawnInSafehouse(GameClient.username) {
 IsoChunkMap.WorldXA = safeHouse0.getX() + safeHouse0.getH() / 2;
 IsoChunkMap.WorldYA = safeHouse0.getY() + safeHouse0.getW() / 2;
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
 KahluaTable table0 =
 (KahluaTable)LuaManager.env.rawget("selectedDebugScenario");
 if (table0 != nullptr) {
 KahluaTable table1 = (KahluaTable)table0.rawget("startLoc");
 int int7 = ((Double)table1.rawget("x")).intValue();
 int int8 = ((Double)table1.rawget("y")).intValue();
 int int9 = ((Double)table1.rawget("z")).intValue();
 IsoChunkMap.WorldXA = int7;
 IsoChunkMap.WorldYA = int8;
 IsoChunkMap.WorldZA = int9;
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
 this->CurrentCell =
 CellLoader.LoadCellBinaryChunk(spriteManager, WorldX, WorldY);
 ClimateManager.getInstance().postCellLoadSetSnow();
 GameLoadingState.GameLoadingString =
 Translator.getText("IGUI_MP_LoadWorld");
 MapCollisionData.instance.start();
 MapItem.LoadWorldMap();

 while (WorldStreamer.instance.isBusy()) {
 try {
 Thread.sleep(100L);
 } catch (InterruptedException interruptedException) {
 interruptedException.printStackTrace();
 }
 }

 std::vector arrayList = new ArrayList();
 arrayList.addAll(IsoChunk.loadGridSquare);

 for (auto &chunk : arrayList)
 this->CurrentCell.ChunkMap[0].setChunkDirect(chunk, false);
 }

 IsoChunk.bDoServerRequests = true;
 if (int1 && SystemDisabler.doPlayerCreation) {
 this->CurrentCell.LoadPlayer(SavedWorldVersion);
 if (GameClient.bClient) {
 IsoPlayer.getInstance().setUsername(GameClient.username);
 }

 ZomboidRadio.getInstance().getRecordedMedia().handleLegacyListenedLines(
 IsoPlayer.getInstance());
 } else {
 ZomboidRadio.getInstance().getRecordedMedia().handleLegacyListenedLines(
 nullptr);
 IsoGridSquare square0 = nullptr;
 if (IsoPlayer.numPlayers == 0) {
 IsoPlayer.numPlayers = 1;
 }

 int int10 = IsoChunkMap.WorldXA;
 int int11 = IsoChunkMap.WorldYA;
 int int12 = IsoChunkMap.WorldZA;
 if (GameClient.bClient &&
 !ServerOptions.instance.SpawnPoint.getValue().empty()) {
 String[] strings1 =
 ServerOptions.instance.SpawnPoint.getValue().split(",");
 if (strings1.length != 3) {
 DebugLog.log("ERROR: SpawnPoint must be x,y,z, got \"" +
 ServerOptions.instance.SpawnPoint.getValue() + "\"");
 } else {
 try {
 int int13 = new Integer(strings1[0].trim());
 int int14 = new Integer(strings1[1].trim());
 int int15 = new Integer(strings1[2].trim());
 if (GameClient.bClient &&
 ServerOptions.instance.SafehouseAllowRespawn.getValue()) {
 for (int int16 = 0; int16 < SafeHouse.getSafehouseList().size();
 int16++) {
 SafeHouse safeHouse1 = SafeHouse.getSafehouseList().get(int16);
 if (safeHouse1.getPlayers().contains(GameClient.username) &&
 safeHouse1.isRespawnInSafehouse(GameClient.username) {
 int13 = safeHouse1.getX() + safeHouse1.getH() / 2;
 int14 = safeHouse1.getY() + safeHouse1.getW() / 2;
 int15 = 0;
 }
 }
 }

 if (this->CurrentCell.getGridSquare(int13, int14, int15) != nullptr) {
 int10 = int13;
 int11 = int14;
 int12 = int15;
 }
 } catch (NumberFormatException numberFormatException1) {
 DebugLog.log("ERROR: SpawnPoint must be x,y,z, got \"" +
 ServerOptions.instance.SpawnPoint.getValue() + "\"");
 }
 }
 }

 square0 = this->CurrentCell.getGridSquare(int10, int11, int12);
 if (SystemDisabler.doPlayerCreation && !GameServer.bServer) {
 if (square0 != nullptr && square0.isFree(false) &&
 square0.getRoom() != nullptr) {
 IsoGridSquare square1 = square0;
 square0 = square0.getRoom().getFreeTile();
 if (square0.empty()) {
 square0 = square1;
 }
 }

 IsoPlayer player0 = nullptr;
 if (this->getLuaPlayerDesc() != nullptr) {
 if (GameClient.bClient &&
 ServerOptions.instance.SafehouseAllowRespawn.getValue()) {
 square0 = this->CurrentCell.getGridSquare(
 IsoChunkMap.WorldXA, IsoChunkMap.WorldYA, IsoChunkMap.WorldZA);
 if (square0 != nullptr && square0.isFree(false) &&
 square0.getRoom() != nullptr) {
 IsoGridSquare square2 = square0;
 square0 = square0.getRoom().getFreeTile();
 if (square0.empty()) {
 square0 = square2;
 }
 }
 }

 if (square0.empty()) {
 throw RuntimeException("can't create player at x,y,z=" + int10 +
 "," + int11 + "," + int12 +
 " because the square is nullptr");
 }

 WorldSimulation.instance.create();
 player0 = new IsoPlayer(instance.CurrentCell, this->getLuaPlayerDesc(),
 square0.getX(), square0.getY(), square0.getZ());
 if (GameClient.bClient) {
 player0.setUsername(GameClient.username);
 }

 player0.setDir(IsoDirections.SE);
 player0.sqlID = 1;
 IsoPlayer.players[0] = player0;
 IsoPlayer.setInstance(player0);
 IsoCamera.CamCharacter = player0;
 }

 IsoPlayer player1 = IsoPlayer.getInstance();
 player1.applyTraits(this->getLuaTraits());
 ProfessionFactory.Profession profession = ProfessionFactory.getProfession(
 player1.getDescriptor().getProfession());
 if (profession != nullptr && !profession.getFreeRecipes().empty()) {
 for (String string2 : profession.getFreeRecipes()) {
 player1.getKnownRecipes().add(string2);
 }
 }

 for (String string3 : this->getLuaTraits()) {
 TraitFactory.Trait trait = TraitFactory.getTrait(string3);
 if (trait != nullptr && !trait.getFreeRecipes().empty()) {
 for (String string4 : trait.getFreeRecipes()) {
 player1.getKnownRecipes().add(string4);
 }
 }
 }

 if (square0 != nullptr && square0.getRoom() != nullptr) {
 square0.getRoom().def.setExplored(true);
 square0.getRoom().building.setAllExplored(true);
 if (!GameServer.bServer && !GameClient.bClient) {
 ZombiePopulationManager.instance.playerSpawnedAt(
 square0.getX(), square0.getY(), square0.getZ());
 }
 }

 player1.createKeyRing();
 if (!GameClient.bClient) {
 Core.getInstance().initPoisonousBerry();
 Core.getInstance().initPoisonousMushroom();
 }

 LuaEventManager.triggerEvent("OnNewGame", player0, square0);
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
 int1 = (int)IsoPlayer.getInstance().getX();
 int2 = (int)IsoPlayer.getInstance().getY();
 int3 = (int)IsoPlayer.getInstance().getZ();

 while (int3 > 0) {
 IsoGridSquare square3 =
 this->CurrentCell.getGridSquare(int1, int2, int3);
 if (square3 != nullptr && square3.TreatAsSolidFloor()) {
 break;
 }

 IsoPlayer.getInstance().setZ(--int3);
 }
 }

 IsoPlayer.getInstance().setCurrent(
 this->CurrentCell.getGridSquare((int)IsoPlayer.getInstance().getX(),
 (int)IsoPlayer.getInstance().getY(),
 (int)IsoPlayer.getInstance().getZ()));
 }

 if (!this->bLoaded) {
 if (!this->CurrentCell.getBuildingList().empty()) {
 }

 if (!this->bLoaded) {
 this->PopulateCellWithSurvivors();
 }
 }

 if (IsoPlayer.players[0] != nullptr &&
 !this->CurrentCell.getObjectList().contains(IsoPlayer.players[0])) {
 this->CurrentCell.getObjectList().add(IsoPlayer.players[0]);
 }

 LightingThread.instance.create();
 GameLoadingState.GameLoadingString = "";
 initMessaging();
 WorldDictionary.onWorldLoaded();
}
}

int readWorldVersion() {
 if (GameServer.bServer) {
 File file0 = ZomboidFileSystem.instance.getFileInCurrentSave("map_t.bin");

 try(FileInputStream fileInputStream0 = new FileInputStream(file0);
 DataInputStream dataInputStream0 =
 new DataInputStream(fileInputStream0);) {
 uint8_t byte0 = dataInputStream0.readByte();
 uint8_t byte1 = dataInputStream0.readByte();
 uint8_t byte2 = dataInputStream0.readByte();
 uint8_t byte3 = dataInputStream0.readByte();
 if (byte0 == 71 && byte1 == 77 && byte2 == 84 && byte3 == 77) {
 return dataInputStream0.readInt();
 }

 return -1;
 }
 catch (FileNotFoundException fileNotFoundException0) {
 }
 catch (IOException iOException0) {
 ExceptionLogger.logException(iOException0);
 }

 return -1;
 } else {
 File file1 = ZomboidFileSystem.instance.getFileInCurrentSave("map_ver.bin");

 try {
 int int0;
 try(FileInputStream fileInputStream1 = new FileInputStream(file1);
 DataInputStream dataInputStream1 =
 new DataInputStream(fileInputStream1);) {
 int0 = dataInputStream1.readInt();
 }

 return int0;
 } catch (FileNotFoundException fileNotFoundException1) {
 } catch (IOException iOException1) {
 ExceptionLogger.logException(iOException1);
 }

 return -1;
 }
}

public
ArrayList<String> getLuaTraits() {
 if (this->luatraits.empty()) {
 this->luatraits = std::make_unique<ArrayList<>>();
 }

 return this->luatraits;
}

void addLuaTrait(std::string_view trait) { this->getLuaTraits().add(trait); }

SurvivorDesc getLuaPlayerDesc() { return this->luaDesc; }

void setLuaPlayerDesc(SurvivorDesc desc) { this->luaDesc = desc; }

void KillCell() {
 this->helicopter.deactivate();
 CollisionManager.instance.ContactMap.clear();
 IsoDeadBody.Reset();
 FliesSound.instance.Reset();
 IsoObjectPicker.Instance.Init();
 IsoChunkMap.SharedChunks.clear();
 SoundManager.instance.StopMusic();
 WorldSoundManager.instance.KillCell();
 ZombieGroupManager.instance.Reset();
 this->CurrentCell.Dispose();
 IsoSpriteManager.instance.Dispose();
 this->CurrentCell = nullptr;
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
 this->MetaGrid.Dispose();
 instance = std::make_unique<IsoWorld>();
}

void setDrawWorld(bool b) { this->bDrawWorld = b; }

void sceneCullZombies() {
 this->zombieWithModel.clear();
 this->zombieWithoutModel.clear();

 for (int int0 = 0; int0 < this->CurrentCell.getZombieList().size(); int0++) {
 IsoZombie zombie0 = this->CurrentCell.getZombieList().get(int0);
 bool boolean0 = false;

 for (int int1 = 0; int1 < IsoPlayer.numPlayers; int1++) {
 IsoPlayer player = IsoPlayer.players[int1];
 if (player != nullptr && zombie0.current != nullptr) {
 float float0 = zombie0.getScreenProperX(int1);
 float float1 = zombie0.getScreenProperY(int1);
 if (!(float0 < -100.0F) && !(float1 < -100.0F) &&
 !(float0 > Core.getInstance().getOffscreenWidth(int1) + 100) &&
 !(float1 > Core.getInstance().getOffscreenHeight(int1) + 100) &&
 (zombie0.getAlpha(int1) != 0.0F &&
 zombie0.legsSprite.def.alpha != 0.0F ||
 zombie0.current.isCouldSee(int1)) {
 boolean0 = true;
 break;
 }
 }
 }

 if (boolean0 && zombie0.isCurrentState(FakeDeadZombieState.instance())) {
 boolean0 = false;
 }

 if (boolean0) {
 this->zombieWithModel.add(zombie0);
 } else {
 this->zombieWithoutModel.add(zombie0);
 }
 }

 Collections.sort(this->zombieWithModel, compScoreToPlayer);
 int int2 = 0;
 int int3 = 0;
 int int4 = 0;
 short short0 = 510;
 PerformanceSettings.AnimationSkip = 0;

 for (int int5 = 0; int5 < this->zombieWithModel.size(); int5++) {
 IsoZombie zombie1 = this->zombieWithModel.get(int5);
 if (int4 < short0) {
 if (!zombie1.Ghost) {
 int3++;
 int4++;
 zombie1.setSceneCulled(false);
 if (zombie1.legsSprite != nullptr &&
 zombie1.legsSprite.modelSlot != nullptr) {
 if (int3 > PerformanceSettings.ZombieAnimationSpeedFalloffCount) {
 int2++;
 int3 = 0;
 }

 if (int4 < PerformanceSettings.ZombieBonusFullspeedFalloff) {
 zombie1.legsSprite.modelSlot.model.setInstanceSkip(
 int3 / PerformanceSettings.ZombieBonusFullspeedFalloff);
 int3 = 0;
 } else {
 zombie1.legsSprite.modelSlot.model.setInstanceSkip(
 int2 + PerformanceSettings.AnimationSkip);
 }

 if (zombie1.legsSprite.modelSlot.model.AnimPlayer != nullptr) {
 if (int4 < PerformanceSettings.numberZombiesBlended) {
 zombie1.legsSprite.modelSlot.model.AnimPlayer.bDoBlending =
 !zombie1.isAlphaAndTargetZero(0) ||
 !zombie1.isAlphaAndTargetZero(1) ||
 !zombie1.isAlphaAndTargetZero(2) ||
 !zombie1.isAlphaAndTargetZero(3);
 } else {
 zombie1.legsSprite.modelSlot.model.AnimPlayer.bDoBlending = false;
 }
 }
 }
 }
 } else {
 zombie1.setSceneCulled(true);
 if (zombie1.hasAnimationPlayer()) {
 zombie1.getAnimationPlayer().bDoBlending = false;
 }
 }
 }

 for (int int6 = 0; int6 < this->zombieWithoutModel.size(); int6++) {
 IsoZombie zombie2 = this->zombieWithoutModel.get(int6);
 if (zombie2.hasActiveModel()) {
 zombie2.setSceneCulled(true);
 }

 if (zombie2.hasAnimationPlayer()) {
 zombie2.getAnimationPlayer().bDoBlending = false;
 }
 }
}

void render() {
 IsoWorld.s_performance.isoWorldRender.invokeAndMeasure(
 this, IsoWorld::renderInternal);
}

void renderInternal() {
 if (this->bDrawWorld) {
 if (IsoCamera.CamCharacter != nullptr) {
 SpriteRenderer.instance.doCoreIntParam(0, IsoCamera.CamCharacter.x);
 SpriteRenderer.instance.doCoreIntParam(1, IsoCamera.CamCharacter.y);
 SpriteRenderer.instance.doCoreIntParam(2, IsoCamera.CamCharacter.z);

 try {
 this->sceneCullZombies();
 } catch (Throwable throwable0) {
 ExceptionLogger.logException(throwable0);
 }

 try {
 WeatherFxMask.initMask();
 DeadBodyAtlas.instance.render();
 WorldItemAtlas.instance.render();
 this->CurrentCell.render();
 this->DrawIsoCursorHelper();
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
 } catch (Throwable throwable1) {
 ExceptionLogger.logException(throwable1);
 }
 }
 }
}

void DrawIsoCursorHelper() {
 if (Core.getInstance().getOffscreenBuffer() == nullptr) {
 IsoPlayer player = IsoPlayer.getInstance();
 if (player != nullptr && !player.isDead() && player.isAiming() &&
 player.PlayerIndex == 0 && player.JoypadBind == -1) {
 if (!GameTime.isGamePaused()) {
 float float0 = 0.05F;
 switch (Core.getInstance().getIsoCursorVisibility()) {
 case 0:
 return;
 case 1:
 float0 = 0.05F;
 break;
 case 2:
 float0 = 0.1F;
 break;
 case 3:
 float0 = 0.15F;
 break;
 case 4:
 float0 = 0.3F;
 break;
 case 5:
 float0 = 0.5F;
 break;
 case 6:
 float0 = 0.75F;
 }

 if (Core.getInstance().isFlashIsoCursor()) {
 if (this->flashIsoCursorInc) {
 this->flashIsoCursorA += 0.1F;
 if (this->flashIsoCursorA >= 1.0F) {
 this->flashIsoCursorInc = false;
 }
 } else {
 this->flashIsoCursorA -= 0.1F;
 if (this->flashIsoCursorA <= 0.0F) {
 this->flashIsoCursorInc = true;
 }
 }

 float0 = this->flashIsoCursorA;
 }

 Texture texture = Texture.getSharedTexture("media/ui/isocursor.png");
 int int0 = (int)(texture.getWidth() * Core.TileScale / 2.0F);
 int int1 = (int)(texture.getHeight() * Core.TileScale / 2.0F);
 SpriteRenderer.instance.setDoAdditive(true);
 SpriteRenderer.instance.renderi(
 texture, Mouse.getX() - int0 / 2, Mouse.getY() - int1 / 2, int0,
 int1, float0, float0, float0, float0, nullptr);
 SpriteRenderer.instance.setDoAdditive(false);
 }
 }
 }
}

void update() {
 IsoWorld.s_performance.isoWorldUpdate.invokeAndMeasure(
 this, IsoWorld::updateInternal);
}

void updateInternal() {
 this->m_frameNo++;

 try {
 if (GameServer.bServer) {
 VehicleManager.instance.serverUpdate();
 }
 } catch (Exception exception0) {
 exception0.printStackTrace();
 }

 WorldSimulation.instance.update();
 ImprovedFog.update();
 this->helicopter.update();
 long long0 = System.currentTimeMillis();
 if (long0 - this->emitterUpdateMS >= 30L) {
 this->emitterUpdateMS = long0;
 this->emitterUpdate = true;
 } else {
 this->emitterUpdate = false;
 }

 for (int int0 = 0; int0 < this->currentEmitters.size(); int0++) {
 BaseSoundEmitter baseSoundEmitter = this->currentEmitters.get(int0);
 if (this->emitterUpdate || baseSoundEmitter.hasSoundsToStart()) {
 baseSoundEmitter.tick();
 }

 if (baseSoundEmitter.empty()) {
 FMODSoundEmitter fMODSoundEmitter =
 Type.tryCastTo(baseSoundEmitter, FMODSoundEmitter.class);
 if (fMODSoundEmitter != nullptr) {
 fMODSoundEmitter.clearParameters();
 }

 this->currentEmitters.remove(int0);
 this->freeEmitters.push(baseSoundEmitter);
 IsoObject object = this->emitterOwners.remove(baseSoundEmitter);
 if (object != nullptr && object.emitter == baseSoundEmitter) {
 object.emitter = nullptr;
 }

 int0--;
 }
 }

 if (!GameClient.bClient && !GameServer.bServer) {
 IsoMetaCell metaCell = this->MetaGrid.getCurrentCellData();
 if (metaCell != nullptr) {
 metaCell.checkTriggers();
 }
 }

 WorldSoundManager.instance.initFrame();
 ZombieGroupManager.instance.preupdate();
 OnceEvery.update();
 CollisionManager.instance.initUpdate();

 for (int int1 = 0; int1 < this->CurrentCell.getBuildingList().size(); int1++) {
 this->CurrentCell.getBuildingList().get(int1).update();
 }

 ClimateManager.getInstance().update();
 ObjectRenderEffects.updateStatic();
 this->CurrentCell.update();
 IsoRegions.update();
 HaloTextHelper.update();
 CollisionManager.instance.ResolveContacts();

 for (int int2 = 0; int2 < this->AddCoopPlayers.size(); int2++) {
 AddCoopPlayer addCoopPlayer = this->AddCoopPlayers.get(int2);
 addCoopPlayer.update();
 if (addCoopPlayer.isFinished()) {
 this->AddCoopPlayers.remove(int2--);
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
 } catch (Exception exception1) {
 ExceptionLogger.logException(exception1);
 }

 if (this->updateSafehousePlayers > 0 &&
 (GameServer.bServer || GameClient.bClient) {
 this->updateSafehousePlayers--;
 if (this->updateSafehousePlayers == 0) {
 this->updateSafehousePlayers = 200;
 SafeHouse.updateSafehousePlayersConnected();
 }
 }

 m_animationRecorderDiscard = false;
}

IsoCell getCell() { return this->CurrentCell; }

void PopulateCellWithSurvivors() {}

int getWorldSquareY() {
 return this->CurrentCell.ChunkMap[IsoPlayer.getPlayerIndex()].WorldY * 10;
}

int getWorldSquareX() {
 return this->CurrentCell.ChunkMap[IsoPlayer.getPlayerIndex()].WorldX * 10;
}

IsoMetaChunk getMetaChunk(int wx, int wy) {
 return this->MetaGrid.getChunkData(wx, wy);
}

IsoMetaChunk getMetaChunkFromTile(int wx, int wy) {
 return this->MetaGrid.getChunkDataFromTile(wx, wy);
}

/**
 * Utility method for ClimateManager.getTemperature()
 * @return The current temperature.
 */
float getGlobalTemperature() {
 return ClimateManager.getInstance().getTemperature();
}

/**
 * setGlobalTemperature is now deprecated. Does nothing. member
 * globalTemperature is replaced with ClimateManager.getTemperature()
 */
void setGlobalTemperature(float globalTemperature) {}

std::string getWeather() { return this->weather; }

void setWeather(std::string_view _weather) { this->weather = _weather; }

int getLuaSpawnCellX() { return this->luaSpawnCellX; }

void setLuaSpawnCellX(int _luaSpawnCellX) {
 this->luaSpawnCellX = _luaSpawnCellX;
}

int getLuaSpawnCellY() { return this->luaSpawnCellY; }

void setLuaSpawnCellY(int _luaSpawnCellY) {
 this->luaSpawnCellY = _luaSpawnCellY;
}

int getLuaPosX() { return this->luaPosX; }

void setLuaPosX(int _luaPosX) { this->luaPosX = _luaPosX; }

int getLuaPosY() { return this->luaPosY; }

void setLuaPosY(int _luaPosY) { this->luaPosY = _luaPosY; }

int getLuaPosZ() { return this->luaPosZ; }

void setLuaPosZ(int _luaPosZ) { this->luaPosZ = _luaPosZ; }

std::string getWorld() { return Core.GameSaveWorld; }

void transmitWeather() {
 if (GameServer.bServer) {
 GameServer.sendWeather();
 }
}

bool isValidSquare(int _x, int _y, int z) {
 return z >= 0 && z < 8 ? this->MetaGrid.isValidSquare(_x, _y) : false;
}

public
ArrayList<RandomizedZoneStoryBase> getRandomizedZoneList() {
 return this->randomizedZoneList;
}

public
ArrayList<RandomizedBuildingBase> getRandomizedBuildingList() {
 return this->randomizedBuildingList;
}

public
ArrayList<RandomizedVehicleStoryBase> getRandomizedVehicleStoryList() {
 return this->randomizedVehicleStoryList;
}

RandomizedVehicleStoryBase
getRandomizedVehicleStoryByName(std::string_view name) {
 for (int int0 = 0; int0 < this->randomizedVehicleStoryList.size(); int0++) {
 RandomizedVehicleStoryBase randomizedVehicleStoryBase =
 this->randomizedVehicleStoryList.get(int0);
 if (randomizedVehicleStoryBase.getName().equalsIgnoreCase(name) {
 return randomizedVehicleStoryBase;
 }
 }

 return nullptr;
}

RandomizedBuildingBase getRBBasic() { return this->RBBasic; }

std::string getDifficulty() { return Core.getDifficulty(); }

void setDifficulty(std::string_view difficulty) {
 Core.setDifficulty(difficulty);
}

static bool getZombiesDisabled() {
 return NoZombies || !SystemDisabler.doZombieCreation ||
 SandboxOptions.instance.Zombies.getValue() == 6;
}

static bool getZombiesEnabled() { return !getZombiesDisabled(); }

ClimateManager getClimateManager() { return ClimateManager.getInstance(); }

IsoPuddles getPuddlesManager() { return IsoPuddles.getInstance(); }

static int getWorldVersion() { return 195; }

public
HashMap<String, ArrayList<Double>> getSpawnedZombieZone() {
 return this->spawnedZombieZone;
}

int getTimeSinceLastSurvivorInHorde() {
 return this->timeSinceLastSurvivorInHorde;
}

void setTimeSinceLastSurvivorInHorde(int _timeSinceLastSurvivorInHorde) {
 this->timeSinceLastSurvivorInHorde = _timeSinceLastSurvivorInHorde;
}

float getWorldAgeDays() {
 float float0 = (float)GameTime.getInstance().getWorldAgeHours() / 24.0F;
 return float0 + (SandboxOptions.instance.TimeSinceApo.getValue() - 1) * 30;
}

public
HashMap<String, ArrayList<String>> getAllTiles() { return this->allTiles; }

public
ArrayList<String> getAllTilesName() {
 std::vector arrayList = new ArrayList();
 Iterator iterator = this->allTiles.keySet().iterator();

 while (iterator.hasNext()) {
 arrayList.add((String)iterator.next());
 }

 Collections.sort(arrayList);
 return arrayList;
}

public
ArrayList<String> getAllTiles(String filename) {
 return this->allTiles.get(filename);
}

bool isHydroPowerOn() { return this->bHydroPowerOn; }

void setHydroPowerOn(bool on) { this->bHydroPowerOn = on; }

public
ArrayList<String> getTileImageNames() { return this->tileImages; }

private
static class CompDistToPlayer implements Comparator<IsoZombie> {
 float px;
 float py;

 int compare(IsoZombie zombie0, IsoZombie zombie1) {
 float float0 = IsoUtils.DistanceManhatten((int)zombie0.x, (int)zombie0.y,
 this->px, this->py);
 float float1 = IsoUtils.DistanceManhatten((int)zombie1.x, (int)zombie1.y,
 this->px, this->py);
 if (float0 < float1) {
 return -1;
 } else {
 return float0 > float1 ? 1 : 0;
 }
 }
}

private static class CompScoreToPlayer implements Comparator<IsoZombie> {
 int compare(IsoZombie arg0, IsoZombie arg1) {
 float float0 = this->getScore(arg0);
 float float1 = this->getScore(arg1);
 if (float0 < float1) {
 return 1;
 } else {
 return float0 > float1 ? -1 : 0;
 }
 }

 float getScore(IsoZombie arg0) {
 float float0 = Float.MIN_VALUE;

 for (int int0 = 0; int0 < 4; int0++) {
 IsoPlayer player = IsoPlayer.players[int0];
 if (player != nullptr && player.current != nullptr) {
 float float1 = player.getZombieRelevenceScore(arg0);
 float0 = Math.max(float0, float1);
 }
 }

 return float0;
 }
}

class Frame {
public
 ArrayList<Integer> xPos = std::make_unique<ArrayList<>>();
public
 ArrayList<Integer> yPos = std::make_unique<ArrayList<>>();
public
 ArrayList<Integer> Type = std::make_unique<ArrayList<>>();

public
 Frame() {
 Iterator iterator =
 IsoWorld.instance.CurrentCell.getObjectList().iterator();

 while (iterator != nullptr && iterator.hasNext()) {
 IsoMovingObject movingObject = (IsoMovingObject)iterator.next();
 uint8_t byte0 = 2;
 if (movingObject instanceof IsoPlayer) {
 byte0 = 0;
 } else if (movingObject instanceof IsoSurvivor) {
 byte0 = 1;
 } else {
 if (!(movingObject instanceof IsoZombie) ||
 ((IsoZombie)movingObject).Ghost) {
 continue;
 }

 byte0 = 2;
 }

 this->xPos.add((int)movingObject.getX());
 this->yPos.add((int)movingObject.getY());
 this->Type.add(Integer.valueOf(byte0);
 }
 }
}

public static class MetaCell {
 int x;
 int y;
 int zombieCount;
 IsoDirections zombieMigrateDirection;
public
 int[][] from = new int[3][3];
}

private static class s_performance {
 static const PerformanceProfileProbe isoWorldUpdate =
 new PerformanceProfileProbe("IsoWorld.update");
 static const PerformanceProfileProbe isoWorldRender =
 new PerformanceProfileProbe("IsoWorld.render");
}
}
} // namespace iso
} // namespace zombie
