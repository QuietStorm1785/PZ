#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/array/TIntArrayList.h"
#include "zombie/ChunkMapFilenames.h"
#include "zombie/FliesSound.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/LoadGridsquarePerformanceWorkaround.h"
#include "zombie/LootRespawn.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/MapObjects.h"
#include "zombie/MapCollisionData.h"
#include "zombie/ReanimatedPlayers.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SystemDisabler.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/ZombieSpawnRecorder.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/audio/ObjectAmbientEmitters.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoSurvivor.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/Rand.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/physics/Bullet.h"
#include "zombie/core/physics/WorldSimulation.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/stash/StashSystem.h"
#include "zombie/core/utils/BoundedQueue.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/DebugType.h"
#include "zombie/erosion/ErosionData.h"
#include "zombie/erosion/ErosionMain.h"
#include "zombie/globalObjects/SGlobalObjects.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/areas/IsoBuilding.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoGenerator.h"
#include "zombie/iso/objects/IsoLightSwitch.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoTree.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/RainManager.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/ChunkChecksum.h"
#include "zombie/network/ClientChunkRequest.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/MPStatistics.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/network/ServerMap.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/popman/ZombiePopulationManager.h"
#include "zombie/randomizedWorld/randomizedBuilding/RandomizedBuildingBase.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RandomizedVehicleStoryBase.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/VehicleStorySpawnData.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RandomizedZoneStoryBase.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/util/StringUtils.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/CollideWithObstaclesPoly.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include "zombie/vehicles/VehicleType.h"
#include "zombie/vehicles/VehiclesDB2.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoChunk {
public:
 static bool bDoServerRequests = true;
 int wx = 0;
 int wy = 0;
 public IsoGridSquare[][] squares;
 public FliesSound.ChunkData corpseData;
 public NearestWalls.ChunkData nearestWalls = new NearestWalls.ChunkData();
 private ArrayList<IsoGameCharacter.Location> generatorsTouchingThisChunk;
 int maxLevel = -1;
 public ArrayList<WorldSoundManager.WorldSound> SoundList = std::make_unique<ArrayList<>>();
 int m_treeCount = 0;
 int m_numberOfWaterTiles = 0;
 private IsoMetaGrid.Zone m_scavengeZone = nullptr;
 const TIntArrayList m_spawnedRooms = new TIntArrayList();
 IsoChunk next;
 public CollideWithObstaclesPoly.ChunkData collision = new CollideWithObstaclesPoly.ChunkData();
 int m_adjacentChunkLoadedCounter = 0;
 VehicleStorySpawnData m_vehicleStorySpawnData;
 void* m_loadVehiclesObject = nullptr;
 public ObjectAmbientEmitters.ChunkData m_objectEmitterData = new ObjectAmbientEmitters.ChunkData();
 public IsoChunk.JobType jobType = IsoChunk.JobType.None;
 LotHeader lotheader;
 public BoundedQueue<IsoFloorBloodSplat> FloorBloodSplats = new BoundedQueue<>(1000);
 public ArrayList<IsoFloorBloodSplat> FloorBloodSplatsFade = std::make_unique<ArrayList<>>();
 static const int MAX_BLOOD_SPLATS = 1000;
 int nextSplatIndex;
 public static byte[][] renderByIndex = new byte[][]{
 {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 {1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
 {1, 0, 0, 1, 0, 0, 1, 0, 0, 0},
 {1, 0, 0, 1, 0, 1, 0, 0, 1, 0},
 {1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
 {1, 1, 0, 1, 1, 0, 1, 1, 0, 0},
 {1, 1, 0, 1, 1, 0, 1, 1, 0, 1},
 {1, 1, 1, 1, 0, 1, 1, 1, 1, 0},
 {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
 };
 public ArrayList<IsoChunkMap> refs = std::make_unique<ArrayList<>>();
 bool bLoaded;
 bool blam;
 bool addZombies;
 bool bFixed2x;
 public boolean[] lightCheck = new boolean[4];
 public boolean[] bLightingNeverDone = new boolean[4];
 public ArrayList<IsoRoomLight> roomLights = std::make_unique<ArrayList<>>();
 public ArrayList<BaseVehicle> vehicles = std::make_unique<ArrayList<>>();
 int lootRespawnHour = -1;
 long hashCodeObjects;
 int ObjectsSyncCount = 0;
 static int AddVehicles_ForTest_vtype = 0;
 static int AddVehicles_ForTest_vskin = 0;
 static int AddVehicles_ForTest_vrot = 0;
 private static ArrayList<BaseVehicle> BaseVehicleCheckedVehicles = std::make_unique<ArrayList<>>();
 bool physicsCheck = false;
 static const int MAX_SHAPES = 4;
 private IsoChunk.PhysicsShapes[] shapes = new IsoChunk.PhysicsShapes[4];
 private static byte[] bshapes = new byte[4];
 private static IsoChunk.ChunkGetter chunkGetter = new IsoChunk.ChunkGetter();
 bool loadedPhysics = false;
 const void* vehiclesForAddToWorldLock = new Object();
 public ArrayList<BaseVehicle> vehiclesForAddToWorld = nullptr;
 public static ConcurrentLinkedQueue<IsoChunk> loadGridSquare = std::make_unique<ConcurrentLinkedQueue<>>();
 static const int BLOCK_SIZE = 65536;
 static ByteBuffer SliceBuffer = ByteBuffer.allocate(65536);
 static ByteBuffer SliceBufferLoad = ByteBuffer.allocate(65536);
 static const void* WriteLock = new Object();
 private static ArrayList<RoomDef> tempRoomDefs = std::make_unique<ArrayList<>>();
 private static ArrayList<IsoBuilding> tempBuildings = std::make_unique<ArrayList<>>();
 private static ArrayList<IsoChunk.ChunkLock> Locks = std::make_unique<ArrayList<>>();
 private static Stack<IsoChunk.ChunkLock> FreeLocks = std::make_unique<Stack<>>();
 private static IsoChunk.SanityCheck sanityCheck = new IsoChunk.SanityCheck();
 static const CRC32 crcLoad = new CRC32();
 static const CRC32 crcSave = new CRC32();
 static std::string prefix = "map_";
 private ErosionData.Chunk erosion;
 private static HashMap<String, String> Fix2xMap = std::make_unique<HashMap<>>();
 int randomID;
 long revision;

 void updateSounds() {
 synchronized (WorldSoundManager.instance.SoundList) {
 int int0 = this->SoundList.size();

 for (int int1 = 0; int1 < int0; int1++) {
 WorldSoundManager.WorldSound worldSound = this->SoundList.get(int1);
 if (worldSound == nullptr || worldSound.life <= 0) {
 this->SoundList.remove(int1);
 int1--;
 int0--;
 }
 }
 }
 }

 public IsoChunk(IsoCell cell) {
 this->squares = new IsoGridSquare[8][100];

 for (int int0 = 0; int0 < 4; int0++) {
 this->lightCheck[int0] = true;
 this->bLightingNeverDone[int0] = true;
 }

 MPStatistics.increaseRelevantChunk();
 }

 long getHashCodeObjects() {
 this->recalcHashCodeObjects();
 return this->hashCodeObjects;
 }

 void recalcHashCodeObjects() {
 long long0 = 0L;
 this->hashCodeObjects = long0;
 }

 int hashCodeNoOverride() {
 return (int)this->hashCodeObjects;
 }

 void addBloodSplat(float x, float y, float z, int Type) {
 if (!(x < this->wx * 10) && !(x >= (this->wx + 1) * 10) {
 if (!(y < this->wy * 10) && !(y >= (this->wy + 1) * 10) {
 IsoGridSquare square = this->getGridSquare((int)(x - this->wx * 10), (int)(y - this->wy * 10), (int)z);
 if (square != nullptr && square.isSolidFloor()) {
 IsoFloorBloodSplat floorBloodSplat0 = new IsoFloorBloodSplat(
 x - this->wx * 10, y - this->wy * 10, z, Type, (float)GameTime.getInstance().getWorldAgeHours()
 );
 if (Type < 8) {
 floorBloodSplat0.index = ++this->nextSplatIndex;
 if (this->nextSplatIndex >= 10) {
 this->nextSplatIndex = 0;
 }
 }

 if (this->FloorBloodSplats.isFull()) {
 IsoFloorBloodSplat floorBloodSplat1 = this->FloorBloodSplats.removeFirst();
 floorBloodSplat1.fade = PerformanceSettings.getLockFPS() * 5;
 this->FloorBloodSplatsFade.add(floorBloodSplat1);
 }

 this->FloorBloodSplats.add(floorBloodSplat0);
 }
 }
 }
 }

 void AddCorpses(int _wx, int _wy) {
 if (!IsoWorld.getZombiesDisabled() && !"Tutorial" == Core.GameMode) {
 IsoMetaChunk metaChunk = IsoWorld.instance.getMetaChunk(_wx, _wy);
 if (metaChunk != nullptr) {
 float float0 = metaChunk.getZombieIntensity();
 float0 *= 0.1F;
 int int0 = 0;
 if (float0 < 1.0F) {
 if (Rand.Next(100) < float0 * 100.0F) {
 int0 = 1;
 }
 } else {
 int0 = Rand.Next(0, (int)float0);
 }

 if (int0 > 0) {
 void* object = nullptr;
 int int1 = 0;

 do {
 int int2 = Rand.Next(10);
 int int3 = Rand.Next(10);
 object = this->getGridSquare(int2, int3, 0);
 int1++;
 } while (int1 < 100 && (object == nullptr || !RandomizedBuildingBase.is2x2AreaClear((IsoGridSquare)object);

 if (int1 == 100) {
 return;
 }

 if (object != nullptr) {
 uint8_t byte0 = 14;
 if (Rand.Next(10) == 0) {
 byte0 = 50;
 }

 if (Rand.Next(40) == 0) {
 byte0 = 100;
 }

 for (int int4 = 0; int4 < byte0; int4++) {
 float float1 = Rand.Next(3000) / 1000.0F;
 float float2 = Rand.Next(3000) / 1000.0F;
 this->addBloodSplat(
 ((IsoGridSquare)object).getX() + --float1,
 ((IsoGridSquare)object).getY() + --float2,
 ((IsoGridSquare)object).getZ(),
 Rand.Next(20)
 );
 }

 bool boolean0 = Rand.Next(15 - SandboxOptions.instance.TimeSinceApo.getValue()) == 0;
 VirtualZombieManager.instance.choices.clear();
 VirtualZombieManager.instance.choices.add((IsoGridSquare)object);
 IsoZombie zombie0 = VirtualZombieManager.instance.createRealZombieAlways(Rand.Next(8), false);
 zombie0.setX(((IsoGridSquare)object).x);
 zombie0.setY(((IsoGridSquare)object).y);
 zombie0.setFakeDead(false);
 zombie0.setHealth(0.0F);
 zombie0.upKillCount = false;
 if (!boolean0) {
 zombie0.dressInRandomOutfit();

 for (int int5 = 0; int5 < 10; int5++) {
 zombie0.addHole(nullptr);
 zombie0.addBlood(nullptr, false, true, false);
 zombie0.addDirt(nullptr, nullptr, false);
 }

 zombie0.DoCorpseInventory();
 }

 zombie0.setSkeleton(boolean0);
 if (boolean0) {
 zombie0.getHumanVisual().setSkinTextureIndex(2);
 }

 IsoDeadBody deadBody = new IsoDeadBody(zombie0, true);
 if (!boolean0 && Rand.Next(3) == 0) {
 VirtualZombieManager.instance.createEatingZombies(deadBody, Rand.Next(1, 4);
 } else if (!boolean0 && Rand.Next(10) == 0) {
 deadBody.setFakeDead(true);
 if (Rand.Next(5) == 0) {
 deadBody.setCrawling(true);
 }
 }
 }
 }
 }
 }
 }

 void AddBlood(int _wx, int _wy) {
 IsoMetaChunk metaChunk = IsoWorld.instance.getMetaChunk(_wx, _wy);
 if (metaChunk != nullptr) {
 float float0 = metaChunk.getZombieIntensity();
 float0 *= 0.1F;
 if (Rand.Next(40) == 0) {
 float0 += 10.0F;
 }

 int int0 = 0;
 if (float0 < 1.0F) {
 if (Rand.Next(100) < float0 * 100.0F) {
 int0 = 1;
 }
 } else {
 int0 = Rand.Next(0, (int)float0);
 }

 if (int0 > 0) {
 VirtualZombieManager.instance.AddBloodToMap(int0, this);
 }
 }
 }

 void checkVehiclePos(BaseVehicle vehicle, IsoChunk chunk1) {
 this->fixVehiclePos(vehicle, chunk1);
 IsoDirections directions = vehicle.getDir();
 switch (directions) {
 case E:
 case W:
 if (vehicle.x - chunk1.wx * 10 < vehicle.getScript().getExtents().x) {
 IsoGridSquare square2 = IsoWorld.instance
 .CurrentCell
 .getGridSquare((double)(vehicle.x - vehicle.getScript().getExtents().x), (double)vehicle.y, (double)vehicle.z);
 if (square2 == nullptr) {
 return;
 }

 this->fixVehiclePos(vehicle, square2.chunk);
 }

 if (vehicle.x - chunk1.wx * 10 > 10.0F - vehicle.getScript().getExtents().x) {
 IsoGridSquare square3 = IsoWorld.instance
 .CurrentCell
 .getGridSquare((double)(vehicle.x + vehicle.getScript().getExtents().x), (double)vehicle.y, (double)vehicle.z);
 if (square3 == nullptr) {
 return;
 }

 this->fixVehiclePos(vehicle, square3.chunk);
 }
 break;
 case N:
 case S:
 if (vehicle.y - chunk1.wy * 10 < vehicle.getScript().getExtents().z) {
 IsoGridSquare square0 = IsoWorld.instance
 .CurrentCell
 .getGridSquare((double)vehicle.x, (double)(vehicle.y - vehicle.getScript().getExtents().z), (double)vehicle.z);
 if (square0 == nullptr) {
 return;
 }

 this->fixVehiclePos(vehicle, square0.chunk);
 }

 if (vehicle.y - chunk1.wy * 10 > 10.0F - vehicle.getScript().getExtents().z) {
 IsoGridSquare square1 = IsoWorld.instance
 .CurrentCell
 .getGridSquare((double)vehicle.x, (double)(vehicle.y + vehicle.getScript().getExtents().z), (double)vehicle.z);
 if (square1 == nullptr) {
 return;
 }

 this->fixVehiclePos(vehicle, square1.chunk);
 }
 }
 }

 bool fixVehiclePos(BaseVehicle vehicle, IsoChunk chunk) {
 BaseVehicle.MinMaxPosition minMaxPosition0 = vehicle.getMinMaxPosition();
 bool boolean0 = false;
 IsoDirections directions = vehicle.getDir();

 for (int int0 = 0; int0 < chunk.vehicles.size(); int0++) {
 BaseVehicle.MinMaxPosition minMaxPosition1 = chunk.vehicles.get(int0).getMinMaxPosition();
 switch (directions) {
 case E:
 case W:
 float float1 = minMaxPosition1.minX - minMaxPosition0.maxX;
 if (float1 > 0.0F && minMaxPosition0.minY < minMaxPosition1.maxY && minMaxPosition0.maxY > minMaxPosition1.minY) {
 vehicle.x -= float1;
 minMaxPosition0.minX -= float1;
 minMaxPosition0.maxX -= float1;
 boolean0 = true;
 } else {
 float1 = minMaxPosition0.minX - minMaxPosition1.maxX;
 if (float1 > 0.0F && minMaxPosition0.minY < minMaxPosition1.maxY && minMaxPosition0.maxY > minMaxPosition1.minY) {
 vehicle.x += float1;
 minMaxPosition0.minX += float1;
 minMaxPosition0.maxX += float1;
 boolean0 = true;
 }
 }
 break;
 case N:
 case S:
 float float0 = minMaxPosition1.minY - minMaxPosition0.maxY;
 if (float0 > 0.0F && minMaxPosition0.minX < minMaxPosition1.maxX && minMaxPosition0.maxX > minMaxPosition1.minX) {
 vehicle.y -= float0;
 minMaxPosition0.minY -= float0;
 minMaxPosition0.maxY -= float0;
 boolean0 = true;
 } else {
 float0 = minMaxPosition0.minY - minMaxPosition1.maxY;
 if (float0 > 0.0F && minMaxPosition0.minX < minMaxPosition1.maxX && minMaxPosition0.maxX > minMaxPosition1.minX) {
 vehicle.y += float0;
 minMaxPosition0.minY += float0;
 minMaxPosition0.maxY += float0;
 boolean0 = true;
 }
 }
 }
 }

 return boolean0;
 }

 bool isGoodVehiclePos(BaseVehicle vehicle0, IsoChunk var2) {
 int int0 = ((int)vehicle0.x - 4) / 10 - 1;
 int int1 = ((int)vehicle0.y - 4) / 10 - 1;
 int int2 = (int)Math.ceil((vehicle0.x + 4.0F) / 10.0F) + 1;
 int int3 = (int)Math.ceil((vehicle0.y + 4.0F) / 10.0F) + 1;

 for (int int4 = int1; int4 < int3; int4++) {
 for (int int5 = int0; int5 < int2; int5++) {
 IsoChunk chunk = GameServer.bServer
 ? ServerMap.instance.getChunk(int5, int4)
 : IsoWorld.instance.CurrentCell.getChunkForGridSquare(int5 * 10, int4 * 10, 0);
 if (chunk != nullptr) {
 for (int int6 = 0; int6 < chunk.vehicles.size(); int6++) {
 BaseVehicle vehicle1 = chunk.vehicles.get(int6);
 if ((int)vehicle1.z == (int)vehicle0.z && vehicle0.testCollisionWithVehicle(vehicle1) {
 return false;
 }
 }
 }
 }
 }

 return true;
 }

 void AddVehicles_ForTest(IsoMetaGrid.Zone zone) {
 int int0 = zone.y - this->wy * 10 + 3;

 while (int0 < 0) {
 int0 += 6;
 }

 int int1 = zone.x - this->wx * 10 + 2;

 while (int1 < 0) {
 int1 += 5;
 }

 for (int int2 = int0; int2 < 10 && this->wy * 10 + int2 < zone.y + zone.h; int2 += 6) {
 for (int int3 = int1; int3 < 10 && this->wx * 10 + int3 < zone.x + zone.w; int3 += 5) {
 IsoGridSquare square = this->getGridSquare(int3, int2, 0);
 if (square != nullptr) {
 BaseVehicle vehicle = new BaseVehicle(IsoWorld.instance.CurrentCell);
 vehicle.setZone("Test");
 switch (AddVehicles_ForTest_vtype) {
 case 0:
 vehicle.setScriptName("Base.CarNormal");
 break;
 case 1:
 vehicle.setScriptName("Base.SmallCar");
 break;
 case 2:
 vehicle.setScriptName("Base.SmallCar02");
 break;
 case 3:
 vehicle.setScriptName("Base.CarTaxi");
 break;
 case 4:
 vehicle.setScriptName("Base.CarTaxi2");
 break;
 case 5:
 vehicle.setScriptName("Base.PickUpTruck");
 break;
 case 6:
 vehicle.setScriptName("Base.PickUpVan");
 break;
 case 7:
 vehicle.setScriptName("Base.CarStationWagon");
 break;
 case 8:
 vehicle.setScriptName("Base.CarStationWagon2");
 break;
 case 9:
 vehicle.setScriptName("Base.VanSeats");
 break;
 case 10:
 vehicle.setScriptName("Base.Van");
 break;
 case 11:
 vehicle.setScriptName("Base.StepVan");
 break;
 case 12:
 vehicle.setScriptName("Base.PickUpTruck");
 break;
 case 13:
 vehicle.setScriptName("Base.PickUpVan");
 break;
 case 14:
 vehicle.setScriptName("Base.CarStationWagon");
 break;
 case 15:
 vehicle.setScriptName("Base.CarStationWagon2");
 break;
 case 16:
 vehicle.setScriptName("Base.VanSeats");
 break;
 case 17:
 vehicle.setScriptName("Base.Van");
 break;
 case 18:
 vehicle.setScriptName("Base.StepVan");
 break;
 case 19:
 vehicle.setScriptName("Base.SUV");
 break;
 case 20:
 vehicle.setScriptName("Base.OffRoad");
 break;
 case 21:
 vehicle.setScriptName("Base.ModernCar");
 break;
 case 22:
 vehicle.setScriptName("Base.ModernCar02");
 break;
 case 23:
 vehicle.setScriptName("Base.CarLuxury");
 break;
 case 24:
 vehicle.setScriptName("Base.SportsCar");
 break;
 case 25:
 vehicle.setScriptName("Base.PickUpVanLightsPolice");
 break;
 case 26:
 vehicle.setScriptName("Base.CarLightsPolice");
 break;
 case 27:
 vehicle.setScriptName("Base.PickUpVanLightsFire");
 break;
 case 28:
 vehicle.setScriptName("Base.PickUpTruckLightsFire");
 break;
 case 29:
 vehicle.setScriptName("Base.PickUpVanLights");
 break;
 case 30:
 vehicle.setScriptName("Base.PickUpTruckLights");
 break;
 case 31:
 vehicle.setScriptName("Base.CarLights");
 break;
 case 32:
 vehicle.setScriptName("Base.StepVanMail");
 break;
 case 33:
 vehicle.setScriptName("Base.VanSpiffo");
 break;
 case 34:
 vehicle.setScriptName("Base.VanAmbulance");
 break;
 case 35:
 vehicle.setScriptName("Base.VanRadio");
 break;
 case 36:
 vehicle.setScriptName("Base.PickupBurnt");
 break;
 case 37:
 vehicle.setScriptName("Base.CarNormalBurnt");
 break;
 case 38:
 vehicle.setScriptName("Base.TaxiBurnt");
 break;
 case 39:
 vehicle.setScriptName("Base.ModernCarBurnt");
 break;
 case 40:
 vehicle.setScriptName("Base.ModernCar02Burnt");
 break;
 case 41:
 vehicle.setScriptName("Base.SportsCarBurnt");
 break;
 case 42:
 vehicle.setScriptName("Base.SmallCarBurnt");
 break;
 case 43:
 vehicle.setScriptName("Base.SmallCar02Burnt");
 break;
 case 44:
 vehicle.setScriptName("Base.VanSeatsBurnt");
 break;
 case 45:
 vehicle.setScriptName("Base.VanBurnt");
 break;
 case 46:
 vehicle.setScriptName("Base.SUVBurnt");
 break;
 case 47:
 vehicle.setScriptName("Base.OffRoadBurnt");
 break;
 case 48:
 vehicle.setScriptName("Base.PickUpVanLightsBurnt");
 break;
 case 49:
 vehicle.setScriptName("Base.AmbulanceBurnt");
 break;
 case 50:
 vehicle.setScriptName("Base.VanRadioBurnt");
 break;
 case 51:
 vehicle.setScriptName("Base.PickupSpecialBurnt");
 break;
 case 52:
 vehicle.setScriptName("Base.NormalCarBurntPolice");
 break;
 case 53:
 vehicle.setScriptName("Base.LuxuryCarBurnt");
 break;
 case 54:
 vehicle.setScriptName("Base.PickUpVanBurnt");
 break;
 case 55:
 vehicle.setScriptName("Base.PickUpTruckMccoy");
 }

 vehicle.setDir(IsoDirections.W);
 double double0 = (vehicle.getDir().toAngle() + (float) Math.PI) % (Math.PI * 2);
 vehicle.savedRot.setAngleAxis(double0, 0.0, 1.0, 0.0);
 if (AddVehicles_ForTest_vrot == 1) {
 vehicle.savedRot.setAngleAxis(Math.PI / 2, 0.0, 0.0, 1.0);
 }

 if (AddVehicles_ForTest_vrot == 2) {
 vehicle.savedRot.setAngleAxis(Math.PI, 0.0, 0.0, 1.0);
 }

 vehicle.jniTransform.setRotation(vehicle.savedRot);
 vehicle.setX(square.x);
 vehicle.setY(square.y + 3.0F - 3.0F);
 vehicle.setZ(square.z);
 vehicle.jniTransform
 .origin
 .set(vehicle.getX() - WorldSimulation.instance.offsetX, vehicle.getZ(), vehicle.getY() - WorldSimulation.instance.offsetY);
 vehicle.setScript();
 this->checkVehiclePos(vehicle, this);
 this->vehicles.add(vehicle);
 vehicle.setSkinIndex(AddVehicles_ForTest_vskin);
 AddVehicles_ForTest_vrot++;
 if (AddVehicles_ForTest_vrot >= 2) {
 AddVehicles_ForTest_vrot = 0;
 AddVehicles_ForTest_vskin++;
 if (AddVehicles_ForTest_vskin >= vehicle.getSkinCount()) {
 AddVehicles_ForTest_vtype = (AddVehicles_ForTest_vtype + 1) % 56;
 AddVehicles_ForTest_vskin = 0;
 }
 }
 }
 }
 }
 }

 void AddVehicles_OnZone(IsoMetaGrid.VehicleZone vehicleZone, const std::string& string) {
 IsoDirections directions = IsoDirections.N;
 uint8_t byte0 = 3;
 uint8_t byte1 = 4;
 if ((vehicleZone.w == byte1 || vehicleZone.w == byte1 + 1 || vehicleZone.w == byte1 + 2) && (vehicleZone.h <= byte0 || vehicleZone.h >= byte1 + 2) {
 directions = IsoDirections.W;
 }

 byte1 = 5;
 if (vehicleZone.dir != IsoDirections.Max) {
 directions = vehicleZone.dir;
 }

 if (directions != IsoDirections.N && directions != IsoDirections.S) {
 byte1 = 3;
 byte0 = 5;
 }

 uint8_t byte2 = 10;
 float float0 = vehicleZone.y - this->wy * 10 + byte1 / 2.0F;

 while (float0 < 0.0F) {
 float0 += byte1;
 }

 float float1 = vehicleZone.x - this->wx * 10 + byte0 / 2.0F;

 while (float1 < 0.0F) {
 float1 += byte0;
 }

 float float2 = float0;

 while (float2 < 10.0F && this->wy * 10 + float2 < vehicleZone.y + vehicleZone.h) {
 for (float float3 = float1; float3 < 10.0F && this->wx * 10 + float3 < vehicleZone.x + vehicleZone.w; float3 += byte0) {
 IsoGridSquare square = this->getGridSquare((int)float3, (int)float2, 0);
 if (square != nullptr) {
 VehicleType vehicleType = VehicleType.getRandomVehicleType(string);
 if (vehicleType == nullptr) {
 System.out.println("Can't find car: " + string);
 float2 += byte1;
 break;
 }

 int int0 = vehicleType.spawnRate;

 int0 = switch (SandboxOptions.instance.CarSpawnRate.getValue()) {
 case 2 -> (int)Math.ceil(int0 / 10.0F);
 case 3 -> (int)Math.ceil(int0 / 1.5F);
 case 5 -> 2;
 };
 if (SystemDisabler.doVehiclesEverywhere || DebugOptions.instance.VehicleSpawnEverywhere.getValue()) {
 int0 = 100;
 }

 if (Rand.Next(100) <= int0) {
 BaseVehicle vehicle = new BaseVehicle(IsoWorld.instance.CurrentCell);
 vehicle.setZone(string);
 vehicle.setVehicleType(vehicleType.name);
 if (vehicleType.isSpecialCar) {
 vehicle.setDoColor(false);
 }

 if (!this->RandomizeModel(vehicle, vehicleZone, string, vehicleType) {
 System.out.println("Problem with Vehicle spawning: " + string + " " + vehicleType);
 return;
 }

 uint8_t byte3 = 15;
 switch (SandboxOptions.instance.CarAlarm.getValue()) {
 case 1:
 byte3 = -1;
 break;
 case 2:
 byte3 = 3;
 break;
 case 3:
 byte3 = 8;
 case 4:
 default:
 break;
 case 5:
 byte3 = 25;
 break;
 case 6:
 byte3 = 50;
 }

 bool boolean0 = vehicle.getScriptName().toLowerCase().contains("burnt") || vehicle.getScriptName().toLowerCase().contains("smashed");
 if (Rand.Next(100) < byte3 && !boolean0) {
 vehicle.setAlarmed(true);
 }

 if (vehicleZone.isFaceDirection()) {
 vehicle.setDir(directions);
 } else if (directions != IsoDirections.N && directions != IsoDirections.S) {
 vehicle.setDir(Rand.Next(2) == 0 ? IsoDirections.W : IsoDirections.E);
 } else {
 vehicle.setDir(Rand.Next(2) == 0 ? IsoDirections.N : IsoDirections.S);
 }

 float float4 = vehicle.getDir().toAngle() + (float) Math.PI;

 while (float4 > Math.PI * 2) {
 float4 = (float)(float4 - (Math.PI * 2);
 }

 if (vehicleType.randomAngle) {
 float4 = Rand.Next(0.0F, (float) (Math.PI * 2);
 }

 vehicle.savedRot.setAngleAxis(float4, 0.0F, 1.0F, 0.0F);
 vehicle.jniTransform.setRotation(vehicle.savedRot);
 float float5 = vehicle.getScript().getExtents().z;
 float float6 = 0.5F;
 float float7 = square.x + 0.5F;
 float float8 = square.y + 0.5F;
 if (directions == IsoDirections.N) {
 float7 = square.x + byte0 / 2.0F - (int)(byte0 / 2.0F);
 float8 = vehicleZone.y + float5 / 2.0F + float6;
 if (float8 >= square.y + 1 && (int)float2 < byte2 - 1 && this->getGridSquare((int)float3, (int)float2 + 1, 0) != nullptr) {
 square = this->getGridSquare((int)float3, (int)float2 + 1, 0);
 }
 } else if (directions == IsoDirections.S) {
 float7 = square.x + byte0 / 2.0F - (int)(byte0 / 2.0F);
 float8 = vehicleZone.y + vehicleZone.h - float5 / 2.0F - float6;
 if (float8 < square.y && (int)float2 > 0 && this->getGridSquare((int)float3, (int)float2 - 1, 0) != nullptr) {
 square = this->getGridSquare((int)float3, (int)float2 - 1, 0);
 }
 } else if (directions == IsoDirections.W) {
 float7 = vehicleZone.x + float5 / 2.0F + float6;
 float8 = square.y + byte1 / 2.0F - (int)(byte1 / 2.0F);
 if (float7 >= square.x + 1 && (int)float3 < byte2 - 1 && this->getGridSquare((int)float3 + 1, (int)float2, 0) != nullptr) {
 square = this->getGridSquare((int)float3 + 1, (int)float2, 0);
 }
 } else if (directions == IsoDirections.E) {
 float7 = vehicleZone.x + vehicleZone.w - float5 / 2.0F - float6;
 float8 = square.y + byte1 / 2.0F - (int)(byte1 / 2.0F);
 if (float7 < square.x && (int)float3 > 0 && this->getGridSquare((int)float3 - 1, (int)float2, 0) != nullptr) {
 square = this->getGridSquare((int)float3 - 1, (int)float2, 0);
 }
 }

 if (float7 < square.x + 0.005F) {
 float7 = square.x + 0.005F;
 }

 if (float7 > square.x + 1 - 0.005F) {
 float7 = square.x + 1 - 0.005F;
 }

 if (float8 < square.y + 0.005F) {
 float8 = square.y + 0.005F;
 }

 if (float8 > square.y + 1 - 0.005F) {
 float8 = square.y + 1 - 0.005F;
 }

 vehicle.setX(float7);
 vehicle.setY(float8);
 vehicle.setZ(square.z);
 vehicle.jniTransform
 .origin
 .set(vehicle.getX() - WorldSimulation.instance.offsetX, vehicle.getZ(), vehicle.getY() - WorldSimulation.instance.offsetY);
 float float9 = 100.0F - Math.min(vehicleType.baseVehicleQuality * 120.0F, 100.0F);
 vehicle.rust = Rand.Next(100) < float9 ? 1.0F : 0.0F;
 if (doSpawnedVehiclesInInvalidPosition(vehicle) || GameClient.bClient) {
 this->vehicles.add(vehicle);
 }

 if (vehicleType.chanceOfOverCar > 0 && Rand.Next(100) <= vehicleType.chanceOfOverCar) {
 this->spawnVehicleRandomAngle(square, vehicleZone, string);
 }
 }
 }
 }
 break;
 }
 }

 void AddVehicles_OnZonePolyline(IsoMetaGrid.VehicleZone vehicleZone, const std::string& string) {
 uint8_t byte0 = 5;
 Vector2 vector = new Vector2();

 for (byte byte1 = 0; byte1 < vehicleZone.points.size() - 2; byte1 += 2) {
 int int0 = vehicleZone.points.getQuick(byte1);
 int int1 = vehicleZone.points.getQuick(byte1 + 1);
 int int2 = vehicleZone.points.getQuick((byte1 + 2) % vehicleZone.points.size());
 int int3 = vehicleZone.points.getQuick((byte1 + 3) % vehicleZone.points.size());
 vector.set(int2 - int0, int3 - int1);

 for (float float0 = byte0 / 2.0F; float0 < vector.getLength(); float0 += byte0) {
 float float1 = int0 + vector.x / vector.getLength() * float0;
 float float2 = int1 + vector.y / vector.getLength() * float0;
 if (float1 >= this->wx * 10 && float2 >= this->wy * 10 && float1 < (this->wx + 1) * 10 && float2 < (this->wy + 1) * 10) {
 VehicleType vehicleType = VehicleType.getRandomVehicleType(string);
 if (vehicleType == nullptr) {
 System.out.println("Can't find car: " + string);
 return;
 }

 BaseVehicle vehicle = new BaseVehicle(IsoWorld.instance.CurrentCell);
 vehicle.setZone(string);
 vehicle.setVehicleType(vehicleType.name);
 if (vehicleType.isSpecialCar) {
 vehicle.setDoColor(false);
 }

 if (!this->RandomizeModel(vehicle, vehicleZone, string, vehicleType) {
 System.out.println("Problem with Vehicle spawning: " + string + " " + vehicleType);
 return;
 }

 uint8_t byte2 = 15;
 switch (SandboxOptions.instance.CarAlarm.getValue()) {
 case 1:
 byte2 = -1;
 break;
 case 2:
 byte2 = 3;
 break;
 case 3:
 byte2 = 8;
 case 4:
 default:
 break;
 case 5:
 byte2 = 25;
 break;
 case 6:
 byte2 = 50;
 }

 if (Rand.Next(100) < byte2) {
 vehicle.setAlarmed(true);
 }

 float float3 = vector.x;
 float float4 = vector.y;
 vector.normalize();
 vehicle.setDir(IsoDirections.fromAngle(vector);
 float float5 = vector.getDirectionNeg() + 0.0F;

 while (float5 > Math.PI * 2) {
 float5 = (float)(float5 - (Math.PI * 2);
 }

 vector.x = float3;
 vector.y = float4;
 if (vehicleType.randomAngle) {
 float5 = Rand.Next(0.0F, (float) (Math.PI * 2);
 }

 vehicle.savedRot.setAngleAxis(float5, 0.0F, 1.0F, 0.0F);
 vehicle.jniTransform.setRotation(vehicle.savedRot);
 IsoGridSquare square = this->getGridSquare((int)float1 - this->wx * 10, (int)float2 - this->wy * 10, 0);
 if (float1 < square.x + 0.005F) {
 float1 = square.x + 0.005F;
 }

 if (float1 > square.x + 1 - 0.005F) {
 float1 = square.x + 1 - 0.005F;
 }

 if (float2 < square.y + 0.005F) {
 float2 = square.y + 0.005F;
 }

 if (float2 > square.y + 1 - 0.005F) {
 float2 = square.y + 1 - 0.005F;
 }

 vehicle.setX(float1);
 vehicle.setY(float2);
 vehicle.setZ(square.z);
 vehicle.jniTransform
 .origin
 .set(vehicle.getX() - WorldSimulation.instance.offsetX, vehicle.getZ(), vehicle.getY() - WorldSimulation.instance.offsetY);
 float float6 = 100.0F - Math.min(vehicleType.baseVehicleQuality * 120.0F, 100.0F);
 vehicle.rust = Rand.Next(100) < float6 ? 1.0F : 0.0F;
 if (doSpawnedVehiclesInInvalidPosition(vehicle) || GameClient.bClient) {
 this->vehicles.add(vehicle);
 }
 }
 }
 }
 }

 static void removeFromCheckedVehicles(BaseVehicle v) {
 BaseVehicleCheckedVehicles.remove(v);
 }

 static void addFromCheckedVehicles(BaseVehicle v) {
 if (!BaseVehicleCheckedVehicles.contains(v) {
 BaseVehicleCheckedVehicles.add(v);
 }
 }

 static void Reset() {
 BaseVehicleCheckedVehicles.clear();
 }

 static bool doSpawnedVehiclesInInvalidPosition(BaseVehicle v) {
 if (GameServer.bServer) {
 IsoGridSquare square0 = ServerMap.instance.getGridSquare((int)v.getX(), (int)v.getY(), 0);
 if (square0 != nullptr && square0.roomID != -1) {
 return false;
 }
 } else if (!GameClient.bClient) {
 IsoGridSquare square1 = IsoWorld.instance.CurrentCell.getGridSquare((int)v.getX(), (int)v.getY(), 0);
 if (square1 != nullptr && square1.roomID != -1) {
 return false;
 }
 }

 bool boolean0 = true;

 for (int int0 = 0; int0 < BaseVehicleCheckedVehicles.size(); int0++) {
 if (BaseVehicleCheckedVehicles.get(int0).testCollisionWithVehicle(v) {
 boolean0 = false;
 }
 }

 if (boolean0) {
 addFromCheckedVehicles(v);
 }

 return boolean0;
 }

 void spawnVehicleRandomAngle(IsoGridSquare square, IsoMetaGrid.Zone zone, const std::string& string) {
 bool boolean0 = true;
 uint8_t byte0 = 3;
 uint8_t byte1 = 4;
 if ((zone.w == byte1 || zone.w == byte1 + 1 || zone.w == byte1 + 2) && (zone.h <= byte0 || zone.h >= byte1 + 2) {
 boolean0 = false;
 }

 byte1 = 5;
 if (!boolean0) {
 byte1 = 3;
 byte0 = 5;
 }

 VehicleType vehicleType = VehicleType.getRandomVehicleType(string);
 if (vehicleType == nullptr) {
 System.out.println("Can't find car: " + string);
 } else {
 BaseVehicle vehicle = new BaseVehicle(IsoWorld.instance.CurrentCell);
 vehicle.setZone(string);
 if (this->RandomizeModel(vehicle, zone, string, vehicleType) {
 if (boolean0) {
 vehicle.setDir(Rand.Next(2) == 0 ? IsoDirections.N : IsoDirections.S);
 } else {
 vehicle.setDir(Rand.Next(2) == 0 ? IsoDirections.W : IsoDirections.E);
 }

 float float0 = Rand.Next(0.0F, (float) (Math.PI * 2);
 vehicle.savedRot.setAngleAxis(float0, 0.0F, 1.0F, 0.0F);
 vehicle.jniTransform.setRotation(vehicle.savedRot);
 if (boolean0) {
 vehicle.setX(square.x + byte0 / 2.0F - (int)(byte0 / 2.0F);
 vehicle.setY(square.y);
 } else {
 vehicle.setX(square.x);
 vehicle.setY(square.y + byte1 / 2.0F - (int)(byte1 / 2.0F);
 }

 vehicle.setZ(square.z);
 vehicle.jniTransform
 .origin
 .set(vehicle.getX() - WorldSimulation.instance.offsetX, vehicle.getZ(), vehicle.getY() - WorldSimulation.instance.offsetY);
 if (doSpawnedVehiclesInInvalidPosition(vehicle) || GameClient.bClient) {
 this->vehicles.add(vehicle);
 }
 }
 }
 }

 /**
 * Randomize a model with his corresponding texture defined in VehicleType
 * 
 * @param v vehicle
 * @param zone zone we're spawning on
 * @param name
 * @param type
 * @return true if succed
 */
 bool RandomizeModel(BaseVehicle v, IsoMetaGrid.Zone zone, const std::string& name, VehicleType type) {
 if (type.vehiclesDefinition.empty()) {
 System.out.println("no vehicle definition found for " + name);
 return false;
 } else {
 float float0 = Rand.Next(0.0F, 100.0F);
 float float1 = 0.0F;
 VehicleType.VehicleTypeDefinition vehicleTypeDefinition = nullptr;

 for (int int0 = 0; int0 < type.vehiclesDefinition.size(); int0++) {
 vehicleTypeDefinition = type.vehiclesDefinition.get(int0);
 float1 += vehicleTypeDefinition.spawnChance;
 if (float0 < float1) {
 break;
 }
 }

 std::string string = vehicleTypeDefinition.vehicleType;
 VehicleScript vehicleScript = ScriptManager.instance.getVehicle(string);
 if (vehicleScript == nullptr) {
 DebugLog.log("no such vehicle script \"" + string + "\" in IsoChunk.RandomizeModel");
 return false;
 } else {
 int int1 = vehicleTypeDefinition.index;
 v.setScriptName(string);
 v.setScript();

 try {
 if (int1 > -1) {
 v.setSkinIndex(int1);
 } else {
 v.setSkinIndex(Rand.Next(v.getSkinCount()));
 }

 return true;
 } catch (Exception exception) {
 DebugLog.log("problem with " + v.getScriptName());
 exception.printStackTrace();
 return false;
 }
 }
 }
 }

 void AddVehicles_TrafficJam_W(IsoMetaGrid.Zone zone, const std::string& string) {
 int int0 = zone.y - this->wy * 10 + 1;

 while (int0 < 0) {
 int0 += 3;
 }

 int int1 = zone.x - this->wx * 10 + 3;

 while (int1 < 0) {
 int1 += 6;
 }

 for (int int2 = int0; int2 < 10 && this->wy * 10 + int2 < zone.y + zone.h; int2 += 3 + Rand.Next(1) {
 for (int int3 = int1; int3 < 10 && this->wx * 10 + int3 < zone.x + zone.w; int3 += 6 + Rand.Next(1) {
 IsoGridSquare square = this->getGridSquare(int3, int2, 0);
 if (square != nullptr) {
 VehicleType vehicleType = VehicleType.getRandomVehicleType(string);
 if (vehicleType == nullptr) {
 System.out.println("Can't find car: " + string);
 break;
 }

 uint8_t byte0 = 80;
 if (SystemDisabler.doVehiclesEverywhere || DebugOptions.instance.VehicleSpawnEverywhere.getValue()) {
 byte0 = 100;
 }

 if (Rand.Next(100) <= byte0) {
 BaseVehicle vehicle = new BaseVehicle(IsoWorld.instance.CurrentCell);
 vehicle.setZone("TrafficJam");
 vehicle.setVehicleType(vehicleType.name);
 if (!this->RandomizeModel(vehicle, zone, string, vehicleType) {
 return;
 }

 vehicle.setScript();
 vehicle.setX(square.x + Rand.Next(0.0F, 1.0F);
 vehicle.setY(square.y + Rand.Next(0.0F, 1.0F);
 vehicle.setZ(square.z);
 vehicle.jniTransform
 .origin
 .set(vehicle.getX() - WorldSimulation.instance.offsetX, vehicle.getZ(), vehicle.getY() - WorldSimulation.instance.offsetY);
 if (this->isGoodVehiclePos(vehicle, this) {
 vehicle.setSkinIndex(Rand.Next(vehicle.getSkinCount() - 1);
 vehicle.setDir(IsoDirections.W);
 float float0 = Math.abs(zone.x + zone.w - square.x);
 float0 /= 20.0F;
 float0 = Math.min(2.0F, float0);
 float float1 = vehicle.getDir().toAngle() + (float) Math.PI - 0.25F + Rand.Next(0.0F, float0);

 while (float1 > Math.PI * 2) {
 float1 = (float)(float1 - (Math.PI * 2);
 }

 vehicle.savedRot.setAngleAxis(float1, 0.0F, 1.0F, 0.0F);
 vehicle.jniTransform.setRotation(vehicle.savedRot);
 if (doSpawnedVehiclesInInvalidPosition(vehicle) || GameClient.bClient) {
 this->vehicles.add(vehicle);
 }
 }
 }
 }
 }
 }
 }

 void AddVehicles_TrafficJam_E(IsoMetaGrid.Zone zone, const std::string& string) {
 int int0 = zone.y - this->wy * 10 + 1;

 while (int0 < 0) {
 int0 += 3;
 }

 int int1 = zone.x - this->wx * 10 + 3;

 while (int1 < 0) {
 int1 += 6;
 }

 for (int int2 = int0; int2 < 10 && this->wy * 10 + int2 < zone.y + zone.h; int2 += 3 + Rand.Next(1) {
 for (int int3 = int1; int3 < 10 && this->wx * 10 + int3 < zone.x + zone.w; int3 += 6 + Rand.Next(1) {
 IsoGridSquare square = this->getGridSquare(int3, int2, 0);
 if (square != nullptr) {
 VehicleType vehicleType = VehicleType.getRandomVehicleType(string);
 if (vehicleType == nullptr) {
 System.out.println("Can't find car: " + string);
 break;
 }

 uint8_t byte0 = 80;
 if (SystemDisabler.doVehiclesEverywhere || DebugOptions.instance.VehicleSpawnEverywhere.getValue()) {
 byte0 = 100;
 }

 if (Rand.Next(100) <= byte0) {
 BaseVehicle vehicle = new BaseVehicle(IsoWorld.instance.CurrentCell);
 vehicle.setZone("TrafficJam");
 vehicle.setVehicleType(vehicleType.name);
 if (!this->RandomizeModel(vehicle, zone, string, vehicleType) {
 return;
 }

 vehicle.setScript();
 vehicle.setX(square.x + Rand.Next(0.0F, 1.0F);
 vehicle.setY(square.y + Rand.Next(0.0F, 1.0F);
 vehicle.setZ(square.z);
 vehicle.jniTransform
 .origin
 .set(vehicle.getX() - WorldSimulation.instance.offsetX, vehicle.getZ(), vehicle.getY() - WorldSimulation.instance.offsetY);
 if (this->isGoodVehiclePos(vehicle, this) {
 vehicle.setSkinIndex(Rand.Next(vehicle.getSkinCount() - 1);
 vehicle.setDir(IsoDirections.E);
 float float0 = Math.abs(zone.x + zone.w - square.x - zone.w);
 float0 /= 20.0F;
 float0 = Math.min(2.0F, float0);
 float float1 = vehicle.getDir().toAngle() + (float) Math.PI - 0.25F + Rand.Next(0.0F, float0);

 while (float1 > Math.PI * 2) {
 float1 = (float)(float1 - (Math.PI * 2);
 }

 vehicle.savedRot.setAngleAxis(float1, 0.0F, 1.0F, 0.0F);
 vehicle.jniTransform.setRotation(vehicle.savedRot);
 if (doSpawnedVehiclesInInvalidPosition(vehicle) || GameClient.bClient) {
 this->vehicles.add(vehicle);
 }
 }
 }
 }
 }
 }
 }

 void AddVehicles_TrafficJam_S(IsoMetaGrid.Zone zone, const std::string& string) {
 int int0 = zone.y - this->wy * 10 + 3;

 while (int0 < 0) {
 int0 += 6;
 }

 int int1 = zone.x - this->wx * 10 + 1;

 while (int1 < 0) {
 int1 += 3;
 }

 for (int int2 = int0; int2 < 10 && this->wy * 10 + int2 < zone.y + zone.h; int2 += 6 + Rand.Next(-1, 1) {
 for (int int3 = int1; int3 < 10 && this->wx * 10 + int3 < zone.x + zone.w; int3 += 3 + Rand.Next(1) {
 IsoGridSquare square = this->getGridSquare(int3, int2, 0);
 if (square != nullptr) {
 VehicleType vehicleType = VehicleType.getRandomVehicleType(string);
 if (vehicleType == nullptr) {
 System.out.println("Can't find car: " + string);
 break;
 }

 uint8_t byte0 = 80;
 if (SystemDisabler.doVehiclesEverywhere || DebugOptions.instance.VehicleSpawnEverywhere.getValue()) {
 byte0 = 100;
 }

 if (Rand.Next(100) <= byte0) {
 BaseVehicle vehicle = new BaseVehicle(IsoWorld.instance.CurrentCell);
 vehicle.setZone("TrafficJam");
 vehicle.setVehicleType(vehicleType.name);
 if (!this->RandomizeModel(vehicle, zone, string, vehicleType) {
 return;
 }

 vehicle.setScript();
 vehicle.setX(square.x + Rand.Next(0.0F, 1.0F);
 vehicle.setY(square.y + Rand.Next(0.0F, 1.0F);
 vehicle.setZ(square.z);
 vehicle.jniTransform
 .origin
 .set(vehicle.getX() - WorldSimulation.instance.offsetX, vehicle.getZ(), vehicle.getY() - WorldSimulation.instance.offsetY);
 if (this->isGoodVehiclePos(vehicle, this) {
 vehicle.setSkinIndex(Rand.Next(vehicle.getSkinCount() - 1);
 vehicle.setDir(IsoDirections.S);
 float float0 = Math.abs(zone.y + zone.h - square.y - zone.h);
 float0 /= 20.0F;
 float0 = Math.min(2.0F, float0);
 float float1 = vehicle.getDir().toAngle() + (float) Math.PI - 0.25F + Rand.Next(0.0F, float0);

 while (float1 > Math.PI * 2) {
 float1 = (float)(float1 - (Math.PI * 2);
 }

 vehicle.savedRot.setAngleAxis(float1, 0.0F, 1.0F, 0.0F);
 vehicle.jniTransform.setRotation(vehicle.savedRot);
 if (doSpawnedVehiclesInInvalidPosition(vehicle) || GameClient.bClient) {
 this->vehicles.add(vehicle);
 }
 }
 }
 }
 }
 }
 }

 void AddVehicles_TrafficJam_N(IsoMetaGrid.Zone zone, const std::string& string) {
 int int0 = zone.y - this->wy * 10 + 3;

 while (int0 < 0) {
 int0 += 6;
 }

 int int1 = zone.x - this->wx * 10 + 1;

 while (int1 < 0) {
 int1 += 3;
 }

 for (int int2 = int0; int2 < 10 && this->wy * 10 + int2 < zone.y + zone.h; int2 += 6 + Rand.Next(-1, 1) {
 for (int int3 = int1; int3 < 10 && this->wx * 10 + int3 < zone.x + zone.w; int3 += 3 + Rand.Next(1) {
 IsoGridSquare square = this->getGridSquare(int3, int2, 0);
 if (square != nullptr) {
 VehicleType vehicleType = VehicleType.getRandomVehicleType(string);
 if (vehicleType == nullptr) {
 System.out.println("Can't find car: " + string);
 break;
 }

 uint8_t byte0 = 80;
 if (SystemDisabler.doVehiclesEverywhere || DebugOptions.instance.VehicleSpawnEverywhere.getValue()) {
 byte0 = 100;
 }

 if (Rand.Next(100) <= byte0) {
 BaseVehicle vehicle = new BaseVehicle(IsoWorld.instance.CurrentCell);
 vehicle.setZone("TrafficJam");
 vehicle.setVehicleType(vehicleType.name);
 if (!this->RandomizeModel(vehicle, zone, string, vehicleType) {
 return;
 }

 vehicle.setScript();
 vehicle.setX(square.x + Rand.Next(0.0F, 1.0F);
 vehicle.setY(square.y + Rand.Next(0.0F, 1.0F);
 vehicle.setZ(square.z);
 vehicle.jniTransform
 .origin
 .set(vehicle.getX() - WorldSimulation.instance.offsetX, vehicle.getZ(), vehicle.getY() - WorldSimulation.instance.offsetY);
 if (this->isGoodVehiclePos(vehicle, this) {
 vehicle.setSkinIndex(Rand.Next(vehicle.getSkinCount() - 1);
 vehicle.setDir(IsoDirections.N);
 float float0 = Math.abs(zone.y + zone.h - square.y);
 float0 /= 20.0F;
 float0 = Math.min(2.0F, float0);
 float float1 = vehicle.getDir().toAngle() + (float) Math.PI - 0.25F + Rand.Next(0.0F, float0);

 while (float1 > Math.PI * 2) {
 float1 = (float)(float1 - (Math.PI * 2);
 }

 vehicle.savedRot.setAngleAxis(float1, 0.0F, 1.0F, 0.0F);
 vehicle.jniTransform.setRotation(vehicle.savedRot);
 if (doSpawnedVehiclesInInvalidPosition(vehicle) || GameClient.bClient) {
 this->vehicles.add(vehicle);
 }
 }
 }
 }
 }
 }
 }

 void AddVehicles_TrafficJam_Polyline(IsoMetaGrid.Zone zone, const std::string& string) {
 Vector2 vector0 = new Vector2();
 Vector2 vector1 = new Vector2();
 float float0 = 0.0F;
 float float1 = zone.getPolylineLength();

 for (byte byte0 = 0; byte0 < zone.points.size() - 2; byte0 += 2) {
 int int0 = zone.points.getQuick(byte0);
 int int1 = zone.points.getQuick(byte0 + 1);
 int int2 = zone.points.getQuick(byte0 + 2);
 int int3 = zone.points.getQuick(byte0 + 3);
 vector0.set(int2 - int0, int3 - int1);
 float float2 = vector0.getLength();
 vector1.set(vector0);
 vector1.tangent();
 vector1.normalize();
 float float3 = float0;
 float0 += float2;

 for (float float4 = 3.0F; float4 <= float2 - 3.0F; float4 += 6 + Rand.Next(-1, 1) {
 float float5 = PZMath.clamp(float4 + Rand.Next(-1.0F, 1.0F), 3.0F, float2 - 3.0F);
 float float6 = Rand.Next(-1.0F, 1.0F);
 float float7 = int0 + vector0.x / float2 * float5 + vector1.x * float6;
 float float8 = int1 + vector0.y / float2 * float5 + vector1.y * float6;
 this->TryAddVehicle_TrafficJam(zone, string, float7, float8, vector0, float3 + float5, float1);

 for (float float9 = 2.0F; float9 + 1.5F <= zone.polylineWidth / 2.0F; float9 += 2.0F) {
 float6 = float9 + Rand.Next(-1.0F, 1.0F);
 if (float6 + 1.5F <= zone.polylineWidth / 2.0F) {
 float5 = PZMath.clamp(float4 + Rand.Next(-2.0F, 2.0F), 3.0F, float2 - 3.0F);
 float7 = int0 + vector0.x / float2 * float5 + vector1.x * float6;
 float8 = int1 + vector0.y / float2 * float5 + vector1.y * float6;
 this->TryAddVehicle_TrafficJam(zone, string, float7, float8, vector0, float3 + float5, float1);
 }

 float6 = float9 + Rand.Next(-1.0F, 1.0F);
 if (float6 + 1.5F <= zone.polylineWidth / 2.0F) {
 float5 = PZMath.clamp(float4 + Rand.Next(-2.0F, 2.0F), 3.0F, float2 - 3.0F);
 float7 = int0 + vector0.x / float2 * float5 - vector1.x * float6;
 float8 = int1 + vector0.y / float2 * float5 - vector1.y * float6;
 this->TryAddVehicle_TrafficJam(zone, string, float7, float8, vector0, float3 + float5, float1);
 }
 }
 }
 }
 }

 void TryAddVehicle_TrafficJam(IsoMetaGrid.Zone zone, const std::string& string, float float1, float float0, Vector2 vector, float float6, float float7) {
 if (!(float1 < this->wx * 10) && !(float1 >= (this->wx + 1) * 10) && !(float0 < this->wy * 10) && !(float0 >= (this->wy + 1) * 10) {
 IsoGridSquare square = this->getGridSquare((int)float1 - this->wx * 10, (int)float0 - this->wy * 10, 0);
 if (square != nullptr) {
 VehicleType vehicleType = VehicleType.getRandomVehicleType(string + "W");
 if (vehicleType == nullptr) {
 System.out.println("Can't find car: " + string);
 } else {
 uint8_t byte0 = 80;
 if (SystemDisabler.doVehiclesEverywhere || DebugOptions.instance.VehicleSpawnEverywhere.getValue()) {
 byte0 = 100;
 }

 if (Rand.Next(100) <= byte0) {
 BaseVehicle vehicle = new BaseVehicle(IsoWorld.instance.CurrentCell);
 vehicle.setZone("TrafficJam");
 vehicle.setVehicleType(vehicleType.name);
 if (this->RandomizeModel(vehicle, zone, string, vehicleType) {
 vehicle.setScript();
 vehicle.setX(float1);
 vehicle.setY(float0);
 vehicle.setZ(square.z);
 float float2 = vector.x;
 float float3 = vector.y;
 vector.normalize();
 vehicle.setDir(IsoDirections.fromAngle(vector);
 float float4 = vector.getDirectionNeg();
 vector.set(float2, float3);
 float float5 = 90.0F * (float6 / float7);
 float4 += Rand.Next(-float5, float5) * (float) (Math.PI / 180.0);

 while (float4 > Math.PI * 2) {
 float4 = (float)(float4 - (Math.PI * 2);
 }

 vehicle.savedRot.setAngleAxis(float4, 0.0F, 1.0F, 0.0F);
 vehicle.jniTransform.setRotation(vehicle.savedRot);
 vehicle.jniTransform
 .origin
 .set(vehicle.getX() - WorldSimulation.instance.offsetX, vehicle.getZ(), vehicle.getY() - WorldSimulation.instance.offsetY);
 if (this->isGoodVehiclePos(vehicle, this) {
 vehicle.setSkinIndex(Rand.Next(vehicle.getSkinCount() - 1);
 if (doSpawnedVehiclesInInvalidPosition(vehicle) {
 this->vehicles.add(vehicle);
 }
 }
 }
 }
 }
 }
 }
 }

 void AddVehicles() {
 if (SandboxOptions.instance.CarSpawnRate.getValue() != 1) {
 if (VehicleType.vehicles.empty()) {
 VehicleType.init();
 }

 if (!GameClient.bClient) {
 if (SandboxOptions.instance.EnableVehicles.getValue()) {
 if (!GameServer.bServer) {
 WorldSimulation.instance.create();
 }

 IsoMetaCell metaCell = IsoWorld.instance.getMetaGrid().getCellData(this->wx / 30, this->wy / 30);
 std::vector arrayList = metaCell == nullptr ? nullptr : metaCell.vehicleZones;

 for (int int0 = 0; arrayList != nullptr && int0 < arrayList.size(); int0++) {
 IsoMetaGrid.VehicleZone vehicleZone = (IsoMetaGrid.VehicleZone)arrayList.get(int0);
 if (vehicleZone.x + vehicleZone.w >= this->wx * 10
 && vehicleZone.y + vehicleZone.h >= this->wy * 10
 && vehicleZone.x < (this->wx + 1) * 10
 && vehicleZone.y < (this->wy + 1) * 10) {
 std::string string = vehicleZone.name;
 if (string.empty()) {
 string = vehicleZone.type;
 }

 if (SandboxOptions.instance.TrafficJam.getValue()) {
 if (vehicleZone.isPolyline()) {
 if ("TrafficJam".equalsIgnoreCase(string) {
 this->AddVehicles_TrafficJam_Polyline(vehicleZone, string);
 continue;
 }

 if ("RTrafficJam".equalsIgnoreCase(string) && Rand.Next(100) < 10) {
 this->AddVehicles_TrafficJam_Polyline(vehicleZone, string.replaceFirst("rtraffic", "traffic"));
 continue;
 }
 }

 if ("TrafficJamW".equalsIgnoreCase(string) {
 this->AddVehicles_TrafficJam_W(vehicleZone, string);
 }

 if ("TrafficJamE".equalsIgnoreCase(string) {
 this->AddVehicles_TrafficJam_E(vehicleZone, string);
 }

 if ("TrafficJamS".equalsIgnoreCase(string) {
 this->AddVehicles_TrafficJam_S(vehicleZone, string);
 }

 if ("TrafficJamN".equalsIgnoreCase(string) {
 this->AddVehicles_TrafficJam_N(vehicleZone, string);
 }

 if ("RTrafficJamW".equalsIgnoreCase(string) && Rand.Next(100) < 10) {
 this->AddVehicles_TrafficJam_W(vehicleZone, string.replaceFirst("rtraffic", "traffic"));
 }

 if ("RTrafficJamE".equalsIgnoreCase(string) && Rand.Next(100) < 10) {
 this->AddVehicles_TrafficJam_E(vehicleZone, string.replaceFirst("rtraffic", "traffic"));
 }

 if ("RTrafficJamS".equalsIgnoreCase(string) && Rand.Next(100) < 10) {
 this->AddVehicles_TrafficJam_S(vehicleZone, string.replaceFirst("rtraffic", "traffic"));
 }

 if ("RTrafficJamN".equalsIgnoreCase(string) && Rand.Next(100) < 10) {
 this->AddVehicles_TrafficJam_N(vehicleZone, string.replaceFirst("rtraffic", "traffic"));
 }
 }

 if (!StringUtils.containsIgnoreCase(string, "TrafficJam")) {
 if ("TestVehicles" == string) {
 this->AddVehicles_ForTest(vehicleZone);
 } else if (VehicleType.hasTypeForZone(string) {
 if (vehicleZone.isPolyline()) {
 this->AddVehicles_OnZonePolyline(vehicleZone, string);
 } else {
 this->AddVehicles_OnZone(vehicleZone, string);
 }
 }
 }
 }
 }

 IsoMetaChunk metaChunk = IsoWorld.instance.getMetaChunk(this->wx, this->wy);
 if (metaChunk != nullptr) {
 for (int int1 = 0; int1 < metaChunk.numZones(); int1++) {
 IsoMetaGrid.Zone zone = metaChunk.getZone(int1);
 this->addRandomCarCrash(zone, false);
 }
 }
 }
 }
 }
 }

 void addSurvivorInHorde(bool forced) {
 if (forced || !IsoWorld.getZombiesDisabled()) {
 IsoMetaChunk metaChunk = IsoWorld.instance.getMetaChunk(this->wx, this->wy);
 if (metaChunk != nullptr) {
 for (int int0 = 0; int0 < metaChunk.numZones(); int0++) {
 IsoMetaGrid.Zone zone = metaChunk.getZone(int0);
 if (this->canAddSurvivorInHorde(zone, forced) {
 int int1 = 4;
 float float0 = (float)GameTime.getInstance().getWorldAgeHours() / 24.0F;
 float0 += (SandboxOptions.instance.TimeSinceApo.getValue() - 1) * 30;
 int1 = (int)(int1 + float0 * 0.03F);
 int1 = Math.max(15, int1);
 if (forced || Rand.Next(0.0F, 500.0F) < 0.4F * int1) {
 this->addSurvivorInHorde(zone);
 if (forced) {
 break;
 }
 }
 }
 }
 }
 }
 }

 bool canAddSurvivorInHorde(IsoMetaGrid.Zone zone, bool boolean0) {
 if (!boolean0 && IsoWorld.instance.getTimeSinceLastSurvivorInHorde() > 0) {
 return false;
 } else if (!boolean0 && IsoWorld.getZombiesDisabled()) {
 return false;
 } else if (!boolean0 && zone.hourLastSeen != 0) {
 return false;
 } else {
 return !boolean0 && zone.haveConstruction ? false : "Nav" == zone.getType());
 }
 }

 void addSurvivorInHorde(IsoMetaGrid.Zone zone) {
 zone.hourLastSeen++;
 IsoWorld.instance.setTimeSinceLastSurvivorInHorde(5000);
 int int0 = Math.max(zone.x, this->wx * 10);
 int int1 = Math.max(zone.y, this->wy * 10);
 int int2 = Math.min(zone.x + zone.w, (this->wx + 1) * 10);
 int int3 = Math.min(zone.y + zone.h, (this->wy + 1) * 10);
 float float0 = int0 + (int2 - int0) / 2.0F;
 float float1 = int1 + (int3 - int1) / 2.0F;
 VirtualZombieManager.instance.choices.clear();
 IsoGridSquare square = this->getGridSquare((int)float0 - this->wx * 10, (int)float1 - this->wy * 10, 0);
 if (square.getBuilding() == nullptr) {
 VirtualZombieManager.instance.choices.add(square);
 int int4 = Rand.Next(15, 20);

 for (int int5 = 0; int5 < int4; int5++) {
 IsoZombie zombie0 = VirtualZombieManager.instance.createRealZombieAlways(Rand.Next(8), false);
 if (zombie0 != nullptr) {
 zombie0.dressInRandomOutfit();
 ZombieSpawnRecorder.instance.record(zombie0, "addSurvivorInHorde");
 }
 }

 IsoZombie zombie1 = VirtualZombieManager.instance.createRealZombieAlways(Rand.Next(8), false);
 if (zombie1 != nullptr) {
 ZombieSpawnRecorder.instance.record(zombie1, "addSurvivorInHorde");
 zombie1.setAsSurvivor();
 }
 }
 }

 bool canAddRandomCarCrash(IsoMetaGrid.Zone zone, bool force) {
 if (!force && zone.hourLastSeen != 0) {
 return false;
 } else if (!force && zone.haveConstruction) {
 return false;
 } else if (!"Nav" == zone.getType())) {
 return false;
 } else {
 int int0 = Math.max(zone.x, this->wx * 10);
 int int1 = Math.max(zone.y, this->wy * 10);
 int int2 = Math.min(zone.x + zone.w, (this->wx + 1) * 10);
 int int3 = Math.min(zone.y + zone.h, (this->wy + 1) * 10);
 if (zone.w > 30 && zone.h < 13) {
 return int2 - int0 >= 10 && int3 - int1 >= 5;
 } else {
 return zone.h > 30 && zone.w < 13 ? int2 - int0 >= 5 && int3 - int1 >= 10 : false;
 }
 }
 }

 void addRandomCarCrash(IsoMetaGrid.Zone zone, bool addToWorld) {
 if (this->vehicles.empty()) {
 if ("Nav" == zone.getType())) {
 RandomizedVehicleStoryBase.doRandomStory(zone, this, false);
 }
 }
 }

 static bool FileExists(int _wx, int _wy) {
 File file = ChunkMapFilenames.instance.getFilename(_wx, _wy);
 if (file == nullptr) {
 file = ZomboidFileSystem.instance.getFileInCurrentSave(prefix + _wx + "_" + _wy + ".bin");
 }

 long long0 = 0L;
 return file.exists();
 }

 void checkPhysics() {
 if (this->physicsCheck) {
 WorldSimulation.instance.create();
 Bullet.beginUpdateChunk(this);
 uint8_t byte0 = 0;
 if (byte0 < 8) {
 for (int int0 = 0; int0 < 10; int0++) {
 for (int int1 = 0; int1 < 10; int1++) {
 this->calcPhysics(int1, int0, byte0, this->shapes);
 int int2 = 0;

 for (int int3 = 0; int3 < 4; int3++) {
 if (this->shapes[int3] != nullptr) {
 bshapes[int2++] = (byte)(this->shapes[int3].ordinal() + 1);
 }
 }

 Bullet.updateChunk(int1, int0, byte0, int2, bshapes);
 }
 }
 }

 Bullet.endUpdateChunk();
 this->physicsCheck = false;
 }
 }

 void calcPhysics(int int1, int int2, int int3, IsoChunk.PhysicsShapes[] physicsShapess) {
 for (int int0 = 0; int0 < 4; int0++) {
 physicsShapess[int0] = nullptr;
 }

 IsoGridSquare square = this->getGridSquare(int1, int2, int3);
 if (square != nullptr) {
 int int4 = 0;
 if (int3 == 0) {
 bool boolean0 = false;

 for (int int5 = 0; int5 < square.getObjects().size(); int5++) {
 IsoObject object0 = square.getObjects().get(int5);
 if (object0.sprite != nullptr
 && object0.sprite.name != nullptr
 && (
 object0.sprite.name.contains("lighting_outdoor_")
 || object0.sprite.name == "recreational_sports_01_21")
 || object0.sprite.name == "recreational_sports_01_19")
 || object0.sprite.name == "recreational_sports_01_32")
 )
 && (!object0.getProperties().Is("MoveType") || !"WallObject" == object0.getProperties().Val("MoveType")))) {
 boolean0 = true;
 break;
 }
 }

 if (boolean0) {
 physicsShapess[int4++] = IsoChunk.PhysicsShapes.Tree;
 }
 }

 bool boolean1 = false;
 if (!square.getSpecialObjects().empty()) {
 int int6 = square.getSpecialObjects().size();

 for (int int7 = 0; int7 < int6; int7++) {
 IsoObject object1 = square.getSpecialObjects().get(int7);
 if (object1 instanceof IsoThumpable && ((IsoThumpable)object1).isBlockAllTheSquare()) {
 boolean1 = true;
 break;
 }
 }
 }

 PropertyContainer propertyContainer = square.getProperties();
 if (square.hasTypes.isSet(IsoObjectType.isMoveAbleObject) {
 physicsShapess[int4++] = IsoChunk.PhysicsShapes.Tree;
 }

 if (square.hasTypes.isSet(IsoObjectType.tree) {
 std::string string0 = square.getProperties().Val("tree");
 std::string string1 = square.getProperties().Val("WindType");
 if (string0 == nullptr) {
 physicsShapess[int4++] = IsoChunk.PhysicsShapes.Tree;
 }

 if (string0 != nullptr && !string0 == "1") && (string1 == nullptr || !string1 == "2") || !string0 == "2") && !string0 == "1"))) {
 physicsShapess[int4++] = IsoChunk.PhysicsShapes.Tree;
 }
 } else if (!propertyContainer.Is(IsoFlagType.solid)
 && !propertyContainer.Is(IsoFlagType.solidtrans)
 && !propertyContainer.Is(IsoFlagType.blocksight)
 && !square.HasStairs()
 && !boolean1) {
 if (int3 > 0 && (square.SolidFloorCached ? square.SolidFloor : square.TreatAsSolidFloor())) {
 if (int4 == physicsShapess.length) {
 DebugLog.log(DebugType.General, "Error: Too many physics objects on gridsquare: " + square.x + ", " + square.y + ", " + square.z);
 return;
 }

 physicsShapess[int4++] = IsoChunk.PhysicsShapes.Floor;
 }
 } else {
 if (int4 == physicsShapess.length) {
 DebugLog.log(DebugType.General, "Error: Too many physics objects on gridsquare: " + square.x + ", " + square.y + ", " + square.z);
 return;
 }

 physicsShapess[int4++] = IsoChunk.PhysicsShapes.Solid;
 }

 if (!square.getProperties().Is("CarSlowFactor")) {
 if (propertyContainer.Is(IsoFlagType.collideW)
 || propertyContainer.Is(IsoFlagType.windowW)
 || square.getProperties().Is(IsoFlagType.DoorWallW) && !square.getProperties().Is("GarageDoor")) {
 if (int4 == physicsShapess.length) {
 DebugLog.log(DebugType.General, "Error: Too many physics objects on gridsquare: " + square.x + ", " + square.y + ", " + square.z);
 return;
 }

 physicsShapess[int4++] = IsoChunk.PhysicsShapes.WallW;
 }

 if (propertyContainer.Is(IsoFlagType.collideN)
 || propertyContainer.Is(IsoFlagType.windowN)
 || square.getProperties().Is(IsoFlagType.DoorWallN) && !square.getProperties().Is("GarageDoor")) {
 if (int4 == physicsShapess.length) {
 DebugLog.log(DebugType.General, "Error: Too many physics objects on gridsquare: " + square.x + ", " + square.y + ", " + square.z);
 return;
 }

 physicsShapess[int4++] = IsoChunk.PhysicsShapes.WallN;
 }

 if (square.Is("PhysicsShape")) {
 if (int4 == physicsShapess.length) {
 DebugLog.log(DebugType.General, "Error: Too many physics objects on gridsquare: " + square.x + ", " + square.y + ", " + square.z);
 return;
 }

 std::string string2 = square.getProperties().Val("PhysicsShape");
 if ("Solid" == string2) {
 physicsShapess[int4++] = IsoChunk.PhysicsShapes.Solid;
 } else if ("WallN" == string2) {
 physicsShapess[int4++] = IsoChunk.PhysicsShapes.WallN;
 } else if ("WallW" == string2) {
 physicsShapess[int4++] = IsoChunk.PhysicsShapes.WallW;
 } else if ("WallS" == string2) {
 physicsShapess[int4++] = IsoChunk.PhysicsShapes.WallS;
 } else if ("WallE" == string2) {
 physicsShapess[int4++] = IsoChunk.PhysicsShapes.WallE;
 } else if ("Tree" == string2) {
 physicsShapess[int4++] = IsoChunk.PhysicsShapes.Tree;
 } else if ("Floor" == string2) {
 physicsShapess[int4++] = IsoChunk.PhysicsShapes.Floor;
 }
 }
 }
 }
 }

 bool LoadBrandNew(int _wx, int _wy) {
 this->wx = _wx;
 this->wy = _wy;
 if (!CellLoader.LoadCellBinaryChunk(IsoWorld.instance.CurrentCell, _wx, _wy, this) {
 return false;
 } else {
 if (!Core.GameMode == "Tutorial") && !Core.GameMode == "LastStand") && !GameClient.bClient) {
 this->addZombies = true;
 }

 return true;
 }
 }

 bool LoadOrCreate(int _wx, int _wy, ByteBuffer fromServer) {
 this->wx = _wx;
 this->wy = _wy;
 if (fromServer != nullptr && !this->blam) {
 return this->LoadFromBuffer(_wx, _wy, fromServer);
 } else {
 File file = ChunkMapFilenames.instance.getFilename(_wx, _wy);
 if (file == nullptr) {
 file = ZomboidFileSystem.instance.getFileInCurrentSave(prefix + _wx + "_" + _wy + ".bin");
 }

 if (file.exists() && !this->blam) {
 try {
 this->LoadFromDisk();
 } catch (Exception exception) {
 ExceptionLogger.logException(exception, "Error loading chunk " + _wx + "," + _wy);
 if (GameServer.bServer) {
 LoggerManager.getLogger("map").write("Error loading chunk " + _wx + "," + _wy);
 LoggerManager.getLogger("map").write(exception);
 }

 this->BackupBlam(_wx, _wy, exception);
 return false;
 }

 if (GameClient.bClient) {
 GameClient.instance.worldObjectsSyncReq.putRequestSyncIsoChunk(this);
 }

 return true;
 } else {
 return this->LoadBrandNew(_wx, _wy);
 }
 }
 }

 bool LoadFromBuffer(int _wx, int _wy, ByteBuffer bb) {
 this->wx = _wx;
 this->wy = _wy;
 if (!this->blam) {
 try {
 this->LoadFromDiskOrBuffer(bb);
 return true;
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 if (GameServer.bServer) {
 LoggerManager.getLogger("map").write("Error loading chunk " + _wx + "," + _wy);
 LoggerManager.getLogger("map").write(exception);
 }

 this->BackupBlam(_wx, _wy, exception);
 return false;
 }
 } else {
 return this->LoadBrandNew(_wx, _wy);
 }
 }

 void ensureSurroundNotNull(int int3, int int2, int int4) {
 IsoCell cell = IsoWorld.instance.CurrentCell;

 for (int int0 = -1; int0 <= 1; int0++) {
 for (int int1 = -1; int1 <= 1; int1++) {
 if ((int0 != 0 || int1 != 0) && int3 + int0 >= 0 && int3 + int0 < 10 && int2 + int1 >= 0 && int2 + int1 < 10) {
 IsoGridSquare square = this->getGridSquare(int3 + int0, int2 + int1, int4);
 if (square == nullptr) {
 square = IsoGridSquare.getNew(cell, nullptr, this->wx * 10 + int3 + int0, this->wy * 10 + int2 + int1, int4);
 this->setSquare(int3 + int0, int2 + int1, int4, square);
 }
 }
 }
 }
 }

 void loadInWorldStreamerThread() {
 IsoCell cell = IsoWorld.instance.CurrentCell;

 for (int int0 = 0; int0 <= this->maxLevel; int0++) {
 for (int int1 = 0; int1 < 10; int1++) {
 for (int int2 = 0; int2 < 10; int2++) {
 IsoGridSquare square0 = this->getGridSquare(int2, int1, int0);
 if (square0 == nullptr && int0 == 0) {
 square0 = IsoGridSquare.getNew(IsoWorld.instance.CurrentCell, nullptr, this->wx * 10 + int2, this->wy * 10 + int1, int0);
 this->setSquare(int2, int1, int0, square0);
 }

 if (int0 == 0 && square0.getFloor() == nullptr) {
 DebugLog.log("ERROR: added floor at " + square0.x + "," + square0.y + "," + square0.z + " because there wasn't one");
 IsoObject object = IsoObject.getNew();
 object.sprite = IsoSprite.getSprite(IsoSpriteManager.instance, "carpentry_02_58", 0);
 object.square = square0;
 square0.Objects.add(0, object);
 }

 if (square0 != nullptr) {
 if (int0 > 0 && !square0.getObjects().empty()) {
 this->ensureSurroundNotNull(int2, int1, int0);

 for (int int3 = int0 - 1; int3 > 0; int3--) {
 IsoGridSquare square1 = this->getGridSquare(int2, int1, int3);
 if (square1 == nullptr) {
 square1 = IsoGridSquare.getNew(cell, nullptr, this->wx * 10 + int2, this->wy * 10 + int1, int3);
 this->setSquare(int2, int1, int3, square1);
 this->ensureSurroundNotNull(int2, int1, int3);
 }
 }
 }

 square0.RecalcProperties();
 }
 }
 }
 }

 assert chunkGetter.chunk == nullptr;

 chunkGetter.chunk = this;

 for (int int4 = 0; int4 < 10; int4++) {
 for (int int5 = 0; int5 < 10; int5++) {
 for (int int6 = this->maxLevel; int6 > 0; int6--) {
 IsoGridSquare square2 = this->getGridSquare(int5, int4, int6);
 if (square2 != nullptr && square2.Is(IsoFlagType.solidfloor) {
 int6--;

 for (; int6 >= 0; int6--) {
 square2 = this->getGridSquare(int5, int4, int6);
 if (square2 != nullptr && !square2.haveRoof) {
 square2.haveRoof = true;
 square2.getProperties().UnSet(IsoFlagType.exterior);
 }
 }
 break;
 }
 }
 }
 }

 for (int int7 = 0; int7 <= this->maxLevel; int7++) {
 for (int int8 = 0; int8 < 10; int8++) {
 for (int int9 = 0; int9 < 10; int9++) {
 IsoGridSquare square3 = this->getGridSquare(int9, int8, int7);
 if (square3 != nullptr) {
 square3.RecalcAllWithNeighbours(true, chunkGetter);
 }
 }
 }
 }

 chunkGetter.chunk = nullptr;

 for (int int10 = 0; int10 <= this->maxLevel; int10++) {
 for (int int11 = 0; int11 < 10; int11++) {
 for (int int12 = 0; int12 < 10; int12++) {
 IsoGridSquare square4 = this->getGridSquare(int12, int11, int10);
 if (square4 != nullptr) {
 square4.propertiesDirty = true;
 }
 }
 }
 }
 }

 void RecalcAllWithNeighbour(IsoGridSquare square0, IsoDirections directions, int int3) {
 uint8_t byte0 = 0;
 uint8_t byte1 = 0;
 if (directions == IsoDirections.W || directions == IsoDirections.NW || directions == IsoDirections.SW) {
 byte0 = -1;
 } else if (directions == IsoDirections.E || directions == IsoDirections.NE || directions == IsoDirections.SE) {
 byte0 = 1;
 }

 if (directions == IsoDirections.N || directions == IsoDirections.NW || directions == IsoDirections.NE) {
 byte1 = -1;
 } else if (directions == IsoDirections.S || directions == IsoDirections.SW || directions == IsoDirections.SE) {
 byte1 = 1;
 }

 int int0 = square0.getX() + byte0;
 int int1 = square0.getY() + byte1;
 int int2 = square0.getZ() + int3;
 IsoGridSquare square1 = int3 == 0 ? square0.nav[directions.index()] : IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 if (square1 != nullptr) {
 square0.ReCalculateCollide(square1);
 square1.ReCalculateCollide(square0);
 square0.ReCalculatePathFind(square1);
 square1.ReCalculatePathFind(square0);
 square0.ReCalculateVisionBlocked(square1);
 square1.ReCalculateVisionBlocked(square0);
 }

 if (int3 == 0) {
 switch (directions) {
 case E:
 if (square1 == nullptr) {
 square0.e = nullptr;
 } else {
 square0.e = square0.testPathFindAdjacent(nullptr, 1, 0, 0) ? nullptr : square1;
 square1.w = square1.testPathFindAdjacent(nullptr, -1, 0, 0) ? nullptr : square0;
 }
 break;
 case W:
 if (square1 == nullptr) {
 square0.w = nullptr;
 } else {
 square0.w = square0.testPathFindAdjacent(nullptr, -1, 0, 0) ? nullptr : square1;
 square1.e = square1.testPathFindAdjacent(nullptr, 1, 0, 0) ? nullptr : square0;
 }
 break;
 case N:
 if (square1 == nullptr) {
 square0.n = nullptr;
 } else {
 square0.n = square0.testPathFindAdjacent(nullptr, 0, -1, 0) ? nullptr : square1;
 square1.s = square1.testPathFindAdjacent(nullptr, 0, 1, 0) ? nullptr : square0;
 }
 break;
 case S:
 if (square1 == nullptr) {
 square0.s = nullptr;
 } else {
 square0.s = square0.testPathFindAdjacent(nullptr, 0, 1, 0) ? nullptr : square1;
 square1.n = square1.testPathFindAdjacent(nullptr, 0, -1, 0) ? nullptr : square0;
 }
 break;
 case NW:
 if (square1 == nullptr) {
 square0.nw = nullptr;
 } else {
 square0.nw = square0.testPathFindAdjacent(nullptr, -1, -1, 0) ? nullptr : square1;
 square1.se = square1.testPathFindAdjacent(nullptr, 1, 1, 0) ? nullptr : square0;
 }
 break;
 case NE:
 if (square1 == nullptr) {
 square0.ne = nullptr;
 } else {
 square0.ne = square0.testPathFindAdjacent(nullptr, 1, -1, 0) ? nullptr : square1;
 square1.sw = square1.testPathFindAdjacent(nullptr, -1, 1, 0) ? nullptr : square0;
 }
 break;
 case SE:
 if (square1 == nullptr) {
 square0.se = nullptr;
 } else {
 square0.se = square0.testPathFindAdjacent(nullptr, 1, 1, 0) ? nullptr : square1;
 square1.nw = square1.testPathFindAdjacent(nullptr, -1, -1, 0) ? nullptr : square0;
 }
 break;
 case SW:
 if (square1 == nullptr) {
 square0.sw = nullptr;
 } else {
 square0.sw = square0.testPathFindAdjacent(nullptr, -1, 1, 0) ? nullptr : square1;
 square1.ne = square1.testPathFindAdjacent(nullptr, 1, -1, 0) ? nullptr : square0;
 }
 }
 }
 }

 void EnsureSurroundNotNullX(int int1, int int2, int int3) {
 IsoCell cell = IsoWorld.instance.CurrentCell;

 for (int int0 = int1 - 1; int0 <= int1 + 1; int0++) {
 if (int0 >= 0 && int0 < 10) {
 IsoGridSquare square = this->getGridSquare(int0, int2, int3);
 if (square == nullptr) {
 square = IsoGridSquare.getNew(cell, nullptr, this->wx * 10 + int0, this->wy * 10 + int2, int3);
 cell.ConnectNewSquare(square, false);
 }
 }
 }
 }

 void EnsureSurroundNotNullY(int int2, int int1, int int3) {
 IsoCell cell = IsoWorld.instance.CurrentCell;

 for (int int0 = int1 - 1; int0 <= int1 + 1; int0++) {
 if (int0 >= 0 && int0 < 10) {
 IsoGridSquare square = this->getGridSquare(int2, int0, int3);
 if (square == nullptr) {
 square = IsoGridSquare.getNew(cell, nullptr, this->wx * 10 + int2, this->wy * 10 + int0, int3);
 cell.ConnectNewSquare(square, false);
 }
 }
 }
 }

 void EnsureSurroundNotNull(int int0, int int1, int int2) {
 IsoCell cell = IsoWorld.instance.CurrentCell;
 IsoGridSquare square = this->getGridSquare(int0, int1, int2);
 if (square == nullptr) {
 square = IsoGridSquare.getNew(cell, nullptr, this->wx * 10 + int0, this->wy * 10 + int1, int2);
 cell.ConnectNewSquare(square, false);
 }
 }

 void loadInMainThread() {
 IsoCell cell = IsoWorld.instance.CurrentCell;
 IsoChunk chunk0 = cell.getChunk(this->wx - 1, this->wy);
 IsoChunk chunk2 = cell.getChunk(this->wx, this->wy - 1);
 IsoChunk chunk3 = cell.getChunk(this->wx + 1, this->wy);
 IsoChunk chunk4 = cell.getChunk(this->wx, this->wy + 1);
 IsoChunk chunk5 = cell.getChunk(this->wx - 1, this->wy - 1);
 IsoChunk chunk6 = cell.getChunk(this->wx + 1, this->wy - 1);
 IsoChunk chunk7 = cell.getChunk(this->wx + 1, this->wy + 1);
 IsoChunk chunk8 = cell.getChunk(this->wx - 1, this->wy + 1);

 for (int int0 = 1; int0 < 8; int0++) {
 for (int int1 = 0; int1 < 10; int1++) {
 if (chunk2 != nullptr) {
 IsoGridSquare square0 = chunk2.getGridSquare(int1, 9, int0);
 if (square0 != nullptr && !square0.getObjects().empty()) {
 this->EnsureSurroundNotNullX(int1, 0, int0);
 }
 }

 if (chunk4 != nullptr) {
 IsoGridSquare square1 = chunk4.getGridSquare(int1, 0, int0);
 if (square1 != nullptr && !square1.getObjects().empty()) {
 this->EnsureSurroundNotNullX(int1, 9, int0);
 }
 }
 }

 for (int int2 = 0; int2 < 10; int2++) {
 if (chunk0 != nullptr) {
 IsoGridSquare square2 = chunk0.getGridSquare(9, int2, int0);
 if (square2 != nullptr && !square2.getObjects().empty()) {
 this->EnsureSurroundNotNullY(0, int2, int0);
 }
 }

 if (chunk3 != nullptr) {
 IsoGridSquare square3 = chunk3.getGridSquare(0, int2, int0);
 if (square3 != nullptr && !square3.getObjects().empty()) {
 this->EnsureSurroundNotNullY(9, int2, int0);
 }
 }
 }

 if (chunk5 != nullptr) {
 IsoGridSquare square4 = chunk5.getGridSquare(9, 9, int0);
 if (square4 != nullptr && !square4.getObjects().empty()) {
 this->EnsureSurroundNotNull(0, 0, int0);
 }
 }

 if (chunk6 != nullptr) {
 IsoGridSquare square5 = chunk6.getGridSquare(0, 9, int0);
 if (square5 != nullptr && !square5.getObjects().empty()) {
 this->EnsureSurroundNotNull(9, 0, int0);
 }
 }

 if (chunk7 != nullptr) {
 IsoGridSquare square6 = chunk7.getGridSquare(0, 0, int0);
 if (square6 != nullptr && !square6.getObjects().empty()) {
 this->EnsureSurroundNotNull(9, 9, int0);
 }
 }

 if (chunk8 != nullptr) {
 IsoGridSquare square7 = chunk8.getGridSquare(9, 0, int0);
 if (square7 != nullptr && !square7.getObjects().empty()) {
 this->EnsureSurroundNotNull(0, 9, int0);
 }
 }
 }

 for (int int3 = 1; int3 < 8; int3++) {
 for (int int4 = 0; int4 < 10; int4++) {
 if (chunk2 != nullptr) {
 IsoGridSquare square8 = this->getGridSquare(int4, 0, int3);
 if (square8 != nullptr && !square8.getObjects().empty()) {
 chunk2.EnsureSurroundNotNullX(int4, 9, int3);
 }
 }

 if (chunk4 != nullptr) {
 IsoGridSquare square9 = this->getGridSquare(int4, 9, int3);
 if (square9 != nullptr && !square9.getObjects().empty()) {
 chunk4.EnsureSurroundNotNullX(int4, 0, int3);
 }
 }
 }

 for (int int5 = 0; int5 < 10; int5++) {
 if (chunk0 != nullptr) {
 IsoGridSquare square10 = this->getGridSquare(0, int5, int3);
 if (square10 != nullptr && !square10.getObjects().empty()) {
 chunk0.EnsureSurroundNotNullY(9, int5, int3);
 }
 }

 if (chunk3 != nullptr) {
 IsoGridSquare square11 = this->getGridSquare(9, int5, int3);
 if (square11 != nullptr && !square11.getObjects().empty()) {
 chunk3.EnsureSurroundNotNullY(0, int5, int3);
 }
 }
 }

 if (chunk5 != nullptr) {
 IsoGridSquare square12 = this->getGridSquare(0, 0, int3);
 if (square12 != nullptr && !square12.getObjects().empty()) {
 chunk5.EnsureSurroundNotNull(9, 9, int3);
 }
 }

 if (chunk6 != nullptr) {
 IsoGridSquare square13 = this->getGridSquare(9, 0, int3);
 if (square13 != nullptr && !square13.getObjects().empty()) {
 chunk6.EnsureSurroundNotNull(0, 9, int3);
 }
 }

 if (chunk7 != nullptr) {
 IsoGridSquare square14 = this->getGridSquare(9, 9, int3);
 if (square14 != nullptr && !square14.getObjects().empty()) {
 chunk7.EnsureSurroundNotNull(0, 0, int3);
 }
 }

 if (chunk8 != nullptr) {
 IsoGridSquare square15 = this->getGridSquare(0, 9, int3);
 if (square15 != nullptr && !square15.getObjects().empty()) {
 chunk8.EnsureSurroundNotNull(9, 0, int3);
 }
 }
 }

 for (int int6 = 0; int6 <= this->maxLevel; int6++) {
 for (int int7 = 0; int7 < 10; int7++) {
 for (int int8 = 0; int8 < 10; int8++) {
 IsoGridSquare square16 = this->getGridSquare(int8, int7, int6);
 if (square16 != nullptr) {
 if (int8 == 0 || int8 == 9 || int7 == 0 || int7 == 9) {
 IsoWorld.instance.CurrentCell.DoGridNav(square16, IsoGridSquare.cellGetSquare);

 for (int int9 = -1; int9 <= 1; int9++) {
 if (int8 == 0) {
 this->RecalcAllWithNeighbour(square16, IsoDirections.W, int9);
 this->RecalcAllWithNeighbour(square16, IsoDirections.NW, int9);
 this->RecalcAllWithNeighbour(square16, IsoDirections.SW, int9);
 } else if (int8 == 9) {
 this->RecalcAllWithNeighbour(square16, IsoDirections.E, int9);
 this->RecalcAllWithNeighbour(square16, IsoDirections.NE, int9);
 this->RecalcAllWithNeighbour(square16, IsoDirections.SE, int9);
 }

 if (int7 == 0) {
 this->RecalcAllWithNeighbour(square16, IsoDirections.N, int9);
 if (int8 != 0) {
 this->RecalcAllWithNeighbour(square16, IsoDirections.NW, int9);
 }

 if (int8 != 9) {
 this->RecalcAllWithNeighbour(square16, IsoDirections.NE, int9);
 }
 } else if (int7 == 9) {
 this->RecalcAllWithNeighbour(square16, IsoDirections.S, int9);
 if (int8 != 0) {
 this->RecalcAllWithNeighbour(square16, IsoDirections.SW, int9);
 }

 if (int8 != 9) {
 this->RecalcAllWithNeighbour(square16, IsoDirections.SE, int9);
 }
 }
 }

 IsoGridSquare square17 = square16.nav[IsoDirections.N.index()];
 IsoGridSquare square18 = square16.nav[IsoDirections.S.index()];
 IsoGridSquare square19 = square16.nav[IsoDirections.W.index()];
 IsoGridSquare square20 = square16.nav[IsoDirections.E.index()];
 if (square17 != nullptr && square19 != nullptr && (int8 == 0 || int7 == 0) {
 this->RecalcAllWithNeighbour(square17, IsoDirections.W, 0);
 }

 if (square17 != nullptr && square20 != nullptr && (int8 == 9 || int7 == 0) {
 this->RecalcAllWithNeighbour(square17, IsoDirections.E, 0);
 }

 if (square18 != nullptr && square19 != nullptr && (int8 == 0 || int7 == 9) {
 this->RecalcAllWithNeighbour(square18, IsoDirections.W, 0);
 }

 if (square18 != nullptr && square20 != nullptr && (int8 == 9 || int7 == 9) {
 this->RecalcAllWithNeighbour(square18, IsoDirections.E, 0);
 }
 }

 IsoRoom room = square16.getRoom();
 if (room != nullptr) {
 room.addSquare(square16);
 }
 }
 }
 }
 }

 this->fixObjectAmbientEmittersOnAdjacentChunks(chunk3, chunk4);

 for (int int10 = 0; int10 < 4; int10++) {
 if (chunk0 != nullptr) {
 chunk0.lightCheck[int10] = true;
 }

 if (chunk2 != nullptr) {
 chunk2.lightCheck[int10] = true;
 }

 if (chunk3 != nullptr) {
 chunk3.lightCheck[int10] = true;
 }

 if (chunk4 != nullptr) {
 chunk4.lightCheck[int10] = true;
 }

 if (chunk5 != nullptr) {
 chunk5.lightCheck[int10] = true;
 }

 if (chunk6 != nullptr) {
 chunk6.lightCheck[int10] = true;
 }

 if (chunk7 != nullptr) {
 chunk7.lightCheck[int10] = true;
 }

 if (chunk8 != nullptr) {
 chunk8.lightCheck[int10] = true;
 }
 }

 for (int int11 = 0; int11 < IsoPlayer.numPlayers; int11++) {
 LosUtil.cachecleared[int11] = true;
 }

 IsoLightSwitch.chunkLoaded(this);
 }

 void fixObjectAmbientEmittersOnAdjacentChunks(IsoChunk chunk1, IsoChunk chunk0) {
 if (!GameServer.bServer) {
 if (chunk1 != nullptr || chunk0 != nullptr) {
 for (int int0 = 0; int0 < 8; int0++) {
 if (chunk1 != nullptr) {
 for (int int1 = 0; int1 < 10; int1++) {
 IsoGridSquare square0 = chunk1.getGridSquare(0, int1, int0);
 this->fixObjectAmbientEmittersOnSquare(square0, false);
 }
 }

 if (chunk0 != nullptr) {
 for (int int2 = 0; int2 < 10; int2++) {
 IsoGridSquare square1 = chunk0.getGridSquare(int2, 0, int0);
 this->fixObjectAmbientEmittersOnSquare(square1, true);
 }
 }
 }
 }
 }
 }

 void fixObjectAmbientEmittersOnSquare(IsoGridSquare square, bool boolean0) {
 if (square != nullptr && !square.getSpecialObjects().empty()) {
 IsoObject object = square.getDoor(boolean0);
 if (object instanceof IsoDoor && ((IsoDoor)object).isExterior() && !object.hasObjectAmbientEmitter()) {
 object.addObjectAmbientEmitter(new ObjectAmbientEmitters.DoorLogic().init(object);
 }

 IsoWindow window = square.getWindow(boolean0);
 if (window != nullptr && window.isExterior() && !window.hasObjectAmbientEmitter()) {
 window.addObjectAmbientEmitter(new ObjectAmbientEmitters.WindowLogic().init(window);
 }
 }
 }

 void recalcNeighboursNow() {
 IsoCell cell = IsoWorld.instance.CurrentCell;

 for (int int0 = 0; int0 < 10; int0++) {
 for (int int1 = 0; int1 < 10; int1++) {
 for (int int2 = 0; int2 < 8; int2++) {
 IsoGridSquare square0 = this->getGridSquare(int0, int1, int2);
 if (square0 != nullptr) {
 if (int2 > 0 && !square0.getObjects().empty()) {
 square0.EnsureSurroundNotNull();

 for (int int3 = int2 - 1; int3 > 0; int3--) {
 IsoGridSquare square1 = this->getGridSquare(int0, int1, int3);
 if (square1 == nullptr) {
 square1 = IsoGridSquare.getNew(cell, nullptr, this->wx * 10 + int0, this->wy * 10 + int1, int3);
 cell.ConnectNewSquare(square1, false);
 }
 }
 }

 square0.RecalcProperties();
 }
 }
 }
 }

 for (int int4 = 1; int4 < 8; int4++) {
 for (int int5 = -1; int5 < 11; int5++) {
 IsoGridSquare square2 = cell.getGridSquare(this->wx * 10 + int5, this->wy * 10 - 1, int4);
 if (square2 != nullptr && !square2.getObjects().empty()) {
 square2.EnsureSurroundNotNull();
 }

 square2 = cell.getGridSquare(this->wx * 10 + int5, this->wy * 10 + 10, int4);
 if (square2 != nullptr && !square2.getObjects().empty()) {
 square2.EnsureSurroundNotNull();
 }
 }

 for (int int6 = 0; int6 < 10; int6++) {
 IsoGridSquare square3 = cell.getGridSquare(this->wx * 10 - 1, this->wy * 10 + int6, int4);
 if (square3 != nullptr && !square3.getObjects().empty()) {
 square3.EnsureSurroundNotNull();
 }

 square3 = cell.getGridSquare(this->wx * 10 + 10, this->wy * 10 + int6, int4);
 if (square3 != nullptr && !square3.getObjects().empty()) {
 square3.EnsureSurroundNotNull();
 }
 }
 }

 for (int int7 = 0; int7 < 10; int7++) {
 for (int int8 = 0; int8 < 10; int8++) {
 for (int int9 = 0; int9 < 8; int9++) {
 IsoGridSquare square4 = this->getGridSquare(int7, int8, int9);
 if (square4 != nullptr) {
 square4.RecalcAllWithNeighbours(true);
 IsoRoom room = square4.getRoom();
 if (room != nullptr) {
 room.addSquare(square4);
 }
 }
 }
 }
 }

 for (int int10 = 0; int10 < 10; int10++) {
 for (int int11 = 0; int11 < 10; int11++) {
 for (int int12 = 0; int12 < 8; int12++) {
 IsoGridSquare square5 = this->getGridSquare(int10, int11, int12);
 if (square5 != nullptr) {
 square5.propertiesDirty = true;
 }
 }
 }
 }

 IsoLightSwitch.chunkLoaded(this);
 }

 void updateBuildings() {
 }

 static void updatePlayerInBullet() {
 std::vector arrayList = GameServer.getPlayers();
 Bullet.updatePlayerList(arrayList);
 }

 void update() {
 if (!GameServer.bServer) {
 this->checkPhysics();
 }

 if (!this->loadedPhysics) {
 this->loadedPhysics = true;

 for (int int0 = 0; int0 < this->vehicles.size(); int0++) {
 this->vehicles.get(int0).chunk = this;
 }
 }

 if (this->vehiclesForAddToWorld != nullptr) {
 synchronized (this->vehiclesForAddToWorldLock) {
 for (int int1 = 0; int1 < this->vehiclesForAddToWorld.size(); int1++) {
 this->vehiclesForAddToWorld.get(int1).addToWorld();
 }

 this->vehiclesForAddToWorld.clear();
 this->vehiclesForAddToWorld = nullptr;
 }
 }

 this->updateVehicleStory();
 }

 void updateVehicleStory() {
 if (this->bLoaded && this->m_vehicleStorySpawnData != nullptr) {
 IsoMetaChunk metaChunk = IsoWorld.instance.getMetaChunk(this->wx, this->wy);
 if (metaChunk != nullptr) {
 VehicleStorySpawnData vehicleStorySpawnData = this->m_vehicleStorySpawnData;

 for (int int0 = 0; int0 < metaChunk.numZones(); int0++) {
 IsoMetaGrid.Zone zone = metaChunk.getZone(int0);
 if (vehicleStorySpawnData.isValid(zone, this) {
 vehicleStorySpawnData.m_story.randomizeVehicleStory(zone, this);
 zone.hourLastSeen++;
 break;
 }
 }
 }
 }
 }

 void setSquare(int x, int y, int z, IsoGridSquare square) {
 assert square = = nullptr || square.x - this->wx * 10 == x && square.y - this->wy * 10 == y && square.z == z;

 this->squares[z][y * 10 + x] = square;
 if (square != nullptr) {
 square.chunk = this;
 if (square.z > this->maxLevel) {
 this->maxLevel = square.z;
 }
 }
 }

 IsoGridSquare getGridSquare(int x, int y, int z) {
 return x >= 0 && x < 10 && y >= 0 && y < 10 && z < 8 && z >= 0 ? this->squares[z][y * 10 + x] : nullptr;
 }

 IsoRoom getRoom(int roomID) {
 return this->lotheader.getRoom(roomID);
 }

 void removeFromWorld() {
 loadGridSquare.remove(this);
 if (GameClient.bClient && GameClient.instance.bConnected) {
 try {
 GameClient.instance.sendAddedRemovedItems(true);
 } catch (Exception exception0) {
 ExceptionLogger.logException(exception0);
 }
 }

 try {
 MapCollisionData.instance.removeChunkFromWorld(this);
 ZombiePopulationManager.instance.removeChunkFromWorld(this);
 PolygonalMap2.instance.removeChunkFromWorld(this);
 this->collision.clear();
 } catch (Exception exception1) {
 exception1.printStackTrace();
 }

 uint8_t byte0 = 100;

 for (int int0 = 0; int0 < 8; int0++) {
 for (int int1 = 0; int1 < byte0; int1++) {
 IsoGridSquare square = this->squares[int0][int1];
 if (square != nullptr) {
 RainManager.RemoveAllOn(square);
 square.clearWater();
 square.clearPuddles();
 if (square.getRoom() != nullptr) {
 square.getRoom().removeSquare(square);
 }

 if (square.zone != nullptr) {
 square.zone.removeSquare(square);
 }

 std::vector arrayList = square.getMovingObjects();

 for (int int2 = 0; int2 < arrayList.size(); int2++) {
 IsoMovingObject movingObject0 = (IsoMovingObject)arrayList.get(int2);
 if (movingObject0 instanceof IsoSurvivor) {
 IsoWorld.instance.CurrentCell.getSurvivorList().remove(movingObject0);
 movingObject0.Despawn();
 }

 movingObject0.removeFromWorld();
 movingObject0.current = movingObject0.last = nullptr;
 if (!arrayList.contains(movingObject0) {
 int2--;
 }
 }

 arrayList.clear();

 for (int int3 = 0; int3 < square.getObjects().size(); int3++) {
 IsoObject object = square.getObjects().get(int3);
 object.removeFromWorld();
 }

 for (int int4 = 0; int4 < square.getStaticMovingObjects().size(); int4++) {
 IsoMovingObject movingObject1 = square.getStaticMovingObjects().get(int4);
 movingObject1.removeFromWorld();
 }

 this->disconnectFromAdjacentChunks(square);
 square.softClear();
 square.chunk = nullptr;
 }
 }
 }

 for (int int5 = 0; int5 < this->vehicles.size(); int5++) {
 BaseVehicle vehicle = this->vehicles.get(int5);
 if (IsoWorld.instance.CurrentCell.getVehicles().contains(vehicle) || IsoWorld.instance.CurrentCell.addVehicles.contains(vehicle) {
 DebugLog.log("IsoChunk.removeFromWorld: vehicle wasn't removed from world id=" + vehicle.VehicleID);
 vehicle.removeFromWorld();
 }
 }
 }

 void disconnectFromAdjacentChunks(IsoGridSquare square) {
 int int0 = square.x % 10;
 int int1 = square.y % 10;
 if (int0 == 0 || int0 == 9 || int1 == 0 || int1 == 9) {
 int int2 = IsoDirections.N.index();
 int int3 = IsoDirections.S.index();
 if (square.nav[int2] != nullptr && square.nav[int2].chunk != square.chunk) {
 square.nav[int2].nav[int3] = nullptr;
 square.nav[int2].s = nullptr;
 }

 int2 = IsoDirections.NW.index();
 int3 = IsoDirections.SE.index();
 if (square.nav[int2] != nullptr && square.nav[int2].chunk != square.chunk) {
 square.nav[int2].nav[int3] = nullptr;
 square.nav[int2].se = nullptr;
 }

 int2 = IsoDirections.W.index();
 int3 = IsoDirections.E.index();
 if (square.nav[int2] != nullptr && square.nav[int2].chunk != square.chunk) {
 square.nav[int2].nav[int3] = nullptr;
 square.nav[int2].e = nullptr;
 }

 int2 = IsoDirections.SW.index();
 int3 = IsoDirections.NE.index();
 if (square.nav[int2] != nullptr && square.nav[int2].chunk != square.chunk) {
 square.nav[int2].nav[int3] = nullptr;
 square.nav[int2].ne = nullptr;
 }

 int2 = IsoDirections.S.index();
 int3 = IsoDirections.N.index();
 if (square.nav[int2] != nullptr && square.nav[int2].chunk != square.chunk) {
 square.nav[int2].nav[int3] = nullptr;
 square.nav[int2].n = nullptr;
 }

 int2 = IsoDirections.SE.index();
 int3 = IsoDirections.NW.index();
 if (square.nav[int2] != nullptr && square.nav[int2].chunk != square.chunk) {
 square.nav[int2].nav[int3] = nullptr;
 square.nav[int2].nw = nullptr;
 }

 int2 = IsoDirections.E.index();
 int3 = IsoDirections.W.index();
 if (square.nav[int2] != nullptr && square.nav[int2].chunk != square.chunk) {
 square.nav[int2].nav[int3] = nullptr;
 square.nav[int2].w = nullptr;
 }

 int2 = IsoDirections.NE.index();
 int3 = IsoDirections.SW.index();
 if (square.nav[int2] != nullptr && square.nav[int2].chunk != square.chunk) {
 square.nav[int2].nav[int3] = nullptr;
 square.nav[int2].sw = nullptr;
 }
 }
 }

 void doReuseGridsquares() {
 uint8_t byte0 = 100;

 for (int int0 = 0; int0 < 8; int0++) {
 for (int int1 = 0; int1 < byte0; int1++) {
 IsoGridSquare square = this->squares[int0][int1];
 if (square != nullptr) {
 LuaEventManager.triggerEvent("ReuseGridsquare", square);

 for (int int2 = 0; int2 < square.getObjects().size(); int2++) {
 IsoObject object = square.getObjects().get(int2);
 if (object instanceof IsoTree) {
 object.reset();
 CellLoader.isoTreeCache.add((IsoTree)object);
 } else if (object instanceof IsoObject && object.getObjectName() == "IsoObject")) {
 object.reset();
 CellLoader.isoObjectCache.add(object);
 } else {
 object.reuseGridSquare();
 }
 }

 square.discard();
 this->squares[int0][int1] = nullptr;
 }
 }
 }

 this->resetForStore();

 assert !IsoChunkMap.chunkStore.contains(this);

 IsoChunkMap.chunkStore.add(this);
 }

 static int bufferSize(int int0) {
 return (int0 + 65536 - 1) / 65536 * 65536;
 }

 static ByteBuffer ensureCapacity(ByteBuffer byteBuffer, int int0) {
 if (byteBuffer == nullptr || byteBuffer.capacity() < int0) {
 byteBuffer = ByteBuffer.allocate(bufferSize(int0);
 }

 return byteBuffer;
 }

 static ByteBuffer ensureCapacity(ByteBuffer byteBuffer0) {
 if (byteBuffer0 == nullptr) {
 return ByteBuffer.allocate(65536);
 } else if (byteBuffer0.capacity() - byteBuffer0.position() < 65536) {
 ByteBuffer byteBuffer1 = ensureCapacity(nullptr, byteBuffer0.position() + 65536);
 return byteBuffer1.put(byteBuffer0.array(), 0, byteBuffer0.position());
 } else {
 return byteBuffer0;
 }
 }

 void LoadFromDisk() {
 this->LoadFromDiskOrBuffer(nullptr);
 }

 void LoadFromDiskOrBuffer(ByteBuffer bb) {
 sanityCheck.beginLoad(this);

 try {
 ByteBuffer byteBuffer;
 if (bb == nullptr) {
 SliceBufferLoad = SafeRead(prefix, this->wx, this->wy, SliceBufferLoad);
 byteBuffer = SliceBufferLoad;
 } else {
 byteBuffer = bb;
 }

 int int0 = this->wx * 10;
 int int1 = this->wy * 10;
 int0 /= 300;
 int1 /= 300;
 std::string string = ChunkMapFilenames.instance.getHeader(int0, int1);
 if (IsoLot.InfoHeaders.containsKey(string) {
 this->lotheader = IsoLot.InfoHeaders.get(string);
 }

 IsoCell.wx = this->wx;
 IsoCell.wy = this->wy;
 bool boolean0 = byteBuffer.get() == 1;
 int int2 = byteBuffer.getInt();
 if (boolean0) {
 DebugLog.log("WorldVersion = " + int2 + ", debug = " + boolean0);
 }

 if (int2 > 195) {
 throw RuntimeException("unknown world version " + int2 + " while reading chunk " + this->wx + "," + this->wy);
 }

 this->bFixed2x = int2 >= 85;
 if (int2 >= 61) {
 int int3 = byteBuffer.getInt();
 sanityCheck.checkLength(int3, byteBuffer.limit());
 long long0 = byteBuffer.getLong();
 crcLoad.reset();
 crcLoad.update(byteBuffer.array(), 17, byteBuffer.limit() - 1 - 4 - 4 - 8);
 sanityCheck.checkCRC(long0, crcLoad.getValue());
 }

 int int4 = 0;
 if (GameClient.bClient || GameServer.bServer) {
 int4 = ServerOptions.getInstance().BloodSplatLifespanDays.getValue();
 }

 float float0 = (float)GameTime.getInstance().getWorldAgeHours();
 int int5 = byteBuffer.getInt();

 for (int int6 = 0; int6 < int5; int6++) {
 IsoFloorBloodSplat floorBloodSplat = new IsoFloorBloodSplat();
 floorBloodSplat.load(byteBuffer, int2);
 if (floorBloodSplat.worldAge > float0) {
 floorBloodSplat.worldAge = float0;
 }

 if (int4 <= 0 || !(float0 - floorBloodSplat.worldAge >= int4 * 24) {
 if (int2 < 73 && floorBloodSplat.Type < 8) {
 floorBloodSplat.index = ++this->nextSplatIndex;
 }

 if (floorBloodSplat.Type < 8) {
 this->nextSplatIndex = floorBloodSplat.index % 10;
 }

 this->FloorBloodSplats.add(floorBloodSplat);
 }
 }

 IsoMetaGrid metaGrid = IsoWorld.instance.getMetaGrid();
 uint8_t byte0 = 0;

 for (int int7 = 0; int7 < 10; int7++) {
 for (int int8 = 0; int8 < 10; int8++) {
 byte0 = byteBuffer.get();

 for (int int9 = 0; int9 < 8; int9++) {
 IsoGridSquare square0 = nullptr;
 bool boolean1 = false;
 if ((byte0 & 1 << int9) != 0) {
 boolean1 = true;
 }

 if (boolean1) {
 if (square0 == nullptr) {
 if (IsoGridSquare.loadGridSquareCache != nullptr) {
 square0 = IsoGridSquare.getNew(
 IsoGridSquare.loadGridSquareCache, IsoWorld.instance.CurrentCell, nullptr, int7 + this->wx * 10, int8 + this->wy * 10, int9
 );
 } else {
 square0 = IsoGridSquare.getNew(IsoWorld.instance.CurrentCell, nullptr, int7 + this->wx * 10, int8 + this->wy * 10, int9);
 }
 }

 square0.chunk = this;
 if (this->lotheader != nullptr) {
 RoomDef roomDef = metaGrid.getRoomAt(square0.x, square0.y, square0.z);
 int int10 = roomDef != nullptr ? roomDef.ID : -1;
 square0.setRoomID(int10);
 roomDef = metaGrid.getEmptyOutsideAt(square0.x, square0.y, square0.z);
 if (roomDef != nullptr) {
 IsoRoom room = this->getRoom(roomDef.ID);
 square0.roofHideBuilding = room == nullptr ? nullptr : room.building;
 }
 }

 square0.ResetIsoWorldRegion();
 this->setSquare(int7, int8, int9, square0);
 }

 if (boolean1 && square0 != nullptr) {
 square0.load(byteBuffer, int2, boolean0);
 square0.FixStackableObjects();
 if (this->jobType == IsoChunk.JobType.SoftReset) {
 if (!square0.getStaticMovingObjects().empty()) {
 square0.getStaticMovingObjects().clear();
 }

 for (int int11 = 0; int11 < square0.getObjects().size(); int11++) {
 IsoObject object0 = square0.getObjects().get(int11);
 object0.softReset();
 if (object0.getObjectIndex() == -1) {
 int11--;
 }
 }

 square0.setOverlayDone(false);
 }
 }
 }
 }
 }

 if (int2 >= 45) {
 this->getErosionData().load(byteBuffer, int2);
 this->getErosionData().set(this);
 }

 if (int2 >= 127) {
 short short0 = byteBuffer.getShort();
 if (short0 > 0 && this->generatorsTouchingThisChunk == nullptr) {
 this->generatorsTouchingThisChunk = std::make_unique<ArrayList<>>();
 }

 if (this->generatorsTouchingThisChunk != nullptr) {
 this->generatorsTouchingThisChunk.clear();
 }

 for (int int12 = 0; int12 < short0; int12++) {
 int int13 = byteBuffer.getInt();
 int int14 = byteBuffer.getInt();
 uint8_t byte1 = byteBuffer.get();
 IsoGameCharacter.Location location = new IsoGameCharacter.Location(int13, int14, byte1);
 this->generatorsTouchingThisChunk.add(location);
 }
 }

 this->vehicles.clear();
 if (!GameClient.bClient) {
 if (int2 >= 91) {
 short short1 = byteBuffer.getShort();

 for (int int15 = 0; int15 < short1; int15++) {
 uint8_t byte2 = byteBuffer.get();
 uint8_t byte3 = byteBuffer.get();
 uint8_t byte4 = byteBuffer.get();
 IsoObject object1 = IsoObject.factoryFromFileInput(IsoWorld.instance.CurrentCell, byteBuffer);
 if (object1 != nullptr && object1 instanceof BaseVehicle) {
 IsoGridSquare square1 = this->getGridSquare(byte2, byte3, byte4);
 object1.square = square1;
 ((IsoMovingObject)object1).current = square1;

 try {
 object1.load(byteBuffer, int2, boolean0);
 this->vehicles.add((BaseVehicle)object1);
 addFromCheckedVehicles((BaseVehicle)object1);
 if (this->jobType == IsoChunk.JobType.SoftReset) {
 object1.softReset();
 }
 } catch (Exception exception) {
 throw RuntimeException(exception);
 }
 }
 }
 }

 if (int2 >= 125) {
 this->lootRespawnHour = byteBuffer.getInt();
 }

 if (int2 >= 160) {
 uint8_t byte5 = byteBuffer.get();

 for (int int16 = 0; int16 < byte5; int16++) {
 int int17 = byteBuffer.getInt();
 this->addSpawnedRoom(int17);
 }
 }
 }
 } finally {
 sanityCheck.endLoad(this);
 this->bFixed2x = true;
 }

 if (this->getGridSquare(0, 0, 0) == nullptr && this->getGridSquare(9, 9, 0) == nullptr) {
 throw RuntimeException("black chunk " + this->wx + "," + this->wy);
 }
 }

 void doLoadGridsquare() {
 if (this->jobType == IsoChunk.JobType.SoftReset) {
 this->m_spawnedRooms.clear();
 }

 if (!GameServer.bServer) {
 this->loadInMainThread();
 }

 if (this->addZombies && !VehiclesDB2.instance.isChunkSeen(this->wx, this->wy) {
 try {
 this->AddVehicles();
 } catch (Throwable throwable0) {
 ExceptionLogger.logException(throwable0);
 }
 }

 this->AddZombieZoneStory();
 VehiclesDB2.instance.setChunkSeen(this->wx, this->wy);
 if (this->addZombies) {
 if (IsoWorld.instance.getTimeSinceLastSurvivorInHorde() > 0) {
 IsoWorld.instance.setTimeSinceLastSurvivorInHorde(IsoWorld.instance.getTimeSinceLastSurvivorInHorde() - 1);
 }

 this->addSurvivorInHorde(false);
 }

 this->update();
 if (!GameServer.bServer) {
 FliesSound.instance.chunkLoaded(this);
 NearestWalls.chunkLoaded(this);
 }

 if (this->addZombies) {
 int int0 = 5 + SandboxOptions.instance.TimeSinceApo.getValue();
 int0 = Math.min(20, int0);
 if (Rand.Next(int0) == 0) {
 this->AddCorpses(this->wx, this->wy);
 }

 if (Rand.Next(int0 * 2) == 0) {
 this->AddBlood(this->wx, this->wy);
 }
 }

 LoadGridsquarePerformanceWorkaround.init(this->wx, this->wy);
 tempBuildings.clear();
 if (!GameClient.bClient) {
 for (int int1 = 0; int1 < this->vehicles.size(); int1++) {
 BaseVehicle vehicle = this->vehicles.get(int1);
 if (!vehicle.addedToWorld && VehiclesDB2.instance.isVehicleLoaded(vehicle) {
 vehicle.removeFromSquare();
 this->vehicles.remove(int1);
 int1--;
 } else {
 if (!vehicle.addedToWorld) {
 vehicle.addToWorld();
 }

 if (vehicle.sqlID == -1) {
 assert false;

 if (vehicle.square == nullptr) {
 float float0 = 5.0E-4F;
 int int2 = this->wx * 10;
 int int3 = this->wy * 10;
 int int4 = int2 + 10;
 int int5 = int3 + 10;
 float float1 = PZMath.clamp(vehicle.x, int2 + float0, int4 - float0);
 float float2 = PZMath.clamp(vehicle.y, int3 + float0, int5 - float0);
 vehicle.square = this->getGridSquare((int)float1 - this->wx * 10, (int)float2 - this->wy * 10, 0);
 }

 VehiclesDB2.instance.addVehicle(vehicle);
 }
 }
 }
 }

 this->m_treeCount = 0;
 this->m_scavengeZone = nullptr;
 this->m_numberOfWaterTiles = 0;

 for (int int6 = 0; int6 <= this->maxLevel; int6++) {
 for (int int7 = 0; int7 < 10; int7++) {
 for (int int8 = 0; int8 < 10; int8++) {
 IsoGridSquare square = this->getGridSquare(int7, int8, int6);
 if (square != nullptr && !square.getObjects().empty()) {
 for (int int9 = 0; int9 < square.getObjects().size(); int9++) {
 IsoObject object = square.getObjects().get(int9);
 object.addToWorld();
 if (int6 == 0 && object.getSprite() != nullptr && object.getSprite().getProperties().Is(IsoFlagType.water) {
 this->m_numberOfWaterTiles++;
 }
 }

 if (square.HasTree()) {
 this->m_treeCount++;
 }

 if (this->jobType != IsoChunk.JobType.SoftReset) {
 ErosionMain.LoadGridsquare(square);
 }

 if (this->addZombies) {
 MapObjects.newGridSquare(square);
 }

 MapObjects.loadGridSquare(square);
 LuaEventManager.triggerEvent("LoadGridsquare", square);
 LoadGridsquarePerformanceWorkaround.LoadGridsquare(square);
 }

 if (square != nullptr && !square.getStaticMovingObjects().empty()) {
 for (int int10 = 0; int10 < square.getStaticMovingObjects().size(); int10++) {
 IsoMovingObject movingObject = square.getStaticMovingObjects().get(int10);
 movingObject.addToWorld();
 }
 }

 if (square != nullptr && square.getBuilding() != nullptr && !tempBuildings.contains(square.getBuilding())) {
 tempBuildings.add(square.getBuilding());
 }
 }
 }
 }

 if (this->jobType != IsoChunk.JobType.SoftReset) {
 ErosionMain.ChunkLoaded(this);
 }

 if (this->jobType != IsoChunk.JobType.SoftReset) {
 SGlobalObjects.chunkLoaded(this->wx, this->wy);
 }

 ReanimatedPlayers.instance.addReanimatedPlayersToChunk(this);
 if (this->jobType != IsoChunk.JobType.SoftReset) {
 MapCollisionData.instance.addChunkToWorld(this);
 ZombiePopulationManager.instance.addChunkToWorld(this);
 PolygonalMap2.instance.addChunkToWorld(this);
 IsoGenerator.chunkLoaded(this);
 LootRespawn.chunkLoaded(this);
 }

 if (!GameServer.bServer) {
 std::vector arrayList = IsoWorld.instance.CurrentCell.roomLights;

 for (int int11 = 0; int11 < this->roomLights.size(); int11++) {
 IsoRoomLight roomLight = this->roomLights.get(int11);
 if (!arrayList.contains(roomLight) {
 arrayList.add(roomLight);
 }
 }
 }

 this->roomLights.clear();
 if (this->jobType != IsoChunk.JobType.SoftReset) {
 this->randomizeBuildingsEtc();
 }

 this->checkAdjacentChunks();

 try {
 if (GameServer.bServer && this->jobType != IsoChunk.JobType.SoftReset) {
 for (int int12 = 0; int12 < GameServer.udpEngine.connections.size(); int12++) {
 UdpConnection udpConnection = GameServer.udpEngine.connections.get(int12);
 if (!udpConnection.chunkObjectState.empty()) {
 for (byte byte0 = 0; byte0 < udpConnection.chunkObjectState.size(); byte0 += 2) {
 short short0 = udpConnection.chunkObjectState.get(byte0);
 short short1 = udpConnection.chunkObjectState.get(byte0 + 1);
 if (short0 == this->wx && short1 == this->wy) {
 udpConnection.chunkObjectState.remove(byte0, 2);
 byte0 -= 2;
 ByteBufferWriter byteBufferWriter0 = udpConnection.startPacket();
 PacketTypes.PacketType.ChunkObjectState.doPacket(byteBufferWriter0);
 byteBufferWriter0.putShort((short)this->wx);
 byteBufferWriter0.putShort((short)this->wy);

 try {
 if (this->saveObjectState(byteBufferWriter0.bb) {
 PacketTypes.PacketType.ChunkObjectState.send(udpConnection);
 } else {
 udpConnection.cancelPacket();
 }
 } catch (Throwable throwable1) {
 throwable1.printStackTrace();
 udpConnection.cancelPacket();
 }
 }
 }
 }
 }
 }

 if (GameClient.bClient) {
 ByteBufferWriter byteBufferWriter1 = GameClient.connection.startPacket();
 PacketTypes.PacketType.ChunkObjectState.doPacket(byteBufferWriter1);
 byteBufferWriter1.putShort((short)this->wx);
 byteBufferWriter1.putShort((short)this->wy);
 PacketTypes.PacketType.ChunkObjectState.send(GameClient.connection);
 }
 } catch (Throwable throwable2) {
 ExceptionLogger.logException(throwable2);
 }
 }

 void randomizeBuildingsEtc() {
 tempRoomDefs.clear();
 IsoWorld.instance.MetaGrid.getRoomsIntersecting(this->wx * 10 - 1, this->wy * 10 - 1, 11, 11, tempRoomDefs);

 for (int int0 = 0; int0 < tempRoomDefs.size(); int0++) {
 IsoRoom room0 = tempRoomDefs.get(int0).getIsoRoom();
 if (room0 != nullptr) {
 IsoBuilding building0 = room0.getBuilding();
 if (!tempBuildings.contains(building0) {
 tempBuildings.add(building0);
 }
 }
 }

 for (int int1 = 0; int1 < tempBuildings.size(); int1++) {
 IsoBuilding building1 = tempBuildings.get(int1);
 if (!GameClient.bClient && building1.def != nullptr && building1.def.isFullyStreamedIn()) {
 StashSystem.doBuildingStash(building1.def);
 }

 RandomizedBuildingBase.ChunkLoaded(building1);
 }

 if (!GameClient.bClient && !tempBuildings.empty()) {
 for (int int2 = 0; int2 < tempBuildings.size(); int2++) {
 IsoBuilding building2 = tempBuildings.get(int2);

 for (int int3 = 0; int3 < building2.Rooms.size(); int3++) {
 IsoRoom room1 = building2.Rooms.get(int3);
 if (room1.def.bDoneSpawn && !this->isSpawnedRoom(room1.def.ID) && room1.def.intersects(this->wx * 10, this->wy * 10, 10, 10) {
 this->addSpawnedRoom(room1.def.ID);
 VirtualZombieManager.instance.addIndoorZombiesToChunk(this, room1);
 }
 }
 }
 }
 }

 void checkAdjacentChunks() {
 IsoCell cell = IsoWorld.instance.CurrentCell;

 for (int int0 = -1; int0 <= 1; int0++) {
 for (int int1 = -1; int1 <= 1; int1++) {
 if (int1 != 0 || int0 != 0) {
 IsoChunk chunk0 = cell.getChunk(this->wx + int1, this->wy + int0);
 if (chunk0 != nullptr) {
 chunk0.m_adjacentChunkLoadedCounter++;
 }
 }
 }
 }
 }

 void AddZombieZoneStory() {
 IsoMetaChunk metaChunk = IsoWorld.instance.getMetaChunk(this->wx, this->wy);
 if (metaChunk != nullptr) {
 for (int int0 = 0; int0 < metaChunk.numZones(); int0++) {
 IsoMetaGrid.Zone zone = metaChunk.getZone(int0);
 RandomizedZoneStoryBase.isValidForStory(zone, false);
 }
 }
 }

 void setCache() {
 IsoWorld.instance.CurrentCell.setCacheChunk(this);
 }

 private static IsoChunk.ChunkLock acquireLock(int int2, int int1) {
 synchronized (Locks) {
 for (int int0 = 0; int0 < Locks.size(); int0++) {
 if (Locks.get(int0).wx == int2 && Locks.get(int0).wy == int1) {
 return Locks.get(int0).ref();
 }
 }

 IsoChunk.ChunkLock chunkLock = FreeLocks.empty() ? new IsoChunk.ChunkLock(int2, int1) : FreeLocks.pop().set(int2, int1);
 Locks.add(chunkLock);
 return chunkLock.ref();
 }
 }

 static void releaseLock(IsoChunk.ChunkLock chunkLock) {
 synchronized (Locks) {
 if (chunkLock.deref() == 0) {
 Locks.remove(chunkLock);
 FreeLocks.push(chunkLock);
 }
 }
 }

 void setCacheIncludingNull() {
 for (int int0 = 0; int0 < 8; int0++) {
 for (int int1 = 0; int1 < 10; int1++) {
 for (int int2 = 0; int2 < 10; int2++) {
 IsoGridSquare square = this->getGridSquare(int1, int2, int0);
 IsoWorld.instance.CurrentCell.setCacheGridSquare(this->wx * 10 + int1, this->wy * 10 + int2, int0, square);
 }
 }
 }
 }

 void Save(bool bSaveQuit) {
 if (!Core.getInstance().isNoSave() && !GameClient.bClient) {
 synchronized (WriteLock) {
 sanityCheck.beginSave(this);

 try {
 File file = ChunkMapFilenames.instance.getDir(Core.GameSaveWorld);
 if (!file.exists()) {
 file.mkdir();
 }

 SliceBuffer = this->Save(SliceBuffer, crcSave);
 if (!GameClient.bClient && !GameServer.bServer) {
 SafeWrite(prefix, this->wx, this->wy, SliceBuffer);
 } else {
 long long0 = ChunkChecksum.getChecksumIfExists(this->wx, this->wy);
 crcSave.reset();
 crcSave.update(SliceBuffer.array(), 0, SliceBuffer.position());
 if (long0 != crcSave.getValue()) {
 ChunkChecksum.setChecksum(this->wx, this->wy, crcSave.getValue());
 SafeWrite(prefix, this->wx, this->wy, SliceBuffer);
 }
 }

 if (!bSaveQuit && !GameServer.bServer) {
 if (this->jobType != IsoChunk.JobType.Convert) {
 WorldReuserThread.instance.addReuseChunk(this);
 } else {
 this->doReuseGridsquares();
 }
 }
 } finally {
 sanityCheck.endSave(this);
 }
 }
 } else {
 if (!bSaveQuit && !GameServer.bServer && this->jobType != IsoChunk.JobType.Convert) {
 WorldReuserThread.instance.addReuseChunk(this);
 }
 }
 }

 static void SafeWrite(const std::string& _prefix, int _wx, int _wy, ByteBuffer bb) {
 IsoChunk.ChunkLock chunkLock = acquireLock(_wx, _wy);
 chunkLock.lockForWriting();

 try {
 File file = ChunkMapFilenames.instance.getFilename(_wx, _wy);
 sanityCheck.beginSaveFile(file.getAbsolutePath());

 try (FileOutputStream fileOutputStream = new FileOutputStream(file) {
 fileOutputStream.getChannel().truncate(0L);
 fileOutputStream.write(bb.array(), 0, bb.position());
 } finally {
 sanityCheck.endSaveFile();
 }
 } finally {
 chunkLock.unlockForWriting();
 releaseLock(chunkLock);
 }
 }

 static ByteBuffer SafeRead(const std::string& _prefix, int _wx, int _wy, ByteBuffer bb) {
 IsoChunk.ChunkLock chunkLock = acquireLock(_wx, _wy);
 chunkLock.lockForReading();

 try {
 File file = ChunkMapFilenames.instance.getFilename(_wx, _wy);
 if (file == nullptr) {
 file = ZomboidFileSystem.instance.getFileInCurrentSave(_prefix + _wx + "_" + _wy + ".bin");
 }

 sanityCheck.beginLoadFile(file.getAbsolutePath());

 try (FileInputStream fileInputStream = new FileInputStream(file) {
 bb = ensureCapacity(bb, (int)file.length());
 bb.clear();
 int int0 = fileInputStream.read(bb.array());
 bb.limit(PZMath.max(int0, 0);
 } finally {
 sanityCheck.endLoadFile(file.getAbsolutePath());
 }
 } finally {
 chunkLock.unlockForReading();
 releaseLock(chunkLock);
 }

 return bb;
 }

 void SaveLoadedChunk(ClientChunkRequest.Chunk ccrc, CRC32 crc32) {
 ccrc.bb = this->Save(ccrc.bb, crc32);
 }

 static bool IsDebugSave() {
 return !Core.bDebug ? false : false;
 }

 ByteBuffer Save(ByteBuffer bb, CRC32 crc) {
 bb.rewind();
 bb = ensureCapacity(bb);
 bb.clear();
 bb.put((byte)(IsDebugSave() ? 1 : 0);
 bb.putInt(195);
 bb.putInt(0);
 bb.putLong(0L);
 int int0 = Math.min(1000, this->FloorBloodSplats.size());
 int int1 = this->FloorBloodSplats.size() - int0;
 bb.putInt(int0);

 for (int int2 = int1; int2 < this->FloorBloodSplats.size(); int2++) {
 IsoFloorBloodSplat floorBloodSplat = this->FloorBloodSplats.get(int2);
 floorBloodSplat.save(bb);
 }

 int int3 = bb.position();
 uint8_t byte0 = 0;
 int int4 = 0;
 int int5 = 0;

 for (int int6 = 0; int6 < 10; int6++) {
 for (int int7 = 0; int7 < 10; int7++) {
 byte0 = 0;
 int4 = bb.position();
 bb.put(byte0);

 for (int int8 = 0; int8 < 8; int8++) {
 IsoGridSquare square = this->getGridSquare(int6, int7, int8);
 bb = ensureCapacity(bb);
 if (square != nullptr && square.shouldSave()) {
 byte0 = (byte)(byte0 | 1 << int8);
 int int9 = bb.position();

 while (true) {
 try {
 square.save(bb, nullptr, IsDebugSave());
 break;
 } catch (BufferOverflowException bufferOverflowException) {
 DebugLog.log("IsoChunk.Save: BufferOverflowException, growing ByteBuffer");
 bb = ensureCapacity(bb);
 bb.position(int9);
 }
 }
 }
 }

 int5 = bb.position();
 bb.position(int4);
 bb.put(byte0);
 bb.position(int5);
 }
 }

 bb = ensureCapacity(bb);
 this->getErosionData().save(bb);
 if (this->generatorsTouchingThisChunk == nullptr) {
 bb.putShort((short)0);
 } else {
 bb.putShort((short)this->generatorsTouchingThisChunk.size());

 for (int int10 = 0; int10 < this->generatorsTouchingThisChunk.size(); int10++) {
 IsoGameCharacter.Location location = this->generatorsTouchingThisChunk.get(int10);
 bb.putInt(location.x);
 bb.putInt(location.y);
 bb.put((byte)location.z);
 }
 }

 bb.putShort((short)0);
 if ((!GameServer.bServer || GameServer.bSoftReset) && !GameClient.bClient && !GameWindow.bLoadedAsClient) {
 VehiclesDB2.instance.unloadChunk(this);
 }

 if (GameClient.bClient) {
 int int11 = ServerOptions.instance.HoursForLootRespawn.getValue();
 if (int11 > 0 && !(GameTime.getInstance().getWorldAgeHours() < int11) {
 this->lootRespawnHour = 7 + (int)(GameTime.getInstance().getWorldAgeHours() / int11) * int11;
 } else {
 this->lootRespawnHour = -1;
 }
 }

 bb.putInt(this->lootRespawnHour);

 assert this->m_spawnedRooms.size() <= 127;

 bb.put((byte)this->m_spawnedRooms.size());

 for (int int12 = 0; int12 < this->m_spawnedRooms.size(); int12++) {
 bb.putInt(this->m_spawnedRooms.get(int12);
 }

 int int13 = bb.position();
 crc.reset();
 crc.update(bb.array(), 17, int13 - 1 - 4 - 4 - 8);
 bb.position(5);
 bb.putInt(int13);
 bb.putLong(crc.getValue());
 bb.position(int13);
 return bb;
 }

 bool saveObjectState(ByteBuffer bb) {
 bool boolean0 = true;

 for (int int0 = 0; int0 < 8; int0++) {
 for (int int1 = 0; int1 < 10; int1++) {
 for (int int2 = 0; int2 < 10; int2++) {
 IsoGridSquare square = this->getGridSquare(int2, int1, int0);
 if (square != nullptr) {
 int int3 = square.getObjects().size();
 IsoObject[] objects = square.getObjects().getElements();

 for (int int4 = 0; int4 < int3; int4++) {
 IsoObject object = objects[int4];
 int int5 = bb.position();
 bb.position(int5 + 2 + 2 + 4 + 2);
 int int6 = bb.position();
 object.saveState(bb);
 int int7 = bb.position();
 if (int7 > int6) {
 bb.position(int5);
 bb.putShort((short)(int2 + int1 * 10 + int0 * 10 * 10);
 bb.putShort((short)int4);
 bb.putInt(object.getObjectName().hashCode());
 bb.putShort((short)(int7 - int6);
 bb.position(int7);
 boolean0 = false;
 } else {
 bb.position(int5);
 }
 }
 }
 }
 }
 }

 if (boolean0) {
 return false;
 } else {
 bb.putShort((short)-1);
 return true;
 }
 }

 void loadObjectState(ByteBuffer bb) {
 for (short short0 = bb.getShort(); short0 != -1; short0 = bb.getShort()) {
 int int0 = short0 % 10;
 int int1 = short0 / 100;
 int int2 = (short0 - int1 * 10 * 10) / 10;
 short short1 = bb.getShort();
 int int3 = bb.getInt();
 short short2 = bb.getShort();
 int int4 = bb.position();
 IsoGridSquare square = this->getGridSquare(int0, int2, int1);
 if (square != nullptr && short1 >= 0 && short1 < square.getObjects().size()) {
 IsoObject object = square.getObjects().get(short1);
 if (int3 == object.getObjectName().hashCode()) {
 object.loadState(bb);

 assert bb.position() == int4 + short2;
 } else {
 bb.position(int4 + short2);
 }
 } else {
 bb.position(int4 + short2);
 }
 }
 }

 void Blam(int _wx, int _wy) {
 for (int int0 = 0; int0 < 8; int0++) {
 for (int int1 = 0; int1 < 10; int1++) {
 for (int int2 = 0; int2 < 10; int2++) {
 this->setSquare(int1, int2, int0, nullptr);
 }
 }
 }

 this->blam = true;
 }

 void BackupBlam(int int1, int int0, std::exception exception0) {
 File file0 = ZomboidFileSystem.instance.getFileInCurrentSave("blam");
 file0.mkdirs();

 try {
 File file1 = new File(file0 + File.separator + "map_" + int1 + "_" + int0 + "_error.txt");
 FileOutputStream fileOutputStream = new FileOutputStream(file1);
 PrintStream printStream = new PrintStream(fileOutputStream);
 exception0.printStackTrace(printStream);
 printStream.close();
 } catch (Exception exception1) {
 exception1.printStackTrace();
 }

 File file2 = ZomboidFileSystem.instance.getFileInCurrentSave("map_" + int1 + "_" + int0 + ".bin");
 if (file2.exists()) {
 File file3 = new File(file0.getPath() + File.separator + "map_" + int1 + "_" + int0 + ".bin");

 try {
 copyFile(file2, file3);
 } catch (Exception exception2) {
 exception2.printStackTrace();
 }
 }
 }

 static void copyFile(File file1, File file0) {
 if (!file0.exists()) {
 file0.createNewFile();
 }

 FileChannel fileChannel0 = nullptr;
 FileChannel fileChannel1 = nullptr;

 try {
 fileChannel0 = new FileInputStream(file1).getChannel();
 fileChannel1 = new FileOutputStream(file0).getChannel();
 fileChannel1.transferFrom(fileChannel0, 0L, fileChannel0.size());
 } finally {
 if (fileChannel0 != nullptr) {
 fileChannel0.close();
 }

 if (fileChannel1 != nullptr) {
 fileChannel1.close();
 }
 }
 }

 public ErosionData.Chunk getErosionData() {
 if (this->erosion == nullptr) {
 this->erosion = new ErosionData.Chunk();
 }

 return this->erosion;
 }

 static int newtiledefinitions(int int1, int int0) {
 uint8_t byte0 = 1;
 return byte0 * 100 * 1000 + 10000 + int1 * 1000 + int0;
 }

 static int Fix2x(IsoGridSquare square, int spriteID) {
 if (square == nullptr || square.chunk == nullptr) {
 return spriteID;
 } else if (square.chunk.bFixed2x) {
 return spriteID;
 } else {
 std::unordered_map hashMap = IsoSpriteManager.instance.NamedMap;
 if (spriteID >= newtiledefinitions(140, 48) && spriteID <= newtiledefinitions(140, 51) {
 return -1;
 } else if (spriteID >= newtiledefinitions(8, 14) && spriteID <= newtiledefinitions(8, 71) && spriteID % 8 >= 6) {
 return -1;
 } else if (spriteID == newtiledefinitions(92, 2) {
 return spriteID + 20;
 } else if (spriteID == newtiledefinitions(92, 20) {
 return spriteID + 1;
 } else if (spriteID == newtiledefinitions(92, 21) {
 return spriteID - 1;
 } else if (spriteID >= newtiledefinitions(92, 26) && spriteID <= newtiledefinitions(92, 29) {
 return spriteID + 6;
 } else if (spriteID == newtiledefinitions(11, 16) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(11, 17) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(11, 18) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(11, 19) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(11, 24) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(11, 25) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(27, 42) {
 return spriteID + 1;
 } else if (spriteID == newtiledefinitions(27, 43) {
 return spriteID - 1;
 } else if (spriteID == newtiledefinitions(27, 44) {
 return spriteID + 3;
 } else if (spriteID == newtiledefinitions(27, 47) {
 return spriteID - 2;
 } else if (spriteID == newtiledefinitions(27, 45) {
 return spriteID + 1;
 } else if (spriteID == newtiledefinitions(27, 46) {
 return spriteID - 2;
 } else if (spriteID == newtiledefinitions(34, 4) {
 return spriteID + 1;
 } else if (spriteID == newtiledefinitions(34, 5) {
 return spriteID - 1;
 } else if (spriteID >= newtiledefinitions(14, 0) && spriteID <= newtiledefinitions(14, 7) {
 return -1;
 } else if (spriteID >= newtiledefinitions(14, 8) && spriteID <= newtiledefinitions(14, 12) {
 return spriteID + 72;
 } else if (spriteID == newtiledefinitions(14, 13) {
 return spriteID + 71;
 } else if (spriteID >= newtiledefinitions(14, 16) && spriteID <= newtiledefinitions(14, 17) {
 return spriteID + 72;
 } else if (spriteID == newtiledefinitions(14, 18) {
 return spriteID + 73;
 } else if (spriteID == newtiledefinitions(14, 19) {
 return spriteID + 66;
 } else if (spriteID == newtiledefinitions(14, 20) {
 return -1;
 } else if (spriteID == newtiledefinitions(14, 21) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(21, 0) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(21, 1) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(21, 2) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(26, 0) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(26, 6) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(26, 1) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(26, 7) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(26, 8) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(26, 14) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(26, 9) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(26, 15) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(26, 16) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(26, 22) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(26, 17) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(26, 23) {
 return newtiledefinitions();
 } else if (spriteID >= newtiledefinitions(148, 0) && spriteID <= newtiledefinitions(148, 16) {
 int int0 = spriteID - newtiledefinitions(148, 0);
 return newtiledefinitions();
 } else if ((spriteID < newtiledefinitions(42, 44) || spriteID > newtiledefinitions(42, 47)
 && (spriteID < newtiledefinitions(42, 52) || spriteID > newtiledefinitions(42, 55) {
 if (spriteID == newtiledefinitions(43, 24) {
 return spriteID + 4;
 } else if (spriteID == newtiledefinitions(43, 26) {
 return spriteID + 2;
 } else if (spriteID == newtiledefinitions(43, 33) {
 return spriteID - 4;
 } else if (spriteID == newtiledefinitions(44, 0) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(44, 1) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(44, 2) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(44, 3) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(44, 4) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(44, 5) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(44, 6) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(44, 7) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(44, 16) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(44, 17) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(44, 18) {
 return newtiledefinitions();
 } else if (spriteID >= newtiledefinitions(44, 19) && spriteID <= newtiledefinitions(44, 22) {
 return spriteID + 33;
 } else if (spriteID == newtiledefinitions(44, 23) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(46, 8) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(46, 14) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(46, 15) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(46, 22) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(46, 23) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(46, 54) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(46, 55) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(106, 32) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(106, 34) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(47, 0) || spriteID == newtiledefinitions(47, 4) {
 return spriteID + 1;
 } else if (spriteID == newtiledefinitions(47, 1) || spriteID == newtiledefinitions(47, 5) {
 return spriteID - 1;
 } else if (spriteID >= newtiledefinitions(47, 8) && spriteID <= newtiledefinitions(47, 13) {
 return spriteID + 8;
 } else if (spriteID >= newtiledefinitions(47, 22) && spriteID <= newtiledefinitions(47, 23) {
 return spriteID - 12;
 } else if (spriteID >= newtiledefinitions(47, 44) && spriteID <= newtiledefinitions(47, 47) {
 return spriteID + 4;
 } else if (spriteID >= newtiledefinitions(47, 48) && spriteID <= newtiledefinitions(47, 51) {
 return spriteID - 4;
 } else if (spriteID == newtiledefinitions(48, 56) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(48, 58) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(52, 57) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(52, 58) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(52, 45) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(52, 46) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(54, 13) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(54, 15) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(54, 21) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(54, 22) {
 return newtiledefinitions();
 } else if (spriteID == newtiledefinitions(54, 23) {
 return newtiledefinitions();
 } else if (spriteID >= newtiledefinitions(67, 0) && spriteID <= newtiledefinitions(67, 16) {
 int int1 = 64 + Rand.Next(16);
 return ((IsoSprite)hashMap.get("f_bushes_1_" + int1).ID;
 } else if (spriteID == newtiledefinitions(68, 6) {
 return -1;
 } else if (spriteID >= newtiledefinitions(68, 16) && spriteID <= newtiledefinitions(68, 17) {
 return ((IsoSprite)hashMap.get("d_plants_1_53")).ID;
 } else if (spriteID >= newtiledefinitions(68, 18) && spriteID <= newtiledefinitions(68, 23) {
 int int2 = Rand.Next(4) * 16 + Rand.Next(8);
 return ((IsoSprite)hashMap.get("d_plants_1_" + int2).ID;
 } else {
 return spriteID >= newtiledefinitions(79, 24) && spriteID <= newtiledefinitions(79, 41)
 ? newtiledefinitions(81, spriteID - newtiledefinitions(79, 24)
 : spriteID;
 }
 } else {
 return -1;
 }
 }
 }

 static std::string Fix2x(const std::string& tileName) {
 if (Fix2xMap.empty()) {
 std::unordered_map hashMap = Fix2xMap;

 for (int int0 = 48; int0 <= 51; int0++) {
 hashMap.put("blends_streetoverlays_01_" + int0, "");
 }

 hashMap.put("fencing_01_14", "");
 hashMap.put("fencing_01_15", "");
 hashMap.put("fencing_01_22", "");
 hashMap.put("fencing_01_23", "");
 hashMap.put("fencing_01_30", "");
 hashMap.put("fencing_01_31", "");
 hashMap.put("fencing_01_38", "");
 hashMap.put("fencing_01_39", "");
 hashMap.put("fencing_01_46", "");
 hashMap.put("fencing_01_47", "");
 hashMap.put("fencing_01_62", "");
 hashMap.put("fencing_01_63", "");
 hashMap.put("fencing_01_70", "");
 hashMap.put("fencing_01_71", "");
 hashMap.put("fixtures_bathroom_02_2", "fixtures_bathroom_02_22");
 hashMap.put("fixtures_bathroom_02_20", "fixtures_bathroom_02_21");
 hashMap.put("fixtures_bathroom_02_21", "fixtures_bathroom_02_20");

 for (int int1 = 26; int1 <= 29; int1++) {
 hashMap.put("fixtures_bathroom_02_" + int1, "fixtures_bathroom_02_" + (int1 + 6);
 }

 hashMap.put("fixtures_counters_01_16", "fixtures_counters_01_45");
 hashMap.put("fixtures_counters_01_17", "fixtures_counters_01_43");
 hashMap.put("fixtures_counters_01_18", "fixtures_counters_01_41");
 hashMap.put("fixtures_counters_01_19", "fixtures_counters_01_47");
 hashMap.put("fixtures_counters_01_24", "fixtures_counters_01_26");
 hashMap.put("fixtures_counters_01_25", "fixtures_counters_01_27");

 for (int int2 = 0; int2 <= 7; int2++) {
 hashMap.put("fixtures_railings_01_" + int2, "");
 }

 for (int int3 = 8; int3 <= 12; int3++) {
 hashMap.put("fixtures_railings_01_" + int3, "fixtures_railings_01_" + (int3 + 72);
 }

 hashMap.put("fixtures_railings_01_13", "fixtures_railings_01_84");

 for (int int4 = 16; int4 <= 17; int4++) {
 hashMap.put("fixtures_railings_01_" + int4, "fixtures_railings_01_" + (int4 + 72);
 }

 hashMap.put("fixtures_railings_01_18", "fixtures_railings_01_91");
 hashMap.put("fixtures_railings_01_19", "fixtures_railings_01_85");
 hashMap.put("fixtures_railings_01_20", "");
 hashMap.put("fixtures_railings_01_21", "fixtures_railings_01_89");
 hashMap.put("floors_exterior_natural_01_0", "blends_natural_01_16");
 hashMap.put("floors_exterior_natural_01_1", "blends_natural_01_32");
 hashMap.put("floors_exterior_natural_01_2", "blends_natural_01_48");
 hashMap.put("floors_rugs_01_0", "floors_rugs_01_6");
 hashMap.put("floors_rugs_01_6", "floors_rugs_01_0");
 hashMap.put("floors_rugs_01_1", "floors_rugs_01_7");
 hashMap.put("floors_rugs_01_7", "floors_rugs_01_1");
 hashMap.put("floors_rugs_01_8", "floors_rugs_01_14");
 hashMap.put("floors_rugs_01_14", "floors_rugs_01_8");
 hashMap.put("floors_rugs_01_9", "floors_rugs_01_15");
 hashMap.put("floors_rugs_01_15", "floors_rugs_01_9");
 hashMap.put("floors_rugs_01_16", "floors_rugs_01_22");
 hashMap.put("floors_rugs_01_22", "floors_rugs_01_16");
 hashMap.put("floors_rugs_01_17", "floors_rugs_01_23");
 hashMap.put("floors_rugs_01_23", "floors_rugs_01_17");
 hashMap.put("furniture_bedding_01_42", "furniture_bedding_01_43");
 hashMap.put("furniture_bedding_01_43", "furniture_bedding_01_42");
 hashMap.put("furniture_bedding_01_44", "furniture_bedding_01_47");
 hashMap.put("furniture_bedding_01_47", "furniture_bedding_01_45");
 hashMap.put("furniture_bedding_01_45", "furniture_bedding_01_46");
 hashMap.put("furniture_bedding_01_46", "furniture_bedding_01_44");
 hashMap.put("furniture_tables_low_01_4", "furniture_tables_low_01_5");
 hashMap.put("furniture_tables_low_01_5", "furniture_tables_low_01_4");

 for (int int5 = 0; int5 <= 5; int5++) {
 hashMap.put("location_business_machinery_" + int5, "location_business_machinery_01_" + int5);
 hashMap.put("location_business_machinery_" + (int5 + 8), "location_business_machinery_01_" + (int5 + 8);
 hashMap.put("location_ business_machinery_" + int5, "location_business_machinery_01_" + int5);
 hashMap.put("location_ business_machinery_" + (int5 + 8), "location_business_machinery_01_" + (int5 + 8);
 }

 for (int int6 = 44; int6 <= 47; int6++) {
 hashMap.put("location_hospitality_sunstarmotel_01_" + int6, "");
 }

 for (int int7 = 52; int7 <= 55; int7++) {
 hashMap.put("location_hospitality_sunstarmotel_01_" + int7, "");
 }

 hashMap.put("location_hospitality_sunstarmotel_02_24", "location_hospitality_sunstarmotel_02_28");
 hashMap.put("location_hospitality_sunstarmotel_02_26", "location_hospitality_sunstarmotel_02_28");
 hashMap.put("location_hospitality_sunstarmotel_02_33", "location_hospitality_sunstarmotel_02_29");
 hashMap.put("location_restaurant_bar_01_0", "location_restaurant_bar_01_1");
 hashMap.put("location_restaurant_bar_01_1", "location_restaurant_bar_01_0");
 hashMap.put("location_restaurant_bar_01_2", "location_restaurant_bar_01_7");
 hashMap.put("location_restaurant_bar_01_3", "location_restaurant_bar_01_6");
 hashMap.put("location_restaurant_bar_01_4", "location_restaurant_bar_01_5");
 hashMap.put("location_restaurant_bar_01_5", "location_restaurant_bar_01_4");
 hashMap.put("location_restaurant_bar_01_6", "location_restaurant_bar_01_3");
 hashMap.put("location_restaurant_bar_01_7", "location_restaurant_bar_01_2");
 hashMap.put("location_restaurant_bar_01_16", "location_restaurant_bar_01_45");
 hashMap.put("location_restaurant_bar_01_17", "location_restaurant_bar_01_44");
 hashMap.put("location_restaurant_bar_01_18", "location_restaurant_bar_01_46");

 for (int int8 = 19; int8 <= 22; int8++) {
 hashMap.put("location_restaurant_bar_01_" + int8, "location_restaurant_bar_01_" + (int8 + 33);
 }

 hashMap.put("location_restaurant_bar_01_23", "location_restaurant_bar_01_47");
 hashMap.put("location_restaurant_pie_01_8", "location_restaurant_pie_01_5");
 hashMap.put("location_restaurant_pie_01_14", "location_restaurant_pie_01_10");
 hashMap.put("location_restaurant_pie_01_15", "location_restaurant_pie_01_11");
 hashMap.put("location_restaurant_pie_01_22", "location_restaurant_pie_01_14");
 hashMap.put("location_restaurant_pie_01_23", "location_restaurant_pie_01_15");
 hashMap.put("location_restaurant_pie_01_54", "location_restaurant_pie_01_55");
 hashMap.put("location_restaurant_pie_01_55", "location_restaurant_pie_01_54");
 hashMap.put("location_pizzawhirled_01_32", "location_pizzawhirled_01_34");
 hashMap.put("location_pizzawhirled_01_34", "location_pizzawhirled_01_32");
 hashMap.put("location_restaurant_seahorse_01_0", "location_restaurant_seahorse_01_1");
 hashMap.put("location_restaurant_seahorse_01_1", "location_restaurant_seahorse_01_0");
 hashMap.put("location_restaurant_seahorse_01_4", "location_restaurant_seahorse_01_5");
 hashMap.put("location_restaurant_seahorse_01_5", "location_restaurant_seahorse_01_4");

 for (int int9 = 8; int9 <= 13; int9++) {
 hashMap.put("location_restaurant_seahorse_01_" + int9, "location_restaurant_seahorse_01_" + (int9 + 8);
 }

 for (int int10 = 22; int10 <= 23; int10++) {
 hashMap.put("location_restaurant_seahorse_01_" + int10, "location_restaurant_seahorse_01_" + (int10 - 12);
 }

 for (int int11 = 44; int11 <= 47; int11++) {
 hashMap.put("location_restaurant_seahorse_01_" + int11, "location_restaurant_seahorse_01_" + (int11 + 4);
 }

 for (int int12 = 48; int12 <= 51; int12++) {
 hashMap.put("location_restaurant_seahorse_01_" + int12, "location_restaurant_seahorse_01_" + (int12 - 4);
 }

 hashMap.put("location_restaurant_spiffos_01_56", "location_restaurant_spiffos_01_58");
 hashMap.put("location_restaurant_spiffos_01_58", "location_restaurant_spiffos_01_56");
 hashMap.put("location_shop_fossoil_01_45", "location_shop_fossoil_01_44");
 hashMap.put("location_shop_fossoil_01_46", "location_shop_fossoil_01_45");
 hashMap.put("location_shop_fossoil_01_57", "location_shop_fossoil_01_58");
 hashMap.put("location_shop_fossoil_01_58", "location_shop_fossoil_01_59");
 hashMap.put("location_shop_greenes_01_13", "location_shop_greenes_01_18");
 hashMap.put("location_shop_greenes_01_15", "location_shop_greenes_01_19");
 hashMap.put("location_shop_greenes_01_21", "location_shop_greenes_01_16");
 hashMap.put("location_shop_greenes_01_22", "location_shop_greenes_01_13");
 hashMap.put("location_shop_greenes_01_23", "location_shop_greenes_01_17");
 hashMap.put("location_shop_greenes_01_67", "location_shop_greenes_01_70");
 hashMap.put("location_shop_greenes_01_68", "location_shop_greenes_01_67");
 hashMap.put("location_shop_greenes_01_70", "location_shop_greenes_01_71");
 hashMap.put("location_shop_greenes_01_75", "location_shop_greenes_01_78");
 hashMap.put("location_shop_greenes_01_76", "location_shop_greenes_01_75");
 hashMap.put("location_shop_greenes_01_78", "location_shop_greenes_01_79");

 for (int int13 = 0; int13 <= 16; int13++) {
 hashMap.put("vegetation_foliage_01_" + int13, "randBush");
 }

 hashMap.put("vegetation_groundcover_01_0", "blends_grassoverlays_01_16");
 hashMap.put("vegetation_groundcover_01_1", "blends_grassoverlays_01_8");
 hashMap.put("vegetation_groundcover_01_2", "blends_grassoverlays_01_0");
 hashMap.put("vegetation_groundcover_01_3", "blends_grassoverlays_01_64");
 hashMap.put("vegetation_groundcover_01_4", "blends_grassoverlays_01_56");
 hashMap.put("vegetation_groundcover_01_5", "blends_grassoverlays_01_48");
 hashMap.put("vegetation_groundcover_01_6", "");
 hashMap.put("vegetation_groundcover_01_44", "blends_grassoverlays_01_40");
 hashMap.put("vegetation_groundcover_01_45", "blends_grassoverlays_01_32");
 hashMap.put("vegetation_groundcover_01_46", "blends_grassoverlays_01_24");
 hashMap.put("vegetation_groundcover_01_16", "d_plants_1_53");
 hashMap.put("vegetation_groundcover_01_17", "d_plants_1_53");

 for (int int14 = 18; int14 <= 23; int14++) {
 hashMap.put("vegetation_groundcover_01_" + int14, "randPlant");
 }

 for (int int15 = 20; int15 <= 23; int15++) {
 hashMap.put("walls_exterior_house_01_" + int15, "walls_exterior_house_01_" + (int15 + 12);
 hashMap.put("walls_exterior_house_01_" + (int15 + 8), "walls_exterior_house_01_" + (int15 + 8 + 12);
 }

 for (int int16 = 24; int16 <= 41; int16++) {
 hashMap.put("walls_exterior_roofs_01_" + int16, "walls_exterior_roofs_03_" + int16);
 }
 }

 std::string string = Fix2xMap.get(tileName);
 if (string == nullptr) {
 return tileName;
 } else if ("randBush" == string) {
 int int17 = 64 + Rand.Next(16);
 return "f_bushes_1_" + int17;
 } else if ("randPlant" == string) {
 int int18 = Rand.Next(4) * 16 + Rand.Next(8);
 return "d_plants_1_" + int18;
 } else {
 return string;
 }
 }

 void addGeneratorPos(int x, int y, int z) {
 if (this->generatorsTouchingThisChunk == nullptr) {
 this->generatorsTouchingThisChunk = std::make_unique<ArrayList<>>();
 }

 for (int int0 = 0; int0 < this->generatorsTouchingThisChunk.size(); int0++) {
 IsoGameCharacter.Location location0 = this->generatorsTouchingThisChunk.get(int0);
 if (location0.x == x && location0.y == y && location0.z == z) {
 return;
 }
 }

 IsoGameCharacter.Location location1 = new IsoGameCharacter.Location(x, y, z);
 this->generatorsTouchingThisChunk.add(location1);
 }

 void removeGeneratorPos(int x, int y, int z) {
 if (this->generatorsTouchingThisChunk != nullptr) {
 for (int int0 = 0; int0 < this->generatorsTouchingThisChunk.size(); int0++) {
 IsoGameCharacter.Location location = this->generatorsTouchingThisChunk.get(int0);
 if (location.x == x && location.y == y && location.z == z) {
 this->generatorsTouchingThisChunk.remove(int0);
 int0--;
 }
 }
 }
 }

 bool isGeneratorPoweringSquare(int x, int y, int z) {
 if (this->generatorsTouchingThisChunk == nullptr) {
 return false;
 } else {
 for (int int0 = 0; int0 < this->generatorsTouchingThisChunk.size(); int0++) {
 IsoGameCharacter.Location location = this->generatorsTouchingThisChunk.get(int0);
 if (IsoGenerator.isPoweringSquare(location.x, location.y, location.z, x, y, z) {
 return true;
 }
 }

 return false;
 }
 }

 void checkForMissingGenerators() {
 if (this->generatorsTouchingThisChunk != nullptr) {
 for (int int0 = 0; int0 < this->generatorsTouchingThisChunk.size(); int0++) {
 IsoGameCharacter.Location location = this->generatorsTouchingThisChunk.get(int0);
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(location.x, location.y, location.z);
 if (square != nullptr) {
 IsoGenerator generator = square.getGenerator();
 if (generator == nullptr || !generator.isActivated()) {
 this->generatorsTouchingThisChunk.remove(int0);
 int0--;
 }
 }
 }
 }
 }

 bool isNewChunk() {
 return this->addZombies;
 }

 void addSpawnedRoom(int roomID) {
 if (!this->m_spawnedRooms.contains(roomID) {
 this->m_spawnedRooms.add(roomID);
 }
 }

 bool isSpawnedRoom(int roomID) {
 return this->m_spawnedRooms.contains(roomID);
 }

 public IsoMetaGrid.Zone getScavengeZone() {
 if (this->m_scavengeZone != nullptr) {
 return this->m_scavengeZone;
 } else {
 IsoMetaChunk metaChunk = IsoWorld.instance.getMetaGrid().getChunkData(this->wx, this->wy);
 if (metaChunk != nullptr && metaChunk.numZones() > 0) {
 for (int int0 = 0; int0 < metaChunk.numZones(); int0++) {
 IsoMetaGrid.Zone zone = metaChunk.getZone(int0);
 if ("DeepForest" == zone.type) || "Forest" == zone.type) {
 this->m_scavengeZone = zone;
 return zone;
 }

 if ("Nav" == zone.type) || "Town" == zone.type) {
 return nullptr;
 }
 }
 }

 uint8_t byte0 = 5;
 if (this->m_treeCount < byte0) {
 return nullptr;
 } else {
 int int1 = 0;

 for (int int2 = -1; int2 <= 1; int2++) {
 for (int int3 = -1; int3 <= 1; int3++) {
 if (int3 != 0 || int2 != 0) {
 IsoChunk chunk1 = GameServer.bServer
 ? ServerMap.instance.getChunk(this->wx + int3, this->wy + int2)
 : IsoWorld.instance.CurrentCell.getChunk(this->wx + int3, this->wy + int2);
 if (chunk1 != nullptr && chunk1.m_treeCount >= byte0) {
 if (++int1 == 8) {
 uint8_t byte1 = 10;
 this->m_scavengeZone = new IsoMetaGrid.Zone("", "Forest", this->wx * byte1, this->wy * byte1, 0, byte1, byte1);
 return this->m_scavengeZone;
 }
 }
 }
 }
 }

 return nullptr;
 }
 }
 }

 void resetForStore() {
 this->randomID = 0;
 this->revision = 0L;
 this->nextSplatIndex = 0;
 this->FloorBloodSplats.clear();
 this->FloorBloodSplatsFade.clear();
 this->jobType = IsoChunk.JobType.None;
 this->maxLevel = -1;
 this->bFixed2x = false;
 this->vehicles.clear();
 this->roomLights.clear();
 this->blam = false;
 this->lotheader = nullptr;
 this->bLoaded = false;
 this->addZombies = false;
 this->physicsCheck = false;
 this->loadedPhysics = false;
 this->wx = 0;
 this->wy = 0;
 this->erosion = nullptr;
 this->lootRespawnHour = -1;
 if (this->generatorsTouchingThisChunk != nullptr) {
 this->generatorsTouchingThisChunk.clear();
 }

 this->m_treeCount = 0;
 this->m_scavengeZone = nullptr;
 this->m_numberOfWaterTiles = 0;
 this->m_spawnedRooms.resetQuick();
 this->m_adjacentChunkLoadedCounter = 0;

 for (int int0 = 0; int0 < this->squares.length; int0++) {
 for (int int1 = 0; int1 < this->squares[0].length; int1++) {
 this->squares[int0][int1] = nullptr;
 }
 }

 for (int int2 = 0; int2 < 4; int2++) {
 this->lightCheck[int2] = true;
 this->bLightingNeverDone[int2] = true;
 }

 this->refs.clear();
 this->m_vehicleStorySpawnData = nullptr;
 this->m_loadVehiclesObject = nullptr;
 this->m_objectEmitterData.reset();
 MPStatistics.increaseStoredChunk();
 }

 int getNumberOfWaterTiles() {
 return this->m_numberOfWaterTiles;
 }

 void setRandomVehicleStoryToSpawnLater(VehicleStorySpawnData spawnData) {
 this->m_vehicleStorySpawnData = spawnData;
 }

 bool hasObjectAmbientEmitter(IsoObject object) {
 return this->m_objectEmitterData.hasObject(object);
 }

 void addObjectAmbientEmitter(IsoObject object, ObjectAmbientEmitters.PerObjectLogic logic) {
 this->m_objectEmitterData.addObject(object, logic);
 }

 void removeObjectAmbientEmitter(IsoObject object) {
 this->m_objectEmitterData.removeObject(object);
 }

 private static class ChunkGetter implements IsoGridSquare.GetSquare {
 IsoChunk chunk;

 IsoGridSquare getGridSquare(int arg0, int arg1, int arg2) {
 arg0 -= this->chunk.wx * 10;
 arg1 -= this->chunk.wy * 10;
 return arg0 >= 0 && arg0 < 10 && arg1 >= 0 && arg1 < 10 && arg2 >= 0 && arg2 < 8 ? this->chunk.getGridSquare(arg0, arg1, arg2) : nullptr;
 }
 }

 private static class ChunkLock {
 int wx;
 int wy;
 int count;
 ReentrantReadWriteLock rw = new ReentrantReadWriteLock(true);

 public ChunkLock(int int0, int int1) {
 this->wx = int0;
 this->wy = int1;
 }

 public IsoChunk.ChunkLock set(int int0, int int1) {
 assert this->count == 0;

 this->wx = int0;
 this->wy = int1;
 return this;
 }

 public IsoChunk.ChunkLock ref() {
 this->count++;
 return this;
 }

 int deref() {
 assert this->count > 0;

 return --this->count;
 }

 void lockForReading() {
 this->rw.readLock().lock();
 }

 void unlockForReading() {
 this->rw.readLock().unlock();
 }

 void lockForWriting() {
 this->rw.writeLock().lock();
 }

 void unlockForWriting() {
 this->rw.writeLock().unlock();
 }
 }

 public static enum JobType {
 None,
 Convert,
 SoftReset;
 }

 private static enum PhysicsShapes {
 Solid,
 WallN,
 WallW,
 WallS,
 WallE,
 Tree,
 Floor;
 }

 private static class SanityCheck {
 IsoChunk saveChunk;
 std::string saveThread;
 IsoChunk loadChunk;
 std::string loadThread;
 public ArrayList<String> loadFile = std::make_unique<ArrayList<>>();
 std::string saveFile;

 public synchronized void beginSave(IsoChunk arg0) {
 if (this->saveChunk != nullptr) {
 this->log("trying to save while already saving, wx,wy=" + arg0.wx + "," + arg0.wy);
 }

 if (this->loadChunk == arg0) {
 this->log("trying to save the same IsoChunk being loaded");
 }

 this->saveChunk = arg0;
 this->saveThread = Thread.currentThread().getName();
 }

 public synchronized void endSave(IsoChunk arg0) {
 this->saveChunk = nullptr;
 this->saveThread = nullptr;
 }

 public synchronized void beginLoad(IsoChunk arg0) {
 if (this->loadChunk != nullptr) {
 this->log("trying to load while already loading, wx,wy=" + arg0.wx + "," + arg0.wy);
 }

 if (this->saveChunk == arg0) {
 this->log("trying to load the same IsoChunk being saved");
 }

 this->loadChunk = arg0;
 this->loadThread = Thread.currentThread().getName();
 }

 public synchronized void endLoad(IsoChunk arg0) {
 this->loadChunk = nullptr;
 this->loadThread = nullptr;
 }

 public synchronized void checkCRC(long arg0, long arg1) {
 if (arg0 != arg1) {
 this->log("CRC mismatch save=" + arg0 + " load=" + arg1);
 }
 }

 public synchronized void checkLength(long arg0, long arg1) {
 if (arg0 != arg1) {
 this->log("LENGTH mismatch save=" + arg0 + " load=" + arg1);
 }
 }

 public synchronized void beginLoadFile(String arg0) {
 if (arg0 == this->saveFile) {
 this->log("attempted to load file being saved " + arg0);
 }

 this->loadFile.add(arg0);
 }

 public synchronized void endLoadFile(String arg0) {
 this->loadFile.remove(arg0);
 }

 public synchronized void beginSaveFile(String arg0) {
 if (this->loadFile.contains(arg0) {
 this->log("attempted to save file being loaded " + arg0);
 }

 this->saveFile = arg0;
 }

 public synchronized void endSaveFile() {
 this->saveFile = nullptr;
 }

 public synchronized void log(String arg0) {
 StringBuilder stringBuilder = new StringBuilder();
 stringBuilder.append("SANITY CHECK FAIL! thread=\"" + Thread.currentThread().getName() + "\"\n");
 if (arg0 != nullptr) {
 stringBuilder.append(arg0 + "\n");
 }

 if (this->saveChunk != nullptr && this->saveChunk == this->loadChunk) {
 stringBuilder.append("exact same IsoChunk being saved + loaded\n");
 }

 if (this->saveChunk != nullptr) {
 stringBuilder.append("save wx,wy=" + this->saveChunk.wx + "," + this->saveChunk.wy + " thread=\"" + this->saveThread + "\"\n");
 } else {
 stringBuilder.append("save chunk=nullptr\n");
 }

 if (this->loadChunk != nullptr) {
 stringBuilder.append("load wx,wy=" + this->loadChunk.wx + "," + this->loadChunk.wy + " thread=\"" + this->loadThread + "\"\n");
 } else {
 stringBuilder.append("load chunk=nullptr\n");
 }

 std::string string = stringBuilder.toString();
 throw RuntimeException(string);
 }
 }
}
} // namespace iso
} // namespace zombie
