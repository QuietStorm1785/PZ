#pragma once
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/network/packets/INetworkPacket.h"
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
namespace hit {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PlayerHitSquarePacket : public PlayerHitPacket {
public:
  const Square square = new Square();

public
  PlayerHitSquarePacket() { super(HitCharacterPacket.HitType.PlayerHitSquare); }

  void set(IsoPlayer player, HandWeapon weapon, bool boolean0) {
    super.set(player, weapon, boolean0);
    this.square.set(player);
  }

  void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
    super.parse(byteBuffer, udpConnection);
    this.square.parse(byteBuffer, udpConnection);
  }

  void write(ByteBufferWriter byteBufferWriter) {
    super.write(byteBufferWriter);
    this.square.write(byteBufferWriter);
  }

  bool isRelevant(UdpConnection udpConnection) {
    return this.wielder.isRelevant(udpConnection);
  }

  bool isConsistent() {
    return super.isConsistent() && this.square.isConsistent();
  }

  std::string getDescription() {
    return super.getDescription() + "\n\tSquare " +
           this.square.getDescription();
  }

  void process() { this.square.process(this.wielder.getCharacter()); }

  bool validate(UdpConnection var1) { return true; }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
