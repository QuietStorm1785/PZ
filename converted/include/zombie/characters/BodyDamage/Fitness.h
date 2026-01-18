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
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/core/Rand.h"
#include <algorithm>
#include <filesystem>
#include <iterator>

namespace zombie {
namespace characters {
namespace BodyDamage {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Fitness {
public:
 IsoGameCharacter parent = nullptr;
 private HashMap<String, Float> regularityMap = std::make_unique<HashMap<>>();
 int fitnessLvl = 0;
 int strLvl = 0;
 private HashMap<String, Integer> stiffnessTimerMap = std::make_unique<HashMap<>>();
 private HashMap<String, Float> stiffnessIncMap = std::make_unique<HashMap<>>();
 private ArrayList<String> bodypartToIncStiffness = std::make_unique<ArrayList<>>();
 private HashMap<String, Fitness.FitnessExercise> exercises = std::make_unique<HashMap<>>();
 private HashMap<String, Long> exeTimer = std::make_unique<HashMap<>>();
 int lastUpdate = -1;
 private Fitness.FitnessExercise currentExe;
 static const int HOURS_FOR_STIFFNESS = 12;
 static const float BASE_STIFFNESS_INC = 0.5F;
 static const float BASE_ENDURANCE_RED = 0.015F;
 static const float BASE_REGULARITY_INC = 0.08F;
 static const float BASE_REGULARITY_DEC = 0.002F;
 static const float BASE_PAIN_INC = 2.5F;

 public Fitness(IsoGameCharacter _parent) {
 this->setParent(_parent);
 }

