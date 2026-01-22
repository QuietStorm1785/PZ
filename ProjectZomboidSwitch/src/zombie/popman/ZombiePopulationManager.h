#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/array/TIntArrayList.h"
#include "gnu/trove/set/hash/TIntHashSet.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/DebugFileWatcher.h"
#include "zombie/GameTime.h"
#include "zombie/MapCollisionData.h"
#include "zombie/PersistentOutfits.h"
#include "zombie/PredicatedFileWatcher.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SandboxOptions/ZombieConfig.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/WorldSoundManager/WorldSound.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/ai/states/PathFindState.h"
#include "zombie/ai/states/WalkTowardState.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/gameStates/ChooseGameInfo/SpawnOrigin.h"
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
#include <filesystem>

namespace zombie {
namespace popman {


class ZombiePopulationManager {
public:
    static const ZombiePopulationManager instance = std::make_shared<ZombiePopulationManager>();
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
    const DebugCommands dbgCommands = std::make_shared<DebugCommands>();
    static bool bDebugLoggingEnabled = false;
    const LoadedAreas loadedAreas = std::make_shared<LoadedAreas>(false);
    const LoadedAreas loadedServerCells = std::make_shared<LoadedAreas>(true);
    const PlayerSpawns playerSpawns = std::make_shared<PlayerSpawns>();
   private short[] realZombieCount;
   private short[] realZombieCount2;
    long realZombieUpdateTime = 0L;
   private const std::vector<IsoZombie> saveRealZombieHack = std::make_unique<std::vector<>>();
    const ByteBuffer byteBuffer = ByteBuffer.allocateDirect(1024);
    const TIntHashSet newChunks = std::make_shared<TIntHashSet>();
   private const std::vector<SpawnOrigin> spawnOrigins = std::make_unique<std::vector<>>();
   public float[] radarXY;
    int radarCount;
    bool radarRenderFlag;
    bool radarRequestFlag;
   private const std::vector<IsoDirections> m_sittingDirections = std::make_unique<std::vector<>>();

   ZombiePopulationManager() {
      this.newChunks.setAutoCompactionFactor(0.0F);
   }

   private static native void n_init(boolean var0, boolean var1, int var2, int var3, int var4, int var5);

   private static native void n_config(float var0, float var1, float var2, int var3, float var4, float var5, float var6, float var7, int var8);

   private static native void n_setSpawnOrigins(int[] var0);

   private static native void n_setOutfitNames(std::string[] var0);

   private static native void n_updateMain(float var0, double var1);

   private static native boolean n_hasDataForThread();

   private static native void n_updateThread();

   private static native boolean n_shouldWait();

   private static native void n_beginSaveRealZombies(int var0);

   private static native void n_saveRealZombies(int var0, ByteBuffer var1);

   private static native void n_save();

   private static native void n_stop();

   private static native void n_addZombie(float var0, float var1, float var2, byte var3, int var4, int var5, int var6, int var7);

   private static native void n_aggroTarget(int var0, int var1, int var2);

   private static native void n_loadChunk(int var0, int var1, boolean var2);

   private static native void n_loadedAreas(int var0, int[] var1, boolean var2);

   protected static native void n_realZombieCount(short var0, short[] var1);

   protected static native void n_spawnHorde(int var0, int var1, int var2, int var3, float var4, float var5, int var6);

   private static native void n_worldSound(int var0, int var1, int var2, int var3);

   private static native int n_getAddZombieCount();

   private static native int n_getAddZombieData(int var0, ByteBuffer var1);

   private static native boolean n_hasRadarData();

   private static native void n_requestRadarData();

   private static native int n_getRadarZombieData(float[] var0);

    static void noise(const std::string& var0) {
      if (bDebugLoggingEnabled && (Core.bDebug || GameServer.bServer && GameServer.bDebug)) {
         DebugLog.log("ZPOP: " + var0);
      }
   }

