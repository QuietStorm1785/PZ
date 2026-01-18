#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/SandboxOptions.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/PacketValidator.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/network/Userlog.h"
#include "zombie/network/packets/hit/Perk.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class AddXp {
public:
 const PlayerID target = new PlayerID();
 Perk perk = new Perk();
 int amount = 0;

 void set(IsoPlayer player, PerkFactory.Perk perkx, int int0) {
 this->target.set(player);
 this->perk.set(perkx);
 this->amount = int0;
 }

 void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 this->target.parse(byteBuffer, udpConnection);
 this->target.parsePlayer(udpConnection);
 this->perk.parse(byteBuffer, udpConnection);
 this->amount = byteBuffer.getInt();
 }

 void write(ByteBufferWriter byteBufferWriter) {
 this->target.write(byteBufferWriter);
 this->perk.write(byteBufferWriter);
 byteBufferWriter.putInt(this->amount);
 }

 void process() {
 if (this->target.player != nullptr && !this->target.player.isDead()) {
 if (this->target.getCharacter() != nullptr && !this->target.getCharacter().isDead()) {
 this->target.getCharacter().getXp().AddXP(this->perk.getPerk(), this->amount, false, false, true);
 }
 }
 }

 bool isConsistent() {
 return this->target.isConsistent() && this->perk.isConsistent();
 }

 bool validate(UdpConnection udpConnection) {
 if (udpConnection.accessLevel != 1 && udpConnection.accessLevel != 2) {
 return true;
 } else if (!udpConnection.havePlayer(this->target.getCharacter())) {
 if (ServerOptions.instance.AntiCheatProtectionType14.getValue() && PacketValidator.checkUser(udpConnection) {
 PacketValidator.doKickUser(udpConnection, this->getClass().getSimpleName(), "Type14", nullptr);
 }

 return false;
 } else if (this->amount
 > 1000.0 * SandboxOptions.instance.XpMultiplier.getValue() * ServerOptions.instance.AntiCheatProtectionType15ThresholdMultiplier.getValue()) {
 if (ServerOptions.instance.AntiCheatProtectionType15.getValue() && PacketValidator.checkUser(udpConnection) {
 PacketValidator.doKickUser(udpConnection, this->getClass().getSimpleName(), "Type15", nullptr);
 }

 return false;
 } else {
 if (this->amount
 > 1000.0
 * SandboxOptions.instance.XpMultiplier.getValue()
 * ServerOptions.instance.AntiCheatProtectionType15ThresholdMultiplier.getValue()
 / 2.0) {
 LoggerManager.getLogger("user")
 .write(String.format("Warning: player=\"%s\" type=\"%s\" issuer=\"%s\"", udpConnection.username, "Type15", this->getClass().getSimpleName()));
 PacketValidator.doLogUser(udpConnection, Userlog.UserlogType.SuspiciousActivity, this->getClass().getSimpleName(), "Type15");
 }

 return true;
 }
 }

 std::string getDescription() {
 std::string string = "\n\t" + this->getClass().getSimpleName() + " [";
 string = string + "target=" + this->target.getDescription() + " | ";
 string = string + "perk=" + this->perk.getDescription() + " | ";
 return string + "amount=" + this->amount + "] ";
 }
}
} // namespace packets
} // namespace network
} // namespace zombie
