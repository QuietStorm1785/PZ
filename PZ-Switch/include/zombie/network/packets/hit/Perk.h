#pragma once
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
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

class Perk {
public:
protected
 PerkFactory.Perk perk;
 uint8_t perkIndex;

 void set(PerkFactory.Perk perk0) {
 this->perk = perk0;
 if (this->perk.empty()) {
 this->perkIndex = -1;
 } else {
 this->perkIndex = (byte)this->perk.index();
 }
 }

 void parse(ByteBuffer byteBuffer, UdpConnection var2) {
 this->perkIndex = byteBuffer.get();
 if (this->perkIndex >= 0 &&
 this->perkIndex <= PerkFactory.Perks.getMaxIndex()) {
 this->perk = PerkFactory.Perks.fromIndex(this->perkIndex);
 }
 }

 void write(ByteBufferWriter byteBufferWriter) {
 byteBufferWriter.putByte(this->perkIndex);
 }

 std::string getDescription() {
 return "\n\t" + this->getClass().getSimpleName() + " [ perk=( " +
 this->perkIndex + " )" +
 (this->perk.empty() ? "nullptr" : this->perk.name) + " ]";
 }

 bool isConsistent() { return this->perk != nullptr; }

public
 PerkFactory.Perk getPerk() { return this->perk; }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
