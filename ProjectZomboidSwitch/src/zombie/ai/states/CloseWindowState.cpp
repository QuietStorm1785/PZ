#include "zombie/ai/states/CloseWindowState.h"

namespace zombie {
namespace ai {
namespace states {

CloseWindowState& CloseWindowState::instance() {
    static CloseWindowState _instance;
    return _instance;
}

void CloseWindowState::enter(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsClosingWindow", true);
    DebugLog::AI.debug("CloseWindowState::enter: IsClosingWindow set true for %p", var1);
}

void CloseWindowState::execute(IsoGameCharacter* var1) {
    if (!var1) return;
    // Example: play close window animation
    var1->playAnimation("CloseWindow");
    DebugLog::AI.debug("CloseWindowState::execute: playing close window animation for %p", var1);
}

void CloseWindowState::exit(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsClosingWindow", false);
    DebugLog::AI.debug("CloseWindowState::exit: IsClosingWindow set false for %p", var1);
}

void CloseWindowState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    if (!var1 || !var2) return;
    if (var2->m_EventName == "WindowClosed") {
        var1->setVariable("IsClosingWindow", false);
        DebugLog::AI.debug("CloseWindowState::animEvent: WindowClosed for %p", var1);
    }
}

bool CloseWindowState::isDoingActionThatCanBeCancelled() {
    // Example: closing window can be cancelled
    DebugLog::AI.debug("CloseWindowState::isDoingActionThatCanBeCancelled: true");
    return true;
}

void CloseWindowState::onAttemptFinished(IsoGameCharacter* var1, IsoWindow* var2) {
    if (!var1 || !var2) return;
    DebugLog::AI.debug("CloseWindowState::onAttemptFinished: attempt finished for %p on window %p", var1, var2);
}

void CloseWindowState::onSuccess(IsoGameCharacter* var1, IsoWindow* var2) {
    if (!var1 || !var2) return;
    var2->setClosed(true);
    DebugLog::AI.debug("CloseWindowState::onSuccess: window %p closed by %p", var2, var1);
}

void CloseWindowState::exert(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->getStats()->endurance -= 0.05f;
    DebugLog::AI.debug("CloseWindowState::exert: endurance reduced for %p", var1);
}

IsoWindow* CloseWindowState::getWindow(IsoGameCharacter* var1) {
    if (!var1) return nullptr;
    IsoWindow* window = var1->getNearbyWindow();
    DebugLog::AI.debug("CloseWindowState::getWindow: found window %p for %p", window, var1);
    return window;
}

} // namespace states
} // namespace ai
} // namespace zombie
