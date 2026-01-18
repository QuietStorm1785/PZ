#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMOD_STUDIO_EVENT_DESCRIPTION.h"
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_DESCRIPTION.h"
#include "zombie/SoundManager.h"
#include "zombie/core/Core.h"

namespace zombie {
namespace audio {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class GameSoundClip {
public:
 static short INIT_FLAG_DISTANCE_MIN = 1;
 static short INIT_FLAG_DISTANCE_MAX = 2;
 const GameSound gameSound;
 std::string event;
 FMOD_STUDIO_EVENT_DESCRIPTION eventDescription;
 FMOD_STUDIO_EVENT_DESCRIPTION eventDescriptionMP;
 std::string file;
 float volume = 1.0F;
 float pitch = 1.0F;
 float distanceMin = 10.0F;
 float distanceMax = 10.0F;
 float reverbMaxRange = 10.0F;
 float reverbFactor = 0.0F;
 int priority = 5;
 short initFlags = 0;
 short reloadEpoch;

 public GameSoundClip(GameSound _gameSound) {
 this->gameSound = _gameSound;
 this->reloadEpoch = _gameSound.reloadEpoch;
 }

 std::string getEvent() {
 return this->event;
 }

 std::string getFile() {
 return this->file;
 }

 float getVolume() {
 return this->volume;
 }

 float getPitch() {
 return this->pitch;
 }

 bool hasMinDistance() {
 return (this->initFlags & INIT_FLAG_DISTANCE_MIN) != 0;
 }

 bool hasMaxDistance() {
 return (this->initFlags & INIT_FLAG_DISTANCE_MAX) != 0;
 }

 float getMinDistance() {
 return this->distanceMin;
 }

 float getMaxDistance() {
 return this->distanceMax;
 }

 float getEffectiveVolume() {
 float float0 = 1.0F;
 switch (this->gameSound.master) {
 case Primary:
 float0 = SoundManager.instance.getSoundVolume();
 break;
 case Ambient:
 float0 = SoundManager.instance.getAmbientVolume();
 break;
 case Music:
 float0 = SoundManager.instance.getMusicVolume();
 break;
 case VehicleEngine:
 float0 = SoundManager.instance.getVehicleEngineVolume();
 }

 float0 *= this->volume;
 return float0 * this->gameSound.getUserVolume();
 }

 float getEffectiveVolumeInMenu() {
 float float0 = 1.0F;
 switch (this->gameSound.master) {
 case Primary:
 float0 = Core.getInstance().getOptionSoundVolume() / 10.0F;
 break;
 case Ambient:
 float0 = Core.getInstance().getOptionAmbientVolume() / 10.0F;
 break;
 case Music:
 float0 = Core.getInstance().getOptionMusicVolume() / 10.0F;
 break;
 case VehicleEngine:
 float0 = Core.getInstance().getOptionVehicleEngineVolume() / 10.0F;
 }

 float0 *= this->volume;
 return float0 * this->gameSound.getUserVolume();
 }

 GameSoundClip checkReloaded() {
 if (this->reloadEpoch == this->gameSound.reloadEpoch) {
 return this;
 } else {
 GameSoundClip gameSoundClip1 = nullptr;

 for (int int0 = 0; int0 < this->gameSound.clips.size(); int0++) {
 GameSoundClip gameSoundClip2 = this->gameSound.clips.get(int0);
 if (gameSoundClip2 == this) {
 return this;
 }

 if (gameSoundClip2.event != nullptr && gameSoundClip2.event == this->event) {
 gameSoundClip1 = gameSoundClip2;
 }

 if (gameSoundClip2.file != nullptr && gameSoundClip2.file == this->file) {
 gameSoundClip1 = gameSoundClip2;
 }
 }

 if (gameSoundClip1.empty()) {
 this->reloadEpoch = this->gameSound.reloadEpoch;
 return this;
 } else {
 return gameSoundClip1;
 }
 }
 }

 bool hasSustainPoints() {
 return this->eventDescription != nullptr && this->eventDescription.bHasSustainPoints;
 }

 bool hasParameter(FMOD_STUDIO_PARAMETER_DESCRIPTION parameterDescription) {
 return this->eventDescription != nullptr && this->eventDescription.hasParameter(parameterDescription);
 }
}
} // namespace audio
} // namespace zombie
