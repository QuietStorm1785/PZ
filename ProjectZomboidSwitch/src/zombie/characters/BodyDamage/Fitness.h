#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/BodyDamage/Fitness/FitnessExercise.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/core/Rand.h"
#include <algorithm>
#include <filesystem>
#include <iterator>

namespace zombie {
namespace characters {
namespace BodyDamage {


class Fitness {
public:
    IsoGameCharacter parent = nullptr;
   private std::unordered_map<std::string, float> regularityMap = std::make_unique<std::unordered_map<>>();
    int fitnessLvl = 0;
    int strLvl = 0;
   private const std::unordered_map<std::string, int> stiffnessTimerMap = std::make_unique<std::unordered_map<>>();
   private const std::unordered_map<std::string, float> stiffnessIncMap = std::make_unique<std::unordered_map<>>();
   private const std::vector<std::string> bodypartToIncStiffness = std::make_unique<std::vector<>>();
   private const std::unordered_map<std::string, FitnessExercise> exercises = std::make_unique<std::unordered_map<>>();
   private const std::unordered_map<std::string, int64_t> exeTimer = std::make_unique<std::unordered_map<>>();
    int lastUpdate = -1;
    FitnessExercise currentExe;
    static const int HOURS_FOR_STIFFNESS = 12;
    static const float BASE_STIFFNESS_INC = 0.5F;
    static const float BASE_ENDURANCE_RED = 0.015F;
    static const float BASE_REGULARITY_INC = 0.08F;
    static const float BASE_REGULARITY_DEC = 0.002F;
    static const float BASE_PAIN_INC = 2.5F;

    public Fitness(IsoGameCharacter var1) {
      this.setParent(var1);
   }

    void update() {
    int var1 = GameTime.getInstance().getMinutes() / 10;
      if (this.lastUpdate == -1) {
         this.lastUpdate = var1;
      }

      if (var1 != this.lastUpdate) {
         this.lastUpdate = var1;
    std::vector var2 = new std::vector();
         this.decreaseRegularity();

         for (std::string var4 : this.stiffnessTimerMap.keySet()) {
    int var5 = this.stiffnessTimerMap.get(var4);
            var5 = var5 - 1;
            if (var5 <= 0) {
               var2.push_back(var4);
               this.bodypartToIncStiffness.push_back(var4);
            } else {
               this.stiffnessTimerMap.put(var4, var5);
            }
         }

         for (int var8 = 0; var8 < var2.size(); var8++) {
            this.stiffnessTimerMap.remove(var2.get(var8));
         }

         for (int var9 = 0; var9 < this.bodypartToIncStiffness.size(); var9++) {
    std::string var11 = this.bodypartToIncStiffness.get(var9);
    float var6 = this.stiffnessIncMap.get(var11);
            if (var6 == nullptr) {
               return;
            }

            var6 = var6 - 1.0F;
            this.increasePain(var11);
            if (var6 <= 0.0F) {
               this.bodypartToIncStiffness.remove(var9);
               this.stiffnessIncMap.remove(var11);
               var9--;
            } else {
               this.stiffnessIncMap.put(var11, var6);
            }
         }
      }
   }

    void decreaseRegularity() {
      for (std::string var2 : this.regularityMap.keySet()) {
         if (this.exeTimer.containsKey(var2) && GameTime.getInstance().getCalender().getTimeInMillis() - this.exeTimer.get(var2) > 86400000L) {
    float var3 = this.regularityMap.get(var2);
            var3 -= 0.002F;
            this.regularityMap.put(var2, var3);
         }
      }
   }

    void increasePain(const std::string& var1) {
      if ("arms" == var1)) {
         for (int var2 = BodyPartType.ForeArm_L.index(); var2 < BodyPartType.UpperArm_R.index() + 1; var2++) {
    BodyPart var3 = this.parent.getBodyDamage().getBodyPart(BodyPartType.FromIndex(var2));
            var3.setStiffness(var3.getStiffness() + 2.5F);
         }
      }

      if ("legs" == var1)) {
         for (int var4 = BodyPartType.UpperLeg_L.index(); var4 < BodyPartType.LowerLeg_R.index() + 1; var4++) {
    BodyPart var7 = this.parent.getBodyDamage().getBodyPart(BodyPartType.FromIndex(var4));
            var7.setStiffness(var7.getStiffness() + 2.5F);
         }
      }

      if ("chest" == var1)) {
    BodyPart var5 = this.parent.getBodyDamage().getBodyPart(BodyPartType.Torso_Upper);
         var5.setStiffness(var5.getStiffness() + 2.5F);
      }

