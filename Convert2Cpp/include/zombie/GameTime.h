#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/ai/sadisticAIDirector/SleepingEvent.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/Rand.h"
#include "zombie/core/Translator.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/erosion/ErosionMain.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SliceY.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/ui/SpeedControls.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/PZCalendar.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {


class GameTime {
public:
    static auto instance = std::make_shared<GameTime>();
    static const float MULTIPLIER = 0.8F;
    static long serverTimeShift = 0L;
    static bool serverTimeShiftIsSet = false;
    static bool isUTest = false;
    float TimeOfDay = 9.0F;
    int NightsSurvived = 0;
    PZCalendar Calender;
    float FPSMultiplier = 1.0F;
    float Moon = 0.0F;
    float ServerTimeOfDay;
    float ServerLastTimeOfDay;
    int ServerNewDays;
    float lightSourceUpdate = 0.0F;
    float multiplierBias = 1.0F;
    float LastLastTimeOfDay = 0.0F;
    int HelicopterTime1Start = 0;
    float PerObjectMultiplier = 1.0F;
    int HelicopterTime1End = 0;
    int HelicopterDay1 = 0;
    float Ambient = 0.9F;
    float AmbientMax = 1.0F;
    float AmbientMin = 0.24F;
    int Day = 22;
    int StartDay = 22;
    float MaxZombieCountStart = 750.0F;
    float MinZombieCountStart = 750.0F;
    float MaxZombieCount = 750.0F;
    float MinZombieCount = 750.0F;
    int Month = 7;
    int StartMonth = 7;
    float StartTimeOfDay = 9.0F;
    float ViewDistMax = 42.0F;
    float ViewDistMin = 19.0F;
    int Year = 2012;
    int StartYear = 2012;
    double HoursSurvived = 0.0;
    float MinutesPerDayStart = 30.0F;
    float MinutesPerDay = this.MinutesPerDayStart;
    float LastTimeOfDay;
    int TargetZombies = (int)this.MinZombieCountStart;
    bool RainingToday = true;
    bool bGunFireEventToday = false;
   private std::vector<float> GunFireTimes = std::make_shared<std::array<float, 5>>();
    int NumGunFireEvents = 1;
    long lastPing = 0L;
    long lastClockSync = 0L;
    KahluaTable table = null;
    int minutesMod = -1;
    bool thunderDay = true;
    bool randomAmbientToday = true;
    float Multiplier = 1.0F;
    int dusk = 3;
    int dawn = 12;
    float NightMin = 0.0F;
    float NightMax = 1.0F;
    long minutesStamp = 0L;
    long previousMinuteStamp = 0L;

    public GameTime() {
      serverTimeShift = 0L;
      serverTimeShiftIsSet = false;
   }

    static GameTime getInstance() {
    return instance;
   }

    static void setInstance(GameTime var0) {
      instance = var0;
   }

    static void syncServerTime(long var0, long var2, long var4) {
    long var6 = var4 - var0;
    long var8 = var2 - var4 + var6 / 2L;
    long var10 = serverTimeShift;
      if (!serverTimeShiftIsSet) {
         serverTimeShift = var8;
      } else {
         serverTimeShift = serverTimeShift + (var8 - serverTimeShift) / 100L;
      }

    long var12 = 10000000L;
      if (Math.abs(serverTimeShift - var10) > var12) {
         sendTimeSync();
      } else {
         serverTimeShiftIsSet = true;
      }
   }

    static long getServerTime() {
      if (isUTest) {
         return System.nanoTime() + serverTimeShift;
      } else if (GameServer.bServer) {
         return System.nanoTime();
      } else if (GameClient.bClient) {
         return !serverTimeShiftIsSet ? 0L : System.nanoTime() + serverTimeShift;
      } else {
    return 0L;
      }
   }

    static long getServerTimeMills() {
      return TimeUnit.NANOSECONDS.toMillis(getServerTime());
   }

    static bool getServerTimeShiftIsSet() {
    return serverTimeShiftIsSet;
   }

    static void setServerTimeShift(long var0) {
      isUTest = true;
      serverTimeShift = var0;
      serverTimeShiftIsSet = true;
   }

    static void sendTimeSync() {
    ByteBufferWriter var0 = GameClient.connection.startPacket();
      PacketType.TimeSync.doPacket(var0);
      var0.putLong(System.nanoTime());
      var0.putFloat(instance.Multiplier);
      PacketType.TimeSync.send(GameClient.connection);
   }

