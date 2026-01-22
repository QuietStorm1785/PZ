#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SoundManager.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/ZombieSpawnRecorder.h"
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/core/Rand.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoBarricade.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoLightSwitch.h"
#include "zombie/iso/objects/IsoRadio.h"
#include "zombie/iso/objects/IsoStove.h"
#include "zombie/iso/objects/IsoTelevision.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace ai {
namespace sadisticAIDirector {


class SleepingEvent {
public:
    static const SleepingEvent instance = std::make_shared<SleepingEvent>();
    static bool zombiesInvasion = false;

    void setPlayerFallAsleep(IsoPlayer var1, int var2) {
    SleepingEventData var3 = var1.getOrCreateSleepingEventData();
      var3.reset();
      if (!IsoWorld.getZombiesEnabled()) {
         if (ClimateManager.getInstance().isRaining() && this.isExposedToPrecipitation(var1)) {
            var3.bRaining = true;
            var3.bWasRainingAtStart = true;
            var3.rainTimeStartHours = GameTime.getInstance().getWorldAgeHours();
         }

         var3.sleepingTime = var2;
         var1.setTimeOfSleep(GameTime.instance.getTimeOfDay());
         this.doDelayToSleep(var1);
         this.checkNightmare(var1, var2);
         if (var3.nightmareWakeUp <= -1) {
            if (SandboxOptions.instance.SleepingEvent.getValue() != 1 && zombiesInvasion) {
               if (var1.getCurrentSquare() == nullptr || var1.getCurrentSquare().getZone() == nullptr || !var1.getCurrentSquare().getZone().haveConstruction) {
    bool var4 = false;
                  if ((GameTime.instance.getHour() >= 0 && GameTime.instance.getHour() < 5 || GameTime.instance.getHour() > 18) && var2 >= 4) {
                     var4 = true;
                  }

    uint8_t var5 = 20;
                  if (SandboxOptions.instance.SleepingEvent.getValue() == 3) {
                     var5 = 45;
                  }

                  if (Rand.Next(100) <= var5 && var1.getCell().getZombieList().size() >= 1 && var2 >= 4) {
    int var6 = 0;
                     if (var1.getCurrentBuilding() != nullptr) {
    IsoGridSquare var7 = nullptr;
    void* var8 = nullptr;

                        for (int var9 = 0; var9 < 3; var9++) {
                           for (int var10 = var1.getCurrentBuilding().getDef().getX() - 2; var10 < var1.getCurrentBuilding().getDef().getX2() + 2; var10++) {
                              for (int var11 = var1.getCurrentBuilding().getDef().getY() - 2; var11 < var1.getCurrentBuilding().getDef().getY2() + 2; var11++) {
                                 var7 = IsoWorld.instance.getCell().getGridSquare(var10, var11, var9);
                                 if (var7 != nullptr) {
    bool var12 = var7.haveElectricity() || IsoWorld.instance.isHydroPowerOn();
                                    if (var12) {
                                       for (int var13 = 0; var13 < var7.getObjects().size(); var13++) {
    IsoObject var14 = (IsoObject)var7.getObjects().get(var13);
                                          if (var14.getContainer() != nullptr
                                             && (var14.getContainer().getType() == "fridge") || var14.getContainer().getType() == "freezer"))) {
                                             var6 += 3;
                                          }

                                          if (dynamic_cast<IsoStove*>(var14) != nullptr && ((IsoStove)var14).Activated()) {
                                             var6 += 5;
                                          }

                                          if (dynamic_cast<IsoTelevision*>(var14) != nullptr && ((IsoTelevision)var14).getDeviceData().getIsTurnedOn()) {
                                             var6 += 30;
                                          }

                                          if (dynamic_cast<IsoRadio*>(var14) != nullptr && ((IsoRadio)var14).getDeviceData().getIsTurnedOn()) {
                                             var6 += 30;
                                          }
                                       }
                                    }

                                    var8 = var7.getWindow();
                                    if (var8 != nullptr) {
                                       var6 += this.checkWindowStatus((IsoWindow)var8);
                                    }

    IsoDoor var17 = var7.getIsoDoor();
                                    if (var17 != nullptr && var17.isExteriorDoor(nullptr) && var17.IsOpen()) {
                                       var6 += 25;
                                       var3.openDoor = var17;
                                    }
                                 }
                              }
                           }
                        }

                        if (SandboxOptions.instance.SleepingEvent.getValue() == 3) {
                           var6 = (int)(var6 * 1.5);
                        }

                        if (var6 > 70) {
                           var6 = 70;
                        }

                        if (!var4) {
                           var6 /= 2;
                        }

                        if (Rand.Next(100) <= var6) {
                           var3.forceWakeUpTime = Rand.Next(var2 - 4, var2 - 1);
                           var3.zombiesIntruders = true;
                        }
                     }
                  }
               }
            }
         }
      }
   }

    void doDelayToSleep(IsoPlayer var1) {
    float var2 = 0.3F;
    float var3 = 2.0F;
      if (var1.Traits.Insomniac.isSet()) {
         var2 = 1.0F;
      }

      if (var1.getMoodles().getMoodleLevel(MoodleType.Pain) > 0) {
         var2 += 1.0F + var1.getMoodles().getMoodleLevel(MoodleType.Pain) * 0.2F;
      }

      if (var1.getMoodles().getMoodleLevel(MoodleType.Stress) > 0) {
         var2 *= 1.2F;
      }

      if ("badBed" == var1.getBedType())) {
         var2 *= 1.3F;
      } else if ("goodBed" == var1.getBedType())) {
         var2 *= 0.8F;
      } else if ("floor" == var1.getBedType())) {
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

    float var4 = Rand.Next(0.0F, var2);
      var1.setDelayToSleep(GameTime.instance.getTimeOfDay() + var4);
   }

    void checkNightmare(IsoPlayer var1, int var2) {
      if (!GameClient.bClient) {
    SleepingEventData var3 = var1.getOrCreateSleepingEventData();
         if (var2 >= 3) {
    int var4 = 5 + var1.getMoodles().getMoodleLevel(MoodleType.Stress) * 10;
            if (Rand.Next(100) < var4) {
               var3.nightmareWakeUp = Rand.Next(3, var2 - 2);
            }
         }
      }
   }

    int checkWindowStatus(IsoWindow var1) {
    IsoGridSquare var2 = var1.getSquare();
      if (var1.getSquare().getRoom() == nullptr) {
         if (!var1.north) {
            var2 = var1.getSquare().getCell().getGridSquare(var1.getSquare().getX() - 1, var1.getSquare().getY(), var1.getSquare().getZ());
         } else {
            var2 = var1.getSquare().getCell().getGridSquare(var1.getSquare().getX(), var1.getSquare().getY() - 1, var1.getSquare().getZ());
         }
      }

    uint8_t var3 = 0;
    bool var4 = false;

      for (int var5 = 0; var5 < var2.getRoom().lightSwitches.size(); var5++) {
         if (((IsoLightSwitch)var2.getRoom().lightSwitches.get(var5)).isActivated()) {
            var4 = true;
            break;
         }
      }

      if (var4) {
         var3 = 20;
         if (var1.HasCurtains() != nullptr && !var1.HasCurtains().open) {
            var3 -= 17;
         }

    IsoBarricade var9 = var1.getBarricadeOnOppositeSquare();
         if (var9 == nullptr) {
            var9 = var1.getBarricadeOnSameSquare();
         }

         if (var9 != nullptr && (var9.getNumPlanks() > 4 || var9.isMetal())) {
            var3 -= 20;
         }

         if (var3 < 0) {
            var3 = 0;
         }

         if (var2.getZ() > 0) {
            var3 /= 2;
         }

    return var3;
      } else {
         var3 = 5;
         if (var1.HasCurtains() != nullptr && !var1.HasCurtains().open) {
            var3 -= 5;
         }

    IsoBarricade var8 = var1.getBarricadeOnOppositeSquare();
         if (var8 == nullptr) {
            var8 = var1.getBarricadeOnSameSquare();
         }

         if (var8 != nullptr && (var8.getNumPlanks() > 3 || var8.isMetal())) {
            var3 -= 5;
         }

         if (var3 < 0) {
            var3 = 0;
         }

         if (var2.getZ() > 0) {
            var3 /= 2;
         }

    return var3;
      }
   }

    void update(IsoPlayer var1) {
      if (var1 != nullptr) {
    SleepingEventData var2 = var1.getOrCreateSleepingEventData();
         if (var2.nightmareWakeUp == (int)var1.getAsleepTime()) {
            var1.getStats().Panic += 70.0F;
            var1.getStats().stress += 0.5F;
            WorldSoundManager.instance.addSound(var1, (int)var1.getX(), (int)var1.getY(), (int)var1.getZ(), 6, 1);
            SoundManager.instance.setMusicWakeState(var1, "WakeNightmare");
            this.wakeUp(var1);
         }

         if (var2.forceWakeUpTime == (int)var1.getAsleepTime() && var2.zombiesIntruders) {
            this.spawnZombieIntruders(var1);
            WorldSoundManager.instance.addSound(var1, (int)var1.getX(), (int)var1.getY(), (int)var1.getZ(), 6, 1);
            SoundManager.instance.setMusicWakeState(var1, "WakeZombies");
            this.wakeUp(var1);
         }

         this.updateRain(var1);
         this.updateSnow(var1);
         this.updateTemperature(var1);
         this.updateWetness(var1);
      }
   }

    void updateRain(IsoPlayer var1) {
    SleepingEventData var2 = var1.getOrCreateSleepingEventData();
      if (!ClimateManager.getInstance().isRaining()) {
         var2.bRaining = false;
         var2.bWasRainingAtStart = false;
         var2.rainTimeStartHours = -1.0;
      } else if (this.isExposedToPrecipitation(var1)) {
    double var3 = GameTime.getInstance().getWorldAgeHours();
         if (!var2.bWasRainingAtStart) {
            if (!var2.bRaining) {
               var2.rainTimeStartHours = var3;
            }

            if (var2.getHoursSinceRainStarted() >= 0.16666666666666666) {
            }
         }

         var2.bRaining = true;
      }
   }

    void updateSnow(IsoPlayer var1) {
      if (ClimateManager.getInstance().isSnowing()) {
         if (this.isExposedToPrecipitation(var1)) {
            ;
         }
      }
   }

    void updateTemperature(IsoPlayer var1) {
   }

    void updateWetness(IsoPlayer var1) {
   }

    bool isExposedToPrecipitation(IsoGameCharacter var1) {
      if (var1.getCurrentSquare() == nullptr) {
    return false;
      } else if (var1.getCurrentSquare().isInARoom() || var1.getCurrentSquare().haveRoof) {
    return false;
      } else if (var1.getBed() != nullptr && "Tent" == var1.getBed().getName())) {
    return false;
      } else {
    BaseVehicle var2 = var1.getVehicle();
    return var2 = = nullptr || !var2.hasRoof(var2.getSeat(var1));
      }
   }

    void spawnZombieIntruders(IsoPlayer var1) {
    SleepingEventData var2 = var1.getOrCreateSleepingEventData();
    IsoGridSquare var3 = nullptr;
      if (var2.openDoor != nullptr) {
         var3 = var2.openDoor.getSquare();
      } else {
         var2.weakestWindow = this.getWeakestWindow(var1);
         if (var2.weakestWindow != nullptr && var2.weakestWindow.getZ() == 0.0F) {
            if (!var2.weakestWindow.north) {
               if (var2.weakestWindow.getSquare().getRoom() == nullptr) {
                  var3 = var2.weakestWindow.getSquare();
               } else {
                  var3 = var2.weakestWindow
                     .getSquare()
                     .getCell()
                     .getGridSquare(var2.weakestWindow.getSquare().getX() - 1, var2.weakestWindow.getSquare().getY(), var2.weakestWindow.getSquare().getZ());
               }
            } else if (var2.weakestWindow.getSquare().getRoom() == nullptr) {
               var3 = var2.weakestWindow.getSquare();
            } else {
               var3 = var2.weakestWindow
                  .getSquare()
                  .getCell()
                  .getGridSquare(var2.weakestWindow.getSquare().getX(), var2.weakestWindow.getSquare().getY() + 1, var2.weakestWindow.getSquare().getZ());
            }

    IsoBarricade var4 = var2.weakestWindow.getBarricadeOnOppositeSquare();
            if (var4 == nullptr) {
               var4 = var2.weakestWindow.getBarricadeOnSameSquare();
            }

            if (var4 != nullptr) {
               var4.Damage(Rand.Next(500, 900));
            } else {
               var2.weakestWindow.Damage(200.0F);
               var2.weakestWindow.smashWindow();
               if (var2.weakestWindow.HasCurtains() != nullptr) {
                  var2.weakestWindow.removeSheet(nullptr);
               }

               if (var3 != nullptr) {
                  var3.addBrokenGlass();
               }
            }
         }
      }

      var1.getStats().setPanic(var1.getStats().getPanic() + Rand.Next(30, 60));
      if (var3 != nullptr) {
         if (IsoWorld.getZombiesEnabled()) {
    int var7 = Rand.Next(3) + 1;

            for (int var5 = 0; var5 < var7; var5++) {
               VirtualZombieManager.instance.choices.clear();
               VirtualZombieManager.instance.choices.push_back(var3);
    IsoZombie var6 = VirtualZombieManager.instance.createRealZombieAlways(IsoDirections.fromIndex(Rand.Next(8)).index(), false);
               if (var6 != nullptr) {
                  var6.setTarget(var1);
                  var6.pathToCharacter(var1);
                  var6.spotted(var1, true);
                  ZombieSpawnRecorder.instance.record(var6, this.getClass().getSimpleName());
               }
            }
         }
      }
   }

    IsoWindow getWeakestWindow(IsoPlayer var1) {
    IsoGridSquare var2 = nullptr;
    void* var3 = nullptr;
    IsoWindow var4 = nullptr;
    int var5 = 0;

      for (int var6 = var1.getCurrentBuilding().getDef().getX() - 2; var6 < var1.getCurrentBuilding().getDef().getX2() + 2; var6++) {
         for (int var7 = var1.getCurrentBuilding().getDef().getY() - 2; var7 < var1.getCurrentBuilding().getDef().getY2() + 2; var7++) {
            var2 = IsoWorld.instance.getCell().getGridSquare(var6, var7, 0);
            if (var2 != nullptr) {
               var3 = var2.getWindow();
               if (var3 != nullptr) {
    int var8 = this.checkWindowStatus((IsoWindow)var3);
                  if (var8 > var5) {
                     var5 = var8;
                     var4 = (IsoWindow)var3;
                  }
               }
            }
         }
      }

    return var4;
   }

    void wakeUp(IsoGameCharacter var1) {
      if (var1 != nullptr) {
         this.wakeUp(var1, false);
      }
   }

    void wakeUp(IsoGameCharacter var1, bool var2) {
    SleepingEventData var3 = var1.getOrCreateSleepingEventData();
      if (GameClient.bClient && !var2) {
         GameClient.instance.wakeUpPlayer((IsoPlayer)var1);
      }

    bool var4 = false;
    IsoPlayer var5 = (IsoPlayer)Type.tryCastTo(var1, IsoPlayer.class);
      if (var5 != nullptr && var5.isLocalPlayer()) {
         UIManager.setFadeBeforeUI(var5.getPlayerNum(), true);
         UIManager.FadeIn(var5.getPlayerNum(), 2.0);
         if (!GameClient.bClient && IsoPlayer.allPlayersAsleep()) {
            UIManager.getSpeedControls().SetCurrentGameSpeed(1);
            var4 = true;
         }

         var1.setLastHourSleeped((int)var5.getHoursSurvived());
      }

      var1.setForceWakeUpTime(-1.0F);
      var1.setAsleep(false);
      if (var4) {
         try {
            GameWindow.save(true);
         } catch (Throwable var8) {
            ExceptionLogger.logException(var8);
         }
      }

    BodyPart var6 = var1.getBodyDamage().getBodyPart(BodyPartType.Neck);
    float var7 = var3.sleepingTime / 8.0F;
      if ("goodBed" == var1.getBedType())) {
         var1.getStats().setFatigue(var1.getStats().getFatigue() - Rand.Next(0.05F, 0.12F) * var7);
         if (var1.getStats().getFatigue() < 0.0F) {
            var1.getStats().setFatigue(0.0F);
         }
      } else if ("badBed" == var1.getBedType())) {
         var1.getStats().setFatigue(var1.getStats().getFatigue() + Rand.Next(0.1F, 0.2F) * var7);
         if (Rand.Next(5) == 0) {
            var6.AddDamage(Rand.Next(5.0F, 15.0F));
            var6.setAdditionalPain(var6.getAdditionalPain() + Rand.Next(30.0F, 50.0F));
         }
      } else if ("floor" == var1.getBedType())) {
         var1.getStats().setFatigue(var1.getStats().getFatigue() + Rand.Next(0.15F, 0.25F) * var7);
         if (Rand.Next(5) == 0) {
            var6.AddDamage(Rand.Next(10.0F, 20.0F));
            var6.setAdditionalPain(var6.getAdditionalPain() + Rand.Next(30.0F, 50.0F));
         }
      } else if (Rand.Next(10) == 0) {
         var6.AddDamage(Rand.Next(3.0F, 12.0F));
         var6.setAdditionalPain(var6.getAdditionalPain() + Rand.Next(10.0F, 30.0F));
      }

      var3.reset();
   }
}
} // namespace sadisticAIDirector
} // namespace ai
} // namespace zombie
