#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/characters/BodyDamage/BodyDamage.h"
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include <filesystem>

namespace zombie {
namespace network {


class BodyDamageSync {
public:
    static ByteBuffer bb = ByteBuffer.allocate(1024);
    short localIndex;
    short remoteID;
    BodyDamage bdLocal;
    BodyDamage bdSent;
    bool partStarted;
    uint8_t partIndex;
    long sendTime;

    void update() {
    long var1 = System.currentTimeMillis();
      if (var1 - this.sendTime >= 500L) {
         this.sendTime = var1;
         bb.clear();
    int var3 = this.bdLocal.getParentChar().getMoodles().getMoodleLevel(MoodleType.Pain);
         if (this.compareFloats(this.bdLocal.getOverallBodyHealth(), (int)this.bdSent.getOverallBodyHealth())
            || var3 != this.bdSent.getRemotePainLevel()
            || this.bdLocal.IsFakeInfected != this.bdSent.IsFakeInfected
            || this.compareFloats(this.bdLocal.InfectionLevel, this.bdSent.InfectionLevel)) {
            bb.put((byte)50);
            bb.putFloat(this.bdLocal.getOverallBodyHealth());
            bb.put((byte)var3);
            bb.put((byte)(this.bdLocal.IsFakeInfected ? 1 : 0));
            bb.putFloat(this.bdLocal.InfectionLevel);
            this.bdSent.setOverallBodyHealth(this.bdLocal.getOverallBodyHealth());
            this.bdSent.setRemotePainLevel(var3);
            this.bdSent.IsFakeInfected = this.bdLocal.IsFakeInfected;
            this.bdSent.InfectionLevel = this.bdLocal.InfectionLevel;
         }

         for (int var4 = 0; var4 < this.bdLocal.BodyParts.size(); var4++) {
            this.updatePart(var4);
         }

         if (bb.position() > 0) {
            bb.put((byte)65);
    ByteBufferWriter var5 = GameClient.connection.startPacket();
            PacketType.BodyDamageUpdate.doPacket(var5);
            var5.putByte((byte)3);
            var5.putShort(IsoPlayer.players[this.localIndex].getOnlineID());
            var5.putShort(this.remoteID);
            var5.bb.put(bb.array(), 0, bb.position());
            PacketType.BodyDamageUpdate.send(GameClient.connection);
         }
      }
   }

    void updatePart(int var1) {
    BodyPart var2 = (BodyPart)this.bdLocal.BodyParts.get(var1);
    BodyPart var3 = (BodyPart)this.bdSent.BodyParts.get(var1);
      this.partStarted = false;
      this.partIndex = (byte)var1;
      var2.sync(var3, this);
      if (this.partStarted) {
         bb.put((byte)65);
      }
   }

    void updateField(uint8_t var1, bool var2) {
      if (!this.partStarted) {
         bb.put((byte)64);
         bb.put(this.partIndex);
         this.partStarted = true;
      }

      bb.put(var1);
      bb.put((byte)(var2 ? 1 : 0));
   }

    bool compareFloats(float var1, float var2) {
      return float.compare(var1, 0.0F) != float.compare(var2, 0.0F) ? true : (int)var1 != (int)var2;
   }

    bool updateField(uint8_t var1, float var2, float var3) {
      if (!this.compareFloats(var2, var3)) {
    return false;
      } else {
         if (!this.partStarted) {
            bb.put((byte)64);
            bb.put(this.partIndex);
            this.partStarted = true;
         }

         bb.put(var1);
         bb.putFloat(var2);
    return true;
      }
   }

    void updateField(uint8_t var1, const std::string& var2) {
      if (!this.partStarted) {
         bb.put((byte)64);
         bb.put(this.partIndex);
         this.partStarted = true;
      }

      bb.put(var1);
      GameWindow.WriteStringUTF(bb, var2);
   }
}
} // namespace network
} // namespace zombie
