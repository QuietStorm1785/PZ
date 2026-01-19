#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODSoundEmitter.h"
#include "zombie/audio/ObjectAmbientEmitters/PerObjectLogic.h"
#include "zombie/core/Core.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace audio {


class ObjectAmbientEmitters {
:
    IsoObject object = nullptr;
    PerObjectLogic logic = nullptr;
    BaseSoundEmitter emitter = nullptr;
    long instance = 0L;
    bool playing = false;

    void playSound(IsoObject var1, PerObjectLogic var2) {
      if (this.emitter == nullptr) {
         this.emitter = (BaseSoundEmitter)(Core.SoundDisabled ? std::make_unique<DummySoundEmitter>() : std::make_unique<FMODSoundEmitter>());
      }

      var1.getFacingPosition(ObjectAmbientEmitters.tempVector2);
      this.emitter.setPos(ObjectAmbientEmitters.tempVector2.getX(), ObjectAmbientEmitters.tempVector2.getY(), var1.square.z);
      this.object = var1;
      this.logic = var2;
    std::string var3 = var2.getSoundName();
      if (!this.emitter.isPlaying(var3)) {
         this.emitter.stopAll();
    FMODSoundEmitter var4 = (FMODSoundEmitter)Type.tryCastTo(this.emitter, FMODSoundEmitter.class);
         if (var4 != nullptr) {
            var4.clearParameters();
         }

         this.instance = this.emitter.playSoundImpl(var3, (IsoObject)nullptr);
         var2.startPlaying(this.emitter, this.instance);
      }

      var2.checkParameters(this.emitter, this.instance);
      this.playing = true;
      this.emitter.tick();
   }

    void stopPlaying() {
      if (this.emitter != nullptr && this.instance != 0L) {
         this.logic.stopPlaying(this.emitter, this.instance);
         if (this.emitter.hasSustainPoints(this.instance)) {
            this.emitter.triggerCue(this.instance);
            this.instance = 0L;
         } else {
            this.emitter.stopAll();
            this.instance = 0L;
         }
      }
   }
}
} // namespace audio
} // namespace zombie
