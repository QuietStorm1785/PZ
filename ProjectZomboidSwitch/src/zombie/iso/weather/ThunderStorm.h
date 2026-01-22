#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "fmod/javafmod.h"
#include "zombie/GameSounds.h"
#include "zombie/GameTime.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/audio/GameSound.h"
#include "zombie/audio/GameSoundClip.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/RenderSettings/PlayerRenderSettings.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/weather/ClimateManager/ClimateNetAuth.h"
#include "zombie/iso/weather/ThunderStorm/LightningState.h"
#include "zombie/iso/weather/ThunderStorm/PlayerLightningInfo.h"
#include "zombie/iso/weather/ThunderStorm/ThunderCloud.h"
#include "zombie/iso/weather/ThunderStorm/ThunderEvent.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/ui/SpeedControls.h"
#include "zombie/ui/UIManager.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace weather {


class ThunderStorm {
public:
    static int MAP_MIN_X = -3000;
    static int MAP_MIN_Y = -3000;
    static int MAP_MAX_X = 25000;
    static int MAP_MAX_Y = 20000;
    bool hasActiveThunderClouds = false;
    float cloudMaxRadius = 20000.0F;
   private ThunderEvent[] events = new ThunderEvent[30];
   private ThunderCloud[] clouds = new ThunderCloud[3];
    ClimateManager climateManager;
   private std::vector<ThunderCloud> cloudCache;
    bool donoise = false;
    int strikeRadius = 4000;
   private const PlayerLightningInfo[] lightningInfos = new PlayerLightningInfo[4];
    ThunderEvent networkThunderEvent = std::make_shared<ThunderEvent>();
    ThunderCloud dummyCloud;

   public std::vector<ThunderCloud> getClouds() {
      if (this.cloudCache == nullptr) {
         this.cloudCache = new std::vector<>(this.clouds.length);

         for (int var1 = 0; var1 < this.clouds.length; var1++) {
            this.cloudCache.push_back(this.clouds[var1]);
         }
      }

      return this.cloudCache;
   }

    public ThunderStorm(ClimateManager var1) {
      this.climateManager = var1;

      for (int var2 = 0; var2 < this.events.length; var2++) {
         this.events[var2] = std::make_unique<ThunderEvent>();
      }

      for (int var3 = 0; var3 < this.clouds.length; var3++) {
         this.clouds[var3] = std::make_unique<ThunderCloud>();
      }

      for (int var4 = 0; var4 < 4; var4++) {
         this.lightningInfos[var4] = std::make_shared<PlayerLightningInfo>(this);
      }
   }

    ThunderEvent getFreeEvent() {
      for (int var1 = 0; var1 < this.events.length; var1++) {
         if (!this.events[var1].isRunning) {
            return this.events[var1];
         }
      }

    return nullptr;
   }

    ThunderCloud getFreeCloud() {
      for (int var1 = 0; var1 < this.clouds.length; var1++) {
         if (!this.clouds[var1].isRunning) {
            return this.clouds[var1];
         }
      }

    return nullptr;
   }

    ThunderCloud getCloud(int var1) {
    uint8_t var2 = 0;
      return var2 < this.clouds.length ? this.clouds[var2] : nullptr;
   }

    bool HasActiveThunderClouds() {
      return this.hasActiveThunderClouds;
   }

    void noise(const std::string& var1) {
      if (this.donoise && (Core.bDebug || GameServer.bServer && GameServer.bDebug)) {
         DebugLog.log("thunderstorm: " + var1);
      }
   }

    void stopAllClouds() {
      for (int var1 = 0; var1 < this.clouds.length; var1++) {
         this.stopCloud(var1);
      }
   }

    void stopCloud(int var1) {
    ThunderCloud var2 = this.getCloud(var1);
      if (var2 != nullptr) {
         var2.isRunning = false;
      }
   }

    static float addToAngle(float var0, float var1) {
      var0 += var1;
      if (var0 > 360.0F) {
         var0 -= 360.0F;
      } else if (var0 < 0.0F) {
         var0 += 360.0F;
      }

    return var0;
   }

    static int getMapDiagonal() {
    int var0 = MAP_MAX_X - MAP_MIN_X;
    int var1 = MAP_MAX_Y - MAP_MIN_Y;
    int var2 = (int)Math.sqrt(Math.pow(var0, 2.0) + Math.pow(var1, 2.0));
      return var2 / 2;
   }

