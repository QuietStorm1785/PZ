#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/network/ServerLOS/UpdateStatus.h"

namespace zombie {
namespace network {


class ServerLOS {
public:
    IsoPlayer player;
    UpdateStatus status;
    int px;
    int py;
    int pz;
   public boolean[][][] visible;

   public ServerLOS$PlayerData(ServerLOS var1, IsoPlayer var2) {
      this.this$0 = var1;
      this.status = UpdateStatus.NeverDone;
      this.visible = new boolean[100][100][8];
      this.player = var2;
   }
}
} // namespace network
} // namespace zombie