    static void init() {
    std::string var0 = "";
      if ("1" == System.getProperty("zomboid.debuglibs.popman"))) {
         DebugLog.log("***** Loading debug version of PZPopMan");
         var0 = "d";
      }

      if (System.getProperty("os.name").contains("OS X")) {
         System.loadLibrary("PZPopMan");
      } else if (System.getProperty("sun.arch.data.model") == "64")) {
         System.loadLibrary("PZPopMan64" + var0);
      } else {
         System.loadLibrary("PZPopMan32" + var0);
      }

      DebugFileWatcher.instance
         .push_back(std::make_shared<PredicatedFileWatcher>(ZomboidFileSystem.instance.getMessagingDirSub("Trigger_Zombie.xml"), ZombiePopulationManager::onTriggeredZombieFile));
   }

    static void onTriggeredZombieFile(const std::string& var0) {
      DebugLog.General.println("ZombiePopulationManager.onTriggeredZombieFile(" + var0 + ">");

    ZombieTriggerXmlFile var1;
      try {
         var1 = (ZombieTriggerXmlFile)PZXmlUtil.parse(ZombieTriggerXmlFile.class, var0);
      } catch (PZXmlParserException var3) {
         System.err.println("ZombiePopulationManager.onTriggeredZombieFile> Exception thrown. " + var3);
         var3.printStackTrace();
         return;
      }

      if (var1.spawnHorde > 0) {
         processTriggerSpawnHorde(var1);
      }

      if (var1.setDebugLoggingEnabled && bDebugLoggingEnabled != var1.bDebugLoggingEnabled) {
         bDebugLoggingEnabled = var1.bDebugLoggingEnabled;
         DebugLog.General.println("  bDebugLoggingEnabled: " + bDebugLoggingEnabled);
      }
   }

    static void processTriggerSpawnHorde(ZombieTriggerXmlFile var0) {
      DebugLog.General.println("  spawnHorde: " + var0.spawnHorde);
      if (IsoPlayer.getInstance() != nullptr) {
    IsoPlayer var1 = IsoPlayer.getInstance();
         instance.createHordeFromTo((int)var1.x, (int)var1.y, (int)var1.x, (int)var1.y, var0.spawnHorde);
      }
   }

    void init(IsoMetaGrid var1) {
      this.bClient = GameClient.bClient;
      if (!this.bClient) {
         this.minX = var1.getMinX();
         this.minY = var1.getMinY();
         this.width = var1.getWidth();
         this.height = var1.getHeight();
         this.bStopped = false;
         n_init(this.bClient, GameServer.bServer, this.minX, this.minY, this.width, this.height);
         this.onConfigReloaded();
         std::string[] var2 = PersistentOutfits.instance.getOutfitNames().toArray(new std::string[0]);

         for (int var3 = 0; var3 < var2.length; var3++) {
            var2[var3] = var2[var3].toLowerCase();
         }

         n_setOutfitNames(var2);
    TIntArrayList var6 = std::make_shared<TIntArrayList>();

         for (SpawnOrigin var5 : this.spawnOrigins) {
            var6.push_back(var5.x);
            var6.push_back(var5.y);
            var6.push_back(var5.w);
            var6.push_back(var5.h);
         }

         n_setSpawnOrigins(var6.toArray());
      }
   }

    void onConfigReloaded() {
    ZombieConfig var1 = SandboxOptions.instance.zombieConfig;
      n_config(
         (float)var1.PopulationMultiplier.getValue(),
         (float)var1.PopulationStartMultiplier.getValue(),
         (float)var1.PopulationPeakMultiplier.getValue(),
         var1.PopulationPeakDay.getValue(),
         (float)var1.RespawnHours.getValue(),
         (float)var1.RespawnUnseenHours.getValue(),
         (float)var1.RespawnMultiplier.getValue() * 100.0F,
         (float)var1.RedistributeHours.getValue(),
         var1.FollowSoundDistance.getValue()
      );
   }

