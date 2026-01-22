#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameServer.h"
#include "zombie/radio/ZomboidRadio.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {


class WaveSignal {
public:
    int sourceX;
    int sourceY;
    int channel;
    std::string msg;
    std::string guid;
    std::string codes;
    float r;
    float g;
    float b;
    int signalStrength;
    bool isTV;

    void set(int var1, int var2, int var3, const std::string& var4, const std::string& var5, const std::string& var6, float var7, float var8, float var9, int var10, bool var11) {
      this.sourceX = var1;
      this.sourceY = var2;
      this.channel = var3;
      this.msg = var4;
      this.guid = var5;
      this.codes = var6;
      this.r = var7;
      this.g = var8;
      this.b = var9;
      this.signalStrength = var10;
      this.isTV = var11;
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.sourceX = var1.getInt();
      this.sourceY = var1.getInt();
      this.channel = var1.getInt();
      this.msg = nullptr;
      if (var1.get() == 1) {
         this.msg = GameWindow.ReadString(var1);
      }

      this.guid = nullptr;
      if (var1.get() == 1) {
         this.guid = GameWindow.ReadString(var1);
      }

      this.codes = nullptr;
      if (var1.get() == 1) {
         this.codes = GameWindow.ReadString(var1);
      }

      this.r = var1.getFloat();
      this.g = var1.getFloat();
      this.b = var1.getFloat();
      this.signalStrength = var1.getInt();
      this.isTV = var1.get() == 1;
   }

    void write(ByteBufferWriter var1) {
      var1.putInt(this.sourceX);
      var1.putInt(this.sourceY);
      var1.putInt(this.channel);
      var1.putBoolean(this.msg != nullptr);
      if (this.msg != nullptr) {
         var1.putUTF(this.msg);
      }

      var1.putBoolean(this.guid != nullptr);
      if (this.guid != nullptr) {
         var1.putUTF(this.guid);
      }

      var1.putBoolean(this.codes != nullptr);
      if (this.codes != nullptr) {
         var1.putUTF(this.codes);
      }

      var1.putFloat(this.r);
      var1.putFloat(this.g);
      var1.putFloat(this.b);
      var1.putInt(this.signalStrength);
      var1.putBoolean(this.isTV);
   }

    void process(UdpConnection var1) {
      if (GameServer.bServer) {
         ZomboidRadio.getInstance()
            .SendTransmission(
               var1.getConnectedGUID(),
               this.sourceX,
               this.sourceY,
               this.channel,
               this.msg,
               this.guid,
               this.codes,
               this.r,
               this.g,
               this.b,
               this.signalStrength,
               this.isTV
            );
      } else {
         ZomboidRadio.getInstance()
            .ReceiveTransmission(
               this.sourceX, this.sourceY, this.channel, this.msg, this.guid, this.codes, this.r, this.g, this.b, this.signalStrength, this.isTV
            );
      }
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
