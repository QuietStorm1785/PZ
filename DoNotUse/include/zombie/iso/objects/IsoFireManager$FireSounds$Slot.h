#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODSoundEmitter.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/audio/DummySoundEmitter.h"
#include "zombie/audio/parameters/ParameterFireSize.h"
#include "zombie/core/Core.h"
#include "zombie/iso/IsoObject.h"

namespace zombie {
namespace iso {
namespace objects {


class IsoFireManager {
public:
    IsoFire fire;
    BaseSoundEmitter emitter;
    const ParameterFireSize parameterFireSize = std::make_shared<ParameterFireSize>();
    long instance = 0L;
    bool playing;

    void playSound(IsoFire var1) {
      if (this.emitter == nullptr) {
         this.emitter = (BaseSoundEmitter)(Core.SoundDisabled ? std::make_unique<DummySoundEmitter>() : std::make_unique<FMODSoundEmitter>());
         if (!Core.SoundDisabled) {
            ((FMODSoundEmitter)this.emitter).addParameter(this.parameterFireSize);
         }
      }

      this.emitter.setPos(var1.square.x + 0.5F, var1.square.y + 0.5F, var1.square.z);

      byte var2 = switch (var1.LifeStage) {
         case 1, 3 -> 1;
         case 2 -> 2;
         default -> 0;
      };
      this.parameterFireSize.setSize(var2);
      if (var1.isCampfire()) {
         if (!this.emitter.isPlaying("CampfireRunning")) {
            this.instance = this.emitter.playSoundImpl("CampfireRunning", (IsoObject)nullptr);
         }
      } else if (!this.emitter.isPlaying("Fire")) {
         this.instance = this.emitter.playSoundImpl("Fire", (IsoObject)nullptr);
      }

      this.fire = var1;
      this.playing = true;
      this.emitter.tick();
   }

    void stopPlaying() {
      if (this.emitter != nullptr && this.instance != 0L) {
         if (this.emitter.hasSustainPoints(this.instance)) {
            this.emitter.triggerCue(this.instance);
            this.instance = 0L;
         } else {
            this.emitter.stopAll();
            this.instance = 0L;
         }
      } else {
         if (this.emitter != nullptr && !this.emitter.empty()) {
            this.emitter.tick();
         }
      }
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
