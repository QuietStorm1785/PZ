#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODSoundEmitter.h"
#include "fmod/fmod/FMOD_STUDIO_EVENT_CALLBACK.h"
#include "fmod/fmod/FMOD_STUDIO_EVENT_CALLBACK_TYPE.h"
#include "fmod/javafmod.h"
#include "org/joml/Vector2f.h"
#include "zombie/AmbientStreamManager/1.h"
#include "zombie/AmbientStreamManager/Ambient.h"
#include "zombie/AmbientStreamManager/AmbientLoop.h"
#include "zombie/AmbientStreamManager/WorldSoundEmitter.h"
#include "zombie/audio/parameters/ParameterCameraZoom.h"
#include "zombie/audio/parameters/ParameterClosestWallDistance.h"
#include "zombie/audio/parameters/ParameterFogIntensity.h"
#include "zombie/audio/parameters/ParameterHardOfHearing.h"
#include "zombie/audio/parameters/ParameterInside.h"
#include "zombie/audio/parameters/ParameterMoodlePanic.h"
#include "zombie/audio/parameters/ParameterPowerSupply.h"
#include "zombie/audio/parameters/ParameterRainIntensity.h"
#include "zombie/audio/parameters/ParameterRoomSize.h"
#include "zombie/audio/parameters/ParameterRoomType.h"
#include "zombie/audio/parameters/ParameterSeason.h"
#include "zombie/audio/parameters/ParameterSnowIntensity.h"
#include "zombie/audio/parameters/ParameterStorm.h"
#include "zombie/audio/parameters/ParameterTemperature.h"
#include "zombie/audio/parameters/ParameterTimeOfDay.h"
#include "zombie/audio/parameters/ParameterWaterSupply.h"
#include "zombie/audio/parameters/ParameterWeatherEvent.h"
#include "zombie/audio/parameters/ParameterWindIntensity.h"
#include "zombie/audio/parameters/ParameterZone.h"
#include "zombie/audio/parameters/ParameterZoneWaterSide.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/iso/Alarm.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaCell.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/objects/RainManager.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/GameClient.h"
#include <algorithm>

