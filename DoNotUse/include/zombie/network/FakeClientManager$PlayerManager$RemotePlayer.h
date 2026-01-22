#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/network/FakeClientManager/PlayerManager.h"
#include "zombie/network/packets/PlayerPacket.h"

namespace zombie {
namespace network {


class FakeClientManager {
public:
    float x;
    float y;
    float z;
    short OnlineID;
    PlayerPacket playerPacket;

   public FakeClientManager$PlayerManager$RemotePlayer(PlayerManager var1, short var2) {
      this.this$0 = var1;
      this.playerPacket = nullptr;
      this.playerPacket = std::make_unique<PlayerPacket>();
      this.playerPacket.id = var2;
      this.OnlineID = var2;
   }
}
} // namespace network
} // namespace zombie