    void registerSpawnOrigin(int var1, int var2, int var3, int var4, KahluaTable var5) {
      if (var1 >= 0 && var2 >= 0 && var3 >= 0 && var4 >= 0) {
         this.spawnOrigins.push_back(std::make_shared<SpawnOrigin>(var1, var2, var3, var4));
      }
   }

    void playerSpawnedAt(int var1, int var2, int var3) {
      this.playerSpawns.addSpawn(var1, var2, var3);
   }

    void addChunkToWorld(IsoChunk var1) {
      if (!this.bClient) {
         if (var1.isNewChunk()) {
    int var2 = var1.wy << 16 | var1.wx;
            this.newChunks.push_back(var2);
         }

         n_loadChunk(var1.wx, var1.wy, true);
      }
   }

    void removeChunkFromWorld(IsoChunk var1) {
      if (!this.bClient) {
         if (!this.bStopped) {
            n_loadChunk(var1.wx, var1.wy, false);

            for (int var2 = 0; var2 < 8; var2++) {
               for (int var3 = 0; var3 < 10; var3++) {
                  for (int var4 = 0; var4 < 10; var4++) {
    IsoGridSquare var5 = var1.getGridSquare(var4, var3, var2);
                     if (var5 != nullptr && !var5.getMovingObjects().empty()) {
                        for (int var6 = 0; var6 < var5.getMovingObjects().size(); var6++) {
    IsoMovingObject var7 = (IsoMovingObject)var5.getMovingObjects().get(var6);
                           if (dynamic_cast<IsoZombie*>(var7) != nullptr var8 && (!GameServer.bServer || !var8.bIndoorZombie) && !var8.isReanimatedPlayer()) {
    int var9 = this.getZombieState(var8);
                              if (var2 != 0
                                 || var5.getRoom() != nullptr
                                 || var8.getCurrentState() != WalkTowardState.instance() && var8.getCurrentState() != PathFindState.instance()) {
                                 n_addZombie(var8.x, var8.y, var8.z, (byte)var8.dir.index(), var8.getPersistentOutfitID(), var9, -1, -1);
                              } else {
                                 n_addZombie(
                                    var8.x,
                                    var8.y,
                                    var8.z,
                                    (byte)var8.dir.index(),
                                    var8.getPersistentOutfitID(),
                                    var9,
                                    var8.getPathTargetX(),
                                    var8.getPathTargetY()
                                 );
                              }
                           }
                        }
                     }
                  }
               }
            }

    int var10 = var1.wy << 16 | var1.wx;
            this.newChunks.remove(var10);
            if (GameServer.bServer) {
               MapCollisionData.instance.notifyThread();
            }
         }
      }
   }

    void virtualizeZombie(IsoZombie var1) {
    int var2 = this.getZombieState(var1);
      n_addZombie(var1.x, var1.y, var1.z, (byte)var1.dir.index(), var1.getPersistentOutfitID(), var2, var1.getPathTargetX(), var1.getPathTargetY());
      var1.removeFromWorld();
      var1.removeFromSquare();
   }

    int getZombieState(IsoZombie var1) {
    uint8_t var2 = 1;
      if (var1.isCrawling()) {
         var2 |= 2;
      }

      if (var1.isCanWalk()) {
         var2 |= 4;
      }

      if (var1.isFakeDead()) {
         var2 |= 8;
      }

      if (var1.isCanCrawlUnderVehicle()) {
         var2 |= 16;
      }

    return var2;
   }

    void setAggroTarget(int var1, int var2, int var3) {
      n_aggroTarget(var1, var2, var3);
   }

    void createHordeFromTo(int var1, int var2, int var3, int var4, int var5) {
      n_spawnHorde(var1, var2, 0, 0, var3, var4, var5);
   }

