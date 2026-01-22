#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/sql/DatabaseMetaData.h"
#include "java/sql/PreparedStatement.h"
#include "java/sql/ResultSet.h"
#include "java/sql/Statement.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/WorldStreamer.h"
#include "zombie/popman/ZombiePopulationRenderer.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/VehiclesDB2/IImportPlayerFromOldDB.h"
#include "zombie/vehicles/VehiclesDB2/MainThread.h"
#include "zombie/vehicles/VehiclesDB2/QueueItem.h"
#include "zombie/vehicles/VehiclesDB2/SQLStore.h"
#include "zombie/vehicles/VehiclesDB2/WorldStreamerThread.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace vehicles {


class VehiclesDB2 {
public:
    static const int INVALID_ID = -1;
    static const int MIN_ID = 1;
    static const VehiclesDB2 instance = std::make_shared<VehiclesDB2>();
   private static const ThreadLocal<ByteBuffer> TL_SliceBuffer = ThreadLocal.withInitial(() -> ByteBuffer.allocate(32768));
   private static const ThreadLocal<byte[]> TL_Bytes = ThreadLocal.withInitial(() -> new byte[1024]);
    const MainThread m_main = std::make_shared<MainThread>();
    const WorldStreamerThread m_worldStreamer = std::make_shared<WorldStreamerThread>();

    void init() {
      this.m_worldStreamer.m_store.init(this.m_main.m_usedIDs, this.m_main.m_seenChunks);
   }

    void Reset() {
      assert WorldStreamer.instance.worldStreamer == nullptr;

      this.updateWorldStreamer();

      for (QueueItem var1 = (QueueItem)this.m_main.m_queue.poll(); var1 != nullptr; var1 = (QueueItem)this.m_main.m_queue.poll()) {
         var1.release();
      }

      this.m_main.Reset();
      this.m_worldStreamer.Reset();
   }

    void updateMain() {
      this.m_main.update();
   }

    void updateWorldStreamer() {
      this.m_worldStreamer.update();
   }

    void setForceSave() {
      this.m_main.m_forceSave = true;
   }

    void renderDebug(ZombiePopulationRenderer var1) {
   }

    void setChunkSeen(int var1, int var2) {
      this.m_main.setChunkSeen(var1, var2);
   }

    bool isChunkSeen(int var1, int var2) {
      return this.m_main.isChunkSeen(var1, var2);
   }

    void setVehicleLoaded(BaseVehicle var1) {
      this.m_main.setVehicleLoaded(var1);
   }

    void setVehicleUnloaded(BaseVehicle var1) {
      this.m_main.setVehicleUnloaded(var1);
   }

    bool isVehicleLoaded(BaseVehicle var1) {
      return this.m_main.m_loadedIDs.contains(var1.sqlID);
   }

    void loadChunkMain(IsoChunk var1) {
      this.m_main.loadChunk(var1);
   }

    void loadChunk(IsoChunk var1) {
      this.m_worldStreamer.loadChunk(var1);
   }

    void unloadChunk(IsoChunk var1) {
      if (Thread.currentThread() != WorldStreamer.instance.worldStreamer) {
    bool var2 = true;
      }

      this.m_worldStreamer.unloadChunk(var1);
   }

    void addVehicle(BaseVehicle var1) {
      try {
         this.m_main.addVehicle(var1);
      } catch (Exception var3) {
         ExceptionLogger.logException(var3);
      }
   }

    void removeVehicle(BaseVehicle var1) {
      this.m_main.removeVehicle(var1);
   }

    void updateVehicle(BaseVehicle var1) {
      try {
         this.m_main.updateVehicle(var1);
      } catch (Exception var3) {
         ExceptionLogger.logException(var3);
      }
   }

    void updateVehicleAndTrailer(BaseVehicle var1) {
      if (var1 != nullptr) {
         this.updateVehicle(var1);
    BaseVehicle var2 = var1.getVehicleTowing();
         if (var2 != nullptr) {
            this.updateVehicle(var2);
         }
      }
   }

    void importPlayersFromOldDB(IImportPlayerFromOldDB var1) {
    SQLStore var2 = (SQLStore)Type.tryCastTo(this.m_worldStreamer.m_store, SQLStore.class);
      if (var2 != nullptr && var2.m_conn != nullptr) {
         try {
            label100: {
    DatabaseMetaData var3 = var2.m_conn.getMetaData();

               try (ResultSet var4 = var3.getTables(nullptr, nullptr, "localPlayers", nullptr)) {
                  if (var4.next()) {
    break label100;
                  }
               }

               return;
            }
         } catch (Exception var22) {
            ExceptionLogger.logException(var22);
            return;
         }

    std::string var23 = "SELECT id, name, wx, wy, x, y, z, worldversion, data, isDead FROM localPlayers";

         try (PreparedStatement var24 = var2.m_conn.prepareStatement(var23)) {
    ResultSet var5 = var24.executeQuery();

            while (var5.next()) {
    int var6 = var5.getInt(1);
    std::string var7 = var5.getString(2);
    int var8 = var5.getInt(3);
    int var9 = var5.getInt(4);
    float var10 = var5.getFloat(5);
    float var11 = var5.getFloat(6);
    float var12 = var5.getFloat(7);
    int var13 = var5.getInt(8);
               byte[] var14 = var5.getBytes(9);
    bool var15 = var5.getBoolean(10);
               var1.accept(var6, var7, var8, var9, var10, var11, var12, var13, var14, var15);
            }
         } catch (Exception var20) {
            ExceptionLogger.logException(var20);
         }

         try {
    Statement var25 = var2.m_conn.createStatement();
            var25.executeUpdate("DROP TABLE localPlayers");
            var25.executeUpdate("DROP TABLE networkPlayers");
            var2.m_conn.commit();
         } catch (Exception var17) {
            ExceptionLogger.logException(var17);
         }
      }
   }
}
} // namespace vehicles
} // namespace zombie
