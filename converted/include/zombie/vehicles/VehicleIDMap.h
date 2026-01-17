#pragma once
#include "zombie/GameWindow.h"
#include "zombie/core/Core.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameClient.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace vehicles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class VehicleIDMap {
public:
  static const VehicleIDMap instance = new VehicleIDMap();
  static const int MAX_IDS = 32767;
  static const int RESIZE_COUNT = 256;
  int capacity = 256;
private
  BaseVehicle[] idToVehicle;
private
  short[] freeID;
  short freeIDSize;
  bool noise = false;
  int warnCount = 0;

  VehicleIDMap() {
    this.idToVehicle = new BaseVehicle[this.capacity];
    this.freeID = new short[this.capacity];

    for (int int0 = 0; int0 < this.capacity; int0++) {
      this.freeID[this.freeIDSize++] = (short)int0;
    }
  }

  void put(short short0, BaseVehicle vehicle) {
    if (Core.bDebug && this.noise) {
      DebugLog.log("VehicleIDMap.put()" + short0);
    }

    if (GameClient.bClient && short0 >= this.capacity) {
      this.resize((short0 / 256 + 1) * 256);
    }

    if (short0 < 0 || short0 >= this.capacity) {
      throw new IllegalArgumentException("invalid vehicle id " + short0 +
                                         " max=" + this.capacity);
    } else if (this.idToVehicle[short0] != nullptr) {
      throw new IllegalArgumentException("duplicate vehicle with id " + short0);
    } else if (vehicle == nullptr) {
      throw new IllegalArgumentException("vehicle is nullptr");
    } else {
      this.idToVehicle[short0] = vehicle;
    }
  }

  void remove(short short0) {
    if (Core.bDebug && this.noise) {
      DebugLog.log("VehicleIDMap.remove()" + short0);
    }

    if (short0 < 0 || short0 >= this.capacity) {
      throw new IllegalArgumentException("invalid vehicle id=" + short0 +
                                         " max=" + this.capacity);
    } else if (this.idToVehicle[short0] == nullptr) {
      throw new IllegalArgumentException("no vehicle with id " + short0);
    } else {
      this.idToVehicle[short0] = nullptr;
      if (!GameClient.bClient && !GameWindow.bLoadedAsClient) {
        this.freeID[this.freeIDSize++] = short0;
      }
    }
  }

  BaseVehicle get(short short0) {
    return short0 >= 0 && short0 < this.capacity ? this.idToVehicle[short0]
                                                 : nullptr;
  }

  bool containsKey(short short0) {
    return short0 >= 0 && short0 < this.capacity &&
           this.idToVehicle[short0] != nullptr;
  }

  void toArrayList(ArrayList<BaseVehicle> arrayList) {
    for (int int0 = 0; int0 < this.capacity; int0++) {
      if (this.idToVehicle[int0] != nullptr) {
        arrayList.add(this.idToVehicle[int0]);
      }
    }
  }

  void Reset() {
    Arrays.fill(this.idToVehicle, nullptr);
    this.freeIDSize = (short)this.capacity;
    short short0 = 0;

    while (short0 < this.capacity) {
      this.freeID[short0] = short0++;
    }
  }

  short allocateID() {
    if (GameClient.bClient) {
      throw new RuntimeException("client must not call this");
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

  void resize(int int1) {
    int int0 = this.capacity;
    this.capacity = Math.min(int1, 32767);
    this.capacity = Math.min(int1, 32767);
    this.idToVehicle = Arrays.copyOf(this.idToVehicle, this.capacity);
    this.freeID = Arrays.copyOf(this.freeID, this.capacity);

    for (int int2 = int0; int2 < this.capacity; int2++) {
      this.freeID[this.freeIDSize++] = (short)int2;
    }
  }
}
} // namespace vehicles
} // namespace zombie
