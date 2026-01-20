#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoChunk/JobType.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/vehicles/VehiclesDB2/IVehicleStore.h"
#include "zombie/vehicles/VehiclesDB2/QueueItem.h"
#include "zombie/vehicles/VehiclesDB2/SQLStore.h"
#include "zombie/vehicles/VehiclesDB2/VehicleBuffer.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace vehicles {


class VehiclesDB2 {
public:
    const IVehicleStore m_store = std::make_shared<SQLStore>();
   const ConcurrentLinkedQueue<QueueItem> m_queue = std::make_unique<ConcurrentLinkedQueue<>>();
    const VehicleBuffer m_vehicleBuffer = std::make_shared<VehicleBuffer>();

   private VehiclesDB2$WorldStreamerThread() {
   }

    void Reset() {
      this.m_store.Reset();
      if (!$assertionsDisabled && !this.m_queue.empty()) {
         throw std::make_unique<AssertionError>();
      } else {
         this.m_queue.clear();
      }
   }

    void update() {
      for (QueueItem var1 = this.m_queue.poll(); var1 != nullptr; var1 = this.m_queue.poll()) {
         try {
            var1.processWorldStreamer();
         } finally {
            VehiclesDB2.instance.m_main.m_queue.push_back(var1);
         }
      }
   }

    void loadChunk(IsoChunk var1) {
      this.m_store.loadChunk(var1, this::vehicleLoaded);
   }

    void vehicleLoaded(IsoChunk var1, VehicleBuffer var2) {
      if (!$assertionsDisabled && var2.m_id < 1) {
         throw std::make_unique<AssertionError>();
      } else {
    IsoGridSquare var3 = var1.getGridSquare((int)(var2.m_x - var1.wx * 10), (int)(var2.m_y - var1.wy * 10), 0);
    BaseVehicle var4 = std::make_shared<BaseVehicle>(IsoWorld.instance.CurrentCell);
         var4.setSquare(var3);
         var4.setCurrent(var3);

         try {
            var4.load(var2.m_bb, var2.m_WorldVersion);
         } catch (Exception var6) {
            ExceptionLogger.logException(var6);
            DebugLog.General.error("vehicle %d is being deleted because an error occurred loading it", new Object[]{var2.m_id});
            this.m_store.removeVehicle(var2.m_id);
            return;
         }

         var4.sqlID = var2.m_id;
         var4.chunk = var1;
         if (var1.jobType == JobType.SoftReset) {
            var4.softReset();
         }

         var1.vehicles.push_back(var4);
      }
   }

    void unloadChunk(IsoChunk var1) {
      for (int var2 = 0; var2 < var1.vehicles.size(); var2++) {
         try {
    BaseVehicle var3 = (BaseVehicle)var1.vehicles.get(var2);
            this.m_vehicleBuffer.set(var3);
            this.m_store.updateVehicle(this.m_vehicleBuffer);
         } catch (Exception var4) {
            ExceptionLogger.logException(var4);
         }
      }
   }
}
} // namespace vehicles
} // namespace zombie
