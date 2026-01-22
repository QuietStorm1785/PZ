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

enum class EventPacket {
   EventSetActivatedPrimary,
   EventSetActivatedSecondary,
   EventFishing,
   EventFitness,
   EventEmote,
   EventClimbFence,
   EventClimbDownRope,
   EventClimbRope,
   EventClimbWall,
   EventClimbWindow,
   EventOpenWindow,
   EventCloseWindow,
   EventSmashWindow,
   EventSitOnGround,
   wasBumped,
   collideWithWall,
   EventUpdateFitness,
   EventFallClimb,
   EventOverrideItem,
   ChargeSpearConnect,
   Update,
   Unknown;
}
} // namespace packets
} // namespace network
} // namespace zombie
