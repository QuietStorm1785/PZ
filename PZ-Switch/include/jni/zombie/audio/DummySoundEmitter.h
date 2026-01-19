#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_DESCRIPTION.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"

namespace zombie {
namespace audio {


class DummySoundEmitter :  BaseSoundEmitter {
:
    void randomStart() {
   }

    void setPos(float var1, float var2, float var3) {
   }

    int stopSound(long var1) {
    return 0;
   }

    void stopSoundLocal(long var1) {
   }

    int stopSoundByName(const std::string& var1) {
    return 0;
   }

    void stopOrTriggerSound(long var1) {
   }

    void stopOrTriggerSoundByName(const std::string& var1) {
   }

    void setVolume(long var1, float var3) {
   }

    void setPitch(long var1, float var3) {
   }

    bool hasSustainPoints(long var1) {
    return false;
   }

    void setParameterValue(long var1, FMOD_STUDIO_PARAMETER_DESCRIPTION var3, float var4) {
   }

    void setTimelinePosition(long var1, const std::string& var3) {
   }

    void triggerCue(long var1) {
   }

    void set3D(long var1, bool var3) {
   }

    void setVolumeAll(float var1) {
   }

    void stopAll() {
   }

    long playSound(const std::string& var1) {
    return 0L;
   }

    long playSound(const std::string& var1, IsoGameCharacter var2) {
    return 0L;
   }

    long playSound(const std::string& var1, int var2, int var3, int var4) {
    return 0L;
   }

    long playSound(const std::string& var1, IsoGridSquare var2) {
    return 0L;
   }

    long playSoundImpl(const std::string& var1, IsoGridSquare var2) {
    return 0L;
   }

    long playSound(const std::string& var1, bool var2) {
    return 0L;
   }

    long playSoundImpl(const std::string& var1, bool var2, IsoObject var3) {
    return 0L;
   }

    long playSound(const std::string& var1, IsoObject var2) {
    return 0L;
   }

    long playSoundImpl(const std::string& var1, IsoObject var2) {
    return 0L;
   }

    long playClip(GameSoundClip var1, IsoObject var2) {
    return 0L;
   }

    long playAmbientSound(const std::string& var1) {
    return 0L;
   }

    void tick() {
   }

    bool hasSoundsToStart() {
    return false;
   }

    bool isEmpty() {
    return true;
   }

    bool isPlaying(long var1) {
    return false;
   }

    bool isPlaying(const std::string& var1) {
    return false;
   }

    bool restart(long var1) {
    return false;
   }

    long playSoundLooped(const std::string& var1) {
    return 0L;
   }

    long playSoundLoopedImpl(const std::string& var1) {
    return 0L;
   }

    long playAmbientLoopedImpl(const std::string& var1) {
    return 0L;
   }
}
} // namespace audio
} // namespace zombie
