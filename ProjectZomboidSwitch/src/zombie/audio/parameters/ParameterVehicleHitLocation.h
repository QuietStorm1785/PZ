#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"
#include "zombie/audio/parameters/OpenALParameterStub.h"
#include "zombie/audio/parameters/ParameterVehicleHitLocation/HitLocation.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/BaseVehicle/Vector3fObjectPool.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterVehicleHitLocation : public zombie::audio::OpenALParameterStub {
public:
    HitLocation location = HitLocation.Front;

    public ParameterVehicleHitLocation() {
      super("VehicleHitLocation");
   }

    float calculateCurrentValue() {
      return this.location.label;
   }

    static HitLocation calculateLocation(BaseVehicle var0, float var1, float var2, float var3) {
    VehicleScript var4 = var0.getScript();
      if (var4 == nullptr) {
         return HitLocation.Front;
      } else {
    Vector3f var5 = var0.getLocalPos(var1, var2, var3, (Vector3f)((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).alloc());
    Vector3f var6 = var4.getExtents();
    Vector3f var7 = var4.getCenterOfMassOffset();
    float var8 = var7.z - var6.z / 2.0F;
    float var9 = var7.z + var6.z / 2.0F;
         var8 *= 0.9F;
         var9 *= 0.9F;
    HitLocation var10;
         if (var5.z >= var8 && var5.z <= var9) {
            var10 = HitLocation.Side;
         } else if (var5.z > 0.0F) {
            var10 = HitLocation.Front;
         } else {
            var10 = HitLocation.Rear;
         }

         ((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).release(var5);
    return var10;
      }
   }

    void setLocation(HitLocation var1) {
      this.location = var1;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
