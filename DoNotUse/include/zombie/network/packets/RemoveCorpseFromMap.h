#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {


class RemoveCorpseFromMap {
public:
    short id;
    IsoDeadBody deadBody = nullptr;

    void set(IsoDeadBody var1) {
      this.id = var1.getObjectID();
      this.deadBody = var1;
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.id = var1.getShort();
      this.deadBody = IsoDeadBody.getDeadBody(this.id);
   }

    void write(ByteBufferWriter var1) {
      var1.putShort(this.id);
   }

    void process() {
      if (this.isConsistent()) {
         IsoDeadBody.removeDeadBody(this.id);
      }
   }

    std::string getDescription() {
      return std::string.format(this.getClass().getSimpleName() + " id=%d", this.id);
   }

    bool isConsistent() {
      return this.deadBody != nullptr && this.deadBody.getSquare() != nullptr;
   }

    bool isRelevant(UdpConnection var1) {
      return var1.RelevantTo(this.deadBody.getX(), this.deadBody.getY());
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
