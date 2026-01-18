#include "zombie/interfaces/ICommonSoundEmitter.h"

namespace zombie {
namespace interfaces {

void ICommonSoundEmitter::setPos(float x, float y, float z) {
 // TODO: Implement setPos
}

long ICommonSoundEmitter::playSound(const std::string& file) {
 // TODO: Implement playSound
 return 0;
}

long ICommonSoundEmitter::playSound(const std::string& file, bool doWorldSound) {
 // TODO: Implement playSound
 return 0;
}

void ICommonSoundEmitter::tick() {
 // TODO: Implement tick
}

bool ICommonSoundEmitter::isEmpty() {
 // TODO: Implement isEmpty
 return false;
}

void ICommonSoundEmitter::setPitch(long handle, float pitch) {
 // TODO: Implement setPitch
}

void ICommonSoundEmitter::setVolume(long handle, float volume) {
 // TODO: Implement setVolume
}

bool ICommonSoundEmitter::hasSustainPoints(long handle) {
 // TODO: Implement hasSustainPoints
 return false;
}

void ICommonSoundEmitter::triggerCue(long handle) {
 // TODO: Implement triggerCue
}

int ICommonSoundEmitter::stopSound(long channel) {
 // TODO: Implement stopSound
 return 0;
}

void ICommonSoundEmitter::stopOrTriggerSound(long handle) {
 // TODO: Implement stopOrTriggerSound
}

void ICommonSoundEmitter::stopOrTriggerSoundByName(const std::string& name) {
 // TODO: Implement stopOrTriggerSoundByName
}

bool ICommonSoundEmitter::isPlaying(long channel) {
 // TODO: Implement isPlaying
 return false;
}

bool ICommonSoundEmitter::isPlaying(const std::string& alias) {
 // TODO: Implement isPlaying
 return false;
}

} // namespace interfaces
} // namespace zombie