    void createHordeInAreaTo(int var1, int var2, int var3, int var4, int var5, int var6, int var7) {
      n_spawnHorde(var1, var2, var3, var4, var5, var6, var7);
   }

    void addWorldSound(WorldSound var1, bool var2) {
      if (!this.bClient) {
         if (var1.radius >= 50) {
            if (!var1.sourceIsZombie) {
    int var3 = SandboxOptions.instance.Lore.Hearing.getValue();
               if (var3 == 4) {
                  var3 = 2;
               }

    float var4 = WorldSoundManager.instance.getHearingMultiplier(var3);
               n_worldSound(var1.x, var1.y, (int)PZMath.ceil(var1.radius * var4), var1.volume);
            }
         }
      }
   }

    void updateRealZombieCount() {
      if (this.realZombieCount == nullptr || this.realZombieCount.length != this.width * this.height) {
         this.realZombieCount = new short[this.width * this.height];
         this.realZombieCount2 = new short[this.width * this.height * 2];
      }

      Arrays.fill(this.realZombieCount, (short)0);
    std::vector var1 = IsoWorld.instance.CurrentCell.getZombieList();

      for (int var2 = 0; var2 < var1.size(); var2++) {
    IsoZombie var3 = (IsoZombie)var1.get(var2);
    int var4 = (int)(var3.x / 300.0F) - this.minX;
    int var5 = (int)(var3.y / 300.0F) - this.minY;
         this.realZombieCount[var4 + var5 * this.width]++;
      }

    short var6 = 0;

      for (int var7 = 0; var7 < this.width * this.height; var7++) {
         if (this.realZombieCount[var7] > 0) {
            this.realZombieCount2[var6 * 2 + 0] = (short)var7;
            this.realZombieCount2[var6 * 2 + 1] = this.realZombieCount[var7];
            var6++;
         }
      }

      n_realZombieCount(var6, this.realZombieCount2);
   }

    void updateMain() {
      if (!this.bClient) {
    long var1 = System.currentTimeMillis();
         n_updateMain(GameTime.getInstance().getMultiplier(), GameTime.getInstance().getWorldAgeHours());
    int var3 = 0;
    int var4 = 0;
    int var5 = n_getAddZombieCount();
    int var6 = 0;

         while (var6 < var5) {
            this.byteBuffer.clear();
    int var7 = n_getAddZombieData(var6, this.byteBuffer);
            var6 += var7;

            for (int var8 = 0; var8 < var7; var8++) {
    float var9 = this.byteBuffer.getFloat();
    float var10 = this.byteBuffer.getFloat();
    float var11 = this.byteBuffer.getFloat();
    IsoDirections var12 = IsoDirections.fromIndex(this.byteBuffer.get());
    int var13 = this.byteBuffer.getInt();
    int var14 = this.byteBuffer.getInt();
    int var15 = this.byteBuffer.getInt();
    int var16 = this.byteBuffer.getInt();
    int var17 = (int)var9 / 10;
    int var18 = (int)var10 / 10;
    int var19 = var18 << 16 | var17;
               if (this.newChunks.contains(var19)) {
    IsoGridSquare var20 = IsoWorld.instance.CurrentCell.getGridSquare((int)var9, (int)var10, (int)var11);
                  if (var20 != nullptr && var20.roomID != -1) {
                     continue;
                  }
               }

               if (var15 != -1 && this.loadedAreas.isOnEdge((int)var9, (int)var10)) {
                  var15 = -1;
                  var16 = -1;
               }

               if (var15 == -1) {
                  this.addZombieStanding(var9, var10, var11, var12, var13, var14);
                  var3++;
               } else {
                  this.addZombieMoving(var9, var10, var11, var12, var13, var14, var15, var16);
                  var4++;
               }
            }
         }

         if (var3 > 0) {
            noise("unloaded -> real " + var5);
         }

         if (var4 > 0) {
            noise("virtual -> real " + var5);
         }

         if (this.radarRenderFlag && this.radarXY != nullptr) {
            if (this.radarRequestFlag) {
               if (n_hasRadarData()) {
                  this.radarCount = n_getRadarZombieData(this.radarXY);
                  this.radarRenderFlag = false;
                  this.radarRequestFlag = false;
               }
            } else {
               n_requestRadarData();
               this.radarRequestFlag = true;
            }
         }

         this.updateLoadedAreas();
         if (this.realZombieUpdateTime + 5000L < var1) {
            this.realZombieUpdateTime = var1;
            this.updateRealZombieCount();
         }

         if (GameServer.bServer) {
            MPDebugInfo.instance.serverUpdate();
         }

    bool var21 = n_hasDataForThread();
    bool var22 = MapCollisionData.instance.hasDataForThread();
         if (var21 || var22) {
            MapCollisionData.instance.notifyThread();
         }

         this.playerSpawns.update();
      }
   }