    static void receiveTimeSync(ByteBuffer var0, UdpConnection var1) {
      if (GameServer.bServer) {
    long var2 = var0.getLong();
    long var4 = System.nanoTime();
    float var6 = var0.getFloat();
         if (GameServer.bServer && !GameServer.bFastForward) {
            if (instance.Multiplier != var6) {
               var1.validator.failTimeMultiplier(var6);
            } else {
               var1.validator.successTimeMultiplier();
            }
         }

    ByteBufferWriter var7 = var1.startPacket();
         PacketType.TimeSync.doPacket(var7);
         var7.putLong(var2);
         var7.putLong(var4);
         PacketType.TimeSync.send(var1);
      }

      if (GameClient.bClient) {
    long var8 = var0.getLong();
    long var9 = var0.getLong();
    long var10 = System.nanoTime();
         syncServerTime(var8, var9, var10);
         DebugLog.printServerTime = true;
      }
   }

    float getRealworldSecondsSinceLastUpdate() {
      return 0.016666668F * this.FPSMultiplier;
   }

    float getMultipliedSecondsSinceLastUpdate() {
      return 0.016666668F * this.getUnmoddedMultiplier();
   }

    float getGameWorldSecondsSinceLastUpdate() {
    float var1 = 1440.0F / this.getMinutesPerDay();
      return this.getTimeDelta() * var1;
   }

    int daysInMonth(int var1, int var2) {
      if (this.Calender == nullptr) {
         this.updateCalendar(this.getYear(), this.getMonth(), this.getDay(), (int)this.getTimeOfDay(), this.getMinutes());
      }

      std::vector<int> var3 = std::make_shared<std::vector<int>>(){31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
      var3[1] += this.getCalender().isLeapYear(var1) ? 1 : 0;
      return var3[var2];
   }

    std::string getDeathString(IsoPlayer var1) {
      return Translator.getText("IGUI_Gametime_SurvivedFor", this.getTimeSurvived(var1));
   }

    int getDaysSurvived() {
    float var1 = 0.0F;

      for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
    IsoPlayer var3 = IsoPlayer.players[var2];
         if (var3 != nullptr) {
            var1 = Math.max(var1, (float)var3.getHoursSurvived());
         }
      }

    int var4 = (int)var1 / 24;
      return var4 % 30;
   }

    std::string getTimeSurvived(IsoPlayer var1) {
    void* var2 = "";
    float var3 = (float)var1.getHoursSurvived();
    int var4 = (int)var3 % 24;
    int var5 = (int)var3 / 24;
    int var6 = var5 / 30;
      var5 = var5 % 30;
    int var7 = var6 / 12;
      var6 = var6 % 12;
    std::string var8 = Translator.getText("IGUI_Gametime_day");
    std::string var9 = Translator.getText("IGUI_Gametime_year");
    std::string var10 = Translator.getText("IGUI_Gametime_hour");
    std::string var11 = Translator.getText("IGUI_Gametime_month");
      if (var7 != 0) {
         if (var7 > 1) {
            var9 = Translator.getText("IGUI_Gametime_years");
         }

         var2 = var2 + var7 + " " + var9;
      }

      if (var6 != 0) {
         if (var6 > 1) {
            var11 = Translator.getText("IGUI_Gametime_months");
         }

         if (var2.length() > 0) {
            var2 = var2 + ", ";
         }

         var2 = var2 + var6 + " " + var11;
      }

      if (var5 != 0) {
         if (var5 > 1) {
            var8 = Translator.getText("IGUI_Gametime_days");
         }

         if (var2.length() > 0) {
            var2 = var2 + ", ";
         }

         var2 = var2 + var5 + " " + var8;
      }

      if (var4 != 0) {
         if (var4 > 1) {
            var10 = Translator.getText("IGUI_Gametime_hours");
         }

         if (var2.length() > 0) {
            var2 = var2 + ", ";
         }

         var2 = var2 + var4 + " " + var10;
      }

      if (var2.trim().length() == 0) {
    int var12 = (int)(var3 * 60.0F);
    int var13 = (int)(var3 * 60.0F * 60.0F) - var12 * 60;
         var2 = var12 + " " + Translator.getText("IGUI_Gametime_minutes") + ", " + var13 + " " + Translator.getText("IGUI_Gametime_secondes");
      }

      return static_cast<String>(var2);
   }

    std::string getZombieKilledText(IsoPlayer var1) {
    int var2 = var1.getZombieKills();
      if (var2 == 0 || var2 > 1) {
         return Translator.getText("IGUI_Gametime_zombiesCount", var2);
      } else {
    return var2 = = 1 ? Translator.getText("IGUI_Gametime_zombieCount", var2) : null;
      }
   }

    std::string getGameModeText() {
    std::string var1 = Translator.getTextOrNull("IGUI_Gametime_" + Core.GameMode);
      if (var1 == nullptr) {
         var1 = Core.GameMode;
      }

    std::string var2 = Translator.getTextOrNull("IGUI_Gametime_GameMode", var1);
      if (var2 == nullptr) {
         var2 = "Game mode: " + var1;
      }

      if (Core.bDebug) {
         var2 = var2 + " (DEBUG)";
      }

    return var2;
   }

