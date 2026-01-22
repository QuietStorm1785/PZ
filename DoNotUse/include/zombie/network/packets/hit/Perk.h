#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/packets/INetworkPacket.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class Perk {
public:
   protected zombie.characters.skills.PerkFactory.Perk perk;
    uint8_t perkIndex;

    void set(zombie.characters.skills.PerkFactory.Perk var1) {
      this.perk = var1;
      if (this.perk == nullptr) {
         this.perkIndex = -1;
      } else {
         this.perkIndex = (byte)this.perk.index();
      }
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.perkIndex = var1.get();
      if (this.perkIndex >= 0 && this.perkIndex <= Perks.getMaxIndex()) {
         this.perk = Perks.fromIndex(this.perkIndex);
      }
   }

    void write(ByteBufferWriter var1) {
      var1.putByte(this.perkIndex);
   }

    std::string getDescription() {
      return "\n\t" + this.getClass().getSimpleName() + " [ perk=( " + this.perkIndex + " )" + (this.perk == nullptr ? "nullptr" : this.perk.name) + " ]";
   }

    bool isConsistent() {
      return this.perk != nullptr;
   }

   public zombie.characters.skills.PerkFactory.Perk getPerk() {
      return this.perk;
   }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
