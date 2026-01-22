#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"

namespace zombie {
namespace network {


class ItemTransactionManager {
public:
    static const uint8_t StateUnknown = 0;
    static const uint8_t StateRejected = 1;
    static const uint8_t StateAccepted = 2;
    const int itemID;
    const int srcID;
    const int dstID;
    const long timestamp;
    uint8_t state;

   private ItemTransactionManager$ItemRequest(int var1, int var2, int var3) {
      this.itemID = var1;
      this.srcID = var2;
      this.dstID = var3;
      this.timestamp = GameTime.getServerTimeMills() + 5000L;
      this.state = (byte)(GameServer.bServer ? 1 : 0);
   }

    void setState(uint8_t var1) {
      this.state = var1;
   }

    bool isTimeout() {
      return GameTime.getServerTimeMills() > this.timestamp;
   }
}
} // namespace network
} // namespace zombie
