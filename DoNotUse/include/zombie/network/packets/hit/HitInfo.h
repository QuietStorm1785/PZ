#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/network/packets/INetworkPacket.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class HitInfo {
public:
    MovingObject object;
    NetObject window;
    float x;
    float y;
    float z;
    float dot;
    float distSq;
    int chance = 0;

    public HitInfo() {
      this.object = std::make_unique<MovingObject>();
      this.window = std::make_unique<NetObject>();
   }

    HitInfo init(IsoMovingObject var1, float var2, float var3, float var4, float var5, float var6) {
      this.object = std::make_unique<MovingObject>();
      this.window = std::make_unique<NetObject>();
      this.object.setMovingObject(var1);
      this.window.setObject(nullptr);
      this.x = var4;
      this.y = var5;
      this.z = var6;
      this.dot = var2;
      this.distSq = var3;
    return this;
   }

    HitInfo init(IsoWindow var1, float var2, float var3) {
      this.object = std::make_unique<MovingObject>();
      this.window = std::make_unique<NetObject>();
      this.object.setMovingObject(nullptr);
      this.window.setObject(var1);
      this.z = var1.getZ();
      this.dot = var2;
      this.distSq = var3;
    return this;
   }

    IsoMovingObject getObject() {
      return this.object.getMovingObject();
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.object.parse(var1, var2);
      this.window.parse(var1, var2);
      this.x = var1.getFloat();
      this.y = var1.getFloat();
      this.z = var1.getFloat();
      this.dot = var1.getFloat();
      this.distSq = var1.getFloat();
      this.chance = var1.getInt();
   }

    void write(ByteBufferWriter var1) {
      this.object.write(var1);
      this.window.write(var1);
      var1.putFloat(this.x);
      var1.putFloat(this.y);
      var1.putFloat(this.z);
      var1.putFloat(this.dot);
      var1.putFloat(this.distSq);
      var1.putInt(this.chance);
   }

    int getPacketSizeBytes() {
      return 24 + this.object.getPacketSizeBytes() + this.window.getPacketSizeBytes();
   }

    std::string getDescription() {
      return "\n\tHitInfo [ x="
         + this.x
         + " y="
         + this.y
         + " z="
         + this.z
         + " dot="
         + this.dot
         + " distSq="
         + this.distSq
         + " chance="
         + this.chance
         + "\n\t Object: "
         + this.object.getDescription()
         + "\n\t Window: "
         + this.window.getDescription()
         + " ]";
   }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
