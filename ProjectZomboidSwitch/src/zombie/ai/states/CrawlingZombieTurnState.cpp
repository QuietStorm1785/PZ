#include "zombie/ai/states/CrawlingZombieTurnState.h"

namespace zombie {
namespace ai {
namespace states {

CrawlingZombieTurnState& CrawlingZombieTurnState::instance() {
    static CrawlingZombieTurnState _instance;
    return _instance;
}

void CrawlingZombieTurnState::enter(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsCrawlingTurn", true);
    DebugLog::AI.debug("CrawlingZombieTurnState::enter: IsCrawlingTurn set true for %p", var1);
}

void CrawlingZombieTurnState::execute(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->playAnimation("CrawlingTurn");
    DebugLog::AI.debug("CrawlingZombieTurnState::execute: playing crawling turn animation for %p", var1);
}

void CrawlingZombieTurnState::exit(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsCrawlingTurn", false);
    DebugLog::AI.debug("CrawlingZombieTurnState::exit: IsCrawlingTurn set false for %p", var1);
}

void CrawlingZombieTurnState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    if (!var1 || !var2) return;
    if (var2->m_EventName == "CrawlingTurnFinished") {
        var1->setVariable("IsCrawlingTurn", false);
        DebugLog::AI.debug("CrawlingZombieTurnState::animEvent: CrawlingTurnFinished for %p", var1);
    }
}

bool CrawlingZombieTurnState::calculateDir(IsoGameCharacter* var0, IsoDirections var1) {
    if (!var0) return false;
    bool correctDir = (var0->getDir() == var1);
    DebugLog::AI.debug("CrawlingZombieTurnState::calculateDir: %p dir=%d targetDir=%d correct=%d", var0, var0->getDir(), var1, correctDir);
    return correctDir;
}

} // namespace states
} // namespace ai
} // namespace zombie