    void startThunderCloud(float var1, float var2, float var3, float var4, float var5, double var6, bool var8) {
      this.startThunderCloud(var1, var2, var3, var4, var5, var6, var8);
   }

    ThunderCloud startThunderCloud(float var1, float var2, float var3, float var4, float var5, double var6, bool var8, float var9) {
      if (GameClient.bClient) {
    return nullptr;
      } else {
    ThunderCloud var10 = this.getFreeCloud();
         if (var10 != nullptr) {
            var2 = addToAngle(var2, Rand.Next(-10.0F, 10.0F));
            var10.startTime = GameTime.instance.getWorldAgeHours();
            var10.endTime = var10.startTime + var6;
            var10.duration = var6;
            var10.strength = ClimateManager.clamp01(var1);
            var10.angle = var2;
            var10.radius = var3;
            if (var10.radius > this.cloudMaxRadius) {
               var10.radius = this.cloudMaxRadius;
            }

            var10.eventFrequency = var4;
            var10.thunderRatio = ClimateManager.clamp01(var5);
            var10.percentageOffset = PZMath.clamp_01(var9);
    float var11 = addToAngle(var2, 180.0F);
    int var12 = MAP_MAX_X - MAP_MIN_X;
    int var13 = MAP_MAX_Y - MAP_MIN_Y;
    int var14 = Rand.Next(MAP_MIN_X + var12 / 5, MAP_MAX_X - var12 / 5);
    int var15 = Rand.Next(MAP_MIN_Y + var13 / 5, MAP_MAX_Y - var13 / 5);
            if (var8) {
               if (!GameServer.bServer) {
    IsoPlayer var16 = IsoPlayer.getInstance();
                  if (var16 != nullptr) {
                     var14 = (int)var16.getX();
                     var15 = (int)var16.getY();
                  }
               } else {
                  if (GameServer.Players.empty()) {
                     DebugLog.log("Thundercloud couldnt target player...");
    return nullptr;
                  }

    std::vector var19 = GameServer.getPlayers();

                  for (int var17 = var19.size() - 1; var17 >= 0; var17--) {
                     if (((IsoPlayer)var19.get(var17)).getCurrentSquare() == nullptr) {
                        var19.remove(var17);
                     }
                  }

                  if (!var19.empty()) {
    IsoPlayer var20 = (IsoPlayer)var19.get(Rand.Next(var19.size()));
                     var14 = var20.getCurrentSquare().getX();
                     var15 = var20.getCurrentSquare().getY();
                  }
               }
            }

            var10.setCenter(var14, var15, var2);
            var10.isRunning = true;
            var10.suspendTimer.init(3);
    return var10;
         } else {
    return nullptr;
         }
      }
   }

