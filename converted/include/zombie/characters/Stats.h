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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


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
 return this->NumVisibleZombies;
 }

 int getNumChasingZombies() {
 return this->LastNumChasingZombies;
 }

 int getNumVeryCloseZombies() {
 return this->LastVeryCloseZombies;
 }

 void load(DataInputStream input) {
 this->Anger = input.readFloat();
 this->boredom = input.readFloat();
 this->endurance = input.readFloat();
 this->fatigue = input.readFloat();
 this->fitness = input.readFloat();
 this->hunger = input.readFloat();
 this->morale = input.readFloat();
 this->stress = input.readFloat();
 this->Fear = input.readFloat();
 this->Panic = input.readFloat();
 this->Sanity = input.readFloat();
 this->Sickness = input.readFloat();
 this->Boredom = input.readFloat();
 this->Pain = input.readFloat();
 this->Drunkenness = input.readFloat();
 this->thirst = input.readFloat();
 }

 void load(ByteBuffer input, int WorldVersion) {
 this->Anger = input.getFloat();
 this->boredom = input.getFloat();
 this->endurance = input.getFloat();
 this->fatigue = input.getFloat();
 this->fitness = input.getFloat();
 this->hunger = input.getFloat();
 this->morale = input.getFloat();
 this->stress = input.getFloat();
 this->Fear = input.getFloat();
 this->Panic = input.getFloat();
 this->Sanity = input.getFloat();
 this->Sickness = input.getFloat();
 this->Boredom = input.getFloat();
 this->Pain = input.getFloat();
 this->Drunkenness = input.getFloat();
 this->thirst = input.getFloat();
 if (WorldVersion >= 97) {
 this->stressFromCigarettes = input.getFloat();
 }
 }

 void save(DataOutputStream output) {
 output.writeFloat(this->Anger);
 output.writeFloat(this->boredom);
 output.writeFloat(this->endurance);
 output.writeFloat(this->fatigue);
 output.writeFloat(this->fitness);
 output.writeFloat(this->hunger);
 output.writeFloat(this->morale);
 output.writeFloat(this->stress);
 output.writeFloat(this->Fear);
 output.writeFloat(this->Panic);
 output.writeFloat(this->Sanity);
 output.writeFloat(this->Sickness);
 output.writeFloat(this->Boredom);
 output.writeFloat(this->Pain);
 output.writeFloat(this->Drunkenness);
 output.writeFloat(this->thirst);
 }

 void save(ByteBuffer output) {
 output.putFloat(this->Anger);
 output.putFloat(this->boredom);
 output.putFloat(this->endurance);
 output.putFloat(this->fatigue);
 output.putFloat(this->fitness);
 output.putFloat(this->hunger);
 output.putFloat(this->morale);
 output.putFloat(this->stress);
 output.putFloat(this->Fear);
 output.putFloat(this->Panic);
 output.putFloat(this->Sanity);
 output.putFloat(this->Sickness);
 output.putFloat(this->Boredom);
 output.putFloat(this->Pain);
 output.putFloat(this->Drunkenness);
 output.putFloat(this->thirst);
 output.putFloat(this->stressFromCigarettes);
 }

 /**
 * @return the Anger
 */
 float getAnger() {
 return this->Anger;
 }

 /**
 * 
 * @param _Anger the Anger to set
 */
 void setAnger(float _Anger) {
 this->Anger = _Anger;
 }

 /**
 * @return the boredom
 */
 float getBoredom() {
 return this->boredom;
 }

 /**
 * 
 * @param _boredom the boredom to set
 */
 void setBoredom(float _boredom) {
 this->boredom = _boredom;
 }

 /**
 * @return the endurance
 */
 float getEndurance() {
 return this->endurance;
 }

 /**
 * 
 * @param _endurance the endurance to set
 */
 void setEndurance(float _endurance) {
 this->endurance = _endurance;
 }

 /**
 * @return the endurancelast
 */
 float getEndurancelast() {
 return this->endurancelast;
 }

 /**
 * 
 * @param _endurancelast the endurancelast to set
 */
 void setEndurancelast(float _endurancelast) {
 this->endurancelast = _endurancelast;
 }

 /**
 * @return the endurancedanger
 */
 float getEndurancedanger() {
 return this->endurancedanger;
 }

 /**
 * 
 * @param _endurancedanger the endurancedanger to set
 */
 void setEndurancedanger(float _endurancedanger) {
 this->endurancedanger = _endurancedanger;
 }

 /**
 * @return the endurancewarn
 */
 float getEndurancewarn() {
 return this->endurancewarn;
 }

 /**
 * 
 * @param _endurancewarn the endurancewarn to set
 */
 void setEndurancewarn(float _endurancewarn) {
 this->endurancewarn = _endurancewarn;
 }

 bool getEnduranceRecharging() {
 return this->enduranceRecharging;
 }

 /**
 * @return the fatigue
 */
 float getFatigue() {
 return this->fatigue;
 }

 /**
 * 
 * @param _fatigue the fatigue to set
 */
 void setFatigue(float _fatigue) {
 this->fatigue = _fatigue;
 }

 /**
 * @return the fitness
 */
 float getFitness() {
 return this->fitness;
 }

 /**
 * 
 * @param _fitness the fitness to set
 */
 void setFitness(float _fitness) {
 this->fitness = _fitness;
 }

 /**
 * @return the hunger
 */
 float getHunger() {
 return this->hunger;
 }

 /**
 * 
 * @param _hunger the hunger to set
 */
 void setHunger(float _hunger) {
 this->hunger = _hunger;
 }

 /**
 * @return the idleboredom
 */
 float getIdleboredom() {
 return this->idleboredom;
 }

 /**
 * 
 * @param _idleboredom the idleboredom to set
 */
 void setIdleboredom(float _idleboredom) {
 this->idleboredom = _idleboredom;
 }

 /**
 * @return the morale
 */
 float getMorale() {
 return this->morale;
 }

 /**
 * 
 * @param _morale the morale to set
 */
 void setMorale(float _morale) {
 this->morale = _morale;
 }

 /**
 * @return the stress
 */
 float getStress() {
 return this->stress + this->getStressFromCigarettes();
 }

 /**
 * 
 * @param _stress the stress to set
 */
 void setStress(float _stress) {
 this->stress = _stress;
 }

 float getStressFromCigarettes() {
 return this->stressFromCigarettes;
 }

 void setStressFromCigarettes(float _stressFromCigarettes) {
 this->stressFromCigarettes = PZMath.clamp(_stressFromCigarettes, 0.0F, this->getMaxStressFromCigarettes());
 }

 float getMaxStressFromCigarettes() {
 return 0.51F;
 }

 /**
 * @return the Fear
 */
 float getFear() {
 return this->Fear;
 }

 /**
 * 
 * @param _Fear the Fear to set
 */
 void setFear(float _Fear) {
 this->Fear = _Fear;
 }

 /**
 * @return the Panic
 */
 float getPanic() {
 return this->Panic;
 }

 /**
 * 
 * @param _Panic the Panic to set
 */
 void setPanic(float _Panic) {
 this->Panic = _Panic;
 }

 /**
 * @return the Sanity
 */
 float getSanity() {
 return this->Sanity;
 }

 /**
 * 
 * @param _Sanity the Sanity to set
 */
 void setSanity(float _Sanity) {
 this->Sanity = _Sanity;
 }

 /**
 * @return the Sickness
 */
 float getSickness() {
 return this->Sickness;
 }

 /**
 * 
 * @param _Sickness the Sickness to set
 */
 void setSickness(float _Sickness) {
 this->Sickness = _Sickness;
 }

 /**
 * @return the Pain
 */
 float getPain() {
 return this->Pain;
 }

 /**
 * 
 * @param _Pain the Pain to set
 */
 void setPain(float _Pain) {
 this->Pain = _Pain;
 }

 /**
 * @return the Drunkenness
 */
 float getDrunkenness() {
 return this->Drunkenness;
 }

 /**
 * 
 * @param _Drunkenness the Drunkenness to set
 */
 void setDrunkenness(float _Drunkenness) {
 this->Drunkenness = _Drunkenness;
 }

 /**
 * @return the NumVisibleZombies
 */
 int getVisibleZombies() {
 return this->NumVisibleZombies;
 }

 /**
 * 
 * @param _NumVisibleZombies the NumVisibleZombies to set
 */
 void setNumVisibleZombies(int _NumVisibleZombies) {
 this->NumVisibleZombies = _NumVisibleZombies;
 }

 /**
 * @return the Tripping
 */
 bool isTripping() {
 return this->Tripping;
 }

 /**
 * 
 * @param _Tripping the Tripping to set
 */
 void setTripping(bool _Tripping) {
 this->Tripping = _Tripping;
 }

 /**
 * @return the TrippingRotAngle
 */
 float getTrippingRotAngle() {
 return this->TrippingRotAngle;
 }

 /**
 * 
 * @param _TrippingRotAngle the TrippingRotAngle to set
 */
 void setTrippingRotAngle(float _TrippingRotAngle) {
 this->TrippingRotAngle = _TrippingRotAngle;
 }

 /**
 * @return the thirst
 */
 float getThirst() {
 return this->thirst;
 }

 /**
 * 
 * @param _thirst the thirst to set
 */
 void setThirst(float _thirst) {
 this->thirst = _thirst;
 }

 void resetStats() {
 this->Anger = 0.0F;
 this->boredom = 0.0F;
 this->fatigue = 0.0F;
 this->hunger = 0.0F;
 this->idleboredom = 0.0F;
 this->morale = 0.5F;
 this->stress = 0.0F;
 this->Fear = 0.0F;
 this->Panic = 0.0F;
 this->Sanity = 1.0F;
 this->Sickness = 0.0F;
 this->Boredom = 0.0F;
 this->Pain = 0.0F;
 this->Drunkenness = 0.0F;
 this->thirst = 0.0F;
 }
}
} // namespace characters
} // namespace zombie
