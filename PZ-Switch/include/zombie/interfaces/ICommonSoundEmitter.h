#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
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

 long playSound(std::string_view file);

 long playSound(std::string_view file, bool doWorldSound);

 void tick();

 bool isEmpty();

 void setPitch(long handle, float pitch);

 void setVolume(long handle, float volume);

 bool hasSustainPoints(long handle);

 void triggerCue(long handle);

 int stopSound(long channel);

 void stopOrTriggerSound(long handle);

 void stopOrTriggerSoundByName(std::string_view name);

 bool isPlaying(long channel);

 bool isPlaying(std::string_view alias);
}
} // namespace interfaces
} // namespace zombie
