package zombie.iso.weather;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import zombie.GameWindow;
import zombie.iso.weather.WeatherPeriod.1;
import zombie.iso.weather.WeatherPeriod.StrLerpVal;

public class WeatherPeriod$WeatherStage {
   protected WeatherPeriod$WeatherStage previousStage;
   protected WeatherPeriod$WeatherStage nextStage;
   private double stageStart;
   private double stageEnd;
   private double stageDuration;
   protected int stageID;
   protected float entryStrength;
   protected float exitStrength;
   protected float targetStrength;
   protected StrLerpVal lerpMidVal;
   protected StrLerpVal lerpEndVal;
   protected boolean hasStartedCloud = false;
   protected float fogStrength = 0.0F;
   protected float linearT;
   protected float parabolicT;
   protected boolean isCycleFirstHalf = true;
   protected boolean creationFinished = false;
   protected String modID;
   private float m;
   private float e;

   public WeatherPeriod$WeatherStage() {
   }

   public WeatherPeriod$WeatherStage(int var1) {
      this.stageID = var1;
   }

   public void setStageID(int var1) {
      this.stageID = var1;
   }

   public double getStageStart() {
      return this.stageStart;
   }

   public double getStageEnd() {
      return this.stageEnd;
   }

   public double getStageDuration() {
      return this.stageDuration;
   }

   public int getStageID() {
      return this.stageID;
   }

   public String getModID() {
      return this.modID;
   }

   public float getLinearT() {
      return this.linearT;
   }

   public float getParabolicT() {
      return this.parabolicT;
   }

   public void setTargetStrength(float var1) {
      this.targetStrength = var1;
   }

   public boolean getHasStartedCloud() {
      return this.hasStartedCloud;
   }

   public void setHasStartedCloud(boolean var1) {
      this.hasStartedCloud = true;
   }

   public void save(DataOutputStream var1) throws IOException {
      var1.writeDouble(this.stageStart);
      var1.writeFloat(this.entryStrength);
      var1.writeFloat(this.exitStrength);
      var1.writeFloat(this.targetStrength);
      var1.writeInt(this.lerpMidVal.getValue());
      var1.writeInt(this.lerpEndVal.getValue());
      var1.writeBoolean(this.hasStartedCloud);
      var1.writeByte(this.modID != null ? 1 : 0);
      if (this.modID != null) {
         GameWindow.WriteString(var1, this.modID);
      }

      var1.writeFloat(this.fogStrength);
   }

   public void load(DataInputStream var1, int var2) throws IOException {
      this.stageStart = var1.readDouble();
      this.stageEnd = this.stageStart + this.stageDuration;
      this.entryStrength = var1.readFloat();
      this.exitStrength = var1.readFloat();
      this.targetStrength = var1.readFloat();
      this.lerpMidVal = StrLerpVal.fromValue(var1.readInt());
      this.lerpEndVal = StrLerpVal.fromValue(var1.readInt());
      this.hasStartedCloud = var1.readBoolean();
      if (var2 >= 141 && var1.readByte() == 1) {
         this.modID = GameWindow.ReadString(var1);
      }

      if (var2 >= 170) {
         this.fogStrength = var1.readFloat();
      }
   }

   protected void reset() {
      this.previousStage = null;
      this.nextStage = null;
      this.isCycleFirstHalf = true;
      this.hasStartedCloud = false;
      this.lerpMidVal = StrLerpVal.None;
      this.lerpEndVal = StrLerpVal.None;
      this.entryStrength = 0.0F;
      this.exitStrength = 0.0F;
      this.modID = null;
      this.creationFinished = false;
      this.fogStrength = 0.0F;
   }

   protected WeatherPeriod$WeatherStage startStage(double var1) {
      this.stageStart = var1;
      this.stageEnd = var1 + this.stageDuration;
      this.hasStartedCloud = false;
      return this;
   }

   protected double setStageStart(double var1) {
      this.stageStart = var1;
      this.stageEnd = var1 + this.stageDuration;
      return this.stageEnd;
   }

   protected WeatherPeriod$WeatherStage setStageDuration(double var1) {
      this.stageDuration = var1;
      if (this.stageDuration < 1.0) {
         this.stageDuration = 1.0;
      }

      return this;
   }

   protected WeatherPeriod$WeatherStage overrideStageDuration(double var1) {
      this.stageDuration = var1;
      return this;
   }

   public void lerpEntryTo(int var1, int var2) {
      if (!this.creationFinished) {
         this.lerpEntryTo(StrLerpVal.fromValue(var1), StrLerpVal.fromValue(var2));
      }
   }

   protected void lerpEntryTo(StrLerpVal var1) {
      this.lerpEntryTo(StrLerpVal.None, var1);
   }

   protected void lerpEntryTo(StrLerpVal var1, StrLerpVal var2) {
      if (!this.creationFinished) {
         this.lerpMidVal = var1;
         this.lerpEndVal = var2;
      }
   }

   public float getStageCurrentStrength() {
      this.m = this.getLerpValue(this.lerpMidVal);
      this.e = this.getLerpValue(this.lerpEndVal);
      if (this.lerpMidVal == StrLerpVal.None) {
         return ClimateManager.clerp(this.linearT, this.entryStrength, this.e);
      } else {
         return this.isCycleFirstHalf
            ? ClimateManager.clerp(this.parabolicT, this.entryStrength, this.m)
            : ClimateManager.clerp(this.parabolicT, this.e, this.m);
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   private float getLerpValue(StrLerpVal var1) {
      switch (1.$SwitchMap$zombie$iso$weather$WeatherPeriod$StrLerpVal[var1.ordinal()]) {
         case 1:
            return this.entryStrength;
         case 2:
            return this.targetStrength;
         case 3:
            return this.nextStage != null ? this.nextStage.targetStrength : 0.0F;
         case 4:
            return 0.0F;
         default:
            return 0.0F;
      }
   }

   private WeatherPeriod$WeatherStage updateT(double var1) {
      this.linearT = this.getPeriodLerpT(var1);
      if (this.stageID == 11) {
         this.linearT = WeatherPeriod.kateBobStormProgress + (1.0F - WeatherPeriod.kateBobStormProgress) * this.linearT;
      }

      if (this.linearT < 0.5F) {
         this.parabolicT = this.linearT * 2.0F;
         this.isCycleFirstHalf = true;
      } else {
         this.parabolicT = 2.0F - this.linearT * 2.0F;
         this.isCycleFirstHalf = false;
      }

      return this;
   }

   private float getPeriodLerpT(double var1) {
      if (var1 < this.stageStart) {
         return 0.0F;
      } else {
         return var1 > this.stageEnd ? 1.0F : (float)((var1 - this.stageStart) / this.stageDuration);
      }
   }
}
