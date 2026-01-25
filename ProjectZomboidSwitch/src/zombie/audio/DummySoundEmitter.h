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


class DummySoundEmitter : public BaseSoundEmitter {
public:
    virtual ~DummySoundEmitter() = default;

    void randomStart() override {}
    void setPos(float x, float y, float z) override {}
    int stopSound(int64_t id) override { return 0; }
    void stopSoundLocal(int64_t id) override {}
    int stopSoundByName(const std::string& name) override { return 0; }
    void stopOrTriggerSound(int64_t id) override {}
    void stopOrTriggerSoundByName(const std::string& name) override {}
    void setVolume(int64_t id, float volume) override {}
    void setPitch(int64_t id, float pitch) override {}
    bool hasSustainPoints(int64_t id) override { return false; }
    void setParameterValue(int64_t id, const FMOD_STUDIO_PARAMETER_DESCRIPTION& param, float value) override {}
    void setTimelinePosition(int64_t id, const std::string& position) override {}
    void triggerCue(int64_t id) override {}

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
    int64_t playSound(const std::string&, bool) override { return 0; }
    int64_t playSoundImpl(const std::string&, bool, zombie::iso::IsoObject*) override { return 0; }
    int64_t playSound(const std::string&, zombie::iso::IsoObject*) override { return 0; }
    int64_t playSoundImpl(const std::string&, zombie::iso::IsoObject*) override { return 0; }
    int64_t playClip(GameSoundClip&, zombie::iso::IsoObject*) override { return 0; }
    int64_t playAmbientSound(const std::string&) override { return 0; }
    void tick() override {}
    bool hasSoundsToStart() const override { return false; }
    bool isEmpty() const override { return true; }
    bool isPlaying(int64_t) const override { return false; }
    bool isPlaying(const std::string&) const override { return false; }
    bool restart(int64_t) override { return false; }
    int64_t playSoundLooped(const std::string&) override { return 0; }
    int64_t playSoundLoopedImpl(const std::string&) override { return 0; }
    int64_t playAmbientLoopedImpl(const std::string&) override { return 0; }
};
} // namespace audio
} // namespace zombie
