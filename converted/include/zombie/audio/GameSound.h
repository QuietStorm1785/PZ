#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_DESCRIPTION.h"
#include "zombie/SystemDisabler.h"
#include "zombie/core/Rand.h"

namespace zombie {
namespace audio {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class GameSound {
public:
 std::string name;
 std::string category = "General";
 bool loop = false;
 bool is3D = true;
 public ArrayList<GameSoundClip> clips = std::make_unique<ArrayList<>>();
 float userVolume = 1.0F;
 public GameSound.MasterVolume master = GameSound.MasterVolume.Primary;
 int maxInstancesPerEmitter = -1;
 short reloadEpoch;

 std::string getName() {
 return this->name;
 }

 std::string getCategory() {
 return this->category;
 }

 bool isLooped() {
 return this->loop;
 }

 void setUserVolume(float gain) {
 this->userVolume = Math.max(0.0F, Math.min(2.0F, gain);
 }

 float getUserVolume() {
 return !SystemDisabler.getEnableAdvancedSoundOptions() ? 1.0F : this->userVolume;
 }

 GameSoundClip getRandomClip() {
 return this->clips.get(Rand.Next(this->clips.size()));
 }

 std::string getMasterName() {
 return this->master.name();
 }

 int numClipsUsingParameter(const std::string& parameterName) {
 FMOD_STUDIO_PARAMETER_DESCRIPTION fmod_studio_parameter_description = FMODManager.instance.getParameterDescription(parameterName);
 if (fmod_studio_parameter_description.empty()) {
 return 0;
 } else {
 int int0 = 0;

 for (int int1 = 0; int1 < this->clips.size(); int1++) {
 GameSoundClip gameSoundClip = this->clips.get(int1);
 if (gameSoundClip.hasParameter(fmod_studio_parameter_description) {
 int0++;
 }
 }

 return int0;
 }
 }

 void reset() {
 this->name = nullptr;
 this->category = "General";
 this->loop = false;
 this->is3D = true;
 this->clips.clear();
 this->userVolume = 1.0F;
 this->master = GameSound.MasterVolume.Primary;
 this->maxInstancesPerEmitter = -1;
 this->reloadEpoch++;
 }

 public static enum MasterVolume {
 Primary,
 Ambient,
 Music,
 VehicleEngine;
 }
}
} // namespace audio
} // namespace zombie
