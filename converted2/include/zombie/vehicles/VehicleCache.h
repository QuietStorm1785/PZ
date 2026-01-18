#pragma once
#include "gnu/trove/map/hash/TIntObjectHashMap.h"
#include "gnu/trove/map/hash/TShortObjectHashMap.h"
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

class VehicleCache {
public:
  short id;
  float x;
  float y;
  float z;
private
  static TShortObjectHashMap<VehicleCache> mapId =
      std::make_unique<TShortObjectHashMap<>>();
private
  static TIntObjectHashMap<List<VehicleCache>> mapXY =
      std::make_unique<TIntObjectHashMap<>>();

  static void vehicleUpdate(short short0, float float0, float float1,
                            float float2) {
    VehicleCache vehicleCache0 = mapId.get(short0);
    if (vehicleCache0 != nullptr) {
      int int0 = (int)(vehicleCache0.x / 10.0F);
      int int1 = (int)(vehicleCache0.y / 10.0F);
      int int2 = (int)(float0 / 10.0F);
      int int3 = (int)(float1 / 10.0F);
      if (int0 != int2 || int1 != int3) {
        mapXY.get(int0 * 65536 + int1).remove(vehicleCache0);
        if (mapXY.get(int2 * 65536 + int3) == nullptr) {
          mapXY.put(int2 * 65536 + int3, std::make_unique<LinkedList<>>());
        }

        mapXY.get(int2 * 65536 + int3).add(vehicleCache0);
      }

      vehicleCache0.x = float0;
      vehicleCache0.y = float1;
      vehicleCache0.z = float2;
    } else {
      VehicleCache vehicleCache1 = new VehicleCache();
      vehicleCache1.id = short0;
      vehicleCache1.x = float0;
      vehicleCache1.y = float1;
      vehicleCache1.z = float2;
      mapId.put(short0, vehicleCache1);
      int int4 = (int)(float0 / 10.0F);
      int int5 = (int)(float1 / 10.0F);
      if (mapXY.get(int4 * 65536 + int5) == nullptr) {
        mapXY.put(int4 * 65536 + int5, std::make_unique<LinkedList<>>());
      }

      mapXY.get(int4 * 65536 + int5).add(vehicleCache1);
    }
  }

public
  static List<VehicleCache> vehicleGet(float float0, float float1) {
    int int0 = (int)(float0 / 10.0F);
    int int1 = (int)(float1 / 10.0F);
    return mapXY.get(int0 * 65536 + int1);
  }

public
  static List<VehicleCache> vehicleGet(int int1, int int0) {
    return mapXY.get(int1 * 65536 + int0);
  }

  static void remove(short short0) {
    VehicleCache vehicleCache = mapId.get(short0);
    if (vehicleCache != nullptr) {
      mapId.remove(short0);
      int int0 = (int)(vehicleCache.x / 10.0F);
      int int1 = (int)(vehicleCache.y / 10.0F);
      int int2 = int0 * 65536 + int1;

      assert mapXY.containsKey(int2);

      assert mapXY.get(int2).contains(vehicleCache);

      mapXY.get(int2).remove(vehicleCache);
    }
  }

  static void Reset() {
    mapId.clear();
    mapXY.clear();
  }

  static {
    mapId.setAutoCompactionFactor(0.0F);
    mapXY.setAutoCompactionFactor(0.0F);
  }
}
} // namespace vehicles
} // namespace zombie
