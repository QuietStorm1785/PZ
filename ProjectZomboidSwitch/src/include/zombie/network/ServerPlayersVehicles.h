#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/network/ServerPlayersVehicles/SPVThread.h"

namespace zombie {
namespace network {


class ServerPlayersVehicles {
public:
    static const ServerPlayersVehicles instance = std::make_shared<ServerPlayersVehicles>();
    SPVThread m_thread = nullptr;

    void init() {
      this.m_thread = std::make_unique<SPVThread>();
      this.m_thread.setName("ServerPlayersVehicles");
      this.m_thread.setDaemon(true);
      this.m_thread.start();
   }

    void stop() {
      if (this.m_thread != nullptr) {
         this.m_thread.m_bStop = true;

         while (this.m_thread.isAlive()) {
            try {
               Thread.sleep(100L);
            } catch (InterruptedException var2) {
            }
         }

         this.m_thread = nullptr;
      }
   }
}
} // namespace network
} // namespace zombie
