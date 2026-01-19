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
:
    abstract void randomStart();

    abstract void setPos(float var1, float var2, float var3);

    abstract int stopSound(long var1);

    abstract void stopSoundLocal(long var1);

    abstract int stopSoundByName(String var1);

    abstract void stopOrTriggerSound(long var1);

    abstract void stopOrTriggerSoundByName(String var1);

    abstract void setVolume(long var1, float var3);

    abstract void setPitch(long var1, float var3);

    abstract boolean hasSustainPoints(long var1);

    abstract void setParameterValue(long var1, FMOD_STUDIO_PARAMETER_DESCRIPTION var3, float var4);

    abstract void setTimelinePosition(long var1, String var3);

    abstract void triggerCue(long var1);

    abstract void setVolumeAll(float var1);

    abstract void stopAll();

    abstract long playSound(String var1);

    abstract long playSound(String var1, IsoGameCharacter var2);

    abstract long playSound(String var1, int var2, int var3, int var4);

    abstract long playSound(String var1, IsoGridSquare var2);

    abstract long playSoundImpl(String var1, IsoGridSquare var2);

    abstract long playSound(String var1, boolean var2);

    abstract long playSoundImpl(String var1, boolean var2, IsoObject var3);

    abstract long playSoundLooped(String var1);

    abstract long playSoundLoopedImpl(String var1);

    abstract long playSound(String var1, IsoObject var2);

    abstract long playSoundImpl(String var1, IsoObject var2);

    abstract long playClip(GameSoundClip var1, IsoObject var2);

    abstract long playAmbientSound(String var1);

    abstract long playAmbientLoopedImpl(String var1);

    abstract void set3D(long var1, boolean var3);

    abstract void tick();

    abstract boolean hasSoundsToStart();

    abstract boolean isEmpty();

    abstract boolean isPlaying(long var1);

    abstract boolean isPlaying(String var1);

    abstract boolean restart(long var1);
}
} // namespace audio
} // namespace zombie
