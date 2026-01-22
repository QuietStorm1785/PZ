#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace characters {


class Stats {
public:
    float Anger = 0.0F;
    float boredom = 0.0F;
    float endurance = 1.0F;
    bool enduranceRecharging = false;
    float endurancelast = 1.0F;
    float endurancedanger = 0.25F;
    float endurancewarn = 0.5F;
    float fatigue = 0.0F;
    float fitness = 1.0F;
    float hunger = 0.0F;
    float idleboredom = 0.0F;
    float morale = 0.5F;
    float stress = 0.0F;
    float Fear = 0.0F;
    float Panic = 0.0F;
    float Sanity = 1.0F;
    float Sickness = 0.0F;
    float Boredom = 0.0F;
    float Pain = 0.0F;
    float Drunkenness = 0.0F;
    int NumVisibleZombies = 0;
    int LastNumVisibleZombies = 0;
    bool Tripping = false;
    float TrippingRotAngle = 0.0F;
    float thirst = 0.0F;
    int NumChasingZombies = 0;
    int LastVeryCloseZombies = 0;
    static int NumCloseZombies = 0;
    int LastNumChasingZombies = 0;
    float stressFromCigarettes = 0.0F;
    float ChasingZombiesDanger;
    int MusicZombiesVisible = 0;
    int MusicZombiesTargeting = 0;

    int getNumVisibleZombies() {
      return this.NumVisibleZombies;
   }

    int getNumChasingZombies() {
      return this.LastNumChasingZombies;
   }

    int getNumVeryCloseZombies() {
      return this.LastVeryCloseZombies;
   }

    void load(DataInputStream var1) {
      this.Anger = var1.readFloat();
      this.boredom = var1.readFloat();
      this.endurance = var1.readFloat();
      this.fatigue = var1.readFloat();
      this.fitness = var1.readFloat();
      this.hunger = var1.readFloat();
      this.morale = var1.readFloat();
      this.stress = var1.readFloat();
      this.Fear = var1.readFloat();
      this.Panic = var1.readFloat();
      this.Sanity = var1.readFloat();
      this.Sickness = var1.readFloat();
      this.Boredom = var1.readFloat();
      this.Pain = var1.readFloat();
      this.Drunkenness = var1.readFloat();
      this.thirst = var1.readFloat();
   }

    void load(ByteBuffer var1, int var2) {
      this.Anger = var1.getFloat();
      this.boredom = var1.getFloat();
      this.endurance = var1.getFloat();
      this.fatigue = var1.getFloat();
      this.fitness = var1.getFloat();
      this.hunger = var1.getFloat();
      this.morale = var1.getFloat();
      this.stress = var1.getFloat();
      this.Fear = var1.getFloat();
      this.Panic = var1.getFloat();
      this.Sanity = var1.getFloat();
      this.Sickness = var1.getFloat();
      this.Boredom = var1.getFloat();
      this.Pain = var1.getFloat();
      this.Drunkenness = var1.getFloat();
      this.thirst = var1.getFloat();
      if (var2 >= 97) {
         this.stressFromCigarettes = var1.getFloat();
      }
   }

    void save(DataOutputStream var1) {
      var1.writeFloat(this.Anger);
      var1.writeFloat(this.boredom);
      var1.writeFloat(this.endurance);
      var1.writeFloat(this.fatigue);
      var1.writeFloat(this.fitness);
      var1.writeFloat(this.hunger);
      var1.writeFloat(this.morale);
      var1.writeFloat(this.stress);
      var1.writeFloat(this.Fear);
      var1.writeFloat(this.Panic);
      var1.writeFloat(this.Sanity);
      var1.writeFloat(this.Sickness);
      var1.writeFloat(this.Boredom);
      var1.writeFloat(this.Pain);
      var1.writeFloat(this.Drunkenness);
      var1.writeFloat(this.thirst);
   }

    void save(ByteBuffer var1) {
      var1.putFloat(this.Anger);
      var1.putFloat(this.boredom);
      var1.putFloat(this.endurance);
      var1.putFloat(this.fatigue);
      var1.putFloat(this.fitness);
      var1.putFloat(this.hunger);
      var1.putFloat(this.morale);
      var1.putFloat(this.stress);
      var1.putFloat(this.Fear);
      var1.putFloat(this.Panic);
      var1.putFloat(this.Sanity);
      var1.putFloat(this.Sickness);
      var1.putFloat(this.Boredom);
      var1.putFloat(this.Pain);
      var1.putFloat(this.Drunkenness);
      var1.putFloat(this.thirst);
      var1.putFloat(this.stressFromCigarettes);
   }

