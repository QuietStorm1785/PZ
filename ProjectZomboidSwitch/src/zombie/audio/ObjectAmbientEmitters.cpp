#include <string>
#include "zombie/audio/ObjectAmbientEmitters.h"


namespace zombie {
namespace audio {

ObjectAmbientEmitters ObjectAmbientEmitters::getInstance() {
    // TODO: Implement getInstance
    return nullptr;
}

private ObjectAmbientEmitters::ObjectAmbientEmitters() {
    // TODO: Implement ObjectAmbientEmitters
    return nullptr;
}

void ObjectAmbientEmitters::addObject(IsoObject var1, PerObjectLogic var2) {
    // TODO: Implement addObject
}

void ObjectAmbientEmitters::removeObject(IsoObject var1) {
    // TODO: Implement removeObject
}

void ObjectAmbientEmitters::update() {
    // TODO: Implement update
}

void ObjectAmbientEmitters::addObjectsFromChunks() {
    // TODO: Implement addObjectsFromChunks
}

float ObjectAmbientEmitters::getClosestListener(float var1, float var2, float var3) {
    // TODO: Implement getClosestListener
    return 0;
}

bool ObjectAmbientEmitters::shouldPlay(IsoObject var1, PerObjectLogic var2) {
    // TODO: Implement shouldPlay
    return false;
}

int ObjectAmbientEmitters::getExistingSlot(IsoObject var1) {
    // TODO: Implement getExistingSlot
    return 0;
}

int ObjectAmbientEmitters::getFreeSlot() {
    // TODO: Implement getFreeSlot
    return 0;
}

void ObjectAmbientEmitters::stopNotPlaying() {
    // TODO: Implement stopNotPlaying
}

void ObjectAmbientEmitters::render() {
    // TODO: Implement render
}

void ObjectAmbientEmitters::Reset() {
    // TODO: Implement Reset
}


PerObjectLogic ObjectAmbientEmitters$AmbientSoundLogic::init(IsoObject var1) {
    // TODO: Implement init
    return nullptr;
}

bool ObjectAmbientEmitters$AmbientSoundLogic::shouldPlaySound() {
    // TODO: Implement shouldPlaySound
    return false;
}

std::string ObjectAmbientEmitters$AmbientSoundLogic::getSoundName() {
    // TODO: Implement getSoundName
    return "";
}

void ObjectAmbientEmitters$AmbientSoundLogic::startPlaying(BaseSoundEmitter var1, long var2) {
    // TODO: Implement startPlaying
}

void ObjectAmbientEmitters$AmbientSoundLogic::stopPlaying(BaseSoundEmitter var1, long var2) {
    // TODO: Implement stopPlaying
}

void ObjectAmbientEmitters$AmbientSoundLogic::checkParameters(BaseSoundEmitter var1, long var2) {
    // TODO: Implement checkParameters
}

int ObjectAmbientEmitter1::compare(ObjectWithDistance var1, ObjectWithDistance var2) {
    // TODO: Implement compare
    return 0;
}

} // namespace audio
} // namespace zombie
