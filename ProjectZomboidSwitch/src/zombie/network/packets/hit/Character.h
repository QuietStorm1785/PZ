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
#include "zombie/network/GameServer.h"
#include "zombie/network/packets/INetworkPacket.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class char : public Instance {
public:
    IsoGameCharacter character;
    short characterFlags;
    float positionX;
    float positionY;
    float positionZ;
    float directionX;
    float directionY;
    std::string characterReaction;
    std::string playerReaction;
    std::string zombieReaction;

    void set(IsoGameCharacter var1) {
      super.set(var1.getOnlineID());
      this.characterFlags = 0;
      this.characterFlags = (short)(this.characterFlags | (short)(var1.isDead() ? 1 : 0));
      this.characterFlags = (short)(this.characterFlags | (short)(var1.isCloseKilled() ? 2 : 0));
      this.characterFlags = (short)(this.characterFlags | (short)(var1.isHitFromBehind() ? 4 : 0));
      this.characterFlags = (short)(this.characterFlags | (short)(var1.isFallOnFront() ? 8 : 0));
      this.characterFlags = (short)(this.characterFlags | (short)(var1.isKnockedDown() ? 16 : 0));
      this.characterFlags = (short)(this.characterFlags | (short)(var1.isOnFloor() ? 32 : 0));
      this.character = var1;
      this.positionX = var1.getX();
      this.positionY = var1.getY();
      this.positionZ = var1.getZ();
      this.directionX = var1.getForwardDirection().getX();
      this.directionY = var1.getForwardDirection().getY();
      this.characterReaction = Optional.ofNullable(var1.getHitReaction()).orElse("");
      this.playerReaction = Optional.ofNullable(var1.getVariableString("PlayerHitReaction")).orElse("");
      this.zombieReaction = Optional.ofNullable(var1.getVariableString("ZombieHitReaction")).orElse("");
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      super.parse(var1, var2);
      this.characterFlags = var1.getShort();
      this.positionX = var1.getFloat();
      this.positionY = var1.getFloat();
      this.positionZ = var1.getFloat();
      this.directionX = var1.getFloat();
      this.directionY = var1.getFloat();
      this.characterReaction = GameWindow.ReadString(var1);
      this.playerReaction = GameWindow.ReadString(var1);
      this.zombieReaction = GameWindow.ReadString(var1);
   }

    void write(ByteBufferWriter var1) {
      super.write(var1);
      var1.putShort(this.characterFlags);
      var1.putFloat(this.positionX);
      var1.putFloat(this.positionY);
      var1.putFloat(this.positionZ);
      var1.putFloat(this.directionX);
      var1.putFloat(this.directionY);
      var1.putUTF(this.characterReaction);
      var1.putUTF(this.playerReaction);
      var1.putUTF(this.zombieReaction);
   }

    bool isConsistent() {
      return super.isConsistent() && this.character != nullptr;
   }

    std::string getDescription() {
      return super.getDescription()
         + "\n\tCharacter [ hit-reactions=( \"c=\""
         + this.characterReaction
         + "\" ; p=\""
         + this.playerReaction
         + "\" ; z=\""
         + this.zombieReaction
         + "\" ) | "
         + this.getFlagsDescription()
         + " | pos=( "
         + this.positionX
         + " ; "
         + this.positionY
         + " ; "
         + this.positionZ
         + " ) | dir=( "
         + this.directionX
         + " ; "
         + this.directionY
         + " ) | health="
         + (this.character == nullptr ? "?" : this.character.getHealth())
         + " | current="
         + (this.character == nullptr ? "?" : "\"" + this.character.getCurrentActionContextStateName() + "\"")
         + " | previous="
         + (this.character == nullptr ? "?" : "\"" + this.character.getPreviousActionContextStateName() + "\"")
         + " ]";
   }

    std::string getFlagsDescription() {
      return " Flags [ isDead="
         + ((this.characterFlags & 1) != 0)
         + " | isKnockedDown="
         + ((this.characterFlags & 16) != 0)
         + " | isCloseKilled="
         + ((this.characterFlags & 2) != 0)
         + " | isHitFromBehind="
         + ((this.characterFlags & 4) != 0)
         + " | isFallOnFront="
         + ((this.characterFlags & 8) != 0)
         + " | isOnFloor="
         + ((this.characterFlags & 32) != 0)
         + " ]";
   }

    void process() {
      this.character.setHitReaction(this.characterReaction);
      this.character.setVariable("PlayerHitReaction", this.playerReaction);
      this.character.setVariable("ZombieHitReaction", this.zombieReaction);
      this.character.setCloseKilled((this.characterFlags & 2) != 0);
      this.character.setHitFromBehind((this.characterFlags & 4) != 0);
      this.character.setFallOnFront((this.characterFlags & 8) != 0);
      this.character.setKnockedDown((this.characterFlags & 16) != 0);
      this.character.setOnFloor((this.characterFlags & 32) != 0);
      if (GameServer.bServer && (this.characterFlags & 32) == 0 && (this.characterFlags & 4) != 0) {
         this.character.setFallOnFront(true);
      }
   }

    void react() {
   }

    float getX() {
      return this.positionX;
   }

    float getY() {
      return this.positionY;
   }

   public abstract IsoGameCharacter getCharacter();
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
