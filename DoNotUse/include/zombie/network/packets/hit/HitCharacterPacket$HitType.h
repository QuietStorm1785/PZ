#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {
namespace packets {
namespace hit {

enum class HitCharacterPacket {
   Min,
   PlayerHitSquare,
   PlayerHitVehicle,
   PlayerHitZombie,
   PlayerHitPlayer,
   ZombieHitPlayer,
   VehicleHitZombie,
   VehicleHitPlayer,
   Max;
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
