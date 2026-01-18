#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/Color.h"
#include <algorithm>

namespace zombie {
namespace characters {
namespace Moodles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Moodles {
public:
 bool MoodlesStateChanged = false;
 private Stack<Moodle> MoodleList = std::make_unique<Stack<>>();
 const IsoGameCharacter Parent;

 public Moodles(IsoGameCharacter parent) {
 this->Parent = parent;
 this->MoodleList.add(new Moodle(MoodleType.Endurance, this->Parent);
 this->MoodleList.add(new Moodle(MoodleType.Tired, this->Parent);
 this->MoodleList.add(new Moodle(MoodleType.Hungry, this->Parent);
 this->MoodleList.add(new Moodle(MoodleType.Panic, this->Parent);
 this->MoodleList.add(new Moodle(MoodleType.Sick, this->Parent);
 this->MoodleList.add(new Moodle(MoodleType.Bored, this->Parent);
 this->MoodleList.add(new Moodle(MoodleType.Unhappy, this->Parent);
 this->MoodleList.add(new Moodle(MoodleType.Bleeding, this->Parent);
 this->MoodleList.add(new Moodle(MoodleType.Wet, this->Parent);
 this->MoodleList.add(new Moodle(MoodleType.HasACold, this->Parent);
 this->MoodleList.add(new Moodle(MoodleType.Angry, this->Parent);
 this->MoodleList.add(new Moodle(MoodleType.Stress, this->Parent);
 this->MoodleList.add(new Moodle(MoodleType.Thirst, this->Parent);
 this->MoodleList.add(new Moodle(MoodleType.Injured, this->Parent);
 this->MoodleList.add(new Moodle(MoodleType.Pain, this->Parent);
 this->MoodleList.add(new Moodle(MoodleType.HeavyLoad, this->Parent);
 this->MoodleList.add(new Moodle(MoodleType.Drunk, this->Parent);
 this->MoodleList.add(new Moodle(MoodleType.Dead, this->Parent);
 this->MoodleList.add(new Moodle(MoodleType.Zombie, this->Parent);
 this->MoodleList.add(new Moodle(MoodleType.FoodEaten, this->Parent);
 this->MoodleList.add(new Moodle(MoodleType.Hyperthermia, this->Parent, 3);
 this->MoodleList.add(new Moodle(MoodleType.Hypothermia, this->Parent, 3);
 this->MoodleList.add(new Moodle(MoodleType.Windchill, this->Parent);
 this->MoodleList.add(new Moodle(MoodleType.CantSprint, this->Parent);
 }

 int getGoodBadNeutral(int MoodleIndex) {
 return MoodleType.GoodBadNeutral(this->MoodleList.get(MoodleIndex).Type);
 }

 std::string getMoodleDisplayString(int MoodleIndex) {
 return MoodleType.getDisplayName(this->MoodleList.get(MoodleIndex).Type, this->MoodleList.get(MoodleIndex).getLevel());
 }

 std::string getMoodleDescriptionString(int MoodleIndex) {
 return MoodleType.getDescriptionText(this->MoodleList.get(MoodleIndex).Type, this->MoodleList.get(MoodleIndex).getLevel());
 }

 int getMoodleLevel(int MoodleIndex) {
 return this->MoodleList.get(MoodleIndex).getLevel();
 }

 int getMoodleLevel(MoodleType MType) {
 return this->MoodleList.get(MoodleType.ToIndex(MType).getLevel();
 }

 int getMoodleChevronCount(int moodleIndex) {
 return this->MoodleList.get(moodleIndex).getChevronCount();
 }

 bool getMoodleChevronIsUp(int moodleIndex) {
 return this->MoodleList.get(moodleIndex).isChevronIsUp();
 }

 Color getMoodleChevronColor(int moodleIndex) {
 return this->MoodleList.get(moodleIndex).getChevronColor();
 }

 MoodleType getMoodleType(int MoodleIndex) {
 return this->MoodleList.get(MoodleIndex).Type;
 }

 int getNumMoodles() {
 return this->MoodleList.size();
 }

 void Randomise() {
 }

 bool UI_RefreshNeeded() {
 if (this->MoodlesStateChanged) {
 this->MoodlesStateChanged = false;
 return true;
 } else {
 return false;
 }
 }

 void setMoodlesStateChanged(bool refresh) {
 this->MoodlesStateChanged = refresh;
 }

 void Update() {
 for (int int0 = 0; int0 < this->MoodleList.size(); int0++) {
 if (this->MoodleList.get(int0).Update()) {
 this->MoodlesStateChanged = true;
 }
 }
 }
}
} // namespace Moodles
} // namespace characters
} // namespace zombie