namespace zombie {


class AmbientStreamManager : public BaseAmbientStreamManager {
public:
    static int OneInAmbienceChance = 2500;
    static int MaxAmbientCount = 20;
    static float MaxRange = 1000.0F;
   private final ArrayList<Alarm> alarmList = std::make_unique<ArrayList<>>();
    static BaseAmbientStreamManager instance;
   public final ArrayList<Ambient> ambient = std::make_unique<ArrayList<>>();
   public final ArrayList<WorldSoundEmitter> worldEmitters = std::make_unique<ArrayList<>>();
   public final ArrayDeque<WorldSoundEmitter> freeEmitters = std::make_unique<ArrayDeque<>>();
   public final ArrayList<AmbientLoop> allAmbient = std::make_unique<ArrayList<>>();
   public final ArrayList<AmbientLoop> nightAmbient = std::make_unique<ArrayList<>>();
   public final ArrayList<AmbientLoop> dayAmbient = std::make_unique<ArrayList<>>();
   public final ArrayList<AmbientLoop> rainAmbient = std::make_unique<ArrayList<>>();
   public final ArrayList<AmbientLoop> indoorAmbient = std::make_unique<ArrayList<>>();
   public final ArrayList<AmbientLoop> outdoorAmbient = std::make_unique<ArrayList<>>();
   public final ArrayList<AmbientLoop> windAmbient = std::make_unique<ArrayList<>>();
    bool initialized = false;
    FMODSoundEmitter electricityShutOffEmitter = null;
    long electricityShutOffEvent = 0L;
    int electricityShutOffState = -1;
    auto parameterFogIntensity = std::make_shared<ParameterFogIntensity>();
    auto parameterRainIntensity = std::make_shared<ParameterRainIntensity>();
    auto parameterSeason = std::make_shared<ParameterSeason>();
    auto parameterSnowIntensity = std::make_shared<ParameterSnowIntensity>();
    auto parameterStorm = std::make_shared<ParameterStorm>();
    auto parameterTimeOfDay = std::make_shared<ParameterTimeOfDay>();
    auto parameterTemperature = std::make_shared<ParameterTemperature>();
    auto parameterWeatherEvent = std::make_shared<ParameterWeatherEvent>();
    auto parameterWindIntensity = std::make_shared<ParameterWindIntensity>();
    auto parameterZoneDeepForest = std::make_shared<ParameterZone>("ZoneDeepForest", "DeepForest");
    auto parameterZoneFarm = std::make_shared<ParameterZone>("ZoneFarm", "Farm");
    auto parameterZoneForest = std::make_shared<ParameterZone>("ZoneForest", "Forest");
    auto parameterZoneNav = std::make_shared<ParameterZone>("ZoneNav", "Nav");
    auto parameterZoneTown = std::make_shared<ParameterZone>("ZoneTown", "TownZone");
    auto parameterZoneTrailerPark = std::make_shared<ParameterZone>("ZoneTrailerPark", "TrailerPark");
    auto parameterZoneVegetation = std::make_shared<ParameterZone>("ZoneVegetation", "Vegitation");
    auto parameterZoneWaterSide = std::make_shared<ParameterZoneWaterSide>();
    auto parameterCameraZoom = std::make_shared<ParameterCameraZoom>();
    auto parameterClosestWallDistance = std::make_shared<ParameterClosestWallDistance>();
    auto parameterHardOfHearing = std::make_shared<ParameterHardOfHearing>();
    auto parameterInside = std::make_shared<ParameterInside>();
    auto parameterMoodlePanic = std::make_shared<ParameterMoodlePanic>();
    auto parameterPowerSupply = std::make_shared<ParameterPowerSupply>();
    auto parameterRoomSize = std::make_shared<ParameterRoomSize>();
    auto parameterRoomType = std::make_shared<ParameterRoomType>();
    auto parameterWaterSupply = std::make_shared<ParameterWaterSupply>();
    auto tempo = std::make_shared<Vector2>();
    auto electricityShutOffEventCallback = std::make_shared<1>(this);

    static BaseAmbientStreamManager getInstance() {
    return instance;
   }

