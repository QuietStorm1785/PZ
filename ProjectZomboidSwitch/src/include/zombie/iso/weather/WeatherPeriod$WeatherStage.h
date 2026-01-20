#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/iso/weather/WeatherPeriod/1.h"
#include "zombie/iso/weather/WeatherPeriod/StrLerpVal.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace weather {


class WeatherPeriod {
public:
   protected WeatherPeriod$WeatherStage previousStage;
   protected WeatherPeriod$WeatherStage nextStage;
    double stageStart;
    double stageEnd;
    double stageDuration;
    int stageID;
    float entryStrength;
    float exitStrength;
    float targetStrength;
    StrLerpVal lerpMidVal;
    StrLerpVal lerpEndVal;
    bool hasStartedCloud = false;
    float fogStrength = 0.0F;
    float linearT;
    float parabolicT;
    bool isCycleFirstHalf = true;
    bool creationFinished = false;
    std::string modID;
    float m;
    float e;

   public WeatherPeriod$WeatherStage() {
   }

   public WeatherPeriod$WeatherStage(int var1) {
      this.stageID = var1;
   }

    void setStageID(int var1) {
      this.stageID = var1;
   }

    double getStageStart() {
      return this.stageStart;
   }

    double getStageEnd() {
      return this.stageEnd;
   }

    double getStageDuration() {
      return this.stageDuration;
   }

    int getStageID() {
      return this.stageID;
   }

    std::string getModID() {
      return this.modID;
   }

    float getLinearT() {
      return this.linearT;
   }

    float getParabolicT() {
      return this.parabolicT;
   }

    void setTargetStrength(float var1) {
      this.targetStrength = var1;
   }

    bool getHasStartedCloud() {
      return this.hasStartedCloud;
   }

    void setHasStartedCloud(bool var1) {
      this.hasStartedCloud = true;
   }

    void save(DataOutputStream var1) {
      var1.writeDouble(this.stageStart);
      var1.writeFloat(this.entryStrength);
      var1.writeFloat(this.exitStrength);
      var1.writeFloat(this.targetStrength);
      var1.writeInt(this.lerpMidVal.getValue());
      var1.writeInt(this.lerpEndVal.getValue());
      var1.writeBoolean(this.hasStartedCloud);
      var1.writeByte(this.modID != nullptr ? 1 : 0);
      if (this.modID != nullptr) {
         GameWindow.WriteString(var1, this.modID);
      }

      var1.writeFloat(this.fogStrength);
   }

    void load(DataInputStream var1, int var2) {
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

    void reset() {
      this.previousStage = nullptr;
      this.nextStage = nullptr;
      this.isCycleFirstHalf = true;
      this.hasStartedCloud = false;
      this.lerpMidVal = StrLerpVal.None;
      this.lerpEndVal = StrLerpVal.None;
      this.entryStrength = 0.0F;
      this.exitStrength = 0.0F;
      this.modID = nullptr;
      this.creationFinished = false;
      this.fogStrength = 0.0F;
   }

   protected WeatherPeriod$WeatherStage startStage(double var1) {
      this.stageStart = var1;
      this.stageEnd = var1 + this.stageDuration;
      this.hasStartedCloud = false;
    return this;
   }

    double setStageStart(double var1) {
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

    void lerpEntryTo(int var1, int var2) {
      if (!this.creationFinished) {
         this.lerpEntryTo(StrLerpVal.fromValue(var1), StrLerpVal.fromValue(var2));
      }
   }

    void lerpEntryTo(StrLerpVal var1) {
      this.lerpEntryTo(StrLerpVal.None, var1);
   }

    void lerpEntryTo(StrLerpVal var1, StrLerpVal var2) {
      if (!this.creationFinished) {
         this.lerpMidVal = var1;
         this.lerpEndVal = var2;
      }
   }

    float getStageCurrentStrength() {
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
    float getLerpValue(StrLerpVal var1) {
      switch (1.$SwitchMap$zombie$iso$weather$WeatherPeriod$StrLerpVal[var1.ordinal()]) {
         case 1:
            return this.entryStrength;
         case 2:
            return this.targetStrength;
         case 3:
            return this.nextStage != nullptr ? this.nextStage.targetStrength : 0.0F;
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

    float getPeriodLerpT(double var1) {
      if (var1 < this.stageStart) {
         return 0.0F;
      } else {
         return var1 > this.stageEnd ? 1.0F : (float)((var1 - this.stageStart) / this.stageDuration);
      }
   }
}
} // namespace weather
} // namespace iso
} // namespace zombie
