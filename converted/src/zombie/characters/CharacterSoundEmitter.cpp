#include "zombie/characters/CharacterSoundEmitter.h"

namespace zombie {
namespace characters {

public CharacterSoundEmitter::CharacterSoundEmitter(IsoGameCharacter chr) {
 // TODO: Implement CharacterSoundEmitter
 return nullptr;
}

void CharacterSoundEmitter::register() {
 // TODO: Implement register
}

void CharacterSoundEmitter::unregister() {
 // TODO: Implement unregister
}

long CharacterSoundEmitter::playVocals(const std::string& file) {
 // TODO: Implement playVocals
 return 0;
}

void CharacterSoundEmitter::playFootsteps(const std::string& file, float volume) {
 // TODO: Implement playFootsteps
}

long CharacterSoundEmitter::playSound(const std::string& file) {
 // TODO: Implement playSound
 return 0;
}

long CharacterSoundEmitter::playSound(const std::string& file, bool doWorldSound) {
 // TODO: Implement playSound
 return 0;
}

long CharacterSoundEmitter::playSound(const std::string& file, IsoObject proxy) {
 // TODO: Implement playSound
 return 0;
}

long CharacterSoundEmitter::playSoundImpl(const std::string& file, IsoObject proxy) {
 // TODO: Implement playSoundImpl
 return 0;
}

void CharacterSoundEmitter::tick() {
 // TODO: Implement tick
}

void CharacterSoundEmitter::setPos(float x, float y, float z) {
 // TODO: Implement setPos
}

void CharacterSoundEmitter::set(float x, float y, float z) {
 // TODO: Implement set
}

bool CharacterSoundEmitter::isEmpty() {
 // TODO: Implement isEmpty
 return false;
}

bool CharacterSoundEmitter::isClear() {
 // TODO: Implement isClear
 return false;
}

void CharacterSoundEmitter::setPitch(long handle, float pitch) {
 // TODO: Implement setPitch
}

void CharacterSoundEmitter::setVolume(long handle, float volume) {
 // TODO: Implement setVolume
}

bool CharacterSoundEmitter::hasSustainPoints(long handle) {
 // TODO: Implement hasSustainPoints
 return false;
}

void CharacterSoundEmitter::triggerCue(long handle) {
 // TODO: Implement triggerCue
}

int CharacterSoundEmitter::stopSound(long eventInstance) {
 // TODO: Implement stopSound
 return 0;
}

void CharacterSoundEmitter::stopSoundLocal(long handle) {
 // TODO: Implement stopSoundLocal
}

void CharacterSoundEmitter::stopOrTriggerSound(long eventInstance) {
 // TODO: Implement stopOrTriggerSound
}

void CharacterSoundEmitter::stopOrTriggerSoundByName(const std::string& name) {
 // TODO: Implement stopOrTriggerSoundByName
}

void CharacterSoundEmitter::stopAll() {
 // TODO: Implement stopAll
}

int CharacterSoundEmitter::stopSoundByName(const std::string& soundName) {
 // TODO: Implement stopSoundByName
 return 0;
}

bool CharacterSoundEmitter::hasSoundsToStart() {
 // TODO: Implement hasSoundsToStart
 return false;
}

bool CharacterSoundEmitter::isPlaying(long eventInstance) {
 // TODO: Implement isPlaying
 return false;
}

bool CharacterSoundEmitter::isPlaying(const std::string& alias) {
 // TODO: Implement isPlaying
 return false;
}

void CharacterSoundEmitter::setParameterValue(long soundRef, FMOD_STUDIO_PARAMETER_DESCRIPTION parameterDescription, float value) {
 // TODO: Implement setParameterValue
}

} // namespace characters
} // namespace zombie
