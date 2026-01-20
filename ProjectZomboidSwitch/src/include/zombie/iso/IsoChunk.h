#pragma once
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/array/TIntArrayList.h"
#include "zombie/ChunkMapFilenames.h"
#include "zombie/FliesSound.h"
#include "zombie/FliesSound/ChunkData.h"
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
#include "zombie/WorldSoundManager/WorldSound.h"
#include "zombie/ZombieSpawnRecorder.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/audio/ObjectAmbientEmitters/DoorLogic.h"
#include "zombie/audio/ObjectAmbientEmitters/PerObjectLogic.h"
#include "zombie/audio/ObjectAmbientEmitters/WindowLogic.h"
#include "zombie/characters/IsoGameCharacter/Location.h"
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
#include "zombie/erosion/ErosionData/Chunk.h"
#include "zombie/erosion/ErosionMain.h"
#include "zombie/globalObjects/SGlobalObjects.h"
#include "zombie/iso/IsoChunk/1.h"
#include "zombie/iso/IsoChunk/ChunkGetter.h"
#include "zombie/iso/IsoChunk/ChunkLock.h"
#include "zombie/iso/IsoChunk/JobType.h"
#include "zombie/iso/IsoChunk/PhysicsShapes.h"
#include "zombie/iso/IsoChunk/SanityCheck.h"
#include "zombie/iso/IsoMetaGrid/VehicleZone.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
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
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/MPStatistics.h"
#include "zombie/network/PacketTypes/PacketType.h"
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
#include "zombie/vehicles/BaseVehicle/MinMaxPosition.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include "zombie/vehicles/VehicleType.h"
#include "zombie/vehicles/VehicleType/VehicleTypeDefinition.h"
#include "zombie/vehicles/VehiclesDB2.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {


class IsoChunk {
public:
    static bool bDoServerRequests = true;
    int wx = 0;
    int wy = 0;
   public const IsoGridSquare[][] squares;
    ChunkData corpseData;
   public const zombie.iso.NearestWalls.ChunkData nearestWalls = new zombie.iso.NearestWalls.ChunkData();
   private std::vector<Location> generatorsTouchingThisChunk;
    int maxLevel = -1;
   public const std::vector<WorldSound> SoundList = std::make_unique<std::vector<>>();
    int m_treeCount = 0;
    int m_numberOfWaterTiles = 0;
    Zone m_scavengeZone = nullptr;
    const TIntArrayList m_spawnedRooms = std::make_shared<TIntArrayList>();
    IsoChunk next;
   public const zombie.vehicles.CollideWithObstaclesPoly.ChunkData collision = new zombie.vehicles.CollideWithObstaclesPoly.ChunkData();
    int m_adjacentChunkLoadedCounter = 0;
    VehicleStorySpawnData m_vehicleStorySpawnData;
    void* m_loadVehiclesObject = nullptr;
   public const zombie.audio.ObjectAmbientEmitters.ChunkData m_objectEmitterData = new zombie.audio.ObjectAmbientEmitters.ChunkData();
    JobType jobType = JobType.None;
    LotHeader lotheader;
   public const BoundedQueue<IsoFloorBloodSplat> FloorBloodSplats = std::make_shared<BoundedQueue>(1000);
   public const std::vector<IsoFloorBloodSplat> FloorBloodSplatsFade = std::make_unique<std::vector<>>();
    static const int MAX_BLOOD_SPLATS = 1000;
    int nextSplatIndex;
   public static const byte[][] renderByIndex = new byte[][]{
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
   public const std::vector<IsoChunkMap> refs = std::make_unique<std::vector<>>();
    bool bLoaded;
    bool blam;
    bool addZombies;
    bool bFixed2x;
   public const boolean[] lightCheck = new boolean[4];
   public const boolean[] bLightingNeverDone = new boolean[4];
   public const std::vector<IsoRoomLight> roomLights = std::make_unique<std::vector<>>();
   public const std::vector<BaseVehicle> vehicles = std::make_unique<std::vector<>>();
    int lootRespawnHour = -1;
    long hashCodeObjects;
    int ObjectsSyncCount = 0;
    static int AddVehicles_ForTest_vtype = 0;
    static int AddVehicles_ForTest_vskin = 0;
    static int AddVehicles_ForTest_vrot = 0;
   private static const std::vector<BaseVehicle> BaseVehicleCheckedVehicles = std::make_unique<std::vector<>>();
    bool physicsCheck = false;
    static const int MAX_SHAPES = 4;
   private const PhysicsShapes[] shapes = new PhysicsShapes[4];
   private static const byte[] bshapes = new byte[4];
    static const ChunkGetter chunkGetter = std::make_shared<ChunkGetter>();
    bool loadedPhysics = false;
    const void* vehiclesForAddToWorldLock = std::make_shared<Object>();
   public std::vector<BaseVehicle> vehiclesForAddToWorld = nullptr;
   public static const ConcurrentLinkedQueue<IsoChunk> loadGridSquare = std::make_unique<ConcurrentLinkedQueue<>>();
    static const int BLOCK_SIZE = 65536;
    static ByteBuffer SliceBuffer = ByteBuffer.allocate(65536);
    static ByteBuffer SliceBufferLoad = ByteBuffer.allocate(65536);
    static const void* WriteLock = std::make_shared<Object>();
   private static const std::vector<RoomDef> tempRoomDefs = std::make_unique<std::vector<>>();
   private static const std::vector<IsoBuilding> tempBuildings = std::make_unique<std::vector<>>();
   private static const std::vector<ChunkLock> Locks = std::make_unique<std::vector<>>();
   private static const std::stack<ChunkLock> FreeLocks = std::make_unique<std::stack<>>();
    static const SanityCheck sanityCheck = std::make_shared<SanityCheck>();
    static const CRC32 crcLoad = std::make_shared<CRC32>();
    static const CRC32 crcSave = std::make_shared<CRC32>();
    static std::string prefix = "map_";
    Chunk erosion;
   private static const std::unordered_map<std::string, std::string> Fix2xMap = std::make_unique<std::unordered_map<>>();
    int randomID;
    long revision;

    void updateSounds() {
      /* synchronized - TODO: add std::mutex */ (WorldSoundManager.instance.SoundList) {
    int var2 = this.SoundList.size();

         for (int var3 = 0; var3 < var2; var3++) {
    WorldSound var4 = this.SoundList.get(var3);
            if (var4 == nullptr || var4.life <= 0) {
               this.SoundList.remove(var3);
               var3--;
               var2--;
            }
         }
      }
   }

    public IsoChunk(IsoCell var1) {
      this.squares = new IsoGridSquare[8][100];

      for (int var2 = 0; var2 < 4; var2++) {
         this.lightCheck[var2] = true;
         this.bLightingNeverDone[var2] = true;
      }

      MPStatistics.increaseRelevantChunk();
   }

    long getHashCodeObjects() {
      this.recalcHashCodeObjects();
      return this.hashCodeObjects;
   }

    void recalcHashCodeObjects() {
    long var1 = 0L;
      this.hashCodeObjects = var1;
   }

    int hashCodeNoOverride() {
      return (int)this.hashCodeObjects;
   }

    void addBloodSplat(float var1, float var2, float var3, int var4) {
      if (!(var1 < this.wx * 10) && !(var1 >= (this.wx + 1) * 10)) {
         if (!(var2 < this.wy * 10) && !(var2 >= (this.wy + 1) * 10)) {
    IsoGridSquare var5 = this.getGridSquare((int)(var1 - this.wx * 10), (int)(var2 - this.wy * 10), (int)var3);
            if (var5 != nullptr && var5.isSolidFloor()) {
               IsoFloorBloodSplat var6 = std::make_shared<IsoFloorBloodSplat>(
                  var1 - this.wx * 10, var2 - this.wy * 10, var3, var4, (float)GameTime.getInstance().getWorldAgeHours()
               );
               if (var4 < 8) {
                  var6.index = ++this.nextSplatIndex;
                  if (this.nextSplatIndex >= 10) {
                     this.nextSplatIndex = 0;
                  }
               }

               if (this.FloorBloodSplats.isFull()) {
    IsoFloorBloodSplat var7 = (IsoFloorBloodSplat)this.FloorBloodSplats.removeFirst();
                  var7.fade = PerformanceSettings.getLockFPS() * 5;
                  this.FloorBloodSplatsFade.push_back(var7);
               }

               this.FloorBloodSplats.push_back(var6);
            }
         }
      }
   }

    void AddCorpses(int var1, int var2) {
      if (!IsoWorld.getZombiesDisabled() && !"Tutorial" == Core.GameMode)) {
    IsoMetaChunk var3 = IsoWorld.instance.getMetaChunk(var1, var2);
         if (var3 != nullptr) {
    float var4 = var3.getZombieIntensity();
            var4 *= 0.1F;
    int var5 = 0;
            if (var4 < 1.0F) {
               if (Rand.Next(100) < var4 * 100.0F) {
                  var5 = 1;
               }
            } else {
               var5 = Rand.Next(0, (int)var4);
            }

            if (var5 > 0) {
    void* var6 = nullptr;
    int var7 = 0;

               do {
    int var8 = Rand.Next(10);
    int var9 = Rand.Next(10);
                  var6 = this.getGridSquare(var8, var9, 0);
                  var7++;
               } while (var7 < 100 && (var6 == nullptr || !RandomizedBuildingBase.is2x2AreaClear((IsoGridSquare)var6)));

               if (var7 == 100) {
                  return;
               }

               if (var6 != nullptr) {
    uint8_t var14 = 14;
                  if (Rand.Next(10) == 0) {
                     var14 = 50;
                  }

                  if (Rand.Next(40) == 0) {
                     var14 = 100;
                  }

                  for (int var15 = 0; var15 < var14; var15++) {
    float var10 = Rand.Next(3000) / 1000.0F;
    float var11 = Rand.Next(3000) / 1000.0F;
                     this.addBloodSplat(var6.getX() + --var10, var6.getY() + --var11, var6.getZ(), Rand.Next(20));
                  }

    bool var16 = Rand.Next(15 - SandboxOptions.instance.TimeSinceApo.getValue()) == 0;
                  VirtualZombieManager.instance.choices.clear();
                  VirtualZombieManager.instance.choices.push_back(var6);
    IsoZombie var18 = VirtualZombieManager.instance.createRealZombieAlways(Rand.Next(8), false);
                  var18.setX(((IsoGridSquare)var6).x);
                  var18.setY(((IsoGridSquare)var6).y);
                  var18.setFakeDead(false);
                  var18.setHealth(0.0F);
                  var18.upKillCount = false;
                  if (!var16) {
                     var18.dressInRandomOutfit();

                     for (int var20 = 0; var20 < 10; var20++) {
                        var18.addHole(nullptr);
                        var18.addBlood(nullptr, false, true, false);
                        var18.addDirt(nullptr, nullptr, false);
                     }

                     var18.DoCorpseInventory();
                  }

                  var18.setSkeleton(var16);
                  if (var16) {
                     var18.getHumanVisual().setSkinTextureIndex(2);
                  }

    IsoDeadBody var21 = std::make_shared<IsoDeadBody>(var18, true);
                  if (!var16 && Rand.Next(3) == 0) {
                     VirtualZombieManager.instance.createEatingZombies(var21, Rand.Next(1, 4));
                  } else if (!var16 && Rand.Next(10) == 0) {
                     var21.setFakeDead(true);
                     if (Rand.Next(5) == 0) {
                        var21.setCrawling(true);
                     }
                  }
               }
            }
         }
      }
   }

