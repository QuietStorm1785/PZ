#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/SoundManager.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {


class PlayWorldSoundPacket {
public:
    std::string name;
    int x;
    int y;
    uint8_t z;

    void set(const std::string& var1, int var2, int var3, uint8_t var4) {
      this.name = var1;
      this.x = var2;
      this.y = var3;
      this.z = var4;
   }

    void process() {
      SoundManager.instance.PlayWorldSoundImpl(this.name, false, this.x, this.y, this.z, 1.0F, 20.0F, 2.0F, false);
   }

    std::string getName() {
      return this.name;
   }

    int getX() {
      return this.x;
   }

    int getY() {
      return this.y;
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.x = var1.getInt();
      this.y = var1.getInt();
      this.z = var1.get();
      this.name = GameWindow.ReadString(var1);
   }

    void write(ByteBufferWriter var1) {
      var1.putInt(this.x);
      var1.putInt(this.y);
      var1.putByte(this.z);
      var1.putUTF(this.name);
   }

    bool isConsistent() {
      return this.name != nullptr && !this.name.empty();
   }

    int getPacketSizeBytes() {
      return 12 + this.name.length();
   }

    std::string getDescription() {
      return "\n\tPlayWorldSoundPacket [name=" + this.name + " | x=" + this.x + " | y=" + this.y + " | z=" + this.z + " ]";
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
