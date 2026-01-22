#include <string>
#include <unordered_map>
#include "zombie/AmbientSoundManager.h"

namespace zombie {

void AmbientSoundManager::update() {
    if (initialized) {
        updatePowerSupply();
        doOneShotAmbients();
    }
}

void AmbientSoundManager::addAmbient(const std::string& name, int x, int y, int radius, float volume) {
    // Add an ambient sound to the list
    ambient.emplace_back(this, name, static_cast<float>(x), static_cast<float>(y), static_cast<float>(radius), volume);
}

void AmbientSoundManager::addAmbientEmitter(float x, float y, int radius, const std::string& name) {
    // Add an ambient emitter (treated as a regular ambient for now)
    addAmbient(name, static_cast<int>(x), static_cast<int>(y), radius, 1.0f);
}

void AmbientSoundManager::addDaytimeAmbientEmitter(float x, float y, int radius, const std::string& name) {
    // Add a daytime ambient emitter (treated as a regular ambient for now)
    addAmbient(name, static_cast<int>(x), static_cast<int>(y), radius, 1.0f);
}

void AmbientSoundManager::doOneShotAmbients() {
    // Remove finished ambients and update others
    for (size_t i = 0; i < ambient.size(); ) {
        if (ambient[i].finished()) {
            // DebugLog::log(DebugType::Sound, "ambient: removing ambient sound " + ambient[i].name);
            ambient.erase(ambient.begin() + i);
        } else {
            ambient[i].update();
            ++i;
        }
    }
}

void AmbientSoundManager::init() {
    if (!initialized) {
        initialized = true;
    }
}

void AmbientSoundManager::addBlend(const std::string& name, float value, bool, bool, bool, bool) {
    // Store or update blend value for the given name
    blends[name] = value;
}
}

void AmbientSoundManager::addRandomAmbient() {
    // Multiplayer/server context
    if (!zombie::network::GameServer::Players.empty()) {
        auto& players = zombie::network::GameServer::Players;
        int idx = zombie::core::Rand::Next(static_cast<int>(players.size()));
        zombie::characters::IsoPlayer* player = players[idx];
        if (player) {
            std::string sound;
            int hour = zombie::GameTime::instance.getHour();
            if (hour > 7 && hour < 21) {
                int r = zombie::core::Rand::Next(3);
                if (r == 0 && zombie::core::Rand::Next(10) < 2) sound = "MetaDogBark";
                else if (r == 1 && zombie::core::Rand::Next(10) < 3) sound = "MetaScream";
            } else {
                int r = zombie::core::Rand::Next(5);
                if (r == 0 && zombie::core::Rand::Next(10) < 2) sound = "MetaDogBark";
                else if (r == 1 && zombie::core::Rand::Next(13) < 3) sound = "MetaScream";
                else if (r == 2) sound = "MetaOwl";
                else if (r == 3) sound = "MetaWolfHowl";
            }
            if (!sound.empty()) {
                float x = player->x, y = player->y;
                double angle = zombie::core::Rand::Next(-M_PI, M_PI);
                tempo.x = std::cos(angle);
                tempo.y = std::sin(angle);
                tempo.setLength(1000.0f);
                x += tempo.x;
                y += tempo.y;
                float volume = zombie::core::Rand::Next(0.2f, 0.5f);
                ambient.emplace_back(this, sound, x, y, 50.0f, volume);
                zombie::network::GameServer::sendAmbient(sound, static_cast<int>(x), static_cast<int>(y), 50, volume);
            }
        }
    } else {
        // Singleplayer/local context
        for (int i = 0; i < zombie::characters::IsoPlayer::numPlayers; ++i) {
            zombie::characters::IsoPlayer* player = zombie::characters::IsoPlayer::players[i];
            if (player) {
                std::string sound;
                int hour = zombie::GameTime::instance.getHour();
                if (hour > 7 && hour < 21) {
                    int r = zombie::core::Rand::Next(3);
                    if (r == 0 && zombie::core::Rand::Next(10) < 2) sound = "MetaDogBark";
                    else if (r == 1 && zombie::core::Rand::Next(10) < 3) sound = "MetaScream";
                } else {
                    int r = zombie::core::Rand::Next(5);
                    if (r == 0 && zombie::core::Rand::Next(10) < 2) sound = "MetaDogBark";
                    else if (r == 1 && zombie::core::Rand::Next(13) < 3) sound = "MetaScream";
                    else if (r == 2) sound = "MetaOwl";
                    else if (r == 3) sound = "MetaWolfHowl";
                }
                if (!sound.empty()) {
                    float x = player->x, y = player->y;
                    double angle = zombie::core::Rand::Next(-M_PI, M_PI);
                    tempo.x = std::cos(angle);
                    tempo.y = std::sin(angle);
                    tempo.setLength(1000.0f);
                    x += tempo.x;
                    y += tempo.y;
                    ambient.emplace_back(this, sound, x, y, 50.0f, zombie::core::Rand::Next(0.2f, 0.5f));
                }
            }
        }
    }
}