    void addZombieStanding(float var1, float var2, float var3, IsoDirections var4, int var5, int var6) {
    IsoGridSquare var7 = IsoWorld.instance.CurrentCell.getGridSquare((int)var1, (int)var2, (int)var3);
      if (var7 != nullptr && (var7.SolidFloorCached ? var7.SolidFloor : var7.TreatAsSolidFloor())) {
         if (!Core.bLastStand && !this.playerSpawns.allowZombie(var7)) {
            noise("removed zombie near player spawn " + (int)var1 + "," + (int)var2 + "," + (int)var3);
            return;
         }

         VirtualZombieManager.instance.choices.clear();
    IsoGridSquare var8 = nullptr;
         if (!this.isCrawling(var6) && !this.isFakeDead(var6) && Rand.Next(3) == 0) {
            var8 = this.getSquareForSittingZombie(var1, var2, (int)var3);
         }

         if (var8 != nullptr) {
            VirtualZombieManager.instance.choices.push_back(var8);
         } else {
            VirtualZombieManager.instance.choices.push_back(var7);
         }

    IsoZombie var9 = VirtualZombieManager.instance.createRealZombieAlways(var5, var4.index(), false);
         if (var9 != nullptr) {
            if (var8 != nullptr) {
               this.sitAgainstWall(var9, var8);
            } else {
               var9.setX(var1);
               var9.setY(var2);
            }

            if (this.isFakeDead(var6)) {
               var9.setHealth(0.5F + Rand.Next(0.0F, 0.3F));
               var9.sprite = var9.legsSprite;
               var9.setFakeDead(true);
            } else if (this.isCrawling(var6)) {
               var9.setCrawler(true);
               var9.setCanWalk(this.isCanWalk(var6));
               var9.setOnFloor(true);
               var9.setFallOnFront(true);
               var9.walkVariant = "ZombieWalk";
               var9.DoZombieStats();
            }

            if (this.isInitialized(var6)) {
               var9.setCanCrawlUnderVehicle(this.isCanCrawlUnderVehicle(var6));
            } else {
               this.firstTimeLoaded(var9, var6);
            }
         }
      } else {
         noise("real -> unloaded");
         n_addZombie(var1, var2, var3, (byte)var4.index(), var5, var6, -1, -1);
      }
   }

    IsoGridSquare getSquareForSittingZombie(float var1, float var2, int var3) {
    uint8_t var4 = 3;

      for (int var5 = -var4; var5 < var4; var5++) {
         for (int var6 = -var4; var6 < var4; var6++) {
    IsoGridSquare var7 = IsoWorld.instance.CurrentCell.getGridSquare((int)var1 + var5, (int)var2 + var6, var3);
            if (var7 != nullptr && var7.isFree(true) && var7.getBuilding() == nullptr) {
    int var8 = var7.getWallType();
               if (var8 != 0 && !PolygonalMap2.instance.lineClearCollide(var1, var2, var7.x + 0.5F, var7.y + 0.5F, var7.z, nullptr, false, true)) {
    return var7;
               }
            }
         }
      }

    return nullptr;
   }

