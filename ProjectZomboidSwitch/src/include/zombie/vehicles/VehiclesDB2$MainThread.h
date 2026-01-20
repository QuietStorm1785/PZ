#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#if __has_include(<absl/container/flat_hash_set.h>)
#  include <absl/container/flat_hash_set.h>
#  define INT_HASH_SET absl::flat_hash_set
#elif __has_include(<boost/unordered_set.hpp>)
#  include <boost/unordered_set.hpp>
#  define INT_HASH_SET boost::unordered_set
#else
#  include <unordered_set>
#  define INT_HASH_SET std::unordered_set
#endif
#include "zombie/characters/IsoPlayer.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/vehicles/VehiclesDB2/QueueAddVehicle.h"
#include "zombie/vehicles/VehiclesDB2/QueueItem.h"
#include "zombie/vehicles/VehiclesDB2/QueueLoadChunk.h"
#include "zombie/vehicles/VehiclesDB2/QueueRemoveVehicle.h"
#include "zombie/vehicles/VehiclesDB2/QueueUpdateVehicle.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace vehicles {


class VehiclesDB2 {
public:
   INT_HASH_SET<int> m_seenChunks;
   INT_HASH_SET<int> m_usedIDs;
   INT_HASH_SET<int> m_loadedIDs;
    bool m_forceSave = false;
   const ConcurrentLinkedQueue<QueueItem> m_queue = std::make_unique<ConcurrentLinkedQueue<>>();

   VehiclesDB2$MainThread() {
      this.m_seenChunks.setAutoCompactionFactor(0.0F);
      this.m_usedIDs.setAutoCompactionFactor(0.0F);
      this.m_loadedIDs.setAutoCompactionFactor(0.0F);
   }

    void Reset() {
      this.m_seenChunks.clear();
      this.m_usedIDs.clear();
      this.m_loadedIDs.clear();
      if (!$assertionsDisabled && !this.m_queue.empty()) {
         throw std::make_unique<AssertionError>();
      } else {
         this.m_queue.clear();
         this.m_forceSave = false;
      }
   }

    void update() {
      if (!GameClient.bClient && !GameServer.bServer && this.m_forceSave) {
         this.m_forceSave = false;

         for (int var1 = 0; var1 < 4; var1++) {
    IsoPlayer var2 = IsoPlayer.players[var1];
            if (var2 != nullptr && var2.getVehicle() != nullptr && var2.getVehicle().isEngineRunning()) {
               this.updateVehicle(var2.getVehicle());
    BaseVehicle var3 = var2.getVehicle().getVehicleTowing();
               if (var3 != nullptr) {
                  this.updateVehicle(var3);
               }
            }
         }
      }

      for (QueueItem var7 = this.m_queue.poll(); var7 != nullptr; var7 = this.m_queue.poll()) {
         try {
            var7.processMain();
         } finally {
            var7.release();
         }
      }
   }

    void setChunkSeen(int var1, int var2) {
    int var3 = var2 << 16 | var1;
      this.m_seenChunks.push_back(var3);
   }

    bool isChunkSeen(int var1, int var2) {
    int var3 = var2 << 16 | var1;
      return this.m_seenChunks.contains(var3);
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

      throw RuntimeException("ran out of unused vehicle ids");
   }

    void setVehicleLoaded(BaseVehicle var1) {
      if (var1.sqlID == -1) {
         var1.sqlID = this.allocateID();
      }

      if (!$assertionsDisabled && this.m_loadedIDs.contains(var1.sqlID)) {
         throw std::make_unique<AssertionError>();
      } else {
         this.m_loadedIDs.push_back(var1.sqlID);
      }
   }

    void setVehicleUnloaded(BaseVehicle var1) {
      if (var1.sqlID != -1) {
         this.m_loadedIDs.remove(var1.sqlID);
      }
   }

    void addVehicle(BaseVehicle var1) {
      if (var1.sqlID == -1) {
         var1.sqlID = this.allocateID();
      }

    QueueAddVehicle var2 = (QueueAddVehicle)QueueAddVehicle.s_pool.alloc();
      var2.init(var1);
      VehiclesDB2.instance.m_worldStreamer.m_queue.push_back(var2);
   }

    void removeVehicle(BaseVehicle var1) {
    QueueRemoveVehicle var2 = (QueueRemoveVehicle)QueueRemoveVehicle.s_pool.alloc();
      var2.init(var1);
      VehiclesDB2.instance.m_worldStreamer.m_queue.push_back(var2);
   }

    void updateVehicle(BaseVehicle var1) {
      if (var1.sqlID == -1) {
         var1.sqlID = this.allocateID();
      }

    QueueUpdateVehicle var2 = (QueueUpdateVehicle)QueueUpdateVehicle.s_pool.alloc();
      var2.init(var1);
      VehiclesDB2.instance.m_worldStreamer.m_queue.push_back(var2);
   }

    void loadChunk(IsoChunk var1) {
    QueueLoadChunk var2 = (QueueLoadChunk)QueueLoadChunk.s_pool.alloc();
      var2.init(var1.wx, var1.wy);
      var1.m_loadVehiclesObject = var2;
      VehiclesDB2.instance.m_worldStreamer.m_queue.push_back(var2);
   }
}
} // namespace vehicles
} // namespace zombie
