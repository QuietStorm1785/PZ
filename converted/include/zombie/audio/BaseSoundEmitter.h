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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class BaseSoundEmitter {
public:
 public void randomStart();

 public void setPos(float x, float y, float z);

 public int stopSound(long channel);

 public void stopSoundLocal(long handle);

 public int stopSoundByName(String name);

 public void stopOrTriggerSound(long handle);

 public void stopOrTriggerSoundByName(String name);

 public void setVolume(long handle, float volume);

 public void setPitch(long handle, float pitch);

 public boolean hasSustainPoints(long handle);

 public void setParameterValue(long handle, FMOD_STUDIO_PARAMETER_DESCRIPTION parameterDescription, float value);

 public void setTimelinePosition(long handle, String positionName);

 public void triggerCue(long handle);

 public void setVolumeAll(float volume);

 public void stopAll();

 public long playSound(String file);

 public long playSound(String file, IsoGameCharacter character);

 public long playSound(String file, int x, int y, int z);

 public long playSound(String file, IsoGridSquare square);

 public long playSoundImpl(String file, IsoGridSquare square);

 public long playSound(String file, boolean doWorldSound);

 public long playSoundImpl(String file, boolean doWorldSound, IsoObject parent);

 public long playSoundLooped(String file);

 public long playSoundLoopedImpl(String file);

 public long playSound(String file, IsoObject parent);

 public long playSoundImpl(String file, IsoObject parent);

 public long playClip(GameSoundClip clip, IsoObject parent);

 public long playAmbientSound(String name);

 public long playAmbientLoopedImpl(String file);

 public void set3D(long handle, boolean is3D);

 public void tick();

 public boolean hasSoundsToStart();

 public boolean isEmpty();

 public boolean isPlaying(long channel);

 public boolean isPlaying(String alias);

 public boolean restart(long handle);
}
} // namespace audio
} // namespace zombie
