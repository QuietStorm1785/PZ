#pragma once
#include "zombie/characters/BodyDamage/Thermoregulator.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Color.h"
#include "zombie/iso/weather/Temperature.h"
#include "zombie/ui/MoodlesUI.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
namespace Moodles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Moodle {
public:
 MoodleType Type;
 int Level;
 IsoGameCharacter Parent;
 int painTimer = 0;
 Color chevronColor = Color.white;
 bool chevronIsUp = true;
 int chevronCount = 0;
 int chevronMax = 0;
 static Color colorNeg = new Color(0.88235295F, 0.15686275F, 0.15686275F);
 static Color colorPos = new Color(0.15686275F, 0.88235295F, 0.15686275F);
 int cantSprintTimer = 300;

public
 Moodle(MoodleType ChosenType, IsoGameCharacter parent) {
 this(ChosenType, parent, 0);
 }

public
 Moodle(MoodleType ChosenType, IsoGameCharacter parent, int maxChevrons) {
 this->Parent = parent;
 this->Type = ChosenType;
 this->Level = 0;
 this->chevronMax = maxChevrons;
 }

 int getChevronCount() { return this->chevronCount; }

 bool isChevronIsUp() { return this->chevronIsUp; }

 Color getChevronColor() { return this->chevronColor; }

 bool chevronDifference(int count, bool isup, Color col) {
 return count != this->chevronCount || isup != this->chevronIsUp ||
 col != this->chevronColor;
 }

 void setChevron(int count, bool isup, Color col) {
 if (count < 0) {
 count = 0;
 }

 if (count > this->chevronMax) {
 count = this->chevronMax;
 }

 this->chevronCount = count;
 this->chevronIsUp = isup;
 this->chevronColor = col != nullptr ? col : Color.white;
 }

 int getLevel() { return this->Level; }

 void SetLevel(int val) {
 if (val < 0) {
 val = 0;
 }

 if (val > 4) {
 val = 4;
 }

 this->Level = val;
 }

