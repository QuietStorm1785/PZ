#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/savefile/ServerPlayerDB.h"
#include "zombie/vehicles/VehiclesDB2.h"

namespace zombie {
namespace network {


class ServerPlayersVehicles {
public:
    bool m_bStop = false;

   private ServerPlayersVehicles$SPVThread() {
   }

    void run() {
      while (!this.m_bStop) {
         try {
            this.runInner();
         } catch (Throwable var2) {
            ExceptionLogger.logException(var2);
         }
      }
   }

    void runInner() {
      ServerPlayerDB.getInstance().process();
      VehiclesDB2.instance.updateWorldStreamer();

      try {
         Thread.sleep(500L);
      } catch (InterruptedException var2) {
      }
   }
}
} // namespace network
} // namespace zombie
