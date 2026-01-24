#include "zombie/ai/states/ZombieGetUpFromCrawlState.h"

namespace zombie {
namespace ai {
namespace states {

ZombieGetUpFromCrawlState& ZombieGetUpFromCrawlState::instance() {
    static ZombieGetUpFromCrawlState _instance;
    return _instance;
}

void ZombieGetUpFromCrawlState::enter(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsGettingUpFromCrawl", true);
    DebugLog::AI.debug("ZombieGetUpFromCrawlState::enter: IsGettingUpFromCrawl set true for %p", var1);
}

void ZombieGetUpFromCrawlState::execute(IsoGameCharacter* var1) {
    if (!var1) return;
    // Example: play get up animation or update state
    var1->playAnimation("GetUpFromCrawl");
    DebugLog::AI.debug("ZombieGetUpFromCrawlState::execute: playing get up animation for %p", var1);
}

void ZombieGetUpFromCrawlState::exit(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsGettingUpFromCrawl", false);
    DebugLog::AI.debug("ZombieGetUpFromCrawlState::exit: IsGettingUpFromCrawl set false for %p", var1);
}

void ZombieGetUpFromCrawlState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    if (!var1 || !var2) return;
    if (var2->m_EventName == "GetUpFinished") {
        var1->setVariable("IsGettingUpFromCrawl", false);
        DebugLog::AI.debug("ZombieGetUpFromCrawlState::animEvent: GetUpFinished for %p", var1);
    }
}

} // namespace states
} // namespace ai
} // namespace zombie
