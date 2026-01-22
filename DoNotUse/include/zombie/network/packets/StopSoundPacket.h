#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/network/packets/hit/MovingObject.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {


class StopSoundPacket {
public:
    MovingObject object = std::make_shared<MovingObject>();
    std::string name;
    bool trigger;

    void set(IsoMovingObject var1, const std::string& var2, bool var3) {
      this.object.setMovingObject(var1);
      this.name = var2;
      this.trigger = var3;
   }

    void process() {
    IsoMovingObject var1 = this.object.getMovingObject();
    IsoGameCharacter var2 = (IsoGameCharacter)Type.tryCastTo(var1, IsoGameCharacter.class);
      if (var2 != nullptr) {
         if (this.trigger) {
            var2.getEmitter().stopOrTriggerSoundByName(this.name);
         } else {
            var2.getEmitter().stopSoundByName(this.name);
         }
      } else {
    BaseVehicle var3 = (BaseVehicle)Type.tryCastTo(var1, BaseVehicle.class);
         if (var3 != nullptr) {
            if (this.trigger) {
               var3.getEmitter().stopOrTriggerSoundByName(this.name);
            } else {
               var3.getEmitter().stopSoundByName(this.name);
            }
         }
      }
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.trigger = var1.get() == 1;
      this.object.parse(var1, var2);
      this.name = GameWindow.ReadString(var1);
   }

    void write(ByteBufferWriter var1) {
      var1.putByte((byte)(this.trigger ? 1 : 0));
      this.object.write(var1);
      var1.putUTF(this.name);
   }

    int getPacketSizeBytes() {
      return this.object.getPacketSizeBytes() + 2 + this.name.length();
   }

    std::string getDescription() {
      return "\n\tStopSoundPacket [name=" + this.name + " | object=" + this.object.getDescription() + "]";
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
