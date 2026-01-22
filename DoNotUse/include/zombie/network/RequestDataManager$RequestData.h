#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/network/packets/RequestDataPacket/RequestID.h"
#include <filesystem>

namespace zombie {
namespace network {


class RequestDataManager {
public:
    const RequestID id;
    const ByteBuffer bb;
    const long connectionGUID;
    long creationTime = System.currentTimeMillis();
    int realTransmitted;
    int realTransmittedFromLastACK;

   public RequestDataManager$RequestData(RequestID var1, ByteBuffer var2, long var3) {
      this.id = var1;
      this.bb = ByteBuffer.allocate(var2.position());
      this.bb.put(var2.array(), 0, this.bb.limit());
      this.connectionGUID = var3;
      this.realTransmitted = 0;
      this.realTransmittedFromLastACK = 0;
   }

   public RequestDataManager$RequestData(RequestID var1, int var2, long var3) {
      this.id = var1;
      this.bb = ByteBuffer.allocate(var2);
      this.bb.clear();
      this.connectionGUID = var3;
      this.realTransmitted = 0;
      this.realTransmittedFromLastACK = 0;
   }
}
} // namespace network
} // namespace zombie