    void init() {
      this.setDay(this.getStartDay());
      this.setTimeOfDay(this.getStartTimeOfDay());
      this.setMonth(this.getStartMonth());
      this.setYear(this.getStartYear());
      if (SandboxOptions.instance.Helicopter.getValue() != 1) {
         this.HelicopterDay1 = Rand.Next(6, 10);
         this.HelicopterTime1Start = Rand.Next(9, 19);
         this.HelicopterTime1End = this.HelicopterTime1Start + Rand.Next(4) + 1;
      }

      this.setMinutesStamp();
   }

    float Lerp(float var1, float var2, float var3) {
      if (var3 < 0.0F) {
         var3 = 0.0F;
      }

      if (var3 >= 1.0F) {
         var3 = 1.0F;
      }

    float var4 = var2 - var1;
    float var5 = var4 * var3;
      return var1 + var5;
   }

    void RemoveZombiesIndiscriminate(int var1) {
      if (var1 != 0) {
         for (int var2 = 0; var2 < IsoWorld.instance.CurrentCell.getZombieList().size(); var2++) {
    IsoZombie var3 = static_cast<IsoZombie>(IsoWorld).instance.CurrentCell.getZombieList().get(0);
            IsoWorld.instance.CurrentCell.getZombieList().remove(var2);
            IsoWorld.instance.CurrentCell.getRemoveList().add(var3);
            var3.getCurrentSquare().getMovingObjects().remove(var3);
            var2--;
            if (--var1 == 0 || IsoWorld.instance.CurrentCell.getZombieList().isEmpty()) {
               return;
            }
         }
      }
   }

    float TimeLerp(float var1, float var2, float var3, float var4) {
    float var5 = getInstance().getTimeOfDay();
      if (var4 < var3) {
         var4 += 24.0F;
      }

    bool var6 = false;
      if (var5 > var4 && var5 > var3 || var5 < var4 && var5 < var3) {
         var3 += 24.0F;
         var6 = true;
         var3 = var4;
         var4 = var3;
         if (var5 < var3) {
            var5 += 24.0F;
         }
      }

    float var12 = var4 - var3;
    float var8 = var5 - var3;
    float var9 = 0.0F;
      if (var8 > var12) {
         var9 = 1.0F;
      }

      if (var8 < var12 && var8 > 0.0F) {
         var9 = var8 / var12;
      }

      if (var6) {
         var9 = 1.0F - var9;
      }

    float var10 = 0.0F;
      var9 = (var9 - 0.5F) * 2.0F;
      if (var9 < 0.0) {
         var10 = -1.0F;
      } else {
         var10 = 1.0F;
      }

      var9 = Math.abs(var9);
      var9 = 1.0F - var9;
      var9 = (float)Math.pow(var9, 8.0);
      var9 = 1.0F - var9;
      var9 *= var10;
      var9 = var9 * 0.5F + 0.5F;
      return this.Lerp(var1, var2, var9);
   }

    float getDeltaMinutesPerDay() {
      return this.MinutesPerDayStart / this.MinutesPerDay;
   }

    float getNightMin() {
      return 1.0F - this.NightMin;
   }

    void setNightMin(float var1) {
      this.NightMin = 1.0F - var1;
   }

    float getNightMax() {
      return 1.0F - this.NightMax;
   }

    void setNightMax(float var1) {
      this.NightMax = 1.0F - var1;
   }

    int getMinutes() {
      return (int)((this.getTimeOfDay() - (int)this.getTimeOfDay()) * 60.0F);
   }

    void setMoon(float var1) {
      this.Moon = var1;
   }