 bool Update() {
 bool boolean0 = false;
 if (this->Parent.isDead()) {
 uint8_t byte0 = 0;
 if (this->Type != MoodleType.Dead && this->Type != MoodleType.Zombie) {
 byte0 = 0;
 if (byte0 != this->getLevel()) {
 this->SetLevel(byte0);
 boolean0 = true;
 }

 return boolean0;
 }
 }

 if (this->Type == MoodleType.CantSprint) {
 uint8_t byte1 = 0;
 if (((IsoPlayer)this->Parent).MoodleCantSprint) {
 byte1 = 1;
 this->cantSprintTimer--;
 MoodlesUI.getInstance().wiggle(MoodleType.CantSprint);
 if (this->cantSprintTimer == 0) {
 byte1 = 0;
 this->cantSprintTimer = 300;
 ((IsoPlayer)this->Parent).MoodleCantSprint = false;
 }
 }

 if (byte1 != this->getLevel()) {
 this->SetLevel(byte1);
 boolean0 = true;
 }
 }

 if (this->Type == MoodleType.Endurance) {
 uint8_t byte2 = 0;
 if (this->Parent.getBodyDamage().getHealth() != 0.0F) {
 if (this->Parent.getStats().endurance > 0.75F) {
 byte2 = 0;
 } else if (this->Parent.getStats().endurance > 0.5F) {
 byte2 = 1;
 } else if (this->Parent.getStats().endurance > 0.25F) {
 byte2 = 2;
 } else if (this->Parent.getStats().endurance > 0.1F) {
 byte2 = 3;
 } else {
 byte2 = 4;
 }
 }

 if (byte2 != this->getLevel()) {
 this->SetLevel(byte2);
 boolean0 = true;
 }
 }

 if (this->Type == MoodleType.Angry) {
 uint8_t byte3 = 0;
 if (this->Parent.getStats().Anger > 0.75F) {
 byte3 = 4;
 } else if (this->Parent.getStats().Anger > 0.5F) {
 byte3 = 3;
 } else if (this->Parent.getStats().Anger > 0.25F) {
 byte3 = 2;
 } else if (this->Parent.getStats().Anger > 0.1F) {
 byte3 = 1;
 }

 if (byte3 != this->getLevel()) {
 this->SetLevel(byte3);
 boolean0 = true;
 }
 }

 if (this->Type == MoodleType.Tired) {
 uint8_t byte4 = 0;
 if (this->Parent.getBodyDamage().getHealth() != 0.0F) {
 if (this->Parent.getStats().fatigue > 0.6F) {
 byte4 = 1;
 }

 if (this->Parent.getStats().fatigue > 0.7F) {
 byte4 = 2;
 }

 if (this->Parent.getStats().fatigue > 0.8F) {
 byte4 = 3;
 }

 if (this->Parent.getStats().fatigue > 0.9F) {
 byte4 = 4;
 }
 }

 if (byte4 != this->getLevel()) {
 this->SetLevel(byte4);
 boolean0 = true;
 }
 }

 if (this->Type == MoodleType.Hungry) {
 uint8_t byte5 = 0;
 if (this->Parent.getBodyDamage().getHealth() != 0.0F) {
 if (this->Parent.getStats().hunger > 0.15F) {
 byte5 = 1;
 }

 if (this->Parent.getStats().hunger > 0.25F) {
 byte5 = 2;
 }

 if (this->Parent.getStats().hunger > 0.45F) {
 byte5 = 3;
 }

 if (this->Parent.getStats().hunger > 0.7F) {
 byte5 = 4;
 }
 }

 if (byte5 != this->getLevel()) {
 this->SetLevel(byte5);
 boolean0 = true;
 }
 }

 if (this->Type == MoodleType.Panic) {
 uint8_t byte6 = 0;
 if (this->Parent.getBodyDamage().getHealth() != 0.0F) {
 if (this->Parent.getStats().Panic > 6.0F) {
 byte6 = 1;
 }

 if (this->Parent.getStats().Panic > 30.0F) {
 byte6 = 2;
 }

 if (this->Parent.getStats().Panic > 65.0F) {
 byte6 = 3;
 }

 if (this->Parent.getStats().Panic > 80.0F) {
 byte6 = 4;
 }
 }

 if (byte6 != this->getLevel()) {
 this->SetLevel(byte6);
 boolean0 = true;
 }
 }

 if (this->Type == MoodleType.Sick) {
 uint8_t byte7 = 0;
 if (this->Parent.getBodyDamage().getHealth() != 0.0F) {
 this->Parent.getStats().Sickness =
 this->Parent.getBodyDamage().getApparentInfectionLevel() / 100.0F;
 if (this->Parent.getStats().Sickness > 0.25F) {
 byte7 = 1;
 }

 if (this->Parent.getStats().Sickness > 0.5F) {
 byte7 = 2;
 }

 if (this->Parent.getStats().Sickness > 0.75F) {
 byte7 = 3;
 }

 if (this->Parent.getStats().Sickness > 0.9F) {
 byte7 = 4;
 }
 }

 if (byte7 != this->getLevel()) {
 this->SetLevel(byte7);
 boolean0 = true;
 }
 }

 if (this->Type == MoodleType.Bored) {
 uint8_t byte8 = 0;
 if (this->Parent.getBodyDamage().getHealth() != 0.0F) {
 this->Parent.getStats().Boredom =
 this->Parent.getBodyDamage().getBoredomLevel() / 100.0F;
 if (this->Parent.getStats().Boredom > 0.25F) {
 byte8 = 1;
 }

 if (this->Parent.getStats().Boredom > 0.5F) {
 byte8 = 2;
 }

 if (this->Parent.getStats().Boredom > 0.75F) {
 byte8 = 3;
 }

 if (this->Parent.getStats().Boredom > 0.9F) {
 byte8 = 4;
 }
 }

 if (byte8 != this->getLevel()) {
 this->SetLevel(byte8);
 boolean0 = true;
 }
 }

 if (this->Type == MoodleType.Unhappy) {
 uint8_t byte9 = 0;
 if (this->Parent.getBodyDamage().getHealth() != 0.0F) {
 if (this->Parent.getBodyDamage().getUnhappynessLevel() > 20.0F) {
 byte9 = 1;
 }

 if (this->Parent.getBodyDamage().getUnhappynessLevel() > 45.0F) {
 byte9 = 2;
 }

 if (this->Parent.getBodyDamage().getUnhappynessLevel() > 60.0F) {
 byte9 = 3;
 }

 if (this->Parent.getBodyDamage().getUnhappynessLevel() > 80.0F) {
 byte9 = 4;
 }
 }

 if (byte9 != this->getLevel()) {
 this->SetLevel(byte9);
 boolean0 = true;
 }
 }

 if (this->Type == MoodleType.Stress) {
 uint8_t byte10 = 0;
 if (this->Parent.getStats().getStress() > 0.9F) {
 byte10 = 4;
 } else if (this->Parent.getStats().getStress() > 0.75F) {
 byte10 = 3;
 } else if (this->Parent.getStats().getStress() > 0.5F) {
 byte10 = 2;
 } else if (this->Parent.getStats().getStress() > 0.25F) {
 byte10 = 1;
 }

 if (byte10 != this->getLevel()) {
 this->SetLevel(byte10);
 boolean0 = true;
 }
 }

 if (this->Type == MoodleType.Thirst) {
 uint8_t byte11 = 0;
 if (this->Parent.getStats().thirst > 0.12F) {
 byte11 = 1;
 }

 if (this->Parent.getStats().thirst > 0.25F) {
 byte11 = 2;
 }

 if (this->Parent.getStats().thirst > 0.7F) {
 byte11 = 3;
 }

 if (this->Parent.getStats().thirst > 0.84F) {
 byte11 = 4;
 }

 if (byte11 != this->getLevel()) {
 this->SetLevel(byte11);
 boolean0 = true;
 }
 }

 if (this->Type == MoodleType.Bleeding) {
 int int0 = 0;
 if (this->Parent.getBodyDamage().getHealth() != 0.0F) {
 int0 = this->Parent.getBodyDamage().getNumPartsBleeding();
 if (int0 > 4) {
 int0 = 4;
 }
 }

 if (int0 != this->getLevel()) {
 this->SetLevel(int0);
 boolean0 = true;
 }
 }

 if (this->Type == MoodleType.Wet) {
 uint8_t byte12 = 0;
 if (this->Parent.getBodyDamage().getHealth() != 0.0F) {
 if (this->Parent.getBodyDamage().getWetness() > 15.0F) {
 byte12 = 1;
 }

 if (this->Parent.getBodyDamage().getWetness() > 40.0F) {
 byte12 = 2;
 }

 if (this->Parent.getBodyDamage().getWetness() > 70.0F) {
 byte12 = 3;
 }

 if (this->Parent.getBodyDamage().getWetness() > 90.0F) {
 byte12 = 4;
 }
 }

 if (byte12 != this->getLevel()) {
 this->SetLevel(byte12);
 boolean0 = true;
 }
 }

 if (this->Type == MoodleType.HasACold) {
 uint8_t byte13 = 0;
 if (this->Parent.getBodyDamage().getHealth() != 0.0F) {
 if (this->Parent.getBodyDamage().getColdStrength() > 20.0F) {
 byte13 = 1;
 }

 if (this->Parent.getBodyDamage().getColdStrength() > 40.0F) {
 byte13 = 2;
 }

 if (this->Parent.getBodyDamage().getColdStrength() > 60.0F) {
 byte13 = 3;
 }

 if (this->Parent.getBodyDamage().getColdStrength() > 75.0F) {
 byte13 = 4;
 }
 }

 if (byte13 != this->getLevel()) {
 this->SetLevel(byte13);
 boolean0 = true;
 }
 }

 if (this->Type == MoodleType.Injured) {
 uint8_t byte14 = 0;
 if (this->Parent.getBodyDamage().getHealth() != 0.0F) {
 if (100.0F - this->Parent.getBodyDamage().getHealth() > 20.0F) {
 byte14 = 1;
 }

 if (100.0F - this->Parent.getBodyDamage().getHealth() > 40.0F) {
 byte14 = 2;
 }

 if (100.0F - this->Parent.getBodyDamage().getHealth() > 60.0F) {
 byte14 = 3;
 }

 if (100.0F - this->Parent.getBodyDamage().getHealth() > 75.0F) {
 byte14 = 4;
 }
 }

 if (byte14 != this->getLevel()) {
 this->SetLevel(byte14);
 boolean0 = true;
 }
 }

 if (this->Type == MoodleType.Pain) {
 this->painTimer++;
 if (this->painTimer < 120) {
 return false;
 }

 this->painTimer = 0;
 uint8_t byte15 = 0;
 if (this->Parent.getBodyDamage().getHealth() != 0.0F) {
 if (this->Parent.getStats().Pain > 10.0F) {
 byte15 = 1;
 }

 if (this->Parent.getStats().Pain > 20.0F) {
 byte15 = 2;
 }

 if (this->Parent.getStats().Pain > 50.0F) {
 byte15 = 3;
 }

 if (this->Parent.getStats().Pain > 75.0F) {
 byte15 = 4;
 }
 }

 if (byte15 != this->getLevel()) {
 this->SetLevel(byte15);
 boolean0 = true;
 }
 }

 if (this->Type == MoodleType.HeavyLoad) {
 uint8_t byte16 = 0;
 float float0 = this->Parent.getInventory().getCapacityWeight();
 float float1 = this->Parent.getMaxWeight();
 float float2 = float0 / float1;
 if (this->Parent.getBodyDamage().getHealth() != 0.0F) {
 if (float2 >= 1.75) {
 byte16 = 4;
 } else if (float2 >= 1.5) {
 byte16 = 3;
 } else if (float2 >= 1.25) {
 byte16 = 2;
 } else if (float2 > 1.0F) {
 byte16 = 1;
 }
 }

 if (byte16 != this->getLevel()) {
 this->SetLevel(byte16);
 boolean0 = true;
 }
 }

 if (this->Type == MoodleType.Drunk) {
 uint8_t byte17 = 0;
 if (this->Parent.getBodyDamage().getHealth() != 0.0F) {
 if (this->Parent.getStats().Drunkenness > 10.0F) {
 byte17 = 1;
 }

 if (this->Parent.getStats().Drunkenness > 30.0F) {
 byte17 = 2;
 }

 if (this->Parent.getStats().Drunkenness > 50.0F) {
 byte17 = 3;
 }

 if (this->Parent.getStats().Drunkenness > 70.0F) {
 byte17 = 4;
 }
 }

 if (byte17 != this->getLevel()) {
 this->SetLevel(byte17);
 boolean0 = true;
 }
 }

 if (this->Type == MoodleType.Dead) {
 uint8_t byte18 = 0;
 if (this->Parent.isDead()) {
 byte18 = 4;
 if (!this->Parent.getBodyDamage().IsFakeInfected() &&
 this->Parent.getBodyDamage().getInfectionLevel() >= 0.001F) {
 byte18 = 0;
 }
 }

 if (byte18 != this->getLevel()) {
 this->SetLevel(byte18);
 boolean0 = true;
 }
 }

 if (this->Type == MoodleType.Zombie) {
 uint8_t byte19 = 0;
 if (this->Parent.isDead() &&
 !this->Parent.getBodyDamage().IsFakeInfected() &&
 this->Parent.getBodyDamage().getInfectionLevel() >= 0.001F) {
 byte19 = 4;
 }

 if (byte19 != this->getLevel()) {
 this->SetLevel(byte19);
 boolean0 = true;
 }
 }

 if (this->Type == MoodleType.FoodEaten) {
 uint8_t byte20 = 0;
 if (this->Parent.getBodyDamage().getHealth() != 0.0F) {
 if (this->Parent.getBodyDamage().getHealthFromFoodTimer() > 0.0F) {
 byte20 = 1;
 }

 if (this->Parent.getBodyDamage().getHealthFromFoodTimer() >
 this->Parent.getBodyDamage().getStandardHealthFromFoodTime()) {
 byte20 = 2;
 }

 if (this->Parent.getBodyDamage().getHealthFromFoodTimer() >
 this->Parent.getBodyDamage().getStandardHealthFromFoodTime() *
 2.0F) {
 byte20 = 3;
 }

 if (this->Parent.getBodyDamage().getHealthFromFoodTimer() >
 this->Parent.getBodyDamage().getStandardHealthFromFoodTime() *
 3.0F) {
 byte20 = 4;
 }
 }

 if (byte20 != this->getLevel()) {
 this->SetLevel(byte20);
 boolean0 = true;
 }
 }

 int int1 = this->chevronCount;
 bool boolean1 = this->chevronIsUp;
 Color color = this->chevronColor;
 if ((this->Type == MoodleType.Hyperthermia ||
 this->Type == MoodleType.Hypothermia) &&
 this->Parent instanceof
 IsoPlayer) {
 if (!(this->Parent.getBodyDamage().getTemperature() < 36.5F) &&
 !(this->Parent.getBodyDamage().getTemperature() > 37.5F) {
 int1 = 0;
 } else {
 Thermoregulator thermoregulator =
 this->Parent.getBodyDamage().getThermoregulator();
 if (thermoregulator.empty()) {
 int1 = 0;
 } else {
 boolean1 = thermoregulator.thermalChevronUp();
 int1 = thermoregulator.thermalChevronCount();
 }
 }
 }

 if (this->Type == MoodleType.Hyperthermia) {
 uint8_t byte21 = 0;
 if (int1 > 0) {
 color = boolean1 ? colorNeg : colorPos;
 }

 if (this->Parent.getBodyDamage().getTemperature() != 0.0F) {
 if (this->Parent.getBodyDamage().getTemperature() > 37.5F) {
 byte21 = 1;
 }

 if (this->Parent.getBodyDamage().getTemperature() > 39.0F) {
 byte21 = 2;
 }

 if (this->Parent.getBodyDamage().getTemperature() > 40.0F) {
 byte21 = 3;
 }

 if (this->Parent.getBodyDamage().getTemperature() > 41.0F) {
 byte21 = 4;
 }
 }

 if (byte21 != this->getLevel() ||
 byte21 > 0 && this->chevronDifference(int1, boolean1, color) {
 this->SetLevel(byte21);
 this->setChevron(int1, boolean1, color);
 boolean0 = true;
 }
 }

 if (this->Type == MoodleType.Hypothermia) {
 uint8_t byte22 = 0;
 if (int1 > 0) {
 color = boolean1 ? colorPos : colorNeg;
 }

 if (this->Parent.getBodyDamage().getTemperature() != 0.0F) {
 if (this->Parent.getBodyDamage().getTemperature() < 36.5F &&
 this->Parent.getStats().Drunkenness <= 30.0F) {
 byte22 = 1;
 }

 if (this->Parent.getBodyDamage().getTemperature() < 35.0F &&
 this->Parent.getStats().Drunkenness <= 70.0F) {
 byte22 = 2;
 }

 if (this->Parent.getBodyDamage().getTemperature() < 30.0F) {
 byte22 = 3;
 }

 if (this->Parent.getBodyDamage().getTemperature() < 25.0F) {
 byte22 = 4;
 }
 }

 if (byte22 != this->getLevel() ||
 byte22 > 0 && this->chevronDifference(int1, boolean1, color) {
 this->SetLevel(byte22);
 this->setChevron(int1, boolean1, color);
 boolean0 = true;
 }
 }

 if (this->Type == MoodleType.Windchill) {
 uint8_t byte23 = 0;
 if (this->Parent instanceof IsoPlayer) {
 float float3 =
 Temperature.getWindChillAmountForPlayer((IsoPlayer)this->Parent);
 if (float3 > 5.0F) {
 byte23 = 1;
 }

 if (float3 > 10.0F) {
 byte23 = 2;
 }

 if (float3 > 15.0F) {
 byte23 = 3;
 }

 if (float3 > 20.0F) {
 byte23 = 4;
 }
 }

 if (byte23 != this->getLevel()) {
 this->SetLevel(byte23);
 boolean0 = true;
 }
 }

 return boolean0;
 }
}
} // namespace Moodles
} // namespace characters
} // namespace zombie