      if ("abs" == var1)) {
    BodyPart var6 = this.parent.getBodyDamage().getBodyPart(BodyPartType.Torso_Lower);
         var6.setStiffness(var6.getStiffness() + 2.5F);
      }
   }

    void setCurrentExercise(const std::string& var1) {
      this.currentExe = this.exercises.get(var1);
   }

    void exerciseRepeat() {
      this.fitnessLvl = this.parent.getPerkLevel(Perks.Fitness);
      this.strLvl = this.parent.getPerkLevel(Perks.Strength);
      this.incRegularity();
      this.reduceEndurance();
      this.incFutureStiffness();
      this.incStats();
      this.updateExeTimer();
   }

    void updateExeTimer() {
      this.exeTimer.put(this.currentExe.type, GameTime.getInstance().getCalender().getTimeInMillis());
   }

    void incRegularity() {
    float var1 = 0.08F;
    uint8_t var2 = 4;
    double var3 = Math.log(this.fitnessLvl / 5.0F + var2);
      var1 = (float)(var1 * (Math.log(var2 + 1) / var3));
    float var5 = this.regularityMap.get(this.currentExe.type);
      if (var5 == nullptr) {
         var5 = 0.0F;
      }

      var5 = var5 + var1;
      var5 = Math.min(Math.max(var5, 0.0F), 100.0F);
      this.regularityMap.put(this.currentExe.type, var5);
   }

    void reduceEndurance() {
    float var1 = 0.015F;
    float var2 = this.regularityMap.get(this.currentExe.type);
      if (var2 == nullptr) {
         var2 = 0.0F;
      }

    uint8_t var3 = 50;
    double var4 = Math.log(var2 / 50.0F + var3);
      var1 = (float)(var1 * (var4 / Math.log(var3 + 1)));
      if (this.currentExe.metabolics == Metabolics.FitnessHeavy) {
         var1 *= 1.3F;
      }

      var1 *= 1 + this.parent.getMoodles().getMoodleLevel(MoodleType.HeavyLoad) / 3;
      this.parent.getStats().setEndurance(this.parent.getStats().getEndurance() - var1);
   }

    void incFutureStiffness() {
    float var1 = this.regularityMap.get(this.currentExe.type);
      if (var1 == nullptr) {
         var1 = 0.0F;
      }

      for (int var2 = 0; var2 < this.currentExe.stiffnessInc.size(); var2++) {
    float var3 = 0.5F;
    std::string var4 = (std::string)this.currentExe.stiffnessInc.get(var2);
         if (!this.stiffnessTimerMap.containsKey(var4) && !this.bodypartToIncStiffness.contains(var4)) {
            this.stiffnessTimerMap.put(var4, 72);
         }

    float var5 = this.stiffnessIncMap.get(var4);
         if (var5 == nullptr) {
            var5 = 0.0F;
         }

         var3 *= (120.0F - var1) / 170.0F;
         if (this.currentExe.metabolics == Metabolics.FitnessHeavy) {
            var3 *= 1.3F;
         }

         var3 *= 1 + this.parent.getMoodles().getMoodleLevel(MoodleType.Tired) / 3;
         var5 = var5 + var3;
         var5 = Math.min(var5, 150.0F);
         this.stiffnessIncMap.put(var4, var5);
      }
   }

    void incStats() {
    float var1 = 0.0F;
    float var2 = 0.0F;

      for (int var3 = 0; var3 < this.currentExe.stiffnessInc.size(); var3++) {
    std::string var4 = (std::string)this.currentExe.stiffnessInc.get(var3);
         if ("arms" == var4)) {
            var1 += 4.0F;
         }

         if ("chest" == var4)) {
            var1 += 2.0F;
         }

         if ("legs" == var4)) {
            var2 += 4.0F;
         }

         if ("abs" == var4)) {
            var2 += 2.0F;
         }
      }

      if (this.strLvl > 5) {
         var1 *= 1 + (this.strLvl - 5) / 10;
      }

      if (this.fitnessLvl > 5) {
         var2 *= 1 + (this.fitnessLvl - 5) / 10;
      }

      var1 *= this.currentExe.xpModifier;
      var2 *= this.currentExe.xpModifier;
      this.parent.getXp().AddXP(Perks.Strength, var1);
      this.parent.getXp().AddXP(Perks.Fitness, var2);
   }

    void resetValues() {
      this.stiffnessIncMap.clear();
      this.stiffnessTimerMap.clear();
      this.regularityMap.clear();
   }

    void removeStiffnessValue(const std::string& var1) {
      this.stiffnessIncMap.remove(var1);
      this.stiffnessTimerMap.remove(var1);
   }

    void save(ByteBuffer var1) {
      var1.putInt(this.stiffnessIncMap.size());

      for (std::string var3 : this.stiffnessIncMap.keySet()) {
         GameWindow.WriteString(var1, var3);
         var1.putFloat(this.stiffnessIncMap.get(var3));
      }

      var1.putInt(this.stiffnessTimerMap.size());

      for (std::string var7 : this.stiffnessTimerMap.keySet()) {
         GameWindow.WriteString(var1, var7);
         var1.putInt(this.stiffnessTimerMap.get(var7));
      }

      var1.putInt(this.regularityMap.size());

      for (std::string var8 : this.regularityMap.keySet()) {
         GameWindow.WriteString(var1, var8);
         var1.putFloat(this.regularityMap.get(var8));
      }

      var1.putInt(this.bodypartToIncStiffness.size());

      for (int var9 = 0; var9 < this.bodypartToIncStiffness.size(); var9++) {
         GameWindow.WriteString(var1, this.bodypartToIncStiffness.get(var9));
      }

      var1.putInt(this.exeTimer.size());

      for (std::string var10 : this.exeTimer.keySet()) {
         GameWindow.WriteString(var1, var10);
         var1.putLong(this.exeTimer.get(var10));
      }
   }

    void load(ByteBuffer var1, int var2) {
      if (var2 >= 167) {
    int var3 = var1.getInt();
         if (var3 > 0) {
            for (int var4 = 0; var4 < var3; var4++) {
               this.stiffnessIncMap.put(GameWindow.ReadString(var1), var1.getFloat());
            }
         }

         var3 = var1.getInt();
         if (var3 > 0) {
            for (int var9 = 0; var9 < var3; var9++) {
               this.stiffnessTimerMap.put(GameWindow.ReadString(var1), var1.getInt());
            }
         }

         var3 = var1.getInt();
         if (var3 > 0) {
            for (int var10 = 0; var10 < var3; var10++) {
               this.regularityMap.put(GameWindow.ReadString(var1), var1.getFloat());
            }
         }

         var3 = var1.getInt();
         if (var3 > 0) {
            for (int var11 = 0; var11 < var3; var11++) {
               this.bodypartToIncStiffness.push_back(GameWindow.ReadString(var1));
            }
         }

         if (var2 >= 169) {
            var3 = var1.getInt();
            if (var3 > 0) {
               for (int var12 = 0; var12 < var3; var12++) {
                  this.exeTimer.put(GameWindow.ReadString(var1), var1.getLong());
               }
            }
         }
      }
   }

    bool onGoingStiffness() {
      return !this.bodypartToIncStiffness.empty();
   }

    int getCurrentExeStiffnessTimer(const std::string& var1) {
      var1 = var1.split(",")[0];
      return this.stiffnessTimerMap.get(var1) != nullptr ? this.stiffnessTimerMap.get(var1) : 0;
   }

    float getCurrentExeStiffnessInc(const std::string& var1) {
      var1 = var1.split(",")[0];
      return this.stiffnessIncMap.get(var1) != nullptr ? this.stiffnessIncMap.get(var1) : 0.0F;
   }

    IsoGameCharacter getParent() {
      return this.parent;
   }

    void setParent(IsoGameCharacter var1) {
      this.parent = var1;
   }

    float getRegularity(const std::string& var1) {
    float var2 = this.regularityMap.get(var1);
      if (var2 == nullptr) {
         var2 = 0.0F;
      }

    return var2;
   }

   public std::unordered_map<std::string, float> getRegularityMap() {
      return this.regularityMap;
   }

    void setRegularityMap(float> var1) {
      this.regularityMap = var1;
   }

    void init() {
      if (this.exercises.empty()) {
    KahluaTableImpl var1 = (KahluaTableImpl)LuaManager.env.rawget("FitnessExercises");
    KahluaTableImpl var2 = (KahluaTableImpl)var1.rawget("exercisesType");

         for (Entry var4 : var2.delegate.entrySet()) {
            this.exercises.put((std::string)var4.getKey(), std::make_shared<FitnessExercise>((KahluaTableImpl)var4.getValue()));
         }

         this.initRegularityMapProfession();
      }
   }

    void initRegularityMapProfession() {
      if (this.regularityMap.empty()) {
    bool var1 = false;
    bool var2 = false;
    bool var3 = false;
         if (this.parent.getDescriptor().getProfession() == "fitnessInstructor")) {
            var2 = true;
         }

         if (this.parent.getDescriptor().getProfession() == "fireofficer")) {
            var1 = true;
         }

         if (this.parent.getDescriptor().getProfession() == "securityguard")) {
            var3 = true;
         }

         if (var1 || var2 || var3) {
    Iterator var4 = this.exercises.keySet().iterator();

            while (var4.hasNext()) {
    float var5 = Rand.Next(7, 12);
               if (var1) {
                  var5 = Rand.Next(10, 20);
               }

               if (var2) {
                  var5 = Rand.Next(40, 60);
               }

               this.regularityMap.put((std::string)var4.next(), var5);
            }
         }
      }
   }
}
} // namespace BodyDamage
} // namespace characters
} // namespace zombie
