#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#if __has_include(<absl/container/flat_hash_map.h>)
#  include <absl/container/flat_hash_map.h>
#  define INT_HASH_MAP boost::unordered_map
#elif __has_include(<boost/unordered_map.hpp>)
#  include <boost/unordered_map.hpp>
#  define INT_HASH_MAP boost::unordered_map
#else
#  include <unordered_map>
#  define INT_HASH_MAP std::unordered_map
#endif
#include <algorithm>

namespace zombie {
namespace vehicles {


class VehicleCache {
public:
    short id;
    float x;
    float y;
    float z;
   private:
    static INT_HASH_MAP<short, VehicleCache> mapId;
    static INT_HASH_MAP<int, std::list<VehicleCache>> mapXY;

    static void vehicleUpdate(short var0, float var1, float var2, float var3) {
    VehicleCache var4 = (VehicleCache)mapId.get(var0);
      if (var4 != nullptr) {
    int var5 = (int)(var4.x / 10.0F);
    int var6 = (int)(var4.y / 10.0F);
    int var7 = (int)(var1 / 10.0F);
    int var8 = (int)(var2 / 10.0F);
         if (var5 != var7 || var6 != var8) {
            ((List)mapXY.get(var5 * 65536 + var6)).remove(var4);
            if (mapXY.get(var7 * 65536 + var8) == nullptr) {
               mapXY.put(var7 * 65536 + var8, std::make_unique<std::list>());
            }

            ((List)mapXY.get(var7 * 65536 + var8)).push_back(var4);
         }

         var4.x = var1;
         var4.y = var2;
         var4.z = var3;
      } else {
    VehicleCache var9 = std::make_shared<VehicleCache>();
         var9.id = var0;
         var9.x = var1;
         var9.y = var2;
         var9.z = var3;
         mapId.put(var0, var9);
    int var10 = (int)(var1 / 10.0F);
    int var11 = (int)(var2 / 10.0F);
         if (mapXY.get(var10 * 65536 + var11) == nullptr) {
            mapXY.put(var10 * 65536 + var11, std::make_unique<std::list>());
         }

         ((List)mapXY.get(var10 * 65536 + var11)).push_back(var9);
      }
   }

   public static List<VehicleCache> vehicleGet(float var0, float var1) {
    int var2 = (int)(var0 / 10.0F);
    int var3 = (int)(var1 / 10.0F);
      return (List<VehicleCache>)mapXY.get(var2 * 65536 + var3);
   }

   public static List<VehicleCache> vehicleGet(int var0, int var1) {
      return (List<VehicleCache>)mapXY.get(var0 * 65536 + var1);
   }

    static void remove(short var0) {
    VehicleCache var1 = (VehicleCache)mapId.get(var0);
      if (var1 != nullptr) {
         mapId.remove(var0);
    int var2 = (int)(var1.x / 10.0F);
    int var3 = (int)(var1.y / 10.0F);
    int var4 = var2 * 65536 + var3;

         assert mapXY.containsKey(var4);

         assert ((List)mapXY.get(var4)).contains(var1);

         ((List)mapXY.get(var4)).remove(var1);
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
