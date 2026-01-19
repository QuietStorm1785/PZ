package zombie;

import fmod.javafmod;
import fmod.fmod.FMODSoundEmitter;
import fmod.fmod.FMOD_STUDIO_EVENT_CALLBACK;
import fmod.fmod.FMOD_STUDIO_EVENT_CALLBACK_TYPE;
import java.util.ArrayDeque;
import java.util.ArrayList;
import org.joml.Vector2f;
import zombie.AmbientStreamManager.1;
import zombie.AmbientStreamManager.Ambient;
import zombie.AmbientStreamManager.AmbientLoop;
import zombie.AmbientStreamManager.WorldSoundEmitter;
import zombie.audio.parameters.ParameterCameraZoom;
import zombie.audio.parameters.ParameterClosestWallDistance;
import zombie.audio.parameters.ParameterFogIntensity;
import zombie.audio.parameters.ParameterHardOfHearing;
import zombie.audio.parameters.ParameterInside;
import zombie.audio.parameters.ParameterMoodlePanic;
import zombie.audio.parameters.ParameterPowerSupply;
import zombie.audio.parameters.ParameterRainIntensity;
import zombie.audio.parameters.ParameterRoomSize;
import zombie.audio.parameters.ParameterRoomType;
import zombie.audio.parameters.ParameterSeason;
import zombie.audio.parameters.ParameterSnowIntensity;
import zombie.audio.parameters.ParameterStorm;
import zombie.audio.parameters.ParameterTemperature;
import zombie.audio.parameters.ParameterTimeOfDay;
import zombie.audio.parameters.ParameterWaterSupply;
import zombie.audio.parameters.ParameterWeatherEvent;
import zombie.audio.parameters.ParameterWindIntensity;
import zombie.audio.parameters.ParameterZone;
import zombie.audio.parameters.ParameterZoneWaterSide;
import zombie.characters.IsoPlayer;
import zombie.core.Core;
import zombie.core.Rand;
import zombie.core.math.PZMath;
import zombie.debug.DebugLog;
import zombie.debug.DebugType;
import zombie.iso.Alarm;
import zombie.iso.BuildingDef;
import zombie.iso.IsoChunkMap;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoMetaCell;
import zombie.iso.IsoMetaGrid;
import zombie.iso.IsoObject;
import zombie.iso.IsoWorld;
import zombie.iso.RoomDef;
import zombie.iso.Vector2;
import zombie.iso.objects.RainManager;
import zombie.iso.weather.ClimateManager;
import zombie.network.GameClient;

public final class AmbientStreamManager extends BaseAmbientStreamManager {
   public static int OneInAmbienceChance = 2500;
   public static int MaxAmbientCount = 20;
   public static float MaxRange = 1000.0F;
   private final ArrayList<Alarm> alarmList = new ArrayList<>();
   public static BaseAmbientStreamManager instance;
   public final ArrayList<Ambient> ambient = new ArrayList<>();
   public final ArrayList<WorldSoundEmitter> worldEmitters = new ArrayList<>();
   public final ArrayDeque<WorldSoundEmitter> freeEmitters = new ArrayDeque<>();
   public final ArrayList<AmbientLoop> allAmbient = new ArrayList<>();
   public final ArrayList<AmbientLoop> nightAmbient = new ArrayList<>();
   public final ArrayList<AmbientLoop> dayAmbient = new ArrayList<>();
   public final ArrayList<AmbientLoop> rainAmbient = new ArrayList<>();
   public final ArrayList<AmbientLoop> indoorAmbient = new ArrayList<>();
   public final ArrayList<AmbientLoop> outdoorAmbient = new ArrayList<>();
   public final ArrayList<AmbientLoop> windAmbient = new ArrayList<>();
   public boolean initialized = false;
   private FMODSoundEmitter electricityShutOffEmitter = null;
   private long electricityShutOffEvent = 0L;
   private int electricityShutOffState = -1;
   private final ParameterFogIntensity parameterFogIntensity = new ParameterFogIntensity();
   private final ParameterRainIntensity parameterRainIntensity = new ParameterRainIntensity();
   private final ParameterSeason parameterSeason = new ParameterSeason();
   private final ParameterSnowIntensity parameterSnowIntensity = new ParameterSnowIntensity();
   private final ParameterStorm parameterStorm = new ParameterStorm();
   private final ParameterTimeOfDay parameterTimeOfDay = new ParameterTimeOfDay();
   private final ParameterTemperature parameterTemperature = new ParameterTemperature();
   private final ParameterWeatherEvent parameterWeatherEvent = new ParameterWeatherEvent();
   private final ParameterWindIntensity parameterWindIntensity = new ParameterWindIntensity();
   private final ParameterZone parameterZoneDeepForest = new ParameterZone("ZoneDeepForest", "DeepForest");
   private final ParameterZone parameterZoneFarm = new ParameterZone("ZoneFarm", "Farm");
   private final ParameterZone parameterZoneForest = new ParameterZone("ZoneForest", "Forest");
   private final ParameterZone parameterZoneNav = new ParameterZone("ZoneNav", "Nav");
   private final ParameterZone parameterZoneTown = new ParameterZone("ZoneTown", "TownZone");
   private final ParameterZone parameterZoneTrailerPark = new ParameterZone("ZoneTrailerPark", "TrailerPark");
   private final ParameterZone parameterZoneVegetation = new ParameterZone("ZoneVegetation", "Vegitation");
   private final ParameterZoneWaterSide parameterZoneWaterSide = new ParameterZoneWaterSide();
   private final ParameterCameraZoom parameterCameraZoom = new ParameterCameraZoom();
   private final ParameterClosestWallDistance parameterClosestWallDistance = new ParameterClosestWallDistance();
   private final ParameterHardOfHearing parameterHardOfHearing = new ParameterHardOfHearing();
   private final ParameterInside parameterInside = new ParameterInside();
   private final ParameterMoodlePanic parameterMoodlePanic = new ParameterMoodlePanic();
   private final ParameterPowerSupply parameterPowerSupply = new ParameterPowerSupply();
   private final ParameterRoomSize parameterRoomSize = new ParameterRoomSize();
   private final ParameterRoomType parameterRoomType = new ParameterRoomType();
   private final ParameterWaterSupply parameterWaterSupply = new ParameterWaterSupply();
   private final Vector2 tempo = new Vector2();
   private final FMOD_STUDIO_EVENT_CALLBACK electricityShutOffEventCallback = new 1(this);

