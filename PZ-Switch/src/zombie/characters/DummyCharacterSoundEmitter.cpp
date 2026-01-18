#include "zombie/characters/DummyCharacterSoundEmitter.h"

namespace zombie {
namespace characters {

public
DummyCharacterSoundEmitter::DummyCharacterSoundEmitter(IsoGameCharacter chr) {
 // TODO: Implement DummyCharacterSoundEmitter
 return nullptr;
}

void DummyCharacterSoundEmitter::register() {
 // TODO: Implement register
}

void DummyCharacterSoundEmitter::unregister() {
 // TODO: Implement unregister
}

long DummyCharacterSoundEmitter::playVocals(const std::string &file) {
 // TODO: Implement playVocals
 return 0;
}

void DummyCharacterSoundEmitter::playFootsteps(const std::string &file,
 float volume) {
 // TODO: Implement playFootsteps
}

long DummyCharacterSoundEmitter::playSound(const std::string &file) {
 // TODO: Implement playSound
 return 0;
}

long DummyCharacterSoundEmitter::playSound(const std::string &file,
 IsoObject proxy) {
 // TODO: Implement playSound
 return 0;
}

long DummyCharacterSoundEmitter::playSoundImpl(const std::string &file,
 IsoObject proxy) {
 // TODO: Implement playSoundImpl
 return 0;
}

void DummyCharacterSoundEmitter::tick() {
 // TODO: Implement tick
}

void DummyCharacterSoundEmitter::set(float _x, float _y, float _z) {
 // TODO: Implement set
}

bool DummyCharacterSoundEmitter::isClear() {
 // TODO: Implement isClear
 return false;
}

void DummyCharacterSoundEmitter::setPitch(long handle, float pitch) {
 // TODO: Implement setPitch
}

void DummyCharacterSoundEmitter::setVolume(long handle, float volume) {
 // TODO: Implement setVolume
}

int DummyCharacterSoundEmitter::stopSound(long channel) {
 // TODO: Implement stopSound
 return 0;
}

void DummyCharacterSoundEmitter::stopSoundLocal(long handle) {
 // TODO: Implement stopSoundLocal
}

void DummyCharacterSoundEmitter::stopOrTriggerSound(long handle) {
 // TODO: Implement stopOrTriggerSound
}

void DummyCharacterSoundEmitter::stopOrTriggerSoundByName(
 const std::string &name) {
 // TODO: Implement stopOrTriggerSoundByName
}

void DummyCharacterSoundEmitter::stopAll() {
 // TODO: Implement stopAll
}

int DummyCharacterSoundEmitter::stopSoundByName(const std::string &soundName) {
 // TODO: Implement stopSoundByName
 return 0;
}

bool DummyCharacterSoundEmitter::hasSoundsToStart() {
 // TODO: Implement hasSoundsToStart
 return false;
}

bool DummyCharacterSoundEmitter::isPlaying(long channel) {
 // TODO: Implement isPlaying
 return false;
}

bool DummyCharacterSoundEmitter::isPlaying(const std::string &alias) {
 // TODO: Implement isPlaying
 return false;
}

void DummyCharacterSoundEmitter::setParameterValue(
 long soundRef, FMOD_STUDIO_PARAMETER_DESCRIPTION parameterDescription,
 float value) {
 // TODO: Implement setParameterValue
}

bool DummyCharacterSoundEmitter::hasSustainPoints(long handle) {
 // TODO: Implement hasSustainPoints
 return false;
}

} // namespace characters
} // namespace zombie
