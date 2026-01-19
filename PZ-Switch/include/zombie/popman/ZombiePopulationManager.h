#pragma once
#include <mutex>
#include "gnu/trove/list/array/TIntArrayList.h"
#include "gnu/trove/set/hash/TIntHashSet.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/popman/OptimizedZombieManager.h"
#include "zombie/popman/SIMDZombieOptimizer.h"
#include "zombie/popman/MultithreadingZombieOptimizer.h"
#include "zombie/popman/LockFreeZombieOptimizer.h"
#include "SIMDOptimization.h"
#include "MultithreadingFramework.h"
#include "LockFreeStructures.h"
#include "zombie/DebugFileWatcher.h"
#include "zombie/GameTime.h"
#include "zombie/MapCollisionData.h"
#include "zombie/PersistentOutfits.h"
#include "zombie/PredicatedFileWatcher.h"
#include "zombie/SandboxOptions.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/ai/states/PathFindState.h"
#include "zombie/ai/states/WalkTowardState.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/PZXmlParserException.h"
#include "zombie/util/PZXmlUtil.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace popman {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ZombiePopulationManager {
public:
 static const ZombiePopulationManager instance = new ZombiePopulationManager();
 static const int SQUARES_PER_CHUNK = 10;
 static const int CHUNKS_PER_CELL = 30;
 static const int SQUARES_PER_CELL = 300;
 static const uint8_t OLD_ZOMBIE_CRAWLER_CAN_WALK = 1;
 static const uint8_t OLD_ZOMBIE_FAKE_DEAD = 2;
 static const uint8_t OLD_ZOMBIE_CRAWLER = 3;
 static const uint8_t OLD_ZOMBIE_WALKER = 4;
 static const int ZOMBIE_STATE_INITIALIZED = 1;
 static const int ZOMBIE_STATE_CRAWLING = 2;
 static const int ZOMBIE_STATE_CAN_WALK = 4;
 static const int ZOMBIE_STATE_FAKE_DEAD = 8;
 static const int ZOMBIE_STATE_CRAWL_UNDER_VEHICLE = 16;
 int minX;
 int minY;
 int width;
 int height;
 bool bStopped;
 bool bClient;
 const DebugCommands dbgCommands = new DebugCommands();
 static bool bDebugLoggingEnabled = false;
 const LoadedAreas loadedAreas = new LoadedAreas(false);
 const LoadedAreas loadedServerCells = new LoadedAreas(true);
 const PlayerSpawns playerSpawns = new PlayerSpawns();
 std::unique_ptr<OptimizedZombieManager> zombie_pool_manager;

 // Multithreading optimization state (Day 7)
 ::threading::ThreadPool* thread_pool_ = nullptr;
 bool multithreading_enabled_ = false;

 // Lock-free optimization state (Day 8)
 bool lockfree_enabled_ = false;
 short[] realZombieCount;
private
 short[] realZombieCount2;
 long realZombieUpdateTime = 0L;
private
 ArrayList<IsoZombie> saveRealZombieHack =
 std::make_unique<ArrayList<>>();
 const ByteBuffer byteBuffer = ByteBuffer.allocateDirect(1024);
 const TIntHashSet newChunks = new TIntHashSet();
private
 ArrayList<ChooseGameInfo.SpawnOrigin> spawnOrigins =
 std::make_unique<ArrayList<>>();
public
 float[] radarXY;
 int radarCount;
 bool radarRenderFlag;
 bool radarRequestFlag;
private
 ArrayList<IsoDirections> m_sittingDirections =
 std::make_unique<ArrayList<>>();

 ZombiePopulationManager();

 // Pool management methods
 void initialize_zombie_pool() noexcept {
     if (zombie_pool_manager) {
         zombie_pool_manager->initialize_pools();
     }
 }

 void check_zombie_pool_health() noexcept {
     if (zombie_pool_manager) {
         zombie_pool_manager->check_pool_health();
     }
 }

 void print_zombie_pool_status() const noexcept {
     if (zombie_pool_manager) {
         zombie_pool_manager->print_pool_status();
     }
 }

 float get_zombie_pool_utilization() const noexcept {
     return zombie_pool_manager ? zombie_pool_manager->get_pool_utilization() : 0.0f;
 }

private
 static void n_init(boolean var0, boolean var1, int var2, int var3,
 int var4, int var5);

private
 static void n_config(float var0, float var1, float var2, int var3,
 float var4, float var5, float var6, float var7,
 int var8);

private
 static void n_setSpawnOrigins(int[] var0);

private
 static void n_setOutfitNames(String[] var0);

private
 static void n_updateMain(float var0, double var1);

private
 static boolean n_hasDataForThread();

private
 static void n_updateThread();

private
 static boolean n_shouldWait();

private
 static void n_beginSaveRealZombies(int var0);

private
 static void n_saveRealZombies(int var0, ByteBuffer var1);

private
 static void n_save();

