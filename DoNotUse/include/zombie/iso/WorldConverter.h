#pragma once
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/erosion/ErosionRegions.h"
#include "zombie/erosion/season/ErosionIceQueen.h"
#include "zombie/gameStates/GameLoadingState.h"
#include "zombie/gameStates/IngameState.h"
#include "zombie/globalObjects/GlobalObjectLookup.h"
#include "zombie/iso/IsoChunk/JobType.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/CoopSlave.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/vehicles/VehicleManager.h"
#include "zombie/world/WorldDictionary.h"
#include "zombie/world/WorldDictionaryException.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {


class WorldConverter {
public:
    static const WorldConverter instance = std::make_shared<WorldConverter>();
    static bool converting;
   public std::unordered_map<int, int> TilesetConversions = nullptr;
    int oldID = 0;

    void convert(const std::string& var1, IsoSpriteManager var2) {
    File var3 = std::make_shared<File>(ZomboidFileSystem.instance.getGameModeCacheDir() + File.separator + var1 + File.separator + "map_ver.bin");
      if (var3.exists()) {
         converting = true;
    FileInputStream var4 = std::make_shared<FileInputStream>(var3);
    DataInputStream var5 = std::make_shared<DataInputStream>(var4);
    int var6 = var5.readInt();
         var5.close();
         if (var6 < 195) {
            if (var6 < 24) {
               GameLoadingState.build23Stop = true;
               return;
            }

            try {
               this.convert(var1, var6, 195);
            } catch (Exception var8) {
               IngameState.createWorld(var1);
               IngameState.copyWorld(var1 + "_backup", var1);
               var8.printStackTrace();
            }
         }

         converting = false;
      }
   }

    void convert(const std::string& var1, int var2, int var3) {
      if (!GameClient.bClient) {
         GameLoadingState.convertingWorld = true;
    std::string var4 = Core.GameSaveWorld;
         IngameState.createWorld(var1 + "_backup");
         IngameState.copyWorld(var1, Core.GameSaveWorld);
         Core.GameSaveWorld = var4;
         if (var3 >= 14 && var2 < 14) {
            try {
               this.convertchunks(var1, 25, 25);
            } catch (IOException var8) {
               var8.printStackTrace();
            }
         } else if (var2 == 7) {
            try {
               this.convertchunks(var1);
            } catch (IOException var7) {
               var7.printStackTrace();
            }
         }

         if (var2 <= 4) {
            this.loadconversionmap(var2, "tiledefinitions");
            this.loadconversionmap(var2, "newtiledefinitions");

            try {
               this.convertchunks(var1);
            } catch (IOException var6) {
               var6.printStackTrace();
            }
         }

         GameLoadingState.convertingWorld = false;
      }
   }

