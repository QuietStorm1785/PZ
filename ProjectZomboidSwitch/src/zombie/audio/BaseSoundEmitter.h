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
   virtual void setParameterValue(int64_t id, const FMOD_STUDIO_PARAMETER_DESCRIPTION& param, float value) = 0;
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

   public abstract long playSoundImpl(std::string var1, boolean var2, IsoObject var3);

   public abstract long playSoundLooped(std::string var1);

   public abstract long playSoundLoopedImpl(std::string var1);

   public abstract long playSound(std::string var1, IsoObject var2);

   public abstract long playSoundImpl(std::string var1, IsoObject var2);

   public abstract long playClip(GameSoundClip var1, IsoObject var2);

   public abstract long playAmbientSound(std::string var1);

   public abstract long playAmbientLoopedImpl(std::string var1);

   public abstract void set3D(long var1, boolean var3);

   public abstract void tick();

   public abstract boolean hasSoundsToStart();

   public abstract boolean isEmpty();

   public abstract boolean isPlaying(long var1);

   public abstract boolean isPlaying(std::string var1);

   public abstract boolean restart(long var1);
}
} // namespace audio
} // namespace zombie
