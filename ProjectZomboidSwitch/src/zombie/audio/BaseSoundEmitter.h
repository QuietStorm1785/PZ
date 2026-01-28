#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"


namespace zombie {
namespace audio {


class BaseSoundEmitter {
public:
   virtual ~BaseSoundEmitter() = default;

   virtual void randomStart() = 0;
   virtual void setPos(float x, float y, float z) = 0;
   virtual int stopSound(int64_t id) = 0;
   virtual void stopSoundLocal(int64_t id) = 0;
   virtual int stopSoundByName(const std::string& name) = 0;
   virtual void stopOrTriggerSound(int64_t id) = 0;
   virtual void stopOrTriggerSoundByName(const std::string& name) = 0;
   virtual void setVolume(int64_t id, float volume) = 0;
   virtual void setPitch(int64_t id, float pitch) = 0;
   virtual bool hasSustainPoints(int64_t id) = 0;
   virtual void setParameterValue(int64_t id, const std::string& param, float value) = 0;
   virtual void setTimelinePosition(int64_t id, const std::string& position) = 0;
   virtual void triggerCue(int64_t id) = 0;
   virtual void setVolumeAll(float volume) = 0;
   virtual void stopAll() = 0;
   virtual int64_t playSound(const std::string& name) = 0;
   virtual int64_t playSound(const std::string& name, zombie::characters::IsoGameCharacter* character) = 0;
   virtual int64_t playSound(const std::string& name, int x, int y, int z) = 0;
   virtual int64_t playSound(const std::string& name, zombie::iso::IsoGridSquare* square) = 0;
   virtual int64_t playSoundImpl(const std::string& name, zombie::iso::IsoGridSquare* square) = 0;
   virtual int64_t playSound(const std::string& name, bool flag) = 0;


   virtual int64_t playSoundImpl(const std::string& name, bool flag, zombie::iso::IsoObject* obj) = 0;
   virtual int64_t playSoundLooped(const std::string& name) = 0;
   virtual int64_t playSoundLoopedImpl(const std::string& name) = 0;
   virtual int64_t playSound(const std::string& name, zombie::iso::IsoObject* obj) = 0;
   virtual int64_t playSoundImpl(const std::string& name, zombie::iso::IsoObject* obj) = 0;
   virtual int64_t playClip(GameSoundClip& clip, zombie::iso::IsoObject* obj) = 0;
   virtual int64_t playAmbientSound(const std::string& name) = 0;
   virtual int64_t playAmbientLoopedImpl(const std::string& name) = 0;
   virtual void set3D(int64_t id, bool is3D) = 0;

   virtual void tick() = 0;
   virtual bool hasSoundsToStart() const = 0;
   virtual bool isEmpty() const = 0;
   virtual bool isPlaying(int64_t id) const = 0;
   virtual bool isPlaying(const std::string& name) const = 0;
   virtual bool restart(int64_t id) = 0;
}
} // namespace audio
} // namespace zombie