    void convertchunks(const std::string& var1) {
    IsoCell var2 = std::make_shared<IsoCell>(300, 300);
    IsoChunkMap var3 = std::make_shared<IsoChunkMap>(var2);
    File var4 = std::make_shared<File>(ZomboidFileSystem.instance.getGameModeCacheDir() + File.separator + var1 + File.separator);
      if (!var4.exists()) {
         var4.mkdir();
      }

      std::string[] var5 = var4.list();

    for (auto& var9 : var5)         if (var9.contains(".bin")
            && !var9 == "map.bin")
            && !var9 == "map_p.bin")
            && !var9.matches("map_p[0-9]+\\.bin")
            && !var9 == "map_t.bin")
            && !var9 == "map_c.bin")
            && !var9 == "map_ver.bin")
            && !var9 == "map_sand.bin")
            && !var9 == "map_mov.bin")
            && !var9 == "map_meta.bin")
            && !var9 == "map_cm.bin")
            && !var9 == "pc.bin")
            && !var9.startsWith("zpop_")
            && !var9.startsWith("chunkdata_")) {
            std::string[] var10 = var9.replace(".bin", "").replace("map_", "").split("_");
    int var11 = int.parseInt(var10[0]);
    int var12 = int.parseInt(var10[1]);
            var3.LoadChunkForLater(var11, var12, 0, 0);
            var3.SwapChunkBuffers();
            var3.getChunk(0, 0).Save(true);
         }
      }
   }

    void convertchunks(const std::string& var1, int var2, int var3) {
    IsoCell var4 = std::make_shared<IsoCell>(300, 300);
    std::make_shared<IsoChunkMap>();
    File var6 = std::make_shared<File>(ZomboidFileSystem.instance.getGameModeCacheDir() + File.separator + var1 + File.separator);
      if (!var6.exists()) {
         var6.mkdir();
      }

      std::string[] var7 = var6.list();
      IsoWorld.saveoffsetx = var2;
      IsoWorld.saveoffsety = var3;
      IsoWorld.instance.MetaGrid.Create();
      WorldStreamer.instance.create();

    for (auto& var11 : var7)         if (var11.contains(".bin")
            && !var11 == "map.bin")
            && !var11 == "map_p.bin")
            && !var11.matches("map_p[0-9]+\\.bin")
            && !var11 == "map_t.bin")
            && !var11 == "map_c.bin")
            && !var11 == "map_ver.bin")
            && !var11 == "map_sand.bin")
            && !var11 == "map_mov.bin")
            && !var11 == "map_meta.bin")
            && !var11 == "map_cm.bin")
            && !var11 == "pc.bin")
            && !var11.startsWith("zpop_")
            && !var11.startsWith("chunkdata_")) {
            std::string[] var12 = var11.replace(".bin", "").replace("map_", "").split("_");
    int var13 = int.parseInt(var12[0]);
    int var14 = int.parseInt(var12[1]);
    IsoChunk var15 = std::make_shared<IsoChunk>(var4);
            var15.refs.push_back(var4.ChunkMap[0]);
            WorldStreamer.instance.addJobConvert(var15, 0, 0, var13, var14);

            while (!var15.bLoaded) {
               try {
                  Thread.sleep(20L);
               } catch (InterruptedException var18) {
                  var18.printStackTrace();
               }
            }

            var15.wx += var2 * 30;
            var15.wy += var3 * 30;
            var15.jobType = JobType.Convert;
            var15.Save(true);
    File var16 = std::make_shared<File>(ZomboidFileSystem.instance.getGameModeCacheDir() + File.separator + var1 + File.separator + var11);

            while (!ChunkSaveWorker.instance.toSaveQueue.empty()) {
               try {
                  Thread.sleep(13L);
               } catch (InterruptedException var19) {
                  var19.printStackTrace();
               }
            }

            var16.delete();
         }
      }
   }

    void loadconversionmap(int var1, const std::string& var2) {
    std::string var3 = "media/" + var2 + "_" + var1 + ".tiles";
    File var4 = std::make_shared<File>(var3);
      if (var4.exists()) {
         try {
    RandomAccessFile var5 = std::make_shared<RandomAccessFile>(var4.getAbsolutePath(), "r");
    int var6 = IsoWorld.readInt(var5);

            for (int var7 = 0; var7 < var6; var7++) {
               Thread.sleep(4L);
    std::string var8 = IsoWorld.readString(var5);
    std::string var9 = var8.trim();
               IsoWorld.readString(var5);
    int var10 = IsoWorld.readInt(var5);
    int var11 = IsoWorld.readInt(var5);
    int var12 = IsoWorld.readInt(var5);

               for (int var13 = 0; var13 < var12; var13++) {
    IsoSprite var14 = (IsoSprite)IsoSpriteManager.instance.NamedMap.get(var9 + "_" + var13);
                  if (this.TilesetConversions == nullptr) {
                     this.TilesetConversions = std::make_unique<std::unordered_map<>>();
                  }

                  this.TilesetConversions.put(this.oldID, var14.ID);
                  this.oldID++;
    int var15 = IsoWorld.readInt(var5);

                  for (int var16 = 0; var16 < var15; var16++) {
                     var8 = IsoWorld.readString(var5);
    std::string var17 = var8.trim();
                     var8 = IsoWorld.readString(var5);
    std::string var18 = var8.trim();
                  }
               }
            }
         } catch (Exception var19) {
         }
      }
   }

    void softreset() {
    std::string var1 = GameServer.ServerName;
      Core.GameSaveWorld = var1;
    IsoCell var2 = std::make_shared<IsoCell>(300, 300);
    IsoChunk var3 = std::make_shared<IsoChunk>(var2);
    File var4 = std::make_shared<File>(ZomboidFileSystem.instance.getGameModeCacheDir() + File.separator + var1 + File.separator);
      if (!var4.exists()) {
         var4.mkdir();
      }

      std::string[] var5 = var4.list();
      if (CoopSlave.instance != nullptr) {
         CoopSlave.instance.sendMessage("softreset-count", nullptr, int.toString(var5.length));
      }

      IsoWorld.instance.MetaGrid.Create();
      ServerMap.instance.init(IsoWorld.instance.MetaGrid);
    std::make_shared<ErosionIceQueen>();
      ErosionRegions.init();
      WorldStreamer.instance.create();
      VehicleManager.instance = std::make_unique<VehicleManager>();
      WorldDictionary.init();
      GlobalObjectLookup.init(IsoWorld.instance.getMetaGrid());
      LuaEventManager.triggerEvent("OnSGlobalObjectSystemInit");
    int var6 = var5.length;
      DebugLog.log("processing " + var6 + " files");

    for (auto& var10 : var5)         var6--;
         if (var10.startsWith("zpop_")) {
            deleteFile(var10);
         } else if (var10 == "map_t.bin")) {
            deleteFile(var10);
         } else if (var10 == "map_meta.bin") || var10 == "map_zone.bin")) {
            deleteFile(var10);
         } else if (var10 == "reanimated.bin")) {
            deleteFile(var10);
         } else if (var10.matches("map_[0-9]+_[0-9]+\\.bin")) {
            System.out.println("Soft clearing chunk: " + var10);
            std::string[] var11 = var10.replace(".bin", "").replace("map_", "").split("_");
    int var12 = int.parseInt(var11[0]);
    int var13 = int.parseInt(var11[1]);
            var3.refs.push_back(var2.ChunkMap[0]);
            var3.wx = var12;
            var3.wy = var13;
            ServerMap.instance.setSoftResetChunk(var3);
            WorldStreamer.instance.addJobWipe(var3, 0, 0, var12, var13);

            while (!var3.bLoaded) {
               try {
                  Thread.sleep(20L);
               } catch (InterruptedException var16) {
                  var16.printStackTrace();
               }
            }

            var3.jobType = JobType.Convert;
            var3.FloorBloodSplats.clear();

            try {
               var3.Save(true);
            } catch (Exception var15) {
               var15.printStackTrace();
            }

            ServerMap.instance.clearSoftResetChunk(var3);
            var3.doReuseGridsquares();
            IsoChunkMap.chunkStore.remove(var3);
            if (var6 % 100 == 0) {
               DebugLog.log(var6 + " files to go");
            }

            if (CoopSlave.instance != nullptr && var6 % 10 == 0) {
               CoopSlave.instance.sendMessage("softreset-remaining", nullptr, int.toString(var6));
            }
         }
      }

      GameServer.ResetID = Rand.Next(10000000);
      ServerOptions.instance.putSaveOption("ResetID", std::string.valueOf(GameServer.ResetID));
      IsoWorld.instance.CurrentCell = nullptr;
      DebugLog.log("soft-reset complete, server terminated");
      if (CoopSlave.instance != nullptr) {
         CoopSlave.instance.sendMessage("softreset-finished", nullptr, "");
      }

      SteamUtils.shutdown();
      System.exit(0);
   }

    static void deleteFile(const std::string& var0) {
    File var1 = std::make_shared<File>(ZomboidFileSystem.instance.getGameModeCacheDir() + File.separator + GameServer.ServerName + File.separator + var0);
      var1.delete();
   }
}
} // namespace iso
} // namespace zombie
