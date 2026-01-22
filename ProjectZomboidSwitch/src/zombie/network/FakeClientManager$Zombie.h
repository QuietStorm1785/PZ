#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/network/NetworkVariables/WalkType.h"
#include "zombie/network/packets/ZombiePacket.h"

namespace zombie {
namespace network {


class FakeClientManager {
public:
    long lastUpdate;
    float x;
    float y;
    float z;
    short OnlineID;
    bool localOwnership = false;
    ZombiePacket zombiePacket = nullptr;
    IsoDirections dir = IsoDirections.N;
    float health = 1.0F;
    uint8_t walkType = (byte)Rand.Next(WalkType.values().length);
    float dropPositionX;
    float dropPositionY;
    bool isMoving = false;

   public FakeClientManager$Zombie(short var1) {
      this.zombiePacket = std::make_unique<ZombiePacket>();
      this.zombiePacket.id = var1;
      this.OnlineID = var1;
      this.localOwnership = false;
   }
}
} // namespace network
} // namespace zombie
