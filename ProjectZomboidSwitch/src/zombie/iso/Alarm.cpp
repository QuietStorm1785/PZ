#include "zombie/iso/Alarm.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include <iostream>

namespace zombie {
namespace iso {

int64_t Alarm::inst = 0;
FMOD_STUDIO_EVENT_DESCRIPTION* Alarm::event = nullptr;

Alarm::Alarm(int x_, int y_)
    : x(x_), y(y_) {
    const uint8_t duration = 49;
    float worldAge = static_cast<float>(GameTime::instance->getWorldAgeHours());
    endGameTime = worldAge + duration / 3600.0f * (1440.0f / GameTime::instance->getMinutesPerDay());
}

void Alarm::update() {
    if (!GameClient::bClient) {
        WorldSoundManager::instance->addSound(this, x, y, 0, 600, 600);
    }
    if (!GameServer::bServer) {
        updateSound();
        if (GameTime::getInstance()->getWorldAgeHours() >= endGameTime) {
            if (inst != 0) {
                javafmod::FMOD_Studio_EventInstance_Stop(inst, false);
                inst = 0;
            }
            finished = true;
        }
    }
}

void Alarm::updateSound() {
    if (!GameServer::bServer && !Core::SoundDisabled && !finished) {
        if (FMODManager::instance->getNumListeners() != 0) {
            if (inst == 0) {
                event = FMODManager::instance->getEventDescription("event:/Meta/HouseAlarm");
                if (event) {
                    javafmod::FMOD_Studio_LoadEventSampleData(event->address);
                    inst = javafmod::FMOD_Studio_System_CreateEventInstance(event->address);
                }
            }
            if (inst > 0) {
                float vol = SoundManager::instance->getSoundVolume();
                GameSound* gs = GameSounds::getSound("HouseAlarm");
                if (gs) vol *= gs->getUserVolume();
                if (vol != volume) {
                    javafmod::FMOD_Studio_EventInstance_SetVolume(inst, vol);
                    volume = vol;
                }
                javafmod::FMOD_Studio_EventInstance3D(inst, x, y, 0.0f);
                auto state = javafmod::FMOD_Studio_GetPlaybackState(inst);
                if (state != FMOD_STUDIO_PLAYBACK_STATE::FMOD_STUDIO_PLAYBACK_PLAYING.index &&
                    state != FMOD_STUDIO_PLAYBACK_STATE::FMOD_STUDIO_PLAYBACK_STARTING.index) {
                    if (state == FMOD_STUDIO_PLAYBACK_STATE::FMOD_STUDIO_PLAYBACK_STOPPING.index) {
                        finished = true;
                        return;
                    }
                    javafmod::FMOD_Studio_StartEvent(inst);
                    std::cout << javafmod::FMOD_Studio_GetPlaybackState(inst) << std::endl;
                }
                float occ = 0.0f;
                if (IsoPlayer::numPlayers == 1) {
                    IsoGridSquare* sq = IsoPlayer::getInstance()->getCurrentSquare();
                    if (sq && !sq->Is(IsoFlagType::exterior)) {
                        occ = 0.2f;
                        IsoGridSquare* sq2 = IsoWorld::instance->getCell()->getGridSquare(x, y, 0);
                        if (sq2 && sq2->getBuilding() == sq->getBuilding()) {
                            occ = 0.0f;
                        }
                    }
                }
                if (occlusion != occ) {
                    occlusion = occ;
                    javafmod::FMOD_Studio_EventInstance_SetParameterByName(inst, "Occlusion", occlusion);
                }
            }
        }
    }
}

} // namespace iso
} // namespace zombie
