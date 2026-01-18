#pragma once
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_DESCRIPTION.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace audio {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class DummySoundEmitter : public BaseSoundEmitter {
public:
 void randomStart() {}

 void setPos(float x, float y, float z) {}

 int stopSound(long channel) { return 0; }

 void stopSoundLocal(long handle) {}

 int stopSoundByName(const std::string &name) { return 0; }

 void stopOrTriggerSound(long handle) {}

 void stopOrTriggerSoundByName(const std::string &name) {}

 void setVolume(long handle, float volume) {}

 void setPitch(long handle, float volume) {}

 bool hasSustainPoints(long handle) { return false; }

 void setParameterValue(long handle,
 FMOD_STUDIO_PARAMETER_DESCRIPTION parameterDescription,
 float value) {}

 void setTimelinePosition(long handle, const std::string &positionName) {}

 void triggerCue(long handle) {}

 void set3D(long handle, bool is3D) {}

 void setVolumeAll(float volume) {}

 void stopAll() {}

 long playSound(const std::string &file) { return 0L; }

 long playSound(const std::string &file, IsoGameCharacter character) {
 return 0L;
 }

 long playSound(const std::string &file, int x, int y, int z) { return 0L; }

 long playSound(const std::string &file, IsoGridSquare square) { return 0L; }

 long playSoundImpl(const std::string &file, IsoGridSquare square) {
 return 0L;
 }

 long playSound(const std::string &file, bool doWorldSound) { return 0L; }

 long playSoundImpl(const std::string &file, bool doWorldSound,
 IsoObject parent) {
 return 0L;
 }

 long playSound(const std::string &file, IsoObject parent) { return 0L; }

 long playSoundImpl(const std::string &file, IsoObject parent) { return 0L; }

 long playClip(GameSoundClip clip, IsoObject parent) { return 0L; }

 long playAmbientSound(const std::string &name) { return 0L; }

 void tick() {}

 bool hasSoundsToStart() { return false; }

 bool isEmpty() { return true; }

 bool isPlaying(long channel) { return false; }

 bool isPlaying(const std::string &alias) { return false; }

 bool restart(long handle) { return false; }

 long playSoundLooped(const std::string &file) { return 0L; }

 long playSoundLoopedImpl(const std::string &file) { return 0L; }

 long playAmbientLoopedImpl(const std::string &file) { return 0L; }
}
} // namespace audio
} // namespace zombie
