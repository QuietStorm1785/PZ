#include "zombie/ai/states/ZombieGetDownState.h"

namespace zombie {
namespace ai {
namespace states {


ZombieGetDownState& ZombieGetDownState::instance() {
    static ZombieGetDownState _instance;
    return _instance;
}

void ZombieGetDownState::enter(IsoGameCharacter* character) {
    if (!character) return;
    auto& params = character->getStateMachineParams(this);
    params[PARAM_PREV_STATE] = character->getStateMachine()->getPrevious();
    params[PARAM_START_X] = character->getX();
    params[PARAM_START_Y] = character->getY();
    character->setStateEventDelayTimer(static_cast<float>(params[PARAM_WAIT_TIME]));
}

void ZombieGetDownState::execute(IsoGameCharacter* character) {
    if (!character) return;
    auto& params = character->getStateMachineParams(this);
    // No-op, matches Java
}

void ZombieGetDownState::exit(IsoGameCharacter* character) {
    if (!character) return;
    auto& params = character->getStateMachineParams(this);
    IsoZombie* zombie = dynamic_cast<IsoZombie*>(character);
    if (zombie) {
        zombie->setStateEventDelayTimer(0.0f);
        zombie->AllowRepathDelay = 0.0f;
        auto prevState = params[PARAM_PREV_STATE];
        if (prevState == PathFindState::instance()) {
            if (!character->getPathFindBehavior2()->getTargetChar()) {
                character->setVariable("bPathfind", true);
                character->setVariable("bMoving", false);
            } else if (zombie->isTargetLocationKnown()) {
                character->pathToCharacter(character->getPathFindBehavior2()->getTargetChar());
            } else if (zombie->LastTargetSeenX != -1) {
                character->pathToLocation(zombie->LastTargetSeenX, zombie->LastTargetSeenY, zombie->LastTargetSeenZ);
            }
        } else if (prevState == WalkTowardState::instance()) {
            character->setVariable("bPathFind", false);
            character->setVariable("bMoving", true);
        }
    }
}

void ZombieGetDownState::animEvent(IsoGameCharacter* character, AnimEvent* event) {
    IsoZombie* zombie = dynamic_cast<IsoZombie*>(character);
    if (zombie && event && event->m_EventName == "StartCrawling" && !zombie->isCrawling()) {
        zombie->toggleCrawling();
    }
}

bool ZombieGetDownState::isNearStartXY(IsoGameCharacter* character) {
    if (!character) return false;
    auto& params = character->getStateMachineParams(this);
    auto itX = params.find(PARAM_START_X);
    auto itY = params.find(PARAM_START_Y);
    if (itX != params.end() && itY != params.end()) {
        float x = static_cast<float>(itX->second);
        float y = static_cast<float>(itY->second);
        return character->DistToSquared(x, y) <= 0.25f;
    }
    return false;
}

void ZombieGetDownState::setParams(IsoGameCharacter* character) {
    if (!character) return;
    auto& params = character->getStateMachineParams(this);
    params[PARAM_WAIT_TIME] = Rand::Next(60.0f, 150.0f);
}

} // namespace states
} // namespace ai
} // namespace zombie
