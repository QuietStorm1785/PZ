#include "zombie/audio/DummySoundEmitter.h"

namespace zombie {
namespace audio {

void DummySoundEmitter::randomStart() {
 // TODO: Implement randomStart
}

void DummySoundEmitter::setPos(float x, float y, float z) {
 // TODO: Implement setPos
}

int DummySoundEmitter::stopSound(long channel) {
 // TODO: Implement stopSound
 return 0;
}

void DummySoundEmitter::stopSoundLocal(long handle) {
 // TODO: Implement stopSoundLocal
}

int DummySoundEmitter::stopSoundByName(const std::string& name) {
 // TODO: Implement stopSoundByName
 return 0;
}

void DummySoundEmitter::stopOrTriggerSound(long handle) {
 // TODO: Implement stopOrTriggerSound
}

void DummySoundEmitter::stopOrTriggerSoundByName(const std::string& name) {
 // TODO: Implement stopOrTriggerSoundByName
}

void DummySoundEmitter::setVolume(long handle, float volume) {
 // TODO: Implement setVolume
}

void DummySoundEmitter::setPitch(long handle, float volume) {
 // TODO: Implement setPitch
}

bool DummySoundEmitter::hasSustainPoints(long handle) {
 // TODO: Implement hasSustainPoints
 return false;
}

void DummySoundEmitter::setParameterValue(long handle, FMOD_STUDIO_PARAMETER_DESCRIPTION parameterDescription, float value) {
 // TODO: Implement setParameterValue
}

void DummySoundEmitter::setTimelinePosition(long handle, const std::string& positionName) {
 // TODO: Implement setTimelinePosition
}

void DummySoundEmitter::triggerCue(long handle) {
 // TODO: Implement triggerCue
}

void DummySoundEmitter::set3D(long handle, bool is3D) {
 // TODO: Implement set3D
}

void DummySoundEmitter::setVolumeAll(float volume) {
 // TODO: Implement setVolumeAll
}

void DummySoundEmitter::stopAll() {
 // TODO: Implement stopAll
}

long DummySoundEmitter::playSound(const std::string& file) {
 // TODO: Implement playSound
 return 0;
}

long DummySoundEmitter::playSound(const std::string& file, IsoGameCharacter character) {
 // TODO: Implement playSound
 return 0;
}

long DummySoundEmitter::playSound(const std::string& file, int x, int y, int z) {
 // TODO: Implement playSound
 return 0;
}

long DummySoundEmitter::playSound(const std::string& file, IsoGridSquare square) {
 // TODO: Implement playSound
 return 0;
}

long DummySoundEmitter::playSoundImpl(const std::string& file, IsoGridSquare square) {
 // TODO: Implement playSoundImpl
 return 0;
}

long DummySoundEmitter::playSound(const std::string& file, bool doWorldSound) {
 // TODO: Implement playSound
 return 0;
}

long DummySoundEmitter::playSoundImpl(const std::string& file, bool doWorldSound, IsoObject parent) {
 // TODO: Implement playSoundImpl
 return 0;
}

long DummySoundEmitter::playSound(const std::string& file, IsoObject parent) {
 // TODO: Implement playSound
 return 0;
}

long DummySoundEmitter::playSoundImpl(const std::string& file, IsoObject parent) {
 // TODO: Implement playSoundImpl
 return 0;
}

long DummySoundEmitter::playClip(GameSoundClip clip, IsoObject parent) {
 // TODO: Implement playClip
 return 0;
}

long DummySoundEmitter::playAmbientSound(const std::string& name) {
 // TODO: Implement playAmbientSound
 return 0;
}

void DummySoundEmitter::tick() {
 // TODO: Implement tick
}

bool DummySoundEmitter::hasSoundsToStart() {
 // TODO: Implement hasSoundsToStart
 return false;
}

bool DummySoundEmitter::isEmpty() {
 // TODO: Implement isEmpty
 return false;
}

bool DummySoundEmitter::isPlaying(long channel) {
 // TODO: Implement isPlaying
 return false;
}

bool DummySoundEmitter::isPlaying(const std::string& alias) {
 // TODO: Implement isPlaying
 return false;
}

bool DummySoundEmitter::restart(long handle) {
 // TODO: Implement restart
 return false;
}

long DummySoundEmitter::playSoundLooped(const std::string& file) {
 // TODO: Implement playSoundLooped
 return 0;
}

long DummySoundEmitter::playSoundLoopedImpl(const std::string& file) {
 // TODO: Implement playSoundLoopedImpl
 return 0;
}

long DummySoundEmitter::playAmbientLoopedImpl(const std::string& file) {
 // TODO: Implement playAmbientLoopedImpl
 return 0;
}

} // namespace audio
} // namespace zombie