    void update() {
      if (this.initialized) {
         if (!GameTime.isGamePaused()) {
            if (IsoPlayer.getInstance() != nullptr) {
               if (IsoPlayer.getInstance().getCurrentSquare() != nullptr) {
                  this.updatePowerSupply();
                  this.parameterFogIntensity.update();
                  this.parameterRainIntensity.update();
                  this.parameterSeason.update();
                  this.parameterSnowIntensity.update();
                  this.parameterStorm.update();
                  this.parameterTemperature.update();
                  this.parameterTimeOfDay.update();
                  this.parameterWeatherEvent.update();
                  this.parameterWindIntensity.update();
                  this.parameterZoneDeepForest.update();
                  this.parameterZoneFarm.update();
                  this.parameterZoneForest.update();
                  this.parameterZoneNav.update();
                  this.parameterZoneVegetation.update();
                  this.parameterZoneTown.update();
                  this.parameterZoneTrailerPark.update();
                  this.parameterZoneWaterSide.update();
                  this.parameterCameraZoom.update();
                  this.parameterClosestWallDistance.update();
                  this.parameterHardOfHearing.update();
                  this.parameterInside.update();
                  this.parameterMoodlePanic.update();
                  this.parameterPowerSupply.update();
                  this.parameterRoomSize.update();
                  this.parameterRoomType.update();
                  this.parameterWaterSupply.update();
    float var1 = GameTime.instance.getTimeOfDay();

                  for (int var2 = 0; var2 < this.worldEmitters.size(); var2++) {
    WorldSoundEmitter var3 = this.worldEmitters.get(var2);
                     if (var3.daytime != nullptr) {
    IsoGridSquare var4 = IsoWorld.instance.CurrentCell.getGridSquare(var3.x, var3.y, var3.z);
                        if (var4 == nullptr) {
                           var3.fmodEmitter.stopAll();
                           SoundManager.instance.unregisterEmitter(var3.fmodEmitter);
                           this.worldEmitters.remove(var3);
                           this.freeEmitters.add(var3);
                           var2--;
                        } else {
                           if (var1 > var3.dawn && var1 < var3.dusk) {
                              if (var3.fmodEmitter.isEmpty()) {
                                 var3.channel = var3.fmodEmitter.playAmbientLoopedImpl(var3.daytime);
                              }
                           } else if (!var3.fmodEmitter.isEmpty()) {
                              var3.fmodEmitter.stopSound(var3.channel);
                              var3.channel = 0L;
                           }

                           if (!var3.fmodEmitter.isEmpty() && (IsoWorld.instance.emitterUpdate || var3.fmodEmitter.hasSoundsToStart())) {
                              var3.fmodEmitter.tick();
                           }
                        }
                     } else if (IsoPlayer.getInstance() != nullptr && IsoPlayer.getInstance().Traits.Deaf.isSet()) {
                        var3.fmodEmitter.stopAll();
                        SoundManager.instance.unregisterEmitter(var3.fmodEmitter);
                        this.worldEmitters.remove(var3);
                        this.freeEmitters.add(var3);
                        var2--;
                     } else {
    IsoGridSquare var8 = IsoWorld.instance.CurrentCell.getGridSquare(var3.x, var3.y, var3.z);
                        if (var8 != nullptr && !var3.fmodEmitter.isEmpty()) {
                           var3.fmodEmitter.x = var3.x;
                           var3.fmodEmitter.y = var3.y;
                           var3.fmodEmitter.z = var3.z;
                           if (IsoWorld.instance.emitterUpdate || var3.fmodEmitter.hasSoundsToStart()) {
                              var3.fmodEmitter.tick();
                           }
                        } else {
                           var3.fmodEmitter.stopAll();
                           SoundManager.instance.unregisterEmitter(var3.fmodEmitter);
                           this.worldEmitters.remove(var3);
                           this.freeEmitters.add(var3);
                           var2--;
                        }
                     }
                  }

    float var6 = GameTime.instance.getNight();
    bool var7 = IsoPlayer.getInstance().getCurrentSquare().isInARoom();
    bool var9 = RainManager.isRaining();

                  for (int var5 = 0; var5 < this.allAmbient.size(); var5++) {
                     this.allAmbient.get(var5).targVol = 1.0F;
                  }

                  for (int var10 = 0; var10 < this.nightAmbient.size(); var10++) {
                     this.nightAmbient.get(var10).targVol *= var6;
                  }

                  for (int var11 = 0; var11 < this.dayAmbient.size(); var11++) {
                     this.dayAmbient.get(var11).targVol *= 1.0F - var6;
                  }

                  for (int var12 = 0; var12 < this.indoorAmbient.size(); var12++) {
                     this.indoorAmbient.get(var12).targVol *= var7 ? 0.8F : 0.0F;
                  }

                  for (int var13 = 0; var13 < this.outdoorAmbient.size(); var13++) {
                     this.outdoorAmbient.get(var13).targVol *= var7 ? 0.15F : 0.8F;
                  }

                  for (int var14 = 0; var14 < this.rainAmbient.size(); var14++) {
                     this.rainAmbient.get(var14).targVol *= var9 ? 1.0F : 0.0F;
                     if (this.rainAmbient.get(var14).channel != 0L) {
                        javafmod.FMOD_Studio_EventInstance_SetParameterByName(
                           this.rainAmbient.get(var14).channel, "RainIntensity", ClimateManager.getInstance().getPrecipitationIntensity()
                        );
                     }
                  }

                  for (int var15 = 0; var15 < this.allAmbient.size(); var15++) {
                     this.allAmbient.get(var15).update();
                  }

                  for (int var16 = 0; var16 < this.alarmList.size(); var16++) {
                     this.alarmList.get(var16).update();
                     if (this.alarmList.get(var16).finished) {
                        this.alarmList.remove(var16);
                        var16--;
                     }
                  }

                  this.doOneShotAmbients();
               }
            }
         }
      }
   }