void AmbientSoundManager::doGunEvent() {
    // Multiplayer/server context
    if (!zombie::network::GameServer::Players.empty()) {
        auto& players = zombie::network::GameServer::Players;
        int idx = zombie::core::Rand::Next(static_cast<int>(players.size()));
        zombie::characters::IsoPlayer* player = players[idx];
        if (player) {
            std::string sound;
            float x = player->x, y = player->y;
            short radius = 600;
            double angle = zombie::core::Rand::Next(-M_PI, M_PI);
            tempo.x = std::cos(angle);
            tempo.y = std::sin(angle);
            tempo.setLength(radius - 100);
            x += tempo.x;
            y += tempo.y;
            // Optionally: add world sound here
            int r = zombie::core::Rand::Next(6);
            if (r == 0) sound = "MetaAssaultRifle1";
            else if (r == 1) sound = "MetaPistol1";
            else if (r == 2) sound = "MetaShotgun1";
            else if (r == 3) sound = "MetaPistol2";
            else if (r == 4) sound = "MetaPistol3";
            else if (r == 5) sound = "MetaShotgun1";
            float volume = 1.0f;
            ambient.emplace_back(this, sound, x, y, 700.0f, volume);
            zombie::network::GameServer::sendAmbient(sound, static_cast<int>(x), static_cast<int>(y), 700, volume);
        }
    } else {
        // Singleplayer/local context
        for (int i = 0; i < zombie::characters::IsoPlayer::numPlayers; ++i) {
            zombie::characters::IsoPlayer* player = zombie::characters::IsoPlayer::players[i];
            if (player) {
                std::string sound;
                float x = player->x, y = player->y;
                short radius = 600;
                double angle = zombie::core::Rand::Next(-M_PI, M_PI);
                tempo.x = std::cos(angle);
                tempo.y = std::sin(angle);
                tempo.setLength(radius - 100);
                x += tempo.x;
                y += tempo.y;
                int r = zombie::core::Rand::Next(6);
                if (r == 0) sound = "MetaAssaultRifle1";
                else if (r == 1) sound = "MetaPistol1";
                else if (r == 2) sound = "MetaShotgun1";
                else if (r == 3) sound = "MetaPistol2";
                else if (r == 4) sound = "MetaPistol3";
                else if (r == 5) sound = "MetaShotgun1";
                float volume = 1.0f;
                ambient.emplace_back(this, sound, x, y, 700.0f, volume);
            }
        }
    }
}