    float getAnger() {
      return this.Anger;
   }

    void setAnger(float var1) {
      this.Anger = var1;
   }

    float getBoredom() {
      return this.boredom;
   }

    void setBoredom(float var1) {
      this.boredom = var1;
   }

    float getEndurance() {
      return this.endurance;
   }

    void setEndurance(float var1) {
      this.endurance = var1;
   }

    float getEndurancelast() {
      return this.endurancelast;
   }

    void setEndurancelast(float var1) {
      this.endurancelast = var1;
   }

    float getEndurancedanger() {
      return this.endurancedanger;
   }

    void setEndurancedanger(float var1) {
      this.endurancedanger = var1;
   }

    float getEndurancewarn() {
      return this.endurancewarn;
   }

    void setEndurancewarn(float var1) {
      this.endurancewarn = var1;
   }

    bool getEnduranceRecharging() {
      return this.enduranceRecharging;
   }

    float getFatigue() {
      return this.fatigue;
   }

    void setFatigue(float var1) {
      this.fatigue = var1;
   }

    float getFitness() {
      return this.fitness;
   }

    void setFitness(float var1) {
      this.fitness = var1;
   }

    float getHunger() {
      return this.hunger;
   }

    void setHunger(float var1) {
      this.hunger = var1;
   }

    float getIdleboredom() {
      return this.idleboredom;
   }

    void setIdleboredom(float var1) {
      this.idleboredom = var1;
   }

    float getMorale() {
      return this.morale;
   }

    void setMorale(float var1) {
      this.morale = var1;
   }

    float getStress() {
      return this.stress + this.getStressFromCigarettes();
   }

    void setStress(float var1) {
      this.stress = var1;
   }

    float getStressFromCigarettes() {
      return this.stressFromCigarettes;
   }

    void setStressFromCigarettes(float var1) {
      this.stressFromCigarettes = PZMath.clamp(var1, 0.0F, this.getMaxStressFromCigarettes());
   }

    float getMaxStressFromCigarettes() {
      return 0.51F;
   }

    float getFear() {
      return this.Fear;
   }

    void setFear(float var1) {
      this.Fear = var1;
   }

    float getPanic() {
      return this.Panic;
   }

    void setPanic(float var1) {
      this.Panic = var1;
   }

    float getSanity() {
      return this.Sanity;
   }

    void setSanity(float var1) {
      this.Sanity = var1;
   }

    float getSickness() {
      return this.Sickness;
   }

    void setSickness(float var1) {
      this.Sickness = var1;
   }

    float getPain() {
      return this.Pain;
   }

    void setPain(float var1) {
      this.Pain = var1;
   }

    float getDrunkenness() {
      return this.Drunkenness;
   }

    void setDrunkenness(float var1) {
      this.Drunkenness = var1;
   }

    int getVisibleZombies() {
      return this.NumVisibleZombies;
   }

    void setNumVisibleZombies(int var1) {
      this.NumVisibleZombies = var1;
   }

    bool isTripping() {
      return this.Tripping;
   }

    void setTripping(bool var1) {
      this.Tripping = var1;
   }

    float getTrippingRotAngle() {
      return this.TrippingRotAngle;
   }

    void setTrippingRotAngle(float var1) {
      this.TrippingRotAngle = var1;
   }

    float getThirst() {
      return this.thirst;
   }

    void setThirst(float var1) {
      this.thirst = var1;
   }

    void resetStats() {
      this.Anger = 0.0F;
      this.boredom = 0.0F;
      this.fatigue = 0.0F;
      this.hunger = 0.0F;
      this.idleboredom = 0.0F;
      this.morale = 0.5F;
      this.stress = 0.0F;
      this.Fear = 0.0F;
      this.Panic = 0.0F;
      this.Sanity = 1.0F;
      this.Sickness = 0.0F;
      this.Boredom = 0.0F;
      this.Pain = 0.0F;
      this.Drunkenness = 0.0F;
      this.thirst = 0.0F;
   }
}
} // namespace characters
} // namespace zombie
