#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/network/packets/PlayerVariables/NetworkPlayerVariableIDs.h"

namespace zombie {
namespace network {
namespace packets {


class PlayerVariables {
public:
    NetworkPlayerVariableIDs id;
    float value;

   private PlayerVariables$NetworkPlayerVariable(PlayerVariables var1) {
      this.this$0 = var1;
   }

    void set(IsoPlayer var1, NetworkPlayerVariableIDs var2) {
      this.id = var2;
      this.value = var1.getVariableFloat(var2.name(), 0.0F);
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
