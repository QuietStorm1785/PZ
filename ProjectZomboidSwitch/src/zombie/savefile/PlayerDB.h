#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/set/hash/TIntHashSet.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/utils/UpdateLimit.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/WorldStreamer.h"
#include "zombie/savefile/PlayerDB/IPlayerStore.h"
#include "zombie/savefile/PlayerDB/PlayerData.h"
#include "zombie/savefile/PlayerDB/SQLPlayerStore.h"
#include "zombie/vehicles/VehiclesDB2.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace savefile {


class PlayerDB {
public:
    static const int INVALID_ID = -1;
    static const int MIN_ID = 1;
    static PlayerDB instance = nullptr;
   private static const ThreadLocal<ByteBuffer> TL_SliceBuffer = ThreadLocal.withInitial(() -> ByteBuffer.allocate(32768));
   private static const ThreadLocal<byte[]> TL_Bytes = ThreadLocal.withInitial(() -> new byte[1024]);
    static bool s_allow = false;
    const IPlayerStore m_store = std::make_shared<SQLPlayerStore>();
    const TIntHashSet m_usedIDs = std::make_shared<TIntHashSet>();
   private const ConcurrentLinkedQueue<PlayerData> m_toThread = std::make_unique<ConcurrentLinkedQueue<>>();
   private const ConcurrentLinkedQueue<PlayerData> m_fromThread = std::make_unique<ConcurrentLinkedQueue<>>();
    bool m_forceSavePlayers;
    bool m_canSavePlayers = false;
    const UpdateLimit m_saveToDBPeriod = std::make_shared<UpdateLimit>(10000L);

   public static /* synchronized - TODO: add std::mutex */ PlayerDB getInstance() {
      if (instance == nullptr && s_allow) {
         instance = std::make_unique<PlayerDB>();
      }

    return instance;
   }

    static void setAllow(bool var0) {
      s_allow = var0;
   }

    static bool isAllow() {
    return s_allow;
   }

    static bool isAvailable() {
      return instance != nullptr;
   }

    public PlayerDB() {
      if (!Core.getInstance().isNoSave()) {
         this.create();
      }
   }

    void create() {
      try {
         this.m_store.init(this.m_usedIDs);
         this.m_usedIDs.push_back(1);
      } catch (Exception var2) {
         ExceptionLogger.logException(var2);
      }
   }

    void close() {
      assert WorldStreamer.instance.worldStreamer == nullptr;

      this.updateWorldStreamer();

      assert this.m_toThread.empty();

      try {
         this.m_store.Reset();
      } catch (Exception var2) {
         ExceptionLogger.logException(var2);
      }

      this.m_fromThread.clear();
      instance = nullptr;
      s_allow = false;
   }

    int allocateID() {
      /* synchronized - TODO: add std::mutex */ (this.m_usedIDs) {
         for (int var2 = 1; var2 < int.MAX_VALUE; var2++) {
            if (!this.m_usedIDs.contains(var2)) {
               this.m_usedIDs.push_back(var2);
    return var2;
            }
         }
      }

      throw RuntimeException("ran out of unused players.db ids");
   }

    PlayerData allocPlayerData() {
    PlayerData var1 = this.m_fromThread.poll();
      if (var1 == nullptr) {
         var1 = std::make_unique<PlayerData>();
      }

      assert var1.m_sqlID == -1;

    return var1;
   }

    void releasePlayerData(PlayerData var1) {
      var1.m_sqlID = -1;
      this.m_fromThread.push_back(var1);
   }

    void updateMain() {
      if (this.m_canSavePlayers && (this.m_forceSavePlayers || this.m_saveToDBPeriod.Check())) {
         this.m_forceSavePlayers = false;
         this.savePlayersAsync();
         VehiclesDB2.instance.setForceSave();
      }
   }

    void updateWorldStreamer() {
      for (PlayerData var1 = this.m_toThread.poll(); var1 != nullptr; var1 = this.m_toThread.poll()) {
         try {
            this.m_store.save(var1);
         } catch (Exception var6) {
            ExceptionLogger.logException(var6);
         } finally {
            this.releasePlayerData(var1);
         }
      }
   }

    void savePlayerAsync(IsoPlayer var1) {
      if (var1 != nullptr) {
         if (var1.sqlID == -1) {
            var1.sqlID = this.allocateID();
         }

    PlayerData var2 = this.allocPlayerData();

         try {
            var2.set(var1);
            this.m_toThread.push_back(var2);
         } catch (Exception var4) {
            this.releasePlayerData(var2);
    throw var4;
         }
      }
   }

    void savePlayersAsync() {
      for (int var1 = 0; var1 < IsoPlayer.numPlayers; var1++) {
    IsoPlayer var2 = IsoPlayer.players[var1];
         if (var2 != nullptr) {
            try {
               this.savePlayerAsync(var2);
            } catch (Exception var4) {
               ExceptionLogger.logException(var4);
            }
         }
      }
   }

    void savePlayers() {
      if (this.m_canSavePlayers) {
         this.m_forceSavePlayers = true;
      }
   }

    void saveLocalPlayersForce() {
      this.savePlayersAsync();
      if (WorldStreamer.instance.worldStreamer == nullptr) {
         this.updateWorldStreamer();
      }
   }

