package zombie;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.GregorianCalendar;
import java.util.concurrent.TimeUnit;
import se.krka.kahlua.vm.KahluaTable;
import zombie.Lua.LuaEventManager;
import zombie.Lua.LuaManager;
import zombie.ai.sadisticAIDirector.SleepingEvent;
import zombie.characters.IsoPlayer;
import zombie.characters.IsoZombie;
import zombie.core.Core;
import zombie.core.PerformanceSettings;
import zombie.core.Rand;
import zombie.core.Translator;
import zombie.core.logger.ExceptionLogger;
import zombie.core.math.PZMath;
import zombie.core.network.ByteBufferWriter;
import zombie.core.raknet.UdpConnection;
import zombie.debug.DebugLog;
import zombie.debug.DebugOptions;
import zombie.erosion.ErosionMain;
import zombie.iso.IsoWorld;
import zombie.iso.SliceY;
import zombie.iso.weather.ClimateManager;
import zombie.network.GameClient;
import zombie.network.GameServer;
import zombie.network.ServerOptions;
import zombie.network.PacketTypes.PacketType;
import zombie.radio.ZomboidRadio;
import zombie.ui.SpeedControls;
import zombie.ui.UIManager;
import zombie.util.PZCalendar;

public final class GameTime {
   public static GameTime instance = new GameTime();
   public static final float MULTIPLIER = 0.8F;
   private static long serverTimeShift = 0L;
   private static boolean serverTimeShiftIsSet = false;
   private static boolean isUTest = false;
   public float TimeOfDay = 9.0F;
   public int NightsSurvived = 0;
   public PZCalendar Calender;
   public float FPSMultiplier = 1.0F;
   public float Moon = 0.0F;
   public float ServerTimeOfDay;
   public float ServerLastTimeOfDay;
   public int ServerNewDays;
   public float lightSourceUpdate = 0.0F;
   public float multiplierBias = 1.0F;
   public float LastLastTimeOfDay = 0.0F;
   private int HelicopterTime1Start = 0;
   public float PerObjectMultiplier = 1.0F;
   private int HelicopterTime1End = 0;
   private int HelicopterDay1 = 0;
   private float Ambient = 0.9F;
   private float AmbientMax = 1.0F;
   private float AmbientMin = 0.24F;
   private int Day = 22;
   private int StartDay = 22;
   private float MaxZombieCountStart = 750.0F;
   private float MinZombieCountStart = 750.0F;
   private float MaxZombieCount = 750.0F;
   private float MinZombieCount = 750.0F;
   private int Month = 7;
   private int StartMonth = 7;
   private float StartTimeOfDay = 9.0F;
   private float ViewDistMax = 42.0F;
   private float ViewDistMin = 19.0F;
   private int Year = 2012;
   private int StartYear = 2012;
   private double HoursSurvived = 0.0;
   private float MinutesPerDayStart = 30.0F;
   private float MinutesPerDay = this.MinutesPerDayStart;
   private float LastTimeOfDay;
   private int TargetZombies = (int)this.MinZombieCountStart;
   private boolean RainingToday = true;
   private boolean bGunFireEventToday = false;
   private float[] GunFireTimes = new float[5];
   private int NumGunFireEvents = 1;
   private long lastPing = 0L;
   private long lastClockSync = 0L;
   private KahluaTable table = null;
   private int minutesMod = -1;
   private boolean thunderDay = true;
   private boolean randomAmbientToday = true;
   private float Multiplier = 1.0F;
   private int dusk = 3;
   private int dawn = 12;
   private float NightMin = 0.0F;
   private float NightMax = 1.0F;
   private long minutesStamp = 0L;
   private long previousMinuteStamp = 0L;

   public GameTime() {
      serverTimeShift = 0L;
      serverTimeShiftIsSet = false;
   }

   public static GameTime getInstance() {
      return instance;
   }

   public static void setInstance(GameTime var0) {
      instance = var0;
   }

