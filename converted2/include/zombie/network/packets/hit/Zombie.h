#pragma once
#include "zombie/GameWindow.h"
#include "zombie/PersistentOutfits.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerGUI.h"
#include "zombie/network/ServerMap.h"
#include "zombie/network/packets/INetworkPacket.h"
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
namespace hit {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Zombie : public Character {
public:
  IsoZombie zombie;
  short zombieFlags;
  std::string attackOutcome;
  std::string attackPosition;

  void set(IsoZombie zombie1, bool boolean0) {
    super.set(zombie1);
    this.zombie = zombie1;
    this.zombieFlags = 0;
    this.zombieFlags =
        (short)(this.zombieFlags | (short)(zombie1.isStaggerBack() ? 1 : 0));
    this.zombieFlags =
        (short)(this.zombieFlags | (short)(zombie1.isFakeDead() ? 2 : 0));
    this.zombieFlags =
        (short)(this.zombieFlags | (short)(zombie1.isBecomeCrawler() ? 4 : 0));
    this.zombieFlags =
        (short)(this.zombieFlags | (short)(zombie1.isCrawling() ? 8 : 0));
    this.zombieFlags =
        (short)(this.zombieFlags | (short)(zombie1.isKnifeDeath() ? 16 : 0));
    this.zombieFlags =
        (short)(this.zombieFlags | (short)(zombie1.isJawStabAttach() ? 32 : 0));
    this.zombieFlags |= (short)(boolean0 ? 64 : 0);
    this.zombieFlags =
        (short)(this.zombieFlags |
                (short)(zombie1.getVariableBoolean("AttackDidDamage") ? 128
                                                                      : 0));
    this.attackOutcome = zombie1.getVariableString("AttackOutcome");
    this.attackPosition = zombie1.getPlayerAttackPosition();
  }

  void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
    super.parse(byteBuffer, udpConnection);
    this.zombieFlags = byteBuffer.getShort();
    this.attackOutcome = GameWindow.ReadString(byteBuffer);
    this.attackPosition = GameWindow.ReadString(byteBuffer);
    if (GameServer.bServer) {
      this.zombie = ServerMap.instance.ZombieMap.get(this.ID);
      this.character = this.zombie;
    } else if (GameClient.bClient) {
      this.zombie = GameClient.IDToZombieMap.get(this.ID);
      this.character = this.zombie;
    }
  }

  void write(ByteBufferWriter byteBufferWriter) {
    super.write(byteBufferWriter);
    byteBufferWriter.putShort(this.zombieFlags);
    byteBufferWriter.putUTF(this.attackOutcome);
    byteBufferWriter.putUTF(this.attackPosition);
  }

  bool isConsistent() { return super.isConsistent() && this.zombie != nullptr; }

  std::string getDescription() {
    return super.getDescription() +
           "\n\tZombie [attack-position=" + this.attackPosition +
           " | isStaggerBack=" + ((this.zombieFlags & 1) != 0) +
           " | isFakeDead=" + ((this.zombieFlags & 2) != 0) +
           " | isBecomeCrawler=" + ((this.zombieFlags & 4) != 0) +
           " | isCrawling=" + ((this.zombieFlags & 8) != 0) +
           " | isKnifeDeath=" + ((this.zombieFlags & 16) != 0) +
           " | isJawStabAttach=" + ((this.zombieFlags & 32) != 0) +
           " | isHelmetFall=" + ((this.zombieFlags & 64) != 0) +
           " | attackDidDamage=" + ((this.zombieFlags & 128) != 0) +
           " | attack-outcome=" + this.attackOutcome + " ]";
  }

  void process() {
    super.process();
    this.zombie.setVariable("AttackOutcome", this.attackOutcome);
    this.zombie.setPlayerAttackPosition(this.attackPosition);
    this.zombie.setStaggerBack((this.zombieFlags & 1) != 0);
    this.zombie.setFakeDead((this.zombieFlags & 2) != 0);
    this.zombie.setBecomeCrawler((this.zombieFlags & 4) != 0);
    this.zombie.setCrawler((this.zombieFlags & 8) != 0);
    this.zombie.setKnifeDeath((this.zombieFlags & 16) != 0);
    this.zombie.setJawStabAttach((this.zombieFlags & 32) != 0);
    this.zombie.setVariable("AttackDidDamage", (this.zombieFlags & 128) != 0);
  }

  void react(HandWeapon weapon) {
    if (this.zombie.isJawStabAttach()) {
      this.zombie.setAttachedItem("JawStab", weapon);
    }

    if (GameServer.bServer && (this.zombieFlags & 64) != 0 &&
        !PersistentOutfits.instance.isHatFallen(this.zombie)) {
      PersistentOutfits.instance.setFallenHat(this.zombie, true);
      if (ServerGUI.isCreated()) {
        PersistentOutfits.instance.removeFallenHat(
            this.zombie.getPersistentOutfitID(), this.zombie);
        ModelManager.instance.ResetNextFrame(this.zombie);
      }
    }

    this.react();
  }

  IsoGameCharacter getCharacter() { return this.zombie; }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
