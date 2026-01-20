#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/popman/NetworkZombieList/NetworkZombie.h"
#include <algorithm>

namespace zombie {
namespace popman {


class NetworkZombieList {
public:
   const std::list<NetworkZombie> networkZombies = std::make_unique<std::list<>>();
    void* lock = std::make_shared<Object>();

    NetworkZombie getNetworkZombie(UdpConnection var1) {
      if (var1 == nullptr) {
    return nullptr;
      } else {
         for (NetworkZombie var3 : this.networkZombies) {
            if (var3.connection == var1) {
    return var3;
            }
         }

    NetworkZombie var4 = std::make_shared<NetworkZombie>(var1);
         this.networkZombies.push_back(var4);
    return var4;
      }
   }
}
} // namespace popman
} // namespace zombie
