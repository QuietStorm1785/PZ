#include "zombie/ai/states/FishingState.h"

namespace zombie {
namespace ai {
namespace states {

FishingState FishingState::instance() {
    static FishingState _instance;
    return _instance;
}

void FishingState::enter(IsoGameCharacter* var1) {
    // DebugLog::log("FISHINGSTATE - ENTER");
    var1->setVariable("FishingFinished", false);
    this->pauseTime = Rand::Next(60.0f, 120.0f);
}

void FishingState::execute(IsoGameCharacter* var1) {
    if (GameClient::bClient && dynamic_cast<IsoPlayer*>(var1) && static_cast<IsoPlayer*>(var1)->isLocalPlayer()) {
        std::string var2 = var1->getVariableString("FishingStage");
        if (!var2.empty() && var2 != this->stage) {
            this->stage = var2;
            if (var2 != "idle") {
                GameClient::sendEvent(static_cast<IsoPlayer*>(var1), "EventFishing");
            }
        }
    }
}

void FishingState::exit(IsoGameCharacter* var1) {
    // DebugLog::log("FISHINGSTATE - EXIT");
    var1->clearVariable("FishingStage");
    var1->clearVariable("FishingFinished");
}

void FishingState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    // No-op
}

} // namespace states
} // namespace ai
} // namespace zombie
