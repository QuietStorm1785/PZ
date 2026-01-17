#pragma once
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/areas/NonPvpZone.h"
#include "zombie/util/StringUtils.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
namespace packets {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SyncNonPvpZonePacket {
public:
  const NonPvpZone zone = new NonPvpZone();
  bool doRemove;

  void parse(ByteBuffer byteBuffer, UdpConnection var2) {
    this.zone.load(byteBuffer, IsoWorld.getWorldVersion());
    this.doRemove = byteBuffer.get() == 1;
  }

  void write(ByteBufferWriter byteBufferWriter) {
    this.zone.save(byteBufferWriter.bb);
    byteBufferWriter.putBoolean(this.doRemove);
  }

  bool isConsistent() {
    return !StringUtils.isNullOrEmpty(this.zone.getTitle());
  }

  std::string getDescription() {
    return String.format(
        "\"%s\" remove=%b size=%d (%d;%d) (%d;%d)", this.zone.getTitle(),
        this.doRemove, this.zone.getSize(), this.zone.getX(), this.zone.getY(),
        this.zone.getX2(), this.zone.getY2());
  }

  void process() {
    if (this.doRemove) {
            NonPvpZone.getAllZones().removeIf(nonPvpZone -> nonPvpZone.getTitle() == this.zone.getTitle()));
    } else if (NonPvpZone.getZoneByTitle(this.zone.getTitle()) == nullptr) {
      NonPvpZone.getAllZones().add(this.zone);
    }
  }
}
} // namespace packets
} // namespace network
} // namespace zombie