    void update(bool var1) {
    long var2 = System.currentTimeMillis();
      if (GameClient.bClient && (this.lastPing == 0L || var2 - this.lastPing > 10000L)) {
         sendTimeSync();
         this.lastPing = var2;
      }

    short var4 = 9000;
      if (SandboxOptions.instance.MetaEvent.getValue() == 1) {
         var4 = -1;
      }

      if (SandboxOptions.instance.MetaEvent.getValue() == 3) {
         var4 = 6000;
      }

      if (!GameClient.bClient && this.randomAmbientToday && var4 != -1 && Rand.Next(Rand.AdjustForFramerate(var4)) == 0 && !isGamePaused()) {
         AmbientStreamManager.instance.addRandomAmbient();
         this.randomAmbientToday = SandboxOptions.instance.MetaEvent.getValue() == 3 && Rand.Next(3) == 0;
      }

      if (GameServer.bServer && UIManager.getSpeedControls() != nullptr) {
         UIManager.getSpeedControls().SetCurrentGameSpeed(1);
      }

      if (GameServer.bServer || !GameClient.bClient) {
         if (this.bGunFireEventToday) {
            for (int var5 = 0; var5 < this.NumGunFireEvents; var5++) {
               if (this.TimeOfDay > this.GunFireTimes[var5] && this.LastLastTimeOfDay < this.GunFireTimes[var5]) {
                  AmbientStreamManager.instance.doGunEvent();
               }
            }
         }

         if (this.NightsSurvived == this.HelicopterDay1
            && this.TimeOfDay > this.HelicopterTime1Start
            && this.TimeOfDay < this.HelicopterTime1End
            && !IsoWorld.instance.helicopter.isActive()
            && Rand.Next((int)(800.0F * this.getInvMultiplier())) == 0) {
            this.HelicopterTime1Start = (int)(this.HelicopterTime1Start + 0.5F);
            IsoWorld.instance.helicopter.pickRandomTarget();
         }

         if (this.NightsSurvived > this.HelicopterDay1
            && (SandboxOptions.instance.Helicopter.getValue() == 3 || SandboxOptions.instance.Helicopter.getValue() == 4)) {
            if (SandboxOptions.instance.Helicopter.getValue() == 3) {
               this.HelicopterDay1 = this.NightsSurvived + Rand.Next(10, 16);
            }

            if (SandboxOptions.instance.Helicopter.getValue() == 4) {
               this.HelicopterDay1 = this.NightsSurvived + Rand.Next(6, 10);
            }

            this.HelicopterTime1Start = Rand.Next(9, 19);
            this.HelicopterTime1End = this.HelicopterTime1Start + Rand.Next(4) + 1;
         }
      }

    int var12 = this.getHour();
      this.updateCalendar(
         this.getYear(), this.getMonth(), this.getDay(), (int)this.getTimeOfDay(), (int)((this.getTimeOfDay() - (int)this.getTimeOfDay()) * 60.0F)
      );
    float var6 = this.getTimeOfDay();
      if (!isGamePaused()) {
    float var7 = 1.0F / this.getMinutesPerDay() / 60.0F * this.getMultiplier() / 2.0F;
         if (Core.bLastStand) {
            var7 = 1.0F / this.getMinutesPerDay() / 60.0F * this.getUnmoddedMultiplier() / 2.0F;
         }

         this.setTimeOfDay(this.getTimeOfDay() + var7);
         if (this.getHour() != var12) {
            LuaEventManager.triggerEvent("EveryHours");
         }

         if (!GameServer.bServer) {
            for (int var8 = 0; var8 < IsoPlayer.numPlayers; var8++) {
    IsoPlayer var9 = IsoPlayer.players[var8];
               if (var9 != nullptr && var9.isAlive()) {
                  var9.setHoursSurvived(var9.getHoursSurvived() + var7);
               }
            }
         }

         if (GameServer.bServer) {
    std::vector var14 = GameClient.instance.getPlayers();

            for (int var18 = 0; var18 < var14.size(); var18++) {
    IsoPlayer var10 = static_cast<IsoPlayer>(var14).get(var18);
               var10.setHoursSurvived(var10.getHoursSurvived() + var7);
            }
         }

         if (GameClient.bClient) {
    std::vector var15 = GameClient.instance.getPlayers();

            for (int var19 = 0; var19 < var15.size(); var19++) {
    IsoPlayer var22 = static_cast<IsoPlayer>(var15).get(var19);
               if (var22 != nullptr && !var22.isDead() && !var22.isLocalPlayer()) {
                  var22.setHoursSurvived(var22.getHoursSurvived() + var7);
               }
            }
         }

         for (int var16 = 0; var16 < IsoPlayer.numPlayers; var16++) {
    IsoPlayer var20 = IsoPlayer.players[var16];
            if (var20 != nullptr) {
               if (var20.isAsleep()) {
                  var20.setAsleepTime(var20.getAsleepTime() + var7);
                  SleepingEvent.instance.update(var20);
               } else {
                  var20.setAsleepTime(0.0F);
               }
            }
         }
      }

      if (!GameClient.bClient && var6 <= 7.0F && this.getTimeOfDay() > 7.0F) {
         this.setNightsSurvived(this.getNightsSurvived() + 1);
         this.doMetaEvents();
      }

      if (GameClient.bClient) {
         if (this.getTimeOfDay() >= 24.0F) {
            this.setTimeOfDay(this.getTimeOfDay() - 24.0F);
         }

         while (this.ServerNewDays > 0) {
            this.ServerNewDays--;
            this.setDay(this.getDay() + 1);
            if (this.getDay() >= this.daysInMonth(this.getYear(), this.getMonth())) {
               this.setDay(0);
               this.setMonth(this.getMonth() + 1);
               if (this.getMonth() >= 12) {
                  this.setMonth(0);
                  this.setYear(this.getYear() + 1);
               }
            }

            this.updateCalendar(this.getYear(), this.getMonth(), this.getDay(), (int)this.getTimeOfDay(), this.getMinutes());
            LuaEventManager.triggerEvent("EveryDays");
         }
      } else if (this.getTimeOfDay() >= 24.0F) {
         this.setTimeOfDay(this.getTimeOfDay() - 24.0F);
         this.setDay(this.getDay() + 1);
         if (this.getDay() >= this.daysInMonth(this.getYear(), this.getMonth())) {
            this.setDay(0);
            this.setMonth(this.getMonth() + 1);
            if (this.getMonth() >= 12) {
               this.setMonth(0);
               this.setYear(this.getYear() + 1);
            }
         }

         this.updateCalendar(this.getYear(), this.getMonth(), this.getDay(), (int)this.getTimeOfDay(), this.getMinutes());
         LuaEventManager.triggerEvent("EveryDays");
         if (GameServer.bServer) {
            GameServer.syncClock();
            this.lastClockSync = var2;
         }
      }

    float var13 = this.Moon * 20.0F;
      if (!ClimateManager.getInstance().getThunderStorm().isModifyingNight()) {
         this.setAmbient(this.TimeLerp(this.getAmbientMin(), this.getAmbientMax(), this.getDusk(), this.getDawn()));
      }

      if (Core.getInstance().RenderShader != nullptr && Core.getInstance().getOffscreenBuffer() != nullptr) {
         this.setNightTint(0.0F);
      }

      this.setMinutesStamp();
    int var17 = (int)((this.getTimeOfDay() - (int)this.getTimeOfDay()) * 60.0F);
      if (var17 / 10 != this.minutesMod) {
         std::vector<IsoPlayer> var21 = IsoPlayer.players;

         for (int var23 = 0; var23 < var21.length; var23++) {
    IsoPlayer var11 = var21[var23];
            if (var11 != nullptr) {
               var11.dirtyRecalcGridStackTime = 1.0F;
            }
         }

         ErosionMain.EveryTenMinutes();
         ClimateManager.getInstance().updateEveryTenMins();
         getInstance().updateRoomLight();
         LuaEventManager.triggerEvent("EveryTenMinutes");
         this.minutesMod = var17 / 10;
         ZomboidRadio.getInstance().UpdateScripts(this.getHour(), var17);
      }

      if (this.previousMinuteStamp != this.minutesStamp) {
         LuaEventManager.triggerEvent("EveryOneMinute");
         this.previousMinuteStamp = this.minutesStamp;
      }

      if (GameServer.bServer && (var2 - this.lastClockSync > 10000L || GameServer.bFastForward)) {
         GameServer.syncClock();
         this.lastClockSync = var2;
      }
   }