    void AddBlood(int var1, int var2) {
    IsoMetaChunk var3 = IsoWorld.instance.getMetaChunk(var1, var2);
      if (var3 != nullptr) {
    float var4 = var3.getZombieIntensity();
         var4 *= 0.1F;
         if (Rand.Next(40) == 0) {
            var4 += 10.0F;
         }

    int var5 = 0;
         if (var4 < 1.0F) {
            if (Rand.Next(100) < var4 * 100.0F) {
               var5 = 1;
            }
         } else {
            var5 = Rand.Next(0, (int)var4);
         }

         if (var5 > 0) {
            VirtualZombieManager.instance.AddBloodToMap(var5, this);
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void checkVehiclePos(BaseVehicle var1, IsoChunk var2) {
      this.fixVehiclePos(var1, var2);
    IsoDirections var3 = var1.getDir();
      switch (1.$SwitchMap$zombie$iso$IsoDirections[var3.ordinal()]) {
         case 1:
         case 2:
            if (var1.x - var2.wx * 10 < var1.getScript().getExtents().x) {
    IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var1.x - var1.getScript().getExtents().x, var1.y, var1.z);
               if (var6 == nullptr) {
                  return;
               }

               this.fixVehiclePos(var1, var6.chunk);
            }

            if (var1.x - var2.wx * 10 > 10.0F - var1.getScript().getExtents().x) {
    IsoGridSquare var7 = IsoWorld.instance.CurrentCell.getGridSquare(var1.x + var1.getScript().getExtents().x, var1.y, var1.z);
               if (var7 == nullptr) {
                  return;
               }

               this.fixVehiclePos(var1, var7.chunk);
            }
            break;
         case 3:
         case 4:
            if (var1.y - var2.wy * 10 < var1.getScript().getExtents().z) {
    IsoGridSquare var4 = IsoWorld.instance.CurrentCell.getGridSquare(var1.x, var1.y - var1.getScript().getExtents().z, var1.z);
               if (var4 == nullptr) {
                  return;
               }

               this.fixVehiclePos(var1, var4.chunk);
            }

            if (var1.y - var2.wy * 10 > 10.0F - var1.getScript().getExtents().z) {
    IsoGridSquare var5 = IsoWorld.instance.CurrentCell.getGridSquare(var1.x, var1.y + var1.getScript().getExtents().z, var1.z);
               if (var5 == nullptr) {
                  return;
               }

               this.fixVehiclePos(var1, var5.chunk);
            }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    bool fixVehiclePos(BaseVehicle var1, IsoChunk var2) {
    MinMaxPosition var3 = var1.getMinMaxPosition();
    bool var5 = false;
    IsoDirections var6 = var1.getDir();

      for (int var7 = 0; var7 < var2.vehicles.size(); var7++) {
    MinMaxPosition var8 = var2.vehicles.get(var7).getMinMaxPosition();
         switch (1.$SwitchMap$zombie$iso$IsoDirections[var6.ordinal()]) {
            case 1:
            case 2:
    float var10 = var8.minX - var3.maxX;
               if (var10 > 0.0F && var3.minY < var8.maxY && var3.maxY > var8.minY) {
                  var1.x -= var10;
                  var3.minX -= var10;
                  var3.maxX -= var10;
                  var5 = true;
               } else {
                  var10 = var3.minX - var8.maxX;
                  if (var10 > 0.0F && var3.minY < var8.maxY && var3.maxY > var8.minY) {
                     var1.x += var10;
                     var3.minX += var10;
                     var3.maxX += var10;
                     var5 = true;
                  }
               }
               break;
            case 3:
            case 4:
    float var4 = var8.minY - var3.maxY;
               if (var4 > 0.0F && var3.minX < var8.maxX && var3.maxX > var8.minX) {
                  var1.y -= var4;
                  var3.minY -= var4;
                  var3.maxY -= var4;
                  var5 = true;
               } else {
                  var4 = var3.minY - var8.maxY;
                  if (var4 > 0.0F && var3.minX < var8.maxX && var3.maxX > var8.minX) {
                     var1.y += var4;
                     var3.minY += var4;
                     var3.maxY += var4;
                     var5 = true;
                  }
               }
         }
      }

    return var5;
   }

    bool isGoodVehiclePos(BaseVehicle var1, IsoChunk var2) {
    int var3 = ((int)var1.x - 4) / 10 - 1;
    int var4 = ((int)var1.y - 4) / 10 - 1;
    int var5 = (int)Math.ceil((var1.x + 4.0F) / 10.0F) + 1;
    int var6 = (int)Math.ceil((var1.y + 4.0F) / 10.0F) + 1;

      for (int var7 = var4; var7 < var6; var7++) {
         for (int var8 = var3; var8 < var5; var8++) {
            IsoChunk var9 = GameServer.bServer
               ? ServerMap.instance.getChunk(var8, var7)
               : IsoWorld.instance.CurrentCell.getChunkForGridSquare(var8 * 10, var7 * 10, 0);
            if (var9 != nullptr) {
               for (int var10 = 0; var10 < var9.vehicles.size(); var10++) {
    BaseVehicle var11 = var9.vehicles.get(var10);
                  if ((int)var11.z == (int)var1.z && var1.testCollisionWithVehicle(var11)) {
    return false;
                  }
               }
            }
         }
      }

    return true;
   }

    void AddVehicles_ForTest(Zone var1) {
    int var2 = var1.y - this.wy * 10 + 3;

      while (var2 < 0) {
         var2 += 6;
      }

    int var3 = var1.x - this.wx * 10 + 2;

      while (var3 < 0) {
         var3 += 5;
      }

      for (int var4 = var2; var4 < 10 && this.wy * 10 + var4 < var1.y + var1.h; var4 += 6) {
         for (int var5 = var3; var5 < 10 && this.wx * 10 + var5 < var1.x + var1.w; var5 += 5) {
    IsoGridSquare var6 = this.getGridSquare(var5, var4, 0);
            if (var6 != nullptr) {
    BaseVehicle var7 = std::make_shared<BaseVehicle>(IsoWorld.instance.CurrentCell);
               var7.setZone("Test");
               switch (AddVehicles_ForTest_vtype) {
                  case 0:
                     var7.setScriptName("Base.CarNormal");
                     break;
                  case 1:
                     var7.setScriptName("Base.SmallCar");
                     break;
                  case 2:
                     var7.setScriptName("Base.SmallCar02");
                     break;
                  case 3:
                     var7.setScriptName("Base.CarTaxi");
                     break;
                  case 4:
                     var7.setScriptName("Base.CarTaxi2");
                     break;
                  case 5:
                     var7.setScriptName("Base.PickUpTruck");
                     break;
                  case 6:
                     var7.setScriptName("Base.PickUpVan");
                     break;
                  case 7:
                     var7.setScriptName("Base.CarStationWagon");
                     break;
                  case 8:
                     var7.setScriptName("Base.CarStationWagon2");
                     break;
                  case 9:
                     var7.setScriptName("Base.VanSeats");
                     break;
                  case 10:
                     var7.setScriptName("Base.Van");
                     break;
                  case 11:
                     var7.setScriptName("Base.StepVan");
                     break;
                  case 12:
                     var7.setScriptName("Base.PickUpTruck");
                     break;
                  case 13:
                     var7.setScriptName("Base.PickUpVan");
                     break;
                  case 14:
                     var7.setScriptName("Base.CarStationWagon");
                     break;
                  case 15:
                     var7.setScriptName("Base.CarStationWagon2");
                     break;
                  case 16:
                     var7.setScriptName("Base.VanSeats");
                     break;
                  case 17:
                     var7.setScriptName("Base.Van");
                     break;
                  case 18:
                     var7.setScriptName("Base.StepVan");
                     break;
                  case 19:
                     var7.setScriptName("Base.SUV");
                     break;
                  case 20:
                     var7.setScriptName("Base.OffRoad");
                     break;
                  case 21:
                     var7.setScriptName("Base.ModernCar");
                     break;
                  case 22:
                     var7.setScriptName("Base.ModernCar02");
                     break;
                  case 23:
                     var7.setScriptName("Base.CarLuxury");
                     break;
                  case 24:
                     var7.setScriptName("Base.SportsCar");
                     break;
                  case 25:
                     var7.setScriptName("Base.PickUpVanLightsPolice");
                     break;
                  case 26:
                     var7.setScriptName("Base.CarLightsPolice");
                     break;
                  case 27:
                     var7.setScriptName("Base.PickUpVanLightsFire");
                     break;
                  case 28:
                     var7.setScriptName("Base.PickUpTruckLightsFire");
                     break;
                  case 29:
                     var7.setScriptName("Base.PickUpVanLights");
                     break;
                  case 30:
                     var7.setScriptName("Base.PickUpTruckLights");
                     break;
                  case 31:
                     var7.setScriptName("Base.CarLights");
                     break;
                  case 32:
                     var7.setScriptName("Base.StepVanMail");
                     break;
                  case 33:
                     var7.setScriptName("Base.VanSpiffo");
                     break;
                  case 34:
                     var7.setScriptName("Base.VanAmbulance");
                     break;
                  case 35:
                     var7.setScriptName("Base.VanRadio");
                     break;
                  case 36:
                     var7.setScriptName("Base.PickupBurnt");
                     break;
                  case 37:
                     var7.setScriptName("Base.CarNormalBurnt");
                     break;
                  case 38:
                     var7.setScriptName("Base.TaxiBurnt");
                     break;
                  case 39:
                     var7.setScriptName("Base.ModernCarBurnt");
                     break;
                  case 40:
                     var7.setScriptName("Base.ModernCar02Burnt");
                     break;
                  case 41:
                     var7.setScriptName("Base.SportsCarBurnt");
                     break;
                  case 42:
                     var7.setScriptName("Base.SmallCarBurnt");
                     break;
                  case 43:
                     var7.setScriptName("Base.SmallCar02Burnt");
                     break;
                  case 44:
                     var7.setScriptName("Base.VanSeatsBurnt");
                     break;
                  case 45:
                     var7.setScriptName("Base.VanBurnt");
                     break;
                  case 46:
                     var7.setScriptName("Base.SUVBurnt");
                     break;
                  case 47:
                     var7.setScriptName("Base.OffRoadBurnt");
                     break;
                  case 48:
                     var7.setScriptName("Base.PickUpVanLightsBurnt");
                     break;
                  case 49:
                     var7.setScriptName("Base.AmbulanceBurnt");
                     break;
                  case 50:
                     var7.setScriptName("Base.VanRadioBurnt");
                     break;
                  case 51:
                     var7.setScriptName("Base.PickupSpecialBurnt");
                     break;
                  case 52:
                     var7.setScriptName("Base.NormalCarBurntPolice");
                     break;
                  case 53:
                     var7.setScriptName("Base.LuxuryCarBurnt");
                     break;
                  case 54:
                     var7.setScriptName("Base.PickUpVanBurnt");
                     break;
                  case 55:
                     var7.setScriptName("Base.PickUpTruckMccoy");
               }

               var7.setDir(IsoDirections.W);
    double var8 = (var7.getDir().toAngle() + (float) Math.PI) % (Math.PI * 2);
               var7.savedRot.setAngleAxis(var8, 0.0, 1.0, 0.0);
               if (AddVehicles_ForTest_vrot == 1) {
                  var7.savedRot.setAngleAxis(Math.PI / 2, 0.0, 0.0, 1.0);
               }

               if (AddVehicles_ForTest_vrot == 2) {
                  var7.savedRot.setAngleAxis(Math.PI, 0.0, 0.0, 1.0);
               }

               var7.jniTransform.setRotation(var7.savedRot);
               var7.setX(var6.x);
               var7.setY(var6.y + 3.0F - 3.0F);
               var7.setZ(var6.z);
               var7.jniTransform.origin.set(var7.getX() - WorldSimulation.instance.offsetX, var7.getZ(), var7.getY() - WorldSimulation.instance.offsetY);
               var7.setScript();
               this.checkVehiclePos(var7, this);
               this.vehicles.push_back(var7);
               var7.setSkinIndex(AddVehicles_ForTest_vskin);
               AddVehicles_ForTest_vrot++;
               if (AddVehicles_ForTest_vrot >= 2) {
                  AddVehicles_ForTest_vrot = 0;
                  AddVehicles_ForTest_vskin++;
                  if (AddVehicles_ForTest_vskin >= var7.getSkinCount()) {
                     AddVehicles_ForTest_vtype = (AddVehicles_ForTest_vtype + 1) % 56;
                     AddVehicles_ForTest_vskin = 0;
                  }
               }
            }
         }
      }
   }

    void AddVehicles_OnZone(VehicleZone var1, const std::string& var2) {
    IsoDirections var3 = IsoDirections.N;
    uint8_t var4 = 3;
    uint8_t var5 = 4;
      if ((var1.w == var5 || var1.w == var5 + 1 || var1.w == var5 + 2) && (var1.h <= var4 || var1.h >= var5 + 2)) {
         var3 = IsoDirections.W;
      }

      var5 = 5;
      if (var1.dir != IsoDirections.Max) {
         var3 = var1.dir;
      }

      if (var3 != IsoDirections.N && var3 != IsoDirections.S) {
         var5 = 3;
         var4 = 5;
      }

    uint8_t var6 = 10;
    float var7 = var1.y - this.wy * 10 + var5 / 2.0F;

      while (var7 < 0.0F) {
         var7 += var5;
      }

    float var8 = var1.x - this.wx * 10 + var4 / 2.0F;

      while (var8 < 0.0F) {
         var8 += var4;
      }

    float var9 = var7;

      while (var9 < 10.0F && this.wy * 10 + var9 < var1.y + var1.h) {
         for (float var10 = var8; var10 < 10.0F && this.wx * 10 + var10 < var1.x + var1.w; var10 += var4) {
    IsoGridSquare var11 = this.getGridSquare((int)var10, (int)var9, 0);
            if (var11 != nullptr) {
    VehicleType var12 = VehicleType.getRandomVehicleType(var2);
               if (var12 == nullptr) {
                  System.out.println("Can't find car: " + var2);
                  var9 += var5;
                  break;
               }

    int var13 = var12.spawnRate;

               var13 = switch (SandboxOptions.instance.CarSpawnRate.getValue()) {
                  case 2 -> (int)Math.ceil(var13 / 10.0F);
                  case 3 -> (int)Math.ceil(var13 / 1.5F);
                  case 5 -> 2;
               };
               if (SystemDisabler.doVehiclesEverywhere || DebugOptions.instance.VehicleSpawnEverywhere.getValue()) {
                  var13 = 100;
               }

               if (Rand.Next(100) <= var13) {
    BaseVehicle var14 = std::make_shared<BaseVehicle>(IsoWorld.instance.CurrentCell);
                  var14.setZone(var2);
                  var14.setVehicleType(var12.name);
                  if (var12.isSpecialCar) {
                     var14.setDoColor(false);
                  }

                  if (!this.RandomizeModel(var14, var1, var2, var12)) {
                     System.out.println("Problem with Vehicle spawning: " + var2 + " " + var12);
                     return;
                  }

    uint8_t var15 = 15;
                  switch (SandboxOptions.instance.CarAlarm.getValue()) {
                     case 1:
                        var15 = -1;
                        break;
                     case 2:
                        var15 = 3;
                        break;
                     case 3:
                        var15 = 8;
                     case 4:
                     default:
                        break;
                     case 5:
                        var15 = 25;
                        break;
                     case 6:
                        var15 = 50;
                  }

    bool var16 = var14.getScriptName().toLowerCase().contains("burnt") || var14.getScriptName().toLowerCase().contains("smashed");
                  if (Rand.Next(100) < var15 && !var16) {
                     var14.setAlarmed(true);
                  }

                  if (var1.isFaceDirection()) {
                     var14.setDir(var3);
                  } else if (var3 != IsoDirections.N && var3 != IsoDirections.S) {
                     var14.setDir(Rand.Next(2) == 0 ? IsoDirections.W : IsoDirections.E);
                  } else {
                     var14.setDir(Rand.Next(2) == 0 ? IsoDirections.N : IsoDirections.S);
                  }

    float var17 = var14.getDir().toAngle() + (float) Math.PI;

                  while (var17 > Math.PI * 2) {
                     var17 = (float)(var17 - (Math.PI * 2));
                  }

                  if (var12.randomAngle) {
                     var17 = Rand.Next(0.0F, (float) (Math.PI * 2));
                  }

                  var14.savedRot.setAngleAxis(var17, 0.0F, 1.0F, 0.0F);
                  var14.jniTransform.setRotation(var14.savedRot);
    float var18 = var14.getScript().getExtents().z;
    float var19 = 0.5F;
    float var20 = var11.x + 0.5F;
    float var21 = var11.y + 0.5F;
                  if (var3 == IsoDirections.N) {
                     var20 = var11.x + var4 / 2.0F - (int)(var4 / 2.0F);
                     var21 = var1.y + var18 / 2.0F + var19;
                     if (var21 >= var11.y + 1 && (int)var9 < var6 - 1 && this.getGridSquare((int)var10, (int)var9 + 1, 0) != nullptr) {
                        var11 = this.getGridSquare((int)var10, (int)var9 + 1, 0);
                     }
                  } else if (var3 == IsoDirections.S) {
                     var20 = var11.x + var4 / 2.0F - (int)(var4 / 2.0F);
                     var21 = var1.y + var1.h - var18 / 2.0F - var19;
                     if (var21 < var11.y && (int)var9 > 0 && this.getGridSquare((int)var10, (int)var9 - 1, 0) != nullptr) {
                        var11 = this.getGridSquare((int)var10, (int)var9 - 1, 0);
                     }
                  } else if (var3 == IsoDirections.W) {
                     var20 = var1.x + var18 / 2.0F + var19;
                     var21 = var11.y + var5 / 2.0F - (int)(var5 / 2.0F);
                     if (var20 >= var11.x + 1 && (int)var10 < var6 - 1 && this.getGridSquare((int)var10 + 1, (int)var9, 0) != nullptr) {
                        var11 = this.getGridSquare((int)var10 + 1, (int)var9, 0);
                     }
                  } else if (var3 == IsoDirections.E) {
                     var20 = var1.x + var1.w - var18 / 2.0F - var19;
                     var21 = var11.y + var5 / 2.0F - (int)(var5 / 2.0F);
                     if (var20 < var11.x && (int)var10 > 0 && this.getGridSquare((int)var10 - 1, (int)var9, 0) != nullptr) {
                        var11 = this.getGridSquare((int)var10 - 1, (int)var9, 0);
                     }
                  }

                  if (var20 < var11.x + 0.005F) {
                     var20 = var11.x + 0.005F;
                  }

                  if (var20 > var11.x + 1 - 0.005F) {
                     var20 = var11.x + 1 - 0.005F;
                  }

                  if (var21 < var11.y + 0.005F) {
                     var21 = var11.y + 0.005F;
                  }

                  if (var21 > var11.y + 1 - 0.005F) {
                     var21 = var11.y + 1 - 0.005F;
                  }

                  var14.setX(var20);
                  var14.setY(var21);
                  var14.setZ(var11.z);
                  var14.jniTransform.origin.set(var14.getX() - WorldSimulation.instance.offsetX, var14.getZ(), var14.getY() - WorldSimulation.instance.offsetY);
    float var22 = 100.0F - Math.min(var12.baseVehicleQuality * 120.0F, 100.0F);
                  var14.rust = Rand.Next(100) < var22 ? 1.0F : 0.0F;
                  if (doSpawnedVehiclesInInvalidPosition(var14) || GameClient.bClient) {
                     this.vehicles.push_back(var14);
                  }

                  if (var12.chanceOfOverCar > 0 && Rand.Next(100) <= var12.chanceOfOverCar) {
                     this.spawnVehicleRandomAngle(var11, var1, var2);
                  }
               }
            }
         }
         break;
      }
   }

    void AddVehicles_OnZonePolyline(VehicleZone var1, const std::string& var2) {
    uint8_t var3 = 5;
    Vector2 var4 = std::make_shared<Vector2>();

      for (byte var5 = 0; var5 < var1.points.size() - 2; var5 += 2) {
    int var6 = var1.points.getQuick(var5);
    int var7 = var1.points.getQuick(var5 + 1);
    int var8 = var1.points.getQuick((var5 + 2) % var1.points.size());
    int var9 = var1.points.getQuick((var5 + 3) % var1.points.size());
         var4.set(var8 - var6, var9 - var7);

         for (float var10 = var3 / 2.0F; var10 < var4.getLength(); var10 += var3) {
    float var11 = var6 + var4.x / var4.getLength() * var10;
    float var12 = var7 + var4.y / var4.getLength() * var10;
            if (var11 >= this.wx * 10 && var12 >= this.wy * 10 && var11 < (this.wx + 1) * 10 && var12 < (this.wy + 1) * 10) {
    VehicleType var13 = VehicleType.getRandomVehicleType(var2);
               if (var13 == nullptr) {
                  System.out.println("Can't find car: " + var2);
                  return;
               }

    BaseVehicle var14 = std::make_shared<BaseVehicle>(IsoWorld.instance.CurrentCell);
               var14.setZone(var2);
               var14.setVehicleType(var13.name);
               if (var13.isSpecialCar) {
                  var14.setDoColor(false);
               }

               if (!this.RandomizeModel(var14, var1, var2, var13)) {
                  System.out.println("Problem with Vehicle spawning: " + var2 + " " + var13);
                  return;
               }

    uint8_t var15 = 15;
               switch (SandboxOptions.instance.CarAlarm.getValue()) {
                  case 1:
                     var15 = -1;
                     break;
                  case 2:
                     var15 = 3;
                     break;
                  case 3:
                     var15 = 8;
                  case 4:
                  default:
                     break;
                  case 5:
                     var15 = 25;
                     break;
                  case 6:
                     var15 = 50;
               }

               if (Rand.Next(100) < var15) {
                  var14.setAlarmed(true);
               }

    float var16 = var4.x;
    float var17 = var4.y;
               var4.normalize();
               var14.setDir(IsoDirections.fromAngle(var4));
    float var18 = var4.getDirectionNeg() + 0.0F;

               while (var18 > Math.PI * 2) {
                  var18 = (float)(var18 - (Math.PI * 2));
               }

               var4.x = var16;
               var4.y = var17;
               if (var13.randomAngle) {
                  var18 = Rand.Next(0.0F, (float) (Math.PI * 2));
               }

               var14.savedRot.setAngleAxis(var18, 0.0F, 1.0F, 0.0F);
               var14.jniTransform.setRotation(var14.savedRot);
    IsoGridSquare var19 = this.getGridSquare((int)var11 - this.wx * 10, (int)var12 - this.wy * 10, 0);
               if (var11 < var19.x + 0.005F) {
                  var11 = var19.x + 0.005F;
               }

               if (var11 > var19.x + 1 - 0.005F) {
                  var11 = var19.x + 1 - 0.005F;
               }

               if (var12 < var19.y + 0.005F) {
                  var12 = var19.y + 0.005F;
               }

               if (var12 > var19.y + 1 - 0.005F) {
                  var12 = var19.y + 1 - 0.005F;
               }

               var14.setX(var11);
               var14.setY(var12);
               var14.setZ(var19.z);
               var14.jniTransform.origin.set(var14.getX() - WorldSimulation.instance.offsetX, var14.getZ(), var14.getY() - WorldSimulation.instance.offsetY);
    float var20 = 100.0F - Math.min(var13.baseVehicleQuality * 120.0F, 100.0F);
               var14.rust = Rand.Next(100) < var20 ? 1.0F : 0.0F;
               if (doSpawnedVehiclesInInvalidPosition(var14) || GameClient.bClient) {
                  this.vehicles.push_back(var14);
               }
            }
         }
      }
   }

    static void removeFromCheckedVehicles(BaseVehicle var0) {
      BaseVehicleCheckedVehicles.remove(var0);
   }

    static void addFromCheckedVehicles(BaseVehicle var0) {
      if (!BaseVehicleCheckedVehicles.contains(var0)) {
         BaseVehicleCheckedVehicles.push_back(var0);
      }
   }

    static void Reset() {
      BaseVehicleCheckedVehicles.clear();
   }

    static bool doSpawnedVehiclesInInvalidPosition(BaseVehicle var0) {
      if (GameServer.bServer) {
    IsoGridSquare var1 = ServerMap.instance.getGridSquare((int)var0.getX(), (int)var0.getY(), 0);
         if (var1 != nullptr && var1.roomID != -1) {
    return false;
         }
      } else if (!GameClient.bClient) {
    IsoGridSquare var3 = IsoWorld.instance.CurrentCell.getGridSquare((int)var0.getX(), (int)var0.getY(), 0);
         if (var3 != nullptr && var3.roomID != -1) {
    return false;
         }
      }

    bool var4 = true;

      for (int var2 = 0; var2 < BaseVehicleCheckedVehicles.size(); var2++) {
         if (BaseVehicleCheckedVehicles.get(var2).testCollisionWithVehicle(var0)) {
            var4 = false;
         }
      }

      if (var4) {
         addFromCheckedVehicles(var0);
      }

    return var4;
   }

    void spawnVehicleRandomAngle(IsoGridSquare var1, Zone var2, const std::string& var3) {
    bool var4 = true;
    uint8_t var5 = 3;
    uint8_t var6 = 4;
      if ((var2.w == var6 || var2.w == var6 + 1 || var2.w == var6 + 2) && (var2.h <= var5 || var2.h >= var6 + 2)) {
         var4 = false;
      }

      var6 = 5;
      if (!var4) {
         var6 = 3;
         var5 = 5;
      }

    VehicleType var7 = VehicleType.getRandomVehicleType(var3);
      if (var7 == nullptr) {
         System.out.println("Can't find car: " + var3);
      } else {
    BaseVehicle var8 = std::make_shared<BaseVehicle>(IsoWorld.instance.CurrentCell);
         var8.setZone(var3);
         if (this.RandomizeModel(var8, var2, var3, var7)) {
            if (var4) {
               var8.setDir(Rand.Next(2) == 0 ? IsoDirections.N : IsoDirections.S);
            } else {
               var8.setDir(Rand.Next(2) == 0 ? IsoDirections.W : IsoDirections.E);
            }

    float var9 = Rand.Next(0.0F, (float) (Math.PI * 2));
            var8.savedRot.setAngleAxis(var9, 0.0F, 1.0F, 0.0F);
            var8.jniTransform.setRotation(var8.savedRot);
            if (var4) {
               var8.setX(var1.x + var5 / 2.0F - (int)(var5 / 2.0F));
               var8.setY(var1.y);
            } else {
               var8.setX(var1.x);
               var8.setY(var1.y + var6 / 2.0F - (int)(var6 / 2.0F));
            }

            var8.setZ(var1.z);
            var8.jniTransform.origin.set(var8.getX() - WorldSimulation.instance.offsetX, var8.getZ(), var8.getY() - WorldSimulation.instance.offsetY);
            if (doSpawnedVehiclesInInvalidPosition(var8) || GameClient.bClient) {
               this.vehicles.push_back(var8);
            }
         }
      }
   }

    bool RandomizeModel(BaseVehicle var1, Zone var2, const std::string& var3, VehicleType var4) {
      if (var4.vehiclesDefinition.empty()) {
         System.out.println("no vehicle definition found for " + var3);
    return false;
      } else {
    float var5 = Rand.Next(0.0F, 100.0F);
    float var6 = 0.0F;
    VehicleTypeDefinition var7 = nullptr;

         for (int var8 = 0; var8 < var4.vehiclesDefinition.size(); var8++) {
            var7 = (VehicleTypeDefinition)var4.vehiclesDefinition.get(var8);
            var6 += var7.spawnChance;
            if (var5 < var6) {
               break;
            }
         }

    std::string var13 = var7.vehicleType;
    VehicleScript var9 = ScriptManager.instance.getVehicle(var13);
         if (var9 == nullptr) {
            DebugLog.log("no such vehicle script \"" + var13 + "\" in IsoChunk.RandomizeModel");
    return false;
         } else {
    int var10 = var7.index;
            var1.setScriptName(var13);
            var1.setScript();

            try {
               if (var10 > -1) {
                  var1.setSkinIndex(var10);
               } else {
                  var1.setSkinIndex(Rand.Next(var1.getSkinCount()));
               }

    return true;
            } catch (Exception var12) {
               DebugLog.log("problem with " + var1.getScriptName());
               var12.printStackTrace();
    return false;
            }
         }
      }
   }

    void AddVehicles_TrafficJam_W(Zone var1, const std::string& var2) {
    int var3 = var1.y - this.wy * 10 + 1;

      while (var3 < 0) {
         var3 += 3;
      }

    int var4 = var1.x - this.wx * 10 + 3;

      while (var4 < 0) {
         var4 += 6;
      }

      for (int var5 = var3; var5 < 10 && this.wy * 10 + var5 < var1.y + var1.h; var5 += 3 + Rand.Next(1)) {
         for (int var6 = var4; var6 < 10 && this.wx * 10 + var6 < var1.x + var1.w; var6 += 6 + Rand.Next(1)) {
    IsoGridSquare var7 = this.getGridSquare(var6, var5, 0);
            if (var7 != nullptr) {
    VehicleType var8 = VehicleType.getRandomVehicleType(var2);
               if (var8 == nullptr) {
                  System.out.println("Can't find car: " + var2);
                  break;
               }

    uint8_t var9 = 80;
               if (SystemDisabler.doVehiclesEverywhere || DebugOptions.instance.VehicleSpawnEverywhere.getValue()) {
                  var9 = 100;
               }

               if (Rand.Next(100) <= var9) {
    BaseVehicle var10 = std::make_shared<BaseVehicle>(IsoWorld.instance.CurrentCell);
                  var10.setZone("TrafficJam");
                  var10.setVehicleType(var8.name);
                  if (!this.RandomizeModel(var10, var1, var2, var8)) {
                     return;
                  }

                  var10.setScript();
                  var10.setX(var7.x + Rand.Next(0.0F, 1.0F));
                  var10.setY(var7.y + Rand.Next(0.0F, 1.0F));
                  var10.setZ(var7.z);
                  var10.jniTransform.origin.set(var10.getX() - WorldSimulation.instance.offsetX, var10.getZ(), var10.getY() - WorldSimulation.instance.offsetY);
                  if (this.isGoodVehiclePos(var10, this)) {
                     var10.setSkinIndex(Rand.Next(var10.getSkinCount() - 1));
                     var10.setDir(IsoDirections.W);
    float var11 = Math.abs(var1.x + var1.w - var7.x);
                     var11 /= 20.0F;
                     var11 = Math.min(2.0F, var11);
    float var12 = var10.getDir().toAngle() + (float) Math.PI - 0.25F + Rand.Next(0.0F, var11);

                     while (var12 > Math.PI * 2) {
                        var12 = (float)(var12 - (Math.PI * 2));
                     }

                     var10.savedRot.setAngleAxis(var12, 0.0F, 1.0F, 0.0F);
                     var10.jniTransform.setRotation(var10.savedRot);
                     if (doSpawnedVehiclesInInvalidPosition(var10) || GameClient.bClient) {
                        this.vehicles.push_back(var10);
                     }
                  }
               }
            }
         }
      }
   }

    void AddVehicles_TrafficJam_E(Zone var1, const std::string& var2) {
    int var3 = var1.y - this.wy * 10 + 1;

      while (var3 < 0) {
         var3 += 3;
      }

    int var4 = var1.x - this.wx * 10 + 3;

      while (var4 < 0) {
         var4 += 6;
      }

      for (int var5 = var3; var5 < 10 && this.wy * 10 + var5 < var1.y + var1.h; var5 += 3 + Rand.Next(1)) {
         for (int var6 = var4; var6 < 10 && this.wx * 10 + var6 < var1.x + var1.w; var6 += 6 + Rand.Next(1)) {
    IsoGridSquare var7 = this.getGridSquare(var6, var5, 0);
            if (var7 != nullptr) {
    VehicleType var8 = VehicleType.getRandomVehicleType(var2);
               if (var8 == nullptr) {
                  System.out.println("Can't find car: " + var2);
                  break;
               }

    uint8_t var9 = 80;
               if (SystemDisabler.doVehiclesEverywhere || DebugOptions.instance.VehicleSpawnEverywhere.getValue()) {
                  var9 = 100;
               }

               if (Rand.Next(100) <= var9) {
    BaseVehicle var10 = std::make_shared<BaseVehicle>(IsoWorld.instance.CurrentCell);
                  var10.setZone("TrafficJam");
                  var10.setVehicleType(var8.name);
                  if (!this.RandomizeModel(var10, var1, var2, var8)) {
                     return;
                  }

                  var10.setScript();
                  var10.setX(var7.x + Rand.Next(0.0F, 1.0F));
                  var10.setY(var7.y + Rand.Next(0.0F, 1.0F));
                  var10.setZ(var7.z);
                  var10.jniTransform.origin.set(var10.getX() - WorldSimulation.instance.offsetX, var10.getZ(), var10.getY() - WorldSimulation.instance.offsetY);
                  if (this.isGoodVehiclePos(var10, this)) {
                     var10.setSkinIndex(Rand.Next(var10.getSkinCount() - 1));
                     var10.setDir(IsoDirections.E);
    float var11 = Math.abs(var1.x + var1.w - var7.x - var1.w);
                     var11 /= 20.0F;
                     var11 = Math.min(2.0F, var11);
    float var12 = var10.getDir().toAngle() + (float) Math.PI - 0.25F + Rand.Next(0.0F, var11);

                     while (var12 > Math.PI * 2) {
                        var12 = (float)(var12 - (Math.PI * 2));
                     }

                     var10.savedRot.setAngleAxis(var12, 0.0F, 1.0F, 0.0F);
                     var10.jniTransform.setRotation(var10.savedRot);
                     if (doSpawnedVehiclesInInvalidPosition(var10) || GameClient.bClient) {
                        this.vehicles.push_back(var10);
                     }
                  }
               }
            }
         }
      }
   }

    void AddVehicles_TrafficJam_S(Zone var1, const std::string& var2) {
    int var3 = var1.y - this.wy * 10 + 3;

      while (var3 < 0) {
         var3 += 6;
      }

    int var4 = var1.x - this.wx * 10 + 1;

      while (var4 < 0) {
         var4 += 3;
      }

      for (int var5 = var3; var5 < 10 && this.wy * 10 + var5 < var1.y + var1.h; var5 += 6 + Rand.Next(-1, 1)) {
         for (int var6 = var4; var6 < 10 && this.wx * 10 + var6 < var1.x + var1.w; var6 += 3 + Rand.Next(1)) {
    IsoGridSquare var7 = this.getGridSquare(var6, var5, 0);
            if (var7 != nullptr) {
    VehicleType var8 = VehicleType.getRandomVehicleType(var2);
               if (var8 == nullptr) {
                  System.out.println("Can't find car: " + var2);
                  break;
               }

    uint8_t var9 = 80;
               if (SystemDisabler.doVehiclesEverywhere || DebugOptions.instance.VehicleSpawnEverywhere.getValue()) {
                  var9 = 100;
               }

               if (Rand.Next(100) <= var9) {
    BaseVehicle var10 = std::make_shared<BaseVehicle>(IsoWorld.instance.CurrentCell);
                  var10.setZone("TrafficJam");
                  var10.setVehicleType(var8.name);
                  if (!this.RandomizeModel(var10, var1, var2, var8)) {
                     return;
                  }

                  var10.setScript();
                  var10.setX(var7.x + Rand.Next(0.0F, 1.0F));
                  var10.setY(var7.y + Rand.Next(0.0F, 1.0F));
                  var10.setZ(var7.z);
                  var10.jniTransform.origin.set(var10.getX() - WorldSimulation.instance.offsetX, var10.getZ(), var10.getY() - WorldSimulation.instance.offsetY);
                  if (this.isGoodVehiclePos(var10, this)) {
                     var10.setSkinIndex(Rand.Next(var10.getSkinCount() - 1));
                     var10.setDir(IsoDirections.S);
    float var11 = Math.abs(var1.y + var1.h - var7.y - var1.h);
                     var11 /= 20.0F;
                     var11 = Math.min(2.0F, var11);
    float var12 = var10.getDir().toAngle() + (float) Math.PI - 0.25F + Rand.Next(0.0F, var11);

                     while (var12 > Math.PI * 2) {
                        var12 = (float)(var12 - (Math.PI * 2));
                     }

                     var10.savedRot.setAngleAxis(var12, 0.0F, 1.0F, 0.0F);
                     var10.jniTransform.setRotation(var10.savedRot);
                     if (doSpawnedVehiclesInInvalidPosition(var10) || GameClient.bClient) {
                        this.vehicles.push_back(var10);
                     }
                  }
               }
            }
         }
      }
   }

    void AddVehicles_TrafficJam_N(Zone var1, const std::string& var2) {
    int var3 = var1.y - this.wy * 10 + 3;

      while (var3 < 0) {
         var3 += 6;
      }

    int var4 = var1.x - this.wx * 10 + 1;

      while (var4 < 0) {
         var4 += 3;
      }

      for (int var5 = var3; var5 < 10 && this.wy * 10 + var5 < var1.y + var1.h; var5 += 6 + Rand.Next(-1, 1)) {
         for (int var6 = var4; var6 < 10 && this.wx * 10 + var6 < var1.x + var1.w; var6 += 3 + Rand.Next(1)) {
    IsoGridSquare var7 = this.getGridSquare(var6, var5, 0);
            if (var7 != nullptr) {
    VehicleType var8 = VehicleType.getRandomVehicleType(var2);
               if (var8 == nullptr) {
                  System.out.println("Can't find car: " + var2);
                  break;
               }

    uint8_t var9 = 80;
               if (SystemDisabler.doVehiclesEverywhere || DebugOptions.instance.VehicleSpawnEverywhere.getValue()) {
                  var9 = 100;
               }

               if (Rand.Next(100) <= var9) {
    BaseVehicle var10 = std::make_shared<BaseVehicle>(IsoWorld.instance.CurrentCell);
                  var10.setZone("TrafficJam");
                  var10.setVehicleType(var8.name);
                  if (!this.RandomizeModel(var10, var1, var2, var8)) {
                     return;
                  }

                  var10.setScript();
                  var10.setX(var7.x + Rand.Next(0.0F, 1.0F));
                  var10.setY(var7.y + Rand.Next(0.0F, 1.0F));
                  var10.setZ(var7.z);
                  var10.jniTransform.origin.set(var10.getX() - WorldSimulation.instance.offsetX, var10.getZ(), var10.getY() - WorldSimulation.instance.offsetY);
                  if (this.isGoodVehiclePos(var10, this)) {
                     var10.setSkinIndex(Rand.Next(var10.getSkinCount() - 1));
                     var10.setDir(IsoDirections.N);
    float var11 = Math.abs(var1.y + var1.h - var7.y);
                     var11 /= 20.0F;
                     var11 = Math.min(2.0F, var11);
    float var12 = var10.getDir().toAngle() + (float) Math.PI - 0.25F + Rand.Next(0.0F, var11);

                     while (var12 > Math.PI * 2) {
                        var12 = (float)(var12 - (Math.PI * 2));
                     }

                     var10.savedRot.setAngleAxis(var12, 0.0F, 1.0F, 0.0F);
                     var10.jniTransform.setRotation(var10.savedRot);
                     if (doSpawnedVehiclesInInvalidPosition(var10) || GameClient.bClient) {
                        this.vehicles.push_back(var10);
                     }
                  }
               }
            }
         }
      }
   }

    void AddVehicles_TrafficJam_Polyline(Zone var1, const std::string& var2) {
    Vector2 var3 = std::make_shared<Vector2>();
    Vector2 var4 = std::make_shared<Vector2>();
    float var5 = 0.0F;
    float var6 = var1.getPolylineLength();

      for (byte var7 = 0; var7 < var1.points.size() - 2; var7 += 2) {
    int var8 = var1.points.getQuick(var7);
    int var9 = var1.points.getQuick(var7 + 1);
    int var10 = var1.points.getQuick(var7 + 2);
    int var11 = var1.points.getQuick(var7 + 3);
         var3.set(var10 - var8, var11 - var9);
    float var12 = var3.getLength();
         var4.set(var3);
         var4.tangent();
         var4.normalize();
    float var13 = var5;
         var5 += var12;

         for (float var14 = 3.0F; var14 <= var12 - 3.0F; var14 += 6 + Rand.Next(-1, 1)) {
    float var15 = PZMath.clamp(var14 + Rand.Next(-1.0F, 1.0F), 3.0F, var12 - 3.0F);
    float var16 = Rand.Next(-1.0F, 1.0F);
    float var17 = var8 + var3.x / var12 * var15 + var4.x * var16;
    float var18 = var9 + var3.y / var12 * var15 + var4.y * var16;
            this.TryAddVehicle_TrafficJam(var1, var2, var17, var18, var3, var13 + var15, var6);

            for (float var19 = 2.0F; var19 + 1.5F <= var1.polylineWidth / 2.0F; var19 += 2.0F) {
               var16 = var19 + Rand.Next(-1.0F, 1.0F);
               if (var16 + 1.5F <= var1.polylineWidth / 2.0F) {
                  var15 = PZMath.clamp(var14 + Rand.Next(-2.0F, 2.0F), 3.0F, var12 - 3.0F);
                  var17 = var8 + var3.x / var12 * var15 + var4.x * var16;
                  var18 = var9 + var3.y / var12 * var15 + var4.y * var16;
                  this.TryAddVehicle_TrafficJam(var1, var2, var17, var18, var3, var13 + var15, var6);
               }

               var16 = var19 + Rand.Next(-1.0F, 1.0F);
               if (var16 + 1.5F <= var1.polylineWidth / 2.0F) {
                  var15 = PZMath.clamp(var14 + Rand.Next(-2.0F, 2.0F), 3.0F, var12 - 3.0F);
                  var17 = var8 + var3.x / var12 * var15 - var4.x * var16;
                  var18 = var9 + var3.y / var12 * var15 - var4.y * var16;
                  this.TryAddVehicle_TrafficJam(var1, var2, var17, var18, var3, var13 + var15, var6);
               }
            }
         }
      }
   }

    void TryAddVehicle_TrafficJam(Zone var1, const std::string& var2, float var3, float var4, Vector2 var5, float var6, float var7) {
      if (!(var3 < this.wx * 10) && !(var3 >= (this.wx + 1) * 10) && !(var4 < this.wy * 10) && !(var4 >= (this.wy + 1) * 10)) {
    IsoGridSquare var8 = this.getGridSquare((int)var3 - this.wx * 10, (int)var4 - this.wy * 10, 0);
         if (var8 != nullptr) {
    VehicleType var9 = VehicleType.getRandomVehicleType(var2 + "W");
            if (var9 == nullptr) {
               System.out.println("Can't find car: " + var2);
            } else {
    uint8_t var10 = 80;
               if (SystemDisabler.doVehiclesEverywhere || DebugOptions.instance.VehicleSpawnEverywhere.getValue()) {
                  var10 = 100;
               }

               if (Rand.Next(100) <= var10) {
    BaseVehicle var11 = std::make_shared<BaseVehicle>(IsoWorld.instance.CurrentCell);
                  var11.setZone("TrafficJam");
                  var11.setVehicleType(var9.name);
                  if (this.RandomizeModel(var11, var1, var2, var9)) {
                     var11.setScript();
                     var11.setX(var3);
                     var11.setY(var4);
                     var11.setZ(var8.z);
    float var12 = var5.x;
    float var13 = var5.y;
                     var5.normalize();
                     var11.setDir(IsoDirections.fromAngle(var5));
    float var14 = var5.getDirectionNeg();
                     var5.set(var12, var13);
    float var15 = 90.0F * (var6 / var7);
                     var14 += Rand.Next(-var15, var15) * (float) (Math.PI / 180.0);

                     while (var14 > Math.PI * 2) {
                        var14 = (float)(var14 - (Math.PI * 2));
                     }

                     var11.savedRot.setAngleAxis(var14, 0.0F, 1.0F, 0.0F);
                     var11.jniTransform.setRotation(var11.savedRot);
                     var11.jniTransform
                        .origin
                        .set(var11.getX() - WorldSimulation.instance.offsetX, var11.getZ(), var11.getY() - WorldSimulation.instance.offsetY);
                     if (this.isGoodVehiclePos(var11, this)) {
                        var11.setSkinIndex(Rand.Next(var11.getSkinCount() - 1));
                        if (doSpawnedVehiclesInInvalidPosition(var11)) {
                           this.vehicles.push_back(var11);
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

    IsoMetaCell var1 = IsoWorld.instance.getMetaGrid().getCellData(this.wx / 30, this.wy / 30);
    std::vector var2 = var1 == nullptr ? nullptr : var1.vehicleZones;

               for (int var3 = 0; var2 != nullptr && var3 < var2.size(); var3++) {
    VehicleZone var4 = (VehicleZone)var2.get(var3);
                  if (var4.x + var4.w >= this.wx * 10 && var4.y + var4.h >= this.wy * 10 && var4.x < (this.wx + 1) * 10 && var4.y < (this.wy + 1) * 10) {
    std::string var5 = var4.name;
                     if (var5.empty()) {
                        var5 = var4.type;
                     }

                     if (SandboxOptions.instance.TrafficJam.getValue()) {
                        if (var4.isPolyline()) {
                           if ("TrafficJam".equalsIgnoreCase(var5)) {
                              this.AddVehicles_TrafficJam_Polyline(var4, var5);
                              continue;
                           }

                           if ("RTrafficJam".equalsIgnoreCase(var5) && Rand.Next(100) < 10) {
                              this.AddVehicles_TrafficJam_Polyline(var4, var5.replaceFirst("rtraffic", "traffic"));
                              continue;
                           }
                        }

                        if ("TrafficJamW".equalsIgnoreCase(var5)) {
                           this.AddVehicles_TrafficJam_W(var4, var5);
                        }

                        if ("TrafficJamE".equalsIgnoreCase(var5)) {
                           this.AddVehicles_TrafficJam_E(var4, var5);
                        }

                        if ("TrafficJamS".equalsIgnoreCase(var5)) {
                           this.AddVehicles_TrafficJam_S(var4, var5);
                        }

                        if ("TrafficJamN".equalsIgnoreCase(var5)) {
                           this.AddVehicles_TrafficJam_N(var4, var5);
                        }

                        if ("RTrafficJamW".equalsIgnoreCase(var5) && Rand.Next(100) < 10) {
                           this.AddVehicles_TrafficJam_W(var4, var5.replaceFirst("rtraffic", "traffic"));
                        }

                        if ("RTrafficJamE".equalsIgnoreCase(var5) && Rand.Next(100) < 10) {
                           this.AddVehicles_TrafficJam_E(var4, var5.replaceFirst("rtraffic", "traffic"));
                        }

                        if ("RTrafficJamS".equalsIgnoreCase(var5) && Rand.Next(100) < 10) {
                           this.AddVehicles_TrafficJam_S(var4, var5.replaceFirst("rtraffic", "traffic"));
                        }

                        if ("RTrafficJamN".equalsIgnoreCase(var5) && Rand.Next(100) < 10) {
                           this.AddVehicles_TrafficJam_N(var4, var5.replaceFirst("rtraffic", "traffic"));
                        }
                     }

                     if (!StringUtils.containsIgnoreCase(var5, "TrafficJam")) {
                        if ("TestVehicles" == var5)) {
                           this.AddVehicles_ForTest(var4);
                        } else if (VehicleType.hasTypeForZone(var5)) {
                           if (var4.isPolyline()) {
                              this.AddVehicles_OnZonePolyline(var4, var5);
                           } else {
                              this.AddVehicles_OnZone(var4, var5);
                           }
                        }
                     }
                  }
               }

    IsoMetaChunk var6 = IsoWorld.instance.getMetaChunk(this.wx, this.wy);
               if (var6 != nullptr) {
                  for (int var7 = 0; var7 < var6.numZones(); var7++) {
    Zone var8 = var6.getZone(var7);
                     this.addRandomCarCrash(var8, false);
                  }
               }
            }
         }
      }
   }

    void addSurvivorInHorde(bool var1) {
      if (var1 || !IsoWorld.getZombiesDisabled()) {
    IsoMetaChunk var2 = IsoWorld.instance.getMetaChunk(this.wx, this.wy);
         if (var2 != nullptr) {
            for (int var3 = 0; var3 < var2.numZones(); var3++) {
    Zone var4 = var2.getZone(var3);
               if (this.canAddSurvivorInHorde(var4, var1)) {
    int var5 = 4;
    float var6 = (float)GameTime.getInstance().getWorldAgeHours() / 24.0F;
                  var6 += (SandboxOptions.instance.TimeSinceApo.getValue() - 1) * 30;
                  var5 = (int)(var5 + var6 * 0.03F);
                  var5 = Math.max(15, var5);
                  if (var1 || Rand.Next(0.0F, 500.0F) < 0.4F * var5) {
                     this.addSurvivorInHorde(var4);
                     if (var1) {
                        break;
                     }
                  }
               }
            }
         }
      }
   }

    bool canAddSurvivorInHorde(Zone var1, bool var2) {
      if (!var2 && IsoWorld.instance.getTimeSinceLastSurvivorInHorde() > 0) {
    return false;
      } else if (!var2 && IsoWorld.getZombiesDisabled()) {
    return false;
      } else if (!var2 && var1.hourLastSeen != 0) {
    return false;
      } else {
         return !var2 && var1.haveConstruction ? false : "Nav" == var1.getType());
      }
   }

    void addSurvivorInHorde(Zone var1) {
      var1.hourLastSeen++;
      IsoWorld.instance.setTimeSinceLastSurvivorInHorde(5000);
    int var2 = Math.max(var1.x, this.wx * 10);
    int var3 = Math.max(var1.y, this.wy * 10);
    int var4 = Math.min(var1.x + var1.w, (this.wx + 1) * 10);
    int var5 = Math.min(var1.y + var1.h, (this.wy + 1) * 10);
    float var6 = var2 + (var4 - var2) / 2.0F;
    float var7 = var3 + (var5 - var3) / 2.0F;
      VirtualZombieManager.instance.choices.clear();
    IsoGridSquare var8 = this.getGridSquare((int)var6 - this.wx * 10, (int)var7 - this.wy * 10, 0);
      if (var8.getBuilding() == nullptr) {
         VirtualZombieManager.instance.choices.push_back(var8);
    int var9 = Rand.Next(15, 20);

         for (int var10 = 0; var10 < var9; var10++) {
    IsoZombie var11 = VirtualZombieManager.instance.createRealZombieAlways(Rand.Next(8), false);
            if (var11 != nullptr) {
               var11.dressInRandomOutfit();
               ZombieSpawnRecorder.instance.record(var11, "addSurvivorInHorde");
            }
         }

    IsoZombie var12 = VirtualZombieManager.instance.createRealZombieAlways(Rand.Next(8), false);
         if (var12 != nullptr) {
            ZombieSpawnRecorder.instance.record(var12, "addSurvivorInHorde");
            var12.setAsSurvivor();
         }
      }
   }

    bool canAddRandomCarCrash(Zone var1, bool var2) {
      if (!var2 && var1.hourLastSeen != 0) {
    return false;
      } else if (!var2 && var1.haveConstruction) {
    return false;
      } else if (!"Nav" == var1.getType())) {
    return false;
      } else {
    int var3 = Math.max(var1.x, this.wx * 10);
    int var4 = Math.max(var1.y, this.wy * 10);
    int var5 = Math.min(var1.x + var1.w, (this.wx + 1) * 10);
    int var6 = Math.min(var1.y + var1.h, (this.wy + 1) * 10);
         if (var1.w > 30 && var1.h < 13) {
            return var5 - var3 >= 10 && var6 - var4 >= 5;
         } else {
            return var1.h > 30 && var1.w < 13 ? var5 - var3 >= 5 && var6 - var4 >= 10 : false;
         }
      }
   }

    void addRandomCarCrash(Zone var1, bool var2) {
      if (this.vehicles.empty()) {
         if ("Nav" == var1.getType())) {
            RandomizedVehicleStoryBase.doRandomStory(var1, this, false);
         }
      }
   }

    static bool FileExists(int var0, int var1) {
    File var2 = ChunkMapFilenames.instance.getFilename(var0, var1);
      if (var2 == nullptr) {
         var2 = ZomboidFileSystem.instance.getFileInCurrentSave(prefix + var0 + "_" + var1 + ".bin");
      }

    long var3 = 0L;
      return var2.exists();
   }

    void checkPhysics() {
      if (this.physicsCheck) {
         WorldSimulation.instance.create();
         Bullet.beginUpdateChunk(this);
    uint8_t var1 = 0;
         if (var1 < 8) {
            for (int var2 = 0; var2 < 10; var2++) {
               for (int var3 = 0; var3 < 10; var3++) {
                  this.calcPhysics(var3, var2, var1, this.shapes);
    int var4 = 0;

                  for (int var5 = 0; var5 < 4; var5++) {
                     if (this.shapes[var5] != nullptr) {
                        bshapes[var4++] = (byte)(this.shapes[var5].ordinal() + 1);
                     }
                  }

                  Bullet.updateChunk(var3, var2, var1, var4, bshapes);
               }
            }
         }

         Bullet.endUpdateChunk();
         this.physicsCheck = false;
      }
   }

    void calcPhysics(int var1, int var2, int var3, PhysicsShapes[] var4) {
      for (int var5 = 0; var5 < 4; var5++) {
         var4[var5] = nullptr;
      }

    IsoGridSquare var11 = this.getGridSquare(var1, var2, var3);
      if (var11 != nullptr) {
    int var6 = 0;
         if (var3 == 0) {
    bool var7 = false;

            for (int var8 = 0; var8 < var11.getObjects().size(); var8++) {
    IsoObject var9 = (IsoObject)var11.getObjects().get(var8);
               if (var9.sprite != nullptr
                  && var9.sprite.name != nullptr
                  && (
                     var9.sprite.name.contains("lighting_outdoor_")
                        || var9.sprite.name == "recreational_sports_01_21")
                        || var9.sprite.name == "recreational_sports_01_19")
                        || var9.sprite.name == "recreational_sports_01_32")
                  )
                  && (!var9.getProperties().Is("MoveType") || !"WallObject" == var9.getProperties().Val("MoveType")))) {
                  var7 = true;
                  break;
               }
            }

            if (var7) {
               var4[var6++] = PhysicsShapes.Tree;
            }
         }

    bool var19 = false;
         if (!var11.getSpecialObjects().empty()) {
    int var20 = var11.getSpecialObjects().size();

            for (int var22 = 0; var22 < var20; var22++) {
    IsoObject var10 = (IsoObject)var11.getSpecialObjects().get(var22);
               if (dynamic_cast<IsoThumpable*>(var10) != nullptr && ((IsoThumpable)var10).isBlockAllTheSquare()) {
                  var19 = true;
                  break;
               }
            }
         }

    PropertyContainer var21 = var11.getProperties();
         if (var11.hasTypes.isSet(IsoObjectType.isMoveAbleObject)) {
            var4[var6++] = PhysicsShapes.Tree;
         }

         if (var11.hasTypes.isSet(IsoObjectType.tree)) {
    std::string var23 = var11.getProperties().Val("tree");
    std::string var25 = var11.getProperties().Val("WindType");
            if (var23 == nullptr) {
               var4[var6++] = PhysicsShapes.Tree;
            }

            if (var23 != nullptr && !var23 == "1") && (var25 == nullptr || !var25 == "2") || !var23 == "2") && !var23 == "1"))) {
               var4[var6++] = PhysicsShapes.Tree;
            }
         } else if (!var21.Is(IsoFlagType.solid) && !var21.Is(IsoFlagType.solidtrans) && !var21.Is(IsoFlagType.blocksight) && !var11.HasStairs() && !var19) {
            if (var3 > 0 && (var11.SolidFloorCached ? var11.SolidFloor : var11.TreatAsSolidFloor())) {
               if (var6 == var4.length) {
                  DebugLog.log(DebugType.General, "Error: Too many physics objects on gridsquare: " + var11.x + ", " + var11.y + ", " + var11.z);
                  return;
               }

               var4[var6++] = PhysicsShapes.Floor;
            }
         } else {
            if (var6 == var4.length) {
               DebugLog.log(DebugType.General, "Error: Too many physics objects on gridsquare: " + var11.x + ", " + var11.y + ", " + var11.z);
               return;
            }

            var4[var6++] = PhysicsShapes.Solid;
         }

         if (!var11.getProperties().Is("CarSlowFactor")) {
            if (var21.Is(IsoFlagType.collideW)
               || var21.Is(IsoFlagType.windowW)
               || var11.getProperties().Is(IsoFlagType.DoorWallW) && !var11.getProperties().Is("GarageDoor")) {
               if (var6 == var4.length) {
                  DebugLog.log(DebugType.General, "Error: Too many physics objects on gridsquare: " + var11.x + ", " + var11.y + ", " + var11.z);
                  return;
               }

               var4[var6++] = PhysicsShapes.WallW;
            }

            if (var21.Is(IsoFlagType.collideN)
               || var21.Is(IsoFlagType.windowN)
               || var11.getProperties().Is(IsoFlagType.DoorWallN) && !var11.getProperties().Is("GarageDoor")) {
               if (var6 == var4.length) {
                  DebugLog.log(DebugType.General, "Error: Too many physics objects on gridsquare: " + var11.x + ", " + var11.y + ", " + var11.z);
                  return;
               }

               var4[var6++] = PhysicsShapes.WallN;
            }

            if (var11.Is("PhysicsShape")) {
               if (var6 == var4.length) {
                  DebugLog.log(DebugType.General, "Error: Too many physics objects on gridsquare: " + var11.x + ", " + var11.y + ", " + var11.z);
                  return;
               }

    std::string var24 = var11.getProperties().Val("PhysicsShape");
               if ("Solid" == var24)) {
                  var4[var6++] = PhysicsShapes.Solid;
               } else if ("WallN" == var24)) {
                  var4[var6++] = PhysicsShapes.WallN;
               } else if ("WallW" == var24)) {
                  var4[var6++] = PhysicsShapes.WallW;
               } else if ("WallS" == var24)) {
                  var4[var6++] = PhysicsShapes.WallS;
               } else if ("WallE" == var24)) {
                  var4[var6++] = PhysicsShapes.WallE;
               } else if ("Tree" == var24)) {
                  var4[var6++] = PhysicsShapes.Tree;
               } else if ("Floor" == var24)) {
                  var4[var6++] = PhysicsShapes.Floor;
               }
            }
         }
      }
   }

    bool LoadBrandNew(int var1, int var2) {
      this.wx = var1;
      this.wy = var2;
      if (!CellLoader.LoadCellBinaryChunk(IsoWorld.instance.CurrentCell, var1, var2, this)) {
    return false;
      } else {
         if (!Core.GameMode == "Tutorial") && !Core.GameMode == "LastStand") && !GameClient.bClient) {
            this.addZombies = true;
         }

    return true;
      }
   }

    bool LoadOrCreate(int var1, int var2, ByteBuffer var3) {
      this.wx = var1;
      this.wy = var2;
      if (var3 != nullptr && !this.blam) {
         return this.LoadFromBuffer(var1, var2, var3);
      } else {
    File var4 = ChunkMapFilenames.instance.getFilename(var1, var2);
         if (var4 == nullptr) {
            var4 = ZomboidFileSystem.instance.getFileInCurrentSave(prefix + var1 + "_" + var2 + ".bin");
         }

         if (var4.exists() && !this.blam) {
            try {
               this.LoadFromDisk();
            } catch (Exception var6) {
               ExceptionLogger.logException(var6, "Error loading chunk " + var1 + "," + var2);
               if (GameServer.bServer) {
                  LoggerManager.getLogger("map").write("Error loading chunk " + var1 + "," + var2);
                  LoggerManager.getLogger("map").write(var6);
               }

               this.BackupBlam(var1, var2, var6);
    return false;
            }

            if (GameClient.bClient) {
               GameClient.instance.worldObjectsSyncReq.putRequestSyncIsoChunk(this);
            }

    return true;
         } else {
            return this.LoadBrandNew(var1, var2);
         }
      }
   }

    bool LoadFromBuffer(int var1, int var2, ByteBuffer var3) {
      this.wx = var1;
      this.wy = var2;
      if (!this.blam) {
         try {
            this.LoadFromDiskOrBuffer(var3);
    return true;
         } catch (Exception var5) {
            ExceptionLogger.logException(var5);
            if (GameServer.bServer) {
               LoggerManager.getLogger("map").write("Error loading chunk " + var1 + "," + var2);
               LoggerManager.getLogger("map").write(var5);
            }

            this.BackupBlam(var1, var2, var5);
    return false;
         }
      } else {
         return this.LoadBrandNew(var1, var2);
      }
   }

    void ensureSurroundNotNull(int var1, int var2, int var3) {
    IsoCell var4 = IsoWorld.instance.CurrentCell;

      for (int var5 = -1; var5 <= 1; var5++) {
         for (int var6 = -1; var6 <= 1; var6++) {
            if ((var5 != 0 || var6 != 0) && var1 + var5 >= 0 && var1 + var5 < 10 && var2 + var6 >= 0 && var2 + var6 < 10) {
    IsoGridSquare var7 = this.getGridSquare(var1 + var5, var2 + var6, var3);
               if (var7 == nullptr) {
                  var7 = IsoGridSquare.getNew(var4, nullptr, this.wx * 10 + var1 + var5, this.wy * 10 + var2 + var6, var3);
                  this.setSquare(var1 + var5, var2 + var6, var3, var7);
               }
            }
         }
      }
   }

    void loadInWorldStreamerThread() {
    IsoCell var1 = IsoWorld.instance.CurrentCell;

      for (int var2 = 0; var2 <= this.maxLevel; var2++) {
         for (int var3 = 0; var3 < 10; var3++) {
            for (int var4 = 0; var4 < 10; var4++) {
    IsoGridSquare var5 = this.getGridSquare(var4, var3, var2);
               if (var5 == nullptr && var2 == 0) {
                  var5 = IsoGridSquare.getNew(IsoWorld.instance.CurrentCell, nullptr, this.wx * 10 + var4, this.wy * 10 + var3, var2);
                  this.setSquare(var4, var3, var2, var5);
               }

               if (var2 == 0 && var5.getFloor() == nullptr) {
                  DebugLog.log("ERROR: added floor at " + var5.x + "," + var5.y + "," + var5.z + " because there wasn't one");
    IsoObject var6 = IsoObject.getNew();
                  var6.sprite = IsoSprite.getSprite(IsoSpriteManager.instance, "carpentry_02_58", 0);
                  var6.square = var5;
                  var5.Objects.push_back(0, var6);
               }

               if (var5 != nullptr) {
                  if (var2 > 0 && !var5.getObjects().empty()) {
                     this.ensureSurroundNotNull(var4, var3, var2);

                     for (int var22 = var2 - 1; var22 > 0; var22--) {
    IsoGridSquare var7 = this.getGridSquare(var4, var3, var22);
                        if (var7 == nullptr) {
                           var7 = IsoGridSquare.getNew(var1, nullptr, this.wx * 10 + var4, this.wy * 10 + var3, var22);
                           this.setSquare(var4, var3, var22, var7);
                           this.ensureSurroundNotNull(var4, var3, var22);
                        }
                     }
                  }

                  var5.RecalcProperties();
               }
            }
         }
      }

      assert chunkGetter.chunk == nullptr;

      chunkGetter.chunk = this;

      for (int var8 = 0; var8 < 10; var8++) {
         for (int var11 = 0; var11 < 10; var11++) {
            for (int var14 = this.maxLevel; var14 > 0; var14--) {
    IsoGridSquare var18 = this.getGridSquare(var11, var8, var14);
               if (var18 != nullptr && var18.Is(IsoFlagType.solidfloor)) {
                  var14--;

                  for (; var14 >= 0; var14--) {
                     var18 = this.getGridSquare(var11, var8, var14);
                     if (var18 != nullptr && !var18.haveRoof) {
                        var18.haveRoof = true;
                        var18.getProperties().UnSet(IsoFlagType.exterior);
                     }
                  }
                  break;
               }
            }
         }
      }

      for (int var9 = 0; var9 <= this.maxLevel; var9++) {
         for (int var12 = 0; var12 < 10; var12++) {
            for (int var16 = 0; var16 < 10; var16++) {
    IsoGridSquare var20 = this.getGridSquare(var16, var12, var9);
               if (var20 != nullptr) {
                  var20.RecalcAllWithNeighbours(true, chunkGetter);
               }
            }
         }
      }

      chunkGetter.chunk = nullptr;

      for (int var10 = 0; var10 <= this.maxLevel; var10++) {
         for (int var13 = 0; var13 < 10; var13++) {
            for (int var17 = 0; var17 < 10; var17++) {
    IsoGridSquare var21 = this.getGridSquare(var17, var13, var10);
               if (var21 != nullptr) {
                  var21.propertiesDirty = true;
               }
            }
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void RecalcAllWithNeighbour(IsoGridSquare var1, IsoDirections var2, int var3) {
    uint8_t var4 = 0;
    uint8_t var5 = 0;
      if (var2 == IsoDirections.W || var2 == IsoDirections.NW || var2 == IsoDirections.SW) {
         var4 = -1;
      } else if (var2 == IsoDirections.E || var2 == IsoDirections.NE || var2 == IsoDirections.SE) {
         var4 = 1;
      }

      if (var2 == IsoDirections.N || var2 == IsoDirections.NW || var2 == IsoDirections.NE) {
         var5 = -1;
      } else if (var2 == IsoDirections.S || var2 == IsoDirections.SW || var2 == IsoDirections.SE) {
         var5 = 1;
      }

    int var6 = var1.getX() + var4;
    int var7 = var1.getY() + var5;
    int var8 = var1.getZ() + var3;
    IsoGridSquare var9 = var3 == 0 ? var1.nav[var2.index()] : IsoWorld.instance.CurrentCell.getGridSquare(var6, var7, var8);
      if (var9 != nullptr) {
         var1.ReCalculateCollide(var9);
         var9.ReCalculateCollide(var1);
         var1.ReCalculatePathFind(var9);
         var9.ReCalculatePathFind(var1);
         var1.ReCalculateVisionBlocked(var9);
         var9.ReCalculateVisionBlocked(var1);
      }

      if (var3 == 0) {
         switch (1.$SwitchMap$zombie$iso$IsoDirections[var2.ordinal()]) {
            case 1:
               if (var9 == nullptr) {
                  var1.e = nullptr;
               } else {
                  var1.e = var1.testPathFindAdjacent(nullptr, 1, 0, 0) ? nullptr : var9;
                  var9.w = var9.testPathFindAdjacent(nullptr, -1, 0, 0) ? nullptr : var1;
               }
               break;
            case 2:
               if (var9 == nullptr) {
                  var1.w = nullptr;
               } else {
                  var1.w = var1.testPathFindAdjacent(nullptr, -1, 0, 0) ? nullptr : var9;
                  var9.e = var9.testPathFindAdjacent(nullptr, 1, 0, 0) ? nullptr : var1;
               }
               break;
            case 3:
               if (var9 == nullptr) {
                  var1.n = nullptr;
               } else {
                  var1.n = var1.testPathFindAdjacent(nullptr, 0, -1, 0) ? nullptr : var9;
                  var9.s = var9.testPathFindAdjacent(nullptr, 0, 1, 0) ? nullptr : var1;
               }
               break;
            case 4:
               if (var9 == nullptr) {
                  var1.s = nullptr;
               } else {
                  var1.s = var1.testPathFindAdjacent(nullptr, 0, 1, 0) ? nullptr : var9;
                  var9.n = var9.testPathFindAdjacent(nullptr, 0, -1, 0) ? nullptr : var1;
               }
               break;
            case 5:
               if (var9 == nullptr) {
                  var1.nw = nullptr;
               } else {
                  var1.nw = var1.testPathFindAdjacent(nullptr, -1, -1, 0) ? nullptr : var9;
                  var9.se = var9.testPathFindAdjacent(nullptr, 1, 1, 0) ? nullptr : var1;
               }
               break;
            case 6:
               if (var9 == nullptr) {
                  var1.ne = nullptr;
               } else {
                  var1.ne = var1.testPathFindAdjacent(nullptr, 1, -1, 0) ? nullptr : var9;
                  var9.sw = var9.testPathFindAdjacent(nullptr, -1, 1, 0) ? nullptr : var1;
               }
               break;
            case 7:
               if (var9 == nullptr) {
                  var1.se = nullptr;
               } else {
                  var1.se = var1.testPathFindAdjacent(nullptr, 1, 1, 0) ? nullptr : var9;
                  var9.nw = var9.testPathFindAdjacent(nullptr, -1, -1, 0) ? nullptr : var1;
               }
               break;
            case 8:
               if (var9 == nullptr) {
                  var1.sw = nullptr;
               } else {
                  var1.sw = var1.testPathFindAdjacent(nullptr, -1, 1, 0) ? nullptr : var9;
                  var9.ne = var9.testPathFindAdjacent(nullptr, 1, -1, 0) ? nullptr : var1;
               }
         }
      }
   }

    void EnsureSurroundNotNullX(int var1, int var2, int var3) {
    IsoCell var4 = IsoWorld.instance.CurrentCell;

      for (int var5 = var1 - 1; var5 <= var1 + 1; var5++) {
         if (var5 >= 0 && var5 < 10) {
    IsoGridSquare var6 = this.getGridSquare(var5, var2, var3);
            if (var6 == nullptr) {
               var6 = IsoGridSquare.getNew(var4, nullptr, this.wx * 10 + var5, this.wy * 10 + var2, var3);
               var4.ConnectNewSquare(var6, false);
            }
         }
      }
   }

    void EnsureSurroundNotNullY(int var1, int var2, int var3) {
    IsoCell var4 = IsoWorld.instance.CurrentCell;

      for (int var5 = var2 - 1; var5 <= var2 + 1; var5++) {
         if (var5 >= 0 && var5 < 10) {
    IsoGridSquare var6 = this.getGridSquare(var1, var5, var3);
            if (var6 == nullptr) {
               var6 = IsoGridSquare.getNew(var4, nullptr, this.wx * 10 + var1, this.wy * 10 + var5, var3);
               var4.ConnectNewSquare(var6, false);
            }
         }
      }
   }

    void EnsureSurroundNotNull(int var1, int var2, int var3) {
    IsoCell var4 = IsoWorld.instance.CurrentCell;
    IsoGridSquare var5 = this.getGridSquare(var1, var2, var3);
      if (var5 == nullptr) {
         var5 = IsoGridSquare.getNew(var4, nullptr, this.wx * 10 + var1, this.wy * 10 + var2, var3);
         var4.ConnectNewSquare(var5, false);
      }
   }

    void loadInMainThread() {
    IsoCell var1 = IsoWorld.instance.CurrentCell;
    IsoChunk var2 = var1.getChunk(this.wx - 1, this.wy);
    IsoChunk var3 = var1.getChunk(this.wx, this.wy - 1);
    IsoChunk var4 = var1.getChunk(this.wx + 1, this.wy);
    IsoChunk var5 = var1.getChunk(this.wx, this.wy + 1);
    IsoChunk var6 = var1.getChunk(this.wx - 1, this.wy - 1);
    IsoChunk var7 = var1.getChunk(this.wx + 1, this.wy - 1);
    IsoChunk var8 = var1.getChunk(this.wx + 1, this.wy + 1);
    IsoChunk var9 = var1.getChunk(this.wx - 1, this.wy + 1);

      for (int var11 = 1; var11 < 8; var11++) {
         for (int var12 = 0; var12 < 10; var12++) {
            if (var3 != nullptr) {
    IsoGridSquare var10 = var3.getGridSquare(var12, 9, var11);
               if (var10 != nullptr && !var10.getObjects().empty()) {
                  this.EnsureSurroundNotNullX(var12, 0, var11);
               }
            }

            if (var5 != nullptr) {
    IsoGridSquare var18 = var5.getGridSquare(var12, 0, var11);
               if (var18 != nullptr && !var18.getObjects().empty()) {
                  this.EnsureSurroundNotNullX(var12, 9, var11);
               }
            }
         }

         for (int var38 = 0; var38 < 10; var38++) {
            if (var2 != nullptr) {
    IsoGridSquare var19 = var2.getGridSquare(9, var38, var11);
               if (var19 != nullptr && !var19.getObjects().empty()) {
                  this.EnsureSurroundNotNullY(0, var38, var11);
               }
            }

            if (var4 != nullptr) {
    IsoGridSquare var20 = var4.getGridSquare(0, var38, var11);
               if (var20 != nullptr && !var20.getObjects().empty()) {
                  this.EnsureSurroundNotNullY(9, var38, var11);
               }
            }
         }

         if (var6 != nullptr) {
    IsoGridSquare var21 = var6.getGridSquare(9, 9, var11);
            if (var21 != nullptr && !var21.getObjects().empty()) {
               this.EnsureSurroundNotNull(0, 0, var11);
            }
         }

         if (var7 != nullptr) {
    IsoGridSquare var22 = var7.getGridSquare(0, 9, var11);
            if (var22 != nullptr && !var22.getObjects().empty()) {
               this.EnsureSurroundNotNull(9, 0, var11);
            }
         }

         if (var8 != nullptr) {
    IsoGridSquare var23 = var8.getGridSquare(0, 0, var11);
            if (var23 != nullptr && !var23.getObjects().empty()) {
               this.EnsureSurroundNotNull(9, 9, var11);
            }
         }

         if (var9 != nullptr) {
    IsoGridSquare var24 = var9.getGridSquare(9, 0, var11);
            if (var24 != nullptr && !var24.getObjects().empty()) {
               this.EnsureSurroundNotNull(0, 9, var11);
            }
         }
      }

      for (int var34 = 1; var34 < 8; var34++) {
         for (int var39 = 0; var39 < 10; var39++) {
            if (var3 != nullptr) {
    IsoGridSquare var25 = this.getGridSquare(var39, 0, var34);
               if (var25 != nullptr && !var25.getObjects().empty()) {
                  var3.EnsureSurroundNotNullX(var39, 9, var34);
               }
            }

            if (var5 != nullptr) {
    IsoGridSquare var26 = this.getGridSquare(var39, 9, var34);
               if (var26 != nullptr && !var26.getObjects().empty()) {
                  var5.EnsureSurroundNotNullX(var39, 0, var34);
               }
            }
         }

         for (int var40 = 0; var40 < 10; var40++) {
            if (var2 != nullptr) {
    IsoGridSquare var27 = this.getGridSquare(0, var40, var34);
               if (var27 != nullptr && !var27.getObjects().empty()) {
                  var2.EnsureSurroundNotNullY(9, var40, var34);
               }
            }

            if (var4 != nullptr) {
    IsoGridSquare var28 = this.getGridSquare(9, var40, var34);
               if (var28 != nullptr && !var28.getObjects().empty()) {
                  var4.EnsureSurroundNotNullY(0, var40, var34);
               }
            }
         }

         if (var6 != nullptr) {
    IsoGridSquare var29 = this.getGridSquare(0, 0, var34);
            if (var29 != nullptr && !var29.getObjects().empty()) {
               var6.EnsureSurroundNotNull(9, 9, var34);
            }
         }

         if (var7 != nullptr) {
    IsoGridSquare var30 = this.getGridSquare(9, 0, var34);
            if (var30 != nullptr && !var30.getObjects().empty()) {
               var7.EnsureSurroundNotNull(0, 9, var34);
            }
         }

         if (var8 != nullptr) {
    IsoGridSquare var31 = this.getGridSquare(9, 9, var34);
            if (var31 != nullptr && !var31.getObjects().empty()) {
               var8.EnsureSurroundNotNull(0, 0, var34);
            }
         }

         if (var9 != nullptr) {
    IsoGridSquare var32 = this.getGridSquare(0, 9, var34);
            if (var32 != nullptr && !var32.getObjects().empty()) {
               var9.EnsureSurroundNotNull(9, 0, var34);
            }
         }
      }

      for (int var35 = 0; var35 <= this.maxLevel; var35++) {
         for (int var41 = 0; var41 < 10; var41++) {
            for (int var13 = 0; var13 < 10; var13++) {
    IsoGridSquare var33 = this.getGridSquare(var13, var41, var35);
               if (var33 != nullptr) {
                  if (var13 == 0 || var13 == 9 || var41 == 0 || var41 == 9) {
                     IsoWorld.instance.CurrentCell.DoGridNav(var33, IsoGridSquare.cellGetSquare);

                     for (int var14 = -1; var14 <= 1; var14++) {
                        if (var13 == 0) {
                           this.RecalcAllWithNeighbour(var33, IsoDirections.W, var14);
                           this.RecalcAllWithNeighbour(var33, IsoDirections.NW, var14);
                           this.RecalcAllWithNeighbour(var33, IsoDirections.SW, var14);
                        } else if (var13 == 9) {
                           this.RecalcAllWithNeighbour(var33, IsoDirections.E, var14);
                           this.RecalcAllWithNeighbour(var33, IsoDirections.NE, var14);
                           this.RecalcAllWithNeighbour(var33, IsoDirections.SE, var14);
                        }

                        if (var41 == 0) {
                           this.RecalcAllWithNeighbour(var33, IsoDirections.N, var14);
                           if (var13 != 0) {
                              this.RecalcAllWithNeighbour(var33, IsoDirections.NW, var14);
                           }

                           if (var13 != 9) {
                              this.RecalcAllWithNeighbour(var33, IsoDirections.NE, var14);
                           }
                        } else if (var41 == 9) {
                           this.RecalcAllWithNeighbour(var33, IsoDirections.S, var14);
                           if (var13 != 0) {
                              this.RecalcAllWithNeighbour(var33, IsoDirections.SW, var14);
                           }

                           if (var13 != 9) {
                              this.RecalcAllWithNeighbour(var33, IsoDirections.SE, var14);
                           }
                        }
                     }

    IsoGridSquare var42 = var33.nav[IsoDirections.N.index()];
    IsoGridSquare var15 = var33.nav[IsoDirections.S.index()];
    IsoGridSquare var16 = var33.nav[IsoDirections.W.index()];
    IsoGridSquare var17 = var33.nav[IsoDirections.E.index()];
                     if (var42 != nullptr && var16 != nullptr && (var13 == 0 || var41 == 0)) {
                        this.RecalcAllWithNeighbour(var42, IsoDirections.W, 0);
                     }

                     if (var42 != nullptr && var17 != nullptr && (var13 == 9 || var41 == 0)) {
                        this.RecalcAllWithNeighbour(var42, IsoDirections.E, 0);
                     }

                     if (var15 != nullptr && var16 != nullptr && (var13 == 0 || var41 == 9)) {
                        this.RecalcAllWithNeighbour(var15, IsoDirections.W, 0);
                     }

                     if (var15 != nullptr && var17 != nullptr && (var13 == 9 || var41 == 9)) {
                        this.RecalcAllWithNeighbour(var15, IsoDirections.E, 0);
                     }
                  }

    IsoRoom var43 = var33.getRoom();
                  if (var43 != nullptr) {
                     var43.addSquare(var33);
                  }
               }
            }
         }
      }

      this.fixObjectAmbientEmittersOnAdjacentChunks(var4, var5);

      for (int var36 = 0; var36 < 4; var36++) {
         if (var2 != nullptr) {
            var2.lightCheck[var36] = true;
         }

         if (var3 != nullptr) {
            var3.lightCheck[var36] = true;
         }

         if (var4 != nullptr) {
            var4.lightCheck[var36] = true;
         }

         if (var5 != nullptr) {
            var5.lightCheck[var36] = true;
         }

         if (var6 != nullptr) {
            var6.lightCheck[var36] = true;
         }

         if (var7 != nullptr) {
            var7.lightCheck[var36] = true;
         }

         if (var8 != nullptr) {
            var8.lightCheck[var36] = true;
         }

         if (var9 != nullptr) {
            var9.lightCheck[var36] = true;
         }
      }

      for (int var37 = 0; var37 < IsoPlayer.numPlayers; var37++) {
         LosUtil.cachecleared[var37] = true;
      }

      IsoLightSwitch.chunkLoaded(this);
   }

    void fixObjectAmbientEmittersOnAdjacentChunks(IsoChunk var1, IsoChunk var2) {
      if (!GameServer.bServer) {
         if (var1 != nullptr || var2 != nullptr) {
            for (int var3 = 0; var3 < 8; var3++) {
               if (var1 != nullptr) {
                  for (int var4 = 0; var4 < 10; var4++) {
    IsoGridSquare var5 = var1.getGridSquare(0, var4, var3);
                     this.fixObjectAmbientEmittersOnSquare(var5, false);
                  }
               }

               if (var2 != nullptr) {
                  for (int var6 = 0; var6 < 10; var6++) {
    IsoGridSquare var7 = var2.getGridSquare(var6, 0, var3);
                     this.fixObjectAmbientEmittersOnSquare(var7, true);
                  }
               }
            }
         }
      }
   }

    void fixObjectAmbientEmittersOnSquare(IsoGridSquare var1, bool var2) {
      if (var1 != nullptr && !var1.getSpecialObjects().empty()) {
    IsoObject var3 = var1.getDoor(var2);
         if (dynamic_cast<IsoDoor*>(var3) != nullptr && ((IsoDoor)var3).isExterior() && !var3.hasObjectAmbientEmitter()) {
            var3.addObjectAmbientEmitter(std::make_unique<DoorLogic>().init(var3));
         }

    IsoWindow var4 = var1.getWindow(var2);
         if (var4 != nullptr && var4.isExterior() && !var4.hasObjectAmbientEmitter()) {
            var4.addObjectAmbientEmitter(std::make_unique<WindowLogic>().init(var4));
         }
      }
   }

    void recalcNeighboursNow() {
    IsoCell var1 = IsoWorld.instance.CurrentCell;

      for (int var2 = 0; var2 < 10; var2++) {
         for (int var3 = 0; var3 < 10; var3++) {
            for (int var4 = 0; var4 < 8; var4++) {
    IsoGridSquare var5 = this.getGridSquare(var2, var3, var4);
               if (var5 != nullptr) {
                  if (var4 > 0 && !var5.getObjects().empty()) {
                     var5.EnsureSurroundNotNull();

                     for (int var6 = var4 - 1; var6 > 0; var6--) {
    IsoGridSquare var7 = this.getGridSquare(var2, var3, var6);
                        if (var7 == nullptr) {
                           var7 = IsoGridSquare.getNew(var1, nullptr, this.wx * 10 + var2, this.wy * 10 + var3, var6);
                           var1.ConnectNewSquare(var7, false);
                        }
                     }
                  }

                  var5.RecalcProperties();
               }
            }
         }
      }

      for (int var8 = 1; var8 < 8; var8++) {
         for (int var11 = -1; var11 < 11; var11++) {
    IsoGridSquare var15 = var1.getGridSquare(this.wx * 10 + var11, this.wy * 10 - 1, var8);
            if (var15 != nullptr && !var15.getObjects().empty()) {
               var15.EnsureSurroundNotNull();
            }

            var15 = var1.getGridSquare(this.wx * 10 + var11, this.wy * 10 + 10, var8);
            if (var15 != nullptr && !var15.getObjects().empty()) {
               var15.EnsureSurroundNotNull();
            }
         }

         for (int var12 = 0; var12 < 10; var12++) {
    IsoGridSquare var17 = var1.getGridSquare(this.wx * 10 - 1, this.wy * 10 + var12, var8);
            if (var17 != nullptr && !var17.getObjects().empty()) {
               var17.EnsureSurroundNotNull();
            }

            var17 = var1.getGridSquare(this.wx * 10 + 10, this.wy * 10 + var12, var8);
            if (var17 != nullptr && !var17.getObjects().empty()) {
               var17.EnsureSurroundNotNull();
            }
         }
      }

      for (int var9 = 0; var9 < 10; var9++) {
         for (int var13 = 0; var13 < 10; var13++) {
            for (int var19 = 0; var19 < 8; var19++) {
    IsoGridSquare var21 = this.getGridSquare(var9, var13, var19);
               if (var21 != nullptr) {
                  var21.RecalcAllWithNeighbours(true);
    IsoRoom var23 = var21.getRoom();
                  if (var23 != nullptr) {
                     var23.addSquare(var21);
                  }
               }
            }
         }
      }

      for (int var10 = 0; var10 < 10; var10++) {
         for (int var14 = 0; var14 < 10; var14++) {
            for (int var20 = 0; var20 < 8; var20++) {
    IsoGridSquare var22 = this.getGridSquare(var10, var14, var20);
               if (var22 != nullptr) {
                  var22.propertiesDirty = true;
               }
            }
         }
      }

      IsoLightSwitch.chunkLoaded(this);
   }

    void updateBuildings() {
   }

    static void updatePlayerInBullet() {
    std::vector var0 = GameServer.getPlayers();
      Bullet.updatePlayerList(var0);
   }

    void update() {
      if (!GameServer.bServer) {
         this.checkPhysics();
      }

      if (!this.loadedPhysics) {
         this.loadedPhysics = true;

         for (int var1 = 0; var1 < this.vehicles.size(); var1++) {
            this.vehicles.get(var1).chunk = this;
         }
      }

      if (this.vehiclesForAddToWorld != nullptr) {
         /* synchronized - TODO: add std::mutex */ (this.vehiclesForAddToWorldLock) {
            for (int var2 = 0; var2 < this.vehiclesForAddToWorld.size(); var2++) {
               this.vehiclesForAddToWorld.get(var2).addToWorld();
            }

            this.vehiclesForAddToWorld.clear();
            this.vehiclesForAddToWorld = nullptr;
         }
      }

      this.updateVehicleStory();
   }

    void updateVehicleStory() {
      if (this.bLoaded && this.m_vehicleStorySpawnData != nullptr) {
    IsoMetaChunk var1 = IsoWorld.instance.getMetaChunk(this.wx, this.wy);
         if (var1 != nullptr) {
    VehicleStorySpawnData var2 = this.m_vehicleStorySpawnData;

            for (int var3 = 0; var3 < var1.numZones(); var3++) {
    Zone var4 = var1.getZone(var3);
               if (var2.isValid(var4, this)) {
                  var2.m_story.randomizeVehicleStory(var4, this);
                  var4.hourLastSeen++;
                  break;
               }
            }
         }
      }
   }

    void setSquare(int var1, int var2, int var3, IsoGridSquare var4) {
    assert var4 = = nullptr || var4.x - this.wx * 10 == var1 && var4.y - this.wy * 10 == var2 && var4.z == var3;

      this.squares[var3][var2 * 10 + var1] = var4;
      if (var4 != nullptr) {
         var4.chunk = this;
         if (var4.z > this.maxLevel) {
            this.maxLevel = var4.z;
         }
      }
   }

    IsoGridSquare getGridSquare(int var1, int var2, int var3) {
      return var1 >= 0 && var1 < 10 && var2 >= 0 && var2 < 10 && var3 < 8 && var3 >= 0 ? this.squares[var3][var2 * 10 + var1] : nullptr;
   }

    IsoRoom getRoom(int var1) {
      return this.lotheader.getRoom(var1);
   }

    void removeFromWorld() {
      loadGridSquare.remove(this);
      if (GameClient.bClient && GameClient.instance.bConnected) {
         try {
            GameClient.instance.sendAddedRemovedItems(true);
         } catch (Exception var9) {
            ExceptionLogger.logException(var9);
         }
      }

      try {
         MapCollisionData.instance.removeChunkFromWorld(this);
         ZombiePopulationManager.instance.removeChunkFromWorld(this);
         PolygonalMap2.instance.removeChunkFromWorld(this);
         this.collision.clear();
      } catch (Exception var8) {
         var8.printStackTrace();
      }

    uint8_t var1 = 100;

      for (int var2 = 0; var2 < 8; var2++) {
         for (int var3 = 0; var3 < var1; var3++) {
    IsoGridSquare var4 = this.squares[var2][var3];
            if (var4 != nullptr) {
               RainManager.RemoveAllOn(var4);
               var4.clearWater();
               var4.clearPuddles();
               if (var4.getRoom() != nullptr) {
                  var4.getRoom().removeSquare(var4);
               }

               if (var4.zone != nullptr) {
                  var4.zone.removeSquare(var4);
               }

    std::vector var5 = var4.getMovingObjects();

               for (int var6 = 0; var6 < var5.size(); var6++) {
    IsoMovingObject var7 = (IsoMovingObject)var5.get(var6);
                  if (dynamic_cast<IsoSurvivor*>(var7) != nullptr) {
                     IsoWorld.instance.CurrentCell.getSurvivorList().remove(var7);
                     var7.Despawn();
                  }

                  var7.removeFromWorld();
                  var7.current = var7.last = nullptr;
                  if (!var5.contains(var7)) {
                     var6--;
                  }
               }

               var5.clear();

               for (int var12 = 0; var12 < var4.getObjects().size(); var12++) {
    IsoObject var14 = (IsoObject)var4.getObjects().get(var12);
                  var14.removeFromWorld();
               }

               for (int var13 = 0; var13 < var4.getStaticMovingObjects().size(); var13++) {
    IsoMovingObject var15 = (IsoMovingObject)var4.getStaticMovingObjects().get(var13);
                  var15.removeFromWorld();
               }

               this.disconnectFromAdjacentChunks(var4);
               var4.softClear();
               var4.chunk = nullptr;
            }
         }
      }

      for (int var10 = 0; var10 < this.vehicles.size(); var10++) {
    BaseVehicle var11 = this.vehicles.get(var10);
         if (IsoWorld.instance.CurrentCell.getVehicles().contains(var11) || IsoWorld.instance.CurrentCell.addVehicles.contains(var11)) {
            DebugLog.log("IsoChunk.removeFromWorld: vehicle wasn't removed from world id=" + var11.VehicleID);
            var11.removeFromWorld();
         }
      }
   }

    void disconnectFromAdjacentChunks(IsoGridSquare var1) {
    int var2 = var1.x % 10;
    int var3 = var1.y % 10;
      if (var2 == 0 || var2 == 9 || var3 == 0 || var3 == 9) {
    int var4 = IsoDirections.N.index();
    int var5 = IsoDirections.S.index();
         if (var1.nav[var4] != nullptr && var1.nav[var4].chunk != var1.chunk) {
            var1.nav[var4].nav[var5] = nullptr;
            var1.nav[var4].s = nullptr;
         }

         var4 = IsoDirections.NW.index();
         var5 = IsoDirections.SE.index();
         if (var1.nav[var4] != nullptr && var1.nav[var4].chunk != var1.chunk) {
            var1.nav[var4].nav[var5] = nullptr;
            var1.nav[var4].se = nullptr;
         }

         var4 = IsoDirections.W.index();
         var5 = IsoDirections.E.index();
         if (var1.nav[var4] != nullptr && var1.nav[var4].chunk != var1.chunk) {
            var1.nav[var4].nav[var5] = nullptr;
            var1.nav[var4].e = nullptr;
         }

         var4 = IsoDirections.SW.index();
         var5 = IsoDirections.NE.index();
         if (var1.nav[var4] != nullptr && var1.nav[var4].chunk != var1.chunk) {
            var1.nav[var4].nav[var5] = nullptr;
            var1.nav[var4].ne = nullptr;
         }

         var4 = IsoDirections.S.index();
         var5 = IsoDirections.N.index();
         if (var1.nav[var4] != nullptr && var1.nav[var4].chunk != var1.chunk) {
            var1.nav[var4].nav[var5] = nullptr;
            var1.nav[var4].n = nullptr;
         }

         var4 = IsoDirections.SE.index();
         var5 = IsoDirections.NW.index();
         if (var1.nav[var4] != nullptr && var1.nav[var4].chunk != var1.chunk) {
            var1.nav[var4].nav[var5] = nullptr;
            var1.nav[var4].nw = nullptr;
         }

         var4 = IsoDirections.E.index();
         var5 = IsoDirections.W.index();
         if (var1.nav[var4] != nullptr && var1.nav[var4].chunk != var1.chunk) {
            var1.nav[var4].nav[var5] = nullptr;
            var1.nav[var4].w = nullptr;
         }

         var4 = IsoDirections.NE.index();
         var5 = IsoDirections.SW.index();
         if (var1.nav[var4] != nullptr && var1.nav[var4].chunk != var1.chunk) {
            var1.nav[var4].nav[var5] = nullptr;
            var1.nav[var4].sw = nullptr;
         }
      }
   }

    void doReuseGridsquares() {
    uint8_t var1 = 100;

      for (int var2 = 0; var2 < 8; var2++) {
         for (int var3 = 0; var3 < var1; var3++) {
    IsoGridSquare var4 = this.squares[var2][var3];
            if (var4 != nullptr) {
               LuaEventManager.triggerEvent("ReuseGridsquare", var4);

               for (int var5 = 0; var5 < var4.getObjects().size(); var5++) {
    IsoObject var6 = (IsoObject)var4.getObjects().get(var5);
                  if (dynamic_cast<IsoTree*>(var6) != nullptr) {
                     var6.reset();
                     CellLoader.isoTreeCache.push_back((IsoTree)var6);
                  } else if (dynamic_cast<IsoObject*>(var6) != nullptr && var6.getObjectName() == "IsoObject")) {
                     var6.reset();
                     CellLoader.isoObjectCache.push_back(var6);
                  } else {
                     var6.reuseGridSquare();
                  }
               }

               var4.discard();
               this.squares[var2][var3] = nullptr;
            }
         }
      }

      this.resetForStore();

      assert !IsoChunkMap.chunkStore.contains(this);

      IsoChunkMap.chunkStore.push_back(this);
   }

    static int bufferSize(int var0) {
      return (var0 + 65536 - 1) / 65536 * 65536;
   }

    static ByteBuffer ensureCapacity(ByteBuffer var0, int var1) {
      if (var0 == nullptr || var0.capacity() < var1) {
         var0 = ByteBuffer.allocate(bufferSize(var1));
      }

    return var0;
   }

    static ByteBuffer ensureCapacity(ByteBuffer var0) {
      if (var0 == nullptr) {
         return ByteBuffer.allocate(65536);
      } else if (var0.capacity() - var0.position() < 65536) {
    ByteBuffer var1 = ensureCapacity(nullptr, var0.position() + 65536);
         return var1.put(var0.array(), 0, var0.position());
      } else {
    return var0;
      }
   }

    void LoadFromDisk() {
      this.LoadFromDiskOrBuffer(nullptr);
   }

    void LoadFromDiskOrBuffer(ByteBuffer var1) {
      sanityCheck.beginLoad(this);

      try {
    ByteBuffer var2;
         if (var1 == nullptr) {
            SliceBufferLoad = SafeRead(prefix, this.wx, this.wy, SliceBufferLoad);
            var2 = SliceBufferLoad;
         } else {
            var2 = var1;
         }

    int var3 = this.wx * 10;
    int var4 = this.wy * 10;
         var3 /= 300;
         var4 /= 300;
    std::string var5 = ChunkMapFilenames.instance.getHeader(var3, var4);
         if (IsoLot.InfoHeaders.containsKey(var5)) {
            this.lotheader = (LotHeader)IsoLot.InfoHeaders.get(var5);
         }

         IsoCell.wx = this.wx;
         IsoCell.wy = this.wy;
    bool var6 = var2.get() == 1;
    int var7 = var2.getInt();
         if (var6) {
            DebugLog.log("WorldVersion = " + var7 + ", debug = " + var6);
         }

         if (var7 > 195) {
            throw RuntimeException("unknown world version " + var7 + " while reading chunk " + this.wx + "," + this.wy);
         }

         this.bFixed2x = var7 >= 85;
         if (var7 >= 61) {
    int var8 = var2.getInt();
            sanityCheck.checkLength(var8, var2.limit());
    long var9 = var2.getLong();
            crcLoad.reset();
            crcLoad.update(var2.array(), 17, var2.limit() - 1 - 4 - 4 - 8);
            sanityCheck.checkCRC(var9, crcLoad.getValue());
         }

    int var28 = 0;
         if (GameClient.bClient || GameServer.bServer) {
            var28 = ServerOptions.getInstance().BloodSplatLifespanDays.getValue();
         }

    float var29 = (float)GameTime.getInstance().getWorldAgeHours();
    int var10 = var2.getInt();

         for (int var11 = 0; var11 < var10; var11++) {
    IsoFloorBloodSplat var12 = std::make_shared<IsoFloorBloodSplat>();
            var12.load(var2, var7);
            if (var12.worldAge > var29) {
               var12.worldAge = var29;
            }

            if (var28 <= 0 || !(var29 - var12.worldAge >= var28 * 24)) {
               if (var7 < 73 && var12.Type < 8) {
                  var12.index = ++this.nextSplatIndex;
               }

               if (var12.Type < 8) {
                  this.nextSplatIndex = var12.index % 10;
               }

               this.FloorBloodSplats.push_back(var12);
            }
         }

    IsoMetaGrid var30 = IsoWorld.instance.getMetaGrid();
    uint8_t var31 = 0;

         for (int var13 = 0; var13 < 10; var13++) {
            for (int var14 = 0; var14 < 10; var14++) {
               var31 = var2.get();

               for (int var15 = 0; var15 < 8; var15++) {
    IsoGridSquare var16 = nullptr;
    bool var17 = false;
                  if ((var31 & 1 << var15) != 0) {
                     var17 = true;
                  }

                  if (var17) {
                     if (var16 == nullptr) {
                        if (IsoGridSquare.loadGridSquareCache != nullptr) {
                           var16 = IsoGridSquare.getNew(
                              IsoGridSquare.loadGridSquareCache, IsoWorld.instance.CurrentCell, nullptr, var13 + this.wx * 10, var14 + this.wy * 10, var15
                           );
                        } else {
                           var16 = IsoGridSquare.getNew(IsoWorld.instance.CurrentCell, nullptr, var13 + this.wx * 10, var14 + this.wy * 10, var15);
                        }
                     }

                     var16.chunk = this;
                     if (this.lotheader != nullptr) {
    RoomDef var18 = var30.getRoomAt(var16.x, var16.y, var16.z);
    int var19 = var18 != nullptr ? var18.ID : -1;
                        var16.setRoomID(var19);
                        var18 = var30.getEmptyOutsideAt(var16.x, var16.y, var16.z);
                        if (var18 != nullptr) {
    IsoRoom var20 = this.getRoom(var18.ID);
                           var16.roofHideBuilding = var20 == nullptr ? nullptr : var20.building;
                        }
                     }

                     var16.ResetIsoWorldRegion();
                     this.setSquare(var13, var14, var15, var16);
                  }

                  if (var17 && var16 != nullptr) {
                     var16.load(var2, var7, var6);
                     var16.FixStackableObjects();
                     if (this.jobType == JobType.SoftReset) {
                        if (!var16.getStaticMovingObjects().empty()) {
                           var16.getStaticMovingObjects().clear();
                        }

                        for (int var47 = 0; var47 < var16.getObjects().size(); var47++) {
    IsoObject var50 = (IsoObject)var16.getObjects().get(var47);
                           var50.softReset();
                           if (var50.getObjectIndex() == -1) {
                              var47--;
                           }
                        }

                        var16.setOverlayDone(false);
                     }
                  }
               }
            }
         }

         if (var7 >= 45) {
            this.getErosionData().load(var2, var7);
            this.getErosionData().set(this);
         }

         if (var7 >= 127) {
    short var33 = var2.getShort();
            if (var33 > 0 && this.generatorsTouchingThisChunk == nullptr) {
               this.generatorsTouchingThisChunk = std::make_unique<std::vector<>>();
            }

            if (this.generatorsTouchingThisChunk != nullptr) {
               this.generatorsTouchingThisChunk.clear();
            }

            for (int var36 = 0; var36 < var33; var36++) {
    int var39 = var2.getInt();
    int var42 = var2.getInt();
    uint8_t var44 = var2.get();
    Location var48 = std::make_shared<Location>(var39, var42, var44);
               this.generatorsTouchingThisChunk.push_back(var48);
            }
         }

         this.vehicles.clear();
         if (!GameClient.bClient) {
            if (var7 >= 91) {
    short var34 = var2.getShort();

               for (int var37 = 0; var37 < var34; var37++) {
    uint8_t var40 = var2.get();
    uint8_t var43 = var2.get();
    uint8_t var45 = var2.get();
    IsoObject var49 = IsoObject.factoryFromFileInput(IsoWorld.instance.CurrentCell, var2);
                  if (var49 != nullptr && dynamic_cast<BaseVehicle*>(var49) != nullptr) {
    IsoGridSquare var51 = this.getGridSquare(var40, var43, var45);
                     var49.square = var51;
                     ((IsoMovingObject)var49).current = var51;

                     try {
                        var49.load(var2, var7, var6);
                        this.vehicles.push_back((BaseVehicle)var49);
                        addFromCheckedVehicles((BaseVehicle)var49);
                        if (this.jobType == JobType.SoftReset) {
                           var49.softReset();
                        }
                     } catch (Exception var24) {
                        throw RuntimeException(var24);
                     }
                  }
               }
            }

            if (var7 >= 125) {
               this.lootRespawnHour = var2.getInt();
            }

            if (var7 >= 160) {
    uint8_t var35 = var2.get();

               for (int var38 = 0; var38 < var35; var38++) {
    int var41 = var2.getInt();
                  this.addSpawnedRoom(var41);
               }
            }
         }
      } finally {
         sanityCheck.endLoad(this);
         this.bFixed2x = true;
      }

      if (this.getGridSquare(0, 0, 0) == nullptr && this.getGridSquare(9, 9, 0) == nullptr) {
         throw RuntimeException("black chunk " + this.wx + "," + this.wy);
      }
   }

    void doLoadGridsquare() {
      if (this.jobType == JobType.SoftReset) {
         this.m_spawnedRooms.clear();
      }

      if (!GameServer.bServer) {
         this.loadInMainThread();
      }

      if (this.addZombies && !VehiclesDB2.instance.isChunkSeen(this.wx, this.wy)) {
         try {
            this.AddVehicles();
         } catch (Throwable var11) {
            ExceptionLogger.logException(var11);
         }
      }

      this.AddZombieZoneStory();
      VehiclesDB2.instance.setChunkSeen(this.wx, this.wy);
      if (this.addZombies) {
         if (IsoWorld.instance.getTimeSinceLastSurvivorInHorde() > 0) {
            IsoWorld.instance.setTimeSinceLastSurvivorInHorde(IsoWorld.instance.getTimeSinceLastSurvivorInHorde() - 1);
         }

         this.addSurvivorInHorde(false);
      }

      this.update();
      if (!GameServer.bServer) {
         FliesSound.instance.chunkLoaded(this);
         NearestWalls.chunkLoaded(this);
      }

      if (this.addZombies) {
    int var1 = 5 + SandboxOptions.instance.TimeSinceApo.getValue();
         var1 = Math.min(20, var1);
         if (Rand.Next(var1) == 0) {
            this.AddCorpses(this.wx, this.wy);
         }

         if (Rand.Next(var1 * 2) == 0) {
            this.AddBlood(this.wx, this.wy);
         }
      }

      LoadGridsquarePerformanceWorkaround.init(this.wx, this.wy);
      tempBuildings.clear();
      if (!GameClient.bClient) {
         for (int var14 = 0; var14 < this.vehicles.size(); var14++) {
    BaseVehicle var2 = this.vehicles.get(var14);
            if (!var2.addedToWorld && VehiclesDB2.instance.isVehicleLoaded(var2)) {
               var2.removeFromSquare();
               this.vehicles.remove(var14);
               var14--;
            } else {
               if (!var2.addedToWorld) {
                  var2.addToWorld();
               }

               if (var2.sqlID == -1) {
    assert false;

                  if (var2.square == nullptr) {
    float var3 = 5.0E-4F;
    int var4 = this.wx * 10;
    int var5 = this.wy * 10;
    int var6 = var4 + 10;
    int var7 = var5 + 10;
    float var8 = PZMath.clamp(var2.x, var4 + var3, var6 - var3);
    float var9 = PZMath.clamp(var2.y, var5 + var3, var7 - var3);
                     var2.square = this.getGridSquare((int)var8 - this.wx * 10, (int)var9 - this.wy * 10, 0);
                  }

                  VehiclesDB2.instance.addVehicle(var2);
               }
            }
         }
      }

      this.m_treeCount = 0;
      this.m_scavengeZone = nullptr;
      this.m_numberOfWaterTiles = 0;

      for (int var15 = 0; var15 <= this.maxLevel; var15++) {
         for (int var19 = 0; var19 < 10; var19++) {
            for (int var22 = 0; var22 < 10; var22++) {
    IsoGridSquare var25 = this.getGridSquare(var19, var22, var15);
               if (var25 != nullptr && !var25.getObjects().empty()) {
                  for (int var27 = 0; var27 < var25.getObjects().size(); var27++) {
    IsoObject var30 = (IsoObject)var25.getObjects().get(var27);
                     var30.addToWorld();
                     if (var15 == 0 && var30.getSprite() != nullptr && var30.getSprite().getProperties().Is(IsoFlagType.water)) {
                        this.m_numberOfWaterTiles++;
                     }
                  }

                  if (var25.HasTree()) {
                     this.m_treeCount++;
                  }

                  if (this.jobType != JobType.SoftReset) {
                     ErosionMain.LoadGridsquare(var25);
                  }

                  if (this.addZombies) {
                     MapObjects.newGridSquare(var25);
                  }

                  MapObjects.loadGridSquare(var25);
                  LuaEventManager.triggerEvent("LoadGridsquare", var25);
                  LoadGridsquarePerformanceWorkaround.LoadGridsquare(var25);
               }

               if (var25 != nullptr && !var25.getStaticMovingObjects().empty()) {
                  for (int var28 = 0; var28 < var25.getStaticMovingObjects().size(); var28++) {
    IsoMovingObject var31 = (IsoMovingObject)var25.getStaticMovingObjects().get(var28);
                     var31.addToWorld();
                  }
               }

               if (var25 != nullptr && var25.getBuilding() != nullptr && !tempBuildings.contains(var25.getBuilding())) {
                  tempBuildings.push_back(var25.getBuilding());
               }
            }
         }
      }

      if (this.jobType != JobType.SoftReset) {
         ErosionMain.ChunkLoaded(this);
      }

      if (this.jobType != JobType.SoftReset) {
         SGlobalObjects.chunkLoaded(this.wx, this.wy);
      }

      ReanimatedPlayers.instance.addReanimatedPlayersToChunk(this);
      if (this.jobType != JobType.SoftReset) {
         MapCollisionData.instance.addChunkToWorld(this);
         ZombiePopulationManager.instance.addChunkToWorld(this);
         PolygonalMap2.instance.addChunkToWorld(this);
         IsoGenerator.chunkLoaded(this);
         LootRespawn.chunkLoaded(this);
      }

      if (!GameServer.bServer) {
    std::vector var16 = IsoWorld.instance.CurrentCell.roomLights;

         for (int var20 = 0; var20 < this.roomLights.size(); var20++) {
    IsoRoomLight var23 = this.roomLights.get(var20);
            if (!var16.contains(var23)) {
               var16.push_back(var23);
            }
         }
      }

      this.roomLights.clear();
      if (this.jobType != JobType.SoftReset) {
         this.randomizeBuildingsEtc();
      }

      this.checkAdjacentChunks();

      try {
         if (GameServer.bServer && this.jobType != JobType.SoftReset) {
            for (int var17 = 0; var17 < GameServer.udpEngine.connections.size(); var17++) {
    UdpConnection var21 = (UdpConnection)GameServer.udpEngine.connections.get(var17);
               if (!var21.chunkObjectState.empty()) {
                  for (byte var24 = 0; var24 < var21.chunkObjectState.size(); var24 += 2) {
    short var26 = var21.chunkObjectState.get(var24);
    short var29 = var21.chunkObjectState.get(var24 + 1);
                     if (var26 == this.wx && var29 == this.wy) {
                        var21.chunkObjectState.remove(var24, 2);
                        var24 -= 2;
    ByteBufferWriter var32 = var21.startPacket();
                        PacketType.ChunkObjectState.doPacket(var32);
                        var32.putShort((short)this.wx);
                        var32.putShort((short)this.wy);

                        try {
                           if (this.saveObjectState(var32.bb)) {
                              PacketType.ChunkObjectState.send(var21);
                           } else {
                              var21.cancelPacket();
                           }
                        } catch (Throwable var10) {
                           var10.printStackTrace();
                           var21.cancelPacket();
                        }
                     }
                  }
               }
            }
         }

         if (GameClient.bClient) {
    ByteBufferWriter var18 = GameClient.connection.startPacket();
            PacketType.ChunkObjectState.doPacket(var18);
            var18.putShort((short)this.wx);
            var18.putShort((short)this.wy);
            PacketType.ChunkObjectState.send(GameClient.connection);
         }
      } catch (Throwable var12) {
         ExceptionLogger.logException(var12);
      }
   }

    void randomizeBuildingsEtc() {
      tempRoomDefs.clear();
      IsoWorld.instance.MetaGrid.getRoomsIntersecting(this.wx * 10 - 1, this.wy * 10 - 1, 11, 11, tempRoomDefs);

      for (int var1 = 0; var1 < tempRoomDefs.size(); var1++) {
    IsoRoom var2 = tempRoomDefs.get(var1).getIsoRoom();
         if (var2 != nullptr) {
    IsoBuilding var3 = var2.getBuilding();
            if (!tempBuildings.contains(var3)) {
               tempBuildings.push_back(var3);
            }
         }
      }

      for (int var5 = 0; var5 < tempBuildings.size(); var5++) {
    IsoBuilding var7 = tempBuildings.get(var5);
         if (!GameClient.bClient && var7.def != nullptr && var7.def.isFullyStreamedIn()) {
            StashSystem.doBuildingStash(var7.def);
         }

         RandomizedBuildingBase.ChunkLoaded(var7);
      }

      if (!GameClient.bClient && !tempBuildings.empty()) {
         for (int var6 = 0; var6 < tempBuildings.size(); var6++) {
    IsoBuilding var8 = tempBuildings.get(var6);

            for (int var9 = 0; var9 < var8.Rooms.size(); var9++) {
    IsoRoom var4 = (IsoRoom)var8.Rooms.get(var9);
               if (var4.def.bDoneSpawn && !this.isSpawnedRoom(var4.def.ID) && var4.def.intersects(this.wx * 10, this.wy * 10, 10, 10)) {
                  this.addSpawnedRoom(var4.def.ID);
                  VirtualZombieManager.instance.addIndoorZombiesToChunk(this, var4);
               }
            }
         }
      }
   }

    void checkAdjacentChunks() {
    IsoCell var1 = IsoWorld.instance.CurrentCell;

      for (int var2 = -1; var2 <= 1; var2++) {
         for (int var3 = -1; var3 <= 1; var3++) {
            if (var3 != 0 || var2 != 0) {
    IsoChunk var4 = var1.getChunk(this.wx + var3, this.wy + var2);
               if (var4 != nullptr) {
                  var4.m_adjacentChunkLoadedCounter++;
               }
            }
         }
      }
   }

    void AddZombieZoneStory() {
    IsoMetaChunk var1 = IsoWorld.instance.getMetaChunk(this.wx, this.wy);
      if (var1 != nullptr) {
         for (int var2 = 0; var2 < var1.numZones(); var2++) {
    Zone var3 = var1.getZone(var2);
            RandomizedZoneStoryBase.isValidForStory(var3, false);
         }
      }
   }

    void setCache() {
      IsoWorld.instance.CurrentCell.setCacheChunk(this);
   }

    static ChunkLock acquireLock(int var0, int var1) {
      /* synchronized - TODO: add std::mutex */ (Locks) {
         for (int var3 = 0; var3 < Locks.size(); var3++) {
            if (Locks.get(var3).wx == var0 && Locks.get(var3).wy == var1) {
               return Locks.get(var3).ref();
            }
         }

    ChunkLock var6 = FreeLocks.empty() ? std::make_shared<ChunkLock>(var0, var1) : FreeLocks.pop().set(var0, var1);
         Locks.push_back(var6);
         return var6.ref();
      }
   }

    static void releaseLock(ChunkLock var0) {
      /* synchronized - TODO: add std::mutex */ (Locks) {
         if (var0.deref() == 0) {
            Locks.remove(var0);
            FreeLocks.push(var0);
         }
      }
   }

    void setCacheIncludingNull() {
      for (int var1 = 0; var1 < 8; var1++) {
         for (int var2 = 0; var2 < 10; var2++) {
            for (int var3 = 0; var3 < 10; var3++) {
    IsoGridSquare var4 = this.getGridSquare(var2, var3, var1);
               IsoWorld.instance.CurrentCell.setCacheGridSquare(this.wx * 10 + var2, this.wy * 10 + var3, var1, var4);
            }
         }
      }
   }

    void Save(bool var1) {
      if (!Core.getInstance().isNoSave() && !GameClient.bClient) {
         /* synchronized - TODO: add std::mutex */ (WriteLock) {
            sanityCheck.beginSave(this);

            try {
    File var3 = ChunkMapFilenames.instance.getDir(Core.GameSaveWorld);
               if (!var3.exists()) {
                  var3.mkdir();
               }

               SliceBuffer = this.Save(SliceBuffer, crcSave);
               if (!GameClient.bClient && !GameServer.bServer) {
                  SafeWrite(prefix, this.wx, this.wy, SliceBuffer);
               } else {
    long var4 = ChunkChecksum.getChecksumIfExists(this.wx, this.wy);
                  crcSave.reset();
                  crcSave.update(SliceBuffer.array(), 0, SliceBuffer.position());
                  if (var4 != crcSave.getValue()) {
                     ChunkChecksum.setChecksum(this.wx, this.wy, crcSave.getValue());
                     SafeWrite(prefix, this.wx, this.wy, SliceBuffer);
                  }
               }

               if (!var1 && !GameServer.bServer) {
                  if (this.jobType != JobType.Convert) {
                     WorldReuserThread.instance.addReuseChunk(this);
                  } else {
                     this.doReuseGridsquares();
                  }
               }
            } finally {
               sanityCheck.endSave(this);
            }
         }
      } else {
         if (!var1 && !GameServer.bServer && this.jobType != JobType.Convert) {
            WorldReuserThread.instance.addReuseChunk(this);
         }
      }
   }

    static void SafeWrite(const std::string& var0, int var1, int var2, ByteBuffer var3) {
    ChunkLock var4 = acquireLock(var1, var2);
      var4.lockForWriting();

      try {
    File var5 = ChunkMapFilenames.instance.getFilename(var1, var2);
         sanityCheck.beginSaveFile(var5.getAbsolutePath());

         try (FileOutputStream var6 = std::make_shared<FileOutputStream>(var5)) {
            var6.getChannel().truncate(0L);
            var6.write(var3.array(), 0, var3.position());
         } finally {
            sanityCheck.endSaveFile();
         }
      } finally {
         var4.unlockForWriting();
         releaseLock(var4);
      }
   }

    static ByteBuffer SafeRead(const std::string& var0, int var1, int var2, ByteBuffer var3) {
    ChunkLock var4 = acquireLock(var1, var2);
      var4.lockForReading();

      try {
    File var5 = ChunkMapFilenames.instance.getFilename(var1, var2);
         if (var5 == nullptr) {
            var5 = ZomboidFileSystem.instance.getFileInCurrentSave(var0 + var1 + "_" + var2 + ".bin");
         }

         sanityCheck.beginLoadFile(var5.getAbsolutePath());

         try (FileInputStream var6 = std::make_shared<FileInputStream>(var5)) {
            var3 = ensureCapacity(var3, (int)var5.length());
            var3.clear();
    int var7 = var6.read(var3.array());
            var3.limit(PZMath.max(var7, 0));
         } finally {
            sanityCheck.endLoadFile(var5.getAbsolutePath());
         }
      } finally {
         var4.unlockForReading();
         releaseLock(var4);
      }

    return var3;
   }

    void SaveLoadedChunk(zombie.network.ClientChunkRequest.Chunk var1, CRC32 var2) {
      var1.bb = this.Save(var1.bb, var2);
   }

    static bool IsDebugSave() {
      return !Core.bDebug ? false : false;
   }

    ByteBuffer Save(ByteBuffer var1, CRC32 var2) {
      var1.rewind();
      var1 = ensureCapacity(var1);
      var1.clear();
      var1.put((byte)(IsDebugSave() ? 1 : 0));
      var1.putInt(195);
      var1.putInt(0);
      var1.putLong(0L);
    int var3 = Math.min(1000, this.FloorBloodSplats.size());
    int var4 = this.FloorBloodSplats.size() - var3;
      var1.putInt(var3);

      for (int var5 = var4; var5 < this.FloorBloodSplats.size(); var5++) {
    IsoFloorBloodSplat var6 = (IsoFloorBloodSplat)this.FloorBloodSplats.get(var5);
         var6.save(var1);
      }

    int var18 = var1.position();
    uint8_t var19 = 0;
    int var7 = 0;
    int var8 = 0;

      for (int var9 = 0; var9 < 10; var9++) {
         for (int var10 = 0; var10 < 10; var10++) {
            var19 = 0;
            var7 = var1.position();
            var1.put(var19);

            for (int var11 = 0; var11 < 8; var11++) {
    IsoGridSquare var12 = this.getGridSquare(var9, var10, var11);
               var1 = ensureCapacity(var1);
               if (var12 != nullptr && var12.shouldSave()) {
                  var19 = (byte)(var19 | 1 << var11);
    int var13 = var1.position();

                  while (true) {
                     try {
                        var12.save(var1, nullptr, IsDebugSave());
                        break;
                     } catch (BufferOverflowException var15) {
                        DebugLog.log("IsoChunk.Save: BufferOverflowException, growing ByteBuffer");
                        var1 = ensureCapacity(var1);
                        var1.position(var13);
                     }
                  }
               }
            }

            var8 = var1.position();
            var1.position(var7);
            var1.put(var19);
            var1.position(var8);
         }
      }

      var1 = ensureCapacity(var1);
      this.getErosionData().save(var1);
      if (this.generatorsTouchingThisChunk == nullptr) {
         var1.putShort((short)0);
      } else {
         var1.putShort((short)this.generatorsTouchingThisChunk.size());

         for (int var23 = 0; var23 < this.generatorsTouchingThisChunk.size(); var23++) {
    Location var27 = this.generatorsTouchingThisChunk.get(var23);
            var1.putInt(var27.x);
            var1.putInt(var27.y);
            var1.put((byte)var27.z);
         }
      }

      var1.putShort((short)0);
      if ((!GameServer.bServer || GameServer.bSoftReset) && !GameClient.bClient && !GameWindow.bLoadedAsClient) {
         VehiclesDB2.instance.unloadChunk(this);
      }

      if (GameClient.bClient) {
    int var24 = ServerOptions.instance.HoursForLootRespawn.getValue();
         if (var24 > 0 && !(GameTime.getInstance().getWorldAgeHours() < var24)) {
            this.lootRespawnHour = 7 + (int)(GameTime.getInstance().getWorldAgeHours() / var24) * var24;
         } else {
            this.lootRespawnHour = -1;
         }
      }

      var1.putInt(this.lootRespawnHour);

      assert this.m_spawnedRooms.size() <= 127;

      var1.put((byte)this.m_spawnedRooms.size());

      for (int var25 = 0; var25 < this.m_spawnedRooms.size(); var25++) {
         var1.putInt(this.m_spawnedRooms.get(var25));
      }

    int var26 = var1.position();
      var2.reset();
      var2.update(var1.array(), 17, var26 - 1 - 4 - 4 - 8);
      var1.position(5);
      var1.putInt(var26);
      var1.putLong(var2.getValue());
      var1.position(var26);
    return var1;
   }

    bool saveObjectState(ByteBuffer var1) {
    bool var2 = true;

      for (int var3 = 0; var3 < 8; var3++) {
         for (int var4 = 0; var4 < 10; var4++) {
            for (int var5 = 0; var5 < 10; var5++) {
    IsoGridSquare var6 = this.getGridSquare(var5, var4, var3);
               if (var6 != nullptr) {
    int var7 = var6.getObjects().size();
                  IsoObject[] var8 = (IsoObject[])var6.getObjects().getElements();

                  for (int var9 = 0; var9 < var7; var9++) {
    IsoObject var10 = var8[var9];
    int var11 = var1.position();
                     var1.position(var11 + 2 + 2 + 4 + 2);
    int var12 = var1.position();
                     var10.saveState(var1);
    int var13 = var1.position();
                     if (var13 > var12) {
                        var1.position(var11);
                        var1.putShort((short)(var5 + var4 * 10 + var3 * 10 * 10));
                        var1.putShort((short)var9);
                        var1.putInt(var10.getObjectName().hashCode());
                        var1.putShort((short)(var13 - var12));
                        var1.position(var13);
                        var2 = false;
                     } else {
                        var1.position(var11);
                     }
                  }
               }
            }
         }
      }

      if (var2) {
    return false;
      } else {
         var1.putShort((short)-1);
    return true;
      }
   }

    void loadObjectState(ByteBuffer var1) {
      for (short var2 = var1.getShort(); var2 != -1; var2 = var1.getShort()) {
    int var3 = var2 % 10;
    int var4 = var2 / 100;
    int var5 = (var2 - var4 * 10 * 10) / 10;
    short var6 = var1.getShort();
    int var7 = var1.getInt();
    short var8 = var1.getShort();
    int var9 = var1.position();
    IsoGridSquare var10 = this.getGridSquare(var3, var5, var4);
         if (var10 != nullptr && var6 >= 0 && var6 < var10.getObjects().size()) {
    IsoObject var11 = (IsoObject)var10.getObjects().get(var6);
            if (var7 == var11.getObjectName().hashCode()) {
               var11.loadState(var1);

               assert var1.position() == var9 + var8;
            } else {
               var1.position(var9 + var8);
            }
         } else {
            var1.position(var9 + var8);
         }
      }
   }

    void Blam(int var1, int var2) {
      for (int var3 = 0; var3 < 8; var3++) {
         for (int var4 = 0; var4 < 10; var4++) {
            for (int var5 = 0; var5 < 10; var5++) {
               this.setSquare(var4, var5, var3, nullptr);
            }
         }
      }

      this.blam = true;
   }

    void BackupBlam(int var1, int var2, std::exception var3) {
    File var4 = ZomboidFileSystem.instance.getFileInCurrentSave("blam");
      var4.mkdirs();

      try {
    File var5 = std::make_shared<File>(var4 + File.separator + "map_" + var1 + "_" + var2 + "_error.txt");
    FileOutputStream var6 = std::make_shared<FileOutputStream>(var5);
    PrintStream var7 = std::make_shared<PrintStream>(var6);
         var3.printStackTrace(var7);
         var7.close();
      } catch (Exception var9) {
         var9.printStackTrace();
      }

    File var10 = ZomboidFileSystem.instance.getFileInCurrentSave("map_" + var1 + "_" + var2 + ".bin");
      if (var10.exists()) {
    File var11 = std::make_shared<File>(var4.getPath() + File.separator + "map_" + var1 + "_" + var2 + ".bin");

         try {
            copyFile(var10, var11);
         } catch (Exception var8) {
            var8.printStackTrace();
         }
      }
   }

    static void copyFile(File var0, File var1) {
      if (!var1.exists()) {
         var1.createNewFile();
      }

    FileChannel var2 = nullptr;
    FileChannel var3 = nullptr;

      try {
         var2 = std::make_shared<FileInputStream>(var0).getChannel();
         var3 = std::make_shared<FileOutputStream>(var1).getChannel();
         var3.transferFrom(var2, 0L, var2.size());
      } finally {
         if (var2 != nullptr) {
            var2.close();
         }

         if (var3 != nullptr) {
            var3.close();
         }
      }
   }

    Chunk getErosionData() {
      if (this.erosion == nullptr) {
         this.erosion = std::make_unique<Chunk>();
      }

      return this.erosion;
   }

    static int newtiledefinitions(int var0, int var1) {
    uint8_t var2 = 1;
      return var2 * 100 * 1000 + 10000 + var0 * 1000 + var1;
   }

    static int Fix2x(IsoGridSquare var0, int var1) {
      if (var0 == nullptr || var0.chunk == nullptr) {
    return var1;
      } else if (var0.chunk.bFixed2x) {
    return var1;
      } else {
    std::unordered_map var2 = IsoSpriteManager.instance.NamedMap;
         if (var1 >= newtiledefinitions(140, 48) && var1 <= newtiledefinitions(140, 51)) {
            return -1;
         } else if (var1 >= newtiledefinitions(8, 14) && var1 <= newtiledefinitions(8, 71) && var1 % 8 >= 6) {
            return -1;
         } else if (var1 == newtiledefinitions(92, 2)) {
            return var1 + 20;
         } else if (var1 == newtiledefinitions(92, 20)) {
            return var1 + 1;
         } else if (var1 == newtiledefinitions(92, 21)) {
            return var1 - 1;
         } else if (var1 >= newtiledefinitions(92, 26) && var1 <= newtiledefinitions(92, 29)) {
            return var1 + 6;
         } else if (var1 == newtiledefinitions(11, 16)) {
    return newtiledefinitions();
         } else if (var1 == newtiledefinitions(11, 17)) {
    return newtiledefinitions();
         } else if (var1 == newtiledefinitions(11, 18)) {
    return newtiledefinitions();
         } else if (var1 == newtiledefinitions(11, 19)) {
    return newtiledefinitions();
         } else if (var1 == newtiledefinitions(11, 24)) {
    return newtiledefinitions();
         } else if (var1 == newtiledefinitions(11, 25)) {
    return newtiledefinitions();
         } else if (var1 == newtiledefinitions(27, 42)) {
            return var1 + 1;
         } else if (var1 == newtiledefinitions(27, 43)) {
            return var1 - 1;
         } else if (var1 == newtiledefinitions(27, 44)) {
            return var1 + 3;
         } else if (var1 == newtiledefinitions(27, 47)) {
            return var1 - 2;
         } else if (var1 == newtiledefinitions(27, 45)) {
            return var1 + 1;
         } else if (var1 == newtiledefinitions(27, 46)) {
            return var1 - 2;
         } else if (var1 == newtiledefinitions(34, 4)) {
            return var1 + 1;
         } else if (var1 == newtiledefinitions(34, 5)) {
            return var1 - 1;
         } else if (var1 >= newtiledefinitions(14, 0) && var1 <= newtiledefinitions(14, 7)) {
            return -1;
         } else if (var1 >= newtiledefinitions(14, 8) && var1 <= newtiledefinitions(14, 12)) {
            return var1 + 72;
         } else if (var1 == newtiledefinitions(14, 13)) {
            return var1 + 71;
         } else if (var1 >= newtiledefinitions(14, 16) && var1 <= newtiledefinitions(14, 17)) {
            return var1 + 72;
         } else if (var1 == newtiledefinitions(14, 18)) {
            return var1 + 73;
         } else if (var1 == newtiledefinitions(14, 19)) {
            return var1 + 66;
         } else if (var1 == newtiledefinitions(14, 20)) {
            return -1;
         } else if (var1 == newtiledefinitions(14, 21)) {
    return newtiledefinitions();
         } else if (var1 == newtiledefinitions(21, 0)) {
    return newtiledefinitions();
         } else if (var1 == newtiledefinitions(21, 1)) {
    return newtiledefinitions();
         } else if (var1 == newtiledefinitions(21, 2)) {
    return newtiledefinitions();
         } else if (var1 == newtiledefinitions(26, 0)) {
    return newtiledefinitions();
         } else if (var1 == newtiledefinitions(26, 6)) {
    return newtiledefinitions();
         } else if (var1 == newtiledefinitions(26, 1)) {
    return newtiledefinitions();
         } else if (var1 == newtiledefinitions(26, 7)) {
    return newtiledefinitions();
         } else if (var1 == newtiledefinitions(26, 8)) {
    return newtiledefinitions();
         } else if (var1 == newtiledefinitions(26, 14)) {
    return newtiledefinitions();
         } else if (var1 == newtiledefinitions(26, 9)) {
    return newtiledefinitions();
         } else if (var1 == newtiledefinitions(26, 15)) {
    return newtiledefinitions();
         } else if (var1 == newtiledefinitions(26, 16)) {
    return newtiledefinitions();
         } else if (var1 == newtiledefinitions(26, 22)) {
    return newtiledefinitions();
         } else if (var1 == newtiledefinitions(26, 17)) {
    return newtiledefinitions();
         } else if (var1 == newtiledefinitions(26, 23)) {
    return newtiledefinitions();
         } else if (var1 >= newtiledefinitions(148, 0) && var1 <= newtiledefinitions(148, 16)) {
    int var5 = var1 - newtiledefinitions(148, 0);
    return newtiledefinitions();
         } else if ((var1 < newtiledefinitions(42, 44) || var1 > newtiledefinitions(42, 47))
            && (var1 < newtiledefinitions(42, 52) || var1 > newtiledefinitions(42, 55))) {
            if (var1 == newtiledefinitions(43, 24)) {
               return var1 + 4;
            } else if (var1 == newtiledefinitions(43, 26)) {
               return var1 + 2;
            } else if (var1 == newtiledefinitions(43, 33)) {
               return var1 - 4;
            } else if (var1 == newtiledefinitions(44, 0)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(44, 1)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(44, 2)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(44, 3)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(44, 4)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(44, 5)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(44, 6)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(44, 7)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(44, 16)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(44, 17)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(44, 18)) {
    return newtiledefinitions();
            } else if (var1 >= newtiledefinitions(44, 19) && var1 <= newtiledefinitions(44, 22)) {
               return var1 + 33;
            } else if (var1 == newtiledefinitions(44, 23)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(46, 8)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(46, 14)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(46, 15)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(46, 22)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(46, 23)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(46, 54)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(46, 55)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(106, 32)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(106, 34)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(47, 0) || var1 == newtiledefinitions(47, 4)) {
               return var1 + 1;
            } else if (var1 == newtiledefinitions(47, 1) || var1 == newtiledefinitions(47, 5)) {
               return var1 - 1;
            } else if (var1 >= newtiledefinitions(47, 8) && var1 <= newtiledefinitions(47, 13)) {
               return var1 + 8;
            } else if (var1 >= newtiledefinitions(47, 22) && var1 <= newtiledefinitions(47, 23)) {
               return var1 - 12;
            } else if (var1 >= newtiledefinitions(47, 44) && var1 <= newtiledefinitions(47, 47)) {
               return var1 + 4;
            } else if (var1 >= newtiledefinitions(47, 48) && var1 <= newtiledefinitions(47, 51)) {
               return var1 - 4;
            } else if (var1 == newtiledefinitions(48, 56)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(48, 58)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(52, 57)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(52, 58)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(52, 45)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(52, 46)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(54, 13)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(54, 15)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(54, 21)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(54, 22)) {
    return newtiledefinitions();
            } else if (var1 == newtiledefinitions(54, 23)) {
    return newtiledefinitions();
            } else if (var1 >= newtiledefinitions(67, 0) && var1 <= newtiledefinitions(67, 16)) {
    int var4 = 64 + Rand.Next(16);
               return ((IsoSprite)var2.get("f_bushes_1_" + var4)).ID;
            } else if (var1 == newtiledefinitions(68, 6)) {
               return -1;
            } else if (var1 >= newtiledefinitions(68, 16) && var1 <= newtiledefinitions(68, 17)) {
               return ((IsoSprite)var2.get("d_plants_1_53")).ID;
            } else if (var1 >= newtiledefinitions(68, 18) && var1 <= newtiledefinitions(68, 23)) {
    int var3 = Rand.Next(4) * 16 + Rand.Next(8);
               return ((IsoSprite)var2.get("d_plants_1_" + var3)).ID;
            } else {
               return var1 >= newtiledefinitions(79, 24) && var1 <= newtiledefinitions(79, 41)
                  ? newtiledefinitions(81, var1 - newtiledefinitions(79, 24))
                  : var1;
            }
         } else {
            return -1;
         }
      }
   }

    static std::string Fix2x(const std::string& var0) {
      if (Fix2xMap.empty()) {
    std::unordered_map var1 = Fix2xMap;

         for (int var2 = 48; var2 <= 51; var2++) {
            var1.put("blends_streetoverlays_01_" + var2, "");
         }

         var1.put("fencing_01_14", "");
         var1.put("fencing_01_15", "");
         var1.put("fencing_01_22", "");
         var1.put("fencing_01_23", "");
         var1.put("fencing_01_30", "");
         var1.put("fencing_01_31", "");
         var1.put("fencing_01_38", "");
         var1.put("fencing_01_39", "");
         var1.put("fencing_01_46", "");
         var1.put("fencing_01_47", "");
         var1.put("fencing_01_62", "");
         var1.put("fencing_01_63", "");
         var1.put("fencing_01_70", "");
         var1.put("fencing_01_71", "");
         var1.put("fixtures_bathroom_02_2", "fixtures_bathroom_02_22");
         var1.put("fixtures_bathroom_02_20", "fixtures_bathroom_02_21");
         var1.put("fixtures_bathroom_02_21", "fixtures_bathroom_02_20");

         for (int var4 = 26; var4 <= 29; var4++) {
            var1.put("fixtures_bathroom_02_" + var4, "fixtures_bathroom_02_" + (var4 + 6));
         }

         var1.put("fixtures_counters_01_16", "fixtures_counters_01_45");
         var1.put("fixtures_counters_01_17", "fixtures_counters_01_43");
         var1.put("fixtures_counters_01_18", "fixtures_counters_01_41");
         var1.put("fixtures_counters_01_19", "fixtures_counters_01_47");
         var1.put("fixtures_counters_01_24", "fixtures_counters_01_26");
         var1.put("fixtures_counters_01_25", "fixtures_counters_01_27");

         for (int var5 = 0; var5 <= 7; var5++) {
            var1.put("fixtures_railings_01_" + var5, "");
         }

         for (int var6 = 8; var6 <= 12; var6++) {
            var1.put("fixtures_railings_01_" + var6, "fixtures_railings_01_" + (var6 + 72));
         }

         var1.put("fixtures_railings_01_13", "fixtures_railings_01_84");

         for (int var7 = 16; var7 <= 17; var7++) {
            var1.put("fixtures_railings_01_" + var7, "fixtures_railings_01_" + (var7 + 72));
         }

         var1.put("fixtures_railings_01_18", "fixtures_railings_01_91");
         var1.put("fixtures_railings_01_19", "fixtures_railings_01_85");
         var1.put("fixtures_railings_01_20", "");
         var1.put("fixtures_railings_01_21", "fixtures_railings_01_89");
         var1.put("floors_exterior_natural_01_0", "blends_natural_01_16");
         var1.put("floors_exterior_natural_01_1", "blends_natural_01_32");
         var1.put("floors_exterior_natural_01_2", "blends_natural_01_48");
         var1.put("floors_rugs_01_0", "floors_rugs_01_6");
         var1.put("floors_rugs_01_6", "floors_rugs_01_0");
         var1.put("floors_rugs_01_1", "floors_rugs_01_7");
         var1.put("floors_rugs_01_7", "floors_rugs_01_1");
         var1.put("floors_rugs_01_8", "floors_rugs_01_14");
         var1.put("floors_rugs_01_14", "floors_rugs_01_8");
         var1.put("floors_rugs_01_9", "floors_rugs_01_15");
         var1.put("floors_rugs_01_15", "floors_rugs_01_9");
         var1.put("floors_rugs_01_16", "floors_rugs_01_22");
         var1.put("floors_rugs_01_22", "floors_rugs_01_16");
         var1.put("floors_rugs_01_17", "floors_rugs_01_23");
         var1.put("floors_rugs_01_23", "floors_rugs_01_17");
         var1.put("furniture_bedding_01_42", "furniture_bedding_01_43");
         var1.put("furniture_bedding_01_43", "furniture_bedding_01_42");
         var1.put("furniture_bedding_01_44", "furniture_bedding_01_47");
         var1.put("furniture_bedding_01_47", "furniture_bedding_01_45");
         var1.put("furniture_bedding_01_45", "furniture_bedding_01_46");
         var1.put("furniture_bedding_01_46", "furniture_bedding_01_44");
         var1.put("furniture_tables_low_01_4", "furniture_tables_low_01_5");
         var1.put("furniture_tables_low_01_5", "furniture_tables_low_01_4");

         for (int var8 = 0; var8 <= 5; var8++) {
            var1.put("location_business_machinery_" + var8, "location_business_machinery_01_" + var8);
            var1.put("location_business_machinery_" + (var8 + 8), "location_business_machinery_01_" + (var8 + 8));
            var1.put("location_ business_machinery_" + var8, "location_business_machinery_01_" + var8);
            var1.put("location_ business_machinery_" + (var8 + 8), "location_business_machinery_01_" + (var8 + 8));
         }

         for (int var9 = 44; var9 <= 47; var9++) {
            var1.put("location_hospitality_sunstarmotel_01_" + var9, "");
         }

         for (int var10 = 52; var10 <= 55; var10++) {
            var1.put("location_hospitality_sunstarmotel_01_" + var10, "");
         }

         var1.put("location_hospitality_sunstarmotel_02_24", "location_hospitality_sunstarmotel_02_28");
         var1.put("location_hospitality_sunstarmotel_02_26", "location_hospitality_sunstarmotel_02_28");
         var1.put("location_hospitality_sunstarmotel_02_33", "location_hospitality_sunstarmotel_02_29");
         var1.put("location_restaurant_bar_01_0", "location_restaurant_bar_01_1");
         var1.put("location_restaurant_bar_01_1", "location_restaurant_bar_01_0");
         var1.put("location_restaurant_bar_01_2", "location_restaurant_bar_01_7");
         var1.put("location_restaurant_bar_01_3", "location_restaurant_bar_01_6");
         var1.put("location_restaurant_bar_01_4", "location_restaurant_bar_01_5");
         var1.put("location_restaurant_bar_01_5", "location_restaurant_bar_01_4");
         var1.put("location_restaurant_bar_01_6", "location_restaurant_bar_01_3");
         var1.put("location_restaurant_bar_01_7", "location_restaurant_bar_01_2");
         var1.put("location_restaurant_bar_01_16", "location_restaurant_bar_01_45");
         var1.put("location_restaurant_bar_01_17", "location_restaurant_bar_01_44");
         var1.put("location_restaurant_bar_01_18", "location_restaurant_bar_01_46");

         for (int var11 = 19; var11 <= 22; var11++) {
            var1.put("location_restaurant_bar_01_" + var11, "location_restaurant_bar_01_" + (var11 + 33));
         }

         var1.put("location_restaurant_bar_01_23", "location_restaurant_bar_01_47");
         var1.put("location_restaurant_pie_01_8", "location_restaurant_pie_01_5");
         var1.put("location_restaurant_pie_01_14", "location_restaurant_pie_01_10");
         var1.put("location_restaurant_pie_01_15", "location_restaurant_pie_01_11");
         var1.put("location_restaurant_pie_01_22", "location_restaurant_pie_01_14");
         var1.put("location_restaurant_pie_01_23", "location_restaurant_pie_01_15");
         var1.put("location_restaurant_pie_01_54", "location_restaurant_pie_01_55");
         var1.put("location_restaurant_pie_01_55", "location_restaurant_pie_01_54");
         var1.put("location_pizzawhirled_01_32", "location_pizzawhirled_01_34");
         var1.put("location_pizzawhirled_01_34", "location_pizzawhirled_01_32");
         var1.put("location_restaurant_seahorse_01_0", "location_restaurant_seahorse_01_1");
         var1.put("location_restaurant_seahorse_01_1", "location_restaurant_seahorse_01_0");
         var1.put("location_restaurant_seahorse_01_4", "location_restaurant_seahorse_01_5");
         var1.put("location_restaurant_seahorse_01_5", "location_restaurant_seahorse_01_4");

         for (int var12 = 8; var12 <= 13; var12++) {
            var1.put("location_restaurant_seahorse_01_" + var12, "location_restaurant_seahorse_01_" + (var12 + 8));
         }

         for (int var13 = 22; var13 <= 23; var13++) {
            var1.put("location_restaurant_seahorse_01_" + var13, "location_restaurant_seahorse_01_" + (var13 - 12));
         }

         for (int var14 = 44; var14 <= 47; var14++) {
            var1.put("location_restaurant_seahorse_01_" + var14, "location_restaurant_seahorse_01_" + (var14 + 4));
         }

         for (int var15 = 48; var15 <= 51; var15++) {
            var1.put("location_restaurant_seahorse_01_" + var15, "location_restaurant_seahorse_01_" + (var15 - 4));
         }

         var1.put("location_restaurant_spiffos_01_56", "location_restaurant_spiffos_01_58");
         var1.put("location_restaurant_spiffos_01_58", "location_restaurant_spiffos_01_56");
         var1.put("location_shop_fossoil_01_45", "location_shop_fossoil_01_44");
         var1.put("location_shop_fossoil_01_46", "location_shop_fossoil_01_45");
         var1.put("location_shop_fossoil_01_57", "location_shop_fossoil_01_58");
         var1.put("location_shop_fossoil_01_58", "location_shop_fossoil_01_59");
         var1.put("location_shop_greenes_01_13", "location_shop_greenes_01_18");
         var1.put("location_shop_greenes_01_15", "location_shop_greenes_01_19");
         var1.put("location_shop_greenes_01_21", "location_shop_greenes_01_16");
         var1.put("location_shop_greenes_01_22", "location_shop_greenes_01_13");
         var1.put("location_shop_greenes_01_23", "location_shop_greenes_01_17");
         var1.put("location_shop_greenes_01_67", "location_shop_greenes_01_70");
         var1.put("location_shop_greenes_01_68", "location_shop_greenes_01_67");
         var1.put("location_shop_greenes_01_70", "location_shop_greenes_01_71");
         var1.put("location_shop_greenes_01_75", "location_shop_greenes_01_78");
         var1.put("location_shop_greenes_01_76", "location_shop_greenes_01_75");
         var1.put("location_shop_greenes_01_78", "location_shop_greenes_01_79");

         for (int var16 = 0; var16 <= 16; var16++) {
            var1.put("vegetation_foliage_01_" + var16, "randBush");
         }

         var1.put("vegetation_groundcover_01_0", "blends_grassoverlays_01_16");
         var1.put("vegetation_groundcover_01_1", "blends_grassoverlays_01_8");
         var1.put("vegetation_groundcover_01_2", "blends_grassoverlays_01_0");
         var1.put("vegetation_groundcover_01_3", "blends_grassoverlays_01_64");
         var1.put("vegetation_groundcover_01_4", "blends_grassoverlays_01_56");
         var1.put("vegetation_groundcover_01_5", "blends_grassoverlays_01_48");
         var1.put("vegetation_groundcover_01_6", "");
         var1.put("vegetation_groundcover_01_44", "blends_grassoverlays_01_40");
         var1.put("vegetation_groundcover_01_45", "blends_grassoverlays_01_32");
         var1.put("vegetation_groundcover_01_46", "blends_grassoverlays_01_24");
         var1.put("vegetation_groundcover_01_16", "d_plants_1_53");
         var1.put("vegetation_groundcover_01_17", "d_plants_1_53");

         for (int var17 = 18; var17 <= 23; var17++) {
            var1.put("vegetation_groundcover_01_" + var17, "randPlant");
         }

         for (int var18 = 20; var18 <= 23; var18++) {
            var1.put("walls_exterior_house_01_" + var18, "walls_exterior_house_01_" + (var18 + 12));
            var1.put("walls_exterior_house_01_" + (var18 + 8), "walls_exterior_house_01_" + (var18 + 8 + 12));
         }

         for (int var19 = 24; var19 <= 41; var19++) {
            var1.put("walls_exterior_roofs_01_" + var19, "walls_exterior_roofs_03_" + var19);
         }
      }

    std::string var3 = Fix2xMap.get(var0);
      if (var3 == nullptr) {
    return var0;
      } else if ("randBush" == var3)) {
    int var21 = 64 + Rand.Next(16);
         return "f_bushes_1_" + var21;
      } else if ("randPlant" == var3)) {
    int var20 = Rand.Next(4) * 16 + Rand.Next(8);
         return "d_plants_1_" + var20;
      } else {
    return var3;
      }
   }

    void addGeneratorPos(int var1, int var2, int var3) {
      if (this.generatorsTouchingThisChunk == nullptr) {
         this.generatorsTouchingThisChunk = std::make_unique<std::vector<>>();
      }

      for (int var4 = 0; var4 < this.generatorsTouchingThisChunk.size(); var4++) {
    Location var5 = this.generatorsTouchingThisChunk.get(var4);
         if (var5.x == var1 && var5.y == var2 && var5.z == var3) {
            return;
         }
      }

    Location var6 = std::make_shared<Location>(var1, var2, var3);
      this.generatorsTouchingThisChunk.push_back(var6);
   }

    void removeGeneratorPos(int var1, int var2, int var3) {
      if (this.generatorsTouchingThisChunk != nullptr) {
         for (int var4 = 0; var4 < this.generatorsTouchingThisChunk.size(); var4++) {
    Location var5 = this.generatorsTouchingThisChunk.get(var4);
            if (var5.x == var1 && var5.y == var2 && var5.z == var3) {
               this.generatorsTouchingThisChunk.remove(var4);
               var4--;
            }
         }
      }
   }

    bool isGeneratorPoweringSquare(int var1, int var2, int var3) {
      if (this.generatorsTouchingThisChunk == nullptr) {
    return false;
      } else {
         for (int var4 = 0; var4 < this.generatorsTouchingThisChunk.size(); var4++) {
    Location var5 = this.generatorsTouchingThisChunk.get(var4);
            if (IsoGenerator.isPoweringSquare(var5.x, var5.y, var5.z, var1, var2, var3)) {
    return true;
            }
         }

    return false;
      }
   }

    void checkForMissingGenerators() {
      if (this.generatorsTouchingThisChunk != nullptr) {
         for (int var1 = 0; var1 < this.generatorsTouchingThisChunk.size(); var1++) {
    Location var2 = this.generatorsTouchingThisChunk.get(var1);
    IsoGridSquare var3 = IsoWorld.instance.CurrentCell.getGridSquare(var2.x, var2.y, var2.z);
            if (var3 != nullptr) {
    IsoGenerator var4 = var3.getGenerator();
               if (var4 == nullptr || !var4.isActivated()) {
                  this.generatorsTouchingThisChunk.remove(var1);
                  var1--;
               }
            }
         }
      }
   }

    bool isNewChunk() {
      return this.addZombies;
   }

    void addSpawnedRoom(int var1) {
      if (!this.m_spawnedRooms.contains(var1)) {
         this.m_spawnedRooms.push_back(var1);
      }
   }

    bool isSpawnedRoom(int var1) {
      return this.m_spawnedRooms.contains(var1);
   }

    Zone getScavengeZone() {
      if (this.m_scavengeZone != nullptr) {
         return this.m_scavengeZone;
      } else {
    IsoMetaChunk var1 = IsoWorld.instance.getMetaGrid().getChunkData(this.wx, this.wy);
         if (var1 != nullptr && var1.numZones() > 0) {
            for (int var2 = 0; var2 < var1.numZones(); var2++) {
    Zone var3 = var1.getZone(var2);
               if ("DeepForest" == var3.type) || "Forest" == var3.type)) {
                  this.m_scavengeZone = var3;
    return var3;
               }

               if ("Nav" == var3.type) || "Town" == var3.type)) {
    return nullptr;
               }
            }
         }

    uint8_t var8 = 5;
         if (this.m_treeCount < var8) {
    return nullptr;
         } else {
    int var9 = 0;

            for (int var4 = -1; var4 <= 1; var4++) {
               for (int var5 = -1; var5 <= 1; var5++) {
                  if (var5 != 0 || var4 != 0) {
                     IsoChunk var6 = GameServer.bServer
                        ? ServerMap.instance.getChunk(this.wx + var5, this.wy + var4)
                        : IsoWorld.instance.CurrentCell.getChunk(this.wx + var5, this.wy + var4);
                     if (var6 != nullptr && var6.m_treeCount >= var8) {
                        if (++var9 == 8) {
    uint8_t var7 = 10;
                           this.m_scavengeZone = std::make_shared<Zone>("", "Forest", this.wx * var7, this.wy * var7, 0, var7, var7);
                           return this.m_scavengeZone;
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
      this.randomID = 0;
      this.revision = 0L;
      this.nextSplatIndex = 0;
      this.FloorBloodSplats.clear();
      this.FloorBloodSplatsFade.clear();
      this.jobType = JobType.None;
      this.maxLevel = -1;
      this.bFixed2x = false;
      this.vehicles.clear();
      this.roomLights.clear();
      this.blam = false;
      this.lotheader = nullptr;
      this.bLoaded = false;
      this.addZombies = false;
      this.physicsCheck = false;
      this.loadedPhysics = false;
      this.wx = 0;
      this.wy = 0;
      this.erosion = nullptr;
      this.lootRespawnHour = -1;
      if (this.generatorsTouchingThisChunk != nullptr) {
         this.generatorsTouchingThisChunk.clear();
      }

      this.m_treeCount = 0;
      this.m_scavengeZone = nullptr;
      this.m_numberOfWaterTiles = 0;
      this.m_spawnedRooms.resetQuick();
      this.m_adjacentChunkLoadedCounter = 0;

      for (int var1 = 0; var1 < this.squares.length; var1++) {
         for (int var2 = 0; var2 < this.squares[0].length; var2++) {
            this.squares[var1][var2] = nullptr;
         }
      }

      for (int var3 = 0; var3 < 4; var3++) {
         this.lightCheck[var3] = true;
         this.bLightingNeverDone[var3] = true;
      }

      this.refs.clear();
      this.m_vehicleStorySpawnData = nullptr;
      this.m_loadVehiclesObject = nullptr;
      this.m_objectEmitterData.reset();
      MPStatistics.increaseStoredChunk();
   }

    int getNumberOfWaterTiles() {
      return this.m_numberOfWaterTiles;
   }

    void setRandomVehicleStoryToSpawnLater(VehicleStorySpawnData var1) {
      this.m_vehicleStorySpawnData = var1;
   }

    bool hasObjectAmbientEmitter(IsoObject var1) {
      return this.m_objectEmitterData.hasObject(var1);
   }

    void addObjectAmbientEmitter(IsoObject var1, PerObjectLogic var2) {
      this.m_objectEmitterData.addObject(var1, var2);
   }

    void removeObjectAmbientEmitter(IsoObject var1) {
      this.m_objectEmitterData.removeObject(var1);
   }
}
} // namespace iso
} // namespace zombie