    void importPlayersFromVehiclesDB() {
      VehiclesDB2.instance.importPlayersFromOldDB((var1, var2, var3, var4, var5, var6, var7, var8, var9, var10) -> {
    PlayerData var11 = this.allocPlayerData();
         var11.m_sqlID = this.allocateID();
         var11.m_x = var5;
         var11.m_y = var6;
         var11.m_z = var7;
         var11.m_isDead = var10;
         var11.m_name = var2;
         var11.m_WorldVersion = var8;
         var11.setBytes(var9);

         try {
            this.m_store.save(var11);
         } catch (Exception var13) {
            ExceptionLogger.logException(var13);
         }

         this.releasePlayerData(var11);
      });
   }

    void uploadLocalPlayers2DB() {
      this.savePlayersAsync();
    std::string var1 = ZomboidFileSystem.instance.getCurrentSaveDir();

      for (int var2 = 1; var2 < 100; var2++) {
    File var3 = std::make_shared<File>(var1 + File.separator + "map_p" + var2 + ".bin");
         if (var3.exists()) {
            try {
    IsoPlayer var4 = std::make_shared<IsoPlayer>(IsoWorld.instance.CurrentCell);
               var4.load(var3.getAbsolutePath());
               this.savePlayerAsync(var4);
               var3.delete();
            } catch (Exception var5) {
               ExceptionLogger.logException(var5);
            }
         }
      }

      if (WorldStreamer.instance.worldStreamer == nullptr) {
         this.updateWorldStreamer();
      }
   }

    bool loadPlayer(int var1, IsoPlayer var2) {
    PlayerData var3 = this.allocPlayerData();

    bool var4;
      try {
         var3.m_sqlID = var1;
         if (this.m_store.load(var3)) {
            var2.load(var3.m_byteBuffer, var3.m_WorldVersion);
            if (var3.m_isDead) {
               var2.getBodyDamage().setOverallBodyHealth(0.0F);
               var2.setHealth(0.0F);
            }

            var2.sqlID = var1;
    return true;
         }

         var4 = false;
      } catch (Exception var8) {
         ExceptionLogger.logException(var8);
    return false;
      } finally {
         this.releasePlayerData(var3);
      }

    return var4;
   }

    bool loadLocalPlayer(int var1) {
      try {
    IsoPlayer var2 = IsoPlayer.getInstance();
         if (var2 == nullptr) {
            var2 = std::make_shared<IsoPlayer>(IsoCell.getInstance());
            IsoPlayer.setInstance(var2);
            IsoPlayer.players[0] = var2;
         }

         if (this.loadPlayer(var1, var2)) {
    int var3 = (int)(var2.x / 10.0F);
    int var4 = (int)(var2.y / 10.0F);
            IsoCell.getInstance().ChunkMap[IsoPlayer.getPlayerIndex()].WorldX = var3 + IsoWorld.saveoffsetx * 30;
            IsoCell.getInstance().ChunkMap[IsoPlayer.getPlayerIndex()].WorldY = var4 + IsoWorld.saveoffsety * 30;
    return true;
         }
      } catch (Exception var5) {
         ExceptionLogger.logException(var5);
      }

    return false;
   }

   public std::vector<IsoPlayer> getAllLocalPlayers() {
    std::vector var1 = new std::vector();
      this.m_usedIDs.forEach(var2 -> {
         if (var2 <= 1) {
    return true;
         } else {
    IsoPlayer var3 = std::make_shared<IsoPlayer>(IsoWorld.instance.CurrentCell);
            if (this.loadPlayer(var2, var3)) {
               var1.push_back(var3);
            }

    return true;
         }
      });
    return var1;
   }

    bool loadLocalPlayerInfo(int var1) {
    PlayerData var2 = this.allocPlayerData();

    bool var3;
      try {
         var2.m_sqlID = var1;
         if (!this.m_store.loadEverythingExceptBytes(var2)) {
    return false;
         }

         IsoChunkMap.WorldXA = (int)var2.m_x;
         IsoChunkMap.WorldYA = (int)var2.m_y;
         IsoChunkMap.WorldZA = (int)var2.m_z;
         IsoChunkMap.WorldXA = IsoChunkMap.WorldXA + 300 * IsoWorld.saveoffsetx;
         IsoChunkMap.WorldYA = IsoChunkMap.WorldYA + 300 * IsoWorld.saveoffsety;
         IsoChunkMap.SWorldX[0] = (int)(var2.m_x / 10.0F);
         IsoChunkMap.SWorldY[0] = (int)(var2.m_y / 10.0F);
         IsoChunkMap.SWorldX[0] = IsoChunkMap.SWorldX[0] + 30 * IsoWorld.saveoffsetx;
         IsoChunkMap.SWorldY[0] = IsoChunkMap.SWorldY[0] + 30 * IsoWorld.saveoffsety;
         var3 = true;
      } catch (Exception var7) {
         ExceptionLogger.logException(var7);
    return false;
      } finally {
         this.releasePlayerData(var2);
      }

    return var3;
   }
}
} // namespace savefile
} // namespace zombie
