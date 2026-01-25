#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#if __has_include(<absl/container/flat_hash_map.h>)
#  include <absl/container/flat_hash_map.h>
#  include <absl/container/flat_hash_set.h>
#  define INT_HASH_MAP boost::unordered_map
#  define INT_HASH_SET boost::unordered_set
#elif __has_include(<boost/unordered_map.hpp>)
#  include <boost/unordered_map.hpp>
#  include <boost/unordered_set.hpp>
#  define INT_HASH_MAP boost::unordered_map
#  define INT_HASH_SET boost::unordered_set
#else
#  include <unordered_map>
#  include <unordered_set>
#  define INT_HASH_MAP std::unordered_map
#  define INT_HASH_SET std::unordered_set
#endif
#include "zombie/iso/IsoChunk.h"
#include "zombie/vehicles/VehiclesDB2/IVehicleStore.h"
#include "zombie/vehicles/VehiclesDB2/ThrowingBiConsumer.h"
#include "zombie/vehicles/VehiclesDB2/ThrowingConsumer.h"
#include "zombie/vehicles/VehiclesDB2/VehicleBuffer.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace vehicles {


class VehiclesDB2 {
public:
   INT_HASH_MAP<int, VehicleBuffer> m_IDToVehicle;
   INT_HASH_MAP<int, std::vector<VehicleBuffer>> m_ChunkToVehicles;

   private VehiclesDB2$MemoryStore() {
   }

   void init(INT_HASH_SET<int>& var1, INT_HASH_SET<int>& var2) {
      var1.clear();
      var2.clear();
   }

    void Reset() {
      this.m_IDToVehicle.clear();
      this.m_ChunkToVehicles.clear();
   }

    void loadChunk(IsoChunk var1, IOException> var2) {
    int var3 = var1.wy << 16 | var1.wx;
    std::vector var4 = (std::vector)this.m_ChunkToVehicles.get(var3);
      if (var4 != nullptr) {
         for (int var5 = 0; var5 < var4.size(); var5++) {
    VehicleBuffer var6 = (VehicleBuffer)var4.get(var5);
            var6.m_bb.rewind();
    bool var7 = var6.m_bb.get() == 1;
    int var8 = var6.m_bb.getInt();
            var2.accept(var1, var6);
         }
      }
   }

    void loadChunk(int var1, int var2, IOException> var3) {
    int var4 = var2 << 16 | var1;
    std::vector var5 = (std::vector)this.m_ChunkToVehicles.get(var4);
      if (var5 != nullptr) {
         for (int var6 = 0; var6 < var5.size(); var6++) {
    VehicleBuffer var7 = (VehicleBuffer)var5.get(var6);
            var7.m_bb.rewind();
    bool var8 = var7.m_bb.get() == 1;
    int var9 = var7.m_bb.getInt();
            var3.accept(var7);
         }
      }
   }

    void updateVehicle(VehicleBuffer var1) {
      if (!$assertionsDisabled && var1.m_id < 1) {
         throw std::make_unique<AssertionError>();
      } else {
         /* synchronized - TODO: add std::mutex */ (VehiclesDB2.instance.m_main.m_usedIDs) {
            if (!$assertionsDisabled && !VehiclesDB2.instance.m_main.m_usedIDs.contains(var1.m_id)) {
               throw std::make_unique<AssertionError>();
            }
         }

         var1.m_bb.rewind();
    VehicleBuffer var5 = (VehicleBuffer)this.m_IDToVehicle.get(var1.m_id);
         if (var5 == nullptr) {
            var5 = std::make_unique<VehicleBuffer>();
            var5.m_id = var1.m_id;
            this.m_IDToVehicle.put(var1.m_id, var5);
         } else {
    int var3 = var5.m_wy << 16 | var5.m_wx;
            ((std::vector)this.m_ChunkToVehicles.get(var3)).remove(var5);
         }

         var5.m_wx = var1.m_wx;
         var5.m_wy = var1.m_wy;
         var5.m_x = var1.m_x;
         var5.m_y = var1.m_y;
         var5.m_WorldVersion = var1.m_WorldVersion;
         var5.setBytes(var1.m_bb);
    int var6 = var5.m_wy << 16 | var5.m_wx;
         if (this.m_ChunkToVehicles.get(var6) == nullptr) {
            this.m_ChunkToVehicles.put(var6, std::make_unique<std::vector>());
         }

         ((std::vector)this.m_ChunkToVehicles.get(var6)).push_back(var5);
      }
   }

    void removeVehicle(int var1) {
    VehicleBuffer var2 = (VehicleBuffer)this.m_IDToVehicle.remove(var1);
      if (var2 != nullptr) {
    int var3 = var2.m_wy << 16 | var2.m_wx;
         ((std::vector)this.m_ChunkToVehicles.get(var3)).remove(var2);
      }
   }
}
} // namespace vehicles
} // namespace zombie
