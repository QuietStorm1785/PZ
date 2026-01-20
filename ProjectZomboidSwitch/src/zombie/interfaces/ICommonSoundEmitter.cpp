#include <string>
#include "zombie\interfaces/ICommonSoundEmitter.h"

namespace zombie {
namespace interfaces {

void ICommonSoundEmitter::setPos(float var1, float var2, float var3) {
    // TODO: Implement setPos
}

long ICommonSoundEmitter::playSound(const std::string& var1) {
    // TODO: Implement playSound
    return 0;
}

long ICommonSoundEmitter::playSound(const std::string& var1, bool var2) {
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

void ICommonSoundEmitter::setPitch(long var1, float var3) {
    // TODO: Implement setPitch
}

void ICommonSoundEmitter::setVolume(long var1, float var3) {
    // TODO: Implement setVolume
}

bool ICommonSoundEmitter::hasSustainPoints(long var1) {
    // TODO: Implement hasSustainPoints
    return false;
}

void ICommonSoundEmitter::triggerCue(long var1) {
    // TODO: Implement triggerCue
}

int ICommonSoundEmitter::stopSound(long var1) {
    // TODO: Implement stopSound
    return 0;
}

void ICommonSoundEmitter::stopOrTriggerSound(long var1) {
    // TODO: Implement stopOrTriggerSound
}

void ICommonSoundEmitter::stopOrTriggerSoundByName(const std::string& var1) {
    // TODO: Implement stopOrTriggerSoundByName
}

bool ICommonSoundEmitter::isPlaying(long var1) {
    // TODO: Implement isPlaying
    return false;
}

bool ICommonSoundEmitter::isPlaying(const std::string& var1) {
    // TODO: Implement isPlaying
    return false;
}

} // namespace interfaces
} // namespace zombie
