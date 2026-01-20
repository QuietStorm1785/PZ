#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/javafmod.h"
#include "zombie/SoundManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/iso/Vector3.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"

namespace fmod {
namespace fmod {


class SoundListener : public BaseSoundListener {
public:
    float lx;
    float ly;
    float lz;
    static const Vector3 vec = std::make_shared<Vector3>();

    public SoundListener(int var1) {
      super(var1);
   }

    void tick() {
      if (!GameServer.bServer) {
    int var1 = 0;

         for (int var2 = 0; var2 < IsoPlayer.numPlayers && var2 != this.index; var2++) {
            if (IsoPlayer.players[var2] != nullptr) {
               var1++;
            }
         }

         vec.x = -1.0F;
         vec.y = -1.0F;
         vec.normalize();
         if (IsoPlayer.players[this.index] != nullptr && IsoPlayer.players[this.index].Traits.Deaf.isSet()) {
            this.x = -1000.0F;
            this.y = -1000.0F;
            this.z = 0.0F;
         }

         this.lx = this.x;
         this.ly = this.y;
         this.lz = this.z;
         if (!GameClient.bClient || SoundManager.instance.getSoundVolume() > 0.0F) {
            javafmod.FMOD_Studio_Listener3D(
               var1, this.x, this.y, this.z * 3.0F, this.x - this.lx, this.y - this.ly, this.z - this.lz, vec.x, vec.y, vec.z, 0.0F, 0.0F, 1.0F
            );
         }

         this.lx = this.x;
         this.ly = this.y;
         this.lz = this.z;
      }
   }
}
} // namespace fmod
} // namespace fmod
