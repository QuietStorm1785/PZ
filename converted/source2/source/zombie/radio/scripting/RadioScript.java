package zombie.radio.scripting;

import java.util.ArrayList;
import java.util.UUID;
import zombie.core.Rand;
import zombie.debug.DebugLog;
import zombie.debug.DebugType;
import zombie.radio.scripting.RadioScript.ExitOption;

public final class RadioScript {
   private final ArrayList<RadioBroadCast> broadcasts = new ArrayList<>();
   private final ArrayList<ExitOption> exitOptions = new ArrayList<>();
   private String GUID;
   private String name = "Unnamed radioscript";
   private int startDay = 0;
   private int startDayStamp = 0;
   private int loopMin = 1;
   private int loopMax = 1;
   private int internalStamp = 0;
   private RadioBroadCast currentBroadcast = null;
   private boolean currentHasAired = false;

   public RadioScript(String var1, int var2, int var3) {
      this(var1, var2, var3, UUID.randomUUID().toString());
   }

   public RadioScript(String var1, int var2, int var3, String var4) {
      this.name = var1;
      this.loopMin = var2;
      this.loopMax = var3;
      this.GUID = var4;
   }

   public String GetGUID() {
      return this.GUID;
   }

   public String GetName() {
      return this.name;
   }

   public int getStartDayStamp() {
      return this.startDayStamp;
   }

   public int getStartDay() {
      return this.startDay;
   }

   public int getLoopMin() {
      return this.loopMin;
   }

   public int getLoopMax() {
      return this.loopMax;
   }

   public RadioBroadCast getCurrentBroadcast() {
      return this.currentBroadcast;
   }

   public ArrayList<RadioBroadCast> getBroadcastList() {
      return this.broadcasts;
   }

   public void clearExitOptions() {
      this.exitOptions.clear();
   }

   public void setStartDayStamp(int var1) {
      this.startDay = var1;
      this.startDayStamp = var1 * 24 * 60;
   }

   public RadioBroadCast getValidAirBroadcast() {
      if (!this.currentHasAired
         && this.currentBroadcast != null
         && this.internalStamp >= this.currentBroadcast.getStartStamp()
         && this.internalStamp < this.currentBroadcast.getEndStamp()) {
         this.currentHasAired = true;
         return this.currentBroadcast;
      } else {
         return null;
      }
   }

   public void Reset() {
      this.currentBroadcast = null;
      this.currentHasAired = false;
   }

   private RadioBroadCast getNextBroadcast() {
      if (this.currentBroadcast != null && this.currentBroadcast.getEndStamp() > this.internalStamp) {
         return this.currentBroadcast;
      } else {
         for (int var1 = 0; var1 < this.broadcasts.size(); var1++) {
            RadioBroadCast var2 = this.broadcasts.get(var1);
            if (var2.getEndStamp() > this.internalStamp) {
               this.currentHasAired = false;
               return var2;
            }
         }

         return null;
      }
   }

   public RadioBroadCast getBroadcastWithID(String var1) {
      for (int var2 = 0; var2 < this.broadcasts.size(); var2++) {
         RadioBroadCast var3 = this.broadcasts.get(var2);
         if (var3.getID().equals(var1)) {
            this.currentBroadcast = var3;
            this.currentHasAired = true;
            return var3;
         }
      }

      return null;
   }

   public boolean UpdateScript(int var1) {
      this.internalStamp = var1 - this.startDayStamp;
      this.currentBroadcast = this.getNextBroadcast();
      return this.currentBroadcast != null;
   }

   public ExitOption getNextScript() {
      int var1 = 0;
      int var2 = Rand.Next(100);

      for (ExitOption var4 : this.exitOptions) {
         if (var2 >= var1 && var2 < var1 + var4.getChance()) {
            return var4;
         }

         var1 += var4.getChance();
      }

      return null;
   }

   public void AddBroadcast(RadioBroadCast var1) {
      this.AddBroadcast(var1, false);
   }

   public void AddBroadcast(RadioBroadCast var1, boolean var2) {
      boolean var3 = false;
      if (var1 != null && var1.getID() != null) {
         if (var2) {
            this.broadcasts.add(var1);
            var3 = true;
         } else if (var1.getStartStamp() >= 0 && var1.getEndStamp() > var1.getStartStamp()) {
            if (this.broadcasts.size() == 0 || this.broadcasts.get(this.broadcasts.size() - 1).getEndStamp() <= var1.getStartStamp()) {
               this.broadcasts.add(var1);
               var3 = true;
            } else if (this.broadcasts.size() > 0) {
               DebugLog.log(
                  DebugType.Radio,
                  "startstamp = '"
                     + var1.getStartStamp()
                     + "', endstamp = '"
                     + var1.getEndStamp()
                     + "', previous endstamp = '"
                     + this.broadcasts.get(this.broadcasts.size() - 1).getEndStamp()
                     + "'."
               );
            }
         } else {
            DebugLog.log(DebugType.Radio, "startstamp = '" + var1.getStartStamp() + "', endstamp = '" + var1.getEndStamp() + "'.");
         }
      }

      if (!var3) {
         String var4 = var1 != null ? var1.getID() : "null";
         DebugLog.log(DebugType.Radio, "Error cannot add broadcast ID: '" + var4 + "' to script '" + this.name + "', null or timestamp error");
      }
   }

   public void AddExitOption(String var1, int var2, int var3) {
      int var4 = var2;

      for (ExitOption var6 : this.exitOptions) {
         var4 += var6.getChance();
      }

      if (var4 <= 100) {
         this.exitOptions.add(new ExitOption(var1, var2, var3));
      } else {
         DebugLog.log(DebugType.Radio, "Error cannot add exitoption with scriptname '" + var1 + "' to script '" + this.name + "', total chance exceeding 100");
      }
   }

   public RadioBroadCast getValidAirBroadcastDebug() {
      if (this.currentBroadcast != null && this.currentBroadcast.getEndStamp() > this.internalStamp) {
         return this.currentBroadcast;
      } else {
         for (int var1 = 0; var1 < this.broadcasts.size(); var1++) {
            RadioBroadCast var2 = this.broadcasts.get(var1);
            if (var2.getEndStamp() > this.internalStamp) {
               return var2;
            }
         }

         return null;
      }
   }

   public ArrayList<ExitOption> getExitOptions() {
      return this.exitOptions;
   }
}
