#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/iso/Vector2.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehicleLight.h"
#include "zombie/vehicles/VehiclePart.h"

namespace zombie {
namespace characters {


class IsoGameCharacter {
public:
   private static final ObjectPool<IsoGameCharacter$TorchInfo> TorchInfoPool = new ObjectPool(IsoGameCharacter$TorchInfo::new);
    static auto tempVector3f = std::make_shared<Vector3f>();
    int id;
    float x;
    float y;
    float z;
    float angleX;
    float angleY;
    float dist;
    float strength;
    bool bCone;
    float dot;
    int focusing;

   public static IsoGameCharacter$TorchInfo alloc() {
      return (IsoGameCharacter$TorchInfo)TorchInfoPool.alloc();
   }

    static void release(IsoGameCharacter$TorchInfo var0) {
      TorchInfoPool.release(var0);
   }

   public IsoGameCharacter$TorchInfo set(IsoPlayer var1, InventoryItem var2) {
      this.x = var1.getX();
      this.y = var1.getY();
      this.z = var1.getZ();
    Vector2 var3 = var1.getLookVector(IsoGameCharacter.tempVector2);
      this.angleX = var3.x;
      this.angleY = var3.y;
      this.dist = var2.getLightDistance();
      this.strength = var2.getLightStrength();
      this.bCone = var2.isTorchCone();
      this.dot = var2.getTorchDot();
      this.focusing = 0;
    return this;
   }

   public IsoGameCharacter$TorchInfo set(VehiclePart var1) {
    BaseVehicle var2 = var1.getVehicle();
    VehicleLight var3 = var1.getLight();
    VehicleScript var4 = var2.getScript();
    Vector3f var5 = tempVector3f;
      var5.set(var3.offset.x * var4.getExtents().x / 2.0F, 0.0F, var3.offset.y * var4.getExtents().z / 2.0F);
      var2.getWorldPos(var5, var5);
      this.x = var5.x;
      this.y = var5.y;
      this.z = var5.z;
      var5 = var2.getForwardVector(var5);
      this.angleX = var5.x;
      this.angleY = var5.z;
      this.dist = var1.getLightDistance();
      this.strength = var1.getLightIntensity();
      this.bCone = true;
      this.dot = var3.dot;
      this.focusing = (int)var1.getLightFocusing();
    return this;
   }
}
} // namespace characters
} // namespace zombie
