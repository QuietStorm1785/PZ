#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_DESCRIPTION.h"
#include "zombie/SystemDisabler.h"
#include "zombie/audio/GameSound/MasterVolume.h"
#include "zombie/core/Rand.h"

namespace zombie {
namespace audio {


class GameSound {
:
    std::string name;
    std::string category = "General";
    bool loop = false;
    bool is3D = true;
    ArrayList<GameSoundClip> clips = std::make_unique<ArrayList<>>();
    float userVolume = 1.0F;
    MasterVolume master = MasterVolume.Primary;
    int maxInstancesPerEmitter = -1;
    short reloadEpoch;

    std::string getName() const {
      return this.name;
   }

    std::string getCategory() const {
      return this.category;
   }

    bool isLooped() {
      return this.loop;
   }

    void setUserVolume(float var1) {
      this.userVolume = Math.max(0.0F, Math.min(2.0F, var1));
   }

    float getUserVolume() const {
      return !SystemDisabler.getEnableAdvancedSoundOptions() ? 1.0F : this.userVolume;
   }

    GameSoundClip getRandomClip() const {
      return this.clips.get(Rand.Next(this.clips.size()));
   }

    std::string getMasterName() const {
      return this.master.name();
   }

    int numClipsUsingParameter(std::string_view var1) {
    FMOD_STUDIO_PARAMETER_DESCRIPTION var2 = FMODManager.instance.getParameterDescription(var1);
      if (var2 == nullptr) {
    return 0;
      } else {
    int var3 = 0;

         for (int var4 = 0; var4 < this.clips.size(); var4++) {
    GameSoundClip var5 = this.clips.get(var4);
            if (var5.hasParameter(var2)) {
               var3++;
            }
         }

    return var3;
      }
   }

    void reset() {
      this.name = nullptr;
      this.category = "General";
      this.loop = false;
      this.is3D = true;
      this.clips.clear();
      this.userVolume = 1.0F;
      this.master = MasterVolume.Primary;
      this.maxInstancesPerEmitter = -1;
      this.reloadEpoch++;
   }
}
} // namespace audio
} // namespace zombie