    void updateRoomLight() {
   }

    void setMinutesStamp() {
      this.minutesStamp = (long)this.getWorldAgeHours() * 60L + this.getMinutes();
   }

    long getMinutesStamp() {
      return this.minutesStamp;
   }

    bool getThunderStorm() {
      return ClimateManager.getInstance().getIsThunderStorming();
   }

    void doMetaEvents() {
    uint8_t var1 = 3;
      if (SandboxOptions.instance.MetaEvent.getValue() == 1) {
         var1 = -1;
      }

      if (SandboxOptions.instance.MetaEvent.getValue() == 3) {
         var1 = 2;
      }

      this.bGunFireEventToday = var1 != -1 && Rand.Next(var1) == 0;
      if (this.bGunFireEventToday) {
         this.NumGunFireEvents = 1;

         for (int var2 = 0; var2 < this.NumGunFireEvents; var2++) {
            this.GunFireTimes[var2] = Rand.Next(18000) / 1000.0F + 7.0F;
         }
      }

      this.randomAmbientToday = true;
   }

    float getAmbient() {
      return ClimateManager.getInstance().getAmbient();
   }

    void setAmbient(float var1) {
      this.Ambient = var1;
   }

    float getAmbientMax() {
      return this.AmbientMax;
   }

    void setAmbientMax(float var1) {
      var1 = Math.min(1.0F, var1);
      var1 = Math.max(0.0F, var1);
      this.AmbientMax = var1;
   }

    float getAmbientMin() {
      return this.AmbientMin;
   }

    void setAmbientMin(float var1) {
      var1 = Math.min(1.0F, var1);
      var1 = Math.max(0.0F, var1);
      this.AmbientMin = var1;
   }

    int getDay() {
      return this.Day;
   }

    int getDayPlusOne() {
      return this.Day + 1;
   }

    void setDay(int var1) {
      this.Day = var1;
   }

    int getStartDay() {
      return this.StartDay;
   }

    void setStartDay(int var1) {
      this.StartDay = var1;
   }

    float getMaxZombieCountStart() {
      return 0.0F;
   }

    void setMaxZombieCountStart(float var1) {
      this.MaxZombieCountStart = var1;
   }

    float getMinZombieCountStart() {
      return 0.0F;
   }

    void setMinZombieCountStart(float var1) {
      this.MinZombieCountStart = var1;
   }

