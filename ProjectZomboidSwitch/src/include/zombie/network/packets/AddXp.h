#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/SandboxOptions.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/PacketValidator.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/network/Userlog/UserlogType.h"
#include "zombie/network/packets/hit/Perk.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {


class AddXp {
public:
    const PlayerID target = std::make_shared<PlayerID>();
    Perk perk = std::make_shared<Perk>();
    int amount = 0;

    void set(IsoPlayer var1, zombie.characters.skills.PerkFactory.Perk var2, int var3) {
      this.target.set(var1);
      this.perk.set(var2);
      this.amount = var3;
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.target.parse(var1, var2);
      this.target.parsePlayer(var2);
      this.perk.parse(var1, var2);
      this.amount = var1.getInt();
   }

    void write(ByteBufferWriter var1) {
      this.target.write(var1);
      this.perk.write(var1);
      var1.putInt(this.amount);
   }

    void process() {
      if (this.target.player != nullptr && !this.target.player.isDead()) {
         if (this.target.getCharacter() != nullptr && !this.target.getCharacter().isDead()) {
            this.target.getCharacter().getXp().AddXP(this.perk.getPerk(), this.amount, false, false, true);
         }
      }
   }

    bool isConsistent() {
      return this.target.isConsistent() && this.perk.isConsistent();
   }

    bool validate(UdpConnection var1) {
      if (var1.accessLevel != 1 && var1.accessLevel != 2) {
    return true;
      } else if (!var1.havePlayer(this.target.getCharacter())) {
         if (ServerOptions.instance.AntiCheatProtectionType14.getValue() && PacketValidator.checkUser(var1)) {
            PacketValidator.doKickUser(var1, this.getClass().getSimpleName(), "Type14", nullptr);
         }

    return false;
      } else if (this.amount
         > 1000.0 * SandboxOptions.instance.XpMultiplier.getValue() * ServerOptions.instance.AntiCheatProtectionType15ThresholdMultiplier.getValue()) {
         if (ServerOptions.instance.AntiCheatProtectionType15.getValue() && PacketValidator.checkUser(var1)) {
            PacketValidator.doKickUser(var1, this.getClass().getSimpleName(), "Type15", nullptr);
         }

    return false;
      } else {
         if (this.amount
            > 1000.0 * SandboxOptions.instance.XpMultiplier.getValue() * ServerOptions.instance.AntiCheatProtectionType15ThresholdMultiplier.getValue() / 2.0) {
            LoggerManager.getLogger("user")
               .write(std::string.format("Warning: player=\"%s\" type=\"%s\" issuer=\"%s\"", var1.username, "Type15", this.getClass().getSimpleName()));
            PacketValidator.doLogUser(var1, UserlogType.SuspiciousActivity, this.getClass().getSimpleName(), "Type15");
         }

    return true;
      }
   }

    std::string getDescription() {
    std::string var1 = "\n\t" + this.getClass().getSimpleName() + " [";
      var1 = var1 + "target=" + this.target.getDescription() + " | ";
      var1 = var1 + "perk=" + this.perk.getDescription() + " | ";
      return var1 + "amount=" + this.amount + "] ";
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
