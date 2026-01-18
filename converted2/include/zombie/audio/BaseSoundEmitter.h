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

class BaseSoundEmitter {
public:
public
  abstract void randomStart();

public
  abstract void setPos(float x, float y, float z);

public
  abstract int stopSound(long channel);

public
  abstract void stopSoundLocal(long handle);

public
  abstract int stopSoundByName(String name);

public
  abstract void stopOrTriggerSound(long handle);

public
  abstract void stopOrTriggerSoundByName(String name);

public
  abstract void setVolume(long handle, float volume);

public
  abstract void setPitch(long handle, float pitch);

public
  abstract boolean hasSustainPoints(long handle);

public
  abstract void
  setParameterValue(long handle,
                    FMOD_STUDIO_PARAMETER_DESCRIPTION parameterDescription,
                    float value);

public
  abstract void setTimelinePosition(long handle, String positionName);

public
  abstract void triggerCue(long handle);

public
  abstract void setVolumeAll(float volume);

public
  abstract void stopAll();

public
  abstract long playSound(String file);

public
  abstract long playSound(String file, IsoGameCharacter character);

public
  abstract long playSound(String file, int x, int y, int z);

public
  abstract long playSound(String file, IsoGridSquare square);

public
  abstract long playSoundImpl(String file, IsoGridSquare square);

public
  abstract long playSound(String file, boolean doWorldSound);

public
  abstract long playSoundImpl(String file, boolean doWorldSound,
                              IsoObject parent);

public
  abstract long playSoundLooped(String file);

public
  abstract long playSoundLoopedImpl(String file);

public
  abstract long playSound(String file, IsoObject parent);

public
  abstract long playSoundImpl(String file, IsoObject parent);

public
  abstract long playClip(GameSoundClip clip, IsoObject parent);

public
  abstract long playAmbientSound(String name);

public
  abstract long playAmbientLoopedImpl(String file);

public
  abstract void set3D(long handle, boolean is3D);

public
  abstract void tick();

public
  abstract boolean hasSoundsToStart();

public
  abstract boolean isEmpty();

public
  abstract boolean isPlaying(long channel);

public
  abstract boolean isPlaying(String alias);

public
  abstract boolean restart(long handle);
}
} // namespace audio
} // namespace zombie