    float getMaxZombieCount() {
      return this.MaxZombieCount;
   }

    void setMaxZombieCount(float var1) {
      this.MaxZombieCount = var1;
   }

    float getMinZombieCount() {
      return this.MinZombieCount;
   }

    void setMinZombieCount(float var1) {
      this.MinZombieCount = var1;
   }

    int getMonth() {
      return this.Month;
   }

    void setMonth(int var1) {
      this.Month = var1;
   }

    int getStartMonth() {
      return this.StartMonth;
   }

    void setStartMonth(int var1) {
      this.StartMonth = var1;
   }

    float getNightTint() {
      return ClimateManager.getInstance().getNightStrength();
   }

    void setNightTint(float var1) {
   }

    float getNight() {
      return ClimateManager.getInstance().getNightStrength();
   }

    void setNight(float var1) {
   }

    float getTimeOfDay() {
      return this.TimeOfDay;
   }

    void setTimeOfDay(float var1) {
      this.TimeOfDay = var1;
   }

    float getStartTimeOfDay() {
      return this.StartTimeOfDay;
   }

    void setStartTimeOfDay(float var1) {
      this.StartTimeOfDay = var1;
   }

    float getViewDist() {
      return ClimateManager.getInstance().getViewDistance();
   }

    float getViewDistMax() {
      return this.ViewDistMax;
   }

    void setViewDistMax(float var1) {
      this.ViewDistMax = var1;
   }

    float getViewDistMin() {
      return this.ViewDistMin;
   }

    void setViewDistMin(float var1) {
      this.ViewDistMin = var1;
   }

    int getYear() {
      return this.Year;
   }

    void setYear(int var1) {
      this.Year = var1;
   }

    int getStartYear() {
      return this.StartYear;
   }

    void setStartYear(int var1) {
      this.StartYear = var1;
   }

    int getNightsSurvived() {
      return this.NightsSurvived;
   }

    void setNightsSurvived(int var1) {
      this.NightsSurvived = var1;
   }

    double getWorldAgeHours() {
    float var1 = this.getNightsSurvived() * 24;
      if (this.getTimeOfDay() >= 7.0F) {
         var1 += this.getTimeOfDay() - 7.0F;
      } else {
         var1 += this.getTimeOfDay() + 17.0F;
      }

    return var1;
   }

    double getHoursSurvived() {
      DebugLog.log("GameTime.getHoursSurvived() has no meaning, use IsoPlayer.getHourSurvived() instead");
      return this.HoursSurvived;
   }

    void setHoursSurvived(double var1) {
      DebugLog.log("GameTime.getHoursSurvived() has no meaning, use IsoPlayer.getHourSurvived() instead");
      this.HoursSurvived = var1;
   }

    int getHour() {
    double var1 = Math.floor(this.getTimeOfDay() * 3600.0F);
      return (int)Math.floor(var1 / 3600.0);
   }

    PZCalendar getCalender() {
      this.updateCalendar(
         this.getYear(), this.getMonth(), this.getDay(), (int)this.getTimeOfDay(), (int)((this.getTimeOfDay() - (int)this.getTimeOfDay()) * 60.0F)
      );
      return this.Calender;
   }

    void setCalender(PZCalendar var1) {
      this.Calender = var1;
   }

    void updateCalendar(int var1, int var2, int var3, int var4, int var5) {
      if (this.Calender == nullptr) {
         this.Calender = new PZCalendar(std::make_unique<GregorianCalendar>());
      }

      this.Calender.set(var1, var2, var3, var4, var5);
   }

    float getMinutesPerDay() {
      return this.MinutesPerDay;
   }

    void setMinutesPerDay(float var1) {
      this.MinutesPerDay = var1;
   }

    float getLastTimeOfDay() {
      return this.LastTimeOfDay;
   }

    void setLastTimeOfDay(float var1) {
      this.LastTimeOfDay = var1;
   }

    void setTargetZombies(int var1) {
      this.TargetZombies = var1;
   }

    bool isRainingToday() {
      return this.RainingToday;
   }

    float getMultiplier() {
      if (!GameServer.bServer && !GameClient.bClient && IsoPlayer.getInstance() != nullptr && IsoPlayer.allPlayersAsleep()) {
         return 200.0F * (30.0F / PerformanceSettings.getLockFPS());
      } else {
    float var1 = 1.0F;
         if (GameServer.bServer && GameServer.bFastForward) {
            var1 = (float)ServerOptions.instance.FastForwardMultiplier.getValue() / this.getDeltaMinutesPerDay();
         } else if (GameClient.bClient && GameClient.bFastForward) {
            var1 = (float)ServerOptions.instance.FastForwardMultiplier.getValue() / this.getDeltaMinutesPerDay();
         }

         var1 *= this.Multiplier;
         var1 *= this.FPSMultiplier;
         var1 *= this.multiplierBias;
         var1 *= this.PerObjectMultiplier;
         if (DebugOptions.instance.GameTimeSpeedQuarter.getValue()) {
            var1 *= 0.25F;
         }

         if (DebugOptions.instance.GameTimeSpeedHalf.getValue()) {
            var1 *= 0.5F;
         }

         return var1 * 0.8F;
      }
   }

