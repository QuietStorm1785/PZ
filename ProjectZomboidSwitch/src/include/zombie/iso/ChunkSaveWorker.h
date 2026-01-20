#pragma once
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameServer.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehiclesDB2.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {


class ChunkSaveWorker {
public:
    static ChunkSaveWorker instance = std::make_shared<ChunkSaveWorker>();
   private const std::vector<IsoChunk> tempList = std::make_unique<std::vector<>>();
   public ConcurrentLinkedQueue<IsoChunk> toSaveQueue = std::make_unique<ConcurrentLinkedQueue<>>();
    bool bSaving;

    void Update(IsoChunk var1) {
      if (!GameServer.bServer) {
    IsoChunk var2 = nullptr;
    void* var3 = nullptr;
         this.bSaving = !this.toSaveQueue.empty();
         if (this.bSaving) {
            if (var1 != nullptr) {
               for (IsoChunk var6 : this.toSaveQueue) {
                  if (var6.wx == var1.wx && var6.wy == var1.wy) {
                     var2 = var6;
                     break;
                  }
               }
            }

            if (var2 == nullptr) {
               var2 = this.toSaveQueue.poll();
            } else {
               this.toSaveQueue.remove(var2);
            }

            if (var2 != nullptr) {
               try {
                  var2.Save(false);
               } catch (Exception var5) {
                  var5.printStackTrace();
               }
            }
         }
      }
   }

    void SaveNow(std::vector<IsoChunk> var1) {
      this.tempList.clear();

      for (IsoChunk var2 = this.toSaveQueue.poll(); var2 != nullptr; var2 = this.toSaveQueue.poll()) {
    bool var3 = false;

         for (int var4 = 0; var4 < var1.size(); var4++) {
    IsoChunk var5 = (IsoChunk)var1.get(var4);
            if (var2.wx == var5.wx && var2.wy == var5.wy) {
               try {
                  var2.Save(false);
               } catch (IOException var7) {
                  var7.printStackTrace();
               }

               var3 = true;
               break;
            }
         }

         if (!var3) {
            this.tempList.push_back(var2);
         }
      }

      for (int var8 = 0; var8 < this.tempList.size(); var8++) {
         this.toSaveQueue.push_back(this.tempList.get(var8));
      }

      this.tempList.clear();
   }

    void SaveNow() {
      DebugLog.log("EXITDEBUG: ChunkSaveWorker.SaveNow 1");

      for (IsoChunk var1 = this.toSaveQueue.poll(); var1 != nullptr; var1 = this.toSaveQueue.poll()) {
         try {
            DebugLog.log("EXITDEBUG: ChunkSaveWorker.SaveNow 2 (ch=" + var1.wx + ", " + var1.wy + ")");
            var1.Save(false);
         } catch (Exception var3) {
            var3.printStackTrace();
         }
      }

      this.bSaving = false;
      DebugLog.log("EXITDEBUG: ChunkSaveWorker.SaveNow 3");
   }

    void Add(IsoChunk var1) {
      if (Core.getInstance().isNoSave()) {
         for (int var2 = 0; var2 < var1.vehicles.size(); var2++) {
            VehiclesDB2.instance.updateVehicle((BaseVehicle)var1.vehicles.get(var2));
         }
      }

      if (!this.toSaveQueue.contains(var1)) {
         this.toSaveQueue.push_back(var1);
      }
   }
}
} // namespace iso
} // namespace zombie
