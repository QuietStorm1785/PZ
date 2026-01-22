#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/BaseSoundEmitter.h"

namespace fmod {
namespace fmod {


class FMODAudio {
public:
    BaseSoundEmitter emitter;

    public FMODAudio(BaseSoundEmitter var1) {
      this.emitter = var1;
   }

    bool isPlaying() {
      return !this.emitter.empty();
   }

    void setVolume(float var1) {
      this.emitter.setVolumeAll(var1);
   }

    void start() {
   }

    void pause() {
   }

    void stop() {
      this.emitter.stopAll();
   }

    void setName(const std::string& var1) {
   }

    std::string getName() {
    return nullptr;
   }
}
} // namespace fmod
} // namespace fmod
