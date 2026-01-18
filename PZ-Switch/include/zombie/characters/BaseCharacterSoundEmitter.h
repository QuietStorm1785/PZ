#pragma once
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_DESCRIPTION.h"
#include "zombie/iso/IsoObject.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class BaseCharacterSoundEmitter {
public:
 const IsoGameCharacter character;

public
 BaseCharacterSoundEmitter(IsoGameCharacter chr) { this->character = chr; }

public
 void register();

public
 void unregister();

public
 long playVocals(String file);

public
 void playFootsteps(String file, float volume);

public
 long playSound(String file);

public
 long playSound(String file, IsoObject proxy);

public
 long playSoundImpl(String file, IsoObject proxy);

public
 void tick();

public
 void set(float x, float y, float z);

public
 boolean isClear();

public
 void setPitch(long handle, float pitch);

public
 void setVolume(long handle, float volume);

public
 int stopSound(long channel);

public
 void stopSoundLocal(long handle);

public
 int stopSoundByName(String soundName);

public
 void stopOrTriggerSound(long handle);

public
 void stopOrTriggerSoundByName(String name);

public
 void stopAll();

public
 boolean hasSoundsToStart();

public
 boolean isPlaying(long channel);

public
 boolean isPlaying(String alias);

public
 void
 setParameterValue(long soundRef,
 FMOD_STUDIO_PARAMETER_DESCRIPTION parameterDescription,
 float value);
}
} // namespace characters
} // namespace zombie