    void update(double var1) {
      if (!GameClient.bClient || GameServer.bServer) {
         this.hasActiveThunderClouds = false;

         for (int var3 = 0; var3 < this.clouds.length; var3++) {
    ThunderCloud var4 = this.clouds[var3];
            if (var4.isRunning) {
               if (var1 < var4.endTime) {
    float var5 = (float)((var1 - var4.startTime) / var4.duration);
                  if (var4.percentageOffset > 0.0F) {
                     var5 = var4.percentageOffset + (1.0F - var4.percentageOffset) * var5;
                  }

                  var4.currentX = (int)ClimateManager.lerp(var5, var4.startX, var4.endX);
                  var4.currentY = (int)ClimateManager.lerp(var5, var4.startY, var4.endY);
                  var4.suspendTimer.update();
                  this.hasActiveThunderClouds = true;
                  if (var4.suspendTimer.finished()) {
    float var6 = Rand.Next(3.5F - 3.0F * var4.strength, 24.0F - 20.0F * var4.strength);
                     var4.suspendTimer.init((int)(var6 * 60.0F));
    float var7 = Rand.Next(0.0F, 1.0F);
                     if (var7 < 0.6F) {
                        this.strikeRadius = (int)(var4.radius / 2.0F) / 3;
                     } else if (var7 < 0.9F) {
                        this.strikeRadius = (int)(var4.radius / 2.0F) / 4 * 3;
                     } else {
                        this.strikeRadius = (int)(var4.radius / 2.0F);
                     }

                     if (Rand.Next(0.0F, 1.0F) < var4.thunderRatio) {
                        this.noise("trigger thunder event");
                        this.triggerThunderEvent(
                           Rand.Next(var4.currentX - this.strikeRadius, var4.currentX + this.strikeRadius),
                           Rand.Next(var4.currentY - this.strikeRadius, var4.currentY + this.strikeRadius),
                           true,
                           true,
                           Rand.Next(0.0F, 1.0F) > 0.4F
                        );
                     } else {
                        this.triggerThunderEvent(
                           Rand.Next(var4.currentX - this.strikeRadius, var4.currentX + this.strikeRadius),
                           Rand.Next(var4.currentY - this.strikeRadius, var4.currentY + this.strikeRadius),
                           false,
                           false,
                           true
                        );
                        this.noise("trigger rumble event");
                     }
                  }
               } else {
                  var4.isRunning = false;
               }
            }
         }
      }

      if (GameClient.bClient || !GameServer.bServer) {
         for (int var15 = 0; var15 < 4; var15++) {
    PlayerLightningInfo var17 = this.lightningInfos[var15];
            if (var17.lightningState == LightningState.ApplyLightning) {
               var17.timer.update();
               if (!var17.timer.finished()) {
                  var17.lightningMod = ClimateManager.clamp01(var17.timer.ratio());
                  this.climateManager.dayLightStrength.finalValue = this.climateManager.dayLightStrength.finalValue
                     + (1.0F - this.climateManager.dayLightStrength.finalValue) * (1.0F - var17.lightningMod);
    IsoPlayer var19 = IsoPlayer.players[var15];
                  if (var19 != nullptr) {
                     var19.dirtyRecalcGridStackTime = 1.0F;
                  }
               } else {
                  this.noise("apply lightning done.");
                  var17.timer.init(2);
                  var17.lightningStrength = 0.0F;
                  var17.lightningState = LightningState.Idle;
               }
            }
         }

    bool var16 = SpeedControls.instance.getCurrentGameSpeed() > 1;
    bool var18 = false;
    bool var20 = false;

         for (int var21 = 0; var21 < this.events.length; var21++) {
    ThunderEvent var22 = this.events[var21];
            if (var22.isRunning) {
               var22.soundDelay.update();
               if (var22.soundDelay.finished()) {
                  var22.isRunning = false;
    bool var8 = true;
                  if (UIManager.getSpeedControls() != nullptr && UIManager.getSpeedControls().getCurrentGameSpeed() > 1) {
                     var8 = false;
                  }

                  if (var8 && !Core.SoundDisabled && FMODManager.instance.getNumListeners() > 0) {
                     if (var22.doStrike && (!var16 || !var18)) {
                        this.noise("thunder sound");
    GameSound var9 = GameSounds.getSound("Thunder");
    GameSoundClip var10 = var9 == nullptr ? nullptr : var9.getRandomClip();
                        if (var10 != nullptr && var10.eventDescription != nullptr) {
    long var11 = var10.eventDescription.address;
    long var13 = javafmod.FMOD_Studio_System_CreateEventInstance(var11);
                           javafmod.FMOD_Studio_EventInstance3D(var13, var22.eventX, var22.eventY, 100.0F);
                           javafmod.FMOD_Studio_EventInstance_SetVolume(var13, var10.getEffectiveVolume());
                           javafmod.FMOD_Studio_StartEvent(var13);
                           javafmod.FMOD_Studio_ReleaseEventInstance(var13);
                        }
                     }

                     if (var22.doRumble && (!var16 || !var20)) {
                        this.noise("rumble sound");
    GameSound var23 = GameSounds.getSound("RumbleThunder");
    GameSoundClip var24 = var23 == nullptr ? nullptr : var23.getRandomClip();
                        if (var24 != nullptr && var24.eventDescription != nullptr) {
    long var25 = var24.eventDescription.address;
    long var26 = javafmod.FMOD_Studio_System_CreateEventInstance(var25);
                           javafmod.FMOD_Studio_EventInstance3D(var26, var22.eventX, var22.eventY, 200.0F);
                           javafmod.FMOD_Studio_EventInstance_SetVolume(var26, var24.getEffectiveVolume());
                           javafmod.FMOD_Studio_StartEvent(var26);
                           javafmod.FMOD_Studio_ReleaseEventInstance(var26);
                        }
                     }
                  }
               } else {
                  var18 = var18 || var22.doStrike;
                  var20 = var20 || var22.doRumble;
               }
            }
         }
      }
   }

