#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODSoundEmitter.h"

namespace zombie {


class AmbientStreamManager {
:
    static float volChangeAmount = 0.01F;
    float targVol;
    float currVol;
    std::string name;
    float volumedelta = 1.0F;
    long channel = -1L;
    const FMODSoundEmitter emitter = new FMODSoundEmitter();

    AmbientStreamManager$AmbientLoop(float var1, String var2, float var3) {
      this.volumedelta = var3;
      this.channel = this.emitter.playAmbientLoopedImpl(var2);
      this.targVol = var1;
      this.currVol = 0.0F;
      this.update();
   }

    void update() {
      if (this.targVol > this.currVol) {
         this.currVol = this.currVol + volChangeAmount;
         if (this.currVol > this.targVol) {
            this.currVol = this.targVol;
         }
      }

      if (this.targVol < this.currVol) {
         this.currVol = this.currVol - volChangeAmount;
         if (this.currVol < this.targVol) {
            this.currVol = this.targVol;
         }
      }

      this.emitter.setVolumeAll(this.currVol * this.volumedelta);
      this.emitter.tick();
   }

    void stop() {
      this.emitter.stopAll();
   }
}
} // namespace zombie
