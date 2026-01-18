#include "IsoObject.h"
#include "IsoGridSquare.h"
#include "AudioInteractionSystem.h"

IsoObject::IsoObject() 
    : x(0.0f), y(0.0f), z(0.0f)
    , square(nullptr)
    , solid(false)
    , type("generic") {
}

IsoObject::~IsoObject() {
}

void IsoObject::render() {
    // Base implementation does nothing
}

void IsoObject::update() {
    // Base implementation does nothing
}

void IsoObject::onInteract(zombie::characters::IsoPlayer* /*player*/) {
    // Play interaction sound based on object type
    auto audio = AudioInteractionSystem::getInstance();
    audio->playInteractionSound(type, x, y);
}