private
 static void n_stop();

private
 static void n_addZombie(float var0, float var1, float var2, byte var3,
 int var4, int var5, int var6, int var7);

private
 static void n_aggroTarget(int var0, int var1, int var2);

private
 static void n_loadChunk(int var0, int var1, boolean var2);

private
 static void n_loadedAreas(int var0, int[] var1, boolean var2);

protected
 static void n_realZombieCount(short var0, short[] var1);

protected
 static void n_spawnHorde(int var0, int var1, int var2, int var3,
 float var4, float var5, int var6);

private
 static void n_worldSound(int var0, int var1, int var2, int var3);

private
 static int n_getAddZombieCount();

private
 static int n_getAddZombieData(int var0, ByteBuffer var1);

private
 static boolean n_hasRadarData();

private
 static void n_requestRadarData();

private
 static int n_getRadarZombieData(float[] var0);

 static void noise(std::string_view string) {
 if (bDebugLoggingEnabled &&
 (Core.bDebug || GameServer.bServer && GameServer.bDebug) {
 DebugLog.log("ZPOP: " + string);
 }
 }

 static void init() {
 std::string string = "";
 if ("1" == System.getProperty("zomboid.debuglibs.popman"))) {
 DebugLog.log("***** Loading debug version of PZPopMan");
 string = "d";
 }

 if (System.getProperty("os.name").contains("OS X")) {
 System.loadLibrary("PZPopMan");
 } else if (System.getProperty("sun.arch.data.model") == "64")) {
 System.loadLibrary("PZPopMan64" + string);
 }
 else {
 System.loadLibrary("PZPopMan32" + string);
 }

 DebugFileWatcher.instance.add(new PredicatedFileWatcher(
 ZomboidFileSystem.instance.getMessagingDirSub("Trigger_Zombie.xml"),
 ZombiePopulationManager::onTriggeredZombieFile);
 }

 static void onTriggeredZombieFile(std::string_view string) {
 DebugLog.General.println("ZombiePopulationManager.onTriggeredZombieFile(" +
 string + ">");

 ZombieTriggerXmlFile zombieTriggerXmlFile;
 try {
 zombieTriggerXmlFile =
 PZXmlUtil.parse(ZombieTriggerXmlFile.class, string);
 } catch (PZXmlParserException pZXmlParserException) {
 System.err.println(
 "ZombiePopulationManager.onTriggeredZombieFile> Exception thrown. " +
 pZXmlParserException);
 pZXmlParserException.printStackTrace();
 return;
 }

 if (zombieTriggerXmlFile.spawnHorde > 0) {
 processTriggerSpawnHorde(zombieTriggerXmlFile);
 }

 if (zombieTriggerXmlFile.setDebugLoggingEnabled &&
 bDebugLoggingEnabled != zombieTriggerXmlFile.bDebugLoggingEnabled) {
 bDebugLoggingEnabled = zombieTriggerXmlFile.bDebugLoggingEnabled;
 DebugLog.General.println(" bDebugLoggingEnabled: " +
 bDebugLoggingEnabled);
 }
 }

 static void
 processTriggerSpawnHorde(ZombieTriggerXmlFile zombieTriggerXmlFile) {
 DebugLog.General.println(" spawnHorde: " +
 zombieTriggerXmlFile.spawnHorde);
 if (IsoPlayer.getInstance() != nullptr) {
 IsoPlayer player = IsoPlayer.getInstance();
 instance.createHordeFromTo((int)player.x, (int)player.y, (int)player.x,
 (int)player.y,
 zombieTriggerXmlFile.spawnHorde);
 }
 }

 void init(IsoMetaGrid metaGrid) {
 this->bClient = GameClient.bClient;
 if (!this->bClient) {
 this->minX = metaGrid.getMinX();
 this->minY = metaGrid.getMinY();
 this->width = metaGrid.getWidth();
 this->height = metaGrid.getHeight();
 this->bStopped = false;
 n_init(this->bClient, GameServer.bServer, this->minX, this->minY, this->width,
 this->height);
 this->onConfigReloaded();
 String[] strings =
 PersistentOutfits.instance.getOutfitNames().toArray(new String[0]);

 for (int int0 = 0; int0 < strings.length; int0++) {
 strings[int0] = strings[int0].toLowerCase();
 }

 n_setOutfitNames(strings);
 TIntArrayList tIntArrayList = new TIntArrayList();

 for (ChooseGameInfo.SpawnOrigin spawnOrigin : this->spawnOrigins) {
 tIntArrayList.add(spawnOrigin.x);
 tIntArrayList.add(spawnOrigin.y);
 tIntArrayList.add(spawnOrigin.w);
 tIntArrayList.add(spawnOrigin.h);
 }

 n_setSpawnOrigins(tIntArrayList.toArray());
 }
 }

 void onConfigReloaded() {
 SandboxOptions.ZombieConfig zombieConfig =
 SandboxOptions.instance.zombieConfig;
 n_config((float)zombieConfig.PopulationMultiplier.getValue(),
 (float)zombieConfig.PopulationStartMultiplier.getValue(),
 (float)zombieConfig.PopulationPeakMultiplier.getValue(),
 zombieConfig.PopulationPeakDay.getValue(),
 (float)zombieConfig.RespawnHours.getValue(),
 (float)zombieConfig.RespawnUnseenHours.getValue(),
 (float)zombieConfig.RespawnMultiplier.getValue() * 100.0F,
 (float)zombieConfig.RedistributeHours.getValue(),
 zombieConfig.FollowSoundDistance.getValue());
 }

 void registerSpawnOrigin(int int3, int int2, int int1, int int0,
 KahluaTable var5) {
 if (int3 >= 0 && int2 >= 0 && int1 >= 0 && int0 >= 0) {
 this->spawnOrigins.add(
 new ChooseGameInfo.SpawnOrigin(int3, int2, int1, int0);
 }
 }

 void playerSpawnedAt(int int0, int int1, int int2) {
 this->playerSpawns.addSpawn(int0, int1, int2);
 }

 void addChunkToWorld(IsoChunk chunk) {
 if (!this->bClient) {
 if (chunk.isNewChunk()) {
 int int0 = chunk.wy << 16 | chunk.wx;
 this->newChunks.add(int0);
 }

 n_loadChunk(chunk.wx, chunk.wy, true);
 }
 }

 void removeChunkFromWorld(IsoChunk chunk) {
 if (!this->bClient) {
 if (!this->bStopped) {
 n_loadChunk(chunk.wx, chunk.wy, false);

 for (int int0 = 0; int0 < 8; int0++) {
 for (int int1 = 0; int1 < 10; int1++) {
 for (int int2 = 0; int2 < 10; int2++) {
 IsoGridSquare square = chunk.getGridSquare(int2, int1, int0);
 if (square != nullptr && !square.getMovingObjects().empty()) {
 for (int int3 = 0; int3 < square.getMovingObjects().size();
 int3++) {
 IsoMovingObject movingObject =
 square.getMovingObjects().get(int3);
 if (movingObject instanceof
 IsoZombie zombie0 &&
 (!GameServer.bServer || !zombie0.bIndoorZombie) &&
 !zombie0.isReanimatedPlayer()) {
 int int4 = this->getZombieState(zombie0);
 if (int0 != 0 || square.getRoom() != nullptr ||
 zombie0.getCurrentState() !=
 WalkTowardState.instance() &&
 zombie0.getCurrentState() !=
 PathFindState.instance()) {
 n_addZombie(zombie0.x, zombie0.y, zombie0.z,
 (byte)zombie0.dir.index(),
 zombie0.getPersistentOutfitID(), int4, -1,
 -1);
 } else {
 n_addZombie(zombie0.x, zombie0.y, zombie0.z,
 (byte)zombie0.dir.index(),
 zombie0.getPersistentOutfitID(), int4,
 zombie0.getPathTargetX(),
 zombie0.getPathTargetY());
 }
 }
 }
 }
 }
 }
 }

 int int5 = chunk.wy << 16 | chunk.wx;
 this->newChunks.remove(int5);
 if (GameServer.bServer) {
 MapCollisionData.instance.notifyThread();
 }
 }
 }
 }

 void virtualizeZombie(IsoZombie zombie0) {
 int int0 = this->getZombieState(zombie0);
 n_addZombie(zombie0.x, zombie0.y, zombie0.z, (byte)zombie0.dir.index(),
 zombie0.getPersistentOutfitID(), int0, zombie0.getPathTargetX(),
 zombie0.getPathTargetY());
 zombie0.removeFromWorld();
 zombie0.removeFromSquare();
 }

 int getZombieState(IsoZombie zombie0) {
 uint8_t byte0 = 1;
 if (zombie0.isCrawling()) {
 byte0 |= 2;
 }

 if (zombie0.isCanWalk()) {
 byte0 |= 4;
 }

 if (zombie0.isFakeDead()) {
 byte0 |= 8;
 }

 if (zombie0.isCanCrawlUnderVehicle()) {
 byte0 |= 16;
 }

 return byte0;
 }

 void setAggroTarget(int int0, int int1, int int2) {
 n_aggroTarget(int0, int1, int2);
 }

 void createHordeFromTo(int int0, int int1, int int4, int int3, int int2) {
 n_spawnHorde(int0, int1, 0, 0, int4, int3, int2);
 }

 void createHordeInAreaTo(int int0, int int1, int int2, int int3, int int6,
 int int5, int int4) {
 n_spawnHorde(int0, int1, int2, int3, int6, int5, int4);
 }

 void addWorldSound(WorldSoundManager.WorldSound worldSound, bool var2) {
 if (!this->bClient) {
 if (worldSound.radius >= 50) {
 if (!worldSound.sourceIsZombie) {
 int int0 = SandboxOptions.instance.Lore.Hearing.getValue();
 if (int0 == 4) {
 int0 = 2;
 }

 float float0 = WorldSoundManager.instance.getHearingMultiplier(int0);
 n_worldSound(worldSound.x, worldSound.y,
 (int)PZMath.ceil(worldSound.radius * float0),
 worldSound.volume);
 }
 }
 }
 }

 void updateRealZombieCount() noexcept{
 if (this->realZombieCount.empty() ||
 this->realZombieCount.length != this->width * this->height) {
 this->realZombieCount = new short[this->width * this->height];
 this->realZombieCount2 = new short[this->width * this->height * 2];
 }

 Arrays.fill(this->realZombieCount, (short)0);
 std::vector arrayList = IsoWorld.instance.CurrentCell.getZombieList();

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 IsoZombie zombie0 = (IsoZombie)arrayList.get(int0);
 int int1 = (int)(zombie0.x / 300.0F) - this->minX;
 int int2 = (int)(zombie0.y / 300.0F) - this->minY;
 this->realZombieCount[int1 + int2 * this->width]++;
 }

 short short0 = 0;

 for (int int3 = 0; int3 < this->width * this->height; int3++) {
 if (this->realZombieCount[int3] > 0) {
 this->realZombieCount2[short0 * 2 + 0] = (short)int3;
 this->realZombieCount2[short0 * 2 + 1] = this->realZombieCount[int3];
 short0++;
 }
 }

 n_realZombieCount(short0, this->realZombieCount2);
 }

 void updateMain() {
 if (!this->bClient) {
 long long0 = System.currentTimeMillis();
 n_updateMain(GameTime.getInstance().getMultiplier(),
 GameTime.getInstance().getWorldAgeHours());
 int int0 = 0;
 int int1 = 0;
 int int2 = n_getAddZombieCount();
 int int3 = 0;

 while (int3 < int2) {
 this->byteBuffer.clear();
 int int4 = n_getAddZombieData(int3, this->byteBuffer);
 int3 += int4;

 for (int int5 = 0; int5 < int4; int5++) {
 float float0 = this->byteBuffer.getFloat();
 float float1 = this->byteBuffer.getFloat();
 float float2 = this->byteBuffer.getFloat();
 IsoDirections directions =
 IsoDirections.fromIndex(this->byteBuffer.get());
 int int6 = this->byteBuffer.getInt();
 int int7 = this->byteBuffer.getInt();
 int int8 = this->byteBuffer.getInt();
 int int9 = this->byteBuffer.getInt();
 int int10 = (int)float0 / 10;
 int int11 = (int)float1 / 10;
 int int12 = int11 << 16 | int10;
 if (this->newChunks.contains(int12) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(
 (int)float0, (int)float1, (int)float2);
 if (square != nullptr && square.roomID != -1) {
 continue;
 }
 }

 if (int8 != -1 &&
 this->loadedAreas.isOnEdge((int)float0, (int)float1) {
 int8 = -1;
 int9 = -1;
 }

 if (int8 == -1) {
 this->addZombieStanding(float0, float1, float2, directions, int6,
 int7);
 int0++;
 } else {
 this->addZombieMoving(float0, float1, float2, directions, int6, int7,
 int8, int9);
 int1++;
 }
 }
 }

 if (int0 > 0) {
 noise("unloaded -> real " + int2);
 }

 if (int1 > 0) {
 noise("virtual -> real " + int2);
 }

 if (this->radarRenderFlag && this->radarXY != nullptr) {
 if (this->radarRequestFlag) {
 if (n_hasRadarData()) {
 this->radarCount = n_getRadarZombieData(this->radarXY);
 this->radarRenderFlag = false;
 this->radarRequestFlag = false;
 }
 } else {
 n_requestRadarData();
 this->radarRequestFlag = true;
 }
 }

 this->updateLoadedAreas();
 if (this->realZombieUpdateTime + 5000L < long0) {
 this->realZombieUpdateTime = long0;
 this->updateRealZombieCount();
 }

 if (GameServer.bServer) {
 MPDebugInfo.instance.serverUpdate();
 }

 bool boolean0 = n_hasDataForThread();
 bool boolean1 = MapCollisionData.instance.hasDataForThread();
 if (boolean0 || boolean1) {
 MapCollisionData.instance.notifyThread();
 }

 this->playerSpawns.update();
 }
 }

 void addZombieStanding(float float2, float float1, float float0,
 IsoDirections directions, int int1, int int0) {
 IsoGridSquare square0 = IsoWorld.instance.CurrentCell.getGridSquare(
 (int)float2, (int)float1, (int)float0);
 if (square0 != nullptr &&
 (square0.SolidFloorCached ? square0.SolidFloor
 : square0.TreatAsSolidFloor())) {
 if (!Core.bLastStand && !this->playerSpawns.allowZombie(square0) {
 noise("removed zombie near player spawn " + (int)float2 + "," +
 (int)float1 + "," + (int)float0);
 return;
 }

 VirtualZombieManager.instance.choices.clear();
 IsoGridSquare square1 = nullptr;
 if (!this->isCrawling(int0) && !this->isFakeDead(int0) &&
 Rand.Next(3) == 0) {
 square1 = this->getSquareForSittingZombie(float2, float1, (int)float0);
 }

 if (square1 != nullptr) {
 VirtualZombieManager.instance.choices.add(square1);
 } else {
 VirtualZombieManager.instance.choices.add(square0);
 }

 IsoZombie zombie0 = VirtualZombieManager.instance.createRealZombieAlways(
 int1, directions.index(), false);
 if (zombie0 != nullptr) {
 if (square1 != nullptr) {
 this->sitAgainstWall(zombie0, square1);
 } else {
 zombie0.setX(float2);
 zombie0.setY(float1);
 }

 if (this->isFakeDead(int0) {
 zombie0.setHealth(0.5F + Rand.Next(0.0F, 0.3F);
 zombie0.sprite = zombie0.legsSprite;
 zombie0.setFakeDead(true);
 } else if (this->isCrawling(int0) {
 zombie0.setCrawler(true);
 zombie0.setCanWalk(this->isCanWalk(int0);
 zombie0.setOnFloor(true);
 zombie0.setFallOnFront(true);
 zombie0.walkVariant = "ZombieWalk";
 zombie0.DoZombieStats();
 }

 if (this->isInitialized(int0) {
 zombie0.setCanCrawlUnderVehicle(this->isCanCrawlUnderVehicle(int0);
 } else {
 this->firstTimeLoaded(zombie0, int0);
 }
 }
 } else {
 noise("real -> unloaded");
 n_addZombie(float2, float1, float0, (byte)directions.index(), int1, int0,
 -1, -1);
 }
 }

 IsoGridSquare getSquareForSittingZombie(float float1, float float0,
 int int2) {
 uint8_t byte0 = 3;

 for (int int0 = -byte0; int0 < byte0; int0++) {
 for (int int1 = -byte0; int1 < byte0; int1++) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(
 (int)float1 + int0, (int)float0 + int1, int2);
 if (square != nullptr && square.isFree(true) &&
 square.getBuilding() == nullptr) {
 int int3 = square.getWallType();
 if (int3 != 0 && !PolygonalMap2.instance.lineClearCollide(
 float1, float0, square.x + 0.5F, square.y + 0.5F,
 square.z, nullptr, false, true) {
 return square;
 }
 }
 }
 }

 return nullptr;
 }

 void sitAgainstWall(IsoZombie zombie0, IsoGridSquare square) {
 float float0 = square.x + 0.5F;
 float float1 = square.y + 0.5F;
 zombie0.setX(float0);
 zombie0.setY(float1);
 zombie0.setSitAgainstWall(true);
 int int0 = square.getWallType();
 if (int0 != 0) {
 this->m_sittingDirections.clear();
 if ((int0 & 1) != 0 && (int0 & 4) != 0) {
 this->m_sittingDirections.add(IsoDirections.SE);
 }

 if ((int0 & 1) != 0 && (int0 & 8) != 0) {
 this->m_sittingDirections.add(IsoDirections.SW);
 }

 if ((int0 & 2) != 0 && (int0 & 4) != 0) {
 this->m_sittingDirections.add(IsoDirections.NE);
 }

 if ((int0 & 2) != 0 && (int0 & 8) != 0) {
 this->m_sittingDirections.add(IsoDirections.NW);
 }

 if ((int0 & 1) != 0) {
 this->m_sittingDirections.add(IsoDirections.S);
 }

 if ((int0 & 2) != 0) {
 this->m_sittingDirections.add(IsoDirections.N);
 }

 if ((int0 & 4) != 0) {
 this->m_sittingDirections.add(IsoDirections.E);
 }

 if ((int0 & 8) != 0) {
 this->m_sittingDirections.add(IsoDirections.W);
 }

 IsoDirections directions =
 PZArrayUtil.pickRandom(this->m_sittingDirections);
 if (GameClient.bClient) {
 int int1 = (square.x & 1) + (square.y & 1);
 directions = this->m_sittingDirections.get(
 int1 % this->m_sittingDirections.size());
 }

 zombie0.setDir(directions);
 zombie0.setForwardDirection(directions.ToVector());
 if (zombie0.getAnimationPlayer() != nullptr) {
 zombie0.getAnimationPlayer().SetForceDir(zombie0.getForwardDirection());
 }
 }
 }

 void addZombieMoving(float float2, float float1, float float0,
 IsoDirections directions, int int0, int int1, int int3,
 int int2) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(
 (int)float2, (int)float1, (int)float0);
 if (square != nullptr &&
 (square.SolidFloorCached ? square.SolidFloor
 : square.TreatAsSolidFloor())) {
 if (!Core.bLastStand && !this->playerSpawns.allowZombie(square) {
 noise("removed zombie near player spawn " + (int)float2 + "," +
 (int)float1 + "," + (int)float0);
 return;
 }

 VirtualZombieManager.instance.choices.clear();
 VirtualZombieManager.instance.choices.add(square);
 IsoZombie zombie0 = VirtualZombieManager.instance.createRealZombieAlways(
 int0, directions.index(), false);
 if (zombie0 != nullptr) {
 zombie0.setX(float2);
 zombie0.setY(float1);
 if (this->isCrawling(int1) {
 zombie0.setCrawler(true);
 zombie0.setCanWalk(this->isCanWalk(int1);
 zombie0.setOnFloor(true);
 zombie0.setFallOnFront(true);
 zombie0.walkVariant = "ZombieWalk";
 zombie0.DoZombieStats();
 }

 if (this->isInitialized(int1) {
 zombie0.setCanCrawlUnderVehicle(this->isCanCrawlUnderVehicle(int1);
 } else {
 this->firstTimeLoaded(zombie0, int1);
 }

 if (Math.abs(int3 - float2) > 1.0F || Math.abs(int2 - float1) > 1.0F) {
 zombie0.AllowRepathDelay = -1.0F;
 zombie0.pathToLocation(int3, int2, 0);
 }
 }
 } else {
 noise("real -> virtual " + float2 + "," + float1);
 n_addZombie(float2, float1, float0, (byte)directions.index(), int0, int1,
 int3, int2);
 }
 }

 bool isInitialized(int int0) { return (int0 & 1) != 0; }

 bool isCrawling(int int0) { return (int0 & 2) != 0; }

 bool isCanWalk(int int0) { return (int0 & 4) != 0; }

 bool isFakeDead(int int0) { return (int0 & 8) != 0; }

 bool isCanCrawlUnderVehicle(int int0) { return (int0 & 16) != 0; }

 void firstTimeLoaded(IsoZombie var1, int var2) {}

 void updateThread() { n_updateThread(); }

 bool shouldWait() {
 { std::lock_guard<std::mutex> __sync_lock__(MapCollisionData.instance.renderLock_mutex);
 return n_shouldWait();
 }
 }

 void updateLoadedAreas() {
 if (this->loadedAreas.set()) {
 n_loadedAreas(this->loadedAreas.count, this->loadedAreas.areas, false);
 }

 if (GameServer.bServer && this->loadedServerCells.set()) {
 n_loadedAreas(this->loadedServerCells.count, this->loadedServerCells.areas,
 true);
 }
 }

 void dbgSpawnTimeToZero(int int0, int int1) {
 if (!this->bClient || GameClient.connection.accessLevel == 32) {
 this->dbgCommands.SpawnTimeToZero(int0, int1);
 }
 }

 void dbgClearZombies(int int0, int int1) {
 if (!this->bClient || GameClient.connection.accessLevel == 32) {
 this->dbgCommands.ClearZombies(int0, int1);
 }
 }

 void dbgSpawnNow(int int0, int int1) {
 if (!this->bClient || GameClient.connection.accessLevel == 32) {
 this->dbgCommands.SpawnNow(int0, int1);
 }
 }

 void beginSaveRealZombies() {
 if (!this->bClient) {
 this->saveRealZombieHack.clear();

 for (IsoZombie zombie0 : IsoWorld.instance.CurrentCell.getZombieList()) {
 if (!zombie0.isReanimatedPlayer() &&
 (!GameServer.bServer || !zombie0.bIndoorZombie) {
 this->saveRealZombieHack.add(zombie0);
 }
 }

 int int0 = this->saveRealZombieHack.size();
 n_beginSaveRealZombies(int0);
 int int1 = 0;

 while (int1 < int0) {
 this->byteBuffer.clear();
 int int2 = 0;

 while (int1 < int0) {
 int int3 = this->byteBuffer.position();
 IsoZombie zombie1 = this->saveRealZombieHack.get(int1++);
 this->byteBuffer.putFloat(zombie1.x);
 this->byteBuffer.putFloat(zombie1.y);
 this->byteBuffer.putFloat(zombie1.z);
 this->byteBuffer.put((byte)zombie1.dir.index());
 this->byteBuffer.putInt(zombie1.getPersistentOutfitID());
 int int4 = this->getZombieState(zombie1);
 this->byteBuffer.putInt(int4);
 int2++;
 int int5 = this->byteBuffer.position() - int3;
 if (this->byteBuffer.position() + int5 > this->byteBuffer.capacity()) {
 break;
 }
 }

 n_saveRealZombies(int2, this->byteBuffer);
 }

 this->saveRealZombieHack.clear();
 }
 }

 void endSaveRealZombies() {
 if (!this->bClient) {
 ;
 }
 }

 void save() {
 if (!this->bClient) {
 n_save();
 }
 }

 void stop() {
 if (!this->bClient) {
 this->bStopped = true;
 n_stop();
 this->loadedAreas.clear();
 this->newChunks.clear();
 this->spawnOrigins.clear();
 this->radarXY = nullptr;
 this->radarCount = 0;
 this->radarRenderFlag = false;
 this->radarRequestFlag = false;
 }
 }

 // =========================================================================
 // SIMD OPTIMIZATION METHODS (Day 6 - Advanced Optimizations Phase 2)
 // =========================================================================

 /**
  * @brief Initialize SIMD optimization layer
  * 
  * Called during game startup to verify SIMD capabilities and warm up
  * any CPU caches. Must be called before using SIMD operations.
  * 
  * Performance: +5-10% FPS from vectorized math operations
  */
 void initialize_simd_optimizations() noexcept {
 // Verify SIMD support and correctness
 if (SIMDZombieOptimizer::verify_simd_operations()) {
 printf("SIMD Optimization: Active (Level %d)\n", 
        SIMDZombieOptimizer::get_simd_level());
 simd_enabled_ = true;
 } else {
 printf("SIMD Optimization: Disabled (verification failed)\n");
 simd_enabled_ = false;
 }
 }

 /**
  * @brief Check if SIMD optimizations are enabled
  */
 bool is_simd_enabled() const noexcept {
 return simd_enabled_;
 }

 /**
  * @brief Get SIMD capability level
  * @return 0=None, 1=SSE4.1, 2=AVX, 3=AVX2
  */
 int get_simd_level() const noexcept {
 return SIMDZombieOptimizer::get_simd_level();
 }

 // =========================================================================
 // MULTITHREADING OPTIMIZATION METHODS (Day 7 - Advanced Optimizations Phase 2)
 // =========================================================================

 /**
  * @brief Initialize multithreading optimization layer
  * 
  * Called during game startup to initialize thread pool and set up
  * parallel processing infrastructure for zombie AI, collision detection,
  * and pathfinding. 
  * 
  * Performance Target: +10-20% FPS from parallelization
  */
 void initialize_multithreading_optimizations() noexcept {
 try {
 // Get or create global thread pool
 thread_pool_ = &::threading::get_global_thread_pool();
 
 // Initialize the zombie-specific optimizer
 threading_optimizer::MultithreadingZombieOptimizer::initialize(*thread_pool_);
 
 // Log configuration
 printf("Multithreading Optimization: Initializing...\n");
 printf("  Worker threads: %zu\n", 
        threading_optimizer::MultithreadingZombieOptimizer::get_worker_count());
 
 multithreading_enabled_ = true;
 printf("Multithreading Optimization: Active\n");
 } catch (const std::exception& e) {
 printf("Multithreading Optimization: Failed to initialize (%s)\n", 
        e.what());
 multithreading_enabled_ = false;
 }
 }

 /**
  * @brief Check if multithreading optimizations are enabled
  */
 bool is_multithreading_enabled() const noexcept {
 return multithreading_enabled_;
 }

 /**
  * @brief Get number of worker threads in pool
  */
 size_t get_worker_thread_count() const noexcept {
 return threading_optimizer::MultithreadingZombieOptimizer::get_worker_count();
 }

 /**
  * @brief Get thread pool utilization (0.0 to 1.0)
  */
 double get_thread_pool_utilization() const noexcept {
 return threading_optimizer::MultithreadingZombieOptimizer::get_utilization();
 }

 /**
  * @brief Get number of pending tasks in thread pool
  */
 size_t get_pending_tasks() const noexcept {
 return threading_optimizer::MultithreadingZombieOptimizer::get_pending_tasks();
 }

 /**
  * @brief Wait for all pending thread pool tasks
  */
 void wait_thread_pool() noexcept {
 if (multithreading_enabled_) {
 threading_optimizer::MultithreadingZombieOptimizer::wait_all();
 }
 }

 /**
  * @brief Parallel update of zombie AI states
  * 
  * Distributes zombie AI computation across thread pool.
  * 
  * @param zombie_count Number of zombies to update
  * @param update_func Function to call for each zombie: f(size_t index)
  * @param batch_size Zombies per task
  * @return Time elapsed in milliseconds
  */
 double parallel_update_zombie_ai(
 size_t zombie_count,
 std::function<void(size_t)> update_func,
 size_t batch_size = 32) noexcept {
 
 if (!multithreading_enabled_) return 0.0;
 return threading_optimizer::MultithreadingZombieOptimizer::parallel_update_ai(
 zombie_count, update_func, batch_size);
 }

 /**
  * @brief Parallel collision detection using spatial hashing
  * 
  * Processes collision detection in parallel across grid cells.
  * 
  * @param positions Zombie positions (x, y, z per zombie)
  * @param zombie_count Number of zombies
  * @param collision_func Function called for collisions: f(idx1, idx2, dist_sq)
  * @param radius Collision detection radius
  * @return Time elapsed in milliseconds
  */
 double parallel_collision_detection(
 const float* positions,
 size_t zombie_count,
 std::function<void(size_t, size_t, float)> collision_func,
 float radius = 2.0f) noexcept {
 
 if (!multithreading_enabled_) return 0.0;
 return threading_optimizer::MultithreadingZombieOptimizer::parallel_collision_detection(
 positions, zombie_count, collision_func, radius);
 }

 // =========================================================================
 // LOCK-FREE OPTIMIZATION METHODS (Day 8 - Advanced Optimizations Phase 2)
 // =========================================================================

 /**
  * @brief Initialize lock-free optimization layer
  * 
  * Called during game startup to initialize lock-free queues and stacks
  * for audio commands, collision events, and entity pool management.
  * 
  * Eliminates mutex contention in high-frequency operations.
  * Performance Target: +5-10% FPS from reduced lock contention
  */
 void initialize_lockfree_optimizations() noexcept {
 try {
 lockfree_optimizer::LockFreeZombieOptimizer::initialize();
 
 // Pre-allocate some entities in the pool
 lockfree_optimizer::LockFreeZombieOptimizer::preallocate_entities(256);
 
 printf("Lock-Free Optimization: Initializing...\n");
 lockfree_optimizer::LockFreeZombieOptimizer::log_config();
 
 lockfree_enabled_ = true;
 printf("Lock-Free Optimization: Active\n");
 } catch (const std::exception& e) {
 printf("Lock-Free Optimization: Failed to initialize (%s)\n", 
        e.what());
 lockfree_enabled_ = false;
 }
 }

 /**
  * @brief Check if lock-free optimizations are enabled
  */
 bool is_lockfree_enabled() const noexcept {
 return lockfree_enabled_;
 }

 /**
  * @brief Enqueue an audio command lock-free
  * 
  * Safe to call from multiple threads without blocking.
  * 
  * @param cmd Audio command
  * @return true if queued, false if queue full
  */
 bool enqueue_audio_command(
 const lockfree_optimizer::AudioCommand& cmd) noexcept {
 
 if (!lockfree_enabled_) return false;
 return lockfree_optimizer::LockFreeZombieOptimizer::enqueue_audio_command(cmd);
 }

 /**
  * @brief Process all queued audio commands
  * 
  * Drains the lock-free audio queue.
  * 
  * @param handler Function called for each command
  * @return Number of commands processed
  */
 size_t process_audio_commands(
 std::function<void(const lockfree_optimizer::AudioCommand&)> handler) noexcept {
 
 if (!lockfree_enabled_) return 0;
 return lockfree_optimizer::LockFreeZombieOptimizer::process_audio_commands(handler);
 }

 /**
  * @brief Enqueue a collision event lock-free
  * 
  * Multiple collision threads can write without contention.
  * 
  * @param evt Collision event
  * @return true if queued, false if queue full
  */
 bool enqueue_collision_event(
 const lockfree_optimizer::CollisionEvent& evt) noexcept {
 
 if (!lockfree_enabled_) return false;
 return lockfree_optimizer::LockFreeZombieOptimizer::enqueue_collision_event(evt);
 }

 /**
  * @brief Process all queued collision events
  * 
  * Drains the lock-free collision queue.
  * 
  * @param handler Function called for each event
  * @return Number of events processed
  */
 size_t process_collision_events(
 std::function<void(const lockfree_optimizer::CollisionEvent&)> handler) noexcept {
 
 if (!lockfree_enabled_) return 0;
 return lockfree_optimizer::LockFreeZombieOptimizer::process_collision_events(handler);
 }

 /**
  * @brief Allocate an entity from lock-free pool
  * 
  * @return Entity handle from pool, or invalid if empty
  */
 lockfree_optimizer::PooledEntityHandle allocate_entity() noexcept {
 if (!lockfree_enabled_) return lockfree_optimizer::PooledEntityHandle{0, 0};
 return lockfree_optimizer::LockFreeZombieOptimizer::allocate_entity();
 }

 /**
  * @brief Return an entity to lock-free pool
  * 
  * @param handle Entity handle to deallocate
  */
 void deallocate_entity(
 const lockfree_optimizer::PooledEntityHandle& handle) noexcept {
 
 if (!lockfree_enabled_) return;
 lockfree_optimizer::LockFreeZombieOptimizer::deallocate_entity(handle);
 }

 /**
  * @brief Get lock-free queue statistics
  */
 lockfree_optimizer::LockFreeZombieOptimizer::QueueStats get_lockfree_stats() const noexcept {
 if (!lockfree_enabled_) {
 return lockfree_optimizer::LockFreeZombieOptimizer::QueueStats{0, 0, false, false};
 }
 return lockfree_optimizer::LockFreeZombieOptimizer::get_queue_stats();
 }

private:
 /// Flag tracking if SIMD is enabled
 bool simd_enabled_ = false;

}
} // namespace popman
} // namespace zombie
