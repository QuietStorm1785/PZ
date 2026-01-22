#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/core/Core.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameClient.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class VehicleIDMap {
public:
    static const VehicleIDMap instance = std::make_shared<VehicleIDMap>();
    static const int MAX_IDS = 32767;
    static const int RESIZE_COUNT = 256;
    int capacity = 256;
   private BaseVehicle[] idToVehicle;
   private short[] freeID;
    short freeIDSize;
    bool noise = false;
    int warnCount = 0;

   VehicleIDMap() {
      this.idToVehicle = new BaseVehicle[this.capacity];
      this.freeID = new short[this.capacity];

      for (int var1 = 0; var1 < this.capacity; var1++) {
         this.freeID[this.freeIDSize++] = (short)var1;
      }
   }

    void put(short var1, BaseVehicle var2) {
      if (Core.bDebug && this.noise) {
         DebugLog.log("VehicleIDMap.put()" + var1);
      }

      if (GameClient.bClient && var1 >= this.capacity) {
         this.resize((var1 / 256 + 1) * 256);
      }

      if (var1 < 0 || var1 >= this.capacity) {
         throw IllegalArgumentException("invalid vehicle id " + var1 + " max=" + this.capacity);
      } else if (this.idToVehicle[var1] != nullptr) {
         throw IllegalArgumentException("duplicate vehicle with id " + var1);
      } else if (var2 == nullptr) {
         throw IllegalArgumentException("vehicle is nullptr");
      } else {
         this.idToVehicle[var1] = var2;
      }
   }

    void remove(short var1) {
      if (Core.bDebug && this.noise) {
         DebugLog.log("VehicleIDMap.remove()" + var1);
      }

      if (var1 < 0 || var1 >= this.capacity) {
         throw IllegalArgumentException("invalid vehicle id=" + var1 + " max=" + this.capacity);
      } else if (this.idToVehicle[var1] == nullptr) {
         throw IllegalArgumentException("no vehicle with id " + var1);
      } else {
         this.idToVehicle[var1] = nullptr;
         if (!GameClient.bClient && !GameWindow.bLoadedAsClient) {
            this.freeID[this.freeIDSize++] = var1;
         }
      }
   }

    BaseVehicle get(short var1) {
      return var1 >= 0 && var1 < this.capacity ? this.idToVehicle[var1] : nullptr;
   }

    bool containsKey(short var1) {
      return var1 >= 0 && var1 < this.capacity && this.idToVehicle[var1] != nullptr;
   }

    void toArrayList(std::vector<BaseVehicle> var1) {
      for (int var2 = 0; var2 < this.capacity; var2++) {
         if (this.idToVehicle[var2] != nullptr) {
            var1.push_back(this.idToVehicle[var2]);
         }
      }
   }

    void Reset() {
      Arrays.fill(this.idToVehicle, nullptr);
      this.freeIDSize = (short)this.capacity;
    short var1 = 0;

      while (var1 < this.capacity) {
         this.freeID[var1] = var1++;
      }
   }

    short allocateID() {
      if (GameClient.bClient) {
         throw RuntimeException("client must not call this");
      } else if (this.freeIDSize > 0) {
         return this.freeID[--this.freeIDSize];
      } else if (this.capacity >= 32767) {
         if (this.warnCount < 100) {
            DebugLog.log("warning: ran out of unique vehicle ids");
            this.warnCount++;
         }

         return -1;
      } else {
         this.resize(this.capacity + 256);
         return this.allocateID();
      }
   }

    void resize(int var1) {
    int var2 = this.capacity;
      this.capacity = Math.min(var1, 32767);
      this.capacity = Math.min(var1, 32767);
      this.idToVehicle = Arrays.copyOf(this.idToVehicle, this.capacity);
      this.freeID = Arrays.copyOf(this.freeID, this.capacity);

      for (int var3 = var2; var3 < this.capacity; var3++) {
         this.freeID[this.freeIDSize++] = (short)var3;
      }
   }
}
} // namespace vehicles
} // namespace zombie
