#include "zombie/iso/Alarm.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include <iostream>

namespace zombie {
namespace iso {

int64_t Alarm::inst = 0;
OpenALSoundEventDescription Alarm::event = {};

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
                OpenALSoundEmitter::stopEvent(inst, false);
                inst = 0;
            }
            finished = true;
        }
    }
}

void Alarm::updateSound() {
    if (!GameServer::bServer && !Core::SoundDisabled && !finished) {
        if (inst == 0) {
            event = OpenALSoundEmitter::getEventDescription("event:/Meta/HouseAlarm");
            if (event.address != 0) {
                inst = OpenALSoundEmitter::createEventInstance(event.address);
            }
        }
        if (inst > 0) {
            float vol = SoundManager::instance->getSoundVolume();
            GameSound* gs = GameSounds::getSound("HouseAlarm");
            if (gs) vol *= gs->getUserVolume();
            if (vol != volume) {
                OpenALSoundEmitter::setEventInstanceVolume(inst, vol);
                volume = vol;
            }
            OpenALSoundEmitter::setEventInstance3D(inst, x, y, 0.0f);
            // OpenAL: No direct playback state, assume always playing after start
            if (!finished) {
                OpenALSoundEmitter::startEvent(inst);
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
                OpenALSoundEmitter::setEventInstanceParameterByName(inst, "Occlusion", occlusion);
            }
        }
    }
}

} // namespace iso
} // namespace zombie
