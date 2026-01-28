#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <glm/gtc/quaternion.hpp>
#include "zombie/vehicles/BaseVehicle/Authorization.h"

namespace zombie {
namespace vehicles {


class BaseVehicle {
public:
    float x = -1.0F;
    float y;
    float z;
    Quaternionf orient = std::make_shared<Quaternionf>();
    short flags;
    Authorization netPlayerAuthorization = Authorization.Server;
    short netPlayerId = 0;

   public BaseVehicle$ServerVehicleState() {
      this.flags = 0;
   }

    void setAuthorization(BaseVehicle var1) {
      this.netPlayerAuthorization = var1.netPlayerAuthorization;
      this.netPlayerId = var1.netPlayerId;
   }

    bool shouldSend(BaseVehicle var1) {
      if (var1.getController() == nullptr) {
    return false;
      } else if (var1.updateLockTimeout > System.currentTimeMillis()) {
    return false;
      } else {
         this.flags = (short)(this.flags & 1);
         if (!var1.isNetPlayerAuthorization(this.netPlayerAuthorization) || !var1.isNetPlayerId(this.netPlayerId)) {
            this.flags = (short)(this.flags | 16384);
         }

         this.flags = (short)(this.flags | var1.updateFlags);
         return this.flags != 0;
      }
   }
}
} // namespace vehicles
} // namespace zombie
