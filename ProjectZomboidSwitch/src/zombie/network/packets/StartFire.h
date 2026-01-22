#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoFire.h"
#include "zombie/iso/objects/IsoFireManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketValidator.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/network/packets/hit/Square.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {


class StartFire {
public:
    const Square square = std::make_shared<Square>();
    int fireEnergy;
    bool ignite;
    int life;
    bool smoke;
    int spreadDelay;
    int numParticles;

    void set(IsoGridSquare var1, bool var2, int var3, int var4, bool var5) {
      this.square.set(var1);
      this.fireEnergy = var3;
      this.ignite = var2;
      this.life = var4;
      this.smoke = var5;
      this.spreadDelay = 0;
      this.numParticles = 0;
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.square.parse(var1, var2);
      this.fireEnergy = var1.getInt();
      this.ignite = var1.get() == 1;
      this.life = var1.getInt();
      this.smoke = var1.get() == 1;
      if (GameClient.bClient) {
         this.spreadDelay = var1.getInt();
         this.numParticles = var1.getInt();
      }
   }

    void write(ByteBufferWriter var1) {
      this.square.write(var1);
      var1.putInt(this.fireEnergy);
      var1.putBoolean(this.ignite);
      var1.putInt(this.life);
      var1.putBoolean(this.smoke);
      if (GameServer.bServer) {
         var1.putInt(this.spreadDelay);
         var1.putInt(this.numParticles);
      }
   }

    void process() {
      if (GameServer.bServer) {
         IsoFire var1 = this.smoke
            ? std::make_shared<IsoFire>(this.square.getSquare().getCell(), this.square.getSquare(), this.ignite, this.fireEnergy, this.life, true)
            : std::make_shared<IsoFire>(this.square.getSquare().getCell(), this.square.getSquare(), this.ignite, this.fireEnergy, this.life);
         IsoFireManager.Add(var1);
         this.spreadDelay = var1.getSpreadDelay();
         this.numParticles = var1.numFlameParticles;
         this.square.getSquare().getObjects().push_back(var1);
      }

      if (GameClient.bClient) {
         IsoFire var2 = this.smoke
            ? std::make_shared<IsoFire>(IsoWorld.instance.CurrentCell, this.square.getSquare(), this.ignite, this.fireEnergy, this.life, true)
            : std::make_shared<IsoFire>(IsoWorld.instance.CurrentCell, this.square.getSquare(), this.ignite, this.fireEnergy, this.life);
         var2.SpreadDelay = this.spreadDelay;
         var2.numFlameParticles = this.numParticles;
         IsoFireManager.Add(var2);
         this.square.getSquare().getObjects().push_back(var2);
      }
   }

    bool isConsistent() {
      return this.square.getSquare() != nullptr && this.life <= 500;
   }

    bool validate(UdpConnection var1) {
      if (GameServer.bServer && !this.smoke && ServerOptions.instance.NoFire.getValue()) {
         if (ServerOptions.instance.AntiCheatProtectionType16.getValue() && PacketValidator.checkUser(var1)) {
            PacketValidator.doKickUser(var1, this.getClass().getSimpleName(), "Type16", this.getDescription());
         }

    return false;
      } else if (!this.smoke && !IsoFire.CanAddFire(this.square.getSquare(), this.ignite, this.smoke)) {
         DebugLog.log("not adding fire that on " + this.square.getX() + "," + this.square.getY());
         if (ServerOptions.instance.AntiCheatProtectionType17.getValue() && PacketValidator.checkUser(var1)) {
            PacketValidator.doKickUser(var1, this.getClass().getSimpleName(), "Type17", this.getDescription());
         }

    return false;
      } else if (this.smoke && !IsoFire.CanAddSmoke(this.square.getSquare(), this.ignite)) {
         if (ServerOptions.instance.AntiCheatProtectionType18.getValue() && PacketValidator.checkUser(var1)) {
            PacketValidator.doKickUser(var1, this.getClass().getSimpleName(), "Type18", this.getDescription());
         }

    return false;
      } else {
         return GameClient.bClient || var1.RelevantTo(this.square.getX(), this.square.getY());
      }
   }

    std::string getDescription() {
    std::string var1 = "\n\t" + this.getClass().getSimpleName() + " [";
      var1 = var1 + "square=" + this.square.getDescription() + " | ";
      var1 = var1 + "fireEnergy=" + this.fireEnergy + " | ";
      var1 = var1 + "ignite=" + this.ignite + " | ";
      var1 = var1 + "life=" + this.life + " | ";
      var1 = var1 + "smoke=" + this.smoke + " | ";
      var1 = var1 + "spreadDelay=" + this.spreadDelay + " | ";
      return var1 + "numParticles=" + this.numParticles + "] ";
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