   public static void syncServerTime(long var0, long var2, long var4) {
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

   public static long getServerTime() {
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

   public static long getServerTimeMills() {
      return TimeUnit.NANOSECONDS.toMillis(getServerTime());
   }

   public static boolean getServerTimeShiftIsSet() {
      return serverTimeShiftIsSet;
   }

   public static void setServerTimeShift(long var0) {
      isUTest = true;
      serverTimeShift = var0;
      serverTimeShiftIsSet = true;
   }

   private static void sendTimeSync() {
      ByteBufferWriter var0 = GameClient.connection.startPacket();
      PacketType.TimeSync.doPacket(var0);
      var0.putLong(System.nanoTime());
      var0.putFloat(instance.Multiplier);
      PacketType.TimeSync.send(GameClient.connection);
   }

   public static void receiveTimeSync(ByteBuffer var0, UdpConnection var1) {
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

   public float getRealworldSecondsSinceLastUpdate() {
      return 0.016666668F * this.FPSMultiplier;
   }

   public float getMultipliedSecondsSinceLastUpdate() {
      return 0.016666668F * this.getUnmoddedMultiplier();
   }

   public float getGameWorldSecondsSinceLastUpdate() {
      float var1 = 1440.0F / this.getMinutesPerDay();
      return this.getTimeDelta() * var1;
   }

   public int daysInMonth(int var1, int var2) {
      if (this.Calender == null) {
         this.updateCalendar(this.getYear(), this.getMonth(), this.getDay(), (int)this.getTimeOfDay(), this.getMinutes());
      }

      int[] var3 = new int[]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
      var3[1] += this.getCalender().isLeapYear(var1) ? 1 : 0;
      return var3[var2];
   }

   public String getDeathString(IsoPlayer var1) {
      return Translator.getText("IGUI_Gametime_SurvivedFor", this.getTimeSurvived(var1));
   }

   public int getDaysSurvived() {
      float var1 = 0.0F;

      for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
         IsoPlayer var3 = IsoPlayer.players[var2];
         if (var3 != null) {
            var1 = Math.max(var1, (float)var3.getHoursSurvived());
         }
      }

      int var4 = (int)var1 / 24;
      return var4 % 30;
   }

   public String getTimeSurvived(IsoPlayer var1) {
      Object var2 = "";
      float var3 = (float)var1.getHoursSurvived();
      Integer var4 = (int)var3 % 24;
      Integer var5 = (int)var3 / 24;
      Integer var6 = var5 / 30;
      var5 = var5 % 30;
      Integer var7 = var6 / 12;
      var6 = var6 % 12;
      String var8 = Translator.getText("IGUI_Gametime_day");
      String var9 = Translator.getText("IGUI_Gametime_year");
      String var10 = Translator.getText("IGUI_Gametime_hour");
      String var11 = Translator.getText("IGUI_Gametime_month");
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

      return (String)var2;
   }

   public String getZombieKilledText(IsoPlayer var1) {
      int var2 = var1.getZombieKills();
      if (var2 == 0 || var2 > 1) {
         return Translator.getText("IGUI_Gametime_zombiesCount", var2);
      } else {
         return var2 == 1 ? Translator.getText("IGUI_Gametime_zombieCount", var2) : null;
      }
   }

   public String getGameModeText() {
      String var1 = Translator.getTextOrNull("IGUI_Gametime_" + Core.GameMode);
      if (var1 == null) {
         var1 = Core.GameMode;
      }

      String var2 = Translator.getTextOrNull("IGUI_Gametime_GameMode", var1);
      if (var2 == null) {
         var2 = "Game mode: " + var1;
      }

      if (Core.bDebug) {
         var2 = var2 + " (DEBUG)";
      }

      return var2;
   }

   public void init() {
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

   public float Lerp(float var1, float var2, float var3) {
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

   public void RemoveZombiesIndiscriminate(int var1) {
      if (var1 != 0) {
         for (int var2 = 0; var2 < IsoWorld.instance.CurrentCell.getZombieList().size(); var2++) {
            IsoZombie var3 = (IsoZombie)IsoWorld.instance.CurrentCell.getZombieList().get(0);
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

   public float TimeLerp(float var1, float var2, float var3, float var4) {
      float var5 = getInstance().getTimeOfDay();
      if (var4 < var3) {
         var4 += 24.0F;
      }

      boolean var6 = false;
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

   public float getDeltaMinutesPerDay() {
      return this.MinutesPerDayStart / this.MinutesPerDay;
   }

   public float getNightMin() {
      return 1.0F - this.NightMin;
   }

   public void setNightMin(float var1) {
      this.NightMin = 1.0F - var1;
   }

   public float getNightMax() {
      return 1.0F - this.NightMax;
   }

   public void setNightMax(float var1) {
      this.NightMax = 1.0F - var1;
   }

   public int getMinutes() {
      return (int)((this.getTimeOfDay() - (int)this.getTimeOfDay()) * 60.0F);
   }

   public void setMoon(float var1) {
      this.Moon = var1;
   }

   public void update(boolean var1) {
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

      if (GameServer.bServer && UIManager.getSpeedControls() != null) {
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
               if (var9 != null && var9.isAlive()) {
                  var9.setHoursSurvived(var9.getHoursSurvived() + var7);
               }
            }
         }

         if (GameServer.bServer) {
            ArrayList var14 = GameClient.instance.getPlayers();

            for (int var18 = 0; var18 < var14.size(); var18++) {
               IsoPlayer var10 = (IsoPlayer)var14.get(var18);
               var10.setHoursSurvived(var10.getHoursSurvived() + var7);
            }
         }

         if (GameClient.bClient) {
            ArrayList var15 = GameClient.instance.getPlayers();

            for (int var19 = 0; var19 < var15.size(); var19++) {
               IsoPlayer var22 = (IsoPlayer)var15.get(var19);
               if (var22 != null && !var22.isDead() && !var22.isLocalPlayer()) {
                  var22.setHoursSurvived(var22.getHoursSurvived() + var7);
               }
            }
         }

         for (int var16 = 0; var16 < IsoPlayer.numPlayers; var16++) {
            IsoPlayer var20 = IsoPlayer.players[var16];
            if (var20 != null) {
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

      if (Core.getInstance().RenderShader != null && Core.getInstance().getOffscreenBuffer() != null) {
         this.setNightTint(0.0F);
      }

      this.setMinutesStamp();
      int var17 = (int)((this.getTimeOfDay() - (int)this.getTimeOfDay()) * 60.0F);
      if (var17 / 10 != this.minutesMod) {
         IsoPlayer[] var21 = IsoPlayer.players;

         for (int var23 = 0; var23 < var21.length; var23++) {
            IsoPlayer var11 = var21[var23];
            if (var11 != null) {
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

   private void updateRoomLight() {
   }

   private void setMinutesStamp() {
      this.minutesStamp = (long)this.getWorldAgeHours() * 60L + this.getMinutes();
   }

   public long getMinutesStamp() {
      return this.minutesStamp;
   }

   public boolean getThunderStorm() {
      return ClimateManager.getInstance().getIsThunderStorming();
   }

   private void doMetaEvents() {
      byte var1 = 3;
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

   @Deprecated
   public float getAmbient() {
      return ClimateManager.getInstance().getAmbient();
   }

   public void setAmbient(float var1) {
      this.Ambient = var1;
   }

   public float getAmbientMax() {
      return this.AmbientMax;
   }

   public void setAmbientMax(float var1) {
      var1 = Math.min(1.0F, var1);
      var1 = Math.max(0.0F, var1);
      this.AmbientMax = var1;
   }

   public float getAmbientMin() {
      return this.AmbientMin;
   }

   public void setAmbientMin(float var1) {
      var1 = Math.min(1.0F, var1);
      var1 = Math.max(0.0F, var1);
      this.AmbientMin = var1;
   }

   public int getDay() {
      return this.Day;
   }

   public int getDayPlusOne() {
      return this.Day + 1;
   }

   public void setDay(int var1) {
      this.Day = var1;
   }

   public int getStartDay() {
      return this.StartDay;
   }

   public void setStartDay(int var1) {
      this.StartDay = var1;
   }

   public float getMaxZombieCountStart() {
      return 0.0F;
   }

   public void setMaxZombieCountStart(float var1) {
      this.MaxZombieCountStart = var1;
   }

   public float getMinZombieCountStart() {
      return 0.0F;
   }

   public void setMinZombieCountStart(float var1) {
      this.MinZombieCountStart = var1;
   }

   public float getMaxZombieCount() {
      return this.MaxZombieCount;
   }

   public void setMaxZombieCount(float var1) {
      this.MaxZombieCount = var1;
   }

   public float getMinZombieCount() {
      return this.MinZombieCount;
   }

   public void setMinZombieCount(float var1) {
      this.MinZombieCount = var1;
   }

   public int getMonth() {
      return this.Month;
   }

   public void setMonth(int var1) {
      this.Month = var1;
   }

   public int getStartMonth() {
      return this.StartMonth;
   }

   public void setStartMonth(int var1) {
      this.StartMonth = var1;
   }

   public float getNightTint() {
      return ClimateManager.getInstance().getNightStrength();
   }

   public void setNightTint(float var1) {
   }

   public float getNight() {
      return ClimateManager.getInstance().getNightStrength();
   }

   public void setNight(float var1) {
   }

   public float getTimeOfDay() {
      return this.TimeOfDay;
   }

   public void setTimeOfDay(float var1) {
      this.TimeOfDay = var1;
   }

   public float getStartTimeOfDay() {
      return this.StartTimeOfDay;
   }

   public void setStartTimeOfDay(float var1) {
      this.StartTimeOfDay = var1;
   }

   public float getViewDist() {
      return ClimateManager.getInstance().getViewDistance();
   }

   public float getViewDistMax() {
      return this.ViewDistMax;
   }

   public void setViewDistMax(float var1) {
      this.ViewDistMax = var1;
   }

   public float getViewDistMin() {
      return this.ViewDistMin;
   }

   public void setViewDistMin(float var1) {
      this.ViewDistMin = var1;
   }

   public int getYear() {
      return this.Year;
   }

   public void setYear(int var1) {
      this.Year = var1;
   }

   public int getStartYear() {
      return this.StartYear;
   }

   public void setStartYear(int var1) {
      this.StartYear = var1;
   }

   public int getNightsSurvived() {
      return this.NightsSurvived;
   }

   public void setNightsSurvived(int var1) {
      this.NightsSurvived = var1;
   }

   public double getWorldAgeHours() {
      float var1 = this.getNightsSurvived() * 24;
      if (this.getTimeOfDay() >= 7.0F) {
         var1 += this.getTimeOfDay() - 7.0F;
      } else {
         var1 += this.getTimeOfDay() + 17.0F;
      }

      return var1;
   }

   public double getHoursSurvived() {
      DebugLog.log("GameTime.getHoursSurvived() has no meaning, use IsoPlayer.getHourSurvived() instead");
      return this.HoursSurvived;
   }

   public void setHoursSurvived(double var1) {
      DebugLog.log("GameTime.getHoursSurvived() has no meaning, use IsoPlayer.getHourSurvived() instead");
      this.HoursSurvived = var1;
   }

   public int getHour() {
      double var1 = Math.floor(this.getTimeOfDay() * 3600.0F);
      return (int)Math.floor(var1 / 3600.0);
   }

   public PZCalendar getCalender() {
      this.updateCalendar(
         this.getYear(), this.getMonth(), this.getDay(), (int)this.getTimeOfDay(), (int)((this.getTimeOfDay() - (int)this.getTimeOfDay()) * 60.0F)
      );
      return this.Calender;
   }

   public void setCalender(PZCalendar var1) {
      this.Calender = var1;
   }

   public void updateCalendar(int var1, int var2, int var3, int var4, int var5) {
      if (this.Calender == null) {
         this.Calender = new PZCalendar(new GregorianCalendar());
      }

      this.Calender.set(var1, var2, var3, var4, var5);
   }

   public float getMinutesPerDay() {
      return this.MinutesPerDay;
   }

   public void setMinutesPerDay(float var1) {
      this.MinutesPerDay = var1;
   }

   public float getLastTimeOfDay() {
      return this.LastTimeOfDay;
   }

   public void setLastTimeOfDay(float var1) {
      this.LastTimeOfDay = var1;
   }

   public void setTargetZombies(int var1) {
      this.TargetZombies = var1;
   }

   public boolean isRainingToday() {
      return this.RainingToday;
   }

   public float getMultiplier() {
      if (!GameServer.bServer && !GameClient.bClient && IsoPlayer.getInstance() != null && IsoPlayer.allPlayersAsleep()) {
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

   public float getTimeDelta() {
      return this.getMultiplier() / (0.8F * this.multiplierBias) / 60.0F;
   }

   public static float getAnimSpeedFix() {
      return 0.8F;
   }

   public void setMultiplier(float var1) {
      this.Multiplier = var1;
   }

   public float getServerMultiplier() {
      float var1 = 10.0F / GameWindow.averageFPS / (PerformanceSettings.ManualFrameSkips + 1);
      float var2 = this.Multiplier * var1;
      var2 *= 0.5F;
      if (!GameServer.bServer && !GameClient.bClient && IsoPlayer.getInstance() != null && IsoPlayer.allPlayersAsleep()) {
         return 200.0F * (30.0F / PerformanceSettings.getLockFPS());
      } else {
         var2 *= 1.6F;
         return var2 * this.multiplierBias;
      }
   }

   public float getUnmoddedMultiplier() {
      return !GameServer.bServer && !GameClient.bClient && IsoPlayer.getInstance() != null && IsoPlayer.allPlayersAsleep()
         ? 200.0F * (30.0F / PerformanceSettings.getLockFPS())
         : this.Multiplier * this.FPSMultiplier * this.PerObjectMultiplier;
   }

   public float getInvMultiplier() {
      return 1.0F / this.getMultiplier();
   }

   public float getTrueMultiplier() {
      return this.Multiplier * this.PerObjectMultiplier;
   }

   public void save() {
      File var1 = new File(ZomboidFileSystem.instance.getFileNameInCurrentSave("map_t.bin"));
      Object var2 = null;

      try {
         var2 = new FileOutputStream(var1);
      } catch (FileNotFoundException var7) {
         var7.printStackTrace();
         return;
      }

      DataOutputStream var3 = new DataOutputStream(new BufferedOutputStream((OutputStream)var2));

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

   public void save(DataOutputStream var1) throws IOException {
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
      if (this.table != null) {
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

   public void save(ByteBuffer var1) throws IOException {
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
      if (this.table != null) {
         var1.put((byte)1);
         this.table.save(var1);
      } else {
         var1.put((byte)0);
      }
   }

   public void load(DataInputStream var1) throws IOException {
      int var2 = IsoWorld.SavedWorldVersion;
      if (var2 == -1) {
         var2 = 195;
      }

      var1.mark(0);
      byte var3 = var1.readByte();
      byte var4 = var1.readByte();
      byte var5 = var1.readByte();
      byte var6 = var1.readByte();
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
         if (this.table == null) {
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

   public void load(ByteBuffer var1) throws IOException {
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
         if (this.table == null) {
            this.table = LuaManager.platform.newTable();
         }

         this.table.load(var1, var2);
      }

      this.setMinutesStamp();
   }

   public void load() {
      File var1 = ZomboidFileSystem.instance.getFileInCurrentSave("map_t.bin");

      try (
         FileInputStream var2 = new FileInputStream(var1);
         BufferedInputStream var3 = new BufferedInputStream(var2);
      ) {
         synchronized (SliceY.SliceBufferLock) {
            SliceY.SliceBuffer.clear();
            int var5 = var3.read(SliceY.SliceBuffer.array());
            SliceY.SliceBuffer.limit(var5);
            DataInputStream var6 = new DataInputStream(new ByteArrayInputStream(SliceY.SliceBuffer.array(), 0, var5));
            this.load(var6);
         }
      } catch (FileNotFoundException var13) {
      } catch (Exception var14) {
         ExceptionLogger.logException(var14);
      }
   }

   public int getDawn() {
      return this.dawn;
   }

   public void setDawn(int var1) {
      this.dawn = var1;
   }

   public int getDusk() {
      return this.dusk;
   }

   public void setDusk(int var1) {
      this.dusk = var1;
   }

   public KahluaTable getModData() {
      if (this.table == null) {
         this.table = LuaManager.platform.newTable();
      }

      return this.table;
   }

   public boolean isThunderDay() {
      return this.thunderDay;
   }

   public void setThunderDay(boolean var1) {
      this.thunderDay = var1;
   }

   public void saveToPacket(ByteBuffer var1) throws IOException {
      KahluaTable var2 = getInstance().getModData();
      Object var3 = var2.rawget("camping");
      Object var4 = var2.rawget("farming");
      Object var5 = var2.rawget("trapping");
      var2.rawset("camping", null);
      var2.rawset("farming", null);
      var2.rawset("trapping", null);
      this.save(var1);
      var2.rawset("camping", var3);
      var2.rawset("farming", var4);
      var2.rawset("trapping", var5);
   }

   public int getHelicopterDay1() {
      return this.HelicopterDay1;
   }

   public int getHelicopterDay() {
      return this.HelicopterDay1;
   }

   public void setHelicopterDay(int var1) {
      this.HelicopterDay1 = PZMath.max(var1, 0);
   }

   public int getHelicopterStartHour() {
      return this.HelicopterTime1Start;
   }

   public void setHelicopterStartHour(int var1) {
      this.HelicopterTime1Start = PZMath.clamp(var1, 0, 24);
   }

   public int getHelicopterEndHour() {
      return this.HelicopterTime1End;
   }

   public void setHelicopterEndHour(int var1) {
      this.HelicopterTime1End = PZMath.clamp(var1, 0, 24);
   }

   public static boolean isGamePaused() {
      if (GameServer.bServer) {
         return GameServer.Players.isEmpty() && ServerOptions.instance.PauseEmpty.getValue();
      } else if (GameClient.bClient) {
         return GameClient.IsClientPaused();
      } else {
         SpeedControls var0 = UIManager.getSpeedControls();
         return var0 != null && var0.getCurrentGameSpeed() == 0;
      }
   }
}