   public static BaseAmbientStreamManager getInstance() {
      return instance;
   }

   public void update() {
      if (this.initialized) {
         if (!GameTime.isGamePaused()) {
            if (IsoPlayer.getInstance() != null) {
               if (IsoPlayer.getInstance().getCurrentSquare() != null) {
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
                     if (var3.daytime != null) {
                        IsoGridSquare var4 = IsoWorld.instance.CurrentCell.getGridSquare(var3.x, var3.y, var3.z);
                        if (var4 == null) {
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
                     } else if (IsoPlayer.getInstance() != null && IsoPlayer.getInstance().Traits.Deaf.isSet()) {
                        var3.fmodEmitter.stopAll();
                        SoundManager.instance.unregisterEmitter(var3.fmodEmitter);
                        this.worldEmitters.remove(var3);
                        this.freeEmitters.add(var3);
                        var2--;
                     } else {
                        IsoGridSquare var8 = IsoWorld.instance.CurrentCell.getGridSquare(var3.x, var3.y, var3.z);
                        if (var8 != null && !var3.fmodEmitter.isEmpty()) {
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
                  boolean var7 = IsoPlayer.getInstance().getCurrentSquare().isInARoom();
                  boolean var9 = RainManager.isRaining();

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

   public void doOneShotAmbients() {
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

   public void addRandomAmbient() {
      if (!Core.GameMode.equals("LastStand") && !Core.GameMode.equals("Tutorial")) {
         ArrayList var1 = new ArrayList();

         for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
            IsoPlayer var3 = IsoPlayer.players[var2];
            if (var3 != null && var3.isAlive()) {
               var1.add(var3);
            }
         }

         if (!var1.isEmpty()) {
            IsoPlayer var9 = (IsoPlayer)var1.get(Rand.Next(var1.size()));
            String var10 = "";
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
                  Ambient var8 = new Ambient(var10, var4, var5, 50.0F, Rand.Next(0.2F, 0.5F));
                  this.ambient.add(var8);
               }
            }
         }
      }
   }

   public void addBlend(String var1, float var2, boolean var3, boolean var4, boolean var5, boolean var6) {
      AmbientLoop var7 = new AmbientLoop(0.0F, var1, var2);
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

   public void init() {
      if (!this.initialized) {
         this.initialized = true;
      }
   }

   public void doGunEvent() {
      ArrayList var1 = new ArrayList();

      for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
         IsoPlayer var3 = IsoPlayer.players[var2];
         if (var3 != null && var3.isAlive()) {
            var1.add(var3);
         }
      }

      if (!var1.isEmpty()) {
         IsoPlayer var11 = (IsoPlayer)var1.get(Rand.Next(var1.size()));
         String var12 = null;
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
         WorldSoundManager.instance.addSound(null, (int)var4, (int)var5, 0, var6, var6);
         float var9 = 1.0F;
         Ambient var10 = new Ambient(var12, var4, var5, 700.0F, var9);
         this.ambient.add(var10);
      }
   }

   public void doAlarm(RoomDef var1) {
      if (var1 != null && var1.building != null && var1.building.bAlarmed) {
         var1.building.bAlarmed = false;
         var1.building.setAllExplored(true);
         this.alarmList.add(new Alarm(var1.x + var1.getW() / 2, var1.y + var1.getH() / 2));
      }
   }

   public void stop() {
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
      if (this.electricityShutOffEmitter != null) {
         this.electricityShutOffEmitter.stopAll();
         this.electricityShutOffEvent = 0L;
      }

      this.electricityShutOffState = -1;
      this.initialized = false;
   }

   public void addAmbient(String var1, int var2, int var3, int var4, float var5) {
      if (GameClient.bClient) {
         Ambient var6 = new Ambient(var1, var2, var3, var4, var5, true);
         this.ambient.add(var6);
      }
   }

   public void addAmbientEmitter(float var1, float var2, int var3, String var4) {
      WorldSoundEmitter var5 = this.freeEmitters.isEmpty() ? new WorldSoundEmitter() : this.freeEmitters.pop();
      var5.x = var1;
      var5.y = var2;
      var5.z = var3;
      var5.daytime = null;
      if (var5.fmodEmitter == null) {
         var5.fmodEmitter = new FMODSoundEmitter();
      }

      var5.fmodEmitter.x = var1;
      var5.fmodEmitter.y = var2;
      var5.fmodEmitter.z = var3;
      var5.channel = var5.fmodEmitter.playAmbientLoopedImpl(var4);
      var5.fmodEmitter.randomStart();
      SoundManager.instance.registerEmitter(var5.fmodEmitter);
      this.worldEmitters.add(var5);
   }

   public void addDaytimeAmbientEmitter(float var1, float var2, int var3, String var4) {
      WorldSoundEmitter var5 = this.freeEmitters.isEmpty() ? new WorldSoundEmitter() : this.freeEmitters.pop();
      var5.x = var1;
      var5.y = var2;
      var5.z = var3;
      if (var5.fmodEmitter == null) {
         var5.fmodEmitter = new FMODSoundEmitter();
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

   private void updatePowerSupply() {
      boolean var1 = GameTime.getInstance().NightsSurvived < SandboxOptions.getInstance().getElecShutModifier();
      if (this.electricityShutOffState == -1) {
         IsoWorld.instance.setHydroPowerOn(var1);
      }

      if (this.electricityShutOffState == 0 && var1) {
         IsoWorld.instance.setHydroPowerOn(true);
         this.checkHaveElectricity();
      }

      if (this.electricityShutOffState == 1 && !var1) {
         if (this.electricityShutOffEmitter == null) {
            this.electricityShutOffEmitter = new FMODSoundEmitter();
         }

         if (!this.electricityShutOffEmitter.isPlaying(this.electricityShutOffEvent)) {
            Vector2f var2 = new Vector2f();
            this.getListenerPos(var2);
            BuildingDef var3 = this.getNearestBuilding(var2.x, var2.y, var2);
            if (var3 == null) {
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
      if (this.electricityShutOffEmitter != null) {
         this.electricityShutOffEmitter.tick();
      }
   }

   private void checkHaveElectricity() {
      for (int var1 = 0; var1 < IsoPlayer.numPlayers; var1++) {
         IsoChunkMap var2 = IsoWorld.instance.CurrentCell.ChunkMap[var1];
         if (!var2.ignore) {
            for (int var3 = 0; var3 < 8; var3++) {
               for (int var4 = var2.getWorldYMinTiles(); var4 <= var2.getWorldYMaxTiles(); var4++) {
                  for (int var5 = var2.getWorldXMinTiles(); var5 <= var2.getWorldXMaxTiles(); var5++) {
                     IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var5, var4, var3);
                     if (var6 != null) {
                        for (int var7 = 0; var7 < var6.getObjects().size(); var7++) {
                           IsoObject var8 = (IsoObject)var6.getObjects().get(var7);
                           var8.checkHaveElectricity();
                        }
                     }
                  }
               }
            }
         }
      }
   }

   public BuildingDef getNearestBuilding(float var1, float var2, Vector2f var3) {
      IsoMetaGrid var4 = IsoWorld.instance.getMetaGrid();
      int var5 = PZMath.fastfloor(var1 / 300.0F);
      int var6 = PZMath.fastfloor(var2 / 300.0F);
      BuildingDef var7 = null;
      float var8 = Float.MAX_VALUE;
      var3.set(0.0F);
      Vector2f var9 = new Vector2f();

      for (int var10 = var6 - 1; var10 <= var6 + 1; var10++) {
         for (int var11 = var5 - 1; var11 <= var5 + 1; var11++) {
            IsoMetaCell var12 = var4.getCellData(var11, var10);
            if (var12 != null && var12.info != null) {
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

   private void getListenerPos(Vector2f var1) {
      IsoPlayer var2 = null;
      var1.set(0.0F);

      for (int var3 = 0; var3 < IsoPlayer.numPlayers; var3++) {
         IsoPlayer var4 = IsoPlayer.players[var3];
         if (var4 != null && (var2 == null || var2.isDead() && var4.isAlive() || var2.Traits.Deaf.isSet() && !var4.Traits.Deaf.isSet())) {
            var2 = var4;
            var1.set(var4.getX(), var4.getY());
         }
      }
   }
}
