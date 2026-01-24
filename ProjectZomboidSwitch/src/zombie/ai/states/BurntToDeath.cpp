#include "zombie/ai/states/BurntToDeath.h"

namespace zombie {
namespace ai {
namespace states {

BurntToDeath BurntToDeath::instance() {
    static BurntToDeath _instance;
    return _instance;
}

void BurntToDeath::enter(IsoGameCharacter var1) {
    if (dynamic_cast<IsoSurvivor*>(&var1)) {
        var1.getDescriptor().bDead = true;
    }
    if (!dynamic_cast<IsoZombie*>(&var1)) {
        var1.PlayAnimUnlooped("Die");
    } else {
        var1.PlayAnimUnlooped("ZombieDeath");
    }
    var1.def.AnimFrameIncrease = 0.25F;
    var1.setStateMachineLocked(true);
    std::string sound = var1.isFemale() ? "FemaleZombieDeath" : "MaleZombieDeath";
    var1.getEmitter().playVocals(sound);
    if (GameServer::bServer && dynamic_cast<IsoZombie*>(&var1)) {
        GameServer::sendZombieSound(ZombieSound::Burned, static_cast<IsoZombie*>(&var1));
    }
}

void BurntToDeath::execute(IsoGameCharacter var1) {
    if (static_cast<int>(var1.def.Frame) == var1.sprite.CurrentAnim.Frames.size() - 1) {
        if (&var1 == TutorialManager::instance.wife) {
            var1.dir = IsoDirections::S;
        }
        var1.RemoveAttachedAnims();
        if (GameClient::bClient && dynamic_cast<IsoZombie*>(&var1)) {
            GameClient::sendZombieDeath(static_cast<IsoZombie*>(&var1));
        }
        if (!GameClient::bClient) {
            new IsoDeadBody(&var1);
        }
    }
}

new BurntToDeath::IsoDeadBody() {
    // Already handled in execute method above
    return nullptr;
}

void BurntToDeath::exit(IsoGameCharacter var1) {
    // No-op (matches Java)
}

} // namespace states
} // namespace ai
} // namespace zombie
