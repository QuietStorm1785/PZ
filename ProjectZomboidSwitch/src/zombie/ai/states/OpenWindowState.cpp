#include "zombie/ai/states/OpenWindowState.h"

namespace zombie {
namespace ai {
namespace states {

OpenWindowState& OpenWindowState::instance() {
    static OpenWindowState _instance;
    return _instance;
}
}

void OpenWindowState::enter(IsoGameCharacter* var1) {
    var1->setIgnoreMovement(true);
    var1->setHideWeaponModel(true);
    auto& params = var1->getStateMachineParams(this);
    IsoWindow* window = static_cast<IsoWindow*>(params[PARAM_WINDOW]);
    if (window && window->north) {
        if (window->getSquare()->getY() < var1->getY()) var1->setDir(IsoDirections::N);
        else var1->setDir(IsoDirections::S);
    } else if (window && window->getSquare()->getX() < var1->getX()) {
        var1->setDir(IsoDirections::W);
    } else {
        var1->setDir(IsoDirections::E);
    }
    var1->setVariable("bOpenWindow", true);
    DebugLog::AI.debug("OpenWindowState::enter: window open started");
}
}

void OpenWindowState::execute(IsoGameCharacter* var1) {
    auto& params = var1->getStateMachineParams(this);
    if (var1->getVariableBoolean("bOpenWindow")) {
        IsoPlayer* player = dynamic_cast<IsoPlayer*>(var1);
        if (player && !player->pressedMovement(false) && !player->pressedCancelAction()) {
            IsoWindow* window = static_cast<IsoWindow*>(params[PARAM_WINDOW]);
            if (!window || window->getObjectIndex() == -1) {
                var1->setVariable("bOpenWindow", false);
            } else {
                player->setCollidable(true);
                player->updateLOS();
                if (window->north) {
                    if (window->getSquare()->getY() < var1->getY()) var1->setDir(IsoDirections::N);
                    else var1->setDir(IsoDirections::S);
                } else if (window->getSquare()->getX() < var1->getX()) {
                    var1->setDir(IsoDirections::W);
                } else {
                    var1->setDir(IsoDirections::E);
                }
            }
        }
    }
    DebugLog::AI.debug("OpenWindowState::execute: window open logic executed");
}
}

void OpenWindowState::exit(IsoGameCharacter* var1) {
    var1->setVariable("bOpenWindow", false);
    var1->setIgnoreMovement(false);
    var1->setHideWeaponModel(false);
    DebugLog::AI.debug("OpenWindowState::exit: window open ended");
}
}

void OpenWindowState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    DebugLog::AI.debug("OpenWindowState::animEvent: event=%s", var2->m_EventName.c_str());
}
}

bool OpenWindowState::isDoingActionThatCanBeCancelled() {
    // Window opening can be cancelled
    DebugLog::AI.debug("OpenWindowState::isDoingActionThatCanBeCancelled: true");
    return true;
}
}

void OpenWindowState::onAttemptFinished(IsoGameCharacter* var1, IsoWindow* var2) {
    var1->setVariable("bOpenWindow", false);
    DebugLog::AI.debug("OpenWindowState::onAttemptFinished: attempt finished");
}
}

void OpenWindowState::onSuccess(IsoGameCharacter* var1, IsoWindow* var2) {
    var1->setVariable("bOpenWindow", false);
    DebugLog::AI.debug("OpenWindowState::onSuccess: window opened successfully");
}
}

void OpenWindowState::exert(IsoGameCharacter* var1) {
    var1->getStats()->endurance -= 0.05f;
    DebugLog::AI.debug("OpenWindowState::exert: endurance reduced");
}
}

void OpenWindowState::slideX(IsoGameCharacter* var1, float var2) {
    var1->x += var2;
    DebugLog::AI.debug("OpenWindowState::slideX: x=%f", var1->x);
}
}

void OpenWindowState::slideY(IsoGameCharacter* var1, float var2) {
    var1->y += var2;
    DebugLog::AI.debug("OpenWindowState::slideY: y=%f", var1->y);
}
}

void OpenWindowState::setParams(IsoGameCharacter* var1, IsoWindow* var2) {
    auto& params = var1->getStateMachineParams(this);
    params[PARAM_WINDOW] = var2;
    DebugLog::AI.debug("OpenWindowState::setParams: window param set");
}
}

} // namespace states
} // namespace ai
} // namespace zombie
