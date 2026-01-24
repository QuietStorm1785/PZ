#include "zombie/ai/states/IdleState.h"

namespace zombie {
namespace ai {
namespace states {

IdleState& IdleState::instance() {
    static IdleState _instance;
    return _instance;
}

void IdleState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    if (!var1 || !var2) return;
    DebugLog::AI.debug("IdleState::animEvent: event %s for %p", var2->m_EventName.c_str(), var1);
}

} // namespace states
} // namespace ai
} // namespace zombie
