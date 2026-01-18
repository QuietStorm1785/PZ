#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace interfaces {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * TurboTuTone.
 */
class ICommonSoundEmitter {
public:
 virtual ~ICommonSoundEmitter() = default;
 void setPos(float x, float y, float z);

 long playSound(const std::string &file);

 long playSound(const std::string &file, bool doWorldSound);

 void tick();

 bool isEmpty();

 void setPitch(long handle, float pitch);

 void setVolume(long handle, float volume);

 bool hasSustainPoints(long handle);

 void triggerCue(long handle);

 int stopSound(long channel);

 void stopOrTriggerSound(long handle);

 void stopOrTriggerSoundByName(const std::string &name);

 bool isPlaying(long channel);

 bool isPlaying(const std::string &alias);
}
} // namespace interfaces
} // namespace zombie