void AmbientSoundManager::doAlarm(RoomDef room) {
    // Check for valid room and alarmed building
    if (room && room.building && room.building->bAlarmed) {
        float volume = 1.0f;
        float x = room.x + room.getW() / 2.0f;
        float y = room.y + room.getH() / 2.0f;
        Ambient amb(this, "burglar2", x, y, 700.0f, volume);
        amb.duration = 49;
        amb.worldSoundDelay = 3;
        room.building->bAlarmed = false;
        room.building->setAllExplored(true);
        ambient.push_back(amb);
        // Send to clients if in server context
        if (!zombie::network::GameServer::Players.empty()) {
            zombie::network::GameServer::sendAmbient("burglar2", static_cast<int>(x), static_cast<int>(y), 700, volume);
        }
    }
}

void AmbientSoundManager::stop() {
    ambient.clear();
    initialized = false;
}

void AmbientSoundManager::updatePowerSupply() {
    // Get nights survived and shutoff modifier
    int nightsSurvived = zombie::GameTime::instance.getNightsSurvived();
    int elecShutModifier = zombie::SandboxOptions::instance.getElecShutModifier();
    bool hydroShouldBeOn = true;

    // Only set the shutoff time once, at the start of the game
    static bool shutoffTimeInitialized = false;
    static int shutoffDay = -1;
    if (!shutoffTimeInitialized) {
        // If the sandbox setting is 0 or negative, power never shuts off
        if (elecShutModifier > 0) {
            // Random day between 0 and elecShutModifier (default 30)
            shutoffDay = zombie::core::Rand::Next(elecShutModifier + 1);
        } else {
            shutoffDay = -1; // Never shuts off
        }
        shutoffTimeInitialized = true;
    }

    // Power should be on if we haven't reached the shutoff day, or if shutoff is disabled
    if (shutoffDay < 0 || nightsSurvived < shutoffDay) {
        hydroShouldBeOn = true;
    } else {
        hydroShouldBeOn = false;
    }

    if (electricityShutOffState == -1) {
        zombie::iso::IsoWorld::instance.setHydroPowerOn(hydroShouldBeOn);
    }
    if (electricityShutOffState == 0) {
        if (hydroShouldBeOn) {
            zombie::iso::IsoWorld::instance.setHydroPowerOn(true);
            checkHaveElectricity();
            electricityShutOffTime = 0L;
        } else if (electricityShutOffTime != 0L && std::chrono::system_clock::now().time_since_epoch().count() >= electricityShutOffTime) {
            electricityShutOffTime = 0L;
            zombie::iso::IsoWorld::instance.setHydroPowerOn(false);
            checkHaveElectricity();
        }
    }
    if (electricityShutOffState == 1 && !hydroShouldBeOn) {
        // Set a future time for shutoff (simulate warning period, e.g. 3 days in ms)
        // In-game day is 24*60*60*1000 ms, but here we just simulate a delay (e.g. 3 real seconds)
        electricityShutOffTime = std::chrono::system_clock::now().time_since_epoch().count() + 3000L;
    }
    electricityShutOffState = hydroShouldBeOn ? 1 : 0;
}

void AmbientSoundManager::checkHaveElectricity() {
    // Called when electricity state may have changed. Add logic here as needed.
    bool isOn = zombie::iso::IsoWorld::instance.isHydroPowerOn();
    // Log the state for debugging
    // (Uncomment if DebugLog is available)
    // DebugLog::log(DebugType::Sound, std::string("Electricity is now ") + (isOn ? "ON" : "OFF"));

    // Trigger a global event (placeholder, replace with actual event system if available)
    // Example: EventManager::trigger("ElectricityStateChanged", isOn);

    // Play an audio cue for all players (placeholder, replace with actual audio system if available)
    const char* cue = isOn ? "ElectricityOn" : "ElectricityOff";
    for (int i = 0; i < zombie::characters::IsoPlayer::numPlayers; ++i) {
        zombie::characters::IsoPlayer* player = zombie::characters::IsoPlayer::players[i];
        if (player) {
            // Example: player->playSound(cue);
        }
    }

    // Optionally, display a notification (placeholder, replace with actual UI system if available)
    // Example: NotificationManager::show(isOn ? "The power is back on!" : "The power has shut off.");
}

} // namespace zombie