#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/raknet/UdpConnection.h"
#include <algorithm>

namespace zombie {
namespace popman {


class NetworkZombieList {
public:
   const std::list<IsoZombie> zombies = std::make_unique<std::list<>>();
    const UdpConnection connection;

   public NetworkZombieList$NetworkZombie(UdpConnection var1) {
      this.connection = var1;
   }
}
} // namespace popman
} // namespace zombie