 /**
 * We update every 10 in game minutes to facilitate calculs
 */
 void update() {
 int int0 = GameTime.getInstance().getMinutes() / 10;
 if (this->lastUpdate == -1) {
 this->lastUpdate = int0;
 }

 if (int0 != this->lastUpdate) {
 this->lastUpdate = int0;
 std::vector arrayList = new ArrayList();
 this->decreaseRegularity();

 for (String string0 : this->stiffnessTimerMap.keySet()) {
 int integer = this->stiffnessTimerMap.get(string0);
 integer = integer - 1;
 if (integer <= 0) {
 arrayList.add(string0);
 this->bodypartToIncStiffness.add(string0);
 } else {
 this->stiffnessTimerMap.put(string0, integer);
 }
 }

 for (int int1 = 0; int1 < arrayList.size(); int1++) {
 this->stiffnessTimerMap.remove(arrayList.get(int1);
 }

 for (int int2 = 0; int2 < this->bodypartToIncStiffness.size(); int2++) {
 std::string string1 = this->bodypartToIncStiffness.get(int2);
 float float0 = this->stiffnessIncMap.get(string1);
 if (float0 == nullptr) {
 return;
 }

 float0 = float0 - 1.0F;
 this->increasePain(string1);
 if (float0 <= 0.0F) {
 this->bodypartToIncStiffness.remove(int2);
 this->stiffnessIncMap.remove(string1);
 int2--;
 } else {
 this->stiffnessIncMap.put(string1, float0);
 }
 }
 }
 }

 void decreaseRegularity() {
 for (String string : this->regularityMap.keySet()) {
 if (this->exeTimer.containsKey(string) && GameTime.getInstance().getCalender().getTimeInMillis() - this->exeTimer.get(string) > 86400000L) {
 float float0 = this->regularityMap.get(string);
 float0 -= 0.002F;
 this->regularityMap.put(string, float0);
 }
 }
 }

 void increasePain(const std::string& string) {
 if ("arms" == string) {
 for (int int0 = BodyPartType.ForeArm_L.index(); int0 < BodyPartType.UpperArm_R.index() + 1; int0++) {
 BodyPart bodyPart0 = this->parent.getBodyDamage().getBodyPart(BodyPartType.FromIndex(int0);
 bodyPart0.setStiffness(bodyPart0.getStiffness() + 2.5F);
 }
 }

 if ("legs" == string) {
 for (int int1 = BodyPartType.UpperLeg_L.index(); int1 < BodyPartType.LowerLeg_R.index() + 1; int1++) {
 BodyPart bodyPart1 = this->parent.getBodyDamage().getBodyPart(BodyPartType.FromIndex(int1);
 bodyPart1.setStiffness(bodyPart1.getStiffness() + 2.5F);
 }
 }

 if ("chest" == string) {
 BodyPart bodyPart2 = this->parent.getBodyDamage().getBodyPart(BodyPartType.Torso_Upper);
 bodyPart2.setStiffness(bodyPart2.getStiffness() + 2.5F);
 }

 if ("abs" == string) {
 BodyPart bodyPart3 = this->parent.getBodyDamage().getBodyPart(BodyPartType.Torso_Lower);
 bodyPart3.setStiffness(bodyPart3.getStiffness() + 2.5F);
 }
 }

 void setCurrentExercise(const std::string& type) {
 this->currentExe = this->exercises.get(type);
 }

 void exerciseRepeat() {
 this->fitnessLvl = this->parent.getPerkLevel(PerkFactory.Perks.Fitness);
 this->strLvl = this->parent.getPerkLevel(PerkFactory.Perks.Strength);
 this->incRegularity();
 this->reduceEndurance();
 this->incFutureStiffness();
 this->incStats();
 this->updateExeTimer();
 }

 void updateExeTimer() {
 this->exeTimer.put(this->currentExe.type, GameTime.getInstance().getCalender().getTimeInMillis());
 }

 /**
 * Increase the regularity when you've done a repeat of an exercice Depend on fitness (using logarithm), the more fitness, the LESS regularity you get Regularity will influence on the stiffness you get once you've finished an exercise
 */
 void incRegularity() {
 float float0 = 0.08F;
 uint8_t byte0 = 4;
 double double0 = Math.log(this->fitnessLvl / 5.0F + byte0);
 float0 = (float)(float0 * (Math.log(byte0 + 1) / double0);
 float float1 = this->regularityMap.get(this->currentExe.type);
 if (float1 == nullptr) {
 float1 = 0.0F;
 }

 float1 = float1 + float0;
 float1 = Math.min(Math.max(float1, 0.0F), 100.0F);
 this->regularityMap.put(this->currentExe.type, float1);
 }

 /**
 * Reduce endurance, using metabolics (to know what kind of exercise it is, some are more exhausting than others), regularity, current carrying weight.
 */
 void reduceEndurance() {
 float float0 = 0.015F;
 float float1 = this->regularityMap.get(this->currentExe.type);
 if (float1 == nullptr) {
 float1 = 0.0F;
 }

 uint8_t byte0 = 50;
 double double0 = Math.log(float1 / 50.0F + byte0);
 float0 = (float)(float0 * (double0 / Math.log(byte0 + 1);
 if (this->currentExe.metabolics == Metabolics.FitnessHeavy) {
 float0 *= 1.3F;
 }

 float0 *= 1 + this->parent.getMoodles().getMoodleLevel(MoodleType.HeavyLoad) / 3;
 this->parent.getStats().setEndurance(this->parent.getStats().getEndurance() - float0);
 }

 /**
 * We setup a timer after finishing an exercice, 12h after, we gonna start to increase stiffness (add pains in muscles) When adding the stiffness, we decrease slowly our vars while increasing pain, untill no more stiffness is to be added. Stiffness induced will depend on regularity, fatigue. Numbers approx: At 0 regularity, 60min exercises should gives almost 4h of stiffness (gets additional pain)
 */
 void incFutureStiffness() {
 float float0 = this->regularityMap.get(this->currentExe.type);
 if (float0 == nullptr) {
 float0 = 0.0F;
 }

 for (int int0 = 0; int0 < this->currentExe.stiffnessInc.size(); int0++) {
 float float1 = 0.5F;
 std::string string = this->currentExe.stiffnessInc.get(int0);
 if (!this->stiffnessTimerMap.containsKey(string) && !this->bodypartToIncStiffness.contains(string) {
 this->stiffnessTimerMap.put(string, 72);
 }

 float float2 = this->stiffnessIncMap.get(string);
 if (float2 == nullptr) {
 float2 = 0.0F;
 }

 float1 *= (120.0F - float0) / 170.0F;
 if (this->currentExe.metabolics == Metabolics.FitnessHeavy) {
 float1 *= 1.3F;
 }

 float1 *= 1 + this->parent.getMoodles().getMoodleLevel(MoodleType.Tired) / 3;
 float2 = float2 + float1;
 float2 = Math.min(float2, 150.0F);
 this->stiffnessIncMap.put(string, float2);
 }
 }

 void incStats() {
 float float0 = 0.0F;
 float float1 = 0.0F;

 for (int int0 = 0; int0 < this->currentExe.stiffnessInc.size(); int0++) {
 std::string string = this->currentExe.stiffnessInc.get(int0);
 if ("arms" == string) {
 float0 += 4.0F;
 }

 if ("chest" == string) {
 float0 += 2.0F;
 }

 if ("legs" == string) {
 float1 += 4.0F;
 }

 if ("abs" == string) {
 float1 += 2.0F;
 }
 }

 if (this->strLvl > 5) {
 float0 *= 1 + (this->strLvl - 5) / 10;
 }

 if (this->fitnessLvl > 5) {
 float1 *= 1 + (this->fitnessLvl - 5) / 10;
 }

 float0 *= this->currentExe.xpModifier;
 float1 *= this->currentExe.xpModifier;
 this->parent.getXp().AddXP(PerkFactory.Perks.Strength, float0);
 this->parent.getXp().AddXP(PerkFactory.Perks.Fitness, float1);
 }

 void resetValues() {
 this->stiffnessIncMap.clear();
 this->stiffnessTimerMap.clear();
 this->regularityMap.clear();
 }

 void removeStiffnessValue(const std::string& type) {
 this->stiffnessIncMap.remove(type);
 this->stiffnessTimerMap.remove(type);
 }

 void save(ByteBuffer output) {
 output.putInt(this->stiffnessIncMap.size());

 for (String string0 : this->stiffnessIncMap.keySet()) {
 GameWindow.WriteString(output, string0);
 output.putFloat(this->stiffnessIncMap.get(string0);
 }

 output.putInt(this->stiffnessTimerMap.size());

 for (String string1 : this->stiffnessTimerMap.keySet()) {
 GameWindow.WriteString(output, string1);
 output.putInt(this->stiffnessTimerMap.get(string1);
 }

 output.putInt(this->regularityMap.size());

 for (String string2 : this->regularityMap.keySet()) {
 GameWindow.WriteString(output, string2);
 output.putFloat(this->regularityMap.get(string2);
 }

 output.putInt(this->bodypartToIncStiffness.size());

 for (int int0 = 0; int0 < this->bodypartToIncStiffness.size(); int0++) {
 GameWindow.WriteString(output, this->bodypartToIncStiffness.get(int0);
 }

 output.putInt(this->exeTimer.size());

 for (String string3 : this->exeTimer.keySet()) {
 GameWindow.WriteString(output, string3);
 output.putLong(this->exeTimer.get(string3);
 }
 }

 void load(ByteBuffer input, int WorldVersion) {
 if (WorldVersion >= 167) {
 int int0 = input.getInt();
 if (int0 > 0) {
 for (int int1 = 0; int1 < int0; int1++) {
 this->stiffnessIncMap.put(GameWindow.ReadString(input), input.getFloat());
 }
 }

 int0 = input.getInt();
 if (int0 > 0) {
 for (int int2 = 0; int2 < int0; int2++) {
 this->stiffnessTimerMap.put(GameWindow.ReadString(input), input.getInt());
 }
 }

 int0 = input.getInt();
 if (int0 > 0) {
 for (int int3 = 0; int3 < int0; int3++) {
 this->regularityMap.put(GameWindow.ReadString(input), input.getFloat());
 }
 }

 int0 = input.getInt();
 if (int0 > 0) {
 for (int int4 = 0; int4 < int0; int4++) {
 this->bodypartToIncStiffness.add(GameWindow.ReadString(input);
 }
 }

 if (WorldVersion >= 169) {
 int0 = input.getInt();
 if (int0 > 0) {
 for (int int5 = 0; int5 < int0; int5++) {
 this->exeTimer.put(GameWindow.ReadString(input), input.getLong());
 }
 }
 }
 }
 }

 bool onGoingStiffness() {
 return !this->bodypartToIncStiffness.empty();
 }

 int getCurrentExeStiffnessTimer(const std::string& type) {
 type = type.split(",")[0];
 return this->stiffnessTimerMap.get(type) != nullptr ? this->stiffnessTimerMap.get(type) : 0;
 }

 float getCurrentExeStiffnessInc(const std::string& type) {
 type = type.split(",")[0];
 return this->stiffnessIncMap.get(type) != nullptr ? this->stiffnessIncMap.get(type) : 0.0F;
 }

 IsoGameCharacter getParent() {
 return this->parent;
 }

 void setParent(IsoGameCharacter _parent) {
 this->parent = _parent;
 }

 float getRegularity(const std::string& type) {
 float float0 = this->regularityMap.get(type);
 if (float0 == nullptr) {
 float0 = 0.0F;
 }

 return float0;
 }

 public HashMap<String, Float> getRegularityMap() {
 return this->regularityMap;
 }

 void setRegularityMap(Float> _regularityMap) {
 this->regularityMap = _regularityMap;
 }

 void init() {
 if (this->exercises.empty()) {
 KahluaTableImpl kahluaTableImpl0 = (KahluaTableImpl)LuaManager.env.rawget("FitnessExercises");
 KahluaTableImpl kahluaTableImpl1 = (KahluaTableImpl)kahluaTableImpl0.rawget("exercisesType");

 for (Entry entry : kahluaTableImpl1.delegate.entrySet()) {
 this->exercises.put((String)entry.getKey(), new Fitness.FitnessExercise((KahluaTableImpl)entry.getValue()));
 }

 this->initRegularityMapProfession();
 }
 }

 void initRegularityMapProfession() {
 if (this->regularityMap.empty()) {
 bool boolean0 = false;
 bool boolean1 = false;
 bool boolean2 = false;
 if (this->parent.getDescriptor().getProfession() == "fitnessInstructor")) {
 boolean1 = true;
 }

 if (this->parent.getDescriptor().getProfession() == "fireofficer")) {
 boolean0 = true;
 }

 if (this->parent.getDescriptor().getProfession() == "securityguard")) {
 boolean2 = true;
 }

 if (boolean0 || boolean1 || boolean2) {
 Iterator iterator = this->exercises.keySet().iterator();

 while (iterator.hasNext()) {
 float float0 = Rand.Next(7, 12);
 if (boolean0) {
 float0 = Rand.Next(10, 20);
 }

 if (boolean1) {
 float0 = Rand.Next(40, 60);
 }

 this->regularityMap.put((String)iterator.next(), float0);
 }
 }
 }
 }

 public static class FitnessExercise {
 std::string type = nullptr;
 Metabolics metabolics = nullptr;
 ArrayList<String> stiffnessInc = nullptr;
 float xpModifier = 1.0F;

 public FitnessExercise(KahluaTableImpl exeDatas) {
 this->type = exeDatas.rawgetStr("type");
 this->metabolics = (Metabolics)exeDatas.rawget("metabolics");
 this->stiffnessInc = new ArrayList<>(Arrays.asList(exeDatas.rawgetStr("stiffness").split(",")));
 if (exeDatas.rawgetFloat("xpMod") > 0.0F) {
 this->xpModifier = exeDatas.rawgetFloat("xpMod");
 }
 }
 }
}
} // namespace BodyDamage
} // namespace characters
} // namespace zombie
