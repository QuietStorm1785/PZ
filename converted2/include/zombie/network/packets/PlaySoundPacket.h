#pragma once
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

class PlaySoundPacket {
public:
  std::string name;
  MovingObject object = std::make_unique<MovingObject>();
  bool loop;

  void set(const std::string &string, bool boolean0,
           IsoMovingObject movingObject) {
    this.name = string;
    this.loop = boolean0;
    this.object.setMovingObject(movingObject);
  }

  void process() {
    IsoMovingObject movingObject = this.object.getMovingObject();
    if (movingObject instanceof IsoGameCharacter) {
      BaseCharacterSoundEmitter baseCharacterSoundEmitter =
          ((IsoGameCharacter)movingObject).getEmitter();
      if (!this.loop) {
        baseCharacterSoundEmitter.playSoundImpl(this.name, (IsoObject) nullptr);
      }
    } else if (movingObject != nullptr) {
      BaseSoundEmitter baseSoundEmitter = movingObject.emitter;
      if (baseSoundEmitter == nullptr) {
        baseSoundEmitter = IsoWorld.instance.getFreeEmitter(
            movingObject.x, movingObject.y, movingObject.z);
        IsoWorld.instance.takeOwnershipOfEmitter(baseSoundEmitter);
        movingObject.emitter = baseSoundEmitter;
      }

      if (!this.loop) {
        baseSoundEmitter.playSoundImpl(this.name, (IsoObject) nullptr);
      } else {
        baseSoundEmitter.playSoundLoopedImpl(this.name);
      }

      baseSoundEmitter.tick();
    }
  }

  std::string getName() { return this.name; }

  IsoMovingObject getMovingObject() { return this.object.getMovingObject(); }

  void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
    this.object.parse(byteBuffer, udpConnection);
    this.name = GameWindow.ReadString(byteBuffer);
    this.loop = byteBuffer.get() == 1;
  }

  void write(ByteBufferWriter byteBufferWriter) {
    this.object.write(byteBufferWriter);
    byteBufferWriter.putUTF(this.name);
    byteBufferWriter.putByte((byte)(this.loop ? 1 : 0));
  }

  bool isConsistent() { return this.name != nullptr && !this.name.isEmpty(); }

  int getPacketSizeBytes() { return 12 + this.name.length(); }

  std::string getDescription() {
    return "\n\tPlaySoundPacket [name=" + this.name +
           " | object=" + this.object.getDescription() +
           " | loop=" + this.loop + " ]";
  }
}
} // namespace packets
} // namespace network
} // namespace zombie
