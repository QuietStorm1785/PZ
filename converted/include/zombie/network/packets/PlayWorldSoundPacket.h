#pragma once
#include "zombie/GameWindow.h"
#include "zombie/SoundManager.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
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

class PlayWorldSoundPacket {
public:
  std::string name;
  int x;
  int y;
  uint8_t z;

  void set(const std::string &string, int int0, int int1, uint8_t byte0) {
    this.name = string;
    this.x = int0;
    this.y = int1;
    this.z = byte0;
  }

  void process() {
    SoundManager.instance.PlayWorldSoundImpl(this.name, false, this.x, this.y,
                                             this.z, 1.0F, 20.0F, 2.0F, false);
  }

  std::string getName() { return this.name; }

  int getX() { return this.x; }

  int getY() { return this.y; }

  void parse(ByteBuffer byteBuffer, UdpConnection var2) {
    this.x = byteBuffer.getInt();
    this.y = byteBuffer.getInt();
    this.z = byteBuffer.get();
    this.name = GameWindow.ReadString(byteBuffer);
  }

  void write(ByteBufferWriter byteBufferWriter) {
    byteBufferWriter.putInt(this.x);
    byteBufferWriter.putInt(this.y);
    byteBufferWriter.putByte(this.z);
    byteBufferWriter.putUTF(this.name);
  }

  bool isConsistent() { return this.name != nullptr && !this.name.isEmpty(); }

  int getPacketSizeBytes() { return 12 + this.name.length(); }

  std::string getDescription() {
    return "\n\tPlayWorldSoundPacket [name=" + this.name + " | x=" + this.x +
           " | y=" + this.y + " | z=" + this.z + " ]";
  }
}
} // namespace packets
} // namespace network
} // namespace zombie
