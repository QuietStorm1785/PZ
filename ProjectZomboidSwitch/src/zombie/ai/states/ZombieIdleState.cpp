#include "zombie/ai/states/ZombieIdleState.h"

namespace zombie {
namespace ai {
namespace states {

ZombieIdleState ZombieIdleState::instance() {
    static ZombieIdleState _instance;
    return _instance;
}

void ZombieIdleState::enter(IsoGameCharacter* var1) {
    auto& var2 = var1->getStateMachineParams(this);
    IsoZombie* zombie = dynamic_cast<IsoZombie*>(var1);
    if (zombie) {
        zombie->soundSourceTarget = nullptr;
        zombie->soundAttract = 0.0f;
        zombie->movex = 0.0f;
        zombie->movey = 0.0f;
    }
    var1->setStateEventDelayTimer(this->pickRandomWanderInterval());
    if (!IngameState::instance) {
        var2[PARAM_TICK_COUNT] = 0L;
    } else {
        var2[PARAM_TICK_COUNT] = IngameState::instance->numberTicks;
    }
}

void ZombieIdleState::execute(IsoGameCharacter* var1) {
    IsoZombie* var2 = dynamic_cast<IsoZombie*>(var1);
    auto& var3 = var1->getStateMachineParams(this);
    if (var2) {
        var2->movex = 0.0f;
        var2->movey = 0.0f;
        if (Core::bLastStand) {
            IsoPlayer* closestPlayer = nullptr;
            float minDist = 1000000.0f;
            for (int i = 0; i < IsoPlayer::numPlayers; ++i) {
                if (IsoPlayer::players[i] && IsoPlayer::players[i]->DistTo(var1) < minDist && !IsoPlayer::players[i]->isDead()) {
                    minDist = IsoPlayer::players[i]->DistTo(var1);
                    closestPlayer = IsoPlayer::players[i];
                }
            }
            if (closestPlayer) {
                var2->pathToCharacter(closestPlayer);
            }
        } else {
            if (var2->bCrawling) {
                var1->setOnFloor(true);
            } else {
                var1->setOnFloor(false);
            }
            long tickCount = static_cast<long>(var3[PARAM_TICK_COUNT]);
            if (IngameState::instance->numberTicks - tickCount == 2L) {
                var2->parameterZombieState->setState(ParameterZombieState::State::Idle);
            }
            if (!var2->bIndoorZombie) {
                if (!var2->isUseless()) {
                    if (var2->getStateEventDelayTimer() <= 0.0f) {
                        var1->setStateEventDelayTimer(this->pickRandomWanderInterval());
                        int var6 = static_cast<int>(var1->getX()) + (Rand::Next(8) - 4);
                        int var7 = static_cast<int>(var1->getY()) + (Rand::Next(8) - 4);
                        if (var1->getCell()->getGridSquare(var6, var7, var1->getZ()) && var1->getCell()->getGridSquare(var6, var7, var1->getZ())->isFree(true)) {
                            var1->pathToLocation(var6, var7, static_cast<int>(var1->getZ()));
                            var2->AllowRepathDelay = 200.0f;
                        }
                    }
                    var2->networkAI->mindSync->zombieIdleUpdate();
                }
            }
        }
    }
}

void ZombieIdleState::exit(IsoGameCharacter* var1) {
    // No-op
}

void ZombieIdleState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    // No-op
}

float ZombieIdleState::pickRandomWanderInterval() {
    float interval = Rand::Next(400, 1000);
    if (!RainManager::isRaining()) {
        interval *= 1.5f;
    }
    return interval;
}

} // namespace states
} // namespace ai
} // namespace zombie
