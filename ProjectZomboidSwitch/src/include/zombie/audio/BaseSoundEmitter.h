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
   public abstract void randomStart();

   public abstract void setPos(float var1, float var2, float var3);

   public abstract int stopSound(long var1);

   public abstract void stopSoundLocal(long var1);

   public abstract int stopSoundByName(std::string var1);

   public abstract void stopOrTriggerSound(long var1);

   public abstract void stopOrTriggerSoundByName(std::string var1);

   public abstract void setVolume(long var1, float var3);

   public abstract void setPitch(long var1, float var3);

   public abstract boolean hasSustainPoints(long var1);

   public abstract void setParameterValue(long var1, FMOD_STUDIO_PARAMETER_DESCRIPTION var3, float var4);

   public abstract void setTimelinePosition(long var1, std::string var3);

   public abstract void triggerCue(long var1);

   public abstract void setVolumeAll(float var1);

   public abstract void stopAll();

   public abstract long playSound(std::string var1);

   public abstract long playSound(std::string var1, IsoGameCharacter var2);

   public abstract long playSound(std::string var1, int var2, int var3, int var4);

   public abstract long playSound(std::string var1, IsoGridSquare var2);

   public abstract long playSoundImpl(std::string var1, IsoGridSquare var2);

   public abstract long playSound(std::string var1, boolean var2);

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
