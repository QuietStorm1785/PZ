#include "SleepingEvent.h"

namespace zombie {
namespace ai {
namespace sadisticAIDirector {

SleepingEvent& SleepingEvent::instance() {
    static SleepingEvent instance_;
    return instance_;
}

bool SleepingEvent::zombiesInvasion = false;

void SleepingEvent::setPlayerFallAsleep(IsoPlayer& player, int sleepTime) {
    SleepingEventData eventData = player.getOrCreateSleepingEventData();
    eventData.reset();
    // ...modernized logic from header...
}

// Implement other methods with modern C++ signatures and documentation as needed

} // namespace sadisticAIDirector
} // namespace ai
} // namespace zombie
#include "zombie/ai/sadisticAIDirector/SleepingEvent.h"

namespace zombie {
namespace ai {
namespace sadisticAIDirector {

void SleepingEvent::setPlayerFallAsleep(IsoPlayer var1, int var2) {
    SleepingEventData eventData = var1.getOrCreateSleepingEventData();
    eventData.reset();
    if (!IsoWorld::getZombiesEnabled()) {
        if (ClimateManager::getInstance().isRaining() && isExposedToPrecipitation(var1)) {
            eventData.bRaining = true;
            eventData.bWasRainingAtStart = true;
            eventData.rainTimeStartHours = GameTime::getInstance().getWorldAgeHours();
        }
        eventData.sleepingTime = var2;
        var1.setTimeOfSleep(GameTime::instance.getTimeOfDay());
        doDelayToSleep(var1);
        checkNightmare(var1, var2);
        if (eventData.nightmareWakeUp <= -1) {
            if (SandboxOptions::instance.SleepingEvent.getValue() != 1 && zombiesInvasion) {
                if (var1.getCurrentSquare() == nullptr || var1.getCurrentSquare().getZone() == nullptr || !var1.getCurrentSquare().getZone().haveConstruction) {
                    bool var4 = false;
                    if ((GameTime::instance.getHour() >= 0 && GameTime::instance.getHour() < 5 || GameTime::instance.getHour() > 18) && var2 >= 4) {
                        var4 = true;
                    }
                    uint8_t var5 = 20;
                    if (SandboxOptions::instance.SleepingEvent.getValue() == 3) {
                        var5 = 45;
                    }
                    if (Rand::Next(100) <= var5 && var1.getCell()->getZombieList().size() >= 1 && var2 >= 4) {
                        int var6 = 0;
                        if (var1.getCurrentBuilding() != nullptr) {
                            for (int var9 = 0; var9 < 3; var9++) {
                                for (int var10 = var1.getCurrentBuilding()->getDef().getX() - 2; var10 < var1.getCurrentBuilding()->getDef().getX2() + 2; var10++) {
                                    for (int var11 = var1.getCurrentBuilding()->getDef().getY() - 2; var11 < var1.getCurrentBuilding()->getDef().getY2() + 2; var11++) {
                                        IsoGridSquare* var7 = IsoWorld::instance.getCell()->getGridSquare(var10, var11, var9);
                                        if (var7 != nullptr) {
                                            bool var12 = var7->haveElectricity() || IsoWorld::instance.isHydroPowerOn();
                                            if (var12) {
                                                for (int var13 = 0; var13 < var7->getObjects().size(); var13++) {
                                                    IsoObject* var14 = static_cast<IsoObject*>(var7->getObjects()[var13]);
                                                    if (var14->getContainer() != nullptr && (var14->getContainer()->getType() == "fridge" || var14->getContainer()->getType() == "freezer")) {
                                                        var6 += 3;
                                                    }
                                                    if (dynamic_cast<IsoStove*>(var14) && static_cast<IsoStove*>(var14)->Activated()) {
                                                        var6 += 5;
                                                    }
                                                    if (dynamic_cast<IsoTelevision*>(var14) && static_cast<IsoTelevision*>(var14)->getDeviceData().getIsTurnedOn()) {
                                                        var6 += 30;
                                                    }
                                                    if (dynamic_cast<IsoRadio*>(var14) && static_cast<IsoRadio*>(var14)->getDeviceData().getIsTurnedOn()) {
                                                        var6 += 30;
                                                    }
                                                }
                                            }
                                            IsoWindow* var8 = var7->getWindow();
                                            if (var8 != nullptr) {
                                                var6 += checkWindowStatus(*var8);
                                            }
                                            IsoDoor* var17 = var7->getIsoDoor();
                                            if (var17 != nullptr && var17->isExteriorDoor(nullptr) && var17->IsOpen()) {
                                                var6 += 25;
                                                eventData.openDoor = var17;
                                            }
                                        }
                                    }
                                }
                            }
                            if (SandboxOptions::instance.SleepingEvent.getValue() == 3) {
                                var6 = static_cast<int>(var6 * 1.5);
                            }
                            if (var6 > 70) {
                                var6 = 70;
                            }
                            if (!var4) {
                                var6 /= 2;
                            }
                            if (Rand::Next(100) <= var6) {
                                eventData.forceWakeUpTime = Rand::Next(var2 - 4, var2 - 1);
                                eventData.zombiesIntruders = true;
                            }
                        }
                    }
                }
            }
        }
    }
}

void SleepingEvent::doDelayToSleep(IsoPlayer var1) {
    float var2 = 0.3F;
    float var3 = 2.0F;
    if (var1.Traits.Insomniac.isSet()) {
        var2 = 1.0F;
    }
    if (var1.getMoodles().getMoodleLevel(MoodleType::Pain) > 0) {
        var2 += 1.0F + var1.getMoodles().getMoodleLevel(MoodleType::Pain) * 0.2F;
    }
    if (var1.getMoodles().getMoodleLevel(MoodleType::Stress) > 0) {
        var2 *= 1.2F;
    }
    if (var1.getBedType() == "badBed") {
        var2 *= 1.3F;
    } else if (var1.getBedType() == "goodBed") {
        var2 *= 0.8F;
    } else if (var1.getBedType() == "floor") {
        var2 *= 1.6F;
    }
    if (var1.Traits.NightOwl.isSet()) {
        var2 *= 0.5F;
    }
    if (var1.getSleepingTabletEffect() > 1000.0F) {
        var2 = 0.1F;
    }
    if (var2 > var3) {
        var2 = var3;
    }
    float var4 = Rand::Next(0.0F, var2);
    var1.setDelayToSleep(GameTime::instance.getTimeOfDay() + var4);
}

void SleepingEvent::checkNightmare(IsoPlayer var1, int var2) {
    if (!GameClient::bClient) {
        SleepingEventData eventData = var1.getOrCreateSleepingEventData();
        if (var2 >= 3) {
            int chance = 5 + var1.getMoodles().getMoodleLevel(MoodleType::Stress) * 10;
            if (Rand::Next(100) < chance) {
                eventData.nightmareWakeUp = Rand::Next(3, var2 - 2);
            }
        }
    }
}

int SleepingEvent::checkWindowStatus(IsoWindow var1) {
    IsoGridSquare* square = var1.getSquare();
    if (square->getRoom() == nullptr) {
        if (!var1.north) {
            square = square->getCell()->getGridSquare(square->getX() - 1, square->getY(), square->getZ());
        } else {
            square = square->getCell()->getGridSquare(square->getX(), square->getY() - 1, square->getZ());
        }
    }
    int score = 0;
    bool hasLight = false;
    for (auto& lightSwitch : square->getRoom()->lightSwitches) {
        if (lightSwitch->isActivated()) {
            hasLight = true;
            break;
        }
    }
    if (hasLight) {
        score = 20;
        if (var1.HasCurtains() != nullptr && !var1.HasCurtains()->open) {
            score -= 17;
        }
        IsoBarricade* barricade = var1.getBarricadeOnOppositeSquare();
        if (!barricade) barricade = var1.getBarricadeOnSameSquare();
        if (barricade && (barricade->getNumPlanks() > 4 || barricade->isMetal())) {
            score -= 20;
        }
        if (score < 0) score = 0;
        if (square->getZ() > 0) score /= 2;
        return score;
    } else {
        score = 5;
        if (var1.HasCurtains() != nullptr && !var1.HasCurtains()->open) {
            score -= 5;
        }
        IsoBarricade* barricade = var1.getBarricadeOnOppositeSquare();
        if (!barricade) barricade = var1.getBarricadeOnSameSquare();
        if (barricade && (barricade->getNumPlanks() > 3 || barricade->isMetal())) {
            score -= 5;
        }
        if (score < 0) score = 0;
        if (square->getZ() > 0) score /= 2;
        return score;
    }
}

void SleepingEvent::update(IsoPlayer var1) {
    if (var1 != nullptr) {
        SleepingEventData eventData = var1.getOrCreateSleepingEventData();
        if (eventData.nightmareWakeUp == static_cast<int>(var1.getAsleepTime())) {
            var1.getStats().Panic += 70.0F;
            var1.getStats().stress += 0.5F;
            WorldSoundManager::instance.addSound(var1, static_cast<int>(var1.getX()), static_cast<int>(var1.getY()), static_cast<int>(var1.getZ()), 6, 1);
            SoundManager::instance.setMusicWakeState(var1, "WakeNightmare");
            wakeUp(var1);
        }
        if (eventData.forceWakeUpTime == static_cast<int>(var1.getAsleepTime()) && eventData.zombiesIntruders) {
            spawnZombieIntruders(var1);
            WorldSoundManager::instance.addSound(var1, static_cast<int>(var1.getX()), static_cast<int>(var1.getY()), static_cast<int>(var1.getZ()), 6, 1);
            SoundManager::instance.setMusicWakeState(var1, "WakeZombies");
            wakeUp(var1);
        }
        updateRain(var1);
        updateSnow(var1);
        updateTemperature(var1);
        updateWetness(var1);
    }
}

void SleepingEvent::updateRain(IsoPlayer var1) {
    SleepingEventData eventData = var1.getOrCreateSleepingEventData();
    if (!ClimateManager::getInstance().isRaining()) {
        eventData.bRaining = false;
        eventData.bWasRainingAtStart = false;
        eventData.rainTimeStartHours = -1.0;
    } else if (isExposedToPrecipitation(var1)) {
        double now = GameTime::getInstance().getWorldAgeHours();
        if (!eventData.bWasRainingAtStart) {
            if (!eventData.bRaining) {
                eventData.rainTimeStartHours = now;
            }
            if (eventData.getHoursSinceRainStarted() >= 0.16666666666666666) {
                // Additional rain logic if needed
            }
        }
        eventData.bRaining = true;
    }
}

void SleepingEvent::updateSnow(IsoPlayer var1) {
    // Update snow state for sleeping event
    // Add more game logic as needed
}

void SleepingEvent::updateTemperature(IsoPlayer var1) {
    // Update temperature state for sleeping event
    // Add more game logic as needed
}

void SleepingEvent::updateWetness(IsoPlayer var1) {
    // Update wetness state for sleeping event
    // Add more game logic as needed
}

bool SleepingEvent::isExposedToPrecipitation(IsoGameCharacter var1) {
    if (var1.getCurrentSquare() == nullptr) return false;
    if (var1.getCurrentSquare()->isInARoom() || var1.getCurrentSquare()->haveRoof) return false;
    if (var1.getBed() != nullptr && var1.getBed()->getName() == "Tent") return false;
    BaseVehicle* vehicle = var1.getVehicle();
    return vehicle == nullptr || !vehicle->hasRoof(vehicle->getSeat(var1));
}

void SleepingEvent::spawnZombieIntruders(IsoPlayer var1) {
    SleepingEventData eventData = var1.getOrCreateSleepingEventData();
    IsoGridSquare* square = nullptr;
    if (eventData.openDoor != nullptr) {
        square = eventData.openDoor->getSquare();
    } else {
        eventData.weakestWindow = getWeakestWindow(var1);
        if (eventData.weakestWindow != nullptr && eventData.weakestWindow->getZ() == 0.0F) {
            if (!eventData.weakestWindow->north) {
                if (eventData.weakestWindow->getSquare()->getRoom() == nullptr) {
                    square = eventData.weakestWindow->getSquare();
                } else {
                    square = eventData.weakestWindow->getSquare()->getCell()->getGridSquare(eventData.weakestWindow->getSquare()->getX() - 1, eventData.weakestWindow->getSquare()->getY(), eventData.weakestWindow->getSquare()->getZ());
                }
            } else if (eventData.weakestWindow->getSquare()->getRoom() == nullptr) {
                square = eventData.weakestWindow->getSquare();
            } else {
                square = eventData.weakestWindow->getSquare()->getCell()->getGridSquare(eventData.weakestWindow->getSquare()->getX(), eventData.weakestWindow->getSquare()->getY() + 1, eventData.weakestWindow->getSquare()->getZ());
            }
            IsoBarricade* barricade = eventData.weakestWindow->getBarricadeOnOppositeSquare();
            if (!barricade) barricade = eventData.weakestWindow->getBarricadeOnSameSquare();
            if (barricade) {
                barricade->Damage(Rand::Next(500, 900));
            } else {
                eventData.weakestWindow->Damage(200.0F);
                eventData.weakestWindow->smashWindow();
                if (eventData.weakestWindow->HasCurtains() != nullptr) {
                    eventData.weakestWindow->removeSheet(nullptr);
                }
                if (square != nullptr) {
                    square->addBrokenGlass();
                }
            }
        }
    }
    var1.getStats().setPanic(var1.getStats().getPanic() + Rand::Next(30, 60));
    if (square != nullptr) {
        if (IsoWorld::getZombiesEnabled()) {
            int numZombies = Rand::Next(3) + 1;
            for (int i = 0; i < numZombies; ++i) {
                VirtualZombieManager::instance.choices.clear();
                VirtualZombieManager::instance.choices.push_back(square);
                IsoZombie* zombie = VirtualZombieManager::instance.createRealZombieAlways(IsoDirections::fromIndex(Rand::Next(8)).index(), false);
                if (zombie != nullptr) {
                    zombie->setTarget(var1);
                    zombie->pathToCharacter(var1);
                    zombie->spotted(var1, true);
                    ZombieSpawnRecorder::instance.record(zombie, "SleepingEvent");
                }
            }
        }
    }
}

IsoWindow SleepingEvent::getWeakestWindow(IsoPlayer var1) {
    IsoGridSquare* square = nullptr;
    IsoWindow* weakest = nullptr;
    int maxScore = 0;
    for (int x = var1.getCurrentBuilding()->getDef().getX() - 2; x < var1.getCurrentBuilding()->getDef().getX2() + 2; ++x) {
        for (int y = var1.getCurrentBuilding()->getDef().getY() - 2; y < var1.getCurrentBuilding()->getDef().getY2() + 2; ++y) {
            square = IsoWorld::instance.getCell()->getGridSquare(x, y, 0);
            if (square != nullptr) {
                IsoWindow* window = square->getWindow();
                if (window != nullptr) {
                    int score = checkWindowStatus(*window);
                    if (score > maxScore) {
                        maxScore = score;
                        weakest = window;
                    }
                }
            }
        }
    }
    return weakest;
}

void SleepingEvent::wakeUp(IsoGameCharacter var1) {
    if (var1 != nullptr) {
        wakeUp(var1, false);
    }
}

void SleepingEvent::wakeUp(IsoGameCharacter var1, bool var2) {
    SleepingEventData eventData = var1.getOrCreateSleepingEventData();
    if (GameClient::bClient && !var2) {
        GameClient::instance.wakeUpPlayer(static_cast<IsoPlayer*>(var1));
    }
    bool fade = false;
    IsoPlayer* player = dynamic_cast<IsoPlayer*>(var1);
    if (player != nullptr && player->isLocalPlayer()) {
        UIManager::setFadeBeforeUI(player->getPlayerNum(), true);
        UIManager::FadeIn(player->getPlayerNum(), 2.0);
        if (!GameClient::bClient && IsoPlayer::allPlayersAsleep()) {
            UIManager::getSpeedControls().SetCurrentGameSpeed(1);
            fade = true;
        }
        var1.setLastHourSleeped(static_cast<int>(player->getHoursSurvived()));
    }
    var1.setForceWakeUpTime(-1.0F);
    var1.setAsleep(false);
    if (fade) {
        try {
            GameWindow::save(true);
        } catch (...) {
            ExceptionLogger::logException();
        }
    }
    BodyPart* neck = var1.getBodyDamage()->getBodyPart(BodyPartType::Neck);
    float sleepFactor = eventData.sleepingTime / 8.0F;
    if (var1.getBedType() == "goodBed") {
        var1.getStats().setFatigue(var1.getStats().getFatigue() - Rand::Next(0.05F, 0.12F) * sleepFactor);
        if (var1.getStats().getFatigue() < 0.0F) {
            var1.getStats().setFatigue(0.0F);
        }
    } else if (var1.getBedType() == "badBed") {
        var1.getStats().setFatigue(var1.getStats().getFatigue() + Rand::Next(0.1F, 0.2F) * sleepFactor);
        if (Rand::Next(5) == 0) {
            neck->AddDamage(Rand::Next(5.0F, 15.0F));
            neck->setAdditionalPain(neck->getAdditionalPain() + Rand::Next(30.0F, 50.0F));
        }
    } else if (var1.getBedType() == "floor") {
        var1.getStats().setFatigue(var1.getStats().getFatigue() + Rand::Next(0.15F, 0.25F) * sleepFactor);
        if (Rand::Next(5) == 0) {
            neck->AddDamage(Rand::Next(10.0F, 20.0F));
            neck->setAdditionalPain(neck->getAdditionalPain() + Rand::Next(30.0F, 50.0F));
        }
    } else if (Rand::Next(10) == 0) {
        neck->AddDamage(Rand::Next(3.0F, 12.0F));
        neck->setAdditionalPain(neck->getAdditionalPain() + Rand::Next(10.0F, 30.0F));
    }
    eventData.reset();
}

} // namespace sadisticAIDirector
} // namespace ai
} // namespace zombie
