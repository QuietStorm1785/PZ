#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/areas/NonPvpZone.h"
#include "zombie/util/StringUtils.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {


class SyncNonPvpZonePacket {
public:
    const NonPvpZone zone = std::make_shared<NonPvpZone>();
    bool doRemove;

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.zone.load(var1, IsoWorld.getWorldVersion());
      this.doRemove = var1.get() == 1;
   }

    void write(ByteBufferWriter var1) {
      this.zone.save(var1.bb);
      var1.putBoolean(this.doRemove);
   }

    bool isConsistent() {
      return !StringUtils.isNullOrEmpty(this.zone.getTitle());
   }

    std::string getDescription() {
      return std::string.format(
         "\"%s\" remove=%b size=%d (%d;%d) (%d;%d)",
         this.zone.getTitle(),
         this.doRemove,
         this.zone.getSize(),
         this.zone.getX(),
         this.zone.getY(),
         this.zone.getX2(),
         this.zone.getY2()
      );
   }

    void process() {
      if (this.doRemove) {
         NonPvpZone.getAllZones().removeIf(var1 -> var1.getTitle() == this.zone.getTitle()));
      } else if (NonPvpZone.getZoneByTitle(this.zone.getTitle()) == nullptr) {
         NonPvpZone.getAllZones().push_back(this.zone);
      }
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