    void doOneShotAmbients() {
      for (int var1 = 0; var1 < this.ambient.size(); var1++) {
    Ambient var2 = this.ambient.get(var1);
         if (var2.finished()) {
            DebugLog.log(DebugType.Sound, "ambient: removing ambient sound " + var2.name);
            this.ambient.remove(var1--);
         } else {
            var2.update();
         }
      }
   }

    void addRandomAmbient() {
      if (!Core.GameMode == "LastStand") && !Core.GameMode == "Tutorial")) {
    std::vector var1 = new ArrayList();

         for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
    IsoPlayer var3 = IsoPlayer.players[var2];
            if (var3 != nullptr && var3.isAlive()) {
               var1.add(var3);
            }
         }

         if (!var1.isEmpty()) {
    IsoPlayer var9 = static_cast<IsoPlayer>(var1).get(Rand.Next(var1.size()));
    std::string var10 = "";
            if (GameTime.instance.getHour() > 7 && GameTime.instance.getHour() < 21) {
               switch (Rand.Next(3)) {
                  case 0:
                     if (Rand.Next(10) < 2) {
                        var10 = "MetaDogBark";
                     }
                     break;
                  case 1:
                     if (Rand.Next(10) < 3) {
                        var10 = "MetaScream";
                     }
               }
            } else {
               switch (Rand.Next(5)) {
                  case 0:
                     if (Rand.Next(10) < 2) {
                        var10 = "MetaDogBark";
                     }
                     break;
                  case 1:
                     if (Rand.Next(13) < 3) {
                        var10 = "MetaScream";
                     }
                     break;
                  case 2:
                     var10 = "MetaOwl";
                     break;
                  case 3:
                     var10 = "MetaWolfHowl";
               }
            }

            if (!var10.isEmpty()) {
    float var4 = var9.x;
    float var5 = var9.y;
    double var6 = Rand.Next((float) -Math.PI, (float) Math.PI);
               this.tempo.x = (float)Math.cos(var6);
               this.tempo.y = (float)Math.sin(var6);
               this.tempo.setLength(1000.0F);
               var4 += this.tempo.x;
               var5 += this.tempo.y;
               if (!GameClient.bClient) {
                  System.out.println("playing ambient: " + var10 + " at dist: " + Math.abs(var4 - var9.x) + "," + Math.abs(var5 - var9.y));
    auto var8 = std::make_shared<Ambient>(var10, var4, var5, 50.0F, Rand.Next(0.2F, 0.5F));
                  this.ambient.add(var8);
               }
            }
         }
      }
   }

    void addBlend(const std::string& var1, float var2, bool var3, bool var4, bool var5, bool var6) {
    auto var7 = std::make_shared<AmbientLoop>(0.0F, var1, var2);
      this.allAmbient.add(var7);
      if (var3) {
         this.indoorAmbient.add(var7);
      } else {
         this.outdoorAmbient.add(var7);
      }

      if (var4) {
         this.rainAmbient.add(var7);
      }

      if (var5) {
         this.nightAmbient.add(var7);
      }

      if (var6) {
         this.dayAmbient.add(var7);
      }
   }

    void init() {
      if (!this.initialized) {
         this.initialized = true;
      }
   }

    void doGunEvent() {
    std::vector var1 = new ArrayList();

      for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
    IsoPlayer var3 = IsoPlayer.players[var2];
         if (var3 != nullptr && var3.isAlive()) {
            var1.add(var3);
         }
      }

      if (!var1.isEmpty()) {
    IsoPlayer var11 = static_cast<IsoPlayer>(var1).get(Rand.Next(var1.size()));
    std::string var12 = null;
         switch (Rand.Next(6)) {
            case 0:
               var12 = "MetaAssaultRifle1";
               break;
            case 1:
               var12 = "MetaPistol1";
               break;
            case 2:
               var12 = "MetaShotgun1";
               break;
            case 3:
               var12 = "MetaPistol2";
               break;
            case 4:
               var12 = "MetaPistol3";
               break;
            case 5:
               var12 = "MetaShotgun1";
         }

    float var4 = var11.x;
    float var5 = var11.y;
    short var6 = 600;
    double var7 = Rand.Next((float) -Math.PI, (float) Math.PI);
         this.tempo.x = (float)Math.cos(var7);
         this.tempo.y = (float)Math.sin(var7);
         this.tempo.setLength(var6 - 100);
         var4 += this.tempo.x;
         var5 += this.tempo.y;
         WorldSoundManager.instance.addSound(nullptr, (int)var4, (int)var5, 0, var6, var6);
    float var9 = 1.0F;
    auto var10 = std::make_shared<Ambient>(var12, var4, var5, 700.0F, var9);
         this.ambient.add(var10);
      }
   }

    void doAlarm(RoomDef var1) {
      if (var1 != nullptr && var1.building != nullptr && var1.building.bAlarmed) {
         var1.building.bAlarmed = false;
         var1.building.setAllExplored(true);
         this.alarmList.add(new Alarm(var1.x + var1.getW() / 2, var1.y + var1.getH() / 2));
      }
   }

    void stop() {
      for (AmbientLoop var2 : this.allAmbient) {
         var2.stop();
      }

      this.allAmbient.clear();
      this.ambient.clear();
      this.dayAmbient.clear();
      this.indoorAmbient.clear();
      this.nightAmbient.clear();
      this.outdoorAmbient.clear();
      this.rainAmbient.clear();
      this.windAmbient.clear();
      this.alarmList.clear();
      if (this.electricityShutOffEmitter != nullptr) {
         this.electricityShutOffEmitter.stopAll();
         this.electricityShutOffEvent = 0L;
      }

      this.electricityShutOffState = -1;
      this.initialized = false;
   }

    void addAmbient(const std::string& var1, int var2, int var3, int var4, float var5) {
      if (GameClient.bClient) {
    auto var6 = std::make_shared<Ambient>(var1, var2, var3, var4, var5, true);
         this.ambient.add(var6);
      }
   }

    void addAmbientEmitter(float var1, float var2, int var3, const std::string& var4) {
    WorldSoundEmitter var5 = this.freeEmitters.isEmpty() ? new WorldSoundEmitter() : this.freeEmitters.pop();
      var5.x = var1;
      var5.y = var2;
      var5.z = var3;
      var5.daytime = nullptr;
      if (var5.fmodEmitter == nullptr) {
         var5.fmodEmitter = std::make_unique<FMODSoundEmitter>();
      }

      var5.fmodEmitter.x = var1;
      var5.fmodEmitter.y = var2;
      var5.fmodEmitter.z = var3;
      var5.channel = var5.fmodEmitter.playAmbientLoopedImpl(var4);
      var5.fmodEmitter.randomStart();
      SoundManager.instance.registerEmitter(var5.fmodEmitter);
      this.worldEmitters.add(var5);
   }

    void addDaytimeAmbientEmitter(float var1, float var2, int var3, const std::string& var4) {
    WorldSoundEmitter var5 = this.freeEmitters.isEmpty() ? new WorldSoundEmitter() : this.freeEmitters.pop();
      var5.x = var1;
      var5.y = var2;
      var5.z = var3;
      if (var5.fmodEmitter == nullptr) {
         var5.fmodEmitter = std::make_unique<FMODSoundEmitter>();
      }

      var5.fmodEmitter.x = var1;
      var5.fmodEmitter.y = var2;
      var5.fmodEmitter.z = var3;
      var5.daytime = var4;
      var5.dawn = Rand.Next(7.0F, 8.0F);
      var5.dusk = Rand.Next(19.0F, 20.0F);
      SoundManager.instance.registerEmitter(var5.fmodEmitter);
      this.worldEmitters.add(var5);
   }

    void updatePowerSupply() {
    bool var1 = GameTime.getInstance().NightsSurvived < SandboxOptions.getInstance().getElecShutModifier();
      if (this.electricityShutOffState == -1) {
         IsoWorld.instance.setHydroPowerOn(var1);
      }

      if (this.electricityShutOffState == 0 && var1) {
         IsoWorld.instance.setHydroPowerOn(true);
         this.checkHaveElectricity();
      }

      if (this.electricityShutOffState == 1 && !var1) {
         if (this.electricityShutOffEmitter == nullptr) {
            this.electricityShutOffEmitter = std::make_unique<FMODSoundEmitter>();
         }

         if (!this.electricityShutOffEmitter.isPlaying(this.electricityShutOffEvent)) {
    auto var2 = std::make_shared<Vector2f>();
            this.getListenerPos(var2);
    BuildingDef var3 = this.getNearestBuilding(var2.x, var2.y, var2);
            if (var3 == nullptr) {
               this.electricityShutOffEmitter.setPos(-1000.0F, -1000.0F, 0.0F);
            } else {
               this.electricityShutOffEmitter.setPos(var2.x, var2.y, 0.0F);
            }

            this.electricityShutOffEvent = this.electricityShutOffEmitter.playSound("WorldEventElectricityShutdown");
            if (this.electricityShutOffEvent != 0L) {
               javafmod.FMOD_Studio_EventInstance_SetCallback(
                  this.electricityShutOffEvent,
                  this.electricityShutOffEventCallback,
                  FMOD_STUDIO_EVENT_CALLBACK_TYPE.FMOD_STUDIO_EVENT_CALLBACK_TIMELINE_MARKER.bit
               );
            }
         }
      }

      this.electricityShutOffState = var1 ? 1 : 0;
      if (this.electricityShutOffEmitter != nullptr) {
         this.electricityShutOffEmitter.tick();
      }
   }

    void checkHaveElectricity() {
      for (int var1 = 0; var1 < IsoPlayer.numPlayers; var1++) {
    IsoChunkMap var2 = IsoWorld.instance.CurrentCell.ChunkMap[var1];
         if (!var2.ignore) {
            for (int var3 = 0; var3 < 8; var3++) {
               for (int var4 = var2.getWorldYMinTiles(); var4 <= var2.getWorldYMaxTiles(); var4++) {
                  for (int var5 = var2.getWorldXMinTiles(); var5 <= var2.getWorldXMaxTiles(); var5++) {
    IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var5, var4, var3);
                     if (var6 != nullptr) {
                        for (int var7 = 0; var7 < var6.getObjects().size(); var7++) {
    IsoObject var8 = static_cast<IsoObject>(var6).getObjects().get(var7);
                           var8.checkHaveElectricity();
                        }
                     }
                  }
               }
            }
         }
      }
   }

    BuildingDef getNearestBuilding(float var1, float var2, Vector2f var3) {
    IsoMetaGrid var4 = IsoWorld.instance.getMetaGrid();
    int var5 = PZMath.fastfloor(var1 / 300.0F);
    int var6 = PZMath.fastfloor(var2 / 300.0F);
    BuildingDef var7 = null;
    float var8 = Float.MAX_VALUE;
      var3.set(0.0F);
    auto var9 = std::make_shared<Vector2f>();

      for (int var10 = var6 - 1; var10 <= var6 + 1; var10++) {
         for (int var11 = var5 - 1; var11 <= var5 + 1; var11++) {
    IsoMetaCell var12 = var4.getCellData(var11, var10);
            if (var12 != nullptr && var12.info != nullptr) {
               for (BuildingDef var14 : var12.info.Buildings) {
    float var15 = var14.getClosestPoint(var1, var2, var9);
                  if (var15 < var8) {
                     var8 = var15;
                     var7 = var14;
                     var3.set(var9);
                  }
               }
            }
         }
      }

    return var7;
   }

    void getListenerPos(Vector2f var1) {
    IsoPlayer var2 = null;
      var1.set(0.0F);

      for (int var3 = 0; var3 < IsoPlayer.numPlayers; var3++) {
    IsoPlayer var4 = IsoPlayer.players[var3];
         if (var4 != nullptr && (var2 == nullptr || var2.isDead() && var4.isAlive() || var2.Traits.Deaf.isSet() && !var4.Traits.Deaf.isSet())) {
            var2 = var4;
            var1.set(var4.getX(), var4.getY());
         }
      }
   }
}
} // namespace zombie
