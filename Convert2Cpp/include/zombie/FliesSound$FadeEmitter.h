#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/iso/IsoGridSquare.h"

namespace zombie {


class FliesSound {
public:
    static const float FADE_IN_RATE = 0.01F;
    static const float FADE_OUT_RATE = -0.01F;
    BaseSoundEmitter emitter;
    float volume;
    float targetVolume;
    IsoGridSquare sq;

   private FliesSound$FadeEmitter(FliesSound var1) {
      this.this$0 = var1;
      this.emitter = nullptr;
      this.volume = 1.0F;
      this.targetVolume = 1.0F;
      this.sq = nullptr;
   }

    bool update() {
      if (this.emitter == nullptr) {
    return true;
      } else {
         if (this.volume < this.targetVolume) {
            this.volume = this.volume + 0.01F * (GameTime.getInstance().getMultiplier() / 1.6F);
            if (this.volume >= this.targetVolume) {
               this.volume = this.targetVolume;
    return true;
            }
         } else {
            this.volume = this.volume + -0.01F * (GameTime.getInstance().getMultiplier() / 1.6F);
            if (this.volume <= 0.0F) {
               this.volume = 0.0F;
               this.emitter.stopAll();
               this.emitter = nullptr;
    return true;
            }
         }

         this.emitter.setVolumeAll(this.volume);
    return false;
      }
   }

    void Reset() {
      this.emitter = nullptr;
      this.volume = 1.0F;
      this.targetVolume = 1.0F;
      this.sq = nullptr;
   }
}
} // namespace zombie