    void sitAgainstWall(IsoZombie var1, IsoGridSquare var2) {
    float var3 = var2.x + 0.5F;
    float var4 = var2.y + 0.5F;
      var1.setX(var3);
      var1.setY(var4);
      var1.setSitAgainstWall(true);
    int var5 = var2.getWallType();
      if (var5 != 0) {
         this.m_sittingDirections.clear();
         if ((var5 & 1) != 0 && (var5 & 4) != 0) {
            this.m_sittingDirections.push_back(IsoDirections.SE);
         }

         if ((var5 & 1) != 0 && (var5 & 8) != 0) {
            this.m_sittingDirections.push_back(IsoDirections.SW);
         }

         if ((var5 & 2) != 0 && (var5 & 4) != 0) {
            this.m_sittingDirections.push_back(IsoDirections.NE);
         }

         if ((var5 & 2) != 0 && (var5 & 8) != 0) {
            this.m_sittingDirections.push_back(IsoDirections.NW);
         }

         if ((var5 & 1) != 0) {
            this.m_sittingDirections.push_back(IsoDirections.S);
         }

         if ((var5 & 2) != 0) {
            this.m_sittingDirections.push_back(IsoDirections.N);
         }

         if ((var5 & 4) != 0) {
            this.m_sittingDirections.push_back(IsoDirections.E);
         }

         if ((var5 & 8) != 0) {
            this.m_sittingDirections.push_back(IsoDirections.W);
         }

    IsoDirections var6 = (IsoDirections)PZArrayUtil.pickRandom(this.m_sittingDirections);
         if (GameClient.bClient) {
    int var7 = (var2.x & 1) + (var2.y & 1);
            var6 = this.m_sittingDirections.get(var7 % this.m_sittingDirections.size());
         }

         var1.setDir(var6);
         var1.setForwardDirection(var6.ToVector());
         if (var1.getAnimationPlayer() != nullptr) {
            var1.getAnimationPlayer().SetForceDir(var1.getForwardDirection());
         }
      }
   }

    void addZombieMoving(float var1, float var2, float var3, IsoDirections var4, int var5, int var6, int var7, int var8) {
    IsoGridSquare var9 = IsoWorld.instance.CurrentCell.getGridSquare((int)var1, (int)var2, (int)var3);
      if (var9 != nullptr && (var9.SolidFloorCached ? var9.SolidFloor : var9.TreatAsSolidFloor())) {
         if (!Core.bLastStand && !this.playerSpawns.allowZombie(var9)) {
            noise("removed zombie near player spawn " + (int)var1 + "," + (int)var2 + "," + (int)var3);
            return;
         }

         VirtualZombieManager.instance.choices.clear();
         VirtualZombieManager.instance.choices.push_back(var9);
    IsoZombie var10 = VirtualZombieManager.instance.createRealZombieAlways(var5, var4.index(), false);
         if (var10 != nullptr) {
            var10.setX(var1);
            var10.setY(var2);
            if (this.isCrawling(var6)) {
               var10.setCrawler(true);
               var10.setCanWalk(this.isCanWalk(var6));
               var10.setOnFloor(true);
               var10.setFallOnFront(true);
               var10.walkVariant = "ZombieWalk";
               var10.DoZombieStats();
            }

            if (this.isInitialized(var6)) {
               var10.setCanCrawlUnderVehicle(this.isCanCrawlUnderVehicle(var6));
            } else {
               this.firstTimeLoaded(var10, var6);
            }

            if (Math.abs(var7 - var1) > 1.0F || Math.abs(var8 - var2) > 1.0F) {
               var10.AllowRepathDelay = -1.0F;
               var10.pathToLocation(var7, var8, 0);
            }
         }
      } else {
         noise("real -> virtual " + var1 + "," + var2);
         n_addZombie(var1, var2, var3, (byte)var4.index(), var5, var6, var7, var8);
      }
   }