    float getTimeDelta() {
      return this.getMultiplier() / (0.8F * this.multiplierBias) / 60.0F;
   }

    static float getAnimSpeedFix() {
      return 0.8F;
   }

    void setMultiplier(float var1) {
      this.Multiplier = var1;
   }

    float getServerMultiplier() {
    float var1 = 10.0F / GameWindow.averageFPS / (PerformanceSettings.ManualFrameSkips + 1);
    float var2 = this.Multiplier * var1;
      var2 *= 0.5F;
      if (!GameServer.bServer && !GameClient.bClient && IsoPlayer.getInstance() != nullptr && IsoPlayer.allPlayersAsleep()) {
         return 200.0F * (30.0F / PerformanceSettings.getLockFPS());
      } else {
         var2 *= 1.6F;
         return var2 * this.multiplierBias;
      }
   }

    float getUnmoddedMultiplier() {
      return !GameServer.bServer && !GameClient.bClient && IsoPlayer.getInstance() != nullptr && IsoPlayer.allPlayersAsleep()
         ? 200.0F * (30.0F / PerformanceSettings.getLockFPS())
         : this.Multiplier * this.FPSMultiplier * this.PerObjectMultiplier;
   }

    float getInvMultiplier() {
      return 1.0F / this.getMultiplier();
   }

    float getTrueMultiplier() {
      return this.Multiplier * this.PerObjectMultiplier;
   }

    void save() {
    auto var1 = std::make_shared<File>(ZomboidFileSystem.instance.getFileNameInCurrentSave("map_t.bin"));
    void* var2 = null;

      try {
         var2 = new FileOutputStream(var1);
      } catch (FileNotFoundException var7) {
         var7.printStackTrace();
         return;
      }

    auto var3 = std::make_shared<DataOutputStream>(new BufferedOutputStream(static_cast<OutputStream>(var2)));

      try {
         instance.save(var3);
      } catch (IOException var6) {
         var6.printStackTrace();
      }

      try {
         var3.flush();
         var3.close();
      } catch (IOException var5) {
         var5.printStackTrace();
      }
   }

    void save(DataOutputStream var1) {
      var1.writeByte(71);
      var1.writeByte(77);
      var1.writeByte(84);
      var1.writeByte(77);
      var1.writeInt(195);
      var1.writeFloat(this.Multiplier);
      var1.writeInt(this.NightsSurvived);
      var1.writeInt(this.TargetZombies);
      var1.writeFloat(this.LastTimeOfDay);
      var1.writeFloat(this.TimeOfDay);
      var1.writeInt(this.Day);
      var1.writeInt(this.Month);
      var1.writeInt(this.Year);
      var1.writeFloat(0.0F);
      var1.writeFloat(0.0F);
      var1.writeInt(0);
      if (this.table != nullptr) {
         var1.writeByte(1);
         this.table.save(var1);
      } else {
         var1.writeByte(0);
      }

      GameWindow.WriteString(var1, Core.getInstance().getPoisonousBerry());
      GameWindow.WriteString(var1, Core.getInstance().getPoisonousMushroom());
      var1.writeInt(this.HelicopterDay1);
      var1.writeInt(this.HelicopterTime1Start);
      var1.writeInt(this.HelicopterTime1End);
      ClimateManager.getInstance().save(var1);
   }

    void save(ByteBuffer var1) {
      var1.putFloat(this.Multiplier);
      var1.putInt(this.NightsSurvived);
      var1.putInt(this.TargetZombies);
      var1.putFloat(this.LastTimeOfDay);
      var1.putFloat(this.TimeOfDay);
      var1.putInt(this.Day);
      var1.putInt(this.Month);
      var1.putInt(this.Year);
      var1.putFloat(0.0F);
      var1.putFloat(0.0F);
      var1.putInt(0);
      if (this.table != nullptr) {
         var1.put((byte)1);
         this.table.save(var1);
      } else {
         var1.put((byte)0);
      }
   }

