#include <string>
#include "zombie/audio/DummySoundEmitter.h"

namespace zombie {
namespace audio {

void DummySoundEmitter::randomStart() {
    // Dummy implementation: does nothing
}

void DummySoundEmitter::setPos(float var1, float var2, float var3) {
    // Dummy implementation: does nothing
}

int DummySoundEmitter::stopSound(long var1) {
    // Dummy implementation: does nothing
    return 0;
}

void DummySoundEmitter::stopSoundLocal(long var1) {
    // Dummy implementation: does nothing
}

int DummySoundEmitter::stopSoundByName(const std::string& var1) {
    // Dummy implementation: does nothing
    return 0;
}

void DummySoundEmitter::stopOrTriggerSound(long var1) {
    // Dummy implementation: does nothing
}

void DummySoundEmitter::stopOrTriggerSoundByName(const std::string& var1) {
    // Dummy implementation: does nothing
}

void DummySoundEmitter::setVolume(long var1, float var3) {
    // Dummy implementation: does nothing
}

void DummySoundEmitter::setPitch(long var1, float var3) {
    // Dummy implementation: does nothing
}

bool DummySoundEmitter::hasSustainPoints(long var1) {
    // Dummy implementation: does nothing
    return false;
}

void DummySoundEmitter::setParameterValue(long var1, FMOD_STUDIO_PARAMETER_DESCRIPTION var3, float var4) {
    // Dummy implementation: does nothing
}

void DummySoundEmitter::setTimelinePosition(long var1, const std::string& var3) {
    // Dummy implementation: does nothing
}

void DummySoundEmitter::triggerCue(long var1) {
    // Dummy implementation: does nothing
}

void DummySoundEmitter::set3D(long var1, bool var3) {
    // Dummy implementation: does nothing
}

void DummySoundEmitter::setVolumeAll(float var1) {
    // Dummy implementation: does nothing
}

void DummySoundEmitter::stopAll() {
    // Dummy implementation: does nothing
}

long DummySoundEmitter::playSound(const std::string& var1) {
    // Dummy implementation: does nothing
    return 0;
}

long DummySoundEmitter::playSound(const std::string& var1, IsoGameCharacter var2) {
    // Dummy implementation: does nothing
    return 0;
}

long DummySoundEmitter::playSound(const std::string& var1, int var2, int var3, int var4) {
    // Dummy implementation: does nothing
    return 0;
}

long DummySoundEmitter::playSound(const std::string& var1, IsoGridSquare var2) {
    // Dummy implementation: does nothing
    return 0;
}

long DummySoundEmitter::playSoundImpl(const std::string& var1, IsoGridSquare var2) {
    // Dummy implementation: does nothing
    return 0;
}

long DummySoundEmitter::playSound(const std::string& var1, bool var2) {
    // Dummy implementation: does nothing
    return 0;
}

long DummySoundEmitter::playSoundImpl(const std::string& var1, bool var2, IsoObject var3) {
    // Dummy implementation: does nothing
    return 0;
}

long DummySoundEmitter::playSound(const std::string& var1, IsoObject var2) {
    // Dummy implementation: does nothing
    return 0;
}

long DummySoundEmitter::playSoundImpl(const std::string& var1, IsoObject var2) {
    // Dummy implementation: does nothing
    return 0;
}

long DummySoundEmitter::playClip(GameSoundClip var1, IsoObject var2) {
    // Dummy implementation: does nothing
    return 0;
}

long DummySoundEmitter::playAmbientSound(const std::string& var1) {
    // Dummy implementation: does nothing
    return 0;
}

void DummySoundEmitter::tick() {
    // Dummy implementation: does nothing
}

bool DummySoundEmitter::hasSoundsToStart() {
    // Dummy implementation: does nothing
    return false;
}

bool DummySoundEmitter::isEmpty() {
    // Dummy implementation: does nothing
    return false;
}

bool DummySoundEmitter::isPlaying(long var1) {
    // Dummy implementation: does nothing
    return false;
}

bool DummySoundEmitter::isPlaying(const std::string& var1) {
    // Dummy implementation: does nothing
    return false;
}

bool DummySoundEmitter::restart(long var1) {
    // Dummy implementation: does nothing
    return false;
}

long DummySoundEmitter::playSoundLooped(const std::string& var1) {
    // Dummy implementation: does nothing
    return 0;
}

long DummySoundEmitter::playSoundLoopedImpl(const std::string& var1) {
    // Dummy implementation: does nothing
    return 0;
}

long DummySoundEmitter::playAmbientLoopedImpl(const std::string& var1) {
    // Dummy implementation: does nothing
    return 0;
}

} // namespace audio
} // namespace zombie