    void applyLightningForPlayer(PlayerRenderSettings var1, int var2, IsoPlayer var3) {
    PlayerLightningInfo var4 = this.lightningInfos[var2];
      if (var4.lightningState == LightningState.ApplyLightning) {
    ClimateColorInfo var5 = var1.CM_GlobalLight;
         var4.lightningColor.getExterior().r = var5.getExterior().r + var4.lightningStrength * (1.0F - var5.getExterior().r);
         var4.lightningColor.getExterior().g = var5.getExterior().g + var4.lightningStrength * (1.0F - var5.getExterior().g);
         var4.lightningColor.getExterior().b = var5.getExterior().b + var4.lightningStrength * (1.0F - var5.getExterior().b);
         var4.lightningColor.getInterior().r = var5.getInterior().r + var4.lightningStrength * (1.0F - var5.getInterior().r);
         var4.lightningColor.getInterior().g = var5.getInterior().g + var4.lightningStrength * (1.0F - var5.getInterior().g);
         var4.lightningColor.getInterior().b = var5.getInterior().b + var4.lightningStrength * (1.0F - var5.getInterior().b);
         var4.lightningColor.interp(var1.CM_GlobalLight, var4.lightningMod, var4.outColor);
         var1.CM_GlobalLight.getExterior().r = var4.outColor.getExterior().r;
         var1.CM_GlobalLight.getExterior().g = var4.outColor.getExterior().g;
         var1.CM_GlobalLight.getExterior().b = var4.outColor.getExterior().b;
         var1.CM_GlobalLight.getInterior().r = var4.outColor.getInterior().r;
         var1.CM_GlobalLight.getInterior().g = var4.outColor.getInterior().g;
         var1.CM_GlobalLight.getInterior().b = var4.outColor.getInterior().b;
         var1.CM_Ambient = ClimateManager.lerp(var4.lightningMod, 1.0F, var1.CM_Ambient);
         var1.CM_DayLightStrength = ClimateManager.lerp(var4.lightningMod, 1.0F, var1.CM_DayLightStrength);
         var1.CM_Desaturation = ClimateManager.lerp(var4.lightningMod, 0.0F, var1.CM_Desaturation);
         if (Core.getInstance().RenderShader != nullptr && Core.getInstance().getOffscreenBuffer() != nullptr) {
            var1.CM_GlobalLightIntensity = ClimateManager.lerp(var4.lightningMod, 1.0F, var1.CM_GlobalLightIntensity);
         } else {
            var1.CM_GlobalLightIntensity = ClimateManager.lerp(var4.lightningMod, 0.0F, var1.CM_GlobalLightIntensity);
         }
      }
   }

    bool isModifyingNight() {
    return false;
   }

    void triggerThunderEvent(int var1, int var2, bool var3, bool var4, bool var5) {
      if (GameServer.bServer) {
         this.networkThunderEvent.eventX = var1;
         this.networkThunderEvent.eventY = var2;
         this.networkThunderEvent.doStrike = var3;
         this.networkThunderEvent.doLightning = var4;
         this.networkThunderEvent.doRumble = var5;
         this.climateManager.transmitClimatePacket(ClimateNetAuth.ServerOnly, (byte)2, nullptr);
      } else if (!GameClient.bClient) {
         this.enqueueThunderEvent(var1, var2, var3, var4, var5);
      }
   }

    void writeNetThunderEvent(ByteBuffer var1) {
      var1.putInt(this.networkThunderEvent.eventX);
      var1.putInt(this.networkThunderEvent.eventY);
      var1.put((byte)(this.networkThunderEvent.doStrike ? 1 : 0));
      var1.put((byte)(this.networkThunderEvent.doLightning ? 1 : 0));
      var1.put((byte)(this.networkThunderEvent.doRumble ? 1 : 0));
   }

    void readNetThunderEvent(ByteBuffer var1) {
    int var2 = var1.getInt();
    int var3 = var1.getInt();
    bool var4 = var1.get() == 1;
    bool var5 = var1.get() == 1;
    bool var6 = var1.get() == 1;
      this.enqueueThunderEvent(var2, var3, var4, var5, var6);
   }

