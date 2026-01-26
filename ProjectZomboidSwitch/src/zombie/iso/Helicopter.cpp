#include "zombie/iso/Helicopter.h"

namespace zombie {
namespace iso {

void Helicopter::pickRandomTarget() {
    std::vector<std::shared_ptr<IsoGameCharacter>> candidates;
    if (GameServer::bServer) {
        candidates = GameServer::getPlayers();
    } else {
        if (GameClient::bClient) {
            throw std::runtime_error("can't call this on the client");
        }
        for (int i = 0; i < IsoPlayer::numPlayers; ++i) {
            auto player = IsoPlayer::players[i];
            if (player && player->isAlive()) {
                candidates.push_back(player);
            }
        }
    }
    if (candidates.empty()) {
        bActive = false;
        target = nullptr;
    } else {
        setTarget(candidates[Rand::Next(static_cast<int>(candidates.size()))]);
    }
}

void Helicopter::setTarget(std::shared_ptr<IsoGameCharacter> t) {
    target = t;
    x = target->x + 1000.0f;
    y = target->y + 1000.0f;
    targetX = target->x;
    targetY = target->y;
    move.x = targetX - x;
    move.y = targetY - y;
    if (glm::length(move) > 0.0f) move = glm::normalize(move) * 0.5f;
    state = HelicopterState::Arriving;
    bActive = true;
    DebugLog::log("chopper: activated");
}

void Helicopter::changeState(HelicopterState newState) {
    DebugLog::log("chopper: state " + std::to_string(static_cast<int>(state)) + " -> " + std::to_string(static_cast<int>(newState)));
    state = newState;
}

void Helicopter::update() {
    if (!bActive) return;
    if (GameClient::bClient) {
        updateSound();
        return;
    }
    float timeMult = 1.0f;
    if (GameServer::bServer) {
        if (!GameServer::PlayersContains(target)) {
            target = nullptr;
        }
    } else {
        timeMult = GameTime::getInstance()->getTrueMultiplier();
    }
    switch (state) {
        case HelicopterState::Arriving:
            if (target && !target->isDead()) {
                if (IsoUtils::DistanceToSquared(x, y, targetX, targetY) < 4.0f) {
                    changeState(HelicopterState::Hovering);
                    hoverTime = 0.0f;
                    searchTime = 0.0f;
                    timeSinceChopperSawPlayer = 0.0f;
                } else {
                    targetX = target->x;
                    targetY = target->y;
                    move.x = targetX - x;
                    move.y = targetY - y;
                    if (glm::length(move) > 0.0f) move = glm::normalize(move) * 0.75f;
                }
            } else {
                changeState(HelicopterState::Leaving);
            }
            break;
        case HelicopterState::Hovering:
            if (target && !target->isDead()) {
                hoverTime += GameTime::getInstance()->getRealworldSecondsSinceLastUpdate() * timeMult;
                if (hoverTime + searchTime > MAX_BOTHER_SECONDS) {
                    changeState(HelicopterState::Leaving);
                } else {
                    if (!isTargetVisible()) {
                        timeSinceChopperSawPlayer += GameTime::getInstance()->getRealworldSecondsSinceLastUpdate() * timeMult;
                        if (timeSinceChopperSawPlayer > MAX_UNSEEN_SECONDS) {
                            changeState(HelicopterState::Searching);
                            break;
                        }
                    }
                    if (IsoUtils::DistanceToSquared(x, y, targetX, targetY) < 1.0f) {
                        targetX = target->x + (Rand::Next(RADIUS_HOVER * 2) - RADIUS_HOVER);
                        targetY = target->y + (Rand::Next(RADIUS_HOVER * 2) - RADIUS_HOVER);
                        move.x = targetX - x;
                        move.y = targetY - y;
                        if (glm::length(move) > 0.0f) move = glm::normalize(move) * 0.5f;
                    }
                }
            } else {
                changeState(HelicopterState::Leaving);
            }
            break;
        case HelicopterState::Searching:
            if (target && !target->isDead()) {
                searchTime += GameTime::getInstance()->getRealworldSecondsSinceLastUpdate() * timeMult;
                if (hoverTime + searchTime > MAX_BOTHER_SECONDS) {
                    changeState(HelicopterState::Leaving);
                } else if (isTargetVisible()) {
                    timeSinceChopperSawPlayer = 0.0f;
                    changeState(HelicopterState::Hovering);
                } else if (IsoUtils::DistanceToSquared(x, y, targetX, targetY) < 1.0f) {
                    targetX = target->x + (Rand::Next(RADIUS_SEARCH * 2) - RADIUS_SEARCH);
                    targetY = target->y + (Rand::Next(RADIUS_SEARCH * 2) - RADIUS_SEARCH);
                    move.x = targetX - x;
                    move.y = targetY - y;
                    if (glm::length(move) > 0.0f) move = glm::normalize(move) * 0.5f;
                }
            } else {
                changeState(HelicopterState::Leaving);
            }
            break;
        case HelicopterState::Leaving: {
            bool anyNearby = false;
            if (GameServer::bServer) {
                auto players = GameServer::getPlayers();
                for (const auto& p : players) {
                    if (IsoUtils::DistanceToSquared(x, y, p->getX(), p->getY()) < 1000000.0f) {
                        anyNearby = true;
                        break;
                    }
                }
            } else {
                for (int i = 0; i < IsoPlayer::numPlayers; ++i) {
                    auto p = IsoPlayer::players[i];
                    if (p && IsoUtils::DistanceToSquared(x, y, p->getX(), p->getY()) < 1000000.0f) {
                        anyNearby = true;
                        break;
                    }
                }
            }
            if (!anyNearby) {
                deactivate();
                return;
            }
            break;
        }
    }
    if (Rand::Next(Rand::AdjustForFramerate(300)) == 0) {
        WorldSoundManager::instance->addSound(nullptr, static_cast<int>(x), static_cast<int>(y), 0, 500, 500);
    }
    float dx = move.x * (GameTime::getInstance()->getMultiplier() / 1.6f);
    float dy = move.y * (GameTime::getInstance()->getMultiplier() / 1.6f);
    if (state != HelicopterState::Leaving &&
        IsoUtils::DistanceToSquared(x + dx, y + dy, targetX, targetY) > IsoUtils::DistanceToSquared(x, y, targetX, targetY)) {
        x = targetX;
        y = targetY;
    } else {
        x += dx;
        y += dy;
    }
    if (GameServer::bServer) {
        GameServer::sendHelicopter(x, y, bActive);
    }
    updateSound();
}

void Helicopter::updateSound() {
    if (GameServer::bServer) return;
    if (Core::SoundDisabled) return;
    if (FMODManager::instance->getNumListeners() == 0) return;
    auto sound = GameSounds::getSound("Helicopter");
    if (!sound || sound->clips.empty()) return;
    if (inst == 0L) {
        auto clip = sound->getRandomClip();
        event = clip.eventDescription;
        if (event.address != 0) {
            javafmod::FMOD_Studio_LoadEventSampleData(event.address);
            inst = javafmod::FMOD_Studio_System_CreateEventInstance(event.address);
        }
    }
    if (inst != 0L) {
        float vol = SoundManager::instance->getSoundVolume();
        vol *= sound->getUserVolume();
        if (vol != volume) {
            javafmod::FMOD_Studio_EventInstance_SetVolume(inst, vol);
            volume = vol;
        }
        javafmod::FMOD_Studio_EventInstance3D(inst, x, y, 200.0f);
        float occ = 0.0f;
        if (IsoPlayer::numPlayers == 1) {
            auto sq = IsoPlayer::getInstance()->getCurrentSquare();
            if (sq && !sq->Is(IsoFlagType::exterior)) {
                occ = 1.0f;
            }
        }
        if (occlusion != occ) {
            occlusion = occ;
            javafmod::FMOD_Studio_EventInstance_SetParameterByName(inst, "Occlusion", occlusion);
        }
        if (!bSoundStarted) {
            javafmod::FMOD_Studio_StartEvent(inst);
            bSoundStarted = true;
        }
    }
}

bool Helicopter::isTargetVisible() const {
    if (target && !target->isDead()) {
        auto sq = target->getCurrentSquare();
        if (!sq) return false;
        if (!sq->getProperties().Is(IsoFlagType::exterior)) return false;
        auto zone = sq->getZone();
        if (!zone) return true;
        std::string type = zone->getType();
        return type != "Forest" && type != "DeepForest";
    }
    return false;
}

void Helicopter::deactivate() {
    if (bActive) {
        bActive = false;
        if (bSoundStarted) {
            javafmod::FMOD_Studio_EventInstance_Stop(inst, false);
            bSoundStarted = false;
        }
        if (GameServer::bServer) {
            GameServer::sendHelicopter(x, y, bActive);
        }
        DebugLog::log("chopper: deactivated");
    }
}

bool Helicopter::isActive() const {
    return bActive;
}

void Helicopter::clientSync(float nx, float ny, bool active) {
    if (GameClient::bClient) {
        x = nx;
        y = ny;
        if (!active) deactivate();
        bActive = active;
    }
}

} // namespace iso
} // namespace zombie
