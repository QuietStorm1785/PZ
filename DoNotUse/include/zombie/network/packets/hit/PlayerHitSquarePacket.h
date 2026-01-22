#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/network/packets/INetworkPacket.h"
#include "zombie/network/packets/hit/HitCharacterPacket/HitType.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class PlayerHitSquarePacket : public PlayerHitPacket {
public:
    const Square square = std::make_shared<Square>();

    public PlayerHitSquarePacket() {
      super(HitType.PlayerHitSquare);
   }

    void set(IsoPlayer var1, HandWeapon var2, bool var3) {
      super.set(var1, var2, var3);
      this.square.set(var1);
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      super.parse(var1, var2);
      this.square.parse(var1, var2);
   }

    void write(ByteBufferWriter var1) {
      super.write(var1);
      this.square.write(var1);
   }

    bool isRelevant(UdpConnection var1) {
      return this.wielder.isRelevant(var1);
   }

    bool isConsistent() {
      return super.isConsistent() && this.square.isConsistent();
   }

    std::string getDescription() {
      return super.getDescription() + "\n\tSquare " + this.square.getDescription();
   }

    void process() {
      this.square.process(this.wielder.getCharacter());
   }

    bool validate(UdpConnection var1) {
    return true;
   }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