    void enqueueThunderEvent(int var1, int var2, bool var3, bool var4, bool var5) {
      LuaEventManager.triggerEvent("OnThunderEvent", var1, var2, var3, var4, var5);
      if (var3 || var5) {
    int var6 = 9999999;

         for (int var7 = 0; var7 < IsoPlayer.numPlayers; var7++) {
    IsoPlayer var8 = IsoPlayer.players[var7];
            if (var8 != nullptr) {
    int var9 = this.GetDistance((int)var8.getX(), (int)var8.getY(), var1, var2);
               if (var9 < var6) {
                  var6 = var9;
               }

               if (var4) {
                  this.lightningInfos[var7].distance = var9;
                  this.lightningInfos[var7].x = var1;
                  this.lightningInfos[var7].y = var2;
               }
            }
         }

         this.noise("dist to player = " + var6);
         if (var6 < 10000) {
    ThunderEvent var11 = this.getFreeEvent();
            if (var11 != nullptr) {
               var11.doRumble = var5;
               var11.doStrike = var3;
               var11.eventX = var1;
               var11.eventY = var2;
               var11.isRunning = true;
               var11.soundDelay.init((int)(var6 / 300.0F * 60.0F));
               if (var4) {
                  for (int var12 = 0; var12 < IsoPlayer.numPlayers; var12++) {
    IsoPlayer var13 = IsoPlayer.players[var12];
                     if (var13 != nullptr && this.lightningInfos[var12].distance < 7500.0F) {
    float var10 = 1.0F - this.lightningInfos[var12].distance / 7500.0F;
                        this.lightningInfos[var12].lightningState = LightningState.ApplyLightning;
                        if (var10 > this.lightningInfos[var12].lightningStrength) {
                           this.lightningInfos[var12].lightningStrength = var10;
                           this.lightningInfos[var12].timer.init(20 + (int)(80.0F * this.lightningInfos[var12].lightningStrength));
                        }
                     }
                  }
               }
            }
         }
      }
   }

    int GetDistance(int var1, int var2, int var3, int var4) {
      return (int)Math.sqrt(Math.pow(var1 - var3, 2.0) + Math.pow(var2 - var4, 2.0));
   }

    void save(DataOutputStream var1) {
      if (GameClient.bClient && !GameServer.bServer) {
         var1.writeByte(0);
      } else {
         var1.writeByte(this.clouds.length);

         for (int var2 = 0; var2 < this.clouds.length; var2++) {
    ThunderCloud var3 = this.clouds[var2];
            var1.writeBoolean(var3.isRunning);
            if (var3.isRunning) {
               var1.writeInt(var3.startX);
               var1.writeInt(var3.startY);
               var1.writeInt(var3.endX);
               var1.writeInt(var3.endY);
               var1.writeFloat(var3.radius);
               var1.writeFloat(var3.angle);
               var1.writeFloat(var3.strength);
               var1.writeFloat(var3.thunderRatio);
               var1.writeDouble(var3.startTime);
               var1.writeDouble(var3.endTime);
               var1.writeDouble(var3.duration);
               var1.writeFloat(var3.percentageOffset);
            }
         }
      }
   }

    void load(DataInputStream var1) {
    uint8_t var2 = var1.readByte();
      if (var2 != 0) {
         if (var2 > this.clouds.length && this.dummyCloud == nullptr) {
            this.dummyCloud = std::make_unique<ThunderCloud>();
         }

         for (int var4 = 0; var4 < var2; var4++) {
    bool var5 = var1.readBoolean();
    ThunderCloud var3;
            if (var4 >= this.clouds.length) {
               var3 = this.dummyCloud;
            } else {
               var3 = this.clouds[var4];
            }

            var3.isRunning = var5;
            if (var5) {
               var3.startX = var1.readInt();
               var3.startY = var1.readInt();
               var3.endX = var1.readInt();
               var3.endY = var1.readInt();
               var3.radius = var1.readFloat();
               var3.angle = var1.readFloat();
               var3.strength = var1.readFloat();
               var3.thunderRatio = var1.readFloat();
               var3.startTime = var1.readDouble();
               var3.endTime = var1.readDouble();
               var3.duration = var1.readDouble();
               var3.percentageOffset = var1.readFloat();
            }
         }
      }
   }
}
} // namespace weather
} // namespace iso
} // namespace zombie
