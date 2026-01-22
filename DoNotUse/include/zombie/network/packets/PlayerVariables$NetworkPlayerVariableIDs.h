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

enum class PlayerVariables {
   IdleSpeed,
   WalkInjury,
   WalkSpeed,
   DeltaX,
   DeltaY,
   AttackVariationX,
   AttackVariationY,
   targetDist,
   autoShootVarX,
   autoShootVarY,
   recoilVarX,
   recoilVarY,
   ShoveAimX,
   ShoveAimY;
}
} // namespace packets
} // namespace network
} // namespace zombie