    bool isInitialized(int var1) {
      return (var1 & 1) != 0;
   }

    bool isCrawling(int var1) {
      return (var1 & 2) != 0;
   }

    bool isCanWalk(int var1) {
      return (var1 & 4) != 0;
   }

    bool isFakeDead(int var1) {
      return (var1 & 8) != 0;
   }

    bool isCanCrawlUnderVehicle(int var1) {
      return (var1 & 16) != 0;
   }

    void firstTimeLoaded(IsoZombie var1, int var2) {
   }

    void updateThread() {
      n_updateThread();
   }

    bool shouldWait() {
      /* synchronized - TODO: add std::mutex */ (MapCollisionData.instance.renderLock) {
    return n_shouldWait();
      }
   }

    void updateLoadedAreas() {
      if (this.loadedAreas.set()) {
         n_loadedAreas(this.loadedAreas.count, this.loadedAreas.areas, false);
      }

      if (GameServer.bServer && this.loadedServerCells.set()) {
         n_loadedAreas(this.loadedServerCells.count, this.loadedServerCells.areas, true);
      }
   }

    void dbgSpawnTimeToZero(int var1, int var2) {
      if (!this.bClient || GameClient.connection.accessLevel == 32) {
         this.dbgCommands.SpawnTimeToZero(var1, var2);
      }
   }

    void dbgClearZombies(int var1, int var2) {
      if (!this.bClient || GameClient.connection.accessLevel == 32) {
         this.dbgCommands.ClearZombies(var1, var2);
      }
   }

    void dbgSpawnNow(int var1, int var2) {
      if (!this.bClient || GameClient.connection.accessLevel == 32) {
         this.dbgCommands.SpawnNow(var1, var2);
      }
   }

    void beginSaveRealZombies() {
      if (!this.bClient) {
         this.saveRealZombieHack.clear();

         for (IsoZombie var3 : IsoWorld.instance.CurrentCell.getZombieList()) {
            if (!var3.isReanimatedPlayer() && (!GameServer.bServer || !var3.bIndoorZombie)) {
               this.saveRealZombieHack.push_back(var3);
            }
         }

    int var9 = this.saveRealZombieHack.size();
         n_beginSaveRealZombies(var9);
    int var10 = 0;

         while (var10 < var9) {
            this.byteBuffer.clear();
    int var4 = 0;

            while (var10 < var9) {
    int var5 = this.byteBuffer.position();
    IsoZombie var6 = this.saveRealZombieHack.get(var10++);
               this.byteBuffer.putFloat(var6.x);
               this.byteBuffer.putFloat(var6.y);
               this.byteBuffer.putFloat(var6.z);
               this.byteBuffer.put((byte)var6.dir.index());
               this.byteBuffer.putInt(var6.getPersistentOutfitID());
    int var7 = this.getZombieState(var6);
               this.byteBuffer.putInt(var7);
               var4++;
    int var8 = this.byteBuffer.position() - var5;
               if (this.byteBuffer.position() + var8 > this.byteBuffer.capacity()) {
                  break;
               }
            }

            n_saveRealZombies(var4, this.byteBuffer);
         }

         this.saveRealZombieHack.clear();
      }
   }

    void endSaveRealZombies() {
      if (!this.bClient) {
         ;
      }
   }

    void save() {
      if (!this.bClient) {
         n_save();
      }
   }

    void stop() {
      if (!this.bClient) {
         this.bStopped = true;
         n_stop();
         this.loadedAreas.clear();
         this.newChunks.clear();
         this.spawnOrigins.clear();
         this.radarXY = nullptr;
         this.radarCount = 0;
         this.radarRenderFlag = false;
         this.radarRequestFlag = false;
      }
   }
}
} // namespace popman
} // namespace zombie