    void load(DataInputStream var1) {
    int var2 = IsoWorld.SavedWorldVersion;
      if (var2 == -1) {
         var2 = 195;
      }

      var1.mark(0);
    uint8_t var3 = var1.readByte();
    uint8_t var4 = var1.readByte();
    uint8_t var5 = var1.readByte();
    uint8_t var6 = var1.readByte();
      if (var3 == 71 && var4 == 77 && var5 == 84 && var6 == 77) {
         var2 = var1.readInt();
      } else {
         var1.reset();
      }

      this.Multiplier = var1.readFloat();
      this.NightsSurvived = var1.readInt();
      this.TargetZombies = var1.readInt();
      this.LastTimeOfDay = var1.readFloat();
      this.TimeOfDay = var1.readFloat();
      this.Day = var1.readInt();
      this.Month = var1.readInt();
      this.Year = var1.readInt();
      var1.readFloat();
      var1.readFloat();
    int var7 = var1.readInt();
      if (var1.readByte() == 1) {
         if (this.table == nullptr) {
            this.table = LuaManager.platform.newTable();
         }

         this.table.load(var1, var2);
      }

      if (var2 >= 74) {
         Core.getInstance().setPoisonousBerry(GameWindow.ReadString(var1));
         Core.getInstance().setPoisonousMushroom(GameWindow.ReadString(var1));
      }

      if (var2 >= 90) {
         this.HelicopterDay1 = var1.readInt();
         this.HelicopterTime1Start = var1.readInt();
         this.HelicopterTime1End = var1.readInt();
      }

      if (var2 >= 135) {
         ClimateManager.getInstance().load(var1, var2);
      }

      this.setMinutesStamp();
   }

    void load(ByteBuffer var1) {
    short var2 = 195;
      this.Multiplier = var1.getFloat();
      this.NightsSurvived = var1.getInt();
      this.TargetZombies = var1.getInt();
      this.LastTimeOfDay = var1.getFloat();
      this.TimeOfDay = var1.getFloat();
      this.Day = var1.getInt();
      this.Month = var1.getInt();
      this.Year = var1.getInt();
      var1.getFloat();
      var1.getFloat();
    int var3 = var1.getInt();
      if (var1.get() == 1) {
         if (this.table == nullptr) {
            this.table = LuaManager.platform.newTable();
         }

         this.table.load(var1, var2);
      }

      this.setMinutesStamp();
   }

    void load() {
    File var1 = ZomboidFileSystem.instance.getFileInCurrentSave("map_t.bin");

      try (
    auto var2 = std::make_shared<FileInputStream>(var1);
    auto var3 = std::make_shared<BufferedInputStream>(var2);
      ) {
         synchronized (SliceY.SliceBufferLock) {
            SliceY.SliceBuffer.clear();
    int var5 = var3.read(SliceY.SliceBuffer.array());
            SliceY.SliceBuffer.limit(var5);
    auto var6 = std::make_shared<DataInputStream>(new ByteArrayInputStream(SliceY.SliceBuffer.array(), 0, var5));
            this.load(var6);
         }
      } catch (FileNotFoundException var13) {
      } catch (Exception var14) {
         ExceptionLogger.logException(var14);
      }
   }

    int getDawn() {
      return this.dawn;
   }

    void setDawn(int var1) {
      this.dawn = var1;
   }

    int getDusk() {
      return this.dusk;
   }

    void setDusk(int var1) {
      this.dusk = var1;
   }

    KahluaTable getModData() {
      if (this.table == nullptr) {
         this.table = LuaManager.platform.newTable();
      }

      return this.table;
   }

    bool isThunderDay() {
      return this.thunderDay;
   }

    void setThunderDay(bool var1) {
      this.thunderDay = var1;
   }

    void saveToPacket(ByteBuffer var1) {
    KahluaTable var2 = getInstance().getModData();
    void* var3 = var2.rawget("camping");
    void* var4 = var2.rawget("farming");
    void* var5 = var2.rawget("trapping");
      var2.rawset("camping", nullptr);
      var2.rawset("farming", nullptr);
      var2.rawset("trapping", nullptr);
      this.save(var1);
      var2.rawset("camping", var3);
      var2.rawset("farming", var4);
      var2.rawset("trapping", var5);
   }

    int getHelicopterDay1() {
      return this.HelicopterDay1;
   }

    int getHelicopterDay() {
      return this.HelicopterDay1;
   }

    void setHelicopterDay(int var1) {
      this.HelicopterDay1 = PZMath.max(var1, 0);
   }

    int getHelicopterStartHour() {
      return this.HelicopterTime1Start;
   }

    void setHelicopterStartHour(int var1) {
      this.HelicopterTime1Start = PZMath.clamp(var1, 0, 24);
   }

    int getHelicopterEndHour() {
      return this.HelicopterTime1End;
   }

    void setHelicopterEndHour(int var1) {
      this.HelicopterTime1End = PZMath.clamp(var1, 0, 24);
   }

    static bool isGamePaused() {
      if (GameServer.bServer) {
         return GameServer.Players.isEmpty() && ServerOptions.instance.PauseEmpty.getValue();
      } else if (GameClient.bClient) {
         return GameClient.IsClientPaused();
      } else {
    SpeedControls var0 = UIManager.getSpeedControls();
         return var0 != nullptr && var0.getCurrentGameSpeed() == 0;
      }
   }
}
} // namespace zombie
