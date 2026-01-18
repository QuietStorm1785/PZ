#pragma once
#include "fmod/javafmod.h"
#include "zombie/SoundManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/iso/Vector3.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace fmod {
namespace fmod {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SoundListener : public BaseSoundListener {
public:
  float lx;
  float ly;
  float lz;
  static const Vector3 vec = new Vector3();

public
  SoundListener(int int0) { super(int0); }

  void tick() {
    if (!GameServer.bServer) {
      int int0 = 0;

      for (int int1 = 0; int1 < IsoPlayer.numPlayers && int1 != this.index;
           int1++) {
        if (IsoPlayer.players[int1] != nullptr) {
          int0++;
        }
      }

      vec.x = -1.0F;
      vec.y = -1.0F;
      vec.normalize();
      if (IsoPlayer.players[this.index] != nullptr &&
          IsoPlayer.players[this.index].Traits.Deaf.isSet()) {
        this.x = -1000.0F;
        this.y = -1000.0F;
        this.z = 0.0F;
      }

      this.lx = this.x;
      this.ly = this.y;
      this.lz = this.z;
      if (!GameClient.bClient ||
          SoundManager.instance.getSoundVolume() > 0.0F) {
        javafmod.FMOD_Studio_Listener3D(int0, this.x, this.y, this.z * 3.0F,
                                        this.x - this.lx, this.y - this.ly,
                                        this.z - this.lz, vec.x, vec.y, vec.z,
                                        0.0F, 0.0F, 1.0F);
      }

      this.lx = this.x;
      this.ly = this.y;
      this.lz = this.z;
    }
  }
}
} // namespace fmod
} // namespace fmod
