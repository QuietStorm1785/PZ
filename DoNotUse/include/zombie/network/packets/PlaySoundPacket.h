#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/characters/BaseCharacterSoundEmitter.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/packets/hit/MovingObject.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {


class PlaySoundPacket {
public:
    std::string name;
    MovingObject object = std::make_shared<MovingObject>();
    bool loop;

    void set(const std::string& var1, bool var2, IsoMovingObject var3) {
      this.name = var1;
      this.loop = var2;
      this.object.setMovingObject(var3);
   }

    void process() {
    IsoMovingObject var1 = this.object.getMovingObject();
      if (dynamic_cast<IsoGameCharacter*>(var1) != nullptr) {
    BaseCharacterSoundEmitter var2 = ((IsoGameCharacter)var1).getEmitter();
         if (!this.loop) {
            var2.playSoundImpl(this.name, (IsoObject)nullptr);
         }
      } else if (var1 != nullptr) {
    BaseSoundEmitter var3 = var1.emitter;
         if (var3 == nullptr) {
            var3 = IsoWorld.instance.getFreeEmitter(var1.x, var1.y, var1.z);
            IsoWorld.instance.takeOwnershipOfEmitter(var3);
            var1.emitter = var3;
         }

         if (!this.loop) {
            var3.playSoundImpl(this.name, (IsoObject)nullptr);
         } else {
            var3.playSoundLoopedImpl(this.name);
         }

         var3.tick();
      }
   }

    std::string getName() {
      return this.name;
   }

    IsoMovingObject getMovingObject() {
      return this.object.getMovingObject();
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.object.parse(var1, var2);
      this.name = GameWindow.ReadString(var1);
      this.loop = var1.get() == 1;
   }

    void write(ByteBufferWriter var1) {
      this.object.write(var1);
      var1.putUTF(this.name);
      var1.putByte((byte)(this.loop ? 1 : 0));
   }

    bool isConsistent() {
      return this.name != nullptr && !this.name.empty();
   }

    int getPacketSizeBytes() {
      return 12 + this.name.length();
   }

    std::string getDescription() {
      return "\n\tPlaySoundPacket [name=" + this.name + " | object=" + this.object.getDescription() + " | loop=" + this.loop + " ]";
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
