#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/AmbientSoundManager/Ambient.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Rand.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/GameServer.h"

namespace zombie {


class AmbientSoundManager :  BaseAmbientStreamManager {
:
    ArrayList<Ambient> ambient = std::make_unique<ArrayList<>>();
    const Vector2 tempo = new Vector2();
    int electricityShutOffState = -1;
    long electricityShutOffTime = 0L;
    bool initialized = false;

    void update() {
      if (this.initialized) {
         this.updatePowerSupply();
         this.doOneShotAmbients();
      }
   }

    void addAmbient(std::string_view var1, int var2, int var3, int var4, float var5) {
   }

    void addAmbientEmitter(float var1, float var2, int var3, std::string_view var4) {
   }

    void addDaytimeAmbientEmitter(float var1, float var2, int var3, std::string_view var4) {
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

    void init() {
      if (!this.initialized) {
         this.initialized = true;
      }
   }

    void addBlend(std::string_view var1, float var2, bool var3, bool var4, bool var5, bool var6) {
   }

    void addRandomAmbient() {
      if (!GameServer.Players.isEmpty()) {
    IsoPlayer var1 = (IsoPlayer)GameServer.Players.get(Rand.Next(GameServer.Players.size()));
         if (var1 != nullptr) {
    std::string var2 = nullptr;
            if (GameTime.instance.getHour() > 7 && GameTime.instance.getHour() < 21) {
               switch (Rand.Next(3)) {
                  case 0:
                     if (Rand.Next(10) < 2) {
                        var2 = "MetaDogBark";
                     }
                     break;
                  case 1:
                     if (Rand.Next(10) < 3) {
                        var2 = "MetaScream";
                     }
               }
            } else {
               switch (Rand.Next(5)) {
                  case 0:
                     if (Rand.Next(10) < 2) {
                        var2 = "MetaDogBark";
                     }
                     break;
                  case 1:
                     if (Rand.Next(13) < 3) {
                        var2 = "MetaScream";
                     }
                     break;
                  case 2:
                     var2 = "MetaOwl";
                     break;
                  case 3:
                     var2 = "MetaWolfHowl";
               }
            }

            if (var2 != nullptr) {
    float var3 = var1.x;
    float var4 = var1.y;
    double var5 = Rand.Next((float) -Math.PI, (float) Math.PI);
               this.tempo.x = (float)Math.cos(var5);
               this.tempo.y = (float)Math.sin(var5);
               this.tempo.setLength(1000.0F);
               var3 += this.tempo.x;
               var4 += this.tempo.y;
    Ambient var7 = new Ambient(this, var2, var3, var4, 50.0F, Rand.Next(0.2F, 0.5F));
               this.ambient.add(var7);
               GameServer.sendAmbient(var2, (int)var3, (int)var4, 50, Rand.Next(0.2F, 0.5F));
            }
         }
      }
   }

    void doGunEvent() {
    std::vector var1 = GameServer.getPlayers();
      if (!var1.isEmpty()) {
    IsoPlayer var2 = (IsoPlayer)var1.get(Rand.Next(var1.size()));
    std::string var3 = nullptr;
    float var4 = var2.x;
    float var5 = var2.y;
    short var6 = 600;
    double var7 = Rand.Next((float) -Math.PI, (float) Math.PI);
         this.tempo.x = (float)Math.cos(var7);
         this.tempo.y = (float)Math.sin(var7);
         this.tempo.setLength(var6 - 100);
         var4 += this.tempo.x;
         var5 += this.tempo.y;
         WorldSoundManager.instance.addSound(nullptr, (int)var4 + Rand.Next(-10, 10), (int)var5 + Rand.Next(-10, 10), 0, 600, 600);
         switch (Rand.Next(6)) {
            case 0:
               var3 = "MetaAssaultRifle1";
               break;
            case 1:
               var3 = "MetaPistol1";
               break;
            case 2:
               var3 = "MetaShotgun1";
               break;
            case 3:
               var3 = "MetaPistol2";
               break;
            case 4:
               var3 = "MetaPistol3";
               break;
            case 5:
               var3 = "MetaShotgun1";
         }

    float var9 = 1.0F;
    Ambient var10 = new Ambient(this, var3, var4, var5, 700.0F, var9);
         this.ambient.add(var10);
         GameServer.sendAmbient(var3, (int)var4, (int)var5, (int)Math.ceil(var10.radius), var10.volume);
      }
   }

    void doAlarm(RoomDef var1) {
      if (var1 != nullptr && var1.building != nullptr && var1.building.bAlarmed) {
    float var2 = 1.0F;
    Ambient var3 = new Ambient(this, "burglar2", var1.x + var1.getW() / 2, var1.y + var1.getH() / 2, 700.0F, var2);
         var3.duration = 49;
         var3.worldSoundDelay = 3;
         var1.building.bAlarmed = false;
         var1.building.setAllExplored(true);
         this.ambient.add(var3);
         GameServer.sendAlarm(var1.x + var1.getW() / 2, var1.y + var1.getH() / 2);
      }
   }

    void stop() {
      this.ambient.clear();
      this.initialized = false;
   }

    void updatePowerSupply() {
    bool var1 = GameTime.getInstance().NightsSurvived < SandboxOptions.getInstance().getElecShutModifier();
      if (this.electricityShutOffState == -1) {
         IsoWorld.instance.setHydroPowerOn(var1);
      }

      if (this.electricityShutOffState == 0) {
         if (var1) {
            IsoWorld.instance.setHydroPowerOn(true);
            this.checkHaveElectricity();
            this.electricityShutOffTime = 0L;
         } else if (this.electricityShutOffTime != 0L && System.currentTimeMillis() >= this.electricityShutOffTime) {
            this.electricityShutOffTime = 0L;
            IsoWorld.instance.setHydroPowerOn(false);
            this.checkHaveElectricity();
         }
      }

      if (this.electricityShutOffState == 1 && !var1) {
         this.electricityShutOffTime = System.currentTimeMillis() + 2650L;
      }

      this.electricityShutOffState = var1 ? 1 : 0;
   }

    void checkHaveElectricity() {
   }
}
} // namespace zombie
