#include "zombie/ai/states/ZombieEatBodyState.h"

namespace zombie {
namespace ai {
namespace states {

ZombieEatBodyState ZombieEatBodyState::instance() {
    static ZombieEatBodyState _instance;
    return _instance;
}

void ZombieEatBodyState::enter(IsoGameCharacter* var1) {
    IsoZombie* var2 = dynamic_cast<IsoZombie*>(var1);
    var2->setStateEventDelayTimer(Rand::Next(1800.0f, 3600.0f));
    var2->setVariable("onknees", Rand::Next(3) != 0);
    if (dynamic_cast<IsoDeadBody*>(var2->getEatBodyTarget())) {
        IsoDeadBody* var3 = static_cast<IsoDeadBody*>(var2->eatBodyTarget);
        if (!var2->isEatingOther(var3)) {
            auto& var4 = var1->getStateMachineParams(this);
            var4[0] = var3;
            var3->getEatingZombies().push_back(var2);
        }
        if (GameClient::bClient && var2->isLocal()) {
            GameClient::sendEatBody(var2, var2->getEatBodyTarget());
        }
    } else if (dynamic_cast<IsoPlayer*>(var2->getEatBodyTarget()) && GameClient::bClient && var2->isLocal()) {
        GameClient::sendEatBody(var2, var2->getEatBodyTarget());
    }
}

void ZombieEatBodyState::execute(IsoGameCharacter* var1) {
    IsoZombie* var2 = dynamic_cast<IsoZombie*>(var1);
    IsoMovingObject* var3 = var2->getEatBodyTarget();
    if (var2->getStateEventDelayTimer() <= 0.0f) {
        var2->setEatBodyTarget(nullptr, false);
    } else if (!GameServer::bServer && !Core::SoundDisabled && Rand::Next(Rand::AdjustForFramerate(15)) == 0) {
        var2->parameterZombieState->setState(ParameterZombieState::State::Eating);
    }
    var2->TimeSinceSeenFlesh = 0.0f;
    if (var3) {
        var2->faceThisObject(var3);
    }
    if (Rand::Next(Rand::AdjustForFramerate(450)) == 0) {
        var2->getCurrentSquare()->getChunk()->addBloodSplat(var2->x + Rand::Next(-0.5f, 0.5f), var2->y + Rand::Next(-0.5f, 0.5f), var2->z, Rand::Next(8));
        if (Rand::Next(6) == 0) {
            new IsoZombieGiblets(GibletType::B, var2->getCell(), var2->getX(), var2->getY(), var2->getZ() + 0.3f, Rand::Next(-0.2f, 0.2f) * 1.5f, Rand::Next(-0.2f, 0.2f) * 1.5f);
        } else {
            new IsoZombieGiblets(GibletType::A, var2->getCell(), var2->getX(), var2->getY(), var2->getZ() + 0.3f, Rand::Next(-0.2f, 0.2f) * 1.5f, Rand::Next(-0.2f, 0.2f) * 1.5f);
        }
        if (Rand::Next(4) == 0) {
            var2->addBlood(nullptr, true, false, false);
        }
    }
}

void ZombieEatBodyState::exit(IsoGameCharacter* var1) {
    IsoZombie* var2 = dynamic_cast<IsoZombie*>(var1);
    auto& var3 = var1->getStateMachineParams(this);
    if (dynamic_cast<IsoDeadBody*>(var3[0])) {
        static_cast<IsoDeadBody*>(var3[0])->getEatingZombies().remove(var2);
    }
    if (var2->parameterZombieState->isState(ParameterZombieState::State::Eating)) {
        var2->parameterZombieState->setState(ParameterZombieState::State::Idle);
    }
    if (GameClient::bClient && var2->isLocal()) {
        GameClient::sendEatBody(var2, nullptr);
    }
}

} // namespace states
} // namespace ai
} // namespace zombie
